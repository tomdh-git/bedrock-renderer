// LIFT 0x675d320 size 0x10f 1.26.62.01 sub_675d320
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_675d320.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// Layout assertions (mirror the header so liftcheck sees them in source).
static_assert(offsetof(sub_675d320_rcx, f38) == 0x38, "sub_0x675d320 rcx+0x38 field");
static_assert(offsetof(sub_675d320_rcx, f40) == 0x40, "sub_0x675d320 rcx+0x40 field");
static_assert(offsetof(sub_675d320_rcx, f48) == 0x48, "sub_0x675d320 rcx+0x48 field");
static_assert(offsetof(sub_675d320_rcx, f50) == 0x50, "sub_0x675d320 rcx+0x50 field");
static_assert(offsetof(sub_675d320_rcx, f9c) == 0x9c, "sub_0x675d320 rcx+0x9c field");
static_assert(offsetof(sub_675d320_rcx, fa0) == 0xa0, "sub_0x675d320 rcx+0xa0 field");
static_assert(sizeof(sub_675d320_rcx) >= 0xa1, "sub_0x675d320 rcx sizeof lower bound");
static_assert(offsetof(sub_675d320_rax, f0) == 0x0, "sub_0x675d320 rax+0x0 field");
static_assert(offsetof(sub_675d320_rax, f8) == 0x8, "sub_0x675d320 rax+0x8 field");
static_assert(offsetof(sub_675d320_rax, f10) == 0x10, "sub_0x675d320 rax+0x10 field");
static_assert(sizeof(sub_675d320_rax) >= 0x18, "sub_0x675d320 rax sizeof lower bound");
static_assert(offsetof(sub_675d320_rbx, f0) == 0x0, "sub_0x675d320 rbx+0x0 field");
static_assert(sizeof(sub_675d320_rbx) >= 0x8, "sub_0x675d320 rbx sizeof lower bound");

LIFT_FN(sub_675d320, "sub_675d320", 0x675d320, sub_675d320, nullptr);

// Forward declarations of callees (native symbols; exact signatures [open]).
void* sub_9bd4a0(void*);
void* sub_9bc830(int);
void sub_9bd6d0(void*, void*);
int sub_eec59f0(void*);
void sub_eec5a10(void*);
void sub_eec59e0();
void sub_eec5a00(int);

// Global indirect-call thunk slot [data_f99ffa0] = sub_eea6040.
extern void** g_data_F99FFA0;

// Verbatim call instructions from the disassembly of [0x675d320, 0x675d42f) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x675d336  call 0x9BD4A0
0x675d35c  call qword ptr [0xF99FFA0]
0x675d39e  call qword ptr [0xF99FFA0]
0x675d3aa  call 0x9BD6D0
0x675d3b6  call 0xEEC59F0
0x675d3e4  call 0xEEC5A10
0x675d3fe  call 0x9BC830
0x675d40b  call 0xEEC59E0
0x675d415  call 0xEEC5A00
0x675d429  call 0xEEC5A00
#endif

