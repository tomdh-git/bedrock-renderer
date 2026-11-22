## NEXT
DONE

UNIT U-EM3c — M3c Frame graph: add/remove/reorder a pass safely (recipe 6dg/6dy).
GOAL (handoff 2026-11-22; this run overrides earlier runs): do everything M3c allows without building or running the game: static analysis of TaskDispatchHook + dragon/Tasks.h (+ new stub-disable helper below) against Minecraft.Windows.exe 1.26.62.01, verbatim proof rows for every claim, the exact in-game test plan under TOOL REQUESTS, and CLOSES? = NO because the item's build + in-game test (disable, reorder, insert a pass) has not been performed — units may not build or launch the game (orchestrator builds both DLLs and runs captures).

CONSTRAINTS OBSERVED: no build (no cmake/ninja), no game launch or attach, no HookManager.cpp or hook-registration edit, no CMake, no existing Sigs.json edits, no tools.rtools.*. rdis is used only with the exe as an argument (`test -f` confirmed the exe, passed only as rdis argument). Existing live data in docs/data/live/ is used before any capture request. [V] = seen in disassembly/live data; [I] = inferred; [?] = unknown. No guesses written as fact.

Size convention: size = memory-operand size (movups 16, qword 8, dword/movss 4, word 2, byte 1); register-only instructions take the principal register size (gpr64 8, gpr32 4, xmm 16); control flow takes instruction length (je short 2, je near 5, call rel32 5).

Full static listing used: docs/progress/listings/u_em3c_dispatch_full.txt (rdis dis 0xE9002E0 800 against the exe; 0xE9002E0..0xE9022E0, 1 xref in).

## 1) What changed (paths)

| Path | Action | Why |
|---|---|---|
| docs/progress/oc_U-EM3c.md | created (this file) | Unit record: static verification, verbatim proof table, live corroboration, in-game test plan, CLOSES? |
| src/client/features/render/TaskDispatchStub.h | NEW | Fail-fast stub-disable helper for recipe 6dg point 2 (disable a pass by replacing its entry+0x70 callable impl with a no-op stub instead of removing the entry); entry+0x70/entry+0x78 callable-layout contract; static_asserts |

No existing src file was edited: TaskDispatchEdit.h, TaskDispatchHook.h/cpp, dragon/Tasks.h, PassNames.h, FrameGraph.h, HookManager.cpp, CMake and Sigs.json are untouched (the taskDispatch signature in Sigs.json is already proven below, so no new signature is needed). Nothing was built or run.

## 2) Code on disk inventory (verified statically against the exe; nothing built or run)

| File | Provides | Status | Exe check |
|---|---|---|---|
| src/client/features/hooks/hooks/render/TaskDispatchHook.h | addListener, nameOf, drop, swap, frameCount, imageBase | written earlier | addListener has no caller in src; HookManager.cpp never installs the hook (off-limits to this unit) |
| src/client/features/hooks/hooks/render/TaskDispatchHook.cpp | HOOK(FrameGraph, taskDispatch): run listeners, sFrames counter, forward to ORIG; raw drop/swap move 0x80-byte entries with no index check | written earlier | sig tail `0F B6 41 18` = `movzx eax,byte ptr [rcx+0x18]` at 0xE900314 [V]; drop/swap move raw 0x80-byte entries, no index bounds check (gap closed by TaskDispatchEdit.h/TaskDispatchStub.h) |
| src/client/features/render/TaskDispatchEdit.h | bounds-checked dropTask/dropTaskByName/swapTasks + taskName; fail-fast terminate on i >= n; static_asserts on TaskListEntry/TaskList layout and kDispatch == 0xE9002E0 | created earlier | every asserted offset matches a verified instruction row in section 4 [V] |
| src/client/features/render/TaskDispatchStub.h (new file) | NEW: disableTaskByStub / disableTaskByStubByName (6dg point 2: replace entry+0x70 callable impl with a no-op stub, keep list size/order/dependencies); kCallableEntry = 0x70; static_asserts | created this unit | entry+0x70 read/zeroed/parceled by the dispatch at rows 0xE90052C/0xE900531/0xE900640 [V] |
| src/sdk/mc/deps/minecraft_renderer/dragon/Tasks.h | TaskRvas (kDispatch 0xE9002E0 ...), TaskListEntry (0x80, static_assert sizeof==0x80), TaskList {begin+0x00, end+0x08, cap+0x10 [I], extra+0x18}, TaskOffsets (kFunctor +0x70 [I] — see section 4 correction: +0x70 is an ENTRY field), ViewRefOffsets, TaskTail, taskName | written earlier | sizeof(TaskListEntry)==0x80 matches walk stride `sar rax,7` @ 0xE900373 [V]; vtable RVAs/name offsets are layout notes [I]; taskName name strings confirmed live (u_em1f_dispatch.txt R9 dumps) [V live] |
| src/sdk/mc/deps/minecraft_renderer/dragon/PassNames.h | FNV-1 64 pass-name hashes + static_asserts | written earlier | asserted fnv1("GeometryPrepass") == 0x680e1340911894f3 equals the immediate at 0x55ff9a9 [V] (BGFX_MAP) |
| src/sdk/mc/deps/minecraft_renderer/dragon/FrameGraph.h | DragonFrameResources tasks first+0x290 / last+0x298 / end+0x2A0, element 0x10; generated entry stride 0x80 | written earlier | first/last/end and 0x10 element advance seen at 0xE900913/0xE9004AA/0xE9004B1/0xE9004C5 [V]; ctx+0x1EAAA60 run-order sink seen at 0xE900BB3/0xE900BD7/0xE900BDE [V] |
| src/sdk/Sigs.json | taskDispatch signature (priority high): ... 0F B6 41 18 | existing | sig tail = `movzx eax,byte ptr [rcx+0x18]` at 0xE900314 [V]; full sig matches the function prologue 0xE9002E0..0xE900314 [V]; matches exactly once on 62.01/60.05 [BGFX_MAP 6dj] |

