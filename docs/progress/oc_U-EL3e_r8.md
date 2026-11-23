## NEXT
DONE

# UNIT U-EL3e — L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.

## NEXT block (resume pointer)

step 2 — begin new angle: find where the BatchActor bucket's slot array and records are created; trace callers of extractor 0x66d9af0 via Item visitor 0x6646980 (CFG), then find who fills slot+0x00 (record pointer) using rdis rw/descscan2 on bucket offsets +0x28/+0x30/+0x38/+0x42/+0x48/+0x52/+0x78; check docs/data/live/batchActor_extractor.txt for a live bucket anchor for one livemem read of a record (+0x28); read docs/BGFX_MAP.md sections 6ad/6o. Do NOT redo: TaskList-entry==record hypothesis (refuted r3-r7), full extractor re-decode (consume-only, r6/r7), ripscan of [0x129F9128] (consumer-only, r5/r7).

## Basis (closed by prior units, not retried)

- Checklist part (1) "task kind = FNV-1a 64 of a uniform name" CLOSED [V]: record+0x28 qword task-kind hash = fnv1a(uniform name); fnv1a("UseAlphaRewrite")=0x481CF7B16E204CF8, fnv1a("LightWorldSpaceDirection")=0x48603E36F5CE3EB2 (BGFX_MAP 6ad; recomputed basis 0xCBF29CE484222325 / prime 0x100000001B3 matches record+0x28 comparands). Two hash families: pass names FNV-1 (render_hashes.txt), task-record kinds FNV-1a of uniform names.
- BatchActor bucket/slot fields (+0x28/+0x30/+0x38/+0x42/+0x48/+0x52/+0x78, slot 0x10 stride, record-array stride 0x30 at bucket+0x48 with entry+0x00 = record pointer, record count word at bucket+0x52) mapped [V EC3b/E C3b2, check OK 11 rows].

## Blocker carried from r1-r7, updated this unit

Record SIZE [?], record+0x28 WRITER [?], and every record field other than +0x28 (kind hash), +0x30 (u16), +0x32 (u16), +0x34 (u8 flag) are [?]. New angle exhausted (this unit): sub_66d0a00 is consumer-only (creates scratch records via sub_66b2b30 which zeroes +0x28 but writes no hash; searches a caller-supplied slot array by [record+0x28] hash); sub_66b2b30's object is a different (~0x58-byte) entity with kind u32 at +0x00 = 1-8; fld_0x28_w_full.txt shows NO record+0x28 writer anywhere in .text; TaskList-entry==record hypothesis refuted [V negative] r3-r7; live reads blocked (capture bucket VA 0x3459FFF0F00 stale/unreadable, re-capture orchestrator-only). Record creation is upstream of 0x66d9af0 (material/uniform registration, before Item visitor 0x6646980 -> sub_66466e0). No static path or live anchor reaches the creation site; record size has no provable upper bound (lower bound >= 0x35 from last observed field +0x34).

## What I tried that failed (this unit — new angle only; nothing already proven redone)

