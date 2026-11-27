#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_567a5b0, reverse-engineered from the disassembly
// of [0x567a5b0, 0x567a6be), Minecraft Windows 1.26.62.01.
// One struct per base register that is dereferenced.
// Field f<hex> is at offset 0x<hex>. Packed (#pragma pack(1)) so offsetof() matches
// the observed offsets exactly; sizeof is a lower bound.

// Struct for base register rcx (= self argument, dereferenced in this function)
#pragma pack(push, 1)
struct sub_567a5b0_rcx {
    void* f0;   // +0x00: void* R/W  (R/W cited: 0x567a5c9:R, 0x567a642:R, 0x567a675:W)
    std::uint64_t f8;   // +0x08: std::uint64_t R/W  (R/W cited: 0x567a5d5:R, 0x567a683:W)
    std::uint64_t f10;   // +0x10: std::uint64_t R/W  (R/W cited: 0x567a645:R, 0x567a692:W)
};
#pragma pack(pop)

// Struct for base register r15 (dereferenced in this function)
#pragma pack(push, 1)
struct sub_567a5b0_r15 {
    std::uint8_t pad0x00[0x18];   // +0x00..+0x17 padding
    void* f18;   // +0x18: void* R/W  (R/W cited: 0x567a5f5:W, 0x567a614:R)
    std::uint8_t pad0x20[0x8];   // +0x20..+0x27 padding
    std::uint64_t f28;   // +0x28: std::uint64_t W  (R/W cited: 0x567a5e5:W)
    std::uint64_t f30;   // +0x30: std::uint64_t R/W  (R/W cited: 0x567a5ed:W, 0x567a60a:R)
    std::uint8_t pad0x38[0x8];   // +0x38..+0x3f padding
    std::uint8_t f40;   // +0x40: std::uint8_t R  (R/W cited: 0x567a603:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function)
#pragma pack(push, 1)
struct sub_567a5b0_rax {
    std::uint8_t pad0x00[0x1];   // +0x00..+0x00 padding
    std::uint8_t f1;   // +0x01: std::uint8_t R  (R/W cited: 0x567a618:R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function)
#pragma pack(push, 1)
struct sub_567a5b0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding
    std::uint64_t f20;   // +0x20: std::uint64_t W  (R/W cited: 0x567a6a4:W)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_567a5b0_rcx, f0) == 0x0, "sub_0x567a5b0 rcx+0x0 field");
static_assert(offsetof(sub_567a5b0_rcx, f8) == 0x8, "sub_0x567a5b0 rcx+0x8 field");
static_assert(offsetof(sub_567a5b0_rcx, f10) == 0x10, "sub_0x567a5b0 rcx+0x10 field");
static_assert(sizeof(sub_567a5b0_rcx) >= 0x18, "sub_0x567a5b0 rcx sizeof lower bound");

static_assert(offsetof(sub_567a5b0_r15, f18) == 0x18, "sub_0x567a5b0 r15+0x18 field");
static_assert(offsetof(sub_567a5b0_r15, f28) == 0x28, "sub_0x567a5b0 r15+0x28 field");
static_assert(offsetof(sub_567a5b0_r15, f30) == 0x30, "sub_0x567a5b0 r15+0x30 field");
static_assert(offsetof(sub_567a5b0_r15, f40) == 0x40, "sub_0x567a5b0 r15+0x40 field");
static_assert(sizeof(sub_567a5b0_r15) >= 0x41, "sub_0x567a5b0 r15 sizeof lower bound");

static_assert(offsetof(sub_567a5b0_rax, f1) == 0x1, "sub_0x567a5b0 rax+0x1 field");
static_assert(sizeof(sub_567a5b0_rax) >= 0x2, "sub_0x567a5b0 rax sizeof lower bound");

static_assert(offsetof(sub_567a5b0_rsp, f20) == 0x20, "sub_0x567a5b0 rsp+0x20 field");
static_assert(sizeof(sub_567a5b0_rsp) >= 0x28, "sub_0x567a5b0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI): argument rcx = self. Return type is uintptr_t;
// callers consume the return value as a pointer-sized value. The function performs
// no calls that return to it except sub_e935700 (returns void) and the indirect
// slot call via [0xF9A8C78] (returns void); the returned rax/rdx-derived pointer
// comes from self fields.
uintptr_t sub_567a5b0(void* self);

} // namespace native::helpers
