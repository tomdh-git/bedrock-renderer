// LIFT 0x567a7b0 size 0x138 1.26.62.01 sub_567a7b0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_567a7b0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_567a7b0, "sub_567a7b0", 0x567a7b0, sub_567a7b0, nullptr);

// Verbatim call instructions from the disassembly of [0x567a7b0, 0x567a8e8) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x567a7e8  call qword ptr [0xF99FFA0]
0x567a89c  call 0xA4C70
0x567a8c7  call 0xE935700
0x567a8d3  call 0x9BC830
0x567a8e1  call 0xA4EA0
#endif

// Ranges: every instruction of [0x567a7b0, 0x567a8e8) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_567a7b0(void* self) {
    // 0x567a7b0..0x567a7fa: basic block 0
    // 0x567a7b0  push rbp
    // 0x567a7b1  push r15
    // 0x567a7b3  push r14
    // 0x567a7b5  push rsi
    // 0x567a7b6  push rdi
    // 0x567a7b7  push rbx
    // 0x567a7b8  sub rsp,0x48
    // 0x567a7bc  lea rbp,[rsp+0x40]
    // 0x567a7c1  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0x567a7c9  mov rbx,r8
    // 0x567a7cc  mov rsi,rdx
    // 0x567a7cf  mov rdi,rcx
    // 0x567a7d2  mov r14,[rcx]
    // 0x567a7d5  mov rcx,[0x1233E1A8]
    // 0x567a7dc  mov rax,[rcx]
    // 0x567a7df  mov rax,[rax+8]
    // 0x567a7e3  mov edx,0x30
    // 0x567a7e8  call qword ptr [0xF99FFA0]
    // 0x567a7ee  mov r15,rax
    // 0x567a7f1  test rax,rax
    // 0x567a7f4  je 0x567A8CE
    // -> if ret@567a7e8 == 0 goto L_0x567a8ce
    // -> if ret@567a7e8 != 0 goto L_0x567a7fa
    // [open] translate statements for this block
    L_0x567a7b0:;
    __debugbreak(); // [open] NOT LIFTED block 0

    // 0x567a7fa..0x567a82b: basic block 1
    // 0x567a7fa  mov rax,[rbx]
    // 0x567a7fd  mov [r15+0x20],rax
    // 0x567a801  mov ecx,[rbx+8]
    // 0x567a804  mov [r15+0x28],ecx
    // 0x567a808  mov [r15],r14
    // 0x567a80b  mov [r15+8],r14
    // 0x567a80f  mov [r15+0x10],r14
    // 0x567a813  mov word ptr [r15+0x18],0
    // 0x567a81a  mov rcx,[rdi]
    // 0x567a81d  mov r10,[rcx+8]
    // 0x567a821  xor r8d,r8d
    // 0x567a824  cmp byte ptr [r10+0x19],0
    // 0x567a829  je short 0x567A840
    // -> if *u8(*(*(a0)+0x8)+0x19) == 0x0 goto L_0x567a840
    // -> if *u8(*(*(a0)+0x8)+0x19) != 0x0 goto L_0x567a82b
    // [open] translate statements for this block
    L_0x567a7fa:;
    __debugbreak(); // [open] NOT LIFTED block 1

    // 0x567a82b..0x567a834: basic block 2
    // 0x567a82b  mov rdx,r10
    // 0x567a82e  cmp byte ptr [rcx+0x19],0
    // 0x567a832  jne short 0x567A87A
    // -> if *u8(*(a0)+0x19) != 0x0 goto L_0x567a87a
    // -> if *u8(*(a0)+0x19) == 0x0 goto L_0x567a834
    // [open] translate statements for this block
    L_0x567a82b:;
    __debugbreak(); // [open] NOT LIFTED block 2

    // 0x567a834..0x567a836: basic block 3
    // 0x567a834  jmp short 0x567A874
    // -> if jmp goto L_0x567a874
    // [open] translate statements for this block
    L_0x567a834:;
    __debugbreak(); // [open] NOT LIFTED block 3

    // 0x567a836..0x567a840: basic block 4
    // 0x567a836  nop [rax+rax]
    // -> if fallthrough goto L_0x567a840
    // [open] translate statements for this block
    L_0x567a836:;
    __debugbreak(); // [open] NOT LIFTED block 4

    // 0x567a840..0x567a864: basic block 5
    // 0x567a840  mov rdx,r10
    // 0x567a843  mov r9,[r10+0x20]
    // 0x567a847  xor r8d,r8d
    // 0x567a84a  cmp r9,rax
    // 0x567a84d  setb r8b
    // 0x567a851  cmovae rcx,r10
    // 0x567a855  shl r8d,4
    // 0x567a859  mov r10,[r10+r8]
    // 0x567a85d  cmp byte ptr [r10+0x19],0
    // 0x567a862  je short 0x567A840
    // -> if ? == 0x0 goto L_0x567a840
    // -> if ? != 0x0 goto L_0x567a864
    // [open] translate statements for this block
    L_0x567a840:;
    __debugbreak(); // [open] NOT LIFTED block 5

    // 0x567a864..0x567a874: basic block 6
    // 0x567a864  xor r8d,r8d
    // 0x567a867  cmp r9,rax
    // 0x567a86a  setae r8b
    // 0x567a86e  cmp byte ptr [rcx+0x19],0
    // 0x567a872  jne short 0x567A87A
    // -> if ? != 0x0 goto L_0x567a87a
    // -> if ? == 0x0 goto L_0x567a874
    // [open] translate statements for this block
    L_0x567a864:;
    __debugbreak(); // [open] NOT LIFTED block 6

    // 0x567a874..0x567a87a: basic block 7
    // 0x567a874  cmp rax,[rcx+0x20]
    // 0x567a878  jae short 0x567A8B8
    // -> if *(a2) >=u ? goto L_0x567a8b8
    // -> if *(a2) <u ? goto L_0x567a87a
    // [open] translate statements for this block
    L_0x567a874:;
    __debugbreak(); // [open] NOT LIFTED block 7

    // 0x567a87a..0x567a88a: basic block 8
    // 0x567a87a  mov rax,0x555555555555555
    // 0x567a884  cmp [rdi+8],rax
    // 0x567a888  je short 0x567A8DD
    // -> if *(a0+0x8) == 0x555555555555555 goto L_0x567a8dd
    // -> if *(a0+0x8) != 0x555555555555555 goto L_0x567a88a
    // [open] translate statements for this block
    L_0x567a87a:;
    __debugbreak(); // [open] NOT LIFTED block 8

    // 0x567a88a..0x567a8a8: basic block 9
    // 0x567a88a  mov [rbp-0x18],rdx
    // 0x567a88e  mov [rbp-0x10],r8d
    // 0x567a892  lea rdx,[rbp-0x18]
    // 0x567a896  mov rcx,rdi
    // 0x567a899  mov r8,r15
    // 0x567a89c  call 0xA4C70
    // 0x567a8a1  mov [rsi],rax
    // 0x567a8a4  mov byte ptr [rsi+8],1
    // -> if fallthrough goto L_0x567a8a8
    // [open] translate statements for this block
    L_0x567a88a:;
    __debugbreak(); // [open] NOT LIFTED block 9

    // 0x567a8a8..0x567a8b8: basic block 10
    // 0x567a8a8  mov rax,rsi
    // 0x567a8ab  add rsp,0x48
    // 0x567a8af  pop rbx
    // 0x567a8b0  pop rdi
    // 0x567a8b1  pop rsi
    // 0x567a8b2  pop r14
    // 0x567a8b4  pop r15
    // 0x567a8b6  pop rbp
    // 0x567a8b7  ret
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x567a8a8:;
    __debugbreak(); // [open] NOT LIFTED block 10

    // 0x567a8b8..0x567a8ce: basic block 11
    // 0x567a8b8  mov [rsi],rcx
    // 0x567a8bb  mov byte ptr [rsi+8],0
    // 0x567a8bf  mov edx,0x30
    // 0x567a8c4  mov rcx,r15
    // 0x567a8c7  call 0xE935700
    // 0x567a8cc  jmp short 0x567A8A8
    // -> if jmp goto L_0x567a8a8
    // [open] translate statements for this block
    L_0x567a8b8:;
    __debugbreak(); // [open] NOT LIFTED block 11

    // 0x567a8ce..0x567a8dd: basic block 12
    // 0x567a8ce  mov ecx,0x30
    // 0x567a8d3  call 0x9BC830
    // 0x567a8d8  jmp 0x567A7FA
    // -> if jmp goto L_0x567a7fa
    // [open] translate statements for this block
    L_0x567a8ce:;
    __debugbreak(); // [open] NOT LIFTED block 12

    // 0x567a8dd..0x567a8e8: basic block 13
    // 0x567a8dd  mov [rbp-8],r15
    // 0x567a8e1  call 0xA4EA0
    // 0x567a8e6  nop
    // 0x567a8e7  int3
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x567a8dd:;
    __debugbreak(); // [open] NOT LIFTED block 13

    return 0;   // unreachable; kept so the skeleton compiles until every block is translated
}

} // namespace native::helpers
