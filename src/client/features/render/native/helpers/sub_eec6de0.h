#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec6de0 (0xeec6de0, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec6de0  jmp qword ptr [0xF9A8AA0]     ; [data_f9a8aa0]
// an indirect tail jump through IAT data slot 0xF9A8AA0 (.rdata). The slot holds the
// imported address of VCRUNTIME140.dll!memmove; the jmp tail-calls memmove with dst in
// RCX, src in RDX, size in R8 and forwards memmove's return (RAX). The instruction reads
// no memory and writes none; the copy semantics belong to memmove.
//
// Slot 0xF9A8AA0 (.rdata) holds VCRUNTIME140.dll!memmove
// [V: PE import table read via tools/sigs/peimports.py: slot RVA 0xF9A8AA0 ->
// VCRUNTIME140.dll!memmove]. At runtime the loader fills the slot with memmove's address.
//
// There are no struct fields to layout-assert; the x64 ABI contract is asserted below.
struct sub_eec6de0Layout {
    static_assert(sizeof(void*) == 8, "sub_eec6de0: x64 ABI, pointer-sized address space");
    using Fn = void* (__cdecl*)(void*, const void*, std::uint64_t);
    static_assert(sizeof(Fn) == 8, "sub_eec6de0: x64 function pointer is 8 bytes");
};

// VCRUNTIME140!memmove, the target of data slot 0xF9A8AA0. Declared with its real C
// signature so the lifted body of sub_eec6de0 calls exactly what the original's
// jmp qword ptr [0xF9A8AA0] dispatches to at runtime.
extern "C" void* memmove(void* dst, const void* src, std::uint64_t size);

namespace native {

// Signature of sub_eec6de0 itself: identical to the target (tail forwarder, no register
// shuffling). x64 Microsoft ABI: dst in RCX, src in RDX, size in R8, return in RAX;
// control passes straight to memmove.
void* sub_eec6de0(void* dst, const void* src, std::uint64_t size);

} // namespace native
