#pragma once
#include <cstdint>
#include <cstddef>

namespace native {

// LIFT 0xe806410 size 0x127 1.26.62.01 sub_e806410

// layout constants

constexpr std::size_t kA0CountOff = 0x0;
constexpr std::size_t kA0BeginOff = 0x8;
constexpr std::size_t kA0EndOff = 0x10;
constexpr std::size_t kA1ValOff = 0x0;
constexpr std::size_t kA1Ptr10Off = 0x10;
constexpr std::size_t kA1Ptr18Off = 0x18;

static_assert(kA0BeginOff == 0x8, "a0 begin off");
static_assert(kA0EndOff == 0x10, "a0 end off");
static_assert(kA1Ptr10Off == 0x10, "a1 ptr10 off");
static_assert(kA1Ptr18Off == 0x18, "a1 ptr18 off");

extern "C" void sub_e806410(void* a0, void* a1);

} // namespace native