#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_e815ea0, reverse-engineered from the disassembly
// of [0xe815ea0, 0xe815fbf), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_e815ea0_rcx {
    std::uint8_t pad0x00[0xbde178];   // +0x00..+0xbde177 padding (no observed access)
    std::uint8_t fbde178;   // // +0xbde178: std::uint8_t R  (R/W cited: 0xe815eaa:R)
    std::uint8_t pad0xbde179[0xb7fff];   // +0xbde179..+0xc96177 padding (no observed access)
    void* fc96178;   // // +0xc96178: void* R // vtable-call slot(s) slot 0  (R/W cited: 0xe815f01:R)
    std::uint8_t pad0xc96180[0x10];   // +0xc96180..+0xc9618f padding (no observed access)
    std::uint8_t fc96190;   // // +0xc96190: std::uint8_t R  (R/W cited: 0xe815ec7:R)
};
#pragma pack(pop)

// Struct for base register r8 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_e815ea0_r8 {
    std::uint8_t f0;   // // +0x00: std::uint8_t RW  (R/W cited: 0xe815f5c:RW)
    std::uint8_t pad0x01[0xb7fff];   // +0x01..+0xb7fff padding (no observed access)
    std::uint64_t fb8000;   // // +0xb8000: std::uint64_t R  (R/W cited: 0xe815f67:R, 0xe815f6e:R, 0xe815f75:R, 0xe815f7c:R, 0xe815f83:R, 0xe815f8a:R, 0xe815f98:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_e815ea0_rax {
    std::uint64_t f0;   // // +0x00: std::uint64_t R  (R/W cited: 0xe815f08:R)
};
#pragma pack(pop)

// Struct for base register rsi (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_e815ea0_rsi {
    std::uint8_t pad0x00[0xb8000];   // +0x00..+0xb7fff padding (no observed access)
    std::uint64_t fb8000;   // // +0xb8000: std::uint64_t R  (R/W cited: 0xe815f47:R, 0xe815f60:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_e815ea0_rcx, fbde178) == 0xbde178, "sub_0xe815ea0 rcx+0xbde178 field");
static_assert(offsetof(sub_e815ea0_rcx, fc96178) == 0xc96178, "sub_0xe815ea0 rcx+0xc96178 field");
static_assert(offsetof(sub_e815ea0_rcx, fc96190) == 0xc96190, "sub_0xe815ea0 rcx+0xc96190 field");
static_assert(sizeof(sub_e815ea0_rcx) >= 0xc96191, "sub_0xe815ea0 rcx sizeof lower bound");

static_assert(offsetof(sub_e815ea0_r8, f0) == 0x0, "sub_0xe815ea0 r8+0x0 field");
static_assert(offsetof(sub_e815ea0_r8, fb8000) == 0xb8000, "sub_0xe815ea0 r8+0xb8000 field");
static_assert(sizeof(sub_e815ea0_r8) >= 0xb8008, "sub_0xe815ea0 r8 sizeof lower bound");

static_assert(offsetof(sub_e815ea0_rax, f0) == 0x0, "sub_0xe815ea0 rax+0x0 field");
static_assert(sizeof(sub_e815ea0_rax) >= 0x8, "sub_0xe815ea0 rax sizeof lower bound");

static_assert(offsetof(sub_e815ea0_rsi, fb8000) == 0xb8000, "sub_0xe815ea0 rsi+0xb8000 field");
static_assert(sizeof(sub_e815ea0_rsi) >= 0xb8008, "sub_0xe815ea0 rsi sizeof lower bound");

// Signature (x64 Microsoft ABI), resolved from the listing:
//   0xe815ea7  mov rdi,rcx            -> RCX = self (void*)
//   0xe815eb1  movzx ebx,dx           -> RDX = index, only the low 16 bits are read (std::uint16_t)
//   R8/R9 (3rd/4th args) are read only on the guard-failure path before the
//   sub_bc5f110 call (0xe815ed9); they are forwarded to that variadic log helper.
//   0xe815fba  jmp 0xE80F290          -> return value is forwarded from sub_e80f290,
//   which receives the computed pointer in RCX (tail jump, return forwarded).
uintptr_t sub_e815ea0(void* self, std::uint16_t index, std::uintptr_t r8_in, std::uintptr_t r9_in);

} // namespace native::helpers
