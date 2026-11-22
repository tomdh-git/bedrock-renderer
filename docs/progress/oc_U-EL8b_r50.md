## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression — RETRY #1

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?]) + final `CLOSES?` line (YES only if every pending part of the item line is [V]-proven, else NO plus the single blocking fact).

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
PE image base 0x140000000. LIVE image (this session): pid 13452 base 0x7FF7A59C0000 size 0x1383e000 (livemem status) → live image range [0x7FF7A59C0000, 0x7FF7B91FE000) [V live].
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [V live] read-only live capture (docs/data/live/), [I] inferred (say from what), [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address (R/W base+disp) | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis output) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped or summarized offsets.

## Sources read (NOT re-run / NOT re-derived)
- docs/progress/oc_U-EL8b_r1..r48: prior retries; carried [V] rows below re-verified against the exe with rdis / xref / ripscan before quoting.
- docs/data/live/mc_root_4e05e50_callers.txt [V live]: read IN FULL this session — sub_4e05e50 entry capture, hits=150 samples=32, CALLER ret=0x1289496 in all 32 samples (line 3); RCX object bytes at line 4.
- docs/data/live/l8b_texcreate_record.txt [V live]: read IN FULL this session — TextureD3D12::create 0xe81bf30 entry capture, hits=150 samples=24, all ret=0xE814560 (line 3).
- docs/data/live/_status.txt: DONE targets mc_root_4e05e50_callers (hits=150 samples=32), l8b_texcreate_record (hits=150 samples=24); NO l8b_resizetex_slot31 result.
- python tools/livecap/request.py result <name>: checked l8b_resizetex_slot31, sub_1289440_callers, er5_clone_4c8a5b0, oc_u_er6_light_desc — all "no result yet (orchestrator has not run it)".
- python tools/livecap/request.py list: 4 pending (queue full) — no new L8b capture can be added this unit.
- docs/BGFX_MAP.md: 6h (PointLightShadowTextureAtlas 0xbb682b0), 1105/1107 (task 16 TerrainAtlasBlit, functor vtable 0xF43E9E0, blit body sub_bc02090), 1502/1511 (slot 31 = resizeTexture(handle,w,h,mips,layers); slot 26 = createTexture -> TextureD3D12::create 0xe81bf30), 1812 (texture record +0xAF requested format, +0xB0 actual format, +0xB1 numMips), 6o/448 (D3D format name table incl. BC3/BC7, data only), 782 (sampler bit 10 = mip FILTER, usage not generation) [I].

## Part 1 — Atlases (terrain, items): registration PROVEN, texture creation NOT located

