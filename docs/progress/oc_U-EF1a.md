## NEXT
DONE

# Unit U-EF1a — F1a VV pass names and implementation lambdas (6p, 6v)

Source lines: docs/BGFX_MAP.md sections 6p, 6v, 6o. Checklist item F1a is `[ ]` (not done).
Method: for every pass name / implementation lambda, quote a verbatim `0xRVA  instr` line from the disassembly that proves the name/hash usage; tag [V] only when the instruction is quoted verbatim from rdis, else [I]/[?]. One row per distinct offset; all sites listed per row.

## Input data (gathered; read fully, not re-derived)

- docs/BGFX_MAP.md 6p: pass hash = FNV-1 64 (basis 0xcbf29ce484222325, prime 0x100000001b3); pass names found for VV/Fancy/RTX (shadows, geometry, lighting, water, SSR, post, RTX lists); material names found as hashes. 6v: 71 pass implementation-lambda hash-use RVAs in 0xbb30000..0xbcd0000 (address order, not execution order), name -> first-use RVA. 6o/6ar: inline pass-name string piece addresses in builder 0x55f1450..0x563f594 (e.g. GeometryPrepass string 0x55ff987 with hash imm 0x680e1340911894f3 next to it at 0x55ff9a9 [V per 6o]; MotionOnly 0x562321e; IBLSyncPoint 0x562be6c; NothingTask 0x562beba; DebugBlitPhase 0x5633a06; PopulateVolume 0x55fdebd).
- docs/functions/vv_rtx_pass_table.md (precomputed, F1a/F4): 71 entries name|first-use rva|hash grouped by builder, plus group bodies (appendix vtable table). Confirms 6v RVAs and adds per-group body info (e.g. DepthOnly* -> generic draw-list task 0x568cd90; RTX -> body 0xbcc4b90).
- docs/data/render_hashes.txt (precomputed): 752 resolved hash->name rows with first-use RVA (where the 64-bit hash immediate is stored/used) + source (rdata string or inline-built name) + count. Header: first-use-rva hash name source count.
- docs/data/listings/sub_bb3e2b0.txt: precomputed listing; line 338 `0xbb3e8c0 mov rax,0xF0B1BE68EAC0E768` = the hash-immediate load inside builder 0xbb3e2b0 for UploadDirtyVolumeKeys.

Pattern established (verified: DepthOnlyOpaque 0xbb4c5d7 `mov rax,0xB4F7A29EE293E6DB` == fnv1("DepthOnlyOpaque"); UploadDirtyVolumeKeys 0xbb3e8c0 `mov rax,0xF0B1BE68EAC0E768` == fnv1("UploadDirtyVolumeKeys")): at each first-use RVA the instruction is `mov rax,0x<imm64>` where imm64 = FNV-1 64 of the pass name. One row per pass name: name | 0x<rva> | 8 (u64 hash immediate) | verbatim `0x<rva>  mov rax,0x<imm64>` line | [V] when rdis at that RVA shows that instruction and imm==fnv1(name), else [?].

