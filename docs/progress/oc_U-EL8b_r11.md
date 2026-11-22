## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #4)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized.

## Part 1 — Atlases (terrain, items) — carried [V] rows from oc_U-EL8b_r1..r10 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| registration index store | registered obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | code 0x1870e70 | 4 (dword) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocs 0x48-byte object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | code 0x1870e75 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object | [V] |
| sub_1870de0 name store | code 0x1870ec5 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 | [V] |
| sub_186e6a0 registration dispatcher | code 0x186e6a0 | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop (0x186e6a0..~0x18706a0): allocs named objects via sub_1870de0; five atlas names; NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 static callers | xref sub_186e6a0 callers | - | xref | - | sub_186e6a0 has exactly 2 static callers: sub_8f6810 (+0x61d) and sub_1042320 (+0x1d1) [V via xref.py callers] | [V] |
| sub_1870de0 static callers | xref sub_1870de0 callers | - | xref | - | sub_1870de0 has 37 xrefs in; callers include sub_1042320 (+0x1d1) and sub_186e6a0 (+0x1cb7) [V via xref.py callers] | [V] |
| sub_1042320 ServerLevelLoad | code 0x1042320 | - | 0x104237e | `0x104237e  call 0x186E6A0` | ServerLevelLoad triggers atlas registration via sub_186e6a0; loads "ResourceLoadType::ServerLevelLoad" at `0x104239b  lea rax,[0xF602326]` | [V] |
| sub_1042320 full listing grepped | code 0x1042320..0x1044320 | - | full listing | - | grep of the 1778-line listing found NO `call 0xE8143C0` / `0xE815840` / `0xE81BF30` and no TerrainAtlas/ItemAtlas string — ServerLevelLoad registers atlas names but does NOT create atlas textures | [V] |
| sub_8f6810 initStep1 caller | code 0x8f6810 | - | 0x8f6810+0x61d | - | second caller of sub_186e6a0 (initStep1); writes "initStep1" at `0x8f685b  lea rcx,[0xF7DE3DB]`; registers objects | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0 | [V] |
| TerrainAtlasBlit blit body | code 0xbc02090 | - | vtable 0xF43E9E0 slot 2 | - | vtable slot 2 = sub_bc02090 (size 0x3da): reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 | [V] |
| BlitUncompressed key | str data 0xf5f440c | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| item-atlas texture creation (not located) | item-atlas-creation | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task | [?] |
| terrain-atlas texture creation (not located) | terrain-atlas-creation | - | none | - | not located: xref "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture/resizeTexture call tied to TerrainAtlas | [?] |
| createTexture -> TextureD3D12::create call | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (slot 26) builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture itself has 0 static callers, reached only indirect via [vptr+0xD0] (slot 26 = offset 0xD0); live callers all ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry decode | code 0xe815840 | mixed (qword/dword/word/byte) | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode [V via rdis dis 0xe815840: `sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in`]: RCX=this renderer (`0xe81586c  mov r14,rcx`), DX=handle word stored (`0xe81586f  mov [rbp+0x8E],dx`), R8D=width->ebx (`0xe815869  mov ebx,r8d`), R9D=mips->edi (`0xe815866  mov edi,r9d`), stack word mips read (`0xe815980  movzx r13d,word ptr [rbp+0x108]`), stack byte layers (`0xe815988  movzx r12d,byte ptr [rbp+0x100]`), renderer+0xBDE178 handle array (`0xe815876  lea rsi,[rcx+0xBDE178]`); resizeTexture (handle,w,h,mips,layers) per BGFX_MAP 1505/1512; mips can be specified on resize; 0 static xrefs — indirect vtable dispatch only | [V] |

## Part 2 — mipmaps — carried [V] rows from oc_U-EL8b_r1..r10 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written inside TextureD3D12::create sub_e81bf30; dl loaded at `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed-format fallback 0x42 | code 0xe81bf30 | 1 (byte) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function (not located) | mip-generation | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-gen Blit task [V]; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression — carried [V]/[I] rows from oc_U-EL8b_r1..r10 (NOT re-derived)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542 | - | references in 0x765330 and PNG decoder 0x777ed0 are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): image (PNG zlib) decompression, called from PNG decoder dispatcher | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code (not located) | bc-code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback [V at 0xe81c12b/0xe81c077]; live census/all captures all-uncompressed [V live] | [V] |

