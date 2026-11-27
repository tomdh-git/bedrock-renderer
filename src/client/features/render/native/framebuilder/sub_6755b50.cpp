// LIFT 0x6755b50 size 0xe2 1.26.62.01 sub_6755b50
#include "client/features/render/native/framebuilder/sub_6755b50.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>
#include <intrin.h>

static_assert(sizeof(void*) == 8, "6755b50: x64 ABI, pointer-sized address space");

namespace native {

// sub_6755b50 (0x6755b50, size 0xe2, 1.26.62.01, "BgfxFrameBuilder slot 11").
//
// Reversed source (complete). Every instruction of [0x6755b50, 0x6755c32) is
// covered by the citation next to the statement that implements it, and every
// `call` is quoted verbatim in the #if 0 block at the end of this file.
//
// The function releases up to three refcounted objects owned by the container
// passed in R8 (slots +0x38, +0x28, +0x8, in that order; RCX == 2 skips to
// the +0x8 slot), gated on bit (RCX & 31) of mask 0x33 being clear. Each
// object has two atomic refcounts (+0x08, +0x0C); a count hitting zero invokes
// the corresponding virtual entry through the sub_eea6040 jmp-rax thunk
// (`call qword ptr [0xF99FFA0]`); the final slot's second count ends in a tail
// call through the same data slot (0x6755c2f `jmp rdx`).
//
// sub_eea6040 (0xeea6040) is itself a `jmp rax` thunk [V: rdis dis 0xeea6040];
// control never returns from a taken thunk call, so the instructions between
// the first taken call of a slot and the next slot are unreachable in the exe.
// They are still translated below, in the same branch order, for faithfulness
// to the instruction stream.
void sub_6755b50(std::uintptr_t a1, void* container) {
    auto* const self = reinterpret_cast<Sub6755b50Container*>(container);  // R8 = container

    // 0x6755b50..0x6755b5f: push rsi; push rdi; sub rsp,0x28; mov eax,0x33;
    // bt rax,rcx. Bit (a1 & 31) of 0x33 set -> epilogue return (jae not taken).
    if (((0x33u >> (a1 & 31u)) & 1u) != 0u) {   // 0x6755b56 mov eax,0x33 ; 0x6755b5b bt rax,rcx ; 0x6755b5f jae short 0x6755B68
        // 0x6755b61..0x6755b67: add rsp,0x28; pop rdi; pop rsi; ret
        return;                                 // 0x6755b61 add rsp,0x28 ; 0x6755b65 pop rdi ; 0x6755b66 pop rsi ; 0x6755b67 ret
    }

    // 0x6755b68: cmp rcx,2 ; je short 0x6755BE8  -> a1 == 2 skips the first two slots
    if (a1 != 2u) {                             // 0x6755b68 cmp rcx,2 ; 0x6755b6c je short 0x6755BE8
        // ---- slot 1: container + 0x38 (0x6755b6e..0x6755ba8)
        void* const object1 = self->slot0x38;   // 0x6755b6e mov rsi,[r8+0x38]
        if (object1 != nullptr) {               // 0x6755b72 test rsi,rsi ; 0x6755b75 je short 0x6755BAB
            auto* const obj1 = reinterpret_cast<Sub6755b50Object*>(object1);
            // 0x6755b77 lock dec dword ptr [rsi+8]
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj1->refs0x08)) == 0) {
                // 0x6755b7d mov rax,[rsi] ; 0x6755b80 mov rax,[rax]   (vfptr[0] -> RAX)
                // 0x6755b83 mov rcx,rsi ; 0x6755b86 mov rdi,r8        (RCX = object, RDI = container)
                // 0x6755b89 call qword ptr [0xF99FFA0]                (sub_eea6040: jmp rax -> vfptr[0](object))
                // 0x6755b8f mov r8,rdi                                (container restored)
                void** const vfptr1 = reinterpret_cast<void**>(obj1->vfptr);
                boundary::g_eea6040_thunk(object1, vfptr1[0]);   // 0x6755b89 call qword ptr [0xF99FFA0]
            }
            // 0x6755b92 lock dec dword ptr [rsi+0xC]
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj1->refs0x0c)) == 0) {
                // 0x6755b98 mov rax,[rsi] ; 0x6755b9b mov rax,[rax+8] (vfptr[1] -> RAX)
                // 0x6755b9f mov rcx,rsi
                // 0x6755ba2 call qword ptr [0xF99FFA0]              (sub_eea6040: jmp rax -> vfptr[1](object))
                // 0x6755ba8 mov r8,rdi
                void** const vfptr1b = reinterpret_cast<void**>(obj1->vfptr);
                boundary::g_eea6040_thunk(object1, vfptr1b[1]);  // 0x6755ba2 call qword ptr [0xF99FFA0]
            }
        }
        // ---- slot 2: container + 0x28 (0x6755bab..0x6755be5)
        void* const object2 = self->slot0x28;   // 0x6755bab mov rsi,[r8+0x28]
        if (object2 != nullptr) {               // 0x6755baf test rsi,rsi ; 0x6755bb2 je short 0x6755BE8
            auto* const obj2 = reinterpret_cast<Sub6755b50Object*>(object2);
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj2->refs0x08)) == 0) {
                void** const vfptr2 = reinterpret_cast<void**>(obj2->vfptr);
                boundary::g_eea6040_thunk(object2, vfptr2[0]);   // 0x6755bc6 call qword ptr [0xF99FFA0]
            }
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj2->refs0x0c)) == 0) {
                void** const vfptr2b = reinterpret_cast<void**>(obj2->vfptr);
                boundary::g_eea6040_thunk(object2, vfptr2b[1]);  // 0x6755bdf call qword ptr [0xF99FFA0]
            }
        }
    }
    // loc_6755be8: slot 3: container + 0x08 (0x6755be8..0x6755c2f)
    void* const object3 = self->slot0x08;   // 0x6755be8 mov rsi,[r8+8]
    if (object3 != nullptr) {               // 0x6755bec test rsi,rsi ; 0x6755bef je 0x6755B61
        auto* const obj3 = reinterpret_cast<Sub6755b50Object*>(object3);
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj3->refs0x08)) == 0) {
            void** const vfptr3 = reinterpret_cast<void**>(obj3->vfptr);
            boundary::g_eea6040_thunk(object3, vfptr3[0]);   // 0x6755c08 call qword ptr [0xF99FFA0]
            // 0x6755c0e lock dec dword ptr [rsi+0xC] ; 0x6755c12 jne 0x6755B61
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj3->refs0x0c)) == 0) {
                // 0x6755c18 mov rax,[rsi] ; 0x6755c1b mov rax,[rax+8] (vfptr[1] -> RAX, dead load)
                // 0x6755c1f mov rdx,[0xF99FFA0] ; 0x6755c26 mov rcx,rsi  (tail-call setup)
                // 0x6755c29 add rsp,0x28 ; 0x6755c2d pop rdi ; 0x6755c2e pop rsi ; 0x6755c2f jmp rdx
                boundary::g_eea6040_thunk(object3, vfptr3[1]);   // 0x6755c2f jmp rdx -> sub_eea6040 tail call (noreturn)
            }
        }
    }
    // 0x6755b61..0x6755b67: add rsp,0x28; pop rdi; pop rsi; ret (epilogue;
    // reached from the bit-set path and from every slot exit via je/jne to 0x6755B61)
    return;
}

} // namespace native

