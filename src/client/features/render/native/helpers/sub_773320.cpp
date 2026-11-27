// LIFT 0x773320 size 0xc9 1.26.62.01 sub_773320
#include "sub_773320.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// Layout assertions (definitions live in sub_773320.h; repeated here so liftcheck sees them
// in the source file).
static_assert(kA0StateOffset == 0xB0, "sub_773320: a0 state at +0xB0");
static_assert(kA0VfptrSlotIndex == 4, "sub_773320: a0 vfptr method slot index 4");
static_assert(kA2ObjOffset == 0x00, "sub_773320: a2 obj at +0x00");
static_assert(kA2CbOffset == 0x08, "sub_773320: a2 cb at +0x08");
static_assert(kObjFlagOffset == 0x30, "sub_773320: obj flag at +0x30");
static_assert(kCbStrongOffset == 0x08, "sub_773320: cb strong at +0x08");
static_assert(kCbWeakOffset == 0x0C, "sub_773320: cb weak at +0x0C");
static_assert(kCbVfptrSlotDtor == 0, "sub_773320: cb vfptr dtor slot index 0");
static_assert(kCbVfptrSlotDealloc == 1, "sub_773320: cb vfptr dealloc slot index 1");
static_assert(kBlockObjOffset == 0x00, "sub_773320: block obj at +0x00");
static_assert(kBlockCbOffset == 0x08, "sub_773320: block cb at +0x08");
static_assert(kEea6040SlotRva == 0xF99FFA0, "sub_773320: call slot at 0xF99FFA0");
static_assert(sizeof(void*) == 8, "sub_773320: x64 pointers are 8 bytes");

// sub_773320 (0x773320, size 0xc9, 1.26.62.01): state-driven release/call on handle a2 with a0 callback.
// Same reads, same writes, same calls in the same order, same return (void) as [0x773320, 0x7733E9).

