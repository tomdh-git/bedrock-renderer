#include "client/features/render/rewrite/RewriteDescriptions.h"
#include "sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h"
#include "sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h"
#include "sdk/mc/deps/minecraft_renderer/framebuilder/BatchActorDescription.h"

// Tags: FrameBuilder.h enums for Item / Effect / Ui / Sky / Editor; the Light group follows docs/progress/descriptions.md (tag 2 GameplayMetadata, 3 LightPoint, 4 an atlas-like 0x50 block,
// 5 ServerGraphicsOverrideParameters; 6 and 7 not typed). Sizes of the untyped ones are 0.
// BatchActor (Item tag 10) is typed via bluey::batchactor::Description (BatchActorDescription.h, 0x110, 34 [V]); closes M2c for BatchActor.
static const RewriteDescInfo sRwDescTable[] = {
    {RewriteGroup::Item, 0, "EnvironmentalText", sizeof(mce::framebuilder::RenderEnvironmentalTextDescription)},
    {RewriteGroup::Item, 1, "Nametag", sizeof(mce::framebuilder::RenderNametagDescription)},
    {RewriteGroup::Item, 2, "MeshFallback", sizeof(mce::framebuilder::RenderMeshFallbackDescription)},
    {RewriteGroup::Item, 3, "ChunkGeometry", sizeof(mce::framebuilder::RenderChunkGeometryDescription)},
    {RewriteGroup::Item, 4, "ChunkOccluders", sizeof(mce::framebuilder::RenderChunkOccludersDescription)},
    {RewriteGroup::Item, 5, "Crack", sizeof(mce::framebuilder::RenderCrackDescription)},
    {RewriteGroup::Item, 6, "ItemInHand", sizeof(mce::framebuilder::RenderItemInHandDescription)},
    {RewriteGroup::Item, 7, "SkinnedMesh", sizeof(mce::framebuilder::RenderSkinnedMeshDescription)},
    {RewriteGroup::Item, 8, "BlockSelectionOverlayBlockEntity", sizeof(mce::framebuilder::RenderBlockSelectionOverlayDescription)},
    {RewriteGroup::Item, 9, "BlockChanges", sizeof(mce::framebuilder::RenderBlockChangesDescription)},
    {RewriteGroup::Item, 10, "BatchActor", sizeof(bluey::batchactor::Description)},
    {RewriteGroup::Effect, 0, "FlameBillboard", sizeof(mce::framebuilder::RenderFlameBillboardDescription)},
    {RewriteGroup::Effect, 1, "BlitFlipbookTexture", sizeof(mce::framebuilder::RenderBlitFlipbookDescription)},
    {RewriteGroup::Effect, 2, "Particle", sizeof(mce::framebuilder::RenderParticleDescription)},
    {RewriteGroup::Effect, 3, "PlayerVision", sizeof(mce::framebuilder::RenderPlayerVisionDescription)},
    {RewriteGroup::Effect, 4, "Shadow", 0},
    {RewriteGroup::Effect, 5, "FadeToBlack", 0},
    {RewriteGroup::Effect, 6, "CameraAimAssistHighlight", sizeof(mce::framebuilder::RenderAimAssistHighlightDescription)},
    {RewriteGroup::Effect, 7, "FullscreenEffect", sizeof(mce::framebuilder::RenderFullscreenEffectDescription)},
    {RewriteGroup::Effect, 8, "EditorHighlightConfiguration", sizeof(mce::framebuilder::RenderEditorHighlightDescription)},
    {RewriteGroup::Ui, 0, "Gameface", sizeof(mce::framebuilder::RenderGameFaceDescription)},
    {RewriteGroup::Ui, 1, "HudIcon", 0},
    {RewriteGroup::Ui, 2, "UIMesh", sizeof(mce::framebuilder::RenderUIMeshDescription)},
    {RewriteGroup::Ui, 3, "UIText", sizeof(mce::framebuilder::RenderUITextDescription)},
    {RewriteGroup::Sky, 0, "AmbientAtmosphere", sizeof(mce::framebuilder::RenderAtmosphereDescription)},
    {RewriteGroup::Sky, 1, "Clouds", sizeof(mce::framebuilder::RenderCloudsDescription)},
    {RewriteGroup::Sky, 2, "Cubemap", sizeof(mce::framebuilder::RenderCubemapDescription)},
    {RewriteGroup::Sky, 3, "EndSky", 0},
    {RewriteGroup::Sky, 4, "LegacyCubemap", 0},
    {RewriteGroup::Sky, 5, "SkyStars", sizeof(mce::framebuilder::RenderStarsDescription)},
    {RewriteGroup::Sky, 7, "CelestialBody", 0},
    {RewriteGroup::Sky, 8, "VolumetricFog", 0},
    {RewriteGroup::Sky, 9, "Weather", sizeof(mce::framebuilder::RenderWeatherDescription)},
    {RewriteGroup::Sky, 10, "SkyAmbientSamples", 0},
    {RewriteGroup::Light, 0, "LightAmbient", sizeof(mce::framebuilder::RenderLightAmbientDescription)},
    {RewriteGroup::Light, 1, "LightDirectional", sizeof(mce::framebuilder::RenderLightDirectionalDescription)},
    {RewriteGroup::Light, 2, "GameplayMetadata", sizeof(mce::framebuilder::RenderLightTag2Description)},
    {RewriteGroup::Light, 3, "LightPoint", sizeof(mce::framebuilder::RenderLightTag3Description)},
    {RewriteGroup::Light, 4, "LightTag4", sizeof(mce::framebuilder::RenderLightTag4Description)},
    {RewriteGroup::Light, 5, "ServerGraphicsOverrideParameters", sizeof(mce::framebuilder::RenderLightServerGraphicsOverrideDescription)},
    {RewriteGroup::Light, 6, "LightTag6", 0},
    {RewriteGroup::Light, 7, "LightTag7", 0},
    {RewriteGroup::Editor, 0, "BlockVolumeBoundingBox", 0},
    {RewriteGroup::Editor, 1, "GizmoHandleArrow", 0},
    {RewriteGroup::Editor, 2, "GizmoHandleCube", 0},
    {RewriteGroup::Editor, 3, "GizmoHandlePane", 0},
    {RewriteGroup::Editor, 4, "GizmoHandleRing", 0},
    {RewriteGroup::Editor, 5, "SelectionCursor", 0},
    {RewriteGroup::Editor, 6, "BlockVolumeOutline", 0},
    {RewriteGroup::Editor, 7, "RenderPlane", 0},
};

const RewriteDescInfo* RewriteDescriptions::find(RewriteGroup group, uint64_t tag) {
    for (const RewriteDescInfo& d : sRwDescTable)
        if (d.group == group && d.tag == tag)
            return &d;
    return nullptr;
}

size_t RewriteDescriptions::count() {
    return sizeof(sRwDescTable) / sizeof(sRwDescTable[0]);
}

const char* RewriteDescriptions::groupName(RewriteGroup group) {
    switch (group) {
    case RewriteGroup::Editor: return "Editor";
    case RewriteGroup::Effect: return "Effect";
    case RewriteGroup::Ui: return "Ui";
    case RewriteGroup::Sky: return "Sky";
    case RewriteGroup::Item: return "Item";
    case RewriteGroup::Light: return "Light";
    }
    Logger::fatal("[probe] bad group {}", static_cast<int>(group));
}
