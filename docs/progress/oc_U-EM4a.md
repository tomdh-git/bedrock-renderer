## NEXT
DONE

# U-EM4a — M4a version-stable anchors for D2/D3 functions (Minecraft.Windows.exe 1.26.62.01)

## Goal
Close checklist item M4a: "For every D2/D3 function record the version-stable anchor (string / __FUNCSIG__ / unique sig) beside the RVA (Sigs.json + dossier "anchors" block)". Scope = the ten sigs listed on the item line: Encoder{submit,reset,frameSort}, FrameGraph{endFrame,generate,taskDispatch,viewSetupTask}, D3D12Context{drawExecutor,psoBuilder,drawFlush}.

## Files touched
- docs/progress/oc_U-EM4a.md — this note (created; the unit's output file, no other file).
- docs/functions/568cd90.md — filled the previously empty "Version-stable anchors" block for viewSetupTask 0x568cd90 (unique sig + view-record field offsets).
Not touched: Sigs.json (all ten entries already exist; existing entries are not edited), HookManager.cpp, CMake, any other dossier.

## Anchor status per function
Sigs.json entries (priority + comment RVA + unique sig, all present, not modified). Dossier anchors blocks: all ten exist; nine carried [V] content already; viewSetupTask's block was empty and is filled below.
- Encoder::submit 0xbc60740 — Sigs.json sig [V]; dossier docs/functions/bc60740.md anchors block: sig + layoutcheck-asserted constants [V]
- Encoder::reset 0xbc60d10 — Sigs.json sig [V]; dossier anchors block: sig + asserted constants [V]
- Encoder::frameSort 0xbc61e20 — Sigs.json sig [V]; dossier anchors block: sig + asserted constants [V]
- FrameGraph::endFrame 0xc270460 — Sigs.json sig [V]; dossier anchors block: string "BgfxContext - Generate and encode frame graph" + sig [V]
- FrameGraph::generate 0xc273420 — Sigs.json sig [V]; dossier anchors block: sig, no usable strings [V]
- FrameGraph::taskDispatch 0xe9002e0 — Sigs.json sig [V]; dossier anchors block: sig, no strings [V]
- FrameGraph::viewSetupTask 0x568cd90 — Sigs.json sig [V]; dossier anchors block WAS EMPTY — filled in this unit (below) [V]
- D3D12Context::drawExecutor 0xe821120 — Sigs.json sig [V]; dossier anchors block: sig [V]
- D3D12Context::psoBuilder 0xe81e860 — Sigs.json sig [V]; dossier anchors block: strings "TEXCOORD" + sig [V]
- D3D12Context::drawFlush 0xe81b720 — Sigs.json sig [V]; dossier anchors block: sig + behaviour anchor [V]

## Pending part closed here: viewSetupTask 0x568cd90
The 331-instruction body has no string reference (no [rip] lea in the full listing) and no __FUNCSIG__ [V; listing checked]. Its version-stable anchors are therefore (a) the unique prologue sig, verified byte-for-byte against the exe at 0x568cd90, and (b) the view-record field offsets it stores through s_ctx = [0x12AE1748], matching BGFX_MAP 6dd (per-view rect, 4 mat4, sortMode byte at +0x122). No in-game/live check is needed for an anchor; static [V] suffices. Sigs.json `FrameGraph::viewSetupTask` already carries the same sig (docs/data/function_anchors.tsv row 0x568cd90 prefix/window agree).

## Proof table (verbatim `0xRVA  instr` lines copied from the exe disassembly; one row per distinct offset)
| offset | size | read/store address | instr | meaning |
| 0x568cd90 | 1 | - | `0x568cd90  push rbp` | unique-sig head [V] |
| 0x568cd9c | 4 | - | `0x568cd9c  sub rsp,0x1D8` | stack frame 0x1D8 = dossier stack frame [V] |
| 0x568cdab | 16 | - | `0x568cdab  movdqa [rbp+0x140],xmm6` | unique-sig tail (66 0F 7F B5 40 ...) [V] |
| 0x568cdf6 | 4 | [0x12AE1748]+view*0x50+0x1EAB090 | `0x568cdf6  movd [rcx+r13+0x1EAB090],xmm0` | view rect lo write [V] |
| 0x568ce0c | 4 | [0x12AE1748]+view*0x50+0x1EAB094 | `0x568ce0c  movd [rcx+r13+0x1EAB094],xmm1` | view rect hi write [V] |
| 0x568ce44 | - | - | `0x568ce44  add rcx,0x1EAB0A0` | view matrix-1 anchor [V] |
| 0x568ce5a | - | - | `0x568ce5a  add rcx,0x1EAB0E0` | view matrix-2 anchor [V] |
| 0x568ce73 | - | - | `0x568ce73  add rcx,0x1EAB120` | view matrix-3 anchor [V] |
| 0x568ce8c | - | - | `0x568ce8c  add rcx,0x1EAB160` | view matrix-4 anchor [V] |
| 0x568cea5 | - | - | `0x568cea5  add rcx,0x1EAB1A0` | view sortMode-area anchor [V] |
| 0x568cecc | 1 | [0x12AE1748]+view*0x50+0x1EAB1B2 | `0x568cecc  mov [rcx+r13+0x1EAB1B2],al` | view byte flag at +0x122 [V] |

Sig recorded beside the RVA (matches Sigs.json `FrameGraph::viewSetupTask` and the exe at 0x568cd90) [V]:
`55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC D8 01 00 00 48 8D AC 24 ?? ?? ?? ?? 66 0F 7F B5 40`

## Dossier update
docs/functions/568cd90.md anchors block filled with the sig above, "no strings / no __FUNCSIG__" and the eight view-record offsets (rect lo/hi, 4 matrices, byte flag), each tagged [V] with the quoted lines above.

## CLOSES?
YES — every function on the M4a line now has a version-stable anchor recorded beside its RVA: a Sigs.json entry (sig + comment RVA) and a dossier anchors block for all ten (Encoder submit/reset/frameSort, FrameGraph endFrame/generate/taskDispatch/viewSetupTask, D3D12Context drawExecutor/psoBuilder/drawFlush); the last empty block (viewSetupTask) was filled in this unit with [V] verbatim proof. Nothing on the item line remains pending.
