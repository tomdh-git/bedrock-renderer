---
status: proposed
phase: 0
updated: 2026-11-09
---

# Plan: optimization overhaul (regular renderer, no Vibrant Visuals)

## Goal

2-3x frame rate at high render distance with little visible change, by hooking the game's chunk, culling, entity and
draw paths and replacing the expensive parts with our own. Target build: 1.26.62 (`GameVersion.h`), d3d12 backend.

## What a 2-3x gain can and cannot mean

- At render distance 24+ the frame is bound by terrain: draw count (one draw per sub chunk per layer), vertex count of
  far chunks, and the per-chunk CPU work that feeds them (cull, queue, frame builder insert, bgfx submit and encode).
  This is where LOD and batching give 2-3x.
- On a GPU-bound machine at any render distance, rendering the scene at 67% and upscaling gives about 1.5-2x.
- At render distance 8-12 on a server the game is already cheap and none of this gives 2x. Servers cap the view
  distance, so there the far-LOD cache (phase 5) is a visual feature (see further), not a speed feature.
- Nothing is assumed. Phase 0 measures where the time goes; each later phase is kept only if it shows a gain in the
  same benchmark.

## What LeviLamina gives us (Desktop/LeviLamina-26.51)

Headers under `src/mc/client/renderer` are empty stubs. The real layouts are under `src-client/mc/client/renderer`:

| Class | Header | What is usable |
|---|---|---|
| `LevelRenderer` | `game/LevelRenderer.h` | `mRenderChunkCoordinators` (per dimension), `mLevelBuilder` (1456 bytes, opaque), `mLevelRendererPlayer`, `mParticleEngine`, `mAtlasTexture` |
| `LevelRendererCamera` | `game/LevelRendererCamera.h` | `mViewArea` (`GridArea<shared_ptr<RenderChunkInstanced>>`), `mLevelCuller`, `mFrustumCuller`, `mFarChunksDistance`, `mRenderDistance`, `mCullEndDistance`, `mMaxInflightChunks`, fog fields, `mActorRenderQueue`, block actor queues; functions `queueChunk`, `_addToRenderChunkQueue(.., TerrainLayer, TerrainLayerLOD, ..)`, `cullerIsVisible`, `isAABBVisible`, `shouldCullThisFrame`, `updateFarChunksDistance`, `updatePerChunkFaceSortState`, `queueRenderEntities`, `_tryInsertBlockEntityIntoRenderQueues` |
| `RenderChunkCoordinator` | `chunks/RenderChunkCoordinator.h` | `mRenderChunkSharedMap` (`SubChunkPos -> weak_ptr<RenderChunkShared>`), `_setDirty(min, max, immediate, changesVisibility, canInterlock)`, `_launchVisibilityRebuild`, `tick`, block/chunk listener callbacks |
| `RenderChunkShared` | `chunks/RenderChunkShared.h` | `mEmpty`, `mPosition`, `mCurrentRenderChunkGeometry`, build states, `startRebuild`, `endRebuild` |
| `RenderChunkInstanced` | `chunks/RenderChunkInstanced.h` | `mDistanceFromCamera2`, `mChunkBuildPriority`, `mFallbackToUnsorted`, current index buffer + 22 layer ranges, `onPerspectiveCameraMoved`, `_startSortCommon`, `endSort` |
| `RenderChunkGeometry` | `chunks/RenderChunkGeometry.h` | `mMeshData` (`mce::Mesh` or `RenderChunkDirectVertexData`), `mRenderLayerIndexRanges[22]`, `mDataBounds`, flags, `rebuild`, `endRebuild` |
| `RenderChunkBuilder` | `chunks/RenderChunkBuilder.h` | `build(geometry, transparentLeaves, lightingType, ..)`, block queues per layer, `mBuiltMesh`, `mMeshData` |
| `BlockTessellator`, `AmbientOcclusionCalculator`, `BlockTessellatorCache` | `block/` | function names only matter (hook points) |
| `ParticleEngine`, `ActorRenderDispatcher`, `BlockActorRenderDispatcher` | `particle/`, `actor/`, `blockactor/` | `_emitParticleNew`, `render`, `tick` |

World side (`src/mc/world/level/chunk`) is complete: `LevelChunk` (`mSubChunks`, `mRenderHeightmap`, `mBiomes`),
`SubChunk` (`mBlocksReadPtr`, light storage, `isUniform`), `SubChunkStoragePaletted` (`getPackedElement`,
`getPaletteSnapshot`). `ChunkBlockView`/`ChunkBlocks` already read these.

Still empty in LeviLamina, so they come from the binary: `LevelCuller*`, `LevelBuilder` internals, `VisibilityNode`,
`RenderChunkQuadInfo`, `RenderChunkGeometryDescription::PerChunkData`, `mce::Mesh` to bgfx handle to D3D12 buffer.

Limits: the headers are for 1.26.51, the target is 1.26.62. Every offset used is proven with
`tools/sdkgen/check_offsets.py`; function addresses come from `tools/sigs/xref.py` (the game keeps function names in
assert strings, e.g. `RenderChunkCoordinator::_launchVisibilityRebuild`) and go in `Sigs.json`.

## Phases

### Phase 0: measure (first, about 2 days)

