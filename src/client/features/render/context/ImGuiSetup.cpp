#include "client/features/render/context/ImGuiSetup.h"
#include "client/platform/resources/Resources.h"
#include "client/features/render/Fonts.h"

static bool sReady = false;

bool ImGuiSetup::ready() {
    return sReady;
}

void ImGuiSetup::init(HWND wnd) {
    BS_CHECK(!sReady);
    ImGui::CreateContext();
    // Rounded corners and circles are tessellated finely (the default error of 0.3 px leaves visible facets on big radii).
    ImGui::GetStyle().CircleTessellationMaxError = 0.03f;
    // Embedded fonts (see Resources.cpp); the atlas must not own the static bytes.
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    ImFontConfig cfg{};
    cfg.FontDataOwnedByAtlas = false;
    // Every glyph advance on a whole pixel: with fractional advances a glyph's bitmap is drawn between two pixel columns and sampled bilinearly, which is the fuzz of small text.
    cfg.PixelSnapH = true;
    auto fontFrom = [&](const char* key, float px = 28.f) -> ImFont* {
        auto it = Platform::ResourceLoader::Resources.find(key);
        if (it == Platform::ResourceLoader::Resources.end() || it->second.size() == 0)
            return nullptr;
        return io.Fonts->AddFontFromMemoryTTF(it->second.data2(), (int)it->second.size(), px, &cfg);
    };
    Fonts::regular = fontFrom("product_sans");
    Fonts::bold = fontFrom("product_sans_bold");
    Fonts::mojangles = fontFrom("mojangles");
    Fonts::lexend = fontFrom("lexend");
    Fonts::icons = fontFrom("lucide_icons");
    cfg.PixelSnapH = false; // the Schwag watermark lays its own letters out (and bends them) by the exact advances
    Fonts::impact = fontFrom("impact", 52.f);
    if (!Fonts::regular) {
        io.Fonts->AddFontDefault();
        Logger::warn("[render] embedded fonts missing, using the default font");
    }
    ImGui_ImplWin32_Init(wnd);
    // OverlayBackend draws and makes the textures, and honours the vertex offsets
    io.BackendRendererName = "overlaybackend";
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset | ImGuiBackendFlags_RendererHasTextures;
    sReady = true;
}

void ImGuiSetup::shutdown() {
    if (!sReady)
        return;
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    sReady = false;
}
