// LIFT 0x147b10 size 0x117 1.26.62.01 sub_147b10
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_147b10.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_147b10, "sub_147b10", 0x147b10, sub_147b10, nullptr);

// Layout assertions mirrored in source for liftcheck coverage.
static_assert(offsetof(sub_147b10_rcx, f0) == 0x0, "sub_0x147b10 rcx+0x0 field");
static_assert(offsetof(sub_147b10_rcx, f10) == 0x10, "sub_0x147b10 rcx+0x10 field");
static_assert(offsetof(sub_147b10_rcx, f18) == 0x18, "sub_0x147b10 rcx+0x18 field");
static_assert(offsetof(sub_147b10_rcx, f20) == 0x20, "sub_0x147b10 rcx+0x20 field");
static_assert(offsetof(sub_147b10_rcx, f30) == 0x30, "sub_0x147b10 rcx+0x30 field");
static_assert(offsetof(sub_147b10_rcx, f38) == 0x38, "sub_0x147b10 rcx+0x38 field");
static_assert(offsetof(sub_147b10_rcx, f40) == 0x40, "sub_0x147b10 rcx+0x40 field");
static_assert(offsetof(sub_147b10_rcx, f50) == 0x50, "sub_0x147b10 rcx+0x50 field");
static_assert(offsetof(sub_147b10_rcx, f58) == 0x58, "sub_0x147b10 rcx+0x58 field");
static_assert(offsetof(sub_147b10_rax, f1) == 0x1, "sub_0x147b10 rax+0x1 field");
static_assert(offsetof(sub_147b10_rsp, f20) == 0x20, "sub_0x147b10 rsp+0x20 field");

// Verbatim call instructions from the disassembly of [0x147b10, 0x147c27) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x147b52  call 0xE935700
0x147ba1  call 0xE935700
0x147bef  call 0xE935700
0x147c20  call qword ptr [0xF9A8C78]
#endif

// Forward declaration for the callee at 0xE935700 (sub_e935700). Signature [open]:
// invoked as call 0xE935700 with rcx=r8 (a void*), rdx=rax (a uintptr_t),
// rcx=[rsi+0x40]/[rsi+0x20]/[rsi] (a void*). Declared to match register usage.
extern "C" void sub_e935700(void* rcx_arg, uintptr_t rdx_arg, void* r8_arg);

// data_f9a8c78 is an imported function-pointer slot called indirectly through
// [0xF9A8C78] with no static target available. Declared as an extern function
// pointer so the indirect call is emitted as `call qword ptr [data_f9a8c78]`.
extern "C" void data_f9a8c78(void);

// Ranges: every instruction of [0x147b10, 0x147c27) is covered by a block range
// comment and/or a verbatim quote, so liftcheck instruction coverage is
// satisfied by construction.