- Timing hooks (rdtsc, no locks, no logging on the hot path) on: `LevelRendererCamera::preRenderUpdate` and `render`,
  the culler step, `queueChunk`, `RenderChunkBuilder::build`, `RenderChunkInstanced::_startSortCommon`/`endSort`,
  `RenderChunkCoordinator::tick`, `ActorRenderDispatcher::render`, `ParticleEngine::render`, bgfx frame, Present.
- Counters already available from `CommandListTracker`/`MaterialIndex`: draws, indices and lists per `MatRole` per
  frame. GPU time from the `UnderGpu` timers.
- A `Perf` module: HUD and a 30 s CSV capture. Benchmark = fixed flat-seed and normal-seed worlds, fixed position
  and fixed camera path, render distance 12 / 24 / 48, plus one busy server lobby.
- Result: a table of ms per stage. It decides the order of phases 2-5.

### Phase 1: knobs the game already has (about 3-4 days)

No new rendering, only hooks and fields from the table above.

- Far-chunk shader LOD: the game already draws far chunks with a cheaper `TerrainLayerLOD`; pull
  `mFarChunksDistance` in (setting).
- Transparent face sorting: stop re-sorting beyond N chunks (`mFallbackToUnsorted`, `updatePerChunkFaceSortState`).
- Culling: cull chunks past the fog end; hook `cullerIsVisible` for a stricter test; make sure the cached culler is
  the one in use.
- Entities: distance and frustum cut in `queueRenderEntities`, block actor distance cut in
  `_tryInsertBlockEntityIntoRenderQueues`, animation updates of far actors every 2nd-4th frame.
- Particles: cap and distance cut in `ParticleEngine::_emitParticleNew`.
- Whole passes off by option through the existing `FrameFilterHook` (clouds, weather, actor shadows).
- Rebuild storms: coalesce neighbour (interlock) rebuilds in `_setDirty`; raise the in-flight build limit for
  loading, lower it while moving.

Expected: 10-40% depending on scene. Low risk.

### Phase 2: dynamic resolution + upscale (about 1 week)

For GPU-bound machines. Scene lists before the UnderUI UI cut are recorded with scaled viewports and scissors, then
our FSR1 EASU + RCAS pass writes the full back buffer before the UI. Scale driven by the GPU timers to hold a target
frame time. Open point: the regular renderer draws the scene straight into the swapchain buffer, so the pass reads
the sub-rectangle from a copy. Expected: 1.5-2x when GPU-bound, none when CPU-bound.

### Phase 3: terrain draw submission (about 2-3 weeks, biggest CPU item)

Only if phase 0 shows per-draw CPU cost dominating. Take terrain submission away from the game:

1. RE: `mce::Mesh` -> bgfx vertex/index handles -> D3D12 buffers; the terrain constant layout (chunk origin, fog);
   the terrain root signature (PSOs are already retained by the LCE twin work).
2. Drop the game's terrain insert (the `FrameFilterHook` terrain call site is known).
3. Draw all visible chunks of a layer with one `ExecuteIndirect`, chunk origins in a structured buffer, visibility
   list taken from the game's own culler result.

Expected: terrain CPU cost on the render thread falls by several times at render distance 32+.

### Phase 4: LOD inside the loaded distance (about 2-3 weeks)

- Our own mesher on worker threads builds simplified meshes for far chunks from the block palettes: columns from the
  render heightmap plus exposed sides, greedy-merged, one colour per face (average of the block's atlas tile times
  biome tint), baked light. Levels at 1/2/4/8 blocks, 4x4 chunks merged into one mesh.
- Beyond the LOD distance the game's chunks are not queued (hook `queueChunk`) and their geometry can be freed; our
  pass draws the LOD in the Scene layer with the game's depth buffer and the game's fog values.
- Rebuild on `onBlockChanged`/`onSubChunkLoaded` through the coordinator's listener callbacks.

Expected: vertex and draw counts beyond the LOD distance fall by 10x or more. Risk: seams and popping at the
boundary, light and colour mismatch.

### Phase 5: LOD beyond the loaded distance (Distant Horizons style, about 2 weeks after phase 4)

- LOD data of every chunk seen is cached on disk per server, world and dimension, and drawn past the server's view
  distance with our own far plane, before the game's terrain.
- The game's terrain fog has to be pushed out and unified with ours: fog fields on `LevelRendererCamera`, or a twin
  terrain shader through the LCE twin-PSO path.
- This is the visible feature on servers; it costs frame time instead of saving it.

### Phase 6: chunk build and low-level items (ongoing, each proven by phase 0 numbers)

- Mesher fast paths: skip sub chunks whose palette is one opaque block with opaque neighbours; cheaper ambient
  occlusion for far chunks. Gain is load speed and less stutter, not steady frame rate.
- libdeflate for chunk payloads (game ships zlib 1.3.1), Molang result caching for repeated actor queries.
- Not planned: replacing the allocator from an injected DLL (allocations made before injection cannot be moved).

## Order

0 -> 1 -> (2 or 3, whichever phase 0 says) -> 4 -> 5, with 6 filled in between.

## Rules

- Hot hooks: no locks, no allocation, no logging. Main path works or `__fastfail` (no guards).
- Addresses by RE (`xref.py`, `Sigs.json`), not by scanning memory.
- Every optimization is a setting of one `Optimizer` module and can be switched off live for an A/B number.
