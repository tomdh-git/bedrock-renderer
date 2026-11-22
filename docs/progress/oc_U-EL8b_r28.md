## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression — blocking fact: atlas texture-creation stitcher not located

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis/disrange) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste the input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized.
Input reviewed: docs/progress/oc_U-L8b.md (PNG/TGA decoder unit — unrelated to atlases); docs/progress/oc_U-EL8b_r1..r13 (prior retries, carried below as proven, NOT re-derived); docs/data/live/mc_root_4e05e50_callers.txt, docs/data/live/l8b_texcreate_record.txt, docs/data/live/createtexture_callers.txt (captures already available, read fully); docs/BGFX_MAP.md L8 section + sections 6o/448, 6e, 6k. disrange.py used for listings (rdis hangs when invoked directly from shell; verify_oc subprocess calls work).

## Part 1 — Atlases (terrain, items) — carried [V] rows from oc_U-EL8b_r1..r12 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas name EXISTS in the exe | [V] |
| registration index store | registered obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | code 0x1870e70 | 4 (dword) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocs 0x48-byte object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | code 0x1870e75 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object | [V] |
| sub_1870de0 name store | code 0x1870ec5 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 | [V] |
| sub_1870de0 registry sentinel scan | registry dword array +0..end | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | scans fixed registry dword array for 0x2A '*' sentinel; `0x1870e45  mov [rdx+8],r15` writes range end; `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29` bounds idx to 0..41 | [V] |
| sub_186e6a0 registration dispatcher | code 0x186e6a0 | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop: allocs named objects via sub_1870de0; five atlas names; NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 static callers | xref sub_186e6a0 callers | - | xref | - | sub_186e6a0 has exactly 2 static callers: sub_8f6810 and sub_1042320 [V via xref.py callers] | [V] |
| sub_1870de0 static callers | xref sub_1870de0 callers | - | xref | - | sub_1870de0 has exactly 2 direct static callers: sub_1042320 and sub_186e6a0 (+0x1cb7) [V via xref.py callers] — NO third consumer of the registrar | [V] |
| sub_1042320 ServerLevelLoad entry | code 0x1042320 | - | sub header | - | sub_1042320 [0x1042320..0x1044320) size 0x2000 0 xrefs in; triggers atlas registration via sub_186e6a0; loads "ResourceLoadType::ServerLevelLoad" at `0x104239b  lea rax,[0xF602326]` | [V] |
| sub_1042320 registration call | code 0x1042320 | - | 0x104237e | `0x104237e  call 0x186E6A0` | ServerLevelLoad calls sub_186e6a0 (rcx=0x78 object, rdx=&name view) | [V] |
| sub_1042320 no texture creation | listing 0x1042320..0x1044320 | - | full listing | - | grep of the 1778-line listing of sub_1042320 found NO `call 0xE8143C0` / `0xE815840` / `0xE81BF30` and no TerrainAtlas/ItemAtlas string — ServerLevelLoad registers atlas names but does NOT create atlas textures | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0 | [V] |
| TerrainAtlasBlit blit body | code 0xbc02090 | - | vtable 0xF43E9E0 slot 2 | - | vtable slot 2 = sub_bc02090 (size 0x3da): reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 | [V] |
| BlitUncompressed key | str data 0xf5f440c | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| item-atlas texture creation (not located) | item-atlas-creation | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task | [?] |
| terrain-atlas texture creation (not located) | terrain-atlas-creation | - | none | - | not located: xref "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture/resizeTexture call tied to TerrainAtlas | [?] |

