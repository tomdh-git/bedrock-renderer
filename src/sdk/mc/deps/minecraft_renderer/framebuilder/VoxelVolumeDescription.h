#pragma once
// VoxelVolumeDescription (Light group tag 6), read by the light visitor 0x6640d80 case 0x664187d
// (docs/functions/6640d80_light_visitor.md section 3). Every field below is a [V] read of the
// description pointer in rsi. The producer (0x53599d0) builds a 0x30-byte object; the visitor reads
// +0x00..+0x27, so +0x28..+0x2F is padding to the producer size [I size, V reads].

namespace mce::framebuilder {

struct VoxelVolumeDescription {
    void*   mPairA;     // +0x00 pointer to a {object, control-block} pair; use count at ctrl+8 incremented [V 0x664187d]
    void*   mPairB;     // +0x08 pointer to a second {object, control-block} pair [V 0x6641b3a]
    uint64_t mValue10;  // +0x10 qword [V 0x6641bb4]
    void*   mVecBegin;  // +0x18 vector begin, elements are 8 bytes [V 0x6641bd8]
    void*   mVecEnd;    // +0x20 vector end [V 0x6641bd4]
    uint8_t mPad28[8];  // +0x28..+0x2F padding to producer size 0x30 [I]
};
static_assert(sizeof(VoxelVolumeDescription) == 0x30);
static_assert(offsetof(VoxelVolumeDescription, mPairA) == 0x00);
static_assert(offsetof(VoxelVolumeDescription, mPairB) == 0x08);
static_assert(offsetof(VoxelVolumeDescription, mValue10) == 0x10);
static_assert(offsetof(VoxelVolumeDescription, mVecBegin) == 0x18);
static_assert(offsetof(VoxelVolumeDescription, mVecEnd) == 0x20);

} // namespace mce::framebuilder
