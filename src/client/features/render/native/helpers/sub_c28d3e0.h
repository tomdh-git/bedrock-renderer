#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_c28d3e0 (= BgfxFrameBuilder::endFrame), reverse-engineered
// from the disassembly of [0xc28d3e0, 0xc28d508). Offsets and widths are [proven] straight
// from the instruction operands; field NAMES and MEANINGS are [open] (chosen below to match
// the access pattern, never moved).
// One struct per base register that is dereferenced. The structs are packed (#pragma pack(1))
// so every declared field sits exactly at its observed offset and offsetof() matches it.
// The real object may have compiler-inserted alignment padding, so sizeof is a lower bound,
// not an exact size.

// Struct for base register rcx (the `self` / BgfxFrameBuilder pointer) [proven base]
// Accessed offsets: +0x118 (list 1 head), +0x1c0 (list 2 head).
#pragma pack(push, 1)
struct sub_c28d3e0_rcx {
    std::uint8_t pad0x00[0x118];
    void* list1Head;   // +0x118: void* R  (R/W cited: 0xc28d3f3:R, 0xc28d3fa:R)
    std::uint8_t pad0x120[0xa0];
    void* list2Head;   // +0x1c0: void* R  (R/W cited: 0xc28d481:R)
};
#pragma pack(pop)

// Struct for base register rbx/rdi (a frame-list entry) [proven base]
// Both loops walk entries of this layout: +0x00 next pointer, +0x18 sub-list start,
// +0x20 sub-list end, +0x30 type byte (== 1 means the entry has a sub-list to release).
#pragma pack(push, 1)
struct sub_c28d3e0_rbx {
    void* next;        // +0x00: void* R  (R/W cited: 0xc28d423:R, 0xc28d4b3:R)
    std::uint8_t pad0x08[0x10];
    void* subStart;    // +0x18: void* R  (R/W cited: 0xc28d410:R, 0xc28d431:R, 0xc28d4a0:R, 0xc28d4c1:R)
    void* subEnd;      // +0x20: void* R  (R/W cited: 0xc28d43a:R, 0xc28d4ca:R)
    std::uint8_t pad0x28[0x8];
    std::uint8_t type; // +0x30: std::uint8_t R/W  (R/W cited: 0xc28d41f:W, 0xc28d42b:R, 0xc28d4af:W, 0xc28d4bb:R)
};
#pragma pack(pop)

// Struct for base register r14 (a sub-list 1 entry, stride 0x18) [proven base]
// Accessed offsets: +0x08 (refcounted object, weak refcount at +0xC), +0x10 (destroy target).
#pragma pack(push, 1)
struct sub_c28d3e0_r14 {
    std::uint8_t pad0x00[0x8];
    void* objA;        // +0x08: void* R  (R/W cited: 0xc28d463:R)
    void* objB;        // +0x10: void* R  (R/W cited: 0xc28d449:R)
};
#pragma pack(pop)

// sizeof lower bounds: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_c28d3e0_rcx, list1Head) == 0x118, "sub_0xc28d3e0 rcx+0x118 field");
static_assert(offsetof(sub_c28d3e0_rcx, list2Head) == 0x1c0, "sub_0xc28d3e0 rcx+0x1c0 field");
static_assert(sizeof(sub_c28d3e0_rcx) >= 0x1c8, "sub_0xc28d3e0 rcx sizeof lower bound");

static_assert(offsetof(sub_c28d3e0_rbx, next) == 0x0, "sub_0xc28d3e0 rbx/rdi+0x0 field");
static_assert(offsetof(sub_c28d3e0_rbx, subStart) == 0x18, "sub_0xc28d3e0 rbx/rdi+0x18 field");
static_assert(offsetof(sub_c28d3e0_rbx, subEnd) == 0x20, "sub_0xc28d3e0 rbx/rdi+0x20 field");
static_assert(offsetof(sub_c28d3e0_rbx, type) == 0x30, "sub_0xc28d3e0 rbx/rdi+0x30 field");
static_assert(sizeof(sub_c28d3e0_rbx) >= 0x31, "sub_0xc28d3e0 rbx/rdi sizeof lower bound");

static_assert(offsetof(sub_c28d3e0_r14, objA) == 0x8, "sub_0xc28d3e0 r14+0x8 field");
static_assert(offsetof(sub_c28d3e0_r14, objB) == 0x10, "sub_0xc28d3e0 r14+0x10 field");
static_assert(sizeof(sub_c28d3e0_r14) >= 0x18, "sub_0xc28d3e0 r14 sizeof lower bound");

// Signature (x64 Microsoft ABI): RCX = self (BgfxFrameBuilder*). Return: void (RAX is dead
// at every ret in [0xc28d3e0, 0xc28d508); no instruction writes a defined return value).
void sub_c28d3e0(sub_c28d3e0_rcx* self);

} // namespace native::helpers
