## NEXT
DONE

# Unit U-ER14 — Close checklist item R14 (output file docs/progress/oc_U-ER14.md, no other file)

Source item (docs/RENDER_CHECKLIST.md line 612, section R Partials ledger):
`- [ ] R14 M1b classification, M1c/M1d/M1e dossier gaps, M3a-M3f, M4a-M4d, M1f (see their own lines)`

Rule applied: do ONLY the part marked pending/not found/not decoded in that line. Sub-lines already `[x]` per the STATUS block (last update 2026-11-22) are recorded closed and NOT re-proven here: M1b (oc_U-EM1b.md, verify_oc 8/8), M3b (oc_U-EM3b.md, verify_oc 24/24), M3d (oc_U-EM3d.md, verify_oc 67/67), M4a (oc_U-EM4a.md), M4b (oc_U-EM4b.md), M4c (oc_U-EN4b.md/oc_U-EO3b.md), M4d (oc_U-EO3c.md, verify_oc 130/130). This unit covers the pending parts: M1c, M1d, M1e dossier gaps; M3a, M3c, M3e, M3f acceptance capabilities; M1f D3 live checks.

Static analysis only per docs/OPENCODE_BRIEF.md rules 1-2: the exe is data, never launched; no builds; no debugger or breakpoints. BGFX_MAP.md sections read for role provenance: 6t (submit), 6am (draw header / executor base), 6e-2 (executor), 6q/6r/6s (Context init/frame/swap), 6b (live frame spacing), 6g/6w (clones/tags), 6ci (item visitor), 6u/6be/6ab/6x (extractors), 6p/6v (pass lambdas), 6n/6n-2 (endFrame/generate), 6ac (GraphicsTasks chain), 6z (resource tables).

Every `0xRVA  instr` line below is verbatim (two spaces after the address), taken from the precomputed docs/data/d2_first_instructions.json or a single `rdis dis 0x<rva> 1` first-instruction read; every line is re-checked by verify_oc. Size comes from the instruction; first-instruction anchor rows have no load/store operand, so size is `-` and the function extent cited from an input file is marked [I] in meaning, not re-measured. Meaning is `-` unless an instruction/string shows it; role/provenance from cited input data is tagged [I]. Tag [V] = verbatim first instruction matched rdis dis; [I] = cited from input data, not shown by the instruction itself.

## Answer — anchor evidence (one row per distinct RVA; all sites of that RVA listed)

