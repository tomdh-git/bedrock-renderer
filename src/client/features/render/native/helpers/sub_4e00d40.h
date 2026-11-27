#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"
#include "client/features/render/native/helpers/sub_e935700.h"

// sub_4e00d40 (0x4e00d40, size 0x94, 1.26.62.01).
//
// Jump-table dispatch on the index passed in RCX. The table sits at image RVA
// 0xF2158A4 (VA 0x14F2158A4 with image base 0x140000000) and holds 19 signed
// int32 offsets from the table base; each entry is tail-jumped to
// (0x4e00d53 `jmp rcx`) as base + entry[index]:
//   index 0,1 -> 0x4e00dce   : return immediately
//   index 2   -> 0x4e00d92   : release the object at [a2+0x0], then tail call sub_e935700(a2)
//   index 3,4 -> 0x4e00d55   : release the object at [a2+0x10]
//   index 5..18 -> computed tail jump to code outside this function
//
// a2 (R8) is a handle: [a2+0x00] vfptr, [a2+0x08] pointer to refcounted
// object A, [a2+0x10] pointer to refcounted object B. A refcounted object is
// +0x00 vfptr, +0x08 std::uint32_t refcount, +0x0C std::uint32_t refcount;
// both refcounts are lock-dec released here.
//
// The two calls go through data slot 0xF99FFA0 = sub_eea6040
// (docs/data/native_boundary.tsv: vendor class, "thunk via data slot 0xF99FFA0
// (loader-resolved)"). sub_eea6040 is a `jmp rax` thunk, so the caller
// preloads RAX from the object's vtable and each `call qword ptr [0xF99FFA0]`
// executes obj->vfptr[n](obj). The lifted code calls the vtable entry
// directly, which is behaviorally identical (the thunk is only a tail jump to
// RAX).
//
// a1 (RDX) is unused by this function except that it is forwarded in RDX on
// the computed tail jumps (jmp rcx leaves RDX/R8 unchanged).
//
// x64 Microsoft ABI: RCX = index, RDX = a1, R8 = a2 (handle). Returns void.
//
// Struct fields touched ([V] = seen in the disassembly):
//   [a2+0x00] R  vfptr                              0x4e00d92  mov rcx,[r8]
//   [a2+0x08] R  handle->objectA pointer             0x4e00d9a  mov rdx,[rcx+8]
//   [a2+0x10] R  handle->objectB pointer             0x4e00d55  mov rsi,[r8+0x10]
//   [obj+0x08] R/W lock-dec refcount                 0x4e00d5e  lock dec dword ptr [rsi+8]
//   [obj+0x0C] R/W lock-dec refcount                 0x4e00d73  lock dec dword ptr [rsi+0xC]
//   [p+0x0C]   R/W lock-dec refcount                 0x4e00da3  lock dec dword ptr [rdx+0xC]
//   vfptr[0] / vfptr[1]  R  virtual method preload    0x4e00d67 / 0x4e00d7c / 0x4e00dac
//
// Callees:
//   0x4e00d6d  call qword ptr [0xF99FFA0]  -> sub_eea6040 (boundary, vendor, via data slot 0xF99FFA0)
//   0x4e00db6  call qword ptr [0xF99FFA0]  -> sub_eea6040 (boundary, vendor, via data slot 0xF99FFA0)
//   0x4e00dc9  jmp 0xE935700               -> native::sub_e935700 (lift set, tail call)
//   0x4e00d53  jmp rcx                     -> computed tail jump, no fixed target
// 0 callees in the lift set are called before returning except sub_e935700 on the index-2 path.

// Layout mirror: no shared SDK header declares this handle type, so the
// observed offsets are asserted locally instead.
struct RefCountedObjectLayout {
    void* vfptr;          // +0x00
    std::uint32_t ref8;   // +0x08 lock-dec released
    std::uint32_t refC;   // +0x0C lock-dec released
};
struct HandleLayout {
    void* vfptr;          // +0x00
    void* objectA8;       // +0x08 pointer to a RefCountedObject
    void* objectB10;      // +0x10 pointer to a RefCountedObject
};

static_assert(offsetof(RefCountedObjectLayout, ref8) == 0x08,
    "sub_4e00d40: refcount at +0x08 (0x4e00d5e, 0x4e00da3)");
static_assert(offsetof(RefCountedObjectLayout, refC) == 0x0C,
    "sub_4e00d40: refcount at +0x0C (0x4e00d73)");
static_assert(offsetof(HandleLayout, objectA8) == 0x08,
    "sub_4e00d40: handle field at +0x08 (0x4e00d9a)");
static_assert(offsetof(HandleLayout, objectB10) == 0x10,
    "sub_4e00d40: handle field at +0x10 (0x4e00d55)");
static_assert(sizeof(void*) == 8, "sub_4e00d40: x64 pointers");

namespace native {

// sub_4e00d40 (0x4e00d40, size 0x94, 1.26.62.01): see the layout comments above.
void sub_4e00d40(std::uint32_t index, void* a1, void* a2);

} // namespace native
