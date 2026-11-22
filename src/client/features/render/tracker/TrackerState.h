#pragma once
#include "client/features/render/tracker/CommandListTracker.h"
#include "client/features/render/tracker/MaterialIndex.h"
#include "client/features/render/underui/UnderGpu.h"
#include "client/features/hooks/VtableHook.h"

// The tracker's shared state: the view / pipeline tables and the per-list facts. Defined in CommandListTracker.cpp; the command list /
// queue / device detours (TrackerHooks.cpp) feed it.
struct TrackerState {
    struct View {
        uintptr_t res = 0;
        DXGI_FORMAT fmt = DXGI_FORMAT_UNKNOWN;
    };

    struct PsoInfo {
        bool depth = false, depthWrite = false, stencil = false, blend = false;
        uint8_t nrt = 0;
        DXGI_FORMAT rt0 = DXGI_FORMAT_UNKNOWN, dsv = DXGI_FORMAT_UNKNOWN;
        uint32_t vsSize = 0, psSize = 0, vsHash = 0, psHash = 0;
        int srcBlend = 0, dstBlend = 0; // colour blend factors of target 0 (D3D12_BLEND)
        MatRole role = MatRole::Unknown; // what it draws, by the material its shaders belong to
        std::string layout;
        // What the layout says, worked out once when the state is created (the list hooks ask per SetPipelineState and per draw: no string is looked at there).
        bool skinned = false;      // the layout has BLENDINDICES: a skinned mesh
        bool celLayout = false;    // "POSITION,COLOR,TEXCOORD" or "POSITION,COLOR": the sun and moon's, or the stars'
        bool posUvLayout = false;  // "POSITION,TEXCOORD": a face of a sky box
        uint32_t serial = 0;       // which creation this is (sPsoSerial): the game frees states and the allocator hands their addresses to new ones, so an address alone does not say which state it is
    };

    // What a list needs to know about the state it just set: PsoInfo boiled down to flags, small enough to keep per thread.
    struct PsoFacts {
        bool known = false, flat = false, flatBlend = false, cel = false, write = false, blend = false, actor = false, posUv = false;
        MatRole role = MatRole::Unknown;
        uint32_t serial = 0; // PsoInfo::serial (0: a state made before the hooks)
    };
    // Every state made (or made again at an address a freed one had) bumps this: a thread's cached PsoFacts are only good for the generation they were read in.
    static inline std::atomic<uint32_t> sPsoGeneration{1};
    // One number per CreateGraphicsPipelineState, never reused. A twin (LCE, chams) is kept with the serial of the state it was made from and is only ever used for
    // a state with that serial: a twin whose state was freed can never be drawn with by the state that later got its address (a nametag's, the sky's, one of ours).
    static inline std::atomic<uint32_t> sPsoSerial{0};
    static inline thread_local uint32_t tCurSerial = 0; // the serial of tCurGamePso
    static PsoFacts psoFacts(ID3D12PipelineState* pso); // per thread, lock-free once a state has been seen since the last state was created

