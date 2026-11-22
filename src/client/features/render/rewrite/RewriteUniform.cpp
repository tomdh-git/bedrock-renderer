#include "client/features/render/rewrite/RewriteFunctions.h"
#include "client/features/render/rewrite/RewriteVerify.h"

// Q2a: UniformBlock::setVec4Array at 0x5679DB0 (1.26.62.01), every instruction read again for this file:
//   entry = *(u8**)(block+0x30) + (u32(*slot) << 4); offset = u16 at entry+8;
//   if (u64 at block+0x20 <= offset || value->count == 0) the game calls 0x78ED0 and executes int3 (it ends itself);
//   memcpy(*(u8**)(block+0x28) + offset, value->data, value->count << 4);  entry[0xC] = 1;
//   h = u64 at block+0x70; h = combine(h, fnv1a({slot lo, slot hi})); store; h = combine(h, fnv1a(8 bytes, little endian, of xxh64(value, count*16, seed 0))); store.

uint64_t RewriteUniform::hashAfter(uint64_t before, uint16_t slot, const void* value, size_t bytes) {
    const uint8_t slotBytes[2] = {static_cast<uint8_t>(slot), static_cast<uint8_t>(slot >> 8)};
    uint64_t h = RewriteHash::combine(before, RewriteHash::fnv1a(slotBytes, 2));
    const uint64_t digest = RewriteHash::xxh64(value, bytes, 0);
    uint8_t digestBytes[8];
    std::memcpy(digestBytes, &digest, 8); // little endian: the game feeds the low byte first
    return RewriteHash::combine(h, RewriteHash::fnv1a(digestBytes, 8));
}

static uint8_t* rwUniformEntry(uint8_t* block, uint16_t slot) {
    return *reinterpret_cast<uint8_t**>(block + RewriteUniform::kBlockSlots) + (static_cast<uint32_t>(slot) << 4);
}

void RewriteUniform::setVec4Array(uint8_t* block, const uint16_t* slot, const Span* value) {
    uint8_t* const entry = rwUniformEntry(block, *slot);
    const uint16_t offset = *reinterpret_cast<const uint16_t*>(entry + kSlotOffset);
    if (*reinterpret_cast<const uint64_t*>(block + kBlockSize) <= offset || value->count == 0)
        Logger::fatal("[rewrite] UniformBlock::setVec4Array: slot {} (offset {}) is outside the block of {} bytes or the value is empty; the game ends the process here too", *slot, offset,
            *reinterpret_cast<const uint64_t*>(block + kBlockSize));
    const size_t bytes = static_cast<size_t>(value->count) << 4;
    std::memcpy(*reinterpret_cast<uint8_t**>(block + kBlockData) + offset, value->data, bytes);
    entry[kSlotDirty] = 1;
    uint64_t& hash = *reinterpret_cast<uint64_t*>(block + kBlockHash);
    hash = hashAfter(hash, *slot, value->data, bytes);
}

static void rwUniformDetour(uint8_t* block, const uint16_t* slot, const RewriteUniform::Span* value);
static RewriteEntry sUniformEntry("UniformBlock::setVec4Array", "UniformBlock::setVec4Array", 0x5679DB0, reinterpret_cast<void*>(&rwUniformDetour));
static const RewriteReg sUniformReg(sUniformEntry);

// Shadow / Verify: the rewrite's result is computed from copies taken before the original runs (the expected data bytes are the value itself, the expected hash comes from the
// hash before), the original runs on the real block, and the block is compared with the expectation afterwards. The rewrite never writes to the game's memory in these modes.
// A call the game ends by itself (slot out of range, empty value) is not compared: the original runs and does it.
static void rwUniformCompare(RewriteEntry& e, RewriteMode mode, uint8_t* block, const uint16_t* slot, const RewriteUniform::Span* value) {
    uint8_t* const entry = rwUniformEntry(block, *slot);
    const uint16_t offset = *reinterpret_cast<const uint16_t*>(entry + RewriteUniform::kSlotOffset);
    if (*reinterpret_cast<const uint64_t*>(block + RewriteUniform::kBlockSize) <= offset || value->count == 0) {
        e.skipped.fetch_add(1, std::memory_order_relaxed); // the original ends the process
        e.original<&rwUniformDetour>()(block, slot, value);
        return;
    }
    RewriteBusy::Scope busy;
    const size_t bytes = static_cast<size_t>(value->count) << 4;
    const uint16_t slotValue = *slot;
    const uint64_t hashBefore = *reinterpret_cast<const uint64_t*>(block + RewriteUniform::kBlockHash);
    static thread_local std::vector<uint8_t> tValue;
    tValue.assign(static_cast<const uint8_t*>(value->data), static_cast<const uint8_t*>(value->data) + bytes);
    {
        RewriteTimed timed(e, e.ticksOriginal);
        e.original<&rwUniformDetour>()(block, slot, value);
    }
    uint64_t expectedHash;
    {
        RewriteTimed timed(e, e.ticksRewrite);
        expectedHash = RewriteUniform::hashAfter(hashBefore, slotValue, tValue.data(), bytes);
    }
    e.evaluated.fetch_add(1, std::memory_order_relaxed);
    RewriteVerify::compare(e, mode, "uniform data", *reinterpret_cast<uint8_t**>(block + RewriteUniform::kBlockData) + offset, tValue.data(), bytes);
    const uint8_t expectedDirty = 1;
    RewriteVerify::compare(e, mode, "slot dirty byte", entry + RewriteUniform::kSlotDirty, &expectedDirty, 1);
    RewriteVerify::compare(e, mode, "running hash", block + RewriteUniform::kBlockHash, &expectedHash, sizeof(expectedHash));
}

// rcx = block, rdx = slot index pointer, r8 = {count, data}; r9 is not used by the game.
static void rwUniformDetour(uint8_t* block, const uint16_t* slot, const RewriteUniform::Span* value) {
    RewriteEntry& e = sUniformEntry;
    const uint64_t calls = e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0)
        return e.original<&rwUniformDetour>()(block, slot, value);
    if (mode == RewriteMode::On) {
        if ((calls & 15) != 0)
            return RewriteUniform::setVec4Array(block, slot, value);
        RewriteTimed timed(e, e.ticksRewrite);
        return RewriteUniform::setVec4Array(block, slot, value);
    }
    rwUniformCompare(e, mode, block, slot, value);
}
