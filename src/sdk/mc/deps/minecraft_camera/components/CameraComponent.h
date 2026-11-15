#pragma once
#include "sdk/mc/deps/core/string/HashedString.h"
#include "sdk/mc/deps/core/math/Matrix.h"
#include "sdk/mc/deps/core/math/Vec.h"

struct CameraComponent {
    static constexpr uint32_t enttHash = 0xDC565235;

    HashedString mId; // "minecraft:first_person", "minecraft:third_person", ...
    float mOrientation[4];
    Vec3 mPosition;
    float mAspectRatio;
    float mFieldOfView;
    float mNearPlane;
    float mFarPlane;
    Matrix mPostViewTransform;
    Matrix mSavedProjection;
    Matrix mSavedModelView;
};
static_assert(sizeof(CameraComponent) == 0x120);
static_assert(offsetof(CameraComponent, mFieldOfView) == 0x50);
