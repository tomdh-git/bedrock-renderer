#pragma once
// RenderLightTag4Description (Light group tag 4 = ShadowAtlasFrame-like [I tag from jump table [0xF2BF2B0] per
// descriptions.md R6]). Light visitor 0x6640d80 case 0x6640ec1 copies the description verbatim: 4 movups rows
// +0x00/+0x10/+0x20/+0x30 [V], then qword +0x48 (`0x6640f01  mov rcx,[rsi+0x48]`) which is a shared-ref control block
// whose strong count is incremented (`0x6640f0e  lock inc dword ptr [rcx+8]`) [V]; the element is appended to the pass
// vector at pass+0x498/+0x4A0 with stride 0x50 [V]. Size 0x50 [V]. The +0x40 object pointer is not read by this case
// (producer-only, [I]) and is kept as padding here. Field meanings are [-].

namespace mce::framebuilder {

struct RenderLightTag4Description {
    float  mMatrix[16];     // +0x00 [V] four movups rows: `0x6640ec1  movups xmm6,[rsi]` ... `0x6640ee3  movups xmm9,[rsi+0x30]`
    uint8_t mPad40[8];      // +0x40 object pointer: producer-only, never read by case 0x6640ec1 [I]
    void*  mControlBlock;   // +0x48 [V] `0x6640f01  mov rcx,[rsi+0x48]`; `0x6640f0e  lock inc dword ptr [rcx+8]`
};
static_assert(sizeof(RenderLightTag4Description) == 0x50);
static_assert(offsetof(RenderLightTag4Description, mControlBlock) == 0x48);

} // namespace mce::framebuilder
