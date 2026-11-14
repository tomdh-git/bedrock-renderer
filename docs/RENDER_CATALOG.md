# Render type catalog (1.26.62.01)

Mass-extracted from the binary's `entt::internal::pretty_function` and `__FUNCSIG__` strings (every type the game registers or serializes carries its name there). It is the vocabulary of the renderer: use it to name SDK structs and to find components. Not a layout: layouts come from live captures (docs/BGFX_MAP.md). Generated 2026-11-11; regenerate per game version.

## Framebuilder descriptions (62 types)
- `mce::framebuilder::BlitFlipbookTextureDescription`
- `mce::framebuilder::CloudLightingParameters`
- `mce::framebuilder::CloudParameters`
- `mce::framebuilder::FullscreenEffectDescription`
- `mce::framebuilder::LightAmbientDescription`
- `mce::framebuilder::LightDirectionalDescription`
- `mce::framebuilder::LightPointDescription`
- `mce::framebuilder::PerCascadeParameters`
- `mce::framebuilder::PerCascadeParameters *`
- `mce::framebuilder::PointLightBudgetParameters`
- `mce::framebuilder::PointLightBudgetParameters::ScoringWeights`
- `mce::framebuilder::PointLightClusteringParameters`
- `mce::framebuilder::PointLightShadowParameters`
- `mce::framebuilder::ProbeMetadataDeltaTriggers`
- `mce::framebuilder::ProbeRegenParameters`
- `mce::framebuilder::ReflectionParameters`
- `mce::framebuilder::RenderAtmosphereDescription`
- `mce::framebuilder::RenderBatchActorDescription`
- `mce::framebuilder::RenderBlockSelectionOverlayBlockEntityDescription`
- `mce::framebuilder::RenderCameraAimAssistHighlightDescription`
- `mce::framebuilder::RenderCelestialBodyDescription`
- `mce::framebuilder::RenderChunkGeometryDescription`
- `mce::framebuilder::RenderChunkOccludersDescription`
- `mce::framebuilder::RenderCloudsDescription`
- `mce::framebuilder::RenderCrackDescription`
- `mce::framebuilder::RenderCubemapDescription`
- `mce::framebuilder::RenderEditorBlockVolumeBoundingBoxDescription`
- `mce::framebuilder::RenderEditorBlockVolumeOutlineDescription`
- `mce::framebuilder::RenderEditorGizmoHandleArrowDescription`
- `mce::framebuilder::RenderEditorGizmoHandleCubeDescription`
- `mce::framebuilder::RenderEditorGizmoHandlePaneDescription`
- `mce::framebuilder::RenderEditorGizmoHandleRingDescription`
- `mce::framebuilder::RenderEditorRenderPlaneDescription`
- `mce::framebuilder::RenderEditorSelectionCursorDescription`
- `mce::framebuilder::RenderEndSkyDescription`
- `mce::framebuilder::RenderEnvironmentalTextDescription`
- `mce::framebuilder::RenderFlameBillboardDescription`
- `mce::framebuilder::RenderItemInHandDescription`
- `mce::framebuilder::RenderLegacyCubemapDescription`
- `mce::framebuilder::RenderMeshFallbackDescription`
- `mce::framebuilder::RenderNametagDescription`
- `mce::framebuilder::RenderParticleDescription`
- `mce::framebuilder::RenderPlayerVisionDescription`
- `mce::framebuilder::RenderShadowDescription`
- `mce::framebuilder::RenderSkinnedMeshDescription`
- `mce::framebuilder::RenderSkyDescription`
- `mce::framebuilder::RenderStarsDescription`
- `mce::framebuilder::RenderUIGamefaceDescription`
- `mce::framebuilder::RenderUIHudIconDescription`
- `mce::framebuilder::RenderUIMeshDescription`
- `mce::framebuilder::RenderUITextDescription`
- `mce::framebuilder::RenderVolumetricFogDescription`
- `mce::framebuilder::RenderWeatherDescription`
- `mce::framebuilder::ShadowAtlasFrameDescription`
- `mce::framebuilder::ShadowParameters`
- `mce::framebuilder::ShadowRange`
- `mce::framebuilder::SkyAmbientSamplesDescription`
- `mce::framebuilder::TransitioningVoxelVolumeDescription`
- `mce::framebuilder::VoxelVolumeDescription`
- `mce::framebuilder::gamecomponents::EditorHighlightConfiguration`
- `mce::framebuilder::gamecomponents::GameplayMetadata`
- `mce::framebuilder::gamecomponents::ServerGraphicsOverrideParameters`

