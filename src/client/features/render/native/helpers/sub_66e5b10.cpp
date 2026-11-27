// LIFT 0x66e5b10 size 0x137 1.26.62.01 sub_66e5b10
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_66e5b10.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_66e5b10, "sub_66e5b10", 0x66e5b10, sub_66e5b10, nullptr);

// Verbatim call instructions from the disassembly of [0x66e5b10, 0x66e5c47) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x66e5b42  call qword ptr [0xF99FFA0]
0x66e5b58  call qword ptr [0xF99FFA0]
0x66e5ba7  call qword ptr [0xF99FFA0]
0x66e5bbd  call qword ptr [0xF99FFA0]
0x66e5c0e  call 0xE935700
0x66e5c40  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x66e5b10, 0x66e5c47) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_66e5b10(void* self) {
    // 0x66e5b10..0x66e5b27: basic block 0
    // 0x66e5b10  push r15
    // 0x66e5b12  push r14
    // 0x66e5b14  push rsi
    // 0x66e5b15  push rdi
    // 0x66e5b16  push rbx
    // 0x66e5b17  sub rsp,0x30
    // 0x66e5b1b  mov rsi,rcx
    // 0x66e5b1e  cmp byte ptr [rcx+0x170],3
    // 0x66e5b25  jne short 0x66E5B5E
    // -> if *u8(a0+0x170) != 0x3 goto L_0x66e5b5e
    // -> if *u8(a0+0x170) == 0x3 goto L_0x66e5b27
    // [open] translate statements for this block
    L_0x66e5b10:;
    __debugbreak(); // [open] NOT LIFTED block 0

    // 0x66e5b27..0x66e5b33: basic block 1
    // 0x66e5b27  mov rdi,[rsi+0x168]
    // 0x66e5b2e  test rdi,rdi
    // 0x66e5b31  je short 0x66E5B5E
    // -> if *(a0+0x168) == 0 goto L_0x66e5b5e
    // -> if *(a0+0x168) != 0 goto L_0x66e5b33
    // [open] translate statements for this block
    L_0x66e5b27:;
    __debugbreak(); // [open] NOT LIFTED block 1

    // 0x66e5b33..0x66e5b39: basic block 2
    // 0x66e5b33  lock dec dword ptr [rdi+8]
    // 0x66e5b37  jne short 0x66E5B5E
    // -> if (Dec *u32(*(a0+0x168)+0x8), ?) != 0 goto L_0x66e5b5e
    // -> if (Dec *u32(*(a0+0x168)+0x8), ?) == 0 goto L_0x66e5b39
    // [open] translate statements for this block
    L_0x66e5b33:;
    __debugbreak(); // [open] NOT LIFTED block 2

    // 0x66e5b39..0x66e5b4e: basic block 3
    // 0x66e5b39  mov rax,[rdi]
    // 0x66e5b3c  mov rax,[rax]
    // 0x66e5b3f  mov rcx,rdi
    // 0x66e5b42  call qword ptr [0xF99FFA0]
    // 0x66e5b48  lock dec dword ptr [rdi+0xC]
    // 0x66e5b4c  jne short 0x66E5B5E
    // -> if (Dec *u32(*(a0+0x168)+0xC), ?) != 0 goto L_0x66e5b5e
    // -> if (Dec *u32(*(a0+0x168)+0xC), ?) == 0 goto L_0x66e5b4e
    // [open] translate statements for this block
    L_0x66e5b39:;
    __debugbreak(); // [open] NOT LIFTED block 3

    // 0x66e5b4e..0x66e5b5e: basic block 4
    // 0x66e5b4e  mov rax,[rdi]
    // 0x66e5b51  mov rax,[rax+8]
    // 0x66e5b55  mov rcx,rdi
    // 0x66e5b58  call qword ptr [0xF99FFA0]
    // -> if fallthrough goto L_0x66e5b5e
    // [open] translate statements for this block
    L_0x66e5b4e:;
    __debugbreak(); // [open] NOT LIFTED block 4

    // 0x66e5b5e..0x66e5b6a: basic block 5
    // 0x66e5b5e  mov rbx,[rsi+0x140]
    // 0x66e5b65  test rbx,rbx
    // 0x66e5b68  je short 0x66E5BD4
    // -> if *(a0+0x140) == 0 goto L_0x66e5bd4
    // -> if *(a0+0x140) != 0 goto L_0x66e5b6a
    // [open] translate statements for this block
    L_0x66e5b5e:;
    __debugbreak(); // [open] NOT LIFTED block 5

    // 0x66e5b6a..0x66e5b7a: basic block 6
    // 0x66e5b6a  lea r14,[rsi+0x140]
    // 0x66e5b71  mov r15,[rsi+0x148]
    // 0x66e5b78  jmp short 0x66E5B84
    // -> if jmp goto L_0x66e5b84
    // [open] translate statements for this block
    L_0x66e5b6a:;
    __debugbreak(); // [open] NOT LIFTED block 6

    // 0x66e5b7a..0x66e5b80: basic block 7
    // 0x66e5b7a  nop [rax+rax]
    // -> if fallthrough goto L_0x66e5b80
    // [open] translate statements for this block
    L_0x66e5b7a:;
    __debugbreak(); // [open] NOT LIFTED block 7

    // 0x66e5b80..0x66e5b84: basic block 8
    // 0x66e5b80  add rbx,0x28
    // -> if fallthrough goto L_0x66e5b84
    // [open] translate statements for this block
    L_0x66e5b80:;
    __debugbreak(); // [open] NOT LIFTED block 8

    // 0x66e5b84..0x66e5b89: basic block 9
    // 0x66e5b84  cmp rbx,r15
    // 0x66e5b87  je short 0x66E5BC5
    // -> if ? == *(a0+0x148) goto L_0x66e5bc5
    // -> if ? != *(a0+0x148) goto L_0x66e5b89
    // [open] translate statements for this block
    L_0x66e5b84:;
    __debugbreak(); // [open] NOT LIFTED block 9

    // 0x66e5b89..0x66e5b8f: basic block 10
    // 0x66e5b89  cmp byte ptr [rbx+0x18],2
    // 0x66e5b8d  jne short 0x66E5B80
    // -> if ? != 0x2 goto L_0x66e5b80
    // -> if ? == 0x2 goto L_0x66e5b8f
    // [open] translate statements for this block
    L_0x66e5b89:;
    __debugbreak(); // [open] NOT LIFTED block 10

    // 0x66e5b8f..0x66e5b98: basic block 11
    // 0x66e5b8f  mov rdi,[rbx+8]
    // 0x66e5b93  test rdi,rdi
    // 0x66e5b96  je short 0x66E5B80
    // -> if ? == 0 goto L_0x66e5b80
    // -> if ? != 0 goto L_0x66e5b98
    // [open] translate statements for this block
    L_0x66e5b8f:;
    __debugbreak(); // [open] NOT LIFTED block 11

    // 0x66e5b98..0x66e5b9e: basic block 12
    // 0x66e5b98  lock dec dword ptr [rdi+8]
    // 0x66e5b9c  jne short 0x66E5B80
    // -> if (Dec ?, ?) != 0 goto L_0x66e5b80
    // -> if (Dec ?, ?) == 0 goto L_0x66e5b9e
    // [open] translate statements for this block
    L_0x66e5b98:;
    __debugbreak(); // [open] NOT LIFTED block 12

    // 0x66e5b9e..0x66e5bb3: basic block 13
    // 0x66e5b9e  mov rax,[rdi]
    // 0x66e5ba1  mov rax,[rax]
    // 0x66e5ba4  mov rcx,rdi
    // 0x66e5ba7  call qword ptr [0xF99FFA0]
    // 0x66e5bad  lock dec dword ptr [rdi+0xC]
    // 0x66e5bb1  jne short 0x66E5B80
    // -> if (Dec ?, ?) != 0 goto L_0x66e5b80
    // -> if (Dec ?, ?) == 0 goto L_0x66e5bb3
    // [open] translate statements for this block
    L_0x66e5b9e:;
    __debugbreak(); // [open] NOT LIFTED block 13

    // 0x66e5bb3..0x66e5bc5: basic block 14
    // 0x66e5bb3  mov rax,[rdi]
    // 0x66e5bb6  mov rax,[rax+8]
    // 0x66e5bba  mov rcx,rdi
    // 0x66e5bbd  call qword ptr [0xF99FFA0]
    // 0x66e5bc3  jmp short 0x66E5B80
    // -> if jmp goto L_0x66e5b80
    // [open] translate statements for this block
    L_0x66e5bb3:;
    __debugbreak(); // [open] NOT LIFTED block 14

    // 0x66e5bc5..0x66e5bd4: basic block 15
    // 0x66e5bc5  xorps xmm0,xmm0
    // 0x66e5bc8  movups [r14],xmm0
    // 0x66e5bcc  mov qword ptr [r14+0x10],0
    // -> if fallthrough goto L_0x66e5bd4
    // [open] translate statements for this block
    L_0x66e5bc5:;
    __debugbreak(); // [open] NOT LIFTED block 15

    // 0x66e5bd4..0x66e5bda: basic block 16
    // 0x66e5bd4  cmp byte ptr [rsi+0x48],1
    // 0x66e5bd8  jne short 0x66E5C21
    // -> if *u8(a0+0x48) != 0x1 goto L_0x66e5c21
    // -> if *u8(a0+0x48) == 0x1 goto L_0x66e5bda
    // [open] translate statements for this block
    L_0x66e5bd4:;
    __debugbreak(); // [open] NOT LIFTED block 16

    // 0x66e5bda..0x66e5be6: basic block 17
    // 0x66e5bda  lea rdi,[rsi+8]
    // 0x66e5bde  mov rcx,[rdi]
    // 0x66e5be1  test rcx,rcx
    // 0x66e5be4  je short 0x66E5C21
    // -> if *(a0+0x8) == 0 goto L_0x66e5c21
    // -> if *(a0+0x8) != 0 goto L_0x66e5be6
    // [open] translate statements for this block
    L_0x66e5bda:;
    __debugbreak(); // [open] NOT LIFTED block 17

    // 0x66e5be6..0x66e5bf6: basic block 18
    // 0x66e5be6  mov rdx,[rsi+0x18]
    // 0x66e5bea  sub rdx,rcx
    // 0x66e5bed  cmp rdx,0x1000
    // 0x66e5bf4  jb short 0x66E5C0E
    // -> if (*(a0+0x18) - *(a0+0x8)) <u 0x1000 goto L_0x66e5c0e
    // -> if (*(a0+0x18) - *(a0+0x8)) >=u 0x1000 goto L_0x66e5bf6
    // [open] translate statements for this block
    L_0x66e5be6:;
    __debugbreak(); // [open] NOT LIFTED block 18

    // 0x66e5bf6..0x66e5c07: basic block 19
    // 0x66e5bf6  mov rax,[rcx-8]
    // 0x66e5bfa  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x66e5bfe  sub rcx,rax
    // 0x66e5c01  cmp rcx,0x20
    // 0x66e5c05  jae short 0x66E5C2D
    // -> if (*(a0+0x8)-0x8 - *(*(a0+0x8)-0x8)) >=u 0x20 goto L_0x66e5c2d
    // -> if (*(a0+0x8)-0x8 - *(*(a0+0x8)-0x8)) <u 0x20 goto L_0x66e5c07
    // [open] translate statements for this block
    L_0x66e5bf6:;
    __debugbreak(); // [open] NOT LIFTED block 19

    // 0x66e5c07..0x66e5c0e: basic block 20
    // 0x66e5c07  or rdx,0x27
    // 0x66e5c0b  mov rcx,rax
    // -> if fallthrough goto L_0x66e5c0e
    // [open] translate statements for this block
    L_0x66e5c07:;
    __debugbreak(); // [open] NOT LIFTED block 20

    // 0x66e5c0e..0x66e5c21: basic block 21
    // 0x66e5c0e  call 0xE935700
    // 0x66e5c13  xorps xmm0,xmm0
    // 0x66e5c16  movups [rdi],xmm0
    // 0x66e5c19  mov qword ptr [rdi+0x10],0
    // -> if fallthrough goto L_0x66e5c21
    // [open] translate statements for this block
    L_0x66e5c0e:;
    __debugbreak(); // [open] NOT LIFTED block 21

    // 0x66e5c21..0x66e5c2d: basic block 22
    // 0x66e5c21  add rsp,0x30
    // 0x66e5c25  pop rbx
    // 0x66e5c26  pop rdi
    // 0x66e5c27  pop rsi
    // 0x66e5c28  pop r14
    // 0x66e5c2a  pop r15
    // 0x66e5c2c  ret
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x66e5c21:;
    __debugbreak(); // [open] NOT LIFTED block 22

    // 0x66e5c2d..0x66e5c47: basic block 23
    // 0x66e5c2d  mov qword ptr [rsp+0x20],0
    // 0x66e5c36  xor ecx,ecx
    // 0x66e5c38  xor edx,edx
    // 0x66e5c3a  xor r8d,r8d
    // 0x66e5c3d  xor r9d,r9d
    // 0x66e5c40  call qword ptr [0xF9A8C78]
    // 0x66e5c46  int3
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x66e5c2d:;
    __debugbreak(); // [open] NOT LIFTED block 23

    return 0;   // unreachable; kept so the skeleton compiles until every block is translated
}

} // namespace native::helpers
