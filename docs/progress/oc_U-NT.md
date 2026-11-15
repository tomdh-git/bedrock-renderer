# U-NT: nametag producer 0x11276b0 — detailed instruction decode (1.26.62.01)

## NEXT
All four ranges decoded: 0x11278c5..0x1127b06, 0x1127c35..0x1127d23, 0x11283d3..0x11285f4, 0x112888e..0x1128a40. File complete.

## Context
Unit U-NT (nametag producer 0x11276b0), NametagRenderer render of one tag. Sole caller 0x539e3b0. Context from docs/functions/11276b0.md: signature `void render(RenderCtx* r13 /*rcx*/, const CameraRec* r14 /*rdx*/, const NametagObj* rbx /*r8*/, SharedPair* rsi /*r9*/)`. Ranges below are the remaining un-decoded regions from the context dossier (items 3, 4, 7, 8).

---

## Range 1: 0x11278c5..0x1127b06 — billboard rotation math (delta, length, sin/cos, quaternion)

### Phase 1: 0x11278c5..0x1127945 — camera–nametag delta, squared length, sqrt
```
// dx = cam.x - tag.x  (xmm0)
// early-out: if dx == 0, xmm4 = F07FAF0 (1.0f), else xmm4 = dx
// xmm6 = dx*dx
// yz = (cam.yz - tag.yz) as packed singles  (xmm2)
// if |yz| == 0, yz = (1.0,1.0)
// lenSq = yx^2 + yy^2 + z^2 + dx^2  (packed add)
// len = sqrt(lenSq)
// invLen = F0D3400 / len   (F0D3400 = ? )
```

```
0x11278c5  movss xmm0,[r14]
0x11278ca  subss xmm0,[rbx+0x50]
0x11278cf  xorps xmm13,xmm13
0x11278d3  ucomiss xmm0,xmm13
0x11278d7  movss xmm5,[0xF07FAF0]                        ; [data_f07faf0]
0x11278df  movaps xmm4,xmm0
0x11278e2  jne short 0x11278E7                           ; -> loc_11278e7
0x11278e4  movaps xmm4,xmm5

loc_11278e7:  ; from 11278e2
0x11278e7  movaps xmm3,xmm4
0x11278ea  mulss xmm3,xmm4
0x11278ee  movaps xmm6,xmm0
0x11278f1  mulss xmm6,xmm0
0x11278f5  movsd xmm2,[r14+4]
0x11278fb  movsd xmm1,[rbx+0x54]
0x1127900  subps xmm2,xmm1
0x1127903  movaps xmm1,xmm2
0x1127906  shufps xmm1,xmm2,0x55
0x112790a  ucomiss xmm1,xmm13
0x112790e  jne short 0x1127913                           ; -> loc_1127913
0x1127910  movaps xmm1,xmm5

loc_1127913:  ; from 112790e
0x1127913  mulss xmm11,[0xF09BDDC]                       ; [data_f09bddc]
0x112791c  movaps xmm5,xmm2
0x112791f  mulss xmm5,xmm2
0x1127923  addss xmm5,xmm6
0x1127927  unpcklps xmm5,xmm3
0x112792a  movq xmm6,xmm1
0x112792e  xorps xmm14,xmm14
0x1127932  shufps xmm6,xmm14,0xE2
0x1127937  shufps xmm1,xmm2,0xD4
0x112793b  shufps xmm1,xmm2,0x52
0x112793f  mulps xmm1,xmm1
0x1127942  addps xmm1,xmm5
0x1127945  sqrtps xmm3,xmm1
```

- xmm0 = [r14] - [rbx+0x50] = camera.x - nametag.x [V: 0x11278c5, 0x11278ca]
- xmm13 = 0.0 (zero register) [V: 0x11278cf]
- Branch: if dx != 0 skip, else xmm4 = [0xF07FAF0] (constant 1.0f likely) [V: 0x11278d7, 0x11278e2, 0x11278e4]
- xmm3 = xmm4*xmm4 = dx² [V: 0x11278e7, 0x11278ea]
- xmm6 = xmm0*xmm0 = dx² (duplicate) [V: 0x11278ee, 0x11278f1]
- yz delta: xmm2 = [r14+4] - [rbx+0x54] = camera.yz - nametag.yz [V: 0x11278f5, 0x11278fb, 0x1127900]
- xmm1 = shuffle yz for zero-check [V: 0x1127903-0x1127906]
- Branch: if yz != 0 skip, else xmm1 = 1.0 vector [V: 0x112790a, 0x112790e, 0x1127910]
- xmm11 *= [0xF09BDDC] (scale constant) [V: 0x1127913] — likely tag scale * const
- xmm5 = yz² + dx² (unpacked into packed form) [V: 0x112791c-0x1127927]
- xmm6 = shuffle of yz (sign-masked: 0xE2 = flip signs of y,z) [V: 0x112792a, 0x1127932]
- xmm1 = yz² packed (0xD4 then 0x52 shuffles then mulps) [V: 0x1127937-0x112793f]
- xmm1 = lenSq packed [V: 0x1127942]
- xmm3 = sqrt(lenSq) = length [V: 0x1127945]

### Phase 2: 0x1127948..0x11279be — normalize, quaternion pair, polynomial approx start
```
// invLen = F0D3400 / len  (xmm1)
// xmm3 = invLen (broadcast)
// xmm6 = (negY, negZ, 0, 0) pattern
// xmm0 = (dx, dx, ?, ?)
// dir = invLen * (dx, -dy, -dz)  → unit direction
// cross-like terms in xmm5/xmm4
// poly: xmm7 = x^3 * c0, then x^5 term, etc. (sin/cos polynomial approximation)
```

```
0x1127948  movaps xmm1,[0xEFD3400]                       ; [data_efd3400]
0x112794f  divps xmm1,xmm3
0x1127952  movaps xmm3,xmm1
0x1127955  shufps xmm3,xmm1,0x55
0x1127959  mulps xmm3,xmm6
0x112795c  unpcklps xmm0,xmm4
0x112795f  mulps xmm0,xmm1
0x1127962  movaps xmm6,xmm0
0x1127965  shufps xmm6,xmm0,0x55
0x1127969  movaps xmm4,xmm6
0x112796c  mulss xmm4,xmm13
0x1127971  movaps xmm5,xmm3
0x1127974  mulss xmm5,xmm13
0x1127979  addss xmm5,xmm4
0x112797d  movaps xmm4,xmm3
0x1127980  shufps xmm4,xmm3,0x55
0x1127984  subss xmm5,xmm4
0x1127988  mulss xmm4,xmm13
0x112798d  addss xmm4,xmm6
0x1127991  shufps xmm1,xmm1,0
0x1127995  mulps xmm1,xmm2
0x1127998  mulps xmm3,xmm1
0x112799b  mulss xmm6,xmm0
0x112799f  addss xmm6,xmm3
0x11279a3  shufps xmm3,xmm3,0x55
0x11279a7  addss xmm3,xmm6
0x11279ab  movss xmm0,[0xF0CD500]                        ; [data_f0cd500]
0x11279b3  movaps xmm7,xmm5
0x11279b6  mulss xmm7,xmm0
0x11279ba  mulss xmm7,xmm5
0x11279be  mulss xmm7,xmm5
```

