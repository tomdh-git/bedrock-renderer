#include "client/features/render/rewrite/RewriteFunctions.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "client/features/render/rewrite/RewriteProbe.h"
#include "sdk/mc/deps/bgfx/Frame.h"

// Q2c: Frame::sort at 0xBC61E20 (1.26.62.01; docs/functions/bc61e20.md). The radix sorts behind it were read for this file (0xBC62040 for u64 keys + u16 values, 0xBC62BC0 for the u32
// blit keys): stock bx::radixSort, 11-bit digits at shifts 0, 11, 22, 33, 44, 55, one histogram per pass, a pass whose input is already sorted by the full key ends the sort (and
// copies the data back when it sits in the scratch), so the result is the STABLE ascending sort by the full 64-bit key, values carried along. The rewrite computes exactly that
// result: all six histograms in one read of the keys, a pass is skipped when every key has the same digit (its scatter would be the identity), and an input that is already sorted
// is left alone. The blit keys are 32-bit and carry no values: equal keys are identical, so any ascending sort gives the same bytes.

static_assert(bgfx::FrameOffsets::kSortKeys == 0x14700 && bgfx::FrameOffsets::kSortedItems == 0x94700 && bgfx::FrameOffsets::kBlitKeys == 0x934778);
static_assert(bgfx::FrameOffsets::kItemCount == 0xDC57E8 && bgfx::FrameOffsets::kBlitCount == 0xDC57EC && bgfx::FrameOffsets::kViewRemap == 0);

static constexpr int kRwDigitBits = 11;
static constexpr uint32_t kRwDigits = 1u << kRwDigitBits;
static constexpr int kRwPasses = 6; // 6 * 11 = 66 >= 64

// Scratch of the sort. Frame::sort runs on the bgfx render thread only (it is called from the three renderer submits); verify mode may sort a private copy on that thread too.
static uint64_t sRwTempKeys[RewriteFrame::kMaxItems];
static uint16_t sRwTempValues[RewriteFrame::kMaxItems];
static std::atomic<bool> sRwSorting{false};

static void rwRadixSort(uint64_t* keys, uint16_t* values, uint32_t count) {
    if (count < 2)
        return;
    bool sorted = true;
    static uint32_t histogram[kRwPasses][kRwDigits];
    std::memset(histogram, 0, sizeof(histogram));
    uint64_t previous = keys[0];
    for (uint32_t i = 0; i < count; ++i) {
        const uint64_t key = keys[i];
        sorted &= previous <= key;
        previous = key;
        for (int pass = 0; pass < kRwPasses; ++pass)
            ++histogram[pass][(key >> (pass * kRwDigitBits)) & (kRwDigits - 1)];
    }
    if (sorted)
        return;
    uint64_t* srcKeys = keys;
    uint16_t* srcValues = values;
    uint64_t* dstKeys = sRwTempKeys;
    uint16_t* dstValues = sRwTempValues;
    for (int pass = 0; pass < kRwPasses; ++pass) {
        uint32_t* h = histogram[pass];
        const uint32_t firstDigit = (srcKeys[0] >> (pass * kRwDigitBits)) & (kRwDigits - 1);
        if (h[firstDigit] == count)
            continue; // every key has this digit: the scatter is the identity
        uint32_t sum = 0;
        for (uint32_t d = 0; d < kRwDigits; ++d) {
            const uint32_t n = h[d];
            h[d] = sum;
            sum += n;
        }
        for (uint32_t i = 0; i < count; ++i) {
            const uint64_t key = srcKeys[i];
            const uint32_t at = h[(key >> (pass * kRwDigitBits)) & (kRwDigits - 1)]++;
            dstKeys[at] = key;
            dstValues[at] = srcValues[i];
        }
        std::swap(srcKeys, dstKeys);
        std::swap(srcValues, dstValues);
    }
    if (srcKeys != keys) {
        std::memcpy(keys, srcKeys, count * sizeof(uint64_t));
        std::memcpy(values, srcValues, count * sizeof(uint16_t));
    }
}

void RewriteFrame::sortArrays(const uint16_t* viewRemap, uint64_t* keys, uint16_t* values, uint32_t itemCount, uint32_t* blitKeys, uint32_t blitCount) {
    BS_CHECK(!sRwSorting.exchange(true));
    BS_CHECK(itemCount <= kMaxItems);
    uint16_t inverse[256] = {};
    for (uint32_t i = 0; i < 256; ++i) {
        BS_CHECK(viewRemap[i] < 256);
        inverse[viewRemap[i]] = static_cast<uint16_t>(i);
    }
    for (uint32_t i = 0; i < itemCount; ++i) {
        const uint64_t key = keys[i];
        const uint8_t view = static_cast<uint8_t>(key >> 54);
        keys[i] = (key & 0xC03FFFFFFFFFFFFFull) | (static_cast<uint64_t>(inverse[view]) << 54);
    }
    rwRadixSort(keys, values, itemCount);
    for (uint32_t i = 0; i < blitCount; ++i) {
        uint8_t* const view = reinterpret_cast<uint8_t*>(&blitKeys[i]) + 3;
        *view = static_cast<uint8_t>(inverse[*view]);
    }
    std::sort(blitKeys, blitKeys + blitCount);
    sRwSorting.store(false);
}

