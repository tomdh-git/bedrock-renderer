#include "client/features/render/underui/passes/SkyShared.h"
#include "client/features/render/underui/UnderShaders.h"
#include "client/core/diagnostics/Profiler.h"

// The shader that draws the picture and the composite onto the game's target. Both are null while they are still being built.
struct SkyImpl::Pipelines {
    ID3D12PipelineState* picture;
    ID3D12PipelineState* composite;
};
SkyImpl::Pipelines SkyImpl::pipelinesFor(const SkyPick& pick, DXGI_FORMAT pictureFormat, const UnderTarget& tg) {
    const D3D12_RESOURCE_DESC rd = reinterpret_cast<ID3D12Resource*>(tg.rt)->GetDesc();
    const DXGI_FORMAT depth = tg.depth ? UnderGpu::dsvFormatOf(reinterpret_cast<ID3D12Resource*>(tg.depth)->GetDesc().Format) : DXGI_FORMAT_UNKNOWN;
    if (!psoCache.picture || psoCache.pictureKey != pick.key || psoCache.pictureFormat != pictureFormat) {
        psoCache.picture = UnderGpu::pipeline(std::string("sky:") + pick.key, pictureFormat, 1, DXGI_FORMAT_UNKNOWN);
        psoCache.pictureKey = pick.key;
        psoCache.pictureFormat = pictureFormat;
    }
    if (!psoCache.composite || psoCache.compositeFormat != rd.Format || psoCache.compositeSamples != rd.SampleDesc.Count || psoCache.compositeDepth != depth) {
        psoCache.composite = UnderGpu::pipeline("composite", rd.Format, rd.SampleDesc.Count, depth);
        psoCache.compositeFormat = rd.Format;
        psoCache.compositeSamples = rd.SampleDesc.Count;
        psoCache.compositeDepth = depth;
    }
    return {psoCache.picture, psoCache.composite};
}

// Draws the picture into `target` (a texture of ours, brought to render-target state and back) with the shader the list was begun with.
// `b.before` brings the game's target into the state the composite needs, in the same barrier call.
void SkyImpl::drawPicture(ID3D12Resource* target, int rtvIndex, bool clear, const D3D12_VIEWPORT& viewport, const D3D12_RECT& scissor, const UnderGpu::Bound& b, const float* constants) {
    const D3D12_RESOURCE_BARRIER toRt = D3D12Util::transition(target, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);
    std::vector<D3D12_RESOURCE_BARRIER> first = b.before;
    first.push_back(toRt);
    UnderGpu::list->ResourceBarrier(static_cast<UINT>(first.size()), first.data());
    D3D12_CPU_DESCRIPTOR_HANDLE rtv = skyRtv(rtvIndex);
    UnderGpu::list->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
    if (clear) {
        const float black[4] = {0.f, 0.f, 0.f, 1.f};
        UnderGpu::list->ClearRenderTargetView(rtv, black, 0, nullptr);
    }
    UnderGpu::list->RSSetViewports(1, &viewport);
    UnderGpu::list->RSSetScissorRects(1, &scissor);
    UnderGpu::list->SetGraphicsRoot32BitConstants(0, kConstants, constants, 0);
    UnderGpu::list->DrawInstanced(3, 1, 0, 0);
    const D3D12_RESOURCE_BARRIER toSrv = GpuUtil::reversed(toRt);
    UnderGpu::list->ResourceBarrier(1, &toSrv);
}

// The picture onto the game's target: the sky pixels only when depth tested, the whole frame for the menu.
void SkyImpl::compositeOnto(const SkyPick& pick, const UnderGpu::Bound& b, ID3D12PipelineState* composite) {
    float c[kConstants];
    const int timed = UnderGpu::beginTimed();
    UnderGpu::list->SetPipelineState(composite);
    UnderGpu::bindAndSize(b);
    skyConstants(c, pick, static_cast<float>(b.rd.Width), static_cast<float>(b.rd.Height), b.hdr, UnderGpu::camera(), true);
    UnderGpu::list->SetGraphicsRoot32BitConstants(0, kConstants, c, 0);
    UnderGpu::list->DrawInstanced(3, 1, 0, 0);
    if (!b.after.empty())
        UnderGpu::list->ResourceBarrier(static_cast<UINT>(b.after.size()), b.after.data());
    UnderGpu::endTimed(timed, UnderGpu::Composite);
}

