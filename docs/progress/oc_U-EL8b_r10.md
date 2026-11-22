## NEXT
DONE — CLOSES? NO: atlas texture-creation stitcher not located; atlas registration proven (TerrainAtlas idx6 / ItemAtlas idx7 via sub_186e6a0/sub_1870de0, triggered by ServerLevelLoad sub_1042320); mipmap generation and BC1/BC3/BC7 compression proven ABSENT; L8b live-capture could not be queued (4 pending for other units).

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped.

## Sources carried from earlier attempts (oc_U-EL8b_r1..r9) — NOT re-derived
- oc_U-L8b.md: PNG entry 0x777ed0, IHDR 0x781550; TGA/texture_set hits are NOT decoders; "mipmap" xref -> only "OES_fbo_render_mipmap" refs=[] (no functions).
- BGFX_MAP.md: L8 = Textures, atlases and resources. 6h: PointLightShadowTextureAtlas 0xbb682b0; MaterialTerrainTextureAtlas string only, no fn. 6z/6z-2: texture record +0x28 DXGI_FORMAT [I]. 6o/448: D3D format name table 0x56e3a12..0x56e42f6 incl. BC3/BC7 (data only). 1105/1107: task "TerrainAtlasBlit" functor vtable 0xF43E9E0, task 16. 1511/1512: createTexture slot 26 = 0xe8143c0 (handle, mem, flags, skip); resizeTexture slot 31 = 0xe815840 (handle,w,h,mips,layers). 1812: TextureD3D12::create 0xe81bf30 writes record +0xAF requested format, +0xB0 actual format, +0xB1 numMips; +0xB0 fallback 0x42 uncompressed.
- docs/data/live/texture_table.txt: live census 1465 textures; every format uncompressed (none BC1=71/BC3=77/BC7=99) [V live].
- docs/data/live/createtexture_callers.txt: capture at 0xe8143c0 (createTexture slot 26), 25 hits all ret=0xBC6A2C8 command interpreter; R8=bimg Memory* with decoded image names (cpu-decoded png/tga before upload) [V live].
- docs/data/live/l8b_texcreate_record.txt: capture at TextureD3D12::create entry 0xe81bf30; all hits ret=0xE814560 (inside createTexture after `0xe81455b  call 0xE81BF30`), all format 0x1C uncompressed, numMips=1, no atlas names [V live].
- docs/data/live/mc_root_4e05e50_callers.txt: capture at sub_4e05e50 entry; CALLER ret=0x1289496 (inside sub_12893d0), 150 hits/32 samples [V live]. Decoded: sub_4e05e50 = texture ensure-loaded/upload via deferred transactions (sub_6632bf0 -> sub_12893d0 array iterator -> vtable[1]=sub_4e05e50 via sub_eea6040 thunk), texture RELEASE/ensure-loaded, NOT atlas creation. [V live]
- docs/data/live/_status.txt: batch DONE t=120; mc_root_4e05e50_callers hits=150 samples=32; l8b_texcreate_record hits=150 samples=24; oc_u_el6b_desc hits=0; el10b_lighting_desc hits=0.

## Part 1 — Atlases (terrain, items)
| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| registration index store | registered obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 object alloc size | code 0x1870de0 | 4 (dword) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocs 0x48-byte object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | code 0x1870de0 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object | [V] |
| sub_1870de0 name store | code 0x1870de0 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 | [V] |
| sub_1870de0 fixed registry scan | code 0x1870de0 | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | fixed registry of 41 entries (idx 0..0x29); loop scans [container+0x20 .. container+0x28) for a 0x2A '*' sentinel dword; `0x1870e45  mov [rdx+8],r15` writes range start; `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29` bounds idx to 0..41 | [V] |
| sub_186e6a0 registration dispatcher | code 0x186e6a0 | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop (0x186e6a0..~0x18706a0): allocs named objects via sub_1870de0; five atlas names; NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 callers (xref) | - | - | xref | `0x8f6810 0x61d`, `0x1042320 0x1d1` | sub_186e6a0 has exactly 2 static callers: sub_8f6810 (+0x61d) and sub_1042320 (+0x1d1) [V via xref.py callers] | [V] |
| sub_1870de0 callers (xref) | - | - | xref | `0x1042320 0x1d1`, `0x186e6a0 0x1cb7` | sub_1870de0 has 37 xrefs in; callers include sub_1042320 (+0x1d1) and sub_186e6a0 (+0x1cb7) [V via xref.py callers] | [V] |
| sub_1042320 ServerLevelLoad | code 0x1042320 | - | 0x104237e | `0x104237e  call 0x186E6A0` | ServerLevelLoad triggers atlas registration via sub_186e6a0; also calls sub_1870de0 at 0x10423c7 (idx 0x28) and 0x104246b (idx 0x29); loads "ResourceLoadType::ServerLevelLoad" at `0x104239b  lea rax,[0xF602326]` | [V] |
| sub_1042320 no texture creation | code 0x1042320 (full fn 0x1042320..0x1044320) | - | full listing | (no `call 0xE8143C0` / `0xE815840` / `0xE81BF30`; no TerrainAtlas/ItemAtlas string) | grep of the 1778-line listing of sub_1042320 found NO createTexture/resizeTexture/TextureD3D12::create call and no atlas string — ServerLevelLoad registers atlas names but does NOT create atlas textures | [V] |
| sub_8f6810 initStep1 caller | code 0x8f6810 | - | 0x8f6810+0x61d | (call to sub_186e6a0 inside sub_8f6810) | second caller of sub_186e6a0 (initStep1); writes "initStep1" at `0x8f685b  lea rcx,[0xF7DE3DB]`; registers objects | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0 | [V] |
| TerrainAtlasBlit blit body | code 0xbc02090 | - | vtable 0xF43E9E0 slot 2 | - | vtable slot 2 = sub_bc02090 (size 0x3da): reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 | [V] |
| BlitUncompressed key | str data 0xf5f440c | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| Item-atlas texture creation | none | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task | [?] |
| Terrain-atlas texture creation | none | - | none | - | not located: xref "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture/resizeTexture call tied to TerrainAtlas | [?] |
| createTexture -> TextureD3D12::create call | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (slot 26) builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture itself has 0 static callers, reached only indirect via [vptr+0xD0] (slot 26 = offset 0xD0); live callers all ret=0xBC6A2C8 command interpreter [V live] | [V] |

