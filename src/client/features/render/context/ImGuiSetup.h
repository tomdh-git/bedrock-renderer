#pragma once

// ImGui context + embedded fonts + the Win32 backend (drawing is OverlayBackend's). The context is destroyed and rebuilt with every swapchain resize.
struct ImGuiSetup {
    static void init(HWND wnd);
    static void shutdown();
    static bool ready();
};
