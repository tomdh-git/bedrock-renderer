#pragma once
// RenderEnvironmentalTextDescription (Item group tag 0, in-world text such as signs), built by ctor 0x668b400
// (docs/progress/envtext_ctor_668b400.txt, docs/functions/668b400.md). Every field below is written by that constructor [V].
// Size 0xE8 [I] (aligned end, from Descriptions.h; ctor writes up to +0xE4 then 2 tail pad bytes).


namespace mce::framebuilder {

// Reference-counted pointer as the game stores it: object ptr + control block (strong count at ctrl+8).
struct SharedRef {
    void* mPtr;
    void* mCtrl;
};
static_assert(sizeof(SharedRef) == 0x10);

struct RenderEnvironmentalTextDescription {
    const void* mSource;           // +0x00 [V] `0x668b446  mov [rcx],rdx`
    SharedRef mTexture;            // +0x08 [V] `0x668b450  call 0x4DFB570` (converts r8 to SharedRef at [rcx+8])
    float mMatrix[16];             // +0x18 [V] `0x668b459  movss [rsi+0x18],xmm0` ... `0x668b4ef  movss [rsi+0x54],xmm0` (from [rdi+0x0..0x3C])
    float mPosition[3];            // +0x58 [V] `0x668b4f9  movss [rsi+0x58],xmm0` ... `0x668b50f  movss [rsi+0x60],xmm0` (from [r15+0x0..0x8])
    float mBlock64[4];             // +0x64 [V] `0x668b519  movups [rsi+0x64],xmm0` (from [r13])
    char pad74[4];                 // +0x074 padding (no ctor store; gap before mText at +0x078)
    SharedRef mText;               // +0x078 [V] `0x668b53e  mov [rsi+0x78],rcx` `0x668b547  mov [rsi+0x80],rcx` (from [r12]/[r12+8])
    uint8_t mByte88;               // +0x88 [V] `0x668b54e  mov [rsi+0x88],bpl`
    uint8_t mByte89;               // +0x89 [V] `0x668b55d  mov [rsi+0x89],cl`
    char pad8A[2];                 // +0x08A padding (no ctor store; gap before mParamD8 at +0x08C)
    float mParamD8[4];             // +0x08C [V] `0x668b572  movss [rsi+0x8c],xmm0` ... `0x668b599  movss [rsi+0x98],xmm0` (from [[r14+0xD8]+0x40])
    float mParamE0[2];             // +0x09C [V] `0x668b5b0  movss [rsi+0x9c],xmm0` `0x668b5bd  movss [rsi+0xa0],xmm0` (from [[r14+0xE0]+0x40])
    float mParamE8[4];             // +0x0A4 [V] `0x668b5d4  movss [rsi+0xa4],xmm0` ... `0x668b5fb  movss [rsi+0xb0],xmm0` (from [[r14+0xE8]+0x40])
    float mParam70[4];             // +0x0B4 [V] `0x668b60f  movss [rsi+0xb4],xmm0` ... `0x668b636  movss [rsi+0xc0],xmm0` (from [[r14+0x70]+0x40])
    float mParam78[2];             // +0x0C4 [V] `0x668b64a  movss [rsi+0xc4],xmm0` `0x668b657  movss [rsi+0xc8],xmm0` (from [[r14+0x78]+0x40])
    float mParam80;                // +0x0CC [V] `0x668b66e  movss [rsi+0xcc],xmm0` (from [[r14+0x80]+0x40])
    float mOverride[4];            // +0x0D0 [V] `0x668b687  movss [rsi+0xd0],xmm0` ... `0x668b6ae  movss [rsi+0xdc],xmm0` (from [rbx], conditional: gated by [rbx+0x10]==1)
    bool mHasOverride;             // +0x0E0 [V] `0x668b676  mov byte ptr [rsi+0xe0],0` `0x668b6b6  mov byte ptr [rsi+0xe0],1`
    char padE1[3];                 // +0x0E1 padding (no ctor store; gap before mFlags at +0x0E4)
    uint16_t mFlags;               // +0x0E4 [V] `0x668b6c0  mov [rsi+0xe4],ax` (word from [rax]=[rsp+0xC8])
};
static_assert(sizeof(RenderEnvironmentalTextDescription) == 0xE8);
static_assert(offsetof(RenderEnvironmentalTextDescription, mMatrix) == 0x18);
static_assert(offsetof(RenderEnvironmentalTextDescription, mText) == 0x78);
static_assert(offsetof(RenderEnvironmentalTextDescription, mParamD8) == 0x8C);
static_assert(offsetof(RenderEnvironmentalTextDescription, mParam80) == 0xCC);
static_assert(offsetof(RenderEnvironmentalTextDescription, mHasOverride) == 0xE0);
static_assert(offsetof(RenderEnvironmentalTextDescription, mFlags) == 0xE4);

} // namespace mce::framebuilder
