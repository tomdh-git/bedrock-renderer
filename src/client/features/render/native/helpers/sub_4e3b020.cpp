// LIFT 0x4e3b020 size 0x11e 1.26.62.01 sub_4e3b020
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_4e3b020.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

static_assert(sizeof(void*) == 8, "sub_4e3b020: x64 ABI, pointer-sized address space");

namespace native::helpers {

LIFT_FN(sub_4e3b020, "sub_4e3b020", 0x4e3b020, sub_4e3b020, nullptr);

// Verbatim call instructions from the disassembly of [0x4e3b020, 0x4e3b13e) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
// Every one of them targets data slot 0xF99FFA0, which holds sub_eea6040, a `jmp rax`
// forwarder; the preceding two `mov rax` loads select the vtable slot that is reached.
#if 0
0x4e3b041  call qword ptr [0xF99FFA0]
0x4e3b057  call qword ptr [0xF99FFA0]
0x4e3b075  call qword ptr [0xF99FFA0]
0x4e3b08b  call qword ptr [0xF99FFA0]
0x4e3b0a9  call qword ptr [0xF99FFA0]
0x4e3b0bf  call qword ptr [0xF99FFA0]
0x4e3b0dd  call qword ptr [0xF99FFA0]
0x4e3b0f3  call qword ptr [0xF99FFA0]
0x4e3b111  call qword ptr [0xF99FFA0]
#endif

// Releases the five refcounted members of *self in descending offset order
// (+0x58, +0x48, +0x30, +0x18, +0x08). For each member: strong-- ; if it reached zero,
// vtable[0](member) (destroy), then weak-- ; if that reached zero, vtable[1](member)
// (deallocate). The +0x08 member's deallocate call is a tail jump at 0x4e3b134.
extern "C" std::uintptr_t sub_4e3b020(void* selfRaw) {
    sub_4e3b020_self* self = static_cast<sub_4e3b020_self*>(selfRaw);
    sub_4e3b020_refcounted* rdi = nullptr;
    // RAX after each virtual call is the call's result; on a path that makes no virtual
    // call RAX is never written by this function, so 0 models the caller-defined entry value.
    std::uintptr_t result = 0;

    // 0x4e3b020..0x4e3b032: basic block 0 (prologue; member +0x58)
    //   0x4e3b020  push rsi
    //   0x4e3b021  push rdi
    //   0x4e3b022  sub rsp,0x28
    //   0x4e3b026  mov rsi,rcx
    //   0x4e3b029  mov rdi,[rcx+0x58]
    //   0x4e3b02d  test rdi,rdi
    //   0x4e3b030  je short 0x4E3B05D
    rdi = self->ref0x58;
    if (rdi == nullptr) goto L_0x4e3b05d;

    // 0x4e3b032..0x4e3b038: basic block 1
    //   0x4e3b032  lock dec dword ptr [rdi+8]
    //   0x4e3b036  jne short 0x4E3B05D
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->strong)) != 0) goto L_0x4e3b05d;

    // 0x4e3b038..0x4e3b04d: basic block 2
    //   0x4e3b038  mov rax,[rdi]
    //   0x4e3b03b  mov rax,[rax]
    //   0x4e3b03e  mov rcx,rdi
    //   0x4e3b041  call qword ptr [0xF99FFA0]
    //   0x4e3b047  lock dec dword ptr [rdi+0xC]
    //   0x4e3b04b  jne short 0x4E3B05D
    result = rdi->vtable->destroy(rdi);
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->weak)) != 0) goto L_0x4e3b05d;

    // 0x4e3b04d..0x4e3b05d: basic block 3
    //   0x4e3b04d  mov rax,[rdi]
    //   0x4e3b050  mov rax,[rax+8]
    //   0x4e3b054  mov rcx,rdi
    //   0x4e3b057  call qword ptr [0xF99FFA0]
    result = rdi->vtable->dealloc(rdi);

L_0x4e3b05d:
    // 0x4e3b05d..0x4e3b066: basic block 4 (member +0x48)
    //   0x4e3b05d  mov rdi,[rsi+0x48]
    //   0x4e3b061  test rdi,rdi
    //   0x4e3b064  je short 0x4E3B091
    rdi = self->ref0x48;
    if (rdi == nullptr) goto L_0x4e3b091;

    // 0x4e3b066..0x4e3b06c: basic block 5
    //   0x4e3b066  lock dec dword ptr [rdi+8]
    //   0x4e3b06a  jne short 0x4E3B091
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->strong)) != 0) goto L_0x4e3b091;

    // 0x4e3b06c..0x4e3b081: basic block 6
    //   0x4e3b06c  mov rax,[rdi]
    //   0x4e3b06f  mov rax,[rax]
    //   0x4e3b072  mov rcx,rdi
    //   0x4e3b075  call qword ptr [0xF99FFA0]
    //   0x4e3b07b  lock dec dword ptr [rdi+0xC]
    //   0x4e3b07f  jne short 0x4E3B091
    result = rdi->vtable->destroy(rdi);
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->weak)) != 0) goto L_0x4e3b091;

    // 0x4e3b081..0x4e3b091: basic block 7
    //   0x4e3b081  mov rax,[rdi]
    //   0x4e3b084  mov rax,[rax+8]
    //   0x4e3b088  mov rcx,rdi
    //   0x4e3b08b  call qword ptr [0xF99FFA0]
    result = rdi->vtable->dealloc(rdi);

