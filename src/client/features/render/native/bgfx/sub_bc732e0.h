#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// Layout reconstructed from the disassembly of 0xbc732e0 (size 0x280,
// 0xbc732e0..0xbc73560, sub_bc732e0, 1.26.62.01).
struct StreamFrame732e0 {
    char pad_0x0000[0xE05820];
    std::uint32_t writePos;                 // +0xE05820
    std::uint8_t data[0xE4B8B0 - 0xE05828]; // +0xE05828 .. +0xE4B8AF
    std::uint16_t freeList[0x1000];        // +0xE4B8B0
    std::uint16_t freeListCount;           // +0xE4C8B0
};

struct Slot732e0 {
    std::uint16_t word0;                    // +0x00
    std::uint16_t word1;                    // +0x02
    std::uint16_t word2;                    // +0x04
};

struct Ctx732e0 {
    char pad_0x0000[0x1C0];
    void* lock;                             // +0x1C0 (passed to sub_ebdbf10/20)
    char pad_0x1C8[0x1CFCEA0];              // +0x1C8 .. +0x1CFD0C7
    StreamFrame732e0* stream;               // +0x1CFD0C8
    char pad_0x1CFD0D0[0x1E2D1E8];          // +0x1CFD0D0 .. +0x1E4CAB3
    std::uint32_t hashCount;                // +0x1E4CAB4
    std::uint32_t aux[0x1000];              // +0x1E4CAB8
    std::uint16_t entries[0x1000];          // +0x1E50AB8
    Slot732e0 slots[0x1000];                // +0x1E52AB8 (stride 6)
};

static constexpr std::size_t kCtxLockOffset = 0x1C0;
static constexpr std::size_t kCtxStreamOffset = 0x1CFD0C8;
static constexpr std::size_t kCtxHashCountOffset = 0x1E4CAB4;
static constexpr std::size_t kCtxAuxOffset = 0x1E4CAB8;
static constexpr std::size_t kCtxEntriesOffset = 0x1E50AB8;
static constexpr std::size_t kCtxSlotsOffset = 0x1E52AB8;
static constexpr std::size_t kSlotStride = 6;
static constexpr std::size_t kStreamWritePosOffset = 0xE05820;
static constexpr std::size_t kStreamDataOffset = 0xE05828;
static constexpr std::size_t kStreamFreeListOffset = 0xE4B8B0;
static constexpr std::size_t kStreamFreeListCountOffset = 0xE4C8B0;
static constexpr std::uint16_t kHashEmpty = 0xFFFF;
static constexpr std::uint32_t kHashCapacity = 0x1000;
static constexpr std::uint32_t kHashMask = 0xFFF;
static constexpr std::uint32_t kHashMul1 = 0x5EBCA77u;
static constexpr std::uint32_t kHashShift = 0x13;
static constexpr std::uint32_t kHashMul2 = 0x9B1u;
static constexpr std::uint8_t kStreamTag = 0x21;

static_assert(offsetof(Ctx732e0, lock) == kCtxLockOffset, "Ctx+0x1C0 lock");
static_assert(offsetof(Ctx732e0, stream) == kCtxStreamOffset, "Ctx+0x1CFD0C8 stream");
static_assert(offsetof(Ctx732e0, hashCount) == kCtxHashCountOffset, "Ctx+0x1E4CAB4 hashCount");
static_assert(offsetof(Ctx732e0, aux) == kCtxAuxOffset, "Ctx+0x1E4CAB8 aux");
static_assert(offsetof(Ctx732e0, entries) == kCtxEntriesOffset, "Ctx+0x1E50AB8 entries");
static_assert(offsetof(Ctx732e0, slots) == kCtxSlotsOffset, "Ctx+0x1E52AB8 slots");
static_assert(sizeof(Slot732e0) == kSlotStride, "Slot stride 6");
static_assert(offsetof(StreamFrame732e0, writePos) == kStreamWritePosOffset, "StreamFrame+0xE05820 writePos");
static_assert(offsetof(StreamFrame732e0, data) == kStreamDataOffset, "StreamFrame+0xE05828 data");
static_assert(offsetof(StreamFrame732e0, freeList) == kStreamFreeListOffset, "StreamFrame+0xE4B8B0 freeList");
static_assert(offsetof(StreamFrame732e0, freeListCount) == kStreamFreeListCountOffset, "StreamFrame+0xE4C8B0 freeListCount");

extern "C" void sub_ebdbf10(void* lock);
extern "C" void sub_ebdbf20(void* lock);
extern "C" void sub_ebce390(void* dst, const void* src, std::uint32_t n);
extern "C" void sub_bc79790(Ctx79790* ctx, std::uint16_t idx);

extern "C" void sub_bc732e0(Ctx732e0* ctx, std::uint16_t idx);

} // namespace native