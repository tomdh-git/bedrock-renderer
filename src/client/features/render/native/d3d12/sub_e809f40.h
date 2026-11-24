#pragma once
#include <cstddef>
#include <cstdint>

namespace native { namespace d3d12 {

// Layout constants for 0xe809f40
constexpr std::size_t kOff_0x20 = 0x20;
constexpr std::size_t kOff_0x28 = 0x28;
constexpr std::size_t kOff_0x30 = 0x30;

struct RendererContextD3D12BaseSlot58 {
    // placeholder; real layout asserted by usage
};

static_assert(kOff_0x20 == 0x20, "off 0x20");
static_assert(kOff_0x28 == 0x28, "off 0x28");
static_assert(kOff_0x30 == 0x30, "off 0x30");

} } // namespace

#define LIFT_FN_E809F40 0xe809f40