- xmm1 = F0D3400 / len = inverse length [V: 0x1127948, 0x112794f]
- xmm3 = invLen broadcast [V: 0x1127952, 0x1127955]
- xmm3 = invLen * signMaskedYZ [V: 0x1127959]
- xmm0 = (dx, dx) unpicked * invLen [V: 0x112795c, 0x112795f]
- xmm6 = direction components [V: 0x1127962-0x1127969]
- xmm5 = cross/dot combo from quaternion terms [V: 0x1127971-0x112798d]
- xmm3 = more quaternion term [V: 0x1127991-0x11279a7]
- Polynomial: xmm7 = x * c0, then x*x, then x*x again → x³ * c0 pattern [V: 0x11279ab-0x11279be]

### Phase 3: 0x11279c2..0x1127a4e — sin/cos polynomial, import call setup
```
// xmm2 = [0xF0CD504] (poly constant)
// xmm7 = x^3*c0 - x^5*c2 + c1  (sin approx: x - x^3/6 + x^5/120)
// xmm0 = x^3 * (xmm3)^3 ... cos-ish poly
// xmm9 = sign mask, xmm10 = 0.5f
// xmm9 = copysign-like blend: if xmm1 < 0 use -result else result
// Same for xmm7 vs xmm4
// xmm0 = poly const [0xEEE7C00]
// xmm7 *= const, xmm9 *= const  (scale by PI or similar)
// rdi = import ptr [0xF9A8E18] = sinf
// xmm6 = sinf(xmm7)
// rdi = import ptr [0xF9A8F48] = cosf
// xmm8 = cosf(xmm7), xmm7 = cosf(xmm9)
```

```
0x11279c2  movss xmm2,[0xF0CD504]                        ; [data_f0cd504]
0x11279ca  mulss xmm5,xmm2
0x11279ce  subss xmm7,xmm5
0x11279d2  movss xmm5,[0xEF3F018]                        ; [data_ef3f018]
0x11279da  addss xmm7,xmm5
0x11279de  mulss xmm0,xmm3
0x11279e2  mulss xmm0,xmm3
0x11279e6  mulss xmm0,xmm3
0x11279ea  mulss xmm3,xmm2
0x11279ee  subss xmm0,xmm3
0x11279f2  addss xmm0,xmm5
0x11279f6  movaps xmm10,[0xEF3F050]                      ; [data_ef3f050]
0x11279fe  xorps xmm9,xmm9
0x1127a02  cmpltss xmm9,xmm1
0x1127a08  movaps xmm1,xmm9
0x1127a0c  andps xmm1,xmm0
0x1127a0f  xorps xmm0,xmm10
0x1127a13  andnps xmm9,xmm0
0x1127a17  orps xmm9,xmm1
0x1127a1b  xorps xmm0,xmm0
0x1127a1e  cmpltss xmm0,xmm4
0x1127a23  movaps xmm1,xmm0
0x1127a26  andnps xmm1,xmm7
0x1127a29  xorps xmm7,xmm10
0x1127a2d  andps xmm7,xmm0
0x1127a30  orps xmm7,xmm1
0x1127a33  movss xmm0,[0xEEE7C00]                        ; [data_eee7c00]
0x1127a3b  mulss xmm7,xmm0
0x1127a3f  mulss xmm9,xmm0
0x1127a44  mov rdi,[0xF9A8E18]                           ; [data_f9a8e18]
0x1127a4b  movaps xmm0,xmm7
0x1127a4e  call rdi
```

- xmm7 = sin-approx result: x³*c2 subtracted, +0xEF3F018 added (constant) [V: 0x11279c2-0x11279da]
- xmm0 = cos-approx: xmm0*xmm3³ - xmm3*xmm2 + 0xEF3F018 [V: 0x11279de-0x11279f2]
- xmm10 = [0xEF3F050] (constant, likely 0.5f or sign bit) [V: 0x11279f6]
- Sign-mask blend: xmm9 = (xmm1 < 0) ? -xmm0 : xmm0 [V: 0x11279fe-0x1127a17]
- Same pattern for xmm7 vs xmm4 [V: 0x1127a1b-0x1127a30]
- xmm0 = [0xEEE7C00] (constant, likely PI or PI/2) [V: 0x1127a33]
- xmm7 *= const, xmm9 *= const [V: 0x1127a3b, 0x1127a3f]
- rdi = import [0xF9A8E18] (sinf) [V: 0x1127a44]
- xmm6 = sinf(xmm7) [V: 0x1127a4b, 0x1127a4e]

### Phase 4: 0x1127a50..0x1127a88 — imported cosf calls, quaternion multiply
```
// xmm8 = cosf(xmm9)   [second import at 0xF9A8F48]
// xmm7 = cosf(xmm7)   [first import at 0xF9A8F48]
// xmm7 = cosf(xmm9)   [second import at 0xF9A8F48]
// xmm2 = (cos, sin, cos, sin) packed from xmm0/xmm8
// xmm14 = xmm14 * xmm2  (accumulate rotation into quaternion pair xmm14)
```

```
0x1127a50  movaps xmm6,xmm0
0x1127a53  movaps xmm0,xmm9
0x1127a57  call rdi
0x1127a59  movaps xmm8,xmm0
0x1127a5d  mov rdi,[0xF9A8F48]                           ; [data_f9a8f48]
0x1127a64  movaps xmm0,xmm7
0x1127a67  call rdi
0x1127a69  movaps xmm7,xmm0
0x1127a6c  movaps xmm0,xmm9
0x1127a70  call rdi
```

- xmm6 = previous sin result saved [V: 0x1127a50]
- xmm8 = cosf(xmm9) [V: 0x1127a53-0x1127a59]
- rdi = import [0xF9A8F48] (cosf) [V: 0x1127a5d]
- xmm7 = cosf(xmm7) [V: 0x1127a64-0x1127a69]
- xmm7 = cosf(xmm9) [V: 0x1127a6c, 0x1127a70] — overwrites previous cosf result

Wait, this looks like xmm7 gets cosf(xmm7) then xmm0=xmm9, call rdi → result in xmm0 but not moved to xmm7. Let me re-read:

```
0x1127a64  movaps xmm0,xmm7        ; xmm0 = xmm7 (which is sin-approx result scaled)
0x1127a67  call rdi                 ; xmm0 = cosf(sinResult) → but this was already called above...
0x1127a69  movaps xmm7,xmm0        ; xmm7 = cosf(xmm7)
0x1127a6c  movaps xmm0,xmm9        ; xmm0 = xmm9 (cos-approx result scaled)
0x1127a70  call rdi                 ; xmm0 = cosf(cosResult) → result in xmm0, not stored to xmm7
```

Hmm, the call at 0x1127a70 returns in xmm0 but xmm7 was already set at 0x1127a69. So xmm7 = cosf(sinApprox) and xmm0 = cosf(cosApprox). Then at 0x1127a72, `mov eax,[rbx+0x88]` loads the mode byte.

Actually wait, looking again at phase 3: `call rdi` at 0x1127a4e puts sinf result in xmm0, then `movaps xmm6,xmm0` saves it. Then xmm0=xmm9, call rdi → cosf(xmm9) in xmm0 → saved to xmm8. Then rdi changed to cosf import, xmm0=xmm7, call rdi → cosf(xmm7) in xmm0 → saved to xmm7. Then xmm0=xmm9, call rdi → cosf(xmm9) again in xmm0 (but xmm7 already has the previous result).

This is the sin/cos computation via the polynomial approximations AND the actual libm calls. The polynomial results (xmm7, xmm9) are passed to sinf/cosf, which seems redundant — possibly the polynomial is a fast approximation and the libm calls are the accurate versions, used depending on some condition. Or the polynomial IS the computation and the libm calls refine it.

