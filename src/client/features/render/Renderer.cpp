#include "client/features/render/Renderer.h"
#include "client/core/event/events/ui/GuiRenderEvent.h"
#include "client/core/event/events/render/OverlayResetEvent.h"
#include "client/core/runtime/UiState.h"
#include "sdk/mc/deps/bgfx/BgfxContext.h"
#include "client/features/render/post/GlowFx.h"
#include "client/features/render/post/ScreenShock.h"
#include "client/features/render/underui/UnderUI.h"
#include "client/core/diagnostics/Profiler.h"
#include "client/features/render/context/ImGuiSetup.h"
#include "client/features/render/backend/OverlayBackend.h"
#include "client/features/render/post/FullscreenFx.h"
#include "client/platform/filesystem/Files.h"
#include "client/platform/window/Window.h"
#include "client/core/runtime/Runtime.h"
#include "client/features/render/draw/GifAnim.h"
#include "client/features/render/draw/Blur.h"
#include "client/core/event/events/game/TickEvent.h"
#include "client/features/hooks/hooks/input/wnd_proc/InputQueue.h"
#include "client/features/hooks/hooks/input/wnd_proc/WndProcHook.h"
#include "sdk/csgo/game/client/c_baseviewmodel/ViewModelRenderer.h"
#include "client/features/render/geekbar/GeekbarFeed.h"

namespace Render {



enum class RendererState : uint8_t { Waiting, Ready, Resizing, Suspended, Recovering, Failed, Stopped };

struct RendererContext {
    std::mutex frameVsTeardown;
    std::atomic<uint32_t> resizeCount{0};
    std::atomic<RendererState> state{RendererState::Waiting};

    ID3D12Device* device = nullptr;
    ID3D12CommandQueue* queue = nullptr; // the game's queue; it outlives our device, no reference taken
    HWND window = nullptr;
    IDXGISwapChain* swapchain = nullptr; // identity only: a different chain means our buffers are stale

