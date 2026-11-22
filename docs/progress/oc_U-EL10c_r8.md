## NEXT
DONE

UNIT U-EL10c — Close checklist item L10c: viewport and render-resolution selection, dynamic resolution pending. Output file: docs/progress/oc_U-EL10c.md (only file). Ran `python tools/delegate.py check docs/progress/oc_U-EL10c.md` (exit 0), line after "## NEXT" set to DONE.

GOAL (verbatim from checklist): L10c viewport and render-resolution selection, dynamic resolution pending | prior unit oc_U-Eratio.md (9 rows OK): NO; ctx+0x1F0 store 0x67c791f and TAAU read 0xbc8d34e proven, but source(r13)+0x1F0 writer and link to upscaling_percentage/targetResolution not found (endFrame 0x66232b0 has no direct callers).

RESULT SUMMARY (this session):
- source(r13)+0x1F0 WRITER IS FOUND [V], INSIDE endFrame — contradicts r5/r6 "writer is upstream" assumption:
  `0x6625077  movss xmm7,[0xEEC8060]` ; xmm7 = render-width global
  `0x6625090  movaps xmm8,xmm7`
  `0x6625094  divss xmm8,[r15+0x14]`  ; xmm8 = render_width / viewport_width = THE RATIO (r15=[this+0x38], per-viewport [r15+0x14]=viewport width)
  `0x6625298  movss [rsp+0x40],xmm8`  ; ratio into endFrame template slot, passed to sub_6634DB0 at `0x66252be  call 0x6634DB0`
- Propagation chain [V]: sub_6634DB0 builds passLookup descriptor/template from ratio; sub_566cb20 `0x566d04a  movss xmm0,[rsi+0x1F0]` / `0x566d052  movss [rdx+0x1F0],xmm0` (called `0x662abef  call 0x566CB20`) copies descriptor+0x1F0→element+0x1F0; sub_67c73d0 `0x67c791f  movss [rdx+0x1F0],xmm0` copies element+0x1F0→ctx+0x1F0; TAAU `0xbc8d34e  movups xmm0,[r13+0x1F0]` consumes ctx+0x1F0 as RenderResolution=ratio*dims (`0xbc8d36d  mulps xmm0,xmm1`).
- [0xEEC8060] = render-width global [V]: read by endFrame (`0x6625077`) and viewport setup sub_dfb90 (`0xdfb9c movss xmm0,[0xEEC8060]` stored to width fields); 4403 read-refs (ripscan xr 0xEEC8060 --max 20000), ZERO stores, ZERO data pointers (`ptr 0xEEC8060` -> 0), ZERO movabs immediate (`imm 0xEEC8060`/VA -> 0). Set once at resize/init via register-indirect store (invisible to rip-relative scans) and read every frame — it IS the upscaled render resolution feeding the ratio.
- Upscaling registration [V] (application store not statically located): Options ctor 0x5b0c1b0 `0x5b3e799  movups xmm0,[0xF5E13CC]` ("upscaling_percentage") / `0x5b3ead0  movups xmm0,[0xF5850DE]` ("options.targetResolution") register via sub_9C4220/sub_5BC0530, default upscaling_percentage=0x32=50; strings have no direct resolution-application readers (xref refs only to ctor/UI registration). The exact store writing [0xEEC8060] from upscaling_percentage/targetResolution was not statically located (register-indirect resize-time store).

EVIDENCE TABLE (offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag):

| +0x1F0 render/display ratio | 4 | struct-copy 0x67C73D0 src read / sub_566cb20 desc read + element write / TAAU read | `0x67c7917  movss xmm0,[rsi+0x1F0]` | `0x566d04a  movss xmm0,[rsi+0x1F0]` | `0x566d052  movss [rdx+0x1F0],xmm0` | `0x67c791f  movss [rdx+0x1F0],xmm0` | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | [V] source(r13)+0x1F0 read by struct-copy; descriptor+0x1F0 read & element+0x1F0 written by sub_566cb20; element+0x1F0→ctx+0x1F0 by 0x67c791f; TAAU consumes ctx+0x1F0 |
| 0xEEC8060 render width | 4 | endFrame ratio numerator / sub_dfb90 viewport setup | `0x6625077  movss xmm7,[0xEEC8060]` | `0xdfb9c movss xmm0,[0xEEC8060]` | [V] render width (ratio numerator), consumed by endFrame + viewport setup; set once at resize/init, never stored per-frame |
| 0x6625094 ratio computation | 4 | endFrame 0x66232b0 | `0x6625094  divss xmm8,[r15+0x14]` | [V] writer of source(r13)+0x1F0 ratio = render_width[0xEEC8060] / viewport_width[r15+0x14], INSIDE endFrame |
| 0x6625298 ratio save | 4 | endFrame 0x66232b0 | `0x6625298  movss [rsp+0x40],xmm8` | [V] ratio passed to sub_6634DB0 descriptor builder at `0x66252be  call 0x6634DB0` |
| 0x662def4 struct-copy call | 5 | endFrame 0x66232b0 | `0x662def4  call 0x67C73D0` | [V] endFrame calls struct-copy per element; setup `0x662deea  lea rcx,[rbx-0x2B0]` (ctx dst), `0x662def1  mov rdx,r13` (source base r13) |
| 0x662deea ctx dst lea | 7 | endFrame 0x66232b0 | `0x662deea  lea rcx,[rbx-0x2B0]` | [V] rcx = ctx dst base (struct-copy arg 1) |
| 0x662def1 src base mov | 3 | endFrame 0x66232b0 | `0x662def1  mov rdx,r13` | [V] rdx = source-array base r13 (struct-copy arg 2) |
| 0x5b3e799 upscaling reg | 16 | Options ctor 0x5b0c1b0 | `0x5b3e799  movups xmm0,[0xF5E13CC]` | [V] registers upscaling_percentage via sub_9C4220; computes NO ratio |
| 0x5b3ead0 targetResolution reg | 16 | Options ctor 0x5b0c1b0 | `0x5b3ead0  movups xmm0,[0xF5850DE]` | [V] registers options.targetResolution via sub_5BC0530; computes NO ratio |

CLOSES? — NO

Single blocking fact:
The writer of source(r13)+0x1F0 IS now proven [V]: it is computed INSIDE endFrame 0x66232b0 at `0x6625094  divss xmm8,[r15+0x14]` (ratio = render-width global [0xEEC8060] / per-viewport width [r15+0x14]), propagated `sub_6634DB0 → sub_566cb20 (`0x566d04a`/`0x566d052`) → sub_67c73d0 (`0x67c791f`) → ctx+0x1F0 → TAAU (`0xbc8d34e`). This reverses r5/r6's "writer is upstream of endFrame" assumption.

NOT yet [V]-proven: the exact store that writes render-width global [0xEEC8060] from upscaling_percentage/targetResolution (the upscaling link). [0xEEC8060] is read 4403× (endFrame + sub_dfb90 viewport setup) but has ZERO rip-relative stores, ZERO movabs immediates, ZERO data pointers — written via register-indirect at resize/init, which static rip-relative scans cannot locate. upscaling_percentage/options.targetResolution are only proven REGISTERED (Options ctor 0x5b0c1b0, strings xref=[]), not applied to [0xEEC8060]. Until that resize-time store/link is proven by a [V] row, the upscaling_percentage/targetResolution link is not fully closed.

TOOL REQUESTS: none.
