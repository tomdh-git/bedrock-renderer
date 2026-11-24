# Render reversal plan: all rendering (1.26.62.01)

Goal: every part of how the game turns world state into pixels is mapped, has SDK headers, and has a hook or replacement point, so any of it can be observed, changed or replaced. This is the work plan; `docs/BGFX_MAP.md` is the map it fills in. Confidence tags used in both: [V] verified live or by disassembly, [I] inferred, [?] unknown.

Size (static counts of the 991,816 functions in the exe, region bounds approximate): bgfx core ~290 fns / 120 KB, D3D12 context ~1,900 / 0.8 MB, RenderDragon platform+tasks ~980 / 0.3 MB, BgfxFrameBuilder + inserts ~2,300 / 0.8 MB, frame-graph renderers ~3,600 / 1 MB. The neighbors of those regions are 3-5x bigger. Estimate for the whole plan: 20-30 sessions of the length of the ones so far. Percent figures in earlier chat estimates were guesses; the "status" columns below are the real record.

## 0. How the work is done (every layer)

1. **Static:** `tools/sigs/srcloc.py` (function by `__FUNCSIG__`/assert string), `vtdump.py`, `fsum.py`, `xref.py`. Find the layer's entry points from strings and vtables, read the prologue for the real argument list (a detour that drops an argument crashes: the endFrame hook did, it reads rdx).
2. **Live (Cheat Engine only, no DLL probes):** hardware logging breakpoints for registers; `auto_assemble` code caves to copy stack-resident or short-lived structures into an `alloc`'d buffer; `write_region_to_file` + offline Python decode. Remove every patch afterwards and verify the original bytes.
3. **Write down:** section in `docs/BGFX_MAP.md` with RVAs, offsets and a [V]/[I]/[?] tag; the offset goes into `OffsetProvider.h` or a sig into `Sigs.json`.
4. **SDK + hook:** headers mirror the game's names/paths (see section 3). Hooks go through the HOOK/Detour DSL; a hook may depend on sdk/core/platform only.
5. **Verify in game** with the debug build, check `blueysensev2.log`. A hook that does not work must say so loudly (no silent fallback: removed from UnderUI, same rule everywhere).

Scenes needed for live captures (ask the user for each): first person in a world (done), third person with a mob in view, a visible nametag, rain/snow, particles (hit a mob, break a block), a held item and a block in hand, water/lava, a chest or sign (block entities), Vibrant Visuals ON (done) and OFF (Fancy), a resource pack with a custom material, the inventory and a menu screen, F1/hidden HUD, a dimension change, a world join/leave, window resize, an RTX world if hardware allows.

## 1. Layers

Order matters: each layer lists what it needs. "Done" means mapped AND has SDK/hook.

### L1. Frame, submit and the bgfx core (foundation)
- Reverse: `bgfx::Context` live layout and its global (0x12BB4910 is the D3D12 renderer-context object, NOT the Context), `Frame` / `RenderItem` / `RenderBind` / `View` / `ViewRemap` structs and strides, the encoder, `bgfx::submit/setState/setTexture/setUniform/setVertexBuffer/setIndexBuffer/setInstanceData*` entry points, view setup (`setViewRect/Clear/Transform/FrameBuffer/Name`), uniform registry and predefined uniforms (0xbc60100), handle allocators (paged guarded arrays), frame-buffer and render-target management, the API thread to render thread handoff (`frame()`, semaphore, "bgfx - renderer backend thread" 0xbc65720), async init, shutdown, dynamic texture handles, RT/TLAS slots of the fork.
- Anchors: core region 0xbc5f000-0xbc7d000; Context init 0xbc63690; thread proc 0xbc65720; texture validation 0xbc735b0; handle alloc 0xbc66de0; `submit` 0xe82e230 [V] (Frame* in rdx, two Frame buffers alternate 0xE749C0 apart, per-view block at +0xDC57E0).
- Output: `src/sdk/mc/deps/bgfx/{Context,Frame,RenderItem,View,Encoder,Handles}.h`, a `FrameObserver` hook at submit that can read (later edit) the render item list.
- Needs: nothing. Do first.

