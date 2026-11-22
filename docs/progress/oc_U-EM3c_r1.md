## NEXT
DONE

UNIT U-EM3c — M3c Frame graph: add/remove/reorder a pass safely (recipe 6dg/6dy)
GOAL (handoff 2026-11-22): close checklist item M3c (RENDER_CHECKLIST.md line 455) — "Frame graph: add/remove/reorder a pass safely (recipe 6dg/6dy, TaskDispatchHook + dragon/Tasks.h written but never built or run; needs the build + in-game test)". This unit does everything that can be done without building or running the game: static analysis of TaskDispatchHook + dragon/Tasks.h against Minecraft.Windows.exe 1.26.62.01, verbatim proof rows, live corroboration from existing capture data, and the exact in-game test plan under TOOL REQUESTS. CLOSES? = NO (section 7): the build + in-game test remains.

CONSTRAINTS OBSERVED: no build (no cmake/ninja), no game launch or attach, no HookManager.cpp or hook-registration edits, no CMake, no existing Sigs.json edits. rdis is used only with the exe as an argument (rule 6). Existing live data in docs/data/live/ is used before any new capture request.

## 1) What changed (paths)

| Path | Action | Why |
|---|---|---|
| docs/progress/oc_U-EM3c.md | created | Unit record: static verification of the M3c code that exists on disk, verbatim proof table, live corroboration, in-game test plan, CLOSES? |

No src file was created or edited. TaskDispatchHook.h/cpp, dragon/Tasks.h, PassNames.h and the Sigs.json taskDispatch signature already exist on disk (written earlier, never built or run), so there is no code change pending from this unit except the build + in-game test it cannot perform. The file is the only deliverable of this unit.

## 2) Code on disk inventory (verified statically against the exe; not built)

| File | Provides | Status | Exe check |
|---|---|---|---|
| src/client/features/hooks/hooks/render/TaskDispatchHook.h | addListener, nameOf, drop, swap, frameCount, imageBase | written [I] | addListener has no caller in src; the hook is never installed by HookManager.cpp |
| src/client/features/hooks/hooks/render/TaskDispatchHook.cpp | HOOK(FrameGraph, taskDispatch): run listeners, sFrames counter, forward to ORIG with the list untouched unless a listener mutated it | written [I] | drop/swap move raw 0x80-byte entries; no index bounds check (fail-fast gap, section 5) |
| src/sdk/mc/deps/minecraft_renderer/dragon/Tasks.h | TaskRvas (kDispatch 0xE9002E0), TaskListEntry (0x80, static_assert sizeof==0x80), TaskList {begin+0x00, end+0x08, cap+0x10, extra+0x18}, TaskOffsets (functor +0x70, args +0x78 [I]), ViewRefOffsets, TaskTail, taskName, TaskBodyRvas | written | static_assert sizeof(TaskListEntry)==0x80 matches the observed 0x80 walk stride (row 0xE900373) [V] |
| src/sdk/mc/deps/minecraft_renderer/dragon/PassNames.h | FNV-1 64 pass-name hashes; static_assert fnv1("GeometryPrepass") == 0x680e1340911894f3 | written | the asserted hash equals the immediate embedded at 0x55ff9a9 in the VV pass declaration [V] |
| src/sdk/Sigs.json | taskDispatch signature (priority high): ... 0F B6 41 18 | existing | sig tail = `movzx eax,byte ptr [rcx+0x18]` at 0xE900314 (row below) [V] |
| src/sdk/mc/deps/minecraft_renderer/dragon/FrameGraph.h | Generator layout: declared entries 0x10 {key, PassDesc*}, generated entry stride 0x80, DragonFrameResources tasks vector first+0x290 / last+0x298 / end+0x2A0, element 0x10 | written | context for "add": new tasks must be declared in generate 0xc273420; the hook cannot insert passes [V static] |

