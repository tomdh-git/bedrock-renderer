#include "client/features/render/tracker/TrackerState.h"
#include "client/platform/text/StringUtils.h"
#include "client/features/hooks/VtableHook.h"
#include "client/features/render/lce/Renderer.h"
#include "client/features/render/chams/Renderer.h"
#include "client/features/hooks/hooks/render/ActorRenderDispatcherHook.h"
#include "client/features/hooks/hooks/render/FrameFilterHook.h"
#include "client/features/hooks/hooks/render/RenderMarkHook.h"
#include "client/features/render/tracker/DiagStack.h"
#include "client/platform/time/Time.h"
#include "client/features/render/underui/UnderUI.h"


std::mutex TrackerState::sRetainedMu;
std::unordered_map<uintptr_t, TrackerState::Retained> TrackerState::sRetained;
std::atomic<ID3D12Device*> TrackerState::sDevice {nullptr};

std::unique_ptr<VtableHook> TrackerState::sDraw;
std::unique_ptr<VtableHook> TrackerState::sDrawIdx;
std::unique_ptr<VtableHook> TrackerState::sPso;
std::unique_ptr<VtableHook> TrackerState::sBarrier;
std::unique_ptr<VtableHook> TrackerState::sOmRt;
std::unique_ptr<VtableHook> TrackerState::sStencilRef;
std::unique_ptr<VtableHook> TrackerState::sClearRt;
std::unique_ptr<VtableHook> TrackerState::sClearDs;
std::unique_ptr<VtableHook> TrackerState::sReset;
std::unique_ptr<VtableHook> TrackerState::sScissor;
std::unique_ptr<VtableHook> TrackerState::sExecute;
std::unique_ptr<VtableHook> TrackerState::sCreateRtv;
std::unique_ptr<VtableHook> TrackerState::sCreateDsv;
std::unique_ptr<VtableHook> TrackerState::sCopyDescSimple;
std::unique_ptr<VtableHook> TrackerState::sCopyDesc;
std::unique_ptr<VtableHook> TrackerState::sCreatePso;

// ---- command list ----------------------------------------------------------------------------------------------------
// Chams: the twin of the state this draw uses, if chams are on and the list is the one whose state we saw set.
static ID3D12PipelineState* chamsTwin(ID3D12GraphicsCommandList* list) {
    if (!ChamsRenderer::active() || TrackerState::tCurList != list)
        return nullptr;
    // No per-actor flag here: the game records these draws after ActorRenderDispatcher::render has returned (the flag was never up at a draw: 0 twin draws). The
    // filter is the draw path itself: twinOf gives nothing for the DDRv2 batch states, which is where every actor not sent to DDRv1 goes (the bots Anti Bot flags).
    return ChamsRenderer::ensureTwin(reinterpret_cast<uintptr_t>(TrackerState::tCurGamePso), TrackerState::tCurSerial);
}
void __stdcall TrackerState::rsSetScissorRects(ID3D12GraphicsCommandList* self, UINT n, const D3D12_RECT* rects) {
    tScissorList = self;
    tScissorCount = n < 8 ? n : 8;
    for (UINT i = 0; i < tScissorCount; ++i)
        tScissor[i] = rects[i];
    if (!sScissor) return;
    sScissor->getOriginal<&rsSetScissorRects>()(self, n, rects);
}

