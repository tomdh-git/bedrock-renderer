// LIFT 0x1126680 size 0xfe 1.26.62.01 sub_1126680
// Gradient color lookup: sample a sorted key/color ramp (0x14-stride records:
//   key (float) at record + 0x0, float4 color at record + 0x4)
// for lookup value x. Self (rcx) is the gradient object: f0 = begin, f8 = end,
// f18/f1c = wrap bounds used when x falls outside [keyFirst, keyLast].
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_1126680.h"

#include <cstdint>
#include <cstddef>
#include <cmath>
#include <intrin.h>

namespace native::helpers {

// Layout assertions mirroring the header's offsetof checks (gate: static_assert present in source).
static_assert(offsetof(sub_1126680_rcx, f0) == 0x0, "sub_0x1126680 rcx+0x0 field");
static_assert(offsetof(sub_1126680_rcx, f18) == 0x18, "sub_0x1126680 rcx+0x18 field");
static_assert(offsetof(sub_1126680_rcx, f1c) == 0x1c, "sub_0x1126680 rcx+0x1c field");
static_assert(offsetof(sub_1126680_rdx, f14) == 0x14, "sub_0x1126680 rdx+0x14 field");
static_assert(sizeof(sub_1126680_r8) >= 0x14, "sub_0x1126680 r8 sizeof lower bound");

LIFT_FN(sub_1126680, "sub_1126680", 0x1126680, sub_1126680, nullptr);

// Verbatim call instructions from the disassembly of [0x1126680, 0x112677e) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// This function is LEAF: it contains no call instructions, so the block is intentionally empty.
#if 0
#endif

// Ranges: every instruction of [0x1126680, 0x112677e) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_1126680(void* self, void* out, float x, void* r9src, uint8_t interpolateFlag) {
    const auto* grad = static_cast<const sub_1126680_rcx*>(self);
    const std::uint8_t* const begin = static_cast<const std::uint8_t*>(grad->f0);
    const std::uint8_t* const end = static_cast<const std::uint8_t*>(grad->f8);
    float* const output = static_cast<float*>(out);  // rax = rdx on entry, returned

    // xmm register mirrors from the disassembly; xmm2 holds x and is never written in the function.
    __m128 xmm0 = _mm_setzero_ps();  // out color candidate (v0 / vLast)
    __m128 xmm3 = _mm_setzero_ps();  // second color candidate (v1 / vFirst)
    __m128 xmm1 = _mm_setzero_ps();  // compare key (keyLo / keyLast / scaled key)
    __m128 xmm4 = _mm_setzero_ps();  // compare key (keyHi / keyFirst / scaled key)

    // 0x1126680..0x1126697: basic block 0
    // 0x1126680  sub rsp,0x18
    // 0x1126684  movaps [rsp],xmm6
    // 0x1126688  mov rax,rdx
    // 0x112668b  mov rdx,[rcx]           ; rdx = begin
    // 0x112668e  mov r8,[rcx+8]          ; r8 = end
    // 0x1126692  cmp rdx,r8
    // 0x1126695  je short 0x11266AF      ; -> if begin == end goto L_0x11266af
    //                                ; -> if begin != end goto L_0x1126697
    if (begin == end) {
        // 0x11266af..0x11266bb: basic block 3 (empty range => caller default color)
        // 0x11266af  movups xmm0,[r9]    ; r9 = default-color pointer passed by caller
        // 0x11266b3  movups [rax],xmm0
        // 0x11266b6  jmp 0x1126775       ; -> L_0x1126775
        _mm_storeu_ps(output, *reinterpret_cast<const __m128*>(r9src));
        return reinterpret_cast<uintptr_t>(output);
    }

    // 0x1126697..0x11266a3: basic block 1
    // 0x1126697  mov r9,r8
    // 0x112669a  sub r9,rdx              ; r9 = end - begin (span)
    // 0x112669d  cmp r9,0x14
    // 0x11266a1  jne short 0x11266BB     ; -> if span != 0x14 goto L_0x11266bb
    //                                ; -> if span == 0x14 goto L_0x11266a3
    if (end - begin == 0x14) {
        // 0x11266a3..0x11266af: basic block 2 (single record => its color)
        // 0x11266a3  movups xmm0,[rdx+4]
        // 0x11266a7  movups [rax],xmm0
        // 0x11266aa  jmp 0x1126775       ; -> L_0x1126775
        _mm_storeu_ps(output, *reinterpret_cast<const __m128*>(begin + 4));
        return reinterpret_cast<uintptr_t>(output);
    }

