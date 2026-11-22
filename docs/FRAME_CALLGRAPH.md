# One frame, game logic to D3D12 submit (call-graph table)

Checklist item M3b. Built from the function dossiers in `docs/functions/`, BGFX_MAP sections 6n..6ew and `docs/data/functions.tsv`.
All RVAs are 1.26.62.01 unless noted. Tags: [V] read in the disassembly, [I] inferred, [?] open. Everything here is static; nothing was observed live except where BGFX_MAP says so.
"D2" = dossier with pseudocode exists, "D1" = named/described only.

## Thread A: game/render-prep thread (produces the Frame)

| # | Function (rva) | Status | Called by / how | Arguments / data handed on | Notes |
|---|---|---|---|---|---|
| A1 | FrameBuilder::insert<T> clones (62 types, e.g. Nametag clone 0x1127330) | D1 | game extraction code | `{description*, tag}` variant into group slot (Editor 0x358, Effect 0x360, UI 0x368, Sky 0x370, Item 0x378, Light 0x380) | `ExtractionObserver` hooks these slots (unbuilt) [V static] |
| A2 | Group visitors (Item 0x6646980, etc.) | D1 | via the slot | `(this, frameCtx, variant)` -> per-description extractor (0x6698e30 ItemInHand, 0x66d9af0 BatchActor, ...) | extractors build draws through Encoder::submit [V] |
| A3 | `BgfxFrameBuilder::endFrame` 0x66232b0 | D2 | vtable slot 18 of the frame builder [V 6g] | `this = BgfxFrameBuilder`, `[this+0x28]` = BgfxContext | stage map in `docs/functions/66232b0.md` |
| A3a | Deferred flush 0x6632bf0 (start and end of A3) | D2 | A3 at 0x66233ae / 0x662e3b4 | `DeferredTransactions*` (buffer vec +0x18, texture vec +0x00) | buffers first, then textures; jobs run via vtbl[1] then deleted [V] |
| A3b | Task runner 0xc25fe20 | D2 | A3 at 0x662358a (also Execute, 0xc260050) | task queue | drains queued std::function tasks FIFO [V] |
| A3c | Wait for previous frame 0xc25f960 | D2 | A3 at 0x6623881 and 0x662da86 | `GraphicsTasks*` | joins pending-frame futures; calls Execute if mode == 1 [V] |
| A3d | GraphicsTasks Execute 0xc25fc50 | D2 | A3c, Render lambda 0xc267200 | `GraphicsTasks*` (+0x140 context) | runs task runner then **bgfx frame() 0xbc65800** [V] |
| A4 | bgfx `Context::frame(capture)` 0xbc65800 | D2 | A3d (also 0xbc660a0 shutdown, 0xbc63c80) | `(Context*, flags edx)` | writes present record into surface tail block, waits N-1 on sem ctx+0x100, copies timing, calls swap 0xbc66de0 [V] |
| A4a | Swap 0xbc66de0 | D2 | A4 | `Context*` | memcpy view remap (0x200), view structs (0x14000), view flags (0x100) into the submit Frame; drains destroy queues; ++Frame+0xE746D8 [V] |
| A5 | Frame renderer lambda 0x67c9c20 ("Frame renderer - Frame") | D2 | task system via vtable slot 0 of .rdata vtable 0xf2beb90 [V]; not a direct call; dispatch mechanism [I] | closure `rsi`: Context at `[[rsi+0x20]]`, DFR at `[rsi+0x10]+0x268` | sets up 7 resource sets, then calls A6 at 0x67ca3cd with rcx=bgfxCtx, rdx=DFR, r8=Declarator, r9=allocator; names vector EMPTY [V]; dossier docs/functions/67c9c20.md |
| A6 | `BgfxContext::endFrame` 0xc270460 | D2 | A5 at 0x67ca3cd | `(BgfxContext*, DragonFrameResources&, Declarator&, IntraFrameAllocator&, vector<HashedString>&& (empty))` | calls A7 at 0xc270521 then A8 at 0xc270554 [V] |
| A7 | Frame-graph generate/encode 0xc273420 | D2 | A6 at 0xc270521 | `(S* {ctx+0x38,+0x40/+0x48,+0x50,IFA}, out, Declarator, names)` | per-pass loop 0xc277e8c..0xc2793fe; ordering stage skipped (names empty); stable_sort 0xc280ca0/0xc280010 on key +0x78 [V]; dossier docs/functions/c273420.md (innermost dep sub-steps callee-delegated [I]) |
| A8 | Task dispatch 0xe9002e0 | D2 | A6 | `(TaskList*, args)` | TaskList of 0x80-byte entries (18 in a sampled world frame); registers kind-1 tasks into DFR+0x298/+0x2A0 [V live+static] |
| A9 | Pass task bodies (object+0x70 std::function) | D0/D1 | A8 via vtbl | per-task `{obj, ctrl, kind, name}` | e.g. Scene/HUD per-view setup 0x568CD90 writes view rect/matrices/sort mode [V static] |
| A10 | `Encoder::submit` family 0xbc60740 (+variants 0xbc61140, 0xbc61560, 0xbc618e0 = 6cr values +0xC00) | D2 | extractors and pass bodies (callers 0x569a3a0, 0x56ad350, 0x56ad810, 0xbcc39b0..) | `(Encoder*, viewId, program, occlusionQuery, depth, preserveState)` | allocates draw slot (CAS Frame+0xDC57E8), writes key/header/0x540 RenderDraw [V] |
| A11 | Resource creation commands | D2 | game/bgfx API calls | bytes into Frame cmdPre (+0xDC5818/0xDC5820) / cmdPost (+0xE05820/0xE05828) | consumed on the render thread at B3/B5 [I] |

