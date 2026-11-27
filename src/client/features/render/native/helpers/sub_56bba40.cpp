// LIFT 0x56bba40 size 0x119 1.26.62.01 sub_56bba40
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_56bba40.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>
#include <emmintrin.h>

namespace native::helpers {

// Layout assertions mirrored from sub_56bba40.h (liftcheck scans the .cpp source).
static_assert(offsetof(sub_56bba40_rcx, sink) == 0x0, "sub_0x56bba40 rcx+0x0 field");
static_assert(sizeof(sub_56bba40_rcx) >= 0x8, "sub_0x56bba40 rcx sizeof lower bound");
static_assert(offsetof(sub_56bba40_rdx, object) == 0x0, "sub_0x56bba40 rdx+0x0 field");
static_assert(offsetof(sub_56bba40_rdx, control) == 0x8, "sub_0x56bba40 rdx+0x8 field");
static_assert(offsetof(sub_56bba40_rdx, state) == 0x18, "sub_0x56bba40 rdx+0x18 field");
static_assert(sizeof(sub_56bba40_rdx) >= 0x19, "sub_0x56bba40 rdx sizeof lower bound");
static_assert(offsetof(sub_56bba40_r8, strong) == 0x8, "sub_0x56bba40 r8+0x8 field");
static_assert(sizeof(sub_56bba40_r8) >= 0xc, "sub_0x56bba40 r8 sizeof lower bound");
static_assert(offsetof(sub_56bba40_rax, object) == 0x0, "sub_0x56bba40 rax+0x0 field");
static_assert(offsetof(sub_56bba40_rax, control) == 0x8, "sub_0x56bba40 rax+0x8 field");
static_assert(offsetof(sub_56bba40_rax, state) == 0x18, "sub_0x56bba40 rax+0x18 field");
static_assert(sizeof(sub_56bba40_rax) >= 0x19, "sub_0x56bba40 rax sizeof lower bound");
static_assert(offsetof(sub_56bba40_rdi, object) == 0x0, "sub_0x56bba40 rdi+0x0 field");
static_assert(offsetof(sub_56bba40_rdi, control) == 0x8, "sub_0x56bba40 rdi+0x8 field");
static_assert(offsetof(sub_56bba40_rdi, state) == 0x18, "sub_0x56bba40 rdi+0x18 field");
static_assert(sizeof(sub_56bba40_rdi) >= 0x19, "sub_0x56bba40 rdi sizeof lower bound");
static_assert(offsetof(sub_56bba40_rsi, vftable) == 0x0, "sub_0x56bba40 rsi+0x0 field");
static_assert(offsetof(sub_56bba40_rsi, strong) == 0x8, "sub_0x56bba40 rsi+0x8 field");
static_assert(offsetof(sub_56bba40_rsi, weak) == 0xc, "sub_0x56bba40 rsi+0xc field");
static_assert(sizeof(sub_56bba40_rsi) >= 0x10, "sub_0x56bba40 rsi sizeof lower bound");

LIFT_FN(sub_56bba40, "sub_56bba40", 0x56bba40, sub_56bba40, nullptr);

// Boundary callee: sub_eea6040, vendor thunk reached through data slot 0xF99FFA0.
// The thunk is `jmp rax`, so RAX receives the vtable entry and RCX the control block.
// The four uses here are: slot[0] destructor (0x56bbac1, 0x56bbb2c) and slot[1]
// deallocator (0x56bbadd, 0x56bbb56). Return value ignored.
native::Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// Verbatim call instructions from the disassembly of [0x56bba40, 0x56bbb59) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x56bbac1  call qword ptr [0xF99FFA0]
0x56bbadd  call qword ptr [0xF99FFA0]
0x56bbb2c  call qword ptr [0xF99FFA0]
#endif

void sub_56bba40(void* a0, void* a1) {
    static_assert(sizeof(void*) == 8, "sub_56bba40: x64 pointers are 8 bytes");

    auto* const arg0 = reinterpret_cast<sub_56bba40_rcx*>(a0);
    auto* const arg1 = reinterpret_cast<sub_56bba40_rdx*>(a1);

    sub_56bba40_rdi* sink = nullptr;      // rdi = *a0
    sub_56bba40_rdx* dst = nullptr;       // rdx after `mov rdx,[rcx]`
    sub_56bba40_rax* pair = nullptr;      // rax = a1->object
    sub_56bba40_rsi* ctrl = nullptr;      // rcx = pair->control
    sub_56bba40_rsi* oldCtrl = nullptr;   // rsi = sink->control
    void** vftable = nullptr;             // [rsi] -> vtable
    void* object = nullptr;               // [pair] / slot value
    std::uint8_t state = 0;               // byte at *a0+0x18

    // 0x56bba40..0x56bba56: basic block 0
    // 0x56bba40  push r14
    // 0x56bba42  push rsi
    // 0x56bba43  push rdi
    // 0x56bba44  push rbx
    // 0x56bba45  sub rsp,0x28
    // 0x56bba49  mov rdi,[rcx]
    // 0x56bba4c  movzx eax,byte ptr [rdi+0x18]
    // 0x56bba50  cmp rax,4
    // 0x56bba54  ja short 0x56BBA66
    sink = reinterpret_cast<sub_56bba40_rdi*>(arg0->sink);   // 0x56bba49  mov rdi,[rcx]
    state = sink->state;                                     // 0x56bba4c  movzx eax,byte ptr [rdi+0x18]
    if (state > 4) goto L_0x56bba66;                         // 0x56bba50  cmp rax,4
                                                             // 0x56bba54  ja short 0x56BBA66

    // 0x56bba56..0x56bba66: basic block 1
    // 0x56bba56  lea r8,[0xF25D32C]
    // 0x56bba5d  movsxd rax,[r8+rax*4]
    // 0x56bba61  add rax,r8
    // 0x56bba64  jmp rax
    // Jump table 0xF25D32C: tag 1 -> 0x56bbaee, tag 2 -> 0x56bbaa3, tags 0/3/4 -> 0x56bba66.
    switch (state) {
    case 1: goto L_0x56bbaee;
    case 2: goto L_0x56bbaa3;
    default: goto L_0x56bba66;
    }

    // 0x56bba66..0x56bba7f: basic block 2
    // 0x56bba66  mov byte ptr [rdi+0x18],0xFF
    // 0x56bba6a  mov rax,[rdx]
    // 0x56bba6d  mov rdx,[rcx]
    // 0x56bba70  xorps xmm0,xmm0
    // 0x56bba73  movups [rdx],xmm0
    // 0x56bba76  mov r8,[rax+8]
    // 0x56bba7a  test r8,r8
    // 0x56bba7d  je short 0x56BBA84
L_0x56bba66:;
    sink->state = 0xFF;                                      // 0x56bba66  mov byte ptr [rdi+0x18],0xFF
    pair = reinterpret_cast<sub_56bba40_rax*>(arg1->object); // 0x56bba6a  mov rax,[rdx]
    dst = reinterpret_cast<sub_56bba40_rdx*>(arg0->sink);    // 0x56bba6d  mov rdx,[rcx]
    _mm_storeu_si128(reinterpret_cast<__m128i*>(dst),        // 0x56bba70  xorps xmm0,xmm0
                     _mm_setzero_si128());                   // 0x56bba73  movups [rdx],xmm0
    ctrl = reinterpret_cast<sub_56bba40_rsi*>(pair->control);// 0x56bba76  mov r8,[rax+8]
    if (ctrl == nullptr) goto L_0x56bba84;                   // 0x56bba7a  test r8,r8
                                                             // 0x56bba7d  je short 0x56BBA84

    // 0x56bba7f..0x56bba84: basic block 3
    // 0x56bba7f  lock inc dword ptr [r8+8]
    _InterlockedIncrement(reinterpret_cast<volatile long*>(&ctrl->strong));  // 0x56bba7f  lock inc dword ptr [r8+8]

    // 0x56bba84..0x56bba99: basic block 4
    // 0x56bba84  mov r8,[rax]
    // 0x56bba87  mov [rdx],r8
    // 0x56bba8a  mov rax,[rax+8]
    // 0x56bba8e  mov [rdx+8],rax
    // 0x56bba92  mov rax,[rcx]
    // 0x56bba95  mov byte ptr [rax+0x18],1
L_0x56bba84:;
    object = pair->object;                                   // 0x56bba84  mov r8,[rax]
    dst->object = object;                                    // 0x56bba87  mov [rdx],r8
    ctrl = reinterpret_cast<sub_56bba40_rsi*>(pair->control);// 0x56bba8a  mov rax,[rax+8]
    dst->control = ctrl;                                     // 0x56bba8e  mov [rdx+8],rax
    reinterpret_cast<sub_56bba40_rdi*>(arg0->sink)->state = 1;  // 0x56bba92  mov rax,[rcx]
                                                             // 0x56bba95  mov byte ptr [rax+0x18],1

    // 0x56bba99..0x56bbaa3: basic block 5
    // 0x56bba99  add rsp,0x28
    // 0x56bba9d  pop rbx
    // 0x56bba9e  pop rdi
    // 0x56bba9f  pop rsi
    // 0x56bbaa0  pop r14
    // 0x56bbaa2  ret
L_0x56bba99:;
    return;

    // 0x56bbaa3..0x56bbaac: basic block 6
    // 0x56bbaa3  mov rsi,[rdi+8]
    // 0x56bbaa7  test rsi,rsi
    // 0x56bbaaa  je short 0x56BBA66
L_0x56bbaa3:;
    oldCtrl = reinterpret_cast<sub_56bba40_rsi*>(sink->control);  // 0x56bbaa3  mov rsi,[rdi+8]
    if (oldCtrl == nullptr) goto L_0x56bba66;                // 0x56bbaa7  test rsi,rsi
                                                             // 0x56bbaaa  je short 0x56BBA66

    // 0x56bbaac..0x56bbab2: basic block 7
    // 0x56bbaac  lock dec dword ptr [rsi+8]
    // 0x56bbab0  jne short 0x56BBA66
    if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&oldCtrl->strong)) != 0)  // 0x56bbaac  lock dec dword ptr [rsi+8]
        goto L_0x56bba66;                                    // 0x56bbab0  jne short 0x56BBA66

    // 0x56bbab2..0x56bbad3: basic block 8
    // 0x56bbab2  mov rax,[rsi]
    // 0x56bbab5  mov rax,[rax]
    // 0x56bbab8  mov rbx,rcx
    // 0x56bbabb  mov rcx,rsi
    // 0x56bbabe  mov r14,rdx
    // 0x56bbac1  call qword ptr [0xF99FFA0]
    // 0x56bbac7  mov rdx,r14
    // 0x56bbaca  mov rcx,rbx
    // 0x56bbacd  lock dec dword ptr [rsi+0xC]
    // 0x56bbad1  jne short 0x56BBA66
    vftable = oldCtrl->vftable;                              // 0x56bbab2  mov rax,[rsi]
                                                             // 0x56bbab5  mov rax,[rax]
    sub_eea6040(oldCtrl, vftable[0]);                        // 0x56bbac1  call qword ptr [0xF99FFA0]
    if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&oldCtrl->weak)) != 0)  // 0x56bbacd  lock dec dword ptr [rsi+0xC]
        goto L_0x56bba66;                                    // 0x56bbad1  jne short 0x56BBA66

    // 0x56bbad3..0x56bbaee: basic block 9
    // 0x56bbad3  mov rax,[rsi]
    // 0x56bbad6  mov rax,[rax+8]
    // 0x56bbada  mov rcx,rsi
    // 0x56bbadd  call qword ptr [0xF99FFA0]
    // 0x56bbae3  mov rdx,r14
    // 0x56bbae6  mov rcx,rbx
    // 0x56bbae9  jmp 0x56BBA66
    vftable = oldCtrl->vftable;                              // 0x56bbad3  mov rax,[rsi]
                                                             // 0x56bbad6  mov rax,[rax+8]
    sub_eea6040(oldCtrl, vftable[1]);                        // 0x56bbadd  call qword ptr [0xF99FFA0]
    goto L_0x56bba66;                                        // 0x56bbae9  jmp 0x56BBA66

    // 0x56bbaee..0x56bbafa: basic block 10
    // 0x56bbaee  mov rax,[rdx]
    // 0x56bbaf1  mov rcx,[rax+8]
    // 0x56bbaf5  test rcx,rcx
    // 0x56bbaf8  je short 0x56BBB04
