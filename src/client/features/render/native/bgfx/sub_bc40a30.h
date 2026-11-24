#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the BgfxFrameBuilder object as observed in sub_0xbc40a30 (endFrame).
// Only offsets the function touches are declared; padding is unnamed.
// Verified against the disassembly of [0xbc40a30, 0xbc40b76).
struct BgfxFrameBuilder {
    uint8_t mPad00[0x10];      // +0x00  16 bytes, copied via movups
    uint64_t mField10;         // +0x10  8 bytes
    uint8_t* mData;            // +0x18  8 bytes, data pointer (heap) or inline data
    uint8_t mPad20[0x8];       // +0x20
    uint64_t mSize;            // +0x28  8 bytes, size (rbx)
    uint64_t mCapacity;        // +0x30  8 bytes, capacity
    uint32_t mField38;         // +0x38  4 bytes
    uint16_t mField3C;         // +0x3C  2 bytes
    uint8_t mPad3E[0x2];       // +0x3E
    uint8_t mField40[0x10];    // +0x40  16 bytes, zeroed
    uint8_t mField50[0x10];    // +0x50  16 bytes, zeroed
    uint8_t mField60[0x10];    // +0x60  16 bytes, zeroed
    uint8_t mPad70[0x8];       // +0x70
    uint8_t mField78;          // +0x78  1 byte
    uint8_t mPad79[0x7];       // +0x79
    uint8_t mField80;          // +0x80  1 byte
};
static_assert(offsetof(BgfxFrameBuilder, mField10) == 0x10);
static_assert(offsetof(BgfxFrameBuilder, mData) == 0x18);
static_assert(offsetof(BgfxFrameBuilder, mSize) == 0x28);
static_assert(offsetof(BgfxFrameBuilder, mCapacity) == 0x30);
static_assert(offsetof(BgfxFrameBuilder, mField38) == 0x38);
static_assert(offsetof(BgfxFrameBuilder, mField3C) == 0x3C);
static_assert(offsetof(BgfxFrameBuilder, mField40) == 0x40);
static_assert(offsetof(BgfxFrameBuilder, mField50) == 0x50);
static_assert(offsetof(BgfxFrameBuilder, mField60) == 0x60);
static_assert(offsetof(BgfxFrameBuilder, mField78) == 0x78);
static_assert(offsetof(BgfxFrameBuilder, mField80) == 0x80);
static_assert(sizeof(BgfxFrameBuilder) >= 0x81);

// endFrame(BgfxFrameBuilder* this = rcx, void* frameData = rdx) -> BgfxFrameBuilder* (rax = this)
BgfxFrameBuilder* endFrame(BgfxFrameBuilder* dst, void* src);

} // namespace native::bgfx
