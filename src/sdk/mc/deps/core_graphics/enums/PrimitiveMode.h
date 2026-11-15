#pragma once
// Primitive mode enum.
namespace mce {
enum class PrimitiveMode : unsigned char {
    None          = 0,
    QuadList      = 1,
    TriangleList  = 2,
    TriangleStrip = 3,
    LineList      = 4,
    LineStrip     = 5,
};
} // namespace mce