// The twin draw of chams, around the game's own draw: the state swapped in. `draw` issues the draw call through the original function.
template <typename Draw>
static void chamsDraws(ID3D12GraphicsCommandList* self, ID3D12PipelineState* twin, unsigned slot, Draw draw) {
    using T = TrackerState;
    {   // the players are the only actors the game draws alone; the twin table has no entry for its batches
        if (Logger::verbose)
            ActorRenderDispatcherHook::chamsPlayerDraws.fetch_add(1, std::memory_order_relaxed);
        // The player is drawn into a picture and a depth buffer of ours, cleared once a frame: its own parts sort against each other (a front face and a back face are
        // never both shown), nothing of the world is in the way, so it shows through, and the chams pass puts it over the scene after the blur. The game's targets are
        // bound again after.
        D3D12_CPU_DESCRIPTOR_HANDLE rtv{}, dsv{};
        const uintptr_t target = T::sFrameTarget.load();
        bool clear = false;
        const bool ownTargets = target && T::tRtList == self && T::tRtCount > 0 && (T::isBackBuffer(T::viewOf(T::tRts[0].ptr).res) || T::isSwapHandle(T::tRts[0].ptr)) &&
                                ChamsRenderer::targetsFor(T::device(), reinterpret_cast<ID3D12Resource*>(target), rtv, dsv, clear);
        if (!ownTargets) {
            ActorRenderDispatcherHook::chamsDraftsDropped.fetch_add(1, std::memory_order_relaxed);
            return; // not the scene's pass (a shadow map, a preview): no chams there
        }
        if (clear) {
            const FLOAT none[4] = {0, 0, 0, 0};
            T::sClearRt->getOriginal<&T::clearRenderTargetView>()(self, rtv, none, 0, nullptr);
            T::sClearDs->getOriginal<&T::clearDepthStencilView>()(self, dsv, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, ChamsRenderer::clearDepth(), 0, 0, nullptr);
        }
        ChamsRenderer::markDrawn(target);
        T::sOmRt->getOriginal<&T::omSetRenderTargets>()(self, 1, &rtv, FALSE, &dsv);
        T::sPso->getOriginal<&T::setPipelineState>()(self, twin);
        // The twin writes the player's roster number into the stencil wherever it draws a pixel: the picture says whose every pixel is.
        T::sStencilRef->getOriginal<&T::omSetStencilRef>()(self, slot);
        draw();
        T::sStencilRef->getOriginal<&T::omSetStencilRef>()(self, T::tStencilList == self ? T::tStencilRef : 0u); // the game's own value back
        T::sPso->getOriginal<&T::setPipelineState>()(self, T::tCurBound);
        T::sOmRt->getOriginal<&T::omSetRenderTargets>()(self, T::tRtCount, T::tRts, T::tRtSingle, T::tRtHasDs ? &T::tRtDs : nullptr);
    }
}
// The exact selector: a draw of a wanted player carries RenderMarkHook::kRosterStartInstance as its start instance (see RenderMarkHook.h). The game is given 0, as it always had;
// only a draw that carries the value may have a twin.
void __stdcall TrackerState::drawInstanced(ID3D12GraphicsCommandList* self, UINT vc, UINT ic, UINT sv, UINT si) {
    noteDraw(self, vc);
    const unsigned slot = RenderMarkHook::slotOf(si);
    if (slot)
        si = 0;
    if (slot)
        if (ID3D12PipelineState* twin = chamsTwin(self))
            chamsDraws(self, twin, slot, [&] { sDraw->getOriginal<&drawInstanced>()(self, vc, ic, sv, si); });
    sDraw->getOriginal<&drawInstanced>()(self, vc, ic, sv, si);
}
void __stdcall TrackerState::drawIndexedInstanced(ID3D12GraphicsCommandList* self, UINT ic, UINT inst, UINT si, INT bv, UINT sinst) {
    noteDraw(self, ic);
    const unsigned slot = RenderMarkHook::slotOf(sinst);
    if (slot)
        sinst = 0;
    if (slot) {
        if (ID3D12PipelineState* twin = chamsTwin(self)) {
            ChamsRenderer::noteDraw(ic);
            chamsDraws(self, twin, slot, [&] { sDrawIdx->getOriginal<&drawIndexedInstanced>()(self, ic, inst, si, bv, sinst); });
        }
    }
    sDrawIdx->getOriginal<&drawIndexedInstanced>()(self, ic, inst, si, bv, sinst);
}