Group slots, clone RVAs and tags: docs/BGFX_MAP.md section 6g and `src/sdk/mc/deps/minecraft_renderer/framebuilder/DescriptionClones.h`.

## RenderDragon types
- `dragon::framerenderer::DeferredShadingParameters`
- `dragon::framerenderer::modules::ExposureCompensationType`
- `dragon::framerenderer::modules::IBLConvolutionType`
- `dragon::framerenderer::modules::IBLParameters`
- `dragon::framerenderer::modules::ScreenSpaceReflectionsParameters`
- `dragon::framerenderer::modules::TemperatureGrading::Type`
- `dragon::framerenderer::modules::Tonemapper`
- `dragon::framerenderer::modules::VolumeScatteringParameters`

Plus named functions: `dragon::tasks::GraphicsTasks::{frame,_render,waitForPreviousFrame}`, `dragon::platform::BgfxContext::endFrame`, `dragon::res::DragonFrameResources`, `dragon::frameobject::IntraFrameAllocator`, `dragon::framerenderer::RenderContext`, `dragon::framerenderer::modules::Declarator`, `dragon::texturestreaming::TaskGroupExecutor::{execute,_chainRemaining}`, `dragon::utils::PipelineDiskCache::tick`. Pass names are NOT in the binary as strings (release strips them; passes are identified by 64-bit hashes): recover them by hashing candidate names.

## Lighting (LightingGroup)
- `LightingGroup::AmbientLightImpl<1, 21, 40>`
- `LightingGroup::AmbientLightImpl<1, 26, 0>`
- `LightingGroup::Emissive`
- `LightingGroup::KeyframedDirectionalLightImpl<LightingGroup::RGB>`
- `LightingGroup::KeyframedDirectionalLightImpl<LightingGroup::RGBA>`
- `LightingGroup::LightingDescription`
- `LightingGroup::LightingImpl<1, 21, 40>`
- `LightingGroup::LightingImpl<1, 21, 40>::LightingSettings`
- `LightingGroup::LightingImpl<1, 21, 60>`
- `LightingGroup::LightingImpl<1, 21, 60>::LightingSettings`
- `LightingGroup::LightingImpl<1, 21, 70>`
- `LightingGroup::LightingImpl<1, 21, 70>::LightingSettings`
- `LightingGroup::LightingImpl<1, 21, 80>`
- `LightingGroup::LightingImpl<1, 21, 80>::LightingSettings`
- `LightingGroup::LightingImpl<1, 21, 80>::LightingSettings::DirectionalLights`
- `LightingGroup::LightingImpl<1, 26, 0>`
- `LightingGroup::LightingImpl<1, 26, 0>::LightingSettings`
- `LightingGroup::OrbitalLights<LightingGroup::RGB>`
- `LightingGroup::OrbitalLights<LightingGroup::RGBA>`
- `LightingGroup::SkyIntensityImpl<1, 21, 70>`
- `LightingGroup::SkyIntensityImpl<1, 26, 0>`
- `LightingGroup::StaticDirectionalLight`

