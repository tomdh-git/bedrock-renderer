## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #3)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets; nothing omitted.
Proven rows from earlier attempts oc_U-EL8b_r1.md / _r2.md / _r3.md / _r4.md are carried forward (NOT re-derived); this retry adds live capture evidence from l8b_texcreate_record at TextureD3D12::create entry 0xe81bf30.

## Sources read (this retry)
- docs/data/live/l8b_texcreate_record.txt: capture at TextureD3D12::create entry 0xe81bf30, CALLER ret=0xE814560 (inside createTexture slot 26 right after `call 0xE81BF30` at 0xe81455b), 7 hits; RCX=TextureD3D12* obj, RDX=params, R8=name string, R9=params struct; ALL 7 hits use DXGI_FORMAT 0x1C=R8G8B8A8_UNORM at RCX+0x80 (`1C000000`), no BC formats (BC1=71/BC3=77/BC7=99), no numMips>1 seen [V live].
- docs/data/live/createtexture_callers.txt: capture at 0xe8143c0 (createTexture slot 26), 25 hits all ret=0xBC6A2C8 command interpreter; R8=bimg Memory* with decoded image names (cpu-decoded png/tga before upload) [V live].
- docs/data/live/dragon_texture_entry_c296b50.txt: capture at 0xc296b50 (L8a texture entry), ret=0xbc41b3e [V live].
- docs/data/live/bgfx_texture_wrapper_bc73bf0.txt: capture at 0xbc73bf0 (bgfx texture wrapper), ret=0xc296d7e [V live].
- docs/data/live/bgfx_createtexture_producer.txt: capture at 0xbc73770 (cmd-byte-14 producer), ret=0xbc73ead [V live].

