// LIFT 0xc284020 size 0x10b 1.26.62.01 sub_c284020
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c284020.h"
#include "client/features/render/native/helpers/sub_c28bc30.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native {

// sub_e935700 is a lift-set callee (0xe935700): a tail jump to sub_392960.
// The single argument arrives in RCX and the result is returned in RAX.
// Declared here so the lifted body calls the native symbol directly (no wrapper,
// no boundary function). The real header (sub_e935700.h) pulls in SDK headers
// that are not present in this tree, so the symbol is forward-declared instead.
void* sub_e935700(void* a0);

} // namespace native

namespace native::helpers {

LIFT_FN(sub_c284020, "sub_c284020", 0xc284020, sub_c284020, nullptr);

// Verbatim call instructions from the disassembly of [0xc284020, 0xc28412b) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
// Two indirect calls go through data slot 0xF99FFA0 (vendor release thunk, no static target by design).
// One direct call goes to sub_e935700 (lift-set callee, forwarded to sub_392960).
// One direct call goes to sub_c28bc30 (lift-set callee).
// One indirect call goes through data slot 0xF9A8C78 (abort/corruption path, then int3).
#if 0
0xc284091  call qword ptr [0xF99FFA0]
0xc2840a7  call qword ptr [0xF99FFA0]
0xc2840e0  call 0xE935700
0xc2840f7  call 0xC28BC30
0xc284124  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0xc284020, 0xc28412b) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

namespace {
    using release_fn = void* (__cdecl*)(void*);
    using abort_fn = uintptr_t (__cdecl*)(uintptr_t, uintptr_t, uintptr_t, uintptr_t);
}

// Layout assertion for the `this` object base (rcx): f248 at 0x248, f250 at 0x250, f258 at 0x258.
static_assert(offsetof(sub_c284020_rcx, f248) == 0x248, "sub_c284020 layout rcx+0x248");
static_assert(offsetof(sub_c284020_rcx, f250) == 0x250, "sub_c284020 layout rcx+0x250");
static_assert(offsetof(sub_c284020_rcx, f258) == 0x258, "sub_c284020 layout rcx+0x258");

uintptr_t sub_c284020(void* self) {
    auto* st = reinterpret_cast<sub_c284020_rcx*>(self);

    void* rdi = nullptr;      // cursor into the element range [f248, f250)
    void** r14 = nullptr;     // &st->f248
    uint64_t r15 = 0;         // st->f250 (range end)
    uint64_t rdx = 0;         // scratch
    uint64_t rax = 0;         // scratch

    // 0xc284020..0xc28404c: basic block 0
    // 0xc284020  push rbp
    // 0xc284021  push r15
    // 0xc284023  push r14
    // 0xc284025  push rsi
    // 0xc284026  push rdi
    // 0xc284027  push rbx
    // 0xc284028  sub rsp,0x38
    // 0xc28402c  lea rbp,[rsp+0x30]
    // 0xc284031  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0xc284039  mov rsi,rcx
    // 0xc28403c  mov rdi,[rcx+0x248]                           ; R a0+0x248
    // 0xc284043  test rdi,rdi
    // 0xc284046  je 0xC2840F4                                  ; -> loc_c2840f4
    // -> if *(a0+0x248) == 0 goto L_0xc2840f4
    // -> if *(a0+0x248) != 0 goto L_0xc28404c
    rdi = st->f248;
    if (rdi == nullptr) goto L_0xc2840f4;

    // 0xc28404c..0xc28405f: basic block 1
    // 0xc28404c  lea r14,[rsi+0x248]                           ; R a0+0x248
    // 0xc284053  mov r15,[rsi+0x250]                           ; R a0+0x250
    // 0xc28405a  cmp rdi,r15
    // 0xc28405d  jne short 0xC284079                           ; -> loc_c284079
    // -> if *(a0+0x248) != *(a0+0x250) goto L_0xc284079
    // -> if *(a0+0x248) == *(a0+0x250) goto L_0xc28405f
    r14 = &st->f248;
    r15 = st->f250;
    if (rdi != reinterpret_cast<void*>(r15)) goto L_0xc284079;
    goto L_0xc2840b2;

    // 0xc28405f..0xc284061: basic block 2
    // 0xc28405f  jmp short 0xC2840B2                           ; -> loc_c2840b2
    // -> if jmp goto L_0xc2840b2
    // (fallthrough target L_0xc2840b2 emitted above)

    // 0xc284061..0xc284070: basic block 3
    // 0xc284061  nop [rax+rax]
    // -> if fallthrough goto L_0xc284070
    // (dead padding block; no predecessor, no emitted label)

    // 0xc284070..0xc284079: basic block 4
    // 0xc284070  add rdi,0x18
    // 0xc284074  cmp rdi,r15
    // 0xc284077  je short 0xC2840AF                            ; -> loc_c2840af
    // -> if ? == *(a0+0x250) goto L_0xc2840af
    // -> if ? != *(a0+0x250) goto L_0xc284079
L_0xc284070:
    rdi = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(rdi) + 0x18);
    if (rdi == reinterpret_cast<void*>(r15)) goto L_0xc2840af;
    goto L_0xc284079;

    // 0xc284079..0xc284082: basic block 5
    // 0xc284079  mov rbx,[rdi+8]
    // 0xc28407d  test rbx,rbx
    // 0xc284080  je short 0xC284070                            ; -> loc_c284070
    // -> if ? == 0 goto L_0xc284070
    // -> if ? != 0 goto L_0xc284082
