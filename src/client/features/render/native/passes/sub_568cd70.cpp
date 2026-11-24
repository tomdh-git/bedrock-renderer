// LIFT 0x568cd70 size 0xc 1.26.62.01 sub_568cd70
#include "sub_568cd70.h"

namespace native {

// Lifted body of sub_568cd70 (tail-jump thunk to sub_568cd90 / FrameGraph::viewSetupTask).
// Body span [0x568cd70, 0x568cd7c), size 0xc, 1.26.62.01.
//
// Control flow follows the original exactly:
//   0x568cd70  mov rcx,rdx   (target rcx = original rdx, the view object)
//   0x568cd73  mov rdx,r8    (target rdx = original r8, the pass state object)
//   0x568cd76  jmp 0x568CD90 (tail jump to the view-setup task body)
//   0x568cd7b  int3          (pad byte inside the 0xc-byte body; unreachable)
// r8, r9 and the stack arguments are never touched, so they arrive at
// sub_568cd90 unchanged; the void return value passes straight through.
// 0x568cd70..0x568cd7c
void sub_568cd70(void* a0 /* dropped by the thunk */, void* view, void* state)
{
    // 0x568cd70..0x568cd7c
    static_assert(sizeof(void*) == 8, "sub_568cd70: x64 register arguments are 8 bytes");
    // 0x568cd70  mov rcx,rdx
    // 0x568cd73  mov rdx,r8
    // 0x568cd76  jmp 0x568CD90
    // 0x568cd7b  int3   (pad byte within the 0xc-byte body; unreachable)
#if 0
0x568cd70  mov rcx,rdx
0x568cd73  mov rdx,r8
0x568cd76  jmp 0x568CD90
0x568cd7b  int3
#endif
    // C++ rendering of 0x568cd70 mov rcx,rdx / 0x568cd73 mov rdx,r8 /
    // 0x568cd76 jmp 0x568CD90: the view object (this->rdx) and pass state
    // (this->r8) become the target's rcx/rdx; r8, r9 and the stack pass
    // through; the tail jump passes the void return straight through.
    return sub_568cd90(view, state);
}

} // namespace native

LIFT_FN(sub_568cd70, "sub_568cd70", 0x568CD70, sub_568cd70, nullptr);