    // The full description a pipeline state was created from, deep-copied: the desc's own pointers dangle after createGraphicsPipelineState returns,
    // so every blob it points at is owned here - the five shader bytecodes, the input element array and its semantic name strings, the stream output
    // and its names/strides, and the cached blob. LceRenderer builds a twin from this (a clone with our pixel shader); the game's root signature is
    // the one pointer kept, with a reference held so a twin can outlive the game's own pipeline states.
    struct Retained {
        D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};
        std::vector<uint8_t> vs, ps, ds, hs, gs, cachedPso;
        std::vector<std::string> semantics;
        std::vector<D3D12_INPUT_ELEMENT_DESC> elements;
        std::vector<std::string> soSemantics;
        std::vector<D3D12_SO_DECLARATION_ENTRY> soEntries;
        std::vector<UINT> soStrides;
        MatRole role = MatRole::Unknown;
        uint32_t serial = 0; // PsoInfo::serial of the state this describes
    };

    static std::mutex sPsoMu;
    static std::unordered_map<uintptr_t, PsoInfo> sPsos; // pipeline state object -> what it was created with
    static std::mutex sRetainedMu;
    static std::unordered_map<uintptr_t, Retained> sRetained; // pipeline state object -> the description it was created from, deep-copied
    static std::atomic<ID3D12Device*> sDevice;                 // the game's device, captured at the first pipeline state created after the hooks went in
    static ID3D12Device* device() { return sDevice.load(std::memory_order_relaxed); }
    static void forgetRetained();                              // eject: release every retained desc's root signature reference
    // While LceRenderer builds one of its twins, the device hook must not retain it: its pixel shader is ours, and its vertex shader is the game's, so it
    // would classify as the game's role and nest another twin inside it.
    static inline thread_local bool tCreatingTwin = false;
    // The state the list being recorded on this thread last set: the game's own (before any LCE twin) and what was really bound. The chams draw hooks swap a twin in around a draw.
    static inline thread_local ID3D12GraphicsCommandList* tCurList = nullptr;
    static inline thread_local ID3D12PipelineState* tCurGamePso = nullptr;
    static inline thread_local ID3D12PipelineState* tCurBound = nullptr;
    // The render targets the list on this thread last bound (what the game set, after any substitution of ours): the chams twin draws rebind them with a depth buffer
    // of their own and put these back.
    static inline thread_local ID3D12GraphicsCommandList* tRtList = nullptr;
    static inline thread_local UINT tRtCount = 0;
    static inline thread_local BOOL tRtSingle = FALSE;
    static inline thread_local D3D12_CPU_DESCRIPTOR_HANDLE tRts[8] = {};
    static inline thread_local bool tRtHasDs = false;
    static inline thread_local D3D12_CPU_DESCRIPTOR_HANDLE tRtDs = {};
    static inline thread_local ID3D12GraphicsCommandList* tChamsDepthList = nullptr; // the list whose chams depth has been cleared in this recording
    // The scissor rectangles the list on this thread last set (bgfx sets them when they change): put back after a chams draw that narrowed them.
    static inline thread_local ID3D12GraphicsCommandList* tScissorList = nullptr;
    static inline thread_local UINT tScissorCount = 0;
    static inline thread_local D3D12_RECT tScissor[8] = {};
    static std::mutex sViewMu;
    static std::unordered_map<uintptr_t, View> sViews; // descriptor handle -> what it views

    static void** sDevVt;
    static void** sListVt;

    // What the UnderUI layer needs to know about every recorded list.
    static std::mutex sFactsMu;
    static std::unordered_map<uintptr_t, ListFacts> sFacts;
    static std::atomic<uintptr_t> sBackBuffers[8]; // the swapchain's buffers (refreshed every Present)
    static std::atomic<uintptr_t> sFrameTarget;    // the buffer that went PRESENT -> RENDER_TARGET this frame
    static std::atomic<uintptr_t> sSwapHandle;     // the render target view handle of that buffer, for views created before injection

    static bool isBackBuffer(uintptr_t res);
    static bool isSwapHandle(uintptr_t handle);   // a render target view handle of a swapchain buffer (learned from the acquire barrier, for views created before injection)
    static void rememberSwapHandle(uintptr_t handle);
    static void forgetSwapHandles();

    // The renderer records a list on one thread, call after call. The facts of a list live in a node of an unordered_map (nodes never move, and
    // a reset clears one in place instead of erasing it), so the thread keeps a pointer to the list it is on and only the first call per list
    // takes the lock: these hooks run thousands of times a frame.
    static inline thread_local uintptr_t tFactsList = 0;
    static inline thread_local ListFacts* tFacts = nullptr;

    template <typename F>
    static void facts(void* list, F fn) {
        const auto key = reinterpret_cast<uintptr_t>(list);
        if (tFactsList != key || !tFacts) {
            std::lock_guard<std::mutex> lk(sFactsMu);
            tFacts = &sFacts[key];
            tFactsList = key;
        }
        fn(*tFacts);
    }

    static void noteDraw(void* list, uint32_t elements);
    static View viewOf(uintptr_t handle);
    static std::atomic<uintptr_t> sSwapHandles[8];
    static std::unique_ptr<VtableHook> sDraw;
    static std::unique_ptr<VtableHook> sDrawIdx;
    static std::unique_ptr<VtableHook> sPso;
    static std::unique_ptr<VtableHook> sBarrier;
    static std::unique_ptr<VtableHook> sOmRt;
    static std::unique_ptr<VtableHook> sStencilRef;
    // The stencil reference the list on this thread last set (the chams twin draws set their own and put this back).
    static inline thread_local ID3D12GraphicsCommandList* tStencilList = nullptr;
    static inline thread_local UINT tStencilRef = 0;
    static void __stdcall omSetStencilRef(ID3D12GraphicsCommandList* self, UINT ref);
    static std::unique_ptr<VtableHook> sClearRt;
    static std::unique_ptr<VtableHook> sClearDs;
    static std::unique_ptr<VtableHook> sReset;
    static std::unique_ptr<VtableHook> sScissor;
    static std::unique_ptr<VtableHook> sExecute;
    static std::unique_ptr<VtableHook> sCreateRtv;
    static std::unique_ptr<VtableHook> sCreateDsv;
    static std::unique_ptr<VtableHook> sCopyDescSimple;
    static std::unique_ptr<VtableHook> sCopyDesc;
    static std::unique_ptr<VtableHook> sCreatePso;
    static void __stdcall drawInstanced(ID3D12GraphicsCommandList* self, UINT vc, UINT ic, UINT sv, UINT si);
    static void __stdcall drawIndexedInstanced(ID3D12GraphicsCommandList* self, UINT ic, UINT inst, UINT si, INT bv, UINT sinst);
    static void probeUnknownPso(ID3D12PipelineState* pso);
    static void __stdcall setPipelineState(ID3D12GraphicsCommandList* self, ID3D12PipelineState* pso);
    static void __stdcall rsSetScissorRects(ID3D12GraphicsCommandList* self, UINT n, const D3D12_RECT* rects);
    static void __stdcall resourceBarrier(ID3D12GraphicsCommandList* self, UINT n, const D3D12_RESOURCE_BARRIER* barriers);
    static std::atomic<uintptr_t> sSwapDepthHandle; // the unknown depth view the swapchain pass uses (learned from a bind)
    static std::atomic<bool> sOwnDepthOn;      // the swapchain pass draws into our depth buffer
    static void __stdcall omSetRenderTargets(ID3D12GraphicsCommandList* self, UINT n, const D3D12_CPU_DESCRIPTOR_HANDLE* rts, BOOL single, const D3D12_CPU_DESCRIPTOR_HANDLE* ds);
    static void __stdcall clearRenderTargetView(ID3D12GraphicsCommandList* self, D3D12_CPU_DESCRIPTOR_HANDLE h, const FLOAT color[4], UINT nr, const D3D12_RECT* r);
    static void __stdcall clearDepthStencilView(ID3D12GraphicsCommandList* self, D3D12_CPU_DESCRIPTOR_HANDLE h, D3D12_CLEAR_FLAGS flags, FLOAT depth, UINT8 stencil, UINT nr, const D3D12_RECT* r);
    static HRESULT __stdcall reset(ID3D12GraphicsCommandList* self, ID3D12CommandAllocator* alloc, ID3D12PipelineState* pso);
    static HRESULT __stdcall createGraphicsPipelineState(ID3D12Device* self, const D3D12_GRAPHICS_PIPELINE_STATE_DESC* d, REFIID riid, void** pp);
    static void runExecute(ID3D12CommandQueue* q, UINT n, ID3D12CommandList* const* lists);
    static void __stdcall executeCommandLists(ID3D12CommandQueue* self, UINT n, ID3D12CommandList* const* lists);
    static void __stdcall createRenderTargetView(ID3D12Device* self, ID3D12Resource* res, const D3D12_RENDER_TARGET_VIEW_DESC* desc, D3D12_CPU_DESCRIPTOR_HANDLE h);
    static void __stdcall createDepthStencilView(ID3D12Device* self, ID3D12Resource* res, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc, D3D12_CPU_DESCRIPTOR_HANDLE h);
    static bool isViewHeap(D3D12_DESCRIPTOR_HEAP_TYPE t);
    static void copyView(UINT64 dst, UINT64 src);
    static void __stdcall copyDescriptorsSimple(ID3D12Device* self, UINT n, D3D12_CPU_DESCRIPTOR_HANDLE dst, D3D12_CPU_DESCRIPTOR_HANDLE src, D3D12_DESCRIPTOR_HEAP_TYPE type);
    static void __stdcall copyDescriptors(ID3D12Device* self, UINT nd, const D3D12_CPU_DESCRIPTOR_HANDLE* ds, const UINT* dsz, UINT ns, const D3D12_CPU_DESCRIPTOR_HANDLE* ss, const UINT* ssz, D3D12_DESCRIPTOR_HEAP_TYPE type);
};
