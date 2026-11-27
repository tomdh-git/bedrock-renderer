// LIFT 0x663f9d0 size 0x54 1.26.62.01 BgfxFrameBuilder slot 50
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/framebuilder/sub_663f9d0.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

// Layout assertions (definitions and the full set of offset static_asserts live in
// sub_663f9d0.h; repeated here so liftcheck sees them in the source file).
static_assert(offsetof(native::FrameBuilderSlot50, obj0x48) == 0x48,
              "sub_663f9d0: a1+0x48 is the object pointer field (R, 0x663f9dc)");
static_assert(offsetof(native::FrameBuilderSlot50, releaseFlag0x50) == 0x50,
              "sub_663f9d0: a1+0x50 is the release flag field (R/W, 0x663f9d6/0x663fa19)");
static_assert(offsetof(native::RefCountedObj, vtable) == 0x00,
              "sub_663f9d0: refcounted object vtable at +0x00 (R, 0x663f9eb/0x663fa06)");
static_assert(offsetof(native::RefCountedObj, refcount1) == 0x08,
              "sub_663f9d0: refcounted object refcount1 at +0x08 (RW, 0x663f9e5)");
static_assert(offsetof(native::RefCountedObj, refcount2) == 0x0C,
              "sub_663f9d0: refcounted object refcount2 at +0x0C (RW, 0x663fa00)");

// Verbatim instructions of the function (matches rdis dis 0x663f9d0 0x54, copied from
// the exe listing and machine-checked with tools/sigs/verify_oc.py).
// Both calls go through data slot [0xF99FFA0] = sub_eea6040, a `jmp rax` thunk, so each is an
// indirect virtual call whose target (vtable slot) was already loaded into RAX:
//   0x663f9f7: RAX = vtable[0](obj), RCX = obj, RDX = a1   -> vtableCallSlot0(obj, a1)
//   0x663fa10: RAX = vtable[1](obj), RCX = obj, RDX = a1   -> vtableCallSlot1(obj, a1)
// sub_eea6040 is class "vendor" in docs/data/native_boundary.tsv ("thunk via data slot 0xF99FFA0").
// Following the sub_bc2bca0 precedent, these are direct virtual calls in lifted code, not boundary calls.
// UNRESOLVED CALL = none.
#if 0
0x663f9d0  push rsi
0x663f9d1  push rdi
0x663f9d2  sub rsp,0x28
0x663f9d6  cmp byte ptr [rdx+0x50],1
0x663f9da  jne short 0x663FA1D
0x663f9dc  mov rsi,[rdx+0x48]
0x663f9e0  test rsi,rsi
0x663f9e3  je short 0x663FA19
0x663f9e5  lock dec dword ptr [rsi+8]
0x663f9e9  jne short 0x663FA19
0x663f9eb  mov rax,[rsi]
0x663f9ee  mov rax,[rax]
0x663f9f1  mov rcx,rsi
0x663f9f4  mov rdi,rdx
0x663f9f7  call qword ptr [0xF99FFA0]
0x663f9fd  mov rdx,rdi
0x663fa00  lock dec dword ptr [rsi+0xC]
0x663fa04  jne short 0x663FA19
0x663fa06  mov rax,[rsi]
0x663fa09  mov rax,[rax+8]
0x663fa0d  mov rcx,rsi
0x663fa10  call qword ptr [0xF99FFA0]
0x663fa16  mov rdx,rdi
0x663fa19  mov byte ptr [rdx+0x50],0
0x663fa1d  add rsp,0x28
0x663fa21  pop rdi
0x663fa22  pop rsi
0x663fa23  ret
#endif

