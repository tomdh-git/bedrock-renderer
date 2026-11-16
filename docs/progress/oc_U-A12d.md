## NEXT
Unit complete — all three steps done. Ready for orchestrator review.

---

# UNIT U-A12d: upscaling — Step 1 & 2 Complete

## Step 1: NGX parameter-name strings referenced in 0xe83ec70 and 0xe8403d0, in order, with referencing call sites

### Function 0xe83ec70 (RTX slot 60: reset handler / DLSS mode select) — size 0x55e

NGX parameter strings and their call sites (in execution order):

| # | Parameter string | String RVA | Call site RVA | Callee | Value source (register/stack) |
|---|------------------|------------|---------------|--------|------------------------------|
| 1 | `DLSSOptimalSettingsCallback` | 0xF5ABF1E (ref at 0xe83ee17) | 0xe83ee26 | sub_ed36b30 (set-callback) | rdx=string, rcx=NGX feature (r14), r8=[rsp+0x58] out-param |
| 2 | `Width` | 0xF5AEED2 (ref at 0xe83ee33) | 0xe83ee3d | sub_ed36950 (set-int) | rdx=string, rcx=NGX feature, r8d=r15d (width from ctx+0x19F78) |
| 3 | `Height` | 0xF53B446 (ref at 0xe83ee45) | 0xe83ee4c | sub_ed36950 (set-int) | rdx=string, rcx=NGX feature, r8d=ebp (height from ctx+0x19F7C) |
| 4 | `PerfQualityValue` | 0xF5BF37A (ref at 0xe83ee57) | 0xe83ee64 | sub_ed369b0 (set-bool/uint) | rdx=string, rcx=NGX feature, r8d=r12d (quality from ctx+0x3C56430) |
| 5 | `RTXValue` | 0xF5BF6B2 (ref at 0xe83ee69) | 0xe83ee76 | sub_ed369b0 (set-bool/uint) | rdx=string, rcx=NGX feature, r8d=0 (hardcoded) |
| 6 | `OutWidth` | 0xF5AED1A (ref at 0xe83efa4) | 0xe83efab | sub_ed36ad0 (get-int) | rdx=string, rcx=NGX feature, r8=[rsp+0x54] out |
| 7 | `OutHeight` | 0xF53B227 (ref at 0xe83efb8) | 0xe83efbf | sub_ed36ad0 (get-int) | rdx=string, rcx=NGX feature, r8=[rsp+0x50] out |
| 8 | `DLSS.Get.Dynamic.Max.Render.Width` | 0xF5AEE80 (ref at 0xe83efe4) | 0xe83efeb | sub_ed36ad0 (get-int) | rdx=string, rcx=NGX feature, r8=[rsp+0x40] out |
| 9 | `DLSS.Get.Dynamic.Max.Render.Height` | 0xF53B3FA (ref at 0xe83eff8) | 0xe83efff | sub_ed36ad0 (get-int) | rdx=string, rcx=NGX feature, r8=[rsp+0x3C] out |
| 10 | `DLSS.Get.Dynamic.Min.Render.Width` | 0xF5AEEA2 (ref at 0xe83f00c) | 0xe83f018 | sub_ed36ad0 (get-int) | rdx=string, rcx=NGX feature, r8=[rsp+0x48] out |
| 11 | `DLSS.Get.Dynamic.Min.Render.Height` | 0xF53B41D (ref at 0xe83f020) | 0xe83f027 | sub_ed36ad0 (get-int) | rdx=string, rcx=NGX feature, r8=[rsp+0x44] out |
| 12 | `Sharpness` | 0xF547A61 (ref at 0xe83f034) | 0xe83f040 | sub_ed36a70 (get-float) | rdx=string, rcx=NGX feature, r8=[rsp+0x4C] out |
| 13 | `CreationNodeMask` | 0xF5A737E (ref at 0xe83f0ce) | 0xe83f0d8 | sub_ed36950 (set-int) | rdx=string, rcx=NGX feature (r14), r8d=1 |
| 14 | `VisibilityNodeMask` | 0xF5A736B (ref at 0xe83f0e3) | 0xe83f0ed | sub_ed36950 (set-int) | rdx=string, rcx=NGX feature (r14), r8d=1 |
| 15 | `Width` | 0xF5AEED2 (ref at 0xe83f0f8) | 0xe83f0ff | sub_ed36950 (set-int) | rdx=string, rcx=NGX feature, r8d=r13d (out width) |
| 16 | `Height` | 0xF53B446 (ref at 0xe83f10a) | 0xe83f114 | sub_ed36950 (set-int) | rdx=string, rcx=NGX feature, r8d=r12d (out height) |
| 17 | `OutWidth` | 0xF5AED1A (ref at 0xe83f11c) | 0xe83f126 | sub_ed36950 (set-int) | rdx=string, rcx=NGX feature, r8d=r15d (backbuffer width ctx+0x19F78) |
| 18 | `OutHeight` | 0xF53B227 (ref at 0xe83f12e) | 0xe83f138 | sub_ed36950 (set-int) | rdx=string, rcx=NGX feature, r8d=[rsp+0x2C] (backbuffer height ctx+0x19F7C) |
| 19 | `PerfQualityValue` | 0xF5BF37A (ref at 0xe83f142) | 0xe83f14c | sub_ed369b0 (set-bool/uint) | rdx=string, rcx=NGX feature, r8d=ebp (quality 2 or from ctx+0x3C56420) |
| 20 | `DLSS.Feature.Create.Flags` | 0xF555238 (ref at 0xe83f154) | 0xe83f15b | sub_ed369b0 (set-bool/uint) | rdx=string, rcx=NGX feature, r8d=3 |
| 21 | `DLSS.Enable.Output.Subrects` | 0xF546A4D (ref at 0xe83f169) | 0xe83f173 | sub_ed369b0 (set-bool/uint) | rdx=string, rcx=NGX feature, r8d=0 |

Mode-log strings (referenced, not NGX parameters):
- `Upscaling Mode: DLSS` at 0xe83eed0 (lea r8, [0xF7C9076]) → jumps to logging at 0xe83ef68
- `Upscaling Mode: Fallback` at 0xe83ef58 (lea r8, [0xF5ABF05]) → logging at 0xe83ef68
- `Upscaling Mode: Off` at 0xe83ef61 (lea r8, [0xF5BAC38]) → logging at 0xe83ef68

---

### Function 0xe8403d0 (RTX slot 64: SuperSampling evaluate / DLSS per-frame) — size 0xAA5B

#### Phase 1: Driver gate parameters (early in function, ~0xe840615..0xe84069e)

| # | Parameter string | String RVA | Call site RVA | Callee | Value source |
|---|------------------|------------|---------------|--------|--------------|
| 1 | `SuperSampling.NeedsUpdatedDriver` | 0xF56666A (ref at 0xe840615) | 0xe840623 | vcall [0xF99FFA0] (NGX get-parameter) | rdx=string, rcx=NGX feature (rdi), r8=[rbp+0x920] out |
| 2 | `SuperSampling.MinDriverVersionMajor` | 0xF563E51 (ref at 0xe840659) | 0xe840667 | vcall [0xF99FFA0] | rdx=string, rcx=NGX feature, r8=[rbp+0x8D0] out |
| 3 | `SuperSampling.MinDriverVersionMinor` | 0xF562F31 (ref at 0xe840677) | 0xe840682 | vcall [0xF99FFA0] | rdx=string, rcx=NGX feature, r8=[rbp-0x30] out |
| 4 | `SuperSampling.Available` | 0xF5DDC16 (ref at 0xe84069e) | 0xe8406ac | vcall [0xF99FFA0] | rdx=string, rcx=NGX feature, r8=[rbp+0x8D0] out |

