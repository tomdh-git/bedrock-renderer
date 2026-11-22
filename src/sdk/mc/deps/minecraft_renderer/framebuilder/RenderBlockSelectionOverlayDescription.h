#pragma once
// RenderBlockSelectionOverlayDescription (Item group tag 8), built by ctor 0x668d990
// (docs/progress/blocksel_ctor_668d990.txt, docs/functions/668d990.md). Every field below is written by that constructor [V].
// Size 0xB8 [I] (aligned end, from Descriptions.h; ctor writes up to +0xB0 then 7 tail pad bytes).


namespace mce::framebuilder {

// Reference-counted pointer as the game stores it: object ptr + control block (strong count at ctrl+8).
struct SharedRef {
    void* mPtr;
    void* mCtrl;
};
static_assert(sizeof(SharedRef) == 0x10);

struct RenderBlockSelectionOverlayDescription {
    float mMatrix[16];             // +0x00 [V] `0x668d9ca  movss [rsi],xmm0` ... `0x668da5f  movss [rsi+0x3c],xmm0` (from rdx)
    const void* mMesh;             // +0x40 [V] `0x668da64  mov [rsi+0x40],r8`
    uint32_t mValue48;             // +0x48 [V] `0x668da68  mov [rsi+0x48],r9d`
    char pad4C[4];                 // +0x04C padding (no ctor store; gap before mBlock50 at +0x050)
    float mBlock50[4];             // +0x050 [V] `0x668da70  movups [rsi+0x50],xmm0` (from [r11])
    SharedRef mTexture;            // +0x060 [V] `0x668dbca  call 0x4DFB570` `0x668dbf0  mov [rsi+0x60],rcx` `0x668dbf8  mov [rsi+0x68],rax` (from 0x4DFB570 result)
    SharedRef mMaterial;           // +0x070 [V] `0x668da9f  mov [rsi+0x70],rdx` `0x668daa7  mov [rsi+0x78],rdx` (from [r10]/[r10+8])
    float mColor[4];               // +0x080 [V] `0x668dabe  movups [rsi+0x80],xmm0` (from [rcx]=[rbp+0x70])
    uint16_t mFlags;               // +0x090 [V] `0x668dab5  mov [rsi+0x90],ax` (word from [rbp+0x78])
    char pad92[6];                 // +0x092 padding (no ctor store; gap before mVariantPayload at +0x098)
    uint8_t mVariantPayload[0x18]; // +0x098 [V] `0x668daec  mov [rsi+0x98],rax` (kind 0: u64 from [rbx]) `0x668db19  mov [rax],rcx` (+0xA0 SharedRef ctrl from [rbx+8]) `0x668db1f  mov [rsi+0xa8],rax` (+0xA8 from [rbx+0x10]); kind 1+: heap copy via 0xF99FFA0 alloc
    uint8_t mVariantIndex;         // +0x0B0 [V] `0x668dac3  mov byte ptr [rsi+0xb0],0xff` `0x668dbb1  mov [rsi+0xb0],r14b`
    char padB1[7];                 // +0x0B1 padding (no ctor store; tail to reach 0xB8)
};
static_assert(sizeof(RenderBlockSelectionOverlayDescription) == 0xB8);
static_assert(offsetof(RenderBlockSelectionOverlayDescription, mMesh) == 0x40);
static_assert(offsetof(RenderBlockSelectionOverlayDescription, mTexture) == 0x60);
static_assert(offsetof(RenderBlockSelectionOverlayDescription, mColor) == 0x80);
static_assert(offsetof(RenderBlockSelectionOverlayDescription, mFlags) == 0x90);
static_assert(offsetof(RenderBlockSelectionOverlayDescription, mVariantIndex) == 0xB0);

} // namespace mce::framebuilder
