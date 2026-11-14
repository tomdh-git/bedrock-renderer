#pragma once
#include "sdk/Layout.h"

// The game's keyboard settings, ported from Solstice-Updated (build 1.26.51): ClientInstance::getKeyboardSettings()
// walks here. The layout holds the binds as the Settings -> Controls screen shows them ("key.hotbar.1" ...
// "key.hotbar.9", "key.swapOffhand", ...). Read-only: nothing here changes what the game does with a key.
//
// Layout mirrors only: these objects live in the game's memory and are never constructed here, so the padding
// needs no initializer. The PAD macro is ported from Solstice-Updated's MemUtils (none existed here); the token
// paste keeps two pads on adjacent lines distinct.
#define BS2_PASTE(x, y) x##y
#define BS2_PASTE2(x, y) BS2_PASTE(x, y)
#define PAD(size) char BS2_PASTE2(padding_, __LINE__)[size]

// One row of the controls list: a bind's name ("key.forward") and the keys bound to it (usually one).
class MinecraftBind {
public:
    std::string mBindName;
    std::vector<int> mBindKey;
    PAD(0x8);
};

class KeyboardRemappingLayout {
public:
    PAD(0x8);
    std::vector<MinecraftBind> mKeyTypeA; // the primary binds
    std::vector<MinecraftBind> mKeyTypeB; // the alternate binds (keyboard gameplay's second column)

    int operator[](const std::string& key); // the first key bound to `key`, -1 when absent
};

class ClientInputMappingFactory {
public:
    KeyboardRemappingLayout* getKeyboardRemappingLayout(); // member at 0x110
};

class ClientInputHandler {
public:
    ClientInputMappingFactory* getMappingFactory(); // member at 0x48
};
