#pragma once
#include <cstdint>

namespace native::d3d12 {
// Layout constants
constexpr std::size_t kStrSize = 0;
static_assert(sizeof(void*) == 8, "x64");
void* sub_e834520(void* a0, std::uint32_t a1);
extern "C" void sub_75720();
extern "C" void sub_9bc830(void*);
extern "C" void* sub_eec6ec0(void*, const void*, std::size_t);
} // namespace native::d3d12