#pragma once
// RenderLightTag2Description (Light group tag 2 = GameplayMetadata [I tag from jump table [0xF2BF2B0] per
// descriptions.md R6]). Light visitor 0x6640d80 case 0x6640f1b copies the whole 0x84-byte description verbatim into the
// pass vector at pass+0x498/+0x4A0 (element stride 0x84, `0x6641090  add qword ptr [rdi+0x4A0],0x84`) [V]. Reads:
// movups rows +0x00/+0x10/+0x20/+0x2A and movss scalars +0x3C..+0x80 step 4 [V]. Offsets with no read
// (+0x04..+0x0F, +0x14..+0x1F, +0x24..+0x29, +0x2E..+0x3B, +0x7D..+0x7F) are zero-initialised padding [I].
// Size 0x84 [V: copy length confirmed by the stride add]. Field meanings are [-].

namespace mce::framebuilder {

struct RenderLightTag2Description {
    uint8_t mData[0x84];   // +0x00 [V] whole-description verbatim copy by case 0x6640f1b:
                           // `0x6640f8c  movups xmm0,[rsi]` `0x6640f8f  movups xmm1,[rsi+0x10]`
                           // `0x6640f93  movups xmm2,[rsi+0x20]` `0x6640f97  movups xmm3,[rsi+0x2A]`
                           // `0x6640fb2  movss xmm0,[rsi+0x3C]` ... `0x664107e  movss xmm0,[rsi+0x80]`
};
static_assert(sizeof(RenderLightTag2Description) == 0x84);

} // namespace mce::framebuilder
