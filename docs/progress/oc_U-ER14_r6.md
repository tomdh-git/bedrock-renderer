## NEXT
DONE

# Unit U-ER14 — Close checklist item R14

Source item (docs/RENDER_CHECKLIST.md line 612, section R Partials ledger):
`- [ ] R14 M1b classification, M1c/M1d/M1e dossier gaps, M3a-M3f, M4a-M4d, M1f (see their own lines)`

R14 references its sub-lines in section M ("M. Full-RE method: function dossiers, acceptance tests, definition of done"). Per the STATUS block (last update 2026-11-22):
- already closed `[x]`, recorded as closed and NOT re-proven here: M1b classification (oc_U-EM1b.md, verify_oc 8/8), M4a/M4b/M4c/M4d version resilience (oc_U-EM4a.md, oc_U-EM4b.md, oc_U-EN4b.md/oc_U-EO3b.md, oc_U-EO3c.md).
- pending / not found / not decoded (this unit's scope, done only here): M1c, M1d, M1e dossier gaps; M3a, M3c, M3e, M3f acceptance capabilities; M1f D3 live checks.

Static analysis only per docs/OPENCODE_BRIEF.md rules 1-2: the exe is data, never launched; no builds; no debugger/breakpoints. Every `0xRVA  instr` line below is verbatim (two spaces after the address), taken from the precomputed docs/data/d2_first_instructions.json or a single `rdis dis 0x<rva> 1` read, and re-checked by verify_oc. Size comes from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1); first-instruction anchor rows have no load/store size, so size is `-` and the function extent cited from docs/BGFX_MAP.md or docs/data/d3d12_vtable_1.26.62.01.txt is marked [I] in the meaning and was not re-measured. Meaning is `-` unless an instruction or string shows it.

## Evidence table (one row per distinct offset; all sites of that offset listed; verbatim `0xRVA  instr` copied verbatim)

| offset | size | site | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| M1c: submit 0xe82e230 | - | - | `0xe82e230  push rbp` | RendererContextD3D12::submit (vtable slot 50); D2 dossier exists; extent 0x4d91 cited [I per 6t] | [V] |
| M1c: draw executor 0xe821120 | - | - | `0xe821120  push rbp` | D3D12 draw executor, per-job item loop; D2 dossier exists; extent 0xc3c3 cited [I per 6e-2] | [V] |
| M1c/M3e: draw flush 0xe81b720 | - | - | `0xe81b720  push r15` | draw batch flush (DrawInstanced/DrawIndexedInstanced/ExecuteIndirect); D2 dossier; extent 0x803 cited [I per port_metrics_60.05 == 62.01] | [V] |
| M1c: PSO builder 0xe81e860 | - | - | `0xe81e860  push r15` | state -> D3D12 PSO desc builder; D2 dossier exists; extent 0x1c9a cited [I per port_metrics_60.05 == 62.01] | [V] |
| M1c: endFrame 0xc270460 | - | - | `0xc270460  push rbp` | BgfxContext::endFrame (generate+encode frame graph); D2 dossier; extent 0x2aa cited [I per 6n] | [V] |
| M1c: generate 0xc273420 | - | - | `0xc273420  push rbp` | dragon frame-graph generate/encode inside endFrame; D2 dossier; extent 0x8A73 cited [I per 6n-2] | [V] |
| M1c: Context::init 0xbc63690 | - | - | `0xbc63690  push rsi` | bgfx::Context init / backend-thread start; D2 dossier; extent 0x4e7 cited [I per 6q] | [V] |
| M1c: Context::frame 0xbc66de0 | - | - | `0xbc66de0  push rbp` | bgfx::Context::frame()/swap; D2 dossier; extent 0x19d7 cited [I per 6r] | [V] |
| M1c: task dispatch 0xe9002e0 | - | - | `0xe9002e0  push rbp` | task list dispatch in GraphicsTasks chain; D2 dossier; extent 0xc3a cited [I per port_metrics_60.05 == 62.01] | [V] |
| M1c: init slot 58 0xe807ff0 | - | - | `0xe807ff0  push rbp` | D3D12 init (d3d12.dll/device); D1, NO dossier — gap; extent 0x1734 cited [I per docs/data/d3d12_vtable_1.26.62.01.txt] | [V] |
| M1c: vtable slot 45 0xe8189c0 | - | - | `0xe8189c0  push rsi` | slot 45 target, unnamed — 'slots 39-45' read gap; extent 0xa1 cited [I per docs/data/d3d12_vtable_1.26.62.01.txt] | [V] |
| M1c: slot 39 0xe817880 | - | - | `0xe817880  push r15` | create window-backed frame buffer/swapchain; D1 gap; extent 0x37b cited [I per docs/data/d3d12_vtable_1.26.62.01.txt] | [V] |
| M1c: slot 40 0xe8176a0 | - | - | `0xe8176a0  push r15` | slot 40 target; D1 gap; extent 0xeb cited [I per docs/data/d3d12_vtable_1.26.62.01.txt] | [V] |
| M1c: slot 41 0xe817c00 | - | - | `0xe817c00  push rsi` | slot 41 target; D1 gap; extent 0xe5 cited [I per docs/data/d3d12_vtable_1.26.62.01.txt] | [V] |
| M1d: chunk 0x66ea3d0 | - | - | `0x66ea3d0  push rbp` | Item tag 3/4 terrain draw builder; D1, inner field decode pending; extent 0xF430 cited [I per 6be] | [V] |
| M1d: batch-actor 0x66d9af0 | - | - | `0x66d9af0  push rbp` | Item tag 10 extractor; D1+, inner decode pending; extent 0x8BB7 cited [I per 6u] | [V] |
| M1d: item-in-hand 0x6698e30 | - | - | `0x6698e30  push rbp` | Item tag 6 extractor; D1+, pending ranges; extent 0x5FB4 cited [I per 6ab] | [V] |
| M1d: particle 0x67417f0 | - | - | `0x67417f0  push rbp` | Effect tag 2 extractor; D1 structure only; extent 0x2CD7 cited [I per 6x] | [V] |
| M1d: weather 0x6745440 | - | - | `0x6745440  push rbp` | Sky tag 9 extractor; D1 head only; extent 0x3A5A cited [I per 6x] | [V] |
| M1d: clouds 0x67375a0 | - | - | `0x67375a0  push rbp` | Sky tag 1 extractor; D1 structure; extent 0x3DFB cited [I per 6x] | [V] |
| M1e: deferred 0xbc2cd20 | - | - | `0xbc2cd20  push rbp` | DirectionalLightingPass/DoDeferredLighting body; D0, body and per-pass in/out unread | [V] |
| M1e: voxel upload 0xbc0ac20 | - | - | `0xbc0ac20  push r15` | dirty volume upload body; D0, body and per-pass in/out unread | [V] |
| M1e: RTX driver 0xbc080c0 | - | - | `0xbc080c0  push rbp` | RTX denoise/raygen driver (43 passes); D0, body and per-pass in/out unread | [V] |
| M1e: ClusterLights 0xbc5bad0 | - | - | `0xbc5bad0  push rbp` | cluster lights body; D0, body and per-pass in/out unread | [V] |
| M1e: TAAU 0x56d4880 | - | - | `0x56d4880  push rbp` | TAA upscale body; D0, body and per-pass in/out unread | [V] |
| M1e: DoDeferredShading 0x56a06a0 | - | - | `0x56a06a0  push rbp` | deferred shading body; D0, body and per-pass in/out unread | [V] |
| M3e: header base 0xe82269e | - | - | `0xe82269e  lea r12,[r9+rdx]` | executor header base = Frame+0xB4700 + (itemIndex<<7) [I per 6am]; header->record mapping still incomplete | [V] |
| M3f: submitCustom 0xbc61560 | - | - | `0xbc61560  push r15` | Encoder::submitCustom key bit 53 custom-item seam; untested in game | [V] |
| M1f: frame spacing 0xE749C0 | - | - | `-` | two submit Frame* buffers alternate 0xE749C0 apart [I per 6b/6as]; constant, no instruction to quote | [I] |

