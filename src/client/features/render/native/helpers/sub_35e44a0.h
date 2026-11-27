#pragma once
#include <cstdint>
#include <cstddef>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_35e44a0 (0x35e44a0, size 0x39, 1.26.62.01): recursive node walker.
// Fields read by the function (all [V] from disassembly of 0x35e44a0):
//   +0x00  void*       field0x0   read as [rsi] then [rdi] (child pointer)
//   +0x10  void*       next0x10   read as [rsi+0x10] (sibling/next pointer, recursed into)
//   +0x19  uint8_t     flag0x19   read as [rcx+0x19] and [rdi+0x19] (compared against 0)
struct sub_35e44a0_node {
    void*       field0x0;   // +0x00
    uint8_t     pad0x08[0x10 - 0x08]; // +0x08..0x0f not read
    void*       next0x10;   // +0x10
    uint8_t     pad0x18[0x19 - 0x18]; // +0x18
    uint8_t     flag0x19;   // +0x19
};
static_assert(offsetof(sub_35e44a0_node, field0x0) == 0x00, "sub_35e44a0: field0x0 at +0x00");
static_assert(offsetof(sub_35e44a0_node, next0x10) == 0x10, "sub_35e44a0: next0x10 at +0x10");
static_assert(offsetof(sub_35e44a0_node, flag0x19) == 0x19, "sub_35e44a0: flag0x19 at +0x19");
static_assert(sizeof(sub_35e44a0_node) >= 0x1a, "sub_35e44a0: node size at least up to flag0x19");

namespace native {

// sub_e935700 (0xe935700, size 0x5, 1.26.62.01): tail jump to sub_392960.
// Lift-set callee, forward-declared with its exact ABI (one argument in RCX, returns void*).
// The call site at 0x35e44c4 passes RDX=0x40, but sub_392960 overwrites RDX immediately
// (0x392972 mov rdx,rcx), so the second argument is dead.
void* sub_e935700(void* a0);

// sub_35e44a0 (0x35e44a0, size 0x39, 1.26.62.01): recursive walk, calls self and sub_e935700.
// ABI: argument in RCX, returns void, callee-saved RSI/RDI.
void sub_35e44a0(sub_35e44a0_node* a0);

} // namespace native