L_0x4e3b091:
    // 0x4e3b091..0x4e3b09a: basic block 8 (member +0x30)
    //   0x4e3b091  mov rdi,[rsi+0x30]
    //   0x4e3b095  test rdi,rdi
    //   0x4e3b098  je short 0x4E3B0C5
    rdi = self->ref0x30;
    if (rdi == nullptr) goto L_0x4e3b0c5;

    // 0x4e3b09a..0x4e3b0a0: basic block 9
    //   0x4e3b09a  lock dec dword ptr [rdi+8]
    //   0x4e3b09e  jne short 0x4E3B0C5
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->strong)) != 0) goto L_0x4e3b0c5;

    // 0x4e3b0a0..0x4e3b0b5: basic block 10
    //   0x4e3b0a0  mov rax,[rdi]
    //   0x4e3b0a3  mov rax,[rax]
    //   0x4e3b0a6  mov rcx,rdi
    //   0x4e3b0a9  call qword ptr [0xF99FFA0]
    //   0x4e3b0af  lock dec dword ptr [rdi+0xC]
    //   0x4e3b0b3  jne short 0x4E3B0C5
    result = rdi->vtable->destroy(rdi);
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->weak)) != 0) goto L_0x4e3b0c5;

    // 0x4e3b0b5..0x4e3b0c5: basic block 11
    //   0x4e3b0b5  mov rax,[rdi]
    //   0x4e3b0b8  mov rax,[rax+8]
    //   0x4e3b0bc  mov rcx,rdi
    //   0x4e3b0bf  call qword ptr [0xF99FFA0]
    result = rdi->vtable->dealloc(rdi);

L_0x4e3b0c5:
    // 0x4e3b0c5..0x4e3b0ce: basic block 12 (member +0x18)
    //   0x4e3b0c5  mov rdi,[rsi+0x18]
    //   0x4e3b0c9  test rdi,rdi
    //   0x4e3b0cc  je short 0x4E3B0F9
    rdi = self->ref0x18;
    if (rdi == nullptr) goto L_0x4e3b0f9;

    // 0x4e3b0ce..0x4e3b0d4: basic block 13
    //   0x4e3b0ce  lock dec dword ptr [rdi+8]
    //   0x4e3b0d2  jne short 0x4E3B0F9
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->strong)) != 0) goto L_0x4e3b0f9;

    // 0x4e3b0d4..0x4e3b0e9: basic block 14
    //   0x4e3b0d4  mov rax,[rdi]
    //   0x4e3b0d7  mov rax,[rax]
    //   0x4e3b0da  mov rcx,rdi
    //   0x4e3b0dd  call qword ptr [0xF99FFA0]
    //   0x4e3b0e3  lock dec dword ptr [rdi+0xC]
    //   0x4e3b0e7  jne short 0x4E3B0F9
    result = rdi->vtable->destroy(rdi);
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->weak)) != 0) goto L_0x4e3b0f9;

    // 0x4e3b0e9..0x4e3b0f9: basic block 15
    //   0x4e3b0e9  mov rax,[rdi]
    //   0x4e3b0ec  mov rax,[rax+8]
    //   0x4e3b0f0  mov rcx,rdi
    //   0x4e3b0f3  call qword ptr [0xF99FFA0]
    result = rdi->vtable->dealloc(rdi);

L_0x4e3b0f9:
    // 0x4e3b0f9..0x4e3b102: basic block 16 (member +0x08)
    //   0x4e3b0f9  mov rsi,[rsi+8]
    //   0x4e3b0fd  test rsi,rsi
    //   0x4e3b100  je short 0x4E3B137
    rdi = self->ref0x08;
    if (rdi == nullptr) goto L_0x4e3b137;

    // 0x4e3b102..0x4e3b108: basic block 17
    //   0x4e3b102  lock dec dword ptr [rsi+8]
    //   0x4e3b106  jne short 0x4E3B137
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->strong)) != 0) goto L_0x4e3b137;

    // 0x4e3b108..0x4e3b11d: basic block 18
    //   0x4e3b108  mov rax,[rsi]
    //   0x4e3b10b  mov rax,[rax]
    //   0x4e3b10e  mov rcx,rsi
    //   0x4e3b111  call qword ptr [0xF99FFA0]
    //   0x4e3b117  lock dec dword ptr [rsi+0xC]
    //   0x4e3b11b  jne short 0x4E3B137
    result = rdi->vtable->destroy(rdi);
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->weak)) != 0) goto L_0x4e3b137;

    // 0x4e3b11d..0x4e3b137: basic block 19 (tail dispatch to vtable[1])
    //   0x4e3b11d  mov rax,[rsi]
    //   0x4e3b120  mov rax,[rax+8]
    //   0x4e3b124  mov rdx,[0xF99FFA0]
    //   0x4e3b12b  mov rcx,rsi
    //   0x4e3b12e  add rsp,0x28
    //   0x4e3b132  pop rdi
    //   0x4e3b133  pop rsi
    //   0x4e3b134  jmp rdx
    return rdi->vtable->dealloc(rdi);

L_0x4e3b137:
    // 0x4e3b137..0x4e3b13e: basic block 20 (epilogue)
    //   0x4e3b137  add rsp,0x28
    //   0x4e3b13b  pop rdi
    //   0x4e3b13c  pop rsi
    //   0x4e3b13d  ret
    return result;
}

} // namespace native::helpers
