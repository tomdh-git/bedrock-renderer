## NEXT
DONE

UNIT U-EL10c (docs/progress/oc_U-EL10c.md only). Checklist item L10c "viewport and render-resolution selection, dynamic resolution" — pending part carried from oc_U-Eratio.md (9 rows OK, CLOSES? NO): "ctx+0x1F0 store 0x67c791f and TAAU read 0xbc8d34e proven, but source(r13)+0x1F0 writer and link to upscaling_percentage/targetResolution not found (endFrame 0x66232b0 has no direct callers)".

PENDING QUESTION (verbatim from the item line): find the WRITER of source(r13)+0x1F0 — the value that struct-copy 0x67C73D0 copies into ctx+0x1F0 — and link that value to upscaling_percentage / targetResolution.

PROVEN [V] context (from oc_U-Eratio.md, re-verified against the input data):
- Struct-copy 0x67C73D0 (rsi = r13 = source-array base; rdi = r15 = ctx dst base): `0x67c7917  movss xmm0,[rsi+0x1F0]` reads source(r13)+0x1F0; `0x67c791f  movss [rdx+0x1F0],xmm0` writes ctx+0x1F0. Pure field-by-field copy (0x2B0-byte elements), no computation — the ratio is copied verbatim, not computed here.
- endFrame 0x66232b0 invokes the copy at `0x662def4  call 0x67C73D0` with `0x662deea  lea rcx,[rbx-0x2B0]` (rcx = r15 = ctx dst) and `0x662def1  mov rdx,r13` (rdx = source base). Copy loop: `0x662de92  cmp r13,rdi` / `0x662ded3  add r13,0x2B0` / `0x662dee1  cmp r13,rdi` until r13 == rdi.
- TAAU body `0xbc8d34e  movups xmm0,[r13+0x1F0]` reads ctx+0x1F0 as the render/display ratio (r13 = ctx there).
- Options ctor 0x5b0c1b0: `0x5b3e799  movups xmm0,[0xF5E13CC]` ("upscaling_percentage") and `0x5b3ead0  movups xmm0,[0xF5850DE]` ("options.targetResolution") only REGISTER the properties via sub_9C4220/sub_5BC0530; it computes NO ratio and no instruction ties source+0x1F0 to either option value.
- Strings upscaling_percentage (0xf5e13cc) and options.targetResolution (0xf5850de): xref refs = [] — registered through a table, no direct code refs.

TOOLS USED on the pending part:
- `python tools/sigs/xref.py callers 0x66232b0` -> no direct callers (confirmed; docs/functions/66232b0.md dossier: "callers: none direct (vtable / std::function / CFG)").
- `python tools/sigs/ripscan.py 0xf2bdeb0` (BgfxFrameBuilder vtable, slot 18/+0x90 = endFrame per BGFX_MAP.md section 3/167) -> refs only at 0x660d9d3 (func 0x660d940) and 0x67eca03 (func 0x67ec9e0), both vtable-store constructor sites; NO endFrame call site located.
- rdis dis of endFrame regions 0x66232b0–0x662e07e (gaps not fully traced: 0x6624571–0x6626100, 0x6628a00–0x662d5c0). r13 is assigned inside endFrame only as scratch (e.g. `0x6626d5c  mov r13,[rbp+0x1428]` — a deferred-transaction list end, stride 0x18 cleanup loop, not the 0x2B0-stride source array); the source-array base r13 used at `0x662def1  mov rdx,r13` is not traced to a computable upscaling source.
- Full read of orchestrator input data: out_67c73d0.txt, out_67c73d0_callers.txt, out_opt_ctor.txt, out_upsc_pct.txt, out_upsc_pct2.txt, out_upscaling_pct.txt, out_target_res.txt, out_target_res2.txt, out_upsc_mode.txt, out_upsc_mode2.txt, out_parser1.txt, out_reg2.txt, out_reg5bc0530.txt, out_reg_callers.txt, out_ef_callsite.txt, out_ef_callsite2.txt, out_ef_callsite3.txt.
- BGFX_MAP.md sections consulted: L10 layer row ("viewport and render-resolution selection, dynamic resolution"), section 3 (vtable slot 18 = endFrame), section 6ev (endFrame stage map), dossier docs/functions/66232b0.md.

