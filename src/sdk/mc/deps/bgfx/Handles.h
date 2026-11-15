#pragma once

namespace bgfx {

// Handle allocators inside bgfx::Context (1.26.62.01), the object at rva 0x12AE1748. Found by pairing the u16 loads at +X / +X+2 over the
// whole bgfx range (tools/sigs/bgfxalloc_dragon.py), checked live (counts/max/dense-sparse consistency, 0 bad entries on every one) and named
// by the Stats copy in Context::frame() 0xbc66de0 (0xbc6848d..0xbc68520), which stores each allocator's count into bgfx::Stats::num* in stock
// order (docs/progress/bgfx-d3d12-dragon.md, A8a). [V] unless marked.
//
// A static allocator is stock bgfx HandleAllocT<N>: { u16 numHandles; u16 maxHandles; u16 dense[N]; u16 sparse[N]; }. alloc() = dense[numHandles++].
struct HandleAllocHeader {
    uint16_t numHandles; // +0
    uint16_t maxHandles; // +2 (the allocator's capacity, N)
    // u16 dense[maxHandles] at +4, u16 sparse[maxHandles] at +4 + 2*maxHandles
};
static_assert(sizeof(HandleAllocHeader) == 4);

struct ContextHandleAlloc {
    uintptr_t offset; // header offset in bgfx::Context
    uint16_t capacity;
    uint16_t statsOffset; // offset in Context of the u16 copy that frame() writes (bgfx::Stats::num*)
};

struct HandleAllocators {
    //                                                                          offset      cap   Stats copy (Context+)
    static constexpr ContextHandleAlloc kDynamicIndexBuffers{0x1DDD308, 4096, 0x484}; // createDynamicIndexBuffer 0xbc6f910 (also takes an index buffer handle); live 5
    static constexpr ContextHandleAlloc kDynamicVertexBuffers{0x1DE1348, 4096, 0x486}; // createDynamicVertexBuffer 0xbc70240 (also takes a vertex buffer handle + layout); live 10
    static constexpr ContextHandleAlloc kFrameBuffers{0x1DFB48C, 128, 0x488};         // 0xbc74a80 / 0xbc750b0 (6ai called 0xbc74a80 createDynamicTexture: wrong, it is createFrameBuffer); live 1
    static constexpr ContextHandleAlloc kIndexBuffers{0x1DE534C, 4096, 0x48A};        // createIndexBuffer 0xbc6f0a0; live 9 = the 9 non-null IB records of the D3D12 table
    static constexpr ContextHandleAlloc kOcclusionQueries{0x1DFBE94, 256, 0x48C};     // only frame() and the destructor touch it in the bgfx range; live 0
    static constexpr ContextHandleAlloc kPrograms{0x1DF145C, 2048, 0x48E};            // createProgram 0xbc72c80 / destroy 0xbc73000; live 150 = 150 non-null program records
    static constexpr ContextHandleAlloc kShaders{0x1DED458, 4096, 0x490};             // createShader 0xbc71f60; live 118 = 118 non-null shader records (6ai had programs/shaders swapped)
    static constexpr ContextHandleAlloc kUniforms{0x1DFB690, 512, 0x494};             // createUniform 0xbc75440 (6ah); live 54
    static constexpr ContextHandleAlloc kVertexBuffers{0x1DE9454, 4096, 0x496};       // createVertexBuffer 0xbc6f4d0; live 14 = 14 non-null VB records
    static constexpr ContextHandleAlloc kVertexLayouts{0x1DE9350, 64, 0x498};         // createVertexLayout 0xbc76490; live 14
    // Not in Stats (Mojang additions), named by use:
    static constexpr ContextHandleAlloc kShaderBuffers{0x1DF7488, 4096, 0};           // createShaderBuffer-like 0xbc70ca0 (header initialised by the Context constructor, dword 0x10000000 = {0, 0x1000}); live 3 = 3 non-null D3D12 shader-buffer records [I name]
    static constexpr ContextHandleAlloc kAccelerationStructures{0x1DFC298, 32768, 0}; // 0xbc716a0 / 0xbc71990 (BLAS/TLAS variants) / destroy 0xbc71da0; CapsLimit::MaxAccelerationStructures = 32768; live 0 (no RTX) [I name]
};

// Every static allocator is followed by its own dense+sparse arrays and the next allocator starts right after (or after a free-queue block).
// These asserts pin the chain the offsets were found in; a drift of one of them means the Context layout moved.
constexpr uintptr_t allocEnd(const ContextHandleAlloc& a) { return a.offset + 4 + 4u * a.capacity; }
static_assert(allocEnd(HandleAllocators::kIndexBuffers) == HandleAllocators::kVertexLayouts.offset);
static_assert(allocEnd(HandleAllocators::kVertexLayouts) == HandleAllocators::kVertexBuffers.offset);
static_assert(allocEnd(HandleAllocators::kVertexBuffers) == HandleAllocators::kShaders.offset);
static_assert(allocEnd(HandleAllocators::kShaders) == HandleAllocators::kPrograms.offset);
static_assert(allocEnd(HandleAllocators::kDynamicVertexBuffers) == HandleAllocators::kIndexBuffers.offset);
static_assert(allocEnd(HandleAllocators::kShaderBuffers) == HandleAllocators::kFrameBuffers.offset);
static_assert(allocEnd(HandleAllocators::kFrameBuffers) == HandleAllocators::kUniforms.offset);
static_assert(allocEnd(HandleAllocators::kUniforms) == HandleAllocators::kOcclusionQueries.offset);
static_assert(allocEnd(HandleAllocators::kOcclusionQueries) == HandleAllocators::kAccelerationStructures.offset);
static_assert(HandleAllocators::kDynamicIndexBuffers.offset + 4 + 4 * 4096 + 0x3C == HandleAllocators::kDynamicVertexBuffers.offset); // 0x3C-byte free-queue block (+0x1DDD2D0.. and +0x1DE1310.. vectors) lies around it
static_assert(HandleAllocators::kPrograms.statsOffset == HandleAllocators::kFrameBuffers.statsOffset + 6);

// bgfx::Stats copy inside the Context: frame() copies the 0xD8-byte stats block of the consumed Frame (Frame+0xE60DE8) to Context+0x410 and then
// overwrites the u16 num* fields with the allocator counts above (0xbc6848d..0xbc68520). Stock Stats order, 2 bytes each.
struct ContextStats {
    static constexpr uintptr_t kBase = 0x410;
    static constexpr size_t kSize = 0xD8;
    static constexpr uintptr_t kFrameSourceOffset = 0xE60DE8; // in the Frame
    static constexpr uintptr_t kNumDynamicIndexBuffers = 0x484; // Context-relative; first of 11 consecutive u16
    static constexpr uintptr_t kNumVertexLayouts = 0x498;
};
static_assert(ContextStats::kNumDynamicIndexBuffers >= ContextStats::kBase && ContextStats::kNumVertexLayouts + 2 <= ContextStats::kBase + ContextStats::kSize);
static_assert(ContextStats::kNumVertexLayouts == ContextStats::kNumDynamicIndexBuffers + 10 * 2 + 2 - 2);

// The dynamic (growable) allocator behind texture handles (bgfx caps flag DynamicTextureHandles, bit 36 = byte 0x12ADFA54 & 0x10). Object at
// Context+0x1DF3460 (right after the 2048-entry program allocator), allocated by 0xbc79a60 (the only allocator call in createTexture 0xbc73770
// and the second texture create 0xbc74590). It is a paged HandleAllocT whose dense and sparse arrays are interleaved in 4-byte entries.
struct DynamicHandleAlloc {
    static constexpr uintptr_t kObject = 0x1DF3460;
    static constexpr size_t kInlineEntries = 0x1000;       // first page: entries 0..0xFFF live inline at +0 .. +0x3FFF
    static constexpr size_t kPageBytes = 0x4000;           // later pages are chained: page k+1 pointer at page_k + 0x4000 (read by walking +0x4000)
    static constexpr uintptr_t kPageList = 0x4000;         // ptr to a 0x18-byte header {first page*, +8 last page*, +0x10 total paged bytes} (null while <= 0x1000 entries)
    static constexpr uintptr_t kSizeBytes = 0x4008;        // u64 entries * 4 currently stored (live 8336 = 2084 entries)
    static constexpr uintptr_t kCapacityBytes = 0x4010;    // u64
    static constexpr uintptr_t kNumHandles = 0x4018;       // u16 handles currently allocated = bgfx::Stats::numTextures source (Context+0x1DF7478)
    // Entry i = { u16 sparse (lo): index of handle i in the dense order; u16 dense (hi): handle at position i }. New entries are appended as
    // {i, i} (identity, live entries 0..13 untouched). alloc(): idx = numHandles++; handle = entry[idx].dense; entry[handle].sparse = idx.
    static constexpr uintptr_t kAllocFn = 0xBC79A60;       // returns the handle in ax
};
static_assert(DynamicHandleAlloc::kObject + DynamicHandleAlloc::kNumHandles == 0x1DF7478);
static_assert(DynamicHandleAlloc::kObject + DynamicHandleAlloc::kPageBytes == DynamicHandleAlloc::kObject + 0x4000);

struct ContextTextureState {
    static constexpr uintptr_t kStaticLimitFlag = 0x1DF7480; // u8: 1 = handle count limited to 0x1000 (createTexture returns 0xFFFF past it); set to 1 by the Context constructor, cleared by frame() when the reset flag 0x400000 turns on
    static constexpr uintptr_t kRecordPagedFlag = 0x1E7DAD0;  // u8, same lifecycle: 1 = texture record vector is not paged
    static constexpr uintptr_t kReqDynamicFlag = 0x1EBF2F3;   // u8, constructor sets 1; frame() clears it with the other two
    static constexpr uintptr_t kRecords = 0x1E55AB8;          // texture TextureRef records, stride 0x28 (handle * 40), pages of 0x1000 records (0x28000 bytes) chained at page + 0x28000
    static constexpr size_t kRecordStride = 0x28;
    static constexpr size_t kRecordPage = 0x1000 * kRecordStride;
    static constexpr uintptr_t kResetFlags = 0x1EBF19C;       // u32 API-side reset flags; frame() compares bit 0x400000 with the consumed Frame's (Frame+0xDC5810)
    static constexpr uint32_t kResetDynamicHandles = 0x400000;
    static constexpr uintptr_t kCapsFlagAddr = 0x12ADFA54;    // game .data: byte & 0x10 = CapsFlag::DynamicTextureHandles
};
static_assert(ContextTextureState::kRecordPage == 0x28000);

} // namespace bgfx
