#include "client/features/render/backend/OverlayBackendState.h"
#include "client/platform/process/Process.h"
#include "client/features/render/backend/D3D12Util.h"

const char* OverlayBackendState::kShader = R"(
cbuffer C : register(b0) { float4x4 proj; };
struct VSIn { float2 pos : POSITION; float2 uv : TEXCOORD0; float4 col : COLOR0; };
struct PSIn { float4 pos : SV_POSITION; float4 col : COLOR0; float2 uv : TEXCOORD0; };
PSIn VS(VSIn i) {
    PSIn o;
    o.pos = mul(proj, float4(i.pos, 0.0, 1.0));
    o.col = i.col;
    o.uv = i.uv;
    return o;
}
Texture2D tex : register(t0);
SamplerState smp : register(s0);
float4 PS(PSIn i) : SV_Target { return i.col * tex.Sample(smp, i.uv); }
)";
OverlayBackendState::State OverlayBackendState::g;
void OverlayBackendState::waitFor(UINT64 value) {
    Platform::GpuSync::wait(g.fence, value, g.event, 5000);
}
void OverlayBackendState::collectRetired() {
    const UINT64 done = g.fence->GetCompletedValue();
    for (size_t i = 0; i < g.retired.size();) {
        if (g.retired[i].fence <= done) {
            g.retired[i].res->Release();
            g.retired.erase(g.retired.begin() + static_cast<long>(i));
        } else {
            ++i;
        }
    }
}
ID3D12Resource* OverlayBackendState::makeBuffer(UINT64 size, D3D12_HEAP_TYPE type, D3D12_RESOURCE_STATES state) {
    D3D12_HEAP_PROPERTIES hp{type};
    D3D12_RESOURCE_DESC rd{D3D12_RESOURCE_DIMENSION_BUFFER, 0, size, 1, 1, 1, DXGI_FORMAT_UNKNOWN, {1, 0}, D3D12_TEXTURE_LAYOUT_ROW_MAJOR, D3D12_RESOURCE_FLAG_NONE};
    ID3D12Resource* r = nullptr;
    BS_CHECK_HR(g.dev->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &rd, state, nullptr, IID_PPV_ARGS(&r)));
    return r;
}
D3D12_CPU_DESCRIPTOR_HANDLE OverlayBackendState::srvCpuAt(UINT slot) {
    D3D12_CPU_DESCRIPTOR_HANDLE h = g.srvHeap->GetCPUDescriptorHandleForHeapStart();
    h.ptr += static_cast<SIZE_T>(slot) * g.srvStep;
    return h;
}
D3D12_GPU_DESCRIPTOR_HANDLE OverlayBackendState::srvGpuAt(UINT slot) {
    D3D12_GPU_DESCRIPTOR_HANDLE h = g.srvHeap->GetGPUDescriptorHandleForHeapStart();
    h.ptr += static_cast<UINT64>(slot) * g.srvStep;
    return h;
}

// The ImGui pipeline for a target format (made the first time the format is drawn to).
ID3D12PipelineState* OverlayBackendState::pipelineFor(DXGI_FORMAT format) {
    auto it = g.pso.find(static_cast<int>(format));
    if (it != g.pso.end())
        return it->second;
    D3D12_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(ImDrawVert, pos), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(ImDrawVert, uv), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, offsetof(ImDrawVert, col), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
    };
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pd{};
    pd.pRootSignature = g.root;
    pd.VS = {g.vs->GetBufferPointer(), g.vs->GetBufferSize()};
    pd.PS = {g.ps->GetBufferPointer(), g.ps->GetBufferSize()};
    pd.InputLayout = {layout, 3};
    auto& rt = pd.BlendState.RenderTarget[0];
    rt.BlendEnable = TRUE;
    rt.SrcBlend = D3D12_BLEND_SRC_ALPHA;
    rt.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
    rt.BlendOp = D3D12_BLEND_OP_ADD;
    rt.SrcBlendAlpha = D3D12_BLEND_ONE;
    rt.DestBlendAlpha = D3D12_BLEND_INV_SRC_ALPHA;
    rt.BlendOpAlpha = D3D12_BLEND_OP_ADD;
    rt.LogicOp = D3D12_LOGIC_OP_NOOP;
    rt.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    pd.SampleMask = UINT_MAX;
    pd.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    pd.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    pd.RasterizerState.DepthClipEnable = TRUE;
    pd.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    pd.NumRenderTargets = 1;
    pd.RTVFormats[0] = format;
    pd.SampleDesc.Count = 1;
    ID3D12PipelineState* pso = nullptr;
    BS_CHECK_HR(g.dev->CreateGraphicsPipelineState(&pd, IID_PPV_ARGS(&pso)));
    g.pso[static_cast<int>(format)] = pso;
    return pso;
}

