#include "client/features/render/underui/passes/Passes.h"
#include "client/features/render/backend/D3D12Util.h"
#include "client/features/render/Theme.h"
#include "client/features/render/tracker/TrackerState.h"
#include "client/features/render/underui/UnderGpu.h"
#include "client/features/render/underui/UnderShaders.h"
#include "client/features/render/chams/Renderer.h"
#include "client/features/hooks/hooks/render/SetupAndRenderHook.h"
#include "client/features/hooks/hooks/render/ActorRenderDispatcherHook.h"
#include "client/features/render/players/PlayerSeen.h"
#include "client/features/render/underui/feeds/ChamsFeed.h"
#include "client/platform/time/Time.h"

// The players' chams over the finished scene: UnderUI's PostScene layer, added after the motion blur so it is drawn over the blurred picture (the players stay sharp).
// The twin draws of the game's player shaders went into a picture and a depth buffer of ours (ChamsRenderer); chams.hlsl turns them into the model, a fill, an outline and a
// glow, in the client's colours. See the shader for what each is. Where the players are on screen is taken from the frame being drawn (its camera and the positions the
// game drew in that same frame), so a rectangle is never a frame late.

static constexpr UINT kViews = 3;     // the players' picture, their depth, and their stencil (the roster number of the player each pixel belongs to)
static constexpr UINT kSlotViews = 6; // and the small picture, and the glow's two blurs of it (the first pass draws the small one and reads only the first three: each view has a table of its own)
static constexpr UINT kDivide = 4;    // the small picture is a quarter of the screen each way
static constexpr int kRing = 16;      // descriptor sets: a few frames in flight
static constexpr UINT kMaxPlayers = 5;
static constexpr UINT kConstants = 40 + 4 * kMaxPlayers; // 40 + 20: inside the 64 a root signature has (the descriptor table takes one)

struct Cfg {
    bool actor = true, fill = false, outline = true, glow = false;
    uint32_t primary = 0xFFFFFFFF, secondary = 0xFFFFFFFF; // the client's colours, ABGR
    float fillOpacity = 0.45f, outlineWidth = 1.5f, glowRadius = 12.f;
};

struct ChamsGpu {
    GpuPtr<ID3D12RootSignature> root;
    GpuPtr<ID3D12DescriptorHeap> heap;
    UINT step = 0;
    UINT slot = 0;
    uint32_t frame = 0;
    GpuTexture low;   // what the first shader writes: how much of a 4x4 block is a player, and whether it holds a step of depth
    GpuTexture blurA, blurB; // the glow: that coverage blurred along x, then along y
};

static ChamsGpu cg;
static Render::PassSettings<Cfg> sSettings;

// Chams::onFrame pushes the module's settings here every frame: the pass draws with what it was last given.
void ChamsFeed::publish(bool on, bool actor, bool fill, bool outline, bool glow, float fillOpacity, float outlineWidth, float glowRadius) {
    sSettings.publish(on, {actor, fill, outline, glow, Render::Theme::gradA, Render::Theme::gradB, fillOpacity, outlineWidth, glowRadius});
}

static UnderShaderDef resolveChams(const std::string& name) {
    UnderShaderDef d;
    d.vsSource = d.psSource = UnderShaders::chamsSource();
    d.vsName = "chams_vs";
    // The same file with one name defined for each of the small pictures' shaders; the composite has none.
    const char* define = name == "chams:mask" ? "MASK" : name == "chams:blurh" ? "BLURH" : name == "chams:blurv" ? "BLURV" : nullptr;
    d.psName = define ? "chams_" + std::string(define) : name;
    if (define)
        d.psSource = "#define " + std::string(define) + " 1\n" + d.psSource;
    d.root = cg.root.get();
    d.blend = define == nullptr; // the composite is source alpha over the scene; the small pictures are overwritten
    return d;
}