| name | rva or offset | size | read/store address (R/W base+disp) | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| "TerrainAtlas" string | str data 0xF55CDD3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name; len 0xC `0x186f73f mov qword ptr [rbp+0x108],0xC`; registration idx 6 `0x186f767 mov r9d,6`; `0x186f76d call 0x1870DE0` inside sub_186e6a0 | [V] |
| "ItemAtlas" string | str data 0xF55CDE0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name; len 9 `0x186f80a mov qword ptr [rbp+0x118],9`; idx 7 `0x186f832 mov r9d,7`; `0x186f838 call 0x1870DE0` inside sub_186e6a0 — item-atlas NAME + registration DO exist in the exe (original claim "no item atlas string/code" REFUTED) | [V] |
| atlas-string xref negatives | xref str | - | xref | - | xref.py str "TerrainAtlas" → refs only (0x186f731, 0x186e6a0); "ItemAtlas" → refs only (0x186f7fc, 0x186e6a0) — no other code references either atlas name [V via xref, re-verified this session] | [V] |
| registered obj +0 | obj +0 | 8 (qword store) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 inside sub_1870de0 | [V] |
| registered obj +8 | obj +8 | 4 (dword store) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | code 0x1870e70 | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocs a 0x48-byte registered object | [V] |
| sub_1870de0 alloc call | code 0x1870e75 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk (data_f99ffa0) for the 0x48-byte registered object | [V] |
| registry sentinel scan | registry dword array | 4 (dword cmp) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | scans fixed registry dword array for 0x2A '*' free-slot sentinel; index bounded `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29` -> slots 0..41 | [V] |
| registration dispatcher | code 0x186e6a0 | - | 0x186f75d/0x186f828 | `0x186f75d  mov rcx,[rbp+0x628]`; `0x186f76d call 0x1870DE0`; `0x186f838 call 0x1870DE0` | sub_186e6a0 [0x186e6a0..0x1870357), size 0x1cb7, 2 static xrefs in; registers atlases via sub_1870de0 (rcx = the manager object); FULL LISTING CHECKED THIS SESSION: NO call 0xE8143C0/0xE815840/0xE81BF30/0xBC73BF0/0xC296B50/0xBC73770 and no atlas-creation code anywhere in 0x186e6a0..0x1870357 | [V] |
| sub_186e6a0 static callers | xref callers | - | xref | - | exactly 2 static callers: sub_8f6810 (+0x61d, initStep1) and sub_1042320 (+0x1d1, ServerLevelLoad) [V via xref.py callers] | [V] |
| per-level manager alloc | code 0x104235c | 4 (dword imm) | 0x104235c | `0x104235c  mov edx,0x78` | ServerLevelLoad (sub_1042320) allocates a 0x78-byte manager object per level load; passes it as `this` to sub_186e6a0 (`0x104237e call 0x186E6A0`) and calls sub_1870de0 directly for idx 0x28 (`0x10423c7 mov r9d,0x28`) / 0x29 (`0x1042465 mov r9d,0x29`) — manager is PER-LEVEL, not a global, so no global registry-reader stitcher exists to find | [V] |
| ServerLevelLoad no atlas creation | code 0x1042320 | - | 0x104237e | `0x104237e  call 0x186E6A0` | sub_1042320 [0x1042320..0x1044320] triggers atlas registration but creates NO atlas texture: no call 0xE8143C0/0xE815840/0xE81BF30 and no TerrainAtlas/ItemAtlas string in its full listing | [V] |
| TerrainAtlasBlit task name | str data 0xF539A0B | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0; blit body sub_bc02090 (BGFX_MAP 1105/1107) — atlas BLIT (consumption), not creation | [V] |
| MaterialTerrainTextureAtlas string | str data 0xF55CE1B | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| PointLightShadowTextureAtlas registration | code 0xbb682b0 | - | 0xbb682b0 | - | L8 BGFX_MAP.md:336: PointLightShadowTextureAtlas registered at 0xbb682b0 — a THIRD atlas; only its registration point known, no creation located for it either (context: atlas creation generally not found in exe) | [I] |
| terrain-atlas texture creation | terrain-atlas-creation | - | none | - | not located: xref "TerrainAtlas" → registration sites only; no createTexture/resizeTexture call tied to TerrainAtlas statically or in any live capture | [?] |
| item-atlas texture creation | item-atlas-creation | - | none | - | not located: xref "ItemAtlas" → registration sites only; no createTexture/resizeTexture call tied to ItemAtlas; no ItemAtlasBlit task | [?] |

## Part 2 — mipmaps

