## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #1)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line (YES only if every pending part of the item is [V]-proven, else NO plus the single blocking fact).

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Image base (PE OptionalHeader, read-only parse): 0x140000000.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [V live] read-only live capture (docs/data/live/), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis output) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped or summarized offsets.

## Sources read (NOT re-run / NOT re-derived)
- docs/progress/oc_U-L8b.md: PNG/TGA decoder unit — unrelated to atlases (PNG entry 0x777ed0, IHDR 0x781550; no atlas, mip-generation or compression code there); no offsets from it belong to this unit.
- docs/progress/oc_U-EL8b_r1..r46: prior retries; [V] rows below re-verified against the exe with rdis before quoting (registration, blit, createTexture/resizeTexture decode, mip keys, numMips store, format fallback, BC strings unreferenced, sub_4e05e50/texgroup_load/texload decode, live capture census). Carried rows were verify_oc.py-clean (mismatch=0) in r46 and are re-quoted identically.
- docs/data/live/mc_root_4e05e50_callers.txt [V live]: read IN FULL this session — sub_4e05e50 entry capture, hits=150 samples=32, CALLER ret=0x1289496 in all 32 samples.
- docs/data/live/l8b_texcreate_record.txt [V live]: read IN FULL this session — TextureD3D12::create 0xe81bf30 entry capture, hits=150 samples=24, all ret=0xE814560.
- docs/data/live/_status.txt: DONE targets only mc_root_4e05e50_callers (hits=150 samples=32) and l8b_texcreate_record (hits=150 samples=24); NO l8b_resizetex_slot31 result.
- python tools/livecap/request.py result <name>: checked l8b_resizetex_slot31, sub_1289440_callers, er5_clone_4c8a5b0, oc_u_er6_light_desc — all "no result yet (orchestrator has not run it)".
- python tools/livecap/request.py list: 4 pending (queue full: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) — no new L8b capture can be added this unit.
- docs/BGFX_MAP.md sections 6h (PointLightShadowTextureAtlas 0xbb682b0; MaterialTerrainTextureAtlas string only), 1105/1107 (task 16 TerrainAtlasBlit, functor vtable 0xF43E9E0, blit body sub_bc02090), 1502/1511/1512 (resizeTexture slot 31 = (handle,w,h,numMips,numLayers); createTexture slot 26 -> TextureD3D12::create 0xe81bf30), 1812 (texture record +0xAF requested format, +0xB0 actual format, +0xB1 numMips), 6o/448 (D3D format name table incl. BC3/BC7, data only), 782 (sampler bit 10 = mip FILTER, usage not generation) [I].

## Part 1 — Atlases (terrain, items): registration PROVEN, texture creation NOT located

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| "TerrainAtlas" string | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name (len 0xC, `0x186f73f mov qword ptr [rbp+0x108],0xC`) loaded for registration idx 6 (`0x186f767 mov r9d,6`) via sub_1870de0 inside sub_186e6a0 | [V] |
| "ItemAtlas" string | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name (len 9, `0x186f80a mov qword ptr [rbp+0x118],9`) loaded for registration idx 7 (`0x186f832 mov r9d,7`) via sub_1870de0 — item atlas NAME exists in the exe | [V] |
| registered obj +0 | obj +0 | 8 (qword store) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 inside sub_1870de0 | [V] |
| registered obj +8 | obj +8 | 4 (dword store) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | code 0x1870e70 | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocs a 0x48-byte object | [V] |
| sub_1870de0 alloc call | code 0x1870e75 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk (data_f99ffa0) for the 0x48-byte registered object | [V] |
| registry sentinel scan | registry +0..end | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | scans fixed registry dword array for 0x2A '*' sentinel; index bounded `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29` -> 0..41 | [V] |
| registration dispatcher | code 0x186e6a0 | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop allocs named objects via sub_1870de0 (TerrainAtlas 6, ItemAtlas 7, AnimatedAtlas 8, BlockThumbnailAtlas 0x26); NO createTexture/resizeTexture call anywhere inside sub_186e6a0 (0x186e6a0..0x18706a0) | [V] |
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
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte store) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written inside TextureD3D12::create; dl loaded `0xe81c0cd movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte store) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table `0xe81c022 movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed fallback 0x42 | code 0xe81c12b | 1 (byte cmp) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
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
| BC texture compression/decompression code | bc-code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed format 0x1C [V live] | [V] |