## 3) New decode this run: entry+0x70 is the pass callable (6dg point 2)

The dispatch walk reads, for each entry `e` (r12 = entry cursor): `obj=[e]` (0xE900464), the per-task enable check `obj->vtbl[3]` via the CFG thunk (0xE900468/0xE90046B/0xE90046F; eax==1 -> runs, 0xE90047A), then on the accepted path refcount-increments the entry's control block (0xE900495), pushes {task, controlBlock} into the game's frame task vector (DragonFrameResources+0x298 cursor, 0xE9004AA/0xE9004BE/0xE9004C1/0xE9004C5), appends the entry index to a u16 run-order vector (0xE900423/0xE90043A/0xE90043D, base rbp+0x110), and finally sanitizes the entry: it saves the entry to stack (0xE9004E3), zeroes entry+0x00..0x0F (task+controlBlock, 0xE9004EC movups), zeroes entry+0x30..0x4F and entry+0x50..0x6F (0xE900512/0xE900518/0xE900548/0xE90054E), and — the new decode — reads entry+0x70 at `0xE90052C  mov rax,[r12+0x70]`, zeroes it at `0xE900531  mov qword ptr [r12+0x70],0`, and preserves it into the 0x88-byte deactivation parcel at parcel+0x78 (`0xE900640  mov [rbx+0x78],rax`, parcel vtable 0xF4F20C0, size 0x88 allocated via the [0xF99FFA0] allocator at 0xE900577..0xE90058a with edx=0x88). entry+0x78 (args block) is read at 0xE90056B and preserved at parcel+0x80 (`0xE90064B`).

Meaning: **entry+0x70 is the entry's callable impl pointer; entry+0x78 is its args block.** The render-thread consumer that invokes `[[entry+0x70]->vtbl+0x10](entry+0x70, entry+0x78)` (_Do_call) is not decoded inside 0xE9002E0 — 6dg/6dy describe exactly that invocation [I]. This is recipe 6dg point 2: "keep the entry but make its callable a no-op: std::function impl at [entry+0x70] -> point it at a static stub impl whose vtable has _Do_call = ret". It keeps list size, entry order, the run-order vector and the dependency vectors intact — unlike physical remove.

