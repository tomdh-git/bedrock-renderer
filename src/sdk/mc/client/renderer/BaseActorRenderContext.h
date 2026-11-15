#pragma once
#include "sdk/Layout.h"
#include "sdk/mc/client/gui/screens/ScreenContext.h"
#include "sdk/mc/client/renderer/game/ItemInHandRenderer.h"
// Member order: mNumEntitiesRenderedThisFrame, mLastFrameTime, mSortedMeshDrawList,
// mClientInstance, mMinecraftGame, mScreenContext, mBlockEntityRenderDispatcher,
// mEntityRenderDispatcher, mEntityBlockRenderer, mItemInHandRenderer,
// mItemRenderer, mHudIconActorRenderer, mLightVolumeManager,
// mParticleSystemEngine, mProcessedV2DataDrivenRenderers,
// mV2DataDrivenContinuousData, mV2ShouldRenderActorsWithAttachables,
// mRenderUniqueIdOverride, mImpl(camTarget/camPos/worldClip/historical),
// mFrameAlpha, mActorDitheringMaxDistance, mIsOnScreen,
// mUpdateBonesAndEffects, mUpdateEffects, mIgnoresLighting, mForceLightingOn,
// mIsRenderingOnMap.
// Impl: mOffscreenCaptureDescription, mCameraTargetPosition, mCameraPosition,
// mWorldClipRegion, mHistoricalFrameTimes.
// Offsets unproven (prior 0x50/0x28 layout stale).
// All accessors below are TODO stubs, null-guarded defaults, no invented
// offsets, no garbage reads. Ctor/dtor-thunks omitted (game-side only).

struct Actor;
struct ScreenContext;

class BaseActorRenderContext {
public:
    static constexpr int VTable_Dtor = 0;
    static constexpr int VTable_Size = 1;

    ItemInHandRenderer* getItemInHandRenderer() {
        sdkLogStub("BaseActorRenderContext::getItemInHandRenderer");
        return nullptr;
    }
    ScreenContext* getScreenContext() {
        sdkLogStub("BaseActorRenderContext::getScreenContext");
        return nullptr;
    }
    float getFrameAlpha(const Actor& actor) const {
        (void)actor;
        sdkLogStub("BaseActorRenderContext::getFrameAlpha");
        return 0.f;
    }
    // TODO: picks in member order when a caller needs them, each with a proven
    // offset first: clientInstance, minecraftGame, entityDispatcher,
    // entityBlockRenderer, itemRenderer, hudIconRenderer, lightVolumeManager,
    // particleEngine, cameraTarget/Position, worldClipRegion, frameTimes,
    // frameAlpha, dithering, onScreen/bones/effects/lighting/map flags,
    // getCameraRotation, getDataDrivenRenderer, getFontHandle.
};
