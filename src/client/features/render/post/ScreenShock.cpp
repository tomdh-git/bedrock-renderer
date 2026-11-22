#include "client/features/render/post/ScreenShock.h"

void ScreenShock::end() {
    sActive = false;
    sSnapValid = false;
    sWave = Wave{};
    FullscreenFx::freeTarget(sSnap);
    FullscreenFx::freeTarget(sCover);
}

void ScreenShock::setCoverage(const uint8_t* px, int w, int h) {
    if (!px) {
        sFull = true;
        return;
    }
    sFull = false;
    sCovW = w;
    sCovH = h;
    sCov.assign(px, px + static_cast<size_t>(w) * static_cast<size_t>(h));
    sDirty = true;
}

void ScreenShock::capture(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height) {
    if (!sActive || !width || !height)
        return;
    if (sSnap.res && (sSnap.w != width || sSnap.h != height))
        sSnapValid = false;
    if (sSnapValid)
        return;
    const DXGI_FORMAT format = OverlayBackend::backFormat();
    FullscreenFx::ensureCopy(sSnap, width, height, format);
    OverlayBackend::moveBuffer(cmd, bufferIndex, bufferState, D3D12_RESOURCE_STATE_COPY_SOURCE);
    FullscreenFx::toState(cmd, sSnap, D3D12_RESOURCE_STATE_COPY_DEST);
    D3D12_TEXTURE_COPY_LOCATION dst{}, src{};
    dst.pResource = sSnap.res;
    dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    src.pResource = OverlayBackend::buffer(bufferIndex);
    src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    cmd.list->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
    FullscreenFx::toState(cmd, sSnap, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    OverlayBackend::moveBuffer(cmd, bufferIndex, bufferState, D3D12_RESOURCE_STATE_RENDER_TARGET);
    sSnapValid = true;
}

void ScreenShock::composite(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height) {
    if (!sActive || !sSnapValid || !width || !height)
        return;
    if (!sFull) {
        if (!sCover.res || sCover.w != static_cast<UINT>(sCovW) || sCover.h != static_cast<UINT>(sCovH)) {
            FullscreenFx::freeTarget(sCover);
            FullscreenFx::makeTarget(sCover, static_cast<UINT>(sCovW), static_cast<UINT>(sCovH), DXGI_FORMAT_R8_UNORM);
            sDirty = true;
        }
        if (sDirty) {
            const UINT pitch = (static_cast<UINT>(sCovW) + 255u) & ~255u;
            std::vector<uint8_t> rows(static_cast<size_t>(pitch) * static_cast<size_t>(sCovH));
            for (int y = 0; y < sCovH; ++y)
                std::memcpy(&rows[static_cast<size_t>(y) * pitch], &sCov[static_cast<size_t>(y) * static_cast<size_t>(sCovW)], static_cast<size_t>(sCovW));
            ID3D12Resource* up = OverlayBackend::createUploadBuffer(rows.data(), rows.size());
            FullscreenFx::toState(cmd, sCover, D3D12_RESOURCE_STATE_COPY_DEST);
            D3D12_TEXTURE_COPY_LOCATION dst{}, src{};
            dst.pResource = sCover.res;
            dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
            src.pResource = up;
            src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
            src.PlacedFootprint.Footprint = {DXGI_FORMAT_R8_UNORM, static_cast<UINT>(sCovW), static_cast<UINT>(sCovH), 1, pitch};
            cmd.list->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
            FullscreenFx::toState(cmd, sCover, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
            OverlayBackend::retire(up);
            sDirty = false;
        }
    }
    OverlayBackend::moveBuffer(cmd, bufferIndex, bufferState, D3D12_RESOURCE_STATE_RENDER_TARGET);
    const float aspect = static_cast<float>(width) / static_cast<float>(height);
    constexpr float kWaveSpeed = 0.9f; // screen heights a second
    const float c[8] = {sWave.since, sWave.amp, kWaveSpeed, aspect, sWave.shakeX, sWave.shakeY, sFull ? 1.f : 0.f, 0.f};
    FullscreenFx::pass(cmd, FullscreenFx::Shock, FullscreenFx::Alpha, sSnap.res, sFull ? nullptr : sCover.res, OverlayBackend::bufferRtv(bufferIndex), OverlayBackend::backFormat(), width, height, c);
}

void ScreenShock::shutdown() {
    end();
}
