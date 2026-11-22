## NEXT
DONE

# UNIT U-EL3e — L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Basis — checklist part (1) "task kind = FNV-1a 64 of uniform name" is CLOSED (prior units, not this unit's work)

Closed by U-C3b/U-C3b2 + BGFX_MAP 6ad [V]: task-record kinds are FNV-1a 64 of uniform names; `0x481CF7B16E204CF8 = fnv1a("UseAlphaRewrite")`, `0x48603E36F5CE3EB2 = fnv1a("LightWorldSpaceDirection")`. I recomputed both with basis 0xCBF29CE484222325 / prime 0x100000001B3 (the FNV-1a loop in the exe, e.g. `0x664707a  mov r10,0xCBF29CE484222325` / `0x6647084  xor rcx,r10` / `0x6647091  imul rcx,rsi`) and they match the record+0x28 comparands [V]. BGFX_MAP 6ad states two hash families: pass/material names = FNV-1 64; task-record kinds = FNV-1a 64 of uniform names. render_hashes.txt values are FNV-1 (checked: fnv1("DoDeferredShading") = 0xB2525E19C6E17C4B == file value; fnv1a = 0x573A1853C482D22F != file) [computed check].

## This unit — part (2) "record layout pending": new angle tested

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

## Task record layout table (this unit = pending part)

| name | offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| task RECORD +0x28 = qword task-kind hash (FNV-1a 64 of uniform name) | record+0x28 | 8 | `0x66dc923  cmp [r10+0x28],r8` (r10 = [slot+0x00], r8 = uniform-name hash `0x66dc908  mov r8,[0x129F9128]`); same cmp at `0x66dcae3`, `0x66dcb33`, `0x66dce03`, `0x66dce73`, `0x66dd013`, `0x66dd1b3`, `0x66dd353`, `0x66dd4f3`, `0x66dd693`, `0x66dd833`, `0x66ddaf3`, `0x66ddc53`, `0x66dddc3`, `0x66dea53` (`cmp [r8+0x28],rcx`), `0x66de103`, `0x66de263`, `0x66de373`, `0x66de533`, `0x66df283`, `0x66df483` (21 cmp sites in 0x66dc900..0x66de900); bindMaterial reads `0xe86d91f  mov r12,[rax+0x28]`, `0xe86da25  cmp [rdx+0x28],rcx`, `0xe86db47  cmp [rsi+0x28],rcx`, `0xe86e399  mov r10,[rax+0x28]`, `0xe86e519  mov rax,[rdx+0x28]` | [V] |
| task RECORD +0x34 = u8 flag (bindMaterial processes record only when == 1) | record+0x34 | 1 | `0xe86d910  cmp byte ptr [rax+0x34],1`; same at `0xe86db11`, `0xe86df12`, `0xe86e38a` (rax/rsi = record pointer from slot+0x00) | [V] |
| TaskListEntry stride (hypothesis source: record == entry?) | entry stride | 0x80 | `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` (r12 += 0x80 per entry); `0xE900373  sar rax,7` ((end-begin) >> 7) | [V] |
| TaskListEntry +0x00 = task object pointer | entry+0x00 | 8 | `0xE900464  mov rcx,[r12]` | [V] |
| TaskListEntry +0x08 = control block pointer | entry+0x08 | 8 | `0xE90048b  mov rax,[r12+8]` | [V] |
| entry+0x28 as FNV-1 pass-name hash (hypothesis claim, tested negatively) | entry+0x28 | - | never read in isolation in 0xE9002E0..0xE900F1A; fields read: +0x00 `0xE9004e3  movups xmm0,[r12]`, +0x10 `0xE9004f1  movups xmm0,[r12+0x10]`, +0x1C..+0x2F `0xE9004f7  movups xmm1,[r12+0x1C]`, +0x30, +0x40, +0x50, +0x60, +0x70 `0xE90052c  mov rax,[r12+0x70]`, +0x78 `0xE90056b  mov rax,[r12+0x78]`; kind via `0xE90046b  mov rax,[rax+0x18]` / `0xE90047a  cmp eax,1`; tail calls `0xE900EE1  call 0xEEC59E0`, `0xE900EE7  call 0x75740`, `0xE900F0D  call 0x75B60`, `0xE900F13  call 0x75B60` [V] | [V] negative |
| task RECORD size | record SIZE | ? | — (no allocator/sizer found; entry == record link not established) | [?] |
| task RECORD fields other than +0x28/+0x34 | record+0x00..+0x27,+0x35.. | ? | — (no store/read of any other record field observed) | [?] |

## What I tried that failed (new angles; nothing already proven was redone)

- Dispatcher 0xE9002E0 full decode for entry+0x28 pass-name hash: negative (section above).
- render_hashes.txt cross-check of the live entry+0x20 hash-like id 0x4BA175A2D6006D58 (live 6da): not any file hash [V].
- Live TaskList entry read (<=0x80 bytes at one entry's +0x28): impossible — no TaskList pointer anchor available (section above).
- Static record allocator/initializer search from oc_U-EL3e_r1/r2: confirmed negative again (zero stores to slot+0x00 / record-array entry+0x00; no store into record+0x28 anywhere in .text).

## CLOSES?

NO — blocking fact: the task RECORD SIZE and every RECORD field other than +0x28 kind hash and +0x34 u8 flag are not provable by [V] rows. The TaskList-entry hypothesis (record size = 0x80, +0x00 task / +0x08 ctrl / +0x28 kind) is unsupported: the dispatcher derives kind from vtbl[3]() (`0xE90046b` / `0xE90047a`), never isolates or compares entry+0x28 against a pass-name hash; pass names are FNV-1 while the record kind is FNV-1a of uniform names; no static code links the extractor's record pointer (slot+0x00) to a TaskList entry (zero stores, records created upstream, allocator/initializer not found); and no live TaskList pointer anchor is obtainable, so entry+0x28 could not be read. Only record+0x28 and record+0x34 are [V].

## Verification

- verify_oc.py: all quoted `0xRVA  instr` lines re-disassembled this session and match.
- delegate.py check: pending

## TOOL REQUESTS

- None (no helper scripts written; all evidence from rdis disassembly this session plus verify_oc/livemem status)
