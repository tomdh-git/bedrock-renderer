// LIFT 0xeec75a0 size 0x6 1.26.62.01 sub_eec75a0
#include "sub_eec75a0.h"

#include <cmath>

static_assert(sizeof(void*) == 8, "sub_eec75a0: x64 ABI, pointer-sized address space");

namespace native {

// sub_eec75a0 (0xeec75a0, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec75a0  jmp qword ptr [0xF9A8E60]     ; [data_f9a8e60]
//
// Slot 0xF9A8E60 (.rdata) is the MSVC CRT import slot of floorf:
//   float floorf(float);
// [V: PE import table read, slot RVA 0xF9A8E60 -> import-by-name RVA 0xF9B0820,
// hint 0xBF, name 'floorf']. At runtime the loader fills the slot with floorf's address,
// so the jmp tail-calls floorf: the float argument arrives in XMM0 and is forwarded
// unchanged, floorf's float return lands in XMM0 and is returned to the caller;
// control never returns to the caller of this thunk.
//
// Verbatim instruction of the function (matches rdis dis 0xeec75a0):
#if 0
0xeec75a0  jmp qword ptr [0xF9A8E60]
#endif

float sub_eec75a0(float value) {
    // 0xeec75a0..0xeec75a6: jmp qword ptr [0xF9A8E60] ; tail call to floorf via data slot 0xF9A8E60 (value=XMM0, return=XMM0)
    return std::floorf(value);   // 0xeec75a0  jmp qword ptr [0xF9A8E60]
}

} // namespace native

LIFT_FN(eec75a0, "sub_eec75a0", 0xEEC75A0, sub_eec75a0, nullptr);
