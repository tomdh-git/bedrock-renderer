// LIFT 0x3165620 size 0x137 1.26.62.01 sub_3165620
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_3165620.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_3165620, "sub_3165620", 0x3165620, sub_3165620, nullptr);

// Verbatim call instructions from the disassembly of [0x3165620, 0x3165757) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x316565f  call 0x9B8D610
0x31656a9  call 0x9B8D610
0x31656d0  call 0xE938CB0
0x3165700  call 0xE938D70
0x316571a  call 0xE938CB0
0x316574a  call 0xE938D70
#endif

// Ranges: every instruction of [0x3165620, 0x3165757) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_3165620(void* self) {
    // 0x3165620..0x316564e: basic block 0
    // 0x3165620  push rsi
    // 0x3165621  push rdi
    // 0x3165622  sub rsp,0x28
    // 0x3165626  mov rsi,rcx
    // 0x3165629  add rcx,8
    // 0x316562d  mov eax,[0x1294A594]
    // 0x3165633  mov edx,[0x128767C8]
    // 0x3165639  mov r8,gs:[0x58]
    // 0x3165642  mov rdx,[r8+rdx*8]
    // 0x3165646  cmp eax,[rdx+4]
    // 0x316564c  jg short 0x31656C3
    // -> if *u32(&data_1294a594) >s *u32(*((*(gs(0x0)+0x58) + (*u32(&data_128767c8) * 0x8)))+0x4) goto L_0x31656c3
    // -> if *u32(&data_1294a594) <=s *u32(*((*(gs(0x0)+0x58) + (*u32(&data_128767c8) * 0x8)))+0x4) goto L_0x316564e
    // [open] translate statements for this block
    L_0x3165620:;
    __debugbreak(); // [open] NOT LIFTED block 0

    // 0x316564e..0x3165669: basic block 1
    // 0x316564e  movzx eax,word ptr [0x1294A590]
    // 0x3165655  mov [rsp+0x24],ax
    // 0x316565a  lea rdx,[rsp+0x24]
    // 0x316565f  call 0x9B8D610
    // 0x3165664  test rax,rax
    // 0x3165667  je short 0x316566F
    // -> if ret@316565f == 0 goto L_0x316566f
    // -> if ret@316565f != 0 goto L_0x3165669
    // [open] translate statements for this block
    L_0x316564e:;
    __debugbreak(); // [open] NOT LIFTED block 1

    // 0x3165669..0x316566f: basic block 2
    // 0x3165669  add rax,8
    // 0x316566d  jmp short 0x31656BC
    // -> if jmp goto L_0x31656bc
    // [open] translate statements for this block
    L_0x3165669:;
    __debugbreak(); // [open] NOT LIFTED block 2

    // 0x316566f..0x3165698: basic block 3
    // 0x316566f  mov rcx,[rsi+0x68]
    // 0x3165673  add rcx,0x30
    // 0x3165677  mov eax,[0x1294A594]
    // 0x316567d  mov edx,[0x128767C8]
    // 0x3165683  mov r8,gs:[0x58]
    // 0x316568c  mov rdx,[r8+rdx*8]
    // 0x3165690  cmp eax,[rdx+4]
    // 0x3165696  jg short 0x316570D
    // -> if *u32(&data_1294a594) >s *u32(*((*(gs(0x0)+0x58) + (*u32(&data_128767c8) * 0x8)))+0x4) goto L_0x316570d
    // -> if *u32(&data_1294a594) <=s *u32(*((*(gs(0x0)+0x58) + (*u32(&data_128767c8) * 0x8)))+0x4) goto L_0x3165698
    // [open] translate statements for this block
    L_0x316566f:;
    __debugbreak(); // [open] NOT LIFTED block 3

    // 0x3165698..0x31656bc: basic block 4
    // 0x3165698  movzx eax,word ptr [0x1294A590]
    // 0x316569f  mov [rsp+0x26],ax
    // 0x31656a4  lea rdx,[rsp+0x26]
    // 0x31656a9  call 0x9B8D610
    // 0x31656ae  mov rcx,rax
    // 0x31656b1  add rax,8
    // 0x31656b5  test rcx,rcx
    // 0x31656b8  cmove rax,rcx
    // -> if fallthrough goto L_0x31656bc
    // [open] translate statements for this block
    L_0x3165698:;
    __debugbreak(); // [open] NOT LIFTED block 4

    // 0x31656bc..0x31656c3: basic block 5
    // 0x31656bc  add rsp,0x28
    // 0x31656c0  pop rdi
    // 0x31656c1  pop rsi
    // 0x31656c2  ret
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x31656bc:;
    __debugbreak(); // [open] NOT LIFTED block 5

    // 0x31656c3..0x31656e5: basic block 6
    // 0x31656c3  lea rax,[0x1294A594]
    // 0x31656ca  mov rdi,rcx
    // 0x31656cd  mov rcx,rax
    // 0x31656d0  call 0xE938CB0
    // 0x31656d5  mov rcx,rdi
    // 0x31656d8  cmp dword ptr [0x1294A594],0xFFFFFFFF
    // 0x31656df  jne 0x316564E
    // -> if *u32(&data_1294a594) != -0x1 goto L_0x316564e
    // -> if *u32(&data_1294a594) == -0x1 goto L_0x31656e5
    // [open] translate statements for this block
    L_0x31656c3:;
    __debugbreak(); // [open] NOT LIFTED block 6

    // 0x31656e5..0x316570d: basic block 7
    // 0x31656e5  mov ax,1
    // 0x31656e9  lock xadd [0x128E97DC],ax
    // 0x31656f2  mov [0x1294A590],ax
    // 0x31656f9  lea rcx,[0x1294A594]
    // 0x3165700  call 0xE938D70
    // 0x3165705  mov rcx,rdi
    // 0x3165708  jmp 0x316564E
    // -> if jmp goto L_0x316564e
    // [open] translate statements for this block
    L_0x31656e5:;
    __debugbreak(); // [open] NOT LIFTED block 7

    // 0x316570d..0x316572f: basic block 8
    // 0x316570d  lea rax,[0x1294A594]
    // 0x3165714  mov rsi,rcx
    // 0x3165717  mov rcx,rax
    // 0x316571a  call 0xE938CB0
    // 0x316571f  mov rcx,rsi
    // 0x3165722  cmp dword ptr [0x1294A594],0xFFFFFFFF
    // 0x3165729  jne 0x3165698
    // -> if *u32(&data_1294a594) != -0x1 goto L_0x3165698
    // -> if *u32(&data_1294a594) == -0x1 goto L_0x316572f
    // [open] translate statements for this block
    L_0x316570d:;
    __debugbreak(); // [open] NOT LIFTED block 8

    // 0x316572f..0x3165757: basic block 9
    // 0x316572f  mov ax,1
    // 0x3165733  lock xadd [0x128E97DC],ax
    // 0x316573c  mov [0x1294A590],ax
    // 0x3165743  lea rcx,[0x1294A594]
    // 0x316574a  call 0xE938D70
    // 0x316574f  mov rcx,rsi
    // 0x3165752  jmp 0x3165698
    // -> if jmp goto L_0x3165698
    // [open] translate statements for this block
    L_0x316572f:;
    __debugbreak(); // [open] NOT LIFTED block 9

    return 0;   // unreachable; kept so the skeleton compiles until every block is translated
}

} // namespace native::helpers
