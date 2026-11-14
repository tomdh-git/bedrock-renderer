#pragma once
// (Lite OffsetProvider Actor_mBuiltInComponents, 1.26.51 CODE-PROVEN.)
#include "sdk/mc/deps/vanilla_components/StateVectorComponent.h"

struct AABBShapeComponent;
struct ActorRotationComponent;
struct ActorWalkAnimationComponent;

struct BuiltInActorComponents {
    StateVectorComponent* mStateVectorComponent;
    AABBShapeComponent* mAABBShapeComponent;
    ActorRotationComponent* mActorRotationComponent;
    ActorWalkAnimationComponent* mWalkAnimationComponent;
};
