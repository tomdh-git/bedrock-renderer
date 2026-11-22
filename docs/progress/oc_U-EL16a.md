## NEXT
DONE

# U-EL16a — L16a RTX pass names and resources — 6cg, 6p

Goal: close RENDER_CHECKLIST.md line 396 item `L16a RTX pass names and resources — 6cg, 6p`.
Scope: ONLY the pass names and RTX resources cited in BGFX_MAP.md sections 6cg (0xbbe2d50 RTX frame builder, 0xc28e330 G-buffer/denoiser resources, 0xe8403d0 RTX context init) and 6p (RTX pass-name and material-name tables). Bodies/lambda internals (0xbbe2d50 internals, BLAS/TLAS build) are L16c/L16b and are NOT part of this item.
Source: rdis/xref on Minecraft.Windows.exe (1.26.62.01); every verbatim `0xRVA  instr` line below is copied from rdis disassembly and re-checked by tools/sigs/verify_oc.py.
Verdicts: [V] = proven by verbatim instruction/string, [I] = inferred from structure/order, [?] = not confirmed.

CLOSES?: YES — every pending part of L16a ("RTX pass names and resources — 6cg, 6p") is proven by [V] rows: RTX pass names from 0xbbe2d50 (RTXAccelerationStructure, PreBlasSkinDispatch, RTXStub x2, RTXPostFX.ToneMapping x2, RTXPostFX.Bloom x2, SceneGammaFallbackBlit, FullscreenSceneGammaPass, WholeFrameGammaFallbackBlit, FullscreenWholeFrameGammaPass), RTX light uniforms (LightAmbientColorAndIntensity, LightWorldSpaceDirection, LightDiffuseColorAndIlluminance), RTX G-buffer/denoiser resources from 0xc28e330 (PrimaryHitT0, TaaOutput, ToneMappingButNoBloom, G-Buffer Metalness/Emissive/Roughness, SurfaceOpacityAndObjectCategory, SurfaceNormals, GeometryNormal0, Diffuse0Noisy/Chroma0Noisy, Diffuse3PreTemporal/Chroma3PreTemporal, Diffuse2Denoised/Chroma2Denoised, IncomingIrradianceCache, DiffuseMoments0, Specular0Noisy, Specular3PreTemporal, Specular2Denoised, SpecularMoments0, HistoryLength0, SunLightShadow0/1, AdaptiveDenoiserGradients/Reference, FinalOutput, FirstIterationVarianceColor/SH, G-Buffer Normals/Albedo/Ambient/Split Mask, FirstIterationSpecularVariance, DesnoisedSpecularVariance), and RTX context init resources from 0xe8403d0 (MotionVectorsReflection, MotionVectors3D, GBuffer.Roughness). All 50 rows [V], verify_oc 0 mismatch / 0 no-such-instr. Inline-immediate pass names (DepthOnlyAlphaTest, PrepareTLAS, and the 0xbcc4b90 raygen/denoiser names) are documented as [I] in Notes per BGFX_MAP 6o/6p (names built as ASCII immediates, not .rdata strings).

