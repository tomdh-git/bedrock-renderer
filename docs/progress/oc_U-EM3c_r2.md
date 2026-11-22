## NEXT
DONE

UNIT U-EM3c — M3c Frame graph: add/remove/reorder a pass safely (recipe 6dg/6dy)
GOAL (orchestrator handoff 2026-11-22): close checklist item M3c — "Frame graph: add/remove/reorder a pass safely (recipe 6dg/6dy, TaskDispatchHook + dragon/Tasks.h written but never built or run; needs the build + in-game test)". This unit does everything that can be done WITHOUT building or running the game: static analysis of TaskDispatchHook + dragon/Tasks.h (+ new fail-fast edit header) against Minecraft.Windows.exe 1.26.62.01, verbatim proof rows, live corroboration from existing capture data, and the exact in-game test plan under TOOL REQUESTS. CLOSES? = NO (section 8): the build + in-game test remains.

CONSTRAINTS OBSERVED: no build (no cmake/ninja), no game launch or attach, no HookManager.cpp or hook-registration edit, no CMake, no existing Sigs.json edits, no tools.rtools.*. rdis is used only with the exe as an argument (exe presence checked with `test -f`, passed only as rdis argument). Existing live data in docs/data/live/ is used before any capture request. [V] = seen in disassembly/live data; [I] = inferred; [?] = unknown. No guesses written as fact.

Size convention for the proof table: size = memory-operand size (movups 16, qword 8, dword 4, word 2, byte 1); register-only instructions take the principal register size (xmm 16, gpr64 8, gpr32 4); control flow takes instruction length (je short 2, call rel32 5).

## 1) What changed (paths)

| Path | Action | Why |
|---|---|---|
| docs/progress/oc_U-EM3c.md | created | Unit record: static verification of the M3c code on disk, verbatim proof table, live corroboration, in-game test plan, CLOSES? |
| src/client/features/render/TaskDispatchEdit.h | created | New header: fail-fast, bounds-checked pass drop/swap/drop-by-name built on TaskDispatchHook; static_asserts on the 0x80-byte entry layout (TaskListEntry == 0x80, TaskList offsets, dispatch RVA anchor) |

No src file other than the new header was created or edited. TaskDispatchHook.h/cpp, dragon/Tasks.h, PassNames.h, FrameGraph.h and the Sigs.json taskDispatch signature already exist on disk (written earlier, never built or run) and are left untouched: HookManager.cpp and hook registration are off-limits, CMake untouched, existing Sigs.json entries untouched (the taskDispatch signature is proven below, so no new signature is needed).

## 2) Code on disk inventory (verified statically against the exe; nothing built or run)

| File | Provides | Status | Exe check |
|---|---|---|---|
| src/client/features/hooks/hooks/render/TaskDispatchHook.h | addListener, nameOf, drop, swap, frameCount, imageBase | written earlier | addListener has no caller in src; HookManager.cpp never installs the hook (off-limits to this unit) |
| src/client/features/hooks/hooks/render/TaskDispatchHook.cpp | HOOK(FrameGraph, taskDispatch): run listeners, sFrames counter, forward to ORIG with the list untouched unless a listener mutated it | written earlier | sig tail `0F B6 41 18` = `movzx eax,byte ptr [rcx+0x18]` at 0xE900314 [V]; drop/swap move raw 0x80-byte entries with no index bounds check (gap, closed by the new header) |
| src/client/features/render/TaskDispatchEdit.h | NEW: bounds-checked dropTask/dropTaskByName/swapTasks + taskName; fail-fast terminate on i >= n; static_asserts on TaskListEntry/TaskList layout and kDispatch == 0xE9002E0 | created this unit | every asserted offset matches a verified instruction row in section 3 [V] |
| src/sdk/mc/deps/minecraft_renderer/dragon/Tasks.h | TaskRvas (kDispatch 0xE9002E0, kFrameGraphGenerate 0xC273420, kBgfxContextEndFrame 0xC270460, kFrameRenderer 0x67C9C20, kSceneHudViewSetup 0x568CD90, class vtables), TaskListEntry (0x80, static_assert sizeof==0x80), TaskList {begin+0x00, end+0x08, cap+0x10, extra+0x18}, TaskOffsets, ViewRefOffsets, TaskTail, taskName | written earlier | sizeof(TaskListEntry)==0x80 matches the observed walk stride `sar rax,7` at 0xE900373 [V]; vtable RVAs/name offsets are layout notes, [I] (0xF25C7B0 probed as a real vtable with slot +0x18 = sub_76920, [V raw]) |
| src/sdk/mc/deps/minecraft_renderer/dragon/PassNames.h | FNV-1 64 pass-name hashes; static_assert fnv1("GeometryPrepass") == 0x680e1340911894f3 | written earlier | asserted hash equals the immediate embedded in the VV pass declaration [V] (BGFX_MAP; not re-probed this unit) |
| src/sdk/mc/deps/minecraft_renderer/dragon/FrameGraph.h | Generator layout: declared entries 0x10 {key, PassDesc*}, generated entry stride 0x80, DragonFrameResources tasks first+0x290 / last+0x298 / end+0x2A0, element 0x10 | written earlier | +0x298 push cursor and +0x2A0 end and 0x10 element advance seen in the dispatch listing (rows 0xE9004AA/0xE9004B1/0xE9004C5) [V]; +0x290 cited elsewhere in the listing [I] |

