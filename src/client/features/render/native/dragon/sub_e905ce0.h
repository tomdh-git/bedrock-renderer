#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_e905ce0 (0xe905ce0, size 0x19, 1.26.62.01, "Frame renderer lambda").
//
// Body [0xe905ce0, 0xe905cf9):
//   0xe905ce0  sub rsp,0x28       (shadow-space allocation; no observable store)
//   0xe905ce4  mov r8d,0x66        (callee's 3rd argument)
//   0xe905cea  call 0xEEC6EB0      (rcx=a1, rdx=a2, r8=0x66; returns eax)
//   0xe905cef  test eax,eax
//   0xe905cf1  sete al             (return value AL = (eax == 0))
//   0xe905cf4  add rsp,0x28
//   0xe905cf8  ret
//
// The function reads or writes NO struct fields and NO memory (no [reg+off] or
// absolute-address operand anywhere in the body). rcx (a1) and rdx (a2) are
// forwarded unchanged to the callee; there are therefore no field-offset layout
// constants to assert here. The x64 ABI contract is asserted in sub_e905ce0.cpp.
//
// Callee 0xeec6eb0 is an IAT import thunk (0xeec6eb0  jmp qword ptr [0xF9A8A90])
// that is absent from docs/data/native_functions.tsv and from
// docs/data/native_boundary.tsv, so it cannot be resolved to a lifted function or
// to a boundary wrapper. Its call target is unresolved; see
// docs/progress/oc_U-EX3.e905ce0.md ## UNRESOLVED CALL. The unit stops at that
// blocking fact. The .cpp forward-declares it with a best-effort signature only to
// express the call; this is not a boundary wrapper.

static_assert(sizeof(void*) == 8, "sub_e905ce0: x64 ABI, pointer-sized address space");

// Signature of sub_e905ce0 itself: x64 Microsoft ABI, a1 in RCX, a2 in RDX,
// return AL = (eax == 0) as bool.
bool sub_e905ce0(void* a1, void* a2);

} // namespace native
