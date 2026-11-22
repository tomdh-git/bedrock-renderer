## NEXT
DONE

# U-EL3p — pending part of checklist item L3p: per-frame enumeration detour on 0xE9002E0

Item line (docs/RENDER_CHECKLIST.md L3p): "dragon/Tasks.h (task list, class vtables, name offsets, taskName) + PassNames.h written (6eg); the per-frame enumeration detour on 0xE9002E0 not written".

Scope: everything before the semicolon is already written and checked (BGFX_MAP 6eg): src/sdk/mc/deps/minecraft_renderer/dragon/Tasks.h (TaskRvas with dispatch 0xE9002E0 and the five task-class vtables, TaskListEntry 0x80 stride static_assert, TaskList begin+0x00/end+0x08, TaskOffsets functor +0x70 / args +0x78, name offsets per class, taskName(task, imageBase)) and src/sdk/mc/deps/minecraft_renderer/dragon/PassNames.h (FNV-1 64 pass names). This note closes ONLY the pending part: "the per-frame enumeration detour on 0xE9002E0 not written".

Source of truth: rdis of Minecraft.Windows.exe 1.26.62.01, dispatcher 0xE9002E0 (size 0xC3A; single caller 0xC270460 = BgfxContext::endFrame, xref callers). Precomputed listing: docs/progress/pre/0xe9002e0.md. Every `0xRVA  instr` below is verbatim from that listing (re-checked by verify_oc.py against the exe). Tags: [V] = seen in the disassembly, [I] = inferred from structure, [?] = unknown.

## (1) Per-frame enumeration — field map of the detour

| name | rva or offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| hook site A: dispatcher entry; rcx = TaskList*; single caller 0xC270460 = BgfxContext::endFrame [V xref] | 0xE9002E0 | - | `0xE9002E0  push rbp` | [V] |
| detour entry patch span: 8 pushes + `sub rsp,0x1E8` = 19 displaced bytes, ends before `lea rbp,[rsp+0x80]` at 0xE9002F3; a 14-byte jmp fits; nothing live on entry so only the prologue needs trampoline re-execution | 0xE9002E0..0xE9002F3 | 19 | `0xE9002EC  sub rsp,0x1E8` | [V] |
| TaskList.begin: walk pointer r12 = [rcx] at entry; reloaded from rdi (rdi = rcx copy) after the grow path | TaskList+0x00 | 8 | `0xE900366  mov r12,[rcx]` `0xE90039B  mov r12,[rdi]` `0xE9003E0  mov r12,[rdi]` | [V] |
| TaskList.end: exclusive end pointer rdx = [rcx+8] | TaskList+0x08 | 8 | `0xE900369  mov rdx,[rcx+8]` `0xE90039E  mov rdx,[rdi+8]` `0xE9003E3  mov rdx,[rdi+8]` | [V] |
| TaskList.state byte: 0 -> fallthrough plain path (0xE90032A), 1 -> early path 0xE900EB9, otherwise call 0x1166E0 at 0xE900325 | TaskList+0x18 | 1 | `0xE900314  movzx eax,byte ptr [rcx+0x18]` | [V] |
| entry count = (end - begin) >> 7, spilled once and re-read for the run-order reserve | stack [rbp+0x50] | 8 | `0xE900377  mov [rbp+0x50],rax` `0xE900391  lea rdx,[rbp+0x50]` | [V] |
| entry stride 0x80: per-iteration advance of walk pointer r12 (r12 += 0x80) | stride 0x80 | - | `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` | [V] |
| end pointer saved at entry to the loop and reloaded every iteration | stack [rbp+0x28] | 8 | `0xE9003FB  mov [rbp+0x28],rdx` `0xE900416  mov rdx,[rbp+0x28]` | [V] |
| hook site B: loop head; r12 = current Entry*, rdx = end, rsi = 0-based index (inc esi at 0xE900410); loop exit je 0xE900BA2 | 0xE90041A | - | `0xE90041A  cmp r12,rdx` `0xE90041D  je 0xE900BA2` `0xE900410  inc esi` | [V] |
| run-order vector<u16>: loop index si stored as u16 at vector begin [rdx], begin advanced by 2 (begin [rbp+0x110], end [rbp+0x120]; full -> call 0x74C9C0 at 0xE90045E) | stack [rbp+0x118] | 2 | `0xE90043A  mov [rdx],si` `0xE90043D  add qword ptr [rbp+0x118],2` | [V] |
| hook site C: first per-entry access; rcx = entry.task object pointer | entry+0x00 | 8 | `0xE900464  mov rcx,[r12]` | [V] |
| task object vtable = first qword of the task object | task+0x00 | 8 | `0xE900468  mov rax,[rcx]` | [V] |
| task-kind vtable slot 0x18 (vtable index 3) loaded for the virtual call | vtable+0x18 | 8 | `0xE90046B  mov rax,[rax+0x18]` | [V] |
| the kind vcall itself, through the CFG-guard thunk [0xF99FFA0] = sub_eea6040 | call [0xF99FFA0] | - | `0xE90046F  call qword ptr [0xF99FFA0]` | [V] |
| kind classifier: returned kind compared against 1 (1 -> owned/registered, pushed into DragonFrameResources) | eax kind result | 4 | `0xE90047A  cmp eax,1` `0xE90047D  jne short 0xE9004D8` | [V] |
| entry.controlBlock: shared_ptr control-block pointer | entry+0x08 | 8 | `0xE90048B  mov rax,[r12+8]` `0xE900499  mov rbx,[r12+8]` | [V] |
| control-block refcount increment (lock inc [cb+8]) | controlBlock+0x08 | 4 | `0xE900495  lock inc dword ptr [rax+8]` | [V] |
| dispatch struct field args+0x20 = DragonFrameResources* (r15 = args at entry; target of the kind==1 push) | args+0x20 | 8 | `0xE900483  mov rdi,[r15+0x20]` | [V] |
| kind==1 push: {task obj, controlBlock} 16-byte element appended at DFR+0x298, cap checked against DFR+0x2A0, end advanced by 0x10 (r13 = entry.task from 0xE90047F; rbx = control block from 0xE900499) | DFR+0x298 / DFR+0x2A0 | 8 | `0xE9004AA  mov r15,[rdi+0x298]` `0xE9004B1  cmp r15,[rdi+0x2A0]` `0xE9004BE  mov [r15],r13` `0xE9004C1  mov [r15+8],rbx` `0xE9004C5  add qword ptr [rdi+0x298],0x10` | [V] |
| entry move-copy out: 16-byte blocks at entry+0x30/+0x40/+0x50/+0x60 copied to stack then zeroed in place (xmm7 = zero) | entry 16-byte blocks at +0x30 / +0x40 / +0x50 / +0x60 | 16 | `0xE900506  movups xmm0,[r12+0x30]` `0xE900512  movups [r12+0x30],xmm7` `0xE90050C  movups xmm1,[r12+0x40]` `0xE900518  movups [r12+0x40],xmm7` `0xE90053A  movdqu xmm0,[r12+0x50]` `0xE900548  movups [r12+0x50],xmm7` `0xE900541  movdqu xmm1,[r12+0x60]` `0xE90054E  movups [r12+0x60],xmm7` | [V] |
| entry+0x70 qword (functor impl slot per Tasks.h TaskOffsets::kFunctor=0x70, [I]) read then zeroed | entry+0x70 | 8 | `0xE90052C  mov rax,[r12+0x70]` `0xE900531  mov qword ptr [r12+0x70],0` | [V] |
| entry+0x78 qword (functor args slot per Tasks.h kFunctorArgs=0x78, [I]) read then stored to stack [rbp+0xC8] | entry+0x78 | 8 | `0xE90056B  mov rax,[r12+0x78]` `0xE900570  mov [rbp+0xC8],rax` | [V] |