## Render/visual configuration types
- `BlockLightConfiguration`
- `BlockLightQuality`
- `BloomConfiguration`
- `CloudConfiguration`
- `CloudQuality`
- `ColorGraderConfig::ColorGradingParametersSrcV0::ColorGradingSettings`
- `ColorGraderConfig::ColorGradingParametersSrcV1::ColorGradingSettings`
- `DeferredLightingConfiguration`
- `DeferredRenderingGroup::DeferredRenderingSettings`
- `FogDefinitionCerealParser::FogParametersSrcV0::FogSettings`
- `LightingGroup::LightingImpl<1, 21, 40>::LightingSettings`
- `LightingGroup::LightingImpl<1, 21, 60>::LightingSettings`
- `LightingGroup::LightingImpl<1, 21, 70>::LightingSettings`
- `LightingGroup::LightingImpl<1, 21, 80>::LightingSettings`
- `LightingGroup::LightingImpl<1, 26, 0>::LightingSettings`
- `ReflectionConfiguration`
- `ReflectionsQuality`
- `RenderDistanceConfiguration`
- `RenderDistanceConfiguration::RenderDistanceConfig`
- `ShadowConfiguration`
- `ShadowQuality`
- `ShadowStylizationConfig::ShadowStylizationConfigSettings`
- `ShadowStylizationConfig::ShadowStylizationConfigSettings::ShadowStylizationSettings`
- `VolumetricFogConfiguration`
- `VolumetricFogQuality`
- `WaterConfig::WaterConfigSettingsV0::WaterSettings`
- `WaterConfig::WaterConfigSettingsV1::WaterSettings`
- `WaterConfig::WaterConfigSettingsV2::WaterSettings`
- `WaterConfig::WaterConfigSettingsV3::WaterSettings`
- `WaterConfig::WaterConfigSettingsV4::WaterSettings`

## Registry components related to rendering
- `AtomicEntityAnimStateComponent`
- `AtomicEntityAnimationContextComponent`
- `AtomicEntityComponent`
- `AtomicEntityInitDataComponent`
- `AtomicEntityLocatorComponent`
- `AtomicEntityMolangVariablesComponent`
- `AtomicEntityMotionComponent`
- `AtomicEntityNeedsInitializationComponent`
- `AtomicEntityParticleTrackingComponent`
- `AtomicEntityShouldRenderComponent`
- `AtomicEntitySoundTrackingComponent`
- `AtomicEntityTransformComponent`
- `ClientParticleInitializationComponent`
- `ClientParticleTerminationComponent`
- `ClientParticleTrackingComponent`
- `DynamicPropertiesComponent`
- `DynamicRenderOffsetComponent`
- `EmitParticleRequestComponent`
- `FogCommandComponent`
- `GlobalActorRenderComponent`
- `GlobalTextureGroupStateComponent`
- `ParticleEventDispatcherComponent`
- `ParticleEventRequestQueueComponent`
- `PassengerComponent`
- `PassengerOfBlockChangedComponent`
- `PassengerOfBlockComponent`
- `PassengerRenderingRidingOffsetComponent`
- `PassengerYRotLimitComponent`
- `PassengersChangedFlagComponent`
- `PassengersToPositionComponent`
- `RelativeShadowOffsetComponent`
- `RenderOffsetsItemComponent`
- `RenderPositionComponent`
- `RenderRotationComponent`
- `UpdateAndRenderThrottleComponent`
- `VehicleComponent`
- `VehicleInputIntentComponent`
- `VehicleRenderingRidingOffsetComponent`

