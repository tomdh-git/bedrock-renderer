#pragma once
// RenderPlayerVisionDescription (Effect group tag 3). Built on the stack by insert<RenderPlayerVisionDescription>
// 0x53e62b0 (fat clone, fully reversed: docs/functions/53e62b0.md; checklist 6fw). The description local is at
// [rbp+0x44]; every field below is written there by that constructor [V]. Size 0x14 [V: end of last store].
// Field meanings mPlayer4D4/mPulse are [I]: no instruction names them.

namespace mce::framebuilder {

struct RenderPlayerVisionDescription {
    bool   mVisionEffect;   // +0x00 [V] `0x53e6676  mov [rbp+0x44],r12b`
    uint8_t mPad01[3];
    float  mVisionScale;    // +0x04 [V] `0x53e667a  movss [rbp+0x48],xmm0`
    float  mPlayer4D4;      // +0x08 [V] `0x53e667f  movss [rbp+0x4C],xmm8` (player +0x4D4 [I])
    float  mBlockLight;     // +0x0C [V] `0x53e6685  movss [rbp+0x50],xmm1`
    float  mPulse;          // +0x10 [V] `0x53e668a  movss [rbp+0x54],xmm6`
};
static_assert(sizeof(RenderPlayerVisionDescription) == 0x14);
static_assert(offsetof(RenderPlayerVisionDescription, mVisionScale) == 0x04);
static_assert(offsetof(RenderPlayerVisionDescription, mPulse) == 0x10);

} // namespace mce::framebuilder
