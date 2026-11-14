#pragma once
#include "sdk/Layout.h"
#include "sdk/OffsetProvider.h"

// Member order, condensed: mRenderChunkCoordinators, mPointLightCoordinator,
// mPointLightShadowProbeManager, mLightVolumeManager,
// mLightPropagationCoordinator, mLightVolumeOptionSubscription, mTextureGroup,
// mShadowCylinder/OverlayCube/Disc, mSkyMesh, mStarsMesh, mEndSkyMesh,
// mSunMesh, mMoonMesh[8], mNameplateBackgroundMesh, mAtlasTexture,
// mBrightnessTex, mSunTex(+Vibrant), mMoonTex, mEndSkyTex, mEndFlashTex,
// mCrackFrames, mDebugRenderer, mScriptDebugRenderer, mTicks,
// mBlockEntityRenderDispatcher, mLocalRenderer, mParticleEngine,
// mParticleSystemEngine, mGeometryEditorGui, mTaskGroup, mSyncTaskGroup,
// mGameRenderer, mLevel, mOptions, mClientInstance, mLocalUser,
// mReleaseParticleSystemInterfaceProxyCallback, mLevelRendererPlayer,
// mLevelRendererShadowCamera, mLevelRendererCloudShadowCamera,
// mShadowCascadeState, mTextureShiftsEnabled, mLevelBuilder, mProxy,
// mClearBufferColor, mPlayerView, mDataDrivenRendererV2RequiredData,
// mUniversalEntityRenderer.
// Proven offset below is the ONLY direct read (CODE-PROVEN: getter mov
// rax,[rcx+0x468] + renderLevel movss camera trio). Rest is TODO stubs.

#include "sdk/mc/client/renderer/game/LevelRendererPlayer.h"

struct LevelRenderer {
    CLASS_FIELD(LevelRendererPlayer*, mRendererPlayer, OffsetProvider::LevelRenderer_mRendererPlayer);

    LevelRendererPlayer* rendererPlayer() const {
        LevelRendererPlayer* p = mRendererPlayer;
        return p;
    }
    // TODO: picks below need proven offsets first: blockRenderer,
    // particleEngine, renderChunkCoordinator(dim), viewRegion, cameras,
    // textures/meshes, options/level/client refs. No invented offsets.
};
