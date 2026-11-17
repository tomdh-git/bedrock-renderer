## NEXT
DONE

# U-Tl4 — texload tail slice 0x58a1fd0..0x58a23ce (chunk 4 of 4; texload function at 0x58a1310)

Coverage claim [V]: docs/progress/_part_Tl4.txt lists 224 instructions of this slice; every one is quoted verbatim below (two spaces after the address, copied from the input data), assigned to exactly one phase, and none is skipped or summarized. Non-consecutive RVAs are simply absent from the input listing and are not covered by this unit. Every quoted `0xRVA  instr` line was checked against Minecraft.Windows.exe 1.26.62.01 with tools/sigs/verify_oc.py.

Frame [I]: rbp-based frame; locals/spill slots from [rbp-0x20] to [rbp+0x1F0]; rbx holds the vertex/row pointer ([rbx+0x6C], [rbx+0x7C]); xmm8 is reused as a broadcast scale vector.

## Phase 1: 0x58a1fd0..0x58a2054 — vector setup for a 4x4 transform (35 instructions)

Rearranges vector components (movlhps/shufps/unpcklps/movq/unpckhpd) across xmm0..xmm10, adds xmm5 into xmm0 with a scalar addss into xmm1, multiplies xmm4 by the constant vector at [0xEFD3400], then stores result rows to [rbp+0x80] (xmm7) and [rbp+0x90] (xmm6).

0x58a1fd0  movlhps xmm5,xmm4
0x58a1fd3  shufps xmm5,xmm5,0x64
0x58a1fd7  unpcklps xmm0,xmm7
0x58a1fda  movq xmm10,xmm9
0x58a1fdf  shufps xmm9,xmm7,0xD4
0x58a1fe4  shufps xmm0,xmm9,0x84
0x58a1fe9  shufps xmm10,xmm8,0xE2
0x58a1fee  shufps xmm0,xmm0,0x24
0x58a1ff2  addps xmm0,xmm5
0x58a1ff5  addss xmm1,xmm6
0x58a1ff9  movaps xmm5,xmm0
0x58a1ffc  unpckhpd xmm5,xmm0
0x58a2000  unpcklps xmm5,xmm4
0x58a2003  subps xmm5,xmm10
0x58a2007  movaps xmm6,xmm2
0x58a200a  shufps xmm6,xmm5,0xD4
0x58a200e  movaps xmm7,xmm0
0x58a2011  shufps xmm7,xmm5,0xD6
0x58a2015  shufps xmm7,xmm5,0x52
0x58a2019  movaps xmm4,xmm5
0x58a201c  shufps xmm4,xmm5,4
0x58a2020  shufps xmm3,xmm6,0x24
0x58a2024  mulps xmm7,xmm8
0x58a2028  movlhps xmm2,xmm7
0x58a202b  mulps xmm4,[0xEFD3400]
0x58a2032  movaps xmm5,xmm0
0x58a2035  shufps xmm5,xmm4,0x23
0x58a2039  movaps xmm6,xmm4
0x58a203c  addps xmm4,xmm7
0x58a203f  shufps xmm7,xmm2,0x80
0x58a2043  addps xmm7,xmm3
0x58a2046  movaps [rbp+0x80],xmm7
0x58a204d  shufps xmm6,xmm5,0x8A
0x58a2051  addps xmm6,xmm0
0x58a2054  movaps [rbp+0x90],xmm6

## Phase 2: 0x58a205b..0x58a20b2 — third result row, constant load, and first 0xAA6580 call (17 instructions)

Completes the third row (mulss by xmm11, unpcklps/shufps/addps) and stores it to [rbp+0xA0], loads a constant vector from [0xF0922E0] into [rbp+0xB0], lea's the call pointers (rcx=rbp+0xC0 dest, rdx=rbp+0x80 src, r8=rbp+0x110 dest), calls 0xAA6580, then reloads the source rows [rbp+0xC0..0xF0] into xmm0..xmm3.

0x58a205b  movaps xmm0,xmm1
0x58a205e  mulss xmm0,xmm11
0x58a2063  unpcklps xmm0,xmm1
0x58a2066  shufps xmm0,xmm0,0x10
0x58a206a  addps xmm0,xmm4
0x58a206d  movaps [rbp+0xA0],xmm0
0x58a2074  movaps xmm0,[0xF0922E0]
0x58a207b  movaps [rbp+0xB0],xmm0
0x58a2082  lea rcx,[rbp+0xC0]
0x58a2089  lea rdx,[rbp+0x80]
0x58a2090  lea r8,[rbp+0x110]
0x58a2097  call 0xAA6580
0x58a209c  nop
0x58a209d  movaps xmm0,[rbp+0xC0]
0x58a20a4  movaps xmm1,[rbp+0xD0]
0x58a20ab  movaps xmm2,[rbp+0xE0]
0x58a20b2  movaps xmm3,[rbp+0xF0]

