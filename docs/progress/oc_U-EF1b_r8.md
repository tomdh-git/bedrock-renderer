## NEXT
DONE

# oc U-EF1b — VV pass order from builder 0x55f1450, per-pass in/out resources (checklist F1b)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis disassembly of .text). Builder range: 0x55f1450..0x563f594 (size 0x4e144) [V preflight].

## Status on entry

- docs/functions/vv_builder_pass_order_55f1450.md: ordered pass-name strings (210 refs, Shadow Cascades .. FullScreenOverlayObjects ..).
- docs/progress/oc_U-F1b.md + oc_U-F1b2.md: 50 pass-declaration call sites in 0x55f1450 targeting 9 helpers (sub_5667860 x4, sub_5684660 x1, sub_5689800 x18, sub_5693680 x7, sub_5694510 x2, sub_5695960 x1, sub_5696540 x1, sub_5697650 x1, sub_5698290 x15). Pass names mostly UNVERIFIED; in/out resources only visible as config-struct pointers.
- docs/progress/oc_U-EL6b.md (verify_oc 11/11): pass declaration fns copy a 28-byte descriptor struct opaquely [V]; nothing in 0x55f1450 or callees separates input from output resources statically.
- ORCHESTRATOR HINT (verified fact): per-pass in/out resources live in each pass's EXECUTE body, not its declaration. Use per-group execute-body table from M1e/6ha notes (docs/BGFX_MAP.md 6gz/6ha; oc_U-EM1e_r1/r2/r3 which has bloom-down, ScreenDraw 0xbc04dc0, ColorPostProcess with in/out resources).

## Execute-body mapping (from docs/BGFX_MAP.md 6gz/6ha and oc_U-EM1e_r1/r2/r3)

Per 6gz, VV pass-group builders (callee of 0x55f1450) and their execute bodies per 6ha:
- Pass object vtable slot 2: deferred lighting/shading (0xbc2c590/0xbc2cd20/0xbc2d550/0xbc2dd20), water (0xbc2eb50/0xbc2f4a0), voxel combine (0xbc0b240), ClusterLights (0xbc5bad0).
- ScreenDraw std::function: 0xbc04dc0 (writes view rect/mat4s into s_ctx views [0x12AE1748]+viewId*0x140, binds material 0xe86d7f0, submits via 0xbcc38e0).
- Generic draw-list task: 0x568cd90 (depth prepasses, DepthAndNormal, water surface buffer, forward PBR, RTX prep; also all Fancy Scene/HUD tasks).
- Indirect: RTX prep 0xbc080c0 -> 0xbcc4b90, RTX denoise 0xbcc4b90, FSR1 0xbcb7590/0xbcb7e70, voxel upload 0xbc0ac20.

EM1e per-pass in/out table (verbatim rows re-verified, verify_oc 404/404) covers: voxel (PopulateVolume), depth prepasses (ScenePrepass, DepthOnlyAlphaTest, GeometryPrepassAlphaTest), deferred (DoDeferredLighting, DirectionalLightingPass, DiscreteIndirectCombinedLightingPass), DepthAndNormal, DoWaterSurfaceBuffer, WaterExtinction, WaterSurface, forward PBR (ForwardPBRAlphaTest, ForwardPBRTransparent, ForceForwardPBROpaque), ColorPostProcess (ScreenDraw), NothingTask, LightClustering, VolumeScattering, MinMax, SSR (SSRColorBufferBlit), TAAUpscaling, LuminanceHistogram/HistogramBuild, CubemapToOffscreen, RTX prep + RTX denoise/raygen, FSR1, Fancy Scene/HUD tasks.

## In/out table — one row per pass name from 0x55f1450's ordered list that existing data covers

| name | rva or offset | size | verbatim `0xRVA  instr` | [V]/[I]/[?] |
|---|---|---|---|---|
| Shadow Cascades | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| SampleCascadedShadows | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| PopulateVolume | 0xbc0b27f | 2 | `0xbc0b27f  movzx eax,word ptr [rax+8]                     ; R *(a1+0x8)+0x8` | [V] |
| ScenePrepass | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| GeometryPrepassAlphaTest | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| DepthOnlyAlphaTest | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| WaterSurfaceStencil | 0xbc2f4e6 | 2 | `0xbc2f4e6  movzx eax,word ptr [rax+8]                     ; R *(a1+0x8)+0x8` | [V] |
| WaterDepthBufferBlit | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| Core/Screen/Blit | 0xbc04e11 | 8 | `0xbc04e11  movq xmm0,[r8+0x168]              ; R a2+0x168` | [V] |
| DebugDepthBufferCopy | 0xbc04e11 | 8 | `0xbc04e11  movq xmm0,[r8+0x168]              ; R a2+0x168` | [V] |
| BlitUncompressed | 0xbc04e11 | 8 | `0xbc04e11  movq xmm0,[r8+0x168]              ; R a2+0x168` | [V] |
| Sky (pre-water) | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| ForwardPBR - Sky (pre-water) | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| ForwardPBRTransparent | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| Clouds (pre-water) | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| ForwardPBR - Clouds (pre-water) | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| ForceForwardPBROpaque | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| ForwardPBROpaque | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| ForwardPBRAlphaTest | 0x568cdde | 8 | `0x568cdde  movq xmm0,[rbx+0xF8]                          ; R a1+0xF8` | [V] |
| SSRColorBufferBlit | 0xbc84b7c | 8 | `0xbc84b7c  mov rdx,0x46B26355E42496DA         ` | [V] |
| DebugWaterDepthBufferCopy | 0xbc04e11 | 8 | `0xbc04e11  movq xmm0,[r8+0x168]              ; R a2+0x168` | [V] |
| BlitFSRToBackBuffer | 0xbc04e11 | 8 | `0xbc04e11  movq xmm0,[r8+0x168]              ; R a2+0x168` | [V] |

