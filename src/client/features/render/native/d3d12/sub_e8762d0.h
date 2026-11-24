#pragma once
#include <cstdint>
#include <cstddef>

namespace native { namespace d3d12 {

// Layout constants (offsets used by 0xe8762d0)
constexpr std::size_t kOff_0x00 = 0x00;
constexpr std::size_t kOff_0x10 = 0x10;
constexpr std::size_t kOff_0x20 = 0x20;

static_assert(kOff_0x00 == 0x00, "off 0x00");
static_assert(kOff_0x10 == 0x10, "off 0x10");
static_assert(kOff_0x20 == 0x20, "off 0x20");

void* sub_e8762d0(void* a0);

} } // namespace native::d3d12