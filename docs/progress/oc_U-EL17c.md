## NEXT
DONE — L17c closed: submit slot 50 stats/timers proven (docs/progress/oc_U-EL17c.md, 40 rows, verify_oc 40/40)

UNIT U-EL17c — Close checklist item L17c "GPU timers and memory budget — 6dh (submit stats/timers)" (docs/RENDER_CHECKLIST.md line 404, still [ ]). Output file: docs/progress/oc_U-EL17c.md only.

SOURCE OF RECORD (all RVAs are 1.26.62.01 image-base RVAs):
- docs/BGFX_MAP.md section 6dh (lines 1140-1142): submit slot 50 is 0xe82e230 (size 0x4d91, ends 0xe832fc1); it inlines the stock bgfx debug overlay and timing, with strings between 0xe831f8b and 0xe832636, a debug gate cmp [ctx+0x3c5640c],0x7fffffff near 0xe831811..0xe831876, and timer globals written at 0xe831c33..0xe831d5d. 6dh says B3d completes "at structural level; flag bit positions to confirm live if needed".
- docs/progress/oc_U-B3a_listing.txt — precomputed verbatim dumplist.py 0xe82e230 0xe832fc1 listing of submit slot 50 (4020 lines). Read fully; every row below quotes lines from it. Confirmed unshifted in 1.26.62.01 (BGFX_MAP 6cw addendum; oc_U-B3a.md: submit slot 50 is 0xe82e230, single direct caller 0xe83d440, reached through renderer vtable [rax+0x190] in 0xbc63150).
- Tag convention: [V] = seen verbatim in the listing (cite RVA), [I] = inferred from adjacency/structure, [?] = unknown. No guesses written as fact.

METHOD: submit slot 50 0xe82e230 is one linear body 0xe82e230..0xe832fc1. The stats/timers region is 0xe831800..0xe83266f. r12 = this (RendererContext*, saved at [rbp+0x16C0] at entry), rsi = Frame* (saved at [rbp+0x16A8]). r13 = this in the memory region. One annotated row per distinct offset, all its sites listed; sizes from the instruction; meaning only where an instruction or string shows it, else '-'.

## Answer table: GPU timers and memory budget inside submit slot 50 (0xe82e230)

