// LIFT 0x568b9e0 size 0x95 1.26.62.01 sub_568b9e0
#include "sub_568b9e0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_568b9e0 (0x568b9e0, size 0x95, 1.26.62.01, "common pass task encode (queues the custom item)").
//
// Full instruction-by-instruction reversal:
//   0x568b9e0..0x568b9e6  push rsi; push rdi; sub rsp,0x28        (prologue, callee-saved registers)
//   0x568b9e6             mov rsi,rcx                              ; rsi = pass object (a0)
//   0x568b9e9             mov rax,[rdx]                            ; rax = *item (+0x0)
//   0x568b9ec             mov [rcx+0x2E0],rax                      ; pass+0x2E0 = *item
//   0x568b9f3             mov rax,[rdx+0x10]                       ; rax = item+0x10 (refcounted obj ptr)
//   0x568b9f7             test rax,rax
//   0x568b9fa             je short 0x568BA06                       ; if null, skip addref
//   0x568b9fc             lock inc dword ptr [rax+8]               ; *(item+0x10)+0x8 refcount +1
//   0x568ba00             mov rax,[rdx+0x10]                       ; rax = item+0x10 again (same value)
//   0x568ba04             jmp short 0x568BA08
//   0x568ba06             xor eax,eax                              ; rax = 0
//   0x568ba08             mov rcx,[rdx+8]                          ; rcx = item+0x8 (obj8 ptr)
//   0x568ba0c             mov [rsi+0x2E8],rcx                      ; pass+0x2E8 = obj8
//   0x568ba13             mov rdi,[rsi+0x2F0]                      ; rdi = pass+0x2F0 (old obj)
//   0x568ba1a             mov [rsi+0x2F0],rax                      ; pass+0x2F0 = rax (new obj)
//   0x568ba21             test rdi,rdi                             ; old obj != null?
//   0x568ba24             je short 0x568BA51                       ; if null, skip release
//   0x568ba26             lock dec dword ptr [rdi+8]               ; *(oldObj)+0x8 refcount -1
//   0x568ba2a             jne short 0x568BA51                      ; if not zero, skip delete
//   0x568ba2c             mov rax,[rdi]                            ; rax = *oldObj (vfptr)
//   0x568ba2f             mov rax,[rax]                            ; rax = vfptr[0] (destructor)
//   0x568ba32             mov rcx,rdi                              ; RCX = oldObj
//   0x568ba35             call qword ptr [0xF99FFA0]               ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
//   0x568ba3b             lock dec dword ptr [rdi+0xC]             ; *(oldObj)+0xC count0xC -1
//   0x568ba3f             jne short 0x568BA51                      ; if not zero, skip delete
//   0x568ba41             mov rax,[rdi]                            ; rax = *oldObj (vfptr)
//   0x568ba44             mov rax,[rax+8]                          ; rax = vfptr[1] (operator delete)
//   0x568ba48             mov rcx,rdi                              ; RCX = oldObj
//   0x568ba4b             call qword ptr [0xF99FFA0]               ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
//   0x568ba51             mov rax,[rsi+0x2E8]                      ; rax = pass+0x2E8 = obj8
//   0x568ba58             mov rcx,[rax+0x10]                       ; rcx = obj8+0x10 (pointer)
//   0x568ba5c             movzx edx,word ptr [rax+8]               ; edx = obj8+8 as u16
//   0x568ba60             lea r8,[0x568BCD0]                       ; r8 = &sub_568bcd0
//   0x568ba67             mov r9,rsi                               ; r9 = passObj
//   0x568ba6a             add rsp,0x28                             ; epilogue
//   0x568ba6e             pop rdi                                  ; epilogue
//   0x568ba6f             pop rsi                                  ; epilogue
//   0x568ba70             jmp 0xBC61560                            ; tail call to sub_bc61560
//
// Reads: pass+0x2E0, pass+0x2E8, pass+0x2F0; item+0x0, item+0x8, item+0x10;
//   *(item+0x10)+0x8 (refcount read-modify-write); obj8+0x8 (u16), obj8+0x10 (ptr);
//   oldObj+0x0 (vfptr), vfptr+0x0 (destructor), vfptr+0x8 (delete), oldObj+0x8 (refcount),
//   oldObj+0xC (count0xC).
// Writes: pass+0x2E0, pass+0x2E8, pass+0x2F0; *(item+0x10)+0x8 (lock inc);
//   *(oldObj)+0x8 (lock dec), *(oldObj)+0xC (lock dec).
// Calls: 2x sub_eea6040 via data slot 0xF99FFA0 (boundary/vendor); tail call to
//   sub_bc61560 (lift set). sub_568bcd0 address is taken (not called).
// Return: void (tail call to sub_bc61560 passes through).
// Same reads, same writes, same calls in the same order, same return. Nothing else
// happens in [0x568b9e0, 0x568ba75).

