#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_e935700 is lift set; forward-declared here rather than including sub_e935700.h
// (that unit's header has a static_assert on its own incomplete layout type that MSVC
// rejects). Signature matches sub_e935700.h exactly: void* sub_e935700(void* a0).
namespace native {
void* sub_e935700(void* a0);
} // namespace native

// sub_1a459d0 (0x1a459d0, size 0xb9 bytes, 1.26.62.01).
// Teardown of the object passed in RCX (this). All offsets below are [V] from the
// disassembly of 0x1a459d0 ([0x1a459d0, 0x1a45a89)):
//   this + 0x10  void* buffer   [R] heap buffer pointer; [W] byte 0x10 = 0 at reset (one byte only)
//   this + 0x20  u64            [W] = 0 at reset
//   this + 0x28  u64 size       [R/W] buffer size
//   this + 0x38  void* object   [R] refcounted object owned by this
// The refcounted object (*(this + 0x38)) layout:
//   + 0x00 void* vfptr          [R] vfptr[0] = destructor, vfptr[1] = operator delete
//   + 0x08 u32  refs            [R/W] lock dec dword ptr [object + 8]
//   + 0x0C u32  refs0x0c        [R/W] lock dec dword ptr [object + 0xC]
// Calls [V]:
//   0x1a459f1 call qword ptr [0xF99FFA0]  -> sub_eea6040 (boundary/vendor, native_boundary.tsv row 0xeea6040,
//                                          reached through boundary::g_eea6040_thunk)
//   0x1a45a07 call qword ptr [0xF99FFA0]  -> same
//   0x1a45a43 call 0xE935700              -> native::sub_e935700 (lift set, declared in sub_e935700.h)
//   0x1a45a6a jmp 0xE935700               -> native::sub_e935700 (tail call; the function's return value)
//   0x1a45a82 call qword ptr [0xF9A8C78]  -> failfast path; target read from the data slot at call time
//                                          (brief rule 68: indirect call through a data slot)
// x64 Microsoft ABI: argument (this) in RCX; result in RAX (result of the tail call to
// sub_e935700; sub_e935700 returns void* [V: sub_e935700.h]).

struct sub_1a459d0_refcounted {
    void* vfptr;                    // + 0x00 [R] vfptr
    std::uint32_t refs0x08;         // + 0x08 [R/W] lock dec dword
    std::uint32_t refs0x0c;         // + 0x0C [R/W] lock dec dword
};

struct sub_1a459d0_this {
    std::uint8_t pad0x00[0x10];     // + 0x00
    void* buffer;                   // + 0x10 [R/W] heap buffer pointer
    std::uint8_t pad0x18[0x20 - 0x18];
    std::uint64_t field0x20;        // + 0x20 [W]
    std::uint64_t size;             // + 0x28 [R/W]
    std::uint8_t pad0x30[0x38 - 0x30];
    void* object;                   // + 0x38 [R] refcounted object
    std::uint8_t pad0x40[0x48 - 0x40];
};

struct sub_1a459d0Layout {
    static_assert(offsetof(sub_1a459d0_refcounted, vfptr) == 0x00, "sub_1a459d0_refcounted: vfptr at +0x00");
    static_assert(offsetof(sub_1a459d0_refcounted, refs0x08) == 0x08, "sub_1a459d0_refcounted: refs0x08 at +0x08");
    static_assert(offsetof(sub_1a459d0_refcounted, refs0x0c) == 0x0c, "sub_1a459d0_refcounted: refs0x0c at +0x0c");
    static_assert(offsetof(sub_1a459d0_this, buffer) == 0x10, "sub_1a459d0_this: buffer at +0x10");
    static_assert(offsetof(sub_1a459d0_this, field0x20) == 0x20, "sub_1a459d0_this: field0x20 at +0x20");
    static_assert(offsetof(sub_1a459d0_this, size) == 0x28, "sub_1a459d0_this: size at +0x28");
    static_assert(offsetof(sub_1a459d0_this, object) == 0x38, "sub_1a459d0_this: object at +0x38");
    static_assert(sizeof(void*) == 8, "sub_1a459d0: x64 pointer-sized arguments (Microsoft x64 ABI)");
    static constexpr std::uintptr_t kThunkSlotRva = 0xF99FFA0;   // call qword ptr [0xF99FFA0] -> sub_eea6040 thunk slot
    static constexpr std::uintptr_t kFailfastSlotRva = 0xF9A8C78; // call qword ptr [0xF9A8C78] (failfast path)
    static_assert(kThunkSlotRva == 0xF99FFA0, "sub_1a459d0: thunk data slot RVA 0xF99FFA0");
    static_assert(kFailfastSlotRva == 0xF9A8C78, "sub_1a459d0: failfast data slot RVA 0xF9A8C78");
};

namespace native {
namespace boundary {

// sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0; native_boundary.tsv row 0xeea6040).
// The thunk at 0xeea6040 is a one-byte `jmp rax`; g_eea6040_thunk(RCX = object, RDX = target funcptr)
// moves RDX into RAX and jumps through the data slot, so the net effect is target(object).
using eea6040_fn = void(*)(void* rcx, void* rdx);
extern eea6040_fn g_eea6040_thunk;   // resolved from Sigs.json at install

} // namespace boundary

// sub_1a459d0(void* a0) -> void*
//   a0 (this) arrives in RCX. Every returning path ends with the tail call
//   native::sub_e935700(a0) (0x1a45a6a jmp 0xE935700); the return value is that call's result [V].
void* sub_1a459d0(void* a0);

} // namespace native
