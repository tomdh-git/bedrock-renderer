## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (FINAL)

Source checklist line (docs/RENDER_CHECKLIST.md line 345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] = seen in disassembly (RVA cited, verbatim line quoted) or read-only live capture (file:line cited); [I] = inferred (say from what); [?] = unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed in that row (merge sites, no duplicate offset rows, no skipped offsets); columns: name | offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis/live capture) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups/movaps 16, qword 8, dword/movss 4, word 2, byte 1). Carried rows from oc_U-EL8b_r1..r29 are NOT re-derived; quoted instr lines are kept verbatim and re-checked with verify_oc.py.

## Inputs reviewed (carried context, NOT re-derived)

oc_U-EL8b_r1..r29: atlas registration [V] (TerrainAtlas idx 6, ItemAtlas idx 7 via sub_186e6a0/sub_1870de0), TerrainAtlasBlit task [V], createTexture/resizeTexture/TextureD3D12::create decode [V], mip keys [V], numMips +0xB1 [V], format fallback 0x42 [V], BC strings unreferenced [V], sub_4e05e50/texgroup_load/texload/TexturePtr decode [V], live census [V live]. Nothing here is guessed.
Input reviewed: docs/progress/oc_U-L8b.md (PNG/TGA decoder unit — unrelated to atlases; no atlas or compression code there).
BGFX_MAP.md sections carried: 1511/1512 createTexture slot 26 = 0xe8143c0, resizeTexture slot 31 = 0xe815840 (handle,w,h,mips,layers); 1812 TextureD3D12::create 0xe81bf30 writes +0xB0 actual format, +0xB1 numMips, +0x42 uncompressed fallback; 1105/1107 TerrainAtlasBlit task 16, functor vtable 0xF43E9E0, _Do_call sub_bc02090; 6o/448 D3D format name table incl. BC3/BC7 (data only); 6z/6z-2 texture record format/flag bits.

## NEW THIS SESSION — the two available live captures read FIRST (per orchestrator hint)

