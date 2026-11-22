## NEXT
DONE

# UNIT U-EL3e — L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Basis — checklist part (1) "task kind = FNV-1a 64 of uniform name" is CLOSED (prior units, not this unit's work)

Closed by U-C3b/U-C3b2 + BGFX_MAP 6ad [V]: task-record kinds are FNV-1a 64 of uniform names; `0x481CF7B16E204CF8 = fnv1a("UseAlphaRewrite")`, `0x48603E36F5CE3EB2 = fnv1a("LightWorldSpaceDirection")`. Recomputed with basis 0xCBF29CE484222325 / prime 0x100000001B3 (FNV-1a loop in exe, e.g. `0x664707a  mov r10,0xCBF29CE484222325` / `0x6647084  xor rcx,r10` / `0x6647091  imul rcx,rsi`) and they match record+0x28 comparands [V]. BGFX_MAP 6ad states two hash families: pass/material names = FNV-1 64; task-record kinds = FNV-1a 64 of uniform names. render_hashes.txt values are FNV-1 (checked: fnv1("DoDeferredShading") = 0xB2525E19C6E17C4B == file value; fnv1a = 0x573A1853C482D22F != file) [computed check].

## This unit — part (2) "record layout pending": TaskList-entry hypothesis tested, rejected; uniform-node fields confirmed via bindMaterial