## Part 4 — creation entries, TexturePtr chain, and live capture census

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture slot 26 -> TextureD3D12::create | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture has 0 static callers (reached indirect via [vptr+0xD0] slot 26); live callers ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 | code 0xe815840 | - | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode [V via rdis dis 0xe815840: sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in]: RCX=this renderer `0xe81586c  mov r14,rcx`; DX=handle `0xe81586f  mov [rbp+0x8E],dx`; R8D=width->ebx `0xe815869  mov ebx,r8d`; R9D=mips->edi `0xe815866`; stack word mips `0xe815980  movzx r13d,word ptr [rbp+0x108]`; stack byte layers `0xe815988  movzx r12d,byte ptr [rbp+0x100]`; renderer+0xBDE178 handle array `0xe815876  lea rsi,[rcx+0xBDE178]`; resizeTexture(handle,w,h,mips,layers), mips can be specified; 0 static xrefs; never observed live | [V] |
| TextureD3D12::create callers | xref TextureD3D12::create callers | - | xref | - | only createTexture and resizeTexture slot 31 (0xe815840) call TextureD3D12::create [V via xref]; xref hit at 0xe8403d0+0xaa5b verified as a vtable DATA store `0xe8eaf2b  mov [rax+0x40],rcx`, not a call | [V] |
| sub_4e05e50 entry | code 0x4e05e50 | - | sub header | sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in | TexturePtr ensure-loaded/upload bridge; 0 static xrefs in (reached at runtime via the indirect call from sub_12893d0) | [V] |
| sub_4e05e50 arg map | regs | - | 0x4e05e6b / 0x4e05e6e | `0x4e05e6b  mov rsi,rdx` / `0x4e05e6e  mov rdi,rcx` | rdi = a0 (TexturePtr-like object), rsi = out pointer | [V] |
| pointee refcount add | pointee +8 | 4 (lock cmpxchg) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref loop on refcount at *(a0+0x10)+8 | [V] |
| pointee destroy | pointee +0 | 8 (qword call) | 0x4e05ed8 | `0x4e05ed8  call qword ptr [0xF99FFA0]` | destroys pointee via vtable-dtor thunk when refcount hits 0 | [V] |
| desc-region call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 (dragon-layer upload bridge) called with rcx = a0+0x58 (texture description region) — ensure-loaded/upload, NOT atlas creation | [V] |
| result call | out | - | 0x4e05f85 | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 called on the produced result | [V] |
| sub_12893d0 entry | code 0x12893d0 | - | sub header | sub_12893d0 [0x12893d0..0x12895d3) size 0x203 13 xrefs in | TexturePtr release/collect: walks a 0x18-strided entry array [r13..r14); entry object pointer at [r13+8] | [V] |
| sub_12893d0 array walk stride | elem stride 0x18 | - | 0x1289420 | `0x1289420  add r13,0x18` | next array entry | [V] |
| sub_12893d0 entry add-ref | entry obj +8 | 4 (lock cmpxchg) | 0x1289447 | `0x1289447  lock cmpxchg [rcx+8],edx` | add-ref object at [r13+8] | [V] |
| sub_12893d0 entry copy | entry | 16 (movups) | 0x128944e | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of array entry | [V] |
| LIVE: indirect call to sub_4e05e50 | ret=0x1289496 | - | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | fall-through `0x1289496  nop` = ret=0x1289496 seen in mc_root_4e05e50_callers.txt line 3 for ALL 32 samples; runtime target resolves to sub_4e05e50 on this path | [V live] |
| sub_12893d0 release sites | pointee/entry | 8 (qword call) | 0x12894b3 | `0x12894b3  call qword ptr [0xF99FFA0]` (same instr text at 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612) | seven more release/decrement calls on old pointees and array entries | [V] |
| sub_12893d0 refcount dec strong | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | strong refcount decrement; destroy at zero | [V] |
| sub_12893d0 refcount dec weak | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | weak-count decrement | [V] |
| sub_12893d0 count output | out +0 | 8 (qword store) | 0x12895a8 | `0x12895a8  mov [rsi],r12` | stores collected count | [V] |
| LIVE object +0x00 | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | - | `00007ff6a8215838` at obj+0 — vtable/type pointer into ANOTHER MODULE, not this exe (imagebase 0x140000000; 0x7FF6A8215838 - 0x140000000 = 0x6BE6A8215838, far beyond any exe section; .text range per livecap tool is 0x1000..0x0F000000) [V live + PE base] | [V live] |
| LIVE object +0x10 | obj +0x10 | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | - | `00000390be9102a0` pointee texture object pointer; sub_4e05e50 reads [rdi+0x10] at `0x4e05e8c  mov rdx,[rdi+0x10]` | [V live] |
| LIVE desc bytes | desc at RCX+0x64..+0x77 | 5 dwords | mc_root_4e05e50_callers.txt hit=1 RCX | - | `1c000000 01000000 01000000 01000000 74657800` = format 0x1C (R8G8B8A8_UNORM uncompressed), three 1-dword dims (1/1/1), debug tag "tex\0" [V live] | [V live] |
| LIVE caller | ret=0x1289496 | - | mc_root_4e05e50_callers.txt line 3 | - | `CALLER ret=0x1289496 first_hit=1` — all 150 hits / 32 samples share ONE caller: sub_12893d0 [V live] | [V live] |
| texgroup_load | code 0x5421c90 | - | 0x5421dec | `0x5421dec  call 0x5477A30` | looks up a texture by name via sub_5477a30 (rcx = rsi+0x248); add-ref `0x5421e0a  lock inc dword ptr [rcx+8]` on the looked-up texture ((ret+0x68)+8) | [V] |
| sub_5477a30 callers | xref sub_5477a30 callers | - | xref | - | exactly 2 static callers: sub_541f8f0 (+0xc7d) and texgroup_load 0x5421c90 (+0x190f) — no stitcher looks up atlas textures by name | [V] |
| texload | code 0x58a1310 | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list ([rbx+0x160..0x168)); per-rect floats `0x58a1450  movss xmm3,[rcx+8]` — atlas UV CONSUMPTION, not creation | [V] |
| l8b_texcreate_record census | capture 0xe81bf30 | - | `CALLER ret=0xE814560` line 3 | - | 24 samples at TextureD3D12::create entry 0xe81bf30; format 0x1C at RCX+0x40 (`1c000000`, line 4); R8 names "Texture: 2815"/"Texture: 2799" UTF-16, URLs "ui://./hbui/index.html"; NO atlas names; no compressed formats; all numMips=1 [V live] | [V live] |
| createtexture_callers census | capture 0xe8143c0 | - | `CALLER ret=0xBC6A2C8` line 3 | - | 150 hits / 32 samples at createTexture 0xe8143c0; all callers ret=0xBC6A2C8 command interpreter; R8 description objects format 0x1C with UI/screen texture names only; ZERO atlas names [V live] | [V live] |

