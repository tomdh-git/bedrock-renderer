#pragma once

class Packet;

// One per packet type: handle() routes a received packet to the game's handler for it.
struct IPacketHandlerDispatcher {
    static constexpr int vHandle = 1; // virtual void handle(NetworkIdentifier const&, NetEventCallback&, std::shared_ptr<Packet>&) const
    void* handleAddress() const { return (*reinterpret_cast<void* const* const*>(this))[vHandle]; }
};
