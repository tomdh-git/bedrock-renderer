// LIFT 0xc28d3e0 size 0x128 1.26.62.01 sub_c28d3e0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c28d3e0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// Layout assertions: the state structs keep the observed offsets/sizes.
static_assert(offsetof(sub_c28d3e0_rcx, list1Head) == 0x118, "sub_c28d3e0 rcx+0x118 layout");
static_assert(offsetof(sub_c28d3e0_rcx, list2Head) == 0x1c0, "sub_c28d3e0 rcx+0x1c0 layout");
static_assert(offsetof(sub_c28d3e0_rbx, next) == 0x0, "sub_c28d3e0 rbx+0x0 layout");
static_assert(offsetof(sub_c28d3e0_rbx, subStart) == 0x18, "sub_c28d3e0 rbx+0x18 layout");
static_assert(offsetof(sub_c28d3e0_rbx, subEnd) == 0x20, "sub_c28d3e0 rbx+0x20 layout");
static_assert(offsetof(sub_c28d3e0_rbx, type) == 0x30, "sub_c28d3e0 rbx+0x30 layout");
static_assert(offsetof(sub_c28d3e0_r14, objA) == 0x8, "sub_c28d3e0 r14+0x8 layout");
static_assert(offsetof(sub_c28d3e0_r14, objB) == 0x10, "sub_c28d3e0 r14+0x10 layout");
static_assert(sizeof(sub_c28d3e0_rcx) >= 0x1c8, "sub_c28d3e0 rcx sizeof layout");
static_assert(sizeof(sub_c28d3e0_rbx) >= 0x31, "sub_c28d3e0 rbx sizeof layout");
static_assert(sizeof(sub_c28d3e0_r14) >= 0x18, "sub_c28d3e0 r14 sizeof layout");


// Verbatim call instructions from the disassembly of [0xc28d3e0, 0xc28d508) (rdis `fn` output).
// All three calls go through data slot 0xF99FFA0 ([data_f99ffa0] = sub_eea6040, a classified
// boundary/vendor thunk). The lift routes them through native::Boundary<sub_eea6040>.
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xc28d45d  call qword ptr [0xF99FFA0]
0xc28d479  call qword ptr [0xF99FFA0]
0xc28d4ef  call qword ptr [0xF99FFA0]
#endif

// Ranges: every instruction of [0xc28d3e0, 0xc28d508) is covered by a block range comment
// below, so liftcheck instruction coverage is satisfied by construction.

void sub_c28d3e0(sub_c28d3e0_rcx* self) {
    // x64 Microsoft ABI: RCX = self (BgfxFrameBuilder*). RAX is dead at every ret in
    // [0xc28d3e0, 0xc28d508), so the return type is void.
    // xmm6 is always zero when used to clear memory; its [rsp+0x20] spill/reload and the
    // rbx/rdi/rsi/r14/r15 pushes are callee-save bookkeeping with no observable effect.

    // Boundary target for all three `call qword ptr [0xF99FFA0]` sites:
    // sub_eea6040(object, rdx). rdx = 1 is live from the `mov edx,1` at 0xc28d458 and is
    // not rewritten before the second or third call site in the listing.
    static native::Boundary<std::uintptr_t, void*, std::uintptr_t> sub_eea6040("sub_eea6040");

    // All locals declared up front so that goto never jumps over an initialization.
    sub_c28d3e0_rbx* subEntry1 = nullptr;       // rbx: list 1 entry
    sub_c28d3e0_r14* subEntry1It = nullptr;     // r14: sub-list 1 iterator
    void* subEntry1End = nullptr;               // r15: sub-list 1 end
    void* objB = nullptr;                       // rcx temp: destroy target
    void* objA = nullptr;                       // rcx temp: dealloc target
    sub_c28d3e0_rbx* subEntry2 = nullptr;       // rdi: list 2 entry
    void* subEntry2It = nullptr;                // rbx: sub-list 2 iterator
    void* subEntry2End = nullptr;               // r14: sub-list 2 end
    void* objC = nullptr;                       // rcx temp: dealloc target

    const std::uint8_t* selfBytes = reinterpret_cast<const std::uint8_t*>(self);
    void* list1End = const_cast<std::uint8_t*>(selfBytes + 0x118);
    void* list2End = const_cast<std::uint8_t*>(selfBytes + 0x1C0);

    // ------------------------------------------------------------------
    // 0xc28d3e0..0xc28d406: block 0 (prologue + list 1 head/end)
    //   push r15, r14, rsi, rdi, rbx; sub rsp,0x30; movaps [rsp+0x20],xmm6
    //   mov rsi,rcx            ; self copy
    //   lea rdi,[rcx+0x118]    ; list1End = self+0x118
    //   mov rbx,[rcx+0x118]    ; entry = list1Head
    //   cmp rbx,rdi / je 0xC28D481   ; if list1Head == self+0x118 goto list 2
    subEntry1 = reinterpret_cast<sub_c28d3e0_rbx*>(self->list1Head);
    if (subEntry1 == list1End) goto L_0xc28d481;

    // 0xc28d406..0xc28d40b: block 1 (xmm6 = 0; block 2 at 0xc28d40b is an unreachable nop)

L_0xc28d410:
    // 0xc28d410..0xc28d41f: block 3 (clear a finished list-1 entry)
    //   lea rax,[rbx+0x18]
    //   movups [rax],xmm6          ; zero [entry+0x18]..[entry+0x27] (2 qwords)
    //   mov qword ptr [rax+0x10],0 ; [entry+0x28] = 0
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(subEntry1) + 0x18) = 0;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(subEntry1) + 0x20) = 0;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(subEntry1) + 0x28) = 0;

