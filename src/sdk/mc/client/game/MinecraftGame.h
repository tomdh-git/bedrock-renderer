#pragma once
#include "sdk/OffsetProvider.h"

struct ClientInstance;

struct MinecraftGame {
    static MinecraftGame* get(); // GameCore::get()->getMinecraftGame()
    ClientInstance* getPrimaryClientInstance(); // map<uint8_t, ClientInterface>::find(0)
    // True while the game owns the cursor (in-world).
    bool isCursorGrabbed() const {
        return *reinterpret_cast<const bool*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::MinecraftGame_mMouseGrabbed);
    }
};