// A pipeline state made before the hooks were in: whether the game gave it a debug name (a name would say what it is), for the first few.
void TrackerState::probeUnknownPso(ID3D12PipelineState* pso) {
    static std::mutex sMu;
    static std::unordered_set<uintptr_t> sSeen;
    static int sLogged = 0;
    std::lock_guard<std::mutex> lk(sMu);
    if (sLogged >= 24 || !sSeen.insert(reinterpret_cast<uintptr_t>(pso)).second)
        return;
    static const GUID kName = {0x429b8c22, 0x9188, 0x4b0c, {0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00}}; // WKPDID_D3DDebugObjectName
    static const GUID kNameW = {0x4cca5fd8, 0x921f, 0x42c8, {0x85, 0x66, 0x70, 0xca, 0xf2, 0xa9, 0xb7, 0x41}}; // WKPDID_D3DDebugObjectNameW
    char name[128] = {};
    UINT size = sizeof(name) - 1;
    const HRESULT hr = pso->GetPrivateData(kName, &size, name);
    wchar_t wname[128] = {};
    UINT wsize = sizeof(wname) - sizeof(wchar_t);
    const HRESULT hrw = pso->GetPrivateData(kNameW, &wsize, wname);
    ++sLogged;
    Logger::info("[tracker] pipeline state {:#x} was made before the hooks: debug name {} / {}", reinterpret_cast<uintptr_t>(pso), SUCCEEDED(hr) ? name : "(none)", SUCCEEDED(hrw) ? "(wide name set)" : "(none)");
}
// bgfx sets a pipeline state whenever it changes, hundreds of times a frame on each recording thread. The answer for a state is kept per thread in a small table,
// so a state already seen costs no lock and no hash lookup; the table is dropped as a whole when any state is created (sPsoGeneration), which also covers a freed
// state's address being given to a new one.
TrackerState::PsoFacts TrackerState::psoFacts(ID3D12PipelineState* pso) {
    struct Cached {
        const void* pso = nullptr;
        uint32_t generation = 0;
        PsoFacts facts;
    };
    constexpr size_t kCached = 256;
    thread_local Cached tCached[kCached];
    const uintptr_t key = reinterpret_cast<uintptr_t>(pso);
    Cached& c = tCached[((key >> 4) ^ (key >> 12)) & (kCached - 1)];
    const uint32_t generation = sPsoGeneration.load(std::memory_order_acquire);
    if (c.pso == pso && c.generation == generation)
        return c.facts;
    PsoFacts out;
    {
        std::lock_guard<std::mutex> lk(sPsoMu);
        const auto it = sPsos.find(key);
        if (it != sPsos.end()) {
            const PsoInfo& i = it->second;
            out.known = true;
            out.flat = !i.depth && !i.blend;     // flat: depth test off and no blending (a full-screen pass writing the target as it is)
            out.flatBlend = !i.depth && i.blend; // depth test off and blending: over the scene whatever is in front of it (the through-wall nametags)
            // sun and moon (position, colour, uv) or stars (position, colour): depth tested, no depth write, blended; seen in the traces and in
            // sky.material (the blend factors alone did not match what the game creates)
            out.cel = i.depth && !i.depthWrite && i.blend && i.celLayout;
            out.write = i.depth && i.depthWrite; // writes depth: world geometry, not sky
            out.blend = i.blend;
            out.role = i.role;
            out.actor = i.role == MatRole::Entity || i.skinned; // an entity: its material, or the skinned mesh vertex layout (bones per vertex)
            out.posUv = i.posUvLayout;
            out.serial = i.serial;
        }
    }
    if (!out.known)
        probeUnknownPso(pso);
    c = Cached{pso, generation, out};
    return out;
}

void __stdcall TrackerState::setPipelineState(ID3D12GraphicsCommandList* self, ID3D12PipelineState* pso) {
    const PsoFacts p = psoFacts(pso);
    {
        facts(self, [&](ListFacts& f) {
            if (!f.psoFirst)
                f.psoFirst = reinterpret_cast<uintptr_t>(pso);
            f.psoLast = reinterpret_cast<uintptr_t>(pso);
            f.flatPso = p.flat;
            f.psoKnown = p.known;
            f.celPso = p.cel;
            f.writePso = p.write;
            f.blendPso = p.blend;
            f.flatBlendPso = p.flatBlend;
            f.actorPso = p.actor;
            f.curRole = p.role;
            f.posUvPso = p.posUv;
        });
    }
    tCurList = self;
    tCurGamePso = pso;
    tCurSerial = p.serial;
    pso = LceRenderer::substitute(pso, p.serial); // LCE on: our twin of exactly this state; off (one atomic read) or no twin: the game's own, unchanged
    tCurBound = pso;
    sPso->getOriginal<&setPipelineState>()(self, pso);
}
void __stdcall TrackerState::resourceBarrier(ID3D12GraphicsCommandList* self, UINT n, const D3D12_RESOURCE_BARRIER* barriers) {
    for (UINT i = 0; i < n; ++i) {
        if (barriers[i].Type != D3D12_RESOURCE_BARRIER_TYPE_TRANSITION)
            continue;
        const auto& t = barriers[i].Transition;
        auto res = reinterpret_cast<uintptr_t>(t.pResource);
        const bool acquire = t.StateBefore == D3D12_RESOURCE_STATE_PRESENT && (t.StateAfter & D3D12_RESOURCE_STATE_RENDER_TARGET) && isBackBuffer(res);
        if (acquire)
            sFrameTarget.store(res);
        facts(self, [&](ListFacts& f) {
            f.acquired |= acquire;
            f.transitions.emplace_back(res, static_cast<uint32_t>(t.StateAfter));
            f.barriers.push_back(barriers[i]);
        });
    }
    sBarrier->getOriginal<&resourceBarrier>()(self, n, barriers);
}

