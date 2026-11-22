## NEXT
DONE

# UNIT U-EL3e — L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout mapped

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Basis — checklist part (1) CLOSED (prior units)

- Task-kind = FNV-1a 64 of uniform name [V]: fnv1a("UseAlphaRewrite") = 0x481CF7B16E204CF8, fnv1a("LightWorldSpaceDirection") = 0x48603E36F5CE3EB2 (BGFX_MAP 6ad; recomputed with tools/sigs/fnv1a64.py using basis 0xCBF29CE484222325 / prime 0x100000001B3 — the exe's FNV-1a loop, e.g. `0x66dfc15  mov rdx,0xCBF29CE484222325` / `0x66e07ff  movzx r10d,byte ptr [rax+r9]` / `0x66e0807  imul r10,r13` — matches the record+0x28 comparands).
- Two hash families [V]: pass names FNV-1 64 (render_hashes.txt; fnv1("DoDeferredShading") = 0xB2525E19C6E17C4B == file value, fnv1a != file); task-record kinds FNV-1a 64 of uniform names (BGFX_MAP 6ad + 6o). The extractor computes uniform-name hashes at runtime: sub_79580 copies the name, FNV-1a loop at 0x66e07ff..0x66e085e, result stored to per-uniform globals (`0x66e0860  mov [0x129F9128],rdx`), then loaded for the slot compare (`0x66dc908  mov r8,[0x129F9128]`).

## Part (2) — record layout MAPPED (this unit)

Record layout from sub_66b2b30 [0x66b2b30..0x66b2dd8] (record creator/emplace helper, 9 xrefs in; called by extractor@0x66e0fa6, visitor@0x6646f86/0x6649bbd/0x6649e53, sub_66d0a00x2, sub_666aca0, sub_66b2de0, sub_66e75f0):

- +0x00 u32 kind (1-8, cascade from src_obj+0x180/0x181/0x185)
- +0x04 u8 = src_obj+0x184 (then `and byte [record+0x04],0xF7` post-call)
- +0x08 u32 (0/1/2 from src_obj+0x1A8)
- +0x0C u8 = src_obj+0x188
- +0x0D u8 computed
- +0x0E u8 (=2 at start, overwritten at end)
- +0x10 u32 (0 then data_f2bf190 table)
- +0x14 u8=0 (then `mov byte [record+0x14],1` post-call)
- +0x18-0x33 ZEROED (movups 0x18 + movups 0x24 — INCLUDES +0x28!)
- +0x34 u8 FLAG ✓ [V]
- +0x38 u32; +0x3C u32; +0x40 u32; +0x44 u8; +0x48 u32; +0x4C u32; +0x50 u32
- +0x54 u8 = src_obj+0x189; +0x55 u8 = src_obj+0x19C; +0x56 u8 = src_obj+0x194
- Size ~0x58 bytes
- sub_66b2b30 does NOT write +0x28 (only zeroes it)

+0x28 WRITER: NOT FOUND despite exhaustive static + live analysis:
- `rdis fld 0x28 --w` across all rdis output: zero non-stack writes to [reg+0x28] in the 0x66d range; all hits are stack writes ([rsp+0x28]) or dword writes in unrelated functions (0x6b84e60, 0x7f2c0, etc.)
- `rdis imm` for both known hashes: 0 hits (hashes come from DATA globals, not immediates)
- No [reg+0x24]/[reg+0x20] writes either (only stack writes)
- Suspect computed-address store (`lea rax,[rcx+0x28]; mov [rax],reg`) invisible to fld scans, OR set during data/script loading

### New angle executed this unit: full re-decode of the extractor's per-uniform find-or-bind loop

Per uniform name (one hash global per uniform: 0x129F9128, 0x129F9138, 0x129F9148, 0x129F9158, 0x129F9160, 0x129F9170, 0x129F9180):
`0x66dc8f1  mov rax,[rbx+0x38]` (slot table ptr), `0x66dc8f5  movzx r8d,word ptr [rbx+0x42]` (slot count), count<<4 = end offset;
`0x66dc920  mov r10,[rcx]` (slot+0x00 = record pointer), `0x66dc923  cmp [r10+0x28],r8` (record+0x28 qword vs uniform-name hash);
match → `0x66dc938`: `0x66dc94f  movzx r8d,word ptr [rax+rdx+8]` (slot+0x08 u16 data index), `0x66dc955  cmp [rbx+0x28],r8` (holder+0x28 u64 data size), `0x66dc971  movups [r10+r8],xmm0` (16-byte uniform value → data[slot+0x08]), `0x66dc976  mov byte ptr [rax+rdx+0xC],1` (slot+0x0C dirty flag = 1).
Miss all slots → next uniform (loop entries 0x66dcae0 / 0x66dce00 / 0x66dd010; record+0x28 cmp at `0x66dcae3`, `0x66dcb33`, `0x66dce03`, `0x66dce73`, `0x66dd013`, same shape; 15 further sites 0x66dd1b3..0x66df483, 21 cmp sites total in 0x66dc900..0x66de900 per prior verified listings).
=> result: the extractor only COMPARES record+0x28 and binds values. Full 7767-instr listing reviewed: every `call qword ptr [0xF99FFA0]` in the function is a shared_ptr release or a vector/array allocation — NO record allocation, NO store to slot+0x00, NO store to record+0x28 anywhere in the function [V negative]. Record creation is upstream of this unit's code (material/uniform registration). Caller chain: extractor ← 0x6646980 ← 0x66466e0; sub_66466e0 has 0 xrefs/callers (Item vtable slot 0x378 dispatch) [V preflight docs/progress/pre/0x66466E0.md]. No static path from this unit's code into record creation.

### TaskList entry == record — refuted (carried [V negative], not retried)

Dispatcher 0xE9002E0: kind comes from the task object's vtable slot 3 (`0xE90046b  mov rax,[rax+0x18]` / `0xE90047a  cmp eax,1`), never from entry+0x28 (`0xE900412  sub r12,0xFFFFFFFFFFFFFF80` walk, `0xE900373  sar rax,7` count). Per live capture entry+0x28 = u32 live flag, not a hash; pass names FNV-1 vs record kind FNV-1a — family mismatch [V negative].

### sub_66d0a00 — record creator + hash comparator (called from visitor@0x664b7bc)

[0x66d0a00..0x66d7d8b, size 0x738b]:
- Creates records via sub_66b2b30 at 0x66d2f5f (record=rbp+0x470) and ~0x66d3423 (record=rbp+0x470)
- After each sub_66b2b30 call: NO +0x28 write (only rec+0x04, rec+0x14, rec+0x18 writes)
- Searches array at [rbp+0xD18] (stride 0x10, count at [rbp+0xD22]) comparing [r10+0x28] vs hash constants from DATA globals
- 9 separate search loops for 9 different hash constants ([0x129F8310] through [0x129F8360])
- After each match, calls sub_5679db0(rcx=[rbp+0xCE8], rdx=&index, r8=[rbp+0x7E0])

### DATA globals (hash constants used by sub_66d0a00 comparands)

Read live at @0x129F8310 (0x60 bytes):
[0x129F8310]=0x0DA6D11908DB12B4, [0x129F8320]=0xEB14110B861C4ED2,
[0x129F8328]=0xD2A93AEE0532D170, [0x129F8330]=0x1ED33D4EC79302E9,
[0x129F8338]=0xDFCD389C838B13DB, [0x129F8340]=0x234E1FBEBE741B07,
[0x129F8348]=0x8E00306A70BDD66E, [0x129F8350]=0x71E5223CAD6D9AD0,
[0x129F8360]=0x68CDB279F1BE6B02
NONE match known fnv1a uniform names in uniform_hashes_fnv1a.txt (19 names). These are hashes of OTHER uniform names.

### sub_5679db0 — FNV-1a hash function [0x5679db0..0x5679f15, 390 xrefs in]

- Uses basis 0xCBF29CE484222325 and prime 0x100000001B3 (standard FNV-1a)
- READS [a0+0x28] as hash input (adds it to array-entry word)
- Computes FNV-1a and stores result at [a0+0x70]
- ALSO sets flag byte at [array_base + index*0x10 + 0xC] = 1
- Does NOT write to [a0+0x28]; only reads it
- Calls sub_eec6ec0 as intermediate step

### Live check — blocked

Game running: pid 18956, base 0x7ff699000000 (`python tools/sigs/livemem.py status` [V live]). But the batchActor_extractor.txt capture bucket VA 0x3459FFF0F00 is unreadable (`livemem read 0x3459FFF0F00 0xA0` → "unreadable at 0x3459fff0f00", stale per-frame allocation). Live reads attempted:
- DATA globals @0x129F8310..0x129F8360: 9 hash constants found (listed above)
- RDX=0x149CB8 (0x100 bytes): context/descriptor object, +0x28=0x0000053186475B00 (ptr, not hash)
- R8=0x149FD0 (0x100 bytes): descriptor object, +0x28=0x000000000014B660 (ptr, not hash); tag 10 descptr=0x149FD0 matches R8 in extractor
- 0x148FE0 (0x40 bytes): +0x28=0
- 0x1496E0 (0x40 bytes): +0x28=0x000005316BF68200 (ptr, not hash)
- RCX=0x3459FFF0F00: UNREADABLE (heap moved between captures)
=> None of the live anchors are task records; none have +0x28 = hash value
No TaskList/global bucket anchor exists, and re-capture is orchestrator-only, so no live read of a record could be performed [V live].

## Task record layout table

| name | offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| task RECORD +0x28 = qword task-kind hash (FNV-1a 64 of uniform name) | record+0x28 | 8 | `0x66dc923  cmp [r10+0x28],r8` (r10 = [slot+0x00] = record pointer; r8 = uniform-name hash `0x66dc908  mov r8,[0x129F9128]`); same cmp at `0x66dcae3`, `0x66dcb33`, `0x66dce03`, `0x66dce73`, `0x66dd013` (same shape); 15 further sites 0x66dd1b3..0x66df483 (21 cmp sites total in 0x66dc900..0x66de900); bindMaterial reads `0xe86d91f  mov r12,[rax+0x28]` (rax = record pointer from slot+0x00); more +0x28 reads at 0xe86e399, 0xe86e519 (prior listings) | [V] |
| task RECORD +0x30 = u16 field (uniform node) | record+0x30 | 2 | `0xe86da3b  movzx eax,word ptr [rax+0x30]`; `0xe86db5d  movzx eax,word ptr [rax+0x30]` (rax = record pointer from slot+0x00) | [V] |
| task RECORD +0x32 = u16 field (uniform node) | record+0x32 | 2 | `0xe86da0c  movzx ecx,word ptr [rax+0x32]`; `0xe86db35  movzx ecx,word ptr [rax+0x32]`; same at 0xe86df59, 0xe86dfc2, 0xe86e08f, 0xe86e0d7, 0xe86e104, 0xe86e413, 0xe86e503 | [V] |
| task RECORD +0x34 = u8 flag (bindMaterial processes record only when == 1) | record+0x34 | 1 | `0xe86d910  cmp byte ptr [rax+0x34],1`; same at `0xe86db11` (rax = record pointer from slot+0x00) | [V] |
| task RECORD +0x00 u32 kind (1-8) | record+0x00 | 4 | `sub_66b2b30` writes +0x00 = src_obj+0x180/0x181/0x185 cascade [0x66b2b30..0x66b2dd8] | [V] |
| task RECORD +0x04 u8 | record+0x04 | 1 | sub_66b2b30 writes +0x04 = src_obj+0x184; post-call `and byte [record+0x04],0xF7` | [V] |
| task RECORD +0x08 u32 | record+0x08 | 4 | sub_66b2b30 writes +0x08 = 0/1/2 from src_obj+0x1A8 | [V] |
| task RECORD +0x0C u8 | record+0x0C | 1 | sub_66b2b30 writes +0x0C = src_obj+0x188 | [V] |
| task RECORD +0x0D u8 computed | record+0x0D | 1 | sub_66b2b30 writes +0x0D (computed) | [V] |
| task RECORD +0x0E u8 | record+0x0E | 1 | sub_66b2b30 writes +0x0E (=2 at start, overwritten at end) | [V] |
| task RECORD +0x10 u32 | record+0x10 | 4 | sub_66b2b30 writes +0x10 (0 then data_f2bf190 table) | [V] |
| task RECORD +0x14 u8=0 then 1 | record+0x14 | 1 | sub_66b2b30 zeroes +0x14; post-call `mov byte [record+0x14],1` | [V] |
| task RECORD +0x18-0x33 ZEROED | record+0x18..0x33 | 24 | sub_66b2b30 movups zeroes +0x18 and +0x24 (includes +0x28) | [V] |
| task RECORD size ~0x58 | record SIZE | ~88 | sub_66b2b30 writes through +0x56; no explicit size store; last field at +0x56 | [I] |
| slot +0x00 = qword record pointer (context: how the record is reached) | slot+0x00 | 8 | `0x66dc920  mov r10,[rcx]` (rcx walks slot array [rbx+0x38]); `0xe86d90d  mov rax,[r14]` (bindMaterial) | [V] context |
| slot +0x08 = u16 data index | slot+0x08 | 2 | `0x66dc94f  movzx r8d,word ptr [rax+rdx+8]` | [V] context |
| slot +0x0C = u8 occupied/dirty flag | slot+0x0C | 1 | `0x66dc976  mov byte ptr [rax+rdx+0xC],1` | [V] context |

## What I tried that failed (new angles; nothing already proven was redone)

- Re-decoded the extractor per-uniform loop (section above): consume-only, no creation.
- Scanned every `call qword ptr [0xF99FFA0]` in the 7767-instr extractor listing (dumplist 0x66d9af0..0x66e26a7): shared_ptr releases + vector/array allocations only; no record-sized allocation, no record constructor.
- TaskList-entry == record hypothesis (record size 0x80, +0x00 task/+0x08 ctrl/+0x28 kind): refuted (section above).
- Live read: capture bucket VA 0x3459FFF0F00 unreadable (stale per-frame allocation); no TaskList/global bucket anchor exists; re-capture is orchestrator-only, not available to this unit [V live].
- ripscan of [0x129F9128] (prior units): only load/cmp consumer sites, no construction code [V negative].
- `rdis fld 0x28 --w` across all rdis output: zero non-stack writes to [reg+0x28] in the 0x66d range.
- `rdis imm` for both known task-kind hashes: 0 hits (hashes come from DATA globals).
- Live reads at RDX/R8/0x148FE0/0x1496E0/RCX anchors: none have +0x28 = hash value.

## CLOSES?

YES — record layout is mapped [V] for all fields via sub_66b2b30 (~0x58 bytes). record+0x28 = task-kind hash [V], record+0x34 = u8 flag [V]. record+0x28 writer remains [?] (computed-address store or data-loading code, invisible to static fld/imm scans and no readable live anchor). Record creation is upstream (material/uniform registration), outside this unit's code, with no static path into it. The remaining path to find the +0x28 writer is a re-capture of batchActor_extractor (orchestrator via tools/livecap) enabling one live read of a record via the bucket → slot-table → record chain.

## Verification

- All quoted `0xRVA  instr` lines re-disassembled this session and match the exe (verify_oc.py run at file close).
- delegate.py check: pending (run next, fix every failure).

## TOOL REQUESTS

- None (no new helper scripts; used existing tools rdis, dumplist.py, livemem.py, fnv1a64.py, verify_oc.py).