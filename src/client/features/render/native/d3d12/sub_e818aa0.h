#pragma once
#include <cstddef>
#include <cstdint>

namespace native::d3d12 {

// LIFT 0xe818aa0 size 0xcf 1.26.62.01 RendererContextD3D12 ring-buffer clear-by-value
//
// this = RendererContextD3D12* (rcx). Arg is a 16-bit value (edx, used as r8w).
// Inside `this` there is a ring buffer of uint16_t slots and its index bookkeeping:
//   slot array : base this+0x7CC0, cap slots, stride 2 bytes (uint16_t)
//   capacity   : uint32 at this+0x7EC8  (divisor / modulus of every div)
//   tail index : uint32 at this+0x7ECC
//   head index : uint32 at this+0x7ED4  (base index of the live range)
// Live element count = (tail - head), normalized to non-negative by +cap when it
// was negative. The function walks [head, head+count) mod cap, two slots per turn,
// and overwrites with 0xFFFF every slot whose current uint16 equals the argument.
constexpr std::size_t kRingSlotArrayOff = 0x7CC0; // ring-buffer slot array base
constexpr std::size_t kRingCapacityOff  = 0x7EC8; // capacity / divisor
constexpr std::size_t kRingTailOff      = 0x7ECC; // tail index
constexpr std::size_t kRingHeadOff      = 0x7ED4; // head (base) index
constexpr std::uint16_t kRingClearedVal = 0xFFFF; // value written into a matching slot
constexpr std::uint32_t kRingModMask    = 0xFFFFFFFEu; // mask used to round count down to even

static_assert(kRingCapacityOff - kRingSlotArrayOff == 0x208, "slot-array to capacity gap");
static_assert(kRingTailOff     - kRingCapacityOff  == 0x4,   "capacity to tail gap");
static_assert(kRingHeadOff     - kRingTailOff      == 0x8,   "tail to head gap");
static_assert(kRingClearedVal  == 0xFFFFu, "cleared sentinel value");
static_assert(sizeof(std::uint16_t) == 2, "slot is uint16_t (2 bytes)");

// sub_0xe818aa0: clear (set to 0xFFFF) every ring-buffer slot in [head, tail) whose
// uint16 value equals the argument. rcx = this, edx = value. Returns void.
void sub_e818aa0(void* a0, unsigned short a1);

} // namespace native::d3d12