#pragma once


namespace mce::framebuilder {

// The 0xC8-byte record a pass's item vector holds (pass object from ThreadLocalObject::get 0x5aba5c0: begin +0x00, end +0x08, cap +0x10).
// Pushed by the two item writers 0x6765020 and 0x6768c70 (both called from RenderMark::bodyActor 0x66D0A00; docs/BGFX_MAP.md 6hc).
// The record carries no data of its own: every field is a u16 index into a per-pass pool that the same call appended to just before
// (index = pool.size() - 1), plus a mask of which indices are set. 1.26.62.01, static.
struct DrawItem {
    uint32_t mValidMask;           // +0x00 bits set as the pools are filled: 0x1, 0x4400001, then 0x7407001 when complete
    uint32_t mKindA;               // +0x04 2 for items from 0x6765020 (which also fill mPoolA), 0 otherwise
    uint16_t mPad08;               // +0x08
    uint16_t mKindB;               // +0x0A 2 for items from 0x6768c70 (which also fill mPoolB), 0 otherwise
    uint8_t mPad0C[0x04];          // +0x0C
    uint16_t mU16PoolA;            // +0x10 index into pass+0x8A0 (u16 values: the writer's 3rd argument)
    uint8_t mPad12[0x16];          // +0x12
    uint16_t mPool780;             // +0x28 index into pass+0x780 (0x58-byte DrawItemGeometry records, push 0x675f3b0)
    uint16_t mPool768;             // +0x2A index into pass+0x768 (0x88-byte shader-state blocks, copy 0xe869ff0, ownership of +0x80 moved)
    uint16_t mPool750;             // +0x2C index into pass+0x750 (0x58-byte state records)
    uint8_t mPad2E[0x0E];          // +0x2E
    uint16_t mU16PoolB;            // +0x3C index into pass+0x690 (u16 values: the writer's 4th argument)
    uint8_t mPad3E[0x02];          // +0x3E
    uint16_t mPool660;             // +0x40 index into pass+0x660 (0x2C-byte records, push 0x6762270)
    uint16_t mPool648;             // +0x42 index into pass+0x648 (0x48-byte records, push 0x675fb30)
    uint16_t mU32Pool;             // +0x44 index into pass+0x630 (u32 values)
    uint8_t mPad46[0x0C];          // +0x46
    uint16_t mPoolA;               // +0x52 0x6765020 only: index into pass+0x588 (0x30-byte records, built by 0x6764990)
    uint8_t mPad54[0x5E];          // +0x54
    uint16_t mPoolB;               // +0xB2 0x6768c70 only: index into pass+0x108 (0x38-byte records, built by 0x67693f0)
    uint8_t mPadB4[0x14];          // +0xB4
};
static_assert(sizeof(DrawItem) == 0xC8);
static_assert(offsetof(DrawItem, mKindA) == 0x04);
static_assert(offsetof(DrawItem, mKindB) == 0x0A);
static_assert(offsetof(DrawItem, mU16PoolA) == 0x10);
static_assert(offsetof(DrawItem, mPool780) == 0x28);
static_assert(offsetof(DrawItem, mPool768) == 0x2A);
static_assert(offsetof(DrawItem, mPool750) == 0x2C);
static_assert(offsetof(DrawItem, mU16PoolB) == 0x3C);
static_assert(offsetof(DrawItem, mPool660) == 0x40);
static_assert(offsetof(DrawItem, mPool648) == 0x42);
static_assert(offsetof(DrawItem, mU32Pool) == 0x44);
static_assert(offsetof(DrawItem, mPoolA) == 0x52);
static_assert(offsetof(DrawItem, mPoolB) == 0xB2);

// The pools on the pass object the indices above point into: {begin, end, cap} vectors at these offsets, element sizes beside them.
struct DrawItemPassPools {
    static constexpr uintptr_t kItems = 0x000;     // std::vector<DrawItem>
    static constexpr uintptr_t kPoolB = 0x108;     // 0x38-byte records
    static constexpr uintptr_t kPoolA = 0x588;     // 0x30-byte records
    static constexpr uintptr_t kU32 = 0x630;       // u32
    static constexpr uintptr_t k648 = 0x648;       // 0x48-byte records
    static constexpr uintptr_t k660 = 0x660;       // 0x2C-byte records
    static constexpr uintptr_t kU16B = 0x690;      // u16
    static constexpr uintptr_t k750 = 0x750;       // 0x58-byte records
    static constexpr uintptr_t k768 = 0x768;       // 0x88-byte records
    static constexpr uintptr_t k780 = 0x780;       // 0x58-byte records
    static constexpr uintptr_t kU16A = 0x8A0;      // u16
};

// Pool element layouts, from the push helpers (6hd). Copy/move semantics are as the helpers do them; field names are by role [I].

// pool +0x108 (writer B, push 0x67693f0): two shared_ptrs (AddRef'd on copy), 16 bytes, a u64.
struct DrawItemShared {
    void* mFirst;             // +0x00
    void* mFirstCtrl;         // +0x08
    void* mSecond;            // +0x10
    void* mSecondCtrl;        // +0x18
    uint8_t mData[0x10];      // +0x20
    uint64_t mTail;           // +0x30
};
static_assert(sizeof(DrawItemShared) == 0x38);

// pool +0x588 (writer A, copy 0x6764990): a small vector with one inline 0x20-byte element ({?, shared_ptr ctrl at +8}).
struct DrawItemSmallVector {
    void* mData;              // +0x00 points at mInline when not spilled
    uint32_t mSize;           // +0x08
    uint32_t mCapacity;       // +0x0C
    uint8_t mInline[0x20];    // +0x10
};
static_assert(sizeof(DrawItemSmallVector) == 0x30);

// pool +0x660 (push 0x6762270): an optional box and four floats.
struct DrawItemBounds {
    float mBox[6];            // +0x00 min xyz, max xyz [I]
    uint8_t mBoxIndex;        // +0x18 0 = set, 0xFF = empty (variant-style index)
    uint8_t mPad19[3];
    float mExtra[4];          // +0x1C
};
static_assert(sizeof(DrawItemBounds) == 0x2C);

// pool +0x648 (push 0x675fb30): the transform variant submitPass (0xbcc38e0) takes: index at +0x40,
// 0 = one inline mat4, 1 = list of mat4 (instancing), 2 = pointer form, 0xFF = empty.
// Alternatives read from the push 0x675fb30 (6hk): 0 = float[16] inline (copied element by element), 1 = std::vector<mat4> (moved:
// begin +0x00, end +0x08, cap +0x10), 2 = one pointer at +0x00 (copied).
struct DrawItemTransform {
    enum Index : uint8_t { kInlineMatrix = 0, kMatrixList = 1, kPointer = 2, kEmpty = 0xFF };
    uint8_t mStorage[0x40];   // +0x00
    uint8_t mIndex;           // +0x40
    uint8_t mPad41[7];