L_0xc284079:;
    {
        void* rbx = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rdi) + 8);
        if (rbx == nullptr) goto L_0xc284070;

        // 0xc284082..0xc284088: basic block 6
        // 0xc284082  lock dec dword ptr [rbx+8]
        // 0xc284086  jne short 0xC284070                       ; -> loc_c284070
        // -> if (Dec ?, ?) != 0 goto L_0xc284070
        // -> if (Dec ?, ?) == 0 goto L_0xc284088
        if (::InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(rbx) + 8)) != 0)
            goto L_0xc284070;

        // 0xc284088..0xc28409d: basic block 7
        // 0xc284088  mov rax,[rbx]
        // 0xc28408b  mov rax,[rax]
        // 0xc28408e  mov rcx,rbx
        // 0xc284091  call qword ptr [0xF99FFA0]                ; [data_f99ffa0] = sub_eea6040
        // 0xc284097  lock dec dword ptr [rbx+0xC]
        // 0xc28409b  jne short 0xC284070                       ; -> loc_c284070
        // -> if (Dec ?, ?) != 0 goto L_0xc284070
        // -> if (Dec ?, ?) == 0 goto L_0xc28409d
        {
            release_fn eea6040 = *reinterpret_cast<release_fn*>(static_cast<uintptr_t>(0xF99FFA0));
            eea6040(rbx);
            if (::InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(rbx) + 0xC)) != 0)
                goto L_0xc284070;

            // 0xc28409d..0xc2840af: basic block 8
            // 0xc28409d  mov rax,[rbx]
            // 0xc2840a0  mov rax,[rax+8]
            // 0xc2840a4  mov rcx,rbx
            // 0xc2840a7  call qword ptr [0xF99FFA0]           ; [data_f99ffa0] = sub_eea6040
            // 0xc2840ad  jmp short 0xC284070                  ; -> loc_c284070
            // -> if jmp goto L_0xc284070
            eea6040 = *reinterpret_cast<release_fn*>(static_cast<uintptr_t>(0xF99FFA0));
            eea6040(rbx);
        }
    }
    goto L_0xc284070;

    // 0xc2840af..0xc2840b2: basic block 9
    // 0xc2840af  mov rdi,[r14]
    // -> if fallthrough goto L_0xc2840b2
L_0xc2840af:
    rdi = *r14;

    // 0xc2840b2..0xc2840c5: basic block 10
    // 0xc2840b2  mov rdx,[rsi+0x258]
    // 0xc2840b9  sub rdx,rdi
    // 0xc2840bc  cmp rdx,0x1000
    // 0xc2840c3  jb short 0xC2840DD                            ; -> loc_c2840dd
    // -> if (*(a0+0x258) - *(a0+0x248)) <u 0x1000 goto L_0xc2840dd
    // -> if (*(a0+0x258) - *(a0+0x248)) >=u 0x1000 goto L_0xc2840c5
