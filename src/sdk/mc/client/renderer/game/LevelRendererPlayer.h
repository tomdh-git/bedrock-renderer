#pragma once
#include "sdk/OffsetProvider.h"

// LevelRendererPlayer's members that the client reads (mFov at +0x1238 is not the live camera FOV on 26.51; the live camera position and FOV come from
// the first-person CameraComponent, see CameraHook). The projection matrix is the level renderer's own, which is what the screen projection and the
// sky/fog depth mapping need.
struct LevelRendererPlayer {
    Vec3 cameraPos() const { return at<Vec3>(OffsetProvider::LevelRendererPlayer_mCameraPos); }
    Vec2 fovScale() const { return Vec2{at<float>(OffsetProvider::LevelRendererPlayer_mFovX), at<float>(OffsetProvider::LevelRendererPlayer_mFovY)}; }
    void projection(float out[16]) const { memcpy(out, reinterpret_cast<const uint8_t*>(this) + OffsetProvider::LevelRendererPlayer_mProjection, 16 * sizeof(float)); }

private:
    template <typename T>
    T at(size_t offset) const { return *reinterpret_cast<const T*>(reinterpret_cast<const uint8_t*>(this) + offset); }
};
