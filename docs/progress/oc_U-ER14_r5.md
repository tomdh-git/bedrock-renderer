## NEXT
DONE

# Unit U-ER14 — Close checklist item R14

Source item (docs/RENDER_CHECKLIST.md line 612, section R Partials ledger):
`- [ ] R14 M1b classification, M1c/M1d/M1e dossier gaps, M3a-M3f, M4a-M4d, M1f (see their own lines)`

Rule applied: do ONLY the part marked pending/not found/not decoded in that line. Sub-lines already `[x]` in the STATUS block (M1b, M3b, M3d, M4a, M4b, M4c, M4d per the STATUS block last updated 2026-11-22) are recorded as closed and not re-proven here. Static analysis only per docs/OPENCODE_BRIEF.md rules 1-2: the exe is data, never launched; no builds; every verbatim `0xRVA  instr` line below was taken from the precomputed `docs/data/d2_first_instructions.json` (orchestrator input data, read in full) or from a single `rdis dis 0x<rva> 1` first-instruction read, and is re-checked by `verify_oc` before this unit is considered done. Sizes marked [I] are function extents cited in docs/BGFX_MAP.md or the EM-unit notes (not re-measured); "-" means no extent is cited in the sections read.

## Anchor evidence table (one row per distinct RVA; verbatim `0xRVA  instr` proof line copied verbatim from the input data / rdis)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | tag |
|---|---|---|---|---|
| M1c anchor: RendererContextD3D12::submit (vtable slot 50, D2 dossier) | 0xe82e230 | 0x4d91 | `0xe82e230  push rbp` | [V] |
| M1c anchor: D3D12 draw executor 0xe821120 (D2 dossier) | 0xe821120 | 0xc3c3 | `0xe821120  push rbp` | [V] |
| M1c/M3e anchor: draw batch flush 0xe81b720 (D2 dossier) | 0xe81b720 | 0x803 | `0xe81b720  push r15` | [V] |
| M1c anchor: D3D12 graphics PSO builder 0xe81e860 (D2 dossier) | 0xe81e860 | 0x1c9a | `0xe81e860  push r15` | [V] |
| M1c anchor: BgfxContext::endFrame 0xc270460 (D2 dossier) | 0xc270460 | 0x2aa | `0xc270460  push rbp` | [V] |
| M1c/M3b anchor: dragon frame-graph generate/encode 0xc273420 (D2 dossier) | 0xc273420 | 0x8A73 | `0xc273420  push rbp` | [V] |
| M1c anchor: bgfx::Context::init 0xbc63690 (D2 dossier) | 0xbc63690 | 0x4e7 | `0xbc63690  push rsi` | [V] |
| M1c anchor: bgfx::Context::frame/swap 0xbc66de0 (D2 dossier) | 0xbc66de0 | 0x19d7 | `0xbc66de0  push rbp` | [V] |
| M1c anchor: bgfx render thread proc 0xbc65720 (D2 dossier) | 0xbc65720 | - | `0xbc65720  push rsi` | [V] |
| M1c anchor: Context::renderFrame 0xbc63150 (D2 dossier) | 0xbc63150 | - | `0xbc63150  push r14` | [V] |
| M1c anchor: frame()/swap shutdown sequence 0xbc660a0 (D2 dossier) | 0xbc660a0 | 0x9ab | `0xbc660a0  push rbp` | [V] |
| M1c/M3b anchor: GraphicsTasks task dispatch 0xe9002e0 (D2 dossier) | 0xe9002e0 | 0xc3a | `0xe9002e0  push rbp` | [V] |
| M1c anchor: GraphicsTasks Execute 0xc25fc50 (D2 dossier) | 0xc25fc50 | - | `0xc25fc50  push rbp` | [V] |
| M1c anchor: GraphicsTasks Wait for previous frame 0xc25f960 (D2 dossier) | 0xc25f960 | - | `0xc25f960  push rbp` | [V] |
| M1c anchor: bgfx command buffer interpreter 0xbc68e40 (D2 dossier) | 0xbc68e40 | - | `0xbc68e40  push r15` | [V] |
| M1c anchor: GuardedPagedArray<0x540>::ensure 0xbc7a7c0 (D2 dossier) | 0xbc7a7c0 | - | `0xbc7a7c0  push rbp` | [V] |
| M1c anchor: deferred texture/buffer transactions flush 0x6632bf0 (D2 dossier) | 0x6632bf0 | - | `0x6632bf0  push rbp` | [V] |
| M1c anchor: D3D12 init slot 58 0xe807ff0 (D1, NO dossier — gap) | 0xe807ff0 | - | `0xe807ff0  push rbp` | [V] |
| M1c anchor: device-lost/TDR slot 7 0xe8102b0 (D1, NO dossier — gap) | 0xe8102b0 | - | `0xe8102b0  push rbp` | [V] |
| M1c anchor: createIndexBuffer base 0xe8124c0 (D1, NO dossier — gap) | 0xe8124c0 | - | `0xe8124c0  push rbp` | [V] |
| M1c anchor: createShader 0xe8137b0 (D1, NO dossier — gap) | 0xe8137b0 | - | `0xe8137b0  push r15` | [V] |
| M1c anchor: createTexture base 0xe8143c0 (D1, NO dossier — gap) | 0xe8143c0 | - | `0xe8143c0  push rbp` | [V] |
| M1c anchor: createFrameBuffer(window) slot 39 0xe817880 (D1, NO dossier — gap) | 0xe817880 | - | `0xe817880  push r15` | [V] |
| M1c anchor: framebuffer post-create 0xe819b50 (D0, NO dossier — gap) | 0xe819b50 | - | `0xe819b50  push r15` | [V] |
| M1c anchor: TextureD3D12::create 0xe81bf30 (D1, NO dossier — gap) | 0xe81bf30 | - | `0xe81bf30  push rbp` | [V] |
| M1c anchor: resource state transition helper 0xe82d960 (D1, NO dossier — gap) | 0xe82d960 | - | `0xe82d960  push r15` | [V] |
| M1c anchor: upload ring allocator 0xe8360f0 (D1, NO dossier — gap) | 0xe8360f0 | - | `0xe8360f0  push rbp` | [V] |
| M1c anchor: draw executor wrapper 0xe83c390 (D1, NO dossier — gap) | 0xe83c390 | - | `0xe83c390  push rbp` | [V] |
| M1c anchor: RTX submit override slot 50 0xe83d440 (D1, NO dossier — gap) | 0xe83d440 | - | `0xe83d440  push r14` | [V] |
| M1c anchor: DLSS reset slot 60 0xe83ec70 (D1, NO dossier — gap) | 0xe83ec70 | - | `0xe83ec70  push r15` | [V] |
| M1c anchor: RTX GPU skinning slot 63 0xe83f1d0 (D1, NO dossier — gap) | 0xe83f1d0 | - | `0xe83f1d0  push rbp` | [V] |
| M1c anchor: SuperSampling slot 64 0xe8403d0 (D1, NO dossier — gap) | 0xe8403d0 | - | `0xe8403d0  push rbp` | [V] |
| M1c anchor: vtable slot 45 target 0xe8189c0 (D0 entry-indirect, UNNAMED — 'slots 39-45' read gap) | 0xe8189c0 | - | `0xe8189c0  push rsi` | [V] |
| M1c anchor: render-thread begin/init step 0xbc68840 (D1, NO dossier — gap) | 0xbc68840 | - | `0xbc68840  push r15` | [V] |
| M1d anchor: terrain/chunk draw builder 0x66ea3d0 (L5 D1, NO dossier — gap) | 0x66ea3d0 | - | `0x66ea3d0  push rbp` | [V] |
| M1d anchor: ItemInHand extractor 0x6698e30 (L5 D1+, pending ranges, NO D2 dossier — gap) | 0x6698e30 | - | `0x6698e30  push rbp` | [V] |
| M1d anchor: BatchActor extractor 0x66d9af0 (L5 D1, NO dossier — gap) | 0x66d9af0 | - | `0x66d9af0  push rbp` | [V] |
| M1d anchor: Particle extractor 0x67417f0 (L5 D1, NO dossier — gap) | 0x67417f0 | - | `0x67417f0  push rbp` | [V] |
| M1d anchor: Weather extractor 0x6745440 (L5 D1, NO dossier — gap) | 0x6745440 | - | `0x6745440  push rbp` | [V] |
| M1d anchor: Clouds extractor 0x67375a0 (L5 D1, NO dossier — gap) | 0x67375a0 | - | `0x67375a0  push rbp` | [V] |
| M1d anchor: UI text renderer 0x674a3a0 (L5 D1, NO dossier — gap) | 0x674a3a0 | - | `0x674a3a0  push rbp` | [V] |
| M1d anchor: BlockSelectionOverlay extractor 0x66e75f0 (L5 D1, NO dossier — gap) | 0x66e75f0 | - | `0x66e75f0  push rbp` | [V] |
| M1d anchor: Editor block-volume extractor 0x66a1860 (L5 D1, NO dossier — gap) | 0x66a1860 | - | `0x66a1860  push rbp` | [V] |
| M1d anchor: FlameBillboard extractor 0x673d150 (L5 D1, NO dossier — gap) | 0x673d150 | - | `0x673d150  push rbp` | [V] |
| M1d anchor: Gameface extractor 0x66ade80 (L5 D1, NO dossier — gap) | 0x66ade80 | - | `0x66ade80  push rbp` | [V] |
| M1d anchor: EnvironmentalText/UIText insert clone 0xe71330 (L4 D1, NO dossier — gap) | 0xe71330 | - | `0xe71330  push rbp` | [V] |
| M1d anchor: RenderSkinnedMeshDescription insert general 0x6b84e60 (L4 D1, NO dossier — gap) | 0x6b84e60 | - | `0x6b84e60  push rbp` | [V] |
| M1d anchor: RenderSkinnedMeshDescription insert second 0x4e39f20 (L4 D1, NO dossier — gap) | 0x4e39f20 | - | `0x4e39f20  push rbp` | [V] |
| M1d anchor: BlockSelectionOverlayBlockEntity insert 0x539b7c0 (L4 D1, NO dossier — gap) | 0x539b7c0 | - | `0x539b7c0  push rbp` | [V] |
| M1d anchor: RenderCloudsDescription insert clone 0x53e88a0 (L4 D1, NO dossier — gap) | 0x53e88a0 | - | `0x53e88a0  push rbp` | [V] |
| M1e anchor: DirectionalLightingPass execute 0xbc2cd20 (L6 D0, body/in-out unread — gap) | 0xbc2cd20 | - | `0xbc2cd20  push rbp` | [V] |
| M1e anchor: voxel upload pass execute 0xbc0ac20 (L6 D0, body/in-out unread — gap) | 0xbc0ac20 | - | `0xbc0ac20  push r15` | [V] |
| M1e anchor: RTX denoise/raygen execute 0xbc080c0 (L6 D0, body/in-out unread — gap) | 0xbc080c0 | - | `0xbc080c0  push rbp` | [V] |
| M1e anchor: ClusterLights execute 0xbc5bad0 (L6 D0, body/in-out unread — gap) | 0xbc5bad0 | - | `0xbc5bad0  push rbp` | [V] |
| M1e anchor: TAAUpscaling execute 0x56d4880 (L6 D0, body/in-out unread — gap) | 0x56d4880 | - | `0x56d4880  push rbp` | [V] |
| M1e anchor: pass lambda 0xbc2c590 (L6 D0) | 0xbc2c590 | - | `0xbc2c590  push rbp` | [V] |
| M1e anchor: pass lambda 0xbc2d550 (L6 D0) | 0xbc2d550 | - | `0xbc2d550  push rbp` | [V] |
| M1e anchor: pass lambda 0xbc2dd20 (L6 D0) | 0xbc2dd20 | - | `0xbc2dd20  push rbp` | [V] |
| M1e anchor: pass lambda 0xbc2eb50 (L6 D0) | 0xbc2eb50 | - | `0xbc2eb50  push rbp` | [V] |
| M1e anchor: pass lambda 0xbc2f4a0 (L6 D0) | 0xbc2f4a0 | - | `0xbc2f4a0  push rbp` | [V] |
| M1e anchor: pass lambda 0xbc0b240 (L6 D0) | 0xbc0b240 | - | `0xbc0b240  push rbp` | [V] |
| M1e anchor: pass lambda 0xbc36140 (L6 D0) | 0xbc36140 | - | `0xbc36140  push rbp` | [V] |
| M1e anchor: pass lambda 0xbc38c20 (L6 D0) | 0xbc38c20 | - | `0xbc38c20  push rbp` | [V] |
| M1e anchor: pass lambda 0xbc0f130 (L6 D0) | 0xbc0f130 | - | `0xbc0f130  push rbp` | [V] |
| M1e anchor: pass lambda 0x56e1990 (L6 D0) | 0x56e1990 | - | `0x56e1990  push rbp` | [V] |
| M1e anchor: pass lambda 0x56a06a0 (L6 D0, DoDeferredShading/SkyProbeDeferredShading) | 0x56a06a0 | - | `0x56a06a0  push rbp` | [V] |
| M3a anchor: Encoder::submit 0xbc60740 (D2 dossier, anchors block filled per oc_U-EM4a.md) | 0xbc60740 | 0x5d0 | `0xbc60740  push r15` | [V] |
| M3c anchor: task list dispatch 0xe9002e0 (TaskDispatchHook written, never built/run) | 0xe9002e0 | 0xc3a | `0xe9002e0  push rbp` | [V] |
| M3e anchor: draw flush 0xe81b720 (header->record mapping + in-game test missing) | 0xe81b720 | 0x803 | `0xe81b720  push r15` | [V] |
| M3f anchor: custom-item seam Encoder::submitCustom (key bit 53, untested in game) | 0xbc61560 | - | `0xbc61560  push r15` | [V] |

