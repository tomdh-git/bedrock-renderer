#include "client/features/render/underui/UnderGpu.h"
#include "client/platform/process/Process.h"
#include "client/features/render/underui/UnderGpuPrivate.h"
#include "client/core/diagnostics/Profiler.h"

// ---- the device objects ----------------------------------------------------------------------------------------------------

void UnderGpu::ensure(ID3D12CommandQueue* queue) {
    using P = UnderGpuPrivate;
    if (dev)
        return;
    BS_CHECK_HR(queue->GetDevice(IID_PPV_ARGS(&dev)));
    D3D12_DESCRIPTOR_HEAP_DESC hd{D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 1, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, 0};
    BS_CHECK_HR(dev->CreateDescriptorHeap(&hd, IID_PPV_ARGS(&P::rtvHeap)));
    hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    BS_CHECK_HR(dev->CreateDescriptorHeap(&hd, IID_PPV_ARGS(&P::dsvHeap)));
    P::rtvStep = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    for (auto& a : P::alloc)
        BS_CHECK_HR(dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&a)));
    BS_CHECK_HR(dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, P::alloc[0], nullptr, IID_PPV_ARGS(&list)));
    BS_CHECK_HR(list->Close());
    BS_CHECK_HR(dev->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&P::fence)));
    P::event = CreateEventA(nullptr, FALSE, FALSE, nullptr);
    BS_CHECK(P::event);

    // GPU timestamps, to know what our passes cost
    D3D12_QUERY_HEAP_DESC qd{D3D12_QUERY_HEAP_TYPE_TIMESTAMP, kPairs * 2, 0};
    BS_CHECK_HR(dev->CreateQueryHeap(&qd, IID_PPV_ARGS(&P::qHeap)));
    D3D12_HEAP_PROPERTIES hp{D3D12_HEAP_TYPE_READBACK};
    D3D12_RESOURCE_DESC bd{D3D12_RESOURCE_DIMENSION_BUFFER, 0, kPairs * 2 * sizeof(UINT64), 1, 1, 1, DXGI_FORMAT_UNKNOWN, {1, 0}, D3D12_TEXTURE_LAYOUT_ROW_MAJOR, D3D12_RESOURCE_FLAG_NONE};
    BS_CHECK_HR(dev->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &bd, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&P::qBuf)));
    BS_CHECK_HR(P::qBuf->Map(0, nullptr, reinterpret_cast<void**>(const_cast<UINT64**>(&P::qData))));
    BS_CHECK_HR(queue->GetTimestampFrequency(&P::freq));
}

void UnderGpu::waitIdle() {
    using P = UnderGpuPrivate;
    if (P::fence && P::value)
        Platform::GpuSync::wait(P::fence, P::value, P::event, 2000);
}

// Resets our list on the next allocator (waiting only if the GPU is that far behind).
void UnderGpu::beginList(ID3D12PipelineState* pso) {
    using P = UnderGpuPrivate;
    BS_PROFILE("underui", "our list: begin (allocator wait, reset)");
    UINT slot = P::frame++ % kRing;
    Platform::GpuSync::wait(P::fence, P::allocValue[slot], P::event, 2000); // the GPU may still be reading this allocator's commands
    BS_CHECK_HR(P::alloc[slot]->Reset());
    BS_CHECK_HR(list->Reset(P::alloc[slot], pso));
    P::allocValue[slot] = P::value + 1; // what the signal after this list will be
}

void UnderGpu::submit(ID3D12CommandQueue* queue, UnderExec run) {
    using P = UnderGpuPrivate;
    BS_PROFILE("underui", "our list: close, execute, signal");
    BS_CHECK_HR(list->Close());
    ID3D12CommandList* l = list;
    run(queue, 1, &l);
    BS_CHECK_HR(queue->Signal(P::fence, ++P::value));
}

// ---- GPU timing ------------------------------------------------------------------------------------------------------------

void UnderGpu::harvest() {
    using P = UnderGpuPrivate;
    const UINT64 done = P::fence->GetCompletedValue();
    for (int p = 0; p < kPairs; ++p) {
        auto& pr = P::pairs[p];
        if (!pr.pending || pr.fence > done)
            continue;
        pr.pending = false;
        const UINT64 a = P::qData[p * 2], b = P::qData[p * 2 + 1];
        if (b > a && P::freq) {
            const double ms = static_cast<double>(b - a) * 1000.0 / static_cast<double>(P::freq);
            sumMs[pr.timer] += ms;
            count[pr.timer]++;
            const double full = ms * pr.bands; // a slice of 1/bands of a shader: the whole of it costs this many times that
            ema[pr.timer] = ema[pr.timer] == 0 ? full : ema[pr.timer] + (full - ema[pr.timer]) * 0.08;
        }
    }
}