// The swapchain pass's depth view is one the game made before the DLL was injected, so which resource it is stays unknown to us (a view is a handle; only
// its creation says what it is). In the regular renderer that depth buffer is only ever bound as a depth view and cleared (the traces show no copy, resolve,
// barrier or read of it), so when a pass wants the scene's depth the swapchain pass is given a depth buffer of ours instead: from the next clear of that
std::atomic<uintptr_t> TrackerState::sSwapDepthHandle {0}; // the unknown depth view the swapchain pass uses (learned from a bind)
std::atomic<bool> TrackerState::sOwnDepthOn {false};      // the swapchain pass draws into our depth buffer
void __stdcall TrackerState::omSetRenderTargets(ID3D12GraphicsCommandList* self, UINT n, const D3D12_CPU_DESCRIPTOR_HANDLE* rts, BOOL single, const D3D12_CPU_DESCRIPTOR_HANDLE* ds) {
    D3D12_CPU_DESCRIPTOR_HANDLE own{};
    uintptr_t ownRes = 0;
    // The swapchain buffer's view usually predates the injection too (its resource is unknown): it is then told by its handle, learned at the acquire barrier.
    const uintptr_t bufferRes = n && rts ? viewOf(rts[0].ptr).res : 0;
    if (n && rts && ds && (isBackBuffer(bufferRes) || isSwapHandle(rts[0].ptr)) && viewOf(ds->ptr).res == 0) {
        if (sSwapDepthHandle.exchange(ds->ptr) == 0)
            Logger::info("[underui] the swapchain pass's depth view learned (a view that predates the injection); our own depth is {} for it", sOwnDepthOn.load() ? "on" : "off until its next clear");
        const uintptr_t target = bufferRes ? bufferRes : sFrameTarget.load();
        if (sOwnDepthOn.load() && target && UnderGpu::ownDepthFor(self, reinterpret_cast<ID3D12Resource*>(target), own, ownRes))
            ds = &own;
    }
    if (n && rts) {
        uintptr_t handle = rts[0].ptr, res = viewOf(handle).res;
        uintptr_t dsHandle = ds ? ds->ptr : 0, dsRes = ownRes ? ownRes : ds ? viewOf(dsHandle).res : 0;
        facts(self, [&](ListFacts& f) {
            if (f.rtHandle)
                return; // the first bind is the list's target
            f.rtHandle = handle;
            f.rtRes = res;
            f.dsRes = dsRes;
            f.rtCount = static_cast<uint8_t>(std::min<UINT>(n, 8));
            static UINT sInc = 0; // the render target views of a single-range bind are consecutive descriptors
            if (single && n > 1 && !sInc) {
                ID3D12Device* dev = nullptr;
                BS_CHECK_HR(self->GetDevice(IID_PPV_ARGS(&dev)));
                sInc = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
                dev->Release();
            }
            for (UINT i = 0; i < f.rtCount; ++i)
                f.rtAll[i] = viewOf(single ? rts[0].ptr + i * sInc : rts[i].ptr).res;
            if (f.acquired) {
                sSwapHandle.store(handle);
                rememberSwapHandle(handle);
            }
        });
    }
    tRtList = self;
    tRtCount = n < 8 ? n : 8;
    tRtSingle = single;
    for (UINT i = 0; i < tRtCount && rts; ++i)
        tRts[i] = rts[i]; // a single-range bind has only the first handle to give
    tRtHasDs = ds != nullptr;
    tRtDs = ds ? *ds : D3D12_CPU_DESCRIPTOR_HANDLE{};
    sOmRt->getOriginal<&omSetRenderTargets>()(self, n, rts, single, ds);
}
void __stdcall TrackerState::omSetStencilRef(ID3D12GraphicsCommandList* self, UINT ref) {
    tStencilList = self;
    tStencilRef = ref;
    sStencilRef->getOriginal<&omSetStencilRef>()(self, ref);
}
void __stdcall TrackerState::clearRenderTargetView(ID3D12GraphicsCommandList* self, D3D12_CPU_DESCRIPTOR_HANDLE h, const FLOAT color[4], UINT nr, const D3D12_RECT* r) {
    facts(self, [&](ListFacts& f) { f.colorClear = true; });
    sClearRt->getOriginal<&clearRenderTargetView>()(self, h, color, nr, r);
}
void __stdcall TrackerState::clearDepthStencilView(ID3D12GraphicsCommandList* self, D3D12_CPU_DESCRIPTOR_HANDLE h, D3D12_CLEAR_FLAGS flags, FLOAT depth, UINT8 stencil, UINT nr, const D3D12_RECT* r) {
    if (h.ptr == sSwapDepthHandle.load() && viewOf(h.ptr).res == 0) {
        // the swapchain pass's depth is cleared: the moment to start (or stop) using our own, so a frame never mixes the two
        const bool want = UnderGpu::ownDepthWanted.load();
        sOwnDepthOn.store(want);
        D3D12_CPU_DESCRIPTOR_HANDLE own{};
        uintptr_t ownRes = 0;
        if (want && sFrameTarget.load() && UnderGpu::ownDepthFor(self, reinterpret_cast<ID3D12Resource*>(sFrameTarget.load()), own, ownRes))
            h = own;
    }
    facts(self, [&](ListFacts& f) {
        f.depthClear = true;
        f.clearFlags |= static_cast<uint32_t>(flags);
    });
    sClearDs->getOriginal<&clearDepthStencilView>()(self, h, flags, depth, stencil, nr, r);
}
HRESULT __stdcall TrackerState::reset(ID3D12GraphicsCommandList* self, ID3D12CommandAllocator* alloc, ID3D12PipelineState* pso) {
    if (tChamsDepthList == self)
        tChamsDepthList = nullptr; // its chams depth has to be cleared again in the new recording
    if (tStencilList == self)
        tStencilList = nullptr; // a new recording: the reference starts over
    if (tCurList == self)
        tCurList = nullptr; // a new recording: no state is set until the first SetPipelineState
    facts(self, [](ListFacts& f) { f = ListFacts{}; }); // the list starts over
    return sReset->getOriginal<&reset>()(self, alloc, pso);
}
HRESULT __stdcall TrackerState::createGraphicsPipelineState(ID3D12Device* self, const D3D12_GRAPHICS_PIPELINE_STATE_DESC* d, REFIID riid, void** pp) {
    HRESULT hr = sCreatePso->getOriginal<&createGraphicsPipelineState>()(self, d, riid, pp);
    if (FAILED(hr) || !pp || !*pp)
        return hr;

    PsoInfo i;
    i.depth = d->DepthStencilState.DepthEnable;
    i.depthWrite = d->DepthStencilState.DepthWriteMask == D3D12_DEPTH_WRITE_MASK_ALL;
    i.stencil = d->DepthStencilState.StencilEnable;
    i.blend = d->BlendState.RenderTarget[0].BlendEnable;
    i.srcBlend = d->BlendState.RenderTarget[0].SrcBlend;
    i.dstBlend = d->BlendState.RenderTarget[0].DestBlend;
    i.nrt = static_cast<uint8_t>(d->NumRenderTargets);
    i.rt0 = d->RTVFormats[0];
    i.dsv = d->DSVFormat;
    i.vsSize = static_cast<uint32_t>(d->VS.BytecodeLength);
    i.psSize = static_cast<uint32_t>(d->PS.BytecodeLength);
    i.vsHash = Platform::Str::fnv1a(d->VS.pShaderBytecode, d->VS.BytecodeLength);
    i.psHash = Platform::Str::fnv1a(d->PS.pShaderBytecode, d->PS.BytecodeLength);
    i.role = MaterialIndex::roleOf(i.psHash);
    if (i.role == MatRole::Unknown)
        i.role = MaterialIndex::roleOf(i.vsHash);
    for (UINT e = 0; e < d->InputLayout.NumElements; ++e) {
        const auto& el = d->InputLayout.pInputElementDescs[e];
        i.layout += fmt::format("{}{}{}", e ? "," : "", el.SemanticName, el.SemanticIndex ? std::to_string(el.SemanticIndex) : "");
    }
    i.skinned = i.layout.find("BLENDINDICES") != std::string::npos;
    i.celLayout = i.layout == "POSITION,COLOR,TEXCOORD" || i.layout == "POSITION,COLOR";
    i.posUvLayout = i.layout == "POSITION,TEXCOORD";
    const uint32_t serial = sPsoSerial.fetch_add(1, std::memory_order_relaxed) + 1;
    i.serial = serial;

    const auto pso = reinterpret_cast<uintptr_t>(*pp);
    const MatRole role = i.role;
    ID3D12Device* noDevice = nullptr;
    sDevice.compare_exchange_strong(noDevice, self);

    {
        std::lock_guard<std::mutex> lk(sPsoMu);
        sPsos[pso] = std::move(i);
    }
    sPsoGeneration.fetch_add(1, std::memory_order_release); // after the table has the state: a thread that reads the new generation finds it
    {
        // Whatever was retained under this address described a state that has been freed (the allocator gave its address to this one): it must not outlive it, or the
        // next table build would make a twin of the dead state for whatever lives here now. A state that is retained below puts its own description back.
        std::lock_guard<std::mutex> lk(sRetainedMu);
        const auto old = sRetained.find(pso);
        if (old != sRetained.end()) {
            if (old->second.desc.pRootSignature)
                old->second.desc.pRootSignature->Release();
            sRetained.erase(old);
        }
    }

    // A twin's state was made by us: retaining it would classify as the game's role and nest another twin inside it.
    if (tCreatingTwin)
        return hr;

    switch (role) {
    case MatRole::Terrain:
    case MatRole::Entity:
    case MatRole::HeldItem:
    case MatRole::Clouds:
    case MatRole::Weather:
    case MatRole::Particle:
        break;
    default: {
        // A skinned model is kept whatever its shaders were classified as: a player's state may not be in the material index, and its marked draws need a twin.
        bool skinned = false;
        for (UINT e = 0; e < d->InputLayout.NumElements && !skinned; ++e)
            skinned = std::string_view(d->InputLayout.pInputElementDescs[e].SemanticName) == "BLENDINDICES";
        if (!skinned)
            return hr; // no twin is ever built for these; keeping them would only grow the map
        break;
    }
    }

    Retained r;
    r.role = role;
    r.serial = serial;
    r.desc = *d;

    // Every pointer in the desc points into the game's own storage, which may die with the call: own each blob and point the desc back at it.
    auto ownBytes = [](const void* data, SIZE_T size, std::vector<uint8_t>& owned) -> const void* {
        if (!data || !size)
            return nullptr;
        const auto* bytes = static_cast<const uint8_t*>(data);
        owned.assign(bytes, bytes + size);
        return owned.data();
    };
    r.desc.VS.pShaderBytecode = ownBytes(d->VS.pShaderBytecode, d->VS.BytecodeLength, r.vs);
    r.desc.VS.BytecodeLength = r.vs.size();
    r.desc.PS.pShaderBytecode = ownBytes(d->PS.pShaderBytecode, d->PS.BytecodeLength, r.ps);
    r.desc.PS.BytecodeLength = r.ps.size();
    r.desc.DS.pShaderBytecode = ownBytes(d->DS.pShaderBytecode, d->DS.BytecodeLength, r.ds);
    r.desc.DS.BytecodeLength = r.ds.size();
    r.desc.HS.pShaderBytecode = ownBytes(d->HS.pShaderBytecode, d->HS.BytecodeLength, r.hs);
    r.desc.HS.BytecodeLength = r.hs.size();
    r.desc.GS.pShaderBytecode = ownBytes(d->GS.pShaderBytecode, d->GS.BytecodeLength, r.gs);
    r.desc.GS.BytecodeLength = r.gs.size();
    r.desc.CachedPSO.pCachedBlob = ownBytes(d->CachedPSO.pCachedBlob, d->CachedPSO.CachedBlobSizeInBytes, r.cachedPso);
    r.desc.CachedPSO.CachedBlobSizeInBytes = r.cachedPso.size();

    const UINT elementCount = d->InputLayout.NumElements;
    if (elementCount && d->InputLayout.pInputElementDescs) {
        r.elements.assign(d->InputLayout.pInputElementDescs, d->InputLayout.pInputElementDescs + elementCount);
        r.semantics.reserve(elementCount);
        for (UINT e = 0; e < elementCount; ++e) {
            const char* name = d->InputLayout.pInputElementDescs[e].SemanticName;
            r.semantics.emplace_back(name ? name : "");
        }
        for (UINT e = 0; e < elementCount; ++e)
            r.elements[e].SemanticName = r.semantics[e].c_str();
        r.desc.InputLayout = {r.elements.data(), elementCount};
    } else {
        r.desc.InputLayout = {nullptr, 0};
    }

    const UINT soCount = d->StreamOutput.NumEntries;
    if (soCount && d->StreamOutput.pSODeclaration) {
        r.soEntries.assign(d->StreamOutput.pSODeclaration, d->StreamOutput.pSODeclaration + soCount);
        r.soSemantics.reserve(soCount);
        for (UINT e = 0; e < soCount; ++e) {
            const char* name = d->StreamOutput.pSODeclaration[e].SemanticName;
            r.soSemantics.emplace_back(name ? name : "");
        }
        for (UINT e = 0; e < soCount; ++e)
            r.soEntries[e].SemanticName = r.soSemantics[e].c_str();
        r.desc.StreamOutput.pSODeclaration = r.soEntries.data();
        r.desc.StreamOutput.NumEntries = soCount;
    } else {
        r.desc.StreamOutput.pSODeclaration = nullptr;
        r.desc.StreamOutput.NumEntries = 0;
    }

    const UINT strideCount = d->StreamOutput.NumStrides;
    if (strideCount && d->StreamOutput.pBufferStrides) {
        r.soStrides.assign(d->StreamOutput.pBufferStrides, d->StreamOutput.pBufferStrides + strideCount);
        r.desc.StreamOutput.pBufferStrides = r.soStrides.data();
        r.desc.StreamOutput.NumStrides = strideCount;
    } else {
        r.desc.StreamOutput.pBufferStrides = nullptr;
        r.desc.StreamOutput.NumStrides = 0;
    }

    // The root signature is the game's own object; the reference lets a twin outlive the game's pipeline states.
    if (d->pRootSignature)
        d->pRootSignature->AddRef();
    r.desc.pRootSignature = d->pRootSignature;

    {
        std::lock_guard<std::mutex> lk(sRetainedMu);
        auto it = sRetained.find(pso);
        if (it != sRetained.end()) {
            if (it->second.desc.pRootSignature)
                it->second.desc.pRootSignature->Release();
            it->second = std::move(r);
        } else {
            sRetained.emplace(pso, std::move(r));
        }
    }
    LceRenderer::onStateCreated(pso); // a no-op unless LCE is on and has built its table
    ChamsRenderer::onStateCreated(pso); // the same for the chams twins
    return hr;
}

