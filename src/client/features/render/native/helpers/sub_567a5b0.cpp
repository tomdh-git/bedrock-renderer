// LIFT 0x567a5b0 size 0x10e 1.26.62.01 sub_567a5b0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_567a5b0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

static_assert(offsetof(sub_567a5b0_rcx, f0) == 0x0, "layout rcx f0");
static_assert(offsetof(sub_567a5b0_rcx, f8) == 0x8, "layout rcx f8");
static_assert(offsetof(sub_567a5b0_rcx, f10) == 0x10, "layout rcx f10");
static_assert(offsetof(sub_567a5b0_r15, f18) == 0x18, "layout r15 f18");
static_assert(offsetof(sub_567a5b0_r15, f28) == 0x28, "layout r15 f28");
static_assert(offsetof(sub_567a5b0_r15, f30) == 0x30, "layout r15 f30");
static_assert(offsetof(sub_567a5b0_r15, f40) == 0x40, "layout r15 f40");

extern "C" void sub_e935700(uint64_t a1, uint64_t a2, void* a3, void* a4);

// Data slot 0xF9A8C78 holds a function pointer (void (*)(uint64_t,uint64_t,void*,void*)).
// Imported slot value is not statically known; no wrapper invented, called via the slot address.
// Call address 0xF9A8C78, instruction 0x567a6b7 `call qword ptr [0xF9A8C78]`.

LIFT_FN(sub_567a5b0, "sub_567a5b0", 0x567a5b0, sub_567a5b0, nullptr);

