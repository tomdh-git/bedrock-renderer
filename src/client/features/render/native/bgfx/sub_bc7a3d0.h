#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// sub_bc7a3d0 ("bgfx shutdown") - resize/destroy helper for the paged element store of the
// state object. Lifted from [0xbc7a3d0, 0xbc7a79c), size 0x3cc, Minecraft Windows 1.26.62.01.
// Every offset below is read or written by the function [V]; per-instruction address cites
// live in sub_bc7a3d0.cpp.
//
// Element record, stride 0x28 (40 bytes):
//   +0x00 void*   ptr     resource handle; destroyed via sub_eea6040(g, ptr, 0, 0), then
//                           tombstoned to imageBase() + 0xF847A07
//   +0x08 uint32  live    nonzero => element is live
//   +0x10 byte[16]        zeroed by movups
//   +0x20 uint8           = 0
//   +0x22 uint32          = 0
//   +0x26 uint8           = 0
//   +0x27 pad; sizeof == 0x28
struct sub_bc7a3d0_elem {
    void* ptr;                          // +0x00
    std::uint32_t live;                 // +0x08
    std::uint8_t reserved0x0c[4];       // +0x0c
    std::uint8_t zero0x10[16];          // +0x10
    std::uint8_t b0x20;                 // +0x20
    std::uint8_t reserved0x21[1];       // +0x21
    std::uint32_t d0x22;                // +0x22
    std::uint8_t b0x26;                 // +0x26
    std::uint8_t reserved0x27[1];       // +0x27
};
static_assert(offsetof(sub_bc7a3d0_elem, ptr) == 0x00, "sub_bc7a3d0: elem ptr at +0x00");
static_assert(offsetof(sub_bc7a3d0_elem, live) == 0x08, "sub_bc7a3d0: elem live at +0x08");
static_assert(offsetof(sub_bc7a3d0_elem, zero0x10) == 0x10, "sub_bc7a3d0: elem zero block at +0x10");
static_assert(offsetof(sub_bc7a3d0_elem, b0x20) == 0x20, "sub_bc7a3d0: elem b0x20 at +0x20");
static_assert(offsetof(sub_bc7a3d0_elem, d0x22) == 0x22, "sub_bc7a3d0: elem d0x22 at +0x22");
static_assert(offsetof(sub_bc7a3d0_elem, b0x26) == 0x26, "sub_bc7a3d0: elem b0x26 at +0x26");
static_assert(sizeof(sub_bc7a3d0_elem) == 0x28, "sub_bc7a3d0: elem size 0x28");

static constexpr std::size_t kElemStride = 0x28;           // 40 bytes per element (magic /40)
static constexpr std::size_t kInlineElemCount = 0x1000;    // elements stored inline in the state object
static constexpr std::size_t kInlineElemBytes = 0x28000;   // kInlineElemCount * kElemStride
static constexpr std::size_t kBlockElemBytes = 0x28000;    // element bytes per chained block
static constexpr std::size_t kBlockSize = 0x28008;         // block: elements + next-pointer qword at +0x28000
static constexpr std::size_t kStateChainHead = 0x28000;    // chain-head descriptor (first block @+0, tail @+8, capacity @+0x10)
static constexpr std::size_t kStateUsedBytes = 0x28008;    // = elementCount * kElemStride
static constexpr std::size_t kStateCapacityBytes = 0x28010; // reserved bytes
static constexpr std::uintptr_t kTombstoneRva = 0xF847A07; // value stored to elem.ptr after destroy

// State object (the rcx 'this' argument):
//   +0x0000..0x27FF inline element array (kInlineElemCount x kElemStride)
//   +0x28000 void*  chainHead   head descriptor: +0x00 first block, +0x08 tail block, +0x10 capacity bytes
//   +0x28008 uint64 usedBytes   = elementCount * kElemStride
//   +0x28010 uint64 capacityBytes
//   sizeof == 0x28018
struct sub_bc7a3d0_state {
    std::uint8_t inlineElems[kInlineElemBytes];  // +0x0000
    void* chainHead;              // +0x28000
    std::uint64_t usedBytes;      // +0x28008
    std::uint64_t capacityBytes;  // +0x28010
};
static_assert(offsetof(sub_bc7a3d0_state, chainHead) == 0x28000, "sub_bc7a3d0: state chainHead at +0x28000");
static_assert(offsetof(sub_bc7a3d0_state, usedBytes) == 0x28008, "sub_bc7a3d0: state usedBytes at +0x28008");
static_assert(offsetof(sub_bc7a3d0_state, capacityBytes) == 0x28010, "sub_bc7a3d0: state capacityBytes at +0x28010");
static_assert(sizeof(sub_bc7a3d0_state) == 0x28018, "sub_bc7a3d0: state size 0x28018");

// Image data referenced by the function (rdis prints RVAs; VA = imageBase() + RVA):
static constexpr std::uintptr_t kAllocatorGlobalRva = 0x12ADF800;  // mov rcx,[0x12ADF800] (allocator interface)
static constexpr std::uintptr_t kThunkSlotRva = 0xF99FFA0;         // call [0xF99FFA0] / mov r10,[0xF99FFA0]

// std::uint64_t sub_bc7a3d0(sub_bc7a3d0_state* self /*rcx*/, std::uint64_t count /*rdx*/)
// Destroys elements [count, oldElementCount) via sub_eea6040(allocator, elem->ptr, 0, 0),
// grows the chained block storage to hold `count` elements, zero-initializes
// [oldElementCount, count), sets usedBytes = count * kElemStride and returns it in rax.
std::uint64_t sub_bc7a3d0(sub_bc7a3d0_state* self, std::uint64_t count);

} // namespace native::bgfx