// A different shader or size: the game's own picture shows behind the new one until it has faded in.
void SkyImpl::prepareMenuPicture(const SkyPick& pick, const D3D12_RESOURCE_DESC& rd) {
    const bool resized = ensureMenu(std::max<UINT>(64, static_cast<UINT>(rd.Width * pick.scale)), std::max<UINT>(36, static_cast<UINT>(rd.Height * pick.scale)));
    if (resized || bake.key != pick.key) {
        bake = Bake{};
        bake.key = pick.key;
        bake.fadeStart = Platform::Time::millis();
    }
    // The sky's maps are made here, in the menu, where a frame has room for it: joining a world must not stall on allocating them.
    const UINT mapW = envWidth(rd.Height, pick.envScale);
    if (!g.tex[0] || g.skyW != mapW)
        ensureEnv(mapW, mapW / 2);
    bake.phase = 1.f;
}
void SkyImpl::drawMenuPicture(const SkyPick& pick, const UnderGpu::Bound& b) {
    const int timed = UnderGpu::beginTimed();
    sMenuTable = true;
    bindTable();
    float c[kConstants];
    skyConstants(c, pick, static_cast<float>(g.menuW), static_cast<float>(g.menuH), false, UnderGpu::camera(), false); // display colours: the composite converts
    c[3] = 1.0f;
    static uint32_t sMenuFrame = 0;
    c[55] = pick.interleave ? 1.0f + static_cast<float>(sMenuFrame++ & 3u) : 0.0f; // L.w: the phase of the picture drawn this frame
    const bool clear = g.menuClear; // the picture was just made: it is cleared before the first phase is drawn over it
    g.menuClear = false;
    drawPicture(g.menuTex, 3, clear, D3D12_VIEWPORT{0, 0, static_cast<float>(g.menuW), static_cast<float>(g.menuH), 0, 1}, D3D12_RECT{0, 0, static_cast<LONG>(g.menuW), static_cast<LONG>(g.menuH)}, b, c);
    UnderGpu::endTimed(timed, UnderGpu::SkyShader, 1);
}

// A different shader or size: the game's own sky shows until the first map is done.
void SkyImpl::prepareBake(const SkyPick& pick, const D3D12_RESOURCE_DESC& rd) {
    const UINT mapW = envWidth(rd.Height, pick.envScale);
    const bool resized = ensureEnv(mapW, mapW / 2);
    if (resized || bake.key != pick.key) {
        bake = Bake{};
        bake.key = pick.key;
        bake.p = bake.c = bake.w = 0;
    }
    if (bake.band == 0)
        bake.time = skySeconds();
    bake.phase = bake.have ? static_cast<float>(bake.band + 1) / static_cast<float>(bake.bands) : 1.f;
}

// One slice (a band of rows) of the work map, for the instant the whole map is drawn for.
void SkyImpl::drawBakeSlice(const SkyPick& pick, const UnderGpu::Bound& b) {
    const int timed = UnderGpu::beginTimed();
    sMenuTable = false;
    bindTable();
    float c[kConstants];
    skyConstants(c, pick, static_cast<float>(g.skyW), static_cast<float>(g.skyH), false, UnderGpu::camera(), false, true); // display colours: the composite converts
    c[2] = bake.time; // every slice of a map is for the same instant
    c[3] = 1.0f;
    const LONG rowFrom = static_cast<LONG>(g.skyH * static_cast<UINT>(bake.band) / static_cast<UINT>(bake.bands));
    const LONG rowTo = static_cast<LONG>(g.skyH * static_cast<UINT>(bake.band + 1) / static_cast<UINT>(bake.bands));
    drawPicture(g.tex[bake.w], bake.w, false, D3D12_VIEWPORT{0, 0, static_cast<float>(g.skyW), static_cast<float>(g.skyH), 0, 1}, D3D12_RECT{0, rowFrom, static_cast<LONG>(g.skyW), rowTo}, b, c);
    UnderGpu::endTimed(timed, UnderGpu::SkyShader, 1);
}

