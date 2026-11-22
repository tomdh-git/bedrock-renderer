#include "client/features/render/tracker/TrackerState.h"
#include "client/features/render/underui/UnderUI.h"
#include "client/features/hooks/hooks/render/ActorRenderDispatcherHook.h"
#include "client/core/diagnostics/Profiler.h"

// Which render target each descriptor handle stands for, what each pipeline state was created with, and what every command list did (ListFacts):
// the command list, queue and device methods the game's renderer calls are detoured once at startup (TrackerHooks.cpp). Views the game created
// before the DLL was injected are unknown until a resize or a graphics change rebuilds them.

std::mutex TrackerState::sPsoMu;
std::unordered_map<uintptr_t, TrackerState::PsoInfo> TrackerState::sPsos;
std::mutex TrackerState::sViewMu;
std::unordered_map<uintptr_t, TrackerState::View> TrackerState::sViews;
void** TrackerState::sDevVt = nullptr;
void** TrackerState::sListVt = nullptr;
std::mutex TrackerState::sFactsMu;
std::unordered_map<uintptr_t, ListFacts> TrackerState::sFacts;
std::atomic<uintptr_t> TrackerState::sBackBuffers[8];
std::atomic<uintptr_t> TrackerState::sFrameTarget {0};
std::atomic<uintptr_t> TrackerState::sSwapHandle {0};
std::atomic<uintptr_t> TrackerState::sSwapHandles[8];
bool TrackerState::isSwapHandle(uintptr_t handle) {
    if (!handle)
        return false;
    for (auto& h : sSwapHandles)
        if (h.load(std::memory_order_relaxed) == handle)
            return true;
    return false;
}
void TrackerState::rememberSwapHandle(uintptr_t handle) {
    if (isSwapHandle(handle))
        return;
    for (auto& h : sSwapHandles) {
        uintptr_t empty = 0;
        if (h.compare_exchange_strong(empty, handle))
            return;
    }
}
void TrackerState::forgetSwapHandles() {
    for (auto& h : sSwapHandles)
        h.store(0);
}
bool TrackerState::isBackBuffer(uintptr_t res) {
    if (!res)
        return false;
    for (auto& b : sBackBuffers)
        if (b.load(std::memory_order_relaxed) == res)
            return true;
    return false;
}
void TrackerState::noteDraw(void* list, uint32_t elements) {
    facts(list, [&](ListFacts& f) {
        if (++f.draws == 1) {
            f.firstElements = elements;
            f.quad = elements == 6 && (f.flatPso || !f.psoKnown); // a state we never saw created is not held against it
        }
        // The game's own sky bodies, from its materials (sky.material): the sun and moon blend source-alpha / one, the stars one-minus-
        // destination-colour / one, both depth tested without writing depth. A state we never saw created is told by its shape instead:
        // a single 6-element quad.
        f.totalElements += elements;
        f.maxElements = std::max(f.maxElements, elements);
        if (f.psoKnown && f.writePso)
            f.writeDraws++;
        if (f.actorPso)
            f.actorDraws++;
        if (f.psoKnown && f.blendPso)
            f.blendDraws++;
        if (f.psoKnown && f.flatBlendPso)
            f.flatBlendDraws++;
        if (f.psoKnown && f.blendPso && f.curRole == MatRole::Terrain)
            f.terrainBlendDraws++;
        if (!f.psoKnown)
            f.unknownDraws++;
        if (ActorRenderDispatcherHook::renderingLocalPlayer)
            f.playerDraws++; // recorded while the game renders the local player's model
        // What the draw is: by the material when the state's shaders are in one (exact); only a draw whose material is not known is told by the shape of what it
        // draws (the old way: a lone 6-element quad is maybe the sun or the moon).
        if (f.curRole != MatRole::Unknown) {
            f.roleDraws[static_cast<int>(f.curRole)]++;
        } else if (f.celPso) {
            f.bodyDraws++;
        } else if (!f.psoKnown && elements == 6) {
            f.sixDraws++;
        } else if (f.psoKnown && !f.writePso && elements == 6 && f.posUvPso) {
            f.cubeDraws++;
        }
    });
}
TrackerState::View TrackerState::viewOf(uintptr_t handle) {
    std::lock_guard<std::mutex> lk(sViewMu);
    auto it = sViews.find(handle);
    return it == sViews.end() ? View{} : it->second;
}



bool CommandListTracker::facts(ID3D12CommandList* list, ListFacts& out) {
    std::lock_guard<std::mutex> lk(TrackerState::sFactsMu);
    auto it = TrackerState::sFacts.find(reinterpret_cast<uintptr_t>(list));
    if (it == TrackerState::sFacts.end() || (!it->second.draws && !it->second.rtHandle && !it->second.depthClear && !it->second.colorClear && it->second.transitions.empty()))
        return false;
    std::swap(out, it->second); // a list is executed once per recording: the facts are handed over, not copied
    it->second.reset();         // and the node keeps the capacity it just received from out
    return true;
}

bool CommandListTracker::isSwapchain(const ListFacts& f) {
    return TrackerState::isBackBuffer(f.rtRes) || (f.rtHandle && (f.rtHandle == TrackerState::sSwapHandle.load() || TrackerState::isSwapHandle(f.rtHandle)));
}

uintptr_t CommandListTracker::frameTarget() {
    return TrackerState::sFrameTarget.load();
}

void CommandListTracker::onPresent(IDXGISwapChain* sc) {
    DXGI_SWAP_CHAIN_DESC desc{};
    sc->GetDesc(&desc);
    for (UINT i = 0; i < 8; ++i) { // the buffers the lists are told apart by
        uintptr_t res = 0;
        ID3D12Resource* b = nullptr;
        if (i < desc.BufferCount && SUCCEEDED(sc->GetBuffer(i, IID_PPV_ARGS(&b)))) {
            res = reinterpret_cast<uintptr_t>(b);
            b->Release();
        }
        TrackerState::sBackBuffers[i].store(res);
    }
    Profiler::frame();
    Render::UnderUI::poll(desc.OutputWindow);
}