## Phase 3: 0x58a20b9..0x58a2155 — call output store, 1.0f initializers, and the [rbp+0x70]/[rbp+0x78] weighted row (32 instructions)

Stores the 0xAA6580 output rows to [rbp+0x110..0x140], writes float 1.0 (0x3F800000) to [rbp+0x80] and [rbp+0x94], broadcasts xmm8 to [rbp+0x84] and [rbp+0x98] (rax=rbp+0x84), then builds a row from [rbp+0x70]*xmm8 plus [rbp+0x78]*[0xEEC8060] plus constant [0xEFD32F0], merges it with [0xF0A4080] via movlhps, stores [rbp+0xA8] and the low quad of xmm1 to [rbp+0xB8].

0x58a20b9  movaps [rbp+0x110],xmm0
0x58a20c0  movaps [rbp+0x120],xmm1
0x58a20c7  movaps [rbp+0x130],xmm2
0x58a20ce  movaps [rbp+0x140],xmm3
0x58a20d5  mov dword ptr [rbp+0x80],0x3F800000
0x58a20df  lea rax,[rbp+0x84]
0x58a20e6  movups [rax],xmm8
0x58a20ea  mov dword ptr [rbp+0x94],0x3F800000
0x58a20f4  movups [rax+0x14],xmm8
0x58a20f9  movsd xmm0,[rbp+0x70]
0x58a20fe  movaps xmm1,xmm0
0x58a2101  mulps xmm1,xmm8
0x58a2105  movaps xmm2,xmm1
0x58a2108  shufps xmm2,xmm1,0xE1
0x58a210c  addps xmm2,xmm0
0x58a210f  movss xmm0,[rbp+0x78]
0x58a2114  shufps xmm0,xmm0,0
0x58a2118  movss xmm4,[0xEEC8060]
0x58a2120  mulps xmm0,xmm4
0x58a2123  movaps xmm3,xmm1
0x58a2126  shufps xmm3,xmm1,0x55
0x58a212a  unpcklps xmm1,xmm1
0x58a212d  addps xmm1,xmm3
0x58a2130  addps xmm1,xmm0
0x58a2133  addps xmm1,[0xEFD32F0]
0x58a213a  shufps xmm0,xmm0,0x55
0x58a213e  addps xmm0,xmm2
0x58a2141  movaps xmm2,[0xF0A4080]
0x58a2148  movlhps xmm2,xmm0
0x58a214b  addps xmm2,xmm4
0x58a214e  movups [rbp+0xA8],xmm2
0x58a2155  movlps [rbp+0xB8],xmm1

## Phase 4: 0x58a215c..0x58a2218 — second 0xAA6580 call plus cvtsi2ss/minps/maxps clamping chain (37 instructions)

Repeats the 0xAA6580 call with the same pointers (rcx=rbp+0xC0, rdx=rbp+0x80, r8=rbp+0x110), then extracts element pairs ([rbp+0xC0]/[rbp+0xC8] -> xmm5/xmm6, [rbp+0xF8]/[rbp+0xD8]/[rbp+0xE8] -> xmm7/xmm4/xmm1), converts the dword locals [rbp-0x1C] and [rbp-0x20] to scalars with cvtsi2ss, reloads rows [rbp+0xD0..0xF0], scales xmm3 by broadcast xmm14, and applies minps then maxps clamping against running sums.

