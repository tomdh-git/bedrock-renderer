#pragma once
#include "sdk/mc/deps/core/math/Vec.h"
#include "sdk/mc/deps/core_graphics/enums/PrimitiveMode.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/MeshDataVertexFieldCounts.h"
// Member order mirrors the game header. std::vector (24B MSVC); no numeric
// offsets are used.

namespace mce {

class MeshData {
public:
    using Index = unsigned int;

    PrimitiveMode mMode = PrimitiveMode::None;
    std::vector<Vec3> mPositions;
    std::vector<Vec4> mNormals;
    std::vector<Vec4> mTangents;
    std::vector<unsigned int> mIndices;
    std::vector<unsigned int> mColors;
    std::vector<unsigned short> mBoneId0s;
    std::vector<Vec2> mTextureUVs[3];
    std::vector<unsigned short> mPBRTextureIndices;
    std::vector<unsigned int> mMERS;
    std::vector<unsigned char> mGeoType;
    std::pair<Vec3, Vec3> mAABB{};
    std::pair<Vec2, Vec2> mUVAABB{};
    std::array<bool, 15> mFieldEnabled{};

    const std::vector<Vec3>* positions() const {
        return &mPositions;
    }
    const std::vector<Vec4>* normals() const {
        return &mNormals;
    }
    const std::vector<Vec4>* tangents() const {
        return &mTangents;
    }
    const std::vector<unsigned int>* indices() const {
        return &mIndices;
    }
    const std::vector<unsigned int>* colors() const {
        return &mColors;
    }
    const std::vector<Vec2>* uvs(unsigned int channel) const {
        if (channel >= 3)
            return nullptr;
        return &mTextureUVs[channel];
    }

    uint64_t size() const {
        return static_cast<uint64_t>(mPositions.size());
    }

    MeshDataVertexFieldCounts getVertexFieldCount() const {
        MeshDataVertexFieldCounts out{};
        out.mPositions         = !mPositions.empty();
        out.mNormals           = !mNormals.empty();
        out.mTangents          = !mTangents.empty();
        out.mIndices           = !mIndices.empty();
        out.mColors            = !mColors.empty();
        out.mBoneId0s          = !mBoneId0s.empty();
        out.mTextureUVs        = !mTextureUVs[0].empty() || !mTextureUVs[1].empty() || !mTextureUVs[2].empty();
        out.mPBRTextureIndices = !mPBRTextureIndices.empty();
        out.mMERSs             = !mMERS.empty();
        out.mGeoType           = !mGeoType.empty();
        out.mCount             = static_cast<uint64_t>(mPositions.size());
        return out;
    }

    void clear() {
        mPositions.clear();
        mNormals.clear();
        mTangents.clear();
        mIndices.clear();
        mColors.clear();
        mBoneId0s.clear();
        mTextureUVs[0].clear();
        mTextureUVs[1].clear();
        mTextureUVs[2].clear();
        mPBRTextureIndices.clear();
        mMERS.clear();
        mGeoType.clear();
    }

    void freeMemory() {
        clear();
        mPositions.shrink_to_fit();
        mNormals.shrink_to_fit();
        mTangents.shrink_to_fit();
        mIndices.shrink_to_fit();
        mColors.shrink_to_fit();
        mBoneId0s.shrink_to_fit();
        mTextureUVs[0].shrink_to_fit();
        mTextureUVs[1].shrink_to_fit();
        mTextureUVs[2].shrink_to_fit();
        mPBRTextureIndices.shrink_to_fit();
        mMERS.shrink_to_fit();
        mGeoType.shrink_to_fit();
    }
};

// Layout checked against the 1.26.62.01 binary (docs/BGFX_MAP.md 6ho): MeshData::clear 0x4df0440 empties the vectors at exactly these
// offsets, resets mAABB / mUVAABB to FLT_MAX / -FLT_MAX and zeroes the 15 mFieldEnabled bytes; it is embedded at RenderControllerMesh+0x50.
static_assert(sizeof(MeshData) == 0x160);
static_assert(offsetof(MeshData, mPositions) == 0x08);
static_assert(offsetof(MeshData, mNormals) == 0x20);
static_assert(offsetof(MeshData, mTangents) == 0x38);
static_assert(offsetof(MeshData, mIndices) == 0x50);
static_assert(offsetof(MeshData, mColors) == 0x68);
static_assert(offsetof(MeshData, mBoneId0s) == 0x80);
static_assert(offsetof(MeshData, mTextureUVs) == 0x98);
static_assert(offsetof(MeshData, mPBRTextureIndices) == 0xE0);
static_assert(offsetof(MeshData, mMERS) == 0xF8);
static_assert(offsetof(MeshData, mGeoType) == 0x110);
static_assert(offsetof(MeshData, mAABB) == 0x128);
static_assert(offsetof(MeshData, mUVAABB) == 0x140);
static_assert(offsetof(MeshData, mFieldEnabled) == 0x150);

} // namespace mce
