#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout constants for 0xbcc1910 (RenderStateDesc -> bgfx state bits).
// Offsets observed in the disassembly; no named struct is asserted here.

inline constexpr std::size_t kBcc1910OutSize = 0x58;

} // namespace native::bgfx

extern "C" void* sub_bcc1910(void* a0, void* a1);
