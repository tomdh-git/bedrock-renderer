#include "sdk/mc/network/MinecraftPackets.h"
#include "sdk/SigManager.h"

// static std::shared_ptr<Packet> createPacket(MinecraftPacketIds): the shared_ptr comes back through a hidden pointer.
// shared_ptr is two pointers in every STL configuration, and its control block is the game's own.
std::shared_ptr<Packet> MinecraftPackets::createPacket(MinecraftPacketIds id) {
    using Fn = std::shared_ptr<Packet>* (*)(std::shared_ptr<Packet>*, MinecraftPacketIds);
    std::shared_ptr<Packet> out;
    reinterpret_cast<Fn>(SIG("MinecraftPackets::createPacket"))(&out, id);
    return out;
}
