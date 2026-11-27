// LIFT 0xc2879f0 size 0x120 1.26.62.01 sub_c2879f0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c2879f0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

static_assert(offsetof(native::helpers::sub_c2879f0_rcx, f0) == 0x0, "sub_c2879f0 layout: rcx+0x0");
static_assert(offsetof(native::helpers::sub_c2879f0_rcx, f10) == 0x10, "sub_c2879f0 layout: rcx+0x10");
static_assert(offsetof(native::helpers::sub_c2879f0_rcx, f20) == 0x20, "sub_c2879f0 layout: rcx+0x20");
static_assert(offsetof(native::helpers::sub_c2879f0_rcx, f28) == 0x28, "sub_c2879f0 layout: rcx+0x28");
static_assert(offsetof(native::helpers::sub_c2879f0_rcx, f74) == 0x74, "sub_c2879f0 layout: rcx+0x74");
static_assert(offsetof(native::helpers::sub_c2879f0_rcx, fa0) == 0xa0, "sub_c2879f0 layout: rcx+0xa0");
static_assert(offsetof(native::helpers::sub_c2879f0_rcx, f180) == 0x180, "sub_c2879f0 layout: rcx+0x180");
static_assert(offsetof(native::helpers::sub_c2879f0_rax, f0) == 0x0, "sub_c2879f0 layout: rax+0x0");
static_assert(offsetof(native::helpers::sub_c2879f0_rax, f8) == 0x8, "sub_c2879f0 layout: rax+0x8");
static_assert(offsetof(native::helpers::sub_c2879f0_rdi, f0) == 0x0, "sub_c2879f0 layout: rdi+0x0");
static_assert(offsetof(native::helpers::sub_c2879f0_rdi, f10) == 0x10, "sub_c2879f0 layout: rdi+0x10");
static_assert(offsetof(native::helpers::sub_c2879f0_rsp, f20) == 0x20, "sub_c2879f0 layout: rsp+0x20");
static_assert(offsetof(native::helpers::sub_c2879f0_rsp, f30) == 0x30, "sub_c2879f0 layout: rsp+0x30");

// Callee signatures used by this translation unit. sub_eec59f0 returns the _Mtx_lock
// status tested in EAX at 0xc287a13; sub_eec5a10 / sub_eec5a00 return void; sub_e935700
// returns the value left in RAX by its tail target sub_392960. These are forward
// declarations only; the callee headers are not included here to avoid conflicting
// _Mtx / void-return declarations (sub_c28a920.h is included through our own header).
namespace native {
int sub_eec59f0(void* mtx);
void sub_eec5a10(void* mtx);
void* sub_e935700(void* a0);
void sub_eec5a00(int errorCode);
} // namespace native

