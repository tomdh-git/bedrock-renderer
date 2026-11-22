#pragma once
#include "client/features/render/backend/OverlayBackend.h"

// Full screen passes on D3D12 for the glow and the backdrop blur: one root signature (eight constants, two textures, a linear clamp sampler), one full screen
// triangle, a pipeline per (shader, blend, target format), and render targets of the passes' own. Everything is recorded in the caller's OverlayBackend list.
struct FullscreenFx {
    enum Shader { GlowDown, GlowUp, GlowAdaptive, ShadowComp, BlurDown, Blur, BlurComp, Shock, ShaderCount };
    enum Blend { Opaque, Add, Shade, Alpha };

    // A texture a pass can draw to and the next can read: its views, its size, and the state it is in.
    struct Target {
        ID3D12Resource* res = nullptr;
        UINT rtv = 0;
        UINT w = 0, h = 0;
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
        D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    };

    static void init();                    // shaders and the root signature (after OverlayBackend::init)
    static void shutdown();
    static void makeTarget(Target& t, UINT w, UINT h, DXGI_FORMAT format);
    static void freeTarget(Target& t);     // handed to the GPU's retirement: safe for lists still in flight
    static void toState(OverlayBackend::Cmd& cmd, Target& t, D3D12_RESOURCE_STATES to);
    // A copy of a swapchain buffer to read: `copy` is made on demand (same size and format), the buffer must be in COPY_SOURCE.
    static void ensureCopy(Target& copy, UINT w, UINT h, DXGI_FORMAT format);
    // The pass: `a` and `b` (b may be null) are the textures it samples (t0, t1), `rtv` the target it draws to.
    // `scissor`: only these pixels of the target are drawn (the pass is still the whole-screen one: what it samples does not change).
    static void pass(OverlayBackend::Cmd& cmd, Shader shader, Blend blend, ID3D12Resource* a, ID3D12Resource* b, D3D12_CPU_DESCRIPTOR_HANDLE rtv, DXGI_FORMAT rtvFormat, UINT w, UINT h,
        const float constants[8], const D3D12_RECT* scissor = nullptr);

private:
    static const char* kVS;
    static const char* kGlowDown;
    static const char* kGlowUp;
    static const char* kSmooth;
    static const char* kGlowAdaptive;
    static const char* kShadowComp;
    static const char* kBlurDown;
    static const char* kBlur;
    static const char* kBlurComp;
    static const char* kShock;
    static ID3DBlob* compileMain(const char* src, const char* name, const char* target);
    static void setBlend(D3D12_RENDER_TARGET_BLEND_DESC& rt, Blend blend);
    static ID3D12PipelineState* pipeline(Shader shader, Blend blend, DXGI_FORMAT format);

    struct Pipelines {
        ID3D12RootSignature* root = nullptr;
        ID3DBlob* vs = nullptr;
        ID3DBlob* ps[ShaderCount] = {};
        std::map<std::tuple<int, int, int>, ID3D12PipelineState*> pso;
        bool ready = false;
    };
    static Pipelines f;
};