// The whole texture goes to the GPU through an upload buffer (the atlas is small and changes rarely).
void OverlayBackendState::uploadTexture(ImTextureData* tex, Tex* t, Slot& s, ID3D12GraphicsCommandList* list) {
    const UINT w = static_cast<UINT>(tex->Width), h = static_cast<UINT>(tex->Height);
    const UINT pitch = (w * 4 + 255) & ~255u;
    ID3D12Resource* up = makeBuffer(static_cast<UINT64>(pitch) * h, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
    uint8_t* mapped = nullptr;
    BS_CHECK_HR(up->Map(0, nullptr, reinterpret_cast<void**>(&mapped)));
    const uint8_t* src = static_cast<const uint8_t*>(tex->GetPixels());
    for (UINT y = 0; y < h; ++y)
        memcpy(mapped + static_cast<size_t>(y) * pitch, src + static_cast<size_t>(y) * w * 4, static_cast<size_t>(w) * 4);
    up->Unmap(0, nullptr);
    D3D12_TEXTURE_COPY_LOCATION dst{};
    dst.pResource = t->res;
    dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    D3D12_TEXTURE_COPY_LOCATION from{};
    from.pResource = up;
    from.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    from.PlacedFootprint = {0, {DXGI_FORMAT_R8G8B8A8_UNORM, w, h, 1, pitch}};
    list->CopyTextureRegion(&dst, 0, 0, 0, &from, nullptr);
    s.temps.push_back(up);
}
void OverlayBackendState::updateTexture(ImTextureData* tex, Slot& s, ID3D12GraphicsCommandList* list) {
    if (tex->Status == ImTextureStatus_WantCreate) {
        BS_CHECK(!g.freeSrv.empty());
        BS_CHECK(tex->Format == ImTextureFormat_RGBA32);
        Tex* t = new Tex();
        t->slot = g.freeSrv.back();
        g.freeSrv.pop_back();
        D3D12_HEAP_PROPERTIES hp{D3D12_HEAP_TYPE_DEFAULT};
        D3D12_RESOURCE_DESC rd{D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0, static_cast<UINT64>(tex->Width), static_cast<UINT>(tex->Height), 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, {1, 0}, D3D12_TEXTURE_LAYOUT_UNKNOWN, D3D12_RESOURCE_FLAG_NONE};
        BS_CHECK_HR(g.dev->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &rd, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&t->res)));
        uploadTexture(tex, t, s, list);
        const D3D12_RESOURCE_BARRIER to = D3D12Util::transition(t->res, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        list->ResourceBarrier(1, &to);
        g.dev->CreateShaderResourceView(t->res, nullptr, srvCpuAt(t->slot));
        tex->SetTexID(static_cast<ImTextureID>(srvGpuAt(t->slot).ptr));
        tex->SetStatus(ImTextureStatus_OK);
        tex->BackendUserData = t;
        g.textures.push_back(t);
    } else if (tex->Status == ImTextureStatus_WantUpdates) {
        Tex* t = static_cast<Tex*>(tex->BackendUserData);
        const D3D12_RESOURCE_BARRIER toCopy = D3D12Util::transition(t->res, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_COPY_DEST);
        list->ResourceBarrier(1, &toCopy);
        uploadTexture(tex, t, s, list);
        const D3D12_RESOURCE_BARRIER back = D3D12Util::transition(t->res, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        list->ResourceBarrier(1, &back);
        tex->SetStatus(ImTextureStatus_OK);
    }
    if (tex->Status == ImTextureStatus_WantDestroy && tex->UnusedFrames > 0) {
        Tex* t = static_cast<Tex*>(tex->BackendUserData);
        if (t) {
            g.retired.push_back({t->res, g.value}); // lists up to the last submitted may still read it
            g.freeSrv.push_back(t->slot);
            g.textures.erase(std::remove(g.textures.begin(), g.textures.end(), t), g.textures.end());
            delete t;
        }
        tex->SetTexID(ImTextureID_Invalid);
        tex->SetStatus(ImTextureStatus_Destroyed);
        tex->BackendUserData = nullptr;
    }
}



// The root signature (16 constants for the vertex shader, one texture for the pixel shader) and the shaders; the pipeline for the swapchain's format is made now.
void OverlayBackendState::makePipeline() {
    D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
    D3D12_ROOT_PARAMETER params[2]{};
    params[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    params[0].Constants = {0, 0, 16};
    params[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
    params[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[1].DescriptorTable = {1, &range};
    params[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    const D3D12_STATIC_SAMPLER_DESC ss = D3D12Util::linearSampler();
    D3D12_ROOT_SIGNATURE_DESC rd{2, params, 1, &ss, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT};
    g.root = D3D12Util::createRootSignature(g.dev, rd);
    ID3DBlob* err = nullptr;
    BS_CHECK_HR(D3DCompile(kShader, strlen(kShader), "imgui", nullptr, nullptr, "VS", "vs_5_0", D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &g.vs, &err));
    BS_CHECK_HR(D3DCompile(kShader, strlen(kShader), "imgui", nullptr, nullptr, "PS", "ps_5_0", D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &g.ps, &err));
    pipelineFor(g.format); // the one that is always needed, made now
}



// The descriptor heaps, and the free lists of descriptors the textures, extra targets and depth buffers take from.
void OverlayBackendState::makeDescriptors(UINT bufferCount) {
    g.rtvHeap = GpuUtil::createDescriptorHeap(g.dev, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, bufferCount + kExtraRtvs);
    g.dsvHeap = GpuUtil::createDescriptorHeap(g.dev, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, kDsvs);
    g.srvHeap = GpuUtil::createDescriptorHeap(g.dev, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kStaticSrvs + kSlots * kDynamicPerSlot, true);
    g.rtvStep = g.dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    g.dsvStep = g.dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    g.srvStep = g.dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    g.freeSrv.clear();
    for (UINT i = kStaticSrvs; i > 0; --i)
        g.freeSrv.push_back(i - 1);
    g.freeRtv.clear();
    for (UINT i = kExtraRtvs; i > 0; --i)
        g.freeRtv.push_back(bufferCount + i - 1);
    g.freeDsv.clear();
    for (UINT i = kDsvs; i > 0; --i)
        g.freeDsv.push_back(i - 1);
}



// A view of each back buffer. They are held by identity only: the swapchain owns them, and a reference here would fail the game's ResizeBuffers.
void OverlayBackendState::adoptBackBuffers(IDXGISwapChain* sc, UINT bufferCount) {
    g.buffers.clear();
    for (UINT i = 0; i < bufferCount; ++i) {
        ID3D12Resource* buffer = nullptr;
        BS_CHECK_HR(sc->GetBuffer(i, IID_PPV_ARGS(&buffer)));
        g.dev->CreateRenderTargetView(buffer, nullptr, OverlayBackend::rtvCpu(i));
        g.buffers.push_back(buffer);
        buffer->Release();
    }
}



// Per frame in flight: a command allocator and a persistently mapped upload ring for the vertices; then the one command list they all record into.
void OverlayBackendState::makeSlots() {
    for (Slot& s : g.slots) {
        BS_CHECK_HR(g.dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&s.alloc)));
        s.ring = makeBuffer(kRingBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
        BS_CHECK_HR(s.ring->Map(0, nullptr, reinterpret_cast<void**>(&s.ringMap)));
    }
    BS_CHECK_HR(g.dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g.slots[0].alloc, nullptr, IID_PPV_ARGS(&g.list)));
    BS_CHECK_HR(g.list->Close());
}



// GPU timestamps: a query heap per slot and the readback buffer they are resolved into.
void OverlayBackendState::makeTimestamps(ID3D12CommandQueue* queue) {
    D3D12_QUERY_HEAP_DESC qd{D3D12_QUERY_HEAP_TYPE_TIMESTAMP, kSlots * kQueriesPerSlot, 0};
    BS_CHECK_HR(g.dev->CreateQueryHeap(&qd, IID_PPV_ARGS(&g.qHeap)));
    const D3D12_RESOURCE_DESC qbd{D3D12_RESOURCE_DIMENSION_BUFFER, 0, kSlots * kQueriesPerSlot * sizeof(UINT64), 1, 1, 1, DXGI_FORMAT_UNKNOWN, {1, 0}, D3D12_TEXTURE_LAYOUT_ROW_MAJOR, D3D12_RESOURCE_FLAG_NONE};
    g.qBuf = GpuUtil::createResource(g.dev, D3D12_HEAP_TYPE_READBACK, qbd, D3D12_RESOURCE_STATE_COPY_DEST);
    BS_CHECK_HR(g.qBuf->Map(0, nullptr, reinterpret_cast<void**>(const_cast<UINT64**>(&g.qData))));
    BS_CHECK_HR(queue->GetTimestampFrequency(&g.freq));
}



// The fence the frames wait on, and the immediate list (texture uploads) with its own fence.
void OverlayBackendState::makeSync() {
    BS_CHECK_HR(g.dev->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g.fence)));
    g.event = CreateEventA(nullptr, FALSE, FALSE, nullptr);
    BS_CHECK(g.event);
    BS_CHECK_HR(g.dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g.immAlloc)));
    BS_CHECK_HR(g.dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g.immAlloc, nullptr, IID_PPV_ARGS(&g.immList)));
    BS_CHECK_HR(g.immList->Close());
    BS_CHECK_HR(g.dev->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g.immFence)));
    g.value = 0;
    g.immValue = 0;
    g.next = 0;
}



