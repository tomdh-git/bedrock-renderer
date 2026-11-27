#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_c2981f0, reverse-engineered from the disassembly
// of [0xc2981f0, 0xc298320), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c2981f0_rcx {
    std::uint8_t pad0x00[0x30];   // +0x00..+0x2f padding (no observed access)
    std::uint64_t f30;   // // +0x30: std::uint64_t R  (R/W cited: 0xc2981fc:R)
    void* f38;   // // +0x38: void* R  (R/W cited: 0xc298200:R)
    std::uint8_t pad0x40[0x8];   // +0x40..+0x47 padding (no observed access)
    std::uint8_t f48;   // // +0x48: std::uint8_t R  (R/W cited: 0xc2982f9:R)
    std::uint8_t pad0x49[0x7];   // +0x49..+0x4f padding (no observed access)
    std::uint8_t f50;   // // +0x50: std::uint8_t R  (R/W cited: 0xc298302:R)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c2981f0_rdx {
    std::uint8_t f0;   // // +0x00: std::uint8_t W  (R/W cited: 0xc29831a:W)
    std::uint8_t pad0x01[0x3];   // +0x01..+0x03 padding (no observed access)
    std::uint8_t f4;   // // +0x04: std::uint8_t W  (R/W cited: 0xc29830a:W)
};
#pragma pack(pop)

// Struct for base register r8 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c2981f0_r8 {
    std::uint64_t f0;   // // +0x00: std::uint64_t R  (R/W cited: 0xc298217:R)
};
#pragma pack(pop)

// Struct for base register rsi (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c2981f0_rsi {
    std::uint32_t f0;   // // +0x00: std::uint32_t R  (R/W cited: 0xc298317:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_c2981f0_rcx, f30) == 0x30, "sub_0xc2981f0 rcx+0x30 field");
static_assert(offsetof(sub_c2981f0_rcx, f38) == 0x38, "sub_0xc2981f0 rcx+0x38 field");
static_assert(offsetof(sub_c2981f0_rcx, f48) == 0x48, "sub_0xc2981f0 rcx+0x48 field");
static_assert(offsetof(sub_c2981f0_rcx, f50) == 0x50, "sub_0xc2981f0 rcx+0x50 field");
static_assert(sizeof(sub_c2981f0_rcx) >= 0x51, "sub_0xc2981f0 rcx sizeof lower bound");

static_assert(offsetof(sub_c2981f0_rdx, f0) == 0x0, "sub_0xc2981f0 rdx+0x0 field");
static_assert(offsetof(sub_c2981f0_rdx, f4) == 0x4, "sub_0xc2981f0 rdx+0x4 field");
static_assert(sizeof(sub_c2981f0_rdx) >= 0x5, "sub_0xc2981f0 rdx sizeof lower bound");

static_assert(offsetof(sub_c2981f0_r8, f0) == 0x0, "sub_0xc2981f0 r8+0x0 field");
static_assert(sizeof(sub_c2981f0_r8) >= 0x8, "sub_0xc2981f0 r8 sizeof lower bound");

static_assert(offsetof(sub_c2981f0_rsi, f0) == 0x0, "sub_0xc2981f0 rsi+0x0 field");
static_assert(sizeof(sub_c2981f0_rsi) >= 0x4, "sub_0xc2981f0 rsi sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0xc2981f0  push r15; 0xc2981f2  push r14; 0xc2981f4  push r12; 0xc2981f6  push rsi
uintptr_t sub_c2981f0(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
