// LIFT 0xe93b480 size 0x6 1.26.62.01 sub_e93b480
#include "sub_e93b480.h"

#include "client/features/render/native/Lift.h"

namespace native {

// sub_e93b480 (0xe93b480, size 0x6, 1.26.62.01).
//
// The body is exactly one instruction:
//
//   0xe93b480  jmp 0xE93B490   ; -> loc_e93b490      (0xe93b480..0xe93b485)
//
// followed by one padding byte inside the function's 6-byte span:
//
//   0xe93b485  int3             (0xe93b485..0xe93b486)
//
// It performs no reads, no writes and no calls of its own: arguments arrive in
// RCX (first), RDX (last), R8 (ch) and the result leaves in RAX. It is a pure
// tail forwarder to sub_e93b490, whose result is returned as-is.
//
// Verbatim instructions of the function (rdis output for 0xe93b480):
#if 0
0xe93b480  jmp 0xE93B490                                 ; -> loc_e93b490
0xe93b485  int3
#endif

// 0xe93b480..0xe93b486:  jmp 0xE93B490 ; int3  -- tail forward to sub_e93b490
wchar_t* sub_e93b480(wchar_t* first, wchar_t* last, wchar_t ch) {
    static_assert(sizeof(wchar_t) == 2, "sub_e93b480: 16-bit wchar_t argument in R8");
    static_assert(sizeof(void*) == 8, "sub_e93b480: x64 ABI, pointer-sized arguments and return value in RAX");
    // 0xe93b480..0xe93b486
    return sub_e93b490(first, last, ch);   // 0xe93b480  jmp 0xE93B490 ; tail forward to sub_e93b490, result in RAX as-is
}

} // namespace native

LIFT_FN(sub_e93b480, "sub_e93b480", 0xE93B480, sub_e93b480, nullptr);
