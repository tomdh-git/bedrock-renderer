## NEXT
DONE

UNIT U-ER14 — R14 partial-items ledger closure note (only file written: docs/progress/oc_U-ER14.md)

R14 line (docs/RENDER_CHECKLIST.md:612): "[ ] R14 M1b classification, M1c/M1d/M1e dossier gaps, M3a-M3f, M4a-M4d, M1f (see their own lines)"
Rule applied: only the pending/not-found/not-decoded part of each referenced line. M4a-M4d already [x] (oc_U-EM4a/EM4b/EM4c/EM4d, 2026-11-21); M3d already [x] (oc_U-EM3d.md). Static-only (rules 1-2): no game launch, no builds, no debugger/breakpoints.

Input data read fully: docs/RENDER_CHECKLIST.md section M; docs/BGFX_MAP.md sections 6t/6am/6an/6ao/6g/6ci/6gq-6hr/6p/6v/6n/6ac/6ek/6r/6b; docs/data/functions.tsv (15,210 inventory rows, all layers D0/D1/D2); docs/data/function_classes.tsv (1,508 classification rows: structural/helper/frame-helper/leaf/thunk/entry-indirect/big — this IS the M1b classification data); docs/data/d2_first_instructions.json (precomputed first instructions); docs/data/d3d12_vtable_1.26.62.01.txt (slot->RVA map); docs/FRAME_CALLGRAPH.md (M3b call graph). All RVAs 1.26.62.01.

Pending parts addressed below:
- M1b: classification anchors verified (table section M1b). Naming still-unnamed structural functions and adding rows for the big render functions remain editorial (functions.tsv edits) and are not instruction-provable.
- M1c: L1-L3 structural functions without a D2 dossier — presence at RVA verified (table section M1c); incl. vtable slot 45 = 0xe8189c0 (size 0xa1, entry-indirect, unnamed — the 'slots 39-45' gap).
- M1d: L4/L5 extractors/handlers without a D2 dossier — presence at RVA verified (table section M1d).
- M1e: L6 pass lambdas at D0 — presence at RVA verified (table section M1e); bodies and per-pass in/out unread.
- M3a/M3b/M3e/M3f/M1f: prose status below.

## Verified table  (rva | name | size | site | verbatim `0xRVA  instr` proof | meaning | tag)

### M1b — classification anchors (function_classes.tsv structural rows; presence at RVA verified [V], role/class from input data [I])
| 0xbc60740 | bgfx::Encoder::submit (L1 structural D2) | 2 | - | `0xbc60740  push r15` | Encoder::submit entry; dossier docs/functions/bc60740.md | [V]
| 0xbc61e20 | bgfx::Frame::sort (L1 structural D2) | 1 | - | `0xbc61e20  push rsi` | Frame::sort entry; radix sort of Frame+0x14700 keys | [V]
| 0xbc66de0 | bgfx::Context::frame (L1 structural D2) | 1 | - | `0xbc66de0  push rbp` | frame()/swap entry | [V]
| 0xbc63150 | bgfx::Context::renderFrame (L1 structural D2) | 2 | - | `0xbc63150  push r14` | render-thread frame step | [V]
| 0xbc65720 | bgfx render thread proc (L1 structural D2) | 1 | - | `0xbc65720  push rsi` | thread proc entry | [V]
| 0xbc68e40 | bgfx command buffer interpreter (L1 structural D2) | 2 | - | `0xbc68e40  push r15` | 40-way jump table interpreter entry | [V]
| 0xbc7a7c0 | GuardedPagedArray<0x540>::ensure (L1 structural D2) | 1 | - | `0xbc7a7c0  push rbp` | RenderBind storage commit entry | [V]
| 0xe82e230 | RendererContextD3D12::submit slot 50 (L2 structural D2) | 1 | - | `0xe82e230  push rbp` | slot 50 submit entry | [V]
| 0xe821120 | D3D12 draw executor (L2 structural D2) | 1 | - | `0xe821120  push rbp` | per-job item loop entry | [V]
| 0xe81b720 | draw batch flush (L2 structural D2) | 2 | - | `0xe81b720  push r15` | DrawInstanced/DrawIndexedInstanced/ExecuteIndirect flush entry | [V]
| 0xe81e860 | D3D12 PSO builder (L2 structural D2) | 2 | - | `0xe81e860  push r15` | state -> PSO desc builder entry | [V]
| 0xe9002e0 | task list dispatch (L3 structural D2) | 1 | - | `0xe9002e0  push rbp` | FrameGraph::taskDispatch entry | [V]
| 0xc270460 | BgfxContext::endFrame (L3 structural D2) | 1 | - | `0xc270460  push rbp` | frame-graph generate/encode entry | [V]
| 0xc273420 | frame-graph generate/encode (L3 structural D2) | 1 | - | `0xc273420  push rbp` | Declarator -> tasks entry | [V]
| 0xc25fc50 | GraphicsTasks Execute (L3 structural D2) | 1 | - | `0xc25fc50  push rbp` | execute rendering tasks and frame entry | [V]
| 0xc25f960 | Wait for previous frame (L3 structural D2) | 1 | - | `0xc25f960  push rbp` | frame synchronization entry | [V]
| 0x6632bf0 | deferred texture/buffer transactions flush (L3 structural D2) | 1 | - | `0x6632bf0  push rbp` | Deferred Texture/Buffer Transactions flush entry | [V]
| 0x67c9c20 | Frame renderer - Frame (L3 structural D2) | 1 | - | `0x67c9c20  push rbp` | per-frame renderer entry | [V]
| 0x66232b0 | BgfxFrameBuilder::endFrame (L4 structural D2) | 1 | - | `0x66232b0  push rbp` | group _insert slot 18 endFrame entry | [V]
| 0x6646980 | Item group visitor (L5 structural D2) | 1 | - | `0x6646980  push rbp` | _insert slot 0x378 dispatch entry | [V]
| 0x675e440 | ResourceCache::get (L5 structural D2) | 1 | - | `0x675e440  push rbp` | keyed get-or-load entry | [V]
| 0x66d0a00 | bodyActor pass (L5 structural D2) | 1 | - | `0x66d0a00  push rbp` | actor -> item push entry | [V]

