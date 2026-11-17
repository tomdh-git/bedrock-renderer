## NEXT
DONE

# UNIT U-EC4a — DragonFrameResources field decode (endFrame 0xe9002e0)

Goal: close checklist item C4a. +0x298/+0x2A0 vector<shared_ptr<Task>> already found via endFrame/0xe9002e0 (6cx). Pending parts: the "remaining fields" (+0x08 q, +0x0C dword, +0x10 q, +0x18 byte) and "no object size/ctor yet".

## Method / register discipline

0xe9002e0(taskList* rcx, args* rdx) [V: BGFX_MAP 6cx/1081]. At entry rcx = taskList, rdx = args. args+0x20 = DragonFrameResources*.
The listing shows rdi is REASSIGNED:
- `0xe90032d  mov rdi,rcx`  → rdi = taskList (NOT DragonFrameResources) until...
- `0xe900483  mov rdi,[r15+0x20]`  → rdi = [args+0x20] = DragonFrameResources* (r15=args set at `0xe90032a  mov r15,rdx`)

So every `[rdi+off]` access BEFORE 0xe900483 is a taskList field, NOT a DragonFrameResources field. Every `[rdi+off]` access AFTER 0xe900483 IS a DragonFrameResources field. The proven DragonFrameResources fields are +0x290/+0x298/+0x2A0 (rdi = DFR). The +0x08/+0x0C/+0x10/+0x18 attributed to rdi in oc_U-C4a are taskList fields (rdi=taskList at those points) — see uncertain section below.

## Field table — DragonFrameResources (one row per distinct offset, all sites listed)

| offset | size | access | verbatim `0xRVA  instr` proof sites | meaning | tag |
|---|---|---|---|---|---|
| +0x290 | 8 | R/W | `0xe900827  sub rsi,[rdi+0x290]`; `0xe900913  mov r13,[rdi+0x290]`; `0xe9009ff  mov r13,[rdi+0x290]`; `0xe900a71  mov r13,[rdi+0x290]`; `0xe900aba  mov [rdi+0x290],r14`; `0xe900b2d  mov [rdi+0x290],r14` | vector begin — base of the 16-byte `{Task*, control-block*}` element storage (element index = (ptr - begin) >> 4) | [V] |
| +0x298 | 8 | R/W | `0xe9004aa  mov r15,[rdi+0x298]`; `0xe9004c5  add qword ptr [rdi+0x298],0x10`; `0xe90091a  mov rax,[rdi+0x298]`; `0xe90096f  mov rax,[rdi+0x298]`; `0xe900a16  mov rsi,[rdi+0x298]`; `0xe900acc  mov [rdi+0x298],rax`; `0xe900b3f  mov [rdi+0x298],rax` | vector end / write cursor; advanced by 0x10 (16-byte element stride) per pushed task at `0xe9004c5` | [V] |
| +0x2A0 | 8 | R/W | `0xe9004b1  cmp r15,[rdi+0x2A0]`; `0xe900a7f  mov rdx,[rdi+0x2A0]`; `0xe900add  mov [rdi+0x2A0],rax`; `0xe900b50  mov [rdi+0x2A0],rax` | vector capacity end; `cmp r15,[rdi+0x2A0]` tests end==capacity (triggers realloc) | [V] |

Vector<shared_ptr<Task>> at DragonFrameResources+0x290/+0x298/+0x2A0 is now fully decoded: {begin, end/cursor, capacity} qwords, 16-byte (`0x10`) elements `{Task*, shared_ptr control block*}`, stride confirmed by `0xe9004c5  add qword ptr [rdi+0x298],0x10`. Push stores `{object*,ctrl}` at `[end]`/`[end+8]` then advances end (`0xe9004be  mov [r15],r13`; `0xe9004c1  mov [r15+8],rbx`).

## "Remaining fields" — attribution uncertain ([?])

oc_U-C4a lists +0x08 q, +0x0C dword, +0x10 q, +0x18 byte via rdi, but rdi = taskList until `0xe900483`, so these are NOT proven as DragonFrameResources fields:
- +0x18 byte: `0xe900314  movzx eax,byte ptr [rcx+0x18]` — rcx = taskList at function entry; per BGFX_MAP 1081 `[rcx+0x18] byte = state` (taskList entry state, 1 = early path). Tag [?] for DFR.
- +0x08 q: `0xe90039e  mov rdx,[rdi+8]` / `0xe9003e3  mov rdx,[rdi+8]` — rdi = taskList here → taskList end pointer. Tag [?] for DFR.
- +0x0C dword: `0xe900e67  lock dec dword ptr [rdi+0xC]` — rdi = shared_ptr control block at that point (cleanup loop) → ctrl weak refcount. Tag [?] for DFR.
- +0x10 q: `0xe901239  mov rbx,[rdi+0x10]` / `0xe901319  mov rbx,[rdi+0x10]` — in the entry destructor helper (e901200), rdi = taskList entry. Tag [?] for DFR.

These are taskList/shared_ptr fields, not DragonFrameResources fields. No DragonFrameResources meaning is shown by any instruction for them.

## Object size / constructor — [UNVERIFIED]

endFrame receives DragonFrameResources by reference (args+0x20 forwarded; rdx never dereferenced as the object itself in 0xe9002e0). No allocation, `operator new`, `memset`, or ctor call for the DragonFrameResources object appears in `0xe9002e0`. The only allocations in the function are task-entry objects (0x88-byte via `0x1233E1A8`+`0x88`, and 0x98-byte) — not the DFR object. Constructor search was blocked in oc_U-C4a2 ("constructor not found"). Object size: not determinable from endFrame.

`[UNVERIFIED: 0xe9002e0 DragonFrameResources object size and constructor — not in endFrame (passed by ref); ctor search blocked in oc_U-C4a2]`

## Standalone verified instruction lines (claims)

0xe900aba  mov [rdi+0x290],r14
0xe900acc  mov [rdi+0x298],rax
0xe900add  mov [rdi+0x2A0],rax
0xe9004c5  add qword ptr [rdi+0x298],0x10
0xe9004aa  mov r15,[rdi+0x298]
0xe900827  sub rsi,[rdi+0x290]

All copied verbatim from docs/progress/pre/0xe9002e0.md (rdis listing) and match the exe disassembly.

## CLOSES?

NO. The DragonFrameResources vector fields +0x290/+0x298/+0x2A0 (begin/end/capacity, 16-byte stride) are proven [V], and the "remaining fields" +0x08/+0x0C/+0x10/+0x18 are shown to be taskList/shared_ptr fields, not DragonFrameResources fields ([?]). However the single pending part "no object size/ctor yet" is NOT proven: DragonFrameResources object size and constructor are not found (endFrame takes DFR by reference; no allocation/ctor of the object in 0xe9002e0; ctor search blocked). Single blocking fact: no DragonFrameResources constructor or object-size evidence exists in the input data (oc_U-C4a2 blocked on constructor; endFrame performs no DFR allocation/memset).

## TOOL REQUESTS
- None needed for this unit; all data came from precomputed pre/0xe9002e0.md, oc_U-C4a.md, oc_U-C4a2.md, BGFX_MAP.md.