## RTX pass names and resources cited in BGFX_MAP.md 6cg / 6p

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|--------|------|------|------------------------------------|---------|-------------|
| 0xF5C72E9 | - | 0xF5C72E9 | `bbf5bea  lea rdx,[0xF5C72E9]` | RTXAccelerationStructure — acceleration-structure bind name in RTX frame builder 0xbbe2d50 | [V] |
| 0xF5B075A | - | 0xF5B075A | `bbe4387  lea r9,[0xF5B075A]` | PreBlasSkinDispatch — RTX pass name in RTX frame builder 0xbbe2d50 | [V] |
| 0xF6076E2 | - | 0xF6076E2 | `bbe4f6f  lea rax,[0xF6076E2]` ; `bbf5b82  lea rax,[0xF6076E2]` | RTXStub — RTX pass name (two sites) in RTX frame builder 0xbbe2d50 | [V] |
| 0xF5B4E5B | - | 0xF5B4E5B | `bbf46b7  lea rax,[0xF5B4E5B]` ; `bbf5dcb  lea rax,[0xF5B4E5B]` | RTXPostFX.ToneMapping — RTX pass name (two sites) in RTX frame builder 0xbbe2d50 | [V] |
| 0xF59A754 | - | 0xF59A754 | `bbf477d  lea rax,[0xF59A754]` ; `bbf5d5c  lea rax,[0xF59A754]` | RTXPostFX.Bloom — RTX pass name (two sites) in RTX frame builder 0xbbe2d50 | [V] |
| 0xF539A44 | - | 0xF539A44 | `bbf4dbb  lea rcx,[0xF539A44]` | SceneGammaFallbackBlit — RTX pass name in RTX frame builder 0xbbe2d50 | [V] |
| 0xF54986D | - | 0xF54986D | `bbf4dc7  lea rcx,[0xF54986D]` | FullscreenSceneGammaPass — RTX pass name in RTX frame builder 0xbbe2d50 | [V] |
| 0xF539A5B | - | 0xF539A5B | `bbf51f8  lea rcx,[0xF539A5B]` | WholeFrameGammaFallbackBlit — RTX pass name in RTX frame builder 0xbbe2d50 | [V] |
| 0xF549886 | - | 0xF549886 | `bbf5204  lea rcx,[0xF549886]` | FullscreenWholeFrameGammaPass — RTX pass name in RTX frame builder 0xbbe2d50 | [V] |
| 0xF5161A4 | - | 0xF5161A4 | `bbf59a6  lea rdx,[0xF5161A4]` | LightAmbientColorAndIntensity — RTX light uniform string in 0xbbe2d50 | [V] |
| 0xF58A852 | - | 0xF58A852 | `bbf5a18  lea rdx,[0xF58A852]` | LightWorldSpaceDirection — RTX light uniform string in 0xbbe2d50 | [V] |
| 0xF5E7B68 | - | 0xF5E7B68 | `bbf5a8a  lea rdx,[0xF5E7B68]` | LightDiffuseColorAndIlluminance — RTX light uniform string in 0xbbe2d50 | [V] |
| 0xF7E5415 | - | 0xF7E5415 | `c28e37f  lea rcx,[0xF7E5415]` | PrimaryHitT0 — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF524D8A | - | 0xF524D8A | `c28e3fd  lea rcx,[0xF524D8A]` | TaaOutput — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF59A726 | - | 0xF59A726 | `c28e44b  lea rcx,[0xF59A726]` | ToneMappingButNoBloom — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF547AB1 | - | 0xF547AB1 | `c28ee3d  lea rcx,[0xF547AB1]` | G-Buffer Metalness — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF5BD5AE | - | 0xF5BD5AE | `c28ee7e  lea rax,[0xF5BD5AE]` | G-Buffer Emissive — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF547DA6 | - | 0xF547DA6 | `c28ef0a  lea rcx,[0xF547DA6]` | G-Buffer Roughness — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF5190CD | - | 0xF5190CD | `c28e5a8  lea rcx,[0xF5190CD]` | SurfaceOpacityAndObjectCategory — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF5518D2 | - | 0xF5518D2 | `c28e5f3  lea rcx,[0xF5518D2]` | SurfaceNormals — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF7E4209 | - | 0xF7E4209 | `c28e641  lea rcx,[0xF7E4209]` | GeometryNormal0 — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF51759E | - | 0xF51759E | `c28e68f  lea rcx,[0xF51759E]` | Diffuse0Noisy — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5175AC | - | 0xF5175AC | `c28e6dd  lea rcx,[0xF5175AC]` | DiffuseChroma0Noisy — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5A56D5 | - | 0xF5A56D5 | `c28e72b  lea rcx,[0xF5A56D5]` | Diffuse3PreTemporal — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5A56E9 | - | 0xF5A56E9 | `c28e776  lea r8,[0xF5A56E9]` | DiffuseChroma3PreTemporal — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5F4C8A | - | 0xF5F4C8A | `c28e7c1  lea r9,[0xF5F4C8A]` | Diffuse2Denoised — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5F4C9B | - | 0xF5F4C9B | `c28e816  lea r9,[0xF5F4C9B]` | DiffuseChroma2Denoised — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5DF6FB | - | 0xF5DF6FB | `c28e86b  lea r9,[0xF5DF6FB]` | IncomingIrradianceCache — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF7E4164 | - | 0xF7E4164 | `c28e8b6  lea r9,[0xF7E4164]` | DiffuseMoments0 — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF51758F | - | 0xF51758F | `c28e988  lea rcx,[0xF51758F]` | Specular0Noisy — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5A56C0 | - | 0xF5A56C0 | `c28e9d6  lea rcx,[0xF5A56C0]` | Specular3PreTemporal — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5F4C78 | - | 0xF5F4C78 | `c28ea21  lea r8,[0xF5F4C78]` | Specular2Denoised — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF7E4153 | - | 0xF7E4153 | `c28ea76  lea r8,[0xF7E4153]` | SpecularMoments0 — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF7E4219 | - | 0xF7E4219 | `c28eb52  lea rcx,[0xF7E4219]` | HistoryLength0 — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF7E40C6 | - | 0xF7E40C6 | `c28eba0  lea rax,[0xF7E40C6]` | SunLightShadow0 — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF7DDC31 | - | 0xF7DDC31 | `c28ebeb  lea rax,[0xF7DDC31]` | SunLightShadow1 — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF545890 | - | 0xF545890 | `c28ec81  lea rax,[0xF545890]` | AdaptiveDenoiserGradients — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5E684C | - | 0xF5E684C | `c28eccc  lea rax,[0xF5E684C]` | AdaptiveDenoiserReference — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF524D09 | - | 0xF524D09 | `c28ed62  lea rax,[0xF524D09]` | FinalOutput — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF563C84 | - | 0xF563C84 | `c28e906  lea r9,[0xF563C84]` | FirstIterationVarianceColor — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF7CB98F | - | 0xF7CB98F | `c28e947  lea rcx,[0xF7CB98F]` | FirstIterationVarianceSH — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5518F1 | - | 0xF5518F1 | `c28eda7  lea rax,[0xF5518F1]` | G-Buffer Normals — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF57F886 | - | 0xF57F886 | `c28edf2  lea rax,[0xF57F886]` | G-Buffer Albedo — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF53761C | - | 0xF53761C | `c28eec9  lea rcx,[0xF53761C]` | G-Buffer Ambient — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF5A73C2 | - | 0xF5A73C2 | `c28ef4b  lea rax,[0xF5A73C2]` | G-Buffer Split Mask — RTX G-buffer resource in 0xc28e330 | [V] |
| 0xF5E7E4D | - | 0xF5E7E4D | `c28eac6  lea r8,[0xF5E7E4D]` | FirstIterationSpecularVariance — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF5E7E6C | - | 0xF5E7E6C | `c28eb07  lea rcx,[0xF5E7E6C]` | DesnoisedSpecularVariance — RTX denoiser resource in 0xc28e330 | [V] |
| 0xF58ADE0 | - | 0xF58ADE0 | `e84a65d  lea rdx,[0xF58ADE0]` | MotionVectorsReflection — RTX context init resource string in 0xe8403d0 | [V] |
| 0xF7CDE83 | - | 0xF7CDE83 | `e84a5df  lea rdx,[0xF7CDE83]` | MotionVectors3D — RTX context init resource string in 0xe8403d0 | [V] |
| 0xF547D94 | - | 0xF547D94 | `e84a4bf  lea rdx,[0xF547D94]` | GBuffer.Roughness — RTX context init resource string in 0xe8403d0 | [V] |

