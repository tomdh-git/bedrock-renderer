#pragma once
#include <cstddef>
#include <cstdint>

namespace native {
namespace d3d12 {

namespace boundary {
    // vendor thunk via data slot 0xF99FFA0 (sub_eea6040)
    void* thunk_f99ffa0(void* a0, std::uint64_t a1, std::uint32_t a2, std::uint32_t a3, const void* a4, std::uint32_t a5);
    // CRT import thunk: memset (sub_eec6ed0)
    void* sub_eec6ed0(void* dst, std::uint64_t val, std::uint64_t n);
}

// Layout recovered from the disassembly of 0xe83b200 (size 0x1c5, 1.26.62.01).
// RendererContextD3D12 RTX slot 64: growable arena allocator used by the RTX path.
//
//   rcx = this (RendererContextD3D12*), rdx = requested element count.
//   returns (rax) the previous capacity (this+0x2010) on the fast path.
//
// Fields used:
//   this+0x2000 : arena header pointer (hdr*)   [R/W]
//   this+0x2010 : capacity (u64)               [R/W]
//   hdr+0x00    : head block pointer            [R/W]
//   hdr+0x08    : current block pointer         [R/W]
//   hdr+0x10    : used bytes (u64)              [R/W]

static constexpr std::size_t kArenaHdr      = 0x2000; // this+0x2000
static constexpr std::size_t kArenaCapacity  = 0x2010; // this+0x2010
static constexpr std::size_t kHdrHead       = 0x00;   // hdr+0x00
static constexpr std::size_t kHdrCurrent    = 0x08;   // hdr+0x08
static constexpr std::size_t kHdrUsed       = 0x10;   // hdr+0x10
static constexpr std::size_t kBlockSize     = 0x2000; // block size
static constexpr std::size_t kAllocSize     = 0x2008; // allocation size (block + 8)
static constexpr std::size_t kMinCount      = 0x1001; // threshold count

static_assert(kArenaCapacity - kArenaHdr == 0x10, "e83b200: capacity follows hdr");
static_assert(kHdrCurrent - kHdrHead == 0x08, "e83b200: current follows head");
static_assert(kHdrUsed - kHdrCurrent == 0x08, "e83b200: used follows current");

extern "C" std::uint64_t sub_e83b200(void* a0, std::uint64_t count);

} // namespace d3d12
} // namespace native