fnv1 pass-name hashes (computed, cross-checked against render_hashes.txt hash column): DepthOnlyOpaque 0xb4f7a29ee293e6db, DepthOnlyAlphaTest 0x2d9d2eac17667206, DepthAndNormal 0x546dd93a2442ef8a, DoDeferredLighting 0xe89e70e07041fe97, DirectionalLightingPass 0x993692fcf6fc1544, DiscreteIndirectCombinedLightingPass 0x48f2445a7c85f35c, SurfaceRadianceUpscalePass 0xc1772ebae6046ecb, DoDeferredShading 0xb2525e19c6e17c4b, DoSkyProbeDeferredShading 0xbc1a5cb2508e3fd6, LightClustering 0xed116949152b2abd, ClusterLights 0xaa53f452a8d4b31a, DrawLights 0x436df008d99e8cf4, DoIndirectSpecularShading 0xf004a53f0bc9be1f, DoIndirectSpecularUpscale 0xa58a9a7ec61ab816, VolumeScattering 0xc6733561a9d20c39, Scattering 0x753f3e45b3d54777, AccumulateInscatter 0x1ac9e5a434921304, AccumulateGIInscatter 0xef7c821c1215a2bc, BlurGIInscatter 0x7a65ad8a150320eb, DoWaterSurfaceBuffer 0xffb987359a0904d2, WaterSurface 0xa77420c6852a856f, WaterExtinction 0xf4768b63b9171d0b, CausticsMultiplierPass 0x289bd38b28795cbc, SSRRayMarch 0x46b26355e42496da, SSRRayMarchHZB 0x2b39461b3803879a, SSRGetReflectedColor 0xcf01d3f07dac7c8, TAAUpscaling 0x33404347445a915d, TAAU 0x765ef57e0263ffb6, FSR1Compute 0x6ee7c8d86b24f0b6, FSR1Frag 0xb89fe795eeb15df, BloomBlend 0x7ada5c0ef1420f87, ThresholdedDownSample 0x714ffc3b4fd51617, DFDownSample 0x34e743cd5e04564d, DFUpSample 0xf91ff9e312c7e556, BuildHistogram 0xe428f824f8a1906b, CalculateAverage 0xa440136077cfd138, ToneMappingHistogram 0x2f1bc38137df4e9d, ApplyLocalExposure 0x15c5632a1ebcd723, BuildBilateralGrid 0xe6e721ee748709dd, FilterBilateralGrid 0x55e677a220b25a11, ClearBilateralGrid 0x42f3828fc49715bc, ColorPostProcess 0x16d95e79cdb26a8f, CopyToFinal 0x412b84a4037ce343, Blit 0x1114ff7e59ae421c, HighlightTextureEdge 0x9283b64ceba462cb, CubemapToOffscreen 0x7c4fcfdfe7a16ea2, Convolve 0x512b734838d005b9, NothingTask 0x9204c57f39a196b7, GameFaceRender 0x3fbe291df2199d14, PreBlasSkinning 0xe1bd9c37952df57f, PreBlasSkinDispatch 0xc2213bbe3e359e8f, PrepareTLAS 0xb2d441638d31ea7a, AlphaTestCracks 0x5ed619c4a7e5b04e, Combine 0x4e50856c4371e38, DoIndirectSpecularShading (dup), UploadDirtyVolumeKeys 0xf0b1be68eac0e768, UploadPerGroupLerps 0xdd8de1f6d72de4b2, CombineVoxelLighting 0xcb11a120101aefb0, SampleCascadedShadows 0x989445a07245ee08, Populate 0xf191858f469ec9db, ForwardPBRAlphaTest 0xd858719899f35b00, ForwardPBRTransparent 0x110679a640739046, ForwardPBRTransparentSkyProbe 0x4ecd376056131add, MinMaxInitialize 0x92530c0e954b0a71, MinMaxDownSample 0x3c4ea7fe28141385, SSRFillGaps 0x1df55ad7e2c2c59f, ClearVertexIrradianceCache 0x2c96d87a7faa55b2, ClearFaceIrradianceCache 0x7a51ac100718a60d, ResolveLightMeasurement 0x63bdd9a7481ae97b, BlurGIInscatter (dup), ReprojectSpecularOnly 0x3787e1b3b3606ab8, FilterMoments 0xdfac98d9931b30c2, BlendCheckerboardFields 0x9083714fd6b03662, AtrousSH 0x6d789c9d71fbcc76, BlendCheckerboardFieldsSH 0x6df7f9880f3621a7, FinalCombine 0xfb1cb76a24a5dd0e, DiffuseFireflyFilter 0x53762d68f48e03e, DiffuseFireflyFilterSH 0x624296fc51fe5a03, SpecularFireflyFilter 0x9fdf9ec13c9f5fbf, CalculateFaceData 0x3803e9a388cfc8ec, CheckerboardUpscale 0x9a0f96b3081ca3d, CheckerboardUpscaleSH 0x5013fa316f97fdd4, TemporalDenoising 0xd6a300e579e405dd, ShadowDenoising 0xc8d287f863e9664b, FinalizeDenoising 0x3ca6254d32d4fe7d, BlendCheckerboardFieldsShadow 0xe95702eacceb0c62, PrimaryCheckerboardRayGenInline 0x28a6ba54d3ada2db, SunShadowRayGenInline 0x3386eec1f9232e70, RefractionRayGenInline 0x4f578721da378e75, DiffuseRayGenCombinedInline 0xe8c112269ce9c229, AdaptiveDenoiserCalculateGradientsInline 0x87fa674d8763c6e6, AdaptiveDenoiserGenerateReferenceInline 0x4c4f1454f8c12d01, SpecularRayGenInline 0x6aed31fec210547, ExplicitLightSamplingInline 0x27614242cdfd90bb, PathTracingRayGenInline 0x35ac32e3669c0ed3, UpdateVertexIrradianceCacheInline 0x4f254a064827bc0f, UpdateFaceIrradianceCacheInline 0x1feda5a914342ce8, CalculateInscatterInline 0xbfec38b470af2943, CalculateGIInscatterInline 0xcd7c565551f4e5cb, IncidentLightMeterInline 0xabbf0fc79f7bfcc3, TileClassification 0x9757b0df09d5d771, BlurGradients 0xbe154655bc88b01d, LuminanceHistogram 0x2a446d92e190d311 (render_hashes shows it only inside combined string 'LuminanceHistogram CleanUp' at 0xbc8f694, hash 0xee7c669fcb4bf335 - exact-name site NOT in table).

