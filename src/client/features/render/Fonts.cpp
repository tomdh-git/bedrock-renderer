#include "client/features/render/Fonts.h"

ImFont* Fonts::ui(int mode) {
    ImFont* font = (mode == 2) ? lexend : (mode == 1) ? mojangles : regular;
    return font ? font : ImGui::GetFont();
}

ImFont* Fonts::uiBold(int mode) {
    ImFont* font = (mode == 2) ? lexend : (mode == 1) ? mojangles : bold;
    return font ? font : ImGui::GetFont();
}

ImFont* Fonts::global(int mode) {
    return uiBold(mode);
}