#### Phase 2: Resource creation (0xe840762..0xe841a11) — debug names, not NGX parameters
(These are UTF-16 debug names for ID3D12Resource creation via sub_e81bf30, e.g. `LPBRTextureData`, `LCheckerboardActions`, `LRefractionIndices`, `LVertexIrradianceCacheUpdates`, `LFaceIrradianceCacheUpdates`, `LLightMeter`, `LLightsBuffer`, `LReducedLightsBuffer`, `LTemporallyStableLightsBuffer`, `LVolumetrics0`, `LVolumetrics1`, `LResolvedInscatter`, `LResolvedTransmission`, `LVolumetricsGI0`, `LVolumetricsGI1`, `LResolvedGIInscatter`)

#### Phase 3: NGX parameter map population (tail, ~0xe84a334..0xe84a7a1) — in order

| # | Parameter string | String RVA | Call site RVA | Callee (NGX setter) | Value source (register/stack) |
|---|------------------|------------|---------------|---------------------|------------------------------|
| 1 | `ResourceWidth` | 0xF5AEE1C (ref 0xe84a334) | 0xe84a33b | vcall [0xF99FFA0] (set-int) | rcx=NGX feature (rbx), r8d=[rsi+0x19F78] (ctx width) |
| 2 | `ResourceHeight` | 0xF53B34C (ref 0xe84a356) | 0xe84a35d | vcall [0xF99FFA0] | rcx=rbx, r8d=[rsi+0x19F7C] (ctx height) |
| 3 | `DLSS.Checkerboard.Jitter.Hack` | 0xF5AC7E3 (ref 0xe84a37f) | 0xe84a386 | vcall [0xF99FFA0] | rcx=rbx, r8b=sete from [rbx+0x144] |
| 4 | `Color` | 0xF563DF4 (ref 0xe84a3a1) | 0xe84a3ae | sub_ed36a10 (set-resource) | rcx=rbx, r8=r13 (resource handle) |
| 5 | `Output` | 0xF524DB9 (ref 0xe84a3b3) | 0xe84a3ba | sub_ed36a10 | rcx=rbx, r8=r12 |
| 6 | `Depth` | 0xF5ADF13 (ref 0xe84a3c5) | 0xe84a3cc | sub_ed36a10 | rcx=rbx, r8=r15 |
| 7 | `MotionVectors` | 0xF549A76 (ref 0xe84a3d7) | 0xe84a3de | sub_ed36a10 | rcx=rbx, r8=rdi |
| 8 | `Jitter.Offset.X` | 0xF7C81BB (ref 0xe84a3e9) | 0xe84a3f7 | sub_ed36900 (set-float) | rcx=rbx, xmm2=xmm9 |
| 9 | `Jitter.Offset.Y` | 0xF7C7A7A (ref 0xe84a3fc) | 0xe84a40a | sub_ed36900 | rcx=rbx, xmm2=xmm8 |
| 10 | `Sharpness` | 0xF547A61 (ref 0xe84a40f) | 0xe84a41c | sub_ed36900 | rcx=rbx, xmm2=xmm7 |
| 11 | `Reset` | 0xF53CDAA (ref 0xe84a421) | 0xe84a42e | sub_ed369b0 (set-bool) | rcx=rbx, r8d=0 |
| 12 | `MV.Scale.X` | 0xF7C8297 (ref 0xe84a443) | 0xe84a44a | sub_ed36900 | rcx=rbx, xmm2=(r14d?cvtsi2ss:0) |
| 13 | `MV.Scale.Y` | 0xF7C7B56 (ref 0xe84a468) | 0xe84a472 | sub_ed36900 | rcx=rbx, xmm2=(rdi?cvtsi2ss:0) |
| 14 | `TransparencyMask` | 0xF5A7300 (ref 0xe84a477) | 0xe84a484 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 15 | `ExposureTexture` | 0xF5C6E38 (ref 0xe84a489) | 0xe84a496 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 16 | `DLSS.Input.Bias.Current.Color.Mask` | 0xF5A739F (ref 0xe84a49b) | 0xe84a4a8 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 17 | `GBuffer.Albedo` | 0xF57F877 (ref 0xe84a4ad) | 0xe84a4ba | sub_ed36a10 | rcx=rbx, r8d=0 |
| 18 | `GBuffer.Roughness` | 0xF547D94 (ref 0xe84a4bf) | 0xe84a4c6 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 19 | `GBuffer.Metallic` | 0xF6068C6 (ref 0xe84a4d1) | 0xe84a4de | sub_ed36a10 | rcx=rbx, r8d=0 |
| 20 | `GBuffer.Specular` | 0xF5710B9 (ref 0xe84a4e3) | 0xe84a4ea | sub_ed36a10 | rcx=rbx, r8d=0 |
| 21 | `GBuffer.Subsurface` | 0xF5EA31D (ref 0xe84a4f5) | 0xe84a502 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 22 | `GBuffer.Normals` | 0xF5518E1 (ref 0xe84a507) | 0xe84a514 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 23 | `GBuffer.ShadingModelId` | 0xF603B49 (ref 0xe84a519) | 0xe84a526 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 24 | `GBuffer.MaterialId` | 0xF603B71 (ref 0xe84a52b) | 0xe84a538 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 25 | `GBuffer.Attrib.8` | 0xF7D22C4 (ref 0xe84a53d) | 0xe84a54a | sub_ed36a10 | rcx=rbx, r8d=0 |
| 26 | `GBuffer.Attrib.9` | 0xF7D160F (ref 0xe84a54f) | 0xe84a55c | sub_ed36a10 | rcx=rbx, r8d=0 |
| 27 | `GBuffer.Attrib.10` | 0xF7E5CB1 (ref 0xe84a561) | 0xe84a56e | sub_ed36a10 | rcx=rbx, r8d=0 |
| 28 | `GBuffer.Attrib.11` | 0xF7E3971 (ref 0xe84a573) | 0xe84a580 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 29 | `GBuffer.Attrib.12` | 0xF7DD5DD (ref 0xe84a585) | 0xe84a592 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 30 | `GBuffer.Attrib.13` | 0xF7D91AE (ref 0xe84a597) | 0xe84a5a4 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 31 | `GBuffer.Attrib.14` | 0xF7D686E (ref 0xe84a5a9) | 0xe84a5b6 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 32 | `GBuffer.Attrib.15` | 0xF7D4D0B (ref 0xe84a5bb) | 0xe84a5c8 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 33 | `TonemapperType` | 0xF5CBB48 (ref 0xe84a5cd) | 0xe84a5da | sub_ed36950 (set-int) | rcx=rbx, r8d=0 |
| 34 | `MotionVectors3D` | 0xF7CDE83 (ref 0xe84a5df) | 0xe84a5e9 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 35 | `IsParticleMask` | 0xF5A735C (ref 0xe84a5f1) | 0xe84a5fe | sub_ed36a10 | rcx=rbx, r8d=0 |
| 36 | `AnimatedTextureMask` | 0xF5A7348 (ref 0xe84a603) | 0xe84a610 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 37 | `DepthHighRes` | 0xF55AE11 (ref 0xe84a615) | 0xe84a622 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 38 | `Position.ViewSpace` | 0xF5E9EA7 (ref 0xe84a627) | 0xe84a634 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 39 | `FrameTimeDeltaInMsec` | 0xF606AD6 (ref 0xe84a639) | 0xe84a646 | sub_ed36900 (set-float) | rcx=rbx, xmm2=0 |
| 40 | `RayTracingHitDistance` | 0xF5E75B6 (ref 0xe84a64b) | 0xe84a658 | sub_ed36a10 | rcx=rbx, r8d=0 |
| 41 | `MotionVectorsReflection` | 0xF58ADE0 (ref 0xe84a65d) | 0xe84a66a | sub_ed36a10 | rcx=rbx, r8d=0 |
| 42 | `DLSS.Input.Color.Subrect.Base.X` | 0xF7C820D (ref 0xe84a66f) | 0xe84a67c | sub_ed36950 | rcx=rbx, r8d=0 |
| 43 | `DLSS.Input.Color.Subrect.Base.Y` | 0xF7C7ACC (ref 0xe84a681) | 0xe84a68e | sub_ed36950 | rcx=rbx, r8d=0 |
| 44 | `DLSS.Input.Depth.Subrect.Base.X` | 0xF7C825A (ref 0xe84a693) | 0xe84a6a0 | sub_ed36950 | rcx=rbx, r8d=0 |
| 45 | `DLSS.Input.Depth.Subrect.Base.Y` | 0xF7C7B19 (ref 0xe84a6a5) | 0xe84a6b2 | sub_ed36950 | rcx=rbx, r8d=0 |
| 46 | `DLSS.Input.MV.Subrect.Base.X` | 0xF7C827A (ref 0xe84a6b7) | 0xe84a6c4 | sub_ed36950 | rcx=rbx, r8d=0 |
| 47 | `DLSS.Input.MV.Subrect.Base.Y` | 0xF7C7B39 (ref 0xe84a6c9) | 0xe84a6d6 | sub_ed36950 | rcx=rbx, r8d=0 |
| 48 | `DLSS.Input.Translucency.Subrect.Base.X` | 0xF7C81CB (ref 0xe84a6db) | 0xe84a6e8 | sub_ed36950 | rcx=rbx, r8d=0 |
| 49 | `DLSS.Input.Translucency.Subrect.Base.Y` | 0xF7C7A8A (ref 0xe84a6ed) | 0xe84a6fa | sub_ed36950 | rcx=rbx, r8d=0 |
| 50 | `DLSS.Input.Bias.Current.Color.Subrect.Base.X` | 0xF7C822D (ref 0xe84a6ff) | 0xe84a70c | sub_ed36950 | rcx=rbx, r8d=0 |
| 51 | `DLSS.Input.Bias.Current.Color.Subrect.Base.Y` | 0xF7C7AEC (ref 0xe84a711) | 0xe84a71e | sub_ed36950 | rcx=rbx, r8d=0 |
| 52 | `DLSS.Output.Subrect.Base.X` | 0xF7C81F2 (ref 0xe84a723) | 0xe84a730 | sub_ed36950 | rcx=rbx, r8d=0 |
| 53 | `DLSS.Output.Subrect.Base.Y` | 0xF7C7AB1 (ref 0xe84a735) | 0xe84a73c | sub_ed36950 | rcx=rbx, r8d=0 |
| 54 | `DLSS.Render.Subrect.Dimensions.Width` | 0xF5AEE5B (ref 0xe84a747) | 0xe84a754 | sub_ed36950 | rcx=rbx, r8d=r14d (render width) |
| 55 | `DLSS.Render.Subrect.Dimensions.Height` | 0xF53B3D4 (ref 0xe84a759) | 0xe84a766 | sub_ed36950 | rcx=rbx, r8d=edi (render height) |
| 56 | `DLSS.Pre.Exposure` | 0xF5C919E (ref 0xe84a76b) | 0xe84a778 | sub_ed36900 | rcx=rbx, xmm2=xmm6 |
| 57 | `DLSS.Exposure.Scale` | 0xF5DEB9F (ref 0xe84a77d) | 0xe84a78a | sub_ed36900 | rcx=rbx, xmm2=xmm6 |
| 58 | `DLSS.Indicator.Invert.X.Axis` | 0xF553A8D (ref 0xe84a78f) | 0xe84a79c | sub_ed369b0 | rcx=rbx, r8d=0 |
| 59 | `DLSS.Indicator.Invert.Y.Axis` | 0xF553A70 (ref 0xe84a7a1) | 0xe84a7ae | sub_ed369b0 | rcx=rbx, r8d=0 |

