#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_56b66f0, reverse-engineered from the disassembly
// of [0x56b66f0, 0x56b67ec), Minecraft Windows 1.26.62.01. [proven] offsets/widths
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.

// Struct for base register rcx (the 'self' argument, dereferenced in this function)
// +0x00: head pointer of a walked range (R)
// +0x08: end   pointer of the walked range (R)
// +0x10: extra pointer/size field (R/W)
#pragma pack(push, 1)
struct sub_56b66f0_rcx {
    void* f0;   // +0x00: void* R  (R cited: 0x56b66fe:R, 0x56b6782:R; W cited: 0x56b67b8:W as part of 16-byte store)
    void* f8;   // +0x08: void* R  (R cited: 0x56b670d:R; W cited: 0x56b67b8:W as part of 16-byte store)
    void* f10;  // +0x10: void* R/W (R cited: 0x56b6785:R; W cited: 0x56b67bb:W)
};
#pragma pack(pop)

// Struct for base register r14 (points into an entry at entry+0xe8)
// +0x00: buffer pointer (R at 0x56b674d, W as part of 16-byte store at 0x56b6725)
// +0x10: size/count field (W at 0x56b6729)
#pragma pack(push, 1)
struct sub_56b66f0_r14 {
    void* f0;   // +0x00: void* R/W (R/W cited: 0x56b674d:R, 0x56b6725:W as part of 16-byte store)
    void* f8;   // +0x08: void* W (W cited: 0x56b6725:W as part of 16-byte store)
    std::uint64_t f10;   // +0x10: std::uint64_t W (W cited: 0x56b6729:W)
};
#pragma pack(pop)

// Struct for base register rdi (a walked entry, stride 0x128)
// +0xe8:  buffer pointer (R via r14 = rdi+0xe8 at 0x56b674d)
// +0xf8:  size/end field (R at 0x56b6755; W via r14+0x10 == rdi+0xf8 at 0x56b6729)
// +0x100: flag byte compared to 1 (R at 0x56b673d)
#pragma pack(push, 1)
struct sub_56b66f0_rdi {
    std::uint8_t pad0x00[0xe8];   // +0x00..+0xe7 padding (no observed access)
    void* f_e8;                   // +0xe8: void* R  (R cited: 0x56b6746:lea / 0x56b674d:R via r14)
    std::uint8_t pad0xf0[0x8];    // +0xf0..+0xf7 padding (no observed access)
    std::uint64_t f_f8;           // +0xf8: std::uint64_t R (R cited: 0x56b6755:R; W via r14+0x10)
    std::uint8_t f_100;           // +0x100: std::uint8_t R (R cited: 0x56b673d:R)
};
#pragma pack(pop)

// Struct for base register rsp (spill slots)
// +0x20: scratch slot (W at 0x56b67d2)
// +0x30: xmm6 spill slot (W at 0x56b66f9, R at 0x56b67c3)
#pragma pack(push, 1)
struct sub_56b66f0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;            // +0x20: std::uint64_t W (W cited: 0x56b67d2:W)
    std::uint8_t pad0x28[0x8];    // +0x28..+0x2f padding (no observed access)
    std::uint8_t f30[16];         // +0x30: 16-byte xmm6 slot (W cited: 0x56b66f9:W, R cited: 0x56b67c3:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_56b66f0_rcx, f0) == 0x0, "sub_0x56b66f0 rcx+0x0 field");
static_assert(offsetof(sub_56b66f0_rcx, f8) == 0x8, "sub_0x56b66f0 rcx+0x8 field");
static_assert(offsetof(sub_56b66f0_rcx, f10) == 0x10, "sub_0x56b66f0 rcx+0x10 field");
static_assert(sizeof(sub_56b66f0_rcx) >= 0x18, "sub_0x56b66f0 rcx sizeof lower bound");

static_assert(offsetof(sub_56b66f0_r14, f0) == 0x0, "sub_0x56b66f0 r14+0x0 field");
static_assert(offsetof(sub_56b66f0_r14, f10) == 0x10, "sub_0x56b66f0 r14+0x10 field");
static_assert(sizeof(sub_56b66f0_r14) >= 0x18, "sub_0x56b66f0 r14 sizeof lower bound");

static_assert(offsetof(sub_56b66f0_rdi, f_e8) == 0xe8, "sub_0x56b66f0 rdi+0xe8 field");
static_assert(offsetof(sub_56b66f0_rdi, f_f8) == 0xf8, "sub_0x56b66f0 rdi+0xf8 field");
static_assert(offsetof(sub_56b66f0_rdi, f_100) == 0x100, "sub_0x56b66f0 rdi+0x100 field");
static_assert(sizeof(sub_56b66f0_rdi) >= 0x101, "sub_0x56b66f0 rdi sizeof lower bound");

static_assert(offsetof(sub_56b66f0_rsp, f20) == 0x20, "sub_0x56b66f0 rsp+0x20 field");
static_assert(offsetof(sub_56b66f0_rsp, f30) == 0x30, "sub_0x56b66f0 rsp+0x30 field");
static_assert(sizeof(sub_56b66f0_rsp) >= 0x40, "sub_0x56b66f0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI). rcx = self (a0); return value in rax. The exact
// semantic type of the return is [open]; it is the value sub_e935700 leaves in rax
// on the free path, and 0 on the empty-input path. Argument is the range object.
uintptr_t sub_56b66f0(void* self);   // signature: rcx=self, return=rax (uintptr_t)

} // namespace native::helpers
