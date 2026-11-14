# Dossier: the six "material pass object" bodies (deferred lighting, deferred shading, water) (1.26.62.01)

Static. Agent passes-materials-visuals, 2026-11-14. Extends docs/functions/pass_bodies.md (which reversed 0xbc2cd20 only). Method: each body listed with tools/sigs/disrange.py, call sequence and displacement multiset diffed, pass-name hashes recomputed (FNV-1 64) and compared with the movabs immediates. Tags: [V] read/verified, [I] inferred, [?] open.

## Result: one template, six instances [V]

All six bodies are `void Pass::execute(this, PassContext* ctx /*rdx*/, const Resources* r /*r8, kept in rdi*/)`. The first 21 calls are identical in sequence in the four deferred bodies:

`5x 0xebce390 (memcpy of the four mat4 + rect + extra into s_ctx->views[viewId])` -> `0xbcc1a30 openScope` -> `0xebce5e0` (marker UniformBuffer write, size 0x7fffffff) -> `2x 0xebce390` (marker string append) -> `0x568db90` (DrawState ctor) -> `0xe86d7f0 bindMaterial` -> `0xbcc3190 applyState` -> `0xbcc2b00 bindVertexStreams` -> `0xbcc2eb0 bindIndexBuffer` -> `0x9d6d0` (std::string assign of the pass name) -> `movabs hash` -> `0xc4bba0 findPass(material+0x2F8/+0x300, hash)` -> (optional `0xbcc1910/0xbcc24f0 applyUniforms`) -> submit -> `3x 0xe935700` (shared_ptr releases) -> `0x568da90` (DrawState dtor) -> `0x655cea0` (scope close).

Fields read from `this` (all six identical, [V]): view rect `+0x88/+0x8C`, mat4 at `+0x08`, `+0x48`, `+0x9C`, `+0xDC` (four mat4, 0x40 each; the second and third pair overlap by design of a {view, proj} x2 layout: +0x08/+0x48 and +0x9C/+0xDC), 16-byte extra at `+0x11C`, byte `+0x98`. Fields read from `Resources r` (rdi) [V]: `+0x10` (AddRef'd shared block, 2 reads), `+0x38` geometry reference (vertex-stream vector + index variant, consumed by 0xbcc2b00/0xbcc2eb0), `+0x90` material (shared_ptr; `[material+0x2F8..+0x300]` is the 24-byte `{hash, ...}` pass table, `+0x310/+0x318` second table), `+0x23C..` 0x58-byte state block.

## Per-body table [V unless tagged]

| body | size | marker (ScreenDraw-style debug marker) | pass FNV-1 hash (verified == FNV1(name)) | submit form | extra Resources reads |
|---|---|---|---|---|---|
| 0xbc2c590 | 0x558 | DoDeferredLighting | 0x289bd38b28795cbc CausticsMultiplierPass | 0xbcc38e0 (submitPass: transform variant 0 = inline mat4) | `+0x23C` only; no uniform block |
| 0xbc2cd20 | 0x5F2 | DoDeferredLighting | 0x993692fcf6fc1544 DirectionalLightingPass | 0xbcc38e0 | `+0x23C,+0x24C,+0x250,+0x254,+0x264,+0x274,+0x283` (state/blend/stencil bytes) |
| 0xbc2d550 | 0x5E4 | DoDeferredShading | 0x48f2445a7c85f35c DiscreteIndirectCombinedLightingPass | 0xbcc3e50 (pointer-form transform, see below) | state block as above plus `+0x1A0` uniform block, `+0x295`, `+0x296` |
| 0xbc2dd20 | 0x5DB | DoDeferredShading | 0xc1772ebae6046ecb SurfaceRadianceUpscalePass | 0xbcc3e50 | state block plus `+0x1A0`, `+0x298` |
| 0xbc2eb50 | 0x54C | WaterExtinction | 0xf4768b63b9171d0b WaterExtinction (name built inline from two movabs: "WaterExt"+"inction") | 0xbcc38e0 | uniforms applied (0xbcc1910/0xbcc24f0) before the pass lookup |
| 0xbc2f4a0 | 0x85B | WaterSurface | 0xa77420c6852a856f WaterSurface | 0xbcc39b0 (submitPass alternative with matrix list = instancing form) | extra string lookups "PointLightShading", "GPUBlockLighting" (2 x 0x50-byte std::string temporaries, 0x56d8e00/0x9b020/0xaa840 string concat) choose a pass variant before 0xc4bba0 |

Submit forms: 0xbcc38e0 and 0xbcc3b90 (alt 0), 0xbcc39b0 (alt 1 list), 0xbcc3e50 (alt 2: argument r9 is a pointer to a mat4; the transform is first copied with 0xebce390 into the Frame matrix cache slot allocated by the atomic increment of `Frame+0xD457C0`, written at `Frame+0x9457C0 + slot*0x40`, `draw.startMatrix = slot` (encoder+0x7C), `numMatrices = 1` (encoder+0x9E word = 1), then `Encoder::submit` 0xbc60740 with occlusion 0xFFFF) [V: 0xbcc3e50 read in full; it calls 0xbcc7ce0 (materialPass -> {u16 program, valid}) first and returns false if invalid]. The sixth argument (`[rsp+0xc0]`) is the depth, 5th `[rsp+0xb0/0xb8]` the material pass reference.

## In/out resources [V in, I out]

- In: the geometry reference at `r+0x38` (fullscreen triangle/quad or light-volume mesh; vertex streams are bound by 0xbcc2b00 into encoder `+0x40..`, index buffer by 0xbcc2eb0), the material at `r+0x90` (names above: DoDeferredLighting / DoDeferredShading / WaterExtinction / WaterSurface), uniform block `r+0x1A0` (shading passes), `r+0x23C` state. Textures (G-buffer, shadow, lightmap) are not read from `r` in these bodies: they travel inside the bound material instance and the scope opened by 0xbcc1a30 from `r+0x00` and the shared block `r+0x08/+0x10` [I].
- Out: the framebuffer of `ctx->view->id`, selected by the frame graph's pass declaration (not by this body) [I].

## What is still open (so these are D1, not D2) [?]

1. Which texture handles each pass actually samples: needs the pass-group builders' resource declaration order (0xbb6b350, 0xbb74040, 0xbb7efb0, 0xbb81880) mapped to `Resources` fields; the bodies only forward `r` to the generic binders.
2. The meaning of `Resources+0x1A0..` uniform block entries per pass (0xbcc1910/0xbcc24f0 read in full not done here).
3. WaterSurface variant selection logic (PointLightShading / GPUBlockLighting strings; 0x2 temporaries) not decoded.
