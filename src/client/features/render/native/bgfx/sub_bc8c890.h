#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Forward declaration: 0x5669770 is classed `lift` (docs/data/native_functions.tsv, depth 0,
// listed in native_roots.txt) and is lifted by its own unit (pass-tasks).
// Disassembly [0x5669770, 0x5669ada): rcx = dest, rdx = src; copies 0x124 bytes
// [src, src+0x124) -> [dest, dest+0x124) (movss per float, movups at +0x80/+0x114,
// dword at +0x90), a leaf with no calls, and returns dest in rax.
// Called from sub_0xbc8c890 at 0xbc8c959 (`call 0x5669770`).
void* sub_5669770(void* dest, const void* src);

} // namespace native

namespace native::bgfx {

// Layout of the frame-graph builder object as observed in sub_0xbc8c890.
// The type has no public symbol name; VvFrameGraphBuilder is a local layout name.
// Only offsets read or written by sub_0xbc8c890 are declared; padding is unnamed.
// Verified against the disassembly of [0xbc8c890, 0xbc8ccc5).
struct VvFrameGraphBuilder {
    uint8_t mBlock00[0x10];   // +0x00  16 bytes copied src->dst; src+0x8 additionally zeroed
    uint8_t mBlock10[0x10];   // +0x10  16 bytes copied src->dst, then zeroed on src
    uint64_t mField20;        // +0x20  copied src->dst
    uint64_t mField28;        // +0x28  pointer; switch-dependent copy
    uint64_t mField30;        // +0x30  pointer to refcounted object; copy + lock inc [ptr+8]
    uint8_t mField38;         // +0x38  tag byte: dst pre-set 0xFF, then tag when tag <= 3
    uint8_t mPad39[0x7];      // +0x39
    uint8_t mBlock40[0x10];   // +0x40  16 bytes copied
    uint64_t mField50;        // +0x50  copied
    uint64_t mField58;        // +0x58  moved: read from src, zeroed on src, written to dst
    uint8_t mBlock60[0x124];  // +0x60  0x124 bytes copied by sub_5669770 (ends at 0x184)
    uint8_t mBlock184[0x10];  // +0x184 16 bytes copied (ends at 0x194)
    uint32_t mField194;       // +0x194 copied
    uint8_t mField198;        // +0x198 copied
    uint8_t mPad199[0x3];     // +0x199
    float mField19C;          // +0x19C
    float mField1A0;          // +0x1A0
    float mField1A4;          // +0x1A4
    float mField1A8;          // +0x1A8
    uint8_t mBlock1AC[0x10];  // +0x1AC copied (ends at 0x1BC)
    uint8_t mBlock1BC[0x10];  // +0x1BC copied (ends at 0x1CB)
    uint8_t mBlock1CB[0x10];  // +0x1CB copied (ends at 0x1DC; overlaps last byte of mBlock1BC)
    uint64_t mField1DC;       // +0x1DC copied
    float mField1E4;          // +0x1E4
    float mField1E8;          // +0x1E8
    uint64_t mField1EC;       // +0x1EC copied (ends at 0x1F4)
    float mField1F4;          // +0x1F4
    float mField1F8;          // +0x1F8
    uint16_t mField1FC;       // +0x1FC copied
    uint8_t mPad1FE[0x2];     // +0x1FE
    float mBlock200[38];      // +0x200 38 floats copied (ends at 0x298)
};
static_assert(offsetof(VvFrameGraphBuilder, mBlock00) == 0x00);
static_assert(offsetof(VvFrameGraphBuilder, mBlock10) == 0x10);
static_assert(offsetof(VvFrameGraphBuilder, mField20) == 0x20);
static_assert(offsetof(VvFrameGraphBuilder, mField28) == 0x28);
static_assert(offsetof(VvFrameGraphBuilder, mField30) == 0x30);
static_assert(offsetof(VvFrameGraphBuilder, mField38) == 0x38);
static_assert(offsetof(VvFrameGraphBuilder, mBlock40) == 0x40);
static_assert(offsetof(VvFrameGraphBuilder, mField50) == 0x50);
static_assert(offsetof(VvFrameGraphBuilder, mField58) == 0x58);
static_assert(offsetof(VvFrameGraphBuilder, mBlock60) == 0x60);
static_assert(offsetof(VvFrameGraphBuilder, mBlock184) == 0x184);
static_assert(offsetof(VvFrameGraphBuilder, mField194) == 0x194);
static_assert(offsetof(VvFrameGraphBuilder, mField198) == 0x198);
static_assert(offsetof(VvFrameGraphBuilder, mField19C) == 0x19C);
static_assert(offsetof(VvFrameGraphBuilder, mField1A0) == 0x1A0);
static_assert(offsetof(VvFrameGraphBuilder, mField1A4) == 0x1A4);
static_assert(offsetof(VvFrameGraphBuilder, mField1A8) == 0x1A8);
static_assert(offsetof(VvFrameGraphBuilder, mBlock1AC) == 0x1AC);
static_assert(offsetof(VvFrameGraphBuilder, mBlock1BC) == 0x1BC);
static_assert(offsetof(VvFrameGraphBuilder, mBlock1CB) == 0x1CB);
static_assert(offsetof(VvFrameGraphBuilder, mField1DC) == 0x1DC);
static_assert(offsetof(VvFrameGraphBuilder, mField1E4) == 0x1E4);
static_assert(offsetof(VvFrameGraphBuilder, mField1E8) == 0x1E8);
static_assert(offsetof(VvFrameGraphBuilder, mField1EC) == 0x1EC);
static_assert(offsetof(VvFrameGraphBuilder, mField1F4) == 0x1F4);
static_assert(offsetof(VvFrameGraphBuilder, mField1F8) == 0x1F8);
static_assert(offsetof(VvFrameGraphBuilder, mField1FC) == 0x1FC);
static_assert(offsetof(VvFrameGraphBuilder, mBlock200) == 0x200);
static_assert(sizeof(VvFrameGraphBuilder) >= 0x298);

// sub_bc8c890(dst = rcx, src = rdx) -> rax = dst
VvFrameGraphBuilder* sub_bc8c890(VvFrameGraphBuilder* dst, VvFrameGraphBuilder* src);

} // namespace native::bgfx
