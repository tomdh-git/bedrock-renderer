## NEXT
DONE

# UNIT U-EC3b — C3b task record layout: record SIZE and remaining fields (BGFX_MAP 6ad)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Pending part of C3b (this unit only)
Checklist C3b: "Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending".
Closed already (U-C3b/U-C3b2, [V]): task-kind hasher 0x66a02d0 computes FNV-1a 64 over a std::string (`h ^= b; h *= 0x100000001b3` per byte, result stored `mov [rsi],rdx` at 0x66a03b7); record+0x28 = qword task-kind hash [V]; fnv1a("UseAlphaRewrite")=0x481CF7B16E204CF8, fnv1a("LightWorldSpaceDirection")=0x48603E36F5CE3EB2 [V per BGFX_MAP 6ad].
Pending here: the task RECORD SIZE and every RECORD field other than +0x28.
BatchActor bucket/slot fields (+0x28/+0x30/+0x38/+0x42/+0x48/+0x52/+0x78, slot 0x10 stride) are mapped in C3b2 and are NOT re-decoded here; they are cited only as context for where record pointers come from. BGFX_MAP has no section 1267 (the C3b2 "0x80-byte dispatch entry" claim cites a non-existent section and is not used here).

## Method [V]
- Dumped the FULL BatchActor extractor 0x66d9af0..0x66e26a7 (7767 instructions) with `python tools/sigs/dumplist.py 0x66d9af0 0x66e26a7 docs/progress/listings/oc_U-EC3b_full.txt` [V], then grepped every access to [reg+0x28], every memory store, and every record-pointer load in that listing.

