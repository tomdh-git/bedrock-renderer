#include "client/features/render/underui/passes/SkyShared.h"
#include "client/features/render/backend/D3D12Util.h"
#include "client/features/render/underui/UnderShaders.h"
#include "client/features/render/underui/MenuBackground.h"
#include "client/features/render/underui/SkyInput.h"
#include "client/features/render/Theme.h"
#include "client/core/diagnostics/Profiler.h"
#include "client/features/hooks/hooks/render/FrameFilterHook.h"
#include "client/features/hooks/hooks/render/SetupAndRenderHook.h"

// The shader sky (the Ambience module), the main menu's background shader and the distance fog: the passes of UnderUI's Sky and Fog layers.



UnderShaderDef SkyImpl::resolveSky(const std::string& name) {
    UnderShaderDef d;
    d.vsSource = UnderShaders::preludeSource();
    d.vsName = "prelude";
    d.root = g.root;
    if (name.rfind("sky:", 0) == 0) { // the bake overwrites its texture
        d.psSource = UnderShaders::source(name.c_str() + 4);
        d.psName = name.c_str() + 4;
    } else if (name == "composite") { // fades in over the game's picture
        d.psSource = UnderShaders::compositeSource();
        d.psName = "composite";
        d.blend = true;
        d.depth = true;
    } else { // fog slices are layered over it
        BS_CHECK(name == "fog");
        d.psSource = UnderShaders::fogSource();
        d.psName = "fog";
        d.blend = true; // over the terrain by its own opacity; the depth is read in the shader, not tested
    }
    return d;
}
void SkyImpl::createRootSignature(ID3D12Device* dev) {
    D3D12_ROOT_PARAMETER params[4]{};
    params[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    params[0].Constants = {0, 0, kRootConstants};
    params[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
    D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 2, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
    params[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[1].DescriptorTable = {1, &range};
    params[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    D3D12_DESCRIPTOR_RANGE noiseRange{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 2, 2, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
    params[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[2].DescriptorTable = {1, &noiseRange};
    params[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    D3D12_DESCRIPTOR_RANGE depthRange{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 4, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND}; // the fog reads the scene's depth
    params[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[3].DescriptorTable = {1, &depthRange};
    params[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    const D3D12_STATIC_SAMPLER_DESC ss[2] = {D3D12Util::linearSampler(), D3D12Util::linearSampler(D3D12_TEXTURE_ADDRESS_MODE_WRAP, 1)}; // the noise lattices wrap
    D3D12_ROOT_SIGNATURE_DESC rd{4, params, 2, ss, D3D12_ROOT_SIGNATURE_FLAG_NONE};
    g.root = D3D12Util::createRootSignature(dev, rd);
}
void SkyImpl::createHeaps(ID3D12Device* dev) {
    g.skyRtvHeap = GpuUtil::createDescriptorHeap(dev, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 4); // three environment maps and the menu picture
    g.srvHeap = GpuUtil::createDescriptorHeap(dev, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kSrvCount, true);
    g.rtvStep = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    g.srvStep = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

}

// Every shader's pipeline state is built in the background (the current one first): a heavy shader takes a second or more to compile.
void SkyImpl::warmPipelines() {
    const DXGI_FORMAT menuFmt = DXGI_FORMAT_R16G16B16A16_FLOAT, skyFmt = DXGI_FORMAT_R10G10B10A2_UNORM;
    const auto menuIndex = static_cast<size_t>(std::max(MenuBackground::index(), 1)) - 1;
    if (menuIndex < UnderShaders::menu().size())
        UnderGpu::warm(std::string("sky:") + UnderShaders::menu()[menuIndex].key, menuFmt, 1u, DXGI_FORMAT_UNKNOWN);
    for (const auto& e : UnderShaders::sky())
        UnderGpu::warm(std::string("sky:") + e.key, skyFmt, 1u, DXGI_FORMAT_UNKNOWN);
    for (const auto& e : UnderShaders::menu())
        UnderGpu::warm(std::string("sky:") + e.key, menuFmt, 1u, DXGI_FORMAT_UNKNOWN);
    UnderGpu::startBuilder();
}
void SkyImpl::skyInit(ID3D12CommandQueue* q, Render::UnderUI::ExecFn run) {
    UnderGpu::ensure(q);
    psoCache = PsoCache{};
    createRootSignature(UnderGpu::dev);
    createHeaps(UnderGpu::dev);
    makeNoise(q, run);
    warmPipelines();
}
void SkyImpl::skyShutdown() {
    psoCache = PsoCache{};
    for (auto& t : g.tex)
        t.reset();
    g.lat3.reset();
    g.lat2.reset();
    g.menuTex.reset();
    g.skyRtvHeap.reset();
    g.srvHeap.reset();
    g.root.reset();
    g.skyW = g.skyH = g.menuW = g.menuH = 0;
    bake = Bake{};
}


// What the sky and the fog share: what the Sky pass decided for the frame being executed (each execute() decides on its own thread's copy).
thread_local SkyImpl::SkySettings SkyImpl::sNow;
thread_local SkyImpl::SkyPick SkyImpl::sPick;
thread_local bool SkyImpl::sSkyOn = false;
// The frame builder reads the mask while it builds a frame ahead of the one being executed, so a mask that lets go of a bit for one execute shows the game's own
// sky (or clouds) in a frame of its own. A bit is given up only after the wish has been gone for a few frames in a row; taking one is immediate.
static uint32_t settledDrop(uint32_t wanted) {
    static thread_local uint32_t sHeld = 0;
    static thread_local int sGone = 0;
    if ((sHeld & ~wanted) == 0) {
        sHeld = wanted;
        sGone = 0;
    } else if (++sGone >= 8) {
        sHeld = wanted;
        sGone = 0;
    } else {
        sHeld |= wanted; // gaining bits at once, losing none yet
    }
    return sHeld;
}

class SkyImpl::SkyPass : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::Sky; }
    const char* name() const override { return "sky / menu background"; }

    void poll() override {
        sThemeA.store(Render::Theme::gradA);
        sThemeB.store(Render::Theme::gradB);
        SkySettings s; // everything stays off while the module is
        const SkyInputState in = SkyInputState::get();
        if (in.enabled) {
            s.skyOn = in.shaderSky;
            s.style = in.style;
            s.theme = in.theme;
            s.resolution = in.resolution;
            s.hideCelestial = in.hideCelestial;
            s.gain = in.gain;
            s.fogOn = in.fogOn;
            s.fogStart = in.fogStart;
            s.fogEnd = in.fogEnd;
            s.fogGround = in.fogGround;
            s.fogHeight = in.fogHeight;
        }
        sSettings.publish(in.enabled, s);
    }

    bool wanted() override {
        const SkySettings cfg = sSettings.get();
        const SkyPick wantedPick = currentPick(cfg);
        // Turning the shader off (its toggle, or the module) fades it out instead of cutting it: the last pick keeps being drawn while the ramp runs down.
        static thread_local SkyPick sLast;
        static thread_local bool sHaveLast = false;
        if (wantedPick.key) {
            sLast = wantedPick;
            sHaveLast = true;
        }
        sSkyTarget.store(wantedPick.key ? 1.f : 0.f);
        if (!wantedPick.key && sRamp.load() <= 0.f)
            sHaveLast = false;
        sPick = !wantedPick.key && sHaveLast ? sLast : wantedPick;
        sNow = cfg;
        sSkyOn = sPick.key != nullptr;
        // The frame's copies, taken once here at frame start: the theme pair and the projection's planes are published on the Present
        // thread while this frame draws, and no draw of the frame may catch either half-moved (see SkyShared.h).
        sFrameThemeA = sThemeA.load();
        sFrameThemeB = sThemeB.load();
        sFrameNear = UnderGpu::nearPlane.load();
        sFrameFar = UnderGpu::farPlane.load();
        // What our sky replaces never gets into the game's frame: the texture pack's sky box and the clouds (the clouds of a game sky are not ours to show over
        // a shader sky), and the sun, the moon and the stars when asked. The game is told at the call that would have made each pass, so there is nothing to
        // recognise in the frame afterwards.
        using F = FrameFilterHook;
        uint32_t drop = 0;
        if (sSkyOn)
            drop |= F::bit(FrameDesc::Cubemap) | F::bit(FrameDesc::LegacyCubemap) | F::bit(FrameDesc::Clouds);
        if (cfg.hideCelestial && UnderGpu::inWorld.load())
            drop |= F::bit(FrameDesc::Stars) | F::bit(FrameDesc::Celestial);
        F::drop(settledDrop(drop));
        return sSkyOn;
    }

    bool hidesSkyBodies() const override { return sNow.hideCelestial && UnderGpu::inWorld.load(); }

    void record(ID3D12CommandQueue* q, Render::UnderUI::ExecFn run, const UnderTarget& tg) override {
        injectSky(q, sPick, tg, run);
    }

    void report(UnderStats& st) override {
        st.gpuShaderMs = UnderGpu::count[UnderGpu::SkyShader] ? UnderGpu::sumMs[UnderGpu::SkyShader] / UnderGpu::count[UnderGpu::SkyShader] : 0.0;
        st.gpuCompositeMs = UnderGpu::count[UnderGpu::Composite] ? UnderGpu::sumMs[UnderGpu::Composite] / UnderGpu::count[UnderGpu::Composite] : 0.0;
        st.gpuFogMs = UnderGpu::count[UnderGpu::Fog] ? UnderGpu::sumMs[UnderGpu::Fog] / UnderGpu::count[UnderGpu::Fog] : 0.0;
        st.fullMs = UnderGpu::ema[UnderGpu::SkyShader];
        st.bands = bake.bands;
        st.resolution = sNow.resolution;
        st.mode = !sSkyOn ? "off" : sPick.menu ? "menu background" : "sky";
    }

    void shutdown() override { skyShutdown(); }
};
class SkyImpl::FogPass : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::Fog; }
    const char* name() const override { return "distance fog"; }

    bool wanted() override { // after the sky's wanted(): it needs the sky's picture to fade into, and the planes the sky took at frame start
        return sNow.fogOn && sSkyOn && UnderGpu::inWorld.load() && sFrameNear > 0.f && sFrameFar > sFrameNear;
    }

    bool needsProjection() const override {
        const SkySettings cfg = sSettings.get();
        return cfg.fogOn && cfg.skyOn;
    }

    // The fog reads the scene's depth: it asks for it itself (asked only while the fog is wanted), instead of relying on another pass having asked.
    bool needsDepth() const override { return true; }

    void record(ID3D12CommandQueue* q, Render::UnderUI::ExecFn run, const UnderTarget& tg) override {
        if (!tg.depth)
            return;
        // The terrain ends at the render distance (UnderGpu::farPlane, sampled as sFrameFar at frame start). The fog must be COMPLETE
        // before terrain stops existing, or the drop-off shows through a half-fogged edge at the chunk cliff: clamp the fog end to
        // farPlane so fog completes exactly where terrain stops rendering. Zero margin — any margin leaves a half-fogged band between
        // the last fogged chunk and the chunk edge where the world ends.
        const float fogEnd = std::max(sNow.fogEnd, sNow.fogStart + 4.0f); // keep more than four blocks of ramp
        // effectiveEnd = min(fogEnd, farPlane): fog completes exactly where terrain stops rendering
        // (farPlane follows your render distance). Zero margin — any margin leaves a half-fogged
        // band between the last fogged chunk and the chunk edge where the world ends.
        const float effectiveEnd = fogEnd >= sFrameFar ? sFrameFar * 0.94f : fogEnd; // the last chunk is a ring, the far plane a bit beyond it: complete a little early
        const float start = std::min(sNow.fogStart, effectiveEnd * 0.6f); // a short render distance pulls the whole ramp in, whatever the range slider says
        const FogParams fog{sFrameNear, sFrameFar, start, effectiveEnd, sNow.fogGround ? 1.0f : 0.0f, sNow.fogHeight};
        injectFog(q, sPick, tg, fog, run);
    }
};


void SkyPasses::install() {
    UnderGpu::addShaders("sky:", &SkyImpl::resolveSky);
    UnderGpu::addShaders("composite", &SkyImpl::resolveSky);
    UnderGpu::addShaders("fog", &SkyImpl::resolveSky);
    static SkyImpl::SkyPass sky;
    static SkyImpl::FogPass fog;
    Render::UnderUI::add(&sky); // the fog comes after the sky: it asks what the sky decided
    Render::UnderUI::add(&fog);
}
