#pragma once
#if __has_include("imgui.h")
#include "imgui.h"
#else
#include "external/imgui/imgui.h"
#endif
#if __has_include("imgui_internal.h")
#include "imgui_internal.h"
#else
#include "external/imgui/imgui_internal.h"
#endif

struct SchwagRender {

// Seamless 128x128 diamond glitter tile, built once at first use (jittered voronoi facets: white / icy cyan, dark creases, a few hot
// specks). Procedural so the DLL carries code, not a 64 KB pixel table; ABGR packed.
static const uint32_t* diamondTile() {
    static uint32_t tile[128 * 128];
    static bool built = false;
    if (built)
        return tile;
    constexpr int N = 128, G = 22;
    uint32_t seed = 7u;
    const auto rnd = [&]() {
        seed = seed * 1664525u + 1013904223u;
        return static_cast<float>(seed >> 8) / 16777216.f;
    };
    struct Cell { float x, y, bright, tint, kind; };
    static Cell cells[G][G];
    for (int gy = 0; gy < G; ++gy)
        for (int gx = 0; gx < G; ++gx) {
            Cell& c = cells[gy][gx];
            c.x = static_cast<float>(gx) + rnd();
            c.y = static_cast<float>(gy) + rnd();
            c.bright = rnd();
            c.tint = rnd();
            c.kind = rnd();
        }
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x) {
            const float px = static_cast<float>(x) / N * G, py = static_cast<float>(y) / N * G;
            const int cx = static_cast<int>(px), cy = static_cast<int>(py);
            float d1 = 1e9f, d2 = 1e9f;
            const Cell* nearest = nullptr;
            for (int j = -1; j <= 1; ++j)
                for (int i = -1; i <= 1; ++i) {
                    const int gx = ((cx + i) % G + G) % G, gy = ((cy + j) % G + G) % G;
                    const Cell& c = cells[gy][gx];
                    const float d = std::hypot(px - (c.x + static_cast<float>(cx + i - gx)), py - (c.y + static_cast<float>(cy + j - gy)));
                    if (d < d1) { d2 = d1; d1 = d; nearest = &c; }
                    else if (d < d2) d2 = d;
                }
            const float edge = std::min(1.f, (d2 - d1) / 0.22f); // 0 on a crease, 1 inside a facet
            float lum = 0.74f + 0.26f * nearest->bright;
            if (nearest->kind < 0.14f)
                lum *= 0.8f; // a few shadowed facets
            const float cyan = nearest->tint * 0.6f;
            const float shade = 0.68f + 0.32f * edge;
            float r = 255.f * lum * (1.f - cyan * 0.42f) * shade;
            float g = 255.f * lum * (1.f - cyan * 0.14f) * shade;
            float b = 255.f * lum * (0.75f + 0.25f * edge);
            if (nearest->kind > 0.93f && edge > 0.5f)
                r = g = b = 255.f;
            tile[y * N + x] = 0xFF000000u | (static_cast<uint32_t>(std::min(255.f, b)) << 16) | (static_cast<uint32_t>(std::min(255.f, g)) << 8) | static_cast<uint32_t>(std::min(255.f, r));
        }
    built = true;
    return tile;
}

// Bilinear sampling of the diamond tile
static ImU32 sampleDiamondTileBilinear(float u, float v) {
    const uint32_t* kDiamondTile = diamondTile();
    u = u - floorf(u);
    v = v - floorf(v);
    const float fx = u * 127.0f;
    const float fy = v * 127.0f;
    const int x0 = static_cast<int>(fx);
    const int y0 = static_cast<int>(fy);
    const int x1 = (x0 + 1) & 127;
    const int y1 = (y0 + 1) & 127;
    const float tx = fx - static_cast<float>(x0);
    const float ty = fy - static_cast<float>(y0);

    const uint32_t c00 = kDiamondTile[y0 * 128 + x0];
    const uint32_t c10 = kDiamondTile[y0 * 128 + x1];
    const uint32_t c01 = kDiamondTile[y1 * 128 + x0];
    const uint32_t c11 = kDiamondTile[y1 * 128 + x1];

    const auto unpackR = [](uint32_t c) -> float { return static_cast<float>(c & 0xFF); };
    const auto unpackG = [](uint32_t c) -> float { return static_cast<float>((c >> 8) & 0xFF); };
    const auto unpackB = [](uint32_t c) -> float { return static_cast<float>((c >> 16) & 0xFF); };

    const float r0 = unpackR(c00) * (1.f - tx) + unpackR(c10) * tx;
    const float r1 = unpackR(c01) * (1.f - tx) + unpackR(c11) * tx;
    const float r = r0 * (1.f - ty) + r1 * ty;

    const float g0 = unpackG(c00) * (1.f - tx) + unpackG(c10) * tx;
    const float g1 = unpackG(c01) * (1.f - tx) + unpackG(c11) * tx;
    const float g = g0 * (1.f - ty) + g1 * ty;

    const float b0 = unpackB(c00) * (1.f - tx) + unpackB(c10) * tx;
    const float b1 = unpackB(c01) * (1.f - tx) + unpackB(c11) * tx;
    const float b = b0 * (1.f - ty) + b1 * ty;

    return IM_COL32(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b), 255);
}

// Sparkle instance definition for rendering and dynamic point-light reflections
struct ActiveSparkle {
    ImVec2 pos;
    float intensity; // 0.0 .. 1.0 pulse factor
    float size;      // ray radius
    float angle;
};

// Inward collegiate keystone slant and side barrel curve:
// 1. Upright stems lean towards center line (x=0) by angle proportional to x.
// 2. Outer side edges pinch/curve inward at the corners (collegiate shield effect).
static float applyKeystoneAndSideCurve(float x, float y, float totalW, float yMin, float yMax, float s) {
    if (totalW <= 1.0f) return x;
    const float normX = x / (totalW * 0.5f); // -1.0 .. +1.0
    const float glyphH = (yMax > yMin) ? (yMax - yMin) : 48.0f;
    const float yNorm = std::clamp((y - yMin) / glyphH, 0.0f, 1.0f); // 0.0 (top) .. 1.0 (bottom)

    // Subtle collegiate lean towards center (preserves straight upright edges and sharp 90-degree corners):
    const float lean = normX * (1.0f - yNorm) * (1.8f * s);
    return x - lean;
}

// Warps a point for the TOP word ("BLUEY"):
// Arched upward along a circular arc matching the reference apex rise
static ImVec2 warpTopPoint(float x, float y, ImVec2 center, float radius, float totalW, float yMin, float yMax, float s) {
    const float adjX = applyKeystoneAndSideCurve(x, y, totalW, yMin, yMax, s);
    const float theta = adjX / radius;

    const float normX = totalW > 1.f ? (adjX / (totalW * 0.5f)) : 0.f;
    const float flare = 1.0f + 0.05f * (normX * normX); // slightly bigger on ends (~5%)
    const float flaredY = y * flare;

    const float r = radius - flaredY;
    return ImVec2(center.x + sinf(theta) * r, center.y + (radius - cosf(theta) * r));
}

// Warps a point for the BOTTOM word ("SENSE"):
static ImVec2 warpBottomPoint(float x, float y, ImVec2 center, float totalW, float yMin, float yMax, float s) {
    const float adjX = applyKeystoneAndSideCurve(x, y, totalW, yMin, yMax, s);
    const float normX = totalW > 1.f ? (adjX / (totalW * 0.5f)) : 0.f;
    const float flare = 1.0f + 0.07f * (normX * normX); // slightly bigger on ends (~7%)

    // Anchor to bottom baseline (y == yMax stays at baseline):
    const float newY = yMax + (y - yMax) * flare;
    return ImVec2(center.x + adjX, center.y + newY);
}

static ImVec2 warpPointDispatch(float x, float y, ImVec2 center, float radius, bool isTop, float totalW, float yMin, float yMax, float s) {
    if (isTop) {
        return warpTopPoint(x, y, center, radius, totalW, yMin, yMax, s);
    } else {
        return warpBottomPoint(x, y, center, totalW, yMin, yMax, s);
    }
}

