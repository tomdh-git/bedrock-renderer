#pragma once

// Which transport the game talks on. No in-binary signal is proven on this build (LoopbackPacketSender exposes only
// dtor/send/sendToServer, the NetworkSystem connectors are opaque, the raknet/nethernet signatures are parked), so
// detect() scans the process's loaded modules for a component that names itself - and reports Unknown, never a guess.
struct Transport {
    enum class Kind { Unknown, RakNet, NetherNet };
    static Kind detect(); // cached after the first probe; one atomic load on the warm path
    static const char* name(Kind kind);
};