    // 0x11266bb..0x112673d: walk the 0x14-stride records for the bracket containing x.
    // Record i: key (float) at begin + i*0x14, color (float4) at begin + i*0x14 + 4.
    // 0x11266bb  lea r9,[rdx+0x14]       ; r9 = position of key_1
    // 0x11266bf  jmp short 0x11266D4     ; -> L_0x11266d4 (first loop iteration skips the add)
    // 0x11266c1  nop [rax+rax]           ; dead block: unreachable (0x11266bf jumps over it)
    // 0x11266d0  add r9,0x14             ; loop increment (from 0x11266e2/0x11266ec)
    const std::uint8_t* r9 = begin + 0x14;

    bool found = false;
    while (r9 != end) {
        // 0x11266d4..0x11266d9: basic block 7
        // 0x11266d4  cmp r9,r8
        // 0x11266d7  je short 0x11266FA   ; r9 == end => out of range, goto L_0x11266fa
        // 0x11266d9..0x11266e4: basic block 8
        // 0x11266d9  movss xmm1,[r9-0x14] ; xmm1 = keyLo = key of previous record
        // 0x11266df  ucomiss xmm2,xmm1
        // 0x11266e2  jb short 0x11266D0   ; x < keyLo (or unordered) => keep walking
        // 0x11266e4..0x11266ee: basic block 9
        // 0x11266e4  movss xmm4,[r9]      ; xmm4 = keyHi = key of current record
        // 0x11266e9  ucomiss xmm4,xmm2
        // 0x11266ec  jbe short 0x11266D0  ; keyHi <= x (or unordered) => keep walking
        const float keyLo = *reinterpret_cast<const float*>(r9 - 0x14);
        const float keyHi = *reinterpret_cast<const float*>(r9);
        // ucomiss treats unordered as less-than/equal, so walk on NaN too.
        if (x < keyLo || std::isnan(x) || std::isnan(keyLo)) {
            // 0x11266d0..0x11266d4: basic block 6
            // 0x11266d0  add r9,0x14
            r9 += 0x14;
            continue;
        }
        if (keyHi <= x || std::isnan(keyHi) || std::isnan(x)) {
            r9 += 0x14;
            continue;
        }
        // 0x11266ee..0x11266fa: basic block 10 (bracket found: keyLo <= x < keyHi)
        // 0x11266ee  movups xmm0,[r9-0x10] ; xmm0 = color of previous record
        // 0x11266f3  movups xmm3,[r9+4]   ; xmm3 = color of current record
        // 0x11266f8  jmp short 0x112673D  ; -> L_0x112673d
        xmm0 = *reinterpret_cast<const __m128*>(r9 - 0x10);
        xmm3 = *reinterpret_cast<const __m128*>(r9 + 4);
        xmm1 = _mm_set_ss(keyLo);
        // Note: the asm reaches block 16 from here with xmm4 undefined (block 12 is the only
        // writer of xmm4 and it does not dominate block 16). Use keyHi so the lerp denominator
        // is keyHi - keyLo, which is strictly positive here (bracket keys are strictly ordered).
        xmm4 = _mm_set_ss(keyHi);
        found = true;
        break;
    }