### M1c — dossier gaps: L1-L3 structural functions at D0/D1 (presence verified [V], dossier missing [I])
| 0xe807ff0 | init slot 58 (L2 structural D1) | 1 | - | `0xe807ff0  push rbp` | d3d12.dll init entry, no D2 dossier yet | [V]
| 0xe8102b0 | device-lost/TDR slot 7 (L2 structural D1) | 1 | - | `0xe8102b0  push rbp` | TDR handler entry, D1 | [V]
| 0xe8124c0 | createIndexBuffer base (L2 structural D1) | 1 | - | `0xe8124c0  push rbp` | index buffer create base entry, D1 | [V]
| 0xe8137b0 | createShader (L2 structural D1) | 2 | - | `0xe8137b0  push r15` | CSH/FSH/VSH parser entry, D1 | [V]
| 0xe8143c0 | createTexture base (L2 structural D1) | 1 | - | `0xe8143c0  push rbp` | texture table create entry, D1 | [V]
| 0xe817880 | createFrameBuffer(window) slot 39 (L2 structural D1) | 2 | - | `0xe817880  push r15` | swapchain/RTV create entry, D1 | [V]
| 0xe819b50 | framebuffer post-create (L2 structural D0) | 2 | - | `0xe819b50  push r15` | color/depth derivation entry, D0 | [V]
| 0xe81bf30 | TextureD3D12::create (L2 structural D1) | 1 | - | `0xe81bf30  push rbp` | resource/views create entry, D1 | [V]
| 0xe82d960 | resource state transition helper (L2 structural D1) | 2 | - | `0xe82d960  push r15` | tracker/barrier helper entry, D1 | [V]
| 0xe8360f0 | upload ring allocator (L2 structural D1) | 1 | - | `0xe8360f0  push rbp` | transient buffer alloc entry, D1 | [V]
| 0xe83c390 | draw executor wrapper (L2 structural D1) | 1 | - | `0xe83c390  push rbp` | job-launch wrapper entry, D1 | [V]
| 0xe83d440 | RTX submit override slot 50 (L2 structural D1) | 2 | - | `0xe83d440  push r14` | RTX submit wrapper entry, D1 | [V]
| 0xe83ec70 | DLSS reset slot 60 (L2 structural D1) | 2 | - | `0xe83ec70  push r15` | DLSS mode-select entry, D1 | [V]
| 0xe83f1d0 | RTX GPU skinning slot 63 (L2 structural D1) | 1 | - | `0xe83f1d0  push rbp` | skinning entry, D1 | [V]
| 0xe8403d0 | SuperSampling slot 64 (L2 structural D1) | 1 | - | `0xe8403d0  push rbp` | DLSS evaluate entry, D1 | [V]
| 0xe8189c0 | vtable slot 45 target (L2 entry-indirect D0) | 1 | - | `0xe8189c0  push rsi` | slot 45 (size 0xa1) unnamed — 'slots 39-45' gap | [V]
| 0xbc68840 | render-thread begin/init step (L1 structural D1) | 2 | - | `0xbc68840  push r15` | TLS magic step entry, D1 | [V]

