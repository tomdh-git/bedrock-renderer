// LIFT 0xeec5880 size 0x6 1.26.62.01 sub_eec5880
#include "sub_eec5880.h"

static_assert(sizeof(void*) == 8, "sub_eec5880: x64 ABI contract, pointer-sized address space");

namespace native {

// sub_eec5880 (0xeec5880, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec5880  jmp qword ptr [0xF9A7918]     ; [data_f9a7918]
//
// Slot 0xF9A7918 (.rdata) holds import-by-name RVA 0xF9AC050: hint 14, name
// 'K32GetProcessMemoryInfo' (kernel32). At runtime the loader fills the slot with
// that function's address, so the jmp is a tail call to
// K32GetProcessMemoryInfo(hProcess, ppsmemCounters, cb): RCX = hProcess,
// RDX = pointer to the counters buffer (0x50 bytes at all three call sites),
// R8D = cb = 0x50, forwarded unchanged; the int (BOOL) return in EAX propagates to
// the thunk's caller and control never returns here. No memory is read or written by
// the instruction itself beyond the 8-byte slot load.
//
// Verbatim instruction of the function (matches rdis dis 0xeec5880 6):
#if 0
0xeec5880  jmp qword ptr [0xF9A7918]
#endif

int sub_eec5880(void* hProcess, void* ppsmemCounters, unsigned int cb)
{
    // 0xeec5880..0xeec5886: jmp qword ptr [0xF9A7918] ; tail jump to K32GetProcessMemoryInfo via data slot 0xF9A7918
    return K32GetProcessMemoryInfo(hProcess, ppsmemCounters, cb);   // 0xeec5880  jmp qword ptr [0xF9A7918]
}

} // namespace native

LIFT_FN(eec5880, "sub_eec5880", 0xEEC5880, native::sub_eec5880, nullptr);