## 3) Proof table: task-dispatch mechanics (verbatim `0xRVA  instr` lines from rdis, exe 1.26.62.01)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xE9002E0 | 1 | - | `0xE9002E0  push rbp` | FrameGraph::taskDispatch entry (prologue); rcx = TaskList*, the frame's task list argument | [V] |
| 0xE900314 | 1 | TaskList+0x18 `extra` (mode byte) | `0xE900314  movzx eax,byte ptr [rcx+0x18]` | dispatch reads TaskList.extra; 0 takes the normal walk path (also the Sigs.json taskDispatch sig tail) | [V] |
| 0xE900318 | 4 | - | `0xE900318  test eax,eax` | extra == 0 test | [V] |
| 0xE90031A | 2 | - | `0xE90031A  je short 0xE90032A` | extra == 0 branches to the list walk at 0xE90032A | [V] |
| 0xE900366 | 8 | TaskList+0x00 `begin` | `0xE900366  mov r12,[rcx]` | list.begin loaded as the walk cursor | [V] |
| 0xE900369 | 8 | TaskList+0x08 `end` | `0xE900369  mov rdx,[rcx+8]` | list.end = walk bound | [V] |
| 0xE900370 | 8 | - | `0xE900370  sub rax,r12` | end - begin, byte span of the list | [V] |
| 0xE900373 | 8 | - | `0xE900373  sar rax,7` | count = span >> 7, entries of 0x80 bytes (matches static_assert sizeof(TaskListEntry) == 0x80) | [V] |
| 0xE9003ED | 16 | - | `0xE9003ED  xorps xmm7,xmm7` | xmm7 zeroed; the removal path blanks entries with it | [V] |
| 0xE900412 | 8 | - | `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` | walk cursor stepped by 0x80 per entry | [V] |
| 0xE90041A | 8 | - | `0xE90041A  cmp r12,rdx` | loop exits when the walk cursor reaches end | [V] |
| 0xE900464 | 8 | entry+0x00 `task` | `0xE900464  mov rcx,[r12]` | entry.task = the task object pointer | [V] |
| 0xE900468 | 8 | task vtable | `0xE900468  mov rax,[rcx]` | task object vtable pointer | [V] |
| 0xE90046B | 8 | task vtable+0x18 (slot 3) | `0xE90046B  mov rax,[rax+0x18]` | vtbl[3] — the per-task enable check invoked next | [V] |
| 0xE90046F | 8 | [0xF99FFA0] CFG guard thunk | `0xE90046F  call qword ptr [0xF99FFA0]` | indirect call of vtbl[3](task) through the CFG dispatch thunk ([data_f99ffa0] = sub_eea6040) | [V] |
| 0xE90047A | 4 | - | `0xE90047A  cmp eax,1` | enable result == 1 means the task runs this frame | [V] |
| 0xE90048B | 8 | entry+0x08 `controlBlock` | `0xE90048B  mov rax,[r12+8]` | entry.controlBlock = shared_ptr control block | [V] |
| 0xE900495 | 4 | controlBlock+0x08 strong refcount | `0xE900495  lock inc dword ptr [rax+8]` | strong refcount inc for a task that runs this frame | [V] |
| 0xE9004AA | 8 | - | `0xE9004AA  mov r15,[rdi+0x298]` | game loads its frame-task push cursor (DragonFrameResources+0x298, per FrameGraph.h) | [V] |
| 0xE9004B1 | 8 | - | `0xE9004B1  cmp r15,[rdi+0x2A0]` | cursor vs the vector end/capacity (+0x2A0) | [V] |
| 0xE9004BE | 8 | cursor[0] task store | `0xE9004BE  mov [r15],r13` | game pushes entry.task into its frame task vector | [V] |
| 0xE9004C1 | 8 | cursor[8] control store | `0xE9004C1  mov [r15+8],rbx` | game pushes entry.controlBlock into its frame task vector | [V] |
| 0xE9004C5 | 8 | DragonFrameResources+0x298 | `0xE9004C5  add qword ptr [rdi+0x298],0x10` | push cursor advanced by one 0x10-byte {task, control} element | [V] |
| 0xE9004EC | 16 | entry+0x00 (store) | `0xE9004EC  movups [r12],xmm7` | removal path zeroes the entry in place (movups = 16 bytes; xmm7 was zeroed at 0xE9003ED) | [V] |
| 0xE900531 | 8 | entry+0x70 (store) | `0xE900531  mov qword ptr [r12+0x70],0` | entry+0x70 cleared on the removal path; field meaning not decoded by this instruction [I] | [V] |
| 0xC270554 | 5 | imm 0xE9002E0 | `0xC270554  call 0xE9002E0` | BgfxContext::endFrame calls the dispatch once per frame; return address 0xC270559 | [V] |

