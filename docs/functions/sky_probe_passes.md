# Sky probe / IBLSyncPoint passes (L11d), 1.26.62.01

Tags: [V] verified in disassembly/hash computation, [I] inferred, [?] unknown.

## Names and hashes (FNV-1 64, computed [V])
- SkyProbeDeferredShading = 0xeec3d36083d95107 (pass-group marker)
- DoSkyProbeDeferredShading = 0xbc1a5cb2508e3fd6 (the pass)
- ForwardPBRTransparentSkyProbe = 0x4ecd376056131add
- IBLSyncPoint = 0x463a4116e7586005
- NothingTask = 0x9204c57f39a196b7 (task kind used by IBLSyncPoint)

## IBLSyncPoint [V]
- Declared in the 0x55f1450 builder around 0x562be6c through helper 0x568ad40 with the NothingTask hash.
- Closure vtable 0xf25c0a0, slot-2 body 0x56aeeb0 (size 0x123). It only sets up the view: rect plus four mat4 copies into the s_ctx views. No draw, no material. It is a pure ordering/sync node (dependency barrier between the IBL producers and consumers) [I for the "ordering" purpose].

## Sky probe builder 0x56a06a0 (size 0x4b94, called from 0x55f1450) [V]
- Declares SkyProbeDeferredShading (DoDeferredShading marker, pass DoSkyProbeDeferredShading) and ForwardPBRTransparentSkyProbe.
- Closures: pass object vtable 0xf25bf30 (execute body 0x56ae230, size 0x545); fn vtable 0xf25bf10 (body 0x56adf40); generic draw-list pairs 0xf25c020 / 0xf25c050 (0x5688f70 / 0x568cd70 -> 0x568cd90).
- Uniforms/textures named: SkyProbeUVFadeParameters, ClampViewVectors, Color0, ColorMetalness, Normal, EmissiveAmbientLinearRoughness, SceneDepth, CurrentFace (CurrentFace: the probe renders per cube face).

## Body 0x56ae230 (standard material-pass template) [V]
scope 0xbcc1a30 -> DrawState 0x568db90 -> bindMaterial 0xe86d7f0 -> applyState 0xbcc3190 -> uniforms 0xbcc1910/0xbcc24f0 -> geometry 0xbcc2b00/0xbcc2eb0 -> findPass 0xc4bba0 with hash immediate 0xb2525e19c6e17c4b (at 0x56ae5c9) -> submitPass 0xbcc38e0. Other callees: 0x9d6d0, 0x568da90, 0x655cea0.
The hash 0xb2525e19c6e17c4b is the material pass name looked up in the sky-probe deferred-shading material (see bcc7ce0.md / material_lookup_chain.md for how a pass+variant is selected).

## Not covered
- The shader source of the probe material and RT (ray tracing) lighting: RT passes are in vv_rtx_pass_table.md and vv_lambda_bodies.md (M1e agent).