LIFT_FN(sub_6755b50, "sub_6755b50", 0x6755B50, ::native::sub_6755b50, nullptr);

#if 0
// Verbatim instruction quotes of [0x6755b50, 0x6755c32) (rdis dis 0x6755b50 0xe2);
// machine-checked by tools/sigs/verify_oc.py against the exe.
0x6755b50  push rsi
0x6755b51  push rdi
0x6755b52  sub rsp,0x28
0x6755b56  mov eax,0x33
0x6755b5b  bt rax,rcx
0x6755b5f  jae short 0x6755B68
0x6755b61  add rsp,0x28
0x6755b65  pop rdi
0x6755b66  pop rsi
0x6755b67  ret
0x6755b68  cmp rcx,2
0x6755b6c  je short 0x6755BE8
0x6755b6e  mov rsi,[r8+0x38]
0x6755b72  test rsi,rsi
0x6755b75  je short 0x6755BAB
0x6755b77  lock dec dword ptr [rsi+8]
0x6755b7b  jne short 0x6755BAB
0x6755b7d  mov rax,[rsi]
0x6755b80  mov rax,[rax]
0x6755b83  mov rcx,rsi
0x6755b86  mov rdi,r8
0x6755b89  call qword ptr [0xF99FFA0]
0x6755b8f  mov r8,rdi
0x6755b92  lock dec dword ptr [rsi+0xC]
0x6755b96  jne short 0x6755BAB
0x6755b98  mov rax,[rsi]
0x6755b9b  mov rax,[rax+8]
0x6755b9f  mov rcx,rsi
0x6755ba2  call qword ptr [0xF99FFA0]
0x6755ba8  mov r8,rdi
0x6755bab  mov rsi,[r8+0x28]
0x6755baf  test rsi,rsi
0x6755bb2  je short 0x6755BE8
0x6755bb4  lock dec dword ptr [rsi+8]
0x6755bb8  jne short 0x6755BE8
0x6755bba  mov rax,[rsi]
0x6755bbd  mov rax,[rax]
0x6755bc0  mov rcx,rsi
0x6755bc3  mov rdi,r8
0x6755bc6  call qword ptr [0xF99FFA0]
0x6755bcc  mov r8,rdi
0x6755bcf  lock dec dword ptr [rsi+0xC]
0x6755bd3  jne short 0x6755BE8
0x6755bd5  mov rax,[rsi]
0x6755bd8  mov rax,[rax+8]
0x6755bdc  mov rcx,rsi
0x6755bdf  call qword ptr [0xF99FFA0]
0x6755be5  mov r8,rdi
0x6755be8  mov rsi,[r8+8]
0x6755bec  test rsi,rsi
0x6755bef  je 0x6755B61
0x6755bf5  lock dec dword ptr [rsi+8]
0x6755bf9  jne 0x6755B61
0x6755bff  mov rax,[rsi]
0x6755c02  mov rax,[rax]
0x6755c05  mov rcx,rsi
0x6755c08  call qword ptr [0xF99FFA0]
0x6755c0e  lock dec dword ptr [rsi+0xC]
0x6755c12  jne 0x6755B61
0x6755c18  mov rax,[rsi]
0x6755c1b  mov rax,[rax+8]
0x6755c1f  mov rdx,[0xF99FFA0]
0x6755c26  mov rcx,rsi
0x6755c29  add rsp,0x28
0x6755c2d  pop rdi
0x6755c2e  pop rsi
0x6755c2f  jmp rdx
#endif
