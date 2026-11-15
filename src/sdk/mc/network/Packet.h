#pragma once
#include "sdk/mc/network/MinecraftPacketIds.h"
#include "sdk/Layout.h"

struct IPacketHandlerDispatcher;

enum class PacketPriority : int { Immediate = 0, High = 1, Medium = 2, Low = 3 };
enum class Reliability : int { Reliable = 0, ReliableOrdered = 1, Unreliable = 2, UnreliableSequenced = 3 };
enum class Compressibility : int { Compressible = 0, Incompressible = 1 };

// The fields are the game's; virtuals are called by index.
class Packet {
public:
    void* mVtable;
    PacketPriority mPriority;
    Reliability mReliability;
    uint8_t mSenderSubId;
    bool mIsHandled;
    int64_t mReceiveTimepoint;
    const IPacketHandlerDispatcher* mHandler;
    Compressibility mCompressible;

    MinecraftPacketIds getId() const { return callVirtual<MinecraftPacketIds>(1, const_cast<Packet*>(this)); }
    std::string_view getName() const {
        std::string_view out;
        callVirtual<std::string_view*>(2, const_cast<Packet*>(this), &out);
        return out;
    }
};
static_assert(sizeof(Packet) == 0x30);