### L2. RendererContextD3D12 and the D3D12 backend
- Reverse: all 65 vtable slots (names, args), `submit` body (0x4D91 bytes: view loop, sort, draw dispatch, state-to-PSO lookup), PSO cache and key layout, root signature, descriptor heaps and allocation, command queue wrapper (+0xCC9268), resource creation (textures, buffers, upload/readback), resource-state tracking, fences, swapchain/present, device-lost/TDR (`_initiateTDR`), GPU timers, shader loading (DXIL/DXBC blobs, `createShader`, `createProgram`), RTX/TLAS build, upload ring buffers. Relationship to the "Direct3D 11" and "Direct3D 12 RTX" contexts (same interface, other vtables).
- Anchors: D3D12 vtable 0xF4EEE80; init slot 58 0xe807ff0; region 0xe7f0000-0xe8c0000.
- Already used by the client: TrackerHooks, CommandListTracker (command-list level). This layer gives them names and stable struct offsets.
- Output: `src/sdk/mc/deps/bgfx/d3d12/*.h`, offsets in `OffsetProvider.h`.
- Needs: L1.

### L3. RenderDragon: platform, tasks, scheduler, frame graph encoding
- Reverse: `dragon::platform::BgfxContext::endFrame` (0xc270460, "Generate and encode frame graph"), `GraphicsTasks` (frame lambda 0xc267200, `_render` 0xc25fc50, `waitForPreviousFrame` 0xc25f960), the task scheduler (0xc25b1a0), task record layout (kind hash, data +0x78, see RenderMarkHook), `DragonFrameResources`, `IntraFrameAllocator`, the `Declarator`, the module/pass declaration system (`framerenderer::modules`), resource lifetimes/aliasing, how a frame graph compiles to bgfx calls, how many threads encode.
- Output: `src/sdk/mc/deps/minecraft_renderer/dragon/*.h`; hook to enumerate and enable/disable passes by name and to see the compiled graph.
- Needs: L1.

### L4. FrameBuilder layer (mce::framebuilder)
- Reverse: `BgfxFrameBuilder` (114 vtable slots; names for all; fields +0x20/+0x28/+0x358; LeviLamina `FrameBuilder.h` lists 110 so indices are not portable), the six group `_insert` slots (Editor 0x358, Effect 0x360, UI 0x368, Sky 0x370, Item 0x378, Light 0x380 [V on Sky/Item]), every description type of every group and its tag order (37 `insert<T>` clones; Item group tags 0-10 known), the layout of each description, `beginFrame/endFrame` (endFrame(this, frame), 0x66232b0, 0xB3D0 bytes), TDR handling.
- Descriptions to capture (one live capture each): EnvironmentalText, Nametag, MeshFallback, ChunkGeometry, ChunkOccluders, Crack, ItemInHand, SkinnedMesh, BlockSelectionOverlayBlockEntity, BlockChanges, BatchActor ([V]: +0xE0 count, +0xE8 array, stride 0x48; instances are model/draw records with NO actor id, see BGFX_MAP 6d), plus Sky/EndSky/Stars/Celestial/Clouds/Cubemap/LegacyCubemap/Weather, Particle, UI descriptions, Light descriptions, Editor descriptions.
- Existing: `FrameFilterHook` (insert hooks by call-site; Item 0x378 and Sky 0x370 [V]) and `FrameBuilderHook` (endFrame listeners, in this repo).
- Output: `src/sdk/mc/deps/minecraft_renderer/framebuilder/*.h` (one header per description), typed hooks per group.
- Needs: L1 for how a description becomes draws.

### L5. Extractors and the registry (description -> render objects)
- Reverse: the Item visitor 0x6646980 with jump table 0xf2bf2d0 (11 entries) and each extractor behind it (BatchActor 0x66d9af0 size 0x8BB7, skinned mesh inline in 0x6646dc2 with material-hash branches, chunk geometry, crack, nametag, block entity 0x66e75f0, ...); the entt registry and every render component (`SceneObjectActors`, `NonShadowOnlyObject`, `DynamicShadowCaster`, `ActorShadow`, ...); how components become the `extractAndDrawWithExclusion<Opaque|AlphaTest|Transparent, X>` lists; where per-actor identity, world transform and material come from (NOT in the batch instance).
- Output: component headers, an `ExtractionObserver`, and the identity route for per-actor control (existing item-key table in RenderMarkHook is one route; registry components are the other).
- Needs: L4.