0x58a215c  lea rcx,[rbp+0xC0]
0x58a2163  lea rdx,[rbp+0x80]
0x58a216a  lea r8,[rbp+0x110]
0x58a2171  call 0xAA6580
0x58a2176  nop
0x58a2177  movsd xmm5,[rbp+0xC0]
0x58a217f  movsd [rbp+0x110],xmm5
0x58a2187  movss xmm6,[rbp+0xC8]
0x58a218f  movss [rbp+0x118],xmm6
0x58a2197  movss xmm7,[rbp+0xF8]
0x58a219f  movss xmm4,[rbp+0xD8]
0x58a21a7  movss xmm1,[rbp+0xE8]
0x58a21af  xorps xmm0,xmm0
0x58a21b2  cvtsi2ss xmm0,dword ptr [rbp-0x1C]
0x58a21b7  movups xmm3,[rbp+0xD0]
0x58a21be  cvtsi2ss xmm9,dword ptr [rbp-0x20]
0x58a21c4  movups xmm2,[rbp+0xE0]
0x58a21cb  movups xmm10,[rbp+0xF0]
0x58a21d3  movlhps xmm6,xmm5
0x58a21d6  shufps xmm5,xmm6,0x84
0x58a21da  shufps xmm9,xmm9,0
0x58a21df  mulps xmm9,xmm5
0x58a21e3  xorps xmm5,xmm5
0x58a21e6  minps xmm5,xmm9
0x58a21ea  movlhps xmm7,xmm10
0x58a21ee  shufps xmm10,xmm7,0x84
0x58a21f3  addps xmm5,xmm10
0x58a21f7  xorps xmm6,xmm6
0x58a21fa  maxps xmm6,xmm9
0x58a21fe  addps xmm6,xmm10
0x58a2202  shufps xmm14,xmm14,0
0x58a2207  movlhps xmm4,xmm3
0x58a220a  shufps xmm3,xmm4,0x84
0x58a220e  mulps xmm3,xmm14
0x58a2212  xorps xmm4,xmm4
0x58a2215  minps xmm4,xmm3
0x58a2218  addps xmm4,xmm5

## Phase 5: 0x58a221b..0x58a2286 — clamp finish and component-wise min/max clamp of the [rbx+0x6C] row (33 instructions)

Finishes the clamping chain (maxps/addps into xmm5/xmm1/xmm2), loads the vertex row at [rbx+0x6C], then performs component-wise min/max clamping against the two computed bounds using cmpltps/andps/andnps/orps and stores the clamped row back to [rbx+0x6C].

0x58a221b  xorps xmm5,xmm5
0x58a221e  maxps xmm5,xmm3
0x58a2221  addps xmm5,xmm6
0x58a2224  movlhps xmm1,xmm2
0x58a2227  shufps xmm2,xmm1,0x84
0x58a222b  shufps xmm0,xmm0,0
0x58a222f  mulps xmm0,xmm2
0x58a2232  xorps xmm1,xmm1
0x58a2235  minps xmm1,xmm0
0x58a2238  addps xmm1,xmm4
0x58a223b  xorps xmm2,xmm2
0x58a223e  maxps xmm2,xmm0
0x58a2241  addps xmm2,xmm5
0x58a2244  movups xmm0,[rbx+0x6C]
0x58a2248  movaps xmm3,xmm0
0x58a224b  cmpltps xmm3,xmm1
0x58a224f  movaps xmm4,xmm1
0x58a2252  cmpltps xmm4,xmm0
0x58a2256  shufps xmm4,xmm3,0x23
0x58a225a  shufps xmm3,xmm4,0x24
0x58a225e  andps xmm0,xmm3
0x58a2261  andnps xmm3,xmm1
0x58a2264  orps xmm3,xmm0
0x58a2267  movaps xmm0,xmm3
0x58a226a  cmpltps xmm0,xmm2
0x58a226e  movaps xmm4,xmm2
0x58a2271  cmpltps xmm4,xmm3
0x58a2275  shufps xmm4,xmm0,0x23
0x58a2279  shufps xmm0,xmm4,0x24
0x58a227d  andps xmm3,xmm0
0x58a2280  andnps xmm0,xmm2
0x58a2283  orps xmm0,xmm3
0x58a2286  movups [rbx+0x6C],xmm0

## Phase 6: 0x58a228a..0x58a22cc — [rbx+0x7C] clamp, 0x541A8A0 call, and descriptor reset (16 instructions)

Loads [rbx+0x7C] (8 B), clamps it with two maxps against bounds shuffled with 0xE9, and stores the low quad back to [rbx+0x7C]; then calls 0x541A8A0 (rcx=rsi, edx=0) and resets the descriptor at rsi+0x1CC (qword 0, dword at +8 = 0) and rsi+0x1D8 (qword = r15, dword at +8 = r14d).

