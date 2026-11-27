#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_567d9f0, reverse-engineered from the disassembly
// of [0x567d9f0, 0x567daf9), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_567d9f0_rcx {
    void* f0;   // +0x00: void* W  (R/W cited: 0x567dad8:W 8-byte store)
    void* f8;   // +0x08: void* R  (R/W cited: 0x567dac0:R)
    std::uint64_t f10;   // +0x10: std::uint64_t RW  (R/W cited: 0x567dad0:RW)
    void* f18;   // +0x18: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x567da94:R)
    std::uint8_t pad0x20[0x10];   // +0x20..+0x2f padding (no observed access)
    std::uint8_t f30;   // +0x30: std::uint8_t R  (R/W cited: 0x567da90:R)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_567d9f0_rdx {
    void* f0;   // +0x00: void* R  (R/W cited: 0x567daac:R, 0x567dacd:R)
    void* f8;   // +0x08: void* R  (R/W cited: 0x567daba:R, 0x567dad4:R, 0x567dadb:R)
    void* f10;   // +0x10: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x567d9f8:R)
    std::uint8_t f18;   // +0x18: std::uint8_t R  (R/W cited: 0x567d9fc:R)
    std::uint8_t f19;   // +0x19: std::uint8_t R  (R/W cited: 0x567da1c:R)
    std::uint8_t f1a;   // +0x1a: std::uint8_t R  (R/W cited: 0x567da28:R)
    std::uint8_t f1b;   // +0x1b: std::uint8_t R  (R/W cited: 0x567da34:R)
    std::uint8_t f1c;   // +0x1c: std::uint8_t R  (R/W cited: 0x567da40:R)
    std::uint8_t f1d;   // +0x1d: std::uint8_t R  (R/W cited: 0x567da4c:R)
    std::uint8_t f1e;   // +0x1e: std::uint8_t R  (R/W cited: 0x567da58:R)
    std::uint8_t f1f;   // +0x1f: std::uint8_t R  (R/W cited: 0x567da64:R)
};
#pragma pack(pop)

// Struct for base register rsi (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_567d9f0_rsi {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* f8;   // +0x08: void* W  (R/W cited: 0x567dadf:W 8-byte store)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_567d9f0_rcx, f0) == 0x0, "sub_0x567d9f0 rcx+0x0 field");
static_assert(offsetof(sub_567d9f0_rcx, f8) == 0x8, "sub_0x567d9f0 rcx+0x8 field");
static_assert(offsetof(sub_567d9f0_rcx, f10) == 0x10, "sub_0x567d9f0 rcx+0x10 field");
static_assert(offsetof(sub_567d9f0_rcx, f18) == 0x18, "sub_0x567d9f0 rcx+0x18 field");
static_assert(offsetof(sub_567d9f0_rcx, f30) == 0x30, "sub_0x567d9f0 rcx+0x30 field");
static_assert(sizeof(sub_567d9f0_rcx) >= 0x31, "sub_0x567d9f0 rcx sizeof lower bound");

static_assert(offsetof(sub_567d9f0_rdx, f0) == 0x0, "sub_0x567d9f0 rdx+0x0 field");
static_assert(offsetof(sub_567d9f0_rdx, f8) == 0x8, "sub_0x567d9f0 rdx+0x8 field");
static_assert(offsetof(sub_567d9f0_rdx, f10) == 0x10, "sub_0x567d9f0 rdx+0x10 field");
static_assert(offsetof(sub_567d9f0_rdx, f18) == 0x18, "sub_0x567d9f0 rdx+0x18 field");
static_assert(offsetof(sub_567d9f0_rdx, f19) == 0x19, "sub_0x567d9f0 rdx+0x19 field");
static_assert(offsetof(sub_567d9f0_rdx, f1a) == 0x1a, "sub_0x567d9f0 rdx+0x1a field");
static_assert(offsetof(sub_567d9f0_rdx, f1b) == 0x1b, "sub_0x567d9f0 rdx+0x1b field");
static_assert(offsetof(sub_567d9f0_rdx, f1c) == 0x1c, "sub_0x567d9f0 rdx+0x1c field");
static_assert(offsetof(sub_567d9f0_rdx, f1d) == 0x1d, "sub_0x567d9f0 rdx+0x1d field");
static_assert(offsetof(sub_567d9f0_rdx, f1e) == 0x1e, "sub_0x567d9f0 rdx+0x1e field");
static_assert(offsetof(sub_567d9f0_rdx, f1f) == 0x1f, "sub_0x567d9f0 rdx+0x1f field");
static_assert(sizeof(sub_567d9f0_rdx) >= 0x20, "sub_0x567d9f0 rdx sizeof lower bound");

static_assert(offsetof(sub_567d9f0_rsi, f8) == 0x8, "sub_0x567d9f0 rsi+0x8 field");
static_assert(sizeof(sub_567d9f0_rsi) >= 0x10, "sub_0x567d9f0 rsi sizeof lower bound");

// Signature (x64 Microsoft ABI) - first argument in rcx (self), second in rdx (a1)
// 0x567d9f0  push rsi; 0x567d9f1  sub rsp,0x20; 0x567d9f5  mov rax,rdx; 0x567d9f8  mov rdx,[rdx+0x10]
uintptr_t sub_567d9f0(void* self, void* a1);

} // namespace native::helpers