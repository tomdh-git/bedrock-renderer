## NEXT
DONE

# Unit U-ER14 — Close checklist item R14

## Source item (docs/RENDER_CHECKLIST.md section R, last line)
`- [ ] R14 M1b classification, M1c/M1d/M1e dossier gaps, M3a-M3f, M4a-M4d, M1f (see their own lines)`
R14 references its sub-lines in section M ("M. Full-RE method: function dossiers, acceptance tests, definition of done"). This unit closes only what is provable here: re-verify each sub-line's anchor RVAs in the 1.26.62.01 exe (verbatim first instruction via rdis), record each sub-line's state from the checklist STATUS block (auto-updated, last update 2026-11-22), and close what is closed. Static analysis only per OPENCODE_BRIEF.md rules 1-2: no build, no game launch, exe treated as data.

## Anchor evidence (one row per distinct anchor RVA; verbatim `0xRVA  instr` copied from rdis of the exe)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | tag |
| M1c anchor: RendererContextD3D12::submit (slot 50) | 0xe82e230 | 0x4d91 | `0xe82e230  push rbp` | [V] |
| M1c anchor: D3D12 draw executor (per-job item loop) | 0xe821120 | 0xc3c3 | `0xe821120  push rbp` | [V] |
| M1c/M3e anchor: D3D12 draw batch flush (DrawInstanced/DrawIndexedInstanced/ExecuteIndirect) | 0xe81b720 | - | `0xe81b720  push r15` | [V] |
| M1c anchor: BgfxFrameBuilder::endFrame | 0xc270460 | 0x2aa | `0xc270460  push rbp` | [V] |
| M1c anchor: dragon frame-graph generate/encode | 0xc273420 | 0x8A73 | `0xc273420  push rbp` | [V] |
| M1c anchor: bgfx::Context::init (thread start) | 0xbc63690 | 0x4e7 | `0xbc63690  push rsi` | [V] |
| M1c anchor: D3D12 init (slot 58) | 0xe807ff0 | - | `0xe807ff0  push rbp` | [V] |
| M3c anchor: task list dispatch | 0xe9002e0 | - | `0xe9002e0  push rbp` | [V] |
| M1c/M3b anchor: GraphicsTasks Execute (render thread) | 0xc25fc50 | - | `0xc25fc50  push rbp` | [V] |
| M1c anchor: GraphicsTasks Render lambda | 0xc267200 | - | `0xc267200  push rbp` | [V] |
| M3d anchor: ActorRenderDispatcher bodyActor | 0x66d0a00 | - | `0x66d0a00  push rbp` | [V] |
| M1d anchor: Item group visitor (dispatch reversed) | 0x6646980 | - | `0x6646980  push rbp` | [V] |
| M1c anchor: graphics PSO builder | 0xe81e860 | - | `0xe81e860  push r15` | [V] |
| M1d anchor: BatchActor thin clone (Item tag 10) | 0x4e39cb0 | - | `0x4e39cb0  push rbp` | [V] |
| M1e anchor: VV frame-graph builder (giant) | 0x55f1450 | - | `0x55f1450  push rbp` | [V] |
| M1c anchor: Frame renderer entry (Fancy shares it) | 0x67c9c20 | - | `0x67c9c20  push rbp` | [V] |
| M4a anchor: UniformBlock::setUniform (vec4 array, dirty bit) | 0x5679db0 | - | `0x5679db0  push r15` | [V] |
| M4a anchor: mat4 multiply (pure SIMD leaf) | 0xaa6580 | - | `0xaa6580  sub rsp,0xB8` | [V] |

Size note: 0x4d91 (submit, BGFX_MAP 6t), 0xc3c3 (executor, 6e-2), 0x2aa (endFrame, 6n), 0x8A73 (generate, 6n-2), 0x4e7 (Context::init, 6q) are function extents cited from BGFX_MAP and are [I] (not re-measured here); every quoted first instruction is [V] via rdis. Rows marked "-" have no function extent cited in the sections read.

## Sub-line states from docs/RENDER_CHECKLIST.md (STATUS block, last update 2026-11-22)

