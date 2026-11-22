## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | offset | size | read/store address | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste the input data as-is; one annotated row per distinct offset, with all its sites listed; every offset covered, none skipped or summarized. No abbreviations or skipped offsets.

## Carried negative proofs (from oc_U-EL8b_r80.md — NOT re-derived)

- Atlas registration inside sub_186e6a0 via sub_1870de0 [V]: node +0 = name ptr, node +8 = slot index. TerrainAtlas idx 6 str 0xF55CDD3; ItemAtlas idx 7 str 0xF55CDE0; AnimatedAtlas idx 8 str 0xF55CE42; BlockThumbnailAtlas idx 0x26 str 0xF55CDEA. sub_186e6a0 (0x186e6a0..~0x18706a0, 2 static xrefs: ServerLevelLoad sub_1042320, initStep1 sub_8f6810) contains NO createTexture/resizeTexture call. Registered node then freed by sub_2fe440 (desc buffers +0xF8/+0x98 via sub_e935700) — discarded, NOT retained; no reader/stitcher of registered objects located in exe.
- Texture creation entries [V]: slot 26 = createTexture 0xe8143c0 (`0xe81455b  call 0xE81BF30` -> TextureD3D12::create; ret `0xe814560  nop`; 0 static xrefs). Slot 31 = resizeTexture 0xe815840 (takes mips `0xe815866  mov edi,r9d`; texture table base `0xe815876  lea rsi,[rcx+0xBDE178]`; 0 static xrefs). TextureD3D12::create 0xe81bf30 writes +0xB0 actual format (`0xe81c077  mov [rdi+0xB0],r13b`), +0xB1 numMips (`0xe81c0d1  mov [rdi+0xB1],dl`); uncompressed fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42`.
- Live captures [V live]: l8b_texcreate_record (rva 0xE81BF30, 24 samples): CALLER ret=0xE814560; all format 0x1C numMips=1; ZERO atlas names. createtexture_callers (rva 0xE8143C0, 25 hits): CALLER ret=0xBC6A2C8 (bgfx executor); format 0x1C sizes 128x128/64x64; ZERO atlas names/mips>1/compressed. l8b_resizetex_slot31 + _b (rva 0xE815840): BOTH EMPTY — resizeTexture never triggered. mc_root_4e05e50_callers (rva 0x4E05E50): indirect caller sub_12893d0, ret=0x1289496; texture ensure-loaded/upload via deferred-transaction path, NOT atlas creation.
- Blit side [V]: 'TerrainAtlasBlit' task `0xbb431ee  lea rdx,[0xF539A0B]` (task 16, functor vtable 0xF43E9E0); 'BlitUncompressed' `0x560be9f  lea r9,[0xF5F440C]`; no ItemAtlasBlit task.
- Mip generation [V] NOT located: xref GenMip/Mips/MipMap/mipchain -> refs=[]; no mip-gen Blit task; numMips only at +0xB1; all live creations numMips=1.
- Compression (BC1/BC3/BC7/DXT) [V] provably ABSENT: all those strings unreferenced [V via xref]; only PNG/zlib decompression exists; all live creations uncompressed format 0x1C.

## Blocking fact (single)

Atlas TEXTURE CREATION stitcher not located in the exe — TerrainAtlas(idx6)/ItemAtlas(idx7) registration is proven [V] and the TerrainAtlasBlit body [V] reads atlas fields at runtime, but no createTexture(slot 26)/resizeTexture(slot 31) call is tied to either atlas; registered objects are discarded after registration (sub_2fe440 frees desc buffers); no ItemAtlasBlit task; live texture creation shows no atlas names, all format 0x1C uncompressed numMips=1 [V live]. Creation is likely external/cross-module to the exe (not located by static analysis). A live capture at the TerrainAtlasBlit producer entry (0xbc02090) is queued (docs/data/live/l8b_atlas_blit.txt) to confirm atlas field meanings/sizes at runtime, but it reads the atlas object rather than locating its texture-creation stitcher.

## Answer table

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| Registered atlas node +0 name ptr | +0x00 | 8 (qword) | [rsi]+0x00 | `0x1870ec5  mov [rsi],rax` | registered atlas name pointer stored at node+0 inside sub_1870de0 (node allocs 0x48 bytes via `0x1870e70  mov edx,0x48`) | [V] |
| Registered atlas node +8 slot index | +0x08 | 4 (dword) | [rsi]+0x08 | `0x1870ecb  mov [rsi+8],eax` | registered atlas slot index stored at node+8 inside sub_1870de0 (r9d = 6 TerrainAtlas / 7 ItemAtlas) | [V] |
| "TerrainAtlas" registered name | str 0xF55CDD3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0 | [V] |
| "ItemAtlas" registered name | str 0xF55CDE0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| sub_186e6a0 no createTexture/resizeTexture | code 0x186e6a0 | - | - | - | registration loop sub_186e6a0..~0x18706a0 contains NO createTexture(0xe8143c0)/resizeTexture(0xe815840) call | [V] |
| Registered objects discarded | node | - | - | - | node consumed by sub_2fe440 (frees desc buffers +0xF8/+0x98 via sub_e935700) then freed — discarded, NOT retained; no reader/stitcher of registered objects located in exe | [V] |
| "TerrainAtlasBlit" task name | str 0xF539A0B | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | TerrainAtlasBlit task-16 name; functor vtable 0xF43E9E0 slot 2 = sub_bc02090 (body reads atlas fields +0x88/+0x8C/+0x98/+0x9C/+0x48/+0xDC/+0x11C) | [V] |
| "BlitUncompressed" key | str 0xF5F440C | 8 (lea qword) | 0x560be9f | `0x560be9f  lea r9,[0xF5F440C]` | atlas/texture blit path uncompressed; referenced once from 0x560be9f inside 0x55f1450 | [V] |
| Atlas texture creation via createTexture/resizeTexture | none | - | - | - | NOT located: no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to TerrainAtlas(idx6) or ItemAtlas(idx7); xref "ItemAtlas"/"TerrainAtlas" refs only the two registration lea lines | [?] |
| ItemAtlasBlit task | none | - | - | - | NOT present: no ItemAtlasBlit task; only TerrainAtlasBlit task exists | [?] |
| Texture record +0xB0 actual format | +0xB0 | 1 (byte) | [rdi]+0xB0 (two sites) | `0xe81c077  mov [rdi+0xB0],r13b` / `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format byte at +0xB0 inside TextureD3D12::create (0xe81bf30); uncompressed fallback 0x42 (`0xe81c068  mov ecx,0x42`); all live creations format 0x1C uncompressed [V live] | [V] |
| Texture record +0xB1 numMips | +0xB1 | 1 (byte) | [rdi]+0xB1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte at +0xB1 inside create; dl loaded `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]`; all live creations numMips=1 [V live] | [V] |
| resizeTexture slot 31 | code 0xe815840 | - | 0xe815866 | `0xe815866  mov edi,r9d` | resizeTexture(handle,w,h,mips,layers) takes mips in r9d; texture table base `0xe815876  lea rsi,[rcx+0xBDE178]`; 0 static xrefs; never observed live (l8b_resizetex_slot31 + _b captures empty) [V live] | [V] |
| createTexture slot 26 | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture builds bimg params then calls TextureD3D12::create 0xe81bf30; ret `0xe814560  nop`; 0 static xrefs; reached only indirect via vtable+0xD0 (slot 26) | [V] |
| Mip generation function | none | - | - | - | NOT located: xref GenMip/Mips/MipMap/mipchain -> refs=[]; no mip-gen Blit task; numMips only stored at +0xB1; all live numMips=1 [V live]; sampler bit 10 = mip FILTER usage not generation [I] | [?] |
| BC1 string | str 0xf84ad1c | - | none | - | BC1/DXT1 format name string; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str 0xf84aaf8 | - | none | - | BC3/DXT5 format name string; xref.py refs=[] | [?] |
| BC7 string | str 0xf84a930 | - | none | - | BC7 format name string; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str 0xf7ddd18/0xf7d3d04/0xf7d6ac8/0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 name strings; all xref.py refs=[] | [?] |
| BC texture compression code | none | - | - | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists; create path selects uncompressed [V]; live census all-uncompressed format 0x1C [V live] | [V] |

