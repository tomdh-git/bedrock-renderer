#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/native/Lift.h"

// sub_673cef0 (0x673cef0, size 0xea, 1.26.62.01): BgfxFrameBuilder::endFrame.
// Releases four vendor ref-counted objects owned by the frame builder:
//   self+0x50 (released first), self+0x40, self+0x30, then self+0x08 (released last).
// Each release: atomic strong-refcount-- at obj+0x8; if it reaches 0, call vfptr[0] (destroy)
// via the sub_eea6040 thunk; then atomic weak-refcount-- at obj+0xC; if it reaches 0, call
// vfptr[8] (delete, at vfptr+0x8) via the same thunk. The final object (self+0x08) tail-calls
// the delete through the thunk and never returns.
//
//   0x673cef9  mov rdi,[rcx+0x50]     ; obj = self->m_obj50
//   0x673cf02  lock dec dword ptr [rdi+8]      ; strong-- (atomic write)
//   0x673cf08  mov rax,[rdi]      ; vfptr = obj->m_vfptr                       (read obj+0x0)
//   0x673cf0b  mov rax,[rax]      ; destroy = vfptr[0]                         (read vfptr+0x0)
//   0x673cf11  call qword ptr [0xF99FFA0]       ; sub_eea6040(obj, destroy) via data-slot thunk (jmp rax)
//   0x673cf17  lock dec dword ptr [rdi+0xC]    ; weak-- (atomic write)
//   0x673cf1d  mov rax,[rdi]      ; vfptr re-read                                  (read obj+0x0)
//   0x673cf20  mov rax,[rax+8]    ; delete = vfptr[8]                          (read vfptr+0x8)
//   0x673cf27  call qword ptr [0xF99FFA0]       ; sub_eea6040(obj, delete)
// Identical sequence for self+0x40 (0x673cf2d..0x673cf61) and self+0x30 (0x673cf61..0x673cf95).
// For self+0x08 (0x673cf95..0x673cfda) the delete call is a tail call:
//   0x673cfc0  mov rdx,[0xF99FFA0] ; 0x673cfc7  mov rcx,obj ; 0x673cfd0  jmp rdx
//
// All calls go through data slot 0xF99FFA0 ([data_f99ffa0] = sub_eea6040), a vendor boundary
// thunk whose body is `jmp rax`: RCX = object, RAX = vtable entry to tail-jump to.
// Field semantics of self+0x08/+0x30/+0x40/+0x50 are not derivable from the listing;
// neutral names below ([open]: see docs/functions/673cef0.md '## DECISIONS').

namespace native {

// sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0): `jmp rax` thunk.
// Called with rcx = object pointer; the vtable entry to jump to is passed as the second
// argument (it is what RAX holds at the call site). Return value is the tail-jumped entry's;
// ignored by this lift (the thunk never returns to its caller).
// Declared with void* return because Lift.h's Boundary static_assert (sizeof(R) <= 8) cannot
// be instantiated with R = void.
::native::Boundary<void*, void*, void*> sub_eea6040("sub_eea6040");

} // namespace native

namespace native::helpers {

// Vendor ref-counted object pointed to by each self field.
//   +0x00 void** m_vfptr
//   +0x08 std::uint32 m_strong  (atomic, lock dec; destroy when it reaches 0)
//   +0x0C std::uint32 m_weak    (atomic, lock dec; delete when it reaches 0)
struct sub_673cef0_refobj {
    void** m_vfptr;                  // +0x00
    std::uint32_t m_strong;          // +0x08
    std::uint32_t m_weak;            // +0x0C
};                                   // sizeof == 0x10

// Object passed in RCX ('this', BgfxFrameBuilder). Touched fields: +0x08, +0x30, +0x40, +0x50
// (all reads of void* object pointers); everything between is unobserved padding.
struct sub_673cef0_state {
    std::uint8_t pad_0x00[0x08];     // +0x00 unobserved
    void* m_obj08;                   // +0x08 (released last, tail call)
    std::uint8_t pad_0x10[0x20];     // +0x10..0x2F unobserved
    void* m_obj30;                   // +0x30
    std::uint8_t pad_0x38[0x08];     // +0x38..0x3F unobserved
    void* m_obj40;                   // +0x40
    std::uint8_t pad_0x48[0x08];     // +0x48..0x4F unobserved
    void* m_obj50;                   // +0x50 (released first)
};                                   // sizeof == 0x58

struct sub_673cef0Layout {
    static_assert(sizeof(void*) == 8, "sub_673cef0: x64 ABI, pointer-sized address space");
    // state fields (every [reg+off] read of self, [V] cited by instruction)
    static_assert(offsetof(sub_673cef0_state, m_obj08) == 0x08, "sub_673cef0: m_obj08 at self+0x08");
    static_assert(offsetof(sub_673cef0_state, m_obj30) == 0x30, "sub_673cef0: m_obj30 at self+0x30");
    static_assert(offsetof(sub_673cef0_state, m_obj40) == 0x40, "sub_673cef0: m_obj40 at self+0x40");
    static_assert(offsetof(sub_673cef0_state, m_obj50) == 0x50, "sub_673cef0: m_obj50 at self+0x50");
    static_assert(sizeof(sub_673cef0_state) == 0x58, "sub_673cef0: state size");
    // refobj fields (every [reg+off] read/write of the released object, [V])
    static_assert(offsetof(sub_673cef0_refobj, m_vfptr) == 0x00, "sub_673cef0: m_vfptr at obj+0x00");
    static_assert(offsetof(sub_673cef0_refobj, m_strong) == 0x08, "sub_673cef0: m_strong at obj+0x08");
    static_assert(offsetof(sub_673cef0_refobj, m_weak) == 0x0C, "sub_673cef0: m_weak at obj+0x0C");
    static_assert(sizeof(sub_673cef0_refobj) == 0x10, "sub_673cef0: refobj size");
    // vtable entries read through the thunk target slot
    static constexpr std::uintptr_t kDestroyVtableOffset = 0x00;   // vfptr[0] = destroy
    static constexpr std::uintptr_t kDeleteVtableOffset = 0x08;    // vfptr[1] = delete (at vfptr+0x8)
    static_assert(kDestroyVtableOffset == 0x00, "sub_673cef0: destroy at vfptr+0x00");
    static_assert(kDeleteVtableOffset == 0x08, "sub_673cef0: delete at vfptr+0x08");
    // Data slot holding the sub_eea6040 thunk ([data_f99ffa0] = sub_eea6040)
    static constexpr std::uintptr_t kThunkSlotRva = 0xF99FFA0;
    static_assert(kThunkSlotRva == 0xF99FFA0, "sub_673cef0: thunk data slot at 0xF99FFA0");
};

// sub_673cef0 (0x673cef0, size 0xea): x64 Microsoft ABI, 'this' in RCX, no return value.
// Block ranges mirror the disassembly: [0x673cef0, 0x673cf2d), [0x673cf2d, 0x673cf61),
// [0x673cf61, 0x673cf95), [0x673cf95, 0x673cfda).
void sub_673cef0(sub_673cef0_state* self);

} // namespace native::helpers
