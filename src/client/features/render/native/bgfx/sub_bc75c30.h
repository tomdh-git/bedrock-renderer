#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// Layout reconstructed from the disassembly of 0xbc75c30 (size 0x2a9,
// 0xbc75c30..0xbc75ed9, sub_bc75c30, 1.26.62.01; instruction offsets cited
// in sub_bc75c30.cpp). The structs are layout overlays only: no object of
// these types is instantiated here.
//
// a0 (rcx) is the render context:
//   +0x1C0        lock subobject: address taken by lea and passed to
//                 sub_ebdbf10/sub_ebdbf20, never loaded
//   +0x1CFD0C8    pointer P to the stream frame ([ctx+0x1CFD0C8])
//   +0x1E1C2A0    u32 hash-set entry count
//   +0x1E1C2A4    u32 aux[0x400] (hashed values)
//   +0x1E1D2A4    u16 entries[0x400] (hash-set keys, empty 0xFFFF)
//   +0x1E1DABE + idx*0x18   u16 slot reference count
//   +0x1E1DAA8 + idx*0x18   slot object: +0x00 pointer, +0x08 u32 flag,
//                 +0x16 u16 reference count (same field as the +0x1E1DABE bias)
// sizeof(Ctx) == 0x1E1DAA8, so the slot object array follows the context
// overlay immediately (stride 0x18).
//
// P (ctx->stream) is the stream/pre-command frame:
//   +0xE05820  u32 writePos
//   +0xE05828  u8  data[] (byte stream)
//   +0xE509DC  u16 freeList[0x200]
//   +0xE50DDC  u16 freeListCount

struct StreamFrame {
    char pad_0x0000[0xE05820];
    std::uint32_t writePos;             // +0xE05820
    char pad_0xE05824[4];               // +0xE05824 (between writePos and data)
    std::uint8_t data[0x4B1B4];         // +0xE05828
    std::uint16_t freeList[0x200];      // +0xE509DC
    std::uint16_t freeListCount;        // +0xE50DDC
};

struct Ctx {
    char pad_0x0000[0x1C0];
    std::uint32_t lockField;            // +0x1C0
    char pad_0x1C4[0x1CFD0C8 - 0x1C4];
    StreamFrame* stream;                // +0x1CFD0C8
    char pad_0x1CFD0D0[0x1E1C2A0 - 0x1CFD0D0];
    std::uint32_t entryCount;           // +0x1E1C2A0
    std::uint32_t aux[0x400];           // +0x1E1C2A4
    std::uint16_t entries[0x400];       // +0x1E1D2A4
};

struct SlotObject {
    void* ptr;                          // +0x00
    std::uint32_t flag;                 // +0x08
    char pad_0x000C[0x0A];              // +0x0C
    std::uint16_t refCount;             // +0x16
};

static constexpr std::size_t kCtxLockFieldOffset = 0x1C0;
static constexpr std::size_t kCtxStreamOffset = 0x1CFD0C8;
static constexpr std::size_t kCtxEntryCountOffset = 0x1E1C2A0;
static constexpr std::size_t kCtxAuxOffset = 0x1E1C2A4;
static constexpr std::size_t kCtxEntriesOffset = 0x1E1D2A4;
static constexpr std::size_t kSlotObjectBase = 0x1E1DAA8;
static constexpr std::size_t kSlotObjectStride = 0x18;
static constexpr std::size_t kSlotPtrOffset = 0x00;
static constexpr std::size_t kSlotFlagOffset = 0x08;
static constexpr std::size_t kSlotRefCountOffset = 0x16;
static constexpr std::size_t kStreamWritePosOffset = 0xE05820;
static constexpr std::size_t kStreamDataOffset = 0xE05828;
static constexpr std::size_t kStreamFreeListOffset = 0xE509DC;
static constexpr std::size_t kStreamFreeListCountOffset = 0xE50DDC;
static constexpr std::size_t kHashCapacity = 0x400;
static constexpr std::uint16_t kHashEmpty = 0xFFFF;
static constexpr std::uint32_t kHashMul1 = 0x5EBCA77u;
static constexpr std::uint32_t kHashShift = 0x13;
static constexpr std::uint32_t kHashMul2 = 0x1B1u;
static constexpr std::uint32_t kHashMask = 0x3FFu;
static constexpr std::uint8_t kStreamTag = 0x25;

