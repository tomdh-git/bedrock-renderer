// LIFT 0x2fe330 size 0x10b 1.26.62.01 sub_2fe330
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_2fe330.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_2fe330, "sub_2fe330", 0x2fe330, sub_2fe330, nullptr);

// Verbatim call instructions from the disassembly of [0x2fe330, 0x2fe43b) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x2fe361  call 0x39A7AD0
#endif

// Ranges: every instruction of [0x2fe330, 0x2fe43b) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_2fe330(sub_2fe330_rcx* a0, const sub_2fe330_rdx* a1, std::uint32_t a2,
                     sub_2fe330_r9* a3, std::uint32_t a4, void* a5) {
    // 0x2fe330..0x2fe43b: basic block 0 (single block, no branches)
    // 0x2fe330  push r14
    // 0x2fe332  push rsi
    // 0x2fe333  push rdi
    // 0x2fe334  push rbp
    // 0x2fe335  push rbx
    // 0x2fe336  sub rsp,0x30
    // 0x2fe33a  mov rdi,r9            ; rdi = a3
    // 0x2fe33d  mov ebx,r8d           ; ebx = a2 (truncated to 32 bits)
    // 0x2fe340  mov rsi,rcx           ; rsi = a0
    // 0x2fe343  mov r14,[rsp+0x88]    ; r14 = a5 (6th arg)
    // 0x2fe34b  mov ebp,[rsp+0x80]    ; ebp = a4 (5th arg)
    // 0x2fe352  movups xmm0,[rdx]     ; xmm0 = a1->f0[2]  (16 bytes)
    // 0x2fe355  movaps [rsp+0x20],xmm0 ; stack copy of a1->f0
    // 0x2fe35a  lea rcx,[rsp+0x20]    ; rcx = &stack copy
    // 0x2fe35f  xor edx,edx           ; edx = 0
    // 0x2fe361  call 0x39A7AD0        ; rax = sub_39a7ad0(&stack copy, 0)
    // 0x2fe366  mov rcx,[rdi]         ; rcx = a3->f0
    // 0x2fe369  mov rdx,[rdi+8]       ; rdx = a3->f8
    // 0x2fe36d  mov [rsi],rax         ; a0->f0 = rax
    // 0x2fe370  mov [rsi+8],bl        ; a0->f8 = (uint8_t)a2
    // 0x2fe373  mov [rsi+0x10],rcx    ; a0->f10 = a3->f0
    // 0x2fe377  mov [rsi+0x18],rcx    ; a0->f18 = a3->f0
    // 0x2fe37b  mov [rsi+0x20],rdx    ; a0->f20 = a3->f8
    // 0x2fe37f  mov byte ptr [rsi+0x28],1  ; a0->f28 = 1
    // 0x2fe383  mov [rsi+0x30],ebp    ; a0->f30 = a4
    // 0x2fe386  movups xmm0,[r14]     ; xmm0 = a5->f0[2]
    // 0x2fe38a  movups xmm1,[r14+0x10]; xmm1 = a5->f10[2]
    // 0x2fe38f  movups [rsi+0x38],xmm0 ; a0->f38 = a5->f0
    // 0x2fe393  movups [rsi+0x48],xmm1 ; a0->f48 = a5->f10
    // 0x2fe397  mov dword ptr [rsi+0x58],0  ; a0->f58 = 0
    // 0x2fe39e  xorps xmm0,xmm0       ; xmm0 = 0
    // 0x2fe3a1  movups [rsi+0x68],xmm0  ; a0->f68 = 0
    // 0x2fe3a5  mov byte ptr [rsi+0x88],0  ; a0->f88 = 0
    // 0x2fe3ac  mov dword ptr [rsi+0x90],0  ; a0->f90 = 0
    // 0x2fe3b6  movups [rsi+0xB8],xmm0    ; a0->fb8 = 0
    // 0x2fe3bd  movups [rsi+0xA8],xmm0    ; a0->fa8 = 0
    // 0x2fe3c4  movups [rsi+0x98],xmm0    ; a0->f98 = 0
    // 0x2fe3cb  mov qword ptr [rsi+0xC8],0xF  ; a0->fc8 = 0xF
    // 0x2fe3d6  mov dword ptr [rsi+0xD0],0  ; a0->fd0 = 0
    // 0x2fe3e0  movups [rsi+0xF8],xmm0    ; a0->ff8 = 0
    // 0x2fe3e7  mov qword ptr [rsi+0x108],0 ; a0->f108 = 0
    // 0x2fe3f2  mov byte ptr [rsi+0xF0],0   ; a0->ff0 = 0
    // 0x2fe3f9  lea rax,[0xF1B4480]     ; rax = &"UNSET" (0xF1B4480)
    // 0x2fe400  mov [rsi+0xE0],rax     ; a0->fe0 = &"UNSET"
    // 0x2fe407  mov qword ptr [rsi+0xE8],5  ; a0->fe8 = 5
    // 0x2fe412  mov dword ptr [rsi+0x110],0 ; a0->f110 = 0
    // 0x2fe41c  mov byte ptr [rsi+0x128],0  ; a0->f128 = 0
    // 0x2fe423  mov dword ptr [rsi+0x130],0 ; a0->f130 = 0
    // 0x2fe42d  mov rax,rsi            ; rax = a0
    // 0x2fe430  add rsp,0x30
    // 0x2fe434  pop rbx
    // 0x2fe435  pop rbp
    // 0x2fe436  pop rdi
    // 0x2fe437  pop rsi
    // 0x2fe438  pop r14
    // 0x2fe43a  ret
    // -> (fall-through / ret / end)

    alignas(16) std::uint64_t stack_copy[2];
    stack_copy[0] = a1->f0[0];
    stack_copy[1] = a1->f0[1];

    std::uintptr_t rax = reinterpret_cast<std::uintptr_t>(sub_39a7ad0(stack_copy, 0u));

    a0->f0 = reinterpret_cast<void*>(rax);
    a0->f8 = static_cast<std::uint8_t>(a2);
    a0->f10 = a3->f0;
    a0->f18 = a3->f0;
    a0->f20 = a3->f8;
    a0->f28 = 1;
    a0->f30 = a4;

    const sub_2fe330_r14* r14 = reinterpret_cast<const sub_2fe330_r14*>(a5);
    a0->f38[0] = r14->f0[0];
    a0->f38[1] = r14->f0[1];
    a0->f48[0] = r14->f10[0];
    a0->f48[1] = r14->f10[1];

    a0->f58 = 0;
    a0->f68[0] = 0;
    a0->f68[1] = 0;
    a0->f88 = 0;
    a0->f90 = 0;
    a0->fb8[0] = 0;
    a0->fb8[1] = 0;
    a0->fa8[0] = 0;
    a0->fa8[1] = 0;
    a0->f98[0] = 0;
    a0->f98[1] = 0;
    a0->fc8 = 0xF;
    a0->fd0 = 0;
    a0->ff8[0] = 0;
    a0->ff8[1] = 0;
    a0->f108 = 0;
    a0->ff0 = 0;
    a0->fe0 = reinterpret_cast<void*>(0xF1B4480);  // "UNSET"
    a0->fe8 = 5;
    a0->f110 = 0;
    a0->f128 = 0;
    a0->f130 = 0;

    return reinterpret_cast<std::uintptr_t>(a0);
}