// The next slice; when the map is complete it becomes the current one.
void SkyImpl::advanceBake() {
    if (++bake.band < bake.bands)
        return;
    bake.band = 0;
    if (!bake.have) {
        bake.have = true;
        bake.p = bake.c = bake.w;
        bake.fadeStart = Platform::Time::millis();
    } else {
        bake.p = bake.c;
        bake.c = bake.w;
    }
    bake.w = (bake.c + 1) % 3; // the pairs in the descriptor heap are (m, m + 1): the next current picture must be the one after this
    bake.bands = std::clamp(static_cast<int>(std::ceil(kCycleSeconds / std::max(sFrameSeconds, 0.001))), 1, 128);
}


bool SkyImpl::injectMenu(ID3D12CommandQueue* q, const SkyPick& pick, const UnderTarget& tg, Render::UnderUI::ExecFn run) {
    const SkyImpl::Pipelines pipes = SkyImpl::pipelinesFor(pick, DXGI_FORMAT_R16G16B16A16_FLOAT, tg);
    if (!pipes.picture || !pipes.composite)
        return false;
    SkyImpl::prepareMenuPicture(pick, reinterpret_cast<ID3D12Resource*>(tg.rt)->GetDesc());
    const UnderGpu::Bound b = UnderGpu::prepareTarget(tg);
    UnderGpu::beginList(pipes.picture);
    SkyImpl::drawMenuPicture(pick, b);
    SkyImpl::compositeOnto(pick, b, pipes.composite);
    UnderGpu::submit(q, run);
    return true;
}

// The sky: a slice of the environment map for the next instant, then the frame's pixels looked up in the finished maps (the previous and the
// current, crossfaded) onto the game's target (only the sky pixels when depth tested).
bool SkyImpl::injectEnv(ID3D12CommandQueue* q, const SkyPick& pick, const UnderTarget& tg, Render::UnderUI::ExecFn run) {
    const SkyImpl::Pipelines pipes = SkyImpl::pipelinesFor(pick, DXGI_FORMAT_R10G10B10A2_UNORM, tg);
    if (!pipes.picture || !pipes.composite)
        return false;
    SkyImpl::prepareBake(pick, reinterpret_cast<ID3D12Resource*>(tg.rt)->GetDesc());
    const bool show = SkyImpl::bake.have;
    UnderGpu::Bound b;
    if (show)
        b = UnderGpu::prepareTarget(tg);
    UnderGpu::beginList(pipes.picture);
    SkyImpl::drawBakeSlice(pick, b);
    if (show)
        SkyImpl::compositeOnto(pick, b, pipes.composite);
    UnderGpu::submit(q, run);
    SkyImpl::advanceBake();
    return true;
}

bool SkyImpl::injectSky(ID3D12CommandQueue* q, const SkyPick& pick, const UnderTarget& tg, Render::UnderUI::ExecFn run) {
    BS_PROFILE("underui", "sky/menu pass (CPU)");
    if (!SkyImpl::g.root)
        SkyImpl::skyInit(q, run);
    UnderGpu::harvest();
    SkyImpl::frameClock();
    return pick.menu ? injectMenu(q, pick, tg, run) : injectEnv(q, pick, tg, run);
}

