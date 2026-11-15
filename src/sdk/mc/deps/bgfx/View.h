#pragma once

namespace bgfx {

// Per-view record inside bgfx::Context (docs/BGFX_MAP.md 6dd, live-verified 6dd): Context* = *(base + 0x12AE1748).
// record = Context + 0x1EAB090 + viewId * 0x140. Filled each frame by the Scene/HUD task body 0x568CD90.
struct ViewRecord {
    static constexpr uintptr_t kBase = 0x1EAB090;
    static constexpr size_t kStride = 0x140;
    static constexpr uintptr_t kRectXY = 0x00;       // [V] i16 x, y (clamped >= 0)
    static constexpr uintptr_t kRectWH = 0x04;       // [V] u16 w, h (live 1920x1137)
    static constexpr uintptr_t kView = 0x10;         // [V] float4x4, identity in live frames (camera-relative rendering)
    static constexpr uintptr_t kProj = 0x50;         // [V] float4x4, perspective: m00 = 1/(aspect*tan(fov/2)), m11 = 1/tan(fov/2), m22=-1, m23=-1, m32=-0.025
    static constexpr uintptr_t kPrevA = 0x90;        // [I] float4x4 (previous-frame pair)
    static constexpr uintptr_t kPrevB = 0xD0;        // [I] float4x4
    static constexpr uintptr_t kVec4 = 0x110;        // [I] 16 bytes (viewport / clear)
    static constexpr uintptr_t kSortMode = 0x122;    // [V] u8: 1 Sequence, 2 DepthAscending, 3 DepthDescending (read by Encoder::submit)
    static constexpr uintptr_t kSeqCounters = 0x1EAAC60; // [V] u32[viewId], Context-relative: lock xadd in submit mode 1

    // The full per-view struct starts 0x10 earlier, at the array base Context+0x1EAB080 (6q: +0x00 clear RGBA, +0x08 clear depth,
    // +0x130 u16 framebuffer). The pass bodies (ScreenDraw 0xbc04dc0, DirectionalLightingPass 0xbc2cd20; 6hs) address views from that
    // base and write rect +0x10, size +0x14, four mat4 at +0x20/+0x60/+0xA0/+0xE0, 16 bytes at +0x120 and the sort-mode byte at +0x132:
    // exactly this record's offsets + 0x10. That settles the 6em "+0x10 vs +0x20" conflict: same layout, two bases.
    static constexpr uintptr_t kArrayBase = 0x1EAB080;
    static_assert(kBase == kArrayBase + 0x10);
    static_assert(kView + 0x10 == 0x20 && kProj + 0x10 == 0x60 && kPrevA + 0x10 == 0xA0 && kPrevB + 0x10 == 0xE0);
    static_assert(kVec4 + 0x10 == 0x120 && kSortMode + 0x10 == 0x132);
};

} // namespace bgfx
