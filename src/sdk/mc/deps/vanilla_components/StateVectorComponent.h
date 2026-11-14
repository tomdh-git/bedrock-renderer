#pragma once
#include "sdk/mc/deps/core/math/Vec.h"

struct StateVectorComponent {
    Vec3 mPos;
    Vec3 mPosPrev;
    Vec3 mVelocity; // per-tick motion
};
