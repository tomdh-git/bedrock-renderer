#pragma once
#include "sdk/mc/deps/core/math/Vec.h"

// Layout: total + client + clientUI sizes. Value type inside GuiData; no offsets.
struct ScreenSizeData {
    Vec2 totalScreenSize{};
    Vec2 clientScreenSize{};
    Vec2 clientUIScreenSize{};
};
static_assert(sizeof(ScreenSizeData) == 24);