Body→in/out summary for the covered rows (from EM1e per-pass table):
- generic task 0x568cd90 (Shadow Cascades, SampleCascadedShadows, ScenePrepass, GeometryPrepassAlphaTest, DepthOnlyAlphaTest, WaterDepthBufferBlit, Sky/Clouds pre-water, ForwardPBR*, ForceForwardPBROpaque): In = task rect +0xF8/+0xFC, mats +0x78/+0xB8/+0x10C/+0x14C, vec4 +0x18C, sort byte +0x108, dependency records +0x48; Out = view writes +0x10/+0x14/+0x20/+0x60/+0xA0/+0xE0/+0x120/+0x132 + draws [V from 0x568cd90 rows].
- voxel 0xbc0b240/0xbc0ac20 (PopulateVolume): In = pass rect +0x88, pass+0x98 byte, material arg fields, globals 0x12ADF6D0/0x128767C8; Out = view rect +0x10/+0x14, mat4 +0x20/+0x60/+0xA0/+0xE0, view+0x120, view+0x132; VoxelBuffer compute write [V].
- WaterSurface 0xbc2f4a0 (WaterSurfaceStencil): In = material +0x23C/+0x1A0, byte +0x294; Out = standard view writes [V].
- ScreenDraw 0xbc04dc0 (Core/Screen/Blit, DebugDepthBufferCopy, BlitUncompressed, DebugWaterDepthBufferCopy, BlitFSRToBackBuffer): In = drawstate rect +0x168/+0x16C, byte +0x178, viewId word, pass-name chain via sub_ebce5e0 on [rcx+0xDC57E0]; Out = pass view's framebuffer [V] in, [I] out target.
- SSR (SSRColorBufferBlit): In = param struct via sub_bc88560, pass slots 0x12AE18D8/1910/1948/1980; Out = RT/dispatch writes in guarded execute bodies [V] in, [I] out.

## Pass names in the ordered list WITHOUT existing-data coverage (no [V] row possible)

The following pass-name strings from docs/functions/vv_builder_pass_order_55f1450.md have no execute-body in/out data in oc_U-EM1e_r1/r2/r3:
- VolumetricsShadows (0x55fc1c9)
- RasterizedObjects (0x56104c0)
- TransparentDegamma (0x5610e82)
- [ClearStencil][ForwardPBR] / ForwardPBR stencil (0x5611ebd/0x5611ec8)
- ItemInHandObject / [ClearDepth][ItemInHandObject] (0x5625633/0x562563e)
- WaitOnUpscalingOutput (0x562d068)
- ForceRasterization / [ClearColor][ForceRasterization] (0x562e6fb/0x562e706)
- ForceRasterizedObjects (0x562e91b)
- RasterizedOpaque (0x562e96b)
- RasterizedAlphaTest (0x562eaf8)
- RasterizedTransparent (0x562ec85)
- FullScreenOverlayObjects (0x562ef35)
- FullScreenOverlayTransparent (0x562ef87, 0x562f100)
- ColorCorrectedUI / [ClearColorDepth][ColorCorrectedUI] (0x56331b8/0x56331c3)
- BlitColorCorrectedUIToScreen (0x5634379/0x5634384)
- ScreenSpaceWaterFrontFaceDepthAndNormal (0x563801f)
- ScreenSpaceWaterBackFaceDepthAndNormal (0x5638096)
- SkyAmbientSamples (0x56381c8)
- EntitiesInUI / [ClearDepth][EntitiesInUI] (0x563df0b/0x563df16)

Additionally, FSR1 (0x5632969, 0x563d536) is covered by EM1e as [V structure] (docs/functions/vv_lambda_bodies.md) but has no verbatim instruction rows available, so no [V] table row can be written for it.

The ordered list also contains uniform names (ViewportScale, DitherParams, SunDir, MoonDir, FogColor, ClusterDimensions, IBLParameters, MatTexture, FbIn, FbOut, Color0/1/2 and others) which are not pass names and have no execute bodies; they are not listed as passes.

## Verification of verbatim lines

All `0xRVA  instr` lines above were re-verified against the exe with rdis.exe:
- 0x568cdde: `movq xmm0,[rbx+0xF8]` [V]
- 0xbc0b27f: `movzx eax,word ptr [rax+8]` [V]
- 0xbc2f4e6: `movzx eax,word ptr [rax+8]` [V]
- 0xbc04e11: `movq xmm0,[r8+0x168]` [V]
- 0xbc84b7c: `mov rdx,0x46B26355E42496DA` [V]

## CLOSES?

NO — blocking fact: not every pass name in 0x55f1450's ordered list has a [V] table row. 22 distinct pass names have [V] rows (covered above), but 19 additional distinct pass names (VolumetricsShadows, RasterizedObjects, TransparentDegamma, ForwardPBR stencil, ItemInHandObject, WaitOnUpscalingOutput, ForceRasterization, ForceRasterizedObjects, RasterizedOpaque/AlphaTest/Transparent, FullScreenOverlayObjects/Transparent, ColorCorrectedUI, BlitColorCorrectedUIToScreen, ScreenSpaceWaterFront/BackFaceDepthAndNormal, SkyAmbientSamples, EntitiesInUI) plus FSR1 ([V structure] only, no verbatim rows) have no executable-body in/out row. Existing EM1e data does not cover these pass bodies, so no verbatim `0xRVA  instr` proof line can be supplied for them.

## TOOL REQUESTS

- rdis.exe | exe + RVA -> instruction listing | used to verify all verbatim `0xRVA  instr` lines.
- verify_oc.py | md -> mismatch/no-such-instr report | EM1e rows validated 404/404.

## NEXT
DONE