bool OverlayBackend::init(IDXGISwapChain* sc, ID3D12CommandQueue* queue) {
    BS_CHECK(!OverlayBackendState::g.ready);
    OverlayBackendState::g.queue = queue;
    BS_CHECK_HR(sc->GetDevice(IID_PPV_ARGS(&OverlayBackendState::g.dev)));
    DXGI_SWAP_CHAIN_DESC desc{};
    BS_CHECK_HR(sc->GetDesc(&desc));
    OverlayBackendState::g.format = desc.BufferDesc.Format;
    OverlayBackendState::g.bufferCount = desc.BufferCount;
    OverlayBackendState::makePipeline();
    OverlayBackendState::makeDescriptors(desc.BufferCount);
    OverlayBackendState::adoptBackBuffers(sc, desc.BufferCount);
    OverlayBackendState::makeSlots();
    OverlayBackendState::makeTimestamps(queue);
    OverlayBackendState::makeSync();
    OverlayBackendState::g.ready = true;
    return true;
}

void OverlayBackend::waitIdle() {
    if (OverlayBackendState::g.fence && OverlayBackendState::g.value)
        OverlayBackendState::waitFor(OverlayBackendState::g.value);
}

// Per frame in flight: the temporary uploads, the ring, the allocator.
void OverlayBackendState::releaseSlots() {
    for (Slot& s : g.slots) {
        for (ID3D12Resource* t : s.temps)
            t->Release();
        s.temps.clear();
        if (s.ring)
            s.ring->Unmap(0, nullptr);
        D3D12Util::release(s.ring);
        s.ringMap = nullptr;
        D3D12Util::release(s.alloc);
        s.fence = 0;
        s.ringUsed = 0;
        s.dynUsed = 0;
    }
}



