# Function 0xbc7b7d0 - sub_bc7b7d0 ("VV frame-graph builder")

## Source location
`src/client/features/render/native/bgfx/sub_bc7b7d0.cpp` + `.h`, first line
`// LIFT 0xbc7b7d0 size 0x28b 1.26.62.01 VV frame-graph builder`.
Registry: `LIFT_FN(sub_bc7b7d0, "sub_bc7b7d0", 0xbc7b7d0, sub_bc7b7d0, sub_bc7b7d0_footprint)`.

## Signature (exact x64 Microsoft ABI of the original)
`float* sub_bc7b7d0(float* out /*rcx*/, const float* in /*rdx*/)` returns `out` in rax
(`0xbc7ba0a  mov rax,rsi` where rsi holds the rcx argument).
The function writes [out, out+0x0C) (movlps out[0..8), movss out[8..0xC)) and reads
in[0x0] and in[0x0C] only. No game structs are touched.

## Register / argument map
- rcx (=rsi) = out, written at 0xbc7ba01 / 0xbc7ba04, returned in rax at 0xbc7ba0a
- rdx (=rdi) = in, read at 0xbc7b81d (in[0x0]) and 0xbc7b9ad (in[0x0C])
- xmm9 = in[0x0] at 0xbc7b81d; reused for later values

## Reversed source (complete)
Every instruction of [0xbc7b7d0, 0xbc7ba5b) falls inside one of the cited ranges below
(identical text is in sub_bc7b7d0.cpp).

// 0xbc7b7d0..0xbc7b864 - prologue (push rsi/rdi/rbx, sub rsp,0xB0, save xmm6-xmm14),
// v = inX / [0xEFD32AC] * [0xEFC6CF8]; a = thunkEec75a0(v); idxA = rnd(a)
float v = inX / dataF(0xEFD32AC) * dataF(0xEFC6CF8);   // 0xbc7b826 divss xmm6,[0xEFD32AC] ; 0xbc7b82e mulss xmm6,[0xEFC6CF8]
const float a = thunkEec75a0()(v);                       // 0xbc7b839  call 0xEEC75A0
const std::int64_t idxA = rnd(a);                        // 0xbc7b85a..0xbc7b864 (cvttss2si/sar/and/or)

// 0xbc7b867..0xbc7b899 - b = thunkEec73f0(v); check idxA >= 0x65; idxB = rnd(b); check idxB >= 0x65
const float b = thunkEec73f0()(v);                       // 0xbc7b86a  call 0xEEC73F0
if (idxA >= 0x65) errorPath();                           // 0xbc7b86f  cmp rbx,0x65 ; 0xbc7b873  jae 0xBC7BA55
const std::int64_t idxB = rnd(b);                        // 0xbc7b879..0xbc7b892
if (idxB >= 0x65) errorPath();                           // 0xbc7b895  cmp rax,0x65 ; 0xbc7b899  jae 0xBC7BA55

// 0xbc7b89f..0xbc7b8c1 - table row base: t1[idxA], t1[idxB] (rows {f0@0, pad@4, f8@8}, stride 0x0c)
const float t1A_f8 = t1[idxA].f8;                        // 0xbc7b8c1  movss xmm10,[rdx+rcx*4+8]
const float t1B_f8 = t1[idxB].f8;                        // 0xbc7b8ae  movss xmm14,[rdx+rax*4+8]
const float t1A_f0 = t1[idxA].f0;                        // 0xbc7b8bb  movsd xmm11,[rdx+rcx*4]
const float t1B_f0 = t1[idxB].f0;                        // 0xbc7b8b5  movsd xmm12,[rdx+rax*4]

