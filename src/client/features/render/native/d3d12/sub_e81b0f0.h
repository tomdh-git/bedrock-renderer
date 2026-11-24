#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xe81b0f0 (size 0x14b, 1.26.62.01).
// RendererContextD3D12 base slot 62: flush the queue of pending frame objects.
// The function (this = rcx) does, in order:
//   1. a guarded virtual call this->vtable[0x1E8](this, 0)            (0xe81b119),
//   2. if this->pendingCount (0x3C55288) != 0: walk pendingCount elements from
//      srcArray (0x3C54A08), push each through a 0x110-entry ring (head 0x3C55B18,
//      tail 0x3C55B10) into dstArray (0x3C55290), stamp two fields into each
//      element (0x2CBD0 <- valueObj->[0x28], 0x2CBD8 <- byte 1), advance to the
//      element's next (0x30) and collect those next-pointers on the stack, then a
//      guarded virtual call flushObj->vtable[0x50](flushObj, count, &nextPtrs)
//      (0xe81b1f9) where flushObj = this->[0xCC9268], and finally reset
//      this->pendingCount = 0 (0xe81b1ff),
//   3. the /GS epilogue (cookie check -> sub_e951550 on mismatch).
// Every offset below is an instruction [reg+off] seen in the listing [V].

// this (RendererContextD3D12) fields touched by the function [V]:
static constexpr std::size_t kPendingCount  = 0x3C55288; // u64  pending element count (R 0xe81b11f, W 0 at 0xe81b1ff)
static constexpr std::size_t kSrcArray      = 0x3C54A08; // u64[] source element pointers (R 0xe81b18d)
static constexpr std::size_t kRingTail      = 0x3C55B10; // u64  ring tail index        (R/W)
static constexpr std::size_t kRingHead      = 0x3C55B18; // u64  ring head index        (R/W)
static constexpr std::size_t kDstArray      = 0x3C55290; // u64[] ring destination slot pointers (W 0xe81b156)
static constexpr std::size_t kValueObj      = 0x3C563B0; // void* object whose +0x28 is stamped into each element (R 0xe81b15e)
static constexpr std::size_t kFlushObj      = 0xCC9268;  // void* object whose vtable[0x50] is called (R 0xe81b1e6)

static_assert(kRingHead - kRingTail   == 0x8, "e81b0f0: head immediately follows tail");
static_assert(kDstArray < kPendingCount && kPendingCount < kSrcArray, "e81b0f0: field order");

// Ring capacity: indices wrap to 0 at this value (cmp r10,0x110 / cmovne) [V].
static constexpr std::uint64_t kRingCapacity = 0x110; // 272 entries

// Per-element (the objects stored in srcArray) offsets [V]:
static constexpr std::size_t kElemStateWord = 0x2CBD0; // u64 written from valueObj->[0x28] (0xe81b169)
static constexpr std::size_t kElemReadyFlag = 0x2CBD8; // u8  set to 1                            (0xe81b170)
static constexpr std::size_t kElemNext      = 0x30;    // u64 next-element pointer               (0xe81b178)
static_assert(kElemReadyFlag - kElemStateWord == 0x8, "e81b0f0: state word then ready flag");
static_assert(kElemNext < kElemStateWord, "e81b0f0: next pointer precedes state word");

// valueObj field read and stamped into each element [V].
static constexpr std::size_t kValueObjField = 0x28; // *(valueObj + 0x28) (0xe81b165)

// Guarded (CFG) virtual-call vtable byte offsets; slot index = offset / 8 [V].
static constexpr std::size_t kVslotBegin = 0x1E8; // this->vtable[0x1E8](this, 0)        (0xe81b110)
static constexpr std::size_t kVslotFlush = 0x50;  // flushObj->vtable[0x50](flushObj,...) (0xe81b1f0)
static_assert(kVslotBegin / 8 == 0x3D, "e81b0f0: begin slot index 61");
static_assert(kVslotFlush / 8 == 0x0A, "e81b0f0: flush slot index 10");

// Read-only globals [V].
static constexpr std::uintptr_t kGblCookie = 0x1230A0C0u; // mov rcx,[0x1230A0C0]    (/GS stack cookie)
static constexpr std::uintptr_t kGuardSlot = 0xF99FFA0u;  // call qword ptr [0xF99FFA0] (sub_eea6040 = jmp rax thunk)

// x64 Microsoft ABI: rcx = this (RendererContextD3D12*). No other arguments are read
// before being set internally. Return: void (rax is only the /GS cookie at the ret) [V].
extern "C" void sub_e81b0f0(void* a0);

} // namespace native