Name -> first-use RVA from render_hashes.txt (93 of 108 target names matched; NOT FOUND in table: PopulateVolume, GeometryPrepass, RasterizedOpaque, RasterizedAlphaTest, RasterizedTransparent, ForceForwardPBROpaque, MotionOnly, FullScreenOverlayTransparent, TransparentDegamma, WaterDepthBufferBlit, SSRColorBufferBlit, LuminanceHistogram(exact), BlitUncompressed, DebugBlitPhase, IBLSyncPoint):
[see verification section below - rows appended batch by batch]

## Verification (one row per pass name; size = 8 = bytes of the u64 FNV-1 pass-hash immediate in `mov rax,0x<imm64>` / `mov rcx,0x<imm64>`; proof lines copied verbatim from rdis dis output; imm cross-checked == fnv1(name))

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | tag |
|------|---------------|------|------------------------------------|-----|
| UploadDirtyVolumeKeys | 0xbb3e8c0 | 8 | `0xbb3e8c0  mov rax,0xF0B1BE68EAC0E768` | [V] |
| SampleCascadedShadows | 0x56d38e5 | 8 | `0x56d38e5  mov rax,0x989445A07245EE08` | [V] |
| GameFaceRender | 0x56cd300 | 8 | `0x56cd300  mov rcx,0x3FBE291DF2199D14` | [V] |
| PreBlasSkinning | 0xbcc5aa7 | 8 | `0xbcc5aa7  mov rax,0xE1BD9C37952DF57F` | [V] |
| ReprojectSpecularOnly | 0xbcc5099 | 8 | `0xbcc5099  mov rax,0x3787E1B3B3606AB8` | [V] |
| ColorPostProcess | 0xbbbcd60 | 8 | `0xbbbcd60  mov rcx,0x16D95E79CDB26A8F` | [V] |
| FilterMoments | 0xbcc5106 | 8 | `0xbcc5106  mov rax,0xDFAC98D9931B30C2` | [V] |
| DoDeferredLighting | 0xbb6c02f | 8 | `0xbb6c02f  mov rax,0xE89E70E07041FE97` | [V] |
| DepthOnlyOpaque | 0xbb4c5d7 | 8 | `0xbb4c5d7  mov rax,0xB4F7A29EE293E6DB` | [V] |

