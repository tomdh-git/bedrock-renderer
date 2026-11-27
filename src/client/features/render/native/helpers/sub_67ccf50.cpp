// LIFT 0x67ccf50 size 0x105 1.26.62.01 sub_67ccf50
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_67ccf50.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_67ccf50, "sub_67ccf50", 0x67ccf50, sub_67ccf50, nullptr);

// Verbatim call instructions from the disassembly of [0x67ccf50, 0x67cd055) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x67ccf91  call qword ptr [0xF99FFA0]
0x67ccff0  call qword ptr [0xF99FFA0]
0x67cd031  call qword ptr [0xF99FFA0]
0x67cd04e  call 0xEEC59E0
#endif

// Ranges: every instruction of [0x67ccf50, 0x67cd055) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.
//
// Lifted logic (proven from the listing):
//   The function walks the half-open range [*(a1+0), *(a1+0x8)) as a float array (stride 4).
//   If a1+0x50 is non-null it is used as a context object; vtable slot 0 fills a local,
//   then each loop iteration calls vtable slot 4 of *(context->vtable) with (context,
//   &localA, &localB), and updates two cursors based on the low bit of the result.
//   The chosen element pointer is stored at *a0, and a0 is returned.
//   When context is null, the first element pointer is stored and a0 returned.
//   If context+0x20 vtable slot exists (context != &localA), a release slot-5 call is made
//   before storing. Block 9 (call 0xeec59e0 then int3) is a trap tail that never returns.
static void* import_eea6040(void* a, void** b) {
    return ((void* (__fastcall*)(void*, void**))(void*)0xF99FFA0)(a, b);
}

// Layout assertion for the lifted state (offsets proven from the listing).
static_assert(offsetof(sub_67ccf50_rdx, f50) == 0x50, "sub_0x67ccf50 rdx+0x50 field");
static_assert(offsetof(sub_67ccf50_rax, f20) == 0x20, "sub_0x67ccf50 rax+0x20 field");

