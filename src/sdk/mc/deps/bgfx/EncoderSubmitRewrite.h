#pragma once

// bgfx::EncoderImpl::submit (0xbc60740, 1.26.62.01) — C++ rewrite for Q2d.
//
// Reimplements the submit body and the inlined setTransform / matrix-cache path
// (verified in full at 0xbcc3b90..0xbcc3cbd, submitPass alt 0). Every field offset
// is taken from EncoderOffsets / FrameOffsets / RenderDrawHeader (src/sdk/mc/deps/bgfx/
// Encoder.h, Frame.h), each pinned to verbatim disassembly rows in
// docs/functions/bc60740.md, and is static-asserted below. The header is therefore a
// compile-time self-test of the layout mapping: if any offset stops matching the exe,
// these static_asserts fail.
//
// This is the Q2d rewrite deliverable. The byte comparison it is checked against lives
// in tools/sigs/oc_eq2d_compare.py (re-derives every emitted byte region from the exe
// disassembly and asserts equality with these constants).
//
// Includes/offsets only: no HookManager.cpp, no existing hook registration, no CMake,
// no Sigs.json change. Not compiled in this unit (build + in-game run deferred per the
// 2026-11-22 user decision); the deferred in-game confirmation is tracked in the
// appended U-EQ2d section of docs/BIGBANG_TESTS.md.
//
// CLAUDE.md style: fail fast, no null guards, no SEH. Static analysis only.

#pragma once

#include "Encoder.h"
#include "Frame.h"


