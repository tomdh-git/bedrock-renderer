# Dossier: the fullscreen ("ScreenDraw") pass path of the Vibrant Visuals renderer (1.26.62.01)

Static. One worked pass (ColorPostProcess) read end to end, plus the shared declaration helpers and the shared execute body that every pass declared this way runs. Tags: [V] read, [I] inferred, [?] open.

## Chain

```
VV frame builder 0x55f1450
  -> pass-group builder (ColorPostProcess: 0xbbbcb20, 0x711 bytes, read in full)
       -> declareScreenPass 0xbbbd3d0 (0x3E6, read in full; also called by 0xbbcd010 and the bloom builder 0xbc9ada0)
            -> buildScreenPass 0xbc37320 (0x784, read in full; also called by 0xbcbade0)
                 -> 0xbc039a0 build the draw packet (6 callers: forward PBR 0xbb84ee0, NothingTask group 0xbbbfc50, 0xbc02d20, 0xbc88560, 0xbc98310)
                 -> 0x568ad40 pass name -> pass id; 0xbc04bb0 attach; 0xbc054a0 finalize
                 -> execute = std::function, vtable rva 0xF440710 (_Copy/_Move 0xbc380c0, _Do_call 0xbc380d0, _Target_type 0xbc380e0)
                 -> registerPass 0xbc37ca0 (0x2D7; callers 0xbc37320, 0xbc81a40)
render time: _Do_call 0xbc380d0 = `jmp 0xbc04dc0(capture + 8, ctx, pass)`  -> the ScreenDraw body below
```

## Group builder: ColorPostProcess 0xbbbcb20 (reversed source, complete)

```cpp
void declareColorPostProcess(Declarator* d /*rcx*/, X* a2 /*rdx*/, const Size* target /*r8*/, MaterialUniforms* mat /*r9*/,
                             const PostSettings* s /*5th*/, const Inputs* in /*6th*/, Y* a7 /*7th*/) {
    static uint64_t hColorTexture   = fnv1a64("ColorTexture");        // lazy statics (guards 0x12ADF1C0 / 0x12ADF1D0)
    static uint64_t hColorGradingMisc = fnv1a64("ColorGrading_Misc");
    vec4 misc = { s->f_EC /*+0xEC*/, (float)(int8_t)s->b_F9 /*+0xF9*/, 0, 0 };
    if (auto slot = mat->findSlot(hColorGradingMisc))                   // linear search of mat+0x38 (count u16 +0x42, 16-byte entries, name hash at entry->+0x28)
        setUniform(&mat->block /*mat+8*/, &slot, {1, &misc});            // 0x5679db0 (6gr)
    TextureBinding tex = { hColorTexture, 0, 0, 0, in->colorTexture /*in+8*/, 0 };          // rbp+0x160
    std::string phase = "GammaColorPostProcessPhase";                    // 26 chars
    PassName name = { 0x16D95E79CDB26A8F /*FNV-1 64 of "ColorPostProcess" (6p)*/, "ColorPostProcess" };
    ViewSetup view = defaultView(*target);                               // identity matrices, rect = target size, flags 0x3F80000000000001, bytes 7/2/8/8/0xFF, engaged
    declareScreenPass(d, &view, a2, target, &name, &phase, mat, a7, &tex);   // 0xbbbd3d0
}
```

## declareScreenPass 0xbbbd3d0 (reversed source, complete)

```cpp
bool declareScreenPass(Declarator* d, const std::optional<ViewSetup>* view /*engaged byte +0x17C*/, X* a2, const Size* target,
                       const PassName* name, const std::string* phase, MaterialUniforms* mat, Y* a7, const TextureBinding* tex) {
    ViewSetup v;                                                          // 0x17C bytes: 6 identity mat4 + rect + flags
    if (view->has_value()) v = **view;                                    // field-by-field copy (+0x00..+0x17B)
    else { v = ViewSetup::identity(); v.rect = { *target, *target }; v.count = 1; v.b138 = 0x0F; }
    std::optional<std::vector<...>> extra;                                // empty
    bool ok = buildScreenPass(d, &v, &extra, a2, name, phase, mat, a7, tex);   // 0xbc37320
    return ok;                                                            // extra destroyed if it was filled
}
```

## buildScreenPass 0xbc37320 (structure, read in full) [V order]

