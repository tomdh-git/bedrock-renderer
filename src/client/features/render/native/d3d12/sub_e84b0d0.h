#pragma once
#include <cstdint>
#include <cstddef>

namespace native { namespace d3d12 {

constexpr std::size_t kE84b0d0StructSize = 0x30;
static_assert(kE84b0d0StructSize == 0x30, "layout");

extern "C" void sub_e84b0d0(void* a0);

} } // namespace native::d3d12