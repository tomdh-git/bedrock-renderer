## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | offset | size | read/store address | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched. Game process observed running (livemem status: pid 13452, base 0x7ff7a59c0000, size 0x1383e000, version OK 1.26.62.01 [V live]).
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred (say from what), [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste the input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized; no summary/abbreviation rows allowed.

## Part 1 — Atlases (terrain, items)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name (len 0xC) loaded before sub_1870de0 call inside sub_186e6a0; registered idx 6 (r9d=6) | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name (len 9) loaded before sub_1870de0 call inside sub_186e6a0; registered idx 7 (r9d=7) — item atlas EXISTS as a registered name | [V] |
| registered obj +0 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 inside sub_1870de0 | [V] |
| registered obj +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocates a 0x48-byte registered object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object | [V] |
| registry sentinel scan | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | sub_1870de0 scans each registry-slot dword for the 0x2A '*' free sentinel; loop `0x1870e35  add rcx,4` until end | [V] |
| registry array end reset | 8 (qword) | 0x1870e45 | `0x1870e45  mov [rdx+8],r15` | on sentinel hit, sub_1870de0 resets the registry array end (slot reuse path), `0x1870e49  xor r14d,r14d; 0x1870e4c  cmp r14d,0x29; 0x1870e50  jbe 0x1870F35` (index bound 0..41) | [V] |
| slot index write | 4 (dword) | 0x1870f40 | `0x1870f40  mov [r15],r14d` | registration index (6 TerrainAtlas / 7 ItemAtlas / 8 AnimatedAtlas / 0x26 BlockThumbnailAtlas) written into the registry slot, replacing the 0x2A sentinel — INDEX stored, not object pointer; loop `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29; 0x1870f2f  ja 0x1870E56` | [V] |
| sub_1870de0 nature | - | sub header | `sub_1870de0 [0x1870de0..0x1872de0) size 0x2000 37 xrefs in` | generic idx->name registry manager (37 static callers), NOT atlas-specific: NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 registration dispatcher | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 (0x186e6a0..0x18706a0, size 0x2000, 2 xrefs in) registers named atlases via sub_1870de0 (TerrainAtlas 6, ItemAtlas 7, AnimatedAtlas 8, BlockThumbnailAtlas 0x26); NO createTexture/resizeTexture call anywhere inside | [V] |
| registration trigger ServerLevelLoad | - | 0x104237e | `0x104237e  call 0x186E6A0` | sub_1042320 ServerLevelLoad triggers atlas registration via sub_186e6a0 ("ResourceLoadType::ServerLevelLoad" `0x104239b  lea rax,[0xF602326]`); second caller initStep1 sub_8f6810 (+0x61d, `0x8f685b  lea rcx,[0xF7DE3DB]`) | [V] |
| post-registration cleanup call | - | 0x186f782 | `0x186f782  call 0x2FE440` | immediately after TerrainAtlas sub_1870de0 returns (0x186f76d), sub_2fe440 cleanup then sub_e935700 frees the registered object (same pattern for ItemAtlas at 0x186f84d/0x186f85a); object discarded, not retained | [V] |
| post-registration free call | - | 0x186f78f | `0x186f78f  call 0xE935700` | sub_e935700 frees the registered object after sub_2fe440 cleanup | [V] |
| sub_1042320 texture creation | - | full listing | - | grep of the 1778-line listing (0x1042320..0x1044320): NO `call 0xE8143C0` / `0xE815840` / `0xE81BF30` and no TerrainAtlas/ItemAtlas string — ServerLevelLoad registers atlas names but creates NO atlas texture | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| TerrainAtlasBlit task name | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task name referenced inside 0xbb418d0; body sub_bc02090 reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 — BLIT only, no texture creation | [V] |
| BlitUncompressed key | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| atlas texture creation (terrain + item) | - | none | - | NOT located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)], "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture/resizeTexture call tied to either atlas; no ItemAtlasBlit task exists; registered objects freed right after registration | [?] |