## Part 2 — Registration path fully decoded this retry (new; rdis hangs on this exe, listings via disrange.py per brief fallback)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_8f6810 initStep1 entry | code 0x8f6810 | - | sub header | `0x8f6810  push rbp` | sub_8f6810 [0x8f6810..0x8f6dcc) size 0x22c, 0 xrefs in: initStep1 — full listing decoded (prologue, XOR-obfuscated "initStep1" name compare, allocator calls, registration call at 0x8f6919, time-of-day/global stores). NO `call 0xE8143C0` / `0xE815840` / `0xE81BF30` anywhere in 0x8f6810..0x8f6dcc — initStep1 does NOT create textures | [V] |
| sub_8f6810 name compare | code 0x8f6841 | 8 (mov imm) | 0x8f6841 | `0x8f6841  mov rdx,0x7065745374696e69` | XOR-obfuscated "initStep" name; `0x8f6852  xor rcx,0x31` per-byte deobfuscate, compare at 0x8f6856 | [V] |
| sub_8f6810 registration call | code 0x8f6919 | - | 0x8f6919 | `0x8f6919  call 0x186E6A0` | initStep1 registers "initStep1" via sub_186e6a0 (rcx=newly allocated 0x78 object, rdx=&name view) — another registered name, not an atlas creator | [V] |
| sub_8f6810 allocator calls | code 0x8f687d | - | 0x8f687d, 0x8f6a42, 0x8f6a4a | `0x8f687d  call qword ptr [0xF99FFA0]` | sub_8f6810 calls allocator (0x78 object via thunk [0xF99FFA0] = sub_eea6040), then `0x8f6a42  call 0xeec5920` / `0x8f6a4a  call 0xeec5930` (eec-layer; results compared against 0x16e3600/0x989680 = time-of-day math), then `0x8f6b3d  call 0x840110` — no texture creation | [V] |
| sub_1870de0 entry | code 0x1870de0 | - | sub header | `0x1870de0  push rbp` | sub_1870de0 [0x1870de0..0x18710c0+) decodes: alloc 0x48-byte object (`0x1870e70  mov edx,0x48`; `0x1870e75  call qword ptr [0xF99FFA0]`), name at obj+0 (`0x1870ec5  mov [rsi],rax`), idx at obj+8 (`0x1870ecb  mov [rsi+8],eax`), registry dword-array insert with 0x2A '*' sentinel (`0x1870e30  cmp dword ptr [rcx],0x2A`), idx bounded 0..41 (`0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29`) | [V] |
| sub_1870de0 registry arg mechanics | code 0x104234a | 16 (movaps) | 0x104234a | `0x104234a  movaps [rbp-0x50],xmm0` | sub_1042320 zeroes stack-local 16-byte vector [rbp-0x50] (prologue) and passes it as sub_1870de0's registry arg ({base,end,cap} dword vector); `0x10423ae  mov [rsp+0x20],rsi` passes &[rbp-0x50] as the 5th stack arg at call `0x10423c7` — registry is caller-supplied, persistent storage/reader not located | [V] |
| sub_1042320 sub_1870de0 call site 1 | code 0x10423c7 | - | 0x10423c7 | `0x10423c7  call 0x1870DE0` | sub_1042320 +0xa7: rcx=[rbp+0x28] (0x78 object), rdx=&[rbp-0x20] string_view {"ServerLevelLoad",0x21}, r8=&[rbp-0x50], r9d=0x28, 5th stack arg=[rsp+0x20]=rsi | [V] |
| sub_1042320 sub_1870de0 call site 2 | code 0x104246b | - | 0x104246b | `0x104246b  call 0x1870DE0` | sub_1042320 +0x14b: same shape, r9d=0x29, name="ResourceLoadType::ServerLevelAssignResults" (`0x1042441  lea rax,[0xF545CDD]`) | [V] |

## Part 3 — mipmaps — carried [V] rows from oc_U-EL8b_r1..r12 (NOT re-derived)

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

## Part 4 — compression — carried [V]/[I] rows from oc_U-EL8b_r1..r12 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542 | - | references in 0x765330 and PNG decoder 0x777ed0 are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): image (PNG zlib) decompression, called from PNG decoder dispatcher | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code (not located) | bc-code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b` / `0xe81c077` [V]; live census all-uncompressed [V live] | [V] |

