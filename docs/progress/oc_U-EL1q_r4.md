## NEXT
DONE

# Unit U-EL1q — Record table field layouts (checklist L1q pending part: 0x130 framebuffer-texture record)

Goal (checklist L1q): decode field layouts of the 0x78/0x80/0x130/0x68 record tables. Texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 done per 6au — not this unit. Done previously (oc_U-EL1q_r1.md): 0x78 index-buffer records at renderer+0x93A178 [V], 0x80 vertex-buffer records at renderer+0x9B2178 [V], 0x68 framebuffer-window records at renderer+0xC97698 [V] (128 entries).

Pending part (this unit): 0x130 framebuffer-texture record whose pointer is held in the guard slot at ctx+0xA32178+handle*0x78 (createFrameBuffer 0xe816380; ctx = renderer object = qword at 0x12BB4910, live-verified by the orchestrator 2026-11-21 and by sub_e80ef60 reading [0x12BB4910] directly). Fields +0x01..+0x12F to decode. Records are separate 0x130-byte allocations from sub_e8360f0 (bump arena ctx+0x238+8, align 0x10).

Input data used (all read fully, NOT regenerated per brief rule): docs/progress/pre/_tmp_el1q_createfb.txt (createFrameBuffer 0xe816380 full listing 0xe816380..0xe817180), _tmp_el1q_e80ef60.txt (destroyer sub_e80ef60), _tmp_el1q_eec6ec0.txt (import thunk 0xEEC6EC0), _tmp_el1q_e8360f0.txt (allocator sub_e8360f0 complete), _tmp_el1q_e92a8f0.txt (sub_e92a8f0), _tmp_el1q_descscan2.txt (descscan2.py broken: TypeError), _tmp_el1q_imm_a32178.txt + _tmp_el1q_imm_a32178b.txt (imm scan for 0xA32178: 2 hits only).

## NEW-ANGLE ATTEMPTS THAT FAILED (this attempt)

1. Static writers for record bytes +0x01..+0x12F: none exist. Imm scan for table base 0xA32178 has only 2 hits (`e815fc0+0x13e add rcx,0xA32178` destroy stub and `e816380+0x19a add rdi,0xA32178` createFrameBuffer). sub_e80ef60 destroyer touches only guard-slot fields (+0x00 record ptr, +0x0C type tag, +0x58 resource, +0x5F, +0x68 — all SLOT fields, cleared on destroy); sub_e92a8f0 reads the slot-resource object fields (+0x7C, +0x128, +0x178, +0x180, +0xC8, +0xD8...), not record fields. createFrameBuffer 0xe816380 reads record fields +0x00/+0x10/+0x1C but writes NO record byte: it memcpys into *(record+0x10)+[rsp+0x58], an offset that is not record-relative and not statically resolvable (see below). No other located function reads or writes any record byte.

2. Caller of createFrameBuffer (needed for the runtime size rbx=[r9+8]): not locatable. `rdis ptr 0xe816380` finds 0xE816380 stored at vtable entries `0xF4ED3F8` (base vtable 0xF4ED2D0, slot 37) and `0xF4EEFA8` (RTX vtable 0xF4EEE80, slot 37 — RTX inherits the base slot). `rdis xr 0xF4ED3F8` and `rdis xr 0xF4EEFA8`: 0 xrefs each — callers use `call qword ptr [reg+0x128]` (register+imm indirect), which neither `xr` nor `callers` can enumerate. No xrefs to e816380 at all (vtable-dispatched). So the runtime size [r9+8] and source [r9] are unobservable statically, and read-only livemem cannot read registers mid-call.

3. descscan2.py broken (TypeError); rdis rw/struct not applicable; record is a plain data struct (no vtable/vcalls).

## PROVEN [V] — createFrameBuffer 0xe816380 and the allocator (verbatim from the listings)

