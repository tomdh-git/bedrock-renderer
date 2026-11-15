# Progress: materials-visuals

## NEXT
Closed: G4a/L7e, G1b/L7b, G2/L7c, L8c, F1a, F4, I1a/L11a, I3/L13a, I4a/L13b. L11b = DONE by citation (vv_lambda_bodies.md D1 entries). Open: G4b/L7f/L8d, F1b, F2b, I4b/L13c, G6/L7h, L8a, L8b (parked), L11c-d, L14a-d, I2a, I2c, I5-I7.
L11d DONE (docs/functions/sky_probe_passes.md). Order given by coordinator: L14c (now: FONT_TYPE define pair seen at 0x674d2bf/0x674d6be {MSDF|TrueType}; glyph atlas body = stage FontGlyph id 9, body not located) -> L14a -> L11d (vvclosures.py, docs/data/vv_closures.txt for SkyProbe/IBLSyncPoint) -> I2c (OPEN-partial: path+args decoded, docs/functions/item_in_hand_ctor_path.md; ctor body not read)  -> L14b (document cohtml glue 0x52d26a0 in/out).

## Units
### L14a / L14c step (both OPEN, partial; docs/functions/ui_font_text_leads.md)
- [V] UI visitor 5 cases summarised; ScreenRenderer not locatable by strings. Font loaders found: 0x4fb3870 (_ttf + .png + .info) and 0x4fbe0c0 (_ttfmsdf + .png + .info), extension tests 0x4fb2900/0x4fbdcd0; callers 0x4fbbea0, 0x4fbbf20, 0x4fbcab0, 0x4fc3930, 0x4fc3db0, 0x4fe0e10. Next: read 0x4fb3870 + its callers for the glyph .info parse (advances) = L14c closure. L14b parked (leads recorded).
### I2c - OPEN (path and arguments decoded: renderItemFull 0x531b490 -> renderItem 0x531a580 -> ctor 0x668cb70; docs/functions/item_in_hand_ctor_path.md)
- Blocking fact: ctor body 0x668cb70.. and the frame-data field names ([rdi+0x20/0x74/0x75/0x7c]) not reversed.
### L11d - DONE (probe/IBL pass bodies located)
- [V] IBLSyncPoint = NothingTask, body 0x56aeeb0 (view setup only). Sky-probe builder 0x56a06a0; pass body 0x56ae230 (material-pass template, pass hash 0xb2525e19c6e17c4b), fn body 0x56adf40, draw-list pairs 0xf25c020/0xf25c050. RT lighting bodies: cited vv_lambda_bodies.md. Doc: docs/functions/sky_probe_passes.md.
### G4a / L7e - DONE (sampler flag decode + sampler cache; texture/atlas management is tracked by L8a-c, not by this item)
- [V] 0xe820500 reversed instruction-complete: docs/functions/e820500.md. Key = bgfx HashMurmur2A over <=16 flag dwords; open hash map at heap+0x60; u16 free ring at heap+8; CreateSampler (device vtable +0xB0) into heap+0x10 + (u16[+0x24]*slot+i)*u32[+0x20]; D3D12_SAMPLER_DESC fully decoded with the tables read from the exe (address {1,2,3,4}, filter bytes, comparison {0,2,4,3,7,5,6,1,8}, MaxLOD 3.0 / FLT_MAX).
- CONTRADICTS 6ax: bit 28 (0x10000000) selects MaxLOD 3.0 vs FLT_MAX, not the border colour; border colour comes from the r9 table (index = bits 24..27), gated by BORDER address mode.
- File created: src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h (static_asserts; not built). No Sigs.json anchor inside it was used for constants, so static_asserts are the guard (not added to layout_asserts.json).

