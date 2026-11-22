#pragma once
// RenderMeshFallbackDescription (Item group tag 2), the generic mesh draw. Built by constructor 0x668b850
// (docs/data/listings/meshfallback_ctor_668b850_668be49.txt, docs/functions/668b850.md). Every field below is written by that constructor [V].
// Size 0x1D0 [V] (ctor writes up to +0x1CF, total 0x1D0).


namespace mce::framebuilder {

// Reference-counted pointer as the game stores it: object ptr + control block (strong count at ctrl+8).
struct SharedRef {
    void* mPtr;
    void* mCtrl;
};
static_assert(sizeof(SharedRef) == 0x10);

struct RenderMeshFallbackDescription {
    const void* mMesh;               // +0x000 [V] `0x668b8a3  mov [rsi],r8`
    char pad008[0x80];               // +0x008 padding (mTextures[8] filled by caller, not by this ctor)
    uint64_t mNumTextures;           // +0x088 [V] `0x668b8a6  mov qword ptr [rsi+0x88],0`
    float mMatrix[16];               // +0x090 [V] `0x668b8b6  movss [rsi+0x90],xmm0` ... `0x668b988  movss [rsi+0xcc],xmm0` (from r9)
    float mCameraPos[3];             // +0x0D0 [V] `0x668b995  movss [rsi+0xd0],xmm0` ... `0x668b9b1  movss [rsi+0xd8],xmm0` (from r15)
    uint8_t mFlagDC;                 // +0x0DC [V] `0x668b9b9  mov [rsi+0xdc],r14b`
    uint8_t mFlagDD;                 // +0x0DD [V] `0x668b9c0  mov [rsi+0xdd],dil`
    uint8_t mFlagDE;                 // +0x0DE [V] `0x668b9cc  mov [rsi+0xde],r9b`
    uint8_t mFlagDF;                 // +0x0DF [V] `0x668b9d3  mov [rsi+0xdf],bl`
    uint8_t mFlagE0;                 // +0x0E0 [V] `0x668b9d9  mov [rsi+0xe0],r11b`
    char padE1[3];                   // +0x0E1 padding (no ctor store; gap before mBlockE4 at +0x0E4)
    float mBlockE4[4];               // +0x0E4 [V] `0x668b9e8  movups [rsi+0xe4],xmm0` (from [rdx+0x20])
    float mBlockF4[4];               // +0x0F4 [V] `0x668b9f7  movups [rsi+0xf4],xmm0` (from [rdx+0x28])
    char pad104[4];                  // +0x104 padding (no ctor store; gap before mMaterial at +0x108)
    SharedRef mMaterial;             // +0x108 [V] `0x668ba27  mov [rsi+0x108],r11` `0x668ba32  mov [rsi+0x110],r10` (from [r10]/[r10+8])
    const void* mParams;             // +0x118 [V] `0x668ba39  mov [rsi+0x118],rcx`
    float mParam100[4];              // +0x120 [V] `0x668ba50  movss [rsi+0x120],xmm0` ... `0x668ba7a  movss [rsi+0x12c],xmm0` (from [[rcx+0x100]+0x40])
    float mParam150;                 // +0x130 [V] `0x668ba92  movss [rsi+0x130],xmm0` (from [[rcx+0x150]+0x40])
    float mContext6D;                // +0x134 [V] `0x668baa5  movss [rsi+0x134],xmm0` (float(int8) from [rdx+0x6D])
    float mParam70[4];               // +0x138 [V] `0x668bab9  movss [rsi+0x138],xmm0` ... `0x668bae0  movss [rsi+0x144],xmm0` (from [[rcx+0x70]+0x40])
    float mParam78[2];               // +0x148 [V] `0x668baf4  movss [rsi+0x148],xmm0` `0x668bb01  movss [rsi+0x14c],xmm0` (from [[rcx+0x78]+0x40])
    float mParam80;                  // +0x150 [V] `0x668bb18  movss [rsi+0x150],xmm0` (from [[rcx+0x80]+0x40])
    float mOverride[4];              // +0x154 [V] `0x668bb31  movss [rsi+0x154],xmm0` ... `0x668bb58  movss [rsi+0x160],xmm0` (from [rax], conditional: gated by [rax+0x10]==1)
    bool mHasOverride;               // +0x164 [V] `0x668bb20  mov byte ptr [rsi+0x164],0` `0x668bb60  mov byte ptr [rsi+0x164],1`
    char pad165[3];                  // +0x165 padding (no ctor store; gap before mFlags at +0x168)
    uint16_t mFlags;                 // +0x168 [V] `0x668bb7a  mov [rsi+0x168],ax` (word from [r9])
    char pad16A[6];                  // +0x16A padding (no ctor store; gap before mVariantHead at +0x170)
    uint8_t mVariantHead[0x10];      // +0x170 [V] `0x668bb84  movups [rsi+0x170],xmm0` (from [rbx])
    uint8_t mVariantByte;            // +0x180 [V] `0x668bb8f  mov [rsi+0x180],al` (from [rbx+0x10])
    uint8_t mVariantPayload[0x18];   // +0x188 [V] `0x668bbbf  mov [rsi+0x188],rax` `0x668bbec  mov [rax],rcx` `0x668bbf2  mov [rsi+0x198],rax` (kind-dependent variant copy; remainder zeroed by `0x668bbd0  movups [rsi+0x190],xmm0`)
    uint8_t mVariantIndex;           // +0x1A0 [V] `0x668bb95  mov byte ptr [rsi+0x1a0],0xff` `0x668bca4  mov [rsi+0x1a0],r14b`
    float mBounds[6];                // +0x1A8 [V] `0x668bcba  movss [rsi+0x1a8],xmm0` ... `0x668bcfb  movss [rsi+0x1bc],xmm0` (from [rcx]=[rbp+0x68])
    float mMeshVec4[4];              // +0x1C0 [V] `0x668bd0c  movss [rsi+0x1c0],xmm0` ... `0x668bd3f  movss [rsi+0x1cc],xmm0` (from [r8+0x190..0x19C])
};
static_assert(sizeof(RenderMeshFallbackDescription) == 0x1D0);
static_assert(offsetof(RenderMeshFallbackDescription, mNumTextures) == 0x88);
static_assert(offsetof(RenderMeshFallbackDescription, mMatrix) == 0x90);
static_assert(offsetof(RenderMeshFallbackDescription, mFlagDC) == 0xDC);
static_assert(offsetof(RenderMeshFallbackDescription, mBlockE4) == 0xE4);
static_assert(offsetof(RenderMeshFallbackDescription, mMaterial) == 0x108);
static_assert(offsetof(RenderMeshFallbackDescription, mParams) == 0x118);
static_assert(offsetof(RenderMeshFallbackDescription, mParam80) == 0x150);
static_assert(offsetof(RenderMeshFallbackDescription, mHasOverride) == 0x164);
static_assert(offsetof(RenderMeshFallbackDescription, mFlags) == 0x168);
static_assert(offsetof(RenderMeshFallbackDescription, mVariantHead) == 0x170);
static_assert(offsetof(RenderMeshFallbackDescription, mVariantIndex) == 0x1A0);
static_assert(offsetof(RenderMeshFallbackDescription, mBounds) == 0x1A8);
static_assert(offsetof(RenderMeshFallbackDescription, mMeshVec4) == 0x1C0);

} // namespace mce::framebuilder
