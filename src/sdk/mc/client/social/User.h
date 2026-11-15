#pragma once
#include "sdk/OffsetProvider.h"
#include "sdk/SigManager.h"
#include "sdk/mc/deps/core/string/GameString.h"

// Social::User (UserImpl): the account the game is signed in as. Only the gamertag is proven: the getter at vtable 44
// (sub 0x84f50 in 1.26.51) copies the std::string at +0x358 into its result, and ConnectionRequest::create's thirdPartyName
// is that getter's value.
namespace Social {
struct User {
    // The vtable slot of getGamertag(this, out): it has no fixed index we trust across builds, so it is found as the slot that holds the sig-found function.
    size_t gamertagGetterSlot() {
        void** vt = *reinterpret_cast<void***>(this);
        size_t slot = 0;
        while (slot < 256 && vt[slot] != reinterpret_cast<void*>(SIG("User::getGamertag")))
            ++slot;
        BS_CHECK(slot < 256);
        return slot;
    }
    GameString& gamertag() { return *reinterpret_cast<GameString*>(reinterpret_cast<std::byte*>(this) + OffsetProvider::User_mGamertag); }
};
} // namespace Social
