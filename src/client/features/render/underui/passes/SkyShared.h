#pragma once
#include "client/features/render/underui/passes/Passes.h"
#include "client/features/render/underui/UnderGpu.h"

// What the sky / menu-background / fog passes share: the pictures they draw into (SkyGpu), the settings the Ambience module hands over,
// the bake state, and the helpers that bind and fill them. State lives in SkySupport.cpp, the drawing in SkyInject.cpp, the layers
// (passes) in SkyPass.cpp.
struct SkyImpl {
    // The pictures the passes make and read: the environment maps, the menu picture, the noise lattices, their descriptors.
    struct SkyGpu {
        GpuPtr<ID3D12RootSignature> root;
        GpuPtr<ID3D12DescriptorHeap> skyRtvHeap; // four views: one per bake texture and the menu picture
        GpuPtr<ID3D12DescriptorHeap> srvHeap;    // shader visible: the bake textures
        GpuPtr<ID3D12Resource> tex[3];
        GpuPtr<ID3D12Resource> lat3; // the noise lattices
        GpuPtr<ID3D12Resource> lat2;
        UINT skyW = 0, skyH = 0; // the environment maps
        GpuPtr<ID3D12Resource> menuTex;
        bool menuClear = false; // the picture was just made: it is cleared before the first phase is drawn over it
        UINT menuW = 0, menuH = 0;
        UINT rtvStep = 0, srvStep = 0;
    };
    static SkyGpu g;

    // What the layers are told every frame (written on the Present thread, read on the render thread). From the Ambience module.
    struct SkySettings {
        bool skyOn = false;
        int style = 0;
        bool theme = true;
        float gain = 0.6f;       // brightness of the shader in a Vibrant Visuals (HDR) scene
        bool hideCelestial = false;
        int resolution = 0; // 0 native, 1 three quarters, 2 half
        bool fogOn = false;
        float fogStart = 80.f, fogEnd = 170.f; // blocks
        bool fogGround = true;
        float fogHeight = 20.f; // blocks above the camera
    };

    static Render::PassSettings<SkySettings> sSettings; // published by SkyPass::poll from the Ambience module

    static std::atomic<float> sSkyTarget; // 1 while the sky/menu shader is wanted, 0 when it is off (the toggle or the module): it fades between them
    static std::atomic<float> sRamp;      // the fade, 0..1, moved towards the target a frame at a time (frameClock, on the thread that draws)
    static inline constexpr float kRampSeconds = 0.6f;
    static std::atomic<uint32_t> sThemeA, sThemeB;

    // The frame's theme colours, taken once at frame start (SkyPass::wanted) instead of per draw: poll publishes the pair on the Present
    // thread, and a draw that catches it half-moved shows a gradient of two generations for a frame.
    static thread_local uint32_t sFrameThemeA, sFrameThemeB;

    // The frame's near and far plane, also taken once at frame start: the fog reads the pair here for the whole frame. The atomics they
    // come from are stored one after the other by the Present thread (setProjection, once per presented frame), and a fog that re-reads
    // them mid-frame can linearise the depth by a pair from two different projections - the fog band a frame at the wrong distance.
    static thread_local float sFrameNear, sFrameFar; // the fog stays off while sFrameNear is 0

    static inline constexpr UINT kConstants = 56;    // A-L: the constants skyConstants writes
    static inline constexpr UINT kRootConstants = 56; // A-L: the root signature's constants, exactly kConstants
    static inline constexpr UINT kFOffset = 28;      // the fog's float4 (near plane, far plane, start, end)
    static inline constexpr UINT kIOffset = 40;      // the fog's I slot: x = ground-fog mix, y = fog height (blocks)

    static inline constexpr float kBudgetMs = 1.2f;  // what the shader may cost a frame: it is drawn in slices over as many frames as that takes
    static inline constexpr int kMaxBands = 6;       // ... but a picture is never older than this many frames
    static inline constexpr float kFadeSeconds = 0.45f;
    static inline constexpr UINT kSrvCount = 31;     // [m0 m1 m2 m0 m1 | m0 m0 | m1 m1 | m2 m2 | menu menu | lattice3 lattice2]: pairs of pictures (a map twice: previous = current)
    static inline constexpr UINT kMenuAt = 11;       // the menu picture, twice
    static inline constexpr UINT kNoiseAt = 13;      // the noise lattices (see resources/shaders/common.hlsl)
    static inline constexpr UINT kDepthAt = 15;      // the scene's depth for the fog, a ring of descriptors (one a frame; the GPU may still be reading the last few)
    static inline constexpr UINT kDepthRing = 16;
    static inline constexpr float kCycleSeconds = 0.4f;  // an environment map is drawn over this long

    static double sFrameSeconds; // how long a frame takes (smoothed), from the calls that draw the sky

    // What to draw in the sky layer: a shader, and whether it takes the client theme or its own palette.
    struct SkyPick {
        const char* key = nullptr;
        bool theme = false;
        bool menu = false; // the main menu's background: no camera
        float scale = 1.0f;    // the menu picture's size against the game's target
        bool interleave = false; // an expensive menu shader: a quarter of its pixels are drawn each frame
        float envScale = 1.0f; // the sky map's size against the screen's height
        float interval = 0.05f; // the longest a picture may take to be drawn (seconds): a menu's motion is all in it, a sky's turns are made up by the lookup
        float gain = 0.6f;
    };

