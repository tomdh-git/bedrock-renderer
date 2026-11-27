#pragma once
#include <cstdint>
#include <cstddef>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_aaa6e0 (0xaaa6e0, size 0xd7, 1.26.62.01).
//
// Field offsets touched ([V]: rdis dis 0xaaa6e0; exact listing in docs/progress/pack/aaa6e0.md):
//   a0+0x0          R  pointer P = [a0]                                            (0xaaa6f1, 0xaaa782)
//   P+0x8           R/W  [P+8] = 0                                                 (0xaaa6f4, 0xaaa6f8)
//   P+0x0           R  rdi = [P]                                                    (0xaaa6ff)
//   rdi+0x178       R/W                                                          (0xaaa749 read; 0xaaa710 lea; 0xaaa71c/0xaaa720 write)
//   rdi+0x180       W  [rdi+0x180] = 0                                             (0xaaa720)
//   rdi+0x18        R  passed as RCX to sub_a89240                                 (0xaaa728)
//   rdi+0x188       R  [rdi+0x188]                                                 (0xaaa755)
//   [rcx-8]         R  where rcx was [rdi+0x178]                                  (0xaaa768)
//
// The offsets are byte offsets into pointer-chained objects (a0 -> P=[a0] -> rdi=[P]);
// no single game struct is defined by this function. Only the x64 ABI contract is
// asserted: argument a0 in RCX, result in RAX (tail call to sub_e935700).
struct sub_aaa6e0Layout {
    static_assert(sizeof(void*) == 8, "sub_aaa6e0: x64 ABI, pointer argument in RCX, result in RAX");
};

namespace native {

// sub_aaa6e0: a0 in RCX, result in RAX. Returns void* (tail call to sub_e935700
// on every returning path; the other path is noreturn via data slot 0xF9A8C78).
void* sub_aaa6e0(void* a0);

} // namespace native
