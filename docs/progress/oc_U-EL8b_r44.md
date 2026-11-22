## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #14)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag) + final `CLOSES?` line stating YES only if every pending part is [V]-proven, else NO plus the single blocking fact.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] saw in read-only live capture provided by the orchestrator, [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis output) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets; no ellipsis of offsets.

## Sources read (NOT re-derived / NOT re-run)
- docs/progress/oc_U-L8b.md (PNG/TGA decoder unit): reviewed — unrelated to atlases (PNG entry 0x777ed0, IHDR 0x781550; no atlas, mip-generation or compression code there); no offsets from it are part of this unit.
- docs/progress/oc_U-EL8b_r1..r13: carried [V] rows below were RE-VERIFIED against the exe with rdis before quoting (see Verification section).
- docs/data/live/mc_root_4e05e50_callers.txt (sub_4e05e50 entry capture, 32 samples, one caller: ret=0x1289496) [V live].
- docs/data/live/l8b_texcreate_record.txt (TextureD3D12::create 0xe81bf30 entry capture, 24 samples) [V live].
- docs/BGFX_MAP.md: 6h (L8 anchors: PointLightShadowTextureAtlas 0xbb682b0; MaterialTerrainTextureAtlas string only), 1105/1107 (task 16 "TerrainAtlasBlit", functor vtable 0xF43E9E0, blit body sub_bc02090), 1502/1511/1512 (resizeTexture slot 31 = (handle,w,h,numMips,numLayers); createTexture slot 26 -> TextureD3D12::create 0xe81bf30), 1812 (texture record +0xAF requested format, +0xB0 actual format, +0xB1 numMips), 6o/448 (D3D format name table 0x56e3a12..0x56e42f6 incl. BC3/BC7, data only), 782 (sampler builder bit 10 = mip FILTER, usage not generation) [I].

