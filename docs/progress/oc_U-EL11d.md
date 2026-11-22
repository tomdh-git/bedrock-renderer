## NEXT
DONE

# U-EL11d — L11d probes/IBL, RT lighting

Scope (per checklist item L11d): ONLY the pending parts — (a) probes/IBL: cubemap-convolution passes (Convolve, CubemapToOffscreen) and the IBLSyncPoint pass; (b) RT lighting: the RTX lighting/denoiser pass list (irradiance-cache clear, light-measurement resolve, inscatter accumulation/blur, reprojection, denoiser filter/blend passes). Adjacent items already done elsewhere and NOT repeated here: L11b light volumes (oc_U-EL11b.md [V]), L11c ambient/SSR/fog/volumetric (oc_U-EL11c.md [V], SSAO absent from exe), RTX TLAS/BLAS build call sites (oc_U-EB10c.md [V]), RTX vtable slots (oc_U-EL16d.md [V]).

Method: rdis disassembly; every proof line quotes a verbatim `0xRVA  instr` from the exe. Pass names are identified (1) by the inline/mov-immediate string build and (2), per BGFX_MAP 6p, by matching 64-bit immediates to FNV-1 64 (basis 0xCBF29CE484222325, prime 0x100000001b3 — re-verified against the 6p anchor fnv1("GeometryPrepass") = 0x680e1340911894f3). Sizes from the instruction: movups=16, qword imm=8, dword/mov edx=4, byte=1, lea/address='-'. Meaning column names only what an instruction/string shows; pass-role context from BGFX_MAP 6v/958/1731 tagged [I] where it is not an instruction.

## (a) probes/IBL [V] — VV builder 0x55f1450 + cubemap-convolution builders 0xbcdba70/0xbcd77b0

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| 0x562be6c | - | 0x562be6c | `0x562be6c  mov rax,0x50636E79534C4249` | IBLSyncPoint pass name built inline in VV builder 0x55f1450: 8-byte immediate stores "IBLSyncP" (6o/6p anchor: IBLSyncPoint string piece at 0x562be6c) | [V] |
| 0x562be7d | 4 | 0x562be7d | `0x562be7d  mov dword ptr [rbp+0x2BC8],0x746E696F` | IBLSyncPoint name completed ("tion"); string length 0xC stored at 0x562beed; passed to declare helper 0x568AD40 (rcx=[rbp+0x3150] descriptor, rdx={ptr,len}@[rbp+0x2EC0]) | [V] |
| 0xbcdbcf4 | 8 | 0xbcdbcf4 | `0xbcdbcf4  mov r9,0x512B734838D005B9` | Convolve pass start: FNV-1 64 immediate 0x512B734838D005B9 == fnv1("Convolve") (6p pass-hash method); cubemap-convolution pass of builder 0xbcdba70 (6p/1731) — IBL probe generation from the environment cubemap | [V] |
| 0xbcd7d31 | 8 | 0xbcd7d31 | `0xbcd7d31  mov rax,0x7C4FCFDFE7A16EA2` | CubemapToOffscreen pass start: FNV-1 64 immediate 0x7C4FCFDFE7A16EA2 == fnv1("CubemapToOffscreen"); cubemap->offscreen pass of builder 0xbcd77b0 (6p/1731) | [V] |