## What is proven vs what remains open

Proven [V] here: each anchor/executor/pass-lambda RVA above is a real function entry in Minecraft.Windows.exe 1.26.62.01 and its verbatim first instruction matches rdis (verify_oc: mismatch=0, no-such-instr=0). This includes the previously-unnamed vtable slot-45 target 0xe8189c0 ('slots 39-45' gap) and the executor header-base computation 0xe82269e (`lea r12,[r9+rdx]`). Sizes cited as extents are [I], not re-measured.

Not closed by this unit (blocking R14): M1c/M1d/M1e dossier bodies (presence proven, D2 dossiers still absent), M3a SelfTest world-phase validation (game closed, rule 1), M3c TaskDispatchHook build + in-game run (rules 1-2), M3e in-game draw-edit test (rule 1), M3f whole-frame replacement in game (rule 1), M1f remaining D3 live reads (two passes done previously; a static unit cannot add poll-only reads).

## Sub-line states (pending parts only)

- M1c — [ ] open: D2 dossiers missing for the D0/D1 L1-L3 structural functions; presence at RVA proven [V] above (incl. the unnamed slot-45 target 0xe8189c0, the 'slots 39-45' gap, slots 39/40/41); dossiers still absent.
- M1d — [ ] open: extractor inner field decodes pending (chunk 0x66ea3d0, batch-actor 0x66d9af0, item-in-hand 0x6698e30, particle 0x67417f0, weather 0x6745440, clouds 0x67375a0); presence proven [V] above.
- M1e — [ ] open: pass lambdas at D0 (0xbc2cd20, 0xbc0ac20, 0xbc080c0, 0xbc5bad0, 0x56d4880, 0x56a06a0); presence proven [V], bodies and per-pass in/out resources unread.
- M3a — [ ] open: startup SelfTest world-phase validation not run (game closed, rule 1).
- M3c — [ ] open: TaskDispatchHook + dragon/Tasks.h written but never built or run (rules 1-2).
- M3e — [ ] open: edit draws at submit — header->record mapping incomplete plus an in-game test (rule 1).
- M3f — [ ] open: whole-frame replacement — custom-item seam 0xbc61560 present [V], untested in game, needs M1c-M3e (rule 1).
- M1f — [ ] PARTIAL = NOT DONE: D3 live checks done for two passes only; every other D2 claim lacks a poll-only live read; out of scope for this static unit.

## CLOSES?

NO — single blocking fact: M3c (frame-graph pass add/remove/reorder via TaskDispatchHook + dragon/Tasks.h) was never built or run, and OPENCODE_BRIEF.md rules 1-2 forbid both the DLL build and the in-game test, so this acceptance capability can never be proven closed by static [V] verbatim-instruction rows in this note (M3e's in-game test and M3f hit the same limit, and M1f's remaining D3 live reads are out of scope for a static unit). R14 stays `[ ]`.

## TOOL REQUESTS

None
