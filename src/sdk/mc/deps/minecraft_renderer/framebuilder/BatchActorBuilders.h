#pragma once
// Draw-item prototype and builder call shapes of the ten BatchActor variant builders of 0x66d9af0 (1.26.62.01, static; dossier
// docs/functions/66d9af0_builders.md). Everything is [V] from disassembly unless tagged. Not Sigs.json-anchored, so the static_asserts
// are the guard (no layout_asserts.json entry).

#include "DrawItem.h"

namespace mce::framebuilder {

// Aligned prototype ("rec4a0") that every builder takes as its 5th (stack) argument, built by 0x66c11b0 from the packed record 0x66d9710
// writes. Each builder pushes its members into the pass pools and writes the resulting indices into a DrawItem (DrawItem.h).
struct DrawItemProto {
    uint32_t mPad00;                       // +0x00
    uint16_t mU16B;                        // +0x04 value pushed to pool +0x690 (item +0x3C)
    uint16_t mPad06;                       // +0x06
    uint16_t mU16A;                        // +0x08 value pushed to pool +0x8A0 (item +0x10)
    uint16_t mPad0A;                       // +0x0A
    DrawItemState mState;                  // +0x0C 0x58 bytes, pushed to pool +0x750 (item +0x2C)
    uint32_t mPad64;                       // +0x64
    uint64_t mShaderHead;                  // +0x68 head of the pool +0x768 element
    uint8_t mShaderBlock[0x78];            // +0x70 copied by 0xE869FF0
    void* mShaderOwned;                    // +0xE8 moved into the pool element (+0x80)
    DrawItemBounds mBounds;                // +0xF0 pushed to pool +0x660 (item +0x40); box index byte at +0x108 (0xFF = none)
    uint32_t mPad11C;                      // +0x11C
    DrawItemTransform mTransform;          // +0x120 pushed to pool +0x648 (item +0x42); variant index at +0x160
    DrawItemGeometry mGeometry;            // +0x168 pushed to pool +0x780 (item +0x28)
};
static_assert(sizeof(DrawItemProto) == 0x1C0);
static_assert(offsetof(DrawItemProto, mU16B) == 0x04);
static_assert(offsetof(DrawItemProto, mU16A) == 0x08);
static_assert(offsetof(DrawItemProto, mState) == 0x0C);
static_assert(offsetof(DrawItemProto, mShaderHead) == 0x68);
static_assert(offsetof(DrawItemProto, mShaderBlock) == 0x70);
static_assert(offsetof(DrawItemProto, mShaderOwned) == 0xE8);
static_assert(offsetof(DrawItemProto, mBounds) == 0xF0);
static_assert(offsetof(DrawItemProto, mTransform) == 0x120);
static_assert(offsetof(DrawItemProto, mGeometry) == 0x168);
static_assert(offsetof(DrawItemProto, mGeometry) + offsetof(DrawItemGeometry, mIndexKind) == 0x1A0);   // tag byte tested at 0x66c1358 etc.
static_assert(offsetof(DrawItemProto, mTransform) + offsetof(DrawItemTransform, mIndex) == 0x160);     // tag byte tested at 0x66c1279

// Packed record 0x66d9710 fills ("rec110": same members, different offsets), converted to DrawItemProto by 0x66c11b0.
struct DrawItemProtoPacked {
    uint16_t mPad00;                       // +0x00
    uint16_t mU16B;                        // +0x02 <- *(u16*)src[0x30]
    uint16_t mPad04;                       // +0x04
    uint16_t mU16A;                        // +0x06 <- *(u16*)(desc + 0x1C), desc = src[0x28]
    DrawItemState mState;                  // +0x08 <- *src[0x20]
    uint64_t mShaderHead;                  // +0x60 <- *(u64*)src[0x18]
    uint8_t mShaderBlock[0x78];            // +0x68 <- copy of src[0x18]+8 (0xE869FF0)
    void* mShaderOwned;                    // +0xE0 <- moved from src[0x18]+0x80 (source cleared)
    DrawItemBounds mBounds;                // +0xE8 box from groupRec+0x1C..+0x33, index +0x100 = (groupRec+0x34 != 0xFF ? 0 : 0xFF), extra from groupRec+0x38
    uint32_t mPad114;                      // +0x114
    DrawItemTransform mTransform;          // +0x118 mat4 = passRecord+0x00..+0x3F, index byte +0x158 = 0 (inline matrix)
    DrawItemGeometry mGeometry;            // +0x160 moved from *src[0x00]
};
static_assert(sizeof(DrawItemProtoPacked) == 0x1B8);
static_assert(offsetof(DrawItemProtoPacked, mU16B) == 0x02);
static_assert(offsetof(DrawItemProtoPacked, mU16A) == 0x06);
static_assert(offsetof(DrawItemProtoPacked, mState) == 0x08);
static_assert(offsetof(DrawItemProtoPacked, mShaderHead) == 0x60);
static_assert(offsetof(DrawItemProtoPacked, mShaderBlock) == 0x68);
static_assert(offsetof(DrawItemProtoPacked, mShaderOwned) == 0xE0);
static_assert(offsetof(DrawItemProtoPacked, mBounds) == 0xE8);
static_assert(offsetof(DrawItemProtoPacked, mTransform) == 0x118);
static_assert(offsetof(DrawItemProtoPacked, mGeometry) == 0x160);

// Sources block ("ctx3c8", 7 pointers, 0x38 bytes) the dispatcher fills at rbp+0x3C8 before every 0x66D9710 call (e.g. 0x66e12de..0x66e1332).
struct DrawProtoSources {
    DrawItemGeometry* mGeometry;           // +0x00 &rbp+0x360, built by 0x66A0F60
    const float* mPassRecord;              // +0x08 P = [rbp+0x718]: mat4 at +0x00 (translation +0x30), byte +0x50 (P50), byte +0x51 (P51)
    const uint8_t* mGroupRecord;           // +0x10 R = [rbp+0x7D0]: AABB floats +0x1C..+0x33, valid byte +0x34, vec4 +0x38
    DrawItemShaderState* mShader;          // +0x18 instance shader-state (head +0x00, block +0x08, owned +0x80)
    const DrawItemState* mRenderState;     // +0x20 &rbp+0x400 (state record built in the group loop)
    const uint8_t* mDescription;           // +0x28 [rbp+0x7A8]: u16 at +0x1C
    const uint16_t* mU16Source;            // +0x30 [rbp+0x6C0]
};
static_assert(sizeof(DrawProtoSources) == 0x38);
static_assert(offsetof(DrawProtoSources, mDescription) == 0x28);

// The {count, begin} pair every builder receives in rdx: elements are 0x30-byte (small-vector sized) records of builder state +0x480/+0x488.
struct BuilderSpan {
    uint64_t mCount;                       // (end - begin) / 0x30, built with the 0xAAAAAAAAAAAAAAAB multiply at 0x66e13be
    const void* mBegin;
};
static_assert(sizeof(BuilderSpan) == 0x10);

// Bit meanings of the 64-bit valid mask at DrawItem+0x00 and the u16 fields they guard (read from the builders' store sequence;
// the DrawItem.h view still models +0x00 as u32). Fields marked [?] have no mask bit visible in the store sequence.
namespace DrawItemMaskBits {
constexpr uint64_t kU16A = 0x1ull;                 // +0x10
constexpr uint64_t kBytePool888 = 0x2ull;          // +0x12 (builders with pool +0x888)
constexpr uint64_t kBytePool858 = 0x8ull;          // +0x16 (builders with pool +0x858)
constexpr uint64_t kPool780 = 0x1000ull;           // +0x28
constexpr uint64_t kPool768 = 0x2000ull;           // +0x2A
constexpr uint64_t kPool750 = 0x4000ull;           // +0x2C
constexpr uint64_t kBytePool6d8 = 0x80000ull;      // +0x36
constexpr uint64_t kU16B = 0x400000ull;            // +0x3C
constexpr uint64_t kPool660 = 0x1000000ull;        // +0x40
constexpr uint64_t kPool648 = 0x2000000ull;        // +0x42
constexpr uint64_t kPoolA588 = 0x200000000ull;     // +0x52
constexpr uint64_t kBytePool570 = 0x400000000ull;  // +0x54
constexpr uint64_t kBytePool3f0 = 0x4000000000000ull;  // +0x74
constexpr uint64_t kBytePool300 = 0x1000000000000000ull; // +0x88
constexpr uint64_t kBytePool318 = 0x0800000000000000ull; // +0x86
}

// Byte pools on the pass object: std::vector of 1-byte elements, one element appended per item (0x6760E60 = grow; the inline form
// increments the end pointer), index stored as u16 = (size - 1). The element type is an empty tag [?].
struct BytePoolIndexOffsets {
    static constexpr uint16_t k1f8 = 0x9E;   // f-family only (0x66cc7a0 0x66ce8d0 0x66c7680 0x66c98e0)
    static constexpr uint16_t k300 = 0x88;
    static constexpr uint16_t k318 = 0x86;   // 0x66bb7b0 / 0x66bd430 only
    static constexpr uint16_t k3f0 = 0x74;
    static constexpr uint16_t k570 = 0x54;
    static constexpr uint16_t k6d8 = 0x36;   // all but 0x66bb7b0 / 0x66bd430
    static constexpr uint16_t k858 = 0x16;
    static constexpr uint16_t k888 = 0x12;
};

} // namespace mce::framebuilder