// 0xbc7b8c8..0xbc7b8fa - blended = max(0,inX)/[0xF10D440]*[0xEFC6CF8], or [0xEFC6CF8] when [0xF10D440] < inX
const float t0 = std::max(0.0f, inX);                    // 0xbc7b8cb  maxss xmm0,xmm9
const float t = t0 / dataF(0xF10D440) * dataF(0xEFC6CF8);  // 0xbc7b8d8 divss ; 0xbc7b8e4 mulss [0xEFC6CF8]
const float blended = (dataF(0xF10D440) < inX)           // 0xbc7b8e8 cmpltss xmm7,xmm9
    ? dataF(0xEFC6CF8)                                   // 0xbc7b8f1 andnps ; 0xbc7b8f4 andps ; 0xbc7b8f7 orps
    : t;

// 0xbc7b8fd..0xbc7b91f - d = thunkEec75a0(blended); idxD = rnd(d); check idxD >= 0x65
const float d = thunkEec75a0()(blended);                 // 0xbc7b8fd  call 0xEEC75A0 ; xmm9 = d
const std::int64_t idxD = rnd(d);                        // 0xbc7b906..0xbc7b91f
if (idxD >= 0x65) errorPath();                           // 0xbc7b92a  cmp rbx,0x65 ; 0xbc7b92e  jae 0xBC7BA55

// 0xbc7b922..0xbc7b954 - e = thunkEec73f0(blended); idxE = rnd(e); check idxE >= 0x65
const float e = thunkEec73f0()(blended);                 // 0xbc7b925  call 0xEEC73F0
const std::int64_t idxE = rnd(e);                        // 0xbc7b934..0xbc7b94d
if (idxE >= 0x65) errorPath();                           // 0xbc7b950  cmp rdx,0x65 ; 0xbc7b954  jae 0xBC7BA55

// 0xbc7b95a..0xbc7b9c0 - z term
const float vma = v - a;                                 // 0xbc7b95a  subss xmm6,xmm8   (xmm8 still = a)
float z = t1A_f8 * (dataF(0xEEC8060) - vma);             // 0xbc7b95f movss xmm1,[0xEEC8060] ; 0xbc7b96a subss ; 0xbc7b96e mulss xmm10
z += t1B_f8 * vma;                                       // 0xbc7b973 mulss xmm14,xmm6 ; 0xbc7b978 addss xmm10,xmm14
const float blendMinusD = blended - d;                   // 0xbc7b98c subss xmm7,xmm9
const float c4blendD = dataF(0xEEC8060) - blendMinusD;   // 0xbc7b99b subss xmm1,xmm7
const float w = t2[idxD].f8 * c4blendD + t2[idxE].f8 * blendMinusD;  // 0xbc7b99f..0xbc7b9a9
z += dataF(0xF449710);                                   // 0xbc7b9b2 addss xmm10,[0xF449710]
z += w;                                                  // 0xbc7b9bb addss xmm10,xmm3
const float inZ = in[0x0C];                              // 0xbc7b9ad movss xmm2,[rdi+0xC]
z += inZ;                                                // 0xbc7b9c0 addss xmm10,xmm2

// 0xbc7b9c5..0xbc7ba04 - xy term and stores
xy = E*T1[idxA].f0 + (v-a)*T1[idxB].f0 + [0xF449720]_lane + C4blendD*T2[idxD].f0 + (blended-d)*T2[idxE].f0 + inZ
// implemented as __m128 with lane1 = same with bitcast(pad04) instead of f0:
__m128 xy = _mm_mul_ps(_mm_set1_ps(e), rowVec(t1, idxA));     // 0xbc7b9cd shufps ; 0xbc7b9d1 mulps xmm0,xmm11
xy += _mm_mul_ps(_mm_set1_ps(vma), rowVec(t1, idxB));         // 0xbc7b9c5 shufps xmm6 ; 0xbc7b9c9 mulps xmm6,xmm12 ; 0xbc7b9d5 addps
xy += c6;                                                     // 0xbc7b9f1 addps xmm0,[0xF449720]
xy += c4blendD*rowVec(t2, idxD) + (blended-d)*rowVec(t2, idxE);  // 0xbc7b9d8..0xbc7b9ee
xy += {inZ, inZ, 0, 0};                                       // 0xbc7b9fb unpcklps xmm2 ; 0xbc7b9fe addps
std::memcpy(out, &xy, 8);                                     // 0xbc7ba01 movlps [rsi],xmm2  W out[0..8)
out[8] = z;                                                   // 0xbc7ba04 movss [rsi+8],xmm10  W out[8..0xC)

