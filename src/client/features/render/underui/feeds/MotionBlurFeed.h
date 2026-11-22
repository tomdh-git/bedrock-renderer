#pragma once

// What the motion blur passes draw with. The MotionBlur module pushes it every frame (MotionBlur::onFrame); the passes never read the module.
struct MotionBlurFeed {
    static void publish(bool on, bool nameTags, bool depthOfField, float aperture, bool autoFocus, float focusDistance, float shutter, bool keepOwnPlayerSharp, int quality,
                        bool fastGather, float focusSpeed);
    // The nametag blur runs only with the module on and its option set, and the world drawn (the pass checks the last).
    static bool nameTagsWanted() { return nameTagsOn.load(std::memory_order_acquire); }

private:
    static inline std::atomic<bool> nameTagsOn{false};
};