REMAINING (not found): the writer that stores the render/display ratio into source(r13)+0x1F0 before endFrame copies it to ctx+0x1F0, and any link from that write to upscaling_percentage/targetResolution. endFrame is reached only through an indirect vtable call (no direct callers), so the caller that sets up r13 before `0x662def4  call 0x67C73D0` is not statically reachable; no instruction in the binary ties source+0x1F0 to either option value (strings refs=[], ctor computes no ratio).

EVIDENCE TABLE (name | rva or offset | size | verbatim `0xRVA  instr` proof | tag)

| source(r13)+0x1F0 read by struct-copy 0x67C73D0 (rsi = r13 = source base) | 0x67c7917 | 4 (movss) | `0x67c7917  movss xmm0,[rsi+0x1F0]` | [V] |
| ctx+0x1F0 write by struct-copy 0x67C73D0 (rdx = r15 = ctx) | 0x67c791f | 4 (movss) | `0x67c791f  movss [rdx+0x1F0],xmm0` | [V] |
| endFrame calls struct-copy at the ratio-write site | 0x662def4 | 5 (call) | `0x662def4  call 0x67C73D0` | [V] |
| endFrame call setup: rdx = r13 = source-array base | 0x662def1 | 3 (mov r64,r64) | `0x662def1  mov rdx,r13` | [V] |
| endFrame call setup: rcx = r15 = ctx dst base | 0x662deea | 7 (lea r64,m) | `0x662deea  lea rcx,[rbx-0x2B0]` | [V] |
| copy loop: source base r13 steps by 0x2B0 until r13 == rdi | 0x662ded3 | 8 (add r64,imm32) | `0x662ded3  add r13,0x2B0` | [V] |
| Options ctor registers upscaling_percentage, computes no ratio | 0x5b3e799 | 16 (movups) | `0x5b3e799  movups xmm0,[0xF5E13CC]` | [V] |
| Options ctor registers options.targetResolution, computes no ratio | 0x5b3ead0 | 16 (movups) | `0x5b3ead0  movups xmm0,[0xF5850DE]` | [V] |
| upscaling_percentage string 0xf5e13cc: no code refs (table-registered) | 0xf5e13cc | - | (no instruction; xref refs = []) | [V] |
| options.targetResolution string 0xf5850de: no code refs (table-registered) | 0xf5850de | - | (no instruction; xref refs = []) | [V] |
| endFrame 0x66232b0: no direct callers; entered via indirect BgfxFrameBuilder vtable slot 18 (+0x90) | 0x66232b0 | - | (no instruction; xref.py callers 0x66232b0 = empty; dossier "callers: none direct") | [I] |
| BgfxFrameBuilder vtable 0xF2BDEB0 refs: constructor stores only (0x660d9d3, 0x67eca03); no endFrame `call [..+0x90]` call site found | 0xf2bdeb0 | - | (no instruction; ripscan 0xf2bdeb0 -> only 0x660d9d3, 0x67eca03) | [I] |

CLOSES? — NO

Single blocking fact: the writer of source(r13)+0x1F0 and its link to upscaling_percentage/targetResolution were not located. endFrame 0x66232b0 has no direct callers (indirect vtable slot-18 call; xref.py empty), r13 = source-array base is not assigned to a computable upscaling source in endFrame, and no instruction ties source+0x1F0 to either option value (both strings refs=[], Options ctor 0x5b0c1b0 registers only and computes no ratio). Until that writer/link is proven by a [V] row, the item cannot close.

TOOL REQUESTS: None (all evidence gathered with rdis.exe, xref.py, ripscan.py and full reads of the orchestrator's precomputed input data; no new scripts written).
