#pragma once
// RenderChunkGeometryDescription (Item group tag 3, extractor 0x66ea3d0 in 1.26.62.01).
// Only the fields the extractor head reads directly (rva 0x66ea3d0..0x66ec2a0, docs/functions/66ea3d0.md) are named; all offsets are
// [V] from the disassembly (rbx = description from rva 0x66eaf56 on, r12 = description in the head). Bytes between the named
// fields are NOT decoded [?]. The type is deliberately a view with explicit offsets, not a layout claim for the whole object: the
// object size is unknown (the producer is the thin clone 0x15a6880, which only stores the pointer).

namespace mce::framebuilder {

// The pass kind the extractor switches on (value read from *(u64*)(desc + 0x48)). Names of the values are NOT recovered [?]; the
// predicates the extractor derives from it are in docs/functions/66ea3d0.md. Special values: 1 = EndPortal(ForwardPBR),
// 0xB = WaterPrepass, 0xD and 0xA/0xB/0xC take the dedicated builders 0x67762e0 / 0x670b6e0 / 0x6722cb0 (see dossier).
using ChunkPassKind = uint64_t;

struct ChunkGeometryDescriptionView {
    void* mShared0Ptr;            // +0x00 shared_ptr-like pair {ptr, control block} (control block refcount at ctl+8, +0xC)
    void* mShared0Ctl;            // +0x08
    void* mShared1Ptr;            // +0x10 second pair, copied under lock inc in the block at 0x66eb06f..0x66eb090
    void* mShared1Ctl;            // +0x18
    uint8_t mPad20[0x10];         // +0x20..+0x2F [?]
    uint64_t mBindingCount;       // +0x30 compared with 2 at 0x66eafd2 (jb -> single-binding path)
    uint8_t mPad38[0x10];         // +0x38..+0x47 [?]
    const ChunkPassKind* mPassKind; // +0x48 pointer to the pass-kind value
    uint8_t mFlag50;              // +0x50 selects the predicate set (0x66ea5ba)
    uint8_t mPad51[3];
    float mFogColor[4];           // +0x54 written whole as uniform FogColor (movups at 0x66eb99e)
    float mFogAndDistance[4];     // +0x64 written whole as uniform FogAndDistanceControl when mFlagB8 == 0 (movups at 0x66eb91a)
    float mTime;                  // +0x74 ViewPositionAndTime.w (movss at 0x66eb6c2)
    uint8_t mPad78[0x40];         // +0x78..+0xB7 [?]
    uint8_t mFlagB8;              // +0xB8 MeshContext.x / ViewPositionAndTime and Fog selector (movzx at 0x66ea56e)
    uint8_t mPadB9[0x1F];         // +0xB9..+0xD7 [?]
    uint8_t mModeD8;              // +0xD8 compared with 3 (0x66ea72e)
    uint8_t mPadD9[7];
    uint8_t mFlagE0;              // +0xE0 (0x66ea65c)
    uint8_t mFlagE1;              // +0xE1 (0x66ea76f)
    uint8_t mPadE2[2];
    float mViewPos[3];            // +0xE4 ViewPositionAndTime.xyz when mFlagB8 == 0 (movsd [+0xE4] + movss [+0xEC] at 0x66eb750)
};
static_assert(offsetof(ChunkGeometryDescriptionView, mShared1Ptr) == 0x10);
static_assert(offsetof(ChunkGeometryDescriptionView, mBindingCount) == 0x30);
static_assert(offsetof(ChunkGeometryDescriptionView, mPassKind) == 0x48);
static_assert(offsetof(ChunkGeometryDescriptionView, mFlag50) == 0x50);
static_assert(offsetof(ChunkGeometryDescriptionView, mFogColor) == 0x54);
static_assert(offsetof(ChunkGeometryDescriptionView, mFogAndDistance) == 0x64);
static_assert(offsetof(ChunkGeometryDescriptionView, mTime) == 0x74);
static_assert(offsetof(ChunkGeometryDescriptionView, mFlagB8) == 0xB8);
static_assert(offsetof(ChunkGeometryDescriptionView, mModeD8) == 0xD8);
static_assert(offsetof(ChunkGeometryDescriptionView, mFlagE0) == 0xE0);
static_assert(offsetof(ChunkGeometryDescriptionView, mFlagE1) == 0xE1);
static_assert(offsetof(ChunkGeometryDescriptionView, mViewPos) == 0xE4);

// Per-frame context (rdx of every Item extractor, kept at [rbp+0x8a0] in the visitor, [rbp+0x16a8] in 0x66ea3d0). Fields read by the head:
struct ItemFrameContextView {
    void* mP00;                   // +0x00 [rax] -> value stored into three registry entries as the "owner" (0x66ea466/0x66ea535)
    uint8_t mPad08[0x28];
    void* mReg30;                 // +0x30 registry object (entt storage) #2, +0x30 sub-offset passed to 0xa784c0
    uint8_t mPad38[8];
    void* mReg40;                 // +0x40 registry object #3 / material cache arg r9 for 0x675e440
    void* mReg48;                 // +0x48 registry object #1
    uint8_t mPad50[0x18];
    void* mP68;                   // +0x68 material resolver arg rcx for 0x675e440
    uint32_t mMode70;             // +0x70 render mode; ==1 selects the ForwardPBR material family (read when desc+0xB8 == 0, 0x66ea58b)
    uint8_t mFlag74;              // +0x74 (0x66ea79a)
    uint8_t mFlag75;              // +0x75 (0x66ea66c)
};
static_assert(offsetof(ItemFrameContextView, mReg30) == 0x30);
static_assert(offsetof(ItemFrameContextView, mReg40) == 0x40);
static_assert(offsetof(ItemFrameContextView, mReg48) == 0x48);
static_assert(offsetof(ItemFrameContextView, mP68) == 0x68);
static_assert(offsetof(ItemFrameContextView, mMode70) == 0x70);
static_assert(offsetof(ItemFrameContextView, mFlag74) == 0x74);
static_assert(offsetof(ItemFrameContextView, mFlag75) == 0x75);

} // namespace mce::framebuilder
