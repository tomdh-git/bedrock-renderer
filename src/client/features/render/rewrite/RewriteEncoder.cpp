#include "client/features/render/rewrite/RewriteFunctions.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"
#include "sdk/mc/deps/bgfx/BgfxContext.h"
#include "sdk/mc/deps/bgfx/Encoder.h"
#include "sdk/mc/deps/bgfx/Frame.h"

// Q2d: bgfx::EncoderImpl::submit at 0xBC60740 (1.26.62.01), the whole body of docs/functions/bc60740.md re-read against the disassembly for this file, as a pure plan (what the call
// writes, from the encoder as it was found and the four values the call takes from outside) plus the code that applies it to the Frame.
//
// The side table (encoder+0x680, the ranged binds) is written too: commitSideTable (0xBC60F10) and the clear loop at the end of submit were read in full and are ported below with
// the game's own allocator (the interface object whose pointer sits in a global; slot 1 = realloc(self, ptr, size, align, file, line); size 0 frees). The discarded and the dropped
// draws call the game's own Encoder::reset (0xBC60D10).

static_assert(sizeof(RewriteEncoder::Plan::encoderAfter) == RewriteEncoder::kSpan);
static_assert(bgfx::EncoderOffsets::kFrame == 0x00 && bgfx::EncoderOffsets::kDepthSeq == 0x08 && bgfx::EncoderOffsets::kSeqResult == 0x0C && bgfx::EncoderOffsets::kProgram == 0x10);
static_assert(bgfx::EncoderOffsets::kViewId == 0x12 && bgfx::EncoderOffsets::kFlags == 0x14 && bgfx::EncoderOffsets::kHeader == 0x40 && bgfx::EncoderOffsets::kState == 0x60);
static_assert(bgfx::EncoderOffsets::kState2 == 0x68 && bgfx::EncoderOffsets::kRenderBind == 0x140 && bgfx::EncoderOffsets::kBindHash == 0x654 && bgfx::EncoderOffsets::kPostCallback == 0x680);
static_assert(bgfx::EncoderOffsets::kBindDirty == 0x688 && bgfx::EncoderOffsets::kSubmitted == 0x68C && bgfx::EncoderOffsets::kDiscarded == 0x690 && bgfx::EncoderOffsets::kUniformBegin == 0x694);
static_assert(bgfx::EncoderOffsets::kUniformEnd == 0x698 && bgfx::EncoderOffsets::kNumVertices == 0x69C && bgfx::EncoderOffsets::kViewSlot == 0x6AC && bgfx::EncoderOffsets::kDiscard == 0x6AD);
static_assert(bgfx::EncoderOffsets::kBindingCount * bgfx::EncoderOffsets::kBindingSize == 0x514 && bgfx::EncoderOffsets::kRenderBind + 0x514 == bgfx::EncoderOffsets::kBindHash);
static_assert(bgfx::EncoderOffsets::kNumIndices == 0x84 && bgfx::EncoderOffsets::kHeaderNumVertices == 0x8C && bgfx::EncoderOffsets::kStreamMask == 0xA3 && bgfx::EncoderOffsets::kOcclusionQuery == 0xBA);
static_assert(bgfx::FrameOffsets::kSortKeys == 0x14700 && bgfx::FrameOffsets::kSortedItems == 0x94700 && bgfx::FrameOffsets::kDrawHeaders == 0xB4700 && bgfx::FrameOffsets::kRenderDraws == 0x8B4700);
static_assert(bgfx::FrameOffsets::kRenderDrawStride == 0x540 && bgfx::FrameOffsets::kItemCount == 0xDC57E8);

static constexpr uintptr_t kRwUniformTable = 0xDC57E0;     // Frame: UniformBuffer** (one UniformBuffer { u32 size, u32 pos, data } per encoder uniform index)
static constexpr uintptr_t kRwViewModeBase = 0x1EAB1B2;    // Context: view[i].mode byte, stride 0x140
static constexpr uintptr_t kRwSeqBase = 0x1EAAC60;         // Context: u32 m_seq[256]
static constexpr size_t kRwViewStride = 0x140;
static constexpr uint64_t kRwViewBits = 0x3FC0000000000000ull;
static constexpr uint64_t kRwDefaultState = 0x010000500000001Full;
static constexpr uint32_t kRwMaxDraws = 0xFFFF;
static constexpr uint8_t kRwDrawDefaults[16] = {0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF}; // rodata 0xF08EF70, read from the exe