// What the textures held, and what was waiting to be released once the GPU was done with it.
void OverlayBackendState::releaseTextures() {
    for (Retired& r : g.retired)
        r.res->Release();
    g.retired.clear();
    for (Tex* t : g.textures) {
        D3D12Util::release(t->res);
        delete t;
    }
    g.textures.clear();
}



void OverlayBackendState::releaseCommands() {
    if (g.qBuf)
        g.qBuf->Unmap(0, nullptr);
    g.qData = nullptr;
    D3D12Util::release(g.qBuf);
    D3D12Util::release(g.qHeap);
    D3D12Util::release(g.list);
    D3D12Util::release(g.fence);
    D3D12Util::release(g.immList);
    D3D12Util::release(g.immAlloc);
    D3D12Util::release(g.immFence);
    if (g.event) {
        CloseHandle(g.event);
        g.event = nullptr;
    }
}



void OverlayBackendState::releasePipeline() {
    for (auto& [fmt, pso] : g.pso)
        pso->Release();
    g.pso.clear();
    D3D12Util::release(g.vs);
    D3D12Util::release(g.ps);
    D3D12Util::release(g.root);
    D3D12Util::release(g.rtvHeap);
    D3D12Util::release(g.srvHeap);
    D3D12Util::release(g.dsvHeap);
}



