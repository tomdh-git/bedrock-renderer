#pragma once

// The embedded faces, published once by ImGuiSetup and shared by the UI and the HUD.
struct Fonts {
    static inline ImFont* regular = nullptr;
    static inline ImFont* bold = nullptr;
    static inline ImFont* mojangles = nullptr;
    static inline ImFont* lexend = nullptr;
    static inline ImFont* impact = nullptr;
    static inline ImFont* icons = nullptr; // Lucide glyphs (Icons.h)
    static ImFont* ui(int mode);
    static ImFont* uiBold(int mode);
    static ImFont* global(int mode);
};
