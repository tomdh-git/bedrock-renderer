#pragma once
#include <cstdint>

namespace native {

// LIFT 0xe8041a0 size 0x21c 1.26.62.01 sub_e8041a0
struct SubE8041A0Args {
    void* a0; // rcx
};

// layout constants
static_assert(sizeof(void*) == 8, "ptr size");

extern "C" void sub_e8041a0(void* rcx);

} // namespace native