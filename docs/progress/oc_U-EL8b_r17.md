## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #14)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized.

Inputs reviewed: docs/progress/oc_U-L8b.md (PNG/TGA decoder unit — unrelated to atlases; no atlas or compression code there). Prior state carried from oc_U-EL8b_r1..r13 (NOT re-derived): registration, blit, createTexture/resizeTexture decode, mip keys, numMips store, format fallback, BC strings unreferenced. Live data read this unit: docs/data/live/mc_root_4e05e50_callers.txt (150 hits/32 samples, DONE per _status.txt) and docs/data/live/l8b_texcreate_record.txt (24 samples, DONE per _status.txt); docs/data/live/readlog.txt line 125 shows `04:08:45 read 0x7FF6A8215838 0x80`.

## Part 1 — Atlases (terrain, items) — carried [V] rows from oc_U-EL8b_r1..r13 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 (r9d=6 at 0x186f767) via sub_1870de0 inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 (r9d=7 at 0x186f832) via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| registration index store | registered obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | code 0x1870e70 | 4 (dword) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocs 0x48-byte object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | code 0x1870e75 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object | [V] |
| sub_1870de0 name store | code 0x1870ec5 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 | [V] |
| sub_1870de0 registry scan | registry +0..end | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | fixed registry scan for a 0x2A '*' sentinel dword; `0x1870e45  mov [rdx+8],r15` writes range start; `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29` bounds idx to 0..41 | [V] |
| sub_186e6a0 registration dispatcher | code 0x186e6a0 | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | registration loop allocs named objects via sub_1870de0; five atlas names; NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 static callers | xref sub_186e6a0 callers | - | - | - | exactly 2 static callers: sub_8f6810 (+0x61d) and sub_1042320 (+0x1d1) [V via xref.py callers] | [V] |
| sub_1870de0 static callers | xref sub_1870de0 callers | - | - | - | callers include sub_1042320 (+0x1d1) and sub_186e6a0 (+0x1cb7) [V via xref.py callers] | [V] |
| sub_1042320 ServerLevelLoad call site | code 0x1042320 | - | 0x104237e | `0x104237e  call 0x186E6A0` | ServerLevelLoad triggers atlas registration via sub_186e6a0; loads "ResourceLoadType::ServerLevelLoad" at `0x104239b  lea rax,[0xF602326]` | [V] |
| sub_1042320 full listing | code 0x1042320 | - | full listing 0x1042320..0x1044320 | - | grep of the 1778-line listing found NO `call 0xE8143C0` / `0xE815840` / `0xE81BF30` and no TerrainAtlas/ItemAtlas string — ServerLevelLoad registers atlas names but does NOT create atlas textures | [V] |
| sub_8f6810 initStep1 caller | code 0x8f6810 | - | 0x8f685b | `0x8f685b  lea rcx,[0xF7DE3DB]` | second caller of sub_186e6a0 (+0x61d); writes "initStep1" and registers objects | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task name referenced inside 0xbb418d0; functor vtable 0xF43E9E0; body sub_bc02090 reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 | [V] |
| BlitUncompressed key | str data 0xf5f440c | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| item-atlas texture creation | not located | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task exists | [?] |
| terrain-atlas texture creation | not located | - | none | - | not located: xref "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture/resizeTexture call tied to TerrainAtlas | [?] |
| createTexture slot 26 | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (slot 26) builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture has 0 static callers, reached only indirect via [vptr+0xD0]; live callers all ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry decode | code 0xe815840 | mixed (qword/dword/word/byte) | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode [V via rdis dis 0xe815840: `sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in`]: RCX=this renderer (`0xe81586c  mov r14,rcx`), DX=handle word stored (`0xe81586f  mov [rbp+0x8E],dx`), R8D=width->ebx (`0xe815869  mov ebx,r8d`), R9D=mips->edi (`0xe815866  mov edi,r9d`), stack word mips read (`0xe815980  movzx r13d,word ptr [rbp+0x108]`), stack byte layers (`0xe815988  movzx r12d,byte ptr [rbp+0x100]`), renderer+0xBDE178 handle array (`0xe815876  lea rsi,[rcx+0xBDE178]`); resizeTexture (handle,w,h,mips,layers) per BGFX_MAP 1505/1512; mips can be specified on resize; 0 static xrefs — indirect vtable dispatch only; never captured live | [V] |

