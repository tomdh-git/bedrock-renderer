## NEXT
DONE

# UNIT U-EL3e — L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Basis (from oc_U-EL3e_r1.md / oc_U-EC3b.md, check OK 11 rows)

Part (1) "Task kind = FNV-1a 64 of uniform name" — CLOSED by U-C3b/U-C3b2 (0x481CF7B16E204CF8 = fnv1a("UseAlphaRewrite"), 0x48603E36F5CE3EB2 = fnv1a("LightWorldSpaceDirection") [V per BGFX_MAP 6ad]).
Part (2) "record layout pending" — THIS UNIT.

Known [V] from oc_U-EL3e_r1.md:
- BatchActor extractor 0x66d9af0 (0x66d9af0..0x66e26a7), interior 0x66dc900..0x66de900 (find-or-create / uniform-bind loops over bucket rbx):
  - bucket rbx = material holder {MaterialInstance* +0x00, UniformBlock @+0x08}: block+0x20 = holder+0x28 u64 data size, block+0x28 = holder+0x30 data-array ptr, block+0x30 = holder+0x38 slot-table ptr, block+0x3A = holder+0x42 u16 slot count, block+0x40 = holder+0x48 record-table ptr.
  - slot (0x10 bytes) at [rbx+0x38]: +0x00 qword record pointer, +0x08 word data index, +0x0C byte occupied/dirty flag [V].
  - record array [rbx+0x48]: 0x30-stride entries, +0x00 = record pointer [V].
  - task RECORD object r10 = [slot+0x00] = [record_array_entry+0x00]: only verified field was +0x28 = qword task kind hash, compared at 12+ cmp sites [V].

NEW [V] this unit (bindMaterial 0xe86d7f0, an independent consumer of the same record):
- 0xe86d90d  mov rax,[r14]          (r14 walks slot table [holder+0x38]; rax = slot+0x00 = record ptr)
- 0xe86d910  cmp byte ptr [rax+0x34],1   — record+0x34 u8 flag, processed only when == 1
- 0xe86d91f  mov r12,[rax+0x28]      — record+0x28 = hash, then used as MaterialInstance map key
- 0xe86d92e  mov rdx,[rcx+0x398]     (rcx = [holder+0x0] = MaterialInstance*)  MaterialInstance+0x398 = map mask
- 0xe86d93f  mov r8,[rcx+0x380]      — MaterialInstance+0x380 = map buckets
- 0xe86da25  cmp [rdx+0x28],rcx      — map lookup compares node+0x28 hash
- 0xe86db11, 0xe86df12, 0xe86e38a: cmp byte ptr [rax+0x34],1 (same flag check, more sites)
- 0xe86e399  mov r10,[rax+0x28]; 0xe86e519  mov rax,[rdx+0x28] (more +0x28 hash reads)

## Pending (this unit): task RECORD size and task RECORD fields other than +0x28 kind hash

Record size lower bound: ≥ 0x35 (fields +0x28 qword and +0x34 byte both observed). No upper bound proven. No record allocator/initializer found anywhere in the extractor path; records are created outside this unit's code (upstream of 0x66d9af0 / 0xe86d7f0), presumably at material/uniform registration.

## Attempts this unit (new angle; nothing already proven was redone)

1. Full static read of sub_66d9af0 (fn_clean.txt, 0x66d9af0..0x66e26a7): records are only READ ([r10+0x28] kind cmp ×33, slot +0x08/+0x0C, 16-byte data writes to data array [rbx+0x30]); no write to any record offset, no store to record+0x28, no record allocation inside the function.
2. Caller chain: rdis callers 0x66d9af0 -> exactly 1 caller, sub_6646980; rdis callers 0x6646980 -> sub_66466e0. Neither function writes slot+0x00 or any record field; sub_6646980 tail-jumps to 0x66D9AF0 with a pre-built bucket.
3. ripscan of kind-hash globals 0x129F8320 and 0x129F9128..0x129F91F8: every code reference is a consumer (load + cmp [record+0x28]); no code writes a kind hash into a record.
4. Bucket resolver sub_675e440: allocates a 0x20 chain node (not a record); confirms bucket fields but creates no record objects.
5. bindMaterial sub_e86d7f0 (new consumer): confirms record+0x28 hash + record+0x34 flag; no record creation.
6. sub_79580 (uniform name copy), sub_aa710 (0x50-byte node — different object: +0x28 there is string capacity, not hash), sub_567dba0 (same string-keyed map, 0x50 alloc) — none is the record allocator.
7. Dossiers docs/functions/5679db0.md, 66d9af0.md, 6698e30.md reviewed: no record creation/allocation or record size.
8. Live capture docs/data/live/batchActor_extractor.txt exists but yields no usable record object address; livemem requires a specific target and no scanning is allowed, so it cannot settle the size.

