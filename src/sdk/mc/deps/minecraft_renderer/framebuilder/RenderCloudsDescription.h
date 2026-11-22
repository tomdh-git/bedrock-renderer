#pragma once
// RenderCloudsDescription (Sky group tag 1), one per cloud mesh piece, built by ctor 0x668e940
// (docs/data/listings/lightgame_clouds_ctor_668e940_668eb03.txt). Every field is written by that constructor [V].
// Size 0xA8 [I] (aligned end, from Descriptions.h; ctor writes up to +0xA0 then 6 tail pad bytes).


namespace mce::framebuilder {

struct RenderCloudsDescription {
    float mMatrixA[16];              // +0x00 [V] `0x668e969  movss [rax],xmm0` ... `0x668e9fe  movss [rax+0x3c],xmm0`
    float mMatrixB[16];              // +0x40 [V] `0x668ea08  movss [rax+0x40],xmm0` ... `0x668eaad  movss [rax+0x7c],xmm0`
    const void* mMesh;               // +0x80 [V] `0x668eab2  mov [rax+0x80],r9`
    float mColor[4];                 // +0x88 [V] `0x668eabc  movups [rax+0x88],xmm0`
    uint8_t mByte98;                 // +0x98 [V] `0x668eac3  mov [rax+0x98],sil`
    uint8_t mByte99;                 // +0x99 [V] `0x668eaca  mov [rax+0x99],bl`
    uint8_t mByte9A;                 // +0x9A [V] `0x668ead0  mov [rax+0x9a],r11b`
    uint8_t mPad9B;                  // +0x9B padding (no ctor store; gap before mValue9C at +0x9C)
    uint32_t mValue9C;               // +0x9C [V] `0x668eaf1  mov [rax+0x9c],r10d` (conditional, gated by bt r10,0x20 / jb)
    uint16_t mFlags;                 // +0xA0 [V] `0x668eaf8  mov [rax+0xa0],cx`
    uint8_t mPadA2[6];               // +0xA2 padding (no ctor store; tail to reach 0xA8)
};
static_assert(sizeof(RenderCloudsDescription) == 0xA8);
static_assert(offsetof(RenderCloudsDescription, mMesh) == 0x80);
static_assert(offsetof(RenderCloudsDescription, mColor) == 0x88);
static_assert(offsetof(RenderCloudsDescription, mValue9C) == 0x9C);
static_assert(offsetof(RenderCloudsDescription, mFlags) == 0xA0);

} // namespace mce::framebuilder
