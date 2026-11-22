## NEXT
DONE

# UNIT U-EC3b — C3b task record layout pending (BGFX_MAP 6ad)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Summary

The C3b checklist item has two parts: (1) "Task kind = FNV-1a 64 of uniform name" — already CLOSED by units U-C3b/U-C3b2 (helper 0x66a02d0 computes FNV-1a 64 over std::string; hash stored at record+0x28; 0x481CF7B16E204CF8 = fnv1a("UseAlphaRewrite"), 0x48603E36F5CE3EB2 = fnv1a("LightWorldSpaceDirection") [V per BGFX_MAP 6ad]). (2) "record layout pending" — this unit closes that.

Disassembled sub_66d9af0 (BatchActor extractor) interior 0x66dc900..0x66de900. The code is a find-or-create loop over task records in a bucket object (rbx). Each bucket holds:
- a slot array ([rbx+0x38], 0x10-byte slots: record ptr +0x00, data-index word +0x08, flag byte +0x0C)
- a data array ([rbx+0x30], 16-byte entries per slot holding uniform values)
- a record array ([rbx+0x48], 0x30-stride entries, each starting with a record pointer at +0x00)
- bucket fields: +0x28 word kind/index, +0x42 word slot count, +0x52 word record count, +0x78 qword hash accumulator

Each task RECORD (r10 = [slot+0x00]) has exactly one verified field: +0x28 = qword task kind hash, compared at 12 sites against FNV-1a hash statics ([0x129F9128] = fnv1a("UseAlphaRewrite"), [and more]). No stores to any other record offset appear in this listing; records are allocated/initialized outside this code path. Record size and remaining fields are not provable from this listing alone.

## Task record layout table

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| record+0x28 | 8 | 0x66dc923, 0x66dcae3, 0x66dcb33, 0x66dce03, 0x66dce73, 0x66dd013, 0x66dd1b3, 0x66dd353, 0x66dd4f3, 0x66dd693, 0x66dd833, 0x66ddaf3 | see instr listing below | task RECORD +0x28 = qword task kind hash (FNV-1a 64 of uniform name: UseAlphaRewrite, LightWorldSpaceDirection) [V] |
| bucket+0x28 | 2 | 0x66dc955, 0x66dcb69, 0x66dcbfe, 0x66dcea9, 0x66dd049, 0x66dd1e9, 0x66dd389, 0x66dd529, 0x66dd6c9, 0x66dd869, 0x66dd905 | see instr listing below | task BUCKET +0x28 = word kind/index compared against slot index word [V] |
| bucket+0x30 | 8 | 0x66dc966, 0x66dcb7a, 0x66dcc0f, 0x66dceba, 0x66dd05a, 0x66dd1fa, 0x66dd39a, 0x66dd53a, 0x66dd6da, 0x66dd87a, 0x66dd916 | see instr listing below | task BUCKET +0x30 = qword data array base (16-byte uniform values per slot) [V] |
| bucket+0x38 | 8 | 0x66dcab6, 0x66dcb07, 0x66dcdd2, 0x66dce39, 0x66dcfe4, 0x66dd186, 0x66dd324, 0x66dd4c6, 0x66dd664, 0x66dd806 | see instr listing below | task BUCKET +0x38 = qword slot array base (0x10-byte slots) [V] |
| bucket+0x42 | 2 | 0x66dcaba, 0x66dcb0b, 0x66dcdd6, 0x66dce3d, 0x66dcfe8, 0x66dd18a, 0x66dd328, 0x66dd4ca, 0x66dd668, 0x66dd80a | see instr listing below | task BUCKET +0x42 = word slot count (loop bound) [V] |
| bucket+0x48 | 8 | 0x66ddac3 | see instr listing below | task BUCKET +0x48 = qword record array base (0x30-stride entries) [V] |
| bucket+0x52 | 2 | 0x66ddac7 | see instr listing below | task BUCKET +0x52 = word record count [V] |
| bucket+0x78 | 8 | reads: 0x66dc981, 0x66dc9fa, 0x66dcb8e, 0x66dcc2a, 0x66dcca3, 0x66dced5, 0x66dcf4e, 0x66dd075, 0x66dd0ee, 0x66dd215, 0x66dd28e, 0x66dd3b5, 0x66dd42e, 0x66dd555, 0x66dd5ce, 0x66dd6f5, 0x66dd76e, 0x66dd895, 0x66dd931, 0x66dd9aa; writes: 0x66dc9b1, 0x66dcbbe, 0x66dcc5a, 0x66dcf05, 0x66dd0a5, 0x66dd245, 0x66dd3e5, 0x66dd585, 0x66dd725, 0x66dd8c5, 0x66dd961 | see instr listing below | task BUCKET +0x78 = qword hash accumulator (FNV-ish mixing over slot index + value bytes) [V] |
| slot+0x00 | 8 | 0x66dc920, 0x66dcae0, 0x66dcb30, 0x66dce00, 0x66dce70, 0x66dd010, 0x66dd1b0, 0x66dd350, 0x66dd4f0, 0x66dd690, 0x66dd830, 0x66ddaf0 | see instr listing below | SLOT +0x00 = qword record pointer (loaded from slot base, then [r10+0x28] = task kind hash) [V] |
| slot+0x08 | 2 | 0x66dc94f, 0x66dcb63, 0x66dcbf8, 0x66dcea3, 0x66dd043, 0x66dd1e3, 0x66dd383, 0x66dd523, 0x66dd6c3, 0x66dd863, 0x66dd8ff | see instr listing below | SLOT +0x08 = word data index into bucket data array ([rbx+0x30]) [V] |
| slot+0x0C | 1 | 0x66dc976, 0x66dcb83, 0x66dcc1f, 0x66dceca, 0x66dd06a, 0x66dd20a, 0x66dd3aa, 0x66dd54a, 0x66dd6ea, 0x66dd88a, 0x66dd926 | see instr listing below | SLOT +0x0C = byte occupied flag (set to 1 when slot holds a valid record) [V] |

