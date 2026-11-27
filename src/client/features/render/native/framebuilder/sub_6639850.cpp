// LIFT 0x6639850 size 0x6d 1.26.62.01 BgfxFrameBuilder slot 76
#include "sub_6639850.h"

#include <cstdint>
#include <cstring>

static_assert(sizeof(void*) == 8, "sub_6639850: x64 ABI, pointer-sized address space");

namespace native {

// sub_6639850 (0x6639850, size 0x6d, 1.26.62.01, "BgfxFrameBuilder slot 76").
//
// Reversed source (complete). Every instruction of [0x6639850, 0x66398bd) is covered by
// the citation next to the statement that implements it (the whole-function range covers
// prologue/epilogue); the single call is quoted verbatim in the #if 0 block at the end.
//
//   0x6639850  push rsi                                   ; prologue (callee-saved)
//   0x6639851  push rdi
//   0x6639852  sub rsp,0x28                               ; stack frame
//   0x6639856  mov rsi,rdx                                ; out -> RSI
//   0x6639859  mov rdi,rcx                                ; self -> RDI
//   0x663985c  mov rax,[rcx]                              ; R self+0x0 (vtable pointer)
//   0x663985f  mov rax,[rax+0x228]                        ; R vtable+0x228 -> RAX
//   0x6639866  call qword ptr [0xF99FFA0]                 ; -> sub_eea6040 [V boundary: vendor;
//       docs/data/native_boundary.tsv: thunk via data slot 0xF99FFA0]; sub_eea6040 = `jmp rax`
//       tails to RAX = vtable+0x228 target with RCX = self, result AL
//   0x663986c  test al,al                                 ; call result == 0?
//   0x663986e  je short 0x66398a2                         ; if zero, zero path
//   0x6639870  mov rax,[rdi+0x278]                        ; R self+0x278 (attachment pointer) -> RAX
//   0x6639877  test rax,rax                               ; attachment == 0?
//   0x663987a  je short 0x66398a2                         ; if null, zero path
//   0x663987c  xorps xmm0,xmm0
//   0x663987f  movups [rsi],xmm0                          ; W out 16B zero (tentative, before refObject)
//   0x6639882  mov rcx,[rdi+0x280]                        ; R self+0x280 (refObject pointer) -> RCX
//   0x6639889  test rcx,rcx                               ; refObject == 0?
//   0x663988c  je short 0x66398aa                         ; if null, store with rcx = 0
//   0x663988e  lock inc dword ptr [rcx+8]                 ; R/W atomic refcount += 1 at refObject+8
//   0x6639892  mov rax,[rdi+0x278]                        ; reload attachment
//   0x6639899  mov rcx,[rdi+0x280]                        ; reload refObject
//   0x66398a0  jmp short 0x66398ac
//   0x66398a2  xorps xmm0,xmm0                            ; zero path
//   0x66398a5  movups [rsi],xmm0                          ; W out 16B zero
//   0x66398a8  jmp short 0x66398b3
//   0x66398aa  xor ecx,ecx                                ; rcx = 0
//   0x66398ac  mov [rsi],rax                              ; W out+0 = attachment
//   0x66398af  mov [rsi+8],rcx                            ; W out+8 = refObject or 0
//   0x66398b3  mov rax,rsi                                ; return out pointer
//   0x66398b6  add rsp,0x28                               ; epilogue
//   0x66398ba  pop rdi
//   0x66398bb  pop rsi
//   0x66398bc  ret                                       ; return RAX = out
//
// 0x6639850..0x66398bd
OutPair* sub_6639850(BgfxFrameBuilder* self, OutPair* out) {
    // 0x6639850..0x66398bd
    const std::uintptr_t vtable = *reinterpret_cast<const std::uintptr_t*>(self);  // 0x663985c mov rax,[rcx]        ; R self+0x0 (vtable pointer)
    using Slot228Target = uint8_t (*)(BgfxFrameBuilder* self);
    const Slot228Target slot228Target = reinterpret_cast<Slot228Target>(            // 0x663985f mov rax,[rax+0x228] ; R vtable+0x228 -> RAX
        *reinterpret_cast<const std::uintptr_t*>(
            reinterpret_cast<const std::uint8_t*>(vtable) + kVtableSlotByteOffset0x228));
    // 0x6639866  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040 [V boundary: vendor;
    //     0xEEA6040  jmp rax                   ; tail-call to RAX = slot228Target, RCX = self]
    const uint8_t callResult = slot228Target(self);                                  // 0x6639866 ; result in AL
    // 0x663986c  test al,al
    // 0x663986e  je short 0x66398a2   ; if zero, zero path -> return out
    if (callResult == 0) {                                                           // 0x663986c..0x663986e
        // 0x66398a2  xorps xmm0,xmm0
        // 0x66398a5  movups [rsi],xmm0     ; W out 16B zero
        // 0x66398a8  jmp short 0x66398b3
        // 0x66398b3  mov rax,rsi           ; return out pointer
        std::memset(out, 0, kOutPairSize);                                           // 0x66398a2..0x66398a5
        return out;                                                                  // 0x66398b3 mov rax,rsi
    }
    // 0x6639870  mov rax,[rdi+0x278]     ; R self+0x278 (attachment pointer) -> RAX
    void* attachment = self->attachment0x278;                                        // 0x6639870
    // 0x6639877  test rax,rax
    // 0x663987a  je short 0x66398a2      ; if null, zero path -> return out
    if (attachment == nullptr) {                                                     // 0x6639877..0x663987a
        // 0x66398a2  xorps xmm0,xmm0
        // 0x66398a5  movups [rsi],xmm0     ; W out 16B zero
        // 0x66398a8  jmp short 0x66398b3
        std::memset(out, 0, kOutPairSize);                                           // 0x66398a2..0x66398a5
        return out;                                                                  // 0x66398b3 mov rax,rsi
    }
    // 0x663987c  xorps xmm0,xmm0
    // 0x663987f  movups [rsi],xmm0       ; W out 16B zero (tentative, before refObject inc)
    std::memset(out, 0, kOutPairSize);                                               // 0x663987c..0x663987f
    // 0x6639882  mov rcx,[rdi+0x280]     ; R self+0x280 (refObject pointer) -> RCX
    RefCountedObject* refObject = reinterpret_cast<RefCountedObject*>(               // 0x6639882
        self->refObject0x280);
    // 0x6639889  test rcx,rcx
    // 0x663988c  je short 0x66398aa      ; if null, store out+8 = 0
    if (refObject != nullptr) {                                                      // 0x6639889..0x663988c
        // 0x663988e  lock inc dword ptr [rcx+8]   ; R/W atomic refcount += 1
        ++(*reinterpret_cast<std::uint32_t*>(                                        // 0x663988e
            reinterpret_cast<std::uint8_t*>(refObject) + kRefCountOffset0x8));
    }
    // 0x6639892  mov rax,[rdi+0x278]     ; reload attachment
    // 0x6639899  mov rcx,[rdi+0x280]     ; reload refObject
    // 0x66398a0  jmp short 0x66398ac
    // 0x66398aa  xor ecx,ecx             ; rcx = 0 (refObject null path)
    // 0x66398ac  mov [rsi],rax           ; W out+0 = attachment
    // 0x66398af  mov [rsi+8],rcx         ; W out+8 = refObject or 0
    out->attachment0x0 = attachment;                                                 // 0x6639892..0x66398ac
    out->refObject0x8 = refObject;                                                   // 0x6639899..0x66398af
    // 0x66398b3  mov rax,rsi             ; return out pointer
    // 0x66398b6  add rsp,0x28
    // 0x66398ba  pop rdi
    // 0x66398bb  pop rsi
    // 0x66398bc  ret
    return out;                                                                      // 0x66398b3..0x66398bc
}

// Verbatim instructions of the function (matches rdis dis 0x6639850 0x6d, copied from
// the exe listing and machine-checked with tools/sigs/verify_oc.py):
#if 0
0x6639850  push rsi
0x6639851  push rdi
0x6639852  sub rsp,0x28
0x6639856  mov rsi,rdx
0x6639859  mov rdi,rcx
0x663985c  mov rax,[rcx]
0x663985f  mov rax,[rax+0x228]
0x6639866  call qword ptr [0xF99FFA0]
0x663986c  test al,al
0x663986e  je short 0x66398a2
0x6639870  mov rax,[rdi+0x278]
0x6639877  test rax,rax
0x663987a  je short 0x66398a2
0x663987c  xorps xmm0,xmm0
0x663987f  movups [rsi],xmm0
0x6639882  mov rcx,[rdi+0x280]
0x6639889  test rcx,rcx
0x663988c  je short 0x66398aa
0x663988e  lock inc dword ptr [rcx+8]
0x6639892  mov rax,[rdi+0x278]
0x6639899  mov rcx,[rdi+0x280]
0x66398a0  jmp short 0x66398ac
0x66398a2  xorps xmm0,xmm0
0x66398a5  movups [rsi],xmm0
0x66398a8  jmp short 0x66398b3
0x66398aa  xor ecx,ecx
0x66398ac  mov [rsi],rax
0x66398af  mov [rsi+8],rcx
0x66398b3  mov rax,rsi
0x66398b6  add rsp,0x28
0x66398ba  pop rdi
0x66398bb  pop rsi
0x66398bc  ret
#endif

} // namespace native

LIFT_FN(sub_6639850, "sub_6639850", 0x6639850, sub_6639850, nullptr);
