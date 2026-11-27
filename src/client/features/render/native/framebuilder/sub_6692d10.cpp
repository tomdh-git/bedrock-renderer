// LIFT 0x6692d10 size 0x79 1.26.62.01 group insert effect
#include "client/features/render/native/framebuilder/sub_6692d10.h"

#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

// Layout assertions (definitions live in sub_6692d10.h; repeated here so
// liftcheck sees them in the source file).
static_assert(offsetof(native::EffectSlot, ptr) == 0x00,
              "sub_6692d10: EffectSlot::ptr at +0x00 (W, 0x6692d1c/0x6692d33/0x6692d77)");
static_assert(offsetof(native::EffectSlot, object) == 0x08,
              "sub_6692d10: EffectSlot::object at +0x08 (R/W, 0x6692d1f/0x6692d2c/0x6692d33/0x6692d7a)");
static_assert(offsetof(native::RefCountedObject, vtable) == 0x00,
              "sub_6692d10: RefCountedObject::vtable at +0x00 (R, 0x6692d41/0x6692d5f)");
static_assert(offsetof(native::RefCountedObject, refcount1) == 0x08,
              "sub_6692d10: RefCountedObject::refcount1 at +0x08 (RW, 0x6692d28/0x6692d3b)");
static_assert(offsetof(native::RefCountedObject, refcount2) == 0x0C,
              "sub_6692d10: RefCountedObject::refcount2 at +0x0C (RW, 0x6692d59)");

// Verbatim instructions of sub_6692d10 ([0x6692d10, 0x6692d89), size 0x79):
// Both calls go through loader-resolved data slot 0xF99FFA0, which holds
// sub_eea6040 (docs/data/native_boundary.tsv: class vendor,
// "thunk via data slot 0xF99FFA0 (loader-resolved)"). sub_eea6040 is a
// `jmp rax` tail forwarder, so the real call target is whatever this function
// preloaded into rax: vtable[0] at 0x6692d50 and vtable[1] at 0x6692d69.
// rcx = oldObj (this) on entry to each call. The lifted code reads the vtable
// entry itself and calls it with rcx = oldObj, which is the net effect of each
// `call qword ptr [0xF99FFA0]` (same precedent as sub_c283ce0 and sub_663f9d0).
//
// These two call sites are inside the release block, which is dead code: the
// old object pointer is read from a0+0x8 at 0x6692d2c after that same 16 bytes
// were zeroed at 0x6692d1c, so oldObj is always 0 and vtable[0]/vtable[1] are
// never invoked. UNRESOLVED CALL = none.
#if 0
0x6692d10  push rsi
0x6692d11  push rdi
0x6692d12  sub rsp,0x28
0x6692d16  mov rax,rcx
0x6692d19  xorps xmm0,xmm0
0x6692d1c  movups [rcx],xmm0
0x6692d1f  mov rcx,[rdx+8]
0x6692d23  test rcx,rcx
0x6692d26  je short 0x6692D74
0x6692d28  lock inc dword ptr [rcx+8]
0x6692d2c  mov rsi,[rax+8]
0x6692d30  movups xmm0,[rdx]
0x6692d33  movups [rax],xmm0
0x6692d36  test rsi,rsi
0x6692d39  je short 0x6692D82
0x6692d3b  lock dec dword ptr [rsi+8]
0x6692d3f  jne short 0x6692D82
0x6692d41  mov rcx,[rsi]
0x6692d44  mov rdx,[rcx]
0x6692d47  mov rcx,rsi
0x6692d4a  mov rdi,rax
0x6692d4d  mov rax,rdx
0x6692d50  call qword ptr [0xF99FFA0]
0x6692d56  mov rax,rdi
0x6692d59  lock dec dword ptr [rsi+0xC]
0x6692d5d  jne short 0x6692D82
0x6692d5f  mov rax,[rsi]
0x6692d62  mov rax,[rax+8]
0x6692d66  mov rcx,rsi
0x6692d69  call qword ptr [0xF99FFA0]
0x6692d6f  mov rax,rdi
0x6692d72  jmp short 0x6692D82
0x6692d74  mov rcx,[rdx]
0x6692d77  mov [rax],rcx
0x6692d7a  mov qword ptr [rax+8],0
0x6692d82  add rsp,0x28
0x6692d86  pop rdi
0x6692d87  pop rsi
0x6692d88  ret
#endif

