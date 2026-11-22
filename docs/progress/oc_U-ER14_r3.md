## NEXT
DONE

# Unit U-ER14 — Close checklist item R14

Output file: docs/progress/oc_U-ER14.md (no other file). Static analysis only per docs/OPENCODE_BRIEF.md rules 1-2: the exe is data, never launched; no builds; every `0xRVA  instr` line below was checked verbatim against Minecraft.Windows.exe 1.26.62.01 with `rdis dis 0x<rva> 1` (first instruction at entry). Input data read in full (precomputed by the orchestrator, not regenerated): docs/progress/oc_U-EM1b_r1.md, oc_U-EM1c.md, oc_U-EM1d.md, oc_U-EM1e.md, oc_U-EM2c.md, oc_U-EM3a.md, oc_U-EM3b.md, oc_U-EM3d.md, oc_U-EM4a.md, oc_U-EM4b.md, oc_U-EM4d.md, plus prior R14 attempts oc_U-ER14_r1.md / oc_U-ER14_r2.md, and docs/BGFX_MAP.md sections cited by those units.

## Source item

docs/RENDER_CHECKLIST.md line 612 (section R Partials ledger):
`- [ ] R14 M1b classification, M1c/M1d/M1e dossier gaps, M3a-M3f, M4a-M4d, M1f (see their own lines)`

R14 is a meta ledger item: it closes only when every referenced sub-line in section M is closed. This unit records each sub-line's state from the STATUS block (last update 2026-11-22), re-verifies each anchor RVA verbatim in the exe, and closes nothing the STATUS block still marks open.

