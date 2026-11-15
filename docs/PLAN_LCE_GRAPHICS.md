---
status: in-progress
phase: 3
updated: 2026-10-24
---

# Plan: LCE graphics (4J Xbox One look)

This is the working plan for the LCE graphics feature. It supersedes `C:\Users\Atomi\Downloads\lce-graphics-implementation-guide.md` (see Notes at the end).

## Goal

Render Minecraft Bedrock's world visually identical to 4J Studios' Legacy Console Edition (the Xbox One look), by swapping pipeline states, shaders, textures, the lightmap and post-processing on the bgfx/RenderDragon D3D12 path, toggleable at runtime, for personal use.

## Context & decisions

Two research sessions feed this plan: `ref:ses_e9ea16357ffelzK7pKGbi0CQSU` (4J source research, cited as `4J`) and `ref:ses_e9ea15404ffeCRKLC8X1i9tw48` (BlueySenseV2 architecture research, cited as `BSV2`).

| Decision | Rationale | Source |
|---|---|---|
| Strategy = twin-PSO/shader/state swap on the bgfx D3D12 path, extended to all MatRoles (not just terrain), not a full native renderer replacement | User directive: visually identical to 4J, staying on RenderDragon/bgfx. A native terrain replacement was considered and rejected. | user decision 2026-10-21 |
| SSR (source-to-shader reconstruction) approach: the 4J HLSL files do NOT exist in the LCE source tree | The entire platform backend (D3D11/GNM/D3D9 shaders) lives inside the closed `4J_Render.lib`. What survives is the full `C4JRender` interface (`4J_Render.h` per platform) plus all game-side rendering code. | ref:ses_e9ea16357ffelzK7pKGbi0CQSU |
| Reconstruct 4J's per-pixel math instead of extracting it | Terrain pixel shader reconstructs as: `out = atlasSample(rgb*a) * vertexColor * lightmap16x16 * gammaRamp`, fog linear or exp per `setupFog`, alpha-test for cutouts. Constants must come from porting the in-source generators, not guessing. | ref:ses_e9ea16357ffelzK7pKGbi0CQSU |
| Visual constants extracted by parsing the ACTUAL 4J source files (Python tools), not approximated: `GameRenderer::updateLightTexture` (`GameRenderer.cpp:860`), `Dimension::updateLightRamp` (`Dimension.cpp:24-32`, formula `brightnessRamp[i] = ((1-v)/(v*3+1))*(1-ambientLight)+ambientLight` with `v = 1-i/MAX_BRIGHTNESS`, gamma curve `r = 1-(1-r)^4` with a warm block-light tint in the gb/bb channels), `GameRenderer::setupFog` (`GameRenderer.cpp:1954`), water UV slope animation (`TileRenderer.cpp:3972-4244`) | These ARE in source; extract them exactly. | ref:ses_e9ea16357ffelzK7pKGbi0CQSU |
| Accept a known limit: RD vertex formats carry different baked data than LCE's (LCE bakes AO plus a 16x16 lightmap index per vertex in 32-byte quads; RD does not). The ported shaders reproduce the LCE look from RD's vertex data. This is visual identity, not pixel identity | Needed for staying on the bgfx path. | ref:ses_e9ea16357ffelzK7pKGbi0CQSU |
| Vibrant Visuals (deferred) is explicitly out of scope when LCE mode is on. VV requires d3d features the 4J-look forward path deliberately bypasses; the LCE module disables/ignores VV | User acknowledged: VV won't work with this renderer. | user decision 2026-10-21 |
| PSO classification is exact, not heuristic: `MaterialIndex.cpp` maps shader-blob FNV1a hashes to MatRole from `data/renderer/materials/*.material.bin` names. Reuse as-is | Measurements show it works for VV materials too (e.g. `EndSkyForwardPBR`). | ref:ses_e9ea15404ffeCRKLC8X1i9tw48 |

## Architecture facts (from ref:ses_e9ea15404ffeCRKLC8X1i9tw48)

