#pragma once

struct MinecraftGame;

// The GameCore (AppPlatform) object behind the Platform_GameCore global: the
// root of the game-object chain. Callers use MinecraftGame::get() /
// ClientInstance::get(), never this chain.
struct GameCore {
    static GameCore* get();
    MinecraftGame* getMinecraftGame(); // this -> Platform -> holder -> MinecraftGame
};