## CLOSES?

CLOSES? NO. Blocking fact (single): atlas TEXTURE CREATION stitcher not located in the exe — TerrainAtlas(idx6)/ItemAtlas(idx7) registration is proven [V] and the TerrainAtlasBlit body [V] reads atlas fields at runtime, but no createTexture(slot 26)/resizeTexture(slot 31) call is tied to either atlas; registered objects are discarded after registration (sub_2fe440 frees desc buffers); no ItemAtlasBlit task; live texture creation shows no atlas names, all format 0x1C uncompressed numMips=1 [V live]. Creation is likely external/cross-module to the exe (not located by static analysis). Live capture l8b_atlas_blit (rva 0xbc02090) is queued; result pending in docs/data/live/l8b_atlas_blit.txt.

Resolved as provably-ABSENT (negatives, closed as not-present-in-exe): mipmap generation [V] (no mip-gen function/task; numMips=1 for all live creations [V live]) and BC1/BC3/BC7/DXT compression [V] (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists; all 1465 live textures uncompressed [V live]).

## TOOL REQUESTS

CAPTURE REQUESTED l8b_atlas_blit (rva 0xbc02090, TerrainAtlasBlit _Do_call producer entry [V], size 0x100, max 6) — queued 2026-11-22; result pending in docs/data/live/l8b_atlas_blit.txt. why: L8b: dump live atlas object (RCX = this) at blit time to confirm atlas field meanings/sizes at runtime; ret= names task-dispatcher caller chain.
Helper scripts: none (all verbatim lines taken directly from rdis dis output and prior verified notes; no throwaway scripts written).

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md` and fix EVERY failure. Only when delegate check exits 0, set line 2 ("## NEXT" follower) to DONE.
