#pragma once
#include <cstddef>
#include <cstdint>

// sub_53d5c20 (0x53d5c20, size 0xab, 1.26.62.01): copies 16 floats from a1 to a0,
// guarded by the flag byte at a0+0x40. Full reversal in sub_53d5c20.cpp.
// Layout derived from the disassembly [V: rdis dis 0x53d5c20 0xab]:
//   a0: float v[16] at +0x00..0x3C (movss stores 0x53d5c28..0x53d5cc5),
//       std::uint8_t flag at +0x40 (movzx byte read 0x53d5c20)
//   a1: float v[16] at +0x00..0x3C (movss loads 0x53d5c24..0x53d5cc0)
//   return: void (ret at 0x53d5cca, no return value)
// x64 Microsoft ABI: RCX = a0, RDX = a1.

struct Sub53d5c20Arg {
    float v[16];         // +0x00..0x3C  16 floats copied by sub_53d5c20
    std::uint8_t flag;   // +0x40        flag byte read at 0x53d5c20
};
static_assert(offsetof(Sub53d5c20Arg, v) == 0x00, "sub_53d5c20: v at +0x00");
static_assert(offsetof(Sub53d5c20Arg, flag) == 0x40, "sub_53d5c20: flag at +0x40");
static_assert(sizeof(Sub53d5c20Arg) == 0x44, "sub_53d5c20: object size 0x44");

namespace native {

// Signature of sub_53d5c20: RCX = a0, RDX = a1, return void [V: rdis dis 0x53d5c20 0xab].
void sub_53d5c20(Sub53d5c20Arg* a0, const Sub53d5c20Arg* a1);

} // namespace native