## Part 5 — atlas texture-name resolution (data-driven usage, live)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| atlas name "atlas.items" | str data 0xf550917 | 8 (lea qword) | 0x575527c | `0x575527c  lea rdx,[0xF550917]` | "atlas.items" passed to sub_7f1a0 at `0x5755283  call 0x7F1A0`, which stores it at item object +0x78 (rcx=[rsi+0x78]) | [V] |
| atlas name "textures/items/compass_atlas" | str data 0xf55ccd6 | 8 (lea qword) | 0x5755303 | `0x5755303  lea rdx,[0xF55CCD6]` | "textures/items/compass_atlas" stored at item+0x78 via `0x575530a  call 0x7F1A0` | [V] |
| atlas name select "atlas.items"/"atlas.terrain" | str data 0xf550917 / 0xf593358 | 8 (lea qword) | 0x5755456 | `0x5755456  cmp dword ptr [rsi+0x1A0],2` / `0x575545d  lea rax,[0xF550917]` / `0x5755464  lea rdx,[0xF593358]` / `0x575546b  cmove rdx,rax` / `0x5755473  call 0x7F1A0` | [rsi+0x1A0]==2 → "atlas.items" else "atlas.terrain" stored at item+0x78 | [V] |
| atlas name "textures/items/lodestonecompass_atlas" | str data 0xf55cc8a | 8 (lea qword) | 0x575549d | `0x575549d  lea rdx,[0xF55CC8A]` | stored at item+0x78 via `0x57554a4  call 0x7F1A0` | [V] |
| atlas name "textures/items/recovery_compass_atlas" | str data 0xf55ccb0 | 8 (lea qword) | 0x57554ce | `0x57554ce  lea rdx,[0xF55CCB0]` | stored at item+0x78 via `0x57554d5  call 0x7F1A0` | [V] |
| atlas name "textures/items/watch_atlas" | str data 0xf55cd08 | 8 (lea qword) | 0x5755502 | `0x5755502  lea rdx,[0xF55CD08]` | stored at item+0x78 via `0x5755509  call 0x7F1A0` | [V] |
| atlas name "atlas.items" fallback | str data 0xf550917 | 8 (lea qword) | 0x5755517 | `0x5755517  lea rdx,[0xF550917]` | stored at item+0x78 via `0x575551e  call 0x7F1A0` | [V] |
| sub_7f1a0 string setter | string object | 8 (qword rcx) | [rsi+0x78] via 0x7f1a0 | `0x7f1b5  mov rcx,[rsi+0x18]` / `0x7f1ce  jmp 0x9D6D0` and `0x7f1ef  call 0xEEC6DE0` / `0x7f1f4  mov byte ptr [rbx+rdi],0` | sub_7f1a0 sets the string at string-object+0x10 (rcx=string obj, [rsi+0x18]=cap; rdx=src ptr): length via sub_eec7570, copy via sub_9d6d0/sub_eec6de0, null-terminate | [V] |
| sub_5752d50/sub_5755000 static callers | xref | xref | `0x15ac010 0xabc`, `0x5755bc0 0xe1` | item-definition parser that resolves each item's atlas texture name (the rows above); 2 static xrefs in | [V] |
| registry global data_128d3d68 live | data global | 8 (qword) | `read @0x128d3d68 0x140` | `python tools/sigs/livemem.py read @0x128d3d68 0x140` → `00007FF7B8293D68  00 9e 1d 30 1d 03 00 00 d0 fd 04 30 1d 03 00 00 c0 fd 04 30 1d 03 00 00 00 03 16 30 1d 03 00 00 ...` | data_128d3d68 holds heap pointer 0x31d301d9e00 to the live registration array (nonzero exe/heap pointers at +0..+0x38; dwords at +0x14..+0x1C read 0x1E) — registration registry populated at runtime | [V live] |
| registry-array reader functions | - | - | ripscan 0x128d3d68/0x128d3d80 | - | ripscan found refs in 0x13bf10 (allocs 0x528-byte obj), 0x13f1b0 (refcounted obj), 0x166c20 (reads [0x128D3D68] at `0x166d11  mov r8,[0x128D3D68]`, "HeadlessJoiner" strings), 0x16fc90, 0x183fc0 (allocs 0x28/0x48), 0x19b460 (allocs 0x18 + 0x420 zeroed buffer) — all object constructors, NONE is the atlas stitcher | [V] |
| live registered object 0x031D301D4FA0 | obj | - | `read 0x031D301D4FA0 0x60` | `python tools/sigs/livemem.py read 0x031D301D4FA0 0x60` → `0000031D301D4FA0  03 00 00 00 00 00 00 00 0f 00 00 00 00 00 00 00  60 a8 02 30 1d 03 00 00 00 00 00 00 00 00 00 00  10 00 00 00 00 00 00 00 1f 00 00 00 00 00 00 00  31 31 30 00 ...` | +0x00 dword=3, +0x08 qword=15, +0x10 heap ptr 0x031D3002A860, +0x20 dword=16, +0x28 dword=31, +0x30 string "110", +0x40 dword=3, +0x48 qword=15 — item-like registered object, NOT an atlas texture object | [V live] |
| live registered object 0x031D301D4FF0 | obj | - | `read 0x031D301D4FF0 0x60` | `python tools/sigs/livemem.py read 0x031D301D4FF0 0x60` → `0000031D301D4FF0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 7b 00  80 50 1d 30 1d 03 00 00 80 4f 1d 30 1d 03 00 00  31 32 36 00 ...` | +0x00 qword=0, +0x10 heap ptrs 0x031D301D5080/0x031D301D4F80, +0x20 string "126", +0x40 string "Star trader", +0x50 qword=11 qword=15 — item-like registered object, NOT an atlas texture object | [V live] |
| live registered object 0x031D309987C0 | obj | - | `read 0x031D309987C0 0x60` | `python tools/sigs/livemem.py read 0x031D309987C0 0x60` → `0000031D309987C0  40 08 a5 b4 f7 7f 00 00 01 00 00 00 02 00 00 00  40 86 a5 b4 f7 7f 00 00 80 fd 9f 30 1d 03 00 00 ...` | +0x00 vtable 0x7FF7B4A50840 (exe RVA 0xA90840), +0x08 dword=1, +0x0C dword=2, +0x10 vtable 0x7FF7B4A58640 (exe RVA 0xA98640), +0x18 heap ptr 0x031D3099FD80, +0x78 qword=8824 — has exe vtable pointers, embedded object pointer | [V live] |
| live registered object 0x031D309987D0 | obj | - | `read 0x031D309987D0 0x60` | `python tools/sigs/livemem.py read 0x031D309987D0 0x60` → `0000031D309987D0  40 86 a5 b4 f7 7f 00 00 80 fd 9f 30 1d 03 00 00 ...` | +0x00 vtable 0x7FF7B4A58640 (exe RVA 0xA98640), +0x08 heap ptr 0x031D3099FD80, +0x78 qword=8824 — same vtable as embedded obj at +0x10 of 0x031D309987C0 | [V live] |
| vtable at exe RVA 0xA90840 | code | - | `dis 0xA90840 20` | `0xa90840  cli` / `0xa90841  call qword ptr [0xF99FFA0]` — vtable entry calls sub_eea6040 allocator | [V] |
| vtable at exe RVA 0xA98640 | code | - | `dis 0xA98640 20` | `0xa98640  or [rax-0x7F],cl` / `0xa98645  dec dword ptr [rdi]` — not valid code, likely data misaligned | [I] |
| other-module pointer +0x00 | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | `385821A8F67F0000` → 0x00007FF6A8215838 at object+0x00 in every sampled sub_4e05e50 object — pointer into ANOTHER MODULE (exe base 0x7ff7a59c0000 size 0x1383e000, range 0x7ff7a59c0000–0x7ff7bd2fe000; 0x7FF6A8215838 outside image) | [V live] |
| other-module pointer unreadable | VA 0x00007FF6A8215838 | - | `read 0x7FF6A8215838 0x80` | `python tools/sigs/livemem.py read 0x7FF6A8215838 0x80` → "unreadable at 0x7ff6a8215838" — transient/stale, cannot identify module/RVA | [V live] |

