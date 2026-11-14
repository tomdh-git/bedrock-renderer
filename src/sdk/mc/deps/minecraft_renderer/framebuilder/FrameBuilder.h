#pragma once

#include "sdk/mc/deps/minecraft_renderer/renderer/MeshData.h"

namespace mce::framebuilder {

// The frame builder's virtual table as the 1.26.62.01 binary lays it out (docs/BGFX_MAP.md section 3): byte offsets of the slots we use. The real BgfxFrameBuilder vtable has 114
// slots; LeviLamina's FrameBuilder.h lists 110, so indices are NOT portable between the two: use these.
struct FrameBuilderSlots {
    static constexpr uintptr_t kEndFrame = 0x90;      // BgfxFrameBuilder::endFrame -> dragon::platform::BgfxContext::endFrame (the frame graph is encoded here)
    static constexpr uintptr_t kInsertEditor = 0x358; // _insert(group variant): one slot per group, the variant's tag is the index within the group
    static constexpr uintptr_t kInsertEffect = 0x360;
    static constexpr uintptr_t kInsertUi = 0x368;
    static constexpr uintptr_t kInsertSky = 0x370;
    static constexpr uintptr_t kInsertItem = 0x378;   // actors, terrain, cracks, name tags
    static constexpr uintptr_t kInsertLight = 0x380;
    static constexpr uintptr_t kInitiateTdr = 0x388;
};

// The tag of an Item-group variant {description*, tag}.
enum class ItemGroupTag : uint64_t {
    EnvironmentalText = 0,
    Nametag = 1,
    MeshFallback = 2,
    ChunkGeometry = 3,
    ChunkOccluders = 4,
    Crack = 5,
    ItemInHand = 6,
    SkinnedMesh = 7,
    BlockSelectionOverlayBlockEntity = 8,
    BlockChanges = 9,
    BatchActor = 10,
};

// Variant tags of the other groups, read from the tag byte each insert clone stores before its group-slot call (see docs/BGFX_MAP.md 6w).
enum class EffectGroupTag : uint64_t {
    UIGameface = 0, // shares the clone with the UI group (see 6w)
    BlitFlipbookTexture = 1,
    Particle = 2,
    PlayerVision = 3,
    Shadow = 4,
    CameraAimAssistHighlight = 6,
    FullscreenEffect = 7,
    EditorHighlightConfiguration = 8,
};

enum class UIGroupTag : uint64_t {
    Gameface = 0,
    HudIcon = 1,
    UIMesh = 2,
    UIText = 3,
};

enum class SkyGroupTag : uint64_t {
    AmbientAtmosphere = 0,
    Clouds = 1,
    Cubemap = 2,
    EndSky = 3,
    LegacyCubemap = 4,
    SkyStars = 5,
    CelestialBody = 7,
    VolumetricFog = 8,
    Weather = 9,
    SkyAmbientSamples = 10,
};

enum class LightGroupTag : uint64_t {
    Ambient = 0,
    Directional = 1,
    GameplayMetadata = 2,
    ServerGraphicsOverrideParameters = 5,
};

enum class EditorGroupTag : uint64_t {
    BlockVolumeBoundingBox = 0,
    GizmoHandleArrow = 1,
    GizmoHandleCube = 2,
    GizmoHandlePane = 3,
    GizmoHandleRing = 4,
    SelectionCursor = 5,
    BlockVolumeOutline = 6,
    RenderPlane = 7,
};

// The variant every _insert receives: a pointer to the description and the index of its type within the group.
struct InsertVariant {
    void* mDescription;
    uint64_t mTag;
};

// RenderBatchActorDescription: every actor of the frame in one description (measured live, docs/BGFX_MAP.md section 6c).
struct RenderBatchActorDescription {
    static constexpr uintptr_t kCountOffset = 0xE0;
    static constexpr uintptr_t kInstancesOffset = 0xE8;
    static constexpr size_t kInstanceStride = 0x48;