namespace native {

// sub_eea6040 ([data_f99ffa0]) is a `jmp rax` thunk, so each `call qword ptr [0xF99FFA0]`
// above is an indirect virtual call whose target (vtable slot) the original already loaded
// into rax. Reads: [obj] (vtable pointer) and [vtable + slot*8]; call: target(obj, a1) with
// rcx=obj, rdx=a1.
static void vtableCallSlot0(void* obj, void* a1) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*, void*)>(vt[0])(obj, a1);  // 0x663f9f7  call qword ptr [0xF99FFA0]
}
static void vtableCallSlot1(void* obj, void* a1) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*, void*)>(vt[1])(obj, a1);  // 0x663fa10  call qword ptr [0xF99FFA0]
}

// sub_0x663f9d0(a1 = rdx) -> void.
// Release pattern: if a1->releaseFlag0x50 == 1, decrements two refcounts on a1->obj0x48,
// calling vtable[0] and/or vtable[1] when each hits zero, then always clears the flag.
// Every block carries the instruction range it implements; every call is quoted verbatim above.
// 0x663f9d0..0x663f9d2: prologue (push rsi, push rdi, sub rsp,0x28) — no observable effect.
void sub_663f9d0(void* /*dead_rcx*/, FrameBuilderSlot50* a1) {
    // 0x663f9d6  cmp byte ptr [rdx+0x50],1
    // 0x663f9da  jne short 0x663FA1D        ; if flag != 1, skip to epilogue
    if (a1->releaseFlag0x50 != 1) {        // 0x663f9d6..0x663f9da
        return;                            // 0x663fa1d..0x663fa23  epilogue (add rsp,0x28; pop rdi; pop rsi; ret)
    }

    // 0x663f9dc  mov rsi,[rdx+0x48]         ; obj = a1+0x48
    // 0x663f9e0  test rsi,rsi
    // 0x663f9e3  je short 0x663FA19         ; if obj == 0, skip to flag clear
    RefCountedObj* obj = a1->obj0x48;      // 0x663f9dc
    if (obj != nullptr) {                  // 0x663f9e0..0x663f9e3
        // 0x663f9e5  lock dec dword ptr [rsi+8]
        // 0x663f9e9  jne short 0x663FA19    ; if refcount1 != 0, skip to flag clear
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&obj->refcount1)) == 0) {  // 0x663f9e5..0x663f9e9
            // 0x663f9eb  mov rax,[rsi]      ; R vtable pointer
            // 0x663f9ee  mov rax,[rax]      ; R vtable[0]
            // 0x663f9f1  mov rcx,rsi        ; RCX = obj
            // 0x663f9f4  mov rdi,rdx        ; save RDX=a1
            // 0x663f9f7  call qword ptr [0xF99FFA0]  ; vtable[0](obj, a1)
            // 0x663f9fd  mov rdx,rdi        ; restore RDX=a1
            vtableCallSlot0(obj, a1);      // 0x663f9eb..0x663f9fd
            // 0x663fa00  lock dec dword ptr [rsi+0xC]
            // 0x663fa04  jne short 0x663FA19 ; if refcount2 != 0, skip to flag clear
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&obj->refcount2)) == 0) {  // 0x663fa00..0x663fa04
                // 0x663fa06  mov rax,[rsi]      ; R vtable pointer
                // 0x663fa09  mov rax,[rax+8]    ; R vtable[1]
                // 0x663fa0d  mov rcx,rsi        ; RCX = obj
                // 0x663fa10  call qword ptr [0xF99FFA0]  ; vtable[1](obj, a1)
                // 0x663fa16  mov rdx,rdi        ; restore RDX=a1
                vtableCallSlot1(obj, a1);  // 0x663fa06..0x663fa16
            }
        }
    }

    // 0x663fa19  mov byte ptr [rdx+0x50],0   ; W a1+0x50 = 0
    a1->releaseFlag0x50 = 0;               // 0x663fa19
    // 0x663fa1d  add rsp,0x28; 0x663fa21 pop rdi; 0x663fa22 pop rsi; 0x663fa23 ret
}

LIFT_FN(sub_663f9d0, "sub_663f9d0", 0x663f9d0, sub_663f9d0, nullptr);

} // namespace native
