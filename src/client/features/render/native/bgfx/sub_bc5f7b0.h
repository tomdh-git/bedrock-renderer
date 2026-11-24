#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xbc5f7b0 (size 0x11e, 1.26.62.01).
// The function uses a raw stack frame (sub rsp,0x50) and one pointer argument;
// it touches no game struct: all reads/writes are [rcx+0x0] (the *a0 pointer),
// raw [rsp+off] stack slots, and the stack-cookie global [0x1230A0C0] [V].
//
// Pair: 16-byte { ptr, len } string descriptor. pairB is built at [rsp+0x20],
// pairA at [rsp+0x30]; both are passed by reference to the call at 0xbc5f854
// (rcx = &pairB, rdx = &pairA, r8d = 2) [V].
struct Pair {
    std::uintptr_t ptr;      // +0x00  string pointer
    std::uint32_t  len;      // +0x08  length returned by 0xEBCE5E0 in eax
    std::uint8_t   pad0c[4]; // +0x0C  never read by the function
};
static_assert(offsetof(Pair, ptr) == 0x00, "bc5f7b0: Pair::ptr at +0x00");
static_assert(offsetof(Pair, len) == 0x08, "bc5f7b0: Pair::len at +0x08");
static_assert(sizeof(Pair) == 0x10, "bc5f7b0: Pair must be 0x10 bytes");

// rsp-relative stack-frame slots of sub 0xbc5f7b0 (after `sub rsp,0x50`) [V].
static constexpr std::uint32_t kBc5f7b0PairBOffset = 0x20; // pairB, [rsp+0x20]/[rsp+0x28]
static constexpr std::uint32_t kBc5f7b0PairAOffset = 0x30; // pairA, [rsp+0x30]/[rsp+0x38]
static constexpr std::uint32_t kBc5f7b0SavedPtrOffset = 0x40; // savedPtr, [rsp+0x40]
static constexpr std::uint32_t kBc5f7b0CookieOffset = 0x48; // cookie slot, [rsp+0x48]
static constexpr std::uint32_t kBc5f7b0FrameSize = 0x50;    // sub rsp,0x50
static_assert(kBc5f7b0PairBOffset == 0x20, "bc5f7b0: pairB at rsp+0x20");
static_assert(kBc5f7b0PairAOffset == 0x30, "bc5f7b0: pairA at rsp+0x30");
static_assert(kBc5f7b0SavedPtrOffset == 0x40, "bc5f7b0: savedPtr at rsp+0x40");
static_assert(kBc5f7b0CookieOffset == 0x48, "bc5f7b0: cookie slot at rsp+0x48");
static_assert(kBc5f7b0FrameSize == 0x50, "bc5f7b0: frame size 0x50");

// sub 0xbc5f7b0: D3D12 submit RTX override.
// x64 Microsoft ABI: rcx = a0 (uintptr_t*: [rcx+0x0] read and written),
// edx = arg (uint32_t, carried in ebx), return eax = ebx (uint32_t) [V].
extern "C" std::uint32_t sub_bc5f7b0(std::uintptr_t* a0, std::uint32_t arg);

// Native symbol of the lifted callee 0xbc76380 (CALLEES list, X1.bc76380;
// its definition lives in src/client/features/render/native/bgfx/sub_bc76380.cpp).
// Call sites of 0xbc5f7b0: rcx = &savedPtr, rdx = ch (';' at 0xbc5f86e, 'm' at
// 0xbc5f880; the callee reads the low byte only [V]), r8d = depth, r9 is never
// read by the callee [V]. eax is consumed after both calls
// (0xbc5f873 mov ebp,eax; 0xbc5f885 mov ebx,eax; 0xbc5f8af mov eax,ebx), so the
// return type is uint32_t [V].
extern "C" std::uint32_t Bc76380_lifted(std::uint64_t* slot, std::uint64_t counter,
                                        std::uint32_t depth, std::uint32_t flags);

} // namespace native
