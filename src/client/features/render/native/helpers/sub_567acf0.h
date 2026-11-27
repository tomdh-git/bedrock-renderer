#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/native/Lift.h"

namespace native::helpers {

// Layout of the object passed to sub_567acf0 in rcx (this), reverse-engineered from the
// disassembly of [0x567acf0, 0x567add9), Minecraft Windows 1.26.62.01.
//
// The object is a small buffer header holding a run of 0x28-byte elements followed by a
// backing-allocation end pointer. Fields observed ([V] = cited by instruction):
//
//   +0x00  data_start   R/W  start of the element array           [V: 0x567acfb R, 0x567ada8 W]
//   +0x08  data_end     R/W  one-past-last element (loop bound)   [V: 0x567ad0a R, 0x567ada8 W]
//   +0x10  buffer_end   R/W  end of the backing buffer (size=end-start)
//                                                                [V: 0x567ad75 R, 0x567adab W]
//
// Each element is 0x28 bytes:
//   +0x08  ref_obj      R   pointer to a refcounted object         [V: 0x567ad3c]
//   +0x18  type_tag     R   u8 type tag (switch table at data_f25cd68)
//                                                                [V: 0x567ad29]
//
// The refcounted object (element+0x8):
//   +0x00  vfptr        R   virtual function table pointer         [V: 0x567ad4b]
//   +0x08  refcount     R/W int32, lock dec at 0x567ad45           [V: 0x567ad45]
//   +0x0C  count0xC     R/W int32, lock dec at 0x567ad5a           [V: 0x567ad5a]
//   vfptr[0] = destructor, vfptr[1] = operator delete, both invoked
//   through the sub_eea6040 thunk via data slot 0xF99FFA0.

struct sub_567acf0_state {
    void* data_start;   // +0x00
    void* data_end;     // +0x08
    void* buffer_end;   // +0x10
};

static_assert(offsetof(sub_567acf0_state, data_start) == 0x00,
              "sub_567acf0: data_start at +0x00");
static_assert(offsetof(sub_567acf0_state, data_end) == 0x08,
              "sub_567acf0: data_end at +0x08");
static_assert(offsetof(sub_567acf0_state, buffer_end) == 0x10,
              "sub_567acf0: buffer_end at +0x10");
static_assert(sizeof(void*) == 8, "sub_567acf0: x64 pointers are 8 bytes");

// sub_eea6040 (boundary/vendor, via data slot 0xF99FFA0): std::uintptr_t
// sub_eea6040(void* object, void* vfptr_entry); return value ignored (thunk jmp rax).
native::Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// Signature (x64 Microsoft ABI) - arg1 (RCX) = this pointer to sub_567acf0_state,
// return value in RAX = result of sub_e935700 (the freed-buffer pointer).
// 0x567acf0  push r15; ...  0x567adbe  ret
uintptr_t sub_567acf0(sub_567acf0_state* self);

} // namespace native::helpers
