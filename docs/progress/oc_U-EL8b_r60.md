## NEXT
DONE - awaiting l8b_resizetex_slot31 capture result; CLOSES? NO (atlas texture-creation stitcher not located; needs live capture or external/parked decision)

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #20)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [V live] read-only live capture (docs/data/live/), [I] inferred (say from what), [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste the input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized; no catch-all rows; no ellipsis abbreviations.

## 0. Input reviewed this session (NOT re-derived)

- docs/progress/oc_U-EL8b_r54..r59 carried: atlas registration [V], blit consumption [V], createTexture/resizeTexture decode [V], mip keys [V], numMips store [V], format fallback [V], BC strings unreferenced [V], sub_4e05e50/texgroup_load/texload/TexturePtr decode [V + V live], live capture census [V live]. Every verbatim `0xRVA  instr` line below was re-confirmed against the exe with `rdis.exe dis` this session; all match.
- docs/data/live/mc_root_4e05e50_callers.txt [V live] re-read in full: line 3 `CALLER ret=0x1289496 first_hit=1`; all 150 hits/32 samples → sub_12893d0 (TexturePtr release/ensure-loaded, NOT a creator).
- docs/data/live/l8b_texcreate_record.txt [V live] re-read in full: line 3 `CALLER ret=0xE814560 first_hit=1`; 24 samples, format 0x1C, numMips=1, ZERO atlas names, names like "Texture: 2815"/"Texture: 2799" (R8 strings).
- 2026-11-22 orchestrator hint: static analysis alone is exhausted for this item; only live data can still add.
- Capture queue at 4-pending limit = er5_clone_4c8a5b0, l8b_resizetex_slot31 (rva 0xe815840 = resizeTexture slot 31 entry, NO result yet), sub_1289440_callers, oc_u_er6_light_desc. `request.py add` refused ('4 requests already pending').

## NEW ANGLE THIS SESSION — consumers of the registered atlas objects (r10 hint, completed)

The registered atlas objects (0x48-byte, name at +0, idx at +8) are made by sub_1870de0 inside sub_186e6a0 (idx 6 = TerrainAtlas, idx 7 = ItemAtlas), triggered by ServerLevelLoad sub_1042320 and initStep1 sub_8f6810. New lead traced: callers of sub_18718d0 (registered-object-by-index lookup, [a0+0x30] list, compares [entry+0x20] vs index r8d, byte flag [entry+0x19]). The texture-region caller sub_e84070 [0xe84070..0xe84da8) size 0xd38 builds a 0x88 object (`0xe846ed mov edx,0x88`, alloc via [F99FFA0]), copies name strings from a0+0x328/a0+0x338, then `0xe84a58 mov rcx,[rbp+0x48]; 0xe84a5c mov r8d,9; 0xe84a62 call 0x18718D0` — looks up REGISTERED OBJECT INDEX 9 (NOT atlas idx 6 Terrain / 7 Item). Then `0xe84ab1 call 0xE87AC0`. sub_e87ac0 [0xe87ac0..0xe89ac0) is a pure destructor/refcount-release (NOT a stitcher). sub_e84070 does NOT call createTexture/resizeTexture. Caller chain: sub_e82e00 (0 xrefs in, size 0x2000). sub_e85290/sub_e85434/sub_e86630 are string-setup/small-object builders, not createTexture. Conclusion: this consumer chain does NOT build atlas texture descriptions or call createTexture/resizeTexture with atlas params. Static angle exhausted.

## 1. Table of proven facts (offset | size | read/store addr | verbatim `0xRVA  instr` | meaning | tag)

| name | rva or offset | size | read/store addr | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| Atlas registration entry | sub_186e6a0 `0x186e6a0` | - | `0x186e6a0` | `0x186e6a0  push rbp` | entry of atlas-registration function (TerrainAtlas idx6, ItemAtlas idx7) | [V] |
| TerrainAtlas name string | `0x186f731` | - | `0x186f731` | `0x186f731  lea rax,[0xF55CDD3]` | 'TerrainAtlas' name, idx 6 | [V] |
| ItemAtlas name string | `0x186f7fc` | - | `0x186f7fc` | `0x186f7fc  lea rax,[0xF55CDE0]` | 'ItemAtlas' name, idx 7 | [V] |
| Registry sentinel scan | `0x1870e30` | 4 | `0x1870e30` | `0x1870e30  cmp dword ptr [rcx],0x2A` | registry dword array scanned for 0x2A '*' free-slot sentinel | [V] |
| Registered object size | `0x1870e70` | 4 (imm) | `0x1870e70` | `0x1870e70  mov edx,0x48` | alloc size 0x48 for each registered atlas object | [V] |
| Index store | `0x1870ecb` | 4 | `0x1870ecb` | `0x1870ecb  mov [rsi+8],eax` | registered-object idx stored at +8 | [V] |
| createTexture entry slot 26 | `0xe81455b` | - | `0xe81455b` | `0xe81455b  call 0xE81BF30` | TextureD3D12::create entry, createTexture slot 26 | [V] |
| resizeTexture entry slot 31 | `0xe815840` | - | `0xe815840` | `0xe815840  push rbp` | resizeTexture slot 31 entry (takes mips), 0 static xrefs in | [V] |
| numMips store | `0xe81c0d1` | 1 | `0xe81c0d1` | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored at desc+0xB1 | [V] |
| format store | `0xe81c077` | 1 | `0xe81c077` | `0xe81c077  mov [rdi+0xB0],r13b` | format byte stored at desc+0xB0 via u16 table | [V] |
| format fallback | `0xe81c12b` | 1 | `0xe81c12b` | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | format fallback check at desc+0xB0 | [V] |
| BC1 string | `0xf84ad1c` | - | `-` | - | BC1 string present in .rdata | [V] |
| BC3 string | `0xf84aaf8` | - | `-` | - | BC3 string present in .rdata | [V] |
| BC7 string | `0xf84a930` | - | `-` | - | BC7 string present in .rdata | [V] |
| BC string xrefs | all BC1/BC3/BC7/DXT1-5 strings | - | `-` | - | xref.py refs=[] for every BC/DXT string — no compression path references them | [V] |
| Mip gen xrefs | GenMip/Mips/MipMap/mipchain strings | - | `-` | - | xref.py refs=[] — no mip-generation code located | [V] |
| sub_e84070 alloc size | `0xe846ed` | 4 (imm) | `0xe846ed` | `0xe846ed  mov edx,0x88` | sub_e84070 builds 0x88-byte object (texture-region consumer) | [V] |
| sub_e84070 registered-obj lookup | `0xe84a62` | - | `0xe84a62` | `0xe84a62  call 0x18718D0` | sub_e84070 looks up registered object index 9 (NOT atlas 6/7), then calls destructor sub_e87ac0 | [V] |

