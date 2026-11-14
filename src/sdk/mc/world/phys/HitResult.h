#pragma once
#include "sdk/mc/deps/core/math/BlockPos.h"
#include "sdk/mc/deps/core/math/Vec.h"

enum class HitResultType : int {
    Tile = 0,
    Entity = 1,
    EntityOutOfRange = 2,
    NoHit = 3,
};

// What the crosshair ray hit, as the level keeps it (LeviLamina 26.60 layout; Level slot 336 returns the liquid twin 0x88 further, which fixes the size).
struct HitResult {
    Vec3 mStartPos;
    Vec3 mRayDir;
    HitResultType mType;
    uint8_t mFacing;
    BlockPos mBlock;
    Vec3 mPos;
    std::byte mEntity[0x18]; // ::WeakEntityRef
    float mEntityAABB[6];
    bool mIsHitLiquid;
    uint8_t mLiquidFacing;
    BlockPos mLiquid;
    Vec3 mLiquidPos;
    bool mIndirectHit;
};
static_assert(offsetof(HitResult, mType) == 0x18);
static_assert(offsetof(HitResult, mBlock) == 0x20);
static_assert(offsetof(HitResult, mPos) == 0x2C);
static_assert(offsetof(HitResult, mIsHitLiquid) == 0x68);
static_assert(offsetof(HitResult, mLiquid) == 0x6C);
static_assert(sizeof(HitResult) == 0x88);