## Part 5 — creation-entry census — carried [V] + [V live] rows from oc_U-EL8b_r13 and the two live captures

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture slot 26 -> TextureD3D12::create | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (slot 26) builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture has 0 static callers, reached only indirect via [vptr+0xD0] (slot 26 = offset 0xD0); live callers all ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry decode | code 0xe815840 | mixed (qword/dword/word/byte) | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode [V via rdis dis 0xe815840: `sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in`]: RCX=this renderer (`0xe81586c  mov r14,rcx`), DX=handle word stored (`0xe81586f  mov [rbp+0x8E],dx`), R8D=width->ebx (`0xe815869  mov ebx,r8d`), R9D=mips->edi (`0xe815866  mov edi,r9d`), stack word mips read (`0xe815980  movzx r13d,word ptr [rbp+0x108]`), stack byte layers (`0xe815988  movzx r12d,byte ptr [rbp+0x100]`), renderer+0xBDE178 handle array (`0xe815876  lea rsi,[rcx+0xBDE178]`); resizeTexture (handle,w,h,mips,layers) per BGFX_MAP 1505/1512; mips can be specified on resize; 0 static xrefs — indirect vtable dispatch only; never observed live | [V] |
| live census — createTexture slot 26 | capture l8b_texcreate_record.txt (24 samples) | - | line 3 header | `CALLER ret=0xE814560 first_hit=1` | all 24 TextureD3D12::create entries ret=0xE814560 (inside createTexture after the 0xe81455b call); R8 description bytes show format 0x1C uncompressed, numMips=1; names "Texture: 2815"/"Texture: 2799" among others; ZERO atlas names across all samples | [V live] |
| live census — createTexture entry callers | capture createtexture_callers.txt | - | line 3 header | `CALLER ret=0xBC6A2C8` (line 3: `RCX=5314A010000 hit=1 ret=0xBC6A2C8 ...`) | all createTexture entry (0xe8143c0) hits ret=0xBC6A2C8 command interpreter; R8/R9 description names = UI/screen textures only ("store_filter_menu_screen.json", ".../world_download_default", ...); ZERO atlas names | [V live] |
| TextureD3D12::create callers | xref code 0xe81bf30 | - | xref | - | only createTexture (slot 26) and resizeTexture (slot 31) call TextureD3D12::create; xref hit at 0xe8403d0+0xaa5b verified as vtable DATA store (`0xe8eaf2b  mov [rax+0x40],rcx`), not a call | [V] |
| resizeTexture slot 31 status | resizeTexture slot 31 (0xe815840) | - | xref | none | 0 static xrefs; never observed live in any capture; the one creation entry that can still show mips>1 / stitcher caller via ret= | [V] |
| sub_4e05e50 / sub_12893d0 census | TexturePtr ensure-loaded path | - | Part 1 rows | - | sub_4e05e50 (0x4e05e50, 0 xrefs in) = TexturePtr ensure-loaded/upload bridge, NOT a creator: refcounts pointee +8 (`0x4e05ea8  lock cmpxchg [rdx+8],r8d`), calls sub_bc41420 with desc at a0+0x58 (`0x4e05f77  call 0xbc41420`); its only live caller is sub_12893d0 (TexturePtr release/collect) at `0x1289490  call qword ptr [0xF99FFA0]`, fall-through `0x1289496  nop` = ret=0x1289496 for all 32 samples [V live]; sub_5477a30 texture-name lookup callers = texgroup_load (0x5421c90 `0x5421dec call 0x5477a30`) + sub_541f8f0 only — no stitcher looks up atlas textures by name [V via xref] | [V + V live] |