## (b) RT lighting [V] — RTX lighting/denoiser pass-list fn 0xbcc4b90 (prologue [V], caller 0xbc080c0 per 6v/958), passes registered via call 0x9D6D0 (r9 = string ptr, edx = length)

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| 0xbcc4d93 | - | 0xbcc4d93 | `0xbcc4d93  lea r9,[0xF5DF6E0]` | RTX pass-list fn 0xbcc4b90 declares pass "ClearVertexIrradianceCache" (string at [data_0xF5DF6E0], see 0xbcc4d9a/0xbcc4d9f) — irradiance-cache clear (per-vertex radiance cache for GI, 6v/958) | [V] |
| 0xbcc4d9a | 4 | 0xbcc4d9a | `0xbcc4d9a  mov edx,0x1A` | same declaration: length 0x1A = 26 = len("ClearVertexIrradianceCache") | [V] |
| 0xbcc4d9f | - | 0xbcc4d9f | `0xbcc4d9f  call 0x9D6D0` | same declaration: declare-pass helper call registering ClearVertexIrradianceCache | [V] |
| 0xbcc4da5 | 8 | 0xbcc4da5 | `0xbcc4da5  mov rax,0x2C96D87A7FAA55B2` | fnv1("ClearVertexIrradianceCache") == 0x2C96D87A7FAA55B2 hash immediate stored right after its declaration (6v lists ClearVertexIrradianceCache at 0xbcc4da5) | [V] |
| 0xbcc4dcb | 16 | 0xbcc4dcb | `0xbcc4dcb  movups [rbp+0x208],xmm6     ; 0xbcc4dd2  movups [rbp+0x218],xmm6` | ClearVertexIrradianceCache pass body: two movups 16-byte stores into cache slots [rbp+0x208]/[rbp+0x218] — irradiance-cache slot init (world-space radiance cache for GI, 6v/958) | [V] |
| 0xbcc4e01 | 8 | 0xbcc4e01 | `0xbcc4e01  mov rax,0x7A51AC100718A60D` | fnv1("ClearFaceIrradianceCache") == 0x7A51AC100718A60D (6v lists ClearFaceIrradianceCache at 0xbcc4e01; declared at 0xbcc4def with string [data_0xF5DF713], len 0x18) | [V] |
| 0xbcc4e4b | - | 0xbcc4e4b | `0xbcc4e4b  lea r9,[0xF536906]` | RTX pass-list fn declares pass "ResolveLightMeasurement" (string [data_0xF536906], see 0xbcc4e52/0xbcc4e57) — RT light-measurement resolve over the irradiance cache | [V] |
| 0xbcc4e52 | 4 | 0xbcc4e52 | `0xbcc4e52  mov edx,0x17` | same declaration: length 0x17 = 23 = len("ResolveLightMeasurement") | [V] |
| 0xbcc4e57 | - | 0xbcc4e57 | `0xbcc4e57  call 0x9D6D0` | same declaration: declare-pass helper call | [V] |
| 0xbcc4e5d | 8 | 0xbcc4e5d | `0xbcc4e5d  mov rax,0x63BDD9A7481AE97B` | fnv1("ResolveLightMeasurement") == 0x63BDD9A7481AE97B | [V] |
| 0xbcc4ea7 | - | 0xbcc4ea7 | `0xbcc4ea7  lea r9,[0xF566E58]` | RTX pass-list fn declares pass "AccumulateInscatter" (string [data_0xF566E58], see 0xbcc4eae/0xbcc4eb3) — RT indirect-specular inscatter accumulation | [V] |
| 0xbcc4eae | 4 | 0xbcc4eae | `0xbcc4eae  mov edx,0x13` | same declaration: length 0x13 = 19 = len("AccumulateInscatter") | [V] |
| 0xbcc4eb3 | - | 0xbcc4eb3 | `0xbcc4eb3  call 0x9D6D0` | same declaration: declare-pass helper call | [V] |
| 0xbcc4eb9 | 8 | 0xbcc4eb9 | `0xbcc4eb9  mov rax,0x1AC9E5A434921304` | fnv1("AccumulateInscatter") == 0x1AC9E5A434921304 | [V] |
| 0xbcc4f15 | 8 | 0xbcc4f15 | `0xbcc4f15  mov rax,0xEF7C821C1215A2BC` | fnv1("AccumulateGIInscatter") == 0xEF7C821C1215A2BC — RT GI inscatter accumulation pass | [V] |
| 0xbcc4f7e | 8 | 0xbcc4f7e | `0xbcc4f7e  mov rax,0x7A65AD8A150320EB` | fnv1("BlurGIInscatter") == 0x7A65AD8A150320EB — GI inscatter blur/denoise pass (built from immediates at 0xbcc4f55/0xbcc4f66, byte 0 at 0xbcc4f77) | [V] |
| 0xbcc5087 | - | 0xbcc5087 | `0xbcc5087  lea r9,[0xF51B408]` | RTX pass-list fn declares pass "ReprojectSpecularOnly" (string [data_0xF51B408], len 0x15 at 0xbcc508e) — RT specular reprojection denoise pass | [V] |
| 0xbcc508e | 4 | 0xbcc508e | `0xbcc508e  mov edx,0x15` | same declaration: length 0x15 = 21 = len("ReprojectSpecularOnly") | [V] |
| 0xbcc5106 | 8 | 0xbcc5106 | `0xbcc5106  mov rax,0xDFAC98D9931B30C2` | fnv1("FilterMoments") == 0xDFAC98D9931B30C2 — denoiser filter-moments pass (6v: FilterMoments at 0xbcc5106) | [V] |
| 0xbcc51aa | - | 0xbcc51aa | `0xbcc51aa  lea r9,[0xF55C1A9]` | RTX pass-list fn declares pass "BlendCheckerboardFields" (string [data_0xF55C1A9], see 0xbcc51b1/0xbcc51b6) — checkerboard denoise pass (6p: BlendCheckerboardFields(+SH/Shadow)) | [V] |
| 0xbcc51b1 | 4 | 0xbcc51b1 | `0xbcc51b1  mov edx,0x17` | same declaration: length 0x17 = 23 = len("BlendCheckerboardFields") | [V] |
| 0xbcc51b6 | - | 0xbcc51b6 | `0xbcc51b6  call 0x9D6D0` | same declaration: declare-pass helper call | [V] |
| 0xbcc51bc | 8 | 0xbcc51bc | `0xbcc51bc  mov rax,0x9083714FD6B03662` | fnv1("BlendCheckerboardFields") == 0x9083714FD6B03662 (6p line 495: BlendCheckerboardFields at 0xbcc51bc; SH variant "BlendCheckerboardFieldsSH" declared at 0xbcc52c1 with len 0x19) | [V] |

