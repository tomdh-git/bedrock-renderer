// LIFT 0x118420 size 0x53 1.26.62.01 sub_118420
#include "sub_118420.h"

namespace native {

// sub_118420 (0x118420, size 0x53, 1.26.62.01).
// Recursive walk over a node list headed at a3 (R8):
//   - entry: if *(u8*)(a3 + 0x19) != 0, return immediately (0x118429/0x11842e)
//   - for each node: recurse into *child (+0x10), then release the node with
//     native::sub_e935700(node), then advance to *next (+0x00); stop when
//     *(u8*)(next + 0x19) != 0 (0x11845f).
// No memory is written by this function itself; sub_e935700 (lift set, declared
// in sub_e935700.h) performs the release. rax is never written in
// [0x118420, 0x118473), so the function returns void [V].
//
// Verbatim instructions of [0x118420, 0x118473) (rdis dis 0x118420 0x53):
#if 0
0x118420  push r14
0x118422  push rsi
0x118423  push rdi
0x118424  push rbx
0x118425  sub rsp,0x28
0x118429  cmp byte ptr [r8+0x19],0                      ; R a3+0x19 (entry flag)
0x11842e  jne short 0x118469                            ; -> epilogue
0x118430  mov rbx,r8
0x118433  mov rsi,rdx
0x118436  mov rdi,rcx
0x118439  nop [rax]
0x118440  mov r8,[rbx+0x10]                             ; R node+0x10 (child)
0x118444  mov rcx,rdi
0x118447  mov rdx,rsi
0x11844a  call 0x118420                                 ; -> sub_118420 (recursion)
0x11844f  mov r14,[rbx]                                 ; R node+0x00 (next)
0x118452  mov edx,0x30
0x118457  mov rcx,rbx
0x11845a  call 0xE935700                                ; -> sub_e935700 (lift set)
0x11845f  cmp byte ptr [r14+0x19],0                     ; R next+0x19
0x118464  mov rbx,r14
0x118467  je short 0x118440                             ; -> loop head
0x118469  add rsp,0x28
0x11846d  pop rbx
0x11846e  pop rdi
0x11846f  pop rsi
0x118470  pop r14
0x118472  ret
#endif

void sub_118420(void* a1, void* a2, void* a3, void* a4) {
    // 0x118420..0x11842e: prologue, then entry flag check on a3+0x19
    if (*(std::uint8_t*)(reinterpret_cast<char*>(a3) + 0x19) != 0) return;
    //     0x118429  cmp byte ptr [r8+0x19],0
    //     0x11842e  jne short 0x118469   (-> epilogue, 0x118469)

    void* node = a3;              // 0x118430  mov rbx,r8
    void* saved_a1 = a1;          // 0x118436  mov rdi,rcx   (arg 1 preserved across recursion)
    void* saved_a2 = a2;          // 0x118433  mov rsi,rdx   (arg 2 preserved across recursion)
                                 // 0x118439  nop [rax]

    for (;;) {                    // 0x118440  loc_118440: loop head (jump target of 0x118467)
        void* child = *(void**)(reinterpret_cast<char*>(node) + 0x10);
                                    // 0x118440  mov r8,[rbx+0x10]   (arg 3 of recursive call)
        // 0x118444  mov rcx,rdi   (arg 1 = saved_a1)
        // 0x118447  mov rdx,rsi   (arg 2 = saved_a2)
        sub_118420(saved_a1, saved_a2, child, a4);
                                    // 0x11844a  call 0x118420   (recursion; arg 4 = a4, unmodified)
        void* next = *(void**)node;
                                    // 0x11844f  mov r14,[rbx]     (next node via +0x00)
        // 0x118452  mov edx,0x30    (dead store: sub_e935700->sub_392960 copies rcx into rdx)
        // 0x118457  mov rcx,rbx     (arg 1 = node)
        native::sub_e935700(node);
                                    // 0x11845a  call 0xE935700    (lift set; native::sub_e935700(void*))
        // 0x11845f  cmp byte ptr [r14+0x19],0
        if (*(std::uint8_t*)(reinterpret_cast<char*>(next) + 0x19) != 0) return;
        //     nonzero -> epilogue (0x118469); 0x118464 mov rbx,r14 is dead on that path
        node = next;              // 0x118464  mov rbx,r14 ; 0x118467  je short 0x118440 (-> loop head)
    }
                                 // 0x118469  add rsp,0x28
                                 // 0x11846d..0x118470  pop rbx,rdi,rsi,r14
                                 // 0x118472  ret
}

} // namespace native

LIFT_FN(118420, "sub_118420", 0x118420, ::native::sub_118420, nullptr);
