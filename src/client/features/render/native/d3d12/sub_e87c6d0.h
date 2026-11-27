#pragma once
#include <cstddef>
#include <cstdint>

namespace native {   // reopen ::native: forward declaration of the lift-set callee
void* sub_e935700(void* a0);   // 0xe935700 (docs/data/native_boundary.tsv line 505: `0xe935700 lift`; lifted at helpers/sub_e935700.cpp)
} // namespace native

namespace native { namespace d3d12 {

// Layout overlay of the argument object of 0xe87c6d0 (sub_e87c6d0, size 0x9d,
// 1.26.62.01). The object's real type name is unknown; every offset below is
// [V] from the disassembly of the function (0xe87c6d0..0xe87c76d):
//   +0x08  pointer field (read, then written 0 on exit)
//   +0x18  u64 field (written 0 on exit)
//   +0x20  u64 size field (read, then written 0xF on exit)
//   +0x32  u16 field (read: index argument of sub_bc75c30)
//   +0x34  u8  field (read: compared with 1)
struct alignas(8) ArgLayout {
    char pad_0x00[0x08];          // +0x00
    void* field08;                // +0x08  R/W pointer
    char pad_0x10[0x08];          // +0x10
    std::uint64_t field18;        // +0x18  W
    std::uint64_t field20;        // +0x20  R/W size
    char pad_0x28[0x0A];          // +0x28..0x31
    std::uint16_t field32;        // +0x32  R index
    std::uint8_t field34;         // +0x34  R flag
};

static_assert(offsetof(ArgLayout, field08) == 0x08, "ArgLayout+0x08 field08");
static_assert(offsetof(ArgLayout, field18) == 0x18, "ArgLayout+0x18 field18");
static_assert(offsetof(ArgLayout, field20) == 0x20, "ArgLayout+0x20 field20");
static_assert(offsetof(ArgLayout, field32) == 0x32, "ArgLayout+0x32 field32");
static_assert(offsetof(ArgLayout, field34) == 0x34, "ArgLayout+0x34 field34");
static_assert(sizeof(ArgLayout) == 0x38, "ArgLayout size");

// sub_e935700 (0xe935700, size 0x5): lift-set callee
// (docs/data/native_boundary.tsv line 505: `0xe935700 lift`; lifted source at
// src/client/features/render/native/helpers/sub_e935700.cpp). Called through its
// native symbol; forward-declared here per brief rule 66.
void* ::native::sub_e935700(void* a0);

// 0xe87c6d0, size 0x9d, 1.26.62.01. x64 Microsoft ABI: RCX = a0, returns void.
// Calls: native::sub_bc75c30 (lift set), native::sub_e935700 (lift set via
// docs/data/native_boundary.tsv line 505), and one indirect call through data
// slot 0xF9A8C78 (brief rule 69).
void sub_e87c6d0(void* a0);

} } // namespace native::d3d12