// Computes dynamic point-light illumination from nearby sparkles onto a vertex position
static void applySparkleLighting(ImVec2 p, const std::vector<ActiveSparkle>& sparkles, float s, float& r, float& g, float& b, bool isGold = false) {
    const float rLight = 45.0f * s; // reach of light
    const float rLightSq = rLight * rLight;

    for (const auto& sp : sparkles) {
        if (sp.intensity <= 0.05f) continue;
        const float dx = p.x - sp.pos.x;
        const float dy = p.y - sp.pos.y;
        const float distSq = dx * dx + dy * dy;
        if (distSq < rLightSq) {
            const float dist = sqrtf(distSq);
            // Core blowout: inside 9.0px, wash directly to brilliant pure white!
            if (dist < 9.0f * s) {
                const float coreT = (1.0f - dist / (9.0f * s)) * sp.intensity;
                r = r * (1.0f - coreT) + 255.0f * coreT;
                g = g * (1.0f - coreT) + 255.0f * coreT;
                b = b * (1.0f - coreT) + 255.0f * coreT;
            } else {
                const float t = (1.0f - (dist - 9.0f * s) / (36.0f * s)) * sp.intensity;
                const float boost = t * t * 175.0f;
                if (isGold) {
                    // Gold catches warm golden-white specular flare
                    r = std::min(255.0f, r + boost);
                    g = std::min(255.0f, g + boost * 0.95f);
                    b = std::min(255.0f, b + boost * 0.50f);
                } else {
                    // Diamonds catch pure crystalline icy-white/cyan flare (never yellow!)
                    r = std::min(255.0f, r + boost * 0.85f);
                    g = std::min(255.0f, g + boost * 0.96f);
                    b = std::min(255.0f, b + boost * 1.08f);
                }
            }
        }
    }
}

struct BentGlyph {
    const ImFontGlyph* glyph;
    char ch;
    float x0, x1;
    float y0, y1;
    float u0, u1;
    float v0, v1;
};

// Measures text layout, builds glyph infos with outer letters a couple sizes bigger
static std::vector<BentGlyph> layoutBentText(ImFont* font, float size, const char* text, float letterSpacing, float& outTotalWidth, float& outYMin, float& outYMax) {
    std::vector<BentGlyph> glyphs;
    if (!font || !text || !*text)
        return glyphs;

    ImFontBaked* baked = font->GetFontBaked(size);
    const float scale = (size >= 0.0f && baked->Size > 0.0f) ? (size / baked->Size) : 1.0f;
    const float scaleX = scale * 1.12f;
    const float scaleY = scale;

    const int numLetters = static_cast<int>(strlen(text));

    // First pass: measure total width with per-letter scale
    float totalAdvance = 0.f;
    int letterIdx = 0;
    for (const char* c = text; *c; ++c, ++letterIdx) {
        const ImFontGlyph* g = baked->FindGlyph(static_cast<ImWchar>(static_cast<unsigned char>(*c)));
        if (!g) continue;
        const float normPos = numLetters > 1 ? (static_cast<float>(letterIdx) / static_cast<float>(numLetters - 1) * 2.0f - 1.0f) : 0.f;
        const float letterScale = 1.0f + 0.07f * (normPos * normPos); // outer letters only slightly bigger (~7%)
        totalAdvance += g->AdvanceX * scaleX * letterScale + letterSpacing;
    }
    if (totalAdvance > letterSpacing)
        totalAdvance -= letterSpacing;

    outTotalWidth = totalAdvance;
    float curX = -totalAdvance * 0.5f;
    float yMin = 0.f, yMax = 0.f;

    letterIdx = 0;
    for (const char* c = text; *c; ++c, ++letterIdx) {
        const ImFontGlyph* g = baked->FindGlyph(static_cast<ImWchar>(static_cast<unsigned char>(*c)));
        if (!g) continue;

        const float normPos = numLetters > 1 ? (static_cast<float>(letterIdx) / static_cast<float>(numLetters - 1) * 2.0f - 1.0f) : 0.f;
        const float letterScale = 1.0f + 0.07f * (normPos * normPos);
        const float curScaleX = scaleX * letterScale;
        const float curScaleY = scaleY * letterScale;

        if (g->Visible) {
            BentGlyph bg;
            bg.glyph = g;
            bg.ch = *c;
            bg.x0 = curX + g->X0 * curScaleX;
            bg.x1 = curX + g->X1 * curScaleX;
            bg.y0 = g->Y0 * curScaleY;
            bg.y1 = g->Y1 * curScaleY;
            bg.u0 = g->U0;
            bg.u1 = g->U1;
            bg.v0 = g->V0;
            bg.v1 = g->V1;
            glyphs.push_back(bg);

            if (bg.y0 < yMin) yMin = bg.y0;
            if (bg.y1 > yMax) yMax = bg.y1;
        }
        curX += g->AdvanceX * curScaleX + letterSpacing;
    }

    outYMin = yMin;
    outYMax = yMax;
    return glyphs;
}

// Draws bent glyphs with solid color or vertical gradient
static void drawBentGlyphsFlat(ImDrawList* d, const std::vector<BentGlyph>& glyphs, ImVec2 center, float radius, bool isTop, float totalW,
                              float offsetX, float offsetY, ImU32 colTop, ImU32 colBottom, float yMin, float yMax, float s) {
    const int Nx = 2; // a glyph is ~40px wide on a 560px radius: two slices follow the arch
    const int Ny = 1;
    const float yRange = (yMax > yMin) ? (yMax - yMin) : 1.0f;

    const auto lerpCol = [&](float t) -> ImU32 {
        const int rA = (colTop >> IM_COL32_R_SHIFT) & 0xFF;
        const int gA = (colTop >> IM_COL32_G_SHIFT) & 0xFF;
        const int bA = (colTop >> IM_COL32_B_SHIFT) & 0xFF;
        const int aA = (colTop >> IM_COL32_A_SHIFT) & 0xFF;

        const int rB = (colBottom >> IM_COL32_R_SHIFT) & 0xFF;
        const int gB = (colBottom >> IM_COL32_G_SHIFT) & 0xFF;
        const int bB = (colBottom >> IM_COL32_B_SHIFT) & 0xFF;
        const int aB = (colBottom >> IM_COL32_A_SHIFT) & 0xFF;

        const int r = static_cast<int>(rA + t * (rB - rA));
        const int g = static_cast<int>(gA + t * (gB - gA));
        const int b = static_cast<int>(bA + t * (bB - bA));
        const int a = static_cast<int>(aA + t * (aB - aA));

        return IM_COL32(r, g, b, a);
    };

    const ImVec2 offsetCenter(center.x + offsetX, center.y + offsetY);

    for (const auto& bg : glyphs) {
        for (int i = 0; i < Nx; ++i) {
            const float tx0 = static_cast<float>(i) / static_cast<float>(Nx);
            const float tx1 = static_cast<float>(i + 1) / static_cast<float>(Nx);
            const float xa = bg.x0 + tx0 * (bg.x1 - bg.x0);
            const float xb = bg.x0 + tx1 * (bg.x1 - bg.x0);
            const float ua = bg.u0 + tx0 * (bg.u1 - bg.u0);
            const float ub = bg.u0 + tx1 * (bg.u1 - bg.u0);

            for (int j = 0; j < Ny; ++j) {
                const float ty0 = static_cast<float>(j) / static_cast<float>(Ny);
                const float ty1 = static_cast<float>(j + 1) / static_cast<float>(Ny);
                const float ya = bg.y0 + ty0 * (bg.y1 - bg.y0);
                const float yb = bg.y0 + ty1 * (bg.y1 - bg.y0);
                const float va = bg.v0 + ty0 * (bg.v1 - bg.v0);
                const float vb = bg.v0 + ty1 * (bg.v1 - bg.v0);

                const ImVec2 pTL = warpPointDispatch(xa, ya, offsetCenter, radius, isTop, totalW, yMin, yMax, s);
                const ImVec2 pTR = warpPointDispatch(xb, ya, offsetCenter, radius, isTop, totalW, yMin, yMax, s);
                const ImVec2 pBR = warpPointDispatch(xb, yb, offsetCenter, radius, isTop, totalW, yMin, yMax, s);
                const ImVec2 pBL = warpPointDispatch(xa, yb, offsetCenter, radius, isTop, totalW, yMin, yMax, s);

                const float tMid = std::clamp(((ya + yb) * 0.5f - yMin) / yRange, 0.0f, 1.0f);
                const ImU32 col = lerpCol(tMid);

                d->PrimReserve(6, 4);
                const ImDrawIdx idx = static_cast<ImDrawIdx>(d->_VtxCurrentIdx);
                d->PrimWriteIdx(idx);     d->PrimWriteIdx(idx + 1); d->PrimWriteIdx(idx + 2);
                d->PrimWriteIdx(idx);     d->PrimWriteIdx(idx + 2); d->PrimWriteIdx(idx + 3);

                d->PrimWriteVtx(pTL, ImVec2(ua, va), col);
                d->PrimWriteVtx(pTR, ImVec2(ub, va), col);
                d->PrimWriteVtx(pBR, ImVec2(ub, vb), col);
                d->PrimWriteVtx(pBL, ImVec2(ua, vb), col);
            }
        }
    }
}