    bool frameBuilt = false;
    bool backgroundDrawnUnder = false;
    bool eventDrawnUnder = false;
    ImDrawList* underActors = nullptr;
    ImDrawList* splash = nullptr;
    bool underActorsDone = false;
    std::atomic<int> underActorsRecent{0};
    std::atomic<int> backgroundRecent{0}; // frames left in which the background list is taken to have content (the game's frame is cut for it only then)
    DWORD presentThread = 0;
};
static RendererContext sRenderer; // one owner for device, swapchain, ImGui lists, and their teardown state
static thread_local bool tInRenderer = false; // inside Renderer code: the game's ExecuteCommandLists we hook is called by our own flushes too

static bool createDevice(IDXGISwapChain* sc) {
    BS_CHECK_HR(sc->GetDevice(IID_PPV_ARGS(&sRenderer.device)));
    sRenderer.queue = BgfxContext::get()->getCommandQueue();
    BS_CHECK(sRenderer.queue);
    return true;
}

static void releaseDevice() {
    if (sRenderer.device) {
        sRenderer.device->Release();
        sRenderer.device = nullptr;
    }
    sRenderer.queue = nullptr;
}

// Everything tied to the current swapchain's buffers. The device stays.
static void releaseSwapchainSide() {
    // The subclass comes off before the swapchain is touched (DXGI subclasses
    // the window itself during fullscreen); setup puts it back.
    WndProcHook::uninstall();
    UiState::reset(); // no ImGui state survives this
    InputQueue::clear();
    ViewHandsRenderer::shutdown();
    GifAnim::clear(); // its texture belongs to the device generation that made it
    Eventing::trigger<OverlayResetEvent>();
    BlurUtils::shutdown();
    ScreenShock::shutdown();
    GlowFx::shutdown(); // its draw lists belong to the ImGui context destroyed below
    if (sRenderer.underActors) { // so does the list under the actors (the context asserts that none is left)
        IM_DELETE(sRenderer.underActors);
        sRenderer.underActors = nullptr;
    }
    if (sRenderer.splash) {
        IM_DELETE(sRenderer.splash);
        sRenderer.splash = nullptr;
    }
    FullscreenFx::shutdown();
    OverlayBackend::shutdown(); // waits for the GPU: the game's ResizeBuffers needs every use of its buffers finished
    ImGuiSetup::shutdown();
    sRenderer.frameBuilt = false;
    sRenderer.backgroundDrawnUnder = false;
    sRenderer.eventDrawnUnder = false;
    sRenderer.window = nullptr;
    sRenderer.swapchain = nullptr;
}

static bool setup(IDXGISwapChain* sc) {
    if (!sRenderer.device && !createDevice(sc)) {
        sRenderer.state.store(RendererState::Failed, std::memory_order_release);
        return false;
    }
    DXGI_SWAP_CHAIN_DESC d{};
    BS_CHECK_HR(sc->GetDesc(&d));
    sRenderer.window = d.OutputWindow;
    BS_CHECK(sRenderer.window);
    ImGuiSetup::init(sRenderer.window);
    OverlayBackend::init(sc, sRenderer.queue);
    FullscreenFx::init();
    GlowFx::init();
    WndProcHook::install(sRenderer.window); // after ImGui owns the window
    sRenderer.swapchain = sc;
    sRenderer.state.store(RendererState::Ready, std::memory_order_release);
    Logger::info("[render] ready {}x{}, {} buffers", d.BufferDesc.Width, d.BufferDesc.Height, OverlayBackend::bufferCount());
    return true;
}

// Everything an ImGui frame is made of: input, the client's UI and the modules' draw calls, ending in finished draw lists. Built once per
// frame, at the first place that needs it: the game's frame reaches the background layer before Present does.
// A minimised window has no client area: there is nothing to lay a UI out in or draw into (the game still presents).
static bool minimized() {
    if (!sRenderer.window)
        return false;
    const SIZE client = Platform::Window::clientSize(sRenderer.window);
    return client.cx <= 0 || client.cy <= 0;
}

static void buildFrame() {
    BS_CHECK(!sRenderer.frameBuilt);
    BS_PROFILE("render", "build the UI frame");
    Eventing::trigger<TickEvent>();
    WndProcHook::pump(); // window-thread input, replayed on this thread
    ImGui_ImplWin32_NewFrame();
    {
        // The swapchain's buffers are not always the window's client size (fullscreen, resizing, a scaled display): the UI is laid out in
        // client pixels (where the mouse is) and drawn to the buffer, so every pass that maps one onto the other needs this ratio.
        DXGI_SWAP_CHAIN_DESC scd{};
        BS_CHECK_HR(sRenderer.swapchain->GetDesc(&scd));
        ImGuiIO& io = ImGui::GetIO();
        BS_CHECK(io.DisplaySize.x > 0.f && io.DisplaySize.y > 0.f);
        io.DisplayFramebufferScale = ImVec2(scd.BufferDesc.Width / io.DisplaySize.x, scd.BufferDesc.Height / io.DisplaySize.y);
    }
    {
        BS_PROFILE("render", "ImGui::NewFrame");
        ImGui::NewFrame();
        GlowFx::beginFrame();
        if (!sRenderer.underActors)
            sRenderer.underActors = IM_NEW(ImDrawList)(ImGui::GetDrawListSharedData());
        sRenderer.underActors->_ResetForNewFrame();
        sRenderer.underActors->PushTexture(ImGui::GetIO().Fonts->TexRef);
        sRenderer.underActors->PushClipRectFullScreen();
        if (!sRenderer.splash)
            sRenderer.splash = IM_NEW(ImDrawList)(ImGui::GetDrawListSharedData());
        sRenderer.splash->_ResetForNewFrame();
        sRenderer.splash->PushTexture(ImGui::GetIO().Fonts->TexRef);
        sRenderer.splash->PushClipRectFullScreen();
    }
    {
        BS_PROFILE("render", "GuiRenderEvent listeners");
        Eventing::trigger<GuiRenderEvent>();
    }
    {
        BS_PROFILE("render", "ImGui::Render");
        ImGui::Render();
        const bool hasUnderActorContent = sRenderer.underActors->VtxBuffer.Size > 0 || GlowFx::hasUnderActors();
        sRenderer.underActorsRecent.store(hasUnderActorContent ? 12 : std::max(0, sRenderer.underActorsRecent.load() - 1), std::memory_order_relaxed);
        sRenderer.backgroundRecent.store(ImGui::GetBackgroundDrawList()->VtxBuffer.Size > 0 ? 12 : std::max(0, sRenderer.backgroundRecent.load() - 1), std::memory_order_relaxed);
        if (sRenderer.underActors->VtxBuffer.Size > 0) { // drawn by the under-actors pass, or with the rest at Present
            ImDrawData* all = ImGui::GetDrawData();
            all->CmdLists.push_back(sRenderer.underActors);
            all->CmdListsCount = all->CmdLists.Size;
            all->TotalVtxCount += sRenderer.underActors->VtxBuffer.Size;
            all->TotalIdxCount += sRenderer.underActors->IdxBuffer.Size;
        }
    }
    if (Profiler::collecting()) { // geometry sizes are counters, never milliseconds
        static const Profiler::Id fg = Profiler::valueId("UI geometry", "foreground vertices", "k vertices"), bg = Profiler::valueId("UI geometry", "background vertices", "k vertices"),
                                  total = Profiler::valueId("UI geometry", "all vertices", "k vertices"), idx = Profiler::valueId("UI geometry", "all indices", "k indices");
        Profiler::addValue(fg, ImGui::GetForegroundDrawList()->VtxBuffer.Size / 1000.0);
        Profiler::addValue(bg, ImGui::GetBackgroundDrawList()->VtxBuffer.Size / 1000.0);
        Profiler::addValue(total, ImGui::GetDrawData()->TotalVtxCount / 1000.0);
        Profiler::addValue(idx, ImGui::GetDrawData()->TotalIdxCount / 1000.0);
    }
    sRenderer.frameBuilt = true;
    sRenderer.backgroundDrawnUnder = false;
    sRenderer.eventDrawnUnder = false;
    sRenderer.underActorsDone = false;
}

// A draw data holding only some of the frame's lists: the background list, the list under the actors, or the rest (the windows, the foreground list, and the other
// two when they were not drawn earlier in the game's frame).
enum class Lists { Background, UnderActors, Rest };
static ImDrawData subset(ImDrawData* all, Lists which) {
    ImDrawData part = *all;
    part.CmdLists.resize(0);
    part.TotalVtxCount = part.TotalIdxCount = 0;
    ImDrawList* bg = ImGui::GetBackgroundDrawList();
    for (ImDrawList* list : all->CmdLists) {
        const bool isBg = list == bg, isUnder = list == sRenderer.underActors;
        const bool take = which == Lists::Background ? isBg : which == Lists::UnderActors ? isUnder : ((!isBg || !sRenderer.backgroundDrawnUnder) && (!isUnder || !sRenderer.underActorsDone));
        if (!take)
            continue;
        part.CmdLists.push_back(list);
        part.TotalVtxCount += list->VtxBuffer.Size;
        part.TotalIdxCount += list->IdxBuffer.Size;
    }
    part.CmdListsCount = part.CmdLists.Size;
    return part;
}

static void directExecute(ID3D12CommandQueue* q, UINT n, ID3D12CommandList* const* lists) {
    q->ExecuteCommandLists(n, lists);
}

// The command list a frame is: one pass after another onto the back buffer `index` (the game left it in the PRESENT state), ending
// submitted to the game's queue. Pure recording — everything it reads is passed in.
static void recordFrame(UINT index, UINT w, UINT h, ImDrawData* data) {
    BS_PROFILE("render", "draw the UI");
    OverlayBackend::Cmd cmd = OverlayBackend::begin("Present list: glow, blur, UI");
    D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_PRESENT;
    ScreenShock::capture(cmd, index, state, w, h); // the boot screen holds the game's picture as it is now, before anything of ours is drawn on it
    const float open = UiState::openAmount.load(std::memory_order_acquire);
    if (open > 0.01f) { // the gaussian backdrop behind the Click GUI
        BS_PROFILE("render", "backdrop blur");
        BlurUtils::paint(cmd, index, state, w, h, open);
    }
    OverlayBackend::stamp(cmd, "backdrop blur");
    { // the shadows and the glow of the UI, under it
        BS_PROFILE("render", "glow and shadow");
        GlowFx::render(cmd, index, state, w, h);
    }
    OverlayBackend::stamp(cmd, "glow and shadow");
    if (!sRenderer.eventDrawnUnder) { // the item in hand, if it was not drawn already under the game's UI
        BS_PROFILE("render", "render event (item in hand)");
        ViewHandsRenderer::render(cmd, index, state, w, h);
    }
    OverlayBackend::stamp(cmd, "item in hand");
    if (UiState::cosOpen && UiState::cosPreviewRect.z > UiState::cosPreviewRect.x && UiState::cosPreviewRect.w > UiState::cosPreviewRect.y) {
        ViewHandsRenderer::renderPreview(cmd, UiState::cosSpin, UiState::cosPitch, UiState::cosZoom, UiState::cosTab == 1);
        OverlayBackend::stamp(cmd, "cosmetics preview");
    }
    OverlayBackend::moveBuffer(cmd, index, state, D3D12_RESOURCE_STATE_RENDER_TARGET);
    OverlayBackend::drawImGui(cmd, data, OverlayBackend::bufferRtv(index), OverlayBackend::backFormat(), data->DisplaySize.x * data->FramebufferScale.x, data->DisplaySize.y * data->FramebufferScale.y);
    OverlayBackend::stamp(cmd, "UI lists (ImGui)");
    if (ScreenShock::active()) { // the held picture back over everything the opening has not reached, then the boot screen itself
        ScreenShock::composite(cmd, index, state, w, h);
        if (sRenderer.splash && sRenderer.splash->VtxBuffer.Size > 0) {
            ImDrawData* all = ImGui::GetDrawData();
            ImDrawData part; // its own, not a copy of the frame's (the copy would share, and free, the frame's list array)
            part.Valid = true;
            part.DisplayPos = all->DisplayPos;
            part.DisplaySize = all->DisplaySize;
            part.FramebufferScale = all->FramebufferScale;
            part.CmdLists.push_back(sRenderer.splash);
            part.CmdListsCount = 1;
            part.TotalVtxCount = sRenderer.splash->VtxBuffer.Size;
            part.TotalIdxCount = sRenderer.splash->IdxBuffer.Size;
            OverlayBackend::moveBuffer(cmd, index, state, D3D12_RESOURCE_STATE_RENDER_TARGET);
            OverlayBackend::drawImGui(cmd, &part, OverlayBackend::bufferRtv(index), OverlayBackend::backFormat(), part.DisplaySize.x * part.FramebufferScale.x, part.DisplaySize.y * part.FramebufferScale.y);
        }
        OverlayBackend::stamp(cmd, "boot screen");
    }
    OverlayBackend::moveBuffer(cmd, index, state, D3D12_RESOURCE_STATE_PRESENT);
    OverlayBackend::submit(cmd, sRenderer.queue, &directExecute);
}

// The native renderer's frame: the UI onto the back buffer the game just finished (it is in the PRESENT state).
static void drawFrame(IDXGISwapChain* sc) {
    const UINT index = static_cast<IDXGISwapChain3*>(sc)->GetCurrentBackBufferIndex();
    if (!sRenderer.frameBuilt)
        buildFrame();
    ImDrawData* all = ImGui::GetDrawData();
    ImDrawData rest;
    ImDrawData* data = all;
    if (sRenderer.backgroundDrawnUnder || sRenderer.underActorsDone) { // the background list and the one under the actors are already in the picture
        rest = subset(all, Lists::Rest);
        data = &rest;
    }
    DXGI_SWAP_CHAIN_DESC desc{};
    sc->GetDesc(&desc);
    recordFrame(index, desc.BufferDesc.Width, desc.BufferDesc.Height, data);
    sRenderer.frameBuilt = false;
    sRenderer.backgroundDrawnUnder = false;
    sRenderer.eventDrawnUnder = false;
    sRenderer.underActorsDone = false;
}

void Renderer::frame(IDXGISwapChain* sc) {
    if (!sc)
        return;
    // This detour is entered for each DXGI Present; once our D3D12 overlay is ready it is only
    // drawn on its owning swapchain. Do the cheap identity check before locking or querying the OS.
    if (!Runtime::eject && sRenderer.swapchain && sc != sRenderer.swapchain)
        return;
    std::lock_guard<std::mutex> lock(sRenderer.frameVsTeardown);
    tInRenderer = true;
    struct Leave { ~Leave() { tInRenderer = false; } } leave;
    sRenderer.presentThread = GetCurrentThreadId();
    if (Runtime::eject) {
        if (Runtime::gameSideDone && !Runtime::renderSideDone) {
            releaseSwapchainSide();
            releaseDevice();
            Runtime::renderSideDone = true;
        }
        return;
    }
    if (!sRenderer.swapchain) { // setting up: only a Direct3D 12 swapchain is the game's (another overlay's, or a different API's, presents through the same detour)
        ID3D12Device* probe = nullptr;
        const HRESULT hr = sc->GetDevice(IID_PPV_ARGS(&probe));
        if (probe)
            probe->Release();
        if (FAILED(hr)) {
            static bool sLogged = false;
            if (!sLogged) {
                sLogged = true;
                Logger::warn("[render] a swapchain {:#x} that is not Direct3D 12 presented (hr {:#x}): left alone", reinterpret_cast<uintptr_t>(sc), static_cast<uint32_t>(hr));
            }
            return;
        }
    }
    // A resize that began while we waited for the lock: leave the buffers alone.
    if (sRenderer.resizeCount.load(std::memory_order_acquire) != 0) {
        sRenderer.state.store(RendererState::Resizing, std::memory_order_release);
        sRenderer.frameBuilt = false; // a frame built for the buffers that are going away
        sRenderer.backgroundDrawnUnder = false;
        return;
    }
    if (!sRenderer.swapchain && minimized()) {
        sRenderer.state.store(RendererState::Suspended, std::memory_order_release);
        return;
    }
    if (sRenderer.swapchain && minimized()) {
        sRenderer.state.store(RendererState::Suspended, std::memory_order_release);
        sRenderer.frameBuilt = false;
        sRenderer.backgroundDrawnUnder = false;
        return;
    }
    // A different swapchain: our buffers belong to the old one. MinHook patches
    // code, so the detours still cover it; only the cached state is stale.
    if (sRenderer.device && FAILED(sRenderer.device->GetDeviceRemovedReason())) {
        Logger::error("[render] device removed ({:#x}), rebuilding", static_cast<uint32_t>(sRenderer.device->GetDeviceRemovedReason()));
        sRenderer.state.store(RendererState::Recovering, std::memory_order_release);
        releaseSwapchainSide();
        releaseDevice();
        return;
    }
    if (!sRenderer.swapchain && !setup(sc))
        return;
    sRenderer.state.store(RendererState::Ready, std::memory_order_release);
    drawFrame(sc);
}

void Renderer::beginResize(IDXGISwapChain* sc, UINT w, UINT h) {
    if (sRenderer.resizeCount.fetch_add(1) != 0)
        return;
    sRenderer.state.store(RendererState::Resizing, std::memory_order_release);
    std::lock_guard<std::mutex> lock(sRenderer.frameVsTeardown);
    releaseSwapchainSide();
    UnderUI::dropTargets();
    releaseDevice(); // everything goes, the next Present builds a fresh device
}

void Renderer::endResize() {
    if (sRenderer.resizeCount.fetch_sub(1) == 1)
        sRenderer.state.store(RendererState::Waiting, std::memory_order_release);
}

bool Renderer::resizing() {
    return sRenderer.resizeCount.load(std::memory_order_acquire) != 0;
}

void Renderer::shutdown() {
    std::lock_guard<std::mutex> lock(sRenderer.frameVsTeardown);
    WndProcHook::uninstall();
    releaseSwapchainSide();
    releaseDevice();
    sRenderer.state.store(RendererState::Stopped, std::memory_order_release);
}

bool Renderer::ready() {
    return sRenderer.state.load(std::memory_order_acquire) == RendererState::Ready && !Runtime::eject;
}

const char* Renderer::status() {
    switch (sRenderer.state.load(std::memory_order_acquire)) {
    case RendererState::Waiting: return "waiting for swapchain";
    case RendererState::Ready: return "ready";
    case RendererState::Resizing: return "swapchain resize in progress";
    case RendererState::Suspended: return "window minimized";
    case RendererState::Recovering: return "device removed; rebuilding on next frame";
    case RendererState::Failed: return "device or swapchain setup failed";
    case RendererState::Stopped: return "renderer stopped";
    }
    return "unknown renderer state";
}

// The pass may run only on the present thread (our lists and the ImGui frame belong to it) and not while the swapchain is being torn down or resized.
static bool underUiAllowed() {
    if (Runtime::eject || sRenderer.resizeCount.load(std::memory_order_acquire) != 0 || !sRenderer.swapchain || !ImGuiSetup::ready() || minimized())
        return false;
    if (GetCurrentThreadId() == sRenderer.presentThread)
        return true;
    static bool sLogged = false;
    if (!sLogged) {
        sLogged = true;
        Logger::warn("[render] the game submits its frame on thread {} but presents on {}: the background layer stays over the UI", GetCurrentThreadId(), sRenderer.presentThread);
    }
    return false;
}

// Recorded and submitted by OverlayBackend into the game's frame: the buffer is in the render target state here.
static bool recordUnderUi(uintptr_t target, ID3D12CommandQueue* queue, void (*run)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*)) {
    if (!OverlayBackend::ready())
        return false;
    if (!sRenderer.frameBuilt)
        buildFrame();
    ImDrawData bgNative = subset(ImGui::GetDrawData(), Lists::Background);
    // nothing on the background list and no item in hand to draw: the pass would be a list for nothing; Present draws what there is
    if (bgNative.CmdLists.Size == 0 && !ViewHandsRenderer::drawing.load(std::memory_order_acquire) && !GeekbarFeed::drawing.load(std::memory_order_acquire))
        return false;
    const int index = OverlayBackend::bufferIndexOf(target);
    if (index < 0)
        return false;
    const D3D12_RESOURCE_DESC bd = OverlayBackend::buffer(static_cast<UINT>(index))->GetDesc();
    OverlayBackend::Cmd cmd = OverlayBackend::begin("under-UI list: background, item in hand");
    D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_RENDER_TARGET;
    if (bgNative.CmdLists.Size > 0) {
        BS_PROFILE("render", "draw the background list (native d3d12)");
        OverlayBackend::drawImGui(cmd, &bgNative, OverlayBackend::bufferRtv(static_cast<UINT>(index)), OverlayBackend::backFormat(), bgNative.DisplaySize.x * bgNative.FramebufferScale.x,
            bgNative.DisplaySize.y * bgNative.FramebufferScale.y);
        sRenderer.backgroundDrawnUnder = true;
    }
    {
        BS_PROFILE("render", "render event (item in hand)");
        ViewHandsRenderer::render(cmd, static_cast<UINT>(index), state, static_cast<UINT>(bd.Width), bd.Height);
    }
    OverlayBackend::moveBuffer(cmd, static_cast<UINT>(index), state, D3D12_RESOURCE_STATE_RENDER_TARGET); // left as the game had it
    OverlayBackend::submit(cmd, queue, run);
    sRenderer.eventDrawnUnder = true;
    return true;
}