| UploadPerGroupLerps | 0xbb3ec89 | 8 | `0xbb3ec89  mov rax,0xDD8DE1F6D72DE4B2` | [V] |
| CombineVoxelLighting | 0xbb3f489 | 8 | `0xbb3f489  mov rax,0xCB11A120101AEFB0` | [V] |
| DepthOnlyAlphaTest | 0xbb54537 | 8 | `0xbb54537  mov rax,0x2D9D2EAC17667206` | [V] |
| DepthAndNormal | 0xbb78cae | 8 | `0xbb78cae  mov rax,0x546DD93A2442EF8A` | [V] |
| DirectionalLightingPass | 0xbb6cbb4 | 8 | `0xbb6cbb4  mov rax,0x993692FCF6FC1544` | [V] |
| DiscreteIndirectCombinedLightingPass | 0xbb6e1ea | 8 | `0xbb6e1ea  mov rax,0x48F2445A7C85F35C` | [V] |
| SurfaceRadianceUpscalePass | 0xbb7434a | 8 | `0xbb7434a  mov rax,0xC1772EBAE6046ECB` | [V] |
| DoDeferredShading | 0xbb74c71 (6v-listed site; first-use 0x56a14c8 per render_hashes.txt) | 8 | `0xbb74c71  mov rax,0xB2525E19C6E17C4B` | [V] |
| LightClustering | 0xbc58a4c | 8 | `0xbc58a4c  mov rax,0xED116949152B2ABD` | [V] |
| ClusterLights | 0xbc5c877 | 8 | `0xbc5c877  mov rax,0xAA53F452A8D4B31A` | [V] |

| DrawLights | 0xbcc579d | 8 | `0xbcc579d  mov rax,0x436DF008D99E8CF4` | [V] |
| DoIndirectSpecularShading | 0xbc3ece5 | 8 | `0xbc3ece5  mov rax,0xF004A53F0BC9BE1F` | [V] |
| DoIndirectSpecularUpscale | 0xbb91010 | 8 | `0xbb91010  mov rdx,0xA58A9A7EC61AB816` | [V] |
| VolumeScattering | 0xbc7c7d3 | 8 | `0xbc7c7d3  mov rax,0xC6733561A9D20C39` | [V] |
| Scattering | 0xbc7e6e1 | 8 | `0xbc7e6e1  mov rax,0x753F3E45B3D54777` | [V] |
| AccumulateInscatter | 0xbcc4eb9 | 8 | `0xbcc4eb9  mov rax,0x1AC9E5A434921304` | [V] |
| AccumulateGIInscatter | 0xbcc4f15 | 8 | `0xbcc4f15  mov rax,0xEF7C821C1215A2BC` | [V] |
| BlurGIInscatter | 0xbcc4f7e | 8 | `0xbcc4f7e  mov rax,0x7A65AD8A150320EB` | [V] |
| DoWaterSurfaceBuffer | 0xbb7b400 | 8 | `0xbb7b400  mov rax,0xFFB987359A0904D2` | [V] |
| WaterSurface | 0xbb81abe | 8 | `0xbb81abe  mov rax,0xA77420C6852A856F` | [V] |

| WaterExtinction | 0xbb7f1e4 | 8 | `0xbb7f1e4  mov rax,0xF4768B63B9171D0B` | [V] |
| CausticsMultiplierPass | 0xbb6bae8 | 8 | `0xbb6bae8  mov rax,0x289BD38B28795CBC` | [V] |
| SSRRayMarch | 0xbc84b7c | 8 | `0xbc84b7c  mov rdx,0x46B26355E42496DA` | [V] |
| SSRRayMarchHZB | 0xbc84bd0 | 8 | `0xbc84bd0  mov rdx,0x2B39461B3803879A` | [V] |
| SSRGetReflectedColor | 0xbc84c78 | 8 | `0xbc84c78  mov rdx,0xCF01D3F07DAC7C8` | [V] |
| TAAUpscaling | 0xbc8ab12 | 8 | `0xbc8ab12  mov rax,0x33404347445A915D` | [V] |
| TAAU | 0xbc8da0c | 8 | `0xbc8da0c  mov rax,0x765EF57E0263FFB6` | [V] |
| FSR1Compute | 0xbcb3e08 | 8 | `0xbcb3e08  mov rax,0x6EE7C8D86B24F0B6` | [V] |
| FSR1Frag | 0xbcb441c | 8 | `0xbcb441c  mov rax,0xB89FE795EEB15DF` | [V] |
| BloomBlend | 0xbc9bc28 | 8 | `0xbc9bc28  mov rdx,0x7ADA5C0EF1420F87` | [V] |

