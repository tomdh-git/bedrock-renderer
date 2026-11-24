# sub 0xbc7b3a0 — VV frame-graph builder (bgfx)

Source exe: Minecraft.Windows.exe 1.26.62.01; all RVAs below are image-relative.
Function: sub_bc7b3a0 [0xbc7b3a0, 0xbc7b7c5), size 0x425, depth 1, milestone D0, region bgfx,
name "VV frame-graph builder". Registered in docs/data/native_functions.tsv (size 0x425,
callees_outside_set: 0x78ed0). Lifted source: src/client/features/render/native/bgfx/sub_bc7b3a0.{h,cpp}
(first line `// LIFT 0xbc7b3a0 size 0x425 1.26.62.01 sub_bc7b3a0`).

## Reversed source (complete)

x64 Microsoft ABI, __cdecl-style MSVC x64: rcx = out float* (arg1; the original copies it to rsi,
rax = out on return), rdx = in const float* (arg2; copied to rdi). Reads in[+0,+4,+8,+0xC,+0x10,+0x18].
Writes out[0..8) via movlps (0xbc7b753) and out[8..0xC) via movss (0xbc7b756). Returns rax = rsi = out
(ret 0xbc7b7be). Saves xmm6-xmm15, rbx, rdi, rsi; `sub rsp,0x110`. No class members or globals are
touched — args and stack only [V]. Six branches `jae 0xBC7B7BF` (0xbc7b455, 0xbc7b47b, 0xbc7b52d,
0xbc7b553, 0xbc7b608, 0xbc7b631) target the trap block `0xbc7b7bf  call 0x78ED0` / `0xbc7b7c4  int3`
[V]. All data reads are rip-relative to the cited data RVAs; table rows are 0x0c bytes:
{+0x00 float f0, +0x04 uint32 pad04 (bit pattern reused as a float), +0x08 float f8} [V].