void TrackerState::forgetRetained() {
    std::lock_guard<std::mutex> lk(sRetainedMu);
    for (auto& entry : sRetained)
        if (entry.second.desc.pRootSignature)
            entry.second.desc.pRootSignature->Release();
    sRetained.clear();
}

// ---- queue -----------------------------------------------------------------------------------------------------------
// The game's own ExecuteCommandLists, for UnderUI to submit the game's lists in pieces and its own list between them.
void TrackerState::runExecute(ID3D12CommandQueue* q, UINT n, ID3D12CommandList* const* lists) {
    sExecute->getOriginal<&executeCommandLists>()(q, n, lists);
}
void __stdcall TrackerState::executeCommandLists(ID3D12CommandQueue* self, UINT n, ID3D12CommandList* const* lists) {
    Render::UnderUI::execute(self, n, lists, &runExecute); // submits the lists (in pieces when a layer is on) and follows their resource states
}

// ---- device: which resource a render target / depth view handle stands for -------------------------------------------
void __stdcall TrackerState::createRenderTargetView(ID3D12Device* self, ID3D12Resource* res, const D3D12_RENDER_TARGET_VIEW_DESC* desc, D3D12_CPU_DESCRIPTOR_HANDLE h) {
    {
        std::lock_guard<std::mutex> lk(sViewMu);
        sViews[h.ptr] = View{reinterpret_cast<uintptr_t>(res), desc ? desc->Format : DXGI_FORMAT_UNKNOWN};
    }
    sCreateRtv->getOriginal<&createRenderTargetView>()(self, res, desc, h);
}
void __stdcall TrackerState::createDepthStencilView(ID3D12Device* self, ID3D12Resource* res, const D3D12_DEPTH_STENCIL_VIEW_DESC* desc, D3D12_CPU_DESCRIPTOR_HANDLE h) {
    {
        std::lock_guard<std::mutex> lk(sViewMu);
        sViews[h.ptr] = View{reinterpret_cast<uintptr_t>(res), desc ? desc->Format : DXGI_FORMAT_UNKNOWN};
    }
    sCreateDsv->getOriginal<&createDepthStencilView>()(self, res, desc, h);
}
bool TrackerState::isViewHeap(D3D12_DESCRIPTOR_HEAP_TYPE t) {
    return t == D3D12_DESCRIPTOR_HEAP_TYPE_RTV || t == D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
}
void TrackerState::copyView(UINT64 dst, UINT64 src) {
    std::lock_guard<std::mutex> lk(sViewMu);
    auto it = sViews.find(src);
    if (it != sViews.end())
        sViews[dst] = it->second;
    else
        sViews.erase(dst);
}
void __stdcall TrackerState::copyDescriptorsSimple(ID3D12Device* self, UINT n, D3D12_CPU_DESCRIPTOR_HANDLE dst, D3D12_CPU_DESCRIPTOR_HANDLE src, D3D12_DESCRIPTOR_HEAP_TYPE type) {
    if (isViewHeap(type)) {
        UINT inc = self->GetDescriptorHandleIncrementSize(type);
        for (UINT i = 0; i < n; ++i)
            copyView(dst.ptr + static_cast<UINT64>(i) * inc, src.ptr + static_cast<UINT64>(i) * inc);
    }
    sCopyDescSimple->getOriginal<&copyDescriptorsSimple>()(self, n, dst, src, type);
}
void __stdcall TrackerState::copyDescriptors(ID3D12Device* self, UINT nd, const D3D12_CPU_DESCRIPTOR_HANDLE* ds, const UINT* dsz, UINT ns, const D3D12_CPU_DESCRIPTOR_HANDLE* ss, const UINT* ssz, D3D12_DESCRIPTOR_HEAP_TYPE type) {
    if (isViewHeap(type)) {
        UINT inc = self->GetDescriptorHandleIncrementSize(type);
        UINT di = 0, doff = 0, si = 0, soff = 0;
        while (di < nd && si < ns) {
            UINT dn = dsz ? dsz[di] : 1;
            UINT sn = ssz ? ssz[si] : 1;
            copyView(ds[di].ptr + static_cast<UINT64>(doff) * inc, ss[si].ptr + static_cast<UINT64>(soff) * inc);
            if (++doff == dn) { ++di; doff = 0; }
            if (++soff == sn) { ++si; soff = 0; }
        }
    }
    sCopyDesc->getOriginal<&copyDescriptors>()(self, nd, ds, dsz, ns, ss, ssz, type);
}


