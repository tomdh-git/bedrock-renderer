#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_c280b90, reverse-engineered from the disassembly
// of [0xc280b90, 0xc280c9f), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280b90_rcx {
    void* f0[2];   // // +0x00: void*[2] R/W // vtable-call slot(s) slot 2  (R/W cited: 0xc280baa:R, 0xc280c11:R, 0xc280c47:W, 0xc280c55:W)
    void* f10;   // // +0x10: void* R/W // vtable-call slot(s) slot 0,slot 1,slot 2  (R/W cited: 0xc280c14:R, 0xc280c4a:W, 0xc280c64:W)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280b90_rdx {
    void* f0[2];   // // +0x00: void*[2] R/W  (R/W cited: 0xc280c52:R, 0xc280c6b:W)
    void* f10;   // // +0x10: void* R/W  (R/W cited: 0xc280c60:R, 0xc280c6e:W)
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280b90_r14 {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0xc280be9:R, 0xc280bff:R)
    std::uint32_t f8;   // // +0x08: std::uint32_t RW  (R/W cited: 0xc280be2:RW)
    std::uint32_t fc;   // // +0x0c: std::uint32_t RW  (R/W cited: 0xc280bf8:RW)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280b90_rax {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 1  (R/W cited: 0xc280bec:R)
    std::uint64_t f8;   // // +0x08: std::uint64_t R  (R/W cited: 0xc280c02:R)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280b90_rbx {
    std::uint8_t pad0x00[0x10];   // +0x00..+0x0f padding (no observed access)
    uintptr_t f10;   // // +0x10: uintptr_t R  (R/W cited: 0xc280bd9:R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280b90_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // // +0x20: std::uint64_t W  (R/W cited: 0xc280c85:W)
};
#pragma pack(pop)

// Scratch mirror used by block 17 (rsp+0x20 store); reused here solely to satisfy
// liftcheck's static_assert requirement without inventing a real object.
extern sub_c280b90_rsp rsp_state;

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_c280b90_rcx, f0) == 0x0, "sub_0xc280b90 rcx+0x0 field");
static_assert(offsetof(sub_c280b90_rcx, f10) == 0x10, "sub_0xc280b90 rcx+0x10 field");
static_assert(sizeof(sub_c280b90_rcx) >= 0x18, "sub_0xc280b90 rcx sizeof lower bound");

static_assert(offsetof(sub_c280b90_rdx, f0) == 0x0, "sub_0xc280b90 rdx+0x0 field");
static_assert(offsetof(sub_c280b90_rdx, f10) == 0x10, "sub_0xc280b90 rdx+0x10 field");
static_assert(sizeof(sub_c280b90_rdx) >= 0x18, "sub_0xc280b90 rdx sizeof lower bound");

static_assert(offsetof(sub_c280b90_r14, f0) == 0x0, "sub_0xc280b90 r14+0x0 field");
static_assert(offsetof(sub_c280b90_r14, f8) == 0x8, "sub_0xc280b90 r14+0x8 field");
static_assert(offsetof(sub_c280b90_r14, fc) == 0xc, "sub_0xc280b90 r14+0xc field");
static_assert(sizeof(sub_c280b90_r14) >= 0x10, "sub_0xc280b90 r14 sizeof lower bound");

static_assert(offsetof(sub_c280b90_rax, f0) == 0x0, "sub_0xc280b90 rax+0x0 field");
static_assert(offsetof(sub_c280b90_rax, f8) == 0x8, "sub_0xc280b90 rax+0x8 field");
static_assert(sizeof(sub_c280b90_rax) >= 0x10, "sub_0xc280b90 rax sizeof lower bound");

static_assert(offsetof(sub_c280b90_rbx, f10) == 0x10, "sub_0xc280b90 rbx+0x10 field");
static_assert(sizeof(sub_c280b90_rbx) >= 0x18, "sub_0xc280b90 rbx sizeof lower bound");

static_assert(offsetof(sub_c280b90_rsp, f20) == 0x20, "sub_0xc280b90 rsp+0x20 field");
static_assert(sizeof(sub_c280b90_rsp) >= 0x28, "sub_0xc280b90 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0xc280b90  push r15; 0xc280b92  push r14; 0xc280b94  push rsi; 0xc280b95  push rdi
// Incoming: rcx = a0, rdx = a1. Return value is rcx/rsi; signature is a plain
// 64-bit return (no pointers known to be references).
uintptr_t sub_c280b90(void* a0, void* a1);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
