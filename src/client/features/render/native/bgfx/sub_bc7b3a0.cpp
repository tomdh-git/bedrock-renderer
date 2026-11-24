// LIFT 0xbc7b3a0 size 0x425 1.26.62.01 sub_bc7b3a0
#include "client/features/render/native/bgfx/sub_bc7b3a0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>
#include <intrin.h>
#include <xmmintrin.h>

namespace native {

namespace {

inline std::uintptr_t imageBase() { return RewriteRegistry::imageBase(); }

inline float dataF(std::uintptr_t rva) {
    // Const game data, read at the same address the original's rip-relative read resolves to.
    return *reinterpret_cast<const float*>(imageBase() + rva);
}

// 0xbc7b42d..0xbc7b446 / 0xbc7b504..0xbc7b51d / 0xbc7b5e0..0xbc7b5f8 / 0xbc7b60e..0xbc7b62a:
//   cvttss2si rax,xmm   (straight = trunc(x))
//   cvttss2si rcx,xmm
//   subss xmm,[0xEEE6700] ; cvttss2si rdx/rbx,xmm   (below = trunc(x - K))
//   sar reg,0x3F          (sign = straight >> 63)
//   and reg,rax           (sign & below)
//   or reg,rcx            (result = (sign & below) | straight)
inline std::int64_t rnd(float x) {
    const std::int64_t straight = static_cast<std::int64_t>(x);
    const std::int64_t below = static_cast<std::int64_t>(x - dataF(kRvaK));
    const std::int64_t sign = straight >> 63;     // sar reg,0x3F (arithmetic, MSVC)
    return (sign & below) | straight;             // and ; or
}

// 0xbc7b7bf  call 0x78ED0 ; 0xbc7b7c4  int3  — trap block (noreturn crt thunk, then breakpoint).
// 0x78ed0 = sub rsp,0x28 / call qword ptr [0xF9A8CF0] / int3 (noreturn crt).
// Hard rule 69: read the pointer from the slot at call time, exactly as the thunk does;
// slot RVA 0xF9A8CF0 (constant kRvaSlot78ed0 in the header).
[[noreturn]] inline void trap78ed0() {
    reinterpret_cast<void (*)()>(
        *reinterpret_cast<std::uintptr_t*>(imageBase() + kRvaSlot78ed0))();
    __debugbreak();                             // 0xbc7b7c4 int3  (only if the noreturn thunk returns)
}

// movsd-like 8-byte load of a table row's low quadword: {f0, pad-as-float, 0, 0} [V].
// The high float lane reuses the pad04 bit pattern as a float (the original's movsd
// multiply uses it).
inline __m128 rowLo(const TableRow* t) {
    __m128 v;
    std::memcpy(&v, t, 8);                      // 8 bytes copied, upper lanes zeroed (like movsd)
    return v;
}

} // namespace

float* sub_bc7b3a0(float* out /*rcx, kept in rsi*/, const float* in /*rdx, kept in rdi*/) {
    const float c8 = dataF(kRvaC8);             // [0xEEC8060] — z-term blend base

    // 0xbc7b3a0..0xbc7b402 — prologue: push rsi/rdi/rbx; sub rsp,0x110; save xmm6-xmm15;
    //                        rdi = in ; rsi = out (rax = rsi = out at 0xbc7b7be ret).

    // ---- channel 0 ----
    // 0xbc7b405  movss xmm6,[rdx]               R in+0x0
    // 0xbc7b409  divss xmm6,[0xEFD32AC]
    // 0xbc7b411  mulss xmm6,[0xEFC6CF8]
    const float v0 = in[0x00] / dataF(kRvaDivC1) * dataF(kRvaMulC2);

    // 0xbc7b419  movaps xmm0,xmm6
    // 0xbc7b41c  call 0xEEC75A0                  a0 = sub_eec75a0(v0)
    const float a0 = sub_eec75a0(v0);           // 0xbc7b41c  call 0xEEC75A0
    // 0xbc7b449  movaps xmm0,xmm6
    // 0xbc7b44c  call 0xEEC73F0                  b0 = sub_eec73f0(v0)
    const float b0 = sub_eec73f0(v0);           // 0xbc7b44c  call 0xEEC73F0

    const std::int64_t idxA0 = rnd(a0);         // 0xbc7b42d..0xbc7b446
    // 0xbc7b451  cmp rbx,0x65
    // 0xbc7b455  jae 0xBC7B7BF                   trap: 0xbc7b7bf  call 0x78ED0 ; 0xbc7b7c4  int3
    if (idxA0 >= kIndexLimit) {                 // 0xbc7b451..0xbc7b455
        trap78ed0();                            // 0xbc7b7bf..0xbc7b7c4
    }
    const std::int64_t idxB0 = rnd(b0);         // 0xbc7b45b..0xbc7b474
    // 0xbc7b477  cmp rax,0x65
    // 0xbc7b47b  jae 0xBC7B7BF
    if (idxB0 >= kIndexLimit) {                 // 0xbc7b477..0xbc7b47b
        trap78ed0();                            // 0xbc7b7bf..0xbc7b7c4
    }

    // 0xbc7b481  lea rcx,[rbx+rbx*2]            idxA0*3
    // 0xbc7b485  lea rdx,[0xF449730]            table T0
    // 0xbc7b48c  lea rax,[rax+rax*2]            idxB0*3
    // 0xbc7b490  movss xmm13,[rdx+rax*4+8]      T0[idxB0].f8
    // 0xbc7b497  movsd xmm14,[rdx+rax*4]        T0[idxB0] row lo {f0, pad-as-float}
    // 0xbc7b49d  movsd xmm9,[rdx+rcx*4]         T0[idxA0] row lo
    // 0xbc7b4a3  movss xmm12,[rdx+rcx*4+8]      T0[idxA0].f8
    const TableRow* const t0 =
        reinterpret_cast<const TableRow*>(imageBase() + kRvaTable0);   // 0xbc7b485
    const float z0B = t0[idxB0].f8;               // 0xbc7b490
    const float z0A = t0[idxA0].f8;               // 0xbc7b4a3

    // 0xbc7b4aa  movss xmm0,[rdi+4]              R in+0x4
    // 0xbc7b4af  movss xmm1,[0xEFC2540]
    // 0xbc7b4b7  maxss xmm1,xmm0
    // 0xbc7b4bb  addss xmm1,[0xF0C8C88]
    // 0xbc7b4c3  divss xmm1,[0xF1527C8]
    // 0xbc7b4cb  movss xmm11,[0xEFC6CF8]
    // 0xbc7b4d4  mulss xmm1,xmm11
    const float t1 = (std::max(dataF(kRvaC3), in[0x04]) + dataF(kRvaC4)) /
                     dataF(kRvaC5) * dataF(kRvaMulC2);   // 0xbc7b4aa..0xbc7b4d4

    // 0xbc7b4d9  movss xmm8,[0xEF40D44]
    // 0xbc7b4e2  cmpltss xmm8,xmm0               xmm0 still = in[4]: mask = [0xEF40D44] < in[4]
    // 0xbc7b4e8..0xbc7b4f3                      blended1 = mask ? [0xEFC6CF8] : t1
    const float blended1 = dataF(kRvaC6) < in[0x04] ? dataF(kRvaMulC2) : t1;  // 0xbc7b4d9..0xbc7b4f3

    // 0xbc7b4f7  movaps xmm0,xmm8
    // 0xbc7b4fb  call 0xEEC75A0                 d1 = sub_eec75a0(blended1)
    const float d1 = sub_eec75a0(blended1);     // 0xbc7b4fb  call 0xEEC75A0
    // 0xbc7b520  movaps xmm0,xmm8
    // 0xbc7b524  call 0xEEC73F0                 e1 = sub_eec73f0(blended1)
    const float e1 = sub_eec73f0(blended1);     // 0xbc7b524  call 0xEEC73F0

    const std::int64_t idxD1 = rnd(d1);         // 0xbc7b504..0xbc7b51d
    // 0xbc7b529  cmp rbx,0x65
    // 0xbc7b52d  jae 0xBC7B7BF
    if (idxD1 >= kIndexLimit) {                 // 0xbc7b529..0xbc7b52d
        trap78ed0();
    }
    const std::int64_t idxE1 = rnd(e1);         // 0xbc7b533..0xbc7b54c
    // 0xbc7b54f  cmp rax,0x65
    // 0xbc7b553  jae 0xBC7B7BF
    if (idxE1 >= kIndexLimit) {                 // 0xbc7b54f..0xbc7b553
        trap78ed0();
    }

    // 0xbc7b56a  lea rcx,[rbx+rbx*2]            idxD1*3
    // 0xbc7b56e  lea rdx,[0xF44A0A8]            table T1
    // 0xbc7b575  lea rax,[rax+rax*2]            idxE1*3
    const TableRow* const t1 =
        reinterpret_cast<const TableRow*>(imageBase() + kRvaTable1);   // 0xbc7b56e
    const float t1D1_f0 = t1[idxD1].f0;           // 0xbc7b58e (row lo spilled at [rsp+0x30])
    const float t1D1_f8 = t1[idxD1].f8;           // 0xbc7b598
    const float t1E1_f0 = t1[idxE1].f0;           // 0xbc7b584 (row lo spilled at [rsp+0x20])
    const float t1E1_f8 = t1[idxE1].f8;           // 0xbc7b57d

    // ---- channel 2 ----
    // 0xbc7b59f  movss xmm0,[rdi+8]              R in+0x8
    // 0xbc7b5a4  xorps xmm1,xmm1
    // 0xbc7b5a7  maxss xmm1,xmm0
    // 0xbc7b5ab  movss xmm9,[0xF10D440]
    // 0xbc7b5b4  divss xmm1,xmm9
    // 0xbc7b5b9  mulss xmm1,xmm11
    const float t2 = std::max(0.0f, in[0x08]) / dataF(kRvaC7) * dataF(kRvaMulC2);  // 0xbc7b59f..0xbc7b5b9

    // 0xbc7b5be  cmpltss xmm9,xmm0               xmm0 still = in[8]: mask = [0xF10D440] < in[8]
    // 0xbc7b5c4..0xbc7b5cf                      blended2 = mask ? [0xEFC6CF8] : t2
    const float blended2 = dataF(kRvaC7) < in[0x08] ? dataF(kRvaMulC2) : t2;  // 0xbc7b5be..0xbc7b5cf

    // 0xbc7b5d3  movaps xmm0,xmm9
    // 0xbc7b5d7  call 0xEEC75A0                 d2 = sub_eec75a0(blended2)
    const float d2 = sub_eec75a0(blended2);     // 0xbc7b5d7  call 0xEEC75A0
    // 0xbc7b5fb  movaps xmm0,xmm9
    // 0xbc7b5ff  call 0xEEC73F0                 e2 = sub_eec73f0(blended2)
    const float e2 = sub_eec73f0(blended2);     // 0xbc7b5ff  call 0xEEC73F0

    const std::int64_t idxD2 = rnd(d2);         // 0xbc7b5e0..0xbc7b5f8
    // 0xbc7b604  cmp rbx,0x65
    // 0xbc7b608  jae 0xBC7B7BF
    if (idxD2 >= kIndexLimit) {                 // 0xbc7b604..0xbc7b608
        trap78ed0();
    }
    const std::int64_t idxE2 = rnd(e2);         // 0xbc7b60e..0xbc7b62a
    // 0xbc7b62d  cmp rdx,0x65
    // 0xbc7b631  jae 0xBC7B7BF
    if (idxE2 >= kIndexLimit) {                 // 0xbc7b62d..0xbc7b631
        trap78ed0();
    }

    const TableRow* const t2 =
        reinterpret_cast<const TableRow*>(imageBase() + kRvaTable2);   // 0xbc7b67b

    const float diff1 = blended1 - d1;          // 0xbc7b637  subss xmm8,xmm10
    const float s1a = c8 - diff1;               // 0xbc7b647  subss xmm1,xmm8
    const float s1b = diff1;

    const float diff2 = blended2 - d2;          // 0xbc7b686  subss xmm9,xmm11
    const float s2a = c8 - diff2;               // 0xbc7b696  subss xmm0,xmm9
    const float s2b = diff2;

    // ---- z term (scalar; accumulation order follows the addss chain) ----
    // 0xbc7b65b  subss xmm6,[rsp+0x40]           xmm6 = v0 - a0
    // 0xbc7b664  subss xmm2,xmm6                 xmm2 = c8 - (v0 - a0)
    // 0xbc7b668  mulss xmm13,xmm6                xmm13 = T0[idxB0].f8 * (v0 - a0)
    // 0xbc7b66d  mulss xmm12,xmm2                xmm12 = T0[idxA0].f8 * (c8 - (v0 - a0))
    // 0xbc7b672  addss xmm12,xmm13
    float z0 = z0A * (c8 - (v0 - a0));          // 0xbc7b66d
    z0 += z0B * (v0 - a0);                      // 0xbc7b668 + 0xbc7b672

    // 0xbc7b6c2  addss xmm12,[0xF246F60]
    z0 += dataF(kRvaC10);                       // 0xbc7b6c2

    // w1: 0xbc7b64c  mulss xmm15,xmm8   (T1[idxE1].f8 * diff1)
    //     0xbc7b651  mulss xmm14,xmm1   (T1[idxD1].f8 * s1a)
    //     0xbc7b656  addss xmm14,xmm15
    float w1 = t1D1_f8 * s1a;                   // 0xbc7b651
    w1 += t1E1_f8 * s1b;                        // 0xbc7b64c + 0xbc7b656

    // w2: 0xbc7b691  mulss xmm3,xmm9   (T2[idxE2].f8 * diff2)
    //     0xbc7b6a1  mulss xmm4,xmm0   (T2[idxD2].f8 * s2a)
    //     0xbc7b6a5  addss xmm4,xmm3
    float w2 = t2[idxD2].f8 * s2a;              // 0xbc7b6a1
    w2 += t2[idxE2].f8 * s2b;                   // 0xbc7b691 + 0xbc7b6a5

    // 0xbc7b6a9  movss xmm3,[rdi+0xC]            R in+0xC
    // 0xbc7b6ae  movss xmm5,[0xEFD3410]
    // 0xbc7b6b6  maxss xmm5,[rdi+0x18]           R in+0x18
    // 0xbc7b6be  divss xmm7,xmm5
    // 0xbc7b6cb  subss xmm7,xmm3
    const float inCpart = in[0x0C] / std::max(dataF(kRvaC9), in[0x18]) - in[0x0C];  // 0xbc7b6ae..0xbc7b6cb

    // 0xbc7b6cf  addss xmm12,xmm14   ; 0xbc7b6d4  addss xmm12,xmm4   ; 0xbc7b6d9  addss xmm12,xmm7
    float z = z0;                               // 0xbc7b672
    z += w1;                                    // 0xbc7b6cf
    z += w2;                                    // 0xbc7b6d4
    z += inCpart;                               // 0xbc7b6d9

    // ---- xy term, vector (stored to out[0..7]) ----
    // 0xbc7b6f6..0xbc7b708   row0 = s0a*rowLo(T0[idxA0]) + s0b*rowLo(T0[idxB0])
    const __m128 s0a = _mm_set1_ps(c8 - (v0 - a0));  // 0xbc7b661..0xbc7b664
    const __m128 s0b = _mm_set1_ps(v0 - a0);         // 0xbc7b65b + 0xbc7b6f6 shufps
    __m128 outVec =
        _mm_add_ps(_mm_mul_ps(s0a, rowLo(&t0[idxA0])),
                   _mm_mul_ps(s0b, rowLo(&t0[idxB0])));   // 0xbc7b708 addps xmm2,xmm6

    // 0xbc7b6e9..0xbc7b6f2   row1 = s1a*rowLo(T1[idxD1]) + s1b*rowLo(T1[idxE1])
    const __m128 row1 =
        _mm_add_ps(_mm_mul_ps(_mm_set1_ps(s1a), rowLo(&t1[idxD1])),
                   _mm_mul_ps(_mm_set1_ps(s1b), rowLo(&t1[idxE1])));

    // 0xbc7b71d..0xbc7b723   row2 = s2a*rowLo(T2[idxD2]) + s2b*rowLo(T2[idxE2])
    //     (unpcklps yields {d,d,0,0}; _mm_set1_ps yields {d,d,d,d}; lanes 2,3 are never
    //     stored, so the results are identical where it matters)
    const __m128 row2 =
        _mm_add_ps(_mm_mul_ps(_mm_set1_ps(s2a), rowLo(&t2[idxD2])),
                   _mm_mul_ps(_mm_set1_ps(s2b), rowLo(&t2[idxE2])));

    // 0xbc7b743  addps xmm2,[0xF449700]
    outVec = _mm_add_ps(outVec,
                        _mm_loadu_ps(reinterpret_cast<const float*>(imageBase() + kRvaC12)));
    // 0xbc7b74a  addps xmm2,xmm1
    outVec = _mm_add_ps(outVec, row1);
    // 0xbc7b74d  addps xmm2,xmm0
    outVec = _mm_add_ps(outVec, row2);

    // 0xbc7b727  movsd xmm4,[rdi+0x10]           {in[0x10], in[0x14], 0, 0}  R in+0x10
    // 0xbc7b72c  movaps xmm5,[0xF0A9660]
    // 0xbc7b733  maxps xmm5,xmm4
    // 0xbc7b736  shufps xmm3,xmm3,0              in[0xC] splat
    // 0xbc7b73d  divps xmm4,xmm5
    // 0xbc7b740  subps xmm4,xmm3
    const __m128 c11 = _mm_loadu_ps(reinterpret_cast<const float*>(imageBase() + kRvaC11));
    const __m128 in10v = _mm_set_ps(0.f, 0.f, in[0x14], in[0x10]);   // {in[0x10], in[0x14], 0, 0}
    const __m128 in0c = _mm_set1_ps(in[0x0C]);                      // splat
    const __m128 inPartVec =
        _mm_sub_ps(_mm_div_ps(in0c, _mm_max_ps(c11, in10v)), in0c);  // 0xbc7b733..0xbc7b740
    // 0xbc7b750  addps xmm2,xmm4
    outVec = _mm_add_ps(outVec, inPartVec);

    // 0xbc7b753  movlps [rsi],xmm2               W out[0..7]
    std::memcpy(out, &outVec, 8);
    // 0xbc7b756  movss [rsi+8],xmm12             W out[8..0xC]
    out[8] = z;
    // 0xbc7b75c  mov rax,rsi
    // 0xbc7b7be  ret                            rax = rsi = out
    return out;

    // 0xbc7b7bf  call 0x78ED0                   (trap block, entered by the idx >= 0x65 checks above)
    // 0xbc7b7c4  int3                           — handled by trap78ed0() (slot read + __debugbreak)
}

std::size_t sub_bc7b3a0_footprint(float* out, const float* /*in*/) {
    // Bytes written directly by this function: [out, out+8) via movlps (0xbc7b753) and
    // [out+8,out+0xC) via movss (0xbc7b756) — i.e. [out, out+0xC) [V].
    return {{out, 0x0cull}};
}

// Layout assertions (full set in sub_bc7b3a0.h; repeated here so liftcheck sees them).
static_assert(offsetof(TableRow, f0) == 0x00, "sub_bc7b3a0: table row f0 at +0x00");
static_assert(offsetof(TableRow, pad04) == 0x04, "sub_bc7b3a0: table row pad at +0x04");
static_assert(offsetof(TableRow, f8) == 0x08, "sub_bc7b3a0: table row f8 at +0x08");
static_assert(sizeof(TableRow) == 0x0c, "sub_bc7b3a0: table row stride 0x0c");

// Verbatim log of every call instruction in [0xbc7b3a0, 0xbc7b7c5) (rdis dis output,
// two spaces after the address):
// 0xbc7b41c  call 0xEEC75A0
// 0xbc7b44c  call 0xEEC73F0
// 0xbc7b4fb  call 0xEEC75A0
// 0xbc7b524  call 0xEEC73F0
// 0xbc7b5d7  call 0xEEC75A0
// 0xbc7b5ff  call 0xEEC73F0
// 0xbc7b7bf  call 0x78ED0   ; trap block — 0xbc7b7c4  int3 follows
// UNRESOLVED CALL = none    (0xEEC75A0/0xEEC73F0: class lift in native_boundary.tsv lines
//                            514/513, called as sub_eec75a0/sub_eec73f0 forward-declared in
//                            the header; 0x78ed0: class crt, entered through the slot read
//                            at 0xF9A8CF0 per hard rule 69)

LIFT_FN(sub_bc7b3a0, "sub_bc7b3a0", 0xbc7b3a0, sub_bc7b3a0, sub_bc7b3a0_footprint);

} // namespace native
