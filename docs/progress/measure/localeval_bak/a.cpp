// LIFT 0xc283ce0 size 0x6b 1.26.62.01 Frame renderer lambda
#include "client/features/render/native/dragon/sub_c283ce0.h"

#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

namespace native {

// Both `call qword ptr [0xF99FFA0]` sites go through loader-resolved data slot
// 0xF99FFA0, which holds sub_eea6040 (docs/data/native_boundary.tsv: class
// vendor, "thunk via data slot 0xF99FFA0 (loader-resolved)"). sub_eea6040 is a
// `jmp rax` tail forwarder, so the real call target is whatever this function
// preloaded into rax: vtable[0] (destructor) at 0xc283d2d, vtable[8]
// (deallocator) at 0xc283d43. rcx = refCount on entry in both cases. The
// lifted code reads the vtable entry itself and calls it with rcx = rc, which
// is the net effect of each `call qword ptr [0xF99FFA0]` (same precedent as
// GuardedPagedArray_ensure at 0xbc7a867/0xbc7a8b1).
//
// The preloaded rax values are reads the original also performs (both loads are
// dead once the target is resolved, but they model the vtable reads):
//   0xc283d24  mov rax,[rdi]      0xc283d27  mov rax,[rax]
//   0xc283d39  mov rax,[rdi]      0xc283d3c  mov rax,[rax+8]

void sub_c283ce0(RenderNode* node) {
    // 0xc283ce0..0xc283cec: push rsi; push rdi; sub rsp,0x28;
    //   cmp byte ptr [rcx+0x19],0 ; je short 0xC283CF3
    //   renderFlag != 0 -> return via the epilogue at 0xc283cec.
    if (node->renderFlag != 0) {
        return;   // 0xc283cec  add rsp,0x28 ; pop rdi ; pop rsi ; ret
    }

    // 0xc283cf3..0xc283d06: mov rsi,rcx ; jmp short 0xC283D06
    RenderNode* cur = node;

    for (;;) {
        // 0xc283d06..0xc283d12: mov rdi,rsi ; mov rcx,[rsi+0x10] ; call 0xC283CE0
        RenderNode* thisNode = cur;
        sub_c283ce0(thisNode->child);   // 0xc283d0d  call 0xC283CE0  (rcx = child)

        // 0xc283d12..0xc283d1c: mov rsi,[rsi] ; mov rdi,[rdi+0x30] ; test rdi,rdi ; je short 0xC283D00
        cur = thisNode->nextSibling;     // 0xc283d12  mov rsi,[rsi]
        RefCountBase* rc = thisNode->refCount;  // 0xc283d15  mov rdi,[rdi+0x30]
        if (rc == 0) {
            continue;                    // 0xc283d1c  je short 0xC283D00
        }

        // 0xc283d1e..0xc283d22: lock dec dword ptr [rdi+8] ; jne short 0xC283D00
        //   strong == 0 -> destroy (fall-through), strong != 0 -> skip the
        //   destroy call AND the weak-count dec (jne jumps to 0xc283d00).
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rc->strong)) == 0) {
            // 0xc283d24..0xc283d2d: mov rax,[rdi] ; mov rax,[rax] ; mov rcx,rdi
            //   then call qword ptr [0xF99FFA0] (sub_eea6040 -> jmp rax = vtable[0])
            using DestroyFn = void (*)(void*);
            DestroyFn destroy = reinterpret_cast<DestroyFn>(reinterpret_cast<void**>(rc->vtable)[0]);
            destroy(rc);   // 0xc283d2d  call qword ptr [0xF99FFA0]

            // 0xc283d33..0xc283d37: lock dec dword ptr [rdi+0xC] ; jne short 0xC283D00
            //   weak == 0 -> dealloc (fall-through), weak != 0 -> skip dealloc.
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rc->weak)) == 0) {
                // 0xc283d39..0xc283d43: mov rax,[rdi] ; mov rax,[rax+8] ; mov rcx,rdi
                //   then call qword ptr [0xF99FFA0] (sub_eea6040 -> jmp rax = vtable[8])
                using DeallocFn = void (*)(void*);
                DeallocFn dealloc = reinterpret_cast<DeallocFn>(reinterpret_cast<void**>(rc->vtable)[1]);
                dealloc(rc);   // 0xc283d43  call qword ptr [0xF99FFA0]
            }
        }

        // 0xc283d00..0xc283d04: cmp byte ptr [rsi+0x19],0 ; jne short 0xC283CEC
        if (cur->renderFlag != 0) {
            return;   // 0xc283d04  jne short 0xC283CEC -> epilogue ret
        }
        // fall through: 0xc283d06 processes cur again
    }
}

LIFT_FN(c283ce0, "sub_c283ce0", 0xC283CE0, sub_c283ce0, nullptr);

} // namespace native

// Verbatim instructions of the function (rdis dis 0xc283ce0 0x6b), for
// liftcheck/verify_oc. Every line matches rdis output for its address.
#if 0
0xC283CE0  push rsi
0xC283CE1  push rdi
0xC283CE2  sub rsp,0x28
0xC283CE6  cmp byte ptr [rcx+0x19],0
0xC283CEA  je short 0xC283CF3
0xC283CEC  add rsp,0x28
0xC283CF0  pop rdi
0xC283CF1  pop rsi
0xC283CF2  ret
0xC283CF3  mov rsi,rcx
0xC283CF6  jmp short 0xC283D06
0xC283CF8  nop [rax+rax]
0xC283D00  cmp byte ptr [rsi+0x19],0
0xC283D04  jne short 0xC283CEC
0xC283D06  mov rdi,rsi
0xC283D09  mov rcx,[rsi+0x10]
0xC283D0D  call 0xC283CE0
0xC283D12  mov rsi,[rsi]
0xC283D15  mov rdi,[rdi+0x30]
0xC283D19  test rdi,rdi
0xC283D1C  je short 0xC283D00
0xC283D1E  lock dec dword ptr [rdi+8]
0xC283D22  jne short 0xC283D00
0xC283D24  mov rax,[rdi]
0xC283D27  mov rax,[rax]
0xC283D2A  mov rcx,rdi
0xC283D2D  call qword ptr [0xF99FFA0]
0xC283D33  lock dec dword ptr [rdi+0xC]
0xC283D37  jne short 0xC283D00
0xC283D39  mov rax,[rdi]
0xC283D3C  mov rax,[rax+8]
0xC283D40  mov rcx,rdi
0xC283D43  call qword ptr [0xF99FFA0]
0xC283D49  jmp short 0xC283D00
#endif
