#pragma once
// RenderLightAmbientDescription (Light group tag 0). Light visitor 0x6640d80 case 0x6640de8 reads the description
// (in rsi): qword +0x00, dword +0x08, dword +0x10, word +0x14 [V], then queues a 0x14-byte element {qword,float,float,u16}
// into the pass vector at pass+0x800 (`0x6640eb4  add qword ptr [rsi+0x800],0x14`) [V]. Producer 0x53e2c00 extent is 0x18
// [V] (next local at rbp+0x130); +0x0C is written by the producer but never read by the case [V gap]. Size 0x18 [V extent + align].
// Field meanings are [-]: no instruction or string names them.

namespace mce::framebuilder {

struct RenderLightAmbientDescription {
    float  mValue00[2];   // +0x00 [V] `0x6640dfb  movsd xmm7,[rsi]` (read as one qword)
    float  mValue08;      // +0x08 [V] `0x6640df6  movss xmm6,[rsi+8]`
    uint8_t mPad0C[4];    // +0x0C unread by the case [V gap]
    float  mValue10;      // +0x10 [V] `0x6640dff  movss xmm0,[rsi+0x10]`
    uint16_t mValue14;    // +0x14 [V] `0x6640df1  movzx r12d,word ptr [rsi+0x14]`
    uint8_t mPad16[2];
};
static_assert(sizeof(RenderLightAmbientDescription) == 0x18);
static_assert(offsetof(RenderLightAmbientDescription, mValue08) == 0x08);
static_assert(offsetof(RenderLightAmbientDescription, mValue10) == 0x10);
static_assert(offsetof(RenderLightAmbientDescription, mValue14) == 0x14);

} // namespace mce::framebuilder