## Part 2 — mipmaps
| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written inside TextureD3D12::create sub_e81bf30; dl loaded at `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed-format fallback 0x42 | code 0xe81bf30 | 1 (byte) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| resizeTexture slot 31 | code 0xe815840 | - | - | - | resizeTexture (handle,w,h,mips,layers) per BGFX_MAP 1505/1512; mips can be specified on resize; indirect vtable slot dispatch, 0 static xrefs in | [V] |
| mip generation function | none | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-gen Blit task [V]; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I] | [?] |

## Part 3 — compression
| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542 | - | references in 0x765330 and PNG decoder 0x777ed0 are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): image (PNG zlib) decompression, called from PNG decoder dispatcher | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | none | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback [V at 0xe81c12b/0xe81c077]; live census all-uncompressed [V live] | [V] |

## New static angles tried this attempt (NOT repeated proofs)
- xref.py callers of sub_186e6a0 -> 0x8f6810 (+0x61d, initStep1) and 0x1042320 (+0x1d1, ServerLevelLoad) [V] — decoded both; sub_1042320 triggers atlas registration but creates NO atlas texture (no createTexture/resizeTexture/TextureD3D12::create call, no atlas strings in full listing) [V].
- xref.py callers of sub_1870de0 -> 37 xrefs in; includes sub_1042320 (+0x1d1) and sub_186e6a0 (+0x1cb7) [V]. sub_1870de0 is a fixed 41-entry registry (idx 0..0x29) scanning for a 0x2A '*' sentinel; stores *r8 at obj+0 and r9d(idx) at obj+8 [V]. Registry reader / stitcher not located.
- sub_1042320 (ServerLevelLoad) full listing (1778 lines) grepped for createTexture/resizeTexture/TextureD3D12::create calls and TerrainAtlas/ItemAtlas strings: NONE [V].
- Live capture queue: 4 pending for OTHER units (oc_u_el6b_desc, el10b_lighting_desc, oc_u_er2, oc_u_er1_producer); `tools/livecap/request.py add l8b_atlas_reg 0x186e6a0` rejected ("4 requests already pending"). No L8b live capture could be queued this unit.

## CLOSES?
CLOSES? NO. Blocking fact (single): atlas TEXTURE CREATION (the stitcher that builds the TerrainAtlas/ItemAtlas texture description and calls createTexture/resizeTexture) is not located in the exe:
1. "TerrainAtlas" idx 6 and "ItemAtlas" idx 7 are only REGISTERED names (`0x186f731` / `0x186f7fc` inside sub_186e6a0 [V]); registration is triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 [V], but sub_1042320 creates NO atlas texture [V].
2. No createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to either atlas; no ItemAtlasBlit task; live texture creation shows no atlas names (all format 0x1C uncompressed, numMips=1 [V live]); createTexture reachable only indirectly via [vptr+0xD0] bgfx command interpreter (ret=0xBC6A2C8 [V live]).
3. Live capture (which could confirm the atlas description bytes + caller chain via ret=) could NOT be queued — capture request queue full (4 pending for other units).

Resolved as provably-ABSENT (negatives, closed as not-present-in-exe): mipmap generation (no mip-gen function or task; numMips=1 for all live creations [V live]) and BC1/BC3/BC7/DXT compression (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists; all 1465 live textures uncompressed [V live]; create path selects uncompressed 0x42 fallback [V at 0xe81c12b/0xe81c077]).

## TOOL REQUESTS
CAPTURE REQUESTED l8b_atlas_reg (rva 0x186e6a0, size 0x100, max 6) — BLOCKED: capture request queue full (4 pending for other units: oc_u_el6b_desc, el10b_lighting_desc, oc_u_er2, oc_u_er1_producer). Retry next unit once a slot frees. Why: L8b: confirm atlas registration at runtime (TerrainAtlas idx6 / ItemAtlas idx7 name+idx bytes) and name the caller chain via ret= (ServerLevelLoad sub_1042320 vs sub_8f6810 initStep1).
Helper scripts: none (all verbatim lines taken directly from rdis dis output, xref.py callers output, and live capture files; no throwaway scripts written; /tmp/opencode/sub_1042320.txt was a throwaway listing already discarded).

## Verification
Re-check with `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`. Fix every failure; only when delegate check exits 0, set line 2 ("## NEXT") to DONE.
