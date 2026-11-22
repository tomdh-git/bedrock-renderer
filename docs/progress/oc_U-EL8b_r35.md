## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?]) + final `CLOSES?` line stating YES only if every pending part of the item line is proven by [V] rows, else NO plus the single blocking fact.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA/capture line cited, verbatim line quoted), [I] inferred (say from what), [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis/live capture) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste the input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized. No "etc.".

## Status (this session = RETRY #1)

Earlier notes read: oc_U-EL8b_r34.md (latest) + oc_U-EL8b_r33.md; both end CLOSES? NO. Everything in r1..r34 is carried as proven and NOT re-derived: atlas registration [V] (TerrainAtlas idx6 / ItemAtlas idx7 via sub_186e6a0/sub_1870de0, triggered by ServerLevelLoad sub_1042320 + initStep1 sub_8f6810), no createTexture/resizeTexture inside sub_186e6a0/sub_1870de0 [V], TextureD3D12::create callers = createTexture+resizeTexture only [V], live census all format 0x1C uncompressed numMips=1 [V live], BC1/BC3/BC7/DXT strings unreferenced [V], numMips +0xB1 only store [V], cross-module pointer 0x00007FF6A8215838 at obj+0x00 [V live], sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release [V+V live], texgroup_load/texload = consumers [V].

Blocking fact (single, still open): the atlas TEXTURE-CREATION STITCHER is not located — no code in this exe builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26) or resizeTexture (slot 31, takes mips) with atlas parameters. Static analysis exhausted (orchestrator hint 2026-11-22).

## New angles tried this session (blocking fact attack)

1. Re-read docs/data/live/mc_root_4e05e50_callers.txt (150 hits, 32 samples): line 3 `CALLER ret=0x1289496` — single caller of sub_4e05e50 is sub_12893d0 (TexturePtr release/collect; `0x1289496  nop` after `0x1289490  call qword ptr [0xF99FFA0]`). Consumers only, no stitcher [V live].
2. Re-read docs/data/live/l8b_texcreate_record.txt (24 samples): line 3 `CALLER ret=0xE814560` — all 24 creations format 0x1C uncompressed, numMips=1, no atlas names [V live]. Same as r10; nothing new.
3. `python tools/livecap/request.py result l8b_resizetex_slot31` -> "no result yet (orchestrator has not run it)"; capture queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) — no new capture can be queued right now.
4. `python tools/sigs/xref.py str "TerrainAtlas"` -> 0xf55cdd3 refs=[('0x186f731','0x186e6a0')] only: the name is referenced solely by registration inside sub_186e6a0 [V].
5. `python tools/sigs/xref.py str "ItemAtlas"` -> 0xf55cde0 refs=[('0x1870fc','0x186e6a0')] only: same [V].
6. xref for BC1/BC3/BC7/DXT1-DXT5 and GenMip/mips code/task: negative (carried [V via xref]); no stitcher found by callers/xr/vt/descscan2 angles in r1..r34.

Result: no new angle located the stitcher. Blocking fact stands; reported honestly below.

