// LIFT 0x8f1e10 size 0x118 1.26.62.01 sub_8f1e10
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_8f1e10.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

#include "client/features/render/native/helpers/sub_ae500.h"
#include "client/features/render/native/helpers/sub_eec59e0.h"
#include "client/features/render/native/helpers/sub_eec5a00.h"
#include "client/features/render/native/helpers/sub_eec5b90.h"

// sub_eec59f0 and sub_eec5a10 are the MSVCP140 _Mtx_lock/_Mtx_unlock forwarders. Their
// accepted headers declare the CRT entry points themselves, and the CRT headers pulled in
// by Lift.h already declare those entry points, so the forwarders are declared here with
// the same tag and signature their own translation units use.
struct _Mtx;
namespace native {
void sub_eec59f0(struct _Mtx* mtx);
void sub_eec5a10(struct _Mtx* mtx);
} // namespace native

namespace native::helpers {

LIFT_FN(sub_8f1e10, "sub_8f1e10", 0x8f1e10, sub_8f1e10, nullptr);

// Verbatim call instructions from the disassembly of [0x8f1e10, 0x8f1f28) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x8f1e3e  call 0xAE500
0x8f1e65  call qword ptr [0xF99FFA0]
0x8f1e92  call qword ptr [0xF99FFA0]
0x8f1eb0  call 0xEEC59F0
0x8f1ecf  call 0xEEC5B90
0x8f1ed7  call 0xEEC5A10
0x8f1ee8  call 0xEEC5B90
0x8f1f03  call 0xEEC59E0
0x8f1f0e  call 0xEEC5A00
0x8f1f22  call 0xEEC5A00
#endif

// Ranges: every instruction of [0x8f1e10, 0x8f1f28) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.
static_assert(offsetof(sub_8f1e10_rcx, f88) == 0x88, "sub_0x8f1e10 self+0x88 callable object");
static_assert(offsetof(sub_8f1e10_rcx, f90) == 0x90, "sub_0x8f1e10 self+0x90 reference count");
static_assert(offsetof(sub_8f1e10_rcx, f34c) == 0x34c, "sub_0x8f1e10 self+0x34c _Mtx state word");
static_assert(sizeof(sub_8f1e10_rdx) == 0x10, "sub_0x8f1e10 result is two quadwords");
static_assert(sizeof(sub_8f1e10_ctx) >= 0x48, "sub_0x8f1e10 stack context lower bound");
//
// The two `call qword ptr [0xF99FFA0]` sites dispatch through the vendor thunk sub_eea6040
// (a boundary function): the callee is loaded from the object's vtable and the thunk is a
// plain `jmp rax`, so the lifted code loads the same vtable slot and calls it directly.
// The two 16-byte constants 0x128D4558 and 0x128D4248 lie in .data past its raw image and
// carry no base relocations, so both slots are zero-filled at load; the corresponding
// movups pair therefore stores sixteen zero bytes.

sub_8f1e10_rdx* sub_8f1e10(sub_8f1e10_rcx* self, sub_8f1e10_rdx* out) {
    sub_8f1e10_ctx ctx;
    sub_8f1e10_rax* vt;
    bool ok;
    std::uint64_t refs;
    int lockResult;

    // 0x8f1e10..0x8f1e4a: basic block 0
    // 0x8f1e10  push rbp
    // 0x8f1e11  push rsi
    // 0x8f1e12  push rdi
    // 0x8f1e13  push rbx
    // 0x8f1e14  sub rsp,0x68
    // 0x8f1e18  lea rbp,[rsp+0x60]
    // 0x8f1e1d  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0x8f1e25  mov rsi,rdx
    // 0x8f1e28  mov rdi,rcx
    // 0x8f1e2b  mov qword ptr [rbp-8],0
    // 0x8f1e33  add rcx,0x98
    // 0x8f1e3a  lea rdx,[rbp-0x40]
    // 0x8f1e3e  call 0xAE500
    // 0x8f1e43  nop
    // 0x8f1e44  mov ebx,eax
    // 0x8f1e46  test al,al
    // 0x8f1e48  je short 0x8F1E6E
    // -> if u8(ret@8f1e3e) == 0 goto L_0x8f1e6e
    // -> if u8(ret@8f1e3e) != 0 goto L_0x8f1e4a
    ctx.f40 = 0xFFFFFFFFFFFFFFFEull;   // 0x8f1e1d
    ctx.f38 = nullptr;                 // 0x8f1e2b
    ok = sub_ae500(reinterpret_cast<sub_ae500_head*>(&self->f98), &ctx);   // 0x8f1e3e
    if (!ok) goto L_0x8f1e6e;          // 0x8f1e48

    // 0x8f1e4a..0x8f1e5a: basic block 1
    // 0x8f1e4a  mov rcx,[rdi+0x88]
    // 0x8f1e51  test rcx,rcx
    // 0x8f1e54  je 0x8F1F03
    // -> if *(a0+0x88) == 0 goto L_0x8f1f03
    // -> if *(a0+0x88) != 0 goto L_0x8f1e5a
    if (self->f88 == nullptr) goto L_0x8f1f03;   // 0x8f1e54

    // 0x8f1e5a..0x8f1e6e: basic block 2
    // 0x8f1e5a  mov rax,[rcx]
    // 0x8f1e5d  mov rax,[rax+0x10]
    // 0x8f1e61  lea rdx,[rbp-0x40]
    // 0x8f1e65  call qword ptr [0xF99FFA0]
    // 0x8f1e6b  nop
    // 0x8f1e6c  jmp short 0x8F1E78
    // -> if jmp goto L_0x8f1e78
    vt = *reinterpret_cast<sub_8f1e10_rax**>(self->f88);   // 0x8f1e5a, 0x8f1e5d
    reinterpret_cast<void (*)(void*, sub_8f1e10_ctx*)>(vt->f10)(self->f88, &ctx);   // 0x8f1e65
    goto L_0x8f1e78;                                        // 0x8f1e6c

    // 0x8f1e6e..0x8f1e78: basic block 3
    // 0x8f1e6e  movups xmm0,[0x128D4558]
    // 0x8f1e75  movups [rsi],xmm0
    // -> if fallthrough goto L_0x8f1e78
L_0x8f1e6e:
    out->f0[0] = 0;   // 0x8f1e6e: 0x128D4558 is a zero-filled .data slot
    out->f0[1] = 0;   // 0x8f1e75

    // 0x8f1e78..0x8f1e81: basic block 4
    // 0x8f1e78  mov rcx,[rbp-8]
    // 0x8f1e7c  test rcx,rcx
    // 0x8f1e7f  je short 0x8F1E98
    // -> if ctx+0x38 == 0 goto L_0x8f1e98
    // -> if ctx+0x38 != 0 goto L_0x8f1e81
L_0x8f1e78:
    if (ctx.f38 != nullptr) {   // 0x8f1e78, 0x8f1e7f
        // 0x8f1e81..0x8f1e98: basic block 5
        // 0x8f1e81  lea rax,[rbp-0x40]
        // 0x8f1e85  cmp rcx,rax
        // 0x8f1e88  setne dl
        // 0x8f1e8b  mov rax,[rcx]
        // 0x8f1e8e  mov rax,[rax+0x20]
        // 0x8f1e92  call qword ptr [0xF99FFA0]
        // -> if fallthrough goto L_0x8f1e98
        vt = *reinterpret_cast<sub_8f1e10_rax**>(ctx.f38);   // 0x8f1e8b, 0x8f1e8e
        const unsigned char notInline = (ctx.f38 != static_cast<void*>(&ctx)) ? 1 : 0;   // 0x8f1e85, 0x8f1e88
        reinterpret_cast<void (*)(void*, unsigned char)>(vt->f20)(ctx.f38, notInline);   // 0x8f1e92
    }

    // 0x8f1e98..0x8f1e9c: basic block 6
    // 0x8f1e98  test bl,bl
    // 0x8f1e9a  je short 0x8F1EF7
    // -> if u8(u32(u32(ret@8f1e3e))) == 0 goto L_0x8f1ef7
    // -> if u8(u32(u32(ret@8f1e3e))) != 0 goto L_0x8f1e9c
    if (!ok) goto L_0x8f1ef7;   // 0x8f1e9a

    // 0x8f1e9c..0x8f1ea6: basic block 7
    // 0x8f1e9c  lock dec qword ptr [rdi+0x90]
    // 0x8f1ea4  jne short 0x8F1EDE
    // -> if (Dec *(a0+0x90), ?) != 0 goto L_0x8f1ede
    // -> if (Dec *(a0+0x90), ?) == 0 goto L_0x8f1ea6
    refs = static_cast<std::uint64_t>(
        _InterlockedDecrement64(reinterpret_cast<volatile __int64*>(&self->f90)));   // 0x8f1e9c
    if (refs != 0) goto L_0x8f1ede;   // 0x8f1ea4

    // 0x8f1ea6..0x8f1eb9: basic block 8
    // 0x8f1ea6  lea rbx,[rdi+0x300]
    // 0x8f1ead  mov rcx,rbx
    // 0x8f1eb0  call 0xEEC59F0
    // 0x8f1eb5  test eax,eax
    // 0x8f1eb7  jne short 0x8F1F09
    // -> if u32(ret@8f1eb0) != 0 goto L_0x8f1f09
    // -> if u32(ret@8f1eb0) == 0 goto L_0x8f1eb9
    // sub_eec59f0 tail-jumps to MSVCP140!_Mtx_lock, whose result arrives in EAX.
    lockResult = reinterpret_cast<int (*)(void*)>(&::native::sub_eec59f0)(&self->f300);   // 0x8f1eb0
    if (lockResult != 0) goto L_0x8f1f09;   // 0x8f1eb7

    // 0x8f1eb9..0x8f1ec5: basic block 9
    // 0x8f1eb9  cmp dword ptr [rdi+0x34C],0x7FFFFFFF
    // 0x8f1ec3  je short 0x8F1F13
    // -> if *u32(a0+0x34C) == 0x7FFFFFFF goto L_0x8f1f13
    // -> if *u32(a0+0x34C) != 0x7FFFFFFF goto L_0x8f1ec5
    if (self->f34c == 0x7FFFFFFFu) goto L_0x8f1f13;   // 0x8f1ec3

    // 0x8f1ec5..0x8f1ede: basic block 10
    // 0x8f1ec5  add rdi,0x350
    // 0x8f1ecc  mov rcx,rdi
    // 0x8f1ecf  call 0xEEC5B90
    // 0x8f1ed4  mov rcx,rbx
    // 0x8f1ed7  call 0xEEC5A10
    // 0x8f1edc  jmp short 0x8F1EED
    // -> if jmp goto L_0x8f1eed
    reinterpret_cast<int (*)(void*)>(&::native::sub_eec5b90)(&self->f350);   // 0x8f1ecf
    reinterpret_cast<void (*)(void*)>(&::native::sub_eec5a10)(&self->f300);  // 0x8f1ed7
    goto L_0x8f1eed;                                                        // 0x8f1edc

    // 0x8f1ede..0x8f1eed: basic block 11
    // 0x8f1ede  add rdi,0x350
    // 0x8f1ee5  mov rcx,rdi
    // 0x8f1ee8  call 0xEEC5B90
    // -> if fallthrough goto L_0x8f1eed
L_0x8f1ede:
    reinterpret_cast<int (*)(void*)>(&::native::sub_eec5b90)(&self->f350);   // 0x8f1ee8

    // 0x8f1eed..0x8f1ef7: basic block 12
    // 0x8f1eed  movups xmm0,[0x128D4248]
    // 0x8f1ef4  movups [rsi],xmm0
    // -> if fallthrough goto L_0x8f1ef7
L_0x8f1eed:
    out->f0[0] = 0;   // 0x8f1eed: 0x128D4248 is a zero-filled .data slot
    out->f0[1] = 0;   // 0x8f1ef4

    // 0x8f1ef7..0x8f1f03: basic block 13
    // 0x8f1ef7  mov rax,rsi
    // 0x8f1efa  add rsp,0x68
    // 0x8f1efe  pop rbx
    // 0x8f1eff  pop rdi
    // 0x8f1f00  pop rsi
    // 0x8f1f01  pop rbp
    // 0x8f1f02  ret
    // -> (fall-through / ret / end)
L_0x8f1ef7:
    return out;   // 0x8f1ef7, 0x8f1f02

    // 0x8f1f03..0x8f1f09: basic block 14
    // 0x8f1f03  call 0xEEC59E0
    // 0x8f1f08  nop
    // -> if fallthrough goto L_0x8f1f09
L_0x8f1f03:
    ::native::sub_eec59e0();   // std::_Xbad_function_call, does not return

    // 0x8f1f09..0x8f1f13: basic block 15
    // 0x8f1f09  mov ecx,5
    // 0x8f1f0e  call 0xEEC5A00
    // -> if fallthrough goto L_0x8f1f13
L_0x8f1f09:
    ::native::sub_eec5a00(5);   // std::_Throw_Cpp_error(5), does not return

    // 0x8f1f13..0x8f1f28: basic block 16
    // 0x8f1f13  mov dword ptr [rdi+0x34C],0x7FFFFFFE
    // 0x8f1f1d  mov ecx,6
    // 0x8f1f22  call 0xEEC5A00
    // 0x8f1f27  int3
    // -> (fall-through / ret / end)
L_0x8f1f13:
    self->f34c = 0x7FFFFFFEu;   // 0x8f1f13
    ::native::sub_eec5a00(6);   // 0x8f1f22, does not return
    return out;                 // 0x8f1f27 int3; unreachable, _Throw_Cpp_error never returns
}

} // namespace native::helpers
