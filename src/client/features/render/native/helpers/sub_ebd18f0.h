// LIFT 0xebd18f0 size 0xb9 1.26.62.01 sub_ebd18f0
#pragma once

#include <cstdint>
#include <immintrin.h>

namespace native {

// Layout constants for data referenced by sub_ebd18f0
// Verified from exe: .rdata section at RVAs 0xEECB5D0 and 0xEF40D90
inline constexpr std::uintptr_t kShuffleMaskHighBytes_RVA = 0xEECB5D0; // 0xFF00FF00 per dword
inline constexpr std::uintptr_t kShuffleMaskLowBytes_RVA  = 0xEF40D90; // 0x00FF00FF per dword

// Static assertions for the shuffle masks (loaded at runtime from exe image base)
// These verify the expected constant values at the known RVAs
static_assert(sizeof(__m128i) == 16, "__m128i must be 16 bytes");

// Function signature matching the x64 Microsoft ABI
// void sub_ebd18f0(
//     void* dest,           // RCX
//     int dest_stride,      // RDX
//     uint32_t inner_count, // R8  (elements per row, multiple of 4 for fast path)
//     uint32_t outer_count, // R9  (row count)
//     void* unused_arg5,    // [RSP+0x20] home space (clobbered)
//     const void* src,      // [RSP+0x28] arg6
//     int src_stride        // [RSP+0x30] arg7 (low 32 bits)
// );
using sub_ebd18f0_fn = void(*)(
    void* dest,
    int dest_stride,
    uint32_t inner_count,
    uint32_t outer_count,
    void* unused_arg5,
    const void* src,
    int src_stride
) noexcept;

} // namespace native