0x58a228a  movsd xmm0,[rbx+0x7C]
0x58a228f  shufps xmm1,xmm1,0xE9
0x58a2293  maxps xmm0,xmm1
0x58a2296  shufps xmm2,xmm2,0xE9
0x58a229a  maxps xmm0,xmm2
0x58a229d  movlps [rbx+0x7C],xmm0
0x58a22a1  mov rcx,rsi
0x58a22a4  xor edx,edx
0x58a22a6  call 0x541A8A0
0x58a22ab  nop
0x58a22ac  lea rax,[rsi+0x1CC]
0x58a22b3  mov dword ptr [rax+8],0
0x58a22ba  mov qword ptr [rax],0
0x58a22c1  lea rax,[rsi+0x1D8]
0x58a22c8  mov [rax+8],r14d
0x58a22cc  mov [rax],r15

## Phase 7: 0x58a22cf..0x58a2317 — heap-block size validation (17 instructions)

Loads block size [rbp+0x60] and rejects < 0x10 (jb 0x58A15F9); loads heap base [rbp+0x48], requires index+1 < 0x1000 (else jb 0x58A15F4), derives size from [rcx-8] minus 8 and rejects < 0x20 (else jb 0x58A15EA). When every test passes control reaches jmp 0x58A23B4; a separate cold block moves 0x40 into ecx, calls 0x9BC830, and jumps to 0x58A1752.

0x58a22cf  mov rax,[rbp+0x60]
0x58a22d3  cmp rax,0x10
0x58a22d7  jb 0x58A15F9
0x58a22dd  mov rcx,[rbp+0x48]
0x58a22e1  lea rdx,[rax+1]
0x58a22e5  cmp rdx,0x1000
0x58a22ec  jb 0x58A15F4
0x58a22f2  mov r8,[rcx-8]
0x58a22f6  add rcx,0xFFFFFFFFFFFFFFF8
0x58a22fa  sub rcx,r8
0x58a22fd  cmp rcx,0x20
0x58a2301  jb 0x58A15EA
0x58a2307  jmp 0x58A23B4
0x58a230c  mov ecx,0x40
0x58a2311  call 0x9BC830
0x58a2316  nop
0x58a2317  jmp 0x58A1752

## Phase 8: 0x58a231c..0x58a2348 — global-state teardown (8 instructions)

Calls 0xE938CB0 with rcx = &0x129CC628; if that dword is still 0xFFFFFFFF it writes byte 0 to [0x129CC624], then calls 0xE938D70 with the same pointer and jumps to 0x58A1AA5.

0x58a231c  lea rcx,[0x129CC628]
0x58a2323  call 0xE938CB0
0x58a2328  cmp dword ptr [0x129CC628],0xFFFFFFFF
0x58a232f  jne 0x58A1AA5
0x58a2335  mov byte ptr [0x129CC624],0
0x58a233c  lea rcx,[0x129CC628]
0x58a2343  call 0xE938D70
0x58a2348  jmp 0x58A1AA5

## Phase 9: 0x58a234d..0x58a23ae — epilogue, xmm6..xmm15 restore and stack teardown (20 instructions)

Restores xmm6..xmm15 from [rbp+0x160..0x1F0], releases the frame with add rsp,0x288, pops rbx/rdi/rsi/r12/r13/r14/r15/rbp and returns.

0x58a234d  movaps xmm6,[rbp+0x160]
0x58a2354  movaps xmm7,[rbp+0x170]
0x58a235b  movaps xmm8,[rbp+0x180]
0x58a2363  movaps xmm9,[rbp+0x190]
0x58a236b  movaps xmm10,[rbp+0x1A0]
0x58a2373  movaps xmm11,[rbp+0x1B0]
0x58a237b  movaps xmm12,[rbp+0x1C0]
0x58a2383  movaps xmm13,[rbp+0x1D0]
0x58a238b  movaps xmm14,[rbp+0x1E0]
0x58a2393  movaps xmm15,[rbp+0x1F0]
0x58a239b  add rsp,0x288
0x58a23a2  pop rbx
0x58a23a3  pop rdi
0x58a23a4  pop rsi
0x58a23a5  pop r12
0x58a23a7  pop r13
0x58a23a9  pop r14
0x58a23ab  pop r15
0x58a23ad  pop rbp
0x58a23ae  ret

## Phase 10: 0x58a23af..0x58a23ce — cold tail block (9 instructions)

Calls 0x78ED0; the 0x58A23B4 target zeroes [rsp+0x20], clears ecx/edx/r8d/r9d, calls indirect through [0xF9A8C78], then int3 and xchg ax,ax padding.

0x58a23af  call 0x78ED0
0x58a23b4  mov qword ptr [rsp+0x20],0
0x58a23bd  xor ecx,ecx
0x58a23bf  xor edx,edx
0x58a23c1  xor r8d,r8d
0x58a23c4  xor r9d,r9d
0x58a23c7  call qword ptr [0xF9A8C78]
0x58a23cd  int3
0x58a23ce  xchg ax,ax

