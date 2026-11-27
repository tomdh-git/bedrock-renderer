#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_67576c0, reverse-engineered from the disassembly
// of [0x67576c0, 0x67577b8), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67576c0_rcx {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x67576ce:R, 0x6757741:R)
    void* f8;   // // +0x08: void* R  (R/W cited: 0x67576d1:R) range-end pointer of the element array
    std::uint8_t pad0x10[0x8];   // +0x10..+0x17 padding (no observed access)
    void* f18[2];   // // +0x18: void*[2] R/W  (R/W cited: 0x6757794:R, 0x67577a0:W)
    void* f28;   // // +0x28: void* W  (R/W cited: 0x67577a4:W)
};
#pragma pack(pop)

// Struct for base register r15 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67576c0_r15 {
    std::uint8_t pad0x00[0x10];   // +0x00..+0x0f padding (no observed access)
    std::uint8_t f10;   // // +0x10: std::uint8_t W  (R/W cited: 0x6757752:W)
    std::uint8_t pad0x11[0x7];   // +0x11..+0x17 padding (no observed access)
    void* f18;   // // +0x18: void* R // vtable-call slot(s) slot 0,slot 1,slot 2  (R/W cited: 0x675771a:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67576c0_rax {
    void* f0;   // // +0x00: void* R/RW/W // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x67576f9:RW, 0x675771e:W, 0x6757744:R, 0x6757769:R)
    // // +0x01: std::uint8_t R  (R/W cited: 0x6757704:R)   [subsumed by earlier field; overlapping access, no separate field]
    // // +0x04: std::uint64_t W  (R/W cited: 0x6757724:W)   [subsumed by earlier field; overlapping access, no separate field]
    std::uint64_t f8;   // // +0x08: std::uint64_t R  (R/W cited: 0x6757782:R)
    // // +0x0c: std::uint8_t W  (R/W cited: 0x675772c:W)   [subsumed by earlier field; overlapping access, no separate field]
    void* f10;   // // +0x10: void* R/W // vtable-call slot(s) slot 0,slot 5  (R/W cited: 0x6757730:R, 0x6757734:W)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67576c0_rbx {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 3  (R/W cited: 0x675770e:R)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 0,slot 5  (R/W cited: 0x67576ed:R, 0x6757711:R)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67576c0_rdi {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x6757766:R, 0x675777f:R)
    std::uint32_t f8;   // // +0x08: std::uint32_t RW  (R/W cited: 0x675775c:RW)
    std::uint32_t fc;   // // +0x0c: std::uint32_t RW  (R/W cited: 0x6757775:RW)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_67576c0_rcx, f0) == 0x0, "sub_0x67576c0 rcx+0x0 field");
static_assert(offsetof(sub_67576c0_rcx, f8) == 0x8, "sub_0x67576c0 rcx+0x8 field");
static_assert(offsetof(sub_67576c0_rcx, f18) == 0x18, "sub_0x67576c0 rcx+0x18 field");
static_assert(offsetof(sub_67576c0_rcx, f28) == 0x28, "sub_0x67576c0 rcx+0x28 field");
static_assert(sizeof(sub_67576c0_rcx) >= 0x30, "sub_0x67576c0 rcx sizeof lower bound");

static_assert(offsetof(sub_67576c0_r15, f10) == 0x10, "sub_0x67576c0 r15+0x10 field");
static_assert(offsetof(sub_67576c0_r15, f18) == 0x18, "sub_0x67576c0 r15+0x18 field");
static_assert(sizeof(sub_67576c0_r15) >= 0x20, "sub_0x67576c0 r15 sizeof lower bound");

static_assert(offsetof(sub_67576c0_rax, f0) == 0x0, "sub_0x67576c0 rax+0x0 field");
static_assert(offsetof(sub_67576c0_rax, f8) == 0x8, "sub_0x67576c0 rax+0x8 field");
static_assert(offsetof(sub_67576c0_rax, f10) == 0x10, "sub_0x67576c0 rax+0x10 field");
static_assert(sizeof(sub_67576c0_rax) >= 0x18, "sub_0x67576c0 rax sizeof lower bound");

static_assert(offsetof(sub_67576c0_rbx, f0) == 0x0, "sub_0x67576c0 rbx+0x0 field");
static_assert(offsetof(sub_67576c0_rbx, f8) == 0x8, "sub_0x67576c0 rbx+0x8 field");
static_assert(sizeof(sub_67576c0_rbx) >= 0x10, "sub_0x67576c0 rbx sizeof lower bound");

static_assert(offsetof(sub_67576c0_rdi, f0) == 0x0, "sub_0x67576c0 rdi+0x0 field");
static_assert(offsetof(sub_67576c0_rdi, f8) == 0x8, "sub_0x67576c0 rdi+0x8 field");
static_assert(offsetof(sub_67576c0_rdi, fc) == 0xc, "sub_0x67576c0 rdi+0xc field");
static_assert(sizeof(sub_67576c0_rdi) >= 0x10, "sub_0x67576c0 rdi sizeof lower bound");

// Signature (x64 Microsoft ABI) - [proven] from the prologue: rcx is the 'this' pointer
// (copied to rsi at 0x67576cb). Return value is whatever RAX holds at ret; the original
// does not explicitly set it on the exit path, so it is treated as don't-care / 0 here.
// 0x67576c0  push r15; 0x67576c2  push r14; 0x67576c4  push rsi; 0x67576c5  push rdi
uintptr_t sub_67576c0(void* self);   // 'this' = self (rcx), return value don't-care

} // namespace native::helpers