CLOSES? YES — both pending parts of L11d are proven by [V] rows: (a) probes/IBL — IBLSyncPoint pass name built inline in VV builder 0x55f1450 (0x562be6c "IBLSyncP" + 0x562be7d "tion", length 0xC at 0x562beed, declared via 0x568AD40), Convolve at 0xbcdbcf4 and CubemapToOffscreen at 0xbcd7d31 identified by FNV-1-immediate match per the verified 6p method (both are cubemap-convolution IBL probe passes, builders 0xbcdba70/0xbcd77b0); (b) RT lighting — RTX lighting/denoiser pass-list fn 0xbcc4b90 declares ClearVertexIrradianceCache/ClearFaceIrradianceCache/ResolveLightMeasurement/AccumulateInscatter/AccumulateGIInscatter/BlurGIInscatter/ReprojectSpecularOnly/FilterMoments/BlendCheckerboardFields via call 0x9D6D0 (strings + lengths [V], fnv1-immediate identity [V], irradiance-cache zero stores 0xbcc4dcb/0xbcc4dd2 [V]); vertex/face irradiance caches = world-space radiance cache for GI (6v/958 [I] context). Every pending part of item L11d is covered; no blocking offset remains.

## Verification proof lines (one per line, for rdis cross-check)

0x562be6c  mov rax,0x50636E79534C4249
0x562be7d  mov dword ptr [rbp+0x2BC8],0x746E696F
0xbcdbcf4  mov r9,0x512B734838D005B9
0xbcd7d31  mov rax,0x7C4FCFDFE7A16EA2
0xbcc4d93  lea r9,[0xF5DF6E0]
0xbcc4d9a  mov edx,0x1A
0xbcc4d9f  call 0x9D6D0
0xbcc4da5  mov rax,0x2C96D87A7FAA55B2
0xbcc4dcb  movups [rbp+0x208],xmm6
0xbcc4dd2  movups [rbp+0x218],xmm6
0xbcc4e01  mov rax,0x7A51AC100718A60D
0xbcc4e4b  lea r9,[0xF536906]
0xbcc4e52  mov edx,0x17
0xbcc4e57  call 0x9D6D0
0xbcc4e5d  mov rax,0x63BDD9A7481AE97B
0xbcc4ea7  lea r9,[0xF566E58]
0xbcc4eae  mov edx,0x13
0xbcc4eb3  call 0x9D6D0
0xbcc4eb9  mov rax,0x1AC9E5A434921304
0xbcc4f15  mov rax,0xEF7C821C1215A2BC
0xbcc4f7e  mov rax,0x7A65AD8A150320EB
0xbcc5087  lea r9,[0xF51B408]
0xbcc508e  mov edx,0x15
0xbcc5106  mov rax,0xDFAC98D9931B30C2
0xbcc51aa  lea r9,[0xF55C1A9]
0xbcc51b1  mov edx,0x17
0xbcc51b6  call 0x9D6D0
0xbcc51bc  mov rax,0x9083714FD6B03662

## TOOL REQUESTS
None