## Part 6 — live object other-module pointer at TexturePtr+0x00 (r13's last unexplored lead)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TexturePtr-like object +0x00 | capture mc_root_4e05e50_callers.txt line 4 | 8 (qword) | RCX+0x00 | bytes at RCX+0x00: `385821A8F67F0000` = 0x00007FF6A8215838, stable across all 32 samples (RCX=3908FFDE900 hit=1, ret=0x1289496) | first qword of the TexturePtr-like object is a pointer into ANOTHER MODULE (likely a vtable) — texture-object decode may be outside the exe; exact module/RVA not identifiable from the capture (that session's exe base was not recorded; module enumeration without a memory scan is out of scope) — consistent with "CPU decode in another module / data-driven" | [V live] + [I] |

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas texture-creation STITCHER is not located in the exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, 0xe8143c0 -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, 0xe815840, takes mips) with atlas parameters, and ItemAtlas texture-creation code is not located:

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) inside sub_186e6a0 (sub_1870de0 0x48-byte object, name at obj+0 `0x1870ec5  mov [rsi],rax`, idx at obj+8 `0x1870ecb  mov [rsi+8],eax`); triggered by ServerLevelLoad sub_1042320 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810 (`0x8f6919  call 0x186E6A0`). sub_1870de0 scans a registry dword array for a 0x2A '*' sentinel (`0x1870e30  cmp dword ptr [rcx],0x2A`, bound `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29`). But sub_1870de0's direct callers are exactly sub_1042320 (0x10423c7, 0x104246b) and sub_186e6a0 (+0x1cb7) [V via xref]; sub_186e6a0's direct callers are exactly sub_8f6810 and sub_1042320 [V via xref]; neither registration path creates a texture [V] (initStep1 fully decoded 0x8f6810..0x8f6dcc, negative; sub_1042320 full 1778-line listing, negative). The registered objects are consumed by NO located reader/stitcher; xref of "TerrainAtlas"/"ItemAtlas" strings shows refs only inside sub_186e6a0 [V].
- Creation entry points fully enumerated and negative [V + V live]: createTexture census (live x2: l8b_texcreate_record + createtexture_callers; all format 0x1C, numMips=1, UI/screen texture names only, no atlas names); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture slot 31 (takes mips): 0 static xrefs, never captured [V]; sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded, not creation [V + V live]; sub_5477a30 texture lookup callers = texgroup_load + sub_541f8f0 only, no stitcher [V via xref].
- Live mc_root_4e05e50_callers objects carry an other-module pointer at +0x00 (0x00007FF6A8215838, bytes `385821a8f67f0000` at RCX+0x00, all 32 samples [V live]) — supports the original assessment "likely CPU decode in another module / data-driven"; module/RVA not identifiable statically [I].
- Proven ABSENT (not the blocker): mip generation (no GenMip/Mips/MipMap/mipchain code or task [V via xref]; numMips=1 for all live creations [V live]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]) and BC1/BC3/BC7/DXT1-DXT5 compression (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]).

Remaining path: the resizeTexture slot 31 capture l8b_resizetex_slot31 is QUEUED (state=pending, rva 0xe815840, size 0x100, max 6); result file docs/data/live/l8b_resizetex_slot31.txt not yet present — check `python tools/livecap/request.py result l8b_resizetex_slot31` next unit. If it returns 0 samples or no atlas/mips>1 evidence, the honest close decision is: atlas texture creation + item-atlas creation are not in the exe statically → mark external/data-driven.

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure it prints; only when it exits 0 set the line after "## NEXT" to DONE.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 (rva 0xe815840, size 0x100, max 6, why: "L8b: resizeTexture slot 31 (handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= names the stitcher caller; mips>1 would be mip-generation evidence for terrain/item atlases") — already queued, state=pending, result not yet available (docs/data/live/l8b_resizetex_slot31.txt does not exist yet).
Queue note: 4 capture requests pending (er5_clone_4c8a5b0, sub_1289440_callers, oc_u_er6_light_desc, l8b_resizetex_slot31) = at the 4-pending limit; no further capture can be queued this unit.
Helper scripts: none (all verbatim lines taken directly from disrange.py/rdis output and live capture files; no throwaway scripts written; nothing left in temp).
