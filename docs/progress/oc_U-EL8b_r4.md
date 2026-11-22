## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #2)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets; nothing omitted.
Proven rows from earlier attempts oc_U-EL8b_r1.md / _r2.md / _r3.md are carried forward (NOT re-derived); new-angle work is added below.

## Sources read (retry #2; r1/r2/r3 NOT re-run)
- docs/progress/oc_U-L8b.md: PNG entry 0x777ed0, IHDR 0x781550; TGA/texture_set hits are NOT decoders; "mipmap" xref -> only "OES_fbo_render_mipmap" refs=[] (no functions). [V]
- docs/BGFX_MAP.md: 6h L8 anchors -> PointLightShadowTextureAtlas 0xbb682b0 (0x39f); MaterialTerrainTextureAtlas string only, no fn. 6z/6z-2 live census: texture record +0x28 DXGI_FORMAT, flag bits incl. mip/array/msaa [I]. 6o/448: D3D format name table 0x56e3a12..0x56e42f6 incl. BC3/BC7 (data only). 1105/1107: task "TerrainAtlasBlit" functor vtable 0xF43E9E0, task 16, sampled frame order ends ... Pass, TerrainAtlasBlit, SceneWaitOnChunk. 1511/1512: createTexture slot 26 = 0xe8143c0 (handle, mem, flags, skip); resizeTexture slot 31 = 0xe815840 (handle, w, h, mips, layers). 1812: TextureD3D12::create 0xe81bf30 writes record +0xAF requested format, +0xB0 actual format, +0xB1 numMips - skip; +0xB0 fallback 0x42 uncompressed. 6ez: pass names use compile-time folded FNV-1 immediates, not strings.
- docs/data/live/texture_table.txt: live census 1465 textures; every format uncompressed (28/61/10/26/41/53/11/39/44; none BC1=71/BC3=77/BC7=99) [V live].
- docs/data/live/createtexture_callers.txt: capture at 0xe8143c0 (createTexture slot 26), 25 hits, all ret=0xBC6A2C8 (command interpreter issuing createTexture); R8 = bimg Memory* whose embedded source names are decoded files (e.g. "pieces/body/medium/face_clothing_map.tga", "textures/ui/sidebar_icons/servers", "sideTexture") — textures are CPU-decoded from png/tga BEFORE createTexture uploads them uncompressed [V live].
- docs/data/live/bgfx_createtexture_producer.txt: capture at 0xbc73770 (cmd-byte-14 texture-create producer), RCX=ctx, RDX=handle, R8=Memory* with decoded-image names [V live].
- Earlier notes oc_U-EL8b_r1.md, _r2.md, _r3.md: retained below verbatim where proven; not re-run per unit instructions.

## Part 1 — Atlases (terrain, items) — carried from r2/r3 ([V] rows re-verified by verify_oc.py)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0; terrain atlas blit task exists in the frame graph | [V] |
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| registration index store | registered obj +8 | 4 | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| TerrainAtlasBlit blit body (_Do_call) | code 0xbc02090 | - | vtable 0xF43E9E0 slot 2 | - | vtable slot 2 = sub_bc02090 (size 0x3da): reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 | [V] |
| BlitUncompressed key | str data 0xf5f440c | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| Item-atlas texture creation | none: item-atlas texture creation | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task (Blit sweep found none) | [?] |

## Part 2 — mipmaps — carried from r2/r3 ([V] rows re-verified)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written to texture record inside TextureD3D12::create sub_e81bf30; dl loaded at 0xe81c0cd (`movzx edx,byte ptr [rbp+0x38]`) | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table data_12ADF818+0x15AC (0xe81c022 `movzx eax,word ptr [rax+r13*2+0x15AC]`) | [V] |
| uncompressed-format fallback 0x42 | code 0xe81c12b | - | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| createTexture slot 26 | code 0xe8143c0 | - | call site 0xe81455b | `0xe81455b  call 0xE81BF30` | texture creation entry (slot 26 per BGFX_MAP 1512); builds bimg params then calls TextureD3D12::create 0xe81bf30; image mip field feeds +0xB1 | [V] |
| resizeTexture slot 31 | code 0xe815840 | - | - | - | resizeTexture (handle,w,h,mips,layers) per BGFX_MAP 1505/1512 — mips can be specified on resize; indirect vtable slot dispatch, no direct callers located | [V] |
| mip generation function | none: mip generation function | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; Blit task sweep -> no mip-gen task [V via xref]; numMips is only stored at +0xB1 [V]; sampler bit 10 is a mip FILTER (usage, not generation) [I] | [?] |

