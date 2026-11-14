# Render reversal master checklist (bgfx, RenderDragon, FrameBuilder, adjacent)

Rule for ticking: `[x]` only when the item is written down in `docs/BGFX_MAP.md` (or the named doc) with RVAs/offsets AND has an SDK header or hook where one is listed. There is NO partial state (rule of 2026-11-14): only `[x]` (fully done, evidence written, constants in both assertion lists) or `[ ]` (anything less, including "partly done"). Progress notes stay inside the item text but never change its box. "Done" for the whole effort = every box below is `[x]`. Work order: top to bottom inside each section, sections in the order of "Execution order" at the end. Last updated 2026-11-12.

## A. bgfx core
- [x] A1 Frame buffer layout (view remap, matrices, draw headers, tail block, counters) — 6e, `Frame.h` (P2) — offsets move per patch
- [x] A2 Draw header (0x80) fields read by the executor — 6e-2
- [x] A3 bgfx::Caps (limits, flags, globals) — 6j, `Caps.h` (P1) — version-stable concepts
- [x] A4a Context init + thread start 0xbc63690 — 6q
- [ ] A4b Context global 0x12ae1748 + view array + semaphores — 6r (handle allocators A8 pending)
- [x] A5a frame()/swap = 0xbc66de0, handoff 0xbc65800, thread 0xbc65720 — 6r,6s
- [x] A5b Encoder::submit 0xbc5fb40 decoded: encoder object layout, draw index alloc (Frame+0xDC57E8), key build, header copy (6cq) (P2) — RVA moves per patch
- [x] A5c Encoder setters: inlined stores (state +0x60, rect +0x80, binds +0x140 block) — no call sites (6cr)
- [x] A5d Encoder submit variants + reset + Frame::sort 0xbc61220 (6cq, 6cr); setters are inlined stores into Encoder+0x40..0x680
- [x] A6a View struct (0x140, 256 views at ctx+0x1eab080) — 6q
- [x] A6b View matrices: s_ctx view array +0x20 (6q, live 6r)
- [ ] A6c Sorted item list Frame+0x94700 (6am); sort key bit layout partly
- [x] A7a Uniform name lookup + createUniform registry (hash table, records, allocator) — 6ag, 6ah
- [x] A7b Predefined uniforms list (14, Mojang additions marked) — 6ag
- [ ] A7c Per-draw constant stream cursor + 20-byte binding records (type 0-8) — 6an; opcode set pending
- [ ] A8a Handle allocators located in Context (offsets) — 6s, 6ai (API fn map; per-allocator roles [I])
- [ ] A8b Record tables: texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 layouts — 6au; 0x78/0x80/0x130/0x68 field layouts pending
- [x] A8c Guarded paged array layout (4096 inline + chained pages, guard byte +0xC96190) — 6z
- [x] A9 Render item state bits: u64 S bit map (write mask 0-3, depth func 4-7, blend factors 12-27, equation 28-30, cull 36-37, flags) + stencil state2 + PSO key mask (6ct); a few bit names (31-35, 48-50, 56-58) still candidates — enum tables dumped (6cu) (P1) — bit semantics version-stable -- 6fs: bits 31-35 and 56-58 now named from the PSO desc (alpha equation 31-33, independent blend 34, alpha-to-coverage 35, MSAA 56, line AA 57, conservative raster 58); stencil word map and all five enum tables dumped.
- [ ] A10 render thread proc, semaphores ctx+0x80/+0x100, surface array stride 0x700 — 6as; 0xbc63150 internals pending
- [x] A11 init/reset/shutdown: lifecycle (6di), reset entry = submit prologue + slot 60 0xe81a610 (6dn); shutdown ordering = slot 59 (not exercised live)
- [ ] A12a dynamic texture handles = reset flag 0x400000 + caps bit 0x12ADFA54&0x10 + free-list (6ei); createDynamicTexture 0xbc74a80
- [ ] A12b ranged vertex-buffer binds: only the RTX skinning range check (0xe83f1d0) found (6ei); setter API not isolated -- 6fe: storage side decoded (Frame+0x8B4778 SideTable* per item, 0x41 x {Binding*, count}, fed from Encoder+0x680 by 0xbc60f10); the setter filling the encoder table is still open
- [ ] A12c RTX handles: pass+string anchors (6ei); fork handle/call API not isolated
- [ ] A12d upscaling: DLSS/NGX parameter set in 0xe83ec70 + 0xe8403d0, TAAU/FSR1 passes (6ei); call wrappers not isolated
- [ ] A13 SDK headers: Encoder.h and View.h added (Frame.h, Caps.h existed); Handles.h/Uniforms.h pending

## B. D3D12 backend (RendererContextD3D12 + RTX subclass)
- [x] B1 vtable slots named; corrections in 6aj — 6k, 6aj (P1) — interface survives
- [x] B2a Slots 0-21 verified by disassembly — 6aj (table-evidence)
- [x] B2b Slots 22-49 verified — 6aj (table-evidence)
- [x] B2c Slots 50-62 verified — 6aj (table-evidence)
- [x] B2d RTX slots 54/63/64 and overrides verified — 6al
- [ ] B3a submit stage map by callees — 6t, 6af (P2) — callees move
- [ ] B3b submit: descriptor binding types (6an), sort-key program field, descriptor flush (6ao)
- [x] B3c Draw emitter found: 0xe81b720 DrawBatcher flush (DrawInstanced 0x70-stride records, DrawIndexedInstanced 0x88-stride records, ExecuteIndirect for batches); executor calls it at 0xe822e4e etc. (6ej); sig D3D12Context.drawFlush; not run in game
- [x] B3d submit stats/timers/debug overlay: stock bgfx stats text + timers inlined in slot 50 (6dh); flag bit positions to confirm live
- [ ] B4 PSO cache: builder 0xe81dc60 decodes state to D3D12 PSO desc, key mask known (6ct, 6ao); disk cache 0xe8feb10 pending -- 6fr/6fs: key (Murmur2A over 13 inputs) and the blend/rasterizer/depth-stencil part of the desc reversed; RenderDraw +0x68/+0x6C/+0x70 = depth bias fields; input layout, formats, CreateGraphicsPipelineState and cache insert still to do. -- 6ft: builder transcribed end to end (input layout, topology, targets, sample desc, create, cache insert); disk cache 0xe8feb10 still pending.
- [ ] B5 Root signature serialized in init (6ak); >=6 root params, tables 2/3, value 5 (6ao); full layout pending
- [ ] B6 Queue wrapper +0xCC9268, current list +0x19F58, submit/flush slots 8/61/62, frame-context ring — 6av; fence wait internals pending
- [ ] B7a createTexture signature + table access — 6z
- [ ] B7b State transition helper 0xe82d960 + tracker entries — 6ae
- [ ] B7c Upload tracking lists (0x48/0x18 entries @+0x1A000/+0x1A018) + destroy path slot 57 (6ba); slot 55 init (6bb); copy path + slot 56 pending
- [x] B8a Swapchain: create slot 39 (6az), reset slot 60 (6aw/6ax), present slot 6 (6ay), window table 0xC97698 (stride 0x68)
- [x] B8b TDR / device lost handling (slot 7) — 6ak
- [x] B9a createShader blob formats (CSH3/FSH5/VSH5 wrapping DXBC; no DXIL) — 6at (P1) — format semantics stable
- [ ] B9b createProgram/destroyShader records (6au); input-layout builder ('TEXCOORD' user 0xe81xxxx) pending
- [ ] B10a RTX GPU skinning (slot 63 = 0xe83f1d0, 0x107b) anchor — 6al, 6bc (P3) — RTX, low priority unless RTX hardware
- [x] B10b DLSS/SuperSampling surface: mode select slot 60, param-key vocabulary slot 64 — 6al, 6bc
- [ ] B10c TLAS/BLAS: PrepareTLAS 0xbbe5c43, PreBlasSkinDispatch 0xbbe4399, RTXAccelerationStructure ref 0xbbf5bea (6ei); the D3D12 build call sites not located
- [x] B11 SDK header bgfx/d3d12/D3D12Context.h: rvas, offsets, six resource tables, slots (6eg); compile-checked, not in DLL build

## C. RenderDragon
- [x] C1 BgfxContext::endFrame (0xc270460) flow — 6n (P1) — architecture, survives
- [x] C2a GraphicsTasks Render lambda 0xc267200 + chain — 6ab, 6ac
- [x] C2b Execute 0xc25fc50 and Wait for previous frame 0xc25f960 — 6ac
- [ ] C3a Task scheduler 0xc25b1a0 call map — 6ac; queue layout pending
- [ ] C3b Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending
- [ ] C4a DragonFrameResources: +0x298/+0x2A0 vector<shared_ptr<Task>> found via endFrame/0xe9002e0 (6cx); remaining fields pending
- [ ] C4b IntraFrameAllocator: wrapper over pooled arena via 0xa78940 blocks with refcounted control (6cy); exact field list pending
- [ ] C5a Declarator<RenderContext> + five Bind* dependency kinds + module names — 6aq; registration call addresses pending
- [ ] C5b drawutils pass-declaration templates (178 signatures) — 6aq; per-pass bodies pending
- [x] C5c HashedString hash = FNV-1a 64, names built inline — 6o (P1) — algorithm constant
- [ ] C6 Deferred Texture/Buffer Transactions flush 0x6632bf0 (two labelled vector<Transaction*>, vtbl slot1 run + slot0 delete) (6dv); aliasing not found
- [ ] C7a 0xc273420 prologue + stages: 51 callees, hot helpers mapped (6n-2); stage split pending a live breakpoint on 0xc27f940
- [ ] C7b per-pass loop located (0xc277e8c..0xc2793fe), dependency records = 24/40-byte vectors (6cz); body fields pending
- [x] C7c Dispatch 0xe9002e0 + task classes + live pass order/names (6cx, 6da, 6db) (P2) — task dispatch RVAs move
- [ ] C8 Threading: draw executor runs as parallel jobs, one command list per job (this+0x19F60[job]), job slices of the sorted list (6cp); encode-thread side pending [RVAs in 6cp are 60.05, see 6cw]
- [ ] C9 dragon/Tasks.h (task list, class vtables, name offsets, taskName) + PassNames.h written (6eg); the per-frame enumeration detour on 0xE9002E0 not written

