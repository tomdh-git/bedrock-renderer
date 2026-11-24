// LIFT 0xebdbf10 size 0x7 1.26.62.01 sub_ebdbf10
#include "sub_ebdbf10.h"

#include "client/features/render/native/Lift.h"

namespace native {

// sub_ebdbf10 (0xebdbf10, size 0x7, 1.26.62.01).
//
// The body is exactly one instruction, an indirect tail jump through the
// loader-resolved data slot 0xF9A7B10:
//
//   0xebdbf10  jmp qword ptr [0xF9A7B10]   ; [data_f9a7b10]   (0xebdbf10..0xebdbf16)
//
// It reads no struct field, writes no memory and executes no call of its own:
// the single argument arrives in RCX (callers pass &ctx->lock at ctx+0x1C0
// [V: sub_bc70ca0.h, sub_bc66c50.h, bc66c50.md, bc71da0.md]) and the result
// leaves in RAX exactly as the slot target leaves it (return unused by callers).
// The int3 at 0xebdbf17 is padding past the 7-byte function span [V: rdis dis].
//
// Verbatim instruction of the function (matches the rdis output for 0xebdbf10):
#if 0
0xebdbf10  jmp qword ptr [0xF9A7B10]                     ; [data_f9a7b10]
#endif

void sub_ebdbf10(void* lock) {
    static_assert(sizeof(void*) == 8, "sub_ebdbf10: x64 ABI, pointer-sized argument in RCX and result in RAX");
    // 0xebdbf10..0xebdbf17:  jmp qword ptr [0xF9A7B10]   ; tail jump through loader-resolved data slot 0xF9A7B10
    using Fn = void (*)(void*);
    return reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A7B10ull))(lock);   // 0xebdbf10  jmp qword ptr [0xF9A7B10]   ; 8-byte load from the slot, tail jump, RAX result as-is
}

} // namespace native

LIFT_FN(sub_ebdbf10, "sub_ebdbf10", 0xEBDbf10, sub_ebdbf10, nullptr);