## Camera components (MinecraftCamera::* and VanillaCamera::*, 76)
- `MinecraftCamera::ActiveCameraComponent`
- `MinecraftCamera::AllowInsideBlockRenderComponent`
- `MinecraftCamera::CameraActivationRequestComponent`
- `MinecraftCamera::CameraAdjustedPositionComponent`
- `MinecraftCamera::CameraAnimationDataComponent`
- `MinecraftCamera::CameraAnimationStorageComponent`
- `MinecraftCamera::CameraAttachComponent`
- `MinecraftCamera::CameraAttachToEntityComponent`
- `MinecraftCamera::CameraAvoidanceComponent`
- `MinecraftCamera::CameraBlendStateComponent`
- `MinecraftCamera::CameraCalculateAnimationComponent`
- `MinecraftCamera::CameraComponent`
- `MinecraftCamera::CameraCustomFovComponent`
- `MinecraftCamera::CameraCustomFovEaseComponent`
- `MinecraftCamera::CameraDirectLookComponent`
- `MinecraftCamera::CameraEntityStateComponent`
- `MinecraftCamera::CameraFadeEffectComponent`
- `MinecraftCamera::CameraFirstPersonClimbingComponent`
- `MinecraftCamera::CameraFirstPersonComponent`
- `MinecraftCamera::CameraFlyMoveComponent`
- `MinecraftCamera::CameraGlobalInstructionComponent`
- `MinecraftCamera::CameraGlobalSplineComponent`
- `MinecraftCamera::CameraIgnoreInstructionValuesComponent`
- `MinecraftCamera::CameraIgnoreStartingValuesComponent`
- `MinecraftCamera::CameraInstructionComponent`
- `MinecraftCamera::CameraInstructionsComponent`
- `MinecraftCamera::CameraLiquidOffsetComponent`
- `MinecraftCamera::CameraLocalSpaceRotationComponent`
- `MinecraftCamera::CameraLookAtComponent`
- `MinecraftCamera::CameraLookAtPositionComponent`
- `MinecraftCamera::CameraOffsetComponent`
- `MinecraftCamera::CameraOrbitComponent`
- `MinecraftCamera::CameraPerspectiveOptionComponent`
- `MinecraftCamera::CameraPresetComponent`
- `MinecraftCamera::CameraRenderFirstPersonObjectsComponent`
- `MinecraftCamera::CameraRenderPlayerModelComponent`
- `MinecraftCamera::CameraSetUpAnimationComponent`
- `MinecraftCamera::CameraShakeSupportComponent`
- `MinecraftCamera::CameraStartingValuesComponent`
- `MinecraftCamera::CameraTargetComponent`
- `MinecraftCamera::CameraTargetSettingsComponent`
- `MinecraftCamera::CameraThirdPersonBoomComponent`
- `MinecraftCamera::CameraThirdPersonComponent`
- `MinecraftCamera::CameraThirdPersonFixedBoomComponent`
- `MinecraftCamera::CameraTimeComponent`
- `MinecraftCamera::CameraTimeOverrideComponent`
- `MinecraftCamera::CameraUsageComponent`
- `MinecraftCamera::CameraWorldSpaceRotationComponent`
- `MinecraftCamera::CurrentInputCameraComponent`
- `MinecraftCamera::DeathCameraComponent`
- `MinecraftCamera::DebugCameraComponent`
- `MinecraftCamera::DefaultInputCameraComponent`
- `MinecraftCamera::ExtendPlayerRenderingComponent`
- `MinecraftCamera::FixedBoomOrientationComponent`
- `MinecraftCamera::GameCameraComponent`
- `MinecraftCamera::GameplayAffectsFovComponent`
- `MinecraftCamera::OverrideCameraComponent`
- `MinecraftCamera::PlayerAudioListenerComponent`
- `MinecraftCamera::PlayerStateAffectsRenderingComponent`
- `MinecraftCamera::RedirectCameraInputComponent`
- `MinecraftCamera::RenderCameraComponent`
- `MinecraftCamera::SeatCameraRelaxDistanceSmoothingOverrideComponent`
- `MinecraftCamera::SeatThirdPersonCameraRadiusOverrideComponent`
- `MinecraftCamera::SpecialCameraModeComponent`
- `MinecraftCamera::StationaryCameraComponent`
- `MinecraftCamera::TargetCameraOrientationComponent`
- `MinecraftCamera::TargetCameraOutOfRangeComponent`
- `MinecraftCamera::TargetCameraRotationLimitComponent`
- `MinecraftCamera::TargetCameraRotationSpeedComponent`
- `MinecraftCamera::TargetCameraSetInitialOrientationComponent`
- `VanillaCamera::CameraBobComponent`
- `VanillaCamera::CameraComfortMoveVRComponent`
- `VanillaCamera::CameraPortalDistortionComponent`
- `VanillaCamera::CameraSleepVignetteComponent`
- `VanillaCamera::CameraVehicleRotationComponent`
- `VanillaCamera::UpdatePlayerFromCameraComponent`

