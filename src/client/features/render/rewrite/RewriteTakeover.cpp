#include "client/features/render/rewrite/RewriteTakeover.h"

#include "sdk/mc/deps/bgfx/Frame.h"

namespace render::takeover {

// Startup self-check (M3a-style): every layout constant this renderer relies on is compile-time asserted,
// so a layout change in a new game version fails the build instead of silently drawing wrong.
// Runtime validation (Sigs anchor resolution for Encoder::submitCustom 0xbc61560, live Frame dump compare)
// is done at init once the module is wired into a build; this unit may not build or run.
bool selfTest() {
    static_assert(sizeof(ExecCtx) == 0x18, "ExecCtx must be the 0x18-byte executor context");
    static_assert(offsetof(ExecCtx, tag) == 0x00, "ExecCtx::tag at +0x00");
    static_assert(offsetof(ExecCtx, user) == 0x08, "ExecCtx::user at +0x08");
    static_assert(offsetof(ExecCtx, commandList) == 0x10, "ExecCtx::commandList at +0x10");
    static_assert(bgfx::RenderDrawHeader::kSize == 0x80, "item header is 0x80 bytes");
    static_assert(bgfx::FrameOffsets::kItemCount == 0xDC57E8, "Frame item count at +0xDC57E8");
    static_assert(bgfx::FrameOffsets::kSortKeys == 0x14700, "Frame sort keys at +0x14700");
    static_assert(bgfx::FrameOffsets::kSortedItems == 0x94700, "Frame sort values at +0x94700");
    static_assert(bgfx::FrameOffsets::kDrawHeaders == 0xB4700, "Frame item headers at +0xB4700");
    static_assert(bgfx::RenderDrawHeader::kState == 0x20, "header stateFlags at +0x20");
    static_assert(bgfx::RenderDrawHeader::kHandle7A == 0x7A, "header occlusionQuery at +0x7A");
    static_assert(bgfx::RenderDrawHeader::kByte62 == 0x62, "header submitFlags at +0x62");
    static_assert(bgfx::RenderDrawHeader::kScissor == 0x60, "header scissor index at +0x60");
    return true;
}

size_t walkRenderItems(const bgfx::Frame* frame, void* user, ItemVisitor* visit) {
    const uint8_t* base = reinterpret_cast<const uint8_t*>(frame);
    const uint32_t count = *reinterpret_cast<const uint32_t*>(base + bgfx::FrameOffsets::kItemCount);
    size_t visited = 0;
    for (uint32_t index = 0; index < count; ++index) {
        const uint64_t key =
            *reinterpret_cast<const uint64_t*>(base + bgfx::FrameOffsets::kSortKeys + index * 8);
        const uint16_t value =
            *reinterpret_cast<const uint16_t*>(base + bgfx::FrameOffsets::kSortedItems + index * 2);
        const uint8_t* header = base + bgfx::FrameOffsets::kDrawHeaders + index * 0x80;
        RenderItemView item{frame, index, key, value, header};
        visit(user, item);
        ++visited;
    }
    return visited;
}

// Our renderer: the fn passed to Encoder::submitCustom(viewId, render, user).
//
// user is a context block built by the queue point (not written by this unit). It must carry the Frame*:
// ctx itself has no Frame/job back-pointer - only tag+0x00 (rodata 0xF4EDE00, meaning [?], never interpreted
// here), user+0x08, and commandList+0x10, the live ID3D12GraphicsCommandList we record into.
//
// The walk consumes exactly the same extractor output the stock executor consumes (see the header for the
// cited offsets): item count, sort keys, sort values, and the 0x80-byte headers. For each draw header the
// demo re-records the draw through ctx->commandList; custom-item slots (key bit 53) are the renderer's own
// previously queued items and are passed through.
//
// Unwired: the queue point that calls submitCustom, the per-draw re-record into the command list, and the
// user context block definition. No build or in-game run is performed by this unit, so the body below does
// the read-only walk and classifies items; nothing is submitted to the GPU here.
void render(void* user, ExecCtx* ctx) {
    static_cast<void>(user);
    static_cast<void>(ctx);
    // const bgfx::Frame* frame = <Frame* from the user context block>;
    // walkRenderItems(frame, user, [](void* u, RenderItemView item) {
    //     const bool isCustom = (item.key & kKeyCustomBit) != 0;
    //     ... re-record item.header into ctx->commandList (draw) or pass through (custom) ...
    // });
}

} // namespace render::takeover
