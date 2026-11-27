// LIFT 0x56c85c0 size 0x95 1.26.62.01 sub_56c85c0
#include "sub_56c85c0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_56c85c0 (0x56c85c0, size 0x95, 1.26.62.01, "pass encode C").
//
// Full instruction-by-instruction reversal:
//   0x56c85c0..0x56c85c6  push rsi; push rdi; sub rsp,0x28        (prologue, callee-saved registers)
//   0x56c85c6             mov rsi,rcx                              ; rsi = pass object (a0)
//   0x56c85c9             mov rax,[rdx]                            ; rax = *item (+0x0)
//   0x56c85cc             mov [rcx+0x100],rax                      ; pass+0x100 = *item
//   0x56c85d3             mov rax,[rdx+0x10]                       ; rax = item+0x10 (refcounted obj ptr)
//   0x56c85d7             test rax,rax
//   0x56c85da             je short 0x56C85E6                       ; if null, skip addref
//   0x56c85dc             lock inc dword ptr [rax+8]               ; *(item+0x10)+0x8 refcount +1
//   0x56c85e0             mov rax,[rdx+0x10]                       ; rax = item+0x10 again (same value)
//   0x56c85e4             jmp short 0x56C85E8
//   0x56c85e6             xor eax,eax                              ; rax = 0
//   0x56c85e8             mov rcx,[rdx+8]                          ; rcx = item+0x8 (obj8 ptr)
//   0x56c85ec             mov [rsi+0x108],rcx                      ; pass+0x108 = obj8
//   0x56c85f3             mov rdi,[rsi+0x110]                      ; rdi = pass+0x110 (old obj)
//   0x56c85fa             mov [rsi+0x110],rax                      ; pass+0x110 = rax (new obj)
//   0x56c8601             test rdi,rdi                             ; old obj != null?
//   0x56c8604             je short 0x56C8631                       ; if null, skip release
//   0x56c8606             lock dec dword ptr [rdi+8]               ; *(oldObj)+0x8 refcount -1
//   0x56c860a             jne short 0x56C8631                      ; if not zero, skip delete
//   0x56c860c             mov rax,[rdi]                            ; rax = *oldObj (vfptr)
//   0x56c860f             mov rax,[rax]                            ; rax = vfptr[0] (destructor)
//   0x56c8612             mov rcx,rdi                              ; RCX = oldObj
//   0x56c8615             call qword ptr [0xF99FFA0]               ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
//   0x56c861b             lock dec dword ptr [rdi+0xC]             ; *(oldObj)+0xC count0xC -1
//   0x56c861f             jne short 0x56C8631                      ; if not zero, skip delete
//   0x56c8621             mov rax,[rdi]                            ; rax = *oldObj (vfptr)
//   0x56c8624             mov rax,[rax+8]                          ; rax = vfptr[1] (operator delete)
//   0x56c8628             mov rcx,rdi                              ; RCX = oldObj
//   0x56c862b             call qword ptr [0xF99FFA0]               ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
//   0x56c8631             mov rax,[rsi+0x108]                      ; rax = pass+0x108 = obj8
//   0x56c8638             mov rcx,[rax+0x10]                       ; rcx = obj8+0x10 (pointer)
//   0x56c863c             movzx edx,word ptr [rax+8]               ; edx = obj8+8 as u16
//   0x56c8640             lea r8,[0x56C8810]                       ; r8 = &sub_56c8810
//   0x56c8647             mov r9,rsi                               ; r9 = passObj
//   0x56c864a             add rsp,0x28                             ; epilogue
//   0x56c864e             pop rdi                                  ; epilogue
//   0x56c864f             pop rsi                                  ; epilogue
//   0x56c8650             jmp 0xBC61560                            ; tail call to sub_bc61560
//
// Reads: pass+0x100, pass+0x108, pass+0x110; item+0x0, item+0x8, item+0x10;
//   *(item+0x10)+0x8 (refcount read-modify-write); obj8+0x8 (u16), obj8+0x10 (ptr);
//   oldObj+0x0 (vfptr), vfptr+0x0 (destructor), vfptr+0x8 (delete), oldObj+0x8 (refcount),
//   oldObj+0xC (count0xC).
// Writes: pass+0x100, pass+0x108, pass+0x110; *(item+0x10)+0x8 (lock inc);
//   *(oldObj)+0x8 (lock dec), *(oldObj)+0xC (lock dec).
// Calls: 2x sub_eea6040 via data slot 0xF99FFA0 (boundary/vendor); tail call to
//   sub_bc61560 (lift set). sub_56c8810 address is taken (not called).
// Return: void (tail call to sub_bc61560 passes through).
// Same reads, same writes, same calls in the same order, same return. Nothing else
// happens in [0x56c85c0, 0x56c8655).

