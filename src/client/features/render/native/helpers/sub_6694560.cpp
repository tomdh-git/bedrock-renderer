// LIFT 0x6694560 size 0xfe 1.26.62.01 sub_6694560
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_6694560.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// vtable slot 0 = destroy (invoked when the strong count reaches 0)
// 0x66945da  mov rax,[rdi]; 0x66945dd  mov rax,[rax]   ; rax = rdi->vptr[0]
// 0x66945e3  call qword ptr [0xF99FFA0]                ; rdi->vptr[0](rdi) via thunk
static void (*vtableDestroy(void* obj))(void*) {
    void** vt = reinterpret_cast<void**>(obj);
    return reinterpret_cast<void (*)(void*)>(vt[0]);
}

// vtable slot 1 = dealloc (invoked when the weak count reaches 0)
// 0x66945ef  mov rax,[rdi]; 0x66945f2  mov rax,[rax+8] ; rax = rdi->vptr[1]
// 0x66945f9  call qword ptr [0xF99FFA0]                ; rdi->vptr[1](rdi) via thunk
static void* (*vtableDealloc(void* obj))(void*) {
    void** vt = reinterpret_cast<void**>(obj);
    return reinterpret_cast<void* (*)(void*)>(vt[1]);
}

// [0xF9A8C78] data-slot call on the out-of-range heap path (terminator,
// followed by int3 padding; control never continues past the call).
// 0x6694644  mov qword ptr [rsp+0x20],0
// 0x669464d  xor ecx,ecx; 0x669464f  xor edx,edx
// 0x6694651  xor r8d,r8d; 0x6694654  xor r9d,r9d
// 0x6694657  call qword ptr [0xF9A8C78]
[[noreturn]] static void reportFatalFailure() {
    using Fn = uintptr_t(__cdecl*)(uintptr_t, uintptr_t, uintptr_t, uintptr_t);
    reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(
        RewriteRegistry::imageBase() + 0xF9A8C78))(0, 0, 0, 0);
    __assume(false);
}

uintptr_t sub_6694560(sub_6694560_state* self) {
    // All locals declared up front so goto cannot skip initializations.
    uintptr_t rax = 0;
    uintptr_t rdx = 0;
    uintptr_t r8 = 0;
    void* rcx = nullptr;
    void* rdi = nullptr;
    void* rsi = nullptr;

    // 0x6694560..0x6694576: basic block 0
    // 0x6694560  push rsi
    // 0x6694561  push rdi
    // 0x6694562  sub rsp,0x28
    // 0x6694566  mov rsi,rcx
    // 0x6694569  mov rax,[rcx+0x240]
    // 0x6694570  cmp rax,0x10
    // 0x6694574  jb short 0x66945AE
    // -> if self->mBufferSize <u 0x10 goto L_0x66945ae
    // -> if self->mBufferSize >=u 0x10 goto L_0x6694576
    rax = self->mBufferSize;
    if (rax < 0x10) goto L_0x66945ae;

    // 0x6694576..0x669458a: basic block 1
    // 0x6694576  mov rcx,[rsi+0x228]
    // 0x669457d  lea rdx,[rax+1]
    // 0x6694581  cmp rdx,0x1000
    // 0x6694588  jb short 0x66945A9
    // -> if self->mBufferSize+1 <u 0x1000 goto L_0x66945a9
    // -> if self->mBufferSize+1 >=u 0x1000 goto L_0x669458a
    rcx = self->mBuffer;
    rdx = rax + 1;
    if (rdx < 0x1000) goto L_0x66945a9;

    // 0x669458a..0x669459f: basic block 2
    // 0x669458a  mov r8,[rcx-8]
    // 0x669458e  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x6694592  sub rcx,r8
    // 0x6694595  cmp rcx,0x20
    // 0x6694599  jae 0x6694644
    // -> if (*(mBuffer-8) adjusted) >=u 0x20 goto L_0x6694644
    // -> if ... <u 0x20 goto L_0x669459f
    r8 = *reinterpret_cast<const uintptr_t*>(
        reinterpret_cast<const uint8_t*>(rcx) - 8);
    rcx = reinterpret_cast<void*>(
        reinterpret_cast<uint8_t*>(rcx) - 8 - r8);
    if (rcx >= reinterpret_cast<void*>(0x20)) goto L_0x6694644;
    rax = rax + 0x28;
    rdx = rax;
    rcx = reinterpret_cast<void*>(r8);
    goto L_0x66945a9;

L_0x66945a9:  // from 0x6694588, 0x669459f
    // 0x66945a9  call 0xE935700
    // -> if fallthrough goto L_0x66945ae
    native::sub_e935700(rcx);
    goto L_0x66945ae;

L_0x66945ae:  // from 0x6694574, 0x66945a9
    // 0x66945ae  mov qword ptr [rsi+0x238],0
    // 0x66945b9  mov qword ptr [rsi+0x240],0xF
    // 0x66945c4  mov byte ptr [rsi+0x228],0
    // 0x66945cb  mov rdi,[rsi+0x18]
    // 0x66945cf  test rdi,rdi
    // 0x66945d2  je short 0x66945FF
    // -> if self->mRefCountedA == 0 goto L_0x66945ff
    // -> if self->mRefCountedA != 0 goto L_0x66945d4
    self->mBufferCount = 0;
    self->mBufferSize = 0xF;
    *reinterpret_cast<uint8_t*>(&self->mBuffer) = 0;
    rdi = self->mRefCountedA;
    if (rdi == nullptr) goto L_0x66945ff;

L_0x66945d4:  // from 0x66945d2 (not taken)
    // 0x66945d4  lock dec dword ptr [rdi+8]
    // 0x66945d8  jne short 0x66945FF
    // -> if (Dec *u32(rdi+8), ?) != 0 goto L_0x66945ff
    // -> if (Dec *u32(rdi+8), ?) == 0 goto L_0x66945da
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(
            &static_cast<RefCountedObject*>(rdi)->strong)) != 0)
        goto L_0x66945ff;

