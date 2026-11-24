#pragma once
#include <cstdint>
#include <cstddef>

namespace native::d3d12 {

// sub_e83ace0: D3D12 draw executor wrapper (0xe83ace0, size 0x1e8)
// Signature: std::size_t sub_e83ace0(void* a0, std::size_t a1)  // rcx=a0, rdx=a1
std::size_t sub_e83ace0(void* a0, std::size_t a1);

// layout constants
constexpr std::uintptr_t kOff_12ADF800 = 0x12ADF800ULL;
constexpr std::uintptr_t kOff_F99FFA0 = 0xF99FFA0ULL;
constexpr std::uintptr_t kOff_B8000 = 0xB8000;
constexpr std::uintptr_t kOff_B8010 = 0xB8010;

static_assert(sizeof(void*) == 8);
static_assert(kOff_B8000 == 0xB8000);
static_assert(kOff_B8010 == 0xB8010);

} // namespace native::d3d12