## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste the input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized.

Input reviewed: docs/progress/oc_U-L8b.md (PNG/TGA decoder unit — unrelated to atlases; no atlas or compression code there). Prior state carried from oc_U-EL8b_r1..r54 (NOT re-derived): registration, blit, createTexture/resizeTexture decode, mip keys, numMips store, format fallback, BC strings unreferenced. This retry attacks the single blocking fact (atlas texture-creation stitcher not located) from a NEW angle ordered by the orchestrator: read the two live captures that just became available (mc_root_4e05e50_callers.txt, l8b_texcreate_record.txt), and request a live capture on the extractor/visitor/producer entry proved for this item.

## Part 1 — Atlases (terrain, items) [carried from r54, not re-derived]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| registration index store | registered obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 object alloc size | code 0x1870e70 | 4 (dword) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocs 0x48-byte object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | code 0x1870e75 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object | [V] |
| sub_1870de0 name store | code 0x1870ec5 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 | [V] |
| sub_1870de0 fixed registry scan | code 0x1870e30 | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | fixed registry of 41 entries (idx 0..0x29); loop scans [container+0x20 .. container+0x28) for a 0x2A '*' sentinel dword; `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29` bounds idx to 0..41 | [V] |
| sub_186e6a0 registration dispatcher | code 0x186e6a0 | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop (0x186e6a0..~0x18706a0): allocs named objects via sub_1870de0; five atlas names; NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 static callers | xref sub_186e6a0 callers | - | xref | `0x8f6810 0x61d`, `0x1042320 0x1d1` | sub_186e6a0 has exactly 2 static callers: sub_8f6810 (+0x61d) and sub_1042320 (+0x1d1) [V via xref.py callers] | [V] |
| sub_1870de0 static callers | xref sub_1870de0 callers | - | xref | `0x1042320 0x1d1`, `0x186e6a0 0x1cb7` | sub_1870de0 has 37 xrefs in; callers include sub_1042320 (+0x1d1) and sub_186e6a0 (+0x1cb7) [V via xref.py callers] | [V] |
| sub_1042320 ServerLevelLoad | code 0x1042320 | - | 0x104237e | `0x104237e  call 0x186E6A0` | ServerLevelLoad triggers atlas registration via sub_186e6a0; loads "ResourceLoadType::ServerLevelLoad" at `0x104239b  lea rax,[0xF602326]` | [V] |
| sub_1042320 no texture creation | code 0x1042320 (full fn 0x1042320..0x1044320) | - | full listing | (no `call 0xE8143C0` / `0xE815840` / `0xE81BF30`; no TerrainAtlas/ItemAtlas string) | grep of the 1778-line listing of sub_1042320 found NO createTexture/resizeTexture/TextureD3D12::create call and no atlas string — ServerLevelLoad registers atlas names but does NOT create atlas textures | [V] |
| sub_8f6810 initStep1 caller | code 0x8f6810 | - | 0x8f6810+0x61d | - | second caller of sub_186e6a0 (initStep1); writes "initStep1" at `0x8f685b  lea rcx,[0xF7DE3DB]`; registers objects | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0 | [V] |
| BlitUncompressed key | str data 0xf5f440c | - | ref 0x560be9f | `0x560be9f  lea r9,[0xF5F440C]` | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| item-atlas texture creation | none | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task | [?] |
| terrain-atlas texture creation | none | - | none | - | not located: xref "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture/resizeTexture call tied to TerrainAtlas | [?] |
| createTexture -> TextureD3D12::create call | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (slot 26) builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture itself has 0 static callers, reached only indirect via [vptr+0xD0] (slot 26 = offset 0xD0); live callers all ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry decode | code 0xe815840 | mixed | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode [V via rdis dis 0xe815840: `sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in`]: RCX=this renderer (`0xe81586c  mov r14,rcx`), DX=handle word stored (`0xe81586f  mov [rbp+0x8E],dx`), R8D=width->ebx (`0xe815869  mov ebx,r8d`), R9D=mips->edi (`0xe815866  mov edi,r9d`), stack word mips read (`0xe815980  movzx r13d,word ptr [rbp+0x108]`), stack byte layers (`0xe815988  movzx r12d,byte ptr [rbp+0x100]`), renderer+0xBDE178 handle array (`0xe815876  lea rsi,[rcx+0xBDE178]`); resizeTexture (handle,w,h,mips,layers) per BGFX_MAP 1505/1512; mips can be specified on resize; 0 static xrefs — indirect vtable dispatch only; never captured live | [V] |

## Part 2 — mipmaps [carried from r54, not re-derived]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written inside TextureD3D12::create sub_e81bf30; dl loaded at `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed-format fallback 0x42 | code 0xe81bf30 | 1 (byte) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | none | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-gen Blit task [V]; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression [carried from r54, not re-derived]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542 | - | references in 0x765330 and PNG decoder 0x777ed0 are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): image (PNG zlib) decompression, called from PNG decoder dispatcher | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | none | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live] | [V] |

