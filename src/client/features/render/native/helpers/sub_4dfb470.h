#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_4dfb470 (0x4dfb470, size 0x47, 1.26.62.01).
//
//   0x4dfb470  push rsi
//   0x4dfb471  sub rsp,0x20
//   0x4dfb475  mov rcx,[rcx]
//   0x4dfb478  test rcx,rcx
//   0x4dfb47b  je short 0x4DFB4B1
//   0x4dfb47d  mov rdx,[rcx+8]
//   0x4dfb481  test rdx,rdx
//   0x4dfb484  je short 0x4DFB4A2
//   0x4dfb486  lock dec dword ptr [rdx+0xC]
//   0x4dfb48a  jne short 0x4DFB4A2
//   0x4dfb48c  mov rax,[rdx]
//   0x4dfb48f  mov rax,[rax+8]
//   0x4dfb493  mov rsi,rcx
//   0x4dfb496  mov rcx,rdx
//   0x4dfb499  call qword ptr [0xF99FFA0]
//   0x4dfb49f  mov rcx,rsi
//   0x4dfb4a2  mov edx,0x20
//   0x4dfb4a7  add rsp,0x20
//   0x4dfb4ab  pop rsi
//   0x4dfb4ac  jmp 0xE935700
//   0x4dfb4b1  add rsp,0x20
//   0x4dfb4b5  pop rsi
//   0x4dfb4b6  ret
//
// The function takes a smart pointer object (pointer to managed object at +0x0).
// If managed is null, returns. Otherwise loads inner = managed[+0x8].
// If inner is null, tail-calls sub_e935700(managed, 0x20).
// Otherwise atomically decrements inner[+0xC] (refcount). If non-zero, tail-calls
// sub_e935700(managed, 0x20). If zero, calls sub_eea6040(inner, vtable[1]) via
// data slot 0xF99FFA0, then tail-calls sub_e935700(managed, 0x20).
// No game struct fields are read/written beyond the smart pointer and inner object layout.
// Layout constants: only the x64 ABI contract and the smart pointer/inner offsets, asserted below.

struct sub_4dfb470Layout {
    static_assert(sizeof(void*) == 8, "sub_4dfb470: x64 ABI, pointer-sized address space");
    // Smart pointer layout
    static constexpr std::uintptr_t kManagedOffset = 0x0;   // void* managed at a0+0x0
    static constexpr std::uintptr_t kInnerOffset = 0x8;     // void* inner at managed+0x8
    // Inner object layout
    static constexpr std::uintptr_t kRefcountOffset = 0xC;  // uint32_t refcount at inner+0xC
    static constexpr std::uintptr_t kVfptrOffset = 0x0;     // void* vfptr at inner+0x0
    static constexpr std::uintptr_t kDestructorOffset = 0x8; // void* destructor at vfptr+0x8 (vtable[1])
    // Data slot for vendor thunk
    static constexpr std::uintptr_t kThunkSlotRva = 0xF99FFA0; // image RVA of sub_eea6040 thunk slot
    // Callee
    static constexpr std::uintptr_t kCallee_e935700 = 0xE935700; // sub_e935700 (lift set)
    static_assert(kManagedOffset == 0x0, "sub_4dfb470: managed at +0x0");
    static_assert(kInnerOffset == 0x8, "sub_4dfb470: inner at +0x8");
    static_assert(kRefcountOffset == 0xC, "sub_4dfb470: refcount at +0xC");
    static_assert(kVfptrOffset == 0x0, "sub_4dfb470: vfptr at +0x0");
    static_assert(kDestructorOffset == 0x8, "sub_4dfb470: destructor at vfptr+0x8");
};

namespace native {

// sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0, docs/data/native_boundary.tsv row 506).
// Called with rcx = inner object (this), rdx = destructor function pointer (vtable[1]).
// The thunk tail-jumps to the destructor via RAX. Return value ignored.
native::Boundary<void, void*, void*> sub_eea6040("sub_eea6040");

// sub_e935700 (0xe935700, size 0x5, 1.26.62.01): lift-set callee.
// Tail-called with rcx = managed object, rdx = 0x20.
// Declared in sub_e935700.h; forward-declared here for the call.
void* sub_e935700(void* a0, std::uint32_t a1);

// sub_4dfb470 (0x4dfb470, 0x47 bytes, 1.26.62.01): argument `a0` arrives in RCX, no return value.
// See the instruction block above for the instruction-by-instruction reversal.
void sub_4dfb470(void* a0);

} // namespace native