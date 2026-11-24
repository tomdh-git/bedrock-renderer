// LIFT 0xeec6de0 size 0x6 1.26.62.01 sub_eec6de0
#include "sub_eec6de0.h"

static_assert(sizeof(void*) == 8, "sub_eec6de0: x64 ABI, pointer-sized address space");

namespace native {

// sub_eec6de0 (0xeec6de0, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec6de0  jmp qword ptr [0xF9A8AA0]     ; [data_f9a8aa0]
//
// Slot 0xF9A8AA0 (.rdata) holds the imported address of VCRUNTIME140.dll!memmove:
// void* memmove(void* dst, const void* src, size_t size) [V: PE import table read via
// tools/sigs/peimports.py: slot RVA 0xF9A8AA0 -> VCRUNTIME140.dll!memmove]. At runtime
// the loader fills the slot with memmove's address, so the jmp tail-jumps to memmove:
// dst arrives in RCX, src in RDX, size in R8, and memmove's return value (RAX) becomes
// this function's return; nothing else is read or written by the instruction itself.
//
// Verbatim instruction of the function (matches rdis dis 0xeec6de0):
#if 0
0xeec6de0  jmp qword ptr [0xF9A8AA0]
#endif

void* sub_eec6de0(void* dst, const void* src, std::uint64_t size) {
    // 0xeec6de0..0xeec6de6: jmp qword ptr [0xF9A8AA0] ; tail call to memmove via IAT slot 0xF9A8AA0
    return ::memmove(dst, src, size);   // 0xeec6de0  jmp qword ptr [0xF9A8AA0]
}

} // namespace native

LIFT_FN(eec6de0, "sub_eec6de0", 0xEEC6DE0, native::sub_eec6de0, nullptr);