### docs/data/live/mc_root_4e05e50_callers.txt (rva=0x4E05E50, kind=regs, size=0x100; hits=150 samples=32, _status.txt DONE)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 live caller chain | CALLER ret=0x1289496 | - | mc_root_4e05e50_callers.txt:3 | `CALLER ret=0x1289496 first_hit=1` | sub_4e05e50 entered ONLY indirectly; ret=0x1289496 is the return address inside its sole caller; identical for all 32 samples [V live] | [V live] |
| sub_4e05e50 indirect call site / sub_12893d0 release old pointee | call site in sub_12893d0 (+ sibling release sites) | 8 (qword) | 0x1289490 (siblings 0x12894b3, 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612) | `0x1289490  call qword ptr [0xF99FFA0]` | statically [0xF99FFA0]=sub_eea6040 thunk; at runtime this site tail-calls sub_4e05e50 via rax=vtable[1] (`0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]` / `0x128948d  mov rdx,rbx` set up rax); fall-through `0x1289496  nop` = ret=0x1289496 seen for ALL 32 samples [V live mc_root_4e05e50_callers.txt:3, docs/progress/oc_U-EL8b_sub1289480.list lines 4-8] | [V live] |
| indirect caller of sub_4e05e50 NAMED | sub_12893d0 | - | sub_12893d0 [0x12893d0..0x12895d3) size 0x203 13 xrefs in | - | sub_12893d0 is the only live caller of sub_4e05e50 (ret=0x1289496 every sample); sub_4e05e50 has 0 static xrefs in [V] | [V live] |
| object +0x00 pointer at sub_4e05e50 entry (cross-module) | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes 385821A8F67F0000 at RCX+0 = 0x00007FF6A8215838 | first qword of objects passed to sub_4e05e50 is a pointer OUTSIDE the exe image (exe base 0x7ff7a59c0000, end 0x7ff7bd2fe000 from livemem status) -> ANOTHER MODULE [V live] | [V live] |
| module/RVA of 0x00007FF6A8215838 | - | - | livemem read + vt | `python tools/sigs/livemem.py read 0x00007FF6A8215838 0x40` -> unreadable; `vt` -> "vtable None" | module/RVA not identifiable from the static exe image (no module enumeration); read unreadable in this snapshot [V live] / [?] | [V live] / [?] |
| sub_4e05e50 entry | sub header | - | sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in | - | TexturePtr ensure-loaded/release (refcount + desc upload); NOT a creator [V carried] | [V] |
| sub_4e05e50 arg map | regs | - | 0x4e05e6b / 0x4e05e6e | `0x4e05e6b  mov rsi,rdx` / `0x4e05e6e  mov rdi,rcx` | rdi=rcx=a0 TexturePtr-like object (+0x10 pointee, +0x58 desc region); rsi=rdx=output [V carried] | [V] |
| sub_4e05e50 pointee add-ref | pointee +8 | 4 (dword cmpxchg) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref loop on refcount at *(a0+0x10)+8 [V carried] | [V] |
| sub_4e05e50 desc-region upload call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 dragon-layer upload bridge called with rcx=a0+0x58 description region — upload/ensure-loaded, NOT atlas creation [V carried] | [V] |
| sub_12893d0 entry | sub header | - | sub_12893d0 [0x12893d0..0x12895d3) size 0x203 13 xrefs in | - | TexturePtr release/collect; walks a 0x18-strided entry array [V] | [V] |
| sub_12893d0 add-ref | entry obj +8 | 4 (dword cmpxchg) | 0x1289447 | `0x1289447  lock cmpxchg [rcx+8],edx` | CAS incrementing refcount dword at object+8 [V carried] | [V] |
| sub_12893d0 16-byte object copy | entry | 16 (movups) | 0x128944e | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of the texture object (entry obj +0) [V carried] | [V] |
| sub_12893d0 refcount dec strong | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | destroy pointee when refcount reaches zero [V carried] | [V] |
| sub_12893d0 refcount dec weak | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | second (weak) count decrement [V carried] | [V] |
| sub_12893d0 0x18-strided array walk | array walk stride | 0x18 (stride) | 0x1289560 | `0x1289560  add rbx,0x18` | walks a 0x18-strided array releasing [rbx+0x10] and [rbx+8] entries [V carried] | [V] |
| sub_12893d0 count output | out +0 count | 8 (qword) | 0x12895a8 | `0x12895a8  mov [rsi],r12` | stores collected count r12 into the output pointer [V carried] | [V] |
| sub_12893d0 caller chain | sub_6632bf0 caller chain | - | sub_6632bf0 "Deferred Texture Transactions" | - | sub_6632bf0 reads [rcx+0x18] pointer pair (16 bytes) then `0x6632c55 call 0x12893D0` [V carried] — deferred-release path, not creation | [V] |
| texgroup_load | texgroup_load entry | - | 0x5421dec | `0x5421dec  call 0x5477a30` | looks up a texture by name in the texture table via sub_5477a30; 7 static xrefs in — TexturePtr CONSUMER (lookup), not creator [V carried] | [V] |
| texgroup_load add-ref | texture +8 | 4 (dword) | 0x5421e0a | `0x5421e0a  lock inc dword ptr [rcx+8]` | add-ref on the looked-up texture [V carried] | [V] |
| texload | texload entry | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list calling sub_5417950 per rect, tracks min/max UV at [rbx+0x6C]/[rbx+0x78]; 2 static xrefs in — atlas UV CONSUMPTION, not creation [V carried] | [V] |
| texload rect read | 4 (movss) | 0x58a1450 | `0x58a1450  movss xmm3,[rcx+8]` | per-rect float read in the rect walk [V carried] | [V] |
| sub_5477a30 callers | sub_5477a30 callers | - | `0x541f8f0 +0xc7d`, `0x5421c90 +0x190f` | - | ONLY two static callers: texgroup_load (+0x190f) and sub_541f8f0 (+0xc7d) — no stitcher looks up atlas textures by name [V via xref] | [V] |

