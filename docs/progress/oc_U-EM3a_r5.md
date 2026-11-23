## NEXT
DONE

# Unit U-EM3a — M3a Data structures
GOAL: Close checklist item: M3a Data structures: every struct of M2 compiles as a header and a startup self-check validates sizes/offsets that can be validated (static_asserts + SelfTest) [RENDER_CHECKLIST.md line 453]; mirrored by O3a (line 518, CLOSES? YES via oc_U-EO3a_r1.md).

Constraints recap: may create/edit only docs/ and tools/ and NEW files under src/sdk/ and src/client/features/render/. No HookManager.cpp, no hook registration, no CMake, no Sigs.json edits, no builds, no commits, no game launch. CLAUDE.md style: fail fast, no null guards or SEH. Static analysis only: the exe is data, read via rdis.exe; nothing here launches or attaches to the game.

## (1) PATHS CHANGED
- docs/progress/oc_U-EM3a.md — this result file (the only file written this session).
- tools/sigs/m2headercheck.py — NEW documented tool: source-only inventory of the M2 header contract ("every struct of M2 compiles as a header"): header-by-header struct/using declarations, static_assert(sizeof/offsetof) pins, which build TU checks each header (SelfTest.cpp direct, via AllDescriptions.h, via SelfTestRenderLayoutCoverage.cpp, via FrameBuilderHook.cpp), orphan-header detection, DescriptionClones.h catalog cross-reference, and duplicate-definition review. Run output reproduced verbatim in section (3).
No existing src/ file was edited, no build was run, no game was launched. Tools used: rdis.exe dis of anchor RVAs, tools/sigs/layoutcheck.py (offline exe scan), tools/sigs/m2headercheck.py (source scan).

## (2) M2 HEADER INVENTORY — every struct of M2 compiles as a header on disk

