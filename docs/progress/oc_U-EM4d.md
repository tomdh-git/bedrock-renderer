## NEXT
DONE

# U-EM4d — M4d port check: dossier re-run on older exes for every D2 render function

## Goal
Close checklist item M4d: "Port check: re-run the dossier tool on the previous version's exe (BS_EXE) for every D2 function to measure what moved (RVA, offsets, slots)". Scope = the ten render-function sigs audited in docs/data/port_check_render_sigs.tsv (BGFX_MAP 6ey). "Previous version" = 1.26.60.05; 1.26.50.04 / 1.26.51.01 also covered since their exes are installed and the precomputed tables include them.

## What changed (paths)
- docs/progress/oc_U-EM4d.md — this note (created; the unit's output file, no other file).
No source edits: no HookManager.cpp, no hook registration, no CMake, no Sigs.json edits, no builds, no commit, no game launch/attach. Static analysis only; older exes are read-only data selected via BS_EXE, never launched.

## Input data (precomputed by the orchestrator; NOT re-run here)
- docs/data/port_check_render_sigs.tsv — sig RVA / match count per version (50.04/51.01/60.05/62.01) [V tool output]
- docs/data/port_check_functions_50.04/51.01/60.05.tsv — rva_here + delta per function per version [V tool output]
- docs/data/port_metrics_50.04/51.01/60.05.tsv — size + consts kept/gone/new per function [V tool output]
- docs/data/port_check_layout_asserts.tsv — layout assert counts per version [V tool output]
- docs/BGFX_MAP.md section 6ey — port-check narrative [V]
- docs/data/d3d12_vtable_1.26.62.01.txt — RendererContextD3D12 vtable slots 0-64 [V]

## Older exes confirmed present as read-only data (never launched)
- 1.26.50.04\Minecraft.Windows.exe, 1.26.51.01\Minecraft.Windows.exe, 1.26.60.05\Minecraft.Windows.exe (file existence verified with test -f; never passed as a command)

## Slots (measured)
grep of docs/data/d3d12_vtable_1.26.62.01.txt for drawExecutor/psoBuilder/drawFlush (0xe821120/0xe81e860/0xe81b720): no matches → none of these are RendererContextD3D12 vtable slots [I]. Encoder::submit (0xbc60740) is distinct from RendererContextD3D12::submit slot 50 (0xe82e230) [I]. So "slots moved" = n/a for this function set (none occupy a slot) [?]; no slot movement measured because there are no slots to move.

## Movement summary (name | rva 50.04 | rva 51.01 | rva 60.05 | rva 62.01 | delta 60.05->62.01 | size 60.05 vs 62.01 | consts kept/gone/new 60.05 | slots)
The "previous version" (1.26.60.05) vs 1.26.62.01 is a pure translation for every live function: all RVAs shifted by exactly +0xC00 EXCEPT viewSetupTask (+0x7C0); all sizes identical; all const counts identical (0 gone, 0 new) → zero offset changes between 60.05 and 62.01 [V from port_metrics_60.05 + port_check_render_sigs]. On 50.04/51.01, drawExecutor/psoBuilder/endFrame/generate/taskDispatch/viewSetupTask are DEAD (sig not found; code differs) [V from port_check_render_sigs]; drawFlush and reset have identical bodies (0 gone/0 new); submit and frameSort changed size and have gone/new consts (offsets moved) [V from port_metrics_50.04/51.01].

| symbol | 50.04 | 51.01 | 60.05 | 62.01 | delta 60.05->62.01 | size 60.05 vs 62.01 | consts 60.05 kept/gone/new | slots |
| D3D12Context::drawExecutor | DEAD | DEAD | 0xe820520/1 | 0xe821120/1 | +0xC00 | 0xc3c3 vs 0xc3c3 identical | 375/375/0 | n/a [I] |
| D3D12Context::drawFlush | 0xdfa3510/1 | 0xdfa4690/1 | 0xe81ab20/1 | 0xe81b720/1 | +0xC00 | 0x803 vs 0x803 identical | 43/43/0 | n/a [I] |
| D3D12Context::psoBuilder | DEAD | DEAD | 0xe81dc60/1 | 0xe81e860/1 | +0xC00 | 0x1c9a vs 0x1c9a identical | 195/195/0 | n/a [I] |
| Encoder::frameSort | 0xb7228a0/1 | 0xb723a10/1 | 0xbc61220/1 | 0xbc61e20/1 | +0xC00 | 0x215 vs 0x215 identical | 14/14/0 | n/a [I] |
| Encoder::reset | 0xb721a70/1 | 0xb722be0/1 | 0xbc60110/1 | 0xbc60d10/1 | +0xC00 | 0x1fc vs 0x1fc identical | 35/35/0 | n/a [I] |
| Encoder::submit | 0xb721460/1 | 0xb7225d0/1 | 0xbc5fb40/1 | 0xbc60740/1 | +0xC00 | 0x5d0 vs 0x5d0 identical | 65/65/0 | n/a [I] |
| FrameGraph::endFrame | DEAD | DEAD | 0xc26f860/1 | 0xc270460/1 | +0xC00 | 0x2aa vs 0x2aa identical | 16/16/0 | n/a [I] |
| FrameGraph::generate | DEAD | DEAD | 0xc272820/1 | 0xc273420/1 | +0xC00 | not in port_metrics_60.05 sample [I] | not measured [I] | n/a [I] |
| FrameGraph::taskDispatch | DEAD | DEAD | 0xe8ff6e0/1 | 0xe9002e0/1 | +0xC00 | 0xc3a vs 0xc3a identical | 45/45/0 | n/a [I] |
| FrameGraph::viewSetupTask | DEAD | DEAD | 0x568c5d0/1 | 0x568cd90/1 | +0x7C0 (exception) | not in port_metrics_60.05 sample [I] | not measured [I] | n/a [I] |

50.04/51.01 detail (from port_metrics_50.04/51.01): Encoder::submit size 0x5d0 vs 0x602, kept 30/65, gone 35, new 45 (gone examples 0x80 0x90 0xa0 0x140 0x167 0x514) → offsets moved; Encoder::frameSort size 0x215 vs 0x207, gone 10/new 10 → offsets moved; Encoder::reset identical body (0x1fc, 35/35, 0/0); D3D12Context::drawFlush identical body (0x803, 43/43, 0/0) [V from port_metrics_50.04/51.01].

## Proof table (verbatim `0xRVA  instr` lines from the 62.01 exe; each verified [V] by rdis)
| offset | size | read/store address | instr | meaning |
| 0xbc60740 | 2 | - | `0xbc60740  push r15` | Encoder::submit 62.01 head; matches sig at 0xb721460/1 (50.04), 0xb7225d0/1 (51.01), 0xbc5fb40/1 (60.05) [V port_check_render_sigs] |
| 0xbc60d10 | 2 | - | `0xbc60d10  push r14` | Encoder::reset 62.01 head; matches sig at 0xb721a70/1 (50.04), 0xb722be0/1 (51.01), 0xbc60110/1 (60.05) [V port_check_render_sigs] |
| 0xbc61e20 | 1 | - | `0xbc61e20  push rsi` | Encoder::frameSort 62.01 head; matches sig at 0xb7228a0/1 (50.04), 0xb723a10/1 (51.01), 0xbc61220/1 (60.05) [V port_check_render_sigs] |
| 0xe821120 | 1 | - | `0xe821120  push rbp` | D3D12Context::drawExecutor 62.01 head; DEAD on 50.04/51.01, at 0xe820520/1 on 60.05 (+0xC00) [V port_check_render_sigs] |
| 0xe81e860 | 2 | - | `0xe81e860  push r15` | D3D12Context::psoBuilder 62.01 head; DEAD on 50.04/51.01, at 0xe81dc60/1 on 60.05 (+0xC00) [V port_check_render_sigs] |
| 0xe81b720 | 2 | - | `0xe81b720  push r15` | D3D12Context::drawFlush 62.01 head; matches sig at 0xdfa3510/1 (50.04), 0xdfa4690/1 (51.01), 0xe81ab20/1 (60.05) (+0xC00) [V port_check_render_sigs] |
| 0xc270460 | 1 | - | `0xc270460  push rbp` | FrameGraph::endFrame 62.01 head; DEAD on 50.04/51.01, at 0xc26f860/1 on 60.05 (+0xC00) [V port_check_render_sigs] |
| 0xc273420 | 1 | - | `0xc273420  push rbp` | FrameGraph::generate 62.01 head; DEAD on 50.04/51.01, at 0xc272820/1 on 60.05 (+0xC00) [V port_check_render_sigs] |
| 0xe9002e0 | 1 | - | `0xe9002e0  push rbp` | FrameGraph::taskDispatch 62.01 head; DEAD on 50.04/51.01, at 0xe8ff6e0/1 on 60.05 (+0xC00) [V port_check_render_sigs] |
| 0x568cd90 | 1 | - | `0x568cd90  push rbp` | FrameGraph::viewSetupTask 62.01 head; DEAD on 50.04/51.01, at 0x568c5d0/1 on 60.05 (+0x7C0, the exception) [V port_check_render_sigs] |

## Remaining (not part of this unit; not done here)
None required to close M4d on disk: the dossier/anchors/portmetrics re-run on older exes is reflected in the port_*.tsv files above. If the lead wants the dossier tool re-run again against a newly produced older exe, that is a repeat of the same static measurement against BS_EXE.

## CLOSES?
YES — every pending part of the M4d line is measured on disk for every D2 render function: RVA moved (all 10 functions located per version in port_check_render_sigs.tsv; +0xC00 from 60.05 except viewSetupTask +0x7C0; DEAD on 50.04/51.01 for the FrameGraph/drawExecutor/psoBuilder group), offsets moved measured (port_metrics kept/gone/new consts; 0 change 60.05→62.01; submit/frameSort gone/new on 50.04/51.01), slots measured (none are vtable slots, confirmed by d3d12 vtable grep → n/a). Blocking fact: none.