## D. FrameBuilder
- [x] D1 vtable group slots + endFrame — `FrameBuilder.h` (P2) — slots shift per patch
- [x] D2 Catalog of 62 types / 50 clones with group — `DescriptionClones.h`, RENDER_CATALOG
- [x] D3 Clone calling convention + Nametag clone — 6l (P1) — calling convention stable
- [x] D4 BatchActor description layout — 6d
- [x] D5a Nametag description (0x98) typed in Descriptions.h — 6m
- [ ] D5b ChunkGeometry description: extractor + pointer route (6be); field layout pending (needs live capture)
- [ ] D5c ChunkOccluders: thin clone 0x5369920 -> Item vslot 0x378 tag 4, handler 0x6646a89 creates "ChunkOccluder" render object, fields +0x30..+0x48 (6dx); field types pending
- [ ] D5d Crack: fat clone 0x539fff0 builds from a destroy-progress list at B+0x3280 (node+0x10 pos, +0x20 progress float) (6ea); final description fields pending
- [ ] D5e ItemInHand: thin clone 0x531b180 -> tag 6 -> extractor 0x6698e30; fields +0x28 ptr, +0x38 mat4, +0x78/+0x7A flags, +0x11C, +0x158.. blocks, +0x1D0/+0x1D4 (6dz)
- [ ] D5f SkinnedMesh: general clone 0x6b84e60 fields +0x10/+0x18/+0x20/+0x30/+0x38/+0x60/+0x74-76/+0x108-118 and second producer 0x4e39f20 (6ec); field meanings pending
- [ ] D5g MeshFallback description head typed (Descriptions.h); tail to 0x1d0 pending
- [ ] D5h BlockSelectionOverlayBlockEntity: fat clone 0x539b7c0, Item tag 8, built from the selected block position + region block-entity lookup (6eh); description fields pending
- [ ] D5i EnvironmentalText/UIText: shared clone 0xe71330 -> Item vslot 0x378 or UI vslot 0x368; text = shared string at desc+0x90/0x98/0xA0, font obj +0xB0, flag +0x75 (6eb); +0x60 struct pending
- [ ] D6a Sky / Stars description (tag 5; fields pending) — 6w
- [ ] D6b Sky-group clones: EndSky 0x53707a0 tag3, Celestial 0x5370b20 tag7, Cubemap 0x660b720 tag2 (thin); LegacyCubemap 0x660b1a0 tag4 (fat, texture variant select) (6ed); fields pending
- [ ] D6c Clouds, Weather, Atmosphere — clone kind/group/tag table 6ee; fields pending
- [ ] D7a Particle, FlameBillboard — clone kind/group/tag table 6ee; fields pending
- [ ] D7b Shadow, PlayerVision, VolumetricFog — clone kind/group/tag table 6ee; fields pending
- [ ] D7c FullscreenEffect, BlitFlipbookTexture — clone kind/group/tag table 6ee; fields pending
- [ ] D8 UI descriptions (Mesh, Gameface, HudIcon) — clone kind/group/tag table 6ee; fields pending
- [ ] D9a Light descriptions (Ambient, Directional, Point) — clone kind/group/tag table 6ee; fields pending
- [ ] D9b Voxel/TransitioningVoxel volumes, ShadowAtlasFrame, SkyAmbientSamples — clone kind/group/tag table 6ee; fields pending
- [ ] D9c gamecomponents (GameplayMetadata, ServerGraphicsOverrideParameters, EditorHighlightConfiguration) — clone kind/group/tag table 6ee; fields pending
- [ ] D10 Editor group descriptions (gizmos, block volumes, render plane, selection cursor) — clone kind/group/tag table 6ee; fields pending
- [ ] D11 Descriptions.h: Nametag, MeshFallback head; BatchActor in FrameBuilder.h
- [ ] D12 Group tag enums for all six groups added (FrameBuilder.h) — 6w; typed hooks pending

## E. Extractors and registry
- [x] E1a Item visitor jump table with verified tag identities — 6w (P2) — RVAs shift per patch
- [ ] E1b Tag 0/4: entries (6ci); live field decode (6cv: transform, colours, pointer arrays); per-field names partial
- [ ] E1c Tag 1/5 and 2/3/7/9: entries (6ci); tag 7 and 1 fields decoded from live dumps (6cv: model matrix pair, AABB, material node at +0x140)
- [ ] E1d Tag 6/8/10 forwarders: entries 0x6647320 / 0x66473e6 / 0x6647383 (6ci); GlowInkSign inside 8
- [ ] E2 BatchActor extractor callee map — 6u (inner decode pending)
- [ ] E3 Tag 7 = skinned items incl. entity models (live: ender_dragon.skinning, 6cn) + block-entity overlays (6cj); general skinned clone 0x6b84e60 not decoded
- [ ] E4 Chunk geometry extractor 0x66ea3d0 anchors + materials/uniforms (6be); inner decode pending
- [x] E5a Component vocabulary: 12,836 entt type names + 94 render/anim/camera components (6dt, docs/data/entt_*) (P1) — __FUNCSIG__ strings survive
- [x] E5b entt storage layout (sparse pages 2048, packed pages 128, tombstones): EnttStorage.h + EntityContext, notes 6du
- [x] E6 Actor identity route: bodyActor 0x66D0A00 S+0xC8, item records 0xC8, passLookup 0x5ABA5C0 — 6bg (implemented in RenderMarkHook) (P1) — identity route is architecture
- [ ] E7 draw-list builders per variant located — 6u
- [x] E8 Typed ExtractionObserver: ExtractionObserver.h (Group+tag registry, veto) wired into the Item/Sky/UI insert detours (6ef); header syntax-checked, DLL not rebuilt

## F. Frame-graph renderers and passes
- [ ] F1a VV pass names and implementation lambdas — 6p, 6v
- [ ] F1b VV pass order from builder 0x55f1450 (6ar); in/out resources per pass pending
- [x] F2a Frame renderer entry 0x67c9c20 + Fancy function set — 6aa, 6ab (P2) — entry RVA moves
- [ ] F2b Fancy frame pass list (6da-6dc); Scene/HUD task body = bgfx per-view setup (view rect, 4 matrices, sort mode) 0x568CD90 (6dd); the 0xBC3.... lambdas pending [per-view matrices live-verified]
- [x] F3 No separate legacy frame renderer: Fancy shares 0x67c9c20; legacy = LegacyCubemap + legacy-UI draw helpers (6ds); GraphicsMode consumers 0x3a10d20 0x3a10e40 0x7ea7de0 0x88beee0
- [ ] F4 RTX pass names (0xbcc.. region) — 6p, 6v
- [x] F5a Pass name hash = FNV-1 64 verified, 752 hashes resolved — 6p, PassNames.h (P1) — algorithm constant
- [x] F5b Pass registry hash->name table — docs/data/render_hashes.txt, PassNames.h
- [x] F5c Pass enable/disable/reorder hook: recipe on 0xe9002e0 task list (6dg, untested in game) (P1) — hook seam stable -- 6eo: generate-time ordering also exists: stable sort by index in endFrame's names vector (0xc27ab07..); but the sole caller passes an EMPTY vector (6ep), so it is inert in 62.01

## G. Materials / shaders / textures
- [x] G1a File format: header, samplers, uniforms, passes, axes, shader records — 6ap, `tools/lce/matparse.py` (P1) — file format stable
- [ ] G1b MaterialPtr = shared_ptr<void> (SDK); async loader 0xc26caa0 + 0xF0 material-set / 0x258 objects mapped (6dr); name->info lookup pending
- [ ] G2 Variant axes + (pass, flags) permutation keys (6ap); runtime selection code pending
- [x] G3 Per-material uniform lists + extractor bind slots and names — 6ap, 6ca-6cc (RenderChunk fully resolved; ForwardPBR sampler tail variant needs matparse fix)
- [ ] G4a Sampler flag decode + sampler cache (6ax); texture/atlas management pending
- [ ] G4b Live texture census + record layout (Fancy) — 6z-2; VV/RTX RTs pending
- [x] G5 Pack reload path — docs/resourcepack-1.26.60-notes.md + memory (6bh; RVAs 1.26.51, stale) (P3) — version-stale RVAs
- [ ] G6 Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented

## H. Geometry / level renderer
- [ ] H1a RenderChunkCoordinator anchor + task name — 6x (P2) — anchor RVA moves
- [ ] H1b visibility: launcher 0x7923d50, task body 0x792e630, compute 0x791f170 (+store 0x6b0c4c0), face matrix state+0x38..0x3d, listener 0x537dab0 (6bo-6br); phase 1 voxel occupancy read (6bs, Block+0xA3 opaque flag); flood 0x6b1ba90 read (6bt); BFS queue 0x6b0d380 (6bv), render-chunk record +0x254/0x258/0x25E (6bw); RenderChunk ctor 0x7926f20 layout (6bx); event processor 0x5334850 (6by) writes depth to draw record +0x63 via 0x533f580; draw-record handle lookup 0x533f580 (6bz, 6ca: ECS guess dropped); +0x63 reader pending
- [ ] H2 Occlusion: 0x660ecd0 is the bgfx caps JSON dump (6bl), not a query pool; ChunkOccluder/SimpleOccluder are materials (6bk); real occlusion-query user not found
- [x] H3a Camera/projection/view: bgfx per-view record (0x1EAB090+viewId*0x140), CI+0x418 view, LevelRendererPlayer cameraPos/fovScale, CameraComponent FOV (6dd, 6dw) (P1) — per-view record semantics stable
- [ ] H3b Frustum/culling anchors (6bf, 6bi); 6bj: frustum_visibility is a light-scoring weight (fn 0x10f09f0), real cull fn still unfound
- [ ] H4 Per-frame constants: live ViewPositionAndTime (w = seconds), FogColor, MeshContext, GlobalRoughness read (6co); FogAndDistanceControl/sky/weather pending

