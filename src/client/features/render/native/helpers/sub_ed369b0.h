#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_ed369b0 (0xed369b0, size 0x52, 1.26.62.01): data-slot thunk that dispatches to a virtual slot.
//
//   0xed369c5  mov rax,[rcx]           [a0 + 0x00]  vtable pointer                  R
//   0xed369d1  mov rbx,[rax+0x18]      [vtable + 0x18]  function pointer            R   (tail-call target; also 'this' of the slot call)
//   0xed369d8  call qword ptr [0xF99FF98]   ; [data_f99ff98] = sub_e9c7f10  side-effect call; return discarded
//   0xed369ff  jmp rax                          tail call to vtable[3]; RAX propagates as the return value
//
// Reads: two game-memory qword reads (listed above) plus the 8-byte call-target slot at RVA 0xF99FF98.
// Writes: no game memory - only the function's own stack frame (callee-saved save/restore).
// Calls: one indirect call through data slot RVA 0xF99FF98, read at every call exactly as the
// original does; never a static callee (rule 69).
//
// Layout constants (all offsets [V] from the disassembly of [0xed369b0, 0xed36a02)):
struct sub_ed369b0_this {   // object passed in RCX; only the field touched here is modeled
    void* vtable;           // +0x00 vtable pointer (0xed369c5 mov rax,[rcx])
};
static_assert(offsetof(sub_ed369b0_this, vtable) == 0x00, "sub_ed369b0: this->vtable at +0x00");

struct sub_ed369b0_vtable {  // vtable pointed at by this->vtable; only slot 3 (+0x18) is touched
    std::uint8_t pad0x00[0x18];
    void* target;            // +0x18 vtable[3]: tail-call target (0xed369ff jmp rax) and the
                             // 'this' argument of the data-slot call (0xed369d5 mov rcx,rbx)
};
static_assert(offsetof(sub_ed369b0_vtable, target) == 0x18, "sub_ed369b0: vtable[3] at +0x18");

// Image data read by the function (RVA; VA = imageBase() + RVA):
static constexpr std::uintptr_t kThunkSlotRva = 0xF99FF98;  // 0xed369d8 call qword ptr [0xF99FF98]

// std::uintptr_t sub_ed369b0(void* a0 /*rcx*/, void* a1 /*rdx*/, std::uint32_t a2 /*r8d*/)
// Return: pointer-sized; RAX of the tail-called vtable[3] propagates as-is (0xed369ff jmp rax).
// The return type of vtable[3] is dynamic and not determined statically by this function.
std::uintptr_t sub_ed369b0(void* a0, void* a1, std::uint32_t a2);

} // namespace native
