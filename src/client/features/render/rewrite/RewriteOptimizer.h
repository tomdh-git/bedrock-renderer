#pragma once

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/mc/deps/bgfx/Frame.h"

// Q6b: Optimization module — culling/batching/LOD driven by probe + profiler data, each feature registry-toggled.
// See docs/progress/oc_U-EQ6b.md for the proof rows and seam pinning.
//
// Three features, each a registry entry (RewriteMode Off/Shadow/On/Verify, set via BS_REWRITE or setMode):
//   Optimizer::cull      drop whole description classes at insert (insert clones) when the probe counted
//                        too many of them last frame and the profiler frame time is high.
//   Optimizer::batch     at the draw flush, record batch stats and, in On mode, skip tiny batches that the
//                        flush would emit one-by-one (keeps the batcher's existing direct/indirect paths).
//   Optimizer::lod       at endFrame, raise/lower a frame-time-driven LOD level that callers consult; the
//                        clock itself is an endFrame detour so the policy is re-evaluated every frame.
// Nothing is enabled by default (mode Off). All seam targets are proven-unique sigs (Sigs.json, appended
// and sigscan-proven). No HookManager.cpp edit, no existing hook registration, no CMake change.

// The optimization feature keys. These are the registry names and the profiler row prefixes ("optimizer.cull", ...).
enum class OptimizerFeature : uint8_t { Cull = 0, Batch, Lod, Count };

struct RewriteOptimizer {
    // ---- seam targets (proven unique, pinned to RVAs on 1.26.62.01; see oc_U-EQ6b.md) ----
    static constexpr uintptr_t kInsertBatchActor = 0x4E39CB0; // insert<RenderBatchActorDescription> clone
    static constexpr uintptr_t kInsertSkinnedMesh = 0x4E39F20; // insert<RenderSkinnedMeshDescription> clone
    static constexpr uintptr_t kDrawFlush = 0xE81B720;          // D3D12 draw batch flush
    static constexpr uintptr_t kEndFrame = 0xC270460;           // dragon::platform::BgfxContext::endFrame

    // Insert clone signature: (self = BgfxFrameBuilder*, variant = InsertVariant*, a3, a4) -> u64 insert result.
    using InsertFn = uint64_t(__fastcall*)(void* self, void* variant, uint64_t a3, uint64_t a4);
    // Draw flush signature: flush(batcher rcx, renderer rdx, job r8, kind r9d).
    using FlushFn = void(__fastcall*)(void* batcher, void* renderer, void* job, uint32_t kind);
    // endFrame signature: endFrame(BgfxFrameBuilder* rcx).
    using EndFrameFn = void(__fastcall*)(void* frameBuilder);

    // ---- policy: cull ----
    // True when the (group,tag) description should be culled this frame. Driven by the probe's per-tag
    // insert count from the last frame (RewriteProbe::sRwDescLast) and the profiler frame time.
    static bool shouldCull(uint64_t group, uint64_t tag, uint32_t insertCountLastFrame);

    // ---- policy: batch ----
    // True when a flush record batch is small enough to skip emitting (kept as a stat in Shadow/On).
    static bool shouldSkipBatch(uint32_t kind, uint32_t pendingCount);

    // ---- policy: lod ----
    // Current frame-time-driven LOD level (0 = full quality, higher = coarser). Updated once per frame by
    // the endFrame clock from the profiler; consultable by any caller.
    static int lodLevel();
    static void setLodLevel(int level);

    // ---- seam detours ----
    static uint64_t __fastcall detourInsertBatchActor(void* self, void* variant, uint64_t a3, uint64_t a4);
    static uint64_t __fastcall detourInsertSkinnedMesh(void* self, void* variant, uint64_t a3, uint64_t a4);
    static void __fastcall detourDrawFlush(void* batcher, void* renderer, void* job, uint32_t kind);
    static void __fastcall detourEndFrame(void* frameBuilder);

    // ---- module clock (endFrame) and self-test ----
    static void tickFromProfiler(); // re-evaluate cull/batch/lod thresholds from last frame's timings
    static void selfTest();          // runs under BS_REWRITE=Optimizer::selfTest=verify or a unit host
};

// Registry entries (defined in RewriteOptimizer.cpp). Names: "Optimizer::cull", "Optimizer::batch",
// "Optimizer::lod", "Optimizer::endFrame".
extern RewriteEntry gOptEntryCull;
extern RewriteEntry gOptEntryBatch;
extern RewriteEntry gOptEntryLod;
extern RewriteEntry gOptEntryClock;
