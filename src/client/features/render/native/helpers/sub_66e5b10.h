#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_66e5b10, reverse-engineered from the disassembly
// of [0x66e5b10, 0x66e5c47), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e5b10_rcx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    std::uint8_t f8;   // // +0x08: std::uint8_t R  (R/W cited: 0x66e5bda:R)
    std::uint8_t pad0x09[0xf];   // +0x09..+0x17 padding (no observed access)
    std::uint64_t f18;   // // +0x18: std::uint64_t R  (R/W cited: 0x66e5be6:R)
    std::uint8_t pad0x20[0x28];   // +0x20..+0x47 padding (no observed access)
    std::uint8_t f48;   // // +0x48: std::uint8_t R  (R/W cited: 0x66e5bd4:R)
    std::uint8_t pad0x49[0xf7];   // +0x49..+0x13f padding (no observed access)
    void* f140;   // // +0x140: void* R // vtable-call slot(s) slot 1  (R/W cited: 0x66e5b5e:R, 0x66e5b6a:R)
    std::uint64_t f148;   // // +0x148: std::uint64_t R  (R/W cited: 0x66e5b71:R)
    std::uint8_t pad0x150[0x18];   // +0x150..+0x167 padding (no observed access)
    void* f168;   // // +0x168: void* R // vtable-call slot(s) slot 0,slot 2  (R/W cited: 0x66e5b27:R)
    std::uint8_t f170;   // // +0x170: std::uint8_t R  (R/W cited: 0x66e5b1e:R)
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e5b10_r14 {
    std::uint64_t f0[2];   // // +0x00: std::uint64_t[2] W  (R/W cited: 0x66e5bc8:W)
    std::uint64_t f10;   // // +0x10: std::uint64_t W  (R/W cited: 0x66e5bcc:W)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e5b10_rax {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x66e5b3c:R, 0x66e5ba1:R)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x66e5b51:R, 0x66e5bb6:R)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e5b10_rbx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 0,slot 2  (R/W cited: 0x66e5b8f:R)
    std::uint8_t pad0x10[0x8];   // +0x10..+0x17 padding (no observed access)
    std::uint8_t f18;   // // +0x18: std::uint8_t R  (R/W cited: 0x66e5b89:R)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e5b10_rdi {
    void* f0[2];   // // +0x00: void*[2] R/W // vtable-call slot(s) slot 0,slot 1,slot 3  (R/W cited: 0x66e5b39:R, 0x66e5b4e:R, 0x66e5b9e:R, 0x66e5bb3:R, 0x66e5bde:R, 0x66e5c16:W)
    // // +0x08: std::uint32_t RW  (R/W cited: 0x66e5b33:RW, 0x66e5b98:RW)   [subsumed by earlier field; overlapping access, no separate field]
    // // +0x0c: std::uint32_t RW  (R/W cited: 0x66e5b48:RW, 0x66e5bad:RW)   [subsumed by earlier field; overlapping access, no separate field]
    std::uint64_t f10;   // // +0x10: std::uint64_t W  (R/W cited: 0x66e5c19:W)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_66e5b10_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // // +0x20: std::uint64_t W  (R/W cited: 0x66e5c2d:W)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_66e5b10_rcx, f8) == 0x8, "sub_0x66e5b10 rcx+0x8 field");
static_assert(offsetof(sub_66e5b10_rcx, f18) == 0x18, "sub_0x66e5b10 rcx+0x18 field");
static_assert(offsetof(sub_66e5b10_rcx, f48) == 0x48, "sub_0x66e5b10 rcx+0x48 field");
static_assert(offsetof(sub_66e5b10_rcx, f140) == 0x140, "sub_0x66e5b10 rcx+0x140 field");
static_assert(offsetof(sub_66e5b10_rcx, f148) == 0x148, "sub_0x66e5b10 rcx+0x148 field");
static_assert(offsetof(sub_66e5b10_rcx, f168) == 0x168, "sub_0x66e5b10 rcx+0x168 field");
static_assert(offsetof(sub_66e5b10_rcx, f170) == 0x170, "sub_0x66e5b10 rcx+0x170 field");
static_assert(sizeof(sub_66e5b10_rcx) >= 0x171, "sub_0x66e5b10 rcx sizeof lower bound");

static_assert(offsetof(sub_66e5b10_r14, f0) == 0x0, "sub_0x66e5b10 r14+0x0 field");
static_assert(offsetof(sub_66e5b10_r14, f10) == 0x10, "sub_0x66e5b10 r14+0x10 field");
static_assert(sizeof(sub_66e5b10_r14) >= 0x18, "sub_0x66e5b10 r14 sizeof lower bound");

static_assert(offsetof(sub_66e5b10_rax, f0) == 0x0, "sub_0x66e5b10 rax+0x0 field");
static_assert(offsetof(sub_66e5b10_rax, f8) == 0x8, "sub_0x66e5b10 rax+0x8 field");
static_assert(sizeof(sub_66e5b10_rax) >= 0x10, "sub_0x66e5b10 rax sizeof lower bound");

static_assert(offsetof(sub_66e5b10_rbx, f8) == 0x8, "sub_0x66e5b10 rbx+0x8 field");
static_assert(offsetof(sub_66e5b10_rbx, f18) == 0x18, "sub_0x66e5b10 rbx+0x18 field");
static_assert(sizeof(sub_66e5b10_rbx) >= 0x19, "sub_0x66e5b10 rbx sizeof lower bound");

static_assert(offsetof(sub_66e5b10_rdi, f0) == 0x0, "sub_0x66e5b10 rdi+0x0 field");
static_assert(offsetof(sub_66e5b10_rdi, f10) == 0x10, "sub_0x66e5b10 rdi+0x10 field");
static_assert(sizeof(sub_66e5b10_rdi) >= 0x18, "sub_0x66e5b10 rdi sizeof lower bound");

static_assert(offsetof(sub_66e5b10_rsp, f20) == 0x20, "sub_0x66e5b10 rsp+0x20 field");
static_assert(sizeof(sub_66e5b10_rsp) >= 0x28, "sub_0x66e5b10 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0x66e5b10  push r15; 0x66e5b12  push r14; 0x66e5b14  push rsi; 0x66e5b15  push rdi
uintptr_t sub_66e5b10(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
