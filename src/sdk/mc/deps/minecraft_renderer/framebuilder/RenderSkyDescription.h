#pragma once
// RenderSkyDescription (inserted by the thin EndSky clone 0x53707a0 = Sky group tag 3): built by ctor 0x668c910
// (docs/progress/sky_ctor_668c910.txt, docs/functions/668c910.md). Every field below is written by that constructor [V].
// Size 0xB0 [I] (aligned end, from Descriptions.h; ctor writes up to +0xAC then 4 tail pad bytes).


namespace mce::framebuilder {

// Reference-counted pointer as the game stores it: object ptr + control block (strong count at ctrl+8).
struct SharedRef {
    void* mPtr;
    void* mCtrl;
};
static_assert(sizeof(SharedRef) == 0x10);

struct RenderSkyDescription {
    const void* mSource;           // +0x00 [V] `0x668c93b  mov [rcx],rax` (rax = [rdx], first qword of source)
    SharedRef mTexture;            // +0x08 [V] `0x668c9c5  call 0x4DFB570` (converts [rdx+0x40] chain or static default to SharedRef at [rcx+8])
    uint16_t mFlags;               // +0x18 [V] `0x668ca0f  mov [rsi+0x18],r12w` (word from [rbp+0x70])
    char pad1A[2];                 // +0x01A padding (no ctor store; gap before mColor at +0x01C)
    float mColor[4];               // +0x1C [V] `0x668ca17  movups [rsi+0x1c],xmm0` (from [rbx]=[r8])
    float mMatrix[16];             // +0x2C [V] `0x668ca1f  movss [rsi+0x2c],xmm0` ... `0x668cab5  movss [rsi+0x68],xmm0` (from [rdi+0x0..0x3C])
    float mUvTransform[16];        // +0x6C [V] `0x668cac5  movups [rsi+0x6c],xmm1` (elements 0-1 from [r15]) `0x668cb01  movss [rsi+0x78],xmm0` (element 3 from [r15+8]) `0x668cac9  movsd [rsi+0x7c],xmm0` (elements 4-5 from [r15+0xC]) `0x668cad1  movups [rsi+0x84],xmm0` (elements 6-9 zeroed) `0x668cad8  mov dword ptr [rsi+0x94],0x3F800000` (element 10 = 1.0f) `0x668cae2  movups [rsi+0x98],xmm0` (elements 11-14 zeroed) `0x668cae9  mov dword ptr [rsi+0xa8],0x3F800000` (element 15 = 1.0f) — builds a 4x4 from a 2x3 matrix: rows {a,b,0,c},{d,e,0,f},{0,0,1,0},{0,0,0,1}
    float mValueAC;                // +0xAC [V] `0x668caf3  movss [rsi+0xac],xmm6` (from [rbp+0x68])
};
static_assert(sizeof(RenderSkyDescription) == 0xB0);
static_assert(offsetof(RenderSkyDescription, mFlags) == 0x18);
static_assert(offsetof(RenderSkyDescription, mMatrix) == 0x2C);
static_assert(offsetof(RenderSkyDescription, mUvTransform) == 0x6C);

} // namespace mce::framebuilder
