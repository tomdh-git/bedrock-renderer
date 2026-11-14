#pragma once
#include "sdk/mc/deps/core/string/GameString.h"

// The game's key object (LeviLamina: 8-byte vftable, 32 bytes, 8 bytes). The 32-byte member is read as the public key text;
// the account switcher checks that assumption against the live object before relying on it.
struct KeyManager {
    void* mVtable;
    GameString mPublicKey;
    std::byte mPad0[0x8];
};
static_assert(sizeof(KeyManager) == 0x30);
