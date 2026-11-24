#pragma once
#include <cstddef>
#include <cstdint>

namespace native {
// LIFT 0xe835f00
constexpr std::size_t kE835F00Off_C000 = 0xC000;
constexpr std::size_t kE835F00Off_C010 = 0xC010;
static_assert(kE835F00Off_C000 == 0xC000);
static_assert(kE835F00Off_C010 == 0xC010);

extern "C" std::size_t sub_e835f00(void* a0, std::size_t a1);
} // namespace native