namespace native::helpers {

LIFT_FN(sub_c2879f0, "sub_c2879f0", 0xc2879f0, sub_c2879f0, nullptr);

// Verbatim call instructions from the disassembly of [0xc2879f0, 0xc287b10) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xc287a0e  call 0xEEC59F0
0xc287a2b  call 0xEEC5A10
0xc287a42  call 0xC28A920
0xc287a80  call 0xE935700
0xc287ab8  call 0xE935700
0xc287ade  call 0xEEC5A00
0xc287af0  call 0xEEC5A00
0xc287b09  call qword ptr [0xF9A8C78]
#endif

// Invalid-parameter handler reached through data slot [0xF9A8C78] (rule 69).
// The original zeroes the 5th argument slot ([rsp+0x20] at 0xc287af6), clears
// ECX/EDX/R8D/R9D and calls the slot; int3 at 0xc287b0f follows, so it never returns.
[[noreturn]] void sub_c2879f0Fail() {
    using fail_fn = void (*)(void*, void*, void*, void*, void*);
    fail_fn const fail = reinterpret_cast<fail_fn>(
        *reinterpret_cast<std::uintptr_t*>(
            RewriteRegistry::imageBase() + 0xF9A8C78u));
    fail(nullptr, nullptr, nullptr, nullptr, nullptr);   // 0xc287b09 call qword ptr [0xF9A8C78]
    __assume(0);                                         // 0xc287b0f int3: control never returns here
}

uintptr_t sub_c2879f0(void* self) {
    sub_c2879f0_rcx* rsi = static_cast<sub_c2879f0_rcx*>(self);
    void* rcx = nullptr;
    void* rax = nullptr;
    void* rdi = nullptr;
    std::uint64_t rdx = 0;
    std::uintptr_t rcx_u = 0;
    sub_c2879f0_rax* head = nullptr;
    void* const mutex = reinterpret_cast<void*>(&rsi->f28);

    // 0xc2879f0..0xc287a1b: basic block 0
    // 0xc2879f0  push rbp
    // 0xc2879f1  push rsi
    // 0xc2879f2  push rdi
    // 0xc2879f3  sub rsp,0x30
    // 0xc2879f7  lea rbp,[rsp+0x30]
    // 0xc2879fc  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    // 0xc287a04  mov rsi,rcx
    // 0xc287a07  lea rdi,[rcx+0x28]
    // 0xc287a0b  mov rcx,rdi
    // 0xc287a0e  call 0xEEC59F0
    // 0xc287a13  test eax,eax
    // 0xc287a15  jne 0xC287AD9
    // -> if u32(ret@c287a0e) != 0 goto L_0xc287ad9
    // -> if u32(ret@c287a0e) == 0 goto L_0xc287a1b
    L_0xc2879f0:;
    if (::native::sub_eec59f0(mutex) != 0) goto L_0xc287ad9;
    goto L_0xc287a1b;

    // 0xc287a1b..0xc287a28: basic block 1
    // 0xc287a1b  cmp dword ptr [rsi+0x74],0x7FFFFFFF
    // 0xc287a22  je 0xC287AE4
    // -> if *u32(a0+0x74) == 0x7FFFFFFF goto L_0xc287ae4
    // -> if *u32(a0+0x74) != 0x7FFFFFFF goto L_0xc287a28
    L_0xc287a1b:;
    if (rsi->f74 == 0x7FFFFFFFu) goto L_0xc287ae4;
    goto L_0xc287a28;

    // 0xc287a28..0xc287a50: basic block 2
    // 0xc287a28  mov rcx,rdi
    // 0xc287a2b  call 0xEEC5A10
    // 0xc287a30  mov qword ptr [rsi+0x180],0
    // 0xc287a3b  lea rcx,[rsi+0xA0]
    // 0xc287a42  call 0xC28A920
    // 0xc287a47  mov rcx,[rsi+0x10]
    // 0xc287a4b  test rcx,rcx
    // 0xc287a4e  je short 0xC287A93
    // -> if *(a0+0x10) == 0 goto L_0xc287a93
    // -> if *(a0+0x10) != 0 goto L_0xc287a50
    L_0xc287a28:;
    ::native::sub_eec5a10(mutex);
    rsi->f180 = 0;
    sub_c28a920(reinterpret_cast<sub_c28a920_state*>(&rsi->fa0));
    rcx = rsi->f10;
    if (rcx == nullptr) goto L_0xc287a93;
    goto L_0xc287a50;

    // 0xc287a50..0xc287a60: basic block 3
    // 0xc287a50  mov rdx,[rsi+0x20]
    // 0xc287a54  sub rdx,rcx
    // 0xc287a57  cmp rdx,0x1000
    // 0xc287a5e  jb short 0xC287A7C
    // -> if (*(a0+0x20) - *(a0+0x10)) <u 0x1000 goto L_0xc287a7c
    // -> if (*(a0+0x20) - *(a0+0x10)) >=u 0x1000 goto L_0xc287a60
    L_0xc287a50:;
    rdx = rsi->f20 - reinterpret_cast<std::uintptr_t>(rcx);
    if (rdx < 0x1000ULL) goto L_0xc287a7c;
    goto L_0xc287a60;

    // 0xc287a60..0xc287a75: basic block 4
    // 0xc287a60  mov rax,[rcx-8]
    // 0xc287a64  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xc287a68  sub rcx,rax
    // 0xc287a6b  cmp rcx,0x20
    // 0xc287a6f  jae 0xC287AF6
    // -> if (*(a0+0x10)-0x8 - *(*(a0+0x10)-0x8)) >=u 0x20 goto L_0xc287af6
    // -> if (*(a0+0x10)-0x8 - *(*(a0+0x10)-0x8)) <u 0x20 goto L_0xc287a75
    L_0xc287a60:;
    rcx_u = reinterpret_cast<std::uintptr_t>(rcx);
    rax = *reinterpret_cast<void**>(rcx_u - 8);
    if ((rcx_u - 8) - reinterpret_cast<std::uintptr_t>(rax) >= 0x20ULL) goto L_0xc287af6;
    goto L_0xc287a75;

    // 0xc287a75..0xc287a7c: basic block 5
    // 0xc287a75  add rdx,0x27
    // 0xc287a79  mov rcx,rax
    // -> if fallthrough goto L_0xc287a7c
    L_0xc287a75:;
    rdx += 0x27;
    rcx = rax;
    goto L_0xc287a7c;

    // 0xc287a7c..0xc287a93: basic block 6
    // 0xc287a7c  lea rdi,[rsi+0x10]
    // 0xc287a80  call 0xE935700
    // 0xc287a85  xorps xmm0,xmm0
    // 0xc287a88  movups [rdi],xmm0
    // 0xc287a8b  mov qword ptr [rdi+0x10],0
    // -> if fallthrough goto L_0xc287a93
    L_0xc287a7c:;
    ::native::sub_e935700(rcx);
    rsi->f10 = nullptr;   // 0xc287a88 movups [rdi],xmm0 zeroes +0x10..+0x1f
    rsi->f20 = 0;         // 0xc287a8b mov qword ptr [rdi+0x10],0
    goto L_0xc287a93;

    // 0xc287a93..0xc287aa9: basic block 7
    // 0xc287a93  mov rax,[rsi]
    // 0xc287a96  mov rcx,[rax+8]
    // 0xc287a9a  mov qword ptr [rcx],0
    // 0xc287aa1  mov rcx,[rax]
    // 0xc287aa4  test rcx,rcx
    // 0xc287aa7  je short 0xC287AC5
    // -> if *(*(a0)) == 0 goto L_0xc287ac5
    // -> if *(*(a0)) != 0 goto L_0xc287aa9
    L_0xc287a93:;
    head = reinterpret_cast<sub_c2879f0_rax*>(rsi->f0);
    *head->f8 = nullptr;   // 0xc287a9a mov qword ptr [rcx],0
    rcx = head->f0;        // 0xc287aa1 mov rcx,[rax]
    if (rcx == nullptr) goto L_0xc287ac5;
    goto L_0xc287aa9;

    // 0xc287aa9..0xc287ab0: basic block 8
    // 0xc287aa9  nop [rax]
    // -> if fallthrough goto L_0xc287ab0
    L_0xc287aa9:;
    goto L_0xc287ab0;

    // 0xc287ab0..0xc287ac5: basic block 9
    // 0xc287ab0  mov rdi,[rcx]
    // 0xc287ab3  mov edx,0x50
    // 0xc287ab8  call 0xE935700
    // 0xc287abd  mov rcx,rdi
    // 0xc287ac0  test rdi,rdi
    // 0xc287ac3  jne short 0xC287AB0
    // -> if rdi != 0 goto L_0xc287ab0
    // -> if rdi == 0 goto L_0xc287ac5
    L_0xc287ab0:;
    rdi = reinterpret_cast<sub_c2879f0_rax*>(rcx)->f0;   // 0xc287ab0 mov rdi,[rcx]
    ::native::sub_e935700(rcx);                          // 0xc287ab8 call 0xE935700
    rcx = rdi;                                           // 0xc287abd mov rcx,rdi
    if (rdi != nullptr) goto L_0xc287ab0;
    goto L_0xc287ac5;

    // 0xc287ac5..0xc287ad9: basic block 10
    // 0xc287ac5  mov rcx,[rsi]
    // 0xc287ac8  mov edx,0x50
    // 0xc287acd  add rsp,0x30
    // 0xc287ad1  pop rdi
    // 0xc287ad2  pop rsi
    // 0xc287ad3  pop rbp
    // 0xc287ad4  jmp 0xE935700
    // -> tail call; returns sub_e935700(self->f0)
    L_0xc287ac5:;
    return reinterpret_cast<uintptr_t>(::native::sub_e935700(rsi->f0));   // 0xc287ad4 jmp 0xE935700

    // 0xc287ad9..0xc287ae4: basic block 11
    // 0xc287ad9  mov ecx,5
    // 0xc287ade  call 0xEEC5A00
    // 0xc287ae3  nop
    // -> if fallthrough goto L_0xc287ae4
    L_0xc287ad9:;
    ::native::sub_eec5a00(5);   // 0xc287ade call 0xEEC5A00
    goto L_0xc287ae4;

    // 0xc287ae4..0xc287af6: basic block 12
    // 0xc287ae4  mov dword ptr [rsi+0x74],0x7FFFFFFE
    // 0xc287aeb  mov ecx,6
    // 0xc287af0  call 0xEEC5A00
    // 0xc287af5  nop
    // -> if fallthrough goto L_0xc287af6
    L_0xc287ae4:;
    rsi->f74 = 0x7FFFFFFE;      // 0xc287ae4 mov dword ptr [rsi+0x74],0x7FFFFFFE
    ::native::sub_eec5a00(6);   // 0xc287af0 call 0xEEC5A00
    goto L_0xc287af6;

    // 0xc287af6..0xc287b10: basic block 13
    // 0xc287af6  mov qword ptr [rsp+0x20],0
    // 0xc287aff  xor ecx,ecx
    // 0xc287b01  xor edx,edx
    // 0xc287b03  xor r8d,r8d
    // 0xc287b06  xor r9d,r9d
    // 0xc287b09  call qword ptr [0xF9A8C78]
    // 0xc287b0f  int3
    // -> invalid-parameter handler; the following int3 makes this path noreturn
    L_0xc287af6:;
    sub_c2879f0Fail();   // 0xc287b09 call qword ptr [0xF9A8C78] (noreturn; int3 at 0xc287b0f)
}

} // namespace native::helpers
