#include "client/features/render/rewrite/RewriteFunctions.h"
#include "client/features/render/rewrite/RewriteMaterialSwap.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// Q2b: ResourceCache::get at 0x675E440 (1.26.62.01), the hit path only (docs/functions/675e440.md; lock/unlock addresses corrected from the disassembly):
//   lock the recursive mutex at this+0x98 (0xEEC59F0), look the key up in the stale set (+0x40) and in the entry map (+0x00), both MSVC hash containers with 16-byte {first,last}
//   buckets and nodes {next +0, prev +8, key +0x10, value +0x20/+0x28, used +0x30}; a key that is not stale and whose holder's resource has `requested` set (+0x10) gets
//   node.used = 1 and the holder copied out with its use count incremented; unlock (0xEEC5A10). A miss, a stale key or a resource that is not loaded yet is the game's whole function.
// Skipped on a hit: the allocator tag set/restore around the call (restored before return, nothing allocates on this path) and the function-local static guard of the load path.

uint64_t RewriteResourceCache::hashOf(const Key& key) {
    uint8_t hi[8];
    std::memcpy(hi, &key.hi, 8);
    return RewriteHash::combine(key.lo, RewriteHash::fnv1a(hi, 8));
}

uint8_t* RewriteResourceCache::findNode(const uint8_t* cache, uintptr_t container, const Key& key) {
    const uint8_t* const base = cache + container;
    const uint8_t* const sentinel = *reinterpret_cast<uint8_t* const*>(base + kSentinel);
    const uint8_t* const buckets = *reinterpret_cast<uint8_t* const*>(base + kBuckets);
    const uint64_t mask = *reinterpret_cast<const uint64_t*>(base + kMask);
    const uint8_t* const bucket = buckets + ((hashOf(key) & mask) << 4);
    uint8_t* node = *reinterpret_cast<uint8_t* const*>(bucket + 8); // last node of the bucket
    if (node == sentinel)
        return nullptr;
    const uint8_t* const first = *reinterpret_cast<uint8_t* const*>(bucket);
    for (;;) {
        const Key& at = *reinterpret_cast<const Key*>(node + kNodeKey);
        if (at.lo == key.lo && at.hi == key.hi)
            return node;
        if (node == first)
            return nullptr;
        node = *reinterpret_cast<uint8_t* const*>(node + kNodePrev);
    }
}

bool RewriteResourceCache::lookup(const uint8_t* cache, const Key& key, Hit& hit) {
    if (findNode(cache, kStale, key))
        return false;
    uint8_t* const node = findNode(cache, kEntries, key);
    if (!node)
        return false;
    uint8_t* const holder = *reinterpret_cast<uint8_t**>(node + kNodeHolder);
    if (!holder)
        return false;
    const uint8_t* const resource = *reinterpret_cast<uint8_t* const*>(holder);
    if (!resource || resource[kResourceRequested] == 0)
        return false;
    hit.node = node;
    hit.holder = holder;
    hit.control = *reinterpret_cast<uint8_t**>(node + kNodeControl);
    return true;
}

// The two calls in the game's function at +0x53 (lock) and +0x447 (unlock): E8 rel32 each.
static RewriteResourceCache::MutexFn rwCallAt(uintptr_t function, uintptr_t offset) {
    const uint8_t* const at = reinterpret_cast<const uint8_t*>(function + offset);
    BS_CHECK(at[0] == 0xE8);
    return reinterpret_cast<RewriteResourceCache::MutexFn>(reinterpret_cast<uintptr_t>(at) + 5 + *reinterpret_cast<const int32_t*>(at + 1));
}

RewriteResourceCache::MutexFn RewriteResourceCache::lockFn() {
    static const MutexFn sFn = rwCallAt(SigManager::get("ResourceCache::get"), 0x53);
    return sFn;
}

RewriteResourceCache::MutexFn RewriteResourceCache::unlockFn() {
    static const MutexFn sFn = rwCallAt(SigManager::get("ResourceCache::get"), 0x447);
    return sFn;
}

bool RewriteResourceCache::fastGet(uint8_t* cache, uint64_t* out, const Key& key) {
    void* const mutex = cache + kMutex;
    BS_CHECK(lockFn()(mutex) == 0);
    Hit hit;
    const bool found = lookup(cache, key, hit);
    if (found) {
        *(hit.node + kNodeUsed) = 1;
        if (hit.control)
            _InterlockedIncrement(reinterpret_cast<volatile long*>(hit.control + 8));
        out[0] = reinterpret_cast<uint64_t>(hit.holder);
        out[1] = reinterpret_cast<uint64_t>(hit.control);
    }
    unlockFn()(mutex);
    return found;
}

