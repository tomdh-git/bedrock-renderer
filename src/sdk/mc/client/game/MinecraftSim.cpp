#include "sdk/mc/client/game/MinecraftSim.h"
#include "client/core/diagnostics/Log.h"
#include "sdk/OffsetProvider.h"

Simulation* MinecraftSim::getGameSim() {
    return *reinterpret_cast<Simulation**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::MinecraftSim_mGameSim);
}

Simulation* MinecraftSim::getRenderSim() {
    return *reinterpret_cast<Simulation**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::MinecraftSim_mRenderSim);
}

// The game clock offset is inferred, not proven: a clock that does not read as a tick rate means they are wrong, and writing would corrupt the game.
void MinecraftSim::setTicksPerSecond(float ticks) {
    Simulation* game = getGameSim();
    Simulation* render = getRenderSim();
    BS_CHECK(game->mTicksPerSecond > 0.f && game->mTicksPerSecond <= 1000.f);
    BS_CHECK(render->mTicksPerSecond > 0.f && render->mTicksPerSecond <= 1000.f);
    game->mTicksPerSecond = ticks;
    render->mTicksPerSecond = ticks;
}
