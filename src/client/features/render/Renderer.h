#pragma once

struct IDXGISwapChain;
struct ID3D12CommandQueue;
struct ID3D12CommandList;
struct ImDrawList;

namespace Render {



// Owns everything of ours that touches the game's swapchain: the D3D12 device and queue it uses, ImGui, and the per-frame draw (OverlayBackend, FullscreenFx and the passes
// on them). One mutex, because the game can resize and present from different threads; nothing else in the client needs a lock.
struct Renderer {
    static void frame(IDXGISwapChain* sc);        // Present detour: draw our overlay
    static void beginResize(IDXGISwapChain* sc, UINT w, UINT h);      // ResizeBuffers detours: release before the game resizes
    static void endResize();
    static bool resizing();                       // a resize is in flight: leave the buffers alone
    static void shutdown();                       // eject: release everything incl. the device
    static bool ready();                          // set up against the swapchain: the ImGui overlay can draw
    static const char* status();                  // short runtime health state for diagnostics
    // Mid-frame, on the present thread, with the game's lists up to the layer already submitted: builds this frame's ImGui frame
    // if it is not built yet and draws its BACKGROUND draw list (and the item in hand) into the swapchain buffer `target` (a D3D12 resource), so it lands
    // under everything the game draws after this point. The foreground list and the windows still draw at Present.
    // A draw list of ours that goes under the game's ACTORS, not just under its UI (the UnderActors layer: the world drawn, the entities not yet): what is drawn
    // there is covered by the actors in front of it, with the model's own silhouette. Rebuilt every frame (empty at the start of the frame's GuiRenderEvent); when the
    // game's frame has no such layer it is drawn at Present with the rest. Same ImGui frame as the background list.
    static ImDrawList* underActors();
    // The boot screen's own list: drawn last, over the held picture (see ScreenShock), which hides every other list outside the opening. Empty at the start of each frame.
    static ImDrawList* splashList();
    static bool backgroundWanted();  // the background list had something in it in the last few frames (one frame behind, like underActorsWanted)
    static bool underActorsWanted(); // the list had something in it in the last few frames: the game's frame is cut for it (decided before the frame is built, so one frame behind)
    static bool underActorsPass(uintptr_t target, ID3D12CommandQueue* queue, void (*run)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*));
    static bool underUiPass(uintptr_t target, ID3D12CommandQueue* queue, void (*run)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*));
};

} // namespace Render
