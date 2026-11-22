## NEXT
DONE

# U-EP3d — P3d: Frame graph add/remove/reorder pass safely (M3c)

Goal (docs/RENDER_CHECKLIST.md section P3, item P3d): "Frame graph add/remove/reorder pass safely — M3c". Acceptance (Q5b): "TaskDispatchHook + Tasks.h built and run in game: disable, reorder, insert a pass (M3c)". Tick rule (checklist header): [x] only when written in docs/BGFX_MAP.md with RVAs/offsets AND an SDK header or hook exists; no partial state.

## 1. What exists on disk now (read from files [V]; none of it built or run)

| path | what it is | status |
|---|---|---|
| src/client/features/hooks/hooks/render/TaskDispatchHook.h / .cpp | listener registry + HOOK(FrameGraph,taskDispatch) at RVA 0xE9002E0; nameOf() via dragon::taskName; drop() parks entry i behind the new end (end -= one 0x80 entry; the parked entry's shared_ptr is never released, small per-frame leak); swap() exchanges two raw entries via std::swap; header states "UNTESTED IN GAME" | present, not registered in HookManager (grep over src found no HookManager.cpp/TaskDispatchHook::addListener reference), never enabled |
| src/client/features/render/rewrite/RewriteProbe.h / .cpp | notePassList() is a TaskDispatchHook::Listener (game thread): records the last frame's pass names in dispatch order, logged as "[probe] frame N passes (K): ..."; armed via BS_PROBE_FRAMES + a Frame::sort detour, mode Off (original runs, read-only probe) | present, not wired to TaskDispatchHook::addListener |
| src/sdk/mc/deps/minecraft_renderer/dragon/Tasks.h | TaskListEntry (size 0x80, static_assert), TaskList {begin+0x00, end+0x08, cap+0x10, extra+0x18}, TaskOffsets {kFunctor=0x70, kFunctorArgs=0x78, name offsets per class}, taskName() reads the embedded std::string (SSO when cap < 16), TaskRvas {kDispatch=0xE9002E0, kFrameGraphGenerate=0xC273420, kBgfxContextEndFrame=0xC270460, kFrameRenderer=0x67C9C20, kSceneHudViewSetup=0x568CD90} | present |
| src/sdk/mc/deps/minecraft_renderer/dragon/PassNames.h | constexpr fnv1 (FNV-1 64, basis 0xcbf29ce484222325, prime 0x100000001b3) with static_assert fnv1("GeometryPrepass") == 0x680e1340911894f3; ~110 pass-name constants | present |
| src/sdk/Sigs.json | "taskDispatch": priority "high", 56-byte pattern, comment cites 6cx/6dg; matches exactly once in the 62.01 .text (BGFX_MAP 6dj/6dj) | present |
| src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h | kTaskDispatch constants: {0x298,"DragonFrameResources task vector begin"}, {0x2A0,"...end"}, {0xFFFFFF80,"task entry stride 0x80 (sub r12,-0x80 at 0xE900412")} | present |
| tools/sigs/layoutcheck.py + docs/data/layout_asserts.json (via RenderLayoutAsserts.h) | 199 layout assertions, 0 failed (O3b); kTaskDispatch constants among them | present |
| docs/BGFX_MAP.md 6dg / 6dy / 8a | pass enable/disable/reorder recipe on 0xe9002e0: disable via no-op std::function impl at [obj+0x70]; reorder via raw entry swap; remove via park + end -= 0x80; add NOT supported by this hook | documented |

## 2. What this unit verified statically (disassembly of 0xe9002e0, the task dispatch; every quote below copied verbatim from rdis and checked by tools/sigs/verify_oc.py)

