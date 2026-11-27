// LIFT 0x67bc2c0 size 0x137 1.26.62.01 sub_67bc2c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_67bc2c0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_67bc2c0, "sub_67bc2c0", 0x67bc2c0, sub_67bc2c0, nullptr);

// Verbatim call instructions from the disassembly of [0x67bc2c0, 0x67bc3f7) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x67bc2f2  call qword ptr [0xF99FFA0]
0x67bc308  call qword ptr [0xF99FFA0]
0x67bc357  call qword ptr [0xF99FFA0]
0x67bc36d  call qword ptr [0xF99FFA0]
0x67bc3be  call 0xE935700
0x67bc3f0  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x67bc2c0, 0x67bc3f7) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_67bc2c0(void* self) {
    // 0x67bc2c0..0x67bc2d7: basic block 0
    // 0x67bc2c0  push r15
    // 0x67bc2c2  push r14
    // 0x67bc2c4  push rsi
    // 0x67bc2c5  push rdi
    // 0x67bc2c6  push rbx
    // 0x67bc2c7  sub rsp,0x30
    // 0x67bc2cb  mov rsi,rcx
    // 0x67bc2ce  cmp byte ptr [rcx+0xF0],3
    // 0x67bc2d5  jne short 0x67BC30E
    // -> if *u8(a0+0xF0) != 0x3 goto L_0x67bc30e
    // -> if *u8(a0+0xF0) == 0x3 goto L_0x67bc2d7
    // [open] translate statements for this block
    L_0x67bc2c0:;
    __debugbreak(); // [open] NOT LIFTED block 0

    // 0x67bc2d7..0x67bc2e3: basic block 1
    // 0x67bc2d7  mov rdi,[rsi+0xE8]
    // 0x67bc2de  test rdi,rdi
    // 0x67bc2e1  je short 0x67BC30E
    // -> if *(a0+0xE8) == 0 goto L_0x67bc30e
    // -> if *(a0+0xE8) != 0 goto L_0x67bc2e3
    // [open] translate statements for this block
    L_0x67bc2d7:;
    __debugbreak(); // [open] NOT LIFTED block 1

    // 0x67bc2e3..0x67bc2e9: basic block 2
    // 0x67bc2e3  lock dec dword ptr [rdi+8]
    // 0x67bc2e7  jne short 0x67BC30E
    // -> if (Dec *u32(*(a0+0xE8)+0x8), ?) != 0 goto L_0x67bc30e
    // -> if (Dec *u32(*(a0+0xE8)+0x8), ?) == 0 goto L_0x67bc2e9
    // [open] translate statements for this block
    L_0x67bc2e3:;
    __debugbreak(); // [open] NOT LIFTED block 2

    // 0x67bc2e9..0x67bc2fe: basic block 3
    // 0x67bc2e9  mov rax,[rdi]
    // 0x67bc2ec  mov rax,[rax]
    // 0x67bc2ef  mov rcx,rdi
    // 0x67bc2f2  call qword ptr [0xF99FFA0]
    // 0x67bc2f8  lock dec dword ptr [rdi+0xC]
    // 0x67bc2fc  jne short 0x67BC30E
    // -> if (Dec *u32(*(a0+0xE8)+0xC), ?) != 0 goto L_0x67bc30e
    // -> if (Dec *u32(*(a0+0xE8)+0xC), ?) == 0 goto L_0x67bc2fe
    // [open] translate statements for this block
    L_0x67bc2e9:;
    __debugbreak(); // [open] NOT LIFTED block 3

    // 0x67bc2fe..0x67bc30e: basic block 4
    // 0x67bc2fe  mov rax,[rdi]
    // 0x67bc301  mov rax,[rax+8]
    // 0x67bc305  mov rcx,rdi
    // 0x67bc308  call qword ptr [0xF99FFA0]
    // -> if fallthrough goto L_0x67bc30e
    // [open] translate statements for this block
    L_0x67bc2fe:;
    __debugbreak(); // [open] NOT LIFTED block 4

    // 0x67bc30e..0x67bc31a: basic block 5
    // 0x67bc30e  mov rbx,[rsi+0xC0]
    // 0x67bc315  test rbx,rbx
    // 0x67bc318  je short 0x67BC384
    // -> if *(a0+0xC0) == 0 goto L_0x67bc384
    // -> if *(a0+0xC0) != 0 goto L_0x67bc31a
    // [open] translate statements for this block
    L_0x67bc30e:;
    __debugbreak(); // [open] NOT LIFTED block 5

    // 0x67bc31a..0x67bc32a: basic block 6
    // 0x67bc31a  lea r14,[rsi+0xC0]
    // 0x67bc321  mov r15,[rsi+0xC8]
    // 0x67bc328  jmp short 0x67BC334
    // -> if jmp goto L_0x67bc334
    // [open] translate statements for this block
    L_0x67bc31a:;
    __debugbreak(); // [open] NOT LIFTED block 6

    // 0x67bc32a..0x67bc330: basic block 7
    // 0x67bc32a  nop [rax+rax]
    // -> if fallthrough goto L_0x67bc330
    // [open] translate statements for this block
    L_0x67bc32a:;
    __debugbreak(); // [open] NOT LIFTED block 7

    // 0x67bc330..0x67bc334: basic block 8
    // 0x67bc330  add rbx,0x28
    // -> if fallthrough goto L_0x67bc334
    // [open] translate statements for this block
    L_0x67bc330:;
    __debugbreak(); // [open] NOT LIFTED block 8

    // 0x67bc334..0x67bc339: basic block 9
    // 0x67bc334  cmp rbx,r15
    // 0x67bc337  je short 0x67BC375
    // -> if ? == *(a0+0xC8) goto L_0x67bc375
    // -> if ? != *(a0+0xC8) goto L_0x67bc339
    // [open] translate statements for this block
    L_0x67bc334:;
    __debugbreak(); // [open] NOT LIFTED block 9

    // 0x67bc339..0x67bc33f: basic block 10
    // 0x67bc339  cmp byte ptr [rbx+0x18],2
    // 0x67bc33d  jne short 0x67BC330
    // -> if ? != 0x2 goto L_0x67bc330
    // -> if ? == 0x2 goto L_0x67bc33f
    // [open] translate statements for this block
    L_0x67bc339:;
    __debugbreak(); // [open] NOT LIFTED block 10

    // 0x67bc33f..0x67bc348: basic block 11
    // 0x67bc33f  mov rdi,[rbx+8]
    // 0x67bc343  test rdi,rdi
    // 0x67bc346  je short 0x67BC330
    // -> if ? == 0 goto L_0x67bc330
    // -> if ? != 0 goto L_0x67bc348
    // [open] translate statements for this block
    L_0x67bc33f:;
    __debugbreak(); // [open] NOT LIFTED block 11

    // 0x67bc348..0x67bc34e: basic block 12
    // 0x67bc348  lock dec dword ptr [rdi+8]
    // 0x67bc34c  jne short 0x67BC330
    // -> if (Dec ?, ?) != 0 goto L_0x67bc330
    // -> if (Dec ?, ?) == 0 goto L_0x67bc34e
    // [open] translate statements for this block
    L_0x67bc348:;
    __debugbreak(); // [open] NOT LIFTED block 12

    // 0x67bc34e..0x67bc363: basic block 13
    // 0x67bc34e  mov rax,[rdi]
    // 0x67bc351  mov rax,[rax]
    // 0x67bc354  mov rcx,rdi
    // 0x67bc357  call qword ptr [0xF99FFA0]
    // 0x67bc35d  lock dec dword ptr [rdi+0xC]
    // 0x67bc361  jne short 0x67BC330
    // -> if (Dec ?, ?) != 0 goto L_0x67bc330
    // -> if (Dec ?, ?) == 0 goto L_0x67bc363
    // [open] translate statements for this block
    L_0x67bc34e:;
    __debugbreak(); // [open] NOT LIFTED block 13

    // 0x67bc363..0x67bc375: basic block 14
    // 0x67bc363  mov rax,[rdi]
    // 0x67bc366  mov rax,[rax+8]
    // 0x67bc36a  mov rcx,rdi
    // 0x67bc36d  call qword ptr [0xF99FFA0]
    // 0x67bc373  jmp short 0x67BC330
    // -> if jmp goto L_0x67bc330
    // [open] translate statements for this block
    L_0x67bc363:;
    __debugbreak(); // [open] NOT LIFTED block 14

    // 0x67bc375..0x67bc384: basic block 15
    // 0x67bc375  xorps xmm0,xmm0
    // 0x67bc378  movups [r14],xmm0
    // 0x67bc37c  mov qword ptr [r14+0x10],0
    // -> if fallthrough goto L_0x67bc384
    // [open] translate statements for this block
    L_0x67bc375:;
    __debugbreak(); // [open] NOT LIFTED block 15

    // 0x67bc384..0x67bc38a: basic block 16
    // 0x67bc384  cmp byte ptr [rsi+0x48],1
    // 0x67bc388  jne short 0x67BC3D1
    // -> if *u8(a0+0x48) != 0x1 goto L_0x67bc3d1
    // -> if *u8(a0+0x48) == 0x1 goto L_0x67bc38a
    // [open] translate statements for this block
    L_0x67bc384:;
    __debugbreak(); // [open] NOT LIFTED block 16

    // 0x67bc38a..0x67bc396: basic block 17
    // 0x67bc38a  lea rdi,[rsi+8]
    // 0x67bc38e  mov rcx,[rdi]
    // 0x67bc391  test rcx,rcx
    // 0x67bc394  je short 0x67BC3D1
    // -> if *(a0+0x8) == 0 goto L_0x67bc3d1
    // -> if *(a0+0x8) != 0 goto L_0x67bc396
    // [open] translate statements for this block
    L_0x67bc38a:;
    __debugbreak(); // [open] NOT LIFTED block 17

    // 0x67bc396..0x67bc3a6: basic block 18
    // 0x67bc396  mov rdx,[rsi+0x18]
    // 0x67bc39a  sub rdx,rcx
    // 0x67bc39d  cmp rdx,0x1000
    // 0x67bc3a4  jb short 0x67BC3BE
    // -> if (*(a0+0x18) - *(a0+0x8)) <u 0x1000 goto L_0x67bc3be
    // -> if (*(a0+0x18) - *(a0+0x8)) >=u 0x1000 goto L_0x67bc3a6
    // [open] translate statements for this block
    L_0x67bc396:;
    __debugbreak(); // [open] NOT LIFTED block 18

    // 0x67bc3a6..0x67bc3b7: basic block 19
    // 0x67bc3a6  mov rax,[rcx-8]
    // 0x67bc3aa  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x67bc3ae  sub rcx,rax
    // 0x67bc3b1  cmp rcx,0x20
    // 0x67bc3b5  jae short 0x67BC3DD
    // -> if (*(a0+0x8)-0x8 - *(*(a0+0x8)-0x8)) >=u 0x20 goto L_0x67bc3dd
    // -> if (*(a0+0x8)-0x8 - *(*(a0+0x8)-0x8)) <u 0x20 goto L_0x67bc3b7
    // [open] translate statements for this block
    L_0x67bc3a6:;
    __debugbreak(); // [open] NOT LIFTED block 19

    // 0x67bc3b7..0x67bc3be: basic block 20
    // 0x67bc3b7  or rdx,0x27
    // 0x67bc3bb  mov rcx,rax
    // -> if fallthrough goto L_0x67bc3be
    // [open] translate statements for this block
    L_0x67bc3b7:;
    __debugbreak(); // [open] NOT LIFTED block 20

    // 0x67bc3be..0x67bc3d1: basic block 21
    // 0x67bc3be  call 0xE935700
    // 0x67bc3c3  xorps xmm0,xmm0
    // 0x67bc3c6  movups [rdi],xmm0
    // 0x67bc3c9  mov qword ptr [rdi+0x10],0
    // -> if fallthrough goto L_0x67bc3d1
    // [open] translate statements for this block
    L_0x67bc3be:;
    __debugbreak(); // [open] NOT LIFTED block 21

    // 0x67bc3d1..0x67bc3dd: basic block 22
    // 0x67bc3d1  add rsp,0x30
    // 0x67bc3d5  pop rbx
    // 0x67bc3d6  pop rdi
    // 0x67bc3d7  pop rsi
    // 0x67bc3d8  pop r14
    // 0x67bc3da  pop r15
    // 0x67bc3dc  ret
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x67bc3d1:;
    __debugbreak(); // [open] NOT LIFTED block 22

    // 0x67bc3dd..0x67bc3f7: basic block 23
    // 0x67bc3dd  mov qword ptr [rsp+0x20],0
    // 0x67bc3e6  xor ecx,ecx
    // 0x67bc3e8  xor edx,edx
    // 0x67bc3ea  xor r8d,r8d
    // 0x67bc3ed  xor r9d,r9d
    // 0x67bc3f0  call qword ptr [0xF9A8C78]
    // 0x67bc3f6  int3
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x67bc3dd:;
    __debugbreak(); // [open] NOT LIFTED block 23

    return 0;   // unreachable; kept so the skeleton compiles until every block is translated
}

} // namespace native::helpers