## 3) Proof table: task-dispatch mechanics (verbatim `0xRVA  instr` lines from rdis, exe 1.26.62.01)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xE9002E0 | 1 | - | `0xE9002E0  push rbp` | FrameGraph::taskDispatch entry; rcx = TaskList* (the list argument) | [V] |
| 0xE900314 | 1 | TaskList+0x18 `extra` (mode byte) | `0xE900314  movzx eax,byte ptr [rcx+0x18]` | dispatch reads TaskList.extra; 0 takes the normal walk path | [V] |
| 0xE900318 | 4 | - | `0xE900318  test eax,eax` | extra == 0 test; je to the list walk at 0xE90032A | [V] |
| 0xE900366 | 8 | TaskList+0x00 `begin` | `0xE900366  mov r12,[rcx]` | list.begin loaded as the walk cursor | [V] |
| 0xE900369 | 8 | TaskList+0x08 `end` | `0xE900369  mov rdx,[rcx+8]` | list.end = walk bound | [V] |
| 0xE900370 | 8 | - | `0xE900370  sub rax,r12` | end - begin (byte span of the list) | [V] |
| 0xE900373 | 8 | - | `0xE900373  sar rax,7` | count = (end - begin) >> 7, i.e. entries of 0x80 bytes (matches static_assert sizeof(TaskListEntry) == 0x80) | [V] |
| 0xE900412 | 8 | - | `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` | walk step += 0x80 per entry | [V] |
| 0xE90041A | 8 | - | `0xE90041A  cmp r12,rdx` | loop exits when the walk cursor reaches end | [V] |
| 0xE900464 | 8 | entry+0x00 `task` | `0xE900464  mov rcx,[r12]` | entry.task = the task object pointer | [V] |
| 0xE900468 | 8 | task vtable | `0xE900468  mov rax,[rcx]` | task object vtable pointer | [V] |
| 0xE90046B | 8 | task vtable+0x18 (slot 3) | `0xE90046B  mov rax,[rax+0x18]` | vtbl[3] — the per-task enable check invoked next | [V] |
| 0xE90046F | 8 | [0xF99FFA0] CFG guard thunk | `0xE90046F  call qword ptr [0xF99FFA0]` | indirect call of vtbl[3](task) through the CFG dispatch thunk | [V] |
| 0xE90047A | 4 | - | `0xE90047A  cmp eax,1` | enable result == 1 means the task runs this frame | [V] |
| 0xE90048B | 8 | entry+0x08 `controlBlock` | `0xE90048B  mov rax,[r12+8]` | entry.controlBlock = shared_ptr control block | [V] |
| 0xE900495 | 4 | controlBlock+0x08 refcount | `0xE900495  lock inc dword ptr [rax+8]` | strong refcount inc for a task that runs this frame | [V] |
| 0xE9004EC | 16 | entry+0x00 (store) | `0xE9004EC  movups [r12],xmm7` | removal path zeroes the entry in place (movups = 16 bytes) | [V] |
| 0xE90052C | 8 | entry+0x70 | `0xE90052C  mov rax,[r12+0x70]` | entry+0x70 saved and cleared on the entry-removal path (field not decoded; Tasks.h rest[0x30..0x7F]) | [I] |
| 0xC270554 | 5 | imm 0xE9002E0 | `0xC270554  call 0xE9002E0` | BgfxContext::endFrame calls the dispatch once per frame; return address 0xC270559 | [V] |

Row count: 19 data rows. No duplicate offsets. movups row size 16 matches the instruction. No raw instruction dump pasted; no catch-all summary; no skipped offset.

## 4) Live corroboration (existing data — no new capture needed)

docs/data/live/u_em1f_dispatch.txt (regs capture at rva 0xE9002E0, 10 samples, every hit; header line 2 documents the format):
- line 3: `CALLER ret=0xC270559 first_hit=1` — the caller's return address is 0xC270559, exactly the instruction after `0xC270554  call 0xE9002E0`, and it fires once per endFrame [V live]. Confirms static row 0xC270554 live.
- RCX holds the TaskList*: [rcx] = begin, [rcx+8] = end, and end - begin = 0x900 in every sample → 18 entries per frame = (end - begin) >> 7 (static rows 0xE900366/0xE900369/0xE900373) [V live]. Matches the statically sampled 18-task frame order in docs/BGFX_MAP.md section 6cx `[ClearColorDepth][Scene], Scene x12, [ClearDepth][HUD], HUD, Pass, TerrainAtlasBlit, SceneWaitOnChunk` [V].
- [rcx+0x18] = extra = 0 in every sample → the dispatch takes the normal walk path (`movzx eax,[rcx+0x18]; test eax,eax; je 0xE90032A`) — static row 0xE900314 confirmed live [V live].
- RDX dumps contain the declared pass names ([ClearColorDepth][Scene], TerrainAtlasBlit, SceneWaitOnChunk, Scene, HUD, Pass, ...) [V live] — the pass set the hook can enable, disable and reorder.