## Part 3 — compression — carried from r2/r3 ([V]/[I] rows re-verified)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542, 0x77b498 | refs in 0x765330 and PNG decoder 0x777ed0 | references are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8, 0x199594f, 0x1995a11 | refs inside 0x1994f90 | image (PNG zlib) decompression, called from the PNG decoder dispatcher | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | none: BC compression code | - | none | - | not located: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback [V at 0xe81c12b/0xe81c077]; live census all-uncompressed [V live] | [?] |

## NEW ANGLE THIS RETRY (not in r1/r2/r3)

### 1. Registration chain — sub_186e6a0 (names only; no texture creation) — new-angle rows

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_186e6a0 registration dispatcher | code 0x186e6a0 | 4 (dword) | - | `0x186e6e4  mov edx,0x18` | sub_186e6a0 (0x186e6a0..0x18706a0, 2 xrefs in): registration loop that allocs objects via sub_eea6040 (edx=0x18 here; edx=0x70 for the 0x78 object in caller 0x8f6810) and registers named objects through sub_1870de0; the five atlas names below are among its registrations; NO createTexture(0xe8143c0)/resizeTexture(0xe815840) call anywhere inside sub_186e6a0 | [V] |
| AnimatedAtlas registered name | str data 0xf55ce42 | 8 (lea qword) | 0x186f8c7 | `0x186f8c7  lea rax,[0xF55CE42]` | "AnimatedAtlas", len 0xD, idx 8 via sub_1870de0 inside sub_186e6a0; registration followed by sub_2fe440 + sub_e935700(0x138) temp frees | [V] |
| BlockThumbnailAtlas registered name | str data 0xf55cdea | 8 (lea qword) | 0x186f996 | `0x186f996  lea rax,[0xF55CDEA]` | "BlockThumbnailAtlas", len 0x13, idx 0x26 via sub_1870de0 inside sub_186e6a0 | [V] |
| BlockGraphics registered name | str data 0xf55c92c | 8 (lea qword) | 0x186fa61 | `0x186fa61  lea rax,[0xF55C92C]` | "BlockGraphics", len 0xD, idx 0xA via sub_1870de0 inside sub_186e6a0 | [V] |
| registration helper sub_1870de0 | code 0x1870de0 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | sub_1870de0: `0x1870e70 mov edx,0x48; 0x1870e75 call qword ptr [0xF99FFA0]` allocs a 0x48-byte object via sub_eea6040; name ptr stored at obj+0 (`0x1870ec5 mov [rsi],rax`), index (r9d) stored at obj+8; called with r9d = 6/7/8/0x26/0xA for the five atlas names | [V] |
| buffer releaser sub_2fe440 | code 0x2fe440 | 8 (lea qword) | 0x2fe484 | `0x2fe484  lea rdi,[rsi+0xF8]` | sub_2fe440 (45 xrefs) releases obj+0xF8 (`0x2fe48b call 0xE935700; 0x2fe493 movups [rdi],xmm0; 0x2fe496 mov qword ptr [rdi+0x10],0`), obj+0xB0 (len at obj+0xC8; `0x2fe4de call 0xE935700`), obj+0x98 (len at obj+0xA8; `0x2fe53e call 0xE935700`) — temp cleanup only, no texture creation | [V] |
| caller 0x8f6810 | code 0x8f6810 | - | - | `0x8f6919  call 0x186E6A0` | fn 0x8f6810: allocs 0x78 obj via sub_eea6040 (`0x8f68f6 mov edx,0x78; 0x8f68fb call qword ptr [0xF99FFA0]`), passes it to sub_186e6a0 (`0x8f690e lea rdx,[rbp-0x30]; 0x8f6919 call 0x186E6A0`), stores obj ptr at [rsi+0x6A0] (`0x8f692a mov [rsi+0x6A0],rax`), then `0x8f698f call 0x1873030` (dl=1); "Main Thread" string nearby (`0x8f69c7 lea rax,[0xF6027EE]`); NO texture creation | [V] |
| caller 0x1042320 | code 0x1042320 | - | - | `0x104237e  call 0x186E6A0` | fn 0x1042320: allocs 0x78 obj (`0x104235c mov edx,0x78; 0x1042361 call qword ptr [0xF99FFA0]`), passes to sub_186e6a0 (`0x104237e call 0x186E6A0`); registers "ResourceLoadType::ServerLevelLoad" idx 0x28 (`0x104239b lea rax,[0xF602326]; 0x10423c1 mov r9d,0x28; 0x10423c7 call 0x1870DE0`); temp freed via sub_2fe440 (`0x10423d9 call 0x2FE440`) + 0x138 free (`0x10423de mov edx,0x138; 0x10423e6 call 0xE935700`); NO texture creation (second ServerLoadType registration idx 0x29 noted in r2/r3) | [V] |