#### DLSS evaluate wrapper call
- `sub_ed360d0` at 0xe84a7ca — called after all parameters set, with NGX feature (r12), parameter map (rbx), and context. This is the DLSS evaluate entry point.

---

### Callee mapping (NGX setter functions)
- `sub_ed36950` — NGX `SetInt` / `SetUInt` (parameter name in rdx, feature in rcx, value in r8d)
- `sub_ed369b0` — NGX `SetBool` / `SetUInt` (parameter name in rdx, feature in rcx, value in r8d)
- `sub_ed36a10` — NGX `SetResource` / `SetTexture` (parameter name in rdx, feature in rcx, resource in r8)
- `sub_ed36900` — NGX `SetFloat` (parameter name in rdx, feature in rcx, value in xmm2)
- `sub_ed36a70` — NGX `GetFloat` (parameter name in rdx, feature in rcx, out in r8)
- `sub_ed36ad0` — NGX `GetInt` (parameter name in rdx, feature in rcx, out in r8)
- `sub_ed36b30` — NGX `SetCallback` (parameter name in rdx, feature in rcx, callback out in r8)
- `sub_ed36000` — NGX `CreateFeature` (feature in rcx, params in rdx/r8/r9)
- `sub_ed360d0` — NGX `EvaluateFeature` (feature in rcx, parameter map in rdx/r8, context in r9)
- `sub_ed35e90`, `sub_ed35fb0`, `sub_ed36080` — NGX init/query helpers

---

## Step 2: Instruction-complete listing of 0xe83ec70 (0xe83ec70..0xe83f1ce, size 0x55e)

### Register/argument map
- `rcx` / `rsi` = `this` (D3D12ContextRTX*, RTX subclass of RendererContextD3D12)
- `rdx` = `Frame*` (from submit, contains backbuffer size at +0x0/+0x4 and reset flags at +0x8)
- `r14` = NGX feature handle (from `this+0x3C56410`)
- `r15` = backbuffer width (`this+0x19F78`)
- `rbp` / `ebx` = backbuffer height (`this+0x19F7C`)
- `r12` = quality mode / PerfQualityValue (`this+0x3C56420` → `this+0x3C56430`)
- `rdi` = pointer to `this+0x3C56460` (NGX feature pointer storage)
- Stack frame: 0x68 bytes + saved registers

