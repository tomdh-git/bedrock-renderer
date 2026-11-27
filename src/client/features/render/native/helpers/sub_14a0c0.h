#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_14a0c0, reverse-engineered from the disassembly
// of [0x14a0c0, 0x14a1f0), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_14a0c0_rcx {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1,slot 3  (R/W cited: 0x14a10d:R, 0x14a138:R)
    std::uint64_t f8;   // // +0x08: std::uint64_t R  (R/W cited: 0x14a117:R, 0x14a128:R)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_14a0c0_rdx {
    void* f0;   // // +0x00: void* R  (R/W cited: 0x14a138:R)  vtable pointer of the a1 object
    std::uint32_t f8;   // // +0x08: std::uint32_t RW  (R/W cited: 0x14a124:RW)
};
#pragma pack(pop)

// Struct for base register r8 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_14a0c0_r8 {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x14a1a3:R, 0x14a1b8:R, 0x14a1cc:R)
    std::uint32_t f8;   // // +0x08: std::uint32_t RW  (R/W cited: 0x14a19d:RW)
    std::uint32_t fc;   // // +0x0c: std::uint32_t RW  (R/W cited: 0x14a1b2:RW)
    std::uint8_t pad0x10[0x20];   // +0x10..+0x2f padding (no observed access)
    std::uint8_t f30;   // // +0x30: std::uint8_t R  (R/W cited: 0x14a170:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_14a0c0_rax {
    void* f0[2];   // // +0x00: void*[2] R/W // vtable-call slot(s) slot 1  (R/W cited: 0x14a14e:R, 0x14a158:R, 0x14a16d:R, 0x14a179:R, 0x14a17f:W, 0x14a1a6:R)
    // // +0x08: void* R // vtable-call slot(s) slot 1  (R/W cited: 0x14a194:R, 0x14a1bb:R, 0x14a1d8:R)   [subsumed by earlier field; overlapping access, no separate field]
    std::uint8_t pad0x10[0x8];   // +0x10..+0x17 padding (no observed access)
    void* f18;   // // +0x18: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x14a13b:R)
};
#pragma pack(pop)

// Struct for base register rbp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_14a0c0_rbp {
    std::uint8_t pad0x00[0x40];   // +0x00..+0x3f padding (no observed access)
    std::uint8_t f40;   // // +0x40: std::uint8_t R  (R/W cited: 0x14a0e8:R)
    std::uint8_t pad0x41[0x7];   // +0x41..+0x47 padding (no observed access)
    void* f48;   // // +0x48: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x14a0e4:R, 0x14a1c8:R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_14a0c0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint8_t f20;   // // +0x20: std::uint8_t W  (R/W cited: 0x14a0f3:W)
    std::uint8_t pad0x21[0x5f];   // +0x21..+0x7f padding (no observed access)
    std::uint8_t f80;   // // +0x80: std::uint8_t R  (R/W cited: 0x14a0ca:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_14a0c0_rcx, f0) == 0x0, "sub_0x14a0c0 rcx+0x0 field");
static_assert(offsetof(sub_14a0c0_rcx, f8) == 0x8, "sub_0x14a0c0 rcx+0x8 field");
static_assert(sizeof(sub_14a0c0_rcx) >= 0x10, "sub_0x14a0c0 rcx sizeof lower bound");

static_assert(offsetof(sub_14a0c0_rdx, f0) == 0x0, "sub_0x14a0c0 rdx+0x0 field");
static_assert(offsetof(sub_14a0c0_rdx, f8) == 0x8, "sub_0x14a0c0 rdx+0x8 field");
static_assert(sizeof(sub_14a0c0_rdx) >= 0xc, "sub_0x14a0c0 rdx sizeof lower bound");

static_assert(offsetof(sub_14a0c0_r8, f0) == 0x0, "sub_0x14a0c0 r8+0x0 field");
static_assert(offsetof(sub_14a0c0_r8, f8) == 0x8, "sub_0x14a0c0 r8+0x8 field");
static_assert(offsetof(sub_14a0c0_r8, fc) == 0xc, "sub_0x14a0c0 r8+0xc field");
static_assert(offsetof(sub_14a0c0_r8, f30) == 0x30, "sub_0x14a0c0 r8+0x30 field");
static_assert(sizeof(sub_14a0c0_r8) >= 0x31, "sub_0x14a0c0 r8 sizeof lower bound");

static_assert(offsetof(sub_14a0c0_rax, f0) == 0x0, "sub_0x14a0c0 rax+0x0 field");
static_assert(offsetof(sub_14a0c0_rax, f18) == 0x18, "sub_0x14a0c0 rax+0x18 field");
static_assert(sizeof(sub_14a0c0_rax) >= 0x20, "sub_0x14a0c0 rax sizeof lower bound");

static_assert(offsetof(sub_14a0c0_rbp, f40) == 0x40, "sub_0x14a0c0 rbp+0x40 field");
static_assert(offsetof(sub_14a0c0_rbp, f48) == 0x48, "sub_0x14a0c0 rbp+0x48 field");
static_assert(sizeof(sub_14a0c0_rbp) >= 0x50, "sub_0x14a0c0 rbp sizeof lower bound");

static_assert(offsetof(sub_14a0c0_rsp, f20) == 0x20, "sub_0x14a0c0 rsp+0x20 field");
static_assert(offsetof(sub_14a0c0_rsp, f80) == 0x80, "sub_0x14a0c0 rsp+0x80 field");
static_assert(sizeof(sub_14a0c0_rsp) >= 0x81, "sub_0x14a0c0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; decided from the register usage at entry:
// rcx=self, rdx=a1, r8=a2, r9=a3 are all read before being written; the return
// value is self (rax = rsi = [rbp-0x18] on every path to the epilogue).
// 0x14a0c0  push rbp; 0x14a0c1  push rsi; 0x14a0c2  push rdi; 0x14a0c3  sub rsp,0x80
uintptr_t sub_14a0c0(void* self, sub_14a0c0_rdx* a1, sub_14a0c0_r8* a2, void* a3);   // [open] signature, decided from the listing

} // namespace native::helpers
