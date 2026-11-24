#pragma once
#include <cstddef>
#include <cstdint>

namespace native::d3d12 {

// Layout constants read/written by sub_e839020 (base slot 58).
// All offsets are into the RendererContextD3D12-related pair objects (rsi/a0, r12/a1).
static constexpr size_t kSlotPtr      = 0x00;  // [rsi] / [rsi+8] container bounds (begin/end pointers)
static constexpr size_t kField38      = 0x38;  // pointer field, written 0 / copied from source
static constexpr size_t kField40      = 0x40;  // embedded object base (for pointer comparison)
static constexpr size_t kField78      = 0x78;  // pointer field, written 0 / copied from source
static constexpr size_t kField80      = 0x80;  // qword copied from source
static constexpr size_t kGrowBy      = 0x88;  // added to [rsi+8] at end of first path
static constexpr size_t kStride      = 0x48;  // element stride in the copy loop
static constexpr size_t kStride2     = 0x88;  // alternate element stride (offset +0x88)
static constexpr size_t kPtrSize     = 0x08;

// [UNVERIFIED: 0xe839020 exact per-field struct identity of rsi/r12 objects not resolved from static analysis alone]

// Exact x64 Microsoft ABI signature: (this=a0 context pair in rcx, a1 source pair in rdx).
extern "C" void sub_e839020(void* a0, void* a1);

} // namespace native::d3d12