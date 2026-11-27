#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Layout of the object passed to sub_4e69270 in rcx ('this'), reverse-engineered from the
// disassembly of [0x4e69270, 0x4e6935a), Minecraft Windows 1.26.62.01.
// 'this' is copied from rcx to rsi at 0x4e69276; every field access below uses rsi/this
// and is cited by the instruction(s) that touch it. Field names are derived decisions;
// offsets and access directions are [V] facts from the listing.

// Refcounted object, read at self+0x148 and self+0x1A8, and as the child of self+0x198.
//   +0x00  void*       vtable      R: 0x4e692af/0x4e692c4 (ref0x1a8), 0x4e692f1 (child),
//                                  0x4e69323/0x4e69338 (ref0x148)
//   +0x08  std::int32_t strong      R/W: lock dec 0x4e692a6/0x4e6931a (ref0x1a8/ref0x148)
//   +0x0C  std::int32_t weak        R/W: lock dec 0x4e692bb/0x4e692ec/0x4e6932f
//   vtable[0] (destructor) and vtable[8] (deallocator) are invoked with rcx = the object
//   through vendor thunk sub_eea6040 at data slot 0xF99FFA0:
//
//     0x4e692b5  call qword ptr [0xF99FFA0]   ; vtable[0](ref0x1a8)
//     0x4e692cb  call qword ptr [0xF99FFA0]   ; vtable[1](ref0x1a8)
//     0x4e692fb  call qword ptr [0xF99FFA0]   ; vtable[1](child)
//     0x4e69329  call qword ptr [0xF99FFA0]   ; vtable[0](ref0x148)
//     0x4e6933f  call qword ptr [0xF99FFA0]   ; vtable[1](ref0x148)
struct RefCounted {
    void* vtable;        // +0x00
    std::int32_t strong; // +0x08
    std::int32_t weak;   // +0x0C
};

// Object referenced by self+0x198. Only its relative +0x08 field is read
// (0x4e692df  mov rdx,[rcx+8] with rcx = self->link0x198), yielding the RefCounted*
// child0x08; the pointer itself is passed to sub_e935700 at 0x4e69309.
struct Link0x198 {
    std::uint8_t _pad_0x00[0x8];
    RefCounted* child0x08; // +0x08 relative to the object at self+0x198
};

struct sub_4e69270_state {
    std::uint8_t _pad_0x000[0x148];
    RefCounted* ref0x148;           // +0x148  R: 0x4e6930e `mov rdi,[rsi+0x148]`
    std::uint8_t _pad_0x150[0x198 - 0x150];
    Link0x198* link0x198;           // +0x198  R: 0x4e692d3 `mov rcx,[rsi+0x198]`
    std::uint8_t _pad_0x1a0[0x1a8 - 0x1a0];
    RefCounted* ref0x1a8;           // +0x1a8  R: 0x4e6929a `mov rdi,[rsi+0x1A8]`
    std::uint8_t caseSelector0x1b0; // +0x1b0  R: 0x4e69279 `movzx eax,byte ptr [rcx+0x1B0]`
};

static_assert(offsetof(RefCounted, vtable) == 0x00, "sub_4e69270: RefCounted::vtable at +0x00");
static_assert(offsetof(RefCounted, strong) == 0x08, "sub_4e69270: RefCounted::strong at +0x08");
static_assert(offsetof(RefCounted, weak) == 0x0C, "sub_4e69270: RefCounted::weak at +0x0C");
static_assert(offsetof(Link0x198, child0x08) == 0x08, "sub_4e69270: Link0x198::child0x08 at +0x08");
static_assert(offsetof(sub_4e69270_state, ref0x148) == 0x148, "sub_4e69270: ref0x148 at +0x148");
static_assert(offsetof(sub_4e69270_state, link0x198) == 0x198, "sub_4e69270: link0x198 at +0x198");
static_assert(offsetof(sub_4e69270_state, ref0x1a8) == 0x1a8, "sub_4e69270: ref0x1a8 at +0x1a8");
static_assert(offsetof(sub_4e69270_state, caseSelector0x1b0) == 0x1b0, "sub_4e69270: caseSelector0x1b0 at +0x1b0");
static_assert(sizeof(void*) == 8, "sub_4e69270: x64 ABI, pointer-sized address space");

// sub_e935700 (0xE935700): lift-set callee, tail jump to sub_392960. Reads RCX only; the
// RDX=0x20 store at 0x4e69304 is dead on entry to sub_392960 (`0x392972 mov rdx,rcx`).
// Return value in RAX is ignored by this function. Called through its native symbol.
namespace native {
void* sub_e935700(void* a0);
}

// 0x4e69355  jmp 0x4E3B020: tail call; argument is this+0xE0 in RCX, return value in RAX
// returned by this function as-is. Not in the lift set; forward-declared as an external
// native symbol.
extern "C" uintptr_t sub_4e3b020(sub_4e69270_state* next);

// x64 Microsoft ABI: arg1 (RCX) = this pointer; return value (RAX) =
// sub_4e3b020(this + 0xE0)'s result (tail call).
uintptr_t sub_4e69270(sub_4e69270_state* self);

} // namespace native::helpers
