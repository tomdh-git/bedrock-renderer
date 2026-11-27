#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_e83abb0, reverse-engineered from the disassembly
// of [0xe83abb0, 0xe83acdf), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_e83abb0_rcx {
    std::uint8_t pad0x00[0xb8000];   // +0x00..+0xb7fff padding (no observed access)
    void* fb8000;   // // +0xb8000: void* R // vtable-call slot(s) slot 0,slot 94208  (R/W cited: 0xe83aca3:R)
    void* fb8008;   // // +0xb8008: void* R/W // vtable-call slot(s) slot 0,slot 94208  (R/W cited: 0xe83abd1:R, 0xe83ac0a:R, 0xe83ac2a:W)
    std::uint8_t pad0xb8010[0x8];   // +0xb8010..+0xb8017 padding (no observed access)
    std::uint8_t fb8018;   // // +0xb8018: std::uint8_t R  (R/W cited: 0xe83abc8:R)
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_e83abb0_r14 {
    std::uint64_t f0;   // // +0x00: std::uint64_t W  (R/W cited: 0xe83ac43:W)
    std::uint8_t pad0x08[0x38];   // +0x08..+0x3f padding (no observed access)
    std::uint8_t f40;   // // +0x40: std::uint8_t R  (R/W cited: 0xe83ac5f:R)
    std::uint8_t pad0x41[0x4f];   // +0x41..+0x8f padding (no observed access)
    std::uint64_t f90;   // // +0x90: std::uint64_t W  (R/W cited: 0xe83ac4a:W)
    std::uint8_t pad0x98[0x19];   // +0x98..+0xb0 padding (no observed access)
    std::uint16_t fb1;   // // +0xb1: std::uint16_t W  (R/W cited: 0xe83ac55:W)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_e83abb0_rax {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 94208  (R/W cited: 0xe83acaa:R)
    std::uint8_t pad0x08[0xb7ff8];   // +0x08..+0xb7fff padding (no observed access)
    std::uint64_t fb8000;   // // +0xb8000: std::uint64_t R  (R/W cited: 0xe83acc7:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(sizeof(sub_e83abb0_rax) >= 0xb8008, "sub_0xe83abb0 rax sizeof lower bound");

// Signature (x64 Microsoft ABI): rcx = self (sub_e83abb0_rcx*), rdx = size (uint64).
// Return value is rax. Proven from the prologue: 0xe83abb0 push r14; 0xe83abb2 push rsi;
// 0xe83abb3 push rdi; 0xe83abb4 push rbx; 0xe83abb9 mov rsi,rdx; 0xe83abbc mov rdi,rcx.
uintptr_t sub_e83abb0(void* self, std::uint64_t size);

} // namespace native::helpers
