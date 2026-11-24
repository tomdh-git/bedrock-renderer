#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// Layout reconstructed from the disassembly of 0xbc79790 (size 0x2ce,
// 0xbc79790..0xbc79a5e, sub_bc79790, 1.26.62.01).
struct StreamFrame79790 {
    char pad_0x0000[0xE05820];
    std::uint32_t writePos;                 // +0xE05820
    std::uint8_t data[0xE498AE - 0xE05828]; // +0xE05828 .. +0xE498AD
    std::uint16_t freeList[0x1000];        // +0xE498AE
    std::uint16_t freeListCount;           // +0xE4B8AE
};

struct SlotObject79790 {
    void* ptr;                              // +0x00
    char pad_0x0008[0x1C];                  // +0x08 .. +0x1B
    std::uint16_t refCount;                 // +0x1C
    std::uint16_t count;                    // +0x1E
};

struct Ctx79790 {
    char pad_0x0000[0x1CFD0C8];
    StreamFrame79790* stream;                // +0x1CFD0C8
    char pad_0x1CFD0D0[0x1E20AAC - 0x1CFD0D0];
    std::uint32_t hashCount;                // +0x1E20AAC
    std::uint32_t aux[0x2000];              // +0x1E20AB0
    std::uint16_t entries[0x2000];          // +0x1E28AB0
    // slots at +0x1E2CAB0, stride 0x20
};

static constexpr std::size_t kCtxStreamOffset = 0x1CFD0C8;
static constexpr std::size_t kCtxHashCountOffset = 0x1E20AAC;
static constexpr std::size_t kCtxAuxOffset = 0x1E20AB0;
static constexpr std::size_t kCtxEntriesOffset = 0x1E28AB0;
static constexpr std::size_t kSlotBase = 0x1E2CAB0;
static constexpr std::size_t kSlotStride = 0x20;
static constexpr std::size_t kSlotRefCountOffset = 0x1C;
static constexpr std::size_t kSlotCountOffset = 0x1E;
static constexpr std::size_t kStreamWritePosOffset = 0xE05820;
static constexpr std::size_t kStreamDataOffset = 0xE05828;
static constexpr std::size_t kStreamFreeListOffset = 0xE498AE;
static constexpr std::size_t kStreamFreeListCountOffset = 0xE4B8AE;
static constexpr std::uint16_t kHashEmpty = 0xFFFF;
static constexpr std::uint32_t kHashCapacity = 0x2000;
static constexpr std::uint32_t kHashMask = 0x1FFF;
static constexpr std::uint32_t kHashMul1 = 0x85EBCA77u;
static constexpr std::uint32_t kHashShift = 0x13;
static constexpr std::uint32_t kHashMul2 = 0x19B1u;
static constexpr std::uint8_t kStreamTag = 0x20;

static_assert(offsetof(Ctx79790, stream) == kCtxStreamOffset, "Ctx+0x1CFD0C8 stream");
static_assert(offsetof(Ctx79790, hashCount) == kCtxHashCountOffset, "Ctx+0x1E20AAC hashCount");
static_assert(offsetof(Ctx79790, aux) == kCtxAuxOffset, "Ctx+0x1E20AB0 aux");
static_assert(offsetof(Ctx79790, entries) == kCtxEntriesOffset, "Ctx+0x1E28AB0 entries");
static_assert(offsetof(StreamFrame79790, writePos) == kStreamWritePosOffset, "StreamFrame+0xE05820 writePos");
static_assert(offsetof(StreamFrame79790, data) == kStreamDataOffset, "StreamFrame+0xE05828 data");
static_assert(offsetof(StreamFrame79790, freeList) == kStreamFreeListOffset, "StreamFrame+0xE498AE freeList");
static_assert(offsetof(StreamFrame79790, freeListCount) == kStreamFreeListCountOffset, "StreamFrame+0xE4B8AE freeListCount");
static_assert(offsetof(SlotObject79790, refCount) == kSlotRefCountOffset, "Slot+0x1C refCount");
static_assert(offsetof(SlotObject79790, count) == kSlotCountOffset, "Slot+0x1E count");
static_assert(sizeof(SlotObject79790) == kSlotStride, "Slot stride 0x20");

extern "C" void sub_ebdbf10(void* lock);
extern "C" void sub_ebce390(void* dst, const void* src, std::uint32_t n);
extern "C" void sub_ebdbf20(void* lock);
extern "C" void sub_e951550(void* cookie);

using Eea6040Fn79790 = void (*)(void*, void*, std::uint32_t, std::uint32_t,
                                 std::uint64_t, std::uint64_t);

extern "C" void sub_bc79790(Ctx79790* ctx, std::uint16_t idx);

} // namespace native