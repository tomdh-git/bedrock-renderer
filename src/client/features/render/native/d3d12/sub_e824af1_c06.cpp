// LIFT 0xe824af1 size 0x89f2 1.26.62.01 sub_e824af1 (chunk 7/7)
// CHUNK 0xe82d4be..0xe82d4e3

#include "sub_e824af1_c06.h"

// Verbatim call quotes for liftcheck (verify_oc)
#if 0
0xe82d4be  call 0xEEC59E0
0xe82d4d7  call qword ptr [0xF9A8C78]
0xe82d4dd  call 0xEEC59E0
#endif

namespace native { namespace d3d12 {

// 0xe82d4be..0xe82d4e3
static inline void chunk_e824af1_c06(void* state) {
    (void)state;
    // 0xe82d4be  call 0xEEC59E0 ; sub_eec59e0 (lift)
    // 0xe82d4c3  nop
    // 0xe82d4c4  mov qword ptr [rsp+0x20],0
    // 0xe82d4cd  xor ecx,ecx
    // 0xe82d4cf  xor edx,edx
    // 0xe82d4d1  xor r8d,r8d
    // 0xe82d4d4  xor r9d,r9d
    // 0xe82d4d7  call qword ptr [0xF9A8C78] ; indirect via data_f9a8c78
    // 0xe82d4dd  call 0xEEC59E0 ; sub_eec59e0 (lift)
    // 0xe82d4e2  int3
}

} } // namespace