Actually, looking more carefully: xmm7 after phase 3 is the sin approximation result scaled by [0xEEE7C00]. Then xmm0=xmm7, call cosf → xmm7 = cosf(sinApprox)? That doesn't make sense.

Let me re-read phase 3 end:
```
0x1127a33  movss xmm0,[0xEEE7C00]     ; xmm0 = const
0x1127a3b  mulss xmm7,xmm0            ; xmm7 = sinApprox * const
0x1127a3f  mulss xmm9,xmm0            ; xmm9 = cosApprox * const
0x1127a44  mov rdi,[0xF9A8E18]        ; rdi = sinf import
0x1127a4b  movaps xmm0,xmm7           ; xmm0 = sinApprox*const
0x1127a4e  call rdi                   ; xmm0 = sinf(sinApprox*const)
0x1127a50  movaps xmm6,xmm0           ; xmm6 = sinf(...)
0x1127a53  movaps xmm0,xmm9           ; xmm0 = cosApprox*const
0x1127a57  call rdi                   ; xmm0 = sinf(cosApprox*const)  ← using sinf import again!
0x1127a59  movaps xmm8,xmm0           ; xmm8 = sinf(cosApprox*const)
0x1127a5d  mov rdi,[0xF9A8F48]        ; rdi = cosf import
0x1127a64  movaps xmm0,xmm7           ; xmm0 = sinApprox*const
0x1127a67  call rdi                   ; xmm0 = cosf(sinApprox*const)
0x1127a69  movaps xmm7,xmm0           ; xmm7 = cosf(sinApprox*const)
0x1127a6c  movaps xmm0,xmm9           ; xmm0 = cosApprox*const
0x1127a70  call rdi                   ; xmm0 = cosf(cosApprox*const)  → result in xmm0, not stored
```

So: xmm6 = sinf(sinApprox*const), xmm8 = sinf(cosApprox*const), xmm7 = cosf(sinApprox*const), and cosf(cosApprox*const) is computed but left in xmm0 (used at 0x1127a7e as xmm2 = xmm0).

This is computing sin and cos of the yaw angle via sinf/cosf, with the polynomial approximations possibly serving as initial guesses or being unused (dead code from fast-approx path). The results xmm6/xmm7/xmm8 are the actual sin/cos values.

### Phase 5: 0x1127a8c..0x1127b01 — quaternion combine, mode byte override
```
// xmm2 = (xmm0, xmm8, ...) packed  (cos/sin pairs)
// xmm14 = xmm14 * xmm2  (quaternion multiply accumulate)
// xmm2 = shufps(xmm2, 0xE1)
// xmm1 = xmm14 + xmm2, xmm14 = xmm14 - xmm2, xmm14 = shufps shuffle
// xmm1 = [rbx+0x80] (stored sin/cos override)
// xmm9 = sign mask from eax ([rbx+0x88] mode byte)
// xmm1 = blend(xmm1, signMask)
// if byte [rbx+0x88] != 0: xmm7 = [rbx+0x78], xmm6 = [rbx+0x7C] (override sin/cos)
// else: xmm6 = xmm6*xmm0 - xmm8*xmm7...  (rotation composition)
//       xmm6 = xmm6*xmm13 + xmm8
```

```
0x1127a8c  shufps xmm2,xmm2,0xE1
0x1127a90  movaps xmm1,xmm14
0x1127a94  addps xmm1,xmm2
0x1127a97  subps xmm14,xmm2
0x1127a9b  shufps xmm14,xmm1,1
0x1127aa0  shufps xmm14,xmm1,0xE2
0x1127aa5  movsd xmm1,[rbx+0x80]
0x1127aad  shufps xmm1,xmm1,0xE1
0x1127ab1  movd xmm2,eax
0x1127ab5  pshufd xmm9,xmm2,0
0x1127abb  pslld xmm9,0x1F
0x1127ac1  psrad xmm9,0x1F
0x1127ac7  andps xmm1,xmm9
0x1127acb  andnps xmm9,xmm14
0x1127acf  orps xmm9,xmm1
0x1127ad3  test al,al
0x1127ad5  jne short 0x1127AFC                           ; -> loc_1127afc
0x1127ad7  mulss xmm6,xmm0
0x1127adb  mulss xmm8,xmm7
0x1127ae0  movaps xmm0,xmm8
0x1127ae4  mulss xmm0,xmm13
0x1127ae9  movaps xmm7,xmm6
0x1127aec  subss xmm7,xmm0
0x1127af0  mulss xmm6,xmm13
0x1127af5  addss xmm6,xmm8
0x1127afa  jmp short 0x1127B06                           ; -> loc_1127b06

loc_1127afc:  ; from 1127ad5
0x1127afc  movss xmm7,[rbx+0x78]
0x1127b01  movss xmm6,[rbx+0x7C]
```

- xmm2 = repacked sin/cos pairs [V: 0x1127a8c]
- Quaternion multiply: xmm1 = xmm14 + xmm2, xmm14 = xmm14 - xmm2, then shuffle [V: 0x1127a90-0x1127aa0]
- xmm1 = [rbx+0x80] (stored sin/cos override from nametag) [V: 0x1127aa5]
- xmm9 = sign-mask from mode byte eax=[rbx+0x88] [V: 0x1127ab1-0x1127ac1]
- xmm1 = sign-blended override value [V: 0x1127ac7-0x1127acf]
- Branch: if mode byte != 0, use stored values [rbx+0x78], [rbx+0x7C] [V: 0x1127ad3, 0x1127ad5]
- Fall-through (mode == 0): compose rotation from xmm6,xmm8,xmm7,xmm0,xmm13 [V: 0x1127ad7-0x1127af5]
- Override path: xmm7 = [rbx+0x78], xmm6 = [rbx+0x7C] [V: 0x1127afc, 0x1127b01]

---

## Range 2: 0x1127c35..0x1127d23 — mat4 construction and matrix multiply

### Phase 1: 0x1127c35..0x1127cd0 — build 3x3 rotation into mat4 at rbp+0x1E0
```
// xmm3 = xmm9 + xmm9  (2*sin or 2*cos)
// xmm13 = xmm8 * xmm3
// xmm4 = xmm7 + xmm7  (2*cos or 2*sin)
// xmm14 = xmm7 * xmm4
// xmm2 -= xmm14
// xmm15 = xmm13 + xmm14
// xmm14 = unpack(xmm2) - xmm13  → matrix row 1
// xmm5 -= xmm13 → [rbp+0x1E0] = m00
// [rbp+0x1E4] = xmm15  → m01
// xmm13 = xmm4*xmm8 - xmm3*xmm6 → [rbp+0x1E8] = m02
// [rbp+0x1F0] = xmm14 (low 2)  → m10,m11
// xmm13 = xmm1*xmm8 + xmm3*xmm7 → [rbp+0x1F8] = m12
// [rbp+0x1FC] = 0
// xmm5 += xmm4 → [rbp+0x200] = m20
// xmm1 -= xmm3 → [rbp+0x204] = m21
// xmm2 -= xmm0 → [rbp+0x208] = m22
```

