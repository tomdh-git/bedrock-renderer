## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #1)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only.
Tags: [V] saw in disassembly/live (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one row per distinct offset/key; col1 = unique offset or key; size from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1); verbatim `0xRVA  instr` copied from rdis; meaning only if an instruction/string shows it else '-'. No input data pasted as-is; no skipped offsets.

## NEW-ANGLE ATTACKS DONE THIS RETRY (r1/r2 rows NOT re-done)
- xref str "TerrainAtlas" / "ItemAtlas": refs = only the registration leas (0x186f731 / 0x186f7fc inside sub_186e6a0) [V via xref]
- xref str "GenMip", "Mips", "MipMap", "mipchain", "dds", "TextureAtlas": no such strings in the exe [V via xref]
- xref str "Blit": WholeFrameGammaFallbackBlit, Texture_Blit, Core/Screen/Blit, UI/Blit, BlitTexture, BlitHDR, BlitUncompressed — NO ItemAtlasBlit, NO mip-generation blit task [V via xref]
- vt 0xF43E9E0 (TerrainAtlasBlit functor): slot 2 = sub_bc02090 (size 0x3da) [V via rdis vt]
- callers of TextureD3D12::create 0xe81bf30: 0xe8143c0 (createTexture slot 26, call at 0xe81455b), 0xe815840 (resizeTexture slot 31, indirect slot dispatch), 0xe8403d0 (7 rendertarget creates, all numMips=1) [V via xref callers + rdis dis]
- Full read of TextureD3D12::create 0xe81bf30: +0xB0 actual format + +0xB1 numMips writes, u16/format table at data_12ADF818+0x15AC, 0x42 uncompressed fallback [V via rdis dis]
- docs/data/live/texture_table.txt (live read, read-only): every live texture format is uncompressed (28/61/10/26/41/53/11/39/44; none BC1=71/BC3=77/BC7=99) [V live]
Not located despite the above: item-atlas texture creation, mip generation function, any BC compression/decompression code path.

## Part 1 — Atlases (terrain, items)

| ref | offset/key | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0; then sub_2fe440 + sub_e935700(edx=0x138) | [V] |
| ItemAtlas registered name | str 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0; then sub_2fe440 + sub_e935700(edx=0x138); item atlas EXISTS as a registered name | [V] |
| Item-atlas texture creation | item-atlas-creation | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task (Blit sweep found none) | [?] |
| TerrainAtlasBlit task name | str 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0 | [V] |
| TerrainAtlasBlit blit body | code 0xbc02090 | - | vtable 0xF43E9E0 slot 2 | - | vtable slot 2 = sub_bc02090 (size 0x3da): reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 | [V] |
| BlitUncompressed key | str 0xf5f440c | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |

## Part 2 — mipmaps

| ref | offset/key | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| createTexture slot 26 | code 0xe8143c0 | - | call site 0xe81455b | `0xe81455b  call 0xE81BF30` | texture creation entry (slot 26 per BGFX_MAP 1512); builds bimg params then calls TextureD3D12::create 0xe81bf30; image mip field feeds +0xB1 | [V] |
| resizeTexture slot 31 | code 0xe815840 | - | - | - | resizeTexture (handle,w,h,mips,layers) per BGFX_MAP 1505/1512 — mips can be specified on resize; indirect vtable slot dispatch, no direct callers | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written to texture record inside TextureD3D12::create 0xe81bf30; derived from params field r9+0x2E clamped by maxMips skip arg; live reads show +0xB1=1 [V live, BGFX_MAP 1812] | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table data_12ADF818+0x15AC (0xe81c022 movzx eax,word ptr [rax+r13*2+0x15AC]) | [V] |
| uncompressed-format fallback 0x42 | struct +0xB0 | - | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when table caps lack the type | [V] |
| mip generation function | mip-generation | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; Blit task sweep -> no mip-gen task [V via xref]; numMips is only stored at +0xB1 [V], no generator code found | [?] |

## Part 3 — compression

| ref | offset/key | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| BC/DXT compression code path | compression-path | - | none | - | not located: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists (mce::ImageUtils::decompressImage str 0xf5e339b, refs inside 0x1994f90) [V]; live census formats all uncompressed — 28/61/10/26/41/53/11/39/44, none BC1(71)/BC3(77)/BC7(99) [V live docs/data/live/texture_table.txt]; create path selects uncompressed 0x42 fallback [V] | [?] |
| DXGI format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |

## CLOSES?

NO. Single blocking fact: the item cannot be ticked because the item-atlas texture creation is not located ("ItemAtlas" is only name-registered idx 7 [V at 0x186f7fc]; no createTexture/resizeTexture path and no ItemAtlasBlit task [V via Blit sweep]) AND mip generation is not located (no GenMip/Mips/MipMap code or task [V via xref refs=[]]; only the numMips field +0xB1 [V at 0xe81c0d1] and material mip keys [V]). Compression is provably absent rather than present (all BC1/BC3/BC7/DXT strings unreferenced [V via xref], only PNG/zlib decompression [V], create path falls back to uncompressed 0x42 [V at 0xe81c12b/0xe81c077], live census all-uncompressed [V live]) — but since item-atlas creation and mip generation lack [V] rows, the checklist item stays pending.

## What was tried and failed (do not redo)
- r1/r2 rows: terrain/item name registration [V], TerrainAtlasBlit task + body [V], +0xB1/+0xB0 [V], material mip keys [V], BC strings unreferenced [?] — all retained above, not re-derived.
- New angles tried this retry: full "Blit"/"GenMip"/"Mips"/"MipMap"/"mipchain"/"dds"/"TextureAtlas" string sweeps (all negative except known blits), vt 0xF43E9E0, callers of 0xe81bf30 (0xe8143c0/0xe815840/0xe8403d0), full create disassembly, live texture census. None located item-atlas creation, a mip generator, or a BC code path.

## Verification

Verbatim `0xRVA  instr` lines copied from `rdis.exe dis` output and confirmed against rdis for: 0x186f731, 0x186f7fc, 0xbb431ee, 0xe81455b, 0xe81c077, 0xe81c0d1, 0xe81c12b, 0xe81c022, 0x4e1a7e9, 0x4e1b275, 0x4e1b29b, 0x11528cf. Re-check with `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`.

## TOOL REQUESTS

None — rdis dis/vt, xref.py str/callers, BGFX_MAP.md, docs/data/live/texture_table.txt sufficed.
