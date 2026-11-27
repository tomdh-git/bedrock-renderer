#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_567a7b0, reverse-engineered from the disassembly
// of [0x567a7b0, 0x567a8e8), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_567a7b0_rcx {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 1  (R/W cited: 0x567a7d2:R, 0x567a7dc:R, 0x567a81a:R)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 4  (R/W cited: 0x567a81d:R, 0x567a884:R)
    std::uint8_t pad0x10[0x9];   // +0x10..+0x18 padding (no observed access)
    std::uint8_t f19;   // // +0x19: std::uint8_t R  (R/W cited: 0x567a82e:R, 0x567a86e:R)
    std::uint8_t pad0x1a[0x6];   // +0x1a..+0x1f padding (no observed access)
    std::uint8_t f20;   // // +0x20: std::uint8_t R  (R/W cited: 0x567a874:R)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_567a7b0_rdx {
    std::uint8_t f0;   // // +0x00: std::uint8_t W  (R/W cited: 0x567a8a1:W, 0x567a8b8:W)
    std::uint8_t pad0x01[0x7];   // +0x01..+0x07 padding (no observed access)
    std::uint8_t f8;   // // +0x08: std::uint8_t W  (R/W cited: 0x567a8a4:W, 0x567a8bb:W)
};
#pragma pack(pop)

// Struct for base register r8 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_567a7b0_r8 {
    void* f0;   // // +0x00: void* R  (R/W cited: 0x567a7fa:R)
    std::uint32_t f8;   // // +0x08: std::uint32_t R  (R/W cited: 0x567a801:R)
};
#pragma pack(pop)

// Struct for base register r10 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_567a7b0_r10 {
    std::uint8_t pad0x00[0x19];   // +0x00..+0x18 padding (no observed access)
    std::uint8_t f19;   // // +0x19: std::uint8_t R  (R/W cited: 0x567a824:R, 0x567a85d:R)
    std::uint8_t pad0x1a[0x6];   // +0x1a..+0x1f padding (no observed access)
    std::uint64_t f20;   // // +0x20: std::uint64_t R  (R/W cited: 0x567a843:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_567a7b0_rax {
    std::uint8_t f0;   // // +0x00: std::uint8_t W  (R/W cited: 0x567a808:W)
    std::uint8_t pad0x01[0x7];   // +0x01..+0x07 padding (no observed access)
    std::uint64_t f8;   // // +0x08: std::uint64_t R/W  (R/W cited: 0x567a7df:R, 0x567a80b:W)
    std::uint8_t f10;   // // +0x10: std::uint8_t W  (R/W cited: 0x567a80f:W)
    std::uint8_t pad0x11[0x7];   // +0x11..+0x17 padding (no observed access)
    std::uint16_t f18;   // // +0x18: std::uint16_t W  (R/W cited: 0x567a813:W)
    std::uint8_t pad0x1a[0x6];   // +0x1a..+0x1f padding (no observed access)
    std::uint8_t f20;   // // +0x20: std::uint8_t W  (R/W cited: 0x567a7fd:W)
    std::uint8_t pad0x21[0x7];   // +0x21..+0x27 padding (no observed access)
    std::uint8_t f28;   // // +0x28: std::uint8_t W  (R/W cited: 0x567a804:W)
};
#pragma pack(pop)

// Struct for base register rbp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_567a7b0_rbp {
    std::uint64_t f0;   // // +0x00: std::uint64_t W  (R/W cited: 0x567a7c1:W)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_567a7b0_rsp {
    std::uint8_t pad0x00[0x40];   // +0x00..+0x3f padding (no observed access)
    std::uint8_t f40;   // // +0x40: std::uint8_t R  (R/W cited: 0x567a7bc:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_567a7b0_rcx, f0) == 0x0, "sub_0x567a7b0 rcx+0x0 field");
static_assert(offsetof(sub_567a7b0_rcx, f8) == 0x8, "sub_0x567a7b0 rcx+0x8 field");
static_assert(offsetof(sub_567a7b0_rcx, f19) == 0x19, "sub_0x567a7b0 rcx+0x19 field");
static_assert(offsetof(sub_567a7b0_rcx, f20) == 0x20, "sub_0x567a7b0 rcx+0x20 field");
static_assert(sizeof(sub_567a7b0_rcx) >= 0x21, "sub_0x567a7b0 rcx sizeof lower bound");

static_assert(offsetof(sub_567a7b0_rdx, f0) == 0x0, "sub_0x567a7b0 rdx+0x0 field");
static_assert(offsetof(sub_567a7b0_rdx, f8) == 0x8, "sub_0x567a7b0 rdx+0x8 field");
static_assert(sizeof(sub_567a7b0_rdx) >= 0x9, "sub_0x567a7b0 rdx sizeof lower bound");

static_assert(offsetof(sub_567a7b0_r8, f0) == 0x0, "sub_0x567a7b0 r8+0x0 field");
static_assert(offsetof(sub_567a7b0_r8, f8) == 0x8, "sub_0x567a7b0 r8+0x8 field");
static_assert(sizeof(sub_567a7b0_r8) >= 0xc, "sub_0x567a7b0 r8 sizeof lower bound");

static_assert(offsetof(sub_567a7b0_r10, f19) == 0x19, "sub_0x567a7b0 r10+0x19 field");
static_assert(offsetof(sub_567a7b0_r10, f20) == 0x20, "sub_0x567a7b0 r10+0x20 field");
static_assert(sizeof(sub_567a7b0_r10) >= 0x28, "sub_0x567a7b0 r10 sizeof lower bound");

static_assert(offsetof(sub_567a7b0_rax, f0) == 0x0, "sub_0x567a7b0 rax+0x0 field");
static_assert(offsetof(sub_567a7b0_rax, f8) == 0x8, "sub_0x567a7b0 rax+0x8 field");
static_assert(offsetof(sub_567a7b0_rax, f10) == 0x10, "sub_0x567a7b0 rax+0x10 field");
static_assert(offsetof(sub_567a7b0_rax, f18) == 0x18, "sub_0x567a7b0 rax+0x18 field");
static_assert(offsetof(sub_567a7b0_rax, f20) == 0x20, "sub_0x567a7b0 rax+0x20 field");
static_assert(offsetof(sub_567a7b0_rax, f28) == 0x28, "sub_0x567a7b0 rax+0x28 field");
static_assert(sizeof(sub_567a7b0_rax) >= 0x29, "sub_0x567a7b0 rax sizeof lower bound");

static_assert(offsetof(sub_567a7b0_rbp, f0) == 0x0, "sub_0x567a7b0 rbp+0x0 field");
static_assert(sizeof(sub_567a7b0_rbp) >= 0x8, "sub_0x567a7b0 rbp sizeof lower bound");

static_assert(offsetof(sub_567a7b0_rsp, f40) == 0x40, "sub_0x567a7b0 rsp+0x40 field");
static_assert(sizeof(sub_567a7b0_rsp) >= 0x41, "sub_0x567a7b0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0x567a7b0  push rbp; 0x567a7b1  push r15; 0x567a7b3  push r14; 0x567a7b5  push rsi
uintptr_t sub_567a7b0(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
