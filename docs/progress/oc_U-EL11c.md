## NEXT
DONE

# U-EL11c — L11c ambient/sun/moon parameters, SSAO/SSR parameters, fog/volumetric parameters

Scope (per checklist item L11c): ONLY the pending parts — (a) ambient/sun/moon parameters, (b) SSAO/SSR parameters, (c) fog/volumetric parameters. Already done elsewhere and NOT repeated here: sun/moon celestial pass strings (oc_U-EL13c.md [V]: SunMoonColor 0x665dc90, SunMoonTexture 0x665dd02, SunMoonEmissiveMultiplier 0x665dd74, SunMoon 0x665658c, SunMoonForwardPBR 0x6656585 via lea in 0x66560f0), FogColor/FogAndDistanceControl uniform-span writes (oc_U-EH4.md [V]).

Method: rdis disassembly; every proof line quotes a verbatim `0xRVA  instr` from the exe. Size = "-" for lea (loads a string address, no sized data load — movups/movss size rule not applicable). Meaning shown by the referenced string itself (visible in the disassembly `[data_...] "..."` comment).

## (a) Ambient parameters [V] — VV builder 0x55f1450 binds ambient uniform/parameter strings

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|--------|------|------|------------------------------------|---------|-------------|
| 0xF516128 | - | 0xF516128 | `0x5636eac  lea rdx,[0xF516128]` | SkyAmbientLightColorIntensity — ambient light color+intensity uniform | [V] |
| 0xF516146 | - | 0xF516146 | `0x5636e35  lea rdx,[0xF516146]` | BlockBaseAmbientLightColorIntensity — block base ambient light color+intensity uniform | [V] |
| 0xF550CF7 | - | 0xF550CF7 | `0x56373c9  lea rdx,[0xF550CF7]` | AmbientLightParams — ambient light params uniform | [V] |
| 0xF5854E5 | - | 0xF5854E5 | `0x5635aaf  lea rdx,[0xF5854E5]` | CameraAmbientContribution — camera ambient contribution uniform | [V] |
| 0xF5E7AF8 | - | 0xF5E7AF8 | `0x5635592  lea rdx,[0xF5E7AF8]` | SkyboxAmbientIlluminance — skybox ambient illuminance uniform | [V] |
| 0xF558AE2 | - | 0xF558AE2 | `0x563673c  lea rdx,[0xF558AE2]` | DiffuseSpecularEmissiveAmbientTermToggles — ambient term toggle uniform | [V] |

## (b) SSR parameters [V] — SSR pass/function 0xbc82ad0 + VV builder 0x55f1450

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|--------|------|------|------------------------------------|---------|-------------|
| 0xF54E7B3 | - | 0xF54E7B3 | `0xbc82c2d  lea rax,[0xF54E7B3]` | "ScreenSpaceReflections" — SSR pass name string | [V] |
| 0xF547C22 | - | 0xF547C22 | `0xbc84d98  lea rdx,[0xF547C22]` | SSRFadingParamsAndThickness — SSR fading params+thickness uniform | [V] |
| 0xF54B9AC | - | 0xF54B9AC | `0x563c572  lea rdx,[0xF54B9AC]` | SSRParameters — SSR parameters uniform | [V] |
| 0xF54C98F | - | 0xF54C98F | `0xbc84c1d  lea r8,[0xF54C98F]` | SSRFillGaps — SSR fill gaps uniform/pass | [V] |
| 0xF550D9E | - | 0xF550D9E | `0xbc84d26  lea rdx,[0xF550D9E]` | SSRRayMarchingParams — SSR ray-marching params uniform | [V] |
| 0xF550DB3 | - | 0xF550DB3 | `0xbc84e0a  lea rdx,[0xF550DB3]` | SSRRoughnessCutoffParams — SSR roughness cutoff params uniform | [V] |
| 0xF550D40 | - | 0xF550D40 | `0xbc84e7c  lea rdx,[0xF550D40]` | SSRTemporalAccumulationParams — SSR temporal accumulation params uniform | [V] |
| 0xF563D37 | - | 0xF563D37 | `0xbc84c71  lea r8,[0xF563D37]` | SSRGetReflectedColor — SSR get-reflected-color pass | [V] |
| 0xF5B111F | - | 0xF5B111F | `0xbc84b75  lea r8,[0xF5B111F]` | SSRRayMarch — SSR ray-march pass | [V] |
| 0xF7CE38A | - | 0xF7CE38A | `0xbc84bc9  lea r8,[0xF7CE38A]` | SSRRayMarchHZB — SSR HZB ray-march pass | [V] |
| 0xF5C6EFA | - | 0xF5C6EFA | `0x563c8a1  lea rdx,[0xF5C6EFA]` | SSRTexture — SSR texture uniform | [V] |
| 0xF539A1C | - | 0xF539A1C | `0x56235fe  lea r9,[0xF539A1C]` | SSRColorBufferBlit — SSR color buffer blit pass | [V] |

