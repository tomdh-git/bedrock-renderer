// LIFT 0xe809cc0 size 0xa1 1.26.62.01 sub_e809cc0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e809cc0.h"

#include <cstddef>
#include <cstdint>

namespace native::d3d12 {

// Layout assertion for the two stack objects (full asserts with per-field offsets live in sub_e809cc0.h).
static_assert(sizeof(SlotObjA) == 0x40 && sizeof(SlotObjB) == 0x50, "sub_e809cc0 stack-object layouts must match the disassembly");

extern "C" void sub_e809cc0(void* ctx, void* arg2)
{
    // 0xe809cc0..0xe809cca  push rbp; push rsi; push rdi; sub rsp,0xB0; lea rbp,[rsp+0x80] (prologue, machine instructions only)
    // 0xe809cd2..0xe809d08  objB.state = -2; objA.vptr = 0xF4EE1D0; objA.unk08 = arg2;
    //                       objA.self = &objA; objB.vptr = 0xF4EE200; objB.unk08 = arg2;
    //                       objB.self = &objB; objB.unk40 = arg2
    //
    // Stack: objA at [rbp-0x60] (sizeof 0x40), objB at [rbp-0x20] (sizeof 0x50).
    // [rbp-0x28] aliases objA+0x38 (objA.self); [rbp+0x18] aliases objB+0x38 (objB.self).

    SlotObjB objB;   // [rbp-0x20] (rsp+0x60), sizeof 0x50
    SlotObjA objA;   // [rbp-0x60] (rsp+0x20), sizeof 0x40

    // 0xe809cd2  mov qword ptr [rbp+0x28], 0xFFFFFFFFFFFFFFFE  -> objB.state (objB+0x48)
    objB.state = -2;

    // 0xe809cda..0xe809ce1  lea rax,[0xF4EE1D0]; mov [rbp-0x60],rax   -> objA.vptr
    objA.vptr = reinterpret_cast<void*>(0xF4EE1D0);
    // 0xe809ce5  mov [rbp-0x58],rdx   -> objA.unk08
    objA.unk08 = arg2;
    // 0xe809ce9..0xe809ced  lea rsi,[rbp-0x60]; mov [rbp-0x28],rsi   -> objA.self = &objA
    objA.self = &objA;

    // 0xe809cf1..0xe809cfc  lea rdi,[rbp-0x20]; lea rax,[0xF4EE200]; mov [rbp-0x20],rax   -> objB.vptr
    objB.vptr = reinterpret_cast<void*>(0xF4EE200);
    // 0xe809d00  mov [rbp-0x18],rdx   -> objB.unk08
    objB.unk08 = arg2;
    // 0xe809d04  mov [rbp+0x18],rdi   -> objB.self = &objB
    objB.self = &objB;
    // 0xe809d08  mov [rbp+0x20],rdx   -> objB.unk40 (rdx still arg2 at this point)
    objB.unk40 = arg2;

    // 0xe809d0c..0xe809d0f  mov rdx,rsi ; call 0xE839020     ; rcx = ctx (argument register, never spilled), rdx = &objA
    // 0xe809d0f  call 0xE839020       ; -> sub_e839020 (lift set, native symbol)
    sub_e839020(ctx, &objA);

    // 0xe809d14  nop

    // 0xe809d15..0xe809d39
    if (objB.self != nullptr) {
        // 0xe809d1e  cmp rcx,rdi ; 0xe809d21  setne dl   ; rcx == rdi == &objB, so dl == 0; result never read
        (void)(objB.self != objB.self);
        // 0xe809d24  mov rax,[rcx]           -> rax = objB.self->vptr
        // 0xe809d27  mov rax,[rax+0x20]      -> rax = objB.self->vptr[4]
        // 0xe809d2b  call qword ptr [0xF99FFA0] ; -> sub_eea6040 via data slot 0xF99FFA0 (vendor boundary);
        //            sub_eea6040 is "jmp rax", net effect: objB.self->vptr[4](objB.self)
        void** vtableB = reinterpret_cast<void**>(objB.self->vptr);
        using ReleaseFn = void(__thiscall*)(void*);
        ReleaseFn releaseB = reinterpret_cast<ReleaseFn>(vtableB[4]);
        releaseB(objB.self);
        // 0xe809d31  mov qword ptr [rbp+0x18], 0   -> objB.self = 0
        objB.self = nullptr;
    }

    // 0xe809d39..0xe809d56
    if (objA.self != nullptr) {
        // 0xe809d42  cmp rcx,rsi ; 0xe809d45  setne dl   ; rcx == rsi == &objA, so dl == 0; result never read
        (void)(objA.self != objA.self);
        // 0xe809d48  mov rax,[rcx]           -> rax = objA.self->vptr
        // 0xe809d4b  mov rax,[rax+0x20]      -> rax = objA.self->vptr[4]
        // 0xe809d4f  call qword ptr [0xF99FFA0] ; objA.self->vptr[4](objA.self)
        void** vtableA = reinterpret_cast<void**>(objA.self->vptr);
        using ReleaseFn = void(__thiscall*)(void*);
        ReleaseFn releaseA = reinterpret_cast<ReleaseFn>(vtableA[4]);
        releaseA(objA.self);
        // no store nulling objA.self: falls through to the epilogue
    }

    // 0xe809d56..0xe809d60  add rsp,0xB0; pop rdi; pop rsi; pop rbp; ret
    return;
}

} // namespace native::d3d12

