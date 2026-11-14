#pragma once

// A simulation clock: the first float is the ticks per second (20 normally); the rest of the object is not mirrored.
struct Simulation {
    float mTicksPerSecond;
};

// The client's simulation: a game clock and a render clock that both run on the same rate.
struct MinecraftSim {
    Simulation* getGameSim();
    Simulation* getRenderSim();
    void setTicksPerSecond(float ticks); // both clocks
};
