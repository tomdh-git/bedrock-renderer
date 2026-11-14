#pragma once

struct CameraDirectLookComponent {
    static constexpr uint32_t enttHash = 0x77F3DFE3;

    float mYaw;
    float mPitch;
    float mYawDelta;
    float mPitchMin;
    float mPitchMax;
};
static_assert(sizeof(CameraDirectLookComponent) == 0x14);