## 2. Live-capture evidence [V live]

- l8b_texcreate_record (rva 0xe81bf30 TextureD3D12::create, 24 samples): format 0x1C (DXGI 28 = R8G8B8A8_UNORM uncompressed), numMips=1, ZERO atlas names, names like "Texture: 2815"/"Texture: 2799" (R8 strings). docs/data/live/l8b_texcreate_record.txt line 3.
- mc_root_4e05e50_callers (rva 0x4e05e50, 150 hits/32 samples): sole caller sub_12893d0 (TexturePtr release/ensure-loaded, NOT a creator), ret=0x1289496 (`0x1289496 nop` after `0x1289490 call qword ptr [0xF99FFA0]`). docs/data/live/mc_root_4e05e50_callers.txt line 3.
- texture_table.txt (full live texture table, ctx=*(base+0x12BB4910); record=ctx+0xBDE178+h*0xB8; width u32 @+0x18, height u32 @+0x20, DXGI_FORMAT u32 @+0x28): every row fmt 28 (uncompressed), no BC formats, no names, no atlas entries identifiable. docs/data/live/texture_table.txt.
- Handle correlation: l8b_texcreate_record names 'Texture: 2815'/'Texture: 2799' → texture_table.txt handle 2815 = 128x64 fmt28 (line 1430), handle 2799 = 128x128 fmt28 (line 1414). Plausible atlas sizes but UNNAMED in capture — not proof they are atlases. [I]

## 3. Capture queue status [V live]

| name | rva | size | max | state | why |
|---|---|---|---|---|---|
| l8b_resizetex_slot31 | 0xe815840 | 0x100 | 6 | pending, NO result yet | L8b: does the atlas stitcher create/resize atlases via resizeTexture(handle,w,h,mips,layers); ret= names the stitcher caller; mips>1 is mip-generation evidence |
| sub_1289440_callers | 0x1289440 | 0x100 | 8 | pending | U-EL7e: who calls sub_1289440 at runtime (tail-calls sub_4e05e50 via rax/[0xF99FFA0] trampoline with ret=0x1289496) |
| er5_clone_4c8a5b0 | 0x4c8a5b0 | 0x100 | 6 | pending | R5: clone entry |
| oc_u_er6_light_desc | 0x6640d80 | 0x100 | 6 | pending | R6: light-visitor entry producer capture |
| Limit | 4 pending | - | - | FULL | `request.py add` refused: '4 requests already pending' |

`python tools/livecap/request.py result l8b_resizetex_slot31` -> 'no result yet (orchestrator has not run it)'.
`python tools/livecap/request.py result sub_1289440_callers` -> 'no result yet (orchestrator has not run it)'.

## 4. What I tried that failed (this session)

- Traced callers of sub_18718d0 (registered-object-by-index lookup) — the r10 hint 'trace what consumes the registered atlas objects after sub_1042320'. Found sub_e84070 in the 0xe8xxxx texture-create region: builds a 0x88 object, copies name strings, looks up registered object INDEX 9 (not atlas 6/7), calls destructor sub_e87ac0, does NOT call createTexture/resizeTexture. sub_e87ac0 is a pure destructor. sub_e85290/sub_e85434/sub_e86630 are string-setup builders. This consumer chain does not build atlas texture descriptions or call createTexture/resizeTexture with atlas params. [V via rdis]
- xref.py str for BC1/BC3/BC7/DXT1-5, GenMip/Mips — all refs=[] (already proven in r54-r59, not redone).
- Requested new live capture — refused (queue at 4-pending limit).

## 5. CLOSES?

CLOSES? NO — single blocking fact: the atlas TEXTURE-CREATION STITCHER is not located. No code in the exe builds a TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, 0xe8143c0) or resizeTexture (slot 31, 0xe815840, takes mips) with atlas params. Mip generation, BC1/BC3/BC7 compression, and item-atlas texture creation are not in the exe statically (likely CPU decode in another module / data-driven). All live creations are format 0x1C uncompressed numMips=1 with zero atlas names. Needs the l8b_resizetex_slot31 live capture result (ret= names the stitcher caller) or a decision to mark as external/parked. Currently parked pending capture.

## TOOL REQUESTS

livecap l8b_resizetex_slot31 | entry 0xe815840 (resizeTexture slot 31) | ret= would name the atlas stitcher caller; queue full (4 pending), result not yet available | waiting on orchestrator to run the batch