## Task record layout table

| name | rva or offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| task RECORD +0x28 = qword task kind hash (FNV-1a 64 of uniform name) | record+0x28 | 8 | `0x66dc923  cmp [r10+0x28],r8` (r10 = [slot+0x00] = record pointer); same cmp at `0x66dcae3`, `0x66dcb33`, `0x66dce03`, `0x66dce73`, `0x66dd013`, `0x66dd1b3`, `0x66dd353`, `0x66dd4f3`, `0x66dd693`, `0x66dd833`, `0x66ddaf3`, `0x66ddc53`, `0x66dddc3`, `0x66dea53`, `0x66de103`, `0x66de263`, `0x66de373`, `0x66de533`, `0x66df283`, `0x66df483`; also bindMaterial `0xe86d91f  mov r12,[rax+0x28]`, `0xe86da25  cmp [rdx+0x28],rcx`, `0xe86db47  cmp [rsi+0x28],rcx`, `0xe86e399  mov r10,[rax+0x28]`, `0xe86e519  mov rax,[rdx+0x28]` | [V] |
| task RECORD +0x34 = u8 flag (bindMaterial processes record only when flag == 1) | record+0x34 | 1 | `0xe86d910  cmp byte ptr [rax+0x34],1`; same check at `0xe86db11`, `0xe86df12`, `0xe86e38a` (rax/rsi = record pointer from slot+0x00) | [V] |
| task RECORD size | record object | ? | — (no instruction allocates or sizes the record object) | [?] |
| task RECORD fields other than +0x28 and +0x34 | record+0x00..+0x27, +0x35.. | ? | — (no store/read of any other record field observed) | [?] |
| slot +0x00 = qword record pointer (context: how the record is reached) | holder+0x38 slot +0x00 | 8 | `0x66dc920  mov r10,[rcx]` (rcx walks slot array [rbx+0x38], stride 0x10); `0xe86d90d  mov rax,[r14]` (r14 walks slot table [holder+0x38]) | [V] |
| slot +0x08 = u16 data index/offset | slot+0x08 | 2 | `0x66dc94f  movzx r8d,word ptr [rax+rdx+8]` | [V] |
| slot +0x0C = u8 occupied/dirty flag | slot+0x0C | 1 | `0x66dc976  mov byte ptr [rax+rdx+0xC],1` | [V] |
| holder+0x28 (UniformBlock+0x20) = u64 data size | holder+0x28 | 8 | `0x66dc955  cmp [rbx+0x28],r8`; same at `0x66db50d`, `0x66dc435`, `0x66dc5c5`, `0x66dc78d` | [V] |
| holder+0x30 (UniformBlock+0x28) = data-array pointer | holder+0x30 | 8 | `0x66dc966  mov r10,[rbx+0x30]`; `0x66dc971  movups [r10+r8],xmm0` (16-byte uniform value write to data[data_index]) | [V] |
| holder+0x38 (UniformBlock+0x30) = slot-table pointer | holder+0x38 | 8 | `0x66dc8f1  mov rax,[rbx+0x38]` | [V] |
| holder+0x42 (UniformBlock+0x3A) = u16 slot count | holder+0x42 | 2 | `0x66dc8f5  movzx r8d,word ptr [rbx+0x42]` | [V] |
| holder+0x48 (UniformBlock+0x40) = record-table pointer (0x30-stride entries, +0x00 = record ptr) | holder+0x48 | 8 | `0x66ddaf0  mov r10,[rcx]` walking [rbx+0x48]; `0x66ddaf3  cmp [r10+0x28],r8`; `0x66ddaf9  add rcx,0x30` | [V] |
| MaterialInstance+0x380 = map buckets | holder+0x0+0x380 | 8 | `0xe86d93f  mov r8,[rcx+0x380]` (rcx = [holder+0x0] = MaterialInstance*) | [V] |
| MaterialInstance+0x398 = map mask | holder+0x398 | 4 (loaded as qword) | `0xe86d92e  mov rdx,[rcx+0x398]` | [V] |

## CLOSES?

NO — blocking fact: the task record size and every record field other than +0x28 kind hash and +0x34 u8 flag were never observed written or read; no record allocator/initializer was found anywhere in the extractor path (records are created outside this unit's code), so the record size is not derivable from any [V] row and remains [?]. Only record+0x28 (kind hash) and record+0x34 (flag) are [V].

## Verification

- All quoted `0xRVA  instr` lines copied verbatim from rdis disassembly of the exe (1.26.62.01): sub_66d9af0 listing (fn_clean) and sub_e86d7f0 listing.
- verify_oc.py: pending
- delegate.py check: pending

## TOOL REQUESTS

- None (record allocator not found statically; livemem cannot be used without a record object address and scanning is disallowed)