## Part 2 — mipmaps — carried [V] rows from oc_U-EL8b_r1..r13 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written inside TextureD3D12::create sub_e81bf30; dl loaded at `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed-format fallback 0x42 | code 0xe81bf30 | 1 (byte) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | not located | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-gen Blit task [V]; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression — carried [V]/[I] rows from oc_U-EL8b_r1..r13 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | - | - | references in 0x765330 and PNG decoder 0x777ed0 are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): image (PNG zlib) decompression, called from PNG decoder dispatcher | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | not located | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback [V at `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b`]; live census all-uncompressed [V live] | [V] |

## Part 4 — TexturePtr / texgroup_load / texload / sub_4e05e50 — carried from oc_U-EL8b_r12..r13 (NOT re-derived), with one correction

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | code 0x4E05E50 | - | sub header | - | TexturePtr ensure-loaded/release; `sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in`; reached only indirectly via [0xF99FFA0] from sub_12893d0 at runtime | [V] |
| sub_4e05e50 arg map | regs | - | 0x4e05e6b / 0x4e05e6e | `0x4e05e6b  mov rsi,rdx` / `0x4e05e6e  mov rdi,rcx` | rdi=rcx=a0=TexturePtr-like object (+0x10 pointee, +0x18, +0x58 desc region); rsi=rdx=output | [V] |
| sub_4e05e50 pointee add-ref | pointee +8 | 4 (dword cmpxchg) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref loop on refcount at *(a0+0x10)+8 | [V] |
| sub_4e05e50 pointee destroy | pointee +0 | 8 (qword) | 0x4e05ed8 | `0x4e05ed8  call qword ptr [0xF99FFA0]` | destroys pointee when refcount hits 0 (vtable dtor via thunk) | [V] |
| sub_4e05e50 desc-region call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 (dragon-layer upload bridge) called with rcx=a0+0x58 (texture description region) — upload/ensure-loaded, not atlas creation | [V] |
| sub_4e05e50 result call | out rbp-0x50 | - | 0x4e05f85 | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 on the produced description/result | [V] |
| sub_12893d0 entry | code 0x12893d0 | - | sub header | - | TexturePtr release/collect: walks 0x18-strided entry array [r13..r14), [r13+8]=object pointer; `sub_1289440` is NOT a separate function — rdis shows `loc_1289440` as an INTERNAL label inside sub_12893d0 [V via current rdis dis 0x12893d0, size 0x2000, 13 xrefs in] | [V] |
| sub_12893d0 array walk | elem stride 0x18 | - | 0x1289420 | `0x1289420  add r13,0x18` | next array entry | [V] |
| sub_12893d0 add-ref | entry obj +8 | 4 (dword cmpxchg) | 0x1289447 | `0x1289447  lock cmpxchg [rcx+8],edx` | add-ref object at [r13+8] | [V] |
| sub_12893d0 16-byte copy | entry | 16 (movups) | 0x128944e | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of array entry | [V] |
| sub_12893d0 release pointee | pointee +0x10 | 8 (qword) | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | LIVE-CAPTURED SITE: runtime target = sub_4e05e50; fall-through `0x1289496  nop` = ret=0x1289496 seen in mc_root_4e05e50_callers.txt line 3 for ALL 32 samples | [V live] |
| sub_12893d0 release sites | +0x10/+8 | 8 (qword) | 0x12894b3, 0x1289529, 0x1289544, 0x1289599 (+ more) | `0x12894b3  call qword ptr [0xF99FFA0]` (same instruction text at each) | seven more release/decrement calls through [0xF99FFA0] on old pointees and array entries | [V] |
| sub_12893d0 refcount dec strong | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | destroy at zero | [V] |
| sub_12893d0 refcount dec weak | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | weak-count decrement | [V] |
| sub_12893d0 count output | out +0 | 8 (qword) | 0x12895a8 | `0x12895a8  mov [rsi],r12` | stores collected count | [V] |
| texgroup_load | code 0x5421c90 | - | 0x5421dec | `0x5421dec  call 0x5477a30` | looks up a texture by name in the table via sub_5477a30(rcx=rsi+0x248, rdx=built name), then add-refs; 7 static xrefs in | [V] |
| texgroup_load refcount inc | texture +8 | 4 (dword) | 0x5421e0a | `0x5421e0a  lock inc dword ptr [rcx+8]` | add-ref looked-up texture ([rax+0x68]+8) | [V] |
| texload | code 0x58a1310 | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list ([rbx+0x160..0x168)), calls sub_5417950 per rect, tracks min/max UV at [rbx+0x6C]/[rbx+0x78]; 2 static xrefs in — atlas UV CONSUMPTION, not creation | [V] |
| texload rect read | 0x8 | 4 (movss) | 0x58a1450 | `0x58a1450  movss xmm3,[rcx+8]` | per-rect float read in the rect walk | [V] |
| sub_5477a30 callers | code sub_5477a30 | - | xref | `0x541f8f0 0xc7d`, `0x5421c90 0x190f` | only two static callers: sub_541f8f0 (+0xc7d) and texgroup_load (+0x190f) — no stitcher looks up atlas textures by name | [V] |
| TextureD3D12::create callers | code 0xe81bf30 | - | xref | `0xe8143c0 0x2e1`, `0xe815840 0x3ae` | only createTexture (slot 26) and resizeTexture (slot 31) call TextureD3D12::create; the 0xe8403d0+0xaa5b hit verified as a vtable DATA store (`0xe8eaf2b  mov [rax+0x40],rcx`), not a call | [V] |
| resizeTexture static xrefs | code 0xe815840 | - | xref | none | 0 static xrefs — indirect vtable dispatch only; never captured live | [V] |

