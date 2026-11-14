#include "sdk/mc/common/client/game/GameCore.h"
#include "sdk/OffsetProvider.h"
#include "sdk/SigManager.h"

GameCore* GameCore::get() {
    return *reinterpret_cast<GameCore**>(SIG("GameCore::instance"));
}

MinecraftGame* GameCore::getMinecraftGame() {
    uintptr_t platform = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::GameCore_mPlatform);
    uintptr_t holder = *reinterpret_cast<uintptr_t*>(platform + OffsetProvider::Platform_mGameHolder);
    return *reinterpret_cast<MinecraftGame**>(holder + OffsetProvider::GameHolder_mMinecraftGame);
}
