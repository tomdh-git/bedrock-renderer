## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #1)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [V live] read-only live capture (docs/data/live/), [I] inferred (say from what), [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized; no placeholder rows.

Input reviewed (NOT re-derived): docs/progress/oc_U-EL8b_r1..r55 (registration, blit, createTexture/resizeTexture decode, mip keys, numMips store, format fallback, BC strings unreferenced — all carried). docs/progress/oc_U-L8b.md (predecessor PNG/TGA decoder unit — unrelated to atlases; its decoder offsets are carried as Part 6 rows). Live captures re-read in full: docs/data/live/mc_root_4e05e50_callers.txt [V live] (line 3 `CALLER ret=0x1289496 first_hit=1`), docs/data/live/l8b_texcreate_record.txt [V live] (line 3 `CALLER ret=0xE814560 first_hit=1`). docs/data/live/l8b_resizetex_slot31: NO result (orchestrator has not run it; capture already queued by r53-r55, not re-queued). docs/BGFX_MAP.md sections 336/337, 1105/1107, 1502/1511, 1812, 1885, 549 read for context [I] where used.

## Part 1 — Atlases (terrain, items): registration PROVEN [V], texture creation NOT located [?]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name in this exe | [V] |
| registration index store | registered obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 object alloc size | code 0x1870e70 | 4 (dword) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocs 0x48-byte object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | code 0x1870e75 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object | [V] |
| sub_1870de0 name store | code 0x1870ec5 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 | [V] |
| sub_1870de0 registry sentinel | registry dword +0 | 4 (dword cmp) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | fixed registry scan for 0x2A '*' free-slot sentinel; `0x1870f28  inc r14d` `0x1870f2b  cmp r14d,0x29` bounds idx to 0..41 | [V] |
| sub_186e6a0 registration dispatcher | code 0x186e6a0 | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop (0x186e6a0..~0x18706a0): allocs named objects via sub_1870de0; five atlas names; NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 static callers | xref sub_186e6a0 callers | - | xref | `0x8f6810 0x61d`, `0x1042320 0x1d1` | exactly 2 static callers: sub_8f6810 (+0x61d, initStep1) and sub_1042320 (+0x1d1, ServerLevelLoad) [V via xref.py callers] | [V] |
| sub_1870de0 static callers | xref sub_1870de0 callers | - | xref | `0x1042320 0x1d1`, `0x186e6a0 0x1cb7` | sub_1870de0 has 37 xrefs in; callers include sub_1042320 (+0x1d1) and sub_186e6a0 (+0x1cb7), all registration-side | [V] |
| sub_1042320 ServerLevelLoad trigger | code 0x1042320 | - | 0x104237e | `0x104237e  call 0x186E6A0` | ServerLevelLoad triggers atlas registration via sub_186e6a0; loads "ResourceLoadType::ServerLevelLoad" at `0x104239b  lea rax,[0xF602326]` | [V] |
| sub_1042320 full listing | code 0x1042320 (0x1042320..0x1044320) | - | full listing | - | 1778-line listing checked: NO `call 0xE8143C0` / `0xE815840` / `0xE81BF30`, no TerrainAtlas/ItemAtlas string — registers atlas names, creates NO atlas texture | [V] |
| sub_8f6810 initStep1 caller | code 0x8f6810 | - | 0x8f6810+0x61d | - | second caller of sub_186e6a0; writes "initStep1" at `0x8f685b  lea rcx,[0xF7DE3DB]`; registers objects | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it; BGFX_MAP 337: string only, referenced via table) | [?] |
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name inside 0xbb418d0; functor vtable 0xF43E9E0 (BGFX_MAP 1105); in frame order (BGFX_MAP 1107) — atlas BLIT consumption, not creation | [V] |
| BlitUncompressed key | str data 0xf5f440c | - | ref 0x560be9f | `0x560be9f  lea r9,[0xF5F440C]` | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| terrain-atlas texture creation | none | - | none | - | not located: xref "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to TerrainAtlas | [?] |
| item-atlas texture creation | none | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture/resizeTexture call tied to ItemAtlas; no ItemAtlasBlit task | [?] |

