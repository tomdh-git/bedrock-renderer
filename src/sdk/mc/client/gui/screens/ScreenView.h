#pragma once
#include "sdk/mc/deps/core/math/Vec.h"
#include "sdk/Layout.h"
// Member order, condensed: mLastTime, mTickTime, mLastRawJoystickEventTime, mSize,
// mMenuUp/Down/Left/RightButtonId, mMenuTabLeft/RightButtonId,
// mPointerButtonIds[2], mController, mVisualTree, mAlwaysBindControls,
// mInputControls, mScrollViewControls, mOutOfModalScopeScrollViewControls,
// mAnimationControls, mFactoryControls, mTextEditBoxControls,
// mAlwaysListeningInputControls, mRenderableControls,
// mFlyingItemRendererControls, mSliderControls, mCustomRendererControls,
// mCustomFrameUpdateControls, mControlsToRemove map, mRootRenderBatch,
// mAnimationController, mReservedButtonUpEvents, mSelectedControl, mInputMode,
// mLayoutManager, mFocusManager, mTTSEventManager, mTextToSpeechEnabled,
// mTTSSectionHeader, mCurrentSliderValue, mIsGUIScaleSlider,
// mControllerStickDirections, mControllerLastMoved, mCursorTick,
// mControllerX/YThreshold, mControllerStickValues[9], mGamepadCursorData,
// mGamepadCursorPosition, mHasSetInitialPosition,
// mGamepadCursorFocusMode/MagnetEnabled, mGamepadMagnetControl,
// mGamepadMoveTime, mGamepadTrackedDirection, mGamepadHasTapped, mTouchPadData,
// mPointerLocationPrevious, mLastPointInTime, mCurrentTime, mTimeAccumulator,
// mFixedAnimationUpdateRate, mKeyboardHeight, mShouldShowKeyboard,
// mInitKeyboard, mCurrentObfuscateTime, mKeyboardManager, mInputAreas,
// mMeasureStrategy, mCanMoveFocus, mNextFocusAction, mControlFactory,
// mAnimationEvents, mCustomRendererEvents, mStartLocation,
// mTimeUntilNextPointerHeldEvent, mDelayBetweenEachPointerHeldEvent,
// mShouldSendPointerHeldEvents, mDelayedCommands, mProxy, mQueuedTextChange,
// mIsExiting/Entering/Initialized, mHasFocus/HadFocus, mIsTerminating,
// mDirectionalButtonWasPressed, mDelayedFocusRefresh,
// mTextEditFocusedListener, mScreenLoadTimeTracker, mFocusChangeSub.
// Methods: render(uiRenderContext), resize, getRoute/ScreenName,
// handlePointerLocation/ButtonEvent, setupAndRender(screenView, mcuirc) is the
// world-view frame entry (hook target, SigManager screenview_setupandrender).
// Offsets unproven; no data members here (no invented layout). View state
// below is TODO stubs, null-guarded defaults.

struct MinecraftUIRenderContext;

struct ScreenView {
    Vec2 viewSize() const {
        sdkLogStub("ScreenView::viewSize");
        return Vec2{};
    }
    const char* screenName() const {
        sdkLogStub("ScreenView::screenName");
        return "";
    }
    void* setupAndRender(void* mcuirc) {
        (void)mcuirc;
        sdkLogStub("ScreenView::setupAndRender");
        return nullptr;
    }
    void render(MinecraftUIRenderContext&) { sdkLogStub("ScreenView::render"); }
    void resize() { sdkLogStub("ScreenView::resize"); }
    // TODO: controller/visualTree/focus/layout/measure/proxy/inputAreas/
    // gamepad/touch/keyboard/animationEvents/delayedCommands/loadTracker when
    // a caller needs them; each needs a proven offset first.
};
