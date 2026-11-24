# Native render verification protocol

Levels (spec section 8 of `docs/RENDER_NATIVE_SPEC.md`): L1 = statically complete (`liftcheck`), L2 = live-verified zero divergence, L3 = runs in Native mode.

## Per milestone gate (Xnz)
1. Orchestrator: batch build of the Release DLL (`tools/build_when_free.sh`); fix compile errors; sig anchors and layout lists generated from the per-function headers; `tools/sigs/layoutcheck.py` clean; `liftcheck` OK for every [x] item of the milestone.
2. In game (user), with `BS_REWRITE` / native modes set per the milestone section of `docs/BIGBANG_TESTS.md`: functions of the milestone in Verify mode (footprint differential, spec 8) over the scenes below. Zero divergence in every scene, no crash, `%APPDATA%\BlueySenseV2\diagnostics` report attached.
3. Mirror pushed; functions.tsv rows set to L2.

## Scenes (X0f per-function coverage: docs/data/native_scene_coverage.tsv)

First person in a world; third person with a mob in view; a visible nametag; rain/snow; particles (hit a mob, break a block); a held item and a block in hand; water/lava; a chest or sign (block entities); Vibrant Visuals on and off; a resource pack with a custom material; inventory and a menu screen; F1/hidden HUD; a dimension change; world join and leave; window resize; an RTX world if hardware allows. Each scene is at least 600 frames.

Per scene below: what must be on screen, the frame-path functions (docs/data/frame_path_functions.tsv) the scene exercises, and the coverage tag. The per-frame backbone runs in every scene: `RendererContextD3D12::submit` 0xe82e230, `BgfxFrameBuilder::endFrame` 0x66232b0 and `dragon::platform::BgfxContext::endFrame` 0xc270460 fire 1:1:1 per frame [V] (BGFX_MAP.md 6b), and the live submit target is the RTX override 0xe83d440 even on non-RTX hardware [V live, BGFX_MAP.md 6b]. The D3D12 draw executor 0xe821120, draw batch flush 0xe81b720, GraphicsTasks 0xc25fc50/0xe9002e0 and the bgfx render thread 0xbc65720 run in every scene [I]. Scene-specific inserts/extractors are [I]: inferred from the insert tag and visitor dispatch in the frame-path table, not from a live run (in-game confirmation deferred per the 2026-11-22 user decision; one big test covers all scenes).

| # | Scene | What must be on screen | Functions exercised (frame-path table) |
|---|---|---|---|
| 1 | first person world | terrain chunks at render distance, sky, hand, HUD | insert ChunkGeometry 0x15a6880, insert ChunkOccluders 0x5369920, insert BatchActor 0x4e39cb0 + extractor 0x66d9af0, blob shadows 0x53e6c30, clouds 0x53e88a0, sky/celestial 0x5369b30/0x5370b20/0x53707a0, terrain/chunk draw builder 0x66ea3d0, Item group wrapper+visitor 0x66466e0/0x6646980, light group 0x6640ae0/0x6640d80, sky group 0x6655de0/0x66560f0, backbone |
| 2 | third person with mob and nametag | player body in third person, a mob, the mob's nametag above its head | insert SkinnedMesh 0x6b84e60/0x4e39f20 + ctor 0x668d350, insert Nametag 0x1127330 + ctor 0x668b6e0, insert BatchActor 0x4e39cb0 + extractor 0x66d9af0 |
| 3 | rain/snow | falling precipitation | insert Weather 0x5ad5800 (Sky tag 9), effect group wrapper+visitor 0x666aa00/0x666aca0 |
| 4 | particles | hit particles on a mob, block break particles | insert Particle 0x5b8d520, insert BlitFlipbook 0x5acbe20, insert PlayerVision 0x53e62b0 |
| 5 | held item and block | held item/block in first-person hand, block highlight on the looked-at block | insert ItemInHand 0x531b180 + extractor 0x6698e30, insert BlockSelectionOverlayBlockEntity 0x539b7c0 + extractor 0x66e75f0, insert Crack 0x539fff0 while breaking |
| 6 | water/lava | water or lava block surface | terrain/chunk draw builder 0x66ea3d0 (water/lava chunks); with VV on also VV pass bodies 0x568bcd0/0x5699e30/0x56c8810 [I] |
| 7 | chest/sign | a chest or sign block entity (sign text readable) | insert BlockSelectionOverlayBlockEntity 0x539b7c0, BatchActor extractor 0x66d9af0 (block entities are batched actors), terrain/chunk draw builder 0x66ea3d0 |
| 8 | VV on and off | same world region with Vibrant Visuals toggled on vs off | VV on: VV frame-graph builder 0x55f1450, pass bodies A/B/C 0x568bcd0/0x5699e30/0x56c8810 (+ encode 0x568b9e0/0x5699be0/0x56c85c0); VV off: legacy/Fancy path via endFrame 0x66232b0 renderer selection; both: backbone |
| 9 | resource pack with custom material | a block/item drawn with the pack's custom .material.bin | MaterialLoader::load 0xe86b730, Material::deserialize 0xe870350, MaterialRepository::get/loadFile 0xc2919d0/0xc292a20 |
| 10 | inventory/menu | inventory screen or a menu (pause/settings) open | UI group wrapper+visitor 0x6664760/0x6664a00, insert UIMesh 0x4c96140, insert EnvironmentalText/UIText 0xe71330, RenderUITextDescription ctor 0x668c750, UI text renderer 0x674a3a0 |
| 11 | F1 / HUD hidden | debug overlay text on screen, normal HUD hidden | insert EnvironmentalText/UIText 0xe71330 (debug text); UI group 0x6664760/0x6664a00 still fires (HUD hidden is a UI-layer filter, not a frame-path skip) |
| 12 | dimension change | dimension transition (e.g. overworld <-> nether) completes | deferred texture/buffer transactions flush 0x6632bf0, ResourceLoader::processPending 0x6622610, loader merge 0xc288990, endFrame 0x66232b0 |
| 13 | world join/leave | join a world and leave back to the main menu | bgfx::Context::init 0xbc63690, Context::shutdown 0xbc660a0, Context::frame 0xbc66de0, Context::frame(capture) 0xbc65800 |
| 14 | window resize | window resized / render targets recreated | EncoderImpl::discard(reset) 0xbc60d10, createFrameBuffer(window) 0xe817880 |
| 15 | RTX world (if hardware allows) | DXR reflections on an RTX world | RTX submit override 0xe83d440 (slot 50 target) + base submit 0xe82e230 |

Editor-only inserts (Editor group tags 0-6) are exercised by none of the 16 scenes and are deliberately out of scope for this item.

## What counts as a divergence
Any byte of the declared footprint differing after the call, any difference in the sequence, arguments or return values of boundary calls, a different return value. Verify mode ends the process on the first one and logs function, scene, frame, offset, expected and actual.

## Whole-frame (L3)
`BS_NATIVE=on`: the roots run our code; compare draw records and the D3D12 call stream against the original run for the same scenes (`tools/sigs/drawstream_compare.py`), then a visual pass by the user.