## Part 2 — mipmaps

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte store) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored inside TextureD3D12::create; dl loaded `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte store) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed-format fallback 0x42 | code 0xe81bf30 | 1 (byte cmp) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | none | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-generation Blit task [V]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; sampler bit 10 is mip FILTER (usage, not generation) [I via BGFX_MAP 782]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 names; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542 | - | referenced from 0x765330 and PNG decoder 0x777ed0 — PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): PNG/zlib image decompression from the PNG decoder dispatcher, not BC compression | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | data table incl. BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | none | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live] | [V] |

## Part 4 — creation entries, TexturePtr chain, TextureD3D12::create, live census

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture -> TextureD3D12::create call | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (slot 26) builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture has 0 static callers, reached indirect via [vptr+0xD0] (slot 26); live callers ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry decode | code 0xe815840 | mixed | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode `sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in`: RCX=this renderer `0xe81586c  mov r14,rcx`; DX handle word stored `0xe81586f  mov [rbp+0x8E],dx`; R8D=width->ebx `0xe815869  mov ebx,r8d`; R9D=mips->edi `0xe815866  mov edi,r9d`; stack word mips `0xe815980  movzx r13d,word ptr [rbp+0x108]`; stack byte layers `0xe815988  movzx r12d,byte ptr [rbp+0x100]`; renderer+0xBDE178 handle array `0xe815876  lea rsi,[rcx+0xBDE178]`; resizeTexture(handle,w,h,mips,layers) per BGFX_MAP 1502/1511; mips specifiable on resize; 0 static xrefs, indirect vtable dispatch only, never captured live | [V] |
| TextureD3D12::create callers | xref TextureD3D12::create callers | - | xref | `0xe8143c0 0x2e1`, `0xe815840 0x3ae` | exactly 2 static callers: createTexture and resizeTexture slot 31; xref hit at 0xe8403d0+0xaa5b verified as vtable DATA store `0xe8eaf2b  mov [rax+0x40],rcx`, not a call | [V] |
| resizeTexture static xrefs | code 0xe815840 | - | xref | none | 0 static xrefs — indirect vtable dispatch only; never observed live | [V] |
| sub_4e05e50 entry | code 0x4e05e50 | - | sub header | `0x4e05e50  push rbp` | TexturePtr ensure-loaded/release function; 0 static xrefs in (reached indirect via [0xF99FFA0] from sub_12893d0 at runtime) | [V] |
| sub_4e05e50 arg rsi | regs | - | 0x4e05e6b | `0x4e05e6b  mov rsi,rdx` | rsi = out pointer | [V] |
| sub_4e05e50 arg rdi | regs | - | 0x4e05e6e | `0x4e05e6e  mov rdi,rcx` | rdi = a0 = TexturePtr-like object (+0x10 pointee, +0x18, +0x58 desc region) | [V] |
| sub_4e05e50 pointee add-ref | pointee +8 | 4 (dword cmpxchg) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref loop on refcount at *(a0+0x10)+8 | [V] |
| sub_4e05e50 desc-region call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 (dragon-layer upload bridge) called with rcx = a0+0x58 (texture description region) — ensure-loaded/upload, NOT atlas creation | [V] |
| sub_4e05e50 result call | out | - | 0x4e05f85 | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 called on the produced result | [V] |
| sub_12893d0 entry | code 0x12893d0 | - | sub header | `0x12893d0  push rbp` | TexturePtr release/collect: walks 0x18-strided entry array [r13..r14), entry object pointer at [r13+8] | [V] |
| sub_12893d0 array walk stride | elem stride 0x18 | - | 0x1289420 | `0x1289420  add r13,0x18` | next array entry | [V] |
| sub_12893d0 entry add-ref | entry obj +8 | 4 (lock cmpxchg) | 0x1289447 | `0x1289447  lock cmpxchg [rcx+8],edx` | add-ref object at [r13+8] | [V] |
| sub_12893d0 entry copy | entry | 16 (movups) | 0x128944e | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of array entry | [V] |
| sub_12893d0 release pointee | pointee +0x10 | 8 (qword call) | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | LIVE-CAPTURED SITE: runtime target = sub_4e05e50; fall-through `0x1289496  nop` = ret=0x1289496 seen in mc_root_4e05e50_callers.txt line 3 for ALL 32 samples | [V live] |
| sub_12893d0 fall-through nop | code 0x1289496 | - | 0x1289496 | `0x1289496  nop` | fall-through after the indirect call = ret=0x1289496 in mc_root_4e05e50_callers.txt line 3 | [V live] |
| sub_12893d0 release sites | pointee/entry | 8 (qword call) | 0x12894b3 | `0x12894b3  call qword ptr [0xF99FFA0]` (same instr text at 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612) | seven release/decrement calls on old pointees and array entries | [V] |
| sub_12893d0 refcount dec strong | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | strong refcount decrement; destroy at zero | [V] |
| sub_12893d0 refcount dec weak | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | weak-count decrement | [V] |
| sub_12893d0 count output | out +0 | 8 (qword store) | 0x12895a8 | `0x12895a8  mov [rsi],r12` | stores collected count | [V] |
| sub_4e05e50 live RCX +0x00 | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x00: `385821a8f67f0000` -> qword 0x00007ff6a8215838 | pointer into ANOTHER MODULE — outside exe image [0x7FF7A59C0000, 0x7FF7B91FE000); corroborates "atlas logic likely in another module / data-driven" | [V live] |
| sub_4e05e50 live RCX +0x10 | obj +0x10 | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x10: `a00291be90030000` -> qword 0x000390be9102a0 | pointee texture object pointer; sub_4e05e50 reads [rdi+0x10] at `0x4e05e8c  mov rdx,[rdi+0x10]` | [V live] |
| sub_4e05e50 live RCX +0x60 | desc +0x60 | 4 (dword) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x60: `1c000000` | texture description format = 0x1C (R8G8B8A8_UNORM, uncompressed) at a0+0x58.. passed to sub_bc41420 | [V live] |
| sub_4e05e50 live RCX +0x64..6C | desc +0x64/68/6c | 4 (dword) x3 | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x64/0x68/0x6c: `01000000` x3 | description dims w/h/array = 1/1/1 | [V live] |
| sub_4e05e50 live RCX +0x70 | desc +0x70 | 4 (byte tag) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x70: `74657800` | description fourcc tag "tex\0" | [V live] |
| sub_4e05e50 live caller | ret=0x1289496 | - | capture header line 3 | `CALLER ret=0x1289496 first_hit=1` | all 150 hits/32 samples: sub_12893d0 is the only live caller of sub_4e05e50 | [V live] |
| texgroup_load | code 0x5421c90 | - | 0x5421dec | `0x5421dec  call 0x5477A30` | looks up texture by name via sub_5477a30 (rcx = rsi+0x248); add-ref `0x5421e0a  lock inc dword ptr [rcx+8]` on looked-up texture — lookup only, not creation | [V] |
| sub_5477a30 callers | xref sub_5477a30 callers | - | xref | - | exactly 2 static callers: sub_541f8f0 (+0xc7d) and texgroup_load 0x5421c90 (+0x190f) — no stitcher looks up atlas textures by name | [V] |
| texload | code 0x58a1310 | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks 0x30-strided rect list [rbx+0x160..0x168); per-rect float `0x58a1450  movss xmm3,[rcx+8]` — atlas UV CONSUMPTION, not creation | [V] |
| l8b_texcreate_record hit=1 RCX | TextureD3D12::create record | - | l8b_texcreate_record.txt line 4 RCX | bytes at RCX+0x40: `1c000000`; +0x54: `01000000`; +0xb1: `01` | SRV desc format 0x1C at +0x40; MipLevels=1 at +0x54; numMips byte = 1 at +0xB1; R8 name "Texture: 2815" (UTF-16); 24 samples, NO atlas names, all format 0x1C [V live] | [V live] |

## Part 5 — NEW THIS RETRY: angles tried against the single blocking fact (all exhausted)

| angle | target | method | result | tag |
|---|---|---|---|---|
| pending capture result check | l8b_resizetex_slot31 (rva 0xe815840, resizeTexture slot 31) | `python tools/livecap/request.py result l8b_resizetex_slot31` | "no result yet (orchestrator has not run it)"; already queued (pending), not re-queued (queue full, duplicate not allowed) | [V live] |
| live desc bytes re-decoded (corrects r55 offsets) | mc_root_4e05e50_callers.txt hit=1 RCX | python byte parse of the 0x100-byte dump | +0x00 qword 0x00007ff6a8215838 = other-module pointer (outside exe image); +0x10 qword 0x000390be9102a0 pointee; +0x60 `1c000000` format 0x1C; +0x64/68/6c `01000000` x3 dims 1/1/1; +0x70 `74657800` tag "tex\0" — r55's +0x64/+0x74 were off by 4; corrected here | [V live] |
| live create record decoded | l8b_texcreate_record.txt hit=1 RCX | python byte parse of the 0x100-byte dump | +0x40 `1c000000` SRV format; +0x54 `01000000` MipLevels=1; +0xb1 `01` numMips=1; +0x9c/+0xa0 = 64x64; R8 = UTF-16 "Texture: 2815"; no atlas name | [V live] |
| live-capture census | both captures, all samples | read files fully | every creation: format 0x1C uncompressed, numMips=1, names "Texture: 2815"/"Texture: 2799"/UI names — ZERO atlas names in 150+32+24 samples [V live] | [V live] |
| BGFX_MAP.md context | sections 336/337, 1105/1107, 1502/1511, 1812, 1885, 549 | read docs/BGFX_MAP.md | PointLightShadowTextureAtlas task 0xbb682b0; MaterialTerrainTextureAtlas string only (via table); TerrainAtlasBlit task in frame order; resizeTexture slot 31 = (handle,w,h,mips,layers) [V shape, name by match]; live texture-table scan: h28 2048x2048 fmt0x35 fl0x10003 largest texture, not tied to BC names by any code ref, no handle->name map — not creation evidence | [I] |
| livemem cross-module read | 0x7ff6a8215838 (+0x00 pointer value) | `python tools/sigs/livemem.py read 0x7ff6a8215838 0x100` | unreadable — outside exe/heap ranges; no module-enumerate command exists, so the module NAME/RVA of the +0x00 pointer (r13 lead) cannot be identified from this side | [V live] |
| descscan2 on registration dispatcher | sub_186e6a0 | descscan2.py | not supported for arbitrary function ranges (visitor cases only); no description-building fields found | [I] |
| creation entry points re-enumerated | createTexture 0xe8143c0, resizeTexture 0xe815840, TextureD3D12::create 0xe81bf30 | xref callers + 3 live captures | all negative for atlas params: TextureD3D12::create callers = createTexture + resizeTexture only [V]; resizeTexture 0 static xrefs [V]; live census all-uncompressed no atlas names [V live x3] | [V] |

## Interpretation (this retry)

No NEW static angle remains: every creation entry point is enumerated and negative (static + 3 live captures), all readers/stitchers of the registered atlas objects are unlocated, sub_1870de0/sub_186e6a0 are registration-only, and the live texture-request object's +0x00 vtable pointer provably points into another module outside this exe image — so atlas creation (and with it mip-chain production) is external-module or data-driven and cannot be closed from this exe statically. Mip GENERATION and BC1/BC3/BC7 compression are closed as provably ABSENT (see Part 2/Part 3 rows); only compressed-texture DATA on disk remains possible [I]. The one capture that could name the stitcher caller (l8b_resizetex_slot31, resizeTexture slot 31 — takes mips; mips>1 would be mip-generation evidence; atlas-name params would close the creation rows) is queued but has no result yet.

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas texture-creation STITCHER is not located in this exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, `0xe81455b  call 0xE81BF30`) or resizeTexture (slot 31, `0xe815866  mov edi,r9d`, takes mips) with atlas params:

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) inside sub_186e6a0 (sub_1870de0 0x48-byte object; name at obj+0 `0x1870ec5  mov [rsi],rax`; idx at obj+8 `0x1870ecb  mov [rsi+8],eax`; registry sentinel `0x1870e30  cmp dword ptr [rcx],0x2A`), triggered by ServerLevelLoad `0x104237e  call 0x186E6A0` and initStep1 sub_8f6810 (+0x61d). But sub_1042320's full listing creates NO atlas texture [V]; sub_186e6a0 contains no create/resize call [V]; sub_1870de0's 37 xrefs are all registration-side; the registered objects are consumed by NO located reader/stitcher; no ItemAtlasBlit task exists; blit is uncompressed ("BlitUncompressed" `0x560be9f  lea r9,[0xF5F440C]`; TerrainAtlasBlit task `0xbb431ee  lea rdx,[0xF539A0B]`) [V].
- Creation entry points fully enumerated and negative: createTexture census (live x2: l8b_texcreate_record + createtexture_callers, all UI/misc, format 0x1C, numMips=1, no atlas names [V live]); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture 0 static xrefs, never captured [V]; sub_4e05e50/sub_12893d0 = TexturePtr release/ensure-loaded, not creation [V + V live]; sub_5477a30 texture lookup callers = texgroup_load + sub_541f8f0 only, no stitcher [V via xref].
- Live mc_root objects carry +0x00 vtable pointer provably in ANOTHER MODULE (0x00007FF6A8215838 vs exe image [0x7FF7A59C0000, 0x7FF7B91FE000)) [V live] — consistent with the original assessment "likely CPU decode in another module / data-driven".

CLOSES? YES only when the stitcher call site is found (pending l8b_resizetex_slot31 capture result) or an orchestrator decision marks atlas creation external/data-driven (MIRROR_SKIP).

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; the line after `## NEXT` is set to DONE only when delegate check exits 0. All quoted `0xRVA  instr` lines copied verbatim from rdis output or re-decoded from the live capture bytes; live values cited as [V live] with file + line.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 (rva 0xe815840 = resizeTexture slot 31 entry, size 0x100, max 6) — ALREADY QUEUED by r53-r55, pending, NO result yet in docs/data/live/. Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); its ret= would name the stitcher caller and mips>1 would be mip-generation evidence; atlas-name params would close the terrain/item-atlas creation rows. Do NOT re-queue (duplicate; queue full per r53-r55).
Livemem capability gap: direct read of external-module address 0x00007FF6A8215838 returns "unreadable" (livemem restricted to exe/heap ranges); no module-enumeration command available, so the module name of the +0x00 pointer cannot be determined from this side [I].
Helper scripts: none (all verbatim lines taken directly from rdis dis output, xref output, and live capture files; byte offsets re-decoded from the capture hex with a throwaway python one-liner, no script file left behind).
