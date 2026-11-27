// LIFT 0x5699be0 size 0x95 1.26.62.01 sub_5699be0
#include "sub_5699be0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_5699be0 (0x5699be0, size 0x95, 1.26.62.01, "pass encode B").
//
// Full instruction-by-instruction reversal:
//   0x5699be0..0x5699be6  push rsi; push rdi; sub rsp,0x28        (prologue, callee-saved registers)
//   0x5699be6             mov rsi,rcx                              ; rsi = pass object (a0)
//   0x5699be9             mov rax,[rdx]                            ; rax = *item (+0x0)
//   0x5699bec             mov [rcx+0xA8],rax                       ; pass+0xA8 = *item
//   0x5699bf3             mov rax,[rdx+0x10]                       ; rax = item+0x10 (refcounted object ptr)
//   0x5699bf7             test rax,rax
//   0x5699bfa             je short 0x5699C06                       ; if null, skip addref
//   0x5699bfc             lock inc dword ptr [rax+8]               ; *(item+0x10)+0x8 refcount +1
//   0x5699c00             mov rax,[rdx+0x10]                       ; rax = item+0x10 again (same value)
//   0x5699c04             jmp short 0x5699C08
//   0x5699c06             xor eax,eax                              ; rax = 0
//   0x5699c08             mov rcx,[rdx+8]                          ; rcx = item+0x8 (obj8 pointer)
//   0x5699c0c             mov [rsi+0xB0],rcx                       ; pass+0xB0 = obj8
//   0x5699c13             mov rdi,[rsi+0xB8]                       ; rdi = pass+0xB8 (old obj)
//   0x5699c1a             mov [rsi+0xB8],rax                       ; pass+0xB8 = rax (new obj)
//   0x5699c21             test rdi,rdi                             ; old obj != null?
//   0x5699c24             je short 0x5699C51                       ; if null, skip release
//   0x5699c26             lock dec dword ptr [rdi+8]               ; *(oldObj)+0x8 refcount -1
//   0x5699c2a             jne short 0x5699C51                      ; if not zero, skip delete
//   0x5699c2c             mov rax,[rdi]                            ; rax = *oldObj (vfptr)
//   0x5699c2f             mov rax,[rax]                            ; rax = vfptr[0] (destructor)
//   0x5699c32             mov rcx,rdi                              ; RCX = oldObj
//   0x5699c35             call qword ptr [0xF99FFA0]               ; -> sub_eea6040 (boundary/vendor thunk: jmp rax) -> vfptr[0](oldObj)
//   0x5699c3b             lock dec dword ptr [rdi+0xC]             ; *(oldObj)+0xC count0xC -1
//   0x5699c3f             jne short 0x5699C51                      ; if not zero, skip delete
//   0x5699c41             mov rax,[rdi]                            ; rax = *oldObj (vfptr)
//   0x5699c44             mov rax,[rax+8]                          ; rax = vfptr[1] (operator delete)
//   0x5699c48             mov rcx,rdi                              ; RCX = oldObj
//   0x5699c4b             call qword ptr [0xF99FFA0]               ; -> sub_eea6040 (boundary/vendor thunk: jmp rax) -> vfptr[1](oldObj)
//   0x5699c51             mov rax,[rsi+0xB0]                       ; rax = pass+0xB0 = obj8
//   0x5699c58             mov rcx,[rax+0x10]                       ; rcx = obj8+0x10 (pointer)
//   0x5699c5c             movzx edx,word ptr [rax+8]               ; edx = obj8+8 as u16
//   0x5699c60             lea r8,[0x5699E30]                       ; r8 = &sub_5699e30 (pass body B, NOT called here)
//   0x5699c67             mov r9,rsi                               ; r9 = passObj
//   0x5699c6a             add rsp,0x28                             ; epilogue
//   0x5699c6e             pop rdi                                  ; epilogue
//   0x5699c6f             pop rsi                                  ; epilogue
//   0x5699c70             jmp 0xBC61560                            ; tail call to sub_bc61560
//
// Reads: pass+0xA8, pass+0xB0, pass+0xB8; item+0x0, item+0x8, item+0x10;
//   *(item+0x10)+0x8 (refcount read-modify-write); obj8+0x8 (u16), obj8+0x10 (ptr);
//   oldObj+0x0 (vfptr), vfptr+0x0 (destructor), vfptr+0x8 (delete), oldObj+0x8 (refcount),
//   oldObj+0xC (count0xC).
// Writes: pass+0xA8, pass+0xB0, pass+0xB8; *(item+0x10)+0x8 (lock inc);
//   *(oldObj)+0x8 (lock dec), *(oldObj)+0xC (lock dec).
// Calls: 2x sub_eea6040 via data slot 0xF99FFA0 (boundary/vendor); tail call to
//   sub_bc61560 (lift set). sub_5699e30 address is taken (not called).
// Return: void (tail call to sub_bc61560 passes through).
// Same reads, same writes, same calls in the same order, same return. Nothing else
// happens in [0x5699be0, 0x5699c75).