template <typename T>
static T& rwAt(uint8_t* base, uintptr_t offset) {
    return *reinterpret_cast<T*>(base + offset);
}
template <typename T>
static const T& rwAt(const uint8_t* base, uintptr_t offset) {
    return *reinterpret_cast<const T*>(base + offset);
}

// The draw state and bindings the submit clears after a draw that does not preserve it (bc60b6e..bc60cf6); discard (0xBC60D10) clears the same fields.
void RewriteEncoder::clearDrawState(uint8_t* e) {
    rwAt<uint64_t>(e, 0x60) = kRwDefaultState;
    rwAt<uint64_t>(e, 0x68) = 0;
    std::memset(e + 0x70, 0, 16);
    std::memcpy(e + 0x80, kRwDrawDefaults, 16);
    rwAt<uint64_t>(e, 0x90) = 0x0000000100000000ull;
    rwAt<uint64_t>(e, 0x98) = 0x0001FFFF00000000ull;
    e[0xA2] = 0;
    rwAt<uint16_t>(e, 0xA0) = 0xFFFF;
    rwAt<uint16_t>(e, 0xA3) = 0xFF00; // streamMask = 0, uniformIdx = 0xFF
    rwAt<uint64_t>(e, 0x40) = 0xFFFFFFFF00000000ull;
    rwAt<uint64_t>(e, 0xB4) = ~0ull;
    rwAt<int32_t>(e, 0xA8) = 0x7FFFFFFF;
    rwAt<uint64_t>(e, 0xAC) = 0;
    for (size_t i = 0; i < bgfx::EncoderOffsets::kBindingCount; ++i) {
        uint8_t* const b = e + bgfx::EncoderOffsets::kRenderBind + i * bgfx::EncoderOffsets::kBindingSize;
        rwAt<uint32_t>(b, 0x00) = 0;          // samplerFlags
        rwAt<uint16_t>(b, 0x0A) = 0xFFFF;     // idx
        rwAt<uint32_t>(b, 0x0C) = 0xFFFFFFFF; // extra
        b[0x13] = 0;                          // type
    }
}

static void rwClearEncoder(uint8_t* e) {
    RewriteEncoder::clearDrawState(e);
    rwAt<uint32_t>(e, 0x694) = rwAt<uint32_t>(e, 0x698); // m_uniformBegin = m_uniformEnd
    e[0x688] = 1; // m_bindDirty
}

static uint64_t rwSortKey(uint8_t viewMode, uint16_t view, uint16_t program, uint32_t depthArg, uint32_t seq, uint8_t* e) {
    const uint64_t viewBits = (static_cast<uint64_t>(view) << 54) & kRwViewBits;
    const uint32_t trans = rwAt<uint32_t>(e, 0x14) & 3;
    if (viewMode == 1) {
        rwAt<uint32_t>(e, 0x0C) = seq;
        return 0x0018000000000000ull | viewBits | (static_cast<uint64_t>(seq & 0xFFFFF) << 30) | ((static_cast<uint32_t>(program) << 17) & 0x0FFE0000u) | (static_cast<uint64_t>(trans) << 28);
    }
    if (viewMode == 2 || viewMode == 3) {
        const uint32_t depth = viewMode == 3 ? 0u - depthArg : depthArg;
        rwAt<uint32_t>(e, 0x08) = depth;
        return 0x0014000000000000ull | viewBits | (static_cast<uint64_t>(depth) << 18) | static_cast<uint16_t>(program << 5) | (static_cast<uint64_t>(trans) << 16);
    }
    return 0x0010000000000000ull | viewBits | (static_cast<uint64_t>(rwAt<uint32_t>(e, 0x08)) << 5) | (static_cast<uint64_t>(program & 0x7FF) << 37) | (static_cast<uint64_t>(trans) << 48);
}

// bc609bd..bc60a13: the vertex count of the draw is the minimum over the bound streams (0xFFFFFFFF when none, stream 0's alone for the mask 0xFF).
static uint32_t rwVertexCount(const uint8_t* e) {
    const uint8_t mask = e[0xA3];
    if (mask == 0)
        return 0xFFFFFFFFu;
    if (mask == 0xFF)
        return rwAt<uint32_t>(e, 0x69C);
    uint32_t count = 0xFFFFFFFFu;
    for (uint32_t stream = 0; stream < 8; ++stream)
        if (mask & (1u << stream))
            count = std::min(count, rwAt<uint32_t>(e, 0x69C + stream * 4));
    return count;
}

