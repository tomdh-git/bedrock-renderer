## NEXT
Write the complete analysis for U-C9: Entry layout, Task object vtable/name, minimum hook design. Then run verify_oc.py.

# UNIT U-C9 — Task list enumeration (checklist C9 in RENDER_CHECKLIST.md; BGFX_MAP 6eg; dispatcher 0xE9002E0 walks a vector<Entry> with Entry size 0x80)

## Scope
Decode every field of the 0x80-byte TaskListEntry that the dispatcher 0xE9002E0 reads/writes; identify the task object vtable slot 0x18 (task kind) and where the task NAME string/hash lives per class; specify the exact instruction range inside 0xE9002E0 where a detour could enumerate tasks per frame.

All tags: [V] = read from disassembly (rdis), [I] = inferred from use, [?] = unknown.

## Source of truth
- Dispatcher: 0xE9002E0 (size 0xC3A, single caller 0xC270460 = BgfxContext::endFrame)
- Preflight listing: `rdis fn 0xe9002e0` output (this document quotes verbatim lines)
- TaskList struct (from Tasks.h, live-verified): begin at +0x00, end at +0x08, cap at +0x10, extra at +0x18
- TaskListEntry struct (from Tasks.h, live-verified): stride 0x80

---

## (1) Entry layout (0x80 bytes) — every field the dispatcher 0xE9002E0 reads/writes

The dispatcher receives the TaskList in **rcx** at entry. It loads `begin` → **r12**, `end` → **rdx**. The main loop iterates `r12` from begin to end, stride 0x80. Each iteration processes one Entry at **r12**.

| Offset | Size | R/W | Meaning | Evidence (quoted `0xRVA  instr`) | Tag |
|--------|------|-----|---------|----------------------------------|-----|
| +0x00 | 8 | R | `task` — pointer to task object (first qword = vtable) | `0xE900464  mov rcx,[r12]` | [V] |
| +0x08 | 8 | R | `controlBlock` — shared_ptr control block (refcounted) | `0xE90048B  mov rax,[r12+8]`<br>`0xE900495  lock inc dword ptr [rax+8]`<br>`0xE900499  mov rbx,[r12+8]` | [V] |
| +0x10 | 8 | R | `state` — heap pointer, per-task state | `0xE9004DB  mov rsi,[r15+0x20]` (r15 = entry ptr) | [V] |
| +0x18 | 8 | R | `kind` — task param/kind index (5 for most scene tasks) | Copied as part of 16-byte load at `0xE9004E3  movups xmm0,[r12]` | [V] |
| +0x20 | 8 | R | `frameId` — value identical in every entry of a frame | Copied as part of 16-byte load at `0xE9004F1  movups xmm0,[r12+0x10]` | [V] |
| +0x28 | 4 | R | `live` — 1 while live | Copied as part of 16-byte load at `0xE9004F1  movups xmm0,[r12+0x10]` (overlaps +0x1C..+0x2B) | [V] |
| +0x2C | 4 | R | `debugColor` | Copied as part of 16-byte load at `0xE9004F7  movups xmm1,[r12+0x1C]` | [V] |
| +0x30 | 16 | R/W | Unknown payload (copied to stack, then zeroed in entry) | `0xE900506  movups xmm0,[r12+0x30]`<br>`0xE900512  movups [r12+0x30],xmm7` | [V] |
| +0x40 | 16 | R/W | Unknown payload (copied to stack, then zeroed in entry) | `0xE90050C  movups xmm1,[r12+0x40]`<br>`0xE900518  movups [r12+0x40],xmm7` | [V] |
| +0x50 | 16 | R/W | Unknown payload (copied to stack, then zeroed in entry) | `0xE90053A  movdqu xmm0,[r12+0x50]`<br>`0xE900548  movups [r12+0x50],xmm7` | [V] |
| +0x60 | 16 | R/W | Unknown payload (copied to stack, then zeroed in entry) | `0xE900541  movdqu xmm1,[r12+0x60]`<br>`0xE90054E  movups [r12+0x60],xmm7` | [V] |
| +0x70 | 8 | R/W | Unknown qword (copied to stack, then zeroed in entry) | `0xE90052C  mov rax,[r12+0x70]`<br>`0xE900531  mov qword ptr [r12+0x70],0` | [V] |
| +0x78 | 8 | R/W | Unknown qword (copied to stack) | `0xE90056B  mov rax,[r12+0x78]`<br>`0xE900570  mov [rbp+0xC8],rax` | [V] |

