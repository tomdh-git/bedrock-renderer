#pragma once

namespace mce::framebuilder {

// Every FrameBuilder::insert<TDescription> clone of 1.26.62.01 (generated from the binary by tools/sigs/srcloc.py-style scans; docs/RENDER_CATALOG.md). A "thin" clone (size 0x139)
// stores {description*, tag} and calls its group's _insert slot; its group is certain. A fat clone (several types folded into one function, or a type whose insert is inlined into a
// larger function) lists the group only when it uses exactly one slot. Group "?" is not told apart yet.
struct DescriptionClone {
    const char* mName;
    uintptr_t mCloneRva;
    bool mThin;
    const char* mGroup; // Editor, Effect, Ui, Sky, Item, Light
};

inline constexpr DescriptionClone kDescriptionClones[] = {
    {"BlitFlipbookTextureDescription", 0x5acbe20, true, "Effect"},
    {"FullscreenEffectDescription", 0x530a1b0, false, "Effect"},
    {"LightAmbientDescription", 0x53e2c00, false, "?"},
    {"LightDirectionalDescription", 0x5370960, true, "Light"},
    {"LightPointDescription", 0x53599d0, false, "?"},
    {"RenderAtmosphereDescription", 0x53e2c00, false, "?"},
    {"RenderBatchActorDescription", 0x4e39cb0, true, "Item"},
    {"RenderBlockSelectionOverlayBlockEntityDescription", 0x539b7c0, false, "?"},
    {"RenderCameraAimAssistHighlightDescription", 0x5370e80, true, "Effect"},
    {"RenderCelestialBodyDescription", 0x5370b20, true, "Sky"},
    {"RenderChunkGeometryDescription", 0x15a6880, true, "Item"},
    {"RenderChunkOccludersDescription", 0x5369920, true, "Item"},
    {"RenderCloudsDescription", 0x53e88a0, false, "Sky"},
    {"RenderCrackDescription", 0x539fff0, false, "Item"},
    {"RenderCubemapDescription", 0x660b720, true, "Sky"},
    {"RenderEditorBlockVolumeBoundingBoxDescription", 0x6c956b0, true, "Editor"},
    {"RenderEditorBlockVolumeOutlineDescription", 0x6c961e0, true, "Editor"},
    {"RenderEditorGizmoHandleArrowDescription", 0x4c85d70, true, "Editor"},
    {"RenderEditorGizmoHandleCubeDescription", 0x4c85f30, true, "Editor"},
    {"RenderEditorGizmoHandlePaneDescription", 0x4c860f0, true, "Editor"},
    {"RenderEditorGizmoHandleRingDescription", 0x4c862b0, true, "Editor"},
    {"RenderEditorRenderPlaneDescription", 0x6d3c040, false, "Editor"},
    {"RenderEditorSelectionCursorDescription", 0x5371160, true, "Editor"},
    {"RenderEndSkyDescription", 0x53707a0, true, "Sky"},
    {"RenderEnvironmentalTextDescription", 0xe71330, false, "?"},
    {"RenderFlameBillboardDescription", 0x594cbe0, false, "?"},
    {"RenderItemInHandDescription", 0x531b180, true, "Item"},
    {"RenderLegacyCubemapDescription", 0x660b1a0, false, "Sky"},
    {"RenderMeshFallbackDescription", 0x4def480, false, "?"},
    {"RenderNametagDescription", 0x1127330, false, "Item"},
    {"RenderParticleDescription", 0x5b8d520, true, "Effect"},
    {"RenderPlayerVisionDescription", 0x53e62b0, false, "?"},
    {"RenderShadowDescription", 0x53e6c30, false, "Effect"},
    {"RenderSkinnedMeshDescription", 0x4e39f20, false, "?"},
    {"RenderSkinnedMeshDescription", 0x6b84e60, false, "?"},
    {"RenderSkyDescription", 0x5369b30, false, "?"},
    {"RenderStarsDescription", 0x5369b30, false, "?"},
    {"RenderUIGamefaceDescription", 0x1f44d80, false, "?"},
    {"RenderUIHudIconDescription", 0xe9aed0, false, "Ui"},
    {"RenderUIMeshDescription", 0x4c96140, true, "Ui"},
    {"RenderUITextDescription", 0xe71330, false, "?"},
    {"RenderVolumetricFogDescription", 0x53e3aa0, false, "?"},
    {"RenderWeatherDescription", 0x5ad5800, true, "Sky"},
    {"ShadowAtlasFrameDescription", 0x53599d0, false, "?"},
    {"SkyAmbientSamplesDescription", 0x53e3aa0, false, "?"},
    {"TransitioningVoxelVolumeDescription", 0x53599d0, false, "?"},
    {"VoxelVolumeDescription", 0x53599d0, false, "?"},
    {"gamecomponents::EditorHighlightConfiguration", 0x4c8a5b0, true, "Effect"},
    {"gamecomponents::GameplayMetadata", 0x53e5910, false, "Light"},
    {"gamecomponents::ServerGraphicsOverrideParameters", 0x6c2e820, false, "?"},
};

} // namespace mce::framebuilder
