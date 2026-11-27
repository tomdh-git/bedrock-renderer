#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layouts for sub_c2ae6c0, recovered from the disassembly of
// [0xc2ae6c0, 0xc2ae7cd), Minecraft Windows 1.26.62.01. Offsets, widths and
// signedness come straight from the instruction operands.
// One struct per base register dereferenced in the function. Field f<hex> sits at
// offset 0x<hex>.

// Base register rcx (also rsi): the function argument; rsi is reused as a control
// block pointer after 0xc2ae78d, which is why the reference-count fields below are
// reached through this same layout. Packed so every field is at its observed offset
// and offsetof() matches; the real object can carry compiler padding, so sizeof is
// a lower bound.
#pragma pack(push, 1)
struct sub_c2ae6c0_rcx {
    void* f0;   // +0x00: vtable pointer of the object at rsi after 0xc2ae78d (0xc2ae79c R, 0xc2ae7b1 R)
    std::uint32_t f8;   // +0x08: strong reference count reached with rsi (0xc2ae796 lock dec)
    std::uint32_t fc;   // +0x0c: weak reference count reached with rsi (0xc2ae7ab lock dec)
    std::uint8_t pad0x10[0x258];   // +0x10..+0x267 padding (no observed access)
    std::uint64_t f268[2];   // +0x268: 16 bytes cleared (0xc2ae70a W)
    std::uint64_t f278[2];   // +0x278: 16 bytes cleared (0xc2ae703 W)
    std::uint64_t f288;   // +0x288: cleared (0xc2ae711 W)
    void* f290;   // +0x290: element array begin (0xc2ae71c R, 0xc2ae77f R)
    std::uint64_t f298;   // +0x298: element array end (0xc2ae723 R, 0xc2ae786 W)
};
#pragma pack(pop)

// Base register rax: the vtable reached through the control block's first field.
#pragma pack(push, 1)
struct sub_c2ae6c0_rax {
    void* f0;   // +0x00: virtual slot 0, dispatched at 0xc2ae761 / 0xc2ae7a5 (0xc2ae75b R, 0xc2ae79f R)
    void* f8;   // +0x08: virtual slot 1, dispatched at 0xc2ae777 / 0xc2ae7bb (0xc2ae770 R, 0xc2ae7b4 R)
};
#pragma pack(pop)

// Base register rbx: one 16-byte element of the array [0x290, 0x298).
#pragma pack(push, 1)
struct sub_c2ae6c0_rbx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* f8;   // +0x08: control block pointer of the element (0xc2ae749 R)
};
#pragma pack(pop)

// Base register rdi: reference-counting control block.
#pragma pack(push, 1)
struct sub_c2ae6c0_rdi {
    void* f0;   // +0x00: vtable pointer (0xc2ae758 R, 0xc2ae76d R)
    std::uint32_t f8;   // +0x08: strong reference count (0xc2ae752 lock dec)
    std::uint32_t fc;   // +0x0c: weak reference count (0xc2ae767 lock dec)
};
#pragma pack(pop)

// Base register rsp: frame slot probed by lea rbp,[rsp+0x40] at 0xc2ae6ca.
#pragma pack(push, 1)
struct sub_c2ae6c0_rsp {
    std::uint8_t pad0x00[0x40];   // +0x00..+0x3f padding (no observed access)
    std::uint8_t f40;   // +0x40: frame-pointer slot (0xc2ae6ca address computation)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_c2ae6c0_rcx, f0) == 0x0, "sub_0xc2ae6c0 rcx+0x0 field");
static_assert(offsetof(sub_c2ae6c0_rcx, f8) == 0x8, "sub_0xc2ae6c0 rcx+0x8 field");
static_assert(offsetof(sub_c2ae6c0_rcx, fc) == 0xc, "sub_0xc2ae6c0 rcx+0xc field");
static_assert(offsetof(sub_c2ae6c0_rcx, f268) == 0x268, "sub_0xc2ae6c0 rcx+0x268 field");
static_assert(offsetof(sub_c2ae6c0_rcx, f278) == 0x278, "sub_0xc2ae6c0 rcx+0x278 field");
static_assert(offsetof(sub_c2ae6c0_rcx, f288) == 0x288, "sub_0xc2ae6c0 rcx+0x288 field");
static_assert(offsetof(sub_c2ae6c0_rcx, f290) == 0x290, "sub_0xc2ae6c0 rcx+0x290 field");
static_assert(offsetof(sub_c2ae6c0_rcx, f298) == 0x298, "sub_0xc2ae6c0 rcx+0x298 field");
static_assert(sizeof(sub_c2ae6c0_rcx) >= 0x2a0, "sub_0xc2ae6c0 rcx sizeof lower bound");

static_assert(offsetof(sub_c2ae6c0_rax, f0) == 0x0, "sub_0xc2ae6c0 rax+0x0 field");
static_assert(offsetof(sub_c2ae6c0_rax, f8) == 0x8, "sub_0xc2ae6c0 rax+0x8 field");
static_assert(sizeof(sub_c2ae6c0_rax) >= 0x10, "sub_0xc2ae6c0 rax sizeof lower bound");

static_assert(offsetof(sub_c2ae6c0_rbx, f8) == 0x8, "sub_0xc2ae6c0 rbx+0x8 field");
static_assert(sizeof(sub_c2ae6c0_rbx) >= 0x10, "sub_0xc2ae6c0 rbx sizeof lower bound");

static_assert(offsetof(sub_c2ae6c0_rdi, f0) == 0x0, "sub_0xc2ae6c0 rdi+0x0 field");
static_assert(offsetof(sub_c2ae6c0_rdi, f8) == 0x8, "sub_0xc2ae6c0 rdi+0x8 field");
static_assert(offsetof(sub_c2ae6c0_rdi, fc) == 0xc, "sub_0xc2ae6c0 rdi+0xc field");
static_assert(sizeof(sub_c2ae6c0_rdi) >= 0x10, "sub_0xc2ae6c0 rdi sizeof lower bound");

static_assert(offsetof(sub_c2ae6c0_rsp, f40) == 0x40, "sub_0xc2ae6c0 rsp+0x40 field");
static_assert(sizeof(sub_c2ae6c0_rsp) >= 0x41, "sub_0xc2ae6c0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI): rcx = the object pointer (moved to rsi at 0xc2ae6d7).
// No path stores a return register before the ret at 0xc2ae7cc, so the function
// returns nothing.
// 0xc2ae6c0  push rbp; 0xc2ae6c1  push r14; 0xc2ae6c3  push rsi; 0xc2ae6c4  push rdi
void sub_c2ae6c0(void* self);

} // namespace native::helpers