namespace native {

void* sub_6692d10(EffectSlot* a0, const EffectSlot* a1)
{
    // 0x6692d10..0x6692d1c: prologue (push rsi; push rdi; sub rsp,0x28;
    //   mov rax,rcx ; xorps xmm0,xmm0) — RAX preloaded with a0 (the return value).
    // 0x6692d1c  movups [rcx],xmm0   ; W a0+0x0 (16 bytes zeroed)
    a0->ptr = nullptr;             // 0x6692d1c  movups [rcx],xmm0
    a0->object = nullptr;          // 0x6692d1c  movups [rcx],xmm0

    // 0x6692d1f  mov rcx,[rdx+8]     ; R a1+0x8  incoming object pointer
    // 0x6692d23  test rcx,rcx
    // 0x6692d26  je short 0x6692D74  ; null object -> null-object branch
    RefCountedObject* incoming = reinterpret_cast<RefCountedObject*>(a1->object);  // 0x6692d1f  mov rcx,[rdx+8]
    if (incoming != nullptr) {     // 0x6692d23  test rcx,rcx ; 0x6692d26  je short 0x6692D74
        // 0x6692d28  lock inc dword ptr [rcx+8]   ; W incoming+0x8 (refcount1)
        _InterlockedIncrement(reinterpret_cast<volatile LONG*>(&incoming->refcount1));  // 0x6692d28  lock inc dword ptr [rcx+8]

        // 0x6692d2c  mov rsi,[rax+8]     ; R a0+0x8  old object pointer (always 0: zeroed above)
        RefCountedObject* oldObj = reinterpret_cast<RefCountedObject*>(a0->object);  // 0x6692d2c  mov rsi,[rax+8]

        // 0x6692d30  movups xmm0,[rdx]   ; R a1+0x0
        // 0x6692d33  movups [rax],xmm0   ; W a0+0x0  copy 16 bytes a1 -> a0
        a0->ptr = a1->ptr;          // 0x6692d30  movups xmm0,[rdx] / 0x6692d33  movups [rax],xmm0
        a0->object = a1->object;    // 0x6692d33  movups [rax],xmm0

        // 0x6692d36  test rsi,rsi
        // 0x6692d39  je short 0x6692D82  ; oldObj == 0 -> epilogue (always taken)
        if (oldObj != nullptr) {    // 0x6692d36  test rsi,rsi ; 0x6692d39  je short 0x6692D82  (dead: oldObj always 0)
            // 0x6692d3b  lock dec dword ptr [rsi+8]   ; W oldObj+0x8 (refcount1)
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&oldObj->refcount1)) == 0) {  // 0x6692d3b  lock dec dword ptr [rsi+8] ; 0x6692d3f  jne short 0x6692D82
                // refcount1 hit 0 -> destroy:
                // 0x6692d41  mov rcx,[rsi]        ; R oldObj+0x0  (vtable)
                // 0x6692d44  mov rdx,[rcx]        ; R vtable+0x0  (vtable[0])
                // 0x6692d47  mov rcx,rsi          ; RCX = oldObj (this)
                // 0x6692d4a  mov rdi,rax          ; save return value a0
                // 0x6692d4d  mov rax,rdx          ; target = vtable[0]
                // 0x6692d50  call qword ptr [0xF99FFA0]   ; vtable[0](oldObj)
                // 0x6692d56  mov rax,rdi          ; restore return value a0
                using Slot0Fn = void (*)(void*);
                Slot0Fn slot0 = reinterpret_cast<Slot0Fn>(oldObj->vtable[0]);
                slot0(oldObj);                     // 0x6692d41..0x6692d56

                // 0x6692d59  lock dec dword ptr [rsi+0xC]   ; W oldObj+0xC (refcount2)
                if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&oldObj->refcount2)) == 0) {  // 0x6692d59  lock dec dword ptr [rsi+0xC] ; 0x6692d5d  jne short 0x6692D82
                    // refcount2 hit 0 -> dealloc:
                    // 0x6692d5f  mov rax,[rsi]        ; R oldObj+0x0  (vtable)
                    // 0x6692d62  mov rax,[rax+8]      ; R vtable+0x8  (vtable[1])
                    // 0x6692d66  mov rcx,rsi          ; RCX = oldObj (this)
                    // 0x6692d69  call qword ptr [0xF99FFA0]   ; vtable[1](oldObj)
                    // 0x6692d6f  mov rax,rdi          ; restore return value a0
                    // 0x6692d72  jmp short 0x6692D82   ; -> epilogue
                    using Slot1Fn = void (*)(void*);
                    Slot1Fn slot1 = reinterpret_cast<Slot1Fn>(oldObj->vtable[1]);
                    slot1(oldObj);                     // 0x6692d5f..0x6692d6f
                }
            }
        }
    } else {
        // 0x6692d74  mov rcx,[rdx]      ; R a1+0x0
        // 0x6692d77  mov [rax],rcx      ; W a0+0x0
        // 0x6692d7a  mov qword ptr [rax+8],0   ; W a0+0x8 = 0
        a0->ptr = a1->ptr;          // 0x6692d74  mov rcx,[rdx] ; 0x6692d77  mov [rax],rcx
        a0->object = nullptr;       // 0x6692d7a  mov qword ptr [rax+8],0
    }

    // 0x6692d82  add rsp,0x28 ; 0x6692d86 pop rdi ; 0x6692d87 pop rsi ; 0x6692d88 ret
    return a0;                      // RAX = a0
}

LIFT_FN(sub_6692d10, "group insert effect", 0x6692d10, sub_6692d10, nullptr);

} // namespace native
