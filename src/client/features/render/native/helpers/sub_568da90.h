#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_568da90, reverse-engineered from the disassembly
// of [0x568da90, 0x568db87), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.

// Struct for base register rcx/rsi (the context pointer 'a0', passed in RCX, copied to RSI).
// Dereferenced at +0x0, +0x10, +0x18, +0x20, +0x28.
#pragma pack(push, 1)
struct sub_568da90_ctx {
    void* f0;               // +0x00: buffer #1 begin (R at 0x568db1e, W at 0x568db56)
    std::uint8_t pad0x8[0x8]; // +0x08..+0x0f padding (no observed access)
    std::uint64_t f10;      // +0x10: buffer #1 end   (R at 0x568db26, W at 0x568db59)
    std::uint64_t f18;      // +0x18: buffer #2 begin (R at 0x568da9e, 0x568daa7)
    std::uint64_t f20;      // +0x20: buffer #2 end   (R at 0x568daab)
    std::uint64_t f28;      // +0x28: buffer #2 limit (R at 0x568dadf)
};
#pragma pack(pop)

// Struct for base register rdi (a buffer begin pointer, iterated in 0x20-byte steps).
// Dereferenced at +0x18 (element index byte) and -8 (heap header).
#pragma pack(push, 1)
struct sub_568da90_buf {
    std::uint8_t pad0x00[0x18];   // +0x00..+0x17 padding (no observed access)
    std::int8_t f18;              // +0x18: element index byte (R at 0x568dac0)
};
#pragma pack(pop)

// Struct for base register rsp (stack frame).
#pragma pack(push, 1)
struct sub_568da90_stack {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;            // +0x20: fail-path dead slot (W at 0x568db6d)
    std::uint8_t pad0x28[0x7];    // +0x28..+0x2e padding (no observed access)
    std::uint8_t f2f;             // +0x2f: address-taken scratch byte (R at 0x568dab4 via lea rbx,[rsp+0x2f])
};
#pragma pack(pop)

static_assert(offsetof(sub_568da90_ctx, f0) == 0x0, "sub_568da90 ctx+0x0 field");
static_assert(offsetof(sub_568da90_ctx, f10) == 0x10, "sub_568da90 ctx+0x10 field");
static_assert(offsetof(sub_568da90_ctx, f18) == 0x18, "sub_568da90 ctx+0x18 field");
static_assert(offsetof(sub_568da90_ctx, f20) == 0x20, "sub_568da90 ctx+0x20 field");
static_assert(offsetof(sub_568da90_ctx, f28) == 0x28, "sub_568da90 ctx+0x28 field");
static_assert(sizeof(sub_568da90_ctx) >= 0x30, "sub_568da90 ctx sizeof lower bound");

static_assert(offsetof(sub_568da90_buf, f18) == 0x18, "sub_568da90 buf+0x18 field");
static_assert(sizeof(sub_568da90_buf) >= 0x19, "sub_568da90 buf sizeof lower bound");

static_assert(offsetof(sub_568da90_stack, f20) == 0x20, "sub_568da90 stack+0x20 field");
static_assert(offsetof(sub_568da90_stack, f2f) == 0x2f, "sub_568da90 stack+0x2f field");
static_assert(sizeof(sub_568da90_stack) >= 0x30, "sub_568da90 stack sizeof lower bound");

// Signature (x64 Microsoft ABI): single context argument in RCX, return void.
// 0x568da90  push r15; ...; 0x568da9b  mov rsi,rcx  (context copied to RSI)
void sub_568da90(void* a0);   // return void; argument is the context pointer in RCX

} // namespace native::helpers
