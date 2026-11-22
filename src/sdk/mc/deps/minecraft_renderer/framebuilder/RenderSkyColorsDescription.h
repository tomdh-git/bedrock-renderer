#pragma once
// RenderSkyColorsDescription (Sky group tag 5), built by the SkyColors clone 0x5369b30.
// Size 0x70 [I] (aligned end of the 0x70-byte stack object; ctor/clone writes up to +0x69 then pad to 0x70).
// Field-level [V] marks an offset touched by a verified store/load in the clone; [I] = inferred from the
// clone write range, not individually confirmed. Evidence RVAs verified verbatim against the exe with rdis.

namespace mce::framebuilder {

struct RenderSkyColorsDescription {
    const void* mMesh;                // +0x00 [V] `0x536a146  mov rcx,[r15]` (clone loads mesh ptr)
    float mSkyColor[2];               // +0x08 [V] `0x536a150  movlps [rbp+0xF8],xmm8` (8-byte store)
    uint8_t mPad10[8];                // +0x10 padding (gap before FogColor at +0x18)
    float mFogColor[4];               // +0x18 [V] `0x536a16d  movups [rbp+0x108],xmm0` (movups, 16 B); visitor addr calc `0x536a132  lea rax,[rdi+0x18]`
    float mMatrix[4];                 // +0x28 [V] first elem `0x536a180  movss xmm0,[rax]` ... `0x536a247  movss [rbp+0x154],xmm0` (matrix block +0x28..+0x37, range-confirmed)
    uint8_t mPad38[0x30];             // +0x38 padding (no store in +0x38..+0x67)
    uint16_t mFlags;                  // +0x68 [V] `0x536a25a  mov [rbp+0x158],ax` (ax store, 2 B); byte loaded `0x536a256  movzx eax,byte ptr [rax+0x74]`
    uint8_t mPad6A[6];                // +0x6A padding (tail to reach 0x70)
};
static_assert(sizeof(RenderSkyColorsDescription) == 0x70);
static_assert(offsetof(RenderSkyColorsDescription, mMesh) == 0x00);
static_assert(offsetof(RenderSkyColorsDescription, mFogColor) == 0x18);
static_assert(offsetof(RenderSkyColorsDescription, mFlags) == 0x68);

} // namespace mce::framebuilder
