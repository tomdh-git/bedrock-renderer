#pragma once

namespace bgfx {

// Offsets inside the frame buffer the game thread fills and the render thread's submit() consumes (docs/BGFX_MAP.md 6e). Two buffers alternate, 0xE749C0 bytes apart, each starts
// with the identity table of view ids. [V] = confirmed in a live dump, [I] = inferred from submit's code.
struct FrameOffsets {
    static constexpr size_t kFrameSize = 0xE749C0;          // [V] distance between the two frame buffers
    static constexpr uintptr_t kViewRemap = 0x0;            // [V] uint16_t[256], identity
    static constexpr uintptr_t kViewStructs = 0x200;        // [V static 6q/6ek] 256 per-view structs, stride 0x140 (memcpy of ctx+0x1eab080, 0x14000 bytes); per struct: rect +0x10, view mtx +0x20, proj +0x60, prev pair +0xA0/+0xE0, sort mode +0x132 (ViewRecord in bgfx/View.h is the same layout based 0x10 later; resolved 6hs). Was wrongly listed as 4x4 matrices of stride 0x40
    static constexpr size_t kViewStructStride = 0x140;
    // From the fully reversed Frame::sort (docs/functions/bc61e20.md) and Encoder::submit; all asserted by tools/sigs/layoutcheck.py.
    static constexpr uintptr_t kOcclusion = 0x14300;        // [V] int32_t m_occlusion[256]: occlusion query results by query handle (executor 0xe82270b), ends where kSortKeys starts
    static constexpr uintptr_t kSortKeys = 0x14700;        // [V] uint64_t[65535]; view field = bits 54..61, remapped by Frame::sort
    static constexpr uintptr_t kBlitKeys = 0x934778;        // [V] uint32_t[]; view in the top byte
    static constexpr uintptr_t kRenderDraws = 0x8B4700;     // [V] RenderDraw array object, records of kRenderDrawStride
    static constexpr size_t kRenderDrawStride = 0x540;      // [V] bind block 0x514 + u32 bind hash at +0x514
    static constexpr uintptr_t kSideTables = 0x8B4778;      // [V] SideTable* per render item (0x41 x {Binding* data, u64 count} + u32 used at +0x410): ranged binds, docs/functions/bc60f10.md
    static constexpr uintptr_t kFrameParamsA = 0xE746DC;    // [V] 0x1E8-byte frame-global parameter block, written by the compute form 0xbc618e0 (submit_variants.md)
    static constexpr uintptr_t kFrameParamsB = 0xE748C8;    // [V] 0x38 bytes + shared_ptr {ptr +0x38, ctrl +0x40}, same writer
    static constexpr uintptr_t kItemCount = 0xDC57E8;      // [V] u32 m_numRenderItems (atomic draw slot counter, cap 0xFFFE)
    static constexpr uintptr_t kBlitCount = 0xDC57EC;       // [V] u16 m_numBlitItems
    static constexpr uintptr_t kSortedItems = 0x94700;      // [V] uint16_t[65536] draw order (render item index per sorted slot), executor 0xe822673; ascending ids in a live dump
    static constexpr uintptr_t kDrawHeaders = 0xB4700;      // [V] RenderDrawHeader[], stride 0x80; header = base + (index << 7) (executor 0xe82269e; 0xB4700 = 0x94700 + 0x20000). Earlier value 0xB4000 was wrong by 0x700
    static constexpr uintptr_t kMatrixCache = 0x9457C0;     // [V] mat4[65535], stride 0x40: m_matrixCache.m_cache (inlined setTransform in 0xbcc3b90, 6hr)
    static constexpr uintptr_t kMatrixCount = 0xD457C0;     // [V] u32 m_matrixCache.m_num (atomic slot counter, cap 0xFFFF; RenderDraw startMatrix = slot)
    static_assert(kMatrixCache + 0x10000 * 0x40 == kMatrixCount);   // the cache array ends exactly at its counter
    static constexpr uintptr_t kScissorRects = 0xD457D0;    // [V] {u16 x,y,w,h}[] indexed by header +0x60 (0xFFFF = none), executor 0xe822758
    static constexpr uintptr_t kTransientIbSize = 0xDC57F0; // [I] u32
    static constexpr uintptr_t kTransientVbSize = 0xDC57F4; // [I] u32
    static constexpr uintptr_t kTransientIb = 0xDC57F8;     // [I] TransientIndexBuffer* (u16 handle at +0x10)
    static constexpr uintptr_t kTransientVb = 0xDC5800;     // [I] TransientVertexBuffer* (u16 handle at +0x12)
    static constexpr uintptr_t kBackbufferSize = 0xDC5808;  // [V] u32 width, u32 height
    static constexpr uintptr_t kResetFlags = 0xDC5810;      // [I] u32
    static constexpr uintptr_t kFrameCounter = 0xE746D8;    // [V] u32, +1 per frame
    static constexpr uintptr_t kCmdPrePos = 0xDC5818;       // [I static 6eq] u32 write position of the pre-command buffer (bgfx CommandBuffer m_cmdPre); data at kCmdPreData
    static constexpr uintptr_t kCmdPreData = 0xDC5820;      // [I static 6eq] pre-command bytes (resource create commands); command enum numbering unverified
    static constexpr uintptr_t kCmdPostPos = 0xE05820;      // [I static 6eq] u32 write position of the post-command buffer (m_cmdPost, destroy commands)
    static constexpr uintptr_t kCmdPostData = 0xE05828;     // [I static 6eq] post-command bytes
};

// The 0x80-byte draw header (bgfx RenderDraw in Mojang's layout). Fields read by the D3D12 draw executor (0xe821120, record builder ending at 0xE82CB90); the rest is not decoded.
struct RenderDrawHeader {
    static constexpr size_t kSize = 0x80;
    static constexpr uintptr_t kState = 0x20;            // [V] u64 render state; bit 62 tested by the executor (0xe8226bf)
    static constexpr uintptr_t kState2 = 0x28;           // [V] u64 (second state word: stencil/flags), copied to local+0x4e8
    static constexpr uintptr_t kScissor = 0x60;          // [V] u16 scissor rect index, 0xFFFF = none (clipped against the view rect, empty => draw skipped)
    static constexpr uintptr_t kByte62 = 0x62;           // [V] u8 m_submitFlags; its sign bit (0x80) = "draw when the occlusion query says invisible" (BGFX_MAP 6fi)
    static constexpr uintptr_t kHandle7A = 0x7A;         // [V] u16 m_occlusionQuery, 0xFFFF = none; indexes FrameOffsets::kOcclusion. A draw is skipped when (flags sign bit) == (result != 0) is false
    static constexpr uintptr_t kUniformBegin = 0x34;     // [V] u32 (Encoder::submit)
    static constexpr uintptr_t kUniformEnd = 0x38;       // [V] u32
    static constexpr uintptr_t kStreamMask = 0x63;       // [V] u8
    static constexpr uintptr_t kUniformIdx = 0x64;       // [V] u8 index into the Frame's UniformBuffer* table
    static constexpr uintptr_t kStartIndex = 0x40;       // [I] u32
    static constexpr uintptr_t kNumIndices = 0x44;       // [V] u32, 0xFFFFFFFF = computed from the buffer (size / index stride)
    static constexpr uintptr_t kIndexStride = 0x48;      // [V] u32 2 or 4 (DXGI_FORMAT_R16_UINT 0x39 / R32_UINT 0x2A)
    static constexpr uintptr_t kNumVertices = 0x4C;      // [I] u32
    // The next four describe the INSTANCE DATA buffer view, not the mesh vertex buffer (executor 0xe822ba1: copied together with the
    // stream mask, exactly as stock bgfx copies m_instanceData*). The mesh vertex buffers are the streams at +0x00, see RenderDraw below.
    static constexpr uintptr_t kVertexByteOffset = 0x50; // [V] u32 m_instanceDataOffset
    static constexpr uintptr_t kVertexCount = 0x54;      // [V] u32 m_numInstances
    static constexpr uintptr_t kVertexStride = 0x58;     // [V] u16 m_instanceDataStride
    static constexpr uintptr_t kIndexBuffer = 0x74;      // [V] u16 handle (0xFFFF = non-indexed), executor 0xe82c5b8 / 0xe82c8ac. Was 0x5A, which is m_startIndirect (BGFX_MAP 6fl)
    static constexpr uintptr_t kStartIndirect = 0x5A;    // [V] u16, multiplied by 32 (indirect record stride)
    static constexpr uintptr_t kNumIndirect = 0x5C;      // [V] u16, 0xFFFF = whole indirect buffer (size / 32)
    static constexpr uintptr_t kIndirectBuffer = 0x78;   // [V] u16 handle into the vertex buffer table, 0xFFFF = a normal (batched) draw
    static constexpr uintptr_t kVertexBuffer = 0x76;     // [V] u16 m_instanceDataBuffer handle (0xFFFF = none)
    static constexpr uintptr_t kMarkByte = 0x1F;         // used by RenderMarkHook (unused byte in every sample)
};

// The same 0x80 bytes as a struct, from the fully reversed Encoder::submit and the executor's draw path (docs/functions/bc60740.md,
// e821120.md). Unnamed gaps are bytes no reversed code has given a meaning yet. Every named field is pinned by a static_assert.
#pragma pack(push, 1)
struct RenderStream {
    uint32_t startVertex;  // +0x00
    uint16_t handle;       // +0x04 vertex buffer handle
    uint16_t layoutHandle; // +0x06
};
struct RenderDraw {
    RenderStream stream[4];      // +0x00 used entries are the bits of streamMask
    uint64_t stateFlags;         // +0x20 bit 62 = this draw is an occlusion query; bits 48..50 = primitive type
    uint64_t stencil;            // +0x28
    uint32_t rgba;               // +0x30 blend factor; only compared when the state's blend uses a constant factor
    uint32_t uniformBegin;       // +0x34
    uint32_t uniformEnd;         // +0x38
    uint32_t startMatrix;        // +0x3C
    uint32_t startIndex;         // +0x40
    uint32_t numIndices;         // +0x44 0xFFFFFFFF = whole buffer
    uint32_t indexStride;        // +0x48 2 or 4
    uint32_t numVertices;        // +0x4C minimum over the bound streams
    uint32_t instanceDataOffset; // +0x50
    uint32_t numInstances;       // +0x54
    uint16_t instanceDataStride; // +0x58
    uint16_t startIndirect;      // +0x5A first indirect record (x 32 bytes)
    uint16_t numIndirect;        // +0x5C 0xFFFF = whole indirect buffer
    uint16_t numMatrices;        // +0x5E
    uint16_t scissor;            // +0x60 index into the Frame rect cache, 0xFFFF = none
    uint8_t submitFlags;         // +0x62 sign bit inverts the occlusion visibility test
    uint8_t streamMask;          // +0x63
    uint8_t uniformIdx;          // +0x64 which UniformBuffer of the Frame
    uint8_t _65[3];              // +0x65 padding: no reader in the executor, draw flush, Encoder::submit, Frame::sort or PSO builder (6ht)
    int32_t depthBias;           // +0x68 D3D12 rasterizer DepthBias (Mojang addition; part of the PSO key)
    float slopeScaledDepthBias;  // +0x6C RasterizerState.SlopeScaledDepthBias
    float depthBiasClamp;        // +0x70 RasterizerState.DepthBiasClamp
    uint16_t indexBuffer;        // +0x74 0xFFFF = non-indexed
    uint16_t instanceDataBuffer; // +0x76 0xFFFF = none
    uint16_t indirectBuffer;     // +0x78 0xFFFF = a normal draw; else ExecuteIndirect from this vertex-buffer-table entry
    uint16_t occlusionQuery;     // +0x7A 0xFFFF = none
    uint8_t _7C[4];              // +0x7C padding to 0x80: no reader in the same five functions (6ht)
};
#pragma pack(pop)
static_assert(sizeof(RenderStream) == 8);
static_assert(sizeof(RenderDraw) == RenderDrawHeader::kSize);
static_assert(offsetof(RenderDraw, stateFlags) == RenderDrawHeader::kState);
static_assert(offsetof(RenderDraw, stencil) == RenderDrawHeader::kState2);
static_assert(offsetof(RenderDraw, rgba) == 0x30);
static_assert(offsetof(RenderDraw, depthBias) == 0x68);
static_assert(offsetof(RenderDraw, slopeScaledDepthBias) == 0x6C);
static_assert(offsetof(RenderDraw, depthBiasClamp) == 0x70);
static_assert(offsetof(RenderDraw, uniformBegin) == RenderDrawHeader::kUniformBegin);
static_assert(offsetof(RenderDraw, uniformEnd) == RenderDrawHeader::kUniformEnd);
static_assert(offsetof(RenderDraw, startMatrix) == 0x3C);
static_assert(offsetof(RenderDraw, startIndex) == RenderDrawHeader::kStartIndex);
static_assert(offsetof(RenderDraw, numIndices) == RenderDrawHeader::kNumIndices);
static_assert(offsetof(RenderDraw, indexStride) == RenderDrawHeader::kIndexStride);
static_assert(offsetof(RenderDraw, numVertices) == RenderDrawHeader::kNumVertices);
static_assert(offsetof(RenderDraw, instanceDataOffset) == RenderDrawHeader::kVertexByteOffset);
static_assert(offsetof(RenderDraw, numInstances) == RenderDrawHeader::kVertexCount);
static_assert(offsetof(RenderDraw, instanceDataStride) == RenderDrawHeader::kVertexStride);
static_assert(offsetof(RenderDraw, indexBuffer) == RenderDrawHeader::kIndexBuffer);
static_assert(offsetof(RenderDraw, startIndirect) == RenderDrawHeader::kStartIndirect);
static_assert(offsetof(RenderDraw, numIndirect) == RenderDrawHeader::kNumIndirect);
static_assert(offsetof(RenderDraw, indirectBuffer) == RenderDrawHeader::kIndirectBuffer);
static_assert(offsetof(RenderDraw, numMatrices) == 0x5E);
static_assert(offsetof(RenderDraw, scissor) == RenderDrawHeader::kScissor);
static_assert(offsetof(RenderDraw, submitFlags) == RenderDrawHeader::kByte62);
static_assert(offsetof(RenderDraw, streamMask) == RenderDrawHeader::kStreamMask);
static_assert(offsetof(RenderDraw, uniformIdx) == RenderDrawHeader::kUniformIdx);
static_assert(offsetof(RenderDraw, instanceDataBuffer) == RenderDrawHeader::kVertexBuffer);
static_assert(offsetof(RenderDraw, occlusionQuery) == RenderDrawHeader::kHandle7A);

// The other occupant of the same slot (compute items; docs/functions/submit_variants.md).
#pragma pack(push, 1)
struct RenderCompute {
    uint32_t uniformBegin;   // +0x00
    uint32_t uniformEnd;     // +0x04
    uint32_t startMatrix;    // +0x08
    uint16_t indirectBuffer; // +0x0C 0xFFFF = none
    uint8_t _0E[2];          // +0x0E
    uint32_t numX;           // +0x10
    uint32_t numY;           // +0x14
    uint32_t numZ;           // +0x18
    uint32_t _1C;            // +0x1C
    uint16_t numMatrices;    // +0x20
    uint8_t uniformIdx;      // +0x22
    uint8_t subtype;         // +0x23 0 = plain dispatch, 1 = frame-params (ray tracing) item
};
#pragma pack(pop)
static_assert(sizeof(RenderCompute) == 0x24);
static_assert(offsetof(RenderCompute, subtype) == 0x23);

} // namespace bgfx
