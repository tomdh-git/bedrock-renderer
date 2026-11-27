#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_341070, reverse-engineered from the disassembly
// of [0x341070, 0x34119d), Minecraft Windows 1.26.62.01. Offsets and widths come
// straight from the instruction operands; field names describe the observed use.
// One struct per base register that is dereferenced (rcx/rdx/rax this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
//
// The structs are packed (#pragma pack(1)) so every declared field sits exactly at
// its observed offset and offsetof() matches it. The real object may have
// compiler-inserted alignment padding, so sizeof is a lower bound, not an exact size.

// Struct for base register rcx (dereferenced in this function).
#pragma pack(push, 1)
struct sub_341070_rcx {
    std::uint8_t pad0x00[0x4];   // +0x00..+0x03 padding (no observed access)
    void* f4;   // +0x04: void* R  (R/W cited: 0x34117c:R, 0x341189:R)
    std::uint8_t pad0x0C[0x6C];   // +0x0C..+0x77 padding (no observed access)
    std::uint8_t f78;   // +0x78: std::uint8_t W  (R/W cited: 0x34109e:W)
    std::uint8_t pad0x79[0x17];   // +0x79..+0x8f padding (no observed access)
    std::uint8_t f90;   // +0x90: std::uint8_t R/W  (R/W cited: 0x3410a2:R, 0x3410b6:W)
    std::uint8_t pad0x91[0x47];   // +0x91..+0xd7 padding (no observed access)
    std::uint64_t fd8[2];   // +0xd8: std::uint64_t[2] W  (R/W cited: 0x3410c0:W)
    std::uint8_t fe8;   // +0xe8: std::uint8_t W  (R/W cited: 0x3410c7:W)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function).
#pragma pack(push, 1)
struct sub_341070_rdx {
    std::uint8_t f0;   // +0x00: std::uint8_t W  (R/W cited: 0x341103:W)
    std::uint8_t pad0x01[0x17];   // +0x01..+0x17 padding (no observed access)
    void* f18;   // +0x18: void* R // vtable-call slot(s) slot 15  (R/W cited: 0x3410e8:R)
    std::uint8_t pad0x20[0x18];   // +0x20..+0x37 padding (no observed access)
    void* f38;   // +0x38: void* R // vtable-call slot(s) slot 15  (R/W cited: 0x3410ef:R)
    std::uint8_t pad0x40[0x10];   // +0x40..+0x4f padding (no observed access)
    void* f50;   // +0x50: void* R // vtable-call slot(s) slot 15  (R/W cited: 0x3410f6:R)
    std::uint8_t pad0x58[0x10];   // +0x58..+0x67 padding (no observed access)
    std::uint8_t f68;   // +0x68: std::uint8_t W  (R/W cited: 0x3410e0:W)
    std::uint8_t pad0x69[0x7];   // +0x69..+0x6f padding (no observed access)
    std::uint8_t f70;   // +0x70: std::uint8_t W  (R/W cited: 0x3410e4:W)
    std::uint8_t pad0x71[0x7];   // +0x71..+0x77 padding (no observed access)
    void* f78;   // +0x78: void* R // vtable-call slot(s) slot 15  (R/W cited: 0x341106:R, 0x34111a:R, 0x341129:R, 0x34113d:R, 0x341157:R)
    std::uint64_t f80;   // +0x80: std::uint64_t W  (R/W cited: 0x34114c:W)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function).
#pragma pack(push, 1)
struct sub_341070_rax {
    std::uint8_t f0;   // +0x00: std::uint8_t W  (R/W cited: 0x3410ec:W, 0x3410f3:W, 0x3410fa:W, 0x341175:W)
    std::uint8_t pad0x01[0x3];   // +0x01..+0x03 padding (no observed access)
    void* f4;   // +0x04: void* R // vtable-call slot(s) slot 15  (R/W cited: 0x34110a:R, 0x34111e:R, 0x34112d:R, 0x341141:R, 0x34115b:R)
    std::uint8_t pad0x0C[0x6C];   // +0x0C..+0x77 padding (no observed access)
    void* f78;   // +0x78: void* R  (R/W cited: 0x341178:R, 0x341185:R)
};
#pragma pack(pop)

// Struct for base register rbp (dereferenced in this function).
#pragma pack(push, 1)
struct sub_341070_rbp {
    std::uint64_t f0;   // +0x00: std::uint64_t W  (R/W cited: 0x34107d:W)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function).
#pragma pack(push, 1)
struct sub_341070_rsp {
    std::uint8_t pad0x00[0x30];   // +0x00..+0x2f padding (no observed access)
    std::uint8_t f30;   // +0x30: std::uint8_t R  (R/W cited: 0x341078:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_341070_rcx, f4) == 0x4, "sub_0x341070 rcx+0x4 field");
static_assert(offsetof(sub_341070_rcx, f78) == 0x78, "sub_0x341070 rcx+0x78 field");
static_assert(offsetof(sub_341070_rcx, f90) == 0x90, "sub_0x341070 rcx+0x90 field");
static_assert(offsetof(sub_341070_rcx, fd8) == 0xd8, "sub_0x341070 rcx+0xd8 field");
static_assert(offsetof(sub_341070_rcx, fe8) == 0xe8, "sub_0x341070 rcx+0xe8 field");
static_assert(sizeof(sub_341070_rcx) >= 0xe9, "sub_0x341070 rcx sizeof lower bound");

static_assert(offsetof(sub_341070_rdx, f0) == 0x0, "sub_0x341070 rdx+0x0 field");
static_assert(offsetof(sub_341070_rdx, f18) == 0x18, "sub_0x341070 rdx+0x18 field");
static_assert(offsetof(sub_341070_rdx, f38) == 0x38, "sub_0x341070 rdx+0x38 field");
static_assert(offsetof(sub_341070_rdx, f50) == 0x50, "sub_0x341070 rdx+0x50 field");
static_assert(offsetof(sub_341070_rdx, f68) == 0x68, "sub_0x341070 rdx+0x68 field");
static_assert(offsetof(sub_341070_rdx, f70) == 0x70, "sub_0x341070 rdx+0x70 field");
static_assert(offsetof(sub_341070_rdx, f78) == 0x78, "sub_0x341070 rdx+0x78 field");
static_assert(offsetof(sub_341070_rdx, f80) == 0x80, "sub_0x341070 rdx+0x80 field");
static_assert(sizeof(sub_341070_rdx) >= 0x88, "sub_0x341070 rdx sizeof lower bound");

static_assert(offsetof(sub_341070_rax, f0) == 0x0, "sub_0x341070 rax+0x0 field");
static_assert(offsetof(sub_341070_rax, f4) == 0x4, "sub_0x341070 rax+0x4 field");
static_assert(offsetof(sub_341070_rax, f78) == 0x78, "sub_0x341070 rax+0x78 field");
static_assert(sizeof(sub_341070_rax) >= 0x80, "sub_0x341070 rax sizeof lower bound");

static_assert(offsetof(sub_341070_rbp, f0) == 0x0, "sub_0x341070 rbp+0x0 field");
static_assert(sizeof(sub_341070_rbp) >= 0x8, "sub_0x341070 rbp sizeof lower bound");

static_assert(offsetof(sub_341070_rsp, f30) == 0x30, "sub_0x341070 rsp+0x30 field");
static_assert(sizeof(sub_341070_rsp) >= 0x31, "sub_0x341070 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI). The prologue saves RBX/RSI/RDI/RBP and the body
// reads the incoming argument registers: RCX = self (a1), RDX = a2, R8 = a3,
// R9D = a4 (tested for the block-1 path). The return value in RAX is self at ret.
uintptr_t sub_341070(void* self, void* a2, void* a3, std::uint32_t a4);

} // namespace native::helpers