    const float* inlineMatrix() const { return reinterpret_cast<const float*>(mStorage); }
    // Alternative 1: [begin, end) of 0x40-byte matrices.
    const float* listBegin() const { return *reinterpret_cast<const float* const*>(mStorage); }
    const float* listEnd() const { return *reinterpret_cast<const float* const*>(mStorage + 8); }
};
static_assert(sizeof(DrawItemTransform) == 0x48);

// pool +0x750 (inline copy in both writers): render state block, the same 0x58 bytes DirectionalLightingPass copies from resources+0x23C.
// Field meanings from the converter 0xbcc1910, which turns this block into bgfx state bits (tables rdata 0xF44BEE0 / 0xF44BF38 / 0xF44BF78; 6hl).
struct DrawItemState {
    // index 1..11 -> BGFX_STATE_BLEND_FUNC_SEPARATE(src, dst, src, dst) << 12; 0 = no blending
    enum Blend : uint32_t {
        kBlendNone = 0, kReplace = 1, kAlpha = 2, kAlphaPremultipliedOut = 3, kPremultiplied = 4, kInvert = 5,
        kAdditive = 6, kAdditiveAlpha = 7, kMultiply = 8, kMultiply2x = 9, kZeroInvSrcAlpha = 10, kZeroSrcAlpha = 11,
    };
    enum Cull : uint32_t { kCullNone = 0, kCullCw = 1 /*bit 36*/, kCullCcw = 2 /*bit 37*/ };
    // 1..8 -> BGFX_STATE_DEPTH_TEST_*: Never, Less, Equal, LessEqual, Greater, NotEqual, GreaterEqual, Always
    enum DepthFunc : uint8_t { kNever = 1, kLess, kEqual, kLessEqual, kGreater, kNotEqual, kGreaterEqual, kAlways };
    // 0 = triangle list, 1 = line list (PT_LINES), 2 = line strip (PT_LINESTRIP), 3 = triangle strip (PT_TRISTRIP)
    enum Primitive : uint32_t { kTriangleList = 0, kLineList = 1, kLineStrip = 2, kTriangleStrip = 3 };

