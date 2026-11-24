#pragma once
#include <cstddef>
#include <cstdint>

namespace native {
struct Vec12 { void* p; float f; }; // placeholder, 12 bytes
static_assert(sizeof(Vec12) == 12, "Vec12 size");

// Layout constants
constexpr std::size_t kOff0 = 0x0;
constexpr std::size_t kOff8 = 0x8;
constexpr std::size_t kOff10 = 0x10;

// Signature
extern "C" void sub_e854800(void* self, std::size_t n);

// Registry entry
#define LIFT_FN(name, rva) /* placeholder */
}