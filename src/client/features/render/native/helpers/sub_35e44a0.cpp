// LIFT 0x35e44a0 size 0x39 1.26.62.01 sub_35e44a0
#include "sub_35e44a0.h"

namespace native {

// sub_35e44a0 (0x35e44a0, size 0x39, 1.26.62.01).
//
// 0x35e44a0  push rsi
// 0x35e44a1  push rdi
// 0x35e44a2  sub rsp,0x28
// 0x35e44a6  cmp byte ptr [rcx+0x19],0
// 0x35e44aa  jne short 0x35E44D2
// 0x35e44ac  mov rsi,rcx
// 0x35e44af  nop
// 0x35e44b0  mov rcx,[rsi+0x10]
// 0x35e44b4  call 0x35E44A0
// 0x35e44b9  mov rdi,[rsi]
// 0x35e44bc  mov edx,0x40
// 0x35e44c1  mov rcx,rsi
// 0x35e44c4  call 0xE935700
// 0x35e44c9  cmp byte ptr [rdi+0x19],0
// 0x35e44cd  mov rsi,rdi
// 0x35e44d0  je short 0x35E44B0
// 0x35e44d2  add rsp,0x28
// 0x35e44d6  pop rdi
// 0x35e44d7  pop rsi
// 0x35e44d8  ret

void sub_35e44a0(sub_35e44a0_node* a0) {
    // 0x35e44a0..0x35e44ab: entry guard (push rsi; push rdi; sub rsp,0x28; cmp [rcx+0x19],0; jne -> epilogue)
    if (a0->flag0x19 != 0) return;

    // 0x35e44ac..0x35e44b0: init cursor (mov rsi,rcx; nop)
    sub_35e44a0_node* cur = a0;
    do {
        // 0x35e44b0..0x35e44b9: recurse on next0x10 (mov rcx,[rsi+0x10]; call 0x35E44A0)
        sub_35e44a0(cur->next0x10);                 // 0x35e44b4  call 0x35E44A0

        // 0x35e44b9..0x35e44c4: load child, set args (mov rdi,[rsi]; mov edx,0x40; mov rcx,rsi)
        sub_35e44a0_node* child = cur->field0x0;    // 0x35e44b9  mov rdi,[rsi]
        // RDX=0x40 is dead on entry to sub_e935700 (sub_392960: mov rdx,rcx)
        sub_e935700(cur);                           // 0x35e44c4  call 0xE935700

        // 0x35e44c9..0x35e44d2: loop continuation (cmp [rdi+0x19],0; mov rsi,rdi; je -> loop)
        cur = child;                                // 0x35e44cd  mov rsi,rdi
    } while (child->flag0x19 == 0);                 // 0x35e44c9  cmp byte ptr [rdi+0x19],0 ; 0x35e44d0  je short 0x35E44B0
    // 0x35e44d2..0x35e44d9: epilogue (add rsp,0x28; pop rdi; pop rsi; ret)
}

} // namespace native

LIFT_FN(35e44a0, "sub_35e44a0", 0x35E44A0, sub_35e44a0, nullptr);