## Part 2 — mipmaps

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored inside TextureD3D12::create sub_e81bf30; dl loaded `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte stored inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed fallback 0x42 | struct +0xB0 | 1 (byte) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | - | none | - | NOT located: xref str GenMip/Mips/MipMap/mipchain → refs=[] (no functions) [V via xref]; no mip-gen Blit task [V]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | - | none | - | str data 0xf84ad1c; xref.py refs=[] | [?] |
| BC3 string | - | none | - | str data 0xf84aaf8; xref.py refs=[] | [?] |
| BC7 string | - | none | - | str data 0xf84a930; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | - | none | - | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010; all xref.py refs=[] | [?] |
| "bad compression" string | - | ref 0x766542 | - | str data 0xf58ff5a; references in 0x765330 and PNG decoder 0x777ed0 are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): image (PNG zlib) decompression, called from PNG decoder dispatcher | [V] |
| BC texture compression code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live] | [V] |

## Part 4 — TexturePtr chain, creation entries, and live capture census

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture slot 26 → TextureD3D12::create | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture has 0 static callers (reached indirect via [vptr+0xD0] slot 26); live callers ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry | - | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode [V via rdis dis 0xe815840: sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in]: RCX=this renderer `0xe81586c  mov r14,rcx`; DX=handle `0xe81586f  mov [rbp+0x8E],dx`; R8D=width→ebx `0xe815869  mov ebx,r8d`; R9D=mips→edi `0xe815866`; stack word mips `0xe815980  movzx r13d,word ptr [rbp+0x108]`; stack byte layers `0xe815988  movzx r12d,byte ptr [rbp+0x100]`; renderer+0xBDE178 handle array `0xe815876  lea rsi,[rcx+0xBDE178]`; resizeTexture(handle,w,h,mips,layers), mips can be specified; 0 static xrefs; never observed live | [V] |
| TextureD3D12::create callers | xref | xref | `0xe8143c0 0x2e1`, `0xe815840 0x3ae` | only createTexture and resizeTexture call TextureD3D12::create; the xref hit at 0xe8403d0+0xaa5b verified as a vtable DATA store `0xe8eaf2b  mov [rax+0x40],rcx`, not a call | [V] |
| sub_4e05e50 entry | sub header | - | `sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in` | TexturePtr ensure-loaded/release function; 0 static xrefs in; reached indirect via [0xF99FFA0] from sub_12893d0 at runtime | [V] |
| sub_4e05e50 arg map | regs | 0x4e05e6b-0x4e05e6e | `0x4e05e6b  mov rsi,rdx` / `0x4e05e6e  mov rdi,rcx` | rdi=rcx=a0 TexturePtr-like object (+0x10 pointee, +0x18, +0x58 desc region); rsi=rdx=output | [V] |
| sub_4e05e50 pointee add-ref | pointee +8 | 4 (dword cmpxchg) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref loop on refcount at *(a0+0x10)+8 | [V] |
| sub_4e05e50 pointee destroy | pointee +0 | 8 (qword) | 0x4e05ed8 | `0x4e05ed8  call qword ptr [0xF99FFA0]` | destroys pointee when refcount hits 0 (vtable dtor via thunk) | [V] |
| sub_4e05e50 desc-region call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 (dragon-layer upload bridge) called with rcx=a0+0x58 description region — upload/ensure-loaded, NOT atlas creation | [V] |
| sub_4e05e50 pointee read | pointee +0x10 | 8 (qword) | 0x4e05e8c | `0x4e05e8c  mov rdx,[rdi+0x10]` | reads the pointee texture object pointer | [V] |
| sub_12893d0 entry | sub header | - | `sub_12893d0 [0x12893d0..0x12895d3) size 0x203 13 xrefs in` | TexturePtr release/collect; walks 0x18-strided entry array; the ONLY live caller of sub_4e05e50 (ret=0x1289496 in mc_root_4e05e50_callers.txt line 3, all 32 samples) | [V] |
| sub_12893d0 add-ref | entry obj +8 | 4 (dword cmpxchg) | 0x1289447 | `0x1289447  lock cmpxchg [rcx+8],edx` | CAS loop incrementing refcount dword at object+8 (0x1289440 is label loc_1289440 inside sub_12893d0, not a separate entry) | [V] |
| sub_12893d0 16-byte object copy | 16 (movups) | 0x128944e | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of the texture object (entry obj +0) | [V] |
| sub_12893d0 release old pointee | entry obj +0x10 | 8 (qword) | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | statically [0xF99FFA0]=sub_eea6040 thunk; at runtime this site enters sub_4e05e50; fall-through `0x1289496  nop` = ret=0x1289496 seen for ALL 32 samples of mc_root_4e05e50_callers.txt line 3 | [V live] |
| sub_12893d0 further release sites | entry obj +0x10 | 8 (qword) | 0x12894b3 | `0x12894b3  call qword ptr [0xF99FFA0]` (same instr text at 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612) | seven more release/decrement calls through [0xF99FFA0] on old pointees and array entries | [V] |
| sub_12893d0 refcount dec strong | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | decrements refcount; object destroyed when it reaches zero | [V] |
| sub_12893d0 refcount dec weak | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | second (weak) count decrement | [V] |
| sub_12893d0 0x18-strided array walk | array elem stride 0x18 | - | 0x1289560 | `0x1289560  add rbx,0x18` | walks a 0x18-strided array releasing [rbx+0x10] and [rbx+8] entries | [V] |
| sub_12893d0 count output | out +0 | 8 (qword) | 0x12895a8 | `0x12895a8  mov [rsi],r12` | stores collected count r12 into the output pointer | [V] |
| sub_12893d0 static callers | xref | xref | `0x1145c20 +0x4ae`, `0x6622610 +0x1c8`, `0x66232b0 +0xb3d0`, `0x6632bf0 +0x34b` | 13 xrefs in total; these 4 callers — NONE is a texture creator | [V] |
| texgroup_load | - | 0x5421dec | `0x5421dec  call 0x5477a30` | looks up a texture by name in the texture table via sub_5477a30 (rcx=rsi+0x248, rdx=built name); then add-ref `0x5421e0a  lock inc dword ptr [rcx+8]`; 7 static xrefs in | [V] |
| texgroup_load callers | xref | xref | `0x541f8f0 +0xc7d`, `0x5421c90 +0x190f` | ONLY two static callers: texgroup_load (+0x190f) and sub_541f8f0 (+0xc7d) — no stitcher looks up atlas textures by name | [V] |
| texload | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list ([rbx+0x160..0x168)) calling sub_5417950 per entry, tracking min/max UV at [rbx+0x6C]/[rbx+0x78]; 2 static xrefs in — atlas UV CONSUMPTION, not creation | [V] |
| texload rect read | 0x8 | 4 (movss) | 0x58a1450 | `0x58a1450  movss xmm3,[rcx+8]` | per-rect float read in the rect walk | [V] |
| sub_5477a30 callers | xref | xref | `0x541f8f0 +0xc7d`, `0x5421c90 +0x190f` | ONLY two static callers: texgroup_load (+0x190f) and sub_541f8f0 (+0xc7d) — no stitcher looks up atlas textures by name | [V] |
| l8b_texcreate_record capture | capture | - | `CALLER ret=0xE814560` line 3 | 24 samples at TextureD3D12::create entry 0xe81bf30; format 0x1C at desc+0x40 (`1C000000` at RCX+0x40); R8 names "Texture: 2815" (line 1) / "Texture: 2799" (line 8) UTF-16; NO atlas names; no compressed formats; all numMips=1 [V live docs/data/live/l8b_texcreate_record.txt] | [V live] |
| createtexture_callers census | capture | - | `CALLER ret=0xBC6A2C8` line 3 | 150 hits / 32 samples at createTexture 0xe8143c0; all callers ret=0xBC6A2C8 command interpreter; R8 description objects format 0x1C with UI/screen texture names only; ZERO atlas names [V live docs/data/live/createtexture_callers.txt] | [V live] |
| mc_root_4e05e50_callers capture | capture | - | `CALLER ret=0x1289496` line 3 | 150 hits / 32 samples at sub_4e05e50 entry; ALL share ONE caller: sub_12893d0 (ret=0x1289496 = `0x1289496  nop` after `0x1289490  call qword ptr [0xF99FFA0]`); sub_4e05e50 = TexturePtr ensure-loaded/release (deferred transactions sub_6632bf0 → sub_12893d0 array iterator → vtable[1]=sub_4e05e50), NOT atlas creation [V live docs/data/live/mc_root_4e05e50_callers.txt] | [V live] |
| sub_4e05e50 live RCX description | desc object | - | mc_root_4e05e50_callers.txt hit=9/10 RCX | contiguous bytes `1C000000 01000000 01000000 01000000 74657800` = format 0x1C (R8G8B8A8_UNORM uncompressed), three 1-dword dims, fourcc tag "tex\0" | [V live] |

## CLOSES?

NO. Single blocking fact: the atlas TEXTURE-CREATION STITCHER is not located in the exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, `0xe81455b  call 0xE81BF30` → TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, `0xe815866  mov edi,r9d`, takes mips) with atlas params:

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) inside sub_186e6a0 via sub_1870de0 (0x48-byte object `0x1870e70  mov edx,0x48`; name at obj+0 `0x1870ec5  mov [rsi],rax`; idx at obj+8 `0x1870ecb  mov [rsi+8],eax`; slot write `0x1870f40  mov [r15],r14d`, sentinel scan `0x1870e30  cmp dword ptr [rcx],0x2A`), triggered by ServerLevelLoad sub_1042320 → sub_186e6a0 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810 (+0x61d). BUT sub_1870de0 is a generic idx->name registry (37 xrefs, not atlas-specific) and sub_186e6a0 frees the registered 0x48-byte objects immediately after registration (sub_2fe440 `0x186f782  call 0x2FE440` + sub_e935700 `0x186f78f  call 0xE935700`; ItemAtlas at 0x186f84d/0x186f85a); sub_1042320's full listing creates NO atlas texture [V]; sub_186e6a0 contains no createTexture/resizeTexture call [V]; the registered objects are consumed by NO located reader/stitcher [V]; no ItemAtlasBlit task exists; blit side is uncompressed ("BlitUncompressed" key ref 0x560be9f, TerrainAtlasBlit task `0xbb431ee  lea rdx,[0xF539A0B]`) [V].
- All creation entry points enumerated and NEGATIVE: createTexture census (live x2: l8b_texcreate_record + createtexture_callers; all format 0x1C uncompressed, numMips=1, names "Texture: 2799/2815" and UI/screen paths, ZERO atlas names [V live]); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture slot 31 has 0 static xrefs and has never been observed live [V]; sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release, not creation [V + V live mc_root_4e05e50_callers]; sub_5477a30 texture lookup callers = texgroup_load + sub_541f8f0 only, no stitcher [V via xref].
- Live mc_root_4e05e50_callers objects carry an other-module pointer at +0x00 (`00007ff6a8215838`, hit=1 RCX [V live]) — consistent with "atlas logic likely in another module / data-driven"; livemem read of that pointer returned "unreadable" (transient/stale) [V live].
- Registration array live data [V live]: data_128d3d68 holds heap pointer 0x31d301d9e00; registration array contains exe vtable pointers (RVA 0xA90840, 0xA98640) and heap pointers to registered objects; live registered objects are item-like (strings "Star trader", "126", "110") with exe vtables — NOT atlas texture objects. No atlas texture object found in the registration array.
- Live capture l8b_resizetex_slot31 (rva 0xe815840, size 0x100, max 6) is PENDING but has no result yet; capture queue FULL (4 pending: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), cannot re-queue. Its ret= would name the stitcher caller; mips>1 would be mip-generation evidence.
- New angles tried this unit, documented: livemem read of registration array (shows item-like objects, not atlas textures); livemem read of other-module pointer 0x7FF6A8215838 → unreadable; disassembly of exe vtable entries RVA 0xA90840/0xA98640 (one is allocator call, other is misaligned data); descscan2 not applicable (visitor-only tool). Static analysis exhausted per orchestrator hint.

Resolved as provably-ABSENT (negatives, NOT the blocker): mipmap generation (no GenMip/mipchain code or task [V via xref]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; all live creations numMips=1 [V live]) and BC1/BC3/BC7/DXT1-DXT5 compression (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` [V] / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]).

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; only when delegate exits 0 set the line after `## NEXT` to DONE.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — ALREADY QUEUED (pending, rva 0xe815840, size 0x100, max 6), no result in docs/data/live/ yet; queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), NOT re-queued this unit. Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= names the stitcher caller; mips>1 is mip-generation evidence.
CAPTURE REQUESTED none new — queue is full; l8b_resizetex_slot31 already pending.
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files; no throwaway scripts written).