### L6. Frame-graph renderers and pass classes
- Reverse: `VibrantVisualsFrameRenderer` (builder 0x5255450, region 0x5200000-0x5300000), `FancyFrameRenderer`, `RTXMinecraftFrameRenderer`, the legacy/non-VV path; the complete pass list per renderer with names, inputs/outputs, order and enable conditions: GBuffer, lighting, shadow cascades, SSAO/SSR, fog, volumetrics, sky, transparency (OIT?), TAA, upscaling, bloom, tonemap, UI composite, post effects. Pass declaration API, resource names ("Persistent UI Color", "Deferred Texture Transactions", ...).
- Output: a pass registry (name -> RVA, in/out resources), ability to disable, reorder or add a pass.
- Needs: L3, L4.

### L7. Materials and shaders
- Reverse: the material system: `.material.bin` loader, `MaterialPtr` and the material manager (4,788 shader blobs indexed in the log), variants/permutations and how a draw picks one, render-state/blend/depth/stencil setup, uniform buffers and the uniform binding lists seen in the extractor (TintedAlphaTestEnabled, Metalness/Emissive/Roughness/SubsurfaceUniform, PBRTextureFlags, ActorFPEpsilon, DitheringEnabledToggle, MultiplicativeTintColor, UVScale, GlintColor, UseAlphaRewrite, PrevBones, PrevWorld, MERSTexture, NormalTexture, MatTexture1/2), shader compile/cache, and the resource-pack custom material path.
- Output: `minecraft_renderer/renderer/Material*.h`; a hook to swap a draw's material/program.
- Needs: L2 (programs), L5 (what binds them).

### L8. Textures, atlases and resources
- Reverse: texture group and `ClientTexture`/`BedrockTexture`/`TexturePtr` (headers exist, see sdk), how resource packs become GPU textures, atlases (terrain, items), mipmaps and compression, async upload, texture handle lifetime, render targets and their formats, the dynamic-texture-handle mechanism of the fork, the pack reload path (already in `bluey-resourcepack-reload-re`).
- Needs: L1, L2.

### L9. Geometry production: chunks, meshing, buffers
- Reverse: `RenderChunkCoordinator` (`_launchVisibilityRebuild` 0x1c9f270), `LevelBuilder::scheduleChunkBuild` (0x47d8750), the mesher (tessellator, palette, per-face culling, AO), chunk mesh storage, vertex/index buffer pools and upload, chunk occlusion/visibility, LOD/draw distance, sub-chunk draw lists, `Mesh`/`MeshData` (headers exist). Block entity and item/block-in-hand geometry.
- Needs: L4 (ChunkGeometry/Occluders descriptions), L1.

### L10. Level renderer, camera, culling and scene setup
- Reverse: `LevelRenderer` and `LevelRendererPlayer` (camera pos 0x9C4, projection 0xF50, already used), frustum extraction and culling, view/projection/jitter, viewport and render-resolution selection, dynamic resolution, FOV and the screen-space transforms, per-frame constant data, the weather/sky/fog parameters pushed to the renderer.
- Needs: L4.

### L11. Lighting, shadows and environment
- Reverse: shadow cascade setup and caster lists, light volumes and culling, ambient/sun/moon parameters, SSAO/SSR parameters, fog/volumetric parameters, probes/IBL, RT lighting. 
- Needs: L5, L6.

### L12. Actor rendering above the framebuilder
- Reverse: `ActorRenderDispatcher` and the actor renderers (0x6ebb510 data-driven body, 0x4e355a0, player renderer 0x575efc0, 0x6b84e60), Molang evaluation for render (`variable.*`), geometry/skeleton/bone matrices and upload (PrevBones), animation controllers on the render side, skins and capes, held-item and armor rendering, hands (see `bluey-hand-render-notes`), nametags (0x1127330/0x11276b0), shadows blob.
- Needs: L5.

### L13. Particles, weather, sky and clouds
- Reverse: particle engine to `Particle` descriptions and draw (billboards, instancing), weather (rain/snow), sky (celestial 0x5369b30 clone, stars, clouds, cubemap), end sky. Existing hooks already drop some of these by tag.
- Needs: L4, L6.