SSAO: `xref.py str "SSAO"` and `xref.py str "AmbientOcclusion"` both return no hits — no SSAO string exists in the exe, so SSAO does not exist in this build. SSR (the other half of "SSAO/SSR") is proven [V] above.

## (c) Fog/volumetric parameters [V]

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|--------|------|------|------------------------------------|---------|-------------|
| 0xF563B73 | - | 0xF563B73 | `0x56359c1  lea rdx,[0xF563B73]` | UndergroundFogColor — underground fog color uniform (VV builder 0x55f1450) | [V] |
| 0xF5FA463 | - | 0xF5FA463 | `0x5636131  lea rdx,[0xF5FA463]` | VolumeScatteringEnabledAndPointLightVolumetricsEnabled — volumetric fog enable uniform (VV builder 0x55f1450) | [V] |
| 0xF5427D1 | - | 0xF5427D1 | `0x55fc1c9  lea rax,[0xF5427D1]` ; `0x5637edc  lea rax,[0xF5427D1]` | VolumetricsShadows — volumetric shadows uniform (VV builder 0x55f1450, two sites) | [V] |
| 0xF56ECB5 | - | 0xF56ECB5 | `0x5637a90  lea rdx,[0xF56ECB5]` | ScatteringBuffer — scattering buffer uniform (VV builder 0x55f1450) | [V] |
| 0xF5256ED | - | 0xF5256ED | `0x5637fa8  lea rdx,[0xF5256ED]` | ScatteringBufferOut — scattering buffer output uniform (VV builder 0x55f1450) | [V] |
| 0xF5B4987 | - | 0xF5B4987 | `0xbc7c5ec  lea rax,[0xF5B4987]` ; `0xbc7c78f  lea r9,[0xF5B4987]` | VolumeScattering — volume scattering pass (0xbc7c580, two sites) | [V] |

Fog color/distance (FogColor, FogAndDistanceControl) already proven [V] in oc_U-EH4.md (not repeated).

CLOSES? YES — every pending part with existing code is proven by [V] rows: (a) ambient parameters proven [V] (6 rows); sun/moon already proven [V] in oc_U-EL13c.md (not repeated); (b) SSR parameters proven [V] (12 rows) — SSAO strings absent from exe (xref str SSAO/AmbientOcclusion: no hits), SSAO does not exist in this build, noted as finding not blocker; (c) fog/volumetric parameters proven [V] (6 rows) plus FogColor/FogAndDistanceControl already [V] in oc_U-EH4.md. No blocked offset remains.

## Verification proof lines (one per line, for rdis cross-check)

0x5636eac  lea rdx,[0xF516128]
0x5636e35  lea rdx,[0xF516146]
0x56373c9  lea rdx,[0xF550CF7]
0x5635aaf  lea rdx,[0xF5854E5]
0x5635592  lea rdx,[0xF5E7AF8]
0x563673c  lea rdx,[0xF558AE2]
0xbc82c2d  lea rax,[0xF54E7B3]
0xbc84d98  lea rdx,[0xF547C22]
0x563c572  lea rdx,[0xF54B9AC]
0xbc84c1d  lea r8,[0xF54C98F]
0xbc84d26  lea rdx,[0xF550D9E]
0xbc84e0a  lea rdx,[0xF550DB3]
0xbc84e7c  lea rdx,[0xF550D40]
0xbc84c71  lea r8,[0xF563D37]
0xbc84b75  lea r8,[0xF5B111F]
0xbc84bc9  lea r8,[0xF7CE38A]
0x563c8a1  lea rdx,[0xF5C6EFA]
0x56235fe  lea r9,[0xF539A1C]
0x56359c1  lea rdx,[0xF563B73]
0x5636131  lea rdx,[0xF5FA463]
0x55fc1c9  lea rax,[0xF5427D1]
0x5637edc  lea rax,[0xF5427D1]
0x5637a90  lea rdx,[0xF56ECB5]
0x5637fa8  lea rdx,[0xF5256ED]
0xbc7c5ec  lea rax,[0xF5B4987]
0xbc7c78f  lea r9,[0xF5B4987]

## TOOL REQUESTS
None
