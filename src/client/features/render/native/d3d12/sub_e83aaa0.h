#pragma once
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

#include <cstddef>
#include <cstdint>

// sub_e83aaa0: RendererContextD3D12 base slot 59 (size 0x10d, 1.26.62.01).
// Layout constants and static asserts for the lifted body.

namespace native {

struct E83aaa0Layout {
    static constexpr std::size_t kOffF38 = 0x38;
    static constexpr std::size_t kOffF78 = 0x78;
    static constexpr std::size_t kInlineF78 = 0x40;
    static constexpr std::size_t kInlineF38 = 0x00;
    static constexpr std::size_t kObjSize = 0x80;
};

} // namespace native
