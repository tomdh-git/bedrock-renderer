#pragma once
// RenderItemInHandDescription (Item group tag 6; producer ctor 0x668cb70, thin insert clone 0x531b180, extractor 0x6698e30, 1.26.62.01).
// Layout is instruction-complete for the constructor 0x668cb70 (docs/functions/668cb70.md): every store into the object is listed.
// Object size 0x180 (last store +0x17C). Tags: [V] disassembly. Names are by role; where a value is a copy of a field of the
// renderer-side object it says which.
#include <cstddef>
#include <cstdint>

namespace mce::framebuilder {

struct ItemInHandSharedPair { void* mPtr; void* mCtl; };  // {ptr, shared_ptr control block (strong +8, weak +0xC)}
static_assert(sizeof(ItemInHandSharedPair) == 0x10);

// Variant tag at +0x150 (copied from tag byte +0x30 of the source variant); 0xFF = unset (ctor stores it before the switch).
// 0: no payload. 1: +0x138 = heap block (0x20 B). 2/3: +0x138 raw ptr, +0x140 shared pair.
struct ItemInHandDescription {
    void* mItemObjectPlus8;                 // +0x00 = srcObject + 8 (ctor arg rdx)
    ItemInHandSharedPair mTextureA;         // +0x08 resolved by 0x4dfb570 from srcObject+0x270 (or a static default)
    ItemInHandSharedPair mTextureB;         // +0x18 resolved by 0x4dfb570 from stack arg5
    ItemInHandSharedPair mItemData;         // +0x28 copy of the shared pair passed in r9; extractor reads [ptr+0x40] (flags word, cache at +0x258/+0x25C)
    float mTransform[16];                   // +0x38..+0x77 mat4 copied from stack arg6 (top of the ctx matrix stack)
    uint8_t mFlag78;                        // +0x78 = *r8 (renderItem stack byte arg); extractor: bit0 / bit3 (0x08) / bit6 (0x40) used
    uint8_t mFlag79;                        // +0x79 = stack arg7 (= ctxObj[+0x75])
    uint8_t mFlag7A;                        // +0x7A = srcObject[+0x293]
    uint8_t mFlag7B;                        // +0x7B = srcObject[+0x292]
    uint8_t mFlag7C;                        // +0x7C = srcObject[+0x296]
    uint8_t mFlag7D;                        // +0x7D = stack arg11 (= ctxObj[+0x7C])
    uint8_t mPad7E[2];                      // +0x7E..+0x7F not written [V]
    float mParamVec80[4];                   // +0x80 = [[a8+0xF8]+0x40] 4 floats   (a8 = stack arg8 = ctxObj[+0x20] parameter object)
    float mParamVec90[4];                   // +0x90 = [[a8+0xD0]+0x40] 4 floats
    float mParamVecA0[4];                   // +0xA0 = [[a8+0xF0]+0x40] 4 floats
    float mParamVecB0[4];                   // +0xB0 = [[a8+0x108]+0x40] 4 floats
    float mParamVecC0[4];                   // +0xC0 = [[a8+0xD8]+0x40] 4 floats
    float mParamVecD0[2];                   // +0xD0 = [[a8+0xE0]+0x40] 2 floats
    float mParamVecD8[4];                   // +0xD8 = [[a8+0xE8]+0x40] 4 floats
    float mParamVecE8[4];                   // +0xE8 = [[a8+0x70]+0x40] 4 floats
    float mParamVecF8[2];                   // +0xF8 = [[a8+0x78]+0x40] 2 floats
    float mParamScalar100;                  // +0x100 = [[a8+0x80]+0x40] 1 float
    float mUvOffset[2];                     // +0x104 = [[a8+0x110]+0x40] 2 floats (added to scaled UV rect)
    float mParamVec10C[2];                  // +0x10C = [[a8+0x118]+0x40] 2 floats
    float mUvScale[2];                      // +0x114 = [[a8+0x120]+0x40] 2 floats; nonzero -> UV rect at +0x170 is rewritten
    uint16_t mWord11C;                      // +0x11C = stack arg9 (= ctxObj[+0x74] word)
    uint8_t mPad11E[2];
    uint8_t mVariantCopy120[0x10];          // +0x120 16 bytes copied from [arg10+0]
    uint8_t mVariantByte130;                // +0x130 = [arg10+0x10]
    uint8_t mPad131[7];                     // +0x131..+0x137 not written [V]
    void* mVariantPtr138;                   // +0x138 tag1: heap block {ptr,ctl,16B copy}; tag2/3: raw [arg10+0x18]
    ItemInHandSharedPair mVariantShared140; // +0x140 tag2/3 only: {[arg10+0x20], [arg10+0x28] (strong ref inc)}; tag 0/1 leave it unwritten
    uint8_t mVariantTag150;                 // +0x150 0xFF then [arg10+0x30] (0..3)
    uint8_t mPad151[7];
    float mSrcFloats158[6];                 // +0x158..+0x16F = srcObject[+0x180..+0x194] (6 floats)
    float mUvRect[4];                       // +0x170..+0x17F: srcObject[+0x198..+0x1A4] copied raw; if mUvScale != 0 replaced by {min u, min v, max u, max v}
};
// NOTE: +0x170..+0x17C are srcObject[+0x198..+0x1A4] (4 floats) copied raw, then optionally rewritten as the UV rect.

static_assert(offsetof(ItemInHandDescription, mTextureA) == 0x08);
static_assert(offsetof(ItemInHandDescription, mTextureB) == 0x18);
static_assert(offsetof(ItemInHandDescription, mItemData) == 0x28);
static_assert(offsetof(ItemInHandDescription, mTransform) == 0x38);
static_assert(offsetof(ItemInHandDescription, mFlag78) == 0x78);
static_assert(offsetof(ItemInHandDescription, mFlag7D) == 0x7D);
static_assert(offsetof(ItemInHandDescription, mParamVec80) == 0x80);
static_assert(offsetof(ItemInHandDescription, mParamVec90) == 0x90);
static_assert(offsetof(ItemInHandDescription, mParamVecA0) == 0xA0);
static_assert(offsetof(ItemInHandDescription, mParamVecB0) == 0xB0);
static_assert(offsetof(ItemInHandDescription, mParamVecC0) == 0xC0);
static_assert(offsetof(ItemInHandDescription, mParamVecD0) == 0xD0);
static_assert(offsetof(ItemInHandDescription, mParamVecD8) == 0xD8);
static_assert(offsetof(ItemInHandDescription, mParamVecE8) == 0xE8);
static_assert(offsetof(ItemInHandDescription, mParamVecF8) == 0xF8);
static_assert(offsetof(ItemInHandDescription, mParamScalar100) == 0x100);
static_assert(offsetof(ItemInHandDescription, mUvOffset) == 0x104);
static_assert(offsetof(ItemInHandDescription, mParamVec10C) == 0x10C);
static_assert(offsetof(ItemInHandDescription, mUvScale) == 0x114);
static_assert(offsetof(ItemInHandDescription, mWord11C) == 0x11C);
static_assert(offsetof(ItemInHandDescription, mVariantCopy120) == 0x120);
static_assert(offsetof(ItemInHandDescription, mVariantByte130) == 0x130);
static_assert(offsetof(ItemInHandDescription, mVariantPtr138) == 0x138);
static_assert(offsetof(ItemInHandDescription, mVariantShared140) == 0x140);
static_assert(offsetof(ItemInHandDescription, mVariantTag150) == 0x150);
static_assert(offsetof(ItemInHandDescription, mSrcFloats158) == 0x158);
static_assert(offsetof(ItemInHandDescription, mUvRect) == 0x170);
static_assert(sizeof(ItemInHandDescription) == 0x180);

}  // namespace mce::framebuilder
