#pragma once
// 10x bool + uint64 field counts.
namespace mce {
struct MeshDataVertexFieldCounts {
    bool mPositions         = false;
    bool mNormals           = false;
    bool mTangents          = false;
    bool mIndices           = false;
    bool mColors            = false;
    bool mBoneId0s          = false;
    bool mTextureUVs        = false;
    bool mPBRTextureIndices = false;
    bool mMERSs             = false;
    bool mGeoType           = false;
    uint64_t mCount         = 0;
};
} // namespace mce