static void init() {
    D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, kViews, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
    D3D12_DESCRIPTOR_RANGE maskRange{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 3, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
    D3D12_DESCRIPTOR_RANGE glowRange{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 4, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
    D3D12_ROOT_PARAMETER params[4]{};
    params[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    params[0].Constants = {0, 0, kConstants};
    params[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    params[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[1].DescriptorTable = {1, &range};
    params[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    params[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[2].DescriptorTable = {1, &maskRange};
    params[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    params[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[3].DescriptorTable = {1, &glowRange};
    params[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    D3D12_STATIC_SAMPLER_DESC linear{};
    linear.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    linear.AddressU = linear.AddressV = linear.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    linear.MaxLOD = D3D12_FLOAT32_MAX;
    linear.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    D3D12_ROOT_SIGNATURE_DESC rd{4, params, 1, &linear, D3D12_ROOT_SIGNATURE_FLAG_NONE};
    cg.root = D3D12Util::createRootSignature(UnderGpu::dev, rd);
    cg.heap = GpuUtil::createDescriptorHeap(UnderGpu::dev, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kSlotViews * kRing, true);
    cg.step = UnderGpu::dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    UnderGpu::startBuilder();
}

static UINT stateOf(uintptr_t res) {
    const auto it = UnderGpu::state.find(res);
    return it == UnderGpu::state.end() ? static_cast<UINT>(D3D12_RESOURCE_STATE_RENDER_TARGET) : it->second;
}

// A player's box on the screen of the frame (pixels, padded): all of the screen when part of the box is behind the camera. False when it is off screen.
static bool boxRect(const UnderCamera& c, const Vec3& lo, const Vec3& hi, float w, float h, float rect[4]) {
    float mnU = 1e9f, mnV = 1e9f, mxU = -1e9f, mxV = -1e9f;
    for (int i = 0; i < 8; ++i) {
        const float rx = ((i & 1) ? hi.x : lo.x) - c.pos[0], ry = ((i & 2) ? hi.y : lo.y) - c.pos[1], rz = ((i & 4) ? hi.z : lo.z) - c.pos[2];
        const float zz = c.fwd[0] * rx + c.fwd[1] * ry + c.fwd[2] * rz;
        if (zz < 0.1f) {
            rect[0] = rect[1] = 0.f;
            rect[2] = w;
            rect[3] = h;
            return true;
        }
        const float nx = (c.right[0] * rx + c.right[1] * ry + c.right[2] * rz) / zz * c.fov[0];
        const float ny = (c.up[0] * rx + c.up[1] * ry + c.up[2] * rz) / zz * c.fov[1];
        const float u = nx * 0.5f + 0.5f, v = 0.5f - ny * 0.5f;
        mnU = std::min(mnU, u);
        mxU = std::max(mxU, u);
        mnV = std::min(mnV, v);
        mxV = std::max(mxV, v);
    }
    const float padU = (mxU - mnU) * 0.12f + 6.f / w, padV = (mxV - mnV) * 0.08f + 6.f / h;
    rect[0] = std::clamp((mnU - padU) * w, 0.f, w);
    rect[1] = std::clamp((mnV - padV) * h, 0.f, h);
    rect[2] = std::clamp((mxU + padU) * w, 0.f, w);
    rect[3] = std::clamp((mxV + padV) * h, 0.f, h);
    return rect[2] > rect[0] && rect[3] > rect[1];
}

class ChamsPass : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::PostScene; }
    const char* name() const override { return "chams"; }
    bool needsProjection() const override { return sSettings.on(); } // the distance of a player, for how wide the outline is

    void poll() override { warmPipelines(); }

    // The pipelines are asked for as soon as the module is on and the device exists (the menu already has it), not at the first frame in a world: building one takes a second or
    // more, and that second was the wait for the chams after a join. The target's format is not known until a frame is recorded, so each format it can be is asked for.
    void warmPipelines() {
        static bool sWarmed = false;
        if (sWarmed || !sSettings.on() || !UnderGpu::dev)
            return;
        sWarmed = true;
        if (!cg.root)
            init();
        for (DXGI_FORMAT format : {DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R10G10B10A2_UNORM, DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_B8G8R8A8_UNORM})
            UnderGpu::warm("chams", format, 1, DXGI_FORMAT_UNKNOWN);
        UnderGpu::warm("chams:mask", DXGI_FORMAT_R8G8_UNORM, 1, DXGI_FORMAT_UNKNOWN);
        UnderGpu::warm("chams:blurh", DXGI_FORMAT_R16_UNORM, 1, DXGI_FORMAT_UNKNOWN);
        UnderGpu::warm("chams:blurv", DXGI_FORMAT_R16_UNORM, 1, DXGI_FORMAT_UNKNOWN);
    }

    bool wanted() override { return sSettings.on() && UnderGpu::inWorld.load(); }

    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        // Whether a player was drawn into the picture of this frame: the frames are recorded ahead of the one executing, so it is by the frame's target, not one flag.
        if (!ChamsRenderer::takeDrawn(tg.rt, TrackerState::isBackBuffer(tg.rt))) {
            return;
        }
        ID3D12Resource* color = ChamsRenderer::colorTarget();
        ID3D12Resource* depth = ChamsRenderer::depthTarget();
        if (!color || !depth) {
            return;
        }
        UnderGpu::ensure(q);
        if (!cg.root)
            init();
        auto* rt = reinterpret_cast<ID3D12Resource*>(tg.rt);
        const D3D12_RESOURCE_DESC rd = rt->GetDesc(), cd = color->GetDesc();
        if (rd.Width != cd.Width || rd.Height != cd.Height || rd.SampleDesc.Count != 1) {
            return;
        }
        ID3D12PipelineState* pso = UnderGpu::pipeline("chams", rd.Format, 1, DXGI_FORMAT_UNKNOWN);
        ID3D12PipelineState* maskPso = UnderGpu::pipeline("chams:mask", DXGI_FORMAT_R8G8_UNORM, 1, DXGI_FORMAT_UNKNOWN);
        ID3D12PipelineState* blurHPso = UnderGpu::pipeline("chams:blurh", DXGI_FORMAT_R16_UNORM, 1, DXGI_FORMAT_UNKNOWN);
        ID3D12PipelineState* blurVPso = UnderGpu::pipeline("chams:blurv", DXGI_FORMAT_R16_UNORM, 1, DXGI_FORMAT_UNKNOWN);
        if (!pso || !maskPso || !blurHPso || !blurVPso) {
            return; // still being built: no chams for these frames
        }
        const Cfg cfg = sSettings.get();
        const float W = static_cast<float>(rd.Width), H = static_cast<float>(rd.Height);

        // The real players of this frame, where the game drew them, on the screen of this frame's camera.
        // The camera and the bodies of the frame whose picture this is: the game draws a frame presentDelay frames after it set it up, so it is the presented transform (the same
        // one ESP projects with), not the newest. The newest is a few frames ahead: turning the camera moved the rectangles off the players, which cut parts of them away.
        SetupAndRenderHook::Transform t = SetupAndRenderHook::presented();
        if (t.seq == 0)
            t = SetupAndRenderHook::newest();
        UnderCamera cam = UnderGpu::cameraOf(t);
        if (!cam.valid)
            cam = UnderGpu::camera();
        float rects[kMaxPlayers][4] = {};  // on the screen: where the work is done (the stencil decides whose a pixel is)
        uint32_t slotBits[3] = {};         // the roster numbers of the players ESP draws (bit n-1 of 96): a pixel whose stencil is any other number is nobody's and is not drawn
        float scales[kMaxPlayers] = {};    // what the widths are multiplied by for each of them (the same rule as the ESP lines: a player is 1.8 blocks tall)
        const float focal = cam.fov[1] * 0.5f * H;
        UINT count = 0;
        if (t.bodies) {
            for (const PlayerSeen& seen : *static_cast<const std::vector<PlayerSeen>*>(t.bodies.get())) {
                if (seen.local) { // the player's own model is on the screen only away from the head (third person)
                    const float ex = cam.pos[0] - cam.player[0], ey = cam.pos[1] - cam.player[1], ez = cam.pos[2] - cam.player[2];
                    if (ex * ex + ey * ey + ez * ez < 1.5f * 1.5f)
                        continue;
                }
                if (seen.slot >= 1 && seen.slot <= PlayerSeen::kSlots)
                    slotBits[(seen.slot - 1) / 32] |= 1u << ((seen.slot - 1) % 32);
                Vec3 lo, hi;
                PlayerSeen::corners(seen, lo, hi);
                float r[4];
                if (!boxRect(cam, lo, hi, W, H, r))
                    continue;
                // The rectangle only bounds the work (the scissors, and the outline and glow outside the model): which pixel is whose is the stencil's, exactly. It has to hold
                // the arms, a held item, a cape and the outline, so it is generous.
                const float padX = (r[2] - r[0]) * 0.5f + 10.f, padY = (r[3] - r[1]) * 0.2f + 10.f;
                r[0] = std::max(0.f, r[0] - padX);
                r[1] = std::max(0.f, r[1] - padY);
                r[2] = std::min(W, r[2] + padX);
                r[3] = std::min(H, r[3] + padY);
                // More players than the constants have room for: the rest are joined into the last rectangle (a coarser filter for them, never a missing player).
                const float depth = cam.fwd[0] * (seen.feet.x - cam.pos[0]) + cam.fwd[1] * (seen.feet.y - cam.pos[1]) + cam.fwd[2] * (seen.feet.z - cam.pos[2]);
                const float scale = std::clamp(1.8f * focal / std::max(depth, 0.5f) / 300.f, 1.f, 1.5f);
                if (count < kMaxPlayers) {
                    scales[count] = scale;
                    memcpy(rects[count++], r, sizeof(r));
                } else {
                    scales[kMaxPlayers - 1] = std::max(scales[kMaxPlayers - 1], scale);
                    float* last = rects[kMaxPlayers - 1];
                    last[0] = std::min(last[0], r[0]);
                    last[1] = std::min(last[1], r[1]);
                    last[2] = std::max(last[2], r[2]);
                    last[3] = std::max(last[3], r[3]);
                }
            }
        }
        if (count == 0) {
            ActorRenderDispatcherHook::chamsPassEmpty.fetch_add(1, std::memory_order_relaxed);
            return;
        }
        const float glowWidth = cfg.glow ? cfg.glowRadius : 0.f; // the glow is the outline's silhouette search, fading outward over this many pixels (at scale 1)
        const float reach = std::clamp(std::max(cfg.outline ? cfg.outlineWidth : 0.f, glowWidth) * 1.5f + 2.f, 0.f, 96.f);
        // One draw per group of players whose rectangles touch, not one over the union: two players far apart on the screen do not make the pass cover what is between them.
        std::vector<D3D12_RECT> scissors;
        for (UINT i = 0; i < count; ++i)
            scissors.push_back({static_cast<LONG>(std::max(0.f, rects[i][0] - reach)), static_cast<LONG>(std::max(0.f, rects[i][1] - reach)),
                                static_cast<LONG>(std::min(W, rects[i][2] + reach)), static_cast<LONG>(std::min(H, rects[i][3] + reach))});
        for (bool merged = true; merged;) {
            merged = false;
            for (size_t i = 0; i < scissors.size() && !merged; ++i)
                for (size_t j = i + 1; j < scissors.size() && !merged; ++j) {
                    D3D12_RECT &a = scissors[i], &b = scissors[j];
                    if (a.left < b.right && b.left < a.right && a.top < b.bottom && b.top < a.bottom) {
                        a = {std::min(a.left, b.left), std::min(a.top, b.top), std::max(a.right, b.right), std::max(a.bottom, b.bottom)};
                        scissors.erase(scissors.begin() + j);
                        merged = true;
                    }
                }
        }

        {
            static double sArea = 0;
            static uint32_t sFrames = 0, sPlayers = 0;
            static ULONGLONG sNext = 0;
            for (const D3D12_RECT& sc : scissors)
                sArea += static_cast<double>(sc.right - sc.left) * (sc.bottom - sc.top);
            sPlayers += count;
            ++sFrames;
            const ULONGLONG now = Platform::Time::millis();
            if (now >= sNext) {
                if (sNext != 0)
                {
                    const float ex = cam.pos[0] - cam.player[0], ey = cam.pos[1] - cam.player[1], ez = cam.pos[2] - cam.player[2];
                    Logger::info("[chams] pass: {} frames in 5 s, {} players a frame, {:.2f} megapixels of scissor a frame (outline {}, glow {}, reach {:.0f} px); camera {:.1f} blocks from the player, fov {:.2f}x{:.2f}, rect0 [{:.0f} {:.0f} {:.0f} {:.0f}]",
                                 sFrames, sPlayers / std::max(1u, sFrames), sArea / std::max(1u, sFrames) / 1e6, cfg.outline, cfg.glow, reach, std::sqrt(ex * ex + ey * ey + ez * ez), cam.fov[0], cam.fov[1],
                                 rects[0][0], rects[0][1], rects[0][2], rects[0][3]);
                }
                sNext = now + 5000;
                sArea = 0;
                sFrames = sPlayers = 0;
            }
        }

        // The small picture the first shader writes (a quarter of the screen each way).
        const UINT lowW = (static_cast<UINT>(rd.Width) + kDivide - 1) / kDivide, lowH = (rd.Height + kDivide - 1) / kDivide;
        if (!cg.low.matches(lowW, lowH, DXGI_FORMAT_R8G8_UNORM)) {
            UnderGpu::waitIdle();
            const D3D12_CLEAR_VALUE clear{DXGI_FORMAT_R8G8_UNORM, {0.f, 0.f, 0.f, 0.f}};
            cg.low.create(UnderGpu::dev, lowW, lowH, DXGI_FORMAT_R8G8_UNORM, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, &clear);
        }
        if (!cg.blurA.matches(lowW, lowH, DXGI_FORMAT_R16_UNORM)) {
            UnderGpu::waitIdle();
            const D3D12_CLEAR_VALUE clear{DXGI_FORMAT_R16_UNORM, {0.f, 0.f, 0.f, 0.f}};
            cg.blurA.create(UnderGpu::dev, lowW, lowH, DXGI_FORMAT_R16_UNORM, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, &clear);
            cg.blurB.create(UnderGpu::dev, lowW, lowH, DXGI_FORMAT_R16_UNORM, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, &clear);
        }

        // The descriptors: the players' picture, their depth read as R24, their stencil, and the small picture.
        const UINT slot = cg.slot++ % kRing;
        D3D12_CPU_DESCRIPTOR_HANDLE h = GpuUtil::cpuAt(cg.heap, slot * kSlotViews, cg.step);
        UnderGpu::dev->CreateShaderResourceView(color, nullptr, h);
        h.ptr += cg.step;
        D3D12_SHADER_RESOURCE_VIEW_DESC dv{};
        dv.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
        dv.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        dv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        dv.Texture2D.MipLevels = 1;
        UnderGpu::dev->CreateShaderResourceView(depth, &dv, h);
        h.ptr += cg.step;
        dv.Format = DXGI_FORMAT_X24_TYPELESS_G8_UINT; // the stencil plane: the roster number the twin draws wrote
        dv.Texture2D.PlaneSlice = 1;
        UnderGpu::dev->CreateShaderResourceView(depth, &dv, h);
        h.ptr += cg.step;
        UnderGpu::dev->CreateShaderResourceView(cg.low.res, nullptr, h);
        h.ptr += cg.step;
        UnderGpu::dev->CreateShaderResourceView(cg.blurA.res, nullptr, h);
        h.ptr += cg.step;
        UnderGpu::dev->CreateShaderResourceView(cg.blurB.res, nullptr, h);

        const UINT rtHave = stateOf(tg.rt);
        constexpr UINT kRtv = D3D12_RESOURCE_STATE_RENDER_TARGET, kSrv = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
        std::vector<D3D12_RESOURCE_BARRIER> pre, post;
        if (rtHave != kRtv) {
            pre.push_back(UnderGpu::transition(rt, rtHave, kRtv));
            post.push_back(UnderGpu::transition(rt, kRtv, rtHave));
        }
        pre.push_back(UnderGpu::transition(color, kRtv, kSrv));
        pre.push_back(UnderGpu::transition(depth, D3D12_RESOURCE_STATE_DEPTH_WRITE, kSrv));
        post.push_back(UnderGpu::transition(color, kSrv, kRtv));
        post.push_back(UnderGpu::transition(depth, kSrv, D3D12_RESOURCE_STATE_DEPTH_WRITE));

        auto channel = [](uint32_t c, int shift) { return static_cast<float>((c >> shift) & 255) / 255.f; };
        // The glow's width follows the nearest player's scale, the same for all of them (one blur of the whole small picture): sigma is in blocks of it, and the blur reaches three sigmas.
        const float nearestScale = *std::max_element(scales, scales + count);
        const float blurSigma = std::max(glowWidth * nearestScale / static_cast<float>(kDivide) * 0.45f, 0.35f);
        const LONG blurReach = static_cast<LONG>(std::min(std::ceil(blurSigma * 3.f), 24.f)) + 1;
        float k[kConstants] = {
            W, H, UnderGpu::nearPlane.load(), UnderGpu::farPlane.load(),
            cam.fov[1] * 0.5f * H, ChamsRenderer::reversedDepth() ? 1.f : 0.f, static_cast<float>(cg.frame++ & 1023), reach,
            channel(cfg.primary, 0), channel(cfg.primary, 8), channel(cfg.primary, 16), cfg.fill ? cfg.fillOpacity : 0.f,
            cfg.outline ? cfg.outlineWidth : 0.f, glowWidth, cfg.actor ? 1.f : 0.f, 0.f, // [15]: the slots 65..96, below
            channel(cfg.secondary, 0), channel(cfg.secondary, 8), channel(cfg.secondary, 16), static_cast<float>(Platform::Time::seconds()),
            cam.right[0], cam.right[1], cam.right[2], cam.fov[0],
            cam.up[0], cam.up[1], cam.up[2], cam.fov[1],
            cam.fwd[0], cam.fwd[1], cam.fwd[2], static_cast<float>(count),
            scales[0], scales[1], scales[2], scales[3],
            scales[4], blurSigma, 0.f, 0.f}; // [38], [39]: the slots 1..64, below
        // Which roster numbers are real players this frame (the ones ESP draws), as bits: the raw bits go into float slots of the constants.
        memcpy(&k[38], &slotBits[0], sizeof(uint32_t));
        memcpy(&k[39], &slotBits[1], sizeof(uint32_t));
        memcpy(&k[15], &slotBits[2], sizeof(uint32_t));
        for (UINT i = 0; i < count; ++i)
            memcpy(&k[40 + 4 * i], rects[i], sizeof(rects[i])); // where the work is

        UnderGpu::beginList(pso);
        UnderGpu::list->ResourceBarrier(static_cast<UINT>(pre.size()), pre.data());
        ID3D12DescriptorHeap* heaps[] = {cg.heap.get()};
        UnderGpu::list->SetDescriptorHeaps(1, heaps);
        UnderGpu::list->SetGraphicsRootSignature(cg.root.get());
        UnderGpu::list->SetGraphicsRoot32BitConstants(0, kConstants, k, 0);
        UnderGpu::list->SetGraphicsRootDescriptorTable(1, GpuUtil::gpuAt(cg.heap, slot * kSlotViews, cg.step));
        UnderGpu::list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // The small picture first: the depth read once, at a quarter of the resolution, inside the scissors (cleared, so what is outside them reads as no player).
        const D3D12_RESOURCE_BARRIER lowToRt = UnderGpu::transition(cg.low.res, kSrv, kRtv);
        UnderGpu::list->ResourceBarrier(1, &lowToRt);
        UnderGpu::list->SetPipelineState(maskPso);
        const D3D12_CPU_DESCRIPTOR_HANDLE lowRtv = UnderGpu::rtvFor(cg.low.res);
        UnderGpu::list->OMSetRenderTargets(1, &lowRtv, FALSE, nullptr);
        const float none[4] = {0.f, 0.f, 0.f, 0.f};
        UnderGpu::list->ClearRenderTargetView(lowRtv, none, 0, nullptr);
        const D3D12_VIEWPORT lowVp{0, 0, static_cast<float>(lowW), static_cast<float>(lowH), 0, 1};
        UnderGpu::list->RSSetViewports(1, &lowVp);
        for (const D3D12_RECT& scissor : scissors) {
            const D3D12_RECT lowScissor{scissor.left / static_cast<LONG>(kDivide), scissor.top / static_cast<LONG>(kDivide), (scissor.right + static_cast<LONG>(kDivide) - 1) / static_cast<LONG>(kDivide), (scissor.bottom + static_cast<LONG>(kDivide) - 1) / static_cast<LONG>(kDivide)};
            UnderGpu::list->RSSetScissorRects(1, &lowScissor);
            UnderGpu::list->DrawInstanced(3, 1, 0, 0);
        }
        const D3D12_RESOURCE_BARRIER lowToSrv = UnderGpu::transition(cg.low.res, kRtv, kSrv);
        UnderGpu::list->ResourceBarrier(1, &lowToSrv);

        // The glow: the coverage blurred along x into A, then along y into B (cleared, so what the scissors leave out is no glow). Each draws over the scissors grown by the blur's reach.
        if (cfg.glow) {
            const auto blur = [&](GpuTexture& target, ID3D12PipelineState* blurPso, UINT inputView) {
                const D3D12_RESOURCE_BARRIER toRt = UnderGpu::transition(target.res, kSrv, kRtv);
                UnderGpu::list->ResourceBarrier(1, &toRt);
                UnderGpu::list->SetPipelineState(blurPso);
                UnderGpu::list->SetGraphicsRootDescriptorTable(2, GpuUtil::gpuAt(cg.heap, slot * kSlotViews + inputView, cg.step));
                const D3D12_CPU_DESCRIPTOR_HANDLE targetRtv = UnderGpu::rtvFor(target.res);
                UnderGpu::list->OMSetRenderTargets(1, &targetRtv, FALSE, nullptr);
                UnderGpu::list->ClearRenderTargetView(targetRtv, none, 0, nullptr);
                for (const D3D12_RECT& scissor : scissors) {
                    const D3D12_RECT grown{std::max<LONG>(0, scissor.left / static_cast<LONG>(kDivide) - blurReach), std::max<LONG>(0, scissor.top / static_cast<LONG>(kDivide) - blurReach),
                                           std::min<LONG>(lowW, (scissor.right + static_cast<LONG>(kDivide) - 1) / static_cast<LONG>(kDivide) + blurReach),
                                           std::min<LONG>(lowH, (scissor.bottom + static_cast<LONG>(kDivide) - 1) / static_cast<LONG>(kDivide) + blurReach)};
                    UnderGpu::list->RSSetScissorRects(1, &grown);
                    UnderGpu::list->DrawInstanced(3, 1, 0, 0);
                }
                const D3D12_RESOURCE_BARRIER toSrv = UnderGpu::transition(target.res, kRtv, kSrv);
                UnderGpu::list->ResourceBarrier(1, &toSrv);
            };
            blur(cg.blurA, blurHPso, 3);
            blur(cg.blurB, blurVPso, 4);
        }

        // Then the pass itself, over the game's target.
        UnderGpu::list->SetPipelineState(pso);
        UnderGpu::list->SetGraphicsRootDescriptorTable(2, GpuUtil::gpuAt(cg.heap, slot * kSlotViews + 3, cg.step));
        UnderGpu::list->SetGraphicsRootDescriptorTable(3, GpuUtil::gpuAt(cg.heap, slot * kSlotViews + 5, cg.step));
        D3D12_CPU_DESCRIPTOR_HANDLE rtv = UnderGpu::rtvFor(rt);
        UnderGpu::list->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
        const D3D12_VIEWPORT vp{0, 0, W, H, 0, 1};
        UnderGpu::list->RSSetViewports(1, &vp);
        for (const D3D12_RECT& scissor : scissors) {
            UnderGpu::list->RSSetScissorRects(1, &scissor);
            UnderGpu::list->DrawInstanced(3, 1, 0, 0);
        }
        UnderGpu::list->ResourceBarrier(static_cast<UINT>(post.size()), post.data());
        UnderGpu::submit(q, run);
    }

    void shutdown() override {
        cg.heap.reset();
        cg.root.reset();
        cg.low.reset();
        cg.blurA.reset();
        cg.blurB.reset();
        cg.slot = 0;
    }
};

void ChamsPasses::install() {
    UnderGpu::addShaders("chams", &resolveChams);
    static ChamsPass pass;
    Render::UnderUI::add(&pass);
}