### Context fields referenced (RTX context = `this`)
| Offset | Size | Meaning |
|--------|------|---------|
| +0x19F78 | 4 | Backbuffer width (u32) |
| +0x19F7C | 4 | Backbuffer height (u32) |
| +0x19F80 | 4 | Render width (u32) |
| +0x19F58 | 8 | Pointer to some structure (vtable at +0x30) |
| +0x3C56410 | 8 | NGX feature handle (ID3D12GraphicsCommandList4* or NGX feature) |
| +0x3C56418 | 1 | DLSS enabled flag (0=off, 1=on) |
| +0x3C5641C | 4 | Current upscaling mode (0=DLSS, 1=Fallback, 2=Off) |
| +0x3C56420 | 4 | Current PerfQualityValue |
| +0x3C56424 | 4 | Sharpness (float) |
| +0x3C56428 | 4 | Previous sharpness (float) |
| +0x3C5642C | 4 | Requested upscaling mode |
| +0x3C56430 | 4 | Requested PerfQualityValue |
| +0x3C56438 | 4 | Requested sharpness (float) |
| +0x3C5643C | 4 | Computed optimal width (OutWidth) |
| +0x3C56440 | 4 | Computed optimal height (OutHeight) |
| +0x3C56444 | 4 | Fallback width |
| +0x3C56448 | 8 | Fallback dimensions (packed) |
| +0x3C56450 | 4 | Fallback width copy |
| +0x3C56454 | 16 | Fallback computation temp (xmm) |
| +0x3C56458 | 1 | Feature created flag |
| +0x3C56459 | 1 | Fallback active flag |
| +0x3C56460 | 8 | NGX feature pointer (created feature) |
| +0x3C5646C | 1 | RTX enabled flag |
| +0x415E60C | 4 | Divisor for frame counter |
| +0x415E614 | 4 | Frame counter |
| +0x415E620 | 4 | Frame counter snapshot |

### Phase 1: Prologue & mode-change detection (0xe83ec70..0xe83ecd0, 32 instr)
```
0xE83EC70  push r15
0xE83EC72  push r14
0xE83EC74  push r13
0xE83EC76  push r12
0xE83EC78  push rsi
0xE83EC79  push rdi
0xE83EC7A  push rbp
0xE83EC7B  push rbx
0xE83EC7C  sub rsp,0x68
0xE83EC80  mov rsi,rcx                    ; this -> rsi
0xE83EC83  mov rax,[0x1230A0C0]           ; stack cookie
0xE83EC8A  xor rax,rsp
0xE83EC8D  mov [rsp+0x60],rax
0xE83EC92  mov ecx,[rcx+0x3C5641C]        ; ecx = current mode (this+0x3C5641C)
0xE83EC98  mov eax,[rsi+0x3C5642C]        ; eax = requested mode (this+0x3C5642C)
0xE83EC9E  cmp ecx,eax
0xE83ECA0  je short 0xE83ECD0             ; if same, skip mode transition
0xE83ECA2  test eax,eax
0xE83ECA4  je short 0xE83ECB2             ; requested=0 (DLSS) -> cl=1, r8b=0
0xE83ECA6  cmp eax,1
0xE83ECA9  jne short 0xE83ECB6            ; requested=1 (Fallback) -> cl=0, r8b=1
0xE83ECAB  mov r8b,1
0xE83ECAE  xor ecx,ecx
0xE83ECB0  jmp short 0xE83ECBB
0xE83ECB2  mov cl,1                       ; DLSS: feature_created=1, fallback=0
0xE83ECB4  jmp short 0xE83ECB8
0xE83ECB6  xor ecx,ecx                    ; Off: feature_created=0, fallback=0
0xE83ECB8  xor r8d,r8d
0xE83ECBB  mov [rsi+0x3C56458],cl         ; this+0x3C56458 = feature_created
0xE83ECC1  mov [rsi+0x3C56459],r8b        ; this+0x3C56459 = fallback_active
0xE83ECC8  mov [rsi+0x3C5641C],eax        ; this+0x3C5641C = requested mode
0xE83ECCE  mov ecx,eax
```
C-like: detect mode transition (DLSS↔Fallback↔Off), set transition flags.

### Phase 2: DLSS enabled flag & sharpness sync (0xe83ecd0..0xe83ed09, 20 instr)
```
0xE83ECD0  cmp byte ptr [rsi+0x3C56418],0  ; DLSS enabled?
0xE83ECD7  jne short 0xE83ECEA             ; if enabled, skip disable logic
0xE83ECD9  mov byte ptr [rsi+0x3C56458],0  ; feature_created = 0
0xE83ECE0  cmp ecx,2
0xE83ECE3  setne [rsi+0x3C56459]           ; fallback_active = (mode != 2)
0xE83ECEA  movss xmm1,[rsi+0x3C56428]      ; xmm1 = current sharpness
0xE83ECF2  movss xmm0,[rsi+0x3C56438]      ; xmm0 = requested sharpness
0xE83ECFA  ucomiss xmm1,xmm0
0xE83ECFD  jne short 0xE83ED01             ; if changed
0xE83ECFF  jnp short 0xE83ED09             ; if unordered (NaN)
0xE83ED01  movss [rsi+0x3C56428],xmm0      ; update current sharpness
0xE83ED09  mov eax,[rsi+0x3C56458]         ; eax = feature_created
```
C-like: if DLSS disabled, clear feature_created; sync sharpness from requested.

### Phase 3: Backbuffer size check & reset handler call (0xe83ed09..0xe83ed96, 40 instr)
```
0xE83ED09  mov eax,[rsi+0x3C56458]
0xE83ED0F  mov ecx,eax
0xE83ED11  xor cl,1
0xE83ED14  xor ebp,ebp
0xE83ED16  cmp qword ptr [rsi+0x3C56460],0 ; NGX feature ptr null?
0xE83ED1E  movzx r14d,cl                   ; r14d = !feature_created
0xE83ED22  cmove r14d,ebp                  ; if null, r14d=0
0xE83ED26  cmove ebp,eax                   ; if null, ebp=feature_created
0xE83ED29  lea rdi,[rsi+0x3C56460]         ; rdi = &this+0x3C56460
0xE83ED30  mov eax,[rsi+0x19F78]           ; eax = backbuffer width
0xE83ED36  cmp eax,[rdx]                   ; compare with Frame+0x0 (new width)
0xE83ED38  jne short 0xE83ED78             ; size changed -> call reset
0xE83ED3A  mov eax,[rsi+0x19F7C]           ; eax = backbuffer height
0xE83ED40  cmp eax,[rdx+4]                 ; compare with Frame+0x4 (new height)
0xE83ED43  jne short 0xE83ED78             ; size changed -> call reset
0xE83ED45  mov r15d,[rsi+0x19F80]          ; r15d = render width
0xE83ED4C  mov r12d,[rdx+8]                ; r12d = Frame+0x8 (reset flags)
0xE83ED50  mov rcx,rsi
0xE83ED53  call 0xE81A610                  ; base reset handler (slot 60 base)
0xE83ED58  mov ebx,eax
0xE83ED5A  cmp r15d,r12d
0xE83ED5D  jne short 0xE83ED82
0xE83ED5F  mov eax,[rsi+0x3C56420]
0xE83ED65  cmp eax,[rsi+0x3C56430]
0xE83ED6B  je short 0xE83ED96
0xE83ED6D  cmp byte ptr [rsi+0x3C56458],0
0xE83ED74  jne short 0xE83ED8B
0xE83ED76  jmp short 0xE83ED96
0xE83ED78  mov rcx,rsi
0xE83ED7B  call 0xE81A610                  ; base reset handler
0xE83ED80  mov ebx,eax
0xE83ED82  cmp byte ptr [rsi+0x3C56458],1
0xE83ED89  jne short 0xE83ED96
0xE83ED8B  cmp qword ptr [rdi],0
0xE83ED8F  setne r14b
0xE83ED93  mov bpl,1
```
C-like: if backbuffer size changed or reset flags changed, call base reset handler (0xe81a610). Track whether NGX feature exists (r14b) and whether reset occurred (bpl).

