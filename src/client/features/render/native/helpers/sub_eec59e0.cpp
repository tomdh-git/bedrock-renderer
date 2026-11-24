// LIFT 0xeec59e0 size 0x6 1.26.62.01 sub_eec59e0
#include "sub_eec59e0.h"

namespace native {

// sub_eec59e0 (0xeec59e0, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec59e0  jmp qword ptr [0xF9A7310]     ; [data_f9a7310]
//
// Slot 0xF9A7310 (.rdata) holds the import-by-name RVA 0xF9AA638; the entry there
// (hint 652) is '?_Xbad_function_call@std@@YAXXZ', std::_Xbad_function_call(void) of
// the MSVC CRT. At runtime the loader fills the slot with that function's address, so
// the instruction jumps to std::_Xbad_function_call: no register is read, no memory is
// written, no argument is forwarded, and control never returns to the caller.
//
// Verbatim instruction of the function (matches rdis dis 0xeec59e0):
#if 0
0xeec59e0  jmp qword ptr [0xF9A7310]
#endif

void sub_eec59e0(void) {
    // 0xeec59e0..0xeec59e6: jmp qword ptr [0xF9A7310] ; tail jump to std::_Xbad_function_call via data slot 0xF9A7310
    return std::_Xbad_function_call();   // 0xeec59e0  jmp qword ptr [0xF9A7310]
}

} // namespace native

LIFT_FN(eec59e0, "sub_eec59e0", 0xEEC59E0, sub_eec59e0, nullptr);
