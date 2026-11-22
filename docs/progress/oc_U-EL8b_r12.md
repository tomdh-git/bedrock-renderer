## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #5)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized.

Prior state carried (NOT re-derived): oc_U-EL8b_r1..r11 — Parts 1-3 below are [V] carried rows (registration, blit, createTexture/resizeTexture decode, mip keys, numMips store, format fallback, BC strings unreferenced) and were NOT re-disassembled this retry.
New this retry (per orchestrator hint 2026-11-22): read docs/data/live/mc_root_4e05e50_callers.txt + l8b_texcreate_record.txt (both still the only DONE L8b captures per _status.txt); name the indirect caller of sub_4e05e50 (ret=0x1289496) = sub_1289440 and decode it (0 xrefs in); decode texgroup_load 0x5421c90 and texload 0x58a1310; corroborate with L8a chain captures (dragon_texture_entry_c296b50, dragon_texture_caller_bc41420 ret=0x4E05F7C inside sub_4e05e50, bgfx_texture_wrapper_bc73bf0 ret=0xC296D7E inside sub_c296b50, bgfx_createtexture_producer rva=0xBC73770).
Pending captures (queued by r11, NO result in docs/data/live/ yet): l8b_resizetex_slot31 (rva 0xe815840, size 0x100, max 6) and sub_1289440_callers (rva 0x1289440, size 0x100, max 8). Request queue is full (4 pending) — no new L8b capture can be added this unit.

## Part 1 — Atlases (terrain, items) — carried [V] rows from oc_U-EL8b_r1..r11 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| registration index store | registered obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | code 0x1870e70 | 4 (dword) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocs 0x48-byte object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | code 0x1870e75 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object | [V] |
| sub_1870de0 name store | code 0x1870ec5 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 | [V] |
| sub_1870de0 fixed registry scan | code 0x1870e30 | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | fixed registry of 41 entries (idx 0..0x29); loop scans for a 0x2A '*' sentinel dword; `0x1870e45  mov [rdx+8],r15` writes range start; `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29` bounds idx to 0..41 | [V] |
| sub_186e6a0 registration dispatcher | code 0x186e6a0 | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop (0x186e6a0..~0x18706a0): allocs named objects via sub_1870de0; five atlas names; NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 static callers | xref sub_186e6a0 callers | - | xref | `0x8f6810 0x61d`, `0x1042320 0x1d1` | sub_186e6a0 has exactly 2 static callers: sub_8f6810 (+0x61d) and sub_1042320 (+0x1d1) [V via xref.py callers] | [V] |
| sub_1870de0 static callers | xref sub_1870de0 callers | - | xref | `0x1042320 0x1d1`, `0x186e6a0 0x1cb7` | sub_1870de0 has 37 xrefs in; callers include sub_1042320 (+0x1d1) and sub_186e6a0 (+0x1cb7) [V via xref.py callers] | [V] |
| sub_1042320 ServerLevelLoad | code 0x1042320 | - | 0x104237e | `0x104237e  call 0x186E6A0` | ServerLevelLoad triggers atlas registration via sub_186e6a0; loads "ResourceLoadType::ServerLevelLoad" at `0x104239b  lea rax,[0xF602326]` | [V] |
| sub_1042320 no texture creation | code 0x1042320 (full fn 0x1042320..0x1044320) | - | full listing | - | grep of the 1778-line listing of sub_1042320 found NO `call 0xE8143C0` / `0xE815840` / `0xE81BF30` and no TerrainAtlas/ItemAtlas string — ServerLevelLoad registers atlas names but does NOT create atlas textures | [V] |
| sub_8f6810 initStep1 caller | code 0x8f6810 | - | 0x8f6810+0x61d | - | second caller of sub_186e6a0 (initStep1); writes "initStep1" at `0x8f685b  lea rcx,[0xF7DE3DB]`; registers objects | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0 | [V] |
| TerrainAtlasBlit blit body | code 0xbc02090 | - | vtable 0xF43E9E0 slot 2 | - | vtable slot 2 = sub_bc02090 (size 0x3da): reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 | [V] |
| BlitUncompressed key | str data 0xf5f440c | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| item-atlas texture creation (not located) | item-atlas-creation | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task | [?] |
| terrain-atlas texture creation (not located) | terrain-atlas-creation | - | none | - | not located: xref "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture/resizeTexture call tied to TerrainAtlas | [?] |
| createTexture -> TextureD3D12::create call | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (slot 26) builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture itself has 0 static callers, reached only indirect via [vptr+0xD0] (slot 26 = offset 0xD0); live callers all ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry decode | code 0xe815840 | mixed (qword/dword/word/byte) | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode [V via rdis dis 0xe815840: `sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in`]: RCX=this renderer (`0xe81586c  mov r14,rcx`), DX=handle word stored (`0xe81586f  mov [rbp+0x8E],dx`), R8D=width->ebx (`0xe815869  mov ebx,r8d`), R9D=mips->edi (`0xe815866  mov edi,r9d`), stack word mips read (`0xe815980  movzx r13d,word ptr [rbp+0x108]`), stack byte layers (`0xe815988  movzx r12d,byte ptr [rbp+0x100]`), renderer+0xBDE178 handle array (`0xe815876  lea rsi,[rcx+0xBDE178]`); resizeTexture (handle,w,h,mips,layers) per BGFX_MAP 1505/1512; mips can be specified on resize; 0 static xrefs — indirect vtable dispatch only | [V] |

