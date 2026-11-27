#pragma once
#include <cstddef>
#include <cstdint>

// sub_661a2f0 (0x661a2f0, size 0xce, 1.26.62.01, "BgfxFrameBuilder slot 30").
//
// Layout mirrors of the struct fields used by the function, with static_asserts for every
// offset the function reads or writes. All offsets [V] from the disassembly of
// [0x661a2f0, 0x661a3be).
//
// The function (exact x64 Microsoft ABI): RCX = a0 (Slot30*, u16 fields at +0x6EA/+0x6EC/+
// 0x6EE/+0x6F0), RDX = a1 (float[2], read at +0x0 and +0x4). Returns void.
//
// Each float is validated to be non-negative and exactly round-tripping through a u16
// ((float)(uint16_t)(int)value == value); on failure sub_eec6d80 (throw via data slot,
// noreturn) is called [V: 0x661a3ab call 0xEEC6D80]. On success the converted u16 is stored
// at a0+0x6EE (from a1[0]) and a0+0x6F0 (from a1[4]) [V: 0x661a336, 0x661a36b].
// The reads of a0+0x6EA (0x661a326) and a0+0x6EC (0x661a35f) feed a dead cmovb whose result
// is never read [V: 0x661a332, 0x661a368].
// Stack cookie via global [0x1230A0C0]; mismatch calls sub_e951550 (__report_gsfailure,
// noreturn, boundary crt) [V: 0x661a3b8 call 0xE951550]. No null guard or SEH (the original
// has none; none added here).
//
// Callees:
//   - sub_eec6d80 (lift set, already lifted): void sub_eec6d80(void*, u64, u64, u64), noreturn.
//   - sub_e951550 (boundary crt): native::Boundary<void, u64> sub_e951550("sub_e951550").

static constexpr std::size_t kSlot30Field0x6EA = 0x6EA;
static constexpr std::size_t kSlot30Field0x6EC = 0x6EC;
static constexpr std::size_t kSlot30Field0x6EE = 0x6EE;
static constexpr std::size_t kSlot30Field0x6F0 = 0x6F0;

struct Slot30 {
    std::uint8_t pad_0x0[0x6EA];
    std::uint16_t field_0x6EA;   // +0x6EA: R (clamp compare operand, dead cmovb) [V]
    std::uint16_t field_0x6EC;   // +0x6EC: R (u32 read, low16 used, dead cmovb) [V]
    std::uint16_t field_0x6EE;   // +0x6EE: W = (uint16_t)(int)a1[0] [V]
    std::uint16_t field_0x6F0;   // +0x6F0: W = (uint16_t)(int)a1[4] [V]
};                               // size 0x6F2

static_assert(offsetof(Slot30, field_0x6EA) == kSlot30Field0x6EA,
              "sub_661a2f0: Slot30+0x6EA read at 0x661a326");
static_assert(offsetof(Slot30, field_0x6EC) == kSlot30Field0x6EC,
              "sub_661a2f0: Slot30+0x6EC read at 0x661a35f");
static_assert(offsetof(Slot30, field_0x6EE) == kSlot30Field0x6EE,
              "sub_661a2f0: Slot30+0x6EE written at 0x661a336");
static_assert(offsetof(Slot30, field_0x6F0) == kSlot30Field0x6F0,
              "sub_661a2f0: Slot30+0x6F0 written at 0x661a36b");

namespace native {

// sub_661a2f0 (0x661a2f0, size 0xce, 1.26.62.01): exact x64 Microsoft ABI mirror of the
// original. RCX = a0 (Slot30*), RDX = a1 (float[2]). Returns void.
void sub_661a2f0(Slot30* a0, float* a1);

} // namespace native