void RewriteEncoder::plan(const uint8_t* encoderBefore, uint16_t view, uint16_t program, uint16_t occlusionQuery, uint32_t depth, uint8_t preserve, const Inputs& in, Plan& out) {
    std::memcpy(out.encoderAfter, encoderBefore, kSpan);
    uint8_t* const e = out.encoderAfter;
    ++rwAt<uint32_t>(e, 0x68C);                       // m_numSubmitted
    rwAt<uint32_t>(e, 0x698) = in.uniformPos;         // m_uniformEnd
    const uint16_t prog = program == 0xFFFF ? 0 : program;
    rwAt<uint16_t>(e, 0x10) = prog;
    rwAt<uint16_t>(e, 0x12) = view;
    out.key = rwSortKey(in.viewMode, view, prog, depth, in.seq, e);
    e[0xA4] = e[0x6AC];                               // draw.m_uniformIdx
    rwAt<uint64_t>(e, 0x74) = rwAt<uint64_t>(e, 0x694); // draw.m_uniformBegin / m_uniformEnd
    rwAt<uint32_t>(e, 0x8C) = rwVertexCount(e);
    if (occlusionQuery != 0xFFFF) {
        e[0x67] |= 0x40;                              // BGFX_STATE_INTERNAL_OCCLUSION_QUERY
        rwAt<uint16_t>(e, 0xBA) = occlusionQuery;
    }
    if (e[0x688] == 1) {
        rwAt<uint32_t>(e, 0x654) = RewriteHash::murmur2a(e + bgfx::EncoderOffsets::kRenderBind, 0x514);
        e[0x688] = 0;
    }
    std::memcpy(out.header, e + bgfx::EncoderOffsets::kHeader, kHeaderSize);
    std::memcpy(out.bind, e + bgfx::EncoderOffsets::kRenderBind, kBindCopy);
    if (!preserve)
        rwClearEncoder(e);
}

using RwResetFn = void (*)(uint8_t* encoder);
using RwEnsureFn = void (*)(uint8_t* renderBindArray, uint32_t idx);

static RwResetFn rwResetFn() {
    static const RwResetFn sFn = reinterpret_cast<RwResetFn>(SigManager::get("Encoder::reset"));
    BS_CHECK(sFn != nullptr);
    return sFn;
}

static RwEnsureFn rwEnsureFn() {
    static const RwEnsureFn sFn = reinterpret_cast<RwEnsureFn>(SigManager::get("Encoder::ensureBind"));
    BS_CHECK(sFn != nullptr);
    return sFn;
}

static uint8_t* rwContext() {
    return reinterpret_cast<uint8_t*>(BgfxContext::get());
}

static uint32_t rwUniformPos(uint8_t* frame, uint8_t uniformIdx) {
    uint8_t** const table = rwAt<uint8_t**>(frame, kRwUniformTable);
    return rwAt<uint32_t>(table[uniformIdx], 4);
}

static uint8_t rwViewMode(uint16_t view) {
    return rwContext()[kRwViewModeBase + static_cast<size_t>(view) * kRwViewStride];
}

// bc607bf..bc607ff: take the next render item slot, saturating at 0xFFFF, and report the one that was taken.
static uint32_t rwClaimSlot(uint8_t* frame) {
    volatile long* const counter = reinterpret_cast<volatile long*>(frame + bgfx::FrameOffsets::kItemCount);
    uint32_t seen = static_cast<uint32_t>(*counter), idx, next;
    do {
        idx = seen;
        next = (idx + 1 >= kRwMaxDraws || idx >= kRwMaxDraws) ? kRwMaxDraws : idx + 1;
        seen = static_cast<uint32_t>(_InterlockedCompareExchange(counter, static_cast<long>(next), static_cast<long>(idx)));
    } while (idx != kRwMaxDraws && idx != seen);
    return idx;
}

static void rwDropDraw(uint8_t* e) {
    rwResetFn()(e);
    ++rwAt<uint32_t>(e, 0x690); // m_numDropped
}