The retention point already exists. `TrackerHooks.cpp` `createGraphicsPipelineState` at lines 178-206 sees the full `D3D12_GRAPHICS_PIPELINE_STATE_DESC` but discards it after distilling `PsoInfo`; that call is where twin-PSO building gets its inputs.

The substitution point is `TrackerHooks.cpp` `setPipelineState` at line 51 - a single atomic check, then a hash lookup, then possibly a different PSO.

`TrackerState.h` shapes the storage: `PsoInfo` lives at lines 15-23, the `sPsos`/`sViews` stores, and the thread-local first-call locking pattern at lines 45-60. The hot path locks once on first use and never again; that pattern must be respected.

Shader compilation is already solved by `UnderGpu`: a worker thread runs `D3DCompile` with a DXBC cache under `%APPDATA%\BlueySenseV2\shadercache`. The PSO key is (shader name, RTV format, samples, depth format). `pipeline()` returns null until the build is ready, so a frame never hitches, and `warm()` prefetches a known-upcoming build. LCE shader builds should ride this path.

Post-processing passes go through `UnderUI`/`UnderPass`: a `Layer` enum, `record()` and `wanted()`, with `FramePlan` analyze finding cut points; new passes register in `underui/passes/Passes.cpp`.

Modules follow the standard framework (`features/modules/Module.h`, one `Register.cpp` per category, e.g. `visuals/Register.cpp`), appear in the ClickGUI, and use the `PassSettings<Cfg>` publish pattern (mutex, written once per frame) to feed settings to passes.

The build is CMake with `file(GLOB_RECURSE)`, so adding a new `.cpp` requires re-running CMake configure. HLSL lives in `resources/shaders/*.hlsl` and is baked via `bs2_add_resource` in `cmake/Resources.cmake` (lines 47-56); `d3dcompiler_47` is DELAYLOADed, which is what makes runtime compile safe.

Not hooked yet, and all needed for Phase 4:

- `SetGraphicsRootDescriptorTable` (vtable slot 30 on the command list) - the terrain atlas SRV redirect.
- `CreateShaderResourceView` / `CreateSampler` - needed to validate and publish the swapped atlas texture.
- `BaseLightTextureImageBuilder::createBaseLightTextureData` - new signature in `src/sdk/Sigs.json`, hooked with `HOOK()` per `hooks/README.md`, to apply the LCE light curves when active.
- `ClientInstance::clearGraphicsCache` (OffsetProvider vtable 207) - forces the lightmap rebuild on toggle.

Hard constraints that cut across every phase:

- Hot hooks run on the game render/record thread thousands of times per frame: no per-call locks, no allocations, no logging.
- PSO/shader builds happen on the worker thread only.
- Resource barriers must be replayed for any render lists we skip or reorder.
- Eject (END key) runs the reverse shutdown; LCE teardown must release in an order that respects it.

## Phases

Status markers: Phases 1-2 complete, Phase 3 in progress; 3.1 is the current task, gated on the in-game layout dump.

### Phase 1: PSO retention + twin swap infrastructure [COMPLETE]

- [x] 1.1 Retain the full `D3D12_GRAPHICS_PIPELINE_STATE_DESC` plus shader bytecodes, input layout and semantic strings in `TrackerState.h`/`TrackerHooks.cpp`. Deep-copy semantics: pointers inside the desc may dangle after the call returns, so every pointed-at blob must be copied at retention time.
- [x] 1.2 Build `src/client/features/render/lce/LceRenderer.{h,cpp}`: `init(dev)`, `toggle(bool)`, `active()`, `twinOf(uintptr_t)`, `shutdown()`. A twin is a clone of the retained desc with VS/PS bytecode replaced by MatRole; root signature, input layout and RT formats are kept untouched.
- [x] 1.3 Substitute in `setPipelineState` when active: one atomic load + hash lookup per call, nothing else on the hot path.
- [ ] 1.4 Proof-of-life: swap the Terrain PSO with a flat magenta shader before any 4J port. If the world goes magenta, the infrastructure works end to end. Flat magenta PS is written, baked (sh_lce_flat) and substituted; awaiting one in-game run to confirm the world turns magenta.
- [x] 1.5 `LceGraphics` module in `features/modules/visuals/`, registered in `visuals/Register.cpp`, toggled from the ClickGUI.
- [x] 1.6 Diagnostics in `LceRenderer`: build summary (retained/eligible/built/failed/device), per-retained-PSO dump (role, hashes, formats, depth/blend, input-layout string, 40 cap), and once-per-PSO miss logging on the substitute path; hot found-twin path stays two loads + one hash lookup.

