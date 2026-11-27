#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Forward declaration: refcounted object pointed to by FrameBuilderSlot50::obj0x48.
struct RefCountedObj;

// Layout of the object passed to sub_0x663f9d0 in RDX (this-equivalent).
// Only offsets the function touches are declared; the rest is padding.
// Reverse-engineered from the disassembly of [0x663f9d0, 0x663fa24), Minecraft Windows 1.26.62.01.
struct FrameBuilderSlot50 {
    std::uint8_t pad0x00[0x48];       // +0x00..+0x47 padding
    RefCountedObj* obj0x48;           // +0x48: pointer to refcounted object (R, 0x663f9dc)
    std::uint8_t releaseFlag0x50;     // +0x50: u8 flag, compared with 1 then written 0 (R/W, 0x663f9d6/0x663fa19)
};

// Refcounted object layout. Only offsets the function touches are declared.
struct RefCountedObj {
    void** vtable;                    // +0x00: vtable pointer (R, 0x663f9eb / 0x663fa06)
    std::uint32_t refcount1;          // +0x08: first refcount, interlocked dec (RW, 0x663f9e5)
    std::uint32_t refcount2;          // +0x0C: second refcount, interlocked dec (RW, 0x663fa00)
    // vtable[0] invoked via call at 0x663f9f7, vtable[1] via call at 0x663fa10
    // (both through data slot [0xF99FFA0] = sub_eea6040, a jmp rax thunk)
};

static_assert(offsetof(FrameBuilderSlot50, obj0x48) == 0x48,
              "sub_663f9d0: a1+0x48 is the object pointer field (R, 0x663f9dc)");
static_assert(offsetof(FrameBuilderSlot50, releaseFlag0x50) == 0x50,
              "sub_663f9d0: a1+0x50 is the release flag field (R/W, 0x663f9d6/0x663fa19)");
static_assert(offsetof(RefCountedObj, vtable) == 0x00,
              "sub_663f9d0: refcounted object vtable at +0x00 (R, 0x663f9eb/0x663fa06)");
static_assert(offsetof(RefCountedObj, refcount1) == 0x08,
              "sub_663f9d0: refcounted object refcount1 at +0x08 (RW, 0x663f9e5)");
static_assert(offsetof(RefCountedObj, refcount2) == 0x0C,
              "sub_663f9d0: refcounted object refcount2 at +0x0C (RW, 0x663fa00)");

} // namespace native

// Exact x64 Microsoft ABI mirror of the original function.
// RCX = entry argument 1 (dead, never read), RDX = a1 (FrameBuilderSlot50*), return = void.
namespace native {
void sub_663f9d0(void* dead_rcx, FrameBuilderSlot50* a1);
} // namespace native
