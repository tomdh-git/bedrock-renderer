# Dossier: Vibrant Visuals pass execute bodies (1.26.62.01)

Static. Found by scanning every VV pass-group builder (6gz table) for the rdata tables it installs and following the execute slot. Tags: [V] read, [I] inferred, [?] open.

## How a pass gets its body [V]

Three shapes, by what the builder installs:

1. **Pass object** (vtable `{dtor, 0x76920 no-op, execute, ?}`): slot 2 is the body. Deferred lighting, shading, water, voxel combine and light clustering use this.
2. **ScreenDraw std::function** (vtable 0xF440710 and per-builder copies): `_Do_call` tail-jumps to the shared ScreenDraw body 0xbc04dc0 (docs/functions/fullscreen_pass.md).
3. **Generic draw-list task** (std::function pair: `_Do_call` 0x5688f70 for setup, 0x568cd70 -> 0x568cd90 for the body): depth prepasses, DepthAndNormal, DoWaterSurfaceBuffer, forward PBR, RTX prep. These passes draw the extracted scene items, not a fullscreen quad. 0x568cd90 is the Scene/HUD view-setup task already rooted in the census.

## Body table [V addresses and strings]

| body | size | shape | strings in it (material / pass) | declared by |
|---|---|---|---|---|
| 0xbc2c590 | 0x558 | object | DoDeferredLighting / CausticsMultiplierPass | 0xbb6b350 |
| 0xbc2cd20 | 0x5F2 | object | DoDeferredLighting / DirectionalLightingPass (reversed below) | 0xbb6b350 |
| 0xbc2d550 | 0x5E4 | object | DoDeferredShading / DiscreteIndirectCombinedLightingPass | 0xbb6b350 |
| 0xbc2dd20 | 0x5DB | object | DoDeferredShading / SurfaceRadianceUpscalePass | 0xbb74040 |
| 0xbc2eb50 | 0x54C | object | WaterExtinction | 0xbb7efb0 |
| 0xbc2f4a0 | 0x85B | object | WaterSurface (+ PointLightShading, GPUBlockLighting variants) | 0xbb81880 |
| 0xbc0b240 | 0x88B | object | voxel combine (uniform DirtyVolumeCount) | 0xbb3e2b0 |
| 0xbc5bad0 | 0x19D1 | object | ClusterLights (AngularRefinement, LightsPerCluster, ClusterNearFarWidthHeight, CameraFarPlane) | 0xbc57460 |
| 0xbc04dc0 | 0x5D3 | ScreenDraw | shared fullscreen body | ColorPostProcess, forward 0xbb84ee0, NothingTask group, bloom, local exposure |
| 0xbc36140 | 0x5AA | std::function | (no strings) DoIndirectSpecularUpscale | 0xbb8eb70 |
| 0xbc38c20 | 0xDA8 | std::function | (no strings) | 0xbbbfc50 (NothingTask group, x3) |
| 0xbc0f130 | 0x648 | std::function | (no strings) CubemapToOffscreen | 0xbcd77b0 |
| 0xbc084b0 | 0x71 | std::function | (thunk) | 0xbbe2d50 (RTX prep) |
| 0x56d4880 | 0x1DC | std::function | (no strings) TAAUpscaling | 0xbc8a380 |
| 0xbc0ac20 | 0x162 | object | voxel upload | 0xbc09b10 (voxel, 0xbb6a1a0) |
| 0xbc080c0 | 0x25B | object | RTX denoise/raygen driver -> 0xbcc4b90 (direct encoder use) | 0xbbe2d50 |
| 0x568cd90 | 0x615 | draw-list task | generic scene draw | depth x11, DepthAndNormal, DoWaterSurfaceBuffer, forward PBR, RTX prep x7 |