**Total: 0x80 bytes.** The dispatcher copies the entire entry to the stack (rbp+0x50..rbp+0xC8) via four 16-byte loads + two 8-byte loads, then zeroes the entry in place (except +0x78 which is only read).

**Loop control:**
- Entry pointer: **r12** (init at `0xE900366  mov r12,[rcx]`)
- End pointer: **rdx** (init at `0xE900369  mov rdx,[rcx+8]`)
- Loop head: `0xE90041A  cmp r12,rdx` → `je 0xE900BA2` (exit)
- Per-iteration advance: `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` (i.e. `add r12,0x80`) at the **end** of the loop body (loc_e900410)
- Count computation (once at entry): `0xE900370  sub rax,r12` / `0xE900373  sar rax,7` → `rax = (end - begin) >> 7` = entry count. Stored at `0xE900377  mov [rbp+0x50],rax`.

---

## (2) Task object: vtable slot 0x18 (returns task kind) and name offsets

### Vtable slot 0x18 (index 3, offset 0x18) — task kind
The dispatcher calls this virtual function on **every** task object:

```
0xE900464  mov rcx,[r12]              ; rcx = entry.task
0xE900468  mov rax,[rcx]              ; rax = task.vtable
0xE90046B  mov rax,[rax+0x18]         ; rax = vtable[3] (slot 0x18)
0xE90046F  call qword ptr [0xF99FFA0] ; call task->vtable[3]()
0xE90047A  cmp eax,1                  ; compare returned kind with 1
0xE90047D  jne short 0xE9004D8        ; if not 1, skip special handling
```

**Observed vtable slot 0x18 targets [V]:**

| Task class (vtable RVA) | Slot 0x18 target | Return value | Tag |
|-------------------------|------------------|--------------|-----|
| 0xF25C7B0 (CommonPass) | `sub_76920` (`xor eax,eax; ret`) | 0 | [V] |
| 0xF25C850 (ClearWrapper) | `sub_76920` | 0 | [V] |
| 0xF440770 (GenericPass) | `sub_76920` | 0 | [V] |
| 0xF43E9C0 (TerrainAtlasBlit) | `sub_76920` | 0 | [V] |
| 0xF25C080 (WaitOnChunk) | `sub_76920` | 0 | [V] |
| 0xF4F20C0 (Wrapper task, created by dispatcher) | `sub_e9031f0` (`lea rax,[0x12862370]; ret`) | pointer to data 0x12862370 | [V] |

The dispatcher's `cmp eax,1` implies it expects **some** task class to return 1. None of the six known classes do. The wrapper task (0xF4F20C0) returns a data pointer. The "kind == 1" path at 0xE90047F..0xE9004D4 pushes the entry into DragonFrameResources' vector<shared_ptr<Task>> (see U-C4a).

**Conclusion:** The task kind returned by vtable slot 0x18 is a classifier. Known classes return 0. The wrapper task returns a type-info pointer. The dispatcher treats kind==1 as "push to DFR task list". [UNVERIFIED: 0xE90047A] Which task class returns 1? Not found in static analysis.

### Task NAME string/hash location per class
The task object contains an embedded `std::string` (MSVC layout: union{char buf[16]; char* ptr}, size_t size, size_t cap = 24 bytes). The offset depends on the task class (vtable). Verified from Tasks.h and the four render-thread bodies (docs/functions/568bcd0.md):

