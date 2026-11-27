#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_675b550 (0x675b550, size 0xc8, 1.26.62.01, "BgfxFrameBuilder::endFrame").
//
// 'this' (RCX) is a BgfxFrameBuilder object. The function appends one default
// entry to the frame command buffer held at this+0x10 (a std::vector<FrameEntry>):
//   this+0x10 : vector object (_Myfirst at +0x00, _Mylast at +0x08, _Myend at +0x10)
//   this+0x18 : vector._Mylast  (R, current end pointer)
//   this+0x20 : vector._Myend   (R, capacity end)
// FrameEntry is 0x58 bytes; the appended entry is:
//   +0x00..0x0F: 16 bytes from data section RVA 0xF2BE858 (VA 0x152BE858)
//   +0x10..0x1F: 16 bytes from data section RVA 0xF2BE868 (VA 0x152BE868)
//   +0x50:       byte 0
// When the buffer is full the original calls sub_b0ad0 (STL vector growth /
// push_back, class stl boundary) which is replaced by std::vector::push_back.
// Returns 'this' (RAX).
//
// The function also contains unreachable dead code: a post-growth block that
// reads uninitialized stack slots [rbp-0x18]/[rbp-0x30] (only entered if [rbp]
// == 1, which push_back never sets) and a stack-cookie failure path that
// calls the handler at data slot 0xF9A8C78 then int3. These are translated for
// instruction coverage but cannot be reached.

namespace native {

// Offsets within 'this' (RCX) [V]
static constexpr std::size_t kObjOffsetVector  = 0x10;  // this+0x10: std::vector<FrameEntry> object (R)
static constexpr std::size_t kObjOffsetMylast  = 0x18;  // this+0x18: vector._Mylast   (R)
static constexpr std::size_t kObjOffsetMyend   = 0x20;  // this+0x20: vector._Myend    (R)

// Vector element size [V: 0x675b59b add qword ptr [rsi+0x18],0x58]
static constexpr std::size_t kEntrySize = 0x58;

// Frame buffer entry, 0x58 bytes [V]
struct FrameEntry {
    std::uint8_t data[0x58];
};
static_assert(sizeof(FrameEntry) == kEntrySize, "sub_675b550: FrameEntry size is 0x58");

// Data-section constants (16 bytes each, image base 0x140000000 -> VA = RVA + 0x140000000) [V]
static constexpr std::uintptr_t kDataF2BE858 = 0x152BE858ULL; // [data_f2be858], copied to entry+0x00
static constexpr std::uintptr_t kDataF2BE868 = 0x152BE868ULL; // [data_f2be868], copied to entry+0x10

// Failure-handler data slot for the unreachable stack-cookie path [V: 0x675b611 call qword ptr [0xF9A8C78]]
static constexpr std::uintptr_t kFailureHandlerSlot = 0x159A8C78ULL;

// Stack frame offsets used by the unreachable dead code [V]
static constexpr std::size_t kStackFlagOffset    = 0x00;   // [rbp+0x00]  byte flag, written 0 at entry
static constexpr std::size_t kStackCookieOffset  = 0x10;   // [rbp+0x10]  = 0xFFFFFFFFFFFFFFFE (dead store)
static constexpr std::size_t kStackSizeOutOffset = 0x18;   // [rbp-0x18]  read only if flag == 1 (uninitialized)
static constexpr std::size_t kStackPtrOutOffset  = 0x30;   // [rbp-0x30]  read only if flag == 1 (uninitialized)

// sub_e935700 (0xE935700, class lift, docs/data/native_boundary.tsv line 505):
// tail jump to sub_392960; argument in RCX, result in RAX. Forward-declared
// here and called through its native symbol (lift-set callee, not a boundary).
void* sub_e935700(void* a0);

// Exact x64 Microsoft ABI mirror of the original function.
// RCX = this (BgfxFrameBuilder*), return = this (in RAX).
void* sub_675b550(void* a0);

} // namespace native