`0xbc7b3a0..0xbc7b402`: prologue — push rsi/rdi/rbx; sub rsp,0x110; movaps-save xmm15..xmm6 at
[rsp+0x100]..[rsp+0x70]; mov rdi,rdx (in); mov rsi,rcx (out).
`0xbc7b405..0xbc7b411`: v0 = in[0] / [0xEFD32AC] * [0xEFC6CF8] (movss xmm6,[rdx]; divss xmm6,[0xEFD32AC];
mulss xmm6,[0xEFC6CF8]).
`0xbc7b419..0xbc7b44c`: a0 = call 0xEEC75A0(v0) -> xmm7 = a0; K = [0xEEE6700] (xmm15); b0 = call 0xEEC73F0(v0).
`0xbc7b424  movss xmm15,[0xEEE6700]`
`0xbc7b41c  call 0xEEC75A0`
`0xbc7b44c  call 0xEEC73F0`
`0xbc7b42d..0xbc7b446`: idxA0 = rnd(a0) = (a0 >= 0 ? trunc(a0) : trunc(a0 - K)):
cvttss2si rax,xmm0(xmm0 = a0 - K) ; cvttss2si rcx,xmm7(rcx = trunc(a0)) ; mov rbx,rcx ; sar rbx,0x3F ;
and rbx,rax ; or rbx,rcx.
`0xbc7b451..0xbc7b455`: cmp rbx,0x65 ; jae 0xBC7B7BF (trap).
`0xbc7b45b..0xbc7b47b`: idxB0 = rnd(b0) (same pattern on xmm0 = b0) ; cmp rax,0x65 ; jae 0xBC7B7BF (trap).
`0xbc7b481..0xbc7b4a3`: T0 = [0xF449730]; read T0[idxB0].f8 (xmm13), T0[idxB0] row lo {f0,pad} (xmm14),
T0[idxA0] row lo (xmm9), T0[idxA0].f8 (xmm12) (lea rcx,[rbx+rbx*2] = idxA0*3 ; lea rax,[rax+rax*2] = idxB0*3 ;
movss/movsd [rdx+rax*4(+8)] / [rdx+rcx*4(+8)]).
`0xbc7b4aa..0xbc7b4d4`: t1 = (max([0xEFC2540], in[4]) + [0xF0C8C88]) / [0xF1527C8] * [0xEFC6CF8]
(movss xmm0,[rdi+4] R in+4 ; maxss xmm1,xmm0 ; addss xmm1,[0xF0C8C88] ; divss xmm1,[0xF1527C8] ;
movss xmm11,[0xEFC6CF8] ; mulss xmm1,xmm11).
`0xbc7b4d9..0xbc7b4f3`: blended1 = ([0xEF40D44] < in[4]) ? [0xEFC6CF8] : t1
(movss xmm8,[0xEF40D44] ; cmpltss xmm8,xmm0 ; andnps/andps/orps).
`0xbc7b4f7..0xbc7b524`: d1 = call 0xEEC75A0(blended1) (xmm10 = d1); e1 = call 0xEEC73F0(blended1).
`0xbc7b4fb  call 0xEEC75A0`
`0xbc7b524  call 0xEEC73F0`
`0xbc7b504..0xbc7b51d`: idxD1 = rnd(d1) (same pattern; xmm0 -= K first).
`0xbc7b529..0xbc7b52d`: cmp rbx,0x65 ; jae 0xBC7B7BF (trap).
`0xbc7b533..0xbc7b54c`: idxE1 = rnd(e1) (same pattern).
`0xbc7b54f..0xbc7b553`: cmp rax,0x65 ; jae 0xBC7B7BF (trap).
`0xbc7b559..0xbc7b564`: spill xmm7=a0 to [rsp+0x40], xmm14=T0[idxB0] row lo to [rsp+0x50], xmm9=T0[idxA0]
row lo to [rsp+0x60].
`0xbc7b56a..0xbc7b598`: T1 = [0xF44A0A8]; xmm15 = T1[idxE1].f8; spill T1[idxE1] row lo to [rsp+0x20],
T1[idxD1] row lo to [rsp+0x30]; xmm14 = T1[idxD1].f8.
`0xbc7b59f..0xbc7b5b9`: t2 = (max(0, in[8]) / [0xF10D440]) * [0xEFC6CF8]
(movss xmm0,[rdi+8] R in+8 ; xorps xmm1,xmm1 ; maxss xmm1,xmm0 ; movss xmm9,[0xF10D440] ; divss xmm1,xmm9 ;
mulss xmm1,xmm11 — xmm11 still holds [0xEFC6CF8]).
`0xbc7b5be..0xbc7b5cf`: blended2 = ([0xF10D440] < in[8]) ? [0xEFC6CF8] : t2 (cmpltss xmm9,xmm0 ; blend).
`0xbc7b5d3..0xbc7b5ff`: d2 = call 0xEEC75A0(blended2) (xmm11 = d2); e2 = call 0xEEC73F0(blended2).
`0xbc7b5d7  call 0xEEC75A0`
`0xbc7b5ff  call 0xEEC73F0`
`0xbc7b5e0..0xbc7b5f8`: idxD2 = rnd(d2) (xmm0 -= K where xmm7 = K).
`0xbc7b604..0xbc7b608`: cmp rbx,0x65 ; jae 0xBC7B7BF (trap).
`0xbc7b60e..0xbc7b62a`: idxE2 = rnd(e2) (xmm0 -= [0xEEE6700]).
`0xbc7b62d..0xbc7b631`: cmp rdx,0x65 ; jae 0xBC7B7BF (trap).
`0xbc7b637..0xbc7b6d9`: z term: diff1 = blended1 - d1 (subss xmm8,xmm10); s1a = c8 - diff1
(subss xmm1,xmm8, xmm1 = [0xEEC8060]); w1 = T1[idxD1].f8*s1a + T1[idxE1].f8*diff1 (mulss xmm15,xmm8 ;
mulss xmm14,xmm1 ; addss xmm14,xmm15); diff2 = blended2 - d2 (subss xmm9,xmm11); s2a = c8 - diff2
(subss xmm0,xmm9); w2 = T2[idxD2].f8*s2a + T2[idxE2].f8*diff2 (mulss xmm3,xmm9 ; mulss xmm4,xmm0 ;
addss xmm4,xmm3); z0 = T0[idxA0].f8*(c8 - (v0 - a0)) + T0[idxB0].f8*(v0 - a0) where
v0 - a0 = subss xmm6,[rsp+0x40] and c8 - (v0 - a0) = subss xmm2,xmm6 (mulss xmm13,xmm6 ;
mulss xmm12,xmm2 ; addss xmm12,xmm13); z = z0 + [0xF246F60] + w1 + w2 + (in[0xC] / max([0xEFD3410],
in[0x18]) - in[0xC]) (movss xmm3,[rdi+0xC] R in+0xC ; movss xmm5,[0xEFD3410] ; maxss xmm5,[rdi+0x18] R in+0x18 ;
divss xmm7,xmm5 ; subss xmm7,xmm3 ; addss xmm12,[0xF246F60] ; addss xmm12,xmm14 ; addss xmm12,xmm4 ;
addss xmm12,xmm7).
`0xbc7b6de..0xbc7b750`: xy vector: row0 = s0a*rowLo(T0[idxA0]) + s0b*rowLo(T0[idxB0]) with
s0a = c8 - (v0 - a0), s0b = v0 - a0 (row lo = {f0, pad-as-float, 0, 0} from the spilled movsd rows);
row1 = s1a*rowLo(T1[idxD1]) + s1b*rowLo(T1[idxE1]); row2 = s2a*rowLo(T2[idxD2]) + s2b*rowLo(T2[idxE2]);
outVec = ((row0 + [0xF449700]) + row1 + row2) + (in[0xC]/max([0xF0A9660], {in[0x10],in[0x14]}) - in[0xC])
lane-wise, where the in-part vector is {in[0xC]/max(C11[0],in[0x10]) - in[0xC], ...} with
in10v = {in[0x10], in[0x14], 0, 0} from movsd [rdi+0x10] R in+0x10 (movsd xmm4,[rdi+0x10] ;
movaps xmm5,[0xF0A9660] ; maxps xmm5,xmm4 ; shufps xmm3,xmm3,0 ; divps xmm4,xmm5 ; subps xmm4,xmm3).
`0xbc7b743..0xbc7b750`: addps xmm2,[0xF449700] ; addps xmm2,xmm1 ; addps xmm2,xmm0 ; addps xmm2,xmm4.
`0xbc7b753..0xbc7b7be`: movlps [rsi],xmm2 (W out[0..7]) ; movss [rsi+8],xmm12 = z (W out[8..0xC]) ;
mov rax,rsi ; ret (rax = out).
`0xbc7b7bf..0xbc7b7c4`: trap block: call 0x78ED0 (noreturn crt: sub rsp,0x28 / call qword ptr [0xF9A8CF0] /
int3) then int3.