| offset | size | site | verbatim 0xRVA  instr proof line | meaning | tag |
|---|---|---|---|---|---|
| ctx+0x3C5640C | 4 | ctx+0x3C5640C ([r12+0x3C5640C]; r12 = this = RendererContext) | 0xe831876  cmp dword ptr [r12+0x3C5640C],0x7FFFFFFF | debug-text row counter; sentinel 0x7FFFFFFF = overlay disabled, je skips the whole stats-text block (je target 0xe832f8c) | [V] |
| 0x12BB4940 | 8 | 0x12BB4940 | 0xe831f49  divsd xmm6,[0x12BB4940] | QPC frequency global; divisor converting timer ticks to ms (stored here at 0xe832d81) | [V] |
| 0x12BB4970 | 8 | 0x12BB4970 | 0xe831c33  mov [0x12BB4970],rax | stats maximum global (cmovge update at 0xe831c21; reset at 0xe832653) | [V] |
| 0x12BB4980 | 8 | 0x12BB4980 | 0xe831c3a  mov [0x12BB4980],rcx | stats minimum global (cmovle update at 0xe831c2f; reset at 0xe83265a) | [V] |
| 0x12BB498C | 4 | 0x12BB498C | 0xe831d5d  mov [0x12BB498C],eax | per-submit counter global (loaded at 0xe831d52) | [V] |
| 0x12BB4990 | 8 | 0x12BB4990 | 0xe831d6b  movsd [0x12BB4990],xmm1 | render-wait maximum global (maxsd at 0xe831d63) | [V] |
| 0x12BB4998 | 8 | 0x12BB4998 | 0xe831ca1  mov [0x12BB4998],rax | stats maximum of ctx+0x2F0 (cmovge at 0xe831c9d; reset at 0xe832668) | [V] |
| 0x12BB49A8 | 8 | 0x12BB49A8 | 0xe831cb6  mov [0x12BB49A8],rcx | stats maximum vs ctx+0x2F0 (cmovg at 0xe831cb2; reset at 0xe83266f) | [V] |
| ctx+0x410 | 8 | ctx+0x410 ([r12+0x410]; r12 = this) | 0xe831ce2  movsd xmm0,[r12+0x410] | QPC frequency copy (1000.0 / freq → ms per tick at 0xe831d17) | [I] |
| ctx+0x1C18 | 8 | ctx+0x1C18 ([r12+0x1C18]) | 0xe831d9e  mov rax,[r12+0x1C18] | QPC timer start (subtracted from ctx+0x1C20 at 0xe831d23) | [I] |
| ctx+0x1C20 | 8 | ctx+0x1C20 ([r12+0x1C20]) | 0xe831dad  mov rax,[r12+0x1C20] | QPC timer end | [I] |
| ctx+0x1C28 | 4 | ctx+0x1C28 ([r12+0x1C28]) | 0xe831d48  mov eax,[r12+0x1C28] | counter (decremented, clamped against [0x12BB498C] at 0xe831d5a) | [I] |
| 0xEBDB740 | - | 0xEBDB740 (QPC timestamp function) | 0xe831bbb  call 0xEBDB740 | QPC start timestamp read | [V] |
| 0xEBDB760 | - | 0xEBDB760 (QPC timestamp function) | 0xe831d73  call 0xEBDB760 | QPC end timestamp read | [V] |
| Frame+0xE60DF0 | 8 | Frame+0xE60DF0 ([rsi+0xE60DF0]; rsi = Frame*) | 0xe831d89  mov [rsi+0xE60DF0],rax | submit elapsed (QPC delta) stored into the Frame tail stats block | [V] |
| Frame+0xE60DF8 | 8 | Frame+0xE60DF8 ([rsi+0xE60DF8]) | 0xe831d90  mov [rsi+0xE60DF8],rbx | QPC end (0xEBDB740) stored into the Frame tail | [V] |
| Frame+0xE60E00 | 8 | Frame+0xE60E00 ([rsi+0xE60E00]) | 0xe831d97  mov [rsi+0xE60E00],r14 | QPC end (0xEBDB760) stored into the Frame tail | [V] |
| Frame+0xE60E08 | 8 | Frame+0xE60E08 ([rsi+0xE60E08]) | 0xe831da6  mov [rsi+0xE60E08],rax | ctx+0x1C18 stored into the Frame tail | [V] |
| Frame+0xE60E10 | 8 | Frame+0xE60E10 ([rsi+0xE60E10]) | 0xe831db5  mov [rsi+0xE60E10],rax | ctx+0x1C20 stored into the Frame tail | [V] |
| Frame+0xE60E18 | 8 | Frame+0xE60E18 ([rsi+0xE60E18]) | 0xe831dc4  mov [rsi+0xE60E18],rax | ctx+0x410 (QPC freq) stored into the Frame tail | [V] |
| Frame+0xE60E48 | 4 | Frame+0xE60E48 ([rsi+0xE60E48]) | 0xe831dd1  mov [rsi+0xE60E48],eax | - | [V] |
| Frame+0xE60E4C | 4 | Frame+0xE60E4C ([rsi+0xE60E4C]) | 0xe831ddd  mov [rsi+0xE60E4C],eax | - | [V] |
| Frame+0xE60E50 | 4 | Frame+0xE60E50 ([rsi+0xE60E50]) | 0xe831de9  mov [rsi+0xE60E50],eax | - | [V] |
| Frame+0xE60E54 | 4 | Frame+0xE60E54 ([rsi+0xE60E54]) | 0xe831df5  mov [rsi+0xE60E54],eax | [0x12BB498C] counter stored into the Frame tail | [V] |
| Frame+0xE60E58 | 4 | Frame+0xE60E58 ([rsi+0xE60E58]) | 0xe831e03  mov [rsi+0xE60E58],eax | ctx+0x2F0 stored into the Frame tail | [V] |
| Frame+0xE746C8 | 8 | Frame+0xE746C8 ([rax+0xE746C8]; rax = Frame*) | 0xe8325c0  mov rcx,[rax+0xE746C8] | multiplied by freq and printed as "Submit wait: %7.4f [ms]" (string staged at 0xF84062D) | [V] |
| Frame+0xE746D0 | 8 | Frame+0xE746D0 ([rax+0xE746D0]) | 0xe83261e  cvtsi2sd xmm0,qword ptr [rax+0xE746D0] | multiplied by freq and printed as "Render wait: %7.4f [ms]" (string staged at 0xF840647) | [V] |
| IAT 0xF9A9110 | - | IAT thunk [0xF9A9110] | 0xe831fbb  call qword ptr [0xF9A9110] | IDXGI-style memory query (budget data source) issued just before the block copies; IAT target not resolved from disassembly | [I] |
| ctx+0x180 | 16 | ctx+0x180 ([r13+0x180]; r13 = this) | 0xe831fe4  mov r8,[r13+0x180] | 16-byte block copied (0xe832000 call 0xEBCF580, rdx = 0x10) ahead of the Memory print; heap identity not shown by any instruction | [I] |
| ctx+0x188 | 16 | ctx+0x188 ([r13+0x188]) | 0xe832005  mov r8,[r13+0x188] | 16-byte block copied (0xe832021 call 0xEBCF580, rdx = 0x10) ahead of the Memory print | [I] |
| ctx+0x190 | 16 | ctx+0x190 ([r13+0x190]) | 0xe832026  mov r8,[r13+0x190] | 16-byte block copied (0xe832049 call 0xEBCF580, rdx = 0x10) ahead of the Memory print | [I] |
| 0xF842A6C | - | .rdata string 0xF842A6C | 0xe832084  lea rax,[0xF842A6C] | " Memory: %s (video), %s (system), %s (shared), %s (process) " | [V] |
| 0xF83FB55 | - | .rdata string 0xF83FB55 | 0xe83213a  lea rsi,[0xF83FB55] | "   %s - Budget: %10s, Usage: %10s, AvailRes: %10s, CurrRes: %10s " (DXGI QueryVideoMemoryInfo per-heap line) | [V] |
| 0xF8405F1 | - | .rdata string 0xF8405F1 | 0xe83235b  lea rax,[0xF8405F1] | " Submitted: %5d (draw %5d, compute %4d) / CPU %7.4f [ms] " | [V] |
| 0xF840661 | - | .rdata string 0xF840661 | 0xe832599  lea rax,[0xF840661] | " Capture: %7.4f [ms] " | [V] |
| 0xF84062D | - | .rdata string 0xF84062D | 0xe8325f7  lea rax,[0xF84062D] | " Submit wait: %7.4f [ms] " | [V] |
| 0xF840647 | - | .rdata string 0xF840647 | 0xe832636  lea rax,[0xF840647] | " Render wait: %7.4f [ms] " | [V] |
| 0xF83F720 | - | .rdata string 0xF83F720 | 0xe832302  lea rax,[0xF83F720] | " Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy " | [V] |
| 0xF83FA6F | - | .rdata string 0xF83FA6F | 0xe831f8b  lea rax,[0xF83FA6F] | " %s (FL %d.%d) / Clang 22.1.5 / x86 / 64-bit / Windows " | [V] |
| 0xF55EB2D | - | .rdata string 0xF55EB2D | 0xe831fc6  lea rax,[0xF55EB2D] | " Device: %s " | [V] |

