#include "client/features/render/underui/passes/Passes.h"
#include "client/features/render/backend/D3D12Util.h"
#include "client/features/render/underui/UnderGpu.h"
#include "client/features/render/underui/UnderShaders.h"
#include "client/features/render/Renderer.h"
#include "client/core/diagnostics/Profiler.h"

// The ESP parts that belong under the actors (Renderer::underActors: a player someone stands in front of), without the motion blur reading them.
//
// They used to be drawn into the game's frame before its entity lists, so an entity covered them with its own silhouette, but then the blur (which runs over the
// finished scene) smeared them with everything else. Now they are drawn after the blur, and the actors' cover is made again by hand:
//   UnderEntities   a picture of the screen before the game's entity lists (no ESP in it),
//   AfterEntities   a picture of it after them: what differs between the two is where the entities were drawn,
//   PostScene       (after the blur) the blurred scene is copied, the list is drawn over it sharp, and the copy is put back wherever an entity was drawn.
// A frame that has none of these cuts (Vibrant Visuals) or whose snapshots could not be taken leaves the list to Present, drawn over everything with the UI.

namespace UnderEsp { // a name of its own: the passes of a folder are built as one file

constexpr UINT kViews = 3; // before, after, the blurred scene
constexpr int kRing = 16;

struct EspGpu {
    GpuPtr<ID3D12RootSignature> root;
    GpuPtr<ID3D12DescriptorHeap> heap;
    UINT step = 0;
    UINT slot = 0;
    GpuTexture before, after, picture;
    int taken = 0; // this frame: 0 no snapshot, 1 before the entities, 2 and after them
};
EspGpu eg;

UnderShaderDef resolveEspMask(const std::string& name) {
    UnderShaderDef d;
    d.vsSource = d.psSource = UnderShaders::espMaskSource();
    d.vsName = "espmask_vs";
    d.psName = name;
    d.root = eg.root.get();
    return d;
}

void init() {
    D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, kViews, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
    D3D12_ROOT_PARAMETER params[2]{};
    params[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    params[0].Constants = {0, 0, 4};
    params[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    params[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[1].DescriptorTable = {1, &range};
    params[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    D3D12_ROOT_SIGNATURE_DESC rd{2, params, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_NONE};
    eg.root = D3D12Util::createRootSignature(UnderGpu::dev, rd);
    eg.heap = GpuUtil::createDescriptorHeap(UnderGpu::dev, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kViews * kRing, true);
    eg.step = UnderGpu::dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    UnderGpu::startBuilder();
}

// A texture the size and format of the game's target, in the state a shader reads it in.
void ensureTexture(GpuTexture& t, const D3D12_RESOURCE_DESC& rd) {
    const UINT w = static_cast<UINT>(rd.Width);
    if (t.matches(w, rd.Height, rd.Format))
        return;
    UnderGpu::waitIdle();
    t.create(UnderGpu::dev, w, rd.Height, rd.Format, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

// The whole target copied into `tex`, the target back in the state it was in. False when the target cannot be copied (multisampled).
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

bool listWanted() {
    return Render::Renderer::ready() && Render::Renderer::underActorsWanted();
}

// Before the game's entity lists: the world without them.
class EntitiesBefore : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::UnderEntities; }
    const char* name() const override { return "ESP under the actors: the screen before the entities"; }
    bool wanted() override { return listWanted(); }
    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        eg.taken = copyTarget(q, run, tg, eg.before) ? 1 : 0;
    }
};

// After the last of them: the world with them.
class EntitiesAfter : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::AfterEntities; }
    const char* name() const override { return "ESP under the actors: the screen after the entities"; }
    bool wanted() override { return listWanted(); }
    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        if (eg.taken != 1)
            return;
        eg.taken = copyTarget(q, run, tg, eg.after) ? 2 : 0;
    }
};

// Over the blurred scene: the list, then the scene back over the entities.
class EspOverBlur : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::PostScene; }
    const char* name() const override { return "ESP under the actors: the list over the blurred scene"; }
    bool wanted() override { return listWanted(); }

    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        BS_PROFILE("underui", "ESP under the actors (CPU)");
        const bool snapped = eg.taken == 2;
        eg.taken = 0;
        if (!snapped)
            return; // no cut for the entities in this frame: the list is drawn at Present
        UnderGpu::ensure(q);
        if (!eg.root)
            init();
        auto* rt = reinterpret_cast<ID3D12Resource*>(tg.rt);
        const D3D12_RESOURCE_DESC rd = rt->GetDesc();
        const UINT w = static_cast<UINT>(rd.Width);
        if (rd.SampleDesc.Count != 1 || !eg.before.matches(w, rd.Height, rd.Format) || !eg.after.matches(w, rd.Height, rd.Format))
            return; // the target changed between the cuts
        ID3D12PipelineState* pso = UnderGpu::pipeline("espmask", rd.Format, 1, DXGI_FORMAT_UNKNOWN);
        if (!pso)
            return; // still being built: these frames have the list at Present
        ensureTexture(eg.picture, rd);

        // 1. The blurred scene as it is, before any ESP is on it. (copyTarget leaves the target as the game had it)
        if (!copyTarget(q, run, tg, eg.picture))
            return;

        // 2. The list, onto the target in the render target state (what the list's own pass assumes).
        const UINT have = UnderGpu::resourceState(tg.rt, D3D12_RESOURCE_STATE_RENDER_TARGET);
        const bool toTarget = !(have & D3D12_RESOURCE_STATE_RENDER_TARGET);
        if (toTarget) {
            UnderGpu::beginList(nullptr);
            const D3D12_RESOURCE_BARRIER b = UnderGpu::transition(rt, have, D3D12_RESOURCE_STATE_RENDER_TARGET);
            UnderGpu::list->ResourceBarrier(1, &b);
            UnderGpu::submit(q, run);
        }
        const bool drawn = Render::Renderer::underActorsPass(tg.rt, q, run);

        // 3. The blurred scene back wherever an entity was drawn.
        UnderGpu::beginList(pso);
        if (drawn) {
            const UINT slot = eg.slot++ % kRing;
            D3D12_CPU_DESCRIPTOR_HANDLE h = GpuUtil::cpuAt(eg.heap, slot * kViews, eg.step);
            UnderGpu::dev->CreateShaderResourceView(eg.before.res, nullptr, h);
            h.ptr += eg.step;
            UnderGpu::dev->CreateShaderResourceView(eg.after.res, nullptr, h);
            h.ptr += eg.step;
            UnderGpu::dev->CreateShaderResourceView(eg.picture.res, nullptr, h);
            const float k[4] = {static_cast<float>(rd.Width), static_cast<float>(rd.Height), 0.f, 0.f};
            ID3D12DescriptorHeap* heaps[] = {eg.heap.get()};
            UnderGpu::list->SetDescriptorHeaps(1, heaps);
            UnderGpu::list->SetGraphicsRootSignature(eg.root.get());
            UnderGpu::list->SetGraphicsRoot32BitConstants(0, 4, k, 0);
            UnderGpu::list->SetGraphicsRootDescriptorTable(1, GpuUtil::gpuAt(eg.heap, slot * kViews, eg.step));
            UnderGpu::list->SetPipelineState(pso);
            UnderGpu::list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            D3D12_CPU_DESCRIPTOR_HANDLE rtv = UnderGpu::rtvFor(rt);
            UnderGpu::list->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
            const D3D12_VIEWPORT vp{0, 0, static_cast<float>(rd.Width), static_cast<float>(rd.Height), 0, 1};
            const D3D12_RECT sr{0, 0, static_cast<LONG>(rd.Width), static_cast<LONG>(rd.Height)};
            UnderGpu::list->RSSetViewports(1, &vp);
            UnderGpu::list->RSSetScissorRects(1, &sr);
            UnderGpu::list->DrawInstanced(3, 1, 0, 0);
        }
        if (toTarget) {
            const D3D12_RESOURCE_BARRIER b = UnderGpu::transition(rt, D3D12_RESOURCE_STATE_RENDER_TARGET, have);
            UnderGpu::list->ResourceBarrier(1, &b);
        }
        UnderGpu::submit(q, run);
    }

    void dropTargets() override { eg.taken = 0; }

    void shutdown() override {
        eg.before.reset();
        eg.after.reset();
        eg.picture.reset();
        eg.heap.reset();
        eg.root.reset();
        eg.slot = 0;
        eg.taken = 0;
    }
};

} // namespace UnderEsp

void UnderActorsPasses::install() {
    UnderGpu::addShaders("espmask", &UnderEsp::resolveEspMask);
    static UnderEsp::EntitiesBefore before;
    static UnderEsp::EntitiesAfter after;
    static UnderEsp::EspOverBlur over;
    Render::UnderUI::add(&before);
    Render::UnderUI::add(&after);
    Render::UnderUI::add(&over);
}