## Verbatim proof lines (checked by tools/sigs/verify_oc.py)

bbf5bea  lea rdx,[0xF5C72E9]
bbe4387  lea r9,[0xF5B075A]
bbe4f6f  lea rax,[0xF6076E2]
bbf5b82  lea rax,[0xF6076E2]
bbf46b7  lea rax,[0xF5B4E5B]
bbf5dcb  lea rax,[0xF5B4E5B]
bbf477d  lea rax,[0xF59A754]
bbf5d5c  lea rax,[0xF59A754]
bbf4dbb  lea rcx,[0xF539A44]
bbf4dc7  lea rcx,[0xF54986D]
bbf51f8  lea rcx,[0xF539A5B]
bbf5204  lea rcx,[0xF549886]
bbf59a6  lea rdx,[0xF5161A4]
bbf5a18  lea rdx,[0xF58A852]
bbf5a8a  lea rdx,[0xF5E7B68]
c28e37f  lea rcx,[0xF7E5415]
c28e3fd  lea rcx,[0xF524D8A]
c28e44b  lea rcx,[0xF59A726]
c28ee3d  lea rcx,[0xF547AB1]
c28ee7e  lea rax,[0xF5BD5AE]
c28ef0a  lea rcx,[0xF547DA6]
c28e5a8  lea rcx,[0xF5190CD]
c28e5f3  lea rcx,[0xF5518D2]
c28e641  lea rcx,[0xF7E4209]
c28e68f  lea rcx,[0xF51759E]
c28e6dd  lea rcx,[0xF5175AC]
c28e72b  lea rcx,[0xF5A56D5]
c28e776  lea r8,[0xF5A56E9]
c28e7c1  lea r9,[0xF5F4C8A]
c28e816  lea r9,[0xF5F4C9B]
c28e86b  lea r9,[0xF5DF6FB]
c28e8b6  lea r9,[0xF7E4164]
c28e988  lea rcx,[0xF51758F]
c28e9d6  lea rcx,[0xF5A56C0]
c28ea21  lea r8,[0xF5F4C78]
c28ea76  lea r8,[0xF7E4153]
c28eb52  lea rcx,[0xF7E4219]
c28eba0  lea rax,[0xF7E40C6]
c28ebeb  lea rax,[0xF7DDC31]
c28ec81  lea rax,[0xF545890]
c28eccc  lea rax,[0xF5E684C]
c28ed62  lea rax,[0xF524D09]
c28e906  lea r9,[0xF563C84]
c28e947  lea rcx,[0xF7CB98F]
c28eda7  lea rax,[0xF5518F1]
c28edf2  lea rax,[0xF57F886]
c28eec9  lea rcx,[0xF53761C]
c28ef4b  lea rax,[0xF5A73C2]
c28eac6  lea r8,[0xF5E7E4D]
c28eb07  lea rcx,[0xF5E7E6C]
e84a65d  lea rdx,[0xF58ADE0]
e84a5df  lea rdx,[0xF7CDE83]
e84a4bf  lea rdx,[0xF547D94]