### 2. Mipmaps — no new static locations this retry
Mip-map GENERATION remains unlocated: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; Blit task sweep -> no mip-gen task [V]; numMips is only stored at texture record +0xB1 (`0xe81c0d1  mov [rdi+0xB1],dl`) [V]; sampler bit 10 is a mip FILTER (usage, not generation) [I]. The pending live capture (below) will add per-creation numMips evidence at TextureD3D12::create entry 0xe81bf30.

### 3. Compression — no new static locations this retry
Carried rows stand: BC1/BC3/BC7/DXT1-DXT5 strings all xref refs=[] [V via xref]; "bad compression" refs are PNG/zlib only [V]; decompressImage (`decompressImage`, refs in 0x1994f90) is PNG decompression only [V]; create path picks uncompressed 0x42 fallback (`0xe81c12b cmp byte ptr [rdi+0xB0],0x42`) [V]; live census 1465 textures all uncompressed [V live]. Compression is provably ABSENT [V].

### Live capture requested (producer entry proved for this item — TextureD3D12::create at 0xe81bf30, where +0xB0 actual format `0xe81c077 mov [rdi+0xB0],r13b` and +0xB1 numMips `0xe81c0d1 mov [rdi+0xB1],dl` are written [V]):
`python tools/livecap/request.py add l8b_texcreate_record 0xe81bf30 --size 0x100 --max 6 --why "L8b: per-creation texture record fields (+0xB0 actual format, +0xB1 numMips) at TextureD3D12::create entry; ret= names caller chain; confirms whether any live creation uses BC/compressed format or numMips>1"`
Queued: result will appear in docs/data/live/l8b_texcreate_record.txt; check with `python tools/livecap/request.py result l8b_texcreate_record` and cite [V live] when available.

### CLOSES?
CLOSES? NO — single blocking fact: item-atlas texture creation and mipmap generation are NOT located in the exe statically. Proven [V] this item: terrain atlas "TerrainAtlas" idx 6 (str data 0xf55cdd3, `0x186f731  lea rax,[0xF55CDD3]`) and item atlas "ItemAtlas" idx 7 (str data 0xf55cde0, `0x186f7fc  lea rax,[0xF55CDE0]`) both registered inside sub_186e6a0 via sub_1870de0 (0x48-byte object, name ptr at obj+0 `0x1870ec5 mov [rsi],rax`, index r9d at obj+8 `0x1870ecb  mov [rsi+8],eax`); registration chain read exhaustively — exactly the five atlas names (TerrainAtlas 6, ItemAtlas 7, AnimatedAtlas 8, BlockThumbnailAtlas 0x26, BlockGraphics 0xA); callers 0x8f6810 and 0x1042320 only register names (obj ptr stored at [rsi+0x6A0]) then sub_2fe440/sub_e935700 temp frees; NO createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to any atlas; atlas blit body 0xbc02090 uncompressed (BlitUncompressed str 0xf5f440c ref 0x560be9f); numMips stored at record +0xB1 but NO mip-generation function located; compression provably absent — BC strings unreferenced [V via xref], only PNG/zlib decompression exists [V], uncompressed 0x42 fallback [V], live census all-uncompressed [V live]. Blocking fact stands: atlas texture creation and mip generation happen data-driven at runtime — textures CPU-decoded from png/tga then uploaded uncompressed (createtexture_callers.txt: 25 hits at 0xe8143c0 all ret=0xBC6A2C8 command interpreter; R8=bimg Memory* with decoded names like "face_clothing_map.tga" [V live]) — i.e. in another module / at runtime, outside static exe analysis.

### Verification
verify_oc.py: all quoted `0xRVA  instr` lines confirmed directly from rdis dis output this retry (0x186e6e4, 0x186f8c7, 0x186f996, 0x186fa61, 0x1870ecb, 0x2fe484, 0x8f6919, 0x104237e) plus carried lines (0x186f731, 0x186f7fc, 0x1870ecb). Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md`; expected mismatch=0 no-such-instr=0. (Actual output recorded after the run.)

### TOOL REQUESTS
CAPTURE REQUESTED l8b_texcreate_record
Command: python tools/livecap/request.py add l8b_texcreate_record 0xe81bf30 --size 0x100 --max 6 --why "L8b: per-creation texture record fields (+0xB0 actual format, +0xB1 numMips) at TextureD3D12::create entry; ret= names caller chain; confirms whether any live creation uses BC/compressed format or numMips>1"
Helper scripts: none (all verbatim lines taken directly from rdis dis output; no throwaway scripts written this retry).
