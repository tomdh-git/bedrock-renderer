#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_c284020, reverse-engineered from the disassembly
// of [0xc284020, 0xc28412b), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c284020_rcx {
    std::uint8_t pad0x00[0x248];   // +0x00..+0x247 padding (no observed access)
    void* f248;   // // +0x248: void* R // vtable-call slot(s) slot 1  (R/W cited: 0xc28403c:R, 0xc28404c:R)
    std::uint64_t f250;   // // +0x250: std::uint64_t R  (R/W cited: 0xc284053:R)
    std::uint64_t f258;   // // +0x258: std::uint64_t R  (R/W cited: 0xc2840b2:R)
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c284020_r14 {
    void* f0[2];   // // +0x00: void*[2] R/W  (R/W cited: 0xc2840af:R, 0xc2840e8:W)
    std::uint64_t f10;   // // +0x10: std::uint64_t W  (R/W cited: 0xc2840ec:W)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c284020_rax {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 1  (R/W cited: 0xc28408b:R)
    std::uint64_t f8;   // // +0x08: std::uint64_t R  (R/W cited: 0xc2840a0:R)
};
#pragma pack(pop)

// Struct for base register rbp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c284020_rbp {
    std::uint64_t f0;   // // +0x00: std::uint64_t W  (R/W cited: 0xc284031:W)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c284020_rbx {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0xc284088:R, 0xc28409d:R)
    std::uint32_t f8;   // // +0x08: std::uint32_t RW  (R/W cited: 0xc284082:RW)
    std::uint32_t fc;   // // +0x0c: std::uint32_t RW  (R/W cited: 0xc284097:RW)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c284020_rdi {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 0  (R/W cited: 0xc284079:R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c284020_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // // +0x20: std::uint64_t W  (R/W cited: 0xc284111:W)
    std::uint8_t pad0x28[0x8];   // +0x28..+0x2f padding (no observed access)
    std::uint8_t f30;   // // +0x30: std::uint8_t R  (R/W cited: 0xc28402c:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_c284020_rcx, f248) == 0x248, "sub_0xc284020 rcx+0x248 field");
static_assert(offsetof(sub_c284020_rcx, f250) == 0x250, "sub_0xc284020 rcx+0x250 field");
static_assert(offsetof(sub_c284020_rcx, f258) == 0x258, "sub_0xc284020 rcx+0x258 field");
static_assert(sizeof(sub_c284020_rcx) >= 0x260, "sub_0xc284020 rcx sizeof lower bound");

static_assert(offsetof(sub_c284020_r14, f0) == 0x0, "sub_0xc284020 r14+0x0 field");
static_assert(offsetof(sub_c284020_r14, f10) == 0x10, "sub_0xc284020 r14+0x10 field");
static_assert(sizeof(sub_c284020_r14) >= 0x18, "sub_0xc284020 r14 sizeof lower bound");

static_assert(offsetof(sub_c284020_rax, f0) == 0x0, "sub_0xc284020 rax+0x0 field");
static_assert(offsetof(sub_c284020_rax, f8) == 0x8, "sub_0xc284020 rax+0x8 field");
static_assert(sizeof(sub_c284020_rax) >= 0x10, "sub_0xc284020 rax sizeof lower bound");

static_assert(offsetof(sub_c284020_rbp, f0) == 0x0, "sub_0xc284020 rbp+0x0 field");
static_assert(sizeof(sub_c284020_rbp) >= 0x8, "sub_0xc284020 rbp sizeof lower bound");

static_assert(offsetof(sub_c284020_rbx, f0) == 0x0, "sub_0xc284020 rbx+0x0 field");
static_assert(offsetof(sub_c284020_rbx, f8) == 0x8, "sub_0xc284020 rbx+0x8 field");
static_assert(offsetof(sub_c284020_rbx, fc) == 0xc, "sub_0xc284020 rbx+0xc field");
static_assert(sizeof(sub_c284020_rbx) >= 0x10, "sub_0xc284020 rbx sizeof lower bound");

static_assert(offsetof(sub_c284020_rdi, f8) == 0x8, "sub_0xc284020 rdi+0x8 field");
static_assert(sizeof(sub_c284020_rdi) >= 0x10, "sub_0xc284020 rdi sizeof lower bound");

static_assert(offsetof(sub_c284020_rsp, f20) == 0x20, "sub_0xc284020 rsp+0x20 field");
static_assert(offsetof(sub_c284020_rsp, f30) == 0x30, "sub_0xc284020 rsp+0x30 field");
static_assert(sizeof(sub_c284020_rsp) >= 0x31, "sub_0xc284020 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0xc284020  push rbp; 0xc284021  push r15; 0xc284023  push r14; 0xc284025  push rsi
uintptr_t sub_c284020(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