    // Fields from the live capture of 6d (values in the comments are the sampled first-person model). No actor, entity id or world
    // position is stored here: identity comes from RenderMark::bodyActor and its DrawItem records (DrawItem.h, 6bg/6hc).
    struct Instance {
        void* mRenderObject;   // +0x00: the per-instance object (0x300 bytes, contiguous)
        void* mModel;          // +0x08: the shared geometry resource; instances of one model share it
        void* mModelTwin;      // +0x10: the same resource 0x10 lower
        uint32_t mFlags;       // +0x18: e.g. 0xEF000006
        float mAabbMin[3];     // +0x1C: local-space bounds (-5.75, -4.6, -11.8)
        float mAabbMax[3];     // +0x28: (5.75, 12, 7.75)
        uint32_t mUnknown34;   // +0x34
        float mScale[2];       // +0x38: both 1/2048
        uint16_t mPacked[4];   // +0x40: packed halves (uv / bone transform) [I]
    };
    static_assert(sizeof(Instance) == kInstanceStride);
    static_assert(offsetof(Instance, mFlags) == 0x18);
    static_assert(offsetof(Instance, mAabbMin) == 0x1C);
    static_assert(offsetof(Instance, mAabbMax) == 0x28);
    static_assert(offsetof(Instance, mScale) == 0x38);
    static_assert(offsetof(Instance, mPacked) == 0x40);

    // What Instance::mRenderObject points at (6he): the payload of a make_shared block of 0x2D0 bytes (control vtable rva 0xF2E4ED0) that the
    // allocator places in a 0x300 size class, so the live capture's "+0x2F0 vtable, +0x2F8 {1,1}" is the NEXT block's control header, not
    // part of this object. Built in 0x6ea05a0 ("Default Render Controller Mesh"); constructor 0x4de7fb0, then init-from-source 0x4de8170.
    // This is the game's mce::Mesh: Mesh::hasDrawableData 0x4def080 reads exactly these fields (MeshData, the handle groups at
    // +0x1D8/+0x1FC/+0x220 = the mesh's GPU buffer handles, the vector at +0x248), and descriptions hold it by pointer (6ic).
    struct RenderControllerMesh {
        // A group of 15 handles, all 0xFFFF until bound (the live "slot table full of 0xFFFF").
        struct HandleGroup {
            uint16_t mCount;           // +0x00 0
            uint16_t mHandles[15];     // +0x02 0xFFFF
            uint16_t mValue20;         // +0x20 0
            uint8_t mFlag;             // +0x22 1
            uint8_t mPad23;
        };
        static_assert(sizeof(HandleGroup) == 0x24);

        uint8_t mHead[0x1C];           // +0x000 zeroed
        uint8_t mPad1C[0x14];
        uint8_t mByte30;               // +0x030 0
        uint8_t mPad31[7];
        uint8_t mByte38;               // +0x038 copied from the source's +0x38
        uint8_t mPad39[7];
        uint8_t mBlock40[0x10];        // +0x040 zeroed
        // The game's mce::MeshData (layout asserted in MeshData.h, 6ho); the capture's FLT_MAX bounds at +0x178 are mGeometry.mAABB.
        mce::MeshData mGeometry;       // +0x050
        uint8_t mBlock1B0[0x20];       // +0x1B0 zeroed
        uint32_t mCount1D0;            // +0x1D0 element count the ChunkOccluders extractor draws with, valid when mHasCount1D4 (6ig) [I: index count]
        uint8_t mHasCount1D4;          // +0x1D4 0 after construction
        uint8_t mPad1D5[3];
        HandleGroup mGroups[3];        // +0x1D8, +0x1FC, +0x220
        uint8_t mByte244;              // +0x244 0
        uint8_t mPad245[3];
        void* mVecBegin;               // +0x248 std::vector, empty
        void* mVecEnd;                 // +0x250
        void* mVecCap;                 // +0x258
        uint8_t mTail[0x60];           // +0x260 set by the builder after construction (0x6ea05a0 stores +0x260, ...)
    };
    static_assert(sizeof(RenderControllerMesh) == 0x2C0);
    static_assert(offsetof(RenderControllerMesh, mGeometry) == 0x50);
    static_assert(offsetof(RenderControllerMesh, mGroups) == 0x1D8);
    static_assert(offsetof(RenderControllerMesh, mVecBegin) == 0x248);

    static uint64_t count(const void* desc) { return *reinterpret_cast<const uint64_t*>(static_cast<const uint8_t*>(desc) + kCountOffset); }
    static const Instance* instances(const void* desc) { return *reinterpret_cast<const Instance* const*>(static_cast<const uint8_t*>(desc) + kInstancesOffset); }
};

} // namespace mce::framebuilder