    Blend mBlend;             // +0x00
    uint8_t mWriteMask;       // +0x04 low 4 bits -> BGFX_STATE_WRITE_R/G/B/A
    uint8_t mPad05[3];
    Cull mCull;               // +0x08
    bool mDepthTest;          // +0x0C
    bool mDepthWrite;         // +0x0D -> bit 38
    DepthFunc mDepthFunc;     // +0x0E (used only when mDepthTest)
    uint8_t mPad0F;
    Primitive mPrimitive;     // +0x10 -> bits 48..49
    uint8_t mByte14;          // +0x14 copied through to the converted state +0x38
    uint8_t mPad15[3];
    float mFloats[4];         // +0x18 copied through (+0x3C)
    uint64_t mValue28;        // +0x28 copied through (+0x4C)
    uint32_t mValue30;        // +0x30 copied through (+0x54)
    // One stencil face, encoded by 0xe86d770 into a bgfx stencil word: ref | readMask << 8 | test | ops (tables rdata 0xF491060, 0xF4F0120/40/60).
    struct StencilFace {
        // 0 Keep, 1 Zero, 2 Replace, 3 IncrSat, 4 DecrSat, 5 Invert, 6 Incr, 7 Decr. The game's tables map 3, 4 and 5 to bgfx ZERO.
        enum Op : uint32_t { kKeep = 0, kZero, kReplace, kIncrSat, kDecrSat, kInvert, kIncr, kDecr };
        DepthFunc mFunc;      // +0x00 same 1..8 order as depth -> bits 16..19
        uint8_t mPad01[3];
        Op mDepthFail;        // +0x04 -> OP_FAIL_Z, bits 24..27
        Op mPass;             // +0x08 -> OP_PASS_Z, bits 28..31
        Op mStencilFail;      // +0x0C -> OP_FAIL_S, bits 20..23
    };
    static_assert(sizeof(StencilFace) == 0x10);