### Phase 2: Vendored 4J reference sources [COMPLETE]

The 4J sources are vendored at `src/sdk/lce/reference/` (the allowlist below) and are the direct reference for porting; they are excluded from the build.

- [x] 2.1 Read `GameRenderer.cpp` `updateLightTexture` and `Dimension.cpp` `updateLightRamp`, and port the light-curve constants into `LceLightmap.{h,cpp}`.
- [x] 2.2 Read `setupFog` for the per-condition fog formula and parameters.
- [x] 2.3 Read the water slope-UV animation constants (`TileRenderer.cpp:3972-4244`) for the water shader port.

Vendored allowlist: `Minecraft.Client/` (GameRenderer, LevelRenderer, Chunk, Tesselator, TileRenderer, Textures, Options, ParticleEngine, glWrapper), `Minecraft.Client/Windows64/` and `Minecraft.Client/Durango/` (platform Minecraft.cpp + `4JLibs/inc/4J_Render.h`), and `Minecraft.World/` (Dimension, LiquidTile, Level, Tile, Biome, LevelChunk, ChunkSource).

Vendored at `src/sdk/lce/reference/` (34 files, SHA-256 verified), excluded from the build by a CMake filter scoped to that subtree only, and excluded from `tools/check.py`'s scans (its console headers were being hoisted into `Pch.h`; those three includes were removed). The rest of `src/sdk` remains in the build.

### Phase 3: Shader port per MatRole (resources/shaders/lce_*.hlsl, SM compile via the existing UnderShaders pattern) [IN PROGRESS]

Blocked on the layout dump from one in-game run: toggle LCE Graphics and capture the '[lce] retained pso ...' lines; each role's input layout and register bindings come from those lines.

- [ ] **3.1 (CURRENT)** Terrain (`lce_terrain`)
- [ ] 3.2 Entity / held item (`lce_entity`)
- [ ] 3.3 Clouds (`lce_clouds`)
- [ ] 3.4 Water (`lce_water`)
- [ ] 3.5 Weather / particle (pass or port)

Sky, sun/moon and stars are handled by the existing SkyPass/SkyInject, tuned to the 4J look. UI is never swapped.

Constraint for every shader: match the RD PSO's input layout and register bindings exactly, logged from the retained `PsoDesc` per MatRole. All ported shaders must compile to the game's container kind (DXIL/SM6 via DXC; DXBC/SM5 via FXC fallback for sm5 PSOs) — a PSO mixing DXBC and DXIL stages is rejected with E_INVALIDARG.

### Phase 4: Atlas + lightmap [PENDING]

- [ ] 4.1 Hook `SetGraphicsRootDescriptorTable` (vtable slot 30, added in `CommandListTracker::init` at `TrackerHooks.cpp:267-305`) and identify the terrain atlas SRV on terrain draws.
- [ ] 4.2 `tools/lce` `build_atlas.py`: remap the 4J block textures into Bedrock's `terrain_texture.json` UV layout, mipmaps with a box filter.
- [ ] 4.3 Upload the `ID3D12Resource` on first toggle; swap the GPU handle when the game binds the atlas.
- [ ] 4.4 `Sigs.json` entry + `LightmapHook.cpp` for `BaseLightTextureImageBuilder::createBaseLightTextureData`; apply the LCE curves when active; force rebuild via `clearGraphicsCache` (vtable 207) or mark chunks dirty.

### Phase 5: Fog + tone mapping UnderPasses [PENDING]

- [ ] 5.1 `LceFogPass` (`Layer::Fog`, needsDepth, `wanted()` = active): linear distance fog with the 4J parameters from Phase 2.
- [ ] 5.2 `LceTonePass` (`Layer::PostScene`): 4J gamma/warmth/shadow lift, either analytical or a 32^3 3D LUT.

