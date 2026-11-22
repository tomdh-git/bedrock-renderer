## NEXT
DONE

# UNIT U-EL3e — L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.

## Basis (carried forward from oc_U-EL3e_r1..r3.md; NOT redone this unit)

- Item part (1) "task kind = FNV-1a 64 of uniform name" CLOSED by prior units: record+0x28 qword compared against FNV-1a 64 of uniform names; 0x481CF7B16E204CF8 = fnv1a("UseAlphaRewrite"), 0x48603E36F5CE3EB2 = fnv1a("LightWorldSpaceDirection") [V per BGFX_MAP 6ad].
- Item part (2) "record layout pending" = THIS UNIT. Previously [V]: record+0x28 kind hash (21 cmp sites in 0x66dc900..0x66de900, r10 = [slot+0x00] = record ptr); record+0x34 u8 flag (bindMaterial 0xe86d7f0: cmp byte ptr [rax+0x34],1 at 0xe86d910/0xe86db11/0xe86df12/0xe86e38a). Record size and all other record fields: [?]. Zero stores to slot+0x00 / any record field / record allocator anywhere in .text [V negative, r1-r3].

## New angle this unit (orchestrator hint): record == frame TaskList entry? (entry stride 0x80, dispatcher 0xE9002E0)

Tested: (a) does entry+0x28 qword == FNV-1 64 hash of a pass name (docs/data/render_hashes.txt)? (b) do the cmp sites in 0x66dc900..0x66de900 take an entry pointer from a TaskList (callers/flow)? (c) live entry+0x28 read via a TaskList pointer anchor (docs/data/live/ + TaskDispatchHook sig at 0xE9002E0)?

### Dispatcher 0xE9002E0 re-verified this unit [V]

TaskList in rcx: `0xE900366  mov r12,[rcx]` (begin), `0xE900369  mov rdx,[rcx+8]` (end), `0xE900370  sub rax,r12`, `0xE900373  sar rax,7` → count = (end-begin) >> 7 = 0x80-stride entries; walk step `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` (r12 += 0x80).
Per entry: `0xE900464  mov rcx,[r12]` (entry+0x00 = task object*), `0xE900468  mov rax,[rcx]`, `0xE90046b  mov rax,[rax+0x18]`, `0xE90046f  call qword ptr [0xF99FFA0]` → task kind in eax from task-object vtbl slot 3, `0xE90047a  cmp eax,1`. `0xE90048b  mov rax,[r12+8]` (entry+0x08 = control block*), `0xE900495  lock inc dword ptr [rax+8]`.
Bulk entry copies: `0xE9004e3  movups xmm0,[r12]` (+0x00..+0x0F), `0xE9004f1  movups xmm0,[r12+0x10]`, `0xE9004f7  movups xmm1,[r12+0x1C]` (one 16-byte chunk covering +0x1C..+0x2F, +0x28 never isolated), `0xE90052c  mov rax,[r12+0x70]`, `0xE90056b  mov rax,[r12+0x78]`; copied via operator new(0x88) into a new object.
=> entry+0x28 is NEVER read or compared in isolation in 0xE9002E0..0xE900F1A; task kind comes from the task object's vtable, not from entry+0x28 [V]. rdis callers 0xE9002E0 -> exactly 1 caller: BgfxContext::endFrame 0xC270460 [V]; endFrame passes rcx = its stack out-param `[rbp+0x20]` (`0xC27054c  lea rcx,[rbp+0x20]` / `0xC270554  call 0xE9002E0`) — the TaskList is a per-frame stack/arena object produced by 0xc273420, NOT a global [V per dis of 0xC270460].

### Pass-name hash cross-check [V data / V prior units]

docs/data/render_hashes.txt header: "hash(FNV-1 64) -> name" — pass names are FNV-1, e.g. DoDeferredShading = 0xB2525E19C6E17C4B (file value; fnv1 verified match, fnv1a mismatch [computed check r3]), NothingTask = 0x9204c57f39a196b7. The record kind is FNV-1a of UNIFORM names (0x481CF7B16E204CF8 = fnv1a("UseAlphaRewrite")) [V BGFX_MAP 6ad]. Hash families differ => entry+0x28 cannot be both the record's FNV-1a uniform kind hash and a FNV-1 pass-name hash.

### Link extractor record <-> TaskList entry [V negative]