// ---- the static part of the watermark, built once -------------------------------------------------------------------------------------------------------
// Everything about a vertex that does not change from frame to frame (where the bend puts it, which diamond facet it lies on, how the bevel lights it) is worked out
// when the layout is built; a frame only adds what moves: the light sweep, the sparkles, the position of the whole word (it slides in) and the alpha.
// The sweep is sin(x * 0.022 - y * 0.015 - 1.8 t): with the vertex's own phase P (relative to the word's centre) kept as sin P and cos P, the frame's value is
// sin(P + phi) = sin P cos(phi) + cos P sin(phi), phi being the word's phase minus 1.8 t: two sines a word instead of one a vertex.

struct GridVert {
    float x, y;       // relative to the word's centre
    float r, g, b;    // the colour before the sweep and the sparkles
    float sinP, cosP; // the sweep's phase at this vertex
};

static constexpr int kDiaNx = 20, kDiaNy = 20; // the diamond grid of a glyph
static constexpr int kBezNx = 4, kBezNy = 2;   // the gold bezel's
static constexpr int kRimNx = 2;              // the flat passes' (a glyph is ~40px wide on a 560px radius: two slices follow the arch)

struct WordCache {
    std::vector<GridVert> diamond;  // glyphs x (kDiaNx + 1) x (kDiaNy + 1)
    std::vector<GridVert> bezel[8]; // per offset of the 8-sample rim: glyphs x (kBezNx + 1) x (kBezNy + 1)
    std::vector<ImVec2> flat;       // glyphs x kRimNx x 4 corners, relative to the word's centre (the flat passes only differ by an offset)
};

static GridVert makeVert(ImVec2 rel, float r, float g, float b) {
    const float p = rel.x * 0.022f - rel.y * 0.015f;
    return GridVert{rel.x, rel.y, r, g, b, sinf(p), cosf(p)};
}

static void unpackTile(ImU32 c, float& r, float& g, float& b) {
    r = static_cast<float>(c & 0xFF);
    g = static_cast<float>((c >> 8) & 0xFF);
    b = static_cast<float>((c >> 16) & 0xFF);
}

static void buildWordCache(WordCache& wc, const std::vector<BentGlyph>& glyphs, float radius, bool isTop, float totalW, float yMin, float yMax, float s) {
    const float tileScale = 0.016f / s;
    const ImVec2 zero(0.f, 0.f);
    wc.diamond.clear();
    for (auto& v : wc.bezel)
        v.clear();
    wc.flat.clear();
    static const float kBox[8][2] = {{-1.f, -1.f}, {+1.f, -1.f}, {+1.f, +1.f}, {-1.f, +1.f}, {0.f, -1.f}, {+1.f, 0.f}, {0.f, +1.f}, {-1.f, 0.f}};
    const float bezelD = 1.3f * s; // a tight rim keeping the sharp corners of the Impact font
    for (const auto& bg : glyphs) {
        for (int j = 0; j <= kDiaNy; ++j)
            for (int i = 0; i <= kDiaNx; ++i) {
                const float x = bg.x0 + static_cast<float>(i) / kDiaNx * (bg.x1 - bg.x0);
                const float y = bg.y0 + static_cast<float>(j) / kDiaNy * (bg.y1 - bg.y0);
                const ImVec2 rel = warpPointDispatch(x, y, zero, radius, isTop, totalW, yMin, yMax, s);
                float r, g, b;
                unpackTile(sampleDiamondTileBilinear(rel.x * tileScale, rel.y * tileScale), r, g, b);
                wc.diamond.push_back(makeVert(rel, r, g, b));
            }
        for (int k = 0; k < 8; ++k) {
            const float ox = kBox[k][0] * bezelD, oy = kBox[k][1] * bezelD;
            const float dotL = -(kBox[k][0] * 0.6f + kBox[k][1] * 0.8f); // bevel lighting from the top left
            for (int j = 0; j <= kBezNy; ++j)
                for (int i = 0; i <= kBezNx; ++i) {
                    const float x = bg.x0 + static_cast<float>(i) / kBezNx * (bg.x1 - bg.x0);
                    const float y = bg.y0 + static_cast<float>(j) / kBezNy * (bg.y1 - bg.y0);
                    ImVec2 rel = warpPointDispatch(x, y, zero, radius, isTop, totalW, yMin, yMax, s);
                    rel.x += ox;
                    rel.y += oy;
                    // the gold follows the diamond texture
                    float dr, dg, db;
                    unpackTile(sampleDiamondTileBilinear(rel.x * tileScale, rel.y * tileScale), dr, dg, db);
                    const float lum = (dr * 0.299f + dg * 0.587f + db * 0.114f) / 255.0f;
                    float r = 222.0f + lum * 33.0f, g = 160.0f + lum * 85.0f, b = 25.0f + lum * 150.0f;
                    if (dotL > 0.0f) {
                        r = std::min(255.0f, r + dotL * 25.0f);
                        g = std::min(255.0f, g + dotL * 25.0f);
                        b = std::min(255.0f, b + dotL * 45.0f);
                    } else {
                        const float t = -dotL;
                        r = std::max(200.0f, r - t * 20.0f);
                        g = std::max(160.0f, g - t * 20.0f);
                        b = std::max(40.0f, b - t * 10.0f);
                    }
                    wc.bezel[k].push_back(makeVert(rel, r, g, b));
                }
        }
        for (int i = 0; i < kRimNx; ++i) {
            const float xa = bg.x0 + static_cast<float>(i) / kRimNx * (bg.x1 - bg.x0), xb = bg.x0 + static_cast<float>(i + 1) / kRimNx * (bg.x1 - bg.x0);
            wc.flat.push_back(warpPointDispatch(xa, bg.y0, zero, radius, isTop, totalW, yMin, yMax, s));
            wc.flat.push_back(warpPointDispatch(xb, bg.y0, zero, radius, isTop, totalW, yMin, yMax, s));
            wc.flat.push_back(warpPointDispatch(xb, bg.y1, zero, radius, isTop, totalW, yMin, yMax, s));
            wc.flat.push_back(warpPointDispatch(xa, bg.y1, zero, radius, isTop, totalW, yMin, yMax, s));
        }
    }
}