bool Renderer::underUiPass(uintptr_t target, ID3D12CommandQueue* queue, void (*run)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*)) {
    if (tInRenderer)
        return false;
    BS_PROFILE("render", "under-UI pass (background list, item in hand)");
    std::unique_lock<std::mutex> lock(sRenderer.frameVsTeardown, std::defer_lock);
    {
        BS_PROFILE("render", "wait renderer frame lock");
        lock.lock();
    }
    tInRenderer = true;
    struct Leave { ~Leave() { tInRenderer = false; } } leave;
    return underUiAllowed() && recordUnderUi(target, queue, run);
}

ImDrawList* Renderer::underActors() {
    return sRenderer.underActors;
}

ImDrawList* Renderer::splashList() {
    return sRenderer.splash;
}

bool Renderer::backgroundWanted() {
    return sRenderer.backgroundRecent.load(std::memory_order_relaxed) > 0;
}

bool Renderer::underActorsWanted() {
    return sRenderer.underActorsRecent.load(std::memory_order_relaxed) > 0;
}

bool Renderer::underActorsPass(uintptr_t target, ID3D12CommandQueue* queue, void (*run)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*)) {
    if (tInRenderer)
        return false;
    BS_PROFILE("render", "under-actors pass (list under the entities)");
    std::unique_lock<std::mutex> lock(sRenderer.frameVsTeardown, std::defer_lock);
    {
        BS_PROFILE("render", "wait renderer frame lock");
        lock.lock();
    }
    tInRenderer = true;
    struct Leave { ~Leave() { tInRenderer = false; } } leave;
    if (!underUiAllowed() || !OverlayBackend::ready() || sRenderer.underActorsDone)
        return false;
    if (!sRenderer.frameBuilt)
        buildFrame();
    ImDrawData part = subset(ImGui::GetDrawData(), Lists::UnderActors);
    if (part.CmdLists.Size == 0 && !GlowFx::hasUnderActors())
        return false;
    const int index = OverlayBackend::bufferIndexOf(target);
    if (index < 0)
        return false;
    const D3D12_RESOURCE_DESC bd = OverlayBackend::buffer(static_cast<UINT>(index))->GetDesc();
    OverlayBackend::Cmd cmd = OverlayBackend::begin("under-actors list");
    D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_RENDER_TARGET;
    GlowFx::renderUnderActors(cmd, static_cast<UINT>(index), state, static_cast<UINT>(bd.Width), bd.Height);
    if (part.CmdLists.Size > 0)
        OverlayBackend::drawImGui(cmd, &part, OverlayBackend::bufferRtv(static_cast<UINT>(index)), OverlayBackend::backFormat(), part.DisplaySize.x * part.FramebufferScale.x,
            part.DisplaySize.y * part.FramebufferScale.y);
    OverlayBackend::submit(cmd, queue, run);
    sRenderer.underActorsDone = true;
    return true;
}

} // namespace Render