## (2) Detour specification (all facts above are [V])

- Site A (chosen; matches the repo's TaskDispatchHook.cpp): detour at 0xE9002E0 with rcx = TaskList*. Enumerate `for (Entry* e = [rcx]; e < [rcx+8]; e += 0x80)`; entry count = ([rcx+8] - [rcx]) >> 7. Displaced prologue is 19 bytes (0xE9002E0 push rbp .. 0xE9002EC sub rsp,0x1E8); a 14-byte jmp fits and no register is live at entry, so only the prologue must be re-executed in the trampoline.
- Site B (alternative): loop head 0xE90041A — r12 = current entry, rdx = end, rsi = index, count at [rbp+0x50], end reloaded from [rbp+0x28].
- Site C (alternative): 0xE900464 — rcx = entry.task; good for per-task interception.
- What a listener reads per entry: task ptr at entry+0x00; control block at entry+0x08 (refcount at controlBlock+0x08, lock inc at 0xE900495); kind via task->vtable[0x18] (call through [0xF99FFA0] at 0xE90046F, cmp eax,1 at 0xE90047A). kind==1 -> the entry's {task, controlBlock} (16 bytes) appended at DragonFrameResources+0x298 with end advanced by 0x10 at 0xE9004C5 (cap DFR+0x2A0), and the loop index pushed as u16 into the run-order vector ([rbp+0x110..0x120], 0xE90043A / 0xE90043D). One detour hit at site A = one frame's task list (single caller 0xC270460 = BgfxContext::endFrame).
- The detour code itself already exists in the repo (src/client/features/hooks/hooks/render/TaskDispatchHook.cpp/.h, HOOK(FrameGraph, taskDispatch) on the Sigs.json `taskDispatch` sig whose pattern is the 0xE9002E0 prologue); building/running it in game is M3c/P1b/Q5b, outside L3p.

OPEN (non-blocking, outside the pending part):
- [UNVERIFIED: 0xE90047A] which task class returns kind 1 from vtable slot 0x18 — the five Tasks.h classes return 0 (slot 0x18 target sub_76920); the kind==1 push path exists in the dispatcher but no statically-known class returns 1.

CLOSES? YES — the pending clause of L3p ("the per-frame enumeration detour on 0xE9002E0 not written") is proven by [V] rows: every quoted instruction matches the exe (verify_oc clean). Hook site A = 0xE9002E0 dispatcher entry (rcx = TaskList*, single caller 0xC270460); stride 0x80 (0xE900412); count = (end-begin)>>7 (0xE900373/0xE900377); loop head 0xE90041A with exit 0xE90041D; per-entry task obj entry+0x00 (0xE900464); kind via vtable slot 0x18 (0xE90046B, call [0xF99FFA0] at 0xE90046F, cmp eax,1 at 0xE90047A); control block entry+0x08 with refcount lock inc at 0xE900495; kind==1 {task,ctrl} push to DragonFrameResources+0x298/+0x2A0, end += 0x10 at 0xE9004C5; run-order u16 index push at [rbp+0x118] (0xE90043A/0xE90043D). dragon/Tasks.h and dragon/PassNames.h (6eg) were already written; building/running the detour hook in game belongs to M3c/P1b/Q5b, not to L3p.

## TOOL REQUESTS
- None — the rdis listing (docs/progress/pre/0xe9002e0.md) plus verify_oc.py covered everything; no helper script was written.