// The flat passes (the dark rim): the cached corners, moved by the word's centre and the pass's offset, in one colour.
static void drawFlatCached(ImDrawList* d, const std::vector<BentGlyph>& glyphs, const WordCache& wc, ImVec2 center, float offX, float offY, ImU32 col) {
    const ImVec2 o(center.x + offX, center.y + offY);
    size_t n = 0;
    for (const auto& bg : glyphs)
        for (int i = 0; i < kRimNx; ++i, n += 4) {
            const float ua = bg.u0 + static_cast<float>(i) / kRimNx * (bg.u1 - bg.u0), ub = bg.u0 + static_cast<float>(i + 1) / kRimNx * (bg.u1 - bg.u0);
            d->PrimReserve(6, 4);
            const ImDrawIdx idx = static_cast<ImDrawIdx>(d->_VtxCurrentIdx);
            d->PrimWriteIdx(idx);     d->PrimWriteIdx(idx + 1); d->PrimWriteIdx(idx + 2);
            d->PrimWriteIdx(idx);     d->PrimWriteIdx(idx + 2); d->PrimWriteIdx(idx + 3);
            d->PrimWriteVtx(ImVec2(o.x + wc.flat[n].x, o.y + wc.flat[n].y), ImVec2(ua, bg.v0), col);
            d->PrimWriteVtx(ImVec2(o.x + wc.flat[n + 1].x, o.y + wc.flat[n + 1].y), ImVec2(ub, bg.v0), col);
            d->PrimWriteVtx(ImVec2(o.x + wc.flat[n + 2].x, o.y + wc.flat[n + 2].y), ImVec2(ub, bg.v1), col);
            d->PrimWriteVtx(ImVec2(o.x + wc.flat[n + 3].x, o.y + wc.flat[n + 3].y), ImVec2(ua, bg.v1), col);
        }
}

// One indexed grid per glyph (a vertex shared by the quads around it), coloured per frame from the cached base, the sweep and the sparkles.
// gold: the bezel (caustics threshold 0.70, boost 35, gold sparkle flare) or the diamonds (0.72, 24, icy flare, only on bright blue facets).
static void drawGridCached(ImDrawList* d, const std::vector<BentGlyph>& glyphs, const std::vector<GridVert>& verts, int nx, int ny, ImVec2 center, float alpha, float time, float s,
                           bool gold, const std::vector<ActiveSparkle>& sparkles, int mode = 0) {
    // mode 0: as it is every frame; 1: the picture without the sweep and the sparkles (what is baked); 2: with the sweep at its strongest everywhere (the baked "boost" picture)
    const float phi = center.x * 0.022f - center.y * 0.015f - time * 1.8f;
    const float sp = sinf(phi), cp = cosf(phi);
    const int a8 = static_cast<int>(255 * alpha);
    size_t n = 0;
    for (const auto& bg : glyphs) {
        d->PrimReserve(nx * ny * 6, (nx + 1) * (ny + 1));
        const ImDrawIdx base = static_cast<ImDrawIdx>(d->_VtxCurrentIdx);
        for (int j = 0; j <= ny; ++j) {
            const float v = bg.v0 + static_cast<float>(j) / ny * (bg.v1 - bg.v0);
            for (int i = 0; i <= nx; ++i, ++n) {
                const GridVert& g = verts[n];
                float r = g.r, gg = g.g, b = g.b;
                const float sweep = mode == 1 ? -2.f : mode == 2 ? 1.f : g.sinP * cp + g.cosP * sp;
                if (gold) {
                    if (sweep > 0.70f) {
                        const float boost = (sweep - 0.70f) / 0.30f * 35.0f;
                        r = std::min(255.0f, r + boost);
                        gg = std::min(255.0f, gg + boost * 0.95f);
                        b = std::min(255.0f, b + boost * 0.85f);
                    }
                } else if (sweep > 0.72f && b > 80.f) {
                    const float boost = (sweep - 0.72f) / 0.28f * 24.0f;
                    r = std::min(255.f, r + boost * 0.80f);
                    gg = std::min(255.f, gg + boost * 0.95f);
                    b = std::min(255.f, b + boost * 1.15f);
                }
                const ImVec2 p(center.x + g.x, center.y + g.y);
                if (mode == 0 && !sparkles.empty())
                    applySparkleLighting(p, sparkles, s, r, gg, b, gold);
                d->PrimWriteVtx(p, ImVec2(bg.u0 + static_cast<float>(i) / nx * (bg.u1 - bg.u0), v),
                                IM_COL32(static_cast<int>(std::clamp(r, 0.f, 255.f)), static_cast<int>(std::clamp(gg, 0.f, 255.f)), static_cast<int>(std::clamp(b, 0.f, 255.f)), a8));
            }
        }
        for (int j = 0; j < ny; ++j)
            for (int i = 0; i < nx; ++i) {
                const ImDrawIdx i0 = static_cast<ImDrawIdx>(base + j * (nx + 1) + i);
                const ImDrawIdx i1 = static_cast<ImDrawIdx>(i0 + 1);
                const ImDrawIdx i2 = static_cast<ImDrawIdx>(i0 + (nx + 1) + 1);
                const ImDrawIdx i3 = static_cast<ImDrawIdx>(i0 + (nx + 1));
                d->PrimWriteIdx(i0); d->PrimWriteIdx(i1); d->PrimWriteIdx(i2);
                d->PrimWriteIdx(i0); d->PrimWriteIdx(i2); d->PrimWriteIdx(i3);
            }
    }
}

// Crisp diamond sparkle glint on main draw list d:
// Razor-sharp needle starburst rays, horizontal flare streak, and brilliant white hotspot!
// (Outer soft diffuse glow is handled cleanly by GlowFx!)
static void drawRealisticGlint(ImDrawList* d, ImVec2 pos, float size, float pulse, float angle, float alpha, float s) {
    if (pulse <= 0.05f || alpha <= 0.02f)
        return;

    const float effectiveAlpha = pulse * alpha;
    const float rayLen = size * pulse;
    const float rayHalfW = 0.85f * s * pulse;

    // Brilliant crystalline white with icy/silver shimmer (no yellow!)
    const ImU32 whiteCore = IM_COL32(255, 255, 255, static_cast<int>(255 * effectiveAlpha));
    const ImU32 silverMid = IM_COL32(245, 250, 255, static_cast<int>(235 * effectiveAlpha));
    const ImU32 iceFade   = IM_COL32(220, 240, 255, static_cast<int>(160 * effectiveAlpha));
    const ImU32 tipFade   = IM_COL32(205, 230, 255, 0);
    const ImVec2 uvWhite  = ImGui::GetIO().Fonts->TexUvWhitePixel;

    const auto drawRay = [&](float ang, float len, float w, ImU32 baseCol) {
        const float cosA = cosf(ang), sinA = sinf(ang);
        const ImVec2 dir(cosA, sinA);
        const ImVec2 norm(-sinA, cosA);

        const ImVec2 tip = ImVec2(pos.x + dir.x * len, pos.y + dir.y * len);
        const ImVec2 sideA = ImVec2(pos.x - norm.x * w, pos.y - norm.y * w);
        const ImVec2 sideB = ImVec2(pos.x + norm.x * w, pos.y + norm.y * w);

        d->PrimReserve(3, 3);
        const ImDrawIdx idx = static_cast<ImDrawIdx>(d->_VtxCurrentIdx);
        d->PrimWriteIdx(idx);
        d->PrimWriteIdx(idx + 1);
        d->PrimWriteIdx(idx + 2);

        d->PrimWriteVtx(sideA, uvWhite, baseCol);
        d->PrimWriteVtx(sideB, uvWhite, baseCol);
        d->PrimWriteVtx(tip,   uvWhite, tipFade);
    };

    // 4 cardinal primary needle spikes
    for (int k = 0; k < 4; ++k) {
        const float a = angle + static_cast<float>(k) * 1.5707963f;
        drawRay(a, rayLen * 1.35f, rayHalfW * 1.15f, whiteCore);
    }

    // 4 diagonal secondary needle rays
    for (int k = 0; k < 4; ++k) {
        const float a = angle + 0.785398f + static_cast<float>(k) * 1.5707963f;
        drawRay(a, rayLen * 0.72f, rayHalfW * 0.75f, silverMid);
    }

    // 16 fine tertiary starburst rays
    for (int k = 0; k < 16; ++k) {
        const float a = angle + 0.196349f + static_cast<float>(k) * 0.392699f;
        drawRay(a, rayLen * 0.38f, rayHalfW * 0.45f, iceFade);
    }

    // Anamorphic horizontal flare streak
    const float flareHalfW = 34.0f * s * pulse;
    const float flareHalfH = 1.2f * s * pulse;
    d->AddRectFilledMultiColor(
        ImVec2(pos.x - flareHalfW, pos.y - flareHalfH),
        ImVec2(pos.x, pos.y + flareHalfH),
        tipFade, whiteCore, whiteCore, tipFade
    );
    d->AddRectFilledMultiColor(
        ImVec2(pos.x, pos.y - flareHalfH),
        ImVec2(pos.x + flareHalfW, pos.y + flareHalfH),
        whiteCore, tipFade, tipFade, whiteCore
    );

    // Anamorphic vertical flare streak
    const float flareHalfW_v = 1.0f * s * pulse;
    const float flareHalfH_v = 22.0f * s * pulse;
    d->AddRectFilledMultiColor(
        ImVec2(pos.x - flareHalfW_v, pos.y - flareHalfH_v),
        ImVec2(pos.x + flareHalfW_v, pos.y),
        tipFade, tipFade, whiteCore, whiteCore
    );
    d->AddRectFilledMultiColor(
        ImVec2(pos.x - flareHalfW_v, pos.y),
        ImVec2(pos.x + flareHalfW_v, pos.y + flareHalfH_v),
        whiteCore, whiteCore, tipFade, tipFade
    );

    // Brilliant white center hotspot
    d->AddCircleFilled(pos, 2.8f * s * pulse, whiteCore, 16);
}

