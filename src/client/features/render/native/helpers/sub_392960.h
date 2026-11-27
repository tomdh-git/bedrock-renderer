#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_392960 (0x392960, size 0x35, 1.26.62.01).
//
//   0x392960  push rbp
//   0x392961  sub rsp,0x30
//   0x392965  lea rbp,[rsp+0x30]
//   0x39296a  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
//   0x392972  mov rdx,rcx
//   0x392975  mov rcx,[0x1233E1A8]          ; [data_1233e1a8] global object pointer (image RVA 0x1233E1A8)
//   0x39297c  test rdx,rdx
//   0x39297f  je short 0x39298F
//   0x392981  mov rax,[rcx]
//   0x392984  mov rax,[rax+0x10]
//   0x392988  call qword ptr [0xF99FFA0]    ; [data_f99ffa0] = sub_eea6040 (boundary, vendor)
//   0x39298e  nop
//   0x39298f  add rsp,0x30
//   0x392993  pop rbp
//   0x392994  ret
//
// The function reads the qword at image RVA 0x1233E1A8 ([data_1233e1a8], VA 0x15233E1A8
// with image base 0x140000000 [V: PE optional header ImageBase]) to obtain the global
// object pointer; when the argument (RCX) is non-NULL it invokes the boundary callee
// sub_eea6040 (vendor; thunk via data slot 0xF99FFA0 [V: docs/data/native_boundary.tsv])
// with (global object, argument). The two vtable loads at 0x392981/0x392984 produce the
// thunk's target register (RAX = vfptr[2]) and are otherwise unused.
// No game struct fields are read or written; no heap or stack slots beyond its own frame.
// Writes: none to game memory.
// Struct layout: none used (the function touches no game struct fields). Layout
// constants: only the x64 ABI contract, asserted below.
// Callees: sub_eea6040 (boundary vendor, via data slot 0xF99FFA0) - 1 call,
// 0 callees in the lift set.
//
// x64 Microsoft ABI: argument in RCX, return value in RAX (ignored by this function).
struct sub_392960Layout {
    static_assert(sizeof(void*) == 8, "sub_392960: x64 ABI, pointer-sized address space");
    using Fn = void (__cdecl*)(void*);
    static_assert(sizeof(Fn) == 8, "sub_392960: x64 function pointer is 8 bytes");
};

namespace native {

// sub_392960 (0x392960, 0x35 bytes, 1.26.62.01): argument `argument` arrives in RCX, no
// return value. See the instruction block above for the instruction-by-instruction reversal.
void sub_392960(void* argument);

} // namespace native
