// LIFT 0x67d0ff0 size 0x12e 1.26.62.01 sub_67d0ff0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_67d0ff0.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

LIFT_FN(sub_67d0ff0, "sub_67d0ff0", 0x67d0ff0, sub_67d0ff0, nullptr);

// Verbatim call instructions from the disassembly of [0x67d0ff0, 0x67d111e) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
// The indirect calls `call qword ptr [0xF99FFA0]` resolve to sub_eea6040, a `jmp rax` thunk
// that tail-calls a vtable slot (slot 0 = destructor, slot 1 = operator delete) with rcx = obj.
// In the lift this is emitted as a direct call through the object's vtable slots.
#if 0
0x67d1095  call qword ptr [0xF99FFA0]
0x67d10ab  call qword ptr [0xF99FFA0]
0x67d10ea  call qword ptr [0xF99FFA0]
0x67d1100  call qword ptr [0xF99FFA0]
#endif

namespace {

// Intrusive reference-count release for an object referenced by a +0x8/+0x18 field.
// Matches the block sequence: dec [obj+0x8]; if != 0 return;
// call vtable[0](obj); dec [obj+0xc]; if != 0 return; call vtable[1](obj).
static void intrusive_release(void* obj) {
    if (obj == nullptr) return;
    auto* p = reinterpret_cast<sub_67d0ff0_rbx*>(obj);
    if (--p->f8 != 0) return;
    using Fn = void (__cdecl *)(void*);
    void** vt = reinterpret_cast<void**>(p->f0);
    Fn dtor = reinterpret_cast<Fn>(vt[0]);
    dtor(obj);
    if (--p->fc != 0) return;
    vt = reinterpret_cast<void**>(p->f0);
    Fn del = reinterpret_cast<Fn>(vt[1]);
    del(obj);
}

// Intrusive reference-count increment for an object referenced by a +0x8/+0x18 field.
// Matches: inc [obj+0x8].
static void intrusive_inc(void* obj) {
    if (obj == nullptr) return;
    auto* p = reinterpret_cast<sub_67d0ff0_rax*>(obj);
    ++p->f8;
}

} // namespace

