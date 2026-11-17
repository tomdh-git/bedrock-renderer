#pragma once

// Light visitor 0x6640d80 (1.26.62.01): read-views of the Light-group descriptions ShadowAtlasFrame (tag 4), VoxelVolume (tag 6) and
// TransitioningVoxelVolume (tag 7), plus the pass-object records they are copied into. Source: docs/functions/6640d80_light_visitor.md
// (listing docs/data/listings/light_visitor_6640d80_6645400.txt, every quoted instruction re-checked with rdis). READ-VIEWS: a named member
// exists only where a read was seen at a quoted instruction; gaps are explicit pad members with NO meaning and the view size stops at the last
// read, it is not the producer's sizeof. Tag -> type was fixed from the producer 0x53599d0, whose four FrameBuilder::insert call sites carry the
// type in their source-location record (tag 3 LightPoint, 4 ShadowAtlasFrame, 6 VoxelVolume, 7 TransitioningVoxelVolume; GameplayMetadata is
// tag 2 from the clone 0x53e5910, byte store 0x53e5fb4). LightPoint (tag 3) is not typed here.


namespace mce::framebuilder::lightvis {

// A {object, shared control block} pair: copy 16 bytes from the address, `lock inc dword [ctrl+8]` when ctrl != 0 (use count; [ctrl+0xC] is the weak
// count, released after the use count reaches 0: std::shared_ptr control block). Tags 6 and 7 hold POINTERS to such pairs (mov rax,[rsi];
// mov rcx,[rax+8]; lock inc [rcx+8]; movups xmm0,[rax]: 0x664187d..0x6641897, 0x664189b..0x66418a2).
struct SharedPairRead {
    void* mObject;     // +0x00 movups xmm0,[rax] (0x66418a2) copies both qwords
    void* mCtrl;       // +0x08 mov rcx,[rax+8] (0x664188a); null => only [rax] is copied and ctrl := 0 (0x6641b25..0x6641b2f)
};
static_assert(sizeof(SharedPairRead) == 0x10);
static_assert(offsetof(SharedPairRead, mCtrl) == 0x08);

// ShadowAtlasFrame (Light tag 4, case head 0x6640ec1 -> 0x66418f0). The 0x50 bytes are copied unchanged into the pass vector +0x1C8/+0x1D0/+0x1D8
// (stride 0x50, in place 0x66419a5..0x66419bc, grow path 0x6641ce9..0x6643471 and 0x66438d9..0x66439ae).
struct ShadowAtlasFrameDescriptionReads {
    float mRow0[4];       // +0x00 movups xmm6,[rsi] (0x6640ec1)
    float mRow1[4];       // +0x10 movups xmm7,[rsi+0x10] (0x6640ecb)
    float mRow2[4];       // +0x20 movups xmm8,[rsi+0x20] (0x6640ed6)
    float mRow3[4];       // +0x30 movups xmm9,[rsi+0x30] (0x6640ee3)
    void* mTexture;       // +0x40 mov rbx,[rsi+0x40] (0x66418f0)
    void* mTextureCtrl;   // +0x48 mov rcx,[rsi+0x48] (0x6640f01); non-null => lock inc dword [rcx+8] (0x6640f0e), r12 = [rsi+0x48] (0x6640f12)
};
static_assert(offsetof(ShadowAtlasFrameDescriptionReads, mRow0) == 0x00);
static_assert(offsetof(ShadowAtlasFrameDescriptionReads, mRow1) == 0x10);
static_assert(offsetof(ShadowAtlasFrameDescriptionReads, mRow2) == 0x20);
static_assert(offsetof(ShadowAtlasFrameDescriptionReads, mRow3) == 0x30);
static_assert(offsetof(ShadowAtlasFrameDescriptionReads, mTexture) == 0x40);
static_assert(offsetof(ShadowAtlasFrameDescriptionReads, mTextureCtrl) == 0x48);
static_assert(sizeof(ShadowAtlasFrameDescriptionReads) == 0x50);

// VoxelVolume (Light tag 6, case head 0x664187d). rsi = description. Moved into a 0x40-byte VoxelRecord (pass+0x138 vector, push 0x67D5FF0).
struct VoxelVolumeDescriptionReads {
    const SharedPairRead* mPairA;   // +0x00 mov rax,[rsi] (0x664187d)
    const SharedPairRead* mPairB;   // +0x08 mov rax,[rsi+8] (0x6641b3a)
    uint64_t mQword10;              // +0x10 mov r13,[rsi+0x10] (0x6641bb4)
    const uint8_t* mVecBegin;       // +0x18 mov rcx,[rsi+0x18] (0x6641bd8): 8-byte elements, copied as 4 words per element (0x6642300..0x664233a)
    const uint8_t* mVecEnd;         // +0x20 mov rbx,[rsi+0x20] (0x6641bd4)
};
static_assert(offsetof(VoxelVolumeDescriptionReads, mPairA) == 0x00);
static_assert(offsetof(VoxelVolumeDescriptionReads, mPairB) == 0x08);
static_assert(offsetof(VoxelVolumeDescriptionReads, mQword10) == 0x10);
static_assert(offsetof(VoxelVolumeDescriptionReads, mVecBegin) == 0x18);
static_assert(offsetof(VoxelVolumeDescriptionReads, mVecEnd) == 0x20);
static_assert(sizeof(VoxelVolumeDescriptionReads) == 0x28);

// TransitioningVoxelVolume (Light tag 7, case head 0x6641524). rsi = description. Split into a VoxelRecord (+0x00,+0x08,+0x10,+0x20..+0x28) pushed
// to pass+0x138 and a TransitionRecord (+0x18, +0x38..+0x40) pushed to pass+0x168.
struct TransitioningVoxelVolumeDescriptionReads {
    const SharedPairRead* mPairA;   // +0x00 mov rax,[rsi] (0x664213a)
    const SharedPairRead* mPairB;   // +0x08 mov rax,[rsi+8] (0x66421a9)
    uint64_t mQword10;              // +0x10 mov r12,[rsi+0x10] (0x6642223)
    uint64_t mQword18;              // +0x18 mov rax,[rsi+0x18] (0x6641524) -> [rbp+0xAC0] -> TransitionRecord +0x00
    const uint8_t* mVecBegin;       // +0x20 mov rcx,[rsi+0x20] (0x6642244): 8-byte elements (0x6642390..0x66423cd)
    const uint8_t* mVecEnd;         // +0x28 mov rbx,[rsi+0x28] (0x6642240)
    uint8_t mPad30[8];              // +0x30 not read by this case
    const uint8_t* mU32Begin;       // +0x38 mov rcx,[rsi+0x38] (0x6641548): dword array, memcpy 0xEEC6DE0 (0x664212b)
    const uint8_t* mU32End;         // +0x40 mov rbx,[rsi+0x40] (0x6641544)
};
static_assert(offsetof(TransitioningVoxelVolumeDescriptionReads, mPairA) == 0x00);
static_assert(offsetof(TransitioningVoxelVolumeDescriptionReads, mPairB) == 0x08);
static_assert(offsetof(TransitioningVoxelVolumeDescriptionReads, mQword10) == 0x10);
static_assert(offsetof(TransitioningVoxelVolumeDescriptionReads, mQword18) == 0x18);
static_assert(offsetof(TransitioningVoxelVolumeDescriptionReads, mVecBegin) == 0x20);
static_assert(offsetof(TransitioningVoxelVolumeDescriptionReads, mVecEnd) == 0x28);
static_assert(offsetof(TransitioningVoxelVolumeDescriptionReads, mU32Begin) == 0x38);
static_assert(offsetof(TransitioningVoxelVolumeDescriptionReads, mU32End) == 0x40);
static_assert(sizeof(TransitioningVoxelVolumeDescriptionReads) == 0x48);

// Pass-object element of the vector at pass+0x138/+0x140 (tags 6 and 7). The mover 0x67D5FF0 (stride: shr eax,6 at 0x66424a2 / 0x6642681) reads
// [src+0x00],+0x08 (zeroing it), +0x10, +0x18, +0x20, +0x28 (zeroing it), +0x38 (zeroing it): a MOVE of this layout.
struct VoxelRecordRead {
    SharedPairRead mA;        // +0x00 tag 6 local [rbp+0xBE8]; tag 7 local [rbp+0xC00]
    SharedPairRead mB;        // +0x10 tag 6 [rbp+0xBF8]; tag 7 [rbp+0xC10]
    uint64_t mQword20;        // +0x20 description +0x10 (tag 6 store 0x6642408, tag 7 store 0x66425ea)
    void* mVecBegin;          // +0x28 copied vector of 8-byte elements (tag 6 [rbp+0xC10], tag 7 [rbp+0xC28])
    void* mVecEnd;            // +0x30
    void* mVecCap;            // +0x38 (tag 6 [rbp+0xC20] store 0x664242b, tag 7 [rbp+0xC38] store 0x664260a)
};
static_assert(offsetof(VoxelRecordRead, mB) == 0x10);
static_assert(offsetof(VoxelRecordRead, mQword20) == 0x20);
static_assert(offsetof(VoxelRecordRead, mVecBegin) == 0x28);
static_assert(offsetof(VoxelRecordRead, mVecEnd) == 0x30);
static_assert(offsetof(VoxelRecordRead, mVecCap) == 0x38);
static_assert(sizeof(VoxelRecordRead) == 0x40);

// Pass-object element of the vector at pass+0x168/+0x170/+0x178 (tag 7 only, stride 0x20, shr eax,5 at 0x6643f4e / move loop 0x6643d50..0x6643d8b).
struct TransitionRecordRead {
    uint64_t mQword00;        // +0x00 description +0x18 (store 0x6643cef, move 0x6643d50/0x6643d54)
    void* mU32Begin;          // +0x08 copied dword array (move 0x6643d66/0x6643d72 movups [+8])
    void* mU32End;            // +0x10
    void* mU32Cap;            // +0x18 (move 0x6643d58/0x6643d5d)
};
static_assert(offsetof(TransitionRecordRead, mU32Begin) == 0x08);
static_assert(offsetof(TransitionRecordRead, mU32End) == 0x10);
static_assert(offsetof(TransitionRecordRead, mU32Cap) == 0x18);
static_assert(sizeof(TransitionRecordRead) == 0x20);

}  // namespace mce::framebuilder::lightvis
