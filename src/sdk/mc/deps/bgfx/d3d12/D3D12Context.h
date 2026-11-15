#pragma once
// RendererContextD3D12 (the live object is the "Direct3D 12 RTX" subclass) as of 1.26.62.01: offsets and RVAs found by static analysis (docs/BGFX_MAP.md 6f, 6z, 6am-6az, 6cp, 6dq).
// Constants only; nothing here is compiled against the game. [V] = verified on the live game or by several readers, [I] = inferred from code shape.
// Not to be confused with bgfx::Context (the encoder/frame side, bgfx/BgfxContext.h): the D3D12 object is the global at rva 0x12BB4910, bgfx::Context is at 0x12AE1748.

namespace bgfx::d3d12 {

struct D3D12Rvas {
    static constexpr uintptr_t kRendererGlobal = 0x12BB4910; // [V] holds the RendererContextD3D12*
    static constexpr uintptr_t kBaseVtable = 0xF4ED2D0;      // [V]
    static constexpr uintptr_t kRtxVtable = 0xF4EEE80;       // [V] the live object's vtable
    static constexpr uintptr_t kSubmit = 0xE82E230;          // [V] slot 50, base class; RTX override 0xE83D440
    static constexpr uintptr_t kDrawExecutorWrapper = 0xE83C390; // [I]
    static constexpr uintptr_t kDrawExecutor = 0xE821120;    // [V] item loop; matrix cache 6dq
    static constexpr uintptr_t kPsoBuilder = 0xE81E860;      // [V] key mask 0x0707007FFFFFF0FF
    static constexpr uintptr_t kResetHandler = 0xE81A610;    // [V] slot 60 (RTX 0xE83EC70)
    static constexpr uintptr_t kDeviceLostHandler = 0xE8102B0; // [I] slot 7: TDR/device-lost with DRED report
    static constexpr uintptr_t kInit = 0xE807FF0;            // [V] slot 58 ("d3d12.dll")
    // Slots 42-45 (M1c, 1.26.62.01). [V RVA/slots] Semantics partially reversed; see docs/functions/0xe817cf0.md..0xe8189c0.md.
    static constexpr uintptr_t kSlot42 = 0xE817CF0;          // [V] cmd byte 21: per-context uniform/value alloc+store + handle-map tail helper
    static constexpr uintptr_t kSlot43 = 0xE817E50;          // [V] cmd byte 37: release/clear per-context value ptrs and remove handle from 0x400-entry map
    static constexpr uintptr_t kSlot44 = 0xE818050;          // [V] cmd byte 40: screenshot/readback-style path ("LScreenshot")
    static constexpr uintptr_t kSlot45 = 0xE8189C0;          // [V] cmd byte 22 and routed with byte 19: set per-index name at this + index*0x100 + 0x7EDE
    // Slots 39-41 (M1c, 1.26.62.01). [V RVA/slots] Framebuffer/window-record ops on D3D12Tables::kFrameBuffers (stride 0x68).
    static constexpr uintptr_t kCreateWindowFrameBuffer = 0xE817880;   // [V] slot 39: create window-backed FB/swapchain into record
    static constexpr uintptr_t kSetFrameBufferAttachments = 0xE8176A0; // [V] slot 40: copy attachments, derive via 0xe819b50 (internal)
    static constexpr uintptr_t kDestroyFrameBuffer = 0xE817C00;        // [V] slot 41: release swapchain, clear record, remove from window list
};

// Offsets inside the RendererContextD3D12 object.
struct D3D12Offsets {
    static constexpr size_t kDeviceQueueFactory = 0x19F08; // .. +0x19F50: device / queue / factory COM pointers [I]
    static constexpr size_t kResourceTables = 0x19F58;     // pointer to the guarded paged resource tables [V]
    static constexpr size_t kCaps = 0x19F60;               // caps / shader-format info (also per-job command list array start in the executor, 6cp) [I]
    static constexpr size_t kCapsAux = 0x19F68;            // [I]
    static constexpr size_t kSwapchainState = 0x19F80;     // .. +0x19F94 swapchain / resolution state [I]
    static constexpr size_t kRendererState = 0x19F88;      // int, < 5 = submit skips [I]
    static constexpr size_t kCommandQueue = 0xCC9268;      // [V] OffsetProvider bgfx_RendererContextD3D12_mCommandQueue
    static constexpr size_t kGuardByte = 0xC96190;         // paged-array guard toggle (slot 49) [V]
};

// Resource tables (relative to the D3D12 object): base offset and record stride. Four thousand ninety-six records inline, then chained pages; handle >> 12 selects the page.
struct D3D12Tables {
    static constexpr size_t kTextures = 0xBDE178;       // stride 0xB8 [V]
    static constexpr size_t kTexturesStride = 0xB8;
    // Corrected in BGFX_MAP 6fc from the destroy virtuals (slot 11 destroyIndexBuffer, 15 destroyVertexBuffer, 23 destroyShader, 38 on the
    // framebuffer table): the earlier header had index/vertex swapped and the framebuffer stride as 0x130. Each table is 4096 records
    // (table sizes divide exactly: 0x78000/0x78, 0x80000/0x80, 0x78000/0x78, 0xB8000/0xB8, 0x7C000/0xF8 = 512 programs, 0xB8000/0xB8).
    // Acceleration structures (Mojang's ray-tracing additions): 32768 records (= CapsLimit::MaxAccelerationStructures = the bgfx::Context
    // allocator at 0x1DFC298) of the BufferRecord layout (SRV desc at +8 with ViewDimension 0xB, GPU address at +0x18), ending exactly where
    // the index buffer table starts. Read by binding type 5 of the descriptor build (0xe82735a: `imul rax, rdi, 0x78; lea r8,[r9+rax+0x57a180]`). [V static]
    static constexpr size_t kAccelerationStructures = 0x57A178;
    static constexpr size_t kAccelerationStructuresStride = 0x78;
    static constexpr size_t kAccelerationStructuresCount = 32768;
    static constexpr size_t kIndexBuffers = 0x93A178;   // stride 0x78 [V static: slot 11/18 body]
    static constexpr size_t kIndexBuffersStride = 0x78;
    static constexpr size_t kVertexBuffers = 0x9B2178;  // stride 0x80 [V static: slot 15/21 body + exact table size]
    static constexpr size_t kVertexBuffersStride = 0x80;
    // Was named kFrameBuffers (6fc). The descriptor build binds these records as shader resources / UAVs with buffer-style state tracking
    // (binding types 4 and 8, BGFX_MAP 6fq), and command byte 19 creates them from a data blob, so they are Mojang's shader buffers, not
    // framebuffers. [V use, I name] Slots 36/37 create, 38 destroys.
    static constexpr size_t kShaderBuffers = 0xA32178;  // stride 0x78
    static constexpr size_t kShaderBuffersStride = 0x78;
    // The texture array ends at 0xC96178 (0xBDE178 + 4096 * 0xB8). Right after it: the pointer to the chained overflow pages for texture
    // handles >= 4096 (+0x00) and the "dynamic texture handles" guard byte (+0x18 = 0xC96190). Vertex layouts start at 0xC96198
    // (PSO builder hashes record+0 = m_hash; setVertexBuffers reads the stride at record+4). Fixed in BGFX_MAP 6fr: was 0xC96178 / +0x24.
    static constexpr size_t kTextureOverflowPages = 0xC96178; // ptr to pages of 4096 texture records each, chained at page+0xB8000
    static constexpr size_t kDynamicTextureGuard = 0xC96190;  // u8, non-zero = handles >= 4096 are allowed
    static constexpr size_t kVertexLayouts = 0xC96198;  // stride 0x54 [V static]
    static constexpr size_t kVertexLayoutsStride = 0x54;
    static constexpr size_t kShaders = 0xAAA178;        // stride 0xB8 [V static: slot 23 destroyShader]
    static constexpr size_t kShadersStride = 0xB8;
    static constexpr size_t kPrograms = 0xB62178;       // stride 0xF8, variant key at +0xA8 [V]
    static constexpr size_t kProgramsStride = 0xF8;
    // Framebuffers (was kUniforms): the PSO builder indexes this table with the current framebuffer handle and reads, per record,
    // u16 color texture handles at +0x00, the u16 depth texture handle at +0x10, a window/swap-chain pointer at +0x18 and the u8 color
    // attachment count at +0x32 (BGFX_MAP 6fr). [V use]
    // Note (M1c slots 42-45, 1.26.62.01): slot 42/43 operate on per-context uniform/value pointers (context + handle*8 + 0x1250) and a
    // 0x400-entry handle hash map at +0xC9AA9C/+0xC9AAA0/+0xC9BAA0; slot 44 is a screenshot path; slot 45 writes names at this + index*0x100 + 0x7EDE.
    // None of 42-45 contain a direct 0xC97698 displacement in analyzed bodies, despite task-level association; see docs/functions/0xe817cf0.md..0xe8189c0.md. [V/I audit]
    static constexpr size_t kFrameBuffers = 0xC97698;   // stride 0x68
    static constexpr size_t kFrameBuffersStride = 0x68;
    static constexpr size_t kFrameBufferRecords = 128;  // [I] 128 * 0x68 = 0x3400; task claim, not independently proven from 42-45 bodies in this pass
};
static_assert(D3D12Tables::kTextures + 4096 * D3D12Tables::kTexturesStride == D3D12Tables::kTextureOverflowPages);
static_assert(D3D12Tables::kAccelerationStructures + D3D12Tables::kAccelerationStructuresCount * D3D12Tables::kAccelerationStructuresStride == D3D12Tables::kIndexBuffers);
// 64 layouts (stock BGFX_CONFIG_MAX_VERTEX_LAYOUTS) fill the gap to the framebuffer table exactly: 0xC97698 - 0xC96198 = 64 * 0x54.
static_assert(D3D12Tables::kVertexLayouts + 64 * D3D12Tables::kVertexLayoutsStride == D3D12Tables::kFrameBuffers);

struct FrameBufferRecord { // table D3D12Tables::kFrameBuffers, stride 0x68
    static constexpr size_t kColor = 0x00;     // u16[8] texture handles
    static constexpr size_t kDepth = 0x10;     // u16 texture handle, 0xFFFF = none
    static constexpr size_t kWindow = 0x18;    // non-null = a window / swap-chain framebuffer
    static constexpr size_t kNumColor = 0x32;  // u8
};
// Fields set by the framebuffer creates (slot 39 window 0xe817880, slot 40 attachments 0xe8176a0) and destroy (slot 41 0xe817c00; 6hx/6hy).
struct FrameBufferRecordLayout {
    uint16_t mColor[8];        // +0x00 texture handles
    uint16_t mDepth;           // +0x10 0xFFFF = none
    uint8_t mPad12[6];
    void* mSwapChain;          // +0x18 IDXGISwapChain* of a window framebuffer (Release()d when the window is reused)
    void* mWindow;             // +0x20 native window handle
    uint8_t mPad28[8];
    uint16_t mWindowIndex;     // +0x30 index in the context's window list (ctx+0x2F8 count, u16 list +0x2FA), 0xFFFF = not a window
    uint8_t mNumColor;         // +0x32 1 for a window framebuffer
    uint8_t mNumAttachments;   // +0x33 createFrameBuffer(handle, num, attachments) (slot 40, 0xe8176a0); 0 for a window framebuffer
    uint16_t mAttachments[8][3]; // +0x34 the caller's 6-byte attachment records copied verbatim; word 0 = texture handle (0xFFFF skipped)
    uint8_t mDirty;            // +0x64 1 = dirty; the extra-window loop over the u16 list at ctx+0x2FC acts on records with this set (BGFX_MAP "Extra windows")
    uint8_t mPad65[3];
};
static_assert(sizeof(FrameBufferRecordLayout) == D3D12Tables::kFrameBuffersStride);
static_assert(offsetof(FrameBufferRecordLayout, mDepth) == FrameBufferRecord::kDepth);
static_assert(offsetof(FrameBufferRecordLayout, mSwapChain) == FrameBufferRecord::kWindow);
static_assert(offsetof(FrameBufferRecordLayout, mNumColor) == FrameBufferRecord::kNumColor);
static_assert(offsetof(FrameBufferRecordLayout, mDirty) == 0x64);
static_assert(D3D12Tables::kFrameBufferRecords * D3D12Tables::kFrameBuffersStride == 0x3400);

// Handle allocator/hash map used by slots 42/43 (and tail helper 0xe804590) for uniform/value handles. [V from 0xe817e50/0xe817cf0]
// 1024-entry open-addressing table: count at +0xC9AA9C, u32 keys/state at +0xC9AAA0, u16 handles/slots at +0xC9BAA0.
struct UniformHandleMapOffsets {
    static constexpr size_t kBase = 0xC9AA98;       // passed to 0xe804590 as (this + kBase)
    static constexpr size_t kCount = 0xC9AA9C;      // u32 active entries
    static constexpr size_t kKeys = 0xC9AAA0;       // u32[1024]
    static constexpr size_t kHandles = 0xC9BAA0;    // u16[1024], 0xFFFF = empty
    static constexpr size_t kCapacity = 0x400;
};
static_assert(UniformHandleMapOffsets::kCount == UniformHandleMapOffsets::kBase + 0x4);
static_assert(UniformHandleMapOffsets::kKeys == UniformHandleMapOffsets::kBase + 0x8);
static_assert(UniformHandleMapOffsets::kHandles == UniformHandleMapOffsets::kKeys + UniformHandleMapOffsets::kCapacity * sizeof(uint32_t));

// Per-index name storage written by slot 45 (0xe8189c0): destination = this + index*0x100 + 0x7EDE, max copy 0xFA. [V]
struct NamedIndexOffsets {
    static constexpr size_t kNameBase = 0x7EDE;
    static constexpr size_t kNameStride = 0x100;
    static constexpr size_t kNameMax = 0xFA;
};

// The vertex layout record is bgfx::VertexLayout copied verbatim: createVertexLayout (slot 12, 0xe812bb0) is a 0x54-byte memcpy into
// ctx + kVertexLayouts + handle * 0x54 (6hx). See VertexLayoutRecord below for the field offsets.

// createTexture (slot 26, 0xe8143c0, 0x2e1 bytes), instruction-complete reading (docs/progress/bgfx-d3d12-dragon.md B7a): [V static]
//   void* createTexture(RendererContextD3D12* this, u16 handle, const bgfx::Memory* mem /*{data*, u32 size}*/, u32 flags, u8 skip /*stack [rsp+0x20+...]*/)
//   record  = this + kTextures + handle * 0xB8; handle >= 0x1000 walks the chained pages at this+kTextureOverflowPages (page + 0xB8000 -> next); the
//             paged-array bounds helper 0xe83abb0 is called first (growth), and a handle >= 0x1000 with the dynamic guard byte set logs through 0xbc5f110
//   name    = 0xe8066c0(&string, &handle) (debug name); header = bimg parse 0xebd2160(&container, mem->data, mem->size, 0); on failure result = {null, 0}
//   result  = TextureD3D12::create 0xe81bf30(record, &out{ptr +0, u32 state +8}, name, &container, flags, skip) ; returns out.ptr
//   tracker = [this + kStateTracker]: per-handle state entry via 0xe83aed0(tracker + kTrackerMap, handle) = {u64 state (lo = hi = out.state), u8 valid at +8};
//             missing entry -> 0xe83b0e0(tracker + kTrackerBase, handle, state); handle 0xFFFF skips the tracker
//   then    0xe82d960(cmdListWrapper + kCmdTrackerOffset, cmdListWrapper->+0x30, handle, state) = the state transition helper (B7b)
struct CreateTexture {
    static constexpr uintptr_t kFn = 0xE8143C0;
    static constexpr uintptr_t kTextureCreate = 0xE81BF30;
    static constexpr uintptr_t kPagedBoundsHelper = 0xE83ABB0;
    static constexpr uintptr_t kImageParse = 0xEBD2160;
    static constexpr size_t kStateTracker = 0x3C549F8;     // ptr to the resource-state tracker
    static constexpr size_t kTrackerBase = 0x14420;        // inside the tracker
    static constexpr size_t kTrackerMap = 0x14428;
    static constexpr size_t kCmdListWrapper = 0x19F58;     // this+0x19F58 = current command-list wrapper; +0x30 = its command list; +0x14458 = its own state-tracker block
    static constexpr size_t kCmdTrackerOffset = 0x14458;
};

// Resource-state tracker and the transition helper 0xe82d960 (docs/progress/bgfx-d3d12-dragon.md B7b), read in full. [V static]
//   void transition(Tracker* t, ID3D12GraphicsCommandList* list, u16 handle, u32 newState)   // 0xe82d960
//   handle 0xFFFF -> return. e = 0xe83aed0(&t->states, handle). !e->tracked -> tail call firstUse 0xe83b0e0(t, handle, newState) (no barrier).
//   e->current == newState: only when newState == 8 (UNORDERED_ACCESS) emit a UAV barrier {type 2, resource}; else nothing.
//   otherwise e->current = newState and emit {type 0 TRANSITION, resource, subresource 0xFFFFFFFF, before = old, after = newState}
//   through list vtbl +0xD0 = ResourceBarrier(1, &barrier). resource = *(u64*)textureRecord (TextureRecordLayout::mResource), record found
//   through t->textureTable with the same paged walk as createTexture.
struct TrackerEntry {          // 12 bytes
    uint32_t initialState;     // +0 written with the same value as current on first use (createTexture stores (s << 32) | s)
    uint32_t currentState;     // +4 D3D12_RESOURCE_STATES
    uint8_t tracked;           // +8
    uint8_t pad[3];
};
static_assert(sizeof(TrackerEntry) == 12);
struct TrackerOffsets {
    static constexpr size_t kTextureTable = 0x00;     // ptr to the texture table (D3D12Tables::kTextures base) used for the resource lookup
    static constexpr size_t kStates = 0x08;           // paged array of TrackerEntry (the "array" argument of 0xe83aed0)
    static constexpr size_t kEntriesPerPage = 0x1000; // 0xC000-byte pages, next-page pointer at page + 0xC000 (array +0xC000 relative to kStates)
    static constexpr size_t kPageBytes = kEntriesPerPage * sizeof(TrackerEntry);
    static constexpr size_t kGuardByteInArray = 0xC018; // relative to kStates: dynamic-handle guard, same rule as the texture table
    static constexpr size_t kSizeInArray = 0xC008;      // relative to kStates: size in bytes (0xe83aed0 divides by 12 via the 0xAAAAAAAAAAAAAAAB multiply)
    static constexpr size_t kTouchedList = 0xC028;      // relative to the TRACKER (not kStates): u16 handles first used since the last reset, paged (0x1000 u16 per page), appended by 0xe83b0e0
    static constexpr size_t kTouchedListBytes = 0xE030; // tracker-relative u64 bytes (shr 1 = count); list page-chain pointer at tracker+0xE028
};
static_assert(TrackerOffsets::kPageBytes == 0xC000);

// Slot numbers of interest (65-slot table, see RendererContext.h).
struct D3D12Slots {
    static constexpr size_t kRenderThreadSubmit = 50;
    static constexpr size_t kSwapchainCreate = 39;
    static constexpr size_t kPresent = 6;
    static constexpr size_t kReset = 60;
    static constexpr size_t kDeviceLost = 7;
    static constexpr size_t kFlushWait = 8;
    // Resource API, named with evidence (stub/alias pattern + command argument shapes, docs/BGFX_MAP.md 6fb). [V static]
    static constexpr size_t kCreateIndexBuffer = 10;
    static constexpr size_t kDestroyIndexBuffer = 11;
    static constexpr size_t kCreateVertexLayout = 12;
    static constexpr size_t kCreateVertexBuffer = 14;
    static constexpr size_t kDestroyVertexBuffer = 15;
    static constexpr size_t kCreateDynamicIndexBuffer = 16;
    static constexpr size_t kUpdateDynamicIndexBuffer = 17;
    static constexpr size_t kCreateDynamicVertexBuffer = 19;
    static constexpr size_t kUpdateDynamicVertexBuffer = 20;
    static constexpr size_t kCreateShader = 22;
    static constexpr size_t kDestroyShader = 23;
    static constexpr size_t kCreateProgram = 24;
    static constexpr size_t kDestroyProgram = 25;
    static constexpr size_t kCreateTexture = 26;
    static constexpr size_t kUpdateTexture = 28;
    static constexpr size_t kReadTexture = 30;
    static constexpr size_t kResizeTexture = 31;
    static constexpr size_t kOverrideInternal = 32;
    static constexpr size_t kGetInternal = 33;
    static constexpr size_t kDestroyTexture = 34;
    // M1c slots 42-45 (1.26.62.01). [V RVA/dispatch] Names/semantics partially inferred; see docs/functions/0xe817cf0.md..0xe8189c0.md.
    static constexpr size_t kSlot42 = 42; // cmd byte 21: (re)allocate per-context uniform/value storage at context + handle*8 + 0x1250, then 0xe804590(this+0xC9AA98, handle, arg)
    static constexpr size_t kSlot43 = 43; // cmd byte 37: release/clear per-context value storage and remove handle from 0x400-entry hash map at +0xC9AA9C/+0xC9AAA0/+0xC9BAA0
    static constexpr size_t kSlot44 = 44; // cmd byte 40: screenshot/readback-style GPU path ("LScreenshot")
    static constexpr size_t kSlot45 = 45; // cmd byte 22 and routed with byte 19: write bounded name into this + index*0x100 + 0x7EDE
    static constexpr size_t kUpdateUniform = 46; // (ctx, u16 handle, data, size): memcpy into ctx->kUniformValues[handle] [V body 0xe818a70]
    static constexpr size_t kSetMarker = 47;     // (ctx, data, size); empty stub in the D3D12 classes [V]
};

// The draw batcher's records, as the executor fills them (docs/functions/e821120.md part six) and the flush 0xe81b720 replays them.
// Field layouts follow the D3D12 structures they are handed to; sizes match the record strides the flush uses.
struct VertexBufferView { // D3D12_VERTEX_BUFFER_VIEW
    uint64_t bufferLocation;
    uint32_t sizeInBytes;
    uint32_t strideInBytes;
};
struct IndexBufferView { // D3D12_INDEX_BUFFER_VIEW
    uint64_t bufferLocation;
    uint32_t sizeInBytes;
    uint32_t format; // 0x39 DXGI_FORMAT_R16_UINT, 0x2A DXGI_FORMAT_R32_UINT
};
struct BatchDraw {              // non-indexed record
    VertexBufferView vbv[5];    // +0x00 up to 4 streams plus the instance-data view; unused entries zeroed
    uint64_t constants[2];      // +0x50 vertex / fragment constant buffer GPU addresses (root parameters 2 and 3)
    uint32_t vertexCount;       // +0x60 D3D12_DRAW_ARGUMENTS [I: the non-indexed argument writes are not transcribed; layout by the 0x70 stride]
    uint32_t instanceCount;     // +0x64
    uint32_t startVertex;       // +0x68
    uint32_t startInstance;     // +0x6C
};
struct BatchDrawIndexed {       // indexed record
    VertexBufferView vbv[5];    // +0x00
    IndexBufferView ibv;        // +0x50
    uint64_t constants[2];      // +0x60
    uint32_t indexCount;        // +0x70 D3D12_DRAW_INDEXED_ARGUMENTS
    uint32_t instanceCount;     // +0x74
    uint32_t startIndex;        // +0x78
    int32_t baseVertex;         // +0x7C
    uint32_t startInstance;     // +0x80
    uint32_t _84;               // +0x84 padding to the 0x88 stride
};
static_assert(sizeof(VertexBufferView) == 0x10 && sizeof(IndexBufferView) == 0x10);
// The batcher the draw executor fills and flush 0xe81b720 drains (docs/functions/e81b720.md, D2; 6ia). kind 0 = BatchDraw records,
// kind 1 = BatchDrawIndexed records.
struct DrawBatcherOffsets {
    static constexpr size_t kCommandSignature = 0x000; // ID3D12CommandSignature*[2] (ExecuteIndirect per kind)
    static constexpr size_t kPending = 0x010;          // u32[2] records waiting per kind (reset by flush)
    static constexpr size_t kRecords = 0x018;          // record arrays per kind
    static constexpr size_t kRingSlot = 0xF28;         // u32 indirect-argument ring slot (& 0x1F)
    static constexpr size_t kBarrierTable = 0xF30;     // tracked argument-buffer states, up to +0x1040
    static constexpr size_t kBarrierTableEnd = 0x1040;
    static constexpr size_t kVbCache = 0x10C0;         // the last 5 vertex buffer views bound (5 x 0x10)
    static constexpr size_t kIbCache = 0x1110;         // the last index buffer view bound (0x10)
    static constexpr size_t kLastCbv = 0x1120;         // u64[2] the last two root CBV addresses (root params 2 and 3)
    static constexpr size_t kStatDirect = 0x1148;      // u32[2] flushes that fit below kCapacity
    static constexpr size_t kStatOverflow = 0x1150;    // u32[2] flushes at or above kCapacity
    static constexpr size_t kCapacity = 0x115C;        // u32
    static constexpr size_t kIndirectEnabled = 0x1164; // u8: 0 = always draw one by one
};
static_assert(DrawBatcherOffsets::kVbCache + 5 * sizeof(VertexBufferView) == DrawBatcherOffsets::kIbCache);
static_assert(DrawBatcherOffsets::kIbCache + sizeof(IndexBufferView) == DrawBatcherOffsets::kLastCbv);
static_assert(DrawBatcherOffsets::kStatDirect + 8 == DrawBatcherOffsets::kStatOverflow);
static_assert(DrawBatcherOffsets::kRecords == DrawBatcherOffsets::kPending + 8);
struct JobContextOffsets {
    static constexpr size_t kCommandList = 0x30;      // ID3D12GraphicsCommandList* the flush records into
};
static_assert(sizeof(BatchDraw) == 0x70);
static_assert(sizeof(BatchDrawIndexed) == 0x88);
static_assert(offsetof(BatchDrawIndexed, ibv) == 0x50 && offsetof(BatchDrawIndexed, constants) == 0x60 && offsetof(BatchDrawIndexed, indexCount) == 0x70);
static_assert(offsetof(BatchDraw, constants) == 0x50 && offsetof(BatchDraw, vertexCount) == 0x60);

// Per-context resource state tracking for vertex buffers (docs/functions/e81b4d0.md). A buffer is transitioned to GENERIC_READ at most
// once per frame: the first use sets its touched bit and appends it to the touched list. [V static]
struct D3D12StateOffsets {
    static constexpr size_t kVbResources = 0xA248;    // ptr to per-handle records of 0x80 bytes, ID3D12Resource* at +0
    static constexpr size_t kVbTouchedCount = 0xA250; // u16
    static constexpr size_t kVbTouched = 0xA258;      // u64[64] bitmap, handles 0..4095
    static constexpr size_t kVbState = 0xA458;        // {u32 initial, u32 current} per handle
    static constexpr size_t kVbTouchedList = 0x12458; // u16[] handles touched this frame
    static constexpr uint32_t kGenericRead = 0xAC3;   // D3D12_RESOURCE_STATE_GENERIC_READ
    static constexpr size_t kUniformValues = 0x1250;  // void*[] value storage per uniform handle: written by updateUniform (slot 46), read by commit 0xe81e1c0
};

// Renderer fields the PSO builder uses (docs/functions/e81e860.md). [V static]
struct D3D12RendererOffsets {
    static constexpr size_t kDevice = 0x400;          // ID3D12Device*
    static constexpr size_t kRootSignature = 0x1248;  // ID3D12RootSignature*
    static constexpr size_t kDeviceState = 0x19F88;   // int, < 5 = device lost / removed (submit skips work), set to 4 on a failed create
    static constexpr size_t kDeviceLostHr = 0x19F8C;  // HRESULT of the failure
    static constexpr size_t kBackBufferFormat = 0x19F98; // DXGI_FORMAT of the swap chain
    static constexpr size_t kDepthClamp = 0x19FDC;    // u8, DepthClipEnable = !value
};
static_assert(D3D12StateOffsets::kVbTouched + 64 * 8 == 0xA458);

struct VertexLayoutRecord { // table D3D12Tables::kVertexLayouts, stride 0x54 (stock bgfx VertexLayout with 19 attributes)
    static constexpr size_t kHash = 0x00;       // u32
    static constexpr size_t kStride = 0x04;     // u16 bytes per vertex
    static constexpr size_t kOffsets = 0x06;    // u16[19]
    static constexpr size_t kAttributes = 0x2C; // u16[19] packed attribute descriptions
    static constexpr size_t kNumAttributes = 19;
};
static_assert(VertexLayoutRecord::kOffsets + 2 * VertexLayoutRecord::kNumAttributes == VertexLayoutRecord::kAttributes);
static_assert(VertexLayoutRecord::kAttributes + 2 * VertexLayoutRecord::kNumAttributes <= D3D12Tables::kVertexLayoutsStride);

struct TextureRecord {
    static constexpr size_t kFormatKey = 0x40; // u32, hashed into the PSO key for color attachments
    static constexpr size_t kFormat = 0xB0;    // u8 texture format index (16-byte format table entries, DXGI value at +8)
};
// The texture record, from TextureD3D12::create 0xe81bf30 (called by createTexture 0xe8143c0; 6hz). Handles >= 0x1000 live in overflow
// pages (ctx+0xC96178): each page is 4096 records (0xB8000 bytes) followed by the next-page pointer. The tail fields are copied from the
// bimg::ImageContainer argument (format +0x10, width +0x20, height +0x24, depth +0x28, numLayers +0x2C, numMips +0x2E, cubeMap +0x30).
struct TextureRecordLayout {
    void* mResource;          // +0x00 ID3D12Resource* (the first 0x20 bytes are stored as one block at the end of create)
    // The former "opaque view block" is three D3D12 descriptions stored back to back (live read of a 32x32 R8G8B8A8 texture, BGFX_MAP 6im):
    uint8_t mResourceDesc[0x38]; // +0x08 D3D12_RESOURCE_DESC: Dimension +0x08 (3 = TEXTURE2D), Alignment +0x10, Width +0x18, Height +0x20,
                                 // DepthOrArraySize +0x24, MipLevels +0x26, Format +0x28, SampleDesc +0x2C/+0x30, Layout +0x34, Flags +0x38 [V live]
    uint8_t mSrvDesc[0x28];   // +0x40 D3D12_SHADER_RESOURCE_VIEW_DESC: Format +0x40 (the PSO format key), ViewDimension +0x44 (4 = TEXTURE2D),
                              // Shader4ComponentMapping +0x48 (0x1688), union +0x50 (MostDetailedMip, MipLevels +0x54, PlaneSlice, MinLODClamp) [V live]
    uint8_t mUavDesc[0x28];   // +0x68 second description, Format +0x68 / ViewDimension +0x6C like the SRV (a UAV description) [I]
    uint8_t mPad90[8];        // +0x90 unread [?]
    uint32_t mFlags;          // +0x98 low 32 bits of the texture flags (6th argument)
    uint32_t mWidth;          // +0x9C width >> skipped mips, at least the format's block width
    uint32_t mHeight;         // +0xA0 height >> skipped mips, at least the block height
    uint32_t mDepth;          // +0xA4
    uint32_t mNumLayers;      // +0xA8
    uint8_t mPadAC[2];
    uint8_t mType;            // +0xAE 0 = 2D, 1 = 3D (depth >= 2), 2 = cube
    uint8_t mRequestedFormat; // +0xAF
    uint8_t mFormat;          // +0xB0 actual format; 0x42 when the format caps do not cover the texture type
    uint8_t mNumMips;         // +0xB1 numMips - skip (skip clamped to numMips - 1)
    uint8_t mPadB2[6];
};
static_assert(sizeof(TextureRecordLayout) == D3D12Tables::kTexturesStride);
static_assert(offsetof(TextureRecordLayout, mFlags) == 0x98 && offsetof(TextureRecordLayout, mNumLayers) == 0xA8);
static_assert(offsetof(TextureRecordLayout, mFormat) == TextureRecord::kFormat);
static_assert(offsetof(TextureRecordLayout, mResourceDesc) == 0x08 && offsetof(TextureRecordLayout, mSrvDesc) == 0x40);
static_assert(offsetof(TextureRecordLayout, mUavDesc) == 0x68 && offsetof(TextureRecordLayout, mPad90) == 0x90);
static_assert(TextureRecord::kFormatKey == offsetof(TextureRecordLayout, mSrvDesc));
static_assert(D3D12Tables::kTexturesStride * 4096 == 0xB8000);   // one overflow page

// The common buffer record (bgfx BufferD3D12, Mojang field order), from BufferD3D12::create 0xe812740 read in full (6hu). It is the whole
// index buffer record (stride 0x78) and the head of the vertex buffer record (stride 0x80). The two descriptors are the D3D12 SRV / UAV
// descriptions, without the d3d12.h types.
struct BufferRecord {
    void* mResource;                  // +0x00 ID3D12Resource*
    // D3D12_SHADER_RESOURCE_VIEW_DESC
    uint32_t mSrvFormat;              // +0x08 DXGI_FORMAT (3 by default, or from the compute-format table)
    uint32_t mSrvDimension;           // +0x0C 1 = BUFFER, 0xB = RAYTRACING_ACCELERATION_STRUCTURE (create type 4)
    uint32_t mSrvComponentMapping;    // +0x10 0x1688 = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING
    uint32_t mPad14;
    uint64_t mSrvFirstElement;        // +0x18 (for an acceleration structure: its GPU address)
    uint32_t mSrvNumElements;         // +0x20 size / stride
    uint32_t mSrvStructureStride;     // +0x24
    uint32_t mSrvFlags;               // +0x28
    uint32_t mPad2C;
    // D3D12_UNORDERED_ACCESS_VIEW_DESC
    uint32_t mUavFormat;              // +0x30
    uint32_t mUavDimension;           // +0x34 1 = BUFFER
    uint64_t mUavFirstElement;        // +0x38
    uint32_t mUavNumElements;         // +0x40
    uint32_t mUavStructureStride;     // +0x44
    uint64_t mUavCounterOffset;       // +0x48
    uint32_t mUavFlags;               // +0x50
    uint32_t mPad54;
    uint64_t mGpuAddress;             // +0x58 D3D12_GPU_VIRTUAL_ADDRESS
    uint32_t mSize;                   // +0x60 bytes
    uint16_t mFlags;                  // +0x64 bgfx buffer flags (0x400 = compute write, 0x2000 = persistently mapped, ...)
    bool mDynamic;                    // +0x66 created without initial data
    uint8_t mPad67;
    void* mMapped;                    // +0x68 CPU pointer from ID3D12Resource::Map when mFlags & 0x2000
    uint32_t mStride;                 // +0x70 element size (from the format table, or the caller's override)
    uint32_t mPad74;
};
static_assert(sizeof(BufferRecord) == D3D12Tables::kIndexBuffersStride);
// The resource tables are one contiguous run inside the renderer object (A8b): every base is the previous base + capacity * stride. The shader-buffer
// table (slots 36/37, 0xe815fc0: `imul rdi, handle, 0x78; add rcx, 0xa32178; call BufferD3D12::create 0xe812740`) uses the same BufferRecord layout
// as the index buffers. There is no 0x130-stride table any more (the old note came from the pre-6fc framebuffer guess). [V static + arithmetic]
using ShaderBufferRecord = struct BufferRecord;
static_assert(D3D12Tables::kIndexBuffers + 4096 * D3D12Tables::kIndexBuffersStride == D3D12Tables::kVertexBuffers);
static_assert(D3D12Tables::kVertexBuffers + 4096 * D3D12Tables::kVertexBuffersStride == D3D12Tables::kShaderBuffers);
static_assert(D3D12Tables::kShaderBuffers + 4096 * D3D12Tables::kShaderBuffersStride == D3D12Tables::kShaders);
static_assert(D3D12Tables::kShaders + 4096 * D3D12Tables::kShadersStride == D3D12Tables::kPrograms);
static_assert(D3D12Tables::kPrograms + 2048 * D3D12Tables::kProgramsStride == D3D12Tables::kTextures);
static_assert(offsetof(BufferRecord, mGpuAddress) == 0x58 && offsetof(BufferRecord, mSize) == 0x60);
static_assert(offsetof(BufferRecord, mMapped) == 0x68 && offsetof(BufferRecord, mStride) == 0x70);

// Per-handle resource records, fields the executor reads. [V static]
struct IndexBufferRecord {
    static constexpr size_t kGpuAddress = 0x58; // u64
    static constexpr size_t kSize = 0x60;       // u32 bytes
};
static_assert(IndexBufferRecord::kGpuAddress == offsetof(BufferRecord, mGpuAddress) && IndexBufferRecord::kSize == offsetof(BufferRecord, mSize));
struct VertexBufferRecord {
    static constexpr size_t kGpuAddress = 0x58;   // u64
    static constexpr size_t kSize = 0x60;         // u32 bytes
    static constexpr size_t kLayoutHandle = 0x78; // u16, 0xFFFF = use the draw stream's layout
};
static_assert(VertexBufferRecord::kLayoutHandle == sizeof(BufferRecord));   // vertex record = BufferRecord + layout handle
static_assert(VertexBufferRecord::kLayoutHandle + 8 == D3D12Tables::kVertexBuffersStride);
struct ProgramRecord {
    static constexpr size_t kVertexShader = 0x00;   // ShaderRecord*
    static constexpr size_t kFragmentShader = 0x08; // ShaderRecord*
    static constexpr size_t kPredefined = 0x10;     // PredefinedUniform[28]
    static constexpr size_t kNumPredefined = 0xF0;  // u8
};
#pragma pack(push, 1)
struct PredefinedUniform {
    uint32_t loc;   // byte offset in the stage's constant buffer
    uint16_t count; // array count (matrices: number of rows written for ModelViewProj is clamped to 4)
    uint8_t type;   // PredefinedType, | 0x10 = fragment stage
    uint8_t _pad;
};
#pragma pack(pop)
static_assert(sizeof(PredefinedUniform) == 8);
static_assert(ProgramRecord::kPredefined + 28 * sizeof(PredefinedUniform) == ProgramRecord::kNumPredefined);
// The whole program record, from createProgram 0xe8142c0 (vtable slot 24, read in full; 6hw): vertex shader pointer, fragment shader
// pointer (null for a compute / single-shader program), the vertex shader's predefined uniforms followed by the fragment shader's, the sum.
struct ShaderRecordLayout;
struct ProgramRecordLayout {
    ShaderRecordLayout* mVertex;       // +0x00 &shaders[vsh]
    ShaderRecordLayout* mFragment;     // +0x08 &shaders[fsh], unset when fsh == 0xFFFF
    PredefinedUniform mPredefined[28]; // +0x10
    uint8_t mNumPredefined;            // +0xF0 vsh.numPredefined + fsh.numPredefined
    uint8_t mPadF1[7];                 // never written
};
static_assert(sizeof(ProgramRecordLayout) == D3D12Tables::kProgramsStride);
static_assert(offsetof(ProgramRecordLayout, mPredefined) == ProgramRecord::kPredefined);
static_assert(offsetof(ProgramRecordLayout, mNumPredefined) == ProgramRecord::kNumPredefined);
enum class PredefinedType : uint8_t { // index of the executor's jump table (rva 0xF4EE7F8); names by what each case reads
    ViewRect = 0, ViewTexel = 1, View = 2, InvView = 3, Proj = 4, InvProj = 5, ViewProj = 6, InvViewProj = 7,
    PrevViewProj = 8, Model = 9, ModelView = 10, ModelViewProj = 11, PrevWorldPosOffset = 12, AlphaRef4 = 13, // names read from the name table at rva 0xF4418C0 used by nameToPredefinedUniform 0xbc60100 (u_prevViewProj, u_prevWorldPosOffset, u_alphaRef4) [V static]
};
inline constexpr uint8_t kPredefinedFragmentBit = 0x10;
struct ShaderRecord {
    static constexpr size_t kConstantBuffer = 0x08; // UniformBuffer*
    static constexpr size_t kConstantSize = 0xAE;   // u16
};
// The whole shader record (bgfx ShaderD3D12, stock member order), from createShader 0xe8137b0 (6hv). Binary magics accepted:
// 'CSH\3' 0x03485343, 'FSH\5' 0x05485346, 'VSH\5' 0x05485356 ("Unknown shader format %x." otherwise).
struct ShaderRecordLayout {
    void* mCode;                       // +0x00 copied bgfx::Memory {data*, u32 size, inline data}
    void* mConstantBuffer;             // +0x08 UniformBuffer*, created with capacity 0x400 when the shader has uniforms
    PredefinedUniform mPredefined[14]; // +0x10 type | 0x10 for a fragment shader
    uint16_t mAttrMask[19];            // +0x80 0xFFFF for each vertex attribute the shader reads (Attrib::Count = 19)
    uint8_t mPadA6[2];
    uint32_t mHash;                    // +0xA8 MurmurHash2A(iohash, code, numAttrs, attrs)
    uint16_t mNumUniforms;             // +0xAC
    uint16_t mConstantSize;            // +0xAE bytes of the constant buffer
    uint8_t mNumPredefined;            // +0xB0
    uint8_t mPadB1[7];
};
static_assert(sizeof(ShaderRecordLayout) == D3D12Tables::kShadersStride);
static_assert(offsetof(ShaderRecordLayout, mConstantBuffer) == ShaderRecord::kConstantBuffer);
static_assert(offsetof(ShaderRecordLayout, mConstantSize) == ShaderRecord::kConstantSize);
static_assert(offsetof(ShaderRecordLayout, mAttrMask) == 0x80 && offsetof(ShaderRecordLayout, mHash) == 0xA8);
static_assert(offsetof(ShaderRecordLayout, mNumPredefined) == 0xB0);

// The command queue wrapper (renderer + D3D12Offsets::kCommandQueue = 0xCC9268), a ~0x2F8D150-byte struct, and its per-frame command contexts
// (docs/progress/bgfx-d3d12-dragon.md B6). Offsets are relative to the wrapper. [V static: 0xe80ecb0, 0xe818490, 0xe81ac80, 0xe81af20, 0xe81b3b0]
struct CommandQueueOffsets {
    static constexpr size_t kQueue = 0x00;                // ID3D12CommandQueue* (vtbl +0x50 ExecuteCommandLists, +0x70 Signal)
    static constexpr size_t kUnknown2F8B790 = 0x2F8B790;  // u64 passed as 3rd argument of 0xe833210 (pre-state fixup builder) in close+execute [?]
    static constexpr size_t kCompletedValue = 0x2F8B798;  // u64 last fence value retired by 0xe818490
    static constexpr size_t kPending = 0x2F8B7A0;         // u64[] command contexts closed and waiting for ExecuteCommandLists (fixup list first, then the context's own)
    static constexpr size_t kPendingCount = 0x2F8C020;    // u64
    static constexpr size_t kInFlightEntries = 0x2F8C028; // u64[0x110] contexts executed but not yet retired
    static constexpr size_t kInFlightHead = 0x2F8C8A8;    // u64
    static constexpr size_t kInFlightTail = 0x2F8C8B0;    // u64, 0x110 = ring empty
    static constexpr size_t kFreeEntries = 0x2F8C8B8;     // u64[0x110] retired contexts ready for reuse
    static constexpr size_t kFreeHead = 0x2F8D138;
    static constexpr size_t kFreeTail = 0x2F8D140;        // 0x110 = empty
    static constexpr size_t kFence = 0x2F8D148;           // Fence*
    static constexpr size_t kRingSize = 0x110;
};
static_assert(CommandQueueOffsets::kInFlightEntries + 8 * CommandQueueOffsets::kRingSize == CommandQueueOffsets::kInFlightHead);
static_assert(CommandQueueOffsets::kInFlightTail + 8 == CommandQueueOffsets::kFreeEntries);
static_assert(CommandQueueOffsets::kFreeEntries + 8 * CommandQueueOffsets::kRingSize == CommandQueueOffsets::kFreeHead);
static_assert(CommandQueueOffsets::kFreeTail + 8 == CommandQueueOffsets::kFence);
static_assert(D3D12Offsets::kCommandQueue + CommandQueueOffsets::kPendingCount == 0x3C55288 && D3D12Offsets::kCommandQueue + CommandQueueOffsets::kFence == 0x3C563B0); // BGFX_MAP 6av absolute values
struct FenceOffsets {
    static constexpr size_t kListenersBegin = 0x00;  // vector of 0x88-byte entries; entry +0x38 and +0x78 hold objects whose vtbl +0x10 is called with &value (0xe81b3b0 uses +0x38, 0xe80ecb0 uses +0x78)
    static constexpr size_t kListenersEnd = 0x08;
    static constexpr size_t kD3DFence = 0x18;        // ID3D12Fence* (vtbl +0x40 GetCompletedValue, +0x48 SetEventOnCompletion)
    static constexpr size_t kEvent = 0x20;           // HANDLE waited on with the timeout
    static constexpr size_t kNextValue = 0x28;       // value the next Signal uses (post-incremented)
    static constexpr size_t kCompleted = 0x30;       // last GetCompletedValue, 0xFFFFFFFFFFFFFFFF = device removed
};
struct CommandContextOffsets { // the frame context: a command list + allocator + per-frame tracking, stride >= 0x2CBF0
    static constexpr size_t kCommandList = 0x30;         // ID3D12GraphicsCommandList* (vtbl +0x48 Close, +0x50 Reset)
    static constexpr size_t kTouchedTextureCount = 0x40; // u16, bitmap of 0x200 bytes at +0x48 (reset per use)
    static constexpr size_t kTouchedTextures = 0x48;
    static constexpr size_t kVbTouchedCount = 0xA250;    // = D3D12StateOffsets::kVbTouchedCount (those offsets are relative to this context)
    static constexpr size_t kVbTouched = 0xA258;
    static constexpr size_t kRangedTouchedCount = 0x224A0;
    static constexpr size_t kRangedTouched = 0x224A8;    // 0x200-byte bitmap
    static constexpr size_t kAllocator = 0x2CBC8;        // ID3D12CommandAllocator* (vtbl +0x40 Reset)
    static constexpr size_t kFenceValue = 0x2CBD0;       // u64 fence value assigned at execute
    static constexpr size_t kSubmitted = 0x2CBD8;        // u8
    static constexpr size_t kDeferredBegin = 0x2CBE0;    // vector of objects released (vtbl +0x10) when the fence passes, end at +0x2CBE8
    static constexpr size_t kDeferredEnd = 0x2CBE8;
};
static_assert(CommandContextOffsets::kTouchedTextures + 0x200 <= CommandContextOffsets::kVbTouchedCount);
static_assert(CommandContextOffsets::kVbTouched == D3D12StateOffsets::kVbTouched && CommandContextOffsets::kVbTouchedCount == D3D12StateOffsets::kVbTouchedCount);

// Root signatures, both built in code and serialized with D3D12SerializeRootSignature (version 1.0) -- there is no blob in a file.
// (docs/progress/bgfx-d3d12-dragon.md B5.) Read from the stack images of 0xe80c600 and 0xe84ba30 with the .rdata range templates dumped. [V static]
// D3D12 enum values: root parameter type 0 TABLE, 1 32BIT_CONSTANTS, 2 CBV; descriptor range type 0 SRV, 1 UAV, 2 CBV, 3 SAMPLER; append offset 0xFFFFFFFF.
// 1) The graphics root signature: created by 0xe80c600 (called only from init 0xe807ff0, 0xe80d104 is the serialize call, CreateRootSignature through
//    device vtbl +0x80, result stored at object+0x1248 = D3D12RendererOffsets::kRootSignature). Flags = 1 (ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT), no static samplers.
struct GraphicsRootSignature {
    static constexpr uintptr_t kBuilder = 0xE80C600;
    static constexpr uintptr_t kSerializeCall = 0xE80D122;
    static constexpr uint32_t kNumParameters = 5;
    static constexpr uint32_t kFlags = 1;
    // param 0: TABLE, 1 range: SAMPLER x16 at s0 space 0 (all stages)
    // param 1: TABLE, 1 range: SRV, unbounded (0xFFFFFFFF), t0 space 0
    // param 2: ROOT CBV b0 (the vertex-stage constants address, BatchDraw::constants[0])
    // param 3: ROOT CBV b1 (the fragment-stage constants address, BatchDraw::constants[1])
    // param 4: TABLE, 1 range: UAV, unbounded, u0 space 0
    static constexpr uint32_t kSamplerTableCount = 16;
    static constexpr uint32_t kRootCbvVertex = 2;
    static constexpr uint32_t kRootCbvFragment = 3;
};
// 2) The RTX / DLSS root signature: built by 0xe84ba30 (callers 0xe83d440 = RTX submit override and 0xe8403d0 = slot 64), serialized at 0xe84c340
//    from a 6-parameter description (flags 0, no static samplers).
struct RtxRootSignature {
    static constexpr uintptr_t kBuilder = 0xE84BA30;
    static constexpr uintptr_t kSerializeCall = 0xE84C340;
    static constexpr uint32_t kNumParameters = 6;
    // param 0: 32-bit constants, b2 space 0, 3 values
    // param 1: ROOT CBV b99 (0x63) space 0
    // param 2: TABLE, 13 ranges {type, count, reg, space, offset}: CBV 1 b0 s0 @0; CBV 1 b3 s0 @1; UAV 46 u0 s0 @2; SRV 64 t0 s0 @48; UAV 1 u0 s14 @145; UAV 6 u60 s0 @146;
    //          SRV 12 t0 s8 @112; UAV 12 u0 s3 @124; SRV 4 t0 s9 @136; SRV 2 t0 s4 @140; UAV 2 u0 s4 @142; UAV 2 u0 s13 @155; SRV 3 t0 s13 @152
    // param 3: TABLE, 9 ranges, 4096 each: SRV t0 s1 @12288; SRV s2 @0; SRV s3 @4096; SRV s5 @20480; UAV s1 @8192; UAV s2 @16384; UAV s10 @24576; UAV s11 @28672; UAV s9 @32768
    // param 4: TABLE, 1 range: SRV 4096 t0 space 6 @0
    // param 5: TABLE, 1 range: SAMPLER 4 s0 space 0 @0
    static constexpr uint32_t kParam2Ranges = 13;
    static constexpr uint32_t kParam3Ranges = 9;
};
static_assert(GraphicsRootSignature::kNumParameters == 5 && RtxRootSignature::kNumParameters == 6);

} // namespace bgfx::d3d12
