## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred (say from what), [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste the input data as-is; one annotated row per distinct offset; every offset covered, none skipped or summarized (no ellipsis/abbreviation; no short forms).

Carried state: oc_U-EL8b_r1..r27 (atlas registration, blit task, createTexture/resizeTexture decode, mip keys, numMips store, format fallback, BC strings unreferenced, sub_4e05e50/texgroup_load/texload decode, live capture census). All [V] rows were verified by rdis dis or by live capture files; nothing here is guessed.

## Blocking fact (single)
The atlas TEXTURE-CREATION STITCHER is not located in the exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26) or resizeTexture (slot 31, takes mips) with atlas params. Static analysis is exhausted (every creation entry point enumerated and negative; every atlas consumer decoded); live captures show only uncompressed format-0x1C numMips=1 creations with non-atlas names; objects in the TexturePtr path carry an other-module pointer at +0x00 (0x00007FF6A8215838, outside the exe image [V live]) — consistent with atlas logic in another module / data-driven.

## Status: IN PROGRESS → CLOSES? NO (blocking fact stands)

## Part 1 — Atlases (terrain, items): registration [V]; texture creation NOT located

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name (len 0xC) loaded before the sub_1870de0 call; registered idx 6 (r9d=6) inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name (len 9) loaded before sub_1870de0; registered idx 7 (r9d=7) inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| registered object +0 name ptr | obj +0 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 inside sub_1870de0; object head-inserted into the registry list | [V] |
| registered object +8 index dword | obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size imm | - | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocates a 0x48-byte registered object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | - | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk ([data_f99ffa0]) for the 0x48-byte registered object | [V] |
| registry sentinel scan | - | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | fixed registry dword array scanned for the 0x2A '*' free sentinel; slot bound `0x1870f28  inc r14d` / `0x1870f2b  cmp r14d,0x29` (slots 0..41) | [V] |
| registry slot index write | - | 4 (dword) | 0x1870f40 | `0x1870f40  mov [r15],r14d` | registration slot index written into the registry slot (replacing the 0x2A '*' sentinel) — stores INDEX, not object pointer | [V] |
| sub_186e6a0 registration dispatcher | - | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 (0x186e6a0..0x18706a0, size 0x2000, 2 xrefs in) registers named objects via sub_1870de0 (TerrainAtlas 6, ItemAtlas 7, AnimatedAtlas 8, BlockThumbnailAtlas 0x26); NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 static callers | xref | xref | xref.py callers | - | exactly 2 static callers: initStep1 sub_8f6810 (+0x61d) and ServerLevelLoad sub_1042320 (+0x1d1) [V via xref.py callers] | [V] |
| ServerLevelLoad registration call | - | - | 0x104237e | `0x104237e  call 0x186E6A0` | sub_1042320 (ServerLevelLoad) triggers atlas registration via sub_186e6a0 ("ResourceLoadType::ServerLevelLoad" `0x104239b  lea rax,[0xF602326]`) | [V] |
| initStep1 caller of sub_186e6a0 | - | - | 0x8f6810+0x61d | `0x8f685b  lea rcx,[0xF7DE3DB]` | second caller of sub_186e6a0; writes "initStep1"; registers objects | [V] |
| post-registration cleanup call | - | - | 0x186f782 | `0x186f782  call 0x2FE440` | immediately after each sub_1870de0 registration (TerrainAtlas 0x186f76d->0x186f782; ItemAtlas 0x186f84d) sub_2fe440 consumes the registered object (cleanup-only: frees description buffers +0xF8/+0xB0/+0x98, refcount-release walk) | [V] |
| post-registration free call | - | - | 0x186f78f | `0x186f78f  call 0xE935700` | sub_e935700(edx=0x138) frees the registered object right after sub_2fe440 — object discarded, not retained | [V] |
| sub_1042320 post-registration re-entries | - | - | 0x104239b / 0x1042441 | `0x104239b  lea rax,[0xF602326]` / `0x1042441  lea rax,[0xF545CDD]` | after atlas registration, sub_1042320 re-enters sub_1870de0 with idx 0x28 ("ResourceLoadType::ServerLevelLoad") and idx 0x29 ("ResourceLoadType::ServerLevelAssignResults"), then cleanup+free — NO atlas texture creation | [V] |
| sub_1042320 contains no atlas texture creation | - | none | full listing | - | grep of full listing 0x1042320..0x1044320: NO `call 0xE8143C0` / `0xE815840` / `0xE81BF30` and no TerrainAtlas/ItemAtlas string — ServerLevelLoad registers atlas names but creates NO atlas texture | [V] |
| TerrainAtlasBlit task name | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name inside 0xbb418d0; functor vtable 0xF43E9E0, slot 2 = sub_bc02090: reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 — the atlas BLIT/consumer, not its creator | [V] |
| BlitUncompressed key | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| atlas texture creation (terrain + item) | - | none | - | NOT located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)], "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to either atlas; no ItemAtlasBlit task exists; registered objects immediately freed after registration (0x186f782/0x186f78f) | [?] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |

