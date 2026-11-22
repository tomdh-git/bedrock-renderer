## NEXT
DONE

UNIT: U-EM3a
GOAL: Close checklist item M3a — "Data structures: every struct of M2 compiles as a header and a startup self-check validates sizes/offsets that can be validated (static_asserts + SelfTest)" [RENDER_CHECKLIST.md line 453]; mirrored by O3a (line 518, still [ ]).

STATUS: On-disk inventory complete. CLOSES? = NO.

BLOCKING FACT: M2c is open. RENDER_CHECKLIST.md lines 445-451 mark M2c "Every description type (62) as struct (Descriptions.h)" as [ ] OPEN: only 27 of 62 description types are typed as structs with static_asserts; 35 have no struct/header (e.g. RenderBlitFlipbookDescription 0xA0). M3a requires "every struct of M2 compiles as a header", so M3a cannot be closed on disk until M2c provides headers for all 62 description types. M2c is its own checklist item; M3a does not close it.

SECONDARY GAPS (cannot be closed under this unit's constraints — existing src/sdk/SelfTest.cpp and CMake may not be edited, and no build or game launch is permitted):
- SelfTest.cpp includes bgfx/RenderLayoutAsserts.h, bgfx/RendererContext.h, bgfx/Encoder.h, bgfx/Frame.h, bgfx/d3d12/D3D12Context.h, dragon/Tasks.h, framebuilder/Descriptions.h, framebuilder/DrawItem.h (static_asserts at lines 25-30), but NOT bgfx/Caps.h, bgfx/View.h, bgfx/Handles.h, bgfx/Uniforms.h, framebuilder/FrameBuilder.h, renderer/MeshData.h — so those headers' static_asserts do not run in any build.
- SelfTest runtime (runWorld: vtable slots in .text, RenderLayoutAsserts kFunctions code-constant checks, ClientInstance vtable slots, ECS components) is not verifiable without building and launching the game (O3a: "Release build OK, not run in game").

WHAT IS TRUE ON DISK (no build required):
- Every M2a/M2b/M2d/M2e struct has a header containing static_asserts on size/offsets (see INVENTORY below).
- SelfTest.cpp runs static_asserts (every build) plus RenderLayoutAsserts.h code-constant/vtable validation at startup (runStatic/runWorld).
- All RVA anchors used in the headers match the exe disassembly (see PROOF ROWS below; verified with rdis against Minecraft.Windows.exe 1.26.62.01).

M2 SUB-ITEM STATUS [RENDER_CHECKLIST.md lines 445-451]
| sub-item | status | headers | notes |
| M2a | DONE [x] | bgfx/Frame.h, View.h, Encoder.h, Caps.h (bgfx/Handles.h, bgfx/Uniforms.h per A13 tick) | Frame/View/RenderDrawHeader/Encoder/Caps structs + static_asserts |
| M2b | DONE [x] | bgfx/d3d12/D3D12Context.h | DrawBatcherOffsets, draw records, JobContextOffsets, resource tables |
| M2c | OPEN [ ] | framebuilder/Descriptions.h (partial) | 27/62 descriptions typed; 35 missing structs — BLOCKS M3a |
| M2d | DONE [x] | framebuilder/DrawItem.h, FrameBuilder.h | DrawItem 0xC8, RenderBatchActorDescription, InsertVariant, FrameBuilderSlots |
| M2e | DONE [x] | bgfx/d3d12/D3D12Context.h | resource records: texture 0xB8, vertex 0x78, index 0x80, framebuffer 0x68, program 0xF8, shader 0xB8, uniform 0x68 |

M2 HEADER / STATIC_ASSERT / SELFTEST INVENTORY
| header | structs with static_asserts | key size/offset constants | in SelfTest.cpp? |
| bgfx/Frame.h | FrameOffsets, RenderDrawHeader (0x80), RenderDraw (packed 0x80), RenderStream (8B), RenderCompute (0x24) | kItemCount 0xDC57E8, kSortKeys 0x14700, kSortedItems 0x94700, kDrawHeaders 0xB4700, kRenderDraws 0x8B4700, stride 0x540, kFrameSize 0xE749C0 | YES |
| bgfx/Encoder.h | EncoderOffsets, Binding (0x14), DrawState bit map, SortKey decoders | kFrame 0x00, kHeader 0x40, kState 0x60, kRenderBind 0x140, kBindHash 0x654, kPostCallback 0x680, kBindDirty 0x688, kCustomItem 0x100, kCompute 0xC0 | YES |
| bgfx/View.h | ViewRecord | kBase 0x1EAB090 [V live], kStride 0x140, rect +0x00, view +0x10, proj +0x50, sortMode +0x122 [V]; array base 0x1EAB080 [V 6q] | NO |
| bgfx/Caps.h | (no struct — CapsGlobals offsets + CapsLimit/CapsFlag enums) | .data RVAs 0x12ADFA50 supported, 0x12AE0D58 limits | NO |
| bgfx/Handles.h | HandleAllocHeader (4B), HandleAllocators, DynamicHandleAlloc (kObject 0x1DF3460), ContextTextureState | allocator offsets e.g. kIndexBuffers 0x1DE534C cap 4096 | NO |
| bgfx/Uniforms.h | UniformRecord (0x18) | UniformRegistry kRecords 0x1E1DAA8 stride 0x18, kHashKeys 0x1E1C2A4, kHashHandles 0x1E1D2A4 | NO |
| bgfx/RendererContext.h | RendererContextSlots | kBaseVtable 0xF4ED2D0, kRtxVtable 0xF4EEE80, kSubmit slot 50, kSlotCount 65 | YES |
| bgfx/d3d12/D3D12Context.h | D3D12Rvas, D3D12Offsets, D3D12Tables, FrameBufferRecordLayout (0x68), DrawBatcherOffsets, BatchDraw (0x70), BatchDrawIndexed (0x88), JobContextOffsets, TextureRecordLayout (0xB8), BufferRecord (0x78), VertexLayoutRecord (0x54), ShaderRecord/ProgramRecord/PredefinedUniform, CommandQueue/Fence/CommandContextOffsets | kSubmit 0xE82E230 [V slot 50], drawExecutor 0xE821120, psoBuilder 0xE81E860, drawFlush 0xE81B720, kRendererGlobal 0x12BB4910; table strides 0xB8/0x78/0x80/0x78/0xB8/0xF8/0x68/0x54 | YES |
| dragon/Tasks.h | TaskListEntry (0x80), TaskList, TaskOffsets, ViewRefOffsets, TaskTail | TaskRvas kDispatch 0xE9002E0 [V] | YES |
| framebuilder/Descriptions.h | 27 typed descriptions w/ static_asserts (SharedRef 0x10) | RenderNametagDescription 0x98, RenderCloudsDescription 0xA8, RenderSkinnedMeshDescription 0x1D0, RenderWeatherDescription 0x130, RenderParticleDescription 0xB0, RenderFlameBillboardDescription 0xF8, RenderGameFaceDescription 0x78, RenderCubemapDescription 0xC0, RenderAtmosphereDescription 0x138, RenderBlockChangesDescription 0x18, ... | YES |
| framebuilder/DrawItem.h | DrawItem (0xC8), DrawItemShared (0x38), DrawItemSmallVector (0x30), DrawItemBounds (0x2C), DrawItemTransform (0x48), DrawItemState (0x58), DrawItemShaderState (0x88), DrawItemVertexStream (0x28), DrawItemGeometry (0x58) | DrawItem 0xC8 payload | YES |
| framebuilder/FrameBuilder.h | RenderBatchActorDescription (kMinSize 0x110, Instance 0x48 stride, RenderControllerMesh 0x2C0, HandleGroup 0x24), InsertVariant, FrameBuilderSlots | kEndFrame 0x90, kInsertItem 0x378 | NO |
| renderer/MeshData.h | MeshData (sizeof 0x160) | every field static_asserted | NO |

PROOF ROWS — RVA anchors verified against exe disassembly (rdis, Minecraft.Windows.exe 1.26.62.01)
| RVA | symbol | header anchor | instr | meaning |
| 0xBC60740 | Encoder::submit | bgfx/Encoder.h EncoderRvas.kSubmit | `0xBC60740  push r15` | submit entry; consumes FrameOffsets constants (BGFX_MAP 9b [V]) |
| 0xE82E230 | D3D12Context::submit (RendererContext vtable slot 50) | bgfx/d3d12/D3D12Context.h D3D12Rvas.kSubmit | `0xE82E230  push rbp` | submit slot 50 |
| 0xE821120 | drawExecutor | bgfx/d3d12/D3D12Context.h | `0xE821120  push rbp` | draw executor entry |
| 0xE81E860 | psoBuilder | bgfx/d3d12/D3D12Context.h D3D12Rvas.kPsoBuilder | `0xE81E860  push r15` | PSO builder entry |
| 0xE81B720 | drawFlush | bgfx/d3d12/D3D12Context.h | `0xE81B720  push r15` | draw flush entry |
| 0xE9002E0 | FrameGraph::taskDispatch | dragon/Tasks.h TaskRvas.kDispatch | `0xE9002E0  push rbp` | taskDispatch entry |

VERDICT
CLOSES? = NO — blocked by M2c open (35/62 description types lack structs/headers). M3a's "every struct of M2 compiles as a header" is not met on disk. SelfTest + static_asserts exist for the typed M2 structs; the missing pieces are the M2c headers (M2c's own item) plus the SelfTest wiring gaps listed above (not editable under this unit's constraints).

REMAINING / NEXT STEPS (verifiable, not done in this unit):
1. Close M2c: provide headers + static_asserts for the remaining 35 description types (e.g. RenderBlitFlipbookDescription 0xA0).
2. (Blocked by constraints) Add bgfx/Caps.h, bgfx/View.h, bgfx/Handles.h, bgfx/Uniforms.h, framebuilder/FrameBuilder.h, renderer/MeshData.h includes to src/sdk/SelfTest.cpp so their static_asserts run in every build.
3. (Blocked by constraints) Build and run the game to confirm SelfTest runWorld passes (O3a "not run in game").

No changes to src/**, HookManager.cpp, CMake, or Sigs.json were made; output file only = docs/progress/oc_U-EM3a.md.
