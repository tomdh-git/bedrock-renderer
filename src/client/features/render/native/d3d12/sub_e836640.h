#pragma once
#include <cstdint>

namespace native::d3d12 {
extern "C" void* sub_e836640(void* rcx, void* rdx, std::uint64_t r8, std::uint64_t r9);

// layout constants
static constexpr std::size_t kOff_0x40 = 0x40;
static constexpr std::size_t kOff_0x48 = 0x48;
static constexpr std::size_t kOff_0x50 = 0x50;
static constexpr std::size_t kOff_0x58 = 0x58;
static constexpr std::size_t kOff_0x60 = 0x60;
static constexpr std::size_t kOff_0x68 = 0x68;
static constexpr std::size_t kOff_0x70 = 0x70;
static constexpr std::size_t kOff_0x78 = 0x78;
static constexpr std::size_t kOff_0x80 = 0x80;
static constexpr std::size_t kOff_0x88 = 0x88;
static constexpr std::size_t kOff_0x90 = 0x90;
static constexpr std::size_t kOff_0x98 = 0x98;
static_assert(kOff_0x40 == 0x40, "off");
}