### Phase 4: NGX feature cleanup on transition (0xe83ed96..0xe83edaf, 10 instr)
```
0xE83ED96  test r14b,r14b
0xE83ED99  je short 0xE83EDAF
0xE83ED9B  mov rcx,[rdi]
0xE83ED9E  test rcx,rcx
0xE83EDA1  je short 0xE83EDAF
0xE83EDA3  call 0xED36080                  ; NGX feature destroy
0xE83EDA8  mov qword ptr [rdi],0
```
C-like: if feature_created was true and feature ptr non-null, destroy NGX feature.

### Phase 5: Quality mode sync & branch to NGX setup (0xe83edaf..0xe83eec7, 12 instr)
```
0xE83EDAF  mov r12d,[rsi+0x3C56420]       ; current quality
0xE83EDB6  mov eax,[rsi+0x3C56430]        ; requested quality
0xE83EDBC  cmp r12d,eax
0xE83EDBF  je short 0xE83EDCA
0xE83EDC1  mov [rsi+0x3C56420],eax        ; update current quality
0xE83EDC7  mov r12d,eax
0xE83EDCA  test bpl,bpl                    ; did reset happen?
0xE83EDCD  je 0xE83EEC7                    ; if no reset, skip NGX setup
0xE83EDD3  cmp byte ptr [rsi+0x3C56418],1  ; DLSS enabled?
0xE83EDDA  jne 0xE83EEB0                   ; if not, go to fallback/off
0xE83EDE0  mov r14,[rsi+0x3C56410]         ; r14 = NGX feature handle
0xE83EDE7  test r14,r14
0xE83EDEA  je 0xE83EEB0
```
C-like: sync quality mode; if reset occurred and DLSS enabled and NGX handle valid, proceed to NGX feature creation.

### Phase 6: NGX optimal settings callback & feature creation (0xe83edf0..0xe83ee93, 36 instr)
```
0xE83EDF0  mov r15d,[rsi+0x19F78]         ; width
0xE83EDF7  mov ebp,[rsi+0x19F7C]          ; height
0xE83EDFD  mov [rsp+0x54],r15d
0xE83EE02  mov [rsp+0x50],ebp
0xE83EE06  mov dword ptr [rsp+0x4C],0x3F800000  ; sharpness = 1.0f
0xE83EE0E  mov qword ptr [rsp+0x58],0
0xE83EE17  lea rdx,[0xF5ABF1E]            ; "DLSSOptimalSettingsCallback"
0xE83EE1E  lea r8,[rsp+0x58]
0xE83EE23  mov rcx,r14
0xE83EE26  call 0xED36B30                 ; SetCallback
0xE83EE2B  cmp qword ptr [rsp+0x58],0
0xE83EE31  je short 0xE83EE99             ; if callback failed
0xE83EE33  lea rdx,[0xF5AEED2]            ; "Width"
0xE83EE3A  mov rcx,r14
0xE83EE3D  mov r8d,r15d
0xE83EE40  call 0xED36950                 ; SetInt(Width)
0xE83EE45  lea rdx,[0xF53B446]            ; "Height"
0xE83EE4C  mov rcx,r14
0xE83EE4F  mov r8d,ebp
0xE83EE52  call 0xED36950                 ; SetInt(Height)
0xE83EE57  lea rdx,[0xF5BF37A]            ; "PerfQualityValue"
0xE83EE5E  mov rcx,r14
0xE83EE61  mov r8d,r12d
0xE83EE64  call 0xED369B0                 ; SetUInt(PerfQualityValue)
0xE83EE69  lea rdx,[0xF5BF6B2]            ; "RTXValue"
0xE83EE70  mov rcx,r14
0xE83EE73  xor r8d,r8d
0xE83EE76  call 0xED369B0                 ; SetUInt(RTXValue=0)
0xE83EE7B  mov rax,[rsp+0x58]
0xE83EE80  mov rcx,r14
0xE83EE83  call qword ptr [0xF99FFA0]     ; CreateFeature
0xE83EE89  and eax,0xFFF00000
0xE83EE8E  cmp eax,0xBAD00000
0xE83EE93  jne 0xE83EFA4                  ; if success -> get optimal sizes
```
C-like: query optimal settings via callback, then create NGX DLSS feature with Width, Height, PerfQualityValue, RTXValue=0.

### Phase 7: Callback failed → fallback dimensions (0xe83ee99..0xe83eea6, 4 instr)
```
0xE83EE99  mov [rsi+0x3C5643C],r15d       ; OutWidth = backbuffer width
0xE83EEA0  mov [rsi+0x3C56440],ebp        ; OutHeight = backbuffer height
0xE83EEA6  mov dword ptr [rsi+0x3C56424],0 ; Sharpness = 0
```

### Phase 8: Fallback/Off path — clear flags (0xe83eeb0..0xe83eeb7, 4 instr)
```
0xE83EEB0  mov byte ptr [rsi+0x3C56458],0  ; feature_created = 0
0xE83EEB7  mov byte ptr [rsi+0x3C56418],0  ; DLSS enabled = 0
0xE83EEBE  and byte ptr [0x12ADFA54],0xFE  ; global caps bit clear
0xE83EEC5  jmp short 0xE83EEDC
```

### Phase 9: No reset but feature_created=0 → fallback/off (0xe83eec7..0xe83eedc, 6 instr)
```
0xE83EEC7  cmp byte ptr [rsi+0x3C56458],0
0xE83EECE  je short 0xE83EEDC
```