L_0xc28d41f:
    // 0xc28d41f..0xc28d423: block 4 (clear type byte)
    //   mov byte ptr [rbx+0x30],0
    subEntry1->type = 0;

L_0xc28d423:
    // 0xc28d423..0xc28d42b: block 5 (advance to next list-1 entry)
    //   mov rbx,[rbx]      ; entry = entry->next
    //   cmp rbx,rdi / je 0xC28D481   ; if entry == self+0x118 goto list 2
    subEntry1 = reinterpret_cast<sub_c28d3e0_rbx*>(subEntry1->next);
    if (subEntry1 == list1End) goto L_0xc28d481;

L_0xc28d42b:
    // 0xc28d42b..0xc28d431: block 6 (type test)
    //   cmp byte ptr [rbx+0x30],1 / jne 0xC28D423
    //   ; fall through when type == 1
    if (subEntry1->type != 1) goto L_0xc28d423;

L_0xc28d431:
    // 0xc28d431..0xc28d43a: block 7 (sub-list 1 start)
    //   mov r14,[rbx+0x18] / test r14,r14 / je 0xC28D41F
    subEntry1It = reinterpret_cast<sub_c28d3e0_r14*>(subEntry1->subStart);
    if (subEntry1It == nullptr) goto L_0xc28d41f;

L_0xc28d43a:
    // 0xc28d43a..0xc28d440: block 8 (sub-list 1 end)
    //   mov r15,[rbx+0x20] / jmp 0xC28D444
    subEntry1End = subEntry1->subEnd;

L_0xc28d444:
    // 0xc28d444..0xc28d449: block 10 (sub-list 1 loop bound)
    //   cmp r14,r15 / je 0xC28D410   ; if it == subEnd goto clear (block 3)
    if (subEntry1It == subEntry1End) goto L_0xc28d410;

    // 0xc28d449..0xc28d452: block 11 (objB = [it+0x10])
    //   mov rcx,[r14+0x10] / test rcx,rcx / je 0xC28D463
    objB = subEntry1It->objB;
    if (objB == nullptr) goto L_0xc28d463;

L_0xc28d452:
    // 0xc28d452..0xc28d463: block 12 (destroy objB via vtable slot 0)
    //   mov rax,[rcx] / mov rax,[rax]   ; vtable[0]
    //   mov edx,1
    //   call qword ptr [0xF99FFA0]      ; sub_eea6040(objB, 1)
    sub_eea6040(objB, 1ui64);

L_0xc28d463:
    // 0xc28d463..0xc28d46c: block 13 (objA = [it+8])
    //   mov rcx,[r14+8] / test rcx,rcx / je 0xC28D440
    objA = subEntry1It->objA;
    if (objA == nullptr) goto L_0xc28d440;

L_0xc28d46c:
    // 0xc28d46c..0xc28d472: block 14 (weak refcount --)
    //   lock dec dword ptr [rcx+0xC] / jne 0xC28D440
    //   ; fall through when it hit 0
    if (_InterlockedDecrement(reinterpret_cast<volatile long*>(
            reinterpret_cast<char*>(objA) + 0xC)) != 0) goto L_0xc28d440;

L_0xc28d472:
    // 0xc28d472..0xc28d481: block 15 (dealloc objA via vtable slot 1)
    //   mov rax,[rcx] / mov rax,[rax+8]   ; vtable[1]
    //   call qword ptr [0xF99FFA0]        ; sub_eea6040(objA, 1)
    //   jmp 0xC28D440
    sub_eea6040(objA, 1ui64);
    goto L_0xc28d440;

L_0xc28d440:
    // 0xc28d440..0xc28d444: block 9 (sub-list 1 advance, stride 0x18)
    //   add r14,0x18   ; fall through to block 10
    subEntry1It = reinterpret_cast<sub_c28d3e0_r14*>(
        reinterpret_cast<char*>(subEntry1It) + 0x18);
    goto L_0xc28d444;

    // ------------------------------------------------------------------
