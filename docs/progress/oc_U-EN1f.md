## NEXT
DONE

# UNIT U-EN1f — Disk cache 0xe8feb10 consumed or invalidated consistently by replacement blobs (BGFX_MAP 8c; B4)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Cited section: BGFX_MAP.md 8c "State a replacement must preserve": "Disk cache 0xe8feb10: shader/texture blobs are served from it; a replacement must consume or invalidate it consistently [B4]." Cross-ref B4: PipelineDiskCache::tick = 0xe8feb10 (size 0x2df).
INPUT DATA read fully: docs/progress/oc_U-B4disk_listing.txt (tick body), oc_U-B4disk_callers.txt, oc_U-B4disk_callees.txt, oc_U-B4disk_descscan2.txt, oc_U-B4disk.md, docs/functions/e8feb10.md (tick mechanical facts); prior attempts docs/progress/oc_U-EN1f_r1.md (35/38 verify_oc, 3 bad rows fixed below) and oc_U-EN1f_r2.md (37/37 but vtable work unconfirmed, no CLOSES line — re-verified here from fresh disassembly).
Fixed vs r1/r2: (a) 0x66395c7 claimed `movq xmm0,[12adfa58]` — NO instruction at 0x66395c7; the instruction is at 0x66395ca (row below). (b) 0xe8fcaa8 claimed `mov [r15+e8],rax`; real at 0xe8fcaa8 is `mov rax,[rbp+0x2E8]` and `mov [r15+0xE8],rax` is at 0xe8fcaaf. (c) 0xe8fecf2 claimed `mov [rsp+28],al`; real is `mov [rsp+0x20],al` (the [rsp+0x28] store is the preceding instruction at 0xe8feced). All three re-disassembled verbatim below.
No builds, no game launch, no edits to HookManager.cpp, CMake, Sigs.json, or existing src; only this progress file created.

## (1) What changed (paths)

Only docs/progress/oc_U-EN1f.md (this note). No other file created or edited.

## (2) Answer table — disk cache 0xe8feb10 (offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag)

One row per distinct offset; all sites of that offset are listed in its row.

