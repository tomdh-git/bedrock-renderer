#pragma once

// Q6c / M3f — whole-frame takeover: our renderer consumes the same extractor output the stock executor consumes.
//
// The engine's native whole-frame seam is the custom item (docs/BGFX_MAP.md 6fg/6fh):
//   Encoder::submitCustom(viewId, fn, user) (0xbc61560) stores fn at Encoder+0x100 and user at +0x108,
//   sets sort-key bit 53, and the D3D12 executor (0xe821120, item loop head 0xe8221f5) calls
//   fn(user, &ctx) on the render thread in view order, with a 0x18-byte context it builds at
//   0xe822441..0xe822468 at job+0x3B0:
//       ExecCtx { const void* tag @+0x00; void* user @+0x08; void* commandList @+0x10 }
//   ctx->commandList (+0x10) = [[job+0x90]+0x30] is the live ID3D12GraphicsCommandList our renderer records into.
//
// Our renderer is that fn. It consumes the SAME extractor output the stock executor consumes: descriptions
// inserted as InsertVariant {mDescription, mTag} are turned by the extractors (BatchActor, chunk, nametag,
// particle, sky, clouds, weather) into Encoder::submit draw items, i.e. the Frame render items:
//   Frame+0xDC57E8 u32 item count                      (Frame.h kItemCount; executor loop bound at job+0x33C, 0xe822202)
//   Frame+0x14700  u64[] sort keys                     (0xe822220, 0xe82240d)
//   Frame+0x94700  u16[] sort values (item index)      (0xe822414, 0xbc616b5)
//   Frame+0xB4700 item headers, stride 0x80            (0xe82241f/0xe82241c; header base [rbx+0x590])
//   header+0x20 stateFlags, +0x62 submitFlags, +0x7A occlusionQuery  (executor reads: 0xe8226b3, 0xe8226fa, 0xe8226c7)
//   Frame+0x14300 + handle*4 occlusion results         (0xe82270b)
//   custom-item slot: [0]=fn, [8]=user                 (0xe822426, 0xe82245d; written by submitCustom at 0xbc61645, 0xbc6164c)
//
// All offsets are reverse-engineered constants for Minecraft 1.26.62.01, cited with proof RVAs above, and
// pinned by static_asserts here or in src/sdk/mc/deps/bgfx/Frame.h: a layout change fails the build
// (fail fast, no null guards, no SEH - same style as RewriteSubmit).
//
// Nothing in this file hooks the game: no detour, no registry entry, no HookManager edit, no Sigs.json
// change, no CMake edit. A queue point that calls submitCustom(viewId, render, user) plus a build and an
// in-game run are the remaining step (see docs/progress/oc_U-EQ6c.md CLOSES?).


namespace bgfx {
struct Frame;
} // namespace bgfx

namespace render::takeover {

// 0x18-byte context the executor builds for every custom item at job+0x3B0 (instructions 0xe822441..0xe822456).
struct ExecCtx {
    const void* tag;       // +0x00 const pointer to rodata 0xF4EDE00 (lea 0xe822441). ripscan of 0xF4EDE00
                           // returns this lea as its single xref; no .text instruction reads 0xF4EDE00, so the
                           // object's meaning is not decoded statically [?]. Our renderer never interprets it.
    void* user;            // +0x08 user data: rsi = job field [rbx+0xB0], reloaded by the path tail at
                           // 0xe822474 on every iteration [I].
    void* commandList;     // +0x10 [[job+0x90]+0x30] ID3D12GraphicsCommandList* (0xe822436, 0xe82243d, 0xe822456) [V]
};
static_assert(sizeof(ExecCtx) == 0x18, "ExecCtx must be the 0x18-byte context the executor builds");
static_assert(offsetof(ExecCtx, tag) == 0x00, "ExecCtx::tag at +0x00");
static_assert(offsetof(ExecCtx, user) == 0x08, "ExecCtx::user at +0x08");
static_assert(offsetof(ExecCtx, commandList) == 0x10, "ExecCtx::commandList at +0x10");

// Sort-key classes (executor dispatch at 0xe822242 after the bits-52..53 mask at 0xe822235;
// key build at 0xbc61697..0xbc616a1).
constexpr uint64_t kKeyCustomBit = 0x20000000000000ull; // bit 53: custom item class
constexpr uint64_t kKeyViewShift = 54;                    // view id, bits 54..61
constexpr uint64_t kKeySeqShift = 32;                     // seq & 0xFFFFF, bits 32..51
constexpr uint64_t kKeySeqMask = 0x000FFFFF00000000ull; // (seq & 0xFFFFF) << 32

// Callback the executor invokes for a custom item: fn(user, ctx).
// Called as rcx = user (slot[1] = submitCustom's user arg, 0xe82245d), rdx = &ctx (0xe822461)
// through the CFG dispatch thunk at [0xF99FFA0] (0xe822468).
using RenderFn = void(void* user, ExecCtx* ctx);

// Read-only visitor for one render item (extractor output slot). No writes to the game.
struct RenderItemView {
    const bgfx::Frame* frame;
    uint32_t index;   // submission index
    uint64_t key;     // Frame+0x14700 + index*8
    uint16_t value;   // Frame+0x94700 + index*2 (the executor sorts slots by key)
    const uint8_t* header; // Frame+0xB4700 + index*0x80
};
using ItemVisitor = void(void* user, RenderItemView item);

// Walk the extractor output: every render item submitted this frame, in submission index order.
// The executor re-sorts by key before consuming; a demo renderer sorts (index, value) pairs by key
// and visits headers in that order. Returns the number of items visited.
// Fail fast: no null guards - a null frame crashes here exactly as the original code would.
size_t walkRenderItems(const bgfx::Frame* frame, void* user, ItemVisitor* visit);

// Our renderer: the fn passed to Encoder::submitCustom(viewId, render, user).
// user = a context block built by the queue point; it must carry the Frame*, because ctx itself has no
// Frame/job back-pointer - only tag+0x00, user+0x08, commandList+0x10.
// Walks the same extractor output the stock executor consumes (count/keys/values/headers above) and
// re-records it through ctx->commandList. The body and the queue point that submits the custom item are
// intentionally unwired here: no build or in-game run is performed by this unit.
void render(void* user, ExecCtx* ctx);

} // namespace render::takeover