## Vibrant Visuals frame renderer: pass/material labels and the uniform set (function 0x55f1450, size 0x4E144, 1.26.62.01)

This one function registers the VV deferred renderer's passes and uniforms; the strings it references are the names. (Pass identity at runtime is a 64-bit hash of these names.)

Pass / material-variant labels:
- `Shadow Cascades`
- `VolumetricsShadows`
- `SampleCascadedShadows`
- `PopulateVolume`
- `GeometryPrepassAlphaTest`
- `DepthOnlyAlphaTest`
- `WaterDepthBufferBlit`
- `Core/Screen/Blit`
- `BlitUncompressed`
- `ForwardPBRTransparent`
- `TransparentDegamma`
- `ForceForwardPBROpaque`
- `SSRColorBufferBlit`
- `ForwardPBROpaque`
- `ForwardPBRAlphaTest`
- `RasterizedOpaque`
- `RasterizedAlphaTest`
- `RasterizedTransparent`
- `FullScreenOverlayTransparent`
- `FSR1`
- `SkySamplesConfig`
- `VolumeScatteringEnabledAndPointLightVolumetricsEnabled`
- `CascadesPerSet`
- `CascadesParameters`
- `CascadesShadowProj`
- `CascadesShadowInvProj`
- `SkyAmbientSamples`

Uniforms and resources (the VV shader interface):
- `Pys`
- `PTlE`
- `PclE`
- `pclE`
- `PdiE`
- `pdiE`
- `viE`
- `PfkE`
- `ViewportScale`
- `DitherParams`
- `DitherParams2`
- `ColorGrading_OptimizeGammaCorrection`
- `SubPixelOffset`
- `AtmosphericScatteringToggles`
- `SunDir`
- `MoonDir`
- `SunColor`
- `SkyboxAmbientIlluminance`
- `SkyboxParameters`
- `MoonColor`
- `SkyZenithColor`
- `SkyHorizonColor`
- `FogColor`
- `FogAndDistanceControl`
- `FogSkyBlend`
- `AtmosphericScattering`
- `UndergroundFogColor`
- `CameraLightIntensity`
- `CameraAmbientContribution`
- `WorldOrigin`
- `BiomeBlendingMap`
- `VoxelBuffer`
- `GpuEntryBuffer`
- `GpuEntryBufferCapacity`
- `WaterSurfaceEnabledAndExtinctionDistShift`
- `WaterSurfaceParameters`
- `WaterSurfaceWaveParameters`
- `WaterSurfaceOctaveParameters`
- `Time`
- `DirectionalShadowModeAndCloudShadowToggleAndPointLightToggle`
- `QuantizationParameters`
- `SceneNearFar`
- `RenderChunkFogAlpha`
- `ManhattanDistAttenuationEnabled`
- `PointLightAttenuationWindowEnabled`
- `PointLightAttenuationWindow`
- `DirectionalLightSourceWorldSpaceDirection`
- `DirectionalLightSourceDiffuseColorAndIlluminance`
- `DirectionalLightSourceShadowDirection`
- `BiomeBlendingParameters`
- `BiomeBlendingLastUpdatePosition`
- `DiffuseSpecularEmissiveAmbientTermToggles`
- `DirectionalLightSkyLightHeuristicToggles`
- `SubsurfaceScatteringContributionAndDiffuseWrapValueAndFalloffScale`
- `EndPortalEmissiveMultiplierAndDesaturation`
- `GlowStrength`
- `EmissiveMultiplierAndDesaturationAndCloudPCFAndContribution`
- `CloudShadowProj`
- `CloudShadowsVisible`
- `PlayerShadowProj`
- `NdLFloor`
- `PointLightNdLFloor`
- `ShadowFilterOffsetAndRangeFarAndMapSizeAndNormalOffsetStrength`
- `QuantizationPrecisionRoundingParameters`
- `PreExposureEnabled`
- `BlockBaseAmbientLightColorIntensity`
- `SkyAmbientLightColorIntensity`
- `BlockLightIndirectSpecularIntensity`
- `ClusterDimensions`
- `ClusterNearFarWidthHeight`
- `ClusterSize`
- `PointLightProj`
- `PointLightInvProj`
- `PointLightShadowAtlasResolution`
- `PointLightShadowParams1`
- `ClusterDepthBounds`
- `PointLightPreCalcValues`
- `AmbientLightParams`
- `BrdfLUT`
- `WaterExtinctionCoefficients`
- `PreviousFrameAverageLuminance`
- `ConvolutionType`
- `IBLParameters`
- `IBLSkyFadeParameters`
- `SpecularIBLRecords`
- `LastSpecularIBLIdx`
- `ScatteringBuffer`
- `CascadedShadowBufferOut`
- `CascadedShadowBuffer`
- `PreviousCascadedShadowBuffer`
- `VolumeDimensions`
- `VolumeNearFar`
- `Native`
- `LimitedAt256`
- `LimitedAt128`
- `ScatteringBufferOut`
- `ScreenSpaceWaterFrontFaceDepthAndNormal`
- `ScreenSpaceWaterBackFaceDepthAndNormal`
- `FbIn`
- `FbOut`
- `MatTexture`
- `CloudLightingUniforms`
- `CloudLightingToggles`
- `CloudViewport`
- `SSRParameters`
- `CausticsTexture`
- `CausticsTextureParameters`
- `SSRTexture`
- `CausticsParameters`
- `AdaptedFrameAverageLuminance`
- `ColorPostProcessing`
- `DummyUniform`
- `GammaScreenColorPostProcessing`
- `Color0`
- `Color1`
- `Color2`