// The atlas is dynamic and is rebuilt with the ImGui context (every resize): a glyph's UVs are only good for the frame they were read in,
// so the cached layout keeps its geometry and takes the UVs fresh each frame.
static void refreshGlyphUVs(ImFont* font, float size, std::vector<BentGlyph>& glyphs) {
    ImFontBaked* baked = font->GetFontBaked(size);
    for (auto& bg : glyphs) {
        const ImFontGlyph* g = baked->FindGlyph(static_cast<ImWchar>(static_cast<unsigned char>(bg.ch)));
        bg.glyph = g;
        bg.u0 = g->U0; bg.u1 = g->U1;
        bg.v0 = g->V0; bg.v1 = g->V1;
    }
}

// ---- the baked watermark -----------------------------------------------------------------------------------------------------------------------------------
// The letters are a mesh of thousands of tiny vertex-coloured quads (the colour of a vertex is the diamond facet under it): building and drawing that every frame is
// what the watermark cost. What the picture looks like does not change, so it is drawn once, on the CPU, into three small textures of the watermark's own size:
//   base  the letters as they are without the light sweep and the sparkles;
//   boost the same with the sweep at its strongest (blended over the base by the sweep's strength, per cell of a coarse grid, it is the sweep);
//   white the letters' silhouette (blended over the base by a sparkle's reach, it is the sparkle's light).
// A frame then draws the base as one quad, the sweep as a few cells, and a sparkle as a handful of cells.

static inline bool gPerVertex = false; // draw the letters as the mesh of vertices instead of the baked pictures (tools/visualpreview/bakecheck.cpp compares the two)

struct SchwagBake {
    ImGuiContext* ctx = nullptr;
    ImTextureData *base = nullptr, *boost = nullptr, *white = nullptr;
    ImVec2 origin{0.f, 0.f}; // the pictures' top left, from the watermark's base point
    int w = 0, h = 0;
    bool valid() const { return base && boost && white; }
    // The backend makes a texture the frame after it is registered and gives it its handle then: a draw command that names one before that has no handle to draw with.
    bool ready() const { return valid() && base->TexID != ImTextureID_Invalid && boost->TexID != ImTextureID_Invalid && white->TexID != ImTextureID_Invalid; }
};

static float atlasAlpha(const ImTextureData* a, float u, float v) { // bilinear, as the GPU samples the font atlas
    const float fx = u * static_cast<float>(a->Width) - 0.5f, fy = v * static_cast<float>(a->Height) - 0.5f;
    const int x0 = static_cast<int>(std::floor(fx)), y0 = static_cast<int>(std::floor(fy));
    const float tx = fx - static_cast<float>(x0), ty = fy - static_cast<float>(y0);
    const auto at = [&](int x, int y) {
        x = std::clamp(x, 0, a->Width - 1);
        y = std::clamp(y, 0, a->Height - 1);
        const unsigned char* px = a->Pixels + static_cast<size_t>(x + y * a->Width) * static_cast<size_t>(a->BytesPerPixel);
        return static_cast<float>(a->BytesPerPixel == 1 ? px[0] : px[3]) / 255.f;
    };
    return (at(x0, y0) * (1.f - tx) + at(x0 + 1, y0) * tx) * (1.f - ty) + (at(x0, y0 + 1) * (1.f - tx) + at(x0 + 1, y0 + 1) * tx) * ty;
}

// The triangles of a draw list, blended over each other into premultiplied floats: what the GPU would have drawn (pixel centres, linear atlas sampling).
static void rasterizeList(const ImDrawList& l, const ImTextureData* atlas, ImVec2 origin, int w, int h, std::vector<float>& P) {
    for (int i = 0; i + 2 < l.IdxBuffer.Size; i += 3) {
        const ImDrawVert &va = l.VtxBuffer[l.IdxBuffer[i]], &vb = l.VtxBuffer[l.IdxBuffer[i + 1]], &vc = l.VtxBuffer[l.IdxBuffer[i + 2]];
        const float ax = va.pos.x - origin.x, ay = va.pos.y - origin.y, bx = vb.pos.x - origin.x, by = vb.pos.y - origin.y, cx = vc.pos.x - origin.x, cy = vc.pos.y - origin.y;
        const float area = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
        if (std::fabs(area) < 1e-8f)
            continue;
        const float inv = 1.f / area;
        const int x0 = std::max(0, static_cast<int>(std::floor(std::min({ax, bx, cx})))), x1 = std::min(w - 1, static_cast<int>(std::ceil(std::max({ax, bx, cx}))));
        const int y0 = std::max(0, static_cast<int>(std::floor(std::min({ay, by, cy})))), y1 = std::min(h - 1, static_cast<int>(std::ceil(std::max({ay, by, cy}))));
        for (int y = y0; y <= y1; ++y)
            for (int x = x0; x <= x1; ++x) {
                const float px = static_cast<float>(x) + 0.5f, py = static_cast<float>(y) + 0.5f;
                const float w0 = ((bx - px) * (cy - py) - (by - py) * (cx - px)) * inv, w1 = ((cx - px) * (ay - py) - (cy - py) * (ax - px)) * inv, w2 = 1.f - w0 - w1;
                if (w0 < 0.f || w1 < 0.f || w2 < 0.f)
                    continue;
                const float u = va.uv.x * w0 + vb.uv.x * w1 + vc.uv.x * w2, v = va.uv.y * w0 + vb.uv.y * w1 + vc.uv.y * w2;
                const auto chan = [&](int shift) {
                    return (static_cast<float>((va.col >> shift) & 255) * w0 + static_cast<float>((vb.col >> shift) & 255) * w1 + static_cast<float>((vc.col >> shift) & 255) * w2) / 255.f;
                };
                const float a = chan(IM_COL32_A_SHIFT) * atlasAlpha(atlas, u, v);
                if (a <= 0.f)
                    continue;
                float* q = &P[(static_cast<size_t>(y) * static_cast<size_t>(w) + static_cast<size_t>(x)) * 4];
                q[0] = chan(IM_COL32_R_SHIFT) * a + q[0] * (1.f - a);
                q[1] = chan(IM_COL32_G_SHIFT) * a + q[1] * (1.f - a);
                q[2] = chan(IM_COL32_B_SHIFT) * a + q[2] * (1.f - a);
                q[3] = a + q[3] * (1.f - a);
            }
    }
}

