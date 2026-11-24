// LIFT 0xebdbf20 size 0x7 1.26.62.01 sub_ebdbf20
#include "sub_ebdbf20.h"

#include "client/features/render/native/Lift.h"

namespace native {

// sub_ebdbf20 (0xebdbf20, size 0x7, 1.26.62.01).
//
// The body is exactly one instruction, an indirect tail jump through the
// loader-resolved data slot 0xF9A7B28:
//
//   0xebdbf20  jmp qword ptr [0xF9A7B28]   ; [data_f9a7b28]   (0xebdbf20..0xebdbf27)
//
// It reads no struct field, writes no memory and executes no call of its own:
// the single argument arrives in RCX (a caller-supplied pointer) and the result
// leaves in RAX exactly as the slot target leaves it (return unused by callers).
// The int3 bytes at 0xebdbf27..0xebdbf2f are padding past the 7-byte function
// span [V: rdis dis].
//
// Verbatim instruction of the function (matches the rdis output for 0xebdbf20):
#if 0
0xebdbf20  jmp qword ptr [0xF9A7B28]                     ; [data_f9a7b28]
#endif

void sub_ebdbf20(void* a0) {
    static_assert(sizeof(void*) == 8, "sub_ebdbf20: x64 ABI, pointer-sized argument in RCX and result in RAX");
    // 0xebdbf20..0xebdbf27:  jmp qword ptr [0xF9A7B28]   ; tail jump through loader-resolved data slot 0xF9A7B28
    using Fn = void (*)(void*);
    return reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A7B28ull))(a0);   // 0xebdbf20  jmp qword ptr [0xF9A7B28]   ; 8-byte load from the slot, tail jump, RAX result as-is
}

} // namespace native

LIFT_FN(sub_ebdbf20, "sub_ebdbf20", 0xebdbf20, sub_ebdbf20, nullptr);
