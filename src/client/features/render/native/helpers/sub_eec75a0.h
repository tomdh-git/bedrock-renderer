#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec75a0 (0xeec75a0, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec75a0  jmp qword ptr [0xF9A8E60]     ; [data_f9a8e60]
// an indirect tail jump through data slot 0xF9A8E60. It reads no registers of its own,
// writes no memory, and forwards everything unchanged to the slot's target.
//
// Slot 0xF9A8E60 (.rdata) holds the MSVC CRT import of floorf: the qword at the slot is
// import-by-name RVA 0xF9B0820 (hint 0xBF, name "floorf", float floorf(float)) [V: PE
// import table read, slot RVA 0xF9A8E60 -> import-by-name RVA 0xF9B0820 -> name
// floorf]. At runtime the loader fills the slot with floorf's address, so the jmp is a tail
// call to floorf: the float argument arrives in XMM0 and is forwarded unchanged, floorf's
// float return lands in XMM0 and is returned to the caller; control never returns to this
// thunk.
//
// x64 Microsoft ABI: argument float in XMM0, return float in XMM0, identical to floorf.
// There are no struct fields to layout-assert; the x64 ABI contract is asserted below.
struct sub_eec75a0Layout {
    static_assert(sizeof(void*) == 8, "sub_eec75a0: x64 ABI, pointer-sized address space");
    using Fn = float (__cdecl*)(float);
    static_assert(sizeof(Fn) == 8, "sub_eec75a0: x64 function pointer is 8 bytes");
};

namespace native {

// Signature of sub_eec75a0 itself: identical to the target (tail forwarder, no register
// shuffling). float in XMM0, float return in XMM0; control never returns to the caller
// because this is a tail jump to floorf.
float sub_eec75a0(float value);

} // namespace native