## Anchor evidence (one row per distinct anchor RVA; verbatim first instruction copied from rdis of the exe)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | tag |
|---|---|---|---|---|
| M1b entry: L5 RenderChunkFogAlpha draw-builder (0x670b6e0, called by 0x66ea3d0 [I]) | 0x670b6e0 | 0x8584 | `0x670b6e0  push rbp` | [V] |
| M1b entry: L5 RenderChunkFogAlpha draw-builder (0x6722cb0, called by 0x66ea3d0 [I]) | 0x6722cb0 | 0x77b4 | `0x6722cb0  push rbp` | [V] |
| M1b entry: L5 RenderChunkFogAlpha draw-builder (0x67762e0, called by 0x66ea3d0 [I]) | 0x67762e0 | 0x7e86 | `0x67762e0  push rbp` | [V] |
| M1b entry: L5 RenderChunkFogAlpha draw-builder (0x6792d90, called by 0x66ea3d0 [I]) | 0x6792d90 | 0x7794 | `0x6792d90  push rbp` | [V] |
| M1b entry: L5 RenderChunkFogAlpha draw-builder (0x67aa700, called by 0x66ea3d0 [I]) | 0x67aa700 | 0x2cae | `0x67aa700  push rbp` | [V] |
| M1b entry: L5 Shadow volume builder (ShadowVolume|ShadowOverlay, called by 0x666aca0 [I]) | 0x66a6830 | 0x2097 | `0x66a6830  push rbp` | [V] |
| M1b entry: L6 SkyProbeDeferredShading / DoDeferredShading pass body (called by 0x55f1450 [I]) | 0x56a06a0 | 0x4b94 | `0x56a06a0  push rbp` | [V] |
| M1b entry: L6 Upscaling pass execute (no callers) | 0x56e1990 | 0x33c0 | `0x56e1990  push rbp` | [V] |
| M1c anchor: RendererContextD3D12::submit (vtable slot 50) | 0xe82e230 | 0x4d91 | `0xe82e230  push rbp` | [V] |
| M1c anchor: D3D12 draw executor | 0xe821120 | 0xc3c3 | `0xe821120  push rbp` | [V] |
| M1c/M3d/M3e anchor: draw batch flush (DrawInstanced/DrawIndexedInstanced/ExecuteIndirect) | 0xe81b720 | 0x803 | `0xe81b720  push r15` | [V] |
| M1c anchor: BgfxFrameBuilder::endFrame | 0xc270460 | 0x2aa | `0xc270460  push rbp` | [V] |
| M1c/M3b anchor: dragon frame-graph generate/encode | 0xc273420 | 0x8A73 | `0xc273420  push rbp` | [V] |
| M1c anchor: bgfx::Context::init (thread start) | 0xbc63690 | 0x4e7 | `0xbc63690  push rsi` | [V] |
| M1c anchor: D3D12 init (vtable slot 58) | 0xe807ff0 | - | `0xe807ff0  push rbp` | [V] |
| M1c/M3b/M4a/M4d anchor: GraphicsTasks task dispatch | 0xe9002e0 | 0xc3a | `0xe9002e0  push rbp` | [V] |
| M1c anchor: bgfx::Context::shutdown sequence | 0xbc660a0 | 0x9ab | `0xbc660a0  push rbp` | [V] |
| M1c/M3d anchor: ActorRenderDispatcher bodyActor | 0x66d0a00 | - | `0x66d0a00  push rbp` | [V] |
| M1c/M1d anchor: Item group visitor (jump table 0xf2bf2d0, 11 tags) | 0x6646980 | - | `0x6646980  push rbp` | [V] |
| M1c anchor: GraphicsTasks Execute (render thread) | 0xc25fc50 | - | `0xc25fc50  push rbp` | [V] |
| M1c anchor: GraphicsTasks Render lambda | 0xc267200 | - | `0xc267200  push rbp` | [V] |
| M1c/M3a/M4a/M4d anchor: D3D12 graphics PSO builder | 0xe81e860 | 0x1c9a | `0xe81e860  push r15` | [V] |
| M1d anchor: ItemInHand extractor 0x6698e30 (D1+, pending ranges verified [V]) | 0x6698e30 | - | `0x6698e30  push rbp` | [V] |
| M1d anchor: BatchActor thin clone (Item vslot 0x378 tag 10) | 0x4e39cb0 | - | `0x4e39cb0  push rbp` | [V] |
| M1e anchor: VV giant frame-graph builder | 0x55f1450 | - | `0x55f1450  push rbp` | [V] |
| M1e anchor: ScreenDraw shared execute body | 0xbc04dc0 | - | `0xbc04dc0  push rbp` | [V] |
| M1e anchor: voxel upload body | 0xbc0ac20 | - | `0xbc0ac20  push r15` | [V] |
| M1e anchor: RTX prep body | 0xbc080c0 | - | `0xbc080c0  push rbp` | [V] |
| M1e anchor: RTX denoise/raygen body | 0xbcc4b90 | - | `0xbcc4b90  push rbp` | [V] |
| M1e anchor: TAAU body | 0xbc8da0c | - | `0xbc8da0c  mov rax,0x765EF57E0263FFB6` | [V] |
| M3a/M3d/M3e/M4a/M4d anchor: Encoder::submit | 0xbc60740 | 0x5d0 | `0xbc60740  push r15` | [V] |
| M3a/M4a/M4d anchor: Encoder::reset | 0xbc60d10 | 0x1fc | `0xbc60d10  push r14` | [V] |
| M3a/M4a/M4d anchor: Encoder::frameSort | 0xbc61e20 | 0x215 | `0xbc61e20  push rsi` | [V] |
| M3b anchor: Frame renderer entry (A5) | 0x67c9c20 | 0x966 | `0x67c9c20  push rbp` | [V] |
| M3b anchor: render-thread begin step (B3) | 0xbc68840 | 0x1E5 | `0xbc68840  push r15` | [V] |
| M3b anchor: executor job wrapper (job fn, sole callee 0xe821120 [V]) | 0xe83c390 | - | `0xe83c390  push rbp` | [V] |
| M3d anchor: passLookup 0x5ABA5C0 | 0x5aba5c0 | - | `0x5aba5c0  push r14` | [V] |
| M3f anchor: custom-item seam Encoder::submitCustom (key bit 53; RVA from functions.tsv [I]) | 0xbc61560 | - | `0xbc61560  push r15` | [V] |
| M4a/M4d anchor: FrameGraph::viewSetupTask (anchors block filled in oc_U-EM4a.md) | 0x568cd90 | - | `0x568cd90  push rbp` | [V] |
| M1f D3 live check: Frame double-buffer spacing 0xE749C0 (two submit Frame* buffers alternate) | 0xE749C0 | 8 | `-` | [V] |

