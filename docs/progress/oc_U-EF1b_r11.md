## NEXT
DONE

# oc U-EF1b — VV pass in/out resources from execute bodies (checklist F1b)

Source: Minecraft.Windows.exe 1.26.62.01; RVAs relative to image base. Static analysis only — exe passed to rdis.exe as an argument, never launched.
Basis (read in full; not re-derived): docs/BGFX_MAP.md sections 6gz/6ha (checked facts [V]); docs/progress/oc_U-EM1e_r1.md (404 rows, verify_oc claims=404 match=404 mismatch=0 no-such-instr=0); docs/functions/vv_builder_pass_order_55f1450.md + docs/progress/oc_U-F1b2.md (builder 0x55f1450 ordered call list: 50 pass-declaration call sites, 9 helper callees).

Method (orchestrator directive; supersedes the stale "28-byte pass descriptor" line): pass in/out resources are NOT in the 28-byte pass descriptor (proven opaque, 5 runs). They live in each pass's EXECUTE body:
 - pass-object vtable slot 2 bodies: DoDeferredLighting 0xbc2c590, DirectionalLightingPass 0xbc2cd20, DoDeferredShading 0xbc2d550/0xbc2dd20, WaterExtinction 0xbc2eb50, WaterSurface 0xbc2f4a0, VoxelCombine 0xbc0b240, ClusterLights 0xbc5bad0 — [V rows below]
 - ScreenDraw shared std::function body 0xbc04dc0 — ColorPostProcess fullscreen passes; SSR stubs 0xbc84b7c/bd0/c24/c78 register execute bodies 0xbc88320/3B0/440/4D0 that all run 0xbc04dc0 via 0xbc88560 — [V rows below]
 - generic draw-list task 0x568cd90 — depth prepasses, DepthAndNormal, DoWaterSurfaceBuffer, forward PBR, RTX prep — [V per oc_U-EM1e_r2; body not re-quoted here]

ColorPostProcess in/out convention [I per oc_U-EM1e summary]: in = ColorTexture at in+8 plus ColorGrading_Misc uniform; out = the pass view's framebuffer. ScreenDraw writes the s_ctx views and emits the "ScreenDraw:<pass name>" marker (pass-record name std::string at +0x268 per 6gz).