L_0x56bbaee:;
    pair = reinterpret_cast<sub_56bba40_rax*>(arg1->object); // 0x56bbaee  mov rax,[rdx]
    ctrl = reinterpret_cast<sub_56bba40_rsi*>(pair->control);// 0x56bbaf1  mov rcx,[rax+8]
    if (ctrl == nullptr) goto L_0x56bbb04;                   // 0x56bbaf5  test rcx,rcx
                                                             // 0x56bbaf8  je short 0x56BBB04

    // 0x56bbafa..0x56bbb04: basic block 11
    // 0x56bbafa  lock inc dword ptr [rcx+8]
    // 0x56bbafe  mov rcx,[rax+8]
    // 0x56bbb02  jmp short 0x56BBB06
    _InterlockedIncrement(reinterpret_cast<volatile long*>(&ctrl->strong));  // 0x56bbafa  lock inc dword ptr [rcx+8]
    ctrl = reinterpret_cast<sub_56bba40_rsi*>(pair->control);  // 0x56bbafe  mov rcx,[rax+8]
    goto L_0x56bbb06;                                        // 0x56bbb02  jmp short 0x56BBB06

    // 0x56bbb04..0x56bbb06: basic block 12
    // 0x56bbb04  xor ecx,ecx
L_0x56bbb04:;
    ctrl = nullptr;                                          // 0x56bbb04  xor ecx,ecx

    // 0x56bbb06..0x56bbb19: basic block 13
    // 0x56bbb06  mov rax,[rax]
    // 0x56bbb09  mov [rdi],rax
    // 0x56bbb0c  mov rsi,[rdi+8]
    // 0x56bbb10  mov [rdi+8],rcx
    // 0x56bbb14  test rsi,rsi
    // 0x56bbb17  je short 0x56BBA99
