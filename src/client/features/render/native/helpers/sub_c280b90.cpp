// LIFT 0xc280b90 size 0x10f 1.26.62.01 sub_c280b90
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c280b90.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_c280b90, "sub_c280b90", 0xc280b90, sub_c280b90, nullptr);

// Verbatim call instructions from the disassembly of [0xc280b90, 0xc280c9f) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xc280bf2  call qword ptr [0xF99FFA0]
0xc280c09  call qword ptr [0xF99FFA0]
0xc280c3f  call 0xE935700
0xc280c98  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0xc280b90, 0xc280c9f) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

extern "C" void sub_e935700(uint64_t arg0, uint64_t arg1, void* arg2, void* arg3);

static_assert(offsetof(sub_c280b90_rcx, f0) == 0x0, "layout rcx+0x0");
static_assert(offsetof(sub_c280b90_rcx, f10) == 0x10, "layout rcx+0x10");
static_assert(offsetof(sub_c280b90_r14, f0) == 0x0, "layout r14+0x0");
static_assert(offsetof(sub_c280b90_r14, f8) == 0x8, "layout r14+0x8");
static_assert(offsetof(sub_c280b90_r14, fc) == 0xc, "layout r14+0xc");
static_assert(offsetof(sub_c280b90_rbx, f10) == 0x10, "layout rbx+0x10");
static_assert(offsetof(sub_c280b90_rsp, f20) == 0x20, "layout rsp+0x20");