## Thread B: bgfx render thread (consumes the Frame)

| # | Function (rva) | Status | Called by / how | Arguments / data handed on | Notes |
|---|---|---|---|---|---|
| B1 | Thread proc 0xbc65720 | D2 | created by 0xbc63690 ("bgfx - renderer backend thread") | `Context*` | loops `renderFrame(5000)` until Exiting [V] |
| B2 | `Context::renderFrame(msecs)` 0xbc63150 | D2 | B1 (and 0xbc63060, swap 0xbc66de0 in single-thread mode) | `(Context*, msecs)` | order of calls: device-reset notifications -> sem wait ctx+0x80 -> 0xbc68840 -> cmdPre exec -> submit -> cmdPost exec -> sem post ctx+0x100 [V] |
| B3 | Render-thread begin/init step 0xbc68840 | D2 | B2 at 0xbc63340 (+B4) | `Context*` | TLS render-thread identity vs magic 0x78666762 [V]; surface wait table + call 0xEBDBC90 [V]; dossier docs/functions/bc68840.md |
| B4 | Command interpreter 0xbc68e40 | D2 | B2 (cmdPre at 0xbc6337b, cmdPost at 0xbc633c4) | `(Context*, CommandBuffer*)` | 40-entry jump table (0xf449638) -> RendererContext virtuals (createTexture = slot 26 etc.) [V] |
| B5 | Renderer slot 50 `submit` | D2 | B2 at 0xbc633a8 (`[rax+0x190]`) | `(RendererContextD3D12*, Frame*, ...)` | RTX override 0xe83d440 wraps the base 0xe82e230 [V] |
| B5a | `RendererContextD3D12::submit` base 0xe82e230 | D2 | B5 override | `(this, Frame*)` | stage map 6t [V order] |
| B5b | `Frame::sort` 0xbc61e20 | D2 | B5a | `Frame*` | radix sort of keys Frame+0x14700 into Frame+0x94700 [V] |
| B5c | Draw executor 0xe821120 (wrapper 0xe83c390 launches the job) | D2-partial | B5a [?: the call from submit to the wrapper is not re-verified] | per-job state | item loop: branch A resolves program variant, branch B (0xe829b50) draws; PSO via B5d [V] |
| B5d | PSO builder 0xe81e860 | D2-partial | B5c | `(ctx, ?, frame, S, state2, ...)` | key = `S & 0x0707007FFFFFF0FF` [V] |
| B5e | Draw flush 0xe81b720 | D2 | B5c (7 sites) | DrawBatcher records (0x70/0x88) | ID3D12GraphicsCommandList calls (DrawInstanced idx 12, DrawIndexedInstanced 13, ExecuteIndirect 59, ...) [V] |

## What the table still lacks (so M3b stays [~])

- A1/A2 groups have no per-type dossier yet (M1d; separate unit); A9 pass bodies mostly D0 (separate unit). A5/A7/B3 are D2 (dossiers in docs/functions/).
- Link task system -> A5: RESOLVED [V]: `rdis callers 0x67c9c20` = zero direct callers; invoked via vtable slot 0 of .rdata vtable 0xf2beb90 (slot 0 = sub_67c9c20, push rbp, size 0x966); dispatch mechanism [I].
- Link B5a submit -> executor wrapper 0xe83c390: RESOLVED negative [V]: submit body 0xe82e230 has no reference to 0xe83c390; at 0xe83159f submit does `lea r9,[0xE83C390]` then `0xe8315ad  call qword ptr [0xF99FFA0]` (indirect dispatch via CFG thunk, rcx via [0x12adf808], rdx task object [rbp+0x1590], r9=&wrapper); `rdis callers 0xe83c390` = zero; wrapper's sole callee is 0xe821120 [V]. Executor runs as a dispatched job from submit, not submit's direct callee.
- Frame-to-frame hand-off between thread A and B is by semaphores (ctx+0x80 "frame ready", ctx+0x100 "frame consumed") plus the Frame pair at ctx+0x1cfd0c0/+0x1cfd0c8 [V 6as].
