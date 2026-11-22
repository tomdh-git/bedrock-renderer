## NEXT
DONE

# Unit U-EL1q — Record table field layouts (checklist L1q pending part: 0x130 framebuffer-texture record)

Goal (checklist L1q): decode field layouts of the 0x78/0x80/0x130/0x68 record tables. Texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 done per 6au — not this unit. Done previously (oc_U-EL1q_r1.md): 0x78 index-buffer records at renderer+0x93A178 [V], 0x80 vertex-buffer records at renderer+0x9B2178 [V], 0x68 framebuffer-window records at renderer+0xC97698 [V] (128 entries).

Pending part (this unit): 0x130 framebuffer-texture record whose pointer is held in the guard slot at renderer+0xA32178+handle*0x78 (createFrameBuffer 0xe816380). Fields +0x01..+0x12F to decode. Records are separate allocations from sub_e8360f0; the 0xA32178 table itself is the guard-slot array (stride 0x78, 4096 slots per BGFX_MAP line 1521 and the e80e0e0/e80e100 loops `cmp rbx,0x78000`); the guard-slot store of the record pointer happens inside sub_e8360f0 (not shown in the createFrameBuffer listing).

Input data used (all read fully, NOT regenerated per brief rule): docs/progress/pre/_tmp_el1q_createfb.txt (createFrameBuffer 0xe816380 full listing 0xe816380..0xe81657f), _tmp_el1q_e80ef60.txt (destroyer sub_e80ef60), _tmp_el1q_eec6ec0.txt (import thunk 0xEEC6EC0 = `jmp qword ptr [0xF9A8A98]`), _tmp_el1q_e8360f0.txt (allocator sub_e8360f0 complete), _tmp_el1q_e92a8f0.txt (sub_e92a8f0). Additional rdis finding: sub_e836640 out-block layout (`0xe83674a  mov [rdx],rcx` / `0xe83674d  mov [rdx+8],r10` / `0xe836751  mov [rdx+0x10],r11` = { [arena+0], [arena+8], allocated-ptr }, `0xe836755  mov [rdx+0x18],r8` = size, `0xe836759  mov [rdx+0x20],rax` = end). descscan2.py is broken (TypeError, seen in _tmp_el1q_descscan2.txt); rdis rw/struct not applicable to this problem.

## NEW-ANGLE ATTEMPTS THAT FAILED (this attempt)

1. sub_e836640/sub_e943178 disassembly — resolved the allocator out-block: [rsp+0x48] = [[[renderer+0x238]+8]+0] (an owner object, rax), [rsp+0x58] = record pointer (only its low 32 bits used). Confirmed the memcpy dst r12 = ([rax+0x1C]==2) ? [rax+0x10]+rsi : 0 depends on runtime owner-object field [rax+0x10]; no static resolution.
2. livemem: `ptr @0x12ae1748` -> s_ctx = 0x0000053146010040, but `[0x53146010040] = 0x8BC` (val, not a vtable/object) and +0x238 unreadable, so s_ctx is not the renderer object; renderer = s_ctx - 0x19F58 = 0x53145FE10E88 is unreadable (`[0x53145FE10E88] = None`). No live renderer anchor exists, so [rax+0x10] cannot be read live either. 6 livemem calls used; stopping here per brief.
3. r1/r2 table rows claiming createFrameBuffer reads record+0x00/+0x10/+0x1C are WRONG: rax = [rsp+0x48] = owner object, not the record (`0xe8164dc  mov r15,[rax]` / `0xe8164ce  mov rcx,[rax+0x10]` / `0xe8164d8  cmp dword ptr [rax+0x1C],2` all target the owner object). Those rows are removed; the record pointer itself (at [rsp+0x58]) is never dereferenced by createFrameBuffer.

## PROVEN [V] — the copy and its size/source (createFrameBuffer 0xe816380)

