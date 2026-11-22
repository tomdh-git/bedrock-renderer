## NEXT
DONE

# Unit U-EL1q — Record table field layouts (checklist L1q pending part: 0x130 framebuffer-texture record)

Goal (checklist L1q): decode field layouts of the 0x78/0x80/0x130/0x68 record tables. Texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 done per 6au — not this unit. Done previously (oc_U-EL1q_r1.md): 0x78 index-buffer records at renderer+0x93A178 [V], 0x80 vertex-buffer records at renderer+0x9B2178 [V], 0x68 framebuffer-window records at renderer+0xC97698 [V] (128 entries).

Pending part (this unit): 0x130 framebuffer-texture record whose pointer is held in the guard slot at ctx+0xA32178+handle*0x78 (createFrameBuffer 0xe816380). Fields +0x01..+0x12F to decode. Records are separate 0x130-byte allocations from sub_e8360f0 (bump arena ctx+0x238+8, align 0x10). ctx = renderer-context base = qword at 0x12BB4910 [V live].

## Input data used (read fully, NOT regenerated per brief rule)

docs/progress/pre/_tmp_el1q_createfb.txt (createFrameBuffer 0xe816380 listing), _tmp_el1q_e80ef60.txt (destroyer sub_e80ef60), _tmp_el1q_eec6ec0.txt (import thunk 0xEEC6EC0), _tmp_el1q_e8360f0.txt (allocator sub_e8360f0 complete), _tmp_el1q_e92a8f0.txt (sub_e92a8f0), _tmp_el1q_descscan2.txt (descscan2.py TypeError), _tmp_el1q_imm_a32178.txt + _tmp_el1q_imm_a32178b.txt (imm scan for 0xA32178: 2 hits), _tmp_el1q_bytescan_a32178.txt (broken script), _tmp_el1q_site1.txt / _tmp_el1q_site2.txt / _tmp_el1q_site3.txt (renderer init/slot-free/ctor listings). Context: docs/BGFX_MAP.md line 1521 (`0xA32178 | 0x78 | 4096 | slots 36, 37 (create) and 38 ... | frame buffers`) and line 711 (0x78 vs 0x130 conflict note).

## NEW-ANGLE ATTEMPTS THAT FAILED (this attempt)

1. Other callers via rdis `xr`/`callers`: already proven — createFrameBuffer 0xe816380 is stored at vtable entries 0xF4ED3F8 (base vtable 0xF4ED2D0 slot 37) and 0xF4EEFA8 (RTX vtable 0xF4EEE80 slot 37); `xr` on both entries: 0 xrefs; callers use indirect `call qword ptr [reg+0x128]`, which neither xr nor callers can enumerate. No xrefs to e816380 at all (vtable-dispatched). So the runtime size rbx=[r9+8] and source r14=[r9] are unobservable statically, and read-only livemem cannot read mid-call registers. Not redone — confirmed by the precomputed listings.
2. vt/vcalls: not applicable — the 0x130 record is a plain data struct (no vtable, no virtual calls); sub_eec6ec0 is an import thunk, not chased per orchestrator hint.
3. descscan2.py: broken (TypeError, _tmp_el1q_descscan2.txt); rdis `rw`/`struct` not applicable to this problem.
4. Fresh livemem re-read (orchestrator UPDATE: game was said to be restarted, re-read ctx, do not reuse old addresses): `python tools/sigs/livemem.py status` → pid 18956 (same pid as r4, game was NOT actually restarted), base 0x7ff699000000, version OK; `python tools/sigs/livemem.py ptr @0x12BB4910 1` → +0x0 0x000005314A010000 (ctx, same value as r4); `python tools/sigs/livemem.py read 0x5314AA32178 0x3c0` (ctx+0xA32178 = 0x5314AA32178, slots 0-7, 8 x 0x78) → ALL ZEROS: no framebuffer-texture records exist in this instance right now, so no live record dump is obtainable. r4's three record snapshots (p0=0x172B581F0, p1=0x172B55AC0, p2=0x1B62E37F0) stand as the last live observation. No new instruction sites; no live value is tied to the copy.

## What the disassembly proves [V] — createFrameBuffer 0xe816380 (verbatim from _tmp_el1q_createfb.txt)

