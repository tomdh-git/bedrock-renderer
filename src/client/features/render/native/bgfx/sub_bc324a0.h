#pragma once
#include <cstdint>
#include <cstddef>

namespace native {

struct ChunkState {
    // rbp frame base (rsp+0x80); locals documented in docs/functions/bc324a0.md
    std::uint8_t* frame = nullptr;
};

// Layout constants for sub_bc324a0 frame (rbp-relative offsets)
static constexpr std::size_t kFrameSize = 0xC98;
static constexpr std::size_t kThisOff = 0xB28;   // [rbp+0xB28] this/obj (rcx in)
static constexpr std::size_t kR8dOff = 0xBAC;    // [rbp+0xBAC] r8d in
static constexpr std::size_t kR9Off = 0xB48;     // [rbp+0xB48] r9+8
static constexpr std::size_t kA1Off = 0xBC0;     // [rbp+0xBC0] a1 (rdx in)
static constexpr std::size_t kA1_18 = 0xB40;     // [rbp+0xB40] a1+0x18
static constexpr std::size_t kA1_28 = 0xB30;     // [rbp+0xB30] a1+0x28
static constexpr std::size_t kA1_60 = 0xB38;     // [rbp+0xB38] a1+0x60

static_assert(kThisOff == 0xB28, "this offset");
static_assert(kR8dOff == 0xBAC, "r8d offset");
static_assert(kR9Off == 0xB48, "r9 offset");
static_assert(kA1Off == 0xBC0, "a1 offset");
static_assert(kA1_18 == 0xB40, "a1+0x18 offset");
static_assert(kA1_28 == 0xB30, "a1+0x28 offset");
static_assert(kA1_60 == 0xB38, "a1+0x60 offset");

} // namespace native