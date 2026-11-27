// LIFT 0x34d640 size 0x39 1.26.62.01 sub_34d640
#include "sub_34d640.h"
#include "sub_e935700.h"

static_assert(offsetof(Sub34d640Node, p0)  == 0x00, "sub_34d640: node->p0 at +0x00");
static_assert(offsetof(Sub34d640Node, p10) == 0x10, "sub_34d640: node->p10 at +0x10");
static_assert(offsetof(Sub34d640Node, b19) == 0x19, "sub_34d640: node->b19 at +0x19");

namespace native {

// sub_34d640 (0x34d640, size 0x39, 1.26.62.01).
//
// Tree walk over a first-child/next-sibling node layout:
//   p0  (+0x00) next-sibling pointer
//   p10 (+0x10) first-child pointer
//   b19 (+0x19) done byte
//
// For the entry node: if b19 != 0 return. Otherwise recurse into p10, then invoke
// sub_e935700 on the node (argument in RCX; the 0x30 the caller places in EDX is not
// consumed by sub_e935700, which forwards only RCX), then walk the p0 chain while the
// sibling's b19 == 0.
//
//   0x34d640  push rsi
//   0x34d641  push rdi
//   0x34d642  sub rsp,0x28
//   0x34d646  cmp byte ptr [rcx+0x19],0
//   0x34d64a  jne short 0x34D672
//   0x34d64c  mov rsi,rcx
//   0x34d64f  nop
//   0x34d650  mov rcx,[rsi+0x10]
//   0x34d654  call 0x34D640
//   0x34d659  mov rdi,[rsi]
//   0x34d65c  mov edx,0x30
//   0x34d661  mov rcx,rsi
//   0x34d664  call 0xE935700
//   0x34d669  cmp byte ptr [rdi+0x19],0
//   0x34d66d  mov rsi,rdi
//   0x34d670  je short 0x34D650
//   0x34d672  add rsp,0x28
//   0x34d676  pop rdi
//   0x34d677  pop rsi
//   0x34d678  ret
//
// Verbatim instructions of the function (matches rdis dis 0x34d640 0x39):
#if 0
0x34d640  push rsi
0x34d641  push rdi
0x34d642  sub rsp,0x28
0x34d646  cmp byte ptr [rcx+0x19],0
0x34d64a  jne short 0x34D672
0x34d64c  mov rsi,rcx
0x34d64f  nop
0x34d650  mov rcx,[rsi+0x10]
0x34d654  call 0x34D640
0x34d659  mov rdi,[rsi]
0x34d65c  mov edx,0x30
0x34d661  mov rcx,rsi
0x34d664  call 0xE935700
0x34d669  cmp byte ptr [rdi+0x19],0
0x34d66d  mov rsi,rdi
0x34d670  je short 0x34D650
0x34d672  add rsp,0x28
0x34d676  pop rdi
0x34d677  pop rsi
0x34d678  ret
#endif

void sub_34d640(Sub34d640Node* node)
{
    // 0x34d640..0x34d646   push rsi; push rdi; sub rsp,0x28  (frame setup)
    // 0x34d646  cmp byte ptr [rcx+0x19],0
    // 0x34d64a  jne short 0x34D672
    if (node->b19 != 0) {                          // 0x34d646  cmp byte ptr [rcx+0x19],0 ; 0x34d64a  jne short 0x34D672
        return;                                    // -> 0x34d672..0x34d679 epilogue + ret
    }

    // 0x34d64c  mov rsi,rcx ; 0x34d64f  nop
    Sub34d640Node* cur = node;                     // 0x34d64c  mov rsi,rcx

    for (;;) {                                     // loc_34d650
        // 0x34d650  mov rcx,[rsi+0x10]
        // 0x34d654  call 0x34D640
        sub_34d640(cur->p10);                      // 0x34d650  mov rcx,[rsi+0x10] ; 0x34d654  call 0x34D640

        // 0x34d659  mov rdi,[rsi]
        Sub34d640Node* sibling = cur->p0;          // 0x34d659  mov rdi,[rsi]

        // 0x34d65c  mov edx,0x30 ; 0x34d661  mov rcx,rsi
        // 0x34d664  call 0xE935700    (sub_e935700 consumes only RCX; EDX=0x30 is dead)
        sub_e935700(cur);                          // 0x34d65c  mov edx,0x30 ; 0x34d661  mov rcx,rsi ; 0x34d664  call 0xE935700

        // 0x34d669  cmp byte ptr [rdi+0x19],0
        // 0x34d66d  mov rsi,rdi
        // 0x34d670  je short 0x34D650
        if (sibling->b19 == 0) {                   // 0x34d669  cmp byte ptr [rdi+0x19],0 ; 0x34d670  je short 0x34D650
            cur = sibling;                         // 0x34d66d  mov rsi,rdi
            continue;                              // -> loc_34d650
        }
        return;                                    // -> 0x34d672..0x34d679 epilogue + ret
    }
}

LIFT_FN(sub_34d640, "sub_34d640", 0x34d640, sub_34d640, nullptr);

} // namespace native