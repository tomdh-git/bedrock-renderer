#pragma once
#include "client/features/render/backend/OverlayBackend.h"
#include "client/features/render/post/FullscreenFx.h"

// The boot screen's hold on the picture. While it is up, the game's own picture is frozen at the first frame (before anything of ours is in it) and put back over the frame
// wherever the opening has not reached yet, so nothing of the client shows outside the burn and there is no filler colour: what is beyond the edge is the game itself.
// The slam's shockwave moves that picture (a wave travelling out of the middle, and a shake of the whole thing).
// capture() runs before the UI is drawn, composite() after the UI lists (and before the boot screen's own list).
struct ScreenShock {
    struct Wave {
        float since = -1.f;               // seconds since the impact, < 0: no wave
        float amp = 0.f;                  // the wave's height at the middle, in screen heights (set by the impact's speed)
        float shakeX = 0.f, shakeY = 0.f; // the whole picture moved, in screen sizes
    };
    static void begin() { sActive = true; }
    static void end();
    static bool active() { return sActive; }
    // Which cells of the frame are still the old picture (255) and which are open (0): `w` x `h` bytes; null means all of it is the old picture.
    static void setCoverage(const uint8_t* px, int w, int h);
    static void setWave(const Wave& w) { sWave = w; }
    static void capture(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height);
    static void composite(OverlayBackend::Cmd& cmd, UINT bufferIndex, D3D12_RESOURCE_STATES& bufferState, UINT width, UINT height);
    static void shutdown();

private:
    static inline bool sActive = false;
    static inline bool sSnapValid = false;
    static inline bool sFull = true;
    static inline bool sDirty = false;
    static inline int sCovW = 0, sCovH = 0;
    static inline std::vector<uint8_t> sCov;
    static inline Wave sWave;
    static inline FullscreenFx::Target sSnap;
    static inline FullscreenFx::Target sCover;
};
