#pragma once
// RenderNametagDescription (Item group tag 1). Built in place by ctor 0x668b6e0
// (docs/data/listings/nametag_ctor_668b6e0_668b850.txt). Every field below is written by that constructor [V].
// Size 0x98 [V]: ctor writes up to +0x94 (mHasColor byte), plus 3 tail pad bytes = 0x98.


namespace mce::framebuilder {

// Reference-counted pointer as the game stores it: object ptr + control block (strong count at ctrl+8).
struct SharedRef {
    void* mPtr;
    void* mCtrl;
};
static_assert(sizeof(SharedRef) == 0x10);

struct RenderNametagDescription {
    void* mOwner;                    // +0x00 [V] `0x668b6fe  mov [rax],rdx`
    float mMatrix[16];               // +0x08 [V] `0x668b706  movss [rax+8],xmm0` ... `0x668b7ab  movss [rax+0x44],xmm0`
    float mPosition[3];              // +0x48 [V] `0x668b7b4  movss [rax+0x48],xmm0` ... `0x668b7c8  movss [rax+0x50],xmm0`
    char pad54[4];                   // +0x54 padding (no ctor store; gap before SharedRef at +0x58)
    SharedRef mShared;               // +0x58 [V] `0x668b7e4  mov [rax+0x58],rdx` `0x668b7ec  mov [rax+0x60],rdx`
    uint8_t mRaw68[0x10];            // +0x68 [V] `0x668b7f3  movups [rax+0x68],xmm0`
    uint64_t mCtx20;                 // +0x78 [V] `0x668b7f7  mov [rax+0x78],r11`
    uint16_t mFlags;                 // +0x80 [V] `0x668b7ff  mov [rax+0x80],dx`
    char pad82[2];                   // +0x82 padding (no ctor store; gap before mColor at +0x84)
    float mColor[4];                 // +0x84 [V] `0x668b817  movss [rax+0x84],xmm0` ... `0x668b83e  movss [rax+0x90],xmm0` (conditional, gated by [rcx+0x10]==1)
    bool mHasColor;                  // +0x94 [V] `0x668b806  mov byte ptr [rax+0x94],0` `0x668b846  mov byte ptr [rax+0x94],1`
    char pad95[3];                   // +0x95 padding (no ctor store; tail to reach 0x98)
};
static_assert(sizeof(RenderNametagDescription) == 0x98);
static_assert(offsetof(RenderNametagDescription, mOwner) == 0x00);
static_assert(offsetof(RenderNametagDescription, mMatrix) == 0x08);
static_assert(offsetof(RenderNametagDescription, mPosition) == 0x48);
static_assert(offsetof(RenderNametagDescription, mShared) == 0x58);
static_assert(offsetof(RenderNametagDescription, mRaw68) == 0x68);
static_assert(offsetof(RenderNametagDescription, mCtx20) == 0x78);
static_assert(offsetof(RenderNametagDescription, mFlags) == 0x80);
static_assert(offsetof(RenderNametagDescription, mColor) == 0x84);
static_assert(offsetof(RenderNametagDescription, mHasColor) == 0x94);

} // namespace mce::framebuilder
