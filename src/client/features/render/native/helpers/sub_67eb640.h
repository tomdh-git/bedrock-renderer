#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_67eb640, reverse-engineered from the disassembly
// of [0x67eb640, 0x67eb743), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67eb640_rcx {
    void* f0;   // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x67eb6f3:R, 0x67eb708:R)
    std::uint64_t f8;   // +0x08: std::uint64_t R/RW  (R/W cited: 0x67eb6e4:R, 0x67eb6ed:RW)
    // +0x0c: std::uint32_t RW  (R/W cited: 0x67eb702:RW)   [subsumed by earlier field; overlapping access, no separate field]
    void* f10;   // +0x10: void* R // vtable-call slot(s) slot 0,slot 1,slot 4  (R/W cited: 0x67eb69c:R, 0x67eb6cd:R)
    std::uint8_t pad0x18[0x8];   // +0x18..+0x1f padding (no observed access)
    std::uint64_t f20;   // +0x20: std::uint64_t R  (R/W cited: 0x67eb6a5:R)
    std::uint8_t pad0x28[0x8];   // +0x28..+0x2f padding (no observed access)
    void* f30;   // +0x30: void* R/W // vtable-call slot(s) slot 0,slot 1,slot 2,slot 4,slot 8,slot 9  (R/W cited: 0x67eb653:R, 0x67eb698:W)
    std::uint8_t pad0x38[0x8];   // +0x38..+0x3f padding (no observed access)
    std::uint64_t f40;   // +0x40: std::uint64_t W  (R/W cited: 0x67eb688:W)
    void* f48;   // +0x48: void* R/W // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x67eb649:R, 0x67eb690:W)
};
#pragma pack(pop)

// (no non-negative-offset fields; base only used for stack/scratch accesses)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67eb640_rax {
    void* f0;   // +0x00: void* R // vtable-call slot(s) slot 1  (R/W cited: 0x67eb6f6:R)
    // +0x01: std::uint8_t R  (R/W cited: 0x67eb657:R)   [subsumed by earlier field; overlapping access, no separate field]
    std::uint64_t f8;   // +0x08: std::uint64_t R  (R/W cited: 0x67eb70b:R)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67eb640_rdi {
    std::uint64_t f0[2];   // +0x00: std::uint64_t[2] W  (R/W cited: 0x67eb6d9:W)
    std::uint64_t f10;   // +0x10: std::uint64_t W  (R/W cited: 0x67eb6dc:W)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67eb640_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // +0x20: std::uint64_t W  (R/W cited: 0x67eb729:W)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_67eb640_rcx, f0) == 0x0, "sub_0x67eb640 rcx+0x0 field");
static_assert(offsetof(sub_67eb640_rcx, f8) == 0x8, "sub_0x67eb640 rcx+0x8 field");
static_assert(offsetof(sub_67eb640_rcx, f10) == 0x10, "sub_0x67eb640 rcx+0x10 field");
static_assert(offsetof(sub_67eb640_rcx, f20) == 0x20, "sub_0x67eb640 rcx+0x20 field");
static_assert(offsetof(sub_67eb640_rcx, f30) == 0x30, "sub_0x67eb640 rcx+0x30 field");
static_assert(offsetof(sub_67eb640_rcx, f40) == 0x40, "sub_0x67eb640 rcx+0x40 field");
static_assert(offsetof(sub_67eb640_rcx, f48) == 0x48, "sub_0x67eb640 rcx+0x48 field");
static_assert(sizeof(sub_67eb640_rcx) >= 0x50, "sub_0x67eb640 rcx sizeof lower bound");

static_assert(offsetof(sub_67eb640_rax, f0) == 0x0, "sub_0x67eb640 rax+0x0 field");
static_assert(offsetof(sub_67eb640_rax, f8) == 0x8, "sub_0x67eb640 rax+0x8 field");
static_assert(sizeof(sub_67eb640_rax) >= 0x10, "sub_0x67eb640 rax sizeof lower bound");

static_assert(offsetof(sub_67eb640_rdi, f0) == 0x0, "sub_0x67eb640 rdi+0x0 field");
static_assert(offsetof(sub_67eb640_rdi, f10) == 0x10, "sub_0x67eb640 rdi+0x10 field");
static_assert(sizeof(sub_67eb640_rdi) >= 0x18, "sub_0x67eb640 rdi sizeof lower bound");

static_assert(offsetof(sub_67eb640_rsp, f20) == 0x20, "sub_0x67eb640 rsp+0x20 field");
static_assert(sizeof(sub_67eb640_rsp) >= 0x28, "sub_0x67eb640 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - exact argument and return types derived from usage:
// rax = return value from sub_e935700/vtable destructors; return type uintptr_t.
// rcx/this pointer passed as sole argument.
uintptr_t sub_67eb640(void* self);

} // namespace native::helpers