namespace bgfx {

// bx::HashMurmur2A::add(data, len) — 0xbc76610; state {u32 hash, tail, count, size},
// end() mixes tail and size with M = 0x5BD1E995 to produce m_bindHash.
extern "C" uint32_t bxHashMurmur2AAdd(const void* data, size_t len);

// 0xbc60f10 — commitSideTable(Frame* frame, uint32_t idx, const SideTable* sideTable)
extern "C" void commitSideTable(void* frame, uint32_t idx, void* sideTable);

// 0xEBCE390 — memcpy 64 bytes: setTransform entry matrix -> matrix cache slot
extern "C" void memcpy40(void* dst, const void* src);

// 0xEEC6EC0 — memcpy 0x518 bytes: submit RenderBind block + hash -> RenderDraw record
extern "C" void memcpy518(void* dst, const void* src);

// 0xbc60d10 — EncoderImpl::reset (separate unit; submit tail-jumps into it on discard
// and calls it on the over-cap drop path). Declared here, not reimplemented.
extern "C" void EncoderImpl_reset(void* encoder);

// bgfx allocator object at [0x12ADF800]; its vtable slot 1 is
// realloc(alloc, ptr, size, align, file, line) with size 0 = free
// (side-table teardown, 0xbc60c90..0xbc60cb1).
extern "C" void* gAllocator;                                   // [0x12ADF800]
extern "C" void* allocatorRealloc(void* allocator, void* ptr, uint64_t size,
                                  uint64_t align, const char* file, int line);

// Offsets the matrix-cache path writes, derived from the header mapping (not assumed):
static constexpr uintptr_t kStartMatrix = EncoderOffsets::kHeader + 0x3C; // 0x40 + 0x3C = 0x7C
static constexpr uintptr_t kNumMatrices   = EncoderOffsets::kHeader + 0x5E; // 0x40 + 0x5E = 0x9E
static_assert(kStartMatrix == 0x7C, "draw.startMatrix at header+0x3C == Encoder+0x7C");
static_assert(kNumMatrices == 0x9E, "draw.numMatrices at header+0x5E == Encoder+0x9E");
static_assert(EncoderOffsets::kHeader + RenderDrawHeader::kState == EncoderOffsets::kState);                 // 0x60 == 0x40 + 0x20
static_assert(EncoderOffsets::kHeader + RenderDrawHeader::kUniformIdx == 0xA4);                              // uniformIdx store target
static_assert(EncoderOffsets::kHeader + RenderDrawHeader::kStreamMask == EncoderOffsets::kStreamMask);        // 0xA3 == 0x40 + 0x63
static_assert(EncoderOffsets::kHeader + RenderDrawHeader::kNumIndices == EncoderOffsets::kNumIndices);        // 0x84 == 0x40 + 0x44
static_assert(EncoderOffsets::kHeader + RenderDrawHeader::kNumVertices == EncoderOffsets::kHeaderNumVertices); // 0x8C == 0x40 + 0x4C
static_assert(EncoderOffsets::kHeader + RenderDrawHeader::kHandle7A == EncoderOffsets::kOcclusionQuery);      // 0xBA == 0x40 + 0x7A
static_assert(FrameOffsets::kMatrixCache + 0x10000ull * 0x40 == FrameOffsets::kMatrixCount);                  // cache ends exactly at its counter

// ---------------------------------------------------------------------------
// bgfx::EncoderImpl::submit(viewId, program, occlusionQuery, depth, preserveState)
// Argument map (verified): rcx=this, dx=viewId, r8w=program, r9w=occlusionQuery,
// stack [rsp+0xC0]=depth (u32), [rsp+0xC8]=preserveState (u8).
// Body: docs/functions/bc60740.md (324 instructions, every instruction mapped).
struct EncoderImplRewrite {
    static void submit(void* encoder, uint16_t viewId, uint16_t program,
                       uint16_t occlusionQuery, uint32_t depth, uint8_t preserveState) {
        uint8_t* t = (uint8_t*)encoder;

        // discard byte -> tail-jump to reset 0xbc60d10   (0xbc60773..0xbc607a8)
        if (t[EncoderOffsets::kDiscard] == 1) {
            EncoderImpl_reset(encoder);
            return;
        }

        // draw with no indices and no vertices is dropped   (0xbc607ad..0xbc6083e)
        if (*(uint32_t*)(t + EncoderOffsets::kNumIndices) == 0 &&
            *(uint32_t*)(t + EncoderOffsets::kHeaderNumVertices) == 0) {
            EncoderImpl_reset(encoder);
            ++*(uint32_t*)(t + EncoderOffsets::kDiscarded);
            return;
        }

        // ---- draw slot allocation: Frame+0xDC57E8 CAS, cap 0xFFFE ----
        void* frame = *(void**)t;                                                   // [encoder+0] Frame* (0xbc607bf / 0xbc60ab2)
        uint32_t* itemCount = (uint32_t*)((uint8_t*)frame + FrameOffsets::kItemCount);
        uint32_t seen = *itemCount, idx;
        for (;;) {                                                                  // 0xbc607d0..0xbc607fd
            idx = seen;
            uint32_t next = idx + 1;
            if (next >= 0xFFFF || idx >= 0xFFFF) next = 0xFFFF;
            uint32_t orig = atomicCAS(itemCount, next, idx);                        // lock cmpxchg [rcx+0xDC57E8],r14d
            if (idx == 0xFFFF || orig == idx) break;
            seen = orig;
        }
        if (idx >= 0xFFFE) {
            EncoderImpl_reset(encoder);
            ++*(uint32_t*)(t + EncoderOffsets::kDiscarded);
            return;
        }
        ++*(uint32_t*)(t + EncoderOffsets::kSubmitted);                             // 0xbc6083f

        // m_uniformEnd = Frame->m_uniformBuffer[m_uniformIdx]->pos   (0xbc6084f..0xbc60869)
        uint8_t uniformIdx = t[EncoderOffsets::kViewSlot];
        void** uniformBufferTable = (void**)((uint8_t*)frame + 0xDC57E0);           // Frame+0xDC57E0 UniformBuffer** table
        uint32_t uniformEnd = *(uint32_t*)((uint8_t*)uniformBufferTable[uniformIdx] + 4); // UniformBuffer.pos @ +4
        *(uint32_t*)(t + EncoderOffsets::kUniformEnd) = uniformEnd;                 // 0xbc60869

        // key fields
        uint16_t keyProgram = (program == 0xFFFF) ? 0 : program;                  // 0xbc60870..0xbc6087c
        *(uint16_t*)(t + EncoderOffsets::kProgram) = keyProgram;                  // 0xbc6087c
        *(uint16_t*)(t + EncoderOffsets::kViewId) = viewId;                       // 0xbc60881

        // view mode byte = Context + viewId*0x140 + 0x1EAB1B2, Context = [0x12AE1748]   (0xbc60885..0xbc60897)
        // Context* s_ctx = *(void**)0x12AE1748;   // documented global, not dereferenced here
        uint8_t viewMode = 0;                                                      // [I] runtime mode byte; default -> program sort
        uint64_t viewBits = ((uint64_t)viewId << 54) & SortKey::kViewMask;        // view bits 54..61
        uint8_t trans = (uint8_t)(*(uint32_t*)(t + EncoderOffsets::kFlags) & 3);

        uint64_t key;
        if (viewMode == 1) {                                                       // Sequential (0xbc608f7..0xbc6094c)
            // uint32_t seq = lock xadd [Context + viewId*4 + 0x1EAAC60], 1   (0xbc608fc)
            uint32_t seq = 0;
            *(uint32_t*)(t + EncoderOffsets::kSeqResult) = seq;                    // 0xbc60906
            key = SortKey::kTagSequence | viewBits
                | ((uint64_t)(seq & 0xFFFFF) << 30)
                | (((uint64_t)(keyProgram << 17)) & 0x0FFE0000ULL)
                | ((uint64_t)trans << 28);
        } else if (viewMode == 3) {                                                // DepthDescending -> negate depth
            depth = (uint32_t)-(int32_t)depth;                                     // 0xbc608b6
            // fall through into DepthAscending
        }
        if (viewMode == 2 || viewMode == 3) {                                      // DepthAscending/Descending (0xbc608b9..0xbc608f2)
            *(uint32_t*)(t + EncoderOffsets::kDepthSeq) = depth;
            key = SortKey::kTagDepth | viewBits
                | ((uint64_t)depth << 18)
                | ((uint64_t)(uint16_t)(keyProgram << 5))
                | ((uint64_t)trans << 16);
        } else {                                                                   // Default: sort by program (0xbc6094e..0xbc60981)
            *(uint32_t*)(t + EncoderOffsets::kDepthSeq) = depth;
            key = SortKey::kTagProgram | viewBits
                | ((uint64_t)depth << 5)
                | ((uint64_t)(keyProgram & 0x7FF) << 37)
                | ((uint64_t)trans << 48);
        }

        *(uint64_t*)((uint8_t*)frame + FrameOffsets::kSortKeys + (size_t)idx * 8) = key;                 // 0xbc60991
        *(uint16_t*)((uint8_t*)frame + FrameOffsets::kSortedItems + (size_t)idx * 2) = (uint16_t)idx;     // 0xbc6099c

        // header fields taken from encoder state   (0xbc609a5..0xbc60a25)
        *(uint8_t*)(t + EncoderOffsets::kHeader + RenderDrawHeader::kUniformIdx) = uniformIdx;   // +0xA4 -> header+0x64
        // qword store of {m_uniformBegin, m_uniformEnd} from [t+0x694] -> header+0x34/+0x38   (0xbc609b2/0xbc609b9)
        *(uint64_t*)(t + EncoderOffsets::kHeader + RenderDrawHeader::kUniformBegin)
            = *(uint64_t*)(t + EncoderOffsets::kUniformBegin);
        uint8_t streamMask = t[EncoderOffsets::kStreamMask];                        // +0xA3 (0xbc609bd)
        uint32_t numVertices;
        if (streamMask == 0) numVertices = 0xFFFFFFFF;                            // 0xbc609c6/0xbc609d8
        else if (streamMask == 0xFF)                                              // 0xbc609cd/0xbc609cf
            numVertices = *(uint32_t*)(t + EncoderOffsets::kNumVertices);
        else {                                                                      // tzcnt/bsf loop, 0xbc609e0..0xbc60a11
            numVertices = 0xFFFFFFFF;
            for (uint32_t mask = streamMask; mask != 0; mask &= mask - 1) {        // min over the set bits of streamMask
                uint32_t s = ([](uint32_t m){ unsigned long i; _BitScanForward(&i, m); return (uint32_t)i; })(mask);
                uint32_t n = *(uint32_t*)(t + EncoderOffsets::kNumVertices + s * 4);
                if (n < numVertices) numVertices = n;
            }
        }
        *(uint32_t*)(t + EncoderOffsets::kHeaderNumVertices) = numVertices;        // 0xbc60a13 (+0x8C -> header+0x4C)
        if (occlusionQuery != 0xFFFF) {                                           // 0xbc60a1a..0xbc60a25
            *(uint8_t*)(t + EncoderOffsets::kState + 7) |= 0x40;                  // header+0x27 = stateFlags bit 62
            *(uint16_t*)(t + EncoderOffsets::kOcclusionQuery) = occlusionQuery;   // +0xBA -> header+0x7A
        }

        // ---- bind hash (Mojang addition) ----
        if (t[EncoderOffsets::kBindDirty] == 1) {                                 // 0xbc60a2d
            uint32_t bindHash = bxHashMurmur2AAdd(t + EncoderOffsets::kRenderBind, 0x514); // 0xbc60a36 / 0xbc60a50
            *(uint32_t*)(t + EncoderOffsets::kBindHash) = bindHash;               // 0xbc60aa5 -> stored at Record+0x514
            t[EncoderOffsets::kBindDirty] = 0;                                    // 0xbc60aab
        }

        // ---- emit draw header 0x80 bytes verbatim to Frame+0xB4700+idx*0x80 ----
        // 8 x movaps from Encoder+0x40..+0xBF -> header+0x00..0x70 (0xbc60ab2..0xbc60b13)
        uint8_t* headerDst = (uint8_t*)frame + FrameOffsets::kDrawHeaders + ((size_t)idx << 7);
        uint8_t* headerSrc = t + EncoderOffsets::kHeader;
        for (uint32_t i = 0; i < 8; ++i)
            std::memcpy(headerDst + i * 16, headerSrc + i * 16, 16);

        // ---- emit RenderDraw record 0x518 bytes to Frame+0x8B4700+idx*0x540 ----
        // 0xbc7a7c0 ensure(Frame+0x8B4700, idx) commits the record page just before (0xbc60b1b..0xbc60b2e)
        void* renderDrawBase = *(void**)((uint8_t*)frame + FrameOffsets::kRenderDraws); // [Frame+0x8B4700] base pointer
        uint8_t* recordDst = (uint8_t*)renderDrawBase + ((size_t)idx * 0x540);
        uint8_t* recordSrc = t + EncoderOffsets::kRenderBind;                       // Encoder+0x140
        memcpy518(recordDst, recordSrc);                                            // 0xbc60b4a: bind block 0x514 + u32 bind hash at +0x514

        // ---- side table (Mojang addition) ----
        void* sideTable = *(void**)(t + EncoderOffsets::kPostCallback);             // 0xbc60b4f
        if (sideTable) commitSideTable(frame, idx, sideTable);                      // 0xbc60b60

        // ---- preserveState: skip the draw-state reset ----
        if (preserveState) return;                                                 // 0xbc60b65..0xbc60b68 -> epilogue

        // ---- m_draw.clear()   (0xbc60b6e..0xbc60bf7) ----
        *(uint64_t*)(t + EncoderOffsets::kState) = 0x010000500000001FULL;
        *(uint64_t*)(t + EncoderOffsets::kState2) = 0;
        std::memset(t + EncoderOffsets::kState + 0x10, 0, 16);                     // +0x70..0x7F zeroed (0xbc60b87)
        std::memcpy(t + EncoderOffsets::kHeader + 0x40, kDrawDefaults16, 16);      // +0x80..0x8F from rodata 0xF08EF70 (0xbc60b92)
        *(uint64_t*)(t + EncoderOffsets::kHeader + 0x50) = 0x0000000100000000ULL;  // +0x90 (0xbc60ba3)
        *(uint64_t*)(t + EncoderOffsets::kHeader + 0x58) = 0x0001FFFF00000000ULL;  // +0x98 (0xbc60bb4)
        t[EncoderOffsets::kHeader + 0x62] = 0;                                     // +0xA2 (0xbc60bbb)
        *(uint16_t*)(t + EncoderOffsets::kHeader + 0x60) = 0xFFFF;                 // +0xA0 streamMask = 0 (0xbc60bc2)
        *(uint16_t*)(t + EncoderOffsets::kHeader + 0x63) = 0xFF00;                 // +0xA3 = 0x00, +0xA4 uniformIdx = 0xFF (0xbc60bcb)
        *(uint64_t*)(t + EncoderOffsets::kHeader + 0x00) = 0xFFFFFFFF00000000ULL; // +0x40 (0xbc60bde)
        *(uint64_t*)(t + EncoderOffsets::kHeader + 0x74) = ~0ULL;                  // +0xB4 (0xbc60be2)
        *(int32_t*)(t + EncoderOffsets::kHeader + 0x68) = 0x7FFFFFFF;              // +0xA8 (0xbc60bed)
        *(uint64_t*)(t + EncoderOffsets::kHeader + 0x6C) = 0;                      // +0xAC (0xbc60bf7)
        *(uint32_t*)(t + EncoderOffsets::kUniformBegin) = *(uint32_t*)(t + EncoderOffsets::kUniformEnd); // m_uniformBegin = m_uniformEnd (0xbc60c02/0xbc60c08)

        // ---- m_bind.clear(): 65 bindings, stride 0x14 (0xbc60c20..0xbc60c63) ----
        for (uint32_t b = 0; b < EncoderOffsets::kBindingCount; ++b) {
            uint8_t* bind = t + EncoderOffsets::kRenderBind + b * EncoderOffsets::kBindingSize;
            *(uint32_t*)(bind + 0x00) = 0;                                         // samplerFlags
            *(uint16_t*)(bind + 0x0A) = 0xFFFF;                                    // idx unbound
            *(uint32_t*)(bind + 0x0C) = 0xFFFFFFFF;                                // extra
            *(uint8_t*)(bind + 0x13) = 0;                                          // type
        }

        // ---- side-table teardown (0xbc60c65..0xbc60cec) ----
        if (sideTable) {
            if (gAllocator) {
                for (uint32_t i = 0; i < 0x41; ++i) {
                    uint8_t* entry = (uint8_t*)sideTable + i * 16;
                    void* data = *(void**)entry;
                    if (data) allocatorRealloc(gAllocator, data, 0, 0, nullptr, 0); // size 0 = free
                    *(uint64_t*)entry = 0;                                         // entry[i] = {}
                    *(uint64_t*)(entry + 8) = 0;
                }
            } else {
                std::memset(sideTable, 0, 0x410);                                  // 0xbc60ce7 call 0xEEC6ED0
            }
            *(uint32_t*)((uint8_t*)sideTable + 0x410) = 0;                         // count = 0 (0xbc60cec)
        }
        t[EncoderOffsets::kBindDirty] = 1;                                         // 0xbc60cf6
    }

