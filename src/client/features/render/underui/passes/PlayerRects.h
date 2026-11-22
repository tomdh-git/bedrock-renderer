#pragma once
#include "client/features/render/underui/UnderGpu.h"
#include "client/features/hooks/hooks/render/SetupAndRenderHook.h"
#include "client/features/render/players/PlayerSeen.h"

// Where the roster's players are on the screen of the frame being drawn (the camera and the positions the game drew in that same frame), for the passes that draw over the
// finished scene: a rectangle in pixels, how far the player is in front of the camera (blocks), and whether it is the local player.
struct PlayerRects {
    struct One {
        float rect[4];
        float dist;
        bool local;
    };

    // padX / padY: how far the box's rectangle is grown, as a share of its own width / height (plus `pixels`); `above` extra share of the height upward (a nametag is over the head).
    static std::vector<One> collect(const UnderCamera& cam, float w, float h, float padX, float padY, float above, float pixels) {
        std::vector<One> out;
        const SetupAndRenderHook::Transform t = SetupAndRenderHook::newest();
        if (!t.bodies)
            return out;
        for (const PlayerSeen& seen : *static_cast<const std::vector<PlayerSeen>*>(t.bodies.get())) {
            if (seen.local) { // the player's own model is on the screen only away from the head (third person)
                const float ex = cam.pos[0] - cam.player[0], ey = cam.pos[1] - cam.player[1], ez = cam.pos[2] - cam.player[2];
                if (ex * ex + ey * ey + ez * ez < 1.5f * 1.5f)
                    continue;
            }
            Vec3 lo, hi;
            PlayerSeen::corners(seen, lo, hi);
            float mnU = 1e9f, mnV = 1e9f, mxU = -1e9f, mxV = -1e9f;
            bool behind = false;
            for (int i = 0; i < 8 && !behind; ++i) {
                const float rx = ((i & 1) ? hi.x : lo.x) - cam.pos[0], ry = ((i & 2) ? hi.y : lo.y) - cam.pos[1], rz = ((i & 4) ? hi.z : lo.z) - cam.pos[2];
                const float zz = cam.fwd[0] * rx + cam.fwd[1] * ry + cam.fwd[2] * rz;
                if (zz < 0.1f) {
                    behind = true;
                    break;
                }
                const float nx = (cam.right[0] * rx + cam.right[1] * ry + cam.right[2] * rz) / zz * cam.fov[0];
                const float ny = (cam.up[0] * rx + cam.up[1] * ry + cam.up[2] * rz) / zz * cam.fov[1];
                const float u = nx * 0.5f + 0.5f, v = 0.5f - ny * 0.5f;
                mnU = std::min(mnU, u);
                mxU = std::max(mxU, u);
                mnV = std::min(mnV, v);
                mxV = std::max(mxV, v);
            }
            One o{};
            o.local = seen.local;
            const float cx = (lo.x + hi.x) * 0.5f - cam.pos[0], cy = (lo.y + hi.y) * 0.5f - cam.pos[1], cz = (lo.z + hi.z) * 0.5f - cam.pos[2];
            o.dist = std::max(0.5f, cam.fwd[0] * cx + cam.fwd[1] * cy + cam.fwd[2] * cz);
            if (behind) { // a corner is behind the camera: the player is right here, the whole screen
                o.rect[0] = o.rect[1] = 0.f;
                o.rect[2] = w;
                o.rect[3] = h;
            } else {
                const float bw = (mxU - mnU) * w, bh = (mxV - mnV) * h;
                o.rect[0] = std::clamp(mnU * w - bw * padX - pixels, 0.f, w);
                o.rect[1] = std::clamp(mnV * h - bh * (padY + above) - pixels, 0.f, h);
                o.rect[2] = std::clamp(mxU * w + bw * padX + pixels, 0.f, w);
                o.rect[3] = std::clamp(mxV * h + bh * padY + pixels, 0.f, h);
                if (o.rect[2] <= o.rect[0] || o.rect[3] <= o.rect[1])
                    continue;
            }
            out.push_back(o);
        }
        return out;
    }
};