The three builders with no table of their own delegate [V]:
- SSR 0xbc82ad0 declares its four passes through 0xbc88560, which installs a ScreenDraw std::function (vtable 0xF44B280, slot 2 = 0xbc04dc0 directly): SSRRayMarch, SSRRayMarchHZB, SSRFillGaps and SSRGetReflectedColor all run the shared ScreenDraw body. (The five code addresses the SSR builder takes, 0xbc88320..0xbc884d0 and 0xbc89f80, are atexit destructors of its static name strings, not bodies.)
- Voxel upload 0xbb3e2b0 declares through 0xbc09b10 / 0xbc09250 (also used by 0xbb6a1a0, LightClustering 0xbc57460 and LuminanceHistogram 0xbc8eb90): pass object vtable 0xF43EF40, body 0xbc0ac20 (0x162); 0xbc09250 installs 0xF43EF30 (slot 1 0xbc093b0).
- RTX denoise/raygen: a pass object (vtable 0xF43EC30: dtor 0xbc08010, no-op, execute 0xbc080c0, 0xbc08370) installed by the RTX prep builder 0xbbe2d50 at 0xbbe77f3. The body 0xbc080c0 (0x25B) calls 0xbcc4b90, which is not a builder: it records its 43 named passes straight into the encoder (Encoder::submit 0xbc60740, the compute-dispatch variant 0xbc60d10, submitFrameParams 0xbc618e0).

## DirectionalLightingPass 0xbc2cd20 (reversed, helpers named by behaviour)

`void DeferredLightingPass::execute(this /*rcx = pass object*/, PassContext* ctx /*rdx*/, const Resources* r /*r8*/)` [V].

```cpp
void DirectionalLightingPass::execute(PassContext* ctx, const Resources* r) {
    uint16_t viewId = ctx->view->id;
    View& v = s_ctx->views[viewId];                                   // same inlined setViewRect/Transform as ScreenDraw
    v.rect = clampRect(this->rect /*+0x88, +0x8C*/);
    memcpy(v.m[0], this + 0x08, 0x40); memcpy(v.m[1], this + 0x48, 0x40);
    memcpy(v.m[2], this + 0x9C, 0x40); memcpy(v.m[3], this + 0xDC, 0x40);
    memcpy(&v.extra, this + 0x11C, 0x10); v.b132 = this->b98;
    PassScope scope{ r->a /*+0*/, r->shared /*+8/+0x10, AddRef'd*/ };  openScope(ctx->view, &scope);   // 0xbcc1a30
    setMarker(encoder, "DoDeferredLighting");                          // static string, same inlined UniformBuffer write
    DrawState ds(ctx->view);
    if (!bindMaterial(true, &matRef, &ds, &r->material /*r+0x90*/, &scope)) return;   // 0xe86d7f0
    applyState(&ds);                                                    // 0xbcc3190
    if (!bindVertexStreams(&ds, r + 0x38) || !bindIndexBuffer(&ds, r + 0x38)) return;  // 0xbcc2b00 / 0xbcc2eb0: r+0x38 is a geometry reference (6hp)
    StencilAndBlend sb = copy(r + 0x23C .. r + 0x292);                  // 0x58 bytes of state
    MaterialPass* pass = r->material /*[r+0x90]*/->passes /*+0x2F8..+0x300, 24-byte {hash, ...}*/
                           .find(fnv1("DirectionalLightingPass") == 0x993692FCF6FC1544);  // 0xc4bba0
    if (!pass) return;
    Uniforms u{};  applyUniforms(&ds, r + 0x1A0, &u);                  // 0xbcc1910 / 0xbcc24f0
    TransformVariant t = { identity mat4, index 0 };
    submitPass(&ds, 0, viewId, &t, pass, 0);                            // 0xbcc38e0
}
```

In/out [V in, I out]: in = the geometry bound from `r+0x38` (vertex streams + index range: the fullscreen or light-volume mesh, 6hp), the G-buffer and shadow textures that the material binds plus the uniforms at `r+0x1A0`; material DoDeferredLighting, pass DirectionalLightingPass; out = the view's framebuffer (the light accumulation target) set by the frame graph.

The other deferred bodies (0xbc2c590, 0xbc2d550, 0xbc2dd20) have the same size and string shape (material + pass name), so they are almost certainly the same template with a different pass hash [I].

## Verification

Static. 0xbc2cd20 read in full (filtered listing); the table rows come from the vtable scan plus each body's strings. Status: 0xbc2cd20 D1, the rest D0 with names.
