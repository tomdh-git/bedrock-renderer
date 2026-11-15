# re_a4a8 — A4-A8 bgfx core context/handle management

## NEXT
- Resume (if continuing): (1) map `0xbc771f0`/`0xbc76e80` callers to specific handle allocator instances and resource kinds (index/vertex/shader/program/texture/uniform/framebuffer/vertex-layout) to close A8a/A8b lifecycle gaps; (2) locate "encoder pool" allocation/reuse (search for Encoder-sized objects, `0xbc60740`/encoder reset paths, frame-side encoder storage) — currently no static evidence found; (3) decode render-thread consumption of cmdPost opcodes 0x1C/0x1D/0x1E/0x1F/0x21/0x22/0x1A to prove per-table drains; (4) re-read A6c sort key bit layout details from `Frame::sort`/`Encoder::submit` docs and A7c constant-stream opcode set.
- Commands/anchors: `tools\rdis\target\release\rdis.exe "C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe" -c "sum <rva>; dis <rva>"`; key RVAs 0xbc63690,0xbc66de0,0xbc65800,0xbc63150,0xbc65720,0xbc660a0,0xbc65180,0xbc6f2a0,0xbc6f800,0xbc771f0,0xbc76e80,0xbc60740,0xbc61e20; globals ctx [base+0x12AE1748], renderer [base+0x12BB4910]; Frame pair ctx+0x1CFD0C0/0x1CFD0C8.
- Half-done: none (this pass closed small-function dossiers and documented verified mechanics; remaining items are OPEN as listed below).

## Progress log
- Read `docs/AGENT_BRIEF.md`, `tools/README.md`, `docs/RENDER_CHECKLIST.md` (A4-A8/N3b/N3c context), `docs/BGFX_MAP.md` and `docs/FRAME_CALLGRAPH.md` excerpts, existing dossiers `docs/functions/bc63690.md`, `bc66de0.md`, `bc65800.md`, `bc63150.md`, `bc65720.md`, `0xbc660a0.md`, and bgfx headers `src/sdk/mc/deps/bgfx/{Frame.h,Encoder.h,Handles.h,BgfxContext.h,d3d12/D3D12Context.h}` and `docs/data/layout_asserts.json`. [V]
- `graphify query "bgfx core context handle management encoder pool frame double buffer semaphore 0xE749C0 resource handle lifecycle"` failed: `graphify` command not found in environment. Proceeded with docs/grep/rdis static analysis. [V]
- rdis static analysis (1.26.62.01): `sum/dis 0xbc65180, 0xbc6f2a0, 0xbc6f800, 0xbc771f0, 0xbc76e80, 0xbc5f110` (batch/targeted). [V]
- Created dossiers: `docs/functions/bc65180.md`, `docs/functions/bc6f2a0.md`, `docs/functions/bc6f800.md`, `docs/functions/bc771f0.md`, `docs/functions/bc76e80.md`. [V]

## Item status

### A4b - OPEN (handle allocators A8 pending)
- [V] bgfx Context global `s_ctx` at rva `0x12AE1748`; render thread created as `"bgfx - renderer backend thread"` (proc 0xbc65720) by Context init tail 0xbc63690. (`docs/functions/bc63690.md`, BGFX_MAP 6q/6r)
- [V] View state in Context: 256 views, stride `0x140`, base `ctx+0x1EAB080` initialized by 0xbc63690; frame swap copies view remap `ctx+0x1EAAA60` (0x200), view structs `ctx+0x1EAB080` (0x14000), per-view flags `ctx+0x1EBF080` (0x100) into the submit Frame (0xbc66de0, 6s). Frame-local view structs at `Frame+0x200`, stride 0x140 (`Frame.h`).
- [V] Alternating Frame buffers: `Frame*` pair at `ctx+0x1CFD0C0` and `ctx+0x1CFD0C8`; frame size `0xE749C0` (`Frame.h::kFrameSize`, BGFX_MAP 6e/6r/6s). Handoff/swap logic in 0xbc65800/0xbc66de0 and pacing in 0xbc63150/0xbc65720 (see A10/N3b).
- [V] Semaphores/events: 0xbc63690 calls reset/init helper 0xbc65180 on objects at `ctx+0x1CFD0C0` and `ctx+0x1CFD0C8`; pacing uses `ctx+0x80` (frame-ready wait gate) and `ctx+0x100` (frame-consumed/surface completion gate) in 0xbc65800/0xbc63150/0xbc65720 (BGFX_MAP 6as correction, dossiers). [I exact semaphore object types vs wrappers]
- OPEN: complete per-handle-allocator roles/instances beyond `src/sdk/mc/deps/bgfx/Handles.h` mapping (see A8a) and any additional context-level allocator tables not covered there.

