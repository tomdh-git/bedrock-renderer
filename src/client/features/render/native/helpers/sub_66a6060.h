#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// State layouts for sub_66a6060 (BgfxFrameBuilder::endFrame), [0x66a6060, 0x66a6182),
// Minecraft Windows 1.26.62.01. Offsets and widths are proven from the instruction
// operands; field names are the lift's interpretation. One struct per base register
// that is dereferenced. Each struct is packed so offsetof() matches the observed
// offset exactly; sizeof is a lower bound (the real object may have more fields).

#pragma pack(push, 1)
// Base register rcx: the endFrame object.
// +0x28: entry** cursor (R: 0x66a606f, R: 0x66a612a)
// +0x30: entry** end (R: 0x66a6073, R: 0x66a612e)
// +0x40: entry* tail entry (R: 0x66a60f8)
struct sub_66a6060_rcx {
    std::uint8_t pad0x00[0x28];
    void* begin;    // +0x28
    void* end;      // +0x30
    std::uint8_t pad0x38[0x8];
    void* tail;     // +0x40
};
#pragma pack(pop)

// Base registers r12/rsi: frame entries, stepped through by 0x10.
// +0x10: flag byte, bit 0 read (R: 0x66a6095 via r12, R: 0x66a6127 via rsi)
#pragma pack(push, 1)
struct sub_66a6060_entry {
    std::uint8_t pad0x00[0x10];
    std::uint8_t flag0x10;  // +0x10
};
#pragma pack(pop)

static_assert(offsetof(sub_66a6060_rcx, begin) == 0x28, "sub_66a6060 rcx+0x28 field");
static_assert(offsetof(sub_66a6060_rcx, end) == 0x30, "sub_66a6060 rcx+0x30 field");
static_assert(offsetof(sub_66a6060_rcx, tail) == 0x40, "sub_66a6060 rcx+0x40 field");
static_assert(sizeof(sub_66a6060_rcx) >= 0x48, "sub_66a6060 rcx sizeof lower bound");

static_assert(offsetof(sub_66a6060_entry, flag0x10) == 0x10, "sub_66a6060 entry+0x10 field");
static_assert(sizeof(sub_66a6060_entry) >= 0x11, "sub_66a6060 entry sizeof lower bound");

// Exact x64 Microsoft ABI mirror of the original function.
// RCX = self: the endFrame object. Return: AL = (begin != end) && flag (0 or 1);
// the upper bytes of RAX keep the begin pointer value (the original only writes AL).
uintptr_t sub_66a6060(void* self);

} // namespace native::helpers
