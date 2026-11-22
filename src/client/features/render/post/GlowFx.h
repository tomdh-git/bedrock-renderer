#pragma once
#include "client/features/render/backend/OverlayBackend.h"
#include "client/features/render/post/FullscreenFx.h"

// Glow and shadow of the UI, done the way light actually behaves instead of one blurred shape per element.
struct GlowLevel {
    static constexpr int Pill = 215;    // the module list's bar (mode 0)
    static constexpr int Line = 215;    // its edge lines (mode 2)
    static constexpr int Outline = 175; // its outline (mode 1)
    static constexpr int Text = 190;    // text: the watermark
};

struct GlowFx {
    static inline float factor = 1.f; // 0..2, from the Interface module, every frame: multiplies the light of everything that glows
    static void init();
    static void shutdown();       // the targets and the draw lists (before ImGui is destroyed)
    static void beginFrame();     // after ImGui::NewFrame

    // Light source: a filled rounded rectangle / circle of colour `col` (its alpha is the strength); `reach` (px) is how far
    // the light should travel: a larger reach makes the source a little bigger and the tail longer.
    static void glow(ImVec2 mn, ImVec2 mx, float rounding, ImU32 col, float reach, ImDrawFlags flags = 0); // flags: which corners round (the shape as drawn)
    // Any shape: text (glyph by glyph, so the light follows the letters) and polygons (convex or not).
    static ImDrawList* glowList();
    static void glowText(ImFont* font, float size, ImVec2 pos, const char* text, ImU32 col, float reach);
    static void glowPoly(const ImVec2* points, int count, ImU32 col, float reach);
    // Shadow caster: a rounded rectangle; `alpha` 0..1, `reach` (px) is the softness (the shadow also sits a little lower:
    // the light comes from above).
    static void shadow(ImVec2 mn, ImVec2 mx, float rounding, float alpha, float reach);

    // A closed stroked rectangle caster is submitted before the game's entities, which cover it with their exact silhouettes.
    static void shadowOutlineUnderActors(ImVec2 mn, ImVec2 mx, float thickness, float alpha, float reach);
    // The same for any stroked path (corners, polygons): the points are the stroke's centre line, `closed` joins the last to the first; joins are mitred.
    static void shadowPathUnderActors(const ImVec2* points, int count, bool closed, float thickness, float alpha, float reach);
    static ImDrawList* underActorsShadowList();
    static bool hasUnderActors();
    static void renderUnderActors(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height); // before entities

    // After ImGui::Render, before the UI pass: the shadows and the glow are recorded in `cmd` onto swapchain buffer `bufferIndex`, which is in `bufferState`
    // (moved as needed; `bufferState` is where it is left).
    static void render(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height);

private:
    static ImU32 dimmed(ImU32 col, float k);
    static constexpr int kLevels = 4;                 // pyramid levels below the source (1/4 .. 1/32 of the screen)
    static constexpr DXGI_FORMAT kFormat = DXGI_FORMAT_R16G16B16A16_FLOAT; // sums of overlapping lights must not clip
    static constexpr DXGI_FORMAT kShadowFormat = DXGI_FORMAT_R16_FLOAT;    // a shadow is one number (coverage) per texel: a quarter of the memory traffic
    static ImDrawList* sGlowList;
    static ImDrawList* sShadowList;
    static ImDrawList* sUnderActorsShadowList;
    static void renderShadow(OverlayBackend::Cmd& cmd, ImDrawList* list, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height);
    static ImDrawList* makeList();
    static void resetList(ImDrawList* l);
    static FullscreenFx::Target s12Source;            // half resolution: the lights drawn in their own colours
    static FullscreenFx::Target s12Level[kLevels];    // successive halvings of the source
    static FullscreenFx::Target s12ShadowSource;      // the same for the shadows, in one channel
    static FullscreenFx::Target s12ShadowLevel[kLevels];
    static FullscreenFx::Target s12Back;              // a copy of the picture under the glow
    static UINT s12W;
    static UINT s12H;
    static void ensureTargets(UINT w, UINT h);
    static D3D12_RECT reachOf(const ImDrawList* list, float margin, UINT w, UINT h);
    static void drawSource(OverlayBackend::Cmd& cmd, ImDrawList* list, FullscreenFx::Target& s12Source);
    static D3D12_RECT levelArea(const D3D12_RECT& area, UINT width, UINT height, const FullscreenFx::Target& t);
    static void blurPyramid(OverlayBackend::Cmd& cmd, FullscreenFx::Target& s12Source, FullscreenFx::Target (&s12Level)[kLevels], const float upGain[kLevels], const D3D12_RECT& area, UINT width, UINT height);
};
