#pragma once
#include <cstddef>
#include <cstdint>
#include <cassert>

namespace native::d3d12 {

// Layout constants for std::vector-like container used by 0xe835b50
constexpr std::size_t kVecData = 0x0;
constexpr std::size_t kVecSize = 0x8;
constexpr std::size_t kVecCap  = 0x10;

static_assert(kVecData == 0, "vec data offset");
static_assert(kVecSize == 8, "vec size offset");
static_assert(kVecCap == 16, "vec cap offset");

extern "C" void sub_e835b50(void* vec, std::size_t n);

} // namespace native::d3d12