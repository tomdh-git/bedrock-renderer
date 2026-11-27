// LIFT 0x11664a0 size 0x139 1.26.62.01 sub_11664a0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_11664a0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_11664a0, "sub_11664a0", 0x11664a0, sub_11664a0, nullptr);

// Verbatim call instructions from the disassembly of [0x11664a0, 0x11665d9) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x11664ba  call 0xEEC59F0
0x11664f8  call 0xE935700
0x116653d  call qword ptr [0xF99FFA0]
0x1166559  call qword ptr [0xF99FFA0]
0x11665bf  call 0xEEC5A00
0x11665d3  call 0xEEC5A00
#endif

// Ranges: every instruction of [0x11664a0, 0x11665d9) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_11664a0(void* self) {
    // 0x11664a0..0x11664c7: basic block 0
    // 0x11664a0  push r15
    // 0x11664a2  push r14
    // 0x11664a4  push rsi
    // 0x11664a5  push rdi
    // 0x11664a6  push rbx
    // 0x11664a7  sub rsp,0x30
    // 0x11664ab  movaps [rsp+0x20],xmm6
    // 0x11664b0  mov rsi,rcx
    // 0x11664b3  lea rdi,[rcx+0x50]
    // 0x11664b7  mov rcx,rdi
    // 0x11664ba  call 0xEEC59F0
    // 0x11664bf  test eax,eax
    // 0x11664c1  jne 0x11665BA
    // -> if u32(ret@11664ba) != 0 goto L_0x11665ba
    // -> if u32(ret@11664ba) == 0 goto L_0x11664c7
    // [open] translate statements for this block
    L_0x11664a0:;
    __debugbreak(); // [open] NOT LIFTED block 0

    // 0x11664c7..0x11664d7: basic block 1
    // 0x11664c7  cmp dword ptr [rsi+0x9C],0x7FFFFFFF
    // 0x11664d1  je 0x11665C4
    // -> if *u32(a0+0x9C) == 0x7FFFFFFF goto L_0x11665c4
    // -> if *u32(a0+0x9C) != 0x7FFFFFFF goto L_0x11664d7
    // [open] translate statements for this block
    L_0x11664c7:;
    __debugbreak(); // [open] NOT LIFTED block 1

    // 0x11664d7..0x11664e8: basic block 2
    // 0x11664d7  mov rbx,[rsi+0x40]
    // 0x11664db  add rsi,0x40
    // 0x11664df  cmp rbx,rsi
    // 0x11664e2  je 0x11665A2
    // -> if *(a0+0x40) == a0+0x40 goto L_0x11665a2
    // -> if *(a0+0x40) != a0+0x40 goto L_0x11664e8
    // [open] translate statements for this block
    L_0x11664d7:;
    __debugbreak(); // [open] NOT LIFTED block 2

    // 0x11664e8..0x11664ed: basic block 3
    // 0x11664e8  xorps xmm6,xmm6
    // 0x11664eb  jmp short 0x1166509
    // -> if jmp goto L_0x1166509
    // [open] translate statements for this block
    L_0x11664e8:;
    __debugbreak(); // [open] NOT LIFTED block 3

    // 0x11664ed..0x11664f0: basic block 4
    // 0x11664ed  nop [rax]
    // -> if fallthrough goto L_0x11664f0
    // [open] translate statements for this block
    L_0x11664ed:;
    __debugbreak(); // [open] NOT LIFTED block 4

    // 0x11664f0..0x1166509: basic block 5
    // 0x11664f0  mov edx,0x38
    // 0x11664f5  mov rcx,rbx
    // 0x11664f8  call 0xE935700
    // 0x11664fd  mov rbx,[rsi]
    // 0x1166500  cmp rbx,rsi
    // 0x1166503  je 0x11665A2
    // -> if *(a0+0x40) == a0+0x40 goto L_0x11665a2
    // -> if *(a0+0x40) != a0+0x40 goto L_0x1166509
    // [open] translate statements for this block
    L_0x11664f0:;
    __debugbreak(); // [open] NOT LIFTED block 5

    // 0x1166509..0x116650f: basic block 6
    // 0x1166509  cmp byte ptr [rbx+0x30],1
    // 0x116650d  jne short 0x116657F
    // -> if *u8(*(a0+0x40)+0x30) != 0x1 goto L_0x116657f
    // -> if *u8(*(a0+0x40)+0x30) == 0x1 goto L_0x116650f
    // [open] translate statements for this block
    L_0x1166509:;
    __debugbreak(); // [open] NOT LIFTED block 6

    // 0x116650f..0x1166518: basic block 7
    // 0x116650f  mov r14,[rbx+0x18]
    // 0x1166513  test r14,r14
    // 0x1166516  je short 0x116657F
    // -> if *(*(a0+0x40)+0x18) == 0 goto L_0x116657f
    // -> if *(*(a0+0x40)+0x18) != 0 goto L_0x1166518
    // [open] translate statements for this block
    L_0x116650f:;
    __debugbreak(); // [open] NOT LIFTED block 7

    // 0x1166518..0x116651e: basic block 8
    // 0x1166518  mov r15,[rbx+0x20]
    // 0x116651c  jmp short 0x1166524
    // -> if jmp goto L_0x1166524
    // [open] translate statements for this block
    L_0x1166518:;
    __debugbreak(); // [open] NOT LIFTED block 8

    // 0x116651e..0x1166520: basic block 9
    // 0x116651e  xchg ax,ax
    // -> if fallthrough goto L_0x1166520
    // [open] translate statements for this block
    L_0x116651e:;
    __debugbreak(); // [open] NOT LIFTED block 9

    // 0x1166520..0x1166524: basic block 10
    // 0x1166520  add r14,0x18
    // -> if fallthrough goto L_0x1166524
    // [open] translate statements for this block
    L_0x1166520:;
    __debugbreak(); // [open] NOT LIFTED block 10

    // 0x1166524..0x1166529: basic block 11
    // 0x1166524  cmp r14,r15
    // 0x1166527  je short 0x1166570
    // -> if ? == *(*(a0+0x40)+0x20) goto L_0x1166570
    // -> if ? != *(*(a0+0x40)+0x20) goto L_0x1166529
    // [open] translate statements for this block
    L_0x1166524:;
    __debugbreak(); // [open] NOT LIFTED block 11

    // 0x1166529..0x1166532: basic block 12
    // 0x1166529  mov rcx,[r14+0x10]
    // 0x116652d  test rcx,rcx
    // 0x1166530  je short 0x1166543
    // -> if ? == 0 goto L_0x1166543
    // -> if ? != 0 goto L_0x1166532
    // [open] translate statements for this block
    L_0x1166529:;
    __debugbreak(); // [open] NOT LIFTED block 12

    // 0x1166532..0x1166543: basic block 13
    // 0x1166532  mov rax,[rcx]
    // 0x1166535  mov rax,[rax]
    // 0x1166538  mov edx,1
    // 0x116653d  call qword ptr [0xF99FFA0]
    // -> if fallthrough goto L_0x1166543
    // [open] translate statements for this block
    L_0x1166532:;
    __debugbreak(); // [open] NOT LIFTED block 13

    // 0x1166543..0x116654c: basic block 14
    // 0x1166543  mov rcx,[r14+8]
    // 0x1166547  test rcx,rcx
    // 0x116654a  je short 0x1166520
    // -> if ? == 0 goto L_0x1166520
    // -> if ? != 0 goto L_0x116654c
    // [open] translate statements for this block
    L_0x1166543:;
    __debugbreak(); // [open] NOT LIFTED block 14

    // 0x116654c..0x1166552: basic block 15
    // 0x116654c  lock dec dword ptr [rcx+0xC]
    // 0x1166550  jne short 0x1166520
    // -> if (Dec ?, ?) != 0 goto L_0x1166520
    // -> if (Dec ?, ?) == 0 goto L_0x1166552
    // [open] translate statements for this block
    L_0x116654c:;
    __debugbreak(); // [open] NOT LIFTED block 15

    // 0x1166552..0x1166561: basic block 16
    // 0x1166552  mov rax,[rcx]
    // 0x1166555  mov rax,[rax+8]
    // 0x1166559  call qword ptr [0xF99FFA0]
    // 0x116655f  jmp short 0x1166520
    // -> if jmp goto L_0x1166520
    // [open] translate statements for this block
    L_0x1166552:;
    __debugbreak(); // [open] NOT LIFTED block 16

    // 0x1166561..0x1166570: basic block 17
    // 0x1166561  nop [rax+rax]
    // -> if fallthrough goto L_0x1166570
    // [open] translate statements for this block
    L_0x1166561:;
    __debugbreak(); // [open] NOT LIFTED block 17

    // 0x1166570..0x116657f: basic block 18
    // 0x1166570  lea rax,[rbx+0x18]
    // 0x1166574  movups [rax],xmm6
    // 0x1166577  mov qword ptr [rax+0x10],0
    // -> if fallthrough goto L_0x116657f
    // [open] translate statements for this block
    L_0x1166570:;
    __debugbreak(); // [open] NOT LIFTED block 18

    // 0x116657f..0x116658b: basic block 19
    // 0x116657f  mov rax,[rbx]
    // 0x1166582  cmp rax,rbx
    // 0x1166585  je 0x11664F0
    // -> if *(*(a0+0x40)) == *(a0+0x40) goto L_0x11664f0
    // -> if *(*(a0+0x40)) != *(a0+0x40) goto L_0x116658b
    // [open] translate statements for this block
    L_0x116657f:;
    __debugbreak(); // [open] NOT LIFTED block 19

    // 0x116658b..0x11665a2: basic block 20
    // 0x116658b  mov rcx,[rbx+8]
    // 0x116658f  mov [rcx],rax
    // 0x1166592  mov [rax+8],rcx
    // 0x1166596  mov [rbx],rbx
    // 0x1166599  mov [rbx+8],rbx
    // 0x116659d  jmp 0x11664F0
    // -> if jmp goto L_0x11664f0
    // [open] translate statements for this block
    L_0x116658b:;
    __debugbreak(); // [open] NOT LIFTED block 20

    // 0x11665a2..0x11665ba: basic block 21
    // 0x11665a2  mov rcx,rdi
    // 0x11665a5  movaps xmm6,[rsp+0x20]
    // 0x11665aa  add rsp,0x30
    // 0x11665ae  pop rbx
    // 0x11665af  pop rdi
    // 0x11665b0  pop rsi
    // 0x11665b1  pop r14
    // 0x11665b3  pop r15
    // 0x11665b5  jmp 0xEEC5A10
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x11665a2:;
    __debugbreak(); // [open] NOT LIFTED block 21

    // 0x11665ba..0x11665c4: basic block 22
    // 0x11665ba  mov ecx,5
    // 0x11665bf  call 0xEEC5A00
    // -> if fallthrough goto L_0x11665c4
    // [open] translate statements for this block
    L_0x11665ba:;
    __debugbreak(); // [open] NOT LIFTED block 22

    // 0x11665c4..0x11665d9: basic block 23
    // 0x11665c4  mov dword ptr [rsi+0x9C],0x7FFFFFFE
    // 0x11665ce  mov ecx,6
    // 0x11665d3  call 0xEEC5A00
    // 0x11665d8  int3
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x11665c4:;
    __debugbreak(); // [open] NOT LIFTED block 23

    return 0;   // unreachable; kept so the skeleton compiles until every block is translated
}

} // namespace native::helpers
