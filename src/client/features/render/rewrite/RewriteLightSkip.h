#pragma once
#include "client/features/render/rewrite/RewriteFunctions.h"

// Q3d: skip-when-unchanged cache for the Light tag 5 deep copy.
//
// Before the game's converter (0x67B6300) runs, hash the source description.
// If the hash equals last frame's, skip the deep copy (0x67B7810 per element,
// 0x18-byte nodes each) and reuse last frame's converted 0xB00 record.
//
// Description layout (verified: docs/progress/oc_U-ER7.md, BGFX_MAP 6ih):
//   44 elements of 0x40 bytes at +0x00+k*0x40 (k=0..42); element #18 (k=17)
//   is a hash-container header (u32 at +0x440, head at +0x448, size at +0x450,
//   buckets at +0x458, mask at +0x460, count at +0x468); every element's
//   container is head(+0x08)=sentinel node, size(+0x10), node{next+0x00, key(u16)+0x10}.
//   Flavor A (set<u16>, 0x18-byte nodes): bases +0x00..+0x400 (k=0..16),
//   +0x480..+0x500 (k=18..20), +0x900..+0x980 (k=36..38), +0xA00..+0xAC0 (k=40..42).
//   Flavor B (map<u16, float32[3]>, 0x20-byte nodes): bases +0x540..+0x8C0
//   (k=21..35), +0x9C0 (k=39). The hash below reads only keys (order-independent),
//   so equal keys hash equal even when node order differs (unordered_set copy may reorder).
//   Element u32 at +0x00 (max_load_factor bits) is folded into the per-element mix.
//
// Caller (verified by disassembly): Light visitor case 0x66417af
//   0x66417af lea rcx,[rbp-0x50]      out = local 0xB00 record
//   0x66417b3 mov rdx,rsi              desc = rsi
//   0x66417b6 call 0x67B6300           convert desc -> record
//   ...                                get pass via 0x5ABA5C0
//   0x6641860 lea rdx,[rbp-0x50]       src = record
//   0x6641864 mov rcx,rbx              dst = pass vector slot (+0x260)
//   0x6641867 call 0x67E90D0           copy-construct record into pass vector
//   0x664186d add qword ptr [rsi+0x260],0xB00   advance pass+0x260 by stride
//
// Blocker (not established): the consumer of the converted record
// (pass+0x260 vector, stride 0xB00) must not mutate it; reusing a mutated
// record corrupts the cache. Consumer read-only-ness must be established
// before On mode.
//
// Remaining integration (no build, no game; this unit may not edit HookManager.cpp
// or existing hook registration):
//  1. Wire considerSkip() into the caller at 0x66417af (before call 0x67B6300):
//     a detour on that case block, or a source edit of that case. Neither may
//     be added by this unit (HookManager.cpp / existing hook registration off-limits).
//  2. Establish the consumer does not mutate the converted record.
//  3. In-game poll: hash unchanged for 300 frames standing still,
//     changed on an override change (BS_REWRITE=Light::skip=verify).
//  4. Lead's batch build; run with BS_REWRITE=Light::skip=verify.
class RewriteLightSkip {
public:
    // True when the description is unchanged from the last converted frame:
    // skip the deep copy and reuse lastFrameRecord().
    bool considerSkip(const uint8_t* description);

    // Call after a successful conversion: store the hash and the converted
    // 0xB00 record so a later unchanged frame can reuse it.
    void noteConverted(const uint8_t* description, const uint8_t* convertedRecord0xB00);

    // The cached converted record (0xB00 bytes), valid only after noteConverted
    // and while no newer description has arrived. Caller must not mutate it.
    const uint8_t* lastFrameRecord() const { return haveCached_ ? cachedRecord_ : nullptr; }
    bool haveCached() const { return haveCached_; }
    uint64_t lastHash() const { return lastHash_; }

    // Reset (e.g. at end of frame): discard the cache so the next frame
    // always converts. Call from the end-frame listener.
    void reset() { haveCached_ = false; }

private:
    uint64_t lastHash_ = 0;
    uint8_t cachedRecord_[0xB00];
    bool haveCached_ = false;
};
