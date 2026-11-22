#pragma once

// What the Ambience module publishes for the sky and fog passes, so render never reads a module.
struct SkyInputState {
    bool enabled = false;
    bool shaderSky = false;
    int style = 0;
    bool theme = true;
    bool hideCelestial = false;
    int resolution = 0;
    float gain = 0.6f;
    bool fogOn = false;
    float fogStart = 80.f;
    float fogEnd = 170.f;
    bool fogGround = true;
    float fogHeight = 20.f;

    // The game thread publishes the whole state at once and the render thread takes a whole one: a field-by-field write was seen half done (a fog start above its end
    // for a frame, the module on with the old style).
    static SkyInputState get() { return *sCurrent.load(); }
    static void publish(const SkyInputState& state) { sCurrent.store(std::make_shared<const SkyInputState>(state)); }

private:
    static std::atomic<std::shared_ptr<const SkyInputState>> sCurrent;
};

inline std::atomic<std::shared_ptr<const SkyInputState>> SkyInputState::sCurrent{std::make_shared<const SkyInputState>()};
