// LIFT 0xed36950 size 0x52 1.26.62.01 sub_ed36950
#include "sub_ed36950.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native {

// Data-slot thunk: the slot RVA 0xF99FF98 is read at every call, exactly as the original
// does (0xed36978 call qword ptr [0xF99FF98]); [data_f99ff98] currently holds sub_e9c7f10
// [V: rdis dis]. Not a static callee and not a boundary wrapper - rule 68: a call through a
// data slot is made as a function pointer read from the slot at call time, documenting the
// slot RVA.
using Ed36950Thunk = std::uintptr_t (*)(void* iface, void* a1, std::uint32_t a2);

inline Ed36950Thunk ed36950_thunk()
{
    return reinterpret_cast<Ed36950Thunk>(
        *reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + kThunkSlotRva));
}

std::uintptr_t sub_ed36950(void* a0, void* a1, std::uint32_t a2)
{
    // 0xed36950..0xed36964: prologue (mov [rsp+8]rbx, [rsp+0x10]rsi, [rsp+0x18]rdi,
    // push r14, sub rsp,0x20) - stack frame only, no game-memory effect.
    // 0xed36965  mov rax,[rcx]           vtable = a0->vtable          (a0+0x00)
    const sub_ed36950_this* const self = reinterpret_cast<const sub_ed36950_this*>(a0);
    void* const vtable = self->vtable;
    // 0xed36968  mov r14,rcx             r14 = a0  (this restored for the tail call)
    // 0xed3696b  mov edi,r8d             a2 zero-extended (scratch copy)
    // 0xed3696e  mov rsi,rdx             rsi = a1
    // 0xed36971  mov rbx,[rax+0x20]      iface = vtable[4]            (vtable+0x20)
    void* const iface = reinterpret_cast<const sub_ed36950_vtable*>(vtable)->target;
    // 0xed36975  mov rcx,rbx             slot call 'this' = vtable[4]
    // 0xed36978  call qword ptr [0xF99FF98]      side-effect call; RAX result discarded
    ed36950_thunk()(iface, a1, a2);
    // 0xed3697e  mov r8d,edi
    // 0xed36981  mov rdx,rsi           arguments restored: rcx=a0, rdx=a1, r8=a2
    // 0xed36984  mov rcx,r14
    // 0xed36987  mov rax,rbx           rax = vtable[4] (slot call result discarded)
    // 0xed3698a..0xed3699d: epilogue (rbx=[rsp+0x30], rsi=[rsp+0x38], rdi=[rsp+0x40],
    //                         add rsp,0x20, pop r14) - stack only
    // 0xed3699f  jmp rax               tail call to vtable[4]; its RAX result is ours
    return reinterpret_cast<std::uintptr_t (*)(void*, void*, std::uint32_t)>(iface)(a0, a1, a2);  // 0xed3699f jmp rax
}

// Layout assertions (definitions in sub_ed36950.h; repeated here so liftcheck sees them).
static_assert(offsetof(sub_ed36950_this, vtable) == 0x00, "sub_ed36950: this->vtable at +0x00");
static_assert(offsetof(sub_ed36950_vtable, target) == 0x20, "sub_ed36950: vtable[4] at +0x20");

// Verbatim call instructions of [0xed36950, 0xed369a2) (matches rdis dis output,
// two spaces after the address):
#if 0
0xed36978  call qword ptr [0xF99FF98]
#endif

LIFT_FN(sub_ed36950, "sub_ed36950", 0xed36950, sub_ed36950, nullptr);

} // namespace native
