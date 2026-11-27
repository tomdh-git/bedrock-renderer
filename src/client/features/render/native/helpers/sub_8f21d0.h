#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_8f21d0 (0x8f21d0, size 0xe3, 1.26.62.01, sub_8f21d0).
//
// Releases the slot buffer and its elements of the context object a0 (RCX):
//   1. calls sub_7705b0(a0, &local{0xEFCA680, 0x873D0});
//   2. for each pointer in [a0+0x150, a0+0x158) step 8: calls sub_8f22e0(ptr);
//   3. releases the buffer at [a0+0x150] (size = [a0+0x160] - [a0+0x150]) via sub_e935700,
//      or via the noreturn data-slot indirect call at 0xF9A8C78 when the heap-geometry
//      check fails; then zeroes [a0+0x150], [a0+0x158], [a0+0x160];
//   4. calls sub_7727b0(a0) and returns.
//
// Layout of the context object (a0 = RCX):
//   a0+0x150  void*  buffer start        (read at 0x8f220e, 0x8f2241, 0x8f2257)
//   a0+0x158  void*  buffer end          (read at 0x8f2221)
//   a0+0x160  void*  buffer end2 (size)  (read at 0x8f2244)
struct SlotCtx {
    std::uint8_t _pad_0x00[0x150];
    void* buffer_start;   // +0x150
    void* buffer_end;     // +0x158
    void* buffer_end2;    // +0x160
};

static_assert(offsetof(SlotCtx, buffer_start) == 0x150, "sub_8f21d0: buffer_start at +0x150");
static_assert(offsetof(SlotCtx, buffer_end) == 0x158, "sub_8f21d0: buffer_end at +0x158");
static_assert(offsetof(SlotCtx, buffer_end2) == 0x160, "sub_8f21d0: buffer_end2 at +0x160");
static_assert(sizeof(void*) == 8, "sub_8f21d0: x64 ABI, pointer-sized address space");

// sub_e935700 (lift/set): void* sub_e935700(void*) - called via its native symbol.
void* sub_e935700(void* a0);

// Callees outside both docs/data/native_functions.tsv and docs/data/native_boundary.tsv.
// Forward-declared only; signatures are best-effort (return value unused by sub_8f21d0).
// These callees are outside both docs/data/native_functions.tsv and
// docs/data/native_boundary.tsv (callee not yet classified; see docs/progress/oc_U-EX7.8f21d0.md).
void sub_7705b0(void* a0, void* param);
void sub_8f22e0(void* elem);
void sub_7727b0(void* a0);

namespace native {

// sub_8f21d0: x64 Microsoft ABI, arg1 (RCX) = context pointer a0, returns void.
// The slow path (0x8f2299) is noreturn (int3 after the data-slot indirect call).
void sub_8f21d0(void* a0);

} // namespace native