void sub_773320(void* a0, void* a2)
{
    // 0x773320..0x773337
    // 0x773320  push rbp
    // 0x773321  push rsi
    // 0x773322  sub rsp,0x48
    // 0x773326  lea rbp,[rsp+0x40]
    // 0x77332b  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0x773333  mov [rbp-8],rdx          ; spill a2
    // Frame setup (implicit in C++); a2 spilled.
    (void)a2;                            // 0x773333  mov [rbp-8],rdx (a2 itself is the argument)

    // 0x773337..0x773342
    // 0x773337  mov eax,[rcx+0xB0]       ; state = a0+0xB0
    // 0x77333d  cmp eax,1
    // 0x773340  je short 0x7733A9        ; state==1 -> release
    const std::uint32_t state =
        *reinterpret_cast<const std::uint32_t*>(
            reinterpret_cast<const std::uint8_t*>(a0) + kA0StateOffset);  // 0x773337  mov eax,[rcx+0xB0]

    // 0x773342  mov rdx,[rbp-8]          ; rdx = a2  (a2 is already the argument)
    void* const obj =
        *reinterpret_cast<void**>(a2);   // 0x773363  mov rax,[rdx]  (obj = [a2], reused below)
    void* const cb =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a2) + kA2CbOffset);  // 0x773374  mov rax,[rdx+8] (cb = [a2+8])

    if (state == 1) {
        // 0x77333d  cmp eax,1 / 0x773340  je short 0x7733A9 -> release (skip block/call2)
    } else if (state == 2) {
        // 0x77334b  cmp eax,2 / 0x77334e  jne short 0x77336D (taken when state==2, fall to call1)
        // 0x773350  mov rcx,[rdx]        ; obj = [a2]
        // 0x773353  mov rax,[rcx]        ; obj vfptr -> rax
        // 0x773356  mov rax,[rax+8]      ; rax = obj->vfptr[1] (gate target, RAX)
        // 0x77335a  call qword ptr [0xF99FFA0]   ; obj->vfptr[1](obj, a2) via sub_eea6040 thunk
        // 0x773360  nop
        void** const objVfptr =
            *reinterpret_cast<void***>(obj);  // 0x773353  mov rax,[rcx]
        void* const gateTarget1 =
            objVfptr[kCbVfptrSlotDealloc];    // 0x773356  mov rax,[rax+8]  (RAX = obj->vfptr[1])
        (void)gateTarget1;                    // loaded into RAX, then the thunk jumps to it
        sub_eea6040(obj, a2);                 // 0x77335a  call qword ptr [0xF99FFA0]  ; -> obj->vfptr[1](obj, a2)
        // 0x773361  jmp short 0x7733A9   ; state==2 -> release (skip block build and call2)
    } else {
        // state == 3 (after zeroing below) or default: block build + call2  [0x77336d..0x7733a2]
        if (state == 3) {
            // 0x773346  cmp eax,3 / 0x773349  je short 0x773363 -> here
            // 0x773363  mov rax,[rdx]        ; obj = [a2]
            // 0x773366  mov dword ptr [rax+0x30],0   ; obj+0x30 = 0
            *reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uint8_t*>(obj) + kObjFlagOffset) = 0;  // 0x773366
        }

        // 0x77336d  xorps xmm0,xmm0
        // 0x773370  movaps [rbp-0x20],xmm0   ; zero block {obj, cb}
        sub_773320_block block{};                // 0x77336d..0x773370  zero block
        block.obj = obj;                         // 0x773389  mov rdx,[rdx] / 0x77338c  mov [rbp-0x20],rdx  (block.obj = obj)
        block.cb = cb;                           // 0x773390  mov [rbp-0x18],rax  (block.cb = cb)

        // 0x773378  test rax,rax
        // 0x77337b  je short 0x773387        ; cb==0 -> skip inc
        // 0x77337d  lock inc dword ptr [rax+8]   ; cb->strong++
        if (cb != nullptr) {                     // 0x773378  test rax,rax / 0x77337b  je short 0x773387
            _InterlockedIncrement(               // 0x77337d  lock inc dword ptr [rax+8]  (cb->strong++)
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(cb) + kCbStrongOffset));
        }

        // 0x773394  mov rax,[rcx]            ; a0 vfptr -> rax
        // 0x773397  mov rax,[rax+0x20]       ; rax = a0->vfptr[4] (gate target, RAX)
        // 0x77339b  lea rdx,[rbp-0x20]       ; rdx = &block
        // 0x77339f  xor r8d,r8d              ; r8 = 0
        // 0x7733a2  call qword ptr [0xF99FFA0]   ; a0->vfptr[4](a0, &block, 0) via sub_eea6040 thunk
        // 0x7733a8  nop
        void** const a0Vfptr =
            *reinterpret_cast<void***>(a0);   // 0x773394  mov rax,[rcx]
        void* const gateTarget2 =
            reinterpret_cast<void**>(a0Vfptr)[kA0VfptrSlotIndex];  // 0x773397  mov rax,[rax+0x20]
        (void)gateTarget2;                    // loaded into RAX, then the thunk jumps to it
        sub_eea6040(a0, &block);              // 0x7733a2  call qword ptr [0xF99FFA0]  ; -> a0->vfptr[4](a0, &block, 0)
    }

