#pragma once
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_568cd70: tail-jump thunk to sub_568cd90 / FrameGraph::viewSetupTask (size 0xc, 1.26.62.01).
// Layout constants and static asserts for the lifted body.
//
// The body ([0x568cd70, 0x568cd7c)) is register-only:
//   0x568cd70  mov rcx,rdx
//   0x568cd73  mov rdx,r8
//   0x568cd76  jmp 0x568CD90
//   0x568cd7b  int3     (pad byte inside the 0xc-byte body; unreachable)
// It touches no struct fields, so there are no field offsets to assert; the ABI
// constant below is asserted instead.

namespace native {

// Layout constants used by sub_568cd70. The thunk moves register arguments only;
// no memory layout is read or written.
struct Sub568cd70Layout {
    // x64 Microsoft ABI: every register argument is an 8-byte general-purpose register.
    static_assert(sizeof(void*) == 8, "sub_568cd70: x64 register arguments are 8 bytes");
};

// Forward declaration of the tail-jump target.
// 0x568cd90 is in the lift set (docs/data/native_functions.tsv, D2,
// native symbol FrameGraph::viewSetupTask, docs/functions/568cd90.md) and is
// lifted by its own unit; this unit only calls it through the forward declaration.
// Signature recovered from docs/functions/568cd90.md [V]: rcx = view/pass object,
// rdx = pass state object (>= 0xF8 bytes), return void.
// Sub_568cd70 forwards (target rcx = its rdx, target rdx = its r8); r8, r9 and the
// stack arguments are never touched, so they arrive at sub_568cd90 unchanged, and
// the tail jump passes the void return straight through.
void sub_568cd90(void* view, void* state);

// Lifted body of sub_568cd70 (tail-jump thunk to sub_568cd90).
void sub_568cd70(void* a0 /* dropped by the thunk */, void* view, void* state);

} // namespace native
