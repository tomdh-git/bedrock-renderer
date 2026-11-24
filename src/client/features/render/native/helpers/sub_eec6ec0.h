#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec6ec0 (0xeec6ec0, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec6ec0  jmp qword ptr [0xF9A8A98]     ; [data_f9a8a98]
// an indirect tail jump through data slot 0xF9A8A98 (.rdata/IAT). The slot is the MSVC
// CRT import of memcpy:
//   void* memcpy(void* dst, const void* src, size_t n);
// [V] docs/functions/bc40a30.md labels 0xeec6ec0 "CRT/library intrinsic | memcpy (thunk,
// jmp [0xF9A8A98])" citing 0xbc40b17 call 0xEEC6EC0; [V] docs/BGFX_MAP.md:928 records
// the terrain extractor copies a vec4 array "with 0xeec6ec0 (memcpy)" to pool+offset;
// [V] docs/functions/67417f0.md:169 records "0xeec6ec0 / 0xeec6de0 = memcpy-like
// (dst,src,n)"; [V live] docs/data/live/readlog.txt line 6 "17:25:47 ptr @0xF9A8A98 1"
// shows the slot is read at runtime. At runtime the loader fills the slot with memcpy's
// address, so the jmp is a tail call to memcpy: x64 Microsoft ABI passes dst in RCX, src
// in RDX, n in R8, and memcpy returns dst in RAX; control never returns to the thunk.
//
// No struct fields are read or written, so there are no layout constants beyond the x64
// ABI contract asserted below. 0 callees in the lift set: the jmp target comes from a
// data slot, not a direct call; memcpy itself is called directly as a CRT library
// intrinsic (std::memcpy), not through a boundary wrapper.
struct sub_eec6ec0Layout {
    static_assert(sizeof(void*) == 8, "sub_eec6ec0: x64 ABI, pointer-sized address space");
    using Fn = void* (__cdecl*)(void*, const void*, size_t);
    static_assert(sizeof(Fn) == 8, "sub_eec6ec0: x64 function pointer is 8 bytes");
};

namespace native {

// Signature of sub_eec6ec0 itself: identical to the memcpy target (tail forwarder, no
// register shuffling). x64 Microsoft ABI: RCX = dst, RDX = src, R8 = n, return RAX = dst.
void* sub_eec6ec0(void* dst, const void* src, size_t n);

} // namespace native
