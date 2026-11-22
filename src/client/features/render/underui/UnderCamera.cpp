#include "client/features/render/underui/UnderGpuPrivate.h"
#include "client/platform/window/Window.h"
#include "client/platform/time/Time.h"

// ---- camera and projection -------------------------------------------------------------------------------------------------

UnderCamera UnderGpu::cameraOf(const SetupAndRenderHook::Transform& t) {
    UnderCamera c;
    c.valid = t.fov.x > 0.01f && t.fov.y > 0.01f;
    if (c.valid) {
        const float* m = t.view.m;
        for (int k = 0; k < 3; ++k) {
            c.right[k] = m[k];
            c.up[k] = m[4 + k];
            c.fwd[k] = -m[8 + k];
        }
        // The world is drawn relative to an origin and the view matrix carries the rest of the camera's position (a world point P is at R (P - origin) + t in
        // the view, rows of R: right, up, back): the camera is where that is zero, origin - R^T t. When the origin is the camera itself t is zero and this is
        // the origin; when the origin moves in coarse steps, t is the movement between them, and the camera's real movement is in it.
        const float tx = m[3], ty = m[7], tz = m[11];
        c.pos[0] = t.origin.x - (tx * m[0] + ty * m[4] + tz * m[8]);
        c.pos[1] = t.origin.y - (tx * m[1] + ty * m[5] + tz * m[9]);
        c.pos[2] = t.origin.z - (tx * m[2] + ty * m[6] + tz * m[10]);
        c.fov[0] = t.fov.x;
        c.fov[1] = t.fov.y;
        c.player[0] = t.playerPos.x;
        c.player[1] = t.playerPos.y;
        c.player[2] = t.playerPos.z;
        c.time = t.time;
    }
    return c;
}

UnderCamera UnderGpu::camera() {
    std::lock_guard<std::mutex> lk(UnderGpuPrivate::camMu);
    return UnderGpuPrivate::cam;
}

void UnderGpu::setCamera(const UnderCamera& c) {
    std::lock_guard<std::mutex> lk(UnderGpuPrivate::camMu);
    UnderGpuPrivate::cam = c;
}

// Looks for the projection in the client instance each frame in a world until one is found (the level renderer's own is taken when it is available).
void UnderGpu::discoverProjection(HWND window) {
    static bool done = false;
    static int attempts = 0;
    if (done || attempts > 600)
        return;
    ClientInstance* ci = ClientInstance::get();
    if (!ci || !ci->getLocalPlayer())
        return;
    const SIZE client = Platform::Window::clientSize(window);
    if (client.cy <= 0)
        return;
    ++attempts;
    if (const float* m = ci->findProjectionMatrix(static_cast<float>(client.cx) / static_cast<float>(client.cy)))
        done = setProjection(m);
    if (attempts == 600)
        Logger::warn("[underui] no projection matrix found in the client instance: the smooth fog and the depth based effects need it and stay off");
}

// The level renderer's projection (row after row, the perspective divide in [11]): [10] and [14] hold the depth mapping. Both conventions of it give a
// near and a far plane (Direct3D's z in 0..1, OpenGL's -1..1); Bedrock's near plane is 0.05, which tells them apart.
bool UnderGpu::setProjection(const float* m) {
    auto near0 = [](float v) { return std::fabs(v) < 1e-4f; };
    if (!(m[0] > 0.2f && m[0] < 30.f && m[5] > 0.2f && m[5] < 60.f && near0(m[1]) && near0(m[2]) && near0(m[3]) && near0(m[4]) && near0(m[6]) && near0(m[7]) &&
            near0(m[12]) && near0(m[13]) && near0(m[15]) && std::fabs(std::fabs(m[11]) - 1.0f) < 1e-3f))
        return false;
    const float a = m[10], b = m[14];
    auto plausible = [](float n, float f) { return n > 0.005f && n < 2.0f && f > n * 20.0f && f < 20000.0f; };
    const float dxn = b / a, dxf = b / (a + 1.0f);  // Direct3D: z = f / (n - f) * (d - n) / d
    const float gln = b / (a - 1.0f), glf = b / (a + 1.0f); // OpenGL
    const bool dx = plausible(dxn, dxf), gl = plausible(gln, glf);
    if (!dx && !gl)
        return false;
    const bool useDx = dx && (!gl || std::fabs(dxn - 0.05f) <= std::fabs(gln - 0.05f));
    const float n = useDx ? dxn : gln, f = useDx ? dxf : glf;
    // The planes feed the fog's range, the depth every pass linearises and the LCE twins' fog distance. The matrix is read once a frame from the level renderer, and
    // a frame in which it holds another view's projection (or a value the game is half way through changing) must not reach any of them: that frame's fog, blur and
    // depth-tested passes would be drawn with the wrong distances, which shows as a flash. Planes that differ from the published ones are taken once the same new
    // pair has been read three frames running (a render distance change settles in three frames; a one-frame stray never does). The first pair is taken at once.
    static float sSeenNear = 0.f, sSeenFar = 0.f;
    static int sSeenFrames = 0;
    const auto same = [](float a, float b) { return std::fabs(a - b) <= 0.005f * std::max(std::fabs(a), std::fabs(b)); };
    const float haveNear = nearPlane.load(), haveFar = farPlane.load();
    if (haveNear > 0.f && !(same(n, haveNear) && same(f, haveFar))) {
        if (same(n, sSeenNear) && same(f, sSeenFar))
            ++sSeenFrames;
        else {
            sSeenNear = n;
            sSeenFar = f;
            sSeenFrames = 1;
        }
        if (sSeenFrames < 3)
            return true; // a projection was read: the published planes stand
    }
    sSeenFrames = 0;
    nearPlane.store(n);
    farPlane.store(f);
    return true;
}