// Boundary callee: sub_eea6040, vendor class, reached through data slot 0xF99FFA0
// (docs/data/native_boundary.tsv: "0xeea6040 vendor thunk via data slot 0xF99FFA0 (loader-resolved)").
// The thunk at 0xeea6040 is a single `jmp rax`: the caller must have loaded RAX with the
// target function pointer (vfptr[0] or vfptr[1]) just before the call; RCX = object and
// RDX = item object are forwarded by the `jmp rax` tail jump. Return value ignored.
native::Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// 0x5699be0..0x5699c75
void sub_5699be0(void* passObj, void* item)
{
    static_assert(sizeof(void*) == 8, "sub_5699be0: x64 pointers and arguments are 8 bytes");

    void* const a0 = passObj;       // RCX = pass object
    void* const a1 = item;          // RDX = item object

    // 0x5699be9  mov rax,[rdx]           ; rax = *item (+0x0)
    // 0x5699bec  mov [rcx+0xA8],rax      ; pass+0xA8 = *item
    *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0xA8) =
        *reinterpret_cast<void**>(a1);     // 0x5699be9  mov rax,[rdx]
                                           // 0x5699bec  mov [rcx+0xA8],rax

    // 0x5699bf3  mov rax,[rdx+0x10]      ; rax = item+0x10 (refcounted object ptr)
    // 0x5699bf7  test rax,rax
    // 0x5699bfa  je short 0x5699C06      ; if null, skip addref
    void* const newObj =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a1) + kItemOffset0x10);   // 0x5699bf3  mov rax,[rdx+0x10]
    if (newObj != nullptr) {                                          // 0x5699bf7  test rax,rax
                                                                          // 0x5699bfa  je short 0x5699C06
        // 0x5699bfc  lock inc dword ptr [rax+8]   ; *(newObj+0x8) refcount +1
        _InterlockedIncrement(
            reinterpret_cast<volatile long*>(
                reinterpret_cast<std::uint8_t*>(newObj) +
                kRefcountedOffsetRefcount));  // 0x5699bfc  lock inc dword ptr [rax+8]
    }
    // 0x5699c00  mov rax,[rdx+0x10]      ; rax = item+0x10 again (same value as newObj)
    // 0x5699c04  jmp short 0x5699C08
    // 0x5699c06  xor eax,eax             ; not taken when newObj != null
    // loc_5699c08: rax = newObj (or 0 if null)

    // 0x5699c08  mov rcx,[rdx+8]         ; rcx = item+0x8 (obj8 pointer)
    // 0x5699c0c  mov [rsi+0xB0],rcx      ; pass+0xB0 = obj8
    void* const obj8 =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a1) + kItemOffset0x08);  // 0x5699c08  mov rcx,[rdx+8]
    *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0xB0) = obj8;  // 0x5699c0c  mov [rsi+0xB0],rcx

    // 0x5699c13  mov rdi,[rsi+0xB8]      ; rdi = pass+0xB8 (old obj)
    // 0x5699c1a  mov [rsi+0xB8],rax      ; pass+0xB8 = rax (new obj)
    void* const oldObj =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0xB8);  // 0x5699c13  mov rdi,[rsi+0xB8]
    *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0xB8) = newObj;  // 0x5699c1a  mov [rsi+0xB8],rax

    // 0x5699c21  test rdi,rdi            ; old obj != null?
    // 0x5699c24  je short 0x5699C51      ; if null, skip release
    if (oldObj != nullptr) {                                          // 0x5699c21  test rdi,rdi
                                                                          // 0x5699c24  je short 0x5699C51
        // 0x5699c26  lock dec dword ptr [rdi+8]   ; *(oldObj+0x8) refcount -1
        // 0x5699c2a  jne short 0x5699C51           ; if not zero, skip delete
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(oldObj) +
                    kRefcountedOffsetRefcount)) == 0) {  // 0x5699c26  lock dec dword ptr [rdi+8]
                                                          // 0x5699c2a  jne short 0x5699C51

            // refcount reached 0: virtual destructor vfptr[0](oldObj)
            // via sub_eea6040 thunk:
            //   0x5699c2c  mov rax,[rdi]            ; rax = *oldObj (vfptr)
            //   0x5699c2f  mov rax,[rax]            ; rax = vfptr[0] (destructor) -> RAX
            //   0x5699c32  mov rcx,rdi              ; RCX = oldObj
            //   0x5699c35  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (boundary/vendor thunk: jmp rax) -> vfptr[0](oldObj)
            void** const vfptr = *reinterpret_cast<void***>(oldObj);  // 0x5699c2c  mov rax,[rdi]
                                                                        // 0x5699c2f  mov rax,[rax]
            void* const dtorEntry = vfptr[0];                         // 0x5699c2f  mov rax,[rax]  (RAX = gate target)
            sub_eea6040(oldObj, item);   // 0x5699c32  mov rcx,rdi
                                         // 0x5699c35  call qword ptr [0xF99FFA0]   ; gate: jmp rax -> vfptr[0](oldObj)
            (void)dtorEntry;

            // 0x5699c3b  lock dec dword ptr [rdi+0xC]   ; *(oldObj+0xC) count0xC -1
            // 0x5699c3f  jne short 0x5699C51           ; if not zero, skip delete
            if (_InterlockedDecrement(
                    reinterpret_cast<volatile long*>(
                        reinterpret_cast<std::uint8_t*>(oldObj) +
                        kRefcountedOffsetCount0xC)) == 0) {  // 0x5699c3b  lock dec dword ptr [rdi+0xC]
                                                              // 0x5699c3f  jne short 0x5699C51

                // count0xC reached 0: virtual delete vfptr[1](oldObj)
                // via sub_eea6040 thunk:
                //   0x5699c41  mov rax,[rdi]            ; rax = *oldObj (vfptr)
                //   0x5699c44  mov rax,[rax+8]          ; rax = vfptr[1] (operator delete) -> RAX
                //   0x5699c48  mov rcx,rdi              ; RCX = oldObj
                //   0x5699c4b  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (boundary/vendor thunk: jmp rax) -> vfptr[1](oldObj)
                sub_eea6040(oldObj, item);   // 0x5699c48  mov rcx,rdi
                                             // 0x5699c4b  call qword ptr [0xF99FFA0]
            }
        }
    }

    // loc_5699c51:
    // 0x5699c51  mov rax,[rsi+0xB0]     ; rax = pass+0xB0 = obj8
    // 0x5699c58  mov rcx,[rax+0x10]     ; rcx = obj8+0x10 (pointer)
    // 0x5699c5c  movzx edx,word ptr [rax+8]   ; edx = u16 obj8+8
    // 0x5699c60  lea r8,[0x5699E30]     ; r8 = &sub_5699e30 (function pointer, not called here)
    // 0x5699c67  mov r9,rsi             ; r9 = pass object
    // 0x5699c70  jmp 0xBC61560          ; tail call to sub_bc61560(rcxArg, rdxArg, &sub_5699e30, passObj)
    void* const obj8b =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0xB0);   // 0x5699c51  mov rax,[rsi+0xB0]
    void* const rcxArg =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(obj8b) + kObj8Offset0x10);   // 0x5699c58  mov rcx,[rax+0x10]
    std::uint16_t const rdxArg =
        *reinterpret_cast<std::uint16_t*>(
            reinterpret_cast<std::uint8_t*>(obj8b) + kObj8Offset0x08);  // 0x5699c5c  movzx edx,word ptr [rax+8]

    // 0x5699c60  lea r8,[0x5699E30]      ; r8 = &sub_5699e30 (pass body B, not called here)
    // 0x5699c67  mov r9,rsi              ; r9 = passObj
    // 0x5699c70  jmp 0xBC61560           ; tail call to sub_bc61560
    bgfx::sub_bc61560(rcxArg, rdxArg,
                      reinterpret_cast<void*>(sub_5699e30), a0);  // 0x5699c60  lea r8,[0x5699E30]
                                                                         // 0x5699c67  mov r9,rsi
                                                                         // 0x5699c70  jmp 0xBC61560
}

} // namespace native