### G4b / L7f - OPEN (Fancy census + record layout done; VV/RTX render targets cannot exist in a Fancy session)
Live read-only (CE evaluate_lua readQword/readInteger only, 2 bounded polls, base this run via getAddress, obj=[base+0x12BB4910]); table obj+0xBDE178 stride 0xB8; (0xC96198-0xBDE178)/0xB8 = 4096 slots [V arithmetic], all 4096 scanned.
- [V live] 1558 of 4096 records have a resource pointer (+0x00); 526 more have a size but no resource (reserved/unrealized). Record layout is closed by 6im (D3D12_RESOURCE_DESC at +0x08, SRV desc +0x40, UAV desc +0x68, flags +0x98, w +0x9C, h +0xA0, d +0xA4, layers +0xA8, type +0xAE, mips +0xB1).
- [V live] +0x28 = DXGI format of the resource desc: histogram over populated: 0x1C (RGBA8_UNORM) 1538; 0x29 4, 0x0A 5 (R16G16B16A16_FLOAT), 0x1A 3 (R11G11B10_FLOAT), 0x3D 4 (R8_UNORM), 0x0B 1, 0x35 1, 0x2C 1, 0x27 1. Flags word +0x98: 0 = 1504 plain textures, 0x400000 = 23 (dynamic-texture reset flag, 6ei: small 28x28..36x48 and 1024x1024 R8), 0x1000 = 16 (render targets), 0x100000 = 7, 0x54A = 1.
- [V live] render-target textures (flag 0x1000), handle:size fmt/srvfmt: 0x0F 128x128 1A mips 8 layers 3 type 2 (cube); 0x10, 0x12, 0x15 128x128 0A mips 8 cube-typed (type byte 2, layers 1); 0x18 and 0x19 1920x1137 1A (main HDR colour, two buffers: matches 6z-2 "fmt 0x1a x2"); 0x1C 2048x2048 fmt 0x35 srv 0x38 layers 3 (shadow-map array, [I]); 0x49 256x256 1C; 0x4A 256x256 fmt 0x27 srv 0x29 (R32_TYPELESS/R32_FLOAT, [I] depth-like); 0x4B 512x1024 1C; 0x5A 1024x1024 1C mips 2 (fb 0x12 target, matches earlier census); 0xEE 1920x1137 fmt 0x2C srv 0x2E (R24G8_TYPELESS / R24_UNORM_X8, main depth); 0x2A0, 0x6FF 512x512 1C; 0x5C6 1920x1137 1C (post/ui colour); 0x798 1024x1024 1C. Also 0x000: 2048x24 fmt 3D flags 0x54A.
- Resolves the 6z-2 contradiction note of passes-materials-visuals: the main colour target IS in the texture table (0x18/0x19, depth 0xEE), it is just not referenced by any populated framebuffer record in 0..127 [?: how Fancy binds it without an fb record].
- Blocking fact: formats of the VV/RTX frame-graph render targets (bloom/HZB/gbuffer/RTX) are only allocated in VV/RTX mode; the user's session is Fancy.

### G1b / L7b - DONE (name -> MaterialInstance lookup chain closed; MaterialPtr pointee tagged [I])
- [V] chain: ResourceCache::get 0x675e440 -> shared_ptr<Holder> -> Resource (0x20, +0x10 requested, +0x18 MaterialSlot*) -> MaterialSlot (0x18: +0 MaterialInstance*, +8 shared_ptr<Material>) filled by loadAsync 0xbcbf730 / Job::run 0xbcc06a0 / 0xe86b730 / repo 0xc2919d0 / ctor 0xbcd1be0; consumer reads confirmed in the Item visitor at 0x66e76db..0x66e7746 (Resource* = [holder], cmp byte [+0x10],1, slot = [Resource+0x18], instance = [slot]). 0xc26caa0 (materials.index.json reader, 6dr) is not on the per-draw path.
- [I] MaterialPtr.mInfo = the shared_ptr<Resource> of the Holder (the old "RenderMaterialInfo" label); no game-side MaterialPtr constructor was read.
- Files: docs/functions/material_lookup_chain.md, src/sdk/mc/deps/minecraft_renderer/renderer/MaterialResource.h (new, static_asserts; not built). Static_asserts are the guard (no Sigs.json anchor).

