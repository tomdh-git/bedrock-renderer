#pragma once

// What the chams pass draws with. The Chams module pushes it every frame (Chams::onFrame); the pass never reads the module.
struct ChamsFeed {
    static void publish(bool on, bool actor, bool fill, bool outline, bool glow, float fillOpacity, float outlineWidth, float glowRadius);
};
