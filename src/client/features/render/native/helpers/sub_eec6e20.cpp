// LIFT 0xeec6e20 size 0x6 1.26.62.01 sub_eec6e20
#include "sub_eec6e20.h"
#include <cassert>

namespace native {

// Layout assertion for IAT slot constant
static_assert(kIatStdExceptionCopy == 0xF9A8A48, "IAT slot RVA mismatch");

// 0xeec6e20..0xeec6e26
// 0xeec6e20  jmp qword ptr [0xF9A8A48]                     ; [data_f9a8a48]
extern "C" void sub_eec6e20(void* dest, const void* src) {
    // Indirect tail call through IAT slot at 0xF9A8A48 (__std_exception_copy)
    // The loader patches this slot with the actual CRT function address.
    // We replicate by reading the function pointer and calling it.
    // 0xeec6e20  jmp qword ptr [0xF9A8A48]
    auto* iat_slot = reinterpret_cast<StdExceptionCopyFn*>(kIatStdExceptionCopy);
    StdExceptionCopyFn target = *iat_slot;
    target(dest, src);
}

// Registry entry
LIFT_FN(eec6e20, "sub_eec6e20", 0xEEC6E20, native::sub_eec6e20, nullptr);

} // namespace native

// Verbatim instruction quotes for liftcheck
#if 0
0xeec6e20  jmp qword ptr [0xF9A8A48]
#endif