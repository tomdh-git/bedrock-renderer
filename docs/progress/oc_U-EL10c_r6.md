## NEXT
step 2

UNIT U-EL10c — Close checklist item L10c: viewport and render-resolution selection, dynamic resolution pending. Output file: docs/progress/oc_U-EL10c.md (only file). Must run `python tools/delegate.py check docs/progress/oc_U-EL10c.md` (exit 0), then set line after "## NEXT" to DONE.

GOAL (verbatim from checklist): L10c viewport and render-resolution selection, dynamic resolution pending | prior unit oc_U-Eratio.md (9 rows OK): NO; ctx+0x1F0 store 0x67c791f and TAAU read 0xbc8d34e proven, but source(r13)+0x1F0 writer and link to upscaling_percentage/targetResolution not found (endFrame 0x66232b0 has no direct callers).

PENDING QUESTION (verbatim): find the WRITER of source(r13)+0x1F0 — the value that struct-copy 0x67C73D0 copies into ctx+0x1F0 — and link that value to upscaling_percentage / targetResolution.

PROVEN [V] context (from oc_U-Eratio.md, re-verified):
- Struct-copy 0x67C73D0 (rsi = r13 = source-array base; rdx = r15 = ctx dst): `0x67c7917  movss xmm0,[rsi+0x1F0]` reads source(r13)+0x1F0; `0x67c791f  movss [rdx+0x1F0],xmm0` writes ctx+0x1F0. Pure field-by-field copy (0x2B0-byte elements), no computation.
- endFrame 0x66232b0 invokes the copy at `0x662def4  call 0x67C73D0` with `0x662deea  lea rcx,[rbx-0x2B0]` (rcx = ctx dst) and `0x662def1  mov rdx,r13` (rdx = source base). Loop: `0x662ded3  add r13,0x2B0` until r13 == rdi (`0x662dee1  cmp r13,rdi`).
- TAAU body `0xbc8d34e  movups xmm0,[r13+0x1F0]` reads ctx+0x1F0 as the render/display ratio (r13 = ctx there).
- Chain inside endFrame: passLookup descriptor +0x1F0 -> element +0x1F0 via sub_566cb20 (`566d04a  movss xmm0,[rsi+0x1F0]` / `566d052  movss [rdx+0x1F0],xmm0`, called at `0x662abef  call 0x566CB20`, rsi = passLookup descriptor from `0x662ab48  mov rsi,rax`), then element +0x1F0 -> ctx +0x1F0 via 0x67c791f.
- Options ctor 0x5b0c1b0: `0x5b3e799  movups xmm0,[0xF5E13CC]` ("upscaling_percentage") / `0x5b3ead0  movups xmm0,[0xF5850DE]` ("options.targetResolution") only REGISTER the properties via sub_9C4220/sub_5BC0530; computes NO ratio; strings have no code refs (xref refs = []).

NEXT STEPS (per orchestrator r4 hint, in order):
1. grep docs/data/live/*.txt for RVAs 0x66232b0, 0x67c73d0, 0x566cb20, 0xbc8d34e, 0x5aba5c0 and the option strings; interpret [LIVE file:line] chains.
2. Find who writes the passLookup descriptor's +0x1F0 (descriptor rsi built upstream of endFrame; rsi source = `0x662ab48 mov rsi,rax`): scan functions writing the descriptor for a float store at +0x1F0; xref option strings to readers; connect by stored value.
3. If static analysis cannot reach it (endFrame only via indirect vtable slot-18 call, xref.py empty), queue a live capture of endFrame's caller (0x67c9c20 region / the function whose vtable slot holds 0x66232b0) and close what is supported.

CLOSES?: NO pending — single blocking fact: writer of source(r13)+0x1F0 and its link to upscaling_percentage/targetResolution not yet located.
TOOL REQUESTS: none yet.