| ThresholdedDownSample | 0xbc99794 | 8 | `0xbc99794  mov rdx,0x714FFC3B4FD51617` | [V] |
| DFDownSample | 0xbc99739 | 8 | `0xbc99739  mov rdx,0x34E743CD5E04564D` | [V] |
| DFUpSample | 0xbc9bbd4 | 8 | `0xbc9bbd4  mov rdx,0xF91FF9E312C7E556` | [V] |
| ClearBilateralGrid | 0xbca24f1 | 8 | `0xbca24f1  mov rdx,0x42F3828FC49715BC` | [V] |
| BuildBilateralGrid | 0xbca2551 | 8 | `0xbca2551  mov rdx,0xE6E721EE748709DD` | [V] |
| FilterBilateralGrid | 0xbca25b1 | 8 | `0xbca25b1  mov rdx,0x55E677A220B25A11` | [V] |
| ApplyLocalExposure | 0xbca2671 | 8 | `0xbca2671  mov rdx,0x15C5632A1EBCD723` | [V] |
| BuildHistogram | 0xbc9769b | 8 | `0xbc9769b  mov rax,0xE428F824F8A1906B` | [V] |
| CalculateAverage | 0xbc97e44 | 8 | `0xbc97e44  mov rax,0xA440136077CFD138` | [V] |
| ToneMappingHistogram | 0xbcc57f9 | 8 | `0xbcc57f9  mov rax,0x2F1BC38137DF4E9D` | [V] |

| ClearVertexIrradianceCache | 0xbcc4da5 | 8 | `0xbcc4da5  mov rax,0x2C96D87A7FAA55B2` | [V] |
| ClearFaceIrradianceCache | 0xbcc4e01 | 8 | `0xbcc4e01  mov rax,0x7A51AC100718A60D` | [V] |
| ResolveLightMeasurement | 0xbcc4e5d | 8 | `0xbcc4e5d  mov rax,0x63BDD9A7481AE97B` | [V] |
| CopyToFinal | 0xbcc5919 | 8 | `0xbcc5919  mov rax,0x412B84A4037CE343` | [V] |
| CheckerboardInterleave | 0xbcc5975 | 8 | `0xbcc5975  mov rax,0x49E88F350A2C9215` | [V] |
| BlurGradients | 0xbcc59e2 | 8 | `0xbcc59e2  mov rax,0xBE154655BC88B01D` | [V] |
| TileClassification | 0xbcc5a3e | 8 | `0xbcc5a3e  mov rax,0x9757B0DF09D5D771` | [V] |
| FinalCombine | 0xbcc5339 | 8 | `0xbcc5339  mov rax,0xFB1CB76A24A5DD0E` | [V] |
| DiffuseFireflyFilter | 0xbcc5395 | 8 | `0xbcc5395  mov rax,0x53762D68F48E03E` | [V] |
| DiffuseFireflyFilterSH | 0xbcc53f1 | 8 | `0xbcc53f1  mov rax,0x624296FC51FE5A03` | [V] |

| SpecularFireflyFilter | 0xbcc544d | 8 | `0xbcc544d  mov rax,0x9FDF9EC13C9F5FBF` | [V] |
| CalculateFaceData | 0xbcc54a9 | 8 | `0xbcc54a9  mov rax,0x3803E9A388CFC8EC` | [V] |
| CheckerboardUpscale | 0xbcc5505 | 8 | `0xbcc5505  mov rax,0x9A0F96B3081CA3D` | [V] |
| CheckerboardUpscaleSH | 0xbcc5561 | 8 | `0xbcc5561  mov rax,0x5013FA316F97FDD4` | [V] |
| TemporalDenoising | 0xbcc55bd | 8 | `0xbcc55bd  mov rax,0xD6A300E579E405DD` | [V] |
| ShadowDenoising | 0xbcc5626 | 8 | `0xbcc5626  mov rax,0xC8D287F863E9664B` | [V] |
| FinalizeDenoising | 0xbcc5682 | 8 | `0xbcc5682  mov rax,0x3CA6254D32D4FE7D` | [V] |
| BlendCheckerboardFieldsShadow | 0xbcc56de | 8 | `0xbcc56de  mov rax,0xE95702EACCEB0C62` | [V] |
| PreBlasSkinDispatch | 0xbbe4399 | 8 | `0xbbe4399  mov rax,0xC2213BBE3E359E8F` | [V] |
| PrepareTLAS | 0xbbe5c43 | 8 | `0xbbe5c43  mov rax,0xB2D441638D31EA7A` | [V] |

