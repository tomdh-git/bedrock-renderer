// LIFT 0xe824fbe size 0x8525 1.26.62.01 sub_e824fbe
// CHUNK 0xe827fa3..0xe8297a2
#include "client/features/render/native/d3d12/sub_e824fbe_chunk_c02.h"

#if 0
0xe827fad  call 0x47E8F0
0xe82813e  call 0x47E8F0
0xe8281b9  call 0x47E8F0
0xe82821d  call 0x47E8F0
0xe8282a0  call 0x47E8F0
0xe82832c  call 0x47E8F0
0xe828661  call 0x47E8F0
0xe828983  call 0x47E8F0
0xe828a03  call 0x47E8F0
0xe828d30  call 0x47E8F0
0xe828d94  call 0x47E8F0
0xe828e0f  call 0x47E8F0
0xe828fb3  call 0x47E8F0
0xe82902e  call 0x47E8F0
0xe829088  call 0x47E8F0
0xe8290e2  call 0x47E8F0
0xe82913c  call 0x47E8F0
0xe82919c  call 0x47E8F0
0xe8291fc  call 0x47E8F0
0xe829256  call 0x47E8F0
0xe8292b0  call 0x47E8F0
0xe82930a  call 0x47E8F0
0xe829364  call 0x47E8F0
0xe8293be  call 0x47E8F0
0xe829418  call 0x47E8F0
0xe829472  call 0x47E8F0
0xe8294cc  call 0x47E8F0
0xe829526  call 0x47E8F0
0xe82953a  call 0xEEC6ED0
0xe829562  call 0xEEC6ED0
0xe829594  call 0xEEC6ED0
0xe8295c6  call 0xEEC6ED0
0xe8295f5  call 0xEEC6ED0
0xe829627  call 0xEEC6ED0
0xe82964f  call 0xEEC6ED0
0xe82968e  call 0xEEC6ED0
0xe8296b6  call 0xEEC6ED0
0xe8296ed  call 0xEEC6ED0
0xe829715  call 0xEEC6ED0
0xe829747  call 0xEEC6ED0
0xe829779  call 0xEEC6ED0
#endif

namespace native {
namespace d3d12 {

// 0xe827fa3..0xe8297a2
static inline void sub_e824fbe_chunk_c02(ChunkState_e824fbe_c02& s) {
    // 0xe827fa3..0xe8297a2: SIMD/matrix work + memcpy calls; see dossier.
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

LIFT_FN(sub_e824fbe_chunk_c02, 0xe827fa3)

static_assert(true, "sub_e824fbe chunk c02 placeholder");