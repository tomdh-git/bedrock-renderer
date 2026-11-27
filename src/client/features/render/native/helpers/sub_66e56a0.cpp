// LIFT 0x66e56a0 size 0x137 1.26.62.01 sub_66e56a0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_66e56a0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_66e56a0, "sub_66e56a0", 0x66e56a0, sub_66e56a0, nullptr);

// Verbatim call instructions from the disassembly of [0x66e56a0, 0x66e57d7) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x66e56d2  call qword ptr [0xF99FFA0]
0x66e56e8  call qword ptr [0xF99FFA0]
0x66e5737  call qword ptr [0xF99FFA0]
0x66e574d  call qword ptr [0xF99FFA0]
0x66e579e  call 0xE935700
0x66e57d0  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x66e56a0, 0x66e57d7) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_66e56a0(void* self) {
    // 0x66e56a0..0x66e56b7: basic block 0
    // 0x66e56a0  push r15
    // 0x66e56a2  push r14
    // 0x66e56a4  push rsi
    // 0x66e56a5  push rdi
    // 0x66e56a6  push rbx
    // 0x66e56a7  sub rsp,0x30
    // 0x66e56ab  mov rsi,rcx
    // 0x66e56ae  cmp byte ptr [rcx+0x180],3
    // 0x66e56b5  jne short 0x66E56EE
    // -> if *u8(a0+0x180) != 0x3 goto L_0x66e56ee
    // -> if *u8(a0+0x180) == 0x3 goto L_0x66e56b7
    // [open] translate statements for this block
    L_0x66e56a0:;
    __debugbreak(); // [open] NOT LIFTED block 0

    // 0x66e56b7..0x66e56c3: basic block 1
    // 0x66e56b7  mov rdi,[rsi+0x178]
    // 0x66e56be  test rdi,rdi
    // 0x66e56c1  je short 0x66E56EE
    // -> if *(a0+0x178) == 0 goto L_0x66e56ee
    // -> if *(a0+0x178) != 0 goto L_0x66e56c3
    // [open] translate statements for this block
    L_0x66e56b7:;
    __debugbreak(); // [open] NOT LIFTED block 1

    // 0x66e56c3..0x66e56c9: basic block 2
    // 0x66e56c3  lock dec dword ptr [rdi+8]
    // 0x66e56c7  jne short 0x66E56EE
    // -> if (Dec *u32(*(a0+0x178)+0x8), ?) != 0 goto L_0x66e56ee
    // -> if (Dec *u32(*(a0+0x178)+0x8), ?) == 0 goto L_0x66e56c9
    // [open] translate statements for this block
    L_0x66e56c3:;
    __debugbreak(); // [open] NOT LIFTED block 2

    // 0x66e56c9..0x66e56de: basic block 3
    // 0x66e56c9  mov rax,[rdi]
    // 0x66e56cc  mov rax,[rax]
    // 0x66e56cf  mov rcx,rdi
    // 0x66e56d2  call qword ptr [0xF99FFA0]
    // 0x66e56d8  lock dec dword ptr [rdi+0xC]
    // 0x66e56dc  jne short 0x66E56EE
    // -> if (Dec *u32(*(a0+0x178)+0xC), ?) != 0 goto L_0x66e56ee
    // -> if (Dec *u32(*(a0+0x178)+0xC), ?) == 0 goto L_0x66e56de
    // [open] translate statements for this block
    L_0x66e56c9:;
    __debugbreak(); // [open] NOT LIFTED block 3

    // 0x66e56de..0x66e56ee: basic block 4
    // 0x66e56de  mov rax,[rdi]
    // 0x66e56e1  mov rax,[rax+8]
    // 0x66e56e5  mov rcx,rdi
    // 0x66e56e8  call qword ptr [0xF99FFA0]
    // -> if fallthrough goto L_0x66e56ee
    // [open] translate statements for this block
    L_0x66e56de:;
    __debugbreak(); // [open] NOT LIFTED block 4

    // 0x66e56ee..0x66e56fa: basic block 5
    // 0x66e56ee  mov rbx,[rsi+0x150]
    // 0x66e56f5  test rbx,rbx
    // 0x66e56f8  je short 0x66E5764
    // -> if *(a0+0x150) == 0 goto L_0x66e5764
    // -> if *(a0+0x150) != 0 goto L_0x66e56fa
    // [open] translate statements for this block
    L_0x66e56ee:;
    __debugbreak(); // [open] NOT LIFTED block 5

    // 0x66e56fa..0x66e570a: basic block 6
    // 0x66e56fa  lea r14,[rsi+0x150]
    // 0x66e5701  mov r15,[rsi+0x158]
    // 0x66e5708  jmp short 0x66E5714
    // -> if jmp goto L_0x66e5714
    // [open] translate statements for this block
    L_0x66e56fa:;
    __debugbreak(); // [open] NOT LIFTED block 6

    // 0x66e570a..0x66e5710: basic block 7
    // 0x66e570a  nop [rax+rax]
    // -> if fallthrough goto L_0x66e5710
    // [open] translate statements for this block
    L_0x66e570a:;
    __debugbreak(); // [open] NOT LIFTED block 7

    // 0x66e5710..0x66e5714: basic block 8
    // 0x66e5710  add rbx,0x28
    // -> if fallthrough goto L_0x66e5714
    // [open] translate statements for this block
    L_0x66e5710:;
    __debugbreak(); // [open] NOT LIFTED block 8

    // 0x66e5714..0x66e5719: basic block 9
    // 0x66e5714  cmp rbx,r15
    // 0x66e5717  je short 0x66E5755
    // -> if ? == *(a0+0x158) goto L_0x66e5755
    // -> if ? != *(a0+0x158) goto L_0x66e5719
    // [open] translate statements for this block
    L_0x66e5714:;
    __debugbreak(); // [open] NOT LIFTED block 9

    // 0x66e5719..0x66e571f: basic block 10
    // 0x66e5719  cmp byte ptr [rbx+0x18],2
    // 0x66e571d  jne short 0x66E5710
    // -> if ? != 0x2 goto L_0x66e5710
    // -> if ? == 0x2 goto L_0x66e571f
    // [open] translate statements for this block
    L_0x66e5719:;
    __debugbreak(); // [open] NOT LIFTED block 10

    // 0x66e571f..0x66e5728: basic block 11
    // 0x66e571f  mov rdi,[rbx+8]
    // 0x66e5723  test rdi,rdi
    // 0x66e5726  je short 0x66E5710
    // -> if ? == 0 goto L_0x66e5710
    // -> if ? != 0 goto L_0x66e5728
    // [open] translate statements for this block
    L_0x66e571f:;
    __debugbreak(); // [open] NOT LIFTED block 11

    // 0x66e5728..0x66e572e: basic block 12
    // 0x66e5728  lock dec dword ptr [rdi+8]
    // 0x66e572c  jne short 0x66E5710
    // -> if (Dec ?, ?) != 0 goto L_0x66e5710
    // -> if (Dec ?, ?) == 0 goto L_0x66e572e
    // [open] translate statements for this block
    L_0x66e5728:;
    __debugbreak(); // [open] NOT LIFTED block 12

    // 0x66e572e..0x66e5743: basic block 13
    // 0x66e572e  mov rax,[rdi]
    // 0x66e5731  mov rax,[rax]
    // 0x66e5734  mov rcx,rdi
    // 0x66e5737  call qword ptr [0xF99FFA0]
    // 0x66e573d  lock dec dword ptr [rdi+0xC]
    // 0x66e5741  jne short 0x66E5710
    // -> if (Dec ?, ?) != 0 goto L_0x66e5710
    // -> if (Dec ?, ?) == 0 goto L_0x66e5743
    // [open] translate statements for this block
    L_0x66e572e:;
    __debugbreak(); // [open] NOT LIFTED block 13

    // 0x66e5743..0x66e5755: basic block 14
    // 0x66e5743  mov rax,[rdi]
    // 0x66e5746  mov rax,[rax+8]
    // 0x66e574a  mov rcx,rdi
    // 0x66e574d  call qword ptr [0xF99FFA0]
    // 0x66e5753  jmp short 0x66E5710
    // -> if jmp goto L_0x66e5710
    // [open] translate statements for this block
    L_0x66e5743:;
    __debugbreak(); // [open] NOT LIFTED block 14

    // 0x66e5755..0x66e5764: basic block 15
    // 0x66e5755  xorps xmm0,xmm0
    // 0x66e5758  movups [r14],xmm0
    // 0x66e575c  mov qword ptr [r14+0x10],0
    // -> if fallthrough goto L_0x66e5764
    // [open] translate statements for this block
    L_0x66e5755:;
    __debugbreak(); // [open] NOT LIFTED block 15

    // 0x66e5764..0x66e576a: basic block 16
    // 0x66e5764  cmp byte ptr [rsi+0x58],1
    // 0x66e5768  jne short 0x66E57B1
    // -> if *u8(a0+0x58) != 0x1 goto L_0x66e57b1
    // -> if *u8(a0+0x58) == 0x1 goto L_0x66e576a
    // [open] translate statements for this block
    L_0x66e5764:;
    __debugbreak(); // [open] NOT LIFTED block 16

    // 0x66e576a..0x66e5776: basic block 17
    // 0x66e576a  lea rdi,[rsi+0x18]
    // 0x66e576e  mov rcx,[rdi]
    // 0x66e5771  test rcx,rcx
    // 0x66e5774  je short 0x66E57B1
    // -> if *(a0+0x18) == 0 goto L_0x66e57b1
    // -> if *(a0+0x18) != 0 goto L_0x66e5776
    // [open] translate statements for this block
    L_0x66e576a:;
    __debugbreak(); // [open] NOT LIFTED block 17

    // 0x66e5776..0x66e5786: basic block 18
    // 0x66e5776  mov rdx,[rsi+0x28]
    // 0x66e577a  sub rdx,rcx
    // 0x66e577d  cmp rdx,0x1000
    // 0x66e5784  jb short 0x66E579E
    // -> if (*(a0+0x28) - *(a0+0x18)) <u 0x1000 goto L_0x66e579e
    // -> if (*(a0+0x28) - *(a0+0x18)) >=u 0x1000 goto L_0x66e5786
    // [open] translate statements for this block
    L_0x66e5776:;
    __debugbreak(); // [open] NOT LIFTED block 18

    // 0x66e5786..0x66e5797: basic block 19
    // 0x66e5786  mov rax,[rcx-8]
    // 0x66e578a  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x66e578e  sub rcx,rax
    // 0x66e5791  cmp rcx,0x20
    // 0x66e5795  jae short 0x66E57BD
    // -> if (*(a0+0x18)-0x8 - *(*(a0+0x18)-0x8)) >=u 0x20 goto L_0x66e57bd
    // -> if (*(a0+0x18)-0x8 - *(*(a0+0x18)-0x8)) <u 0x20 goto L_0x66e5797
    // [open] translate statements for this block
    L_0x66e5786:;
    __debugbreak(); // [open] NOT LIFTED block 19

    // 0x66e5797..0x66e579e: basic block 20
    // 0x66e5797  or rdx,0x27
    // 0x66e579b  mov rcx,rax
    // -> if fallthrough goto L_0x66e579e
    // [open] translate statements for this block
    L_0x66e5797:;
    __debugbreak(); // [open] NOT LIFTED block 20

    // 0x66e579e..0x66e57b1: basic block 21
    // 0x66e579e  call 0xE935700
    // 0x66e57a3  xorps xmm0,xmm0
    // 0x66e57a6  movups [rdi],xmm0
    // 0x66e57a9  mov qword ptr [rdi+0x10],0
    // -> if fallthrough goto L_0x66e57b1
    // [open] translate statements for this block
    L_0x66e579e:;
    __debugbreak(); // [open] NOT LIFTED block 21

    // 0x66e57b1..0x66e57bd: basic block 22
    // 0x66e57b1  add rsp,0x30
    // 0x66e57b5  pop rbx
    // 0x66e57b6  pop rdi
    // 0x66e57b7  pop rsi
    // 0x66e57b8  pop r14
    // 0x66e57ba  pop r15
    // 0x66e57bc  ret
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x66e57b1:;
    __debugbreak(); // [open] NOT LIFTED block 22

    // 0x66e57bd..0x66e57d7: basic block 23
    // 0x66e57bd  mov qword ptr [rsp+0x20],0
    // 0x66e57c6  xor ecx,ecx
    // 0x66e57c8  xor edx,edx
    // 0x66e57ca  xor r8d,r8d
    // 0x66e57cd  xor r9d,r9d
    // 0x66e57d0  call qword ptr [0xF9A8C78]
    // 0x66e57d6  int3
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x66e57bd:;
    __debugbreak(); // [open] NOT LIFTED block 23

    return 0;   // unreachable; kept so the skeleton compiles until every block is translated
}

} // namespace native::helpers