Orchestrator hypothesis (RETRY #2): the record compared at +0x28 is the frame TaskList entry itself (stride 0x80, dispatcher 0xE9002E0); entry+0x28 == FNV-1 64 hash of a pass name → record size = 0x80, +0x00 task object, +0x08 control block, +0x28 kind hash, remaining fields need their own readers.

### Dispatcher 0xE9002E0 full decode (0xE9002E0..0xE900F1A, 713 instr, single caller 0xC270460 BgfxContext::endFrame) [V]

- TaskList in rcx: `0xE900366  mov r12,[rcx]` (begin → r12), `0xE900369  mov rdx,[rcx+8]` (end → rdx), count = `0xE900370  sub rax,r12` / `0xE900373  sar rax,7` → (end-begin) >> 7 = 0x80-stride entries.
- Walk: `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` (r12 += 0x80 per entry), loop head `0xE90041a  cmp r12,rdx`.
- Per entry: `0xE900464  mov rcx,[r12]` (entry+0x00 = task object), `0xE900468  mov rax,[rcx]`, `0xE90046b  mov rax,[rax+0x18]`, `0xE90046f  call qword ptr [0xF99FFA0]` → kind in eax; `0xE90047a  cmp eax,1` — kind comes from the task object's vtable slot 3, NOT from entry+0x28.
- `0xE90048b  mov rax,[r12+8]` (entry+0x08 = control block), `0xE900495  lock inc dword ptr [rax+8]`.
- Fields moved per entry: +0x00 `0xE9004e3  movups xmm0,[r12]`; +0x10 `0xE9004f1  movups xmm0,[r12+0x10]`; +0x1C..+0x2F `0xE9004f7  movups xmm1,[r12+0x1C]` (one 16-byte chunk covering entry+0x20..+0x2F, entry+0x28 never isolated); +0x30, +0x40, +0x50, +0x60, +0x70 `0xE90052c  mov rax,[r12+0x70]`, +0x78 `0xE90056b  mov rax,[r12+0x78]`; copied via operator new(0x88) into a new object.
- entry+0x28 is NEVER read or compared in isolation anywhere in 0xE9002E0..0xE900F1A, and no pass-name hash immediate is compared against any entry field [V]. Tail 0xE900EE0..0xE900F1A checked: only error-path calls `0xE900EE1  call 0xEEC59E0`, `0xE900EE7  call 0x75740`, `0xE900F0D  call 0x75B60`, `0xE900F13  call 0x75B60` [V].
- => "entry+0x28 = FNV-1 pass-name hash" NOT supported by disassembly; and it cannot be the record's field anyway: record+0x28 is FNV-1a of a *uniform* name while pass names are FNV-1 (two families, BGFX_MAP 6ad [V]; render_hashes.txt is FNV-1, computed check above).

### Link extractor record ↔ TaskList entry

- Extractor: r10 = `0x66dc920  mov r10,[rcx]` walking the slot array stride 0x10 (`0x66dc929  add rcx,0x10`); r8 = uniform-name hash `0x66dc908  mov r8,[0x129F9128]`; cmp `0x66dc923  cmp [r10+0x28],r8`.
- Buckets are 0x90-stride material holders {MaterialInstance* +0x00, UniformBlock @+0x08} [V EC3b], not 0x80 entries.
- Zero stores to slot+0x00 / record-array entry+0x00 anywhere in .text [V negative: EC3b full listing 0x66d9af0..0x66e26a7 (7767 instr), fld 0x28 write scan 248,770 writes, six FNV-1a callers dumped] — records are created upstream of the extractor; allocator/initializer not found [V negative].
- => No static code makes slot+0x00 point at a TaskList entry; record == entry is not provable either way, and the hypothesis yields no entry+0x28 evidence.

### Live check (attempted)

Game running: pid 18956, base 0x7ff699000000 (`python tools/sigs/livemem.py status` [V live]). But no TaskList pointer anchor exists: no breakpoint/register capture at 0xE9002E0/0xC270460 is permitted (orchestrator-only hook captures), docs/data/live/*.txt captures hold no TaskList address, EC3b's bucket VA 0x3462FDB8020 unreadable now [V live]. livemem read of one entry's +0x28 cannot be performed.

### bindMaterial (0xe86d7f0) — uniform node fields CONFIRMED

The 'record' is a uniform node inside a UniformBlock (holder {MaterialInstance* +0x00, UniformBlock +0x08}; UniformBlock slot table at block+0x30, u16 slot count block+0x3A, 16-byte entries pointing at uniform nodes). bindMaterial walks slot entries and for each node:

- `0xe86d90d  mov rax,[r14]` — rax = [slot_entry+0x00] = uniform node pointer
- `0xe86d910  cmp byte ptr [rax+0x34],1` — [rax+0x34] = u8 flag [V]
- `0xe86d91f  mov r12,[rax+0x28]` — [rax+0x28] = qword FNV-1a name hash [V]
- `0xe86da0c  movzx ecx,word ptr [rax+0x32]` — [rax+0x32] = u16 field [V NEW]
- `0xe86da3b  movzx eax,word ptr [rax+0x30]` — [rax+0x30] = u16 field [V NEW]
- Same pattern at `0xe86db31`/`0xe86db35` (`[rax+0x32]` u16), `0xe86db5d` (`[rax+0x30]` u16)
- Second code path: `0xe86df0d  mov rax,[rdi+r15-0x25]` / `0xe86df12  cmp byte ptr [rax+0x34],1` (flag), `0xe86df59`/`0xe86dfc2`/`0xe86e08f`/`0xe86e0d7`/`0xe86e104` (`[rax+0x32]` u16)
- Third code path: `0xe86e387  mov rax,[rbx]` / `0xe86e38a  cmp byte ptr [rax+0x34],1` (flag), `0xe86e399  mov r10,[rax+0x28]` (hash), `0xe86e413`/`0xe86e503`/`0xe86e7a2` region (`[rax+0x32]` u16)
- Slot entry+0x08 u16 offset compared against [rdx+0x28] (data size) and added to [rdx+0x30] (data base)
- bindMaterial walks MaterialInstance map at +0x368 (buckets +0x380, mask +0x398) using node+0x28 hash
- No stores to uniform node fields observed in bindMaterial (only reads)

Minimum size: ≥ 0x35 bytes (fields end at byte 0x34). Exact size: UNKNOWN — no allocator/initializer found in .text, no store to +0x28 anywhere in .text (hash set upstream during material/uniform registration), no live anchor available. Slot entry (UniformSlot) is 16 bytes at block+0x30: +0x00 qword node pointer, +0x08 u16 offset, +0x0C u8 dirty flag — all confirmed in bindMaterial disassembly.

## Task record layout table

| name | offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| task RECORD +0x28 = qword task-kind hash (FNV-1a 64 of uniform name) | record+0x28 | 8 | `0x66dc923  cmp [r10+0x28],r8` (r10 = [slot+0x00], r8 = uniform-name hash `0x66dc908  mov r8,[0x129F9128]`); same cmp at `0x66dcae3`, `0x66dcb33`, `0x66dce03`, `0x66dce73`, `0x66dd013`, `0x66dd1b3`, `0x66dd353`, `0x66dd4f3`, `0x66dd693`, `0x66dd833`, `0x66ddaf3`, `0x66ddc53`, `0x66dddc3`, `0x66dea53` (`cmp [r8+0x28],rcx`), `0x66de103`, `0x66de263`, `0x66de373`, `0x66de533`, `0x66df283`, `0x66df483` (21 cmp sites in 0x66dc900..0x66de900); bindMaterial reads `0xe86d91f  mov r12,[rax+0x28]`, `0xe86da25  cmp [rdx+0x28],rcx`, `0xe86db47  cmp [rsi+0x28],rcx`, `0xe86e399  mov r10,[rax+0x28]`, `0xe86e519  mov rax,[rdx+0x28]` | [V] |
| task RECORD +0x30 = u16 field (uniform node) | record+0x30 | 2 | `0xe86da3b  movzx eax,word ptr [rax+0x30]`; `0xe86db5d  movzx eax,word ptr [rax+0x30]` (rax = uniform node ptr from slot entry+0x00) | [V] |
| task RECORD +0x32 = u16 field (uniform node) | record+0x32 | 2 | `0xe86da0c  movzx ecx,word ptr [rax+0x32]`; `0xe86db35  movzx ecx,word ptr [rax+0x32]`; `0xe86df59  movzx eax,word ptr [rax+0x32]`; `0xe86dfc2  movzx eax,word ptr [rax+0x32]`; `0xe86e08f  movzx eax,word ptr [rax+0x32]`; `0xe86e0d7  movzx eax,word ptr [rax+0x32]`; `0xe86e104  movzx eax,word ptr [rax+0x32]`; `0xe86e413  movzx eax,word ptr [rax+0x32]`; `0xe86e503  movzx eax,word ptr [rax+0x32]` | [V] |
| task RECORD +0x34 = u8 flag (bindMaterial processes record only when == 1) | record+0x34 | 1 | `0xe86d910  cmp byte ptr [rax+0x34],1`; same at `0xe86db11`, `0xe86df12`, `0xe86e38a` (rax/rsi = record pointer from slot+0x00) | [V] |
| TaskListEntry stride (hypothesis source: record == entry?) | entry stride | 0x80 | `0xE900373  sar rax,7` ((end-begin) >> 7); `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` (r12 += 0x80 per entry) | [V] |
| TaskListEntry +0x00 = task object pointer | entry+0x00 | 8 | `0xE900464  mov rcx,[r12]` | [V] |
| TaskListEntry +0x08 = control block pointer | entry+0x08 | 8 | `0xE90048b  mov rax,[r12+8]` | [V] |
| entry+0x28 (hypothesis claim + live capture) | entry+0x28 | u32 | NEVER read as hash in dispatch: kind via `0xE90046b  mov rax,[rax+0x18]` / `0xE90047a  cmp eax,1`; only +0x28 access is `0xE9004f7  movups xmm1,[r12+0x1C]` (chunk +0x1C..+0x2F, never isolated); pass names FNV-1 vs record kind FNV-1a — family mismatch [V negative]. Live capture (BGFX_MAP 6da, orchestrator breakpoint at taskDispatch): base+0xe9002e0, rcx = taskList, n = 18 entries of 0x80 bytes; entry layout +0x00 task obj*, +0x08 shared_ptr ctrl*, +0x18 task param/kind index, +0x20 context id, **+0x28 u32 = 1 (live flag; 0 for entry 13), +0x2C debug marker colour**, rest zero up to +0x78 [I — cited live capture, no TaskList VA anchor available to re-read; taskList is endFrame's stack out-param `0xC27054c  lea rcx,[rbp+0x20]` / `0xC270554  call 0xE9002E0`, docs/data/live/ has no taskDispatch capture] | [V neg + I] |
| task RECORD size | record SIZE | ? | — (no allocator/sizer found; entry == record link rejected; no live TaskList VA anchor; no store to record+0x28 anywhere in .text) | [?] |
| task RECORD fields other than +0x28/+0x30/+0x32/+0x34 | record+0x00..+0x27,+0x35.. | ? | — (no store/read of any other record field observed; slot+0x00/entry+0x00 never stored in .text; 0x66466e0 has 0 callers/xrefs [V this unit]) | [?] |

## What I tried that failed (new angles; nothing already proven was redone)

- Dispatcher 0xE9002E0 full decode for entry+0x28 pass-name hash: negative — entry+0x28 never isolated-read; kind from task-object vtbl[3] (section above).
- render_hashes.txt cross-check: pass names are FNV-1; record kind is FNV-1a of uniform names — families mismatch, hypothesis fails.
- Caller/flow trace: taskDispatch 0xE9002E0 has exactly 1 caller (endFrame 0xC270460, passes stack out-param [rbp+0x20]); sub_6646980 (item visitor/bucket builder) <- sub_66466e0 (0 xrefs/callers) — no TaskList link, no slot+0x00 store; records created upstream (material/uniform registration), allocator/initializer not found [V negative].
- Live TaskList entry read at +0x28: impossible — no TaskList pointer anchor (list is per-frame stack/arena; no global), docs/data/live/ has no taskDispatch/endFrame capture, batchActor_extractor.txt yields no TaskList VA or usable record object address; scanning disallowed [V live status + file read].
- Static record allocator/initializer search from oc_U-EL3e_r1/r2/r3: confirmed negative again (zero stores to slot+0x00 / record-array entry+0x00; no store into record+0x28 anywhere in .text).
- ripscan for [0x129F9128] (uniform-name hash static): only 2 hits (0x66dc90b, 0x66e0863 in func 0x66d9af0) — both cmp sites, no construction code [V].

## CLOSES?

NO — blocking fact: the task RECORD SIZE and every RECORD field other than +0x28 kind hash, +0x30 u16, +0x32 u16, and +0x34 u8 flag are not provable by [V] rows. The TaskList-entry hypothesis (record size = 0x80, +0x00 task / +0x08 ctrl / +0x28 kind) is rejected: entry+0x28 is never read as a hash in taskDispatch 0xE9002E0 (`0xE90046b` vtbl[3]() / `0xE90047a cmp eax,1` supplies the kind; `0xE9004f7 movups xmm1,[r12+0x1C]` is the only +0x28 access, inside a 16-byte chunk) and a live TaskList capture shows entry+0x28 = u32 live flag (=1) [I, BGFX_MAP 6da]; pass names are FNV-1 (render_hashes.txt) vs the record's FNV-1a uniform-name kind; no static code links slot+0x00 record pointers to TaskList entries (slot+0x00 never stored in .text; sub_66466e0 has 0 xrefs/callers; allocator/initializer not found); and no live TaskList VA anchor exists (endFrame 0xC270460 passes the list via its stack out-param [rbp+0x20] at `0xC270554 call 0xE9002E0`; no taskDispatch capture in docs/data/live/), so entry+0x28 could not be live-read. Only record+0x28/+0x30/+0x32/+0x34 are [V].

## Verification

- verify_oc.py: pending
- delegate.py check: pending

## TOOL REQUESTS

- None (no helper scripts written; all evidence from rdis disassembly plus verify_oc/livemem status)
