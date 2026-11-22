## NEXT
DONE

# Unit U-EL1q — Record table field layouts (checklist L1q pending part: 0x130 framebuffer-texture record)

Goal (checklist L1q): decode field layouts of the 0x78/0x80/0x130/0x68 record tables. Texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 done per 6au — not this unit. Done previously (oc_U-EL1q_r1.md .. r5.md): 0x78 index-buffer records at renderer+0x93A178 [V], 0x80 vertex-buffer records at renderer+0x9B2178 [V], 0x68 framebuffer-window records at renderer+0xC97698 [V] (128 entries).

Scope of this file: only the pending part — the 0x130 framebuffer-texture record whose pointer is held in the guard slot at ctx+0xA32178+handle*0x78 (createFrameBuffer 0xe816380). Fields +0x01..+0x12F to decode. Records are separate allocations from sub_e8360f0 (bump arena ctx+0x238+8, align 0x10). ctx = renderer-context base = qword at [0x12BB4910] (oc_U-EL7e Table 3 `mov rax,[0x12BB4910]`; live-verified). All RVAs image-relative. Instruction quotes verbatim from rdis `dis` of the input listings in docs/progress/pre/_tmp_el1q_*.txt (read fully, not regenerated). Meaning column: '-' unless an instruction/string shows it; live values are observations for one instance, not proof of constants. Tags: [V] = seen in disassembly (RVA cited); [V live] = livemem observation, exact command cited.

## New angles tried and failed (RETRY #3)

1. Other callers via rdis `xr`/`callers` (r4/r5, not redone per instructions): createFrameBuffer 0xe816380 is stored at vtable entries 0xF4ED3F8 (base vtable 0xF4ED2D0, slot 37) and 0xF4EEFA8 (RTX vtable 0xF4EEE80, slot 37); `xr` on both entries: 0 xrefs; callers use indirect `call qword ptr [reg+0x128]` which neither tool can enumerate. No xrefs to e816380 at all (vtable-dispatched). Runtime size rbx=[r9+8], source r14=[r9], and any later field writers are unobservable statically.
2. vt/vcalls: not applicable — the 0x130 record is a plain data struct (no vtable, no virtual calls); sub_eec6ec0 is an import thunk, not chased per orchestrator hint.
3. descscan2.py: broken (TypeError, _tmp_el1q_descscan2.txt); rdis `rw`/`struct` not applicable to this plain data struct.
4. Static writers for record bytes +0x01..+0x12F: none exist. Full createFrameBuffer 0xe816380 listing read (_tmp_el1q_createfb.txt, 0xe816380..0xe8165ff): it reads record+0x00/+0x10/+0x1C and performs ONE bulk copy (`0xe81652f  call 0xEEC6EC0`) to an unresolved external destination; it writes NO record byte. Destroyer sub_e80ef60 touches only guard-slot fields; sub_e92a8f0 reads slot-resource object fields ([rsi+0x7C], [rsi+0x128], [rsi+0x178], [rsi+0x180], [rsi+0xC8], [rsi+0xD8]...), not record fields. Imm scan for table base 0xA32178: 2 hits only (destroy stub e815fc0 `add rcx,0xA32178`, createFrameBuffer e816380 `add rdi,0xA32178`); both stride 0x78 for the guard-slot array.
5. Orchestrator-hint livemem reads (read-only, brief §30; game running pid 18956, I did not start it; 3 of 12 calls used):
   - `python tools/sigs/livemem.py ptr @0x12BB4910 1` → +0x0  0x000005314A010000  ptr (ctx; same heap base as r4/r5 — the game was NOT restarted, so old record addresses from r4/r5 are stale and were NOT reused).
   - `python tools/sigs/livemem.py read 0x5314AA32178 0x180` (ctx+0xA32178 = 0x5314AA32178, 8 guard slots at stride 0x78) → ALL ZEROS: slot+0x00 record pointers all NULL, no framebuffer-texture record exists in this instance right now. The hint's planned reads of 2-3 records at stride 0x130 cannot execute — there are no live records to read.
   - r4's three record snapshots from the same pid (records then at p0=0x172B581F0, p1=0x172B55AC0, p2=0x1B62E37F0 via `python tools/sigs/livemem.py read <addr> 0x130`) are stale instance observations; the guard slots that held them are now zero. Kept below as [V live] observations (that instance only, not constants), not as a closure path.

## PROVEN [V] — createFrameBuffer 0xe816380 and the copy (verbatim from _tmp_el1q_createfb.txt)

