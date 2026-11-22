## NEXT
DONE

# UNIT U-EC4a — DragonFrameResources field decode (endFrame 0xe9002e0)

Goal: close checklist item C4a. The DFR vector fields +0x290/+0x298/+0x2A0 are proven [V]; the open parts are the "remaining fields" (+0x08/+0x0C/+0x10/+0x18) and "no object size/ctor yet".

## Method / register discipline

`0xe9002e0(taskList* rcx, args* rdx)` [V: BGFX_MAP 6cx/1081; pre/0xe9002e0.md]. rdi is REASSIGNED inside the function:
- `0xe90032a  mov r15,rdx` then `0xe90032d  mov rdi,rcx` → rdi = taskList (NOT DragonFrameResources) until ...
- `0xe900483  mov rdi,[r15+0x20]` → rdi = [args+0x20] = DragonFrameResources*

Every `[rdi+off]` before 0xe900483 is a taskList field; every `[rdi+off]` from 0xe900483 on is a DragonFrameResources field (rdi is not reassigned again).

## Answer table — DragonFrameResources fields (one row per distinct offset, all sites listed)

| offset | size | access | verbatim `0xRVA  instr` proof sites | meaning | tag |
|---|---|---|---|---|---|
| +0x290 | 8 | R/W | `0xe900827  sub rsi,[rdi+0x290]`; `0xe900913  mov r13,[rdi+0x290]`; `0xe9009ff  mov r13,[rdi+0x290]`; `0xe900a71  mov r13,[rdi+0x290]`; `0xe900aba  mov [rdi+0x290],r14`; `0xe900b2d  mov [rdi+0x290],r14` | vector begin: base of the element storage; `sub rsi,[rdi+0x290]` then `sar rcx,4` at 0xe900827-0xe900831 yields the element index; rewritten with the new base after realloc | [V] |
| +0x298 | 8 | R/W | `0xe9004aa  mov r15,[rdi+0x298]`; `0xe9004c5  add qword ptr [rdi+0x298],0x10`; `0xe90091a  mov rax,[rdi+0x298]`; `0xe90096f  mov rax,[rdi+0x298]`; `0xe900a16  mov rsi,[rdi+0x298]`; `0xe900acc  mov [rdi+0x298],rax`; `0xe900b3f  mov [rdi+0x298],rax` | vector end/write cursor: advanced by 0x10 per push via `add qword ptr [rdi+0x298],0x10` at 0xe9004c5; compared to capacity at 0xe9004b1 | [V] |
| +0x2A0 | 8 | R/W | `0xe9004b1  cmp r15,[rdi+0x2A0]`; `0xe900a7f  mov rdx,[rdi+0x2A0]`; `0xe900add  mov [rdi+0x2A0],rax`; `0xe900b50  mov [rdi+0x2A0],rax` | vector capacity end: `cmp r15,[rdi+0x2A0]` at 0xe9004b1 tests end==capacity (realloc path at 0xe900824); new capacity stored at 0xe900add/0xe900b50 | [V] |

The three qwords are {begin, end/cursor, capacity} of a `vector<shared_ptr<Task>>` with 0x10-byte elements (`{task object*, shared_ptr control block*}`): the 0x10 stride is shown by 0xe9004c5, the push stores `{task object*, ctrl}` at [end] then [end+8] and advances end, and capacity growth reallocates and rewrites all three slots (0xe900aba/0xe900acc/0xe900add). The "shared_ptr" element type is [I] from the control-block refcount ops (`lock dec [rbx+8]`/`[rbx+0xC]`) elsewhere in the function; everything else above is [V].

## "Remaining fields" +0x08/+0x0C/+0x10/+0x18 — NOT DragonFrameResources

oc_U-C4a attributed +0x08 q, +0x0C dword, +0x10 q, +0x18 byte to rdi/DragonFrameResources, but rdi = taskList until 0xe900483 (and rdi walks taskList entries/control blocks in the helpers), so none of them is a DragonFrameResources field and none gets a DFR table row:
- +0x18 byte: `0xe900314  movzx eax,byte ptr [rcx+0x18]` — rcx = taskList at entry; state byte, 1 → early path, else `call 0x1166E0` at 0xe900325. [?] for DFR; taskList field.
- +0x08 q: `0xe90039e  mov rdx,[rdi+8]` / `0xe9003e3  mov rdx,[rdi+8]` — rdi = taskList → [rdi]/[rdi+8] is the begin/end pair used as `([rdi+8]-[rdi])>>7` entry count. [?] for DFR; taskList field.
- +0x0C dword: `0xe900e67  lock dec dword ptr [rdi+0xC]` — cleanup loop, rdi = [rsi+8] = shared_ptr control block*; [rdi+0xC] is the weak refcount. [?] for DFR; shared_ptr field.
- +0x10 q: `0xe901239  mov rbx,[rdi+0x10]` / `0xe901319  mov rbx,[rdi+0x10]` — entry-destroy helpers (0xe901200/0xe9012e0), rdi walks taskList entries; [rdi+0x10] is the entry's shared_ptr. [?] for DFR; taskList-entry field.

No instruction shows +0x08/+0x0C/+0x10/+0x18 through a DragonFrameResources pointer; BGFX_MAP 6cx/1081 describes them as taskList entry fields (Entry size 0x80, [rcx+0x18] byte = state).

## Object size — not determined

Highest DragonFrameResources offset touched: +0x2A0, accessed as qword (`0xe900add  mov [rdi+0x2A0],rax`, `0xe900b50  mov [rdi+0x2A0],rax`) → object size ≥ 0x2A8 [I] (lower bound only; oc_U-C4a2: DFR embedded at owner+0x268, so owner ≥ 0x510, still a lower bound).
No instruction in 0xe9002e0 shows total object size: no memset, `operator new`, or constructor call for the DragonFrameResources object; it is passed by reference (args+0x20). Exact size: [?] unknown.

## Constructor — not found

endFrame performs no allocation, memset, or constructor call for DragonFrameResources; it only pushes `{task object*, control block}` pairs into the embedded vector. oc_U-C4a2's search for the owner-object constructor (owner = FrameContext+0x18, DFR at owner+0x268) is blocked: FrameContext/owner/BgfxFrameBuilder constructors not located. Constructor: [?] unknown.

[UNVERIFIED: 0xe9002e0 DragonFrameResources object size and constructor — DFR passed by reference (args+0x20 → rdi via `0xe900483  mov rdi,[r15+0x20]`); endFrame performs no allocation/memset/ctor of the object; owner-constructor search blocked in oc_U-C4a2]

## CLOSES?

NO. The DragonFrameResources vector fields +0x290/+0x298/+0x2A0 (begin/end/capacity; 0x10 element stride) are proven [V], and the "remaining fields" +0x08/+0x0C/+0x10/+0x18 are shown to be taskList/shared_ptr fields, not DragonFrameResources fields. The single pending part "no object size/ctor yet" is NOT proven: no [V] row exists for DragonFrameResources object size or constructor. Single blocking fact: endFrame (0xe9002e0) borrows DragonFrameResources by reference (args+0x20 → rdi at 0xe900483) and contains no object allocation, memset, or constructor call for it, and oc_U-C4a2's owner-constructor search is blocked (FrameContext/owner/BgfxFrameBuilder constructors not located), so object size and constructor remain undetermined.

## TOOL REQUESTS
- None; all data from pre/0xe9002e0.md (rdis listing), oc_U-C4a.md, oc_U-C4a2.md, BGFX_MAP.md section 6cx.
