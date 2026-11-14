#include "sdk/mc/network/PacketSanity.h"
#include "sdk/mc/network/MinecraftPacketIds.h"
#include "client/core/diagnostics/Log.h"

namespace {

// The known set is the enum's own span [0, EndId): every value in it belongs to this build - the named ids leave no
// holes, and the title-specific reserve 200..299 (start, end markers included) sits inside. An id at or past EndId is
// drift; the limit is read off the enum, so a rebuilt SDK table moves with it.
constexpr uint32_t kKnownIdLimit = static_cast<uint32_t>(MinecraftPacketIds::EndId);
constexpr size_t kMinimalHeader = 8;       // id + header: a serialized packet smaller than this cannot exist
constexpr size_t kSaneSizeCap = 2u << 20;   // 2 MiB: the largest real packets (biome defs, chunk data) stay far below
constexpr uint32_t kReportAt = 500;        // the summary fires on the 500th packet seen
constexpr size_t kUnknownIdCache = 64;      // warn-once bookkeeping for ids from outside the known span

// One warn flag per known id, zero-initialized at static init: the per-id table, no allocation ever.
std::array<std::atomic<uint8_t>, kKnownIdLimit> sWarnedKnown{};
// Unknown ids are unbounded, so 0 doubles as "empty" (unknown ids are >= EndId, never 0, which is KeepAlive).
std::array<std::atomic<uint32_t>, kUnknownIdCache> sWarnedUnknown{};
std::atomic<uint32_t> sUnknownIds{0};
std::atomic<uint32_t> sSuspiciousIds{0};
std::atomic<uint32_t> sOkPackets{0};
std::atomic<uint32_t> sChecked{0};
std::atomic<bool> sReported{false};

// Relaxed everywhere: the warn is the side effect, no other reads depend on the ordering.
bool claimSuspicious(uint32_t id) {
    if (sWarnedKnown[id].exchange(1, std::memory_order_relaxed) != 0)
        return false;
    sSuspiciousIds.fetch_add(1, std::memory_order_relaxed);
    return true;
}

bool claimUnknown(uint32_t id) {
    for (const auto& slot : sWarnedUnknown) // already warned?
        if (slot.load(std::memory_order_relaxed) == id)
            return false;
    for (auto& slot : sWarnedUnknown) // first sighting: claim an empty slot
        if (uint32_t seen = 0; slot.compare_exchange_strong(seen, id, std::memory_order_relaxed)) {
            sUnknownIds.fetch_add(1, std::memory_order_relaxed);
            return true;
        }
    std::atomic<uint32_t>& bucket = sWarnedUnknown[id % kUnknownIdCache]; // full: 64+ new ids is mass drift already
    return bucket.exchange(id, std::memory_order_relaxed) != id; // the displaced id may warn again, bounded chaos
}

} // namespace

PacketSanity::Verdict PacketSanity::check(uint32_t id, const void* data, size_t size) {
    Verdict verdict = Verdict::Ok;
    if (id >= kKnownIdLimit) {
        verdict = Verdict::Unknown;
        if (claimUnknown(id))
            Logger::warn("[net] unknown packet id {} ({} bytes) - drift?", id, size);
    } else if (size < kMinimalHeader || size > kSaneSizeCap) {
        verdict = Verdict::Suspicious;
        if (claimSuspicious(id))
            Logger::warn("[net] suspicious packet id {} ({} bytes) - implausible size", id, size);
    } else {
        sOkPackets.fetch_add(1, std::memory_order_relaxed);
    }
    // data stays untouched: id and size carry the verdicts.
    if (sChecked.fetch_add(1, std::memory_order_relaxed) + 1 == kReportAt)
        reportOnce();
    return verdict;
}

void PacketSanity::reportOnce() {
    if (sReported.exchange(true, std::memory_order_acq_rel))
        return;
    Logger::info("[net] packet sanity: {} ok, {} unknown ids, {} suspicious ({} packets)",
                 sOkPackets.load(std::memory_order_relaxed), sUnknownIds.load(std::memory_order_relaxed),
                 sSuspiciousIds.load(std::memory_order_relaxed), sChecked.load(std::memory_order_relaxed));
}