Respect the `kMbBudgetMs`-style budget pattern; both passes skip their work when nothing changed and `wanted()` returns false while LCE is off.

### Phase 6: Toggle system + validation [PENDING]

- [ ] 6.1 Toggle ordering: build twins (~100 ms) then atlas upload, activate the atomic, rebuild the lightmap, enable passes via `wanted()`. Reverse the order on off.
- [ ] 6.2 Test matrix: toggle on/off in world, 50x toggle stability, VV+LCE behavior (VV must lose), MSAA, resize, world/dimension change, F5, A/B FPS, side-by-side against real Xbox One Edition captures.

Risk register:

- Vertex-format mismatch: log layouts first (Phase 3 constraint) before writing shaders.
- Root signature incompatibility: never change the game's root signature; twins reuse it as-is.
- Pre-injection PSOs: PSOs created before the hook exists - build twins lazily via `GetCachedBlob`, or skip those draws.
- Atlas rebuild on resource pack change: re-learn the binding when the pack swaps.
- COM leak: shutdown releases every retained desc, bytecode and twin PSO.

## Notes

The 2026-10-21 revised plan (this document) supersedes the antigravity guide doc `C:\Users\Atomi\Downloads\lce-graphics-implementation-guide.md`. Source exploration proved the guide's Phase 2 extraction assumption (HLSL files present in the 4J tree) false - the platform shaders live in the closed `4J_Render.lib` - and the user chose the all-MatRole bgfx-path scope over a native renderer replacement. Treat this document as the single plan going forward; the guide remains only as historical background.

2026-10-22: Phase 1 code complete (retention, twin builder, substitution, flat PS, toggle module). Full build verification is currently blocked by another agent's concurrent `Setting.h`/`Module.h` mismatch and unrelated in-progress errors; our TUs (`LceRenderer`, `TrackerHooks`) compile cleanly and `sh_lce_flat` bakes.

2026-10-22: 4J renderer sources vendored (not value-extracted) into `src/sdk/lce/reference/` per user direction; allowlist covers renderer + platform init + light/water/world dependencies.

2026-10-22: `tools/check.py` now skips the reference subtree; `Pch.h`'s injected `<agile.h>`/`<xmcore.h>`/`<xuiapp.h>` removed.

2026-10-24: the layout dump turned out unnecessary. RenderChunk.material.bin holds the game's real DXIL; disassembled through dxcompiler (Disassemble), the terrain pixel shaders are 20 programs in a few families - atlas (t1) x vertex tint (COLOR0) x light map (t0, TEXCOORD1) mixed to a fog colour in cb1 by COLOR2.w, with variants for alpha test, tint-through-atlas-alpha, chunk-fade dither and seasons. `LceTerrain` (lce/LceTerrain.cpp) now writes the twin pixel shader as HLSL per game pixel shader: the input block is read from the game shader's ISG1 chunk and repeated in order, which packs to the identical signature (checked by compiling and comparing), and the body swaps the light map lookup for 4J's `updateLightTexture`/`updateLightRamp` math. Reproduced: the opaque, cutout and tinted variants (no chunk-fade dither, as LCE had none). Left to the game: seasons, translucent (water, glass), depth-only. Twins for states created after the toggle join the table (`LceRenderer::onStateCreated`). Entities, held items, clouds, particles, water and the fog/tone passes (phases 3.2-3.5, 5) are not done. The debug views are generated per variant (Debug View on the module): Lightmap UV and Vanilla Lightmap show which axis of TEXCOORD1 is block and which is sky light (assumed x block, y sky; one line in `lceLight`).
# Status note (2026-10-30)

This plan predates the current rollback of the signature-changing terrain shader experiment. For current implementation coverage, known unsupported material hashes, and remaining visual-match gaps, see [LCE_GRAPHICS_GAPS.md](LCE_GRAPHICS_GAPS.md). Do not treat phase completion notes below as confirmation that the current game build is covered.

