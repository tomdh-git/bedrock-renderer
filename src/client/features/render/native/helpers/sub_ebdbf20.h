#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_ebdbf20 (0xebdbf20, size 0x7, 1.26.62.01): indirect tail jump through the
// loader-resolved data slot 0xF9A7B28 (`jmp qword ptr [0xF9A7B28]`).
// Layout constants: the function reads no struct fields and writes no memory,
// so there are no struct offsets to assert; only the x64 ABI contract is
// asserted below [V: rdis dis/sum for 0xebdbf20, one 8-byte read at &data_f9a7b28].
struct sub_ebdbf20Layout {
    static_assert(sizeof(void*) == 8, "sub_ebdbf20: x64 ABI, pointer-sized argument in RCX and result in RAX");
    static_assert(sizeof(sub_ebdbf20Layout) > 0, "sub_ebdbf20: layout constant block");
};

namespace native {

// sub_ebdbf20: tail jump through data slot 0xF9A7B28; the single argument
// arrives in RCX (a caller-supplied pointer) and the result leaves in RAX exactly
// as the slot target leaves it (return unused by callers).
void sub_ebdbf20(void* a0);

} // namespace native
