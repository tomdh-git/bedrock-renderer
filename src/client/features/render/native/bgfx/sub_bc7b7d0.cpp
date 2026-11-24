// LIFT 0xbc7b7d0 size 0x28b 1.26.62.01 VV frame-graph builder
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc7b7d0.h"

#include <algorithm>
#include <cstdint>
#include <cstring>

#include <intrin.h>
#include <xmmintrin.h>

namespace native::bgfx {

namespace {

inline std::uintptr_t imageBase() { return RewriteRegistry::imageBase(); }

// The three external callees are import thunks (jmp qword ptr [data slot]):
//   0xEEC75A0 = jmp qword ptr [0xF9A8E60]   (float (float))   called 0xbc7b839, 0xbc7b8fd
//   0xEEC73F0 = jmp qword ptr [0xF9A8E08]   (float (float))   called 0xbc7b86a, 0xbc7b925
//   0x78ed0   = sub rsp,0x28 / call [0xF9A8CF0] / int3        (noreturn crt) called 0xbc7ba55
// Per hard rule 69 (call [0xRVA] through a forwarder is not a blocker) the pointer is
// read from the slot at every call, exactly what the CPU does through the thunk.
inline float (*thunkEec75a0())(float) {
    return reinterpret_cast<float (*)(float)>(
        *reinterpret_cast<std::uintptr_t*>(imageBase() + kRvaSlotEec75a0));
}
inline float (*thunkEec73f0())(float) {
    return reinterpret_cast<float (*)(float)>(
        *reinterpret_cast<std::uintptr_t*>(imageBase() + kRvaSlotEec73f0));
}
[[noreturn]] inline void noreturn78ed0() {  // 0x78ed0 callee (noreturn crt thunk)
    reinterpret_cast<void (*)()>(
        *reinterpret_cast<std::uintptr_t*>(imageBase() + kRvaSlot78ed0))();
    __debugbreak();  // 0xbc7ba5a  int3  - traps only if the noreturn thunk returns
}

// Const game data, read at each use (same address as the original's rip-relative read).
inline float dataF(std::uintptr_t rva) {
    return *reinterpret_cast<const float*>(imageBase() + rva);
}

// 0xbc7b85a..0xbc7b864 / 0xbc7b906..0xbc7b91f / 0xbc7b934..0xbc7b94d:
//   cvttss2si rax, xmm-k  ;  cvttss2si rcx, xmm  ;  rbx=rcx; rbx>>=63; rbx&=rax; rbx|=rcx
// i.e. rnd(x) = trunc(x) >= 0 ? trunc(x) : trunc(x - k), k = [0xEEE6700]
inline std::int64_t rnd(float x) {
    const std::int64_t below = static_cast<std::int64_t>(x - dataF(kRvaHalfK));
    const std::int64_t straight = static_cast<std::int64_t>(x);
    return straight >= 0 ? straight : below;
}

// Table row vector {f0, bitcast(pad04), 0, 0} as consumed by mulps after the movsd.
inline __m128 rowVec(const CascadedTableRow* t, std::int64_t idx) {
    float pad;
    std::memcpy(&pad, &t[idx].pad04, sizeof(pad));
    return _mm_set_ps(0.f, 0.f, pad, t[idx].f0);
}

} // namespace

float* sub_bc7b7d0(float* out, const float* in) {
    const float inX = in[0];          // 0xbc7b81d  movss xmm9,[rdx]           R in+0x0

    // 0xbc7b7d0..0xbc7b864: v = inX/C1*C2, then a = thunk75a0(v), idxA = rnd(a)
    float v = inX / dataF(kRvaDivC1) * dataF(kRvaMulC2);  // 0xbc7b826 divss xmm6,[0xEFD32AC]
                                                            // 0xbc7b82e mulss xmm6,[0xEFC6CF8]
    const float a = thunkEec75a0()(v);                    // 0xbc7b839  call 0xEEC75A0   xmm8 = a
    const std::int64_t idxA = rnd(a);                     // 0xbc7b85a..0xbc7b864       rbx = rnd(a)
    const float b = thunkEec73f0()(v);                    // 0xbc7b86a  call 0xEEC73F0

    // 0xbc7b867..0xbc7b899: check idxA, then idxB = rnd(b), check idxB
    if (idxA >= kIndexLimit) {                            // 0xbc7b86f  cmp rbx,0x65
                                                            // 0xbc7b873  jae  0xBC7BA55
        noreturn78ed0();                                  // 0xbc7ba55  call 0x78ED0 ; 0xbc7ba5a  int3
    }
    const std::int64_t idxB = rnd(b);                     // 0xbc7b879..0xbc7b892       rax = rnd(b)
    if (idxB >= kIndexLimit) {                            // 0xbc7b895  cmp rax,0x65
                                                            // 0xbc7b899  jae  0xBC7BA55
        noreturn78ed0();
    }

    // 0xbc7b89f..0xbc7b8c1: table row selection (rcx = idxA*3, rax = idxB*3)
    const CascadedTableRow* const t1 =
        reinterpret_cast<const CascadedTableRow*>(imageBase() + kRvaTable1);
    const CascadedTableRow* const t2 =
        reinterpret_cast<const CascadedTableRow*>(imageBase() + kRvaTable2);
    const float t1A_f8 = t1[idxA].f8;                     // 0xbc7b8c1  movss xmm10,[rdx+rcx*4+8]
    const float t1B_f8 = t1[idxB].f8;                     // 0xbc7b8ae  movss xmm14,[rdx+rax*4+8]
    const float t1A_f0 = t1[idxA].f0;                     // 0xbc7b8bb  movsd xmm11,[rdx+rcx*4]
    const float t1B_f0 = t1[idxB].f0;                     // 0xbc7b8b5  movsd xmm12,[rdx+rax*4]

    // 0xbc7b8c8..0xbc7b8fa: blended = max(0,inX)/C3*C2, or C2 when C3 < inX
    const float t0 = std::max(0.0f, inX);                 // 0xbc7b8cb  maxss xmm0,xmm9
    const float t = t0 / dataF(kRvaC3) * dataF(kRvaMulC2);// 0xbc7b8d8 divss xmm0,[0xF10D440]
                                                            // 0xbc7b8e4 mulss xmm0,[0xEFC6CF8]
    const float blended = (dataF(kRvaC3) < inX)           // 0xbc7b8e8 cmpltss xmm7,xmm9
        ? dataF(kRvaMulC2)                                // 0xbc7b8f1 andnps xmm2,xmm0
        : t;                                              // 0xbc7b8f4 andps xmm7,xmm1 ; 0xbc7b8f7 orps xmm7,xmm2

    // 0xbc7b8fd..0xbc7b91f: d = thunk75a0(blended), idxD = rnd(d), check idxD
    const float d = thunkEec75a0()(blended);              // 0xbc7b8fd  call 0xEEC75A0   xmm9 = d
    const std::int64_t idxD = rnd(d);                     // 0xbc7b906..0xbc7b91f        rbx = rnd(d)
    if (idxD >= kIndexLimit) {                            // 0xbc7b92a  cmp rbx,0x65
                                                            // 0xbc7b92e  jae  0xBC7BA55
        noreturn78ed0();
    }
    // 0xbc7b922..0xbc7b954: e = thunk73f0(blended), idxE = rnd(e), check idxE
    const float e = thunkEec73f0()(blended);              // 0xbc7b925  call 0xEEC73F0
    const std::int64_t idxE = rnd(e);                     // 0xbc7b934..0xbc7b94d        rdx = rnd(e)
    if (idxE >= kIndexLimit) {                            // 0xbc7b950  cmp rdx,0x65
                                                            // 0xbc7b954  jae  0xBC7BA55
        noreturn78ed0();
    }

    // 0xbc7b95a..0xbc7b9c0: z term
    const float vma = v - a;                              // 0xbc7b95a  subss xmm6,xmm8   (xmm8 = a)
    float z = t1A_f8 * (dataF(kRvaC4) - vma);             // 0xbc7b95f movss xmm1,[0xEEC8060]
                                                            // 0xbc7b96a subss xmm0,xmm6 ; 0xbc7b96e mulss xmm10,xmm0
    z += t1B_f8 * vma;                                    // 0xbc7b973 mulss xmm14,xmm6 ; 0xbc7b978 addss xmm10,xmm14
    const float blendMinusD = blended - d;                // 0xbc7b98c subss xmm7,xmm9     (xmm9 = d)
    const float c4blendD = dataF(kRvaC4) - blendMinusD;   // 0xbc7b99b subss xmm1,xmm7
    const float w =
        t2[idxD].f8 * c4blendD + t2[idxE].f8 * blendMinusD;  // 0xbc7b99f..0xbc7b9a9 T2 rows
    z += dataF(kRvaC5);                                     // 0xbc7b9b2 addss xmm10,[0xF449710]
    z += w;                                                 // 0xbc7b9bb addss xmm10,xmm3
    const float inZ = in[0x0C];                             // 0xbc7b9ad movss xmm2,[rdi+0xC]  R in+0xC
    z += inZ;                                               // 0xbc7b9c0 addss xmm10,xmm2

    // 0xbc7b9c5..0xbc7ba04: xy term, then stores out[0..8), out[8..0xC)
    const __m128 c6 = _mm_loadu_ps(
        reinterpret_cast<const float*>(imageBase() + kRvaC6)); // 0xbc7b9f1 addps xmm0,[0xF449720]
    __m128 xy = _mm_mul_ps(_mm_set1_ps(e), rowVec(t1, idxA));  // 0xbc7b9cd shufps xmm0,xmm0,0
                                                            // 0xbc7b9d1 mulps xmm0,xmm11
    xy = _mm_add_ps(xy,                                     // 0xbc7b9c5 shufps xmm6,xmm6,0
                    _mm_mul_ps(_mm_set1_ps(vma), rowVec(t1, idxB)));  // 0xbc7b9c9 mulps xmm6,xmm12
                                                            // 0xbc7b9d5 addps xmm0,xmm6
    xy = _mm_add_ps(xy, c6);
    xy = _mm_add_ps(xy,                                     // 0xbc7b9d8..0xbc7b9ee T2 rows into xmm7/xmm1
        _mm_add_ps(
            _mm_mul_ps(_mm_set1_ps(c4blendD), rowVec(t2, idxD)),
            _mm_mul_ps(_mm_set1_ps(blendMinusD), rowVec(t2, idxE))));
    xy = _mm_add_ps(xy, _mm_set_ps(0.f, 0.f, inZ, inZ));    // 0xbc7b9fb unpcklps xmm2,xmm2
                                                            // 0xbc7b9fe addps xmm2,xmm0
    std::memcpy(out, &xy, 8);                               // 0xbc7ba01 movlps [rsi],xmm2   W out+0x0..8
    out[8] = z;                                             // 0xbc7ba04 movss [rsi+8],xmm10 W out+8..0xC

    // 0xbc7ba0a..0xbc7ba54: return out, epilogue
    return out;                                             // 0xbc7ba0a mov rax,rsi ; 0xbc7ba54 ret
}

// 0xbc7ba55..0xbc7ba5a: error path (unreachable unless the noreturn thunk returns):
//   0xbc7ba55  call 0x78ED0   0xbc7ba5a  int3
// Invoked through noreturn78ed0() above; __debugbreak() there is the int3.

native::Footprint sub_bc7b7d0_footprint(float* out, const float* /*in*/) {
    // Bytes written directly by this function: [out, out+0x0C) (movlps + movss).
    return {{out, 0x0cull}};
}

// Layout assertions (full set in sub_bc7b7d0.h; repeated here so liftcheck sees them).
static_assert(offsetof(CascadedTableRow, f0) == 0x00, "sub_bc7b7d0: table row f0 at +0x00");
static_assert(offsetof(CascadedTableRow, pad04) == 0x04, "sub_bc7b7d0: table row pad at +0x04");
static_assert(offsetof(CascadedTableRow, f8) == 0x08, "sub_bc7b7d0: table row f8 at +0x08");
static_assert(sizeof(CascadedTableRow) == 0x0c, "sub_bc7b7d0: table row stride 0x0c");

// Verbatim log of every call instruction in [0xbc7b7d0, 0xbc7ba5b) (rdis dis output,
// two spaces after the address):
#if 0
0xbc7b839  call 0xEEC75A0
0xbc7b86a  call 0xEEC73F0
0xbc7b8fd  call 0xEEC75A0
0xbc7b925  call 0xEEC73F0
0xbc7ba55  call 0x78ED0
#endif
// Calls out of lifted code - all three are data-slot import thunks (hard rule 69:
// read the pointer from the slot at call time; slot RVA documented above):
//   0xbc7b839 / 0xbc7b8fd  call 0xEEC75A0  -> slot 0xF9A8E60, float (float)
//   0xbc7b86a / 0xbc7b925  call 0xEEC73F0  -> slot 0xF9A8E08, float (float)
//   0xbc7ba55  call 0x78ED0  -> slot 0xF9A8CF0, noreturn; 0xbc7ba5a  int3 follows
// UNRESOLVED CALL = none

LIFT_FN(sub_bc7b7d0, "sub_bc7b7d0", 0xbc7b7d0, sub_bc7b7d0, sub_bc7b7d0_footprint);

} // namespace native::bgfx