// Boundary callee: sub_eea6040, vendor class, reached through data slot 0xF99FFA0
// (docs/data/native_boundary.tsv: "0xeea6040 vendor thunk via data slot 0xF99FFA0 (loader-resolved)").
// The thunk is `jmp rax`; RAX must hold the target function pointer on entry.
// Called with (rcx = object, rdx = vfptr entry); return value ignored.
native::Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// 0x568b9e0..0x568ba75
void sub_568b9e0(void* passObj, void* item)
{
    static_assert(sizeof(void*) == 8, "sub_568b9e0: x64 pointers and arguments are 8 bytes");
    // 0x568b9e0..0x568b9e6  prologue: push rsi; push rdi; sub rsp,0x28
    void* const a0 = passObj;       // RCX = pass object
    void* const a1 = item;          // RDX = item object

    // 0x568b9e9  mov rax,[rdx]           ; rax = *item (+0x0)
    // 0x568b9ec  mov [rcx+0x2E0],rax     ; pass+0x2E0 = *item
    *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0x2E0) =
        *reinterpret_cast<void**>(a1);     // 0x568b9e9  mov rax,[rdx]
                                           // 0x568b9ec  mov [rcx+0x2E0],rax

    // 0x568b9f3  mov rax,[rdx+0x10]      ; rax = item+0x10 (refcounted object ptr)
    // 0x568b9f7  test rax,rax
    // 0x568b9fa  je short 0x568BA06      ; if null, skip addref
    void* const newObj =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a1) + kItemOffset0x10);   // 0x568b9f3  mov rax,[rdx+0x10]
    if (newObj != nullptr) {                                          // 0x568b9f7  test rax,rax
                                                                        // 0x568b9fa  je short 0x568BA06
        // 0x568b9fc  lock inc dword ptr [rax+8]   ; *(newObj+0x8) refcount +1
        _InterlockedIncrement(
            reinterpret_cast<volatile long*>(
                reinterpret_cast<std::uint8_t*>(newObj) +
                kRefcountedOffsetRefcount));  // 0x568b9fc  lock inc dword ptr [rax+8]
    }
    // 0x568ba00  mov rax,[rdx+0x10]      ; rax = item+0x10 again (same value as newObj)
    // 0x568ba04  jmp short 0x568BA08
    // 0x568ba06  xor eax,eax             ; not taken when newObj != null
    // loc_568ba08: rax = newObj (or 0 if null)

    // 0x568ba08  mov rcx,[rdx+8]         ; rcx = item+0x8 (obj8 pointer)
    // 0x568ba0c  mov [rsi+0x2E8],rcx     ; pass+0x2E8 = obj8
    void* const obj8 =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a1) + kItemOffset0x08);  // 0x568ba08  mov rcx,[rdx+8]
    *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0x2E8) = obj8;  // 0x568ba0c  mov [rsi+0x2E8],rcx

    // 0x568ba13  mov rdi,[rsi+0x2F0]     ; rdi = pass+0x2F0 (old obj)
    // 0x568ba1a  mov [rsi+0x2F0],rax     ; pass+0x2F0 = rax (new obj)
    void* const oldObj =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0x2F0);  // 0x568ba13  mov rdi,[rsi+0x2F0]
    *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0x2F0) = newObj;  // 0x568ba1a  mov [rsi+0x2F0],rax

    // 0x568ba21  test rdi,rdi            ; old obj != null?
    // 0x568ba24  je short 0x568BA51      ; if null, skip release
    if (oldObj != nullptr) {                                          // 0x568ba21  test rdi,rdi
                                                                        // 0x568ba24  je short 0x568BA51
        // 0x568ba26  lock dec dword ptr [rdi+8]   ; *(oldObj+0x8) refcount -1
        // 0x568ba2a  jne short 0x568BA51           ; if not zero, skip delete
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(oldObj) +
                    kRefcountedOffsetRefcount)) == 0) {  // 0x568ba26  lock dec dword ptr [rdi+8]
                                                          // 0x568ba2a  jne short 0x568BA51

            // refcount reached 0: virtual destructor vfptr[0](oldObj)
            // via sub_eea6040 thunk:
            //   0x568ba2c  mov rax,[rdi]            ; rax = *oldObj (vfptr)
            //   0x568ba2f  mov rax,[rax]            ; rax = vfptr[0] (destructor) -> RAX
            //   0x568ba32  mov rcx,rdi              ; RCX = oldObj
            //   0x568ba35  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
            void** const vfptr = *reinterpret_cast<void***>(oldObj);  // 0x568ba2c  mov rax,[rdi]
                                                                        // 0x568ba2f  mov rax,[rax]
            sub_eea6040(oldObj, vfptr[0]);   // 0x568ba32  mov rcx,rdi
                                             // 0x568ba35  call qword ptr [0xF99FFA0]

            // 0x568ba3b  lock dec dword ptr [rdi+0xC]   ; *(oldObj+0xC) count0xC -1
            // 0x568ba3f  jne short 0x568BA51           ; if not zero, skip delete
            if (_InterlockedDecrement(
                    reinterpret_cast<volatile long*>(
                        reinterpret_cast<std::uint8_t*>(oldObj) +
                        kRefcountedOffsetCount0xC)) == 0) {  // 0x568ba3b  lock dec dword ptr [rdi+0xC]
                                                              // 0x568ba3f  jne short 0x568BA51

                // count0xC reached 0: virtual delete vfptr[1](oldObj)
                // via sub_eea6040 thunk:
                //   0x568ba41  mov rax,[rdi]            ; rax = *oldObj (vfptr)
                //   0x568ba44  mov rax,[rax+8]          ; rax = vfptr[1] (operator delete) -> RAX
                //   0x568ba48  mov rcx,rdi              ; RCX = oldObj
                //   0x568ba4b  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
                sub_eea6040(oldObj, vfptr[1]);   // 0x568ba41  mov rax,[rdi]
                                                  // 0x568ba44  mov rax,[rax+8]
                                                  // 0x568ba48  mov rcx,rdi
                                                  // 0x568ba4b  call qword ptr [0xF99FFA0]
            }
        }
    }

    // loc_568ba51:
    // 0x568ba51  mov rax,[rsi+0x2E8]     ; rax = pass+0x2E8 = obj8
    // 0x568ba58  mov rcx,[rax+0x10]      ; rcx = obj8+0x10 (pointer)
    // 0x568ba5c  movzx edx,word ptr [rax+8]   ; edx = obj8+8 as u16
    // 0x568ba60  lea r8,[0x568BCD0]      ; r8 = &sub_568bcd0
    // 0x568ba67  mov r9,rsi              ; r9 = passObj
    // 0x568ba70  jmp 0xBC61560           ; tail call to sub_bc61560
    void* const rcxArg =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(obj8) + kObj8Offset0x10);   // 0x568ba51  mov rax,[rsi+0x2E8]
                                                                         // 0x568ba58  mov rcx,[rax+0x10]
    std::uint16_t const rdxArg =
        *reinterpret_cast<std::uint16_t*>(
            reinterpret_cast<std::uint8_t*>(obj8) + kObj8Offset0x08);  // 0x568ba5c  movzx edx,word ptr [rax+8]

    // 0x568ba60  lea r8,[0x568BCD0]      ; r8 = &sub_568bcd0 (function pointer, not called here)
    // 0x568ba67  mov r9,rsi              ; r9 = passObj
    // 0x568ba70  jmp 0xBC61560           ; tail call to sub_bc61560(rcxArg, rdxArg, &sub_568bcd0, passObj)
    bgfx::sub_bc61560(rcxArg, rdxArg,
                      reinterpret_cast<void*>(sub_568bcd0), passObj);  // 0x568ba60  lea r8,[0x568BCD0]
                                                                         // 0x568ba67  mov r9,rsi
                                                                         // 0x568ba70  jmp 0xBC61560
}

} // namespace native

