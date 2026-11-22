#pragma once
#include "client/features/render/backend/D3D12Util.h"
#include "client/features/render/underui/UnderTypes.h"
#include "client/features/hooks/hooks/render/SetupAndRenderHook.h"

// The frame's camera in world space, from the view matrix SetupAndRenderHook captures (rows: right, up, back; the camera looks down -z of the
// view), its position and the level renderer's projection scale (the same convention as WorldUtils::worldToScreen).
struct UnderCamera {
    float right[3] = {1, 0, 0}, up[3] = {0, 1, 0}, fwd[3] = {0, 0, -1};
    float pos[3] = {0, 0, 0};
    float fov[2] = {1, 1};
    float player[3] = {0, 0, 0}; // the local player's eye position that frame
    double time = 0;             // when the game captured it (seconds)
    bool valid = false;
    uint32_t seq = 0; // counts the cameras taken from the game: a new number is a new frame's camera
};

// What a shader of ours is made of; resolved on the builder thread (see UnderGpu::addShaders).
struct UnderShaderDef {
    std::string vsSource, vsName;
    std::string psSource, psName;
    ID3D12RootSignature* root = nullptr;
    bool blend = false;  // source alpha over the target (the composites and the fog); off: the pass overwrites
    bool depth = false;  // depth tested against the scene's depth (read only, less or equal), when the pipeline has a depth format
};

// The D3D12 plumbing every UnderUI pass shares: our device objects, one command list on a ring of allocators with a fence, GPU timestamps, the
// resource states followed at the point of the queue we submit at, the game's target bound for drawing, and the shader pipelines (compiled and
// created on a worker thread: the compile and the driver's own compile of a heavy shader take a second or more, which must never be a hitch in a frame).
struct UnderGpu {
    static constexpr int kRing = 64; // command allocators: four or five lists a frame (the layers) for as many frames as the GPU can be behind: when the ring is short the CPU waits for the GPU
    static constexpr int kPairs = 32; // GPU timestamp pairs in flight
    enum Timer { SkyShader = 0, Fog = 1, Composite = 2, Blur = 3, BlurCopy = 4, BlurDof = 5, BlurDraw = 6, TimerCount };

    static inline ID3D12Device* dev = nullptr;
    static inline ID3D12GraphicsCommandList* list = nullptr; // the one list a pass records into: beginList ... submit
    static inline std::atomic<bool> inWorld{false};
    static inline std::atomic<float> nearPlane{0.f}, farPlane{0.f}; // the frame's projection (see discoverProjection); 0 until found

    static void ensure(ID3D12CommandQueue* queue); // the device objects, on first use
    static void waitIdle();
    static void beginList(ID3D12PipelineState* pso);
    static void submit(ID3D12CommandQueue* queue, UnderExec run);

    // GPU time of a stretch of the list. harvest() collects the finished ones (once a frame); a timer's smoothed average and its window sum:
    static int beginTimed();
    static void endTimed(int pair, Timer timer, int bands = 1);
    static void harvest();
    static inline double ema[TimerCount] = {};     // smoothed ms of one measurement, scaled by `bands` (the cost of the whole thing)
    static inline double sumMs[TimerCount] = {};   // since the last takeWindow
    static inline UINT count[TimerCount] = {};
    static void takeWindow();                      // zero the sums

    // What state each resource is in at the point of the queue we are submitting at.
    static inline std::unordered_map<uintptr_t, uint32_t> state;
    static uint32_t resourceState(uintptr_t resource, uint32_t fallback) {
        const auto it = state.find(resource);
        return it == state.end() ? fallback : it->second;
    }
    static void forgetState(uintptr_t resource) { state.erase(resource); }

    // The game's target (and its depth) for drawing to: both brought into the states we need, with the barriers that give them back as the game
    // left them.
    struct Bound {
        D3D12_RESOURCE_DESC rd{};
        DXGI_FORMAT dsv = DXGI_FORMAT_UNKNOWN;
        bool hdr = false;
        std::vector<D3D12_RESOURCE_BARRIER> before, after;
        D3D12_CPU_DESCRIPTOR_HANDLE rtv{}, dsvHandle{};
        bool hasDepth = false;
    };
    static Bound prepareTarget(const UnderTarget& target);
    static void bindAndSize(const Bound& b);
    static D3D12_CPU_DESCRIPTOR_HANDLE rtvFor(ID3D12Resource* target); // a render target view of the whole resource (valid until the next call)
    static DXGI_FORMAT dsvFormatOf(DXGI_FORMAT typeless);
    static D3D12_RESOURCE_BARRIER transition(ID3D12Resource* r, UINT have, UINT want);

    // Shader pipelines. A name belongs to the resolver registered for its prefix (it runs on the worker). pipeline() gives the built state, or asks for
    // it and gives null: the layer waits for it, the frame goes on. warm() asks without waiting.
    using Resolver = UnderShaderDef (*)(const std::string& name);
    static void addShaders(const char* prefix, Resolver resolver);
    static ID3D12PipelineState* pipeline(const std::string& name, DXGI_FORMAT format, UINT samples, DXGI_FORMAT depth);
    static void warm(const std::string& name, DXGI_FORMAT format, UINT samples, DXGI_FORMAT depth);
    static void startBuilder();
    static void stopBuilder();

    // The camera of the frame being drawn (written on the Present thread, read on the render thread) and the projection.
    static UnderCamera cameraOf(const SetupAndRenderHook::Transform& t); // the camera of a captured frame (seq is not set)
    static UnderCamera camera();
    static void setCamera(const UnderCamera& c);
    static void discoverProjection(HWND window);      // fallback: looks for the matrix in the client instance
    static bool setProjection(const float* m);        // from the level renderer's projection matrix: near and far plane; false when it is not a projection

    // The swapchain pass's depth buffer, owned by us (see RenderTraceHooks.cpp): the game's view of its own was made before we hooked and is unknown, so while a
    // pass wants the scene's depth the swapchain pass is bound to this one instead. ownDepthWanted is set by the engine each frame.
    static inline std::atomic<bool> ownDepthWanted{false};
    static bool ownDepthFor(ID3D12GraphicsCommandList* list, ID3D12Resource* swapchainBuffer, D3D12_CPU_DESCRIPTOR_HANDLE& view, uintptr_t& resource);
    static void dropOwnDepth(); // the swapchain is resized, or we are shutting down

    // The scene's depth in a form a shader can sample. The game's depth buffer is a typed depth format (D24_UNORM_S8_UINT, D32_FLOAT) that cannot have a
    // shader resource view; it is copied, on the list being recorded, into a texture of ours in the typeless format of the same family. A depth that is typeless
    // and sampleable already is read as it is. `view` is the format to read it in.
    struct ReadableDepth {
        ID3D12Resource* source = nullptr; // the game's
        ID3D12Resource* res = nullptr;    // what to read: the game's, or our copy
        DXGI_FORMAT view = DXGI_FORMAT_UNKNOWN;
    };
    static bool readableDepth(ID3D12Resource* depth, ReadableDepth& out); // false: a depth format we do not know
    static void recordDepthCopy(const ReadableDepth& depth);              // on `list`: fills our copy from the game's depth (nothing when it is read as it is)

    static void dropTargets(); // our last list no longer references the game's buffers
    static void shutdown();

    template <typename T>
    static void release(T*& p) { D3D12Util::release(p); }
};
