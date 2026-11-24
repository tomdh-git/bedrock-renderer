// LIFT 0xbcbe410 size 0x11 1.26.62.01 sub_bcbe410
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bcbe410.h"

#include <cstdint>
#include <intrin.h>

namespace native {
void sub_eec5ae0(void* p);
}

namespace native::bgfx {

void sub_bcbe410(void) {
    // 0xbcbe410..0xbcbe414
    // 0xbcbe410  sub rsp,0x28
    // 0xbcbe414..0xbcbe41b
    // 0xbcbe414  lea rcx,[0xF571225]
    static_assert(sizeof(void*) == 8, "x64 ABI");
    // 0xbcbe41b..0xbcbe420
    // 0xbcbe41b  call 0xEEC5AE0
    native::sub_eec5ae0(reinterpret_cast<void*>(0xF571225));
    // 0xbcbe420..0xbcbe421
    // 0xbcbe420  int3
    __debugbreak();
}

} // namespace native::bgfx

LIFT_FN(sub_bcbe410, "sub_bcbe410", 0xbcbe410, sub_bcbe410, nullptr);