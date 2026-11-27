// LIFT 0x66399f0 size 0x64 1.26.62.01 BgfxFrameBuilder slot 92
#include "sub_66399f0.h"

#include <cstdint>

static_assert(sizeof(void*) == 8, "sub_66399f0: x64 ABI, pointer-sized address space");

namespace native {

// sub_66399f0 (0x66399f0, size 0x64, 1.26.62.01, "BgfxFrameBuilder slot 92").
//
// Reversed source (complete). Every instruction of [0x66399f0, 0x6639a54) is covered by
// the citation next to the statement that implements it (the whole-function range covers
// the prologue/epilogue); both calls are quoted verbatim in the #if 0 block at the end.
//
//   0x66399f0  push rsi                                   ; prologue (callee-saved)
//   0x66399f1  sub rsp,0x20                               ; stack frame
//   0x66399f5  mov rsi,rcx                                ; self -> RSI
//   0x66399f8  mov rax,[rcx]                              ; R self+0x0 (vtable pointer)
//   0x66399fb  mov rax,[rax+0x230]                        ; R vtable+0x230 -> RAX
//   0x6639a02  call qword ptr [0xF99FFA0]                 ; -> sub_eea6040 [V boundary:
//       vendor; data slot 0xF99FFA0; tails to RAX = vtable+0x230 target with RCX=self]
//   0x6639a08  test al,al                                 ; first call result == 0?
//   0x6639a0a  je short 0x6639A1C                         ; if zero, second call path
//   0x6639a0c  mov rax,[rsi+0x358]                        ; R self+0x358 (state pointer)
//   0x6639a13  movzx eax,byte ptr [rax+0x7E4]             ; R state+0x7E4 -> AL
//   0x6639a1a  jmp short 0x6639A4E                        ; return AL
//   0x6639a1c  mov rax,[rsi]                              ; R self+0x0 (vtable pointer)
//   0x6639a1f  mov rax,[rax+0x228]                        ; R vtable+0x228 -> RAX
//   0x6639a26  mov rcx,rsi                                ; RCX = self
//   0x6639a29  call qword ptr [0xF99FFA0]                 ; -> sub_eea6040 (see above)
//   0x6639a2f  mov ecx,eax                                ; second call result -> ECX
//   0x6639a31  mov al,1                                   ; default return 1
//   0x6639a33  test cl,cl                                 ; second call result == 0?
//   0x6639a35  je short 0x6639A4E                         ; if zero, return 1
//   0x6639a37  mov rcx,[rsi+0x278]                        ; R self+0x278 (pointer)
//   0x6639a3e  test rcx,rcx                               ; pointer == 0?
//   0x6639a41  je short 0x6639A4E                         ; if null, return 1
//   0x6639a43  cmp dword ptr [rcx+0x184],1                ; R *(rcx+0x184) vs 1
//   0x6639a4a  mov al,2                                   ; default 2
//   0x6639a4c  sbb al,0                                   ; AL = 2 - CF; CF=1 iff dword == 0
//   0x6639a4e  add rsp,0x20                               ; epilogue
//   0x6639a52  pop rsi
//   0x6639a53  ret                                       ; return AL
//
// 0x66399f0..0x6639a54
uint8_t sub_66399f0(BgfxFrameBuilder* self) {
    // 0x66399f0..0x6639a54
    const std::uintptr_t vtable = *reinterpret_cast<const std::uintptr_t*>(self);  // 0x66399f8 mov rax,[rcx]      ; R self+0x0 (vtable pointer)
    using Trampoline = uint8_t (*)(BgfxFrameBuilder* self);
    const Trampoline trampoline0x230 = reinterpret_cast<Trampoline>(               // 0x66399fb mov rax,[rax+0x230] ; R vtable+0x230 -> RAX
        *reinterpret_cast<const std::uintptr_t*>(
            reinterpret_cast<const std::uint8_t*>(vtable) + kVtableSlotByteOffset0x230));
    // 0x6639a02  call qword ptr [0xF99FFA0]  ; -> sub_eea6040 [V boundary: vendor]
    const uint8_t firstResult = trampoline0x230(self);                            // 0x6639a02 ; result in AL
    // 0x6639a08  test al,al
    // 0x6639a0a  je short 0x6639A1C   ; if zero, perform the second trampoline call
    if (firstResult != 0) {                                                       // 0x6639a08..0x6639a0a
        // 0x6639a0c  mov rax,[rsi+0x358]     ; R self+0x358 (state pointer)
        // 0x6639a13  movzx eax,byte ptr [rax+0x7E4]  ; R state+0x7E4 -> AL
        // 0x6639a1a  jmp short 0x6639A4E   ; return AL
        return reinterpret_cast<const BuilderState*>(self->state0x358)->byte0x7E4;  // 0x6639a0c..0x6639a1a
    }
    // 0x6639a1c  mov rax,[rsi]                              ; R self+0x0 (vtable pointer)
    const Trampoline trampoline0x228 = reinterpret_cast<Trampoline>(              // 0x6639a1f mov rax,[rax+0x228] ; R vtable+0x228 -> RAX
        *reinterpret_cast<const std::uintptr_t*>(
            reinterpret_cast<const std::uint8_t*>(vtable) + kVtableSlotByteOffset0x228));
    // 0x6639a26  mov rcx,rsi                                ; RCX = self
    // 0x6639a29  call qword ptr [0xF99FFA0]                 ; -> sub_eea6040 (see above)
    const uint8_t secondResult = trampoline0x228(self);                           // 0x6639a29 ; result in AL/EAX
    // 0x6639a2f  mov ecx,eax
    // 0x6639a31  mov al,1                                   ; default return 1
    // 0x6639a33  test cl,cl
    // 0x6639a35  je short 0x6639A4E   ; if zero, return 1
    uint8_t result = 1;                                                           // 0x6639a31 mov al,1 (default)
    if (secondResult != 0) {                                                      // 0x6639a33..0x6639a35
        // 0x6639a37  mov rcx,[rsi+0x278]     ; R self+0x278 (pointer)
        // 0x6639a3e  test rcx,rcx
        // 0x6639a41  je short 0x6639A4E    ; if null, return 1
        if (self->field0x278 != nullptr) {                                        // 0x6639a37..0x6639a41
            // 0x6639a43  cmp dword ptr [rcx+0x184],1   ; R *(rcx+0x184) vs 1
            // 0x6639a4a  mov al,2
            // 0x6639a4c  sbb al,0                      ; AL = 2 - (dword == 0 ? 1 : 0)
            const std::uint32_t dword =
                reinterpret_cast<const Field0x278Object*>(self->field0x278)->dword0x184;  // 0x6639a43
            result = static_cast<uint8_t>(2u - (dword == 0u ? 1u : 0u));          // 0x6639a4a..0x6639a4c
        }
    }
    // 0x6639a4e  add rsp,0x20; 0x6639a52  pop rsi; 0x6639a53 ret  ; return AL
    return result;                                                                // 0x6639a4e..0x6639a53
}

// Verbatim instructions of the function (matches rdis dis 0x66399f0 0x64, copied from
// the exe listing and machine-checked with tools/sigs/verify_oc.py):
#if 0
0x66399f0  push rsi
0x66399f1  sub rsp,0x20
0x66399f5  mov rsi,rcx
0x66399f8  mov rax,[rcx]
0x66399fb  mov rax,[rax+0x230]
0x6639a02  call qword ptr [0xF99FFA0]
0x6639a08  test al,al
0x6639a0a  je short 0x6639A1C
0x6639a0c  mov rax,[rsi+0x358]
0x6639a13  movzx eax,byte ptr [rax+0x7E4]
0x6639a1a  jmp short 0x6639A4E
0x6639a1c  mov rax,[rsi]
0x6639a1f  mov rax,[rax+0x228]
0x6639a26  mov rcx,rsi
0x6639a29  call qword ptr [0xF99FFA0]
0x6639a2f  mov ecx,eax
0x6639a31  mov al,1
0x6639a33  test cl,cl
0x6639a35  je short 0x6639A4E
0x6639a37  mov rcx,[rsi+0x278]
0x6639a3e  test rcx,rcx
0x6639a41  je short 0x6639A4E
0x6639a43  cmp dword ptr [rcx+0x184],1
0x6639a4a  mov al,2
0x6639a4c  sbb al,0
0x6639a4e  add rsp,0x20
0x6639a52  pop rsi
0x6639a53  ret
#endif

} // namespace native

LIFT_FN(sub_66399f0, "sub_66399f0", 0x66399f0, sub_66399f0, nullptr);
