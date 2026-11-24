#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

struct FrameOutput;  // defined in sub_bc56190.h
struct Q9;            // defined in sub_bc56190.h

} // namespace native

#include "client/features/render/native/bgfx/sub_bc56190.h"

namespace native {

// 0xbc56610, size 0x18e, returns void.
// x64 Microsoft ABI: rcx = out; stack args: b, a, m16, val1, val2, qptr1, flag, qptr2, q9.
extern "C" void sub_bc56610(FrameOutput* out, float* b, float* a, const float* m16,
    float val1, float val2, const void* qptr1, std::uint8_t flag, const void* qptr2,
    const Q9* q9);

} // namespace native

namespace native::bgfx {

void sub_bc56610(FrameOutput* out, float* b, float* a, const float* m16,
    float val1, float val2, const void* qptr1, std::uint8_t flag, const void* qptr2,
    const Q9* q9);

// Layout assertions for offsets used by 0xbc56610 [V]:
static_assert(sizeof(FrameOutput) == 0x118, "FrameOutput must be 0x118 bytes");

} // namespace native::bgfx