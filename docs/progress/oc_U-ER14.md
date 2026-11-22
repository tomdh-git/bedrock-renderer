## NEXT
DONE — table written; CLOSES? NO (still-open sub-items: M1c, M1d, M1e, M3a, M3c, M3e, M3f)

# R14 rollup — sub-item states

R14 is a rollup of other checklist lines (M1b, M1c, M1d, M1e, M3a-M3f, M4a-M4d, M1f).
Source: docs/RENDER_CHECKLIST.md section M, item text:

`- [ ] R14 M1b classification, M1c/M1d/M1e dossier gaps, M3a-M3f, M4a-M4d, M1f (see their own lines)` — the R14 box itself is `[ ]`.

Per checklist rule, only the `[x]`/`[ ]` box state counts (progress notes inside an item never change its box). No disassembly in this run; states are copied verbatim from the checklist boxes.

| Sub-item | Checklist box | Checklist line (section M) |
|---|---|---|
| M1b | [x] | Inventory per layer: list EVERY function of each region (L1 bgfx core ~290, L2 D3D12 ~1,900, L3 RenderDragon ~980, L4/L5 BgfxFrameBuilder ~2,300, L6 frame-graph renderers ~3,600) into functions.tsv as D0 with size, callers, strings; then classify (structural / helper / lambda / thunk) |
| M1c | [ ] | Dossiers (D2) for every structural function of L1-L3 first: Context::init/frame, Encoder::submit family, Frame::sort, submit 0xe82e230, executor 0xe821120 + wrapper, PSO builder, endFrame 0xc270460, generate 0xc273420, GraphicsTasks Render/Execute, dispatch 0xe9002e0, the five task bodies |
| M1d | [ ] | Dossiers for every FrameBuilder clone and visitor handler (L4/L5) and every extractor (chunk, batch actor, item-in-hand, skinned, nametag, particle, sky) |
| M1e | [ ] | Pass lambdas (L6): the 35 VV/RTX lambdas + Fancy pass bodies, each with in/out resources |
| M1f | [x] | Every D2 dossier gets a D3 pass: one live poll-only read or in-game check per claim that can be checked |
| M3a | [ ] | Data structures: every struct of M2 compiles as a header and a startup self-check validates sizes/offsets that can be validated (static_asserts + SelfTest) |
| M3b | [x] | Control flow: one frame traced from game logic to D3D12 submit with every function on the path having a D2 dossier (pipeline diagram as call-graph table with arguments at each hop) |
| M3c | [ ] | Frame graph: add/remove/reorder a pass safely (recipe 6dg/6dy, TaskDispatchHook + dragon/Tasks.h written but never built or run; needs the build + in-game test) |
| M3d | [x] | Actor to draw: identify which draw renders which actor (route 6bg + RenderMarkHook exists; re-validate on 1.26.62.01 against flush 0xe81b720 and Encoder::submit seam) |
| M3e | [ ] | Edit draws at submit: read/modify every draw record before the GPU (flush 0xe81b720 records; needs header-to-record mapping and in-game test) |
| M3f | [ ] | Whole-frame replacement: drive a frame ourselves or feed a custom renderer (needs M1c-M3e) |
| M4a | [x] | For every D2/D3 function record the version-stable anchor (string / __FUNCSIG__ / unique sig) beside the RVA (Sigs.json + dossier "anchors" block) |
| M4b | [x] | Behaviour notes written without RVAs (what the function does) so they survive a patch: one paragraph per structural function in its dossier |
| M4c | [x] | Startup validation: slots point into .text, sigs found, content checks (mask immediates, offset refs) |
| M4d | [x] | Port check: re-run the dossier tool on the previous version's exe (BS_EXE) for every D2 function to measure what moved (RVA, offsets, slots) |

CLOSES? NO — still-open sub-items: M1c, M1d, M1e, M3a, M3c, M3e, M3f

## Verified instruction lines (tooling evidence only; not rollup proof — no disassembly done in this run)
`0xe82e26c  mov [rbp+0x16A8],rdx`   [V] rdis dis 0xe82e26c (submit prologue stores rdx to [rbp+0x16A8]; K-P6 / M1c region)
`0x53365fa  mov [rax+0x63],bl`      [V] rdis dis 0x53365fa (draw-record depth byte write; H1b)
`0x2b632c  mov [rcx+0xCD8],rax`     [V] rdis dis 0x2b632c (owner ctor high-water store; C4b/L3f)
`0xe7f5452  lea rcx,[r12+0x2035F0]` [V] rdis dis 0xe7f5452 (ctx+0x2035F0 address load; H2)

## NEXT
step 3: none — R14 cannot close until M1c, M1d, M1e, M3a, M3c, M3e and M3f are each ticked [x] in docs/RENDER_CHECKLIST.md (that is the orchestrator's/checklist's decision, not something this unit proves). No further action in this run; one table only, no disassembly.
