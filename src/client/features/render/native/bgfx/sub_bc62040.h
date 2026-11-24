#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xbc62040 (size 0xb72, 1.26.62.01).
// Every offset below is an instruction [reg+off] / immediate seen in the listing [V].

// Frame layout (frame base = [rsp+0x20] after the probe sub rsp):
//   +0x0000  u32 counters[2048]   radix counting bins (cleared per pass with a 0x2000-byte memset)
//   +0x2000  u64 cookie           stack cookie ([0x1230A0C0] ^ rsp)
// The cookie slot is addressed directly as [rsp+0x2020] in the listing; the frame above
// describes the counters + cookie portion only (the 0x20 bytes before counters are scratch).
struct Bc62040Frame {
    std::uint32_t counters[2048];  // +0x0000..0x1FFF
    std::uint64_t  cookie;         // +0x2000
};
static_assert(offsetof(Bc62040Frame, counters) == 0x0000u, "bc62040: counters at +0x0000");
static_assert(offsetof(Bc62040Frame, cookie) == 0x2000u, "bc62040: cookie at +0x2000");
static_assert(sizeof(Bc62040Frame) == 0x2008u, "bc62040: counters+cookie size");

// Read-only data addresses referenced by the function [V].
static constexpr std::uintptr_t kGblCookie = 0x1230A0C0u;  // stack cookie global ([0x1230A0C0])

// Loop/frame constants [V].
static constexpr std::uint32_t kCounterBins = 0x800u;   // 2048 u32 counters
static constexpr std::uint32_t kCounterBytes = 0x2000u; // 0x2000-byte memset per pass
static constexpr std::uint32_t kStackSize = 0x2028u;    // probe request size (mov eax,0x2028)

// Digit selectors per pass [V].
//   A: key & 0x7FF                    keys -> workKeys,  words -> workWords
//   B: (key >> 9) & 0x1FFC            workKeys -> keys,  workWords -> words   (byte-offset bins)
//   C: (key >> 22) & 0x7FF            keys -> workKeys
//   D: (key >> 33) & 0x7FF            workKeys -> keys
//   E: (key >> 44) & 0x7FF            keys -> workKeys
//   F: key >> 55                      workKeys -> keys   (0..0xFF bins, no mask)
static constexpr std::uint32_t kMaskA = 0x7FFu;
static constexpr std::uint32_t kMaskB = 0x1FFCu;
static constexpr std::uint32_t kMaskC = 0x7FFu;
static constexpr std::uint32_t kMaskD = 0x7FFu;
static constexpr std::uint32_t kMaskE = 0x7FFu;
static constexpr std::uint8_t    kShiftF = 55u;

// x64 Microsoft ABI: rcx = keys, rdx = workKeys, r8 = words, r9 = workWords,
// 5th stack arg = count. Return: void.
extern "C" void sub_bc62040(std::uint64_t* keys, std::uint64_t* workKeys,
                            std::uint16_t* words, std::uint16_t* workWords,
                            std::uint32_t count);

// Footprint: every region the function (and the library calls it makes) writes.
native::Footprint sub_bc62040_footprint(std::uint64_t* keys, std::uint64_t* workKeys,
                                        std::uint16_t* words, std::uint16_t* workWords,
                                        std::uint32_t count);

} // namespace native