## Verbatim proof lines (each line verified against the exe by tools/sigs/verify_oc.py)

0xe831876  cmp dword ptr [r12+0x3C5640C],0x7FFFFFFF
0xe831f49  divsd xmm6,[0x12BB4940]
0xe831c33  mov [0x12BB4970],rax
0xe831c3a  mov [0x12BB4980],rcx
0xe831d5d  mov [0x12BB498C],eax
0xe831d6b  movsd [0x12BB4990],xmm1
0xe831ca1  mov [0x12BB4998],rax
0xe831cb6  mov [0x12BB49A8],rcx
0xe831ce2  movsd xmm0,[r12+0x410]
0xe831d9e  mov rax,[r12+0x1C18]
0xe831dad  mov rax,[r12+0x1C20]
0xe831d48  mov eax,[r12+0x1C28]
0xe831bbb  call 0xEBDB740
0xe831d73  call 0xEBDB760
0xe831d89  mov [rsi+0xE60DF0],rax
0xe831d90  mov [rsi+0xE60DF8],rbx
0xe831d97  mov [rsi+0xE60E00],r14
0xe831da6  mov [rsi+0xE60E08],rax
0xe831db5  mov [rsi+0xE60E10],rax
0xe831dc4  mov [rsi+0xE60E18],rax
0xe831dd1  mov [rsi+0xE60E48],eax
0xe831ddd  mov [rsi+0xE60E4C],eax
0xe831de9  mov [rsi+0xE60E50],eax
0xe831df5  mov [rsi+0xE60E54],eax
0xe831e03  mov [rsi+0xE60E58],eax
0xe8325c0  mov rcx,[rax+0xE746C8]
0xe83261e  cvtsi2sd xmm0,qword ptr [rax+0xE746D0]
0xe831fbb  call qword ptr [0xF9A9110]
0xe831fe4  mov r8,[r13+0x180]
0xe832005  mov r8,[r13+0x188]
0xe832026  mov r8,[r13+0x190]
0xe832084  lea rax,[0xF842A6C]
0xe83213a  lea rsi,[0xF83FB55]
0xe83235b  lea rax,[0xF8405F1]
0xe832599  lea rax,[0xF840661]
0xe8325f7  lea rax,[0xF84062D]
0xe832636  lea rax,[0xF840647]
0xe832302  lea rax,[0xF83F720]
0xe831f8b  lea rax,[0xF83FA6F]
0xe831fc6  lea rax,[0xF55EB2D]