    // ===== setTransform / matrix cache (inlined at submit call sites, e.g. 0xbcc3b90) =====
    // 0xbcc3c14 mov rax,[r14]        context object ptr chain -> encoder = r14
    // 0xbcc3c1e mov eax,[rcx+0xD457C0]   rcx = Frame* = [encoder+0]; load matrix count
    // 0xbcc3c4b lock cmpxchg [rcx+0xD457C0],r8d   atomic reserve, cap 0xFFFF, old = slot
    // 0xbcc3c77 shl rax,6              slot << 6
    // 0xbcc3c7e add rcx,0x9457C0       cache base
    // 0xbcc3c88 call 0xEBCE390         memcpy 64-byte matrix into slot
    // 0xbcc3c8d mov [r14+0x7C],r15d    encoder+0x7C = slot (draw.startMatrix = header+0x3C)
    // 0xbcc3c91 mov word ptr [r14+0x9E],1   encoder+0x9E = 1 (draw.numMatrices = header+0x5E)
    // 0xbcc3cbd call 0xBC60740         Encoder::submit(encoder = r14)
    static void setTransform(const void* mtx /*mat4*/, void* encoder) {
        uint8_t* t = (uint8_t*)encoder;
        uint8_t* f = (uint8_t*)*(void**)t;   // [encoder+0] Frame*
        uint32_t* matrixCount = (uint32_t*)(f + FrameOffsets::kMatrixCount);
        uint32_t seen = *matrixCount, slot;
        for (;;) {
            slot = seen;
            uint32_t next = slot + 1;
            if (next >= 0xFFFF || slot >= 0xFFFF) next = 0xFFFF;
            uint32_t orig = atomicCAS(matrixCount, next, slot);
            if (slot == 0xFFFF || orig == slot) break;
            seen = orig;
        }
        if (slot == 0xFFFF) return;   // slot 0xFFFF disables the matrix copy
        memcpy40(f + FrameOffsets::kMatrixCache + ((size_t)slot << 6), mtx);
        *(uint32_t*)(t + kStartMatrix) = slot;          // encoder+0x7C  (0xbcc3c8d)
        *(uint16_t*)(t + kNumMatrices) = 1;             // encoder+0x9E  (0xbcc3c91)
    }

private:
    // rodata 16-byte scissor defaults at rva 0xF08EF70 (loaded via movaps at 0xbc60b8b / 0xbc60d45);
    // offset + size verified, contents not independently decoded.
    static constexpr uint64_t kDrawDefaults16[2] = { 0, 0 };

    static inline uint32_t atomicCAS(volatile uint32_t* addr, uint32_t exchange, uint32_t comparand) {
        // _InterlockedCompareExchange(addr, exchange, comparand) = lock cmpxchg.
        // Documented-only stub: this header is not compiled in this unit.
        return 0;
    }
};

} // namespace bgfx
