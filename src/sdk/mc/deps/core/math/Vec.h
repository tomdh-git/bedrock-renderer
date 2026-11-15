#pragma once

// Vec2 {x, y} / Vec3 {x, y, z} / Vec4 {x, y, z, w}. No glm dep.
// Pure-math members implemented here; game-needing thunks omitted
// (construction is game-side only).

struct Vec2 {
    float x = 0.f;
    float y = 0.f;

    constexpr Vec2() = default;
    constexpr Vec2(float ax, float ay) : x(ax), y(ay) {}

    constexpr bool operator==(const Vec2& o) const { return x == o.x && y == o.y; }
    constexpr Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    constexpr Vec2 operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
    constexpr Vec2 operator*(float s) const { return {x * s, y * s}; }

    static Vec2 zero() { return {0.f, 0.f}; }
    static Vec2 one() { return {1.f, 1.f}; }
};
static_assert(sizeof(Vec2) == 8);

struct Vec3 {
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    constexpr Vec3() = default;
    constexpr Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}

    constexpr bool operator==(const Vec3& o) const { return x == o.x && y == o.y && z == o.z; }
    constexpr Vec3 operator+(const Vec3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    constexpr Vec3 operator-(const Vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    constexpr Vec3 operator*(float s) const { return {x * s, y * s, z * s}; }

    float length() const { return std::sqrt(x * x + y * y + z * z); }
    float dot(const Vec3& o) const { return x * o.x + y * o.y + z * o.z; }
    constexpr Vec3 cross(const Vec3& o) const { return {y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x}; }
    // This vector turned by `angle` radians around the unit axis k (Rodrigues).
    Vec3 rotatedAround(const Vec3& k, float angle) const {
        const float c = std::cos(angle), s = std::sin(angle);
        return *this * c + k.cross(*this) * s + k * (k.dot(*this) * (1.0f - c));
    }
    static constexpr Vec3 of(const float* v) { return {v[0], v[1], v[2]}; }

    std::string toString() const {
        char b[96]{};
        snprintf(b, sizeof(b), "[%.3f, %.3f, %.3f]", x, y, z);
        return std::string(b);
    }

    // directionFromRotation(rotX, rotY): pitch/yaw -> unit dir.
    static Vec3 directionFromRotation(float rotX, float rotY) {
        float xr = rotX * 0.0174532925f;
        float yr = rotY * 0.0174532925f;
        float cx = std::cos(xr);
        return {-std::sin(yr) * cx, -std::sin(xr), std::cos(yr) * cx};
    }
    static Vec3 directionFromRotation(const Vec2& rot) {
        return directionFromRotation(rot.x, rot.y);
    }

    static Vec3 zero() { return {0.f, 0.f, 0.f}; }
    static Vec3 one() { return {1.f, 1.f, 1.f}; }
    static Vec3 unitX() { return {1.f, 0.f, 0.f}; }
    static Vec3 unitY() { return {0.f, 1.f, 0.f}; }
    static Vec3 unitZ() { return {0.f, 0.f, 1.f}; }
    static Vec3 min() { return {-3.40282347e+38f, -3.40282347e+38f, -3.40282347e+38f}; }
    static Vec3 max() { return {3.40282347e+38f, 3.40282347e+38f, 3.40282347e+38f}; }
};
static_assert(sizeof(Vec3) == 12);

struct Vec4 {
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
    float w = 0.f;

    constexpr Vec4() = default;
    constexpr Vec4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}

    constexpr bool operator==(const Vec4& o) const {
        return x == o.x && y == o.y && z == o.z && w == o.w;
    }

    static Vec4 one() { return {1.f, 1.f, 1.f, 1.f}; }
    static Vec4 min() { return {-3.40282347e+38f, -3.40282347e+38f, -3.40282347e+38f, -3.40282347e+38f}; }
    static Vec4 max() { return {3.40282347e+38f, 3.40282347e+38f, 3.40282347e+38f, 3.40282347e+38f}; }
};
static_assert(sizeof(Vec4) == 16);
