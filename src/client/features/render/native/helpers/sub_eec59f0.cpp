// LIFT 0xeec59f0 size 0x6 1.26.62.01 sub_eec59f0
#include "sub_eec59f0.h"

static_assert(sizeof(void*) == 8, "sub_eec59f0: x64 ABI contract, pointer-sized address space");

namespace native {

// sub_eec59f0 (0xeec59f0, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec59f0  jmp qword ptr [0xF9A75A8]     ; [data_f9a75a8]
//
// Slot 0xF9A75A8 (.rdata) holds the import-by-name RVA 0xF9AB92C (hint 1413) for
// MSVCP140!_Mtx_lock: void _Mtx_lock(struct _Mtx*). At runtime the loader fills the slot
// with that function's address, so the instruction tail-jumps to _Mtx_lock(mtx): the
// pointer argument arrives in RCX, is forwarded as-is, and control never returns to the
// caller. No memory is read or written by the instruction itself beyond the slot load.
//
// Verbatim instruction of the function (matches rdis dis 0xeec59f0 6):
#if 0
0xeec59f0  jmp qword ptr [0xF9A75A8]
#endif

void sub_eec59f0(struct _Mtx* mtx)
{
    // 0xeec59f0..0xeec59f6: jmp qword ptr [0xF9A75A8] ; tail jump to MSVCP140!_Mtx_lock via data slot 0xF9A75A8
    return ::_Mtx_lock(mtx);   // 0xeec59f0  jmp qword ptr [0xF9A75A8]
}

} // namespace native

LIFT_FN(eec59f0, "sub_eec59f0", 0xEEC59F0, native::sub_eec59f0, nullptr);