## Execute-body resource map (reads vs writes; one row per distinct offset, all sites listed)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
| s_ctx global [0x12AE1748] | 8 | ScreenDraw 0xbc04dc0 prologue | R | `0xbc04e03  mov rcx,[0x12AE1748]              ; [data_12ae1748]` | s_ctx global load (view base) | [V] |
| *(view record+8)+8 (viewId) | 2 | ScreenDraw 0xbc04dc0 prologue | R | `0xbc04dff  movzx eax,word ptr [rax+8]       ; R *(a1+0x8)+0x8` | viewId word read *(view record+8)+8 | [V] |
| drawstate+0x168 | 8 | ScreenDraw 0xbc04dc0 prologue | R | `0xbc04e11  movq xmm0,[r8+0x168]              ; R a2+0x168` | drawstate rect x/y load (movq 8 bytes) | [V] |
| drawstate+0x16C | 4 | ScreenDraw 0xbc04dc0 prologue | R | `0xbc04e22  movd xmm1,[r8+0x16C]              ; R a2+0x16C` | drawstate rect z/w load (movd 4 bytes) | [V] |
| view+0x10 | 4 | W: ScreenDraw 0xbc04e2b, DoDeferredLighting 0xbc2c600, DirectionalLightingPass 0xbc2cd90, DoDeferredShading 0xbc2d5c0 | `0xbc2c600  movd [rcx+rsi+0x1EAB090],xmm0                 ` | view rect dword store view+0x10 (s_ctx+0x1EAB090+viewId*0x140); same movd pattern in all four bodies | [V] |
| view+0x14 | 4 | W: ScreenDraw 0xbc04e40, DoDeferredLighting 0xbc2c615, DirectionalLightingPass 0xbc2cda5, DoDeferredShading 0xbc2d5d5 | `0xbc2c615  movd [rcx+rsi+0x1EAB094],xmm1                 ` | view rect dword store view+0x14; same movd pattern in all four bodies | [V] |
| view+0x20 mat4 slot | - | ScreenDraw 0xbc04dc0 prologue | W | `0xbc04e76  call 0xEBCE390                   ; -> sub_ebce390` | 64-byte memcpy call (r8d=0x40 at 0xbc04e70) into view+0x20; src rdx=a2+0xE8; memcpy pattern [I] | [V] |
| view+0x120 | - | ScreenDraw 0xbc04dc0 prologue | W | `0xbc04ede  call 0xEBCE390                   ; -> sub_ebce390` | 16-byte memcpy call (r8d=0x10 at 0xbc04ed1) into view+0x120; src rsi+0x1FC; memcpy pattern [I] | [V] |
| drawstate+0x178 | 1 | ScreenDraw 0xbc04dc0 prologue | R | `0xbc04ee3  movzx eax,byte ptr [rsi+0x178]   ; R a2+0x178` | drawstate byte load +0x178 (sort mode) | [V] |
| view+0x132 | 1 | ScreenDraw 0xbc04dc0 prologue | W | `0xbc04ef1  mov [rcx+rdi+0x1EAB1B2],al        ` | view+0x132 u8 store (sort mode) | [V] |
| "ScreenDraw:" string data [0xF7D08BE] | 8 | ScreenDraw 0xbc04dc0 strings | R | `0xbc050af  mov rax,[0xF7D08BE]               ; [data_f7d08be] "ScreenDraw:"` | "ScreenDraw:" qword load (debug marker name) | [V] |
| pass+0x88 | 8 | R: DoDeferredLighting 0xbc2c5e8, DirectionalLightingPass 0xbc2cd78, DoDeferredShading 0xbc2d5a8, WaterExtinction 0xbc2eba8, WaterSurface 0xbc2f4f8, VoxelCombine 0xbc0b291 ([rsi]), ClusterLights 0xbc5bb34 ([rdi]) | `0xbc2c5e8  movq xmm0,[rbx+0x88]                          ; R a0+0x88` | pass rect x/y load from pass+0x88; identical movq pattern in all seven bodies (reg varies) | [V] |
| pass+0x98 | 1 | R: DoDeferredLighting 0xbc2c6b5, DoDeferredShading 0xbc2d675, WaterExtinction 0xbc2ec75, WaterSurface 0xbc2f5c5, VoxelCombine 0xbc0b35e ([rsi]), ClusterLights 0xbc5bc04 ([rdi]) | `0xbc2c6b5  movzx eax,byte ptr [rbx+0x98]                 ; R a0+0x98` | pass+0x98 byte load (sort mode); identical movzx pattern in all six bodies | [V] |
| pass object+0x0 | 8 | R: DoDeferredLighting 0xbc2c6ca, WaterExtinction 0xbc2ec8a, WaterSurface 0xbc2f5da | `0xbc2c6ca  mov rax,[rdi]                                 ; R a2+0x0` | pass object qword load +0x0 | [V] |
| pass object+0x8 | 8 | R: DoDeferredLighting 0xbc2c6eb | `0xbc2c6eb  mov rcx,[rdi+8]                               ` | pass object qword load +8 | [V] |
| pass object+0x10+8 | 4 | W: DoDeferredLighting 0xbc2c6df, DoDeferredShading 0xbc2d69f, WaterExtinction 0xbc2ec9f, WaterSurface 0xbc2f5ef | `0xbc2c6df  lock inc dword ptr [rax+8]                    ; W *(a2+0x10)+0x8` | refcount dword inc on pass object+0x10+8; same lock inc pattern in all four bodies | [V] |
| material+0x23C | 16 | DirectionalLightingPass 0xbc2cd20 | R | `0xbc2d080  movups xmm0,[rdi+0x23C]                        ` | material vec4 load +0x23C (movups = 16 bytes) | [V] |
| material+0x250 | 1 | DirectionalLightingPass 0xbc2cd20 | R | `0xbc2d08b  movzx eax,byte ptr [rdi+0x250]                 ` | material byte load +0x250 | [V] |
| material+0x254 | 16 | DirectionalLightingPass 0xbc2cd20 | R | `0xbc2d095  movups xmm0,[rdi+0x254]                        ` | material vec4 load +0x254 (movups = 16 bytes) | [V] |
| material+0x264 | 16 | DirectionalLightingPass 0xbc2cd20 | R | `0xbc2d0a0  movdqu xmm0,[rdi+0x264]                        ` | material load +0x264 (movdqu = 16 bytes) | [V] |
| material+0x283 | 16 | DirectionalLightingPass 0xbc2cd20 | R | `0xbc2d0b0  movups xmm2,[rdi+0x283]                        ` | material vec4 load +0x283 (movups = 16 bytes) | [V] |
| material+0x294 | 1 | WaterSurface 0xbc2f4a0 | R | `0xbc2f830  cmp byte ptr [rdi+0x294],0                     ` | material byte test +0x294 (cmovne string select follows) | [V] |
| material+0x0 | 16 | VoxelCombine 0xbc0b240 | R | `0xbc0b427  movdqu xmm0,[rax]                             ; R *(a2+0x0)+0x0` | 16-byte load from material+0x0 (movdqu = 16 bytes) | [V] |
| material+0x8 refcount inc | 4 | VoxelCombine 0xbc0b240 | W | `0xbc0b41c  lock inc dword ptr [rcx+8]                    ; W *(*(a2+0x0)+0x8)+0x8` | refcount dword inc (a2=r15=material arg) | [V] |
| material+0x8 refcount dec | 4 | VoxelCombine 0xbc0b240 | W | `0xbc0b438  lock dec dword ptr [r15+8]                     ` | refcount dword dec on material+8 | [V] |
| *(rsi+0x38)+8 refcount inc | 4 | ClusterLights 0xbc5bad0 | W | `0xbc5bdb0  lock inc dword ptr [rcx+8]                     ` | refcount dword inc at *(rsi+0x38)+8+8 | [V] |
| *(rsi+0x38)+0 | 16 | ClusterLights 0xbc5bad0 | R | `0xbc5bdbb  movdqu xmm0,[rax]                             ` | 16-byte load from [rsi+0x38]+0 (movdqu = 16 bytes) | [V] |

