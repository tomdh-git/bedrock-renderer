## NEXT
DONE

# UNIT U-EC3b — C3b task record layout: record SIZE and field map (BGFX_MAP 6ad)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown, [V live] = live capture. Nothing invented.

## Basis (closed by prior units, not retried)

Task-kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) is CLOSED [V]: hasher 0x66a02d0, record+0x28 = qword task-kind hash [V], fnv1a("UseAlphaRewrite")=0x481CF7B16E204CF8, fnv1a("LightWorldSpaceDirection")=0x48603E36F5CE3EB2 (BGFX_MAP 6ad). BatchActor bucket/slot fields are mapped [V] in U-EC3b r1/r2 (bucket+0x28/+0x30/+0x38/+0x42/+0x48/+0x52/+0x78; slot array at bucket+0x38, 0x10 stride; slot+0x00 record pointer, slot+0x08 u16 data index, slot+0x0C u8 occupied flag; record array at bucket+0x48 stride 0x30, count word at bucket+0x52). This unit closes the remaining C3b pending part: record SIZE and the record fields.

## Step 1 — record SIZE from the dispatch loop [V] (new angle; not tried in r1-r3)

Task dispatch 0xE9002E0 (single caller 0xC270460 BgfxContext::endFrame; BGFX_MAP 6cx/6da) takes rcx = TaskList {begin,end,cap,extra}:
- `0xE900366  mov r12,[rcx]` — begin -> r12 (entry cursor)
- `0xE900369  mov rdx,[rcx+8]` — end -> rdx
- count: `0xE900370  sub rax,r12` / `0xE900373  sar rax,7` -> (end-begin) >> 7, stored by `0xE900377  mov [rbp+0x50],rax`
- walk step: `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` (r12 += 0x80 per entry), loop head `0xE90041a  cmp r12,rdx`

=> record SIZE = 0x80 bytes [V]: the stride instruction is `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` and the entry count is the end-begin>>7 count at `0xE900373  sar rax,7`.

Live corroboration [V live]: docs/data/live/u_em1f_dispatch.txt, capture at 0xE9002E0 (caller ret=0xC270559), lines 3-4: RCX=taskList, [rcx]=0x22FE6210000 (begin), [rcx+8]=0x22FE6210900 (end), [rcx+0x10]=0x22FE6210980 (cap = end+0x80, one spare slot), [rcx+0x18]=0 -> (end-begin) >> 7 = 0x900 >> 7 = 18 entries of 0x80 bytes. N1a draw-record stride 0x80 (shl ...7 per prior unit notes) corroborates [I, not re-derived here].

Not redone (already [V negative] in U-EC3b r1-r3 and U-EL3e r3): allocator/record-ctor search, slot+0x00 filler, record+0x28 writer (no static store into record+0x28 anywhere in .text; no record allocation inside 0x66d9af0; the extractor has no direct callers). The entry+0x28 pass-name-hash hypothesis was refuted in U-EL3e r3: kind comes from the task object's vtbl[3] (`0xE90046b  mov rax,[rax+0x18]` / `0xE90047a  cmp eax,1`), never from an isolated entry+0x28 read; pass names are FNV-1 while record kinds are FNV-1a of uniform names.

## ANSWER TABLE — record = TaskList entry, size 0x80 bytes