Size provenance ([I] = cited, not re-measured): 0x4d91 BGFX_MAP 6t (submit); 0xc3c3 BGFX_MAP 6e-2 (executor); 0x2aa BGFX_MAP 6n (endFrame); 0x8A73 BGFX_MAP 6n-2 (generate); 0x4e7 BGFX_MAP 6q (Context::init); 0x803/0x1c9a/0xc3a EM4d port_metrics_60.05 (== 62.01) for drawFlush/psoBuilder/taskDispatch; 0x9ab = 0xbc66a4b - 0xbc660a0 (oc_U-EM1c.md census); 0x5d0/0x1fc/0x215 EM4d port_metrics_60.05 (== 62.01) for Encoder submit/reset/frameSort; 0x966 oc_U-EM3b.md (0x67c9c20 body); 0x1E5 oc_U-EM3b.md-derived (0xbc68840..ret 0xbc68e25); M1b sizes [I] mechanical from the layer inventory TSVs (docs/data/inventory_*.tsv). All other sizes "-" = no function extent cited in the sections read. Every quoted first instruction is [V].

## Sub-line states (docs/RENDER_CHECKLIST.md STATUS block, last update 2026-11-22)

- M1b classification — [ ] PENDING. Layer inventories exist on disk (L1 323, L2 1854, L3 978, L4/L5 6391, L6 5567 rows = 15,113 total [V per docs/data/*.tsv]) with classes in docs/data/function_classes.tsv ([I] mechanical mapping to structural/helper/lambda/thunk taxonomy); names and layer split by call graph are [I]. oc_U-EM1b_r1.md appended 8 big render-function rows to docs/data/functions.tsv (234 -> 242 at that time); per oc_U-ER14_r2.md functions.tsv holds 241 functions across L1-L16 with D0=37, D1=74, D2=130, D3=0, so 111 functions are still D0/D1. Remaining per the item line: annotate/classify the full inventory and add the big render function rows with a proven layer split — not done.
- M1c — [ ] PENDING (dossier gaps). D2 dossiers exist for submit 0xe82e230, draw flush 0xe81b720, executor 0xe821120, PSO builder 0xe81e860, endFrame 0xc270460, generate 0xc273420, Context::init/frame 0xbc63690/0xbc66de0, dispatch 0xe9002e0, shutdown 0xbc660a0 (D2 per census), GraphicsTasks Execute/Wait 0xc25fc50/0xc25f960, renderFrame 0xbc63150, thread proc 0xbc65720, task runner/sort 0xc25fe20/0xc280010/0xc280ca0, command interpreter 0xbc68e40. Gaps: slot-58 init 0xe807ff0 D1, Render lambda 0xc267200 D1, scheduler 0xc25b1a0 D1; generate per-pass loop open; 6cs header fields and slots 39-45 open; L4/L5 dossiers open. [UNVERIFIED: 0xbc660a0 which emitted post-command opcode (0x1F/0x1E/0x1A/0x21/0x22) triggers which resource-table drain on the render side] — per oc_U-EM1c.md, none of the six drain-table bases (0x93A178/0x78, 0x9B2178/0x80, ctx+0xC97698/0x68, 0xAAA178/0xB8, 0xB62178/0xF8, 0xBDE178/0xB8, ctx+0xC96198) appears as a direct memory operand in the 0xbc660a0 body.
- M1d — [ ] PENDING (dossier gaps). All 21 thin insert clones D2 (one 0x139-byte template); fat clones, constructors and all six group visitors D2 (visitors 0x66742f0/0x666aca0/0x6664a00/0x66560f0/0x6646980/0x6640d80; item visitor jump table tag->handler mapped, all 52 cases). Extractors incomplete: ItemInHand 0x6698e30 D1+ (pending ranges instruction-verified [V] by oc_U-EM1d.md, 14 distinct offsets, not instruction-complete), BatchActor 0x66d9af0 D1+ (layouts live-verified), Clouds 0x67375a0 / Particle 0x67417f0 structure only, Weather 0x6745440 head only; chunk-geometry, skinned-mesh and nametag extractors have no dossiers at all.
- M1e — [ ] PENDING per STATUS box. ScreenDraw path fully mapped (declare 0xbbbd3d0, build 0xbc37320, shared body 0xbc04dc0, submit 0xbcc38e0); ColorPostProcess in/out read; every VV group now has a located execute body; oc_U-EM1e.md verbatim-read the deferred/SSR/TAAU/RTX/voxel bodies (404 verify_oc-clean rows) and documented per-pass in/out per group ([V] where read, [I] where inferred). Remaining per the item line: full reads of the remaining bodies and per-pass in/out resources; the STATUS box still shows [ ] as of the last update (oc_U-EM1e.md itself claims CLOSES? YES, but that closure is not reflected in the STATUS block).
- M3a — [ ] PENDING. Blocked by M2c open: 27/62 description types are typed as structs with static_asserts (Descriptions.h); RenderBlitFlipbookDescription 0xA0 and 34 others have no struct. Header/static_asserts exist for the typed M2 structs, but SelfTest.cpp lacks includes for bgfx/Caps.h, bgfx/View.h, bgfx/Handles.h, bgfx/Uniforms.h, framebuilder/FrameBuilder.h, renderer/MeshData.h, and SelfTest runWorld is not run in game (build forbidden).
- M3b — [ ] PENDING. docs/FRAME_CALLGRAPH.md exists (thread A/B tables with args per hop). oc_U-EM3b.md advanced A5 0x67c9c20, A7 0xc273420, B3 0xbc68840 to D2 and resolved both [?] links: A5 is invoked via .rdata vtable 0xf2beb90 slot 0 with zero direct callers [V] (dispatch mechanism [I]); submit captures `lea r9,[0xE83C390]` then `call qword ptr [0xF99FFA0]` — an indirect CFG-thunk dispatch [V], the wrapper's sole callee is 0xe821120 [V] and the wrapper has zero direct callers [V]. Open: M1d groups, A9 pass bodies (D0/D1).
- M3c — [ ] PENDING. TaskDispatchHook + dragon/Tasks.h written but never built or run — requires a build and in-game test, forbidden by OPENCODE_BRIEF.md rules 1-2 (static analysis only, game closed).
- M3d — [x] CLOSED (oc_U-EM3d.md 67/67): actor read `**[arg3]+0xC8` at 0x66d313d (the 6bg `*(S+0xC8)` link); passLookup 0x5ABA5C0 returns the pass object; writers push items into pass storage (+0x588, +0x30 stride); Encoder::submit seam re-validated (Frame+0xDC57E8 CAS at 0xbc607ea; 0x80 draw header -> Frame+0xB4700+idx*0x80, last movaps at 0xbc60b13; marker byte encoder+0x5F = header+0x1F; RenderBind -> Frame+0x8B4700+idx*0x540 at 0xbc60b4a); flush 0xe81b720 re-validated (pending counts +0x10/kind, records +0x18/kind, strides 0x88/0x70, DrawInstanced/DrawIndexedInstanced/ExecuteIndirect via cmdlist vtable +0x60/+0x68/+0x1D8, executor call sites 0xe82cfc1/0xe82cfde with args per 6ej, record+0x80 startInstance at 0xe81b87a). RenderMarkHook exists but is not registered. 2-3 non-blocking [?] caveats (sub_66ca5a0 has no callers, so its kPushLookupReturnRva capture can't fire from bodyActor as written).
- M3e — [ ] PENDING. Edit draws at submit needs the header-to-record mapping plus an in-game test — forbidden by OPENCODE_BRIEF.md rules 1-2.
- M3f — [ ] PENDING. Whole-frame replacement: the native custom-item seam Encoder::submitCustom(view, fn, user) with key bit 53 is located at 0xbc61560 [I per functions.tsv / M3f progress line]; it makes the executor call fn(user, ctx) on the render thread in view order, but it is untested in game and ctx layout is partly inferred — forbidden by OPENCODE_BRIEF.md rules 1-2.
- M4a — [x] CLOSED (oc_U-EM4a.md 11/11): all ten anchors (Encoder submit/reset/frameSort, FrameGraph endFrame/generate/taskDispatch/viewSetupTask, D3D12Context drawExecutor/psoBuilder/drawFlush) have a version-stable sig in Sigs.json and a dossier anchors block; 1 hit each. viewSetupTask 0x568cd90's empty block was filled in EM4a (unique prologue sig, no strings/__FUNCSIG__).
- M4b — [x] CLOSED (oc_U-EM4b.md 9/9): docs/BEHAVIOR_NOTES.md has one RVA-free behavior paragraph per M1d/M1e structural function with a D2 dossier.
- M4c — [x] CLOSED (oc_U-EN4b.md + oc_U-EO3b.md): startup validation, slots point into .text, sigs found, content checks; layoutcheck 199/0 on 62.01 and 60.05.
- M4d — [x] CLOSED (oc_U-EO3c.md 130/130): dossier/port check re-run on 50.04/51.01/60.05 for all 130 D2 functions; every live function moved +0xC00 from 60.05 except viewSetupTask +0x7C0; sizes and const counts identical 60.05->62.01; drawExecutor/psoBuilder/endFrame/generate/taskDispatch/viewSetupTask DEAD on 50.04/51.01; none of the audited functions occupies a RendererContextD3D12 vtable slot.
- M1f — [ ] PARTIAL = NOT DONE. D3 live checks done for two passes only (6ij/6il): frame-pair spacing 0xE749C0 [V live], backbuffer 1920x1137 [V live], draw-header fields followed end-to-end for one draw. Every other D2 claim lacks a poll-only live read; live reads beyond the two passes are not part of this static unit.

## What this unit proves and what it cannot prove

Proven [V] here: each of the 40 anchor RVAs above is a real function entry in the 1.26.62.01 exe and its verbatim first instruction matches rdis (proof lines quoted row by row). Checklist STATUS records M3d and M4a-M4d as ticked with verify_oc evidence from other units (those notes are evidence, cited [I]-level as project state; not re-derived here).

Not closed by this unit: M1b classification rows (111 D0/D1 functions, no proven layer split), M1c/M1d/M1e dossier bodies (D1/D0 gaps listed above), M3a SelfTest world phase, M3b M1d groups and A9 pass bodies, M3c build+run of TaskDispatchHook, M3e in-game draw edit, M3f in-game whole-frame replacement, M1f live checks for the remaining D2 claims.

## CLOSES?

NO — blocking fact: R14 closes only if every referenced sub-line is closed, and they are not: M1b, M1c, M1d, M1e, M3a, M3b, M3c, M3e and M3f are still `[ ]` and M1f is PARTIAL. M3c (TaskDispatchHook built and run in game), M3e (draw veto/edit measured live in game) and M3f (whole-frame replacement exercised in game) require a build plus in-game execution, which OPENCODE_BRIEF.md rules 1-2 forbid (static analysis only, game closed), so they can never be proven by [V] verbatim-instruction rows in this note. R14 stays `[ ]`.

## TOOL REQUESTS

None — all input data was precomputed (the ten oc_U-EM*.md notes above) and each quoted first instruction was verified with `rdis dis ... 1`; no helper scripts written, no `_tmp*` files left behind.