L_0x56bbb06:;
    object = pair->object;                                   // 0x56bbb06  mov rax,[rax]
    sink->object = object;                                   // 0x56bbb09  mov [rdi],rax
    oldCtrl = reinterpret_cast<sub_56bba40_rsi*>(sink->control);  // 0x56bbb0c  mov rsi,[rdi+8]
    sink->control = ctrl;                                    // 0x56bbb10  mov [rdi+8],rcx
    if (oldCtrl == nullptr) goto L_0x56bba99;                // 0x56bbb14  test rsi,rsi
                                                             // 0x56bbb17  je short 0x56BBA99

    // 0x56bbb19..0x56bbb23: basic block 14
    // 0x56bbb19  lock dec dword ptr [rsi+8]
    // 0x56bbb1d  jne 0x56BBA99
    if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&oldCtrl->strong)) != 0)  // 0x56bbb19  lock dec dword ptr [rsi+8]
        goto L_0x56bba99;                                    // 0x56bbb1d  jne 0x56BBA99

    // 0x56bbb23..0x56bbb3c: basic block 15
    // 0x56bbb23  mov rax,[rsi]
    // 0x56bbb26  mov rax,[rax]
    // 0x56bbb29  mov rcx,rsi
    // 0x56bbb2c  call qword ptr [0xF99FFA0]
    // 0x56bbb32  lock dec dword ptr [rsi+0xC]
    // 0x56bbb36  jne 0x56BBA99
    vftable = oldCtrl->vftable;                              // 0x56bbb23  mov rax,[rsi]
                                                             // 0x56bbb26  mov rax,[rax]
    sub_eea6040(oldCtrl, vftable[0]);                        // 0x56bbb2c  call qword ptr [0xF99FFA0]
    if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&oldCtrl->weak)) != 0)  // 0x56bbb32  lock dec dword ptr [rsi+0xC]
        goto L_0x56bba99;                                    // 0x56bbb36  jne 0x56BBA99

    // 0x56bbb3c..0x56bbb59: basic block 16
    // 0x56bbb3c  mov rax,[rsi]
    // 0x56bbb3f  mov rax,[rax+8]
    // 0x56bbb43  mov rdx,[0xF99FFA0]
    // 0x56bbb4a  mov rcx,rsi
    // 0x56bbb4d  add rsp,0x28
    // 0x56bbb51  pop rbx
    // 0x56bbb52  pop rdi
    // 0x56bbb53  pop rsi
    // 0x56bbb54  pop r14
    // 0x56bbb56  jmp rdx
    vftable = oldCtrl->vftable;                              // 0x56bbb3c  mov rax,[rsi]
                                                             // 0x56bbb3f  mov rax,[rax+8]
    sub_eea6040(oldCtrl, vftable[1]);                        // 0x56bbb43  mov rdx,[0xF99FFA0]
                                                             // 0x56bbb4a  mov rcx,rsi
                                                             // 0x56bbb56  jmp rdx
    __assume(false);                                         // tail jump: control does not return to this frame
}

} // namespace native::helpers