// 0xbc7ba0a..0xbc7ba54 - return + epilogue
return out;                                                 // 0xbc7ba0a mov rax,rsi ; ... ; 0xbc7ba54 ret

// 0xbc7ba55..0xbc7ba5a - error path (unreachable unless the noreturn thunk returns)
errorPath():                                                // 0xbc7ba55  call 0x78ED0 ; 0xbc7ba5a  int3
    noreturn78ed0(); // reads slot 0xF9A8CF0, calls the noreturn crt thunk; __debugbreak() is the int3

where `rnd(x) = trunc(x) >= 0 ? trunc(x) : trunc(x - [0xEEE6700])` (cvttss2si pair + sar 0x3F sign adjust,
0xbc7b85a..0xbc7b864 / 0xbc7b906..0xbc7b91f / 0xbc7b934..0xbc7b94d), and `rowVec(t,i) = {t[i].f0,
bitcast<float>(t[i].pad04), 0, 0}` (the movsd at 0xbc7b8b5/0xbc7b8b5 reads f0+pad as a double, so the
multiply's high lane sees the pad bytes reinterpreted as float).

## Constants and data reads [V]
- 0xEFD32AC (float divisor C1, 0xbc7b826), 0xEFC6CF8 (float multiplier C2, 0xbc7b82e/0xbc7b8e4)
- 0xEEE6700 (float k subtracted before trunc, 0xbc7b842)
- 0xF10D440 (float C3, 0xbc7b8d0)
- 0xEEC8060 (float C4, 0xbc7b95f)
- 0xF449710 (float C5, 0xbc7b9b2)
- 0xF449720 (16 bytes = 4 floats C6 added by addps, 0xbc7b9f1)
- Table1 @ 0xF449BEC, rows {float f0@0x00; uint32 pad@0x04; float f8@0x08}, stride 0x0c, indexed 12*idx
  (0xbc7b8ae/0xbc7b8b5/0xbc7b8bb/0xbc7b8c1)
- Table2 @ 0xF44AA20, same row layout, stride 0x0c (0xbc7b991/0xbc7b99f/0xbc7b9a3...)

## Struct fields touched
None (no game structs). Writes: [out, out+0x0C) - offset 0x00 size 8 (movlps, W), offset 0x08 size 4
(movss, W). Reads: in[0x0] (R), in[0x0C] (R).

## Callees
- 0xEEC75A0 (called 0xbc7b839, 0xbc7b8fd): import thunk `jmp qword ptr [0xF9A8E60]` [V] - signature
  `float (float)`, slot 0xF9A8E60 read at call time (hard rule 69). Not in any table; not a blocker.
- 0xEEC73F0 (called 0xbc7b86a, 0xbc7b925): import thunk `jmp qword ptr [0xF9A8E08]` [V] - signature
  `float (float)`, slot 0xF9A8E08 read at call time (hard rule 69). Not in any table; not a blocker.
- 0x78ed0 (called 0xbc7ba55): `sub rsp,0x28 / call qword ptr [0xF9A8CF0] / int3` [V] - noreturn crt
  thunk, slot 0xF9A8CF0 read at call time (hard rule 69); 0xbc7ba5a int3 traps if it ever returns.
  Classified crt in docs/data/native_boundary.tsv but has no resolvable Sigs.json symbol, so the
  rule-69 slot read is used instead of a Boundary wrapper.

## OPEN questions
- The load-time contents of data slots 0xF9A8E60 / 0xF9A8E08 / 0xF9A8CF0 (which CRT math functions
  they resolve to) are not statically visible; irrelevant to the lift because the pointer is read
  from the slot at every call, exactly as the original's thunks do (hard rule 69). Not a blocker.