### A6c - OPEN (Sorted item list Frame+0x94700 (6am); sort key bit layout partly)
- [V] Frame layout: sort keys `Frame+0x14700` (`u64[]`), sorted item indices `Frame+0x94700` (`u16[65536]`), draw headers `Frame+0xB4700` stride 0x80, item count `Frame+0xDC57E8`, blit count/keys `Frame+0xDC57EC/0x934778` (`Frame.h`, layout_asserts anchors for Encoder::submit/Frame::sort).
- [V] `SortKey` view/tag helpers and bit fields present in `Encoder.h` (view mask/shift, draw/custom bits, tag/type helpers) — partial decode in headers/docs, not fully restated/verified in this pass. [I completeness]
- OPEN: full, independently re-verified sort key bit layout for all submit variants and any remaining unknown bits/fields (per checklist).

### A7c - OPEN (Per-draw constant stream cursor + 20-byte binding records (type 0-8) — 6an; opcode set pending)
- [V] Existing evidence in repo: `Binding` is 0x14 bytes at `Encoder+0x140` x65 and `BindingType` enum 0-9 defined in `Encoder.h`; per-draw constant/uniform stream and opcode behavior referenced in BGFX_MAP 6an/Encoder docs. [V headers/docs, not re-decoded here]
- OPEN: constant stream cursor mechanics and complete opcode set/semantics (not statically closed in this pass).

### A8a - OPEN (Handle allocators located in Context (offsets) — 6s, 6ai (API fn map; per-allocator roles [I]))
- [V] `src/sdk/mc/deps/bgfx/Handles.h` provides static Context handle allocator offsets/capacities and stats-copy offsets for dynamic index/vertex buffers, framebuffers, index/vertex buffers, occlusion queries, programs, shaders, uniforms, vertex buffers/layouts, shader buffers, acceleration structures, plus texture dynamic allocator and texture-state fields (with static_assert chain checks and live-noted counts in comments). [V header constants/asserts; live counts are header-noted claims not re-polled this pass]
- [V] `0xbc771f0` (`docs/functions/bc771f0.md`): release/refcount helper touching `count @ a+4`, 0x80-entry u16 table at `a+0x208`, per-handle refcount words at `a+0x308 + handle*2`, and dense/sparse bookkeeping — evidence of handle allocator instance internals. [I exact instance mapping]
- [V] `0xbc66de0` drains destroy queues/free-lists and manipulates handle allocator regions across many Context offsets (dossier/BGFX_MAP 6s) as part of frame swap lifecycle. [V]
- OPEN: map each allocator/queue helper to the specific resource table/kind and document allocation/free invariants per allocator (including encoder/other non-listed pools if any).

### A8b - OPEN (Record tables: texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 layouts — 6au; 0x78/0x80/0x130/0x68 field layouts pending)
- [V] D3D12-side record tables/bases/strides and many layouts are already typed in `src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h` (textures 0xB8 @+0xBDE178, shaders 0xB8 @+0xAAA178, programs 0xF8 @+0xB62178, index/vertex/shader buffers, framebuffers, vertex layouts, etc.). [V header; not re-derived in this pass]
- [V] Context-side destroy/enqueue primitives: `0xbc6f2a0` emits post-cmd 0x1C and pushes handle to Frame list at `+0xE45828/+0xE47828`; `0xbc6f800` emits 0x1D to `+0xE478AC/+0xE498AC` (`docs/functions/bc6f2a0.md`, `bc6f800.md`). 0xbc660a0 also emits 0x1E/0x1F/0x1A and calls 0xbc732e0/0xbc79ed0 for specific handles. [V]
- OPEN: complete Context/renderer record-table field layouts for every pending table listed in checklist and bind each destroy opcode/queue to the correct table/handle class (render-thread consumer path not traced here).