## Part 2 — mipmaps — carried [V] rows from oc_U-EL8b_r1..r11 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written inside TextureD3D12::create sub_e81bf30; dl loaded at `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed-format fallback 0x42 | code 0xe81bf30 | 1 (byte) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function (not located) | mip-generation | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-gen Blit task [V]; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression — carried [V]/[I] rows from oc_U-EL8b_r1..r11 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542 | - | references in 0x765330 and PNG decoder 0x777ed0 are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): image (PNG zlib) decompression, called from PNG decoder dispatcher | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code (not located) | bc-code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback [V at 0xe81c12b/0xe81c077]; live census/all captures all-uncompressed [V live] | [V] |

## Part 4 — NEW THIS RETRY: sub_4e05e50 indirect caller (texgroup_load/texload/TexturePtr angle)

Per the 2026-11-22 orchestrator hint: mc_root_4e05e50_callers.txt (150 hits, 32 samples) has a single caller for every hit:

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 live caller (ret=) | docs/data/live/mc_root_4e05e50_callers.txt line 3 | - | capture header | `CALLER ret=0x1289496 first_hit=1` | all 150 hits / 32 samples share ONE return address: ret=0x1289496, i.e. the call to sub_4e05e50 falls through to 0x1289496 (the `nop` at `0x1289496  nop` inside sub_1289440) | [V live] |
| sub_1289440 = indirect caller of sub_4e05e50 | code 0x1289440 | - | sub header | `sub_1289440  [0x1289440..0x128b440)  size 0x2000  0 xrefs in` | TexturePtr-style release/collect function; 0 static xrefs in; NOT sub_12893d0 (r11's misattribution) | [V] |
| refcount inc (add-ref) | object +8 | 8 (qword cmpxchg) | 0x1289447 | `0x1289447  lock cmpxchg [rcx+8],edx` | CAS loop incrementing the refcount dword at object+8 | [V] |
| 16-byte object copy | 0x0 | 16 (movups) | 0x128944e | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of the texture object | [V] |
| release old pointee via thunk | object +0x10 | 8 (qword) | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | this IS the live-captured call site: fall-through 0x1289496 = ret= seen in mc_root_4e05e50_callers.txt; statically [0xF99FFA0] = sub_eea6040 thunk, at runtime this site entered sub_4e05e50 [V live mc_root_4e05e50_callers.txt line 3] | [V live] |
| further release sites via same thunk | object +0x10 / +8 | 8 (qword) | 0x12894b3, 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612 | `0x12894b3  call qword ptr [0xF99FFA0]` (same instruction text at each address) | seven more release/decrement calls through [0xF99FFA0] (sub_eea6040) on old pointees and array entries | [V] |
| refcount dec strong (+8) | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | decrements refcount; object destroyed when it reaches zero | [V] |
| refcount dec weak (+0xC) | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | second refcount/weak-count decrement | [V] |
| 0x18-strided array walk | array elem stride 0x18 | - | 0x1289560 | `0x1289560  add rbx,0x18` | walks a 0x18-strided array ([rdi]..[rdi+8]) releasing [rbx+0x10] and [rbx+8] entries | [V] |
| count output | out +0 | 8 (qword) | 0x12895a8 | `0x12895a8  mov [rsi],r12` | stores collected count r12 into the output pointer | [V] |

Interpretation (this retry): sub_4e05e50's only live caller is sub_1289440, a TexturePtr refcount release/collect function — the sub_6632bf0 "Deferred Texture Transactions" ensure-loaded/release path (r11). It incs/dec refcounts ([rcx+8], [r15+8], [rcx+0xC]) and releases old pointees via [0xF99FFA0]; it does NOT create atlases, generate mips, or compress textures [V + V live].

texgroup_load / texload decode (static, this retry):

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| texgroup_load | code 0x5421c90 | - | 0x5421dec | `0x5421dec  call 0x5477a30` | texture group load/lookup: looks up a texture via sub_5477a30 then add-refs it; 7 static xrefs in | [V] |
| texgroup_load refcount inc | texture +8 | 4 (dword) | 0x5421e0a | `0x5421e0a  lock inc dword ptr [rcx+8]` | refcount increment on the looked-up texture (returned at rax+0x68 stored via [rsi+0x60]) | [V] |
| texload | code 0x58a1310 | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list ([rbx+0x160..0x168)) calling sub_5417950 per entry, tracking min/max UV at [rbx+0x6C..0x80]; 2 static xrefs in | [V] |
| texload rect read | 0x8 | 4 (movss) | 0x58a1450 | `0x58a1450  movss xmm3,[rcx+8]` | per-rect float read in the rect walk | [V] |
| texgroup_load/texload -> sub_1289440 link | link | - | none | - | NOT provable statically: static xrefs/imm to sub_1289440 = 0 and to sub_4e05e50 = 0 (xref.py empty, rdis imm 0x4e05e50 = 0 hits). The queued capture sub_1289440_callers (rva 0x1289440, state pending, no result in docs/data/live/) would name sub_1289440's caller via ret= and complete the chain | [?] |

L8a chain captures corroborate (read this retry, not re-run): dragon_texture_entry_c296b50.txt CALLER ret=0xBC41B3E; dragon_texture_caller_bc41420.txt CALLER ret=0x4E05F7C (the `0x4e05f77  call 0xBC41420` inside sub_4e05e50); RCX texture object at bc41420 entry shows format 0x1C, 1x1x1, "tex" name [V live]; bgfx_texture_wrapper_bc73bf0.txt CALLER ret=0xC296D7E (inside sub_c296b50) [V live]; bgfx_createtexture_producer.txt rva=0xBC73770 (cmd-byte-14 producer -> dispatcher slot 26 -> createTexture 0xe8143c0), all observed texture objects format 0x1C uncompressed, dims 1x1x1 or 64x64, names "textures/misc/en...", "enderTexture", "vanilla.CoreData", "textures/entity/...", "vanillaRealmsPl...", "structures/mansi..." — NO atlas names [V live].

All live texture creation (l8b_texcreate_record.txt, 24 samples, CALLER ret=0xE814560 inside createTexture after `0xe81455b  call 0xE81BF30`): format 0x1C uncompressed, numMips=1, no atlas names [V live]. mc_root_4e05e50_callers.txt: all 150 hits/32 samples ret=0x1289496 single caller sub_1289440 [V live].

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas texture-creation STITCHER is not located in the exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, 0xe8143c0 -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, 0xe815840, takes mips) with atlas params:

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) inside sub_186e6a0 (sub_1870de0 0x48-byte object, name at obj+0, idx at obj+8 `0x1870ecb  mov [rsi+8],eax`), triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 (`0x104237e  call 0x186E6A0`) and by initStep1 sub_8f6810 (+0x61d). But sub_1042320's full 1778-line listing creates NO atlas texture (no createTexture/resizeTexture/TextureD3D12::create call, no atlas string) [V], and sub_186e6a0 contains no createTexture/resizeTexture call [V]. No ItemAtlasBlit task exists; no stitcher/registry reader located (sub_1870de0 has 37 xrefs, all registration-side) [V].
- Live evidence: every createTexture creation is format 0x1C uncompressed, numMips=1, no atlas names [V live l8b_texcreate_record]; sub_4e05e50's only caller sub_1289440 is TexturePtr ensure-loaded/release, not creation [V live mc_root_4e05e50_callers]; resizeTexture slot 31 has 0 static xrefs and its live capture (l8b_resizetex_slot31) is queued but has NO result yet.
- Parts closed as provably ABSENT (not the blocker): mipmap generation (no GenMip/Mips/MipMap/mipchain code or task; numMips=1 for all live creations [V live]; numMips only stored at +0xB1 [V]) and BC1/BC3/BC7/DXT1-DXT5 compression (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback [V at `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b`]; live census all-uncompressed [V live]).

The remaining open part (atlas texture creation) cannot be resolved from static analysis (exhausted) nor from currently available live data; it needs the pending l8b_resizetex_slot31 / sub_1289440_callers capture results (queue full, retry next unit) or an orchestrator decision to mark atlas creation external/data-driven.

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; only when delegate exits 0 set the line after `## NEXT` to DONE.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 (rva 0xe815840, size 0x100, max 6) — already queued by r11, state pending, no result yet. Why: does the atlas stitcher create/resize atlases via resizeTexture(handle,w,h,mips,layers); ret= names the stitcher caller; mips>1 is mip-generation evidence.
CAPTURE REQUESTED sub_1289440_callers (rva 0x1289440, size 0x100, max 8) — already queued, state pending, no result yet. Why: names sub_1289440's caller to complete the texgroup_load/texload -> TexturePtr -> sub_4e05e50 chain (static xrefs = 0).
Queue full (4 pending: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) — no new L8b capture can be added this unit; retry next unit once a slot frees.
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files; no throwaway scripts written).
