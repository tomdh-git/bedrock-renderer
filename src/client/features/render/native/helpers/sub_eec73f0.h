#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec73f0 (0xeec73f0, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec73f0  jmp qword ptr [0xF9A8E08]     ; [data_f9a8e08]
// an indirect tail jump through data slot 0xF9A8E08. It reads no registers of its own,
// writes no memory, and forwards everything unchanged to the slot's target.
//
// Slot 0xF9A8E08 (.rdata) holds the MSVC CRT import of ceilf: the qword at the slot is
// import-by-name RVA 0xF9B07CC (hint 0x7d, name "ceilf", float ceilf(float)) [V: PE
// import table read, slot RVA 0xF9A8E08 -> import-by-name RVA 0xF9B07CC -> name
// ceilf]. At runtime the loader fills the slot with ceilf's address, so the jmp is a tail
// call to ceilf: the float argument arrives in XMM0 and is forwarded unchanged, ceilf's
// float return lands in XMM0 and is returned to the caller; control never returns to this
// thunk.
//
// x64 Microsoft ABI: argument float in XMM0, return float in XMM0, identical to ceilf.
// There are no struct fields to layout-assert; the x64 ABI contract is asserted below.
struct sub_eec73f0Layout {
    static_assert(sizeof(void*) == 8, "sub_eec73f0: x64 ABI, pointer-sized address space");
    using Fn = float (__cdecl*)(float);
    static_assert(sizeof(Fn) == 8, "sub_eec73f0: x64 function pointer is 8 bytes");
};

namespace native {

// Signature of sub_eec73f0 itself: identical to the target (tail forwarder, no register
// shuffling). float in XMM0, float return in XMM0; control never returns to the caller
// because this is a tail jump to ceilf.
float sub_eec73f0(float value);

} // namespace native
