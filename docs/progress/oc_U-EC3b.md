## NEXT
DONE

# UNIT U-EC3b — C3b task record layout: record SIZE and remaining fields (BGFX_MAP 6ad)

Source exe: C:\Users\Atomi\AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Pending part of C3b (this unit only)

Checklist C3b: "Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending".
Closed already (U-C3b/U-C3b2, [V]): task-kind hasher 0x66a02d0 computes FNV-1a 64 over a std::string; record+0x28 = qword task-kind hash [V]; fnv1a("UseAlphaRewrite")=0x481CF7B16E204CF8, fnv1a("LightWorldSpaceDirection")=0x48603E36F5CE3EB2 [V per BGFX_MAP 6ad].
Pending here: the task RECORD SIZE and every RECORD field other than +0x28.
BatchActor bucket/slot fields (+0x28/+0x30/+0x38/+0x42/+0x48/+0x52/+0x78, slot 0x10 stride, record-array stride 0x30 at bucket+0x48, record-count word at bucket+0x52) are mapped in C3b/r2 and are NOT re-decoded here; they are cited only as context for where record pointers come from.

## Record-kind anchor (context, [V]-closed by prior units)

| name | offset | size | read/store address(es) | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|---|
| task RECORD +0x28 | record+0x28 | 8 | 0x66dc923, 0x66dcae3, 0x66dcb33, 0x66dce03, 0x66dce73, 0x66dd013, 0x66dd1b3, 0x66dd353, 0x66dd4f3, 0x66dd693, 0x66dd833, 0x66ddaf3, 0x66ddc53, 0x66dddc3, 0x66ddee3, 0x66de103, 0x66de263, 0x66de373, 0x66de533, 0x66df283, 0x66df483 | `0x66dc920  mov r10,[rcx]`<br>`0x66dc923  cmp [r10+0x28],r8`<br>`0x66dc908  mov r8,[0x129F9128]` | record pointer r10 walked from slot array (slot stride 0x10) / record array (stride 0x30); [r10+0x28] = qword task-kind hash compared against the FNV-1a hash of the current uniform name loaded from static slot [0x129F9128] (fnv1a("UseAlphaRewrite") and others) [V] | [V] |

## Pending: task RECORD SIZE and remaining RECORD fields

| task RECORD SIZE | record SIZE | - | - | - | not observable: no static code allocates, constructs, memcpys, or struct-copies a record object; no store into record+0x28 anywhere in .text; records are created outside the BatchActor extractor 0x66d9af0 (no direct callers — entered via Item visitor 0x6646980/CFG), so neither the record size nor its remaining fields are anchored by any [V] row | [?] |
| task RECORD fields other than +0x28 | record fields ≠ +0x28 | - | - | - | not observable: across the full 0x66d9af0..0x66e26a7 listing (7767 instructions, dumped with dumplist.py) the only record field ever read is +0x28 (21 cmp sites above); zero stores to any record offset, zero stores of a record pointer into slot+0x00 or record-array entry+0x00; every other record field is never touched in static code | [?] |

## What I tried that failed (new angles, all negative)

- ripscan of every static kind-hash slot ([0x129F9128], [0x129F91E8], [0x129F91F0], [0x129F9200], [0x129C13C0], [0x129F9190]): every reader is inside 0x66d9af0 or the guard thunks (0x66e2b10, 0x66e2bf0, … calling 0xE938D30 with &slot). No consumer of a stored record-kind hash exists outside the extractor [V].
- xr 0x66a02d0: all 129 direct call sites lie in six functions (0x6646980, 0x666aca0, 0x6698e30, 0x66ea3d0, 0x6745440, 0x674a3a0). Dumped all six in full with dumplist.py and grepped every [reg+0x28] access: none stores a hash into a record. The Item visitor 0x6646980's single FNV site (0x6647c85) writes the result to stack local [rbp+0x5A0], not a record [V].
- imm 0x481CF7B16E204CF8 and imm 0x48603E36F5CE3EB2: 0 hits — kind hashes are never stored as immediates [V].
- fld 0x28 --w over all of .text (248,770 writes saved to docs/progress/fld_0x28_w_full.txt): no register-source store to [reg+0x28] occurs inside 0x66d9af0 or any of the six FNV-callers [V]; the write that initializes record+0x28 is not visible in static disassembly.
- 0x66b2b30 (registry "emplace" helper, x1 from the extractor): disassembled (0x66b2b30..0x66b2dcd) — it initializes a ~0x58-byte object at fields +0x0..+0x56 but never +0x28; not a task-record creator [V].
- Re-decoded both slot-search loops (0x66dc920/0x66dcae0/0x66dcb30) and every miss-path (0x66dca80, 0x66DCD29, 0x66DF614…): only lazy static-slot init plus cmp [record+0x28]; no record creation [V].
- livemem: game running (pid 10808, `python tools/sigs/livemem.py status` [V live]). The capture-derived bucket VA 0x3462FDB8020 (desc+0x90, rbx = [rcx+0x90] at 0x66db0e0 with rcx = description r8) is unreadable now — `python tools/sigs/livemem.py read 0x3462FDB8020 0xA0` returned "unreadable at 0x3462fdb8020" (retried once, same). Current-frame objects hold no discoverable record/bucket anchor; memory scanning is not permitted [V live].

## CLOSES?

NO — single blocking fact: the task RECORD SIZE and every RECORD field other than +0x28 are not provable by [V] rows. Only record+0x28 = qword task-kind hash is [V]-proven (21 cmp sites). Record objects are created outside 0x66d9af0 (no direct callers; entered via Item visitor 0x6646980/CFG), no static code stores into record+0x28 or allocates/copies a record, and the one live bucket anchor from the capture (0x3462FDB8020) is no longer readable, so record size and remaining fields cannot be anchored statically or via the allowed livemem reads.

## Verification
- verify_oc.py: run and fix every mismatch
- delegate.py check: run and fix every failure; then set the line after "## NEXT" to DONE

## TOOL REQUESTS
- None (no helper scripts written); a ranged variant of `fld` (page writes by address range) would have helped scan the 83k [reg+0x28] writes outside the extractor, but none of them could be tied to a record anyway.