// The scene's depth, for the fog to read: a descriptor of the ring, set as the fourth root table.
void bindSceneDepth(const UnderGpu::ReadableDepth& depth) {
    static UINT sSlot = 0;
    const UINT slot = SkyImpl::kDepthAt + sSlot++ % SkyImpl::kDepthRing;
    D3D12_SHADER_RESOURCE_VIEW_DESC dv{};
    dv.Format = depth.view;
    dv.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    dv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    dv.Texture2D.MipLevels = 1;
    UnderGpu::dev->CreateShaderResourceView(depth.res, &dv, SkyImpl::srvAt(slot));
    UnderGpu::list->SetGraphicsRootDescriptorTable(3, GpuUtil::gpuAt(SkyImpl::g.srvHeap, slot, SkyImpl::g.srvStep));
}

// The distance fog: one layer of the sky colour over the terrain, more of it the farther the scene is, none over the sky. See sky_fog.hlsl.
void SkyImpl::injectFog(ID3D12CommandQueue* q, const SkyPick& pick, const UnderTarget& tg, const FogParams& fp, Render::UnderUI::ExecFn run) {
    BS_PROFILE("underui", "fog pass (CPU)");
    if (!SkyImpl::g.root || SkyImpl::bake.key.empty() || !SkyImpl::bake.have || SkyImpl::sMenuTable)
        return; // the sky has not been drawn: there is nothing to fade into
    UnderGpu::harvest();
    const D3D12_RESOURCE_DESC rd = reinterpret_cast<ID3D12Resource*>(tg.rt)->GetDesc();
    if (!psoCache.fog || psoCache.fogFormat != rd.Format || psoCache.fogSamples != rd.SampleDesc.Count || psoCache.fogDepth != DXGI_FORMAT_UNKNOWN) {
        psoCache.fog = UnderGpu::pipeline("fog", rd.Format, rd.SampleDesc.Count, DXGI_FORMAT_UNKNOWN);
        psoCache.fogFormat = rd.Format;
        psoCache.fogSamples = rd.SampleDesc.Count;
        psoCache.fogDepth = DXGI_FORMAT_UNKNOWN;
    }
    ID3D12PipelineState* pso = psoCache.fog;
    UnderGpu::ReadableDepth depth;
    if (!pso || rd.SampleDesc.Count != 1 || !UnderGpu::readableDepth(reinterpret_cast<ID3D12Resource*>(tg.depth), depth))
        return;
    UnderGpu::Bound b = UnderGpu::prepareTarget(UnderTarget{tg.rt, 0, 0}); // the target only: the depth is read, not tested

    UnderGpu::beginList(pso);
    const int timed = UnderGpu::beginTimed();
    UnderGpu::recordDepthCopy(depth);
    SkyImpl::bindTable();
    bindSceneDepth(depth);
    if (!b.before.empty())
        UnderGpu::list->ResourceBarrier(static_cast<UINT>(b.before.size()), b.before.data());
    UnderGpu::bindAndSize(b);
    float c[SkyImpl::kConstants] = {};
    SkyImpl::skyConstants(c, pick, static_cast<float>(b.rd.Width), static_cast<float>(b.rd.Height), b.hdr, UnderGpu::camera(), true);
    c[SkyImpl::kFOffset] = fp.nearPlane;
    c[SkyImpl::kFOffset + 1] = fp.farPlane;
    c[SkyImpl::kFOffset + 2] = fp.startBlocks;
    c[SkyImpl::kFOffset + 3] = fp.endBlocks;
    c[SkyImpl::kIOffset] = fp.groundMix;
    c[SkyImpl::kIOffset + 1] = fp.heightBlocks;
    UnderGpu::list->SetGraphicsRoot32BitConstants(0, SkyImpl::kConstants, c, 0);
    UnderGpu::list->DrawInstanced(3, 1, 0, 0);
    if (!b.after.empty())
        UnderGpu::list->ResourceBarrier(static_cast<UINT>(b.after.size()), b.after.data());
    UnderGpu::endTimed(timed, UnderGpu::Fog);
    UnderGpu::submit(q, run);
}