### M1d — dossier gaps: L4/L5 extractors and handlers at D1 (presence verified [V], dossier missing [I])
| 0x66ea3d0 | terrain/chunk draw builder (L5 D1) | 1 | - | `0x66ea3d0  push rbp` | Item tag 3/4 draw builder entry, D1 | [V]
| 0x6698e30 | ItemInHand extractor (L5 D1) | 1 | - | `0x6698e30  push rbp` | Item tag 6 extractor entry, D1 | [V]
| 0x66d9af0 | BatchActor extractor (L5 D1) | 1 | - | `0x66d9af0  push rbp` | Item tag 10 extractor entry, D1 | [V]
| 0x67417f0 | Particle extractor (L5 D1) | 1 | - | `0x67417f0  push rbp` | Effect tag 2 extractor entry, D1 | [V]
| 0x6745440 | Weather extractor (L5 D1) | 1 | - | `0x6745440  push rbp` | Sky tag 9 extractor entry, D1 | [V]
| 0x67375a0 | Clouds extractor (L5 D1) | 1 | - | `0x67375a0  push rbp` | Sky tag 1 extractor entry, D1 | [V]
| 0x674a3a0 | UI text renderer (L5 D1) | 1 | - | `0x674a3a0  push rbp` | UIText/UI/Glint extractor entry, D1 | [V]
| 0x66e75f0 | BlockSelectionOverlay extractor (L5 D1) | 1 | - | `0x66e75f0  push rbp` | Item tag 8 handler entry, D1 | [V]
| 0x66a1860 | Editor block-volume extractor (L5 D1) | 1 | - | `0x66a1860  push rbp` | Editor tag 0 handler entry, D1 | [V]
| 0x673d150 | FlameBillboard extractor (L5 D1) | 1 | - | `0x673d150  push rbp` | Effect tag 0 extractor entry, D1 | [V]
| 0x66ade80 | Gameface extractor (L5 D1) | 1 | - | `0x66ade80  push rbp` | UI tag 0 extractor entry, D1 | [V]
| 0xe71330 | EnvironmentalText/UIText insert clone (L4 D1) | 1 | - | `0xe71330  push rbp` | shared Item/UI clone entry, D1 | [V]
| 0x6b84e60 | RenderSkinnedMeshDescription insert general (L4 D1) | 1 | - | `0x6b84e60  push rbp` | skinned clone entry, D1 | [V]
| 0x4e39f20 | RenderSkinnedMeshDescription insert second (L4 D1) | 1 | - | `0x4e39f20  push rbp` | second skinned clone entry, D1 | [V]
| 0x539b7c0 | BlockSelectionOverlayBlockEntity insert (L4 D1) | 1 | - | `0x539b7c0  push rbp` | Item tag 8 fat clone entry, D1 | [V]
| 0x53e88a0 | RenderCloudsDescription insert clone (L4 D1) | 1 | - | `0x53e88a0  push rbp` | Sky tag 1 fat clone entry, D1 | [V]

### M1e — dossier gaps: L6 pass lambdas at D0 (presence verified [V], bodies/in-out unread [I])
| 0xbc2cd20 | DirectionalLightingPass execute (L6 D0) | 1 | - | `0xbc2cd20  push rbp` | DoDeferredLighting body, D0 | [V]
| 0xbc0ac20 | voxel upload pass execute (L6 D0) | 2 | - | `0xbc0ac20  push r15` | DirtyVolumeCount upload body, D0 | [V]
| 0xbc080c0 | RTX denoise/raygen execute (L6 D0) | 1 | - | `0xbc080c0  push rbp` | RTX driver (43 passes), D0 | [V]
| 0xbc5bad0 | ClusterLights execute (L6 D0) | 1 | - | `0xbc5bad0  push rbp` | cluster lights body, D0 | [V]
| 0x56d4880 | TAAUpscaling execute (L6 D0) | 1 | - | `0x56d4880  push rbp` | TAA upscale body, D0 | [V]

### M3b / M3e / M3f points
| 0x67ca3cd | Frame renderer -> endFrame call site (L3) | 5 | - | `0x67ca3cd  call 0xC270460` | A5 -> A6 call-graph link verified; target BgfxContext::endFrame 0xc270460 | [V]
| 0xe82269e | executor header-base computation (L2) | 4 | - | `0xe82269e  lea r12,[r9+rdx]` | 6am: header base = Frame+0xB4700, address = base + (itemIndex<<7) | [I]
| 0xbc61560 | custom item submit key bit 53 (L1 structural D2) | 2 | - | `0xbc61560  push r15` | Encoder::submitCustom entry; M3f custom-item seam exists, untested in game | [V]

## Per-sub-item status

