#pragma once
#include <cstdint>

namespace native { namespace d3d12 {

struct E80b240Ctx {
    void*   p0;       // +0x0
    uint32_t count;   // +0x8
    uint16_t a;       // +0xC
    uint16_t b;       // +0xE
    uint8_t  flag;    // +0x10
};

static_assert(sizeof(E80b240Ctx) >= 0x14, "size");

void sub_e80b240(E80b240Ctx* a0, uint32_t edx, uint32_t r8d);

} } // namespace