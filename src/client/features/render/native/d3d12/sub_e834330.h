#pragma once
#include <cstddef>
#include <cstdint>

namespace native {
// Layout constants for sub_e834330 (0xe834330, size 0x1ee).
// std::vector-like growth (this+0x00 data, +0x08 capacity?, +0x10 size, +0x18 capacity)
static constexpr std::size_t kVecData = 0x00;
static constexpr std::size_t kVecSize = 0x10;
static constexpr std::size_t kVecCap  = 0x18;
static_assert(kVecSize == 0x10, "e834330");
static_assert(kVecCap == 0x18, "e834330");

// Forward declarations for lift callees.
extern "C" void sub_9bc830(std::size_t n); // alloc/free boundary (0x9bc830)
extern "C" void sub_e935700(void* p);      // free (0xe935700, lift)
extern "C" void* sub_eec6ec0(void* dst, const void* src, std::size_t n); // copy (0xeec6ec0, lift)
} // namespace native