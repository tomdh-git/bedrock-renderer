#pragma once
#include <cstddef>
#include <cstdint>

// sub_6ae330 (0x6ae330, size 0xd4, 1.26.62.01): releases the refcounted objects referenced inside a
// range of 0x18-byte elements ([a0+0x00]..[a0+0x08]), then calls sub_e935700 on a derived pointer
// and clears [a0+0x00..0x17]. x64 Microsoft ABI: RCX = a0, return void [V: rdis dis 0x6ae330 0xd4].
//
// Field layout recovered from the disassembly:
//   0x6ae337  mov rdi,[rcx]           ; [a0+0x00] start pointer
//   0x6ae346  mov rbx,[rcx+8]         ; [a0+0x08] iteration-end pointer
//   0x6ae3a4  mov rdx,[rsi+0x10]      ; [a0+0x10] size/end pointer
//   0x6ae369  mov rcx,[rdi+0x10]      ; element[0x10] vfptr object
//   0x6ae383  mov rcx,[rdi+8]         ; element[8] refcounted object
//   0x6ae38c  lock dec dword ptr [rcx+0xC]  ; refcounted object count at +0xC

struct Sub6ae330This {
    void* field00;   // +0x00  start pointer of the element range
    void* field08;   // +0x08  iteration-end pointer of the element range
    void* field10;   // +0x10  size/end pointer used for the 0x1000 comparison
};
static_assert(offsetof(Sub6ae330This, field00) == 0x00, "sub_6ae330: start pointer at +0x00");
static_assert(offsetof(Sub6ae330This, field08) == 0x08, "sub_6ae330: iteration-end pointer at +0x08");
static_assert(offsetof(Sub6ae330This, field10) == 0x10, "sub_6ae330: size/end pointer at +0x10");
static_assert(sizeof(Sub6ae330This) == 0x18, "sub_6ae330: this object size 0x18");

struct Sub6ae330Elem {
    void* field00;   // +0x00  unused by this function
    void* field08;   // +0x08  refcounted object (count at +0xC, dtor at vfptr[8])
    void* field10;   // +0x10  vfptr object (released via vfptr[0] with flag 1)
};
static_assert(offsetof(Sub6ae330Elem, field00) == 0x00, "sub_6ae330: element unused field at +0x00");
static_assert(offsetof(Sub6ae330Elem, field08) == 0x08, "sub_6ae330: element refcounted object at +0x08");
static_assert(offsetof(Sub6ae330Elem, field10) == 0x10, "sub_6ae330: element vfptr object at +0x10");
static_assert(sizeof(Sub6ae330Elem) == 0x18, "sub_6ae330: element size 0x18");

static constexpr std::uintptr_t kEea6040SlotRva = 0xF99FFA0;  // call qword ptr [0xF99FFA0] = sub_eea6040 (vendor boundary)
static_assert(kEea6040SlotRva == 0xF99FFA0, "sub_6ae330: eea6040 thunk slot at RVA 0xF99FFA0");
static constexpr std::uintptr_t kFatalSlotRva = 0xF9A8C78;    // call qword ptr [0xF9A8C78]
static_assert(kFatalSlotRva == 0xF9A8C78, "sub_6ae330: fatal thunk slot at RVA 0xF9A8C78");

namespace native {

// sub_e935700 (lift set, docs/data/native_functions.tsv): tail jump to sub_392960; argument forwarded
// in RCX, result returned in RAX. Forward-declared here and called by the lifted body.
void* sub_e935700(void* a0);

// sub_6ae330 (0x6ae330, size 0xd4, 1.26.62.01): RCX = a0, return void.
void sub_6ae330(void* a0);

} // namespace native