### docs/data/live/l8b_texcreate_record.txt (rva=0xE81BF30 TextureD3D12::create entry, kind=regs, size=0x100; hits=150 samples=24, _status.txt DONE)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TextureD3D12::create entry capture header | capture | - | l8b_texcreate_record.txt:3 | `CALLER ret=0xE814560 first_hit=1` | 24 samples at TextureD3D12::create entry 0xe81bf30; ret=0xE814560 is inside createTexture 0xe8143c0 (`0xe81455b  call 0xE81BF30`) [V live] | [V live] |
| desc+0x40 actual format | desc +0x40 | 4 (dword) | l8b_texcreate_record.txt line 4 | bytes 1C000000 at RCX+0x40 (line 4) | format 0x1C = uncompressed BGRA; observed on every sample [V live] | [V live] |
| R8 texture name sample 1 | R8 string | - | l8b_texcreate_record.txt line 4 | 54006500780074007500720065003A0020003200380031003500 = UTF-16 "Texture: 2815" | dynamic render-target name; ZERO atlas names across all samples [V live] | [V live] |
| R8 texture name sample 2 | R8 string | - | l8b_texcreate_record.txt line 8 | ...3200370039003900... = UTF-16 "Texture: 2799" | second dynamic texture name; not an atlas [V live] | [V live] |
| numMips across all live creations | desc mips field | 1 (byte) | l8b_texcreate_record.txt lines 4-27 | - | every observed creation has numMips=1; no compressed format; no atlas name [V live] | [V live] |
| TextureD3D12::create record writes | record +0xB0 / +0xB1 | 1/1 (byte) | 0xe81c077 / 0xe81c0d1 | `0xe81c077  mov [rdi+0xB0],r13b` `0xe81c0d1  mov [rdi+0xB1],dl` | actual format byte + numMips byte stored inside TextureD3D12::create [V carried] | [V] |

### What I tried that failed (new angles, all negative — NOT repeated static proof)

- livemem read/vt of 0x00007FF6A8215838 (obj +0x00 of sub_4e05e50's live objects): unreadable / "vtable None" [V live row above] — module/RVA of the cross-module pointer cannot be identified from this exe snapshot.
- Capture l8b_resizetex_slot31 (rva 0xe815840, resizeTexture slot 31): ALREADY QUEUED PENDING [V live via request.py list]; queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) so not re-added; no result file in docs/data/live/ yet. Its ret= would name the stitcher caller and mips>1 would be mip-generation evidence.
- Capture l8b_sub2fe440_consumer (rva 0x2FE440): PLANNED, NOT QUEUED (queue full) — would observe the registered TerrainAtlas/ItemAtlas object (name at +0, idx at +8) consumed by sub_2fe440 right after sub_1870de0 inside sub_186e6a0.
- Static stitcher search exhausted (carried [V]): sub_186e6a0 contains no createTexture(0xe8143c0)/resizeTexture(0xe815840) call [V]; registration object immediately consumed by sub_2fe440 (cleanup-only: frees description buffers +0xF8/+0xB0/+0x98, refcount-release walk, object freed by sub_e935700 edx=0x138) [V carried]; sub_1042320 post-registration only re-enters sub_1870de0 with idx 0x28/0x29 load-phase names then cleanup+free, NO atlas texture creation [V carried]; sub_18718d0/sub_186dac0 name lookup never receives "TerrainAtlas"/"ItemAtlas" (referenced ONLY inside sub_186e6a0) [V]/[I carried]; sub_5477a30 lookup callers = texgroup_load + sub_541f8f0 only, no stitcher [V via xref].
- Result: sub_4e05e50/sub_12893d0 decode as TexturePtr release/ensure-loaded (upload bridge to sub_bc41420), NOT atlas/mip/compression creation — this angle does NOT close the item. All live creations are format 0x1C uncompressed numMips=1 with non-atlas names [V live x2 captures].

