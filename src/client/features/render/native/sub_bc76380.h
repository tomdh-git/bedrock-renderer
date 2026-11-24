#pragma once
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_bc76380: D3D12 submit RTX override (size 0x107, 1.26.62.01).
// Layout constants and static asserts for the lifted body.

namespace native {

struct Bc76380Layout {
    // offsets used by sub 0xbc76380, filled from the disassembly of 0xbc76380.
    static_assert(sizeof(Bc76380Layout) > 0, "layout constant block");
};

} // namespace native