### L14. UI rendering
- Reverse: `ScreenRenderer`/`MinecraftUIRenderContext`, the Ore UI/cohtml render integration (cohtml.WindowsDesktop.dll, Renoir), text and font rendering, nine-slice, the UI group descriptions, how UI draws into the frame (UnderUI boundary exists), the HUD/screen composition, RenderDragon "UI" passes, the menu panorama path.
- Needs: L4, L6.

### L15. Post-processing, upscaling, HDR
- Reverse: TAA and history, DLSS (wrapper vtable 0xeb8f120, slot 60 settings 0xdfc6c00, slot 64 evaluate 0xdfc82b0), FSR1 (EASU 0xb77d0f0, builder 0xb74f860), TAAU (0xb752820), dynamic resolution, bloom, tonemap, color grading, motion vectors (VV only), checkerboard.
- Output: the optimization module's upscaler control (`bluey-perf-upscaling-re`).
- Needs: L6.

### L16. Ray tracing (RTX)
- Reverse: the "Direct3D 12 RTX" context, TLAS/BLAS build and update, RT shaders and passes, denoiser, RT slots in the bgfx fork.
- Needs: L2, L6. Lowest priority unless RTX hardware is available to test.

### L17. Platform glue and threading
- Reverse: swapchain/DXGI/present and resize (partly hooked), GDK integration, GPU timers and memory budget, device lost/TDR, the exact thread model (game thread, dragon task threads, bgfx render thread), frame pacing/vsync, async init and shutdown ordering, the graphics options plumbing (`OptionSync`).
- Needs: L1-L3.

### L18. Whole-frame replacement (Level 3 goal)
- With L1-L17 mapped: drive the frame ourselves, from a frame-level takeover of submit, to replacing a renderer's pass list, to a custom renderer fed by the extractors. This is where an optimization module (frame cost, culling, batching, our own upscale) is built; plan in `docs/PLAN_OPTIMIZATION.md`.

## 2. Dependency order and milestones

M1 (first 2-3 sessions): L1, then L4 descriptions, then L5 identity. Unlocks: read/edit render items at submit, per-description hooks, per-actor control.
M2: L7 materials, L9 geometry, L10 camera/culling. Unlocks: material swaps, chunk-level optimization, custom culling.
M3: L3, L6 frame graph and passes, then L11, L13, L14, L15. Unlocks: pass add/remove/reorder, shadow/sky/particle/UI control, upscaler control.
M4: L2 backend depth, L8 textures, L12 actors, L16, L17. Unlocks: deep backend control, resource streaming, RTX.
M5: L18 whole-frame replacement.
After each milestone: build, retest in game, update `BGFX_MAP.md`, the memory note and `graphify update .`.

## 3. Where it lives in the codebase (native-game layout)

- `src/sdk/mc/deps/bgfx/` : bgfx core and backend (`Context.h`, `Frame.h`, `d3d12/`).
- `src/sdk/mc/deps/minecraft_renderer/framebuilder/` : `FrameBuilder.h` (done: slots, group tags, BatchActor description) and one header per description.
- `src/sdk/mc/deps/minecraft_renderer/dragon/` : RenderDragon (platform, tasks, frame graph, passes).
- `src/sdk/mc/deps/minecraft_renderer/renderer/` : materials, meshes, textures (existing headers).
- `src/sdk/mc/client/renderer/` : level renderer, actor renderers, particles (mirrors LeviLamina `src-client`).
- `src/client/features/hooks/hooks/render/` : one hook per layer entry point (`FrameFilterHook`, `FrameBuilderHook` exist); features (`features/render/...`) use them through small listener APIs, never detour directly.
- Offsets: `src/sdk/OffsetProvider.h` and `src/sdk/Sigs.json`. Rules: `docs/CONVENTIONS.md` (quoted includes only, no `using namespace`, no anonymous namespaces, functions <= 40 lines, no silent fallbacks).

## 4. Risks and rules

