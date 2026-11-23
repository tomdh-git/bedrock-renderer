#include "client/features/render/rewrite/RewriteOptimizer.h"
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "client/core/diagnostics/Log.h"
#include "sdk/SigManager.h"
#include "sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h"

// Layout the detours read: detourInsertBatchActor reads the InsertVariant tag at variant + 8.
// Pinned to the SDK header (mce::framebuilder::InsertVariant { void* mDescription; uint64_t mTag; })
// which mirrors mce::FrameBuilder::_insert's variant on 1.26.62.01; verified against the clone
// at 0x4E39CB0 which stores tag 0xA at variant+8 (docs/progress/oc_U-EQ6b.md row 0x4E39D24).
static_assert(offsetof(mce::framebuilder::InsertVariant, mTag) == 8,
              "InsertVariant::mTag must stay at +8: detourInsertBatchActor reads the tag there");
static_assert(sizeof(mce::framebuilder::InsertVariant) == 0x10,
              "InsertVariant size must stay 0x10 (two qwords)");

// Q6b: Optimization module — culling/batching/LOD driven by probe + profiler data, each feature registry-toggled.
// Proof rows and seam pinning: docs/progress/oc_U-EQ6b.md.
//
// Design notes (reviewable on disk; build + in-game BS_REWRITE runs are the remaining steps):
//   * Three registry entries, one per feature (Optimizer::cull / batch / lod), each with name + sig + knownRva +
//     detour + RewriteMode (Off/Shadow/On/Verify). Installed by RewriteRegistry::init() from BS_REWRITE or by
//     setMode(). Mode Off = nothing installed, game runs untouched. Nothing enabled by default.
//   * Cull: detour on the insert<RenderBatchActorDescription> clone 0x4E39CB0. One insert holds every actor of
//     the frame (live data 6c: 317 insert hits vs 313 submits). In On mode, when shouldCull() says so (probe
//     insert count high + profiler frame time high), the original insert is skipped -> whole actor class culled.
//   * Batch: detour on drawFlush 0xE81B720. Counts records per kind per frame; in On mode skips emitting tiny
//     batches (<= kBatchSkipMaxRecords records) that the flush would otherwise emit one-by-one.
//   * Lod: detour on endFrame 0xC270460. Runs the original endFrame (frame must still be produced), then
//     tickFromProfiler() measures frame time (__rdtsc delta = profiler data) and the per-tag insert counts
//     gathered by the cull detour (probe data), re-evaluates thresholds, updates lodLevel(), resets counters.
//     lodLevel() (0 = full quality) is consultable by any caller; the lod feature being On gates the clock.
//   * Self-test exercises shouldCull/shouldSkipBatch/lodLevel with synthetic inputs (no game needed).

namespace {
    // Cull: drop a whole insert class when last frame had too many of them and frame time was high.
    static constexpr uint32_t kCullMinCount = 64;             // inserts of the tag needed to consider culling
    static constexpr uint64_t kCullMinFrameTimeUs = 8000ull;  // only cull when the frame took >= 8 ms

    // Batch: skip emitting when a flush batch has at most this many records (tiny batches are per-draw overhead).
    static constexpr uint32_t kBatchSkipMaxRecords = 4;

    // Per-tag insert counters for the current frame (indexed by tag). BatchActor=10, SkinnedMesh=7 are cull
    // targets; others are counted for the probe-style record but not culled by default.
    static constexpr size_t kTagTable = 64;
    static std::atomic<uint32_t> sInsertCount[kTagTable];
    static std::atomic<uint32_t> sCulledThisFrame{0};
    static std::atomic<uint32_t> sBatchesSkippedThisFrame{0};
    static std::atomic<int> sLodLevel{0};          // 0 = full quality
    static std::atomic<uint64_t> sLastFrameTimeUs{0};
    static std::atomic<bool> sCullArmed{false};    // set true by tickFromProfiler when frame time is high

    void incInsert(uint64_t tag) {
        if (tag < kTagTable)
            sInsertCount[tag].fetch_add(1, std::memory_order_relaxed);
    }

    uint64_t rdtscUs() { return __rdtsc() / 1000ull; } // coarse microseconds; only used for thresholds
} // namespace

