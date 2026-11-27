#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_bd11a0, reverse-engineered from the disassembly
// of [0xbd11a0, 0xbd12d3). [proven] offsets/widths/signedness come straight from
// the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at
// its observed offset and offsetof() matches it. The real object may have
// compiler-inserted alignment padding, so sizeof is a lower bound, not an exact
// size. [open] field meanings.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_bd11a0_rcx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    std::uint64_t f8;   // +0x08: std::uint64_t R  (R/W cited: 0xbd121b:R)
    void* f10;   // +0x10: void* R // vtable-call slot(s) slot 1,slot 2,slot 9,slot 10,slot 13  (R/W cited: 0xbd11a4:R, 0xbd11fd:R, 0xbd121f:R)
    std::uint32_t f18;   // +0x18: std::uint32_t R  (R/W cited: 0xbd11a8:R)
    std::uint8_t pad0x1c[0x34];   // +0x1c..+0x4f padding (no observed access)
    std::uint64_t f50;   // +0x50: std::uint64_t R  (R/W cited: 0xbd125a:R)
};
#pragma pack(pop)

// Struct for base register r8 (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_bd11a0_r8 {
    std::uint8_t pad0x00[0x48];   // +0x00..+0x47 padding (no observed access)
    void* f48;   // +0x48: void* R // vtable-call slot(s) slot 1,slot 2,slot 10  (R/W cited: 0xbd11ab:R)
    std::uint64_t f50;   // +0x50: std::uint64_t R  (R/W cited: 0xbd11af:R)
    std::uint8_t pad0x58[0x10];   // +0x58..+0x67 padding (no observed access)
    void* f68;   // +0x68: void* R // vtable-call slot(s) slot 1,slot 2,slot 10  (R/W cited: 0xbd11c8:R)
    std::uint8_t f70;   // +0x70: std::uint8_t R  (R/W cited: 0xbd11f3:R)
};
#pragma pack(pop)

// Struct for base register r10 (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_bd11a0_r10 {
    std::uint64_t f0;   // +0x00: std::uint64_t R  (R/W cited: 0xbd11d0:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_bd11a0_rax {
    std::uint8_t f0;   // +0x00: std::uint8_t RW  (R/W cited: 0xbd11cc:RW)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_bd11a0_rcx, f8) == 0x8, "sub_0xbd11a0 rcx+0x8 field");
static_assert(offsetof(sub_bd11a0_rcx, f10) == 0x10, "sub_0xbd11a0 rcx+0x10 field");
static_assert(offsetof(sub_bd11a0_rcx, f18) == 0x18, "sub_0xbd11a0 rcx+0x18 field");
static_assert(offsetof(sub_bd11a0_rcx, f50) == 0x50, "sub_0xbd11a0 rcx+0x50 field");
static_assert(sizeof(sub_bd11a0_rcx) >= 0x58, "sub_0xbd11a0 rcx sizeof lower bound");

static_assert(offsetof(sub_bd11a0_r8, f48) == 0x48, "sub_0xbd11a0 r8+0x48 field");
static_assert(offsetof(sub_bd11a0_r8, f50) == 0x50, "sub_0xbd11a0 r8+0x50 field");
static_assert(offsetof(sub_bd11a0_r8, f68) == 0x68, "sub_0xbd11a0 r8+0x68 field");
static_assert(offsetof(sub_bd11a0_r8, f70) == 0x70, "sub_0xbd11a0 r8+0x70 field");
static_assert(sizeof(sub_bd11a0_r8) >= 0x71, "sub_0xbd11a0 r8 sizeof lower bound");

static_assert(offsetof(sub_bd11a0_r10, f0) == 0x0, "sub_0xbd11a0 r10+0x0 field");
static_assert(sizeof(sub_bd11a0_r10) >= 0x8, "sub_0xbd11a0 r10 sizeof lower bound");

static_assert(offsetof(sub_bd11a0_rax, f0) == 0x0, "sub_0xbd11a0 rax+0x0 field");
static_assert(sizeof(sub_bd11a0_rax) >= 0x1, "sub_0xbd11a0 rax sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0xbd11a0  sub rsp,0x28; 0xbd11a4  mov r8,[rcx+0x10]; 0xbd11a8  mov eax,[rcx+0x18]; 0xbd11ab  mov rcx,[r8+0x48]
// edx is read live-in at 0xbd12a0 (mov ecx,edx) with no prior write, so it is the
// second x64 ABI argument.
uintptr_t sub_bd11a0(void* self, std::uint32_t edx);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
