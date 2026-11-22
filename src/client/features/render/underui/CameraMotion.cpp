#include "client/features/render/underui/CameraMotion.h"
#include "client/features/hooks/hooks/render/SetupAndRenderHook.h"

void CameraMotion::reset() {
    cur = prev = UnderCamera{};
    seq = 0;
    havePrev = false;
    histCount = 0;
    v = w = vp = Vec3{};
    valid = false;
}

Vec3 CameraMotion::offset(const float (&a)[3], const float (&b)[3]) { return {b[0] - a[0], b[1] - a[1], b[2] - a[2]}; }

// Not motion: a stall, a respawn, a new world, and the camera being put somewhere else against the player (the perspective was switched: the
// camera sits at the head in first person and behind it in third; that must not run through the filter as a speed).
bool CameraMotion::isJump(const UnderCamera& prev, const UnderCamera& cur, double dt) {
    const Vec3 fromPlayerPrev = offset(prev.player, prev.pos), fromPlayerCur = offset(cur.player, cur.pos);
    return dt > 0.25 || offset(prev.pos, cur.pos).length() > 8.0f || (fromPlayerCur - fromPlayerPrev).length() > 0.35f;
}

// The rotation Q that takes the earlier axes to the later (Q = sum of b_m a_m^T): its axis scaled by sin (s) and its angle.
struct CameraMotion::Turn {
    Vec3 s;
    float sinA, angle;
};
CameraMotion::Turn CameraMotion::turnBetween(const UnderCamera& prev, const UnderCamera& cur) {
    const Vec3 a[3] = {Vec3::of(prev.right), Vec3::of(prev.up), Vec3::of(prev.fwd)};
    const Vec3 b[3] = {Vec3::of(cur.right), Vec3::of(cur.up), Vec3::of(cur.fwd)};
    float Q[3][3] = {};
    for (int m = 0; m < 3; ++m) {
        const float bm[3] = {b[m].x, b[m].y, b[m].z}, am[3] = {a[m].x, a[m].y, a[m].z};
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                Q[i][j] += bm[i] * am[j];
    }
    const Vec3 s = {(Q[2][1] - Q[1][2]) * 0.5f, (Q[0][2] - Q[2][0]) * 0.5f, (Q[1][0] - Q[0][1]) * 0.5f};
    const float sinA = s.length(), cosA = (Q[0][0] + Q[1][1] + Q[2][2] - 1.0f) * 0.5f;
    return {s, sinA, std::atan2(sinA, cosA)};
}


void CameraMotion::push(const UnderCamera& c) {
    for (int i = std::min(histCount, kHistory - 1); i > 0; --i)
        hist[i] = hist[i - 1];
    hist[0] = c;
    histCount = std::min(histCount + 1, kHistory);
}

// The view was switched, the camera jumped: what came before says nothing about the motion from here. The camera of this frame starts the history.
void CameraMotion::stop() {
    v = w = vp = Vec3{};
    valid = false;
    histCount = 0;
    push(cur);
}

// A camera of a new frame, into the history.
void CameraMotion::observe(const UnderCamera& c) {
    if (cur.valid) {
        prev = cur;
        havePrev = true;
    }
    cur = c;
    if (!havePrev)
        return push(cur);
    const double dt = cur.time - prev.time;
    if (isJump(prev, cur, dt))
        return stop();
    if (dt < 1e-4)
        return;
    frameDt += (dt - frameDt) * 0.1;
    if (turnBetween(prev, cur).angle > 1.2f) // a snap of seventy degrees or more in one frame is a view being switched, not turned
        return stop();
    push(cur);
}