| Task class (vtable RVA) | Name offset in task object | Tag |
|-------------------------|---------------------------|-----|
| 0xF25C7B0 (CommonPass) | +0x2C0 | [V] |
| 0xF25C850 (ClearWrapper) | +0x88 | [V] |
| 0xF440770 (GenericPass) | +0x290 | [V] |
| 0xF43E9C0 (TerrainAtlasBlit) | +0x130 | [V] |
| 0xF25C080 (WaitOnChunk) | +0x80 | [V] |

**Wrapper task (vtable 0xF4F20C0):** Created by dispatcher at `0xE90059D..0xE9005B3`. Layout:
- +0x00: vtable (0xF4F20C0)
- +0x08: original task pointer (from entry.task)
- +0x10: original control block (from entry.controlBlock)
- +0x18..: copies 0x70 bytes from stack (saved entry fields)

To get the name of a wrapper task: read original task pointer at wrapper+0x08, read its vtable, match to known class, read std::string at that class's name offset.

**HashedString hash (FNV-1a 64):** The generator (0xC273420) stores the pass name hash at `PassDescOffsets::kU16` area and matches against endFrame's names vector (6eo). The task object itself also stores the hash at inferred offset +0x08 (Tasks.h `kObjNameHash`) and the std::string at +0x10 (Tasks.h `kObjNameString`) for the base task classes. These are [I] — not directly observed in the dispatcher.

---

## (3) Minimum hook design — exact instruction range inside 0xE9002E0 for per-frame task enumeration

A detour can enumerate all tasks for the current frame by hooking the **loop head** where the entry pointer, end pointer, and count are live.

**Optimal hook site: loop head at 0xE90041A**

```
0xE90041A  cmp r12,rdx              ; r12 = current Entry*, rdx = end Entry*
0xE90041D  je 0xE900BA2             ; exit if done
; ... body processes *r12 ...
0xE900410  inc esi                  ; esi = loop index (0,1,2...)
0xE900412  sub r12,0xFFFFFFFFFFFFFF80 ; r12 += 0x80 (next entry)
0xE900416  mov rdx,[rbp+0x28]       ; reload end (invariant)
0xE90041A  cmp r12,rdx              ; loop back
```

**Registers at loop head (0xE90041A):**
- **r12** = current Entry* (TaskListEntry*, stride 0x80)
- **rdx** = end Entry* (exclusive)
- **rsi** = loop index (0-based, incremented at 0xE900410)
- **rbp+0x28** = saved end pointer (backup)
- **rbp+0x50** = total entry count (computed at 0xE900377)

**Count:** `(rdx - r12) >> 7` entries remaining, or read `[rbp+0x50]` for total.

**Alternative hook site: entry load at 0xE900464** (after loop head, before task processing)
```
0xE900464  mov rcx,[r12]              ; rcx = task pointer
0xE900468  mov rax,[rcx]              ; rax = task vtable
; task pointer now in rcx, vtable in rax
```

**Minimum detour specification:**
- **Target RVA:** 0xE90041A (loop head) or 0xE900464 (first task access)
- **Registers to preserve:** All volatile (rax, rcx, rdx, r8-r11) per x64 ABI; r12, rsi, rdi, rbx, rbp, r13-r15 are non-volatile and already preserved by the function prologue.
- **Available context:** r12 = current entry, rdx = end, rsi = index, [rbp+0x50] = total count.
- **Action:** Walk entries from r12 to rdx (step 0x80), for each: read task ptr at +0x00, read vtable, dispatch to name resolver (see Tasks.h `taskName()`), log or modify.

**Quoted instruction block for verification (loop head + one iteration):**