// Verbatim log of every instruction in [0xe809cc0, 0xe809d61) (rdis dis output, two spaces after address):
#if 0
0xe809cc0  push rbp
0xe809cc1  push rsi
0xe809cc2  push rdi
0xe809cc3  sub rsp,0xB0
0xe809cca  lea rbp,[rsp+0x80]
0xe809cd2  mov qword ptr [rbp+0x28],0xFFFFFFFFFFFFFFFE
0xe809cda  lea rax,[0xF4EE1D0]
0xe809ce1  mov [rbp-0x60],rax
0xe809ce5  mov [rbp-0x58],rdx
0xe809ce9  lea rsi,[rbp-0x60]
0xe809ced  mov [rbp-0x28],rsi
0xe809cf1  lea rdi,[rbp-0x20]
0xe809cf5  lea rax,[0xF4EE200]
0xe809cfc  mov [rbp-0x20],rax
0xe809d00  mov [rbp-0x18],rdx
0xe809d04  mov [rbp+0x18],rdi
0xe809d08  mov [rbp+0x20],rdx
0xe809d0c  mov rdx,rsi
0xe809d0f  call 0xE839020
0xe809d14  nop
0xe809d15  mov rcx,[rbp+0x18]
0xe809d19  test rcx,rcx
0xe809d1c  je short 0xE809D39
0xe809d1e  cmp rcx,rdi
0xe809d21  setne dl
0xe809d24  mov rax,[rcx]
0xe809d27  mov rax,[rax+0x20]
0xe809d2b  call qword ptr [0xF99FFA0]
0xe809d31  mov qword ptr [rbp+0x18],0
0xe809d39  mov rcx,[rbp-0x28]
0xe809d3d  test rcx,rcx
0xe809d40  je short 0xE809D56
0xe809d42  cmp rcx,rsi
0xe809d45  setne dl
0xe809d48  mov rax,[rcx]
0xe809d4b  mov rax,[rax+0x20]
0xe809d4f  call qword ptr [0xF99FFA0]
0xe809d55  nop
0xe809d56  add rsp,0xB0
0xe809d5d  pop rdi
0xe809d5e  pop rsi
0xe809d5f  pop rbp
0xe809d60  ret
#endif

LIFT_FN(sub_e809cc0, "sub_e809cc0", 0xe809cc0, sub_e809cc0, nullptr);

} // namespace native::d3d12
