#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"
#include "client/features/render/native/Lift.h"

// sub_4e01c30 (0x4e01c30, size 0x9d, 1.26.62.01).
//
// Entry (0x4e01c30..0x4e01c45): computed tail jump through the table at image
// RVA 0xF2158B8 (VA 0x14F2158B8 with image base 0x140000000):
//   target = 0x14F2158B8 + (int32_t)table[index]     (0x4e01c3d movsxd rcx,[rax+rcx*4])
//   jmp rcx                                          (0x4e01c44 jmp rcx)
// RCX (the index) is consumed by the table load; RDX and R8 are forwarded to
// the target unchanged. No bounds check: any index reads the table exactly as
// the exe does. Callers pass RCX = (int8_t)byte + 1 (sign-extended), so the
// parameter is int32_t: table[index] with a signed index reproduces base +
// index*4 exactly for every value.
//
// Known table entries land at 0x4e01c84 (shared epilogue, ret), 0x4e01c46
// (release the object at [a2+8]) and 0x4e01c8b (release the object at
// [a2+0x18], then fall into 0x4e01c46 via 0x4e01cc8 jmp 0x4E01C46); any other
// entry tail-jumps to code outside this function.
//
// a2 (R8) is a handle: [a2+0x08] and [a2+0x18] are pointers to refcounted
// objects. A refcounted object is +0x00 vfptr, +0x08 std::uint32_t refcount,
// +0x0C std::uint32_t refcount; both refcounts are lock-dec released here.
//
// The calls go through data slot 0xF99FFA0 = sub_eea6040
// (docs/data/native_boundary.tsv: class vendor, "thunk via data slot 0xF99FFA0
// (loader-resolved)"). sub_eea6040 is `jmp rax` (0xeea6040 jmp rax), so each
// `call qword ptr [0xF99FFA0]` with RAX preloaded from the object's vtable
// executes obj->vfptr[n](obj). The lifted code calls the vtable entry
// directly, which is behaviorally identical (the thunk is only a tail jump to
// RAX). The tail jump 0x4e01c81 jmp rdx (rdx = 0xF99FFA0 slot, rax = vfptr[1])
// is likewise a tail call of obj->vfptr[1](obj).
//
// a1 (RDX) is unused by this function except that it is forwarded in RDX on
// the computed tail jumps.
//
// x64 Microsoft ABI: RCX = index, RDX = a1, R8 = a2 (handle). Returns void.
//
// Struct fields touched ([V] = seen in the disassembly):
//   [a2+0x08] R  handle->objectB pointer             0x4e01c46  mov rsi,[r8+8]
//   [a2+0x18] R  handle->objectA pointer             0x4e01c8b  mov rsi,[r8+0x18]
//   [obj+0x08] R/W lock-dec refcount                 0x4e01c4f  lock dec dword ptr [rsi+8]
//   [obj+0x08] R/W lock-dec refcount                 0x4e01c94  lock dec dword ptr [rsi+8]
//   [obj+0x0C] R/W lock-dec refcount                 0x4e01c64  lock dec dword ptr [rsi+0xC]
//   [obj+0x0C] R/W lock-dec refcount                 0x4e01caf  lock dec dword ptr [rsi+0xC]
//   [obj+0x00] R  vfptr                               0x4e01c55  mov rax,[rsi]
//   [obj+0x00] R  vfptr                               0x4e01c9a  mov rax,[rsi]
//   vfptr[0]    R  virtual method preload              0x4e01c58  mov rax,[rax]
//   vfptr[0]    R  virtual method preload              0x4e01c9d  mov rax,[rax]
//   vfptr[1]    R  virtual method preload              0x4e01c6d  mov rax,[rax+8]
//   vfptr[1]    R  virtual method preload              0x4e01cb8  mov rax,[rax+8]
//
// Callees:
//   0x4e01c5e  call qword ptr [0xF99FFA0]  -> sub_eea6040 (boundary, vendor; thunk jmp rax -> obj->vfptr[0](obj))
//   0x4e01c81  jmp rdx                     -> sub_eea6040 tail call (thunk jmp rax -> obj->vfptr[1](obj); no return)
//   0x4e01ca6  call qword ptr [0xF99FFA0]  -> sub_eea6040 (boundary, vendor; -> obj->vfptr[0](obj))
//   0x4e01cbf  call qword ptr [0xF99FFA0]  -> sub_eea6040 (boundary, vendor; -> obj->vfptr[1](obj))
//   0x4e01c44  jmp rcx                     -> computed tail jump, no fixed target
//
// Layout mirror: no shared SDK header declares this handle type, so the
// observed offsets are asserted locally instead.
struct RefCountedObjectLayout4e01c30 {
    void* vfptr;             // +0x00
    std::uint32_t ref8;      // +0x08 lock-dec released
    std::uint32_t refC;      // +0x0C lock-dec released
};
struct HandleLayout4e01c30 {
    void* vfptr;             // +0x00
    void* objectB08;         // +0x08 pointer to a RefCountedObject
    void* pad10;             // +0x10
    void* objectA18;         // +0x18 pointer to a RefCountedObject
};

static_assert(offsetof(RefCountedObjectLayout4e01c30, ref8) == 0x08,
    "sub_4e01c30: refcount at +0x08 (0x4e01c4f, 0x4e01c94)");
static_assert(offsetof(RefCountedObjectLayout4e01c30, refC) == 0x0C,
    "sub_4e01c30: refcount at +0x0C (0x4e01c64, 0x4e01caf)");
static_assert(offsetof(HandleLayout4e01c30, objectB08) == 0x08,
    "sub_4e01c30: handle field at +0x08 (0x4e01c46)");
static_assert(offsetof(HandleLayout4e01c30, objectA18) == 0x18,
    "sub_4e01c30: handle field at +0x18 (0x4e01c8b)");
static_assert(sizeof(void*) == 8, "sub_4e01c30: x64 pointers");

namespace native {

// sub_4e01c30 (0x4e01c30, size 0x9d, 1.26.62.01): see the layout comments above.
void sub_4e01c30(std::int32_t index, void* a1, void* a2);

} // namespace native
