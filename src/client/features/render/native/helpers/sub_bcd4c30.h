#pragma once
#include <cstddef>
#include <cstdint>

// sub_e935700 (0xe935700) is a lift-set callee (tail jump to sub_392960);
// forward-declared here instead of including sub_e935700.h.
// ABI recovered from sub_392960: the single input argument arrives in RCX,
// the result is returned in RAX; no other input register and no stack argument
// is read by the callee.
namespace native {
void* sub_e935700(void* a0);
} // namespace native

namespace native::helpers {

// State layout for sub_bcd4c30 ([0xbcd4c30, 0xbcd4d1d), Minecraft Windows 1.26.62.01).
// The state holds two small-string buffers. Offsets and widths are [proven] from the
// instruction operands of the listing; field names and meanings are the lift decisions:
//   buffer 0: pointer +0x00, size +0x10, capacity +0x18
//   buffer 1: pointer +0x20, size +0x30, capacity +0x38
// A capacity below 0x10 denotes the inline (empty) state; at or above 0x10 the
// buffer is heap-backed and is released through native::sub_e935700.
struct sub_bcd4c30_state {
    void* buffer0_ptr;                   // +0x00 [R] heap buffer pointer; [W] low byte = 0 at reset
    std::uint8_t pad0x08[0x10 - 0x08];   // +0x08..+0x0f: no observed access
    std::uint64_t buffer0_size;          // +0x10 [W] = 0 at reset
    std::uint64_t buffer0_cap;           // +0x18 [R] compared to 0x10; [W] = 0xF at reset
    void* buffer1_ptr;                   // +0x20 [R] heap buffer pointer; [W] low byte = 0 at reset
    std::uint8_t pad0x28[0x30 - 0x28];   // +0x28..+0x2f: no observed access
    std::uint64_t buffer1_size;          // +0x30 [W] = 0 at reset
    std::uint64_t buffer1_cap;           // +0x38 [R] compared to 0x10; [W] = 0xF at reset
};

static_assert(offsetof(sub_bcd4c30_state, buffer0_ptr) == 0x00, "sub_bcd4c30_state buffer0_ptr at +0x00");
static_assert(offsetof(sub_bcd4c30_state, buffer0_size) == 0x10, "sub_bcd4c30_state buffer0_size at +0x10");
static_assert(offsetof(sub_bcd4c30_state, buffer0_cap) == 0x18, "sub_bcd4c30_state buffer0_cap at +0x18");
static_assert(offsetof(sub_bcd4c30_state, buffer1_ptr) == 0x20, "sub_bcd4c30_state buffer1_ptr at +0x20");
static_assert(offsetof(sub_bcd4c30_state, buffer1_size) == 0x30, "sub_bcd4c30_state buffer1_size at +0x30");
static_assert(offsetof(sub_bcd4c30_state, buffer1_cap) == 0x38, "sub_bcd4c30_state buffer1_cap at +0x38");
static_assert(sizeof(void*) == 8, "sub_bcd4c30: pointer-sized fields (x64 Microsoft ABI)");

// x64 Microsoft ABI: count arrives in RCX, state in R8; RDX is passed but unread
// by the original function. RAX is dead at ret; the lift returns 0.
uintptr_t sub_bcd4c30(uint64_t count, uint64_t, sub_bcd4c30_state* state);

} // namespace native::helpers