| name | rva or offset | size | read/store address (R/W base+disp) | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xF5515C8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xF52FE18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xF5636E5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xF593BE9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte store) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored inside TextureD3D12::create; dl loaded `0xe81c0cd movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte store) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table `0xe81c022 movzx eax,word ptr [rax+r13*2+0x15AC]`; BGFX_MAP 1812: +0xAF requested format, +0xB0 actual format, +0xB1 numMips - skip | [V] |
| uncompressed fallback 0x42 | code 0xe81c12b | 1 (byte cmp) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | mip-generation | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-generation Blit task; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I via BGFX_MAP 782]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression

| name | rva or offset | size | read/store address (R/W base+disp) | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xF84AD1C | - | none | - | BC1/DXT1 format name in .rdata; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xF84AAF8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] [V via xref this session] | [?] |
| BC7 string | str data 0xF84A930 | - | none | - | BC7 format name; xref.py refs=[] [V via xref this session] | [?] |
| DXT1-DXT5 strings | str data 0xF7DDD18, 0xF7D3D04, 0xF7D6AC8, 0xEF3FFEC-0xEF40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 names; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xF58FF5A | - | 0x766542, 0x77b498 | - | referenced from 0x765330 and PNG decoder 0x777ed0 — PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xF5E339B | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): PNG/zlib decompression from the PNG decoder dispatcher, not BC compression | [V] |
| D3D format name table | data 0x56E3A12..0x56E42F6 | - | - | - | data table incl. BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | bc-code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed `0xe81c12b cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077 mov [rdi+0xB0],r13b` [V]; live census all-uncompressed format 0x1C [V live]. Compressed texture DATA could still be loaded from disk (createTexture takes a memory blob; format read from the bimg header) — data-driven, not a code gap provable from this exe | [I] |

## Part 4 — creation entries, TexturePtr chain, and live capture census

| name | rva or offset | size | read/store address (R/W base+disp) | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture slot 26 -> TextureD3D12::create | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture has 0 static callers (reached indirect via [vptr+0xD0] slot 26); live callers ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 | code 0xe815840 | - | sub header | sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in: RCX=this renderer `0xe81586c mov r14,rcx`; DX=handle `0xe81586f mov [rbp+0x8E],dx`; R8D=width->ebx `0xe815869 mov ebx,r8d`; R9D=mips->edi `0xe815866 mov edi,r9d`; resizeTexture(handle,w,h,mips,layers), mips can be specified; 0 static xrefs; never observed live | [V] |
| TextureD3D12::create callers | xref TextureD3D12::create callers | - | xref | - | only createTexture and resizeTexture slot 31 (0xe815840) call TextureD3D12::create [V via xref]; xref hit at 0xe8403d0+0xaa5b verified as a vtable DATA store `0xe8eaf2b mov [rax+0x40],rcx`, not a call | [V] |
| sub_4e05e50 entry | code 0x4e05e50 | - | sub header | sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in | TexturePtr ensure-loaded/upload bridge; 0 static xrefs in (reached at runtime via the indirect call from sub_12893d0) | [V] |
| sub_4e05e50 arg map | regs | - | 0x4e05e6b / 0x4e05e6e | `0x4e05e6b  mov rsi,rdx` / `0x4e05e6e  mov rdi,rcx` | rdi = a0 (TexturePtr-like object), rsi = out pointer | [V] |
| desc-region call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 (dragon-layer upload bridge) called with rcx = a0+0x58 (texture description region) — ensure-loaded/upload, NOT atlas creation | [V] |
| result call | out | - | 0x4e05f85 | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 called on the produced result | [V] |
| sub_12893d0 entry | code 0x12893d0 | - | sub header | sub_12893d0 [0x12893d0..0x12895d3) size 0x203 13 xrefs in | TexturePtr release/collect: walks a 0x18-strided entry array [r13..r14); entry object pointer at [r13+8] | [V] |
| LIVE indirect call to sub_4e05e50 | ret=0x1289496 | - | mc_root_4e05e50_callers.txt line 3 | `CALLER ret=0x1289496 first_hit=1` — all 150 hits / 32 samples share ONE caller: sub_12893d0 [V live] | [V live] |
| sub_12893d0 release sites | pointee/entry | 8 (qword call) | 0x12894b3 | `0x12894b3  call qword ptr [0xF99FFA0]` (same instr text at 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612) | seven more release/decrement calls on old pointees and array entries | [V] |
| sub_12893d0 refcount dec strong | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | strong refcount decrement; destroy at zero | [V] |
| texgroup_load | code 0x5421c90 | - | 0x5421dec | `0x5421dec  call 0x5477A30` | looks up a texture by name via sub_5477a30 (rcx = rsi+0x248); add-ref `0x5421e0a  lock inc dword ptr [rcx+8]` on the looked-up texture — lookup only, not creation | [V] |
| sub_5477a30 callers | xref sub_5477a30 callers | - | xref | - | exactly 2 static callers: sub_541f8f0 (+0xc7d) and texgroup_load 0x5421c90 (+0x190f) — no stitcher looks up atlas textures by name | [V] |
| texload | code 0x58a1310 | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list ([rbx+0x160..0x168)); per-rect floats `0x58a1450  movss xmm3,[rcx+8]` — atlas UV CONSUMPTION, not creation | [V] |

## Part 5 — LIVE census (read this session) + NEW: live object +0x00 is in ANOTHER MODULE

| name | rva or offset | size | read/store address (R/W base+disp) | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| l8b_texcreate_record census | capture 0xE81BF30 | - | `CALLER ret=0xE814560` line 3 | docs/data/live/l8b_texcreate_record.txt line 3: 24 samples at TextureD3D12::create entry 0xe81bf30; format 0x1C at RCX+0x40 (`1c000000` line 4); R8 names "Texture: 2815"/"Texture: 2799" UTF-16, URLs "ui://./hbui/index.html"; NO atlas names; no compressed formats; all numMips=1 [V live] | [V live] |
| createtexture_callers census | capture 0xe8143c0 | - | `CALLER ret=0xBC6A2C8` line 3 | 150 hits / 32 samples at createTexture 0xe8143c0; all callers ret=0xBC6A2C8 command interpreter; R8 description objects format 0x1C with UI/screen texture names only; ZERO atlas names [V live] | [V live] |
| mc_root_4e05e50_callers census | capture 0x4e05e50 | - | `CALLER ret=0x1289496` line 3 | docs/data/live/mc_root_4e05e50_callers.txt line 3: 150 hits / 32 samples, all caller ret=0x1289496 (= sub_12893d0) [V live] | [V live] |
| LIVE object +0x00 vtable ptr | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt line 4 RCX | capture bytes at RCX+0x00: `385821A8F67F0000` -> qword 0x00007FF6A8215838 (same value in hits 1, 2, 8, ... 15; RCX=3908FFDE900 hit=1) | vtable/type pointer at object +0, read from live capture memory | [V live] |
| LIVE exe image range | image base | - | python tools/sigs/livemem.py status | pid 13452 base 0x7FF7A59C0000 size 0x1383e000 Minecraft.Windows.exe 1.26.62.01 -> live image range [0x7FF7A59C0000, 0x7FF7B91FE000) [V live] | [V live] |
| obj+0 -> ANOTHER MODULE | obj +0x00 | - | - | 0x00007FF6A8215838 < base 0x7FF7A59C0000 -> pointer at object +0 is OUTSIDE this exe image: ANOTHER MODULE; livemem read of 0x00007FF6A8215838 returned "unreadable" (livemem restricted to exe/heap ranges) — the value itself stands from the capture [V live] | [V live] |
| LIVE desc bytes | desc at RCX+0x60..+0x77 | 4+4+4+4 dwords | mc_root_4e05e50_callers.txt line 4 | +0x60 `1C000000` format 0x1C (R8G8B8A8_UNORM, uncompressed); +0x64/+0x68/+0x6C dims 1/1/1; +0x70 `74657800` tag "tex\0" [V live] | [V live] |

## Interpretation

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731 lea rax,[0xF55CDD3]`; `0x186f767 mov r9d,6`) and "ItemAtlas" idx 7 (`0x186f7fc lea rax,[0xF55CDE0]`; `0x186f832 mov r9d,7`) inside sub_186e6a0 via sub_1870de0 (0x48-byte object, name at obj+0 `0x1870ec5 mov [rsi],rax`, idx at obj+8 `0x1870ecb mov [rsi+8],eax`), triggered per level load by sub_1042320 (ServerLevelLoad) -> sub_186e6a0 (`0x104237e call 0x186E6A0`) and by initStep1 sub_8f6810 (+0x61d). ServerLevelLoad allocates a per-level 0x78 manager (`0x104235c mov edx,0x78`) — not a global — so no global registry-reader stitcher exists to find [V].
- The ORIGINAL item claim "no item atlas string/code in the exe" is REFUTED: "ItemAtlas" string + registration are [V]. Registration stores only name+idx.
- But no located consumer/stitcher builds the atlas texture: sub_186e6a0 contains NO createTexture/resizeTexture/BGFX create call [V — my own grep of the full 0x186e6a0..0x1870357 listing this session]; sub_1042320's full listing creates no atlas texture and references no atlas string [V]; atlas strings referenced only at registration [V]; sub_1870de0's xrefs are all registration-side [V].
- Every texture-creation entry point enumerated and negative [V + V live x3]: createTexture slot 26 (0xe8143c0 -> TextureD3D12::create 0xe81bf30; TextureD3D12::create has exactly 2 static callers: createTexture + resizeTexture); live census all format 0x1C, numMips=1, no atlas names across mc_root_4e05e50_callers + l8b_texcreate_record + createtexture_callers. resizeTexture slot 31 (0xe815840, takes mips) is the only creation entry never observed — capture l8b_resizetex_slot31 pending, no result yet, queue full.
- sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release (decoded verbatim), NOT creators [V]. texgroup_load (lookup via sub_5477a30, only 2 callers [V via xref]) and texload (0x30-strided rect walk, UV consumption only [V]) connect to TexturePtr as lookup/consume, not creation.
- Mip generation provably absent [V via xref refs=[]; no mip-gen task; numMips=1 for all live creations [V live]; numMips only stored at +0xB1 `0xe81c0d1 mov [rdi+0xB1],dl` [V]]. BC1/BC3/BC7/DXT1-DXT5 compression CODE provably absent [V via xref refs=[]; uncompressed-only create path `0xe81c12b cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077 mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]]. Compressed texture DATA may still be loaded from disk [I].
- NEW THIS SESSION: the live texture-request object's +0x00 vtable pointer 0x00007FF6A8215838 is provably OUTSIDE this exe (capture value [V live] vs live image range [0x7FF7A59C0000, 0x7FF7B91FE000) from `livemem status` [V live]) -> another module. Direct livemem read of 0x00007FF6A8215838 returned "unreadable" (livemem restricted to exe/heap ranges; no module-enumeration command exists), so the module NAME/RVA cannot be determined from this side [I]. The stitcher/decode is external-module or data-driven and cannot be closed from this exe statically.
- Static analysis exhausted for this item: rdis dis/fn, xref str/callers, ripscan, imm, grep of full listings, forward trace via the per-level manager — no new static lead remains.

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas texture-creation STITCHER is not located in this exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, 0xe8143c0 -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, 0xe815840, takes mips) with atlas params; registration stores only name+idx [V]; all creation entry points enumerated negative statically and in 3 live captures (all format 0x1C, numMips=1, no atlas names) [V + V live]; live objects carry a +0x00 vtable pointer provably in ANOTHER MODULE (capture value 0x00007FF6A8215838 vs exe image [0x7FF7A59C0000, 0x7FF7B91FE000) from livemem status) [V live], so atlas creation/decode is external-module or data-driven and cannot be closed from this exe statically. CLOSES? YES only when the stitcher call site is found — pending the l8b_resizetex_slot31 capture result (queue full, no new request possible this unit) or an orchestrator decision to mark atlas creation external/data-driven (MIRROR_SKIP).

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; the line after `## NEXT` is DONE only when delegate exits 0. All quoted `0xRVA  instr` lines copied verbatim from rdis output (carried rows were verify_oc-clean mismatch=0 in r46/r48 and are re-quoted identically); live values cited as [V live] with file + hit/line.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — ALREADY QUEUED (pending, rva 0xe815840 = resizeTexture slot 31 entry, size 0x100, max 6), NO result yet in docs/data/live/ (_status.txt lacks it). Cannot re-queue (duplicate) and queue is full (4 pending: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc). Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= names the stitcher caller; mips>1 is mip-generation evidence; atlas-name params close the terrain/item-atlas creation rows.
CAPTURE REQUESTED sub_1289440_callers — ALREADY QUEUED (pending, rva 0x1289440), no result yet. Why: names sub_12893d0's runtime caller to complete the texgroup_load/texload -> TexturePtr -> sub_4e05e50 chain (static xrefs/imm to sub_1289440 are 0; note 0x1289440 is loc_1289440 inside sub_12893d0, not a separate function entry — an entry-RVA capture would need sub_12893d0 itself).
Livemem capability gap: direct read of external-module address 0x00007FF6A8215838 returns "unreadable" (livemem restricted to exe/heap ranges); no module-enumeration command available, so the module NAME of 0x7FF6A8215838 cannot be determined from this side [I]. A module-enumerate/arbitrary-read livemem capability would let me name the stitcher's module.
Helper scripts: none (all verbatim lines taken directly from rdis dis output, xref/ripscan output, and live capture files read this session; no throwaway scripts written; scratch listing docs/progress/oc_U-EL8b_sub186e6a0.list kept as working evidence).
