## NEXT
DONE - all deliverables on disk; delegate.py check exit 0; verify_oc clean

# U-EX0f - X0f Live scene list and capture recipes (Minecraft.Windows.exe 1.26.62.01)

## GOAL

Close checklist item X0f: write docs/NATIVE_VERIFY_PROTOCOL.md section "Scenes" with, per scene (first person world, third person with mob and nametag, rain/snow, particles, held item and block, water/lava, chest/sign, VV on and off, resource pack with custom material, inventory/menu, F1, dimension change, join/leave, resize, RTX if available), what must be on screen and which functions it exercises (from the frame-path table), so each lifted function can be assigned to at least one scene. Output: docs/data/native_scene_coverage.tsv (function id, scenes that execute it, [V]/[I]). Deferred in-game testing per the 2026-11-22 user decision (one big in-game test later; not a reason for CLOSES? NO).

## SCENES — docs/NATIVE_VERIFY_PROTOCOL.md section "Scenes" (written)

Expanded the existing "Scenes" section into a 15-row scene table plus an RTX row: per scene, what must be on screen and the frame-path functions it exercises. Per-frame backbone [V]: RendererContextD3D12::submit 0xe82e230, BgfxFrameBuilder::endFrame 0x66232b0 and dragon::platform::BgfxContext::endFrame 0xc270460 fire 1:1:1 per frame [V] (BGFX_MAP.md 6b); the live submit target is the RTX override 0xe83d440 even on non-RTX hardware [V live, BGFX_MAP.md 6b]. The D3D12 draw executor 0xe821120, draw batch flush 0xe81b720, GraphicsTasks 0xc25fc50/0xe9002e0 and the bgfx render thread 0xbc65720 run in every scene [I]. Scene-specific inserts/extractors are [I]: inferred from the insert tag and visitor dispatch in the frame-path table (orchestrator input data), not from a live run. Editor-only inserts (Editor group tags 0-6) are exercised by none of the 16 scenes and are out of scope.

## COVERAGE — docs/data/native_scene_coverage.tsv (written)

56 rows: function id (RVA from docs/data/frame_path_functions.tsv), scenes that execute it (scene codes fp/tp/weather/particles/held/fluid/blockent/vv/rp/menu/f1/dim/joinleave/resize/rtx/all), [V]/[I]. Every lifted frame-path function is assigned to at least one scene. Backbone rows scenes=all [V]; scene-specific insert/extractor/material/loader/resize/joinleave rows [I].

## FILES CHANGED / CREATED

- docs/NATIVE_VERIFY_PROTOCOL.md (edited: section Scenes expanded with per-scene table)
- docs/data/native_scene_coverage.tsv (created)
- docs/BIGBANG_TESTS.md (appended: U-EX0f section)
- docs/progress/oc_U-EX0f.md (this file)

## PROOF ROWS (function identity at each RVA verified verbatim against the exe with `rdis dis`; copied from rdis output, not retyped)

