#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the small-string object copied by sub_0xbc45130 ("VV frame-graph
// builder"), observed in the disassembly of [0xbc45130, 0xbc45291). The same
// struct is used for the source (rdx) and the destination (rcx):
//   +0x00  16-byte header (copied verbatim)
//   +0x10  u64 (copied verbatim)
//   +0x18  data pointer: heap block from the allocator, or inline storage base (&this+0x18) when small
//   +0x28  u64 size in bytes
//   +0x30  u64 capacity
//   +0x38  u32 (copied verbatim)
//   +0x3C  u16 (copied verbatim)
//   +0x40  u8 valid flag: 0 = empty (set at entry), 1 = populated (set on success)
struct FbSsoString {
    uint8_t mHeader[16];     // +0x00  16-byte header, copied from src+0x00
    uint64_t mField10;       // +0x10  copied from src+0x10
    uint8_t* mData;          // +0x18  heap pointer; inline data base (&this+0x18) in the SSO path
    uint64_t mSize;          // +0x28  size in bytes
    uint64_t mCapacity;      // +0x30  capacity
    uint32_t mField38;       // +0x38  copied from src+0x38
    uint16_t mField3C;       // +0x3C  copied from src+0x3C
    uint8_t mReserved3E[2];  // +0x3E  padding, not touched by this function
    uint8_t mValid;          // +0x40  valid flag (0 at entry, 1 on success)
    uint8_t mReserved41[7];  // +0x41..+0x47  padding, not touched by this function
};
static_assert(sizeof(FbSsoString) == 0x48, "sub_bc45130: FbSsoString size");
static_assert(offsetof(FbSsoString, mHeader) == 0x00, "sub_bc45130: src+0x00/dst+0x00 16-byte header");
static_assert(offsetof(FbSsoString, mField10) == 0x10, "sub_bc45130: +0x10 u64");
static_assert(offsetof(FbSsoString, mData) == 0x18, "sub_bc45130: +0x18 data pointer / inline base");
static_assert(offsetof(FbSsoString, mSize) == 0x28, "sub_bc45130: +0x28 size");
static_assert(offsetof(FbSsoString, mCapacity) == 0x30, "sub_bc45130: +0x30 capacity");
static_assert(offsetof(FbSsoString, mField38) == 0x38, "sub_bc45130: +0x38 u32");
static_assert(offsetof(FbSsoString, mField3C) == 0x3C, "sub_bc45130: +0x3C u16");
static_assert(offsetof(FbSsoString, mValid) == 0x40, "sub_bc45130: +0x40 valid flag");

// sub_bc45130(dst = rcx, src = rdx) -> dst (rax = rcx). Exact x64 ABI of the exe function.
FbSsoString* sub_bc45130(FbSsoString* dst, const FbSsoString* src);

} // namespace native::bgfx
