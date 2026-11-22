#pragma once
#include "client/features/render/underui/UnderUI.h"

// The passes UnderUI draws (each file adds its own; see UnderPass in UnderUI.h). Added once at startup; the order of adding is the order of the
// passes' wanted() calls in a frame (the fog asks what the sky decided, so the sky is first).
struct SkyPasses { static void install(); };      // SkyPass.cpp: the shader sky, the menu background, the distance fog
struct MotionBlurPasses { static void install(); }; // MotionBlurPass.cpp: motion blur over the finished 3D scene
struct GeekbarWorldPasses { static void install(); }; // depth-tested world-space Geekbar smoke
struct UnderActorsPasses { static void install(); }; // UnderActorsPass.cpp: the ESP list under the actors, drawn after the blur
struct NameTagBlurPasses { static void install(); }; // NameTagBlurPass.cpp: the game's nametags smeared by the camera's turn, after they are drawn
// What the scene's blur found about this frame's camera, for the nametag blur after it (render thread, same frame: the blur's pass runs first).
struct BlurShare {
    static inline bool turning = false;                  // the camera moves (turns or walks) enough this frame to blur
    static inline float axis[3] = {0, 0, 1}, turn = 0.f; // the turn over the exposure
    static inline float dp[3] = {0, 0, 0};               // and the walk over it (the blur's own smoothed displacement)
    static inline float right[3] = {1, 0, 0}, up[3] = {0, 1, 0}, fwd[3] = {0, 0, -1}, fov[2] = {1, 1};
};
struct ChamsPasses { static void install(); }; // ChamsPass.cpp: the players' chams over the finished (blurred) scene
struct DrawListPasses { static void install(); }; // DrawListPass.cpp: the ImGui background list and the item in hand under the game's UI
struct UnderPasses { static void install(); };    // Passes.cpp: all of them (Systems::init)