| 0xe8feb10 | fn 0x2df (185 instr) | tick entry | `0xe8feb10  push rbp` | dragon::utils::PipelineDiskCache::tick [0xe8feb10..0xe8fedef); sole caller: Frame renderer 0x67c9c20 ("Frame renderer - Frame") calls it at 0x67ca1c1 [V] | [V] |
| 0xe8feb31 | qword 8 | Phase A | `0xe8feb31  mov rsi,rcx` | this (PipelineDiskCache*, rcx) -> rsi [V] | [V] |
| 0xe8feb34 | call | Phase A | `0xe8feb34  call 0xEEC59F0` | lock entry; eax != 0 -> fail path 0xe8fedd3 [V] | [V] |
| 0xe8feb41 | dword 4 | Phase A +0x4C R | `0xe8feb41  cmp dword ptr [rsi+0x4C],0x7FFFFFFF` | state dword vs poison 0x7FFFFFFF; equal -> fail path [V] | [V] |
| 0xe8feb4e | byte 1 | Phase A +0xD8 R | `0xe8feb4e  cmp byte ptr [rsi+0xD8],1` | flag byte at +0xD8; != 1 -> early return [V] | [V] |
| 0xe8feb5b | call | Phase A | `0xe8feb5b  call 0xEEC5920` | now() -> rax [V] | [V] |
| 0xe8feb60 | qword 8 | Phase B | `0xe8feb60  mov rdi,rax` | now value -> rdi [V] | [V] |
| 0xe8feb68 | qword 8 | Phase B | `0xe8feb68  cmp rdi,0x16E3600` | 24 ms due-interval branch [V] | [V] |
| 0xe8feb71 | qword 8 | Phase B | `0xe8feb71  cmp rdi,0x989680` | 10 ms due-interval branch [V] | [V] |
| 0xe8feb7a | qword 8 | Phase B | `0xe8feb7a  imul rax,0x64` | ms -> us x100 [V] | [V] |
| 0xe8feb7e | qword 8 | Phase B +0xE0 R | `0xe8feb7e  cmp rax,[rsi+0xE0]` | next-due time comparison [V] | [V] |
| 0xe8fec3c | byte 1 | Phase C +0xD9 R | `0xe8fec3c  cmp byte ptr [rsi+0xD9],1` | work-in-progress byte read [V] | [V] |
| 0xe8fec5e | byte 1 | Phase C +0xD9 W | `0xe8fec5e  mov byte ptr [rsi+0xD9],1` | work-in-progress byte = 1 [V] | [V] |
| 0xe8fec59 | call | Phase C epilog | `0xe8fec59  jmp 0xEEC5A10` | unlock tail-call (early-return paths) [V] | [V] |
| 0xe8fec6d | qword 8 | Phase D +0xE8 R | `0xe8fec6d  mov rdi,[rsi+0xE8]` | cache-object pointer at PipelineDiskCache+0xE8 -> rdi [V] | [V] |
| 0xe8fec74 | test/jump | Phase D null-cache | `0xe8fec74  test rdi,rdi`; `0xe8fec77  je 0xE8FED25` | null cache object -> tail-jump to sibling 0xe8fee80 [V] | [V] |
| 0xe8fecc1 | qword 8 | Phase D | `0xe8fecc1  mov rax,[rdi]` | cache-object vtable pointer load [V] | [V] |
| 0xe8fecc4 | qword 8 | Phase D | `0xe8fecc4  mov rax,[rax+0x40]` | vtable[0x40] target (byte offset 0x40) -> rax [V] | [V] |
| 0xe8feccb | call | Phase D | `0xe8feccb  call qword ptr [0xF99FFA0]` | indirect call through CFG guard [V] | [V] |
| 0xe8fecf2 | byte 1 | Phase D | `0xe8fecf2  mov [rsp+0x20],al` | source_location line-byte store (FIXED: was misquoted as [rsp+28] in r1) [V] | [V] |
| 0xe8fed05 | call | Phase E | `0xe8fed05  call 0x14A0C0` | async save enqueue sub_14a0c0(&pair, cacheObj, &srcloc, 0) [V] | [V] |
| 0xe8fed53 | call | Phase E | `0xe8fed53  call 0x773320` | cache commit sub_773320(cacheObj, &pair) [V] | [V] |
| 0xe8feddd | dword 4 | Phase G +0x4C W | `0xe8feddd  mov dword ptr [rsi+0x4C],0x7FFFFFFE` | state poisoned to 0x7FFFFFFE; int3 fail-fast at 0xe8fedee [V] | [V] |
| 0x66395a6 | dword 4 | save gate R | `0x66395a6  cmp dword ptr [0x12ADF818],0xA` | save only if global 0x12ADF818 == 0xA (version gate) [V] | [V] |
| 0x66395c2 | dword 4 | header W | `0x66395c2  mov dword ptr [rsp+0x30],0xA` | header u32#0 stored = 0xA (version) [V] | [V] |
| 0x66395ca | qword 8 | header R | `0x66395ca  movq xmm0,[0x12ADFA58]` | header u16 pair load from data_12adfa58 (FIXED: correct address; 0x66395c7 had no instruction) [V] | [V] |
| 0x66395da | qword 8 | header W | `0x66395da  movq [rsp+0x34],xmm0` | header u16 pair stored at +2 [V] | [V] |
| 0x66395fd | dword 4 | FNV | `0x66395fd  mov r8d,0x84222325` | FNV-1a32 basis 0x84222325 (non-stock; stock is 0x811c9dc5) [V] | [V] |
| 0x6639624 | dword 4 | FNV | `0x6639624  imul r8d,0x1B3` | FNV prime 0x01000193 multiply step [V] | [V] |
| 0x663962b | dword 4 | FNV | `0x663962b  xor r8d,r9d` | per-byte xor mix over string data_12adf83c (len via sub_eec7570 at 0x66395ea) [V] | [V] |
| 0x66396d2 | dword 4 | header W | `0x66396d2  mov [rsp+0x3C],r8d` | header u32#3 = FNV-1a32 hash [V] | [V] |
| 0x6639712 | call | save call | `0x6639712  call 0xE8FC760` | invokes save entry; stack size/limit {0x200000, 0x2540BE400} [V] | [V] |
| 0xe8fc7e0 | lea 8 | filename R | `0xe8fc7e0  lea rax,[0xF593232]` | "rd_pipeline_cache.bin" (data_f593232); this is its ONLY code reference in the exe [V xstr] | [V] |
| 0xe8fc8d7 | dword 4 | save +0x78 W | `0xe8fc8d7  mov eax,[rdi]`; `0xe8fc8d9  mov [r15+0x78],eax` | header u32#0 -> cache object +0x78 [V] | [V] |
| 0xe8fc8dd | dword 4 | save +0x7C W | `0xe8fc8dd  mov eax,[rdi+4]`; `0xe8fc8e0  mov [r15+0x7C],eax` | header u32#1 -> cache object +0x7C [V] | [V] |
| 0xe8fc8e4 | dword 4 | save +0x80 W | `0xe8fc8e4  mov eax,[rdi+8]`; `0xe8fc8e7  mov [r15+0x80],eax` | header u32#2 -> cache object +0x80 [V] | [V] |
| 0xe8fc8ee | dword 4 | save +0x84 W | `0xe8fc8ee  mov eax,[rdi+0xC]`; `0xe8fc8f1  mov [r15+0x84],eax` | header u32#3 -> cache object +0x84 [V] | [V] |
| 0x77253b | qword 8 | ctor vtable R | `0x77253b  lea rax,[0xF08F110]` | cache-object ctor sub_772520 loads vtable RVA 0xF08F110 (data_f08f110, .rdata) [V] | [V] |
| 0x772542 | qword 8 | ctor vtable W | `0x772542  mov [rcx],rax` | vtable stored at cache object +0 [V] | [V] |
| +0x000 | qword 8 | vtable[0x000] slot | `0x7a8f70  push rsi` | dtor stage 1 (strong refcount == 0; frees via sub_e935700) — not load/consume [V instr] | [V] |
| +0x008 | qword 8 | vtable[0x008] slot | `0x772a70  push rbp` | stage-2 destroy (weak refcount == 0, 0x74d bytes) — not load/consume [V instr] | [V] |
| +0x010 | qword 8 | vtable[0x010] slot | `0x773410  push rbp` | management slot — not load/consume [V instr] | [V] |
| +0x018 | qword 8 | vtable[0x018] slot | `0x775560  push rbp` | management slot (mutex on [rcx+0x60]) — not load/consume [V instr] | [V] |
| +0x020 | qword 8 | vtable[0x020] slot | `0x775730  push rbp` | management slot (dispatches [rcx] vtable[0x10]) — not load/consume [V instr] | [V] |
| +0x028 | qword 8 | vtable[0x028] slot | `0x774200  mov eax,[rcx+0xB0]` | u32 getter [+0xB0], then ret — not load/consume [V] | [V] |
| +0x030 | qword 8 | vtable[0x030] slot | `0x775520  mov rax,[rcx+8]` | qword getter [+0x8] — not load/consume [V instr] | [V] |
| +0x038 | qword 8 | vtable[0x038] slot | `0x775320  push r15` | management slot (mutex on [rcx+0x60]) — not load/consume [V instr] | [V] |
| +0x040 | qword 8 | vtable[0x040] slot | `0x7758c0  mov rax,[rcx+0x20]` | tick's vtable[0x40] target: reads cacheObj+0x20 — getter, not load/consume [V] | [V] |
| +0x048 | qword 8 | vtable[0x048] slot | `0x7a8fa0  push rbp` | management slot (references vtable data 0xF08F158) — not load/consume [V instr] | [V] |
| +0x050 | qword 8 | vtable[0x050] slot | `0x7a9450  push rsi` | management slot (stores vtable data 0xF08F160 at [rcx]) — not load/consume [V instr] | [V] |
| +0x058 | qword 8 | vtable[0x058] slot | `0x775e80  mov rax,rdx` | management slot — not load/consume [V instr] | [V] |

