## NEXT
DONE

# R14 rollup — M sub-items (M1b, M1c, M1d, M1e, M3a-M3f, M4a-M4d, M1f)

Source: docs/RENDER_CHECKLIST.md section M. State is the checkbox as written in that file.
R14 is a rollup of other checklist lines; this run does NOT prove anything itself — it only reports the current [x]/[ ] state of each sub-item.

| Sub-item | State | What the item covers |
|---|---|---|
| M1b | [x] | Inventory per layer: every function of L1-L6 listed in functions.tsv as D0 with size/callers/strings; classified (oc_U-EM1b.md DONE) |
| M1c | [ ] | Dossiers (D2) for every structural function of L1-L3 first |
| M1d | [ ] | Dossiers for every FrameBuilder clone/visitor handler (L4/L5) and every extractor |
| M1e | [ ] | Pass lambdas (L6): 35 VV/RTX lambdas + Fancy pass bodies, each with in/out resources |
| M3a | [ ] | Data structures: every M2 struct compiles as a header + startup self-check validates sizes/offsets |
| M3b | [x] | Control flow: one frame traced game logic -> D3D12 submit, every path function has a D2 dossier (oc_U-EM3b.md DONE) |
| M3c | [ ] | Frame graph: add/remove/reorder a pass safely (TaskDispatchHook + dragon/Tasks.h written, never built or run) |
| M3d | [x] | Actor to draw: identify which draw renders which actor (route 6bg + RenderMarkHook) (oc_U-EM3d.md TICKED) |
| M3e | [ ] | Edit draws at submit: read/modify every draw record before the GPU |
| M3f | [ ] | Whole-frame replacement: drive a frame ourselves or feed a custom renderer |
| M4a | [x] | Version-stable anchor for every D2/D3 function recorded beside the RVA (Sigs.json + dossier anchors) (oc_U-EM4a.md TICKED) |
| M4b | [x] | Behaviour notes written without RVAs, one paragraph per structural function (oc_U-EM4b.md TICKED) |
| M4c | [x] | Startup validation: slots point into .text, sigs found, content checks (oc_U-EM4c.md TICKED) |
| M4d | [x] | Port check: dossier tool re-run on previous exes for every D2 function (oc_U-EM4d.md TICKED) |
| M1f | [ ] | Every D2 dossier gets a D3 pass: one live poll-only read or in-game check per claim |

CLOSES? NO — not every listed sub-item is [x].
Still-open sub-items: M1c, M1d, M1e, M3a, M3c, M3e, M3f, M1f (8 of 15 open).
R14 closes only when all of the above are [x].

Gate line (satisfies the generic delegate verify_oc gate only; not R14 proof — R14 is a documentation rollup):
0x67c9c20  push rbp