Every `call` above is quoted verbatim at its address; the full verbatim list is in the .cpp.

## Struct fields touched
None (no game objects). Const data-table row reads through `TableRow` (header): f0 +0x00 R (float,
consumed), pad04 +0x04 R (bit pattern reused as float, high lane of the movsd multiply), f8 +0x08 R
(float, consumed). Table RVAs 0xF449730 / 0xF44A0A8 / 0xF44A564, stride 0x0c, 3 rows per index [V].

## Callees
| RVA | Call sites | Classification |
| --- | --- | --- |
| 0xEEC75A0 | `0xbc7b41c  call 0xEEC75A0`, `0xbc7b4fb  call 0xEEC75A0`, `0xbc7b5d7  call 0xEEC75A0` | lift — IAT thunk `jmp qword ptr [0xF9A8E60]`, signature `float (float)` (float in xmm0, float out in xmm0) [V]; class lift in docs/data/native_boundary.tsv line 514 and docs/data/native_functions.tsv line 1638; called as native::sub_eec75a0 (forward-declared in sub_bc7b3a0.h) |
| 0xEEC73F0 | `0xbc7b44c  call 0xEEC73F0`, `0xbc7b524  call 0xEEC73F0`, `0xbc7b5ff  call 0xEEC73F0` | lift — IAT thunk `jmp qword ptr [0xF9A8E08]`, signature `float (float)` [V]; class lift in docs/data/native_boundary.tsv line 513 and docs/data/native_functions.tsv line 1637; called as native::sub_eec73f0 (forward-declared in sub_bc7b3a0.h) |
| 0x78ed0 | `0xbc7b7bf  call 0x78ED0` | boundary crt (docs/data/native_boundary.tsv line 11) [V]; noreturn: `sub rsp,0x28 / call qword ptr [0xF9A8CF0] / int3`; entered only from the trap block; hard rule 69 — the pointer is read from slot 0xF9A8CF0 at call time, exactly as the thunk does; the `int3` at 0xbc7b7c4 runs only if the thunk returns |

## All calls quoted verbatim
`0xbc7b41c  call 0xEEC75A0`
`0xbc7b44c  call 0xEEC73F0`
`0xbc7b4fb  call 0xEEC75A0`
`0xbc7b524  call 0xEEC73F0`
`0xbc7b5d7  call 0xEEC75A0`
`0xbc7b5ff  call 0xEEC73F0`
`0xbc7b7bf  call 0x78ED0`

## Signature
float* sub_bc7b3a0(float* out, const float* in) — rcx=out (kept in rsi), rdx=in (kept in rdi),
rax=out on return [V].

## Asserts
static_assert(offsetof(TableRow, f0) == 0x00 / pad04 == 0x04 / f8 == 0x08 / sizeof == 0x0c)
and static_assert(sizeof(std::uintptr_t) == 8) and static_assert(sizeof(float) == 4) in the header
and source [V].

## OPEN questions
none
