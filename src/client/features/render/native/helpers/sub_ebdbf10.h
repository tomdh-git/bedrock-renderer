#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_ebdbf10 (0xebdbf10, size 0x7, 1.26.62.01): indirect tail jump through the
// loader-resolved data slot 0xF9A7B10 (`jmp qword ptr [0xF9A7B10]`).
// Layout constants: the function reads no struct fields and writes no memory,
// so there are no struct offsets to assert; only the x64 ABI contract is
// asserted below [V: rdis dis/sum for 0xebdbf10, one 8-byte read at &data_f9a7b10].
struct sub_ebdbf10Layout {
    static_assert(sizeof(void*) == 8, "sub_ebdbf10: x64 ABI, pointer-sized argument in RCX and result in RAX");
    static_assert(sizeof(sub_ebdbf10Layout) > 0, "sub_ebdbf10: layout constant block");
};

namespace native {

// sub_ebdbf10: tail jump through data slot 0xF9A7B10; the single argument
// arrives in RCX (callers pass &ctx->lock at ctx+0x1C0 [V: sub_bc70ca0.h,
// sub_bc66c50.h, bc66c50.md, bc71da0.md]) and the result leaves in RAX exactly
// as the slot target leaves it (return unused by callers).
void sub_ebdbf10(void* lock);

} // namespace native