### A10 - OPEN (render thread proc, semaphores ctx+0x80/+0x100, surface array stride 0x700 — 6as; 0xbc63150 internals pending)
- [V] `0xbc65720` (`docs/functions/bc65720.md`): render thread proc loops `renderFrame(ctx, 5000)` until Exiting (return 3), waits on `ctx+0x80`, records wait duration into Frame stats `Frame+0xE746C8` (current/previous frame copies), posts `ctx+0x100` when not shutting down. [V]
- [V] `0xbc63150` (`docs/functions/bc63150.md`, 6as correction): `renderFrame(int32_t msecs)` clears reset bit 0x40000 in `[ctx+0x1CFD0C0]+0xDC5810`, handles renderer notifications (vtbl slots 6/9/53) based on `ctx+0x1EBF2EC..2EE`, waits on `ctx+0x80` with timeout and returns RenderFrame enum; performs frame execution via helpers (0xbc68e40 x2, 0xbc68840) [I helper roles].
- [V] `0xbc65800` (`docs/functions/bc65800.md`): multi-surface handoff over per-surface array `ctx+0x13D18` stride `0x700`, uses per-surface slot/timing fields `+0x6AC/+0x6F0/+0x6F8` and Frame tail `+0xDC57E0`, takes `ctx+0x1C0` lock, calls `0xbc66de0`, waits on `ctx+0x100` N-1 times, publishes per-surface timing, and signals `ctx+0x80`. [V mechanical]
- [V] `0xbc65180` (`docs/functions/bc65180.md`) initializes/resets Frame-side tables/counters and per-view tail allocations at `Frame+0xDC57E0`, RenderDraw storage at `Frame+0x8B4700` (0x10000 * 0x540), and emits initial cmd bytes 0x19 to pre/post command buffers.
- OPEN: full internal decode of `0xbc63150` execution path (how it drives renderer submit/command consumption) and any remaining semaphore/object ownership details; encoder pool facts (task focus) not located.

### N3b - PARTIAL evidence relevant (not a checklist section edit)
- [V] Frame double buffer `0xE749C0` apart and alternating Frame pointers at `ctx+0x1CFD0C0/0x1CFD0C8` confirmed by headers/dossiers. [V]
- [V] `ctx+0x80` and `ctx+0x100` are the frame-ready and frame-consumed pacing semaphores used in handoff/render-thread paths. [V]
- OPEN: explicit "signaled in backend order" proof across all present/submit paths requires render-thread submit/command-consumer tracing beyond this pass.

### N3c - OPEN
- [?] Custom items invoked on render thread in view order not analyzed in this pass.

## High-value concrete facts (static, verified this pass or directly from verified repo headers/dossiers)

