#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the source object read by sub_0xbc44b40 ("BgfxFrameBuilder slot 41").

// Observed in the disassembly of [0xbc44b40, 0xbc44c73): a 16-byte header at

// +0x00, a u64 at +0x10, a data pointer at +0x18, size at +0x28, capacity at

// +0x30, a u32 at +0x38 and a u16 at +0x3C. Size 0x40.

struct FbSlot41Src {
    uint8_t mHeader[16];     // +0x00  16-byte header, copied to dst+0x08

    uint64_t mField10;       // +0x10  copied to dst+0x18

    uint8_t* mData;          // +0x18  heap pointer, or inline data base (&src+0x18)

    uint8_t mReserved20[8];  // +0x20  not read by this function

    uint64_t mSize;          // +0x28  size (r14)

    uint64_t mCapacity;      // +0x30  capacity

    uint32_t mField38;       // +0x38  copied to dst+0x40

    uint16_t mField3C;       // +0x3C  copied to dst+0x44

    uint8_t mReserved3E[2];  // +0x3E

};
static_assert(sizeof(FbSlot41Src) == 0x40, "FbSlot41Src layout (sub_bc44b40)");
static_assert(offsetof(FbSlot41Src, mHeader) == 0x00, "sub_bc44b40 reads src+0x00 as 16-byte header");
static_assert(offsetof(FbSlot41Src, mField10) == 0x10, "sub_bc44b40 reads src+0x10");
static_assert(offsetof(FbSlot41Src, mData) == 0x18, "sub_bc44b40 reads src+0x18 as data pointer");
static_assert(offsetof(FbSlot41Src, mSize) == 0x28, "sub_bc44b40 reads src+0x28 as size");
static_assert(offsetof(FbSlot41Src, mCapacity) == 0x30, "sub_bc44b40 branches on src+0x30 capacity");
static_assert(offsetof(FbSlot41Src, mField38) == 0x38, "sub_bc44b40 reads src+0x38");
static_assert(offsetof(FbSlot41Src, mField3C) == 0x3C, "sub_bc44b40 reads src+0x3C");

// Layout of the destination object written by sub_0xbc44b40. Same small-string

// header as FbSlot41Src but with a leading u8 tag (shifting the header fields

// by +8), a trailing u32/u16 pair and a pointer field. Size 0x50.

struct FbSlot41Dst {
    uint8_t mTag;            // +0x00  written (dl = low byte of 2nd argument)

    uint8_t mReserved01[7];  // +0x01

    uint8_t mHeader[16];     // +0x08  written from src+0x00 (16 bytes)

    uint64_t mField10;       // +0x18  written from src+0x10

    uint8_t* mData;          // +0x20  heap pointer or inline data destination

    uint64_t mReserved28;    // +0x28  written 0 by this function

    uint64_t mSize;          // +0x30  written (size)

    uint64_t mCapacity;      // +0x38  written (capacity)

    uint32_t mField38;       // +0x40  written from src+0x38

    uint16_t mField3C;       // +0x44  written from src+0x3C

    uint8_t mReserved46[2];  // +0x46

    void* mField48;          // +0x48  written (4th argument)

};
static_assert(sizeof(FbSlot41Dst) == 0x50, "FbSlot41Dst layout (sub_bc44b40)");
static_assert(offsetof(FbSlot41Dst, mTag) == 0x00, "sub_bc44b40 writes dst+0x00 as tag");
static_assert(offsetof(FbSlot41Dst, mHeader) == 0x08, "sub_bc44b40 writes dst+0x08 as 16-byte header");
static_assert(offsetof(FbSlot41Dst, mField10) == 0x18, "sub_bc44b40 writes dst+0x18");
static_assert(offsetof(FbSlot41Dst, mData) == 0x20, "sub_bc44b40 writes dst+0x20 as data pointer");
static_assert(offsetof(FbSlot41Dst, mReserved28) == 0x28, "sub_bc44b40 zeroes dst+0x28");
static_assert(offsetof(FbSlot41Dst, mSize) == 0x30, "sub_bc44b40 writes dst+0x30 as size");
static_assert(offsetof(FbSlot41Dst, mCapacity) == 0x38, "sub_bc44b40 writes dst+0x38 as capacity");
static_assert(offsetof(FbSlot41Dst, mField38) == 0x40, "sub_bc44b40 writes dst+0x40");
static_assert(offsetof(FbSlot41Dst, mField3C) == 0x44, "sub_bc44b40 writes dst+0x44");
static_assert(offsetof(FbSlot41Dst, mField48) == 0x48, "sub_bc44b40 writes dst+0x48");

// sub_bc44b40(dst = rcx, tag = rdx low byte, src = r8, extra = r9) -> dst (rax)

FbSlot41Dst* sub_bc44b40(FbSlot41Dst* dst, uint8_t tag, const FbSlot41Src* src, void* extra);

} // namespace native::bgfx

