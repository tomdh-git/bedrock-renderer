#pragma once

// The id the network protocol names an actor by (SetActorMotion, Animate, ...).
struct RuntimeIDComponent {
    static constexpr uint32_t enttHash = 0xFC0DBBB5;
    int64_t mRuntimeID;
};