## Part 5 — NEW THIS RETRY (r14): live object +0x00 analysis + texcreate census [V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 live caller | CALLER ret=0x1289496 | - | mc_root_4e05e50_callers.txt:3 | `CALLER ret=0x1289496 first_hit=1` — all 150 hits / 32 samples share ONE caller: ret=0x1289496 (fall-through nop after `0x1289490  call qword ptr [0xF99FFA0]` inside sub_12893d0) → sub_4e05e50 is entered only from the TexturePtr release/collect path | [V live] |
| sub_4e05e50 object +0x00 vtable ptr | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt:4 (hit=1 RCX=3908FFDE900) and hits 2-15 | `385821A8F67F0000` at RCX+0x00 → 0x00007FF6A8215838, identical in every sampled object (all RCX lines begin with those bytes) | constant vtable/interface pointer; readlog.txt:125 `04:08:45 read 0x7FF6A8215838 0x80` confirms live access at that VA; capture logs no module base | [V live] |
| sub_4e05e50 object +0x08/+0x10 pointees | obj +0x08/+0x10 | 8 (qword) each | same live lines (RCX dumps) | +0x08 = 0x00000390BE9102B0, +0x10 = 0x00000390BE9102A0 (pointee texture objects, read at `0x4e05e8c  mov rdx,[rdi+0x10]`) | [V live] |
| sub_4e05e50 description bytes | desc region | - | same live lines (RCX dumps) | RCX dump contains `1C000000` (DXGI 0x1C R8G8B8A8_UNORM), three `01000000` dims (1x1x1), `74657800` = "tex\0" fourcc, and item names (e.g. hit=2 line 8: `2E6C656773` = ".legs") — sampled objects are item textures, NOT atlas names; exact field offsets within the +0x58 description region not re-pinned this unit | [V live] |
| sub_4e05e50 object +0x00 module placement | VA 0x00007FF6A8215838 | - | - | - | rdis `sec`: .text rva 0x1000..0xEEC65D6, .rdata from 0xEEC8000 [V]. Under base 0x7FF6A8000000 the VA maps to RVA 0x215838 ∈ `.text` (code), not `.rdata` where vtables live; the run's ASLR base is not recorded in any capture log, so the module/RVA of this pointer cannot be identified statically | [I] — consistent with "atlas logic likely in another module / data-driven" |
| l8b_texcreate_record caller | CALLER ret=0xE814560 | - | l8b_texcreate_record.txt:3 | `CALLER ret=0xE814560 first_hit=1` — all 150 hits / 24 samples: ret=0xE814560 inside createTexture after `0xe81455b  call 0xE81BF30` | [V live] |
| texcreate creation census | creation entries | - | l8b_texcreate_record.txt hits 1-10 | all 24 samples: format 0x1C uncompressed, numMips=1, names "Texture: 2815", "Texture: 2799" and UI/misc paths; ZERO atlas names, ZERO BC formats, ZERO numMips>1 [V live] | [V live] |
| createTexture live census | createtexture_callers.txt | - | - | all hits ret=0xBC6A2C8 command interpreter; R8 description objects format 0x1C, UI/screen texture names only ("store_filter_menu_screen.json", "storage_migration_generic_screen.json", "sidebar_icons/...", "structure_block_corner", "medium_face_cloth_ing.tga", "bread", ...); ZERO atlas names across 25+ samples [V live, carried from oc_U-EL8b_r13] | [V live] |

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas texture-creation STITCHER is still not located:

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) inside sub_186e6a0 (sub_1870de0 0x48-byte object, name at obj+0 `0x1870ec5  mov [rsi],rax`, idx at obj+8 `0x1870ecb  mov [rsi+8],eax`), triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810 (+0x61d). But the registered objects are consumed by NO located reader/stitcher: sub_1042320's full listing creates NO atlas texture [V]; sub_186e6a0 contains no createTexture/resizeTexture call [V]; sub_1870de0's xrefs are all registration-side; no ItemAtlasBlit task exists; blit side is uncompressed ("BlitUncompressed" key `0x560be9f`, TerrainAtlasBlit task `0xbb431ee  lea rdx,[0xF539A0B]`) [V].
- All creation entry points are enumerated and NEGATIVE: createTexture census (live x3: l8b_texcreate_record + createtexture_callers + mc_root_4e05e50_callers context; all UI/misc, format 0x1C, numMips=1, no atlas names [V live]); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture slot 31 has 0 static xrefs and is never observed live [V]; sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release, not creation [V + V live]; sub_5477a30 texture lookup callers = sub_541f8f0 + texgroup_load only, no stitcher [V via xref].
- Live evidence on the +0x00 pointer: every sampled sub_4e05e50 object carries vtable/interface pointer 0x00007FF6A8215838 at +0x00 [V live mc_root_4e05e50_callers.txt hits 1-15; readlog.txt:125]; it cannot be placed in the exe's `.rdata` (vtables' home: rdis sec shows .rdata from rva 0xEEC8000; under base 0x7FF6A8000000 the VA maps to RVA 0x215838 ∈ `.text`) and the run's ASLR base is unrecorded → module unidentified [I]. This is precisely the "another module / data-driven" condition from the original assessment, so the item stays parked (MIRROR_SKIP) unless the pending l8b_resizetex_slot31 capture produces a stitcher caller or the orchestrator decides to mark atlas creation external.
- Parts closed as provably ABSENT (not the blocker): mipmap generation (no GenMip/Mips/MipMap/mipchain code or task; numMips=1 for all live creations [V live]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]) and BC1/BC3/BC7/DXT1-DXT5 compression (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]).

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; only when delegate exits 0 set the line after `## NEXT` to DONE.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 (rva 0xe815840, size 0x100, max 6) — already queued as pending (queue is full at 4: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc); no result in docs/data/live/ yet; NOT re-requested this unit. Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= would name the stitcher caller and mips>1 would be mip-generation evidence. NOTE: sub_1289440_callers targets loc_1289440, an internal label inside sub_12893d0, not a function entry — that request is superseded by the live mc_root_4e05e50_callers result (ret=0x1289496, all 32 samples).
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files; no throwaway scripts written).