GBuffer targets named in the RTX/upscaler path (slot 64, 0xe8403d0): GBuffer.Albedo, .Normals, .Roughness, .Specular, .Subsurface, .ShadingModelId, .MaterialId, WaterSurfaceGBuffer, MotionVectors3D, MotionVectorsReflection, IsParticleMask.

## RenderDragon resource transactions (RTTI, 16 types)

`CreateVertexBufferTransaction`, `CreateIndexBufferTransaction`, `res::CreateTextureTransaction`, `res::CreateCompressedTextureTransaction`, `res::CreateCubemapTransaction`, `res::CreatePoolTextureTransaction`, `res::CreateReadbackTextureTransaction`, `res::WrapApiTextureTransaction`, `CreateShaderBufferTransaction`, `CreatePoolShaderBufferTransaction`, `UpdateShaderBufferTransaction`, `CreateMaterialTransaction`, `CreateMaterialImmediateTransaction`, `CreateImageReadBackTransaction`, `CreateVertexOnlyAccelerationStructureTransaction`, `CreateTopLevelAccelerationStructureTransaction`. These are the commands the game thread queues for the render thread's resource creation (the "Deferred Texture Transactions" label in BgfxFrameBuilder::endFrame); their vtables (RTTI type descriptors at rva 0x123b8fe0.. in .data) are where creation can be observed or replaced.

## RTTI coverage

The game keeps RTTI for only ~1950 types (673 with vtables): almost none of the renderer's own classes (BgfxFrameBuilder, the extractors, the D3D12 contexts have no RTTI). Class identity comes from `__FUNCSIG__`/assert strings, vtable shapes and entt `pretty_function` names, not RTTI.

## Render ECS vocabulary (from the binary's mangled template names, 1.26.62.01) [V]

