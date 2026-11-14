# Progress: materials-visuals

## NEXT
Done so far: G4a/L7e. Next unit: G4b/L7f live texture census (CE evaluate_lua read-only, obj+0xBDE178 stride 0xB8, bounded), then G1b/L7b (closure statement from 6dr/6gs-6hj dossiers), then F1a/F4 body table from 6gz-6hb, then L11/L13/L14 via group_visitors.md.

## Units
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