static void* rwCacheDetour(uint8_t* cache, uint64_t* out, const RewriteResourceCache::Key* key, void* loader, const void* name, const void* defines);
static RewriteEntry sCacheEntry("ResourceCache::get", "ResourceCache::get", 0x675E440, reinterpret_cast<void*>(&rwCacheDetour));
static const RewriteReg sCacheReg(sCacheEntry);

// Shadow / Verify: with the cache's lock held (the original takes it again, it is recursive) the hit is predicted, the original runs, and its result must be the predicted holder and
// control block, with the entry marked used. Calls the rewrite does not cover (miss, stale, not loaded) run the original alone and count in skipped.
static void rwCacheCompare(RewriteEntry& e, RewriteMode mode, uint8_t* cache, uint64_t* out, const RewriteResourceCache::Key* key, void* loader, const void* name, const void* defines) {
    void* const mutex = cache + RewriteResourceCache::kMutex;
    BS_CHECK(RewriteResourceCache::lockFn()(mutex) == 0);
    RewriteResourceCache::Hit predicted;
    const bool hit = RewriteResourceCache::lookup(cache, *key, predicted);
    {
        RewriteTimed timed(e, e.ticksOriginal);
        e.original<&rwCacheDetour>()(cache, out, key, loader, name, defines);
    }
    if (hit) {
        e.evaluated.fetch_add(1, std::memory_order_relaxed);
        const uint64_t expected[2] = {reinterpret_cast<uint64_t>(predicted.holder), reinterpret_cast<uint64_t>(predicted.control)};
        RewriteVerify::compare(e, mode, "returned holder + control block", out, expected, sizeof(expected));
        const uint8_t one = 1;
        RewriteVerify::compare(e, mode, "entry used byte", predicted.node + RewriteResourceCache::kNodeUsed, &one, 1);
    } else {
        e.skipped.fetch_add(1, std::memory_order_relaxed);
    }
    RewriteResourceCache::unlockFn()(mutex);
}

// rcx = cache, rdx = out {pointer, control block}, r8 = 16-byte key, r9 = loader, then two stack arguments (name view, defines span) that only the miss path uses.
static void* rwCacheDetour(uint8_t* cache, uint64_t* out, const RewriteResourceCache::Key* key, void* loader, const void* name, const void* defines) {
    RewriteEntry& e = sCacheEntry;
    const uint64_t calls = e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0)
        return e.original<&rwCacheDetour>()(cache, out, key, loader, name, defines);
    if (mode == RewriteMode::On) {
        // L7h material swap: when the MaterialSwap entry is On and the pass-name view names a
        // replacement, call the original with the replacement view substituted. The replacement
        // bytes live on this frame's stack and cover the synchronous call below — no allocation,
        // nothing stored past the call. Otherwise (MaterialSwap off or no match) the original is
        // called unchanged with the original name argument.
        const void* nameToUse = name;
        if (MaterialSwap::swapEnabled() && name != nullptr) {
            // get()'s 5th argument is a pointer to a {ptr, size} string_view: verified at the call
            // site (ptr at [rbp+0x5A0] by 0x6646e73, size at [rbp+0x5A8] by 0x6646e7a, pointer
            // passed on the stack at [rsp+0x20] by 0x6646e98).
            const char* const namePtr = *reinterpret_cast<const char* const*>(name);
            const size_t nameSize = *reinterpret_cast<const size_t*>(static_cast<const uint8_t*>(name) + 8);
            char repl[MaterialSwap::kMaxReplacement] = {};
            size_t replSize = 0;
            if (nameSize > 0 && MaterialSwap::lookup(namePtr, nameSize, repl, replSize)) {
                PassName replacement{repl, replSize};
                nameToUse = &replacement;
            }
        }
        const bool timed = (calls & 15) == 0;
        const uint64_t t0 = timed ? Profiler::now() : 0;
        const bool hit = RewriteResourceCache::fastGet(cache, out, *key);
        if (timed)
            e.ticksRewrite.fetch_add(Profiler::now() - t0, std::memory_order_relaxed);
        if (hit)
            return out;
        return e.original<&rwCacheDetour>()(cache, out, key, loader, nameToUse, defines);
    }
    RewriteBusy::Scope busy;
    rwCacheCompare(e, mode, cache, out, key, loader, name, defines);
    return out;
}