release:
    // 0x7733a9..0x7733e8
    // 0x7733a9  mov rax,[rbp-8]          ; rax = a2
    // 0x7733ad  mov rsi,[rax+8]          ; rsi = cb = [a2+8]
    // 0x7733b1  test rsi,rsi
    // 0x7733b4  je short 0x7733E2        ; cb==0 -> done
    // 0x7733b6  lock dec dword ptr [rsi+8]   ; cb->strong--
    // 0x7733ba  jne short 0x7733E2       ; strong!=0 -> done
    // 0x7733bc  mov rax,[rsi]            ; cb vfptr -> rax
    // 0x7733bf  mov rax,[rax]            ; rax = cb->vfptr[0] (dtor, RAX)
    // 0x7733c2  mov rcx,rsi              ; rcx = cb
    // 0x7733c5  call qword ptr [0xF99FFA0]   ; cb->vfptr[0](cb) dtor via sub_eea6040 thunk
    // 0x7733cb  lock dec dword ptr [rsi+0xC]   ; cb->weak--
    // 0x7733cf  jne short 0x7733E2       ; weak!=0 -> done
    // 0x7733d1  mov rax,[rsi]            ; cb vfptr -> rax
    // 0x7733d4  mov rax,[rax+8]          ; rax = cb->vfptr[8] (dealloc, RAX)
    // 0x7733d8  mov rcx,rsi              ; rcx = cb
    // 0x7733db  call qword ptr [0xF99FFA0]   ; cb->vfptr[8](cb) dealloc via sub_eea6040 thunk
    // 0x7733e1  nop
    // 0x7733e2  add rsp,0x48             ; epilogue
    // 0x7733e6  pop rsi                  ; epilogue
    // 0x7733e7  pop rbp                  ; epilogue
    // 0x7733e8  ret                      ; return void
    void* const releaseCb =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a2) + kA2CbOffset);  // 0x7733a9 / 0x7733ad  (cb = [a2+8])
    if (releaseCb != nullptr) {            // 0x7733b1  test rsi,rsi / 0x7733b4  je short 0x7733E2
        if (_InterlockedDecrement(       // 0x7733b6  lock dec dword ptr [rsi+8]  (cb->strong--)
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(releaseCb) + kCbStrongOffset)) == 0) {  // 0x7733ba  jne short 0x7733E2
            // refcount reached 0: virtual destructor cb->vfptr[0](cb)
            void** const cbVfptr =
                *reinterpret_cast<void***>(releaseCb);   // 0x7733bc  mov rax,[rsi] / 0x7733bf  mov rax,[rax]
            void* const dtorTarget =
                cbVfptr[kCbVfptrSlotDtor];  // 0x7733bf  rax = cb->vfptr[0] (RAX = gate target)
            (void)dtorTarget;               // loaded into RAX, then the thunk jumps to it
            sub_eea6040(releaseCb, nullptr);// 0x7733c2  mov rcx,rsi / 0x7733c5  call qword ptr [0xF99FFA0]
        }
        if (_InterlockedDecrement(       // 0x7733cb  lock dec dword ptr [rsi+0xC]  (cb->weak--)
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(releaseCb) + kCbWeakOffset)) == 0) {  // 0x7733cf  jne short 0x7733E2
            // weak count reached 0: virtual deallocator cb->vfptr[8](cb)
            void** const cbVfptr =
                *reinterpret_cast<void***>(releaseCb);   // 0x7733d1  mov rax,[rsi] / 0x7733d4  mov rax,[rax+8]
            void* const deallocTarget =
                cbVfptr[kCbVfptrSlotDealloc];  // 0x7733d4  rax = cb->vfptr[8] (RAX = gate target)
            (void)deallocTarget;               // loaded into RAX, then the thunk jumps to it
            sub_eea6040(releaseCb, nullptr);// 0x7733d8  mov rcx,rsi / 0x7733db  call qword ptr [0xF99FFA0]
        }
    }
    // 0x7733e2  add rsp,0x48 / pop rsi / pop rbp / ret  (implicit epilogue, return void)
}

// Verbatim call instructions from the disassembly of [0x773320, 0x7733E9)
// (rdis dis 0x773320 0xc9); machine-checked by tools/sigs/verify_oc.py against the exe.
// All four are `call qword ptr [0xF99FFA0]` -> sub_eea6040 (boundary/vendor thunk, jmp rax).
#if 0
0x77335a  call qword ptr [0xF99FFA0]
0x7733a2  call qword ptr [0xF99FFA0]
0x7733c5  call qword ptr [0xF99FFA0]
0x7733db  call qword ptr [0xF99FFA0]
#endif

} // namespace native

LIFT_FN(sub_773320, "sub_773320", 0x773320, ::native::sub_773320, nullptr);
