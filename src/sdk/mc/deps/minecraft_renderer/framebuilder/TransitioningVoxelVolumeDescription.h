#pragma once
// TransitioningVoxelVolumeDescription (Light group tag 7), read by the light visitor 0x6640d80 case 0x6641524
// (docs/functions/6640d80_light_visitor.md section 4). Every field below is a [V] read of the
// description pointer in rsi. Size 0x48: last read is +0x40 (8 bytes), and the dossier records
// "desc size >= 0x48".

namespace mce::framebuilder {

struct TransitioningVoxelVolumeDescription {
    void*   mPairA;        // +0x00 pointer to a {object, control-block} pair [V 0x664213a]
    void*   mPairB;        // +0x08 pointer to a second {object, control-block} pair [V 0x66421a9]
    uint64_t mValue10;     // +0x10 qword [V 0x6642223]
    uint64_t mValue18;     // +0x18 qword (moved into TransitionRecord +0x00) [V 0x6641524]
    void*   mVecBegin;     // +0x20 vector begin, elements are 8 bytes [V 0x6642244]
    void*   mVecEnd;       // +0x28 vector end [V 0x6642240]
    uint8_t mPad30[8];     // +0x30..+0x37 padding [I]
    void*   mDwordBegin;   // +0x38 dword array begin [V 0x6641548]
    void*   mDwordEnd;     // +0x40 dword array end [V 0x6641544]
};
static_assert(sizeof(TransitioningVoxelVolumeDescription) == 0x48);
static_assert(offsetof(TransitioningVoxelVolumeDescription, mPairA) == 0x00);
static_assert(offsetof(TransitioningVoxelVolumeDescription, mPairB) == 0x08);
static_assert(offsetof(TransitioningVoxelVolumeDescription, mValue10) == 0x10);
static_assert(offsetof(TransitioningVoxelVolumeDescription, mValue18) == 0x18);
static_assert(offsetof(TransitioningVoxelVolumeDescription, mVecBegin) == 0x20);
static_assert(offsetof(TransitioningVoxelVolumeDescription, mVecEnd) == 0x28);
static_assert(offsetof(TransitioningVoxelVolumeDescription, mDwordBegin) == 0x38);
static_assert(offsetof(TransitioningVoxelVolumeDescription, mDwordEnd) == 0x40);

} // namespace mce::framebuilder