No new capture was queued: docs/data/live/u_em1f_dispatch.txt already covers the hook site with 10 samples and caller ret=0xC270559.

## 5) Safety contract for "add/remove/reorder a pass safely" (on disk) and remaining gaps

Remove — TaskDispatchHook::drop: memmoves entries down from i, parks the removed entry at begin[n-1] behind the new end, end -= 0x80. The game itself also neutralizes non-running tasks: task->vtbl[3](task) != 1 entries are zeroed in place (`0xE9004EC  movups [r12],xmm7`) and never pushed into the frame's task vector (DragonFrameResources +0x298, the 0x10-stride {task, control} push cursor, is advanced only on the eax==1 path). The shared_ptr control block is never released by drop (documented leak: one ref per removed task per frame, accepted until game tests show the list is safe to shorten).

Reorder — TaskDispatchHook::swap: std::swap of two raw 0x80 entries; {obj, ctrl} is a plain memcpy so refcounts stay consistent.

Per-task enable already exists in the game: vtbl[3](task) via the CFG thunk [0xF99FFA0]; only eax == 1 tasks run (rows 0xE90046B/0xE90046F/0xE90047A).

Rules from recipe 6dg that listeners must obey: (1) never disable the Scene/HUD per-view setup body (0x568CD90) unless the whole view is dropped — it writes the per-view rect, matrices and sort mode that Encoder::submit reads (BGFX_MAP 6dd); (2) reorder only dependency-free tasks — dependency vectors are built by the generator 0xc273420 from declaration order (the dispatcher builds its run-order at rbp+0x110 per 6dg); (3) insert is unsupported by the hook — new tasks must be declared in 0xc273420 (FrameGraph.h generated-entry stride 0x80); use Encoder::submit for extra draws.

Gaps (not code yet; cannot be built or tested by this unit):
- drop()/swap() have NO index bounds check: i >= n or n == 0 is out-of-bounds UB. A fail-fast guard (terminate loud, CLAUDE.md style: no null guards, no SEH) is required before the hook is enabled in game.
- No "disable via no-op std::function stub at task+0x70" helper (6dg point 2) exists — only physical remove.
- addListener has no caller anywhere in src and HookManager.cpp never installs the hook; wiring registration is out of scope for this unit (editing HookManager.cpp is forbidden).

## 6) TOOL REQUESTS

In-game test plan (M3c / P1b / P2c / P3d / Q5b; to be run after the orchestrator's build, with a listener registered through TaskDispatchHook::addListener):
1. Baseline — regs capture at 0xE9002E0 (rcx = TaskList*): expect begin/end with end - begin = 0x900 → 18 entries, extra = 0, caller ret = 0xC270559 once per frame (already shown by docs/data/live/u_em1f_dispatch.txt).
2. Disable a pass — listener scans nameOf for e.g. "TerrainAtlasBlit" and drops that index. Read back: next capture shows 17 entries (end - begin = 0x880) and nameOf never returns "TerrainAtlasBlit"; the frame still completes (frame counter advances, no crash).
3. Reorder — listener swaps two adjacent entries (e.g. "HUD" and "Pass"). Read back: capture shows the same 18 entries with the two names exchanged at their indices; frame completes.
4. Insert — expected negative result: the hook has no insert path; a new pass requires a declaration in generate 0xc273420 (FrameGraph.h, generated entry stride 0x80). Document as not supported; do not attempt.
What to read back: regs capture at 0xE9002E0 — RCX = TaskList*, qword 0 = begin, qword 8 = end, count = (end - begin) >> 7, entry order/names via the listener log. Expected values: baseline 18; after disable 17 with the named entry absent; after reorder 18 with swapped order.
Capture queue: none — docs/data/live/u_em1f_dispatch.txt already covers the site (10 samples, ret=0xC270559).

## 7) CLOSES?

CLOSES? NO — M3c as worded needs "the build + in-game test" (disable, reorder, insert a pass; P1b/P2c/P3d/Q5b all "written, never built or run"). Everything that can exist on disk without a build is done: the hook and Tasks.h are written, the layout is verified against the exe (proof rows above, all [V] except the one [I] field-meaning note), and the in-game test plan is written. Single blocking fact: the build and the in-game run have not been performed (units may not build or launch the game), and the hook is not yet wired/enabled in HookManager.cpp (editing it is out of scope). Re-open this unit after the orchestrator's build + in-game test to set CLOSES? YES.

## NEXT
step 2
