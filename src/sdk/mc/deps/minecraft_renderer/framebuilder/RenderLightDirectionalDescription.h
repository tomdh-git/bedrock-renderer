#pragma once
// RenderLightDirectionalDescription (Light group tag 1). Light visitor 0x6640d80 case 0x66415b0 reads the description
// (in rsi); the case is gated on pass+0x70 == 1 (`0x66415b0  cmp dword ptr [rdi+0x70],1`) [V]. Reads: movups +0x00,
// byte +0x10, qword +0x14, dword +0x1C, u16 +0x20 [V]. Last read ends at +0x22, so sizeof 0x24 [V extent + align 4].
// Producer thin clone 0x5370960 stores the same offsets [I producer_fields.txt]. Field meanings are [-].

namespace mce::framebuilder {

struct RenderLightDirectionalDescription {
    float  mVec00[4];     // +0x00 [V] `0x66415cc  movups xmm2,[rsi]`
    uint8_t mByte10;      // +0x10 [V] `0x66415c3  movzx ecx,byte ptr [rsi+0x10]`
    uint8_t mPad11[3];
    float  mValue14[2];   // +0x14 [V] `0x66415c7  movsd xmm1,[rsi+0x14]`
    float  mValue1C;      // +0x1C [V] `0x66415ba  movss xmm0,[rsi+0x1C]`
    uint16_t mValue20;    // +0x20 [V] `0x66415bf  movzx eax,word ptr [rsi+0x20]`
    uint8_t mPad22[2];
};
static_assert(sizeof(RenderLightDirectionalDescription) == 0x24);
static_assert(offsetof(RenderLightDirectionalDescription, mByte10) == 0x10);
static_assert(offsetof(RenderLightDirectionalDescription, mValue14) == 0x14);
static_assert(offsetof(RenderLightDirectionalDescription, mValue1C) == 0x1C);
static_assert(offsetof(RenderLightDirectionalDescription, mValue20) == 0x20);

} // namespace mce::framebuilder
