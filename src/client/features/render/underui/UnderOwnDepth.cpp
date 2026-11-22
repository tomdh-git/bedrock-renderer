#include "client/features/render/underui/UnderGpuPrivate.h"

// A depth buffer of ours for the swapchain pass (why: RenderTraceHooks.cpp). Same size as the swapchain, a typeless 24 bit depth with 8 bit stencil (the
// format the game's pipeline states are built for) that can be read as a texture; initially in the depth write state, which is where the game keeps its own.

struct UnderOwnDepth {
    static inline std::mutex mu;
    static inline ID3D12Resource* res = nullptr;
    static inline ID3D12DescriptorHeap* heap = nullptr;
    static inline UINT width = 0, height = 0;
};

bool UnderGpu::ownDepthFor(ID3D12GraphicsCommandList* list, ID3D12Resource* swapchainBuffer, D3D12_CPU_DESCRIPTOR_HANDLE& view, uintptr_t& resource) {
    using O = UnderOwnDepth;
    const D3D12_RESOURCE_DESC bd = swapchainBuffer->GetDesc();
    std::lock_guard<std::mutex> lk(O::mu);
    if (O::res && (O::width != bd.Width || O::height != bd.Height)) {
        waitIdle();
        release(O::res);
    }
    if (!O::res) {
        ID3D12Device* d = nullptr;
        BS_CHECK_HR(list->GetDevice(IID_PPV_ARGS(&d)));
        if (!O::heap) {
            D3D12_DESCRIPTOR_HEAP_DESC hd{D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, 0};
            BS_CHECK_HR(d->CreateDescriptorHeap(&hd, IID_PPV_ARGS(&O::heap)));
        }
        D3D12_HEAP_PROPERTIES hp{D3D12_HEAP_TYPE_DEFAULT};
        D3D12_RESOURCE_DESC rd{D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0, bd.Width, bd.Height, 1, 1, DXGI_FORMAT_R24G8_TYPELESS, {1, 0}, D3D12_TEXTURE_LAYOUT_UNKNOWN,
            D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL};
        D3D12_CLEAR_VALUE cv{};
        cv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        cv.DepthStencil = {1.0f, 0};
        BS_CHECK_HR(d->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &rd, D3D12_RESOURCE_STATE_DEPTH_WRITE, &cv, IID_PPV_ARGS(&O::res)));
        D3D12_DEPTH_STENCIL_VIEW_DESC dd{};
        dd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        dd.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        d->CreateDepthStencilView(O::res, &dd, O::heap->GetCPUDescriptorHandleForHeapStart());
        d->Release();
        O::width = static_cast<UINT>(bd.Width);
        O::height = bd.Height;
        Logger::info("[underui] the swapchain pass now draws its depth into a buffer of ours ({}x{}): the scene's depth is readable", O::width, O::height);
        state.erase(reinterpret_cast<uintptr_t>(O::res));
    }
    view = O::heap->GetCPUDescriptorHandleForHeapStart();
    resource = reinterpret_cast<uintptr_t>(O::res);
    return true;
}

// ---- the scene's depth, readable ---------------------------------------------------------------------------------------------

struct UnderReadDepth {
    static inline GpuTexture copy; // the game's typed depth, copied (typeless, so a shader can read it)
};

bool UnderGpu::readableDepth(ID3D12Resource* depth, ReadableDepth& out) {
    const D3D12_RESOURCE_DESC dd = depth->GetDesc();
    DXGI_FORMAT family = DXGI_FORMAT_UNKNOWN;
    switch (dd.Format) {
    case DXGI_FORMAT_R24G8_TYPELESS:
    case DXGI_FORMAT_D24_UNORM_S8_UINT: family = DXGI_FORMAT_R24G8_TYPELESS; out.view = DXGI_FORMAT_R24_UNORM_X8_TYPELESS; break;
    case DXGI_FORMAT_R32_TYPELESS:
    case DXGI_FORMAT_D32_FLOAT: family = DXGI_FORMAT_R32_TYPELESS; out.view = DXGI_FORMAT_R32_FLOAT; break;
    case DXGI_FORMAT_R32G8X24_TYPELESS:
    case DXGI_FORMAT_D32_FLOAT_S8X24_UINT: family = DXGI_FORMAT_R32G8X24_TYPELESS; out.view = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS; break;
    case DXGI_FORMAT_R16_TYPELESS:
    case DXGI_FORMAT_D16_UNORM: family = DXGI_FORMAT_R16_TYPELESS; out.view = DXGI_FORMAT_R16_UNORM; break;
    default: return false;
    }
    out.source = depth;
    if (dd.Format == family && !(dd.Flags & D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE)) {
        out.res = depth;
        return true;
    }
    auto& c = UnderReadDepth::copy;
    if (!c.matches(static_cast<UINT>(dd.Width), dd.Height, family)) {
        waitIdle();
        c.create(dev, static_cast<UINT>(dd.Width), dd.Height, family, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        Logger::info("[underui] the scene's depth (format {}) is copied into a readable texture of ours ({}x{})", static_cast<int>(dd.Format), c.w, c.h);
    }
    out.res = c.res;
    return true;
}

void UnderGpu::recordDepthCopy(const ReadableDepth& depth) {
    if (depth.res == depth.source)
        return;
    const auto it = state.find(reinterpret_cast<uintptr_t>(depth.source));
    const UINT have = it == state.end() ? D3D12_RESOURCE_STATE_DEPTH_WRITE : it->second;
    const bool toSource = !(have & D3D12_RESOURCE_STATE_COPY_SOURCE);
    std::vector<D3D12_RESOURCE_BARRIER> pre, post;
    if (toSource) {
        pre.push_back(transition(depth.source, have, D3D12_RESOURCE_STATE_COPY_SOURCE));
        post.push_back(transition(depth.source, D3D12_RESOURCE_STATE_COPY_SOURCE, have));
    }
    pre.push_back(transition(depth.res, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_COPY_DEST));
    post.push_back(transition(depth.res, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
    list->ResourceBarrier(static_cast<UINT>(pre.size()), pre.data());
    list->CopyResource(depth.res, depth.source);
    list->ResourceBarrier(static_cast<UINT>(post.size()), post.data());
}

void UnderGpu::dropOwnDepth() {
    using O = UnderOwnDepth;
    std::lock_guard<std::mutex> lk(O::mu);
    if (O::res) {
        state.erase(reinterpret_cast<uintptr_t>(O::res));
        waitIdle();
        release(O::res);
    }
    release(O::heap);
    O::width = O::height = 0;
    waitIdle();
    UnderReadDepth::copy.reset();
}
