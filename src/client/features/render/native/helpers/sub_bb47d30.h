#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_bb47d30, reverse-engineered from the disassembly
// of [0xbb47d30, 0xbb47e4f), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9/r10/rax/rsp this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
// The structs are packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_bb47d30_rcx {
    void* f0;   // +0x00: void* R  (R/W cited: 0xbb47d50:R)
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding (no observed access)
    std::uint64_t f10;   // +0x10: std::uint64_t R  (R/W cited: 0xbb47d5c:R)
    void* f18;   // +0x18: void* R  (R/W cited: 0xbb47d60:R)
    std::uint8_t pad0x20[0x9f0];   // +0x20..+0xa0f padding (no observed access)
    void* fa10;   // +0xa10: void* R  (R/W cited: 0xbb47d37:R, 0xbb47d3e:R)
    std::uint8_t pad0xa18[0x60];   // +0xa18..+0xa77 padding (no observed access)
    void* fa78;   // +0xa78: void* R  (R/W cited: 0xbb47d84:R)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_bb47d30_rdx {
    std::uint8_t pad0x00[0xa];   // +0x00..+0x09 padding (no observed access)
    std::uint8_t fa;   // +0x0a: std::uint8_t R  (R/W cited: 0xbb47d70:R)
};
#pragma pack(pop)

// Struct for base register r9 (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_bb47d30_r9 {
    std::uint8_t pad0x00[0x38];   // +0x00..+0x37 padding (no observed access)
    std::uint32_t f38;   // +0x38: std::uint32_t R  (R/W cited: 0xbb47dc8:R, 0xbb47e24:R)
    std::uint8_t pad0x3c[0x84];   // +0x3c..+0xbf padding (no observed access)
    void* fc0;   // +0xc0: void* R  (R/W cited: 0xbb47e02:R)
};
#pragma pack(pop)

// Struct for base register r10 (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_bb47d30_r10 {
    std::uint8_t pad0x00[0xa];   // +0x00..+0x09 padding (no observed access)
    std::uint8_t fa;   // +0x0a: std::uint8_t R  (R/W cited: 0xbb47dfb:R)
    std::uint8_t pad0x0b[0xab];   // +0x0b..+0xb5 padding (no observed access)
    std::uint16_t fb6;   // +0xb6: std::uint16_t R  (R/W cited: 0xbb47e0e:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_bb47d30_rax {
    std::uint64_t f0;   // +0x00: std::uint64_t R/RW  (R/W cited: 0xbb47d69:RW, 0xbb47d92:R)
    void* f8;   // +0x08: void* R  (R/W cited: 0xbb47de9:R)
    void* f10;   // +0x10: void* R // vtable-call slot(s) slot 24  (R/W cited: 0xbb47df2:R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_bb47d30_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint8_t f20;   // +0x20: std::uint8_t W  (R/W cited: 0xbb47d9e:W)
    std::uint8_t pad0x21[0xd];   // +0x21..+0x2d padding (no observed access)
    std::uint8_t f2e;   // +0x2e: std::uint8_t R  (R/W cited: 0xbb47da8:R)
    std::uint8_t f2f;   // +0x2f: std::uint8_t R  (R/W cited: 0xbb47d99:R)
    std::uint8_t f30;   // +0x30: std::uint8_t R  (R/W cited: 0xbb47da3:R)
    std::uint8_t pad0x31[0xf];   // +0x31..+0x3f padding (no observed access)
    void* f40;   // +0x40: void* R // vtable-call slot(s) slot 1,slot 2  (R/W cited: 0xbb47db2:R)
    std::uint64_t f48;   // +0x48: std::uint64_t R  (R/W cited: 0xbb47db7:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_bb47d30_rcx, f0) == 0x0, "sub_0xbb47d30 rcx+0x0 field");
static_assert(offsetof(sub_bb47d30_rcx, f10) == 0x10, "sub_0xbb47d30 rcx+0x10 field");
static_assert(offsetof(sub_bb47d30_rcx, f18) == 0x18, "sub_0xbb47d30 rcx+0x18 field");
static_assert(offsetof(sub_bb47d30_rcx, fa10) == 0xa10, "sub_0xbb47d30 rcx+0xa10 field");
static_assert(offsetof(sub_bb47d30_rcx, fa78) == 0xa78, "sub_0xbb47d30 rcx+0xa78 field");
static_assert(sizeof(sub_bb47d30_rcx) >= 0xa80, "sub_0xbb47d30 rcx sizeof lower bound");

static_assert(offsetof(sub_bb47d30_rdx, fa) == 0xa, "sub_0xbb47d30 rdx+0xa field");
static_assert(sizeof(sub_bb47d30_rdx) >= 0xb, "sub_0xbb47d30 rdx sizeof lower bound");

static_assert(offsetof(sub_bb47d30_r9, f38) == 0x38, "sub_0xbb47d30 r9+0x38 field");
static_assert(offsetof(sub_bb47d30_r9, fc0) == 0xc0, "sub_0xbb47d30 r9+0xc0 field");
static_assert(sizeof(sub_bb47d30_r9) >= 0xc8, "sub_0xbb47d30 r9 sizeof lower bound");

static_assert(offsetof(sub_bb47d30_r10, fa) == 0xa, "sub_0xbb47d30 r10+0xa field");
static_assert(offsetof(sub_bb47d30_r10, fb6) == 0xb6, "sub_0xbb47d30 r10+0xb6 field");
static_assert(sizeof(sub_bb47d30_r10) >= 0xb8, "sub_0xbb47d30 r10 sizeof lower bound");

static_assert(offsetof(sub_bb47d30_rax, f0) == 0x0, "sub_0xbb47d30 rax+0x0 field");
static_assert(offsetof(sub_bb47d30_rax, f8) == 0x8, "sub_0xbb47d30 rax+0x8 field");
static_assert(offsetof(sub_bb47d30_rax, f10) == 0x10, "sub_0xbb47d30 rax+0x10 field");
static_assert(sizeof(sub_bb47d30_rax) >= 0x18, "sub_0xbb47d30 rax sizeof lower bound");

static_assert(offsetof(sub_bb47d30_rsp, f20) == 0x20, "sub_0xbb47d30 rsp+0x20 field");
static_assert(offsetof(sub_bb47d30_rsp, f2e) == 0x2e, "sub_0xbb47d30 rsp+0x2e field");
static_assert(offsetof(sub_bb47d30_rsp, f2f) == 0x2f, "sub_0xbb47d30 rsp+0x2f field");
static_assert(offsetof(sub_bb47d30_rsp, f30) == 0x30, "sub_0xbb47d30 rsp+0x30 field");
static_assert(offsetof(sub_bb47d30_rsp, f40) == 0x40, "sub_0xbb47d30 rsp+0x40 field");
static_assert(offsetof(sub_bb47d30_rsp, f48) == 0x48, "sub_0xbb47d30 rsp+0x48 field");
static_assert(sizeof(sub_bb47d30_rsp) >= 0x50, "sub_0xbb47d30 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) - exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0xbb47d30  sub rsp,0x58; 0xbb47d34  mov r8,rcx; 0xbb47d37  lea rax,[rcx+0xA10]; 0xbb47d3e  mov rcx,[rcx+0xA10]
uintptr_t sub_bb47d30(void* self);   // signature placeholder (return type, arg types TBD)

} // namespace native::helpers
