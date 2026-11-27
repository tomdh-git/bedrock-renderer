#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_675d320, reverse-engineered from the disassembly
// of [0x675d320, 0x675d42f), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_675d320_rcx {
    std::uint8_t pad0x00[0x38];   // +0x00..+0x37 padding (no observed access)
    void* f38;   // +0x38: void* R  (R/W cited: 0x675d386:R)
    void* f40;   // +0x40: void* R  (R/W cited: 0x675d3cb:R) - address taken (lea)
    void* f48;   // +0x48: void* R/W  (R/W cited: 0x675d3cf:R, 0x675d3dd:W)
    void* f50;   // +0x50: void* R  (R/W cited: 0x675d3af:R) - address taken (lea)
    std::uint8_t pad0x58[0x44];   // +0x58..+0x9b padding (no observed access)
    std::uint32_t f9c;   // +0x9c: std::uint32_t R/W  (R/W cited: 0x675d3bf:R, 0x675d41a:W)
    std::uint8_t fa0;   // +0xa0: std::uint8_t R  (R/W cited: 0x675d32c:R)
    std::uint8_t pad0xa1[0x3];   // +0xa1..+0xa3 padding (no observed access)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_675d320_rax {
    void* f0;   // +0x00: void* R/W  (R/W cited: 0x675d36e:W, 0x675d3d7:W)
    void* f8;   // +0x08: void* R/W  (R/W cited: 0x675d353:R, 0x675d371:W, 0x675d3d3:W)
    void* f10;   // +0x10: void* R/W  (R/W cited: 0x675d379:W, 0x675d395:R)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_675d320_rbx {
    void* f0;   // +0x00: void* R/W  (R/W cited: 0x675d350:R, 0x675d392:R, 0x675d3da:W)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_675d320_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint8_t f20;   // +0x20: std::uint8_t R/W  (R/W cited: 0x675d381:W, 0x675d399:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_675d320_rcx, f38) == 0x38, "sub_0x675d320 rcx+0x38 field");
static_assert(offsetof(sub_675d320_rcx, f40) == 0x40, "sub_0x675d320 rcx+0x40 field");
static_assert(offsetof(sub_675d320_rcx, f50) == 0x50, "sub_0x675d320 rcx+0x50 field");
static_assert(offsetof(sub_675d320_rcx, f9c) == 0x9c, "sub_0x675d320 rcx+0x9c field");
static_assert(offsetof(sub_675d320_rcx, fa0) == 0xa0, "sub_0x675d320 rcx+0xa0 field");
static_assert(sizeof(sub_675d320_rcx) >= 0xa1, "sub_0x675d320 rcx sizeof lower bound");

static_assert(offsetof(sub_675d320_rax, f0) == 0x0, "sub_0x675d320 rax+0x0 field");
static_assert(offsetof(sub_675d320_rax, f8) == 0x8, "sub_0x675d320 rax+0x8 field");
static_assert(offsetof(sub_675d320_rax, f10) == 0x10, "sub_0x675d320 rax+0x10 field");
static_assert(sizeof(sub_675d320_rax) >= 0x18, "sub_0x675d320 rax sizeof lower bound");

static_assert(offsetof(sub_675d320_rbx, f0) == 0x0, "sub_0x675d320 rbx+0x0 field");
static_assert(sizeof(sub_675d320_rbx) >= 0x8, "sub_0x675d320 rbx sizeof lower bound");

static_assert(offsetof(sub_675d320_rsp, f20) == 0x20, "sub_0x675d320 rsp+0x20 field");
static_assert(sizeof(sub_675d320_rsp) >= 0x21, "sub_0x675d320 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0x675d320  push r14; 0x675d322  push rsi; 0x675d323  push rdi; 0x675d324  push rbx
uintptr_t sub_675d320(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
