## NEXT
DONE

# Unit U-EL1q — 0xA32178 table: 0x78-stride shader-buffer entries, not 0x130 records

Goal (checklist L1q pending part, per orchestrator resolution 2026-11-21): the table at ctx+0xA32178 has stride 0x78, NOT 0x130 — the 0x130 (BGFX_MAP 6z lines 638/654, line 711 conflict note) is a mislabel. The 0xA32178 entries are shader-buffer slots (6fq: binding types 4/8, command byte 19 creates them from a data blob, destroy slot 38); bgfx framebuffers live at ctx+0xC97698 stride 0x68 (6fq). Each 0x78-byte slot holds a record pointer at +0x00; the record itself is a bump-allocated block (size [r9+8] from the caller's data blob, sub_e8360f0) whose fields +0x00/+0x10/+0x1C are read by createFrameBuffer 0xe816380.

This note decodes, with offsets < 0x78: (a) every field of the 0x78 slot touched by located code (create/destroy/descriptor build 6fq/executor), (b) every record-block field touched by createFrameBuffer 0xe816380, (c) the copy size/source/allocation facts. All RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Instruction quotes verbatim from rdis `dis` of input listings docs/progress/pre/_tmp_el1q_createfb.txt and _tmp_el1q_e8360f0.txt (read fully) plus fresh dis of 0xe8270ee, 0xe825be1, 0xe824991. Meaning column: '-' unless an instruction/string shows it; inferences are flagged. Tags: [V] = seen in disassembly (RVA cited); [V input] = quoted from an input listing that previously passed verify_oc; [?] = no located instruction touches the offset. No offset is skipped: proven offsets have individual rows; all remaining slot/record offsets below are enumerated as [?] ranges.

## 1. Stride 0x78 proven; 0x130 is a mislabel [V]

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| table stride 0x78 (create) | 0xA32178 table | - | createFrameBuffer 0xe816380 | `0xe816396  imul rbp,rcx,0x78` / `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` | guard-slot index = handle*0x78 into table at ctx+0xA32178; slot+0x00 existence test | [V] |
| table stride 0x78 (destroy) | 0xA32178 table | - | destroy stub 0xe816580 | `0xe816583  imul rax,0x78` / `0xe81658a  add rcx,0xA32178` / `0xe816591  jmp 0xE80EF60` | destroy walks slot at ctx+0xA32178+handle*0x78 | [V] |
| table stride 0x78 (descriptor build type 4) | 0xA32178 table | - | descriptor build 0xe8270ee | `0xe8270ee  imul rax,rdi,0x78` / `0xe8270f2  mov rcx,[rbx+0x3A0]` / `0xe8270f9  lea r14,[rcx+rax]` | type 4 ShaderBuffer locates slot at job+0x3A0 (=ctx+0xA32178) + handle*0x78 | [V] |
| table stride 0x78 (descriptor build type 8) | 0xA32178 table | - | descriptor build 0xe825be1 | `0xe825c70  imul rax,rcx,0x78` / `0xe825c74  mov rdx,[rbx+0x3A0]` / `0xe825c7b  lea r15,[rdx+rax]` | type 8 RangedShaderBuffer locates slot at job+0x3A0 + handle*0x78 | [V] |
| table stride 0x78 (executor bind) | 0xA32178 table | - | executor 0xe824991 | `0xe824991  imul rax,rdi,0x78` / `0xe824995  mov rcx,[rbx+0x3A0]` / `0xe82499c  lea r14,[rcx+rax]` | executor bind type 4 walks slot at job+0x3A0 + handle*0x78 | [V] |
| 0x130 stride absent | 0xA32178 table | - | - | - | no 0x130 stride computation for this table in any located function; every located access uses imul 0x78; BGFX_MAP 6z lines 638/654 and the line-711 "0x130 / two interleaved arrays" wording is a mislabel — correction recorded here only, edits to docs/BGFX_MAP.md forbidden by brief rule 3 | [V] |

## 2. 0x78-byte slot (guard-slot entry) at ctx+0xA32178+handle*0x78 — fields with located access [V]

slot+0x00 holds the record pointer qword (written by the vtable-slot-37 indirect caller — not located in this executable, see section 6).

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| slot +0x00 record pointer | +0x00 | 8 | createFrameBuffer 0xe816380 / descriptor build 0xe8270ee / descriptor build 0xe825be1 / executor 0xe824991 | `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` / `0xe816534  mov rdx,[rdi]` / `0xe82715d  mov rcx,[r11+0x22498]` / `0xe827164  mov rax,[rcx+rax]` / `0xe827173  mov [rbx+0xC8],rax` / `0xe825ce2  mov rcx,[r11+0x22498]` / `0xe825ce9  mov rax,[rcx+rax]` / `0xe825cf8  mov [rbx+0xC8],rax` / `0xe824991  imul rax,rdi,0x78` / `0xe824995  mov rcx,[rbx+0x3A0]` / `0xe82499c  lea r14,[rcx+rax]` / `0xe824a07  mov rax,[rcx+rax]` | qword at slot+0x00 = record pointer; existence test, re-read after create, loaded into descriptors by type-4/type-8 descriptor build and executor bind type 4 | [V] |
| slot +0x0C | +0x0C | 4 | destroyer sub_e80ef60 | `0xe80ef7c  mov r8d,[rcx+0xC]` / `0xe80ef82  cmp r8d,0xB` | dword at slot+0xC compared against 0xB on destroy | [V] |
| slot +0x14 | +0x14 | 4 | descriptor build 0xe825be1 | `0xe826002  mov ecx,[r15+0x14]` / `0xe82600d  mov [rdx-8],ecx` | dword read at slot+0x14 into descriptor (type-8 ranged path) | [V] |
| slot +0x24 | +0x24 | 4 | descriptor build 0xe825be1 | `0xe825fa7  mov r11d,[r15+0x24]` / `0xe825ffb  mov [rbx+0xC0],r13d` | dword read at slot+0x24 (type-8 ranged path) | [V] |
| slot +0x28 | +0x28 | 8 | descriptor build 0xe825be1 | `0xe825f93  mov r10,[r15+0x28]` / `0xe826026  mov [rbx+0xDC],r11d` | qword read at slot+0x28 (type-8 ranged path) | [V] |
| slot +0x30 | +0x30 | 4 | descriptor build 0xe825be1 | `0xe825e8c  mov r11d,[r15+0x30]` / `0xe825e90  mov r10d,[r15+0x44]` | dword read at slot+0x30 (type-8 ranged path) | [V] |
| slot +0x34 | +0x34 | 4 | descriptor build 0xe825be1 | `0xe825e80  mov r9d,[r15+0x34]` | dword read at slot+0x34 (type-8 ranged path) | [V] |
| slot +0x44 | +0x44 | 4 | descriptor build 0xe825be1 | `0xe825e90  mov r10d,[r15+0x44]` | dword read at slot+0x44 (type-8 ranged path) | [V] |
| slot +0x48 | +0x48 | 16 | descriptor build 0xe825be1 | `0xe825f06  movups xmm0,[r15+0x48]` / `0xe825f12  movups [rax+4],xmm0` | 16-byte read at slot+0x48 (movups) into descriptor | [V] |
| slot +0x58 | +0x58 | 8 | destroyer sub_e80ef60 | `0xe80efb4  mov rdx,[rcx+0x58]` / `0xe80efbe  call 0xE92A8F0` / `0xe80f268  mov qword ptr [rcx+0x58],0` | qword slot field read on destroy, released via sub_e92a8f0, then cleared to 0 | [V] |
| slot +0x5F | +0x5F | 1 | destroyer sub_e80ef60 | `0xe80f270  mov qword ptr [rcx+0x5F],0` | byte slot field cleared to 0 on destroy | [V] |
| slot +0x60 | +0x60 | 4 | descriptor build 0xe825be1 | `0xe825ea7  mov eax,[r15+0x60]` / `0xe825eab  sub eax,r8d` | dword read at slot+0x60 (type-8 ranged path) | [V] |
| slot +0x65 | +0x65 | 1 | descriptor build 0xe825be1 | `0xe825e94  movzx eax,byte ptr [r15+0x65]` / `0xe825e99  and al,0x10` | byte read at slot+0x65 (type-8 ranged path) | [V] |
| slot +0x68 | +0x68 | 8 | destroyer sub_e80ef60 | `0xe80f260  mov qword ptr [rcx+0x68],0` | qword slot field cleared to 0 on destroy | [V] |
| slot +0x01..+0x0B | +0x01..+0x0B | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x0D..+0x13 | +0x0D..+0x13 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x15..+0x23 | +0x15..+0x23 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x25..+0x27 | +0x25..+0x27 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x29..+0x2F | +0x29..+0x2F | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x31..+0x33 | +0x31..+0x33 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x35..+0x43 | +0x35..+0x43 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x45..+0x47 | +0x45..+0x47 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x49..+0x57 | +0x49..+0x57 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x59..+0x5E | +0x59..+0x5E | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x61..+0x64 | +0x61..+0x64 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x66..+0x67 | +0x66..+0x67 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| slot +0x69..+0x77 | +0x69..+0x77 | - | - | - | no located instruction reads or writes these slot offsets | [?] |

## 3. Record block (bump-allocated by sub_e8360f0, pointer held at slot+0x00) — fields touched by createFrameBuffer 0xe816380, offsets < 0x78 [V]

The allocation size is the caller-provided [r9+8] (runtime; may exceed 0x78). createFrameBuffer reads record fields but writes none of them.

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| record +0x00 | +0x00 | 8 | createFrameBuffer 0xe816380 | `0xe8164dc  mov r15,[rax]` | qword read at record+0x00; value (resource/guard pointer) passed as r9 to device call `0xe81654f  mov rax,[rax+0x78]` / `0xe816560  call qword ptr [0xF99FFA0]`; role not shown beyond being a pointer argument | [V] |
| record +0x10 | +0x10 | 8 | createFrameBuffer 0xe816380 | `0xe8164ce  mov rcx,[rax+0x10]` / `0xe8164d2  add rcx,rsi` | qword read at record+0x10; used as memcpy-destination base component (r12 = record+0x10 + [rsp+0x58] when record+0x1C==2) | [V] |
| record +0x1C | +0x1C | 4 | createFrameBuffer 0xe816380 | `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164df  cmove r12,rcx` | dword read at record+0x1C compared against 2; kind tag selecting the blob-copy path | [V] |
| record +0x01..+0x0F | +0x01..+0x0F | - | - | - | no located instruction reads or writes these record offsets | [?] |
| record +0x11..+0x1B | +0x11..+0x1B | - | - | - | no located instruction reads or writes these record offsets | [?] |
| record +0x1D..+0x77 | +0x1D..+0x77 | - | - | - | no located instruction reads or writes these record offsets | [?] |

## 4. Record allocation and the 0xe81652f copy [V]

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| record allocation | - | [r9+8] | createFrameBuffer 0xe816380 | `0xe816492  mov ebx,[r9+8]` / `0xe8164b8  mov r8,rbx` / `0xe8164bb  call 0xE8360F0` | sub_e8360f0 bump-allocates [r9+8] bytes aligned 0x10 (r9d=0x10) from arena [rdi+0x238]+8; allocated pointer stored at out-param+0x00 | [V] |
| record pointer out-param | - | 8 | sub_e8360f0 | `0xe836308  mov [rsi],rcx` / `0xe8164c4  mov rax,[rsp+0x48]` | sub_e8360f0 stores the allocated pointer at out-param+0x00 → rax = record pointer | [V] |
| copy source r14 | - | 8 | createFrameBuffer 0xe816380 | `0xe81648f  mov r14,[r9]` / `0xe816521  test r14,r14` / `0xe816524  je short 0xE816534` | source pointer = qword at [r9] (createFrameBuffer arg 4 = caller's data blob); copy skipped when NULL | [V] |
| copy size rbx | - | 4 | createFrameBuffer 0xe816380 | `0xe816492  mov ebx,[r9+8]` / `0xe81652c  mov r8,rbx` | size = dword at [r9+8] zero-extended into r8 (runtime byte count of caller's block; caller indirect, unobservable statically) | [V] |
| copy destination r12 | - | - | createFrameBuffer 0xe816380 | `0xe8164d5  xor r12d,r12d` / `0xe8164df  cmove r12,rcx` / `0xe816526  mov rcx,r12` | r12 = (record+0x1C==2) ? record+0x10 + [rsp+0x58] : 0 ([rsp+0x58] is allocator-provided runtime block info; record+0x10 is itself a record field) — record-relative offset NOT statically resolvable; not a provable record-field store | [V] |
| bulk copy call | - | [r9+8] | createFrameBuffer 0xe816380 | `0xe81652f  call 0xEEC6EC0` | 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` import thunk = memcpy/memmove-style (rcx=dst rdx=src r8=size per orchestrator hint); copies [r9+8] bytes from [r9] to dst r12; thunk target not chased | [V] |

## 5. Descriptor build (6fq) record-level reads [V]

type 4 (0xe8270ee) and type 8 (0xe825be1) locate the slot via `imul handle,0x78` + job+0x3A0 (=ctx+0xA32178) and read slot+0x00 (record pointer) as shown in section 2; the executor bind type 4 (0xe824991) does the same (`0xe824a07  mov rax,[rcx+rax]`). No located descriptor-build instruction reads any record-block offset other than via the slot+0x00 record pointer.

## 6. Blocking fact (why not every offset is [V])

No instruction in Minecraft.Windows.exe writes any field of the 0x78 record block: createFrameBuffer 0xe816380 only reads record +0x00, +0x10, +0x1C and performs one bulk copy to the unresolved external dst r12 (section 4). The record-field writer is the vtable-slot-37 indirect caller: vtable entries 0xF4ED3F8 (base vtable 0xF4ED2D0) and 0xF4EEFA8 (RTX vtable 0xF4EEE80) hold 0xE816380 [V rdis ptr], but there is no call site for it in this executable (r8 angle (b): exhaustive scan — 0 direct `call 0xe816380`, 0 `jmp [reg+0x128]`, and the only two `call [reg+0x128]` sites in .text are unrelated objects); the writer and its writes live outside Minecraft.Windows.exe and are not observable from static analysis or read-only livemem (no mid-call register access; no live records exist now — guard slots at ctx+0xA32178 all zero). descscan2.py is broken; vt/vcalls and rdis rw/struct do not apply to this plain data struct.

## CLOSES?

NO — blocking fact: no instruction in Minecraft.Windows.exe writes any field of the 0x78 record block (only +0x00/+0x10/+0x1C reads at `0xe8164dc  mov r15,[rax]`, `0xe8164ce  mov rcx,[rax+0x10]`, `0xe8164d8  cmp dword ptr [rax+0x1C],2`) and the field-initializing writer (vtable slot 37 indirect caller, entries 0xF4ED3F8/0xF4EEFA8 hold 0xE816380) has no call site in this executable, so record-block offsets +0x01..+0x0F, +0x11..+0x1B, +0x1D..+0x77 (and the unwritten slot offsets) have no [V] row and cannot be proven from this exe; record size [r9+8], copy source [r9] and size [r9+8] are caller-provided runtime values. What IS closed [V]: stride 0x78 for 0xA32178 (create/destroy/descriptor-build/executor all imul 0x78); the 0x130 mislabel (0x130 never appears as this table's stride); slot +0x00 record pointer; record block +0x00/+0x10/+0x1C reads; copy size rbx=[r9+8] and source r14=[r9]; slot fields +0x0C/+0x14/+0x24/+0x28/+0x30/+0x34/+0x44/+0x48/+0x58/+0x5F/+0x60/+0x65/+0x68. Required BGFX_MAP.md 6z (lines 638/654) and line 711 wording corrections are documented here but not applied — brief rule 3 forbids editing docs/BGFX_MAP.md (and docs/RENDER_CHECKLIST.md).

## TOOL REQUESTS

None — all verification via rdis `dis` of the input listings plus fresh dis of 0xe8270ee/0xe825be1/0xe824991; no helper scripts written.