void RewriteFrame::sort(uint8_t* frame) {
    sortArrays(reinterpret_cast<const uint16_t*>(frame + bgfx::FrameOffsets::kViewRemap), reinterpret_cast<uint64_t*>(frame + bgfx::FrameOffsets::kSortKeys),
        reinterpret_cast<uint16_t*>(frame + bgfx::FrameOffsets::kSortedItems), *reinterpret_cast<const uint32_t*>(frame + bgfx::FrameOffsets::kItemCount),
        reinterpret_cast<uint32_t*>(frame + bgfx::FrameOffsets::kBlitKeys), *reinterpret_cast<const uint16_t*>(frame + bgfx::FrameOffsets::kBlitCount));
}

static void rwFrameSortDetour(uint8_t* frame);
static RewriteEntry sFrameSortEntry("Frame::sort", "Encoder::frameSort", 0xBC61E20, reinterpret_cast<void*>(&rwFrameSortDetour));
static const RewriteReg sFrameSortReg(sFrameSortEntry);

// Shadow / Verify: the rewrite sorts private copies of the arrays (taken before the original runs), the original sorts the real frame, the arrays are compared. The original also
// writes the context's scratch arrays (ctx+0x1CFD0D0 / +0x1D7D0C8); nothing reads them after the sort (BGFX_MAP 6ek) [I], so they are not compared.
static void rwFrameSortCompare(RewriteEntry& e, RewriteMode mode, uint8_t* frame) {
    RewriteBusy::Scope busy;
    const uint32_t items = *reinterpret_cast<const uint32_t*>(frame + bgfx::FrameOffsets::kItemCount);
    const uint32_t blits = *reinterpret_cast<const uint16_t*>(frame + bgfx::FrameOffsets::kBlitCount);
    uint64_t* const keys = reinterpret_cast<uint64_t*>(frame + bgfx::FrameOffsets::kSortKeys);
    uint16_t* const values = reinterpret_cast<uint16_t*>(frame + bgfx::FrameOffsets::kSortedItems);
    uint32_t* const blit = reinterpret_cast<uint32_t*>(frame + bgfx::FrameOffsets::kBlitKeys);
    static thread_local std::vector<uint64_t> tKeys;
    static thread_local std::vector<uint16_t> tValues;
    static thread_local std::vector<uint32_t> tBlit;
    static thread_local std::vector<uint16_t> tRemap;
    tKeys.assign(keys, keys + items);
    tValues.assign(values, values + items);
    tBlit.assign(blit, blit + blits);
    tRemap.assign(reinterpret_cast<const uint16_t*>(frame), reinterpret_cast<const uint16_t*>(frame) + 256);
    {
        RewriteTimed timed(e, e.ticksOriginal);
        e.original<&rwFrameSortDetour>()(frame);
    }
    {
        RewriteTimed timed(e, e.ticksRewrite);
        RewriteFrame::sortArrays(tRemap.data(), tKeys.data(), tValues.data(), items, tBlit.data(), blits);
    }
    e.evaluated.fetch_add(1, std::memory_order_relaxed);
    RewriteVerify::compare(e, mode, "sorted keys", keys, tKeys.data(), static_cast<size_t>(items) * sizeof(uint64_t));
    RewriteVerify::compare(e, mode, "sorted item ids", values, tValues.data(), static_cast<size_t>(items) * sizeof(uint16_t));
    RewriteVerify::compare(e, mode, "sorted blit keys", blit, tBlit.data(), static_cast<size_t>(blits) * sizeof(uint32_t));
}

// rcx = the Frame. Called once per frame by each renderer's submit, on the render thread.
static void rwFrameSortDetour(uint8_t* frame) {
    RewriteEntry& e = sFrameSortEntry;
    e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0) {
        e.original<&rwFrameSortDetour>()(frame);
    } else if (mode == RewriteMode::On) {
        RewriteTimed timed(e, e.ticksRewrite);
        RewriteFrame::sort(frame);
    } else {
        rwFrameSortCompare(e, mode, frame);
    }
    RewriteProbe::captureFrame(frame); // read-only; the frame is complete and sorted here
}
