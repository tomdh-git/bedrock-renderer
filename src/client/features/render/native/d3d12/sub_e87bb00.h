#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the object on which 0xe87bb00 (BgfxFrameBuilder::endFrame, size 0x1ac) operates.
// Every offset below is read or written by that function at the stated offset [V] (disassembly
// range [0xe87bb00, 0xe87bcac)). Field roles describe the access pattern observed in the
// disassembly; they are not proven type information.
//
// Observed fields:
//   +0x40 rdi = first entry pointer (array of 0x88-byte entries)
//   +0x48 rbx = one-past-last entry pointer
struct EndFrameObject {
    std::uint8_t pad40[0x40];   // +0x00 .. +0x3f
    void*        first;         // +0x40 rdi
    void*        last;          // +0x48 rbx
};

// Layout constants for the offsets used by 0xe87bb00 [V]:
static constexpr std::size_t kEndFrameFirstOffset = 0x40; // mov rdi,[rcx+0x40]
static constexpr std::size_t kEndFrameLastOffset  = 0x48; // mov rbx,[rcx+0x48]

static_assert(kEndFrameLastOffset - kEndFrameFirstOffset == 0x08,
              "e87bb00: last follows first at +0x48");

// 0xe935700 (size 0x5): `jmp 0x392960` forwarder. Classified lift in
// docs/data/native_boundary.tsv (class lift, auto-unresolved->lift). Called at
// 0xe87bba4, 0xe87bbbd and 0xe87bbea with rcx/rdx set per path; return value unused.
// Forward-declared per the lift rules: called like any lifted function, no boundary wrapper.
extern "C" void sub_e935700(void* a1, std::uintptr_t a2);

// Import slot [0xF9A8C78] called indirectly at 0xe87bc92: `call qword ptr [0xF9A8C78]`.
// Per the indirect-call hard rule: read the pointer from the slot at call time and call it as
// a function pointer with the same arguments (rcx=0, rdx=0, r8=0, r9=0).
static constexpr std::uintptr_t kFailSlotAddr = 0xF9A8C78; // [data_f9a8c78]

// 0x1f5ef50: stl boundary (docs/data/native_boundary.tsv, class stl). Called at 0xe87bbdc with
// rcx=&node->link, rdx=&node->link, r8=node->forward. Return value unused. Called through a
// native::Boundary<> wrapper resolving the address from Sigs.json.

} // namespace native
