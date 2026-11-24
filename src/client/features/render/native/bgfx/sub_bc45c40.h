#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the "BgfxFrameBuilder slot 0" allocator object (this = rcx on entry).
// Observed in the disassembly of [0xbc45c40, 0xbc45dab):
//   +0x10 u32 count      (lock xadd fetch_add(1))
//   +0x18 u64 slab base  (slot i is handed out at base + i * 0x1048; may be null)
//   +0x20 u32 capacity   (branched on)
//   +0x28 u64 free head  (lock cmpxchg pop of the recycled-node list)
struct FbSlot0 {
    std::atomic<std::uint32_t> mCount;   // +0x10
    std::uint64_t mBase;                 // +0x18
    std::uint32_t mCapacity;             // +0x20
    std::uint32_t mReserved24;           // +0x24
    std::atomic<std::uint64_t> mFree;    // +0x28
};
static_assert(sizeof(FbSlot0) == 0x30, "FbSlot0 layout (sub_bc45c40)");
static_assert(offsetof(FbSlot0, mCount) == 0x10, "sub_bc45c40 reads/writes this+0x10 as count");
static_assert(offsetof(FbSlot0, mBase) == 0x18, "sub_bc45c40 reads this+0x18 as slab base");
static_assert(offsetof(FbSlot0, mCapacity) == 0x20, "sub_bc45c40 branches on this+0x20 capacity");
static_assert(offsetof(FbSlot0, mFree) == 0x28, "sub_bc45c40 uses this+0x28 as free-list head");

// Layout of one 0x1048-byte node handed out by the allocator. The function only touches
// +0x1000..+0x102F (zeroed on allocation), +0x1030 (claim count, lock cmpxchg/xadd),
// +0x1038 (back-pointer) and +0x1040 (init byte set to 1).
struct FbSlot0Node {
    std::uint8_t mReserved0000[0x1030];   // +0x0000..+0x102F not read or written here
    std::atomic<std::uint32_t> mNext;     // +0x1030 tagged next pointer / claim count
    std::uint8_t mReserved1034[4];        // +0x1034..+0x1037
    std::uint64_t mBack;                  // +0x1038 back-pointer (head value installed on pop)
    std::uint8_t mInit;                   // +0x1040 set to 1 when a node is handed out
    std::uint8_t mReserved1041[7];        // +0x1041..+0x1047
};
static_assert(sizeof(FbSlot0Node) == 0x1048, "FbSlot0Node layout (sub_bc45c40)");
static_assert(offsetof(FbSlot0Node, mNext) == 0x1030, "sub_bc45c40 uses node+0x1030 as claim count");
static_assert(offsetof(FbSlot0Node, mBack) == 0x1038, "sub_bc45c40 writes node+0x1038 on pop/alloc");
static_assert(offsetof(FbSlot0Node, mInit) == 0x1040, "sub_bc45c40 writes node+0x1040 = 1 on alloc");

// sub_bc45c40(that = rcx) -> rax: hand out one 0x1048-byte slot from the slot-0 allocator:
// either slab slot `mCount` (mBase + mCount * 0x1048, mBase may be null) or a recycled node
// popped from the lock-free free list (mFree), allocating a fresh 0x1048-byte node via the
// imported allocator when the list is empty.
extern "C" void* sub_bc45c40(FbSlot0* that);

} // namespace native::bgfx
