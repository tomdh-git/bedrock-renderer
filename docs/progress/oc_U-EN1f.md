## NEXT
DONE

# UNIT U-EN1f — Disk cache 0xe8feb10 consumed or invalidated consistently by replacement blobs (BGFX_MAP 8c; B4)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Cited section: BGFX_MAP.md 8c "State a replacement must preserve": "Disk cache 0xe8feb10: shader/texture blobs are served from it; a replacement must consume or invalidate it consistently [B4]." Cross-ref B4: PipelineDiskCache::tick = 0xe8feb10 (size 0x2df).
INPUT DATA read fully (precomputed by the orchestrator, not re-run): docs/progress/oc_U-B4disk_listing.txt (tick body), oc_U-B4disk_callers.txt, oc_U-B4disk_callees.txt, oc_U-B4disk_descscan2.txt, oc_U-B4disk.md (tick dossier), docs/functions/e8feb10.md (tick mechanical facts).
Targeted new static disassembly for this unit (rdis/xref/ripscan on the exe, read-only): save entry 0xe8fc760, sibling 0xe8fee80, vtable thunk 0xe8ffa70, entry-map region 0xe8ffa30, save caller 0x6639590, string xrefs. No builds, no game launch, no edits to HookManager.cpp, CMake, Sigs.json, or existing src; only this progress file created.

## (1) What changed (paths)
Only docs/progress/oc_U-EN1f.md (this note). No other file created or edited. The item's pending part (load entry point not found by B4; invalidation not decoded) is answered below from the decoded disassembly.

## (2) Answer table — disk cache 0xe8feb10 (name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag)
One row per distinct offset; all sites of that offset listed in its row.