## Part 4 — NEW THIS RETRY: live capture results (orchestrator-provided, read-only)

mc_root_4e05e50_callers.txt (rva=0x4E05E50, kind=regs, DONE: 150 hits/32 samples): every hit shares one caller — ret=0x1289496, the nop right after `0x1289490  call qword ptr [0xF99FFA0]` inside sub_12893d0. The "sub_1289440" cited in r11/r12 is NOT a function entry: rdis shows `sub_12893d0 [0x12893d0..0x12895d3)  size 0x203  13 xrefs in` and `0x1289440` is just an internal label (`loc_1289440`) inside it; xref.py callers of 0x12893d0 = 0x1145c20(+0x4ae), 0x6622610(+0x1c8), 0x66232b0(+0xb3d0), 0x6632bf0(+0x34b) — none is a texture creator.

l8b_texcreate_record.txt (rva=0xE81BF30, kind=regs, DONE: 150 hits/24 samples): every hit ret=0xE814560 (inside createTexture after `0xe81455b  call 0xE81BF30`), all format 0x1C uncompressed, numMips=1, names "Texture: 2815"/"Texture: 2799" among others, NO atlas names [V live].

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | code 0x4E05E50 | - | sub header | `sub_4e05e50  [0x4e05e50..0x4e06074)  size 0x224  0 xrefs in` | TexturePtr ensure-loaded/release function; 0 static xrefs in (reached indirect via [0xF99FFA0] from sub_12893d0 at runtime) | [V] |
| sub_4e05e50 arg map | regs | - | 0x4e05e6b-0x4e05e6e | `0x4e05e6b  mov rsi,rdx` / `0x4e05e6e  mov rdi,rcx` | rdi=rcx=a0=TexturePtr-like object (+0x10 pointee, +0x18, +0x58 desc region); rsi=rdx=output | [V] |
| sub_4e05e50 pointee add-ref | pointee +8 | 4 (dword cmpxchg) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref loop on refcount at *(a0+0x10)+8 | [V] |
| sub_4e05e50 desc-region call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 (dragon-layer upload bridge) called with rcx=a0+0x58 (texture description region) — upload/ensure-loaded, not atlas creation | [V] |
| sub_4e05e50 result call | out rbp-0x50 | - | 0x4e05f85 | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 on the produced description/result | [V] |
| sub_12893d0 entry | code 0x12893D0 | - | sub header | `sub_12893d0  [0x12893d0..0x12895d3)  size 0x203  13 xrefs in` | TexturePtr release/collect: walks 0x18-strided entry array [r13..r14), [r13+8]=object pointer | [V] |
| sub_12893d0 array walk | elem stride 0x18 | - | 0x1289420 | `0x1289420  add r13,0x18` | next array entry | [V] |
| sub_12893d0 add-ref | entry obj +8 | 4 (dword cmpxchg) | 0x1289447 | `0x1289447  lock cmpxchg [rcx+8],edx` | add-ref object at [r13+8] | [V] |
| sub_12893d0 release pointee | pointee +0x10 | 8 (qword) | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | LIVE-CAPTURED SITE: runtime target = sub_4e05e50; fall-through `0x1289496  nop` = ret=0x1289496 seen in mc_root_4e05e50_callers.txt line 3 for ALL 32 samples | [V live] |
| sub_12893d0 release sites | +0x10/+8 | 8 (qword) | 0x12894b3, 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612 | `0x12894b3  call qword ptr [0xF99FFA0]` (same text at each) | seven more [0xF99FFA0] release/decrement calls on old pointees and array entries | [V] |
| sub_12893d0 refcount dec strong | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | destroy at zero | [V] |
| sub_12893d0 refcount dec weak | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | weak-count decrement | [V] |
| sub_12893d0 count output | out +0 | 8 (qword) | 0x12895a8 | `0x12895a8  mov [rsi],r12` | stores collected count | [V] |
| sub_4e05e50 live RCX +0x00 | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX: `0x7ff6a8215838` | pointer into ANOTHER MODULE (0x00007FF6A8215838) — corroborates "atlas logic likely in another module / data-driven"; PE image range is 0x140000000-0x15383e000, so this ptr is outside the exe | [V live] |
| sub_4e05e50 live RCX +0x10 | obj +0x10 | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x10: `0x390be9102a0` | pointee texture object pointer (sub_4e05e50 reads [rdi+0x10] at `0x4e05e8c  mov rdx,[rdi+0x10]`) | [V live] |
| sub_4e05e50 live RCX +0x60 | desc +0x60 | 4 (dword) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x60: `00000001` `00000001` `00000001` | texture description dims (w/h/array = 1/1/1) at a0+0x58.. passed to sub_bc41420 | [V live] |
| sub_4e05e50 live RCX +0x64 | desc +0x64 | 4 (dword) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x64: `0000001c` | DXGI_FORMAT 0x1C = R8G8B8A8_UNORM (uncompressed) | [V live] |
| sub_4e05e50 live RCX +0x74 | desc +0x74 | 4 (byte tag) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x74: `00786574` = "tex\0" | description fourcc tag "tex" | [V live] |
| sub_4e05e50 live caller | ret=0x1289496 | - | capture header line 3 | `CALLER ret=0x1289496 first_hit=1` | all 150 hits/32 samples: sub_12893d0 is the only caller | [V live] |
| texgroup_load | code 0x5421c90 | - | 0x5421dec | `0x5421dec  call 0x5477a30` | looks up texture by name in table via sub_5477a30(rcx=rsi+0x248, rdx=built name); 7 static xrefs in | [V] |
| texgroup_load add-ref | texture +8 | 4 (dword) | 0x5421e0a | `0x5421e0a  lock inc dword ptr [rcx+8]` | add-ref looked-up texture ([rax+0x68]+8) | [V] |
| texload | code 0x58a1310 | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks 0x30-strided rect list [rbx+0x160..0x168), calls sub_5417950 per rect, tracks min/max UV at [rbx+0x6C]/[rbx+0x78]; 2 static xrefs in — atlas UV CONSUMPTION, not creation | [V] |
| texload rect read | 0x8 | 4 (movss) | 0x58a1450 | `0x58a1450  movss xmm3,[rcx+8]` | per-rect float read | [V] |
| sub_5477a30 (tex table lookup by name) callers | code | - | xref | `0x541f8f0 0xc7d`, `0x5421c90 0x190f` | ONLY two static callers: texgroup_load (+0x190f) and sub_541f8f0 (+0xc7d) — no stitcher looks up atlas textures by name | [V] |
| TextureD3D12::create (0xe81bf30) callers | code | - | xref | `0xe8143c0 0x2e1`, `0xe815840 0x3ae` | only createTexture (slot 26) and resizeTexture (slot 31) call TextureD3D12::create; the xref hit at 0xe8403d0+0xaa5b verified as a vtable DATA store (`0xe8eaf2b  mov [rax+0x40],rcx`), not a call | [V] |
| resizeTexture static xrefs | code 0xe815840 | - | xref | none | 0 static xrefs — indirect vtable dispatch only; never observed live | [V] |

