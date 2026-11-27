#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_67bc2c0, reverse-engineered from the disassembly
// of [0x67bc2c0, 0x67bc3f7), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67bc2c0_rcx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    std::uint8_t f8;   // // +0x08: std::uint8_t R  (R/W cited: 0x67bc38a:R)
    std::uint8_t pad0x09[0xf];   // +0x09..+0x17 padding (no observed access)
    std::uint64_t f18;   // // +0x18: std::uint64_t R  (R/W cited: 0x67bc396:R)
    std::uint8_t pad0x20[0x28];   // +0x20..+0x47 padding (no observed access)
    std::uint8_t f48;   // // +0x48: std::uint8_t R  (R/W cited: 0x67bc384:R)
    std::uint8_t pad0x49[0x77];   // +0x49..+0xbf padding (no observed access)
    void* fc0;   // // +0xc0: void* R // vtable-call slot(s) slot 1  (R/W cited: 0x67bc30e:R, 0x67bc31a:R)
    std::uint64_t fc8;   // // +0xc8: std::uint64_t R  (R/W cited: 0x67bc321:R)
    std::uint8_t pad0xd0[0x18];   // +0xd0..+0xe7 padding (no observed access)
    void* fe8;   // // +0xe8: void* R // vtable-call slot(s) slot 0,slot 2  (R/W cited: 0x67bc2d7:R)
    std::uint8_t ff0;   // // +0xf0: std::uint8_t R  (R/W cited: 0x67bc2ce:R)
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67bc2c0_r14 {
    std::uint64_t f0[2];   // // +0x00: std::uint64_t[2] W  (R/W cited: 0x67bc378:W)
    std::uint64_t f10;   // // +0x10: std::uint64_t W  (R/W cited: 0x67bc37c:W)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67bc2c0_rax {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x67bc2ec:R, 0x67bc351:R)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x67bc301:R, 0x67bc366:R)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67bc2c0_rbx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 0,slot 2  (R/W cited: 0x67bc33f:R)
    std::uint8_t pad0x10[0x8];   // +0x10..+0x17 padding (no observed access)
    std::uint8_t f18;   // // +0x18: std::uint8_t R  (R/W cited: 0x67bc339:R)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67bc2c0_rdi {
    void* f0[2];   // // +0x00: void*[2] R/W // vtable-call slot(s) slot 0,slot 1,slot 3  (R/W cited: 0x67bc2e9:R, 0x67bc2fe:R, 0x67bc34e:R, 0x67bc363:R, 0x67bc38e:R, 0x67bc3c6:W)
    // // +0x08: std::uint32_t RW  (R/W cited: 0x67bc2e3:RW, 0x67bc348:RW)   [subsumed by earlier field; overlapping access, no separate field]
    // // +0x0c: std::uint32_t RW  (R/W cited: 0x67bc2f8:RW, 0x67bc35d:RW)   [subsumed by earlier field; overlapping access, no separate field]
    std::uint64_t f10;   // // +0x10: std::uint64_t W  (R/W cited: 0x67bc3c9:W)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67bc2c0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // // +0x20: std::uint64_t W  (R/W cited: 0x67bc3dd:W)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_67bc2c0_rcx, f8) == 0x8, "sub_0x67bc2c0 rcx+0x8 field");
static_assert(offsetof(sub_67bc2c0_rcx, f18) == 0x18, "sub_0x67bc2c0 rcx+0x18 field");
static_assert(offsetof(sub_67bc2c0_rcx, f48) == 0x48, "sub_0x67bc2c0 rcx+0x48 field");
static_assert(offsetof(sub_67bc2c0_rcx, fc0) == 0xc0, "sub_0x67bc2c0 rcx+0xc0 field");
static_assert(offsetof(sub_67bc2c0_rcx, fc8) == 0xc8, "sub_0x67bc2c0 rcx+0xc8 field");
static_assert(offsetof(sub_67bc2c0_rcx, fe8) == 0xe8, "sub_0x67bc2c0 rcx+0xe8 field");
static_assert(offsetof(sub_67bc2c0_rcx, ff0) == 0xf0, "sub_0x67bc2c0 rcx+0xf0 field");
static_assert(sizeof(sub_67bc2c0_rcx) >= 0xf1, "sub_0x67bc2c0 rcx sizeof lower bound");

static_assert(offsetof(sub_67bc2c0_r14, f0) == 0x0, "sub_0x67bc2c0 r14+0x0 field");
static_assert(offsetof(sub_67bc2c0_r14, f10) == 0x10, "sub_0x67bc2c0 r14+0x10 field");
static_assert(sizeof(sub_67bc2c0_r14) >= 0x18, "sub_0x67bc2c0 r14 sizeof lower bound");

static_assert(offsetof(sub_67bc2c0_rax, f0) == 0x0, "sub_0x67bc2c0 rax+0x0 field");
static_assert(offsetof(sub_67bc2c0_rax, f8) == 0x8, "sub_0x67bc2c0 rax+0x8 field");
static_assert(sizeof(sub_67bc2c0_rax) >= 0x10, "sub_0x67bc2c0 rax sizeof lower bound");

static_assert(offsetof(sub_67bc2c0_rbx, f8) == 0x8, "sub_0x67bc2c0 rbx+0x8 field");
static_assert(offsetof(sub_67bc2c0_rbx, f18) == 0x18, "sub_0x67bc2c0 rbx+0x18 field");
static_assert(sizeof(sub_67bc2c0_rbx) >= 0x19, "sub_0x67bc2c0 rbx sizeof lower bound");

static_assert(offsetof(sub_67bc2c0_rdi, f0) == 0x0, "sub_0x67bc2c0 rdi+0x0 field");
static_assert(offsetof(sub_67bc2c0_rdi, f10) == 0x10, "sub_0x67bc2c0 rdi+0x10 field");
static_assert(sizeof(sub_67bc2c0_rdi) >= 0x18, "sub_0x67bc2c0 rdi sizeof lower bound");

static_assert(offsetof(sub_67bc2c0_rsp, f20) == 0x20, "sub_0x67bc2c0 rsp+0x20 field");
static_assert(sizeof(sub_67bc2c0_rsp) >= 0x28, "sub_0x67bc2c0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0x67bc2c0  push r15; 0x67bc2c2  push r14; 0x67bc2c4  push rsi; 0x67bc2c5  push rdi
uintptr_t sub_67bc2c0(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
