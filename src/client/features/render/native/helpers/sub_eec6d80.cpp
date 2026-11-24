// LIFT 0xeec6d80 size 0x6 1.26.62.01 sub_eec6d80
#include "sub_eec6d80.h"

static_assert(sizeof(void*) == 8, "sub_eec6d80: x64 ABI, pointer-sized address space");

namespace native {

// sub_eec6d80 (0xeec6d80, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec6d80  jmp qword ptr [0xF9A8A18]     ; [data_f9a8a18]
//
// Slot 0xF9A8A18 (.rdata) is the VCRUNTIME140.dll import slot of
// _CxxThrowException(void* exceptionObject, const void* throwInfo) [V:
// tools/sigs/peimports.py: "0F9A8A18 VCRUNTIME140.dll!_CxxThrowException"]. At runtime
// the loader fills the slot with that function's address, so the jmp tail-calls
// _CxxThrowException with the incoming arguments forwarded unchanged and control never
// returns to the caller (_CxxThrowException never returns).
//
// Verbatim instruction of the function (matches rdis dis 0xeec6d80):
#if 0
0xeec6d80  jmp qword ptr [0xF9A8A18]
#endif

void sub_eec6d80(void* a0, std::uintptr_t a1, std::uintptr_t, std::uintptr_t) {
    // 0xeec6d80..0xeec6d86: jmp qword ptr [0xF9A8A18] ; tail call to _CxxThrowException via data slot 0xF9A8A18
    return _CxxThrowException(a0, reinterpret_cast<const void*>(a1));   // 0xeec6d80  jmp qword ptr [0xF9A8A18]
}

} // namespace native

LIFT_FN(eec6d80, "sub_eec6d80", 0xEEC6D80, sub_eec6d80, nullptr);