static ImTextureData* makeTexture(const std::vector<float>& P, int w, int h) {
    ImTextureData* t = IM_NEW(ImTextureData)();
    t->Create(ImTextureFormat_RGBA32, w, h);
    unsigned char* px = static_cast<unsigned char*>(t->GetPixels());
    for (size_t i = 0; i < static_cast<size_t>(w) * static_cast<size_t>(h); ++i) {
        const float a = P[i * 4 + 3];
        for (int c = 0; c < 3; ++c)
            px[i * 4 + c] = static_cast<unsigned char>(std::clamp(a > 1e-5f ? P[i * 4 + c] / a : 0.f, 0.f, 1.f) * 255.f + 0.5f); // straight alpha: what the blend expects
        px[i * 4 + 3] = static_cast<unsigned char>(std::clamp(a, 0.f, 1.f) * 255.f + 0.5f);
    }
    ImGui::RegisterUserTexture(t);
    return t;
}

// The watermark's layers in the order they are drawn (rim, gold bezel, diamonds), into a list of ours.
static void drawLayers(ImDrawList& l, const std::vector<BentGlyph>& gt, const std::vector<BentGlyph>& gb, const WordCache& ct, const WordCache& cb, ImVec2 centerTop, ImVec2 centerBot, float s, int mode) {
    l._ResetForNewFrame();
    l.PushClipRect(ImVec2(-1e5f, -1e5f), ImVec2(1e5f, 1e5f));
    const ImU32 rim = IM_COL32(24, 14, 0, 235);
    const float rd = 0.9f * s;
    static const float kRim[8][2] = {{-1.f, -1.f}, {+1.f, -1.f}, {+1.f, +1.f}, {-1.f, +1.f}, {0.f, -1.f}, {+1.f, 0.f}, {0.f, +1.f}, {-1.f, 0.f}};
    for (const auto& o : kRim) {
        drawFlatCached(&l, gt, ct, centerTop, o[0] * rd, o[1] * rd, rim);
        drawFlatCached(&l, gb, cb, centerBot, o[0] * rd, o[1] * rd, rim);
    }
    const std::vector<ActiveSparkle> none;
    for (int k = 0; k < 8; ++k)
        drawGridCached(&l, gt, ct.bezel[k], kBezNx, kBezNy, centerTop, 1.f, 0.f, s, true, none, mode);
    for (int k = 0; k < 8; ++k)
        drawGridCached(&l, gb, cb.bezel[k], kBezNx, kBezNy, centerBot, 1.f, 0.f, s, true, none, mode);
    drawGridCached(&l, gt, ct.diamond, kDiaNx, kDiaNy, centerTop, 1.f, 0.f, s, false, none, mode);
    drawGridCached(&l, gb, cb.diamond, kDiaNx, kDiaNy, centerBot, 1.f, 0.f, s, false, none, mode);
}

// Draws the three pictures (once per layout, and again when the UI context is rebuilt: its textures go with it). Invalid when the font atlas cannot be read.
static void buildBake(SchwagBake& bk, const std::vector<BentGlyph>& gt, const std::vector<BentGlyph>& gb, const WordCache& ct, const WordCache& cb, ImVec2 centerTop, ImVec2 centerBot, float s) {
    bk = SchwagBake{};
    bk.ctx = ImGui::GetCurrentContext();
    const ImTextureData* atlas = ImGui::GetIO().Fonts->TexData;
    if (!atlas || !atlas->Pixels)
        return;
    ImDrawList tmp(ImGui::GetDrawListSharedData());
    drawLayers(tmp, gt, gb, ct, cb, centerTop, centerBot, s, 1);
    float x0 = 1e9f, y0 = 1e9f, x1 = -1e9f, y1 = -1e9f;
    for (const ImDrawVert& v : tmp.VtxBuffer) {
        x0 = std::min(x0, v.pos.x);
        y0 = std::min(y0, v.pos.y);
        x1 = std::max(x1, v.pos.x);
        y1 = std::max(y1, v.pos.y);
    }
    if (x1 <= x0 || y1 <= y0)
        return;
    bk.origin = ImVec2(std::floor(x0) - 3.f, std::floor(y0) - 3.f);
    bk.w = static_cast<int>(std::ceil(x1) + 3.f - bk.origin.x);
    bk.h = static_cast<int>(std::ceil(y1) + 3.f - bk.origin.y);
    std::vector<float> baseP(static_cast<size_t>(bk.w) * static_cast<size_t>(bk.h) * 4, 0.f), boostP = baseP, whiteP = baseP;
    rasterizeList(tmp, atlas, bk.origin, bk.w, bk.h, baseP);
    drawLayers(tmp, gt, gb, ct, cb, centerTop, centerBot, s, 2);
    rasterizeList(tmp, atlas, bk.origin, bk.w, bk.h, boostP);
    tmp._ResetForNewFrame();
    tmp.PushClipRect(ImVec2(-1e5f, -1e5f), ImVec2(1e5f, 1e5f));
    drawFlatCached(&tmp, gt, ct, centerTop, 0.f, 0.f, IM_COL32(255, 255, 255, 255));
    drawFlatCached(&tmp, gb, cb, centerBot, 0.f, 0.f, IM_COL32(255, 255, 255, 255));
    rasterizeList(tmp, atlas, bk.origin, bk.w, bk.h, whiteP);
    bk.base = makeTexture(baseP, bk.w, bk.h);
    bk.boost = makeTexture(boostP, bk.w, bk.h);
    bk.white = makeTexture(whiteP, bk.w, bk.h);
}

// A grid of quads over a part of the pictures (screen rect r), one texture, vertex alpha from `alphaAt(x, y)`; cells that stay clear are not drawn.
template <class F>
static void drawAlphaGrid(ImDrawList* d, ImTextureData* tex, const SchwagBake& bk, ImVec2 p0, ImVec2 r0, ImVec2 r1, int nx, int ny, F alphaAt) {
    const float rx0 = std::max(r0.x, p0.x), ry0 = std::max(r0.y, p0.y), rx1 = std::min(r1.x, p0.x + static_cast<float>(bk.w)), ry1 = std::min(r1.y, p0.y + static_cast<float>(bk.h));
    if (rx1 <= rx0 || ry1 <= ry0)
        return;
    const float cw = (rx1 - rx0) / static_cast<float>(nx), ch = (ry1 - ry0) / static_cast<float>(ny);
    static std::vector<float> al;
    al.resize(static_cast<size_t>(nx + 1) * static_cast<size_t>(ny + 1));
    bool any = false;
    for (int j = 0; j <= ny; ++j)
        for (int i = 0; i <= nx; ++i) {
            const float a = alphaAt(rx0 + static_cast<float>(i) * cw, ry0 + static_cast<float>(j) * ch);
            al[static_cast<size_t>(j) * static_cast<size_t>(nx + 1) + static_cast<size_t>(i)] = a;
            any |= a > 0.01f;
        }
    if (!any)
        return;
    d->PushTexture(tex->GetTexRef());
    const auto vtx = [&](int i, int j) {
        const float x = rx0 + static_cast<float>(i) * cw, y = ry0 + static_cast<float>(j) * ch;
        d->PrimWriteVtx(ImVec2(x, y), ImVec2((x - p0.x) / static_cast<float>(bk.w), (y - p0.y) / static_cast<float>(bk.h)),
                        IM_COL32(255, 255, 255, static_cast<int>(std::clamp(al[static_cast<size_t>(j) * static_cast<size_t>(nx + 1) + static_cast<size_t>(i)], 0.f, 1.f) * 255.f)));
    };
    for (int j = 0; j < ny; ++j)
        for (int i = 0; i < nx; ++i) {
            const size_t k = static_cast<size_t>(j) * static_cast<size_t>(nx + 1) + static_cast<size_t>(i);
            if (std::max(std::max(al[k], al[k + 1]), std::max(al[k + static_cast<size_t>(nx) + 1], al[k + static_cast<size_t>(nx) + 2])) < 0.01f)
                continue;
            d->PrimReserve(6, 4);
            const ImDrawIdx idx = static_cast<ImDrawIdx>(d->_VtxCurrentIdx);
            d->PrimWriteIdx(idx);     d->PrimWriteIdx(idx + 1); d->PrimWriteIdx(idx + 2);
            d->PrimWriteIdx(idx);     d->PrimWriteIdx(idx + 2); d->PrimWriteIdx(idx + 3);
            vtx(i, j);
            vtx(i + 1, j);
            vtx(i + 1, j + 1);
            vtx(i, j + 1);
        }
    d->PopTexture();
}

