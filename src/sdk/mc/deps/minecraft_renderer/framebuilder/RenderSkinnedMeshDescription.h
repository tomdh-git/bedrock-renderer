#pragma once
// RenderSkinnedMeshDescription (Item group tag 7), built by the 21-argument constructor 0x668d350
// (docs/progress/skinned_ctor_668d350.txt, docs/functions/668d350.md). Every field below is written by that constructor [V].
// Size 0x1D0 [I] (aligned end, from Descriptions.h; ctor writes up to +0x1CE then 2 tail pad bytes).


namespace mce::framebuilder {

// Reference-counted pointer as the game stores it: object ptr + control block (strong count at ctrl+8).
struct SharedRef {
    void* mPtr;
    void* mCtrl;
};
static_assert(sizeof(SharedRef) == 0x10);

struct RenderSkinnedMeshDescription {
    float mMatrixA[16];              // +0x000 [V] `0x668d386  movss [rcx],xmm0` ... `0x668d41b  movss [rcx+0x3c],xmm0` (from rdx)
    float mMatrixB[16];              // +0x040 [V] `0x668d425  movss [rcx+0x40],xmm0` ... `0x668d4ca  movss [rcx+0x7c],xmm0` (from r8)
    float mBounds[6];                // +0x080 [V] `0x668d4e2  movss [rcx+0x80],xmm0` ... `0x668d528  movss [rcx+0x94],xmm0` (from r9, conditional: gated by [r9+0x18]!=0xFF)
    uint8_t mBoundsEmpty;            // +0x098 [V] `0x668d4cf  mov byte ptr [rcx+0x98],0xFF` `0x668d530  mov byte ptr [rcx+0x98],0` (conditional override)
    char pad099[3];                  // +0x099 padding (no ctor store; gap before mMeshVec4 at +0x09C)
    float mMeshVec4[4];              // +0x09C [V] `0x668d53f  movss [rcx+0x9c],xmm0` ... `0x668d56f  movss [rcx+0xa8],xmm0` (from [rdi+0x190..0x19C])
    char pad0AC[4];                  // +0x0AC padding (no ctor store; gap before mMesh at +0x0B0)
    const void* mMesh;               // +0x0B0 [V] `0x668d577  mov [rcx+0xb0],rdi`
    uint32_t mValueB8;               // +0x0B8 [V] `0x668d57e  mov [rcx+0xb8],esi`
    float mBlockC0[4];               // +0x0C0 [V] `0x668d588  movups [rcx+0xc0],xmm0` (from [r11])
    float mBlockD0[4];               // +0x0D0 [V] `0x668d593  movups [rcx+0xd0],xmm0` (from [r10])
    SharedRef mRefE0;                // +0x0E0 [V] `0x668d5b4  mov [rcx+0xe0],rdx` `0x668d5bf  mov [rcx+0xe8],rdx` (from [rax]/[rax+8])
    SharedRef mRefF0;                // +0x0F0 [V] `0x668d5de  mov [rcx+0xf0],rdx` `0x668d5e9  mov [rcx+0xf8],rdx` (from [rax+0x10]/[rax+0x18])
    uint8_t mByte100;                // +0x100 [V] `0x668d5f4  mov [rcx+0x100],dl` (from [rax+0x20])
    SharedRef mRef108;               // +0x108 [V] `0x668d612  mov [rcx+0x108],rdx` `0x668d61d  mov [rcx+0x110],rdx` (from [rax+0x28]/[rax+0x30])
    uint8_t mByte118;                // +0x118 [V] `0x668d628  mov [rcx+0x118],dl` (from [rax+0x38])
    SharedRef mRef120;               // +0x120 [V] `0x668d64a  mov [rcx+0x120],rdx` `0x668d655  mov [rcx+0x128],rdx` (from [rax+0x40]/[rax+0x48])
    SharedRef mMaterial;             // +0x140 [V] `0x668d6dc  mov [rcx+0x140],rax` `0x668d6e7  mov [rcx+0x148],rax` (from [r8]/[r8+8])
    uint8_t mFlags150[4];            // +0x150 [V] `0x668d6ee  mov [rcx+0x150],dil` `0x668d702  mov [rcx+0x153],r10b` (four flag bytes)
    float mBlock154[4];              // +0x154 [V] `0x668d70d  movups [rcx+0x154],xmm0` (from [r11])
    float mBlock164[4];              // +0x164 [V] `0x668d718  movups [rcx+0x164],xmm0` (from [r9])
    uint32_t mValue174;              // +0x174 [V] `0x668d723  mov [rcx+0x174],eax` (from [r9+0x10])
    uint16_t mCount178;              // +0x178 [V] `0x668d73c  mov [rcx+0x178],dx` (checked < 0x10000, throws otherwise)
    char pad17A[6];                  // +0x17A padding (no ctor store; gap before mVariantHead at +0x180)
    uint8_t mVariantHead[0x10];      // +0x180 [V] `0x668d746  movups [rcx+0x180],xmm0` (from [rbx])
    uint8_t mVariantByte;            // +0x190 [V] `0x668d751  mov [rcx+0x190],al` (from [rbx+0x10])
    char pad191[7];                  // +0x191 padding (no ctor store; gap before mVariantPayload at +0x198)
    uint8_t mVariantPayload[0x18];   // +0x198 [V] `0x668d780  mov [rcx+0x198],rax` (kind 0: u64 from [rbx+0x18]; kind 1+: heap copy, 0x20 bytes) — remainder zeroed by `0x668d791  movups [rcx+0x1a0],xmm0`
    uint8_t mVariantIndex;           // +0x1B0 [V] `0x668d757  mov byte ptr [rcx+0x1b0],0xFF` (0xFF = empty; set to dil at `0x668d85e  mov [rcx+0x1b0],dil` for kind != 0)
    char pad1B1[7];                  // +0x1B1 padding (no ctor store; gap before mOverride at +0x1B8)
    float mOverride[4];              // +0x1B8 [V] `0x668d88d  movss [rcx+0x1b8],xmm0` ... `0x668d8b7  movss [rcx+0x1c4],xmm0` (from [r8], conditional: gated by [r8+0x10]==1)
    bool mHasOverride;               // +0x1C8 [V] `0x668d87a  mov byte ptr [rcx+0x1c8],0` `0x668d8bf  mov byte ptr [rcx+0x1c8],1` (conditional)
    char pad1C9[3];                  // +0x1C9 padding (no ctor store; gap before mFlags1CC at +0x1CC)
    uint16_t mFlags1CC;              // +0x1CC [V] `0x668d8c6  mov [rcx+0x1cc],dx` (from [rbp+0xB8])
    uint8_t mByte1CE;                // +0x1CE [V] `0x668d8cd  mov [rcx+0x1ce],al` (from [rbp+0xE0])
    char pad1CF;                     // +0x1CF padding (no ctor store; tail to reach 0x1D0)
};
static_assert(sizeof(RenderSkinnedMeshDescription) == 0x1D0);
static_assert(offsetof(RenderSkinnedMeshDescription, mBoundsEmpty) == 0x98);
static_assert(offsetof(RenderSkinnedMeshDescription, mMesh) == 0xB0);
static_assert(offsetof(RenderSkinnedMeshDescription, mRefE0) == 0xE0);
static_assert(offsetof(RenderSkinnedMeshDescription, mMaterial) == 0x140);
static_assert(offsetof(RenderSkinnedMeshDescription, mCount178) == 0x178);
static_assert(offsetof(RenderSkinnedMeshDescription, mVariantIndex) == 0x1B0);
static_assert(offsetof(RenderSkinnedMeshDescription, mHasOverride) == 0x1C8);
static_assert(offsetof(RenderSkinnedMeshDescription, mByte1CE) == 0x1CE);

} // namespace mce::framebuilder
