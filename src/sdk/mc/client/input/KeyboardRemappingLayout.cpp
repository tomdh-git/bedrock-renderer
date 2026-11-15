#include "sdk/mc/client/input/KeyboardRemappingLayout.h"
#include "client/core/diagnostics/Log.h"

// Names already reported missing: a log-once latch. The lookup runs every frame, so a missing name must not become a
// log stream (the same shape as AnimPlayer::logMissingOnce).
static bool alreadyLoggedMissing(const std::string& name) {
    static std::vector<std::string> logged;
    for (const std::string& seen : logged)
        if (seen == name)
            return true;
    logged.push_back(name);
    return false;
}

int KeyboardRemappingLayout::operator[](const std::string& key) {
    // A wrong offset reads nonsense sizes: no keyboard layout holds a thousand binds.
    if (mKeyTypeA.size() > 1024 || mKeyTypeB.size() > 1024)
        return -1;
    auto firstBound = [&](std::vector<MinecraftBind>& binds) -> int {
        for (MinecraftBind& bind : binds) {
            if (bind.mBindName.size() >= 128) // garbage: not a bind name
                continue;
            if (bind.mBindName != key || bind.mBindKey.empty())
                continue;
            return bind.mBindKey[0];
        }
        return -1;
    };
    const int vk = firstBound(mKeyTypeA);
    if (vk >= 0)
        return vk;
    const int alternate = firstBound(mKeyTypeB);
    if (alternate >= 0)
        return alternate;
    if (!alreadyLoggedMissing(key))
        Logger::warn("[viewhands] the game's keyboard layout has no bind named '{}'", key);
    return -1;
}

KeyboardRemappingLayout* ClientInputMappingFactory::getKeyboardRemappingLayout() {
    return *reinterpret_cast<KeyboardRemappingLayout**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::ClientInputMappingFactory_mKeyboardRemappingLayout);
}

ClientInputMappingFactory* ClientInputHandler::getMappingFactory() {
    return *reinterpret_cast<ClientInputMappingFactory**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::ClientInputHandler_mMappingFactory);
}