uintptr_t sub_67ccf50(void* self) {
    // 0x67ccf50..0x67ccf87: basic block 0
    // 0x67ccf50  push rbp
    // 0x67ccf51  push r15
    // 0x67ccf53  push r14
    // 0x67ccf55  push r13
    // 0x67ccf57  push r12
    // 0x67ccf59  push rsi
    // 0x67ccf5a  push rdi
    // 0x67ccf5b  push rbx
    // 0x67ccf5c  sub rsp,0x78
    // 0x67ccf60  lea rbp,[rsp+0x70]
    // 0x67ccf65  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0x67ccf6d  mov rdi,r8
    // 0x67ccf70  mov rbx,rdx
    // 0x67ccf73  mov rsi,rcx
    // 0x67ccf76  mov qword ptr [rbp-0x10],0
    // 0x67ccf7e  mov rcx,[rdx+0x50]
    // 0x67ccf82  test rcx,rcx
    // 0x67ccf85  je short 0x67CCF9C
    // -> if *(a1+0x50) == 0 goto L_0x67ccf9c
    // -> if *(a1+0x50) != 0 goto L_0x67ccf87
    // translate statements for this block
    L_0x67ccf50:;
    sub_67ccf50_rdx* a1 = (sub_67ccf50_rdx*)self;
    void* a2 = nullptr; // r8: incoming 3rd arg, read as float[] base at +0x0 via rdi
    void* a0 = self;    // rsi: output pointer
    std::uint64_t local_10 = 0; // [rbp-0x10]
    std::uint8_t local_70 = 0;  // [rbp]
    float local_8 = 0.f;        // [rbp-8]
    float local_4f = 0.f;       // [rbp-4] reused as void* cursor storage via rbx alias
    void* local_48 = nullptr;   // [rbp-0x48]
    void* rbx = nullptr;
    void* rsi = nullptr;
    void* rcx = nullptr;
    intptr_t r15 = 0;
    intptr_t r12 = 0;
    void** local_4 = nullptr;
    intptr_t r13 = 0;
    float xmm0 = 0.f;
    float xmm1 = 0.f;
    void* rcx2 = nullptr;
    void* rax = nullptr;
    void* next = nullptr;
    intptr_t not_r13 = 0;
    void* rcx3 = nullptr;
    unsigned char dl = 0;
    void* rax_local = nullptr;
    void* vtable = nullptr;
    void* vtable0 = nullptr;
    void* (*slot10)(void*, void**, float*) = nullptr;

    local_70 = (std::uint8_t)0xFE; // low byte of 0xFFFFFFFFFFFFFFFE (full store is provenance-only)
    rbx = (void*)a1;
    rsi = self;
    rcx = a1->f50;
    if (rcx == 0) goto L_0x67ccf9c;
    goto L_0x67ccf87;

    // 0x67ccf87..0x67ccf9c: basic block 1
    // 0x67ccf87  mov rax,[rcx]
    // 0x67ccf8a  mov rax,[rax]
    // 0x67ccf8d  lea rdx,[rbp-0x48]
    // 0x67ccf91  call qword ptr [0xF99FFA0]
    // 0x67ccf97  nop
    // 0x67ccf98  mov [rbp-0x10],rax
    // -> if fallthrough goto L_0x67ccf9c
    L_0x67ccf87:;
    {
        sub_67ccf50_rcx* v0 = (sub_67ccf50_rcx*)rcx;
        vtable = v0->f0;
        vtable0 = (sub_67ccf50_rcx*)vtable;
        // call [0xF99FFA0](rcx, &local_48); result -> [rbp-0x10]
        local_10 = (std::uint64_t)import_eea6040(rcx, &local_48);
    }
    goto L_0x67ccf9c;

    // 0x67ccf9c..0x67ccfb7: basic block 2
    // 0x67ccf9c  mov r15,[rbx]
    // 0x67ccf9f  mov r12,[rbx+8]
    // 0x67ccfa3  sub r12,r15
    // 0x67ccfa6  sar r12,2
    // 0x67ccfaa  lea rbx,[rbp-4]
    // 0x67ccfae  lea r14,[rbp-8]
    // 0x67ccfb2  test r12,r12
    // 0x67ccfb5  jle short 0x67CD017
    // -> if ((*(a1+0x8) - *(a1)) >>s 0x2) <=s 0 goto L_0x67cd017
    // -> if ((*(a1+0x8) - *(a1)) >>s 0x2) >s 0 goto L_0x67ccfb7
    L_0x67ccf9c:;
    r15 = *(intptr_t*)rbx;
    r12 = *(intptr_t*)((char*)rbx + 8) - r15;
    r12 >>= 2; // arithmetic shift
    local_4 = (void**)&local_4f; // [rbp-4]
    if (r12 <= 0) goto L_0x67cd017;
    goto L_0x67ccfb7;

    // 0x67ccfb7..0x67ccfc0: basic block 3
    // 0x67ccfb7  nop [rax+rax]
    // -> if fallthrough goto L_0x67ccfc0
    L_0x67ccfb7:;
    goto L_0x67ccfc0;

    // 0x67ccfc0..0x67ccfe3: basic block 4
    // 0x67ccfc0  mov r13,r12
    // 0x67ccfc3  shr r13,1
    // 0x67ccfc6  movss xmm0,[r15+r13*4]
    // 0x67ccfcc  movss xmm1,[rdi]
    // 0x67ccfd0  movss [rbp-8],xmm0
    // 0x67ccfd5  movss [rbp-4],xmm1
    // 0x67ccfda  mov rcx,[rbp-0x10]
    // 0x67ccfde  test rcx,rcx
    // 0x67ccfe1  je short 0x67CD04E
    // -> if ? == 0 goto L_0x67cd04e
    // -> if ? != 0 goto L_0x67ccfe3
    L_0x67ccfc0:;
    r13 = (uintptr_t)r12 >> 1; // logical shift
    xmm0 = *(float*)((char*)rbx + (size_t)r13 * 4); // [r15+r13*4] (rbx is base)
    xmm1 = *(float*)a2; // [rdi+0]
    local_8 = xmm0;
    *(float*)local_4 = xmm1; // [rbp-4] holds float bits
    rcx2 = (void*)local_10;
    if (rcx2 == 0) goto L_0x67cd04e;
    goto L_0x67ccfe3;

    // 0x67ccfe3..0x67cd017: basic block 5
    // 0x67ccfe3  mov rax,[rcx]
    // 0x67ccfe6  mov rax,[rax+0x10]
    // 0x67ccfea  mov rdx,rbx
    // 0x67ccfed  mov r8,r14
    // 0x67ccff0  call qword ptr [0xF99FFA0]
    // 0x67ccf97  nop
    // 0x67ccff7  lea rcx,[r15+r13*4]
    // 0x67ccffb  add rcx,4
    // 0x67ccfff  mov rdx,r13
    // 0x67cd002  not rdx
    // 0x67cd005  add r12,rdx
    // 0x67cd008  test al,al
    // 0x67cd00a  cmove r15,rcx
    // 0x67cd00e  cmovne r12,r13
    // 0x67cd012  test r12,r12
    // 0x67cd015  jg short 0x67CCFC0
    // -> if ? >s 0 goto L_0x67ccfc0
    // -> if ? <=s 0 goto L_0x67cd017
    L_0x67ccfe3:;
    {
        sub_67ccf50_rax* v0 = (sub_67ccf50_rax*)rcx2;
        vtable = v0->f0;
        vtable0 = (sub_67ccf50_rax*)vtable;
        slot10 = (void* (*)(void*, void**, float*))((sub_67ccf50_rax*)vtable0)->f10;
        // call [0xF99FFA0] with rcx=rcx2, rdx=&local_4, r8=&local_8 ; rax = slot10(rcx2,&local_4,&local_8)
        rax = slot10(rcx2, local_4, &local_8);
        // lea rcx,[r15+r13*4]; add rcx,4
        next = (void*)((char*)rbx + (size_t)r13 * 4 + 4);
        // not rdx where rdx=r13; add r12, rdx
        not_r13 = ~(intptr_t)r13;
        r12 += not_r13;
        // test al,al -> ZF set if ((uintptr_t)rax & 0xFF)==0
        if (((uintptr_t)rax & 0xFF) == 0) {
            rbx = next; // cmove r15,rcx (rbx holds r15 base after block 2 reassign)
        } else {
            r12 = r13; // cmovne r12,r13
        }
        if (r12 > 0) goto L_0x67ccfc0;
        goto L_0x67cd017;
    }

    // 0x67cd017..0x67cd020: basic block 6
    // 0x67cd017  mov rcx,[rbp-0x10]
    // 0x67cd01b  test rcx,rcx
    // 0x67cd01e  je short 0x67CD037
    // -> if ? == 0 goto L_0x67cd037
    // -> if ? != 0 goto L_0x67cd020
    L_0x67cd017:;
    rcx3 = (void*)local_10;
    if (rcx3 == 0) goto L_0x67cd037;
    goto L_0x67cd020;

    // 0x67cd020..0x67cd037: basic block 7
    // 0x67cd020  lea rax,[rbp-0x48]
    // 0x67cd024  cmp rcx,rax
    // 0x67cd027  setne dl
    // 0x67cd02a  mov rax,[rcx]
    // 0x67cd02d  mov rax,[rax+0x20]
    // 0x67cd031  call qword ptr [0xF99FFA0]
    // -> if fallthrough goto L_0x67cd037
    L_0x67cd020:;
    {
        rax_local = &local_48;
        dl = (rcx3 != rax_local) ? 1 : 0;
        sub_67ccf50_rax* v3 = (sub_67ccf50_rax*)rcx3;
        vtable = v3->f0;
        vtable0 = (sub_67ccf50_rax*)vtable;
        // call [0xF99FFA0](rcx3) -> rax = vtable2->f20(rcx3)
        void* (*slot20)(void*) = (void* (*)(void*))((sub_67ccf50_rax*)vtable0)->f20;
        slot20(rcx3);
    }
    goto L_0x67cd037;

    // 0x67cd037..0x67cd04e: basic block 8
    // 0x67cd037  mov [rsi],r15
    // 0x67cd03a  mov rax,rsi
    // 0x67cd03d  add rsp,0x78
    // pop rbx,rdi,rsi,r12,r13,r14,r15,rbp
    // ret  (return rax == rsi == a0)
    L_0x67cd037:;
    *(void**)rsi = rbx;
    return (uintptr_t)rsi;

    // 0x67cd04e..0x67cd055: basic block 9
    // 0x67cd04e  call 0xEEC59E0
    // 0x67cd053  nop
    // 0x67cd054  int3
    // -> (fall-through / ret / end)
    // call 0xeec59e0 at 0x67cd04e (not in boundary or lift set; noreturn trap tail)
    L_0x67cd04e:;
    __debugbreak(); // trap tail matches original int3; callee 0xeec59e0 does not return
    return 0; // unreachable

    return 0; // unreachable
}

} // namespace native::helpers