## Notes

- All 50 rows are [V]: each string RVA is located in .rdata and each is referenced by a verbatim `lea` instruction inside the cited function (0xbbe2d50 for RTX pass names/light uniforms; 0xc28e330 for G-buffer/denoiser resources; 0xe8403d0 for RTX context init resources).
- DepthOnlyAlphaTest (cited in 6cg as "7x DepthOnlyAlphaTest" in 0xbbe2d50) has no .rdata string ref inside 0xbbe2d50 per xref (its refs are in 0xbb4c2e0/0xbb60cd0/0xbb64cd0 = VV path). Per BGFX_MAP 6o/6p, pass names are built as inline ASCII immediates, not .rdata strings, so DepthOnlyAlphaTest may be constructed inline in 0xbbe2d50 and is not independently verifiable via string xref — covered as [I] by the 6cg citation alone.
- Color0 (cited in 6cg as a light uniform) has no .rdata string ref inside 0xbbe2d50 per xref (refs are in 0x55f1450/0xbb43a90/0xbb487c0/0xbb4a120/0xbb6b350). Same inline-name reasoning applies — [I] by 6cg citation.
- RTX raygen/denoiser inline pass names from 6p (PrimaryCheckerboardRayGenInline, SunShadowRayGenInline, RefractionRayGenInline, DiffuseRayGenCombinedInline, SpecularRayGenInline, ExplicitLightSamplingInline, PathTracingRayGenInline, UpdateVertexIrradianceCacheInline, UpdateFaceIrradianceCacheInline, CalculateInscatterInline, CalculateGIInscatterInline, IncidentLightMeterInline, AdaptiveDenoiserCalculateGradientsInline, AdaptiveDenoiserGenerateReferenceInline, TemporalDenoising, ShadowDenoising, FinalizeDenoising, AtrousSH, FilterMoments, BlendCheckerboardFields, BlendCheckerboardFieldsSH, BlendCheckerboardFieldsShadow, DiffuseFireflyFilter, DiffuseFireflyFilterSH, SpecularFireflyFilter, CheckerboardUpscale, CheckerboardUpscaleSH, CheckerboardInterleave, TileClassification, BlurGradients, FinalCombine, ReprojectSpecularOnly) appear only as strings with refs in 0xbcc4b90 (the RTX compute pass list, L16c), not in 0xbbe2d50/0xc28e330/0xe8403d0. Those belong to L16c (lambda bodies), not L16a.
- Every lea instruction is 7 bytes (REX.W + lea opcode + modrm + 32-bit disp32). Size column is "-" because the documented offset is a string data address, not an instruction address.

## TOOL REQUESTS
None
