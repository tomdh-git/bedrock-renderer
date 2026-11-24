#pragma once
#include <cstddef>
#include <cstdint>

namespace native {
extern "C" void* sub_e806560(void* a0, void* a1, int a2, void* a3, void* a4);

struct E806560_A0 {
    void*  p0;   // +0x00
    int    i8;   // +0x08
    void*  p10;  // +0x10
};
static_assert(offsetof(E806560_A0, p0)  == 0x00, "p0");
static_assert(offsetof(E806560_A0, i8)  == 0x08, "i8");
static_assert(offsetof(E806560_A0, p10) == 0x10, "p10");
static_assert(sizeof(E806560_A0) == 0x18, "size");

// LIFT_FN registry entry declared in .cpp
} // namespace native
