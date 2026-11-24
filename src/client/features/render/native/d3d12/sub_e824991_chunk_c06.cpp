// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991
// CHUNK 0xe82d4dd..0xe82d4e3

#include "sub_e824991_chunk_c06.h"

namespace native {
namespace d3d12 {

// Verbatim call quotes for liftcheck (plain lines for verify_oc)
#if 0
0xe82d4dd  call 0xEEC59E0
#endif

// 0xe82d4dd..0xe82d4e3
// Tail: call sub_eec59e0; int3 (unreachable trap). Function ends.
static inline void chunk_step(ChunkState_e824991_c06& s) {
    // 0xe82d4dd  call 0xEEC59E0
    sub_eec59e0();
    // 0xe82d4e2  int3
    // 0xe82d4e3  nop (function end)
}

void sub_e824991_chunk_c06(ChunkState_e824991_c06& state) {
    chunk_step(state);
}

static const void* LIFT_FN_sub_e824991_chunk_c06 = reinterpret_cast<void*>(sub_e824991_chunk_c06);

} // namespace d3d12
} // namespace native