- `0xe816390  mov rdi,rcx` — rdi = this = renderer object = ctx = qword at [0x12BB4910].
- `0xe816393  movzx ecx,dx` / `0xe816396  imul rbp,rcx,0x78` / `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` — guard slot at ctx+0xA32178+handle*0x78; if slot+0x00 (record pointer) is 0 the function returns (`0xe8163a3  je 0xE816567`) — create runs only on an empty slot.
- `0xe81648f  mov r14,[r9]` — source r14 = qword at [r9] (createFrameBuffer arg 4 = caller's buffer pointer); `0xe816521  test r14,r14` / `0xe816524  je short 0xE816534` — copy skipped when source NULL.
- `0xe816492  mov ebx,[r9+8]` then `0xe81652c  mov r8,rbx` — size rbx = dword at [r9+8], zero-extended into r8 (runtime block byte count, unobservable statically because the caller is indirect).
- `0xe8164bb  call 0xE8360F0` (rcx=[rdi+0x238]+8 arena object, rdx=&[rsp+0x48] out-param, r8=rbx=[r9+8] size, r9d=0x10 align) — sub_e8360f0 bump-allocates [r9+8] bytes aligned 0x10; the allocated pointer is stored at out-param+0x00 (`0xe836308  mov [rsi],rcx` in sub_e8360f0), so `0xe8164c4  mov rax,[rsp+0x48]` loads rax = RECORD POINTER (key correction vs r3: rax is the record, not an owner object). The allocator writes only its out-param stack block; no located instruction writes any byte of the allocated record itself. Record size 0x130 per checklist L1q (input data); allocation size is the runtime [r9+8].
- Record field reads on the fresh record (rax = record ptr):
  - `0xe8164dc  mov r15,[rax]` — qword read at record+0x00; r15 passed as r9 to device method `0xe81654f  mov rax,[rax+0x78]` / `0xe816560  call qword ptr [0xF99FFA0]` ([data_f99ffa0] = sub_eea6040); role of +0x00 not shown by any instruction.
  - `0xe8164ce  mov rcx,[rax+0x10]` — qword read at record+0x10; memcpy-destination base component (`0xe8164d2  add rcx,rsi`).
  - `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164df  cmove r12,rcx` — dword type tag compared against 2; r12 = (record+0x1C==2) ? record+0x10+rsi : 0, where rsi = dword at [rsp+0x58] (`0xe8164c0  mov esi,[rsp+0x58]`) = allocator-provided runtime size, not a constant.
- `0xe816517  add rdi,rbp` / `0xe81651a  add rdi,0xA32178` / `0xe816534  mov rdx,[rdi]` — creator re-reads guard slot [ctx+0xA32178+handle*0x78]+0x00 to get the record pointer back.
- `0xe816526  mov rcx,r12` / `0xe816529  mov rdx,r14` / `0xe81652c  mov r8,rbx` / `0xe81652f  call 0xEEC6EC0` — import-thunk memcpy/memmove: 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` (rcx=dst rdx=src r8=size per orchestrator hint; thunk target not chased). Copies [r9+8] bytes from [r9] into dst r12 — an EXTERNAL address (record+0x10 + allocator size when record+0x1C==2, else 0), NOT a fixed record offset and NOT a record-field store; path inert when record+0x1C==0 (all observations) and skipped when r14==0.
- No store of the record pointer into the guard slot appears in the createFrameBuffer listing (slot write is done by the indirect vtable-slot-37 caller after the call returns — caller unlocatable, see angle 1). Note: +0x0C/+0x58 proven reads in the destroyer are GUARD-SLOT fields (slot type tag compared against 0xB, slot resource), NOT record fields — they are tabled below as slot rows.

## Field table — 0x130 framebuffer-texture record (record pointer held at guard slot [ctx+0xA32178+handle*0x78]+0x00)

| name | offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag |
|------|--------|------|------|-------------------------------|---------|-----|
| framebuffer-texture record +0x00 | +0x00 | 8 | createFrameBuffer 0xe816380 (rax = record ptr = sub_e8360f0 out-param [rsp+0x48]) | `0xe8164dc  mov r15,[rax]` | qword read at record+0x00; r15 passed as r9 to device call `0xe81654f  mov rax,[rax+0x78]` / `0xe816560  call qword ptr [0xF99FFA0]`; live observation: 0x000007FBA1D2E100 stable shared ptr across r4's 3 snapshots (`read 0x172B581F0 0x130` / `read 0x172B55AC0 0x130` / `read 0x1B62E37F0 0x130`); role of +0x00 not shown by any instruction | [V] |
| framebuffer-texture record +0x10 | +0x10 | 8 | createFrameBuffer 0xe816380 | `0xe8164ce  mov rcx,[rax+0x10]` | qword read at record+0x10; used as memcpy-destination base component (`0xe8164d2  add rcx,rsi`; r12 = record+0x10+rsi when record+0x1C==2); live: 0 in all 3 r4 snapshots | [V] |
| framebuffer-texture record +0x1C | +0x1C | 4 | createFrameBuffer 0xe816380 | `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164df  cmove r12,rcx` | dword type tag compared against 2; selects memcpy path r12 = record+0x10+rsi else 0; live: 0 in all 3 r4 snapshots (copy path inert) | [V] |
| record allocation | alloc size=[r9+8] bytes | — | createFrameBuffer 0xe816380 → sub_e8360f0 | `0xe8164bb  call 0xE8360F0` / `0xe836308  mov [rsi],rcx` / `0xe8164c4  mov rax,[rsp+0x48]` | sub_e8360f0 bump-allocates [r9+8] bytes aligned 0x10; allocated pointer stored at out-param+0x00 → rax = record ptr; the record memory itself is not written by any located instruction | [V] |
| memcpy source r14 | src=[r9] | — | createFrameBuffer 0xe816380 | `0xe81648f  mov r14,[r9]` / `0xe816521  test r14,r14` / `0xe816524  je short 0xE816534` | source pointer = qword at [r9] (caller's buffer, arg 4); copy skipped when NULL | [V] |
| memcpy size rbx | size=[r9+8] | — | createFrameBuffer 0xe816380 | `0xe816492  mov ebx,[r9+8]` / `0xe81652c  mov r8,rbx` | size = dword at [r9+8] zero-extended into r8 (runtime byte count of caller's block; caller indirect, unobservable statically) | [V] |
| memcpy destination r12 | copy dst r12 (unresolved record offset) | — | createFrameBuffer 0xe816380 | `0xe816526  mov rcx,r12` / `0xe81652f  call 0xEEC6EC0` | r12 = (record+0x1C==2) ? record+0x10+rsi : 0; record-relative offset NOT resolvable statically (rsi = dword at [rsp+0x58] is allocator-provided runtime size; record+0x10 is itself a record field); writes to an external address, not a record-field store | [V] |
| attachment/record-block memcpy (only record-block write) | size=[r9+8] bytes | — | createFrameBuffer 0xe816380 | `0xe81652f  call 0xEEC6EC0` | 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` import thunk = memcpy/memmove-style (rcx=dst rdx=src r8=size per orchestrator hint); copies [r9+8] bytes from [r9] into dst r12; not a record-field write | [V] |
| guard slot +0x00 (record pointer) | slot +0x00 | 8 | createFrameBuffer 0xe816380 / destroyer sub_e80ef60 | `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` / `0xe816534  mov rdx,[rdi]` / `0xe80ef70  mov rdx,[rcx]` | qword at slot [ctx+0xA32178+handle*0x78]+0x00 = record pointer | [V] |
| guard slot +0x0C | slot +0x0C | 4 | destroyer sub_e80ef60 | `0xe80ef7c  mov r8d,[rcx+0xC]` / `0xe80ef82  cmp r8d,0xB` | dword slot type tag compared against 0xB — SLOT field, NOT a record field | [V] |
| guard slot +0x58 | slot +0x58 | 8 | destroyer sub_e80ef60 | `0xe80efb4  mov rdx,[rcx+0x58]` / `0xe80efbe  call 0xE92A8F0` | qword slot resource released via sub_e92a8f0 — SLOT field, NOT a record field | [V] |
| guard slot clears | slot +0x00/+0x58/+0x5F/+0x68 | 8 | destroyer sub_e80ef60 | `0xe80f259  mov qword ptr [rcx],0` / `0xe80f260  mov qword ptr [rcx+0x68],0` / `0xe80f268  mov qword ptr [rcx+0x58],0` / `0xe80f270  mov qword ptr [rcx+0x5F],0` | slot fields cleared on destroy — SLOT fields, NOT record bytes | [V] |

## [V live] observations (stale r4 instance, pid 18956; records since destroyed, guard slots now all zero)

| name | offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag |
|------|--------|------|------|-------------------------------|---------|-----|
| framebuffer-texture record +0x20 | +0x20 | 8 | livemem read (r4) | — | qword 0x000007FBA1D2E0D8 stable shared ptr across 3 snapshots (`read 0x172B581F0 0x130` / `read 0x172B55AC0 0x130` / `read 0x1B62E37F0 0x130`); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x40 | +0x40 | 4 | livemem read (r4) | — | dword 1 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x48 | +0x48 | 4 | livemem read (r4) | — | dword 2 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x50 | +0x50 | 8 | livemem read (r4) | — | qword 0x000007FFBDB76198 stable shared ptr across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xA8 | +0xA8 | 8 | livemem read (r4) | — | qword 0x000000000653A400 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xB0 | +0xB0 | 8 | livemem read (r4) | — | qword = record's own address (self pointer) in all 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xB8 | +0xB8 | 4 | livemem read (r4) | — | dword 1 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xD8 | +0xD8 | 8 | livemem read (r4) | — | qword 0x000007FBA1D2E1C0 stable shared ptr across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xE8 | +0xE8 | 4 | livemem read (r4) | — | dword 0x11000000 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xEC | +0xEC | 4 | livemem read (r4) | — | dword 0x14000001 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xF0 | +0xF0 | 4 | livemem read (r4) | — | dword 1 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xF4 | +0xF4 | 4 | livemem read (r4) | — | dword 1 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xF8 | +0xF8 | 4 | livemem read (r4) | — | dword 1 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x100 | +0x100 | 4 | livemem read (r4) | — | dword 4 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |

Live observations recorded but not tabled as rows (per-instance values, meaning '-'): +0x58/+0x60/+0x68 vary per record (rec0/rec1: dword 0xFFFFFFFF at +0x58; rec2: qword 0xFFFFFFFFFFFFFFFF at +0x60/+0x68, +0x58 = 0), +0xA0 varies (near-record pointer), +0xBC = 0 in rec0/rec1, dword 0x5C0F3C49 in rec2 only, +0xC0/+0xC8 vary (pointers), +0xE0 varies (dword 8 / 0x20 / 0x40000). All other offsets were 0x00 in all 3 snapshots (value observations with meaning '-', not field layouts and not tied to the copy).

## Unproven

No instruction writes any record byte at +0x01..+0x0F, +0x11..+0x1F, +0x21..+0x12F (other than the +0x10/+0x1C reads above). createFrameBuffer 0xe816380 writes the record only via the external memcpy at unresolved dst r12; live instances have record+0x1C==0 so r12==0 and the copy path is inert (r14==0 also skips it). No other located function writes any record byte: the destroyer touches only guard-slot fields; sub_e80ef60's slot clears are slot fields; sub_e92a8f0 reads slot-resource object fields. The copy size rbx=[r9+8] and source r14=[r9] are runtime values of the indirect caller and cannot be obtained statically or from read-only livemem (no mid-call register access). descscan2.py is broken; vt/vcalls and rdis rw/struct do not apply to this plain data struct.

## CLOSES?

NO — blocking fact: no located instruction writes any byte of the 0x130 framebuffer-texture record at +0x01..+0x12F, so those offsets have no [V] row and cannot be proven. The only record-field reads are +0x00 (`0xe8164dc  mov r15,[rax]`), +0x10 (`0xe8164ce  mov rcx,[rax+0x10]`), +0x1C (`0xe8164d8  cmp dword ptr [rax+0x1C],2`); the only record-block write is the memcpy `0xe81652f  call 0xEEC6EC0` (rcx=dst rdx=src r8=size) whose record-relative destination r12 = (record+0x1C==2) ? record+0x10+[rsp+0x58] : 0 is not statically resolvable and is inert in every observed instance. Proven copy facts: size rbx=[r9+8] (`0xe816492  mov ebx,[r9+8]`), source r14=[r9] (`0xe81648f  mov r14,[r9]`). Livemem re-read confirms ctx = 0x000005314A010000 (`ptr @0x12BB4910 1`) but all guard slots at ctx+0xA32178 are zero (`read 0x5314AA32178 0x180` → 8×0x78 slots all 0x00), so no live records exist in this instance to read; r4's three record snapshots are stale. Until a live instance has records (or a writer function is located), the 0x130 record layout cannot be closed.

## TOOL REQUESTS

None — all data came from the precomputed input listings, rdis dis/xr/ptr, and livemem status/ptr/read calls already made; no helper script written.
