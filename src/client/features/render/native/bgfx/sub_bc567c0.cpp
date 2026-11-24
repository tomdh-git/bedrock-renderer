// LIFT 0xbc567c0 size 0x193 1.26.62.01 BgfxFrameBuilder slot 53
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc567c0.h"

#include <cstdint>
#include <cstddef>
static_assert(sizeof(void*) == 8, "x64");

namespace {
native::Boundary<void, void*, float, float, float, float, float, uint32_t, uint8_t> sub_ebcd820("sub_ebcd820");
}

namespace native::bgfx {

// 0xbc567c0..0xbc56952
void sub_bc567c0(FrameOutput* out, const void* qptr1, const void* qptr2,
    const float* a3, const float* b, const float* a, const float* m16,
    std::uint8_t flag, const void* q9ptr) {

    // 0xbc567c0..0xbc567ee: prologue
    // 0xbc567f2..0xbc568d9: zero/initialize out fields
    // 0xbc568e0..0xbc568f4: save stack args
    // 0xbc568f8..0xbc568fa: rdx = qptr1
    // 0xbc568fb  call 0xBC56190                                ; -> sub_bc56190
    native::sub_bc56190(out, qptr1, qptr2, a3, b, a, m16, qptr2, reinterpret_cast<const Q9*>(q9ptr));

    // 0xbc56901..0xbc5693e: prepare args
    // 0xbc5693e  call 0xEBCD820                                ; -> sub_ebcd820
    sub_ebcd820(out + 0x18, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, flag == 0 ? 1 : 0);

    // 0xbc56944..0xbc56952: epilogue
}

LIFT_FN(sub_bc567c0, "sub_bc567c0", 0xbc567c0, sub_bc567c0, nullptr);

} // namespace native::bgfx
