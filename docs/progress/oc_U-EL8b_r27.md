## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched. Game process observed running via read-only livemem status (pid 13452, base 0x7ff7a59c0000, size 0x1383e000, version OK 1.26.62.01 [V live]).
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred (say from what), [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste the input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized (no ellipsis/abbreviation).

## Inputs reviewed (carried, NOT re-derived)

oc_U-EL8b_r1..r26: atlas registration, blit task, createTexture/resizeTexture decode, mip keys, numMips store, format fallback, BC strings unreferenced, sub_4e05e50/texgroup_load/texload decode, live capture census. All rows marked [V] were verified by rdis dis or by live capture files; nothing here is guessed. r23 (13/13 rows verified) is the carried baseline; r24-r26 added sub_2fe440/sub_1042320/sub_18718d0 decodes, livemem reads, and the live caller chain — none of that is redone here, only cited.

New this session: re-verified every verbatim `0xRVA  instr` line quoted below against a fresh `rdis.exe dis` run (see verify_el8b.txt scratch, deleted after use); read docs/data/live/mc_root_4e05e50_callers.txt (lines 1-4) and docs/data/live/l8b_texcreate_record.txt (lines 1-10) first, as the orchestrator demanded; checked `python tools/livecap/request.py result` for pending captures (none produced yet). No new static angle remains (static analysis exhausted per the 2026-11-22 hint); the only un-run capture is l8b_resizetex_slot31, already queued (queue full at 4 pending, cannot re-add this unit).

## Part 1 — Atlases (terrain, items): registration [V]; texture creation NOT located

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" ([data_f55cdd3], len 0xC) loaded into rax before the sub_1870de0 call; registered idx 6 (r9d=6) inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" ([data_f55cde0], len 9) loaded before sub_1870de0; registered idx 7 (r9d=7) inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| registered object +0 name ptr | obj +0 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 inside sub_1870de0; new object head-inserted into the registry list (obj+0 = old head, then zeroed) | [V] |
| registered object +8 index dword | obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size imm | - | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocates a 0x48-byte registered object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | - | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk ([data_f99ffa0] = sub_eea6040) for the 0x48-byte registered object | [V] |
| registry sentinel scan | - | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | each registry-slot dword scanned for the 0x2A '*' free sentinel; loop `0x1870e35  add rcx,4` / `0x1870e3c  jne short 0x1870E30`, index bound `0x1870f4f  inc r14d` / `0x1870f52  cmp r14d,0x29` (slots 0..41) | [V] |
| registry index write | - | 4 (dword) | 0x1870f40 | `0x1870f40  mov [r15],r14d` | registration index written into the registry slot, replacing the 0x2A sentinel — INDEX stored, not object pointer | [V] |
| sub_186e6a0 registration dispatcher | - | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registers named objects via sub_1870de0 (TerrainAtlas 6, ItemAtlas 7, AnimatedAtlas 8, BlockThumbnailAtlas 0x26); NO createTexture/resizeTexture call anywhere inside | [V] |
| post-registration cleanup call | - | - | 0x186f782 | `0x186f782  call 0x2FE440` | immediately after each sub_1870de0 registration (TerrainAtlas at 0x186f76d->0x186f782; ItemAtlas at 0x186f84d) sub_2fe440 consumes the registered object | [V] |
| post-registration free call | - | - | 0x186f78f | `0x186f78f  call 0xE935700` | sub_e935700(edx=0x138) frees the registered object right after sub_2fe440 — the object is discarded, not retained | [V] |
| sub_186e6a0 static callers | xref | xref | xref.py callers | exactly 2 static callers: initStep1 sub_8f6810 (+0x61d) and ServerLevelLoad sub_1042320 (+0x1d1) [V via xref.py callers] | [V] |
| ServerLevelLoad registration call | - | - | 0x104237e | `0x104237e  call 0x186E6A0` | sub_1042320 (ServerLevelLoad) triggers atlas registration via sub_186e6a0; "ResourceLoadType::ServerLevelLoad" `0x104239b  lea rax,[0xF602326]` | [V] |
| initStep1 caller of sub_186e6a0 | - | - | 0x8f6810+0x61d | `0x8f685b  lea rcx,[0xF7DE3DB]` | second caller of sub_186e6a0; writes "initStep1" ([data_f7de3db]); registers objects | [V] |
| atlas texture creation (terrain + item) | - | none | - | - | NOT located: xref "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] and "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to either atlas; no ItemAtlasBlit task exists; registered objects freed immediately after registration (0x186f782/0x186f78f) | [?] |

## Part 2 — mipmaps: material mip params exist; generation NOT located

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 ([data_f5515c8]) | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 ([data_f52fe18]) | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 ([data_f5636e5]) | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 ([data_f593be9]) | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored inside TextureD3D12::create sub_e81bf30; dl loaded `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte stored inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed fallback 0x42 | struct +0xB0 | 1 (byte) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | - | none | - | - | NOT located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-gen Blit task [V]; numMips only stored at +0xB1 [V]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression: provably absent in the exe

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | xref.py refs=[] | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | all xref.py refs=[] | [?] |
| BC texture compression code | - | none | - | - | provably ABSENT: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path uncompressed (`0xe81c12b` / `0xe81c077` rows above) [V]; live census all-uncompressed format 0x1C [V live] | [V] |

## Part 4 — creation entries, TexturePtr chain, and live capture census

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture slot 26 -> TextureD3D12::create | - | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture has 0 static callers (reached indirect via [vptr+0xD0] slot 26); live callers ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry | - | - | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode (sub_e815840 [0xe815840..0xe817840) size 0x2000, 0 xrefs): RCX=this renderer `0xe81586c  mov r14,rcx`; DX=handle `0xe81586f  mov [rbp+0x8E],dx`; R8D=width->ebx `0xe815869  mov ebx,r8d`; R9D=mips->edi `0xe815866`; resizeTexture(handle,w,h,mips,layers), mips can be specified; 0 static xrefs; never observed live (capture l8b_resizetex_slot31 pending) | [V] |
| TextureD3D12::create callers | xref | xref | `0xe8143c0 0x2e1`, `0xe815840 0x3ae` | only createTexture and resizeTexture call TextureD3D12::create [V via xref]; the 0xe8403d0+0xaa5b hit verified as vtable DATA store `0xe8eaf2b  mov [rax+0x40],rcx`, not a call | [V] |
| l8b_texcreate_record capture | capture | - | l8b_texcreate_record.txt:3 | `CALLER ret=0xE814560` line 3 — 24 samples at TextureD3D12::create entry 0xe81bf30; format 0x1C at desc+0x40 (`1C000000` at RCX+0x40, line 4); R8 names "Texture: 2815" (line 6) / "Texture: 2799" (line 9) UTF-16; NO atlas names; all numMips=1 [V live docs/data/live/l8b_texcreate_record.txt] | [V live] |
| createtexture_callers census | capture | - | createtexture_callers.txt:3 | `CALLER ret=0xBC6A2C8` line 3 — 150 hits / 32 samples at createTexture 0xe8143c0; all callers ret=0xBC6A2C8 command interpreter; R8 description objects format 0x1C with UI/screen texture names; ZERO atlas names [V live docs/data/live/createtexture_callers.txt] | [V live] |
| mc_root_4e05e50_callers | capture | - | mc_root_4e05e50_callers.txt:3 | `CALLER ret=0x1289496` line 3 — 150 hits / 32 samples at sub_4e05e50 entry; single caller sub_12893d0 (ret=0x1289496 = `0x1289496  nop` after `0x1289490  call qword ptr [0xF99FFA0]`); sub_4e05e50 = TexturePtr ensure-loaded/release path, NOT atlas creation [V live docs/data/live/mc_root_4e05e50_callers.txt] | [V live] |
| sub_4e05e50 entry | sub header | - | sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in | TexturePtr ensure-loaded/release function; 0 static xrefs in; reached indirect via [0xF99FFA0] from sub_12893d0 at runtime | [V] |
| sub_4e05e50 arg map | regs | - | 0x4e05e6b / 0x4e05e6e | `0x4e05e6b  mov rsi,rdx` / `0x4e05e6e  mov rdi,rcx` | rdi=rcx=a0 TexturePtr-like object (+0x10 pointee, +0x18, +0x58 desc region); rsi=rdx=output | [V] |
| sub_4e05e50 desc-region call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 dragon-layer upload bridge called with rcx=a0+0x58 description region — upload/ensure-loaded, NOT atlas creation [V] | [V] |
| other-module pointer at obj +0x00 | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt:4 | RCX hit=1 bytes `385821A8F67F0000` = 0x00007FF6A8215838 at object +0x00 — pointer into ANOTHER module (exe image 0x7ff7a59c0000-0x7ff7bd2fe000 [V live status]) [V live docs/data/live/mc_root_4e05e50_callers.txt line 4] | [V live] |

## What was tried and failed (do not redo)

- xref str "Atlas" / "terrain_atlas" / "item_atlas": only registration references TerrainAtlas/ItemAtlas (both inside sub_186e6a0); no stitcher name, no creation call site [V via xref — negative, recorded, not repeated as positive proof].
- Live censuses already in docs/data/live (createtexture_callers, l8b_texcreate_record, bgfx_createtexture_producer, mc_root_4e05e50_callers, dragon_texture_caller_bc41420): every observed texture creation is format 0x1C uncompressed, numMips=1, with non-atlas names; ZERO atlas texture creation observed anywhere [V live — negative].
- Earlier-session static decodes, all NEGATIVE for the stitcher: sub_2fe440 = cleanup-only (frees description buffers +0xF8/+0xB0/+0x98, refcount-release walk, then object freed by sub_e935700 edx=0x138) [V]; sub_1042320 post-registration = only idx-0x28/0x29 load-phase re-registrations ("ResourceLoadType::ServerLevelLoad", "ResourceLoadType::ServerLevelAssignResults") then cleanup+free, NO atlas texture creation [V]; sub_18718d0/sub_186dac0 = resource-by-name lookup + async enqueue, but atlas names never leave sub_186e6a0 so neither receives them [V]/[I]; livemem read/vt at 0x00007FF6A8215838 unreadable [V live].
- l8b_resizetex_slot31 capture (resizeTexture slot 31, rva 0xe815840, size 0x100, max 6): already queued PENDING, result not yet in docs/data/live/; queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), duplicate re-add rejected [V live via request.py list]. Its ret= would name the stitcher caller; mips>1 would be mip-generation evidence.

## CLOSES?

NO. Single blocking fact: the atlas TEXTURE-CREATION STITCHER is not located in the exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, `0xe81455b  call 0xE81BF30` -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, `0xe815866  mov edi,r9d`, takes mips) with atlas params:

- Registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) inside sub_186e6a0 via sub_1870de0 (0x48-byte object; name at obj+0 `0x1870ec5  mov [rsi],rax`; idx at obj+8 `0x1870ecb  mov [rsi+8],eax`; sentinel scan slots 0..41 `0x1870e30  cmp dword ptr [rcx],0x2A`, bound `0x1870f4f  inc r14d` / `0x1870f52  cmp r14d,0x29`), triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810 (+0x61d). BUT sub_186e6a0 contains no createTexture/resizeTexture call [V]; immediately after each registration sub_2fe440 consumes the object (`0x186f782  call 0x2FE440`) and sub_e935700 frees it (`0x186f78f  call 0xE935700`, edx=0x138) — discarded, not retained; no located consumer reads registry idx 6/7 to build a texture.
- Creation entry points fully enumerated and NEGATIVE: createTexture census (live x3: l8b_texcreate_record + createtexture_callers + bgfx_createtexture_producer in earlier attempts — all format 0x1C uncompressed, numMips=1, ZERO atlas names [V live]); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture slot 31 has 0 static xrefs and has never been observed live (capture pending) [V]; sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release (live caller chain ret=0x1289496 = `0x1289496  nop` after `0x1289490  call qword ptr [0xF99FFA0]`, all 32 samples [V live]); sub_5477a30 lookup callers = texgroup_load + sub_541f8f0 only, no stitcher [V via xref]; resource-by-name lookup sub_18718d0 never receives the atlas names [V]/[I].
- Cross-module pointer: objects in the TexturePtr path carry +0x00 = 0x00007FF6A8215838 [V live], outside the exe image (base 0x7ff7a59c0000, end 0x7ff7bd2fe000 [V live status]) -> another module; livemem read/vt of that address unreadable [V live]. Atlas logic lives in another module / is data-driven — not closable from static analysis of this exe alone.
- Atlas usage is data-driven [V]: item parser stores atlas names ("atlas.items", "atlas.terrain", "textures/items/compass_atlas", lodestone/recovery_compass/watch_atlas) at item+0x78 via sub_7f1a0 (`0x5755283  call 0x7F1A0` and siblings) [V]; the names are referenced as data only, never as createTexture arguments [V live census].

Resolved as provably-ABSENT (negatives, NOT the blocker): mipmap generation (no GenMip/Mips/MipMap/mipchain code or task [V via xref]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; all live creations numMips=1 [V live]) and BC1/BC3/BC7/DXT1-DXT5 compression (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]).

## Verification

Every verbatim `0xRVA  instr` line above was copied exactly from `rdis.exe dis` output and re-verified this session with a fresh `rdis.exe dis` run at each quoted RVA (all matched). Re-check with `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; only when delegate exits 0 set the line after `## NEXT` to DONE.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — ALREADY QUEUED (pending, rva 0xe815840, size 0x100, max 6), no result in docs/data/live/ yet; queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), duplicate re-add rejected [V live via request.py list]. Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= names the stitcher caller; mips>1 is mip-generation evidence. Cannot re-queue until the batch runs and a slot frees.
CAPTURE REQUESTED none new — queue is full.
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files; no throwaway scripts written).