Row count: 26 data rows. No duplicate offsets. movups row 0xE9004EC size 16 matches the instruction; no other mov-family rows. No raw instruction dump pasted; no catch-all summary; no skipped offsets.

## 4) Layout contract (static_asserts, matched to the disassembly)

| Assert (Tasks.h / TaskDispatchEdit.h) | Disassembly evidence | Tag |
|---|---|---|
| sizeof(dragon::TaskListEntry) == 0x80 | count = (end - begin) >> 7 at 0xE900373; walk step 0x80 at 0xE900412 | [V] |
| TaskList {begin+0x00, end+0x08, cap+0x10, extra+0x18} | begin at 0xE900366, end at 0xE900369, extra read at 0xE900314 (cap+0x10 seen at 0xE900334/0xE900330 as [rdx+0x10]/[rdx+8]) | [V] |
| dragon::TaskRvas::kDispatch == 0xE9002E0 | function entry 0xE9002E0 `push rbp`; called by endFrame at 0xC270554 | [V] |
| Sigs.json taskDispatch signature | sig tail `0F B6 41 18` = `movzx eax,byte ptr [rcx+0x18]` at 0xE900314; full sig bytes match the function prologue 0xE9002E0..0xE900314 | [V] |

TaskDispatchEdit.h repeats these as static_asserts (sizeof TaskListEntry, TaskList offsets begin/end/cap/extra, kDispatch == 0xE9002E0) so the layout is compile-checked whenever the header is included.

## 5) Safety contract for "add/remove/reorder a pass safely" (on disk)

Remove — TaskDispatchHook::drop: memmoves entries down from i, parks the removed entry at begin[n-1] behind the new end, end -= 0x80. The game itself also neutralizes non-running tasks: vtbl[3](task) != 1 entries are zeroed in place (`0xE9004EC  movups [r12],xmm7`, xmm7 zeroed at `0xE9003ED  xorps xmm7,xmm7`) and never pushed into the frame task vector (push at 0xE9004BE/0xE9004C1 happens only on the eax==1 path, `0xE90047A  cmp eax,1` then fall-through). The shared_ptr control block is never released by drop (documented leak: one ref per removed task per frame, accepted until game tests show the list is safe to shorten). The new header's dropTask adds the missing index bounds check: i >= n or n == 0 terminates loudly (std::terminate, fail fast — no null guards, no SEH) instead of out-of-bounds UB on the 0x80-byte entry array.

Reorder — TaskDispatchHook::swap: std::swap of two raw 0x80 entries; {task, controlBlock} is a plain memcpy so refcounts stay consistent. The new header's swapTasks bounds-checks i and j the same way.

Per-task enable already exists in the game: vtbl[3](task) via the CFG thunk [0xF99FFA0]; only eax == 1 tasks run (rows 0xE90046B/0xE90046F/0xE90047A).

Rules from recipe 6dg that listeners must obey: (1) never disable the Scene/HUD per-view setup body (0x568CD90) unless the whole view is dropped — it writes the per-view rect, matrices and sort mode that Encoder::submit reads (BGFX_MAP 6dd); (2) reorder only dependency-free tasks — dependency vectors are built by the generator 0xC273420 from declaration order; (3) insert is unsupported by the hook — new tasks must be declared in generate 0xC273420 (FrameGraph.h, generated entry stride 0x80); use Encoder::submit for extra draws.