// Boundary callee: sub_eea6040, vendor class, reached through data slot 0xF99FFA0
// (docs/data/native_boundary.tsv: "0xeea6040 vendor thunk via data slot 0xF99FFA0 (loader-resolved)").
// The thunk is `jmp rax`; RAX must hold the target function pointer on entry.
// Called with (rcx = object, rdx = vfptr entry); return value ignored.
native::Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// 0x56c85c0..0x56c8655
void sub_56c85c0(void* passObj, void* item)
{
    static_assert(sizeof(void*) == 8, "sub_56c85c0: x64 pointers and arguments are 8 bytes");
    // 0x56c85c0..0x56c85c6  prologue: push rsi; push rdi; sub rsp,0x28
    void* const a0 = passObj;       // RCX = pass object
    void* const a1 = item;          // RDX = item object

    // 0x56c85c9  mov rax,[rdx]           ; rax = *item (+0x0)
    // 0x56c85cc  mov [rcx+0x100],rax     ; pass+0x100 = *item
    *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0x100) =
        *reinterpret_cast<void**>(a1);     // 0x56c85c9  mov rax,[rdx]
                                           // 0x56c85cc  mov [rcx+0x100],rax

    // 0x56c85d3  mov rax,[rdx+0x10]      ; rax = item+0x10 (refcounted object ptr)
    // 0x56c85d7  test rax,rax
    // 0x56c85da  je short 0x56C85E6      ; if null, skip addref
    void* const newObj =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a1) + kItemOffset0x10);   // 0x56c85d3  mov rax,[rdx+0x10]
    if (newObj != nullptr) {                                          // 0x56c85d7  test rax,rax
                                                                         // 0x56c85da  je short 0x56C85E6
        // 0x56c85dc  lock inc dword ptr [rax+8]   ; *(newObj+0x8) refcount +1
        _InterlockedIncrement(
            reinterpret_cast<volatile long*>(
                reinterpret_cast<std::uint8_t*>(newObj) +
                kRefcountedOffsetRefcount));  // 0x56c85dc  lock inc dword ptr [rax+8]
    }
    // 0x56c85e0  mov rax,[rdx+0x10]      ; rax = item+0x10 again (same value as newObj)
    // 0x56c85e4  jmp short 0x56C85E8
    // 0x56c85e6  xor eax,eax             ; not taken when newObj != null
    // loc_56c85e8: rax = newObj (or 0 if null)

    // 0x56c85e8  mov rcx,[rdx+8]         ; rcx = item+0x8 (obj8 pointer)
    // 0x56c85ec  mov [rsi+0x108],rcx     ; pass+0x108 = obj8
    void* const obj8 =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a1) + kItemOffset0x08);  // 0x56c85e8  mov rcx,[rdx+8]
    *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0x108) = obj8;  // 0x56c85ec  mov [rsi+0x108],rcx

    // 0x56c85f3  mov rdi,[rsi+0x110]     ; rdi = pass+0x110 (old obj)
    // 0x56c85fa  mov [rsi+0x110],rax     ; pass+0x110 = rax (new obj)
    void* const oldObj =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0x110);  // 0x56c85f3  mov rdi,[rsi+0x110]
    *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kPassOffset0x110) = newObj;  // 0x56c85fa  mov [rsi+0x110],rax

    // 0x56c8601  test rdi,rdi            ; old obj != null?
    // 0x56c8604  je short 0x56C8631      ; if null, skip release
    if (oldObj != nullptr) {                                          // 0x56c8601  test rdi,rdi
                                                                         // 0x56c8604  je short 0x56C8631
        // 0x56c8606  lock dec dword ptr [rdi+8]   ; *(oldObj+0x8) refcount -1
        // 0x56c860a  jne short 0x56C8631           ; if not zero, skip delete
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(oldObj) +
                    kRefcountedOffsetRefcount)) == 0) {  // 0x56c8606  lock dec dword ptr [rdi+8]
                                                          // 0x56c860a  jne short 0x56C8631

            // refcount reached 0: virtual destructor vfptr[0](oldObj)
            // via sub_eea6040 thunk:
            //   0x56c860c  mov rax,[rdi]            ; rax = *oldObj (vfptr)
            //   0x56c860f  mov rax,[rax]            ; rax = vfptr[0] (destructor) -> RAX
            //   0x56c8612  mov rcx,rdi              ; RCX = oldObj
            //   0x56c8615  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
            void** const vfptr = *reinterpret_cast<void***>(oldObj);  // 0x56c860c  mov rax,[rdi]
                                                                         // 0x56c860f  mov rax,[rax]
            sub_eea6040(oldObj, vfptr[0]);   // 0x56c8612  mov rcx,rdi
                                             // 0x56c8615  call qword ptr [0xF99FFA0]

            // 0x56c861b  lock dec dword ptr [rdi+0xC]   ; *(oldObj+0xC) count0xC -1
            // 0x56c861f  jne short 0x56C8631           ; if not zero, skip delete
            if (_InterlockedDecrement(
                    reinterpret_cast<volatile long*>(
                        reinterpret_cast<std::uint8_t*>(oldObj) +
                        kRefcountedOffsetCount0xC)) == 0) {  // 0x56c861b  lock dec dword ptr [rdi+0xC]
                                                             // 0x56c861f  jne short 0x56C8631

                // count0xC reached 0: virtual delete vfptr[1](oldObj)
                // via sub_eea6040 thunk:
                //   0x56c8621  mov rax,[rdi]            ; rax = *oldObj (vfptr)
                //   0x56c8624  mov rax,[rax+8]          ; rax = vfptr[1] (operator delete) -> RAX
                //   0x56c8628  mov rcx,rdi              ; RCX = oldObj
                //   0x56c862b  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
                sub_eea6040(oldObj, vfptr[1]);   // 0x56c8621  mov rax,[rdi]
                                                  // 0x56c8624  mov rax,[rax+8]
                                                  // 0x56c8628  mov rcx,rdi
                                                  // 0x56c862b  call qword ptr [0xF99FFA0]
            }
        }
    }

    // loc_56c8631:
    // 0x56c8631  mov rax,[rsi+0x108]     ; rax = pass+0x108 = obj8
    // 0x56c8638  mov rcx,[rax+0x10]      ; rcx = obj8+0x10 (pointer)
    // 0x56c863c  movzx edx,word ptr [rax+8]   ; edx = obj8+8 as u16
    // 0x56c8640  lea r8,[0x56C8810]      ; r8 = &sub_56c8810
    // 0x56c8647  mov r9,rsi              ; r9 = passObj
    // 0x56c8650  jmp 0xBC61560           ; tail call to sub_bc61560
    void* const rcxArg =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(obj8) + kObj8Offset0x10);   // 0x56c8631  mov rax,[rsi+0x108]
                                                                         // 0x56c8638  mov rcx,[rax+0x10]
    std::uint16_t const rdxArg =
        *reinterpret_cast<std::uint16_t*>(
            reinterpret_cast<std::uint8_t*>(obj8) + kObj8Offset0x08);  // 0x56c863c  movzx edx,word ptr [rax+8]

    // 0x56c8640  lea r8,[0x56C8810]      ; r8 = &sub_56c8810 (function pointer, not called here)
    // 0x56c8647  mov r9,rsi              ; r9 = passObj
    // 0x56c8650  jmp 0xBC61560           ; tail call to sub_bc61560(rcxArg, rdxArg, &sub_56c8810, passObj)
    bgfx::sub_bc61560(rcxArg, rdxArg,
                      reinterpret_cast<void*>(sub_56c8810), passObj);  // 0x56c8640  lea r8,[0x56C8810]
                                                                         // 0x56c8647  mov r9,rsi
                                                                         // 0x56c8650  jmp 0xBC61560
}

} // namespace native

