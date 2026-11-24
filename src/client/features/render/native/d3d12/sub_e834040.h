#pragma once
#include <cstdint>

namespace native::d3d12 {
void sub_e834040(void* a0, void* a1, std::uint16_t idx, std::uint32_t value);
static_assert(sizeof(void*) == 8, "x64");
} // namespace native::d3d12