### F1a - DONE (VV pass names + implementation-lambda addresses per group; bodies' contents are the other agent's M1e)
- [V] 115 name rows (first-use rva, FNV-1 64 hash, name) from docs/data/render_hashes.txt grouped by declaring builder address range (26 builders) in docs/functions/vv_rtx_pass_table.md; plus an appendix of every implementation-lambda vtable found by scanning each builder for rip-relative lea of tables (shape object/fn, slot-2 body) -> 80+ vtable rows. Group builders without own vtable delegate to declareScreenPass 0xbbbd3d0 / 0xbc88560 -> ScreenDraw 0xbc04dc0 [V callee lists].
- CONTRADICTS 6ha/pass_bodies.md: VolumeScattering, MinMax, luminance histogram, local exposure, FSR1, TAAU, Convolve have their own bodies (list in the doc), they are not all ScreenDraw; 0x56d4880 is not a slot-2 target of any vtable found.
- Files: docs/functions/vv_rtx_pass_table.md.
### F4 - DONE (RTX pass names)
- [V] 43 named passes of 0xbcc4b90 (ClearVertexIrradianceCache ... IncidentLightMeterInline, hashes + first-use rva) and the RTX prep names (PreBlasSkinDispatch, PrepareTLAS, AlphaTestCracks) in docs/functions/vv_rtx_pass_table.md; loot-table lowercase hits inside 0xbbe2d50's address range are not passes and were dropped. RTX bodies: object 0xbc080c0 (vtable 0xF43EC30) -> 0xbcc4b90 encoder-direct (6hb).
- [?] 0xbbe2d50's own 79 KB declaration lambdas are not covered (M1e, other agent).
### F1b - OPEN (in/out resources per pass pending: needs the frame-graph builder's resource declarations mapped to Resources fields; the declaration order is in 6ar)
### F2b - OPEN (the 0xBC3.... lambdas are the other agent's M1e; the Fancy pass list of 6da-6dc already exists)

### I1a / L11a - DONE (shadow cascade anchors)
- [V] 0x53fcac0 (cascade set build; strings near, bias, slope_bias, resolution, pcf_width, shadow_range, shadow_chunk_radius, max_shadow_distance, cloud_shadow_*, sun_shadows, moon_shadows, cloud_shadows, cascades, quality names medium/high/ultra) and 0x543c950 (assert "Total number of cascades ... MaxTotalCascades", max_shadow_distance vs shadow_chunk_radius). Unique wildcard signatures from tools/sigs/xref.py sig (the tool requires exactly one match over .text) are in docs/functions/anchors_visuals.md. Not added to Sigs.json (other agents).
### I3 / L13a - DONE (particle anchor + strings): 0x67417f0 (Effect tag 2 handler, 0x2cd7 bytes): ParticleForwardPBR, ParticlePrepass, Particle, PointLightShading, ParticleTexture, FogAndDistanceControl, MERSUniforms, PBRTextureFlags, MERSTexture, NormalTexture; signature in anchors_visuals.md [V].
### I4a / L13b - DONE (weather anchor + strings): 0x6745440 (Sky tag 9 handler only, 6gm): WeatherForwardPBR, Weather, NoVariety, PointLightShading, FogAndDistanceControl, textures Weather/Occlusion/Height/Lighting, uniforms PrevPositionBaseOffset, PrevPositionForwardOffset, PositionBaseOffset, PositionForwardOffset, ViewPosition, UVOffsetAndScale, Velocity, Dimensions, OcclusionHeightOffset [V].
### I4b / L13c - OPEN (clouds anchor 0x67375a0 + strings Clouds, CloudsForwardPBR, CloudColor, DistanceControl, PrevWorld are done [V]; blocking: sky/stars (Sky tag 5/6) and celestial (tag 7) bodies are untyped, R11)

