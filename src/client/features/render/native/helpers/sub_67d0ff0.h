#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_67d0ff0, reverse-engineered from the disassembly
// of [0x67d0ff0, 0x67d111e). Offsets and widths come straight from the instruction
// operands; field meanings are not derivable from the static listing and are kept
// as f<hex>. One struct per base register that is dereferenced.
//
// The structs are packed (#pragma pack(1)) so every declared field sits exactly at
// its observed offset and offsetof() matches it. The real object may have compiler-
// inserted alignment padding, so sizeof is a lower bound, not an exact size.

// Dest object, base register rcx/rsi (a0).
#pragma pack(push, 1)
struct sub_67d0ff0_rcx {
    void* f0;                   // +0x00: pointer R/W
    void* f8;                   // +0x08: pointer R/W (refcounted referent)
    void* f10;                  // +0x10: pointer W
    void* f18;                  // +0x18: pointer R/W (refcounted referent)
    std::uint64_t f20[2];       // +0x20: 16 bytes W (movups)
    void* f30;                  // +0x30: pointer W (0x30..0x37)
    std::uint8_t f38;           // +0x38: u8 R/W (initialization flag)
};
#pragma pack(pop)

// Source object, base register rdx/rdi (a1).
#pragma pack(push, 1)
struct sub_67d0ff0_rdx {
    void* f0;                   // +0x00: pointer R
    void* f8;                   // +0x08: pointer R (refcounted referent)
    void* f10;                  // +0x10: pointer R
    void* f18;                  // +0x18: pointer R (refcounted referent)
    std::uint64_t f20[2];       // +0x20: 16 bytes R (movups)
    void* f30;                  // +0x30: pointer R
};
#pragma pack(pop)

// Refcounted referent, base register rax (+0x8 strong refcount).
#pragma pack(push, 1)
struct sub_67d0ff0_rax {
    void* f0;                   // +0x00: vtable pointer R
    std::uint32_t f8;           // +0x08: u32 RW (strong refcount)
};
#pragma pack(pop)

// Refcounted referent, base register rbx (+0x8 strong refcount, +0xc secondary refcount).
#pragma pack(push, 1)
struct sub_67d0ff0_rbx {
    void* f0;                   // +0x00: vtable pointer R
    std::uint32_t f8;           // +0x08: u32 RW (strong refcount)
    std::uint32_t fc;           // +0x0c: u32 RW (secondary refcount)
};
#pragma pack(pop)

static_assert(offsetof(sub_67d0ff0_rcx, f0) == 0x0, "sub_67d0ff0 rcx+0x0 field");
static_assert(offsetof(sub_67d0ff0_rcx, f8) == 0x8, "sub_67d0ff0 rcx+0x8 field");
static_assert(offsetof(sub_67d0ff0_rcx, f10) == 0x10, "sub_67d0ff0 rcx+0x10 field");
static_assert(offsetof(sub_67d0ff0_rcx, f18) == 0x18, "sub_67d0ff0 rcx+0x18 field");
static_assert(offsetof(sub_67d0ff0_rcx, f20) == 0x20, "sub_67d0ff0 rcx+0x20 field");
static_assert(offsetof(sub_67d0ff0_rcx, f30) == 0x30, "sub_67d0ff0 rcx+0x30 field");
static_assert(offsetof(sub_67d0ff0_rcx, f38) == 0x38, "sub_67d0ff0 rcx+0x38 field");
static_assert(sizeof(sub_67d0ff0_rcx) >= 0x39, "sub_67d0ff0 rcx sizeof lower bound");

static_assert(offsetof(sub_67d0ff0_rdx, f0) == 0x0, "sub_67d0ff0 rdx+0x0 field");
static_assert(offsetof(sub_67d0ff0_rdx, f8) == 0x8, "sub_67d0ff0 rdx+0x8 field");
static_assert(offsetof(sub_67d0ff0_rdx, f10) == 0x10, "sub_67d0ff0 rdx+0x10 field");
static_assert(offsetof(sub_67d0ff0_rdx, f18) == 0x18, "sub_67d0ff0 rdx+0x18 field");
static_assert(offsetof(sub_67d0ff0_rdx, f20) == 0x20, "sub_67d0ff0 rdx+0x20 field");
static_assert(offsetof(sub_67d0ff0_rdx, f30) == 0x30, "sub_67d0ff0 rdx+0x30 field");
static_assert(sizeof(sub_67d0ff0_rdx) >= 0x38, "sub_67d0ff0 rdx sizeof lower bound");

static_assert(offsetof(sub_67d0ff0_rax, f0) == 0x0, "sub_67d0ff0 rax+0x0 field");
static_assert(offsetof(sub_67d0ff0_rax, f8) == 0x8, "sub_67d0ff0 rax+0x8 field");
static_assert(sizeof(sub_67d0ff0_rax) >= 0xc, "sub_67d0ff0 rax sizeof lower bound");

static_assert(offsetof(sub_67d0ff0_rbx, f0) == 0x0, "sub_67d0ff0 rbx+0x0 field");
static_assert(offsetof(sub_67d0ff0_rbx, f8) == 0x8, "sub_67d0ff0 rbx+0x8 field");
static_assert(offsetof(sub_67d0ff0_rbx, fc) == 0xc, "sub_67d0ff0 rbx+0xc field");
static_assert(sizeof(sub_67d0ff0_rbx) >= 0x10, "sub_67d0ff0 rbx sizeof lower bound");

// x64 Microsoft ABI: rcx = a0 (dest), rdx = a1 (source), return rax = a1->f30.
// Prologue: 0x67d0ff0 push rsi; 0x67d0ff1 push rdi; 0x67d0ff2 push rbx; 0x67d0ff3 sub rsp,0x20
void* sub_67d0ff0(sub_67d0ff0_rcx* a0, sub_67d0ff0_rdx* a1);

} // namespace native::helpers