L_0x66945da:  // from 0x66945d8 (not taken)
    // 0x66945da  mov rax,[rdi]
    // 0x66945dd  mov rax,[rax]
    // 0x66945e0  mov rcx,rdi
    // 0x66945e3  call qword ptr [0xF99FFA0]  ; vtable[0](rdi) via thunk
    // 0x66945e9  lock dec dword ptr [rdi+0xC]
    // 0x66945ed  jne short 0x66945FF
    // -> if (Dec *u32(rdi+0xC), ?) != 0 goto L_0x66945ff
    // -> if (Dec *u32(rdi+0xC), ?) == 0 goto L_0x66945ef
    vtableDestroy(rdi)(rdi);
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(
            &static_cast<RefCountedObject*>(rdi)->weak)) != 0)
        goto L_0x66945ff;

L_0x66945ef:  // from 0x66945ed (not taken)
    // 0x66945ef  mov rax,[rdi]
    // 0x66945f2  mov rax,[rax+8]
    // 0x66945f6  mov rcx,rdi
    // 0x66945f9  call qword ptr [0xF99FFA0]  ; vtable[1](rdi) via thunk
    // -> if fallthrough goto L_0x66945ff
    vtableDealloc(rdi)(rdi);

L_0x66945ff:  // from 0x66945d2, 0x66945d8, 0x66945ed
    // 0x66945ff  mov rsi,[rsi+8]
    // 0x6694603  test rsi,rsi
    // 0x6694606  je short 0x669463D
    // -> if self->mRefCountedB == 0 goto L_0x669463d
    // -> if self->mRefCountedB != 0 goto L_0x6694608
    rsi = self->mRefCountedB;
    if (rsi == nullptr) goto L_0x669463d;

L_0x6694608:  // from 0x6694606 (not taken)
    // 0x6694608  lock dec dword ptr [rsi+8]
    // 0x669460c  jne short 0x669463D
    // -> if (Dec *u32(rsi+8), ?) != 0 goto L_0x669463d
    // -> if (Dec *u32(rsi+8), ?) == 0 goto L_0x669460e
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(
            &static_cast<RefCountedObject*>(rsi)->strong)) != 0)
        goto L_0x669463d;

L_0x669460e:  // from 0x669460c (not taken)
    // 0x669460e  mov rax,[rsi]
    // 0x6694611  mov rax,[rax]
    // 0x6694614  mov rcx,rsi
    // 0x6694617  call qword ptr [0xF99FFA0]  ; vtable[0](rsi) via thunk
    // 0x669461d  lock dec dword ptr [rsi+0xC]
    // 0x6694621  jne short 0x669463D
    // -> if (Dec *u32(rsi+0xC), ?) != 0 goto L_0x669463d
    // -> if (Dec *u32(rsi+0xC), ?) == 0 goto L_0x6694623
    vtableDestroy(rsi)(rsi);
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(
            &static_cast<RefCountedObject*>(rsi)->weak)) != 0)
        goto L_0x669463d;

L_0x6694623:  // from 0x6694621 (not taken)
    // 0x6694623  mov rax,[rsi]
    // 0x6694626  mov rax,[rax+8]
    // 0x669462a  mov rdx,[0xF99FFA0]
    // 0x6694631  mov rcx,rsi
    // 0x6694634  add rsp,0x28
    // 0x6694638  pop rdi
    // 0x6694639  pop rsi
    // 0x669463a  jmp rdx       ; tail call vtable[1](rsi) via thunk
    // -> (fall-through / ret / end)
    return reinterpret_cast<uintptr_t>(vtableDealloc(rsi)(rsi));

L_0x669463d:  // from 0x6694606, 0x669460c, 0x6694621
    // 0x669463d  add rsp,0x28
    // 0x6694641  pop rdi
    // 0x6694642  pop rsi
    // 0x6694643  ret
    // -> (fall-through / ret / end)
    return 0;

L_0x6694644:  // from 0x6694599
    // 0x6694644  mov qword ptr [rsp+0x20],0
    // 0x669464d  xor ecx,ecx
    // 0x669464f  xor edx,edx
    // 0x6694651  xor r8d,r8d
    // 0x6694654  xor r9d,r9d
    // 0x6694657  call qword ptr [0xF9A8C78]
    // 0x669465d  int3
    // -> (fall-through / ret / end)
    reportFatalFailure();
    __assume(false);
}

static_assert(sizeof(void*) == 8, "6694560: x64 ABI, pointer-sized address space");

// Verbatim call instructions from the disassembly of [0x6694560, 0x669465e) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x66945a9  call 0xE935700
0x66945e3  call qword ptr [0xF99FFA0]
0x66945f9  call qword ptr [0xF99FFA0]
0x6694617  call qword ptr [0xF99FFA0]
0x6694657  call qword ptr [0xF9A8C78]
#endif

LIFT_FN(sub_6694560, "sub_6694560", 0x6694560, sub_6694560, nullptr);

} // namespace native::helpers