1. **Frame double buffer & core pointers [V]:** `FrameOffsets::kFrameSize == 0xE749C0`; alternating Frame buffers referenced via `ctx+0x1CFD0C0` / `ctx+0x1CFD0C8`; frame counter at `Frame+0xE746D8`. (`src/sdk/mc/deps/bgfx/Frame.h`, `docs/functions/bc66de0.md`, `bc65180.md`)
2. **Semaphore/pacing mechanics [V]:** render thread `0xbc65720` waits on semaphore `ctx+0x80` after `renderFrame(5000)` loop progress and records wait delta to `Frame+0xE746C8`; handoff `0xbc65800` waits `ctx+0x100` (N-1 times for other surfaces), publishes per-surface timing table `ctx+0x13D08`, signals `ctx+0x80`; `renderFrame` `0xbc63150` waits on `ctx+0x80` with timeout and returns `RenderFrame::{NoContext,Render,Timeout,Exiting}` per 6as correction. (`docs/functions/bc65720.md`, `bc65800.md`, `bc63150.md`, BGFX_MAP 6as)
3. **Per-surface handoff objects [V]:** `ctx+0x13D18` points to array stride `0x700`; active surface id list/count at `ctx+0x13D20`; per-object fields used: `+0x6AC` slot/index, `+0x6F0/+0x6F8` timing, tail table at `(*obj)+0xDC57E0`. (`docs/functions/bc65800.md`)
4. **Frame command buffers & destroy enqueue [V]:** pre/post command buffers at `Frame+0xDC5818/20` and `Frame+0xE05820/28`; `0xbc65180` emits cmd byte `0x19` to both during frame init/reset; `0xbc6f2a0` enqueues opcode `0x1C` + u16 handle and pushes to list `E45828/E47828`; `0xbc6f800` enqueues opcode `0x1D` + u16 handle to list `E478AC/E498AC`; shutdown `0xbc660a0` also emits `0x01,0x1E,0x1F,0x1A` and calls destroy helpers `0xbc732e0/0xbc79ed0`. (`docs/functions/bc65180.md`, `bc6f2a0.md`, `bc6f800.md`, `0xbc660a0.md`)
5. **Frame storage initialization [V]:** `0xbc65180` allocates/initializes per-view tail blocks via `Frame+0xDC57E0` using count `data_12AE0DAC` (per-entry `0x100008` bytes, header words observed), and RenderDraw storage at `Frame+0x8B4700` for `0x10000 * 0x540` bytes; resets item/blit/matrix counters and many per-frame handle-list counters in `0xE47828..0xE60DDE`. (`docs/functions/bc65180.md`)
6. **Handle allocator / lifecycle evidence [V/I]:** static Context allocator offsets/capacities and dynamic texture allocator state are documented in `src/sdk/mc/deps/bgfx/Handles.h`; `0xbc771f0` shows refcount-decrement + release bookkeeping on an allocator-like structure (`+4` count, `+0x208` sparse/index table region, `+0x308+handle*2` refcounts). `0xbc76e80` drains a queued destroy structure and notifies via `data_12adf800` slot 1. Per-resource kind mapping remains OPEN. (`Handles.h`, `docs/functions/bc771f0.md`, `bc76e80.md`)
7. **Encoder pool [OPEN/?]:** no direct static evidence of a distinct "encoder pool" object/allocator was identified in this pass; encoder API/submit/reset functions and inlined encoder storage are known (`Encoder.h`, BGFX_MAP 6cq/6cr) but pooling/lifecycle not proven.

## Additive SDK/header/layout changes
- Created dossiers only: `docs/functions/bc65180.md`, `docs/functions/bc6f2a0.md`, `docs/functions/bc6f800.md`, `docs/functions/bc771f0.md`, `docs/functions/bc76e80.md`.
- No edits to `docs/BGFX_MAP.md`, `docs/RENDER_CHECKLIST.md`, `src/sdk/...` headers, or `docs/data/layout_asserts.json` in this pass. `src/sdk/mc/deps/bgfx/Handles.h` already contains relevant verified allocator constants/asserts; I did not add duplicates. [V]

## Blockers / missing for closure
- **Encoder pool:** exact object, allocator, count/stride, and acquire/release/reset lifecycle not located (needs targeted search around encoder creation in bgfx API/context, thread-local encoder paths, or frame/submit callsites).
- **A8a/A8b mapping:** need to attribute `0xbc771f0`, `0xbc76e80`, and cmd opcodes 0x1C/0x1D/0x1E/0x1F/0x21/0x22 to specific handle/resource classes and backing tables (Context allocators vs D3D12 tables) by tracing callers and render-thread command consumers.
- **A7c/A6c residuals:** opcode set for constant stream and full sort-key bit semantics require dedicated decode passes (existing partial docs/headers not fully re-proven here).
- **A10 internals:** helper roles inside `0xbc63150` (`0xbc68e40`, `0xbc68840`) and end-to-end backend signaling order in all surface/reset paths not fully decoded.

## Final report (short)
- **DONE (analysis artifacts, A4-A8-focused):** documented frame double-buffer (`0xE749C0`, ctx+0x1CFD0C0/0x1CFD0C8), semaphore/pacing roles (`ctx+0x80`, `ctx+0x100`), per-surface handoff (`ctx+0x13D18` stride 0x700), Frame cmd buffer/init and destroy enqueue opcodes (`0x19,0x1C,0x1D` producers; shutdown emits `0x01,0x1A,0x1E,0x1F`), and handle-allocator/lifecycle helper evidence; wrote dossiers for 0xbc65180, 0xbc6f2a0, 0xbc6f800, 0xbc771f0, 0xbc76e80.
- **OPEN:** A4b (allocator roles incomplete), A6c (sort key bits partly), A7c (constant stream/opcode set), A8a (per-allocator/resource mapping), A8b (pending table field layouts/lifecycle binding), A10 (0xbc63150 internals + full backend signaling proof), and "encoder pool" facts (not found).
- **Files created/edited:** created `docs/progress/re_a4a8.md`, `docs/functions/bc65180.md`, `docs/functions/bc6f2a0.md`, `docs/functions/bc6f800.md`, `docs/functions/bc771f0.md`, `docs/functions/bc76e80.md`. No edits to BGFX_MAP/RENDER_CHECKLIST/src headers/layout_asserts.