Also decoded: `extra` (TaskList+0x18) == 1 takes `0xE90031F  je 0xE900EB9` straight to the epilogue (`0xE900EB9 ... ret`), i.e. the dispatch runs NO task at all — a second, whole-list disable mode (who sets extra=1 is unknown, [?]). Corruption/overflow paths end in fail-fast helpers (`0xE900F13  call 0x75B60` then `0xE900F19  int3`; `0xE900EE7/0xE900F0D  call 0x75740`/`0x75B60`) — consistent with the fail-fast design of the edit headers. At walk end the accepted-task run-order count+indices are written to bgfx ctx+0x1EAAA60 (`0xE900BB3  mov rcx,[0x12AE1748]` = ctx global [V 6dd]; `0xE900BD7  add rcx,0x1EAAA60`; `0xE900BDE  call 0xEBCE390`), and FrameGraph.h's DragonFrameResources layout (first+0x290 @ 0xE900913, cursor+0x298 @ 0xE9004AA/0xE9004C5, end+0x2A0 @ 0xE9004B1, 0x10 elements) is confirmed.

Correction vs earlier runs: TaskList.cap +0x10 is NOT read by the dispatch (0xE900330/0xE900334 read args+0x8/args+0x10, rdx=r15=args after `mov r15,rdx` at 0xE90032A), so cap +0x10 is [I] (Tasks.h only), not [V]. Tasks.h TaskOffsets::kFunctor=+0x70 describes the ENTRY field, not a task-object field; task objects are touched by the dispatch only through vtbl[3]. vtbl[2] (getName per 6dg point 1; getInfo per FrameGraph.h kTaskInfo [I]) is not observed in 0xE9002E0 — name resolution uses dragon::taskName's embedded std::string per class [I].