uintptr_t sub_675d320(void* self) {
    void* rdi = nullptr;
    void* rax = nullptr;
    void* rcx = nullptr;
    void* rbx = nullptr;
    uintptr_t rsp_local20 = 0;
    uintptr_t r14_local = 0;

    // 0x675d320..0x675d340: basic block 0
    // 0x675d320  push r14
    // 0x675d322  push rsi
    // 0x675d323  push rdi
    // 0x675d324  push rbx
    // 0x675d325  sub rsp,0x28
    // 0x675d329  mov rsi,rcx
    // 0x675d32c  lea rbx,[rcx+0xA0]
    // 0x675d333  mov rcx,rbx
    // 0x675d336  call 0x9BD4A0
    // 0x675d33b  test rax,rax
    // 0x675d33e  je short 0x675D349
    // -> if ret@675d336 == 0 goto L_0x675d349
    // -> if ret@675d336 != 0 goto L_0x675d340
    L_0x675d320:;
    {
        sub_675d320_rcx* a0 = reinterpret_cast<sub_675d320_rcx*>(self);
        auto* ret675d336 = sub_9bd4a0(reinterpret_cast<void*>(&a0->fa0));
        if (ret675d336 == nullptr) goto L_0x675d349;
        goto L_0x675d340;
    }

    // 0x675d340..0x675d349: basic block 1
    // 0x675d340  add rax,0x10
    // 0x675d344  jmp 0x675D3EC
    // -> if jmp goto L_0x675d3ec
    L_0x675d340:;
    {
        rax = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rax) + 0x10);
        goto L_0x675d3ec;
    }

    // 0x675d349..0x675d36e: basic block 2
    // 0x675d349  mov rcx,[0x1233E1A8]
    // 0x675d350  mov rax,[rcx]
    // 0x675d353  mov rax,[rax+8]
    // 0x675d357  mov edx,0x100
    // 0x675d35c  call qword ptr [0xF99FFA0]
    // 0x675d362  mov rdi,rax
    // 0x675d365  test rax,rax
    // 0x675d368  je 0x675D3F6
    // -> if ret@675d35c == 0 goto L_0x675d3f6
    // -> if ret@675d35c != 0 goto L_0x675d36e
    L_0x675d349:;
    {
        void* g_data_1233e1a8 = *reinterpret_cast<void**>(0x1233E1A8);
        sub_675d320_rax* rax_obj = reinterpret_cast<sub_675d320_rax*>(g_data_1233e1a8);
        void* vt_slot2 = rax_obj->f8;
        auto* ret675d35c = reinterpret_cast<void* (__cdecl*)(void*, int)>(
            g_data_F99FFA0[0])(rax_obj, 0x100);
        rdi = ret675d35c;
        if (rdi == nullptr) goto L_0x675d3f6;
        goto L_0x675d36e;
    }

    // 0x675d36e..0x675d38f: basic block 3
    // 0x675d36e  mov [rdi],rdi
    // 0x675d371  mov [rdi+8],rdi
    // 0x675d375  add rax,0x10
    // 0x675d379  mov qword ptr [rdi+0x10],0
    // 0x675d381  mov [rsp+0x20],rax
    // 0x675d386  mov rcx,[rsi+0x38]
    // 0x675d38a  test rcx,rcx
    // 0x675d38d  je short 0x675D40B
    // -> if *(a0+0x38) == 0 goto L_0x675d40b
    // -> if *(a0+0x38) != 0 goto L_0x675d38f
    L_0x675d36e:;
    {
        sub_675d320_rax* rdi_obj = reinterpret_cast<sub_675d320_rax*>(rdi);
        rdi_obj->f0 = rdi;
        rdi_obj->f8 = rdi;
        auto* rdi_f10 = reinterpret_cast<sub_675d320_rax*>(reinterpret_cast<uintptr_t>(rdi) + 0x10);
        rdi_f10->f0 = nullptr;
        rax = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rax) + 0x10);
        rsp_local20 = reinterpret_cast<uintptr_t>(rax);
        sub_675d320_rcx* a0 = reinterpret_cast<sub_675d320_rcx*>(self);
        rcx = a0->f38;
        if (rcx == nullptr) goto L_0x675d40b;
        goto L_0x675d38f;
    }

    // 0x675d38f..0x675d3bf: basic block 4
    // 0x675d38f  mov r14,rax
    // 0x675d392  mov rax,[rcx]
    // 0x675d395  mov rax,[rax+0x10]
    // 0x675d399  lea rdx,[rsp+0x20]
    // 0x675d39e  call qword ptr [0xF99FFA0]
    // 0x675d3a4  mov rcx,rbx
    // 0x675d3a7  mov rdx,rdi
    // 0x675d3aa  call 0x9BD6D0
    // 0x675d3af  lea rbx,[rsi+0x50]
    // 0x675d3b3  mov rcx,rbx
    // 0x675d3b6  call 0xEEC59F0
    // 0x675d3bb  test eax,eax
    // 0x675d3bd  jne short 0x675D410
    // -> if u32(ret@675d3b6) != 0 goto L_0x675d410
    // -> if u32(ret@675d3b6) == 0 goto L_0x675d3bf
    L_0x675d38f:;
    {
        r14_local = reinterpret_cast<uintptr_t>(rax);
        sub_675d320_rax* rcx_obj = reinterpret_cast<sub_675d320_rax*>(rcx);
        void* rax_vt0 = rcx_obj->f0;
        sub_675d320_rax* rax_obj2 = reinterpret_cast<sub_675d320_rax*>(rax_vt0);
        void* rax_f10_val = rax_obj2->f10;
        auto* call_fn = reinterpret_cast<void* (__cdecl*)(void*, void*, int)>(
            g_data_F99FFA0[0]);
        void* ret675d39e = call_fn(&rsp_local20, rdi, 0x20);
        sub_675d320_rbx* rbx_obj = reinterpret_cast<sub_675d320_rbx*>(rbx);
        sub_9bd6d0(rbx_obj, rdi);
        sub_675d320_rcx* a0 = reinterpret_cast<sub_675d320_rcx*>(self);
        rbx = reinterpret_cast<void*>(&a0->f50);
        int ret675d3b6 = sub_eec59f0(reinterpret_cast<sub_675d320_rbx*>(rbx));
        if (ret675d3b6 != 0) goto L_0x675d410;
        goto L_0x675d3bf;
    }

    // 0x675d3bf..0x675d3cb: basic block 5
    // 0x675d3bf  cmp dword ptr [rsi+0x9C],0x7FFFFFFF
    // 0x675d3c9  je short 0x675D41A
    // -> if *u32(a0+0x9C) == 0x7FFFFFFF goto L_0x675d41a
    // -> if *u32(a0+0x9C) != 0x7FFFFFFF goto L_0x675d3cb
    L_0x675d3bf:;
    {
        sub_675d320_rcx* a0 = reinterpret_cast<sub_675d320_rcx*>(self);
        if (a0->f9c == 0x7FFFFFFF) goto L_0x675d41a;
        goto L_0x675d3cb;
    }

    // 0x675d3cb..0x675d3ec: basic block 6
    // 0x675d3cb  lea rax,[rsi+0x40]
    // 0x675d3cf  mov rcx,[rsi+0x48]
    // 0x675d3d3  mov [rdi+8],rcx
    // 0x675d3d7  mov [rdi],rax
    // 0x675d3da  mov [rcx],rdi
    // 0x675d3dd  mov [rsi+0x48],rdi
    // 0x675d3e1  mov rcx,rbx
    // 0x675d3e4  call 0xEEC5A10
    // 0x675d3e9  mov rax,r14
    // -> if fallthrough goto L_0x675d3ec
    L_0x675d3cb:;
    {
        sub_675d320_rcx* a0 = reinterpret_cast<sub_675d320_rcx*>(self);
        void* rax_obj3 = reinterpret_cast<void*>(&a0->f40);
        rax = rax_obj3;
        void* rcx2 = a0->f48;
        sub_675d320_rax* rdi_obj2 = reinterpret_cast<sub_675d320_rax*>(rdi);
        rdi_obj2->f8 = rcx2;
        rdi_obj2->f0 = reinterpret_cast<sub_675d320_rax*>(rax_obj3);
        reinterpret_cast<sub_675d320_rax*>(rcx2)->f0 = rdi;
        a0->f48 = rdi;
        rcx = rbx;
        sub_eec5a10(rbx);
        rax = reinterpret_cast<void*>(r14_local);
        goto L_0x675d3ec;
    }

    // 0x675d3ec..0x675d3f6: basic block 7
    // 0x675d3ec  add rsp,0x28
    // 0x675d3f0  pop rbx
    // 0x675d3f1  pop rdi
    // 0x675d3f2  pop rsi
    // 0x675d3f3  pop r14
    // 0x675d3f5  ret
    // -> (fall-through / ret / end)
    L_0x675d3ec:;
    {
        return reinterpret_cast<uintptr_t>(rax);
    }

    // 0x675d3f6..0x675d40b: basic block 8
    // 0x675d3f6  mov ecx,0x100
    // 0x675d3fb  mov r14,rax
    // 0x675d3fe  call 0x9BC830
    // 0x675d403  mov rax,r14
    // 0x675d406  jmp 0x675D36E
    // -> if jmp goto L_0x675d36e
    L_0x675d3f6:;
    {
        r14_local = reinterpret_cast<uintptr_t>(rax);
        auto* ret675d3fe = sub_9bc830(0x100);
        rax = reinterpret_cast<void*>(r14_local);
        goto L_0x675d36e;
    }

    // 0x675d40b..0x675d410: basic block 9
    // 0x675d40b  call 0xEEC59E0
    // -> if fallthrough goto L_0x675d410
    L_0x675d40b:;
    {
        sub_eec59e0();
        goto L_0x675d410;
    }

    // 0x675d410..0x675d41a: basic block 10
    // 0x675d410  mov ecx,5
    // 0x675d415  call 0xEEC5A00
    // -> if fallthrough goto L_0x675d41a
    L_0x675d410:;
    {
        sub_eec5a00(5);
        goto L_0x675d41a;
    }

    // 0x675d41a..0x675d42f: basic block 11
    // 0x675d41a  mov dword ptr [rsi+0x9C],0x7FFFFFFE
    // 0x675d424  mov ecx,6
    // 0x675d429  call 0xEEC5A00
    // 0x675d42e  int3
    // -> (fall-through / ret / end)
    L_0x675d41a:;
    {
        sub_675d320_rcx* a0 = reinterpret_cast<sub_675d320_rcx*>(self);
        a0->f9c = 0x7FFFFFFE;
        sub_eec5a00(6);
        __debugbreak();
    }
}

} // namespace native::helpers