// ---- policy: cull ----
bool RewriteOptimizer::shouldCull(uint64_t group, uint64_t tag, uint32_t insertCountLastFrame) {
    if (!sCullArmed.load(std::memory_order_relaxed))
        return false;
    if (insertCountLastFrame < kCullMinCount)
        return false;
    // Cull the actor-ish classes only: Item::BatchActor (10) and Item::SkinnedMesh (7).
    return tag == 10ull || tag == 7ull;
}

// ---- policy: batch ----
bool RewriteOptimizer::shouldSkipBatch(uint32_t kind, uint32_t pendingCount) {
    // Whether the batch is small enough to be a skip candidate (the actual skip is an On-mode decision made
    // in detourDrawFlush so Shadow/Verify always run the original for comparison).
    return pendingCount > 0 && pendingCount <= kBatchSkipMaxRecords;
}

// ---- policy: lod ----
int RewriteOptimizer::lodLevel() {
    return sLodLevel.load(std::memory_order_relaxed);
}
void RewriteOptimizer::setLodLevel(int level) {
    sLodLevel.store(level, std::memory_order_relaxed);
}

// ---- tickFromProfiler: the module clock, called by the endFrame detour ----
void RewriteOptimizer::tickFromProfiler() {
    const uint64_t nowUs = rdtscUs();
    const uint64_t prev = sLastFrameTimeUs.exchange(nowUs, std::memory_order_relaxed);
    const uint64_t frameTimeUs = nowUs >= prev ? nowUs - prev : 0;

    // Profiler data: frame time decides whether culling is armed this frame.
    sCullArmed.store(frameTimeUs >= kCullMinFrameTimeUs ? 1u : 0u, std::memory_order_relaxed);
    sLastFrameTimeUs.store(frameTimeUs, std::memory_order_relaxed);

    // LOD: coarser when frames are expensive, finer when cheap. Step function for reviewability.
    int level = 0;
    if (frameTimeUs >= 16000ull)      level = 3; // >= 16 ms
    else if (frameTimeUs >= 12000ull) level = 2; // >= 12 ms
    else if (frameTimeUs >= 8000ull)  level = 1; // >= 8 ms
    setLodLevel(level);

    // Probe data: read this frame's per-tag insert counts, then reset for the next frame.
    uint32_t culled = sCulledThisFrame.exchange(0, std::memory_order_relaxed);
    uint32_t skipped = sBatchesSkippedThisFrame.exchange(0, std::memory_order_relaxed);
    for (size_t t = 0; t < kTagTable; ++t)
        sInsertCount[t].store(0, std::memory_order_relaxed);

    if (culled || skipped || level != 0)
        Logger::info("[optimizer] frame {}us cullArmed={} culled={} batchesSkipped={} lod={}",
                     frameTimeUs, sCullArmed.load(std::memory_order_relaxed), culled, skipped, level);
}

// ---- seam detours ----
uint64_t __fastcall RewriteOptimizer::detourInsertBatchActor(void* self, void* variant, uint64_t a3, uint64_t a4) {
    RewriteEntry& e = gOptEntryCull;
    const uint64_t calls = e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0)
        return e.original<&RewriteOptimizer::detourInsertBatchActor>()(self, variant, a3, a4);

    // InsertVariant = {void* mDescription; uint64_t mTag;} (FrameBuilder.h): tag at +8. variant is a required
    // argument of _insert: read it directly, no null guard (fail fast).
    const uint64_t tag = *reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(variant) + 8);
    incInsert(tag);

    // Cull decision uses this frame's count so far (incInsert above just added this insert); when armed and over
    // threshold for an actor-ish tag, skip the original insert -> the whole class is culled this frame.
    uint32_t countThisFrame = tag < kTagTable ? sInsertCount[tag].load(std::memory_order_relaxed) : 0u;
    if (mode == RewriteMode::On && shouldCull(0 /*group*/, tag, countThisFrame)) {
        sCulledThisFrame.fetch_add(1, std::memory_order_relaxed);
        return 0ull;
    }
    {
        RewriteTimed timed(e, e.ticksOriginal);
        return e.original<&RewriteOptimizer::detourInsertBatchActor>()(self, variant, a3, a4);
    }
}