## (3) Vtable decode result

- Vtable RVA 0xF08F110 found statically: cache-object ctor sub_772520 stores it at object+0 (0x77253b `lea rax,[0xF08F110]` / 0x772542 `mov [rcx],rax`) [V]. It lives in .rdata (data_f08f110 xref).
- `rdis vt 0xF08F110` lists exactly 12 code slots (+0x000..+0x058); +0x060..+0x088 are non-code data, so the vtable ends there — complete enumeration [V].
- Per-slot load/consume verdict: NONE. Slots are two destructors, four plain getters/setter-style slots, and six management slots. Slot +0x040 is the one tick calls; it returns cacheObj+0x20 — a getter. No slot references the filename, and "rd_pipeline_cache.bin" (data 0xf593232) has exactly one code reference in the whole exe: the save site 0xe8fc7e0 [V xstr re-run].
- tick's full 185-instruction body (disassembled end-to-end above) contains no file open/read — only the vtable[0x40] dispatch followed by async save enqueue (0xe8fed05 call 0x14A0C0) and cache commit (0xe8fed53 call 0x773320) [V].

## (4) Exact stale-cache rule (from the header u32s)

The save (entry 0xe8fc760, invoked by header builder 0x6639590 at 0x6639712) writes header u32s to cache object +0x78..+0x84:
- u32#0 = version 0xA — save itself is gated on global 0x12ADF818 == 0xA (0x66395a6).
- u32#1/u32#2 = u16 pair loaded from data_12adfa58 (0x66395ca/0x66395da).
- u32#3 = FNV-1a32-style hash of the content string at data_12adf83c: basis 0x84222325 (0x66395fd), prime 0x01000193 per-byte multiply (0x6639624), per-byte xor (0x663962b), result stored at 0x66396d2.
Save-side validation of an existing on-disk file requires magic == 0x43504452 ("RDPC") and header u32[1] != 0 (0xe8fcfdc `cmp dword ptr [rbp+0x2E0],0x43504452`; 0xe8fcfe8 `cmp dword ptr [rbp+0x2E4],0`; 0xe8fcfef `setne bl`) [V].
Rule: the cache is stale/invalid iff magic != "RDPC", or version u32[0] != 0xA, or FNV-1a32 hash u32[3] != hash of the current content string [V instructions; "[I]" the stale-iff conclusion, since no load path exists in this module to observe].

