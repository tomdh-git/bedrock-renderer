// LIFT 0xe943170 size 0x7 1.26.62.01 sub_e943170
#include "sub_e943170.h"

#include "client/features/render/native/Lift.h"

namespace native {

// sub_e943170 (0xe943170, size 0x7, 1.26.62.01).
//
// The body is exactly one instruction, an indirect tail jump through the
// loader-resolved data slot 0xF9A7AF0:
//
//   0xe943170  jmp qword ptr [0xF9A7AF0]   ; [data_f9a7af0]   (0xe943170..0xe943177)
//
// It reads no struct field, writes no memory of its own and executes no call
// instruction of its own: the single argument arrives in RCX (a caller-supplied
// SRWLOCK pointer) and the result leaves in RAX exactly as the slot target leaves
// it. 0xe943177 is the next instruction after the 7-byte function span [V: rdis dis].
// The slot value is loader-resolved (peimports.py: [0xF9A7AF0] = AcquireSRWLockExclusive
// [V]); the lifted code reads the 8-byte pointer from the slot at call time and
// tail-calls it as a function pointer, exactly as the jmp does [rule 68 slot-indirect call].
//
// Verbatim instruction of the function (matches the rdis output for 0xe943170):
#if 0
0xe943170  jmp qword ptr [0xF9A7AF0]                     ; [data_f9a7af0]
#endif

void sub_e943170(void* lock) {
    static_assert(sizeof(void*) == 8, "sub_e943170: x64 ABI, pointer-sized argument in RCX and result in RAX");
    // 0xe943170..0xe943177:  jmp qword ptr [0xF9A7AF0]   ; tail jump through loader-resolved data slot 0xF9A7AF0
    using Fn = void (*)(void*);
    return reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A7AF0ull))(lock);   // 0xe943170  jmp qword ptr [0xF9A7AF0]   ; 8-byte load from the slot, tail jump, RAX result as-is
}

} // namespace native

LIFT_FN(sub_e943170, "sub_e943170", 0xe943170, ::native::sub_e943170, nullptr);
