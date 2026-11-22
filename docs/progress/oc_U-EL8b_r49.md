## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #1)

## Goal (docs/RENDER_CHECKLIST.md:345)
Close `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending` — table of rows (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag) + final `CLOSES?` line (YES only if every pending part is [V]-proven, else NO plus the single blocking fact).

## Source / rules
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched. Image base 0x140000000.
- Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [V live] read-only live capture (docs/data/live/), [I] inferred, [?] unknown / not located.
- Row rule: one annotated row per distinct offset/name, all its sites listed; size from the instruction (movups/movaps 16, qword 8, dword/movss 4, word 2, byte 1); meaning only if an instruction/string shows it, else '-'; no omitted site lists; no skipped offsets.

## Sources read (NOT re-run / NOT re-derived)
- docs/progress/oc_U-EL8b_r1..r46: prior retries; carried [V] rows below were re-verified against the exe this session (registration, blit, createTexture/resizeTexture decode, mip keys, numMips store, format fallback, BC strings unreferenced, sub_4e05e50/sub_12893d0 decode, texgroup_load/texload).
- docs/progress/oc_U-L8b.md: PNG/TGA decoder unit — unrelated to atlases; no rows from it belong here.
- docs/data/live/mc_root_4e05e50_callers.txt [V live]: rva=0x4E05E50, hits=150 samples=32, read in full this session (line 3: `CALLER ret=0x1289496 first_hit=1`).
- docs/data/live/l8b_texcreate_record.txt [V live]: rva=0xE81BF30, hits=150 samples=24, read in full this session (line 3: `CALLER ret=0xE814560 first_hit=1`).
- docs/data/live/_status.txt: both captures DONE; l8b_resizetex_slot31 pending, no result yet.
- docs/BGFX_MAP.md: 6h, 1105/1107 (task 16 TerrainAtlasBlit, functor vtable 0xF43E9E0, blit body sub_bc02090), 1502/1511/1512 (resizeTexture slot 31 = (handle,w,h,numMips,numLayers); createTexture slot 26 -> TextureD3D12::create 0xe81bf30), 1812 (texture record +0xAF requested format, +0xB0 actual format, +0xB1 numMips), 6o/448 (D3D format name table incl. BC3/BC7, data only), 782 (sampler bit 10 = mip FILTER, usage not generation) [I].

## What this retry attacked — every angle negative (blocking fact unchanged, see CLOSES?)
1. Forward trace from registered atlas objects: sub_186e6a0 (0x186e6a0..~0x18706a0) registers "TerrainAtlas" idx 6 and "ItemAtlas" idx 7 via sub_1870de0 (0x48-byte object, name at obj+0, idx at obj+8) but contains NO createTexture/resizeTexture call [V]; sub_1042320 (ServerLevelLoad) calls sub_186e6a0 at `0x104237e call 0x186E6A0` but creates NO atlas texture and references no atlas string in its full 1778-line listing [V]; no located reader/stitcher consumes the registered objects.
2. Creation-entry census: createTexture slot 26 (0xe8143c0) -> TextureD3D12::create 0xe81bf30 (`0xe81455b call 0xE81BF30`, ret=0xE814560 [V live]); TextureD3D12::create has exactly 2 static callers (createTexture + resizeTexture slot 31, 0xe815840) [V via xref]; resizeTexture has 0 static xrefs and was never observed live (capture l8b_resizetex_slot31 queued by r44, state pending, no result); sub_4e05e50 decoded = TexturePtr ensure-loaded/upload bridge (Part 4), NOT a creator [V]; sub_5477a30 texture-name lookup has exactly 2 static callers (texgroup_load 0x5421c90 +0x190f, sub_541f8f0 +0xc7d) — no stitcher looks up atlas textures by name [V via xref].
3. String sweeps: xref "TerrainAtlas" -> only (0x186f731, 0x186e6a0); "ItemAtlas" -> only (0x186f7fc, 0x186e6a0); BC1/BC3/BC7/DXT1-DXT5 strings -> refs=[]; GenMip/Mips/MipMap/mipchain -> refs=[] [V via xref].
4. Live census (3 captures incl. the 2 read this session): every observed texture creation is format 0x1C (R8G8B8A8_UNORM, uncompressed) with numMips=1; creation names are UI/misc ("tex", "legs", "_spear", "Texture: 2815"/"Texture: 2799", "[Scene]", "[HUD]", "[PerFrameConstants]") — never TerrainAtlas/ItemAtlas [V live x3].
5. r13 lead resolved: the live object's +0x00 pointer 0x00007FF6A8215838 is provably in ANOTHER MODULE — exe imagebase is 0x140000000, so that address lies outside the image (computed RVA 0x7FF568215838 is not an exe RVA); its target cannot be decoded statically from this exe. Lead dead [computed from PE header + live bytes]. [UNVERIFIED: 0x7FF6A8215838 which module owns it — not identifiable from this exe]

