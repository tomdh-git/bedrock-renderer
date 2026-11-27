#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_1126680, reverse-engineered from the disassembly
// of [0x1126680, 0x112677e), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_1126680_rcx {
    void* f0;   // +0x00: void* R  (R cited: 0x112668b:R)   gradient object: begin pointer
    void* f8;   // +0x08: void* R  (R cited: 0x112668e:R)   gradient object: end pointer
    std::uint8_t pad0x10[0x8];   // +0x10..+0x17 padding (no observed access)
    float f18;   // +0x18: float R  (R cited: 0x1126717:R)  gradient wrap bound low
    float f1c;   // +0x1c: float R  (R cited: 0x112671c:R)  gradient wrap bound high
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_1126680_rdx {
    float f0[2];   // +0x00: float[2] R/W  (R/W cited: 0x11266a7:W, 0x11266b3:W, 0x112670c:R, 0x1126744:W, 0x1126772:W)  output color
    // +0x04: std::uint64_t[2] R  (R/W cited: 0x11266a3:R, 0x1126710:R)   [subsumed by earlier field; overlapping access, no separate field]
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding (no observed access)
    std::uint8_t pad0x10[0x4];   // +0x10..+0x13 padding (no observed access)
    std::uint8_t f14;   // +0x14: std::uint8_t R  (R cited: 0x11266bb:R)
};
#pragma pack(pop)

// Struct for base register r8 (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_1126680_r8 {
    float f0[2];   // +0x00: float[2] R  (R cited: 0x11266af:R, 0x11266e4:R)  end-key/end-color record
    // +0x04: std::uint64_t[2] R  (R/W cited: 0x11266f3:R)   [subsumed by earlier field; overlapping access, no separate field]
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding (no observed access)
    std::uint8_t pad0x10[0x4];   // +0x10..+0x13 padding to sizeof lower bound 0x14
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_1126680_rsp {
    std::uint8_t f0;   // +0x00: std::uint8_t R/W  (R/W cited: 0x1126684:W, 0x1126775:R)
    std::uint8_t pad0x01[0x3f];   // +0x01..+0x3f padding (no observed access)
    std::uint8_t f40;   // +0x40: std::uint8_t R  (R cited: 0x1126705:R)  interpolate flag
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_1126680_rcx, f0) == 0x0, "sub_0x1126680 rcx+0x0 field");
static_assert(offsetof(sub_1126680_rcx, f8) == 0x8, "sub_0x1126680 rcx+0x8 field");
static_assert(offsetof(sub_1126680_rcx, f18) == 0x18, "sub_0x1126680 rcx+0x18 field");
static_assert(offsetof(sub_1126680_rcx, f1c) == 0x1c, "sub_0x1126680 rcx+0x1c field");
static_assert(sizeof(sub_1126680_rcx) >= 0x20, "sub_0x1126680 rcx sizeof lower bound");

static_assert(offsetof(sub_1126680_rdx, f0) == 0x0, "sub_0x1126680 rdx+0x0 field");
static_assert(offsetof(sub_1126680_rdx, f14) == 0x14, "sub_0x1126680 rdx+0x14 field");
static_assert(sizeof(sub_1126680_rdx) >= 0x15, "sub_0x1126680 rdx sizeof lower bound");

static_assert(offsetof(sub_1126680_r8, f0) == 0x0, "sub_0x1126680 r8+0x0 field");
static_assert(sizeof(sub_1126680_r8) >= 0x14, "sub_0x1126680 r8 sizeof lower bound");

static_assert(offsetof(sub_1126680_rsp, f0) == 0x0, "sub_0x1126680 rsp+0x0 field");
static_assert(offsetof(sub_1126680_rsp, f40) == 0x40, "sub_0x1126680 rsp+0x40 field");
static_assert(sizeof(sub_1126680_rsp) >= 0x41, "sub_0x1126680 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - lifted from [0x1126680, 0x112677e):
// 0x1126680  sub rsp,0x18; 0x1126684  movaps [rsp],xmm6; 0x1126688  mov rax,rdx; 0x112668b  mov rdx,[rcx]
// rcx = self (gradient object), rdx = out (color float4, returned in rax),
// xmm2 = lookup value x (never written), r9 = default-color pointer (used iff begin == end),
// [rsp+0x40] = interpolate flag (0 => clamp out-of-range to last color).
uintptr_t sub_1126680(void* self, void* out, float x, void* r9src, uint8_t interpolateFlag);

} // namespace native::helpers
