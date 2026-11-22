#include "client/features/render/rewrite/RewriteFunctions.h"
#include "client/features/render/rewrite/RewriteVerify.h"

// Q2e: bgfx::EncoderImpl::discard at 0xBC60D10 (the entry "Encoder::reset"), reversed completely in docs/functions/bc60d10.md. It is submit's inline clear plus the +0xC0 block, m_discard = 0 and
// the side-table clear, without moving m_uniformBegin. clearDrawState / clearSideTable are the pieces shared with RewriteEncoder.cpp.
//
// The Encoder is owned by one task thread (RewriteOwnership.h), so Shadow/Verify may copy it: the copy gets the rewrite, the live encoder gets the original, the 0x6B0 bytes are compared. A
// non-null side table at +0x680 makes the original free through the game's allocator, so those calls are not compared (entry.skipped) and the original runs alone.
static constexpr size_t kRwDiscardBytes = 0x6B0;

template <typename T>
static T& rwDiscAt(uint8_t* base, uintptr_t offset) {
    return *reinterpret_cast<T*>(base + offset);
}

void RewriteEncoder::discard(uint8_t* e) {
    rwDiscAt<uint8_t>(e, 0x6AD) = 0;
    RewriteEncoder::clearDrawState(e);
    rwDiscAt<uint64_t>(e, 0xC0) = 0;
    rwDiscAt<uint32_t>(e, 0xC8) = 0;
    rwDiscAt<uint16_t>(e, 0xCC) = 0xFFFF;
    rwDiscAt<uint64_t>(e, 0xD0) = 0;
    rwDiscAt<uint32_t>(e, 0xD8) = 0;
    rwDiscAt<uint32_t>(e, 0xDC) = 0xFFFF0000;
    rwDiscAt<uint16_t>(e, 0xE0) = 0;
    rwDiscAt<uint8_t>(e, 0xE2) = 0xFF;
    rwDiscAt<uint8_t>(e, 0xE3) = 0;
    if (uint8_t* const table = rwDiscAt<uint8_t*>(e, 0x680))
        RewriteEncoder::clearSideTable(table);
    rwDiscAt<uint8_t>(e, 0x688) = 1;
}

static void rwDiscardDetour(uint8_t* encoder);
static RewriteEntry sDiscardEntry("Encoder::discard", "Encoder::reset", 0xBC60D10, reinterpret_cast<void*>(&rwDiscardDetour));
static const RewriteReg sDiscardReg(sDiscardEntry);

static void rwDiscardDetour(uint8_t* encoder) {
    RewriteEntry& e = sDiscardEntry;
    e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0) {
        e.original<&rwDiscardDetour>()(encoder);
        return;
    }
    if (mode == RewriteMode::On) {
        RewriteTimed timed(e, e.ticksRewrite);
        RewriteEncoder::discard(encoder);
        return;
    }
    if (rwDiscAt<uint8_t*>(encoder, 0x680) != nullptr) {
        e.skipped.fetch_add(1, std::memory_order_relaxed);
        e.original<&rwDiscardDetour>()(encoder);
        return;
    }
    RewriteBusy::Scope busy;
    uint8_t expected[kRwDiscardBytes];
    std::memcpy(expected, encoder, sizeof(expected));
    RewriteEncoder::discard(expected);
    {
        RewriteTimed timed(e, e.ticksOriginal);
        e.original<&rwDiscardDetour>()(encoder);
    }
    e.evaluated.fetch_add(1, std::memory_order_relaxed);
    RewriteVerify::compare(e, mode, "encoder[0..0x6B0)", encoder, expected, sizeof(expected));
}