## Part 1 — Atlases (terrain, items): registration [V]; texture creation NOT located

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name (len 0xC) loaded before the sub_1870de0 call; registered idx 6 (r9d=6) inside sub_186e6a0 [V] | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name (len 9) loaded before sub_1870de0; registered idx 7 (r9d=7) inside sub_186e6a0 — item atlas EXISTS as a registered name [V] | [V] |
| registered object +0 name ptr | obj +0 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 inside sub_1870de0; new object head-inserted into the registry list [V] | [V] |
| registered object +8 index dword | obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 [V] | [V] |
| sub_1870de0 alloc size imm | sub_1870de0 alloc imm | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocates a 0x48-byte registered object via sub_eea6040 [V] | [V] |
| sub_1870de0 alloc call | sub_1870de0 alloc call | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object [V] | [V] |
| registry sentinel scan | registry sentinel | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | manager dword array scanned for 0x2A '*' sentinel; slot bound `0x1870f28 inc r14d` / `0x1870f2b cmp r14d,0x29` (slots 0..41) [V] | [V] |
| registry slot index write | registry slot write | 4 (dword) | 0x1870f40 | `0x1870f40  mov [r15],r14d` | sub_1870de0 writes registration slot index into the registry slot (replacing the 0x2A '*' sentinel) — stores INDEX, not object pointer [V] | [V] |
| sub_186e6a0 registration dispatcher | sub_186e6a0 dispatcher | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 (0x186e6a0..0x18706a0, size 0x2000, 2 xrefs in) registers named objects via sub_1870de0 (TerrainAtlas 6, ItemAtlas 7, AnimatedAtlas 8, BlockThumbnailAtlas 0x26); NO createTexture/resizeTexture call anywhere inside [V] | [V] |
| sub_186e6a0 static callers | sub_186e6a0 callers | xref | xref.py callers | - | exactly 2 static callers: initStep1 sub_8f6810 (+0x61d) and ServerLevelLoad sub_1042320 (+0x1d1) [V via xref.py callers] | [V] |
| ServerLevelLoad registration call | ServerLevelLoad call | - | 0x104237e | `0x104237e  call 0x186E6A0` | sub_1042320 (ServerLevelLoad) triggers atlas registration via sub_186e6a0; loads "ResourceLoadType::ServerLevelLoad" `0x104239b lea rax,[0xF602326]` [V] | [V] |
| initStep1 caller of sub_186e6a0 | initStep1 caller | - | 0x8f6810+0x61d | - | second caller of sub_186e6a0; writes "initStep1"; registers objects [V carried] | [V] |
| TerrainAtlasBlit task name | TerrainAtlasBlit task | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name inside 0xbb418d0; functor vtable 0xF43E9E0 (task 16 per BGFX_MAP.md 1105), slot 2 = sub_bc02090 — the atlas BLIT/consumer, not its creator [V] | [V] |
| BlitUncompressed key | BlitUncompressed ref | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed [V] | [V] |
| atlas texture creation (terrain + item) | not located: atlas creation | none | - | - | NOT located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)], "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to either atlas; no ItemAtlasBlit task exists [?] | [?] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) [?] | [?] |
| item atlas name usage (data only) | item +0x78 | - | `0x5755283` (+ siblings 0x575530a/0x5755473/0x57554a4/0x57554d5/0x5755509/0x575551e) | `0x5755283  call 0x7F1A0` | item-definition parser resolves each item's atlas texture name ("atlas.items" `0x575527c lea rdx,[0xF550917]`, "atlas.terrain", "textures/items/compass_atlas" `0x5755303 lea rdx,[0xF55CCD6]`, lodestonecompass/recovery_compass/watch_atlas) and stores it at item+0x78 via sub_7f1a0 — referenced as DATA only, never as createTexture arguments [V] | [V] |