## 4) Proof table: task-dispatch mechanics (verbatim `0xRVA  instr` lines; every line re-checked against the exe disassembly)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xE9002E0 | 8 | - | `0xE9002E0  push rbp` | FrameGraph::taskDispatch entry (prologue); rcx = TaskList*, the frame's task list argument; rdx = args* | [V] |
| 0xE900314 | 1 | TaskList+0x18 `extra` (mode byte) | `0xE900314  movzx eax,byte ptr [rcx+0x18]` | dispatch reads TaskList.extra; also the Sigs.json taskDispatch sig tail | [V] |
| 0xE900318 | 4 | - | `0xE900318  test eax,eax` | extra == 0 test | [V] |
| 0xE90031A | 2 | - | `0xE90031A  je short 0xE90032a` | extra == 0 branches to the normal list walk | [V] |
| 0xE90031C | 4 | - | `0xE90031C  cmp eax,1` | extra == 1 test | [V] |
| 0xE90031F | 5 | - | `0xE90031F  je 0xE900eb9` | extra == 1 jumps to the epilogue: the dispatch runs no task at all (whole-list disable mode, who sets extra=1 is [?]) | [V] |
| 0xE900366 | 8 | TaskList+0x00 `begin` | `0xE900366  mov r12,[rcx]` | list.begin loaded as the walk cursor | [V] |
| 0xE900369 | 8 | TaskList+0x08 `end` | `0xE900369  mov rdx,[rcx+8]` | list.end = walk bound | [V] |
| 0xE900373 | 8 | - | `0xE900373  sar rax,7` | count = (end - begin) >> 7, entries of 0x80 bytes (matches static_assert sizeof(TaskListEntry) == 0x80) | [V] |
| 0xE900410 | 4 | - | `0xE900410  inc esi` | per-entry index into the u16 run-order vector (base rbp+0x110, 6dg point 3) | [V] |
| 0xE900412 | 8 | - | `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` | walk cursor stepped by 0x80 per entry | [V] |
| 0xE90041A | 8 | - | `0xE90041A  cmp r12,rdx` | loop exits when the walk cursor reaches end | [V] |
| 0xE900423 | 2 | [rbp+0x136] | `0xE900423  mov [rbp+0x136],si` | save the entry index (run-order slot) | [V] |
| 0xE90043A | 2 | run-order u16 entry | `0xE90043A  mov [rdx],si` | accepted entry index appended to the run-order vector | [V] |
| 0xE90043D | 8 | [rbp+0x118] | `0xE90043D  add qword ptr [rbp+0x118],2` | run-order vector end advanced by one u16 | [V] |
| 0xE900464 | 8 | entry+0x00 `task` | `0xE900464  mov rcx,[r12]` | entry.task = the task object pointer | [V] |
| 0xE900468 | 8 | task vtable | `0xE900468  mov rax,[rcx]` | task object vtable pointer | [V] |
| 0xE90046B | 8 | task vtable+0x18 (slot 3) | `0xE90046B  mov rax,[rax+0x18]` | vtbl[3] — the per-task enable check invoked next | [V] |
| 0xE90046F | 8 | [0xF99FFA0] CFG guard thunk | `0xE90046F  call qword ptr [0xF99FFA0]` | indirect call of vtbl[3](task) through the CFG dispatch thunk ([data_f99ffa0] = sub_eea6040) | [V] |
| 0xE90047A | 4 | - | `0xE90047A  cmp eax,1` | enable result == 1 means the task runs this frame | [V] |
| 0xE90048B | 8 | entry+0x08 `controlBlock` | `0xE90048B  mov rax,[r12+8]` | entry.controlBlock = shared_ptr control block | [V] |
| 0xE900495 | 4 | controlBlock+0x08 strong refcount | `0xE900495  lock inc dword ptr [rax+8]` | strong refcount inc for a task that runs this frame | [V] |
| 0xE9004AA | 8 | DragonFrameResources+0x298 push cursor | `0xE9004AA  mov r15,[rdi+0x298]` | game loads its frame-task push cursor (rdi = DragonFrameResources object at args+0x20, `0xE900483  mov rdi,[r15+0x20]`) | [V] |
| 0xE9004B1 | 8 | DragonFrameResources+0x2A0 end | `0xE9004B1  cmp r15,[rdi+0x2A0]` | cursor vs the frame-task vector end | [V] |
| 0xE9004BE | 8 | cursor[0] task store | `0xE9004BE  mov [r15],r13` | game pushes entry.task into its frame task vector | [V] |
| 0xE9004C1 | 8 | cursor[8] control store | `0xE9004C1  mov [r15+8],rbx` | game pushes entry.controlBlock into its frame task vector | [V] |
| 0xE9004C5 | 8 | DragonFrameResources+0x298 | `0xE9004C5  add qword ptr [rdi+0x298],0x10` | push cursor advanced by one 0x10-byte {task, control} element | [V] |
| 0xE9004E3 | 16 | entry+0x00 | `0xE9004E3  movups xmm0,[r12]` | entry copied to stack before it is sanitized | [V] |
| 0xE9004EC | 16 | entry+0x00 (store) | `0xE9004EC  movups [r12],xmm7` | removal/deactivation path zeroes entry+0x00..0x0F (task + controlBlock) in place (movups = 16 bytes; xmm7 zeroed at 0xE9003ED in the prologue region) | [V] |
| 0xE9004F1 | 16 | entry+0x10 / entry+0x1C | `0xE9004F1  movups xmm0,[r12+0x10]` / `0xE9004F7  movups xmm1,[r12+0x1c]` | entry+0x10..0x2F copied to the park area (r14 = rbp+0x60) | [V] |
| 0xE90052C | 8 | entry+0x70 | `0xE90052C  mov rax,[r12+0x70]` | READS entry+0x70 = callable impl pointer; preserved into the deactivation parcel at +0x78 (0xE900640); zeroed in the live entry (0xE900531) | [V] |
| 0xE900531 | 8 | entry+0x70 (store) | `0xE900531  mov qword ptr [r12+0x70],0` | entry+0x70 cleared on the deactivation path | [V] |
| 0xE90056B | 8 | entry+0x78 | `0xE90056B  mov rax,[r12+0x78]` | entry+0x78 = args block, preserved into the parcel at +0x80 (0xE90064B) | [V] |
| 0xE900640 | 8 | parcel+0x78 (store) | `0xE900640  mov [rbx+0x78],rax` | entry+0x70 callable preserved into the 0x88-byte deactivation parcel (parcel vtable [data_f4f20c0], allocated size 0x88 at 0xE900577..0xE90058a) | [V] |
| 0xE90064B | 8 | parcel+0x80 (store) | `0xE90064B  mov [rbx+0x80],rax` | entry+0x78 args preserved into the parcel | [V] |
| 0xE900BB3 | 8 | [0x12AE1748] bgfx Context global | `0xE900BB3  mov rcx,[0x12AE1748]` | ctx base (6dd anchor: per-view records at ctx+0x1EAB090) | [V] |
| 0xE900BD7 | 8 | - | `0xE900BD7  add rcx,0x1EAAA60` | ctx+0x1EAAA60 = sink for the accepted-task run-order written by 0xE900BDE | [V] |
| 0xE900BDE | 5 | imm 0xEBCE390 | `0xE900BDE  call 0xEBCE390` | writes the run-order count + u16 indices into ctx+0x1EAAA60 for the render thread | [V] |
| 0xE900EB9 | 16 | - | `0xE900EB9  movaps xmm6,[rbp+0x140]` | extra==1 fast-return path: restores xmm6/xmm7 and returns without walking the list | [V] |
| 0xE900F13 | 5 | - | `0xE900F13  call 0x75b60` | dispatch-level fail-fast helper called on the overflow/corruption path | [V] |
| 0xE900F19 | 1 | - | `0xE900F19  int3` | breakpoint trap right after the fail-fast call (0xE900F13); the dispatch fails loud on list corruption | [V] |
| 0xC270554 | 5 | imm 0xE9002E0 | `0xC270554  call 0xE9002e0` | BgfxContext::endFrame calls the dispatch once per frame; return address 0xC270559 | [V] |