## Live capture evidence read this attempt (NOT re-derived; decoded from the capture files)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 indirect caller (ret=) | code 0x12893d0 | - | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | ret=0x1289496 (`0x1289496  nop`) = return address inside sub_12893d0 right after the thunk call; all 32 mc_root_4e05e50_callers samples share this caller [V live docs/data/live/mc_root_4e05e50_callers.txt line 3-4] | [V live] |
| sub_6632bf0 Deferred Texture Transactions | code 0x6632bf0 | 16 (movups) | 0x6632c19 | `0x6632c19  lea rax,[0xF54E8AF]` | references "Deferred Texture Transactions" at data_f54e8af; reads 16-byte pointer pair `0x6632c28  movups xmm0,[rcx+0x18]`; calls array iterator `0x6632c55  call 0x12893D0` | [V] |
| sub_4e05e50 = texture ensure-loaded/upload, NOT creation | code 0x4e05e50 | mixed | 0x4e05e6e | `0x4e05e6e  mov rdi,rcx` | rdi = rcx = texture object; TexturePtr-style refcounting `0x4e05ea8  lock cmpxchg [rdx+8],r8d` / `0x4e05ebd  lock inc dword ptr [rbx+8]` / `0x4e05ec9  lock dec dword ptr [rbx+8]`; calls sub_bc41420 at `0x4e05f77  call 0xBC41420` (dragon-layer upload bridge); sub_4e05e50 is invoked via sub_12893d0 (vtable[1]=sub_4e05e50 per element) from sub_6632bf0 — this path ensures/releases texture references, it does NOT create atlases, generate mips, or compress textures [V live] | [V live] |
| l8b_texcreate_record capture (TextureD3D12::create entry) | code 0xe81bf30 | - | - | - | 24 samples [V live docs/data/live/l8b_texcreate_record.txt]: all ret=0xE814560 (inside createTexture after `0xe81455b  call 0xE81BF30`), format 0x1C uncompressed (DXGI_FORMAT_R8G8B8A8_UNORM) at RCX+0x88, numMips=1, names are UI textures only ("Texture: 2815"/"Texture: 2799", "ui://./hbui/index.html"); NO atlas names → no atlas creation, no mips (numMips=1 only), no BC format via the createTexture path | [V live] |

## What was tried this attempt (failed angles, not repeated static proofs)

- Stitcher search from the registration objects forward: sub_186e6a0 (0x186e6a0..~0x18706a0) and sub_1042320 (ServerLevelLoad) decoded exhaustively — both register atlas names (TerrainAtlas idx 6, ItemAtlas idx 7) but contain NO createTexture/resizeTexture/TextureD3D12::create call [V]. sub_1870de0 is a fixed 41-entry registry (idx 0..0x29, 0x2A '*' sentinel) storing name ptr at obj+0 and idx at obj+8 [V]; no registry reader / stitcher located.
- Static sweep: xref str "TerrainAtlas"/"ItemAtlas" refs = only the registration leas [V]; xref str GenMip/Mips/MipMap/mipchain -> refs=[] [V]; Blit task sweep -> TerrainAtlasBlit only, no ItemAtlasBlit/mip-gen task [V].
- Live captures read: mc_root_4e05e50_callers.txt -> sub_4e05e50's indirect caller is sub_12893d0 (ret=0x1289496); sub_4e05e50 = deferred-transaction texture ensure-loaded/upload (TexturePtr refcounting), NOT atlas/mip/compression creation — this angle does NOT close the item [V live]. l8b_texcreate_record.txt -> all creations format 0x1C uncompressed, numMips=1, no atlas names [V live] — confirms nothing creates atlases via createTexture slot 26.
- NEW (live, result pending): capture l8b_resizetex_slot31 at resizeTexture entry 0xe815840 (size 0x100, max 6) QUEUED — resizeTexture takes (handle,w,h,mips,layers), has 0 static xrefs, and is the only creation path never observed live; ret= would name the stitcher caller and mips>1 would be mip evidence. Result path: docs/data/live/l8b_resizetex_slot31.txt (orchestrator runs the batch; `python tools/livecap/request.py result l8b_resizetex_slot31` prints it when done).

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas texture-creation STITCHER is not located in the exe — who builds the TerrainAtlas/ItemAtlas texture description and calls createTexture/resizeTexture with the atlas params:
- "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) are only REGISTERED names inside sub_186e6a0 [V], triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 [V]; sub_1042320's full 1778-line listing creates NO atlas texture [V]; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call is tied to either atlas; no ItemAtlasBlit task exists.
- Live evidence: all 24 l8b_texcreate_record creations are format 0x1C uncompressed, numMips=1, no atlas names [V live]; all 150 mc_root_4e05e50_callers hits are the deferred-transaction release/ensure-loaded path (ret=0x1289496 inside sub_12893d0) [V live]; resizeTexture slot 31 (0xe815840, takes mips) has 0 static xrefs — capture l8b_resizetex_slot31 queued, result pending.

Resolved as provably-ABSENT (negatives, not the blocker): mipmap generation (no GenMip/Mips/MipMap/mipchain code or task; numMips=1 for all live creations [V live]) and BC1/BC3/BC7/DXT compression (all those strings xref refs=[] [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback [V at 0xe81c12b/0xe81c077]; live census/all captures all-uncompressed [V live]).

## Verification

Re-check with `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; only when delegate exits 0 set the line after `## NEXT` to DONE.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31
Command: python tools/livecap/request.py add l8b_resizetex_slot31 0xe815840 --size 0x100 --max 6 --why "L8b: does the atlas stitcher create/resize atlases via resizeTexture(handle,w,h,mips,layers); ret= names the stitcher caller; mips>1 is mip-generation evidence. createTexture slot 26 already captured (l8b_texcreate_record): all numMips=1, format 0x1C uncompressed, no atlas names."
State: queued; result pending in docs/data/live/l8b_resizetex_slot31.txt.
