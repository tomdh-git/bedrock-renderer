#include "client/features/render/post/GlowFx.h"
#include "client/features/render/post/FullscreenFx.h"

// Filled shapes are far larger than glyphs, so the same colour carries much more light: they enter the glow at a fraction of
// their strength (text keeps all of it).
ImU32 GlowFx::dimmed(ImU32 col, float k) {
    const ImU32 a = static_cast<ImU32>(static_cast<float>((col >> IM_COL32_A_SHIFT) & 0xFF) * k);
    return (col & ~IM_COL32_A_MASK) | (a << IM_COL32_A_SHIFT);
}
ImDrawList* GlowFx::sGlowList = nullptr;
ImDrawList* GlowFx::sShadowList = nullptr;
ImDrawList* GlowFx::sUnderActorsShadowList = nullptr;
ImDrawList* GlowFx::makeList() {
    ImDrawList* l = IM_NEW(ImDrawList)(ImGui::GetDrawListSharedData());
    return l;
}
void GlowFx::resetList(ImDrawList* l) {
    l->_ResetForNewFrame();
    l->PushTexture(ImGui::GetIO().Fonts->TexRef);
    l->PushClipRectFullScreen();
}


void GlowFx::beginFrame() {
    if (!sGlowList)
        sGlowList = makeList();
    if (!sShadowList)
        sShadowList = makeList();
    if (!sUnderActorsShadowList)
        sUnderActorsShadowList = makeList();
    resetList(sGlowList);
    resetList(sShadowList);
    resetList(sUnderActorsShadowList);
}

void GlowFx::glow(ImVec2 mn, ImVec2 mx, float rounding, ImU32 col, float reach, ImDrawFlags flags) {
    if (!sGlowList)
        return;
    const float g = reach * 0.04f; // a farther-reaching light is a slightly fatter source
    sGlowList->AddRectFilled(ImVec2(mn.x - g, mn.y - g), ImVec2(mx.x + g, mx.y + g), dimmed(col, 0.5f), rounding + g, flags);
}
ImDrawList* GlowFx::glowList() {
    return sGlowList;
}

void GlowFx::glowText(ImFont* font, float size, ImVec2 pos, const char* text, ImU32 col, float) {
    if (sGlowList)
        sGlowList->AddText(font, size, pos, col, text);
}

void GlowFx::glowPoly(const ImVec2* points, int count, ImU32 col, float) {
    if (sGlowList && count >= 3)
        sGlowList->AddConcavePolyFilled(points, count, dimmed(col, 0.6f));
}
static void addShadowRect(ImDrawList* list, ImVec2 mn, ImVec2 mx, float rounding, float alpha, float reach) {
    const float drop = reach * 0.05f, shrink = reach * 0.05f;
    list->AddRectFilled(ImVec2(mn.x + shrink, mn.y + shrink + drop), ImVec2(mx.x - shrink, mx.y - shrink + drop),
                               IM_COL32(255, 255, 255, static_cast<int>(255.0f * (alpha < 0.f ? 0.f : (alpha > 1.f ? 1.f : alpha)))), rounding);
}
void GlowFx::shadow(ImVec2 mn, ImVec2 mx, float rounding, float alpha, float reach) {
    if (sShadowList)
        addShadowRect(sShadowList, mn, mx, rounding, alpha, reach);
}
void GlowFx::shadowOutlineUnderActors(ImVec2 mn, ImVec2 mx, float thickness, float alpha, float reach) {
    if (!sUnderActorsShadowList || thickness <= 0.f)
        return;
    const float drop = reach * 0.05f;
    const float half = thickness * 0.5f;
    const ImU32 color = IM_COL32(255, 255, 255, static_cast<int>(255.0f * std::clamp(alpha, 0.f, 1.f)));
    sUnderActorsShadowList->AddRect(ImVec2(mn.x + half, mn.y + half + drop), ImVec2(mx.x - half, mx.y - half + drop), color, 0.f, ImDrawFlags_None, thickness);
}
void GlowFx::shadowPathUnderActors(const ImVec2* points, int count, bool closed, float thickness, float alpha, float reach) {
    if (!sUnderActorsShadowList || thickness <= 0.f || count < 2)
        return;
    const float drop = reach * 0.05f;
    const ImU32 color = IM_COL32(255, 255, 255, static_cast<int>(255.0f * std::clamp(alpha, 0.f, 1.f)));
    std::vector<ImVec2> shifted(points, points + count);
    for (ImVec2& p : shifted)
        p.y += drop;
    sUnderActorsShadowList->AddPolyline(shifted.data(), count, color, closed ? ImDrawFlags_Closed : ImDrawFlags_None, thickness);
}
ImDrawList* GlowFx::underActorsShadowList() {
    return sUnderActorsShadowList;
}
bool GlowFx::hasUnderActors() {
    return sUnderActorsShadowList && sUnderActorsShadowList->VtxBuffer.Size > 0;
}

