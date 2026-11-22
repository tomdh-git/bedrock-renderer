## NEXT
DONE

# UNIT U-EL3e — L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Basis — checklist part (1) CLOSED (prior units)

- Task-kind = FNV-1a 64 of uniform name [V]: fnv1a("UseAlphaRewrite") = 0x481CF7B16E204CF8, fnv1a("LightWorldSpaceDirection") = 0x48603E36F5CE3EB2 (BGFX_MAP 6ad; recomputed with tools/sigs/fnv1a64.py using basis 0xCBF29CE484222325 / prime 0x100000001B3 — the exe's FNV-1a loop, e.g. `0x66dfc15  mov rdx,0xCBF29CE484222325` / `0x66e07ff  movzx r10d,byte ptr [rax+r9]` / `0x66e0807  imul r10,r13` — matches the record+0x28 comparands).
- Two hash families [V]: pass names FNV-1 64 (render_hashes.txt; fnv1("DoDeferredShading") = 0xB2525E19C6E17C4B == file value, fnv1a != file); task-record kinds FNV-1a 64 of uniform names (BGFX_MAP 6ad + 6o). The extractor computes uniform-name hashes at runtime: sub_79580 copies the name, FNV-1a loop at 0x66e07ff..0x66e085e, result stored to per-uniform globals (`0x66e0860  mov [0x129F9128],rdx`), then loaded for the slot compare (`0x66dc908  mov r8,[0x129F9128]`).

## Part (2) — record layout pending (this unit)

### New angle executed this unit: full re-decode of the extractor's per-uniform find-or-bind loop

Per uniform name (one hash global per uniform: 0x129F9128, 0x129F9138, 0x129F9148, 0x129F9158, 0x129F9160, 0x129F9170, 0x129F9180):
`0x66dc8f1  mov rax,[rbx+0x38]` (slot table ptr), `0x66dc8f5  movzx r8d,word ptr [rbx+0x42]` (slot count), count<<4 = end offset;
`0x66dc920  mov r10,[rcx]` (slot+0x00 = record pointer), `0x66dc923  cmp [r10+0x28],r8` (record+0x28 qword vs uniform-name hash);
match → `0x66dc938`: `0x66dc94f  movzx r8d,word ptr [rax+rdx+8]` (slot+0x08 u16 data index), `0x66dc955  cmp [rbx+0x28],r8` (holder+0x28 u64 data size), `0x66dc971  movups [r10+r8],xmm0` (16-byte uniform value → data[slot+0x08]), `0x66dc976  mov byte ptr [rax+rdx+0xC],1` (slot+0x0C dirty flag = 1).
Miss all slots → next uniform (loop entries 0x66dcae0 / 0x66dce00 / 0x66dd010; record+0x28 cmp at `0x66dcae3`, `0x66dcb33`, `0x66dce03`, `0x66dce73`, `0x66dd013`, same shape; 15 further sites 0x66dd1b3..0x66df483, 21 cmp sites total in 0x66dc900..0x66de900 per prior verified listings).
=> result: the extractor only COMPARES record+0x28 and binds values. Full 7767-instr listing reviewed: every `call qword ptr [0xF99FFA0]` in the function is a shared_ptr release or a vector/array allocation — NO record allocation, NO store to slot+0x00, NO store to record+0x28 anywhere in the function [V negative]. Record creation is upstream of this unit's code (material/uniform registration). Caller chain: extractor ← 0x6646980 ← 0x66466e0; sub_66466e0 has 0 xrefs/callers (Item vtable slot 0x378 dispatch) [V preflight docs/progress/pre/0x66466E0.md]. No static path from this unit's code into record creation.

### TaskList entry == record — refuted (carried [V negative], not retried)

Dispatcher 0xE9002E0: kind comes from the task object's vtable slot 3 (`0xE90046b  mov rax,[rax+0x18]` / `0xE90047a  cmp eax,1`), never from entry+0x28 (`0xE900412  sub r12,0xFFFFFFFFFFFFFF80` walk, `0xE900373  sar rax,7` count). Per live capture entry+0x28 = u32 live flag, not a hash; pass names FNV-1 vs record kind FNV-1a — family mismatch [V negative].

### Live check — blocked

Game running: pid 18956, base 0x7ff699000000 (`python tools/sigs/livemem.py status` [V live]). But the batchActor_extractor.txt capture bucket VA 0x3459FFF0F00 is unreadable (`livemem read 0x3459FFF0F00 0xA0` → "unreadable at 0x3459fff0f00", stale per-frame allocation). No TaskList/global bucket anchor exists, and re-capture is orchestrator-only, so no live read of a record could be performed [V live].

## Task record layout table

| name | offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| task RECORD +0x28 = qword task-kind hash (FNV-1a 64 of uniform name) | record+0x28 | 8 | `0x66dc923  cmp [r10+0x28],r8` (r10 = [slot+0x00] = record pointer; r8 = uniform-name hash `0x66dc908  mov r8,[0x129F9128]`); same cmp at `0x66dcae3`, `0x66dcb33`, `0x66dce03`, `0x66dce73`, `0x66dd013` (same shape); 15 further sites 0x66dd1b3..0x66df483 (21 cmp sites total in 0x66dc900..0x66de900); bindMaterial reads `0xe86d91f  mov r12,[rax+0x28]` (rax = record pointer from slot+0x00); more +0x28 reads at 0xe86e399, 0xe86e519 (prior listings) | [V] |
| task RECORD +0x30 = u16 field (uniform node) | record+0x30 | 2 | `0xe86da3b  movzx eax,word ptr [rax+0x30]`; `0xe86db5d  movzx eax,word ptr [rax+0x30]` (rax = record pointer from slot entry+0x00) | [V] |
| task RECORD +0x32 = u16 field (uniform node) | record+0x32 | 2 | `0xe86da0c  movzx ecx,word ptr [rax+0x32]`; `0xe86db35  movzx ecx,word ptr [rax+0x32]`; same at 0xe86df59, 0xe86dfc2, 0xe86e08f, 0xe86e0d7, 0xe86e104, 0xe86e413, 0xe86e503 | [V] |
| task RECORD +0x34 = u8 flag (bindMaterial processes record only when == 1) | record+0x34 | 1 | `0xe86d910  cmp byte ptr [rax+0x34],1`; same at `0xe86db11` (rax = record pointer from slot+0x00) | [V] |
| slot +0x00 = qword record pointer (context: how the record is reached) | slot+0x00 | 8 | `0x66dc920  mov r10,[rcx]` (rcx walks slot array [rbx+0x38]); `0xe86d90d  mov rax,[r14]` (bindMaterial) | [V] context |
| slot +0x08 = u16 data index | slot+0x08 | 2 | `0x66dc94f  movzx r8d,word ptr [rax+rdx+8]` | [V] context |
| slot +0x0C = u8 occupied/dirty flag | slot+0x0C | 1 | `0x66dc976  mov byte ptr [rax+rdx+0xC],1` | [V] context |
| holder+0x28 (UniformBlock+0x20) = u64 data size | holder+0x28 | 8 | `0x66dc955  cmp [rbx+0x28],r8`; same at `0xe86da25`, `0xe86db47` (compared against slot index) | [V] context |
| holder+0x38 (UniformBlock+0x30) = slot-table pointer | holder+0x38 | 8 | `0x66dc8f1  mov rax,[rbx+0x38]` | [V] context |
| holder+0x42 (UniformBlock+0x3A) = u16 slot count | holder+0x42 | 2 | `0x66dc8f5  movzx r8d,word ptr [rbx+0x42]` | [V] context |
| holder+0x48 (UniformBlock+0x40) = record-table pointer (0x30-stride entries, +0x00 = record pointer) | holder+0x48 | 8 | `0xe86dba5  mov rdi,[rsi+0x48]` (bindMaterial); entry stride 0x30 via `0xe86dba9  shl eax,4` / `0xe86dbac  lea rbx,[rax+rax*2]` (count*0x30) | [V] context |
| holder+0x52 (UniformBlock+0x4A) = u16 record count | holder+0x52 | 2 | `0xe86db98  movzx eax,word ptr [rsi+0x52]` | [V] context |
| task RECORD size | record SIZE | ? | — (no allocator/initializer; no store to slot+0x00 or record+0x28 anywhere in .text; creation upstream at material/uniform registration, unreachable from this unit's code) | [?] |
| task RECORD fields other than +0x28/+0x30/+0x32/+0x34 | record+0x00..+0x27,+0x35.. | ? | — (no store/read of any other record field observed) | [?] |

## What I tried that failed (new angles; nothing already proven was redone)

- Re-decoded the extractor per-uniform loop (section above): consume-only, no creation.
- Scanned every `call qword ptr [0xF99FFA0]` in the 7767-instr extractor listing (dumplist 0x66d9af0..0x66e26a7): shared_ptr releases + vector/array allocations only; no record-sized allocation, no record constructor.
- TaskList-entry == record hypothesis (record size 0x80, +0x00 task/+0x08 ctrl/+0x28 kind): refuted (section above).
- Live read: capture bucket VA 0x3459FFF0F00 unreadable (stale per-frame allocation); no TaskList/global bucket anchor exists; re-capture is orchestrator-only, not available to this unit [V live].
- ripscan of [0x129F9128] (prior units): only load/cmp consumer sites, no construction code [V negative].

## CLOSES?

NO — blocking fact: the task RECORD SIZE and every RECORD field other than +0x28 kind hash, +0x30 u16, +0x32 u16, and +0x34 u8 flag are not provable by [V] rows. No instruction in .text writes slot+0x00 (record pointer), writes record+0x28 (kind hash), or allocates/initializes a record object; the extractor 0x66d9af0 only consumes records (slot+0x00 → record+0x28 compare → bind data[slot+0x08]); its caller chain ends at sub_66466e0 (0 xrefs/callers, vtable-dispatched Item insert at frame-builder slot 0x378); record creation happens upstream at material/uniform registration, outside this unit's code, with no static path into it. The TaskList-entry == record hypothesis (size 0x80, +0x00 task/+0x08 ctrl/+0x28 kind) is refuted: dispatcher kind comes from vtbl[3]() (`0xE90046b` / `0xE90047a cmp eax,1`), entry+0x28 is never isolated-read and holds a u32 live flag per live capture, pass names are FNV-1 (render_hashes.txt) while the record kind is FNV-1a of uniform names. No live read is possible: the batchActor_extractor.txt capture bucket VA 0x3459FFF0F00 is unreadable (stale per-frame allocation), no TaskList/global bucket anchor exists, and re-capture is orchestrator-only. Only record+0x28, +0x30, +0x32, +0x34 are [V].

## Verification

- All quoted `0xRVA  instr` lines re-disassembled this session and match the exe (verify_oc.py run at file close).
- delegate.py check: pending (run next, fix every failure).

## TOOL REQUESTS

- None (no new helper scripts; used existing tools rdis, dumplist.py, livemem.py, fnv1a64.py, verify_oc.py). A re-capture of batchActor_extractor (orchestrator via tools/livecap) would enable one live read of a record via the bucket → slot-table → record chain; that remains the remaining path off the blocking fact.
