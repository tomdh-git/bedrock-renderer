#pragma once
#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the 3-float vector argument (a0, rcx) read at [rcx]+0/+4/+8
// (0xbc5b1c7  movss xmm0,[rcx]; 0xbc5b1ad  movsd xmm1,[rcx+4];
//  0xbc5b1b2  movss xmm10,[rcx+8]) [V].
struct Vec3 {
    float x;
    float y;
    float z;
};
static_assert(sizeof(Vec3) == 12, "bc5b130: Vec3 is 12 bytes");
static_assert(offsetof(Vec3, z) == 8, "bc5b130: Vec3::z is at offset 8");

// a5 (rbx) is a read-only const float[3] read at offsets 0, 4, 8.
// a8 (r14) is a read-only const float[2+] read at offsets 0, 4 (and re-based
// by +4 in the z-block, still reading the same a8[1]) [V].

// Data constants loaded from .rdata by the original. The game was not running
// so their values could not be read; they are declared extern (no fabricated
// values) and used exactly as the original loads them. Addresses [V]:
extern const float kData_ef3f050;   // 0xbc5b1b8  movaps xmm8,[0xEF3F050]   ; [data_ef3f050]
extern const float kData_ef1d470;   // 0xbc5b1ee  movss  xmm0,[0xEF1D470]   ; [data_ef1d470]
extern const float kData_eec8060;   // 0xbc5b24e  movss  xmm10,[0xEEC8060]  ; [data_eec8060]
extern const float kData_eee7c00;   // 0xbc5b29e  movss  xmm14,[0xEEE7C00]  ; [data_eee7c00]
extern const float kData_ef3f048;   // 0xbc5b41f  addss  xmm0,[0xEF3F048]   ; [data_ef3f048]
extern const float kData_ef3f01c;   // 0xbc5b4a8  addss  xmm0,[0xEF3F01C]   ; [data_ef3f01c]

// sub 0xbc5b130: VV frame-graph builder. x64 Microsoft ABI:
//   rcx=a0 (const Vec3*), xmm1=a1 (float), xmm2=a2 (float), xmm3=a3 (float),
//   stack: a5 (const float*), a6 (float), a7 (float), a8 (const float*),
//   outR15 (float*), outRdi (float*). Return void [V].
//   Confirmed by callers sub_bc57460 at 0xbc57f69 and 0xbc583e0
//   (docs/data/listings/sub_bc57460.txt) [V].
void sub_bc5b130(const Vec3* a0, float a1, float a2, float a3,
                 const float* a5, float a6, float a7, const float* a8,
                 float* outR15, float* outRdi);

// Footprint of sub 0xbc5b130: the two 3-float output vectors the original
// writes through outR15 and outRdi (3 floats each = 12 bytes) [V].
native::Footprint sub_bc5b130_footprint(const Vec3* a0, float a1, float a2,
                                        float a3, const float* a5, float a6,
                                        float a7, const float* a8,
                                        float* outR15, float* outRdi);

} // namespace native
