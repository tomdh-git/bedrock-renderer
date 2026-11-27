#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_7e6d0 (0x7e6d0, size 0x48, 1.26.62.01): reference-counted object release with two refcounts.
//
//   0x7e6d0  push rsi
//   0x7e6d1  sub rsp,0x20
//   0x7e6d5  mov rsi,[rcx+8]       ; inner = a0+0x8
//   0x7e6d9  test rsi,rsi
//   0x7e6dc  je short 0x7E712      ; if inner == null, return
//   0x7e6de  lock dec dword ptr [rsi+8]   ; refcount1-- at inner+0x8
//   0x7e6e2  jne short 0x7E712     ; if refcount1 != 0, return
//   0x7e6e4  mov rax,[rsi]         ; vtable = inner[+0x0]
//   0x7e6e7  mov rax,[rax]         ; destructor = vtable[0]
//   0x7e6ea  mov rcx,rsi           ; rcx = inner
//   0x7e6ed  call qword ptr [0xF99FFA0]  ; sub_eea6040(inner, destructor)
//   0x7e6f3  lock dec dword ptr [rsi+0xC] ; refcount2-- at inner+0xC
//   0x7e6f7  jne short 0x7E712     ; if refcount2 != 0, return
//   0x7e6f9  mov rax,[rsi]         ; vtable = inner[+0x0]
//   0x7e6fc  mov rax,[rax+8]       ; deleteFn = vtable[1] (dead read)
//   0x7e700  mov rdx,[0xF99FFA0]   ; rdx = sub_eea6040
//   0x7e707  mov rcx,rsi           ; rcx = inner
//   0x7e70a  add rsp,0x20
//   0x7e70e  pop rsi
//   0x7e70f  jmp rdx               ; tail call sub_eea6040(inner)
//
// loc_7e712:
//   0x7e712  add rsp,0x20
//   0x7e716  pop rsi
//   0x7e717  ret
//
// The owner object at a0 contains a pointer to the inner ref-counted object at +0x8.
// The inner object has vfptr at +0x0, refcount1 at +0x8, refcount2 at +0xC.
// vtable[0] = destroy/destructor; vtable[1] = delete.
// Two calls to sub_eea6040 (vendor boundary via data slot 0xF99FFA0): first calls the
// destructor when refcount1 reaches zero; second tail-calls the delete when refcount2
// reaches zero. x64 Microsoft ABI: argument in RCX, no return value.

struct sub_7e6d0Layout {
    static_assert(sizeof(void*) == 8, "sub_7e6d0: x64 ABI, pointer-sized address space");
    // Owner layout
    static constexpr std::uintptr_t kInnerOffset = 0x8;   // void* inner at owner+0x8
    // Inner object layout
    static constexpr std::uintptr_t kVfptrOffset = 0x0;   // void* vfptr at inner+0x0
    static constexpr std::uintptr_t kRefcount1Offset = 0x8;  // std::uint32_t refcount1 at inner+0x8
    static constexpr std::uintptr_t kRefcount2Offset = 0xC;  // std::uint32_t refcount2 at inner+0xC
    static constexpr std::uintptr_t kDestroyOffset = 0x0; // void* destroy at vfptr+0x0 (vtable[0])
    static constexpr std::uintptr_t kDeleteOffset = 0x8;   // void* delete at vfptr+0x8 (vtable[1])
    // Data slot for vendor thunk
    static constexpr std::uintptr_t kThunkSlotRva = 0xF99FFA0; // image RVA of sub_eea6040 thunk slot
    static_assert(kInnerOffset == 0x8, "sub_7e6d0: inner at +0x8");
    static_assert(kVfptrOffset == 0x0, "sub_7e6d0: vfptr at +0x0");
    static_assert(kRefcount1Offset == 0x8, "sub_7e6d0: refcount1 at +0x8");
    static_assert(kRefcount2Offset == 0xC, "sub_7e6d0: refcount2 at +0xC");
    static_assert(kDestroyOffset == 0x0, "sub_7e6d0: destroy at vfptr+0x0");
    static_assert(kDeleteOffset == 0x8, "sub_7e6d0: delete at vfptr+0x8");
};

namespace native {

// sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0, docs/data/native_boundary.tsv row 506).
// Called with rcx = inner object (this), second arg = function pointer to tail-jump to.
// The thunk tail-jumps to the function pointer. Return value ignored.
native::Boundary<void, void*, void*> sub_eea6040("sub_eea6040");

// sub_7e6d0 (0x7e6d0, 0x48 bytes, 1.26.62.01): argument `a0` arrives in RCX, no return value.
// See the instruction block above for the instruction-by-instruction reversal.
void sub_7e6d0(void* a0);

} // namespace native
