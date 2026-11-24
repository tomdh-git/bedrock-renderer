#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/bgfx/sub_bc55ea0.h"   // native::RefCounted [V]

namespace native {

// Layout recovered from the disassembly of 0xbc7c4e0 (size 0x95) and its caller
// 0xbc7ba60 (0xbc7bad9  lea rcx,[rsi+0x28] / 0xbc7badd  lea rdx,[rsi+0x40] /
// 0xbc7bae1  call 0xBC7C4E0): consecutive slots in the caller's array are 0x18
// bytes apart, and each slot is { raw +0x00, ref +0x08, flag +0x10 } [V].
//
// FrameSlot (passed by pointer in rcx/rdx):
//   +0x00 void* raw      copied between slots, never refcounted itself
//   +0x08 RefCounted* ref  addrefed when acquired, released when replaced
//   +0x10 uint8_t flag   0 = empty, 1 = sole owner, other = shared (role names inferred [I])
struct FrameSlot {
    void* raw;                                                 // +0x00
    RefCounted* ref;                                           // +0x08
    std::uint8_t flag;                                         // +0x10
};

static constexpr std::size_t kFrameSlotRawOffset = 0x00;
static constexpr std::size_t kFrameSlotRefOffset = 0x08;
static constexpr std::size_t kFrameSlotFlagOffset = 0x10;
static constexpr std::size_t kFrameSlotSize = 0x18;

static_assert(offsetof(FrameSlot, raw) == kFrameSlotRawOffset, "FrameSlot::raw must be at +0x00");
static_assert(offsetof(FrameSlot, ref) == kFrameSlotRefOffset, "FrameSlot::ref must be at +0x08");
static_assert(offsetof(FrameSlot, flag) == kFrameSlotFlagOffset, "FrameSlot::flag must be at +0x10");
static_assert(sizeof(FrameSlot) == kFrameSlotSize, "FrameSlot must be 0x18 bytes");

// Lifted function: 0xbc7c4e0, size 0x95, returns void.
// x64 Microsoft ABI: rcx = a0 (FrameSlot*), rdx = a1 (FrameSlot*).
extern "C" void sub_bc7c4e0(FrameSlot* a0, FrameSlot* a1);

} // namespace native
