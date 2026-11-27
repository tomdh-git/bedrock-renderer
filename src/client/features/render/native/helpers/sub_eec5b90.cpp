// LIFT 0xeec5b90 size 0x6 1.26.62.01 sub_eec5b90
#include "sub_eec5b90.h"

static_assert(sizeof(void*) == 8, "sub_eec5b90: x64 ABI, pointer-sized address space");

namespace native {

// sub_eec5b90 (0xeec5b90, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec5b90  jmp qword ptr [0xF9A7560]     ; [data_f9a7560]
//
// Slot 0xF9A7560 (.rdata) holds the import-by-name entry for MSVCP140.dll!_Cnd_broadcast:
// _Thrd_result _Cnd_broadcast(_Cnd_t) where _Cnd_t is the MSVC CRT condition-variable
// pointer type. At runtime the loader fills the slot with that function's address, so the
// instruction tail-jumps to _Cnd_broadcast(cond): the pointer argument arrives in RCX, is
// forwarded as-is, and the _Thrd_result return value (EAX) passes straight through to this
// function's caller. No memory is read or written by the instruction itself beyond the
// slot load. _Cnd_t and _Cnd_broadcast are already declared by the MSVC CRT headers
// (_Cnd_t = _Cnd_internal_imp_t*; _Thrd_result _Cnd_broadcast(_Cnd_t) noexcept), so they
// are used directly and not redeclared here.
//
// Verbatim instruction of the function (matches rdis dis 0xeec5b90):
#if 0
0xeec5b90  jmp qword ptr [0xF9A7560]
#endif

_Thrd_result sub_eec5b90(_Cnd_t cond) {
    // 0xeec5b90..0xeec5b96: jmp qword ptr [0xF9A7560] ; tail jump to MSVCP140!_Cnd_broadcast via data slot 0xF9A7560
    return _Cnd_broadcast(cond);   // 0xeec5b90  jmp qword ptr [0xF9A7560]
}

} // namespace native

LIFT_FN(eec5b90, "sub_eec5b90", 0xEEC5B90, native::sub_eec5b90, nullptr);