// The allocator: `mov rcx,[rip+rel32]` at submit+0x535 (0xBC60C75 in 62.01) loads the global holding the allocator interface; the instruction is checked, never assumed.
struct RwAllocator {
    void** vtable;
};
using RwReallocFn = void* (*)(RwAllocator* self, void* ptr, size_t size, size_t align, const char* file, uint32_t line);
static constexpr size_t kRwSideEntries = 0x41;
static constexpr size_t kRwSideTableBytes = 0x410; // entries; the u32 `used` follows
static constexpr size_t kRwSideEntrySize = 0x14;   // one Binding
static constexpr uintptr_t kRwFrameSideTables = 0x8B4778;

static RwAllocator** rwAllocatorSlot() {
    static RwAllocator** const sSlot = [] {
        const uint8_t* const at = reinterpret_cast<const uint8_t*>(SigManager::get("Encoder::submit") + 0x535);
        BS_CHECK(at[0] == 0x48 && at[1] == 0x8B && at[2] == 0x0D);
        return reinterpret_cast<RwAllocator**>(reinterpret_cast<uintptr_t>(at) + 7 + *reinterpret_cast<const int32_t*>(at + 3));
    }();
    return sSlot;
}

static void* rwRealloc(RwAllocator* a, void* ptr, size_t size) {
    return reinterpret_cast<RwReallocFn>(a->vtable[1])(a, ptr, size, 0, nullptr, 0);
}

// bc60c65..bc60cec (and the same loop in discard): free every entry's array through the allocator, or zero the table when there is no allocator; used = 0.
void RewriteEncoder::clearSideTable(uint8_t* table) {
    RwAllocator* const a = *rwAllocatorSlot();
    if (a) {
        for (size_t i = 0; i < kRwSideEntries; ++i) {
            uint8_t* const entry = table + i * 16;
            rwRealloc(a, *reinterpret_cast<void**>(entry), 0);
            std::memset(entry, 0, 16);
        }
    } else {
        std::memset(table, 0, kRwSideTableBytes);
    }
    rwAt<uint32_t>(table, kRwSideTableBytes) = 0;
}

// 0xBC60F10 commitSideTable(frame, idx, src): copy the encoder's ranged binds into the frame's table of draw idx, allocated on first use and kept across frames.
void RewriteEncoder::commitSideTable(uint8_t* frame, uint32_t idx, const uint8_t* src) {
    uint8_t*& slot = rwAt<uint8_t*>(frame, kRwFrameSideTables + static_cast<uintptr_t>(idx) * 8);
    uint8_t* dst = slot;
    if (rwAt<uint32_t>(src, kRwSideTableBytes) == 0) {
        if (dst && rwAt<uint32_t>(dst, kRwSideTableBytes) != 0)
            RewriteEncoder::clearSideTable(dst);
        return;
    }
    RwAllocator* const a = *rwAllocatorSlot();
    if (!dst) {
        dst = static_cast<uint8_t*>(rwRealloc(a, nullptr, kRwSideTableBytes + 8));
        std::memset(dst, 0, kRwSideTableBytes);
        slot = dst;
    }
    if (dst != src) {
        for (size_t i = 0; i < kRwSideEntries; ++i) {
            const uint64_t count = rwAt<uint64_t>(src, i * 16 + 8);
            uint8_t* const entry = dst + i * 16;
            void* data = nullptr;
            if (a) {
                rwRealloc(a, *reinterpret_cast<void**>(entry), 0);
                std::memset(entry, 0, 16);
                data = rwRealloc(a, nullptr, static_cast<size_t>(count) * kRwSideEntrySize);
            }
            *reinterpret_cast<void**>(entry) = data;
            rwAt<uint64_t>(entry, 8) = count;
            const void* const from = *reinterpret_cast<void* const*>(src + i * 16);
            if (from)
                std::memcpy(data, from, static_cast<size_t>(count) * kRwSideEntrySize);
        }
    }
    const uint32_t used = rwAt<uint32_t>(src, kRwSideTableBytes);
    rwAt<uint32_t>(dst, kRwSideTableBytes) = used;
}

