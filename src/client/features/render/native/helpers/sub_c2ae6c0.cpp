// LIFT 0xc2ae6c0 size 0x10d 1.26.62.01 sub_c2ae6c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c2ae6c0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_c2ae6c0, "sub_c2ae6c0", 0xc2ae6c0, sub_c2ae6c0, nullptr);

// Verbatim call instructions from the disassembly of [0xc2ae6c0, 0xc2ae7cd) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xc2ae6f6  call 0xC2AEA90
0xc2ae761  call qword ptr [0xF99FFA0]
0xc2ae777  call qword ptr [0xF99FFA0]
0xc2ae7a5  call qword ptr [0xF99FFA0]
0xc2ae7bb  call qword ptr [0xF99FFA0]
#endif

// Layout assertions for the slots this translation unit touches (dossier mirrors them).
static_assert(offsetof(sub_c2ae6c0_rcx, f268) == 0x268, "sub_0xc2ae6c0 +0x268");
static_assert(offsetof(sub_c2ae6c0_rcx, f278) == 0x278, "sub_0xc2ae6c0 +0x278");
static_assert(offsetof(sub_c2ae6c0_rcx, f288) == 0x288, "sub_0xc2ae6c0 +0x288");
static_assert(offsetof(sub_c2ae6c0_rcx, f290) == 0x290, "sub_0xc2ae6c0 +0x290");
static_assert(offsetof(sub_c2ae6c0_rcx, f298) == 0x298, "sub_0xc2ae6c0 +0x298");
static_assert(offsetof(sub_c2ae6c0_rdi, f8) == 0x8, "sub_0xc2ae6c0 control block strong count");
static_assert(offsetof(sub_c2ae6c0_rdi, fc) == 0xc, "sub_0xc2ae6c0 control block weak count");
static_assert(offsetof(sub_c2ae6c0_rbx, f8) == 0x8, "sub_0xc2ae6c0 element control block");
static_assert(offsetof(sub_c2ae6c0_rax, f8) == 0x8, "sub_0xc2ae6c0 vtable slot 1");

// 0xc2aea90: direct, depth-1 callee outside this lift set (its own helper file is
// not part of this unit). rcx = owner object, rdx = pointer to the 16-byte value it fills, and it
// returns a bool in al. A non-zero return repeats the call, a zero return ends the drain loop.
bool sub_c2aea90(void* owner, void* out);

// 0xF99FFA0 holds the Control Flow Guard dispatch pointer (sub_eea6040). Every indirect
// call of this function loads the target from the object's vtable into rax, the object
// into rcx, and the guard thunk tail-calls it; the lifted form calls the vtable slot
// directly with the same argument.
using sub_c2ae6c0_vfn = void (*)(void*);

void sub_c2ae6c0(void* self) {
    sub_c2ae6c0_rcx* const a0 = static_cast<sub_c2ae6c0_rcx*>(self);
    // 0xc2ae6c0..0xc2ae6f0: prologue; [rbp-0x20] is zeroed with one 16-byte store
    // (0xc2ae6dd) and rdi points at it (0xc2ae6e1). The -2 stored at [rbp-8]
    // (0xc2ae6cf) is compiler frame bookkeeping for the unwind state, not data of
    // the lifted object.
    // 0xc2ae6c0  push rbp
    // 0xc2ae6c1  push r14
    // 0xc2ae6c3  push rsi
    // 0xc2ae6c4  push rdi
    // 0xc2ae6c5  push rbx
    // 0xc2ae6c6  sub rsp,0x40
    // 0xc2ae6ca  lea rbp,[rsp+0x40]
    // 0xc2ae6d7  mov rsi,rcx
    // 0xc2ae6da  xorps xmm0,xmm0
    // 0xc2ae6dd  movaps [rbp-0x20],xmm0
    std::uint64_t local[2] = {0, 0};   // [rbp-0x20] / [rbp-0x18]
    sub_c2ae6c0_rbx* it = nullptr;
    sub_c2ae6c0_rbx* end = nullptr;

L_0xc2ae6f0:;
    // 0xc2ae6f0..0xc2ae700: drain through 0xc2aea90 until it reports empty
    // 0xc2ae6f0  mov rcx,rsi
    // 0xc2ae6f3  mov rdx,rdi
    // 0xc2ae6f6  call 0xC2AEA90
    // 0xc2ae6fc  test al,al
    // 0xc2ae6fe  jne short 0xC2AE6F0
    if (sub_c2aea90(a0, local)) goto L_0xc2ae6f0;

    // 0xc2ae700..0xc2ae72f: clear the three slots, load [begin, end)
    // 0xc2ae700  xorps xmm0,xmm0
    // 0xc2ae703  movups [rsi+0x278],xmm0
    // 0xc2ae70a  movups [rsi+0x268],xmm0
    // 0xc2ae711  mov qword ptr [rsi+0x288],0
    // 0xc2ae71c  mov rbx,[rsi+0x290]
    // 0xc2ae723  mov r14,[rsi+0x298]
    // 0xc2ae72a  cmp rbx,r14
    // 0xc2ae72d  jne short 0xC2AE749
    a0->f278[0] = 0;
    a0->f278[1] = 0;
    a0->f268[0] = 0;
    a0->f268[1] = 0;
    a0->f288 = 0;
    it = reinterpret_cast<sub_c2ae6c0_rbx*>(a0->f290);
    end = reinterpret_cast<sub_c2ae6c0_rbx*>(a0->f298);
    if (it == end) goto L_0xc2ae78d;
    // 0xc2ae72f..0xc2ae731  jmp short 0xC2AE78D (taken when begin == end)
    // 0xc2ae731..0xc2ae740  nop [rax+rax] padding; no statements

L_0xc2ae740:;
    // 0xc2ae740..0xc2ae749: advance one 16-byte element, test for the end
    // 0xc2ae740  add rbx,0x10
    // 0xc2ae744  cmp rbx,r14
    // 0xc2ae747  je short 0xC2AE77F
    ++it;
    if (it != end) goto L_0xc2ae749;
    goto L_0xc2ae77f;

L_0xc2ae749:;
    {
        // 0xc2ae749..0xc2ae752: control block of this element
        // 0xc2ae749  mov rdi,[rbx+8]
        // 0xc2ae74d  test rdi,rdi
        // 0xc2ae750  je short 0xC2AE740
        sub_c2ae6c0_rdi* const cb = static_cast<sub_c2ae6c0_rdi*>(it->f8);
        if (!cb) goto L_0xc2ae740;

        // 0xc2ae752..0xc2ae758: drop the strong reference, destroy if it was last
        // 0xc2ae752  lock dec dword ptr [rdi+8]
        // 0xc2ae756  jne short 0xC2AE740
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&cb->f8)) != 0) goto L_0xc2ae740;

        // 0xc2ae758..0xc2ae76d: on_zero_shared through vtable slot 0, then weak count
        // 0xc2ae758  mov rax,[rdi]
        // 0xc2ae75b  mov rax,[rax]
        // 0xc2ae75e  mov rcx,rdi
        // 0xc2ae761  call qword ptr [0xF99FFA0]
        // 0xc2ae767  lock dec dword ptr [rdi+0xC]
        // 0xc2ae76b  jne short 0xC2AE740
        sub_c2ae6c0_rax* const vt0 = static_cast<sub_c2ae6c0_rax*>(cb->f0);
        reinterpret_cast<sub_c2ae6c0_vfn>(vt0->f0)(cb);
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&cb->fc)) != 0) goto L_0xc2ae740;

        // 0xc2ae76d..0xc2ae77f: on_zero_shared_weak through vtable slot 1
        // 0xc2ae76d  mov rax,[rdi]
        // 0xc2ae770  mov rax,[rax+8]
        // 0xc2ae774  mov rcx,rdi
        // 0xc2ae777  call qword ptr [0xF99FFA0]
        // 0xc2ae77d  jmp short 0xC2AE740
        sub_c2ae6c0_rax* const vt1 = static_cast<sub_c2ae6c0_rax*>(cb->f0);
        reinterpret_cast<sub_c2ae6c0_vfn>(vt1->f8)(cb);
        goto L_0xc2ae740;
    }