Gaps remaining on disk (not code; cannot be built or tested by this unit):
- No "disable via no-op std::function stub at task+0x70" helper (6dg point 2) exists — only physical remove.
- addListener has no caller anywhere in src and HookManager.cpp never installs the hook; wiring registration is out of scope for this unit (editing HookManager.cpp is forbidden).

## 6) Live corroboration (existing data — no new capture needed)

docs/data/live/u_em1f_dispatch.txt (`# live capture u_em1f_dispatch rva=0xE9002E0 kind=regs size=0x200`; line format `REG=value hit=N hexbytes`):

- Line 3: `CALLER ret=0xC270559 first_hit=1` — the caller return address is 0xC270559, exactly the instruction after `0xC270554  call 0xE9002E0`; hits 1..10 all show ret=0xC270559 → endFrame calls the dispatch once per frame [V live]. Confirms static row 0xC270554.
- RCX hit=1 (line 4): the register dump at the TaskList* shows qword0 = begin, qword1 = end = begin + 0x900, qword2 = cap = end + 0x80, qword3 = extra = 0 → end - begin = 0x900 → 18 entries per frame = (end - begin) >> 7 (static rows 0xE900366/0xE900369/0xE900370/0xE900373), extra = 0 → normal walk path (row 0xE900314) [V live]. Same shape in every RCX sample (hits 1, 3, 5, 7, 9).
- R9 dumps contain pass-name strings: "[ClearColorDepth][Scene]" (3 samples), "[ClearDepth][HUD]" (1), "SceneWaitOnChunk" (1), "terrainAtlasBlit" (2), "inventory_screen" (3) [V live] — the named entries the hook can drop/swap by name via taskName. Matches the statically sampled 18-task frame order in docs/BGFX_MAP.md section 6cx ([ClearColorDepth][Scene], Scene x12, [ClearDepth][HUD], HUD, Pass, TerrainAtlasBlit, SceneWaitOnChunk = 18) [V].

No new capture was queued: docs/data/live/u_em1f_dispatch.txt already covers the hook site with 10 samples, caller ret=0xC270559.

## 7) TOOL REQUESTS

In-game test plan (M3c; to be run after the orchestrator's build, with a listener registered through TaskDispatchHook::addListener — wiring the listener into HookManager.cpp is out of scope for this unit):

1. Baseline — regs capture at 0xE9002E0 (rcx = TaskList*): expect end - begin = 0x900 → 18 entries, extra = 0, caller ret = 0xC270559 once per frame (already shown by docs/data/live/u_em1f_dispatch.txt, hits 1-10).
2. Disable a pass — listener scans nameOf for e.g. "terrainAtlasBlit" and drops that index. Read back: next capture shows 17 entries (end - begin = 0x880) and nameOf never returns "terrainAtlasBlit"; the frame still completes (frame counter advances, no crash).
3. Reorder — listener swaps two adjacent entries (e.g. "HUD" and "Pass"). Read back: capture shows the same 18 entries with the two names exchanged at their indices; frame completes.
4. Insert — expected negative result: the hook has no insert path; a new pass requires a declaration in generate 0xC273420 (FrameGraph.h, generated entry stride 0x80). Documented as not supported; do not attempt in game.

What to read back: regs capture at 0xE9002E0 — RCX = TaskList*, qword 0 = begin, qword 8 = end, count = (end - begin) >> 7, entry order/names via the listener log. Expected values: baseline 18; after disable 17 with the named entry absent; after reorder 18 with swapped order.

Capture queue: none queued now — docs/data/live/u_em1f_dispatch.txt already covers the dispatch site (10 samples, ret=0xC270559). A regs capture at 0xE9002E0 becomes meaningful only after the build wires a listener; if the orchestrator needs per-step evidence, queue `python tools/livecap/request.py add <name> 0xE9002E0 --kind regs --size 0x200 --max 8 --why "U-EM3c pass disable/reorder test"` then.

## 8) CLOSES?

CLOSES? NO — M3c as worded requires "the build + in-game test" (disable, reorder, insert a pass through TaskDispatchHook; P1b/P2c/P3d/Q5b written, never built or run). Everything that can exist on disk without a build is done: the hook and Tasks.h are written and statically verified against the exe (proof table above, all [V]); the fail-fast bounds-checked edit header is added; the in-game test plan is written. Single blocking fact: the build has not been performed and the hook is not wired/enabled in HookManager.cpp (units may not build or launch the game, and editing HookManager.cpp is out of scope). Re-open this unit after the orchestrator's build + in-game test to set CLOSES? YES.

## NEXT
DONE