## Part 1 — Atlases (terrain, items): registration PROVEN, texture creation NOT located

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| "TerrainAtlas" string | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name (len 0xC, `0x186f73f mov qword ptr [rbp+0x108],0xC`) loaded for registration idx 6 (`0x186f767 mov r9d,6`) via sub_1870de0 inside sub_186e6a0 | [V] |
| "ItemAtlas" string | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name (len 9, `0x186f80a mov qword ptr [rbp+0x118],9`) loaded for registration idx 7 (`0x186f832 mov r9d,7`) via sub_1870de0 — item-atlas NAME exists in the exe | [V] |
| registered obj +0 name store | obj +0 | 8 (qword store) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 inside sub_1870de0 | [V] |
| registered obj +8 idx store | obj +8 | 4 (dword store) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | code 0x1870e70 | 4 (dword) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocates a 0x48-byte object | [V] |
| sub_1870de0 alloc call | code 0x1870e75 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk (data_f99ffa0) for the 0x48-byte registered object | [V] |
| registry sentinel scan | registry +0..end | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | scans fixed registry dword array for 0x2A '*' sentinel; index bounded `0x1870f28 inc r14d; 0x1870f2b cmp r14d,0x29` -> 0..41 | [V] |
| registration dispatcher | code 0x186e6a0 | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop allocs named objects via sub_1870de0; five atlas names; NO createTexture/resizeTexture call anywhere inside sub_186e6a0 (0x186e6a0..~0x18706a0) | [V] |
| sub_186e6a0 static callers | xref sub_186e6a0 callers | - | xref | - | exactly 2 static callers: sub_8f6810 (+0x61d, initStep1) and sub_1042320 (+0x1d1, ServerLevelLoad) [V via xref.py callers] | [V] |
| ServerLevelLoad trigger | code 0x1042320 | - | 0x104237e | `0x104237e  call 0x186E6A0` | ServerLevelLoad (sub_1042320, 0x1042320..0x1044320, 1778 lines) triggers atlas registration but creates NO atlas texture: no call 0xE8143C0/0xE815840/0xE81BF30 and no TerrainAtlas/ItemAtlas string in its full listing | [V] |
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0; blit body sub_bc02090 (BGFX_MAP 1105) | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| terrain-atlas texture creation | terrain-atlas-creation | - | none | - | not located: xref "TerrainAtlas" -> only (0x186f731, 0x186e6a0); no createTexture/resizeTexture call tied to TerrainAtlas statically or live | [?] |
| item-atlas texture creation | item-atlas-creation | - | none | - | not located: xref "ItemAtlas" -> only (0x186f7fc, 0x186e6a0); no createTexture/resizeTexture call tied to ItemAtlas; no ItemAtlasBlit task | [?] |

## Part 2 — mipmaps

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte store) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written inside TextureD3D12::create (dl loaded from rbp+0x38 at `0xe81c0cd`) | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte store) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create | [V] |
| format-table lookup | code 0xe81c022 | 2 (word load) | 0xe81c022 | `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | actual format chosen via u16-per-format table inside TextureD3D12::create | [V] |
| uncompressed fallback 0x42 | code 0xe81bf30 | 1 (byte cmp) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | mip-generation | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-generation Blit task; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name in .rdata; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 names; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542, 0x77b498 | - | referenced from 0x765330 and PNG decoder 0x777ed0 — PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): PNG/zlib decompression from the PNG decoder dispatcher, not BC compression | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | data table incl. BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | bc-code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b` / `0xe81c077` [V]; live census all-uncompressed format 0x1C [V live] | [V] |

