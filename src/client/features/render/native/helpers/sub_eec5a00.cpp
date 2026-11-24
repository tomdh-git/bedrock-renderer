// LIFT 0xeec5a00 size 0x6 1.26.62.01 sub_eec5a00
#include "sub_eec5a00.h"

static_assert(sizeof(void*) == 8, "sub_eec5a00: x64 ABI, pointer-sized address space");

namespace native {

// sub_eec5a00 (0xeec5a00, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec5a00  jmp qword ptr [0xF9A72F0]     ; [data_f9a72f0]
//
// Slot 0xF9A72F0 (.rdata) holds the MSVCP140.dll import-by-name
// '?_Throw_Cpp_error@std@@YAXH@Z' = std::_Throw_Cpp_error(int) [V: PE import table read,
// slot RVA 0xF9A72F0 -> MSVCP140.dll !?_Throw_Cpp_error@std@@YAXH@Z]. At runtime the
// loader fills the slot with that function's address, so the instruction jumps to
// std::_Throw_Cpp_error: the error code arrives in RCX and is forwarded unchanged, and
// control transfers straight to the target (tail call) with the same return behavior the
// target has [V: rdis dis 0xeec5a00 = jmp qword ptr [0xF9A72F0]; peimports.py for the slot target].
//
// Verbatim instruction of the function (matches rdis dis 0xeec5a00):
#if 0
0xeec5a00  jmp qword ptr [0xF9A72F0]
#endif

void sub_eec5a00(int errorCode) {
    // 0xeec5a00..0xeec5a06: jmp qword ptr [0xF9A72F0] ; tail call to std::_Throw_Cpp_error via data slot 0xF9A72F0
    return std::_Throw_Cpp_error(errorCode);   // 0xeec5a00  jmp qword ptr [0xF9A72F0]
}

} // namespace native

LIFT_FN(eec5a00, "sub_eec5a00", 0xEEC5A00, sub_eec5a00, nullptr);