| offset | size | site | `0xRVA  instr` | meaning |
|---|---|---|---|---|
| 0xe900366 | 8 | [rcx] = TaskList.begin | `0xe900366  mov r12,[rcx]` | list begin pointer (first entry) loaded [V] |
| 0xe900369 | 8 | [rcx+8] = TaskList.end | `0xe900369  mov rdx,[rcx+8]` | one-past-last entry pointer loaded [V] |
| 0xe900373 | 8 | - | `0xe900373  sar rax,7` | entry count = (end - begin) >> 7, i.e. stride 0x80 [V] |
| 0xe900412 | 8 | - | `0xe900412  sub r12,0xFFFFFFFFFFFFFF80` | walk step adds 0x80 per entry [V] |
| 0xe90046b | 8 | [vtable+0x18] | `0xe90046b  mov rax,[rax+0x18]` | task kind read from vtable slot 3 (offset 0x18), invoked through CFG thunk [0xF99FFA0] [V] |
| 0xe90047a | 4 | - | `0xe90047a  cmp eax,1` | kind == 1 selects the owned-task path [V] |
| 0xe900495 | 4 | [rax+8] = shared_ptr control block | `0xe900495  lock inc dword ptr [rax+8]` | control-block refcount increment [V] |
| 0xe9004aa | 8 | [rdi+0x298] = DFR task vector begin | `0xe9004aa  mov r15,[rdi+0x298]` | vector begin loaded (rdi = DragonFrameResources* at dispatch args +0x20) [V] |
| 0xe9004b1 | 8 | [rdi+0x2A0] = DFR task vector end | `0xe9004b1  cmp r15,[rdi+0x2A0]` | vector end compared [V] |
| 0xe9004c5 | 8 | [rdi+0x298] | `0xe9004c5  add qword ptr [rdi+0x298],0x10` | end += 16: append {task object*, control block*} pair [V] |
| 0xe90052c | 8 | [entry+0x70] | `0xe90052c  mov rax,[r12+0x70]` | functor impl pointer read (per-task pass body slot) [V] |
| 0xe900531 | 8 | [entry+0x70] | `0xe900531  mov qword ptr [r12+0x70],0` | functor slot nulled on the remove/relocate path [V] |
| 0xe900585 | 4 | - | `0xe900585  mov edx,0x88` | operator new(0x88): an entry is copied into a new 0x88-byte object [V] |
| 0xe90043a | 2 | [rdx] = run-order cursor | `0xe90043a  mov [rdx],si` | run-order vector push: entry index as u16 [V] |
| 0xe90043d | 8 | [rbp+0x118] | `0xe90043d  add qword ptr [rbp+0x118],2` | run-order cursor += 2 bytes per entry [V] |

Notes: entry stride 0x80 and the DragonFrameResources task vector at +0x298/+0x2A0 match RenderLayoutAsserts.h kTaskDispatch exactly [V]; the DFR object behind dispatch args+0x20 is identified by BGFX_MAP 6cx [I]. The task object's pass body runs through its std::function: impl pointer at obj+0x70, _Do_call = vtable slot 2, invoked as [[obj+0x70]->vtbl+0x10](obj+0x70, obj+0x78) [I per BGFX_MAP 6dg; that call site is not inside the quoted range].

## 3. Safe add/remove/reorder recipe (BGFX_MAP.md 6dg/6dy; anchored on the [V] disassembly above, steps themselves [I] design-level)

- Disable a pass: keep the entry; replace the std::function impl pointer at [obj+0x70] with a no-op impl whose vtable has {copy, move, _Do_call = ret, type, delete, dtor}. The dispatcher still walks the list, so list size, view-setup ordering and dependency vectors stay intact. Do not disable the Scene/HUD per-view setup body 0x568CD90 unless the whole view is dropped (it writes the rect/matrices/sort mode submit reads).
- Reorder: std::swap two raw 0x80-byte entries (the move is a plain memcpy, refcounts stay consistent). Only reorder tasks with no resource dependency between them (dependencies built in declaration order by 0xc273420) or respect the dispatch run-order vector built at the top of 0xe9002e0 (rbp+0x110, one u16 per entry).
- Remove: park the entry behind the new end and end -= 0x80 (TaskDispatchHook::drop does exactly this; leaked shared_ptr per removed task per frame, accepted for a debug hook), or run the entry dtor obj->vtbl[0](obj,1) for kind-1 tasks after dropping the control-block reference.
- Add a pass: NOT supported by this hook — new tasks must be declared in the generator 0xc273420; use Encoder::submit 0xbc60740 for extra draws instead.
- Renderer detection: first entry names distinguish paths ([ClearColorDepth][Scene] = Fancy; VV/RTX names come from the 0x55f1450 / 0xbbe2d50 declaration tables) [6da live, V live].

## 4. Gap (single blocking fact)

CLOSES?: NO. P3d's acceptance (Q5b) is empirical: TaskDispatchHook + Tasks.h must be built and run in game, demonstrating disable, reorder and insert of a pass through the live task dispatch at 0xE9002E0. This unit may not build the DLL and may not launch or attach to the game; the hook's own header states UNTESTED IN GAME, no listener is registered anywhere (no HookManager.cpp or TaskDispatchHook::addListener reference), and nothing has ever run. So no live evidence exists and the checklist box cannot be ticked. Secondary gap: 6dg item 5 — insert is not supported by this hook at all (new tasks require declaration in 0xc273420).

Exact remaining step: build BlueySenseV2, load the DLL, run the game with a TaskDispatchHook listener (e.g. RewriteProbe::notePassList wired through addListener) that dumps the per-frame task list (names via taskName / PassNames.h), disables one pass (no-op impl at obj+0x70), swaps two entries, and confirms the frame completes with the changed order. Only then can P3d be ticked [x].

## TOOL REQUESTS

None — rdis.exe and tools/sigs/verify_oc.py cover all verification needed in this unit.