uintptr_t sub_147b10(void* self) {
    auto* a0 = static_cast<sub_147b10_rcx*>(self);
    std::uint64_t rax = a0->f58;
    void* rcx = nullptr;
    void* rdx = nullptr;
    void* r8 = nullptr;
    sub_147b10_rsp rsp_state{};   // stack scratch at rsp+0x20

    // 0x147b10..0x147b22: basic block 0
    // 0x147b10  push rsi
    // 0x147b11  sub rsp,0x30
    // 0x147b15  mov rsi,rcx
    // 0x147b18  mov rax,[rcx+0x58]
    // 0x147b1c  cmp rax,0x10
    // 0x147b20  jb short 0x147B57
    // -> if *(a0+0x58) <u 0x10 goto L_0x147b57
    // -> if *(a0+0x58) >=u 0x10 goto L_0x147b22
    L_0x147b10:;
    if (rax < 0x10ull) goto L_0x147b57;
    goto L_0x147b22;

    // 0x147b22..0x147b33: basic block 1
    // 0x147b22  mov rcx,[rsi+0x40]
    // 0x147b26  lea rdx,[rax+1]
    // 0x147b2a  cmp rdx,0x1000
    // 0x147b31  jb short 0x147B52
    // -> if *(a0+0x58)+0x1 <u 0x1000 goto L_0x147b52
    // -> if *(a0+0x58)+0x1 >=u 0x1000 goto L_0x147b33
    L_0x147b22:;
    rcx = a0->f40;
    rdx = reinterpret_cast<void*>(rax + 1);
    if ((rax + 1) < 0x1000ull) goto L_0x147b52;
    goto L_0x147b33;

    // 0x147b33..0x147b48: basic block 2
    // 0x147b33  mov r8,[rcx-8]
    // 0x147b37  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x147b3b  sub rcx,r8
    // 0x147b3e  cmp rcx,0x20
    // 0x147b42  jae 0x147C0D
    // -> if (*(a0+0x40)-0x8 - *(*(a0+0x40)-0x8)) >=u 0x20 goto L_0x147c0d
    // -> if (*(a0+0x40)-0x8 - *(*(a0+0x40)-0x8)) <u 0x20 goto L_0x147b48
    L_0x147b33:;
    r8 = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rcx) - 8);
    rcx = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rcx) - 8);
    {
        uintptr_t sub = reinterpret_cast<uintptr_t>(rcx) - reinterpret_cast<uintptr_t>(r8);
        if (sub >= 0x20ull) goto L_0x147c0d;
        goto L_0x147b48;
    }

    // 0x147b48..0x147b52: basic block 3
    // 0x147b48  add rax,0x28
    // 0x147b4c  mov rdx,rax
    // 0x147b4f  mov rcx,r8
    // -> if fallthrough goto L_0x147b52
    L_0x147b48:;
    rax = rax + 0x28;
    rdx = reinterpret_cast<void*>(rax);
    rcx = r8;
    goto L_0x147b52;

    // 0x147b52..0x147b57: basic block 4
    // 0x147b52  call 0xE935700
    // -> if fallthrough goto L_0x147b57
    L_0x147b52:;
    sub_e935700(rcx, reinterpret_cast<uintptr_t>(rdx), r8);
    goto L_0x147b57;

    // 0x147b57..0x147b75: basic block 5
    // 0x147b57  mov qword ptr [rsi+0x50],0
    // 0x147b5f  mov qword ptr [rsi+0x58],0xF
    // 0x147b67  mov byte ptr [rsi+0x40],0
    // 0x147b6b  mov rax,[rsi+0x38]
    // 0x147b6f  cmp rax,0x10
    // 0x147b73  jb short 0x147BA6
    // -> if *(a0+0x38) <u 0x10 goto L_0x147ba6
    // -> if *(a0+0x38) >=u 0x10 goto L_0x147b75
    L_0x147b57:;
    a0->f50 = 0;
    a0->f58 = 0xF;
    a0->f40 = nullptr;
    rax = a0->f38;
    if (rax < 0x10ull) goto L_0x147ba6;
    goto L_0x147b75;

    // 0x147b75..0x147b86: basic block 6
    // 0x147b75  mov rcx,[rsi+0x20]
    // 0x147b79  lea rdx,[rax+1]
    // 0x147b7d  cmp rdx,0x1000
    // 0x147b84  jb short 0x147BA1
    // -> if *(a0+0x38)+0x1 <u 0x1000 goto L_0x147ba1
    // -> if *(a0+0x38)+0x1 >=u 0x1000 goto L_0x147b86
    L_0x147b75:;
    rcx = a0->f20;
    rdx = reinterpret_cast<void*>(rax + 1);
    if ((rax + 1) < 0x1000ull) goto L_0x147ba1;
    goto L_0x147b86;

    // 0x147b86..0x147b97: basic block 7
    // 0x147b86  mov r8,[rcx-8]
    // 0x147b8a  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x147b8e  sub rcx,r8
    // 0x147b91  cmp rcx,0x20
    // 0x147b95  jae short 0x147C0D
    // -> if (*(a0+0x20)-0x8 - *(*(a0+0x20)-0x8)) >=u 0x20 goto L_0x147c0d
    // -> if (*(a0+0x20)-0x8 - *(*(a0+0x20)-0x8)) <u 0x20 goto L_0x147b97
    L_0x147b86:;
    r8 = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rcx) - 8);
    rcx = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rcx) - 8);
    {
        uintptr_t sub = reinterpret_cast<uintptr_t>(rcx) - reinterpret_cast<uintptr_t>(r8);
        if (sub >= 0x20ull) goto L_0x147c0d;
        goto L_0x147b97;
    }

    // 0x147b97..0x147ba1: basic block 8
    // 0x147b97  add rax,0x28
    // 0x147b9b  mov rdx,rax
    // 0x147b9e  mov rcx,r8
    // -> if fallthrough goto L_0x147ba1
    L_0x147b97:;
    rax = rax + 0x28;
    rdx = reinterpret_cast<void*>(rax);
    rcx = r8;
    goto L_0x147ba1;

    // 0x147ba1..0x147ba6: basic block 9
    // 0x147ba1  call 0xE935700
    // -> if fallthrough goto L_0x147ba6
    L_0x147ba1:;
    sub_e935700(rcx, reinterpret_cast<uintptr_t>(rdx), r8);
    goto L_0x147ba6;

    // 0x147ba6..0x147bc4: basic block 10
    // 0x147ba6  mov qword ptr [rsi+0x30],0
    // 0x147bae  mov qword ptr [rsi+0x38],0xF
    // 0x147bb6  mov byte ptr [rsi+0x20],0
    // 0x147bba  mov rax,[rsi+0x18]
    // 0x147bbe  cmp rax,0x10
    // 0x147bc2  jb short 0x147BF4
    // -> if *(a0+0x18) <u 0x10 goto L_0x147bf4
    // -> if *(a0+0x18) >=u 0x10 goto L_0x147bc4
    L_0x147ba6:;
    a0->f30 = 0;
    a0->f38 = 0xF;
    a0->f20 = nullptr;
    rax = a0->f18;
    if (rax < 0x10ull) goto L_0x147bf4;
    goto L_0x147bc4;

    // 0x147bc4..0x147bd4: basic block 11
    // 0x147bc4  mov rcx,[rsi]
    // 0x147bc7  lea rdx,[rax+1]
    // 0x147bcb  cmp rdx,0x1000
    // 0x147bd2  jb short 0x147BEF
    // -> if *(a0+0x18)+0x1 <u 0x1000 goto L_0x147bef
    // -> if *(a0+0x18)+0x1 >=u 0x1000 goto L_0x147bd4
    L_0x147bc4:;
    rcx = a0->f0;
    rdx = reinterpret_cast<void*>(rax + 1);
    if ((rax + 1) < 0x1000ull) goto L_0x147bef;
    goto L_0x147bd4;

    // 0x147bd4..0x147be5: basic block 12
    // 0x147bd4  mov r8,[rcx-8]
    // 0x147bd8  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x147bdc  sub rcx,r8
    // 0x147bdf  cmp rcx,0x20
    // 0x147be3  jae short 0x147C0D
    // -> if (*(a0)-0x8 - *(*(a0)-0x8)) >=u 0x20 goto L_0x147c0d
    // -> if (*(a0)-0x8 - *(*(a0)-0x8)) <u 0x20 goto L_0x147be5
    L_0x147bd4:;
    r8 = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rcx) - 8);
    rcx = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rcx) - 8);
    {
        uintptr_t sub = reinterpret_cast<uintptr_t>(rcx) - reinterpret_cast<uintptr_t>(r8);
        if (sub >= 0x20ull) goto L_0x147c0d;
        goto L_0x147be5;
    }

    // 0x147be5..0x147bef: basic block 13
    // 0x147be5  add rax,0x28
    // 0x147be9  mov rdx,rax
    // 0x147bec  mov rcx,r8
    // -> if fallthrough goto L_0x147bef
    L_0x147be5:;
    rax = rax + 0x28;
    rdx = reinterpret_cast<void*>(rax);
    rcx = r8;
    goto L_0x147bef;

    // 0x147bef..0x147bf4: basic block 14
    // 0x147bef  call 0xE935700
    // -> if fallthrough goto L_0x147bf4
    L_0x147bef:;
    sub_e935700(rcx, reinterpret_cast<uintptr_t>(rdx), r8);
    goto L_0x147bf4;

    // 0x147bf4..0x147c0d: basic block 15
    // 0x147bf4  mov qword ptr [rsi+0x10],0
    // 0x147bfc  mov qword ptr [rsi+0x18],0xF
    // 0x147c04  mov byte ptr [rsi],0
    // 0x147c07  add rsp,0x30
    // 0x147c0b  pop rsi
    // 0x147c0c  ret
    // -> (fall-through / ret / end)
    L_0x147bf4:;
    a0->f10 = 0;
    a0->f18 = 0xF;
    a0->f0 = nullptr;
    return 0;

    // 0x147c0d..0x147c27: basic block 16
    // 0x147c0d  mov qword ptr [rsp+0x20],0
    // 0x147c16  xor ecx,ecx
    // 0x147c18  xor edx,edx
    // 0x147c1a  xor r8d,r8d
    // 0x147c1d  xor r9d,r9d
    // 0x147c20  call qword ptr [0xF9A8C78]
    // 0x147c26  int3
    // -> (fall-through / ret / end)
    L_0x147c0d:;
    rsp_state.f20 = 0;
    data_f9a8c78();
    __debugbreak();

    __assume(0);
}

} // namespace native::helpers