(step 2, this unit) Traced caller chain 0x66d9af0 <- Item visitor 0x6646980 <- sub_66466e0 (vtable slot 6 'FrameBuilder - Insert item', 0 xrefs/callers, 0x6646848 rcx=[rsi+0x20] rdx=&[rbp-0x28] r8=&[rbp-0x40]): sub_66466e0 is a dead end (vtable dispatch only, no static path into it). Then analyzed sub_66d0a00 (0x66d0a00..0x66d7d8b), the uniform setter called from visitor@0x664b7bc inside visitItem; full listing dumped to docs/progress/listings/oc_U-EL3e_66d0a00.txt (6005 lines). Findings, all [V] from that listing:
- sub_66d0a00 creates scratch records via sub_66b2b30 at 0x66d2f5f (rec=[rbp+0x470], rcx=r13=&[rbp+0x470]) and at 0x66d3423 (rec=[rbp+0x208], rcx=&[rbp+0x208]); after each call writes rec+0x04 ONLY (`0x66d2f65  and byte ptr [rbp+0x474],0xF7`; `0x66d3435  mov byte ptr [rbp+0x21C],1`), NEVER rec+0x28.
- sub_66d0a00 then searches a local slot array at [rbp+0xD18] (stride 0x10, count word at [rbp+0xD22], entry+0x00 = record pointer r10), comparing `cmp [r10+0x28], <hash-reg>` against DATA hash constants [0x129F8310], [0x129F8350], … (9 loops). [rbp+0xD18] is READ-ONLY in sub_66d0a00 (zero writes; every `0xD18` ref in the listing is `mov rax,[rbp+0xD18]` / `movzx ... [rbp+0xD22]`) and NO [reg+0x28] store exists anywhere in sub_66d0a00 (all 57 '+0x28]' refs are reads/cmp or stack [rsp+0x28] spills). => sub_66d0a00 is a CONSUMER: the slot array and record+0x28 are set by its caller / upstream material-registration code.
- sub_66b2b30's object (~0x58 bytes, kind u32 at +0x00 = 1-8) is a DIFFERENT object from the uniform node: it zeroes +0x18..0x33 (incl. +0x28) via movups and writes +0x00/+0x04/+0x08/+0x0C/+0x0D/+0x0E/+0x10/+0x14, never a hash to +0x28.
- fld_0x28_w_full.txt (248,771 writes over all .text): 161,580 non-stack [reg+0x28] writes, NONE in the 0x66d9af0 extractor or bindMaterial 0xe86d7f0 range — all generic small-helper struct writes; no record+0x28 writer found anywhere in .text.
- Live: capture bucket VA 0x3459FFF0F00 stale/unreadable (heap moved); re-capture is orchestrator-only, no live bucket/record anchor available.
=> record+0x28 WRITER and record CREATION remain upstream of this unit's code (material/uniform registration, before Item visitor 0x6646980 -> sub_66466e0); not reachable statically from 0x66d9af0 / sub_66466e0 / sub_66d0a00.

## Task record layout table (carried [V] rows as anchors; pending rows below)

