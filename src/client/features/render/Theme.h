#pragma once
#include "client/platform/time/Time.h"

namespace Render {



// Client-wide animated accent gradient, fed by Interface's Primary /
// Secondary pickers. Screen-space diagonal flow (position + time phase),
// sampled per-vertex like the reference: separate shapes that touch share
struct Theme {
    static inline ImU32 gradA = IM_COL32(64, 186, 255, 255);
    static inline ImU32 gradB = IM_COL32(26, 134, 255, 255);
    static constexpr float gpCycle = 240.f; // one full sweep of the flow along its axis, in gp units (2 * the 120 of sampleRGB's sampling)

    static void set(ImU32 a, ImU32 b) {
        gradA = a | 0xFF000000;
        gradB = b | 0xFF000000;
    }

    // Moves the gradient toward a target instead of snapping (a pack colour arriving after the first frames, a picker changing): the first call lands on it.
    static void setEased(ImU32 a, ImU32 b, float dt) {
        static bool sStarted = false;
        static float cur[6] = {};
        const float to[6] = {float(a & 255), float((a >> 8) & 255), float((a >> 16) & 255), float(b & 255), float((b >> 8) & 255), float((b >> 16) & 255)};
        const float k = sStarted ? 1.f - expf(-dt * 7.f) : 1.f;
        sStarted = true;
        for (int i = 0; i < 6; ++i)
            cur[i] += (to[i] - cur[i]) * k;
        auto pack = [](const float* c) { return IM_COL32(int(c[0] + 0.5f), int(c[1] + 0.5f), int(c[2] + 0.5f), 255); };
        gradA = pack(cur);
        gradB = pack(cur + 3);
    }

    static int clampA(int a) { return a < 0 ? 0 : (a > 255 ? 255 : a); }

    static void sampleRGB(float x, float y, float& r, float& g, float& b, bool flip = false) {
        float gp = (flip ? -(x + y) : (x + y)) * 0.7071f;
        const float speed = 3.f, sep = 120.f;
        float time = 10000.f / speed;
        float phase = gp * (time * 0.5f) / sep;
        float now = (float)(Platform::Time::millis() % 100000);
        float ang = fmodf(now + phase, time);
        float seg = time * 0.5f;
        float t = ang / seg;
        int idx = (int)t;
        float f = t - (float)idx;
        float ar = (float)(gradA & 255), ag = (float)((gradA >> 8) & 255), ab = (float)((gradA >> 16) & 255);
        float br = (float)(gradB & 255), bg = (float)((gradB >> 8) & 255), bb = (float)((gradB >> 16) & 255);
        if (idx == 0) {
            r = ar + (br - ar) * f;
            g = ag + (bg - ag) * f;
            b = ab + (bb - ab) * f;
        } else {
            r = br + (ar - br) * f;
            g = bg + (ag - bg) * f;
            b = bb + (ab - bb) * f;
        }
        // Slight brightness lift so picked themes don't render dark.
        constexpr float kLift = 0.05f;
        r += (255.f - r) * kLift;
        g += (255.f - g) * kLift;
        b += (255.f - b) * kLift;
    }

    static ImU32 sample(float x, float y, int a, bool flip = false) {
        float r, g, b;
        sampleRGB(x, y, r, g, b, flip);
        a = clampA(a);
        return IM_COL32((int)r, (int)g, (int)b, a);
    }

    // Retint a vertex span by position, preserving per-vertex alpha.
    static void shadeRange(ImDrawList* d, int vs, int ve, bool flip = false) {
        if (!d || vs >= ve) return;
        if (vs < 0) vs = 0;
        if (ve > d->VtxBuffer.Size) ve = d->VtxBuffer.Size;
        for (int i = vs; i < ve; i++) {
            ImDrawVert& v = d->VtxBuffer[i];
            ImVec4 c = ImGui::ColorConvertU32ToFloat4(v.col);
            float r, g, b;
            sampleRGB(v.pos.x, v.pos.y, r, g, b, flip);
            v.col = ImGui::ColorConvertFloat4ToU32(ImVec4(r / 255.f, g / 255.f, b / 255.f, c.w));
        }
    }

    // Gradient fill = white shape + shadeRange recolor
    // of exactly the vertices that shape just added.
    static void fillRect(ImDrawList* d, ImVec2 mn, ImVec2 mx, int a, bool flip = false) {
        int vs = d->VtxBuffer.Size;
        d->AddRectFilled(mn, mx, IM_COL32(255, 255, 255, clampA(a)));
        shadeRange(d, vs, d->VtxBuffer.Size, flip);
    }

    static void fillRounded(ImDrawList* d, ImVec2 mn, ImVec2 mx, float r, ImDrawFlags flags, int a,
                            bool flip = false) {
        int vs = d->VtxBuffer.Size;
        d->AddRectFilled(mn, mx, IM_COL32(255, 255, 255, clampA(a)), r, flags);
        shadeRange(d, vs, d->VtxBuffer.Size, flip);
    }
};

} // namespace Render
