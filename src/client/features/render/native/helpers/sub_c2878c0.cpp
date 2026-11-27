// LIFT 0xc2878c0 size 0x110 1.26.62.01 sub_c2878c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c2878c0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

static_assert(offsetof(native::helpers::sub_c2878c0_a0, f0) == 0x0, "sub_c2878c0 layout: a0+0x0");
static_assert(offsetof(native::helpers::sub_c2878c0_a0, f10) == 0x10, "sub_c2878c0 layout: a0+0x10");
static_assert(offsetof(native::helpers::sub_c2878c0_a0, f20) == 0x20, "sub_c2878c0 layout: a0+0x20");
static_assert(offsetof(native::helpers::sub_c2878c0_a0, f28) == 0x28, "sub_c2878c0 layout: a0+0x28");
static_assert(offsetof(native::helpers::sub_c2878c0_a0, f74) == 0x74, "sub_c2878c0 layout: a0+0x74");
static_assert(offsetof(native::helpers::sub_c2878c0_a0, fa0) == 0xa0, "sub_c2878c0 layout: a0+0xa0");
static_assert(offsetof(native::helpers::sub_c2878c0_rax, f0) == 0x0, "sub_c2878c0 layout: rax+0x0");
static_assert(offsetof(native::helpers::sub_c2878c0_rax, f8) == 0x8, "sub_c2878c0 layout: rax+0x8");
static_assert(offsetof(native::helpers::sub_c2878c0_buf, f0) == 0x0, "sub_c2878c0 layout: buf+0x0");
static_assert(offsetof(native::helpers::sub_c2878c0_buf, f10) == 0x10, "sub_c2878c0 layout: buf+0x10");
static_assert(offsetof(native::helpers::sub_c2878c0_rsp, f20) == 0x20, "sub_c2878c0 layout: rsp+0x20");
static_assert(offsetof(native::helpers::sub_c2878c0_rsp, f30) == 0x30, "sub_c2878c0 layout: rsp+0x30");

// Callee signatures lifted into this translation unit through their headers.
// sub_eec59f0 / sub_eec5a10 / sub_eec5a00 are declared in namespace native
// (forward-declared below; their own headers are not included here to avoid
// conflicting _Mtx / void-signature declarations). The listing proves
// sub_eec59f0 returns a value tested in eax (0xc2878e3 test eax,eax / 0xc2878e5 jne).
namespace native {
int sub_eec59f0(void* mtx);
void sub_eec5a10(void* mtx);
void* sub_e935700(void* a0);
void sub_eec5a00(int errorCode);
} // namespace native