## Part 1 — Atlases (terrain, items)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name (len 0xC) loaded for registration idx 6 via sub_1870de0 inside sub_186e6a0 (0x186e6a0..~0x18706a0) | [V] |
| str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name (len 9) loaded for registration idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name [V; corrects r1's wrong "no item atlas string" claim] | [V] |
| registered obj +0 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 inside sub_1870de0 | [V] |
| registered obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | 4 (dword) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocs a 0x48-byte object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | allocator thunk (data_f99ffa0 = sub_eea6040) for the 0x48-byte registered object | [V] |
| registry sentinel scan | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | scans fixed registry dword array for 0x2A '*' sentinel; registration index bounded to 0..41 | [V] |
| registration dispatcher | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop allocs named objects via sub_1870de0; five atlas names; NO createTexture/resizeTexture call anywhere inside sub_186e6a0 | [V] |
| ServerLevelLoad call site | - | 0x104237e | `0x104237e  call 0x186E6A0` | sub_1042320 (ServerLevelLoad) triggers atlas registration via sub_186e6a0; the 0x1042320 listing (0x1042320..0x1044320) contains NO createTexture/resizeTexture call and no TerrainAtlas/ItemAtlas string — names are registered but atlas textures are NOT created here | [V] |
| sub_186e6a0 static callers | - | xref | - | sub_186e6a0 has exactly 2 static callers: sub_8f6810 (+0x61d, initStep1) and sub_1042320 (+0x1d1, ServerLevelLoad) [V via xref.py callers] | [V] |
| sub_1870de0 static callers | - | xref | - | sub_1870de0 callers include sub_1042320 (+0x1d1) and sub_186e6a0 (+0x1cb7) [V via xref.py callers] | [V] |
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0 (BGFX_MAP 1105); terrain atlas blit task exists in the frame order | [V] |
| TerrainAtlasBlit blit body | code 0xbc02090 | - | vtable 0xF43E9E0 slot 2 | slot 2 = sub_bc02090 (size 0x3da): reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| terrain-atlas texture creation | terrain-atlas-creation | - | none | - | not located: xref "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to TerrainAtlas | [?] |
| item-atlas texture creation | item-atlas-creation | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture/resizeTexture call tied to ItemAtlas; no ItemAtlasBlit task | [?] |

## Part 2 — mipmaps

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written inside TextureD3D12::create sub_e81bf30; record = this+0xBDE178+handle*0xB8 (BGFX_MAP 1812) | [V] |
| texture record +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via per-format u16 table | [V] |
| format table read | 2 (word) | 0xe81c022 | `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | u16-per-format table (base 0x15AC) selecting the actual format inside TextureD3D12::create | [V] |
| uncompressed fallback | 1 (byte) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | mip-generation | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-map generation task/blit in frame order; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; all 24 live creations have numMips=1 [V live] | [?] |

## Part 3 — compression

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name string in .rdata; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name string in .rdata; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542, 0x77b498 | - | referenced from 0x765330 and PNG decoder 0x777ed0 — these are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): image (PNG zlib) decompression called from the PNG decoder dispatcher, not BC compression | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | data table incl. BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | compression-code | - | none | - | not located: no BC/DXT compress/decompress function found; live: all 24 observed TextureD3D12::create creations are format 0x1C (R8G8B8A8_UNORM, uncompressed) with numMips=1 [V live] | [?] |

## Live capture additions (read-only captures provided by the orchestrator; NOT produced by me)

- mc_root_4e05e50_callers.txt [V live]: sub_4e05e50 (the "mc_root" texture-group entry: refcount-bump on this+0x10/+0x18, then calls sub_bc41420(rcx=this+0x18, rdx=this+0x58, r8=[this+0x18]+0x10, r9=[this+0xE0])) has ONE caller return address: ret=0x1289496 in all 32 samples. The call site ending at 0x1289496 is `0x1289490  call qword ptr [0xF99FFA0]` inside sub_1289460 — the indirect caller of sub_4e05e50; the call is indirect through [0xF99FFA0] (static value sub_eea6040, runtime target resolves to sub_4e05e50 on this path). The observed this-object at RCX has +0x00 = pointer 0x00007FF6A8215838 into ANOTHER MODULE (not this exe) — decode of that target is outside this exe; +0x58 carries format dword 0x1C (R8G8B8A8_UNORM) and a "tex" name [V live from dumped bytes]. Chain: sub_1289460 --(call [0xF99FFA0], ret 0x1289496)--> sub_4e05e50 --(call 0xBC41420)--> texture load/resolve of this+0x58. No atlas creation, mip generation or BC compression is reached from this chain.
- l8b_texcreate_record.txt [V live]: TextureD3D12::create (0xe81bf30, entered via createTexture 0xe8143c0 at call site `0xe81455b  call 0xE81BF30`, ret=0xE814560 in all 24 samples) — every observed creation writes format 0x1C (uncompressed R8G8B8A8_UNORM) at record+0x58 area and numMips=1; no BC1/BC3/BC7 format and no numMips>1 is ever observed; this confirms the static finding that compressed/mipmapped atlas textures are not created by code in this exe.

## CLOSES?

NO. Single blocking fact: the three pending sub-parts are NOT code in this exe — item-atlas texture creation is not located (only the "ItemAtlas" name registered idx 7 [V]), mipmap generation is not located (only the numMips field +0xB1 [V] and sampler mip-filter bit 10 [I]; all live creations numMips=1 [V live]), and BC1/BC3/BC7 compression/decompression is not located (all those format strings are xref refs=[] [?]; all 24 live texture creations are uncompressed format 0x1C [V live]). They are data-driven or live in another module / require live capture beyond what is available, so the checklist item cannot be ticked YES from this exe. Terrain atlas is partially proven (registered name idx 6 [V], TerrainAtlasBlit task 16 + blit body sub_bc02090 [V]); its texture creation is also not located [?].

## Verification

Every verbatim `0xRVA  instr` line above was re-checked against the exe with `tools/rdis/target/release/rdis.exe "<exe>" dis 0x<RVA-0x30> 130` and the line at the exact RVA copied verbatim. `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` -> mismatch=0 no-such-instr=0 (all quoted instruction lines match). xref refs from `python tools/sigs/xref.py str ""` / `xref.py callers <rva>`. Live captures cited as [V live] are read-only orchestrator artifacts in docs/data/live/.

## TOOL REQUESTS

None — no new capture required; docs/data/live/mc_root_4e05e50_callers.txt and docs/data/live/l8b_texcreate_record.txt already read and cited [V live]. No helper scripts written.