- `0xe816390  mov rdi,rcx` — rdi = this = renderer object = ctx.
- `0xe816396  imul rbp,rcx,0x78` / `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` — guard slot at ctx+0xA32178+handle*0x78; slot+0x00 = record pointer (existence test).
- `0xe81648f  mov r14,[r9]` / `0xe816492  mov ebx,[r9+8]` — source r14 = qword at [r9] (caller's buffer, arg 4); size rbx = dword at [r9+8] zero-extended into r8 (runtime byte count); r14 null-checked `0xe816521  test r14,r14` / `0xe816524  je short 0xE816534`.
- `0xe8164bb  call 0xE8360F0` (rcx=[rdi+0x238]+8 arena object, rdx=&[rsp+0x48] out-param, r8=rbx=[r9+8] size, r9d=0x10 align) — sub_e8360f0 bump-allocates [r9+8] bytes aligned 0x10; per _tmp_el1q_e8360f0.txt the allocated pointer is stored at out-param+0x00 (`0xe836308  mov [rsi],rcx` and variants e83636d/e8363d3/e8363f7). Hence after the call [rsp+0x48] = record pointer.
- `0xe8164c0  mov esi,[rsp+0x58]` / `0xe8164c4  mov rax,[rsp+0x48]` — rax = record ptr; rsi = dword at [rsp+0x58], an allocator-provided runtime value (written by sub_e8360f0 into its out-param block, not statically resolvable as a constant).
- Record field reads on the fresh record (rax = record ptr):
  - `0xe8164dc  mov r15,[rax]` — qword read at record+0x00; r15 later passed as r9 to device method `0xe81654f  mov rax,[rax+0x78]` / `0xe816560  call qword ptr [0xF99FFA0]`; role of +0x00 not shown by any instruction.
  - `0xe8164ce  mov rcx,[rax+0x10]` — qword read at record+0x10; memcpy-destination base component (`0xe8164d2  add rcx,rsi`).
  - `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164df  cmove r12,rcx` — dword type tag compared against 2; r12 = ([rax+0x1C]==2) ? [rax+0x10]+rsi : 0.
- `0xe816517  add rdi,rbp` / `0xe81651a  add rdi,0xA32178` / `0xe816534  mov rdx,[rdi]` — creator re-reads guard slot [ctx+0xA32178+handle*0x78]+0x00 to get the record pointer back.
- `0xe816526  mov rcx,r12` / `0xe816529  mov rdx,r14` / `0xe81652c  mov r8,rbx` / `0xe81652f  call 0xEEC6EC0` — import-thunk memcpy/memmove: 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` (rcx=dst rdx=src r8=size per orchestrator hint). Copies [r9+8] bytes from [r9] into dst r12.
- No store of the record pointer into the guard slot appears in the createFrameBuffer listing; the slot write is performed by the indirect vtable-slot-37 caller after the call returns (caller unlocatable). No other located function reads or writes any record byte: sub_e80ef60 touches only guard-slot fields; sub_e92a8f0 reads slot-resource object fields ([rsi+0x7C], [rsi+0x128], [rsi+0x178], [rsi+0x180], [rsi+0xC8], [rsi+0xD8]...).

Key correction vs earlier attempts: rax at `0xe8164c4  mov rax,[rsp+0x48]` IS the record pointer (sub_e8360f0 stores the allocated block at out-param+0x00), so `0xe8164ce  mov rcx,[rax+0x10]` / `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164dc  mov r15,[rax]` are genuine record-field reads at +0x10/+0x1C/+0x00 — not owner-object fields. However the memcpy destination r12 = ([rax+0x1C]==2) ? [rax+0x10]+rsi : 0 is NOT a fixed record offset: rsi is a runtime dword from the allocator and [rax+0x10] is itself a record field. The only record write is this bulk copy at an unresolved record-relative offset.

## Field table (0x130 framebuffer-texture record at pointer held in guard slot ctx+0xA32178+handle*0x78)

| name | offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag |
|------|--------|------|------|-------------------------------|---------|-----|
| framebuffer-texture record +0x00 | +0x00 | 8 | createFrameBuffer 0xe816380 (rax = record ptr = sub_e8360f0 out-param [rsp+0x48]) | `0xe8164dc  mov r15,[rax]` | qword read at record+0x00; r15 passed as r9 to device method `0xe81654f  mov rax,[rax+0x78]` / `0xe816560  call qword ptr [0xF99FFA0]`; role of +0x00 not shown by any instruction | [V] |
| framebuffer-texture record +0x10 | +0x10 | 8 | createFrameBuffer 0xe816380 | `0xe8164ce  mov rcx,[rax+0x10]` | qword read at record+0x10; used as memcpy-destination base component (`0xe8164d2  add rcx,rsi`, r12 = [rax+0x10]+rsi when [rax+0x1C]==2); live: 0 in all observed snapshots | [V] |
| framebuffer-texture record +0x1C | +0x1C | 4 | createFrameBuffer 0xe816380 | `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164df  cmove r12,rcx` | dword type tag compared against 2; selects memcpy path r12 = [rax+0x10]+rsi else 0; live: 0 in all observed snapshots (copy path inert) | [V] |
| memcpy destination r12 | copy dst | — | createFrameBuffer 0xe816380 | `0xe816526  mov rcx,r12` / `0xe81652f  call 0xEEC6EC0` | r12 = ([rax+0x1C]==2) ? [rax+0x10]+rsi : 0; record-relative offset NOT resolvable — rsi = dword at [rsp+0x58] (`0xe8164c0  mov esi,[rsp+0x58]`) is allocator-provided at runtime and [rax+0x10] is itself a record field; no fixed record offset is written | [V] |
| memcpy source r14 | src=[r9] | 8 | createFrameBuffer 0xe816380 | `0xe81648f  mov r14,[r9]` / `0xe816521  test r14,r14` / `0xe816524  je short 0xE816534` | source pointer = qword at [r9] (caller's buffer); copy skipped when NULL | [V] |
| memcpy size rbx | size=[r9+8] | 4 | createFrameBuffer 0xe816380 | `0xe816492  mov ebx,[r9+8]` / `0xe81652c  mov r8,rbx` | size = dword at [r9+8] zero-extended into r8 (runtime record-block byte count) | [V] |
| record allocation | size=[r9+8] | — | createFrameBuffer 0xe816380 → sub_e8360f0 | `0xe8164bb  call 0xE8360F0` / `0xe836308  mov [rsi],rcx` | sub_e8360f0 bump-allocates [r9+8] bytes aligned 0x10; allocated pointer stored at out-param+0x00 → rax = record ptr (`0xe8164c4  mov rax,[rsp+0x48]`) | [V] |
| attachment-descriptor memcpy (only record-block write) | [r9+8] bytes | — | createFrameBuffer 0xe816380 | `0xe81652f  call 0xEEC6EC0` | 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` import thunk; memcpy(dst=r12, src=r14, size=r8) per orchestrator hint; copies [r9+8] bytes from [r9] into the record at the unresolved offset r12; not a record-field write | [V] |
| guard slot +0x00 (record pointer) | slot +0x00 | 8 | createFrameBuffer 0xe816380 / destroyer sub_e80ef60 | `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` / `0xe816534  mov rdx,[rdi]` / `0xe80ef70  mov rdx,[rcx]` | qword at slot [ctx+0xA32178+handle*0x78]+0x00 = record pointer | [V] |
| guard slot +0x0C | slot +0x0C | 4 | destroyer sub_e80ef60 | `0xe80ef7c  mov r8d,[rcx+0xC]` / `0xe80ef82  cmp r8d,0xB` | dword slot type tag compared against 0xB — SLOT field, NOT a record field | [V] |
| guard slot +0x58 | slot +0x58 | 8 | destroyer sub_e80ef60 | `0xe80efb4  mov rdx,[rcx+0x58]` / `0xe80efbe  call 0xE92A8F0` | qword slot resource released via sub_e92a8f0 — SLOT field, NOT a record field | [V] |
| guard slot clears | slot +0x00/+0x58/+0x5F/+0x68 | 8 | destroyer sub_e80ef60 | `0xe80f259  mov qword ptr [rcx],0` / `0xe80f260  mov qword ptr [rcx+0x68],0` / `0xe80f268  mov qword ptr [rcx+0x58],0` / `0xe80f270  mov qword ptr [rcx+0x5F],0` | slot fields cleared on destroy — SLOT fields, NOT record bytes | [V] |

## [V live] observations (last live instance, pid 18956; not re-obtainable now — guard slots all zero)

- `python tools/sigs/livemem.py status` → pid 18956, base 0x7ff699000000, version OK 1.26.62.01.
- `python tools/sigs/livemem.py ptr @0x12BB4910 1` → +0x0  0x000005314A010000  ptr (ctx).
- `python tools/sigs/livemem.py read 0x5314AA32178 0x3c0` (ctx+0xA32178, slots 0-7, stride 0x78) → ALL ZEROS: no framebuffer-texture records live in this instance right now (confirms ctx+0xA32178 is a guard-slot array holding record pointers at slot+0x00, not a record table).
- r4's three record snapshots from the same pid (records then at p0=0x172B581F0, p1=0x172B55AC0, p2=0x1B62E37F0 via `read <addr> 0x130`; slots are now empty so these values are instance observations, not constants):
  - Stable across all 3 snapshots: +0x00 = 0x000007FBA1D2E100 (shared ptr), +0x20 = 0x000007FBA1D2E0D8 (shared ptr), +0x40 = 1, +0x48 = 2, +0x50 = 0x000007FFBDB76198 (shared ptr), +0xA8 = 0x000000000653A400, +0xB8 = 1, +0xD8 = 0x000007FBA1D2E1C0 (shared ptr), +0xE8 = 0x11000000, +0xEC = 0x14000001, +0xF0 = 1, +0xF4 = 1, +0xF8 = 1, +0x100 = 4.
  - Varies per record: +0x58/+0x60/+0x68, +0xA0 (near-record ptr), +0xB0 = record's own address (self pointer), +0xC0, +0xC8, +0xE0 (8 / 0x20 / 0x40000), +0xBC (0x5C0F3C49 in rec2 only).
  - +0x10 = 0 and +0x1C = 0 in all 3 snapshots → copy path inert (r12 = 0), no record byte written by the copy in the observed instance.
  - All other offsets: 0x00 in all 3 snapshots.
- Meaning is '-' for every live-only offset (not shown by any instruction or string); none of these values is tied to the copy (size rbx=[r9+8] and dst r12 are runtime-unresolvable).

## Unproven — every offset not covered by a [V] row above

No instruction touches them; where observed live they read 0x00 in all 3 snapshots (a value observation with meaning '-', not a field layout and not tied to the copy): +0x01..+0x0F, +0x11..+0x1F, +0x21..+0x27, +0x29..+0x2F, +0x31..+0x3F, +0x41..+0x47, +0x49..+0x4F, +0x51..+0x57, +0x59..+0x5F, +0x61..+0x6F, +0x71..+0x9F, +0xA1..+0xA7, +0xA9..+0xAF, +0xB1..+0xB7, +0xB9..+0xBF, +0xC1..+0xC7, +0xC9..+0xCF, +0xD1..+0xD7, +0xD9..+0xDF, +0xE1..+0xE7, +0xE9..+0xEF, +0xF9..+0xFF, +0x101..+0x12F. Offsets +0x20/+0x58/+0x60/+0x68/+0xA0/+0xB0/+0xBC/+0xC0/+0xC8/+0xE0 have [V live] observations only (no instruction site).

## CLOSES?

NO — blocking fact: no instruction writes any record byte at +0x01..+0x12F. The only record write is the attachment-descriptor copy at `0xe81652f  call 0xEEC6EC0` (memcpy/memmove-style import, rcx=dst rdx=src r8=size) whose record-relative destination r12 = ([rax+0x1C]==2) ? [rax+0x10]+rsi : 0 is not statically resolvable — rsi = dword at [rsp+0x58] (`0xe8164c0  mov esi,[rsp+0x58]`) is an allocator-provided runtime value and [rax+0x10] is itself a record field — and the copy path is inert in every observed live instance (+0x1C==0 → r12==0). No other located function writes any record byte: the destroyer sub_e80ef60 touches only guard-slot fields (+0x00/+0x0C/+0x58/+0x5F/+0x68), sub_e92a8f0 reads slot-resource object fields, and createFrameBuffer's callers are indirect vtable-slot-37 calls (`call [reg+0x128]`) with 0 xrefs to entries 0xF4ED3F8/0xF4EEFA8, so the runtime size [r9+8], source [r9], and any later field writers are unobservable statically. descscan2.py is broken; vt/vcalls and rw/struct do not apply to this plain data struct. Consequently not every pending offset +0x01..+0x12F has a [V] row, so the 0x130 framebuffer-texture record layout cannot be closed from the evidence available to this unit.

## TOOL REQUESTS

None — all data came from the precomputed input listings plus rdis/livemem calls already made; no helper script written.