```
0x1127c35  movaps xmm3,xmm9
0x1127c39  addps xmm3,xmm9
0x1127c3d  movaps xmm13,xmm8
0x1127c41  mulps xmm13,xmm3
0x1127c45  movaps xmm4,xmm7
0x1127c48  addss xmm4,xmm7
0x1127c4c  movaps xmm14,xmm7
0x1127c50  mulss xmm14,xmm4
0x1127c55  subss xmm2,xmm14
0x1127c5a  movaps xmm14,xmm6
0x1127c5e  mulss xmm14,xmm4
0x1127c63  movaps xmm15,xmm13
0x1127c67  addss xmm15,xmm14
0x1127c6c  unpcklps xmm14,xmm2
0x1127c70  subps xmm14,xmm13
0x1127c74  shufps xmm13,xmm13,0x55
0x1127c79  subss xmm5,xmm13
0x1127c7e  movss [rbp+0x1E0],xmm5
0x1127c86  movss [rbp+0x1E4],xmm15
0x1127c8f  mulss xmm4,xmm8
0x1127c94  movaps xmm5,xmm3
0x1127c97  mulss xmm5,xmm6
0x1127c9b  movaps xmm13,xmm4
0x1127c9f  subss xmm13,xmm5
0x1127ca4  movss [rbp+0x1E8],xmm13
0x1127cad  movlps [rbp+0x1F0],xmm14
0x1127cb5  mulss xmm1,xmm8
0x1127cba  mulss xmm3,xmm7
0x1127cbe  movaps xmm13,xmm1
0x1127cc2  addss xmm13,xmm3
0x1127cc7  movss [rbp+0x1F8],xmm13
0x1127cd0  mov dword ptr [rbp+0x1FC],0
```

- xmm3 = xmm9+xmm9 = 2*xmm9 [V: 0x1127c35, 0x1127c39]
- xmm13 = xmm8 * xmm3 [V: 0x1127c3d, 0x1127c41]
- xmm4 = xmm7 + xmm7 = 2*xmm7 [V: 0x1127c45, 0x1127c48]
- xmm14 = xmm7 * xmm4 = 2*xmm7² [V: 0x1127c4c, 0x1127c50]
- xmm2 -= xmm14 [V: 0x1127c55]
- xmm14 = xmm6 * xmm4 [V: 0x1127c5a, 0x1127c5e]
- xmm15 = xmm13 + xmm14 [V: 0x1127c63, 0x1127c67]
- xmm14 = unpck(xmm2) - xmm13 → row data [V: 0x1127c6c, 0x1127c70]
- xmm13 = shufps(xmm13, 0x55) [V: 0x1127c74]
- xmm5 -= xmm13 → stored at [rbp+0x1E0] (mat4[0][0]) [V: 0x1127c79, 0x1127c7e]
- [rbp+0x1E4] = xmm15 (mat4[0][1]) [V: 0x1127c86]
- xmm4 *= xmm8 [V: 0x1127c8f]
- xmm13 = xmm3*xmm6 [V: 0x1127c94, 0x1127c97]
- xmm13 = xmm4 - xmm13 → [rbp+0x1E8] (mat4[0][2]) [V: 0x1127c9b-0x1127ca4]
- [rbp+0x1F0] = low 64 bits of xmm14 (mat4[1][0], [1][1]) [V: 0x1127cad]
- xmm13 = xmm1*xmm8 + xmm3*xmm7 → [rbp+0x1F8] (mat4[1][2]) [V: 0x1127cb5-0x1127cc7]
- [rbp+0x1FC] = 0 (mat4[1][3]) [V: 0x1127cd0]

### Phase 2: 0x1127cd0..0x1127d23 — store remaining mat4, w=1, call 0xAA6580
```
// [rbp+0x200] = xmm5 + xmm4  (mat4[2][0])
// [rbp+0x204] = xmm1 - xmm3  (mat4[2][1])
// [rbp+0x208] = xmm2 - xmm0  (mat4[2][2])
// [rbp+0x20C] = 0  (mat4[2][3])
// [rbp+0x21C] = 0x3F800000  (mat4[3][3] = 1.0f)
// rcx = &[rbp+0x48]  (output matrix)
// r15 = &[rbp+0x1E0]  (local mat4, input B)
// rdx = r12  (input A = ctx stack top matrix)
// r8 = r15
// call 0xAA6580(out=rcx, A=rdx, B=r8)  mat4 multiply
```

```
0x1127cda  addss xmm5,xmm4
0x1127cde  movss [rbp+0x200],xmm5
0x1127ce6  subss xmm1,xmm3
0x1127cea  movss [rbp+0x204],xmm1
0x1127cf2  subss xmm2,xmm0
0x1127cf6  movss [rbp+0x208],xmm2
0x1127cfe  xorps xmm0,xmm0
0x1127d01  movups [rbp+0x20C],xmm0
0x1127d08  mov dword ptr [rbp+0x21C],0x3F800000
0x1127d12  lea rcx,[rbp+0x48]
0x1127d16  lea r15,[rbp+0x1E0]
0x1127d1d  mov rdx,r12
0x1127d20  mov r8,r15
0x1127d23  call 0xAA6580                                 ; -> sub_aa6580
```

- [rbp+0x200] = xmm5+xmm4 (mat4[2][0]) [V: 0x1127cda, 0x1127cde]
- [rbp+0x204] = xmm1-xmm3 (mat4[2][1]) [V: 0x1127ce6, 0x1127cea]
- [rbp+0x208] = xmm2-xmm0 (mat4[2][2]) [V: 0x1127cf2, 0x1127cf6]
- [rbp+0x20C] = 0 (mat4[2][3]) [V: 0x1127cfe, 0x1127d01]
- [rbp+0x21C] = 0x3F800000 = 1.0f (mat4[3][3]) [V: 0x1127d08]
- rcx = output matrix at [rbp+0x48] [V: 0x1127d12]
- r15 = local mat4 at [rbp+0x1E0] [V: 0x1127d16]
- rdx = r12 = input matrix A (ctx stack top) [V: 0x1127d1d]
- r8 = r15 = input matrix B (local rotation mat4) [V: 0x1127d20]
- call 0xAA6580(out=rbp+0x48, A=r12/top, B=rbp+0x1e0) [V: 0x1127d23]

---

## Range 3: 0x11283d3..0x11285f4 — per-line width measurement loop

### Phase 1: 0x11283d3..0x112843b — loop bounds, string pointer (SSO vs heap)
```
// rcx = [rbp+0x1A0] - [rbp+0x198]  (vector<string> end - begin)
// rcx >>= 5  (divide by 32 = sizeof(std::string))
// if rbx >= rcx: goto end (loop exit)
// r13 = rbx * 32  (line index * stride)
// if [rax+r13+0x18] < 0x10: SSO path, rcx = rax+r13  (string data inline)
// else: rcx = [rax+r13]  (heap pointer)
// rax = [rax+r13+0x10]  (string size or SSO buffer)
// [rbp+0x28] = rcx (string ptr)
// [rbp+0x30] = rax (string size/chars)
// rax = [rsi]  (SharedPair)
// rax = [rax+0x30]  (font callback object)
// rcx = rsi
// rdx = &[rbp+0x28]  (string arg)
// xmm2 = xmm6
// r9d = 0
// call [0xF99FFA0]  (sub_eea6040, font width callback)
```