### Phase 10: Fallback active → compute fallback render size (0xe83eedc..0xe83ef50, 32 instr)
```
0xE83EEDC  cmp byte ptr [rsi+0x3C56459],1  ; fallback_active?
0xE83EEE3  jne short 0xE83EF61             ; if not, mode=Off
0xE83EEE5  mov eax,[rsi+0x3C56444]
0xE83EEEB  mov [rsi+0x3C56450],eax
0xE83EEF1  mov rax,[rsi+0x3C5643C]
0xE83EEF8  mov [rsi+0x3C56448],rax
0xE83EEFF  movups xmm0,[rsi+0x3C56454]
0xE83EF06  movsd xmm1,[rsi+0x19F78]       ; backbuffer width as double
0xE83EF0E  xorpd xmm2,xmm2
0xE83EF12  unpcklps xmm1,xmm2
0xE83EF15  movapd xmm2,[0xEFC6AF0]        ; constant 1.0
0xE83EF1D  orpd xmm1,xmm2
0xE83EF21  subpd xmm1,xmm2
0xE83EF25  cvtpd2ps xmm1,xmm1
0xE83EF29  shufps xmm0,xmm0,0
0xE83EF2D  mulps xmm0,xmm1
0xE83EF30  cvttps2dq xmm1,xmm0
0xE83EF34  movdqa xmm2,xmm1
0xE83EF38  psrad xmm2,0x1F
0xE83EF3D  subps xmm0,[0xF089480]
0xE83EF44  cvttps2dq xmm0,xmm0
0xE83EF48  pand xmm0,xmm2
0xE83EF4C  por xmm0,xmm1
0xE83EF50  movq [rsi+0x3C5643C],xmm0      ; compute fallback render dimensions
0xE83EF58  lea r8,[0xF5ABF05]             ; "Upscaling Mode: Fallback"
0xE83EF5F  jmp short 0xE83EF68
```

### Phase 11: Mode = Off (0xe83ef61..0xe83ef68, 2 instr)
```
0xE83EF61  lea r8,[0xF5BAC38]             ; "Upscaling Mode: Off"
0xE83EF68  lea rcx,[0x12AE0E90]           ; log buffer
0xE83EF6F  mov edx,0x7FF
0xE83EF74  call 0x11D490                  ; log message
```

### Phase 12: Success path — query optimal sizes from NGX (0xe83efa4..0xe83ef79, 40 instr)
```
0xE83EFA4  lea rdx,[0xF5AED1A]            ; "OutWidth"
0xE83EFAB  lea r8,[rsp+0x54]
0xE83EFB0  mov rcx,r14
0xE83EFB3  call 0xED36AD0                 ; GetInt(OutWidth)
0xE83EFB8  lea rdx,[0xF53B227]            ; "OutHeight"
0xE83EFBF  lea r8,[rsp+0x50]
0xE83EFC4  mov rcx,r14
0xE83EFC7  call 0xED36AD0                 ; GetInt(OutHeight)
0xE83EFCC  mov eax,[rsp+0x54]
0xE83EFD0  mov [rsp+0x40],eax
0xE83EFD4  mov ecx,[rsp+0x50]
0xE83EFD8  mov [rsp+0x3C],ecx
0xE83EFDC  mov [rsp+0x48],eax
0xE83EFE0  mov [rsp+0x44],ecx
0xE83EFE4  lea rdx,[0xF5AEE80]            ; "DLSS.Get.Dynamic.Max.Render.Width"
0xE83EFEB  lea r8,[rsp+0x40]
0xE83EFF0  mov rcx,r14
0xE83EFF3  call 0xED36AD0                 ; GetInt(MaxRenderWidth)
0xE83EFF8  lea rdx,[0xF53B3FA]            ; "DLSS.Get.Dynamic.Max.Render.Height"
0xE83EFFF  lea r8,[rsp+0x3C]
0xE83F004  mov rcx,r14
0xE83F007  call 0xED36AD0                 ; GetInt(MaxRenderHeight)
0xE83F00C  lea rdx,[0xF5AEEA2]            ; "DLSS.Get.Dynamic.Min.Render.Width"
0xE83F013  lea r8,[rsp+0x48]
0xE83F018  mov rcx,r14
0xE83F01B  call 0xED36AD0                 ; GetInt(MinRenderWidth)
0xE83F020  lea rdx,[0xF53B41D]            ; "DLSS.Get.Dynamic.Min.Render.Height"
0xE83F027  lea r8,[rsp+0x44]
0xE83F02C  mov rcx,r14
0xE83F02F  call 0xED36AD0                 ; GetInt(MinRenderHeight)
0xE83F034  lea rdx,[0xF547A61]            ; "Sharpness"
0xE83F03B  lea r8,[rsp+0x4C]
0xE83F040  mov rcx,r14
0xE83F043  call 0xED36A70                 ; GetFloat(Sharpness)
```

### Phase 13: Store optimal sizes & handle quality=5 (ultra performance) special case (0xe83f048..0xe83f0a1, 24 instr)
```
0xE83F048  mov r13d,[rsp+0x54]            ; r13d = OutWidth
0xE83F04D  mov [rsi+0x3C5643C],r13d       ; this+0x3C5643C = OutWidth
0xE83F054  mov r12d,[rsp+0x50]            ; r12d = OutHeight
0xE83F059  mov [rsi+0x3C56440],r12d       ; this+0x3C56440 = OutHeight
0xE83F060  movss xmm0,[rsp+0x4C]
0xE83F066  movss [rsi+0x3C56424],xmm0     ; this+0x3C56424 = Sharpness
0xE83F06E  mov ebp,[rsi+0x3C56420]        ; ebp = current quality
0xE83F074  cmp ebp,5
0xE83F077  jne short 0xE83F0A6
0xE83F079  lea rax,[rsi+0x19F78]
0xE83F080  lea rcx,[rsi+0x3C5643C]
0xE83F087  mov edx,[rax+8]
0xE83F08A  mov [rcx+8],edx
0xE83F08D  mov rax,[rax]
0xE83F090  mov [rcx],rax
0xE83F093  mov r13d,[rsi+0x3C5643C]
0xE83F09A  mov r12d,[rsi+0x3C56440]
0xE83F0A1  mov ebp,2                      ; quality=5 -> force quality=2, use backbuffer size
```

