// LIFT 0xe824fbe size 0x8525 1.26.62.01 sub_e824fbe
// CHUNK 0xe82d4c4..0xe82d4e3
#include "client/features/render/native/d3d12/sub_e824fbe_c06.h"

#if 0
0xe82d4d7  call qword ptr [0xF9A8C78]
0xe82d4dd  call 0xEEC59E0
#endif

namespace native {
namespace d3d12 {

// 0xe82d4c4..0xe82d4e3
static inline void sub_e824fbe_chunk_c06(ChunkState_e824fbe_c06& s) {
    // 0xe82d4c4  mov qword ptr [rsp+0x20],0
    // 0xe82d4cd  xor ecx,ecx
    // 0xe82d4cf  xor edx,edx
    // 0xe82d4d1  xor r8d,r8d
    // 0xe82d4d4  xor r9d,r9d
    // 0xe82d4d7  call qword ptr [0xF9A8C78]
    // 0xe82d4dd  call 0xEEC59E0
    // 0xe82d4e2  int3
    (void)s;
}

} // namespace d3d12
} // namespace native

#define LIFT_FN(name, rva) \
    namespace native { namespace registry { \
    struct name##_entry { \
        static constexpr uintptr_t rva = rva; \
        static constexpr const char* symbol = #name; \
        static constexpr int mode = 2; \
        name##_entry() { } \
    }; \
    static name##_entry name##_instance; \
    } }

LIFT_FN(sub_e824fbe_chunk_c06, 0xe82d4c4)

static_assert(true, "sub_e824fbe chunk c06 placeholder");