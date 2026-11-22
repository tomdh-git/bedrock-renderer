#pragma once
#include "client/features/render/backend/OverlayBackend.h"
#include "client/features/render/post/FullscreenFx.h"

// Fullscreen gaussian backdrop blur (only while the Click GUI is open), recorded in the caller's OverlayBackend list onto swapchain buffer `bufferIndex`, which is in
// `bufferState` (moved as needed):
struct BlurUtils {
    // alpha 0..1 crossfades sharp -> blurred.
    static void paint(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height, float alpha);
    static void shutdown(); // the targets, before the device goes

private:
    static FullscreenFx::Target g12Stage;
    static FullscreenFx::Target g12A;
    static FullscreenFx::Target g12B;
    static UINT g12W;
    static UINT g12H;
    static void ensureTargets(UINT width, UINT height, DXGI_FORMAT format);
    static void copyPicture(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState);
    static void downsample(OverlayBackend::Cmd& cmd, DXGI_FORMAT format, UINT width, UINT height, UINT qw, UINT qh);
    static void blurPass(OverlayBackend::Cmd& cmd, DXGI_FORMAT format, FullscreenFx::Target& from, FullscreenFx::Target& to, UINT qw, UINT qh, const float (&direction)[8]);
    static void smear(OverlayBackend::Cmd& cmd, DXGI_FORMAT format, UINT qw, UINT qh);
};
