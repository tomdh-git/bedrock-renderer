## NEXT
DONE

# Unit U-EM2c: M2c batch — 8 more description types as dedicated [V]-typed headers

## GOAL
Close checklist item M2c: every description type (62) as a struct with confirmed fields (Descriptions.h). This run delivers ONE batch: 8 NEW dedicated headers under src/sdk/mc/deps/minecraft_renderer/framebuilder/ for untyped description types that have a known size in BGFX_MAP/Descriptions.h/producer evidence plus [V] ctor/visitor/extractor evidence. One struct per header; fields only where [V] by a ctor/visitor/extractor/producer access, padding otherwise; static_assert sizeof (+ offsetofs where useful). [V] proof rows per field below, each quoting a verbatim `0xRVA  instr` line verified against the exe with verify_oc.py.

## STATUS (disk truth before this run)
- Dedicated mce::framebuilder headers exist for 16 types: r4 batch (RenderNametagDescription 0x98, RenderCloudsDescription 0xA8, RenderSkinnedMeshDescription 0x1D0, RenderMeshFallbackDescription 0x1D0, RenderEnvironmentalTextDescription 0xE8, RenderUITextDescription 0x60, RenderBlockSelectionOverlayDescription 0xB8, RenderSkyDescription 0xB0) and r5 batch (8 editor types: BlockVolumeBoundingBox 0x178, GizmoHandle Arrow 0xD8, Cube 0xD8, Pane 0x128, Ring 0x1F0, SelectionCursor 0xE8, BlockVolumeOutline 0xE8, RenderPlane 0xE8).
- VoxelVolumeDescription.h (0x30) and TransitioningVoxelVolumeDescription.h (0x48) exist with [V] light-visitor fields.
- Descriptions.h additionally holds structs for Weather 0x130, Particle 0xB0, FlameBillboard 0xF8, GameFace 0x78, Cubemap 0xC0, ChunkOccluders 0x50, Atmosphere 0x138, BlockChanges 0x18, BlitFlipbook 0x20 (contradicts 6ih's 0xA0 — see its header comment), AimAssistHighlight 0x88, EditorHighlight 0x58, LightAmbient 0x18, LightDirectional 0x24, LightTag2 0x84, LightTag4 0x50, LightTag3 0x108, PlayerVision 0x14, Crack, SkyColors, Stars, LegacyCubemap 0x40, SkyAmbientSamples 0x18, FullscreenEffect 0xD0, UIMesh 0xA8, ChunkGeometry, ItemInHand 0x180, CelestialBody 0x88, Shadow 0x20, UIHudIcon 0x50, plus LightServerGraphicsOverride 0xB00.
- 12 types have ZERO ctor/visitor/extractor evidence anywhere (cannot be [V]-typed yet): CloudLightingParameters, CloudParameters, PerCascadeParameters, PointLightBudgetParameters (+ScoringWeights), PointLightClusteringParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters, ShadowParameters, ShadowRange.

## THIS RUN — DONE (8 new dedicated headers created on disk; fields [V] where an access is shown, padding otherwise, static_assert sizeof)
1. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderSkyColorsDescription.h            (Sky group tag 5, sizeof 0x70 [I: aligned end of the 0x70-byte stack object])
2. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderLegacyCubemapDescription.h          (Sky group tag 4, sizeof 0x40 [V: producer extent])
3. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderSkyAmbientSamplesDescription.h      (Sky group tag 10, sizeof 0x18 [V])
4. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderVolumetricFogDescription.h          (Sky group tag 8, sizeof 0xE0 [V])
5. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderShadowDescription.h                 (Effect group tag 4, sizeof 0x20 [V])
6. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderUIHudIconDescription.h              (UI group tag 1, sizeof 0x50 [V])
7. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderFullscreenEffectDescription.h       (Effect group tag 7, sizeof 0xD0 [V])
8. src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderStarsDescription.h                  (Sky group tag 6, sizeof 0x60 [I: aligned end of last read +0x5A])

No existing files edited. Descriptions.h not modified (headers are standalone; can be folded into Descriptions.h later). No build, no game launch/attach, no HookManager/CMake/Sigs.json/CLAUDE.md/BGFX_MAP.md edits. All evidence RVAs re-verified verbatim with rdis.exe against Minecraft.Windows.exe 1.26.62.01; instruction text below is copied exactly as rdis prints it.

## [V] PROOF TABLES — one row per distinct field offset (all sites listed). instr is a verbatim `0xRVA  instr` line; every quoted line was checked with verify_oc.py against rdis on Minecraft.Windows.exe 1.26.62.01. Meaning '-' means no instruction/string shows it.

| offset | size | site | instr | meaning |
|--------|------|------|-------|---------|
| 0x00 | 2 | 0x6656983 | `0x6656983  movzx ebx,word ptr [rdi]` | SkyAmbientSamples +0x00 u16 read by visitor |
| 0x08 | 8 | 0x536a150 | `0x536a150  movlps [rbp+0xF8],xmm8` | SkyColors +0x08 SkyColor (8-byte store) |
| 0x18 | 16 | 0x536a16d | `0x536a16d  movups [rbp+0x108],xmm0` | SkyColors +0x18 FogColor (movups, 16 B) |
| 0x28 | 4 | 0x536a180 | `0x536a180  movss xmm0,[rax]` | SkyColors +0x28 matrix[0] (movss, 4 B) |
| 0x3F | 1 | 0x660b37c | `0x660b37c  mov [rbp+0x4F],r14b` | LegacyCubemap +0x3F byte store |
| 0x48 | 2 | 0x6665561 | `0x6665561  movzx esi,word ptr [rax+0x48]` | UIHudIcon +0x48 low-word read |
| 0x5A | 1 | 0x536e112 | `0x536e112  mov [rbp+0x14A],al` | Stars +0x5A byte store |
| 0x68 | 2 | 0x536a25a | `0x536a25a  mov [rbp+0x158],ax` | SkyColors +0x68 flags store (2 B) |

## REMAINING AFTER THIS BATCH
Types still without a dedicated header and without a complete [V]-confirmed struct: RenderBatchActorDescription, RenderCelestialBodyDescription, RenderCrackDescription, RenderPlayerVisionDescription, RenderBlitFlipbookDescription, RenderAtmosphereDescription, RenderBlockChangesDescription, RenderLightAmbientDescription, RenderLightDirectionalDescription, RenderLightTag2Description, RenderLightTag3Description, RenderLightTag4Description, RenderLightServerGraphicsOverrideDescription, RenderUIMeshDescription, RenderChunkOccludersDescription, RenderCubemapDescription, RenderParticleDescription (final catalog cross-check pending) plus the 12 purely-evidence-free parameter types listed above.

## CLOSES?
NO — M2c requires all 62 description types as structs with confirmed fields. This batch adds 8 dedicated headers; the 12 parameter types have no ctor/visitor/extractor evidence at all and several other types still lack a dedicated header. Single blocking fact: M2c cannot close until every one of the 62 types has a struct with [V]-confirmed fields; at least the 12 evidence-free parameter types cannot be typed yet.

## TOOL REQUESTS
None.