// A frame of the baked watermark: the picture, the sweep over it, the sparkles' light over that.
static void drawBaked(ImDrawList* d, const SchwagBake& bk, ImVec2 base, float s, float amount, float time, const std::vector<ActiveSparkle>& sparkles) {
    // The pictures are drawn 1:1 with the screen's pixels: on a whole-pixel position (the slide-in moves `base` through fractions, and a picture between two pixel columns is
    // sampled bilinearly: the soft edges).
    const ImVec2 p0(std::round(base.x + bk.origin.x), std::round(base.y + bk.origin.y)), p1(p0.x + static_cast<float>(bk.w), p0.y + static_cast<float>(bk.h));
    d->AddImage(bk.base->GetTexRef(), p0, p1, ImVec2(0.f, 0.f), ImVec2(1.f, 1.f), IM_COL32(255, 255, 255, static_cast<int>(255 * amount)));
    // the caustic sweep: a band travelling across the letters (the same function the per-vertex version used), as the boost picture's alpha
    drawAlphaGrid(d, bk.boost, bk, p0, p0, p1, std::max(1, static_cast<int>(std::ceil(static_cast<float>(bk.w) / 14.f))), std::max(1, static_cast<int>(std::ceil(static_cast<float>(bk.h) / 14.f))),
                  [&](float x, float y) { return std::clamp((sinf(x * 0.022f - y * 0.015f - time * 1.8f) - 0.70f) / 0.30f, 0.f, 1.f) * amount; });
    // a sparkle lights the letters around it: toward white, by how near it is (inside 9 px it washes out, out to 45 px it fades with the square of the distance)
    for (const auto& sp : sparkles) {
        if (sp.intensity <= 0.05f)
            continue;
        const float reach = 45.f * s, core = 9.f * s;
        drawAlphaGrid(d, bk.white, bk, p0, ImVec2(sp.pos.x - reach, sp.pos.y - reach), ImVec2(sp.pos.x + reach, sp.pos.y + reach), 6, 6, [&](float x, float y) {
            const float dist = std::hypot(x - sp.pos.x, y - sp.pos.y);
            if (dist >= reach)
                return 0.f;
            if (dist < core)
                return (1.f - dist / core) * sp.intensity * amount;
            const float t = (1.f - (dist - core) / (36.f * s)) * sp.intensity;
            return std::min(1.f, 3.0f * t * t) * amount; // the original adds up to 175 to a channel: toward white in a lit facet, about 3 t^2 of the way
        });
    }
}

// One size of the watermark: its layout and its baked pictures. Slot 0 is the HUD's; the boot screen has its own (a big one) so neither rebuilds the other's every frame.
struct SchwagSet {
    ImFont* cachedFont = nullptr;
    float cachedSize = 0.f;
    std::vector<BentGlyph> cachedTop, cachedBot;
    WordCache cacheTop, cacheBot;
    SchwagBake bake;
    bool layoutBuilt = false;
    float cTopW = 0.f, cTopMin = 0.f, cTopMax = 0.f, cBotW = 0.f, cBotMin = 0.f, cBotMax = 0.f;
};
static inline SchwagSet gSets[2];

// The layout only changes with the font / size: rebuilt then, not every frame; the pictures follow the layout and the UI context (its textures are gone with it).
static SchwagSet& ensureSet(ImFont* font, float s, int slot) {
    SchwagSet& S = gSets[slot];
    const float fontSize = 58.0f * s;
    if (S.cachedFont != font || S.cachedSize != fontSize) {
        S.cachedTop = layoutBentText(font, fontSize, "BLUEY", 6.0f * s, S.cTopW, S.cTopMin, S.cTopMax);
        S.cachedBot = layoutBentText(font, fontSize, "SENSE", 6.0f * s, S.cBotW, S.cBotMin, S.cBotMax);
        S.cachedFont = font;
        S.cachedSize = fontSize;
        buildWordCache(S.cacheTop, S.cachedTop, 560.0f * s, true, S.cTopW, S.cTopMin, S.cTopMax, s);
        buildWordCache(S.cacheBot, S.cachedBot, 560.0f * s, false, S.cBotW, S.cBotMin, S.cBotMax, s);
        S.layoutBuilt = true;
    }
    refreshGlyphUVs(font, fontSize, S.cachedTop);
    refreshGlyphUVs(font, fontSize, S.cachedBot);
    if (S.layoutBuilt || S.bake.ctx != ImGui::GetCurrentContext()) {
        buildBake(S.bake, S.cachedTop, S.cachedBot, S.cacheTop, S.cacheBot, ImVec2(95.0f * s, 26.0f * s), ImVec2(95.0f * s, 112.0f * s), s); // relative to the base point: the watermark slides
        S.layoutBuilt = false;
    }
    return S;
}

