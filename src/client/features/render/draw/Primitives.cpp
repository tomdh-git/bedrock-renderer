#include "client/features/render/draw/Primitives.h"
#include "client/features/render/post/GlowFx.h"
#include "client/core/util/Math.h"

void RenderUtils::text(ImDrawList* d, ImVec2 pos, const std::string& text, ImU32 col, float size, bool shadow, float shadowOffset) {
    if (text.empty() || size < 1.f)
        return;
    pos = ImVec2(floorf(pos.x), floorf(pos.y));
    ImFont* font = ImGui::GetFont();
    if (shadow)
        d->AddText(font, size, ImVec2(pos.x + shadowOffset, pos.y + shadowOffset), ColorUtils::scaleRgb(col, 0.25f), text.c_str());
    d->AddText(font, size, pos, col, text.c_str());
}
ImVec2 RenderUtils::textSize(const std::string& text, float size) {
    return ImGui::GetFont()->CalcTextSizeA(size, FLT_MAX, -1, ColorUtils::stripCodes(text).c_str());
}
bool RenderUtils::inRect(ImVec2 p, ImVec2 mn, ImVec2 mx) {
    return p.x >= mn.x && p.y >= mn.y && p.x < mx.x && p.y < mx.y;
}
float RenderUtils::textWidth(ImFont* font, float size, const char* text) { return font->CalcTextSizeA(size, FLT_MAX, -1, text).x; }
float RenderUtils::textHeight(ImFont* font, float size) { return font->CalcTextSizeA(size, FLT_MAX, -1, "Ag").y; }

// The font's true line box: ascent + descent (Descent is negative: 1.213em for Product Sans) — CalcTextSizeA only reports the em box.
float RenderUtils::textLineHeight(ImFont* font, float size) {
    const ImFontBaked* b = font->GetFontBaked(size);
    return b ? b->Ascent - b->Descent : textHeight(font, size);
}

void RenderUtils::shadowedText(ImDrawList* d, ImFont* font, float size, ImVec2 pos, ImU32 col, ImU32 shadow, float offset, const char* text) {
    d->AddText(font, size, ImVec2(pos.x + offset, pos.y + offset), shadow, text);
    d->AddText(font, size, pos, col, text);
}

void RenderUtils::fadeVertices(ImDrawList* d, int firstVertex, float y0, float y1, float fade, bool top, bool bottom) {
    if (fade < 0.5f || (!top && !bottom))
        return;
    for (int i = firstVertex; i < d->VtxBuffer.Size; i++) {
        ImDrawVert& v = d->VtxBuffer[i];
        float k = 1.f;
        if (top)
            k *= UiMath::smooth01((v.pos.y - y0) / fade);
        if (bottom)
            k *= UiMath::smooth01((y1 - v.pos.y) / fade);
        const ImU32 a = static_cast<ImU32>(static_cast<float>(v.col >> IM_COL32_A_SHIFT) * k);
        v.col = (v.col & 0x00FFFFFF) | (a << IM_COL32_A_SHIFT);
    }
}

void RenderUtils::fadedRect(ImDrawList* d, ImVec2 mn, ImVec2 mx, ImU32 col, float fade, bool top, bool bottom) {
    const float fh = (std::min)(fade, (mx.y - mn.y) * 0.5f);
    const bool ft = top && fh > 0.5f, fb = bottom && fh > 0.5f;
    if (!ft && !fb) {
        d->AddRectFilled(mn, mx, col);
        return;
    }
    const ImU32 none = col & 0x00FFFFFF;
    const float ya = ft ? mn.y + fh : mn.y, yb = fb ? mx.y - fh : mx.y;
    if (ft)
        d->AddRectFilledMultiColor(mn, ImVec2(mx.x, ya), none, none, col, col);
    if (yb > ya)
        d->AddRectFilled(ImVec2(mn.x, ya), ImVec2(mx.x, yb), col);
    if (fb)
        d->AddRectFilledMultiColor(ImVec2(mn.x, yb), mx, col, col, none, none);
}

void RenderUtils::strokeQuad(ImVec2 a, ImVec2 b, float half, ImVec2 out[4]) {
    float xA = a.x < b.x ? a.x : b.x, xB = a.x < b.x ? b.x : a.x;
    float yA = a.y < b.y ? a.y : b.y, yB = a.y < b.y ? b.y : a.y;
    if (a.x == b.x) {
        const float x = roundf(a.x);
        xA = x - half;
        xB = x + half;
        yA = roundf(yA) - half;
        yB = roundf(yB) + half;
    } else if (a.y == b.y) {
        const float yy = roundf(a.y);
        yA = yy - half;
        yB = yy + half;
        xA = roundf(xA) - half;
        xB = roundf(xB) + half;
    } else {
        xA -= half; xB += half; yA -= half; yB += half;
    }
    out[0] = ImVec2(xA, yA);
    out[1] = ImVec2(xB, yA);
    out[2] = ImVec2(xB, yB);
    out[3] = ImVec2(xA, yB);
}

// Soft shadow: real blur kernel, not layered rects.
void RenderUtils::softShadow(ImDrawList*, ImVec2 mn, ImVec2 mx, float rounding, float alpha) {
    GlowFx::shadow(mn, mx, rounding, alpha, 45.f); // blurred with every other shadow at the end of the frame (GlowFx)
}