```
0x11283d3  mov rax,[rbp+0x198]
0x11283da  mov rcx,[rbp+0x1A0]
0x11283e1  sub rcx,rax
0x11283e4  sar rcx,5
0x11283e8  cmp rbx,rcx
0x11283eb  jae 0x11285F4                                 ; -> loc_11285f4
0x11283f1  mov r13,rbx
0x11283f4  shl r13,5
0x11283f8  cmp qword ptr [rax+r13+0x18],0x10
0x11283fe  jb short 0x1128410                           ; -> loc_1128410
0x1128400  mov rcx,[rax+r13]
0x1128404  jmp short 0x1128414                           ; -> loc_1128414
0x1128406  nop [rax+rax]

loc_1128410:  ; from 11283fe
0x1128410  lea rcx,[rax+r13]

loc_1128414:  ; from 1128404
0x1128414  mov rax,[rax+r13+0x10]
0x1128419  mov [rbp+0x28],rcx
0x112841d  mov [rbp+0x30],rax
0x1128421  mov rax,[rsi]
0x1128424  mov rax,[rax+0x30]
0x1128428  mov rcx,rsi
0x112842b  lea rdx,[rbp+0x28]
0x112842f  movaps xmm2,xmm6
0x1128432  xor r9d,r9d
0x1128435  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x112843b  nop
```

- Loop counter rbx vs count = (end-begin)/32 [V: 0x11283d3-0x11283eb]
- r13 = rbx << 5 = line index * sizeof(std::string) [V: 0x11283f1, 0x11283f4]
- SSO check: if [rax+r13+0x18] < 0x10 use inline buffer, else heap pointer [V: 0x11283f8, 0x11283fe]
- String ptr at [rbp+0x28], size/chars at [rbp+0x30] [V: 0x1128414-0x112841d]
- Font object = [rsi+0x30] [V: 0x1128421, 0x1128424]
- call [0xF99FFA0] = sub_eea6040 (font width/callback) [V: 0x1128435]

### Phase 2: 0x112843c..0x11284ad — line index → float, y-offset setup
```
// test rbx,rbx; if rbx >= 0: xmm0 = (float)rbx
// else: xmm0 = (float)((rbx>>1) | (rbx&1)) * 2  (round-to-even for negative)
// [rbp+0x60] = 0 (byte flag)
// reload string ptr from [rbp+0x198+r13]
// SSO check again for second use
// rdx = string ptr (heap or inline)
// r8d = eax >> 31 sign adjust → r8d = (eax + (eax>>31)) >> 1  (arithmetic mean / 2)
// xmm3 = (float)r8d XOR xmm10  (negate if xmm10 sign bit)
// xmm0 *= xmm7  (lineY * yScale)
```

```
0x112843c  test rbx,rbx
0x112843f  js short 0x1128450                           ; -> loc_1128450
0x1128441  xorps xmm0,xmm0
0x1128444  cvtsi2ss xmm0,rbx
0x1128449  jmp short 0x112846A                           ; -> loc_112846a
0x112844b  nop [rax+rax]

loc_1128450:  ; from 112843f
0x1128450  mov rcx,rbx
0x1128453  shr rcx,1
0x1128456  mov edx,ebx
0x1128458  and edx,1
0x112845b  or rdx,rcx
0x112845e  xorps xmm0,xmm0
0x1128461  cvtsi2ss xmm0,rdx
0x1128466  addss xmm0,xmm0

loc_112846a:  ; from 1128449
0x112846a  mov byte ptr [rbp+0x60],0
0x112846e  mov rcx,[rbp+0x198]
0x1128475  cmp qword ptr [rcx+r13+0x18],0x10
0x112847b  jb short 0x1128490                           ; -> loc_1128490
0x112847d  mov rdx,[rcx+r13]
0x1128481  jmp short 0x1128494                           ; -> loc_1128494
0x1128483  nop [rax+rax]

loc_1128490:  ; from 112847b
0x1128490  lea rdx,[rcx+r13]

loc_1128494:  ; from 1128481
0x1128494  mov r8d,eax
0x1128497  shr r8d,0x1F
0x112849b  add r8d,eax
0x112849e  sar r8d,1
0x11284a1  xorps xmm3,xmm3
0x11284a4  cvtsi2ss xmm3,r8d
0x11284a9  xorps xmm3,xmm10
0x11284ad  mulss xmm0,xmm7
```

- xmm0 = line index as float (with special negative handling) [V: 0x112843c-0x1128466]
- [rbp+0x60] = 0 byte flag [V: 0x112846a]
- Second SSO check for same string (redundant reload) [V: 0x112846e-0x1128490]
- r8d = eax/2 with sign correction (average rounding) [V: 0x1128494-0x112849e]
- xmm3 = (float)r8d, possibly negated via XOR with xmm10 [V: 0x11284a1-0x11284a9]
- xmm0 = lineY * xmm7 (y-scale) [V: 0x11284ad]

### Phase 3: 0x11284ad..0x1128558 — width callback arg setup, call, jump table
```
// rax = [rbp+0x220]  (builder/desc)
// r8 = [rax+0x28]  (some field)
// rax = [rcx+r13+0x10]  (string chars again)
// [rbp+0x38] = rdx  (string ptr)
// [rbp+0x40] = rax  (string chars)
// rax = [rsi]  (SharedPair)
// rax = [rax+0x20]  (another field)
// r9 = [0xF99FFA0]  (callback ptr)
// rcx = &[rbp+0x48]  (output width struct)
// [rsp+0x88] = rcx
// [rsp+0x70] = rdi; [rsp+0x68] = rdi
// [rsp+0x48] = r8
// rcx = [rbp+0x190]
// [rsp+0x28] = rcx
// [rsp+0x20] = xmm0  (lineY offset)
// [rsp+0x90]=0, [rsp+0x80]=0, [rsp+0x78]=0, [rsp+0x60]=0
// [rsp+0x58]=0, [rsp+0x50]=0xFFFFFFFF, [rsp+0x40]=0, [rsp+0x38]=0, [rsp+0x30]=0
// rcx = rsi; rdx = r12; r8 = r15
// call r9  (font width callback)
// eax = byte [rbp+0x60]  (glyph-run kind)
// if eax > 3: goto loop top (sub_11283d0)
// rax = jumpTable[eax]; rax += r14; jmp rax
```

```
0x11284b1  mov rax,[rbp+0x220]
0x11284b8  mov r8,[rax+0x28]
0x11284bc  mov rax,[rcx+r13+0x10]
0x11284c1  mov [rbp+0x38],rdx
0x11284c5  mov [rbp+0x40],rax
0x11284c9  mov rax,[rsi]
0x11284cc  mov rax,[rax+0x20]
0x11284d0  mov r9,[0xF99FFA0]                            ; [data_f99ffa0] = sub_eea6040
0x11284d7  lea rcx,[rbp+0x48]
0x11284db  mov [rsp+0x88],rcx
0x11284e3  mov [rsp+0x70],rdi
0x11284e8  mov [rsp+0x68],rdi
0x11284ed  mov [rsp+0x48],r8
0x11284f2  mov rcx,[rbp+0x190]
0x11284f9  mov [rsp+0x28],rcx
0x11284fe  movss [rsp+0x20],xmm0
0x1128504  mov byte ptr [rsp+0x90],0
0x112850c  mov dword ptr [rsp+0x80],0
0x1128517  mov dword ptr [rsp+0x78],0
0x112851f  mov dword ptr [rsp+0x60],0
0x1128527  mov byte ptr [rsp+0x58],0
0x112852c  mov dword ptr [rsp+0x50],0xFFFFFFFF
0x1128534  mov byte ptr [rsp+0x40],0
0x1128539  mov byte ptr [rsp+0x38],0
0x112853e  mov byte ptr [rsp+0x30],0
0x1128543  mov rcx,rsi
0x1128546  mov rdx,r12
0x1128549  mov r8,r15
0x112854c  call r9
0x112854f  nop
0x1128550  movzx eax,byte ptr [rbp+0x60]
0x1128554  cmp rax,3
0x1128558  ja 0x11283D0                                 ; -> sub_11283d0
0x112855e  movsxd rax,[r14+rax*4]
0x1128562  add rax,r14
0x1128565  jmp rax
```

