## NEXT
DONE (step 2 complete: rollup table written; CLOSES? NO)

# U-ER14 — R14 rollup table

R14 is a rollup of other checklist lines: M1b, M1c, M1d, M1e, M3a-M3f, M4a-M4d, M1f.
State below is copied verbatim from the checkbox in docs/RENDER_CHECKLIST.md ([x] = ticked, [ ] = open).
This is a table-only rollup: no disassembly was done for it; each sub-item's own line/progress note is the source of truth.

| Sub-item | Checklist state | Wording (shortened from docs/RENDER_CHECKLIST.md) |
|---|---|---|
| M1b | [x] | Inventory per layer: list EVERY function of each region into functions.tsv as D0, then classify (structural / helper / lambda / thunk) |
| M1c | [ ] | Dossiers (D2) for every structural function of L1-L3 first: Context::init/frame, Encoder::submit family, Frame::sort, submit 0xe82e230, executor 0xe821120 + wrapper, PSO builder, endFrame 0xc270460, generate 0xc273420, GraphicsTasks Render/Execute, dispatch 0xe9002e0, the five task bodies |
| M1d | [ ] | Dossiers for every FrameBuilder clone and visitor handler (L4/L5) and every extractor (chunk, batch actor, item-in-hand, skinned, nametag, particle, sky) |
| M1e | [ ] | Pass lambdas (L6): the 35 VV/RTX lambdas + Fancy pass bodies, each with in/out resources |
| M3a | [ ] | Data structures: every struct of M2 compiles as a header and a startup self-check validates sizes/offsets (static_asserts + SelfTest) |
| M3b | [x] | Control flow: one frame traced from game logic to D3D12 submit with every function on the path having a D2 dossier |
| M3c | [ ] | Frame graph: add/remove/reorder a pass safely (recipe 6dg/6dy, TaskDispatchHook + dragon/Tasks.h written but never built or run) |
| M3d | [x] | Actor to draw: identify which draw renders which actor (route 6bg + RenderMarkHook; re-validate on 1.26.62.01 against flush 0xe81b720 and Encoder::submit seam) |
| M3e | [ ] | Edit draws at submit: read/modify every draw record before the GPU (flush 0xe81b720 records; header-to-record mapping + in-game test) |
| M3f | [ ] | Whole-frame replacement: drive a frame ourselves or feed a custom renderer (needs M1c-M3e) |
| M4a | [x] | For every D2/D3 function record the version-stable anchor (string / __FUNCSIG__ / unique sig) beside the RVA (Sigs.json + dossier anchors block) |
| M4b | [x] | Behaviour notes written without RVAs so they survive a patch (one paragraph per structural function in its dossier) |
| M4c | [x] | Startup validation: slots point into .text, sigs found, content checks (mask immediates, offset refs) |
| M4d | [x] | Port check: re-run the dossier tool on the previous version's exe for every D2 function to measure RVA/offset/slot movement |
| M1f | [x] | Every D2 dossier gets a D3 pass: one live poll-only read or in-game check per claim that can be checked |

CLOSES? NO — not every listed sub-item is [x]. Still-open sub-items: M1c, M1d, M1e, M3a, M3c, M3e, M3f.

## Check anchor (verify_oc gate only; not disassembly work for this rollup)
0xbc63690  push rsi
