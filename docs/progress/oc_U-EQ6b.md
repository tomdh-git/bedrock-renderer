## NEXT
DONE

# U-EQ6b: Q6b Optimization module — culling/batching/LOD driven by probe + profiler data, each feature registry-toggled

GOAL: Close checklist item Q6b (docs/RENDER_CHECKLIST.md line 590, currently `[ ]`):
"Optimization module: culling/batching/LOD driven by probe + profiler data, each feature registry-toggled".

## (1) What I changed (paths)
- docs/progress/oc_U-EQ6b.md — this note (created by this unit; the unit's only doc output).
- src/client/features/render/rewrite/RewriteOptimizer.h — NEW module header.
- src/client/features/render/rewrite/RewriteOptimizer.cpp — NEW module implementation + registry entries + self-test.
- src/sdk/Sigs.json — append-only: one proven-new sig appended under `mc/deps/bgfx/FrameBuilder`: `insertBatchActor` -> RVA 0x4E39CB0. No existing entry touched, no HookManager.cpp edit, no existing hook registration changed, no CMake edit. No build, no commit, no game launch/attach (the exe is read only as data by rdis/sigscan).

## (2) Registry components on disk (Q6b wording: culling/batching/LOD, each registry-toggled)
| feature | registry entry (name) | seam target | detour | mode gate |
|---|---|---|---|---|
| culling | Optimizer::cull | insert<RenderBatchActorDescription> clone 0x4E39CB0 | detourInsertBatchActor | RewriteMode Off/Shadow/On/Verify via BS_REWRITE / setMode |
| batching | Optimizer::batch | D3D12 draw batch flush 0xE81B720 | detourDrawFlush | RewriteMode Off/Shadow/On/Verify via BS_REWRITE / setMode |
| LOD | Optimizer::lod | dragon::platform::BgfxContext::endFrame 0xC270460 (module clock) | detourEndFrame | RewriteMode Off/Shadow/On/Verify via BS_REWRITE / setMode |

All three entries are `RewriteEntry`s (name + sig + knownRva + detour + hosted=false) registered by `RewriteReg` static initializers and installed by `RewriteRegistry::init()` from `BS_REWRITE`, or by `setMode()`. Mode Off installs nothing (game runs untouched); nothing enabled by default. This matches the R1 registry pattern (RewriteRegistry.h/.cpp, closed by oc_U-EQ1a.md).

The cull detour reads the InsertVariant tag at variant+8 (FrameBuilder.h:104-107), counts per-tag inserts each frame (probe data), and in On mode skips the original insert when `shouldCull()` (armed by profiler frame time + high insert count) says so — dropping the whole actor class. The batch detour wraps drawFlush, reads the DrawBatcher pending count at +0x10+kind*4 (dossier docs/functions/e81b720.md), and in On mode skips tiny batches. The lod detour wraps endFrame, runs the original (frame must still be produced), then `tickFromProfiler()` measures frame time (__rdtsc, profiler data), re-evaluates cull arming and `lodLevel()` (0 = full quality), and resets the per-frame counters. Self-test (`RewriteOptimizer::selfTest`) exercises shouldCull/shouldSkipBatch/lodLevel with synthetic inputs; no game needed.

## (3) Sigs.json — proven-new sig appended (sigscan: exactly 1 match at expected file offset = RVA - 0xC00)
| symbol | rva | sigscan result | file offset (RVA - 0xC00) |
|---|---|---|---|
| FrameBuilder.insertBatchActor | 0x4E39CB0 | exactly 1 match | 0x4E390B0 |

The other two seam symbols already exist in Sigs.json: `D3D12Context.drawFlush` -> 0xE81B720 (line 145), `FrameGraph.endFrame` -> 0xC270460 (line 137). No existing Sigs.json entry was modified.

## (4) Proof rows (one row per distinct seam offset; verbatim `0xRVA  instr` from rdis dis, size = instruction byte size)
| offset | size | site (read/store address) | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0x4E39CB0 | 1 | insert<RenderBatchActorDescription> clone entry (cull seam) | `0x4E39CB0  push rbp` | first instruction of the BatchActor insert clone; detour target for Optimizer::cull | [V] |
| 0x4E39F20 | 1 | insert<RenderSkinnedMeshDescription> clone entry (cull seam) | `0x4E39F20  push rbp` | first instruction of the SkinnedMesh insert clone; second actor-class insert detour target | [V] |
| 0xE81B720 | 1 | D3D12 draw batch flush entry (batching seam) | `0xE81B720  push r15` | first instruction of drawFlush; detour target for Optimizer::batch | [V] |
| 0xC270460 | 1 | dragon::platform::BgfxContext::endFrame entry (LOD / module-clock seam) | `0xC270460  push rbp` | first instruction of endFrame; detour target for Optimizer::lod | [V] |

Sources: rdis dis of each entry (0x4E39CB0 / 0x4E39F20 entry bytes; 0xE81B720 per docs/functions/e81b720.md line 88; 0xC270460 per BGFX_MAP.md 6n / Sigs.json line 137 first byte 0x55 = push rbp). Sigscan uniqueness proven for 0x4E39CB0 (1 match at file offset 0x4E390B0 = RVA 0x4E39CB0); drawFlush/endFrame were already proven unique when originally appended.

## (5) Remaining steps (this unit may not perform them: no build, no game launch/attach)
1. Build the DLL (Release OK) so RewriteOptimizer.cpp is compiled and the three entries register.
2. Run in game with `BS_REWRITE=Optimizer::cull=on` (and batch/lod) and confirm the insert detour fires (calls counter increments) and, for cull, actor inserts are skipped when armed.
3. Run with `BS_REWRITE=Optimizer::cull=verify` / `batch=verify` / `lod=verify` to shadow-compare the detour against the original on the same inputs; first divergence aborts loudly (fail fast).
4. Confirm per-frame tickFromProfiler log line (frame time, cullArmed, culled, batchesSkipped, lod) appears each frame.
5. Then tick Q6b [x] in docs/RENDER_CHECKLIST.md.

## CLOSES?
NO — the item's own wording ("culling/batching/LOD driven by probe + profiler data, each feature registry-toggled") is met on disk now (three registry-toggled features, probe+profiler-driven policy, seam detours at proven RVAs, self-test), but it cannot be fully CLOSED until the build and the in-game BS_REWRITE per-feature runs (steps 1-4 above) are performed, which this unit is not allowed to do. Single blocking fact: no build / no in-game run has been performed, so the registry-toggled features have not been exercised against the live game.

## NEXT
step 5 — (remaining: build, then BS_REWRITE per-feature in-game runs; not part of this unit)