| AlphaTestCracks | 0xbbf4180 | 8 | `0xbbf4180  mov rax,0x5ED619C4A7E5B04E` | [V] |
| Combine | 0xbc0b70a | 8 | `0xbc0b70a  mov rax,0x4E50856C4371E38` | [V] |
| MinMaxInitialize | 0xbc8093f | 8 | `0xbc8093f  mov rdx,0x92530C0E954B0A71` | [V] |
| MinMaxDownSample | 0xbc8099a | 8 | `0xbc8099a  mov rdx,0x3C4EA7FE28141385` | [V] |
| SSRFillGaps | 0xbc84c24 | 8 | `0xbc84c24  mov rdx,0x1DF55AD7E2C2C59F` | [V] |
| AdaptiveDenoiserCalculateGradientsInline | 0xbcc5c73 | 8 | `0xbcc5c73  mov rax,0x87FA674D8763C6E6` | [V] |
| AdaptiveDenoiserGenerateReferenceInline | 0xbcc5ccf | 8 | `0xbcc5ccf  mov rax,0x4C4F1454F8C12D01` | [V] |
| SpecularRayGenInline | 0xbcc5d2b | 8 | `0xbcc5d2b  mov rax,0x6AED31FEC210547` | [V] |
| ExplicitLightSamplingInline | 0xbcc5d87 | 8 | `0xbcc5d87  mov rax,0x27614242CDFD90BB` | [V] |

| PathTracingRayGenInline | 0xbcc5de3 | 8 | `0xbcc5de3  mov rax,0x35AC32E3669C0ED3` | [V] |
| UpdateVertexIrradianceCacheInline | 0xbcc5e3f | 8 | `0xbcc5e3f  mov rax,0x4F254A064827BC0F` | [V] |
| UpdateFaceIrradianceCacheInline | 0xbcc5e9b | 8 | `0xbcc5e9b  mov rax,0x1FEDA5A914342CE8` | [V] |
| CalculateInscatterInline | 0xbcc5ef7 | 8 | `0xbcc5ef7  mov rax,0xBFEC38B470AF2943` | [V] |
| CalculateGIInscatterInline | 0xbcc5f53 | 8 | `0xbcc5f53  mov rax,0xCD7C565551F4E5CB` | [V] |
| IncidentLightMeterInline | 0xbcc5faf | 8 | `0xbcc5faf  mov rax,0xABBF0FC79F7BFCC3` | [V] |
| CubemapToOffscreen | 0xbcd7d31 | 8 | `0xbcd7d31  mov rax,0x7C4FCFDFE7A16EA2` | [V] |
| Convolve | 0xbcdbcf4 | 8 | `0xbcdbcf4  mov r9,0x512B734838D005B9` | [V] |

| Blit | 0xbb4828d | 8 | `0xbb4828d  mov rax,0x1114FF7E59AE421C` | [V] |
| ForwardPBRAlphaTest | 0xbb85489 | 8 | `0xbb85489  mov rax,0xD858719899F35B00` | [V] |
| ForwardPBRTransparent | 0xbb854dd | 8 | `0xbb854dd  mov rax,0x110679A640739046` | [V] |
| HighlightTextureEdge | 0xbb88535 | 8 | `0xbb88535  mov rax,0x9283B64CEBA462CB` | [V] |
| NothingTask | 0xbbc5673 | 8 | `0xbbc5673  mov rax,0x9204C57F39A196B7` | [V] |
| LuminanceHistogram | 0xbc8f694 | 8 | `0xbc8f694  mov rax,0xEE7C669FCB4BF335` | [I] |
| HistogramBuild | 0xbc90ace | 8 | `0xbc90ace  mov rax,0xB652FAF8CA7FA5DF` | [V] |
| CleanUp | 0xbc96bfe | 8 | `0xbc96bfe  mov rax,0xAB1A46491762453` | [V] |
| BlendCheckerboardFields | 0xbcc51bc | 8 | `0xbcc51bc  mov rax,0x9083714FD6B03662` | [V] |
| AtrousSH | 0xbcc5277 | 8 | `0xbcc5277  mov rax,0x6D789C9D71FBCC76` | [V] |

