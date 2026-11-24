#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec6d80 (0xeec6d80, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec6d80  jmp qword ptr [0xF9A8A18]     ; [data_f9a8a18]
// an indirect tail jump through data slot 0xF9A8A18 (.rdata), the VCRUNTIME140.dll import
// slot of _CxxThrowException [V: tools/sigs/peimports.py prints "0F9A8A18 VCRUNTIME140.dll!
// _CxxThrowException"; slot bytes read from the image point at the import-by-name entry
// "_CxxThrowException"]. At runtime the loader fills the slot with that function's address,
// so the jmp tail-calls _CxxThrowException. RCX (exception object) and RDX (throw info)
// arrive from the caller and are forwarded unchanged; R8, R9 and stack arguments are
// forwarded by the jmp as well and read by nobody in this function. Nothing else is read or
// written and control never returns to the caller (_CxxThrowException never returns).
//
// Call sites confirm the convention: sub_e874d80 does lea rcx,[<exception object>];
// lea rdx,[<throw info>] and call 0xEEC6D80 with R8=1, R9=0 (dead arguments) [V:
// src/client/features/render/native/d3d12/sub_e874d80.cpp, 0xe874e02  call 0xEEC6D80].
//
// There are no struct fields to layout-assert: the function reads no memory and writes none.
// The x64 ABI contract is asserted below.
struct sub_eec6d80Layout {
    static_assert(sizeof(void*) == 8, "sub_eec6d80: x64 ABI, pointer-sized address space");
    using Fn = void (__cdecl*)(void*, std::uintptr_t, std::uintptr_t, std::uintptr_t);
    static_assert(sizeof(Fn) == 8, "sub_eec6d80: x64 function pointer is 8 bytes");
};

// VCRUNTIME140!_CxxThrowException -- target of the tail jump through data slot 0xF9A8A18
// [V: PE import table read via tools/sigs/peimports.py: slot RVA 0xF9A8A18 ->
// VCRUNTIME140.dll !_CxxThrowException]. Declared with C linkage; the real parameter types
// are (void* exceptionObject, const _s__ThrowInfo* throwInfo) and the function never returns.
extern "C" void _CxxThrowException(void* exceptionObject, const void* throwInfo);

namespace native {

// Signature of sub_eec6d80 itself: it forwards the incoming x64 arguments unchanged to
// _CxxThrowException (the jmp shuffles no registers). RCX=a0 (exception object), RDX=a1
// (throw info); R8=a2, R9=a3 and any stack arguments are forwarded as well and read by
// nobody. Return void; control never returns to the caller [V: callee never returns].
void sub_eec6d80(void* a0, std::uintptr_t a1, std::uintptr_t a2, std::uintptr_t a3);

} // namespace native