## I. Lighting, actors, particles, sky, UI, post
- [ ] I1a Shadow cascade anchors — 6x
- [ ] I1b Light volumes: CPU point-light scoring (6bj) + shader inputs zLights 128B Light, zLightLookupArray, VoxelBuffer, cluster uniforms (6cd); pass code pending
- [ ] I2a Actor renderer dispatch anchors (ActorRenderDispatcher::render, DataDrivenRendererV2::tryAddActor, bodyActor) — 6bg; internals pending
- [x] I2b Bones/skeleton interface: Bones mat4[8] (0x200 B per draw), PrevBones mat4[8], PrevWorld mat4; actor extractors 0x66d9af0/0x66b2de0; skinned mesh builders (6ch); Molang CPU side not reversed (outside renderer) (P1) — bone semantics stable
- [ ] I2c Hands / held items — docs/first-person-hand-notes-1.26.60.md (6bh); 1.26.62 re-check pending
- [ ] I3 Particle pass anchor + strings — 6x
- [ ] I4a Weather pass strings — 6x
- [ ] I4b Clouds pass strings — 6x; sky/stars/celestial pending
- [ ] I5a UI render passes + context: 0x674a3a0 UI group extractor (UI/Text,Glint,Blit,Base,Sprite,Fill), 0x6664a00 UI+ImGui frame fn (6ce); ScreenRenderer internals pending
- [ ] I5b Ore UI / cohtml: glue fn 0x52d26a0 + ui_textured_premultiplied_alpha (6cf); backend upload/draw pending
- [ ] I5c Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending
- [ ] I6a TAAU + upscale pass uniforms — 6x
- [ ] I6b FSR1/DLSS anchors — 6x, 6bc, 6bh
- [ ] I6c tonemap/SSR strings — 6x (bloom/SSAO inner pending)
- [ ] I7 RTX passes: 0xbbe2d50 main declaration, 0xc28e330 G-buffer/denoiser resources, 0xbcc4b90 compute list, 0xe8403d0 context init (6cg); lambda bodies + BLAS/TLAS build pending (P3) — RTX, low priority unless RTX hardware

## J. Whole-frame control
- [ ] J1 Takeover design written against A-F: seams 1-6 with data and risks (6dy); consistent by static+live evidence, no patch exercised in game (P1) — architecture-level, survives
- [ ] J2 Startup self-check: 9 unique sigs added to Sigs.json (6dj); content checks (mask immediate, offset refs) to code in SelfTest, not built (P1) — infra; sigs re-checked per patch
- [ ] J3 Optimisation hook seams listed (6bh) + docs/PLAN_OPTIMIZATION.md; validation pending (P1) — seams are version-stable

## Execution order
1. D5 (descriptions via extractors) + E1-E4  2. C5/C5c/F5 (hash + pass capture)  3. A4-A8 (Context, handles)  4. B2-B3 (slots, submit)  5. F1-F4  6. G  7. H  8. I  9. B4-B11, A9-A13, C2-C9  10. J.

## K. Full Reverse Engineering — Complete Checklist

Every layer needed to fully reverse the rendering engine (not just chams), organized L1-L18 to match docs/RENDER_REVERSAL_PLAN.md. Rule for ticking: `[x]` only when written down in `docs/BGFX_MAP.md` (or the named doc) with RVAs/offsets AND an SDK header or hook where listed. There is no partial state: only `[x]` or `[ ]`. `[ ]` = not started. Section references (e.g. `6e`) point to `docs/BGFX_MAP.md`.

### L1. Frame, submit and the bgfx core (foundation)
- [x] L1a Frame buffer layout (view remap, matrices, draw headers, tail block, counters) — 6e, Frame.h
- [x] L1b Draw header (0x80) fields read by the executor — 6e-2
- [x] L1c bgfx::Caps (limits, flags, globals) — 6j, Caps.h
- [x] L1d Context init + thread start 0xbc63690 — 6q
- [ ] L1e Context global 0x12ae1748 + view array + semaphores — 6r (handle allocators L1h pending)
- [x] L1f frame()/swap = 0xbc66de0, handoff 0xbc65800, thread 0xbc65720 — 6r,6s
- [x] L1g Encoder::submit 0xbc5fb40 decoded: encoder layout, draw index alloc (Frame+0xDC57E8), key build, header copy — 6cq, 6cr
- [x] L1h Encoder setters: inlined stores (state +0x60, rect +0x80, binds +0x140 block) — no call sites (6cr)
- [x] L1i Encoder submit variants + reset + Frame::sort 0xbc61220 — 6cq, 6cr
- [x] L1j View struct (0x140, 256 views at ctx+0x1eab080) — 6q
- [x] L1k View matrices: s_ctx view array +0x20 (6q, live 6r)
- [ ] L1l Sorted item list Frame+0x94700 (6am); sort key bit layout partly
- [x] L1m Uniform name lookup + createUniform registry (hash table, records, allocator) — 6ag, 6ah
- [x] L1n Predefined uniforms list (14) — 6ag
- [ ] L1o Per-draw constant stream cursor + 20-byte binding records (type 0-8) — 6an; opcode set pending
- [ ] L1p Handle allocators located in Context (offsets) — 6s, 6ai (API fn map; per-allocator roles [I])
- [ ] L1q Record tables: texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 layouts — 6au; 0x78/0x80/0x130/0x68 field layouts pending
- [x] L1r Guarded paged array layout (4096 inline + chained pages, guard byte +0xC96190) — 6z
- [x] L1s Render item state bits: u64 S bit map (write mask 0-3, depth func 4-7, blend factors 12-27, equation 28-30, cull 36-37, flags) + stencil state2 + PSO key mask (6ct); enum tables dumped (6cu)
- [ ] L1t render thread proc, semaphores ctx+0x80/+0x100, surface array stride 0x700 — 6as; 0xbc63150 internals pending
- [x] L1u init/reset/shutdown: lifecycle (6di), reset entry = submit prologue + slot 60 0xe81a610 (6dn); shutdown ordering = slot 59 (not exercised live)
- [ ] L1v dynamic texture handles = reset flag 0x400000 + caps bit 0x12ADFA54&0x10 + free-list (6ei); createDynamicTexture 0xbc74a80
- [ ] L1w ranged vertex-buffer binds: only the RTX skinning range check (0xe83f1d0) found (6ei); setter API not isolated
- [ ] L1x RTX handles: pass+string anchors (6ei); fork handle/call API not isolated
- [ ] L1y upscaling: DLSS/NGX parameter set in 0xe83ec70 + 0xe8403d0, TAAU/FSR1 passes (6ei); call wrappers not isolated
- [ ] L1z SDK headers: Encoder.h and View.h added (Frame.h, Caps.h existed); Handles.h/Uniforms.h pending

### L2. RendererContextD3D12 and the D3D12 backend
- [x] L2a vtable slots named; corrections in 6aj — 6k, 6aj
- [x] L2b Slots 0-21 verified by disassembly — 6aj (table-evidence)
- [x] L2c Slots 22-49 verified — 6aj (table-evidence)
- [x] L2d Slots 50-62 verified — 6aj (table-evidence)
- [x] L2e RTX slots 54/63/64 and overrides verified — 6al
- [ ] L2f submit stage map by callees — 6t, 6af
- [ ] L2g submit: descriptor binding types (6an), sort-key program field, descriptor flush (6ao)
- [x] L2h Draw emitter found: 0xe81b720 DrawBatcher flush (DrawInstanced 0x70-stride records, DrawIndexedInstanced 0x88-stride records, ExecuteIndirect for batches); executor calls it at 0xe822e4e etc. (6ej); sig D3D12Context.drawFlush; not run in game
- [x] L2i submit stats/timers/debug overlay: stock bgfx stats text + timers inlined in slot 50 (6dh); flag bit positions to confirm live
- [ ] L2j PSO cache: builder 0xe81dc60 decodes state to D3D12 PSO desc, key mask known (6ct, 6ao); disk cache 0xe8feb10 pending
- [ ] L2k Root signature serialized in init (6ak); >=6 root params, tables 2/3, value 5 (6ao); full layout pending
- [ ] L2l Queue wrapper +0xCC9268, current list +0x19F58, submit/flush slots 8/61/62, frame-context ring — 6av; fence wait internals pending
- [ ] L2m createTexture signature + table access — 6z
- [ ] L2n State transition helper 0xe82d960 + tracker entries — 6ae
- [ ] L2o Upload tracking lists (0x48/0x18 entries @+0x1A000/+0x1A018) + destroy path slot 57 (6ba); slot 55 init (6bb); copy path + slot 56 pending
- [x] L2p Swapchain: create slot 39 (6az), reset slot 60 (6aw/6ax), present slot 6 (6ay), window table 0xC97698 (stride 0x68)
- [x] L2q TDR / device lost handling (slot 7) — 6ak
- [x] L2r createShader blob formats (CSH3/FSH5/VSH5 wrapping DXBC; no DXIL) — 6at
- [ ] L2s createProgram/destroyShader records (6au); input-layout builder ('TEXCOORD' user 0xe81xxxx) pending
- [ ] L2t RTX GPU skinning (slot 63 = 0xe83f1d0, 0x107b) anchor — 6al, 6bc
- [x] L2u DLSS/SuperSampling surface: mode select slot 60, param-key vocabulary slot 64 — 6al, 6bc
- [ ] L2v TLAS/BLAS: PrepareTLAS 0xbbe5c43, PreBlasSkinDispatch 0xbbe4399, RTXAccelerationStructure ref 0xbbf5bea (6ei); the D3D12 build call sites not located
- [x] L2w SDK header bgfx/d3d12/D3D12Context.h: rvas, offsets, six resource tables, slots (6eg); compile-checked, not in DLL build

### L3. RenderDragon: platform, tasks, scheduler, frame graph encoding
- [x] L3a BgfxContext::endFrame (0xc270460) flow — 6n
- [x] L3b GraphicsTasks Render lambda 0xc267200 + chain — 6ab, 6ac
- [x] L3c Execute 0xc25fc50 and Wait for previous frame 0xc25f960 — 6ac
- [ ] L3d Task scheduler 0xc25b1a0 call map — 6ac; queue layout pending
- [ ] L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending
- [ ] L3f DragonFrameResources: +0x298/+0x2A0 vector<shared_ptr<Task>> found via endFrame/0xe9002e0 (6cx); remaining fields pending
- [ ] L3g IntraFrameAllocator: wrapper over pooled arena via 0xa78940 blocks with refcounted control (6cy); exact field list pending
- [ ] L3h Declarator<RenderContext> + five Bind* dependency kinds + module names — 6aq; registration call addresses pending
- [ ] L3i drawutils pass-declaration templates (178 signatures) — 6aq; per-pass bodies pending
- [x] L3j HashedString hash = FNV-1a 64, names built inline — 6o
- [ ] L3k Deferred Texture/Buffer Transactions flush 0x6632bf0 (two labelled vector<Transaction*>, vtbl slot1 run + slot0 delete) (6dv); aliasing not found
- [ ] L3l 0xc273420 prologue + stages: 51 callees, hot helpers mapped (6n-2); stage split pending a live breakpoint on 0xc27f940
- [ ] L3m per-pass loop located (0xc277e8c..0xc2793fe), dependency records = 24/40-byte vectors (6cz); body fields pending
- [x] L3n Dispatch 0xe9002e0 + task classes + live pass order/names (6cx, 6da, 6db)
- [ ] L3o Threading: draw executor runs as parallel jobs, one command list per job (this+0x19F60[job]), job slices of the sorted list (6cp); encode-thread side pending [RVAs in 6cp are 60.05, see 6cw]
- [ ] L3p dragon/Tasks.h (task list, class vtables, name offsets, taskName) + PassNames.h written (6eg); the per-frame enumeration detour on 0xE9002E0 not written

