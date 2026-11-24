#pragma once
#include <cstdint>

namespace native::d3d12 {

// sub_e876380: BgfxFrameBuilder slot 16 (0xe876380, size 0x92)
// Signature: void sub_e876380(void* a0)  // rcx=a0
void sub_e876380(void* a0);

// layout constants
constexpr std::uintptr_t kOff_08 = 0x8;
constexpr std::uintptr_t kOff_18 = 0x18;
constexpr std::uintptr_t kOff_20 = 0x20;

// Lift-set callee (classified `lift` in docs/data/native_boundary.tsv line 505):
// forward-declared with its exact ABI signature; called like any lifted function.
extern "C" void sub_e935700(void* a1);

static_assert(true);

} // namespace native::d3d12