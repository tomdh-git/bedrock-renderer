// LIFT 0x67c4650 size 0xc1 1.26.62.01 BgfxFrameBuilder slot 17
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/framebuilder/sub_67c4650.h"

#include <cstdint>
#include <intrin.h>

// Layout assertions (definitions and the full set of offset static_asserts live in
// sub_67c4650.h; repeated here so liftcheck sees them in the source file).
static_assert(offsetof(native::FrameBuilderSlot17, objectC) == 0x20,
              "sub_67c4650: a1+0x20 is object C pointer (R)");
static_assert(offsetof(native::FrameBuilderSlot17, objectB) == 0x30,
              "sub_67c4650: a1+0x30 is object B pointer (R)");
static_assert(offsetof(native::FrameBuilderSlot17, objectA) == 0x38,
              "sub_67c4650: a1+0x38 is object A pointer (R)");
static_assert(offsetof(native::RefCountedObj, vtable) == 0x00,
              "sub_67c4650: refcounted object vtable at +0x00 (R)");
static_assert(offsetof(native::RefCountedObj, refcount1) == 0x08,
              "sub_67c4650: refcounted object refcount1 at +0x08 (RW)");
static_assert(offsetof(native::RefCountedObj, refcount2) == 0x0C,
              "sub_67c4650: refcounted object refcount2 at +0x0C (RW)");
static_assert(offsetof(native::RefCountedObj, backObject) == 0xF0,
              "sub_67c4650: object A back-pointer at +0xF0 (R)");

namespace native {

// sub_eea6040 (0xEEA6040, class vendor, docs/data/native_boundary.tsv line 506) is reached through
// data slot 0xF99FFA0: the original does `call qword ptr [0xF99FFA0]` after loading RAX = the
// vtable slot to invoke; sub_eea6040 is a `jmp rax` thunk, so each call is an indirect virtual
// call whose target the original already loaded into RAX. Lifted code invokes that vtable slot
// directly (same target, same arguments RCX=obj, RDX=context); slot RVA 0xF99FFA0 documented.
// sub_e935700 (0xE935700, class lift, forward-declared in sub_67c4650.h) is the tail-jump target.

static void vtableCallSlot0(void* obj, void* context) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*, void*)>(vt[0])(obj, context);  // virtual slot 0
}
static void vtableCallSlot1(void* obj, void* context) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*, void*)>(vt[1])(obj, context);  // virtual slot 1
}