void* sub_67d0ff0(sub_67d0ff0_rcx* a0, sub_67d0ff0_rdx* a1) {
    // rax holds the temporary loaded across basic blocks (return value at the end).
    void* rax = nullptr;

    // 0x67d0ff0..0x67d1003: block 0 (prologue + branch)
    // 0x67d0ff0  push rsi
    // 0x67d0ff1  push rdi
    // 0x67d0ff2  push rbx
    // 0x67d0ff3  sub rsp,0x20
    // 0x67d0ff7  mov rdi,rdx
    // 0x67d0ffa  mov rsi,rcx
    // 0x67d0ffd  cmp byte ptr [rcx+0x38],1
    // 0x67d1001  jne short 0x67D1016   -> if a0->f38 != 1 goto L_0x67d1016 else goto L_0x67d1003
    if (a0->f38 != 1) goto L_0x67d1016;
    goto L_0x67d1003;

L_0x67d1003:
    // 0x67d1003..0x67d100c: block 1
    // 0x67d1003  mov rax,[rdi+8]
    // 0x67d1007  test rax,rax
    // 0x67d100a  je short 0x67D1071    -> if a1->f8 == nullptr goto L_0x67d1071 else goto L_0x67d100c
    rax = a1->f8;
    if (rax == nullptr) goto L_0x67d1071;
    goto L_0x67d100c;

L_0x67d100c:
    // 0x67d100c..0x67d1016: block 2
    // 0x67d100c  lock inc dword ptr [rax+8]
    // 0x67d1010  mov rax,[rdi+8]
    // 0x67d1014  jmp short 0x67D1073   -> goto L_0x67d1073
    intrusive_inc(rax);
    rax = a1->f8;
    goto L_0x67d1073;

L_0x67d1016:
    // 0x67d1016..0x67d1025: block 3
    // 0x67d1016  xorps xmm0,xmm0
    // 0x67d1019  movups [rsi],xmm0     (zero a0+0x00..0x0f)
    // 0x67d101c  mov rax,[rdi+8]
    // 0x67d1020  test rax,rax
    // 0x67d1023  je short 0x67D1029    -> if a1->f8 == nullptr goto L_0x67d1029 else goto L_0x67d1025
    a0->f0 = nullptr;
    a0->f8 = nullptr;
    rax = a1->f8;
    if (rax == nullptr) goto L_0x67d1029;
    goto L_0x67d1025;

L_0x67d1025:
    // 0x67d1025..0x67d1029: block 4
    // 0x67d1025  lock inc dword ptr [rax+8] -> fallthrough goto L_0x67d1029
    intrusive_inc(rax);
    goto L_0x67d1029;

L_0x67d1029:
    // 0x67d1029..0x67d1044: block 5
    // 0x67d1029  mov rax,[rdi]
    // 0x67d102c  mov [rsi],rax
    // 0x67d102f  mov rax,[rdi+8]
    // 0x67d1033  mov [rsi+8],rax
    // 0x67d1037  movups [rsi+0x10],xmm0 (xmm0 is zero -> a0+0x10 = 0)
    // 0x67d103b  mov rax,[rdi+0x18]
    // 0x67d103f  test rax,rax
    // 0x67d1042  je short 0x67D1048    -> if a1->f18 == nullptr goto L_0x67d1048 else goto L_0x67d1044
    a0->f0 = a1->f0;
    a0->f8 = rax;            // rax == a1->f8
    a0->f10 = nullptr;
    rax = a1->f18;
    if (rax == nullptr) goto L_0x67d1048;
    goto L_0x67d1044;

L_0x67d1044:
    // 0x67d1044..0x67d1048: block 6
    // 0x67d1044  lock inc dword ptr [rax+8] -> fallthrough goto L_0x67d1048
    intrusive_inc(rax);
    goto L_0x67d1048;

L_0x67d1048:
    // 0x67d1048..0x67d1071: block 7
    // 0x67d1048  mov rax,[rdi+0x10]
    // 0x67d104c  mov [rsi+0x10],rax
    // 0x67d1050  mov rax,[rdi+0x18]
    // 0x67d1054  mov [rsi+0x18],rax
    // 0x67d1058  movups xmm0,[rdi+0x20]
    // 0x67d105c  movups [rsi+0x20],xmm0
    // 0x67d1060  mov rax,[rdi+0x30]
    // 0x67d1064  mov [rsi+0x30],rax
    // 0x67d1068  mov byte ptr [rsi+0x38],1
    // 0x67d106c  jmp 0x67D1116         -> goto L_0x67d1116
    a0->f10 = a1->f10;
    a0->f18 = rax;            // rax == a1->f18
    a0->f20[0] = a1->f20[0];
    a0->f20[1] = a1->f20[1];
    rax = a1->f30;
    a0->f30 = rax;
    a0->f38 = 1;
    goto L_0x67d1116;

L_0x67d1071:
    // 0x67d1071..0x67d1073: block 8
    // 0x67d1071  xor eax,eax           -> fallthrough goto L_0x67d1073
    rax = nullptr;
    goto L_0x67d1073;

L_0x67d1073:
    // 0x67d1073..0x67d10b1: block 9
    // 0x67d1073  mov rcx,[rdi]
    // 0x67d1076  mov [rsi],rcx
    // 0x67d1079  mov rbx,[rsi+8]       (old a0->f8)
    // 0x67d107d  mov [rsi+8],rax       (rax == a1->f8 or nullptr)
    // 0x67d1081  test rbx,rbx
    // 0x67d1084  je short 0x67D10B1    -> if old == nullptr goto L_0x67d10b1 else blocks 10-12
    {
        void* old = a0->f8;
        a0->f0 = a1->f0;
        a0->f8 = rax;
        if (old == nullptr) goto L_0x67d10b1;
        intrusive_release(old);   // blocks 10-12: dec +0x8, vtable[0], dec +0xc, vtable[1]
        goto L_0x67d10b1;
    }

L_0x67d10b1:
    // 0x67d10b1..0x67d10c4: block 13
    // 0x67d10b1  mov rax,[rdi+0x18]
    // 0x67d10b5  test rax,rax
    // 0x67d10b8  je short 0x67D10C4    -> if a1->f18 == nullptr goto L_0x67d10c4 else goto L_0x67d10ba
    rax = a1->f18;
    if (rax == nullptr) goto L_0x67d10c4;
    goto L_0x67d10ba;

L_0x67d10ba:
    // 0x67d10ba..0x67d10c4: block 14
    // 0x67d10ba  lock inc dword ptr [rax+8]
    // 0x67d10be  mov rax,[rdi+0x18]
    // 0x67d10c2  jmp short 0x67D10C6   -> goto L_0x67d10c6
    intrusive_inc(rax);
    rax = a1->f18;
    goto L_0x67d10c6;

L_0x67d10c4:
    // 0x67d10c4..0x67d10c6: block 15
    // 0x67d10c4  xor eax,eax           -> fallthrough goto L_0x67d10c6
    rax = nullptr;
    goto L_0x67d10c6;

L_0x67d10c6:
    // 0x67d10c6..0x67d1106: block 16
    // 0x67d10c6  mov rcx,[rdi+0x10]
    // 0x67d10ca  mov [rsi+0x10],rcx
    // 0x67d10ce  mov rbx,[rsi+0x18]    (old a0->f18)
    // 0x67d10d2  mov [rsi+0x18],rax    (rax == a1->f18 or nullptr)
    // 0x67d10d6  test rbx,rbx
    // 0x67d10d9  je short 0x67D1106    -> if old == nullptr goto L_0x67d1106 else blocks 17-19
    {
        void* old = a0->f18;
        a0->f10 = a1->f10;
        a0->f18 = rax;
        if (old == nullptr) goto L_0x67d1106;
        intrusive_release(old);   // blocks 17-19: dec +0x8, vtable[0], dec +0xc, vtable[1]
        goto L_0x67d1106;
    }

L_0x67d1106:
    // 0x67d1106..0x67d1116: block 20
    // 0x67d1106  mov rax,[rdi+0x30]
    // 0x67d110a  mov [rsi+0x30],rax
    // 0x67d110e  movups xmm0,[rdi+0x20]
    // 0x67d1112  movups [rsi+0x20],xmm0
    rax = a1->f30;
    a0->f30 = rax;
    a0->f20[0] = a1->f20[0];
    a0->f20[1] = a1->f20[1];
    goto L_0x67d1116;

L_0x67d1116:
    // 0x67d1116..0x67d111e: block 21 (epilogue + ret)
    // return rax == a1->f30
    return rax;
}

// Layout assertions for the dereferenced base registers (mirrors sub_67d0ff0.h).
static_assert(offsetof(sub_67d0ff0_rcx, f38) == 0x38, "sub_67d0ff0 rcx+0x38 field");
static_assert(offsetof(sub_67d0ff0_rdx, f30) == 0x30, "sub_67d0ff0 rdx+0x30 field");
static_assert(offsetof(sub_67d0ff0_rbx, fc) == 0xc, "sub_67d0ff0 rbx+0xc field");

} // namespace native::helpers
