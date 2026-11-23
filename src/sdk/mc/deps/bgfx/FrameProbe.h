#pragma once
// Read-only frame-probe declarations for docs/progress/oc_U-EQ1c.md (Q1c R3 frame probe:
// per-frame dump of typed descriptions, pass list, draw records + RenderDraw +
// material/program/PSO key, actor attribution).
//
// Every offset below is pinned by a verbatim instruction from the exe
// (C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe,
// version 1.26.62.01). [V] = the instruction read/store is shown verbatim in the
// progress file; [I] = role inferred from structure/order. This header documents
// seams and layouts only: it registers no hooks, patches nothing, and performs no
// reads or writes at runtime. It is safe to include from a read-only dump tool.
//
// Frame (two buffers alternate, 0xE749C0 bytes apart; see docs/BGFX_MAP.md 6e)
//   kDrawHeaders      = 0xB4700   RenderDrawHeader[], stride 0x80   [V] executor 0xe82269e
//   kSortedItems      = 0x94700   uint16_t[65536] draw order        [V] executor 0xe822673
//   kRenderDraws      = 0x8B4700  RenderDraw array object, stride 0x540  [V] executor 0xe8226e9
//   kItemCount        = 0xDC57E8  u32 atomic draw-slot counter, cap 0xFFFE [V]
//   kFrameCounter     = 0xE746D8  u32, +1 per frame                 [V] submit 0xe82e34c
//
// Per-item RenderDraw block: +0x514 u32 bind hash / bind block  [V] 0xe8226e9
//
// Program / PSO key path (executor 0xe822483..0xe822549):
//   programIndex   = (sortKey >> 0x15) & 0x7FF                     [V] 0xe822483/0xe82248e
//   programRecord  = renderer + 0xB62178 + programIndex * 0xF8     [V] 0xe822493
//   psoProbeKey    = u32 at programRecord + 0xA8                   [V] 0xe8224b0
//   bucketCount    = (block[0x50] - block[0x48]) >> 3              [V] 0xe8224c5/0xe8224c8
//   node key       = [node+0], next = [node+0x10]                  [V] 0xe822524/0xe822540/0xe822549
//   PSO key mask   = 0x707007FFFFFF0FF (state word)                [V] drawExecutor/layout_asserts.json
//
// Actor attribution [I]: bodyActor (0x66D0A00) reads body+0x150 flag and follows the
// body+0x140 chain, pushing one 0xC8-byte item record per actor [V:
// 0x66d0a51 cmp byte ptr [rax+0x150],0 ; 0x66d0a65 mov rax,[rax+0x140].
// BatchActor instances carry NO actor id/entity id/world position (instance =
// model/draw record only: +0x00 render record*, +0x08 model resource*, key at
// resource+0x40) [V live 6d]; identity routes through bodyActor S+0xC8 / the entt
// registry components (SceneObjectActors) [I]. Correction: 0x5aba5c0 is
// ThreadLocalObject<T>::get (+0xA0 = TLS slot index), NOT passLookup [V:
// 0x5aba5cd lea ebx,[rcx+0xA0]].


namespace bgfx {

// Frame offsets pinned by verbatim instructions (see docs/progress/oc_U-EQ1c.md table).
struct FrameOffsets {
    static constexpr std::size_t kFrameSize = 0xE749C0;        // [V] distance between the two frame buffers
    static constexpr std::uintptr_t kViewRemap = 0x0;          // [V] uint16_t[256], identity
    static constexpr std::uintptr_t kSortedItems = 0x94700;    // [V] uint16_t[65536] draw order, 0xe822673
    static constexpr std::uintptr_t kDrawHeaders = 0xB4700;    // [V] RenderDrawHeader[], stride 0x80, 0xe82269e
    static constexpr std::uintptr_t kRenderDraws = 0x8B4700;   // [V] RenderDraw array object, stride 0x540, 0xe8226e9
    static constexpr std::uintptr_t kSideTables = 0x8B4778;    // [V] SideTable* per render item
    static constexpr std::uintptr_t kItemCount = 0xDC57E8;     // [V] u32 draw-slot counter, cap 0xFFFE
    static constexpr std::uintptr_t kBlitCount = 0xDC57EC;     // [V] u16 blit-item counter
    static constexpr std::uintptr_t kBackbufferSize = 0xDC5808;// [V] {u32 width, u32 height}
    static constexpr std::uintptr_t kFrameCounter = 0xE746D8;  // [V] u32, +1 per frame, 0xe82e34c
    static constexpr std::uintptr_t kSortKeys = 0x14700;       // [V] uint64_t[] sort keys
    static constexpr std::uintptr_t kOcclusion = 0x14300;      // [V] int32_t occlusion results
};

// The 0x80-byte draw header (bgfx RenderDraw, Mojang layout), packed as the game
// lays it out. Every named field is pinned by a verbatim instruction in the exe.
// Unnamed gaps are bytes no reversed code has given a meaning yet.
#pragma pack(push, 1)
struct DrawHeader {
    // +0x00..0x1F: four RenderStream entries {u32 startVertex, u16 vbHandle, u16 layout} —
    //   used entries are the bits of streamMask (+0x63). Not individually reader-verified.
    std::uint8_t _00[0x20];