// sub_67c4650(a1 = rdx) -> void*. Release up to three refcounted objects (a1+0x38 object A,
// a1+0x30 object B, a1+0x20 object C), calling the object's vtable slot when a refcount reaches
// zero, then tail-jump to sub_e935700(a1). No null guard or SEH in the original (none added).
void* sub_67c4650(void* /*dead_rcx*/, FrameBuilderSlot17* a1) {
    // 0x67c4650  push rsi
    // 0x67c4651  push rdi
    // 0x67c4652  sub rsp,0x28
    // 0x67c4656  mov rsi,rdx               ; a1 = rdx (RCX entry arg is dead)
    FrameBuilderSlot17* a = a1;           // 0x67c4656  mov rsi,rdx

    // ---- object A (a1+0x38) ----
    // 0x67c4659  mov rdx,[rdx+0x38]        ; objA = a1+0x38
    // 0x67c465d  test rdx,rdx
    // 0x67c4660  je short 0x67C4696        ; if objA == 0, skip to object B
    RefCountedObj* objA = a->objectA;     // 0x67c4659
    if (objA != nullptr) {                // 0x67c465d..0x67c4660
        // 0x67c4662  lock dec dword ptr [rdx+8]
        // 0x67c4666  jne short 0x67C4696   ; if refcount1 != 0, skip to object B
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&objA->refcount1)) == 0) {  // 0x67c4662..0x67c4666
            // 0x67c4668  mov rcx,[rdx+0xF0]   ; objB = objA+0xF0
            // 0x67c466f  test rcx,rcx
            // 0x67c4672  je short 0x67C4682   ; if objB == 0 -> null-back-pointer path
            RefCountedObj* objB = objA->backObject;  // 0x67c4668
            if (objB != nullptr) {            // 0x67c466f..0x67c4672
                // 0x67c4674  mov rax,[rcx]      ; R vtable pointer (objB)
                // 0x67c4677  mov rax,[rax]      ; R vtable[0]
                // 0x67c467a  call qword ptr [0xF99FFA0]  ; vtable[0](objB, objA)
                // 0x67c4680  jmp short 0x67C4696  ; -> object B
                vtableCallSlot0(objB, objA);  // 0x67c4674..0x67c4680
            } else {
                // loc_67c4682:
                // 0x67c4682  mov rax,[rdx]          ; R objA vtable pointer
                // 0x67c4685  mov rax,[rax]          ; R vtable[0]
                // 0x67c4688  mov rcx,rdx            ; RCX = objA
                // 0x67c468b  mov edx,1              ; RDX = 1
                // 0x67c4690  call qword ptr [0xF99FFA0]  ; vtable[0](objA, reinterpret_cast<void*>(1))
                vtableCallSlot0(objA, reinterpret_cast<void*>(1));  // 0x67c4682..0x67c4690
            }
            // fall through to object B
        }
    }

    // ---- object B (a1+0x30) ----
    // 0x67c4696  mov rdi,[rsi+0x30]        ; objB2 = a1+0x30
    // 0x67c469a  test rdi,rdi
    // 0x67c469d  je short 0x67C46CA        ; if objB2 == 0, skip to object C
    RefCountedObj* objB2 = a->objectB;    // 0x67c4696
    if (objB2 != nullptr) {               // 0x67c469a..0x67c469d
        // 0x67c469f  lock dec dword ptr [rdi+8]
        // 0x67c46a3  jne short 0x67C46CA   ; if refcount1 != 0, skip to object C
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&objB2->refcount1)) == 0) {  // 0x67c469f..0x67c46a3
            // 0x67c46a5  mov rax,[rdi]      ; R vtable pointer
            // 0x67c46a8  mov rax,[rax]      ; R vtable[0]
            // 0x67c46ab  mov rcx,rdi        ; RCX = objB2
            // 0x67c46ae  call qword ptr [0xF99FFA0]  ; vtable[0](objB2, objA)
            vtableCallSlot0(objB2, objA);  // 0x67c46a5..0x67c46ae
            // 0x67c46b4  lock dec dword ptr [rdi+0xC]
            // 0x67c46b8  jne short 0x67C46CA  ; if refcount2 != 0, skip to object C
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&objB2->refcount2)) == 0) {  // 0x67c46b4..0x67c46b8
                // 0x67c46ba  mov rax,[rdi]      ; R vtable pointer
                // 0x67c46bd  mov rax,[rax+8]    ; R vtable[1]
                // 0x67c46c1  mov rcx,rdi        ; RCX = objB2
                // 0x67c46c4  call qword ptr [0xF99FFA0]  ; vtable[1](objB2, objA)
                vtableCallSlot1(objB2, objA);  // 0x67c46ba..0x67c46c4
            }
        }
    }

    // ---- object C (a1+0x20) ----
    // 0x67c46ca  mov rdi,[rsi+0x20]        ; objC = a1+0x20
    // 0x67c46ce  test rdi,rdi
    // 0x67c46d1  je short 0x67C46FE        ; if objC == 0, skip to tail
    RefCountedObj* objC = a->objectC;     // 0x67c46ca
    if (objC != nullptr) {                // 0x67c46ce..0x67c46d1
        // 0x67c46d3  lock dec dword ptr [rdi+8]
        // 0x67c46d7  jne short 0x67C46FE   ; if refcount1 != 0, skip to tail
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&objC->refcount1)) == 0) {  // 0x67c46d3..0x67c46d7
            // 0x67c46d9  mov rax,[rdi]      ; R vtable pointer
            // 0x67c46dc  mov rax,[rax]      ; R vtable[0]
            // 0x67c46df  mov rcx,rdi        ; RCX = objC
            // 0x67c46e2  call qword ptr [0xF99FFA0]  ; vtable[0](objC, objA)
            vtableCallSlot0(objC, objA);  // 0x67c46d9..0x67c46e2
            // 0x67c46e8  lock dec dword ptr [rdi+0xC]
            // 0x67c46ec  jne short 0x67C46FE  ; if refcount2 != 0, skip to tail
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&objC->refcount2)) == 0) {  // 0x67c46e8..0x67c46ec
                // 0x67c46ee  mov rax,[rdi]      ; R vtable pointer
                // 0x67c46f1  mov rax,[rax+8]    ; R vtable[1]
                // 0x67c46f5  mov rcx,rdi        ; RCX = objC
                // 0x67c46f8  call qword ptr [0xF99FFA0]  ; vtable[1](objC, objA)
                vtableCallSlot1(objC, objA);  // 0x67c46ee..0x67c46f8
            }
        }
    }

    // 0x67c46fe  mov edx,0x48               ; EDX is dead: sub_e935700/sub_392960 read only RCX
    // 0x67c4703  mov rcx,rsi                ; RCX = a1
    // 0x67c4706  add rsp,0x28
    // 0x67c470a  pop rdi
    // 0x67c470b  pop rsi
    // 0x67c470c  jmp 0xE935700              ; tail jump -> sub_e935700(a1)
    return sub_e935700(a);                // 0x67c46fe..0x67c470c
}

