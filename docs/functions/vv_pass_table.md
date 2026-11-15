# VV/Fancy/RTX pass table: pass -> builder -> closure vtable -> body -> dossier (1.26.62.01) [V unless noted]

Source of rows: docs/data/vv_closures.txt (tools/sigs/vvclosures.py). Dossier column points into docs/functions/vv_group_builders.md (G) or vv_lambda_bodies.md (B).

| Pass | Builder | Closure vtable | Body rva (size) | Dossier |
|---|---|---|---|---|
| TAAUpscaling | 0xbc8a380 | 0xf44b2e0 | 0xbc8cfd0 (0x1775) | B TAAU (10 uniforms, hash 0x765ef57e0263ffb6) |
| CombineVoxelLighting | 0xbb3e2b0 | 0xf43ef90 | 0xbc0b240 (0x88b) | B, G Voxel group |
| CausticsMultiplierPass | 0xbb6b350 | 0xf43f9e0 | 0xbc2c590 (0x558) | G DeferredLighting |
| DirectionalLightingPass | 0xbb6b350 | 0xf43fa10 | 0xbc2cd20 (0x5f2) | G DeferredLighting |
| DiscreteIndirectCombinedLightingPass | 0xbb6b350 | 0xf43fa40 | 0xbc2d550 (0x5e4) | G DeferredLighting |
| SurfaceRadianceUpscalePass | 0xbb74040 | 0xf43fa70 | 0xbc2dd20 (0x5db) | G SurfaceRadianceUpscale |
| WaterExtinction | 0xbb7efb0 | 0xf43fb90 | 0xbc2eb50 (0x54c) | G WaterExtinction |
| WaterSurface | 0xbb81880 | 0xf43fbc0 | 0xbc2f4a0 (0x85b) | G WaterSurface |
| DoIndirectSpecularUpscale | 0xbb8eb70 | 0xf43fdb0 | 0xbc36140 (0x5aa) | G, B |
| DepthAndNormal (draw list) | 0xbb78240 | 0xf43faa0 | 0x56ad350 (0xf6) | B 0x56ad350 |
| NothingTask item lists (x3) | 0xbbbfc50 | 0xf4407f0 / f440850 / f4408b0 | 0xbc38c20 (0xda8) | B |
| NothingTask small body | 0xbbbfc50, 0xbbe2d50, 0xbc8eb90, 0xbcd77b0 | 0xf43eb20, f43ec60, f44b3a0/420/480, f44c170 | 0x56aeeb0 (0x123) | B (view-only) |
| ScreenDraw (EditorHighlight) | 0xbb84ee0 | 0xf43fbf0 | 0xbc04dc0 (0x5d3) | G Fullscreen |
| RTX PreBlasSkinDispatch | 0xbbe2d50 | 0xf43eb80 | 0xbc068f0 (0x5fa) | B 0xbc068f0 |
| RTX prep | 0xbbe2d50 | 0xf43ebb0 | 0xbc07890 (0x12f) | B |
| RTX PrepareTLAS (instance upload) | 0xbbe2d50 | 0xf43ebe0 | 0xbc07a70 (0x162) | B 0xbc07a70/0xbc71da0 |
| RTX driver (43 passes) | 0xbbe2d50 | 0xf43ec30 | 0xbc080c0 (0x25b) -> 0xbcc4b90 | B 0xbcc4b90 |
| RTX thunk | 0xbbe2d50 | 0xf43ecf0 | 0xbc084b0 (0x71) | B |
| ClusterLights | 0xbc57460 | 0xf4412d0 | 0xbc5bad0 (0x19d1) | B |
| VolumeScattering | 0xbc7c580 | 0xf44b200 | 0xbc7e100 (0xa5f) | B |
| LuminanceHistogram (compute) | 0xbc8eb90 | 0xf44b370 | 0xbc96950 (0x4d1) | B compute table |
| HistogramBuild (compute) | 0xbc8eb90 | 0xf44b3f0 | 0xbc973e0 (0x4e1) | B |
| CalculateAverage | 0xbc8eb90 | 0xf44b450 | 0xbc97bc0 (0x4b1) | B |
| Bloom down (ScreenDraw) | 0xbc98310 | 0xf44b4e0 | 0xbc04dc0 | G Fullscreen, B bloom |
| ClearBilateralGrid | 0xbc9d7a0 | 0xf44b580 | 0xbca85e0 (0x8f8) | B |
| BuildBilateralGrid | 0xbc9d7a0 | 0xf44b5d0 | 0xbca9770 (0xab8) | B |
| FilterBilateralGrid | 0xbc9d7a0 | 0xf44b620 | 0xbcaaac0 (0x988) | B |
| ApplyLocalExposure | 0xbc9d7a0 | 0xf44b650 | 0xbc04dc0 | G |
| CubemapToOffscreen | 0xbcd77b0 | 0xf44c140 | 0xbc0f130 (0x648) | B |
| FSR1 compute (EASU) | 0xbcb3cf0 | 0xf44be30 | 0xbcb7590 (0x3d8) | B (16x16 tiles) |
| FSR1 frag | 0xbcb3cf0 | 0xf44be80 | 0xbcb7e70 (0x447) | B |
| SSR x4 (ScreenDraw) | 0xbc82ad0 via 0xbc88560 | 0xf44b280 | 0xbc04dc0 | G SSR |
| ScreenDraw-only builders | 0xbc7f6e0, 0xbc9ada0, 0xbcdba70 | none non-trivial | 0xbc04dc0 | G Fullscreen |
| Tonemap / colour grading | 0xbcacd90 | see B | see B | B tonemap |

Fancy (L6d): no Fancy-specific builder is distinguished in the closure scan; the Fancy list is the union of the Deferred/Water/SurfaceRadianceUpscale/TAAU/Bloom/SSR/Tonemap rows above. [I] The Fancy-vs-VV selection flag is not isolated, so the per-mode membership is not proven.