int UnderGpu::beginTimed() {
    using P = UnderGpuPrivate;
    int p = P::nextPair;
    if (P::pairs[p].pending)
        return -1; // the oldest measurement is not back yet: skip this one
    P::nextPair = (p + 1) % kPairs;
    list->EndQuery(P::qHeap, D3D12_QUERY_TYPE_TIMESTAMP, static_cast<UINT>(p) * 2);
    return p;
}

void UnderGpu::endTimed(int p, Timer timer, int bands) {
    using P = UnderGpuPrivate;
    if (p < 0)
        return;
    list->EndQuery(P::qHeap, D3D12_QUERY_TYPE_TIMESTAMP, static_cast<UINT>(p) * 2 + 1);
    list->ResolveQueryData(P::qHeap, D3D12_QUERY_TYPE_TIMESTAMP, static_cast<UINT>(p) * 2, 2, P::qBuf, static_cast<UINT64>(p) * 2 * sizeof(UINT64));
    P::pairs[p] = {P::value + 1, static_cast<int>(timer), bands, true}; // the fence value that will be signalled after this list
}

void UnderGpu::takeWindow() {
    for (int i = 0; i < TimerCount; ++i) {
        sumMs[i] = 0;
        count[i] = 0;
    }
}

// ---- the game's target -----------------------------------------------------------------------------------------------------

DXGI_FORMAT UnderGpu::dsvFormatOf(DXGI_FORMAT f) {
    switch (f) {
    case DXGI_FORMAT_R24G8_TYPELESS:
    case DXGI_FORMAT_D24_UNORM_S8_UINT: return DXGI_FORMAT_D24_UNORM_S8_UINT;
    case DXGI_FORMAT_R32_TYPELESS:
    case DXGI_FORMAT_D32_FLOAT: return DXGI_FORMAT_D32_FLOAT;
    case DXGI_FORMAT_R32G8X24_TYPELESS:
    case DXGI_FORMAT_D32_FLOAT_S8X24_UINT: return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
    case DXGI_FORMAT_R16_TYPELESS:
    case DXGI_FORMAT_D16_UNORM: return DXGI_FORMAT_D16_UNORM;
    default: return DXGI_FORMAT_UNKNOWN;
    }
}

D3D12_RESOURCE_BARRIER UnderGpu::transition(ID3D12Resource* r, UINT have, UINT want) {
    return D3D12Util::transition(r, static_cast<D3D12_RESOURCE_STATES>(have), static_cast<D3D12_RESOURCE_STATES>(want));
}

// The depth buffer's DSV flags: written as it is, read only when the game left it in a read state, else brought to write state (and given back).
static D3D12_DSV_FLAGS depthFlags(UnderGpu::Bound& b, ID3D12Resource* depth, uintptr_t depthRes, const std::function<void(ID3D12Resource*, UINT, UINT)>& swapped) {
    auto it = UnderGpu::state.find(depthRes);
    const uint32_t st = it == UnderGpu::state.end() ? D3D12_RESOURCE_STATE_DEPTH_WRITE : it->second;
    if (st & D3D12_RESOURCE_STATE_DEPTH_WRITE)
        return D3D12_DSV_FLAG_NONE;
    if (st & D3D12_RESOURCE_STATE_DEPTH_READ)
        return D3D12_DSV_FLAG_READ_ONLY_DEPTH | D3D12_DSV_FLAG_READ_ONLY_STENCIL;
    swapped(depth, st, D3D12_RESOURCE_STATE_DEPTH_WRITE);
    return D3D12_DSV_FLAG_NONE;
}

