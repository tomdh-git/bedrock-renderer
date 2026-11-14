#include "sdk/mc/client/game/MinecraftGame.h"
#include "sdk/mc/client/game/ClientInstance.h"
#include "sdk/mc/common/client/game/GameCore.h"
#include "sdk/OffsetProvider.h"

MinecraftGame* MinecraftGame::get() {
    return GameCore::get()->getMinecraftGame();
}

// std::map<uint8_t, ClientInterface> (MSVC): head node pointer, then the element count.
// The primary instance has key 0, the smallest key, so it is the FIRST node (head->_Left): no
// search needed. Node layout: _Left 0x00, _Parent 0x08, _Right 0x10,
// _Color 0x18, _Isnil 0x19, key 0x20, ClientInterface{void*, shared_ptr<ClientInstance>} 0x28 -> instance 0x30 (1.26.60: 0x38, proven by the walker at 0x8bce40).
// Null while the map is empty (game still booting): a real state, not a guard.
ClientInstance* MinecraftGame::getPrimaryClientInstance() {
    uintptr_t map = reinterpret_cast<uintptr_t>(this) + OffsetProvider::MinecraftGame_mClientMap;
    uintptr_t head = *reinterpret_cast<uintptr_t*>(map);
    size_t size = *reinterpret_cast<size_t*>(map + 8);
    if (size == 0)
        return nullptr;
    uintptr_t first = *reinterpret_cast<uintptr_t*>(head);
    return *reinterpret_cast<ClientInstance**>(first + 0x38);
}