L_0xc2ae77f:;
    // 0xc2ae77f..0xc2ae78d: mark the array empty
    // 0xc2ae77f  mov rax,[rsi+0x290]
    // 0xc2ae786  mov [rsi+0x298],rax
    a0->f298 = static_cast<std::uint64_t>(reinterpret_cast<std::uintptr_t>(a0->f290));

L_0xc2ae78d:;
    {
        // 0xc2ae78d..0xc2ae796: release the control block left in the drain slot
        // 0xc2ae78d  mov rsi,[rbp-0x18]
        // 0xc2ae791  test rsi,rsi
        // 0xc2ae794  je short 0xC2AE7C2
        sub_c2ae6c0_rdi* const cb = reinterpret_cast<sub_c2ae6c0_rdi*>(local[1]);
        if (!cb) goto L_0xc2ae7c2;

        // 0xc2ae796..0xc2ae79c: strong reference
        // 0xc2ae796  lock dec dword ptr [rsi+8]
        // 0xc2ae79a  jne short 0xC2AE7C2
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&cb->f8)) != 0) goto L_0xc2ae7c2;

        // 0xc2ae79c..0xc2ae7b1: on_zero_shared through vtable slot 0, then weak count
        // 0xc2ae79c  mov rax,[rsi]
        // 0xc2ae79f  mov rax,[rax]
        // 0xc2ae7a2  mov rcx,rsi
        // 0xc2ae7a5  call qword ptr [0xF99FFA0]
        // 0xc2ae7ab  lock dec dword ptr [rsi+0xC]
        // 0xc2ae7af  jne short 0xC2AE7C2
        sub_c2ae6c0_rax* const vt0 = static_cast<sub_c2ae6c0_rax*>(cb->f0);
        reinterpret_cast<sub_c2ae6c0_vfn>(vt0->f0)(cb);
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&cb->fc)) != 0) goto L_0xc2ae7c2;

        // 0xc2ae7b1..0xc2ae7c2: on_zero_shared_weak through vtable slot 1
        // 0xc2ae7b1  mov rax,[rsi]
        // 0xc2ae7b4  mov rax,[rax+8]
        // 0xc2ae7b8  mov rcx,rsi
        // 0xc2ae7bb  call qword ptr [0xF99FFA0]
        sub_c2ae6c0_rax* const vt1 = static_cast<sub_c2ae6c0_rax*>(cb->f0);
        reinterpret_cast<sub_c2ae6c0_vfn>(vt1->f8)(cb);
    }

L_0xc2ae7c2:;
    // 0xc2ae7c2..0xc2ae7cd: epilogue
    // 0xc2ae7c2  add rsp,0x40
    // 0xc2ae7c6  pop rbx
    // 0xc2ae7c7  pop rdi
    // 0xc2ae7c8  pop rsi
    // 0xc2ae7c9  pop r14
    // 0xc2ae7cb  pop rbp
    // 0xc2ae7cc  ret
}

} // namespace native::helpers
