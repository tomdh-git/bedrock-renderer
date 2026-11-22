#include "client/features/render/draw/World.h"
#include "client/features/hooks/hooks/render/SetupAndRenderHook.h"
#include "sdk/csgo/game/client/c_baseviewmodel/ViewmodelSway.h"

// World to screen, on the transform captured by SetupAndRenderHook: the view matrix rows applied to the point relative to
// the camera, scaled by the projection scale of the level renderer.
bool WorldUtils::worldToScreen(const Vec3& world, ImVec2& out) {
    const auto& t = SetupAndRenderHook::transform;
    const float px = world.x - t.origin.x, py = world.y - t.origin.y, pz = world.z - t.origin.z;
    const float* m = t.view.m;
    const float x = m[0] * px + m[1] * py + m[2] * pz + m[3];
    const float y = m[4] * px + m[5] * py + m[6] * pz + m[7];
    const float z = m[8] * px + m[9] * py + m[10] * pz + m[11];
    if (z > 0)
        return false;
    const ImVec2 size = ImGui::GetIO().DisplaySize;
    const float mx = size.x / 2.f, my = size.y / 2.f;
    out = ImVec2(mx + (mx * x / -z * t.fov.x), my - (my * y / -z * t.fov.y));
    return !(out.x > size.x * 2 || out.y > size.y * 2); // too far off screen
}

static void corners(const Vec3& a, const Vec3& b, Vec3 out[8]) {
    out[0] = Vec3(a.x, a.y, a.z);
    out[1] = Vec3(a.x, a.y, b.z);
    out[2] = Vec3(b.x, a.y, a.z);
    out[3] = Vec3(b.x, a.y, b.z);
    out[4] = Vec3(a.x, b.y, a.z);
    out[5] = Vec3(a.x, b.y, b.z);
    out[6] = Vec3(b.x, b.y, a.z);
    out[7] = Vec3(b.x, b.y, b.z);
}

std::vector<ImVec2> WorldUtils::boxPoints(const Vec3& min, const Vec3& max) {
    Vec3 world[8];
    corners(min, max, world);
    std::vector<ImVec2> points;
    for (const Vec3& w : world) {
        ImVec2 p;
        if (!worldToScreen(w, p))
            return {};
        points.push_back(p);
    }
    constexpr float kPi = 3.14159265358979f;
    const ImVec2 start = *std::min_element(points.begin(), points.end(), [](const ImVec2& a, const ImVec2& b) { return a.x < b.x; });
    std::vector<ImVec2> outline{start};
    ImVec2 current = start, lastDir(0.f, -1.f);
    do {
        float smallestAngle = 2 * kPi;
        ImVec2 smallestDir(0.f, 0.f), smallestE(0.f, 0.f);
        const float lastAngle = atan2f(lastDir.y, lastDir.x);
        for (const ImVec2& t : points) {
            if (current.x == t.x && current.y == t.y)
                continue;
            const ImVec2 dir(t.x - current.x, t.y - current.y);
            float angle = atan2f(dir.y, dir.x) - lastAngle;
            if (angle > kPi)
                angle -= 2 * kPi;
            else if (angle <= -kPi)
                angle += 2 * kPi;
            if (angle >= 0 && angle < smallestAngle) {
                smallestAngle = angle;
                smallestDir = dir;
                smallestE = t;
            }
        }
        outline.push_back(smallestE);
        lastDir = smallestDir;
        current = smallestE;
    } while ((current.x != start.x || current.y != start.y) && outline.size() < 8);
    return outline;
}

ImVec4 WorldUtils::boxRect(const Vec3& min, const Vec3& max) {
    Vec3 world[8];
    corners(min, max, world);
    std::vector<ImVec2> points;
    for (const Vec3& w : world) {
        ImVec2 p;
        if (worldToScreen(w, p))
            points.push_back(p);
    }
    if (points.size() < 2)
        return ImVec4(0.f, 0.f, 0.f, 0.f);
    ImVec4 r(points[0].x, points[0].y, points[0].x, points[0].y);
    for (const ImVec2& p : points) {
        r.x = (std::min)(r.x, p.x);
        r.y = (std::min)(r.y, p.y);
        r.z = (std::max)(r.z, p.x);
        r.w = (std::max)(r.w, p.y);
    }
    return r;
}