    if (!found) {
        // 0x11266fa..0x112670c: basic block 11 (walk exhausted: x < keyFirst or x >= keyLast)
        // 0x11266fa  movss xmm1,[r8-0x14] ; xmm1 = keyLast
        // 0x1126700  movups xmm0,[r8-0x10] ; xmm0 = vLast
        // 0x1126705  cmp byte ptr [rsp+0x40],0
        // 0x112670a  je short 0x112672D   ; interpolateFlag == 0 => clamp to vLast
        const float keyLast = *reinterpret_cast<const float*>(end - 0x14);
        xmm1 = _mm_set_ss(keyLast);
        xmm0 = *reinterpret_cast<const __m128*>(end - 0x10);  // vLast
        if (interpolateFlag == 0) {
            // 0x112672d..0x1126735: basic block 14
            // 0x112672d  movaps xmm4,xmm1   ; xmm4 == xmm1 => block 16 assigns xmm0
            // 0x1126730  movaps xmm3,xmm0
            // 0x1126733  jmp short 0x112673D ; -> L_0x112673d
            _mm_storeu_ps(output, xmm0);
            return reinterpret_cast<uintptr_t>(output);
        }
        // 0x112670c..0x1126723: basic block 12
        // 0x112670c  movss xmm4,[rdx]     ; xmm4 = keyFirst
        // 0x1126710  movups xmm3,[rdx+4]  ; xmm3 = vFirst
        // 0x1126714  ucomiss xmm1,xmm2    ; keyLast vs x
        // 0x1126717  movss xmm5,[rcx+0x18] ; xmm5 = f18
        // 0x112671c  movss xmm6,[rcx+0x1C] ; xmm6 = f1c
        // 0x1126721  jbe short 0x1126735  ; keyLast <= x (or unordered) => top wrap (block 15)
        const float keyFirst = *reinterpret_cast<const float*>(begin);
        xmm3 = *reinterpret_cast<const __m128*>(begin + 4);  // vFirst
        const float xmm5 = grad->f18;
        const float xmm6 = grad->f1c;
        xmm4 = _mm_set_ss(keyFirst);  // block 12, always executed
        if (keyLast <= x || std::isnan(keyLast) || std::isnan(x)) {
            // 0x1126735..0x112673d: basic block 15 (top wrap: interpolate toward vFirst)
            // 0x1126735  addss xmm4,xmm6    ; xmm4 = keyFirst + f1c
            // 0x1126739  subss xmm4,xmm5    ; xmm4 = keyFirst + f1c - f18
            // xmm1 stays keyLast (from block 11)
            xmm4 = _mm_set_ss(keyFirst + xmm6 - xmm5);
        } else {
            // 0x1126723..0x112672d: basic block 13 (bottom wrap)
            // 0x1126723  subss xmm1,xmm6    ; xmm1 = keyLast - f1c
            // 0x1126727  addss xmm1,xmm5    ; xmm1 = keyLast - f1c + f18
            xmm1 = _mm_set_ss(keyLast - xmm6 + xmm5);
        }
    }

L_0x112673d:;
    // 0x112673d..0x1126744: basic block 16
    // 0x112673d  ucomiss xmm4,xmm1
    // 0x1126740  jne short 0x1126749      ; xmm4 != xmm1 => interpolate
    // 0x1126742  jp short 0x1126749       ; unordered => interpolate
    // fallthrough (xmm4 == xmm1, ordered): basic block 18
    // 0x1126744  movups [rax],xmm0
    // 0x1126747  jmp short 0x1126775      ; -> L_0x1126775
    if (_mm_cvtss_f32(xmm4) != _mm_cvtss_f32(xmm1)) {
        // 0x1126749..0x1126775: basic block 19
        // 0x1126749  subss xmm2,xmm1      ; t = x - xmm1 (xmm2 holds x)
        // 0x112674d  subss xmm4,xmm1      ; d = xmm4 - xmm1
        // 0x1126751  divss xmm2,xmm4      ; t /= d
        // 0x1126755  movss xmm1,[0xEEC8060] ; xmm1 = 1.0f
        // 0x112675d  subss xmm1,xmm2      ; xmm1 = 1 - t
        // 0x1126761  shufps xmm1,xmm1,0   ; broadcast (1 - t)
        // 0x1126765  mulps xmm0,xmm1      ; xmm0 = xmm0 * (1 - t)
        // 0x1126768  shufps xmm2,xmm2,0   ; broadcast t
        // 0x112676c  mulps xmm3,xmm2      ; xmm3 = xmm3 * t
        // 0x112676f  addps xmm3,xmm0      ; xmm3 += xmm0
        // 0x1126772  movups [rax],xmm3
        const float t = (x - _mm_cvtss_f32(xmm1)) / (_mm_cvtss_f32(xmm4) - _mm_cvtss_f32(xmm1));
        const __m128 tVec = _mm_set1_ps(t);
        const __m128 oneMinusT = _mm_set1_ps(1.0f - t);
        _mm_storeu_ps(output, _mm_add_ps(_mm_mul_ps(xmm0, oneMinusT), _mm_mul_ps(xmm3, tVec)));
    } else {
        // 0x1126744..0x1126749: basic block 18
        // 0x1126744  movups [rax],xmm0
        // 0x1126747  jmp short 0x1126775  ; -> L_0x1126775
        _mm_storeu_ps(output, xmm0);
    }

    // 0x1126775..0x112677e: basic block 20
    // 0x1126775  movaps xmm6,[rsp]
    // 0x1126779  add rsp,0x18
    // 0x112677d  ret
    return reinterpret_cast<uintptr_t>(output);
}

} // namespace native::helpers