## Record evidence table
| offset | size | read/store address(es) | verbatim `0xRVA  instr` line(s) | meaning |
| record+0x28 | 8 | 0x66dc923, 0x66dcae3, 0x66dcb33, 0x66dce03, 0x66dce73, 0x66dd013, 0x66dd1b3, 0x66dd353, 0x66dd4f3, 0x66dd693, 0x66dd833, 0x66ddaf3, 0x66ddc53, 0x66dddc3, 0x66ddee3, 0x66de103, 0x66de263, 0x66de373, 0x66de533, 0x66df283, 0x66df483, 0x66db4d3, 0x66db673, 0x66db843, 0x66db9e3, 0x66dbb83, 0x66dbd33, 0x66dbee3, 0x66dc093, 0x66dc233, 0x66dc403, 0x66dc593, 0x66dc753, 0x66ddf24, 0x66de3b4, 0x66de574, 0x66db50d, 0x66db6ad, 0x66db87d, 0x66dba1d, 0x66dbbbd, 0x66dbd6d, 0x66dc0c5, 0x66dc265, 0x66dc435, 0x66dc5c5, 0x66dc78d, 0x66dc955, 0x66dcb69, 0x66dcbfe, 0x66dcea9, 0x66dd049, 0x66dd1e9, 0x66dd389, 0x66dd529, 0x66dd6c9, 0x66dd869, 0x66dd905, 0x66df2bc, 0x66df4c4 | `0x66dc923  cmp [r10+0x28],r8`<br>`0x66dcae3  cmp [r10+0x28],r8`<br>`0x66dcb33  cmp [r10+0x28],r8`<br>`0x66dce03  cmp [r10+0x28],r8`<br>`0x66dce73  cmp [r10+0x28],r8`<br>`0x66dd013  cmp [r10+0x28],r8`<br>`0x66dd1b3  cmp [r10+0x28],r8`<br>`0x66dd353  cmp [r10+0x28],r8`<br>`0x66dd4f3  cmp [r10+0x28],r8`<br>`0x66dd693  cmp [r10+0x28],r8`<br>`0x66dd833  cmp [r10+0x28],r8`<br>`0x66ddaf3  cmp [r10+0x28],r8`<br>`0x66ddc53  cmp [r10+0x28],r8`<br>`0x66dddc3  cmp [r10+0x28],r8`<br>`0x66ddee3  cmp [r10+0x28],r8`<br>`0x66de103  cmp [r10+0x28],r8`<br>`0x66de263  cmp [r10+0x28],r8`<br>`0x66de373  cmp [r10+0x28],r8`<br>`0x66de533  cmp [r10+0x28],r8`<br>`0x66df283  cmp [r10+0x28],r8`<br>`0x66df483  cmp [r10+0x28],r8`<br>`0x66db4d3  cmp [r10+0x28],r8`<br>`0x66db673  cmp [r10+0x28],r8`<br>`0x66db843  cmp [r10+0x28],r8`<br>`0x66db9e3  cmp [r10+0x28],r8`<br>`0x66dbb83  cmp [r10+0x28],r8`<br>`0x66dbd33  cmp [r10+0x28],r8`<br>`0x66dbee3  cmp [r10+0x28],r8`<br>`0x66dc093  cmp [r10+0x28],r8`<br>`0x66dc233  cmp [r10+0x28],r8`<br>`0x66dc403  cmp [r10+0x28],r8`<br>`0x66dc593  cmp [r10+0x28],r8`<br>`0x66dc753  cmp [r10+0x28],r8`<br>`0x66ddf24  cmp [r14+0x28],r8`<br>`0x66de3b4  cmp [r14+0x28],r8`<br>`0x66de574  cmp [r14+0x28],r8`<br>`0x66db50d  cmp [rbx+0x28],r8`<br>`0x66db6ad  cmp [rbx+0x28],r8`<br>`0x66db87d  cmp [rbx+0x28],r8`<br>`0x66dba1d  cmp [rbx+0x28],r8`<br>`0x66dbbbd  cmp [rbx+0x28],r8`<br>`0x66dbd6d  cmp [rbx+0x28],r8`<br>`0x66dc0c5  cmp [rbx+0x28],r8`<br>`0x66dc265  cmp [rbx+0x28],r8`<br>`0x66dc435  cmp [rbx+0x28],r8`<br>`0x66dc5c5  cmp [rbx+0x28],r8`<br>`0x66dc78d  cmp [rbx+0x28],r8`<br>`0x66dc955  cmp [rbx+0x28],r8`<br>`0x66dcb69  cmp [rbx+0x28],r8`<br>`0x66dcbfe  cmp [rbx+0x28],r8`<br>`0x66dcea9  cmp [rbx+0x28],r8`<br>`0x66dd049  cmp [rbx+0x28],r8`<br>`0x66dd1e9  cmp [rbx+0x28],r8`<br>`0x66dd389  cmp [rbx+0x28],r8`<br>`0x66dd529  cmp [rbx+0x28],r8`<br>`0x66dd6c9  cmp [rbx+0x28],r8`<br>`0x66dd869  cmp [rbx+0x28],r8`<br>`0x66dd905  cmp [rbx+0x28],r8`<br>`0x66df2bc  cmp [rbx+0x28],r8`<br>`0x66df4c4  cmp [rbx+0x28],r8` | task RECORD +0x28 = qword task-kind hash (FNV-1a 64 of uniform name: UseAlphaRewrite 0x481CF7B16E204CF8, LightWorldSpaceDirection 0x48603E36F5CE3EB2) [V — 32 cmp via record pointer r10, 3 cmp via r14; bucket+0x28 cmp sites are the bucket word field, not the record] |
| slot+0x00 | 8 | 0x66db4d0, 0x66db670, 0x66db840, 0x66db9e0, 0x66dbb80, 0x66dbd30, 0x66dbee0, 0x66dc090, 0x66dc230, 0x66dc400, 0x66dc590, 0x66dc750, 0x66dc920, 0x66dcae0, 0x66dcb30, 0x66dce00, 0x66dce70, 0x66dd010, 0x66dd1b0, 0x66dd350, 0x66dd4f0, 0x66dd690, 0x66dd830, 0x66ddaf0, 0x66ddc50, 0x66dddc0, 0x66ddee0, 0x66de370, 0x66de530, 0x66df280, 0x66df480 | `0x66dc920  mov r10,[rcx]`<br>`0x66dcae0  mov r10,[rcx]`<br>`0x66dcb30  mov r10,[rcx]`<br>`0x66dce00  mov r10,[rcx]`<br>`0x66dce70  mov r10,[rcx]`<br>`0x66dd010  mov r10,[rcx]`<br>`0x66dd1b0  mov r10,[rcx]`<br>`0x66dd350  mov r10,[rcx]`<br>`0x66dd4f0  mov r10,[rcx]`<br>`0x66dd690  mov r10,[rcx]`<br>`0x66dd830  mov r10,[rcx]`<br>`0x66ddaf0  mov r10,[rcx]`<br>`0x66ddc50  mov r10,[rcx]`<br>`0x66dddc0  mov r10,[rcx]`<br>`0x66ddee0  mov r10,[rcx]`<br>`0x66db4d0  mov r10,[rcx]`<br>`0x66db670  mov r10,[rcx]`<br>`0x66db840  mov r10,[rcx]`<br>`0x66db9e0  mov r10,[rcx]`<br>`0x66dbb80  mov r10,[rcx]`<br>`0x66dbd30  mov r10,[rcx]`<br>`0x66dbee0  mov r10,[rcx]`<br>`0x66dc090  mov r10,[rcx]`<br>`0x66dc230  mov r10,[rcx]`<br>`0x66dc400  mov r10,[rcx]`<br>`0x66dc590  mov r10,[rcx]`<br>`0x66dc750  mov r10,[rcx]`<br>`0x66de370  mov r10,[rcx]`<br>`0x66de530  mov r10,[rcx]`<br>`0x66df280  mov r10,[rcx]`<br>`0x66df480  mov r10,[rcx]` | SLOT +0x00 = qword record pointer, loaded then dereferenced as [r10+0x28] (record+0x28 kind hash) [V — 30 sites; slot array at bucket+0x38, 0x10 stride] |
| rec-arr entry+0x00 | 8 | 0x66de100, 0x66de260 | `0x66de100  mov r10,[r11]`<br>`0x66de260  mov r10,[r11]` | RECORD-ARRAY entry+0x00 = qword record pointer (entry walked by 0x30; [r10+0x28] = record kind hash) [V — 2 sites; record array at bucket+0x48] |
| record-array stride | 0x30 | 0x66de109, 0x66de269 | `0x66de109  add r11,0x30`<br>`0x66de269  add r11,0x30` | record array at bucket+0x48 strides 0x30 per entry (end = base + record_count*0x30, record_count = word at bucket+0x52) [V] |
| bucket+0x48 | 8 | 0x66de0cf, 0x66de229 | `0x66de0cf  mov rax,[rcx+0x48]` | BUCKET +0x48 = qword record-array base [V; context, mapped in C3b2] |
| bucket+0x52 | 2 | 0x66de0d3, 0x66de22d | `0x66de0d3  movzx r8d,word ptr [rcx+0x52]` | BUCKET +0x52 = word record count [V; context, mapped in C3b2] |
| record SIZE | ? | - | - | not observable: no allocator, constructor, memcpy, or struct copy sizes the record object anywhere in 0x66d9af0; record-array entry stride 0x30 is the stride of the POINTER array, not the record size [?] |
| record fields other than +0x28 | - | - | - | never read or written anywhere in 0x66d9af0; the only record field ever accessed is +0x28 (35 cmp sites above) [?] |