// Layout assertions mirroring the header so the .cpp carries its own static_assert.
static_assert(offsetof(sub_2fe330_rcx, f0) == 0x0, "sub_0x2fe330 rcx+0x0");
static_assert(offsetof(sub_2fe330_rcx, f130) == 0x130, "sub_0x2fe330 rcx+0x130");
static_assert(offsetof(sub_2fe330_rdx, f0) == 0x0, "sub_0x2fe330 rdx+0x0");
static_assert(offsetof(sub_2fe330_r9, f0) == 0x0, "sub_0x2fe330 r9+0x0");
static_assert(offsetof(sub_2fe330_r9, f8) == 0x8, "sub_0x2fe330 r9+0x8");
static_assert(offsetof(sub_2fe330_r14, f0) == 0x0, "sub_0x2fe330 r14+0x0");
static_assert(offsetof(sub_2fe330_r14, f10) == 0x10, "sub_0x2fe330 r14+0x10");
static_assert(offsetof(sub_2fe330_rsp, f20) == 0x20, "sub_0x2fe330 rsp+0x20");
static_assert(offsetof(sub_2fe330_rsp, f80) == 0x80, "sub_0x2fe330 rsp+0x80");
static_assert(offsetof(sub_2fe330_rsp, f88) == 0x88, "sub_0x2fe330 rsp+0x88");

} // namespace native::helpers