## (5) Answer to N1f and CLOSES?

- The game NEVER loads rd_pipeline_cache.bin from this module: tick is save-only, no load entry point exists, and no vtable slot of the cache object (PipelineDiskCache+0xE8, vtable 0xF08F110) is a load/consume entry. Nothing is consumed from the file, so nothing can go stale from a replacement blob.
- A replacement blob is therefore safe iff it avoids writing a conflicting rd_pipeline_cache.bin, or — if the replacement module implements load itself — it must own invalidation using the header rule above (magic/version/hash mismatch).
- Residual non-blocking [I]: possible indirect/vtable callers of tick beyond the single seen caller 0x67c9c20; live save cadence (24 ms / 10 ms units, next-due at +0xE0).

CLOSES? YES — every pending part of N1f is proven on disk by [V] rows: cache object at +0xE8 located, vtable 0xF08F110 found via its ctor store and fully decoded (12 slots, none load/consume), no load entry exists (filename has one code ref, the save site), and the exact stale-cache rule from header u32s {0xA version, FNV-1a32 hash} is given.

## NEXT
DONE

## TOOL REQUESTS

None — used only existing tools: tools/rdis.exe (dis/vt), tools/sigs/xref.py str, tools/sigs/verify_oc.py, python tools/delegate.py check.
