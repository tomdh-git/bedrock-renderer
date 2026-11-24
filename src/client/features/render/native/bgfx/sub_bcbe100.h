#pragma once
#include <cstddef>
#include <cstdint>

static_assert(sizeof(void*) == 8, "x64 ABI");

namespace native::bgfx {
void sub_bcbe100(uint32_t* out, const void* a1);
} // namespace native::bgfx