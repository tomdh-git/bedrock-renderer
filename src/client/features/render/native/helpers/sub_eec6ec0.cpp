// LIFT 0xeec6ec0 size 0x6 1.26.62.01 sub_eec6ec0
#include "sub_eec6ec0.h"

#include <cstring>

static_assert(sizeof(void*) == 8, "sub_eec6ec0: x64 ABI, pointer-sized address space");

namespace native {

// sub_eec6ec0 (0xeec6ec0, size 0x6, 1.26.62.01).
//
// The whole function is one instruction, an indirect tail jump through a data slot:
//   0xeec6ec0  jmp qword ptr [0xF9A8A98]     ; [data_f9a8a98]
//
// Slot 0xF9A8A98 (.rdata/IAT) holds the MSVC CRT import of memcpy
//   void* memcpy(void* dst, const void* src, size_t n);
// [V] docs/functions/bc40a30.md: "0xEEC6EC0 | CRT/library intrinsic | memcpy (thunk,
// jmp [0xF9A8A98])" citing 0xbc40b17 call 0xEEC6EC0; [V] docs/BGFX_MAP.md:928: a vec4
// array is copied "with 0xeec6ec0 (memcpy)"; [V] docs/functions/67417f0.md:169:
// "0xeec6ec0 / 0xeec6de0 = memcpy-like (dst,src,n)". [V live] docs/data/live/readlog.txt
// line 6: "17:25:47 ptr @0xF9A8A98 1" — the slot is read at runtime. At runtime the
// loader fills the slot with memcpy's address, so the jmp is a tail call to memcpy: dst
// arrives in RCX, src in RDX, n in R8 (x64 Microsoft ABI), memcpy's return value (dst)
// lands in RAX and is returned to the caller; control never returns to this thunk.
//
// Verbatim instruction of the function (matches rdis dis 0xeec6ec0 6):
#if 0
0xeec6ec0  jmp qword ptr [0xF9A8A98]
#endif

void* sub_eec6ec0(void* dst, const void* src, size_t n) {
    // 0xeec6ec0..0xeec6ec6: jmp qword ptr [0xF9A8A98] ; tail call to memcpy via data slot 0xF9A8A98 (dst=RCX, src=RDX, n=R8, return RAX=dst)
    return std::memcpy(dst, src, n);   // 0xeec6ec0  jmp qword ptr [0xF9A8A98]
}

} // namespace native

LIFT_FN(eec6ec0, "sub_eec6ec0", 0xEEC6EC0, sub_eec6ec0, nullptr);
