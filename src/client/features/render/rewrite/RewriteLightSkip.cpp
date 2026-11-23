#include "client/features/render/rewrite/RewriteLightSkip.h"
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/core/diagnostics/Log.h"

namespace {
// Single cache instance for the whole DLL. The Light tag 5 visitor runs on the game thread
// (FrameBuilder insert task), so no cross-thread synchronisation is needed here.
RewriteLightSkip& lightSkip() {
    static RewriteLightSkip s_instance;
    return s_instance;
}

static uint8_t* rwLightSkipDetour(uint8_t* out, const uint8_t* desc);
static RewriteEntry sLightSkipEntry("Light::skip", "lightTag5Convert", 0x67B6300,
                                     reinterpret_cast<void*>(&rwLightSkipDetour));
static const RewriteReg sLightSkipReg(sLightSkipEntry);

// Q3d detour on the Light tag 5 converter 0x67B6300.
// Signature (rcx = out 0xB00 record, rdx = description, returns out): when the description is
// unchanged from the last converted frame, skip the deep copy of ~41 unordered_map<u16> parameter
// sets and reuse the cached 0xB00 record; when changed, run the real converter and cache the result.
//
// This is the hook wiring at the converter (the caller at 0x66417af calls 0x67B6300, so intercepting
// here achieves the same skip with a normal function entry instead of a mid-function case block).
// Consumer read-only-ness of pass+0x260 is NOT established (consumer not located statically; same
// E2 consumer blocker as the other Light pass vectors), so On mode must not be enabled yet.
static uint8_t* rwLightSkipDetour(uint8_t* out, const uint8_t* desc) {
    RewriteEntry& e = sLightSkipEntry;
    e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0) {
        e.original<&rwLightSkipDetour>()(out, desc);
        return out;
    }
    // On mode is intentionally unreachable: the consumer sub_6618810 -> sub_67B8030 DESTROYS each 0xB00 record
    // (clears sub-vectors at +0xA18..+0xAE8, oc_U-EQ3d_r4.md), so a memcpy of the cached record would double free.
    // A skip needs a deep copy, which is what the original converter already does; the shadow path below stays.
    if (false && mode == RewriteMode::On) {
        RewriteLightSkip& skip = lightSkip();
        if (skip.considerSkip(desc)) {
            // Unchanged: reuse cached record, skip the deep copy (0x67B7810 per element, 0x18-byte nodes).
            e.skipped.fetch_add(1, std::memory_order_relaxed);
            std::memcpy(out, skip.lastFrameRecord(), 0xB00);
            return out;
        }
        // Changed: run the real converter, then cache so the next unchanged frame can skip.
        e.original<&rwLightSkipDetour>()(out, desc);
        skip.noteConverted(desc, out);
        return out;
    }
    // Shadow / Verify: run the original, count the rewrite as not evaluated (skip semantics cannot be
    // meaningfully compared against a full deep copy without snapshotting the whole 0xB00 output twice).
    e.original<&rwLightSkipDetour>()(out, desc);
    e.skipped.fetch_add(1, std::memory_order_relaxed);
    return out;
}

} // namespace

bool RewriteLightSkip::considerSkip(const uint8_t* description) {
    BS_CHECK(description != nullptr);
    uint64_t h = RewriteLightOverride::hashDescription(description);
    if (!haveCached_ || h != lastHash_)
        return false;
    return true;
}

void RewriteLightSkip::noteConverted(const uint8_t* description,
                                     const uint8_t* convertedRecord0xB00) {
    BS_CHECK(description != nullptr);
    BS_CHECK(convertedRecord0xB00 != nullptr);
    lastHash_ = RewriteLightOverride::hashDescription(description);
    std::memcpy(cachedRecord_, convertedRecord0xB00, 0xB00);
    haveCached_ = true;
}