1. Copy `extra` (0x6760450) and the 0x17C-byte ViewSetup into the pass record.
2. Copy the geometry reference (corrected 6hp; DrawItemGeometry in DrawItem.h): the vertex stream references `std::vector<0x28-byte stream ref>` from `a2+8 .. a2+0x10` (0x56b8630), the vertex count `a2+0x20`, the index buffer reference (4-way variant at `a2+0x28`, index byte `a2+0x38`; index 3 = shared_ptr, AddRef'd), then startIndex `a2+0x40`, index count `a2+0x48`, `a2+0x50`.
3. Copy the shader-state block (0xe869ff0) and take ownership of `a2+0x80`.
4. `0xbc039a0(&packet, &record, &bindings, &view, a7+8, &extra)` builds the draw packet; no packet means the pass is not added and the function returns false.
5. Pass id = 0x568ad40(phase string); 0xbc04bb0 attaches the packet; the execute std::function (vtable 0xF440710) is installed; 0x76a8a0 copies the phase name; 0xbc054a0 finalizes; `registerPass(d, &record, 0)` 0xbc37ca0.
6. Returns true when the pass was added.

## The shared execute body: ScreenDraw 0xbc04dc0 (reversed, helpers named by behaviour)

`void screenDraw(Capture* c /*rcx, unused*/, PassContext* ctx /*rdx*/, ScreenPass* p /*r8*/)` [V].

```cpp
void screenDraw(Capture*, PassContext* ctx, ScreenPass* p) {
    uint16_t viewId = ctx->view /*+8*/->id /*u16 +8*/;
    View& v = s_ctx /*[rva 0x12AE1748]*/->views[viewId];                 // ctx + 0x1EAB080 + viewId*0x140
    v.rect.x = max(p->rect.x, 0);  v.rect.y = max(p->rect.y, 0);         // i16 pair from p+0x168, pmaxsw with 0 -> view+0x10
    v.rect.w = p->rect.w ? p->rect.w : 1; v.rect.h = p->rect.h ? p->rect.h : 1;   // p+0x16C -> view+0x14 (0 becomes 1)
    memcpy(&v.m[0] /*+0x20*/, p->mat0 /*+0xE8*/,  0x40);                 // inlined bgfx::setViewTransform: four mat4
    memcpy(&v.m[1] /*+0x60*/, p->mat1 /*+0x128*/, 0x40);
    memcpy(&v.m[2] /*+0xA0*/, p->mat2 /*+0x17C*/, 0x40);
    memcpy(&v.m[3] /*+0xE0*/, p->mat3 /*+0x1BC*/, 0x40);
    memcpy(&v.extra /*+0x120*/, p + 0x1FC, 0x10);
    v.b132 = p->b178;                                                     // view+0x132
    auto scope = std::make_shared<PassScope>(ctx->view->encoder);         // 0x30-byte block; 0xbcc1a30(ctx->view, &scope) opens it
    std::string marker = "ScreenDraw:" + p->name /*std::string +0x268*/;
    UniformBuffer* ub = frame->uniformBuffers /*Frame+0xDC57E0*/[encoder->index /*+0x6AC*/];   // inlined Encoder::setMarker
    ub->write(u32(0x28000001 + 2*(len+1)));  ub->write(marker.c_str(), len+1);                  // opcode then bytes (bounds-checked)
    DrawState ds(ctx->view);  /* temp vectors cleared; 0x568db90 per 0x20-byte item */
    if (bindMaterial(true, &matRef /*ctx->+0x20 -> +0x28/+0x38*/, &ds, p, &scope)) {              // 0xe86d7f0 (0xFD6, 30 callers)
        applyState(&ds);                                                  // 0xbcc3190 (bounded paged-heap access, calls into 0xbc6e1e0.. = the encoder)
        RenderStateBits rs = convertState(p + 0x20C);  apply(&ds, p + 0x170, &rs);   // 0xbcc1910 (DrawItemState -> bgfx bits, 6hl), 0xbcc24f0 (atomic u16 handle swap in Frame+0xDC57D0)
        if (bindVertexStreams(&ds, p + 0x88) && bindIndexBuffer(&ds, p + 0x88))     // 0xbcc2b00 / 0xbcc2eb0 on the geometry reference (6hp); dynamic VB table s_ctx+0x1DBD0C8 stride 0x1C
            submitPass(&ds, 0, viewId, &p->transform /*+0x2C8*/, p->materialPass /*+0xE0*/, 0);  // 0xbcc38e0
    }
}
```

submitPass 0xbcc38e0 [V, corrected by 6ha]: `(DrawState*, u8, u16 viewId, const TransformVariant* t, MaterialPass* pass /*5th*/, u32 /*6th*/)`. It switches on the transform variant's index byte at `t+0x40`: 0 -> 0xbcc3b90 with the single mat4 stored inline at `t+0x00` (the deferred-lighting body passes identity), 1 -> 0xbcc4150 with a span of mat4 (`count = size >> 6`, one draw per transform, i.e. instancing), 2 -> 0xbcc3fa0 with a pointer at `t+0` plus an optional 16-byte region from `pass+0xE8` (engaged byte +0xF8); any other index -> bad variant (0xb432e0). The 5th argument is the material pass to draw with, not a mesh.

## In/out resources of ColorPostProcess [V for the in side, I for the out side]

- In: `ColorTexture` = `in+8` (the scene color), uniform `ColorGrading_Misc` = {settings+0xEC, (i8)settings+0xF9, 0, 0}.
- Out: the view's framebuffer for the pass view (set by the frame graph; the ViewSetup here only carries rect and matrices).

## View record (s_ctx views, stride 0x140) confirmed by this body [V]

+0x10 rect {i16 x, i16 y}, +0x14 {u16 w, u16 h}, +0x20 / +0x60 / +0xA0 / +0xE0 four mat4, +0x120 16 bytes, +0x130 u16 framebuffer (6q), +0x132 u8.

## Verification

Static. 0xbbbcb20, 0xbbbd3d0, 0xbc37320, 0xbc04dc0 and 0xbcc38e0 read in full; the helpers they call are named by behaviour only. Status: 0xbbbcb20 and 0xbbbd3d0 D2; 0xbc37320, 0xbc04dc0 D1.