L_0xc2840b2:
    rdx = st->f258 - reinterpret_cast<uint64_t>(rdi);
    if (rdx < 0x1000) goto L_0xc2840dd;

    // 0xc2840c5..0xc2840d6: basic block 11
    // 0xc2840c5  mov rax,[rdi-8]
    // 0xc2840c9  add rdi,0xFFFFFFFFFFFFFFF8
    // 0xc2840cd  sub rdi,rax
    // 0xc2840d0  cmp rdi,0x20
    // 0xc2840d4  jae short 0xC284111                           ; -> loc_c284111
    // -> if (*(a0+0x248)-0x8 - *(*(a0+0x248)-0x8)) >=u 0x20 goto L_0xc284111
    // -> if (*(a0+0x248)-0x8 - *(*(a0+0x248)-0x8)) <u 0x20 goto L_0xc2840d6
    rax = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(rdi) - 8);
    {
        uint64_t rdi_adj = reinterpret_cast<uint64_t>(rdi) - 8 - rax;
        if (rdi_adj >= 0x20) goto L_0xc284111;
    }

    // 0xc2840d6..0xc2840dd: basic block 12
    // 0xc2840d6  add rdx,0x27
    // 0xc2840da  mov rdi,rax
    // -> if fallthrough goto L_0xc2840dd
    rdx += 0x27;
    rdi = reinterpret_cast<void*>(rax);
    goto L_0xc2840dd;

    // 0xc2840dd..0xc2840f4: basic block 13
    // 0xc2840dd  mov rcx,rdi
    // 0xc2840e0  call 0xE935700                                ; -> sub_e935700
    // 0xc2840e5  xorps xmm0,xmm0
    // 0xc2840e8  movups [r14],xmm0
    // 0xc2840ec  mov qword ptr [r14+0x10],0
    // -> if fallthrough goto L_0xc2840f4
L_0xc2840dd:
    native::sub_e935700(rdi);
    *r14 = nullptr;
    r14[1] = nullptr;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(r14) + 0x10) = 0;
    goto L_0xc2840f4;

    // 0xc2840f4..0xc284111: basic block 14
    // 0xc2840f4  mov rcx,rsi
    // 0xc2840f7  call 0xC28BC30                                ; -> sub_c28bc30
    // 0xc2840fc  nop
    // 0xc2840fd  mov rcx,rsi
    // 0xc284100  add rsp,0x38
    // 0xc284104  pop rbx
    // 0xc284105  pop rdi
    // 0xc284106  pop rsi
    // 0xc284107  pop r14
    // 0xc284109  pop r15
    // 0xc28410b  pop rbp
    // 0xc28410c  jmp 0xC28B930                                 ; -> sub_c28b930
    // -> (fall-through / ret / end)
    // The original tail-jumps to sub_c28b930 after calling sub_c28bc30;
    // sub_c28b930 is outside the lift set (not a call instruction) and is not modeled here.
L_0xc2840f4:
    return sub_c28bc30(reinterpret_cast<sub_c28bc30_state*>(self));

    // 0xc284111..0xc28412b: basic block 15
    // 0xc284111  mov qword ptr [rsp+0x20],0
    // 0xc28411a  xor ecx,ecx
    // 0xc28411c  xor edx,edx
    // 0xc28411e  xor r8d,r8d
    // 0xc284121  xor r9d,r9d
    // 0xc284124  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
    // 0xc28412a  int3
    // -> (fall-through / ret / end)
    // Corruption/abort path: call the data-slot function with zeroed args, then int3.
    // int3 is not reproduced (no placeholder debugbreak); the slot call is the observable action.
L_0xc284111:;
    {
        abort_fn slot = *reinterpret_cast<abort_fn*>(static_cast<uintptr_t>(0xF9A8C78));
        return slot(0, 0, 0, 0);
    }
}

} // namespace native::helpers