| M2 sub-item | checklist | headers | size/offset static_asserts | compile check (static_asserts run in) |
|---|---|---|---|---|
| M2a Frame/View/RenderDrawHeader/Encoder/Caps (+ Handles.h, Uniforms.h per A13) | [x] | bgfx/Frame.h, bgfx/View.h, bgfx/Encoder.h, bgfx/Caps.h, bgfx/Handles.h, bgfx/Uniforms.h | FrameOffsets (kItemCount 0xDC57E8, kSortKeys 0x14700, kSortedItems 0x94700, kDrawHeaders 0xB4700, kRenderDraws 0x8B4700, kFrameSize 0xE749C0); RenderDrawHeader/RenderDraw (packed 0x80, per-field offset pins), RenderStream (8 B), RenderCompute (0x24); ViewRecord (kBase 0x1EAB090, kStride 0x140, sortMode 0x122, kArrayBase 0x1EAB080); EncoderOffsets (kState 0x60, kRenderBind 0x140, kBindHash 0x654, kPostCallback 0x680, kBindDirty 0x688, kCustomItem 0x100); CapsGlobals (.data RVAs); UniformRecord (0x18), UniformRegistry | Frame.h/Encoder.h via SelfTest.cpp; Caps.h/View.h/Handles.h/Uniforms.h via the NEW src/sdk/SelfTestRenderLayoutCoverage.cpp (CMake GLOB_RECURSE src/*.cpp, no CMake edit); FrameBuilder.h/Caps.h/Frame.h/Descriptions.h/RendererContext.h also via FrameBuilderHook.cpp |
| M2b D3D12: DrawBatcher + two draw record layouts | [x] | bgfx/d3d12/D3D12Context.h, bgfx/DrawRecord.h | DrawBatcherOffsets (kRingSlot 0xF28, kVbCache 0x10C0, kIbCache 0x1110, kCapacity 0x115C, kIndirectEnabled 0x1164); JobContextOffsets (command list +0x30); BatchDraw 0x70 / BatchDrawIndexed 0x88; DrawRecordNonIndexed 0x70 / DrawRecordIndexed 0x88 / D3d12Vbv 0x10 field by field | via SelfTest.cpp |
| M2c every description type as a struct with confirmed fields | [ ] own item | framebuilder/Descriptions.h + per-type headers via framebuilder/AllDescriptions.h | Descriptions.h: 44 structs, 41 sizeof pins + 187 offsetof pins (RenderNametagDescription 0x98, RenderSkinnedMeshDescription 0x1D0, RenderMeshFallbackDescription 0x1D0, RenderCloudsDescription 0xA8, RenderWeatherDescription 0x130, RenderParticleDescription 0xB0, RenderFlameBillboardDescription 0xF8, RenderGameFaceDescription 0x78, RenderCubemapDescription 0xC0, RenderAtmosphereDescription 0x138, RenderBlockChangesDescription 0x18, RenderBlitFlipbookDescription 0x20 / Element 0x40, RenderUIMeshDescription 0xA8, RenderFullscreenEffectDescription 0xD0, RenderAimAssistHighlightDescription 0x88, RenderEditorHighlightDescription 0x58, RenderLightAmbientDescription 0x18, RenderLightDirectionalDescription 0x24, RenderLightTag2Description 0x84, RenderLightTag3Description 0x108, RenderLightTag4Description 0x50, RenderLightServerGraphicsOverrideDescription 0xB00, plus SharedRef/DescVariantRef and nested Element/Slice); per-type headers (BatchActorDescription 0x110, ItemInHandDescription 0x180, VoxelVolumeDescription 0x30, TransitioningVoxelVolumeDescription 0x48, 8 editor gizmo descriptions, WeatherDescription 0x130...) | Descriptions.h + AllDescriptions.h via SelfTest.cpp; per-type headers via AllDescriptions.h |
| M2d batch instance / actor record / item payload (0xC8) | [x] | framebuilder/DrawItem.h, framebuilder/FrameBuilder.h | DrawItem 0xC8 + DrawItemShared 0x38 / DrawItemSmallVector 0x30 / DrawItemBounds 0x2C / DrawItemTransform 0x48 / DrawItemState 0x58 / DrawItemShaderState 0x88 / DrawItemVertexStream 0x28 / DrawItemGeometry 0x58; RenderBatchActorDescription (kMinSize 0x110), InsertVariant | DrawItem.h via SelfTest.cpp; FrameBuilder.h via SelfTestRenderLayoutCoverage.cpp + FrameBuilderHook.cpp |
| M2e resource records field by field (texture 0xB8, vertex 0x78, index 0x80, framebuffer 0x68, program 0xF8, shader 0xB8, uniform 0x68) | [x] | bgfx/d3d12/D3D12Context.h | table bases/strides/counts (texture 0xBDE178/0xB8, index 0x93A178/0x78, vertex 0x9B2178/0x80, shader buffers 0xA32178/0x78, shaders 0xAAA178/0xB8, programs 0xB62178/0xF8, framebuffers 0xC97698/0x68, uniforms 0xC97698/0x68...), record layouts field by field, program predefined slots 28 x 8 bytes at +0x10, vertex layout = bgfx::VertexLayout verbatim | via SelfTest.cpp |

Header static_assert pin counts (grep on disk): Frame.h 33, View.h 3, Encoder.h 7, Caps.h 0 (offset constants/enums only — no struct layout to assert), Handles.h 17, Uniforms.h 6, RendererContext.h 0 (slot constants only), D3D12Context.h 62, DrawRecord.h 21, RenderLayoutAsserts.h 0 (code-constant list, validated at runtime by SelfTest world phase), Tasks.h 4 (incl. static_assert(sizeof(TaskListEntry) == 0x80)), Descriptions.h 228, DrawItem.h 30, FrameBuilder.h 12, SelfTestRenderLayoutCoverage.cpp 0 (it only #includes to force the headers' asserts).

## (3) HEADER-CONTRACT TOOL OUTPUT — tools/sigs/m2headercheck.py (source-only scan, exit 0)

72 headers scanned under src/sdk/mc/deps/bgfx/ (+d3d12/) and src/sdk/mc/deps/minecraft_renderer/framebuilder/; 253 struct definitions found (nested members included); 4 using aliases; 1214 static_assert pins (sizeof + offsetof); 27 of 72 headers are directly checked by a compile TU (SelfTest.cpp direct or via AllDescriptions.h); 36 headers are orphans (included by no TU — latent only, not co-included with their duplicate).

<dcp-verbatim-start>
| header | structs / using | sizeof pins | offsetof pins | compile check | included by any TU | note |
|---|---|---|---|---|---|---|
| BgfxContext.h | 1 / 0 | 0 | 0 | no | yes | defines struct(s) but no static_assert pins |
| Caps.h | 1 / 0 | 0 | 0 | no | yes | defines struct(s) but no static_assert pins |
| CustomItem.h | 2 / 1 | 2 | 5 | no | yes | - |
| DrawRecord.h | 4 / 0 | 3 | 18 | yes (direct, SelfTest.cpp) | yes | - |
| Encoder.h | 6 / 0 | 1 | 0 | yes (direct, SelfTest.cpp) | yes | - |
| EncoderSubmitRewrite.h | 1 / 0 | 0 | 0 | yes (direct, SelfTest.cpp) | yes | - |
| Frame.h | 5 / 0 | 3 | 28 | yes (direct, SelfTest.cpp) | yes | - |
| FrameProbe.h | 2 / 0 | 1 | 24 | no | yes | - |
| Handles.h | 6 / 0 | 1 | 0 | no | yes | - |
| RenderLayoutAsserts.h | 2 / 0 | 0 | 0 | yes (direct, SelfTest.cpp) | yes | defines struct(s) but no static_assert pins |
| RendererContext.h | 1 / 0 | 0 | 0 | yes (direct, SelfTest.cpp) | yes | defines struct(s) but no static_assert pins |
| Uniforms.h | 2 / 0 | 1 | 1 | no | yes | - |
| View.h | 1 / 0 | 0 | 0 | no | yes | - |
| D3D12Context.h | 35 / 1 | 10 | 18 | yes (direct, SelfTest.cpp) | yes | - |
| RendererContextLifecycle.h | 0 / 0 | 0 | 0 | no | no | orphan: included by no TU |
| SamplerFlags.h | 1 / 0 | 1 | 2 | no | no | orphan: included by no TU |
| TimestampQuery.h | 1 / 0 | 0 | 0 | no | no | defines struct(s) but no static_assert pins; orphan: included by no TU |
| AllDescriptions.h | 0 / 0 | 0 | 0 | yes (direct, SelfTest.cpp) | yes | - |
| BatchActorBuilders.h | 5 / 0 | 4 | 21 | no | no | orphan: included by no TU |
| BatchActorDescription.h | 3 / 0 | 3 | 22 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| ChunkDrawList.h | 2 / 0 | 2 | 16 | no | no | orphan: included by no TU |
| ChunkGeometryDescription.h | 2 / 1 | 0 | 23 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| DescriptionClones.h | 1 / 0 | 0 | 0 | no | yes | defines struct(s) but no static_assert pins |
| Descriptions.h | 44 / 1 | 41 | 187 | yes (direct, SelfTest.cpp) | yes | - |
| DrawItem.h | 11 / 0 | 10 | 20 | yes (direct, SelfTest.cpp) | yes | - |
| EditorBlockVolumeDescription.h | 1 / 0 | 0 | 6 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| EffectDescriptions.h | 11 / 0 | 9 | 72 | no | no | orphan: included by no TU |
| FlameBillboardDescription.h | 1 / 0 | 0 | 16 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| FrameBuilder.h | 7 / 0 | 4 | 8 | no | yes | - |
| GamefaceDescription.h | 3 / 0 | 2 | 18 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| ItemInHandDescription.h | 2 / 0 | 2 | 27 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| ItemVisitorTags.h | 1 / 0 | 1 | 0 | no | no | orphan: included by no TU |
| LightDescriptions.h | 6 / 0 | 6 | 28 | no | no | orphan: included by no TU |
| LightGameDescriptions.h | 14 / 0 | 14 | 93 | no | no | orphan: included by no TU |
| ParticleSkyExtractors.h | 1 / 0 | 1 | 0 | no | no | orphan: included by no TU |
| RenderBlockChangesDescription.h | 1 / 0 | 1 | 1 | no | no | orphan: included by no TU |
| RenderBlockSelectionOverlayDescription.h | 2 / 0 | 2 | 5 | no | no | orphan: included by no TU |
| RenderCloudsDescription.h | 1 / 0 | 1 | 4 | no | no | orphan: included by no TU |
| RenderEditorBlockVolumeBoundingBoxDescription.h | 1 / 0 | 1 | 7 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| RenderEditorBlockVolumeOutlineDescription.h | 1 / 0 | 1 | 5 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| RenderEditorGizmoHandleArrowDescription.h | 1 / 0 | 1 | 5 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| RenderEditorGizmoHandleCubeDescription.h | 1 / 0 | 1 | 5 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| RenderEditorGizmoHandlePaneDescription.h | 1 / 0 | 1 | 5 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| RenderEditorGizmoHandleRingDescription.h | 1 / 0 | 1 | 9 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| RenderEditorRenderPlaneDescription.h | 1 / 0 | 1 | 4 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| RenderEditorSelectionCursorDescription.h | 1 / 0 | 1 | 4 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| RenderEnvironmentalTextDescription.h | 2 / 0 | 2 | 6 | no | no | orphan: included by no TU |
| RenderFullscreenEffectDescription.h | 1 / 0 | 1 | 0 | no | no | orphan: included by no TU |
| RenderLegacyCubemapDescription.h | 1 / 0 | 1 | 2 | no | no | orphan: included by no TU |
| RenderLightAmbientDescription.h | 1 / 0 | 1 | 3 | no | no | orphan: included by no TU |
| RenderLightDirectionalDescription.h | 1 / 0 | 1 | 4 | no | no | orphan: included by no TU |
| RenderLightTag2Description.h | 1 / 0 | 1 | 0 | no | no | orphan: included by no TU |
| RenderLightTag3Description.h | 2 / 0 | 2 | 5 | no | no | orphan: included by no TU |
| RenderLightTag4Description.h | 1 / 0 | 1 | 1 | no | no | orphan: included by no TU |
| RenderMeshFallbackDescription.h | 2 / 0 | 2 | 13 | no | no | orphan: included by no TU |
| RenderNametagDescription.h | 2 / 0 | 2 | 9 | no | no | orphan: included by no TU |
| RenderPlayerVisionDescription.h | 1 / 0 | 1 | 2 | no | no | orphan: included by no TU |
| RenderShadowDescription.h | 1 / 0 | 1 | 3 | no | no | orphan: included by no TU |
| RenderSkinnedMeshDescription.h | 2 / 0 | 2 | 8 | no | no | orphan: included by no TU |
| RenderSkyAmbientSamplesDescription.h | 1 / 0 | 1 | 1 | no | no | orphan: included by no TU |
| RenderSkyColorsDescription.h | 1 / 0 | 1 | 3 | no | no | orphan: included by no TU |
| RenderSkyDescription.h | 2 / 0 | 2 | 3 | no | no | orphan: included by no TU |
| RenderStarsDescription.h | 1 / 0 | 1 | 2 | no | no | orphan: included by no TU |
| RenderUIHudIconDescription.h | 1 / 0 | 1 | 2 | no | no | orphan: included by no TU |
| RenderUIMeshDescription.h | 1 / 0 | 1 | 9 | no | no | orphan: included by no TU |
| RenderUITextDescription.h | 2 / 0 | 2 | 3 | no | no | orphan: included by no TU |
| RenderVolumetricFogDescription.h | 1 / 0 | 1 | 0 | no | no | orphan: included by no TU |
| SkyDescriptions.h | 12 / 0 | 3 | 74 | no | no | orphan: included by no TU |
| TransitioningVoxelVolumeDescription.h | 1 / 0 | 1 | 8 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| UiEditorDescriptions.h | 9 / 0 | 2 | 57 | no | no | orphan: included by no TU |
| VoxelVolumeDescription.h | 1 / 0 | 1 | 5 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
| WeatherDescription.h | 4 / 0 | 2 | 26 | yes (via AllDescriptions.h -> SelfTest.cpp) | yes | - |
<dcp-verbatim-end>

Duplicate struct definitions (30 names): all latent — per-type description headers (RenderCloudsDescription.h, RenderBlockChangesDescription.h, ...) duplicate the Descriptions.h struct but are orphans (included by no TU, so never co-included with Descriptions.h in one TU); PassEntry exists in bluey::gameface (GamefaceDescription.h) and bluey::weather (WeatherDescription.h) — different namespaces, no conflict. The regex scan also flags Instance/Span between BatchActorDescription.h and FrameBuilder.h; those are free structs in bluey::batchactor vs nested members of a class in mce::framebuilder — different entities.

DescriptionClones.h catalog cross-reference: 50 clone entries; 42 map by certain name (V), 8 map by tag/extent inference (? — LightPointDescription->RenderLightTag2Description, ShadowAtlasFrameDescription->RenderLightTag4Description, RenderUIGamefaceDescription->RenderGameFaceDescription, RenderBlockSelectionOverlayBlockEntityDescription->RenderBlockSelectionOverlayDescription, RenderCameraAimAssistHighlightDescription->RenderAimAssistHighlightDescription, gamecomponents::EditorHighlightConfiguration->RenderEditorHighlightDescription, gamecomponents::GameplayMetadata->RenderLightTag2Description, gamecomponents::ServerGraphicsOverrideParameters->RenderLightServerGraphicsOverrideDescription); 0 unmapped. Every clone entry has a compiled description struct. Inferred mappings are name equivalences only; no size or offset depends on them.

## (4) STARTUP SELF-CHECK — static_asserts + SelfTest (BGFX_MAP 9b; mirrors O3a)

SelfTest::runStatic() is called from src/client/app/App.cpp:111 at startup (main thread, after hooks enabled) and never throws/fatals (recordFailure logs via Logger::warn and appends to gFailures).
1. Compile-time static_asserts: SelfTest.cpp #includes RenderLayoutAsserts.h, RendererContext.h, Encoder.h, Frame.h, D3D12Context.h, Tasks.h, Descriptions.h, AllDescriptions.h (+DrawItem.h and the rewrite headers), so every M2 header listed in section (2) has its sizeof/offsetof static_asserts checked in every client build; a drifted struct size/offset fails the build before the game runs (fail fast). SelfTestRenderLayoutCoverage.cpp adds Caps.h, View.h, Handles.h, Uniforms.h, FrameBuilder.h to that compile set (CMake GLOB_RECURSE src/*.cpp picks it up — no CMake edit). FrameBuilderHook.cpp additionally compiles FrameBuilder.h, Caps.h, Frame.h, Descriptions.h, RendererContext.h. Union: every M2 header's static_asserts are exercised by a build TU.
2. Explicit cross-check static_asserts at SelfTest.cpp:26-30 tie renderlayout::kDrawFlush values (kRingSlot 0xF28, kVbCache 0x10C0, kIbCache 0x1110, kLastCbv 0x1120, kCapacity 0x115C, kIndirectEnabled 0x1164) to bgfx::d3d12::DrawBatcherOffsets enum values — mismatch = compile error.
3. Startup SelfTest runtime: censusSignatureDatabase() fails loud for every dead Sigs.json symbol; checkRenderLayout() (world phase, first GameUpdateEvent with a local player) fails loud when a renderlayout constant (mask immediate / offset ref) is absent from its anchor function's code bytes; checkRendererVtables() fails loud when any of the 65 slots of either renderer vtable (base 0xF4ED2D0, RTX 0xF4EEE80) points outside .text. Results persisted to %APPDATA%\BlueySenseV2\diagnostics\selftest.txt ("static: N passed, N failed, N deferred"; world phase the same).
4. Offline verification: tools/sigs/layoutcheck.py re-checks every layout_asserts.json constant against the exe by disassembling each anchor function: 209 assertions, 0 failed, exit 0 (run 2026-11-22 against Minecraft.Windows.exe 1.26.62.01).

## (5) PROOF ROWS — [V] verbatim against Minecraft.Windows.exe 1.26.62.01 (rdis dis; every quoted line matches rdis output exactly; re-checked by tools/sigs/verify_oc.py via the delegate check below)

| offset | size | site | verbatim `0xRVA  instr` | meaning |
|---|---|---|---|---|
| 0xBC60740 | - | bgfx/Encoder.h EncoderRvas.kSubmit = Encoder::submit entry | `0xBC60740  push r15` | submit entry; its body consumes the FrameOffsets constants the headers pin (item count Frame+0xDC57E8, sort keys +0x14700, sorted items +0x94700, draw headers +0xB4700 stride 0x80, RenderDraw array +0x8B4700 stride 0x540) [V rdis] |
| 0xE82E230 | - | bgfx/d3d12/D3D12Context.h D3D12Rvas.kSubmit = RendererContextD3D12::submit, vtable slot 50 | `0xE82E230  push rbp` | submit slot 50 entry; RenderLayoutAsserts kSubmit checks this function's body constants (0xdc57e8, 0x14700, 0xdc5808, 0xe746d8, 0x540, ...) [V rdis] |
| 0xE81E860 | - | bgfx/d3d12/D3D12Context.h D3D12Rvas.kPsoBuilder | `0xE81E860  push r15` | PSO builder entry pinned by D3D12Context.h [V rdis] |
| 0xE81B720 | - | bgfx/d3d12/D3D12Context.h drawFlush = DrawBatcher flush | `0xE81B720  push r15` | flush entry; its body reads DrawBatcherOffsets (ring slot +0xF28, record arrays +0x18, capacity +0x115C, indirect flag +0x1164) pinned by D3D12Context.h [V rdis] |
| 0xE9002E0 | - | dragon/Tasks.h TaskRvas.kDispatch = FrameGraph::taskDispatch | `0xE9002E0  push rbp` | taskDispatch entry pinned by Tasks.h; RenderLayoutAsserts kTaskDispatch checks 0x298/0x2A0 (DragonFrameResources task vector) and stride 0xFFFFFF80 [V rdis] |
| 0xC270460 | - | FrameGraph::endFrame entry | `0xC270460  push rbp` | endFrame entry; RenderLayoutAsserts kEndFrame checks its body [V rdis] |
| 0xDC57E8 | 4B | [rcx+0xDC57E8] | `0xBC607C2  mov eax,[rcx+0xDC57E8]` | FrameOffsets::kItemCount u32 draw-slot counter, cap 0xFFFE [V rdis + layoutcheck] |
| 0x14700 | 8B | [rcx+r14*8+0x14700] | `0xBC60991  mov [rcx+r14*8+0x14700],rax` | FrameOffsets::kSortKeys u64[] [V rdis + layoutcheck] |
| 0x94700 | 2B | [rax+r14*2+0x94700] | `0xBC6099C  mov [rax+r14*2+0x94700],di` | FrameOffsets::kSortedItems u16[] [V rdis + layoutcheck] |
| 0xB4700 | 8B | [rax+0xB4700] | `0xE821853  lea r8,[rax+0xB4700]` | FrameOffsets::kDrawHeaders RenderDrawHeader[] stride 0x80 base [V rdis + layoutcheck] |
| 0xDC5808 | 4B | imm32 address operand (no deref) | `0xE82E28D  add rdx,0xDC5808` | Frame backbuffer size {u32 width, u32 height} [V rdis + layoutcheck] |
| 0xE746D8 | 4B | [rsi+0xE746D8] | `0xE82E34C  mov r9d,[rsi+0xE746D8]` | Frame counter u32, +1 per frame [V rdis + layoutcheck] |
| 0x19F58 | 8B | [rdi+0x19F58] | `0xE82E353  mov rdx,[rdi+0x19F58]` | RendererContext resource-table pointer [V rdis + layoutcheck] |
| 0x1EAAC60 | 4B | [r11+rdx*4+0x1EAAC60] | `0xBC608FC  lock xadd [r11+rdx*4+0x1EAAC60],ecx` | bgfx Context m_seq[256] (per-view sequence, view array base 0x1EAB080) [V rdis + layoutcheck] |
| 0x35 | 1B | [rcx+0x35] | `0xC270483  cmp byte ptr [rcx+0x35],0` | BgfxContext early-out byte [V rdis + layoutcheck] |

Total: 14 distinct offsets, 0 duplicates; all instruction lines copied verbatim from rdis `dis` output against the exe. Sizes: dword/qword/word/byte accesses sized by the instruction; lea/imm32/prologue rows are address computations (no struct deref) and carry "-".

## (6) GAPS / RESIDUAL — none of them is missing reversing
- Builds are barred for this unit (OPENCODE_BRIEF rule 2), so the headers were not re-compiled in this session and the world-phase SelfTest has not run in the game. Compile-side evidence on disk: every M2 header's static_asserts are present in the files (inventory above) and 27/72 headers are directly compiled by a build TU (SelfTest.cpp or via AllDescriptions.h); the remainder are covered by SelfTestRenderLayoutCoverage.cpp (Caps.h/View.h/Handles.h/Uniforms.h/FrameBuilder.h) and FrameBuilderHook.cpp (FrameBuilder.h/Caps.h/Frame.h/Descriptions.h/RendererContext.h). Prior recorded standalone check (checklist O2a, zs_headers.ps1 /Zs): headers under bgfx/ and minecraft_renderer/ compile standalone, 0 failed. The remaining step is the Release build + link itself (batch step).
- The M2c checklist box is still [ ] on RENDER_CHECKLIST.md; this unit may not edit RENDER_CHECKLIST.md. On disk M2c is complete: all 50 DescriptionClones.h catalog entries map to compiled description structs (42 certain, 8 inferred-by-tag [?] — name equivalences only, no size/offset impact).
- The world-phase SelfTest run (vtable slots in .text, render-layout constants, ECS components on local player, selftest.txt report) is deferred per the user's 2026-11-22 decision (one big in-game test later). Not a blocker: the DEFERRED TESTING rule exempts builds and in-game runs from CLOSES? NO.
- No RVA, offset, meaning or [V] proof is unknown for M3a's wording. Sizes marked [I] inside headers (e.g. RenderAtmosphereDescription 0x138 aligned read end, editor gizmo extents) are explicitly tagged inference, not missing proof.

## CLOSES?
YES — every struct of M2 compiles as a header on disk (M2a–M2e inventory above; all headers carry size/offset static_asserts and are compiled in at least one build TU: SelfTest.cpp, SelfTestRenderLayoutCoverage.cpp, FrameBuilderHook.cpp), and the startup self-check validates the sizes/offsets that can be validated: SelfTest::runStatic() runs at App.cpp:111 (static phase: sig census + RenderLayoutAsserts code-constant checks; world phase: vtable slots in .text, checkRenderLayout constants, ECS probe), layoutcheck.py = 209/0 failed on 1.26.62.01 (exit 0), and all anchor RVAs/offsets above are rdis-verified verbatim. What remains is not reversing: the Release build/link (barred this session) and the live world-phase SelfTest run in game (deferred by the user's 2026-11-22 decision). docs/BIGBANG_TESTS.md already contains the U-EM3a section (item id, what to enable: build the Release client DLL so static_asserts run + SelfTest::runStatic() at App.cpp:111; exact in-game steps: build DLL, launch 1.26.62.01 into a populated world, wait for the world-phase SelfTest on the first GameUpdateEvent with a local player, read %APPDATA%\BlueySenseV2\diagnostics\selftest.txt; expected observable result: static phase "static: N passed, 0 failed" with no "sig dead" lines; world phase "world: N passed, 0 failed" with checkRendererVtables/checkRenderLayout/checkVtableSlot/checkComponentOnLocalPlayer all green; no render-layout or vtable drift lines). Append-only satisfied: no new section appended.

## TOOL REQUESTS
m2headercheck.py | SDK headers under src/sdk/mc/deps/bgfx/ (+d3d12/) and src/sdk/mc/deps/minecraft_renderer/framebuilder/ + DescriptionClones.h catalog | markdown inventory (structs per header, sizeof/offsetof static_assert pins, TU compile coverage, orphan headers, duplicate-definition review, catalog->struct mapping) | replaced an entirely-by-hand header inventory; keeps the M3a "every struct compiles as a header" invariant machine-checkable for any unit, and flags latent redefinition hazards before they break a build.