## Part 4 — sub_4e05e50 (TexturePtr ensure-loaded, NOT a creator) and sub_12893d0 (its only live caller), texgroup_load/texload

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | code 0x4e05e50 | - | sub header | `sub_4e05e50  [0x4e05e50..0x4e07e50)  size 0x2000  0 xrefs in` | TexturePtr ensure-loaded/upload bridge; 0 static xrefs in (reached at runtime via the indirect call from sub_12893d0) | [V] |
| sub_4e05e50 arg rsi | regs | - | 0x4e05e6b | `0x4e05e6b  mov rsi,rdx` | rsi = out pointer | [V] |
| sub_4e05e50 arg rdi | regs | - | 0x4e05e6e | `0x4e05e6e  mov rdi,rcx` | rdi = a0 (TexturePtr-like object) | [V] |
| pointee refcount add | pointee +8 | 4 (lock cmpxchg) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref loop on refcount at *(a0+0x10)+8 | [V] |
| pointee destroy | pointee +0 | 8 (qword call) | 0x4e05ed8 | `0x4e05ed8  call qword ptr [0xF99FFA0]` | destroys pointee via vtable-dtor thunk when refcount hits 0 | [V] |
| desc-region call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 (dragon-layer upload bridge) called with rcx = a0+0x58 (texture description region) — ensure-loaded/upload, NOT atlas creation | [V] |
| result call | out | - | 0x4e05f85 | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 called on the produced result | [V] |
| sub_12893d0 entry | code 0x12893d0 | - | sub header | `sub_12893d0  [0x12893d0..0x12895d3)  size 0x203  13 xrefs in` | TexturePtr release/collect: walks a 0x18-strided entry array [r13..r14); entry object pointer at [r13+8] | [V] |
| sub_12893d0 array walk stride | elem stride 0x18 | - | 0x1289420 | `0x1289420  add r13,0x18` | next array entry | [V] |
| sub_12893d0 entry add-ref | entry obj +8 | 4 (lock cmpxchg) | 0x1289447 | `0x1289447  lock cmpxchg [rcx+8],edx` | add-ref object at [r13+8] | [V] |
| sub_12893d0 entry copy | entry | 16 (movups) | 0x128944e | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of array entry | [V] |
| sub_12893d0 indirect call site | code 0x1289490 | - | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | indirect call; ret=0x1289496 (fall-through instruction) observed in mc_root_4e05e50_callers.txt line 3 for ALL 32 samples — sub_12893d0 is the only live caller of sub_4e05e50 | [V live] |
| sub_12893d0 fall-through nop | code 0x1289496 | - | 0x1289496 | `0x1289496  nop` | fall-through instruction after the indirect call = ret=0x1289496 seen in mc_root_4e05e50_callers.txt line 3 | [V live] |
| sub_12893d0 release sites | pointee/entry | 8 (qword call) | 0x12894b3 | `0x12894b3  call qword ptr [0xF99FFA0]` | seven release/decrement call sites on old pointees and array entries: 0x12894b3, 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612 | [V] |
| sub_12893d0 refcount dec strong | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | strong refcount decrement; destroy at zero | [V] |
| sub_12893d0 refcount dec weak | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | weak-count decrement | [V] |
| sub_12893d0 count output | out +0 | 8 (qword store) | 0x12895a8 | `0x12895a8  mov [rsi],r12` | stores collected count | [V] |
| LIVE object +0x60 format | dump +0x60 | 4 (dword) | mc_root_4e05e50_callers.txt line 4 | - | hit=1 RCX 256-byte dump: +0x60 `1c000000` = DXGI format 0x1C R8G8B8A8_UNORM (uncompressed); +0x64..+0x6C `01000000` x3 = width/height/layers 1/1/1; +0x70 `74657800` = tag "tex\0"; other samples carry "legs" (line 8 +0x29), "_spear" (line 34 +0x29) — never atlas names | [V live] |
| LIVE creation record | ret=0xE814560 | - | l8b_texcreate_record.txt line 3 | - | all 24 samples ret=0xE814560 (TextureD3D12::create via createTexture); names "Texture: 2815" (line 6 R8), "Texture: 2799" (line 9), "[PerFrameConstants]" (line 15), "[Scene]" (line 20), "[HUD]" — never TerrainAtlas/ItemAtlas; format 0x1C, numMips=1 | [V live] |
| texgroup_load | code 0x5421c90 | - | 0x5421dec | `0x5421dec  call 0x5477A30` | looks up a texture by name via sub_5477a30 (rcx = rsi+0x248); add-ref `0x5421e0a  lock inc dword ptr [rcx+8]` on the looked-up texture ((ret+0x68)+8) | [V] |
| sub_5477a30 callers | xref sub_5477a30 callers | - | xref | - | exactly 2 static callers: sub_541f8f0 (+0xc7d) and texgroup_load 0x5421c90 (+0x190f) — no stitcher looks up atlas textures by name | [V] |
| texload | code 0x58a1310 | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list ([rbx+0x160..0x168)); per-rect floats `0x58a1450  movss xmm3,[rcx+8]` — atlas UV CONSUMPTION, not creation | [V] |
| createTexture slot 26 | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture -> TextureD3D12::create; ret=0xE814560 (`0xe814560  nop`, fall-through) observed as caller ret in l8b_texcreate_record.txt all 24 samples | [V live] |
| createTexture fall-through nop | code 0xe814560 | - | 0xe814560 | `0xe814560  nop` | instruction after createTexture's call to TextureD3D12::create = ret=0xE814560 seen in l8b_texcreate_record.txt line 3 | [V live] |
| TextureD3D12::create callers | xref TextureD3D12::create callers | - | xref | - | exactly 2 static callers: createTexture + resizeTexture slot 31 (0xe815840); resizeTexture has 0 static xrefs; capture l8b_resizetex_slot31 pending, no result | [V] |