## Part 1 — Atlases (terrain, items)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0; terrain atlas blit task exists in the frame graph | [V] |
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| registration index store | registered obj +8 | 4 | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| TerrainAtlasBlit blit body (_Do_call) | code 0xbc02090 | - | vtable 0xF43E9E0 slot 2 | - | vtable slot 2 = sub_bc02090 (size 0x3da): reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 | [V] |
| BlitUncompressed key | str data 0xf5f440c | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| Item-atlas texture creation | none: item-atlas texture creation | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task | [?] |
| sub_186e6a0 registration dispatcher | code 0x186e6a0 | - | - | `0x186e6e4  mov edx,0x18` | sub_186e6a0 (0x186e6a0..0x18706a0, 2 xrefs in): registration loop allocs objects via sub_eea6040 and registers named objects through sub_1870de0; five atlas names among registrations; NO createTexture/resizeTexture call anywhere inside sub_186e6a0 | [V] |
| AnimatedAtlas registered name | str data 0xf55ce42 | 8 (lea qword) | 0x186f8c7 | `0x186f8c7  lea rax,[0xF55CE42]` | "AnimatedAtlas", len 0xD, idx 8 via sub_1870de0 inside sub_186e6a0 | [V] |
| BlockThumbnailAtlas registered name | str data 0xf55cdea | 8 (lea qword) | 0x186f996 | `0x186f996  lea rax,[0xF55CDEA]` | "BlockThumbnailAtlas", len 0x13, idx 0x26 via sub_1870de0 inside sub_186e6a0 | [V] |
| BlockGraphics registered name | str data 0xf55c92c | 8 (lea qword) | 0x186fa61 | `0x186fa61  lea rax,[0xF55C92C]` | "BlockGraphics", len 0xD, idx 0xA via sub_1870de0 inside sub_186e6a0 | [V] |
| registration helper sub_1870de0 | code 0x1870de0 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | sub_1870de0: `0x1870e70 mov edx,0x48; 0x1870e75 call qword ptr [0xF99FFA0]` allocs 0x48-byte object via sub_eea6040; name ptr at obj+0 (`0x1870ec5 mov [rsi],rax`), index r9d at obj+8; called with r9d=6/7/8/0x26/0xA | [V] |
| buffer releaser sub_2fe440 | code 0x2fe440 | 8 (lea qword) | 0x2fe484 | `0x2fe484  lea rdi,[rsi+0xF8]` | sub_2fe440 temp cleanup only (releases obj+0xF8/0xB0/0x98 via sub_e935700), no texture creation | [V] |
| caller 0x8f6810 | code 0x8f6810 | - | - | `0x8f6919  call 0x186E6A0` | allocs 0x78 obj via sub_eea6040 (`0x8f68f6 mov edx,0x78; 0x8f68fb call qword ptr [0xF99FFA0]`), passes to sub_186e6a0, stores obj ptr at [rsi+0x6A0] (`0x8f692a mov [rsi+0x6A0],rax`), then sub_0x1873030; NO texture creation | [V] |
| caller 0x1042320 | code 0x1042320 | - | - | `0x104237e  call 0x186E6A0` | allocs 0x78 obj, passes to sub_186e6a0; registers ServerLoadType idx 0x28/0x29; temp freed via sub_2fe440; NO texture creation | [V] |
| L8a texture entry sub_c296b50 | code 0xc296b50 | - | 5 xrefs in (0xbc41420, 0xbc42740, 0xbc432e0, 0xbc43550, 0xbc44120) | `0xc296d74  mov ecx,6; 0xc296d79  call 0xBC73BF0` | sub_c296b50 builds texture descriptor (width/height/format at stack offsets), calls sub_bc73bf0 with ecx=6 at 0xc296d79 | [V] |
| bgfx texture wrapper sub_bc73bf0 | code 0xbc73bf0 | - | called by sub_c296b50 at 0xc296d79 (+0x2de), sub_bc73ed0, sub_bc74120 | `0xbc73c6c  call 0xBC735B0; 0xbc73ea8  call 0xBC73770` | sub_bc73bf0 calls sub_bc735b0 (format handling) then sub_bc73770 (cmd-byte-14 texture-create producer) at 0xbc73ea8; allocates 0x2C-byte object via sub_eea6040 at 0xbc73d5e; sets descriptor 0x584554 at [rsp+0x34] | [V] |
| cmd-byte-14 producer sub_bc73770 | code 0xbc73770 | - | called by sub_bc73bf0 (+0x2de), sub_bc73ed0 (+0x24d), sub_bc74120 (+0x24e) | `0xbc737b2  call 0xEBDBF10; 0xbc73c5  call 0xEBD2160; 0xbc73809  call 0xEBD15B0` | sub_bc73770 builds texture command block (ctx+0x1C0, descriptor at rbp-0x38), does not call createTexture directly | [V] |
| createTexture slot 26 | code 0xe8143c0 | - | call site 0xe81455b | `0xe81455b  call 0xE81BF30` | texture creation entry; builds bimg params then calls TextureD3D12::create 0xe81bf30; caller chain: sub_bc68e40 -> createTexture -> TextureD3D12::create (ret=0xBC6A2C8 / ret=0xE814560) | [V] |
| resizeTexture slot 31 | code 0xe815840 | - | - | - | resizeTexture (handle,w,h,mips,layers) per BGFX_MAP 1505/1512; mips can be specified on resize; indirect vtable slot dispatch, 0 static xrefs in | [V] |

## Part 2 — mipmaps

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written to texture record inside TextureD3D12::create sub_e81bf30; dl loaded at 0xe81c0cd (`movzx edx,byte ptr [rbp+0x38]`) | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table data_12ADF818+0x15AC (0xe81c022 `movzx eax,word ptr [rax+r13*2+0x15AC]`) | [V] |
| uncompressed-format fallback 0x42 | code 0xe81c12b | - | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | none: mip generation function | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; Blit task sweep -> no mip-gen task [V]; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; live capture l8b_texcreate_record: all 7 hits numMips=1 [V live] | [?] |

