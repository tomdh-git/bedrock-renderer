## NEXT
DONE

# R14 rollup — sub-item states from docs/RENDER_CHECKLIST.md (section M)

R14 line (docs/RENDER_CHECKLIST.md, last line of section R):
"- [ ] R14 M1b classification, M1c/M1d/M1e dossier gaps, M3a-M3f, M4a-M4d, M1f (see their own lines)"

Each sub-item below is listed with its current [x]/[ ] state exactly as written in docs/RENDER_CHECKLIST.md, plus the status note on that checklist line. No disassembly was done for this rollup; the only quoted instruction lines are copies of RVAs already established on those checklist lines, included so the file's inline quotes verify.

| Sub-item | State | Status note from docs/RENDER_CHECKLIST.md |
|---|---|---|
| M1b | [x] | DONE 2026-11-22 oc_U-EM1b.md (verify_oc 8/8): all 15113 functions of L1..L6 are D0+ rows in docs/data/functions.tsv; size, callers, strings and class column joined in docs/data/functions_full.tsv (15113 rows) |
| M1c | [ ] | PROGRESS: D2 dossiers done for submit, draw flush, executor, PSO builder, submit 0xe82e230, Frame::sort, endFrame, Context::frame 0xbc66de0, dispatch 0xe9002e0, init 0xbc63690, handoff 0xbc65800, Execute 0xc25fc50, renderFrame 0xbc63150, thread proc 0xbc65720; L4/L5 dossiers still open |
| M1d | [ ] | PROGRESS: ItemInHand extractor 0x6698e30 dossier started (D1+); BatchActor extractor 0x66d9af0 dossier (D1+, layouts live-verified); clones, visitors and the other extractors (chunk, skinned, nametag, particle, sky) not yet D2 |
| M1e | [ ] | PROGRESS (6gz): VV pass-group builder table done; ScreenDraw path fully mapped; remaining: non-ScreenDraw pass bodies (deferred, SSR, TAAU, RTX, voxel) and their per-pass in/out resources |
| M3a | [ ] | Not started: every struct of M2 compiles as a header and a startup self-check validates sizes/offsets (static_asserts + SelfTest) |
| M3b | [x] | DONE 2026-11-22 oc_U-EM3b.md (verify_oc 24/24): docs/FRAME_CALLGRAPH.md threads A+B with args per hop; every row function has a D2 dossier (A5 `0x67C9C20  push rbp`, A7 0xc273420, B3 0xbc68840, item visitor tag bodies 0x6646a10..); no [?] links left in the table |
| M3c | [ ] | Not started: add/remove/reorder a pass safely (recipe 6dg/6dy; TaskDispatchHook + dragon/Tasks.h written, never built or run; needs build + in-game test) |
| M3d | [x] | TICKED 2026-11-21 oc_U-EM3d.md (verify_oc 67/67): actor read `0x66D313D  mov rax,[rax+0xC8]` (S+0xC8), pass/item push 0x5aba5e0, flush `0xE81B720  push r15` (0xe81b720), record+0x80 startInstance = roster slot -> actor at 0xe81b87a; RenderMarkHook exists but is not registered |
| M3e | [ ] | Not started: edit draws at submit — read/modify every draw record before the GPU (flush 0xe81b720 records 6ej; needs header-to-record mapping and an in-game test) |
| M3f | [ ] | PROGRESS (6fg/6fh): custom item seam found (Encoder::submitCustom(view, fn, user), sort-key bit 53 `0xBC61697  mov rcx,0x20000000000000`); untested in game, ctx layout partly inferred |
| M4a | [x] | TICKED 2026-11-21 oc_U-EM4a.md (verify_oc 11/11): all ten version-stable anchors in Sigs.json + dossier anchors blocks; orchestrator re-ran rdis find on every sig: 1 hit each |
| M4b | [x] | TICKED 2026-11-21 oc_U-EM4b.md (verify_oc 9/9): docs/BEHAVIOR_NOTES.md now has one behaviour paragraph per structural function that has a D2 dossier, incl. M1d/M1e items; RVAs only as bracket index tags |
| M4c | [x] | TICKED 2026-11-21 mirror of N4b (oc_U-EN4b.md) + O3b (oc_U-EO3b.md): slots/sigs/content checks pass; layoutcheck 199 assertions, 0 failed; both assertion lists identical |
| M4d | [x] | TICKED 2026-11-21 oc_U-EO3c.md (verify_oc 130/130): dossier tool re-run on 50.04/51.01/60.05 for all 130 D2 functions; results in docs/data/port_check_dossier_results.json + port_check_*.tsv |
| M1f | [x] | DONE 2026-11-22 oc_U-EM1f_r10.md (verify_oc 6/6): every D2 dossier has a live poll-only row (docs/data/live/); NOTE the line's own tail says "PARTIAL = NOT DONE." — the box is [x] (consistent with M's 13 done / 8 open count), contradiction noted, not counted as a new gap |

CLOSES? NO — still-open sub-items: M1c, M1d, M1e, M3a, M3c, M3e, M3f (7 of 15). Done on their boxes: M1b, M3b, M3d, M4a, M4b, M4c, M4d, M1f.

## TOOL REQUESTS
None
