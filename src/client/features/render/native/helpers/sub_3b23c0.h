#pragma once
#include <cstdint>

#include "client/features/render/native/Lift.h"
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_3b23c0 (0x3b23c0, size 0x8, 1.26.62.01): returns the address of the qword global data_128CC490 in RAX.
//   0x3b23c0  lea rax,[0x128CC490]   ; RAX = &data_128cc490
//   0x3b23c7  ret
// Reads: no memory operand (loads the immediate address of data_128CC490). Writes: nothing.
// Calls: none. x64 Microsoft ABI: no arguments, return value in RAX = &data_128cc490 (std::uint64_t*).
// The caller at 0xeea5f69 does `or qword ptr [rax],2`, confirming the pointee is a 64-bit value. [V]

struct sub_3b23c0Layout {
    static_assert(sizeof(std::uint64_t*) == 8, "sub_3b23c0: x64 pointer-sized return value");
    static constexpr std::uintptr_t kGlobalDataRva = 0x128CC490; // image RVA of data_128cc490 (returned pointer target)
    static_assert(kGlobalDataRva == 0x128CC490, "sub_3b23c0: data_128cc490 at image RVA 0x128CC490");
};

namespace native {

// sub_3b23c0 (0x3b23c0, 0x8 bytes, 1.26.62.01): argument-free, returns &data_128cc490 in RAX.
// See the instruction block above for the instruction-by-instruction reversal.
std::uint64_t* sub_3b23c0(void);

} // namespace native