## Pass -> execute body mapping (per-group execute-body table from BGFX_MAP 6gz/6ha)

| VV pass group (builder) | passes in group | declare fn -> execute body | rows above | status |
| Voxel (0xbb3e2b0) | UploadDirtyVolumeKeys, UploadPerGroupLerps, CombineVoxelLighting | builder 0xbb3e2b0 -> VoxelCombine 0xbc0b240 (voxel upload 0xbc0ac20 per 6hb) | 41-45 | [V] |
| Depth (0xbb4c2e0) | DepthOnlyOpaque, DepthOnlyAlphaTest | builder 0xbb4c2e0 -> generic draw-list task 0x568cd90 (6ha) | generic draw-list task view writes (0x568cd90 body; not re-quoted here) | [V] |
| Deferred lighting (0xbb6b350) | CausticsMultiplierPass, DoDeferredLighting, DirectionalLightingPass, DiscreteIndirectCombinedLightingPass | builder 0xbb6b350 -> DoDeferredLighting 0xbc2c590 / DirectionalLightingPass 0xbc2cd20; CausticsMultiplierPass/DiscreteIndirectCombinedLightingPass [I] | 12-26 | [V] |
| 0xbb74040 | SurfaceRadianceUpscalePass, DoDeferredShading | -> DoDeferredShading 0xbc2d550/0xbc2dd20 | 27-31 | [V] |
| DepthAndNormal (0xbb78240) | DepthAndNormal | -> 0x568cd90 (6ha) | generic draw-list task view writes (not re-quoted here) | [V] |
| DoWaterSurfaceBuffer (0xbb7b210) | DoWaterSurfaceBuffer | -> 0x568cd90 (6ha/r2) | generic draw-list task view writes (not re-quoted here) | [V] |
| WaterExtinction (0xbb7efb0) | WaterExtinction | -> 0xbc2eb50 | 32-35 | [V] |
| WaterSurface (0xbb81880) | WaterSurface | -> 0xbc2f4a0 | 36-40 | [V] |
| Forward (0xbb84ee0) | ForwardPBRAlphaTest, ForwardPBRTransparent, HighlightTextureEdge | -> 0x568cd90 (6ha) | generic draw-list task view writes (not re-quoted here) | [V] |
| DoIndirectSpecularUpscale (0xbb8eb70) | DoIndirectSpecularUpscale | no body located statically | - | [I] |
| ColorPostProcess (0xbbbcb20) | fullscreen blit passes (Core/Screen/Blit family) | -> ScreenDraw 0xbc04dc0 | 1-11 | [V] |
| NothingTask (0xbbbfc50) | NothingTask | no body located statically | - | [I] |
| LightClustering (0xbc57460) | LightClustering | -> ClusterLights 0xbc5bad0 | 46-49 | [V] |
| VolumeScattering (0xbc7c580) | VolumeScattering | no body located statically | - | [I] |
| MinMax (0xbc7f6e0) | MinMax init/downsample | no body located statically | - | [I] |
| SSR (0xbc82ad0) | SSRRayMarch, SSRRayMarchHZB, SSRFillGaps, SSRGetReflectedColor | stubs 0xbc84b7c/bd0/c24/c78 register bodies via 0xbc88560 -> ScreenDraw 0xbc04dc0 | 1-11 | [V] |
| TAAUpscaling (0xbc8a380) | TAA upscaling | -> TAAU 0xbc8da0c (material+0x2F8/+0x300 loads, submitPass 0xBCC38E0; rows in oc_U-EM1e_r1) | - | [V] |
| LuminanceHistogram (0xbc8eb90) | LuminanceHistogram/HistogramBuild | no body located statically | - | [I] |
| bloom down (0xbc98310) | DFDownSample, ThresholdedDownSample | no body located statically | - | [I] |
| bloom up (0xbc9ada0) | DFUpSample, BloomBlend | no body located statically | - | [I] |
| local exposure (0xbc9d7a0) | Clear/Build/FilterBilateralGrid, ApplyLocalExposure | no body located statically | - | [I] |
| CubemapToOffscreen (0xbcd77b0) | CubemapToOffscreen | no body located statically | - | [I] |
| Convolve (0xbcdba70) | Convolve | no body located statically | - | [I] |
| RTX prep (0xbbe2d50, indirect) | PreBlasSkinDispatch, PrepareTLAS, AlphaTestCracks | -> 0x568cd90 (6ha) | generic draw-list task view writes (not re-quoted here) | [V] |
| RTX denoise/raygen (0xbcc4b90, indirect) | 43 denoise/raygen passes | body 0xbcc4b90 from RTX prep 0xbc080c0; encoder writes; UAV outputs not read | - | [I] |
| FSR1 (0xbcb3cf0, indirect) | FSR1 | body 0xbcb3cf0 not read | - | [I] |

