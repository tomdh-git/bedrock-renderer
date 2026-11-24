# Native render verification protocol

Levels (spec section 8 of `docs/RENDER_NATIVE_SPEC.md`): L1 = statically complete (`liftcheck`), L2 = live-verified zero divergence, L3 = runs in Native mode.

## Per milestone gate (Xnz)
1. Orchestrator: batch build of the Release DLL (`tools/build_when_free.sh`); fix compile errors; sig anchors and layout lists generated from the per-function headers; `tools/sigs/layoutcheck.py` clean; `liftcheck` OK for every [x] item of the milestone.
2. In game (user), with `BS_REWRITE` / native modes set per the milestone section of `docs/BIGBANG_TESTS.md`: functions of the milestone in Verify mode (footprint differential, spec 8) over the scenes below. Zero divergence in every scene, no crash, `%APPDATA%\BlueySenseV2\diagnostics` report attached.
3. Mirror pushed; functions.tsv rows set to L2.

## Scenes (X0f per-function coverage: docs/data/native_scene_coverage.tsv)

First person in a world; third person with a mob in view; a visible nametag; rain/snow; particles (hit a mob, break a block); a held item and a block in hand; water/lava; a chest or sign (block entities); Vibrant Visuals on and off; a resource pack with a custom material; inventory and a menu screen; F1/hidden HUD; a dimension change; world join and leave; window resize; an RTX world if hardware allows. Each scene is at least 600 frames.

Per scene below: what must be on screen, the frame-path functions (docs/data/frame_path_functions.tsv) the scene exercises, and the coverage tag. The per-frame backbone runs in every scene: `RendererContextD3D12::submit` 0xe82e230, `BgfxFrameBuilder::endFrame` 0x66232b0 and `dragon::platform::BgfxContext::endFrame` 0xc270460 fire 1:1:1 per frame [V] (BGFX_MAP.md 6b), and the live submit target is the RTX override 0xe83d440 even on non-RTX hardware [V live, BGFX_MAP.md 6b]. The D3D12 draw execut