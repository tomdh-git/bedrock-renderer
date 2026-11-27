// LIFT 0xe809fb0 size 0xa1 1.26.62.01 sub_e809fb0
#include "sub_e809fb0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native { namespace d3d12 {

extern "C" void sub_e809fb0(void* a0, void* a1)
{
    // 0xe809fb0..0xe809fca : push rbp ; push rsi ; push rdi ; sub rsp,0xB0 ; lea rbp,[rsp+0x80]
    // (frame prologue; rbp = rsp + 0x80; locals addressed as [rbp +/- off])

    SlotContextA ctxA = {}; // frame slot [rbp-0x60]
    SlotContextB ctxB = {}; // frame slot [rbp-0x20]

    // 0xe809fca..0xe809fd1 : lea rax,[0xF4EE230] ; mov [rbp-0x60],rax
    ctxA.base = reinterpret_cast<void*>(kContextBaseA); // 0xe809fca lea rax,[0xF4EE230] ; 0xe809fd1 mov [rbp-0x60],rax
    // 0xe809fd5 : mov [rbp-0x58],rdx
    ctxA.ptr = a1; // 0xe809fd5
    // 0xe809fd9..0xe809fe1 : lea rsi,[rbp-0x60] ; mov [rbp-0x28],rsi   (&ctxA saved at [rbp-0x28])
    void* savedA = &ctxA; // 0xe809fd9 / 0xe809fdd
    // 0xe809fe1 : lea rdi,[rbp-0x20]
    // 0xe809fe5..0xe809fec : lea rax,[0xF4EE260] ; mov [rbp-0x20],rax
    ctxB.base = reinterpret_cast<void*>(kContextBaseB); // 0xe809fe5 lea rax,[0xF4EE260] ; 0xe809fec mov [rbp-0x20],rax
    // 0xe809ff0 : mov [rbp-0x18],rdx
    ctxB.ptr = a1; // 0xe809ff0
    // 0xe809ff4 : mov [rbp+0x18],rdi   (&ctxB saved at [rbp+0x18])
    void* savedB = &ctxB; // 0xe809ff4
    // 0xe809ff8 : mov [rbp+0x20],rdx   (dead store: never read again)
    // 0xe809fc2 : mov [rbp+0x28],0xFFFFFFFFFFFFFFFE (dead store: never read again)
    // 0xe809ffc : mov rdx,rsi          (second argument for sub_e839020)

    // 0xe809fff  call 0xE839020        ; -> sub_e839020   (callee in lift set: native::d3d12::sub_e839020)
    sub_e839020(a0, &ctxA);

    // 0xe80a004 : nop
    // 0xe80a005..0xe80a014 : mov rcx,[rbp+0x18] ; test rcx,rcx ; je short 0xE80A029 ; cmp rcx,rdi ; setne dl
    if (savedB != nullptr) {             // 0xe80a005  test rcx,rcx ; je short 0xE80A029
        // 0xe80a00e..0xe80a012 : cmp rcx,rdi ; setne dl   (self-comparison &ctxB==&ctxB; result discarded)
        // 0xe80a014..0xe80a017 : mov rax,[rcx]            (rcx = &ctxB)
        // 0xe80a017..0xe80a01b : mov rax,[rax+0x20]       (method pointer at byte slot 0x20 of the context base)
        using RelFn = void(__cdecl*)(void*);
        RelFn fnB = reinterpret_cast<RelFn>(
            *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(ctxB.base) + kMethodSlot));
        // rcx = &ctxB; rdx holds the discarded setne result (dl == 0), exactly as in the original
        fnB(&ctxB);                      // 0xe80a01b  call qword ptr [0xF99FFA0]  (sub_eea6040 vendor boundary thunk: jmp rax)
        savedB = nullptr;                // 0xe80a021  mov [rbp+0x18],0   (saved &ctxB cleared; never read again)
    }
    // 0xe80a00c : je not taken (rcx = &ctxB != 0) -> fall through to 0xe80a029

    // 0xe80a029..0xe80a038 : mov rcx,[rbp-0x28] ; test rcx,rcx ; je short 0xE80A046 ; cmp rcx,rsi ; setne dl
    if (savedA != nullptr) {             // 0xe80a029  test rcx,rcx ; je short 0xE80A046
        // 0xe80a032..0xe80a038 : cmp rcx,rsi ; setne dl   (self-comparison; result discarded)
        // 0xe80a038..0xe80a03b : mov rax,[rcx]            (rcx = &ctxA)
        // 0xe80a03b..0xe80a03f : mov rax,[rax+0x20]
        using RelFn = void(__cdecl*)(void*);
        RelFn fnA = reinterpret_cast<RelFn>(
            *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(ctxA.base) + kMethodSlot));
        fnA(&ctxA);                      // 0xe80a03f  call qword ptr [0xF99FFA0]  (sub_eea6040 vendor boundary thunk: jmp rax)
    }

    // 0xe80a045 : nop
    // 0xe80a046..0xe80a051 : add rsp,0xB0 ; pop rdi ; pop rsi ; pop rbp ; ret
}

// Layout assertions (mirrored from sub_e809fb0.h): every frame offset the function uses.
static_assert(offsetof(SlotContextA, base) == 0x00, "sub_e809fb0: context A base offset");
static_assert(offsetof(SlotContextA, ptr)  == 0x08, "sub_e809fb0: context A ptr offset");
static_assert(sizeof(SlotContextA) == 0x10,  "sub_e809fb0: context A size");
static_assert(offsetof(SlotContextB, base) == 0x00, "sub_e809fb0: context B base offset");
static_assert(offsetof(SlotContextB, ptr)  == 0x08, "sub_e809fb0: context B ptr offset");
static_assert(sizeof(SlotContextB) == 0x10,  "sub_e809fb0: context B size");
static_assert(kMethodSlot % sizeof(void*) == 0, "sub_e809fb0: method slot is pointer-sized");

LIFT_FN(sub_e809fb0, "RendererContextD3D12 base slot 58", 0xe809fb0, sub_e809fb0, nullptr);

} } // namespace native::d3d12

// Verbatim log of every call instruction in [0xe809fb0, 0xe80a051) (rdis dis output, two spaces after address):
#if 0
0xe809fff  call 0xE839020                                ; -> sub_e839020
0xe80a01b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe80a03f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
#endif