// Q3d self-test. Runs under BS_REWRITE=Light::skip=verify or a unit-test host.
// It cannot run against the live game (no build, no attach): it exercises the
// hash on synthetic buffers whose layout matches the reversed description.
// Checks:
//   1. Deterministic: same bytes -> same hash.
//   2. Order-independent: same keys in different node order -> same hash.
//   3. Sensitive: different keys -> different hash (not guaranteed to differ,
//      but overwhelmingly likely for random keys).
static void rwLightSkipSelfTest() {
    // Build a synthetic 0x40-byte element (flavor A: set<u16>):
    //   +0x00 u32 = 0x3F800000 (1.0f max_load_factor bits)
    //   +0x08 u64 = sentinel node pointer (points into our buffer)
    //   +0x10 u64 = element count
    //   Node at N: +0x00 u64 next, +0x08 u64 prev, +0x10 u16 key
    // Sentinel self-links: [sent+0]=sent, [sent+0x8]=sent.
    uint8_t buf[0x40] = {};
    uint8_t* sent = buf + 0x08;
    uint8_t* node1 = buf + 0x20;
    uint8_t* node2 = buf + 0x30;

    *reinterpret_cast<uint32_t*>(buf + 0x00) = 0x3F800000u; // max_load_factor = 1.0f
    *reinterpret_cast<uint64_t*>(buf + 0x08) = reinterpret_cast<uint64_t>(sent); // head = sentinel
    *reinterpret_cast<uint64_t*>(buf + 0x10) = 2ull;        // count = 2

    // sentinel <-> node1 <-> node2 <-> sentinel (circular list)
    *reinterpret_cast<uint64_t*>(sent + 0x00) = reinterpret_cast<uint64_t>(node1); // sent->next = node1
    *reinterpret_cast<uint64_t*>(sent + 0x08) = reinterpret_cast<uint64_t>(node2); // sent->prev = node2
    *reinterpret_cast<uint64_t*>(node1 + 0x00) = reinterpret_cast<uint64_t>(node2); // node1->next = node2
    *reinterpret_cast<uint64_t*>(node1 + 0x08) = reinterpret_cast<uint64_t>(sent);  // node1->prev = sent
    *reinterpret_cast<uint16_t*>(node1 + 0x10) = 0x0007u;   // node1 key = 7
    *reinterpret_cast<uint64_t*>(node2 + 0x00) = reinterpret_cast<uint64_t>(sent); // node2->next = sent
    *reinterpret_cast<uint64_t*>(node2 + 0x08) = reinterpret_cast<uint64_t>(node1); // node2->prev = node1
    *reinterpret_cast<uint16_t*>(node2 + 0x10) = 0x0042u;   // node2 key = 66

    // Whole description: 44 elements of 0x40 bytes, element #0 = buf, rest zeroed.
    uint8_t desc[44 * 0x40] = {};
    std::memcpy(desc, buf, 0x40);

    // 1. Deterministic.
    uint64_t h1 = RewriteLightOverride::hashDescription(desc);
    uint64_t h2 = RewriteLightOverride::hashDescription(desc);
    BS_CHECK(h1 == h2);

    // 2. Order-independent: swap node1 and node2 in the list; keys {7,66} same.
    uint8_t buf2[0x40] = {};
    uint8_t* sent2 = buf2 + 0x08;
    uint8_t* nodeA = buf2 + 0x20;
    uint8_t* nodeB = buf2 + 0x30;
    *reinterpret_cast<uint32_t*>(buf2 + 0x00) = 0x3F800000u;
    *reinterpret_cast<uint64_t*>(buf2 + 0x08) = reinterpret_cast<uint64_t>(sent2);
    *reinterpret_cast<uint64_t*>(buf2 + 0x10) = 2ull;
    *reinterpret_cast<uint64_t*>(sent2 + 0x00) = reinterpret_cast<uint64_t>(nodeB); // sent->next = nodeB (order swapped)
    *reinterpret_cast<uint64_t*>(sent2 + 0x08) = reinterpret_cast<uint64_t>(nodeA);
    *reinterpret_cast<uint64_t*>(nodeB + 0x00) = reinterpret_cast<uint64_t>(nodeA); // nodeB->next = nodeA
    *reinterpret_cast<uint64_t*>(nodeB + 0x08) = reinterpret_cast<uint64_t>(sent2);
    *reinterpret_cast<uint16_t*>(nodeB + 0x10) = 0x0042u;   // nodeB key = 66
    *reinterpret_cast<uint64_t*>(nodeA + 0x00) = reinterpret_cast<uint64_t>(sent2); // nodeA->next = sent
    *reinterpret_cast<uint64_t*>(nodeA + 0x08) = reinterpret_cast<uint64_t>(nodeB);
    *reinterpret_cast<uint16_t*>(nodeA + 0x10) = 0x0007u;   // nodeA key = 7
    uint8_t desc2[44 * 0x40] = {};
    std::memcpy(desc2, buf2, 0x40);
    uint64_t h3 = RewriteLightOverride::hashDescription(desc2);
    BS_CHECK(h1 == h3); // same keys, different order -> same hash

    // 3. Sensitive: change one key -> different hash (expected, not guaranteed).
    uint8_t buf3[0x40] = {};
    uint8_t* sent3 = buf3 + 0x08;
    uint8_t* nodeC = buf3 + 0x20;
    uint8_t* nodeD = buf3 + 0x30;
    *reinterpret_cast<uint32_t*>(buf3 + 0x00) = 0x3F800000u;
    *reinterpret_cast<uint64_t*>(buf3 + 0x08) = reinterpret_cast<uint64_t>(sent3);
    *reinterpret_cast<uint64_t*>(buf3 + 0x10) = 2ull;
    *reinterpret_cast<uint64_t*>(sent3 + 0x00) = reinterpret_cast<uint64_t>(nodeC);
    *reinterpret_cast<uint64_t*>(sent3 + 0x08) = reinterpret_cast<uint64_t>(nodeD);
    *reinterpret_cast<uint64_t*>(nodeC + 0x00) = reinterpret_cast<uint64_t>(nodeD);
    *reinterpret_cast<uint64_t*>(nodeC + 0x08) = reinterpret_cast<uint64_t>(sent3);
    *reinterpret_cast<uint16_t*>(nodeC + 0x10) = 0x0008u;   // changed key: 8 instead of 7
    *reinterpret_cast<uint64_t*>(nodeD + 0x00) = reinterpret_cast<uint64_t>(sent3);
    *reinterpret_cast<uint64_t*>(nodeD + 0x08) = reinterpret_cast<uint64_t>(nodeC);
    *reinterpret_cast<uint16_t*>(nodeD + 0x10) = 0x0042u;
    uint8_t desc3[44 * 0x40] = {};
    std::memcpy(desc3, buf3, 0x40);
    uint64_t h4 = RewriteLightOverride::hashDescription(desc3);
    BS_CHECK(h1 != h4); // different key -> different hash

    // considerSkip / noteConverted round-trip.
    RewriteLightSkip skip;
    BS_CHECK(!skip.haveCached());
    BS_CHECK(!skip.considerSkip(desc)); // no cache yet -> never skip
    skip.noteConverted(desc, buf);      // note a conversion (record content irrelevant here)
    BS_CHECK(skip.haveCached());
    BS_CHECK(skip.lastHash() == h1);
    BS_CHECK(skip.considerSkip(desc));  // same description -> skip
    BS_CHECK(!skip.considerSkip(desc3)); // different description -> don't skip
    skip.reset();
    BS_CHECK(!skip.haveCached());
    BS_CHECK(!skip.considerSkip(desc)); // after reset -> never skip
}