void __fastcall RewriteOptimizer::detourDrawFlush(void* batcher, void* renderer, void* job, uint32_t kind) {
    RewriteEntry& e = gOptEntryBatch;
    const uint64_t calls = e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0) {
        e.original<&RewriteOptimizer::detourDrawFlush>()(batcher, renderer, job, kind);
        return;
    }
    // DrawBatcher pending count per kind: u32 at +0x10 + kind*4 (dossier docs/functions/e81b720.md). Read-only.
    // batcher is a required argument of flush: read directly, no null guard (fail fast).
    const uint32_t pending = *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(batcher) + 0x10 + static_cast<size_t>(kind) * 4);
    if (mode == RewriteMode::On && shouldSkipBatch(kind, pending)) {
        sBatchesSkippedThisFrame.fetch_add(1, std::memory_order_relaxed);
        return; // batch: skip emitting this tiny batch
    }
    {
        RewriteTimed timed(e, e.ticksOriginal);
        e.original<&RewriteOptimizer::detourDrawFlush>()(batcher, renderer, job, kind);
    }
}

void __fastcall RewriteOptimizer::detourEndFrame(void* frameBuilder) {
    RewriteEntry& e = gOptEntryLod;
    const RewriteMode mode = e.current();
    // The clock always runs the original endFrame (the frame must still be produced); it only observes and
    // retunes policy. No replayable output exists for endFrame, so Verify counts the call and runs the original.
    e.calls.fetch_add(1, std::memory_order_relaxed);
    {
        RewriteTimed timed(e, e.ticksOriginal);
        e.original<&RewriteOptimizer::detourEndFrame>()(frameBuilder);
    }
    tickFromProfiler();
}

// ---- registry entries (one per feature, each registry-toggled) ----
RewriteEntry gOptEntryCull{
    "Optimizer::cull",
    "FrameBuilder::insertBatchActor",   // Sigs.json symbol -> 0x4E39CB0 (appended, sigscan-proven unique)
    RewriteOptimizer::kInsertBatchActor,
    reinterpret_cast<void*>(&RewriteOptimizer::detourInsertBatchActor),
    false
};
RewriteEntry gOptEntryBatch{
    "Optimizer::batch",
    "D3D12Context::drawFlush",          // Sigs.json symbol -> 0xE81B720 (already present)
    RewriteOptimizer::kDrawFlush,
    reinterpret_cast<void*>(&RewriteOptimizer::detourDrawFlush),
    false
};
RewriteEntry gOptEntryLod{
    "Optimizer::lod",
    "FrameGraph::endFrame",             // Sigs.json symbol -> 0xC270460 (already present)
    RewriteOptimizer::kEndFrame,
    reinterpret_cast<void*>(&RewriteOptimizer::detourEndFrame),
    false
};

static RewriteReg gOptRegCull{gOptEntryCull};
static RewriteReg gOptRegBatch{gOptEntryBatch};
static RewriteReg gOptRegLod{gOptEntryLod};

// ---- self-test (no game needed) ----
void RewriteOptimizer::selfTest() {
    // Cull policy: unarmed -> never cull.
    sCullArmed.store(0, std::memory_order_relaxed);
    BS_CHECK(!RewriteOptimizer::shouldCull(0, 10, 1000));
    BS_CHECK(!RewriteOptimizer::shouldCull(0, 7, 1000));

    // Armed + over count -> cull actor-ish tags only.
    sCullArmed.store(1, std::memory_order_relaxed);
    BS_CHECK(RewriteOptimizer::shouldCull(0, 10, kCullMinCount));
    BS_CHECK(RewriteOptimizer::shouldCull(0, 7, kCullMinCount));
    BS_CHECK(!RewriteOptimizer::shouldCull(0, 10, kCullMinCount - 1)); // under threshold
    BS_CHECK(!RewriteOptimizer::shouldCull(0, 3, kCullMinCount));      // not an actor-ish tag
    BS_CHECK(!RewriteOptimizer::shouldCull(0, 99, kCullMinCount));

    // Batch skip candidate: tiny batches yes, larger no.
    BS_CHECK(RewriteOptimizer::shouldSkipBatch(0, 1));
    BS_CHECK(RewriteOptimizer::shouldSkipBatch(1, kBatchSkipMaxRecords));
    BS_CHECK(!RewriteOptimizer::shouldSkipBatch(0, kBatchSkipMaxRecords + 1));
    BS_CHECK(!RewriteOptimizer::shouldSkipBatch(0, 0));

    // LOD level steps.
    RewriteOptimizer::setLodLevel(0);
    BS_CHECK(RewriteOptimizer::lodLevel() == 0);
    RewriteOptimizer::setLodLevel(3);
    BS_CHECK(RewriteOptimizer::lodLevel() == 3);

    Logger::info("[optimizer] selfTest OK");
}