// ---- D3D12 --------------------------------------------------------------------------------------------------------------------------------------

FullscreenFx::Target GlowFx::s12Source;            // half resolution: the lights drawn in their own colours
FullscreenFx::Target GlowFx::s12Level[kLevels];    // successive halvings of the source
FullscreenFx::Target GlowFx::s12ShadowSource;      // the same for the shadows, in one channel
FullscreenFx::Target GlowFx::s12ShadowLevel[kLevels];
FullscreenFx::Target GlowFx::s12Back;              // a copy of the picture under the glow
UINT GlowFx::s12W = 0;
UINT GlowFx::s12H = 0;
void GlowFx::ensureTargets(UINT w, UINT h) {
    if (w == s12W && h == s12H && s12Source.res)
        return;
    FullscreenFx::freeTarget(s12Source);
    for (auto& t : s12Level)
        FullscreenFx::freeTarget(t);
    UINT tw = std::max(1u, w / 2), th = std::max(1u, h / 2);
    FullscreenFx::makeTarget(s12Source, tw, th, kFormat);
    for (auto& t : s12Level) {
        tw = std::max(1u, tw / 2);
        th = std::max(1u, th / 2);
        FullscreenFx::makeTarget(t, tw, th, kFormat);
    }
    FullscreenFx::freeTarget(s12ShadowSource);
    for (auto& t : s12ShadowLevel)
        FullscreenFx::freeTarget(t);
    tw = std::max(1u, w / 2);
    th = std::max(1u, h / 2);
    FullscreenFx::makeTarget(s12ShadowSource, tw, th, kShadowFormat);
    for (auto& t : s12ShadowLevel) {
        tw = std::max(1u, tw / 2);
        th = std::max(1u, th / 2);
        FullscreenFx::makeTarget(t, tw, th, kShadowFormat);
    }
    s12W = w;
    s12H = h;
}