- r8 = [rbp+0x220+0x28] (builder field) [V: 0x11284b1, 0x11284b8]
- String ptr/chars stored at [rbp+0x38]/[rbp+0x40] [V: 0x11284bc-0x11284c5]
- r9 = [0xF99FFA0] = font callback ptr [V: 0x11284d0]
- Stack args zeroed for width callback struct [V: 0x1128504-0x112853e]
- call r9 (font width callback) [V: 0x112854c]
- eax = glyph-run kind byte [rbp+0x60] [V: 0x1128550]
- Jump table: if kind > 3, exit loop; else jumpTable[kind] + r14 [V: 0x1128554-0x1128565]

### Phase 4: 0x112855e..0x11285ef — jump table targets: refcount dec, string release, loop inc
```
// Case targets at r14+kind*4:
// 1128567: r13 = [rbp+0x58]; if !r13 goto loop top
//          lock dec [r13+8]; if != 0 goto loop top
//          rax = [r13]; rax = [rax]; rcx = r13; call [0xF99FFA0]  (release)
//          lock dec [r13+0xC]; if != 0 goto loop top
//          rax = [r13]; rax = [rax+8]; rcx = r13; call [0xF99FFA0]  (release v2)
//          jmp loop top
// 11285b0: rcx = [rbp+0x48]; if !rcx goto loop top
//          rdx = [rcx+8]; if !rdx goto loc_11285e2
//          lock dec [rdx+0xC]; if != 0 goto loc_11285e2
//          rax = [rdx]; rax = [rax+8]; r13 = rcx; rcx = rdx; call [0xF99FFA0]  (release)
// loc_11285e2:
//          edx = 0x20  (sizeof(std::string))
//          call 0xE935700  (free/string destructor)
//          rbx++  (next line)
//          jmp 0x11283D3  (loop top)
```

```
0x1128567  mov r13,[rbp+0x58]
0x112856b  test r13,r13
0x112856e  je 0x11283D0                                 ; -> sub_11283d0
0x1128574  lock dec dword ptr [r13+8]
0x1128579  jne 0x11283D0                               ; -> sub_11283d0
0x112857f  mov rax,[r13]
0x1128583  mov rax,[rax]
0x1128586  mov rcx,r13
0x1128589  call qword ptr [0xF99FFA0]                  ; [data_f99ffa0] = sub_eea6040
0x112858f  lock dec dword ptr [r13+0xC]
0x1128594  jne 0x11283D0                               ; -> sub_11283d0
0x112859a  mov rax,[r13]
0x112859e  mov rax,[rax+8]
0x11285a2  mov rcx,r13
0x11285a5  call qword ptr [0xF99FFA0]                  ; [data_f99ffa0] = sub_eea6040
0x11285ab  jmp 0x11283D0                               ; -> sub_11283d0
0x11285b0  mov rcx,[rbp+0x48]
0x11285b4  test rcx,rcx
0x11285b7  je 0x11283D0                                ; -> sub_11283d0
0x11285bd  mov rdx,[rcx+8]
0x11285c1  test rdx,rdx
0x11285c4  je short 0x11285E2                          ; -> loc_11285e2
0x11285c6  lock dec dword ptr [rdx+0xC]
0x11285ca  jne short 0x11285E2                         ; -> loc_11285e2
0x11285cc  mov rax,[rdx]
0x11285cf  mov rax,[rax+8]
0x11285d3  mov r13,rcx
0x11285d6  mov rcx,rdx
0x11285d9  call qword ptr [0xF99FFA0]                  ; [data_f99ffa0] = sub_eea6040
0x11285df  mov rcx,r13

loc_11285e2:  ; from 11285c4, 11285ca
0x11285e2  mov edx,0x20
0x11285e7  call 0xE935700                              ; -> sub_e935700
0x11285ec  inc rbx
0x11285ef  jmp 0x11283D3                               ; -> sub_11283d3
```

- Jump target 1 (kind 1): refcount-decrement and release via [0xF99FFA0] twice [V: 0x1128567-0x11285ab]
- Jump target 2 (kind 2): release [rbp+0x48]-based refcounted object [V: 0x11285b0-0x11285df]
- Common cleanup: edx = 0x20 (string size), call 0xE935700 (destructor/free) [V: 0x11285e2, 0x11285e7]
- rbx++ (next line), loop back to 0x11283D3 [V: 0x11285ec, 0x11285ef]

---

## Range 4: 0x112888e..0x1128a40 — background quads via MeshFallback

### Phase 1: 0x112888e..0x11288fa — zero params block, first MeshFallback insert
```
// rdi = [rbx+0x60]  (nametag kind counter)
// [rbp+0x1D8] = 0  (variant tag byte)
// r12 = [rbx+0x20]  (shared material/mesh object)
// [rbp+0x218] = 0
// rcx = &[rbp+0x48]  (matrix output)
// r8d = 0x148  (param block size)
// edx = 0
// call 0xEEC6ED0  (memset(&params, 0, 0x148))
// [rsp+0x40] = r15
// rax = &[rbp+0x1C0]; [rsp+0x30] = rax
// rcx = rdi  (kind counter)
// rdx = &[r13+0x10]  (camera?)
// r8 = r12  (shared obj)
// r9 = &[rbp+0x48]  (matrix)
// call 0x4DEF480  (MeshFallback insert #1: border quad)
```

```
0x112888e  mov rdi,[rbx+0x60]
0x1128892  mov byte ptr [rbp+0x1D8],0
0x1128899  mov r12,[rbx+0x20]
0x112889d  mov byte ptr [rbp+0x218],0
0x11288a4  lea rcx,[rbp+0x48]
0x11288a8  mov r8d,0x148
0x11288ae  xor edx,edx
0x11288b0  call 0xEEC6ED0                                ; -> sub_eec6ed0
0x11288b5  nop
0x11288b6  mov [rsp+0x40],r15
0x11288bb  lea rax,[rbp+0x1C0]
0x11288c2  mov [rsp+0x30],rax
0x11288c7  mov rcx,rdi
0x11288ca  lea rdx,[r13+0x10]
0x11288ce  mov r8,r12
0x11288d1  lea r9,[rbp+0x48]
0x11288d5  call 0x4DEF480                                ; -> sub_4def480
0x11288da  nop
```

- rdi = [rbx+0x60] (kind counter) [V: 0x112888e]
- [rbp+0x1D8] = 0 (variant tag) [V: 0x1128892]
- r12 = [rbx+0x20] (shared material/mesh) [V: 0x1128899]
- memset(&params, 0, 0x148) via 0xEEC6ED0 [V: 0x11288a4-0x11288b0]
- [rbp+0x1C0] = param block address saved on stack [V: 0x11288bb-0x11288c2]
- rcx = kind, rdx = [r13+0x10], r8 = shared obj, r9 = matrix [V: 0x11288c7-0x11288d1]
- call 0x4DEF480 (MeshFallback insert, border quad) [V: 0x11288d5]

