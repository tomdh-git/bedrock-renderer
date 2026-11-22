## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only.
Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets.

## Sources read (retry #1 — docs/progress/oc_U-EL8b_r1.md — NOT redone)
- oc_U-L8b.md: PNG entry 0x777ed0, IHDR 0x781550; "mipmap" xref -> only "OES_fbo_render_mipmap" refs=[] (no functions).
- BGFX_MAP.md: 6h L8 anchors -> PointLightShadowTextureAtlas 0xbb682b0; MaterialTerrainTextureAtlas string only (no fn). 6z/6z-2 live census: texture record +0x28 DXGI_FORMAT, flag bits incl. mip/array/msaa [I]. 6o/448: D3D format name table 0x56e3a12..0x56e42f6 includes BC3/BC7 (data only). 1105/1107: task "TerrainAtlasBlit" functor vtable 0xF43E9E0, task 16. 1812: TextureD3D12::create (sub_e81bf30, range 0xe81bf30..0xe81d657) writes record +0xAF requested format, +0xB0 actual format, +0xB1 numMips. 1502/1511: resizeTexture slot 31 takes (handle,w,h,mips,layers). 782: sampler builder bit 10 = mip filter [I].

## Part 1 — Atlases (terrain, items)

Terrain: name "TerrainAtlas" registered [V]; blit task "TerrainAtlasBlit" [V] with functor body sub_bc02090 [V]. Item: name "ItemAtlas" registered [V] (r1's "no item atlas string" claim was wrong — it never searched "ItemAtlas"); no item-atlas texture creation located. MaterialTerrainTextureAtlas string unreferenced [?].

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0 (functor vtable 0xF43E9E0); terrain atlas blit task exists | [V] |
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name registered idx 6 via sub_1870de0 inside sub_186e6a0 (0x186e6a0..0x1870357) | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas exists as a registered name | [V] |
| registration index store | registered obj +8 | 4 | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| TerrainAtlasBlit _Do_call (blit body) | code 0xbc02090 | - | - | - | vtable 0xF43E9E0 slot 2 = sub_bc02090: reads a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C atlas fields; constant uploads via sub_ebce390 to cbv at data_12AE1748; draw calls via sub_e7ebfc0 loop stride 0x28 | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| Item-atlas texture creation | - | - | none | - | sub_186e6a0 registers the name only (sub_1870de0 then sub_2fe440 + sub_e935700); no createTexture/resizeTexture path for ItemAtlas located | [?] |

## Part 2 — mipmaps

Material mip keys are read [V]; the texture record carries +0xB0/+0xB1 [V]; mipmap GENERATION not located [?].

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written to texture record inside TextureD3D12::create sub_e81bf30; dl loaded at 0xe81c0cd (`movzx edx,byte ptr [rbp+0x38]`) | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format byte compared to 0x42 fallback format (BGFX_MAP 1812) inside sub_e81bf30 | [V] |
| mip generation function | - | - | none | - | not located: no "GenerateMips"/"mipgen" code references; only sampler mip-filter bit 10 [I] and numMips field [V] | [?] |

## Part 3 — compression

BC1/BC3/BC7 format strings exist but are unreferenced; only zlib/PNG decompression exists; no BC texture compression/decompression code path located [?].

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format string; xref.py refs=[] (unreferenced by code) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format string; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format string; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542, 0x77b498 | refs in 0x765330 and PNG decoder 0x777ed0 | references are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8, 0x199594f, 0x1995a11 | refs inside 0x1994f90 | image (PNG zlib) decompression, called from the PNG decoder dispatcher | [V] |
| D3D format name table | 0x56e3a12..0x56e42f6 | - | - | - | data table incl. BC3/BC7 names (BGFX_MAP 6o/448); data only, no compression code path | [I] |
| BC texture compression/decompression code | - | - | none | - | not located: no BC/DXT compress/decompress function found; textures appear uploaded uncompressed ("BlitUncompressed" key 0xf5f440c ref'd once from 0x560be9f in 0x55f1450) | [?] |

## CLOSES?

NO. Blocking facts (none of these three is [V]-proven):
1. Mipmap generation not located (no GenerateMips/mipgen code; only the numMips field +0xB1 [V] at 0xe81c0d1 and sampler mip-filter bit 10 [I]).
2. No BC texture-compression/decompression code path (BC1/BC3/BC7/DXT strings all refs=[] [?]; only PNG/zlib decompression [V] at 0xf5e339b/0xf58ff5a).
3. Item-atlas texture creation not located ("ItemAtlas" name registered idx 7 [V] at 0x186f7fc, but no createTexture/resizeTexture path for it).
What IS [V]-proven: terrain atlas name + TerrainAtlasBlit task + blit body sub_bc02090; item-atlas name registered idx 7; texture record +0xB1 numMips write at 0xe81c0d1; +0xB0 actual-format check at 0xe81c12b; material mip keys.

## Verification

Verbatim `0xRVA  instr` lines copied from `rdis.exe dis` output; xref refs from `python tools/sigs/xref.py str ""`. To re-check: `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`.

## TOOL REQUESTS

None — rdis dis/sum/vt, xref.py str/callers, BGFX_MAP.md sufficed. The `vt 0xF43E9E0` output (TerrainAtlasBlit functor: slot2=sub_bc02090) was decisive for the terrain blit body.