| offset | size | site | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| M1c — D3D12 init slot 58 0xe807ff0 | - | - | `0xe807ff0  push rbp` | slot 58 init (loads d3d12.dll, D3D12CreateDevice); D1, no D2 dossier — gap; extent 0x1734 [I per d3d12_vtable_1.26.62.01.txt] | [V] |
| M1c — vtable slot 45 target (unnamed) 0xe8189c0 | - | - | `0xe8189c0  push rsi` | slot 45 target, unnamed — 'slots 39-45' read gap (M1c); extent 0xa1 [I per d3d12_vtable_1.26.62.01.txt] | [V] |
| M1c — slot 39 createFrameBuffer(window) 0xe817880 | - | - | `0xe817880  push r15` | slot 39 target (window-backed framebuffer/swapchain); D1 gap; extent 0x37b [I per d3d12_vtable_1.26.62.01.txt] | [V] |
| M1c — slot 40 0xe8176a0 | - | - | `0xe8176a0  push r15` | slot 40 target; D1 gap; extent 0xeb [I per d3d12_vtable_1.26.62.01.txt] | [V] |
| M1c — slot 41 0xe817c00 | - | - | `0xe817c00  push rsi` | slot 41 target; D1 gap; extent 0xe5 [I per d3d12_vtable_1.26.62.01.txt] | [V] |
| M1c — device-lost/TDR slot 7 0xe8102b0 | - | - | `0xe8102b0  push rbp` | slot 7 target (device-lost/TDR strings); D1 gap; extent 0x1924 [I per d3d12_vtable_1.26.62.01.txt] | [V] |
| M1d — chunk draw builder 0x66ea3d0 | - | - | `0x66ea3d0  push rbp` | Item tag 3/4 terrain draw builder (EndPortal/WaterPrepass/RenderChunk strings); D1, inner field decode pending; extent 0xF430 [I per BGFX_MAP 6x] | [V] |
| M1d — BatchActor extractor 0x66d9af0 | - | - | `0x66d9af0  push rbp` | Item tag 10 extractor; D1+, inner field decode pending; extent 0x8BB7 [I per BGFX_MAP 6u] | [V] |
| M1d — ItemInHand extractor 0x6698e30 | - | - | `0x6698e30  push rbp` | Item tag 6 extractor; D1+, pending ranges verified [V] by oc_U-EM1d.md but not instruction-complete; extent 0x5FB4 [I per BGFX_MAP 6ab] | [V] |
| M1d — Particle extractor 0x67417f0 | - | - | `0x67417f0  push rbp` | Effect tag 2 extractor (ParticleForwardPBR strings); D1, structure only; extent 0x2CD7 [I per BGFX_MAP 6x] | [V] |
| M1d — Weather extractor 0x6745440 | - | - | `0x6745440  push rbp` | Sky tag 9 extractor (WeatherForwardPBR strings); D1, head only; extent 0x3A5A [I per BGFX_MAP 6x] | [V] |
| M1d — Clouds extractor 0x67375a0 | - | - | `0x67375a0  push rbp` | Sky tag 1 extractor (CloudsForwardPBR strings); D1, structure; extent 0x3DFB [I per BGFX_MAP 6x] | [V] |
| M1e — DirectionalLightingPass/DoDeferredLighting 0xbc2cd20 | - | - | `0xbc2cd20  push rbp` | deferred lighting body (VV group); D0, body and per-pass in/out resources unread | [V] |
| M1e — voxel upload pass 0xbc0ac20 | - | - | `0xbc0ac20  push r15` | dirty volume upload body; D0, body and per-pass in/out resources unread | [V] |
| M1e — RTX driver 0xbc080c0 | - | - | `0xbc080c0  push rbp` | RTX denoise/raygen driver (43 passes via 0xbcc4b90); D0, body and per-pass in/out resources unread | [V] |
| M1e — ClusterLights 0xbc5bad0 | - | - | `0xbc5bad0  push rbp` | cluster lights body; D0, body and per-pass in/out resources unread | [V] |
| M1e — TAAU upscale 0x56d4880 | - | - | `0x56d4880  push rbp` | TAA upscale body; D0, body and per-pass in/out resources unread | [V] |
| M1e — DoDeferredShading 0x56a06a0 | - | - | `0x56a06a0  push rbp` | deferred shading body; D0, body and per-pass in/out resources unread | [V] |
| M3a — Encoder::submit 0xbc60740 | - | - | `0xbc60740  push r15` | D2 dossier exists (docs/functions/bc60740.md); extent 0x5d0 [I per oc_U-EM4a.md]; M3a gap is the un-run SelfTest world-phase validation (rule 1), not the anchor | [V] |
| M3a — Encoder::reset 0xbc60d10 | - | - | `0xbc60d10  push r14` | D2 dossier exists (6fe); extent 0x1fc [I per oc_U-EM4a.md] | [V] |
| M3a — Frame::sort 0xbc61e20 | - | - | `0xbc61e20  push rsi` | D2 dossier exists (6fd); extent 0x215 [I per BGFX_MAP 6t] | [V] |
| M3c — task list dispatch 0xe9002e0 | - | - | `0xe9002e0  push rbp` | FrameGraph::taskDispatch (D2 dossier); extent 0xc3a [I per port_metrics_60.05 == 62.01]; TaskDispatchHook written, never built or run — blocking | [V] |
| M3e — draw batch flush 0xe81b720 | - | - | `0xe81b720  push r15` | draw flush (DrawInstanced/DrawIndexedInstanced/ExecuteIndirect, D2); extent 0x803 [I per port_metrics_60.05 == 62.01]; header-to-record mapping + in-game test missing | [V] |
| M3e — executor header base 0xe82269e | - | - | `0xe82269e  lea r12,[r9+rdx]` | executor header base computation (Frame+0xB4700 + (itemIndex<<7)) [I per BGFX_MAP 6am]; header-to-record mapping incomplete | [V] |
| M3f — custom-item seam submitCustom 0xbc61560 | - | - | `0xbc61560  push r15` | Encoder::submitCustom key bit 53 (D2, functions.tsv); untested in game, ctx layout partly inferred | [V] |
| M1f — frame double-buffer spacing 0xE749C0 | - | - | `-` | two submit Frame* buffers alternate 0xE749C0 apart [I per BGFX_MAP 6b/6as; live-checked 6ij/6il]; constant — no instruction to quote | [I] |

