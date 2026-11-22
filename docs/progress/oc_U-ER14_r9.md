## NEXT
DONE

# R14 rollup — sub-item states from docs/RENDER_CHECKLIST.md (section M)

R14 rolls up: M1b, M1c, M1d, M1e, M1f, M3a-M3f, M4a-M4d.

| Sub-item | State | Evidence / notes |
|---|---|---|
| M1b | [x] | Inventory per layer: all 15113 functions of L1..L6 are D0+ rows in docs/data/functions.tsv; size, callers, strings and class column joined in docs/data/functions_full.tsv. DONE 2026-11-22 oc_U-EM1b.md (verify_oc 8/8). |
| M1c | [ ] | D2 dossiers for every structural function of L1-L3 first: done for submit, draw flush, executor, PSO builder, submit 0xe82e230, Frame::sort, endFrame, Context::frame, dispatch 0xe9002e0, init 0xbc63690, handoff 0xbc65800, Execute 0xc25fc50, renderFrame 0xbc63150, thread proc 0xbc65720; NOT complete for all structural functions — gaps remain. |
| M1d | [ ] | Dossiers for every FrameBuilder clone/visitor handler (L4/L5) and every extractor: ItemInHand extractor 0x6698e30 D1+, BatchActor extractor 0x66d9af0 D1+, thin insert clones D1+, Nametag fat clone 0x1127330 D1+, PlayerVision/Shadow/MeshFallback/Crack/Clouds/SkinnedMesh/EnvironmentalText/UIText/BlockSelectionOverlay/Sky constructors D1+, visitor cases mapped; chunk/nametag/particle/sky extractors and other visitors still open. |
| M1e | [ ] | Pass lambdas (L6): 35 VV/RTX lambdas + Fancy pass bodies with in/out resources. VV pass-group builder table and ScreenDraw path mapped; non-ScreenDraw pass bodies (deferred, SSR, TAAU, RTX, voxel) and their resources still open. |
| M1f | [ ] | Every D2 dossier gets a D3 pass: PARTIAL = NOT DONE. First two D3 passes done (frame pair spacing 0xE749C0, counters, backbuffer 1920x1137, 514 items, draw header fields); remaining D2 claims not polled. |
| M3a | [ ] | Data structures: every struct of M2 compiles as a header + startup self-check validates sizes/offsets (static_asserts + SelfTest): NOT built into DLL, not run in game. |
| M3b | [x] | Control flow: one frame traced game logic to D3D12 submit with D2 dossier per function; docs/FRAME_CALLGRAPH.md thread A+B tables with args per hop; no [?] links. DONE 2026-11-22 oc_U-EM3b.md (verify_oc 24/24). |
| M3c | [ ] | Frame graph: add/remove/reorder a pass safely: recipe 6dg/6dy written (TaskDispatchHook + dragon/Tasks.h) but never built or run; needs build + in-game test. |
| M3d | [x] | Actor to draw: identify which draw renders which actor; re-validated on 1.26.62.01 against flush 0xe81b720 and Encoder::submit seam; record+0x80 startInstance = roster slot -> actor. DONE 2026-11-21 oc_U-EM3d.md (verify_oc 67/67). |
| M3e | [ ] | Edit draws at submit: read/modify every draw record before the GPU (flush 0xe81b720 records); needs header-to-record mapping and in-game test. |
| M3f | [ ] | Whole-frame replacement: custom item seam found (Encoder::submitCustom, key bit 53) but untested in game; ctx layout partly inferred. |
| M4a | [x] | Version-stable anchors recorded beside every D2/D3 function RVA (Sigs.json + dossier anchors blocks); all ten anchors re-checked, 1 hit each. DONE 2026-11-21 oc_U-EM4a.md (verify_oc 11/11). |
| M4b | [x] | Behaviour notes without RVAs for every structural function with a D2 dossier (docs/BEHAVIOR_NOTES.md); RVAs only as bracket index tags. DONE 2026-11-21 oc_U-EM4b.md (verify_oc 9/9). |
| M4c | [x] | Startup validation: slots point into .text, sigs found, content checks (mask immediates, offset refs); layoutcheck 199 assertions 0 failed; mirrors N4b/O3b. DONE 2026-11-21. |
| M4d | [x] | Port check: dossier tool re-run on 50.04/51.01/60.05 for all 130 D2 functions; results in docs/data/port_check_dossier_results.json + port_check_*.tsv. DONE 2026-11-21 oc_U-EO3c.md (verify_oc 130/130). |

CLOSES? NO — still-open sub-items: M1c, M1d, M1e, M1f, M3a, M3c, M3e, M3f.
Closed sub-items: M1b, M3b, M3d, M4a, M4b, M4c, M4d.

Verification anchor (already-verified M1b data, no new disassembly):
0xbc60740  push r15

## TOOL REQUESTS
None
