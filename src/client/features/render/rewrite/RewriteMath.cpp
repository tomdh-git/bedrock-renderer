#include "client/features/render/rewrite/RewriteFunctions.h"
#include "client/features/render/rewrite/RewriteVerify.h"

// Q2f: the 4x4 float multiply at 0xAA6580 (1.26.62.01), fully reversed in BGFX_MAP 6ih and re-read for this file (all 0x1C6 bytes, no calls):
//   out = rcx, A = rdx (rows loaded as four xmm), B = r8 (16 floats read one by one and broadcast), returns rcx.
//   row i of out = ((B[i][0] * A.row0 + B[i][1] * A.row1) + B[i][2] * A.row2) + B[i][3] * A.row3, mulps/addps in exactly that order, every input is loaded before the first store (out may
//   alias A or B).
float* RewriteMath::mat4Multiply(float* out, const float* a, const float* b) {
    const __m128 a0 = _mm_loadu_ps(a);
    const __m128 a1 = _mm_loadu_ps(a + 4);
    const __m128 a2 = _mm_loadu_ps(a + 8);
    const __m128 a3 = _mm_loadu_ps(a + 12);
    __m128 rows[4];
    for (int i = 0; i < 4; ++i) {
        const float* r = b + i * 4;
        __m128 t = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(r[0]), a0), _mm_mul_ps(_mm_set1_ps(r[1]), a1));
        t = _mm_add_ps(t, _mm_mul_ps(_mm_set1_ps(r[2]), a2));
        rows[i] = _mm_add_ps(t, _mm_mul_ps(_mm_set1_ps(r[3]), a3));
    }
    _mm_storeu_ps(out, rows[0]);
    _mm_storeu_ps(out + 4, rows[1]);
    _mm_storeu_ps(out + 8, rows[2]);
    _mm_storeu_ps(out + 12, rows[3]);
    return out;
}

static float* rwMat4Detour(float* out, const float* a, const float* b);
static RewriteEntry sMat4Entry("Math::mat4Multiply", "Math::mat4Multiply", 0xAA6580, reinterpret_cast<void*>(&rwMat4Detour));
static const RewriteReg sMat4Reg(sMat4Entry);

static float* rwMat4Detour(float* out, const float* a, const float* b) {
    RewriteEntry& e = sMat4Entry;
    const uint64_t calls = e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0)
        return e.original<&rwMat4Detour>()(out, a, b);
    if (mode == RewriteMode::On) {
        if ((calls & 15) != 0)
            return RewriteMath::mat4Multiply(out, a, b);
        RewriteTimed timed(e, e.ticksRewrite);
        return RewriteMath::mat4Multiply(out, a, b);
    }
    // Shadow / Verify: pure function, two private result buffers. The inputs are copied first because out may alias them.
    RewriteBusy::Scope busy;
    float inA[16], inB[16], original[16], rewrite[16];
    std::memcpy(inA, a, sizeof(inA));
    std::memcpy(inB, b, sizeof(inB));
    {
        RewriteTimed timed(e, e.ticksOriginal);
        e.original<&rwMat4Detour>()(out, a, b);
    }
    std::memcpy(original, out, sizeof(original));
    {
        RewriteTimed timed(e, e.ticksRewrite);
        RewriteMath::mat4Multiply(rewrite, inA, inB);
    }
    e.evaluated.fetch_add(1, std::memory_order_relaxed);
    RewriteVerify::compare(e, mode, "out[16 floats]", original, rewrite, sizeof(original));
    return out;
}