uintptr_t sub_c280b90(void* a0, void* a1) {
    // Scratch mirror for rsp+0x20 spill slot (block 17).
    sub_c280b90_rsp rsp_state{};

    // All variables declared up front so C goto between labels does not skip initialization.
    sub_c280b90_rcx* rsi = nullptr;
    sub_c280b90_rdx* rdi = nullptr;
    sub_c280b90_rbx* rbx = nullptr;
    sub_c280b90_r14* r14 = nullptr;
    uintptr_t r15 = 0;
    uintptr_t rdx = 0;
    uintptr_t rax = 0;

    // 0xc280b90..0xc280ba7: basic block 0
    // 0xc280b90  push r15
    // 0xc280b92  push r14
    // 0xc280b94  push rsi
    // 0xc280b95  push rdi
    // 0xc280b96  push rbx
    // 0xc280b97  sub rsp,0x30
    // 0xc280b9b  mov rsi,rcx
    // 0xc280b9e  cmp rcx,rdx
    // 0xc280ba1  je 0xC280C76
    // -> if a0 == a1 goto L_0xc280c76
    // -> if a0 != a1 goto L_0xc280ba7
    rsi = static_cast<sub_c280b90_rcx*>(a0);
    rdi = static_cast<sub_c280b90_rdx*>(a1);
    if (a0 == a1) goto L_0xc280c76;

    // 0xc280ba7..0xc280bb6: basic block 1
    // 0xc280ba7  mov rdi,rdx
    // 0xc280baa  mov rbx,[rsi]
    // 0xc280bad  test rbx,rbx
    // 0xc280bb0  je 0xC280C52
    // -> if *(a0) == 0 goto L_0xc280c52
    // -> if *(a0) != 0 goto L_0xc280bb6
    L_0xc280ba7:;
    rbx = reinterpret_cast<sub_c280b90_rbx*>(rsi->f0[0]);
    if (rbx == nullptr) goto L_0xc280c52;

    // 0xc280bb6..0xc280bbf: basic block 2
    // 0xc280bb6  mov r15,[rsi+8]
    // 0xc280bba  cmp rbx,r15
    // 0xc280bbd  jne short 0xC280BD9
    // -> if *(a0) != *(a0+0x8) goto L_0xc280bd9
    // -> if *(a0) == *(a0+0x8) goto L_0xc280bbf
    L_0xc280bb6:;
    r15 = reinterpret_cast<uintptr_t>(rsi->f0[1]);
    if (reinterpret_cast<uintptr_t>(rbx) != r15) goto L_0xc280bd9;

    // 0xc280bbf..0xc280bc1: basic block 3
    // 0xc280bbf  jmp short 0xC280C14
    // -> if jmp goto L_0xc280c14
    L_0xc280bbf:;

    // 0xc280bc1..0xc280bd0: basic block 4
    // 0xc280bc1  nop [rax+rax]
    // -> if fallthrough goto L_0xc280bd0
    L_0xc280bc1:;

    // 0xc280bd0..0xc280bd9: basic block 5
    // 0xc280bd0  add rbx,0x20
    // 0xc280bd4  cmp rbx,r15
    // 0xc280bd7  je short 0xC280C11
    // -> if ? == *(a0+0x8) goto L_0xc280c11
    // -> if ? != *(a0+0x8) goto L_0xc280bd9
    L_0xc280bd0:;
    rbx = reinterpret_cast<sub_c280b90_rbx*>(reinterpret_cast<uintptr_t>(rbx) + 0x20);
    if (reinterpret_cast<uintptr_t>(rbx) == r15) goto L_0xc280c11;

    // 0xc280bd9..0xc280be2: basic block 6
    // 0xc280bd9  mov r14,[rbx+0x10]
    // 0xc280bdd  test r14,r14
    // 0xc280be0  je short 0xC280BD0
    // -> if ? == 0 goto L_0xc280bd0
    // -> if ? != 0 goto L_0xc280be2
    L_0xc280bd9:;
    r14 = reinterpret_cast<sub_c280b90_r14*>(rbx->f10);
    if (r14 == nullptr) goto L_0xc280bd0;

    // 0xc280be2..0xc280be9: basic block 7
    // 0xc280be2  lock dec dword ptr [r14+8]
    // 0xc280be7  jne short 0xC280BD0
    // -> if (Dec ?, ?) != 0 goto L_0xc280bd0
    // -> if (Dec ?, ?) == 0 goto L_0xc280be9
    L_0xc280be2:;
    if (_InterlockedDecrement(&r14->f8) != 0) goto L_0xc280bd0;

    // 0xc280be9..0xc280bff: basic block 8
    // 0xc280be9  mov rax,[r14]
    // 0xc280bec  mov rax,[rax]
    // 0xc280bef  mov rcx,r14
    // 0xc280bf2  call qword ptr [0xF99FFA0]
    // 0xc280bf8  lock dec dword ptr [r14+0xC]
    // 0xc280bfd  jne short 0xC280BD0
    // -> if (Dec ?, ?) != 0 goto L_0xc280bd0
    // -> if (Dec ?, ?) == 0 goto L_0xc280bff
    L_0xc280be9:;
    {
        auto* rax2 = reinterpret_cast<void**>(r14->f0);
        auto vt = reinterpret_cast<void(*)(void*)>(rax2[0]);
        vt(r14);
    }
    if (_InterlockedDecrement(&r14->fc) != 0) goto L_0xc280bd0;

    // 0xc280bff..0xc280c11: basic block 9
    // 0xc280bff  mov rax,[r14]
    // 0xc280c02  mov rax,[rax+8]
    // 0xc280c06  mov rcx,r14
    // 0xc280c09  call qword ptr [0xF99FFA0]
    // 0xc280c0f  jmp short 0xC280BD0
    // -> if jmp goto L_0xc280bd0
    L_0xc280bff:;
    {
        auto* rax2 = reinterpret_cast<void**>(r14->f0);
        auto vt1 = reinterpret_cast<void(*)(void*)>(rax2[1]);
        vt1(r14);
    }
    goto L_0xc280bd0;

    // 0xc280c11..0xc280c14: basic block 10
    // 0xc280c11  mov rbx,[rsi]
    // -> if fallthrough goto L_0xc280c14
    L_0xc280c11:;
    rbx = reinterpret_cast<sub_c280b90_rbx*>(rsi->f0[0]);

    // 0xc280c14..0xc280c24: basic block 11
    // 0xc280c14  mov rdx,[rsi+0x10]
    // 0xc280c18  sub rdx,rbx
    // 0xc280c1b  cmp rdx,0x1000
    // 0xc280c22  jb short 0xC280C3C
    // -> if (*(a0+0x10) - *(a0)) <u 0x1000 goto L_0xc280c3c
    // -> if (*(a0+0x10) - *(a0)) >=u 0x1000 goto L_0xc280c24
    L_0xc280c14:;
    rdx = reinterpret_cast<uintptr_t>(rsi->f10) - reinterpret_cast<uintptr_t>(rbx);
    if (rdx < 0x1000ULL) goto L_0xc280c3c;
    if (rdx >= 0x1000ULL) goto L_0xc280c24;

    // 0xc280c24..0xc280c35: basic block 12
    // 0xc280c24  mov rax,[rbx-8]
    // 0xc280c28  add rbx,0xFFFFFFFFFFFFFFF8
    // 0xc280c2c  sub rbx,rax
    // 0xc280c2f  cmp rbx,0x20
    // 0xc280c33  jae short 0xC280C85
    // -> if (*(a0)-0x8 - *(*(a0)-0x8)) >=u 0x20 goto L_0xc280c85
    // -> if (*(a0)-0x8 - *(*(a0)-0x8)) <u 0x20 goto L_0xc280c35
    L_0xc280c24:;
    rax = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(rbx) - 8);
    rbx = reinterpret_cast<sub_c280b90_rbx*>(reinterpret_cast<uintptr_t>(rbx) - 8 - rax);
    if (reinterpret_cast<uintptr_t>(rbx) >= 0x20ULL) goto L_0xc280c85;
    if (reinterpret_cast<uintptr_t>(rbx) < 0x20ULL) goto L_0xc280c35;

    // 0xc280c35..0xc280c3c: basic block 13
    // 0xc280c35  add rdx,0x27
    // 0xc280c39  mov rbx,rax
    // -> if fallthrough goto L_0xc280c3c
    L_0xc280c35:;
    rdx += 0x27;
    rbx = reinterpret_cast<sub_c280b90_rbx*>(rax);
    goto L_0xc280c3c;

    // 0xc280c3c..0xc280c52: basic block 14
    // 0xc280c3c  mov rcx,rbx
    // 0xc280c3f  call 0xE935700
    // 0xc280c44  xorps xmm0,xmm0
    // 0xc280c47  movups [rsi],xmm0
    // 0xc280c4a  mov qword ptr [rsi+0x10],0
    // -> if fallthrough goto L_0xc280c52
    L_0xc280c3c:;
    sub_e935700(reinterpret_cast<uintptr_t>(rbx), rdx, nullptr, nullptr);
    rsi->f0[0] = nullptr;
    rsi->f0[1] = nullptr;
    rsi->f10 = nullptr;
    goto L_0xc280c52;

    // 0xc280c52..0xc280c76: basic block 15
    // 0xc280c52  mov rax,[rdi]
    // 0xc280c55  mov [rsi],rax
    // 0xc280c58  mov rax,[rdi+8]
    // 0xc280c5c  mov [rsi+8],rax
    // 0xc280c60  mov rax,[rdi+0x10]
    // 0xc280c64  mov [rsi+0x10],rax
    // 0xc280c68  xorps xmm0,xmm0
    // 0xc280c6b  movups [rdi],xmm0
    // 0xc280c6e  mov qword ptr [rdi+0x10],0
    // -> if fallthrough goto L_0xc280c76
    L_0xc280c52:;
    rsi->f0[0] = rdi->f0[0];
    rsi->f0[1] = rdi->f0[1];
    rsi->f10 = rdi->f10;
    rdi->f0[0] = nullptr;
    rdi->f0[1] = nullptr;
    rdi->f10 = nullptr;

    // 0xc280c76..0xc280c85: basic block 16
    // 0xc280c76  mov rax,rsi
    // 0xc280c79  add rsp,0x30
    // 0xc280c7d  pop rbx
    // 0xc280c7e  pop rdi
    // 0xc280c7f  pop rsi
    // 0xc280c80  pop r14
    // 0xc280c82  pop r15
    // 0xc280c84  ret
    // -> (fall-through / ret / end)
    L_0xc280c76:;
    return reinterpret_cast<uintptr_t>(rsi);

    // 0xc280c85..0xc280c9f: basic block 17
    // 0xc280c85  mov qword ptr [rsp+0x20],0
    // 0xc280c8e  xor ecx,ecx
    // 0xc280c90  xor edx,edx
    // 0xc280c92  xor r8d,r8d
    // 0xc280c95  xor r9d,r9d
    // 0xc280c98  call qword ptr [0xF9A8C78]
    // 0xc280c9e  int3
    // -> (fall-through / ret / end)
    L_0xc280c85:;
    rsp_state.f20 = 0;
    {
        auto* slot = reinterpret_cast<void**>(0xF9A8C78);
        auto fn = reinterpret_cast<void (*)(uintptr_t, uintptr_t, void*, void*)>(*slot);
        fn(0, 0, nullptr, nullptr);
    }
    __debugbreak(); // unreachable: original executes int3 after the call; no return path from here

    return 0;   // unreachable; keeps the compiler happy
}

} // namespace native::helpers
