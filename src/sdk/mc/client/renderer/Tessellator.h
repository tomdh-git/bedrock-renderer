#pragma once
#include "sdk/Layout.h"
#include "client/core/diagnostics/Log.h"
#include "sdk/mc/client/renderer/SupplementaryFieldAutoGenerationMode.h"
#include "sdk/mc/deps/core/math/Color.h"
#include "sdk/mc/deps/core/math/Vec.h"
#include "sdk/mc/deps/core_graphics/enums/PrimitiveMode.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/MaterialPtr.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/Mesh.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h"
#include "sdk/mc/deps/minecraft_renderer/resources/BufferResourceService.h"
// Method set mirrors the game header. Body unproven (no Lite-proven offsets).
// Ctors/dtor-thunks omitted (construction is game-side only).
// Real CPU accumulator below carries only the onscene 3-slot path
// (begin/color/vertex/tex2/quad/end into MeshData vectors, v4-exact).
// Game-gpu upload stays game-side; the present flush reads the snapshot.

class Tessellator {
public:
    enum class UploadMode : int {
        Buffered = 0,
        Manual   = 1,
        Never    = 2,
    };

    struct DebugContextCallback {}; // Empty struct

    using Index = unsigned int;

    void begin(DebugContextCallback, mce::PrimitiveMode mode, int, bool) {
        mPos.clear();
        mUv.clear();
        mCol.clear();
        mIdx.clear();
        mMode  = mode;
        mBegun = true;
    }
    void beginOverride(DebugContextCallback) {
        sdkLogStub("Tessellator::beginOverride");
    }
    void clear() {
        mPos.clear();
        mUv.clear();
        mCol.clear();
        mIdx.clear();
        mBegun = false;
    }
    void color(const mce::Color& c) {
        mCurR = c.r;
        mCurG = c.g;
        mCurB = c.b;
        mCurA = c.a;
    }
    void color(float r, float g, float b, float a) {
        mCurR = r;
        mCurG = g;
        mCurB = b;
        mCurA = a;
    }
    mce::Mesh end(UploadMode, std::string_view, SupplementaryFieldAutoGenerationMode) {
        if (!mBegun)
            Logger::fatal("[tess] fatal: end without begin");
        if (mPos.empty())
            Logger::fatal("[tess] fatal: end with no verts");
        mce::Mesh mesh{};
        mesh.mMeshData = meshSnapshot();
        return mesh;
    }
    void quad(unsigned int a, unsigned int b, unsigned int c, unsigned int d) {
        if (!mBegun)
            Logger::fatal("[tess] fatal: quad without begin");
        size_t n = mPos.size();
        if (a >= n || b >= n || c >= n || d >= n)
            Logger::fatal("[tess] fatal: quad idx out of range");
        mIdx.push_back(a);
        mIdx.push_back(b);
        mIdx.push_back(c);
        mIdx.push_back(a);
        mIdx.push_back(c);
        mIdx.push_back(d);
    }
    void vertex(float x, float y, float z) {
        if (!mBegun)
            Logger::fatal("[tess] fatal: vertex without begin");
        mPos.push_back(Vec3{x, y, z});
        mUv.push_back(Vec2{0.0f, 0.0f});
        mCol.push_back(pack(mCurR, mCurG, mCurB, mCurA));
    }
    void tex2(const Vec2& uv) {
        if (!mBegun)
            Logger::fatal("[tess] fatal: tex2 without begin");
        if (mPos.empty())
            Logger::fatal("[tess] fatal: tex2 with no verts");
        if (mUv.size() != mPos.size())
            Logger::fatal("[tess] fatal: tex2 count mismatch");
        mUv.back() = uv;
    }
    void addRotation(float, const Vec3&) {
        sdkLogStub("Tessellator::addRotation");
    }
    void addTranslation(const Vec3&) {
        sdkLogStub("Tessellator::addTranslation");
    }
    void resetTransform(bool) {
        sdkLogStub("Tessellator::resetTransform");
    }
    void rotateAroundPivot(const Vec3&, float, const Vec3&, bool) {
        sdkLogStub("Tessellator::rotateAroundPivot");
    }
    void setTessellateIntercept(
        std::function<void(const Tessellator&, const mce::MaterialPtr&, const mce::TexturePtr&)>) {
        sdkLogStub("Tessellator::setTessellateIntercept");
    }
    void simpleQuad(
        const Vec3&, const Vec2&, const Vec3&, const Vec2&, const Vec3&, const Vec2&, const Vec3&,
        const Vec2&) {
        sdkLogStub("Tessellator::simpleQuad");
    }
    void triggerIntercept(const mce::MaterialPtr&, const mce::TexturePtr&) {
        sdkLogStub("Tessellator::triggerIntercept");
    }

    // Present-submit snapshot: exact vectors fed since begin (no game addr).
    bool hasData() const {
        return !mPos.empty();
    }
    mce::MeshData meshSnapshot() const {
        mce::MeshData d{};
        d.mMode         = mMode;
        d.mPositions    = mPos;
        d.mTextureUVs[0] = mUv;
        d.mColors       = mCol;
        if (mIdx.empty()) {
            d.mIndices.resize(mPos.size());
            for (size_t i = 0; i < mPos.size(); ++i)
                d.mIndices[i] = static_cast<unsigned int>(i);
        } else {
            d.mIndices = mIdx;
        }
        return d;
    }
    mce::Color currentColor() const {
        return {mCurR, mCurG, mCurB, mCurA};
    }

private:
    static unsigned int pack(float r, float g, float b, float a) {
        auto q = [](float v) {
            if (v < 0.0f)
                return 0;
            if (v > 1.0f)
                return 255;
            return static_cast<int>(v * 255.0f);
        };
        return static_cast<unsigned int>(q(r) | (q(g) << 8) | (q(b) << 16) | (q(a) << 24));
    }

    bool mBegun = false;
    mce::PrimitiveMode mMode = mce::PrimitiveMode::None;
    std::vector<Vec3> mPos;
    std::vector<Vec2> mUv;
    std::vector<unsigned int> mCol;
    std::vector<unsigned int> mIdx;
    float mCurR = 1.0f;
    float mCurG = 1.0f;
    float mCurB = 1.0f;
    float mCurA = 1.0f;
};