LuminanceHistogram tag note: the 0xbc8f694 site loads imm 0xEE7C669FCB4BF335 = fnv1("LuminanceHistogram CleanUp") per render_hashes.txt ('LuminanceHistogram CleanUp' rdata x2); no exact-name 'LuminanceHistogram' (fnv1 0x2a446d92e190d311) immediate site exists in render_hashes.txt, so exact-name is [I] via the combined-string site, not [V].

| BlendCheckerboardFieldsSH | 0xbcc52d3 | 8 | `0xbcc52d3  mov rax,0x6DF7F9880F3621A7` | [V] |
| PrimaryCheckerboardRayGenInline | 0xbcc5b03 | 8 | `0xbcc5b03  mov rax,0x28A6BA54D3ADA2DB` | [V] |
| SunShadowRayGenInline | 0xbcc5b5f | 8 | `0xbcc5b5f  mov rax,0x3386EEC1F9232E70` | [V] |
| RefractionRayGenInline | 0xbcc5bbb | 8 | `0xbcc5bbb  mov rax,0x4F578721DA378E75` | [V] |
| DiffuseRayGenCombinedInline | 0xbcc5c17 | 8 | `0xbcc5c17  mov rax,0xE8C112269CE9C229` | [V] |
| GeometryPrepass | 0x55ff9a9 | 8 | `0x55ff9a9  mov rax,0x680E1340911894F3` | [V] |
| PopulateVolume | 0x55fdf19 | 8 | `0x55fdf19  mov rax,0xBC86151FCB47FCC9` | [V] |
| MotionOnly | 0x5623282 | 8 | `0x5623282  mov rax,0xD5CD0115D2FF50CD` | [V] |
| IBLSyncPoint | 0x562be6c | 8 | `0x562be6c  mov rax,0x50636E79534C4249` | [I] |
| DebugBlitPhase | 0x5633c82 | 8 | `0x5633c82  mov rax,0x696C426775626544` | [I] |

## 6p pass-name proof notes
- Confirmed [V] builder-immediate sites (mov rax, imm64 == fnv1(name)): GeometryPrepass 0x55ff9a9 imm 0x680E1340911894F3, PopulateVolume 0x55fdf19 imm 0xBC86151FCB47FCC9, MotionOnly 0x5623282 imm 0xD5CD0115D2FF50CD, plus NothingTask 0xbbc5673 imm 0x9204c57f39a196b7 (already [V]) and builder site 0x562bece.
- [I] name-only proof (inline string piece built; hash-immediate load site NOT located): IBLSyncPoint 'IBLSyncP' at 0x562be6c (hash 0x463A4116E7586005 not found); DebugBlitPhase 'DebugBli' at 0x5633c82 (hash 0xBB07784B1B637368 not found).
- [?] names with no render_hashes.txt exact match and no locatable address/imm (no row possible): RasterizedOpaque/AlphaTest/Transparent, ForceForwardPBROpaque, FullScreenOverlayTransparent, TransparentDegamma, WaterDepthBufferBlit, SSRColorBufferBlit, BlitUncompressed, LuminanceHistogram-exact.

0x55ff9a9  mov rax,0x680E1340911894F3
0x55fdf19  mov rax,0xBC86151FCB47FCC9
0x5623282  mov rax,0xD5CD0115D2FF50CD
0x562be6c  mov rax,0x50636E79534C4249
0x5633c82  mov rax,0x696C426775626544

CLOSES? NO — not every pending part is [V]: IBLSyncPoint and DebugBlitPhase lack a readable mov reg,imm64==fnv1(name) site (only inline string pieces [I]); 8 render_hashes-absent names (RasterizedOpaque/AlphaTest/Transparent, ForceForwardPBROpaque, FullScreenOverlayTransparent, TransparentDegamma, WaterDepthBufferBlit, SSRColorBufferBlit, BlitUncompressed, LuminanceHistogram-exact) have no provable address or immediate.







