// LIFT 0x6639930 size 0x72 1.26.62.01 BgfxFrameBuilder slot 90
#include "sub_6639930.h"

#include <cstdint>

static_assert(sizeof(void*) == 8, "sub_6639930: x64 ABI, pointer-sized address space");

namespace native {

// Reversed source (complete). Every instruction of [0x6639930, 0x66399a2) is covered by
// the citation next to the statement that implements it; both calls are quoted verbatim
// in the #if 0 block at the end of this file. The prologue/epilogue (push rsi, sub
// rsp,0x20 / add rsp,0x20, pop rsi, ret) implement themselves and are cited with the
// return statement.
int32_t sub_6639930(BgfxFrameBuilder* self) {
    // 0x6639930  push rsi                                   ; prologue (callee-saved)
    // 0x6639931  sub rsp,0x20                               ; stack frame
    // 0x6639935  mov rsi,rcx                                ; RSI = self for the whole function
    // 0x6639938  mov rax,[rcx]                              ; R self+0x0 (vtable pointer) -- before call #1
    const std::uintptr_t vtable = *reinterpret_cast<const std::uintptr_t*>(self);  // 0x6639938 mov rax,[rcx]        ; R self+0x0 (vtable pointer)
    // 0x663993b  mov rax,[rax+0x230]                        ; R vtable+0x230 (slot 70 fn ptr) -> RAX
    using TrampolineTarget = int32_t (*)(BgfxFrameBuilder* self);
    const TrampolineTarget slot0x230 = reinterpret_cast<TrampolineTarget>(         // 0x663993b mov rax,[rax+0x230] ; R vtable+0x230 -> RAX
        *reinterpret_cast<const std::uintptr_t*>(
            reinterpret_cast<const std::uint8_t*>(vtable) + kVtableSlotByteOffset0x230));
    // 0x6639942  call qword ptr [0xF99FFA0]                 ; call #1 -> sub_eea6040 [V boundary: vendor,
    //     0xEEA6040  jmp rax                   ; thunk via data slot 0xF99FFA0]; tail-call to RAX =
    //     slot0x230 target with RCX = self
    const int32_t call1 = slot0x230(self);                                           // 0x6639942 call qword ptr [0xF99FFA0] ; EAX = call #1 result
    // 0x6639948  test al,al                                 ; call #1 result low byte == 0?
    // 0x663994a  je short 0x663995C                         ; if zero: fall through to call #2
    if ((call1 & 0xFF) != 0) {                                                       // 0x6639948..0x663994a ; jz not taken
        // 0x663994c  mov rax,[rsi+0x358]                   ; R self+0x358 (state pointer)
        // 0x6639953  movzx eax,byte ptr [rax+0x7E5]        ; R state+0x7E5 -> AL, zero-extended
        // 0x663995a  jmp short 0x663999C                   ; return AL
        return static_cast<int32_t>(                                                 // 0x663994c..0x663995a ; return AL (zero-extended byte)
            reinterpret_cast<const BuilderState*>(self->state0x358)->byte0x7E5);
    }
    // 0x663995c  mov rax,[rsi]                              ; R self+0x0 (vtable pointer, reloaded) -- before call #2
    const std::uintptr_t vtable2 = *reinterpret_cast<const std::uintptr_t*>(self);   // 0x663995c mov rax,[rsi]        ; R self+0x0 (vtable pointer)
    // 0x663995f  mov rax,[rax+0x228]                        ; R vtable+0x228 (slot 69 fn ptr) -> RAX
    const TrampolineTarget slot0x228 = reinterpret_cast<TrampolineTarget>(           // 0x663995f mov rax,[rax+0x228] ; R vtable+0x228 -> RAX
        *reinterpret_cast<const std::uintptr_t*>(
            reinterpret_cast<const std::uint8_t*>(vtable2) + kVtableSlotByteOffset0x228));
    // 0x6639966  mov rcx,rsi                                ; RCX = self (call #2 argument)
    // 0x6639969  call qword ptr [0xF99FFA0]                 ; call #2 -> sub_eea6040 [V boundary: vendor];
    //     0xEEA6040  jmp rax                                ; tail-call to RAX = slot0x228 target, RCX = self
    const int32_t call2 = slot0x228(self);                                           // 0x6639966..0x6639969 ; EAX = call #2 result
    // 0x663996f  mov ecx,eax                                ; ECX = call #2 result (full 32 bits)
    const int32_t ecx = call2;                                                       // 0x663996f mov ecx,eax
    // 0x6639971  mov al,3                                   ; default return; EAX upper bits preserved
    int32_t eax = (call2 & 0xFFFFFF00) | 3;                                          // 0x6639971 mov al,3
    // 0x6639973  test cl,cl                                 ; call #2 result low byte == 0?
    // 0x6639975  je short 0x663999C                         ; if zero: return EAX
    if ((ecx & 0xFF) == 0) {                                                         // 0x6639973..0x6639975
        return eax;                                                                  // 0x6639975..0x663999c ; return EAX = (call2 & ~0xFF) | 3
    }
    // 0x6639977  mov rcx,[rsi+0x278]                        ; R self+0x278 (pointer)
    // 0x663997e  test rcx,rcx
    // 0x6639981  je short 0x663999C                         ; if null: return EAX
    const void* p = self->field0x278;                                                // 0x6639977 mov rcx,[rsi+0x278] ; R self+0x278
    if (p == nullptr) {                                                              // 0x663997e..0x6639981
        return eax;                                                                  // 0x6639981..0x663999c ; return EAX
    }
    // 0x6639983  mov ecx,[rcx+0x180]                        ; R pointee+0x180 (int32_t)
    const std::int32_t v = reinterpret_cast<const Field0x278Pointee*>(p)->value0x180; // 0x6639983 mov ecx,[rcx+0x180]
    // 0x6639989  xor eax,eax                                ; EAX = 0
    // 0x663998b  cmp ecx,2
    // 0x663998e  sete al                                    ; AL = (v == 2)
    // 0x6639991  lea eax,[rax+rax*2]                        ; EAX = AL*3
    // 0x6639994  add eax,3                                  ; EAX = AL*3+3 (v==2 -> 6, else 3)
    // 0x6639997  test ecx,ecx
    // 0x6639999  cmove eax,ecx                              ; if v == 0: EAX = ECX = 0
    eax = 0;                                                                         // 0x6639989 xor eax,eax
    if (v == 2) eax = 1;                                                             // 0x663998b..0x663998e cmp ecx,2 / sete al
    eax = eax * 3 + 3;                                                               // 0x6639991 lea eax,[rax+rax*2] / 0x6639994 add eax,3
    if (v == 0) eax = v;                                                             // 0x6639997 test ecx,ecx / 0x6639999 cmove eax,ecx (ECX = 0)
    // 0x663999c  add rsp,0x20                               ; epilogue
    // 0x66399a0  pop rsi
    // 0x66399a1  ret                                       ; return EAX
    return eax;                                                                        // 0x663999c..0x66399a1
}

// Verbatim instructions of the function (matches rdis dis 0x6639930 0x72, copied from
// the exe listing and machine-checked with tools/sigs/verify_oc.py):
#if 0
0x6639930  push rsi
0x6639931  sub rsp,0x20
0x6639935  mov rsi,rcx
0x6639938  mov rax,[rcx]
0x663993b  mov rax,[rax+0x230]
0x6639942  call qword ptr [0xF99FFA0]
0x6639948  test al,al
0x663994a  je short 0x663995C
0x663994c  mov rax,[rsi+0x358]
0x6639953  movzx eax,byte ptr [rax+0x7E5]
0x663995a  jmp short 0x663999C
0x663995c  mov rax,[rsi]
0x663995f  mov rax,[rax+0x228]
0x6639966  mov rcx,rsi
0x6639969  call qword ptr [0xF99FFA0]
0x663996f  mov ecx,eax
0x6639971  mov al,3
0x6639973  test cl,cl
0x6639975  je short 0x663999C
0x6639977  mov rcx,[rsi+0x278]
0x663997e  test rcx,rcx
0x6639981  je short 0x663999C
0x6639983  mov ecx,[rcx+0x180]
0x6639989  xor eax,eax
0x663998b  cmp ecx,2
0x663998e  sete al
0x6639991  lea eax,[rax+rax*2]
0x6639994  add eax,3
0x6639997  test ecx,ecx
0x6639999  cmove eax,ecx
0x663999c  add rsp,0x20
0x66399a0  pop rsi
0x66399a1  ret
#endif

} // namespace native

LIFT_FN(sub_6639930, "sub_6639930", 0x6639930, sub_6639930, nullptr);