## Interpretation (this retry)

sub_4e05e50's only live caller is sub_12893d0 (TexturePtr release/collect — the sub_6632bf0 "Deferred Texture Transactions" path per r11). sub_4e05e50 itself does refcounting on the pointee ([rdx+8]) and calls sub_bc41420 with the description at a0+0x58 — it is an ensure-loaded/upload bridge, NOT an atlas/mip/compression creator. Live RCX objects carry a description (format 0x1C at +0x64, dims at +0x60/68/6C, "tex" tag at +0x74) and an other-module pointer at +0x00; names seen across samples ("legs", "spear", ...) are never atlas names. texgroup_load/texload only LOOK UP and CONSUME textures (sub_5477a30 has only 2 callers, neither a stitcher).

Creation-entry census (static + live, all of this retry):
- createTexture slot 26 (0xe8143c0 -> TextureD3D12::create 0xe81bf30): 0 static callers (vtable slot 26, offset 0xD0). Live: createtexture_callers.txt (rva=0xE8143C0) — ALL hits ret=0xBC6A2C8 command interpreter; R8 description objects carry format 0x1C and UI/screen texture names only ("store_filter_menu_screen.json", "storage_migration_generic_screen.json", "sidebar_icons/...", "structure_block_corner", "medium_face_cloth_ing.tga", "bread", ...) — 25+ samples, ZERO atlas names [V live]. l8b_texcreate_record.txt (rva=0xE81BF30): 24 samples, all ret=0xE814560 (inside createTexture after `0xe81455b  call 0xE81BF30`), format 0x1C uncompressed, numMips=1, names "Texture: 2815"/"Texture: 2799" among others, NO atlas names [V live].
- resizeTexture slot 31 (0xe815840, takes mips): 0 static xrefs, never observed live.
=> No createTexture/resizeTexture call is ever issued with "TerrainAtlas"/"ItemAtlas" params, statically or in any live capture [V + V live x3].

## New angles tried this retry (all exhausted)

