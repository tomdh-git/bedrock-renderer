#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// State layout for sub_8db490 (0x8db490, size 0x119, Minecraft 1.26.62.01).
// Offsets and widths come straight from the instruction operands [proven].
// Field names and meanings are recovered from the access pattern: the object
// holds three inline strings, each laid out as { ptr, gap, sso_buf, size } at
// strides of 0x28 -- string C at +0x08, string B at +0x30, string A at +0x50.
// The struct is packed so offsetof() matches the observed offsets exactly;
// sizeof is a lower bound (the real object may have trailing padding).
#pragma pack(push, 1)
struct sub_8db490_rcx {
    std::uint8_t pad0x00[0x8];    // +0x00..+0x07 no observed access
    void* ptr_c;                  // +0x08: void*   R 0x8db544, W(byte) 0x8db585
    std::uint8_t pad0x10[0x8];    // +0x10..+0x17 no observed access
    std::uint64_t buf_c;          // +0x18: u64     W 0x8db575
    std::uint64_t size_c;         // +0x20: u64     R 0x8db53a, W 0x8db57d
    std::uint8_t pad0x28[0x8];    // +0x28..+0x2f no observed access (gap to next string)
    void* ptr_b;                  // +0x30: void*   R 0x8db4f5, W(byte) 0x8db536
    std::uint8_t pad0x38[0x8];    // +0x38..+0x3f no observed access
    std::uint64_t buf_b;          // +0x40: u64     W 0x8db526
    std::uint64_t size_b;         // +0x48: u64     R 0x8db4eb, W 0x8db52e
    void* ptr_a;                  // +0x50: void*   R 0x8db4a2, W(byte) 0x8db4e7
    std::uint8_t pad0x58[0x8];    // +0x58..+0x5f no observed access
    std::uint64_t buf_a;          // +0x60: u64     W 0x8db4d7
    std::uint64_t size_a;         // +0x68: u64     R 0x8db498, W 0x8db4df
};
#pragma pack(pop)

// Base register rax is used only as the running size value (lea rdx,[rax+1]).
#pragma pack(push, 1)
struct sub_8db490_rax {
    std::uint8_t pad0x00[0x1];    // +0x00 no observed access as a base
    std::uint8_t f1;              // +0x01: u8      R 0x8db4a6, 0x8db4f9, 0x8db548 (lea rdx,[rax+1])
};
#pragma pack(pop)

// Base register rsp: only the stack home slot at +0x20 is written.
#pragma pack(push, 1)
struct sub_8db490_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f no observed access
    std::uint64_t f20;            // +0x20: u64     W 0x8db58f (stack home slot)
};
#pragma pack(pop)

static_assert(offsetof(sub_8db490_rcx, ptr_c) == 0x8, "sub_0x8db490 rcx+0x8 field");
static_assert(offsetof(sub_8db490_rcx, buf_c) == 0x18, "sub_0x8db490 rcx+0x18 field");
static_assert(offsetof(sub_8db490_rcx, size_c) == 0x20, "sub_0x8db490 rcx+0x20 field");
static_assert(offsetof(sub_8db490_rcx, ptr_b) == 0x30, "sub_0x8db490 rcx+0x30 field");
static_assert(offsetof(sub_8db490_rcx, buf_b) == 0x40, "sub_0x8db490 rcx+0x40 field");
static_assert(offsetof(sub_8db490_rcx, size_b) == 0x48, "sub_0x8db490 rcx+0x48 field");
static_assert(offsetof(sub_8db490_rcx, ptr_a) == 0x50, "sub_0x8db490 rcx+0x50 field");
static_assert(offsetof(sub_8db490_rcx, buf_a) == 0x60, "sub_0x8db490 rcx+0x60 field");
static_assert(offsetof(sub_8db490_rcx, size_a) == 0x68, "sub_0x8db490 rcx+0x68 field");
static_assert(sizeof(sub_8db490_rcx) >= 0x70, "sub_0x8db490 rcx sizeof lower bound");

static_assert(offsetof(sub_8db490_rax, f1) == 0x1, "sub_0x8db490 rax+0x1 field");
static_assert(sizeof(sub_8db490_rax) >= 0x2, "sub_0x8db490 rax sizeof lower bound");

static_assert(offsetof(sub_8db490_rsp, f20) == 0x20, "sub_0x8db490 rsp+0x20 field");
static_assert(sizeof(sub_8db490_rsp) >= 0x28, "sub_0x8db490 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI): RCX = 'this' pointer. Returns void: no exit
// path produces a defined return value (the tail path calls a data-slot
// function that never returns, followed by int3 padding).
// 0x8db490  push rsi; 0x8db491  sub rsp,0x30; 0x8db495  mov rsi,rcx; 0x8db498  mov rax,[rcx+0x68]
void sub_8db490(void* self);

} // namespace native::helpers