### Phase 2: 0x11288db..0x112896a — variant tag switch (jump table at 0xF0DF06C)
```
// eax = byte [rbp+0x1D8] (variant tag)
// if eax > 3: goto 0x1127F00 (shared state release)
// rax = jumpTable64[eax]; rax += 0xF0DF06C; jmp rax
// Case 0: [rbp+0x1D8]=0, r12=[rbx+0x20], [rbp+0x218]=0
//         memset(&params, 0, 0x148)
//         rcx=[rbp+0x340], rdx=&[r13+0x10], r8=r12, r9=&[rbp+0x48]
//         call 0x4DEF480 (MeshFallback insert #2: fill quad)
//         eax = byte [rbp+0x1D8]; if > 3 goto 0x1127F00
//         rax = jumpTable64[eax]; rax += 0xF0DF07C; jmp rax
```

```
0x11288db  movzx eax,byte ptr [rbp+0x1D8]
0x11288e2  cmp rax,3
0x11288e6  ja 0x1127F00                                 ; -> sub_1127f00
0x11288ec  lea rcx,[0xF0DF06C]                          ; [data_f0df06c]
0x11288f3  movsxd rax,[rcx+rax*4]
0x11288f7  add rax,rcx
0x11288fa  jmp rax
0x11288fc  mov byte ptr [rbp+0x1D8],0
0x1128903  mov r12,[rbx+0x20]
0x1128907  mov byte ptr [rbp+0x218],0
0x112890e  lea rdi,[rbp+0x48]
0x1128912  mov r8d,0x148
0x1128918  mov rcx,rdi
0x112891b  xor edx,edx
0x112891d  call 0xEEC6ED0                               ; -> sub_eec6ed0
0x1128922  nop
0x1128923  mov [rsp+0x40],r15
0x1128928  lea rax,[rbp+0x1C0]
0x112892f  mov [rsp+0x30],rax
0x1128934  mov rcx,[rbp+0x340]
0x112893b  lea rdx,[r13+0x10]
0x112893f  mov r8,r12
0x1128942  mov r9,rdi
0x1128945  call 0x4DEF480                               ; -> sub_4def480
0x112894a  nop
0x112894b  movzx eax,byte ptr [rbp+0x1D8]
0x1128952  cmp rax,3
0x1128956  ja 0x1127F00                                 ; -> sub_1127f00
0x112895c  lea rcx,[0xF0DF07C]                          ; [data_f0df07c]
0x1128963  movsxd rax,[rcx+rax*4]
0x1128967  add rax,rcx
0x112896a  jmp rax
```

- eax = variant tag [rbp+0x1D8] [V: 0x11288db]
- Bounds check: if tag > 3 goto shared-state cleanup [V: 0x11288e2, 0x11288e6]
- Jump table at [0xF0DF06C] (4-byte entries, 64-bit targets) [V: 0x11288ec-0x11288fa]
- Case fall-through: re-zero params, second MeshFallback insert (fill quad) [V: 0x11288fc-0x1128945]
- Second variant tag check and jump table at [0xF0DF07C] [V: 0x112894b-0x112896a]

### Phase 3: 0x112896c..0x11289c2 — variant destroy (#1/#2) and second insert cleanup
```
// r15 = [rbp+0x1D0]  (variant payload)
// if !r15 goto 0x1127F00
// lock dec [r15+8]; if != 0 goto 0x1127F00
// rax = [r15]; rax = [rax]; rcx = r15; call [0xF99FFA0]  (release variant)
// lock dec [r15+0xC]; if != 0 goto 0x1127F00
// rax = [r15]; rax = [rax+8]; rcx = r15; call [0xF99FFA0]  (release v2)
// jmp 0x1127F00
// (default case of variant tag 3):
// r15d = 0; rax = [rbp+0x58]; r12 = [rbp+0x68]
```

```
0x112896c  mov r15,[rbp+0x1D0]
0x1128973  test r15,r15
0x1128976  je 0x1127F00                                 ; -> sub_1127f00
0x112897c  lock dec dword ptr [r15+8]
0x1128981  jne 0x1127F00                              ; -> sub_1127f00
0x1128987  mov rax,[r15]
0x112898a  mov rax,[rax]
0x112898d  mov rcx,r15
0x1128990  call qword ptr [0xF99FFA0]                  ; [data_f99ffa0] = sub_eea6040
0x1128996  lock dec dword ptr [r15+0xC]
0x112899b  jne 0x1127F00                              ; -> sub_1127f00
0x11289a1  mov rax,[r15]
0x11289a4  mov rax,[rax+8]
0x11289a8  mov rcx,r15
0x11289ab  call qword ptr [0xF99FFA0]                  ; [data_f99ffa0] = sub_eea6040
0x11289b1  jmp 0x1127F00                              ; -> sub_1127f00
0x11289b6  lea rcx,[rbp+0x1C0]
0x11289bd  call 0x4DFB470                              ; -> sub_4dfb470
0x11289c2  jmp 0x1127F00                              ; -> sub_1127f00
```

- r15 = variant payload [rbp+0x1D0] [V: 0x112896c]
- Refcount release: lock dec [r15+8], then call [0xF99FFA0] (sub_eea6040) [V: 0x112897c-0x1128990]
- Secondary release: lock dec [r15+0xC], call [0xF99FFA0] with [r15+8] [V: 0x1128996-0x11289ab]
- Variant tag 3 default: call 0x4DFB470 on [rbp+0x1C0] (param block) [V: 0x11289b6, 0x11289bd]
- All paths jump to 0x1127F00 (shared state release tail) [V: 0x11289b1, 0x11289c2]

### Phase 4: 0x11289c7..0x1128a31 — shared refcount release, null trap, fatal
```
// (tag 3 default continued):
// test rax,rax; if !rax || [rax]==0: goto loc_11289e7
//   mov dword ptr [0],0xDEADC0DE  (NULL deref trap / intentional crash)
// loc_11289e7:
// test r15,r15; if !r15 goto 0x11277BC
// lock dec [r15+8]; if != 0 goto 0x11277BC
// rax=[r15]; rax=[rax]; rcx=r15; call [0xF99FFA0]  (release)
// lock dec [r15+0xC]; if != 0 goto 0x11277BC
// rax=[r15]; rax=[rax+8]; rcx=r15; call [0xF99FFA0]  (release v2)
// jmp 0x11277BC
// 1128a2a: call 0x1166E0  (fatal/unreachable, mode > 1)
// nop; int3; nop
```

```
0x11289c7  xor r15d,r15d
0x11289ca  mov rax,[rbp+0x58]
0x11289ce  mov r12,[rbp+0x68]
0x11289d2  test rax,rax
0x11289d5  je short 0x11289E7                          ; -> loc_11289e7
0x11289d7  cmp byte ptr [rax],0
0x11289da  jne short 0x11289E7                          ; -> loc_11289e7
0x11289dc  mov dword ptr [0],0xDEADC0DE

loc_11289e7:  ; from 11289d5, 11289da
0x11289e7  test r15,r15
0x11289ea  je 0x11277BC                                 ; -> sub_11277bc
0x11289f0  lock dec dword ptr [r15+8]
0x11289f5  jne 0x11277BC                              ; -> sub_11277bc
0x11289fb  mov rax,[r15]
0x11289fe  mov rax,[rax]
0x1128a01  mov rcx,r15
0x1128a04  call qword ptr [0xF99FFA0]                  ; [data_f99ffa0] = sub_eea6040
0x1128a0a  lock dec dword ptr [r15+0xC]
0x1128a0f  jne 0x11277BC                              ; -> sub_11277bc
0x1128a15  mov rax,[r15]
0x1128a18  mov rax,[rax+8]
0x1128a1c  mov rcx,r15
0x1128a1f  call qword ptr [0xF99FFA0]                  ; [data_f99ffa0] = sub_eea6040
0x1128a25  jmp 0x11277BC                              ; -> sub_11277bc
0x1128a2a  call 0x1166E0                               ; -> sub_1166e0
0x1128a2f  nop
0x1128a30  int3
```