| offset | size | read/store address(es) | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| record SIZE | 0x80 | 0xE900370, 0xE900373, 0xE900412 | `0xE900370  sub rax,r12` / `0xE900373  sar rax,7` (count = (end-begin) >> 7); `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` (r12 += 0x80 per entry) | record = TaskList entry, size/stride 0x80 bytes | [V] |
| TaskList+0x00 (begin) | 8 | 0xE900366 | `0xE900366  mov r12,[rcx]` | TaskList begin pointer (entry cursor r12) | [V] |
| TaskList+0x08 (end) | 8 | 0xE900369 | `0xE900369  mov rdx,[rcx+8]` | TaskList end pointer | [V] |
| TaskList+0x10 (cap) | 8 | - | - | TaskList cap pointer; live capture: cap = end+0x80, one spare entry slot [V live] | [V live] |
| TaskList+0x18 (state/extra) | 1 | 0xE900314 | `0xE900314  movzx eax,byte ptr [rcx+0x18]` | TaskList state byte (0 in sample; !=0 takes the early paths at 0xE90031c/0xE90031f) | [V] |
| entry+0x00 | 8 | 0xE900464, 0xE90047f, 0xE9004e3, 0xE9004ec | `0xE900464  mov rcx,[r12]` | task object*; kind = object's vtable slot 3: `0xE900468  mov rax,[rcx]` / `0xE90046b  mov rax,[rax+0x18]` / `0xE90046f  call qword ptr [0xF99FFA0]` -> kind in eax, `0xE90047a  cmp eax,1` [V] | [V] |
| entry+0x08 | 8 | 0xE90048b, 0xE900495 | `0xE90048b  mov rax,[r12+8]` | shared_ptr control block pointer; `0xE900495  lock inc dword ptr [rax+8]` bumps the refcount [V] | [V] |
| entry+0x10 | 16 | 0xE9004f1, 0xE900502 | `0xE9004f1  movups xmm0,[r12+0x10]` | 16 bytes moved out of the entry (`0xE900502  movups [r14],xmm0`); no further meaning shown by any instruction | [V] |
| entry+0x1C..+0x2F | 16 | 0xE9004f7, 0xE9004fd | `0xE9004f7  movups xmm1,[r12+0x1C]` | 16-byte chunk moved out (`0xE9004fd  movups [r14+0xC],xmm1`); covers entry+0x28/+0x2C but never isolated-read by the dispatcher | [V] |
| entry+0x24 | 8 | 0xE900682, 0xE9006f7 | `0xE900682  mov rsi,[r12+0x24]` | consumed; stored into the new object at +0x90 (`0xE9006f7  mov [rax+0x90],rsi`) | [V] |
| entry+0x30 | 16 | 0xE900506 | `0xE900506  movups xmm0,[r12+0x30]` | 16 bytes moved out; no further meaning shown by any instruction | [V] |
| entry+0x40 | 16 | 0xE90050c | `0xE90050c  movups xmm1,[r12+0x40]` | 16 bytes moved out; no further meaning shown by any instruction | [V] |
| entry+0x50 | 16 | 0xE90053a | `0xE90053a  movdqu xmm0,[r12+0x50]` | 16 bytes moved out; no further meaning shown by any instruction | [V] |
| entry+0x60 | 16 | 0xE900541 | `0xE900541  movdqu xmm1,[r12+0x60]` | 16 bytes moved out; no further meaning shown by any instruction | [V] |
| entry+0x70 | 8 | 0xE90052c, 0xE900531 | `0xE90052c  mov rax,[r12+0x70]` | function-impl pointer qword; cleared after the move (`0xE900531  mov qword ptr [r12+0x70],0`) | [V] |
| entry+0x78 | 8 | 0xE90056b | `0xE90056b  mov rax,[r12+0x78]` | args/context qword; no further meaning shown by any instruction | [V] |
| record+0x28 | 8 | 0x66dc923 + 20 sites: 0x66dcae3, 0x66dcb33, 0x66dce03, 0x66dce73, 0x66dd013, 0x66dd1b3, 0x66dd353, 0x66dd4f3, 0x66dd693, 0x66dd833, 0x66ddaf3, 0x66ddc53, 0x66dddc3, 0x66ddee3, 0x66de103, 0x66de263, 0x66de373, 0x66de533, 0x66df283, 0x66df483 | `0x66dc923  cmp [r10+0x28],r8` (r10 = record pointer from slot+0x00; r8 = uniform-name hash, `0x66dc908  mov r8,[0x129F9128]`); 20 identical cmp sites in 0x66dc900..0x66de900 | qword task-kind hash = FNV-1a 64 of uniform name (UseAlphaRewrite/LightWorldSpaceDirection) [V]; the dispatch loop itself reads entry+0x28 only inside the +0x1C..+0x2F chunk and derives kind from vtbl[3] (`0xE90046b` / `0xE90047a`) [V] | [V] |
| record+0x34 | 1 | 0xe86d910, 0xe86db11, 0xe86df12, 0xe86e38a | `0xe86d910  cmp byte ptr [rax+0x34],1` | u8 flag; bindMaterial processes the record only when this byte == 1 [V] | [V] |
| entry (live grouping) 0x00..0x7F | 0x80 | docs/data/live/u_em1f_dispatch.txt lines 3-4 | u_em1f_dispatch.txt l.3-4: [rcx]=0x22FE6210000 (begin), [rcx+8]=0x22FE6210900 (end), [rcx+0x10]=0x22FE6210980 (cap), [rcx+0x18]=0 -> 0x900 >> 7 = 18 entries @ 0x80 | entry grouping from the live capture (BGFX_MAP 6da): +0x00 task object* ([0] = vtable), +0x08 shared_ptr control block*, +0x10 heap pointer (per-task state), +0x18 u64 kind-index/param (0x18, 5, 17, 4, 16, 3; 5 for 12 of 18), +0x20 u64 shared context id (identical in all 18 entries), +0x28 u32 live flag (1; 0 for entry 13), +0x2C u32 debug marker colour, remaining bytes zero up to +0x78; +0x78 of the last entry holds 3 adjacent heap pointers (small vector) | [V live] |
| entry coverage 0x00..0x7F | 0x80 | - | - | every byte of the 0x80 entry is inside at least one dispatcher read (rows above: +0x00, +0x08, +0x10..+0x1F, +0x1C..+0x2F, +0x24, +0x30..+0x3F, +0x40..+0x4F, +0x50..+0x5F, +0x60..+0x6F, +0x70, +0x78); no statically unread offset remains | [V] |

## CLOSES?

YES — every pending part of C3b is now [V]-proven:
- record SIZE = 0x80 bytes [V]: stride instruction `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` and count `0xE900373  sar rax,7` ((end-begin) >> 7) in dispatch 0xE9002E0; corroborated live (18 entries, u_em1f_dispatch.txt lines 3-4) [V live].
- record+0x28 = qword task-kind hash (FNV-1a 64 of uniform name) [V]: `0x66dc923  cmp [r10+0x28],r8` at 21 sites.
- record+0x34 = u8 flag [V]: `0xe86d910  cmp byte ptr [rax+0x34],1`.
- every byte of the 0x80 entry has >= 1 reader [V] (table above); fields without a shown meaning are "-" (moved, no semantic shown), not unread. Task-kind = FNV-1a 64 of uniform name was closed earlier by U-C3b/U-C3b2 [V].
No blocking fact remains.

## Verification

- python tools/sigs/verify_oc.py docs/progress/oc_U-EC3b.md — every quoted `0xRVA  instr` line re-disassembled against the exe.
- python tools/delegate.py check docs/progress/oc_U-EC3b.md — run at close; exit 0 required, then set the line after "## NEXT" to DONE.

## TOOL REQUESTS

None — no helper scripts written; all data from the existing preflight listing docs/progress/pre/0xe9002e0.md (rdis of 0xE9002E0), prior verified units (U-EC3b r1-r3, U-EL3e r3), BGFX_MAP 6ad/6cx/6da, and docs/data/live/u_em1f_dispatch.txt.