- `0xe81648f  mov r14,[r9]` — source r14 = qword at [r9] (createFrameBuffer's 4th arg = caller's buffer); null-checked `0xe816521  test r14,r14` / `0xe816524  je short 0xE816534`.
- `0xe816492  mov ebx,[r9+8]` then `0xe81652c  mov r8,rbx` — size rbx = dword at [r9+8], zero-extended to r8 (runtime value = record block size).
- `0xe8164bb  call 0xE8360F0` with r8=rbx=[r9+8], r9d=0x10 — sub_e8360f0 bump-allocates [r9+8] bytes aligned 0x10 via sub_e836640; out-block `0xe836751  mov [rdx+0x10],r11` = allocated pointer (the record).
- `0xe816526  mov rcx,r12` / `0xe816529  mov rdx,r14` / `0xe81652c  mov r8,rbx` / `0xe81652f  call 0xEEC6EC0` — memcpy/memmove-style import call: 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` (import thunk, args rcx=dst rdx=src r8=size per orchestrator hint). Copies [r9+8] bytes from [r9] into the record at r12.
- `0xe8164c0  mov esi,[rsp+0x58]` / `0xe8164c4  mov rax,[rsp+0x48]` / `0xe8164ce  mov rcx,[rax+0x10]` / `0xe8164d2  add rcx,rsi` / `0xe8164d5  xor r12d,r12d` / `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164df  cmove r12,rcx` — dst r12 = ([rax+0x1C]==2) ? [rax+0x10]+rsi : 0 where rax = [rsp+0x48] = owner object [[[renderer+0x238]+8]+0] and rsi = low32(record ptr). [rax+0x1C] compared against 2 (type gate).
- `0xe816534  mov rdx,[rdi]` — creator re-reads the guard slot [rdi = renderer + handle*0x78 + 0xA32178] to get the record pointer back.

Guard slot (destroyer sub_e80ef60, entry `0xe816580  movzx eax,dx` / `0xe816583  imul rax,0x78` / `0xe816587  add rcx,rax` / `0xe81658a  add rcx,0xA32178` / `0xe816591  jmp 0xE80EF60`, rcx = slot base):
- `0xe80ef70  mov rdx,[rcx]` — 8B read slot+0x00 = record pointer.
- `0xe80ef7c  mov r8d,[rcx+0xC]` / `0xe80ef82  cmp r8d,0xB` — 4B read SLOT+0x0C (slot type tag), NOT a record field.
- `0xe80efb4  mov rdx,[rcx+0x58]` / `0xe80efbe  call 0xE92A8F0` — 8B read SLOT+0x58 (slot resource released via sub_e92a8f0), NOT a record field.
- `0xe80f259  mov qword ptr [rcx],0` / `0xe80f260  mov qword ptr [rcx+0x68],0` / `0xe80f268  mov qword ptr [rcx+0x58],0` / `0xe80f270  mov qword ptr [rcx+0x5F],0` — clears SLOT fields +0x00/+0x68/+0x58/+0x5F, NOT record bytes.

## Field table (0x130 framebuffer-texture record at renderer+0xA32178+handle*0x78 guard slot, record = separate allocation from sub_e8360f0)

| name | offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag |
|------|--------|------|------|-------------------------------|---------|-----|
| memcpy source r14 | source=[r9] | 8 | createFrameBuffer 0xe816380 | `0xe81648f  mov r14,[r9]` | source pointer = qword at [r9], caller's buffer (createFrameBuffer arg 4); null-checked at `0xe816521` | [V] |
| memcpy size rbx | size=[r9+8] | [r9+8] | createFrameBuffer 0xe816380 | `0xe816492  mov ebx,[r9+8]` / `0xe81652c  mov r8,rbx` | size = dword at [r9+8] zero-extended into r8 (runtime record-block size); passed as r8 to the memcpy call | [V] |
| record allocation | — | [r9+8] | createFrameBuffer 0xe816380 | `0xe8164bb  call 0xE8360F0` | sub_e8360f0 bump-allocates [r9+8] bytes aligned 0x10 (sub_e836640); allocated ptr = out-block +0x10 (`0xe836751  mov [rdx+0x10],r11`); stored into guard slot by sub_e8360f0 | [V] |
| record bulk copy (memcpy) | r12 = ([rax+0x1C]==2) ? [rax+0x10]+low32(record_ptr) : 0; record-relative offset UNRESOLVED | [r9+8] | createFrameBuffer 0xe816380 | `0xe81652f  call 0xEEC6EC0` with `0xe816526  mov rcx,r12`, `0xe816529  mov rdx,r14`, `0xe81652c  mov r8,rbx` | 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` memcpy/memmove-style import (rcx=dst rdx=src r8=size); copies [r9+8] bytes from [r9] into the record at r12; which record offset r12 lands on is not provable statically | [V] |
| guard slot +0x00 (record pointer) | slot +0x00 | 8 | destroyer sub_e80ef60 / creator | `0xe80ef70  mov rdx,[rcx]` / `0xe816534  mov rdx,[rdi]` | qword at slot [renderer+0xA32178+handle*0x78]+0x00 = record pointer | [V] |
| guard slot +0x0C | slot +0x0C | 4 | destroyer sub_e80ef60 | `0xe80ef7c  mov r8d,[rcx+0xC]` / `0xe80ef82  cmp r8d,0xB` | dword compared against 0xB; SLOT field, NOT a record field | [V] |
| guard slot +0x58 | slot +0x58 | 8 | destroyer sub_e80ef60 | `0xe80efb4  mov rdx,[rcx+0x58]` / `0xe80efbe  call 0xE92A8F0` | qword slot resource released via sub_e92a8f0; SLOT field, NOT a record field | [V] |