void RewriteEncoder::submit(uint8_t* e, uint16_t view, uint16_t program, uint16_t occlusionQuery, uint32_t depth, uint8_t preserve, SubmitFn) {
    if (e[0x6AD] == 1) { // discarded by the caller
        rwResetFn()(e);
        return;
    }
    if ((rwAt<uint32_t>(e, 0x84) | rwAt<uint32_t>(e, 0x8C)) == 0) { // nothing to draw
        rwDropDraw(e);
        return;
    }
    uint8_t* const frame = rwAt<uint8_t*>(e, 0);
    const uint32_t idx = rwClaimSlot(frame);
    if (idx >= 0xFFFE) {
        rwDropDraw(e);
        return;
    }
    Inputs in;
    in.idx = idx;
    in.viewMode = rwViewMode(view);
    in.seq = in.viewMode == 1 ? static_cast<uint32_t>(_InterlockedExchangeAdd(reinterpret_cast<volatile long*>(rwContext() + kRwSeqBase + static_cast<size_t>(view) * 4), 1)) : 0;
    in.uniformPos = rwUniformPos(frame, e[0x6AC]);
    static thread_local Plan tPlan;
    plan(e, view, program, occlusionQuery, depth, preserve, in, tPlan);
    rwAt<uint64_t>(frame, bgfx::FrameOffsets::kSortKeys + static_cast<uintptr_t>(idx) * 8) = tPlan.key;
    rwAt<uint16_t>(frame, bgfx::FrameOffsets::kSortedItems + static_cast<uintptr_t>(idx) * 2) = static_cast<uint16_t>(idx);
    std::memcpy(frame + bgfx::FrameOffsets::kDrawHeaders + (static_cast<uintptr_t>(idx) << 7), tPlan.header, kHeaderSize);
    rwEnsureFn()(frame + bgfx::FrameOffsets::kRenderDraws, idx);
    std::memcpy(rwAt<uint8_t*>(frame, bgfx::FrameOffsets::kRenderDraws) + static_cast<size_t>(idx) * bgfx::FrameOffsets::kRenderDrawStride, tPlan.bind, kBindCopy);
    uint8_t* const sideTable = rwAt<uint8_t*>(e, 0x680);
    if (sideTable)
        RewriteEncoder::commitSideTable(frame, idx, sideTable);
    std::memcpy(e, tPlan.encoderAfter, kSpan);
    if (sideTable && !preserve)
        RewriteEncoder::clearSideTable(sideTable);
}

static RewriteEntry sEncoderEntry("Encoder::submit", "Encoder::submit", 0xBC60740, nullptr, true);
static const RewriteReg sEncoderReg(sEncoderEntry);
static std::mutex sRwEncoderVerifyMutex;

