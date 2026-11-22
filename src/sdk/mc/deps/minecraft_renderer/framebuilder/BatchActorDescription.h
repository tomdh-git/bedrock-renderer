#pragma once

// bluey::batchactor::Description: complete mirror of the game's RenderBatchActorDescription as the frame builder lays it out
// (Minecraft.Windows.exe 1.26.62.01). FrameBuilder.h holds only the kMinSize 0x110 stub with the Span/Instance skeletons; this
// header is the full mirror and does NOT redefine that struct.
//
// Every offset is a displacement the BatchActor producer 0x4e355a0 writes or the BatchActor extractor 0x66d9af0 reads through
// the description pointer (r8 in the extractor; [rbp-0x20] + 0x20 in the producer). Reads verified verbatim by rdis are tagged
// [V static]; values sampled in the live capture of 6d are tagged [V live]; span roles come from the magic divides [I]; the
// rest is [?].
//
// Layout (sizeof 0x110):
//   +0x00  head block: float[7] +0x00, u16 +0x1C, byte +0x30, 16 bytes +0x34, byte +0x60
//   +0x68  Span {count, data}   +0x78  Span {count, data}
//   +0x88..+0xB8 seven raw qwords (the seven source-vector begin pointers)
//   +0xC0  Span {count, data}   +0xD0  Span {count, data}
//   +0xE0  u64 instance count   +0xE8  Instance* array
//   +0xF0  Span {count, data}   +0x100 Span {count, data}
//
// Identity: no actor id and no world position is stored here [V live 6d]; identity comes from RenderMark::bodyActor
// (the description is stored at bodyActor+0xC8) and the 0xC8-byte DrawItem records it pushes (DrawItem.h).


namespace bluey::batchactor {

struct Span {
    uint64_t mCount;   // +0x00 element count [V static]
    const void* mData; // +0x08 element pointer [V static]
};
static_assert(sizeof(Span) == 0x10);
static_assert(offsetof(Span, mCount) == 0x00);
static_assert(offsetof(Span, mData) == 0x08);

struct Instance; // defined below; Description holds a pointer to it

struct Description {
    // Head block (+0x00..+0x67), written by producer 0x4e355a0 (the zero fill covers +0x00..+0x8F before head + spans are stored).
    float  mHead[7];            // +0x00 float[7] head (movups [rcx] / movsd [rcx+0x10] / movss [rcx+0x18]); the
                                // 0.67 0.82 .. 192.0 block of the 6d capture [V static]
    uint16_t mHead1C;           // +0x1C [V static] (widened from a byte)
    uint8_t mPad1E[0x12];       // +0x1E
    uint8_t mByte30;            // +0x30 = 0 [V static]
    uint8_t mPad31[3];          // +0x31
    uint8_t mBlock34[16];       // +0x34 16 bytes [V static]
    uint8_t mPad44[0x1C];       // +0x44
    uint8_t mByte60;            // +0x60 = 0 [V static]
    uint8_t mPad61[7];          // +0x61
    Span mSpan68;               // +0x68 {count, data}; stride 8 [V stores, I role]
    Span mSpan78;               // +0x78 {count, data}; stride 2 [V stores, I role]
    // +0x88..+0xB8 seven raw qwords copied from r10+0x30/+0x48/+0x60/+0x78/+0x90/+0xA8/+0xC0 (the seven
    // source-vector begin pointers) [V stores, I meaning]
    uint64_t mRaw88;
    uint64_t mRaw90;
    uint64_t mRaw98;
    uint64_t mRawA0;
    uint64_t mRawA8;
    uint64_t mRawB0;
    uint64_t mRawB8;
    Span mSpanC0;               // +0xC0 {count, data}; stride 0x14 [V stores, I role]
    Span mSpanD0;               // +0xD0 {count, data}; stride 0x34 [V stores, I role]
    uint64_t mInstanceCount;    // +0xE0 [V static: mov rax,[r8+0xE0] @0x66d9b79]
    const Instance* mInstances; // +0xE8 [V static: mov rax,[rax+0xE8] @0x66d9c07; i*0x48 stride via 0x66d9c0e/0x66d9c12]
    Span mSpanF0;               // +0xF0 {count, data}; stride 0x40 [V stores, I role]
    Span mSpan100;              // +0x100 {count, data}; stride 0x40 [V stores, I role]

    uint64_t instanceCount() const { return mInstanceCount; }   // [V static] accessor over +0xE0
    const Instance* instances() const { return mInstances; }    // [V static] accessor over +0xE8
};
static_assert(sizeof(Description) == 0x110);
static_assert(offsetof(Description, mHead1C) == 0x1C);
static_assert(offsetof(Description, mByte30) == 0x30);
static_assert(offsetof(Description, mBlock34) == 0x34);
static_assert(offsetof(Description, mByte60) == 0x60);
static_assert(offsetof(Description, mSpan68) == 0x68);
static_assert(offsetof(Description, mSpan78) == 0x78);
static_assert(offsetof(Description, mRaw88) == 0x88);
static_assert(offsetof(Description, mRawB8) == 0xB8);
static_assert(offsetof(Description, mSpanC0) == 0xC0);
static_assert(offsetof(Description, mSpanD0) == 0xD0);
static_assert(offsetof(Description, mInstanceCount) == 0xE0);
static_assert(offsetof(Description, mInstances) == 0xE8);
static_assert(offsetof(Description, mSpanF0) == 0xF0);
static_assert(offsetof(Description, mSpan100) == 0x100);

struct Instance {
    void* mRenderObject;   // +0x00 the per-instance object (0x300 bytes, contiguous) [V live 6d]
    void* mModel;          // +0x08 shared geometry resource; instances of one model share it [V live 6d]
                            // the extractor reads model+0x40 as the XXH64 hash key (0x66d9c17, key 0x19932c0 x30) [V static]
    void* mModelTwin;      // +0x10 the same resource 0x10 lower [V live 6d]
    uint32_t mFlags;       // +0x18 e.g. 0xEF000006 [V live 6d]
    float mAabbMin[3];     // +0x1C local-space bounds [V live 6d]
    float mAabbMax[3];     // +0x28 [V live 6d]
    uint32_t mUnknown34;   // +0x34 [?]
    float mScale[2];       // +0x38 [V live 6d]
    uint16_t mPacked[4];   // +0x40 packed halves (uv / bone transform) [I]
};
static_assert(sizeof(Instance) == 0x48);
static_assert(offsetof(Instance, mModel) == 0x08);
static_assert(offsetof(Instance, mFlags) == 0x18);
static_assert(offsetof(Instance, mAabbMin) == 0x1C);
static_assert(offsetof(Instance, mAabbMax) == 0x28);
static_assert(offsetof(Instance, mScale) == 0x38);
static_assert(offsetof(Instance, mPacked) == 0x40);

} // namespace bluey::batchactor
