// LIFT 0xc2981f0 size 0x130 1.26.62.01 sub_c2981f0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c2981f0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_c2981f0, "sub_c2981f0", 0xc2981f0, sub_c2981f0, nullptr);

// Verbatim call instructions from the disassembly of [0xc2981f0, 0xc298320) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
#endif

// Ranges: every instruction of [0xc2981f0, 0xc298320) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_c2981f0(void* self) {
    // 0xc2981f0..0xc298217: basic block 0
    // 0xc2981f0  push r15
    // 0xc2981f2  push r14
    // 0xc2981f4  push r12
    // 0xc2981f6  push rsi
    // 0xc2981f7  push rdi
    // 0xc2981f8  push rbx
    // 0xc2981f9  mov rax,rdx
    // 0xc2981fc  mov r9,[rcx+0x30]
    // 0xc298200  mov rdx,[rcx+0x38]
    // 0xc298204  mov r11,rdx
    // 0xc298207  sub r11,r9
    // 0xc29820a  sar r11,3
    // 0xc29820e  test r11,r11
    // 0xc298211  jle 0xC298308
    // -> if ((*(a0+0x38) - *(a0+0x30)) >>s 0x3) <=s 0 goto L_0xc298308
    // -> if ((*(a0+0x38) - *(a0+0x30)) >>s 0x3) >s 0 goto L_0xc298217
    // [open] translate statements for this block
    L_0xc2981f0:;
    __debugbreak(); // [open] NOT LIFTED block 0

    // 0xc298217..0xc298222: basic block 1
    // 0xc298217  mov r8,[r8]
    // 0xc29821a  mov r10,r9
    // 0xc29821d  mov rdi,r11
    // 0xc298220  jmp short 0xC298249
    // -> if jmp goto L_0xc298249
    // [open] translate statements for this block
    L_0xc298217:;
    __debugbreak(); // [open] NOT LIFTED block 1

    // 0xc298222..0xc298230: basic block 2
    // 0xc298222  nop [rax+rax]
    // -> if fallthrough goto L_0xc298230
    // [open] translate statements for this block
    L_0xc298222:;
    __debugbreak(); // [open] NOT LIFTED block 2

    // 0xc298230..0xc29823d: basic block 3
    // 0xc298230  add rsi,8
    // 0xc298234  not rdi
    // 0xc298237  add rdi,r11
    // 0xc29823a  mov r10,rsi
    // -> if fallthrough goto L_0xc29823d
    // [open] translate statements for this block
    L_0xc298230:;
    __debugbreak(); // [open] NOT LIFTED block 3

    // 0xc29823d..0xc298249: basic block 4
    // 0xc29823d  mov r11,rdi
    // 0xc298240  test rdi,rdi
    // 0xc298243  jle 0xC298308
    // -> if ? <=s 0 goto L_0xc298308
    // -> if ? >s 0 goto L_0xc298249
    // [open] translate statements for this block
    L_0xc29823d:;
    __debugbreak(); // [open] NOT LIFTED block 4

    // 0xc298249..0xc298259: basic block 5
    // 0xc298249  shr rdi,1
    // 0xc29824c  lea rsi,[r10+rdi*8]
    // 0xc298250  mov rbx,[r10+rdi*8]
    // 0xc298254  cmp rbx,r8
    // 0xc298257  jb short 0xC298230
    // -> if ? <u *(a2) goto L_0xc298230
    // -> if ? >=u *(a2) goto L_0xc298259
    // [open] translate statements for this block
    L_0xc298249:;
    __debugbreak(); // [open] NOT LIFTED block 5

    // 0xc298259..0xc29825b: basic block 6
    // 0xc298259  ja short 0xC29823D
    // -> if ? >u *(a2) goto L_0xc29823d
    // -> if ? <=u *(a2) goto L_0xc29825b
    // [open] translate statements for this block
    L_0xc298259:;
    __debugbreak(); // [open] NOT LIFTED block 6

    // 0xc29825b..0xc298268: basic block 7
    // 0xc29825b  lea rbx,[rdi*8]
    // 0xc298263  test rdi,rdi
    // 0xc298266  je short 0xC29829B
    // -> if ? == 0 goto L_0xc29829b
    // -> if ? != 0 goto L_0xc298268
    // [open] translate statements for this block
    L_0xc29825b:;
    __debugbreak(); // [open] NOT LIFTED block 7

    // 0xc298268..0xc298270: basic block 8
    // 0xc298268  nop [rax+rax]
    // -> if fallthrough goto L_0xc298270
    // [open] translate statements for this block
    L_0xc298268:;
    __debugbreak(); // [open] NOT LIFTED block 8

    // 0xc298270..0xc29829b: basic block 9
    // 0xc298270  mov r14,r10
    // 0xc298273  mov r15,rdi
    // 0xc298276  shr r15,1
    // 0xc298279  mov r12,r15
    // 0xc29827c  not r12
    // 0xc29827f  add r12,rdi
    // 0xc298282  cmp [r10+r15*8],r8
    // 0xc298286  lea r10,[r10+r15*8+8]
    // 0xc29828b  cmovae r10,r14
    // 0xc29828f  cmovae r12,r15
    // 0xc298293  mov rdi,r12
    // 0xc298296  test r12,r12
    // 0xc298299  jg short 0xC298270
    // -> if ? >s 0 goto L_0xc298270
    // -> if ? <=s 0 goto L_0xc29829b
    // [open] translate statements for this block
    L_0xc298270:;
    __debugbreak(); // [open] NOT LIFTED block 9

    // 0xc29829b..0xc2982b3: basic block 10
    // 0xc29829b  shl r11,3
    // 0xc29829f  sub r11,rbx
    // 0xc2982a2  add rsi,8
    // 0xc2982a6  add r11,0xFFFFFFFFFFFFFFF8
    // 0xc2982aa  sar r11,3
    // 0xc2982ae  test r11,r11
    // 0xc2982b1  jle short 0xC2982EB
    // -> if ? <=s 0 goto L_0xc2982eb
    // -> if ? >s 0 goto L_0xc2982b3
    // [open] translate statements for this block
    L_0xc29829b:;
    __debugbreak(); // [open] NOT LIFTED block 10

    // 0xc2982b3..0xc2982c0: basic block 11
    // 0xc2982b3  nop [rax+rax]
    // -> if fallthrough goto L_0xc2982c0
    // [open] translate statements for this block
    L_0xc2982b3:;
    __debugbreak(); // [open] NOT LIFTED block 11

    // 0xc2982c0..0xc2982eb: basic block 12
    // 0xc2982c0  mov rdi,rsi
    // 0xc2982c3  mov rbx,r11
    // 0xc2982c6  shr rbx,1
    // 0xc2982c9  mov r14,rbx
    // 0xc2982cc  not r14
    // 0xc2982cf  add r14,r11
    // 0xc2982d2  cmp r8,[rsi+rbx*8]
    // 0xc2982d6  lea rsi,[rsi+rbx*8+8]
    // 0xc2982db  cmovb rsi,rdi
    // 0xc2982df  cmovb r14,rbx
    // 0xc2982e3  mov r11,r14
    // 0xc2982e6  test r14,r14
    // 0xc2982e9  jg short 0xC2982C0
    // -> if ? >s 0 goto L_0xc2982c0
    // -> if ? <=s 0 goto L_0xc2982eb
    // [open] translate statements for this block
    L_0xc2982c0:;
    __debugbreak(); // [open] NOT LIFTED block 12

    // 0xc2982eb..0xc2982f0: basic block 13
    // 0xc2982eb  cmp r10,rsi
    // 0xc2982ee  je short 0xC298308
    // -> if ? == ? goto L_0xc298308
    // -> if ? != ? goto L_0xc2982f0
    // [open] translate statements for this block
    L_0xc2982eb:;
    __debugbreak(); // [open] NOT LIFTED block 13

    // 0xc2982f0..0xc298302: basic block 14
    // 0xc2982f0  mov r8,r10
    // 0xc2982f3  sub r8,r9
    // 0xc2982f6  sar r8,1
    // 0xc2982f9  add r8,[rcx+0x48]
    // 0xc2982fd  cmp r10,rdx
    // 0xc298300  jne short 0xC298317
    // -> if ? != *(a0+0x38) goto L_0xc298317
    // -> if ? == *(a0+0x38) goto L_0xc298302
    // [open] translate statements for this block
    L_0xc2982f0:;
    __debugbreak(); // [open] NOT LIFTED block 14

    // 0xc298302..0xc298308: basic block 15
    // 0xc298302  cmp r8,[rcx+0x50]
    // 0xc298306  jne short 0xC298317
    // -> if ? != *(a0+0x50) goto L_0xc298317
    // -> if ? == *(a0+0x50) goto L_0xc298308
    // [open] translate statements for this block
    L_0xc298302:;
    __debugbreak(); // [open] NOT LIFTED block 15

    // 0xc298308..0xc29830a: basic block 16
    // 0xc298308  xor ecx,ecx
    // -> if fallthrough goto L_0xc29830a
    // [open] translate statements for this block
    L_0xc298308:;
    __debugbreak(); // [open] NOT LIFTED block 16

    // 0xc29830a..0xc298317: basic block 17
    // 0xc29830a  mov [rax+4],cl
    // 0xc29830d  pop rbx
    // 0xc29830e  pop rdi
    // 0xc29830f  pop rsi
    // 0xc298310  pop r12
    // 0xc298312  pop r14
    // 0xc298314  pop r15
    // 0xc298316  ret
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0xc29830a:;
    __debugbreak(); // [open] NOT LIFTED block 17

    // 0xc298317..0xc298320: basic block 18
    // 0xc298317  mov ecx,[r8]
    // 0xc29831a  mov [rax],ecx
    // 0xc29831c  mov cl,1
    // 0xc29831e  jmp short 0xC29830A
    // -> if jmp goto L_0xc29830a
    // [open] translate statements for this block
    L_0xc298317:;
    __debugbreak(); // [open] NOT LIFTED block 18

    return 0;   // unreachable; kept so the skeleton compiles until every block is translated
}

} // namespace native::helpers
