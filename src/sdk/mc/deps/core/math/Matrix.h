#pragma once
#include "sdk/mc/deps/core/math/Vec.h"
#include "sdk/Layout.h"

// Single float[16] (64B). Game thunks (rotate / scale /
// translate / ctors) need game linkage, stubbed null-safe here.
// projectWorld uses absolute transform with layout proven live
// (eye-match picks row vs col + forward + translation).

struct Matrix {
    float m[16]{};

    constexpr Matrix() = default;

    const float* data() const { return m; }
    float* data() { return m; }

    bool operator==(const Matrix& o) const {
        if (this == &o)
            return true;
        return std::memcmp(m, o.m, sizeof(m)) == 0;
    }

    static const Matrix& identity() {
        static const Matrix kId = [] {
            Matrix v{};
            v.m[0] = 1.f;
            v.m[5] = 1.f;
            v.m[10] = 1.f;
            v.m[15] = 1.f;
            return v;
        }();
        return kId;
    }

    // Mutators below need game linkage; stub-only carriers here.
    // TODO: wire rotate/scale/translate when a caller needs them.
    void rotate(float, const Vec3&) { sdkLogStub("Matrix::rotate"); }
    void rotate(float, float, float, float) { sdkLogStub("Matrix::rotate"); }
    void rotateXYZ(const Vec3&) { sdkLogStub("Matrix::rotateXYZ"); }
    void scale(float) { sdkLogStub("Matrix::scale"); }
    void scale(float, float, float) { sdkLogStub("Matrix::scale"); }
    void translate(const Vec3&) { sdkLogStub("Matrix::translate"); }
    void translate(float, float, float) { sdkLogStub("Matrix::translate"); }
};
static_assert(sizeof(Matrix) == 64);