// Complete Schwag watermark renderer
static void drawSchwag(ImDrawList* d, ImFont* font, ImVec2 base, float s, float amount, ImDrawList* glowList = nullptr, int slot = 0) {
    if (!font || amount <= 0.01f)
        return;

    const float time = static_cast<float>(ImGui::GetTime());
    const float alpha = amount;
    const float radius = 560.0f * s;      // upward arc rise for BLUEY

    // Top and bottom words placed farther apart with clean separation
    const ImVec2 centerTop(base.x + 95.0f * s, base.y + 26.0f * s);
    const ImVec2 centerBot(base.x + 95.0f * s, base.y + 112.0f * s);

    SchwagSet& S = ensureSet(font, s, slot);
    const SchwagBake& bake = S.bake;
    const WordCache& cacheTop = S.cacheTop;
    const WordCache& cacheBot = S.cacheBot;
    const float wTop = S.cTopW, yMinTop = S.cTopMin, yMaxTop = S.cTopMax;
    const float wBot = S.cBotW, yMinBot = S.cBotMin, yMaxBot = S.cBotMax;
    const auto& glyphsTop = S.cachedTop;
    const auto& glyphsBot = S.cachedBot;

    // Calculate active sparkles and their screen positions
    struct SparkleAnchor {
        int glyphIdx;
        float normX, normY;
        bool isTop;
        float speed, phase, size;
    };

    const SparkleAnchor anchors[] = {
        // BLUEY sparkles (matching reference positions)
        { 0, 0.05f, 0.08f, true,  1.1f, 0.2f, 20.0f * s }, // 'B' top-left corner
        { 0, 0.88f, 0.35f, true,  1.4f, 2.5f, 16.0f * s }, // 'B' middle loop
        { 1, 0.10f, 0.94f, true,  1.2f, 1.8f, 18.0f * s }, // 'L' bottom-left
        { 1, 0.92f, 0.94f, true,  0.9f, 4.1f, 16.0f * s }, // 'L' bottom-right
        { 2, 0.50f, 0.02f, true,  1.0f, 2.1f, 22.0f * s }, // 'U' top apex
        { 2, 0.50f, 0.96f, true,  1.3f, 5.0f, 17.0f * s }, // 'U' bottom curve
        { 3, 0.92f, 0.08f, true,  1.1f, 3.4f, 19.0f * s }, // 'E' top-right
        { 3, 0.92f, 0.94f, true,  1.2f, 0.7f, 18.0f * s }, // 'E' bottom-right
        { 4, 0.06f, 0.06f, true,  1.0f, 4.5f, 17.0f * s }, // 'Y' top-left
        { 4, 0.94f, 0.06f, true,  1.2f, 1.2f, 21.0f * s }, // 'Y' top-right

        // SENSE sparkles (matching reference positions)
        { 0, 0.06f, 0.22f, false, 1.0f, 0.9f, 20.0f * s }, // 'S' top-left
        { 0, 0.92f, 0.82f, false, 1.3f, 3.1f, 18.0f * s }, // 'S' bottom-right
        { 1, 0.92f, 0.06f, false, 1.1f, 1.9f, 18.0f * s }, // 'E' top-right
        { 2, 0.10f, 0.06f, false, 1.2f, 4.8f, 17.0f * s }, // 'N' top-left
        { 2, 0.50f, 0.96f, false, 1.4f, 2.8f, 22.0f * s }, // 'N' bottom apex
        { 2, 0.90f, 0.06f, false, 0.9f, 0.4f, 18.0f * s }, // 'N' top-right
        { 3, 0.88f, 0.50f, false, 1.2f, 3.7f, 17.0f * s }, // 'S' middle spine
        { 4, 0.94f, 0.94f, false, 1.1f, 5.3f, 21.0f * s }, // 'E' bottom-right
    };

    // only the sparkles that are lit: every vertex loops this list, and most of the time most are dark
    static std::vector<ActiveSparkle> activeSparkles;
    activeSparkles.clear();
    for (size_t k = 0; k < sizeof(anchors) / sizeof(anchors[0]); ++k) {
        const auto& ga = anchors[k];
        const auto& glyphs = ga.isTop ? glyphsTop : glyphsBot;
        if (ga.glyphIdx >= static_cast<int>(glyphs.size())) continue;
        const auto& g = glyphs[ga.glyphIdx];

        const float unbentX = g.x0 + ga.normX * (g.x1 - g.x0);
        const float unbentY = g.y0 + ga.normY * (g.y1 - g.y0);
        const ImVec2 center = ga.isTop ? centerTop : centerBot;
        const float totalW  = ga.isTop ? wTop : wBot;
        const float yMin    = ga.isTop ? yMinTop : yMinBot;
        const float yMax    = ga.isTop ? yMaxTop : yMaxBot;
        const ImVec2 pos    = warpPointDispatch(unbentX, unbentY, center, radius, ga.isTop, totalW, yMin, yMax, s);

        const float cycle = time * ga.speed * 1.8f + ga.phase;
        const float rawSine = sinf(cycle);
        // Sharper pulse so it glints with real peak timing
        const float pulse = rawSine > 0.25f ? powf((rawSine - 0.25f) / 0.75f, 1.8f) : 0.0f;

        const float angle = time * 0.12f + static_cast<float>(k) * 0.785f;
        if (pulse > 0.05f)
            activeSparkles.push_back({ pos, pulse, ga.size, angle });
    }

    // 1. D3D12 Glow Bloom Pass:
    // Pushes radiant pure white diamond glow with subtle sparkle flare reaction into glowList
    if (glowList) {
        glowList->PushTexture(ImGui::GetIO().Fonts->TexRef);

        // Radiant pure white diamond glow emitted from the letter silhouettes (no yellow text silhouette!)
        const ImU32 whiteGlow = IM_COL32(255, 255, 255, static_cast<int>(255 * alpha));
        // Center solid core of pure white diamond bloom
        drawBentGlyphsFlat(glowList, glyphsTop, centerTop, radius, true,  wTop, 0.f, 0.f, whiteGlow, whiteGlow, yMinTop, yMaxTop, s);
        drawBentGlyphsFlat(glowList, glyphsBot, centerBot, radius, false, wBot, 0.f, 0.f, whiteGlow, whiteGlow, yMinBot, yMaxBot, s);

        // Active sparkles: pure brilliant white center and subtle warm amber flare halo (very slight flare reaction!)
        for (const auto& sp : activeSparkles) {
            if (sp.intensity <= 0.08f) continue;
            const float p = sp.intensity * alpha;
            const ImU32 bloomWhite = IM_COL32(255, 255, 255, static_cast<int>(255 * p));
            // Subtle warm amber flare halo (slight reaction, not overpowering)
            const ImU32 bloomFlare = IM_COL32(255, 225, 120, static_cast<int>(75 * p));

            glowList->AddCircleFilled(sp.pos, 16.0f * s * p, bloomFlare, 20);
            glowList->AddCircleFilled(sp.pos, 5.0f * s * p, bloomWhite, 16);
        }

        glowList->PopTexture();
    }

    // 2. Main Draw Pass on d
    d->PushTexture(ImGui::GetIO().Fonts->TexRef);

    const auto flare = [&]() { // specular flare at the active sparkles along the gold border
        for (const auto& sp : activeSparkles) {
            if (sp.intensity <= 0.08f) continue;
            const float p = sp.intensity * alpha;
            d->AddCircleFilled(sp.pos, 3.5f * s * p, IM_COL32(255, 255, 215, static_cast<int>(255 * p)), 12);
        }
    };
    if (bake.ready() && !gPerVertex) {
        d->PopTexture(); // the baked pictures bring their own
        drawBaked(d, bake, base, s, alpha, time, activeSparkles);
        d->PushTexture(ImGui::GetIO().Fonts->TexRef);
        flare();
        flare(); // as the per-vertex version drew it: once after each word's bezel
    } else {
    // Dark rim outside the gold so the letters separate from whatever is behind them
        {
            const ImU32 rim = IM_COL32(24, 14, 0, static_cast<int>(235 * alpha));
            const float rd = 0.9f * s;
            static const float kRim[8][2] = { { -1.f, -1.f }, { +1.f, -1.f }, { +1.f, +1.f }, { -1.f, +1.f }, { 0.f, -1.f }, { +1.f, 0.f }, { 0.f, +1.f }, { -1.f, 0.f } };
            for (const auto& o : kRim) {
                drawFlatCached(d, glyphsTop, cacheTop, centerTop, o[0] * rd, o[1] * rd, rim);
                drawFlatCached(d, glyphsBot, cacheBot, centerBot, o[0] * rd, o[1] * rd, rim);
            }
        }

        // Outer 3D metallic cast gold bezel (tight, sharp 90-degree miter rim reacting to the diamond texture and the sparkles), a word at a time, each with the
        // specular flare at the active sparkles along the gold border
        const auto flare = [&]() {
            for (const auto& sp : activeSparkles) {
                if (sp.intensity <= 0.08f) continue;
                const float p = sp.intensity * alpha;
                d->AddCircleFilled(sp.pos, 3.5f * s * p, IM_COL32(255, 255, 215, static_cast<int>(255 * p)), 12);
            }
        };
        for (int k = 0; k < 8; ++k)
            drawGridCached(d, glyphsTop, cacheTop.bezel[k], kBezNx, kBezNy, centerTop, alpha, time, s, true, activeSparkles);
        flare();
        for (int k = 0; k < 8; ++k)
            drawGridCached(d, glyphsBot, cacheBot.bezel[k], kBezNx, kBezNy, centerBot, alpha, time, s, true, activeSparkles);
        flare();

        // Core encrusted high-contrast photographic diamond pave pass
        drawGridCached(d, glyphsTop, cacheTop.diamond, kDiaNx, kDiaNy, centerTop, alpha, time, s, false, activeSparkles);
        drawGridCached(d, glyphsBot, cacheBot.diamond, kDiaNx, kDiaNy, centerBot, alpha, time, s, false, activeSparkles);

    }
    d->PopTexture();

    // 3. Draw Razor-Sharp Brilliant White Diamond Sparkle Sunbursts
    for (const auto& sp : activeSparkles) {
        drawRealisticGlint(d, sp.pos, sp.size, sp.intensity, sp.angle, alpha, s);
    }
}

};
