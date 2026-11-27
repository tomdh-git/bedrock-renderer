// LIFT 0x6685f60 size 0x25 1.26.62.01 BgfxFrameBuilder slot 61
#include "sub_6685f60.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

#if 0
// Verbatim instructions of sub_6685f60 ([0x6685f60, 0x6685f85), size 0x25):
0x6685f60  sub rsp,0x28
0x6685f64  test r8,r8
0x6685f67  je short 0x6685F7F
0x6685f69  test rdx,rdx
0x6685f6c  je short 0x6685F7F
0x6685f6e  mov rax,[rcx+0x28]
0x6685f72  mov rcx,[rax+0x18]
0x6685f76  add rsp,0x28
0x6685f7a  jmp 0xC288650
0x6685f7f  call 0x78ED0
0x6685f84  int3
#endif

namespace native {
namespace boundary {
    // 0x78ED0, class=crt [docs/data/native_boundary.tsv line 11]. At the call site (0x6685f7f) the registers are
    // rcx=a0, rdx=a1, r8=a2: the two loads above are skipped on the null-argument path. Its result is never used
    // because int3 follows at 0x6685f84. Signature confirmed only for the registers we pass; return type void.
    // [V: rdis dis 0x6685f60 0x25; native_boundary.tsv line 11]
    Boundary<void, void*, void*, void*> sub_78ed0("sub_78ed0");
} // namespace boundary
} // namespace native

std::uintptr_t sub_6685f60(void* a0, void* a1, void* a2)
{
    // 0x6685f60..0x6685f64: sub rsp,0x28   (prologue stack space; balanced by add rsp,0x28 at 0x6685f76)
    // 0x6685f64..0x6685f67: test r8,r8        // 0x6685f64  test r8,r8
    // 0x6685f67..0x6685f69: je short 0x6685F7F   // 0x6685f67  je short 0x6685F7F
    // 0x6685f69..0x6685f6c: test rdx,rdx     // 0x6685f69  test rdx,rdx
    // 0x6685f6c..0x6685f6e: je short 0x6685F7F   // 0x6685f6c  je short 0x6685F7F
    if (a2 == nullptr || a1 == nullptr) {
        // 0x6685f7f..0x6685f84: call 0x78ED0   // 0x6685f7f  call 0x78ED0
        native::boundary::sub_78ed0(a0, a1, a2);
        // 0x6685f84..0x6685f85: int3   // 0x6685f84  int3
        __debugbreak();
        __assume(false);
    }
    // 0x6685f6e..0x6685f72: mov rax,[rcx+0x28]   // 0x6685f6e  mov rax,[rcx+0x28]
    void* link = *reinterpret_cast<void***>(reinterpret_cast<std::uint8_t*>(a0) + native::sub_6685f60Layout::kObjLinkOff);
    // 0x6685f72..0x6685f76: mov rcx,[rax+0x18]   // 0x6685f72  mov rcx,[rax+0x18]
    void* tailThis = *reinterpret_cast<void***>(reinterpret_cast<std::uint8_t*>(link) + native::sub_6685f60Layout::kTailThisOff);
    // 0x6685f76..0x6685f7a: add rsp,0x28   (stack balanced before the tail jump)
    // 0x6685f7a..0x6685f7f: jmp 0xC288650   (tail call; callee 0xC288650 is outside the lift set and
    //   native_boundary.tsv: not resolved by this unit, see docs/progress/oc_U-EX4.6685f60.md)
    //   0x6685f7a  jmp 0xC288650
    return sub_c288650(tailThis, a1, a2);   // 0x6685f7a  jmp 0xC288650
}

LIFT_FN(sub_6685f60, "BgfxFrameBuilder slot 61", 0x6685f60, sub_6685f60, nullptr);
