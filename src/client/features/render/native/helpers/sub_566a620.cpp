// LIFT 0x566a620 size 0xf2 1.26.62.01 sub_566a620
#include "client/features/render/native/helpers/sub_566a620.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

static_assert(sizeof(std::uintptr_t) == 8, "566a620: uintptr_t is 8 bytes on x64");
static_assert(sizeof(std::uint32_t) == 4, "566a620: uint32_t is 4 bytes on x64");

// Verbatim call instructions from the disassembly of [0x566a620, 0x566a712) (rdis `fn` output):
//   0x566a66c  call 0xE935700            ; direct, sub_e935700 (lift: `jmp 0x392960`, depth 0)
//   0x566a697  call qword ptr [0xF99FFA0]; vtable slot 0 (destroy) of mRefCountedA via the jmp-rax thunk
//   0x566a6ad  call qword ptr [0xF99FFA0]; vtable slot 1 (dealloc) of mRefCountedA via the jmp-rax thunk
//   0x566a6cb  call qword ptr [0xF99FFA0]; vtable slot 0 (destroy) of mRefCountedB via the jmp-rax thunk
//   0x566a70b  call qword ptr [0xF9A8C78]; data slot, loader-patched invalid-parameter handler (_invoke_watson-like), noreturn
// No lift-set callees other than sub_e935700 (called directly, forward-declared in the header).
// UNRESOLVED CALL = none.
using DestroyFn = void (*)(void*);
using DeallocFn = void (*)(void*);

static DestroyFn vtableDestroy(void* obj) {   // 0x566a68e/0x566a6c2  mov rax,[obj]; mov rax,[rax]   (vtable[0] at +0x00)
    void** vt = reinterpret_cast<void**>(obj);
    return reinterpret_cast<DestroyFn>(vt[0]);
}
static DeallocFn vtableDealloc(void* obj) {   // 0x566a6a6/0x566a6da  mov rax,[obj]; mov rax,[rax+8] (vtable[1] at +0x08; vptr re-read after destroy)
    void** vt = reinterpret_cast<void**>(obj);
    return reinterpret_cast<DeallocFn>(vt[1]);
}

// 0x566a6f8..0x566a712: the validation-failure path. [rsp+0x20] = 0 (5th stack arg),
// ecx=edx=r8d=r9d=0 (first four args), then `0x566a70b  call qword ptr [0xF9A8C78]`
// -- the data slot holds a loader-patched invalid-parameter handler; the disassembly
// follows the call with int3 padding, so the target is noreturn and control never
// continues here.
[[noreturn]] static void reportWatsonFailure() {
    //   0x566a6f8  mov qword ptr [rsp+0x20],0
    //   0x566a701  xor ecx,ecx
    //   0x566a703  xor edx,edx
    //   0x566a705  xor r8d,r8d
    //   0x566a708  xor r9d,r9d
    //   0x566a70b  call qword ptr [0xF9A8C78]
    using Watson = std::uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, std::uintptr_t);
    reinterpret_cast<Watson>(*reinterpret_cast<std::uintptr_t*>(
        RewriteRegistry::imageBase() + 0xF9A8C78))(nullptr, nullptr, nullptr, 0, 0);
    //   0x566a711  int3   (padding after the noreturn call; unreachable)
    __assume(false);
}