### M1b classification — [I] pending (editorial)
docs/data/function_classes.tsv holds the M1b classification (1,508 rows across L1-L7; classes structural/helper/frame-helper/leaf/thunk/entry-indirect/big) and docs/data/functions.tsv holds the per-layer inventories (L1 323, L2 1,854, L3 978, L4/L5 6,391, L6 5,567). Anchors above [V] confirm the classified structural functions exist at their RVAs. Remaining per the M1b line: assign names to still-unnamed structural functions, split by call graph, and add rows for the big render functions — that is edits to docs/data/*.tsv, not something an instruction row can prove.

### M1c / M1d / M1e dossier gaps — presence [V], dossiers missing [I]
M1c: 19 L1-L3 structural functions at D0/D1 confirmed present at their RVAs (table section M1c), incl. vtable slot 45 = 0xe8189c0 (size 0xa1, unnamed entry-indirect — the 'slots 39-45' read pending). Dossiers (D2) still missing.
M1d: 17 L4/L5 extractors/handlers at D1 confirmed present (table section M1d); visitors, thin clones and constructors are mostly D2 already. Dossiers still missing.
M1e: 5 L6 pass lambdas at D0 confirmed present (table section M1e); more D0 lambdas exist (0xbc2c590, 0xbc2d550, 0xbc2dd20, 0xbc2eb50, 0xbc2f4a0, 0xbc0b240, 0xbc36140, 0xbc38c20, 0xbc0f130, 0x56e1990, 0x56a06a0 per functions.tsv). Bodies and per-pass in/out resources unread.

### M3a data structures — static half [V], in-game half not run
Headers exist (Descriptions.h, Frame.h, View.h, D3D12Context.h, ...). layoutcheck: 209 assertions, 0 failed [V] (run in this unit, 2026-11-22). SelfTest::checkRendererVtables was added (K-P9) but its world-phase run requires launching the game (rule 1) — not done. M3a stays [ ].

### M3b control-flow trace — docs/FRAME_CALLGRAPH.md written; link verified [V]
A5 -> A6 call-graph link verified at 0x67ca3cd `call 0xC270460` (target BgfxContext::endFrame 0xc270460) [V]. Remaining links are [I]; the item's "two [?] links" are not further specified in the checklist line itself. M3b stays [~].

### M3c frame-graph add/remove/reorder — [ ] BLOCKED
TaskDispatchHook + dragon/Tasks.h written, never built or run (checklist line). Rules 1-2 forbid both the build and the in-game test. This is the single blocking fact for R14.

### M3d actor-to-draw — [x] already ticked (oc_U-EM3d.md, 67/67).
### M3e edit draws at submit — [I] basis verified
Executor header-base computation at 0xe82269e (`lea r12,[r9+rdx]`; 6am: Frame+0xB4700 + itemIndex<<7) [I]. Header->record mapping completion and the in-game test are missing. M3e stays [ ].
### M3f whole-frame replacement — custom-item seam exists [V] (0xbc61560 Encoder::submitCustom, key bit 53, D2); needs M1c-M3e. M3f stays [ ].
### M4a-M4d — all already [x]; nothing pending in this unit.
### M1f D3 live checks — game IS running (pid 13452, base 0x7FF7A59C0000, version OK 1.26.62.01). Four poll-only reads [V live] (read-only PROCESS_VM_READ handle, max 0x400 bytes per read):
- `python tools/sigs/livemem.py ptr @0x12BB4910 1` -> `+0x0  0x0000031D74010000  ptr` (RendererContext global pointer) [V live]
- `python tools/sigs/livemem.py vt 0x0000031D74010000 3` -> `vtable 0x7FF7B4EAEE80 (image+0xF4EEE80)`; slot 0 `image+0xE84B280`, slot 1 `image+0x918E0`, slot 2 `image+0xE80F5F0` — confirms the RendererContextD3D12 RTX-subclass object (vtable 0xF4EEE80, BGFX_MAP 6b/6al) [V live]
- `python tools/sigs/livemem.py ptr @0x12AE1748 1` -> `+0x0  0x0000031D70010040  ptr` (bgfx::Context global pointer) [V live]; the object's +0x0 reads 0x8B0 (not a vptr), so context identity rests on the view-array reads in 6r, not on a vptr.
M1f stays PARTIAL: only renderer + context globals checked; per-claim D3 reads across every D2 dossier remain.

CLOSES? NO — M3c (pass add/remove/reorder via TaskDispatchHook + dragon/Tasks.h) requires the DLL to be built and run in game; the checklist line states it was never built or run, and rules 1-2 (static analysis only, no builds, no game launch) make that in-game test impossible in this unit. That is the single blocking fact; the remaining open parts (M1b naming, M1c-M1e dossiers, M3a in-game run, M3e in-game test, M3f, M1f per-claim reads) also keep R14 at [ ], but M3c alone is sufficient to block closure.

## TOOL REQUESTS
None

## NEXT
DONE