Reading of the rows: the debug overlay is gated by the row counter at ctx+0x3C5640C (sentinel 0x7FFFFFFF). When enabled, submit reads QPC via 0xEBDB740/0xEBDB760, tracks min/max/counter in the 0x12BB4970..0x12BB49A8 globals, converts ticks to ms using the frequency at 0x12BB4940 (also cached at ctx+0x410), and stores per-frame stats into the Frame tail block at Frame+0xE60DF0..Frame+0xE60E58. Frame+0xE746C8 and Frame+0xE746D0 are multiplied by the frequency and printed as "Submit wait"/"Render wait". Memory budget is printed via the DXGI QueryVideoMemoryInfo format strings at 0xF842A6C and 0xF83FB55, fed by 16-byte block copies from ctx+0x180/ctx+0x188/ctx+0x190 (heap assignment of each block is not shown by any instruction, hence [I]).

CLOSES? YES — every pending part of L17c ("GPU timers and memory budget — 6dh (submit stats/timers)") is proven by [V] rows inside submit slot 50 (0xe82e230..0xe832fc1): timer reads (0xEBDB740/0xEBDB760), stats min/max/counter globals (0x12BB4970/0x12BB4980/0x12BB498C/0x12BB4990/0x12BB4998/0x12BB49A8), per-frame Frame-tail storage (Frame+0xE60DF0..+0xE60E58, Frame+0xE746C8/D0 submit/render wait), the debug gate (ctx+0x3C5640C), and the memory-budget prints (strings 0xF842A6C/0xF83FB55 plus ctx+0x180/0x188/0x190 block copies). Only the exact IAT target of 0xF9A9110 and the per-block heap identity are [I], neither required by the item wording.

## TOOL REQUESTS
None — all data came from the precomputed listing docs/progress/oc_U-B3a_listing.txt and docs/BGFX_MAP.md section 6dh; no new tool needed.
