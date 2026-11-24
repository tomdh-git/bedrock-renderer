#pragma once
#include <cstdint>

namespace native::bgfx {

extern "C" void sub_bcbf110(void* a0);
extern "C" void sub_e935700(void* p); // forward-declared lift callee

// Layout constants
constexpr std::size_t kOff_0x48 = 0x48;
constexpr std::size_t kOff_0x58 = 0x58;
constexpr std::size_t kOff_0x68 = 0x68;
constexpr std::size_t kOff_0x80 = 0x80;
constexpr std::size_t kOff_0x88 = 0x88;
constexpr std::size_t kOff_0x90 = 0x90;

} // namespace native::bgfx