## What this retry tried (new angles, per the 2026-11-22 orchestrator hint)

1. Checked `python tools/livecap/request.py result` for l8b_resizetex_slot31, sub_1289440_callers, er5_clone_4c8a5b0, oc_u_er6_light_desc: ALL "no result yet (orchestrator has not run it)". _status.txt shows no new L8b target as DONE beyond mc_root_4e05e50_callers and l8b_texcreate_record. No additional [V live] data available this unit.
2. `python tools/livecap/request.py list`: queue is FULL (4 pending: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) — no duplicate or new L8b capture can be added this unit (`request.py add` rejects with "4 requests already pending"). l8b_resizetex_slot31 (rva 0xe815840 = resizeTexture slot 31 entry, size 0x100, max 6) remains pending and is the highest-value ask: resizeTexture is the only creation entry never observed (0 static xrefs); its ret= would name the stitcher caller; mips>1 would be mip-generation evidence; atlas-name params would close the terrain/item-atlas creation rows.
3. New static angle — forward trace via registry globals: `rdis imm 0x128D3D68` -> 0 hits; `rdis imm 0x128D3D80` -> 0 hits (no instruction in .text carries those globals as an immediate). Static forward trace already exhausted: sub_186e6a0 contains no createTexture/resizeTexture call [V]; sub_1042320's full 1778-line listing creates no atlas texture [V]; no located reader/stitcher consumes the registered objects [V].
4. Re-decoded the live object from mc_root_4e05e50_callers.txt hit=1 this session (read the capture file in full): RCX+0x00 = vtable pointer `00007ff6a8215838` -> provably ANOTHER MODULE (not this exe) [V live]; RCX+0x10 = pointee `00000390be9102a0` [V live]; description bytes `1c000000 01000000 01000000 01000000 74657800` at RCX+0x64..+0x77 = format 0x1C, dims 1/1/1, tag "tex\0" [V live]; other hits carry "legs"/"spear"-class tags — all UI/misc 1x1 uncompressed textures, never TerrainAtlas/ItemAtlas, never numMips>1 [V live]. Confirms sub_4e05e50 is the TexturePtr ensure-loaded path (decode done in r46 Part 4), NOT an atlas creator.

