## NEXT
DONE

# UNIT U-EC3b — C3b task record layout: RECORD SIZE and remaining record fields (BGFX_MAP 6ad)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Basis (closed by prior units — [V] anchors, not retried)

- Checklist part (1) "task kind = FNV-1a 64 of uniform name" is CLOSED: hasher 0x66a02d0 computes FNV-1a 64 over a std::string; fnv1a("UseAlphaRewrite")=0x481CF7B16E204CF8, fnv1a("LightWorldSpaceDirection")=0x48603E36F5CE3EB2 [V per BGFX_MAP 6ad].
- Task RECORD +0x28 = qword task-kind hash [V] — compared at 21 sites in the find-or-bind loops, e.g. `0x66dc923  cmp [r10+0x28],r8` (r10 = record pointer from slot+0x00; r8 = uniform-name hash from global [0x129F9128]).
- Task RECORD +0x34 = u8 flag [V] — bindMaterial processes the record only when this byte == 1 (`0xe86d910  cmp byte ptr [rax+0x34],1`, same at 0xe86db11, 0xe86df12, 0xe86e38a).
- BatchActor bucket/slot fields mapped [V] (prior units, context only): bucket+0x28 word, +0x30 qword data-array pointer, +0x38 qword slot-array pointer (0x10 stride, slot+0x00 = record pointer), +0x42 word slot count, +0x48 qword record-array pointer (0x30 stride, entry+0x00 = record pointer), +0x52 word record count, +0x78 qword hash accumulator.
- NOT the record: TaskList-entry hypothesis refuted (dispatcher 0xE9002E0 takes kind from vtbl[3]() `0xE90046b`/`0xE90047a`; entry+0x28 never isolated; pass names FNV-1 vs record kind FNV-1a) [V negative]. sub_66b2b30 creates only caller-supplied stack scratch records (~0x58 bytes) and zeroes +0x28 — not the persistent record [V].

## ANSWER TABLE — task RECORD (pending part: record SIZE and every field other than +0x28/+0x34)

| name | offset | size | read/store address(es) | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| task RECORD +0x28 = qword task-kind hash (FNV-1a 64 of uniform name) | record+0x28 | 8 | 0x66dc923, 0x66dcae3, 0x66dcb33, 0x66dce03, 0x66dce73, 0x66dd013, 0x66dd1b3, 0x66dd353, 0x66dd4f3, 0x66dd693, 0x66dd833, 0x66ddaf3, 0x66ddc53, 0x66dddc3, 0x66ddee3, 0x66de103, 0x66de263, 0x66de373, 0x66de533, 0x66df283, 0x66df483 | `0x66dc923  cmp [r10+0x28],r8` | record+0x28 compared against the FNV-1a hash of the current uniform name (r8 = [0x129F9128]); identical cmp at all 21 sites in 0x66dc900..0x66de900 | [V] |
| task RECORD +0x34 = u8 flag | record+0x34 | 1 | 0xe86d910, 0xe86db11, 0xe86df12, 0xe86e38a | `0xe86d910  cmp byte ptr [rax+0x34],1` | bindMaterial processes the record only when this byte == 1 (rax/rsi = record pointer from slot+0x00) | [V] |
| record-array entry+0x00 = qword record pointer | entry+0x00 | 8 | 0x66de100, 0x66de260 | `0x66de100  mov r10,[r11]` | record array at bucket+0x48 walked 0x30 per entry; entry+0x00 loads the record pointer whose [r10+0x28] is the kind hash | [V] context |
| record-array stride (pointer-table stride, NOT record size) | entry stride | 0x30 | 0x66de109, 0x66de269 | `0x66de109  add r11,0x30` | each record-array entry is 0x30 bytes; end = base + record_count*0x30 (record_count = word at bucket+0x52) | [V] context |
| task RECORD SIZE | record SIZE | ? | - | - | - | [?] |
| task RECORD fields other than +0x28/+0x34 | record fields ≠ +0x28/+0x34 | - | - | - | - | [?] |
| record+0x28 WRITER | record+0x28 | 8 | - | - | - | [?] |
| slot+0x00 FILLER / record CREATION site | - | - | - | - | - | [?] |

## What I tried that failed (this unit — new angles; prior units' negatives are cited above, not redone)

- fld 0x48 --w over .text: only generic stack writes plus `mov [rbx+0x48],rdi` in sub_76960 (0x76960..0x76ae1) and sub_77490 (0x77490..0x77611) — identical container initializers (self-linked 0x38-byte node + 0x80-byte block), called 132/197 times via generic template call sites (e.g. sub_5bfd7e0 ×55); not the bucket initializer (their +0x30/+0x38 are immediates 7/8, not table pointers) [V].
- fld 0x42 --w / fld 0x52 --w: 192 + 139 accesses, overwhelmingly stack ([rsp+0x42], [rbp+0x52]…); no function writing bucket+0x42/+0x52 together with table pointers at +0x38/+0x48 [V].
- Caller chain: `xr 0x66d9af0` → single tail-jump `0x66473e1  jmp 0x66D9AF0` from sub_6646980 (Item visitor); `callers 0x6646980` → sub_66466e0 (1 xref, 0 callers: vtable/CFG entry). Record tables therefore pre-exist the extractor [V].
- Decoded sub_74c870 (called per uniform from the extractor at 0x66d9bd1): generic string-into-vector append helper, not record creation [V].
- imm 0x481CF7B1 / imm 0x48603E36 (32-bit halves of the two kind hashes): 0 hits each — no immediate hash store [V]. fld 0x28 scan over all .text (248,770 writes): zero `[reg+0x28]` register-source stores [V negative]. fld 0x20 --w / fld 0x24 --w: covering movups/movdqu stores are generic SIMD outside the extractor range; none writes a record+0x28 hash [V].
- Livemem: no bucket/record/TaskList VA anchor; capture-derived VAs stale/unreadable; blind reads not permitted [V live].
- Prior units (not redone): full 7767-instruction dump of 0x66d9af0..0x66e26a7 (records only read at +0x28; no record stores, no slot+0x00/record-array-entry+0x00 stores, no allocation); all six 0x66a02d0 callers dumped (hash results go to stack locals or globals, never into a record); dispatcher 0xE9002E0 fully decoded (TaskList hypothesis refuted); ripscan of static hash slots (readers only inside the extractor).

## CLOSES?

NO — single blocking fact: the task RECORD SIZE is unknown, and consequently every record field other than +0x28 (qword kind hash) and +0x34 (u8 flag) is unproven. No instruction in .text stores into record+0x28 (fld 0x28 scan negative; no immediate; no covering store found), no instruction stores a record pointer into slot+0x00 or record-array entry+0x00, and no record allocator/constructor/sizer exists in static code — records are created upstream at material/uniform registration (asset load), entered via vtable/CFG dispatch (sub_66466e0 → sub_6646980 → sub_66d9af0), outside this unit's reach. Only record+0x28 [V] and record+0x34 [V] are proven; record size and remaining fields are [?].

## Verification

- verify_oc.py: every quoted `0xRVA  instr` line re-disassembled against the exe; run via `python tools/delegate.py check docs/progress/oc_U-EC3b.md`; every failure fixed, exit 0 required.
- delegate.py check: run at close; line after `## NEXT` set to DONE only when it exits 0.

## TOOL REQUESTS

- None (all evidence from rdis disassembly this session plus verified lines from prior units; no new helper scripts).