- M1b classification — [ ] PENDING. functions.tsv holds the layer inventory: 241 functions across L1-L16 (L1 20, L2 34, L3 25, L4 62, L5 57, L6 32, L7 1, L9 6, L10 1, L11 2, L16 1); status D0=37, D1=74, D2=130, D3=0. The remaining work (annotate/classify, layer split by call graph, add rows for the big render functions) is not done: 111 functions are still D0/D1 with no D2 dossier. [V] — functions.tsv is a repo file read in full; counts are mine.
- M1c — [ ] PENDING (dossier gaps). D2 dossiers exist for submit 0xe82e230, executor 0xe821120, PSO builder 0xe81e860, endFrame 0xc270460, generate 0xc273420, Context::init/frame 0xbc63690/0xbc66de0, renderFrame 0xbc63150, thread proc 0xbc65720, shutdown 0xbc660a0, GraphicsTasks Execute/Wait 0xc25fc50/0xc25f960, task runner 0xc25fe20, insertion sort/stable_sort 0xc280010/0xc280ca0, command interpreter 0xbc68e40. Still D1/open: slot 58 init 0xe807ff0 (D1), Render lambda 0xc267200 (D1), scheduler 0xc25b1a0 (D1), plus the D0/D1 functions from the M1b census. The item's own "next" work (6cs header fields, slots 39-45, drain blocks of 0xbc660a0, generate per-pass loop, then L4/L5 dossiers) remains open.
- M1d — [ ] PENDING (dossier gaps). All 21 thin insert clones are D2, their constructors D2, all six group visitors D2 (0x66742f0/0x666aca0/0x6664a00/0x66560f0/0x6640d80/0x6646980). Extractors remain D1 with inner field decode pending: chunk 0x66ea3d0, batch-actor 0x66d9af0, item-in-hand 0x6698e30, skinned 0x6b84e60, nametag, particle, sky.
- M1e — [ ] PENDING (dossier gaps). ScreenDraw group mapped (declare 0xbbbd3d0 D2, build 0xbc37320 D1, execute 0xbc04dc0 D1, submitGeometry 0xbcc38e0 D2). Non-ScreenDraw bodies open: deferred 0xbc2cd20 D1; SSR/TAAU/RTX/voxel bodies D0. Per-pass in/out resources not documented.
- M3a — [ ] PENDING. Headers + static_asserts + layoutcheck (199 assertions, 0 failed) exist, but the SelfTest world-phase validation is not run in game; item not ticked.
- M3b — [ ] PENDING. docs/FRAME_CALLGRAPH.md exists (thread A/B tables with args per hop); open links: M1d groups, A5/A7/B3 D1, two [?] links.
- M3c — [ ] PENDING. TaskDispatchHook + dragon/Tasks.h written, never built or run (needs build + in-game test).
- M3d — [x] CLOSED per STATUS (oc_U-EM3d.md 67/67): actor->draw via RenderMarkHook re-validated against flush 0xe81b720 and the Encoder::submit seam; hook exists, not registered.
- M3e — [ ] PENDING. Edit draws at submit: needs header-to-record mapping plus an in-game test.
- M3f — [ ] PENDING. Whole-frame replacement: custom item seam Encoder::submitCustom (key bit 53, 0xbc61560 D2 in functions.tsv) found; untested in game.
- M4a — [x] CLOSED per STATUS (oc_U-EM4a.md 11/11): ten version-stable anchors in Sigs.json, exactly 1 hit each.
- M4b — [x] CLOSED per STATUS (oc_U-EM4b.md 9/9): behavior paragraphs without RVAs for every structural function with a D2 dossier.
- M4c — [x] CLOSED per STATUS (oc_U-EN4b.md + oc_U-EO3b.md): startup validation, slotcheck 65/65, layoutcheck 199/0.
- M4d — [x] CLOSED per STATUS (oc_U-EO3c.md 130/130): dossier tool re-run on 50.04/51.01/60.05 for all 130 D2 functions (RVA/offset/slot movement measured).
- M1f — [ ] PARTIAL = NOT DONE. D3 live checks done for two passes only (6ij: frame pair spacing 0xE749C0, counters, backbuffer 1920x1137; 6il: buffers/layout). Every other D2 claim lacks a poll-only live read.

## What this unit proves and what it cannot prove

Proven [V] here: each of the 18 anchor RVAs above is a real function entry in the exe (verbatim first instruction matches rdis). Checklist STATUS records M3d and M4a-M4d as ticked with verify_oc evidence files from other units (those notes are evidence, not re-derived here — cited as [I]-level project state).

Not closed by this unit: M1b classification rows (111 D0/D1 functions), M1c/M1d/M1e dossier bodies (D1/D0 gaps listed above), M3a SelfTest world phase, M3b full frame trace, M3c build+run of TaskDispatchHook, M3e in-game draw edit, M3f in-game whole-frame replacement, M1f live checks for the remaining D2 claims.

CLOSES?: NO — single blocking fact: M3c (TaskDispatchHook built and run in game), M3e (draw veto/edit measured live in game) and M3f (whole-frame replacement exercised in game) are acceptance capabilities that require a build and in-game execution, which OPENCODE_BRIEF.md rules 1-2 forbid (no builds, game closed, static analysis only), and M1f's D3 live checks are PARTIAL (two passes done) — so not every pending part of R14 is proven by [V] rows. R14 stays `[ ]`; nothing in this file invents a size, offset, name or meaning.

## TOOL REQUESTS
None