LIFT_FN(sub_568b9e0, "sub_568b9e0", 0x568B9E0, ::native::sub_568b9e0, nullptr);

// Verbatim instructions of [0x568b9e0, 0x568ba75) (rdis dis 0x568b9e0 0x95);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x568b9e0  push rsi
0x568b9e1  push rdi
0x568b9e2  sub rsp,0x28
0x568b9e6  mov rsi,rcx
0x568b9e9  mov rax,[rdx]
0x568b9ec  mov [rcx+0x2E0],rax
0x568b9f3  mov rax,[rdx+0x10]
0x568b9f7  test rax,rax
0x568b9fa  je short 0x568BA06
0x568b9fc  lock inc dword ptr [rax+8]
0x568ba00  mov rax,[rdx+0x10]
0x568ba04  jmp short 0x568BA08
0x568ba06  xor eax,eax
0x568ba08  mov rcx,[rdx+8]
0x568ba0c  mov [rsi+0x2E8],rcx
0x568ba13  mov rdi,[rsi+0x2F0]
0x568ba1a  mov [rsi+0x2F0],rax
0x568ba21  test rdi,rdi
0x568ba24  je short 0x568BA51
0x568ba26  lock dec dword ptr [rdi+8]
0x568ba2a  jne short 0x568BA51
0x568ba2c  mov rax,[rdi]
0x568ba2f  mov rax,[rax]
0x568ba32  mov rcx,rdi
0x568ba35  call qword ptr [0xF99FFA0]
0x568ba3b  lock dec dword ptr [rdi+0xC]
0x568ba3f  jne short 0x568BA51
0x568ba41  mov rax,[rdi]
0x568ba44  mov rax,[rax+8]
0x568ba48  mov rcx,rdi
0x568ba4b  call qword ptr [0xF99FFA0]
0x568ba51  mov rax,[rsi+0x2E8]
0x568ba58  mov rcx,[rax+0x10]
0x568ba5c  movzx edx,word ptr [rax+8]
0x568ba60  lea r8,[0x568BCD0]
0x568ba67  mov r9,rsi
0x568ba6a  add rsp,0x28
0x568ba6e  pop rdi
0x568ba6f  pop rsi
0x568ba70  jmp 0xBC61560
#endif