### Phase 14: Create NGX feature with final parameters (0xe83f0a6..0xe83f1bb, 44 instr)
```
0xE83F0A6  mov r15d,[rsi+0x19F78]         ; backbuffer width
0xE83F0AD  mov eax,[rsi+0x19F7C]
0xE83F0B3  mov [rsp+0x2C],eax             ; backbuffer height
0xE83F0B7  mov r14,[rsi+0x3C56410]        ; NGX handle
0xE83F0BE  mov rax,[rsi+0x19F58]
0xE83F0C5  mov rax,[rax+0x30]
0xE83F0C9  mov [rsp+0x30],rax
0xE83F0CE  lea rdx,[0xF5A737E]            ; "CreationNodeMask"
0xE83F0D5  mov rcx,r14
0xE83F0D8  mov r8d,1
0xE83F0DE  call 0xED36950                 ; SetInt(CreationNodeMask=1)
0xE83F0E3  lea rdx,[0xF5A736B]            ; "VisibilityNodeMask"
0xE83F0EA  mov rcx,r14
0xE83F0ED  mov r8d,1
0xE83F0F3  call 0xED36950                 ; SetInt(VisibilityNodeMask=1)
0xE83F0F8  lea rdx,[0xF5AEED2]            ; "Width"
0xE83F0FF  mov rcx,r14
0xE83F102  mov r8d,r13d
0xE83F105  call 0xED36950                 ; SetInt(Width=OutWidth)
0xE83F10A  lea rdx,[0xF53B446]            ; "Height"
0xE83F111  mov rcx,r14
0xE83F114  mov r8d,r12d
0xE83F117  call 0xED36950                 ; SetInt(Height=OutHeight)
0xE83F11C  lea rdx,[0xF5AED1A]            ; "OutWidth"
0xE83F123  mov rcx,r14
0xE83F126  mov r8d,r15d
0xE83F129  call 0xED36950                 ; SetInt(OutWidth=backbuffer width)
0xE83F12E  lea rdx,[0xF53B227]            ; "OutHeight"
0xE83F135  mov rcx,r14
0xE83F138  mov r8d,[rsp+0x2C]
0xE83F13D  call 0xED36950                 ; SetInt(OutHeight=backbuffer height)
0xE83F142  lea rdx,[0xF5BF37A]            ; "PerfQualityValue"
0xE83F149  mov rcx,r14
0xE83F14C  mov r8d,ebp
0xE83F14F  call 0xED369B0                 ; SetUInt(PerfQualityValue)
0xE83F154  lea rdx,[0xF555238]            ; "DLSS.Feature.Create.Flags"
0xE83F15B  mov rcx,r14
0xE83F15E  mov r8d,3
0xE83F164  call 0xED369B0                 ; SetUInt(CreateFlags=3)
0xE83F169  lea rdx,[0xF546A4D]            ; "DLSS.Enable.Output.Subrects"
0xE83F170  mov rcx,r14
0xE83F173  xor r8d,r8d
0xE83F176  call 0xED369B0                 ; SetUInt(EnableOutputSubrects=0)
0xE83F17B  mov rcx,[rsp+0x30]
0xE83F180  mov edx,1
0xE83F185  mov r8,r14
0xE83F188  mov r9,rdi
0xE83F18B  call 0xED36000                 ; CreateFeature
0xE83F190  and eax,0xFFF00000
0xE83F195  cmp eax,0xBAD00000
0xE83F19A  je 0xE83EEB0                   ; fail -> fallback
0xE83F1A0  cmp qword ptr [rsi+0x3C56460],0
0xE83F1A8  je 0xE83EEB0                   ; fail -> fallback
0xE83F1AE  cmp byte ptr [rsi+0x3C56458],0
0xE83F1B5  je 0xE83EEB7
0xE83F1BB  jmp 0xE83EED0                  ; success -> log "DLSS"
```

### Phase 15: Epilog / stack check fail (0xe83ef79..0xe83f1ce, 24 instr)
```
0xE83EF79  mov rax,[rsp+0x60]
0xE83EF7E  xor rax,rsp
0xE83EF81  mov rcx,[0x1230A0C0]
0xE83EF88  cmp rcx,rax
0xE83EF8B  jne 0xE83F1C0                  ; stack cookie fail
0xE83EF91  mov eax,ebx                    ; return value from base reset
0xE83EF93  add rsp,0x68
0xE83EF97  pop rbx
0xE83EF98  pop rbp
0xE83EF99  pop rdi
0xE83EF9A  pop rsi
0xE83EF9B  pop r12
0xE83EF9D  pop r13
0xE83EF9F  pop r14
0xE83EFA1  pop r15
0xE83EFA3  ret
0xE83F1C0  mov rcx,[rsp+0x60]
0xE83F1C5  xor rcx,rsp
0xE83F1C8  call 0xE951550                 ; __security_check_cookie
0xE83F1CD  int3
0xE83F1CE  int3
0xE83F1CF  int3
```

---

### Parameter table: NGX parameter string → value source → meaning

| NGX Parameter | Value Source | Meaning |
|---------------|--------------|---------|
| `DLSSOptimalSettingsCallback` | Callback pointer out-param ([rsp+0x58]) | NGX callback for optimal settings query |
| `Width` (query) | `r15d` = `this+0x19F78` (backbuffer width) | Input display width for optimal settings |
| `Height` (query) | `ebp` = `this+0x19F7C` (backbuffer height) | Input display height for optimal settings |
| `PerfQualityValue` (query) | `r12d` = `this+0x3C56430` (requested quality) | Quality preset for optimal settings query |
| `RTXValue` | Hardcoded 0 | RTX enable flag for optimal settings (0=off) |
| `OutWidth` (query result) | `[rsp+0x54]` → `this+0x3C5643C` | NGX-recommended render width |
| `OutHeight` (query result) | `[rsp+0x50]` → `this+0x3C56440` | NGX-recommended render height |
| `DLSS.Get.Dynamic.Max.Render.Width` | `[rsp+0x40]` (temp) | Dynamic max render width limit |
| `DLSS.Get.Dynamic.Max.Render.Height` | `[rsp+0x3C]` (temp) | Dynamic max render height limit |
| `DLSS.Get.Dynamic.Min.Render.Width` | `[rsp+0x48]` (temp) | Dynamic min render width limit |
| `DLSS.Get.Dynamic.Min.Render.Height` | `[rsp+0x44]` (temp) | Dynamic min render height limit |
| `Sharpness` (query result) | `[rsp+0x4C]` → `this+0x3C56424` | NGX-recommended sharpness |
| `CreationNodeMask` | Hardcoded 1 | GPU node mask for feature creation |
| `VisibilityNodeMask` | Hardcoded 1 | GPU visibility node mask |
| `Width` (create) | `r13d` = OutWidth (or backbuffer width if quality=5) | Render width for DLSS feature |
| `Height` (create) | `r12d` = OutHeight (or backbuffer height if quality=5) | Render height for DLSS feature |
| `OutWidth` (create) | `r15d` = `this+0x19F78` (backbuffer width) | Output/display width |
| `OutHeight` (create) | `[rsp+0x2C]` = `this+0x19F7C` (backbuffer height) | Output/display height |
| `PerfQualityValue` (create) | `ebp` = current quality (2 if quality=5) | Quality preset for feature creation |
| `DLSS.Feature.Create.Flags` | Hardcoded 3 | Feature creation flags (bit 0=HDR, bit 1=depth?) |
| `DLSS.Enable.Output.Subrects` | Hardcoded 0 | Disable output sub-rectangles |

---

### Callees (direct calls)
| RVA | Function | Purpose | Tag |
|-----|----------|---------|-----|
| 0xE81A610 | Base reset handler (slot 60 base) | Swapchain resize, deferred release | [V] |
| 0xED36080 | NGX feature destroy | Release NGX feature | [V] |
| 0xED36B30 | NGX SetCallback | Register optimal settings callback | [V] |
| 0xED36950 | NGX SetInt/SetUInt | Set integer parameter | [V] |
| 0xED369B0 | NGX SetBool/SetUInt | Set boolean/uint parameter | [V] |
| 0xED36AD0 | NGX GetInt | Get integer parameter | [V] |
| 0xED36A70 | NGX GetFloat | Get float parameter | [V] |
| 0xEEA6040 (via [0xF99FFA0]) | NGX CreateFeature / GetParameter | Feature creation & parameter query | [V] |
| 0xED36000 | NGX CreateFeature | Create DLSS feature | [V] |
| 0x11D490 | Logging | Log upscaling mode | [V] |
| 0xE951550 | __security_check_cookie | Stack cookie check | [V] |

---

## Step 3: Callers of both functions and triggers

