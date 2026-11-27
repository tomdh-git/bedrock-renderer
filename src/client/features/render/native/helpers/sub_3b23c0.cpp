// LIFT 0x3b23c0 size 0x8 1.26.62.01 sub_3b23c0
#include "sub_3b23c0.h"

namespace native {

// sub_3b23c0 (0x3b23c0, size 0x8, 1.26.62.01): returns &data_128cc490 in RAX.
//   0x3b23c0  lea rax,[0x128CC490]   ; RAX = &data_128cc490
//   0x3b23c7  ret
std::uint64_t* sub_3b23c0(void)
{
    // 0x3b23c0..0x3b23c8  lea rax,[0x128CC490] ; ret   (returns &data_128cc490 in RAX)
    return reinterpret_cast<std::uint64_t*>(sub_3b23c0Layout::kGlobalDataRva);
}

#if 0
0x3b23c0  lea rax,[0x128CC490]
0x3b23c7  ret
#endif

LIFT_FN(sub_3b23c0, "sub_3b23c0", 0x3B23C0, sub_3b23c0, nullptr);

} // namespace native
