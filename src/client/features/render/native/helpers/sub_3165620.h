#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_3165620, reverse-engineered from the disassembly
// of [0x3165620, 0x3165757), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_3165620_rcx {
    std::uint8_t pad0x00[0x68];   // +0x00..+0x67 padding (no observed access)
    std::uint64_t f68;   // // +0x68: std::uint64_t R  (R/W cited: 0x316566f:R)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_3165620_rdx {
    std::uint8_t pad0x00[0x4];   // +0x00..+0x03 padding (no observed access)
    std::uint8_t f4;   // // +0x04: std::uint8_t R  (R/W cited: 0x3165646:R, 0x3165690:R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_3165620_rsp {
    std::uint8_t pad0x00[0x24];   // +0x00..+0x23 padding (no observed access)
    std::uint8_t f24;   // // +0x24: std::uint8_t R/W  (R/W cited: 0x3165655:W, 0x316565a:R)
    std::uint8_t pad0x25[0x1];   // +0x25..+0x25 padding (no observed access)
    std::uint8_t f26;   // // +0x26: std::uint8_t R/W  (R/W cited: 0x316569f:W, 0x31656a4:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_3165620_rcx, f68) == 0x68, "sub_0x3165620 rcx+0x68 field");
static_assert(sizeof(sub_3165620_rcx) >= 0x70, "sub_0x3165620 rcx sizeof lower bound");

static_assert(offsetof(sub_3165620_rdx, f4) == 0x4, "sub_0x3165620 rdx+0x4 field");
static_assert(sizeof(sub_3165620_rdx) >= 0x5, "sub_0x3165620 rdx sizeof lower bound");

static_assert(offsetof(sub_3165620_rsp, f24) == 0x24, "sub_0x3165620 rsp+0x24 field");
static_assert(offsetof(sub_3165620_rsp, f26) == 0x26, "sub_0x3165620 rsp+0x26 field");
static_assert(sizeof(sub_3165620_rsp) >= 0x27, "sub_0x3165620 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0x3165620  push rsi; 0x3165621  push rdi; 0x3165622  sub rsp,0x28; 0x3165626  mov rsi,rcx
uintptr_t sub_3165620(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
