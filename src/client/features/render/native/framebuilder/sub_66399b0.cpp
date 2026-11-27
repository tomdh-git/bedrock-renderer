// LIFT 0x66399b0 size 0x34 1.26.62.01 BgfxFrameBuilder slot 91
#include "sub_66399b0.h"

#include <cstdint>

static_assert(sizeof(void*) == 8, "sub_66399b0: x64 ABI, pointer-sized address space");

namespace native {

// sub_66399b0 (0x66399b0, size 0x34, 1.26.62.01, "BgfxFrameBuilder slot 91").
//
// Reversed source (complete). The whole function is one straight-line phase with one
// conditional; every instruction of [0x66399b0, 0x66399e4) is covered by the citation
// next to the statement that implements it. The single call is quoted verbatim in the
// #if 0 block at the end of this file.
//
//   0x66399b0  push rsi                                   ; prologue (callee-saved)
//   0x66399b1  sub rsp,0x20                               ; stack frame
//   0x66399b5  mov rsi,rcx                                ; self -> RSI
//   0x66399b8  mov rax,[rcx]                              ; R self+0x0 (vtable pointer)
//   0x66399bb  mov rax,[rax+0x230]                        ; R vtable+0x230 -> RAX
//   0x66399c2  call qword ptr [0xF99FFA0]                 ; -> sub_eea6040 [V boundary: vendor,
//       native_boundary.tsv: thunk via data slot 0xF99FFA0]; sub_eea6040 = `jmp rax` tails
//       to RAX = vtable+0x230 with RCX = self
//   0x66399c8  mov ecx,eax                                ; call result -> ECX
//   0x66399ca  mov al,2                                   ; default return
//   0x66399cc  test cl,cl                                 ; result == 0?
//   0x66399ce  je short 0x66399DE                         ; if zero, return 2
//   0x66399d0  mov rax,[rsi+0x358]                        ; R self+0x358 (state pointer)
//   0x66399d7  movzx eax,byte ptr [rax+0x7E6]             ; R state+0x7E6 -> AL
//   0x66399de  add rsp,0x20                               ; epilogue
//   0x66399e2  pop rsi
//   0x66399e3  ret                                       ; return AL
//
// 0x66399b0..0x66399e4
uint8_t sub_66399b0(BgfxFrameBuilder* self) {
    // 0x66399b0..0x66399e4
    const std::uintptr_t vtable = *reinterpret_cast<const std::uintptr_t*>(self);  // 0x66399b8 mov rax,[rcx]        ; R self+0x0 (vtable pointer)
    using TrampolineTarget = uint8_t (*)(BgfxFrameBuilder* self);
    const TrampolineTarget trampolineTarget = reinterpret_cast<TrampolineTarget>(  // 0x66399bb mov rax,[rax+0x230] ; R vtable+0x230 -> RAX
        *reinterpret_cast<const std::uintptr_t*>(
            reinterpret_cast<const std::uint8_t*>(vtable) + kVtableSlotByteOffset0x230));
    // 0x66399c2  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040 [V boundary: vendor;
    //     0xEEA6040  jmp rax                   ; tail-call to RAX = trampolineTarget, RCX = self]
    const uint8_t callResult = trampolineTarget(self);  // 0x66399c2 ; call result in AL
    // 0x66399c8  mov ecx,eax
    // 0x66399ca  mov al,2
    uint8_t result = 2;                                   // 0x66399ca mov al,2 (default return)
    // 0x66399cc  test cl,cl
    // 0x66399ce  je short 0x66399DE   ; if the call result is zero, return 2
    if (callResult != 0) {                                // 0x66399cc..0x66399ce
        // 0x66399d0  mov rax,[rsi+0x358]     ; R self+0x358 (state pointer)
        // 0x66399d7  movzx eax,byte ptr [rax+0x7E6]  ; R state+0x7E6 -> AL
        result = reinterpret_cast<const BuilderState*>(self->state0x358)->byte0x7E6;  // 0x66399d0..0x66399d7
    }
    // 0x66399de  add rsp,0x20; 0x66399e2  pop rsi; 0x66399e3 ret  ; return AL
    return result;                                          // 0x66399de..0x66399e3
}

// Verbatim instructions of the function (matches rdis dis 0x66399b0 0x34, copied from
// the exe listing and machine-checked with tools/sigs/verify_oc.py):
#if 0
0x66399b0  push rsi
0x66399b1  sub rsp,0x20
0x66399b5  mov rsi,rcx
0x66399b8  mov rax,[rcx]
0x66399bb  mov rax,[rax+0x230]
0x66399c2  call qword ptr [0xF99FFA0]
0x66399c8  mov ecx,eax
0x66399ca  mov al,2
0x66399cc  test cl,cl
0x66399ce  je short 0x66399DE
0x66399d0  mov rax,[rsi+0x358]
0x66399d7  movzx eax,byte ptr [rax+0x7E6]
0x66399de  add rsp,0x20
0x66399e2  pop rsi
0x66399e3  ret
#endif

} // namespace native

LIFT_FN(sub_66399b0, "sub_66399b0", 0x66399b0, sub_66399b0, nullptr);
