#pragma once
#include "sdk/mc/deps/core/math/Vec.h"
#include "sdk/mc/client/gui/ScreenSizeData.h"
#include "sdk/Layout.h"

// Member order, condensed:
// mScreenSizeData, mScreenSizeDataValid, mGuiScale, mInvGuiScale,
// mOverlappingControlsExist, mIsCurrentlyActive, mPostedErrors, mMenuPointer,
// mPointerX/Y, mHasShowPreexistingMessages, mToolbarWasRendered,
// mPrevSelectedSlot, mPrevSelectedInventoryContainer, mFlashSlotId,
// mFlashSlotStartTime, mClient, mToolbarArea(+Container), mLastPopupText(+Sub,
// Jukebox+Sub), mTickCount, mItemNameOverlayTime, mJukeboxNameOverlayTime,
// mPopupNoticeDirty, mJukeboxPopupNoticeDirty, mGuiMessages, mSubtitleMessages,
// mDevConsoleMessages, mMaxDevConsoleMessages, mContentLogMessages,
// mContentLogErrorCount, mPerfTurtleMessages, mModalScreenData, mTitleMessage,
// mHudVisibilityState[13], mServerSettingsId, mServerSettings, mMuteChat,
// mCurrentDropTicks, mCurrentDropSlot, mLastSelectedSlot, mShowProgress,
// mTipMessage, mTipMessageLength, mRcFeedbackOuter/Inner, mVignette,
// mInvFillMat, mCursorMat, mDevConsoleLogger, mLastTickTime, mDelayedMessages,
// mQueuedDevConsoleMessages, mQueuedDevMessagesMutex, mUseEditorGuiScale,
// mHUDHotbarRectangle, mCoordinateCaptureType, mOnGuiScaleUpdatedPublisher,
// mServerFormDataAvailable.
// Offsets unproven (no layout); proven offsets below are the
// ONLY direct reads (CODE-PROVEN live: CI+0x650 obj carries MI-vtable +
// mResolution 1920x1017 + scale chain 4.0/0.25). Rest is TODO stubs,
// null-guarded defaults, no invented offsets, no garbage reads.
struct GuiData {
    CLASS_FIELD(Vec2, mResolution, 0x40);
    CLASS_FIELD(Vec2, mResolutionRounded, 0x48);
    CLASS_FIELD(Vec2, mResolutionScaled, 0x50);
    CLASS_FIELD(float, mGuiScale, 0x5C);
    CLASS_FIELD(float, mScalingMultiplier, 0x60);

    float getGuiScale() const {
        float s = mGuiScale;
        return s > 0.f ? s : 0.f;
    }
    Vec2 getResolution() const { return mResolution; }
    ScreenSizeData screenSize() const {
        // TODO: map mScreenSizeData once the offset is proven; derived for now.
        ScreenSizeData d{};
        d.totalScreenSize = mResolution;
        d.clientScreenSize = mResolutionRounded;
        d.clientUIScreenSize = mResolutionScaled;
        return d;
    }
    // TODO: full HUD visibility (mHudVisibilityState[13]) + messages/title/
    // popup/toolbar/drop-slot/tip/vignette/materials/loggers/publishers when
    // a caller needs them; each needs a proven offset first.
};
