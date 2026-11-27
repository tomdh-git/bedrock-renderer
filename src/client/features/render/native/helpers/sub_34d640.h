#pragma once
#include <cstdint>
#include <cstddef>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_34d640 (0x34d640, size 0x39, 1.26.62.01).
//
// Observed field accesses, all from the disassembly of 0x34d640..0x34d679:
//   0x34d646  cmp byte ptr [rcx+0x19],0        ; entry node->b19 != 0 => return
//   0x34d650  mov rcx,[rsi+0x10]               ; node->p10, recursed into (first child)
//   0x34d659  mov rdi,[rsi]                    ; node->p0 (next sibling)
//   0x34d669  cmp byte ptr [rdi+0x19],0        ; sibling->b19 != 0 => stop walking
//
// No game struct is known from SDK headers for this node; the layout below is
// reconstructed from the observed offsets. Field names are offset-based (p0/p10/b19),
// no semantics are claimed. Offsets are [V] from the disassembly.
struct Sub34d640Node {
    Sub34d640Node* p0;   // +0x00 next-sibling pointer
    Sub34d640Node* p10;  // +0x10 first-child pointer
    uint8_t b19;         // +0x19 done byte
};
static_assert(offsetof(Sub34d640Node, p0)  == 0x00, "sub_34d640: node->p0 at +0x00");
static_assert(offsetof(Sub34d640Node, p10) == 0x10, "sub_34d640: node->p10 at +0x10");
static_assert(offsetof(Sub34d640Node, b19) == 0x19, "sub_34d640: node->b19 at +0x19");

namespace native {

// sub_34d640 (0x34d640, 0x39 bytes, 1.26.62.01): argument `node` arrives in RCX,
// returns void. x64 Microsoft ABI. Reads node fields only; writes no game memory.
void sub_34d640(Sub34d640Node* node);

} // namespace native
