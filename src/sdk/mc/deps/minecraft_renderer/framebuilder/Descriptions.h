#pragma once


namespace mce::framebuilder {

// Reference-counted pointer as the game stores it: object ptr + control block (strong count at ctrl+8).
struct SharedRef {
    void* mPtr;
    void* mCtrl;
};
static_assert(sizeof(SharedRef) == 0x10);

// RenderNametagDescription (Item group tag 1). Built in place by 0x668b6e0, called from the fat clone 0x1127330; both fully reversed
// (docs/functions/668b6e0.md, 1127330.md), every field below is written by that constructor. Size 0x98.
struct RenderNametagDescription {
    void* mOwner;          // +0x00 the nametag source the clone was given (its r8), not the frame builder
    float mMatrix[16];     // +0x08 copy of the newest per-frame camera record (4x4; translation in elements 12..14)
    float mPosition[3];    // +0x48 camera position: the record's translation, or another ring record's when the ring's useAlt flag is set
    SharedRef mShared;     // +0x58 shared object (text/mesh handle)
    uint8_t mRaw68[0x10];  // +0x68 copied from the frame context +0x30
    uint64_t mCtx20;       // +0x78 copied from the frame context +0x20
    uint16_t mFlags;       // +0x80
    float mColor[4];       // +0x84 optional vec4 (valid when mHasColor)
    bool mHasColor;        // +0x94
    uint8_t mPad95[3];
};
static_assert(sizeof(RenderNametagDescription) == 0x98);
static_assert(offsetof(RenderNametagDescription, mShared) == 0x58);
static_assert(offsetof(RenderNametagDescription, mFlags) == 0x80);
static_assert(offsetof(RenderNametagDescription, mHasColor) == 0x94);

// RenderPlayerVisionDescription (Effect group tag 3), built on the stack by the fat clone 0x53e62b0 (docs/functions/53e62b0.md). [V layout]
struct RenderPlayerVisionDescription {
    bool mVisionEffect;  // +0x00 night vision (id 16) or conduit power (id 26) active
    uint8_t mPad01[3];
    float mVisionScale;  // +0x04 vanilla night-vision scale: 1.0, or 0.7 + 0.3 * sin(t * pi * 0.2) in the last 200 ticks
    float mPlayer4D4;    // +0x08 copied from the player actor +0x4D4 [?]
    float mBlockLight;   // +0x0C brightness of the camera block / 16
    float mPulse;        // +0x10 max(0, pulse * dimension value * 0.45) [I]
};
static_assert(sizeof(RenderPlayerVisionDescription) == 0x14);
static_assert(offsetof(RenderPlayerVisionDescription, mVisionScale) == 0x04);
static_assert(offsetof(RenderPlayerVisionDescription, mPulse) == 0x10);

// RenderCrackDescription (Item group tag 5), one per crack overlay, built on the stack by 0x539fff0 (docs/functions/539fff0.md).
// Field offsets are the clone's stores [V]; the size past +0x24 is not proven [I].
struct RenderCrackDescription {
    const void* mMesh;           // +0x00 the crack entry's mesh (entry +0x00)
    SharedRef mTexture;          // +0x08 the crack material's texture, converted by 0x4dfb570
    const void* mCameraRecord;   // +0x18 pointer to the newest camera record of the extraction ring (not a copy)
    uint8_t mStage;              // +0x20 destroy stage (entry +0x18)
    uint8_t mPad21;
    uint16_t mFlags;             // +0x22 context byte +0x74, widened
    uint8_t mPad24[4];
};
static_assert(offsetof(RenderCrackDescription, mTexture) == 0x08);
static_assert(offsetof(RenderCrackDescription, mCameraRecord) == 0x18);
static_assert(offsetof(RenderCrackDescription, mStage) == 0x20);
static_assert(offsetof(RenderCrackDescription, mFlags) == 0x22);

// RenderCloudsDescription (Sky group tag 1), one per cloud mesh piece, built by 0x668e940 for the clone 0x53e88a0
// (docs/functions/668e940.md). Every field is written by the constructor [V]; the size is the aligned end [I].
struct RenderCloudsDescription {
    float mMatrixA[16];   // +0x00
    float mMatrixB[16];   // +0x40 previous-frame world matrix: the Clouds extractor binds a "PrevWorld" uniform (docs/functions/67375a0.md) [I]
    const void* mMesh;    // +0x80
    float mColor[4];      // +0x88 cloud state +0xA8
    uint8_t mByte98;      // +0x98 cloud state +0xD4
    uint8_t mByte99;      // +0x99 per-piece value from 0x1999140
    uint8_t mByte9A;      // +0x9A
    uint8_t mPad9B;
    uint32_t mValue9C;    // +0x9C optional override, else the default of the parameter at params+0x80
    uint16_t mFlags;      // +0xA0 context byte +0x74
    uint8_t mPadA2[6];
};
static_assert(sizeof(RenderCloudsDescription) == 0xA8);
static_assert(offsetof(RenderCloudsDescription, mMesh) == 0x80);
static_assert(offsetof(RenderCloudsDescription, mColor) == 0x88);
static_assert(offsetof(RenderCloudsDescription, mValue9C) == 0x9C);
static_assert(offsetof(RenderCloudsDescription, mFlags) == 0xA0);

// RenderSkinnedMeshDescription (Item group tag 7), built by the 21-argument constructor 0x668d350 (docs/functions/668d350.md), called
// from the SkinnedMesh producer 0x4e39f20. Every field below is written by the constructor [V]; the size is the aligned end [I].
struct RenderSkinnedMeshDescription {
    float mMatrixA[16];           // +0x000
    float mMatrixB[16];           // +0x040 (current / previous-frame pair [I])
    float mBounds[6];             // +0x080 optional AABB
    uint8_t mBoundsEmpty;         // +0x098 0xFF = no bounds, 0 = valid
    uint8_t mPad099[3];
    float mMeshVec4[4];           // +0x09C mesh +0x190
    uint8_t mPad0AC[4];
    const void* mMesh;            // +0x0B0
    uint32_t mValueB8;            // +0x0B8
    uint8_t mPad0BC[4];
    float mBlockC0[4];            // +0x0C0
    float mBlockD0[4];            // +0x0D0
    SharedRef mRefE0;             // +0x0E0 five shared refs and two bytes from one 0x60-byte source block (bones / geometry [?])
    SharedRef mRefF0;             // +0x0F0
    uint8_t mByte100;             // +0x100
    uint8_t mPad101[7];
    SharedRef mRef108;            // +0x108
    uint8_t mByte118;             // +0x118
    uint8_t mPad119[7];
    SharedRef mRef120;            // +0x120
    SharedRef mRef130;            // +0x130
    SharedRef mMaterial;          // +0x140
    uint8_t mFlags150[4];         // +0x150 four flag bytes
    float mBlock154[4];           // +0x154
    float mBlock164[4];           // +0x164
    uint32_t mValue174;           // +0x174
    uint16_t mCount178;           // +0x178 checked < 0x10000 (throws otherwise)
    uint8_t mPad17A[6];
    uint8_t mVariantHead[0x10];   // +0x180 parameter variant (same shape as the MeshFallback one)
    uint8_t mVariantByte;         // +0x190
    uint8_t mPad191[7];
    uint8_t mVariantPayload[0x18];// +0x198
    uint8_t mVariantIndex;        // +0x1B0 0xFF = empty
    uint8_t mPad1B1[7];
    float mOverride[4];           // +0x1B8 optional vec4
    bool mHasOverride;            // +0x1C8
    uint8_t mPad1C9[3];
    uint16_t mFlags1CC;           // +0x1CC
    uint8_t mByte1CE;             // +0x1CE
    uint8_t mPad1CF;
};
static_assert(sizeof(RenderSkinnedMeshDescription) == 0x1D0);
static_assert(offsetof(RenderSkinnedMeshDescription, mBoundsEmpty) == 0x98);
static_assert(offsetof(RenderSkinnedMeshDescription, mMesh) == 0xB0);
static_assert(offsetof(RenderSkinnedMeshDescription, mRefE0) == 0xE0);
static_assert(offsetof(RenderSkinnedMeshDescription, mMaterial) == 0x140);
static_assert(offsetof(RenderSkinnedMeshDescription, mCount178) == 0x178);
static_assert(offsetof(RenderSkinnedMeshDescription, mVariantIndex) == 0x1B0);
static_assert(offsetof(RenderSkinnedMeshDescription, mHasOverride) == 0x1C8);
static_assert(offsetof(RenderSkinnedMeshDescription, mByte1CE) == 0x1CE);

// RenderEnvironmentalTextDescription (Item group tag 0, in-world text such as signs), built by 0x668b400 for the text clone 0xe71330
// (docs/functions/668b400.md). Every field is written by the constructor [V]; size = aligned end [I].
struct RenderEnvironmentalTextDescription {
    const void* mSource;          // +0x00
    SharedRef mTexture;           // +0x08 converted by 0x4dfb570 (the font atlas)
    float mMatrix[16];            // +0x18
    float mPosition[3];           // +0x58
    float mBlock64[4];            // +0x64
    uint8_t mPad74[4];
    SharedRef mText;              // +0x78 the text object (one extra strong reference)
    uint8_t mByte88;              // +0x88
    uint8_t mByte89;              // +0x89
    uint8_t mPad8A[2];
    float mParamD8[4];            // +0x8C current values of the material parameters at params +0xD8, +0xE0, +0xE8, +0x70, +0x78, +0x80
    float mParamE0[2];            // +0x9C
    float mParamE8[4];            // +0xA4
    float mParam70[4];            // +0xB4
    float mParam78[2];            // +0xC4
    float mParam80;               // +0xCC
    float mOverride[4];           // +0xD0 optional vec4
    bool mHasOverride;            // +0xE0
    uint8_t mPadE1[3];
    uint16_t mFlags;              // +0xE4
    uint8_t mPadE6[2];
};
static_assert(sizeof(RenderEnvironmentalTextDescription) == 0xE8);
static_assert(offsetof(RenderEnvironmentalTextDescription, mMatrix) == 0x18);
static_assert(offsetof(RenderEnvironmentalTextDescription, mText) == 0x78);
static_assert(offsetof(RenderEnvironmentalTextDescription, mParamD8) == 0x8C);
static_assert(offsetof(RenderEnvironmentalTextDescription, mParam80) == 0xCC);
static_assert(offsetof(RenderEnvironmentalTextDescription, mHasOverride) == 0xE0);
static_assert(offsetof(RenderEnvironmentalTextDescription, mFlags) == 0xE4);

// RenderUITextDescription (UI group tag 3), built by 0x668c750 for the same text clone (docs/functions/668c750.md). [V fields, I size]
struct RenderUITextDescription {
    const void* mSource;          // +0x00
    const void* mField08;         // +0x08
    SharedRef mTexture;           // +0x10 converted by 0x4dfb570
    const void* mField20;         // +0x20
    const void* mField28;         // +0x28
    const void* mField30;         // +0x30
    uint16_t mFlags;              // +0x38
    uint8_t mByte3A;              // +0x3A
    uint8_t mPad3B[5];
    uint8_t mVariantPayload[0x18];// +0x40 a three-kind variant (kind 0 = {u64, SharedRef}, kind 1 = 0x20-byte heap copy)
    uint8_t mVariantIndex;        // +0x58 0xFF = empty
    uint8_t mPad59[7];
};
static_assert(sizeof(RenderUITextDescription) == 0x60);
static_assert(offsetof(RenderUITextDescription, mTexture) == 0x10);
static_assert(offsetof(RenderUITextDescription, mFlags) == 0x38);
static_assert(offsetof(RenderUITextDescription, mVariantIndex) == 0x58);

// RenderBlockSelectionOverlayBlockEntityDescription (Item group tag 8), built by 0x668d990 for the clone 0x539b7c0
// (docs/functions/668d990.md). Every field is written by the constructor [V]; size = aligned end [I].
struct RenderBlockSelectionOverlayDescription {
    float mMatrix[16];            // +0x00
    const void* mMesh;            // +0x40
    uint32_t mValue48;            // +0x48 (0 from the clone)
    uint8_t mPad4C[4];
    float mBlock50[4];            // +0x50
    SharedRef mTexture;           // +0x60 converted by 0x4dfb570, empty when the source is null
    SharedRef mMaterial;          // +0x70 (one extra strong reference)
    float mColor[4];              // +0x80
    uint16_t mFlags;              // +0x90
    uint8_t mPad92[6];
    uint8_t mVariantPayload[0x18];// +0x98 three-kind variant, same shape as UIText's
    uint8_t mVariantIndex;        // +0xB0 0xFF = empty
    uint8_t mPadB1[7];
};
static_assert(sizeof(RenderBlockSelectionOverlayDescription) == 0xB8);
static_assert(offsetof(RenderBlockSelectionOverlayDescription, mMesh) == 0x40);
static_assert(offsetof(RenderBlockSelectionOverlayDescription, mTexture) == 0x60);
static_assert(offsetof(RenderBlockSelectionOverlayDescription, mColor) == 0x80);
static_assert(offsetof(RenderBlockSelectionOverlayDescription, mFlags) == 0x90);
static_assert(offsetof(RenderBlockSelectionOverlayDescription, mVariantIndex) == 0xB0);

// RenderSkyDescription (Sky group tag 5), built by 0x668c910 for the sky clone 0x5369b30 (insert at 0x536a2e3; docs/functions/668c910.md).
// Every field is written by the constructor [V]; size = aligned end [I].
struct RenderSkyDescription {
    const void* mSource;          // +0x00 first qword of the source
    SharedRef mTexture;           // +0x08 source +0x40 shared ref (or a static default), converted by 0x4dfb570
    uint16_t mFlags;              // +0x18
    uint8_t mPad1A[2];
    float mColor[4];              // +0x1C
    float mMatrix[16];            // +0x2C
    float mUvTransform[16];       // +0x6C a 4x4 built from a 2x3 matrix: rows {a, b, 0, c}, {d, e, 0, f}, {0, 0, 1, 0}, {0, 0, 0, 1}
    float mValueAC;               // +0xAC
};
static_assert(sizeof(RenderSkyDescription) == 0xB0);
static_assert(offsetof(RenderSkyDescription, mFlags) == 0x18);
static_assert(offsetof(RenderSkyDescription, mMatrix) == 0x2C);
static_assert(offsetof(RenderSkyDescription, mUvTransform) == 0x6C);

// RenderStarsDescription (Sky group tag 6), built inline in the same clone (0x536e006..0x536e112, insert at 0x536e193). [V offsets, I size]
struct RenderStarsDescription {
    const void* mMesh;            // +0x00 source +0x700
    float mBlock08[4];            // +0x08
    float mMatrix[16];            // +0x18 copy of the newest camera record
    uint16_t mFlags;              // +0x58 context byte +0x74
    uint8_t mByte5A;              // +0x5A source +0x7D
    uint8_t mPad5B[5];
};
static_assert(offsetof(RenderStarsDescription, mMatrix) == 0x18);
static_assert(offsetof(RenderStarsDescription, mFlags) == 0x58);

// RenderMeshFallbackDescription (Item group tag 2), the generic mesh draw. Every field is written by the constructor 0x668b850, fully
// reversed in docs/functions/668b850.md; it is called by the generic mesh insert 0x4def480. Size 0x1D0.
struct RenderMeshFallbackDescription {
    const void* mMesh;           // +0x000 the mesh being drawn
    SharedRef mTextures[8];      // +0x008 texture bindings, filled from the caller's span (each converted by 0x4dfb570)
    uint64_t mNumTextures;       // +0x088
    float mMatrix[16];           // +0x090 newest camera record (4x4)
    float mCameraPos[3];         // +0x0D0
    uint8_t mFlagDC;             // +0x0DC context byte +0x65
    uint8_t mFlagDD;             // +0x0DD context byte +0x66
    uint8_t mFlagDE;             // +0x0DE context byte +0x68
    uint8_t mFlagDF;             // +0x0DF context byte +0x6B
    uint8_t mFlagE0;             // +0x0E0 context byte +0x6C
    uint8_t mPadE1[3];
    float mBlockE4[4];           // +0x0E4 16 bytes from *(context +0x20)
    float mBlockF4[4];           // +0x0F4 16 bytes from *(context +0x28)
    uint8_t mPad104[4];
    SharedRef mMaterial;         // +0x108 the material (one extra strong reference)
    const void* mParams;         // +0x118 material parameter object (context +0x10); the floats below are its current values
    float mParam100[4];          // +0x120 value of the parameter at params+0x100
    float mParam150;             // +0x130 value of the parameter at params+0x150
    float mContext6D;            // +0x134 float(int8 context byte +0x6D)
    float mParam70[4];           // +0x138 value of the parameter at params+0x70
    float mParam78[2];           // +0x148 value of the parameter at params+0x78
    float mParam80;              // +0x150 value of the parameter at params+0x80
    float mOverride[4];          // +0x154 optional vec4 from context +0x50, valid when mHasOverride
    bool mHasOverride;           // +0x164
    uint8_t mPad165[3];
    uint16_t mFlags;             // +0x168 context byte +0x64, widened
    uint8_t mPad16A[6];
    uint8_t mVariantHead[0x10];  // +0x170 16 bytes of the caller's parameter variant
    uint8_t mVariantByte;        // +0x180
    uint8_t mPad181[7];
    uint8_t mVariantPayload[0x18]; // +0x188 payload of kind mVariantIndex (0: {u64, SharedRef}; 1: a 0x20-byte heap copy; 2, 3: [?])
    uint8_t mVariantIndex;       // +0x1A0 0xFF = empty
    uint8_t mPad1A1[7];
    float mBounds[6];            // +0x1A8 mesh +0x178: AABB min / max
    float mMeshVec4[4];          // +0x1C0 mesh +0x190
};
static_assert(sizeof(RenderMeshFallbackDescription) == 0x1D0);
static_assert(offsetof(RenderMeshFallbackDescription, mNumTextures) == 0x88);
static_assert(offsetof(RenderMeshFallbackDescription, mMatrix) == 0x90);
static_assert(offsetof(RenderMeshFallbackDescription, mFlagDC) == 0xDC);
static_assert(offsetof(RenderMeshFallbackDescription, mBlockE4) == 0xE4);
static_assert(offsetof(RenderMeshFallbackDescription, mMaterial) == 0x108);
static_assert(offsetof(RenderMeshFallbackDescription, mParams) == 0x118);
static_assert(offsetof(RenderMeshFallbackDescription, mParam80) == 0x150);
static_assert(offsetof(RenderMeshFallbackDescription, mHasOverride) == 0x164);
static_assert(offsetof(RenderMeshFallbackDescription, mFlags) == 0x168);
static_assert(offsetof(RenderMeshFallbackDescription, mVariantHead) == 0x170);
static_assert(offsetof(RenderMeshFallbackDescription, mVariantIndex) == 0x1A0);
static_assert(offsetof(RenderMeshFallbackDescription, mBounds) == 0x1A8);
static_assert(offsetof(RenderMeshFallbackDescription, mMeshVec4) == 0x1C0);

// RenderWeatherDescription (Sky group tag 9), from every read in the Weather extractor 0x6745440 (6ib). The ten vec4 blocks are set as
// uniforms of the "Weather"/"WeatherForwardPBR" material; each name comes from the FNV-1a hash static the block is matched against
// (statics paired with their strings through the function-local guards). [V] for the uniform mapping, [I] for the rest.
struct RenderWeatherDescription {
    const void* mHead;           // +0x00 [?]
    uint8_t mPad08[8];
    float mBlock10[12];          // +0x10 three 16-byte rows, used with +0x40/+0x48 next to the OcclusionHeightOffset uniform [?]
    double mValue40;             // +0x40 [?] (loaded with movsd)
    double mValue48;             // +0x48 [?]
    uint8_t mTexture50[0x10];    // +0x50 texture reference bound as WeatherTexture (0xbcaba00) [I]
    uint8_t mTexture60[0x10];    // +0x60 texture reference (Occlusion / Height / Lighting) [I]
    uint8_t mTexture70[0x10];    // +0x70 texture reference (Occlusion / Height / Lighting) [I]
    int32_t mOcclusionHeight;    // +0x80 converted to float for OcclusionHeightOffset [I]
    uint32_t mValue84;           // +0x84 read first by the extractor (variant selection) [?]
    float mFogColor[4];                  // +0x88 FogColor (hash shared with the actor uniforms)
    float mFogAndDistanceControl[4];     // +0x98 FogAndDistanceControl
    float mPositionBaseOffset[4];        // +0xA8 PositionBaseOffset
    float mPrevPositionForwardOffset[4]; // +0xB8 PrevPositionForwardOffset
    float mPrevPositionBaseOffset[4];    // +0xC8 PrevPositionBaseOffset
    float mPositionForwardOffset[4];     // +0xD8 PositionForwardOffset
    float mViewPosition[4];              // +0xE8 ViewPosition
    float mUVOffsetAndScale[4];          // +0xF8 UVOffsetAndScale
    float mVelocity[4];                  // +0x108 Velocity
    float mDimensions[4];                // +0x118 Dimensions
    uint16_t mValue128;          // +0x128 [?]
    uint8_t mPad12A[6];
};
static_assert(sizeof(RenderWeatherDescription) == 0x130);
static_assert(offsetof(RenderWeatherDescription, mOcclusionHeight) == 0x80);
static_assert(offsetof(RenderWeatherDescription, mFogColor) == 0x88);
static_assert(offsetof(RenderWeatherDescription, mDimensions) == 0x118);
static_assert(offsetof(RenderWeatherDescription, mValue128) == 0x128);

// RenderParticleDescription (Effect group tag 2), from every read in the Particle extractor 0x67417f0 (6ic; descscan method of 6ib).
// Materials "Particle" / "ParticlePrepass" / "ParticleForwardPBR". Size is the aligned end of the last read [I].
struct RenderParticleDescription {
    const void* mMesh;          // +0x00 mce::Mesh*, first checked by Mesh::hasDrawableData 0x4def080 (nothing drawn when false)
    uint8_t mPad08[0x10];
    const void* mTexture18;     // +0x18 optional texture (ParticleTexture / MERSTexture / NormalTexture) [I]
    void* mKeepAlive;           // +0x20 shared_ptr pushed (AddRef'd) onto the pass's keep-alive vector (+0x80/+0x88)
    void* mKeepAliveCtrl;       // +0x28
    const void* mTexture30;     // +0x30 optional texture [I]
    uint8_t mPad38[0x34];
    float mFogColor[4];         // +0x6C FogColor
    float mFogAndDistanceControl[4]; // +0x7C FogAndDistanceControl
    uint8_t mEnum8C;            // +0x8C compared with 3 [?]
    uint8_t mEnum8D;            // +0x8D compared with 2 [?]
    uint8_t mPad8E[3];
    bool mFlag91;               // +0x91 ANDed with a frame-mode test [?]
    uint8_t mPad92;
    uint8_t mMode93;            // +0x93 0/1/2 [?]
    uint8_t mPad94[4];
    float mMERSUniforms[4];     // +0x98 MERSUniforms
    bool mHasMERS;              // +0xA8 MERSUniforms only set when 1
    uint8_t mPadA9[7];
};
static_assert(sizeof(RenderParticleDescription) == 0xB0);
static_assert(offsetof(RenderParticleDescription, mFogColor) == 0x6C);
static_assert(offsetof(RenderParticleDescription, mMERSUniforms) == 0x98);
static_assert(offsetof(RenderParticleDescription, mHasMERS) == 0xA8);

// RenderFlameBillboardDescription (Effect group tag 0), from the FlameBillboard / ActorPrepass extractor 0x673d150 (6id, descscan).
// Uniform names from the hash static each read feeds [V]; the texture slots are named by the static next to them [I]. Size [I].
struct RenderFlameBillboardDescription {
    const void* mMesh;          // +0x00 read before anything else (8 sites)
    uint8_t mPad08[8];
    uint32_t mValue10;          // +0x10 [?]
    uint8_t mPad14[0x34];
    const void* mFlameAtlas;    // +0x48 FlameAtlas texture [I]
    uint8_t mPad50[8];
    const void* mMersTexture;   // +0x58 MERSTexture [I]
    uint8_t mPad60[0x10];
    const void* mNormalTexture; // +0x70 NormalTexture [I]
    uint8_t mPad78[8];
    bool mHasNormal;            // +0x80 [I]
    uint8_t mPad81[0x27];
    float mMetalness;           // +0xA8 MetalnessUniform
    float mEmissive;            // +0xAC EmissiveUniform
    float mRoughness;           // +0xB0 RoughnessUniform
    float mSubsurface;          // +0xB4 SubsurfaceUniform
    bool mHasPbrScalars;        // +0xB8 the four scalars above are only set when 1
    uint8_t mPadB9[3];
    bool mFlagBC;               // +0xBC [?]
    uint8_t mPadBD[3];
    float mUVOffset[2];         // +0xC0 UVOffset
    float mFogColor[4];         // +0xC8 FogColor
    float mFogAndDistanceControl[4]; // +0xD8 FogAndDistanceControl
    float mTileLightIntensity[2];    // +0xE8 TileLightIntensity
    int8_t mDithering;          // +0xF0 DitheringEnabledToggle (sign-extended)
    uint8_t mPadF1[7];
};
static_assert(sizeof(RenderFlameBillboardDescription) == 0xF8);
static_assert(offsetof(RenderFlameBillboardDescription, mMetalness) == 0xA8);
static_assert(offsetof(RenderFlameBillboardDescription, mUVOffset) == 0xC0);
static_assert(offsetof(RenderFlameBillboardDescription, mFogColor) == 0xC8);
static_assert(offsetof(RenderFlameBillboardDescription, mTileLightIntensity) == 0xE8);
static_assert(offsetof(RenderFlameBillboardDescription, mDithering) == 0xF0);

// RenderGameFaceDescription (UI group tag 0), from the Gameface/Renoir extractor 0x66ade80 (6id, descscan). Materials Gameface/*;
// uniforms Viewport, Data_VS, Data_PS. Only the read offsets are certain [V]; their meanings are [?]. Size [I].
struct RenderGameFaceDescription {
    const void* mHead;          // +0x00
    uint8_t mPad08[0x20];
    uint8_t mBlock28[8];        // +0x28 passed by address (optional pair with the byte at +0x38)
    uint64_t mValue30;          // +0x30
    uint8_t mByte38;            // +0x38
    uint8_t mPad39[7];
    uint8_t mBlock40[8];        // +0x40 passed by address (optional pair with the byte at +0x50)
    uint64_t mValue48;          // +0x48
    uint8_t mByte50;            // +0x50
    uint8_t mPad51[7];
    float mVec58[4];            // +0x58
    float mVec68[4];            // +0x68
};
static_assert(sizeof(RenderGameFaceDescription) == 0x78);

// RenderCubemapDescription (Sky group tag 2), built by its producer 0x6606580 (tools/sigs/producerscan.py, 6ie): the constructor 0x668eb10
// fills +0x00..+0x52, the producer writes the rest directly before calling the thin clone 0x660b720. Size = end of the last store.
struct RenderCubemapDescription {
    void* mTexture;            // +0x00 resolved cubemap texture (resolveTexture 0x4dfb570: {GPU texture, shared ctrl})
    void* mTextureCtrl;        // +0x08
    float mTransform[16];      // +0x10 copied from the constructor's 3rd argument
    uint16_t mValue50;         // +0x50 constructor 4th argument
    uint8_t mByte52;           // +0x52 constructor 5th argument
    uint8_t mPad53[0x0D];
    uint64_t mValue60;         // +0x60 producer
    uint8_t mByte68;           // +0x68 producer
    uint8_t mPad69[7];
    uint64_t mValue70;         // +0x70 producer
    uint64_t mValue78;         // +0x78
    uint64_t mValue80;         // +0x80
    uint64_t mValue88;         // +0x88
    float mVec90[4];           // +0x90
    float mVecA0[4];           // +0xA0
    float mVecB0[4];           // +0xB0
};
static_assert(sizeof(RenderCubemapDescription) == 0xC0);
static_assert(offsetof(RenderCubemapDescription, mTransform) == 0x10);
static_assert(offsetof(RenderCubemapDescription, mValue50) == 0x50);
static_assert(offsetof(RenderCubemapDescription, mValue60) == 0x60);
static_assert(offsetof(RenderCubemapDescription, mVecB0) == 0xB0);

// RenderChunkOccludersDescription (Item group tag 4, material "ChunkOccluder"). Producer stores (producer_fields.txt) and the inline
// extractor reads (Item visitor 0x6646980, case 0x6646a89 -> shared tail 0x6647e04; desc in rdi) agree on every field below (6ig).
// The extractor reads nothing past +0x49, so the size is the aligned end [I].
struct RenderChunkOccludersDescription {
    float mTransform[16];      // +0x00 copied out as four 16-byte rows
    const void* mMesh;         // +0x40 mce::Mesh*: positions = MeshData +0x58/+0x60 (count = bytes / 12), index count +0x1D0 when +0x1D4
    uint16_t mValue48;         // +0x48
    uint8_t mPad4A[6];
};
static_assert(sizeof(RenderChunkOccludersDescription) == 0x50);
static_assert(offsetof(RenderChunkOccludersDescription, mMesh) == 0x40);
static_assert(offsetof(RenderChunkOccludersDescription, mValue48) == 0x48);
static_assert(offsetof(RenderGameFaceDescription, mVec58) == 0x58);

// RenderAtmosphereDescription (Sky group tag 0, visitor 0x66560f0, case 0x6656174 -> join 0x6656d4b; desc in rdi). Offsets and widths are the
// extractor's reads (descscan); the per-field uniform mapping (SkyColor, FogColor, SunMoonColor, StarsColor, UV0Transform, CubemapRotation,
// MinimumSkyLuminance, CloudRenderDistanceAndCloudHeight) is NOT resolved yet [?]. 64-bit fields are uint32[2] to keep the 4-byte packing. Size is the aligned read end [I].
struct RenderAtmosphereDescription {
    // descriptions agent 14 Nov: producer fat clone 0x53e2c00 builds this at [rbp-0x38..rbp+0x100] (extent 0x138 verified): u16 +0 (byte [component+0x74]),
    // dword +4 (vcall result, compared with 1 = a mode), vec2 +8 (qword from [env+0x45C]); descscan.py missed these (offsets below 10 are printed decimal).
    uint16_t mWord00;          // +0x00
    uint8_t mPad02[2];
    uint32_t mDword04;         // +0x04
    float mVec08[2];           // +0x08 (second half = +0x0C, clamped width with +0x10)
    float mValue10;            // +0x10
    float mVec14[4];           // +0x14
    float mVec24[4];           // +0x24
    float mVec34[4];           // +0x34
    float mVec44[4];           // +0x44
    float mVec54[4];           // +0x54
    float mVec64[4];           // +0x64
    float mVec74[4];           // +0x74
    float mVec84[4];           // +0x84
    uint32_t mQword94[2];         // +0x94
    float mValue9C;            // +0x9C
    uint8_t mByteA0;           // +0xA0
    uint8_t mPadA1[0x37];
    uint32_t mPtrD8[2];              // +0xD8
    uint32_t mPadE0[2];
    uint32_t mQwordE8;          // +0xE8 (8-byte read overlapping +0xEC: first dword)
    float mValueEC;            // +0xEC
    uint32_t mQwordF0[2];         // +0xF0
    uint32_t mQwordF8[2];         // +0xF8
    uint32_t mQword100;         // +0x100 (8-byte read overlapping +0x104: first dword)
    uint32_t mQword104[2];        // +0x104
    float mVec10C[4];          // +0x10C
    uint32_t mQword11C[2];        // +0x11C
    float mValue124;           // +0x124
    float mVec128[4];          // +0x128
};
static_assert(offsetof(RenderAtmosphereDescription, mDword04) == 0x04);
static_assert(offsetof(RenderAtmosphereDescription, mVec08) == 0x08);
static_assert(offsetof(RenderAtmosphereDescription, mValue10) == 0x10);
static_assert(offsetof(RenderAtmosphereDescription, mVec14) == 0x14);
static_assert(offsetof(RenderAtmosphereDescription, mQword94) == 0x94);
static_assert(offsetof(RenderAtmosphereDescription, mByteA0) == 0xA0);
static_assert(offsetof(RenderAtmosphereDescription, mPtrD8) == 0xD8);
static_assert(offsetof(RenderAtmosphereDescription, mQwordE8) == 0xE8);
static_assert(offsetof(RenderAtmosphereDescription, mQword100) == 0x100);
static_assert(offsetof(RenderAtmosphereDescription, mVec10C) == 0x10C);
static_assert(offsetof(RenderAtmosphereDescription, mVec128) == 0x128);
static_assert(sizeof(RenderAtmosphereDescription) == 0x138);

// RenderBlockChangesDescription (Item group tag 9, visitor case 0x6646bc6): the case copies 0x18 bytes (vec4 at +0x00, qword at +0x10)
// into a 0x18-byte-element vector on the pass object (+0x98/+0xA0). Field meanings unknown [?]; size is the copied length [I].
struct RenderBlockChangesDescription {
    float mVec00[4];           // +0x00
    uint64_t mQword10;         // +0x10
};
static_assert(sizeof(RenderBlockChangesDescription) == 0x18);
static_assert(offsetof(RenderBlockChangesDescription, mQword10) == 0x10);

// RenderBlitFlipbookDescription (Effect group tag 1, thin clone 0x5acbe20, producer 0x5aca680 @5acb267; description at [rbp+0x30]). Descriptions agent: SIZE IS 0x20, not 0xA0
// (CONTRADICTS 6ih): the call-site window stores only a shared_ptr pair at +0x00 (0x4dfb570 @5acb248) and 16 bytes at +0x10 (@5acb25a); the extractor tail (shared with other
// cases) reads exactly +0x00..+0x1F: count u64 at +0x10 and data pointer at +0x18 of 0x40-byte elements. The Element is complete from its copy/emplace routine 0x5acb9c0.
struct RenderBlitFlipbookDescription {
    struct Element {
        uint64_t mValue00;     // +0x00 qword; used as the object handle after 0x5679db0 and 0x4dedd00
        SharedRef mRef08;      // +0x08 shared_ptr pair (addref lock inc [ctrl+8] @5acb9f7), passed by address to 0xbcaba00
        uint32_t mBlendXY[2];  // +0x18 qword (VBlendControl)
        float mBlendZ;         // +0x20 (VBlendControl; copied as dword)
        float mFloat24;        // +0x24
        float mFloat28;        // +0x28
        float mFloat2C;        // +0x2C
        float mFloat30;        // +0x30
        uint32_t mQword34[2];  // +0x34 8 bytes (unaligned qword copy, ends +0x3B)
        uint8_t mByte3C;       // +0x3C
        uint8_t mPad3D[3];
    };
    SharedRef mRef00;          // +0x00 shared_ptr pair built by 0x4dfb570
    uint64_t mCount;           // +0x10 element count
    Element* mElements;        // +0x18
};
static_assert(sizeof(RenderBlitFlipbookDescription::Element) == 0x40);
static_assert(offsetof(RenderBlitFlipbookDescription::Element, mRef08) == 0x08);
static_assert(offsetof(RenderBlitFlipbookDescription::Element, mBlendXY) == 0x18);
static_assert(offsetof(RenderBlitFlipbookDescription::Element, mBlendZ) == 0x20);
static_assert(offsetof(RenderBlitFlipbookDescription::Element, mFloat24) == 0x24);
static_assert(offsetof(RenderBlitFlipbookDescription::Element, mFloat30) == 0x30);
static_assert(offsetof(RenderBlitFlipbookDescription::Element, mQword34) == 0x34);
static_assert(offsetof(RenderBlitFlipbookDescription::Element, mByte3C) == 0x3C);
static_assert(offsetof(RenderBlitFlipbookDescription, mCount) == 0x10);
static_assert(offsetof(RenderBlitFlipbookDescription, mElements) == 0x18);
static_assert(sizeof(RenderBlitFlipbookDescription) == 0x20);

// RenderAimAssistHighlightDescription (Effect group tag 6, visitor 0x666aca0 case 0x666b143; desc in r15 = [r8]). Verified reads of the case:
// vec2 at +0x0C and float at +0x14 build a local translate/scale matrix (rbp+0x3f0), which is multiplied by the mat4 at +0x28 with 0xaa6580
// (out = rbp+0x2a0); the material ("CameraAimAssistHighlight") is then resolved with 0x675e440. The shared exit tail 0x666c8f0 also reads a dword at
// +0x84 but is shared with other Effect cases, so it is not attributed here [?]. Fields +0x00..+0x0B, +0x18..+0x27 are unread [?]. The size is
// at least 0x68 (end of the mat4); the true size is unknown.
struct RenderAimAssistHighlightDescription {
    uint8_t mHead00[0x0C];     // +0x00 unread [?]
    float mVec0C[2];           // +0x0C
    float mValue14;            // +0x14
    uint8_t mPad18[0x10];      // +0x18 unread [?]
    float mMatrix[16];         // +0x28 multiplied into the local transform
};
static_assert(offsetof(RenderAimAssistHighlightDescription, mVec0C) == 0x0C);
static_assert(offsetof(RenderAimAssistHighlightDescription, mValue14) == 0x14);
static_assert(offsetof(RenderAimAssistHighlightDescription, mMatrix) == 0x28);
static_assert(sizeof(RenderAimAssistHighlightDescription) == 0x68);

// RenderEditorHighlightDescription (Effect group tag 8, visitor case 0x666b316): the case copies the whole description (0x58 bytes) verbatim into
// an element of the pass vector at pass+0x80/+0x88 (element stride 0x58), taking a reference on the control block at +0x08 (lock inc [ctrl+8]).
// Every byte is copied, so the size 0x58 and the shared_ptr pair are verified; meanings of the 64-byte block at +0x10 (matrix or four vec4) and +0x50 are unknown [?].
struct RenderEditorHighlightDescription {
    void* mObject;             // +0x00 shared_ptr pointer
    void* mControlBlock;       // +0x08 shared_ptr control block (refcount at ctrl+8)
    float mBlock10[16];        // +0x10 copied as four 16-byte rows [?]
    uint64_t mValue50;         // +0x50
};
static_assert(sizeof(RenderEditorHighlightDescription) == 0x58);
static_assert(offsetof(RenderEditorHighlightDescription, mControlBlock) == 0x08);
static_assert(offsetof(RenderEditorHighlightDescription, mBlock10) == 0x10);
static_assert(offsetof(RenderEditorHighlightDescription, mValue50) == 0x50);

// RenderLightAmbientDescription (Light group tag 0, visitor 0x6640d80 case 0x6640de8; desc = [variant] in rsi). The case reads qword +0x00, float +0x08,
// float +0x10, u16 +0x14 and queues them packed into a 0x14-byte element of the pass vector at pass+0x800/+0x808 (element: qword, float, float, u16;
// +0x0C of the description is not read). Names of the values are unknown [?]; size is the aligned read end [I].
struct RenderLightAmbientDescription {
    float mValue00[2];         // +0x00 copied as a qword
    float mValue08;            // +0x08
    uint8_t mPad0C[4];         // +0x0C unread [?]
    float mValue10;            // +0x10
    uint16_t mValue14;         // +0x14
    uint8_t mPad16[2];
};
static_assert(sizeof(RenderLightAmbientDescription) == 0x18);
static_assert(offsetof(RenderLightAmbientDescription, mValue08) == 0x08);
static_assert(offsetof(RenderLightAmbientDescription, mValue10) == 0x10);
static_assert(offsetof(RenderLightAmbientDescription, mValue14) == 0x14);

// RenderLightDirectionalDescription (Light group tag 1, visitor 0x6640d80 case 0x66415b0; desc = [variant] in rsi; runs only when frame ctx +0x70 == 1).
// Verified reads: vec4 +0x00, byte +0x10, qword +0x14, dword +0x1C, u16 +0x20. The case packs them into a local light record (type 2, flag 1), emplaces it
// into the pass light vector at pass+0x648 through 0x675fb30, and appends a 0x14-byte summary {vec3 +0x00, float +0x0C, byte flag 1, byte +0x10, index of
// the new light} to the summary list at pass+0x800 (the same list LightAmbient writes). Value names are unknown [?]; size is the aligned read end [I].
struct RenderLightDirectionalDescription {
    float mVec00[4];           // +0x00 (xyz direction-like; +0x0C copied to the summary) [?]
    uint8_t mByte10;           // +0x10 copied to the summary
    uint8_t mPad11[3];
    float mValue14[2];         // +0x14 copied as a qword
    float mValue1C;            // +0x1C
    uint16_t mValue20;         // +0x20
    uint8_t mPad22[2];
};
// Size 0x24 (not 0x28): producer 0x5369b30 (@536b1a1, @536c2cc) stores end at +0x22, all members align 4.
static_assert(sizeof(RenderLightDirectionalDescription) == 0x24);
static_assert(offsetof(RenderLightDirectionalDescription, mByte10) == 0x10);
static_assert(offsetof(RenderLightDirectionalDescription, mValue14) == 0x14);
static_assert(offsetof(RenderLightDirectionalDescription, mValue1C) == 0x1C);
static_assert(offsetof(RenderLightDirectionalDescription, mValue20) == 0x20);

// RenderLightTag2Description (Light group tag 2, visitor 0x6640d80 case 0x6640f1b; desc = [variant] in rsi). The case copies the WHOLE description verbatim
// (0x84 bytes: four 16-byte rows with the last at +0x2A overlapping, then dwords +0x3C..+0x80) into an element of the pass vector at pass+0x4A0/+0x4A8
// (element stride 0x84, `add [pass+0x4a0], 0x84`). It holds no pointers (plain POD). Field meanings unknown [?]. Name by tag: group_visitors.md calls this
// case LightPoint, FrameBuilder.h's LightGroupTag lists tag 2 as GameplayMetadata; the two sources disagree [?].
struct RenderLightTag2Description {
    float mData[0x84 / 4];     // +0x00..+0x83 copied verbatim
};
static_assert(sizeof(RenderLightTag2Description) == 0x84);

// RenderLightTag4Description (Light group tag 4, visitor 0x6640d80 case 0x6640ec1; desc = [variant] in rsi). Copied whole (0x50 bytes) into the pass vector at
// pass+0x1D0/+0x1D8 (element stride 0x50, `add [pass+0x1d0], 0x50`): a 64-byte block (four rows, a matrix by shape), a shared_ptr pair at +0x40/+0x48
// (control block refcount at ctrl+8). group_visitors.md lists this slot among ShadowAtlasFrame-like names; the tag name is unconfirmed [?].
struct RenderLightTag4Description {
    float mMatrix[16];         // +0x00 four 16-byte rows [I: matrix]
    void* mObject;             // +0x40 shared_ptr pointer (e.g. a texture/atlas) [?]
    void* mControlBlock;       // +0x48 shared_ptr control block
};
static_assert(sizeof(RenderLightTag4Description) == 0x50);
static_assert(offsetof(RenderLightTag4Description, mObject) == 0x40);
static_assert(offsetof(RenderLightTag4Description, mControlBlock) == 0x48);

// RenderLightTag3Description (Light group tag 3, visitor 0x6640d80 case 0x66410a0; desc = [variant] in rsi). Verified reads: float +0x00, qword +0x08, float
// +0x10, qword +0x14, float +0x1C, byte +0x20, qword +0x28, u16 +0x30, SIX slices at +0x38 + k*0x20 of {weak_ptr {ptr, control block} (the case does
// `lock inc [ctrl+0xC]` = weak count), vec4 at +0x10 of the slice}, then qword +0xF8 and float +0x100. The six texture-handle-plus-vec4 slices look like shadow
// cascades or atlas slices, but the tag name and the meanings are unknown [?]. Size is the aligned read end [I]. The queue destination is not followed.
struct RenderLightTag3Description {
    struct Slice {
        void* mObject;         // +0x00 weak_ptr pointer
        void* mControlBlock;   // +0x08 weak_ptr control block (weak count at ctrl+0xC)
        float mVec[4];         // +0x10
    };
    float mValue00;            // +0x00
    uint8_t mPad04[4];
    float mValue08[2];         // +0x08 copied as a qword
    float mValue10;            // +0x10
    float mValue14[2];         // +0x14 copied as a qword
    float mValue1C;            // +0x1C
    uint8_t mByte20;           // +0x20
    uint8_t mPad21[7];
    uint64_t mValue28;         // +0x28
    uint16_t mValue30;         // +0x30
    uint8_t mPad32[6];
    Slice mSlices[6];          // +0x38
    uint32_t mValueF8[2];      // +0xF8 copied as a qword
    float mValue100;           // +0x100
    uint8_t mPad104[4];
};
static_assert(sizeof(RenderLightTag3Description::Slice) == 0x20);
static_assert(offsetof(RenderLightTag3Description, mValue28) == 0x28);
static_assert(offsetof(RenderLightTag3Description, mValue30) == 0x30);
static_assert(offsetof(RenderLightTag3Description, mSlices) == 0x38);
static_assert(offsetof(RenderLightTag3Description, mValueF8) == 0xF8);
static_assert(offsetof(RenderLightTag3Description, mValue100) == 0x100);
static_assert(sizeof(RenderLightTag3Description) == 0x108);

// Variant used by UIMesh and FullscreenEffect (constructor tails 0x668c4b9.. and 0x668c088..): 0x18 bytes of storage + tag byte (0xFF = empty).
// Alt 0 = {u64 +0, shared_ptr pair +8}; alt 1 = pointer to a heap 0x20-byte {shared_ptr pair {ptr,ctrl}, 16 bytes}; alts 2/3 hold nothing (jump table of 4).
struct DescVariantRef {
    uint8_t mStorage[0x18];
    uint8_t mTag;              // +0x18
    uint8_t mPad19[7];
};
static_assert(sizeof(DescVariantRef) == 0x20);

// RenderUIMeshDescription (UI group tag 2). COMPLETE from its constructor 0x668c3c0 (descriptions agent; callers 0x4c95550 etc.):
// +0x00/+0x08/+0x10 qwords, +0x18 inline array of 4 shared_ptr pairs (capacity 0x40) with count at +0x58 (extractor compares count with 2),
// +0x60/+0x68 qwords, +0x70 float, +0x78 qword, +0x80..+0x85 six flag bytes, +0x86 u16, +0x88 DescVariantRef storage (tag at +0xA0). End 0xA1 -> sizeof 0xA8.
struct RenderUIMeshDescription {
    uint64_t mValue00;         // +0x00
    uint64_t mValue08;         // +0x08
    uint64_t mValue10;         // +0x10
    SharedRef mRefs[4];        // +0x18 .. +0x57 (inline array, constructed empty)
    uint64_t mRefCount;        // +0x58 number of valid mRefs
    uint64_t mValue60;         // +0x60
    uint64_t mValue68;         // +0x68
    float mValue70;            // +0x70
    uint8_t mPad74[4];
    uint64_t mValue78;         // +0x78
    uint8_t mFlags80[6];       // +0x80..+0x85
    uint16_t mValue86;         // +0x86
    uint8_t mVariantStorage88[0x18]; // +0x88
    uint8_t mVariantTag;       // +0xA0 (0xFF empty)
    uint8_t mPadA1[7];
};
static_assert(offsetof(RenderUIMeshDescription, mRefs) == 0x18);
static_assert(offsetof(RenderUIMeshDescription, mRefCount) == 0x58);
static_assert(offsetof(RenderUIMeshDescription, mValue60) == 0x60);
static_assert(offsetof(RenderUIMeshDescription, mValue70) == 0x70);
static_assert(offsetof(RenderUIMeshDescription, mValue78) == 0x78);
static_assert(offsetof(RenderUIMeshDescription, mFlags80) == 0x80);
static_assert(offsetof(RenderUIMeshDescription, mValue86) == 0x86);
static_assert(offsetof(RenderUIMeshDescription, mVariantStorage88) == 0x88);
static_assert(offsetof(RenderUIMeshDescription, mVariantTag) == 0xA0);
static_assert(sizeof(RenderUIMeshDescription) == 0xA8);

// RenderFullscreenEffectDescription (Effect tag 7; producer clone 0x530a1b0). COMPLETE from its constructor 0x668bf20 (rcx = dest):
// qword +0x00, shared_ptr copy +0x08 (0x4dfb570), 19 floats +0x18..+0x63 (copied from a 0x4C-byte block), 16 bytes +0x64, shared_ptr pair +0x78 (the config the
// extractor reads), u16 +0x88, 16 bytes +0x90, byte +0xA0, DescVariantRef storage +0xA8 (tag +0xC0), bytes +0xC8/+0xC9. End 0xCA -> sizeof 0xD0.
struct RenderFullscreenEffectDescription {
    uint64_t mValue00;         // +0x00 (extractor: pointer whose +0x39 byte is passed on)
    SharedRef mRef08;          // +0x08
    float mFloats18[19];       // +0x18 .. +0x63
    uint8_t mBlock64[0x10];    // +0x64 (unaligned 16B copy; ends +0x73)
    uint8_t mPad74[4];
    SharedRef mConfig;         // +0x78 FullscreenEffectConfig shared_ptr
    uint16_t mValue88;         // +0x88
    uint8_t mPad8A[6];
    uint8_t mBlock90[0x10];    // +0x90
    uint8_t mByteA0;           // +0xA0
    uint8_t mPadA1[7];
    uint8_t mVariantStorageA8[0x18]; // +0xA8
    uint8_t mVariantTag;       // +0xC0 (0xFF empty)
    uint8_t mPadC1[7];
    uint8_t mByteC8;           // +0xC8
    uint8_t mByteC9;           // +0xC9
    uint8_t mPadCA[6];
};
static_assert(offsetof(RenderFullscreenEffectDescription, mRef08) == 0x08);
static_assert(offsetof(RenderFullscreenEffectDescription, mFloats18) == 0x18);
static_assert(offsetof(RenderFullscreenEffectDescription, mBlock64) == 0x64);
static_assert(offsetof(RenderFullscreenEffectDescription, mConfig) == 0x78);
static_assert(offsetof(RenderFullscreenEffectDescription, mValue88) == 0x88);
static_assert(offsetof(RenderFullscreenEffectDescription, mBlock90) == 0x90);
static_assert(offsetof(RenderFullscreenEffectDescription, mByteA0) == 0xA0);
static_assert(offsetof(RenderFullscreenEffectDescription, mVariantStorageA8) == 0xA8);
static_assert(offsetof(RenderFullscreenEffectDescription, mVariantTag) == 0xC0);
static_assert(offsetof(RenderFullscreenEffectDescription, mByteC8) == 0xC8);
static_assert(sizeof(RenderFullscreenEffectDescription) == 0xD0);

// RenderLightServerGraphicsOverrideDescription (Light tag 5 = gamecomponents::ServerGraphicsOverrideParameters; producer 0x6c2e820): 44 x std::unordered_set<uint16_t>
// (MSVC layout: float max_load +0, list sentinel +8, size +0x10, bucket vector +0x18/+0x20/+0x28, mask +0x30, max index +0x38; list nodes 0x18 {next, prev, u16 key at +0x10}).
struct UnorderedSetU16Raw {
    float mMaxLoad;            // +0x00 (1.0 after construction)
    uint8_t mPad04[4];
    void* mListHead;           // +0x08 sentinel node
    uint64_t mSize;            // +0x10
    void* mBucketBegin;        // +0x18
    void* mBucketEnd;          // +0x20
    void* mBucketCap;          // +0x28
    uint64_t mMask;            // +0x30 (7 when empty)
    uint64_t mMaxIndex;        // +0x38 (8 when empty)
};
static_assert(sizeof(UnorderedSetU16Raw) == 0x40);
struct RenderLightServerGraphicsOverrideDescription {
    UnorderedSetU16Raw mSets[44];
};
static_assert(sizeof(RenderLightServerGraphicsOverrideDescription) == 0xB00);

// RenderChunkGeometryDescription (Item group; thin clone 0x15a6880; producer 0x15a6190 builds it at [rbp+0x38] with constructor 0x668e350). COMPLETE from the
// constructor: inline array of 3 shared_ptr pairs +0x00..+0x2F (filled from the source's three refs at +0/+0x10/+0x20) with count qword +0x30, 16 bytes +0x38,
// qword +0x48, byte +0x50, floats +0x54..+0x77 (read through a material-parameter table), 16 floats +0x78..+0xB7 (a 4x4 matrix), byte +0xB8, variant storage
// +0xC0 (tag +0xD8, 0xFF empty, same variant type as UIMesh), bytes +0xE0/+0xE1, u16 +0xE2, 3 floats +0xE4. End 0xF0.
struct RenderChunkGeometryDescription {
    SharedRef mRefs[3];        // +0x00
    uint64_t mRefCount;        // +0x30
    uint8_t mBlock38[0x10];    // +0x38
    uint64_t mValue48;         // +0x48
    uint8_t mByte50;           // +0x50
    uint8_t mPad51[3];
    float mParams54[4];        // +0x54
    float mParams64[2];        // +0x64
    float mValue6C;            // +0x6C
    float mValue70;            // +0x70
    float mValue74;            // +0x74
    float mMatrix78[16];       // +0x78 .. +0xB7
    uint8_t mByteB8;           // +0xB8
    uint8_t mPadB9[7];
    uint8_t mVariantStorageC0[0x18]; // +0xC0
    uint8_t mVariantTag;       // +0xD8
    uint8_t mPadD9[7];
    uint8_t mByteE0;           // +0xE0
    uint8_t mByteE1;           // +0xE1
    uint16_t mWordE2;          // +0xE2
    float mValuesE4[3];        // +0xE4
};
static_assert(offsetof(RenderChunkGeometryDescription, mRefCount) == 0x30);
static_assert(offsetof(RenderChunkGeometryDescription, mBlock38) == 0x38);
static_assert(offsetof(RenderChunkGeometryDescription, mValue48) == 0x48);
static_assert(offsetof(RenderChunkGeometryDescription, mByte50) == 0x50);
static_assert(offsetof(RenderChunkGeometryDescription, mParams54) == 0x54);
static_assert(offsetof(RenderChunkGeometryDescription, mMatrix78) == 0x78);
static_assert(offsetof(RenderChunkGeometryDescription, mByteB8) == 0xB8);
static_assert(offsetof(RenderChunkGeometryDescription, mVariantStorageC0) == 0xC0);
static_assert(offsetof(RenderChunkGeometryDescription, mVariantTag) == 0xD8);
static_assert(offsetof(RenderChunkGeometryDescription, mByteE0) == 0xE0);
static_assert(offsetof(RenderChunkGeometryDescription, mValuesE4) == 0xE4);
static_assert(sizeof(RenderChunkGeometryDescription) == 0xF0);

// RenderItemInHandDescription (Item tag 6; thin clone 0x531b180; built by constructor 0x668cb70 from a source object in the producer 0x531a580). COMPLETE:
// pointer +0x00 (= source+8), shared_ptr pairs +0x08 and +0x18 (copied with 0x4dfb570), qwords +0x28/+0x30, 16 floats +0x38..+0x77 (matrix), six bytes +0x78..+0x7D,
// floats +0x80..+0x118 (+0x104 and +0x114 are also read as qwords), u16 +0x11C, 16 bytes +0x120, byte +0x130, variant storage +0x138 (tag +0x150), 10 floats +0x158..+0x17F.
// End 0x180. (The +0x1D0/+0x1D4 reads of extractor 0x6698e30 belong to the mesh object, RenderControllerMesh::mCount1D0, not to the description.)
struct RenderItemInHandDescription {
    void* mSource;             // +0x00
    SharedRef mRef08;          // +0x08
    SharedRef mRef18;          // +0x18
    uint64_t mValue28;         // +0x28
    uint64_t mValue30;         // +0x30
    float mMatrix38[16];       // +0x38 .. +0x77
    uint8_t mFlags78[6];       // +0x78 .. +0x7D
    uint8_t mPad7E[2];
    float mFloats80[39];       // +0x80 .. +0x11B
    uint16_t mWord11C;         // +0x11C
    uint8_t mPad11E[2];
    uint8_t mBlock120[0x10];   // +0x120
    uint8_t mByte130;          // +0x130
    uint8_t mPad131[7];
    uint8_t mVariantStorage138[0x18]; // +0x138
    uint8_t mVariantTag;       // +0x150 (0xFF empty)
    uint8_t mPad151[7];
    float mFloats158[10];      // +0x158 .. +0x17F
};
static_assert(offsetof(RenderItemInHandDescription, mRef08) == 0x08);
static_assert(offsetof(RenderItemInHandDescription, mRef18) == 0x18);
static_assert(offsetof(RenderItemInHandDescription, mValue28) == 0x28);
static_assert(offsetof(RenderItemInHandDescription, mMatrix38) == 0x38);
static_assert(offsetof(RenderItemInHandDescription, mFlags78) == 0x78);
static_assert(offsetof(RenderItemInHandDescription, mFloats80) == 0x80);
static_assert(offsetof(RenderItemInHandDescription, mWord11C) == 0x11C);
static_assert(offsetof(RenderItemInHandDescription, mBlock120) == 0x120);
static_assert(offsetof(RenderItemInHandDescription, mByte130) == 0x130);
static_assert(offsetof(RenderItemInHandDescription, mVariantStorage138) == 0x138);
static_assert(offsetof(RenderItemInHandDescription, mVariantTag) == 0x150);
static_assert(offsetof(RenderItemInHandDescription, mFloats158) == 0x158);
static_assert(sizeof(RenderItemInHandDescription) == 0x180);

// RenderEndSkyDescription (Sky tag 3, thin clone 0x53707a0): built by the SAME constructor as RenderSkyDescription (0x668c910, call @5369f89 right before the clone call
// @5369f99), so it is a RenderSkyDescription (0xB0); the case reads +0x00..+0x6B and +0xAC (descscan2 --follow). [V]
using RenderEndSkyDescription = RenderSkyDescription;

// RenderCelestialBodyDescription (Sky tag 7, thin clone 0x5370b20; five call sites in the sky producer 0x5369b30). Producer stores (callsite.py): qword +0x00,
// shared_ptr pair +0x08 (0x4dfb570), vec2 +0x18, floats +0x20/+0x24, 16 floats +0x28..+0x67 (matrix), u16 +0x68, dword +0x6C (1), byte +0x70, qword +0x74, float +0x7C,
// dword +0x80. End 0x84 -> sizeof 0x88 (align 8). The Sky case 7 reads +0x18..+0x27 and +0x70 itself; the rest is consumed by the material/draw code it calls [?].
struct RenderCelestialBodyDescription {
    uint64_t mValue00;         // +0x00
    SharedRef mTexture;        // +0x08
    float mVec18[2];           // +0x18
    float mValue20;            // +0x20
    float mValue24;            // +0x24
    float mMatrix28[16];       // +0x28 .. +0x67
    uint16_t mWord68;          // +0x68
    uint8_t mPad6A[2];
    uint32_t mDword6C;         // +0x6C (1)
    uint8_t mByte70;           // +0x70
    uint8_t mPad71[3];
    uint32_t mQword74[2];      // +0x74 (8 bytes, 4-aligned)
    float mValue7C;            // +0x7C
    uint32_t mDword80;         // +0x80
    uint8_t mPad84[4];
};
static_assert(offsetof(RenderCelestialBodyDescription, mTexture) == 0x08);
static_assert(offsetof(RenderCelestialBodyDescription, mVec18) == 0x18);
static_assert(offsetof(RenderCelestialBodyDescription, mMatrix28) == 0x28);
static_assert(offsetof(RenderCelestialBodyDescription, mWord68) == 0x68);
static_assert(offsetof(RenderCelestialBodyDescription, mDword6C) == 0x6C);
static_assert(offsetof(RenderCelestialBodyDescription, mByte70) == 0x70);
static_assert(offsetof(RenderCelestialBodyDescription, mQword74) == 0x74);
static_assert(offsetof(RenderCelestialBodyDescription, mDword80) == 0x80);
static_assert(sizeof(RenderCelestialBodyDescription) == 0x88);

// RenderLegacyCubemapDescription (Sky tag 4; fat clone 0x660b1a0, tag 4 variant at [rbp-0x50], description at [rbp+0x10], next local at +0x40). Every field is stored
// right before the insert (0x660b33c..0x660b37c): dword +0x00, shared_ptr pair +0x08, qword +0x18, qword +0x20, float +0x28, u16 +0x2C, vec2 +0x30, float +0x38,
// u16 +0x3C, bytes +0x3E/+0x3F. Size 0x40 [V: producer extent, adjacent local]. The extractor head reads byte +0x3E (case 0x66561cc).
struct RenderLegacyCubemapDescription {
    uint32_t mDword00;         // +0x00
    uint8_t mPad04[4];
    SharedRef mTexture;        // +0x08
    uint64_t mValue18;         // +0x18
    uint64_t mValue20;         // +0x20
    float mValue28;            // +0x28
    uint16_t mWord2C;          // +0x2C
    uint8_t mPad2E[2];
    float mVec30[2];           // +0x30
    float mValue38;            // +0x38
    uint16_t mWord3C;          // +0x3C
    uint8_t mByte3E;           // +0x3E
    uint8_t mByte3F;           // +0x3F
};
static_assert(offsetof(RenderLegacyCubemapDescription, mTexture) == 0x08);
static_assert(offsetof(RenderLegacyCubemapDescription, mValue28) == 0x28);
static_assert(offsetof(RenderLegacyCubemapDescription, mVec30) == 0x30);
static_assert(offsetof(RenderLegacyCubemapDescription, mWord3C) == 0x3C);
static_assert(offsetof(RenderLegacyCubemapDescription, mByte3F) == 0x3F);
static_assert(sizeof(RenderLegacyCubemapDescription) == 0x40);

// RenderSkyAmbientSamplesDescription (Sky tag 10; producer 0x53e3aa0 @53e4896, build @53e47ca..53e4804): u16 +0x00 (byte [component+0x74]), shared_ptr pair +0x08.
// Size 0x18 [V]; the case (0x6656983) reads the word and takes a reference on the control block at +0x10.
struct RenderSkyAmbientSamplesDescription {
    uint16_t mFlags;           // +0x00
    uint8_t mPad02[6];
    SharedRef mSamples;        // +0x08
};
static_assert(offsetof(RenderSkyAmbientSamplesDescription, mSamples) == 0x08);
static_assert(sizeof(RenderSkyAmbientSamplesDescription) == 0x18);

// RenderVolumetricFogDescription (Sky tag 8; producer 0x53e3aa0 @53e4a51, description [rbp+0x90], tag-8 variant at +0xE0). The case 0x66569b1 copies u16 +0x00 and the
// 0x54 bytes +0x04..+0x57 plus qword +0x54 (five 16-byte rows at +4/+0x14/+0x24/+0x34/+0x44, qword +0x54) into a 0x58-byte element of the pass vector at pass+0x158 (stride
// 0x58, `add [pass+0x158], 0x58`). Bytes +0x5C..+0xDF are written by the producer but never read by the visitor [V]. Size 0xE0 [V: variant adjacent].
struct RenderVolumetricFogDescription {
    uint16_t mFlags;           // +0x00
    uint8_t mPad02[2];
    float mRows04[4][4];       // +0x04 .. +0x43 (4 rows, unaligned 16B reads)
    float mRow44[4];           // +0x44
    uint32_t mQword54[2];      // +0x54 (qword read; ends 0x5B)
    uint8_t mUnreadTail5C[0x84]; // +0x5C .. +0xDF written by the producer, never read by the visitor
};
static_assert(offsetof(RenderVolumetricFogDescription, mRows04) == 0x04);
static_assert(offsetof(RenderVolumetricFogDescription, mRow44) == 0x44);
static_assert(offsetof(RenderVolumetricFogDescription, mQword54) == 0x54);
static_assert(offsetof(RenderVolumetricFogDescription, mUnreadTail5C) == 0x5C);
static_assert(sizeof(RenderVolumetricFogDescription) == 0xE0);

} // namespace mce::framebuilder
