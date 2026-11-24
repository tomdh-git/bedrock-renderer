#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_e935700 (0xe935700, size 0x5, 1.26.62.01): a tail jump to sub_392960.
// Layout constants: the function reads no struct fields and writes no memory,
// so there are no struct offsets to assert. The ABI contract is asserted below.
struct sub_e935700Layout {
    static_assert(sizeof(void*) == 8, "sub_e935700: pointer-sized argument and return value (x64)");
    static_assert(sizeof(sub_e935700Layout) > 0, "layout constant block");
};

namespace native {

// sub_392960 (docs/data/native_functions.tsv: 0x392960 size 0x35; boundary row class 'lift').
// Lift-set callee, forward-declared here and called by the lifted body of sub_e935700
// (brief rule: a lift callee is called through its native symbol, never a boundary wrapper).
// ABI recovered from its disassembly:
//   0x392972 mov rdx,rcx     ; the single input argument arrives in RCX
//   0x39297c test rdx,rdx    ; null-checked by the callee
//   0x392988 call qword ptr [0xF99FFA0]   ; vendor thunk via data slot 0xF99FFA0
//   0x392994 ret             ; result returned in RAX
// No other input register and no stack argument is read by sub_392960 itself.
void* sub_392960(void* a0);

// sub_e935700: tail jump to sub_392960; same ABI (argument forwarded in RCX, result in RAX).
void* sub_e935700(void* a0);

} // namespace native
