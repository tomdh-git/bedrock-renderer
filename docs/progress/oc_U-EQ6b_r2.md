## NEXT
DONE

# U-EQ6b: Q6b Optimization module — culling/batching/LOD driven by probe + profiler data, each feature registry-toggled

GOAL: Close checklist item Q6b (docs/RENDER_CHECKLIST.md line 590, `[ ]`): "Optimization module: culling/batching/LOD driven by probe + profiler data, each feature registry-toggled".

## (1) What exists on disk now (paths)

- src/client/features/render/rewrite/RewriteOptimizer.h — module header. Pins the seam targets to 1.26.62.01 RVAs (insert<RenderBatchActorDescription> clone 0x4E39CB0, skinned-mesh insert clone 0x4E39F20, drawFlush 0xE81B720, endFrame 0xC270460), declares the policy functions (shouldCull, shouldSkipBatch, lodLevel/setLodLevel), the four seam detours, tickFromProfiler (the endFrame module clock) and selfTest. Documents: three registry entries Optimizer::cull / Optimizer::batch / Optimizer::lod, RewriteMode Off/Shadow/On/Verify via BS_REWRITE or setMode, nothing enabled by default.
- src/client/features/render/rewrite/RewriteOptimizer.cpp — implementation. Three RewriteEntry{name, sig, knownRva, detour, hosted=false} entries (gOptEntryCull, gOptEntryBatch, gOptEntryLod) plus the clock entry gOptEntryClock ("Optimizer::endFrame"), each registered by a static RewriteReg; RewriteRegistry::init() (called from HookManager.cpp:181 — not edited) resolves each sig via SigManager, checks knownRva against the resolved RVA, and installs the detour only for non-Off modes. Mode Off installs nothing: the game runs untouched. Cull detour reads the InsertVariant tag at variant+8 and skips the original insert when armed (profiler frame time >= 8 ms) and the tag-10/7 insert class exceeded 64 inserts last frame (probe data). Batch detour reads DrawBatcher::pending[kind] at u32 +0x10 + kind*4 (read-only) and skips emitting batches with <= 4 records. Lod detour runs the original endFrame (frame must still be produced) then tickFromProfiler() (__rdtsc delta = profiler data) which arms cull, steps lodLevel 0..3 at 8/12/16 ms, logs the per-frame [optimizer] line and resets counters. Self-test exercises the three policy functions with BS_CHECK (fail fast); no game needed.
- src/sdk/Sigs.json — all three seam sigs already present, each commented with its proven-unique resolution: FrameBuilder::insertBatchActor -> 0x4E39CB0 (line 156; sigscan: exactly 1 match at file offset 0x4E390B0 = RVA 0x4E39CB0), D3D12Context::drawFlush -> 0xE81B720 (line 145), FrameGraph::endFrame -> 0xC270460 (line 137). No Sigs.json edit this run (rule: append proven new ones only; none needed).
- No HookManager.cpp edit, no existing hook registration changed, no CMake edit (file(GLOB_RECURSE src/*.cpp) picks up the new .cpp automatically). No build, no commit, no game launch/attach: the exe is read-only data for rdis.

## (2) Proof rows (verbatim from rdis on Minecraft.Windows.exe 1.26.62.01; every quoted line checked by tools/sigs/verify_oc.py; sizes are instruction byte sizes: push = 1, qword store = 8, byte store = 1)

| offset | size | site (read/store address) | verbatim `0xRVA  instr` | meaning | tag |
|---|---:|---|---|---|---|
| 0x4E39CB0 | 1 | insert<RenderBatchActorDescription> clone entry (cull seam target) | `0x4E39CB0  push rbp` | first instruction of the BatchActor insert clone; detour target of Optimizer::cull | [V] |
| 0x4E39D20 | 8 | [rbp+0x10], where rdi == variant (rdx at 0x4E39CCB) | `0x4E39D20  mov [rbp+0x10],rdi` | InsertVariant* stored at clone frame +0x10; its mTag is stored next at +0x18 | [V] |
| 0x4E39D24 | 1 | [rbp+0x18] == variant+8 == InsertVariant::mTag | `0x4E39D24  mov byte ptr [rbp+0x18],0xA` | the clone stores tag 10 (ItemGroupTag::BatchActor [V header]) at variant+8 | [V] |
| 0x4E39F20 | 1 | insert<RenderSkinnedMeshDescription> clone entry (cull seam target) | `0x4E39F20  push rbp` | first instruction of the SkinnedMesh insert clone; second cull detour target (tag 7) | [V] |
| 0xE81B720 | 1 | D3D12 draw batch flush entry (batch seam target) | `0xE81B720  push r15` | first instruction of drawFlush; detour target of Optimizer::batch | [V] |
| 0xC270460 | 1 | dragon::platform::BgfxContext::endFrame entry (LOD module-clock seam) | `0xC270460  push rbp` | first instruction of endFrame; detour target of Optimizer::lod | [V] |

Code layout pins (static asserts in src/client/features/render/rewrite/RewriteOptimizer.cpp, pinned to the SDK header layout the detours read):
- static_assert(offsetof(mce::framebuilder::InsertVariant, mTag) == 8 && sizeof(mce::framebuilder::InsertVariant) == 0x10) — detourInsertBatchActor reads *reinterpret_cast<const uint64_t*>(variant + 8).
- ItemGroupTag::BatchActor = 10 and ItemGroupTag::SkinnedMesh = 7 [V FrameBuilder.h lines 29 and 32]; the clone at 0x4E39CB0 stores 0xA at variant+8 (row 0x4E39D24 above) [V].
- DrawBatcher::pending[kind] is u32 at +0x10 + kind*4 [V docs/functions/e81b720.md argument use: rcx +0x10..+0x1164]; detourDrawFlush reads it read-only.
- endFrame: rdis shows sub_c270460 [0xC270460..0xC272460) with 1 xref in [V rdis header line above]; Sigs.json FrameGraph::endFrame -> 0xC270460.

## (3) Registry-toggled features (Q6b wording: 3 features, each registry-toggled)

| feature | registry entry | seam (knownRva) | detour | mode gate |
|---|---|---|---|---|
| Optimizer::cull | gOptEntryCull | insert<RenderBatchActorDescription> clone 0x4E39CB0 (+ skinned-mesh clone 0x4E39F20) | detourInsertBatchActor / detourInsertSkinnedMesh | Off/Shadow/On/Verify via BS_REWRITE="Optimizer::cull=<mode>" (or setMode); Off installs nothing |
| Optimizer::batch | gOptEntryBatch | drawFlush 0xE81B720 | detourDrawFlush | same modes via BS_REWRITE="Optimizer::batch=<mode>" |
| Optimizer::lod | gOptEntryLod | endFrame 0xC270460 (module clock) | detourEndFrame (+ tickFromProfiler) | same modes via BS_REWRITE="Optimizer::lod=<mode>" |

Probe + profiler drive: the cull detour counts per-tag inserts each frame (probe data: InsertVariant tag at +8); tickFromProfiler measures the __rdtsc frame-time delta (profiler data), arms cull when >= 8 ms, steps lodLevel 0 (full quality) .. 3 at 8/12/16 ms, logs [optimizer] frame ...us cullArmed= culled= batchesSkipped= lod=, and resets the per-frame counters. detourDrawFlush skips emitting batches with <= 4 pending records in On mode. Modes per RewriteRegistry.h: Off (nothing installed), Shadow (compare + count divergences), On (detour only), Verify (first divergence ends the process loudly — fail fast, no fallback). Nothing enabled by default.

## (4) Self-test on disk

RewriteOptimizer::selfTest(): shouldCull — unarmed never culls; armed with >= 64 inserts culls tags 10/7 only, not under-threshold or other tags. shouldSkipBatch — 1..4 records yes, 0 and 5 no. lodLevel — set/get round-trips. BS_CHECK-fails loudly on any mismatch; logs "[optimizer] selfTest OK". No game, no reads of game memory: runnable from a unit host. Convention: on disk, invoked by the unit host (same as RewriteInsertTable::selfTest / RewriteLightSkip self-test, which are equally unwired).

## (5) What remains (not this unit's steps: no build, no game access)

1. Build the DLL (Release). CMake GLOB_RECURSE src/*.cpp picks up RewriteOptimizer.cpp with no CMake edit; the three RewriteReg static initializers register the entries at DLL load.
2. In-game: per-feature BS_REWRITE runs (cull, batch, lod, each also in verify mode) — see TOOL REQUESTS and the docs/BIGBANG_TESTS.md section below. Deferred per the 2026-11-22 user decision (the one big in-game test); not a reason for CLOSES? NO.

## CLOSES?
YES — every on-disk part of the item is done: 3 registry-toggled features (cull/batch/lod), each a RewriteEntry with name + sig + knownRva + detour + mode (Off by default, gated by BS_REWRITE/setMode through the existing RewriteRegistry installed by the unedited HookManager.cpp:181); probe + profiler-driven policy (per-tag insert counts from the cull detour, __rdtsc frame time in tickFromProfiler, LOD steps 0..3); seam detours at proven-unique RVAs backed by 6 [V] rows above; self-test on disk; includes/registration present (RewriteRegistry static initializers, Sigs.json holds all 3 sigs, CMake globs sources — nothing to edit there). The remaining build + per-feature BS_REWRITE in-game runs are deferred to the single 2026-11-22 big in-game test and are owned by the orchestrator; they are not a reason for CLOSES? NO. Single still-missing step: the build + in-game verification run (sectioned in docs/BIGBANG_TESTS.md below).

## TOOL REQUESTS

q6b_cull_detour_entry | python tools/livecap/request.py add q6b_cull_detour_entry 0x4E39CB0 --why "Q6b: confirm the Optimizer::cull detour fires at insert<RenderBatchActorDescription> clone entry; RDX = InsertVariant*, tag read at variant+8 (ItemGroupTag::BatchActor = 10)" | supporting evidence that the registry-toggled cull detour is installed and receiving inserts in the live run (primary readback stays the [rewrite] entry report line calls>0 and the per-frame [optimizer] culled= line)
CAPTURE REQUESTED q6b_cull_detour_entry

## BIGBANG_TESTS.md section (append-only; item U-EQ6b)

## U-EQ6b (Q6b Optimization module — culling/batching/LOD, registry-toggled)

Item id: U-EQ6b. What to enable: build the client DLL (Release — CMake GLOB_RECURSE picks up src/client/features/render/rewrite/RewriteOptimizer.cpp; no HookManager.cpp, hook-registration, CMake, or Sigs.json change), then launch into a populated world with render distance >= 12 so actors and batch inserts exist.
Exact in-game steps: (1) baseline: launch with all Optimizer entries off — expect the 10 s [rewrite] report to show 0 calls for Optimizer::cull/batch/endFrame and no [optimizer] lines; (2) enable one feature at a time: BS_REWRITE="Optimizer::cull=on" — expect [rewrite] Optimizer::cull mode on: N calls rising past inserts, and when frame time >= 8 ms with >= 64 tag-10/7 inserts last frame: [optimizer] frame ...us cullArmed=1 culled=N ... with tag-10/7 inserts stopping while chunk (tag 3) inserts continue; BS_REWRITE="Optimizer::batch=on" — expect Optimizer::batch calls at drawFlush 0xE81B720 and [optimizer] ... batchesSkipped=N ... when tiny batches pend, draw output otherwise unchanged; BS_REWRITE="Optimizer::lod=on" — expect Optimizer::endFrame calls once per frame and [optimizer] frame ...us cullArmed=X culled=N batchesSkipped=N lod=L with L stepping 0->1->2->3 as frame time crosses 8/12/16 ms; (3) verify mode: BS_REWRITE="Optimizer::cull=verify" (likewise batch=verify, lod=verify) — shadow compares detour vs original on the same inputs; expect completion with divergences=0 (first divergence ends the process loudly: [rewrite] ... DIVERGED ...).
Expected observable result: each enabled entry's detour fires once per matching seam hit (insert / drawFlush / endFrame); the [optimizer] line shows probe+profiler-driven decisions (cullArmed tied to frame time, culled only for tags 10/7 over threshold, batchesSkipped only for <= 4-record batches, lod stepping with frame time); nothing drawn incorrectly (cull drops whole actor-class inserts only when armed); verify runs to completion with zero divergences. Build + this run are the deferred steps (2026-11-22 user decision: one big in-game test); not a reason for CLOSES? NO.
