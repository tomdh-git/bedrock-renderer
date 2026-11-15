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

// Variant tags of the other groups. Every row below was re-checked in the D12 pass (docs/functions/ui_editor_descriptions.md, BGFX_MAP 6uie): the tag byte each insert
// clone stores before its group-slot call ([V] = `mov byte ptr [..],N` then `call [vtbl+slot]` in the clone's own listing), and the group visitor's jump-table case count.
// Effect: visitor 0x666aca0 has 9 cases. 0 FlameBillboard (clone 0x594cbe0: tag 0 stored at 0x594eb1f, slot 0x360 at 0x594eb29), 1 BlitFlipbook (0x5acbe94), 2 Particle
// (0x5b8d594), 3 PlayerVision (0x53e66fc), 4 Shadow (0x53e73ef), 6 CameraAimAssistHighlight (0x5370ef4), 7 FullscreenEffect (0x530a67b), 8 EditorHighlight (0x4c8a624).
// 5 FadeToBlack has no clone found; its name comes from the variant order (BGFX_MAP 6g) and its visitor case (0x666afde, FNV key lookup) [I]. The old value
// `UIGameface = 0` was wrong: the Gameface clone 0x1f44d80 stores tag 0 (0x1f451e5) and calls the UI slot 0x368, so Gameface is UIGroupTag 0, not an Effect.
enum class EffectGroupTag : uint64_t {
    FlameBillboard = 0,
    BlitFlipbookTexture = 1,
    Particle = 2,
    PlayerVision = 3,
    Shadow = 4,
    FadeToBlack = 5,
    CameraAimAssistHighlight = 6,
    FullscreenEffect = 7,
    EditorHighlightConfiguration = 8,
};

// UI: visitor 0x6664a00, 5 cases, jump table 0xF2BF468 (entries 0x6664a6c 0x6664d51 0x6664bd6 0x6664c83 0x6664aab). Clone tag stores: Gameface 0x1f451e5, HudIcon 0xe9b45b,
// UIMesh 0x4c961b4, UIText 0xe7217f. UIImGui (4): case 0x6664aab builds the material "Debug/ImGui" (lea 0xF5AD096, length 0xB at 0x6664af7) [V]; no clone found.
enum class UIGroupTag : uint64_t {
    Gameface = 0,
    HudIcon = 1,
    UIMesh = 2,
    UIText = 3,
    UIImGui = 4,
};

enum class SkyGroupTag : uint64_t {
    AmbientAtmosphere = 0,
    Clouds = 1,
    Cubemap = 2,
    EndSky = 3,
    LegacyCubemap = 4,
    SkyStars = 5,
    Stars = 6,       // visitor case 0x6656812 (docs/functions/66560f0_sky_cases.md section 5); the shared Sky/Stars clone 0x5369b30 stores 5 at 0x536a2d8
    CelestialBody = 7,
    VolumetricFog = 8,
    Weather = 9,
    SkyAmbientSamples = 10,
};

// Light: visitor 0x6640d80, 8 cases, jump table 0xF2BF2B0. Tags 2,3,4,6,7 are the clone tag stores (0x53e5fb4, 0x535a9b7, 0x535a696, 0x535ad34, 0x535aeb9; the types come
// from the zone records, docs/functions/6640d80_light_visitor.md). This corrects the BGFX_MAP 6g order, which had LightPoint at 2 and GameplayMetadata at 3.
enum class LightGroupTag : uint64_t {
    Ambient = 0,
    Directional = 1,
    GameplayMetadata = 2,
    LightPoint = 3,
    ShadowAtlasFrame = 4,
    ServerGraphicsOverrideParameters = 5,
    VoxelVolume = 6,
    TransitioningVoxelVolume = 7,
};

// Editor: visitor 0x66742f0, 8 cases, jump table 0xF2BF520 (0x6674388 0x667499f 0x6674518 0x667463c 0x66743f4 0x6674ac3 0x6674d02 0x6674760). Tag stores in the clones:
// 0 0x6c95724, 1..4 0x4c85de4 / 0x4c85fa4 / 0x4c86164 / 0x4c86324, 5 0x53711d4, 6 0x6c96254, 7 0x6d3d32d; the types come from the zone records (tools/sigs/srcloc.py).
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
    // Producer 0x4e355a0 (listing docs/data/listings/batchactor_producer_4e355a0_4e3606c.txt, call @4e35ddf, description at [rbp-0x20], so description offset = rbp offset + 0x20).
    // D11 re-read: the zero fill covers +0x00..+0x8F; the full path then stores the head and nine spans ({count, data} pairs copied from vectors of the actor-renderer's frame
    // object, r10) up to the pair at +0x100/+0x108 (mov [rbp+0xE0],r8 @4e35d9e, mov [rbp+0xE8],rcx @4e35dab); the short path zeroes +0xF0..+0x10F (@4e35dc7). Last store ends at
    // +0x110, so the description is at least 0x110 bytes [V extent; the earlier 0x100 stopped one pair short]. Meanings of the spans are [I] (strides from the magic divides).
    static constexpr size_t kMinSize = 0x110;
    static constexpr uintptr_t kCountOffset = 0xE0;
    static constexpr uintptr_t kInstancesOffset = 0xE8;
    static constexpr size_t kInstanceStride = 0x48;
    // Head stores: float[7] at +0x00 (movups [rcx] / movsd [rcx+0x10] / movss [rcx+0x18] @4e35b40..4e35b51, the 0.67 0.82 .. 192.0 block of 6c), u16 at +0x1C (@4e35b5e,
    // widened from a byte), byte +0x30 = 0 (@4e35b62), 16 bytes at +0x34 (@4e35b69), byte +0x60 = 0 (@4e35b6d).
    // Span table: description offset of {u64 count, T* data}, element stride of that span, and the source vector (offsets in r10) [V stores, I roles]:
    //   +0x68 stride 8 (r10+0xF0/+0xF8)   +0x78 stride 2 (r10+0x18/+0x20)   +0xC0 stride 0x14 (r10+0xD8/+0xE0)   +0xD0 stride 0x34 (r10+0x108/+0x110)
    //   +0xE0 stride 0x48 = the instances (r10+0x120/+0x128)   +0xF0 stride 0x40 (r10+0x138/+0x140)   +0x100 stride 0x40 (r10+0x150/+0x158)
    // and seven raw qwords at +0x88,+0x90,+0x98,+0xA0,+0xA8,+0xB0,+0xB8 copied from r10+0x30,+0x48,+0x60,+0x78,+0x90,+0xA8,+0xC0 (the begin pointers of seven vectors).
    struct Span {
        uint64_t mCount;
        const void* mData;
    };
    static constexpr uintptr_t kSpan68 = 0x68, kSpan78 = 0x78, kSpanC0 = 0xC0, kSpanD0 = 0xD0, kSpanF0 = 0xF0, kSpan100 = 0x100;
    static constexpr uintptr_t kRawBegins = 0x88; // seven qwords, stride 8
    static_assert(sizeof(Span) == 0x10);

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
