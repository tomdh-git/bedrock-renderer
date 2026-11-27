// LIFT 0xed369b0 size 0x52 1.26.62.01 sub_ed369b0
#include "sub_ed369b0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native {

// Data-slot thunk: the slot RVA 0xF99FF98 is read at every call, exactly as the original
// does (0xed369d8 call qword ptr [0xF99FF98]); [data_f99ff98] currently holds sub_e9c7f10
// ([V: rdis dis]). Not a static callee and not a boundary wrapper - rule 69: a call through a
// data slot is made as a function pointer read from the slot at call time, documenting the
// slot RVA. The helper's RAX result is discarded by the original (0xed369e7 mov rax,rbx
// overwrites it before the tail call).
using Ed369b0Thunk = std::uintptr_t (*)(void* vfunc, void* a1, std::uint32_t a2);

inline Ed369b0Thunk ed369b0_thunk()
{
    return reinterpret_cast<Ed369b0Thunk>(
        *reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + kThunkSlotRva));
}

std::uintptr_t sub_ed369b0(void* a0, void* a1, std::uint32_t a2)
{
    // 0xed369b0..0xed369c4: prologue - save callee-saved RBX/RSI/RDI/R14, build the stack frame.
    // 0xed369c5  mov rax,[rcx]           vtable = a0->vtable              (a0+0x00)  R
    const sub_ed369b0_this* const self = reinterpret_cast<const sub_ed369b0_this*>(a0);
    void* const vtable = self->vtable;
    // 0xed369c8  mov r14,rcx             r14 = a0 (this, restored for the tail call)
    // 0xed369cb  mov edi,r8d             a2 zero-extended scratch copy
    // 0xed369ce  mov rsi,rdx             rsi = a1
    // 0xed369d1  mov rbx,[rax+0x18]      target = vtable[3]               (vtable+0x18)  R
    void* const target = reinterpret_cast<const sub_ed369b0_vtable*>(vtable)->target;
    // 0xed369d5  mov rcx,rbx             slot call 'this' = vtable[3]
    // 0xed369d8  call qword ptr [0xF99FF98]   side-effect call; RAX discarded
    ed369b0_thunk()(target, a1, a2);
    // 0xed369de  mov r8d,edi
    // 0xed369e1  mov rdx,rsi           arguments restored: rcx=a0, rdx=a1, r8=a2
    // 0xed369e4  mov rcx,r14
    // 0xed369e7  mov rax,rbx           rax = vtable[3] (slot call result discarded)
    // 0xed369ea..0xed369fd: epilogue - restore RBX/RSI/RDI/R14, tear down the stack frame.
    // 0xed369ff  jmp rax               tail call to vtable[3]; its RAX result is ours
    return reinterpret_cast<std::uintptr_t (*)(void*, void*, std::uint32_t)>(target)(a0, a1, a2);  // 0xed369ff jmp rax
}

// Layout assertions (definitions in sub_ed369b0.h; repeated here so liftcheck sees them).
static_assert(offsetof(sub_ed369b0_this, vtable) == 0x00, "sub_ed369b0: this->vtable at +0x00");
static_assert(offsetof(sub_ed369b0_vtable, target) == 0x18, "sub_ed369b0: vtable[3] at +0x18");

// Verbatim call instructions of [0xed369b0, 0xed36a02) (matches rdis dis output,
// two spaces after the address):
#if 0
0xed369d8  call qword ptr [0xF99FF98]
#endif

LIFT_FN(sub_ed369b0, "sub_ed369b0", 0xed369b0, sub_ed369b0, nullptr);

} // namespace native
