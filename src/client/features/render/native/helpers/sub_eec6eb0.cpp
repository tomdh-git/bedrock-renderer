// LIFT 0xeec6eb0 size 0x6 1.26.62.01 sub_eec6eb0
#include "sub_eec6eb0.h"

#include <cstring>

static_assert(sizeof(void*) == 8, "sub_eec6eb0: x64 ABI, pointer-sized address space");

namespace native {

// sub_eec6eb0 (0xeec6eb0, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec6eb0  jmp qword ptr [0xF9A8A90]     ; [data_f9a8a90]
//
// Slot 0xF9A8A90 (.rdata/IAT) holds the MSVC CRT import of memcmp:
//   int memcmp(const void* ptr1, const void* ptr2, size_t num);
// [V] 0xeec6eb0  jmp qword ptr [0xF9A8A90] (rdis dis 0xeec6eb0 6)
// [V] Callers (e.g., 0x777aa, 0x77f49, 0x85019, 0xaa98a) set RCX, RDX, R8 before call
// and test EAX after; 7300+ callers in total. The IAT slot 0xF9A8A90 is adjacent to
// memcpy (0xF9A8A98) and memmove (0xF9A8AA0) in the CRT import table. At runtime the
// loader fills the slot with memcmp's address, so the jmp is a tail call to memcmp:
// ptr1 arrives in RCX, ptr2 in RDX, num in R8 (x64 Microsoft ABI), memcmp's return
// value (int) lands in EAX and is returned to the caller; control never returns to
// this thunk.
//
// Verbatim instruction of the function (matches rdis dis 0xeec6eb0 6):
#if 0
0xeec6eb0  jmp qword ptr [0xF9A8A90]
#endif

int sub_eec6eb0(const void* ptr1, const void* ptr2, size_t num) {
    // 0xeec6eb0..0xeec6eb6: jmp qword ptr [0xF9A8A90] ; tail call to memcmp via IAT slot 0xF9A8A90 (ptr1=RCX, ptr2=RDX, num=R8, return EAX)
    return std::memcmp(ptr1, ptr2, num);   // 0xeec6eb0  jmp qword ptr [0xF9A8A90]
}

} // namespace native

LIFT_FN(eec6eb0, "sub_eec6eb0", 0xEEC6EB0, native::sub_eec6eb0, nullptr);