    StencilFace mStencilFront; // +0x34 encoded when mStencil
    StencilFace mStencilBack;  // +0x44
    bool mStencil;            // +0x54
    uint8_t mStencilRef;      // +0x55 bits 0..7 of both faces
    uint8_t mStencilReadMask; // +0x56 bits 8..15 of both faces
    uint8_t mPad57;
};
static_assert(sizeof(DrawItemState) == 0x58);
static_assert(offsetof(DrawItemState, mPrimitive) == 0x10);
static_assert(offsetof(DrawItemState, mStencilFront) == 0x34);
static_assert(offsetof(DrawItemState, mStencil) == 0x54);

// pool +0x768 (push 0x6760710 / inline): u64 then the 0x78-byte shader-state block (copy 0xe869ff0), then an owned pointer (moved).
struct DrawItemShaderState {
    uint64_t mHead;           // +0x00
    uint8_t mBlock[0x78];     // +0x08
    void* mOwned;             // +0x80
};
static_assert(sizeof(DrawItemShaderState) == 0x88);

// pool +0x780 (push 0x675f3b0): the GEOMETRY reference (6hp; earlier notes called it the material record). Same record buildScreenPass
// (0xbc37320) takes and ScreenDraw binds from pass+0x88: bindVertexStreams 0xbcc2b00 reads +0x08..+0x20, bindIndexBuffer 0xbcc2eb0 reads
// +0x28..+0x48 and writes RenderDraw startIndex / numIndices / indexBuffer.
// One element of DrawItemGeometry's stream vector, resolved by 0xbcc2820 (6hq).
struct DrawItemVertexStream {
    // 0 = pointer to a vertex buffer object {u16 handle +0x0C, vertex layout +0x10}; 1 = {u64 id +0x00, u8 +0x08} resolved through
    // 0xe327b30 (optionally with a layout override, below); 2 = pointer to an owner whose +0x18 is that vertex buffer object.
    enum Kind : uint8_t { kBufferPtr = 0, kBufferId = 1, kOwnerPtr = 2 };
    uint8_t mStorage[0x10];   // +0x00
    uint32_t mLayoutOverride; // +0x10 bit 16 = present; low 16 bits = layout key, FNV-1a hashed into the layout map (mutex-guarded)
    uint32_t mPad14;
    Kind mKind;               // +0x18
    uint8_t mPad19[7];
    uint32_t mStartVertex;    // +0x20 added to the resolved buffer offset -> RenderStream startVertex
    uint32_t mPad24;
};
static_assert(sizeof(DrawItemVertexStream) == 0x28);
static_assert(offsetof(DrawItemVertexStream, mKind) == 0x18);
static_assert(offsetof(DrawItemVertexStream, mStartVertex) == 0x20);

struct DrawItemGeometry {
    // The index buffer reference variant: 0 = none, 1 = pointer to a buffer record {u16 handle +0, u8 dynamic +2, u32 size +4,
    // u8 32-bit indices +0xC}, 2 = {u64 id, u8} resolved through 0xe32e310, 3 = shared_ptr whose object holds the buffer record at +0x18.
    enum IndexRef : uint8_t { kNoIndices = 0, kIndexBufferPtr = 1, kIndexBufferId = 2, kIndexBufferShared = 3, kEmpty = 0xFF };

    uint64_t mHead;           // +0x00
    void* mStreamsBegin;      // +0x08 std::vector of 0x28-byte vertex stream references (resolved by 0xbcc2820)
    void* mStreamsEnd;        // +0x10
    void* mStreamsCap;        // +0x18
    uint64_t mVertexCount;    // +0x20 must fit in u32 (RenderDraw numVertices)
    uint8_t mIndexBuffer[0x10]; // +0x28 IndexRef storage
    IndexRef mIndexKind;      // +0x38
    uint8_t mPad39[7];
    uint32_t mStartIndex;     // +0x40 added to the buffer's own offset -> RenderDraw startIndex
    uint32_t mPad44;
    uint64_t mIndexCount;     // +0x48 must fit in u32 -> RenderDraw numIndices
    uint64_t mValue50;        // +0x50 copied with the record, use not seen yet [?]
};
static_assert(sizeof(DrawItemGeometry) == 0x58);
static_assert(offsetof(DrawItemGeometry, mIndexKind) == 0x38);
static_assert(offsetof(DrawItemGeometry, mStartIndex) == 0x40);
static_assert(offsetof(DrawItemGeometry, mIndexCount) == 0x48);

} // namespace mce::framebuilder
