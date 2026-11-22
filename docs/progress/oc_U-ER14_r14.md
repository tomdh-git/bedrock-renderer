## NEXT
DONE

# Unit U-ER14 — R14 rollup table

Source: docs/RENDER_CHECKLIST.md section M ("M. Full-RE method: function dossiers, acceptance tests, definition of done").
Rollup scope per the R14 item line: M1b, M1c, M1d, M1e, M3a, M3b, M3c, M3d, M3e, M3f, M4a, M4b, M4c, M4d, M1f.

Checkbox state read verbatim from docs/RENDER_CHECKLIST.md section M:

| Sub-item | Box | Evidence (verbatim status from docs/RENDER_CHECKLIST.md section M) |
|---|---|---|
| M1b | [x] | DONE 2026-11-22 oc_U-EM1b.md (verify_oc 8/8): all 15113 functions of L1..L6 are D0+ rows in docs/data/functions.tsv; size, callers, strings and the class column are joined per RVA in docs/data/functions_full.tsv |
| M1c | [ ] | Dossiers (D2) for every structural function of L1-L3 first: Context::init/frame, Encoder::submit family, Frame::sort, submit 0xe82e230, executor 0xe821120 + wrapper, PSO builder, endFrame 0xc270460, generate 0xc273420, GraphicsTasks Render/Execute, dispatch 0xe9002e0, five task bodies — line carries PROGRESS notes, box unchecked |
| M1d | [ ] | Dossiers for every FrameBuilder clone and visitor handler (L4/L5) and every extractor (chunk, batch actor, item-in-hand, skinned, nametag, particle, sky) — PROGRESS lists partial work, box unchecked |
| M1e | [ ] | Pass lambdas (L6): 35 VV/RTX lambdas + Fancy pass bodies, each with in/out resources — non-ScreenDraw pass bodies and per-pass in/out remaining, box unchecked |
| M1f | [ ] | Every D2 dossier gets a D3 pass: one live poll-only read or in-game check per claim — PARTIAL = NOT DONE |
| M3a | [ ] | Data structures: every struct of M2 compiles as a header and a startup self-check validates sizes/fields (static_asserts + SelfTest) — box unchecked |
| M3b | [x] | DONE 2026-11-22 oc_U-EM3b.md (verify_oc 24/24): docs/FRAME_CALLGRAPH.md thread A + B tables with args per hop; every row function has a D2 dossier; no [?] links left in the table |
| M3c | [ ] | Frame graph: add/remove/reorder a pass safely (recipe 6dg/6dy, TaskDispatchHook + dragon/Tasks.h written but never built or run; needs the build + in-game test) |
| M3d | [x] | TICKED 2026-11-21 oc_U-EM3d.md (verify_oc 67/67): actor read (S+0xC8) 0x66d313d, pass/item push 0x5aba5e0, Encoder::submit seam and flush 0xe81b720 re-validated; record+0x80 startInstance = roster slot -> actor; RenderMarkHook exists but is not registered |
| M3e | [ ] | Edit draws at submit: read/modify every draw record before the GPU (flush 0xe81b720 records 6ej; needs header-to-record mapping and in-game test) |
| M3f | [ ] | Whole-frame replacement: drive a frame ourselves or feed a custom renderer (needs M1c-M3e) — custom item seam found (key bit 53), untested in game, ctx layout partly inferred |
| M4a | [x] | TICKED 2026-11-21 oc_U-EM4a.md (verify_oc 11/11): all ten anchors in Sigs.json + dossier anchors blocks; rdis find on every sig: 1 hit each |
| M4b | [x] | TICKED 2026-11-21 oc_U-EM4b.md (verify_oc 9/9): one behaviour paragraph per structural function with a D2 dossier in docs/BEHAVIOR_NOTES.md |
| M4c | [x] | TICKED 2026-11-21 mirror of N4b + O3b: startup validation content checks pass (layoutcheck 199/0; both lists identical on 62.01 and 60.05) |
| M4d | [x] | TICKED 2026-11-21 oc_U-EO3c.md (verify_oc 130/130): dossier tool re-run on 50.04/51.01/60.05 for all 130 D2 functions |

CLOSES? NO — not every listed sub-item is [x].
Still-open sub-items: M1c, M1d, M1e, M1f, M3a, M3c, M3e, M3f (8 open).
Closed sub-items: M1b, M3b, M3d, M4a, M4b, M4c, M4d (7 closed).

## Anchor instructions cited (verbatim from rdis output)
  0xe81b720  push r15
  0x67c9c20  push rbp
Anchor citations: 0xe81b720 = DrawBatcher flush 0xe81b720 (cited by M3d/M3e); 0x67c9c20 = Fancy frame renderer entry 0x67c9c20 (cited by M3b).

## TOOL REQUESTS
None
