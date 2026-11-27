#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout for sub_67cace0, reverse-engineered from the disassembly
// of [0x67cace0, 0x67cadd3), Minecraft Windows 1.26.62.01.
// Offsets/widths/signedness are [proven] from instruction operands; field names and meanings are [open].
#pragma pack(push, 1)
struct sub_67cace0_state {
    // +0x00: R/W - base pointer of the block arena (set to 0 on flush)
    uint8_t* base;
    // +0x08: R - end pointer of the block arena (walk limit)
    uint8_t* end;
    // +0x10: R/W - cursor/limit pointer (set to 0 on flush)
    uint8_t* cursor;
};
#pragma pack(pop)

// Block layout (stride 0x50), accessed via rdi during the walk
#pragma pack(push, 1)
struct sub_67cace0_block {
    uint8_t pad0x00[0x18];   // +0x00..+0x17: no observed accesses
    void* data;              // +0x18: R/W - data pointer (submitted to sub_e935700)
    uint8_t pad0x20[0x8];    // +0x20..+0x27: no observed accesses
    std::uint64_t flags;     // +0x28: W - cleared to 0 on reset
    std::uint64_t size;      // +0x30: R/W - set to 0xF on reset, compared against 0x10
    uint8_t pad0x38[0x8];    // +0x38..+0x3F: no observed accesses
    std::uint8_t type;       // +0x40: R - compared against 6
    uint8_t pad0x41[0xF];    // +0x41..+0x4F: pad to stride 0x50
};
#pragma pack(pop)

// sizeof lower bounds
static_assert(offsetof(sub_67cace0_state, base) == 0x0, "sub_67cace0 state+0x0 field");
static_assert(offsetof(sub_67cace0_state, end) == 0x8, "sub_67cace0 state+0x8 field");
static_assert(offsetof(sub_67cace0_state, cursor) == 0x10, "sub_67cace0 state+0x10 field");
static_assert(sizeof(sub_67cace0_state) >= 0x18, "sub_67cace0 state sizeof lower bound");

static_assert(offsetof(sub_67cace0_block, data) == 0x18, "sub_67cace0 block+0x18 field");
static_assert(offsetof(sub_67cace0_block, flags) == 0x28, "sub_67cace0 block+0x28 field");
static_assert(offsetof(sub_67cace0_block, size) == 0x30, "sub_67cace0 block+0x30 field");
static_assert(offsetof(sub_67cace0_block, type) == 0x40, "sub_67cace0 block+0x40 field");
static_assert(sizeof(sub_67cace0_block) >= 0x50, "sub_67cace0 block sizeof lower bound (stride 0x50)");

// sub_e935700 is a lift-set callee (tail jump to sub_392960). ABI: argument in RCX, result in RAX.
// Forward-declared in sub_e935700.h; include that header where needed.

// Signature (x64 Microsoft ABI): argument is 'this' in RCX, return value in RAX.
uintptr_t sub_67cace0(void* self);

} // namespace native::helpers