// LIFT 0x8db490 size 0x119 1.26.62.01 sub_8db490
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_8db490.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// sub_e935700 (0xe935700, size 0x5): lift-set callee, tail jump to sub_392960.
// Forward-declared here and called through its native symbol. sub_e935700.h is
// not included: its sizeof(own-layout) static_assert is not cppsyntax-safe.
namespace native {
void* sub_e935700(void* a0);
}

namespace native::helpers {

LIFT_FN(sub_8db490, "sub_8db490", 0x8db490, sub_8db490, nullptr);

// Verbatim call instructions from the disassembly of [0x8db490, 0x8db5a9) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x8db4d2  call 0xE935700
0x8db521  call 0xE935700
0x8db570  call 0xE935700
0x8db5a2  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x8db490, 0x8db5a9) is covered by a block range comment
// and/or a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

void sub_8db490(void* self_) {
    auto self = static_cast<sub_8db490_rcx*>(self_);

    uint64_t rax = 0;         // running size value
    void* rcx = nullptr;      // heap pointer / first argument slot
    [[maybe_unused]] uint64_t rdx = 0; // second argument slot (set by the caller, unused by sub_e935700)
    uint64_t r8 = 0;          // [ptr - 8] heap metadata

    // 0x8db490..0x8db4a2: basic block 0
    // 0x8db490  push rsi
    // 0x8db491  sub rsp,0x30
    // 0x8db495  mov rsi,rcx
    // 0x8db498  mov rax,[rcx+0x68]
    // 0x8db49c  cmp rax,0x10
    // 0x8db4a0  jb short 0x8DB4D7
    // -> if *(a0+0x68) <u 0x10 goto L_0x8db4d7
    // -> if *(a0+0x68) >=u 0x10 goto L_0x8db4a2
    L_0x8db490:;
    rax = self->size_a;
    if (rax < 0x10) goto L_0x8db4d7;

    // 0x8db4a2..0x8db4b3: basic block 1
    // 0x8db4a2  mov rcx,[rsi+0x50]
    // 0x8db4a6  lea rdx,[rax+1]
    // 0x8db4aa  cmp rdx,0x1000
    // 0x8db4b1  jb short 0x8DB4D2
    // -> if *(a0+0x68)+0x1 <u 0x1000 goto L_0x8db4d2
    // -> if *(a0+0x68)+0x1 >=u 0x1000 goto L_0x8db4b3
    L_0x8db4a2:;
    rcx = self->ptr_a;
    rdx = rax + 1;
    if (rdx < 0x1000) goto L_0x8db4d2;

    // 0x8db4b3..0x8db4c8: basic block 2
    // 0x8db4b3  mov r8,[rcx-8]
    // 0x8db4b7  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x8db4bb  sub rcx,r8
    // 0x8db4be  cmp rcx,0x20
    // 0x8db4c2  jae 0x8DB58F
    // -> if (*(a0+0x50)-0x8 - *(*(a0+0x50)-0x8)) >=u 0x20 goto L_0x8db58f
    // -> if (*(a0+0x50)-0x8 - *(*(a0+0x50)-0x8)) <u 0x20 goto L_0x8db4c8
    L_0x8db4b3:;
    r8 = *reinterpret_cast<const std::uint64_t*>(reinterpret_cast<std::uintptr_t>(rcx) - 8);
    if (((reinterpret_cast<std::uintptr_t>(rcx) - 8) - r8) >= 0x20) goto L_0x8db58f;

    // 0x8db4c8..0x8db4d2: basic block 3
    // 0x8db4c8  add rax,0x28
    // 0x8db4cc  mov rdx,rax
    // 0x8db4cf  mov rcx,r8
    // -> if fallthrough goto L_0x8db4d2
    L_0x8db4c8:;
    rax = rax + 0x28;
    rdx = rax;
    rcx = reinterpret_cast<void*>(r8);
    goto L_0x8db4d2;

    // 0x8db4d2..0x8db4d7: basic block 4
    // 0x8db4d2  call 0xE935700
    // -> if fallthrough goto L_0x8db4d7
    L_0x8db4d2:;
    native::sub_e935700(rcx);

    // 0x8db4d7..0x8db4f5: basic block 5
    // 0x8db4d7  mov qword ptr [rsi+0x60],0
    // 0x8db4df  mov qword ptr [rsi+0x68],0xF
    // 0x8db4e7  mov byte ptr [rsi+0x50],0
    // 0x8db4eb  mov rax,[rsi+0x48]
    // 0x8db4ef  cmp rax,0x10
    // 0x8db4f3  jb short 0x8DB526
    // -> if *(a0+0x48) <u 0x10 goto L_0x8db526
    // -> if *(a0+0x48) >=u 0x10 goto L_0x8db4f5
    L_0x8db4d7:;
    self->buf_a = 0;
    self->size_a = 0xF;
    *reinterpret_cast<std::uint8_t*>(&self->ptr_a) = 0;
    rax = self->size_b;
    if (rax < 0x10) goto L_0x8db526;

    // 0x8db4f5..0x8db506: basic block 6
    // 0x8db4f5  mov rcx,[rsi+0x30]
    // 0x8db4f9  lea rdx,[rax+1]
    // 0x8db4fd  cmp rdx,0x1000
    // 0x8db504  jb short 0x8DB521
    // -> if *(a0+0x48)+0x1 <u 0x1000 goto L_0x8db521
    // -> if *(a0+0x48)+0x1 >=u 0x1000 goto L_0x8db506
    L_0x8db4f5:;
    rcx = self->ptr_b;
    rdx = rax + 1;
    if (rdx < 0x1000) goto L_0x8db521;

    // 0x8db506..0x8db517: basic block 7
    // 0x8db506  mov r8,[rcx-8]
    // 0x8db50a  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x8db50e  sub rcx,r8
    // 0x8db511  cmp rcx,0x20
    // 0x8db515  jae short 0x8DB58F
    // -> if (*(a0+0x30)-0x8 - *(*(a0+0x30)-0x8)) >=u 0x20 goto L_0x8db58f
    // -> if (*(a0+0x30)-0x8 - *(*(a0+0x30)-0x8)) <u 0x20 goto L_0x8db517
    L_0x8db506:;
    r8 = *reinterpret_cast<const std::uint64_t*>(reinterpret_cast<std::uintptr_t>(rcx) - 8);
    if (((reinterpret_cast<std::uintptr_t>(rcx) - 8) - r8) >= 0x20) goto L_0x8db58f;

    // 0x8db517..0x8db521: basic block 8
    // 0x8db517  add rax,0x28
    // 0x8db51b  mov rdx,rax
    // 0x8db51e  mov rcx,r8
    // -> if fallthrough goto L_0x8db521
    L_0x8db517:;
    rax = rax + 0x28;
    rdx = rax;
    rcx = reinterpret_cast<void*>(r8);
    goto L_0x8db521;

    // 0x8db521..0x8db526: basic block 9
    // 0x8db521  call 0xE935700
    // -> if fallthrough goto L_0x8db526
    L_0x8db521:;
    native::sub_e935700(rcx);

    // 0x8db526..0x8db544: basic block 10
    // 0x8db526  mov qword ptr [rsi+0x40],0
    // 0x8db52e  mov qword ptr [rsi+0x48],0xF
    // 0x8db536  mov byte ptr [rsi+0x30],0
    // 0x8db53a  mov rax,[rsi+0x20]
    // 0x8db53e  cmp rax,0x10
    // 0x8db542  jb short 0x8DB575
    // -> if *(a0+0x20) <u 0x10 goto L_0x8db575
    // -> if *(a0+0x20) >=u 0x10 goto L_0x8db544
    L_0x8db526:;
    self->buf_b = 0;
    self->size_b = 0xF;
    *reinterpret_cast<std::uint8_t*>(&self->ptr_b) = 0;
    rax = self->size_c;
    if (rax < 0x10) goto L_0x8db575;

    // 0x8db544..0x8db555: basic block 11
    // 0x8db544  mov rcx,[rsi+8]
    // 0x8db548  lea rdx,[rax+1]
    // 0x8db54c  cmp rdx,0x1000
    // 0x8db553  jb short 0x8DB570
    // -> if *(a0+0x20)+0x1 <u 0x1000 goto L_0x8db570
    // -> if *(a0+0x20)+0x1 >=u 0x1000 goto L_0x8db555
    L_0x8db544:;
    rcx = self->ptr_c;
    rdx = rax + 1;
    if (rdx < 0x1000) goto L_0x8db570;

    // 0x8db555..0x8db566: basic block 12
    // 0x8db555  mov r8,[rcx-8]
    // 0x8db559  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x8db55d  sub rcx,r8
    // 0x8db560  cmp rcx,0x20
    // 0x8db564  jae short 0x8DB58F
    // -> if (*(a0+0x8)-0x8 - *(*(a0+0x8)-0x8)) >=u 0x20 goto L_0x8db58f
    // -> if (*(a0+0x8)-0x8 - *(*(a0+0x8)-0x8)) <u 0x20 goto L_0x8db566
    L_0x8db555:;
    r8 = *reinterpret_cast<const std::uint64_t*>(reinterpret_cast<std::uintptr_t>(rcx) - 8);
    if (((reinterpret_cast<std::uintptr_t>(rcx) - 8) - r8) >= 0x20) goto L_0x8db58f;

    // 0x8db566..0x8db570: basic block 13
    // 0x8db566  add rax,0x28
    // 0x8db56a  mov rdx,rax
    // 0x8db56d  mov rcx,r8
    // -> if fallthrough goto L_0x8db570
    L_0x8db566:;
    rax = rax + 0x28;
    rdx = rax;
    rcx = reinterpret_cast<void*>(r8);
    goto L_0x8db570;

    // 0x8db570..0x8db575: basic block 14
    // 0x8db570  call 0xE935700
    // -> if fallthrough goto L_0x8db575
    L_0x8db570:;
    native::sub_e935700(rcx);

    // 0x8db575..0x8db58f: basic block 15
    // 0x8db575  mov qword ptr [rsi+0x18],0
    // 0x8db57d  mov qword ptr [rsi+0x20],0xF
    // 0x8db585  mov byte ptr [rsi+8],0
    // 0x8db589  add rsp,0x30
    // 0x8db58d  pop rsi
    // 0x8db58e  ret
    // -> (fall-through / ret / end)
    L_0x8db575:;
    self->buf_c = 0;
    self->size_c = 0xF;
    *reinterpret_cast<std::uint8_t*>(&self->ptr_c) = 0;
    return;

    // 0x8db58f..0x8db5a9: basic block 16
    // 0x8db58f  mov qword ptr [rsp+0x20],0
    // 0x8db598  xor ecx,ecx
    // 0x8db59a  xor edx,edx
    // 0x8db59c  xor r8d,r8d
    // 0x8db59f  xor r9d,r9d
    // 0x8db5a2  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
    // 0x8db5a8  int3
    // -> (fall-through / ret / end)
    L_0x8db58f:;
    {
        // [rsp+0x20] home slot is not observable here; ecx/edx/r8/r9 are zeroed,
        // i.e. the data-slot function is called with no arguments.
        auto slot_fn = reinterpret_cast<void(__cdecl *)()>(
            *reinterpret_cast<std::uintptr_t*>(0xF9A8C78ULL));
        slot_fn();
    }
    // 0x8db5a8 int3 follows in the exe; the slot call does not return.
    __assume(false);
}

} // namespace native::helpers
