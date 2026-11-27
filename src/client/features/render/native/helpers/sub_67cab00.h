#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_67cab00, reverse-engineered from the disassembly
// of [0x67cab00, 0x67cabce), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67cab00_rcx {
    void* field_0x00;            // +0x00: void* W  (R/W cited: 0x67cab22:W)
    void* frameRenderer;         // +0x08: void* R  (R/W cited: 0x67cab2f:R)
    void* field_0x10;            // +0x10: void* R  (R/W cited: 0x67cab33:R)
    void* field_0x18;            // +0x18: void* R  (R/W cited: 0x67cab37:R)
    void* field_0x20;            // +0x20: void* R  (R/W cited: 0x67cab3b:R)
    void* field_0x28;            // +0x28: void* R  (R/W cited: 0x67cab3f:R)
    void* field_0x30;            // +0x30: void* R  (R/W cited: 0x67cab43:R)
    void* field_0x38;            // +0x38: void* R  (R/W cited: 0x67cab47:R)
    std::uint8_t shouldRender;   // +0x40: std::uint8_t R  (R/W cited: 0x67cab25:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67cab00_rax {
    std::uint8_t pad0x00[0x10];   // +0x00..+0x0f padding (no observed access)
    std::uint8_t f10;   // +0x10: std::uint8_t W  (R/W cited: 0x67cab55:W, 0x67cab66:W, 0x67cab77:W, 0x67cab88:W, 0x67cab99:W, 0x67cabaa:W, 0x67cabbb:W)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_67cab00_rsp {
    std::uint8_t pad0x00[0x30];   // +0x00..+0x2f padding (no observed access)
    std::uint8_t f30;   // +0x30: std::uint8_t R  (R/W cited: 0x67cab0e:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_67cab00_rcx, field_0x00) == 0x0, "sub_0x67cab00 rcx+0x0 field");
static_assert(offsetof(sub_67cab00_rcx, frameRenderer) == 0x8, "sub_0x67cab00 rcx+0x08 field");
static_assert(offsetof(sub_67cab00_rcx, field_0x10) == 0x10, "sub_0x67cab00 rcx+0x10 field");
static_assert(offsetof(sub_67cab00_rcx, field_0x18) == 0x18, "sub_0x67cab00 rcx+0x18 field");
static_assert(offsetof(sub_67cab00_rcx, field_0x20) == 0x20, "sub_0x67cab00 rcx+0x20 field");
static_assert(offsetof(sub_67cab00_rcx, field_0x28) == 0x28, "sub_0x67cab00 rcx+0x28 field");
static_assert(offsetof(sub_67cab00_rcx, field_0x30) == 0x30, "sub_0x67cab00 rcx+0x30 field");
static_assert(offsetof(sub_67cab00_rcx, field_0x38) == 0x38, "sub_0x67cab00 rcx+0x38 field");
static_assert(offsetof(sub_67cab00_rcx, shouldRender) == 0x40, "sub_0x67cab00 rcx+0x40 field");
static_assert(sizeof(sub_67cab00_rcx) >= 0x41, "sub_0x67cab00 rcx sizeof lower bound");

static_assert(offsetof(sub_67cab00_rax, f10) == 0x10, "sub_0x67cab00 rax+0x10 field");
static_assert(sizeof(sub_67cab00_rax) >= 0x11, "sub_0x67cab00 rax sizeof lower bound");

static_assert(offsetof(sub_67cab00_rsp, f30) == 0x30, "sub_0x67cab00 rsp+0x30 field");
static_assert(sizeof(sub_67cab00_rsp) >= 0x31, "sub_0x67cab00 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0x67cab00  push rbp; 0x67cab01  push r15; 0x67cab03  push r14; 0x67cab05  push r12
uintptr_t sub_67cab00(void* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::helpers
