#include "client/features/render/underui/passes/Passes.h"
#include "client/features/render/underui/passes/MotionBlurPassImpl.h"
#include "client/features/render/backend/D3D12Util.h"
#include "client/features/render/underui/UnderGpu.h"
#include "client/features/render/underui/UnderShaders.h"
#include "client/features/render/underui/CameraMotion.h"
#include "client/features/render/Renderer.h"
#include "client/core/diagnostics/Profiler.h"
#include "client/features/render/underui/feeds/MotionBlurFeed.h"
#include "client/features/hooks/hooks/render/SetupAndRenderHook.h"
#include "client/features/hooks/hooks/render/ActorRenderDispatcherHook.h"

// Motion blur over the finished 3D scene: UnderUI's PostScene layer, before the item in hand, the HUD and every screen (they stay sharp).

struct MotionBlurPassImpl::MbSettings {
    bool dof = true;
    float aperture = 1.0f;
    bool autoFocus = true;
    float focusDistance = 12.0f;
    float shutter = 1.0f;
    bool keepSelf = true;
    int quality = 0; // 0 automatic, 1..4 fixed
    bool fastGather = true;
    float focusSeconds = 0.15f;
};
// MotionBlur::onFrame pushes the module's settings here every frame: the passes draw with what they were last given.
void MotionBlurFeed::publish(bool on, bool nameTags, bool dof, float aperture, bool autoFocus, float focusDistance, float shutter, bool keepOwnPlayerSharp, int quality,
                             bool fastGather, float focusSpeed) {
    MotionBlurPassImpl::sSettings.publish(on, {dof, aperture, autoFocus, focusDistance, shutter, keepOwnPlayerSharp, quality, fastGather, focusSpeed});
    nameTagsOn.store(on && nameTags, std::memory_order_release);
}

struct MotionBlurPassImpl::MbGpu {
    GpuPtr<ID3D12RootSignature> root;
    GpuPtr<ID3D12DescriptorHeap> heap; // shader visible: kMbViews views per ring slot
    GpuPtr<ID3D12Resource> focus[2];   // the focus distance, 1x1: this frame's and the last
    int focusAt = 0;
    bool focusFresh = true;            // the focus has no history yet
    GpuTexture dof;                    // the scene with the depth of field, what the blur reads
    UINT step = 0;
    GpuTexture copy, before, after;
    GpuTexture pack;                   // the scene copy with the distance of each pixel in its alpha (16 bit float), when the depth is read
    UINT slot = 0;
    // The pass's pipelines, kept: UnderGpu::pipeline takes a lock and looks up a map every call, and the format and pass configuration only change with the
    // world's HDR mode and the depth of field, so they are asked for once and reused until that configuration changes (or a pointer is still being built).
    // mbInit and shutdown clear the cache.
    ID3D12PipelineState *pso = nullptr, *psoFocus = nullptr, *psoDof = nullptr, *psoPack = nullptr;
    DXGI_FORMAT cachedFormat = DXGI_FORMAT_UNKNOWN;
    bool cachedDof = false, cachedDofOnly = false, cachedPacked = false;
};
MotionBlurPassImpl::MbGpu MotionBlurPassImpl::mb;
Render::PassSettings<MotionBlurPassImpl::MbSettings> MotionBlurPassImpl::sSettings;