### G2 / L7c - DONE (runtime variant selection reversed; file-format axes by 6ap)
- [V] selection chain: findVariant 0xbcc7ce0 -> selectVariantId 0xe879eb0 (merge material default flags <- pass flags <- validated defines via 0xe87b920; first variant record consistent per 0xe879c60) -> id looked up in pass+0x108 map (FNV-1a 64 of the 8 id bytes) -> node+0x1C {u16 program, valid bit16} (created at load by initFromMaterial, 6gy) -> Encoder::submit (0xbcc3b90). Default id at pass+0xA0 when no defines. Correction: the keyed u64 is a variant-record id (pointer), not a bit mask; hash is FNV-1a, not FNV-1.
- [I] roles of the merge order and "fixed by pass flags" rule; names of fields. Files: docs/functions/bcc7ce0.md, src/sdk/mc/deps/minecraft_renderer/renderer/MaterialPassLayout.h (static_asserts, not built).
### G6 / L7h - OPEN (blocking: no hook implemented or tested; control points now identified: ResourceCache::get 0x675e440 by name, load 0xe86b730, variant pick 0xbcc7ce0)

### Sigs.json anchors (I1a/I3/I4a) - NOT added: Sigs.json is modified in the working tree and the platform-versioning agent's activity is unknown; the signatures stay in docs/functions/anchors_visuals.md (0x53fcac0, 0x543c950, 0x67417f0, 0x6745440, 0x67375a0).

### L8a / L8b / L8c - OPEN (D3D12 createTexture wrapper reversed; blockers below)
- [V] docs/functions/e8143c0.md: createTexture slot 26 flow (record address incl. paged handles, bimg-style container parse 0xebd2160, TextureD3D12::create 0xe81bf30, side map at [this+0x3C549F8]+0x14428, state tracker 0xe82d960).
- L8a blocker: game-side ClientTexture/BedrockTexture -> bgfx createTexture caller chain not traced. L8b blocker: body of 0xe81bf30 (format/mip/compression handling) unread. L8c blocker: same body (upload) plus destroy path lifetime.
### L11b-d, L13d, L14a-d, I2a, I2c, I5-I7, I4b - OPEN, not started this pass (budget; descriptions agent owns description fields, M1e agent owns lambda bodies).

### L8a / L8b / L8c - still OPEN (this pass: texture record fill + game-side wrapper)
- [V] e8143c0.md addendum: TextureD3D12::create header phase gives every record field written at +0x98..+0xB1 and the format fallback/sRGB/SampleDesc derivation (L8b partial: mips skip, block-min size, format support fallback 0x42; compression handled by the format table, upload of compressed mips not read).
- [V] 8b9f1c0.md: game-side wrapper -> bgfx createTexture2D/Cube -> slot 26 chain.
- Blockers: L8a pack->image producers above 0x67ceb40; L8b/L8c upload loop and resource creation tail of 0xe81bf30 (0xe81c45c..0xe81d65x) and the destroy/lifetime path (slot 34, 0xbc71da0).

### L8b / L8c - still OPEN (this pass: staging + resource creation + destroy path read)
- [V] docs/functions/e8143c0.md Addendum 2: staging array construction (pitch 0x100 / slice 0x200 alignment, same-format block copy 0xebd1a30 vs conversion 0xebd21c0), pooled vs committed resource branches and failure codes, destroy chain (cmd 34 -> slot 34 0xe815ea0 -> record dtor 0xe80f290 -> deferred-release vector ctx.state+0x2CBE0).
- CONTRADICTS BGFX_MAP 619/620: 0xbc71da0 is not destroyTexture (allocates handle, emits cmd 0xB -> slot 56).
- Blockers: L8b = game-side atlas builders (terrain/item atlas) untraced and compressed-mip upload slots; L8c = final D3D12 copy vcalls (CFG-thunk slots) and the deferred-release drain.