// What the camera did during the last `exposure` seconds: the camera of that moment (the nearest one kept) against the camera now.
void CameraMotion::over(double exposure) {
    v = w = vp = Vec3{};
    valid = histCount >= 2;
    if (!valid)
        return;
    const UnderCamera& now = hist[0];
    int at = 1;
    for (int i = 2; i < histCount; ++i)
        if (std::abs(hist[i].time - (now.time - exposure)) < std::abs(hist[at].time - (now.time - exposure)))
            at = i;
    const UnderCamera& then = hist[at];
    const double dt = now.time - then.time;
    if (dt < 1e-4)
        return;
    const float perSecond = static_cast<float>(1.0 / dt);
    v = offset(then.pos, now.pos) * perSecond;
    vp = offset(then.player, now.player) * perSecond;
    const Turn turn = turnBetween(then, now);
    w = turn.sinA > 1e-9f ? turn.s * (turn.angle / turn.sinA * perSecond) : Vec3{};
}

// The camera of the frame being drawn: the game captured it in this very frame (the overlay's camera is three frames behind, for Present).
void CameraMotion::advance(double exposure) {
    const SetupAndRenderHook::Transform t = SetupAndRenderHook::newest();
    UnderCamera c = UnderGpu::cameraOf(t);
    c.seq = t.seq;
    if (c.valid && c.seq != seq) {
        seq = c.seq;
        observe(c);
    }
    over(exposure);
}

// Does the camera move during an exposure of this length?
bool CameraMotion::moving(float exposure) const {
    return valid && cur.valid && (std::max(v.length(), vp.length()) * exposure > 1e-4f || w.length() * exposure > 2e-5f);
}

// The player's box on the screen (uv, a little wider), when the camera is away from the head (third person) and the whole box is in front of it.
bool CameraMotion::playerRect(float out[4], float& depthOut) const {
    const UnderCamera& c = cur;
    const float ex = c.pos[0] - c.player[0], ey = c.pos[1] - c.player[1], ez = c.pos[2] - c.player[2];
    if (ex * ex + ey * ey + ez * ez < 1.5f * 1.5f)
        return false;
    const float x0 = c.player[0] - 0.5f, x1 = c.player[0] + 0.5f, z0 = c.player[2] - 0.5f, z1 = c.player[2] + 0.5f;
    const float y0 = c.player[1] - 1.62f - 0.15f, y1 = c.player[1] - 1.62f + 2.0f; // the foot is 1.62 below the eye; room for the arms and what is held
    float mnU = 1e9f, mnV = 1e9f, mxU = -1e9f, mxV = -1e9f;
    for (int i = 0; i < 8; ++i) {
        const float rx = ((i & 1) ? x1 : x0) - c.pos[0], ry = ((i & 2) ? y1 : y0) - c.pos[1], rz = ((i & 4) ? z1 : z0) - c.pos[2];
        const float zz = c.fwd[0] * rx + c.fwd[1] * ry + c.fwd[2] * rz;
        if (zz < 0.1f)
            return false;
        const float nx = (c.right[0] * rx + c.right[1] * ry + c.right[2] * rz) / zz * c.fov[0];
        const float ny = (c.up[0] * rx + c.up[1] * ry + c.up[2] * rz) / zz * c.fov[1];
        const float u = nx * 0.5f + 0.5f, v = 0.5f - ny * 0.5f;
        mnU = std::min(mnU, u);
        mxU = std::max(mxU, u);
        mnV = std::min(mnV, v);
        mxV = std::max(mxV, v);
    }
    const float cx = c.player[0] - c.pos[0], cy = c.player[1] - 0.72f - c.pos[1], cz = c.player[2] - c.pos[2]; // the middle of the player: 0.9 above the foot
    depthOut = c.fwd[0] * cx + c.fwd[1] * cy + c.fwd[2] * cz;
    const float mu = (mxU - mnU) * 0.08f + 0.005f, mv = (mxV - mnV) * 0.08f + 0.005f;
    out[0] = UiMath::clamp01(mnU - mu);
    out[1] = UiMath::clamp01(mnV - mv);
    out[2] = UiMath::clamp01(mxU + mu);
    out[3] = UiMath::clamp01(mxV + mv);
    return out[2] > out[0] && out[3] > out[1];
}