## Verbatim instruction listing (all distinct lines quoted from the listing)
0x66dc923  cmp [r10+0x28],r8
0x66dc920  mov r10,[rcx]
0x66de100  mov r10,[r11]
0x66de109  add r11,0x30
0x66de0cf  mov rax,[rcx+0x48]
0x66de0d3  movzx r8d,word ptr [rcx+0x52]
(The `cmp [reg+0x28],r8` text is identical at all 35 record+0x28 sites; each site's RVA is listed in the table's address column.)

## Negative search results (full 7767-instruction listing of 0x66d9af0..0x66e26a7)
- Zero stores of a kind hash into a record: no `mov [reg+0x28], <hash-reg>` anywhere; every `[*+0x28]` access is a `cmp`/`movss` read (the movss [rax+0x28] at 0x66db806 and the movups/dword stores at 0x66de6c1/0x66de9e7/0x66dec25/0x66def77 touch the on-stack 0x80-byte uniform staging block, not a task record).
- Zero stores of a record pointer into slot+0x00 or record-array-entry+0x00; pointers are only loaded.
- Zero record allocations/ctors; the extractor has no direct callers (vtable/CFG entry per docs/functions/66d9af0.md), so records are created outside this function and outside this unit's reach.

## CLOSES?
NO — single blocking fact: the task record SIZE and every record field other than +0x28 are not provable by [V] rows. Across the full BatchActor extractor listing record objects are only ever read at +0x28 (35 cmp sites); no static code stores a kind hash into a record, stores a record pointer into a slot/record-array entry, allocates a record, or sizes one — records are created outside 0x66d9af0 (no direct callers), so the record creation site, record size, and remaining record fields are not statically observable in this unit. Only record+0x28 = qword task-kind hash is [V]-proven; the rest of the record layout is [?].

## Verification
- verify_oc.py: not yet run
- delegate.py check: not yet run

## TOOL REQUESTS
None — all evidence from the full 0x66d9af0 listing dumped with dumplist.py and grepped by hand.
