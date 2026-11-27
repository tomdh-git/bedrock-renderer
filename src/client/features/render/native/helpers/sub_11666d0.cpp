// LIFT 0x11666d0 size 0x115 1.26.62.01 sub_11666d0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_11666d0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// Layout assertions (mirrored in sub_11666d0.h): every field read or written has
// an offsetof static_assert at its observed offset.
static_assert(offsetof(sub_11666d0_rcx, f0_vtable) == 0x0, "rcx+0x0");
static_assert(offsetof(sub_11666d0_rcx, f40_listHead) == 0x40, "rcx+0x40");
static_assert(offsetof(sub_11666d0_rcx, f50_mutex) == 0x50, "rcx+0x50");
static_assert(offsetof(sub_11666d0_rcx, f9c_state) == 0x9c, "rcx+0x9c");
static_assert(sizeof(sub_11666d0_rcx) >= 0xa0, "rcx sizeof");
static_assert(offsetof(sub_11666d0_rbx, f0_prev) == 0x0, "rbx+0x0");
static_assert(offsetof(sub_11666d0_rbx, f8_next) == 0x8, "rbx+0x8");
static_assert(offsetof(sub_11666d0_rbx, f18_subListHead) == 0x18, "rbx+0x18");
static_assert(offsetof(sub_11666d0_rbx, f20_subListEnd) == 0x20, "rbx+0x20");
static_assert(offsetof(sub_11666d0_rbx, f28) == 0x28, "rbx+0x28");
static_assert(offsetof(sub_11666d0_rbx, f30_flag) == 0x30, "rbx+0x30");
static_assert(sizeof(sub_11666d0_rbx) >= 0x31, "rbx sizeof");
static_assert(offsetof(sub_11666d0_r14, f8_object) == 0x8, "r14+0x8");
static_assert(sizeof(sub_11666d0_r14) >= 0x10, "r14 sizeof");
static_assert(offsetof(sub_11666d0_rax, f0_headEnd) == 0x0, "rax+0x0");
static_assert(offsetof(sub_11666d0_rax, f10_extra) == 0x10, "rax+0x10");
static_assert(sizeof(sub_11666d0_rax) >= 0x18, "rax sizeof");
static_assert(offsetof(sub_11666d0_rsp, f20) == 0x20, "rsp+0x20");
static_assert(sizeof(sub_11666d0_rsp) >= 0x21, "rsp sizeof");

LIFT_FN(sub_11666d0, "sub_11666d0", 0x11666d0, sub_11666d0, nullptr);

// Verbatim call instructions from the disassembly of [0x11666d0, 0x11667e5).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x11666ea  call 0xEEC59F0
0x1166728  call 0xE935700
0x116676f  call qword ptr [0xF99FFA0]
0x11667cb  call 0xEEC5A00
0x11667df  call 0xEEC5A00
#endif

// Native callees used by this lift. Signatures recovered from the disassembly:
// sub_eec59f0 / sub_eec5a10 are tail forwarders to MSVCP140 _Mtx_lock /
// _Mtx_unlock. sub_eec59f0 returns 0 on success, nonzero on error (eax tested).
struct _Mtx;
int sub_eec59f0(struct _Mtx* mtx);
[[noreturn]] void sub_eec5a00(int errorCode);  // tail forwarder to std::_Throw_Cpp_error(int)
void* sub_e935700(void* a0);                   // tail forwarder to sub_392960(void*)
void sub_eec5a10(struct _Mtx* mtx);            // tail forwarder to _Mtx_unlock

// Indirect release call through data slot 0xF99FFA0. The slot holds the address
// of the release function (sub_eea6040 at runtime); there is no static target by
// design. The call passes the object pointer in RCX and ignores the return value.
using release_fn = void (__cdecl*)(void* object);