- Every detour must forward the original's full argument list; read the prologue first.
- Version drift: each patch shifts vtable slots (1.26.60 -> .62 shifted the group slots by +8). Slot constants are named once, in the SDK header, and a startup check must fail loudly if a slot does not point into .text or a sig is missing.
- The game holds the DLL while running; build and eject discipline per `bluey-build-notes`.
- Cheat Engine patches are always removed and the original bytes verified after each capture.
- Do not trust a layout read after the fact for stack-resident data: use the cave method.
- Untested in game means untested: record each layer's status here when verified.

## 5. Status (updated 2026-11-11, end of the first reversal session)

Done this session (all static + Cheat Engine, nothing needs injecting): L4 description catalog is COMPLETE as a catalog (62 framebuilder types, 50 insert clones with group slot, `DescriptionClones.h`, docs/RENDER_CATALOG.md); Frame buffer layout partially decoded from a live dump (BGFX_MAP 6e); both RendererContext vtables dumped and diffed (6f); layer anchors for materials, chunks, shadows, occlusion, post, upscalers, DLSS, particles (6h); the giant VV frame-graph function located (0x55f1450, 319 KB); pass names proven hashed, not present as strings.

| Layer | Mapped | SDK | Hook | Verified in game |
|---|---|---|---|---|
| L1 bgfx core / Frame | Frame header/tail/draw record stride, counters, transient buffers | none yet (offsets in doc only) | none | no |
| L2 D3D12 backend | both 65-slot vtables, RTX overrides (slots 63/64 = GPU skinning, DLSS) | partial (BgfxContext) | tracker hooks (existing) | partly |
| L3 RenderDragon | endFrame, scheduler, PipelineDiskCache, .material.bin loader anchors | none | none | no |
| L4 FrameBuilder | vtable, groups, all types, 50 clones; BatchActor layout | FrameBuilder.h, DescriptionClones.h | FrameFilterHook (Item 0x378 + Sky 0x370 both hooked), FrameBuilderHook | yes (2026-11-11) |
| L5 extractors/registry | visitor, BatchActor extractor, component names | none | none | no |
| L6 frame graph renderers | giant VV function 0x55f1450, builder anchors | none | none | no |
| L7 materials/shaders | loaders 0xc26caa0, 0x842070 | MaterialPtr.h | none | no |
| L8 textures | atlases anchors; pack reload (existing) | headers exist | none | partly |
| L9 geometry/chunks | coordinator 0x7923d50, scheduleChunkBuild 0x533c910 | Mesh.h | none | no |
| L10 level renderer/camera | camera components catalog, takePicture 0x5360e00 | OffsetProvider | none | yes (existing) |
| L11 lighting/shadows | cascades 0x53fcac0, occlusion 0x660ecd0/0x6745440, lighting types | none | none | no |
| L12 actors | nametag 0x4744a00, components | none | none | no |
| L13 particles/weather/sky/clouds | anchors | none | partial drop-by-tag | no |
| L14 UI | UI description types | none | none | no |
| L15 post/upscaling | tonemap 0xbcacd90, SSR 0xbc82ad0, TAAU 0xbc8cfd0, MV 0xbc8a380, FSR 0xbcb64f0, DLSS 0xe83ec70/0xe8403d0 | none | none | no |
| L16 RTX | RTX vtable overrides | none | none | no |
| L17 platform | framerate/vsync anchors | none | existing | yes |
| L18 | not started | | | |

Next (needs the user in game or per-layer deep reading): per-description live captures (third person, nametag, rain, particles, VV off); decode the 0x80-byte draw record field by field against submit's draw loop; name the 65 slots by bgfx order; read the giant 0x55f1450 function's pass declarations; extractors (0x66d9af0 and the Item visitor branches) for actor identity.

### Status update (Caps)
- bgfx::Caps decoded (limits, flag bits, globals): docs/BGFX_MAP.md 6j, src/sdk/mc/deps/bgfx/Caps.h (builds).
- Next: diff-decode insert descriptions via multi-capture, Fancy-path pass graph from 0x66ea3d0, name the 65 RendererContext slots, extractors/actor identity.

### Status update (2026-11-23): direction changed
The goal is now the done state in `docs/RENDER_DONE_STATE.md`: instruction-complete source for every function on the render path, verified byte-identical, running as our own code (Native mode), then optimization from that source. PLAN_OPTIMIZATION.md was deleted; references to it in BGFX_MAP 6bh/J3 and RENDER_CHECKLIST J3/L18c are historical.
