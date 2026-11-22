## NEXT
step 2

UNIT U-EL10c — Close checklist item L10c: viewport and render-resolution selection, dynamic resolution pending. Output file: docs/progress/oc_U-EL10c.md (only file). Must run `python tools/delegate.py check docs/progress/oc_U-EL10c.md` (exit 0), then set line after "## NEXT" to DONE.

GOAL (verbatim from checklist): L10c viewport and render-resolution selection, dynamic resolution pending | prior unit oc_U-Eratio.md (9 rows OK): NO; ctx+0x1F0 store 0x67c791f and TAAU read 0xbc8d34e proven, but source(r13)+0x1F0 writer and link to upscaling_percentage/targetResolution not found (endFrame 0x66232b0 has no direct callers).

PENDING QUESTION (verbatim): find the WRITER of source(r13)+0x1F0 — the value that struct-copy 0x67C73D0 copies into ctx+0x1F0 — and link that value to upscaling_percentage / targetResolution.

KEY REVERSAL (found this session, NOT yet in r5/r6):
- The ratio IS computed INSIDE endFrame 0x66232b0, not upstream:
  - `6625077  movss xmm7,[0xEEC8060]`   ; xmm7 = render width global
  - `6625094  divss xmm8,[r15+0x14]`    ; xmm8 = render_width / viewport_width ([r15+0x14] = per-viewport width) — THIS IS THE RATIO
  - `6625298  movss [rsp+0x40],xmm8`    ; ratio saved into endFrame template stack slot
  - then sub_6634DB0(rcx=[rbp+0x170]=template base, ...) builds the passLookup descriptor/template; later sub_566cb20 copies template+0x1F0 -> element+0x1F0, sub_67c73d0 copies element+0x1F0 -> ctx+0x1F0 (`67c791f  movss [rdx+0x1F0],xmm0`), TAAU `bc8d34e movups xmm0,[r13+0x1F0]` consumes ctx+0x1F0.
- So source(r13)+0x1F0 WRITER = `6625094 divss xmm8,[r15+0x14]` (ratio), inside endFrame. The earlier assumption "writer is upstream of endFrame" was WRONG.

REMAINING GAP (link to upscaling_percentage/targetResolution):
- Render width global [0xEEC8060] is read per-frame but ripscan xr 0xEEC8060 found 4403 refs, ALL reads (movss xmm0,[0xEEC8060]); NO store found via ripscan.
- Stores to [0xEEC8060] in x64 must use `movabs reg,0xEEC8060; store [reg]` (no absolute addressing). Next: `imm 0xEEC8060` to find the writer, then trace that value back to upscaling_percentage/targetResolution (default upscaling_percentage=0x32=50 registered in Options ctor 0x5b0c1b0: `5b3e799 movups xmm0,[0xF5E13CC]`, `5b3ead0 movups xmm0,[0xF5850DE]`; strings xref=[]).
- Related global: `730a5 movss [0x128C0F88],xmm0` (also render width, from 0x73090 which reads [0xEEC8060]).

PROVEN [V] context (from oc_U-Eratio.md, re-verified):
- Struct-copy 0x67C73D0 (rsi = r13 = source-array base; rdx = r15 = ctx dst): `0x67c7917  movss xmm0,[rsi+0x1F0]` reads source(r13)+0x1F0; `0x67c791f  movss [rdx+0x1F0],xmm0` writes ctx+0x1F0. Pure field-by-field copy (0x2B0-byte elements), no computation.
- endFrame 0x66232b0 invokes the copy at `0x662def4  call 0x67C73D0` with `0x662deea  lea rcx,[rbx-0x2B0]` (rcx = ctx dst) and `0x662def1  mov rdx,r13` (rdx = source base). Loop: `0x662ded3  add r13,0x2B0` until r13 == rdi (`0x662dee1  cmp r13,rdi`).
- TAAU body `0xbc8d34e  movups xmm0,[r13+0x1F0]` reads ctx+0x1F0 as the render/display ratio (r13 = ctx there).
- Chain inside endFrame: passLookup descriptor +0x1F0 -> element +0x1F0 via sub_566cb20 (`566d04a movss xmm0,[rsi+0x1F0]` / `566d052 movss [rdx+0x1F0],xmm0`, called at `0x662abef call 0x566CB20`, rsi = passLookup descriptor from `0x662ab48 mov rsi,rax`), then element +0x1F0 -> ctx +0x1F0 via 0x67c791f.
- Options ctor 0x5b0c1b0: `0x5b3e799 movups xmm0,[0xF5E13CC]` ("upscaling_percentage") / `0x5b3ead0 movups xmm0,[0xF5850DE]` ("options.targetResolution") only REGISTER the properties via sub_9C4220/sub_5BC0530; computes NO ratio; strings have no code refs (xref refs = []).

NEXT STEPS:
1. `imm 0xEEC8060` -> find writer of render-width global [0xEEC8060].
2. Trace writer back to upscaling_percentage/targetResolution (render_width = upscaling_percentage% * display_width, or targetResolution).
3. Confirm sub_6634DB0 writes template+0x1F0 from the ratio xmm8 ([rsp+0x40]) — verify [rsp+0x40] reaches template+0x1F0.
4. Write evidence table, run delegate check, fix failures, set DONE.

CLOSES?: NO — pending: link from render-width global [0xEEC8060] writer to upscaling_percentage/targetResolution not yet proven by [V] row.
TOOL REQUESTS: none yet.