| name | offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| task RECORD +0x28 = qword task-kind hash (FNV-1a 64 of uniform name) | record+0x28 | 8 | `0x66dc923  cmp [r10+0x28],r8` (r10 = [slot+0x00] = record pointer; r8 = uniform-name hash `0x66dc908  mov r8,[0x129F9128]`); same cmp at `0x66dcae3`, `0x66dcb33`, `0x66dce03`, `0x66dce73`, `0x66dd013`, `0x66dd1b3`, `0x66dd353`, `0x66dd4f3`, `0x66dd693`, `0x66dd833`, `0x66ddaf3`, `0x66ddc53`, `0x66dddc3`, `0x66dea53`, `0x66de103`, `0x66de263`, `0x66de373`, `0x66de533`, `0x66df283`, `0x66df483` (21 cmp sites in 0x66dc900..0x66de900); bindMaterial reads `0xe86d91f  mov r12,[rax+0x28]`, `0xe86da25  cmp [rdx+0x28],rcx`, `0xe86db47  cmp [rsi+0x28],rcx`, `0xe86e399  mov r10,[rax+0x28]`, `0xe86e519  mov rax,[rdx+0x28]` | [V] |
| task RECORD +0x30 = u16 field (uniform node) | record+0x30 | 2 | `0xe86da3b  movzx eax,word ptr [rax+0x30]`; `0xe86db5d  movzx eax,word ptr [rax+0x30]` (rax = record pointer from slot+0x00) | [V] |
| task RECORD +0x32 = u16 field (uniform node) | record+0x32 | 2 | `0xe86da0c  movzx ecx,word ptr [rax+0x32]`; `0xe86db35  movzx ecx,word ptr [rax+0x32]`; same at `0xe86df59`, `0xe86dfc2`, `0xe86e08f`, `0xe86e0d7`, `0xe86e104`, `0xe86e413`, `0xe86e503` | [V] |
| task RECORD +0x34 = u8 flag (bindMaterial processes record only when == 1) | record+0x34 | 1 | `0xe86d910  cmp byte ptr [rax+0x34],1`; same at `0xe86db11`, `0xe86df12`, `0xe86e38a` (rax/rsi = record pointer from slot+0x00) | [V] |
| sub_66d0a00 writes scratch-record +0x04 after sub_66b2b30, NOT +0x28 (proves sub_66b2b30 record != uniform node) | record+0x04 | 1 | `0x66d2f65  and byte ptr [rbp+0x474],0xF7` (rec = [rbp+0x470] created at `0x66d2f5f  call 0x66B2B30`); `0x66d3435  mov byte ptr [rbp+0x21C],1` (rec = [rbp+0x208] created at `0x66d3423  call 0x66B2B30`) | [V] |
| task RECORD size | record SIZE | ? | — (no allocator, no size immediate, no record creation in this unit's code) | [?] |
| task RECORD fields other than +0x28/+0x30/+0x32/+0x34 | record+0x00..+0x27,+0x35.. | ? | — (no store/read of any other record field in 0x66d9af0 or 0xe86d7f0) | [?] |
| slot +0x00 = qword record pointer (context: how the record is reached) | slot+0x00 | 8 | `0x66dc920  mov r10,[rcx]` (rcx walks slot array [rbx+0x38], stride 0x10); `0xe86d90d  mov rax,[r14]` (bindMaterial) | [V] context |
| slot +0x08 = u16 data index (context) | slot+0x08 | 2 | `0x66dc94f  movzx r8d,word ptr [rax+rdx+8]` | [V] context |
| slot +0x0C = u8 occupied/dirty flag (context) | slot+0x0C | 1 | `0x66dc976  mov byte ptr [rax+rdx+0xC],1` | [V] context |
| bucket+0x28 u64 data size (context) | bucket+0x28 | 8 | `0x66dc955  cmp [rbx+0x28],r8` | [V] context |
| bucket+0x30 qword data-array pointer (context) | bucket+0x30 | 8 | `0x66dc966  mov r10,[rbx+0x30]` | [V] context |
| bucket+0x38 qword slot-table pointer (context) | bucket+0x38 | 8 | `0x66dc8f1  mov rax,[rbx+0x38]` | [V] context |
| bucket+0x42 u16 slot count (context) | bucket+0x42 | 2 | `0x66dc8f5  movzx r8d,word ptr [rbx+0x42]` | [V] context |
| bucket+0x48 qword record-table pointer (context; 0x30-stride entries, +0x00 = record ptr) | bucket+0x48 | 8 | `0x66ddaf0  mov r10,[rcx]` walking [rbx+0x48]; `0x66ddaf3  cmp [r10+0x28],r8`; `0x66ddaf9  add rcx,0x30` | [V] context |
| bucket+0x52 u16 record count (context) | bucket+0x52 | 2 | `0xe86db98  movzx eax,word ptr [rsi+0x52]` | [V] context |
| bucket+0x78 qword hash accumulator (context) | bucket+0x78 | 8 | `0x66dc981  mov rcx,[rbx+0x78]` | [V] context |

## CLOSES?

NO — blocking fact: record SIZE, record+0x28 WRITER, and fields other than +0x28/+0x30/+0x32/+0x34 are not provable by [V] rows; creation site is upstream of this unit's code, no static path or live anchor reaches it. Only record+0x28 (qword FNV-1a hash), +0x30 (u16), +0x32 (u16), +0x34 (u8 flag) are [V].

## Verification

- verify_oc.py: claimed=29 match=29 mismatch=0 no-such-instr=0 [PASS].
- delegate.py check: CHECK OK 17 rows, exit 0 [PASS]. Line after "## NEXT" set to DONE.

## TOOL REQUESTS

- None yet.