void CommandListTracker::init() {
    // the material index must exist before the first pipeline state is created after the hooks, or every role comes back unknown
    MaterialIndex::load();
    ID3D12Device* dev = nullptr;
    BS_CHECK_HR(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&dev)));
    D3D12_COMMAND_QUEUE_DESC qd{};
    qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    ID3D12CommandQueue* q = nullptr;
    BS_CHECK_HR(dev->CreateCommandQueue(&qd, IID_PPV_ARGS(&q)));
    ID3D12CommandAllocator* a = nullptr;
    BS_CHECK_HR(dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&a)));
    ID3D12GraphicsCommandList* l = nullptr;
    BS_CHECK_HR(dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, a, nullptr, IID_PPV_ARGS(&l)));
    void** dv = *reinterpret_cast<void***>(dev);
    void** qv = *reinterpret_cast<void***>(q);
    void** lv = *reinterpret_cast<void***>(l);
    TrackerState::sDevVt = dv;
    TrackerState::sListVt = lv;
    std::vector<VtableHook*> pending;
    auto make = [&pending](const char* name, void** vt, int slot, void* fn) {
        auto hook = std::make_unique<VtableHook>(name, vt, static_cast<size_t>(slot), fn, false); // not swapped in until every pointer below is stored
        pending.push_back(hook.get());
        return hook;
    };
    // Slot numbers counted against d3d12.h (IUnknown 3, ID3D12Object 4, ID3D12DeviceChild 1, ID3D12CommandList 1).
    TrackerState::sDraw = make("CommandList::DrawInstanced", lv, 12, &TrackerState::drawInstanced);
    TrackerState::sDrawIdx = make("CommandList::DrawIndexedInstanced", lv, 13, &TrackerState::drawIndexedInstanced);
    TrackerState::sPso = make("CommandList::SetPipelineState", lv, 25, &TrackerState::setPipelineState);
    TrackerState::sBarrier = make("CommandList::ResourceBarrier", lv, 26, &TrackerState::resourceBarrier);
    TrackerState::sOmRt = make("CommandList::OMSetRenderTargets", lv, 46, &TrackerState::omSetRenderTargets);
    TrackerState::sStencilRef = make("CommandList::OMSetStencilRef", lv, 24, &TrackerState::omSetStencilRef);
    TrackerState::sClearDs = make("CommandList::ClearDepthStencilView", lv, 47, &TrackerState::clearDepthStencilView);
    TrackerState::sClearRt = make("CommandList::ClearRenderTargetView", lv, 48, &TrackerState::clearRenderTargetView);
    TrackerState::sReset = make("CommandList::Reset", lv, 10, &TrackerState::reset);
    TrackerState::sScissor = make("CommandList::RSSetScissorRects", lv, 22, &TrackerState::rsSetScissorRects);
    TrackerState::sExecute = make("CommandQueue::ExecuteCommandLists", qv, 10, &TrackerState::executeCommandLists);
    TrackerState::sCreatePso = make("Device::CreateGraphicsPipelineState", dv, 10, &TrackerState::createGraphicsPipelineState);
    TrackerState::sCreateRtv = make("Device::CreateRenderTargetView", dv, 20, &TrackerState::createRenderTargetView);
    TrackerState::sCreateDsv = make("Device::CreateDepthStencilView", dv, 21, &TrackerState::createDepthStencilView);
    TrackerState::sCopyDescSimple = make("Device::CopyDescriptorsSimple", dv, 24, &TrackerState::copyDescriptorsSimple);
    TrackerState::sCopyDesc = make("Device::CopyDescriptors", dv, 23, &TrackerState::copyDescriptors);
    for (VtableHook* h : pending) // the game's threads call these shared vtables the moment a slot is swapped: every detour finds its hook stored by now
        h->install();
    l->Release();
    a->Release();
    q->Release();
    dev->Release();
}

// The swapchain was resized: the depth view we learned and the buffer we drew into belong to the old one.
void CommandListTracker::forgetOwnDepth() {
    TrackerState::sOwnDepthOn.store(false);
    TrackerState::sSwapDepthHandle.store(0);
    TrackerState::forgetSwapHandles();
}

void CommandListTracker::shutdown() {
    Render::UnderUI::shutdown();
    TrackerState::forgetRetained();
    for (auto* d : {&TrackerState::sDraw, &TrackerState::sDrawIdx, &TrackerState::sPso, &TrackerState::sBarrier, &TrackerState::sOmRt, &TrackerState::sStencilRef, &TrackerState::sClearRt, &TrackerState::sClearDs, &TrackerState::sReset, &TrackerState::sScissor, &TrackerState::sExecute, &TrackerState::sCreateRtv, &TrackerState::sCreateDsv, &TrackerState::sCopyDescSimple, &TrackerState::sCopyDesc, &TrackerState::sCreatePso})
        d->reset();
}
