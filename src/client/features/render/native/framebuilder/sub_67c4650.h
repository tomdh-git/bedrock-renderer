#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_67c4650 (0x67c4650, size 0xc1, 1.26.62.01, "BgfxFrameBuilder slot 17").
//
// The argument arrives in RDX (a1); the RCX entry argument is never read (dead). a1 is a context
// block holding three refcounted-object pointers:
//   a1+0x20  object C   (processed last)
//   a1+0x30  object B   (processed second)
//   a1+0x38  object A   (processed first)
// Each refcounted object: vtable@0x00, refcount1@0x08 (interlocked dec), refcount2@0x0C
// (interlocked dec). Object A additionally reads a back-pointer at +0xF0.
// When a refcount reaches zero the corresponding vtable slot is invoked:
//   vtable[0](obj, context) or vtable[1](obj, context), where context is object A
//   (or reinterpret_cast<void*>(1) in the object-A null-back-pointer path).
// The function ends with a tail jump to sub_e935700(a1) (sub_e935700 is class "lift", see
// docs/data/native_boundary.tsv line 505).
//
// All six `call qword ptr [0xF99FFA0]` are indirect virtual calls: sub_eea6040 (class vendor,
// docs/data/native_boundary.tsv line 506) is a `jmp rax` thunk reached through data slot 0xF99FFA0,
// so the target vtable slot (already loaded into RAX) is invoked directly with RCX=obj, RDX=context.
// Reverse-engineered from [0x67c4650, 0x67c4711), Minecraft Windows 1.26.62.01.

struct RefCountedObj {
    void** vtable;                  // +0x00: vtable pointer (R)
    std::uint32_t refcount1;        // +0x08: first refcount, interlocked dec (RW)
    std::uint32_t refcount2;        // +0x0C: second refcount, interlocked dec (RW)
    std::uint8_t pad0x10[0xE0];     // +0x10..0xEF padding
    RefCountedObj* backObject;      // +0xF0: object A back-pointer (R)
};

static_assert(offsetof(RefCountedObj, vtable) == 0x00,
              "sub_67c4650: refcounted object vtable at +0x00 (R)");
static_assert(offsetof(RefCountedObj, refcount1) == 0x08,
              "sub_67c4650: refcounted object refcount1 at +0x08 (RW)");
static_assert(offsetof(RefCountedObj, refcount2) == 0x0C,
              "sub_67c4650: refcounted object refcount2 at +0x0C (RW)");
static_assert(offsetof(RefCountedObj, backObject) == 0xF0,
              "sub_67c4650: object A back-pointer at +0xF0 (R)");

// Context block passed in RDX (a1). Only the offsets touched are declared.
struct FrameBuilderSlot17 {
    std::uint8_t pad0x00[0x20];     // +0x00..0x1F padding
    RefCountedObj* objectC;         // +0x20: object C pointer (R)
    std::uint8_t pad0x28[0x08];     // +0x28..0x2F padding
    RefCountedObj* objectB;         // +0x30: object B pointer (R)
    RefCountedObj* objectA;         // +0x38: object A pointer (R)
};

static_assert(offsetof(FrameBuilderSlot17, objectC) == 0x20,
              "sub_67c4650: a1+0x20 is object C pointer (R)");
static_assert(offsetof(FrameBuilderSlot17, objectB) == 0x30,
              "sub_67c4650: a1+0x30 is object B pointer (R)");
static_assert(offsetof(FrameBuilderSlot17, objectA) == 0x38,
              "sub_67c4650: a1+0x38 is object A pointer (R)");

// sub_e935700 (0xE935700, size 0x5, class lift): tail jump to sub_392960; same ABI
// (argument forwarded in RCX, result in RAX). Forward-declared here and called directly
// through its native symbol; lifted by its own unit.
void* sub_e935700(void* a0);

// Exact x64 Microsoft ABI mirror of the original function.
// RCX = entry argument 1 (dead, never read), RDX = a1 (FrameBuilderSlot17*), return = void*.
void* sub_67c4650(void* dead_rcx, FrameBuilderSlot17* a1);

} // namespace native
