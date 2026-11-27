#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

namespace native {

// sub_ed36950 (0xed36950, size 0x52, 1.26.62.01): data-slot thunk.
//
//   0xed36965  mov rax,[rcx]           [a0 + 0x00]  vtable pointer                  R
//   0xed36971  mov rbx,[rax+0x20]      [vtable + 0x20]  function pointer             R   (tail-call target; also 'this' of the slot call)
//   0xed36978  call qword ptr [0xF99FF98]   ; [data_f99ff98] = sub_e9c7f10   side effect; return discarded
//   0xed3699f  jmp rax                          tail call to vtable[4]; RAX as-is
//
// Reads: two game-memory qword reads (listed above). Writes: no game memory - only its own
// stack frame (callee-saved save/restore). Calls: one indirect call through data slot RVA
// 0xF99FF98 (loader-resolved, read at every call, never a static callee - rule 68).
//
// Layout constants (all offsets [V] from the disassembly of [0xed36950, 0xed369a2)):
struct sub_ed36950_this {   // object passed in RCX; only the field touched here is modeled
    void* vtable;           // +0x00 vtable pointer (0xed36965 mov rax,[rcx])
};
static_assert(offsetof(sub_ed36950_this, vtable) == 0x00, "sub_ed36950: this->vtable at +0x00");

struct sub_ed36950_vtable {  // vtable pointed at by this->vtable; only slot 4 (+0x20) is touched
    std::uint8_t pad0x00[0x20];
    void* target;            // +0x20 vtable[4]: tail-call target (0xed3699f jmp rax) and the
                             // 'this' argument of the data-slot call (0xed36975 mov rcx,rbx)
};
static_assert(offsetof(sub_ed36950_vtable, target) == 0x20, "sub_ed36950: vtable[4] at +0x20");

// Image data read by the function (RVA; VA = imageBase() + RVA):
static constexpr std::uintptr_t kThunkSlotRva = 0xF99FF98;  // 0xed36978 call qword ptr [0xF99FF98]

// std::uintptr_t sub_ed36950(void* a0 /*rcx*/, void* a1 /*rdx*/, std::uint32_t a2 /*r8d*/)
// Return: pointer-sized; RAX of the tail-called vtable[4] propagates as-is (0xed3699f jmp rax).
// The exact return type of vtable[4] is not statically known.
std::uintptr_t sub_ed36950(void* a0, void* a1, std::uint32_t a2);

} // namespace native
