// LIFT 0xbc5b130 size 0x472 1.26.62.01 VV frame-graph builder
#include "client/features/render/native/bgfx/sub_bc5b130.h"

#include "client/features/render/native/Lift.h"

#include <bit>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

namespace native {

static_assert(sizeof(std::uintptr_t) == 8, "bc5b130: std::uintptr_t is 8 bytes");
static_assert(sizeof(float) == 4, "bc5b130: float is 4 bytes");
static_assert(sizeof(Vec3) == 12, "bc5b130: Vec3 is 12 bytes");
static_assert(offsetof(Vec3, z) == 8, "bc5b130: Vec3::z is at offset 8");

namespace {

// SSE maxss/minss semantics exactly: maxss(a,b) = (a < b) ? b : a (NaN keeps
// the first operand); minss(a,b) = (a < b) ? a : b (NaN yields the second).
// Matches 0xbc5b219/0xbc5b223/0xbc5b2b3/0xbc5b2bb/0xbc5b2fd/0xbc5b305 etc. [V]
inline float maxss(float a, float b) { return (a < b) ? b : a; }
inline float minss(float a, float b) { return (a < b) ? a : b; }

// Bitwise XOR of two floats on their 32-bit representation; exactly the
// low-element effect of 0xbc5b1c0  xorps xmm8,xmm10 [V].
inline float float_xor(float a, float b) {
    return std::bit_cast<float>(std::bit_cast<std::uint32_t>(a) ^
                                std::bit_cast<std::uint32_t>(b));
}

// Shared z-block: writes [rdi+8] (outRdi[2]). Reads a8[0], a8[1], a3, a5[2].
// 0xbc5b4bb..0xbc5b53f [V]. Call results (0xbc5b4ed/0xbc5b4fa call rsi,
// 0xbc5b532 call 0xEEC75A0) are from callees outside the lift set and outside
// native_boundary.tsv, so they are left as uninitialized locals; no wrapper is
// written for them.
float zblock(const float* a8, float xmm7, float a3, const float* a5) {
    // 0xbc5b4bb..0xbc5b4d9  z-block decision part 1
    float xmm9 = 0.0f;                         // 0xbc5b22c/0xbc5b2ac  xorps xmm9,xmm9
    if (a8[0] > xmm7) {                        // 0xbc5b4c0  ucomiss xmm0,xmm7;
                                               //   0xbc5b4c3  ja short 0xBC5B544
        return xmm9;                           // 0xbc5b544  movss [rdi+8],xmm9  (= 0)
    }
    if (a8[1] > xmm7) {                        // 0xbc5b4cb  ucomiss xmm0,xmm7;
                                               //   0xbc5b4ce  jbe short 0xBC5B4DB  (not taken)
        xmm9 = kData_eec8060;                  // 0xbc5b4d0  movss xmm9,[0xEEC8060]
        return xmm9;                           // 0xbc5b4d9  jmp short 0xBC5B544
    }
    // 0xbc5b4db..0xbc5b53f  z-block compute
    float t = xmm7 / a8[1];                    // 0xbc5b4db  add r14,4;
                                               //   0xbc5b4df  divss xmm7,xmm0  (xmm0 = a8[1])
    // 0xbc5b4ed  call rsi   `0xbc5b4ed  call rsi`
    float r_4ed;                               // result of 0xbc5b4ed call rsi
    t = r_4ed;
    float u = a3 / a8[1];                      // 0xbc5b4f2  divss xmm6,[r14]
    // 0xbc5b4fa  call rsi   `0xbc5b4fa  call rsi`
    float r_4fa;                               // result of 0xbc5b4fa call rsi
    u = r_4fa;
    t /= u;                                    // 0xbc5b4fc  divss xmm7,xmm0
    t = maxss(0.0f, t);                        // 0xbc5b500  xorps xmm0,xmm0;
                                               //   0xbc5b503  maxss xmm0,xmm7
    const float clamp = minss(kData_eec8060, t);  // 0xbc5b507  movss xmm1,[0xEEC8060];
                                               //   0xbc5b50f  minss xmm1,xmm0
    // 0xbc5b532  call 0xEEC75A0   `0xbc5b532  call 0xEEC75A0`
    float r_532;                               // result of 0xbc5b532 call 0xEEC75A0
    return minss(kData_ef1d470 + a5[2],
                 r_532 + kData_ef3f01c);       // 0xbc5b537..0xbc5b53f
}

} // namespace

native::Footprint sub_bc5b130_footprint(const Vec3* /*a0*/, float /*a1*/,
                                        float /*a2*/, float /*a3*/,
                                        const float* /*a5*/, float /*a6*/,
                                        float /*a7*/, const float* /*a8*/,
                                        float* outR15, float* outRdi) {
    return { { outR15, 3ull * sizeof(float) },
             { outRdi, 3ull * sizeof(float) } };
}

void sub_bc5b130(const Vec3* a0, float a1, float a2, float a3,
                 const float* a5, float a6, float a7, const float* a8,
                 float* outR15, float* outRdi) {
    // 0xbc5b130..0xbc5b1e5  prologue, length = sqrt(x*x+y*y), branch a1<=length
    const float x = a0->x;                       // 0xbc5b1c7  movss xmm0,[rcx]   ; R a0+0x0
    const float y = a0->y;                       // 0xbc5b1ad  movsd xmm1,[rcx+4] ; R a0+0x4
    const float z = a0->z;                       // 0xbc5b1b2  movss xmm10,[rcx+8]; R a0+0x8
    const float x8raw = float_xor(kData_ef3f050, z);  // 0xbc5b1b8  movaps xmm8,[0xEF3F050];
                                               //   0xbc5b1c0  xorps xmm8,xmm10
    const float length = std::sqrtf(x * x + y * y);  // 0xbc5b1c4..0xbc5b1de

    if (a1 > length) {                           // 0xbc5b1e2  ucomiss xmm7,xmm1;
                                               //   0xbc5b1e5  jbe short 0xBC5B25C  (not taken)
        // 0xbc5b1e7..0xbc5b257  early-out writes and [r15+8] decision
        outR15[0] = 0.0f;                        // 0xbc5b1e7  mov dword ptr [r15],0
        outRdi[0] = a5[0] + kData_ef1d470;       // 0xbc5b1ee  movss xmm0,[0xEF1D470];
                                               //   0xbc5b1f6  movss xmm1,[rbx];
                                               //   0xbc5b1fa  addss xmm1,xmm0; 0xbc5b1fe  movss [rdi],xmm1
        outR15[1] = 0.0f;                        // 0xbc5b202  mov dword ptr [r15+4],0
        outRdi[1] = kData_ef1d470 + a5[1];       // 0xbc5b20a  addss xmm0,[rbx+4]; 0xbc5b20f  movss [rdi+4],xmm0
        const float v8 = maxss(x8raw - a1, a2);  // 0xbc5b214  subss xmm8,xmm7;
                                               //   0xbc5b219  maxss xmm8,xmm2
        const float xmm7 = minss(a1 - z, a3);    // 0xbc5b21e  subss xmm7,xmm10;
                                               //   0xbc5b223  minss xmm7,xmm6
        // 0xbc5b227..0xbc5b257  [r15+8] decision
        if (a8[0] > v8) {                        // 0xbc5b230  ucomiss xmm0,xmm8;
                                               //   0xbc5b238  ja 0xBC5B4B5  (xmm10 = 0)
            outR15[2] = 0.0f;                    // 0xbc5b4b5  movss [r15+8],xmm10  (= 0)
        } else if (a8[1] <= v8) {                // 0xbc5b244  ucomiss xmm0,xmm8;
                                               //   0xbc5b248  jbe 0xBC5B44A
            // 0xbc5b44a..0xbc5b4b5  [r15+8] compute
            float t = v8 / a8[1];                // 0xbc5b44a  divss xmm8,xmm0
            // 0xbc5b45a  call rsi   `0xbc5b45a  call rsi`
            float r_45a;                       // result of 0xbc5b45a call rsi
            t = r_45a;
            float u = a3 / a8[1];                // 0xbc5b463  divss xmm0,[r14+4]
            // 0xbc5b469  call rsi   `0xbc5b469  call rsi`
            float r_469;                       // result of 0xbc5b469 call rsi
            u = r_469;
            t /= u;                              // 0xbc5b46b  divss xmm8,xmm0
            t = maxss(0.0f, t);                  // 0xbc5b470  xorps xmm0,xmm0;
                                               //   0xbc5b473  maxss xmm0,xmm8
            const float clamp = minss(kData_eec8060, t);  // 0xbc5b478..0xbc5b480
            // 0xbc5b4a3  call 0xEEC75A0   `0xbc5b4a3  call 0xEEC75A0`
            float r_4a3;                       // result of 0xbc5b4a3 call 0xEEC75A0
            outR15[2] = minss(kData_ef1d470 + a5[2],
                              r_4a3 + kData_ef3f01c);  // 0xbc5b4a8..0xbc5b4b0; 0xbc5b4b5  movss [r15+8],xmm10
        } else {
            outR15[2] = kData_eec8060;           // 0xbc5b24e  movss xmm10,[0xEEC8060];
                                               //   0xbc5b257  jmp 0xBC5B4B5
        }
        // 0xbc5b4bb..0xbc5b53f  z-block -> [rdi+8] (xmm7 = min(a1-z,a3))
        outRdi[2] = zblock(a8, xmm7, a3, a5);
    } else {
        // 0xbc5b25c..0xbc5b3ae  long path part 1
        const float xmm13 = a6 * x8raw;        // 0xbc5b26d  movss xmm13,[rsp+0x128];
                                               //   0xbc5b277  mulss xmm13,xmm8
        const float den = a7 * xmm13;          // 0xbc5b27c  movss xmm15,[rsp+0x130];
                                               //   0xbc5b286  mulss xmm15,xmm13
        // outR15[0]
        float c0 = maxss(0.0f, (((x - a1) / den + kData_eec8060) * kData_eee7c00));
                                               // 0xbc5b28b..0xbc5b2bb
        float clamp1 = minss(kData_eec8060, c0);  // 0xbc5b2b7..0xbc5b2bb
        // 0xbc5b2d1  call 0xEEC75A0   `0xbc5b2d1  call 0xEEC75A0`
        float r_2d1;                           // result of 0xbc5b2d1 call 0xEEC75A0
        outR15[0] = minss(kData_ef1d470 + a5[0], r_2d1);  // 0xbc5b2d6..0xbc5b2da
        // outRdi[0]
        float c0b = maxss(0.0f, (((x + a1) / den + kData_eec8060) * kData_eee7c00));
        float clamp2 = minss(kData_eec8060, c0b);  // 0xbc5b301..0xbc5b305
        // 0xbc5b312  call 0xEEC75A0   `0xbc5b312  call 0xEEC75A0`
        float r_312;                           // result of 0xbc5b312 call 0xEEC75A0
        outRdi[0] = minss(kData_ef1d470 + a5[0], r_312);  // 0xbc5b317..0xbc5b31b
        // outR15[1]
        float c0y = maxss(0.0f, (((y - a1) / xmm13 + kData_eec8060) * kData_eee7c00));
        float clampy = minss(kData_eec8060, c0y);  // 0xbc5b343..0xbc5b347
        // 0xbc5b354  call 0xEEC75A0   `0xbc5b354  call 0xEEC75A0`
        float r_354;                           // result of 0xbc5b354 call 0xEEC75A0
        outR15[1] = minss(kData_ef1d470 + a5[1], r_354);  // 0xbc5b359..0xbc5b35d
        // outRdi[1]
        float c0y2 = maxss(0.0f, (((y + a1) / xmm13 + kData_eec8060) * kData_eee7c00));
        float clampy2 = minss(kData_eec8060, c0y2);  // 0xbc5b38d..0xbc5b391
        // 0xbc5b39e  call 0xEEC75A0   `0xbc5b39e  call 0xEEC75A0`  (multiplies clampy2 by c0 from above)
        float r_39e;                           // result of 0xbc5b39e call 0xEEC75A0
        outRdi[1] = minss(kData_ef1d470 + c0, r_39e);  // 0xbc5b3a3..0xbc5b3a8
        // [r15+8] decision: xmm8 = x8raw - a1  (xmm7 = a1 here)
        // 0xbc5b3b3..0xbc5b3d0  [r15+8] decision part 1
        float xmm8 = x8raw - a1;               // 0xbc5b3ae  subss xmm8,xmm7
        if (a8[0] > xmm8) {                    // 0xbc5b3c0  ja short 0xBC5B43D  (xmm12 = 0)
            outR15[2] = 0.0f;                  // 0xbc5b43d  movss [r15+8],xmm12
        } else if (a8[1] > xmm8) {             // 0xbc5b3d0  ja short 0xBC5B43D  (xmm12 = eec8060)
            outR15[2] = kData_eec8060;
        } else {
            // 0xbc5b3d2..0xbc5b438  [r15+8] compute
            float t = xmm8 / a8[1];            // 0xbc5b3d2  divss xmm8,xmm0
            // 0xbc5b3e2  call rsi   `0xbc5b3e2  call rsi`
            float r_3e2;                       // result of 0xbc5b3e2 call rsi
            t = r_3e2;
            float u = a3 / a8[1];              // 0xbc5b3eb  divss xmm0,[r14+4]
            // 0xbc5b3f1  call rsi   `0xbc5b3f1  call rsi`
            float r_3f1;                       // result of 0xbc5b3f1 call rsi
            u = r_3f1;
            t /= u;                            // 0xbc5b3f3  divss xmm8,xmm0
            t = maxss(0.0f, t);                // 0xbc5b3f8  xorps xmm0,xmm0;
                                               //   0xbc5b3fb  maxss xmm0,xmm8
            const float clamp = minss(kData_eec8060, t);  // 0xbc5b400..0xbc5b408
            // 0xbc5b42b  call 0xEEC75A0   `0xbc5b42b  call 0xEEC75A0`
            float r_42b;                       // result of 0xbc5b42b call 0xEEC75A0
            outR15[2] = minss(kData_ef1d470 + a5[2],
                              r_42b + kData_ef3f01c);  // 0xbc5b430..0xbc5b438
        }
        // 0xbc5b443..0xbc5b4bb  z-block with xmm7 = a1 - z  (0xbc5b443  subss xmm7,xmm10)
        outRdi[2] = zblock(a8, a1 - z, a3, a5);
    }
    // 0xbc5b54a..0xbc5b5a1  epilogue: restore xmm6..xmm15, pop rbx/rdi/rsi/r14/r15,
    //   add rsp,0xD0, ret 0xbc5b5a1. No further memory side effects [V].
}

LIFT_FN(bc5b130, "VV frame-graph builder", 0xBC5B130, sub_bc5b130,
        sub_bc5b130_footprint);

} // namespace native
