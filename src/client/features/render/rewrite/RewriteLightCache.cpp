#include "client/features/render/rewrite/RewriteFunctions.h"

// Q3d, the hashing half: content hash of the Light tag 5 description (44 MSVC std::unordered_set<uint16_t> of 0x40 bytes, docs/progress/descriptions.md R7). The sets are walked through the
// MSVC list: set+0x08 = sentinel node, set+0x10 = element count, node {next +0x00, prev +0x08, u16 key +0x10}. The sum of a per-key mix is order independent, so two sets with the same ids in a
// different node order hash equal (an unordered_set copy may reorder). The walk is bounded by the stored count and fails fast when the chain does not return to the sentinel in exactly that
// many steps, because a different length means the layout read here is wrong.
// Not wired to a detour: skipping the per-frame deep copy needs the caller of 0x67B6300 (OPEN, see docs/progress/rewrite-program.md Q3d).
static uint64_t rwLightMix(uint16_t key) {
    uint64_t x = key + 0x9E3779B97F4A7C15ull;
    x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ull;
    x = (x ^ (x >> 27)) * 0x94D049BB133111EBull;
    return x ^ (x >> 31);
}

uint64_t RewriteLightOverride::hashSet(const uint8_t* set) {
    const uint8_t* const sentinel = *reinterpret_cast<const uint8_t* const*>(set + kSentinelField);
    const uint64_t count = *reinterpret_cast<const uint64_t*>(set + kSetSizeField);
    const uint8_t* node = *reinterpret_cast<const uint8_t* const*>(sentinel + kNodeNext);
    uint64_t sum = 0;
    uint64_t walked = 0;
    while (node != sentinel) {
        BS_CHECK(walked < count);
        sum += rwLightMix(*reinterpret_cast<const uint16_t*>(node + kNodeKey));
        node = *reinterpret_cast<const uint8_t* const*>(node + kNodeNext);
        ++walked;
    }
    BS_CHECK(walked == count);
    return RewriteHash::combine(sum, count);
}

uint64_t RewriteLightOverride::hashDescription(const uint8_t* description) {
    uint64_t h = 0;
    for (size_t i = 0; i < kSets; ++i)
        h = RewriteHash::combine(h, hashSet(description + i * kSetSize));
    return h;
}