The exe contains ~5,300 long mangled template-instantiation strings (offsets in `scratchpad/mangled.txt`, e.g. rva 0x124b3100..0x124ea780 region) for the pass-declaration templates `dragon::framerenderer::drawutils::...<Frame<components...>, RenderContext, BindFramebufferColor/Depth, BindShaderBuffer, BatchPolicy...>`. They list the full entity-component set of the registry (`dragon::frameobject::BasicRenderRegistry<ViewSetId, ...>`). Three frame renderers exist, selected by resource type: `bgfxbridge::{FancyFrameRendererResources, VibrantVisualsFrameRendererResources, RTXMinecraftFrameRendererResources}` (namespace `mce::framebuilder::bgfxbridge`).

Generic components (`dragon::frameobject::components`, 34): AlphaTest, AmbientLight, AtlassedComponent, Blit, BoundingVolume, Cubemap, DirectionalLight, DynamicShadowCaster, ForceForwardPBR, ForceRasterization, ForceRasterizationWithMultiply, GpuValidationError, InitiateTDR, LightParameters, LightSource, MaterialFilter, MeshFilter, Opaque, PassState, PointLight, PreBlasSkinningDispatch, RaytraceObject, RenderTarget, ShadowSource, SortIndex, SortOrigin, StaticCascadedShadowMapCaster, StaticShadowCaster, StencilWrite, Transform, Transparent, UI, UIElement, ViewSetId.

Default pass tags (`defaultpasses::components`, 6): AlphaTest, Blit, Opaque, StencilWrite, Transparent, UI.

Game components (`mce::framebuilder::gamecomponents`, 55): ActorShadow, AlphaTestCracks, Atmosphere, BlendedCracksObject, BlockChanges, CloudObject, ColorCorrectedUI, DeferredWater, EditorHighlightConfiguration, FadeToBlackEffect, FirstPersonPlayerShadowCaster, FullScreenOverlayObject, FullScreenOverlayObjectDoNotRenderInScreenshot, Gameface, GameplayMetadata, Highlighted, IBLClouds, InLevelCubeMapObject, InMenuCubeMapObject, InsideBlockEffect, ItemInHandObject, ItemShadow, Lead, MotionOnly, NameTag, NonShadowOnlyObject, OverlayUI, ParticleObject, PersistentUIElement, PlayerUI, PlayerVision, SceneObject, SceneObjectActors, SceneObjectBanners, SceneOverlayObject, SceneSky, SceneSkyObject, SceneVolumeBuffers, ScreenshotCapture, SelectionOverlayObject, ServerGraphicsOverrideParameters, ShadowAtlasFrameData, ShadowOverlay, ShadowVolume, SimpleItemShadow, SimpleShadow, SkyAmbientSamples, ThirdPersonItemInHandObject, TransitioningVolumeBuffers, TransparentItemInWorldObject, UIMeshCapture, UIStructureVolumeCapture, VolumetricFog, VoxelVolumeBuffers, WaterHoleObject.

Framerenderer helper types: GenericPassSet, GenericPreprocessingSet, GenericPassContext, PassStateOverride, RenderContext, TileDrawParameters, TileRenderDetails, SortMode, SortedView, `batchpolicy::BatchPolicy/BatchPolicyBase` (variant of lambdas), `framegraph::dependency::BindFramebufferColor/Depth/BindShaderBuffer`, `framegraph::ResourceInitialization`.

Consequence: a pass = `drawutils::<fn>(Declarator, GenericPassContext<Frame<components...>>, SortMode, name HashedString, BatchPolicy variant, ...)`. The set of component tags a pass selects by IS the identity of what it draws (e.g. ActorShadow + DynamicShadowCaster = actor shadows; SceneObjectActors + NonShadowOnlyObject = actors in the main view; NameTag, ParticleObject, CloudObject, SceneSkyObject, ItemInHandObject, ThirdPersonItemInHandObject, TransparentItemInWorldObject, WaterHoleObject, InsideBlockEffect, FadeToBlackEffect, PlayerVision are the per-feature selectors).
