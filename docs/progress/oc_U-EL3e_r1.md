## NEXT
DONE

# UNIT U-EL3e — L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout pending

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Basis (from oc_U-EC3b.md, check OK 11 rows)

Part (1) "Task kind = FNV-1a 64 of uniform name" — CLOSED by U-C3b/U-C3b2 (0x481CF7B16E204CF8 = fnv1a("UseAlphaRewrite"), 0x48603E36F5CE3EB2 = fnv1a("LightWorldSpaceDirection") [V per BGFX_MAP 6ad; also RenderMarkHook.h cites kind 0x48603E36F5CE3EB2]).
Part (2) "record layout pending" — THIS UNIT.
BGFX_MAP 6ad: task-record kinds seen by RenderMarkHook are FNV-1a 64 of uniform names; the BatchActor extractor 0x66d9af0 binds uniforms by FNV-1a name hash.
BatchActor extractor 0x66d9af0, interior 0x66dc900..0x66de900 (find-or-create / uniform-bind loops over bucket rbx):
- bucket: slot array [rbx+0x38] (0x10-byte slots), data array [rbx+0x30], record array [rbx+0x48] (0x30-stride entries); bucket +0x28 word kind/index, +0x42 word slot count, +0x52 word record count, +0x78 qword hash accumulator.
- slot (0x10 bytes): +0x00 qword record pointer, +0x08 word data index, +0x0C byte occupied flag [V].
- record array entry (0x30 bytes): +0x00 = record pointer [V] (`mov r10,[rcx]` walking [rbx+0x48], stride `add rcx,0x30`; count*0x30 via `shl ecx,4; lea rdx,[rcx+rcx*2]`).
- task RECORD object r10 = [slot+0x00] = [record_array_entry+0x00]: only verified field is +0x28 = qword task kind hash, compared at 12+ cmp sites [V].

## Pending (this unit): task RECORD size and task RECORD fields other than +0x28 kind hash

Records are only *compared* (`cmp [r10+0x28],r8`) in 0x66dc900..0x66de900; no store to any record offset and no record allocation/initialization appears in this path (U-EC3b confirmed records are created outside it). Bucket setup (0x66dae40..0x66db020) moves whole 0x90-stride bucket elements (`add rbx,0x90`) and copies bucket fields (+0,+8,+0x80,+0x88) but does not create record objects. No function was found that stores the FNV-1a kind into a record or that allocates a record object, so record size and fields past +0x28 are not provable by [V] rows statically. RenderMarkHook.h (src) only documents a chams hook's use of "a record at data+0x78" (+0x30, +0xB8, +0x84) — hook-author notes, not disassembly proof of the general task record.

## Task record layout table

| name | rva or offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| task RECORD +0x28 = qword task kind hash (FNV-1a 64 of uniform name) | record+0x28 | 8 | `0x66dc923  cmp [r10+0x28],r8`; same cmp at `0x66dcae3`, `0x66dcb33`, `0x66dce03`, `0x66dce73`, `0x66dd013`, `0x66dd1b3`, `0x66dd353`, `0x66dd4f3`, `0x66dd693`, `0x66dd833`, `0x66ddaf3`, `0x66ddc53`, `0x66dddc3`, `0x66dea53` (r10 = [slot+0x00] = record pointer) | [V] |
| record array entry stride (confirms entries are 0x30 bytes holding a record pointer at +0x00) | record array [rbx+0x48] entry | 0x30 (entry) | `0x66ddaf9  add rcx,0x30`; `0x66ddacf  shl ecx,4` / `0x66ddad2  lea rdx,[rcx+rcx*2]` (count*0x30); `0x66ddaf0  mov r10,[rcx]` then `0x66ddaf3  cmp [r10+0x28],r8` | [V] |
| slot stride | slot array [rbx+0x38] slot | 0x10 (slot) | `0x66dc929  add rcx,0x10`; `0x66dc949  and edx,0xFFFF0`; `0x66dc94f  movzx r8d,word ptr [rax+rdx+8]` | [V] |
| task RECORD size | record object | ? | — (no instruction allocates or sizes the record object) | [?] |
| task RECORD fields other than +0x28 | record+0x00, +0x08..+0x27, +0x30.. | ? | — (no store/read of any record field past +0x28 observed) | [?] |

## CLOSES?

NO — blocking fact: the task record size and every record field other than +0x28 kind hash were never observed written or read; no record allocator/initializer was found (records are only *compared* at +0x28 within 0x66dc900..0x66de900 and are created outside that path), so they are not provable by [V] rows. Only record+0x28 = qword task kind hash is [V].

## Verification

- verify_oc.py: pending
- delegate.py check: pending

## TOOL REQUESTS

- None (all data from rdis disassembly of 0x66dc900..0x66de900 and 0x66dae40..0x66db020; no new helper scripts needed)
