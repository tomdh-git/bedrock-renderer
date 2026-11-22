#pragma once
#include "client/features/render/backend/OverlayBackend.h"
#include "client/core/diagnostics/Profiler.h"
#include "client/features/render/backend/D3D12Util.h"

// OverlayBackend's private state, shared by OverlayBackend.cpp (setup, command lists, descriptors) and D3D12UiDraw.cpp (textures, the ImGui draw).
struct OverlayBackendState {
    static constexpr int kSlots = 6;                 // lists in flight: a pass under the UI and one at Present, a few frames
    static constexpr UINT kStaticSrvs = 64;          // ImGui's textures
    static constexpr UINT kDynamicPerSlot = 512;     // descriptors a list can use
    static constexpr size_t kRingBytes = 8u << 20;   // upload memory a list can use (constants, vertices)
    static constexpr int kStamps = 8;                // stage timestamps a list can take besides its start and end
    static constexpr UINT kQueriesPerSlot = 2 + kStamps;
    static constexpr UINT kExtraRtvs = 64;
    static constexpr UINT kDsvs = 8;

    struct Tex {
        ID3D12Resource* res = nullptr;
        UINT slot = 0;
    };

    struct Retired {
        ID3D12Resource* res;
        UINT64 fence; // released once the queue has passed it
    };

    struct Slot {
        ID3D12CommandAllocator* alloc = nullptr;
        ID3D12Resource* ring = nullptr;
        uint8_t* ringMap = nullptr;
        size_t ringUsed = 0;
        UINT dynUsed = 0;
        std::vector<ID3D12Resource*> temps; // upload buffers of this list's texture copies
        UINT64 fence = 0;
        Profiler::Id gpuId = -1; // the current query's row; metric IDs below are cached after first use
        const char* gpuName = nullptr;
        Profiler::Id gpuMetric = -1;
        bool timed = false;
        const char* stageName[kStamps] = {}; // what each stage stamp closed (the stamp holds the time the stage ended)
        Profiler::Id stageId[kStamps] = {-1, -1, -1, -1, -1, -1, -1, -1};
        int stages = 0;
    };

    struct State {
        ID3D12Device* dev = nullptr;
        ID3D12CommandQueue* queue = nullptr; // the game's: not ours to release
        ID3D12RootSignature* root = nullptr;
        std::map<int, ID3D12PipelineState*> pso; // the ImGui pipeline, by target format
        ID3DBlob *vs = nullptr, *ps = nullptr;
        ID3D12DescriptorHeap *rtvHeap = nullptr, *srvHeap = nullptr, *dsvHeap = nullptr;
        UINT rtvStep = 0, srvStep = 0, dsvStep = 0;
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
        UINT bufferCount = 0;
        std::vector<void*> buffers; // the swapchain's buffers (identity only: no reference is held)
        ID3D12GraphicsCommandList* list = nullptr;
        ID3D12Fence* fence = nullptr;
        HANDLE event = nullptr;
        UINT64 value = 0;
        Slot slots[kSlots];
        ID3D12QueryHeap* qHeap = nullptr; // two timestamps per slot: the start and the end of its list
        ID3D12Resource* qBuf = nullptr;
        const UINT64* qData = nullptr;
        UINT64 freq = 0;
        int next = 0;
        std::vector<UINT> freeSrv, freeRtv, freeDsv;
        std::vector<Tex*> textures;
        std::vector<Retired> retired;
        // immediate uploads (textures made now)
        ID3D12CommandAllocator* immAlloc = nullptr;
        ID3D12GraphicsCommandList* immList = nullptr;
        ID3D12Fence* immFence = nullptr;
        UINT64 immValue = 0;
        bool ready = false;
    };
    static State g;

    static void waitFor(UINT64 value);
    static void collectRetired();
    static ID3D12Resource* makeBuffer(UINT64 size, D3D12_HEAP_TYPE type, D3D12_RESOURCE_STATES state);
    static D3D12_CPU_DESCRIPTOR_HANDLE srvCpuAt(UINT slot);
    static D3D12_GPU_DESCRIPTOR_HANDLE srvGpuAt(UINT slot);
    static ID3D12PipelineState* pipelineFor(DXGI_FORMAT format);
    static void uploadTexture(ImTextureData* tex, Tex* t, Slot& s, ID3D12GraphicsCommandList* list);
    static void updateTexture(ImTextureData* tex, Slot& s, ID3D12GraphicsCommandList* list);
    static const char* kShader;
    static void makePipeline();
    static void makeDescriptors(UINT bufferCount);
    static void adoptBackBuffers(IDXGISwapChain* sc, UINT bufferCount);
    static void makeSlots();
    static void makeTimestamps(ID3D12CommandQueue* queue);
    static void makeSync();
    static void releaseSlots();
    static void releaseTextures();
    static void releaseCommands();
    static void releasePipeline();
    struct Geometry;
    static Geometry uploadGeometry(OverlayBackend::Cmd& cmd, ImDrawData* data);
    static void projection(const ImDrawData* data, float (&mvp)[4][4]);
    static void bindState(ID3D12GraphicsCommandList* list, ID3D12PipelineState* pso, const float (&mvp)[4][4], const D3D12_VIEWPORT& vp, const Geometry& geo);
    static void drawCommands(ID3D12GraphicsCommandList* list, ImDrawData* data, const std::function<void()>& rebind);
};
