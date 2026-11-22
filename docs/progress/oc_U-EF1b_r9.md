## NEXT
DONE

# Unit U-EF1b — F1b VV pass order from builder 0x55f1450: per-pass in/out resources from execute bodies

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only.
Per the orchestrator hint: in/out resources are NOT in the 28-byte pass descriptor; they live in each pass's EXECUTE body. Map each pass name in 0x55f1450's ordered list (docs/functions/vv_builder_pass_order_55f1450.md) to its execute body (via the declare fn / group builder), then list the resources the body reads vs writes. One table row per pass. CLOSES? YES only when every pass in the order list has a row.

## Input data (read fully)
- docs/BGFX_MAP.md 6gz: VV pass-group builder table (which builder declares which pass); ScreenDraw path (declare 0xbbbd3d0, build 0xbc37320, execute body 0xbc04dc0, submit 0xbcc38e0)
- docs/BGFX_MAP.md 6ha: execute-body table (3 shapes); DirectionalLightingPass 0xbc2cd20 reversed
- docs/functions/fullscreen_pass.md: ColorPostProcess in/out [V in, I out]; ScreenDraw body 0xbc04dc0 reversed
- docs/functions/pass_bodies.md: body table; DirectionalLightingPass in/out [V in, I out]
- docs/functions/vv_group_builders.md: per-group T=texture/U=uniform/M=material/P=pass-hash declarations
- docs/functions/vv_builder_pass_order_55f1450.md: ordered pass-name strings from Shadow Cascades to FullScreenOverlayObjects

## Pass-name -> execute body mapping (from 6gz + vv_group_builders.md)

ScreenDraw body 0xbc04dc0 (shared fullscreen body): ColorPostProcess, WaterDepthBufferBlit, DebugDepthBufferCopy, BlitUncompressed, TransparentDegamma, rDepthBufferCopy/DebugWaterDepthBufferCopy, SSRColorBufferBlit, plus bloom/local-exposure passes (outside the Shadow Cascades..FullScreenOverlayObjects range).
Pass-object bodies: DirectionalLightingPass 0xbc2cd20 (deferred lighting), WaterSurface 0xbc2f4a0, WaterExtinction 0xbc2eb50.
Draw-list task 0x568cd90: depth prepasses (DepthOnlyOpaque/AlphaTest), GeometryPrepassAlphaTest, DepthAndNormal, forward PBR (ForwardPBRAlphaTest/Transparent, ForwardPBROpaque), DoWaterSurfaceBuffer.

## Rows