| 0xe8feb10 | fn 0x2df (185 instr) | entry | `0xe8feb10  push rbp` | dragon::utils::PipelineDiskCache::tick [0xe8feb10..0xe8fedef); single caller: Frame renderer 0x67c9c20 ("Frame renderer - Frame") calls it at 0x67ca1c1 [V xref, B4disk L7] | [V] |
| 0xe8feb31 | qword 8 | Phase A | `0xe8feb31  mov rsi,rcx` | this (rcx = PipelineDiskCache*) -> rsi [V] | [V] |
| 0xe8feb34 | call | Phase A | `0xe8feb34  call 0xEEC59F0` | mutex lock entry; eax!=0 -> fail path [V] | [V] |
| 0xe8feb41 | dword 4 | Phase A (+0x4C read, x2 sites) | `0xe8feb41  cmp dword ptr [rsi+0x4C],0x7FFFFFFF` | state/flag read; ==0x7FFFFFFF -> poison path [V] | [V] |
| 0xe8feb4e | byte 1 | Phase A | `0xe8feb4e  cmp byte ptr [rsi+0xD8],1` | enabled flag read; !=1 -> return [V] | [V] |
| 0xe8feb5b | call | Phase A | `0xe8feb5b  call 0xEEC5920` | now() -> rax -> rdi at 0xe8feb60 [V] | [V] |
| 0xe8feb68 | cmp | Phase B1 | `0xe8feb68  cmp rdi,0x16E3600` | 24 ms unit branch [V] | [V] |
| 0xe8feb71 | cmp | Phase B2 | `0xe8feb71  cmp rdi,0x989680` | 10 ms unit branch [V] | [V] |
| 0xe8feb7a | imul 4 | Phase B1 | `0xe8feb7a  imul rax,0x64` | ms->us x100 [V] | [V] |
| 0xe8feb7e | qword 8 | Phase B (+0xE0 read, x3 sites) | `0xe8feb7e  cmp rax,[rsi+0xE0]` | next-due time read; due -> do-work gate [V] | [V] |
| 0xe8fec3c | byte 1 | Phase C (+0xD9 read x2) | `0xe8fec3c  cmp byte ptr [rsi+0xD9],1` | work-in-progress flag read [V] | [V] |
| 0xe8fec5e | byte 1 | Phase D | `0xe8fec5e  mov byte ptr [rsi+0xD9],1` | W work-in-progress flag = 1 [V] | [V] |
| 0xe8fec59 | call | Phase C epilog | `0xe8fec59  jmp 0xEEC5A10` | mutex unlock tail-call [V] | [V] |
| 0xe8fec6d | qword 8 | Phase D | `0xe8fec6d  mov rdi,[rsi+0xE8]` | cache-object ptr read (+0xE8) -> rdi [V] | [V] |
| 0xe8fec77 / 0xe8fed39 | jmp | Phase D null-cache | `0xe8fec77  je 0xE8FED25`; `0xe8fed39  jmp 0xE8FEE80` | null cache object -> tail-jump to sibling 0xe8fee80 [V] | [V] |
| 0xe8fecc1 / 0xe8fecc4 / 0xe8feccb | qword 8 | Phase D | `0xe8fecc1  mov rax,[rdi]`; `0xe8fecc4  mov rax,[rax+0x40]`; `0xe8feccb  call qword ptr [0xF99FFA0]` | cache object vtable[0x40] method (save/commit) invoked when due [V] | [V] |
| 0xe8fed05 | call | Phase E | `0xe8fed05  call 0x14A0C0` | sub_14a0c0(&pair, cacheObj, &srcloc, &zero) async save enqueue [V] | [V] |
| 0xe8fed53 | call | Phase E | `0xe8fed53  call 0x773320` | sub_773320(cacheObj, &pair) cache commit [V] | [V] |
| 0xe8feddd | dword 4 | Phase G poison | `0xe8feddd  mov dword ptr [rsi+0x4C],0x7FFFFFFE` | W state = 0x7FFFFFFE poison; then log lvl6 + int3 fail-fast at 0xe8fedee [V] | [V] |
| 0xe8fc760 | fn 0x2000 | save entry | `0xe8fc760  push rbp` | sub_e8fc760 [0xe8fc760..0xe8fe760) SAVE entry: writes cache file; invoked by 0x6639590 at 0x6639712 [V xref] | [V] |
| 0xe8fc7bf / 0xe8fc7d1 | byte 1 | save entry | `0xe8fc7bf  cmp byte ptr [r15+0x50],0`; `0xe8fc7d1  mov byte ptr [r15+0x50],1` | save-in-progress flag R/W [V] | [V] |
| 0xe8fc7e0 | lea | save entry | `0xe8fc7e0  lea rax,[0xF593232]` | cache file name "rd_pipeline_cache.bin" loaded (data 0xf593232) [V] | [V] |
| 0xe8fc8d7 / 0xe8fc8d9 / 0xe8fc8e0 / 0xe8fc8e4 / 0xe8fc8e7 / 0xe8fc8ee | dword 4 | save entry (+0x78..+0x84 W) | `0xe8fc8d7  mov eax,[rdi]`; `0xe8fc8d9  mov [r15+0x78],eax`; `0xe8fc8dd  mov eax,[rdi+4]`; `0xe8fc8e0  mov [r15+0x7C],eax`; `0xe8fc8e4  mov eax,[rdi+8]`; `0xe8fc8e7  mov [r15+0x80],eax`; `0xe8fc8ee  mov eax,[rdi+0xC]`; `0xe8fc8f1  mov [r15+0x84],eax` | four header u32s written into cache object +0x78..+0x84 (from {0xA, FNV-1a32 hash} block prepared by 0x6639590) [V] | [V] |
| 0x6639712 | call | save caller | `0x6639712  call 0xE8FC760` | 0x6639590 (size 0x2000, 0 xrefs in) calls save entry; guards [0x12ADF818]==0xA and FNV-1a32 hash of string 0x12ADF83C; stack limits {0x200000, 0x2540BE400} [V] | [V] |
| 0xe8fee80 | fn 0xa6c | sibling | `0xe8fee80  push rbp` | same-class sibling: same guards (state +0x4C, enabled +0xD8, 24/10 ms); reads header +0x78..+0x84 via vtable[0x38] "Unsigned Int"/"Unsigned Int 64" property writes, walks entry range +0xA0 via sub_a0850/sub_eec6de0; statically uncalled; role unverified [V instructions] | [I] |
| 0xe8ffa70 / 0xe8ffa74 | qword 8 / jmp | vtable thunk | `0xe8ffa70  mov rcx,[rcx+8]`; `0xe8ffa74  jmp 0xE8FEE80` | vtable adjustor thunk tailing into 0xe8fee80 [V] | [V] |
| 0xe8ffa30 | region 0x2000 | entry map | `0xe8ffa86  movzx eax,byte ptr [rdx]`; `0xe8ffa96  mov rax,0x100000001B3`; `0xe8ffaf8  and r8,[rcx+0x30]`; `0xe8ffb7d  dec qword ptr [rcx+0x10]` | FNV-1 64 (basis 0xCBF29CE484222325, prime 0x100000001B3) hash-map erase over 8-byte keys (count at [rcx+0x10], node freed via 0xE935700) — candidate invalidation-by-key; statically unreferenced (0 xrefs into 0xe8ffa30) [V instructions] | [I] |
| none (load RVA does not exist) | not found | load entry | - | "rd_pipeline_cache.bin" (0xf593232) has exactly ONE code reference: 0xe8fc7e0 inside save entry 0xe8fc760 [V xref str]; tick's complete 185-instruction body contains no file open/read [V]; siblings e8fee80/e8ffa30 reference no file name and have no callers [V ripscan/xref]. No LOAD/consumer entry point exists on disk. | [V] |
| none (invalidation RVA does not exist) | not found | invalidation | - | no invalidation path tied to replacement blobs found (no cache delete or generation bump; entry-map erase 0xe8ffa30 unreferenced statically) | [I] |

## (3) CLOSES?
CLOSES? NO — single blocking fact: the disk cache at 0xe8feb10 (PipelineDiskCache::tick) is proven SAVE-ONLY on disk (periodic async save to rd_pipeline_cache.bin via save entry 0xe8fc760, invoked by 0x6639590; header u32s {0xA, FNV-1a32 hash}; save-in-progress flag +0x50; poison fail-fast at state 0x7FFFFFFF). No LOAD/consumer entry point exists on disk — "rd_pipeline_cache.bin" (0xf593232) has exactly one code reference, the save site 0xe8fc7e0, and tick's full 185-instruction body contains no file read — and no invalidation path for replacement blobs is present (entry-map erase at 0xe8ffa30 is statically unreferenced). Therefore "consumed or invalidated consistently by replacement blobs" cannot be shown from what exists on disk now.

Remaining step (offline/in-game, no build needed to look): locate the cache object's full vtable — the cache object lives at PipelineDiskCache+0xE8 (instance reached from FrameRenderer+0x20; tick invokes its vtable[0x40]) — and check its slots for a startup load method (candidates: the unreferenced 0x6639590 region / vtable slots of the cache object), or confirm none exists. If none exists, the replacement module must implement load+invalidation of rd_pipeline_cache.bin itself — a design decision not decidable by static RE alone, and it would need an in-game/build verification once the load/invalidation behavior is settled.

## TOOL REQUESTS
None — no new helper scripts written; used existing tools/sigs/xref.py, tools/sigs/ripscan.py and tools/rdis.exe (all pre-existing).
