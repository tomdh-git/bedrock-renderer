## NEXT
DONE

# U-EC9 — pending part of checklist item C9: "the per-frame enumeration detour on 0xE9002E0 not written"

Everything before the semicolon in the item line is already written and checked (BGFX_MAP 6eg): `src/sdk/mc/deps/minecraft_renderer/dragon/Tasks.h` exists with TaskRvas (dispatch 0xE9002E0, five task-class vtables), `TaskListEntry` (0x80 stride, static_assert), `TaskList` (begin +0x00 / end +0x08), `TaskOffsets` (functor +0x70, args +0x78, name offset per class) and `taskName(task, imageBase)` (reads the class's embedded MSVC std::string, SSO when cap < 16); `dragon/PassNames.h` exists with the FNV-1 64 basis 0xcbf29ce484222325 / prime 0x100000001b3. This note closes ONLY the pending part: the per-frame enumeration detour on 0xE9002E0. It gives the detour's instruction-verified specification (hook site, live registers and list offsets at each candidate site, per-entry reads) with verbatim proof lines from rdis of Minecraft.Windows.exe 1.26.62.01, and records that the detour code itself is already present in the repo (src/client/features/hooks/hooks/render/TaskDispatchHook.cpp, `HOOK(FrameGraph, taskDispatch, ...)` on sig `taskDispatch` = 0xE9002E0 in src/sdk/Sigs.json — its byte pattern `55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC E8 01 00 00 ...` is exactly the prologue proven [V] below). Building and running the hook in game is checklist M3c/P1b/Q5b, not C9.

| name | rva or offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| hook site A: dispatcher entry (per-frame task dispatch; single caller 0xC270460 = BgfxContext::endFrame, xref callers) | 0xE9002E0 | - | 0xE9002E0  push rbp | [V] |
| entry patch span for the detour (8 pushes + `sub rsp,0x1E8` = 19 bytes, ends before `lea rbp,[rsp+0x80]` at 0xE9002F3; a 14-byte jmp patch fits inside) | 0xE9002E0..0xE9002F3 | 19 | 0xE9002EC  sub rsp,0x1E8 | [V] |
| TaskList.begin (rcx at entry; loaded into r12) | TaskList+0x00 | 8 | 0xE900366  mov r12,[rcx] | [V] |
| TaskList.end (exclusive; loaded into rdx) | TaskList+0x08 | 8 | 0xE900369  mov rdx,[rcx+8] | [V] |
| TaskList.extra byte read at entry (0 = plain dispatch path) | TaskList+0x18 | 1 | 0xE900314  movzx eax,byte ptr [rcx+0x18] | [V] |
| entry count = (end-begin)>>7, saved for the run-order pass | stack [rbp+0x50] | 8 | 0xE900373  sar rax,7 | [V] |
| entry stride 0x80; r12 = current entry pointer (advanced once per iteration) | r12 (reg) | - | 0xE900412  sub r12,0xFFFFFFFFFFFFFF80 | [V] |
| end pointer reloaded into rdx each iteration (invariant copy at [rbp+0x28]) | stack [rbp+0x28] | 8 | 0xE900416  mov rdx,[rbp+0x28] | [V] |
| hook site B: loop head (r12 = current Entry*, rdx = end, rsi = 0-based loop index incremented at 0xE900410) | 0xE90041A | - | 0xE90041A  cmp r12,rdx | [V] |
| loop exit branch (jumped when enumeration is done) | 0xE90041D | - | 0xE90041D  je 0xE900BA2 | [V] |
| hook site C: first per-entry task access (rcx = entry.task = task object) | 0xE900464 | - | 0xE900464  mov rcx,[r12] | [V] |
| task object vtable load (first qword of the task object) | task+0x00 | 8 | 0xE900468  mov rax,[rcx] | [V] |
| task-kind vcall slot 0x18 (vtable index 3), dispatched through the CFG guard [0xF99FFA0] | vtable+0x18 | 8 | 0xE90046B  mov rax,[rax+0x18] | [V] |
| the vcall itself (target thunk data_f99ffa0 = sub_eea6040) | 0xE90046F | - | 0xE90046F  call qword ptr [0xF99FFA0] | [V] |
| kind compare against 1 (kind==1 pushes the entry into the DragonFrameResources task vector) | 0xE90047A | - | 0xE90047A  cmp eax,1 | [V] |
| entry.controlBlock (shared_ptr control block, refcount incremented while the wrapper holds the task) | entry+0x08 | 8 | 0xE90048B  mov rax,[r12+8] | [V] |
| control-block refcount increment (dword at cb+8) | controlBlock+0x08 | 4 | 0xE900495  lock inc dword ptr [rax+8] | [V] |

Detour specification (from the [V] rows above; the written hook implements site A):
- Site A (chosen, and the one TaskDispatchHook.cpp installs): detour at 0xE9002E0. On entry rcx = TaskList*; enumerate with `for (e = [rcx]; e < [rcx+8]; e += 0x80)`. The 14-byte jmp patch needs 19 displaced prologue bytes (0xE9002E0 push rbp .. 0xE9002EC sub rsp,0x1E8) re-executed in the trampoline before the original code. No register is live yet at this point, so nothing but the prologue needs relocation.
- Site B (alternative, inside the function): loop head 0xE90041A — r12 = current Entry*, rdx = end Entry*, rsi = loop index, total count at [rbp+0x50]; `(rdx - r12) >> 7` entries remain. Costlier: r12/rbp become live and the two `mov rdx,[rbp+0x28]`/`cmp r12,rdx` bytes must be preserved.
- Site C (alternative): 0xE900464 — rcx = task object, rax = its vtable one instruction later (0xE900468); good for per-task interception, but fires once per entry only inside the dispatcher's own loop.
- What a listener reads per entry (all [V] rows): task pointer at entry+0x00, control block at entry+0x08, kind via `task->vtbl[3]()` (slot 0x18, compare at 0xE90047A), name via dragon::taskName (Tasks.h: vtable 0xF25C7B0 -> +0x2C0, 0xF25C850 -> +0x88, 0xF440770 -> +0x290, 0xF43E9C0 -> +0x130, 0xF25C080 -> +0x80; MSVC std::string, SSO when cap < 16) [V file].
- Per-frame property: the dispatcher has exactly one caller, 0xC270460 (xref callers; BgfxContext::endFrame), so one detour hit = one frame's task list [V xref].

Verbatim instruction proofs (one line per site, exactly as rdis prints them):
    0xE9002E0  push rbp
    0xE9002EC  sub rsp,0x1E8
    0xE900314  movzx eax,byte ptr [rcx+0x18]
    0xE900366  mov r12,[rcx]
    0xE900369  mov rdx,[rcx+8]
    0xE900373  sar rax,7
    0xE900377  mov [rbp+0x50],rax
    0xE900412  sub r12,0xFFFFFFFFFFFFFF80
    0xE900416  mov rdx,[rbp+0x28]
    0xE90041A  cmp r12,rdx
    0xE90041D  je 0xE900BA2
    0xE900464  mov rcx,[r12]
    0xE900468  mov rax,[rcx]
    0xE90046B  mov rax,[rax+0x18]
    0xE90046F  call qword ptr [0xF99FFA0]
    0xE90047A  cmp eax,1
    0xE90048B  mov rax,[r12+8]
    0xE900495  lock inc dword ptr [rax+8]

OPEN facts (outside the pending part, carried from the input data, not blockers for C9):
- [UNVERIFIED: 0xE90047A] which task class returns 1 from vtable slot 0x18 — none of the six known classes do (input data oc_U-C9.md).
- [UNVERIFIED: 0x12862370] structure behind the wrapper task's vtable[3] return pointer (in .data).

CLOSES? YES — the pending part ("the per-frame enumeration detour on 0xE9002E0 not written") is now proven: the detour is written and present as src/client/features/hooks/hooks/render/TaskDispatchHook.cpp + TaskDispatchHook.h (HOOK on sig taskDispatch; Sigs.json carries 0xE9002E0) [V file], and every fact that detour relies on is [V]-proven by the rows above against the exe: hook site 0xE9002E0 with rcx = TaskList, begin +0x00 / end +0x08 / extra byte +0x18, 0x80 stride (r12 advance), count (end-begin)>>7 at [rbp+0x50], loop head 0xE90041A with exit 0xE90041D, per-entry task read 0xE900464, kind vcall at vtable slot 0x18 with the `cmp eax,1` classifier, control block +0x08 with its refcount increment, single per-frame caller 0xC270460, and the 19-byte prologue span that fits a 14-byte entry patch. The dragon/Tasks.h and PassNames.h halves of the item were already written (6eg); the build/run test of the hook belongs to items M3c/P1b/Q5b, not to C9.

## TOOL REQUESTS
- None — the existing toolbox (rdis dis, xref.py callers, verify_oc.py) covered everything; no helper script was written.
