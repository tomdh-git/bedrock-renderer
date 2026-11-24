#pragma once
#include <cstdint>

namespace native {
extern "C" void sub_e935700(void* p);

// LIFT 0xbcbf640 signature
extern "C" void sub_bcbf640(void* a0);
} // namespace native

static_assert(sizeof(void*) == 8, "x64");