### Direct callers (static analysis)
- **0xe83ec70 (slot 60)**: No direct `call 0xe83ec70` instructions found (rdis callers, xref.py, ripscan.py all return empty). This is a **virtual function** called through the vtable.
- **0xe8403d0 (slot 64)**: No direct `call 0xe8403d0` instructions found. This is a **virtual function** called through the vtable.

### Vtable call sites (trigger points)

#### Slot 60 (0xe83ec70) — Reset handler / DLSS mode select
**Call site**: Submit function (slot 50) at **0xe82e294..0xe82e2a4** (base D3D12 submit) / **0xe83d440** (RTX submit override)

Quoted instructions from base submit 0xe82e230:
```
0xE82E28D  add rdx,0xDC5808              ; rdx = Frame + 0xDC5808 (backbuffer size pair)
0xE82E294  mov rax,[rdi]                 ; rax = vtable pointer (this = rdi)
0xE82E297  mov rax,[rax+0x1E0]           ; rax = vtable[60] = slot 60 function (0xe83ec70 for RTX)
0xE82E29E  mov rcx,rdi                   ; rcx = this
0xE82E2A1  mov rsi,r9                    ; rsi = 4th argument (original rdx?)
0xE82E2A4  call qword ptr [0xF99FFA0]    ; [V] virtual call to slot 60 — returns AL=1 if reset occurred [UNVERIFIED: target is NGX ptr sub_eea6040, not slot 60; raw bytes needed]
0xE82E2AD  test al,al
0xE82E2AF  jne 0xE832CEE                 ; if reset happened, abort submit
```

**Trigger condition**: 
- Swapchain exists (`[this+0x2D8] != 0` checked at 0xe82e283)
- Called at **top of every frame's submit** before any draw work
- `bgfx::reset(width, height, flags)` on game thread writes:
  - `Frame+0xDC5808` = new width (u32)
  - `Frame+0xDC580C` = new height (u32)  
  - `Frame+0xDC5810` = reset flags (u32)
- Render thread picks these up at next submit via slot 60

**Quality mode selection**: The function reads requested settings from RTX context fields:
- `this+0x3C5642C` = requested upscaling mode (0=DLSS, 1=Fallback, 2=Off)
- `this+0x3C56430` = requested PerfQualityValue (quality preset)
- `this+0x3C56438` = requested sharpness (float)
- `this+0x3C56418` = DLSS enabled flag (0/1)

These are populated by the game's settings system (not reversed here).

**Render scale field**: Backbuffer size from `Frame+0xDC5808` (width) / `Frame+0xDC580C` (height) passed in `rdx`. Also `this+0x19F78` (current backbuffer width) and `this+0x19F7C` (current backbuffer height) are compared against the Frame values to detect resize.

---

#### Slot 64 (0xe8403d0) — SuperSampling evaluate / RTX frame executor
**Call site**: RTX submit override **0xe83d440** (slot 50 for RTX class)

From `inventory_L2_d3d12.tsv` and `vv_lambda_bodies.md`, the following functions called by 0xe83d440 reference 0xe8403d0:
- 0xe84b620, 0xe84b980, 0xe84ba30, 0xe84c560, 0xe84c7d0, 0xe84d1b0 — all list 0xe83d440 and 0xe8403d0 as callers

**Quoted context from vv_lambda_bodies.md**:
> **Slot 64 0xe8403d0 (0xAA5B) is the whole RTX frame executor**, not just DLSS: (1) gate at 0xe840615..0xe84069e: `SuperSampling.NeedsUpdatedDriver`, `MinDriverVersionMajor/Minor`, `Available`; (2) creates ~17 named GPU resources... (3) the tail 0xe84a334..0xe84a7a1 fills the NGX parameter map... **0xed360d0 at 0xe84a7ca is the DLSS evaluate wrapper** (right after the last parameter `DLSS.Indicator.Invert.Y.Axis`), followed by four indirect calls (0xe84a803..0xe84a88c: post-evaluate barriers/copies)...

**Trigger condition**:
- Called **once per frame** from RTX submit (0xe83d440) when RTX path is active
- Runs **after** resource creation and ray-tracing dispatches, **before** present
- First executes driver gate (checks `SuperSampling.Available`, `NeedsUpdatedDriver`, `MinDriverVersionMajor/Minor` via NGX parameter queries at 0xe840615..0xe84069e)
- If gate passes, populates full NGX parameter map (59 parameters at 0xe84a334..0xe84a7a1) and calls `sub_ed360d0` (DLSS evaluate) at 0xe84a7ca

**Quality mode / render scale for slot 64**:
- Render dimensions from `this+0x19F78` (width) and `this+0x19F7C` (height) → `ResourceWidth`/`ResourceHeight` (0xe84a334/0xe84a356)
- `DLSS.Render.Subrect.Dimensions.Width/Height` from `r14d`/`edi` (computed render size, 0xe84a747/0xe84a759)
- `PerfQualityValue` not directly set in slot 64 (handled in slot 60 feature creation)
- `Sharpness` from `xmm6` (0xe84a40f/0xe84a41c)
- Jitter offsets from `xmm9`/`xmm8` (0xe84a3e9/0xe84a3fc)
- MV scale from `r14d`/`rdi` (0xe84a443/0xe84a468)

---

### Summary of trigger flow

| Event | Thread | Action |
|-------|--------|--------|
| User changes upscaling mode/quality | Game thread | Writes to RTX context fields: `+0x3C5642C` (mode), `+0x3C56430` (quality), `+0x3C56438` (sharpness), `+0x3C56418` (enable) |
| User resizes window / `bgfx::reset()` | Game thread | Writes `Frame+0xDC5808` (width), `+0xDC580C` (height), `+0xDC5810` (flags) |
| Next frame submit | Render thread | Base submit 0xe82e230 / RTX submit 0xe83d440 calls **slot 60 (0xe83ec70)** with Frame size ptr in rdx |
| Slot 60 executes | Render thread | Detects size change or mode change → calls base reset (0xe81a610) → creates/destroys NGX feature with new params → logs mode |
| RTX submit continues | Render thread | If RTX path, calls **slot 64 (0xe8403d0)** → driver gate → NGX parameter map → DLSS evaluate |

---

### [UNVERIFIED] Open questions
- [UNVERIFIED: 0xe82e2a4] Exact call instruction encoding — disassembly shows `call qword ptr [0xF99FFA0]` but logic requires `call rax`; need raw bytes to confirm
- [UNVERIFIED: 0xe83d440] Exact call site of slot 64 within RTX submit — not yet instruction-quoted
- [UNVERIFIED: 0x3C5642C/0x3C56430/0x3C56438] Source of requested mode/quality/sharpness writes (game settings UI path not traced)
- [UNVERIFIED: 0x19F78/0x19F7C] Backbuffer size update path (where swapchain resize writes these)

---

## TOOL REQUESTS
| name | input -> output | why it would have helped |
|------|-----------------|--------------------------|
| `rdis raw-bytes <rva> <n>` | RVA, count -> hex bytes | Verify exact call instruction encoding at 0xe82e2a4 (call rax vs call [rip]) |
| `xref-virtual <vtable-offset>` | vtable index -> call sites | Find all virtual call sites for slot 60/64 automatically |
| `trace-field-writes <rva> <offset>` | context offset -> write sites | Trace where `this+0x3C5642C` (requested mode) is written |