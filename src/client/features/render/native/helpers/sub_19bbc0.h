#pragma once
#include <cstdint>
#include <cstddef>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_e935700 (lift/set): void* sub_e935700(void*) — forward-declared here
// (not via sub_e935700.h, which has a pre-existing empty-struct sizeof static_assert bug).
namespace native {

void* sub_e935700(void* a0);

} // namespace native

// sub_19bbc0 (0x19bbc0, size 0xce, 1.26.62.01).
// Releases two refcounted string members: string 1 at a0+0x20 (data), a0+0x38 (size),
// cap at a0+0x30; string 2 at a0+0x00 (data), a0+0x18 (size), cap at a0+0x10.
// Proceeds only if byte at a0+0x40 == 1. Each heap member is released via sub_e935700
// (argument = data pointer when size+1 < 0x1000, else argument = [data-8] refcount,
// unless data-8-refcount >= 0x20 which takes the slow path through data slot 0xF9A8C78
// and does not return). After release, each member is reset to SSO state (cap=0,
// size=0xF, data=nullptr).
//
// Field offsets observed in the disassembly of 0x19bbc0:
//   a0+0x00  void*   string 2 data pointer
//   a0+0x10  size_t  string 2 capacity
//   a0+0x18  size_t  string 2 size
//   a0+0x20  void*   string 1 data pointer
//   a0+0x30  size_t  string 1 capacity
//   a0+0x38  size_t  string 1 size
//   a0+0x40  uint8   proceed flag (must == 1)
//
// Callees:
//   sub_e935700 (lift/set): void* sub_e935700(void*) — declared in sub_e935700.h.
//   call qword ptr [0xF9A8C78] (slow path only): indirect call through data slot,
//     not in native_boundary.tsv or native_functions.tsv. Called as a function pointer
//     with all arguments zeroed; return value unused (int3 follows, noreturn).
//
// No shared headers or Sigs.json are edited; all layout constants are asserted here.

struct sub_19bbc0Layout {
    static constexpr std::size_t kString2DataOffset = 0x00;   // a0+0x00: string 2 data pointer
    static constexpr std::size_t kString2CapOffset  = 0x10;   // a0+0x10: string 2 capacity
    static constexpr std::size_t kString2SizeOffset = 0x18;   // a0+0x18: string 2 size
    static constexpr std::size_t kString1DataOffset = 0x20;   // a0+0x20: string 1 data pointer
    static constexpr std::size_t kString1CapOffset  = 0x30;   // a0+0x30: string 1 capacity
    static constexpr std::size_t kString1SizeOffset = 0x38;   // a0+0x38: string 1 size
    static constexpr std::size_t kFlagOffset        = 0x40;   // a0+0x40: proceed flag (must == 1)
    static_assert(kString2DataOffset == 0x00, "sub_19bbc0: string 2 data at a0+0x00");
    static_assert(kString2CapOffset == 0x10, "sub_19bbc0: string 2 capacity at a0+0x10");
    static_assert(kString2SizeOffset == 0x18, "sub_19bbc0: string 2 size at a0+0x18");
    static_assert(kString1DataOffset == 0x20, "sub_19bbc0: string 1 data at a0+0x20");
    static_assert(kString1CapOffset == 0x30, "sub_19bbc0: string 1 capacity at a0+0x30");
    static_assert(kString1SizeOffset == 0x38, "sub_19bbc0: string 1 size at a0+0x38");
    static_assert(kFlagOffset == 0x40, "sub_19bbc0: proceed flag at a0+0x40");
    static_assert(sizeof(void*) == 8, "sub_19bbc0: x64 ABI, pointer-sized address space");
};

namespace native {

// sub_19bbc0: x64 Microsoft ABI, arg1 (RCX) = context pointer a0, return void.
void sub_19bbc0(void* a0);

} // namespace native
