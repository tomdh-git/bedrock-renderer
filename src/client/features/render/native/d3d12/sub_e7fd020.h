#pragma once
#include <cstdint>

namespace native::d3d12 {

// sub_e7fd020: D3D12 draw executor wrapper (0xe7fd020, size 0x2ea)
// Signature: void sub_e7fd020(void* a0, void* a1)  // rcx=a0, rdx=a1
void sub_e7fd020(void* a0, void* a1);

// layout constants
constexpr std::uintptr_t kOff_C0D0 = 0xC0D0;
constexpr std::uintptr_t kOff_D0D4 = 0xD0D4;
constexpr std::uintptr_t kOff_D0D8 = 0xD0D8;
constexpr std::uintptr_t kOff_8000 = 0x8000;

static_assert(true);

} // namespace native::d3d12