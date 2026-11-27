// LIFT 0xc25f680 size 0x77 1.26.62.01 BgfxFrameBuilder::endFrame
#include "client/features/render/native/dragon/BgfxFrameBuilder_endFrame.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

static_assert(sizeof(void*) == 8, "c25f680: x64 ABI, pointer-sized address space");
static_assert(offsetof(native::BgfxFrameBuilder, field0x88) == 0x88, "c25f680: field0x88 at +0x88");
static_assert(offsetof(native::BgfxFrameBuilder, field0x90) == 0x90, "c25f680: field0x90 at +0x90");

namespace native {

// BgfxFrameBuilder::endFrame (0xc25f680, size 0x77, 1.26.62.01).
//
// Reversed source (complete). Every instruction of [0xc25f680, 0xc25f6f7) is
// covered by the citation next to the statement that implements it. Both
// indirect calls are quoted verbatim in the #if 0 block at the end of this
// file and cited next to the call statements that implement them.
//
// The function takes a strong reference on self->field0x90 ([rcx+0x90]),
// computes a flag from self->field0x88 ([rcx+0x88]), then releases the strong
// reference and, when it reached zero, destroys the object through vtable[0]
// and releases the weak reference and, when it reached zero, deallocates
// through vtable[8]. Both virtual calls go through loader-resolved data slot
// 0xF99FFA0 (sub_eea6040, a `jmp rax` forwarder, docs/data/native_boundary.tsv
// class vendor row 0xeea6040); the lifted code reads the vtable entry itself
// and calls it with RCX = object, which is the net effect of each
// `call qword ptr [0xF99FFA0]`. Returns the flag (bool): true when
// field0x88 is null, or when the int32 at *field0x88 equals 2; false otherwise.
bool sub_c25f680(BgfxFrameBuilder* self) {
    // 0xc25f680..0xc25f69d: push rsi; push rbx; sub rsp,0x28;
    //   mov rax,[rcx+0x90] ; test rax,rax ; je short 0xC25F69F
    //   lock inc dword ptr [rax+8] ; mov rsi,[rcx+0x90] ; jmp short 0xC25F6A1
    RefCountBase* obj = self->field0x90;   // 0xc25f686 mov rax,[rcx+0x90]    ; R self+0x90
    RefCountBase* rsi = nullptr;
    if (obj != nullptr) {                  // 0xc25f68d test rax,rax ; 0xc25f690 je short 0xC25F69F
        // 0xc25f692  lock inc dword ptr [rax+8]   ; W obj+0x08 (strong refcount++)
        _InterlockedIncrement(reinterpret_cast<volatile LONG*>(&obj->strong));  // 0xc25f692 lock inc dword ptr [rax+8] ; W obj+0x08
        // 0xc25f696  mov rsi,[rcx+0x90]  ; R self+0x90 again
        rsi = self->field0x90;             // 0xc25f696 mov rsi,[rcx+0x90]    ; R self+0x90
    }                                        // 0xc25f69d jmp short 0xC25F6A1
    else {                                   // 0xc25f69f  xor esi,esi          ; rsi = 0
        ;                                    // 0xc25f69f (rsi stays nullptr)
    }

    // 0xc25f6a1..0xc25f6ba: mov rax,[rcx+0x88] ; test rax,rax ; je short 0xC25F6BC
    //   mov eax,[rax] ; cmp eax,2 ; sete bl ; test rsi,rsi ; jne short 0xC25F6C3
    //   jmp short 0xC25F6EE
    std::int32_t* flagPtr = self->field0x88;  // 0xc25f6a1 mov rax,[rcx+0x88]   ; R self+0x88
    bool flag;
    if (flagPtr != nullptr) {               // 0xc25f6a8 test rax,rax ; 0xc25f6ab je short 0xC25F6BC
        // 0xc25f6ad  mov eax,[rax]       ; R flagPtr+0x00
        // 0xc25f6af  cmp eax,2
        // 0xc25f6b2  sete bl              ; BL = (*flagPtr == 2)
        flag = (*flagPtr == 2);            // 0xc25f6ad..0xc25f6b2             ; R flagPtr+0x00
    } else {                                // 0xc25f6bc  mov bl,1
        flag = true;                       // 0xc25f6bc  mov bl,1
    }                                        // 0xc25f6be test rsi,rsi ; 0xc25f6c1 je short 0xC25F6EE

    // 0xc25f6c3..0xc25f6d2: lock dec dword ptr [rsi+8] ; jne short 0xC25F6EE
    //   mov rax,[rsi] ; mov rax,[rax] ; mov rcx,rsi ; call qword ptr [0xF99FFA0]
    if (rsi != nullptr) {                   // release path exactly when rsi != 0
        // 0xc25f6c3  lock dec dword ptr [rsi+8]  ; RW rsi+0x08 (strong--)
        // 0xc25f6c7  jne short 0xC25F6EE
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rsi->strong)) == 0) {  // 0xc25f6c3..0xc25f6c7
            // 0xc25f6c9  mov rax,[rsi]      ; R rsi+0x00 (vtable pointer)
            // 0xc25f6cc  mov rax,[rax]      ; R vtable+0x00 (destructor)
            void** vtable = reinterpret_cast<void**>(rsi);          // 0xc25f6c9 mov rax,[rsi]      ; R rsi+0x00
            using DestroyFn = void (*)(void*);
            DestroyFn destroy = reinterpret_cast<DestroyFn>(vtable[0]);  // 0xc25f6cc mov rax,[rax]  ; R vtable+0x00
            // 0xc25f6cf  mov rcx,rsi        ; RCX = rsi (destroy argument)
            // 0xc25f6d2  call qword ptr [0xF99FFA0]  ; sub_eea6040 -> jmp rax = vtable[0]
            destroy(rsi);                  // 0xc25f6cf mov rcx,rsi ; 0xc25f6d2  call qword ptr [0xF99FFA0]

            // 0xc25f6d8..0xc25f6e8: lock dec dword ptr [rsi+0xC] ; jne short 0xC25F6EE
            //   mov rax,[rsi] ; mov rax,[rax+8] ; mov rcx,rsi ; call qword ptr [0xF99FFA0]
            // 0xc25f6d8  lock dec dword ptr [rsi+0xC]  ; RW rsi+0x0C (weak--)
            // 0xc25f6dc  jne short 0xC25F6EE
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rsi->weak)) == 0) {  // 0xc25f6d8..0xc25f6dc
                // 0xc25f6de  mov rax,[rsi]      ; R rsi+0x00 (vtable pointer)
                // 0xc25f6e1  mov rax,[rax+8]    ; R vtable+0x08 (deallocator)
                vtable = reinterpret_cast<void**>(rsi);            // 0xc25f6de mov rax,[rsi]      ; R rsi+0x00
                using DeallocFn = void (*)(void*);
                DeallocFn dealloc = reinterpret_cast<DeallocFn>(vtable[1]);  // 0xc25f6e1 mov rax,[rax+8] ; R vtable+0x08
                // 0xc25f6e5  mov rcx,rsi        ; RCX = rsi (dealloc argument)
                // 0xc25f6e8  call qword ptr [0xF99FFA0]  ; sub_eea6040 -> jmp rax = vtable[8]
                dealloc(rsi);            // 0xc25f6e5 mov rcx,rsi ; 0xc25f6e8  call qword ptr [0xF99FFA0]
            }
        }
    }                                        // 0xc25f6ee  mov eax,ebx        ; return flag

    // 0xc25f6ee..0xc25f6f6: mov eax,ebx ; add rsp,0x28 ; pop rbx ; pop rsi ; ret
    return flag;                             // 0xc25f6ee..0xc25f6f6 ; return flag (AL = 0/1)
}

