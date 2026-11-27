// LIFT 0x66ad730 size 0xe8 1.26.62.01 sub_66ad730
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_66ad730.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

LIFT_FN(sub_66ad730, "sub_66ad730", 0x66ad730, sub_66ad730, nullptr);

// sub_66ad730 (0x66ad730, size 0xe8, 1.26.62.01). Root: BgfxFrameBuilder::endFrame.
//
// Releases the resources owned by the frame-builder state object:
//
//   * self+0x28 (buffer) / self+0x38 (bufferEnd): when buffer != 0, validates the heap
//     block (*(buffer-8) is the size) and, when valid, notifies the global object via
//     sub_e935700 (a tail jump to sub_392960, which calls globalObject.vfptr[2] with the
//     size). The buffer and bufferEnd fields are then cleared. An invalid block calls
//     _invoke_watson via data slot 0xF9A8C78 and then int3 (fatal).
//   * self+0x18 (resourceObject): intrusive strong-refcount release; when it reaches 0,
//     vfptr[0] (destroyer) is invoked through sub_eea6040, then the weak refcount at +0xC
//     is released; when it reaches 0, vfptr[1] (deallocator) is invoked through sub_eea6040.
//   * self+0x08 (refObject): same strong/weak release sequence as resourceObject.
//
// Verbatim calls from the disassembly of [0x66ad730, 0x66ad818):
//   0x66ad772  call 0xE935700                -> sub_e935700 (lift set, native symbol)
//   0x66ad79d  call qword ptr [0xF99FFA0]    -> sub_eea6040 (vendor boundary thunk, jmp rax)
//   0x66ad7b3  call qword ptr [0xF99FFA0]    -> sub_eea6040 (vendor boundary thunk, jmp rax)
//   0x66ad7d1  call qword ptr [0xF99FFA0]    -> sub_eea6040 (vendor boundary thunk, jmp rax)
//   0x66ad811  call qword ptr [0xF9A8C78]    -> _invoke_watson (data slot; fatal path, then int3)
//
// sub_eea6040 is a "jmp rax" thunk: the caller pre-loads RAX with the target vtable
// function address, then calls/jumps the thunk, which tails to RAX. In lifted C++ we call
// the vtable function directly (RCX = this), which is behaviorally identical.

namespace native {
void* sub_e935700(void* a0);
}

// vfptr[0] (destroyer) and vfptr[1] (deallocator): called as f(this), return in RAX.
using DestroyFn = uintptr_t(*)(void* self);   // vfptr[0]
using DeallocFn = uintptr_t(*)(void* self);   // vfptr[1]

static inline DestroyFn vfptrDestroy(void* obj) {
    void** vfptr = *reinterpret_cast<void***>(obj);
    return reinterpret_cast<DestroyFn>(vfptr[0]);
}
static inline DeallocFn vfptrDealloc(void* obj) {
    void** vfptr = *reinterpret_cast<void***>(obj);
    return reinterpret_cast<DeallocFn>(vfptr[1]);
}

// _invoke_watson via data slot 0xF9A8C78. Call pattern follows the existing lift
// precedent (sub_bc2bca0): read the loader-patched pointer from imageBase + slot and call.
using Watson = uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t);
static inline uintptr_t invokeWatson() {
    return reinterpret_cast<Watson>(
        *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A8C78ull)
    )(nullptr, nullptr, nullptr, 0, 0);
}