Notes:
 - The 50 declaration call sites of builder 0x55f1450 (docs/progress/oc_U-F1b2.md) call helpers sub_5689800 x18, sub_5698290 x15, sub_5667860 x4, sub_5693680 x7, sub_5694510 x2, sub_5695960 x1, sub_5696540 x1, sub_5697650 x1, sub_5684660 x1. No helper->execute-body mapping is documented statically, so per-site pass-name -> body resolution is [?] pending reversal of each helper; the group-level table above is from BGFX_MAP 6gz/6ha [V] + oc_U-EM1e_r1 [V rows].
 - Every verbatim `0xRVA  instr` line above is copied from docs/progress/oc_U-EM1e_r1.md and re-verified against the exe by verify_oc (404 claims, 0 mismatch on that file; this file re-claims the same instructions).

## Verification
 - `python tools/sigs/verify_oc.py docs/progress/oc_U-EF1b.md` — run as part of `python tools/delegate.py check docs/progress/oc_U-EF1b.md`; expect claims>=0 mismatch=0 no-such-instr=0.
 - `python tools/delegate.py check docs/progress/oc_U-EF1b.md` must exit 0; then the line after `## NEXT` is set to DONE.

## CLOSES?
CLOSES? NO — blocking fact: 12 pass groups (DoIndirectSpecularUpscale 0xbb8eb70, NothingTask 0xbbbfc50, VolumeScattering 0xbc7c580, MinMax 0xbc7f6e0, LuminanceHistogram 0xbc8eb90, bloom down 0xbc98310, bloom up 0xbc9ada0, local exposure 0xbc9d7a0, CubemapToOffscreen 0xbcd77b0, Convolve 0xbcdba70, FSR1 0xbcb3cf0, RTX denoise/raygen 0xbcc4b90 UAV outputs) have no verbatim-read execute body, so their in/out resources are only [I] inferred from builder/pass name, not proven by [V] rows; not every pass in the 0x55f1450 order list has a proven row.

## TOOL REQUESTS
- None — all data drawn from existing verified notes (oc_U-EM1e_r1.md, BGFX_MAP.md 6gz/6ha, vv_builder_pass_order_55f1450.md, oc_U-F1b2.md).