// Verbatim instructions of the function (matches `rdis dis 0x67c4650 0xc1` from the exe,
// machine-checked with tools/sigs/verify_oc.py). Branch targets keep the rdis hex casing.
// All six `call qword ptr [0xF99FFA0]` are indirect virtual calls (sub_eea6040 is a `jmp rax`
// thunk); the target vtable slot is loaded into RAX before each. sub_e935700 is class "lift".
#if 0
0x67c4650  push rsi
0x67c4651  push rdi
0x67c4652  sub rsp,0x28
0x67c4656  mov rsi,rdx
0x67c4659  mov rdx,[rdx+0x38]
0x67c465d  test rdx,rdx
0x67c4660  je short 0x67C4696
0x67c4662  lock dec dword ptr [rdx+8]
0x67c4666  jne short 0x67C4696
0x67c4668  mov rcx,[rdx+0xF0]
0x67c466f  test rcx,rcx
0x67c4672  je short 0x67C4682
0x67c4674  mov rax,[rcx]
0x67c4677  mov rax,[rax]
0x67c467a  call qword ptr [0xF99FFA0]
0x67c4680  jmp short 0x67C4696
0x67c4682  mov rax,[rdx]
0x67c4685  mov rax,[rax]
0x67c4688  mov rcx,rdx
0x67c468b  mov edx,1
0x67c4690  call qword ptr [0xF99FFA0]
0x67c4696  mov rdi,[rsi+0x30]
0x67c469a  test rdi,rdi
0x67c469d  je short 0x67C46CA
0x67c469f  lock dec dword ptr [rdi+8]
0x67c46a3  jne short 0x67C46CA
0x67c46a5  mov rax,[rdi]
0x67c46a8  mov rax,[rax]
0x67c46ab  mov rcx,rdi
0x67c46ae  call qword ptr [0xF99FFA0]
0x67c46b4  lock dec dword ptr [rdi+0xC]
0x67c46b8  jne short 0x67C46CA
0x67c46ba  mov rax,[rdi]
0x67c46bd  mov rax,[rax+8]
0x67c46c1  mov rcx,rdi
0x67c46c4  call qword ptr [0xF99FFA0]
0x67c46ca  mov rdi,[rsi+0x20]
0x67c46ce  test rdi,rdi
0x67c46d1  je short 0x67C46FE
0x67c46d3  lock dec dword ptr [rdi+8]
0x67c46d7  jne short 0x67C46FE
0x67c46d9  mov rax,[rdi]
0x67c46dc  mov rax,[rax]
0x67c46df  mov rcx,rdi
0x67c46e2  call qword ptr [0xF99FFA0]
0x67c46e8  lock dec dword ptr [rdi+0xC]
0x67c46ec  jne short 0x67C46FE
0x67c46ee  mov rax,[rdi]
0x67c46f1  mov rax,[rax+8]
0x67c46f5  mov rcx,rdi
0x67c46f8  call qword ptr [0xF99FFA0]
0x67c46fe  mov edx,0x48
0x67c4703  mov rcx,rsi
0x67c4706  add rsp,0x28
0x67c470a  pop rdi
0x67c470b  pop rsi
0x67c470c  jmp 0xE935700
#endif

LIFT_FN(sub_67c4650, "sub_67c4650", 0x67c4650, sub_67c4650, nullptr);

} // namespace native
