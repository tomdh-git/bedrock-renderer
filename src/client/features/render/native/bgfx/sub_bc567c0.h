#pragma once
#include <cstddef>
#include <cstdint>
#include "client/features/render/native/bgfx/sub_bc56190.h"

namespace native { namespace bgfx {
// 0xbc567c0, size 0x193, returns FrameOutput*? actually void? ret rax=out
extern "C" void sub_bc567c0(FrameOutput* out, const void* qptr1, const void* qptr2,
    const float* a3, const float* b, const float* a, const float* m16,
    std::uint8_t flag, const void* q9ptr);
static_assert(sizeof(FrameOutput) == 0x118, "x");
} }