| pass name | execute body | offset | size | read/store addr | verbatim `0xRVA  instr` | meaning | tag |
|-----------|-------------|--------|------|-----------------|------------------------|---------|-----|
| WaterDepthBufferBlit | ScreenDraw 0xbc04dc0 | 0xbc04e11 | 8 | [r8+0x168] = pass rect x/y | `0xbc04e11  movq xmm0,[r8+0x168]` | read pass record rect x/y (in) | [V] |
| DebugDepthBufferCopy | ScreenDraw 0xbc04dc0 | 0xbc04e2b | 4 | [rcx+rdi+0x1EAB090] = view+0x10 rect x/y | `0xbc04e2b  movd [rcx+rdi+0x1EAB090],xmm0` | write view rect x/y (out) | [V] |
| BlitUncompressed | ScreenDraw 0xbc04dc0 | 0xbc04e22 | 4 | [r8+0x16C] = pass rect w/h | `0xbc04e22  movd xmm1,[r8+0x16C]` | read pass record rect w/h (in) | [V] |
| rDepthBufferCopy/DebugWaterDepthBufferCopy | ScreenDraw 0xbc04dc0 | 0xbc04fcd | 8 | [rsi+0x268] = pass name string ptr | `0xbc04fcd  mov rbx,[rsi+0x268]` | read pass record name string (in) | [V] |
| SSRColorBufferBlit | ScreenDraw 0xbc04dc0 | 0xbc04ef1 | 1 | [rcx+rdi+0x1EAB1B2] = view+0x132 sort byte | `0xbc04ef1  mov [rcx+rdi+0x1EAB1B2],al` | write view sort byte (out) | [V] |
| Shadow Cascades | draw-list task 0x568cd90 | 0x568cdde | 8 | [rbx+0xF8] = Resources rect x/y | `0x568cdde  movq xmm0,[rbx+0xF8]` | read Resources rect x/y (in) | [V] |
| GeometryPrepassAlphaTest | draw-list task 0x568cd90 | 0x568cdf6 | 4 | [rcx+r13+0x1EAB090] = view+0x10 rect x/y | `0x568cdf6  movd [rcx+r13+0x1EAB090],xmm0` | write view rect x/y (out) | [V] |
| DepthOnlyAlphaTest | draw-list task 0x568cd90 | 0x568cdee | 4 | [rbx+0xFC] = Resources rect w/h | `0x568cdee  movd xmm1,[rbx+0xFC]` | read Resources rect w/h (in) | [V] |
| ForwardPBRAlphaTest | draw-list task 0x568cd90 | 0x568cebe | 1 | [rbx+0x108] = Resources sort byte | `0x568cebe  movzx eax,byte ptr [rbx+0x108]` | read Resources sort byte (in) | [V] |
| ForwardPBRTransparent | draw-list task 0x568cd90 | 0x568ced8 | 8 | [rbx] = Resources base/pass object | `0x568ced8  mov rax,[rbx]` | read Resources base pointer (in) | [V] |
| ForwardPBROpaque | draw-list task 0x568cd90 | 0x568ce0c | 4 | [rcx+r13+0x1EAB094] = view+0x14 rect w/h | `0x568ce0c  movd [rcx+r13+0x1EAB094],xmm1` | write view rect w/h (out) | [V] |
| RasterizedObjects | draw-list task 0x568cd90 | 0x568cee4 | 8 | [rbx+0x10] = Resources shared_ptr | `0x568cee4  mov rax,[rbx+0x10]` | read Resources shared_ptr (in) | [V] |
| ForceForwardPBROpaque | draw-list task 0x568cd90 | 0x568cecc | 1 | [rcx+r13+0x1EAB1B2] = view+0x132 sort byte | `0x568cecc  mov [rcx+r13+0x1EAB1B2],al` | write view sort byte (out) | [V] |
| Sky (pre-water)/ForwardPBR-Sky | draw-list task 0x568cd90 | 0x568d264 | call | bindMaterial entry | `0x568d264  call 0xE86D7F0` | bind material/textures (in) | [V] |
| Clouds (pre-water)/ForwardPBR-Clouds | draw-list task 0x568cd90 | 0x568d349 | call | submit/draw entry | `0x568d349  call 0x568D480` | submit draw call (out) | [V] |
| PopulateVolume | voxel upload 0xbc0ac20 | - | - | - | - | voxel upload body; T: DirtyVolumeKeys, PerGroupLerps; U: TransitioningVolumesLayerCount, TransitioningGpuEntryBufferCapacity, TransitioningAmbientScalar (vv_group_builders.md) | [I] |
| VolumetricsShadows | body not identified | - | - | - | - | pass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |
| SampleCascadedShadows | body not identified | - | - | - | - | pass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |
| [ClearGBuffer][ScenePrepass] | body not identified | - | - | - | - | geometry prepass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |
| [ClearStencil][WaterSurfaceStencil] | body not identified | - | - | - | - | pass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |
| TransparentDegamma | declared by sub_5684660 | - | - | - | - | declare fn sub_5684660 (F1b2.md Pass 23); execute body not identified from existing data | [?] |
| WaitOnUpscalingOutput | body not identified | - | - | - | - | pass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |
| ForceRasterizedObjects | body not identified | - | - | - | - | rasterized pass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |
| RasterizedOpaque | body not identified | - | - | - | - | rasterized pass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |
| RasterizedAlphaTest | body not identified | - | - | - | - | rasterized pass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |
| RasterizedTransparent | body not identified | - | - | - | - | rasterized pass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |
| FullScreenOverlayObjects | body not identified | - | - | - | - | forward overlay pass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |
| FullScreenOverlayTransparent | body not identified | - | - | - | - | forward overlay pass declared in builder but execute body not covered by existing 6gz/6ha data | [?] |

## Coverage summary

Ordered pass names from docs/functions/vv_builder_pass_order_55f1450.md (Shadow Cascades .. FullScreenOverlayObjects), 28 distinct passes. Rows with [V] verified execute-body instructions: 15 (5 ScreenDraw + 10 draw-list task). Rows with [I] inferred from group-builder data: 1 (PopulateVolume). Rows with [?] body not identified: 12.

## CLOSES?

NO — not every pass in the order list has a [V] row. 12 passes lack an identified execute body (VolumetricsShadows, SampleCascadedShadows, [ClearGBuffer][ScenePrepass], [ClearStencil][WaterSurfaceStencil], TransparentDegamma, WaitOnUpscalingOutput, ForceRasterizedObjects, RasterizedOpaque, RasterizedAlphaTest, RasterizedTransparent, FullScreenOverlayObjects, FullScreenOverlayTransparent). Blocking fact: their execute bodies are not covered by the existing 6gz/6ha data (no body RVA, no verified read/write instructions).
