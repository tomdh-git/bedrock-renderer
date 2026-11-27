#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/native/Lift.h"

namespace native::helpers {

// State object (base register rcx = self): four pointer fields at +0x28,+0x30,+0x40,+0x48.
//   0x6754890  mov rbx,[rcx+0x28]   R
//   0x6754894  mov r14,[rcx+0x30]   R
//   0x6754898  mov r15,[rcx+0x40]   R
//   0x675489c  mov r12,[rcx+0x48]   R
//   0x6754920  mov rax,[rsi+0x28]   R   (rsi == self)
//   0x6754924  cmp rax,[rsi+0x30]   R
//   0x675492a  mov [rsi+0x30],rax   W
//   0x675492e  mov rbx,[rsi+0x40]   R
//   0x6754932  mov r14,[rsi+0x48]   R
//   0x675497f  mov rax,[rsi+0x40]   R
//   0x6754983  mov [rsi+0x48],rax   W
#pragma pack(push, 1)
struct sub_6754880_state {
    std::uint8_t pad0x00[0x28];   // +0x00..+0x27 (no observed access)
    void* f28;                    // +0x28: array1_begin void*  (R/W)
    void* f30;                    // +0x30: array1_end   void*  (R/W)
    std::uint8_t pad0x38[0x8];    // +0x38..+0x3f (no observed access)
    void* f40;                    // +0x40: array2_begin void*  (R)
    void* f48;                    // +0x48: array2_end   void*  (R/W)
};
#pragma pack(pop)

// Refcounted control block (base register rdi): vtable + two refcounts.
//   0x67548f9  mov rax,[rdi]        R +0x00 (vtable)
//   0x67548f3  lock dec [rdi+8]     RW +0x08 (refcount int32)
//   0x6754908  lock dec [rdi+0xC]   RW +0x0C (count0xC int32)
//   vfptr[0] = destructor, vfptr[1] = operator delete; both invoked via sub_eea6040.
#pragma pack(push, 1)
struct sub_6754880_ctrl {
    void* f0;                     // +0x00: vtable void*  (R)
    std::uint32_t f8;             // +0x08: refcount int32  (R/W)
    std::uint32_t fc;             // +0x0C: count0xC int32  (R/W)
};
#pragma pack(pop)

static_assert(offsetof(sub_6754880_state, f28) == 0x28, "sub_6754880 state f28 at +0x28");
static_assert(offsetof(sub_6754880_state, f30) == 0x30, "sub_6754880 state f30 at +0x30");
static_assert(offsetof(sub_6754880_state, f40) == 0x40, "sub_6754880 state f40 at +0x40");
static_assert(offsetof(sub_6754880_state, f48) == 0x48, "sub_6754880 state f48 at +0x48");
static_assert(sizeof(sub_6754880_state) >= 0x50, "sub_6754880 state sizeof lower bound");

static_assert(offsetof(sub_6754880_ctrl, f0) == 0x00, "sub_6754880 ctrl f0 at +0x00");
static_assert(offsetof(sub_6754880_ctrl, f8) == 0x08, "sub_6754880 ctrl f8 at +0x08");
static_assert(offsetof(sub_6754880_ctrl, fc) == 0x0c, "sub_6754880 ctrl fc at +0x0c");
static_assert(sizeof(sub_6754880_ctrl) >= 0x10, "sub_6754880 ctrl sizeof lower bound");

// sub_eea6040 (boundary/vendor, via data slot 0xF99FFA0):
//   std::uintptr_t sub_eea6040(void* object, void* vfptr_entry);
//   Invoked with object = control block pointer, vfptr_entry = vtable[0] or vtable[1].
//   Return value is ignored by the caller.
native::Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// Signature (x64 Microsoft ABI): RCX = self (pointer to sub_6754880_state).
// Return value in RAX is path-dependent: f28 (array1 cursor) when exiting via block 12,
// f40 (array2 begin) when exiting via block 19, 0 when both ranges empty at entry.
uintptr_t sub_6754880(sub_6754880_state* self);

} // namespace native::helpers
