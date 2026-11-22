#include "client/features/render/backend/OverlayBackendState.h"
#include "client/platform/process/Process.h"


void OverlayBackend::moveBuffer(Cmd& cmd, UINT index, D3D12_RESOURCE_STATES& cur, D3D12_RESOURCE_STATES to) {
    if (cur == to)
        return;
    const D3D12_RESOURCE_BARRIER b = D3D12Util::transition(buffer(index), cur, to);
    cmd.list->ResourceBarrier(1, &b);
    cur = to;
}

void OverlayBackend::retire(ID3D12Resource* resource) {
    if (resource)
        OverlayBackendState::g.retired.push_back({resource, OverlayBackendState::g.value});
}

ID3D12Resource* OverlayBackend::createTexture(const void* pixels, UINT width, UINT height, DXGI_FORMAT format, UINT rowPitch) {
    BS_CHECK(OverlayBackendState::g.ready);
    D3D12_HEAP_PROPERTIES hp{D3D12_HEAP_TYPE_DEFAULT};
    D3D12_RESOURCE_DESC rd{D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0, width, height, 1, 1, format, {1, 0}, D3D12_TEXTURE_LAYOUT_UNKNOWN, D3D12_RESOURCE_FLAG_NONE};
    ID3D12Resource* tex = nullptr;
    BS_CHECK_HR(OverlayBackendState::g.dev->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &rd, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&tex)));

    D3D12_PLACED_SUBRESOURCE_FOOTPRINT fp{};
    UINT rows = 0;
    UINT64 rowBytes = 0, total = 0;
    OverlayBackendState::g.dev->GetCopyableFootprints(&rd, 0, 1, 0, &fp, &rows, &rowBytes, &total);
    ID3D12Resource* up = OverlayBackendState::makeBuffer(total, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
    uint8_t* mapped = nullptr;
    BS_CHECK_HR(up->Map(0, nullptr, reinterpret_cast<void**>(&mapped)));
    const uint8_t* src = static_cast<const uint8_t*>(pixels);
    for (UINT y = 0; y < rows; ++y)
        memcpy(mapped + fp.Offset + static_cast<size_t>(y) * fp.Footprint.RowPitch, src + static_cast<size_t>(y) * rowPitch, static_cast<size_t>(std::min<UINT64>(rowBytes, rowPitch)));
    up->Unmap(0, nullptr);

    BS_CHECK_HR(OverlayBackendState::g.immAlloc->Reset());
    BS_CHECK_HR(OverlayBackendState::g.immList->Reset(OverlayBackendState::g.immAlloc, nullptr));
    D3D12_TEXTURE_COPY_LOCATION dst{};
    dst.pResource = tex;
    dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    D3D12_TEXTURE_COPY_LOCATION from{};
    from.pResource = up;
    from.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    from.PlacedFootprint = fp;
    OverlayBackendState::g.immList->CopyTextureRegion(&dst, 0, 0, 0, &from, nullptr);
    const D3D12_RESOURCE_BARRIER to = D3D12Util::transition(tex, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    OverlayBackendState::g.immList->ResourceBarrier(1, &to);
    BS_CHECK_HR(OverlayBackendState::g.immList->Close());
    ID3D12CommandList* l = OverlayBackendState::g.immList;
    OverlayBackendState::g.queue->ExecuteCommandLists(1, &l);
    BS_CHECK_HR(OverlayBackendState::g.queue->Signal(OverlayBackendState::g.immFence, ++OverlayBackendState::g.immValue));
    Platform::GpuSync::wait(OverlayBackendState::g.immFence, OverlayBackendState::g.immValue, OverlayBackendState::g.event, 10000);
    up->Release();
    return tex;
}

// Where the frame's vertices and indices were copied to in the upload ring.
struct OverlayBackendState::Geometry {
    D3D12_GPU_VIRTUAL_ADDRESS vbVa = 0, ibVa = 0;
    size_t vbSize = 0, ibSize = 0;
};
OverlayBackendState::Geometry OverlayBackendState::uploadGeometry(OverlayBackend::Cmd& cmd, ImDrawData* data) {
    Geometry geo;
    geo.vbSize = std::max<size_t>(static_cast<size_t>(data->TotalVtxCount) * sizeof(ImDrawVert), 16);
    geo.ibSize = std::max<size_t>(static_cast<size_t>(data->TotalIdxCount) * sizeof(ImDrawIdx), 16);
    ImDrawVert* vtx = static_cast<ImDrawVert*>(OverlayBackend::upload(cmd, geo.vbSize, 16, &geo.vbVa));
    ImDrawIdx* idx = static_cast<ImDrawIdx*>(OverlayBackend::upload(cmd, geo.ibSize, 16, &geo.ibVa));
    for (const ImDrawList* l : data->CmdLists) {
        memcpy(vtx, l->VtxBuffer.Data, static_cast<size_t>(l->VtxBuffer.Size) * sizeof(ImDrawVert));
        memcpy(idx, l->IdxBuffer.Data, static_cast<size_t>(l->IdxBuffer.Size) * sizeof(ImDrawIdx));
        vtx += l->VtxBuffer.Size;
        idx += l->IdxBuffer.Size;
    }
    return geo;
}

// The orthographic projection of the draw data's rectangle.
void OverlayBackendState::projection(const ImDrawData* data, float (&mvp)[4][4]) {
    const float L = data->DisplayPos.x, R = data->DisplayPos.x + data->DisplaySize.x, T = data->DisplayPos.y, B = data->DisplayPos.y + data->DisplaySize.y;
    const float m[4][4] = {
        {2.0f / (R - L), 0.0f, 0.0f, 0.0f},
        {0.0f, 2.0f / (T - B), 0.0f, 0.0f},
        {0.0f, 0.0f, 0.5f, 0.0f},
        {(R + L) / (L - R), (T + B) / (B - T), 0.5f, 1.0f},
    };
    memcpy(mvp, m, sizeof(m));
}
void OverlayBackendState::bindState(ID3D12GraphicsCommandList* list, ID3D12PipelineState* pso, const float (&mvp)[4][4], const D3D12_VIEWPORT& vp, const Geometry& geo) {
    list->SetPipelineState(pso);
    list->SetGraphicsRootSignature(g.root);
    list->SetGraphicsRoot32BitConstants(0, 16, mvp, 0);
    list->RSSetViewports(1, &vp);
    const D3D12_VERTEX_BUFFER_VIEW vbv{geo.vbVa, static_cast<UINT>(geo.vbSize), sizeof(ImDrawVert)};
    const D3D12_INDEX_BUFFER_VIEW ibv{geo.ibVa, static_cast<UINT>(geo.ibSize), sizeof(ImDrawIdx) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT};
    list->IASetVertexBuffers(0, 1, &vbv);
    list->IASetIndexBuffer(&ibv);
    list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    const float factor[4] = {0, 0, 0, 0};
    list->OMSetBlendFactor(factor);
}

// Every draw command of every list: its clip rectangle as the scissor, its texture, its indices.
void OverlayBackendState::drawCommands(ID3D12GraphicsCommandList* list, ImDrawData* data, const std::function<void()>& rebind) {
    int vtxOffset = 0, idxOffset = 0;
    const ImVec2 clipOff = data->DisplayPos, clipScale = data->FramebufferScale;
    for (const ImDrawList* l : data->CmdLists) {
        for (const ImDrawCmd& c : l->CmdBuffer) {
            if (c.UserCallback) {
                if (c.UserCallback == ImDrawCallback_ResetRenderState)
                    rebind();
                else
                    c.UserCallback(l, &c);
                continue;
            }
            const ImVec2 mn((c.ClipRect.x - clipOff.x) * clipScale.x, (c.ClipRect.y - clipOff.y) * clipScale.y);
            const ImVec2 mx((c.ClipRect.z - clipOff.x) * clipScale.x, (c.ClipRect.w - clipOff.y) * clipScale.y);
            if (mx.x <= mn.x || mx.y <= mn.y)
                continue;
            const D3D12_RECT scissor{static_cast<LONG>(mn.x), static_cast<LONG>(mn.y), static_cast<LONG>(mx.x), static_cast<LONG>(mx.y)};
            list->RSSetScissorRects(1, &scissor);
            list->SetGraphicsRootDescriptorTable(1, D3D12_GPU_DESCRIPTOR_HANDLE{static_cast<UINT64>(c.GetTexID())});
            list->DrawIndexedInstanced(c.ElemCount, 1, c.IdxOffset + idxOffset, static_cast<INT>(c.VtxOffset) + vtxOffset, 0);
        }
        idxOffset += l->IdxBuffer.Size;
        vtxOffset += l->VtxBuffer.Size;
    }
}


void OverlayBackend::drawImGui(Cmd& cmd, ImDrawData* data, D3D12_CPU_DESCRIPTOR_HANDLE rtv, DXGI_FORMAT format, float widthPx, float heightPx) {
    if (data->DisplaySize.x <= 0.0f || data->DisplaySize.y <= 0.0f)
        return;
    ID3D12GraphicsCommandList* list = cmd.list;
    if (data->Textures)
        for (ImTextureData* tex : *data->Textures)
            if (tex->Status != ImTextureStatus_OK)
                OverlayBackendState::updateTexture(tex, OverlayBackendState::g.slots[cmd.slot], list);
    const OverlayBackendState::Geometry geo = OverlayBackendState::uploadGeometry(cmd, data);
    list->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
    float mvp[4][4];
    OverlayBackendState::projection(data, mvp);
    const D3D12_VIEWPORT vp{0.0f, 0.0f, widthPx, heightPx, 0.0f, 1.0f};
    ID3D12PipelineState* pso = OverlayBackendState::pipelineFor(format);
    const auto rebind = [&] { OverlayBackendState::bindState(list, pso, mvp, vp, geo); };
    rebind();
    OverlayBackendState::drawCommands(list, data, rebind);
}

void OverlayBackend::draw(ID3D12CommandQueue* queue, UnderExec run, ImDrawData* data, UINT index, D3D12_RESOURCE_STATES state) {
    BS_CHECK(OverlayBackendState::g.ready && index < OverlayBackendState::g.buffers.size());
    Cmd cmd = begin();
    ID3D12Resource* res = buffer(index);
    if (state != D3D12_RESOURCE_STATE_RENDER_TARGET) {
        const D3D12_RESOURCE_BARRIER in = D3D12Util::transition(res, state, D3D12_RESOURCE_STATE_RENDER_TARGET);
        cmd.list->ResourceBarrier(1, &in);
    }
    drawImGui(cmd, data, rtvCpu(index), OverlayBackendState::g.format, data->DisplaySize.x * data->FramebufferScale.x, data->DisplaySize.y * data->FramebufferScale.y);
    if (state != D3D12_RESOURCE_STATE_RENDER_TARGET) {
        const D3D12_RESOURCE_BARRIER out = D3D12Util::transition(res, D3D12_RESOURCE_STATE_RENDER_TARGET, state);
        cmd.list->ResourceBarrier(1, &out);
    }
    submit(cmd, queue, run);
}

ID3D12Resource* OverlayBackend::createUploadBuffer(const void* data, size_t size) {
    ID3D12Resource* r = OverlayBackendState::makeBuffer(size, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
    void* mapped = nullptr;
    BS_CHECK_HR(r->Map(0, nullptr, &mapped));
    memcpy(mapped, data, size);
    r->Unmap(0, nullptr);
    return r;
}