## Interpretation

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731 lea rax,[0xF55CDD3]; 0x186f767 mov r9d,6`) and "ItemAtlas" idx 7 (`0x186f7fc lea rax,[0xF55CDE0]; 0x186f832 mov r9d=7`) inside sub_186e6a0 via sub_1870de0 (0x48-byte object, name at obj+0 `0x1870ec5 mov [rsi],rax`, idx at obj+8 `0x1870ecb mov [rsi+8],eax`), triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 (`0x104237e call 0x186E6A0`) and initStep1 sub_8f6810 (+0x61d). The ORIGINAL item claim "no item atlas string/code in the exe" is REFUTED: "ItemAtlas" string + registration are [V]. Registration stores only name+idx.
- But no located consumer/stitcher builds the atlas texture: sub_186e6a0 contains no createTexture/resizeTexture call [V]; sub_1042320's full listing creates no atlas texture and references no atlas string [V]; sub_1870de0's xrefs are all registration-side [V].
- Every texture-creation entry point enumerated and negative [V + V live x3]: createTexture slot 26 (0xe8143c0 -> TextureD3D12::create 0xe81bf30; TextureD3D12::create has exactly 2 static callers: createTexture + resizeTexture); live census all format 0x1C, numMips=1, no atlas names across mc_root_4e05e50_callers + l8b_texcreate_record + createtexture_callers. resizeTexture slot 31 (0xe815840, takes mips) is the only entry never observed — capture l8b_resizetex_slot31 pending, no result yet, queue full.
- sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release (decoded verbatim, Part 4), NOT creators [V]. texgroup_load (lookup via sub_5477a30, only 2 callers [V via xref]) and texload (0x30-strided rect walk, UV consumption only [V]) connect to TexturePtr as lookup/consume, not creation.
- Live object +0x00 pointer provably outside this exe (imagebase 0x140000000; 0x7FF6A8215838 - 0x140000000 = 0x6BE6A8215838 not an exe RVA) [V live + PE base] -> the atlas stitcher/decode is external-module or data-driven and cannot be closed from this exe statically.
- Mip generation provably absent [V via xref refs=[]; no mip-gen task; numMips=1 for all live creations [V live]; numMips only stored at +0xB1 `0xe81c0d1 mov [rdi+0xB1],dl` [V]]. BC1/BC3/BC7/DXT1-DXT5 compression provably absent [V via xref refs=[]; uncompressed-only create path `0xe81c12b cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077 mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]].

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas texture-creation STITCHER is not located in this exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, 0xe8143c0 -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, 0xe815840, takes mips) with atlas params; registration stores only name+idx [V]; all creation entry points enumerated negative statically and in 3 live captures (all format 0x1C, numMips=1, no atlas names) [V + V live]; live objects carry a +0x00 pointer provably in ANOTHER MODULE (exe imagebase 0x140000000; 0x00007FF6A8215838 outside the image) [V live], so the stitcher/decode is external-module or data-driven and cannot be closed from this exe statically. CLOSES? YES only when the stitcher call site is found — pending the l8b_resizetex_slot31 capture result (queue full, no new request possible this unit) or an orchestrator decision to mark atlas creation external/data-driven.

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; the line after `## NEXT` is DONE only when delegate exits 0. All quoted `0xRVA  instr` lines copied verbatim from rdis output (carried from r46, verify_oc-clean mismatch=0); live values cited as [V live] with file + hit/line.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — ALREADY QUEUED (pending, rva 0xe815840 = resizeTexture slot 31 entry, size 0x100, max 6), NO result yet in docs/data/live/ (_status.txt lacks it). Cannot re-queue (duplicate) and queue is full (4 pending). Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= names the stitcher caller; mips>1 is mip-generation evidence; atlas-name params close the terrain/item-atlas creation rows.
CAPTURE REQUESTED sub_1289440_callers — ALREADY QUEUED (pending, rva 0x1289440), no result yet. Why: names sub_12893d0's runtime caller to complete the texgroup_load/texload -> TexturePtr -> sub_4e05e50 chain (static xrefs/imm to sub_1289440 are 0; note 0x1289440 is loc_1289440 inside sub_12893d0, not a separate function entry — an entry-RVA capture would need sub_12893d0 itself).
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files read this session; no throwaway scripts written).
