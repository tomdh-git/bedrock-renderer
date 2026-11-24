// LIFT 0xeec5a10 size 0x6 1.26.62.01 sub_eec5a10
#include "sub_eec5a10.h"

namespace native {

// sub_eec5a10 (0xeec5a10, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through an IAT data slot:
//   0xeec5a10  jmp qword ptr [0xF9A75B8]     ; [data_f9a75b8]
//
// Slot 0xF9A75B8 (.rdata) holds the imported address of MSVCP140!_Mtx_unlock:
// void _Mtx_unlock(struct _Mtx*) [V: IAT table in docs/progress/oc_U-EX0b1.md
// (peimports.py): slot RVA 0xF9A75B8 -> _Mtx_unlock]. At runtime the loader fills the
// slot with that address, so the jmp tail-jumps to _Mtx_unlock(mtx): the pointer arrives
// in RCX and is forwarded as-is, nothing else is read or written by the instruction
// itself, and the return value is void.
//
// Verbatim instruction of the function (matches rdis dis 0xeec5a10):
#if 0
0xeec5a10  jmp qword ptr [0xF9A75B8]
#endif

void sub_eec5a10(struct _Mtx* mtx) {
    // 0xeec5a10..0xeec5a16: jmp qword ptr [0xF9A75B8] ; tail jump to _Mtx_unlock via IAT slot 0xF9A75B8
    return ::_Mtx_unlock(mtx);   // 0xeec5a10  jmp qword ptr [0xF9A75B8]
}

} // namespace native

LIFT_FN(eec5a10, "sub_eec5a10", 0xEEC5A10, native::sub_eec5a10, nullptr);