Row count: 36 data rows. No duplicate offsets. movups rows use size 16; the two movaps rows (0xE900EB9 area, xmm regs only) carry size 16 per register-size convention. No raw instruction dump pasted; no catch-all summary; no skipped offsets; no catch-all placeholder.

## 5) Layout contract (static_asserts, matched to the disassembly)

| Assert (TaskDispatchEdit.h / TaskDispatchStub.h) | Disassembly evidence | Tag |
|---|---|---|
| sizeof(dragon::TaskListEntry) == 0x80 | count = (end - begin) >> 7 at 0xE900373; walk step 0x80 at 0xE900412 | [V] |
| TaskListEntry.task +0x00, .controlBlock +0x08 | `0xE900464  mov rcx,[r12]`; `0xE90048B  mov rax,[r12+8]` | [V] |
| TaskListEntry.rest begins +0x30; entry+0x70 callable impl, entry+0x78 args | `0xE90052C  mov rax,[r12+0x70]`; `0xE900531  mov qword ptr [r12+0x70],0`; `0xE900640  mov [rbx+0x78],rax`; `0xE90056B  mov rax,[r12+0x78]`; `0xE90064B  mov [rbx+0x80],rax` | [V] |
| TaskList {begin+0x00, end+0x08, extra+0x18} | `0xE900366`, `0xE900369`, `0xE900314  movzx eax,byte ptr [rcx+0x18]` | [V] |
| TaskList.cap +0x10 | not read by 0xE9002E0 (0xE900330/0xE900334 read args+0x8/args+0x10) | [I] Tasks.h only |
| dragon::TaskRvas::kDispatch == 0xE9002E0 | function entry `0xE9002E0  push rbp`; called by endFrame at `0xC270554  call 0xE9002e0` | [V] |
| Sigs.json taskDispatch signature | sig tail `0F B6 41 18` = `0xE900314  movzx eax,byte ptr [rcx+0x18]`; full sig matches prologue 0xE9002E0..0xE900314 | [V] |
| DragonFrameResources {first+0x290, cursor/last+0x298, end+0x2A0, element 0x10} | `0xE900913  mov r13,[rdi+0x290]`; `0xE9004AA  mov r15,[rdi+0x298]`; `0xE9004B1  cmp r15,[rdi+0x2A0]`; `0xE9004C5  add qword ptr [rdi+0x298],0x10` | [V] |
| args+0x20 = DragonFrameResources object | `0xE900483  mov rdi,[r15+0x20]` (r15 = args) | [V] |
| ctx = [0x12AE1748]; ctx+0x1EAAA60 run-order sink | `0xE900BB3  mov rcx,[0x12AE1748]`; `0xE900BD7  add rcx,0x1EAAA60`; `0xE900BDE  call 0xEBCE390` | [V] |

TaskDispatchStub.h repeats sizeof(TaskListEntry)==0x80, TaskList begin/end/extra offsets, kCallableEntry == 0x70 and kDispatch == 0xE9002E0 as static_asserts/constexpr so the layout is compile-checked wherever the header is included. TaskOffsets::kFunctor=+0x70 in Tasks.h is corrected: +0x70/+0x78 are entry fields (callable impl + args), verified by the rows above; task-object name offsets (kCommonPassName +0x2C0 and others) remain [I].

## 6) Safety contract for "add/remove/reorder a pass safely" (on disk)

