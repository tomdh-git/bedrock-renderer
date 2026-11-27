#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout for sub_56d03a0, reverse-engineered from the disassembly
// of [0x56d03a0, 0x56d04ca). Offsets and widths come from the instruction
// operands; field names/types are best-effort interpretations of the access
// pattern (size fields compared against 0x10/0x1000 are uint64_t, pointers are
// void*, single-byte writes are noted).
//
// One struct per base register that is dereferenced. The struct is packed so
// every declared field sits exactly at its observed offset; sizeof is a lower
// bound (the real object may have compiler-inserted alignment padding).

// Struct for base register rcx/rsi (= the `self` argument).
#pragma pack(push, 1)
struct sub_56d03a0_rcx {
    void* f0;                          // +0x00: pointer R  (0x56d0467:R) / W byte (0x56d04a7:W)
    std::uint8_t pad0x08[0x8];         // +0x08..+0x0f
    std::uint64_t f10;                 // +0x10: uint64 W   (0x56d0497:W)
    std::uint64_t f18;                 // +0x18: uint64 R/W size (0x56d045d:R, 0x56d049f:W)
    std::uint8_t f20;                  // +0x20: uint8  address taken (0x56d043b:R via lea)
    std::uint8_t pad0x21[0x47];        // +0x21..+0x67
    std::uint64_t f68;                 // +0x68: uint64 R   (0x56d043f:R)
    std::uint8_t pad0x70[0x20];        // +0x70..+0x8f
    std::uint8_t f90;                  // +0x90: uint8  address taken (0x56d0416:R via lea)
    std::uint8_t pad0x91[0x37];        // +0x91..+0xc7
    void* fc8;                         // +0xc8: pointer R/W (0x56d040a:R, 0x56d0430:W)
    std::uint8_t pad0xd0[0x8];         // +0xd0..+0xd7
    void* fd8;                         // +0xd8: pointer R  (0x56d03b5:R) / W byte (0x56d0403:W)
    std::uint8_t pad0xe0[0x8];         // +0xe0..+0xe7
    std::uint64_t fe8;                 // +0xe8: uint64 W   (0x56d03ed:W)
    std::uint64_t ff0;                 // +0xf0: uint64 R/W size (0x56d03a8:R, 0x56d03f8:W)
};
#pragma pack(pop)

// Struct for base register r8.
#pragma pack(push, 1)
struct sub_56d03a0_r8 {
    void* f0;                          // +0x00: pointer R  (0x56d0423:R via *[rcx-8])
};
#pragma pack(pop)

// Struct for base register rax (used as a heap/object base).
#pragma pack(push, 1)
struct sub_56d03a0_rax {
    std::uint64_t f0[2];               // +0x00: uint64[2] W (0x56d044d:W movups 16 bytes)
    std::uint64_t f10;                 // +0x10: uint64 W   (0x56d0450:W)
    std::uint8_t pad0x18[0x8];         // +0x18..+0x1f
    void* f20;                         // +0x20: pointer R  (0x56d0426:R vtable slot)
};
#pragma pack(pop)

// Struct for base register rsp (stack home slot).
#pragma pack(push, 1)
struct sub_56d03a0_rsp {
    std::uint8_t pad0x00[0x20];        // +0x00..+0x1f
    std::uint64_t f20;                 // +0x20: uint64 W   (0x56d04b0:W)
};
#pragma pack(pop)

// sizeof lower bound: largest observed offset plus width across all structs.

static_assert(offsetof(sub_56d03a0_rcx, f0) == 0x0, "sub_0x56d03a0 rcx+0x0 field");
static_assert(offsetof(sub_56d03a0_rcx, f10) == 0x10, "sub_0x56d03a0 rcx+0x10 field");
static_assert(offsetof(sub_56d03a0_rcx, f18) == 0x18, "sub_0x56d03a0 rcx+0x18 field");
static_assert(offsetof(sub_56d03a0_rcx, f20) == 0x20, "sub_0x56d03a0 rcx+0x20 field");
static_assert(offsetof(sub_56d03a0_rcx, f68) == 0x68, "sub_0x56d03a0 rcx+0x68 field");
static_assert(offsetof(sub_56d03a0_rcx, f90) == 0x90, "sub_0x56d03a0 rcx+0x90 field");
static_assert(offsetof(sub_56d03a0_rcx, fc8) == 0xc8, "sub_0x56d03a0 rcx+0xc8 field");
static_assert(offsetof(sub_56d03a0_rcx, fd8) == 0xd8, "sub_0x56d03a0 rcx+0xd8 field");
static_assert(offsetof(sub_56d03a0_rcx, fe8) == 0xe8, "sub_0x56d03a0 rcx+0xe8 field");
static_assert(offsetof(sub_56d03a0_rcx, ff0) == 0xf0, "sub_0x56d03a0 rcx+0xf0 field");
static_assert(sizeof(sub_56d03a0_rcx) >= 0xf8, "sub_0x56d03a0 rcx sizeof lower bound");

static_assert(offsetof(sub_56d03a0_r8, f0) == 0x0, "sub_0x56d03a0 r8+0x0 field");
static_assert(sizeof(sub_56d03a0_r8) >= 0x8, "sub_0x56d03a0 r8 sizeof lower bound");

static_assert(offsetof(sub_56d03a0_rax, f0) == 0x0, "sub_0x56d03a0 rax+0x0 field");
static_assert(offsetof(sub_56d03a0_rax, f10) == 0x10, "sub_0x56d03a0 rax+0x10 field");
static_assert(offsetof(sub_56d03a0_rax, f20) == 0x20, "sub_0x56d03a0 rax+0x20 field");
static_assert(sizeof(sub_56d03a0_rax) >= 0x28, "sub_0x56d03a0 rax sizeof lower bound");

static_assert(offsetof(sub_56d03a0_rsp, f20) == 0x20, "sub_0x56d03a0 rsp+0x20 field");
static_assert(sizeof(sub_56d03a0_rsp) >= 0x28, "sub_0x56d03a0 rsp sizeof lower bound");

// Callee declarations (native symbols / boundary).
extern "C" std::uintptr_t sub_e935700(std::uint64_t a1, std::uint64_t a2, std::uint64_t a3, std::uint64_t a4);
extern "C" void sub_655cea0(void* ptr);
extern "C" std::uintptr_t sub_eea6040(void* a);          // [0xF99FFA0] import slot target
extern "C" std::uintptr_t sub_slot_f9a8c78(std::uint64_t a1, std::uint64_t a2, std::uint64_t a3, std::uint64_t a4);  // [0xF9A8C78] import slot target

// Signature (x64 Microsoft ABI). Prologue: push rsi; sub rsp,0x30; mov rsi,rcx; mov rax,[rcx+0xF0].
std::uintptr_t sub_56d03a0(void* self);

} // namespace native::helpers