void OverlayBackend::shutdown() {
    if (!OverlayBackendState::g.ready && !OverlayBackendState::g.dev)
        return;
    waitIdle();
    OverlayBackendState::releaseSlots();
    OverlayBackendState::releaseTextures();
    OverlayBackendState::releaseCommands();
    OverlayBackendState::releasePipeline();
    OverlayBackendState::g.buffers.clear();
    D3D12Util::release(OverlayBackendState::g.dev);
    OverlayBackendState::g.queue = nullptr;
    OverlayBackendState::g.ready = false;
}

bool OverlayBackend::ready() {
    return OverlayBackendState::g.ready;
}

ID3D12Device* OverlayBackend::device() {
    return OverlayBackendState::g.dev;
}

DXGI_FORMAT OverlayBackend::backFormat() {
    return OverlayBackendState::g.format;
}

UINT OverlayBackend::bufferCount() {
    return static_cast<UINT>(OverlayBackendState::g.buffers.size());
}

int OverlayBackend::bufferIndexOf(uintptr_t resource) {
    for (size_t i = 0; i < OverlayBackendState::g.buffers.size(); ++i)
        if (reinterpret_cast<uintptr_t>(OverlayBackendState::g.buffers[i]) == resource)
            return static_cast<int>(i);
    return -1;
}

ID3D12Resource* OverlayBackend::buffer(UINT index) {
    return reinterpret_cast<ID3D12Resource*>(OverlayBackendState::g.buffers[index]);
}

D3D12_CPU_DESCRIPTOR_HANDLE OverlayBackend::bufferRtv(UINT index) {
    return rtvCpu(index);
}

