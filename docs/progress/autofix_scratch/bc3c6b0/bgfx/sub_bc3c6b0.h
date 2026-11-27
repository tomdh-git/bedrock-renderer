#pragma once

#include <cstddef>
#include <cstdint>
// Forward declarations (autofix)
struct sub_392960;
struct sub_bc3c6b0;


// sub_bc3c6b0: BgfxFrameBuilder slot 0 validate-and-clear (size 0xcb, 1.26.62.01).

// Reverse-engineered from the disassembly of [0xbc3c6b0, 0xbc3c77b) in

// Minecraft.Windows.exe 1.26.62.01. Every offset below is observed in that

// listing and is cited beside the statement that uses it in

// src/client/features/render/native/bgfx/sub_bc3c6b0.cpp. [V]

//

// The function's "a2" argument (entry r8) is a frame-builder slot block with

// the observed layout (all fields 8 bytes unless noted):

//

//   0x38 slot pointer (ptr)        R @0xbc3c715, R via [ptr-8] @0xbc3c726, W byte @0xbc3c756

//   0x48 u64                       W @0xbc3c746 (0)

//   0x50 u64 size                  R @0xbc3c70b, W @0xbc3c74e (0xF)

//   0x60 u64 ptr (slot begin)      R @0xbc3c6c3, R via [ptr-8] @0xbc3c6dc, W 16 bytes @0xbc3c700

//   0x70 u64 ptr (slot end)        R @0xbc3c6cc, W @0xbc3c703 (0)

//

// Bytes 0x68..0x70 are padding between field_0x60 and field_0x70; the movups

// at 0xbc3c700 zeroes field_0x60 together with those 8 padding bytes. [V]


namespace native::bgfx {

struct BgfxFrameBuilderSlot0 {
    char pad_0x00[0x38];     // 0x00

    void* field_0x38;        // 0x38 slot pointer

    char pad_0x40[0x8];      // 0x40

    uint64_t field_0x48;     // 0x48

    uint64_t field_0x50;     // 0x50 size

    char pad_0x58[0x8];      // 0x58

    void* field_0x60;        // 0x60 slot begin

    char pad_0x68[0x8];      // 0x68 (zeroed together with field_0x60)

    void* field_0x70;        // 0x70 slot end

};
static_assert(sizeof(BgfxFrameBuilderSlot0) == 0x78, "sub_bc3c6b0: slot block size is 0x78");
static_assert(offsetof(BgfxFrameBuilderSlot0, field_0x38) == 0x38, "sub_bc3c6b0: field_0x38 offset");
static_assert(offsetof(BgfxFrameBuilderSlot0, field_0x48) == 0x48, "sub_bc3c6b0: field_0x48 offset");
static_assert(offsetof(BgfxFrameBuilderSlot0, field_0x50) == 0x50, "sub_bc3c6b0: field_0x50 offset");
static_assert(offsetof(BgfxFrameBuilderSlot0, field_0x60) == 0x60, "sub_bc3c6b0: field_0x60 offset");
static_assert(offsetof(BgfxFrameBuilderSlot0, field_0x70) == 0x70, "sub_bc3c6b0: field_0x70 offset");

// Immediate constants used by sub_bc3c6b0, observed in the disassembly. [V]

static constexpr uint64_t kBc3c6b0ModeRequired = 0x1;        // cmp rcx,1            @0xbc3c6b6

static constexpr uint64_t kBc3c6b0SlotSizeLarge = 0x1000;    // cmp rdx,0x1000       @0xbc3c6d3 / @0xbc3c71d

static constexpr uint64_t kBc3c6b0GuardGap = 0x20;           // cmp rcx,0x20         @0xbc3c6e7 / @0xbc3c731

static constexpr uint64_t kBc3c6b0Size1Bias = 0x27;          // add rdx,0x27         @0xbc3c6ed

static constexpr uint64_t kBc3c6b0Size2Bias = 0x28;          // add rax,0x28         @0xbc3c737

static constexpr uint64_t kBc3c6b0Slot2Small = 0x10;         // cmp rax,0x10         @0xbc3c70f

static constexpr uint64_t kBc3c6b0ResetSize = 0xF;           // mov [rsi+0x50],0xF   @0xbc3c74e


// sub_e935700 (0xe935700): direct callee of sub_bc3c6b0,

// `call 0xE935700` @0xbc3c6f8 and @0xbc3c741. It is a thunk

// (`jmp sub_392960` @0xe935700) and appears in NEITHER

// docs/data/native_functions.tsv NOR docs/data/native_boundary.tsv ->

// UNRESOLVED CALL: this unit cannot close (see docs/progress/oc_U-EX1.bc3c6b0.md).

// Declared with its native symbol only; argument types mirror the registers

// the original passes (rcx, rdx, r8, r9); the return value is unused.

extern "C" void sub_e935700(unsigned __int64 a0, unsigned __int64 a1, void* a2, void* a3);

// void sub_bc3c6b0(unsigned __int64 mode /*rcx: only == 1 proceeds*/,

//                 unsigned __int64 /*rdx: never read*/,

//                 BgfxFrameBuilderSlot0* fb /*r8: slot block*/,

//                 void* a3 /*r9: forwarded to sub_e935700*/)

// Exact x64 Microsoft ABI signature of the original. Returns void: the

// original never writes rax deterministically on any path.

void sub_bc3c6b0(unsigned __int64 mode, unsigned __int64 /*unused*/,
                 BgfxFrameBuilderSlot0* fb, void* a3);

} // namespace native::bgfx

