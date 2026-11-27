#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_66e56a0, reverse-engineered from the disassembly
// of [0x66e56a0, 0x66e57d7), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e56a0_rcx {
    std::uint8_t pad0x00[0x18];   // +0x00..+0x17 padding (no observed access)
    std::uint8_t f18;   // // +0x18: std::uint8_t R  (R/W cited: 0x66e576a:R)
    std::uint8_t pad0x19[0xf];   // +0x19..+0x27 padding (no observed access)
    std::uint64_t f28;   // // +0x28: std::uint64_t R  (R/W cited: 0x66e5776:R)
    std::uint8_t pad0x30[0x28];   // +0x30..+0x57 padding (no observed access)
    std::uint8_t f58;   // // +0x58: std::uint8_t R  (R/W cited: 0x66e5764:R)
    std::uint8_t pad0x59[0xf7];   // +0x59..+0x14f padding (no observed access)
    void* f150;   // // +0x150: void* R // vtable-call slot(s) slot 1  (R/W cited: 0x66e56ee:R, 0x66e56fa:R)
    std::uint64_t f158;   // // +0x158: std::uint64_t R  (R/W cited: 0x66e5701:R)
    std::uint8_t pad0x160[0x18];   // +0x160..+0x177 padding (no observed access)
    void* f178;   // // +0x178: void* R // vtable-call slot(s) slot 0,slot 2  (R/W cited: 0x66e56b7:R)
    std::uint8_t f180;   // // +0x180: std::uint8_t R  (R/W cited: 0x66e56ae:R)
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e56a0_r14 {
    std::uint64_t f0[2];   // // +0x00: std::uint64_t[2] W  (R/W cited: 0x66e5758:W)
    std::uint64_t f10;   // // +0x10: std::uint64_t W  (R/W cited: 0x66e575c:W)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e56a0_rax {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x66e56cc:R, 0x66e5731:R)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x66e56e1:R, 0x66e5746:R)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e56a0_rbx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 0,slot 2  (R/W cited: 0x66e571f:R)
    std::uint8_t pad0x10[0x8];   // +0x10..+0x17 padding (no observed access)
    std::uint8_t f18;   // // +0x18: std::uint8_t R  (R/W cited: 0x66e5719:R)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e56a0_rdi {
    void* f0[2];   // // +0x00: void*[2] R/W // vtable-call slot(s) slot 0,slot 1,slot 5  (R/W cited: 0x66e56c9:R, 0x66e56de:R, 0x66e572e:R, 0x66e5743:R, 0x66e576e:R, 0x66e57a6:W)
    // // +0x08: std::uint32_t RW  (R/W cited: 0x66e56c3:RW, 0x66e5728:RW)   [subsumed by earlier field; overlapping access, no separate field]
    // // +0x0c: std::uint32_t RW  (R/W cited: 0x66e56d8:RW, 0x66e573d:RW)   [subsumed by earlier field; overlapping access, no separate field]
    std::uint64_t f10;   // // +0x10: std::uint64_t W  (R/W cited: 0x66e57a9:W)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e56a0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // // +0x20: std::uint64_t W  (R/W cited: 0x66e57bd:W)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_66e56a0_rcx, f18) == 0x18, "sub_0x66e56a0 rcx+0x18 field");
static_assert(offsetof(sub_66e56a0_rcx, f28) == 0x28, "sub_0x66e56a0 rcx+0x28 field");
static_assert(offsetof(sub_66e56a0_rcx, f58) == 0x58, "sub_0x66e56a0 rcx+0x58 field");
static_assert(offsetof(sub_66e56a0_rcx, f150) == 0x150, "sub_0x66e56a0 rcx+0x150 field");
static_assert(offsetof(sub_66e56a0_rcx, f158) == 0x158, "sub_0x66e56a0 rcx+0x158 field");
static_assert(offsetof(sub_66e56a0_rcx, f178) == 0x178, "sub_0x66e56a0 rcx+0x178 field");
static_assert(offsetof(sub_66e56a0_rcx, f180) == 0x180, "sub_0x66e56a0 rcx+0x180 field");
static_assert(sizeof(sub_66e56a0_rcx) >= 0x181, "sub_0x66e56a0 rcx sizeof lower bound");

static_assert(offsetof(sub_66e56a0_r14, f0) == 0x0, "sub_0x66e56a0 r14+0x0 field");
static_assert(offsetof(sub_66e56a0_r14, f10) == 0x10, "sub_0x66e56a0 r14+0x10 field");
static_assert(sizeof(sub_66e56a0_r14) >= 0x18, "sub_0x66e56a0 r14 sizeof lower bound");

static_assert(offsetof(sub_66e56a0_rax, f0) == 0x0, "sub_0x66e56a0 rax+0x0 field");
static_assert(offsetof(sub_66e56a0_rax, f8) == 0x8, "sub_0x66e56a0 rax+0x8 field");
static_assert(sizeof(sub_66e56a0_rax) >= 0x10, "sub_0x66e56a0 rax sizeof lower bound");

static_assert(offsetof(sub_66e56a0_rbx, f8) == 0x8, "sub_0x66e56a0 rbx+0x8 field");
static_assert(offsetof(sub_66e56a0_rbx, f18) == 0x18, "sub_0x66e56a0 rbx+0x18 field");
static_assert(sizeof(sub_66e56a0_rbx) >= 0x19, "sub_0x66e56a0 rbx sizeof lower bound");

static_assert(offsetof(sub_66e56a0_rdi, f0) == 0x0, "sub_0x66e56a0 rdi+0x0 field");
static_assert(offsetof(sub_66e56a0_rdi, f10) == 0x10, "sub_0x66e56a0 rdi+0x10 field");
static_assert(sizeof(sub_66e56a0_rdi) >= 0x18, "sub_0x66e56a0 rdi sizeof lower bound");

static_assert(offsetof(sub_66e56a0_rsp, f20) == 0x20, "sub_0x66e56a0 rsp+0x20 field");
static_assert(sizeof(sub_66e56a0_rsp) >= 0x28, "sub_0x66e56a0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0x66e56a0  push r15; 0x66e56a2  push r14; 0x66e56a4  push rsi; 0x66e56a5  push rdi
uintptr_t sub_66e56a0(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