OverlayBackend::Cmd OverlayBackend::begin(const char* what) {
    BS_CHECK(OverlayBackendState::g.ready);
    const int slot = OverlayBackendState::g.next++ % OverlayBackendState::kSlots;
    OverlayBackendState::Slot& s = OverlayBackendState::g.slots[slot];
    {
        BS_PROFILE("render", "wait overlay slot fence");
        OverlayBackendState::waitFor(s.fence); // the list this slot recorded last time has run
    }
    if (s.timed) { // ... and its GPU time is in the readback buffer
        s.timed = false;
        const UINT64 a = OverlayBackendState::g.qData[slot * OverlayBackendState::kQueriesPerSlot], b = OverlayBackendState::g.qData[slot * OverlayBackendState::kQueriesPerSlot + 1];
        if (b > a && OverlayBackendState::g.freq)
            Profiler::addMs(s.gpuId, static_cast<double>(b - a) * 1000.0 / static_cast<double>(OverlayBackendState::g.freq));
        UINT64 from = a;
        for (int i = 0; i < s.stages; ++i) { // each stage is the time since the one before it ended
            const UINT64 t = OverlayBackendState::g.qData[slot * OverlayBackendState::kQueriesPerSlot + 2 + i];
            if (t > from && OverlayBackendState::g.freq)
                Profiler::addMs(s.stageId[i], static_cast<double>(t - from) * 1000.0 / static_cast<double>(OverlayBackendState::g.freq));
            from = t;
        }
        s.stages = 0;
    }
    for (ID3D12Resource* t : s.temps)
        t->Release();
    s.temps.clear();
    OverlayBackendState::collectRetired();
    BS_CHECK_HR(s.alloc->Reset());
    BS_CHECK_HR(OverlayBackendState::g.list->Reset(s.alloc, nullptr));
    s.ringUsed = 0;
    s.dynUsed = 0;
    ID3D12DescriptorHeap* heaps[] = {OverlayBackendState::g.srvHeap};
    OverlayBackendState::g.list->SetDescriptorHeaps(1, heaps);
    if (Profiler::collecting()) {
        if (!s.gpuName || std::strcmp(s.gpuName, what) != 0) {
            s.gpuName = what;
            s.gpuMetric = Profiler::id("gpu (d3d12 lists)", what);
        }
        s.gpuId = s.gpuMetric;
        s.timed = true;
        OverlayBackendState::g.list->EndQuery(OverlayBackendState::g.qHeap, D3D12_QUERY_TYPE_TIMESTAMP, static_cast<UINT>(slot * OverlayBackendState::kQueriesPerSlot));
    }
    return {OverlayBackendState::g.list, slot};
}

void OverlayBackend::stamp(Cmd& cmd, const char* stage) {
    OverlayBackendState::Slot& s = OverlayBackendState::g.slots[cmd.slot];
    if (!s.timed || s.stages >= OverlayBackendState::kStamps)
        return;
    const int index = s.stages;
    if (!s.stageName[index] || std::strcmp(s.stageName[index], stage) != 0) {
        s.stageName[index] = stage;
        s.stageId[index] = Profiler::id("gpu (stages)", stage);
    }
    cmd.list->EndQuery(OverlayBackendState::g.qHeap, D3D12_QUERY_TYPE_TIMESTAMP, static_cast<UINT>(cmd.slot * OverlayBackendState::kQueriesPerSlot + 2 + s.stages));
    ++s.stages;
}

void OverlayBackend::submit(Cmd& cmd, ID3D12CommandQueue* queue, UnderExec run) {
    if (OverlayBackendState::g.slots[cmd.slot].timed) {
        cmd.list->EndQuery(OverlayBackendState::g.qHeap, D3D12_QUERY_TYPE_TIMESTAMP, static_cast<UINT>(cmd.slot * OverlayBackendState::kQueriesPerSlot + 1));
        cmd.list->ResolveQueryData(OverlayBackendState::g.qHeap, D3D12_QUERY_TYPE_TIMESTAMP, static_cast<UINT>(cmd.slot * OverlayBackendState::kQueriesPerSlot), OverlayBackendState::kQueriesPerSlot, OverlayBackendState::g.qBuf, static_cast<UINT64>(cmd.slot * OverlayBackendState::kQueriesPerSlot * sizeof(UINT64)));
    }
    BS_CHECK_HR(cmd.list->Close());
    ID3D12CommandList* l = cmd.list;
    run(queue, 1, &l);
    BS_CHECK_HR(queue->Signal(OverlayBackendState::g.fence, ++OverlayBackendState::g.value));
    OverlayBackendState::g.slots[cmd.slot].fence = OverlayBackendState::g.value;
    cmd = Cmd{};
}

