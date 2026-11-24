// LIFT 0xe935700 size 0x5 1.26.62.01 sub_e935700
#include "sub_e935700.h"

namespace native {

// sub_e935700 (0xe935700, size 0x5, 1.26.62.01).
//
// The body is a single tail jump to sub_392960. The function performs no reads,
// no writes and no calls of its own: the argument arrives in RCX and the result
// leaves in RAX, exactly like sub_392960 (0x392972 mov rdx,rcx ... 0x392994 ret).
//
// Verbatim instruction of the function (matches the rdis output for 0xe935700):
#if 0
0xe935700  jmp 0x392960
#endif

void* sub_e935700(void* a0) {
    // 0xe935700..0xe935705:  jmp 0x392960   ; tail call to sub_392960 (lift set, unit X7.392960)
    // 0xe935700  jmp 0x392960
    return sub_392960(a0);   // RCX forwarded unchanged, RAX result returned as-is (tail call)
}

} // namespace native

LIFT_FN(e935700, "sub_e935700", 0xE935700, sub_e935700, nullptr);