## [reg+off] field access table — every load/store with a [reg+off] or absolute address in the 224 listed instructions

One row per distinct offset; all sites of that offset are listed under it. Size comes from the instruction (movups/movaps 16 B, movsd 8 B, movss/mov dword 4 B, mov qword 8 B, movlps 8 B, mov byte 1 B). lea instructions compute addresses but do not load or store, so lea-only sites are not listed here. add rsp,0x288 adjusts the stack pointer but performs no field access. No strings appear in this slice; meaning is "-" unless an instruction immediate shows it.

| offset | size | direction | verbatim `0xRVA  instr` sites | meaning |
|---|---|---|---|---|
| 0xEFD3400 | 16 | R | `0x58a202b  mulps xmm4,[0xEFD3400]` | - |
| rbp+0x80 | 16 / 4 | W | `0x58a2046  movaps [rbp+0x80],xmm7`<br>`0x58a20d5  mov dword ptr [rbp+0x80],0x3F800000` | second site stores float 1.0 (0x3F800000) |
| rbp+0x90 | 16 | W | `0x58a2054  movaps [rbp+0x90],xmm6` | - |
| rbp+0xA0 | 16 | W | `0x58a206d  movaps [rbp+0xA0],xmm0` | - |
| 0xF0922E0 | 16 | R | `0x58a2074  movaps xmm0,[0xF0922E0]` | - |
| rbp+0xB0 | 16 | W | `0x58a207b  movaps [rbp+0xB0],xmm0` | - |
| rbp+0xC0 | 16 / 8 | R | `0x58a209d  movaps xmm0,[rbp+0xC0]`<br>`0x58a2177  movsd xmm5,[rbp+0xC0]` | - |
| rbp+0xD0 | 16 | R | `0x58a20a4  movaps xmm1,[rbp+0xD0]`<br>`0x58a21b7  movups xmm3,[rbp+0xD0]` | - |
| rbp+0xE0 | 16 | R | `0x58a20ab  movaps xmm2,[rbp+0xE0]`<br>`0x58a21c4  movups xmm2,[rbp+0xE0]` | - |
| rbp+0xF0 | 16 | R | `0x58a20b2  movaps xmm3,[rbp+0xF0]`<br>`0x58a21cb  movups xmm10,[rbp+0xF0]` | - |
| rbp+0x110 | 16 / 8 | W | `0x58a20b9  movaps [rbp+0x110],xmm0`<br>`0x58a217f  movsd [rbp+0x110],xmm5` | - |
| rbp+0x120 | 16 | W | `0x58a20c0  movaps [rbp+0x120],xmm1` | - |
| rbp+0x130 | 16 | W | `0x58a20c7  movaps [rbp+0x130],xmm2` | - |
| rbp+0x140 | 16 | W | `0x58a20ce  movaps [rbp+0x140],xmm3` | - |
| rbp+0x84 | 16 | W | `0x58a20e6  movups [rax],xmm8` (rax = rbp+0x84) | - |
| rbp+0x94 | 4 | W | `0x58a20ea  mov dword ptr [rbp+0x94],0x3F800000` | stores float 1.0 (0x3F800000) |
| rbp+0x98 | 16 | W | `0x58a20f4  movups [rax+0x14],xmm8` (rax+0x14 = rbp+0x98) | - |
| rbp+0x70 | 8 | R | `0x58a20f9  movsd xmm0,[rbp+0x70]` | - |
| rbp+0x78 | 4 | R | `0x58a210f  movss xmm0,[rbp+0x78]` | - |
| 0xEEC8060 | 4 | R | `0x58a2118  movss xmm4,[0xEEC8060]` | - |
| 0xEFD32F0 | 16 | R | `0x58a2133  addps xmm1,[0xEFD32F0]` | - |
| 0xF0A4080 | 16 | R | `0x58a2141  movaps xmm2,[0xF0A4080]` | - |
| rbp+0xA8 | 16 | W | `0x58a214e  movups [rbp+0xA8],xmm2` | - |
| rbp+0xB8 | 8 | W | `0x58a2155  movlps [rbp+0xB8],xmm1` | - |
| rbp+0xC8 | 4 | R | `0x58a2187  movss xmm6,[rbp+0xC8]` | - |
| rbp+0x118 | 4 | W | `0x58a218f  movss [rbp+0x118],xmm6` | - |
| rbp+0xF8 | 4 | R | `0x58a2197  movss xmm7,[rbp+0xF8]` | - |
| rbp+0xD8 | 4 | R | `0x58a219f  movss xmm4,[rbp+0xD8]` | - |
| rbp+0xE8 | 4 | R | `0x58a21a7  movss xmm1,[rbp+0xE8]` | - |
| rbp-0x1C | 4 | R | `0x58a21b2  cvtsi2ss xmm0,dword ptr [rbp-0x1C]` | - |
| rbp-0x20 | 4 | R | `0x58a21be  cvtsi2ss xmm9,dword ptr [rbp-0x20]` | - |
| rbx+0x6C | 16 | R/W | `0x58a2244  movups xmm0,[rbx+0x6C]`<br>`0x58a2286  movups [rbx+0x6C],xmm0` | - |
| rbx+0x7C | 8 | R/W | `0x58a228a  movsd xmm0,[rbx+0x7C]`<br>`0x58a229d  movlps [rbx+0x7C],xmm0` | - |
| rsi+0x1D4 | 4 | W | `0x58a22b3  mov dword ptr [rax+8],0` (rax = rsi+0x1CC, store at [rax+8]) | - |
| rsi+0x1CC | 8 | W | `0x58a22ba  mov qword ptr [rax],0` (rax = rsi+0x1CC) | - |
| rsi+0x1E0 | 4 | W | `0x58a22c8  mov [rax+8],r14d` (rax = rsi+0x1D8, store at [rax+8]) | - |
| rsi+0x1D8 | 8 | W | `0x58a22cc  mov [rax],r15` (rax = rsi+0x1D8) | - |
| rbp+0x60 | 8 | R | `0x58a22cf  mov rax,[rbp+0x60]` | - |
| rbp+0x48 | 8 | R | `0x58a22dd  mov rcx,[rbp+0x48]` | - |
| rcx-8 | 8 | R | `0x58a22f2  mov r8,[rcx-8]` | - |
| 0x129CC628 | 4 | R | `0x58a2328  cmp dword ptr [0x129CC628],0xFFFFFFFF` | - |
| 0x129CC624 | 1 | W | `0x58a2335  mov byte ptr [0x129CC624],0` | - |
| rbp+0x160 | 16 | R | `0x58a234d  movaps xmm6,[rbp+0x160]` | - |
| rbp+0x170 | 16 | R | `0x58a2354  movaps xmm7,[rbp+0x170]` | - |
| rbp+0x180 | 16 | R | `0x58a235b  movaps xmm8,[rbp+0x180]` | - |
| rbp+0x190 | 16 | R | `0x58a2363  movaps xmm9,[rbp+0x190]` | - |
| rbp+0x1A0 | 16 | R | `0x58a236b  movaps xmm10,[rbp+0x1A0]` | - |
| rbp+0x1B0 | 16 | R | `0x58a2373  movaps xmm11,[rbp+0x1B0]` | - |
| rbp+0x1C0 | 16 | R | `0x58a237b  movaps xmm12,[rbp+0x1C0]` | - |
| rbp+0x1D0 | 16 | R | `0x58a2383  movaps xmm13,[rbp+0x1D0]` | - |
| rbp+0x1E0 | 16 | R | `0x58a238b  movaps xmm14,[rbp+0x1E0]` | - |
| rbp+0x1F0 | 16 | R | `0x58a2393  movaps xmm15,[rbp+0x1F0]` | - |
| rsp+0x20 | 8 | W | `0x58a23b4  mov qword ptr [rsp+0x20],0` | - |
| rsp (implicit stack top) | 8 | R | `0x58a23a2  pop rbx`<br>`0x58a23a3  pop rdi`<br>`0x58a23a4  pop rsi`<br>`0x58a23a5  pop r12`<br>`0x58a23a7  pop r13`<br>`0x58a23a9  pop r14`<br>`0x58a23ab  pop r15`<br>`0x58a23ad  pop rbp` | epilogue callee-saved register restores (implicit [rsp] loads) |

Open [?]: the exact structure type behind [rbp+0x80..0xF0] rows, [rbx+0x6C/+0x7C] vertex row, and the globals at 0x129CC624/0x129CC628 is not shown by this slice; callees 0xAA6580, 0x541A8A0, 0x9BC830, 0xE938CB0, 0xE938D70, 0x78ED0 and import [0xF9A8C78] are not resolved here.

## TOOL REQUESTS

None — no helper scripts written; verification only with tools/sigs/verify_oc.py.
