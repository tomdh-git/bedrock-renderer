#pragma once
// Chunk draw-list entry (element of the vector view at RenderChunkGeometryDescription +0x38 {u64 count, ptr +0x40}) and the draw descriptor
// 0x678F640 packs (1.26.62.01, static; docs/functions/66ea3d0.md "Body A" and docs/functions/678c4c0.md). Only offsets read by the
// extractor loop 0x66ec31d..0x66ec8c0 and by 0x678C4C0 are named; the rest is padding [?].
#include <cstddef>
#include <cstdint>

#include "DrawItem.h"

namespace mce::framebuilder {

struct ChunkDrawListEntry {
    void* mA;                  // +0x00 tag 0: mesh object* (0x678c62b: r12 = [e]); tag 1: base of a 0x50-byte-stride record array
    void* mB;                  // +0x08 tag 1 only: pointer whose +0x48/+0x40 are read (0x678c6af)
    uint8_t mPad10[8];         // +0x10 tag 0: pointer value tested by the extractor; tag 1: u8 record index at +0x10 (0x678c50c)
    uint64_t mCount;           // +0x18 tag 0: vertex/index count, must fit u32 (shr 0x20 test at 0x678c632); tag 1: pointer tested by the extractor
    uint8_t mPad20[8];         // +0x20
    uint8_t mVariant;          // +0x28 0 or 1 selects the layout above, anything else throws (0x678cc55)
    uint8_t mPad29[7];
    uint8_t mIndexIsId;        // +0x30 1 = index buffer given by id (0xc2aa290 resolver), 0 = direct record
    uint8_t mPad31[3];
    uint32_t mStartIndex;      // +0x34 -> DrawItemGeometry::mStartIndex (+0x40)
    uint32_t mIndexCount;      // +0x38 -> DrawItemGeometry::mIndexCount (+0x48)
    float mPos[2];             // +0x3C local translation x,y (movsd 0x66ec68a)
    float mZ;                  // +0x44 local translation z (+8.0 in the shift variants)
    float mScale;              // +0x48 uniform scale, 1.0 = none (0x66ec719)
    float mFogAlpha;           // +0x4C FogAlpha uniform when > 0 (0x66ec7f7)
    uint8_t mPad50[8];         // +0x50
};
static_assert(sizeof(ChunkDrawListEntry) == 0x58);
static_assert(offsetof(ChunkDrawListEntry, mCount) == 0x18);
static_assert(offsetof(ChunkDrawListEntry, mVariant) == 0x28);
static_assert(offsetof(ChunkDrawListEntry, mIndexIsId) == 0x30);
static_assert(offsetof(ChunkDrawListEntry, mStartIndex) == 0x34);
static_assert(offsetof(ChunkDrawListEntry, mIndexCount) == 0x38);
static_assert(offsetof(ChunkDrawListEntry, mPos) == 0x3C);
static_assert(offsetof(ChunkDrawListEntry, mZ) == 0x44);
static_assert(offsetof(ChunkDrawListEntry, mScale) == 0x48);
static_assert(offsetof(ChunkDrawListEntry, mFogAlpha) == 0x4C);

// Output of 0x678F640(out, const DrawItemTransform* transform, DrawItemGeometry* geometry, DrawItemShaderState* shader): moves the
// parts into one descriptor (geometry and shader owned pointer are moved, the 0x78 shader block is copied with 0xE869FF0).
struct ChunkDrawDescriptor {
    uint64_t mPad00;                 // +0x00
    uint64_t mShaderHead;            // +0x08 = shader->mHead
    uint8_t mShaderBlock[0x78];      // +0x10
    void* mShaderOwned;              // +0x88 moved from shader+0x80
    DrawItemGeometry mGeometry;      // +0x90 moved from *geometry (variant tag at +0xC8)
    DrawItemTransform mTransform;    // +0xE8 copy of *transform (variant tag at +0x128; 0 = 16 floats, 1 = moved vector, 2 = pointer)
};
static_assert(sizeof(ChunkDrawDescriptor) == 0x130);
static_assert(offsetof(ChunkDrawDescriptor, mShaderHead) == 0x08);
static_assert(offsetof(ChunkDrawDescriptor, mShaderBlock) == 0x10);
static_assert(offsetof(ChunkDrawDescriptor, mShaderOwned) == 0x88);
static_assert(offsetof(ChunkDrawDescriptor, mGeometry) == 0x90);
static_assert(offsetof(ChunkDrawDescriptor, mTransform) == 0xE8);
static_assert(offsetof(ChunkDrawDescriptor, mGeometry) + offsetof(DrawItemGeometry, mIndexKind) == 0xC8);
static_assert(offsetof(ChunkDrawDescriptor, mTransform) + offsetof(DrawItemTransform, mIndex) == 0x128);

} // namespace mce::framebuilder