UnderGpu::Bound UnderGpu::prepareTarget(const UnderTarget& tg) {
    using P = UnderGpuPrivate;
    Bound b;
    auto* res = reinterpret_cast<ID3D12Resource*>(tg.rt);
    auto* depth = reinterpret_cast<ID3D12Resource*>(tg.depth);
    b.rd = res->GetDesc();
    if (depth) {
        b.dsv = dsvFormatOf(depth->GetDesc().Format);
        BS_CHECK(b.dsv != DXGI_FORMAT_UNKNOWN);
        b.hasDepth = true;
    }
    b.hdr = b.rd.Format == DXGI_FORMAT_R11G11B10_FLOAT || b.rd.Format == DXGI_FORMAT_R16G16B16A16_FLOAT;
    auto swapped = [&](ID3D12Resource* r, UINT have, UINT want) { // brought to the state we need, and given back as the game left it
        b.before.push_back(transition(r, have, want));
        b.after.push_back(GpuUtil::reversed(b.before.back()));
    };
    if (auto it = state.find(tg.rt); it != state.end() && !(it->second & D3D12_RESOURCE_STATE_RENDER_TARGET))
        swapped(res, it->second, D3D12_RESOURCE_STATE_RENDER_TARGET);
    const D3D12_DSV_FLAGS flags = depth ? depthFlags(b, depth, tg.depth, swapped) : D3D12_DSV_FLAG_NONE;
    b.rtv = P::rtvHeap->GetCPUDescriptorHandleForHeapStart();
    dev->CreateRenderTargetView(res, nullptr, b.rtv);
    if (depth) {
        D3D12_DEPTH_STENCIL_VIEW_DESC dd{};
        dd.Format = b.dsv;
        dd.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        dd.Flags = flags;
        b.dsvHandle = P::dsvHeap->GetCPUDescriptorHandleForHeapStart();
        dev->CreateDepthStencilView(depth, &dd, b.dsvHandle);
    }
    return b;
}

D3D12_CPU_DESCRIPTOR_HANDLE UnderGpu::rtvFor(ID3D12Resource* target) {
    D3D12_CPU_DESCRIPTOR_HANDLE h = UnderGpuPrivate::rtvHeap->GetCPUDescriptorHandleForHeapStart();
    dev->CreateRenderTargetView(target, nullptr, h);
    return h;
}

void UnderGpu::bindAndSize(const Bound& b) {
    list->OMSetRenderTargets(1, &b.rtv, FALSE, b.hasDepth ? &b.dsvHandle : nullptr);
    D3D12_VIEWPORT vp{0, 0, static_cast<float>(b.rd.Width), static_cast<float>(b.rd.Height), 0, 1};
    D3D12_RECT sr{0, 0, static_cast<LONG>(b.rd.Width), static_cast<LONG>(b.rd.Height)};
    list->RSSetViewports(1, &vp);
    list->RSSetScissorRects(1, &sr);
}
// ---- teardown --------------------------------------------------------------------------------------------------------------

// A closed command list keeps a reference to every resource it recorded until it is reset, and the game's ResizeBuffers is refused while any reference to
// its swapchain buffers lives: our last list (it drew into the game's target, often the buffer itself) is emptied here, once the GPU is done with it.
void UnderGpu::dropTargets() {
    using P = UnderGpuPrivate;
    if (!list || !P::alloc[0])
        return;
    waitIdle();
    // Every allocator keeps the resources its recorded commands used alive until it is reset, and the ring is 64 deep: DXGI refuses to resize
    // the swapchain (INVALID_CALL) while any of them still holds a back buffer.
    for (auto* a : P::alloc)
        BS_CHECK_HR(a->Reset());
    BS_CHECK_HR(list->Reset(P::alloc[0], nullptr));
    BS_CHECK_HR(list->Close());
}

// The pipelines and shader blobs the worker built.
static void releaseBuilt() {
    using P = UnderGpuPrivate;
    for (auto& [key, pso] : P::bld.pso)
        pso->Release();
    P::bld.pso.clear();
    P::bld.requested.clear();
    P::bld.jobs.clear();
    for (auto& [key, b] : P::bld.blobs)
        if (b)
            b->Release();
    P::bld.blobs.clear();
}

static void releaseDeviceObjects() {
    using P = UnderGpuPrivate;
    if (P::qBuf) {
        P::qBuf->Unmap(0, nullptr);
        P::qData = nullptr;
    }
    UnderGpu::release(P::qBuf);
    UnderGpu::release(P::qHeap);
    UnderGpu::release(UnderGpu::list);
    for (auto& a : P::alloc)
        UnderGpu::release(a);
    UnderGpu::release(P::rtvHeap);
    UnderGpu::release(P::dsvHeap);
    UnderGpu::release(P::fence);
    if (P::event) {
        CloseHandle(P::event);
        P::event = nullptr;
    }
    UnderGpu::release(UnderGpu::dev);
}

static void resetCounters() {
    using P = UnderGpuPrivate;
    P::value = 0;
    P::frame = 0;
    P::nextPair = 0;
    for (auto& a : P::allocValue)
        a = 0;
    for (auto& p : P::pairs)
        p = P::Pair{};
    for (int i = 0; i < UnderGpu::TimerCount; ++i)
        UnderGpu::ema[i] = 0;
    UnderGpu::takeWindow();
    UnderGpu::state.clear();
}

void UnderGpu::shutdown() {
    stopBuilder();
    waitIdle();
    releaseBuilt();
    releaseDeviceObjects();
    resetCounters();
}