Size provenance ([I] = cited, not re-measured): 0x4d91 submit BGFX_MAP 6t; 0xc3c3 executor 6e-2; 0x803/0x1c9a/0xc3a drawFlush/psoBuilder/taskDispatch per oc_U-EM4a.md port_metrics_60.05 (== 62.01); 0x2aa endFrame 6n; 0x8A73 generate 6n-2; 0x4e7 Context::init 6q; 0x19d7 Context::frame 6r; 0x9ab shutdown 0xbc660a0 per oc_U-EM1c.md census; 0x5d0 Encoder::submit, 0x215 Frame::sort per oc_U-EM4a.md; 0x966 Frame renderer per oc_U-EM3b.md; 0x1E5 render-thread begin step 0xbc68840 per oc_U-EM3b.md-derived. M1b sizes [I] mechanical from docs/data/inventory_*.tsv. All other rows "-" = no function extent cited in the sections read. Every quoted first instruction is [V] (verbatim from d2_first_instructions.json or `rdis dis 0x<rva> 1`).

## Sub-line states (docs/RENDER_CHECKLIST.md section M, STATUS block last updated 2026-11-22)

- M1b classification — [x] CLOSED already (oc_U-EM1b.md, verify_oc 8/8): all 15,113 L1..L6 functions are D0+ rows in docs/data/functions.tsv; class column joined in docs/data/function_classes.tsv (1,508 classification rows); nothing pending in this unit.
- M1c — [ ] OPEN: L1-L3 structural functions at D0/D1 without a D2 dossier. Presence at RVA verified [V] above for 19 functions incl. the unnamed vtable slot 45 target 0xe8189c0 ('slots 39-45' gap); D2 dossiers still missing for all of them.
- M1d — [ ] OPEN: L4/L5 extractors/handlers at D1 without a D2 dossier. Presence at RVA verified [V] above for 16 extractors/handlers/clones; visitors, thin clones and constructors are mostly D2 already; dossiers still missing.
- M1e — [ ] OPEN: L6 pass lambdas at D0. Presence at RVA verified [V] above for 16 lambdas (incl. DoDeferredLighting 0xbc2cd20, voxel upload 0xbc0ac20, RTX driver 0xbc080c0, ClusterLights 0xbc5bad0, TAAU 0x56d4880, DoDeferredShading 0x56a06a0); more D0 lambdas exist per functions.tsv (0xbc2c590, 0xbc2d550, 0xbc2dd20, 0xbc2eb50, 0xbc2f4a0, 0xbc0b240, 0xbc36140, 0xbc38c20, 0xbc0f130 listed). Bodies and per-pass in/out resources unread.
- M3a — [ ] OPEN: static half done (headers + layoutcheck 209/0 [V]); SelfTest world-phase validation requires launching the game (rule 1) — not done.
- M3b — [x] CLOSED already (oc_U-EM3b.md, verify_oc 24/24).
- M3c — [ ] OPEN: TaskDispatchHook + dragon/Tasks.h written but never built or run — the pass add/remove/reorder acceptance capability.
- M3d — [x] CLOSED already (oc_U-EM3d.md, verify_oc 67/67).
- M3e — [ ] OPEN: edit draws at submit — header-to-record mapping completion plus an in-game test missing; forbidden by rules 1-2.
- M3f — [ ] OPEN: whole-frame replacement — custom-item seam 0xbc61560 Encoder::submitCustom (key bit 53) present [V], untested in game, ctx layout partly inferred; needs M1c-M3e.
- M4a — [x] CLOSED already (oc_U-EM4a.md, verify_oc 11/11).
- M4b — [x] CLOSED already (oc_U-EM4b.md, verify_oc 9/9).
- M4c — [x] CLOSED already (oc_U-EN4b.md + oc_U-EO3b.md; layoutcheck 199/0).
- M4d — [x] CLOSED already (oc_U-EO3c.md, verify_oc 130/130).
- M1f — [ ] PARTIAL = NOT DONE: D3 live checks were done for two passes only (prior work); every other D2 claim lacks a poll-only live read; this static unit cannot perform them (rules 1-2).