## FULL PROPOSED BGFX_MAP ENTRY TEXT (entry IDs TBD; do not edit BGFX_MAP.md)

### A4-A8 — bgfx core context/handle management (static pass, 1.26.62.01)

**A4b Context global + view state + semaphores (partial):**
- [V] `bgfx::s_ctx` global at rva `0x12AE1748`. Context init tail `0xbc63690` (0x4e7) resets flags/timestamp, calls `0xbc65180` on `ctx+0x1CFD0C0` and `ctx+0x1CFD0C8`, creates render thread `"bgfx - renderer backend thread"` (proc `0xbc65720`, 0xdb) unless single-threaded, writes TLS magic `0x78666762`, initializes 256 views at `ctx+0x1EAB080` (stride 0x140) and handle/sort tables (`ctx+0x1EA69E0` cleared 0x80, `ctx+0x1EA6A60/+0x1EA8A60` filled 0xFF 0x2000). (`docs/functions/bc63690.md`)
- [V] Alternating Frame pair: `ctx+0x1CFD0C0` / `ctx+0x1CFD0C8`; frame size `0xE749C0` (`Frame.h::kFrameSize`). `0xbc66de0` (frame/swap) copies view remap `ctx+0x1EAAA60` (0x200), view structs `ctx+0x1EAB080` (0x14000), per-view flags `ctx+0x1EBF080` (0x100) into submit Frame, drains destroy queues/allocators, advances frame number. (`docs/functions/bc66de0.md`, `Frame.h`)
- [V] Semaphores/pacing objects: `ctx+0x80` = frame-ready wait gate; `ctx+0x100` = frame-consumed/surface completion gate. `0xbc65800` (handoff) takes `ctx+0x1C0`, calls `0xbc66de0`, waits `ctx+0x100` (N-1), publishes per-surface timing to `ctx+0x13D08`, signals `ctx+0x80`. `0xbc63150` (`renderFrame(msecs)`) waits on `ctx+0x80` with timeout and returns `RenderFrame::{NoContext=0,Render=1,Timeout=2,Exiting=3}`; also handles renderer notifications via `ctx+0x1EBF2D0` vtbl slots 6/9/53. `0xbc65720` loops `renderFrame(5000)` until Exiting and records wait stats in Frame `+0xE746C8`. (`docs/functions/bc65800.md`, `bc63150.md`, `bc65720.md`)
- [I/?] Exact semaphore primitive types/ownership beyond observed wait/post callsites remain to be fully typed; per-handle allocator role mapping incomplete (see A8a).

**A6c Sorted item list / sort key bits (partial):**
- [V] Frame arrays: sort keys `Frame+0x14700` (u64), sorted indices `Frame+0x94700` (u16[65536]), draw headers `Frame+0xB4700` (stride 0x80), item count `Frame+0xDC57E8`, blit keys/count `Frame+0x934778/+0xDC57EC`. `Encoder.h` defines `SortKey` view mask/shift, draw/custom bits, tag/type helpers. (`Frame.h`, `Encoder.h`)
- [OPEN] Full independently verified bit layout across all key forms/submit variants and any residual unknown bits.

**A7c Per-draw constant stream cursor + binding records (partial):**
- [V] Encoder/Frame binding model in headers: 65 bindings x 0x14 at `Encoder+0x140` (`Binding` struct, `BindingType` 0-9 in `Encoder.h`), side table pointer `Encoder+0x680` (`FrameOffsets::kSideTables` linkage in executor/docs). (`Encoder.h`, `Frame.h`)
- [OPEN] Constant stream cursor and complete opcode set/semantics not decoded in this pass.

