#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_c2a4150, reverse-engineered from the disassembly
// of [0xc2a4150, 0xc2a4282), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c2a4150_rdx {
    std::uint8_t pad0x00[0x10];   // +0x00..+0x0f padding (no observed access)
    std::uint8_t f10;   // +0x10: std::uint8_t R (R/W cited: 0xc2a423f:R)
    std::uint8_t pad0x11[0x277];   // +0x11..+0x287 padding (no observed access)
    void* f288;   // +0x288: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0xc2a41ba:R, 0xc2a422e:R)
    std::uint8_t pad0x290[0x8];   // +0x290..+0x297 padding (no observed access)
    std::uint64_t f298;   // +0x298: std::uint64_t R (R/W cited: 0xc2a4165:R, 0xc2a41a0:R)
    std::uint8_t pad0x2a0[0x8];   // +0x2a0..+0x2a7 padding (no observed access)
    void* f2a8;   // +0x2a8: void* R // vtable-call slot(s) slot 81  (R/W cited: 0xc2a4171:R)
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c2a4150_r14 {
    void* f0;   // +0x00: void* R // vtable-call slot(s) slot 4  (R/W cited: 0xc2a41f5:R)
    std::uint8_t pad0x08[0x18];   // +0x08..+0x1f padding (no observed access)
    void* f20;   // +0x20: void* R // vtable-call slot(s) slot 0  (R/W cited: 0xc2a41f8:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c2a4150_rax {
    void* f0;   // +0x00: void* R/W // vtable-call slot(s) slot 0,slot 1,slot 4  (R/W cited: 0xc2a41c5:W, 0xc2a41cc:R, 0xc2a420a:R)
    std::uint64_t f8;   // +0x08: std::uint64_t R (R/W cited: 0xc2a41c1:R, 0xc2a421f:R)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c2a4150_rbx {
    void* f0;   // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0xc2a4207:R, 0xc2a421c:R)
    std::uint32_t f8;   // +0x08: std::uint32_t RW (R/W cited: 0xc2a4201:RW)
    std::uint32_t fc;   // +0x0c: std::uint32_t RW (R/W cited: 0xc2a4216:RW)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c2a4150_rdi {
    std::uint64_t f0[2];   // +0x00: std::uint64_t[2] W (R/W cited: 0xc2a41af:W)
    std::uint64_t f10;   // +0x10: std::uint64_t W (R/W cited: 0xc2a41b2:W)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c2a4150_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // +0x20: std::uint64_t W (R/W cited: 0xc2a4268:W)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_c2a4150_rdx, f10) == 0x10, "sub_0xc2a4150 rdx+0x10 field");
static_assert(offsetof(sub_c2a4150_rdx, f288) == 0x288, "sub_0xc2a4150 rdx+0x288 field");
static_assert(offsetof(sub_c2a4150_rdx, f298) == 0x298, "sub_0xc2a4150 rdx+0x298 field");
static_assert(offsetof(sub_c2a4150_rdx, f2a8) == 0x2a8, "sub_0xc2a4150 rdx+0x2a8 field");
static_assert(sizeof(sub_c2a4150_rdx) >= 0x2b0, "sub_0xc2a4150 rdx sizeof lower bound");

static_assert(offsetof(sub_c2a4150_r14, f0) == 0x0, "sub_0xc2a4150 r14+0x0 field");
static_assert(offsetof(sub_c2a4150_r14, f20) == 0x20, "sub_0xc2a4150 r14+0x20 field");
static_assert(sizeof(sub_c2a4150_r14) >= 0x28, "sub_0xc2a4150 r14 sizeof lower bound");

static_assert(offsetof(sub_c2a4150_rax, f0) == 0x0, "sub_0xc2a4150 rax+0x0 field");
static_assert(offsetof(sub_c2a4150_rax, f8) == 0x8, "sub_0xc2a4150 rax+0x8 field");
static_assert(sizeof(sub_c2a4150_rax) >= 0x10, "sub_0xc2a4150 rax sizeof lower bound");

static_assert(offsetof(sub_c2a4150_rbx, f0) == 0x0, "sub_0xc2a4150 rbx+0x0 field");
static_assert(offsetof(sub_c2a4150_rbx, f8) == 0x8, "sub_0xc2a4150 rbx+0x8 field");
static_assert(offsetof(sub_c2a4150_rbx, fc) == 0xc, "sub_0xc2a4150 rbx+0xc field");
static_assert(sizeof(sub_c2a4150_rbx) >= 0x10, "sub_0xc2a4150 rbx sizeof lower bound");

static_assert(offsetof(sub_c2a4150_rdi, f0) == 0x0, "sub_0xc2a4150 rdi+0x0 field");
static_assert(offsetof(sub_c2a4150_rdi, f10) == 0x10, "sub_0xc2a4150 rdi+0x10 field");
static_assert(sizeof(sub_c2a4150_rdi) >= 0x18, "sub_0xc2a4150 rdi sizeof lower bound");

static_assert(offsetof(sub_c2a4150_rsp, f20) == 0x20, "sub_0xc2a4150 rsp+0x20 field");
static_assert(sizeof(sub_c2a4150_rsp) >= 0x28, "sub_0xc2a4150 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0xc2a4150  push r14; 0xc2a4152  push rsi; 0xc2a4153  push rdi; 0xc2a4154  push rbx
uintptr_t sub_c2a4150(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
