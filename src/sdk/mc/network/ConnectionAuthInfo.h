#pragma once
#include "sdk/mc/certificates/identity/PlayerAuthenticationType.h"
#include "sdk/mc/deps/certificates/KeyManager.h"
#include "sdk/mc/deps/core/string/GameString.h"

// What ConnectionRequest::create signs a login with (LeviLamina layout, client build): the key that signs the client data
// and the game server token (the multiplayer token from the Minecraft services) that vouches for whose key it is.
#pragma pack(push, 1)
struct ConnectionAuthInfo {
    KeyManager* userSigner; // PrivateKeyManager const& in the game
    PlayerAuthenticationType authenticationType;
    std::byte mPad0[0x4];
    GameString gameServerToken; // RawGameServerToken
};
#pragma pack(pop)
static_assert(offsetof(ConnectionAuthInfo, authenticationType) == 0x8);
static_assert(offsetof(ConnectionAuthInfo, gameServerToken) == 0x10);
static_assert(sizeof(ConnectionAuthInfo) == 0x30);