| angle | target | method | result | tag |
|---|---|---|---|---|
| descscan2 on registration dispatcher | sub_186e6a0 | python tools/sigs/descscan2.py --start 0x186e6a0 --end ... | descscan2 only supports visitor cases (--visitor <group> --case N), not arbitrary function ranges; no description-building fields found this way | [I] |
| all callers of sub_1870de0 | sub_1870de0 | `python tools/sigs/xref.py callers 0x1870de0` -> `0x1042320 0x1d1`, `0x186e6a0 0x1cb7` | only 2 callers, both registration-side (ServerLevelLoad + registration dispatcher); no external stitcher creates atlas objects via sub_1870de0 | [V] |
| full disassembly of sub_1870de0 | sub_1870de0 (0x1870e30..0x1872e30, size 0x2000) | rdis dis 0x1870e30 200 | general string-interning/registry function: allocs 0x48-byte object via sub_eea6040 (`0x1870e70  mov edx,0x48`), stores name at +0 (`0x1870ec5  mov [rsi],rax`), idx at +8 (`0x1870ecb  mov [rsi+8],eax`), then string ops via sub_e935700 (`0x1870efb  call 0xE935700`) and sub_eec6de0 (`0x1871059  call 0xEEC6DE0`, `0x1871079  call 0xEEC6DE0`) — NOT a texture description builder, no createTexture/resizeTexture call | [V] |
| livemem read at other-module pointer | 0x7ff6a8215838 | `python tools/sigs/livemem.py read 0x7ff6a8215838 0x100` | unreadable — stale pointer from capture time; game base is 0x7ff7a59c0000, this ptr is outside exe image range | [V live] |
| livemem read at captured RCX object | 0x3908FFDE900 | `python tools/sigs/livemem.py read 0x3908FFDE900 0x100` | unreadable — stale address from capture time | [V live] |
| livemem read at game base | 0x7ff7a59c0000 | `python tools/sigs/livemem.py read 0x7ff7a59c0000 0x40` | readable (MZ header `4d 5a` confirmed) but no atlas objects locatable without scanning (rule 30 forbids scanning/looping ranges) | [V live] |

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas texture-creation STITCHER is not located in the exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, 0xe8143c0 -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, 0xe815840, takes mips) with atlas params:

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) inside sub_186e6a0 (sub_1870de0 0x48-byte object, name at obj+0 `0x1870ec5  mov [rsi],rax`, idx at obj+8 `0x1870ecb  mov [rsi+8],eax`), triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810 (+0x61d). sub_1870de0 scans a fixed registry for a 0x2A '*' sentinel (`0x1870e30  cmp dword ptr [rcx],0x2A`, bound `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29`). But sub_1042320's full 1778-line listing creates NO atlas texture [V]; sub_186e6a0 contains no createTexture/resizeTexture call [V]; sub_1870de0's 37 xrefs are all registration-side; the registered objects are consumed by NO located reader/stitcher. No ItemAtlasBlit task exists; blit side is uncompressed ("BlitUncompressed" key `0x560be9f`, TerrainAtlasBlit task `0xbb431ee  lea rdx,[0xF539A0B]`) [V].
- Creation entry points fully enumerated and negative: createTexture census (live x2: l8b_texcreate_record + createtexture_callers, all UI/misc, format 0x1C, numMips=1, no atlas names [V live]); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture 0 static xrefs, never captured [V]; sub_4e05e50/sub_12893d0 = TexturePtr release/ensure-loaded, not creation [V + V live]; sub_5477a30 texture lookup callers = texgroup_load + sub_541f8f0 only, no stitcher [V via xref].
- Live mc_root_4e05e50_callers objects include an other-module pointer at +0x00 (0x00007FF6A8215838) [V live] — consistent with the original assessment "likely CPU decode in another module / data-driven".
- Parts closed as provably ABSENT (not the blocker): mipmap generation (no GenMip/Mips/MipMap/mipchain code or task; numMips=1 for all live creations [V live]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]) and BC1/BC3/BC7/DXT1-DXT5 compression (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]).

The remaining open part (atlas texture creation) cannot be resolved from static analysis (exhausted over 14 retries; every creation entry point enumerated and negative) nor from currently available live data (x3 captures, no atlas names). The one creation path never observed is resizeTexture slot 31 (takes mips) — capture l8b_resizetex_slot31 remains the highest-value live ask (already pending). sub_1289440_callers request is SUPERSEDED — sub_12893d0's static callers are already known (0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0; none creators), so no capture needed for it. Retry next unit once a capture slot frees, or an orchestrator decision to mark atlas creation external/data-driven.

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; only when delegate check exits 0, set line 2 ("## NEXT") to DONE.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 (rva 0xe815840, size 0x100, max 6) — requested by r11/r12, no result in docs/data/live/. Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= would name the stitcher caller and mips>1 would be mip-generation evidence. createTexture slot 26 already captured (l8b_texcreate_record): all numMips=1, format 0x1C uncompressed, no atlas names.
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files; no throwaway scripts written).