uintptr_t sub_66ad730(sub_66ad730_state* self) {
    // 0x66ad730  push rsi
    // 0x66ad731  push rdi
    // 0x66ad732  sub rsp,0x28
    // 0x66ad736  mov rsi,rcx        ; rsi = self (this)
    sub_66ad730_state* rsi = self;

    // 0x66ad736..0x66ad818: buffer handling (self+0x28 / self+0x38)
    // 0x66ad739  mov rcx,[rsi+0x28]   ; rcx = self->buffer
    void* rcx = self->buffer;
    // 0x66ad73d  test rcx,rcx
    // 0x66ad740  je short 0x66AD785   ; buffer == 0 -> skip buffer handling
    if (rcx != nullptr) {
        // 0x66ad742  mov rdx,[rsi+0x38]   ; rdx = self->bufferEnd
        // 0x66ad746  sub rdx,rcx          ; rdx = bufferEnd - buffer
        std::uintptr_t rdx = (std::uint8_t*)self->bufferEnd - (std::uint8_t*)rcx;
        // 0x66ad749  cmp rdx,0x1000
        // 0x66ad750  jb short 0x66AD76E   ; bufferEnd - buffer < 0x1000 -> skip size validation
        if (rdx >= 0x1000) {
            // 0x66ad752  mov rax,[rcx-8]      ; rax = *(buffer - 8)  (heap block size)
            std::uintptr_t rax = *reinterpret_cast<std::uintptr_t*>((std::uint8_t*)rcx - 8);
            // 0x66ad756  add rcx,0xFFFFFFFFFFFFFFF8   ; rcx = buffer - 8
            std::uint8_t* rcx2 = (std::uint8_t*)rcx - 8;
            // 0x66ad75a  sub rcx,rax         ; rcx = (buffer - 8) - size
            rcx2 -= rax;
            // 0x66ad75d  cmp rcx,0x20
            // 0x66ad761  jae 0x66AD7FE      ; (buffer-8)-size >= 0x20 -> heap corruption, fatal
            if ((std::uintptr_t)rcx2 >= 0x20) {
                // 0x66ad7fe  mov qword ptr [rsp+0x20],0
                // 0x66ad807  xor ecx,ecx
                // 0x66ad809  xor edx,edx
                // 0x66ad80b  xor r8d,r8d
                // 0x66ad80e  xor r9d,r9d
                // 0x66ad811  call qword ptr [0xF9A8C78]  ; _invoke_watson(nullptr,nullptr,nullptr,0,0)
                // 0x66ad817  int3                        ; fatal (noreturn)
                return invokeWatson();
            }
            // 0x66ad767  add rdx,0x27      ; rdx = (bufferEnd - buffer) + 0x27  (dead: unused after)
            // 0x66ad76b  mov rcx,rax      ; rcx = size
            rcx = reinterpret_cast<void*>(rax);
        }
        // 0x66ad76e  lea rdi,[rsi+0x28]   ; rdi = &self->buffer
        // 0x66ad772  call 0xE935700       ; sub_e935700(rcx)   (rcx = buffer or size)
        native::sub_e935700(rcx);
        // 0x66ad777  xorps xmm0,xmm0
        // 0x66ad77a  movups [rdi],xmm0    ; self->buffer = 0  (16-byte store)
        self->buffer = nullptr;
        // 0x66ad77d  mov qword ptr [rdi+0x10],0   ; self->bufferEnd = 0
        self->bufferEnd = nullptr;
    }

    // 0x66ad785  mov rdi,[rsi+0x18]   ; rdi = self->resourceObject
    void* rdi = self->resourceObject;
    // 0x66ad789  test rdi,rdi
    // 0x66ad78c  je short 0x66AD7B9
    if (rdi != nullptr) {
        RefCountedObject* obj = reinterpret_cast<RefCountedObject*>(rdi);
        // 0x66ad78e  lock dec dword ptr [rdi+8]
        // 0x66ad792  jne short 0x66AD7B9   ; strongRefs != 0 after dec -> skip destroy
        if (--obj->strongRefs == 0) {
            // 0x66ad794  mov rax,[rdi]      ; vfptr
            // 0x66ad797  mov rax,[rax]      ; vfptr[0] (destroyer)
            // 0x66ad79a  mov rcx,rdi
            // 0x66ad79d  call sub_eea6040   ; -> vfptr[0](rdi)
            (void)vfptrDestroy(rdi)(rdi);
            // 0x66ad7a3  lock dec dword ptr [rdi+0xC]
            // 0x66ad7a7  jne short 0x66AD7B9   ; weakRefs != 0 after dec -> skip dealloc
            if (--obj->weakRefs == 0) {
                // 0x66ad7a9  mov rax,[rdi]
                // 0x66ad7ac  mov rax,[rax+8]   ; vfptr[1] (deallocator)
                // 0x66ad7b0  mov rcx,rdi
                // 0x66ad7b3  call sub_eea6040   ; -> vfptr[1](rdi)
                (void)vfptrDealloc(rdi)(rdi);
            }
        }
    }

    // 0x66ad7b9  mov rsi,[rsi+0x8]    ; rsi = self->refObject
    void* rsi2 = self->refObject;
    // 0x66ad7bd  test rsi,rsi
    // 0x66ad7c0  je short 0x66AD7F7
    if (rsi2 != nullptr) {
        RefCountedObject* obj2 = reinterpret_cast<RefCountedObject*>(rsi2);
        // 0x66ad7c2  lock dec dword ptr [rsi+8]
        // 0x66ad7c6  jne short 0x66AD7F7   ; strongRefs != 0 after dec -> skip destroy
        if (--obj2->strongRefs == 0) {
            // 0x66ad7c8  mov rax,[rsi]
            // 0x66ad7cb  mov rax,[rax]      ; vfptr[0] (destroyer)
            // 0x66ad7ce  mov rcx,rsi
            // 0x66ad7d1  call sub_eea6040   ; -> vfptr[0](rsi)
            (void)vfptrDestroy(rsi2)(rsi2);
            // 0x66ad7d7  lock dec dword ptr [rsi+0xC]
            // 0x66ad7db  jne short 0x66AD7F7   ; weakRefs != 0 after dec -> skip dealloc
            if (--obj2->weakRefs == 0) {
                // 0x66ad7dd  mov rax,[rsi]
                // 0x66ad7e0  mov rax,[rax+8]   ; vfptr[1] (deallocator)
                // 0x66ad7e4  mov rdx,[0xF99FFA0]   ; sub_eea6040 pointer
                // 0x66ad7eb  mov rcx,rsi
                // 0x66ad7ee  add rsp,0x28; pop rdi; pop rsi
                // 0x66ad7f4  jmp rdx           ; tail call sub_eea6040 -> vfptr[1](rsi)
                return vfptrDealloc(rsi2)(rsi2);   // tail-call equivalent
            }
        }
    }

    // 0x66ad7f7  add rsp,0x28
    // 0x66ad7fb  pop rdi
    // 0x66ad7fc  pop rsi
    // 0x66ad7fd  ret   ; rax is not written on this path (indeterminate); modelled as 0
    return 0;
}

} // namespace native::helpers
