#pragma once
#include "client/features/render/underui/UnderGpu.h"

// How the camera moves, for effects that need its speed (the motion blur): the cameras the game captures, one per frame, are kept for a few tenths of a
// second, and the velocity is what the camera did over the last `exposure` seconds (the pose now against the pose then: the angle it really turned, the
// distance it really moved), as a translation and a rotation vector in world space, plus the local player's own velocity (it moves with the keys even when
struct CameraMotion {
    UnderCamera cur, prev;
    uint32_t seq = 0;
    bool havePrev = false;
    Vec3 v, w;            // mean velocity of the camera over the exposure (blocks/s) and its rotation (a rotation vector, rad/s)
    Vec3 vp;              // mean velocity of the player's own position
    bool valid = false;   // two cameras of the same view are held (not reset by a stall, a new world or a view switch)
    double frameDt = 1.0 / 60.0; // time between two frames' cameras (smoothed)

    void reset();                      // a stale pair must not blur the first frame after the effect is turned on
    void advance(double exposure);     // takes the camera of the frame being drawn (captured in this very frame); the velocities are those over `exposure` seconds
    bool moving(float exposure) const; // does the camera move during an exposure of this length?
    // The player's box on the screen (uv, a little wider), when the camera is away from the head (third person) and the whole box is in front of it;
    // `depth` is how far in front of the camera the player's middle is (blocks).
    bool playerRect(float out[4], float& depth) const;

private:
    static constexpr int kHistory = 32;                             // frames kept: a third of a second at 100 frames a second is the longest exposure there is
    UnderCamera hist[kHistory];                                     // newest first
    int histCount = 0;
    void observe(const UnderCamera& c);
    void push(const UnderCamera& c);
    void stop();                                                    // no motion: a stall, a respawn, a new world or a view switch
    void over(double exposure);                                     // v, w and vp over the last `exposure` seconds

private:
    static Vec3 offset(const float (&a)[3], const float (&b)[3]);
    static bool isJump(const UnderCamera& prev, const UnderCamera& cur, double dt);
    struct Turn;
    static Turn turnBetween(const UnderCamera& prev, const UnderCamera& cur);
};