static void rwEncoderCompare(RewriteEntry& e, RewriteMode mode, RewriteEncoder::SubmitFn original, uint8_t* enc, uint32_t view, uint32_t program, uint32_t query, uint32_t depth, uint8_t preserve) {
    if (enc[0x6AD] == 1 || (rwAt<uint32_t>(enc, 0x84) | rwAt<uint32_t>(enc, 0x8C)) == 0) {
        e.skipped.fetch_add(1, std::memory_order_relaxed); // discarded draw or empty draw: the game's own paths, nothing to plan
        original(enc, view, program, query, depth, preserve);
        return;
    }
    // One verified submit at a time: the slot counter and the view's sequence counter are shared with every other encoder, and the comparison needs to know which slot this call got.
    std::lock_guard<std::mutex> lock(sRwEncoderVerifyMutex);
    uint8_t* const frame = rwAt<uint8_t*>(enc, 0);
    static thread_local uint8_t tBefore[RewriteEncoder::kSpan];
    static thread_local RewriteEncoder::Plan tPlan;
    std::memcpy(tBefore, enc, RewriteEncoder::kSpan);
    const uint32_t idx = rwAt<uint32_t>(frame, bgfx::FrameOffsets::kItemCount);
    const uint32_t posBefore = rwUniformPos(frame, enc[0x6AC]);
    static thread_local std::vector<uint8_t> tSide[kRwSideEntries];
    static thread_local uint64_t tSideCount[kRwSideEntries];
    uint8_t* const side = rwAt<uint8_t*>(enc, 0x680);
    const uint32_t sideUsed = side ? rwAt<uint32_t>(side, kRwSideTableBytes) : 0;
    if (sideUsed) {
        for (size_t i = 0; i < kRwSideEntries; ++i) {
            tSideCount[i] = rwAt<uint64_t>(side, i * 16 + 8);
            const uint8_t* const data = *reinterpret_cast<uint8_t* const*>(side + i * 16);
            tSide[i].assign(data, data + tSideCount[i] * kRwSideEntrySize);
        }
    }
    {
        RewriteTimed timed(e, e.ticksOriginal);
        original(enc, view, program, query, depth, preserve);
    }
    // The compute / custom-item / frame-parameter forms (0xBC61140, 0xBC61560, 0xBC618E0) take slots too and are not serialised here: a call that did not take exactly slot idx
    // cannot be compared. These are counted in skipped; they are rare (no custom item or compute in a normal frame).
    if (idx >= 0xFFFE || rwAt<uint32_t>(frame, bgfx::FrameOffsets::kItemCount) != idx + 1) {
        e.skipped.fetch_add(1, std::memory_order_relaxed);
        return;
    }
    RewriteEncoder::Inputs in;
    in.idx = idx;
    in.viewMode = rwViewMode(static_cast<uint16_t>(view));
    in.seq = in.viewMode == 1 ? rwAt<uint32_t>(enc, 0x0C) : 0; // the value the original took from the view's counter, left in the encoder
    in.uniformPos = posBefore;
    {
        RewriteTimed timed(e, e.ticksRewrite);
        RewriteEncoder::plan(tBefore, static_cast<uint16_t>(view), static_cast<uint16_t>(program), static_cast<uint16_t>(query), depth, preserve, in, tPlan);
    }
    e.evaluated.fetch_add(1, std::memory_order_relaxed);
    RewriteVerify::compare(e, mode, "sort key", frame + bgfx::FrameOffsets::kSortKeys + static_cast<size_t>(idx) * 8, &tPlan.key, 8);
    const uint16_t value = static_cast<uint16_t>(idx);
    RewriteVerify::compare(e, mode, "sort value", frame + bgfx::FrameOffsets::kSortedItems + static_cast<size_t>(idx) * 2, &value, 2);
    RewriteVerify::compare(e, mode, "draw header", frame + bgfx::FrameOffsets::kDrawHeaders + (static_cast<size_t>(idx) << 7), tPlan.header, RewriteEncoder::kHeaderSize);
    RewriteVerify::compare(e, mode, "bind block", rwAt<uint8_t*>(frame, bgfx::FrameOffsets::kRenderDraws) + static_cast<size_t>(idx) * bgfx::FrameOffsets::kRenderDrawStride, tPlan.bind, RewriteEncoder::kBindCopy);
    RewriteVerify::compare(e, mode, "encoder after", enc, tPlan.encoderAfter, RewriteEncoder::kSpan);
    if (sideUsed) {
        const uint8_t* const dst = rwAt<uint8_t*>(frame, kRwFrameSideTables + static_cast<size_t>(idx) * 8);
        BS_CHECK(dst != nullptr);
        RewriteVerify::compareValue(e, mode, "side table used", rwAt<uint32_t>(dst, kRwSideTableBytes), sideUsed);
        for (size_t i = 0; i < kRwSideEntries; ++i) {
            RewriteVerify::compareValue(e, mode, "side entry count", rwAt<uint64_t>(dst, i * 16 + 8), tSideCount[i]);
            RewriteVerify::compare(e, mode, "side entry bindings", *reinterpret_cast<uint8_t* const*>(dst + i * 16), tSide[i].data(), tSide[i].size());
        }
        const uint32_t expectedSrcUsed = preserve ? sideUsed : 0;
        RewriteVerify::compareValue(e, mode, "encoder side table used after", rwAt<uint32_t>(side, kRwSideTableBytes), expectedSrcUsed);
    }
}

void RewriteEncoder::dispatch(SubmitFn original, uint8_t* encoder, uint32_t view, uint32_t program, uint32_t query, uint32_t depth, uint8_t preserve) {
    RewriteEntry& e = sEncoderEntry;
    const uint64_t calls = e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0)
        return original(encoder, view, program, query, depth, preserve);
    if (mode == RewriteMode::On) {
        if ((calls & 15) != 0)
            return submit(encoder, static_cast<uint16_t>(view), static_cast<uint16_t>(program), static_cast<uint16_t>(query), depth, preserve, original);
        RewriteTimed timed(e, e.ticksRewrite);
        return submit(encoder, static_cast<uint16_t>(view), static_cast<uint16_t>(program), static_cast<uint16_t>(query), depth, preserve, original);
    }
    rwEncoderCompare(e, mode, original, encoder, view, program, query, depth, preserve);
}