// One file, three pixel shaders: the blur (PS), the focus (PSFocus) and the depth of field (PSDof); the pipeline's entry is always called PS, so the other two get it by name.
UnderShaderDef MotionBlurPassImpl::resolveBlur(const std::string& name) {
    UnderShaderDef d;
    d.vsSource = d.psSource = UnderShaders::blurSource();
    d.vsName = "mblur_vs";
    d.psName = name;
    d.root = mb.root.get();
    if (name != "mblur") {
        const std::string entry = name == "mfocus" ? "PSFocus" : name == "mpack" ? "PSPack" : "PSDof";
        const std::string main = "float4 PS(VSOut i) : SV_Target {";
        const size_t at = d.psSource.find(main);
        BS_CHECK(at != std::string::npos);
        d.psSource.replace(at, main.size(), "float4 PSMain(VSOut i) : SV_Target {");
        d.psSource += "\nfloat4 PS(VSOut i) : SV_Target { return " + entry + "(i); }\n";
    }
    return d;
}
void MotionBlurPassImpl::mbInit() {
    D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, kMbViews, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
    D3D12_ROOT_PARAMETER params[2]{};
    params[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    params[0].Constants = {0, 0, kMbConstants};
    params[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    params[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[1].DescriptorTable = {1, &range};
    params[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    D3D12_STATIC_SAMPLER_DESC ss = D3D12Util::linearSampler();
    ss.Filter = D3D12_FILTER_ANISOTROPIC; // the blur gathers along the streak with anisotropic fetches (explicit-LOD fetches stay plain bilinear)
    ss.MaxAnisotropy = 16;
    D3D12_ROOT_SIGNATURE_DESC rd{2, params, 1, &ss, D3D12_ROOT_SIGNATURE_FLAG_NONE};
    mb.root = D3D12Util::createRootSignature(UnderGpu::dev, rd);
    mb.heap = GpuUtil::createDescriptorHeap(UnderGpu::dev, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kMbViews * kMbRing, true);
    mb.step = UnderGpu::dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    for (auto& f : mb.focus)
        f = GpuUtil::createTexture(UnderGpu::dev, 1, 1, DXGI_FORMAT_R32_FLOAT, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    mb.focusFresh = true;
    mb.pso = mb.psoFocus = mb.psoDof = mb.psoPack = nullptr;
    mb.cachedFormat = DXGI_FORMAT_UNKNOWN;
    mb.cachedDof = mb.cachedDofOnly = mb.cachedPacked = false;
    UnderGpu::startBuilder();
}

// A texture the size and format of the game's target (a copy of it, or of a part of it), in the state a shader reads it in.
void MotionBlurPassImpl::mbEnsure(GpuTexture& t, UINT w, UINT h, DXGI_FORMAT format, D3D12_RESOURCE_FLAGS flags) {
    if (t.matches(w, h, format))
        return;
    UnderGpu::waitIdle();
    t.create(UnderGpu::dev, w, h, format, flags, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

// The state a resource is in at this point of the queue, as followed from the game's barriers (what it is assumed to be when never seen).
UINT MotionBlurPassImpl::mbStateOf(uintptr_t res, UINT fallback) {
    auto it = UnderGpu::state.find(res);
    return it == UnderGpu::state.end() ? fallback : it->second;
}
struct MotionBlurPassImpl::MbFrame {
    bool actorsWanted = false;
    float rect[4] = {};  // the player's box on the screen (uv): min x, min y, max x, max y
    float depth = 0.f;   // how far in front of the camera the player's middle is (blocks)
    int snaps = 0;       // 0 none, 1 before the entities, 2 and after them
    bool gbuffer = false; // the pictures are of the prepass's vector target (Vibrant Visuals), not of the lit scene: they tell where the player is, not what was behind it
};
MotionBlurPassImpl::MbFrame MotionBlurPassImpl::sFrame;
CameraMotion MotionBlurPassImpl::sMo;
int MotionBlurPassImpl::sLevel = 2;           // automatic quality: index into the tables
uint32_t MotionBlurPassImpl::sSinceCheck = 0;
uint32_t MotionBlurPassImpl::sCalm = 0;       // frames the pass has run under budget while a long blur was drawn (the only proof there is room for more samples)
float MotionBlurPassImpl::sEstPx = 0.f;       // the longest blur this frame, in pixels (estimated on the CPU)
uint32_t MotionBlurPassImpl::sFrames = 0;
Vec3 MotionBlurPassImpl::sLastDp{0, 0, 0};    // what the depth gate of the next frame reads (set at the end of measureMotion)
Vec3 MotionBlurPassImpl::sDpSmooth{0, 0, 0};
bool MotionBlurPassImpl::sDpFresh = false;

// The exposure: the shutter as it is set (1 = the film's 1/48 s), nothing else. It used to be held up to the length of the frame so that a low frame rate did not
// strobe, which at a high frame rate meant the shutter slider did nothing below about a third and every trail was as long as the frame: the smear of a low shutter.
double MotionBlurPassImpl::mbExposure(const MbSettings& cfg) {
    return std::clamp(static_cast<double>(cfg.shutter) * kMbFilmExposure, 0.0, 0.1);
}

// A copy of the player's box of the game's target into `tex` (the rest of `tex` is not written and not read).
void MotionBlurPassImpl::mbSnapshot(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg, GpuTexture& tex) {
    UnderGpu::ensure(q);
    auto* rt = reinterpret_cast<ID3D12Resource*>(tg.rt);
    const D3D12_RESOURCE_DESC rd = rt->GetDesc();
    if (rd.SampleDesc.Count != 1)
        return;
    mbEnsure(tex, static_cast<UINT>(rd.Width), rd.Height, rd.Format);
    sFrame.gbuffer = rd.Format == DXGI_FORMAT_R16G16B16A16_FLOAT;
    const UINT x0 = static_cast<UINT>(sFrame.rect[0] * static_cast<float>(rd.Width)), y0 = static_cast<UINT>(sFrame.rect[1] * static_cast<float>(rd.Height));
    const UINT x1 = std::min<UINT>(static_cast<UINT>(rd.Width), static_cast<UINT>(std::ceil(sFrame.rect[2] * static_cast<float>(rd.Width)))),
               y1 = std::min<UINT>(rd.Height, static_cast<UINT>(std::ceil(sFrame.rect[3] * static_cast<float>(rd.Height))));
    if (x1 <= x0 || y1 <= y0)
        return;
    const UINT have = mbStateOf(tg.rt, D3D12_RESOURCE_STATE_RENDER_TARGET);
    const bool toSource = !(have & D3D12_RESOURCE_STATE_COPY_SOURCE);
    D3D12_RESOURCE_BARRIER pre[2], post[2];
    UINT nPre = 0, nPost = 0;
    if (toSource)
        pre[nPre++] = UnderGpu::transition(rt, have, D3D12_RESOURCE_STATE_COPY_SOURCE);
    pre[nPre++] = UnderGpu::transition(tex.res, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_COPY_DEST);
    post[nPost++] = UnderGpu::transition(tex.res, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    if (toSource)
        post[nPost++] = UnderGpu::transition(rt, D3D12_RESOURCE_STATE_COPY_SOURCE, have);
    UnderGpu::beginList(nullptr);
    UnderGpu::list->ResourceBarrier(nPre, pre);
    D3D12_TEXTURE_COPY_LOCATION dst{}, src{};
    dst.pResource = tex.res;
    dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    src.pResource = rt;
    src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    const D3D12_BOX box{x0, y0, 0, x1, y1, 1};
    UnderGpu::list->CopyTextureRegion(&dst, x0, y0, 0, &src, &box);
    UnderGpu::list->ResourceBarrier(nPost, post);
    UnderGpu::submit(q, run);
}

// What the blur measured and saw since the last report (the log line every few seconds).
struct MotionBlurPassImpl::MbDiag {
    int lastSamples = 0;
    uint32_t noResource = 0, noPlanes = 0, badFormat = 0, frames = 0; // frames: no depth resource at the cut, no projection yet, a depth format that cannot be read
    float maxW = 0.f, maxV = 0.f, maxVp = 0.f, maxDp = 0.f;
    float maxEstPx = 0.f; // the longest streak estimated since the last report (the log's "longest streak")
    bool sawDepth = false, sawVectors = false, sawActorLists = false, sawSnaps = false, sawDof = false;
};
MotionBlurPassImpl::MbDiag MotionBlurPassImpl::sDiag;

// One frame of the blur. The steps run in the order MotionBlurPass::record calls them; each leaves what the next one needs here.
struct MotionBlurPassImpl::BlurFrame {
    ID3D12CommandQueue* q;
    UnderExec run;
    const UnderTarget& tg;
    const MbSettings cfg = sSettings.get();
    ID3D12Resource* rt = reinterpret_cast<ID3D12Resource*>(tg.rt);
    ID3D12Resource* depth = reinterpret_cast<ID3D12Resource*>(tg.depth);
    ID3D12Resource* mv = reinterpret_cast<ID3D12Resource*>(tg.aux);
    const D3D12_RESOURCE_DESC rd = rt->GetDesc();
    D3D12_RESOURCE_DESC dd = rd; // the depth's, when it is read
    DXGI_FORMAT depthView = DXGI_FORMAT_UNKNOWN;
    UnderGpu::ReadableDepth rdepth; // the depth as a shader reads it: the game's own, or a copy of ours
    bool hasDepth = false, useMv = false, dofOn = false, dofOnly = false, moving = false, actors = false; // dofOnly: nothing moves, only the depth of field is drawn (straight onto the game's target)
    Vec3 dp, axis{0, 0, 1};
    float turn = 0.f;
    int level = 0;
    ID3D12PipelineState *pso = nullptr, *psoFocus = nullptr, *psoDof = nullptr, *psoPack = nullptr;
    ID3D12Resource *focusPrev = nullptr, *focusCur = nullptr;
    std::vector<D3D12_RESOURCE_BARRIER> pre, toCopy, afterPack, afterFocus, afterDof, post;

    // The depth is read when something on the frame needs a true per-pixel distance: the depth of field always, and the walk whenever the last frame's
    // smoothed displacement was significant. The turn is distance-independent (the shader's arc is exact at any d0), so a frame whose walk term is zero
    // needs no depth — the sky and the far world then also cannot be moved by a wrong single distance; a walking frame reads the depth so every pixel
    // takes its true distance. One frame of lag is invisible. False without a view of the depth, or with a format that cannot be read. False when the
    // scene is multisampled: not supported.
    bool readTargets() {
        // Whether this frame wants the depth at all: the depth of field, or the walk's term from the last frame (set at the end of measureMotion).
        const bool depthWanted = cfg.dof || sLastDp.x * sLastDp.x + sLastDp.y * sLastDp.y + sLastDp.z * sLastDp.z > 1e-8f;
        hasDepth = depthWanted && depth != nullptr && UnderGpu::nearPlane.load() > 0.f && UnderGpu::farPlane.load() > UnderGpu::nearPlane.load();
        ++sDiag.frames;
        sDiag.noResource += depthWanted && depth == nullptr;
        sDiag.noPlanes += depthWanted && UnderGpu::nearPlane.load() <= 0.f;
        if (hasDepth) {
            dd = depth->GetDesc();
            hasDepth = UnderGpu::readableDepth(depth, rdepth);
            depthView = rdepth.view;
            sDiag.badFormat += !hasDepth;
        }
        if (rd.SampleDesc.Count != 1 || dd.SampleDesc.Count != 1) {
            static bool sLogged = false;
            if (!sLogged) {
                sLogged = true;
                Logger::warn("[motionblur] the scene is multisampled ({} / {} samples): not supported yet, the blur stays off", rd.SampleDesc.Count, dd.SampleDesc.Count);
            }
            return false;
        }
        useMv = mv != nullptr;
        return true;
    }

    // The camera one exposure earlier, along the camera's filtered velocity. The exposure is the film's, but never shorter than the frame itself: a frame's
    // whole motion is always covered, so nothing strobes at a low frame rate. Micro-movements are weighted out: a hand on a mouse is never still, and the
    // camera's position jitters; the eye does not see blur in that. The speeds are weighted x^2 / (x^2 + x0^2): nothing at rest, almost all of it well above
    void measureMotion() {
        const float e = static_cast<float>(mbExposure(cfg));
        // The translation: the camera's own velocity, or, when the camera's position is not following (it can move in steps), the player's: they are the same
        // thing in first person and the camera is rigidly on the player in third.
        const Vec3 vt = sMo.v.length() < 0.25f * sMo.vp.length() ? sMo.vp : sMo.v;
        const float speed = vt.length(), spin = sMo.w.length();
        const float gv = speed * speed / (speed * speed + 0.0025f), gw = spin * spin / (spin * spin + 0.0001f);
        dp = vt * (e * gv * kMbWalkBoost);
        // The camera's own velocity oscillates frame to frame (a third-person camera follows with spring physics): this averages the walk's displacement
        // so the blur's strength does not pulse. The turn is NOT smoothed: the eye reads camera flick as crisp.
        if (!sDpFresh) {
            sDpSmooth = dp;
            sDpFresh = true;
        } else {
            sDpSmooth = sDpSmooth * (1.f - kMbMoveSmoothing) + dp * kMbMoveSmoothing;
        }
        dp = sDpSmooth;
        sLastDp = dp; // what the depth gate of the next frame reads
        turn = spin * e * gw;
        moving = sMo.valid && sMo.cur.valid && (dp.length() > 1e-4f || turn > 2e-5f);
        // The longest streak in pixels: the turn at the focal length, the displacement as seen from two blocks away. Below a pixel and a half the blur cannot be
        // seen, and the copy, the barriers and the full screen draw cost the same as for a long one: leave the frame alone. Once a blur is running it takes a
        // shorter streak to keep it running, so a walk at the threshold does not pop the blur on and off.
        sEstPx = moving ? (turn + dp.length() * 0.5f) * sMo.cur.fov[1] * 0.5f * static_cast<float>(rd.Height) : 0.f;
        static bool sWasMoving = false;
        const float gate = sWasMoving ? kMbSkipPixels * 0.4f : kMbSkipPixels;
        if (sEstPx < gate)
            moving = false;
        sWasMoving = moving;
        axis = spin > 1e-9f ? sMo.w * (1.0f / spin) : Vec3{0, 0, 1};
        sDiag.maxW = std::max(sDiag.maxW, sMo.w.length());
        sDiag.maxV = std::max(sDiag.maxV, sMo.v.length());
        sDiag.maxVp = std::max(sDiag.maxVp, sMo.vp.length());
        sDiag.maxDp = std::max(sDiag.maxDp, dp.length());
        sDiag.maxEstPx = std::max(sDiag.maxEstPx, sEstPx); // the report's "longest streak": sEstPx itself only holds this frame's value, 0 on a skipped frame
        // Whether the depth is read was decided in readTargets (the depth of field, or a walk that needs true distances): no copy of it, no decompression of
        // it (reading a depth buffer costs the GPU a decompress), no fetch of it per sample when the frame does not want it.
        dofOn = cfg.dof && hasDepth; // the depth of field needs the depth
    }

    bool somethingToDo() {
        dofOnly = dofOn && !moving && !useMv; // one pass less: the blur would draw nothing
        return useMv || moving || dofOn;      // nothing moves, nothing to focus
    }

    // False while a pipeline is still being built.
    // The scene copy with the distance of each pixel in its alpha: only the depth of field reads it that way. The blur reads the plain copy and the depth itself.
    bool packed() const { return hasDepth && dofOn; }

    bool findPipelines() {
        const bool packedNow = packed();
        const bool configChanged = mb.cachedFormat != rd.Format || mb.cachedDof != dofOn || mb.cachedDofOnly != dofOnly || mb.cachedPacked != packedNow;
        const bool missing = !mb.pso || (dofOn && (!mb.psoFocus || !mb.psoDof)) || (packedNow && !mb.psoPack);
        if (configChanged || missing) {
            mb.pso = UnderGpu::pipeline("mblur", rd.Format, 1, DXGI_FORMAT_UNKNOWN);
            mb.psoFocus = dofOn ? UnderGpu::pipeline("mfocus", DXGI_FORMAT_R32_FLOAT, 1, DXGI_FORMAT_UNKNOWN) : nullptr;
            mb.psoDof = dofOn ? UnderGpu::pipeline("mdof", dofOnly ? rd.Format : kMbPacked, 1, DXGI_FORMAT_UNKNOWN) : nullptr;
            mb.psoPack = packedNow ? UnderGpu::pipeline("mpack", kMbPacked, 1, DXGI_FORMAT_UNKNOWN) : nullptr;
            mb.cachedFormat = rd.Format;
            mb.cachedDof = dofOn;
            mb.cachedDofOnly = dofOnly;
            mb.cachedPacked = packedNow;
        }
        pso = mb.pso;
        psoFocus = dofOn ? mb.psoFocus : nullptr;
        psoDof = dofOn ? mb.psoDof : nullptr;
        psoPack = packedNow ? mb.psoPack : nullptr;
        return pso && (!packedNow || psoPack) && (!dofOn || (psoFocus && psoDof));
    }

    // Automatic quality: the cap on the samples follows the pass's measured cost.
    void chooseQuality() {
        // Automatic follows the level the governor below steps; a fixed quality is that level minus one. The level sets both the sample cap and the spacing (how
        // many places are gathered along the streak), so the governor has something to follow with either gather.
        level = cfg.quality > 0 ? cfg.quality - 1 : sLevel;
        // Down fast, up slowly: a long streak costs several times what a short one does, so climbing on a calm stretch and then meeting a flick
        // would run a whole second at a quality the GPU cannot afford. Room is only proven by a frame that drew a long blur and still fit.
        if (cfg.quality == 0 && ++sSinceCheck >= 6) {
            sSinceCheck = 0;
            const double ms = UnderGpu::ema[UnderGpu::Blur];
            const float cap = kMbSamples[level] * kMbSpacing[level];
            if (ms > kMbBudgetMs * 1.15 && sLevel > 0) {
                --sLevel;
                sCalm = 0;
                UnderGpu::ema[UnderGpu::Blur] = 0; // the next reading is of the new level
            } else if (ms > 0 && ms < kMbBudgetMs * 0.55 && sEstPx > cap * 0.7f) {
                if (++sCalm >= 40 && sLevel < 3) {
                    ++sLevel;
                    sCalm = 0;
                    UnderGpu::ema[UnderGpu::Blur] = 0;
                }
            } else if (ms > kMbBudgetMs * 0.8) {
                sCalm = 0;
            }
        }
        sDiag.lastSamples = kMbSamples[level];
        actors = sFrame.snaps == 2 && mb.before.res && mb.after.res; // the silhouette is what the entity lists drew between the two pictures
        sDiag.sawDepth |= hasDepth;
        sDiag.sawVectors |= useMv;
        sDiag.sawActorLists |= sFrame.actorsWanted;
        sDiag.sawSnaps |= sFrame.snaps == 2;
        sDiag.sawDof |= dofOn;
    }

    void ensureTextures() {
        mbEnsure(mb.copy, static_cast<UINT>(rd.Width), rd.Height, rd.Format);
        if (packed()) {
            mbEnsure(mb.pack, static_cast<UINT>(rd.Width), rd.Height, kMbPacked, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);
        }
        if (dofOn && !dofOnly)
            mbEnsure(mb.dof, static_cast<UINT>(rd.Width), rd.Height, kMbPacked, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);
        focusPrev = mb.focus[mb.focusAt].get();
        focusCur = mb.focus[1 - mb.focusAt].get();
    }

    // States: the scene is copied (and drawn to afterwards), the depth and the vectors are read, and everything goes back as the game left it.
    void buildBarriers() {
        const UINT rtHave = mbStateOf(tg.rt, D3D12_RESOURCE_STATE_RENDER_TARGET);
        const UINT depthHave = hasDepth ? mbStateOf(tg.depth, D3D12_RESOURCE_STATE_DEPTH_WRITE) : 0;
        const UINT mvHave = mv ? mbStateOf(tg.aux, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE) : 0;
        constexpr UINT kRead = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
        constexpr UINT kSrv = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, kRtv = D3D12_RESOURCE_STATE_RENDER_TARGET;
        const bool rtToSource = !(rtHave & D3D12_RESOURCE_STATE_COPY_SOURCE);
        const bool depthToRead = hasDepth && rdepth.res == depth && !(depthHave & kRead); // a copy is read in its own state
        const bool mvToRead = mv && !(mvHave & kRead);
        if (rtToSource)
            pre.push_back(UnderGpu::transition(rt, rtHave, D3D12_RESOURCE_STATE_COPY_SOURCE));
        pre.push_back(UnderGpu::transition(mb.copy.res, kSrv, D3D12_RESOURCE_STATE_COPY_DEST));
        if (depthToRead)
            pre.push_back(UnderGpu::transition(depth, depthHave, kRead));
        if (mvToRead)
            pre.push_back(UnderGpu::transition(mv, mvHave, kRead));
        const UINT rtNow = rtToSource ? D3D12_RESOURCE_STATE_COPY_SOURCE : rtHave;
        toCopy.push_back(UnderGpu::transition(mb.copy.res, D3D12_RESOURCE_STATE_COPY_DEST, kSrv));
        if (packed()) { // the packed copy is drawn from the plain one, then read by everything after
            toCopy.push_back(UnderGpu::transition(mb.pack.res, kSrv, kRtv));
            afterPack.push_back(UnderGpu::transition(mb.pack.res, kRtv, kSrv));
        }
        if (dofOn) { // the focus pass draws to the new focus, then the depth of field pass to its own picture; the blur reads both, and draws to the game's target
            toCopy.push_back(UnderGpu::transition(focusCur, kSrv, kRtv));
            afterFocus.push_back(UnderGpu::transition(focusCur, kRtv, kSrv));
            if (dofOnly) { // the depth of field draws onto the game's target itself
                afterFocus.push_back(UnderGpu::transition(rt, rtNow, kRtv));
            } else {
                afterFocus.push_back(UnderGpu::transition(mb.dof.res, kSrv, kRtv));
                afterDof.push_back(UnderGpu::transition(mb.dof.res, kRtv, kSrv));
                afterDof.push_back(UnderGpu::transition(rt, rtNow, kRtv));
            }
        } else {
            toCopy.push_back(UnderGpu::transition(rt, rtNow, kRtv));
        }
        if (rtHave != kRtv)
            post.push_back(UnderGpu::transition(rt, kRtv, rtHave));
        if (depthToRead)
            post.push_back(UnderGpu::transition(depth, kRead, depthHave));
        if (mvToRead)
            post.push_back(UnderGpu::transition(mv, kRead, mvHave));
    }

    // A set of descriptors per pass (what is not used holds the scene copy, which is valid and never read).
    D3D12_GPU_DESCRIPTOR_HANDLE makeTable(ID3D12Resource* color, ID3D12Resource* focus) {
        const UINT slot = mb.slot++ % kMbRing;
        D3D12_CPU_DESCRIPTOR_HANDLE h = GpuUtil::cpuAt(mb.heap, slot * kMbViews, mb.step);
        UnderGpu::dev->CreateShaderResourceView(color, nullptr, h);
        h.ptr += mb.step;
        if (hasDepth) {
            D3D12_SHADER_RESOURCE_VIEW_DESC dv{};
            dv.Format = depthView;
            dv.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
            dv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
            dv.Texture2D.MipLevels = 1;
            UnderGpu::dev->CreateShaderResourceView(rdepth.res, &dv, h);
        } else {
            UnderGpu::dev->CreateShaderResourceView(mb.copy.res, nullptr, h);
        }
        h.ptr += mb.step;
        UnderGpu::dev->CreateShaderResourceView(mv ? mv : mb.copy.res.get(), nullptr, h);
        h.ptr += mb.step;
        UnderGpu::dev->CreateShaderResourceView(actors ? mb.before.res.get() : mb.copy.res.get(), nullptr, h);
        h.ptr += mb.step;
        UnderGpu::dev->CreateShaderResourceView(actors ? mb.after.res.get() : mb.copy.res.get(), nullptr, h);
        h.ptr += mb.step;
        UnderGpu::dev->CreateShaderResourceView(focus, nullptr, h);
        return GpuUtil::gpuAt(mb.heap, slot * kMbViews, mb.step);
    }

    // The 15 float4 the shader reads (see motionblur.hlsl), for a pass drawing w x h pixels.
    void constants(float (&k)[kMbConstants], float w, float h) const {
        const UnderCamera c = sMo.cur;
        const bool linear = rd.Format == DXGI_FORMAT_R11G11B10_FLOAT || rd.Format == DXGI_FORMAT_R16G16B16A16_FLOAT;
        const D3D12_RESOURCE_DESC mvd = mv ? mv->GetDesc() : dd;
        const float v[kMbConstants] = {
            w, h, UnderGpu::nearPlane.load(), UnderGpu::farPlane.load(),
            c.right[0], c.right[1], c.right[2], c.fov[0],
            c.up[0], c.up[1], c.up[2], c.fov[1],
            c.fwd[0], c.fwd[1], c.fwd[2], static_cast<float>(sFrames++ & 1023),
            c.pos[0], c.pos[1], c.pos[2], 1.0f,
            axis.x, axis.y, axis.z, moving ? turn : 0.f, // the camera's turn over the exposure
            dofOn ? 1.f : 0.f, kMbCocPercent * 0.01f * static_cast<float>(rd.Height) * cfg.aperture, cfg.autoFocus ? 1.f : 0.f, cfg.focusDistance, // the focus distance, and the blur's one distance when there is no depth
            static_cast<float>(std::clamp(sMo.frameDt, 0.001, 0.25)), mb.focusFresh ? 1.f : 0.f, cfg.focusSeconds, 1.0f,
            moving ? dp.x : 0.f, moving ? dp.y : 0.f, moving ? dp.z : 0.f, moving ? 1.f : 0.f, // and its displacement
            static_cast<float>(kMbSamples[level]), 0.f /* the box kernel: a shutter that is open the whole time */, useMv ? 1.f : 0.f, packed() ? 1.f : 0.f /* the copy carries the distances in its alpha */,
            std::max(2.0f, kMbMaxPercent * 0.01f * h), linear ? 1.f : 0.f, kMbKnee, 0.f /* S.w: the vector-debug view is off (the shader still has it for a manual run) */,
            hasDepth ? static_cast<float>(dd.Width) : 0.f, hasDepth ? static_cast<float>(dd.Height) : 0.f, static_cast<float>(mvd.Width), static_cast<float>(mvd.Height),
            1.f, 1.f /* the game's vectors: not inverted, y flipped (uv runs down) */, kMbSpacing[level], cfg.fastGather ? 1.f : 0.f,
            actors ? sFrame.rect[0] : 0.f, actors ? sFrame.rect[1] : 0.f, sFrame.depth, actors ? (sFrame.gbuffer ? 2.f : 1.f) : 0.f,
            actors ? sFrame.rect[2] : 0.f, actors ? sFrame.rect[3] : 0.f, 1.6f /* blocks either side of the player's middle that still count as the player */, linear ? 1.f : 0.f /* B1.w: the scene is linear light (HDR), so the depth of field averages in the same space as the blur */};
        memcpy(k, v, sizeof(v));
    }

    void drawTo(ID3D12PipelineState* state, ID3D12Resource* target, const D3D12_VIEWPORT& vp, const D3D12_RECT& sr, D3D12_GPU_DESCRIPTOR_HANDLE table) {
        UnderGpu::list->SetPipelineState(state);
        UnderGpu::list->SetGraphicsRootDescriptorTable(1, table);
        D3D12_CPU_DESCRIPTOR_HANDLE rtv = UnderGpu::rtvFor(target);
        UnderGpu::list->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
        UnderGpu::list->RSSetViewports(1, &vp);
        UnderGpu::list->RSSetScissorRects(1, &sr);
        UnderGpu::list->DrawInstanced(3, 1, 0, 0);
    }

    void barriers(const std::vector<D3D12_RESOURCE_BARRIER>& list) const { UnderGpu::list->ResourceBarrier(static_cast<UINT>(list.size()), list.data()); }

    // Copy the scene, then (with the depth of field) the focus and the soft picture, then the blur onto the game's target.
    void recordCommands() {
        float k[kMbConstants];
        constants(k, static_cast<float>(rd.Width), static_cast<float>(rd.Height));
        UnderGpu::beginList(pso);
        const int timed = UnderGpu::beginTimed();
        const int tCopy = UnderGpu::beginTimed();
        if (hasDepth)
            UnderGpu::recordDepthCopy(rdepth);
        barriers(pre);
        UnderGpu::list->CopyResource(mb.copy.res, rt);
        barriers(toCopy);
        ID3D12DescriptorHeap* heaps[] = {mb.heap.get()};
        UnderGpu::list->SetDescriptorHeaps(1, heaps);
        UnderGpu::list->SetGraphicsRootSignature(mb.root.get());
        UnderGpu::list->SetGraphicsRoot32BitConstants(0, kMbConstants, k, 0);
        UnderGpu::list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        const D3D12_VIEWPORT full{0, 0, static_cast<float>(rd.Width), static_cast<float>(rd.Height), 0, 1};
        const D3D12_RECT fullRect{0, 0, static_cast<LONG>(rd.Width), static_cast<LONG>(rd.Height)};
        if (packed()) {
            drawTo(psoPack, mb.pack.res, full, fullRect, makeTable(mb.copy.res, focusPrev));
            barriers(afterPack);
        }
        ID3D12Resource* scene = packed() ? mb.pack.res.get() : mb.copy.res.get(); // what the next passes read
        UnderGpu::endTimed(tCopy, UnderGpu::BlurCopy);
        const int tDof = dofOn ? UnderGpu::beginTimed() : -1;
        if (dofOn) {
            drawTo(psoFocus, focusCur, D3D12_VIEWPORT{0, 0, 1, 1, 0, 1}, D3D12_RECT{0, 0, 1, 1}, makeTable(mb.copy.res, focusPrev));
            barriers(afterFocus);
            drawTo(psoDof, dofOnly ? rt : mb.dof.res.get(), full, fullRect, makeTable(scene, focusCur));
            if (!dofOnly)
                barriers(afterDof);
        }
        UnderGpu::endTimed(tDof, UnderGpu::BlurDof);
        const int tDraw = UnderGpu::beginTimed();
        if (!dofOnly)
            drawTo(pso, rt, full, fullRect, makeTable(dofOn ? mb.dof.res.get() : scene, dofOn ? focusCur : focusPrev));
        UnderGpu::endTimed(tDraw, UnderGpu::BlurDraw);
        if (!post.empty())
            barriers(post);
        UnderGpu::endTimed(timed, UnderGpu::Blur);
        if (dofOn) {
            mb.focusAt = 1 - mb.focusAt;
            mb.focusFresh = false;
        }
        UnderGpu::submit(q, run);
    }
};
class MotionBlurPassImpl::MotionBlurPass : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::PostScene; }
    const char* name() const override { return "motion blur"; }
    bool needsProjection() const override { return sSettings.on(); }
    bool needsDepth() const override { return sSettings.on(); }

    bool wanted() override {
        const MbSettings cfg = sSettings.get();
        const bool on = sSettings.on();
        const bool inWorld = UnderGpu::inWorld.load();
        static bool sPrevOn = false, sPrevInWorld = false;
        // The camera pair and the focus history are dropped when the pass is turned on and when a new world starts: the first drawn frame focuses at once
        // instead of easing from the last focus of another world (or, the pass having been off, from a frame that was never drawn). Not every frame.
        const bool fresh = on && (!sPrevOn || (inWorld && !sPrevInWorld));
        sPrevOn = on;
        sPrevInWorld = inWorld;
        if (!on) {
            BlurShare::turning = false; // the passes that follow the blur (nametags, chams) read this: off means off
            sMo.reset(); // a stale pair must not blur the first frame after it is turned on
            return false;
        }
        if (fresh) {
            sMo.reset();
            mb.focusFresh = true;
            sLastDp = Vec3{0, 0, 0}; // the depth gate and the walk's smoothing start clean: no displacement history of another world (or of the pass being off)
            sDpFresh = false;
        }
        sMo.advance(mbExposure(cfg));
        sFrame.snaps = 0;
        // The player's own model is on the screen when the camera is away from the head (third person): playerRect says so and where the box is. (The game's
        // render call for the entity was the first way to know; in third person it is not seen at all, so the camera's place is what is asked.)
        sFrame.actorsWanted = cfg.keepSelf && sMo.moving(static_cast<float>(cfg.shutter * kMbFilmExposure)) && sMo.playerRect(sFrame.rect, sFrame.depth);
        return UnderGpu::inWorld.load();
    }

    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        BS_PROFILE("underui", "motion blur (CPU)");
        blurFrame(q, run, tg);
        sFrame.snaps = 0;
    }

    void report(UnderStats& st) override {
        st.gpuBlurMs = UnderGpu::count[UnderGpu::Blur] ? UnderGpu::sumMs[UnderGpu::Blur] / UnderGpu::count[UnderGpu::Blur] : 0.0;
        st.blurSamples = sDiag.lastSamples;

    }

    void shutdown() override {
        mb.copy.reset();
        mb.before.reset();
        mb.after.reset();
        mb.dof.reset();
        mb.pack.reset();
        mb.heap.reset();
        mb.root.reset();
        for (auto& f : mb.focus)
            f.reset();
        mb.slot = 0;
        mb.pso = mb.psoFocus = mb.psoDof = mb.psoPack = nullptr;
        mb.cachedFormat = DXGI_FORMAT_UNKNOWN;
        mb.cachedDof = mb.cachedDofOnly = mb.cachedPacked = false;
    }

private:
    static void blurFrame(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) {
        UnderGpu::ensure(q);
        if (!mb.root)
            mbInit();
        UnderGpu::harvest();
        BlurFrame fr{q, run, tg};
        BlurShare::turning = false;
        if (!fr.readTargets())
            return;
        fr.measureMotion();
        BlurShare::turning = fr.moving && sMo.cur.valid;
        if (BlurShare::turning) {
            BlurShare::axis[0] = fr.axis.x;
            BlurShare::axis[1] = fr.axis.y;
            BlurShare::axis[2] = fr.axis.z;
            BlurShare::turn = fr.turn;
            BlurShare::dp[0] = fr.dp.x;
            BlurShare::dp[1] = fr.dp.y;
            BlurShare::dp[2] = fr.dp.z;
            for (int i = 0; i < 3; ++i) {
                BlurShare::right[i] = sMo.cur.right[i];
                BlurShare::up[i] = sMo.cur.up[i];
                BlurShare::fwd[i] = sMo.cur.fwd[i];
            }
            BlurShare::fov[0] = sMo.cur.fov[0];
            BlurShare::fov[1] = sMo.cur.fov[1];
        }
        if (!fr.somethingToDo() || !fr.findPipelines())
            return;
        fr.chooseQuality();
        fr.ensureTextures();
        fr.buildBarriers();
        fr.recordCommands();
    }
};

// Just before the game draws its entities: the world without them.
class MotionBlurPassImpl::MbUnderActors : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::UnderActors; }
    const char* name() const override { return "motion blur: the world before the entities"; }
    bool wanted() override { return sFrame.actorsWanted; }
    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        mbSnapshot(q, run, tg, mb.before);
        sFrame.snaps = 1;
    }
};

// Just after the last list of entities: the world with them.
class MotionBlurPassImpl::MbAfterActors : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::AfterActors; }
    const char* name() const override { return "motion blur: the world with the entities"; }
    bool wanted() override { return sFrame.actorsWanted; }
    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        if (sFrame.snaps != 1)
            return;
        mbSnapshot(q, run, tg, mb.after);
        sFrame.snaps = 2;
    }
};


void MotionBlurPasses::install() {
    UnderGpu::addShaders("mblur", &MotionBlurPassImpl::resolveBlur);
    UnderGpu::addShaders("mfocus", &MotionBlurPassImpl::resolveBlur);
    UnderGpu::addShaders("mdof", &MotionBlurPassImpl::resolveBlur);
    UnderGpu::addShaders("mpack", &MotionBlurPassImpl::resolveBlur);
    static MotionBlurPassImpl::MotionBlurPass pass;
    static MotionBlurPassImpl::MbUnderActors before;
    static MotionBlurPassImpl::MbAfterActors after;
    Render::UnderUI::add(&pass); // first: it decides every frame whether the other two are wanted
    Render::UnderUI::add(&before);
    Render::UnderUI::add(&after);
}
