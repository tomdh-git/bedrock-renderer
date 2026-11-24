// LIFT 0xebce390 size 0x5 1.26.62.01 sub_ebce390
#include "sub_ebce390.h"
#include "client/features/render/native/Lift.h"

#if 0
// Verbatim instruction from the exe (the only instruction of sub_ebce390, [0xebce390, 0xebce395)):
0xebce390  jmp 0xEEC6EC0
#endif

namespace native {

// Lifted body of sub_ebce390 (0xebce390, size 0x5, 1.26.62.01).
//
// The exe function is exactly one instruction, a tail jump, so the lifted body is exactly
// one tail call: same three register arguments in the same order, same return (void, unused
// by callers), no prologue, no stack frame, no branches.
//
//   0xebce390  jmp 0xEEC6EC0     ; -> sub_eec6ec0        (0xebce390..0xebce395)
//   0xeec6ec0  jmp qword ptr [0xF9A8A98]                 (sub_eec6ec0, lift-set callee)
//
// Citation: 0xebce390..0xebce395
void sub_ebce390_lifted(void* dst, void* src, std::uint32_t count) {
    static_assert(sizeof(void*) == 8, "sub_ebce390: x64 ABI, pointer-sized register arguments");
    // 0xebce390..0xebce395
    return sub_eec6ec0(dst, src, count);   // 0xebce390  jmp 0xEEC6EC0
}

} // namespace native

LIFT_FN(sub_ebce390, "sub_ebce390", 0xEBCE390, sub_ebce390_lifted, nullptr);