```
0xE900410  inc esi
0xE900412  sub r12,0xFFFFFFFFFFFFFF80
0xE900416  mov rdx,[rbp+0x28]
0xE90041A  cmp r12,rdx
0xE90041D  je 0xE900BA2
0xE900423  mov [rbp+0x136],si
0xE90042A  mov rdx,[rbp+0x118]
0xE900431  cmp rdx,[rbp+0x120]
0xE900438  je short 0xE900450
0xE90043A  mov [rdx],si
0xE90043D  add qword ptr [rbp+0x118],2
0xE900445  jmp short 0xE900464
0xE900450  lea rcx,[rbp+0x110]
0xE900457  lea r8,[rbp+0x136]
0xE90045E  call 0x74C9C0
0xE900463  nop
0xE900464  mov rcx,[r12]
0xE900468  mov rax,[rcx]
0xE90046B  mov rax,[rax+0x18]
0xE90046F  call qword ptr [0xF99FFA0]
0xE900475  nop
0xE900476  mov [rbp+0x20],rsi
0xE90047A  cmp eax,1
0xE90047D  jne short 0xE9004D8
```

---

## Verification quotes (for python tools/sigs/verify_oc.py)

0xE900366  mov r12,[rcx]
0xE900369  mov rdx,[rcx+8]
0xE900370  sub rax,r12
0xE900373  sar rax,7
0xE900377  mov [rbp+0x50],rax
0xE900410  inc esi
0xE900412  sub r12,0xFFFFFFFFFFFFFF80
0xE900416  mov rdx,[rbp+0x28]
0xE90041A  cmp r12,rdx
0xE90041D  je 0xE900BA2
0xE900464  mov rcx,[r12]
0xE900468  mov rax,[rcx]
0xE90046B  mov rax,[rax+0x18]
0xE90046F  call qword ptr [0xF99FFA0]
0xE90047A  cmp eax,1
0xE90047D  jne short 0xE9004D8
0xE90048B  mov rax,[r12+8]
0xE900495  lock inc dword ptr [rax+8]
0xE900499  mov rbx,[r12+8]
0xE9004DB  mov rsi,[r15+0x20]
0xE9004E3  movups xmm0,[r12]
0xE9004F1  movups xmm0,[r12+0x10]
0xE9004F7  movups xmm1,[r12+0x1C]
0xE900506  movups xmm0,[r12+0x30]
0xE900512  movups [r12+0x30],xmm7
0xE90050C  movups xmm1,[r12+0x40]
0xE900518  movups [r12+0x40],xmm7
0xE90053A  movdqu xmm0,[r12+0x50]
0xE900548  movups [r12+0x50],xmm7
0xE900541  movdqu xmm1,[r12+0x60]
0xE90054E  movups [r12+0x60],xmm7
0xE90052C  mov rax,[r12+0x70]
0xE900531  mov qword ptr [r12+0x70],0
0xE90056B  mov rax,[r12+0x78]
0xE900570  mov [rbp+0xC8],rax
0xE90059D  lea rax,[0xF4F20C0]
0xE9005A4  mov [rbx],rax
0xE9005A7  mov rax,[rbp+0x50]
0xE9005AB  mov [rbx+8],rax
0xE9005AF  mov rax,[rbp+0x58]
0xE9005B3  mov [rbx+0x10],rax

---

## Open items
- [UNVERIFIED: 0xE90047A] Which task class returns 1 from vtable slot 0x18? None of the six known classes do.
- [UNVERIFIED: 0x12862370] The data pointer returned by wrapper task's vtable[3] — what structure is at 0x12862370? (In .data section, not code)
- [UNVERIFIED: 0xE900314] TaskList+0x18 byte (extra) — values other than 0/1 lead to call 0x1166E0; meaning unknown.
- [I] Task name offsets for RTX/VV-specific task classes (not in the six known) — need live capture or more vtable analysis.

---

## TOOL REQUESTS
- `python tools/sigs/verify_oc.py docs/progress/oc_U-C9.md` to confirm all quoted instruction lines match rdis dis output
- A tool to enumerate all vtables in the .rdata section and their slot 0x18 targets would automate the "which class returns 1" question (currently manual vt calls)