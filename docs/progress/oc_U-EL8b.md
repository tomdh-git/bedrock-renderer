## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`
All three parts are pending (none decoded yet):
  1. Atlases (terrain, items)
  2. mipmaps
  3. compression

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only.
Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets.

## Sources read
- docs/progress/oc_U-L8b.md (decoder unit): PNG entry 0x777ed0, IHDR 0x781550; TGA/texture_set hits are NOT decoders. "mipmap" xref -> only "OES_fbo_render_mipmap" refs=[] (no functions). NOT re-run per unit instructions.
- docs/BGFX_MAP.md: 6h L8 anchors -> PointLightShadowTextureAtlas 0xbb682b0; MaterialTerrainTextureAtlas string only (no fn). 6z/6z-2 live texture census: texture record +0x28 DXGI_FORMAT, +0x2c u32 1, flag bits incl. mip/array/msaa [I]. 6o/448: D3D format name table 0x56e3a12..0x56e42f6 includes BC3/BC7 (data only). 1107: sampled frame order includes task "TerrainAtlasBlit" (functor vtable 0xF43E9E0, task 16). 1812: TextureD3D12::create writes record +0xAF requested format, +0xB0 actual format, +0xB1 numMips - skip. 782: sampler builder bit 10 = mip filter [I].

## Part 1 — Atlases (terrain, items)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task name, task 16, functor vtable 0xF43E9E0; referenced inside 0xbb418d0 (size 0x2000, 3 xrefs in) — terrain atlas blit exists as a frame task | [V] |
| texture_atlas material key | str data 0xf55cd23 | 8 (lea qword) | 0x4e1a700 | `0x4e1a700  lea rax,[0xF55CD23]` | material JSON key "texture_atlas" parsed by sub_4e1a0a0 (size 0x2000) | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string present in .rdata but xref.py refs=[] (no code references it) -> terrain atlas is string-only, not decoded | [?] |
| Item atlas | - | - | none | - | no "ItemTextureAtlas"/"item_atlas" string exists; xref refs=[]; no item-atlas code located -> item atlas NOT found | [?] |

## Part 2 — mipmaps

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips written (from skipped-mips value) inside TextureD3D12::create 0xe81bf30; record = this+0xBDE178+handle*0xB8 | [V] |

mipmap status: mip-related MATERIAL PARAMETERS are read (num_mip_levels, mip_fade_amount, mip_fade_color, mip_chain) and the texture record carries +0xB1 numMips [V], but no mipmap GENERATION function (GenerateMips / mip-chain build) was located; sampler bit 10 is a mip FILTER (usage, not generation) [I].

## Part 3 — compression

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format string; xref.py refs=[] (unreferenced by any code) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format string; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format string; xref.py refs=[] | [?] |
| D3D format name table | 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o); data table only, no compression code path | [I] |

compression status: BC1/BC3/BC7 format strings exist in .rdata but NONE is referenced by code (refs=[]); no compression/decompression code path located. Live texture census saw fmt 0x35 (BC7?) at handle h28 [I] only.

## CLOSES?

NO. Blocking fact: not every pending part is [V]-proven. The item atlas is not present anywhere (no "ItemTextureAtlas"/"item_atlas" string, no item-atlas code reference), and compression is unproven (BC1/BC3/BC7 strings all xref refs=[], no compression code path); mipmap generation was also not located (only material mip parameters + the +0xB1 numMips field are [V]). Terrain atlas is only partially evidenced (TerrainAtlasBlit task name [V]; MaterialTerrainTextureAtlas string unreferenced [?]). Until an item atlas reference and a compression code path are found, the item cannot be ticked.

## Verification
Verbatim `0xRVA  instr` lines copied from `rdis.exe dis` output; xref refs from `python tools/sigs/xref.py str "<s>"`. To re-check: `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md`.

## TOOL REQUESTS
None — rdis dis, xref.py str, and BGFX_MAP.md sufficed.
