#include "client/features/render/draw/Blur.h"
#include "client/features/render/post/FullscreenFx.h"

FullscreenFx::Target BlurUtils::g12Stage;
FullscreenFx::Target BlurUtils::g12A;
FullscreenFx::Target BlurUtils::g12B;


UINT BlurUtils::g12W = 0;
UINT BlurUtils::g12H = 0;



void BlurUtils::shutdown() {
    FullscreenFx::freeTarget(g12Stage);
    FullscreenFx::freeTarget(g12A);
    FullscreenFx::freeTarget(g12B);
    g12W = g12H = 0;
}

// The full resolution copy and the two quarter size targets, made again when the size changes.
void BlurUtils::ensureTargets(UINT width, UINT height, DXGI_FORMAT format) {
    if (g12W == width && g12H == height && g12Stage.res)
        return;
    BlurUtils::shutdown();
    const UINT qw = std::max(1u, width / 4), qh = std::max(1u, height / 4);
    FullscreenFx::ensureCopy(g12Stage, width, height, format);
    FullscreenFx::makeTarget(g12A, qw, qh, format);
    FullscreenFx::makeTarget(g12B, qw, qh, format);
    g12W = width;
    g12H = height;
}

// 1) a full resolution copy of the picture
void BlurUtils::copyPicture(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState) {
    OverlayBackend::moveBuffer(cmd, bufferIndex, bufferState, D3D12_RESOURCE_STATE_COPY_SOURCE);
    FullscreenFx::toState(cmd, g12Stage, D3D12_RESOURCE_STATE_COPY_DEST);
    cmd.list->CopyResource(g12Stage.res, OverlayBackend::buffer(bufferIndex));
    FullscreenFx::toState(cmd, g12Stage, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

// 2) the copy into A, a quarter of the size
void BlurUtils::downsample(OverlayBackend::Cmd& cmd, DXGI_FORMAT format, UINT width, UINT height, UINT qw, UINT qh) {
    FullscreenFx::toState(cmd, g12A, D3D12_RESOURCE_STATE_RENDER_TARGET);
    const float down[8] = {1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height), 0, 0, 1.0f, 1.0f, 0, 0};
    FullscreenFx::pass(cmd, FullscreenFx::BlurDown, FullscreenFx::Opaque, g12Stage.res, nullptr, OverlayBackend::rtvCpu(g12A.rtv), format, qw, qh, down);
    FullscreenFx::toState(cmd, g12A, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

// One blur direction from `from` into `to` (both quarter size).
void BlurUtils::blurPass(OverlayBackend::Cmd& cmd, DXGI_FORMAT format, FullscreenFx::Target& from, FullscreenFx::Target& to, UINT qw, UINT qh, const float (&direction)[8]) {
    FullscreenFx::toState(cmd, to, D3D12_RESOURCE_STATE_RENDER_TARGET);
    FullscreenFx::pass(cmd, FullscreenFx::Blur, FullscreenFx::Opaque, from.res, nullptr, OverlayBackend::rtvCpu(to.rtv), format, qw, qh, direction);
    FullscreenFx::toState(cmd, to, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

// 3) separable gaussian H/V x3 at quarter size (creamy enough to smear the UI)
void BlurUtils::smear(OverlayBackend::Cmd& cmd, DXGI_FORMAT format, UINT qw, UINT qh) {
    const float h[8] = {1.0f / static_cast<float>(qw), 1.0f / static_cast<float>(qh), 1.0f, 0.0f, 1.0f, 1.0f, 0, 0};
    const float v[8] = {1.0f / static_cast<float>(qw), 1.0f / static_cast<float>(qh), 0.0f, 1.0f, 1.0f, 1.0f, 0, 0};
    for (int i = 0; i < 3; i++) {
        blurPass(cmd, format, g12A, g12B, qw, qh, h);
        blurPass(cmd, format, g12B, g12A, qw, qh, v);
    }
}


void BlurUtils::paint(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height, float alpha) {
    if (alpha <= 0.01f || !width || !height)
        return;
    alpha = std::min(alpha, 1.f);
    const DXGI_FORMAT format = OverlayBackend::backFormat();
    const UINT qw = std::max(1u, width / 4), qh = std::max(1u, height / 4);
    ensureTargets(width, height, format);
    copyPicture(cmd, bufferIndex, bufferState);
    downsample(cmd, format, width, height, qw, qh);
    smear(cmd, format, qw, qh);
    // 4) crossfade composite over the picture (alpha follows the open animation)
    OverlayBackend::moveBuffer(cmd, bufferIndex, bufferState, D3D12_RESOURCE_STATE_RENDER_TARGET);
    const float comp[8] = {0, 0, 0, 0, alpha, 1.0f, 0, 0};
    FullscreenFx::pass(cmd, FullscreenFx::BlurComp, FullscreenFx::Alpha, g12A.res, nullptr, OverlayBackend::bufferRtv(bufferIndex), format, width, height, comp);
}
