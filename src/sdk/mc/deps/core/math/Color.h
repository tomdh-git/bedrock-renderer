#pragma once
// Color is floatN4 {r, g, b, a} (16B).
// Ctors and helpers need game math; omitted (stub-only carrier).
namespace mce {
struct Color {
    float r = 0.f;
    float g = 0.f;
    float b = 0.f;
    float a = 1.f;
};
} // namespace mce