- Extractor record pointer: r10 = `0x66dc920  mov r10,[rcx]` walking slot array stride 0x10 (`0x66dc929  add rcx,0x10`); slot+0x00 = record pointer [V]. Zero stores to slot+0x00 / record-array entry+0x00 anywhere in .text [V negative r1-r3]; no store into record+0x28 anywhere in .text [V negative]; no record allocator/initializer found [V negative].
- Caller flow: rdis callers 0x6646980 (item visitor, builds bucket and tail-jumps to 0x66d9af0) -> exactly 1 caller, sub_66466e0; rdis callers/ripscan 0x66466e0 -> 0 callers/xrefs [V this unit]; sub_66466e0 builds holder fields on its stack (e.g. `0x66467d1  mov [rbp+0x20],rcx` = (*(a0+0x28)+0x18)+0xE60) and calls sub_6646980 with &locals — no TaskList, no record-pointer store [V this unit]. sub_6646980 resolves materials by name ("ChunkOccluder" at `0x6646ae5  lea rax,[0xF2BE528]` / `0x6646b20  call 0x67D6D70`) — records are created upstream of this unit (material/uniform registration), not here [V negative].
- => No static code makes slot+0x00 point at a TaskList entry; record == entry not provable either way, and the +0x28 field semantics contradict it (u32 live flag vs qword hash).

### Live check [attempted, not possible this unit]

- Game running: pid 18956, base 0x7ff699000000 (`python tools/sigs/livemem.py status` [V live]). At most 12 livemem reads allowed, max 0x400 per read, no scanning.
- No TaskList pointer anchor exists: the TaskList is endFrame's stack out-param (0xC270460 passes [rbp+0x20] to 0xE9002E0); docs/data/live/ contains NO taskDispatch/endFrame capture (grep negative); docs/data/live/batchActor_extractor.txt is a regs capture at 0x66D9AF0 entry (RCX = bucket VA 0x3459FFF0F00, RDX/R8 = stack addresses) with no TaskList VA and no usable record object address [V read this unit; same conclusion r3]. EC3b's prior bucket VA 0x3462FDB8020 unreadable now [r3].
- => livemem read of one TaskList entry at +0x28 cannot be performed: no base address, and scanning is disallowed.

## Hypothesis verdict: record == TaskList entry (size 0x80) — NOT SUPPORTED, rejected

entry+0x28 is not the kind hash: never isolated-read in taskDispatch [V]; kind from task-object vtbl[3] `0xE90046b` / `0xE90047a cmp eax,1` [V]; live capture documents entry+0x28 = u32 live flag (=1), +0x2C = debug marker colour [I — orchestrator live capture cited in BGFX_MAP 6da; not reproducible by me, no TaskList VA anchor]; pass names FNV-1 (render_hashes.txt) vs record kind FNV-1a of uniform names [V data]. Therefore record size != 0x80 via this link; record size and fields other than +0x28/+0x34 remain unprovable.

## Task record layout table (pending part; carried [V] rows included as anchor)