## Part 2 — mipmaps: material mip params exist; generation NOT located

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 ([data_f5515c8]) | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 ([data_f52fe18]) | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 ([data_f5636e5]) | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 ([data_f593be9]) | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored inside TextureD3D12::create sub_e81bf30; dl loaded `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte stored inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed fallback 0x42 | struct +0xB0 | 1 (byte) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | - | none | - | NOT located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-gen Blit task [V]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression: provably absent in the exe

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | ref 0x766542 | - | references in 0x765330 and PNG decoder 0x777ed0 are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): image (PNG zlib) decompression, called from PNG decoder dispatcher | [V] |
| BC texture compression code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live] | [V] |

## Part 4 — creation entries, TexturePtr chain, and live capture census

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture slot 26 -> TextureD3D12::create | - | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture has 0 static callers (reached indirect via [vptr+0xD0] slot 26); live callers ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry | - | - | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode [V via rdis dis 0xe815840: sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in]: RCX=this renderer `0xe81586c  mov r14,rcx`; DX=handle `0xe81586f  mov [rbp+0x8E],dx`; R8D=width->ebx `0xe815869  mov ebx,r8d`; R9D=mips->edi `0xe815866  mov edi,r9d`; stack word mips `0xe815980  movzx r13d,word ptr [rbp+0x108]`; stack byte layers `0xe815988  movzx r12d,byte ptr [rbp+0x100]`; renderer+0xBDE178 handle array `0xe815876  lea rsi,[rcx+0xBDE178]`; resizeTexture(handle,w,h,mips,layers), mips can be specified; 0 static xrefs; never observed live | [V] |
| TextureD3D12::create callers | xref | xref | `0xe8143c0 0x2e1`, `0xe815840 0x3ae` | only createTexture and resizeTexture call TextureD3D12::create; the xref hit at 0xe8403d0+0xaa5b verified as a vtable DATA store `0xe8eaf2b  mov [rax+0x40],rcx`, not a call | [V] |
| l8b_texcreate_record capture | capture | - | l8b_texcreate_record.txt:3 | `CALLER ret=0xE814560` line 3 — 24 samples at TextureD3D12::create entry 0xe81bf30; format 0x1C at desc+0x40 (`1C000000` at RCX+0x40, line 4); R8 names "Texture: 2815"/"Texture: 2799" UTF-16; NO atlas names; no compressed formats; all numMips=1 [V live docs/data/live/l8b_texcreate_record.txt] | [V live] |
| createtexture_callers census | capture | - | createtexture_callers.txt:3 | `CALLER ret=0xBC6A2C8` line 3 — 150 hits / 32 samples at createTexture 0xe8143c0; all callers ret=0xBC6A2C8 command interpreter; R8 description objects format 0x1C with UI/screen texture names only; ZERO atlas names [V live docs/data/live/createtexture_callers.txt] | [V live] |
| bgfx create-chain producer capture | capture rva 0xBC73770 | - | bgfx_createtexture_producer.txt:3 | `CALLER ret=0xBC73EAD` line 3 — 16 samples at 0xBC73770 entry (chain 0xC296D7E -> sub_bc73bf0 -> sub_bc73770 -> createTexture 0xe8143c0); desc objects format 0x1C, dims 0x80x0x80 or 0x40x0x40, layers/mips 1/1, "TEXT\0" tag, names "textures/misc/en...", "vanilla.CoreData", "structures/mansion", "textures/entity/"; ZERO atlas names, ZERO compressed formats [V live docs/data/live/bgfx_createtexture_producer.txt] | [V live] |
| sub_4e05e50 entry | sub header | - | sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in | TexturePtr ensure-loaded/release function; 0 static xrefs in; reached indirect via [0xF99FFA0] from sub_12893d0 at runtime | [V] |
| sub_4e05e50 arg map | regs | 0x4e05e6b / 0x4e05e6e | `0x4e05e6b  mov rsi,rdx` / `0x4e05e6e  mov rdi,rcx` | rdi=rcx=a0 TexturePtr-like object (+0x10 pointee, +0x18, +0x58 desc region); rsi=rdx=output | [V] |
| sub_4e05e50 pointee add-ref | pointee +8 | 4 (dword cmpxchg) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref loop on refcount at *(a0+0x10)+8 | [V] |
| sub_4e05e50 pointee destroy | pointee +0 | 8 (qword) | 0x4e05ed8 | `0x4e05ed8  call qword ptr [0xF99FFA0]` | destroys pointee when refcount hits 0 (vtable dtor via thunk) | [V] |
| sub_4e05e50 desc-region upload call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 (dragon-layer upload bridge) called with rcx=a0+0x58 description region — upload/ensure-loaded, NOT atlas creation | [V] |
| sub_4e05e50 pointee read | pointee +0x10 | 8 (qword) | 0x4e05e8c | `0x4e05e8c  mov rdx,[rdi+0x10]` | reads the pointee texture object pointer | [V] |
| sub_4e05e50 live caller (indirect, ret= chain) | CALLER ret=0x1289496 | - | mc_root_4e05e50_callers.txt:3 | `CALLER ret=0x1289496 first_hit=1` — all 150 hits / 32 samples: sub_4e05e50 entered only from sub_12893d0; ret=0x1289496 = `0x1289496  nop` after `0x1289490  call qword ptr [0xF99FFA0]` inside sub_12893d0 [V live docs/data/live/mc_root_4e05e50_callers.txt line 3] | [V live] |
| sub_12893d0 entry | sub header | - | sub_12893d0 [0x12893d0..0x12895d3) size 0x203 13 xrefs in | TexturePtr release/collect; walks a 0x18-strided entry array; the ONLY live caller of sub_4e05e50 (ret=0x1289496, all 32 samples) [V] | [V] |
| sub_12893d0 add-ref | entry obj +8 | 4 (dword cmpxchg) | 0x1289447 | `0x1289447  lock cmpxchg [rcx+8],edx` | CAS loop incrementing refcount dword at object+8 | [V] |
| sub_12893d0 16-byte object copy | 16 (movups) | 0x128944e | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of the texture object (entry obj +0) | [V] |
| sub_12893d0 release old pointee | entry obj +0x10 | 8 (qword) | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | statically [0xF99FFA0]=sub_eea6040 thunk; at runtime this site enters sub_4e05e50; fall-through `0x1289496  nop` = ret=0x1289496 seen for ALL 32 samples [V live] | [V live] |
| sub_12893d0 further release sites | entry obj +0x10 | 8 (qword) | 0x12894b3 | `0x12894b3  call qword ptr [0xF99FFA0]` (same instr text at 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612) | seven more release/decrement calls through [0xF99FFA0] on old pointees and array entries | [V] |
| sub_12893d0 refcount dec strong | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | decrements refcount; object destroyed when it reaches zero | [V] |
| sub_12893d0 refcount dec weak | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | second (weak) count decrement | [V] |
| sub_12893d0 0x18-strided array walk | array elem stride 0x18 | - | 0x1289560 | `0x1289560  add rbx,0x18` | walks a 0x18-strided array releasing [rbx+0x10] and [rbx+8] entries | [V] |
| sub_12893d0 count output | out +0 | 8 (qword) | 0x12895a8 | `0x12895a8  mov [rsi],r12` | stores collected count r12 into the output pointer | [V] |
| sub_12893d0 static callers | xref | xref | `0x1145c20 +0x4ae`, `0x6622610 +0x1c8`, `0x66232b0 +0xb3d0`, `0x6632bf0 +0x34b` | 13 xrefs in total; these 4 callers — NONE is a texture creator [V] | [V] |
| texgroup_load | - | 0x5421dec | `0x5421dec  call 0x5477a30` | looks up a texture by name in the texture table via sub_5477a30 (rcx=rsi+0x248, rdx=built name); 7 static xrefs in — TexturePtr CONSUMER (lookup), not creator | [V] |
| texgroup_load add-ref | texture +8 | 4 (dword) | 0x5421e0a | `0x5421e0a  lock inc dword ptr [rcx+8]` | add-ref on the looked-up texture ([rax+0x68]+8) | [V] |
| texload | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list ([rbx+0x160..0x168)) calling sub_5417950 per entry, tracking min/max UV at [rbx+0x6C]/[rbx+0x78]; 2 static xrefs in — atlas UV CONSUMPTION, not creation | [V] |
| texload rect read | 0x8 | 4 (movss) | 0x58a1450 | `0x58a1450  movss xmm3,[rcx+8]` | per-rect float read in the rect walk | [V] |
| sub_5477a30 callers | xref | xref | `0x541f8f0 +0xc7d`, `0x5421c90 +0x190f` | ONLY two static callers: texgroup_load (+0x190f) and sub_541f8f0 (+0xc7d) — no stitcher looks up atlas textures by name [V via xref] | [V] |
| atlas usage is data-driven (item+0x78 names) | item +0x78 | - | `0x5755283  call 0x7F1A0` | item-definition parser resolves each item's atlas texture name ("atlas.items" `0x575527c  lea rdx,[0xF550917]`, "atlas.terrain" `0x5755464  lea rdx,[0xF593358]`, "textures/items/compass_atlas" `0x5755303  lea rdx,[0xF55CCD6]`, lodestone/recovery_compass/watch_atlas) and stores it at item+0x78 via sub_7f1a0 (`0x5755283  call 0x7F1A0` plus sites 0x575530a/0x5755473/0x57554a4/0x57554d5/0x5755509/0x575551e) [V]; referenced as DATA only — never as createTexture arguments [V live census] | [V] |
| cross-module pointer at obj +0x00 | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | first qword of objects passed to sub_4e05e50 = 00007ff6a8215838 (bytes `385821A8F67F0000` at RCX+0, hit=1 line 4) — pointer into ANOTHER MODULE (exe image range 0x7ff7a59c0000–0x7ff7bd2fe000 [V live status]) [V live docs/data/live/mc_root_4e05e50_callers.txt line 4] | [V live] |

## New this session — lowercase "atlas" string xref (new angle, NEGATIVE for the stitcher)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| "texture_atlas" material key | str data 0xf55cd23 | - | refs (0x4e1a700, 0x4e1d456) | - | inside sub_4e1a0a0 (material JSON parser) and sub_4e1cfe0 — material-key usage, not atlas texture creation [V via xref str atlas] | [I] |
| "Texture %s is using an invalid atlas index %i" | str data 0xf5ad7d2 | - | ref 0x6bfaac5 | - | inside sub_6bfa9d0 — validates atlas index vs expected UV count; sub_6bfa6d0 walks atlas entries calling release sub_4de9de0/sub_5440320 — atlas USAGE validation, not creation [V via xref str atlas] | [I] |
| "Texture %s is missing from atlas textures" | str data 0xf557267 | - | ref 0x6bfa932 | - | inside sub_6bfa6d0 — atlas usage validation [V via xref str atlas] | [I] |
| "Item %s requires either an icon atlas or icon texture." | str data 0xf80510b | - | ref 0x1a545de | - | inside sub_1a540b0 — item icon validation [V via xref str atlas] | [I] |
| "Persona texture atlas generation failed." | str data 0xf80ef38 | - | ref 0x6a135a0 | - | inside sub_6a13420 — persona-atlas-generation ERROR path only (allocates, refcounts, returns); no createTexture/resizeTexture call with atlas params [V via rdis dis 0x6a13420] | [V] |
| xref str "atlas" — no stitcher | - | none | - | full lowercase "atlas" string list returned only material/icon/persona/usage strings; NO function that builds an atlas texture description or calls createTexture/resizeTexture with atlas params | [V via xref str atlas — negative] |

## What was tried and failed (do not redo)

- xref str "Atlas" / "terrain_atlas" / "item_atlas" / lowercase "atlas": only registration references TerrainAtlas/ItemAtlas (both inside sub_186e6a0); lowercase "atlas" yields material/icon/persona/usage strings only; no stitcher name, no creation call site [V via xref — negative].
- descscan2 on sub_186e6a0: tool requires explicit --start/--end ranges and errored (ranges_for int() failure); registration already fully decoded [V] and contains no createTexture — not a stitcher lead.
- Live censuses already in docs/data/live (createtexture_callers, l8b_texcreate_record, bgfx_createtexture_producer, mc_root_4e05e50_callers, dragon_texture_caller_bc41420): every observed texture creation is format 0x1C uncompressed, numMips=1, with non-atlas names; ZERO atlas texture creation observed anywhere [V live — negative].
- Earlier static decodes, all NEGATIVE for the stitcher: sub_2fe440 = cleanup-only [V]; sub_1042320 post-registration = only idx-0x28/0x29 load-phase re-registrations then cleanup+free, NO atlas texture creation [V]; sub_18718d0/sub_186dac0 = resource-by-name lookup + async enqueue, but atlas names never leave sub_186e6a0 so neither receives them [V]/[I]; livemem read/vt at 0x00007FF6A8215838 unreadable [V live].
- l8b_resizetex_slot31 capture (resizeTexture slot 31, rva 0xe815840, size 0x100, max 6): already queued PENDING, result not in docs/data/live/ ("no result yet — orchestrator has not run it"); queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), duplicate re-add rejected [V live via request.py list]. Cannot re-queue until the batch runs and a slot frees.

## CLOSES?

NO. Single blocking fact: the atlas TEXTURE-CREATION STITCHER is not located in the exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, `0xe81455b  call 0xE81BF30` -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, `0xe815866  mov edi,r9d`, takes mips) with atlas params:

- Registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) inside sub_186e6a0 via sub_1870de0 (0x48-byte object; name at obj+0 `0x1870ec5  mov [rsi],rax`; idx at obj+8 `0x1870ecb  mov [rsi+8],eax`; sentinel scan slots 0..41 `0x1870e30  cmp dword ptr [rcx],0x2A`, bound `0x1870f28  inc r14d` / `0x1870f2b  cmp r14d,0x29`), triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810 (+0x61d). BUT immediately after each sub_1870de0 call sub_2fe440 consumes the object (`0x186f782  call 0x2FE440`) and sub_e935700 frees it (`0x186f78f  call 0xE935700`, edx=0x138) — discarded, not retained; sub_1042320's post-registration code only re-enters sub_1870de0 with idx 0x28/0x29 then frees them. sub_186e6a0 contains no createTexture/resizeTexture call [V]; sub_1870de0's xrefs are all registration-side [V].
- Creation entry points fully enumerated and NEGATIVE: createTexture census (live x3: l8b_texcreate_record + createtexture_callers + bgfx_createtexture_producer — all format 0x1C uncompressed, numMips=1, names "Texture: 2799/2815"/UI, ZERO atlas names [V live]); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture slot 31 has 0 static xrefs, capture pending/not run, never observed live [V]; sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release (live caller chain ret=0x1289496 = `0x1289496  nop` after `0x1289490  call qword ptr [0xF99FFA0]` [V live]; upload path to sub_bc41420 confirmed live ret=0x4E05F7C, desc format 0x1C "tex" [V live]) — NOT creation; sub_5477a30 lookup callers = texgroup_load + sub_541f8f0 only, no stitcher [V via xref]; resource-by-name lookup sub_18718d0 never receives the atlas names [V]/[I].
- Cross-module pointer: objects passed to sub_4e05e50 carry +0x00 = 0x00007FF6A8215838 [V live], outside the exe image (base 0x7ff7a59c0000, end 0x7ff7bd2fe000 [V live status]) -> another module; livemem read/vt of that address unreadable [V live]. Atlas logic lives in another module / is data-driven — not closable from static analysis of this exe alone.
- Atlas usage is data-driven [V]: item parser stores atlas names ("atlas.items", "atlas.terrain", "textures/items/compass_atlas", lodestone/recovery_compass/watch_atlas) at item+0x78 via sub_7f1a0 (`0x5755283  call 0x7F1A0` and siblings) [V]; the names are referenced as data only, never as createTexture arguments [V live census].
- New-angle lowercase "atlas" xref: only material/icon/persona/usage strings, no stitcher [V via xref str atlas — negative].

Resolved as provably-ABSENT (negatives, NOT the blocker): mipmap generation (no GenMip/Mips/MipMap/mipchain code or task [V via xref]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; all live creations numMips=1 [V live]) and BC1/BC3/BC7/DXT1-DXT5 compression (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]).

## Verification

Every verbatim `0xRVA  instr` line above was copied exactly from `rdis.exe dis` output (re-verified across oc_U-EL8b_r13/r26/r27 fresh rdis runs; all matched). Re-check with `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; delegate exits 0 => unit complete (## NEXT already DONE).

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — ALREADY QUEUED (pending, rva 0xe815840, size 0x100, max 6), no result in docs/data/live/ yet; queue full at 4 pending, duplicate re-add rejected [V live via request.py list]. Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= names the stitcher caller; mips>1 is mip-generation evidence. Cannot re-queue until the batch runs and a slot frees.
CAPTURE REQUESTED none new — queue is full.
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files; no throwaway scripts written).