**A8a Handle allocators in Context (partial):**
- [V] Context static allocator map (offset, capacity, stats-copy offset) and dynamic texture allocator/texture-state fields are defined with static asserts in `src/sdk/mc/deps/bgfx/Handles.h` (dynamic index/vertex buffers, framebuffers, index/vertex buffers, occlusion queries, programs, shaders, uniforms, vertex buffers/layouts, shader buffers, acceleration structures; dynamic handle alloc at `ctx+0x1DF3460`; texture records/flags/reset bits). (`Handles.h`)
- [V] Release helper `0xbc771f0` (0x157): on refcount reaching zero (`a + handle*2 + 0x308`), clears slot in 0x80-entry u16 table at `a+0x208`, decrements count `a+4`, and performs dense/sparse bookkeeping over `a+0/a+8/a+0x208`-region. (`docs/functions/bc771f0.md`)
- [V] Destroy queue drain helper `0xbc76e80`: iterates queued entries (`a0+0x20/+0x28`), hashes/matches entries, notifies via `data_12adf800` vtbl slot 1, compacts/moves records and decrements `a0+0x18`. (`docs/functions/bc76e80.md`)
- [OPEN] Exact mapping of each helper/queue to specific allocator/resource kinds and full lifecycle invariants.

**A8b Resource handle lifecycle / record tables (partial):**
- [V] Frame command buffers: pre `Frame+0xDC5818/+0xDC5820`, post `Frame+0xE05820/+0xE05828`. `0xbc65180` initializes/reset frame state (per-view tail table `Frame+0xDC57E0`, RenderDraw array `Frame+0x8B4700` = 0x10000 * 0x540, counters/cmd cursors/handle-list counters) and emits cmd byte `0x19` to pre and post buffers. (`docs/functions/bc65180.md`, `Frame.h`)
- [V] API-thread destroy enqueue primitives (lock `ctx+0x1C0`, operate on fill frame `ctx+0x1CFD0C8`): `0xbc6f2a0` pushes u16 handle to `Frame+E45828` with count `E47828` and emits post-cmd opcode `0x1C` + u16 handle; `0xbc6f800` pushes to `Frame+E478AC` / count `E498AC` and emits opcode `0x1D` + u16 handle. (`docs/functions/bc6f2a0.md`, `bc6f800.md`)
- [V] Shutdown `0xbc660a0` emits pre-cmd `0x01`, post-cmd `0x1E/0x1F/0x1A`, flushes via `0xbc65800`, notifies via `data_12ADF800` slot 1, and calls destroy helpers `0xbc732e0/0xbc79ed0`; it does not directly reference renderer resource-table bases/strides (table drains likely indirect/render-thread-side). (`docs/functions/0xbc660a0.md`)
- [V] D3D12 renderer table bases/strides/layouts for textures/shaders/programs/buffers/framebuffers/vertex layouts are substantially typed in `src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h` (existing repo state; not modified this pass).
- [OPEN] Bind opcodes/queues/helpers to specific resource kinds/tables; finish pending record field layouts listed by checklist; no proven "encoder pool" allocator found.

**A10 Render thread proc / multi-surface handoff (partial):**
- [V] Per-surface array `ctx+0x13D18` stride `0x700`, active id list/count `ctx+0x13D20`; `0xbc65800` writes present record into surface Frame tail (`+0xDC57E0[slot]`), stamps `obj+0x6F8`, waits `ctx+0x100` N-1, copies `{+0x6F0,+0x6F8}` per surface to `ctx+0x13D08`, resets list/bitmap, and signals `ctx+0x80`. (`docs/functions/bc65800.md`)
- [V] `0xbc63150` and `0xbc65720` implement render-thread pacing/reset-notification path around `ctx+0x80/0x100`, `ctx+0x1CFD0C0/0x1CFD0C8`, and renderer `ctx+0x1EBF2D0`. (`docs/functions/bc63150.md`, `bc65720.md`)
- [OPEN] Internal execution stages of `0xbc63150` (`0xbc68e40`, `0xbc68840`) and complete backend signaling order.

**Audit notes:**
- [V] `docs/functions/bc65800.md` and rdis callees show `0xbc65800` calls `0xbc66de0` and is called by `0xbc660a0`/GraphicsTasks Execute; this supersedes older prose implying the opposite direction (trust mechanical call lists).
- [V] Task request to identify "6 drain blocks of shutdown 0xbc660a0" for specific renderer resource tables: not directly observable in `0xbc660a0` disassembly; likely indirect via commands/callees/render-thread processing (see `docs/functions/0xbc660a0.md`).
- [OPEN/?] "Encoder pool" not located statically in this pass. No runtime polling performed (constraints respected).
