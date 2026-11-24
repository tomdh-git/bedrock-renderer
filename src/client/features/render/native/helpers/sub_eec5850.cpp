// LIFT 0xeec5850 size 0x6 1.26.62.01 sub_eec5850
#include "sub_eec5850.h"

static_assert(sizeof(void*) == 8, "sub_eec5850: x64 ABI, pointer-sized address space");

namespace native {

// sub_eec5850 (0xeec5850, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec5850  jmp qword ptr [0xF9A7320]     ; [data_f9a7320]
//
// Slot 0xF9A7320 (.rdata) holds import-by-name RVA 0xF9AA680: hint 654, name
// '?_Xlength_error@std@@YAXPEBD@Z' = std::_Xlength_error(const char*) of the MSVC CRT.
// At runtime the loader fills the slot with that function's address, so the instruction
// jumps to std::_Xlength_error: the argument arrives in RCX (the const char* message,
// e.g. "string too long" at the call sites), is forwarded unchanged, and control never
// returns to the caller because _Xlength_error throws std::length_error.
//
// Verbatim instruction of the function (matches rdis dis 0xeec5850):
#if 0
0xeec5850  jmp qword ptr [0xF9A7320]
#endif

void sub_eec5850(const char* message) {
    // 0xeec5850..0xeec5856: jmp qword ptr [0xF9A7320] ; tail call to std::_Xlength_error via data slot 0xF9A7320
    return std::_Xlength_error(message);   // 0xeec5850  jmp qword ptr [0xF9A7320]
}

} // namespace native

LIFT_FN(eec5850, "sub_eec5850", 0xEEC5850, sub_eec5850, nullptr);