LIFT_FN(c25f680, "BgfxFrameBuilder::endFrame", 0xC25F680, sub_c25f680, nullptr);

} // namespace native

// Verbatim instructions of the function (rdis dis 0xc25f680 0x77), for
// liftcheck/verify_oc. Every line matches rdis output for its address.
#if 0
0xC25F680  push rsi
0xC25F681  push rbx
0xC25F682  sub rsp,0x28
0xC25F686  mov rax,[rcx+0x90]
0xC25F68D  test rax,rax
0xC25F690  je short 0xC25F69F
0xC25F692  lock inc dword ptr [rax+8]
0xC25F696  mov rsi,[rcx+0x90]
0xC25F69D  jmp short 0xC25F6A1
0xC25F69F  xor esi,esi
0xC25F6A1  mov rax,[rcx+0x88]
0xC25F6A8  test rax,rax
0xC25F6AB  je short 0xC25F6BC
0xC25F6AD  mov eax,[rax]
0xC25F6AF  cmp eax,2
0xC25F6B2  sete bl
0xC25F6B5  test rsi,rsi
0xC25F6B8  jne short 0xC25F6C3
0xC25F6BA  jmp short 0xC25F6EE
0xC25F6BC  mov bl,1
0xC25F6BE  test rsi,rsi
0xC25F6C1  je short 0xC25F6EE
0xC25F6C3  lock dec dword ptr [rsi+8]
0xC25F6C7  jne short 0xC25F6EE
0xC25F6C9  mov rax,[rsi]
0xC25F6CC  mov rax,[rax]
0xC25F6CF  mov rcx,rsi
0xC25F6D2  call qword ptr [0xF99FFA0]
0xC25F6D8  lock dec dword ptr [rsi+0xC]
0xC25F6DC  jne short 0xC25F6EE
0xC25F6DE  mov rax,[rsi]
0xC25F6E1  mov rax,[rax+8]
0xC25F6E5  mov rcx,rsi
0xC25F6E8  call qword ptr [0xF99FFA0]
0xC25F6EE  mov eax,ebx
0xC25F6F0  add rsp,0x28
0xC25F6F4  pop rbx
0xC25F6F5  pop rsi
0xC25F6F6  ret
#endif
