#pragma once
#include "sdk/mc/world/gamemode/GameMode.h"

struct Actor;

// The game's GameMode virtuals (vtable slots in OffsetProvider).
struct GameModeCalls {
    static float getDestroyRate(GameMode* gm, const void* block) {
        using Fn = float (*)(GameMode*, const void*);
        return reinterpret_cast<Fn>(SIG("GameMode::getDestroyRate"))(gm, block);
    }
    static bool attack(GameMode* gm, Actor& target, const Vec3& hitPosition) {
        return callVirtual<bool>(OffsetProvider::GameMode_attack, gm, &target, hitPosition);
    }
    static bool startDestroyBlock(GameMode* gm, const BlockPos& pos, uint8_t face, bool& hasDestroyedBlock) {
        return callVirtual<bool>(OffsetProvider::GameMode_startDestroyBlock, gm, pos, face, &hasDestroyedBlock);
    }
    static bool continueDestroyBlock(GameMode* gm, const BlockPos& pos, uint8_t face, const Vec3& playerPos, bool& hasDestroyedBlock) {
        return callVirtual<bool>(OffsetProvider::GameMode_continueDestroyBlock, gm, pos, face, &playerPos, &hasDestroyedBlock);
    }
    static bool destroyBlock(GameMode* gm, const BlockPos& pos, uint8_t face) {
        return callVirtual<bool>(OffsetProvider::GameMode_destroyBlock, gm, pos, face);
    }
    static void stopDestroyBlock(GameMode* gm, const BlockPos& pos) {
        callVirtualVoid(OffsetProvider::GameMode_stopDestroyBlock, gm, pos);
    }
    static bool buildBlock(GameMode* gm, const BlockPos& pos, uint8_t face, uint8_t hand, bool simTick) {
        return callVirtual<bool>(OffsetProvider::GameMode_buildBlock, gm, pos, face, hand, simTick);
    }
};
