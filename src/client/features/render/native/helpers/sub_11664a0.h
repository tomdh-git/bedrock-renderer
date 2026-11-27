#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_11664a0, reverse-engineered from the disassembly
// of [0x11664a0, 0x11665d9), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_11664a0_rcx {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1,slot 3,slot 4  (R/W cited: 0x11664fd:R)
    std::uint8_t pad0x08[0x38];   // +0x08..+0x3f padding (no observed access)
    void* f40;   // // +0x40: void* R // vtable-call slot(s) slot 0,slot 1,slot 3,slot 4  (R/W cited: 0x11664d7:R)
    std::uint8_t pad0x48[0x8];   // +0x48..+0x4f padding (no observed access)
    std::uint8_t f50;   // // +0x50: std::uint8_t R  (R/W cited: 0x11664b3:R)
    std::uint8_t pad0x51[0x4b];   // +0x51..+0x9b padding (no observed access)
    std::uint32_t f9c;   // // +0x9c: std::uint32_t R/W  (R/W cited: 0x11664c7:R, 0x11665c4:W)
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_11664a0_r14 {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    std::uint64_t f8;   // // +0x08: std::uint64_t R  (R/W cited: 0x1166543:R)
    std::uint64_t f10;   // // +0x10: std::uint64_t R  (R/W cited: 0x1166529:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_11664a0_rax {
    void* f0[2];   // // +0x00: void*[2] R/RW/W // vtable-call slot(s) slot 1,slot 2  (R/W cited: 0x11664ed:RW, 0x1166535:R, 0x1166574:W)
    // // +0x08: void* R/W // vtable-call slot(s) slot 2  (R/W cited: 0x1166555:R, 0x1166592:W)   [subsumed by earlier field; overlapping access, no separate field]
    std::uint64_t f10;   // // +0x10: std::uint64_t W  (R/W cited: 0x1166577:W)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_11664a0_rbx {
    void* f0;   // // +0x00: void* R/W // vtable-call slot(s) slot 0,slot 1,slot 2  (R/W cited: 0x1166532:R, 0x1166552:R, 0x116657f:R, 0x116658f:W, 0x1166596:W)
    void* f8;   // // +0x08: void* R/W  (R/W cited: 0x116658b:R, 0x1166599:W)
    // // +0x0c: std::uint32_t RW  (R/W cited: 0x116654c:RW)   [subsumed by earlier field; overlapping access, no separate field]
    std::uint8_t pad0x10[0x8];   // +0x10..+0x17 padding (no observed access)
    void* f18;   // // +0x18: void* R // vtable-call slot(s) slot 1,slot 2  (R/W cited: 0x116650f:R, 0x1166570:R)
    std::uint64_t f20;   // // +0x20: std::uint64_t R  (R/W cited: 0x1166518:R)
    std::uint8_t pad0x28[0x8];   // +0x28..+0x2f padding (no observed access)
    std::uint8_t f30;   // // +0x30: std::uint8_t R  (R/W cited: 0x1166509:R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_11664a0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint8_t f20;   // // +0x20: std::uint8_t R/W  (R/W cited: 0x11664ab:W, 0x11665a5:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_11664a0_rcx, f0) == 0x0, "sub_0x11664a0 rcx+0x0 field");
static_assert(offsetof(sub_11664a0_rcx, f40) == 0x40, "sub_0x11664a0 rcx+0x40 field");
static_assert(offsetof(sub_11664a0_rcx, f50) == 0x50, "sub_0x11664a0 rcx+0x50 field");
static_assert(offsetof(sub_11664a0_rcx, f9c) == 0x9c, "sub_0x11664a0 rcx+0x9c field");
static_assert(sizeof(sub_11664a0_rcx) >= 0xa0, "sub_0x11664a0 rcx sizeof lower bound");

static_assert(offsetof(sub_11664a0_r14, f8) == 0x8, "sub_0x11664a0 r14+0x8 field");
static_assert(offsetof(sub_11664a0_r14, f10) == 0x10, "sub_0x11664a0 r14+0x10 field");
static_assert(sizeof(sub_11664a0_r14) >= 0x18, "sub_0x11664a0 r14 sizeof lower bound");

static_assert(offsetof(sub_11664a0_rax, f0) == 0x0, "sub_0x11664a0 rax+0x0 field");
static_assert(offsetof(sub_11664a0_rax, f10) == 0x10, "sub_0x11664a0 rax+0x10 field");
static_assert(sizeof(sub_11664a0_rax) >= 0x18, "sub_0x11664a0 rax sizeof lower bound");

static_assert(offsetof(sub_11664a0_rbx, f0) == 0x0, "sub_0x11664a0 rbx+0x0 field");
static_assert(offsetof(sub_11664a0_rbx, f8) == 0x8, "sub_0x11664a0 rbx+0x8 field");
static_assert(offsetof(sub_11664a0_rbx, f18) == 0x18, "sub_0x11664a0 rbx+0x18 field");
static_assert(offsetof(sub_11664a0_rbx, f20) == 0x20, "sub_0x11664a0 rbx+0x20 field");
static_assert(offsetof(sub_11664a0_rbx, f30) == 0x30, "sub_0x11664a0 rbx+0x30 field");
static_assert(sizeof(sub_11664a0_rbx) >= 0x31, "sub_0x11664a0 rbx sizeof lower bound");

static_assert(offsetof(sub_11664a0_rsp, f20) == 0x20, "sub_0x11664a0 rsp+0x20 field");
static_assert(sizeof(sub_11664a0_rsp) >= 0x21, "sub_0x11664a0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0x11664a0  push r15; 0x11664a2  push r14; 0x11664a4  push rsi; 0x11664a5  push rdi
uintptr_t sub_11664a0(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
