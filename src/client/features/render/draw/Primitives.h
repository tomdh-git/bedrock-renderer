#pragma once

// Drawing helpers that do more than one ImDrawList call. Plain rectangles, lines and circles are drawn with the
// ImDrawList directly (d->AddRectFilled ...), not through here.
struct RenderUtils {
    // Text, pixel-snapped, with an optional drop shadow (a quarter-brightness copy offset by shadowOffset).
    static void text(ImDrawList* d, ImVec2 pos, const std::string& text, ImU32 col, float size, bool shadow = false, float shadowOffset = 1.f);
    static ImVec2 textSize(const std::string& text, float size); // colour codes are not counted

    // Blurred drop shadow behind a rounded rectangle (convex-poly blur kernel, alpha scales the shadow).
    static void softShadow(ImDrawList* d, ImVec2 mn, ImVec2 mx, float rounding, float alpha);

    static bool inRect(ImVec2 point, ImVec2 mn, ImVec2 mx);

    // Text measured and drawn with an explicit font (the default-font versions above are for the Click GUI's own text).
    static float textWidth(ImFont* font, float size, const char* text);
    static float textHeight(ImFont* font, float size); // the line: a tall and a hanging letter
    static float textLineHeight(ImFont* font, float size); // the font's true line box: ascent + descent (descenders included)
    // A drop copy of the text first (`shadow` colour, `offset` pixels down and right), then the text.
    static void shadowedText(ImDrawList* d, ImFont* font, float size, ImVec2 pos, ImU32 col, ImU32 shadow, float offset, const char* text);

    // Alpha-fades the vertices added to the list since `firstVertex` towards the top and/or bottom edge of [y0, y1], over `fade` pixels.
    static void fadeVertices(ImDrawList* d, int firstVertex, float y0, float y1, float fade, bool top, bool bottom);
    // A filled rectangle whose top and/or bottom edge fades out to transparent over `fade` pixels.
    static void fadedRect(ImDrawList* d, ImVec2 mn, ImVec2 mx, ImU32 col, float fade, bool top, bool bottom);
    // The pixel-snapped rectangle of a stroke from a to b, `half` pixels either side (a diagonal is not snapped).
    static void strokeQuad(ImVec2 a, ImVec2 b, float half, ImVec2 out[4]);
};
