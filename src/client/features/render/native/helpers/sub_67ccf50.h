#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_67ccf50, reverse-engineered from the disassembly
// of [0x67ccf50, 0x67cd055), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are reversed.
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, reversed name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. reversed field meanings.
#pragma pack(push, 1)
struct sub_67ccf50_rcx {
    void* f0;   // +0x00: void* R/W // vtable-call slot(s) slot 0,slot 2,slot 4  (R/W cited: 0x67ccf87:R, 0x67ccfe3:R, 0x67cd02a:R, 0x67cd037:W)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, reversed name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. reversed field meanings.
#pragma pack(push, 1)
struct sub_67ccf50_rdx {
    std::uint64_t f0;   // +0x00: std::uint64_t R  (R/W cited: 0x67ccf9c:R)
    std::uint64_t f8;   // +0x08: std::uint64_t R  (R/W cited: 0x67ccf9f:R)
    std::uint8_t pad0x10[0x40];   // +0x10..+0x4f padding (no observed access)
    void* f50;   // +0x50: void* R // vtable-call slot(s) slot 0  (R/W cited: 0x67ccf7e:R)
};
#pragma pack(pop)

// Struct for base register r8 (dereferenced in this function) [proven base, reversed name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. reversed field meanings.
#pragma pack(push, 1)
struct sub_67ccf50_r8 {
    float f0;   // +0x00: float R  (R/W cited: 0x67ccfcc:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, reversed name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. reversed field meanings.
#pragma pack(push, 1)
struct sub_67ccf50_rax {
    void* f0;   // +0x00: void* R // vtable-call slot(s) slot 2,slot 4  (R/W cited: 0x67ccf8a:R)
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding (no observed access)
    void* f10;   // +0x10: void* R // vtable-call slot(s) slot 4  (R/W cited: 0x67ccfe6:R)
    std::uint8_t pad0x18[0x8];   // +0x18..+0x1f padding (no observed access)
    std::uint64_t f20;   // +0x20: std::uint64_t R  (R/W cited: 0x67cd02d:R)
};
#pragma pack(pop)

// Struct for base register rbp (dereferenced in this function) [proven base, reversed name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. reversed field meanings.
#pragma pack(push, 1)
struct sub_67ccf50_rbp {
    std::uint64_t f0;   // +0x00: std::uint64_t W  (R/W cited: 0x67ccf65:W)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, reversed name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. reversed field meanings.
#pragma pack(push, 1)
struct sub_67ccf50_rsp {
    std::uint8_t pad0x00[0x70];   // +0x00..+0x6f padding (no observed access)
    std::uint8_t f70;   // +0x70: std::uint8_t R  (R/W cited: 0x67ccf60:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_67ccf50_rcx, f0) == 0x0, "sub_0x67ccf50 rcx+0x0 field");
static_assert(sizeof(sub_67ccf50_rcx) >= 0x8, "sub_0x67ccf50 rcx sizeof lower bound");

static_assert(offsetof(sub_67ccf50_rdx, f0) == 0x0, "sub_0x67ccf50 rdx+0x0 field");
static_assert(offsetof(sub_67ccf50_rdx, f8) == 0x8, "sub_0x67ccf50 rdx+0x8 field");
static_assert(offsetof(sub_67ccf50_rdx, f50) == 0x50, "sub_0x67ccf50 rdx+0x50 field");
static_assert(sizeof(sub_67ccf50_rdx) >= 0x58, "sub_0x67ccf50 rdx sizeof lower bound");

static_assert(offsetof(sub_67ccf50_r8, f0) == 0x0, "sub_0x67ccf50 r8+0x0 field");
static_assert(sizeof(sub_67ccf50_r8) >= 0x4, "sub_0x67ccf50 r8 sizeof lower bound");

static_assert(offsetof(sub_67ccf50_rax, f0) == 0x0, "sub_0x67ccf50 rax+0x0 field");
static_assert(offsetof(sub_67ccf50_rax, f10) == 0x10, "sub_0x67ccf50 rax+0x10 field");
static_assert(offsetof(sub_67ccf50_rax, f20) == 0x20, "sub_0x67ccf50 rax+0x20 field");
static_assert(sizeof(sub_67ccf50_rax) >= 0x28, "sub_0x67ccf50 rax sizeof lower bound");

static_assert(offsetof(sub_67ccf50_rbp, f0) == 0x0, "sub_0x67ccf50 rbp+0x0 field");
static_assert(sizeof(sub_67ccf50_rbp) >= 0x8, "sub_0x67ccf50 rbp sizeof lower bound");

static_assert(offsetof(sub_67ccf50_rsp, f70) == 0x70, "sub_0x67ccf50 rsp+0x70 field");
static_assert(sizeof(sub_67ccf50_rsp) >= 0x71, "sub_0x67ccf50 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI): exact argument and return types are reversed from
// the prologue and the observed reads/writes/calls.
// 0x67ccf50  push rbp; 0x67ccf51  push r15; 0x67ccf53  push r14; 0x67ccf55  push r13
uintptr_t sub_67ccf50(void* self);   // reversed signature; return and arg types per listing evidence

} // namespace native::helpers