- tag-3 path: rax = [rbp+0x58], r12 = [rbp+0x68]; null-check rax, trap 0xDEADC0DE if [rax]==0 [V: 0x11289c7-0x11289dc]
- Shared state release at 0x11277BC: refcount dec + double release via [0xF99FFA0] [V: 0x11289e7-0x1128a25]
- Fatal path: call 0x1166e0 (unreachable/bad mode) [V: 0x1128a2a]
- 0x1128a30: int3 (trap) [V: 0x1128a30]

---

## Struct fields touched (across all four ranges)

| Field | Offset | Size | R/W | Meaning | Tag |
|-------|--------|------|-----|---------|-----|
| CameraRec.x | [r14] | 4 | R | camera x | [V] |
| CameraRec.yz | [r14+4] | 8 | R | camera y,z packed | [V] |
| NametagObj.x | [rbx+0x50] | 4 | R | nametag world x | [V] |
| NametagObj.yz | [rbx+0x54] | 8 | R | nametag world y,z | [V] |
| NametagObj.scale | [rbx+0x5C] | 4 | R | tag scale | [V] |
| NametagObj.kind | [rbx+0x60] | 4/8 | R | kind counter / refcount | [V] |
| NametagObj.mode | [rbx+0x70] | 1 | R | mode byte (0,1,2/3=fatal) | [V] |
| NametagObj.sinCos | [rbx+0x78] | 4 | R | stored sin override | [V] |
| NametagObj.sinCos2 | [rbx+0x7C] | 4 | R | stored cos override | [V] |
| NametagObj.modeByte2 | [rbx+0x88] | 1 | R | mode override flag | [V] |
| NametagObj.storedSC | [rbx+0x80] | 4 | R | stored sin/cos | [V] |
| NametagObj.material | [rbx+0x20] | 8 | R | shared material/mesh obj | [V] |
| Local mat4 row0 | [rbp+0x1E0] | 4 | W | mat4[0][0] | [V] |
| Local mat4 row0 | [rbp+0x1E4] | 4 | W | mat4[0][1] | [V] |
| Local mat4 row0 | [rbp+0x1E8] | 4 | W | mat4[0][2] | [V] |
| Local mat4 row1 | [rbp+0x1F0] | 8 | W | mat4[1][0],[1][1] | [V] |
| Local mat4 row1 | [rbp+0x1F8] | 4 | W | mat4[1][2] | [V] |
| Local mat4 row1 | [rbp+0x1FC] | 4 | W | mat4[1][3] = 0 | [V] |
| Local mat4 row2 | [rbp+0x200] | 4 | W | mat4[2][0] | [V] |
| Local mat4 row2 | [rbp+0x204] | 4 | W | mat4[2][1] | [V] |
| Local mat4 row2 | [rbp+0x208] | 4 | W | mat4[2][2] | [V] |
| Local mat4 row2 | [rbp+0x20C] | 16 | W | mat4[2][3] = 0 | [V] |
| Local mat4 row3 | [rbp+0x21C] | 4 | W | mat4[3][3] = 1.0f | [V] |
| Output matrix | [rbp+0x48] | 64 | W | result of mat4 multiply | [V] |
| Line count flag | [rbp+0x60] | 1 | W | glyph-run kind byte | [V] |
| String ptr | [rbp+0x28] | 8 | W | current line string pointer | [V] |
| String size | [rbp+0x30] | 8 | W | current line string size | [V] |
| String ptr 2 | [rbp+0x38] | 8 | W | string ptr (callback args) | [V] |
| String chars | [rbp+0x40] | 8 | W | string chars (callback args) | [V] |
| Variant tag | [rbp+0x1D8] | 1 | R/W | MeshFallback variant tag | [V] |
| Variant flag | [rbp+0x218] | 1 | W | variant flag | [V] |
| Variant payload | [rbp+0x1D0] | 8 | R | variant payload pointer | [V] |
| Param block | [rbp+0x1C0] | 0x148 | W | MeshFallback params (memset) | [V] |
| Vector<string>.begin | [rbp+0x198] | 8 | R | lines vector begin | [V] |
| Vector<string>.end | [rbp+0x1A0] | 8 | R | lines vector end | [V] |
| LineY scalar | [rbp+0x190] | 8 | R | per-line Y offset | [V] |

## Callees

| RVA | What it is | Calls in range | Tag |
|-----|-----------|----------------|-----|
| 0xAA6580 | mat4 multiply (out=rcx, A=rdx, B=r8) | 1 (0x1127d23) | [V] |
| 0xEEC6ED0 | memset | 2 (0x11288b0, 0x112891d) | [V] |
| 0x4DEF480 | MeshFallback insert | 2 (0x11288d5, 0x1128945) | [V] |
| 0x4DFB470 | param block cleanup | 1 (0x11289bd) | [V] |
| 0xE935700 | string destructor/free | 1 (0x11285e7) | [V] |
| 0x1166E0 | fatal/unreachable (bad mode) | 1 (0x1128a2a) | [V] |
| 0xF9A8E18 | import: sinf | 1 (0x1127a4e via rdi) | [V] |
| 0xF9A8F48 | import: cosf | 2 (0x1127a67, 0x1127a70 via rdi) | [V] |
| 0xF99FFA0 | import: sub_eea6040 (refcount release/font callback) | many via [0xF99FFA0] | [V] |
| 0x1127F00 | shared-state release tail (fall-through target) | multiple jump targets | [I] |
| 0x11277BC | shared-state release (alt tail) | multiple jump targets | [I] |
| 0x11283D0 | loop exit / sub_11283d0 | jump table default | [I] |
| 0x11283D3 | loop top | loop back-edge | [I] |

## OPEN questions

1. **Constants**: [0xF07FAF0], [0xF09BDDC], [0xEFD3400], [0xF0CD500], [0xF0CD504], [0xEF3F018], [0xEF3F050], [0xEEE7C00] — exact float values not determined from disassembly alone. [0xEFD3400] used as inverse-length numerator; [0xEEE7C00] used as sin/cos scale. Need data-section dump to resolve.
2. **Font width callback**: 0xF99FFA0 (sub_eea6040) is used both as the per-line width callback (0x1128435, 0x112854c) and as refcount release (0x1128589, 0x11285a5, etc.). Same address, different contexts — need to confirm if it's one overloaded function or two different imports at the same slot.
3. **Quaternion semantics**: xmm14/xmm9/xmm6/xmm7 pairs form quaternion-like rotation terms but exact component ordering (x,y,z,w) not determined.
4. **MeshFallback param block**: [rbp+0x1C0] size 0x148, fields not mapped beyond the memset and the 0x4DEF480 call signature.
5. **Variant tag jump tables**: [0xF0DF06C] and [0xF0DF07C] are 4-entry jump tables; target meanings (tag 0/1/2/3) not determined.
6. **0x1127b06 onwards**: `mulss xmm11,[0xF0922D0]` (scale) and `mulss xmm12,[0xEF40D2C]` (line stack height) fall just outside range 1 end bound — belong to the matrix-push phase (item 4 in context), not decoded here.
