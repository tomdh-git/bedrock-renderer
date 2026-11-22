#include "client/features/render/underui/passes/Passes.h"
#include "client/features/render/underui/passes/PlayerRects.h"
#include "client/features/render/backend/D3D12Util.h"
#include "client/features/render/underui/UnderGpu.h"
#include "client/features/render/underui/UnderShaders.h"
#include "client/features/render/underui/feeds/MotionBlurFeed.h"
#include "client/core/diagnostics/Profiler.h"

// The game's nametags with motion blur, without the blur of what is behind them.
//
// The game draws the nametags after the finished scene, in lists of their own, so the scene's blur (which runs over the finished scene, before them) leaves them sharp, and
// moving the blur after them would blur them by the depth of whatever lies behind (a tag over a near block would get that block's parallax). So:
//   PostScene       (after the blur and the chams) a picture of the screen: the world without the nametags,
//   AfterNameTags   (after the last list that draws one) a picture of the screen with them; ntblur.hlsl smears the difference of the two (the tags) along the path the camera's
//                   turn moves a pixel on, with no depth in it, and writes world + smeared tags onto the target.
// Only while the scene's blur found the camera turning (BlurShare), so a still camera costs nothing.

namespace UnderNameTag { // a name of its own: the passes of a folder are built as one file

constexpr UINT kViews = 2; // with the tags, without
constexpr int kRing = 16;
constexpr UINT kMaxTags = 6;
constexpr UINT kConstants = 24 + 4 * kMaxTags + 8; // six float4, the players' rectangles, their distances: inside the 64 a root signature has
constexpr float kLongestBlur = 40.f; // % of the screen's height, as the scene's blur
constexpr float kKnee = 0.4f;        // pixels

struct Gpu {
    GpuPtr<ID3D12RootSignature> root;
    GpuPtr<ID3D12DescriptorHeap> heap;
    UINT step = 0;
    UINT slot = 0;
    uint32_t frame = 0;
    GpuTexture before, after;
    bool taken = false; // this frame: the picture without the tags is in `before`
};
Gpu ng;

UnderShaderDef resolve(const std::string& name) {
    UnderShaderDef d;
    d.vsSource = d.psSource = UnderShaders::nameTagBlurSource();
    d.vsName = "ntblur_vs";
    d.psName = name;
    d.root = ng.root.get();
    return d;
}

void init() {
    D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, kViews, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
    D3D12_ROOT_PARAMETER params[2]{};
    params[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    params[0].Constants = {0, 0, kConstants};
    params[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    params[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[1].DescriptorTable = {1, &range};
    params[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    D3D12_ROOT_SIGNATURE_DESC rd{2, params, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_NONE};
    ng.root = D3D12Util::createRootSignature(UnderGpu::dev, rd);
    ng.heap = GpuUtil::createDescriptorHeap(UnderGpu::dev, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kViews * kRing, true);
    ng.step = UnderGpu::dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    UnderGpu::startBuilder();
}

void ensureTexture(GpuTexture& t, const D3D12_RESOURCE_DESC& rd) {
    const UINT w = static_cast<UINT>(rd.Width);
    if (t.matches(w, rd.Height, rd.Format))
        return;
    UnderGpu::waitIdle();
    t.create(UnderGpu::dev, w, rd.Height, rd.Format, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

// The whole target copied into `tex`, the target back in the state it was in. False when it cannot be copied (multisampled).
bool copyTarget(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg, GpuTexture& tex) {
    UnderGpu::ensure(q);
    auto* rt = reinterpret_cast<ID3D12Resource*>(tg.rt);
    const D3D12_RESOURCE_DESC rd = rt->GetDesc();
    if (rd.SampleDesc.Count != 1)
        return false;
    ensureTexture(tex, rd);
    const UINT have = UnderGpu::resourceState(tg.rt, D3D12_RESOURCE_STATE_RENDER_TARGET);
    const bool toSource = !(have & D3D12_RESOURCE_STATE_COPY_SOURCE);
    D3D12_RESOURCE_BARRIER pre[2], post[2];
    UINT nPre = 0, nPost = 0;
    if (toSource) {
        pre[nPre++] = UnderGpu::transition(rt, have, D3D12_RESOURCE_STATE_COPY_SOURCE);
        post[nPost++] = UnderGpu::transition(rt, D3D12_RESOURCE_STATE_COPY_SOURCE, have);
    }
    pre[nPre++] = UnderGpu::transition(tex.res, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_COPY_DEST);
    post[nPost++] = UnderGpu::transition(tex.res, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    UnderGpu::beginList(nullptr);
    UnderGpu::list->ResourceBarrier(nPre, pre);
    UnderGpu::list->CopyResource(tex.res, rt);
    UnderGpu::list->ResourceBarrier(nPost, post);
    UnderGpu::submit(q, run);
    return true;
}

bool wantedNow() {
    return MotionBlurFeed::nameTagsWanted() && UnderGpu::inWorld.load();
}

class Before : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::PostScene; }
    const char* name() const override { return "nametag blur: the screen without the nametags"; }
    bool wanted() override { return wantedNow(); }
    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        ng.taken = false;
        if (!BlurShare::turning)
            return; // a camera that does not turn blurs nothing: the tags stay as the game drew them
        ng.taken = copyTarget(q, run, tg, ng.before);
    }
};

class Blur : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::AfterNameTags; }
    const char* name() const override { return "nametag blur"; }
    bool wanted() override { return wantedNow(); }

    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        BS_PROFILE("underui", "nametag blur (CPU)");
        if (!ng.taken)
            return;
        ng.taken = false;
        auto* rt = reinterpret_cast<ID3D12Resource*>(tg.rt);
        const D3D12_RESOURCE_DESC rd = rt->GetDesc();
        if (!ng.before.matches(static_cast<UINT>(rd.Width), rd.Height, rd.Format))
            return; // the target changed between the cuts
        if (!ng.root)
            init();
        ID3D12PipelineState* pso = UnderGpu::pipeline("ntblur", rd.Format, 1, DXGI_FORMAT_UNKNOWN);
        if (!pso)
            return; // still being built: these frames keep the tags sharp
        if (!copyTarget(q, run, tg, ng.after))
            return;

        const float W = static_cast<float>(rd.Width), H = static_cast<float>(rd.Height);
        const UINT slot = ng.slot++ % kRing;
        D3D12_CPU_DESCRIPTOR_HANDLE h = GpuUtil::cpuAt(ng.heap, slot * kViews, ng.step);
        UnderGpu::dev->CreateShaderResourceView(ng.after.res, nullptr, h);
        h.ptr += ng.step;
        UnderGpu::dev->CreateShaderResourceView(ng.before.res, nullptr, h);
        // Whose tags these are: the roster's players on this frame's screen (a nametag is above the head, so their rectangles reach up), with how far each is.
        UnderCamera cam = UnderGpu::cameraOf(SetupAndRenderHook::newest());
        if (!cam.valid)
            cam = UnderGpu::camera();
        const std::vector<PlayerRects::One> players = PlayerRects::collect(cam, W, H, 0.6f, 0.1f, 0.6f, 12.f);
        float k[kConstants] = {
            W, H, std::max(2.f, kLongestBlur * 0.01f * H), kKnee,
            BlurShare::right[0], BlurShare::right[1], BlurShare::right[2], BlurShare::fov[0],
            BlurShare::up[0], BlurShare::up[1], BlurShare::up[2], BlurShare::fov[1],
            BlurShare::fwd[0], BlurShare::fwd[1], BlurShare::fwd[2], static_cast<float>(std::min<size_t>(players.size(), kMaxTags)),
            BlurShare::axis[0], BlurShare::axis[1], BlurShare::axis[2], BlurShare::turn,
            BlurShare::dp[0], BlurShare::dp[1], BlurShare::dp[2], static_cast<float>(ng.frame++ & 1023)};
        for (UINT i = 0; i < kMaxTags; ++i) {
            const bool have = i < players.size();
            for (int c = 0; c < 4; ++c)
                k[24 + 4 * i + c] = have ? players[i].rect[c] : 0.f;
            k[24 + 4 * kMaxTags + i] = have ? players[i].dist : 0.f;
        }

        const UINT have = UnderGpu::resourceState(tg.rt, D3D12_RESOURCE_STATE_RENDER_TARGET);
        const bool toTarget = !(have & D3D12_RESOURCE_STATE_RENDER_TARGET);
        UnderGpu::beginList(pso);
        if (toTarget) {
            const D3D12_RESOURCE_BARRIER b = UnderGpu::transition(rt, have, D3D12_RESOURCE_STATE_RENDER_TARGET);
            UnderGpu::list->ResourceBarrier(1, &b);
        }
        ID3D12DescriptorHeap* heaps[] = {ng.heap.get()};
        UnderGpu::list->SetDescriptorHeaps(1, heaps);
        UnderGpu::list->SetGraphicsRootSignature(ng.root.get());
        UnderGpu::list->SetGraphicsRoot32BitConstants(0, kConstants, k, 0);
        UnderGpu::list->SetGraphicsRootDescriptorTable(1, GpuUtil::gpuAt(ng.heap, slot * kViews, ng.step));
        UnderGpu::list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        D3D12_CPU_DESCRIPTOR_HANDLE rtv = UnderGpu::rtvFor(rt);
        UnderGpu::list->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
        const D3D12_VIEWPORT vp{0, 0, W, H, 0, 1};
        const D3D12_RECT sr{0, 0, static_cast<LONG>(rd.Width), static_cast<LONG>(rd.Height)};
        UnderGpu::list->RSSetViewports(1, &vp);
        UnderGpu::list->RSSetScissorRects(1, &sr);
        UnderGpu::list->DrawInstanced(3, 1, 0, 0);
        if (toTarget) {
            const D3D12_RESOURCE_BARRIER b = UnderGpu::transition(rt, D3D12_RESOURCE_STATE_RENDER_TARGET, have);
            UnderGpu::list->ResourceBarrier(1, &b);
        }
        UnderGpu::submit(q, run);
    }

    void shutdown() override {
        ng.before.reset();
        ng.after.reset();
        ng.heap.reset();
        ng.root.reset();
        ng.slot = 0;
        ng.taken = false;
    }
};

} // namespace UnderNameTag

void NameTagBlurPasses::install() {
    UnderGpu::addShaders("ntblur", &UnderNameTag::resolve);
    static UnderNameTag::Before before;
    static UnderNameTag::Blur blur;
    Render::UnderUI::add(&before);
    Render::UnderUI::add(&blur);
}
