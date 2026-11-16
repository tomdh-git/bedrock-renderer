#pragma once
// UNIT U-D5g: RenderMeshFallbackDescription (Item group tag 2) static layout assertions.
// Verified against ctor 0x668b850 stores (desc = rsi), offset 0x000..0x1D0, size 0x1D0.
// Descriptions.h is NOT edited; this header includes it and re-asserts the full layout.
#include "../../src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h"

namespace mce::framebuilder {

static_assert(sizeof(RenderMeshFallbackDescription) == 0x1D0);
static_assert(offsetof(RenderMeshFallbackDescription, mMesh) == 0x000);
static_assert(offsetof(RenderMeshFallbackDescription, mNumTextures) == 0x088);
static_assert(offsetof(RenderMeshFallbackDescription, mMatrix) == 0x090);
static_assert(offsetof(RenderMeshFallbackDescription, mCameraPos) == 0x0D0);
static_assert(offsetof(RenderMeshFallbackDescription, mFlagDC) == 0x0DC);
static_assert(offsetof(RenderMeshFallbackDescription, mFlagDD) == 0x0DD);
static_assert(offsetof(RenderMeshFallbackDescription, mFlagDE) == 0x0DE);
static_assert(offsetof(RenderMeshFallbackDescription, mFlagDF) == 0x0DF);
static_assert(offsetof(RenderMeshFallbackDescription, mFlagE0) == 0x0E0);
static_assert(offsetof(RenderMeshFallbackDescription, mBlockE4) == 0x0E4);
static_assert(offsetof(RenderMeshFallbackDescription, mBlockF4) == 0x0F4);
static_assert(offsetof(RenderMeshFallbackDescription, mMaterial) == 0x108);
static_assert(offsetof(RenderMeshFallbackDescription, mParams) == 0x118);
static_assert(offsetof(RenderMeshFallbackDescription, mParam100) == 0x120);
static_assert(offsetof(RenderMeshFallbackDescription, mParam150) == 0x130);
static_assert(offsetof(RenderMeshFallbackDescription, mContext6D) == 0x134);
static_assert(offsetof(RenderMeshFallbackDescription, mParam70) == 0x138);
static_assert(offsetof(RenderMeshFallbackDescription, mParam78) == 0x148);
static_assert(offsetof(RenderMeshFallbackDescription, mParam80) == 0x150);
static_assert(offsetof(RenderMeshFallbackDescription, mOverride) == 0x154);
static_assert(offsetof(RenderMeshFallbackDescription, mHasOverride) == 0x164);
static_assert(offsetof(RenderMeshFallbackDescription, mFlags) == 0x168);
static_assert(offsetof(RenderMeshFallbackDescription, mVariantHead) == 0x170);
static_assert(offsetof(RenderMeshFallbackDescription, mVariantByte) == 0x180);
static_assert(offsetof(RenderMeshFallbackDescription, mVariantPayload) == 0x188);
static_assert(offsetof(RenderMeshFallbackDescription, mVariantIndex) == 0x1A0);
static_assert(offsetof(RenderMeshFallbackDescription, mBounds) == 0x1A8);
static_assert(offsetof(RenderMeshFallbackDescription, mMeshVec4) == 0x1C0);

}