void sub_566a620(sub_566a620_state* self) {
    // x64 Microsoft ABI: rcx = self (the state object).
    // Returns void: rax is dead at ret on all non-tail-call paths.

    // Prologue/epilogue (stack frame only, no observable effect):
    //   0x566a620  push rsi
    //   0x566a621  push rdi
    //   0x566a622  sub rsp,0x28
    //   ...
    //   0x566a6e8  add rsp,0x28
    //   0x566a6ec  pop rdi
    //   0x566a6ed  pop rsi
    //   0x566a6ee  jmp rdx   (tail call, from the mRefCountedB dealloc path)
    //   0x566a6f1  add rsp,0x28
    //   0x566a6f5  pop rdi
    //   0x566a6f6  pop rsi
    //   0x566a6f7  ret

    // 0x566a620..0x566a630
    //   0x566a620  push rsi
    //   0x566a621  push rdi
    //   0x566a622  sub rsp,0x28
    //   0x566a626  cmp byte ptr [rcx+0x40],1
    //   0x566a62a  jne 0x566A6F1   ; if mFlag != 1, goto L_0x566a6f1 (return)
    if (self->mFlag != 1) {
        // 0x566a6f1..0x566a6f8
        //   0x566a6f1  add rsp,0x28
        //   0x566a6f5  pop rdi
        //   0x566a6f6  pop rsi
        //   0x566a6f7  ret
        return;
    }

    // 0x566a630..0x566a63c
    //   0x566a630  mov rsi,rcx                 ; rsi = self
    //   0x566a633  mov rcx,[rcx+0x28]          ; rcx = self->mData
    //   0x566a637  test rcx,rcx
    //   0x566a63a  je short 0x566A67F          ; if mData == 0, goto L_0x566a67f
    void* buf = self->mData;
    if (buf != 0) {
        // 0x566a63c..0x566a64c
        //   0x566a63c  mov rdx,[rsi+0x38]     ; rdx = self->mDataEnd
        //   0x566a640  sub rdx,rcx            ; rdx = mDataEnd - mData (size)
        //   0x566a643  cmp rdx,0x1000
        //   0x566a64a  jb short 0x566A668     ; if size <u 0x1000, goto L_0x566a668
        std::uintptr_t size = self->mDataEnd - reinterpret_cast<std::uintptr_t>(buf);
        if (size < 0x1000ull) {
            // 0x566a668..0x566a67f
            //   0x566a668  lea rdi,[rsi+0x28]         ; rdi = &self->mData
            //   0x566a66c  call 0xE935700             ; sub_e935700(mData, size)
            //   0x566a671  xorps xmm0,xmm0
            //   0x566a674  movups [rdi],xmm0         ; self->mData = 0
            //   0x566a677  mov qword ptr [rdi+0x10],0 ; self->mDataEnd = 0
            native::sub_e935700(reinterpret_cast<std::uintptr_t>(buf), size);
            self->mData = nullptr;
            self->mDataEnd = 0;
        } else {
            // 0x566a64c..0x566a661
            //   0x566a64c  mov rax,[rcx-8]            ; rax = *(mData - 8)
            //   0x566a650  add rcx,0xFFFFFFFFFFFFFFF8 ; rcx = mData - 8
            //   0x566a654  sub rcx,rax                ; rcx = (mData - 8) - *(mData - 8)
            //   0x566a657  cmp rcx,0x20
            //   0x566a65b  jae 0x566A6F8              ; if >=u 0x20, goto L_0x566a6f8 (watson)
            const std::uintptr_t hdr = *reinterpret_cast<const std::uintptr_t*>(
                reinterpret_cast<const std::uint8_t*>(buf) - 8);
            const std::uintptr_t delta = (reinterpret_cast<std::uintptr_t>(buf) - 8) - hdr;
            if (delta >= 0x20ull) {
                // 0x566a6f8..0x566a712
                //   0x566a6f8  mov qword ptr [rsp+0x20],0
                //   0x566a701  xor ecx,ecx
                //   0x566a703  xor edx,edx
                //   0x566a705  xor r8d,r8d
                //   0x566a708  xor r9d,r9d
                //   0x566a70b  call qword ptr [0xF9A8C78]   ; watson (noreturn)
                //   0x566a711  int3   (padding)
                reportWatsonFailure();
                __assume(false);
            }
            // 0x566a661..0x566a668
            //   0x566a661  add rdx,0x27          ; rdx = size + 0x27
            //   0x566a665  mov rcx,rax           ; rcx = hdr = *(mData - 8)
            // fall through to L_0x566a668
            native::sub_e935700(hdr, size + 0x27ull);
            self->mData = nullptr;
            self->mDataEnd = 0;
        }
    }

    // 0x566a67f..0x566a6b3
    //   0x566a67f  mov rdi,[rsi+0x18]     ; rdi = self->mRefCountedA
    //   0x566a683  test rdi,rdi
    //   0x566a686  je short 0x566A6B3     ; if mRefCountedA == 0, goto L_0x566a6b3
    if (RefCountedObject* objA = reinterpret_cast<RefCountedObject*>(self->mRefCountedA)) {
        // 0x566a688  lock dec dword ptr [rdi+8]
        // 0x566a68c  jne short 0x566A6B3  ; if strong != 0, goto L_0x566a6b3
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&objA->strong)) == 0) {
            // 0x566a68e  mov rax,[rdi]
            // 0x566a691  mov rax,[rax]           ; rax = objA->vptr[0] (destroy)
            // 0x566a694  mov rcx,rdi
            // 0x566a697  call qword ptr [0xF99FFA0]  ; objA->vptr[0](objA) via thunk
            vtableDestroy(objA)(objA);
            // 0x566a69d  lock dec dword ptr [rdi+0xC]
            // 0x566a6a1  jne short 0x566A6B3     ; if weak != 0, goto L_0x566a6b3
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&objA->weak)) == 0) {
                // 0x566a6a3  mov rax,[rdi]
                // 0x566a6a6  mov rax,[rax+8]     ; rax = objA->vptr[1] (dealloc)
                // 0x566a6aa  mov rcx,rdi
                // 0x566a6ad  call qword ptr [0xF99FFA0]  ; objA->vptr[1](objA) via thunk
                vtableDealloc(objA)(objA);
            }
        }
    }

    // 0x566a6b3..0x566a6f1
    //   0x566a6b3  mov rsi,[rsi+8]      ; rsi = self->mRefCountedB
    //   0x566a6b7  test rsi,rsi
    //   0x566a6ba  je short 0x566A6F1   ; if mRefCountedB == 0, goto L_0x566a6f1 (return)
    if (RefCountedObject* objB = reinterpret_cast<RefCountedObject*>(self->mRefCountedB)) {
        // 0x566a6bc  lock dec dword ptr [rsi+8]
        // 0x566a6c0  jne short 0x566A6F1  ; if strong != 0, goto L_0x566a6f1 (return)
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&objB->strong)) == 0) {
            // 0x566a6c2  mov rax,[rsi]
            // 0x566a6c5  mov rax,[rax]           ; rax = objB->vptr[0] (destroy)
            // 0x566a6c8  mov rcx,rsi
            // 0x566a6cb  call qword ptr [0xF99FFA0]  ; objB->vptr[0](objB) via thunk
            vtableDestroy(objB)(objB);
            // 0x566a6d1  lock dec dword ptr [rsi+0xC]
            // 0x566a6d5  jne short 0x566A6F1     ; if weak != 0, goto L_0x566a6f1 (return)
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&objB->weak)) == 0) {
                // 0x566a6d7  mov rax,[rsi]
                // 0x566a6da  mov rax,[rax+8]     ; rax = objB->vptr[1] (dealloc)
                // 0x566a6de  mov rdx,[0xF99FFA0]   ; rdx = thunk address
                // 0x566a6e5  mov rcx,rsi
                // 0x566a6e8  add rsp,0x28
                // 0x566a6ec  pop rdi
                // 0x566a6ed  pop rsi
                // 0x566a6ee  jmp rdx             ; tail call objB->vptr[1](objB) via thunk
                vtableDealloc(objB)(objB);      // tail call; return value is dead
            }
        }
    }

    // 0x566a6f1: add rsp,0x28; pop rdi; pop rsi; ret   (rax undefined)
}

static native::Footprint sub_566a620_footprint(sub_566a620_state* self) {
    // The function writes mData (+0x28) and mDataEnd (+0x38) within *self.
    // Refcount writes to the objects at +0x18/+0x08, the virtual-call targets,
    // and sub_e935700's frees happen outside *self and cannot be declared
    // statically.
    return {{self, 0x41ull}};
}

LIFT_FN(sub_566a620, "sub_566a620", 0x566a620, sub_566a620, sub_566a620_footprint);

} // namespace native::helpers