void* OverlayBackend::upload(Cmd& cmd, size_t size, size_t align, D3D12_GPU_VIRTUAL_ADDRESS* va) {
    OverlayBackendState::Slot& s = OverlayBackendState::g.slots[cmd.slot];
    const size_t at = (s.ringUsed + align - 1) & ~(align - 1);
    BS_CHECK(at + size <= OverlayBackendState::kRingBytes);
    s.ringUsed = at + size;
    *va = s.ring->GetGPUVirtualAddress() + at;
    return s.ringMap + at;
}

UINT OverlayBackend::srvs(Cmd& cmd, UINT count) {
    OverlayBackendState::Slot& s = OverlayBackendState::g.slots[cmd.slot];
    BS_CHECK(s.dynUsed + count <= OverlayBackendState::kDynamicPerSlot);
    const UINT first = OverlayBackendState::kStaticSrvs + static_cast<UINT>(cmd.slot) * OverlayBackendState::kDynamicPerSlot + s.dynUsed;
    s.dynUsed += count;
    return first;
}

D3D12_CPU_DESCRIPTOR_HANDLE OverlayBackend::srvCpu(UINT index) {
    return OverlayBackendState::srvCpuAt(index);
}

D3D12_GPU_DESCRIPTOR_HANDLE OverlayBackend::srvGpu(UINT index) {
    return OverlayBackendState::srvGpuAt(index);
}

UINT OverlayBackend::allocRtv() {
    BS_CHECK(!OverlayBackendState::g.freeRtv.empty());
    const UINT i = OverlayBackendState::g.freeRtv.back();
    OverlayBackendState::g.freeRtv.pop_back();
    return i;
}

void OverlayBackend::freeRtv(UINT index) {
    OverlayBackendState::g.freeRtv.push_back(index);
}

D3D12_CPU_DESCRIPTOR_HANDLE OverlayBackend::rtvCpu(UINT index) {
    D3D12_CPU_DESCRIPTOR_HANDLE h = OverlayBackendState::g.rtvHeap->GetCPUDescriptorHandleForHeapStart();
    h.ptr += static_cast<SIZE_T>(index) * OverlayBackendState::g.rtvStep;
    return h;
}
void OverlayBackend::freeDsv(UINT index) {
    OverlayBackendState::g.freeDsv.push_back(index);
}
ImTextureID OverlayBackend::registerTexture(ID3D12Resource* resource) {
    BS_CHECK(!OverlayBackendState::g.freeSrv.empty());
    const UINT slot = OverlayBackendState::g.freeSrv.back();
    OverlayBackendState::g.freeSrv.pop_back();
    OverlayBackendState::g.dev->CreateShaderResourceView(resource, nullptr, OverlayBackendState::srvCpuAt(slot));
    return static_cast<ImTextureID>(OverlayBackendState::srvGpuAt(slot).ptr);
}

void OverlayBackend::unregisterTexture(ImTextureID id) {
    if (!id || !OverlayBackendState::g.srvHeap)
        return;
    const UINT64 base = OverlayBackendState::g.srvHeap->GetGPUDescriptorHandleForHeapStart().ptr;
    OverlayBackendState::g.freeSrv.push_back(static_cast<UINT>((static_cast<UINT64>(id) - base) / OverlayBackendState::g.srvStep));
}


UINT OverlayBackend::allocDsv() {
    BS_CHECK(!OverlayBackendState::g.freeDsv.empty());
    const UINT i = OverlayBackendState::g.freeDsv.back();
    OverlayBackendState::g.freeDsv.pop_back();
    return i;
}

D3D12_CPU_DESCRIPTOR_HANDLE OverlayBackend::dsvCpu(UINT index) {
    D3D12_CPU_DESCRIPTOR_HANDLE h = OverlayBackendState::g.dsvHeap->GetCPUDescriptorHandleForHeapStart();
    h.ptr += static_cast<SIZE_T>(index) * OverlayBackendState::g.dsvStep;
    return h;
}