| name | rva or offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| task RECORD +0x28 = qword task kind hash (FNV-1a 64 of uniform name) | record+0x28 | 8 | `0x66dc923  cmp [r10+0x28],r8` (r10 = [slot+0x00] = record pointer; r8 = uniform-name hash `0x66dc908  mov r8,[0x129F9128]`); same cmp at `0x66dcae3`, `0x66dcb33`, `0x66dce03`, `0x66dce73`, `0x66dd013`, `0x66dd1b3`, `0x66dd353`, `0x66dd4f3`, `0x66dd693`, `0x66dd833`, `0x66ddaf3`, `0x66ddc53`, `0x66dddc3`, `0x66dea53` (`cmp [r8+0x28],rcx`), `0x66de103`, `0x66de263`, `0x66de373`, `0x66de533`, `0x66df283`, `0x66df483` (21 cmp sites in 0x66dc900..0x66de900); bindMaterial reads `0xe86d91f  mov r12,[rax+0x28]`, `0xe86da25  cmp [rdx+0x28],rcx`, `0xe86db47  cmp [rsi+0x28],rcx`, `0xe86e399  mov r10,[rax+0x28]`, `0xe86e519  mov rax,[rdx+0x28]` | [V] |
| task RECORD +0x34 = u8 flag (bindMaterial processes record only when == 1) | record+0x34 | 1 | `0xe86d910  cmp byte ptr [rax+0x34],1`; same at `0xe86db11`, `0xe86df12`, `0xe86e38a` (rax/rsi = record pointer from slot+0x00) | [V] |
| TaskListEntry stride (hypothesis source: record == entry?) | entry stride | 0x80 | `0xE900373  sar rax,7` ((end-begin) >> 7); `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` (r12 += 0x80 per entry) | [V] |
| TaskListEntry +0x00 = task object pointer | entry+0x00 | 8 | `0xE900464  mov rcx,[r12]` | [V] |
| TaskListEntry +0x08 = control block pointer | entry+0x08 | 8 | `0xE90048b  mov rax,[r12+8]` | [V] |
| entry+0x28 as FNV-1 pass-name hash (hypothesis claim, rejected) | entry+0x28 | - | never isolated-read/compared in 0xE9002E0..0xE900F1A: fields read are +0x00 `0xE9004e3  movups xmm0,[r12]`, +0x10 `0xE9004f1  movups xmm0,[r12+0x10]`, +0x1C..+0x2F chunk `0xE9004f7  movups xmm1,[r12+0x1C]` (+0x28 inside chunk, never isolated), +0x30/+0x40/+0x50/+0x60 `0xE900506  movups xmm0,[r12+0x30]`/`0xE90050c  movups xmm1,[r12+0x40]`, +0x70 `0xE90052c  mov rax,[r12+0x70]`, +0x78 `0xE90056b  mov rax,[r12+0x78]`; kind via `0xE90046b  mov rax,[rax+0x18]` / `0xE90047a  cmp eax,1` [V]; render_hashes.txt is FNV-1 (header; DoDeferredShading = 0xB2525E19C6E17C4B) while record kind is FNV-1a of uniform names [V data] | [V] negative |
| entry+0x28 per live TaskList capture (BGFX_MAP 6da, orchestrator breakpoint at taskDispatch) | entry+0x28 | u32 | not an instruction: live capture at base+0xe9002e0, rcx = taskList, n = 18 entries of 0x80 bytes; entry layout +0x00 task obj*, +0x08 shared_ptr ctrl*, +0x18 task param/kind index, +0x20 context id, **+0x28 u32 = 1 (live flag; 0 for entry 13), +0x2C debug marker colour**, rest zero up to +0x78 [I — cited live capture, no TaskList VA anchor available to re-read; taskList is endFrame's stack out-param `0xC27054c  lea rcx,[rbp+0x20]` / `0xC270554  call 0xE9002E0`, docs/data/live/ has no taskDispatch capture] | [I] |
| task RECORD size | record SIZE | ? | — (no allocator/sizer found; entry == entry link rejected; no live TaskList VA anchor) | [?] |
| task RECORD fields other than +0x28/+0x34 | record+0x00..+0x27,+0x35.. | ? | — (no store/read of any other record field observed; slot+0x00/entry+0x00 never stored in .text; 0x66466e0 has 0 callers/xrefs [V this unit]) | [?] |

## What I tried that failed (new angles; nothing already proven was redone)

- Dispatcher 0xE9002E0 full decode for entry+0x28 pass-name hash: negative — entry+0x28 never isolated-read; kind from task-object vtbl[3] (section above).
- render_hashes.txt cross-check: pass names are FNV-1; record kind is FNV-1a of uniform names — families mismatch, hypothesis fails.
- Caller/flow trace: taskDispatch 0xE9002E0 has exactly 1 caller (endFrame 0xC270460, passes stack out-param [rbp+0x20]); sub_6646980 (item visitor/bucket builder) <- sub_66466e0 (0 xrefs/callers) — no TaskList link, no slot+0x00 store; records created upstream (material/uniform registration), allocator/initializer not found [V negative].
- Live TaskList entry read at +0x28: impossible — no TaskList pointer anchor (list is per-frame stack/arena; no global), docs/data/live/ has no taskDispatch/endFrame capture, batchActor_extractor.txt yields no TaskList VA or usable record object address; scanning disallowed [V live status + file read].

## CLOSES?

NO — blocking fact: the task RECORD SIZE and every RECORD field other than +0x28 kind hash and +0x34 u8 flag are not provable by [V] rows. The TaskList-entry hypothesis (record size = 0x80, +0x00 task / +0x08 ctrl / +0x28 kind) is rejected: entry+0x28 is never read as a hash in taskDispatch 0xE9002E0 (`0xE90046b` vtbl[3]() / `0xE90047a cmp eax,1` supplies the kind; `0xE9004f7 movups xmm1,[r12+0x1C]` is the only +0x28 access, inside a 16-byte chunk) and a live TaskList capture shows entry+0x28 = u32 live flag (=1) [I, BGFX_MAP 6da]; pass names are FNV-1 (render_hashes.txt) vs the record's FNV-1a uniform-name kind; no static code links slot+0x00 record pointers to TaskList entries (slot+0x00/entry+0x00 never stored in .text; 0x66466e0 has 0 xrefs/callers; allocator/initializer not found); and no live TaskList VA anchor exists (endFrame 0xC270460 passes the list via its stack out-param [rbp+0x20] at `0xC270554 call 0xE9002E0`; no taskDispatch capture in docs/data/live/), so entry+0x28 could not be live-read. Only record+0x28 and record+0x34 are [V].

## Verification

- verify_oc.py: pending (run next)
- delegate.py check: pending (run next; fix every failure)

## TOOL REQUESTS

- None (no new helper scripts; all evidence from rdis disassembly this session, docs/data/render_hashes.txt, docs/BGFX_MAP.md 6cx/6da, docs/data/live/, livemem status)