    struct Bake {
        std::string key;
        int p = 0, c = 0, w = 0;      // environment maps: previous, current, work
        bool have = false;            // a first map is complete
        int band = 0, bands = 16;     // the slice being drawn / how many a map takes
        float time = 0.f;             // the instant the work map is drawn for
        float phase = 1.f;            // crossfade, previous -> current
        ULONGLONG fadeStart = 0;      // the shader fades in over the game's picture
    };
    static Bake bake;
    static bool sMenuTable; // the next pass reads the menu picture, not the environment maps

    struct FogParams {
        float nearPlane = 0.f, farPlane = 0.f;
        float startBlocks = 80.f, endBlocks = 170.f;
        float groundMix = 0.f, heightBlocks = 20.f;
    };

    static void makeNoise(ID3D12CommandQueue* q, Render::UnderUI::ExecFn run);
    static SkyPick currentPick(const SkySettings& s);
    static float skySeconds();
    static void skyConstants(float* c, const SkyPick& pick, float w, float h, bool hdr, const UnderCamera& cam, bool composite, bool envBake = false);
    static D3D12_CPU_DESCRIPTOR_HANDLE skyRtv(int i);
    static D3D12_CPU_DESCRIPTOR_HANDLE srvAt(UINT i);
    static bool ensureEnv(UINT w, UINT h); // true when the maps were (re)made
    static bool ensureMenu(UINT w, UINT h);
    static UINT tableStart();
    static void bindTable();
    static void frameClock();
    static UINT envWidth(UINT screenHeight, float scale);

    static void skyInit(ID3D12CommandQueue* q, Render::UnderUI::ExecFn run);
    static void skyShutdown();
    static bool injectMenu(ID3D12CommandQueue* q, const SkyPick& pick, const UnderTarget& tg, Render::UnderUI::ExecFn run);
    static bool injectEnv(ID3D12CommandQueue* q, const SkyPick& pick, const UnderTarget& tg, Render::UnderUI::ExecFn run);
    static bool injectSky(ID3D12CommandQueue* q, const SkyPick& pick, const UnderTarget& tg, Render::UnderUI::ExecFn run);
    static void injectFog(ID3D12CommandQueue* q, const SkyPick& pick, const UnderTarget& tg, const FogParams& fp, Render::UnderUI::ExecFn run);
    static UnderShaderDef resolveSky(const std::string& name);
    static void createRootSignature(ID3D12Device* dev);
    static void createHeaps(ID3D12Device* dev);
    static void warmPipelines();
    static constexpr UINT kNoiseSize = 256;
    static float latticeHash(float x, float y);
    static void fillLattices(std::vector<uint8_t>& lat3, std::vector<uint8_t>& lat2);
    static void copyLattice(ID3D12Resource* upload, ID3D12Resource* tex, UINT64 offset, DXGI_FORMAT format, UINT pitch);
    static ID3D12Resource* skyMakeTarget(UINT w, UINT h, DXGI_FORMAT format);
    struct Pipelines;
    // The pipelines the passes draw with, kept: UnderGpu::pipeline takes a lock and looks up a map on every call, and the target's format and
    // sample count only change with a resize or a graphics change. skyInit and skyShutdown clear the cache; a null pointer is asked for again
    // while the background builder compiles it.
    struct PsoCache {
        ID3D12PipelineState* picture = nullptr;
        std::string pictureKey;
        DXGI_FORMAT pictureFormat = DXGI_FORMAT_UNKNOWN;
        ID3D12PipelineState* composite = nullptr;
        DXGI_FORMAT compositeFormat = DXGI_FORMAT_UNKNOWN;
        UINT compositeSamples = 0;
        DXGI_FORMAT compositeDepth = DXGI_FORMAT_UNKNOWN;
        ID3D12PipelineState* fog = nullptr;
        DXGI_FORMAT fogFormat = DXGI_FORMAT_UNKNOWN;
        UINT fogSamples = 0;
        DXGI_FORMAT fogDepth = DXGI_FORMAT_UNKNOWN;
    };
    static PsoCache psoCache;
    static Pipelines pipelinesFor(const SkyPick& pick, DXGI_FORMAT pictureFormat, const UnderTarget& tg);
    static void drawPicture(ID3D12Resource* target, int rtvIndex, bool clear, const D3D12_VIEWPORT& viewport, const D3D12_RECT& scissor, const UnderGpu::Bound& b, const float* constants);
    static void compositeOnto(const SkyPick& pick, const UnderGpu::Bound& b, ID3D12PipelineState* composite);
    static void prepareMenuPicture(const SkyPick& pick, const D3D12_RESOURCE_DESC& rd);
    static void drawMenuPicture(const SkyPick& pick, const UnderGpu::Bound& b);
    static void prepareBake(const SkyPick& pick, const D3D12_RESOURCE_DESC& rd);
    static void drawBakeSlice(const SkyPick& pick, const UnderGpu::Bound& b);
    static void advanceBake();
    // What the Sky pass decided for the frame being executed: the pick (fading out counts) and the settings. Thread-local: execute() runs
    // for the game's lists on the render thread and again for the overlay's own list on the Present thread (OverlayBackend submits it
    // through the hooked queue), and each execution must draw by its own decisions, never by another thread's half-written ones.
    static thread_local SkySettings sNow;
    static thread_local SkyPick sPick;
    static thread_local bool sSkyOn;
    class SkyPass;
    class FogPass;
};