LIFT_FN(sub_5699be0, "sub_5699be0", 0x5699BE0, ::native::sub_5699be0, nullptr);

// Verbatim instructions of [0x5699be0, 0x5699c75) (rdis dis 0x5699be0 0x95);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x5699be0  push rsi
0x5699be1  push rdi
0x5699be2  sub rsp,0x28
0x5699be6  mov rsi,rcx
0x5699be9  mov rax,[rdx]
0x5699bec  mov [rcx+0xA8],rax
0x5699bf3  mov rax,[rdx+0x10]
0x5699bf7  test rax,rax
0x5699bfa  je short 0x5699C06
0x5699bfc  lock inc dword ptr [rax+8]
0x5699c00  mov rax,[rdx+0x10]
0x5699c04  jmp short 0x5699C08
0x5699c06  xor eax,eax
0x5699c08  mov rcx,[rdx+8]
0x5699c0c  mov [rsi+0xB0],rcx
0x5699c13  mov rdi,[rsi+0xB8]
0x5699c1a  mov [rsi+0xB8],rax
0x5699c21  test rdi,rdi
0x5699c24  je short 0x5699C51
0x5699c26  lock dec dword ptr [rdi+8]
0x5699c2a  jne short 0x5699C51
0x5699c2c  mov rax,[rdi]
0x5699c2f  mov rax,[rax]
0x5699c32  mov rcx,rdi
0x5699c35  call qword ptr [0xF99FFA0]
0x5699c3b  lock dec dword ptr [rdi+0xC]
0x5699c3f  jne short 0x5699C51
0x5699c41  mov rax,[rdi]
0x5699c44  mov rax,[rax+8]
0x5699c48  mov rcx,rdi
0x5699c4b  call qword ptr [0xF99FFA0]
0x5699c51  mov rax,[rsi+0xB0]
0x5699c58  mov rcx,[rax+0x10]
0x5699c5c  movzx edx,word ptr [rax+8]
0x5699c60  lea r8,[0x5699E30]
0x5699c67  mov r9,rsi
0x5699c6a  add rsp,0x28
0x5699c6e  pop rdi
0x5699c6f  pop rsi
0x5699c70  jmp 0xBC61560
#endif