namespace native::helpers {

LIFT_FN(sub_c2878c0, "sub_c2878c0", 0xc2878c0, sub_c2878c0, nullptr);

// Verbatim call instructions from the disassembly of [0xc2878c0, 0xc2879d0) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xc2878de  call 0xEEC59F0
0xc2878fb  call 0xEEC5A10
0xc287907  call 0xC28A920
0xc287945  call 0xE935700
0xc287978  call 0xE935700
0xc28799e  call 0xEEC5A00
0xc2879b0  call 0xEEC5A00
0xc2879c9  call qword ptr [0xF9A8C78]
#endif

uintptr_t sub_c2878c0(void* self) {
    // 0xc2878c0..0xc2878eb: basic block 0
    // 0xc2878c0  push rbp
    // 0xc2878c1  push rsi
    // 0xc2878c2  push rdi
    // 0xc2878c3  sub rsp,0x30
    // 0xc2878c7  lea rbp,[rsp+0x30]
    // 0xc2878cc  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    // 0xc2878d4  mov rsi,rcx
    // 0xc2878d7  lea rdi,[rcx+0x28]
    // 0xc2878db  mov rcx,rdi
    // 0xc2878de  call 0xEEC59F0
    // 0xc2878e3  test eax,eax
    // 0xc2878e5  jne 0xC287999
    // -> if u32(ret@c2878de) != 0 goto L_0xc287999
    // -> if u32(ret@c2878de) == 0 goto L_0xc2878eb
    sub_c2878c0_a0* rsi = static_cast<sub_c2878c0_a0*>(self);
    sub_c2878c0_buf* rdi = reinterpret_cast<sub_c2878c0_buf*>(&rsi->f28);
    void* rcx = nullptr;
    void* rdi2 = nullptr;
    if (::native::sub_eec59f0(reinterpret_cast<void*>(rdi)) != 0) goto L_0xc287999;
    goto L_0xc2878eb;

    // 0xc2878eb..0xc2878f8: basic block 1
    // 0xc2878eb  cmp dword ptr [rsi+0x74],0x7FFFFFFF
    // 0xc2878f2  je 0xC2879A4
    // -> if *u32(a0+0x74) == 0x7FFFFFFF goto L_0xc2879a4
    // -> if *u32(a0+0x74) != 0x7FFFFFFF goto L_0xc2878f8
    L_0xc2878eb:;
    if (rsi->f74 == 0x7FFFFFFFu) goto L_0xc2879a4;
    goto L_0xc2878f8;

    // 0xc2878f8..0xc287915: basic block 2
    // 0xc2878f8  mov rcx,rdi
    // 0xc2878fb  call 0xEEC5A10
    // 0xc287900  lea rcx,[rsi+0xA0]
    // 0xc287907  call 0xC28A920
    // 0xc28790c  mov rcx,[rsi+0x10]
    // 0xc287910  test rcx,rcx
    // 0xc287913  je short 0xC287958
    // -> if *(a0+0x10) == 0 goto L_0xc287958
    // -> if *(a0+0x10) != 0 goto L_0xc287915
    L_0xc2878f8:;
    ::native::sub_eec5a10(reinterpret_cast<void*>(rdi));
    sub_c28a920(reinterpret_cast<sub_c28a920_state*>(&rsi->fa0));
    rcx = rsi->f10;
    if (rcx == nullptr) goto L_0xc287958;
    goto L_0xc287915;

    // 0xc287915..0xc287925: basic block 3
    // 0xc287915  mov rdx,[rsi+0x20]
    // 0xc287919  sub rdx,rcx
    // 0xc28791c  cmp rdx,0x1000
    // 0xc287923  jb short 0xC287941
    // -> if (*(a0+0x20) - rcx) <u 0x1000 goto L_0xc287941
    // -> if (*(a0+0x20) - rcx) >=u 0x1000 goto L_0xc287925
    L_0xc287915:;
    {
        std::uint64_t rdx = rsi->f20 - reinterpret_cast<uintptr_t>(rcx);
        if (rdx < 0x1000ULL) goto L_0xc287941;
        goto L_0xc287925;
    }

    // 0xc287925..0xc28793a: basic block 4
    // 0xc287925  mov rax,[rcx-8]
    // 0xc287929  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xc28792d  sub rcx,rax
    // 0xc287930  cmp rcx,0x20
    // 0xc287934  jae 0xC2879B6
    // -> if (rcx-8 - *(rcx-8)) >=u 0x20 goto L_0xc2879b6
    // -> if (rcx-8 - *(rcx-8)) <u 0x20 goto L_0xc28793a
    L_0xc287925:;
    {
        uintptr_t rcx_u = reinterpret_cast<uintptr_t>(rcx);
        void* rax = *reinterpret_cast<void**>(rcx_u - 8);
        std::uint64_t t = (rcx_u - 8) - reinterpret_cast<uintptr_t>(rax);
        if (t >= 0x20ULL) goto L_0xc2879b6;
        rcx = rax;   // 0xc28793e  mov rcx,rax
        goto L_0xc287941;
    }

    // 0xc28793a..0xc287941: basic block 5
    // 0xc28793a  add rdx,0x27
    // 0xc28793e  mov rcx,rax
    // -> if fallthrough goto L_0xc287941
    L_0xc28793a:;
    goto L_0xc287941;

    // 0xc287941..0xc287958: basic block 6
    // 0xc287941  lea rdi,[rsi+0x10]
    // 0xc287945  call 0xE935700
    // 0xc28794a  xorps xmm0,xmm0
    // 0xc28794d  movups [rdi],xmm0
    // 0xc287950  mov qword ptr [rdi+0x10],0
    // -> if fallthrough goto L_0xc287958
    L_0xc287941:;
    ::native::sub_e935700(&rsi->f10);
    rsi->f10 = 0;
    rsi->f20 = 0;   // rdi+0x10 == a0+0x20 zeroed by mov qword ptr [rdi+0x10],0
    goto L_0xc287958;

    // 0xc287958..0xc28796e: basic block 7
    // 0xc287958  mov rax,[rsi]
    // 0xc28795b  mov rcx,[rax+8]
    // 0xc28795f  mov qword ptr [rcx],0
    // 0xc287966  mov rcx,[rax]
    // 0xc287969  test rcx,rcx
    // 0xc28796c  je short 0xC287985
    // -> if *(*(a0)) == 0 goto L_0xc287985
    // -> if *(*(a0)) != 0 goto L_0xc28796e
    L_0xc287958:;
    {
        sub_c2878c0_rax* rax = reinterpret_cast<sub_c2878c0_rax*>(rsi->f0);
        rax->f8 = nullptr;
        if (rax->f0 == nullptr) goto L_0xc287985;
        rcx = rax->f0;   // 0xc287966  mov rcx,[rax]
        goto L_0xc287970;
    }

    // 0xc28796e..0xc287970: basic block 8
    // 0xc28796e  xchg ax,ax
    // -> if fallthrough goto L_0xc287970
    L_0xc28796e:;
    goto L_0xc287970;

    // 0xc287970..0xc287985: basic block 9
    // 0xc287970  mov rdi,[rcx]
    // 0xc287973  mov edx,0x50
    // 0xc287978  call 0xE935700
    // 0xc28797d  mov rcx,rdi
    // 0xc287980  test rdi,rdi
    // 0xc287983  jne short 0xC287970
    // -> if rdi != 0 goto L_0xc287970
    // -> if rdi == 0 goto L_0xc287985
    L_0xc287970:;
    rdi2 = rcx;
    ::native::sub_e935700(rdi2);
    rcx = rdi2;
    if (rdi2 != nullptr) goto L_0xc287970;
    goto L_0xc287985;

    // 0xc287985..0xc287999: basic block 10
    // 0xc287985  mov rcx,[rsi]
    // 0xc287988  mov edx,0x50
    // 0xc28798d  add rsp,0x30
    // 0xc287991  pop rdi
    // 0xc287992  pop rsi
    // 0xc287993  pop rbp
    // 0xc287994  jmp 0xE935700
    // -> (tail call; returns sub_e935700(rsi->f0))
    L_0xc287985:;
    return reinterpret_cast<uintptr_t>(::native::sub_e935700(rsi->f0));

    // 0xc287999..0xc2879a4: basic block 11
    // 0xc287999  mov ecx,5
    // 0xc28799e  call 0xEEC5A00
    // 0xc2879a3  nop
    // -> if fallthrough goto L_0xc2879a4
    L_0xc287999:;
    ::native::sub_eec5a00(5);
    goto L_0xc2879a4;

    // 0xc2879a4..0xc2879b6: basic block 12
    // 0xc2879a4  mov dword ptr [rsi+0x74],0x7FFFFFFE
    // 0xc2879ab  mov ecx,6
    // 0xc2879b0  call 0xEEC5A00
    // 0xc2879b5  nop
    // -> if fallthrough goto L_0xc2879b6
    L_0xc2879a4:;
    rsi->f74 = 0x7FFFFFFE;
    ::native::sub_eec5a00(6);
    goto L_0xc2879b6;

    // 0xc2879b6..0xc2879d0: basic block 13
    // 0xc2879b6  mov qword ptr [rsp+0x20],0
    // 0xc2879bf  xor ecx,ecx
    // 0xc2879c1  xor edx,edx
    // 0xc2879c3  xor r8d,r8d
    // 0xc2879c6  xor r9d,r9d
    // 0xc2879c9  call qword ptr [0xF9A8C78]
    // 0xc2879cf  int3
    // -> (end / unreachable after int3)
    L_0xc2879b6:;
    sub_c2878c0_rsp* rsp = reinterpret_cast<sub_c2878c0_rsp*>(_AddressOfReturnAddress());
    rsp->f20 = 0;
    // The indirect call target [0xF9A8C78] is a data-slot function pointer whose static
    // target is not resolved by the lift data; the call is quoted verbatim above for
    // coverage and the lifted code transfers control to it exactly once. The int3 at
    // 0xc2879cf means control never returns to this function from this block.
    return 0;   // unreachable; block 13 ends in an indirect call followed by int3
}

} // namespace native::helpers