    std::uint64_t stateFlags;       // +0x20 u64 render state; bit 62 tested by executor  [V] 0xe8226bf
    std::uint64_t stencil;          // +0x28 u64 (second state word: stencil/flags)
    std::uint32_t rgba;             // +0x30 u32 blend factor
    std::uint32_t uniformBegin;     // +0x34 u32                                             [V] 0xe8224b0 context
    std::uint32_t uniformEnd;       // +0x38 u32                                             [V] 0xe8224b0 context
    std::uint32_t startMatrix;      // +0x3C u32
    std::uint32_t startIndex;       // +0x40 u32                                             [I]
    std::uint32_t numIndices;       // +0x44 u32, 0xFFFFFFFF = whole buffer                  [V]
    std::uint32_t indexStride;      // +0x48 u32, 2 or 4                                     [V]
    std::uint32_t numVertices;      // +0x4C u32                                             [I]
    std::uint32_t instanceDataOffset;// +0x50 u32                                            [V]
    std::uint32_t numInstances;     // +0x54 u32                                             [V]
    std::uint16_t instanceDataStride;// +0x58 u16                                            [V]
    std::uint16_t startIndirect;    // +0x5A u16, multiplied by 32 (indirect record stride)  [V]
    std::uint16_t numIndirect;      // +0x5C u16, 0xFFFF = whole indirect buffer             [V]
    std::uint16_t numMatrices;      // +0x5E u16                                             [V]
    std::uint16_t scissor;          // +0x60 u16 rect index, 0xFFFF = none                   [V] 0xe822737
    std::uint8_t submitFlags;       // +0x62 u8, sign bit inverts occlusion visibility test  [V]
    std::uint8_t streamMask;        // +0x63 u8                                              [V]
    std::uint8_t uniformIdx;        // +0x64 u8, index into the Frame's UniformBuffer* table [V]
    std::uint8_t _65[3];            // +0x65 padding
    std::int32_t depthBias;         // +0x68 D3D12 rasterizer DepthBias (part of PSO key)    [V]
    float slopeScaledDepthBias;     // +0x6C SlopeScaledDepthBias                            [V]
    float depthBiasClamp;           // +0x70 DepthBiasClamp                                  [V]
    std::uint16_t indexBuffer;      // +0x74 u16 handle, 0xFFFF = non-indexed                [V]
    std::uint16_t instanceDataBuffer;// +0x76 u16 handle, 0xFFFF = none                     [V]
    std::uint16_t indirectBuffer;   // +0x78 u16 handle, 0xFFFF = normal (batched) draw      [V]
    std::uint16_t occlusionQuery;   // +0x7A u16 handle, 0xFFFF = none                       [V] 0xe8226c7
    std::uint8_t _7C[4];            // +0x7C padding to 0x80
};
#pragma pack(pop)

static_assert(sizeof(DrawHeader) == 0x80, "DrawHeader must be 0x80 bytes");
static_assert(offsetof(DrawHeader, stateFlags) == 0x20);
static_assert(offsetof(DrawHeader, uniformBegin) == 0x34);
static_assert(offsetof(DrawHeader, uniformEnd) == 0x38);
static_assert(offsetof(DrawHeader, startIndex) == 0x40);
static_assert(offsetof(DrawHeader, numIndices) == 0x44);
static_assert(offsetof(DrawHeader, indexStride) == 0x48);
static_assert(offsetof(DrawHeader, numVertices) == 0x4C);
static_assert(offsetof(DrawHeader, instanceDataOffset) == 0x50);
static_assert(offsetof(DrawHeader, numInstances) == 0x54);
static_assert(offsetof(DrawHeader, instanceDataStride) == 0x58);
static_assert(offsetof(DrawHeader, startIndirect) == 0x5A);
static_assert(offsetof(DrawHeader, numIndirect) == 0x5C);
static_assert(offsetof(DrawHeader, numMatrices) == 0x5E);
static_assert(offsetof(DrawHeader, scissor) == 0x60);
static_assert(offsetof(DrawHeader, submitFlags) == 0x62);
static_assert(offsetof(DrawHeader, streamMask) == 0x63);
static_assert(offsetof(DrawHeader, uniformIdx) == 0x64);
static_assert(offsetof(DrawHeader, depthBias) == 0x68);
static_assert(offsetof(DrawHeader, slopeScaledDepthBias) == 0x6C);
static_assert(offsetof(DrawHeader, depthBiasClamp) == 0x70);
static_assert(offsetof(DrawHeader, indexBuffer) == 0x74);
static_assert(offsetof(DrawHeader, instanceDataBuffer) == 0x76);
static_assert(offsetof(DrawHeader, indirectBuffer) == 0x78);
static_assert(offsetof(DrawHeader, occlusionQuery) == 0x7A);

// Per-item RenderDraw block, stride 0x540 [V: 0xe82267c imul r15,rax,0x540]. The bind hash /
// bind block lives at +0x514 [V: 0xe8226e9 mov r8d,[r8+r15+0x514]].
static constexpr std::size_t kRenderDrawStride = 0x540;
static constexpr std::size_t kRenderDrawBindHash = 0x514;

// Draw-header field -> executor-read verification map (verbatim RVAs).
//   stateFlags       +0x20  bit62 tested         0xe8226b3 read / 0xe8226bf shr r8,0x3E
//   numIndices       +0x44  0xFFFFFFFF = whole   0xe8224b0 probe-key context
//   indexStride      +0x48  2 or 4               DXGI_FORMAT 0x39/0x2A selection
//   scissor          +0x60  0xFFFF = none        0xe822737 movzx edx,word ptr [r12+0x60]
//   occlusionQuery   +0x7A  0xFFFF = none        0xe8226c7 movzx edx,word ptr [r9+rdx+0x7A]

} // namespace bgfx