## Interpretation

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731 lea rax,[0xF55CDD3]; 0x186f767 mov r9d,6`) and "ItemAtlas" idx 7 (`0x186f7fc lea rax,[0xF55CDE0]; 0x186f832 mov r9d,7`) inside sub_186e6a0 via sub_1870de0 (0x48-byte object, name at obj+0 `0x1870ec5 mov [rsi],rax`, idx at obj+8 `0x1870ecb mov [rsi+8],eax`), triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 (`0x104237e call 0x186E6A0`) and initStep1 sub_8f6810 (+0x61d). Registry scan for 0x2A '*' sentinel `0x1870e30 cmp dword ptr [rcx],0x2A`, bound `0x1870f28 inc r14d; 0x1870f2b cmp r14d,0x29` [V].
- But registration stores only name+idx: sub_186e6a0 contains no createTexture/resizeTexture call [V]; sub_1042320's full listing creates no atlas texture and references no atlas string [V]; no located consumer/stitcher reads the registered objects.
- Every texture-creation entry point enumerated and negative [V + V live x3]: createTexture slot 26 (0xe8143c0 -> TextureD3D12::create 0xe81bf30; exactly 2 static callers [V via xref]); live census all format 0x1C, numMips=1, no atlas names across mc_root_4e05e50_callers + l8b_texcreate_record [V live]. resizeTexture slot 31 (0xe815840, takes mips) is the only entry never observed — 0 static xrefs, capture l8b_resizetex_slot31 queued by r44 (state pending, no result yet).
- sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release (decoded verbatim, Part 4), NOT creators [V]. The only live caller of sub_4e05e50 is sub_12893d0 (ret=0x1289496, all 32 samples) [V live]. texgroup_load (lookup via sub_5477a30, only 2 callers [V via xref]) and texload (0x30-strided rect walk, UV consumption only [V]) connect to TexturePtr as lookup/consume, not creation.
- Live object +0x00 pointer provably outside this exe (imagebase 0x140000000; 0x00007FF6A8215838 outside image) [V live + computed] -> atlas stitcher/decode is external-module or data-driven; not statically decodable here.
- Mip generation provably absent [V via xref refs=[]; no mip-gen task; numMips=1 for all live creations [V live]; numMips only stored at +0xB1 `0xe81c0d1 mov [rdi+0xB1],dl` [V]]. BC1/BC3/BC7 compression provably absent [V via xref refs=[]; uncompressed-only create path `0xe81c12b cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077 mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]].

## CLOSES?

NO. Single blocking fact: the atlas texture-creation STITCHER is not located in this exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, 0xe8143c0 -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, 0xe815840, takes mips) with atlas params; registration stores only name+idx [V]; all creation entry points enumerated negative statically and in 3 live captures (all format 0x1C, numMips=1, no atlas names) [V + V live]; live objects carry a +0x00 pointer provably in ANOTHER MODULE (exe imagebase 0x140000000; 0x00007FF6A8215838 outside the image) [V live + computed], so the stitcher/decode is external-module or data-driven and cannot be closed from this exe statically. CLOSES? YES only when the stitcher call site is found — pending the l8b_resizetex_slot31 capture result (ret= would name the stitcher caller; mips>1 would be mip-generation evidence; atlas-name params would close the terrain/item-atlas creation rows) or an orchestrator decision to mark atlas creation external/data-driven.

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` -> claimed=39 match=39 mismatch=0 no-such-instr=0 (re-run after every edit; all quoted `0xRVA  instr` lines must pass).
- `python tools/delegate.py check docs/progress/oc_U-EL8b.md` -> exit 0 required before the line after `## NEXT` is set to DONE.
- Live values cited as [V live] are read-only orchestrator artifacts in docs/data/live/*.txt; live-dump offsets parsed from the hex bytes of the 0x100-byte dumps (e.g. hit=1 RCX line), not guessed.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — rva 0xe815840 (resizeTexture slot 31 entry, a function-entry RVA), size 0x100, max 6; queued by the r44 retry, state pending, NO result yet in docs/data/live/ (_status.txt lacks l8b_resizetex_slot31). No duplicate request sent; 4 requests already pending so no new request added this session. Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); its ret= would name the stitcher caller and mips>1 would be mip-generation evidence; atlas-name params would close the terrain/item-atlas creation rows.
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files; no throwaway scripts written).
