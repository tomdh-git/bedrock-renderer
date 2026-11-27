#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_62f07f0, reverse-engineered from the disassembly
// of [0x62f07f0, 0x62f08fb), Minecraft Windows 1.26.62.01.
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.

// Struct for base register rcx (the "this" object a0).
// rcx points at offset 0x50 of a0 (rcx = [a0+0x50]); also rcx = [a0+0x38], rcx = [a0+0x0].
#pragma pack(push, 1)
struct sub_62f07f0_rcx {
    void* f0;            // +0x00: void* R/W - vtable pointer read at [rcx+0x0], byte at [rcx+0x0] written as 0
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding (no observed access)
    std::uint64_t f10;   // +0x10: std::uint64_t W - set to 0
    void* f18;           // +0x18: void* R/W - read as length, written as 0xF
    std::uint8_t pad0x20[0x18];   // +0x20..+0x37 padding (no observed access)
    void* f38;           // +0x38: void* R - pointer (a pointer to a pointer is read at [rcx+0x38])
    std::uint8_t pad0x40[0x8];   // +0x40..+0x47 padding (no observed access)
    std::uint64_t f48;   // +0x48: std::uint64_t R - end pointer of a range
    void* f50;           // +0x50: void* R - pointer (a pointer to a pointer is read at [rcx+0x50])
    std::uint8_t pad0x58[0x8];   // +0x58..+0x5f padding (no observed access)
    std::uint64_t f60;   // +0x60: std::uint64_t R - end pointer of a range
};
#pragma pack(pop)

// Struct for base register rax.
// rax holds [rcx-8] / [rcx-8] heap-chunk metadata, also [rsi] then [rax+1] is used as length.
#pragma pack(push, 1)
struct sub_62f07f0_rax {
    std::uint8_t pad0x00[0x1];   // +0x00..+0x00 padding (no observed access)
    std::uint8_t f1;   // +0x01: std::uint8_t R - low byte read as part of lea rdx,[rax+1]
};
#pragma pack(pop)

// Struct for base register rdi (destination of sub_e935700 calls).
// rdi = &a0+0x50 or &a0+0x38: 16 bytes zeroed, then qword at +0x10 set to 0.
#pragma pack(push, 1)
struct sub_62f07f0_rdi {
    std::uint64_t f0[2];   // +0x00: std::uint64_t[2] W - 16 bytes zeroed by movups xmm0
    std::uint64_t f10;   // +0x10: std::uint64_t W - set to 0
};
#pragma pack(pop)

// Struct for base register rsp (local stack slot at rsp+0x20).
#pragma pack(push, 1)
struct sub_62f07f0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // +0x20: std::uint64_t W - set to 0 before the indirect call
};
#pragma pack(pop)

static_assert(offsetof(sub_62f07f0_rcx, f0) == 0x0, "sub_0x62f07f0 rcx+0x0 field");
static_assert(offsetof(sub_62f07f0_rcx, f10) == 0x10, "sub_0x62f07f0 rcx+0x10 field");
static_assert(offsetof(sub_62f07f0_rcx, f18) == 0x18, "sub_0x62f07f0 rcx+0x18 field");
static_assert(offsetof(sub_62f07f0_rcx, f38) == 0x38, "sub_0x62f07f0 rcx+0x38 field");
static_assert(offsetof(sub_62f07f0_rcx, f48) == 0x48, "sub_0x62f07f0 rcx+0x48 field");
static_assert(offsetof(sub_62f07f0_rcx, f50) == 0x50, "sub_0x62f07f0 rcx+0x50 field");
static_assert(offsetof(sub_62f07f0_rcx, f60) == 0x60, "sub_0x62f07f0 rcx+0x60 field");
static_assert(sizeof(sub_62f07f0_rcx) >= 0x68, "sub_0x62f07f0 rcx sizeof lower bound");

static_assert(offsetof(sub_62f07f0_rax, f1) == 0x1, "sub_0x62f07f0 rax+0x1 field");
static_assert(sizeof(sub_62f07f0_rax) >= 0x2, "sub_0x62f07f0 rax sizeof lower bound");

static_assert(offsetof(sub_62f07f0_rdi, f0) == 0x0, "sub_0x62f07f0 rdi+0x0 field");
static_assert(offsetof(sub_62f07f0_rdi, f10) == 0x10, "sub_0x62f07f0 rdi+0x10 field");
static_assert(sizeof(sub_62f07f0_rdi) >= 0x18, "sub_0x62f07f0 rdi sizeof lower bound");

static_assert(offsetof(sub_62f07f0_rsp, f20) == 0x20, "sub_0x62f07f0 rsp+0x20 field");
static_assert(sizeof(sub_62f07f0_rsp) >= 0x28, "sub_0x62f07f0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI).
// prologue: push rsi; push rdi; sub rsp,0x28; mov rsi,rcx
// The function takes one pointer argument (rcx = "this") and returns uintptr_t.
// sub_e935700 takes (void* dest, uint64_t size, uint64_t a3, uint64_t a4).
// call qword ptr [0xF9A8C78] takes (uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) and returns void.
extern "C" void sub_e935700(void* dest, uint64_t size, uint64_t a3, uint64_t a4);

uintptr_t sub_62f07f0(void* self);

} // namespace native::helpers