- `0xe816390  mov rdi,rcx` — rdi = this = renderer object = ctx = [0x12BB4910] (same +0x19F58 resource-table usage as the destroyer, which reads [0x12BB4910] directly).
- `0xe816396  imul rbp,rcx,0x78` / `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` — guard slot at ctx+0xA32178+handle*0x78; slot+0x00 = record pointer qword (existence test).
- `0xe8164bb  call 0xE8360F0` (rcx=[rdi+0x238]+8 arena object, rdx=&[rsp+0x48] out-param, r8=rbx=[r9+8] size, r9d=0x10 align) — sub_e8360f0 bump-allocates [r9+8] bytes aligned 0x10; stores the allocated pointer at outParam+0x00 (`e836308  mov [rsi],rcx` and the `e83636d`/`e8363d3`/`e8363f7` variants) and {allocatedPtr,size} at outParam+0x10 (`e83630f  movups xmm0,[rbp]` / `e836317  movups [rsi+0x10],xmm0`, per sub_e836640's out-block where +0x10 = allocated pointer). So after the call: [rsp+0x48] = record ptr, [rsp+0x58] = low32(record ptr).
- Record field reads on the fresh record (rax = [rsp+0x48] = record ptr):
  - `0xe8164dc  mov r15,[rax]` — qword read at record+0x00; r15 later passed as r9 to device method `e81654f  mov rax,[rax+0x78]` / `e816560  call qword ptr [0xF99FFA0]`; role of +0x00 not shown by any instruction.
  - `0xe8164ce  mov rcx,[rax+0x10]` — qword read at record+0x10; memcpy-destination base (`0xe8164d2  add rcx,rsi`).
  - `0xe8164d8  cmp dword ptr [rax+0x1C],2` — dword read at record+0x1C compared against 2 (type tag); `0xe8164d5  xor r12d,r12d` / `0xe8164df  cmove r12,rcx` → r12 = ([rax+0x1C]==2) ? [rax+0x10]+rsi : 0, rsi = [rsp+0x58] = low32(record ptr) — a runtime value, not a constant.
- `0xe81648f  mov r14,[r9]` — src r14 = qword at [r9] (createFrameBuffer arg 4 = caller's buffer ptr); null-checked `0xe816521  test r14,r14` / `0xe816524  je short 0xE816534`.
- `0xe816492  mov ebx,[r9+8]` then `0xe81652c  mov r8,rbx` — size rbx = dword at [r9+8] zero-extended into r8 (runtime record-block byte count).
- `0xe816526  mov rcx,r12` / `0xe816529  mov rdx,r14` / `0xe81652c  mov r8,rbx` / `0xe81652f  call 0xEEC6EC0` — import-thunk memcpy/memmove: 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` (rcx=dst rdx=src r8=size per orchestrator hint; do not chase the thunk target). Copies [r9+8] bytes from [r9] into *(record+0x10)+low32(recordPtr) when record+0x1C==2, else dst=0 — NOT a record-relative store, and not taken at all when r14==0.
- `0xe816517  add rdi,rbp` / `0xe81651a  add rdi,0xA32178` / `0xe816534  mov rdx,[rdi]` — creator re-reads guard slot [ctx+0xA32178+handle*0x78]+0x00 to get the record pointer back.
- (Note: no store of the record pointer into the guard slot appears in the createFrameBuffer listing; sub_e8360f0 receives only the arena object and the out-param — the slot write path is not visible in this unit's listings, but the live table below confirms slot+0x00 holds the record pointer.)

## LIVE READS [V live] (static analysis cannot settle the layout; game pid 18956 was already running — I did not start it)

- `python tools/sigs/livemem.py status` → pid 18956, base 0x7ff699000000, version OK 1.26.62.01.
- `python tools/sigs/livemem.py ptr @0x12BB4910 1` → +0x0  0x000005314A010000  ptr (ctx = renderer object, heap pointer; re-read each run).
- `python tools/sigs/livemem.py read 0x5314AA42178 0x3c0` (ctx+0xA32178 = 0x5314AA42178; first attempt at the mis-added 0x5314AA32178 returned all zeros — corrected address below) → guard slots 0-7, stride 0x78:
  - slot0+0x00 = 0x00000172B581F0 (record pointer p0); slot1+0x00 = 0x00000172B55AC0 (p1); slot2+0x00 = 0x000001B62E37F0 (p2); slots 3-7 empty (+0x00 = 0).
- `python tools/sigs/livemem.py read 0x172B581F0 0x130` → record 0 (p0)
- `python tools/sigs/livemem.py read 0x172B55AC0 0x130` → record 1 (p1)
- `python tools/sigs/livemem.py read 0x1B62E37F0 0x130` → record 2 (p2)
  Calls used: 7 of 12 max; all reads ≤ 0x400 bytes.

Live findings:
- Records are NOT stride-0x130 contiguous (p0→p1 = 0x2730 bytes apart; p2 is in a different heap segment) — record pointers come from slot+0x00 only. The orchestrator's "read consecutive records at stride 0x130" plan does not apply; bump-arena contiguity does not hold across handles.
- All 3 snapshots: +0x10 = 0 and +0x1C = 0 — these are default/empty records, so the type-2 memcpy path (cmove r12,rcx when +0x1C==2) is NOT taken (r12 = 0) and no record byte is written by the copy in the current instance.
- Stable across all 3 snapshots: +0x00 = 0x000007FBA1D2E100 (stable shared ptr), +0x20 = 0x000007FBA1D2E0D8 (stable shared ptr), +0x40 = 1, +0x48 = 2, +0x50 = 0x000007FFBDB76198 (stable shared ptr), +0xA8 = 0x000000000653A400, +0xB8 = 1, +0xD8 = 0x000007FBA1D2E1C0 (stable shared ptr), +0xE8 = 0x11000000, +0xEC = 0x14000001, +0xF0 = 1, +0xF4 = 1, +0xF8 = 1, +0x100 = 4.
- Varies per record: +0x58/+0x60/+0x68 (rec0/rec1: dword 0xFFFFFFFF at +0x58; rec2: qwords 0xFFFFFFFFFFFFFFFF at +0x60/+0x68, +0x58 = 0), +0xA0 (near-record ptr: p0-0x30, p1+0x70, p2-0x30), +0xB0 (self pointer = the record's own address), +0xC0, +0xC8, +0xE0 (8 / 0x20 / 0x40000), +0xBC (0x5C0F3C49 in rec2 only).
- All other offsets (+0x01..+0x0F, +0x11..+0x1F, +0x21..+0x27, +0x29..+0x2F, +0x31..+0x3F, +0x51..+0x57, +0x59..+0x5F, +0x61..+0x9F, +0xA1..+0xA7, +0xA9..+0xAF, +0xB1..+0xB7, +0xB9..+0xBF, +0xC1..+0xC7, +0xC9..+0xCF, +0xD1..+0xD7, +0xD9..+0xDF, +0xE1..+0xE7, +0xED..+0xEF, +0xF9..+0xFF, +0x101..+0x12F): 0x00 in all 3 snapshots.
- None of these live values is tied to the copy (copy size rbx=[r9+8] and dst offset are runtime-unresolvable; see CLOSES?). Meanings are not shown by any live data.

## Field table (0x130 framebuffer-texture record at pointer held in guard slot ctx+0xA32178+handle*0x78)

| name | offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag |
|------|--------|------|------|-------------------------------|---------|-----|
| framebuffer-texture record +0x00 | +0x00 | 8 | createFrameBuffer 0xe816380 (rax = record ptr from sub_e8360f0 out-param [rsp+0x48]) | `0xe8164dc  mov r15,[rax]` | qword read at record+0x00; r15 passed as r9 to device method `e81654f  mov rax,[rax+0x78]` / `e816560  call qword ptr [0xF99FFA0]`; live: 0x000007FBA1D2E100 in all 3 snapshots (stable shared ptr); role not shown by any instruction | [V] |
| framebuffer-texture record +0x10 | +0x10 | 8 | createFrameBuffer 0xe816380 | `0xe8164ce  mov rcx,[rax+0x10]` | qword read at record+0x10; used as memcpy-destination base (`0xe8164d2  add rcx,rsi`); live: 0 in all 3 snapshots (default/empty record) | [V] |
| framebuffer-texture record +0x1C | +0x1C | 4 | createFrameBuffer 0xe816380 | `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164df  cmove r12,rcx` | dword type tag compared against 2; selects memcpy-destination path r12 = [rax+0x10]+rsi else 0; live: 0 in all 3 snapshots | [V] |
| attachment-descriptor memcpy (the only record-block write) | copy dst = *(record+0x10)+low32(recordPtr) when +0x1C==2, else 0 — no fixed record offset | [r9+8] | createFrameBuffer 0xe816380 | `0xe81652f  call 0xEEC6EC0` (`0xe816526  mov rcx,r12`, `0xe816529  mov rdx,r14`, `0xe81652c  mov r8,rbx`) | 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` import thunk (rcx=dst rdx=src r8=size); copies [r9+8] bytes from [r9] into the record block; targets *(record+0x10)+low32(recordPtr), an external/unresolved offset — not a record field write; skipped when r14==0 (`0xe816521  test r14,r14` / `0xe816524  je short 0xE816534`) | [V] |
| memcpy source r14 | src = [r9] | 8 | createFrameBuffer 0xe816380 | `0xe81648f  mov r14,[r9]` | source pointer = qword at [r9] (caller's buffer, arg 4); null-checked at `0xe816521` | [V] |
| memcpy size rbx | size = [r9+8] | 4 | createFrameBuffer 0xe816380 | `0xe816492  mov ebx,[r9+8]` / `0xe81652c  mov r8,rbx` | size = dword at [r9+8] zero-extended into r8 (runtime byte count; unobservable — caller not locatable, see failed angles) | [V] |
| guard slot +0x00 (record pointer) | slot +0x00 | 8 | createFrameBuffer 0xe816380 / destroyer sub_e80ef60 / live table | `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` / `0xe816534  mov rdx,[rdi]` / `0xe80ef70  mov rdx,[rcx]` | qword at slot [ctx+0xA32178+handle*0x78]+0x00 = record pointer; live: slot0 = 0x00000172B581F0, slot1 = 0x00000172B55AC0, slot2 = 0x000001B62E37F0 | [V] |
| guard slot +0x0C | slot +0x0C | 4 | destroyer sub_e80ef60 | `0xe80ef7c  mov r8d,[rcx+0xC]` / `0xe80ef82  cmp r8d,0xB` | dword type tag compared against 0xB; SLOT field, NOT a record field | [V] |
| guard slot +0x58 | slot +0x58 | 8 | destroyer sub_e80ef60 | `0xe80efb4  mov rdx,[rcx+0x58]` / `0xe80efbe  call 0xE92A8F0` | qword slot resource released via sub_e92a8f0; SLOT field, NOT a record field | [V] |
| guard slot clears | slot +0x00/+0x58/+0x5F/+0x68 | 8 | destroyer sub_e80ef60 | `0xe80f259  mov qword ptr [rcx],0` / `0xe80f260  mov qword ptr [rcx+0x68],0` / `0xe80f268  mov qword ptr [rcx+0x58],0` / `0xe80f270  mov qword ptr [rcx+0x5F],0` | slot cleared on destroy; SLOT fields, NOT record fields | [V] |

## [V live] observations for record-only offsets with no instruction site

Meaning is '-' for all of these (not shown by any instruction or string); values are observations from the 3 snapshots cited above, not proof of a constant:
- +0x20: qword 0x000007FBA1D2E0D8 stable (shared ptr) — `read 0x172B581F0 0x130` / `read 0x172B55AC0 0x130` / `read 0x1B62E37F0 0x130` — [V live]
- +0x40: dword 1 stable — same 3 commands — [V live]
- +0x48: dword 2 stable — same 3 commands — [V live]
- +0x50: qword 0x000007FFBDB76198 stable (shared ptr) — same 3 commands — [V live]
- +0x58: varies (dword 0xFFFFFFFF in rec0/rec1; 0 in rec2; rec2 also has qword -1 at +0x60/+0x68) — same 3 commands — [V live]
- +0x60: varies (0 in rec0/rec1; qword 0xFFFFFFFFFFFFFFFF in rec2) — same 3 commands — [V live]
- +0x68: varies (0 in rec0/rec1; qword 0xFFFFFFFFFFFFFFFF in rec2) — same 3 commands — [V live]
- +0xA0: varies (near-record pointer: p0-0x30, p1+0x70, p2-0x30) — same 3 commands — [V live]
- +0xA8: qword 0x000000000653A400 stable — same 3 commands — [V live]
- +0xB0: qword = record's own address (self pointer) in all 3 snapshots — same 3 commands — [V live]
- +0xB8: dword 1 stable — same 3 commands — [V live]
- +0xBC: 0 in rec0/rec1; dword 0x5C0F3C49 in rec2 — same 3 commands — [V live]
- +0xC0: varies (pointer: 0x00000172B55B90 / 0x00000172C61EC0 / 0x000001C726BC40) — same 3 commands — [V live]
- +0xC8: varies (pointer: 0x00000172B57BA0 / 0x00000172B582C0 / 0x000001C7341360) — same 3 commands — [V live]
- +0xD8: qword 0x000007FBA1D2E1C0 stable (shared ptr) — same 3 commands — [V live]
- +0xE0: varies (dword 8 / 0x20 / 0x40000) — same 3 commands — [V live]
- +0xE8: dword 0x11000000 stable — same 3 commands — [V live]
- +0xEC: dword 0x14000001 stable — same 3 commands — [V live]
- +0xF0: dword 1 stable — same 3 commands — [V live]
- +0xF4: dword 1 stable — same 3 commands — [V live]
- +0xF8: dword 1 stable — same 3 commands — [V live]
- +0x100: dword 4 stable — same 3 commands — [V live]

## Unproven

Every offset not listed above (+0x01..+0x0F, +0x11..+0x1F, +0x21..+0x27, +0x29..+0x2F, +0x31..+0x3F, +0x51..+0x57, +0x59..+0x5F, +0x61..+0x9F, +0xA1..+0xA7, +0xA9..+0xAF, +0xB1..+0xB7, +0xB9..+0xBF, +0xC1..+0xC7, +0xC9..+0xCF, +0xD1..+0xD7, +0xD9..+0xDF, +0xE1..+0xE7, +0xED..+0xEF, +0xF9..+0xFF, +0x101..+0x12F): no instruction touches them; they read 0x00 in all 3 live snapshots (a value observation with meaning '-', not a field layout and not tied to the copy).

## CLOSES?

NO — blocking fact: no instruction writes any record byte at +0x01..+0x12F. createFrameBuffer 0xe816380 only reads record+0x00/+0x10/+0x1C and issues the one bulk copy (`0xe81652f  call 0xEEC6EC0`) into *(record+0x10)+low32(recordPtr) when record+0x1C==2 — an external, record-relative-unresolvable offset; live instances have +0x10=0/+0x1C=0 so the copy path is inert (r12=0), and no record byte is written by it in the current instance. No other function references the table base (imm scan: 2 hits only; e816380 is vtable slot 37 of 0xF4ED2D0/0xF4EEE80, entries 0xF4ED3F8/0xF4EEFA8, `xr` on both entries: 0 xrefs — callers are indirect `call [reg+0x128]`, so the caller and the runtime size rbx=[r9+8] are not locatable statically, and read-only livemem cannot read mid-call registers). Not every pending offset has a [V] row, so the layout cannot be closed from the evidence available to this unit.

## TOOL REQUESTS

None — rdis `dis`/`ptr`/`xr`, the precomputed listings, and `livemem` sufficed; no helper script was written.