| offset | size | site | instr | meaning | tag |
| 0x1127330 | 0x2c6 | `0x1127330  push rbp` | insert<RenderNametagDescription> thin clone entry | nametag insert exists at RVA | [V] |
| 0x15a6880 | 0x139 | `0x15a6880  push rbp` | insert<ChunkGeometry> thin clone entry (Item tag 3) | terrain insert exists at RVA | [V] |
| 0x4e39cb0 | 0x139 | `0x4e39cb0  push rbp` | insert<BatchActor> thin clone entry (Item tag 10) | actor batch insert exists at RVA | [V] |
| 0x531b180 | 0x139 | `0x531b180  push rbp` | insert<ItemInHand> thin clone entry (Item tag 6) | held-item insert exists at RVA | [V] |
| 0x5ad5800 | 0x139 | `0x5ad5800  push rbp` | insert<Weather> thin clone entry (Sky tag 9) | weather insert exists at RVA | [V] |
| 0x5b8d520 | 0x139 | `0x5b8d520  push rbp` | insert<Particle> thin clone entry (Effect tag 2) | particle insert exists at RVA | [V] |
| 0x539fff0 | 0x996 | `0x539fff0  push rbp` | insert<RenderCrackDescription> entry (Item tag 5) | crack insert exists at RVA | [V] |
| 0x66d9af0 | 0x8bb7 | `0x66d9af0  push rbp` | BatchActor extractor entry | batch-actor extractor exists at RVA | [V] |
| 0x6698e30 | 0x5fb4 | `0x6698e30  push rbp` | ItemInHand extractor entry | held-item extractor exists at RVA | [V] |
| 0x66ea3d0 | 0xf430 | `0x66ea3d0  push rbp` | terrain/chunk draw builder entry | chunk draw builder exists at RVA | [V] |
| 0x66232b0 | 0xb3d0 | `0x66232b0  push rbp` | BgfxFrameBuilder::endFrame entry | endFrame exists at RVA [V per-frame] | [V] |
| 0x55f1450 | 0x4e144 | `0x55f1450  push rbp` | VV frame-graph builder entry | VV builder exists at RVA | [V] |
| 0xe82e230 | 0x4d91 | `0xe82e230  push rbp` | RendererContextD3D12::submit (slot 50) entry | submit exists at RVA [V per-frame] | [V] |
| 0xe83d440 | 0x381 | `0xe83d440  push r14` | RendererContextD3D12 RTX submit override (slot 50) entry | RTX submit override exists at RVA [V live target] | [V] |
| 0xe821120 | 0xc3c3 | `0xe821120  push rbp` | D3D12 draw executor entry | draw executor exists at RVA | [V] |
| 0xc270460 | 0x2aa | `0xc270460  push rbp` | dragon::platform::BgfxContext::endFrame entry | dragon endFrame exists at RVA [V per-frame] | [V] |
| 0xbc60d10 | 0x1fc | `0xbc60d10  push r14` | EncoderImpl::discard (reset) entry | reset exists at RVA | [V] |
| 0xe817880 | - | `0xe817880  push r15` | createFrameBuffer(window) entry | window framebuffer creation exists at RVA | [V] |
| 0xbc63690 | - | `0xbc63690  push rsi` | bgfx::Context::init entry | bgfx init exists at RVA | [V] |
| 0xbc66de0 | 0x19d7 | `0xbc66de0  push rbp` | bgfx::Context::frame (swap/handoff prep) entry | Context::frame exists at RVA | [V] |
| 0x6632bf0 | 0x34b | `0x6632bf0  push rbp` | deferred texture/buffer transactions flush entry | deferred flush exists at RVA | [V] |
| 0xc25fe20 | 0x1e0 | `0xc25fe20  push rbp` | GraphicsTasks task runner entry | task runner exists at RVA | [V] |
| 0x568cd90 | 0x615 | `0x568cd90  push rbp` | Scene/HUD view-setup task body entry | view-setup task exists at RVA | [V] |
| 0x568bcd0 | 0xc4 | `0x568bcd0  push rbp` | pass body A entry | VV pass body exists at RVA | [V] |
| 0x674a3a0 | - | `0x674a3a0  push rbp` | UI text renderer (UI/Text, UI/Glint) entry | UI text renderer exists at RVA | [V] |

Notes: sizes are from docs/data/frame_path_functions.tsv where the function is listed there ("-" otherwise). The [V] tag on proof rows proves the function exists at the RVA; per-frame rows additionally cite BGFX_MAP.md 6b live 1:1:1 firing. Scene-to-function linkage for insert/extractor rows is [I] (inferred from frame-path role), as documented in the TSV.

## TOOL REQUESTS

None.

## CLOSES?

CLOSES? YES — every on-disk part of X0f is complete: docs/NATIVE_VERIFY_PROTOCOL.md section "Scenes" (per-scene screen content + frame-path functions for all 15 scenes plus RTX), docs/data/native_scene_coverage.tsv (56 rows; each lifted frame-path function assigned to at least one scene; backbone [V], scene-specific [I]), docs/BIGBANG_TESTS.md appended with the U-EX0f section (item id, what to enable, exact in-game steps, expected observable result). No build or game launch is required for this item (hard rules: static analysis only; static documentation item), and the deferred in-game run per the 2026-11-22 user decision is not a reason for CLOSES? NO. No unknown RVA/offset/meaning remains blocking: every scene->function link is explicitly tagged [I] inference from the frame-path table, never claimed as fact.