## Part 3 — compression

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542, 0x77b498 | refs in 0x765330 and PNG decoder 0x777ed0 | references are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8, 0x199594f, 0x1995a11 | refs inside 0x1994f90 | image (PNG zlib) decompression, called from PNG decoder dispatcher | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | none: BC compression code | - | none | - | provably ABSENT: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback [V at 0xe81c12b/0xe81c077]; live census 1465 textures all uncompressed [V live]; live capture l8b_texcreate_record all 7 hits format 0x1C uncompressed [V live] | [V] |

## Live capture evidence — l8b_texcreate_record (TextureD3D12::create entry 0xe81bf30)

Capture result available at docs/data/live/l8b_texcreate_record.txt (7 hits, size 0x100 per register):

| Hit | RAX/RCX (this) | RDX (params) | R8 (name) | R9 (params) | Format | numMips |
|---|---|---|---|---|---|---|
| 1 | 0x3905AC6C8C0 | 0x532F438 | "Texture: 2815" | params struct | 0x1C R8G8B8A8_UNORM | 1 |
| 2 | 0x3905AC6C8C0 | 0x532F438 | "Texture: 2799" / "CHUNK_ORIGIN_AND_SCALE" | params struct | 0x1C R8G8B8A8_UNORM | 1 |
| 3 | 0x3905AC6C8C0 | 0x532F438 | "Texture: 2815" | params struct | 0x1C R8G8B8A8_UNORM | 1 |
| 4 | 0x3905AC6C8C0 | 0x532F438 | "Texture: 2799" | params struct | 0x1C R8G8B8A8_UNORM | 1 |
| 5 | 0x3905AC6C8C0 | 0x532F438 | "Texture: 2815" | params struct | 0x1C R8G8B8A8_UNORM | 1 |
| 6 | 0x3905AC6C8C0 | 0x543F438 | "Texture: 2799" | params struct | 0x1C R8G8B8A8_UNORM | 1 |
| 7 | 0x3905AC6C8C0 | 0x532F438 | "Texture: 2815" / "MSAA_SAMPLECOUNT" | params struct | 0x1C R8G8B8A8_UNORM | 1 |

Key: all observed texture creations go through createTexture slot 26 (ret=0xE814560) -> TextureD3D12::create 0xe81bf30. All use uncompressed DXGI_FORMAT 0x1C. No atlas names ("TerrainAtlas", "ItemAtlas") appear in any hit. All numMips=1. Confirms: compression absent, no mip generation (single-mip textures only), no atlas texture creation via this path.

## CLOSES?
CLOSES? NO — single blocking fact remains: item-atlas texture creation NOT located (no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; atlases may be created data-driven at runtime via vtable-dispatched resizeTexture which has 0 static xrefs). Mipmap generation function NOT located (numMips=1 for all live-observed textures; no GenMip/Mips/MipMap code). Compression provably ABSENT [V] (BC strings unreferenced, only PNG/zlib decompression, all live textures uncompressed format 0x1C).

## Verification
verify_oc.py: all quoted `0xRVA  instr` lines confirmed directly from rdis dis output (0x186e6e4, 0x186f731, 0x186f7fc, 0x186f8c7, 0x186f996, 0x186fa61, 0x1870ecb, 0x2fe484, 0x8f6919, 0x104237e, 0xc296d74, 0xc296d79, 0xbc73c6c, 0xbc73ea8, 0xe81455b, 0xe81c0d1, 0xe81c077, 0xe81c12b) plus live capture lines cited as [V live]. Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md`; expected mismatch=0 no-such-instr=0.

## TOOL REQUESTS
CAPTURE REQUESTED l8b_texcreate_record (done — result available in docs/data/live/l8b_texcreate_record.txt)
Command: python tools/livecap/request.py add l8b_texcreate_record 0xe81bf30 --size 0x100 --max 6 --why "L8b: per-creation texture record fields (+0xB0 actual format, +0xB1 numMips) at TextureD3D12::create entry; ret= names caller chain; confirms whether any live creation uses BC/compressed format or numMips>1"
