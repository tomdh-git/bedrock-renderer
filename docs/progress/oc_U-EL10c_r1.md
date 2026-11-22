## NEXT
DONE

# Unit U-EL10c — L10c viewport and render-resolution selection, dynamic resolution pending

GOAL (from docs/RENDER_CHECKLIST.md line 362): close "L10c viewport and render-resolution selection, dynamic resolution pending". Do ONLY the pending part: dynamic resolution / render-resolution selection (who selects the render resolution and the downscale ratio, e.g. the 0.65 seen live on views 19-25/44-45).

Known anchors (from docs/progress/platform-versioning-live.md L10c entries):
- TAAU body 0xbc8cfd0 consumes pass-ctx: float ctx+0x1F0 = render/display ratio, u16 dims ctx+0x1E0; RenderResolution = ratio*dims (0xbc8d34e..0xbc8d36d). Writer of ctx+0x1F0 NOT located [blocking fact, live note line 138].
- 0x67c73d0 (called from BgfxFrameBuilder::endFrame 0x66232b0) copies a large frame-parameter struct field by field incl. +0x1DC, +0x1E0 (float/dword), +0x1E4, +0x1E8 (u16), +0x1EA (u8), +0x1EC, +0x1F0 (float ratio), +0x1F4, +0x1F8; source arg rsi filled upstream of endFrame [platform-versioning-live.md lines 140-141].

DATA GATHERED: disassembly of 0x67c73d0 (docs/data/listings/_tmp_67c73d0.txt) and of TAAU 0xbc8cfd0 (docs/data/listings/_tmp_bc8cfd0.txt). Confirmed r13 = pass ctx at TAAU (`bc8cffe mov [rbp+0x98],r8`; `bc8d1d3 mov r13,[rbp+0x98]`).

## TABLE (name | rva or offset | size | verbatim `0xRVA  instr` proof | tag)

Sizes per rule: movups 16, movq 8, movss/dword 4, word 2, byte 1. Full verbatim proof lines are listed verbatim under VERBATIM PROOF LINES below; the table references them by RVA.

| render/display ratio field (float) +0x1F0 of pass-ctx / frame-params | +0x1F0 | 4 | 0x67c7917, 0x67c791f (0x67c73d0 copy src rsi -> dest rdx); 0xbc8d1e4, 0xbc8d34e (TAAU 0xbc8cfd0 consume; r13=pass ctx) | [V] |
| viewport render dims (u16 w x h packed in dword) field +0x1E0 | +0x1E0 | 4 | 0x67c78cc, 0x67c78d4 (0x67c73d0 copy); 0xbc8d356, 0xbc8d363, 0xbc8d367 (TAAU unpack to width/height floats) | [V] |
| RenderResolution = ratio x dims computation (per-view render resolution) | 0xbc8d34e..0xbc8d374 | 4 | 0xbc8d34e, 0xbc8d356, 0xbc8d363, 0xbc8d367, 0xbc8d36a, 0xbc8d36d, 0xbc8d370, 0xbc8d374 | [V] |

## VERBATIM PROOF LINES (each line starts with `0xRVA  instr`; verified by verify_oc against rdis)
0x67c7917  movss xmm0,[rsi+0x1F0]
0x67c791f  movss [rdx+0x1F0],xmm0
0x67c78cc  movss xmm0,[rsi+0x1E0]
0x67c78d4  movss [rdx+0x1E0],xmm0
0xbc8d1e4  movss xmm0,[r13+0x1F0]
0xbc8d34e  movups xmm0,[r13+0x1F0]
0xbc8d356  movq xmm1,[r13+0x1E0]
0xbc8d363  punpcklwd xmm1,xmm2
0xbc8d367  cvtdq2ps xmm1,xmm1
0xbc8d36a  unpcklps xmm0,xmm0
0xbc8d36d  mulps xmm0,xmm1
0xbc8d370  movq xmm0,xmm0
0xbc8d374  movdqu [rbp+0x40],xmm0

## Live corroboration [V live]
docs/progress/platform-versioning-live.md line 31: backbuffer 1920x1137 (Frame+0xDC5808=0x780, +0xDC580C=0x471); scene views 1248x739 = exactly 0.65 x 1920x1137 on views 19-25/44-45, consistent with ctx+0x1F0 = 0.65. This proves the RATIO VALUE is 0.65 at runtime, but not the CODE that writes it.

## BLOCKING FACT (single)
The writer/selector of the render/display ratio (+0x1F0) value — i.e. who sets ctx+0x1F0 / fills the source rsi of 0x67c73d0 — is NOT located. Whole-binary scans for +0x1F0 are dominated by stack-frame matches; the option strings (upscaling_percentage 0xf5e13cc, target_resolution) have no direct code refs (registered through the options table); the producer is upstream of endFrame 0x66232b0 and not traced. Therefore "render-resolution selection / dynamic resolution" (the act of choosing the ratio) is not proven by any [V] row.

## CLOSES?
NO — not every pending part of "L10c viewport and render-resolution selection, dynamic resolution pending" is proven by [V] rows. The ratio field +0x1F0 is proven to exist, to be copied field-by-field (0x67c73d0), and to be consumed to compute RenderResolution (TAAU 0xbc8d34e..0xbc8d374), but the CODE THAT WRITES/SELECTS the ratio value (+0x1F0) is not located — single blocking fact above. No other pending offset remains unaccounted for; the only gap is the ratio writer.
