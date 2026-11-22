#pragma once

// World <-> screen helpers for overlays. Valid on the render thread, from the view and camera of the latest world frame.
struct WorldUtils {
    // Screen position of a world point; false when it is behind the camera.
    static bool worldToScreen(const Vec3& world, ImVec2& out);
    // getBoxPoints: the outline of a box on screen (gift wrapping over the eight projected corners), empty when
    // any corner is behind the camera.
    static std::vector<ImVec2> boxPoints(const Vec3& min, const Vec3& max);
    // getRectFromAABB: the rectangle around the projected corners, all zero when fewer than two are in front.
    static ImVec4 boxRect(const Vec3& min, const Vec3& max);
};
