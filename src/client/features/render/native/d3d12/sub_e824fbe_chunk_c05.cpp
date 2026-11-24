// LIFT 0xe824fbe size 0x8525 1.26.62.01 sub_e824fbe
// CHUNK 0xe82c765..0xe82d4c4
#include "client/features/render/native/d3d12/sub_e824fbe_chunk_c05.h"

#if 0
0xe82c7d6  call qword ptr [0xF99FFA0]
0xe82c870  call qword ptr [0xF99FFA0]
0xe82c96b  call qword ptr [0xF99FFA0]
0xe82c9bb  call r10
0xe82ca5c  call qword ptr [0xF99FFA0]
0xe82caaf  call r10
0xe82cb8b  call 0xE81B4D0
0xe82cc6c  call qword ptr [0xF99FFA0]
0xe82cd02  call 0xEBCE430
0xe82cdc2  call 0xEBCE430
0xe82cf98  call qword ptr [0xF99FFA0]
0xe82cfc1  call 0xE81B720
0xe82cfde  call 0xE81B720
0xe82d01e  call qword ptr [0xF99FFA0]
0xe82d079  call r10
0xe82d0f6  call 0xE81B720
0xe82d12b  call 0xE81B720
0xe82d148  call 0xE81B720
0xe82d179  call 0xEBDB740
0xe82d198  call 0xE81D850
0xe82d1f2  call qword ptr [0xF99FFA0]
0xe82d28d  call r10
0xe82d2ec  call r10
0xe82d3d0  call r10
0xe82d458  call r10
0xe82d4be  call 0xEEC59E0
#endif

namespace native {
namespace d3d12 {

// 0xe82c765..0xe82d4c4
static inline void sub_e824fbe_chunk_c05(ChunkState_e824fbe_c05& s) {
    // 0xe82c765..0xe82d4c4: chunk 6/7 body; see dossier.
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

LIFT_FN(sub_e824fbe_chunk_c05, 0xe82c765)

static_assert(true, "sub_e824fbe chunk c05 placeholder");
