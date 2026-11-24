#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the VvFrameGraphBuilder object as observed in sub_0xbc431b0.
// Only offsets the function touches are declared; padding is unnamed.
// Verified against the disassembly of [0xbc431b0, 0xbc432d9).
struct VvFrameGraphBuilder {
    uint8_t mPad00[0x10];      // +0x00  16 bytes, copied from src
    uint64_t mField10;         // +0x10  8 bytes, copied from src
    uint8_t* mData;            // +0x18  8 bytes, heap allocation or inline (SSO) data
    uint8_t mPad20[0x8];       // +0x20
    uint64_t mSize;            // +0x28  8 bytes, size
    uint64_t mCapacity;        // +0x30  8 bytes, capacity
    uint32_t mField38;         // +0x38  4 bytes, copied from src
    uint16_t mField3C;         // +0x3C  2 bytes, copied from src
};
static_assert(offsetof(VvFrameGraphBuilder, mField10) == 0x10, "sub_bc431b0 reads/writes dst+0x10");
static_assert(offsetof(VvFrameGraphBuilder, mData) == 0x18, "sub_bc431b0 reads/writes dst+0x18 (mData)");
static_assert(offsetof(VvFrameGraphBuilder, mSize) == 0x28, "sub_bc431b0 reads src+0x28 and writes dst+0x28 (mSize)");
static_assert(offsetof(VvFrameGraphBuilder, mCapacity) == 0x30, "sub_bc431b0 branches on src+0x30 and writes dst+0x30 (mCapacity)");
static_assert(offsetof(VvFrameGraphBuilder, mField38) == 0x38, "sub_bc431b0 reads/writes dst+0x38");
static_assert(offsetof(VvFrameGraphBuilder, mField3C) == 0x3C, "sub_bc431b0 reads/writes dst+0x3C");
static_assert(sizeof(VvFrameGraphBuilder) >= 0x3E, "sub_bc431b0 touches up to dst+0x3E");

// sub_bc431b0(VvFrameGraphBuilder* dst = rcx, const VvFrameGraphBuilder* src = rdx) -> VvFrameGraphBuilder* (rax = dst at ret)
VvFrameGraphBuilder* sub_bc431b0(VvFrameGraphBuilder* dst, const VvFrameGraphBuilder* src);

} // namespace native::bgfx
