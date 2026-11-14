#pragma once

// The game's own key bindings, by the names its Settings -> Controls screen uses ("key.hotbar.1" ... "key.hotbar.9",
// "key.swapOffhand"). Observation only: the keys themselves still reach the game, untouched — nothing here feeds
// BindFilter. A layout that is missing or a name that is not bound reads as -1, never a crash.
struct GameKeys {
    static int hotbar(int slot);       // slot 0..8 -> the virtual key the game binds there, -1 unknown
    static int swapOffhand();          // "key.swapOffhand", -1 unknown
    static bool hotbarSwitchPressed(); // any of key.hotbar.1..9 or key.swapOffhand pressed since the last call
};
