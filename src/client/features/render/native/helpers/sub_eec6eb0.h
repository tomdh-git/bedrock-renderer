#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec6eb0 (0xeec6eb0, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec6eb0  jmp qword ptr [0xF9A8A90]     ; [data_f9a8a90]
// an indirect tail jump through data slot 0xF9A8A90 (.rdata/IAT). The slot is in the
// same IAT region as memcpy (0xF9A8A98) and memmove (0xF9A8AA0). Callers pass three
// arguments (RCX, RDX, R8) and test the integer return in EAX, matching the signature
// of memcmp: int memcmp(const void* ptr1, const void* ptr2, size_t num).
// [V] 0xeec6eb0  jmp qword ptr [0xF9A8A90] (rdis dis 0xeec6eb0 6)
// [V] Callers (e.g., 0x777aa, 0x77f49, 0x85019, 0xaa98a) set RCX, RDX, R8 before call
// and test EAX after; 7300+ callers in total.
// No struct fields are read or written, so there are no layout constants beyond the x64
// ABI contract asserted below. 0 callees in the lift set: the jmp target comes from a
// data slot; memcmp itself is called directly as a CRT library intrinsic (std::memcmp),
// not through a boundary wrapper.
struct sub_eec6eb0Layout {
    static_assert(sizeof(void*) == 8, "sub_eec6eb0: x64 ABI, pointer-sized address space");
    using Fn = int (__cdecl*)(const void*, const void*, size_t);
    static_assert(sizeof(Fn) == 8, "sub_eec6eb0: x64 function pointer is 8 bytes");
};

namespace native {

// Signature of sub_eec6eb0 itself: identical to the memcmp target (tail forwarder, no
// register shuffling). x64 Microsoft ABI: RCX = ptr1, RDX = ptr2, R8 = num, return EAX = int.
int sub_eec6eb0(const void* ptr1, const void* ptr2, size_t num);

} // namespace native