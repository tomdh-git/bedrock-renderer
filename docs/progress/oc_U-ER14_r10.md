## NEXT
DONE

R14 rollup of M1b, M1c, M1d, M1e, M3a-M3f, M4a-M4d, M1f. States read from docs/RENDER_CHECKLIST.md section M (M1 lines 439-443, M3 lines 453-458, M4 lines 461-464); no new disassembly in this run.

| item | state | note |
| M1b | [x] | DONE 2026-11-22 oc_U-EM1b.md (verify_oc 8/8): 15113 L1..L6 functions D0+ in functions.tsv, class column joined in functions_full.tsv |
| M1c | [ ] | open: L1-L3 structural D2 dossiers incomplete |
| M1d | [ ] | open: FrameBuilder clone/visitor + extractor D2 dossiers incomplete |
| M1e | [ ] | open: L6 VV/RTX pass lambdas + per-pass in/out resources incomplete |
| M3a | [ ] | open: startup self-check/static_asserts not done |
| M3b | [x] | DONE 2026-11-22 oc_U-EM3b.md (verify_oc 24/24): docs/FRAME_CALLGRAPH.md threads A+B, no [?] links; anchor `0xe81b720  push r15` [V] |
| M3c | [ ] | open: TaskDispatchHook + dragon/Tasks.h written, never built or run |
| M3d | [x] | TICKED 2026-11-21 oc_U-EM3d.md (verify_oc 67/67); actor-to-draw route re-validated, hook exists but is not registered |
| M3e | [ ] | open: edit draws at submit needs header-to-record mapping + in-game test |
| M3f | [ ] | open: whole-frame replacement untested in game, custom-item ctx layout partly inferred |
| M4a | [x] | TICKED 2026-11-21 oc_U-EM4a.md (verify_oc 11/11): ten anchors in Sigs.json + dossier anchors blocks |
| M4b | [x] | TICKED 2026-11-21 oc_U-EM4b.md (verify_oc 9/9): one behavior paragraph per D2 structural function in BEHAVIOR_NOTES.md |
| M4c | [x] | TICKED 2026-11-21: layoutcheck 199 assertions, 0 failed; layout_asserts.json and RenderLayoutAsserts.h identical |
| M4d | [x] | TICKED 2026-11-21 oc_U-EO3c.md (verify_oc 130/130): dossier tool re-run on 50.04/51.01/60.05 for all 130 D2 functions |
| M1f | [ ] | open: PARTIAL = NOT DONE; only the first two D3 passes done, every other D2 claim remains |

CLOSES? NO — still-open sub-items: M1c, M1d, M1e, M3a, M3c, M3e, M3f, M1f. Done sub-items: M1b, M3b, M3d, M4a, M4b, M4c, M4d.

Anchor for the delegate check (already-D2 dossier entry, not new disassembly): `0xe81b720  push r15` [V]
