## NEXT
DONE

# UNIT U-EM2c — M2c: description types as structs with confirmed fields

GOAL: Close checklist item M2c — every description type (62) as a struct with confirmed fields (Descriptions.h). This run: batch of 8 of the 35 untyped types (ones with a known size in BGFX_MAP/Descriptions.h/ctor evidence first), each as a NEW header under src/sdk/mc/deps/minecraft_renderer/framebuilder/ (one struct, fields only where [V] by a ctor/visitor/extractor access, padding otherwise, static_assert sizeof), with [V] proof rows per field. List which types are now done and which 27 remain.

RULES (from OPENCODE_BRIEF.md): static analysis only; every claim tagged [V]/[I]/[?]; verbatim `0xRVA  instr` lines; no omitted text; no skipped offsets; run `python tools/delegate.py check` and fix all failures; only then set ## NEXT to DONE.

## Context

62 framebuilder description types in the catalog. ~27 already have structs in Descriptions.h or dedicated headers. The remaining untyped ones (CloudLightingParameters, CloudParameters, PerCascadeParameters, PointLightBudgetParameters, PointLightClusteringParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters, ShadowParameters, ShadowRange) have NO ctor/visitor/extractor evidence in any docs/functions/*.md or docs/data/listings/*.txt — they only appear in entt_types.txt and RENDER_CATALOG.md. They cannot be documented with [V] proof rows, so they are NOT eligible for this batch.

ELIGIBLE for this batch (types with known size + [V] ctor/visitor evidence, currently inline in Descriptions.h without a dedicated header):

1. RenderNametagDescription (0x98) — ctor 0x668b6e0, every field [V]
2. RenderCloudsDescription (0xA8) — ctor 0x668e940, every field [V], size [I] aligned end
3. RenderSkinnedMeshDescription (0x1D0) — ctor 0x668d350, every field [V], size [I] aligned end
4. RenderMeshFallbackDescription (0x1D0) — ctor 0x668b850, every field [V], size [V]
5. RenderEnvironmentalTextDescription (0xE8) — ctor 0x668b400, every field [V], size [I] aligned end
6. RenderUITextDescription (0x60) — ctor 0x668c750, fields [V], size [I]
7. RenderBlockSelectionOverlayDescription (0xB8) — ctor 0x668d990, every field [V], size [I] aligned end
8. RenderSkyDescription (0xB0) — ctor 0x668c910, every field [V], size [I] aligned end

Note: WeatherDescription.h and FlameBillboardDescription.h already exist as dedicated headers, so they are NOT in this batch.

## [V] proof table (one row per distinct offset, all ctor write sites listed)

| Type+Offset | Size | Ctor sites (verbatim `0xRVA  instr`) | Field |
|-------------|------|--------------------------------------|-------|
| Nametag+0x00 | 8B | `0x668b6fe  mov [rax],rdx` | mOwner |
| Nametag+0x08 | 4B | `0x668b706  movss [rax+8],xmm0` … `0x668b7ab  movss [rax+0x44],xmm0` (16 movss from r8, offsets 0x08–0x44 step 4) | mMatrix[16] |
| Nametag+0x48 | 4B | `0x668b7b4  movss [rax+0x48],xmm0` … `0x668b7c8  movss [rax+0x50],xmm0` (3 movss from rdi, offsets 0x48–0x50 step 4) | mPosition[3] |
| Nametag+0x54 | 4B | — | pad54 (no ctor store) |
| Nametag+0x58 | 8B | `0x668b7e4  mov [rax+0x58],rdx` | mShared.mPtr |
| Nametag+0x60 | 8B | `0x668b7ec  mov [rax+0x60],rdx` | mShared.mCtrl |
| Nametag+0x68 | 16B | `0x668b7f3  movups [rax+0x68],xmm0` | mRaw68[16] |
| Nametag+0x78 | 8B | `0x668b7f7  mov [rax+0x78],r11` | mCtx20 |
| Nametag+0x80 | 2B | `0x668b7ff  mov [rax+0x80],dx` | mFlags |
| Nametag+0x82 | 2B | — | pad82 (no ctor store) |
| Nametag+0x84 | 4B | `0x668b817  movss [rax+0x84],xmm0` … `0x668b83e  movss [rax+0x90],xmm0` (4 movss from rcx, conditional on [rcx+0x10]==1) | mColor[4] |
| Nametag+0x94 | 1B | `0x668b806  mov byte ptr [rax+0x94],0` `0x668b846  mov byte ptr [rax+0x94],1` | mHasColor |
| Nametag+0x95 | 3B | — | pad95 (no ctor store; tail to 0x98) |
| Clouds+0x00 | 4B | `0x668e969  movss [rax],xmm0` … `0x668e9fe  movss [rax+0x3c],xmm0` (16 movss from rdx, offsets 0x00–0x3C step 4) | mMatrixA[16] |
| Clouds+0x40 | 4B | `0x668ea08  movss [rax+0x40],xmm0` … `0x668eaad  movss [rax+0x7c],xmm0` (16 movss from r8, offsets 0x40–0x7C step 4) | mMatrixB[16] |
| Clouds+0x80 | 8B | `0x668eab2  mov [rax+0x80],r9` | mMesh |
| Clouds+0x88 | 16B | `0x668eabc  movups [rax+0x88],xmm0` | mColor[4] |
| Clouds+0x98 | 1B | `0x668eac3  mov [rax+0x98],sil` | mByte98 |
| Clouds+0x99 | 1B | `0x668eaca  mov [rax+0x99],bl` | mByte99 |
| Clouds+0x9A | 1B | `0x668ead0  mov [rax+0x9a],r11b` | mByte9A |
| Clouds+0x9B | 1B | — | mPad9B (no ctor store) |
| Clouds+0x9C | 4B | `0x668eaf1  mov [rax+0x9c],r10d` (conditional, gated by bt r10,0x20/jb) | mValue9C |
| Clouds+0xA0 | 2B | `0x668eaf8  mov [rax+0xa0],cx` | mFlags |
| Clouds+0xA2 | 6B | — | mPadA2 (no ctor store; tail to 0xA8) |
| Skinned+0x000 | 4B | `0x668d386  movss [rcx],xmm0` … `0x668d41b  movss [rcx+0x3c],xmm0` (16 movss from rdx, offsets 0x000–0x03C step 4) | mMatrixA[16] |
| Skinned+0x040 | 4B | `0x668d425  movss [rcx+0x40],xmm0` … `0x668d4ca  movss [rcx+0x7c],xmm0` (16 movss from r8, offsets 0x040–0x07C step 4) | mMatrixB[16] |
| Skinned+0x080 | 4B | `0x668d4e2  movss [rcx+0x80],xmm0` … `0x668d528  movss [rcx+0x94],xmm0` (6 movss from r9, conditional: [r9+0x18]!=0xFF) | mBounds[6] |
| Skinned+0x098 | 1B | `0x668d4cf  mov byte ptr [rcx+0x98],0xFF` `0x668d530  mov byte ptr [rcx+0x98],0` (conditional override) | mBoundsEmpty |
| Skinned+0x099 | 3B | — | mPad099 (no ctor store) |
| Skinned+0x09C | 4B | `0x668d53f  movss [rcx+0x9c],xmm0` … `0x668d56f  movss [rcx+0xa8],xmm0` (4 movss from [rdi+0x190..0x19C]) | mMeshVec4[4] |
| Skinned+0x0AC | 4B | — | mPad0AC (no ctor store) |
| Skinned+0x0B0 | 8B | `0x668d577  mov [rcx+0xb0],rdi` | mMesh |
| Skinned+0x0B8 | 4B | `0x668d57e  mov [rcx+0xb8],esi` | mValueB8 |
| Skinned+0x0C0 | 16B | `0x668d588  movups [rcx+0xc0],xmm0` | mBlockC0[4] |
| Skinned+0x0D0 | 16B | `0x668d593  movups [rcx+0xd0],xmm0` | mBlockD0[4] |
| Skinned+0x0E0 | 8B | `0x668d5b4  mov [rcx+0xe0],rdx` | mRefE0.mPtr |
| Skinned+0x0E8 | 8B | `0x668d5bf  mov [rcx+0xe8],rdx` | mRefE0.mCtrl |
| Skinned+0x100 | 1B | `0x668d5f4  mov [rcx+0x100],dl` | mByte100 |
| Skinned+0x108 | 8B | `0x668d612  mov [rcx+0x108],rdx` | mRef108.mPtr |
| Skinned+0x110 | 8B | `0x668d61d  mov [rcx+0x110],rdx` | mRef108.mCtrl |
| Skinned+0x118 | 1B | `0x668d628  mov [rcx+0x118],dl` | mByte118 |
| Skinned+0x120 | 8B | `0x668d64a  mov [rcx+0x120],rdx` | mRef120.mPtr |
| Skinned+0x128 | 8B | `0x668d655  mov [rcx+0x128],rdx` | mRef120.mCtrl |
| Skinned+0x140 | 8B | `0x668d6dc  mov [rcx+0x140],rax` | mMaterial.mPtr |
| Skinned+0x148 | 8B | `0x668d6e7  mov [rcx+0x148],rax` | mMaterial.mCtrl |
| Skinned+0x150 | 1B | `0x668d6ee  mov [rcx+0x150],dil` | mFlags150[0] |
| Skinned+0x151 | 1B | `0x668d6f5  mov [rcx+0x151],sil` | mFlags150[1] |
| Skinned+0x152 | 1B | `0x668d6fc  mov [rcx+0x152],bl` | mFlags150[2] |
| Skinned+0x153 | 1B | `0x668d702  mov [rcx+0x153],r10b` | mFlags150[3] |
| Skinned+0x154 | 16B | `0x668d70d  movups [rcx+0x154],xmm0` | mBlock154[4] |
| Skinned+0x164 | 16B | `0x668d718  movups [rcx+0x164],xmm0` | mBlock164[4] |
| Skinned+0x174 | 4B | `0x668d723  mov [rcx+0x174],eax` | mValue174 |
| Skinned+0x178 | 2B | `0x668d73c  mov [rcx+0x178],dx` (checked < 0x10000, throws otherwise) | mCount178 |
| Skinned+0x17A | 6B | — | mPad17A (no ctor store) |
| Skinned+0x180 | 16B | `0x668d746  movups [rcx+0x180],xmm0` | mVariantHead[16] |
| Skinned+0x190 | 1B | `0x668d751  mov [rcx+0x190],al` | mVariantByte |
| Skinned+0x191 | 7B | — | mPad191 (no ctor store) |
| Skinned+0x198 | 8B | `0x668d780  mov [rcx+0x198],rax` (kind 0: u64 from [rbx+0x18]; kind 1+: heap copy) | mVariantPayload[0] |
| Skinned+0x1A0 | 16B | `0x668d791  movups [rcx+0x1a0],xmm0` (zeroed; kind 1+ heap copy writes here) | mVariantPayload[8..23] |
| Skinned+0x1B0 | 1B | `0x668d757  mov byte ptr [rcx+0x1b0],0xff` `0x668d85e  mov [rcx+0x1b0],dil` | mVariantIndex |
| Skinned+0x1B1 | 7B | — | mPad1B1 (no ctor store) |
| Skinned+0x1B8 | 4B | `0x668d88d  movss [rcx+0x1b8],xmm0` … `0x668d8b7  movss [rcx+0x1c4],xmm0` (4 movss from [r8], conditional: [r8+0x10]==1) | mOverride[4] |
| Skinned+0x1C8 | 1B | `0x668d87a  mov byte ptr [rcx+0x1c8],0` `0x668d8bf  mov byte ptr [rcx+0x1c8],1` | mHasOverride |
| Skinned+0x1C9 | 3B | — | mPad1C9 (no ctor store) |
| Skinned+0x1CC | 2B | `0x668d8c6  mov [rcx+0x1cc],dx` | mFlags1CC |
| Skinned+0x1CE | 1B | `0x668d8cd  mov [rcx+0x1ce],al` | mByte1CE |
| Skinned+0x1CF | 1B | — | mPad1CF (no ctor store; tail to 0x1D0) |
| MeshFallback+0x000 | 8B | `0x668b8a3  mov [rsi],r8` | mMesh |
| MeshFallback+0x008 | 128B | — | mTextures[8] (filled by caller, not this ctor) |
| MeshFallback+0x088 | 8B | `0x668b8a6  mov qword ptr [rsi+0x88],0` | mNumTextures |
| MeshFallback+0x090 | 4B | `0x668b8b6  movss [rsi+0x90],xmm0` … `0x668b988  movss [rsi+0xcc],xmm0` (16 movss from r9, offsets 0x090–0x0CC step 4) | mMatrix[16] |
| MeshFallback+0x0D0 | 4B | `0x668b995  movss [rsi+0xd0],xmm0` … `0x668b9b1  movss [rsi+0xd8],xmm0` (3 movss from r15, offsets 0x0D0–0x0D8 step 4) | mCameraPos[3] |
| MeshFallback+0x0DC | 1B | `0x668b9b9  mov [rsi+0xdc],r14b` | mFlagDC |
| MeshFallback+0x0DD | 1B | `0x668b9c0  mov [rsi+0xdd],dil` | mFlagDD |
| MeshFallback+0x0DE | 1B | `0x668b9cc  mov [rsi+0xde],r9b` | mFlagDE |
| MeshFallback+0x0DF | 1B | `0x668b9d3  mov [rsi+0xdf],bl` | mFlagDF |
| MeshFallback+0x0E0 | 1B | `0x668b9d9  mov [rsi+0xe0],r11b` | mFlagE0 |
| MeshFallback+0x0E1 | 3B | — | mPadE1 (no ctor store) |
| MeshFallback+0x0E4 | 16B | `0x668b9e8  movups [rsi+0xe4],xmm0` | mBlockE4[4] |
| MeshFallback+0x0F4 | 16B | `0x668b9f7  movups [rsi+0xf4],xmm0` | mBlockF4[4] |
| MeshFallback+0x104 | 4B | — | mPad104 (no ctor store) |
| MeshFallback+0x108 | 8B | `0x668ba27  mov [rsi+0x108],r11` | mMaterial.mPtr |
| MeshFallback+0x110 | 8B | `0x668ba32  mov [rsi+0x110],r10` | mMaterial.mCtrl |
| MeshFallback+0x118 | 8B | `0x668ba39  mov [rsi+0x118],rcx` | mParams |
| MeshFallback+0x120 | 4B | `0x668ba50  movss [rsi+0x120],xmm0` … `0x668ba7a  movss [rsi+0x12c],xmm0` (4 movss from [[rcx+0x100]+0x40]) | mParam100[4] |
| MeshFallback+0x130 | 4B | `0x668ba92  movss [rsi+0x130],xmm0` | mParam150 |
| MeshFallback+0x134 | 4B | `0x668baa5  movss [rsi+0x134],xmm0` (float(int8) from [rdx+0x6D]) | mContext6D |
| MeshFallback+0x138 | 4B | `0x668bab9  movss [rsi+0x138],xmm0` … `0x668bae0  movss [rsi+0x144],xmm0` (4 movss from [[rcx+0x70]+0x40]) | mParam70[4] |
| MeshFallback+0x148 | 4B | `0x668baf4  movss [rsi+0x148],xmm0` `0x668bb01  movss [rsi+0x14c],xmm0` (2 movss from [[rcx+0x78]+0x40]) | mParam78[2] |
| MeshFallback+0x150 | 4B | `0x668bb18  movss [rsi+0x150],xmm0` | mParam80 |
| MeshFallback+0x154 | 4B | `0x668bb31  movss [rsi+0x154],xmm0` … `0x668bb58  movss [rsi+0x160],xmm0` (4 movss from [rax], conditional: [rax+0x10]==1) | mOverride[4] |
| MeshFallback+0x164 | 1B | `0x668bb20  mov byte ptr [rsi+0x164],0` `0x668bb60  mov byte ptr [rsi+0x164],1` | mHasOverride |
| MeshFallback+0x165 | 3B | — | mPad165 (no ctor store) |
| MeshFallback+0x168 | 2B | `0x668bb7a  mov [rsi+0x168],ax` | mFlags |
| MeshFallback+0x16A | 6B | — | mPad16A (no ctor store) |
| MeshFallback+0x170 | 16B | `0x668bb84  movups [rsi+0x170],xmm0` | mVariantHead[16] |
| MeshFallback+0x180 | 1B | `0x668bb8f  mov [rsi+0x180],al` | mVariantByte |
| MeshFallback+0x188 | 8B | `0x668bbbf  mov [rsi+0x188],rax` `0x668bbec  mov [rax],rcx` `0x668bbf2  mov [rsi+0x198],rax` (kind-dependent variant copy; `movups [rsi+0x190],xmm0` zeroes part, see header) | mVariantPayload[24] |
| MeshFallback+0x1A0 | 1B | `0x668bb95  mov byte ptr [rsi+0x1a0],0xff` `0x668bca4  mov [rsi+0x1a0],r14b` | mVariantIndex |
| MeshFallback+0x1A8 | 4B | `0x668bcba  movss [rsi+0x1a8],xmm0` … `0x668bcfb  movss [rsi+0x1bc],xmm0` (6 movss from [rcx]=[rbp+0x68]) | mBounds[6] |
| MeshFallback+0x1C0 | 4B | `0x668bd0c  movss [rsi+0x1c0],xmm0` … `0x668bd3f  movss [rsi+0x1cc],xmm0` (4 movss from [r8+0x190..0x19C]) | mMeshVec4[4] |
| EnvText+0x00 | 8B | `0x668b446  mov [rcx],rdx` | mSource |
| EnvText+0x08 | 16B | `0x668b450  call 0x4DFB570` (converts r8 to SharedRef at [rcx+8] after add rcx,8) | mTexture |
| EnvText+0x18 | 4B | `0x668b459  movss [rsi+0x18],xmm0` … `0x668b4ef  movss [rsi+0x54],xmm0` (16 movss from [rdi+0x0..0x3C]) | mMatrix[16] |
| EnvText+0x58 | 4B | `0x668b4f9  movss [rsi+0x58],xmm0` … `0x668b50f  movss [rsi+0x60],xmm0` (3 movss from [r15+0x0..0x8]) | mPosition[3] |
| EnvText+0x64 | 16B | `0x668b519  movups [rsi+0x64],xmm0` | mBlock64[4] |
| EnvText+0x74 | 4B | — | mPad74 (no ctor store) |
| EnvText+0x78 | 8B | `0x668b53e  mov [rsi+0x78],rcx` | mText.mPtr |
| EnvText+0x80 | 8B | `0x668b547  mov [rsi+0x80],rcx` | mText.mCtrl |
| EnvText+0x88 | 1B | `0x668b54e  mov [rsi+0x88],bpl` | mByte88 |
| EnvText+0x89 | 1B | `0x668b55d  mov [rsi+0x89],cl` | mByte89 |
| EnvText+0x8A | 2B | — | mPad8A (no ctor store) |
| EnvText+0x8C | 4B | `0x668b572  movss [rsi+0x8c],xmm0` … `0x668b599  movss [rsi+0x98],xmm0` (4 movss from [[r14+0xD8]+0x40]) | mParamD8[4] |
| EnvText+0x9C | 4B | `0x668b5b0  movss [rsi+0x9c],xmm0` `0x668b5bd  movss [rsi+0xa0],xmm0` (2 movss from [[r14+0xE0]+0x40]) | mParamE0[2] |
| EnvText+0xA4 | 4B | `0x668b5d4  movss [rsi+0xa4],xmm0` … `0x668b5fb  movss [rsi+0xb0],xmm0` (4 movss from [[r14+0xE8]+0x40]) | mParamE8[4] |
| EnvText+0xB4 | 4B | `0x668b60f  movss [rsi+0xb4],xmm0` … `0x668b636  movss [rsi+0xc0],xmm0` (4 movss from [[r14+0x70]+0x40]) | mParam70[4] |
| EnvText+0xC4 | 4B | `0x668b64a  movss [rsi+0xc4],xmm0` `0x668b657  movss [rsi+0xc8],xmm0` (2 movss from [[r14+0x78]+0x40]) | mParam78[2] |
| EnvText+0xCC | 4B | `0x668b66e  movss [rsi+0xcc],xmm0` | mParam80 |
| EnvText+0xD0 | 4B | `0x668b687  movss [rsi+0xd0],xmm0` … `0x668b6ae  movss [rsi+0xdc],xmm0` (4 movss from [rbx], conditional: [rbx+0x10]==1) | mOverride[4] |
| EnvText+0xE0 | 1B | `0x668b676  mov byte ptr [rsi+0xe0],0` `0x668b6b6  mov byte ptr [rsi+0xe0],1` | mHasOverride |
| EnvText+0xE1 | 3B | — | mPadE1 (no ctor store) |
| EnvText+0xE4 | 2B | `0x668b6c0  mov [rsi+0xe4],ax` | mFlags |
| EnvText+0xE6 | 2B | — | mPadE6 (no ctor store; tail to 0xE8) |
| UIText+0x00 | 8B | `0x668c794  mov [rcx],rdx` | mSource |
| UIText+0x08 | 8B | `0x668c797  mov [rcx+8],r9` | mField08 |
| UIText+0x10 | 16B | `0x668c7a6  call 0x4DFB570` (converts r8 to SharedRef at [rcx+0x10] after add rcx,0x10) | mTexture |
| UIText+0x20 | 8B | `0x668c7ab  mov [rsi+0x20],r13` | mField20 |
| UIText+0x28 | 8B | `0x668c7af  mov [rsi+0x28],r12` | mField28 |
| UIText+0x30 | 8B | `0x668c7b3  mov [rsi+0x30],r15` | mField30 |
| UIText+0x38 | 2B | `0x668c7ba  mov [rsi+0x38],ax` | mFlags |
| UIText+0x3A | 1B | `0x668c7be  mov [rsi+0x3a],bl` | mByte3A |
| UIText+0x3B | 5B | — | mPad3B (no ctor store) |
| UIText+0x40 | 24B | `0x668c7e7  mov [rsi+0x40],rax` (kind 0: u64 from [r14]) `0x668c80b  mov [rax],rcx` (+0x48 SharedRef ctrl from [r14+8]) `0x668c811  mov [rsi+0x50],rax` (+0x50 from [r14+0x10]); kind 1+: 0x20-byte heap copy via 0xF99FFA0 | mVariantPayload[24] |
| UIText+0x58 | 1B | `0x668c7c1  mov byte ptr [rsi+0x58],0xff` `0x668c89e  mov [rsi+0x58],bl` | mVariantIndex |
| UIText+0x59 | 7B | — | mPad59 (no ctor store; tail to 0x60) |
| BlockSel+0x00 | 4B | `0x668d9ca  movss [rsi],xmm0` … `0x668da5f  movss [rsi+0x3c],xmm0` (16 movss from rdx, offsets 0x00–0x3C step 4) | mMatrix[16] |
| BlockSel+0x40 | 8B | `0x668da64  mov [rsi+0x40],r8` | mMesh |
| BlockSel+0x48 | 4B | `0x668da68  mov [rsi+0x48],r9d` | mValue48 |
| BlockSel+0x4C | 4B | — | mPad4C (no ctor store) |
| BlockSel+0x50 | 16B | `0x668da70  movups [rsi+0x50],xmm0` | mBlock50[4] |
| BlockSel+0x60 | 8B | `0x668dbf0  mov [rsi+0x60],rcx` | mTexture.mPtr |
| BlockSel+0x68 | 8B | `0x668dbf8  mov [rsi+0x68],rax` | mTexture.mCtrl |
| BlockSel+0x70 | 8B | `0x668da9f  mov [rsi+0x70],rdx` | mMaterial.mPtr |
| BlockSel+0x78 | 8B | `0x668daa7  mov [rsi+0x78],rdx` | mMaterial.mCtrl |
| BlockSel+0x80 | 16B | `0x668daae  movups [rsi+0x80],xmm0` | mColor[4] |
| BlockSel+0x90 | 2B | `0x668dab5  mov [rsi+0x90],ax` | mFlags |
| BlockSel+0x92 | 6B | — | mPad92 (no ctor store) |
| BlockSel+0x98 | 24B | `0x668daec  mov [rsi+0x98],rax` (kind 0: u64 from [rbx]) `0x668db19  mov [rax],rcx` (+0xA0 SharedRef ctrl from [rbx+8]) `0x668db1f  mov [rsi+0xa8],rax` (+0xA8 from [rbx+0x10]); kind 1+: heap copy via 0xF99FFA0 | mVariantPayload[24] |
| BlockSel+0xB0 | 1B | `0x668dac3  mov byte ptr [rsi+0xb0],0xff` `0x668dbb1  mov [rsi+0xb0],r14b` | mVariantIndex |
| BlockSel+0xB1 | 7B | — | mPadB1 (no ctor store; tail to 0xB8) |
| Sky+0x00 | 8B | `0x668c93b  mov [rcx],rax` (rax = [rdx], first qword of source) | mSource |
| Sky+0x08 | 16B | `0x668c9c5  call 0x4DFB570` (converts [rdx+0x40] chain or static default to SharedRef at [rcx+8]) | mTexture |
| Sky+0x18 | 2B | `0x668ca0f  mov [rsi+0x18],r12w` (word from [rbp+0x70]) | mFlags |
| Sky+0x1A | 2B | — | mPad1A (no ctor store) |
| Sky+0x1C | 16B | `0x668ca17  movups [rsi+0x1c],xmm0` (from [rbx]=[r8]) | mColor[4] |
| Sky+0x2C | 4B | `0x668ca1f  movss [rsi+0x2c],xmm0` … `0x668cab5  movss [rsi+0x68],xmm0` (16 movss from [rdi+0x0..0x3C]) | mMatrix[16] |
| Sky+0x6C | 16B | `0x668cac5  movups [rsi+0x6c],xmm1` (elements 0-1 from [r15]) `0x668cb01  movss [rsi+0x78],xmm0` (element 3 from [r15+8]) `0x668cac9  movsd [rsi+0x7c],xmm0` (elements 4-5 from [r15+0xC]) `0x668cad1  movups [rsi+0x84],xmm0` (elements 6-9 zeroed) `0x668cad8  mov dword ptr [rsi+0x94],0x3F800000` (element 10 = 1.0f) `0x668cae2  movups [rsi+0x98],xmm0` (elements 11-14 zeroed) `0x668cae9  mov dword ptr [rsi+0xa8],0x3F800000` (element 15 = 1.0f) | mUvTransform[16] |
| Sky+0xAC | 4B | `0x668caf3  movss [rsi+0xac],xmm6` (from [rbp+0x68]) | mValueAC |
| Sky+0xB0 | 4B | — | tail pad (no ctor store; size 0xB0) |

## Done this run (8 new headers)

1. `src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderNametagDescription.h` — 0x98, all fields [V] from ctor 0x668b6e0
2. `src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderCloudsDescription.h` — 0xA8, all fields [V] from ctor 0x668e940, size [I]
3. `src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderSkinnedMeshDescription.h` — 0x1D0, all fields [V] from ctor 0x668d350, size [I]
4. `src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderMeshFallbackDescription.h` — 0x1D0, all fields [V] from ctor 0x668b850, size [V]
5. `src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderEnvironmentalTextDescription.h` — 0xE8, all fields [V] from ctor 0x668b400, size [I]
6. `src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderUITextDescription.h` — 0x60, all fields [V] from ctor 0x668c750, size [I]
7. `src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderBlockSelectionOverlayDescription.h` — 0xB8, all fields [V] from ctor 0x668d990, size [I]
8. `src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderSkyDescription.h` — 0xB0, all fields [V] from ctor 0x668c910, size [I]

## Remaining untyped types (27)

CloudLightingParameters, CloudParameters, PerCascadeParameters, PointLightBudgetParameters, PointLightClusteringParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters, ShadowParameters, ShadowRange (10 purely untyped, no ctor/visitor evidence — cannot be [V]-documented) plus 17 more from the 62-type catalog that still lack dedicated headers.

## TOOL REQUESTS

Run `python tools/delegate.py check docs/progress/oc_U-EM2c.md` to verify all verbatim instruction lines and table formatting.