## Part 2 — mipmaps: material mip params exist; generation not located

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 [V] | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 [V] | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 [V] | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 [V] | [V] |
| texture record +0xB1 numMips | texture record +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored inside TextureD3D12::create sub_e81bf30; dl loaded `0xe81c0cd movzx edx,byte ptr [rbp+0x38]` [V] | [V] |
| texture record +0xB0 actual format | texture record +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte stored inside create; chosen via u16-per-format table `0xe81c022 movzx eax,word ptr [rax+r13*2+0x15AC]` [V] | [V] |
| uncompressed fallback 0x42 | uncompressed fallback | 1 (byte) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type [V] | [V] |
| mip generation function | not located: mip generation | none | - | - | NOT located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-gen Blit task [V]; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression: provably absent in the exe

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1/BC3/BC7/DXT1-DXT5 strings | str data BC/DXT strings | none | none | - | str data 0xf84ad1c (BC1), 0xf84aaf8 (BC3), 0xf84a930 (BC7), 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8 (DXT1-DXT5), 0xef3ffec-0xef40010; all xref.py refs=[] [?] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | ref 0x766542 | - | str data 0xf58ff5a; references in 0x765330 and PNG decoder 0x777ed0 are PNG/zlib decompression error paths, not BC texture compression [V] | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): image (PNG zlib) decompression, called from PNG decoder dispatcher [V] | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP.md 6o/448); data table only, no compression code path [I] | [I] |
| BC texture compression code | not located: BC code | none | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live] | [V] |

## Part 4 — creation-entry census (static + live)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture -> TextureD3D12::create call | 0xe81455b | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (slot 26 per BGFX_MAP.md 1512) builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture has 0 static callers (reached indirect via [vptr+0xD0] slot 26); live callers ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry decode | 0xe815866 | - | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode [V via rdis dis 0xe815840: sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in]: RCX=this renderer `0xe81586c mov r14,rcx`; DX=handle `0xe81586f mov [rbp+0x8E],dx`; R8D=width->ebx `0xe815869 mov ebx,r8d`; R9D=mips->edi `0xe815866 mov edi,r9d`; resizeTexture(handle,w,h,mips,layers) per BGFX_MAP.md 1505/1512; mips can be specified on resize; 0 static xrefs; never observed live [V] | [V] |
| TextureD3D12::create callers | TextureD3D12::create callers | xref | `0xe8143c0 0x2e1`, `0xe815840 0x3ae` | - | only createTexture and resizeTexture call TextureD3D12::create; xref hit at 0xe8403d0+0xaa5b verified as vtable DATA store `0xe8eaf2b mov [rax+0x40],rcx`, not a call [V] | [V] |
| l8b_texcreate_record census | l8b_texcreate_record census | capture | l8b_texcreate_record.txt:3-27 | `CALLER ret=0xE814560` line 3 — 24 samples at TextureD3D12::create entry 0xe81bf30; format 0x1C at desc+0x40 (`1C000000` at RCX+0x40, line 4); R8 names "Texture: 2815"/"Texture: 2799" UTF-16; NO atlas names; no compressed formats; all numMips=1 [V live] | [V live] |
| createtexture_callers census | createtexture_callers census | capture | createtexture_callers.txt:3 | `CALLER ret=0xBC6A2C8` line 3 — 150 hits / 32 samples at createTexture 0xe8143c0; all callers ret=0xBC6A2C8 command interpreter; R8 description objects format 0x1C with UI/screen texture names only; ZERO atlas names [V live] | [V live] |

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas texture-creation STITCHER — the code that builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, `0xe81455b call 0xE81BF30` -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, `0xe815866 mov edi,r9d`, takes mips) with atlas params — is NOT located in this exe:

- Registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731 lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc lea rax,[0xF55CDE0]`) inside sub_186e6a0 via sub_1870de0 (0x48-byte object; name at obj+0 `0x1870ec5 mov [rsi],rax`; idx at obj+8 `0x1870ecb mov [rsi+8],eax`; sentinel scan slots 0..41 `0x1870e30 cmp dword ptr [rcx],0x2A`, bound `0x1870f28 inc r14d` / `0x1870f2b cmp r14d,0x29`), triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 (`0x104237e call 0x186E6A0`) and initStep1 sub_8f6810 (+0x61d). BUT the registered object is immediately consumed by sub_2fe440 (cleanup-only, decoded [V carried]) and freed by sub_e935700 — discarded, not retained; sub_1042320's post-registration code creates NO atlas texture [V carried]; sub_186e6a0 contains no createTexture/resizeTexture call [V].
- Creation entry points fully enumerated and negative: createTexture census (live x2: l8b_texcreate_record + createtexture_callers — all format 0x1C uncompressed, numMips=1, names "Texture: 2799/2815"/UI/entity, ZERO atlas names [V live]); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture slot 31 has 0 static xrefs and is never observed live (capture l8b_resizetex_slot31 PENDING, queue full); sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release (live caller chain ret=0x1289496 = `0x1289496 nop` after `0x1289490 call qword ptr [0xF99FFA0]` [V live]) — NOT creation; sub_5477a30 lookup callers = texgroup_load + sub_541f8f0 only, no stitcher [V via xref]; resource-by-name lookup sub_18718d0 never receives the atlas names [V]/[I].
- Cross-module pointer: objects passed to sub_4e05e50 carry +0x00 = 0x00007FF6A8215838 [V live docs/data/live/mc_root_4e05e50_callers.txt hit=1], outside the exe image (base 0x7ff7a59c0000, end 0x7ff7bd2fe000 [V live status]) -> another module; livemem read/vt of that address unreadable [V live]. Atlas creation likely lives in another module or is data-driven — not closable from static analysis of this exe alone.
- Atlas usage is data-driven [V]: item parser stores atlas names ("atlas.items", "atlas.terrain", "textures/items/compass_atlas", lodestonecompass/recovery_compass/watch_atlas) at item+0x78 via sub_7f1a0 (`0x5755283 call 0x7F1A0` and siblings) [V]; the names are referenced as data only, never as createTexture arguments [V live census].
- Mip generation [?]: no GenMip/Mips/MipMap/mipchain code or task [V via xref]; numMips=1 for all live creations [V live]; numMips only stored at +0xB1 `0xe81c0d1 mov [rdi+0xB1],dl` [V] — generator not located, likely external/data-driven.
- Compression [V provably ABSENT]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077 mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live].

YES would require every pending part of the item line [V]-proven; atlas stitcher and mip generator are not located, so CLOSES? = NO. Re-open on the l8b_resizetex_slot31 capture result (ret= names the stitcher caller; mips>1 is mip evidence) or identification of the module at 0x00007FF6A8215838.

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; only when delegate exits 0 set the line after `## NEXT` to DONE.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — rva 0xe815840 (resizeTexture slot 31), size 0x100, max 6, ALREADY QUEUED PENDING [V live via request.py list]; queue is full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), so do NOT re-add until a slot frees. Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= names the stitcher caller; mips>1 would be mip-generation evidence for the atlas. createTexture slot 26 already captured (l8b_texcreate_record): all numMips=1, format 0x1C uncompressed, no atlas names [V live].
CAPTURE REQUESTED l8b_sub2fe440_consumer — PLANNED, NOT QUEUED (queue full): rva 0x2FE440, size 0x100, max 6, why "L8b: observe the registered TerrainAtlas/ItemAtlas object (name at +0, idx at +8) consumed by sub_2fe440 right after sub_1870de0 inside sub_186e6a0; confirm cleanup vs any handle/texture handle store; ret= names the sub_186e6a0 call site". Re-add next unit once the queue drains.
Helper scripts: none (all verbatim lines taken directly from rdis dis output, docs/progress/oc_U-EL8b_sub1289480.list, and live capture files; no throwaway scripts written).
