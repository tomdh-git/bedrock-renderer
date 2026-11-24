#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/bgfx/sub_bc55ea0.h"   // ::native::RefCounted [V]

namespace native {

// sub_e935700 (0xe935700, size 0x5 = `jmp 0x392960`): classified `lift` in
// docs/data/native_boundary.tsv. Forward-declared here and called through its native
// symbol by sub_bc7dc90; its own lift unit provides the definition at the milestone gate.
// Body: sub_392960 = mov rdx,rcx; rcx = *(uintptr_t*)0x15233E1A8; test rdx,rdx; je return;
// rax = global->vtable[2] reached through the [0xF99FFA0] `jmp rax` thunk; call rax(global).
// The entry rdx (second argument) is overwritten before sub_392960 reads it, so it is dead
// in the callee; the call site passes it anyway to mirror the instruction exactly.
// Return value: rax from sub_392960; never observed by sub_bc7dc90.
extern "C" uintptr_t sub_e935700(std::uint64_t x, std::uint64_t arg2);

} // namespace native

namespace native::bgfx {

// Layout recovered from the disassembly of 0xbc7dc90 (size 0x13e). Every offset below is
// read or written by that function [V]; role names are inferred from the access pattern.
// The function clears two small strings ({buffer, size, capacity} at +0x00/+0x10/+0x18 and
// +0xC8/+0xD8/+0xE0, SSO threshold: capacity < 0x10), releases the single-owner object at
// +0xB8 through vtable[4] (offset 0x20), and releases the RefCounted at +0x28
// (strong +0x08, weak +0x0C; vtable[0] destroy, vtable[8] dealloc — same layout as
// ::native::RefCounted). It also compares the +0xB8 pointer with &this+0x80; the
// comparison result is never read. Extent observed in this function: 0xE8 bytes.
struct BuilderState {
    void* buf1;                          // +0x00 small string 1: buffer pointer
    std::uint8_t pad0[8];                // +0x08
    std::uint64_t size1;                 // +0x10 small string 1: size
    std::uint64_t cap1;                  // +0x18 small string 1: capacity
    std::uint8_t pad1[8];                // +0x20
    ::native::RefCounted* strongRef;     // +0x28 strong-refcounted object
    std::uint8_t pad2[0x88];             // +0x30
    void* weakRef;                       // +0xB8 single-owner object; destroyed via vtable[4] (offset 0x20)
                                         //        compared against &this+0x80 by the original (result dead)
    std::uint8_t pad3[8];                // +0xC0
    void* buf2;                          // +0xC8 small string 2: buffer pointer
    std::uint8_t pad4[8];                // +0xD0
    std::uint64_t size2;                 // +0xD8 small string 2: size
    std::uint64_t cap2;                  // +0xE0 small string 2: capacity
};                                       // sizeof == 0xE8

static constexpr std::size_t kBuilderStateBuf1Offset = 0x00;
static constexpr std::size_t kBuilderStateSize1Offset = 0x10;
static constexpr std::size_t kBuilderStateCap1Offset = 0x18;
static constexpr std::size_t kBuilderStateStrongRefOffset = 0x28;
static constexpr std::size_t kBuilderStateWeakRefOffset = 0xB8;
static constexpr std::size_t kBuilderStateBuf2Offset = 0xC8;
static constexpr std::size_t kBuilderStateSize2Offset = 0xD8;
static constexpr std::size_t kBuilderStateCap2Offset = 0xE0;
static constexpr std::size_t kBuilderStateSize = 0xE8;

static_assert(offsetof(BuilderState, buf1) == kBuilderStateBuf1Offset, "BuilderState::buf1 must be at +0x00");
static_assert(offsetof(BuilderState, size1) == kBuilderStateSize1Offset, "BuilderState::size1 must be at +0x10");
static_assert(offsetof(BuilderState, cap1) == kBuilderStateCap1Offset, "BuilderState::cap1 must be at +0x18");
static_assert(offsetof(BuilderState, strongRef) == kBuilderStateStrongRefOffset, "BuilderState::strongRef must be at +0x28");
static_assert(offsetof(BuilderState, weakRef) == kBuilderStateWeakRefOffset, "BuilderState::weakRef must be at +0xB8");
static_assert(offsetof(BuilderState, buf2) == kBuilderStateBuf2Offset, "BuilderState::buf2 must be at +0xC8");
static_assert(offsetof(BuilderState, size2) == kBuilderStateSize2Offset, "BuilderState::size2 must be at +0xD8");
static_assert(offsetof(BuilderState, cap2) == kBuilderStateCap2Offset, "BuilderState::cap2 must be at +0xE0");
static_assert(sizeof(BuilderState) == kBuilderStateSize, "BuilderState must be 0xE8 bytes");

// Lifted function: 0xbc7dc90, size 0x13e, returns void.
// x64 Microsoft ABI: rcx = a0 (BuilderState*).
extern "C" void sub_bc7dc90(BuilderState* a0);

} // namespace native::bgfx