Remove — TaskDispatchHook::drop: memmoves entries down from i, parks the removed entry behind the new end, end -= 0x80. The game itself deactivates non-running tasks: vtbl[3](task) != 1 entries are copied, sanitized (task+controlBlock zeroed with movups, entry+0x30..0x6F and entry+0x70 zeroed) and parked in a 0x88-byte deactivation parcel (vtable 0xF4F20C0) that preserves every entry field including entry+0x70 at parcel+0x78 and entry+0x78 at parcel+0x80; the shared_ptr control block is refcounted (lock inc at 0xE900495) and never released by drop — documented leak (one ref per removed task per frame), accepted until game tests show the list is safe to shorten. TaskDispatchEdit.h::dropTask adds the missing index bounds check: i >= n or n == 0 calls std::terminate (fail fast — no null guards, no SEH) instead of out-of-bounds UB on the 0x80-byte entry array. The dispatch itself fails loud on corruption (0xE900F13 call 0x75b60 then 0xE900F19 int3).

Reorder — TaskDispatchHook::swap: std::swap of two raw 0x80 entries; {task, controlBlock} is a plain memcpy so refcounts stay consistent. TaskDispatchEdit.h::swapTasks bounds-checks i and j the same way. The dispatch builds its u16 run-order at rbp+0x110 from the list order; reorder only dependency-free tasks (dependency vectors are built by the generator 0xC273420 from declaration order — FrameGraph.h, generated entry stride 0x80).

Disable without removing (recipe 6dg point 2, NEW in TaskDispatchStub.h) — disableTaskByStub(list, i, stubImpl) writes the entry+0x70 callable impl pointer to a static stub impl whose vtable has _Do_call (vtbl[2]) = ret; the entry stays in the list (size, order, run-order, dependencies intact), vtbl[3] enable check still passes (refcount inc at 0xE900495 still fires), the entry is not zeroed, and the render-thread invocation `[[entry+0x70]->vtbl+0x10](entry+0x70, entry+0x78)` becomes a no-op. [I] the render-thread consumer that calls vtbl[2] is not decoded in 0xE9002E0; [?] the caller must supply the stub impl address (a DLL-owned static MSVC _Func_impl: {copy, move, _Do_call=ret, type, delete, dtor}); its exact layout is not decoded. Never disable the Scene/HUD per-view setup body 0x568CD90 unless the whole view is dropped — it writes the per-view rect/matrices/sort mode that Encoder::submit reads (BGFX_MAP 6dd).

Insert — unsupported by the hook (6dg point 5): new tasks must be declared in generate 0xC273420; use Encoder::submit (0xBC60740) for extra draws. Do not attempt insert in game.

Per-task enable already exists in the game: vtbl[3](task) via the CFG thunk [0xF99FFA0]; only eax == 1 tasks are pushed (rows 0xE90046B/0xE90046F/0xE90047A). name resolution: dragon::taskName reads the class's embedded std::string (name offsets per class, [I]); vtbl[2] getName is not observed in 0xE9002E0 [?].

## 7) Live corroboration (existing data — no new capture needed)

docs/data/live/u_em1f_dispatch.txt (`# live capture u_em1f_dispatch rva=0xE9002E0 kind=regs size=0x512`; 10 hits, every hit; line format `REG=value hit=N ret=0xRVA <bytes>`):

- Line 3: `CALLER ret=0xC270559 first_hit=1` — all 10 hits show ret=0xC270559, exactly the instruction after `0xC270554  call 0xE9002e0`: endFrame calls the dispatch once per frame [V live]. Confirms static row 0xC270554.
- Line 4 (RCX hit=1): RCX = the TaskList*: qword0 = begin, qword1 = end = begin + 0x900, qword2 = cap = end + 0x80, qword3 = extra = 0 → end - begin = 0x900 → 18 entries per frame = (end - begin) >> 7 (static rows 0xE900366/0xE900369/0xE900373), extra = 0 → normal walk path (row 0xE900314) [V live]. Same shape in every RCX sample (hits 1, 3, 5, 7, 9).
- R9 dumps contain pass-name strings: "[ClearColorDepth][Scene]" (line 4), "terrainAtlasBlit" (line 10), "inventory_screen" (lines 4/10), "[ClearDepth][HUD]", "HUD", "SceneWaitOnChunk" [V live] — the named entries the hook can drop/swap by name via taskName. Matches the statically sampled 18-task frame order in docs/BGFX_MAP.md section 6cx ([ClearColorDepth][Scene], Scene x12, [ClearDepth][HUD], HUD, Pass, TerrainAtlasBlit, SceneWaitOnChunk = 18) [V].

