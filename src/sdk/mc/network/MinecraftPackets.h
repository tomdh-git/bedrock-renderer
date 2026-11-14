#pragma once
#include "sdk/mc/network/Packet.h"

struct MinecraftPackets {
    static std::shared_ptr<Packet> createPacket(MinecraftPacketIds id);
};
