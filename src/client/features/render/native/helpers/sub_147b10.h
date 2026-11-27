#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_147b10, reverse-engineered from the disassembly
// of [0x147b10, 0x147c27), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open] decisions.
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
// Layout decision: this is a small-string / inline-buffer object. f58 holds the
// character count (capped at 0xF when the heap buffer is null), f40 is the heap
// buffer pointer, f50 is unused, f38/f40/f20/f0 are three independent inline buffers
// with f30/f28/f20/f10/f08/f00 sibling count pointers. Fields keep their observed
// offsets; names are a best-effort reversal, not a claim about the original source.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_147b10_rcx {
    void* f0;   // +0x00: void* R/W // vtable-call slot(s) slot 2,slot 3  (R/W cited: 0x147bc4:R, 0x147c04:W)
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding (no observed access)
    std::uint64_t f10;   // +0x10: std::uint64_t W  (R/W cited: 0x147bf4:W)
    std::uint64_t f18;   // +0x18: std::uint64_t R/W -- used as a count (compared <0x10, +1) and written 0xF; never dereferenced as a pointer  (R/W cited: 0x147bba:R, 0x147bfc:W)
    void* f20;   // +0x20: void* R/W // vtable-call slot(s) slot 0,slot 2,slot 3,slot 6,slot 7  (R/W cited: 0x147b75:R, 0x147bb6:W)
    std::uint8_t pad0x28[0x8];   // +0x28..+0x2f padding (no observed access)
    std::uint64_t f30;   // +0x30: std::uint64_t W  (R/W cited: 0x147ba6:W)
    std::uint64_t f38;   // +0x38: std::uint64_t R/W  (R/W cited: 0x147b6b:R, 0x147bae:W)
    void* f40;   // +0x40: void* R/W // vtable-call slot(s) slot 0,slot 2,slot 3,slot 4,slot 6,slot 7,slot 10,slot 11  (R/W cited: 0x147b22:R, 0x147b67:W)
    std::uint8_t pad0x48[0x8];   // +0x48..+0x4f padding (no observed access)
    std::uint64_t f50;   // +0x50: std::uint64_t W  (R/W cited: 0x147b57:W)
    std::uint64_t f58;   // +0x58: std::uint64_t R/W  (R/W cited: 0x147b18:R, 0x147b5f:W)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_147b10_rax {
    std::uint8_t pad0x00[0x1];   // +0x00..+0x00 padding (no observed access)
    std::uint8_t f1;   // +0x01: std::uint8_t R  (R/W cited: 0x147b26:R, 0x147b79:R, 0x147bc7:R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_147b10_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // +0x20: std::uint64_t W  (R/W cited: 0x147c0d:W)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_147b10_rcx, f0) == 0x0, "sub_0x147b10 rcx+0x0 field");
static_assert(offsetof(sub_147b10_rcx, f10) == 0x10, "sub_0x147b10 rcx+0x10 field");
static_assert(offsetof(sub_147b10_rcx, f18) == 0x18, "sub_0x147b10 rcx+0x18 field");
static_assert(offsetof(sub_147b10_rcx, f20) == 0x20, "sub_0x147b10 rcx+0x20 field");
static_assert(offsetof(sub_147b10_rcx, f30) == 0x30, "sub_0x147b10 rcx+0x30 field");
static_assert(offsetof(sub_147b10_rcx, f38) == 0x38, "sub_0x147b10 rcx+0x38 field");
static_assert(offsetof(sub_147b10_rcx, f40) == 0x40, "sub_0x147b10 rcx+0x40 field");
static_assert(offsetof(sub_147b10_rcx, f50) == 0x50, "sub_0x147b10 rcx+0x50 field");
static_assert(offsetof(sub_147b10_rcx, f58) == 0x58, "sub_0x147b10 rcx+0x58 field");
static_assert(sizeof(sub_147b10_rcx) >= 0x60, "sub_0x147b10 rcx sizeof lower bound");

static_assert(offsetof(sub_147b10_rax, f1) == 0x1, "sub_0x147b10 rax+0x1 field");
static_assert(sizeof(sub_147b10_rax) >= 0x2, "sub_0x147b10 rax sizeof lower bound");

static_assert(offsetof(sub_147b10_rsp, f20) == 0x20, "sub_0x147b10 rsp+0x20 field");
static_assert(sizeof(sub_147b10_rsp) >= 0x28, "sub_0x147b10 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0x147b10  push rsi; 0x147b11  sub rsp,0x30; 0x147b15  mov rsi,rcx; 0x147b18  mov rax,[rcx+0x58]
uintptr_t sub_147b10(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