### L4. FrameBuilder layer (mce::framebuilder)
- [x] L4a vtable group slots + endFrame — FrameBuilder.h
- [x] L4b Catalog of 62 types / 50 clones with group — DescriptionClones.h, RENDER_CATALOG
- [x] L4c Clone calling convention + Nametag clone — 6l
- [x] L4d BatchActor description layout — 6d
- [x] L4e Nametag description (0x98) typed in Descriptions.h — 6m
- [ ] L4f ChunkGeometry description: extractor + pointer route (6be); field layout pending (needs live capture)
- [ ] L4g ChunkOccluders: thin clone 0x5369920 -> Item vslot 0x378 tag 4, handler 0x6646a89 creates "ChunkOccluder" render object, fields +0x30..+0x48 (6dx); field types pending
- [ ] L4h Crack: fat clone 0x539fff0 builds from a destroy-progress list at B+0x3280 (node+0x10 pos, +0x20 progress float) (6ea); final description fields pending -- 6ga: description fields {mesh, texture, camera record, stage, flags} typed in Descriptions.h; the 6ea list attribution corrected.
- [ ] L4i ItemInHand: thin clone 0x531b180 -> tag 6 -> extractor 0x6698e30; fields +0x28 ptr, +0x38 mat4, +0x78/+0x7A flags, +0x11C, +0x158.. blocks, +0x1D0/+0x1D4 (6dz)
- [ ] L4j SkinnedMesh: general clone 0x6b84e60 fields +0x10/+0x18/+0x20/+0x30/+0x38/+0x60/+0x74-76/+0x108-118 and second producer 0x4e39f20 (6ec); field meanings pending -- 6gc: the description itself is now complete (every field from constructor 0x668d350); producers' bodies still partial.
- [x] L4k MeshFallback description head typed (Descriptions.h); tail to 0x1d0 pending -- DONE 6fz: all 0x1D0 bytes written by the fully reversed constructor 0x668b850.
- [ ] L4l BlockSelectionOverlayBlockEntity: fat clone 0x539b7c0, Item tag 8, built from the selected block position + region block-entity lookup (6eh); description fields pending
- [ ] L4m EnvironmentalText/UIText: shared clone 0xe71330 -> Item vslot 0x378 or UI vslot 0x368; text = shared string at desc+0x90/0x98/0xA0, font obj +0xB0, flag +0x75 (6eb); +0x60 struct pending
- [ ] L4n Sky / Stars description (tag 5; fields pending) — 6w
- [ ] L4o Sky-group clones: EndSky 0x53707a0 tag3, Celestial 0x5370b20 tag7, Cubemap 0x660b720 tag2 (thin); LegacyCubemap 0x660b1a0 tag4 (fat, texture variant select) (6ed); fields pending
- [ ] L4p Clouds, Weather, Atmosphere — clone kind/group/tag table 6ee; fields pending
- [ ] L4q Particle, FlameBillboard — clone kind/group/tag table 6ee; fields pending
- [ ] L4r Shadow, PlayerVision, VolumetricFog — clone kind/group/tag table 6ee; fields pending
- [ ] L4s FullscreenEffect, BlitFlipbookTexture — clone kind/group/tag table 6ee; fields pending
- [ ] L4t UI descriptions (Mesh, Gameface, HudIcon) — clone kind/group/tag table 6ee; fields pending
- [ ] L4u Light descriptions (Ambient, Directional, Point) — clone kind/group/tag table 6ee; fields pending
- [ ] L4v Voxel/TransitioningVoxel volumes, ShadowAtlasFrame, SkyAmbientSamples — clone kind/group/tag table 6ee; fields pending
- [ ] L4w gamecomponents (GameplayMetadata, ServerGraphicsOverrideParameters, EditorHighlightConfiguration) — clone kind/group/tag table 6ee; fields pending
- [ ] L4x Editor group descriptions (gizmos, block volumes, render plane, selection cursor) — clone kind/group/tag table 6ee; fields pending
- [ ] L4y Descriptions.h: Nametag, MeshFallback head; BatchActor in FrameBuilder.h
- [ ] L4z Group tag enums for all six groups added (FrameBuilder.h) — 6w; typed hooks pending

### L5. Extractors and the registry (description -> render objects)
- [x] L5a Item visitor jump table with verified tag identities — 6w
- [ ] L5b Tag 0/4: entries (6ci); live field decode (6cv: transform, colours, pointer arrays); per-field names partial
- [ ] L5c Tag 1/5 and 2/3/7/9: entries (6ci); tag 7 and 1 fields decoded from live dumps (6cv: model matrix pair, AABB, material node at +0x140)
- [ ] L5d Tag 6/8/10 forwarders: entries 0x6647320 / 0x66473e6 / 0x6647383 (6ci); GlowInkSign inside 8
- [ ] L5e BatchActor extractor callee map — 6u (inner decode pending)
- [ ] L5f Tag 7 = skinned items incl. entity models (live: ender_dragon.skinning, 6cn) + block-entity overlays (6cj); general skinned clone 0x6b84e60 not decoded
- [ ] L5g Chunk geometry extractor 0x66ea3d0 anchors + materials/uniforms (6be); inner decode pending
- [x] L5h Component vocabulary: 12,836 entt type names + 94 render/anim/camera components (6dt, docs/data/entt_*)
- [x] L5i entt storage layout (sparse pages 2048, packed pages 128, tombstones): EnttStorage.h + EntityContext, notes 6du
- [x] L5j Actor identity route: bodyActor 0x66D0A00 S+0xC8, item records 0xC8, passLookup 0x5ABA5C0 — 6bg (implemented in RenderMarkHook)
- [ ] L5k draw-list builders per variant located — 6u
- [x] L5l Typed ExtractionObserver: ExtractionObserver.h (Group+tag registry, veto) wired into the Item/Sky/UI insert detours (6ef); header syntax-checked, DLL not rebuilt

### L6. Frame-graph renderers and pass classes
- [ ] L6a VV pass names and implementation lambdas — 6p, 6v
- [ ] L6b VV pass order from builder 0x55f1450 (6ar); in/out resources per pass pending
- [x] L6c Frame renderer entry 0x67c9c20 + Fancy function set — 6aa, 6ab
- [ ] L6d Fancy frame pass list (6da-6dc); Scene/HUD task body = bgfx per-view setup (view rect, 4 matrices, sort mode) 0x568CD90 (6dd); the 0xBC3.... lambdas pending [per-view matrices live-verified]
- [x] L6e No separate legacy frame renderer: Fancy shares 0x67c9c20; legacy = LegacyCubemap + legacy-UI draw helpers (6ds); GraphicsMode consumers 0x3a10d20 0x3a10e40 0x7ea7de0 0x88beee0
- [ ] L6f RTX pass names (0xbcc.. region) — 6p, 6v
- [x] L6g Pass name hash = FNV-1 64 verified, 752 hashes resolved — 6p, PassNames.h
- [x] L6h Pass registry hash->name table — docs/data/render_hashes.txt, PassNames.h
- [x] L6i Pass enable/disable/reorder hook: recipe on 0xe9002e0 task list (6dg, untested in game)

### L7. Materials and shaders
- [x] L7a File format: header, samplers, uniforms, passes, axes, shader records — 6ap, tools/lce/matparse.py
- [ ] L7b MaterialPtr = shared_ptr<void> (SDK); async loader 0xc26caa0 + 0xF0 material-set / 0x258 objects mapped (6dr); name->info lookup pending
- [ ] L7c Variant axes + (pass, flags) permutation keys (6ap); runtime selection code pending
- [x] L7d Per-material uniform lists + extractor bind slots and names — 6ap, 6ca-6cc (RenderChunk fully resolved; ForwardPBR sampler tail variant needs matparse fix)
- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending
- [ ] L7f Live texture census + record layout (Fancy) — 6z-2; VV/RTX RTs pending
- [x] L7g Pack reload path — docs/resourcepack-1.26.60-notes.md + memory (6bh; RVAs 1.26.51, stale)
- [ ] L7h Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented

### L8. Textures, atlases and resources
- [ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending
- [ ] L8b Atlases (terrain, items), mipmaps and compression pending
- [ ] L8c Async upload, texture handle lifetime pending
- [ ] L8d Render targets and their formats pending
- [x] L8e Dynamic-texture-handle mechanism of the fork — 6ei (reset flag 0x400000)
- [x] L8f Pack reload path — docs/resourcepack-1.26.60-notes.md (6bh; version-stale RVAs)

### L9. Geometry production: chunks, meshing, buffers
- [ ] L9a RenderChunkCoordinator anchor + task name — 6x
- [ ] L9b visibility: launcher 0x7923d50, task body 0x792e630, compute 0x791f170 (+store 0x6b0c4c0), face matrix state+0x38..0x3d, listener 0x537dab0 (6bo-6br); phase 1 voxel occupancy read (6bs, Block+0xA3 opaque flag); flood 0x6b1ba90 read (6bt); BFS queue 0x6b0d380 (6bv), render-chunk record +0x254/0x258/0x25E (6bw); RenderChunk ctor 0x7926f20 layout (6bx); event processor 0x5334850 (6by) writes depth to draw record +0x63 via 0x533f580; draw-record handle lookup 0x533f580 (6bz, 6ca: ECS guess dropped); +0x63 reader pending
- [ ] L9c Occlusion: 0x660ecd0 is the bgfx caps JSON dump (6bl), not a query pool; ChunkOccluder/SimpleOccluder are materials (6bk); real occlusion-query user not found
- [x] L9d Camera/projection/view: bgfx per-view record (0x1EAB090+viewId*0x140), CI+0x418 view, LevelRendererPlayer cameraPos/fovScale, CameraComponent FOV (6dd, 6dw)
- [ ] L9e Frustum/culling anchors (6bf, 6bi); 6bj: frustum_visibility is a light-scoring weight (fn 0x10f09f0), real cull fn still unfound
- [ ] L9f Per-frame constants: live ViewPositionAndTime (w = seconds), FogColor, MeshContext, GlobalRoughness read (6co); FogAndDistanceControl/sky/weather pending

### L10. Level renderer, camera, culling and scene setup
- [x] L10a LevelRenderer::takePicture (virtual) — 6x
- [ ] L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound
- [ ] L10c viewport and render-resolution selection, dynamic resolution pending
- [ ] L10d FOV and screen-space transforms — read from per-view record V+0x50 projection (6dd, live FOV ~76.9 deg)

### L11. Lighting, shadows and environment
- [ ] L11a Shadow cascade anchors — 6x
- [ ] L11b Light volumes: CPU point-light scoring (6bj) + shader inputs zLights 128B Light, zLightLookupArray, VoxelBuffer, cluster uniforms (6cd); pass code pending
- [ ] L11c ambient/sun/moon parameters, SSAO/SSR parameters, fog/volumetric parameters pending
- [ ] L11d probes/IBL, RT lighting pending

### L12. Actor rendering above the framebuilder
- [ ] L12a Actor renderer dispatch anchors (ActorRenderDispatcher::render, DataDrivenRendererV2::tryAddActor, bodyActor) — 6bg; internals pending
- [x] L12b Bones/skeleton interface: Bones mat4[8] (0x200 B per draw), PrevBones mat4[8], PrevWorld mat4; actor extractors 0x66d9af0/0x66b2de0; skinned mesh builders (6ch); Molang CPU side not reversed (outside renderer)
- [ ] L12c Hands / held items — docs/first-person-hand-notes-1.26.60.md (6bh); 1.26.62 re-check pending
- [ ] L12d nametags (0x1127330/0x11276b0) — 6l, 6m (decoded); skin shadows blob pending

### L13. Particles, weather, sky and clouds
- [ ] L13a Particle pass anchor + strings — 6x
- [ ] L13b Weather pass strings — 6x
- [ ] L13c Clouds pass strings — 6x; sky/stars/celestial pending
- [ ] L13d end sky / cubemap — 6ed (clones found, fields pending)

### L14. UI rendering
- [ ] L14a UI render passes + context: 0x674a3a0 UI group extractor (UI/Text,Glint,Blit,Base,Sprite,Fill), 0x6664a00 UI+ImGui frame fn (6ce); ScreenRenderer internals pending
- [ ] L14b Ore UI / cohtml: glue fn 0x52d26a0 + ui_textured_premultiplied_alpha (6cf); backend upload/draw pending
- [ ] L14c Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending
- [ ] L14d UI descriptions (Mesh, Gameface, HudIcon, UIText) — clone kind/group/tag table 6ee; fields pending

### L15. Post-processing, upscaling, HDR
- [ ] L15a TAAU + upscale pass uniforms — 6x
- [ ] L15b FSR1/DLSS anchors — 6x, 6bc, 6bh
- [ ] L15c tonemap/SSR strings — 6x (bloom/SSAO inner pending)
- [ ] L15d DLSS wrapper vtable slots 60 optimal-settings / 64 evaluate — 6bc, 6al

### L16. Ray tracing (RTX)
- [ ] L16a RTX pass names and resources — 6cg, 6p
- [ ] L16b TLAS/BLAS build and update — 6ei (call sites not located)
- [ ] L16c RT shaders and denoiser — 6cg (lambda bodies undecoded)
- [ ] L16d RTX slots in the bgfx fork — 6al (slots 54/63/64)

### L17. Platform glue and threading
- [ ] L17a swapchain/DXGI/present and resize (partly hooked) — 6av, 6ay, 6az, 6aw
- [ ] L17b GDK integration pending
- [ ] L17c GPU timers and memory budget — 6dh (submit stats/timers)
- [ ] L17d device lost/TDR — 6ak (slot 7)
- [x] L17e exact thread model (game thread, dragon task threads, bgfx render thread) — 6as, 6ac
- [ ] L17f frame pacing/vsync — 6ay (SyncInterval), 6dn (slot 60 present interval)
- [ ] L17g async init/shutdown ordering — 6di
- [ ] L17h graphics options plumbing (OptionSync) pending

### L18. Whole-frame replacement (Level 3 goal)
- [ ] L18a Takeover design written against A-F: seams 1-6 with data and risks (6dy); consistent by static+live evidence, no patch exercised in game
- [ ] L18b Startup self-check: 9 unique sigs added to Sigs.json (6dj); content checks (mask immediate, offset refs) to code in SelfTest, not built
- [ ] L18c Optimisation hook seams listed (6bh) + docs/PLAN_OPTIMIZATION.md; validation pending

### K-Priority. Version-Stable Priorities (do these first)

A checklist of items that are version-stable and high-value, so they survive across patches. Mark each as `[ ]` since none are version-locked yet. Each item notes why it's version-stable:

- [x] K-P1 Render stack architecture and layer boundaries (survives all versions) — BGFX_MAP 0, stack diagram
- [x] K-P2 Pass name hash algorithm: FNV-1 64, offset basis, prime (survives all versions) — BGFX_MAP 6o/6p
- [x] K-P3 entt component vocabulary and render component names (survive via __FUNCSIG__ strings) — BGFX_MAP RENDER_CATALOG
- [ ] K-P4 bgfx core concepts: Frame, View, RenderItem, Caps (Mojang fork changes slowly) — BGFX_MAP 6e, 6j; audit 6ek fixed Frame.h view structs (stride 0x140); header +0x38/+0x40 fields still unverified
- [x] K-P5 D3D12 backend interface: 65 vtable slots, submit signature (stable across bgfx versions) — BGFX_MAP 6f, 6k
- [ ] K-P6 Function behavior/semantics (audit 6ek: 'submit takes Frame* in rdx' is [I] until the prologue is re-read): submit takes Frame* in rdx, endFrame takes BgfxFrameBuilder in rcx (version-stable) — BGFX_MAP 6e-2, 6n
- [ ] K-P7 RVA/slot database per version: OffsetProvider.h + Sigs.json (infrastructure for fast re-mapping) — existing
- [x] K-P8 String-based discovery via srcloc.py (__FUNCSIG__ substring, survives RVA moves) — existing tools
- [ ] K-P9 Startup validation: fail loudly if slot doesn't point into .text or sig missing — existing convention


## M. Full-RE method: function dossiers, acceptance tests, definition of done (added after the audit 6ek)

Goal: reverse the renderer so that anything in it can be handled without being handed an RVA. RVAs and hooks are only the entry points. Text from other agents is a hypothesis list; the disassembly and live reads are the ground truth (audit: BGFX_MAP 6ek).

### M1. Function inventory and dossiers (the unit of work)
- Database: `docs/data/functions.tsv` (rva, layer, name, status D0 unseen / D1 named+described / D2 dossier with pseudocode / D3 verified live or in game). Seeded with 68 structural functions (D1); 0xe81b720 is D2.
- Tool: `tools/sigs/dossier.py <rva> [--iface d3d12cl] --out docs/functions` writes the mechanical half (frame, per-argument field offsets, stack args, callees, vtable calls with real D3D12 method names, strings, loops with strides, jump tables, constants). The analyst half (purpose, real signature, pseudocode, structs, enums, version-stable anchors, verification) is filled by hand, every claim tagged [V]/[I]/[?].
- [x] M1a Dossier tool written (tools/sigs/dossier.py) and used on 0xe81b720: docs/functions/e81b720.md is the first complete D2 dossier (pseudocode, signature, structs, verification gaps)
- [ ] M1b Inventory per layer: list EVERY function of each region (L1 bgfx core ~290, L2 D3D12 ~1,900, L3 RenderDragon ~980, L4/L5 BgfxFrameBuilder ~2,300, L6 frame-graph renderers ~3,600) into functions.tsv as D0 with size, callers, strings; then classify (structural / helper / lambda / thunk) -- PROGRESS: inventories exist for L1 (323), L2 (1854), L3 (978), L4/L5 region 0x6600000-0x67e0000 (6391), L6 region 0x5500000-0x5700000 (5567, ~0xF0000 noise), see BGFX_MAP 6el. Remaining: annotate/classify (names, layer split by call graph), add rows to functions.tsv for the big render functions.
- [ ] M1c Dossiers (D2) for every structural function of L1-L3 first: Context::init/frame, Encoder::submit family, Frame::sort, submit 0xe82e230, executor 0xe821120 + wrapper, PSO builder, endFrame 0xc270460, generate 0xc273420, GraphicsTasks Render/Execute, dispatch 0xe9002e0, the five task bodies -- PROGRESS: D2 dossiers done: submit (docs/functions/bc60740.md), draw flush (e81b720.md); also D2: executor, PSO builder, submit 0xe82e230, Frame::sort, endFrame (generate 0xc273420 is D1). Also D2: Context::frame 0xbc66de0, dispatch 0xe9002e0. Also D2: init 0xbc63690, handoff 0xbc65800, Execute 0xc25fc50 (Render lambda 0xc267200 D1). Also dossiered: renderFrame 0xbc63150 (D2), thread proc 0xbc65720 (D2); D2 after decode: shutdown sequence 0xbc660a0 + frame(capture) 0xbc65800 (6eq), task runner 0xc25fe20, 0xc280010 (insertion sort) + 0xc280ca0 (stable_sort); Command interpreter 0xbc68e40 + byte table done (6er). Argument layouts for bytes 2,3-8,12,13,27-34 done (6es). createTexture byte 14 decoded (6et). BgfxFrameBuilder::endFrame stage map done (6ev). 0xc25f960 and 0x6632bf0 dossiered (6ew). bytes 15,17,19 read (6fa: 17 = resizeTexture). Slots 10-34 named with evidence (6fb). Resource tables re-derived, index/vertex swap and framebuffer stride fixed (6fc). Next: re-read 6cs header fields, slots 39-45, the 6 drain blocks of 0xbc660a0, and the generate per-pass loop; then L4/L5 dossiers (endFrame 0x66232b0, extractors). FULLY REVERSED (instruction-complete source): Frame::sort, EncoderImpl::submit (6fd). Census: 838 functions on the direct-call frame path, 22 at D2 (docs/data/frame_path_functions.tsv, tools/sigs/closure.py). Also fully reversed (6fe): EncoderImpl::discard 0xbc60d10, RenderBind storage grow 0xbc7a7c0, side-table copy 0xbc60f10; bx::HashMurmur2A::add 0xbc76610 identified. Sibling submit forms reversed by diff (6ff, docs/functions/submit_variants.md): dispatch complete; custom item and frame-params item have open argument meanings. 6fg-6fh: executor item classes by key bits (compute / draw / custom) and the pass-task encode + render-thread body pair (0x568b9e0, 0x568bcd0) fully reversed; branch A/B of 6cs re-read as compute subtypes. 6fi: executor draw path head transcribed (occlusion visibility, scissor, state tracking); pass-class template confirmed across four bodies. 6fj: draw path second part transcribed (root signature, descriptor heaps, currentState, streams). 6fk: draw path third part (layouts, PSO call, batch-compatibility test, bind-state cache). 6fl: executor draw path transcribed end to end (descriptor tables, dynamic state, constants, indirect draws, batch append); holes: bind-cache miss, setPredefined, helper bodies. 6fm: setVertexBuffers 0xe81b4d0 fully reversed; constant commit 0xe81e1c0 structure reversed. 6fn: rendererUpdateUniforms 0xbc6a9d0 and updateUniform slot 46 fully reversed; uniform path of a draw complete. 6fo: predefined uniforms (14 types, program slots at +0x10) transcribed; remaining executor holes: bind-cache miss (descriptor build), PSO builder body. 6fp: bind-cache miss descriptor build structure (10 binding types, buffer and ranged cases); Binding struct typed in Encoder.h. 6fq: all ten binding types named; 0xA32178 table re-identified as shader buffers. 6fr: PSO key reversed (13-argument signature, full Murmur2A key); PSO desc build on a cache miss still open.
- [ ] M1d Dossiers for every FrameBuilder clone and visitor handler (L4/L5) and every extractor (chunk, batch actor, item-in-hand, skinned, nametag, particle, sky) -- PROGRESS: ItemInHand extractor 0x6698e30 dossier started (D1+, docs/functions/6698e30.md); BatchActor extractor 0x66d9af0 dossier (D1+, layouts live-verified); others (chunk, skinned, nametag, particle, sky, clones, visitors) not yet 6fu: all 21 thin insert clones fully reversed (one template, docs/functions/insert_thin_clones.md); fat clones, visitors and the other extractors still open. 6fv: Nametag fat clone 0x1127330 and constructor 0x668b6e0 fully reversed. 6fw: PlayerVision fat clone 0x53e62b0 reversed. 6fx: Shadow clone 0x53e6c30 = blob shadows drawn through MeshFallback. 6fy: MeshFallback insert 0x4def480 main path. 6fz: MeshFallback constructor 0x668b850 fully reversed. 6ga: Crack clone 0x539fff0 phases reversed, description typed. 6gb: Clouds clone structure + constructor 0x668e940 fully reversed. 6gc: SkinnedMesh constructor 0x668d350 fully reversed. 6gd: EnvironmentalText and UIText constructors fully reversed. 6ge: BlockSelectionOverlay constructor 0x668d990 fully reversed. 6gf: Sky constructor 0x668c910 fully reversed; Stars description read inline. 6gg: Item visitor dispatch reversed (tag -> handler table). 6gh: all six group insert wrappers and visitors mapped (dispatch tables, case entries). 6gi: PlayerVision and UIText visitor cases read (queue into pass vector / direct UI text draw). 6gj: all 52 visitor cases mapped to their first handler. 6gk: Clouds extractor 0x67375a0 structure. 6gl: Particle extractor 0x67417f0 structure. 6gm: Weather extractor 0x6745440 head; 6gj Sky row corrected. 6gn: visitor case map re-scanned with per-case bounds (7 cases corrected). 6go: FlameBillboard and Gameface extractors structure. 6gp: Editor block-volume extractor structure; census 955 functions, 82 at D2. 6gq: shared helpers 0x4def080, 0x4dfb570, 0x5aba5c0 fully reversed (the last is a thread-local getter, not a pass lookup). 6gr: uniform writer 0x5679db0 fully reversed. 6gs: 0x675e440 = ResourceCache::get, fully reversed. 6gt: loader 0xbcbf730 + job body fully reversed; drain open. 6gu: material load 0xe86b730 fully reversed. 6gv: material repo, file load, instance ctor fully reversed. 6gw: material.bin header + encryption reversed. 6gx: material.bin body format + per-stage shader pick. 6gy: initFromMaterial phases, uniform types, bgfx shader/program creation. 6hg: material.bin crypto helpers resolved (SHA-256, AES-256-GCM). 6hh: loader per-frame tracked merge (0xc288990 from endFrame) and shutdown path found; job runner still open. 6hi: per-frame pending-job merge 0xc288880 -> 0x67591e0 (7 loaders); 6hj: job runner found (processPending 0x6622610 -> runJobs 0x12893d0): async load path closed.
- [ ] M1e Pass lambdas (L6): the 35 VV/RTX lambdas + Fancy pass bodies, each with in/out resources -- PROGRESS (6gz): VV pass-group builder table (which builder declares which pass); ScreenDraw path fully mapped (declare 0xbbbd3d0, build 0xbc37320, shared execute body 0xbc04dc0, submit 0xbcc38e0); ColorPostProcess in/out read. Remaining: the non-ScreenDraw pass bodies (deferred, SSR, TAAU, RTX, voxel) and their resources. 6ha: execute-body table for every VV group (3 shapes), DirectionalLightingPass reversed, submit variant corrected. 6hb: SSR (ScreenDraw), voxel upload (0xbc0ac20) and RTX denoise (0xbc080c0 -> 0xbcc4b90) bodies found: every VV group now has its execute body. Remaining: full reads of each body and per-pass in/out. 6hr: submitPass inline path reversed (setTransform into the Frame matrix cache, Encoder::submit).
- [ ] M1f Every D2 dossier gets a D3 pass: one live poll-only read or in-game check per claim that can be checked (never a debugger/breakpoint session: it crashed the game twice) -- UNBLOCKED 2026-11-14: bridge connected, user in a populated server (client DLL not injected). First two passes (6ij, 6il): frame pair spacing 0xE749C0, counters, backbuffer 1920x1137, 514 items, draw header fields (all sentinels), index buffer, vertex buffer and vertex layout records followed end-to-end for one draw. Remaining: every other D2 claim (see 6ij list; 6il buffers/layout, 6im texture records, 6in program/shader records done). PARTIAL = NOT DONE.

### M2. Structures: every struct has a header with confirmed offsets
- [x] M2a Frame/View/RenderDrawHeader/Encoder/Caps (Frame.h corrected by the audit; header +0x38/+0x40/+0x4C/+0x7A meanings still open; `Frame+0x8B4700` 0x540-byte RenderBind records, `Frame+0x14300` flag array, `Frame+0x14700` sort keys to add to Frame.h) -- 6fj: header +0x38 = uniformEnd, +0x40 = startIndex, +0x4C = numVertices, +0x7A = occlusionQuery are now decided; RenderDraw / RenderStream / RenderCompute are typed structs with static_asserts compiled in the client. 6hs: View struct offsets resolved statically (one layout, two bases 0x10 apart; asserted in View.h). DONE (6ht): the listed draw bytes were already typed except +0x65..+0x67 and +0x7C..+0x7F, which no reversed reader touches (padding).
- [x] M2b D3D12: DrawBatcher (rdi of 0xe81b720: counts +0x10, arrays +0x18, signatures +0, caches +0x10C0/+0x1110/+0x1120/+0x1128, flag +0x1164, barrier table +0xF28..+0x1040) and its two draw record layouts (0x70 / 0x88) as headers; job context ([ctx+0x30] = command list) -- DONE (6ia): DrawBatcherOffsets + JobContextOffsets in D3D12Context.h, records typed, offsets in both assertion lists (168 pass).
- [ ] M2c Every description type (62) as a struct with confirmed fields (Descriptions.h), starting with those whose extractor is decoded -- PROGRESS: RenderNametagDescription complete (every field written by its fully reversed constructor, 6fv). RenderPlayerVisionDescription (0x14) typed (6fw). RenderMeshFallbackDescription (0x1D0) complete (6fz). RenderCrackDescription typed (6ga). RenderCloudsDescription (0xA8) typed (6gb). RenderSkinnedMeshDescription (0x1D0) typed (6gc). RenderEnvironmentalTextDescription (0xE8) and RenderUITextDescription (0x60) typed (6gd). BlockSelectionOverlay description (0xB8) typed (6ge). RenderSkyDescription (0xB0) and RenderStarsDescription typed (6gf). RenderWeatherDescription (0x130) typed with every uniform named (6ib); method for naming extractor uniforms recorded. RenderParticleDescription (0xB0) typed (6ic). RenderFlameBillboardDescription (0xF8) and RenderGameFaceDescription (0x78) typed (6id); tools/sigs/descscan.py added. RenderCubemapDescription (0xC0) typed from its producer (6ie); tools/sigs/producerscan.py added. 6if: raw producer stores for all 18 thin clones in docs/data/producer_fields.txt (to cross-check with extractor reads before typing). RenderChunkOccludersDescription (0x50) confirmed producer + extractor (6ig). RenderAtmosphereDescription (0x138, field uniforms unresolved) and RenderBlockChangesDescription (0x18) typed (6ih); 27 of 62 typed (AimAssistHighlight min 0x68, EditorHighlight 0x58, LightAmbient 0x18, LightDirectional 0x28, Light tag 2 0x84, Light tag 4 0x50, Light tag 3 0x108, 6ih), 35 left (RenderBlitFlipbookDescription 0xA0 with 0x40-byte elements, 6ih; unread tails marked [?]). Atmosphere is repacked into a stack block by the visitor; corrected 6ih: it is queued into a Sky-pass vector (pass+0x548, 0x58-byte elements); uniform names are in the pass's reader of that vector (next target: readers of pass+0x548). Description layouts are guarded by static_asserts only: layout_asserts.json is keyed by Sigs.json function anchors and the visitors have none yet.
- [x] M2d Batch instance / actor record / item payload (0xC8) full layouts -- PROGRESS (6hc): 0xC8 item = DrawItem index record, typed with static_asserts (DrawItem.h); batch Instance 0x48 typed from the 6d capture (FrameBuilder.h). 6hd: every pool element typed (DrawItem.h). 6he: the 0x300 record is a 0x2C0 RenderControllerMesh (typed). 6hk: transform variant alternatives typed. 6hl: render-state block fully named (blend, cull, depth, primitive, stencil). 6hp: the "material record" is the geometry reference (vertex streams, index buffer variant, start index, index count), typed. 6hq: vertex stream reference typed. DONE (6hr): all layouts typed with static_asserts; residual unknown-meaning fields marked [?] in the headers (geometry +0x50 has no reader in the bind/submit path). (6hm: stencil face typed; 6hn: geometry sub-object = MeshData with 12 streams and bounds, matches the live capture). 6ho: streams = mce::MeshData members, layout asserted in MeshData.h. Remaining: the material record's 24-byte tail. 6hf: material holder {MaterialInstance*, UniformBlock}, slot entries and the 4-way material reference variant.
- [x] M2e Resource records: texture 0xB8, vertex 0x78, index 0x80, framebuffer 0x130, program 0xF8, shader 0xB8, uniform 0x68 (field by field) -- PROGRESS (6fc): table bases, strides and counts re-derived (index 0x93A178/0x78, vertex 0x9B2178/0x80, framebuffer 0xA32178/0x78, shader 0xAAA178/0xB8, program 0xB62178/0xF8, texture 0xBDE178/0xB8, uniform 0xC97698/0x68); the strides in this line title are partly wrong; field-by-field layouts not done 6fk: vertex buffer record +0x78 = layout handle; layout record = 0x54 bytes. 6fl: index/vertex buffer records: GPU address +0x58, size +0x60; program +0x00/+0x08 shaders, +0xF0 numPredefined; shader +0x08 constant buffer, +0xAE constant size; batch records typed (BatchDraw 0x70, BatchDrawIndexed 0x88). 6fo: program record predefined slots typed (PredefinedUniform, 28 x 8 bytes at +0x10). 6fq: the 0xA32178 table (0x78) is shader buffers, not framebuffers; framebuffer location open. 6fr: framebuffers = ctx+0xC97698 (0x68: colour handles +0, depth +0x10, window +0x18, count +0x32); vertex layouts = ctx+0xC96198, 64 x 0x54; texture overflow pages at ctx+0xC96178. 6hu: index and vertex buffer records typed field by field (BufferRecord, from BufferD3D12::create); RTX create overrides mapped. 6hv: shader record typed (ShaderRecordLayout). 6hw: program record complete (ProgramRecordLayout). 6hx: framebuffer record typed (window path) and vertex layout = bgfx::VertexLayout verbatim. 6hy: framebuffer record complete (slots 39/40/41). 6hz DONE: texture record typed (tail fields, overflow paging); every record type now has a layout struct with static_asserts; the texture view block +0x20..+0x97 was left opaque there, then resolved LIVE in 6im (D3D12_RESOURCE_DESC +0x08, SRV desc +0x40, UAV desc +0x68; header edited, pending the batch build).

### M3. The six capabilities as acceptance tests (each is a written procedure + evidence, not just notes)
- [ ] M3a Data structures: every struct of M2 compiles as a header and a startup self-check validates sizes/offsets that can be validated (static_asserts + SelfTest)
- [ ] M3b Control flow: one frame traced from game logic to D3D12 submit with every function on the path having a D2 dossier (the pipeline diagram in section K/BGFX_MAP 0 becomes a call-graph table with arguments passed at each hop) -- PROGRESS: docs/FRAME_CALLGRAPH.md (thread A + thread B tables with args per hop; open: M1d groups, A5/A7/B3 D1, two [?] links)
- [ ] M3c Frame graph: add/remove/reorder a pass safely (recipe 6dg/6dy, TaskDispatchHook + dragon/Tasks.h written but never built or run; needs the build + in-game test)
- [ ] M3d Actor to draw: identify which draw renders which actor (route 6bg + RenderMarkHook exists; re-validate on 1.26.62.01 against the new flush 0xe81b720 and the Encoder::submit seam)
- [ ] M3e Edit draws at submit: read/modify every draw record before the GPU (flush 0xe81b720 records 6ej; needs the header-to-record mapping and an in-game test)
- [ ] M3f Whole-frame replacement: drive a frame ourselves or feed a custom renderer (needs M1c-M3e) -- PROGRESS (6fg/6fh): the native seam is found: a custom item (Encoder::submitCustom(view, fn, user), key bit 53) makes the D3D12 executor call fn(user, ctx) on the render thread in view order with the command list; untested in game, ctx layout partly inferred

### M4. Version resilience (do while reversing, not after)
- [ ] M4a For every D2/D3 function record the version-stable anchor (string / __FUNCSIG__ / unique sig) beside the RVA (Sigs.json + dossier "anchors" block); new sigs so far: Encoder{submit,reset,frameSort}, FrameGraph{endFrame,generate,taskDispatch,viewSetupTask}, D3D12Context{drawExecutor,psoBuilder,drawFlush}
- [ ] M4b Behaviour notes written without RVAs (what the function does) so they survive a patch: one paragraph per structural function in its dossier -- PROGRESS: docs/BEHAVIOR_NOTES.md covers every function that has a D2 dossier (bgfx core, D3D12 backend, frame graph/GraphicsTasks); not yet for M1d/M1e items
- [ ] M4c Startup validation: slots point into .text, sigs found, content checks (mask immediates, offset refs); see L18b -- PROGRESS: content checks exist: docs/data/layout_asserts.json + tools/sigs/layoutcheck.py (55 assertions, pass on 62.01 and 60.05, report the moved values on 51.01) and RenderLayoutAsserts.h run from SelfTest world phase (Release build OK, not run in game). Every newly reversed function adds its constants to both lists.
- [ ] M4d Port check: re-run the dossier tool on the previous version's exe (BS_EXE) for every D2 function to measure what moved (RVA, offsets, slots) -- PROGRESS: sigs of the render functions audited on 50.04/51.01/60.05/62.01 (docs/data/port_check_render_sigs.tsv, BGFX_MAP 6ey); dossier tool not yet re-run on the older exes

### M5. Standing rules while reversing
- Static + plain-memory polling + offline snapshots only; no debugger attach or breakpoints (game crashed twice). No patches without an explicit go-ahead.
- Every new fact gets [V]/[I]/[?]; every contradiction found goes into an audit section (6ek style) and into the dossier's Verification block. Re-derive other agents' claims before building on them.
- Vtable slot guesses must use the interface's real slot table (dossier --iface); do not name an object's method from the offset alone.
- Definition of "reversed" from 2026-11-12 on: a function counts as done only when its dossier has a "Reversed source" block in which every instruction maps to a source line (templates: docs/functions/bc61e20.md, bc60740.md), its structs are in an SDK header, and its layout constants are in layout_asserts.json and RenderLayoutAsserts.h. A stage map or callee profile is D1+, not D2.
- Work order: largest-impact first from docs/data/frame_path_functions.tsv (frame path census), small functions before giants; add indirect targets (pass lambdas, task bodies, job classes) as roots in tools/sigs/closure.py when identified.

## N. Integration & Threading

Integration points between a replacement and the existing renderer, plus the threading contract. References point to BGFX_MAP sections 8-11.

### N1. Submission and backend seams

- [ ] N1a Submit takeover hook at 0xe82e230 (slot 50 stats/timers); replacement walks Frame+0xB4700 draw records (stride 0x80) — BGFX_MAP 8a, 10
- [ ] N1b Per-draw veto/rewrite at draw executor 0xe821120 (flush 0xe81b720) — needs header-to-record mapping plus in-game test — BGFX_MAP 8a; M3e
- [ ] N1c Custom item seam Encoder::submitCustom(view, fn, user) key bit 53; fn(user, ctx) on render thread in view order — untested in game, ctx layout partly inferred — BGFX_MAP 8a; M3f
- [ ] N1d PSO builder 0xe81dc60: replacement draws route through it or rebuild equivalent key — BGFX_MAP 8c; B4
- [ ] N1e Per-view setup 0xe818490 and submit stage order preserved by replacement — BGFX_MAP 8c; 6t
- [ ] N1f Disk cache 0xe8feb10 consumed or invalidated consistently by replacement blobs — BGFX_MAP 8c; B4

### N2. Vtable slots and lifecycle

- [ ] N2a Slot 6 Present, slot 60 reset, slot 59 shutdown, slot 7 TDR handled by replacement without breaking device-lost — BGFX_MAP 10; 6f; B8a/B8b
- [ ] N2b Slot 50 submit stats/timers; slot 26 CreateTexture, slot 22 CreateShader, slot 24 CreateProgram, slots 14/16/17 vertex/index buffer, slot 35 CreateFrameBuffer, slots 36-38 uniform, slot 30 readTexture accounted for — BGFX_MAP 10; 6f; K-P5

### N3. Threading

- [ ] N3a Replacement submit runs on bgfx render thread; game thread / dragon task threads / render thread model per 6as/6ac — L17e (done); BGFX_MAP 11d
- [ ] N3b Frame double buffer 0xE749C0 apart; ctx+0x80 frame-ready and ctx+0x100 frame-consumed semaphores signaled in backend order — BGFX_MAP 8b/11d; A10
- [ ] N3c Custom items invoked on render thread in view order — BGFX_MAP 11d [?]

### N4. Version anchoring and validation

- [ ] N4a OffsetProvider.h + Sigs.json per version; FNV-1 64 pass/material hashes (basis 0xcbf29ce484222325, prime 0x100000001b3); __FUNCSIG__ via srcloc.py — BGFX_MAP 8d; K-P2/K-P7/K-P8
- [ ] N4b Startup validation: slots point into .text, sigs found, content checks (mask immediates, offset refs); fail loudly — BGFX_MAP 9b; K-P9; L18b

## O. DLL Infrastructure

Module layout, build gating, and headers for the replacement DLL.

### O1. Module layout

- [ ] O1a (CORRECTED 6ii: modules inside the existing client DLL, registered via R1; no new DLL) was: Single DLL exporting init (detour install + self-test), shutdown, seam entry points (submit replacement, pass toggles, draw veto) — BGFX_MAP 11a
- [ ] O1b Shutdown mirrors slot 59 ordering; reset entry is submit prologue plus slot 60; no breakage of slot 7 TDR/device-lost — BGFX_MAP 11a; A11

### O2. Headers

- [ ] O2a SDK headers compile-checked with MSVC /Zs (Context/Frame/RenderItem/View/Encoder/Handles, d3d12/*.h, dragon/*.h, one header per description, Descriptions.h, FrameBuilder.h); (built into the client now; Release OK, not run in game) — BGFX_MAP 11b; 6eg; B11
- [ ] O2b D3D12Context.h header: rvas, offsets, six resource tables, slots — B11

### O3. Build gating

- [ ] O3a SelfTest validates sizes/offsets at startup (static_asserts + SelfTest); Release build OK, not run in game — BGFX_MAP 9b; M3a
- [ ] O3b layout_asserts.json + tools/sigs/layoutcheck.py and RenderLayoutAsserts.h constants; every newly reversed function adds constants to both lists — BGFX_MAP 9a; M4c
- [ ] O3c Port check: dossier tool re-run on previous exes (BS_EXE) for every D2 function to measure RVA/offset/slot movement — not yet done — M4d
- [ ] O3d No debugger attach/breakpoints; no patches without explicit go-ahead — M5 standing rule

### O4. Behavior notes

- [ ] O4a Behavior notes without RVAs for every structural function (docs/BEHAVIOR_NOTES.md) so they survive re-mapping; not yet written for M1d/M1e items — M4b

## P. Rewrite Capability

What the rewrite must be able to do, as acceptance criteria against BGFX_MAP sections 8-11.

### P1. Seam selection

- [ ] P1a Seam map written: choose between submit takeover (0xe82e230), per-draw veto at executor flush 0xe821120, and custom item (submitCustom, key bit 53); document used and unused seams — BGFX_MAP 8a
- [ ] P1b Pass control via TaskDispatchHook + dragon/Tasks.h — written, never built or run — M3c; BGFX_MAP 8a
- [ ] P1c Actor-to-draw via RenderMarkHook; re-validate against flush 0xe81b720 and Encoder::submit seam — M3d
- [ ] P1d FrameFilterHook drop-by-kind veto point (nametags ~35/frame, UI meshes ~25/frame) — 6i

### P2. Existing hooks to reuse

- [ ] P2a RenderMarkHook exists; route 6bg — M3d
- [ ] P2b FrameFilterHook drops by kind — 6i
- [ ] P2c TaskDispatchHook + dragon/Tasks.h written, not built/run — M3c

### P3. Acceptance criteria

- [ ] P3a Startup self-check: 9 unique sigs added to Sigs.json; content checks (mask immediate, offset refs) in SelfTest code, not built — L18b; BGFX_MAP 9b
- [ ] P3b Whole-frame takeover: drive the frame ourselves (L18 goal) — BGFX_MAP 8a
- [ ] P3c Edit draws at submit: read/modify every draw record before the GPU — M3e
- [ ] P3d Frame graph add/remove/reorder pass safely — M3c

## Q. Rewrite Program (the actual goal; added in audit 6ii, see BGFX_MAP section 12)

Audit result: N/O/P (opencode) listed seams and startup checks only. Q is the ordered path from the current understanding to rewritten, measurable, controllable rendering. Order: Q1 -> Q2 -> Q3 -> Q4/Q5 -> Q6 -> Q7. M (understanding) keeps running in parallel and feeds Q.

### Q1. Infrastructure (blocks all rewrites)
- [ ] Q1a R1 rewrite registry: {name, sig-resolved rva, original trampoline, replacement, mode off/shadow/on/verify}, version gate, runtime toggle
- [ ] Q1b R2 shadow/verify harness: run original + replacement on copied inputs, compare outputs, abort loudly on first divergence
- [ ] Q1c R3 frame probe: per-frame dump of typed descriptions, pass list, draw records + RenderDraw + material/program/PSO key, actor attribution; read-only
- [ ] Q1d R4 profiler: CPU scope timers per registry function and frame stage; GPU timestamp pairs via custom item (bit 53)
- [ ] Q1e R5 ownership/threading table per rewritten function in its dossier

### Q2. First rewrites: pure, fully reversed leaves
- [ ] Q2a 0x5679db0 uniform/component writer, shadow-verified over many calls, timed
- [ ] Q2b 0x675e440 ResourceCache::get with a per-material cache (same MaterialInstance pointer and load state), timed
- [ ] Q2c Frame::sort (0xc280010/0xc280ca0) replaced by a radix sort on the 64-bit key; order-identical (stable), timed
- [ ] Q2d Encoder::submit 0xbc60740 + setTransform/matrix cache; verified by comparing the emitted Frame draw header/RenderDraw bytes
- [ ] Q3d Light tag 5 deep copy of ~41 unordered_maps per frame (0x67b6300/0x67b7810/0x67e90d0, 6ih): skip when unchanged (optimization candidate)
- [ ] Q2f 0xaa6580 mat4 multiply (pure SIMD leaf, 6ih): trivial first rewrite to validate the registry and shadow-verify harness (compare 16 floats)
- [ ] Q2e Encoder::discard / RenderBind grow / side-table copy

### Q3. Insert and extract layer
- [ ] Q3a The 21 thin clones replaced by one table-driven inserter; verified by an identical InsertVariant stream
- [ ] Q3b Extractors rewritten in cost order (BatchActor, chunk, nametag, particle, sky, clouds, weather); needs M1d reads + M2c; verified by comparing DrawItems/Frame records
- [ ] Q3c Description allocation/free ownership understood so descriptions can be pooled

### Q4. Executor and backend
- [ ] Q4a Close executor holes: bind-cache miss descriptor build, PSO desc build on a miss, setPredefined, helper bodies; job/command-list model; RTX subclass overrides
- [ ] Q4b Draw flush 0xe81b720 / executor 0xe821120 rewritten or wrapped: instancing/batch merge, state dedup, PSO key cache; verified by comparing the recorded D3D12 call stream
- [ ] Q4c Descriptor/upload ring and root signature ownership understood; device-lost/TDR path (slot 7) verified
- [ ] Q4d Per-draw veto/rewrite live in game and measured

### Q5. Passes and frame graph
- [ ] Q5a M1e finished: every pass body with in/out resources; custom-item ctx (0x18 bytes) confirmed
- [ ] Q5b TaskDispatchHook + Tasks.h built and run in game: disable, reorder, insert a pass (M3c)
- [ ] Q5c Own pass through submitCustom drawing with a native material/program, verified in game
- [ ] Q5d Pass-level rewrites (own upscale, own post) behind the registry

### Q6. Whole-frame control
- [ ] Q6a Frame generate 0xc273420 understood well enough to build the same task list ourselves
- [ ] Q6b Optimization module: culling/batching/LOD driven by probe + profiler data, each feature registry-toggled
- [ ] Q6c Whole-frame takeover demo: our renderer consumes the same extractor output (M3f)

### Q7. Control audit ("anything rendering-wise")
Each demonstrated, evidence recorded in BGFX_MAP: read any typed description; follow any actor to its draws; add/remove/reorder/replace any pass; edit or veto any draw; replace any material/program; create/read any texture/buffer/framebuffer; run our own GPU work at any point of the frame; switch any rewritten function back to the original at runtime; survive a version change by sig + layoutcheck report. Excluded by decision: OS/driver calls, DXGI/present internals beyond slot handling, audio/network.

## R. Partial-items ledger (added 2026-11-14 at the user's instruction: PARTIAL ITEMS DO NOT COUNT AS DONE)

Every item below was typed, read or noted only in part. None of them may be ticked [x] until its gap is closed and its constants are in both assertion lists. Revisit in this order; strike a line only when the gap is closed with evidence.
- [ ] R1 Atmosphere (Sky tag 0): per-field meaning, the producer (no thin clone) and the VV AtmosphericScattering pass body that drains the queue at pass+0x548 (BGFX_MAP 6ih, 6ik; the Sky statics belong to tags 5/6, not tag 0); struct is read-widths only
- [ ] R2 BlockChanges (Item tag 9): field meanings; the pass vector it feeds (pass+0x98/+0xA0)
- [ ] R3 BlitFlipbook (Effect tag 1): description +0x00..+0x0F, +0x20..+0x9F, element +0x34..+0x3F unread; true size
- [ ] R4 AimAssistHighlight (Effect tag 6): true size (min 0x68) and the +0x84 read of the shared tail
- [ ] R5 EditorHighlight (Effect tag 8): meanings of the 64-byte block and +0x50; the pass that consumes pass+0x80
- [ ] R6 LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4: value names, tag-name conflict (group_visitors vs LightGroupTag), pass consumers of +0x800 / +0x648 / +0x4A0 / +0x1D0
- [ ] R7 Light tag 5 (ServerGraphicsOverrideParameters): 0x40-byte parameter table element layout, key/value types; 0x67b6300, 0x67b7810, 0x67e90d0 dossiers
- [ ] R8 Light tags 6 and 7: payload behind the shared pair; VoxelVolume queue destination after 0x66421a9
- [ ] R9 FadeToBlack (Effect tag 5): description payload (0x67d6d70 is only a keyed lookup); FullscreenEffect (tag 7): config object layout (+0x180/+0x181/+0x185/+0x1A8)
- [ ] R10 UIMesh (UI tag 2): true size (>= 0x90), sub-objects at +0x18 and +0x88; Gameface, HudIcon, UIImGui untouched
- [ ] R11 Sky: EndSky, LegacyCubemap, CelestialBody, VolumetricFog, SkyAmbientSamples, SkyStars bodies; Editor tags 0-7; Item tags not typed yet (ChunkGeometry, ItemInHand, BatchActor beyond the known fields, Nametag etc. already typed are fine)
- [ ] R12 descscan: add "stop at first write to the description register" (reused r8/rsi misattribution) and a per-visitor register map option (done so far: --reg, --statics; new tools/sigs/ripscan.py, dispfun.py, disrange.py)
- [ ] R13 layout_asserts.json / RenderLayoutAsserts.h have no entries for any description (visitors have no Sigs.json anchors): add anchors and the constants
- [ ] R14 M1b classification, M1c/M1d/M1e dossier gaps, M3a-M3f, M4a-M4d, M1f (see their own lines)