## Unproven

record bytes +0x01..+0x12F: no [V] row covers any of them. createFrameBuffer 0xe816380 never dereferences the record pointer — rax at `0xe8164c4  mov rax,[rsp+0x48]` is the owner object [[[renderer+0x238]+8]+0] (proven via sub_e8360f0's sub_e836640 out-block), and the record pointer at [rsp+0x58] is used only via its low 32 bits in address arithmetic (`0xe8164c0  mov esi,[rsp+0x58]`, `0xe8164d2  add rcx,rsi`). The record's only candidate write is the memcpy above at unresolved record-relative offset r12; its size [r9+8] is a runtime value, not a constant. The destroyer sub_e80ef60 touches only guard-slot fields; sub_e92a8f0 reads ctx/slot fields ([rsi+0x7C], [rsi+0x178], [rsi+0x180], [rcx+0x30]...); no other located function writes any record byte.

CLOSES? NO — blocking fact: the record-relative destination offset of the 0xe81652f attachment/record-image copy is not resolvable statically: r12 = ([rax+0x1C]==2) ? [rax+0x10]+low32(record_ptr) : 0, where [rax] = [[[renderer+0x238]+8]+0] is a runtime owner-object field and rsi = low32(record_ptr); no live renderer anchor exists (s_ctx = 0x0000053146010040 read via `ptr @0x12ae1748` is not the renderer object — `[0x53146010040] = 0x8BC` — and renderer = s_ctx - 0x19F58 = 0x53145FE10E88 is unreadable). Consequently no record byte offset +0x01..+0x12F has a [V] row: createFrameBuffer writes the record only via this memcpy and never dereferences the record pointer itself, the destroyer touches only guard-slot fields, and no other writer of record bytes was located. Size rbx=[r9+8] and source r14=[r9] are the only [V]-proven copy facts.

## TOOL REQUESTS

None — no helper script was written; all data came from the precomputed input listings plus one-off rdis/livemem calls. A live renderer-object anchor would be needed to resolve [rax+0x10] and close the unit, but no static anchor to the renderer object exists.
