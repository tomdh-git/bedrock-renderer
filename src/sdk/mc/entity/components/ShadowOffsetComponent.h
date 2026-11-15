#pragma once

// Layout and hash of this build.
struct ShadowOffsetComponent {
    static constexpr uint32_t enttHash = 0x42F8AFFA;
    float mOffset;
};
static_assert(sizeof(ShadowOffsetComponent) == 4);
