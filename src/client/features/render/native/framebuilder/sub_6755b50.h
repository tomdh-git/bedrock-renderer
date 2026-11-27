#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_6755b50 (0x6755b50, size 0xe2, 1.26.62.01, "BgfxFrameBuilder slot 11").
//
// Releases up to three refcounted objects owned by the container passed in R8
// (slots at +0x38, then +0x28, then +0x8; RCX == 2 skips straight to +0x8),
// gated on bit (RCX & 31) of the 0x33 mask being clear. Each object (*RSI) has
// two atomic refcounts (+0x08 and +0x0C); when a count hits zero the
// corresponding virtual entry (vfptr[0] / vfptr[1]) is invoked through
// `call qword ptr [0xF99FFA0]`, where data slot 0xF99FFA0 holds sub_eea6040,
/// a `jmp rax` thunk (boundary/vendor, native_boundary.tsv row 0xeea6040).
// The final slot's second count ends in a tail call through the same data slot
// (0x6755c2f `mov rdx,[0xF99FFA0]` / `jmp rdx`).
//
// Layout observed in the disassembly of [0x6755b50, 0x6755c32):
//   0x6755b6e  mov rsi,[r8+0x38]   (R: container+0x38, slot 1 object)
//   0x6755bab mov rsi,[r8+0x28]   (R: container+0x28, slot 2 object)
//   0x6755be8 mov rsi,[r8+8]      (R: container+0x08, slot 3 object)
//   object+0x00: vfptr [R]          0x6755b7d mov rax,[rsi] ; 0x6755b80 mov rax,[rax]
//   object+0x08: u32 refcount [R/W] 0x6755b77 lock dec dword ptr [rsi+8]
//   object+0x0C: u32 refcount [R/W] 0x6755b92 lock dec dword ptr [rsi+0xC]
// Only the fields used by this function are declared; nothing else about the
// layouts is assumed.
namespace native {

struct Sub6755b50Object {   // *RSI: refcounted object owned by a container slot
    void* vfptr;                     // +0x00 [R] vfptr; [rax] = vfptr[0] / [rax+8] = vfptr[1] loaded before each thunk call
    std::uint32_t refs0x08;          // +0x08 [R/W] lock dec dword ptr [object + 8]
    std::uint32_t refs0x0c;          // +0x0C [R/W] lock dec dword ptr [object + 0xC]
};

struct Sub6755b50Container {   // *R8
    std::uint8_t _pad_0x00[0x08];  // +0x00 unused by this function
    void* slot0x08;                // +0x08 [R] slot 3 object (processed last)
    std::uint8_t _pad_0x10[0x28 - 0x10];  // +0x10..+0x27 unused by this function
    void* slot0x28;                // +0x28 [R] slot 2 object
    std::uint8_t _pad_0x30[0x38 - 0x30];  // +0x30..+0x37 unused by this function
    void* slot0x38;                // +0x38 [R] slot 1 object (processed first)
};
static_assert(offsetof(Sub6755b50Object, vfptr) == 0x00, "6755b50: Sub6755b50Object::vfptr at +0x00");
static_assert(offsetof(Sub6755b50Object, refs0x08) == 0x08, "6755b50: Sub6755b50Object::refs0x08 at +0x08");
static_assert(offsetof(Sub6755b50Object, refs0x0c) == 0x0c, "6755b50: Sub6755b50Object::refs0x0c at +0x0c");
static_assert(offsetof(Sub6755b50Container, slot0x08) == 0x08, "6755b50: Sub6755b50Container::slot0x08 at +0x08");
static_assert(offsetof(Sub6755b50Container, slot0x28) == 0x28, "6755b50: Sub6755b50Container::slot0x28 at +0x28");
static_assert(offsetof(Sub6755b50Container, slot0x38) == 0x38, "6755b50: Sub6755b50Container::slot0x38 at +0x38");
static_assert(sizeof(void*) == 8, "6755b50: x64 pointer-sized fields (Microsoft x64 ABI)");

// sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0;
// native_boundary.tsv row 0xeea6040). The thunk at 0xeea6040 is `jmp rax`;
// call sites load the target into RAX (vfptr[0] or vfptr[1]) and RCX = object.
// The wrapper forwards (object, target entry) exactly as the original's
// `call qword ptr [0xF99FFA0]` does (RDX/R8/R9 pass-throughs are not read by
// the thunk). Return value is never observed by this function.
namespace boundary {
using eea6040_fn = void(*)(void* rcx, void* rdx);
extern eea6040_fn g_eea6040_thunk;   // resolved from Sigs.json at install (symbol sub_eea6040)
} // namespace boundary

// x64 Microsoft ABI: RCX = bit index tested against mask 0x33 (a1), R8 =
// container pointer. RDX/R9 are only forwarded into the noreturn thunk calls
// and are otherwise unread. Return value: none observable (RAX is scratch
// throughout; the epilogue returns with whatever RAX holds).
void sub_6755b50(std::uintptr_t a1, void* container);

} // namespace native