// The pixels a list's shapes can light or darken: their bounds and the reach of the blur around them (the coarsest level spreads it a hundred pixels or so).
D3D12_RECT GlowFx::reachOf(const ImDrawList* list, float margin, UINT w, UINT h) {
    float x0 = 1e9f, y0 = 1e9f, x1 = -1e9f, y1 = -1e9f;
    for (const ImDrawVert& v : list->VtxBuffer) {
        x0 = std::min(x0, v.pos.x);
        y0 = std::min(y0, v.pos.y);
        x1 = std::max(x1, v.pos.x);
        y1 = std::max(y1, v.pos.y);
    }
    const float sx = static_cast<float>(w) / std::max(ImGui::GetIO().DisplaySize.x, 1.f), sy = static_cast<float>(h) / std::max(ImGui::GetIO().DisplaySize.y, 1.f);
    return D3D12_RECT{std::clamp(static_cast<LONG>((x0 - margin) * sx), 0L, static_cast<LONG>(w)), std::clamp(static_cast<LONG>((y0 - margin) * sy), 0L, static_cast<LONG>(h)),
                      std::clamp(static_cast<LONG>((x1 + margin) * sx) + 1, 0L, static_cast<LONG>(w)), std::clamp(static_cast<LONG>((y1 + margin) * sy) + 1, 0L, static_cast<LONG>(h))};
}
void GlowFx::drawSource(OverlayBackend::Cmd& cmd, ImDrawList* list, FullscreenFx::Target& s12Source) {
    FullscreenFx::toState(cmd, s12Source, D3D12_RESOURCE_STATE_RENDER_TARGET);
    const float clear[4] = {0, 0, 0, 0};
    cmd.list->ClearRenderTargetView(OverlayBackend::rtvCpu(s12Source.rtv), clear, 0, nullptr);
    ImDrawData dd;
    dd.Valid = true;
    dd.CmdListsCount = 1;
    dd.TotalVtxCount = list->VtxBuffer.Size;
    dd.TotalIdxCount = list->IdxBuffer.Size;
    dd.CmdLists.push_back(list);
    dd.DisplayPos = ImVec2(0.f, 0.f);
    dd.DisplaySize = ImGui::GetIO().DisplaySize;
    dd.FramebufferScale = ImVec2(static_cast<float>(s12Source.w) / dd.DisplaySize.x, static_cast<float>(s12Source.h) / dd.DisplaySize.y);
    dd.Textures = &ImGui::GetPlatformIO().Textures;
    OverlayBackend::drawImGui(cmd, &dd, OverlayBackend::rtvCpu(s12Source.rtv), s12Source.format, static_cast<float>(s12Source.w), static_cast<float>(s12Source.h));
    FullscreenFx::toState(cmd, s12Source, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

// source -> halvings -> back up, each level adding the coarser ones: level 0 is the blurred picture at every scale.
// `area`: the pixels (of a width x height screen) the glow can reach; every pass draws only the part of its level that covers them, a few texels wider (the filters
// read a little around). Outside it the levels keep whatever they held, which is never read where it would show.
D3D12_RECT GlowFx::levelArea(const D3D12_RECT& area, UINT width, UINT height, const FullscreenFx::Target& t) {
    const float sx = static_cast<float>(t.w) / static_cast<float>(width), sy = static_cast<float>(t.h) / static_cast<float>(height);
    return D3D12_RECT{std::max(0L, static_cast<LONG>(area.left * sx) - 3), std::max(0L, static_cast<LONG>(area.top * sy) - 3),
                      std::min(static_cast<LONG>(t.w), static_cast<LONG>(area.right * sx) + 4), std::min(static_cast<LONG>(t.h), static_cast<LONG>(area.bottom * sy) + 4)};
}
void GlowFx::blurPyramid(OverlayBackend::Cmd& cmd, FullscreenFx::Target& s12Source, FullscreenFx::Target (&s12Level)[kLevels], const float upGain[kLevels], const D3D12_RECT& area, UINT width, UINT height) {
    FullscreenFx::Target* prev = &s12Source;
    for (int i = 0; i < kLevels; i++) {
        FullscreenFx::toState(cmd, s12Level[i], D3D12_RESOURCE_STATE_RENDER_TARGET);
        const float c[8] = {1.0f / static_cast<float>(prev->w), 1.0f / static_cast<float>(prev->h), 1.0f, 0, 0, 0, 0, 0};
        const D3D12_RECT sr = levelArea(area, width, height, s12Level[i]);
        FullscreenFx::pass(cmd, FullscreenFx::GlowDown, FullscreenFx::Opaque, prev->res, nullptr, OverlayBackend::rtvCpu(s12Level[i].rtv), s12Level[i].format, s12Level[i].w, s12Level[i].h, c, &sr);
        FullscreenFx::toState(cmd, s12Level[i], D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        prev = &s12Level[i];
    }
    for (int i = kLevels - 1; i > 0; i--) {
        FullscreenFx::toState(cmd, s12Level[i - 1], D3D12_RESOURCE_STATE_RENDER_TARGET);
        const float c[8] = {1.0f / static_cast<float>(s12Level[i].w), 1.0f / static_cast<float>(s12Level[i].h), upGain[i], 0, 0, 0, 0, 0};
        const D3D12_RECT sr = levelArea(area, width, height, s12Level[i - 1]);
        FullscreenFx::pass(cmd, FullscreenFx::GlowUp, FullscreenFx::Add, s12Level[i].res, nullptr, OverlayBackend::rtvCpu(s12Level[i - 1].rtv), s12Level[i - 1].format, s12Level[i - 1].w, s12Level[i - 1].h, c, &sr);
        FullscreenFx::toState(cmd, s12Level[i - 1], D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    }
}



void GlowFx::init() {}

void GlowFx::shutdown() {
    if (sGlowList) { IM_DELETE(sGlowList); sGlowList = nullptr; }
    if (sShadowList) { IM_DELETE(sShadowList); sShadowList = nullptr; }
    if (sUnderActorsShadowList) { IM_DELETE(sUnderActorsShadowList); sUnderActorsShadowList = nullptr; }
    FullscreenFx::freeTarget(s12Source);
    for (auto& t : s12Level)
        FullscreenFx::freeTarget(t);
    FullscreenFx::freeTarget(s12Back);
    FullscreenFx::freeTarget(s12ShadowSource);
    for (auto& t : s12ShadowLevel)
        FullscreenFx::freeTarget(t);
    s12W = s12H = 0;
}

// The broad, soft kind: a list's shapes blurred and laid over the picture as shade.
void GlowFx::renderShadow(OverlayBackend::Cmd& cmd, ImDrawList* list, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height) {
    ensureTargets(width, height);
    drawSource(cmd, list, s12ShadowSource);
    const float up[kLevels] = {0.f, 0.8f, 0.6f, 0.4f};
    const D3D12_RECT shadowArea = reachOf(list, 260.f, width, height);
    blurPyramid(cmd, s12ShadowSource, s12ShadowLevel, up, shadowArea, width, height);
    OverlayBackend::moveBuffer(cmd, bufferIndex, bufferState, D3D12_RESOURCE_STATE_RENDER_TARGET);
    const float c[8] = {1.0f / static_cast<float>(s12ShadowLevel[0].w), 1.0f / static_cast<float>(s12ShadowLevel[0].h), 0.9f, 0, 0, 0, 0, 0};
    if (shadowArea.right > shadowArea.left && shadowArea.bottom > shadowArea.top)
        FullscreenFx::pass(cmd, FullscreenFx::ShadowComp, FullscreenFx::Shade, s12ShadowLevel[0].res, nullptr, OverlayBackend::bufferRtv(bufferIndex), OverlayBackend::backFormat(), width, height, c, &shadowArea);
}

void GlowFx::renderUnderActors(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height) {
    if (!hasUnderActors() || !width || !height)
        return;
    renderShadow(cmd, sUnderActorsShadowList, bufferIndex, bufferState, width, height);
    resetList(sUnderActorsShadowList);
}

void GlowFx::render(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height) {
    if (!sGlowList || !sShadowList || !width || !height)
        return;
    const bool hasGlow = sGlowList->VtxBuffer.Size > 0, hasShadow = sShadowList->VtxBuffer.Size > 0, hasLeft = hasUnderActors();
    if (!hasGlow && !hasShadow && !hasLeft)
        return;
    ensureTargets(width, height);
    const D3D12_CPU_DESCRIPTOR_HANDLE back = OverlayBackend::bufferRtv(bufferIndex);
    const DXGI_FORMAT backFormat = OverlayBackend::backFormat();

    // The shadow of the lines under the actors, when the under-actors pass did not draw it this frame (no cut for the entities): it goes on at Present, over the actors,
    // rather than being lost.
    if (hasLeft) {
        renderShadow(cmd, sUnderActorsShadowList, bufferIndex, bufferState, width, height);
        resetList(sUnderActorsShadowList);
    }
    // Shadows first (light falls behind the lights)
    if (hasShadow)
        renderShadow(cmd, sShadowList, bufferIndex, bufferState, width, height);
    // Lights: a hot tight core plus progressively fainter, wider tails, composited with the picture under them.
    if (hasGlow) {
        drawSource(cmd, sGlowList, s12Source);
        const float up[kLevels] = {0.f, 0.42f, 0.2f, 0.08f}; // each coarser scale adds less: a tight rim, a short soft tail
        const D3D12_RECT area = reachOf(sGlowList, 260.f, width, height);
        blurPyramid(cmd, s12Source, s12Level, up, area, width, height);
        OverlayBackend::moveBuffer(cmd, bufferIndex, bufferState, D3D12_RESOURCE_STATE_COPY_SOURCE);
        FullscreenFx::ensureCopy(s12Back, width, height, backFormat);
        FullscreenFx::toState(cmd, s12Back, D3D12_RESOURCE_STATE_COPY_DEST);
        // only the picture under the glow is copied and drawn again
        if (area.right > area.left && area.bottom > area.top) {
            D3D12_TEXTURE_COPY_LOCATION dst{}, src{};
            dst.pResource = s12Back.res;
            dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
            src.pResource = OverlayBackend::buffer(bufferIndex);
            src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
            const D3D12_BOX box{static_cast<UINT>(area.left), static_cast<UINT>(area.top), 0, static_cast<UINT>(area.right), static_cast<UINT>(area.bottom), 1};
            cmd.list->CopyTextureRegion(&dst, static_cast<UINT>(area.left), static_cast<UINT>(area.top), 0, &src, &box);
        }
        FullscreenFx::toState(cmd, s12Back, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        OverlayBackend::moveBuffer(cmd, bufferIndex, bufferState, D3D12_RESOURCE_STATE_RENDER_TARGET);
        const float strength = 0.6f * std::clamp(factor, 0.f, 3.f);
        const float c[8] = {1.0f / static_cast<float>(s12Level[0].w), 1.0f / static_cast<float>(s12Level[0].h), strength, 0, 0, 0, 0, 0};
        if (area.right > area.left && area.bottom > area.top)
            FullscreenFx::pass(cmd, FullscreenFx::GlowAdaptive, FullscreenFx::Opaque, s12Level[0].res, s12Back.res, back, backFormat, width, height, c, &area);
    }
}