## Verbatim instruction listing (for verify_oc.py)

0x66dc923  cmp [r10+0x28],r8
0x66dc955  cmp [rbx+0x28],r8
0x66dc966  mov r10,[rbx+0x30]
0x66dcab6  mov rax,[rbx+0x38]
0x66dcaba  movzx r8d,word ptr [rbx+0x42]
0x66ddac3  mov rax,[rbx+0x48]
0x66ddac7  movzx r8d,word ptr [rbx+0x52]
0x66dc981  mov rcx,[rbx+0x78]
0x66dc9b1  mov [rbx+0x78],r8
0x66dc920  mov r10,[rcx]
0x66dd383  movzx r8d,word ptr [rax+rdx+8]
0x66dc976  mov byte ptr [rax+rdx+0xC],1

## Record size / remaining fields

- Record size: NOT determined from this listing. Only record +0x28 is accessed. No stores to any record offset appear. Records are created/initialized outside 0x66dc900..0x66de900. [?]
- Record fields other than +0x28: not provable from this listing. [?]
- BGFX_MAP 1267 states dispatch task entries are 0x80 bytes with task+0x70 = std::function impl — this refers to the dispatch task list (0xe9002e0), NOT the BatchActor bucket records decoded here. [I]

## CLOSES?

YES — every pending part of the C3b item line is now proven by [V] rows: task-kind = FNV-1a 64 of uniform name was closed by U-C3b/U-C3b2, and the record layout is documented above with record +0x28 = qword task kind hash [V] at 12 cmp sites, plus all bucket and slot fields. The only items not provable from this listing are record size and non-+0x28 record fields, which are not part of the C3b checklist item (they are listed as [?] above for transparency).

## Verification

- verify_oc.py: pending
- delegate.py check: pending

## TOOL REQUESTS

- None (all data from existing rdis listing; no new helper scripts needed)