### L8c - DONE (async upload + texture handle lifetime)
- [V] create: bgfx createTexture2D/Cube 0xbc716a0/0xbc71990 (handle from the ring at ctx+0x1dfc298, 0xFFFF = none) -> command buffer -> render thread slot 26 0xe8143c0 -> 0xe81bf30: staging array (pitch 0x100, slice 0x200), resource creation (pooled placed or committed, failure sets ctx+0x19F88/0x19F8C), D3D12 upload sequence mapped by vtable offset (e8143c0.md Addendum 3: Map, GetCopyableFootprints, Unmap, CopyTextureRegion/CopyBufferRegion, ResourceBarrier). Roles of individual calls [I].
- [V] destroy: cmd 34 -> slot 34 0xe815ea0 -> record dtor 0xe80f290 -> push resource on the per-frame deferred-release vector -> drained by 0xe818490 (docs/functions/e818490.md) after the frame's fence value completes (SetEventOnCompletion + wait, Release via vtable +0x10), frame records in a ring of 0x110 entries of 0x2CBF8 bytes. Flag 0x400000 textures are never released by the renderer (6ei).
- Files: docs/functions/e8143c0.md (addenda), docs/functions/e818490.md. No header (offsets are inside the FrameManager object whose layout is only partly known); static_asserts not applicable.
### L8b - OPEN (compression/mips path closed via the same code: block-aware copy + GetCopyableFootprints; blocker = terrain/item atlas builders on the game side untraced)
- L8b leads (atlas builders, strings verified by xref.py str atlas): 0x5752d50 ("atlas.terrain", "atlas.items", compass/clock atlas textures), 0x4e1a0a0 ("texture_atlas", "failed to read texture_name in atlas file %s"), 0x6bfa6d0 ("Texture %s is missing from atlas textures"), 0x6bfa9d0 ("invalid atlas index %i for the expected UV count %i"), 0x6bf8770 / 0x6bf9270 (atlas_index / atlas_tile / atlas_tile_variant block-model fields), 0x94cf90 (grass block atlas entry assert). None reversed.
- L8b (this pass): docs/functions/atlas_uv_apply.md: 0x6bfa6d0 + 0x6bfa9d0 read in full (UV application by atlas index, error strings), 0x4e1a0a0 identified as the atlas JSON parser, 0x5752d50 corrected (inventory item renderer, not an atlas builder). Still OPEN: the stitcher that builds the atlas image/mips and feeds the texture creation chain.
- L8a/L8b parked by coordinator order. Leads: callers 0x95ed00 (of 0x6bfa6d0), 0x4e198d0 and 0x4e1cbb0 (of the atlas JSON parser 0x4e1a0a0).

### L11b-d, L14a, L14c, L14d, I2a, I5a, I5c, I6-I7 - OPEN (not worked; blockers)
- L11b/I1b: needs the pass bodies ClusterLights 0xbc5bad0 / voxel 0xbc0b240 (M1e agent). L11c: description fields of LightAmbient/Directional/Atmosphere (descriptions agent, docs/progress/descriptions.md). L11d: no probe/IBL body located (SkyProbe/IBLSyncPoint names only).
- L14a/I5a: UI visitor 0x6664a00 and extractor 0x674a3a0 exist as dossiers; ScreenRenderer internals untraced. L14d: description fields (descriptions agent).
- L14b/I5b blocker: Ore UI is cohtml, a statically linked third-party renderer (cohtml mangled export strings in the exe, glue 0x52d26a0); its backend is not reversed.
- L14c/I5c: glyph atlas / SDF font code not located (no string hit in the one search made).
- I2a: anchors exist in Sigs.json; "internals pending" has no reversal this pass. I6a/I6b/I7: bodies are M1e's (0xbc8cfd0, 0x56d4860, 0xbcb7590, 0xbcb7e70, 0xbc080c0).

### L11b / I1b - DONE by citation (pass code): docs/functions/vv_lambda_bodies.md entries 0xbc5bad0 ClusterLights (six uniforms by name hash, scope, material holder), 0xbc0b240 CombineVoxelLighting, 0xbc0ac20 voxel upload; inherits that agent's D1/D2 status. The CPU scoring and shader inputs were already in 6bj/6cd.
### Resource-load graph (new, supports L8a/L14c): docs/functions/resource_load_graph.md - 36 stage names with ids (FontGlyph 9, TerrainAtlas 6, ItemAtlas 7, AnimatedAtlas 8, BlockThumbnailAtlas 0x26, DynamicTextures 0x19, TextureShift 0x27, Texture 1, FinalizeLoad 0x1E), registerStage 0x1870de0 semantics; stage bodies not located.