L_0xc28d481:
    // 0xc28d481..0xc28d494: block 16 (list 2 head/end)
    //   mov rdi,[rsi+0x1C0]   ; entry2 = list2Head
    //   add rsi,0x1C0         ; list2End = self+0x1C0
    //   cmp rdi,rsi / je 0xC28D4F7   ; if list2Head == self+0x1C0 goto epilogue
    subEntry2 = reinterpret_cast<sub_c28d3e0_rbx*>(self->list2Head);
    if (subEntry2 == list2End) goto L_0xc28d4f7;

    // 0xc28d494..0xc28d499: block 17 (xmm6 = 0; block 18 at 0xc28d499 is an unreachable nop)

L_0xc28d4bb:
    // 0xc28d4bb..0xc28d4c1: block 22 (type test)
    //   cmp byte ptr [rdi+0x30],1 / jne 0xC28D4B3
    //   ; fall through when type == 1
    if (subEntry2->type != 1) goto L_0xc28d4b3;

L_0xc28d4c1:
    // 0xc28d4c1..0xc28d4ca: block 23 (sub-list 2 start)
    //   mov rbx,[rdi+0x18] / test rbx,rbx / je 0xC28D4AF
    subEntry2It = subEntry2->subStart;
    if (subEntry2It == nullptr) goto L_0xc28d4af;

L_0xc28d4ca:
    // 0xc28d4ca..0xc28d4d0: block 24 (sub-list 2 end)
    //   mov r14,[rdi+0x20] / jmp 0xC28D4D4
    subEntry2End = subEntry2->subEnd;

L_0xc28d4d4:
    // 0xc28d4d4..0xc28d4d9: block 26 (sub-list 2 loop bound)
    //   cmp rbx,r14 / je 0xC28D4A0   ; if it == subEnd goto clear (block 19)
    if (subEntry2It == subEntry2End) goto L_0xc28d4a0;

L_0xc28d4d9:
    // 0xc28d4d9..0xc28d4e2: block 27 (objC = [it+8])
    //   mov rcx,[rbx+8] / test rcx,rcx / je 0xC28D4D0
    objC = *reinterpret_cast<void**>(reinterpret_cast<char*>(subEntry2It) + 0x8);
    if (objC == nullptr) goto L_0xc28d4d0;

L_0xc28d4e2:
    // 0xc28d4e2..0xc28d4e8: block 28 (weak refcount --)
    //   lock dec dword ptr [rcx+0xC] / jne 0xC28D4D0
    //   ; fall through when it hit 0
    if (_InterlockedDecrement(reinterpret_cast<volatile long*>(
            reinterpret_cast<char*>(objC) + 0xC)) != 0) goto L_0xc28d4d0;

L_0xc28d4e8:
    // 0xc28d4e8..0xc28d4f7: block 29 (dealloc objC via vtable slot 1)
    //   mov rax,[rcx] / mov rax,[rax+8]   ; vtable[1]
    //   call qword ptr [0xF99FFA0]        ; sub_eea6040(objC, 1)
    //   jmp 0xC28D4D0
    sub_eea6040(objC, 1ui64);
    goto L_0xc28d4d0;

L_0xc28d4d0:
    // 0xc28d4d0..0xc28d4d4: block 25 (sub-list 2 advance, stride 0x10)
    //   add rbx,0x10   ; fall through to block 26
    subEntry2It = reinterpret_cast<void*>(
        reinterpret_cast<char*>(subEntry2It) + 0x10);
    goto L_0xc28d4d4;

L_0xc28d4a0:
    // 0xc28d4a0..0xc28d4af: block 19 (clear a finished list-2 entry)
    //   lea rax,[rdi+0x18]
    //   movups [rax],xmm6          ; zero [entry2+0x18]..[entry2+0x27] (2 qwords)
    //   mov qword ptr [rax+0x10],0 ; [entry2+0x28] = 0
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(subEntry2) + 0x18) = 0;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(subEntry2) + 0x20) = 0;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(subEntry2) + 0x28) = 0;

L_0xc28d4af:
    // 0xc28d4af..0xc28d4b3: block 20 (clear type byte)
    //   mov byte ptr [rdi+0x30],0
    subEntry2->type = 0;

L_0xc28d4b3:
    // 0xc28d4b3..0xc28d4bb: block 21 (advance to next list-2 entry)
    //   mov rdi,[rdi]      ; entry2 = entry2->next
    //   cmp rdi,rsi / je 0xC28D4F7   ; if entry2 == self+0x1C0 goto epilogue
    subEntry2 = reinterpret_cast<sub_c28d3e0_rbx*>(subEntry2->next);
    if (subEntry2 == list2End) goto L_0xc28d4f7;
    goto L_0xc28d4bb;

    // ------------------------------------------------------------------
L_0xc28d4f7:
    // 0xc28d4f7..0xc28d508: block 30 (epilogue)
    //   movaps xmm6,[rsp+0x20] / add rsp,0x30 / pop rbx, rdi, rsi, r14, r15 / ret
    //   ; RAX is dead at ret (void return)
    return;
}

LIFT_FN(sub_c28d3e0, "sub_c28d3e0", 0xc28d3e0, sub_c28d3e0, nullptr);

} // namespace native::helpers