## Field map (one row per distinct offset)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas node name string (idx 6) | 0x186f731 | 8 | 0xF55CDD3 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name loaded for atlas node; idx 6 = TerrainAtlas | [V] |
| ItemAtlas node name string (idx 7) | 0x186f7fc | 8 | 0xF55CDE0 | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name loaded for atlas node; idx 7 = ItemAtlas | [V] |
| atlas node +0 = name pointer | 0x1870ec5 | 8 | [rsi]+0x0 | `0x1870ec5  mov [rsi],rax` | 0x48-byte atlas node (sub_1870de0): +0 stores the name pointer | [V] |
| atlas node +8 = stored index | 0x1870ecb | 4 | [rsi]+0x8 | `0x1870ecb  mov [rsi+8],eax` | node +8 stores the atlas slot index | [V] |
| refcounted field setter (not texture creation) | 0x18711b7 | 5 | - | `0x18711b7  call 0x772520` | sub_772520 refcounted setter for name/region fields; sets fields, does not create textures | [V] |
| registry '*' 0x2A sentinel scan | 0x1870e30 | 4 | [rcx]+0x0 | `0x1870e30  cmp dword ptr [rcx],0x2A` | slot scan compares each entry to '*' (0x2A) sentinel; 42 slots 0..0x29 | [V] |
| slot cursor increment | 0x1870f28 | 1 | - | `0x1870f28  inc r14d` | slot cursor r14d incremented, bounded by `cmp r14d,0x29` | [V] |
| slot bound 0x29 | 0x1870f2b | 3 | - | `0x1870f2b  cmp r14d,0x29` | bound 0x29 (max slot 41); `ja` exits scan when exceeded | [V] |
| chosen slot index written out | 0x1870f40 | 4 | [r15]+0x0 | `0x1870f40  mov [r15],r14d` | resolved atlas slot index stored to output | [V] |
| trigger from ServerLevelLoad | 0x104237e | 5 | - | `0x104237e  call 0x186e6a0` | sub_1042320 (ServerLevelLoad) calls registration sub_186e6a0 | [V] |
| trigger from initStep1 | 0x8f6919 | 5 | - | `0x8f6919  call 0x186e6a0` | sub_8f6810 (initStep1) calls registration sub_186e6a0 | [V] |
| createTexture slot 26 -> TextureD3D12::create (live census) | 0xe81455b | 5 | - | `0xe81455b  call 0xE81BF30` | TextureD3D12::create called via createTexture slot 26; live `CALLER ret=0xE814560` = return address right after this call (l8b_texcreate_record.txt line 3); all 24 observed creations format 0x1C uncompressed, numMips=1, no atlas names | [V live] |
| TextureRecord +0xB1 = numMips (only store) | 0xe81c0d1 | 1 | [rdi]+0xB1 | `0xe81c0d1  mov [rdi+0xB1],dl` | createTexture writes numMips - skip at TextureRecord +0xB1 (BGFX_MAP.md line 1812); only numMips store located; live numMips=1 on every creation | [V] |
| BC1/BC3/BC7/DXT compression strings | 0xabsent-bc | - | - | - | BC1/BC3/BC7/DXT1-DXT5 strings unreferenced in exe (xref negative); no compression path statically | [V] |
| mip generation | 0xabsent-mip | - | - | - | mip generation not located: no GenMip/mips task or code (xref negative); only numMips +0xB1 store | [?] |
| atlas texture-creation stitcher | 0xabsent-stitch | - | - | - | not located: no code builds the TerrainAtlas/ItemAtlas texture description or calls createTexture/resizeTexture with atlas params | [?] |

## CLOSES?

CLOSES? NO — single blocking fact: the atlas TEXTURE-CREATION STITCHER is not located in this exe; static analysis is exhausted (orchestrator hint 2026-11-22); live census shows only uncompressed format-0x1C numMips=1 creations with no atlas names; BC1/BC3/BC7 strings are unreferenced; mip generation is not located; TerrainAtlasBlit task exists only as a blit consumer (0xf539a0b "TerrainAtlasBlit" refs at 0xbb431ee/0xbb418d0). Item-atlas texture creation and mips/compression are therefore external to this exe (likely CPU decode in another module / data-driven) — parked MIRROR_SKIP/external. Re-open if l8b_resizetex_slot31 (or a new capture at createTexture/TextureD3D12::create entry 0xe81bf30) returns a stitcher caller with mips>1 or atlas-name arguments.

## TOOL REQUESTS

livecap l8b_resizetex_slot31 | python tools/livecap/request.py result l8b_resizetex_slot31 | queued r34, still "no result yet"; queue full at 4 pending so no new capture can be added yet.
livecap stitcher@0xe81bf30 | python tools/livecap/request.py add <name> 0xe81bf30 --size 0x100 --max 6 --why "L8b: does any createTexture caller pass atlas params/mips>1?" | desired producer-entry capture to find the stitcher; cannot queue while queue is full.
No helper scripts written; none needed.