void sub_11666d0(void* self) {
    auto* a0 = static_cast<sub_11666d0_rcx*>(self);

    sub_11666d0_rbx* rbx = nullptr;
    sub_11666d0_rbx* const sentinel = reinterpret_cast<sub_11666d0_rbx*>(&a0->f40_listHead);
    sub_11666d0_r14* r14 = nullptr;
    void* r15 = nullptr;
    void* rcx = nullptr;
    void* prev = nullptr;

    // 0x11666d0..0x11666f7: block 0 - prologue, lock the mutex at &a0->f50_mutex
    if (sub_eec59f0(reinterpret_cast<struct _Mtx*>(&a0->f50_mutex)) != 0)
        goto L_0x11667c6;   // 0x11666f1 jne -> lock failed

    // 0x11666f7..0x1166707: block 1
    if (a0->f9c_state == 0x7FFFFFFFu)
        goto L_0x11667d0;   // 0x1166701 je

    // 0x1166707..0x1166718: block 2
    rbx = static_cast<sub_11666d0_rbx*>(a0->f40_listHead);
    if (rbx == sentinel)
        goto L_0x11667ae;   // 0x1166712 je -> empty list

    // 0x1166718..0x116671d: block 3 (xmm6 = 0; no state to model)
    goto L_0x1166735;

    // 0x1166720..0x1166735: block 5
L_0x1166720:
    (void)sub_e935700(rbx); // 0x1166728 call sub_e935700 (edx=0x38 dead, rcx=rbx)
    rbx = static_cast<sub_11666d0_rbx*>(a0->f40_listHead); // 0x116672d mov rbx,[rsi]  rsi == sentinel
    if (rbx == sentinel)
        goto L_0x11667ae;   // 0x1166733 je
    goto L_0x1166735;

    // 0x1166735..0x116673b: block 6
L_0x1166735:
    if (rbx->f30_flag != 1)
        goto L_0x116678f;   // 0x1166739 jne
    goto L_0x116673b;

    // 0x116673b..0x1166744: block 7
L_0x116673b:
    r14 = static_cast<sub_11666d0_r14*>(rbx->f18_subListHead);
    if (r14 == nullptr)
        goto L_0x116678f;   // 0x1166742 je
    goto L_0x1166744;

    // 0x1166744..0x116674a: block 8
L_0x1166744:
    r15 = rbx->f20_subListEnd;
    goto L_0x1166754;

    // 0x1166750..0x1166754: block 10
L_0x1166750:
    r14 = reinterpret_cast<sub_11666d0_r14*>(
        reinterpret_cast<std::uint8_t*>(r14) + 0x10);
    goto L_0x1166754;

    // 0x1166754..0x1166759: block 11
L_0x1166754:
    if (r14 == reinterpret_cast<sub_11666d0_r14*>(r15))
        goto L_0x1166780;   // 0x1166757 je
    goto L_0x1166759;

    // 0x1166759..0x1166762: block 12
L_0x1166759:
    rcx = r14->f8_object;
    if (rcx == nullptr)
        goto L_0x1166750;   // 0x1166760 je
    goto L_0x1166762;

    // 0x1166762..0x1166768: block 13
L_0x1166762: {
        std::uint32_t* refcount =
            reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rcx) + 0xC);
        if (_InterlockedDecrement(refcount) != 0)
            goto L_0x1166750; // 0x1166766 jne
        goto L_0x1166768;    // decremented to zero
    }

    // 0x1166768..0x1166777: block 14
L_0x1166768: {
        release_fn release =
            reinterpret_cast<release_fn>(*reinterpret_cast<void**>(0xF99FFA0));
        release(rcx);        // 0x116676f call qword ptr [0xF99FFA0]
    }
    goto L_0x1166750;

    // 0x1166780..0x116678f: block 16
L_0x1166780:
    rbx->f18_subListHead = nullptr;  // 0x1166784 movups [rax],xmm6 (clears f18+f20)
    rbx->f20_subListEnd = nullptr;
    rbx->f28 = 0;                    // 0x1166787 mov [rax+0x10],0
    goto L_0x116678f;

    // 0x116678f..0x1166797: block 17
L_0x116678f:
    prev = rbx->f0_prev;
    if (prev == rbx)
        goto L_0x1166720;   // 0x1166795 je
    goto L_0x1166797;

    // 0x1166797..0x11667ae: block 18
L_0x1166797: {
        void* next = rbx->f8_next;
        auto* prevNode = static_cast<sub_11666d0_rbx*>(prev);
        auto* nextNode = static_cast<sub_11666d0_rbx*>(next);
        nextNode->f0_prev = prev;                      // 0x116679b mov [rcx],rax
        prevNode->f8_next = next;                      // 0x116679e mov [rax+8],rcx
        rbx->f0_prev = rbx;                            // 0x11667a2 mov [rbx],rbx
        rbx->f8_next = rbx;                            // 0x11667a5 mov [rbx+8],rbx
    }
    goto L_0x1166720;

    // 0x11667ae..0x11667c6: block 19 - unlock and return
L_0x11667ae:
    sub_eec5a10(reinterpret_cast<struct _Mtx*>(&a0->f50_mutex));
    return;

    // 0x11667c6..0x11667d0: block 20 - throw error 5
L_0x11667c6:
    sub_eec5a00(5);

    // 0x11667d0..0x11667e5: block 21 - set state, throw error 6
L_0x11667d0:
    a0->f9c_state = 0x7FFFFFFE;
    sub_eec5a00(6);
}

} // namespace native::helpers
