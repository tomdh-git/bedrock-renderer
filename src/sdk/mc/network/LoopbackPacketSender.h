#pragma once

class Packet;

// Slot 0 is PacketSender's destructor.
struct LoopbackPacketSender {
    static constexpr int vSend = 2;         // virtual void send(Packet&)
    static constexpr int vSendToServer = 4; // virtual void sendToServer(Packet&)
    void* sendAddress() const { return (*reinterpret_cast<void* const* const*>(this))[vSend]; }
};