## What is proven vs what remains open

Proven [V] here: each of the 60 anchor RVAs above is a real function entry in Minecraft.Windows.exe 1.26.62.01 and its verbatim first instruction matches rdis (re-checked by verify_oc). M1b/M3b/M3d/M4a-M4d are already `[x]` per the STATUS block and are not re-derived.

Not closed by this unit: M1c/M1d/M1e dossier bodies (D1/D0 gaps — presence proven, dossiers missing), M3a SelfTest world phase, M3c TaskDispatchHook build+run, M3e in-game draw edit, M3f in-game whole-frame replacement, M1f remaining D3 live reads.

## CLOSES?

NO — single blocking fact: M3c (frame-graph pass add/remove/reorder via TaskDispatchHook + dragon/Tasks.h) was never built or run, and OPENCODE_BRIEF.md rules 1-2 forbid both the DLL build and the in-game test, so this acceptance capability can never be proven closed by static [V] verbatim-instruction rows in this note; M3e and M3f likewise require in-game tests and M1f remains PARTIAL. R14 stays `[ ]`.

## TOOL REQUESTS

None — all input data was precomputed (docs/data/d2_first_instructions.json, docs/data/function_classes.tsv, docs/data/functions.tsv, docs/BGFX_MAP.md sections cited) and each quoted first instruction was taken from that data or a single `rdis dis 0x<rva> 1` read; no helper scripts written, no `_tmp*` files left behind.

## NEXT
step 2