static_assert(offsetof(Ctx, lockField) == kCtxLockFieldOffset, "Ctx+0x1C0 lockField");
static_assert(offsetof(Ctx, stream) == kCtxStreamOffset, "Ctx+0x1CFD0C8 stream");
static_assert(offsetof(Ctx, entryCount) == kCtxEntryCountOffset, "Ctx+0x1E1C2A0 entryCount");
static_assert(offsetof(Ctx, aux) == kCtxAuxOffset, "Ctx+0x1E1C2A4 aux");
static_assert(offsetof(Ctx, entries) == kCtxEntriesOffset, "Ctx+0x1E1D2A4 entries");
static_assert(offsetof(StreamFrame, writePos) == kStreamWritePosOffset, "StreamFrame+0xE05820 writePos");
static_assert(offsetof(StreamFrame, data) == kStreamDataOffset, "StreamFrame+0xE05828 data");
static_assert(offsetof(StreamFrame, freeList) == kStreamFreeListOffset, "StreamFrame+0xE509DC freeList");
static_assert(offsetof(StreamFrame, freeListCount) == kStreamFreeListCountOffset, "StreamFrame+0xE50DDC freeListCount");
static_assert(offsetof(SlotObject, ptr) == kSlotPtrOffset, "SlotObject+0x00 ptr");
static_assert(offsetof(SlotObject, flag) == kSlotFlagOffset, "SlotObject+0x08 flag");
static_assert(offsetof(SlotObject, refCount) == kSlotRefCountOffset, "SlotObject+0x16 refCount");
static_assert(sizeof(Ctx) == kSlotObjectBase, "Ctx size == slot object array base");
static_assert(sizeof(SlotObject) == kSlotObjectStride, "SlotObject stride 0x18");

// Calls out of 0xbc75c30, with the contract evidenced by the call sites in
// sub_bc75c30.cpp. The first three are classified `lift` in
// docs/data/native_boundary.tsv (depth-7 roots, D0, already in the lift set)
// and are forward-declared here per docs/OPENCODE_BRIEF.md rule 66; they are
// called directly like any other native function and will be lifted by their
// own units:
//   0xbc75c5c  call 0xEBDBF10    sub_ebdbf10(lock)              lock = ctx + 0x1C0
//   0xbc75ec6  call 0xEBDBF20    sub_ebdbf20(lock)              on every path
//   0xbc75e86/0xbc75eb2  call 0xEBCE390  sub_ebce390(dst, src, n)  memcpy-like copy
// sub_eea6040 is a vendor boundary thunk (native_boundary.tsv: "thunk via data
// slot 0xF99FFA0 (loader-resolved)"). The original does not call it by symbol:
// 0xbc75cbe  mov r10,[0xF99FFA0] / 0xbc75cdc  call r10 (rule 69: read the
// pointer from the slot at call time and call it as a function pointer).
// Called as (g, slot->ptr, 0, 0, 0, 0) with g = *(void**)0x12ADF800; return
// value unused. Declared here to document the native symbol; the callsite
// reads data slot 0xF99FFA0 at call time.
extern "C" void sub_ebdbf10(void* lock);
extern "C" void sub_ebce390(void* dst, const void* src, std::uint32_t n);
extern "C" void sub_ebdbf20(void* lock);
extern "C" void sub_eea6040(void* a1, void* a2, std::uint32_t a3,
                            std::uint32_t a4, std::uint64_t a5,
                            std::uint64_t a6);

using Eea6040Fn = void (*)(void*, void*, std::uint32_t, std::uint32_t,
                            std::uint64_t, std::uint64_t);

// Lifted function: 0xbc75c30, size 0x2a9, returns void.
// x64 Microsoft ABI: rcx = ctx (Ctx*), edx = idx (std::uint16_t, zero extended);
// r8/r9 are never read by the original.
extern "C" void sub_bc75c30(Ctx* ctx, std::uint16_t idx);

} // namespace native