## Sub-line states (pending parts only)

- M1c — [ ] open (dossier gaps). D2 dossiers exist for submit 0xe82e230, executor 0xe821120, flush 0xe81b720, PSO builder 0xe81e860, endFrame 0xc270460, generate 0xc273420, Context::init/frame/renderFrame 0xbc63690/0xbc66de0/0xbc63150, thread proc 0xbc65720, dispatch 0xe9002e0, shutdown 0xbc660a0 (per oc_U-EM1c.md census). Still missing: slot 58 init 0xe807ff0, slots 39-45 (incl. unnamed slot-45 target 0xe8189c0, size 0xa1), slots 7/10-34 partially, the 6 drain blocks of 0xbc660a0, the generate per-pass loop, 6cs header fields; then L4/L5 dossiers. Presence at RVA proven [V] above for the gap anchors.
- M1d — [ ] open (dossier gaps). All 21 thin insert clones D2 (one template); constructors and visitors D2. Extractors open: chunk 0x66ea3d0, BatchActor 0x66d9af0, ItemInHand 0x6698e30 (D1+, ranges verified [V] by oc_U-EM1d.md), particle 0x67417f0 (structure), weather 0x6745440 (head), clouds 0x67375a0 (structure); chunk/skinned/nametag extractors have no dossiers at all. Presence proven [V] above.
- M1e — [ ] open (dossier gaps). ScreenDraw path mapped (declare 0xbbbd3d0, build 0xbc37320, body 0xbc04dc0, submit 0xbcc38e0); ColorPostProcess in/out read. Remaining: non-ScreenDraw bodies (deferred 0xbc2cd20, voxel upload 0xbc0ac20, RTX driver 0xbc080c0, ClusterLights 0xbc5bad0, TAAU 0x56d4880, DoDeferredShading 0x56a06a0, plus further D0 lambdas per functions.tsv) — bodies and per-pass in/out resources unread. Presence proven [V] above.
- M3a — [ ] open. Headers + static_asserts exist for typed M2 structs; blocked by M2c open (35/62 description types untyped, oc_U-EM3a.md); SelfTest world-phase validation requires launching the game (rule 1) — not done. Anchor rows above have D2 dossiers; the gap is the validation run, not the RVAs.
- M3c — [ ] open (BLOCKED). TaskDispatchHook + dragon/Tasks.h written, never built or run — needs a build and an in-game test; forbidden by OPENCODE_BRIEF.md rules 1-2.
- M3d — [x] closed (recorded, not re-proven: oc_U-EM3d.md verify_oc 67/67).
- M3e — [ ] open. Header-to-record mapping incomplete (0xe82269e row above); in-game draw-edit test forbidden by rule 1.
- M3f — [ ] open. Custom-item seam 0xbc61560 present [V]; untested in game; needs M1c-M3e (rule 1).
- M4a-M4d — [x] all closed (recorded, not re-proven: oc_U-EM4a.md, oc_U-EM4b.md, oc_U-EN4b.md/oc_U-EO3b.md, oc_U-EO3c.md verify_oc 130/130).
- M1f — [ ] PARTIAL = NOT DONE. D3 live checks done for two passes only (0xE749C0 spacing row above [I], backbuffer 1920x1137 [V live] per prior work); every other D2 claim lacks a poll-only live read; out of scope for this static unit (rules 1-2).

## CLOSES?
CLOSES?: NO — single blocking fact: M3c (frame-graph pass add/remove/reorder via TaskDispatchHook + dragon/Tasks.h) was never built or run, and OPENCODE_BRIEF.md rules 1-2 forbid both the DLL build and the in-game test, so this acceptance capability can never be proven closed by static [V] verbatim-instruction rows in this note (M3e/M3f share the same in-game limit; M1f stays PARTIAL). R14 stays `[ ]`.

## TOOL REQUESTS
None