LIFT_FN(sub_56c85c0, "sub_56c85c0", 0x56C85C0, ::native::sub_56c85c0, nullptr);

// Verbatim instructions of [0x56c85c0, 0x56c8655) (rdis dis 0x56c85c0 0x95);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x56c85c0  push rsi
0x56c85c1  push rdi
0x56c85c2  sub rsp,0x28
0x56c85c6  mov rsi,rcx
0x56c85c9  mov rax,[rdx]
0x56c85cc  mov [rcx+0x100],rax
0x56c85d3  mov rax,[rdx+0x10]
0x56c85d7  test rax,rax
0x56c85da  je short 0x56C85E6
0x56c85dc  lock inc dword ptr [rax+8]
0x56c85e0  mov rax,[rdx+0x10]
0x56c85e4  jmp short 0x56C85E8
0x56c85e6  xor eax,eax
0x56c85e8  mov rcx,[rdx+8]
0x56c85ec  mov [rsi+0x108],rcx
0x56c85f3  mov rdi,[rsi+0x110]
0x56c85fa  mov [rsi+0x110],rax
0x56c8601  test rdi,rdi
0x56c8604  je short 0x56C8631
0x56c8606  lock dec dword ptr [rdi+8]
0x56c860a  jne short 0x56C8631
0x56c860c  mov rax,[rdi]
0x56c860f  mov rax,[rax]
0x56c8612  mov rcx,rdi
0x56c8615  call qword ptr [0xF99FFA0]
0x56c861b  lock dec dword ptr [rdi+0xC]
0x56c861f  jne short 0x56C8631
0x56c8621  mov rax,[rdi]
0x56c8624  mov rax,[rax+8]
0x56c8628  mov rcx,rdi
0x56c862b  call qword ptr [0xF99FFA0]
0x56c8631  mov rax,[rsi+0x108]
0x56c8638  mov rcx,[rax+0x10]
0x56c863c  movzx edx,word ptr [rax+8]
0x56c8640  lea r8,[0x56C8810]
0x56c8647  mov r9,rsi
0x56c864a  add rsp,0x28
0x56c864e  pop rdi
0x56c864f  pop rsi
0x56c8650  jmp 0xBC61560
#endif