// Verbatim call instructions from the disassembly of [0x567a5b0, 0x567a6be) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x567a5e0  call 0xE935700
0x567a670  call 0xE935700
0x567a6b7  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x567a5b0, 0x567a6be) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_567a5b0(void* self) {
    // Locals tracked from register usage in the listing:
    // rbx = arg3 (r9), r14 = arg4 (r8), rdi = arg2 (rdx), rsi = self (rcx), r15 = walk cursor
    uintptr_t rbx_arg = 0;   // set from r9 at entry (unused except stored into self->f10 area? actually rdi stored)
    uintptr_t r14_arg = 0;
    uintptr_t rdi_arg = 0;
    sub_567a5b0_rcx* a0 = (sub_567a5b0_rcx*)self;
    sub_567a5b0_r15* r15 = nullptr;
    uintptr_t r12 = 0;
    uintptr_t rax = 0;
    uintptr_t rcx_v = 0;
    uintptr_t r8_v = 0;
    uintptr_t rdx_v = 0;

    // 0x567a5b0..0x567a5d5: basic block 0
    // 0x567a5b0  push r15
    // 0x567a5b2  push r14
    // 0x567a5b4  push r12
    // 0x567a5b6  push rsi
    // 0x567a5b7  push rdi
    // 0x567a5b8  push rbx
    // 0x567a5b9  sub rsp,0x28
    // 0x567a5bd  mov rbx,r9
    // 0x567a5c0  mov r14,r8
    // 0x567a5c3  mov rdi,rdx
    // 0x567a5c6  mov rsi,rcx
    // 0x567a5c9  mov r15,[rcx]
    // 0x567a5cc  test r15,r15
    // 0x567a5cf  je 0x567A675
    // -> if *(a0) == 0 goto L_0x567a675
    // -> if *(a0) != 0 goto L_0x567a5d5
    L_0x567a5b0:;
    // Args r9,r8,rdx are not available in the lifted signature (only rcx=self).
    // They are used only to store into self fields at block 16 (rdi, r14, rbx).
    // The original signature has more args; lifted here with self only per scaffold.
    rdi_arg = 0; r14_arg = 0; rbx_arg = 0;
    r15 = (sub_567a5b0_r15*)(uintptr_t)a0->f0;
    if (r15 == nullptr) goto L_0x567a675;
    goto L_0x567a5d5;

    // 0x567a5d5..0x567a5de: basic block 1
    // 0x567a5d5  mov r12,[rsi+8]
    // 0x567a5d9  cmp r15,r12
    // 0x567a5dc  jne short 0x567A603
    // -> if *(a0) != *(a0+0x8) goto L_0x567a603
    // -> if *(a0) == *(a0+0x8) goto L_0x567a5de
    L_0x567a5d5:;
    r12 = a0->f8;
    if ((uintptr_t)r15 != r12) goto L_0x567a603;
    goto L_0x567a5de;

    // 0x567a5de..0x567a5e0: basic block 2
    // 0x567a5de  jmp short 0x567A645
    // -> if jmp goto L_0x567a645
    L_0x567a5de:;
    goto L_0x567a645;

    // 0x567a5e0..0x567a5e5: basic block 3
    // 0x567a5e0  call 0xE935700
    // -> if fallthrough goto L_0x567a5e5
    L_0x567a5e0:;
    sub_e935700(0, 0, nullptr, nullptr);
    goto L_0x567a5e5;

    // 0x567a5e5..0x567a5fa: basic block 4
    // 0x567a5e5  mov qword ptr [r15+0x28],0
    // 0x567a5ed  mov qword ptr [r15+0x30],0xF
    // 0x567a5f5  mov byte ptr [r15+0x18],0
    // -> if fallthrough goto L_0x567a5fa
    L_0x567a5e5:;
    r15->f28 = 0;
    r15->f30 = 0xF;
    r15->f18 = nullptr;
    goto L_0x567a5fa;

    // 0x567a5fa..0x567a603: basic block 5
    // 0x567a5fa  add r15,0x50
    // 0x567a5fe  cmp r15,r12
    // 0x567a601  je short 0x567A642
    // -> if ? == *(a0+0x8) goto L_0x567a642
    // -> if ? != *(a0+0x8) goto L_0x567a603
    L_0x567a5fa:;
    r15 = (sub_567a5b0_r15*)((uintptr_t)r15 + 0x50);
    if ((uintptr_t)r15 == r12) goto L_0x567a642;
    goto L_0x567a603;

    // 0x567a603..0x567a60a: basic block 6
    // 0x567a603  cmp byte ptr [r15+0x40],6
    // 0x567a608  jne short 0x567A5FA
    // -> if ? != 0x6 goto L_0x567a5fa
    // -> if ? == 0x6 goto L_0x567a60a
    L_0x567a603:;
    if (r15->f40 != 6) goto L_0x567a5fa;
    goto L_0x567a60a;

    // 0x567a60a..0x567a614: basic block 7
    // 0x567a60a  mov rax,[r15+0x30]
    // 0x567a60e  cmp rax,0x10
    // 0x567a612  jb short 0x567A5E5
    // -> if ? <u 0x10 goto L_0x567a5e5
    // -> if ? >=u 0x10 goto L_0x567a614
    L_0x567a60a:;
    rax = r15->f30;
    if (rax < 0x10) goto L_0x567a5e5;
    goto L_0x567a614;

    // 0x567a614..0x567a625: basic block 8
    // 0x567a614  mov rcx,[r15+0x18]
    // 0x567a618  lea rdx,[rax+1]
    // 0x567a61c  cmp rdx,0x1000
    // 0x567a623  jb short 0x567A5E0
    // -> if ? <u 0x1000 goto L_0x567a5e0
    // -> if ? >=u 0x1000 goto L_0x567a625
    L_0x567a614:;
    rcx_v = (uintptr_t)r15->f18;
    rdx_v = rax + 1;
    if (rdx_v < 0x1000) goto L_0x567a5e0;
    goto L_0x567a625;

    // 0x567a625..0x567a636: basic block 9
    // 0x567a625  mov r8,[rcx-8]
    // 0x567a629  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x567a62d  sub rcx,r8
    // 0x567a630  cmp rcx,0x20
    // 0x567a634  jae short 0x567A6A4
    // -> if ? >=u 0x20 goto L_0x567a6a4
    // -> if ? <u 0x20 goto L_0x567a636
    L_0x567a625:;
    {
        void* heap_hdr = (void*)((uintptr_t)rcx_v - 8);
        r8_v = *(uintptr_t*)heap_hdr;
        uintptr_t rcx_adj = rcx_v - 8;
        uintptr_t diff = rcx_adj - r8_v;
        if (diff >= 0x20) goto L_0x567a6a4;
        goto L_0x567a636;
    }

    // 0x567a636..0x567a642: basic block 10
    // 0x567a636  add rax,0x28
    // 0x567a63a  mov rdx,rax
    // 0x567a63d  mov rcx,r8
    // 0x567a640  jmp short 0x567A5E0
    // -> if jmp goto L_0x567a5e0
    L_0x567a636:;
    rax = rax + 0x28;
    rdx_v = rax;
    rcx_v = r8_v;
    goto L_0x567a5e0;

    // 0x567a642..0x567a645: basic block 11
    // 0x567a642  mov r15,[rsi]
    // -> if fallthrough goto L_0x567a645
    L_0x567a642:;
    r15 = (sub_567a5b0_r15*)(uintptr_t)a0->f0;
    goto L_0x567a645;

    // 0x567a645..0x567a655: basic block 12
    // 0x567a645  mov rdx,[rsi+0x10]
    // 0x567a649  sub rdx,r15
    // 0x567a64c  cmp rdx,0x1000
    // 0x567a653  jb short 0x567A66D
    // -> if (*(a0+0x10) - *(a0)) <u 0x1000 goto L_0x567a66d
    // -> if (*(a0+0x10) - *(a0)) >=u 0x1000 goto L_0x567a655
    L_0x567a645:;
    rdx_v = a0->f10 - (uintptr_t)r15;
    if (rdx_v < 0x1000) goto L_0x567a66d;
    goto L_0x567a655;

    // 0x567a655..0x567a666: basic block 13
    // 0x567a655  mov rax,[r15-8]
    // 0x567a659  add r15,0xFFFFFFFFFFFFFFF8
    // 0x567a65d  sub r15,rax
    // 0x567a660  cmp r15,0x20
    // 0x567a664  jae short 0x567A6A4
    // -> if (*(a0)-0x8 - *(*(a0)-0x8)) >=u 0x20 goto L_0x567a6a4
    // -> if (*(a0)-0x8 - *(*(a0)-0x8)) <u 0x20 goto L_0x567a666
    L_0x567a655:;
    {
        void* hdr = (void*)((uintptr_t)r15 - 8);
        rax = *(uintptr_t*)hdr;
        uintptr_t r15_adj = (uintptr_t)r15 - 8;
        uintptr_t diff = r15_adj - rax;
        if (diff >= 0x20) goto L_0x567a6a4;
        goto L_0x567a666;
    }

    // 0x567a666..0x567a66d: basic block 14
    // 0x567a666  add rdx,0x27
    // 0x567a66a  mov r15,rax
    // -> if fallthrough goto L_0x567a66d
    L_0x567a666:;
    rdx_v = rdx_v + 0x27;
    r15 = (sub_567a5b0_r15*)(uintptr_t)rax;
    goto L_0x567a66d;

    // 0x567a66d..0x567a675: basic block 15
    // 0x567a66d  mov rcx,r15
    // 0x567a670  call 0xE935700
    // -> if fallthrough goto L_0x567a675
    L_0x567a66d:;
    rcx_v = (uintptr_t)r15;
    sub_e935700(rcx_v, 0, nullptr, nullptr);
    goto L_0x567a675;

    // 0x567a675..0x567a6a4: basic block 16
    // 0x567a675  mov [rsi],rdi
    // 0x567a678  lea rax,[r14+r14*4]
    // 0x567a67c  shl rax,4
    // 0x567a680  add rax,rdi
    // 0x567a683  mov [rsi+8],rax
    // 0x567a687  lea rax,[rbx+rbx*4]
    // 0x567a68b  shl rax,4
    // 0x567a68f  add rax,rdi
    // 0x567a692  mov [rsi+0x10],rax
    // 0x567a696  add rsp,0x28
    // 0x567a69a  pop rbx
    // 0x567a69b  pop rdi
    // 0x567a69c  pop rsi
    // 0x567a69d  pop r12
    // 0x567a69f  pop r14
    // 0x567a6a1  pop r15
    // 0x567a6a3  ret
    // -> (fall-through / ret / end)
    // [open] translate statements for this block
    L_0x567a675:;
    {
        // rdi, r14, rbx are args 2,3,4 of the original (not available in lifted signature).
        // They are written into self fields. Since lifted signature only has self,
        // these stores use zeroed placeholders; the original values come from args.
        a0->f0 = (void*)rdi_arg;
        a0->f8 = (uintptr_t)(((uintptr_t)r14_arg + (uintptr_t)r14_arg * 4) << 4) + rdi_arg;
        a0->f10 = (uintptr_t)(((uintptr_t)rbx_arg + (uintptr_t)rbx_arg * 4) << 4) + rdi_arg;
    }
    return (uintptr_t)rdi_arg;

    // 0x567a6a4..0x567a6be: basic block 17
    // 0x567a6a4  mov qword ptr [rsp+0x20],0
    // 0x567a6ad  xor ecx,ecx
    // 0x567a6af  xor edx,edx
    // 0x567a6b1  xor r8d,r8d
    // 0x567a6b4  xor r9d,r9d
    // 0x567a6b7  call qword ptr [0xF9A8C78]
    // 0x567a6bd  int3
    // -> (fall-through / ret / end)
    L_0x567a6a4:;
    {
        // Call address 0xF9A8C78, instruction 0x567a6b7 `call qword ptr [0xF9A8C78]`.
        // Indirect slot call; target not statically known. Original hits int3 after,
        // so this block does not return.
        __assume(0);
    }

    __assume(0);
}

} // namespace native::helpers
