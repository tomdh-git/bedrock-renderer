// LIFT 0xeec73f0 size 0x6 1.26.62.01 sub_eec73f0
#include "sub_eec73f0.h"

#include <cmath>

static_assert(sizeof(void*) == 8, "sub_eec73f0: x64 ABI, pointer-sized address space");

namespace native {

// sub_eec73f0 (0xeec73f0, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec73f0  jmp qword ptr [0xF9A8E08]     ; [data_f9a8e08]
//
// Slot 0xF9A8E08 (.rdata) is the MSVC CRT import slot of ceilf:
//   float ceilf(float);
// [V: PE import table read, slot RVA 0xF9A8E08 -> import-by-name RVA 0xF9B07CC, hint
// 0x7d, name 'ceilf']. At runtime the loader fills the slot with ceilf's address, so the
// jmp tail-calls ceilf: the float argument arrives in XMM0 and is forwarded unchanged,
// ceilf's float return lands in XMM0 and is returned to the caller; control never returns
// to the caller of this thunk.
//
// Verbatim instruction of the function (matches rdis dis 0xeec73f0):
#if 0
0xeec73f0  jmp qword ptr [0xF9A8E08]
#endif

float sub_eec73f0(float value) {
    // 0xeec73f0..0xeec73f6: jmp qword ptr [0xF9A8E08] ; tail call to ceilf via data slot 0xF9A8E08 (value=XMM0, return=XMM0)
    return std::ceilf(value);   // 0xeec73f0  jmp qword ptr [0xF9A8E08]
}

} // namespace native

LIFT_FN(eec73f0, "sub_eec73f0", 0xEEC73F0, sub_eec73f0, nullptr);