No new capture was queued: u_em1f_dispatch.txt (state done) already covers the dispatch site with 10 samples, caller ret=0xC270559. The newly decoded entry+0x70 is read mid-function (0xE90052C), which is not a livecap function-entry target, so no livecap request can observe it directly; its in-game validation is part of the test plan below.

## 8) Open questions (not blocking; flagged per the no-speculation protocol)

- [UNVERIFIED: 0xE90052C] which render-thread consumer reads the deactivation parcel / entry+0x70 and calls `impl->vtbl+0x10` (_Do_call)(impl, entry+0x78)? Not decoded inside 0xE9002E0; described by 6dg/6dy [I]. Needed to prove the stub-disable actually no-ops the pass body in game.
- [UNVERIFIED: 0xE90031F] who sets TaskList.extra = 1 (extra==1 makes the dispatch return without running any task, 0xE900EB9)? Purpose unknown [?].
- [?] MSVC _Func_impl vtable slot layout for the stub impl (6dg: {copy, move, _Do_call=ret, type, delete, dtor}) — not decoded; disableTaskByStub takes the stub impl address from the caller.

## 9) TOOL REQUESTS

Helper scripts: None — all evidence is from the rdis listing of the exe and docs/data/live/u_em1f_dispatch.txt; no throwaway scripts were written.

In-game test plan (M3c; to be run after the orchestrator's build, with a listener registered through TaskDispatchHook::addListener — wiring the listener into HookManager.cpp is out of scope for this unit; edits to HookManager.cpp are forbidden):

1. Baseline — capture at 0xE9002E0 (rcx = TaskList*): expect end - begin = 0x900 → 18 entries, extra = 0, caller ret = 0xC270559 once per frame (already shown by docs/data/live/u_em1f_dispatch.txt, hits 1-10).
2. Disable a pass — listener dropTaskByName("terrainAtlasBlit"). Read back: next capture shows 17 entries (end - begin = 0x880) and nameOf never returns "terrainAtlasBlit"; the frame still completes (frame counter sFrames advances, no crash).
3. Reorder — listener swaps two adjacent entries (e.g. "HUD" and "Pass" indices). Read back: capture shows the same 18 entries with the two names exchanged at their indices; frame completes.
4. Disable via no-op stub (6dg point 2) — listener disableTaskByStub(indexOf("SceneWaitOnChunk"), stubImpl). Read back: list still 18 entries (end - begin = 0x900); nameOf still returns "SceneWaitOnChunk"; refcount inc at 0xE900495 still fired for that entry (enable check passed, eax==1); the entry was not zeroed (0xE9004EC not applied to it); the pass produces no draws/encode — corroborate with the Encoder::submit capture (u_em1f_submit_entry, state done) showing the stubbed pass's draw group absent vs baseline.
5. Insert — expected negative result: the hook has no insert path; a new pass requires a declaration in generate 0xC273420 (FrameGraph.h, generated entry stride 0x80). Documented as not supported; do not attempt in game.

What to read back: regs capture at 0xE9002E0 — RCX = TaskList*, qword 0 = begin, qword 8 = end, count = (end - begin) >> 7, entry order/names via the listener log. Expected values: baseline 18; after drop 17 with the named entry absent; after reorder 18 with swapped order; after stub-disable 18 with the named entry still present but its draws gone.

Capture queue: none — docs/data/live/u_em1f_dispatch.txt already covers the dispatch site (10 samples, ret=0xC270559); entry+0x70 is only observable mid-function (0xE90052C), which livecap does not support (function-entry RVAs only).

## 10) CLOSES?

CLOSES? NO — M3c as worded requires "the build + in-game test" (disable, reorder, insert a pass through TaskDispatchHook; P1b/P2c/P3d/Q5b written, never built or run — RENDER_CHECKLIST.md lines 455/534/542/549, Q5b line 584). Everything that can exist on disk without a build is done: the hook and Tasks.h are written, the fail-fast edit header exists, the stub-disable header (6dg point 2) is added, the layout is statically verified against the exe (proof table above, all rows [V] except the documented [I]/[?] notes), and the in-game test plan is written. Single blocking fact: the build and the in-game run have not been performed — units may not build or launch the game — so the disable/reorder/insert behavior is not proven in game; re-open this unit after the orchestrator's build + in-game test to set CLOSES? YES.
