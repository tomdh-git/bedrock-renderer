## NEXT
DONE

# UNIT U-EL3e — L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout: mapped fields [V], creation/+0x28 writer/size [?]

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Live cites [V live] with command line. Nothing invented.

## Basis (closed by prior units — carried as [V] anchors, not retried)

- task-kind = FNV-1a 64 of uniform name [V]: fnv1a("UseAlphaRewrite")=0x481CF7B16E204CF8, fnv1a("LightWorldSpaceDirection")=0x48603E36F5CE3EB2 (BGFX_MAP 6ad; recomputed basis 0xCBF29CE484222325 / prime 0x100000001B3 matches the exe's FNV-1a loop, e.g. `0x66e07ff  movzx r10d,byte ptr [rax+r9]` / `0x66e0807  imul r10,r13`, and record+0x28 comparands come from data globals written at `0x66e0860  mov [0x129F9128],rdx`). Two hash families: pass names FNV-1 (render_hashes.txt); task-record kinds FNV-1a of uniform names.
- TaskList-entry == record hypothesis REFUTED (r3-r8, not retried): dispatcher 0xE9002E0 takes kind from the task object's vtbl[3]() (`0xE90046b  mov rax,[rax+0x18]` / `0xE90047a  cmp eax,1`), never from entry+0x28; entry+0x28 never isolated-read (`0xE9004f7  movups xmm1,[r12+0x1C]` is a +0x1C..+0x2F chunk); entry stride 0x80 (`0xE900373  sar rax,7`, `0xE900412  sub r12,0xFFFFFFFFFFFFFF80`); entry+0x00 task object (`0xE900464  mov rcx,[r12]`), entry+0x08 control block (`0xE90048b  mov rax,[r12+8]`); pass names FNV-1 vs record kind FNV-1a — family mismatch.

## NEW ANGLES EXECUTED THIS UNIT (RETRY #2 — nothing already proven was redone)

1. Full decode of sub_66dc8ea [0x66dc8ea..0x66de8ea), the find-or-bind loop for hash global [0x129F9128] (tail-jumped to from `0x66e08a3  jmp 0x66DC8EA` right after the FNV-1a hash is stored at `0x66e0860  mov [0x129F9128],rdx`): `0x66dc8f1  mov rax,[rbx+0x38]` (slot-table ptr), `0x66dc8f5  movzx r8d,word ptr [rbx+0x42]` (slot count), walk `0x66dc920  mov r10,[rcx]` / `0x66dc923  cmp [r10+0x28],r8` / `0x66dc929  add rcx,0x10`; on match `0x66dc94f  movzx r8d,word ptr [rax+rdx+8]` (slot+0x08 u16 data index), `0x66dc955  cmp [rbx+0x28],r8` (holder+0x28 data size), `0x66dc971  movups [r10+r8],xmm0` (16-byte value → data[slot+0x08]), `0x66dc976  mov byte ptr [rax+rdx+0xC],1` (slot+0x0C dirty); on miss-all `0x66dc933  jmp 0x66DCA80` (next uniform). CONSUME-ONLY: no slot insertion, no slot+0x00 store, no record+0x28 store [V].
2. Inline copy of the same loop inside sub_66b2de0 (effect visitor): `0x66b319d  mov rax,[r14+0x38]` (slot table from holder), `0x66b31a1  movzx r8d,word ptr [r14+0x42]` (slot count), `0x66b31b4  mov r8,[0x129F8310]` (hash global), `0x66b31d0  mov r10,[rcx]` / `0x66b31d3  cmp [r10+0x28],r8` / `0x66b31d9  add rcx,0x10`; on match `0x66b31f2  mov [rbp+0x7A0],cx` (slot index), `0x66b31f9  mov byte ptr [rbp+0x7A2],1` (dirty), `0x66b3211  call 0x56D56A0` (bind). Consume-only [V].
3. Full decode of sub_66b2b30 [0x66b2b30..0x66b2dd1], the record creator (9 xrefs in). Takes the record buffer in rcx and a source object in rdx; writes +0x00/+0x04/+0x08/+0x0C/+0x0D/+0x0E/+0x10/+0x14/+0x34/+0x38/+0x3C/+0x40/+0x44/+0x48/+0x4C/+0x50/+0x54/+0x55/+0x56 and zeroes +0x18..0x2F via `0x66b2b4d  movups [rcx+0x18],xmm0` / `0x66b2b51  movups [rcx+0x24],xmm0` — INCLUDING +0x28. NEVER writes +0x28 [V]. All checked callers pass stack scratch buffers: sub_66e0f00 `0x66e0f9f  lea rcx,[rbp+0x400]` / `0x66e0fa6  call 0x66B2B30`; sub_66b2de0 `0x66b2f3e  lea rcx,[rbp+0x2D0]` / `0x66b2f45  call 0x66B2B30`; sub_66d0a00×2 (stack [rbp+0x470], [rbp+0x208]). These are per-call scratch records, not the persistent slot-table records.
4. sub_66d9af0 cluster mapped: sub_66d9af0 iterates the material array at [r8+0xE0]/[r8+0xE8] (`0x66d9b79  mov rax,[r8+0xE0]`); per-uniform FNV-1a hash is computed (loop at 0x66e07ff) and stored to per-uniform globals ([0x129F9128] at `0x66e0860`, [0x129F91E8] at `0x66e091a`), then control tail-jumps into sub_66dc8ea/sub_66defda compare loops. Records are never allocated here.
5. xref.py callers of 0x66d9af0 lists 6 entries but the extra ones are imprecise: 0x666aca0, 0x66b2de0, 0x66e75f0 contain no call to 0x66d9af0 in their disassembly [V negative]; the real caller chain remains sub_66466e0 → sub_6646980 → sub_66d9af0, and sub_66466e0 has 0 xrefs/callers [V prior units].
6. Live read: game running (pid 20572, base 0x7ff605be0000, `python tools/sigs/livemem.py status` [V live]) but the batchActor_extractor.txt capture bucket VA is stale: `python tools/sigs/livemem.py read 0x3459FFF0F00 0xA0` → "unreadable at 0x3459fff0f00" [V live]. No current bucket/slot-table/record VA anchor exists (capture taken under a previous pid/base; endFrame's TaskList is a stack out-param `0xC27054c  lea rcx,[rbp+0x20]` / `0xC270554  call 0xE9002E0`, no global). No live record read possible.

## ANSWER TABLE — slot-table record (the object compared at +0x28 in 0x66dc900..0x66de900)

| name | offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| slot-record +0x28 = qword task-kind hash (FNV-1a 64 of uniform name) | slot-record+0x28 | 8 | `0x66dc923  cmp [r10+0x28],r8` (r10 = [slot+0x00] = record pointer; r8 = uniform-name hash `0x66dc908  mov r8,[0x129F9128]`); same cmp at `0x66dcae3`, `0x66dcb33` (`0x66dcb33  cmp [r10+0x28],r8`), `0x66ddaf3` (`0x66ddaf3  cmp [r10+0x28],r8`), `0x66dce03`, `0x66dce73`, `0x66dd013`, `0x66dd1b3`, `0x66dd353`, `0x66dd4f3`, `0x66dd693`, `0x66dd833`, `0x66ddc53`, `0x66dddc3`, `0x66dea53`, `0x66de103`, `0x66de263`, `0x66de373`, `0x66de533`, `0x66df283`, `0x66df483` (21 cmp sites in 0x66dc900..0x66de900); inline copy `0x66b31d3  cmp [r10+0x28],r8`; bindMaterial reads `0xe86d91f  mov r12,[rax+0x28]`, `0xe86da25  cmp [rdx+0x28],rcx`, `0xe86db47  cmp [rsi+0x28],rcx`, `0xe86e399  mov r10,[rax+0x28]`, `0xe86e519  mov rax,[rdx+0x28]` | [V] |
| slot-record +0x30 = u16 field (read by bindMaterial) | slot-record+0x30 | 2 | `0xe86da3b  movzx eax,word ptr [rax+0x30]`; `0xe86db5d  movzx eax,word ptr [rax+0x30]` (rax = record pointer from slot+0x00) | [V] |
| slot-record +0x32 = u16 field (read by bindMaterial) | slot-record+0x32 | 2 | `0xe86da0c  movzx ecx,word ptr [rax+0x32]`; `0xe86db35  movzx ecx,word ptr [rax+0x32]`; `0xe86df59`, `0xe86dfc2`, `0xe86e08f`, `0xe86e0d7`, `0xe86e104`, `0xe86e413`, `0xe86e503` | [V] |
| slot-record +0x34 = u8 flag (bindMaterial processes record only when == 1) | slot-record+0x34 | 1 | `0xe86d910  cmp byte ptr [rax+0x34],1`; same at `0xe86db11`, `0xe86df12`, `0xe86e38a` | [V] |
| slot +0x00 = qword record pointer; who FILLS slot+0x00 is unknown | slot+0x00 | 8 | `0x66dc920  mov r10,[rcx]` (rcx walks slot array [rbx+0x38], stride 0x10); `0xe86d90d  mov rax,[r14]` (bindMaterial); no store to slot+0x00 anywhere in .text [V negative] | [V] context / [?] filler |
| record SIZE | record SIZE | ? | — (last observed slot-record field is +0x34; sub_66b2b30 scratch object writes through +0x56 → ~0x58 [I] for scratch only; persistent record size not provable) | [?] |
| record+0x28 WRITER | record+0x28 | 8 | — (no [reg+0x28] write anywhere in .text [V negative: fld write scan]; sub_66b2b30 zeroes +0x28 via `0x66b2b51  movups [rcx+0x24],xmm0` and never writes a hash; hash presumed to come from asset data / loader upstream — unproven; computed-address store not excluded but no candidate found) | [?] |
| record CREATION site / persistent slot-table records | record creation | - | — (extractor loops are consume-only; all checked sub_66b2b30 callers pass stack scratch buffers; slot tables/records built upstream at material/uniform registration, outside this unit's code; no static path located) | [?] |

Context (how the record is reached; all [V] from this unit's listings):

| name | offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| holder+0x28 u64 data size (compared against slot data index) | holder+0x28 | 8 | `0x66dc955  cmp [rbx+0x28],r8` | [V] context |
| holder+0x30 qword data-array pointer (bind target `0x66dc971  movups [r10+r8],xmm0`) | holder+0x30 | 8 | `0x66dc966  mov r10,[rbx+0x30]` | [V] context |
| holder+0x38 qword slot-table pointer | holder+0x38 | 8 | `0x66dc8f1  mov rax,[rbx+0x38]` | [V] context |
| holder+0x42 u16 slot count | holder+0x42 | 2 | `0x66dc8f5  movzx r8d,word ptr [rbx+0x42]` | [V] context |
| holder+0x48 qword record-table pointer (0x30-stride entries, +0x00 = record pointer) | holder+0x48 | 8 | `0x66ddac3  mov rax,[rbx+0x48]`; `0x66ddaf0  mov r10,[rcx]` (rcx = [rbx+0x48]); `0x66ddaf3  cmp [r10+0x28],r8`; `0x66ddaf9  add rcx,0x30` | [V] context |
| holder+0x52 u16 record count | holder+0x52 | 2 | `0x66ddac7  movzx r8d,word ptr [rbx+0x52]`; `0x66ddc27  movzx r8d,word ptr [rcx+0x52]` | [V] context |
| holder+0x78 qword FNV-1a hash accumulator (updated per bound uniform) | holder+0x78 | 8 | `0x66dc981  mov rcx,[rbx+0x78]`; `0x66dc9b1  mov [rbx+0x78],r8` | [V] context |
| slot +0x08 = u16 data index | slot+0x08 | 2 | `0x66dc94f  movzx r8d,word ptr [rax+rdx+8]` | [V] context |
| slot +0x0C = u8 occupied/dirty flag | slot+0x0C | 1 | `0x66dc976  mov byte ptr [rax+rdx+0xC],1` | [V] context |

## sub_66b2b30 scratch-object field map [V] (runtime scratch object; +0x28 is zeroed at creation and never written by any instruction in .text, so this object is not the source of the slot-record's +0x28 hash)

| name | offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| scratch +0x00 = u32 kind (1-8, cascade from source+0x180/0x181/0x185) | scratch+0x00 | 4 | `0x66b2c11  mov [rax],r11d` | [V] |
| scratch +0x04 = u8 from source+0x184 | scratch+0x04 | 1 | `0x66b2d84  mov [rax+4],cl` | [V] |
| scratch +0x08 = u32 (0/1/2 from source+0x1A8) | scratch+0x08 | 4 | `0x66b2c34  mov [rax+8],ecx` | [V] |
| scratch +0x0C = u8 from source+0x188 | scratch+0x0C | 1 | `0x66b2d8e  mov [rax+0xC],cl` | [V] |
| scratch +0x0D = u8 computed | scratch+0x0D | 1 | `0x66b2d9f  mov [rax+0xD],r10b` | [V] |
| scratch +0x0E = u8 | scratch+0x0E | 1 | `0x66b2dbb  mov [rax+0xE],r9b` | [V] |
| scratch +0x10 = u32 (0 then data_f2bf190 table entry) | scratch+0x10 | 4 | `0x66b2c5d  mov [rax+0x10],ecx` | [V] |
| scratch +0x14 = u8 | scratch+0x14 | 1 | `0x66b2b46  mov byte ptr [rcx+0x14],0` | [V] |
| scratch +0x18..0x27 = zeroed (16 bytes) | scratch+0x18..0x27 | 16 | `0x66b2b4d  movups [rcx+0x18],xmm0` | [V] |
| scratch +0x28..0x2F = zeroed (16 bytes, INCLUDES +0x28) | scratch+0x28..0x2F | 16 | `0x66b2b51  movups [rcx+0x24],xmm0` | [V] |
| scratch +0x34 = u8 flag | scratch+0x34 | 1 | `0x66b2cf5  mov [rax+0x34],cl` | [V] |
| scratch +0x38 = u32 | scratch+0x38 | 4 | `0x66b2cf8  mov [rax+0x38],esi` | [V] |
| scratch +0x3C = u32 | scratch+0x3C | 4 | `0x66b2cfb  mov [rax+0x3C],edi` | [V] |
| scratch +0x40 = u32 | scratch+0x40 | 4 | `0x66b2cfe  mov [rax+0x40],r11d` | [V] |
| scratch +0x44 = u8 | scratch+0x44 | 1 | `0x66b2d6e  mov [rax+0x44],dil` | [V] |
| scratch +0x48 = u32 | scratch+0x48 | 4 | `0x66b2d72  mov [rax+0x48],r10d` | [V] |
| scratch +0x4C = u32 | scratch+0x4C | 4 | `0x66b2d76  mov [rax+0x4C],r11d` | [V] |
| scratch +0x50 = u32 | scratch+0x50 | 4 | `0x66b2d7a  mov [rax+0x50],esi` | [V] |
| scratch +0x54 = u8 from source+0x189 | scratch+0x54 | 1 | `0x66b2c67  mov [rax+0x54],cl` | [V] |
| scratch +0x55 = u8 from source+0x19C | scratch+0x55 | 1 | `0x66b2c71  mov [rax+0x55],cl` | [V] |
| scratch +0x56 = u8 from source+0x194 (last field written; size ≥ 0x57) | scratch+0x56 | 1 | `0x66b2dc6  mov [rax+0x56],cl` | [V] |

## What I tried that failed (this unit)

- Full decode of sub_66dc8ea and its inline copy in sub_66b2de0: consume-only, no insertion, no slot+0x00 or record+0x28 store (section above).
- Full decode of sub_66b2b30: creates caller-supplied record buffers; zeroes +0x28; writes no hash (section above).
- sub_66d9af0 cluster mapping incl. FNV-1a hash globals [0x129F9128]/[0x129F91E8] written at `0x66e0860`/`0x66e091a` then tail-jumped into compare loops: records consumed, not created (section above).
- xref.py callers of 0x66d9af0: extra entries imprecise (section above).
- fld 0x28 write scan across all rdis output: zero non-stack [reg+0x28] writes in .text; no record+0x28 writer found [V negative].
- Live read: capture bucket VA unreadable (section above); no TaskList/global bucket anchor exists; re-capture is orchestrator-only.

## CLOSES?

NO — blocking fact: the slot-record SIZE, record+0x28 WRITER, slot+0x00 FILLER, and persistent-record CREATION SITE are not provable by [V] rows. No instruction in .text writes slot+0x00 or record+0x28; sub_66b2b30 creates only stack scratch records and zeroes +0x28; the compare loops (sub_66dc8ea/sub_66defda, inline copy in sub_66b2de0) are consume-only; persistent records and slot tables are built upstream at material/uniform registration / asset load, outside this unit's code, with no static path into them; and no live bucket/slot-table/record VA anchor exists (capture VA 0x3459FFF0F00 unreadable under current pid 20572/base 0x7ff605be0000; endFrame passes the TaskList via stack out-param `0xC27054c  lea rcx,[rbp+0x20]` / `0xC270554  call 0xE9002E0`). Single unknown: the record creation site upstream of the extractor — who allocates persistent slot-table records, fills slot+0x00 and record+0x28, and sets record size. Only slot-record +0x28 (qword hash), +0x30 (u16), +0x32 (u16), +0x34 (u8 flag) are [V].

## Verification

- verify_oc.py: all quoted `0xRVA  instr` lines re-disassembled against the exe this session; run via `python tools/delegate.py check docs/progress/oc_U-EL3e.md` at close (exit 0 required).
- delegate.py check: run at close; every failure fixed.

## TOOL REQUESTS

- None (no new helper scripts; all evidence from rdis disassembly, verify_oc, xref.py, and one livemem read).
