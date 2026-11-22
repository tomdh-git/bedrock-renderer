## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste the input data as-is; one annotated row per distinct offset, with all its sites listed.

## Sources read (carried from oc_U-EL8b_r1.md .. r5.md — NOT re-derived)
- oc_U-L8b.md: PNG entry 0x777ed0, IHDR 0x781550; TGA/texture_set hits are NOT decoders; "mipmap" xref -> only "OES_fbo_render_mipmap" refs=[] (no functions).
- BGFX_MAP.md: 6h L8 anchors -> PointLightShadowTextureAtlas 0xbb682b0; MaterialTerrainTextureAtlas string only, no fn. 6z/6z-2 live census: texture record +0x28 DXGI_FORMAT, flag bits incl. mip/array/msaa [I]. 6o/448: D3D format name table 0x56e3a12..0x56e42f6 incl. BC3/BC7 (data only). 1105/1107: task "TerrainAtlasBlit" functor vtable 0xF43E9E0, task 16. 1511/1512: createTexture slot 26 = 0xe8143c0 (handle, mem, flags, skip); resizeTexture slot 31 = 0xe815840 (handle, w, h, mips, layers). 1812: TextureD3D12::create 0xe81bf30 writes record +0xAF requested format, +0xB0 actual format, +0xB1 numMips; +0xB0 fallback 0x42 uncompressed.
- docs/data/live/texture_table.txt: live census 1465 textures; every format uncompressed (28/61/10/26/41/53/11/39/44; none BC1=71/BC3=77/BC7=99) [V live].
- docs/data/live/createtexture_callers.txt: capture at 0xe8143c0 (createTexture slot 26), 25 hits all ret=0xBC6A2C8 command interpreter; R8=bimg Memory* with decoded image names (cpu-decoded png/tga before upload) [V live].
- docs/data/live/l8b_texcreate_record.txt: capture at TextureD3D12::create entry 0xe81bf30; 7 hits, all ret=0xE814560, all format 0x1C uncompressed, numMips=1, no atlas names [V live].
- docs/data/live/mc_root_4e05e50_callers.txt: capture at sub_4e05e50 entry; CALLER ret=0x1289496, 150 hits/32 samples [V live]. Decoded below.

## Part 1 — Atlases (terrain, items) — carried [V] rows from r2-r5
| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| TerrainAtlasBlit task name | str data 0xf539a0b | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0 | [V] |
| TerrainAtlas registered name | str data 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas", len 0xC, registered idx 6 via sub_1870de0 inside sub_186e6a0 | [V] |
| ItemAtlas registered name | str data 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas", len 9, registered idx 7 via sub_1870de0 inside sub_186e6a0 — item atlas EXISTS as a registered name | [V] |
| registration index store | registered obj +8 | 4 | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| TerrainAtlasBlit blit body (_Do_call) | code 0xbc02090 | - | vtable 0xF43E9E0 slot 2 | - | vtable slot 2 = sub_bc02090 (size 0x3da): reads atlas fields a0+0x88/0x8C/0x98/0x9C/0x48/0xDC/0x11C, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 | [V] |
| BlitUncompressed key | str data 0xf5f440c | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| Item-atlas texture creation | none | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task | [?] |
| sub_186e6a0 registration dispatcher | code 0x186e6a0 | - | - | `0x186e6e4  mov edx,0x18` | sub_186e6a0 (0x186e6a0..0x18706a0, 2 xrefs in): registration loop allocs objects via sub_eea6040 and registers named objects through sub_1870de0; five atlas names among registrations; NO createTexture/resizeTexture call anywhere inside sub_186e6a0 | [V] |
| registration helper sub_1870de0 | code 0x1870de0 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | sub_1870de0: allocs 0x48-byte object via sub_eea6040 (`0x1870e70 mov edx,0x48; 0x1870e75 call qword ptr [0xF99FFA0]`); name ptr at obj+0 (`0x1870ec5 mov [rsi],rax`), index r9d at obj+8; called with r9d=6/7/8/0x26/0xA | [V] |

## Part 2 — mipmaps — carried [V] rows from r2-r5
| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte written to texture record inside TextureD3D12::create sub_e81bf30; dl loaded at 0xe81c0cd (`movzx edx,byte ptr [rbp+0x38]`) | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table data_12ADF818+0x15AC (0xe81c022 `movzx eax,word ptr [rax+r13*2+0x15AC]`) | [V] |
| uncompressed-format fallback 0x42 | code 0xe81c12b | - | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| createTexture slot 26 | code 0xe8143c0 | - | call site 0xe81455b | `0xe81455b  call 0xE81BF30` | texture creation entry (slot 26 per BGFX_MAP 1512); builds bimg params then calls TextureD3D12::create 0xe81bf30 | [V] |
| resizeTexture slot 31 | code 0xe815840 | - | - | - | resizeTexture (handle,w,h,mips,layers) per BGFX_MAP 1505/1512; mips can be specified on resize; indirect vtable slot dispatch, 0 static xrefs in | [V] |
| mip generation function | none | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; Blit task sweep -> no mip-gen task [V]; numMips only stored at +0xB1 [V]; sampler bit 10 is mip FILTER (usage, not generation) [I] | [?] |

## Part 3 — compression — carried [V]/[I] rows from r2-r5
| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 and related name strings; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xf58ff5a | - | 0x766542, 0x77b498 | refs in 0x765330 and PNG decoder 0x777ed0 | references are PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xf5e339b | - | 0x19958c8, 0x199594f, 0x1995a11 | refs inside 0x1994f90 | image (PNG zlib) decompression, called from PNG decoder dispatcher | [V] |
| D3D format name table | data 0x56e3a12..0x56e42f6 | - | - | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | none | - | none | - | provably ABSENT: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback [V at 0xe81c12b/0xe81c077]; live census all-uncompressed [V live] | [V] |

## NEW ANGLE — mc_root_4e05e50_callers.txt decode (live capture at sub_4e05e50 entry)
sub_4e05e50 is a per-texture-object processing function (texture release/deferred transaction), NOT atlas creation. RCX = texture object with format 0x1C at offset 0x5C and name strings ("tex", "_spear", ".legs") at offsets 0x64-0x6C. The capture shows 32 samples all with ret=0x1289496, confirming a single indirect call site.

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | code 0x4e05e50 | - | - | `0x4e05e6e  mov rdi,rcx` | rdi = rcx = texture object (this). 0 xrefs in — indirect call only | [V live] |
| [rcx+0x18] read | struct +0x18 | 8 (qword) | 0x4e05e71 | `0x4e05e71  mov rax,[rcx+0x18]` | reads [rcx+0x18] pointer; if non-zero, releases via sub_eea6040 thunk | [V live] |
| [rcx+0x58] write target | struct +0x58 | 8 (lea qword) | 0x4e05e7e | `0x4e05e7e  lea rdx,[rdi+0x58]` | lea rdx = &[rcx+0x58] passed as 2nd arg to sub_eea6040 | [V live] |
| [[rcx+0x18]+0x10] read | struct +0x18+0x10 | 8 (qword) | 0x4e05e82 | `0x4e05e82  mov rax,[rax+0x10]` | rax = [[rcx+0x18]+0x10] = vtable function ptr passed in rax to thunk | [V live] |
| call sub_eea6040 thunk | code 0x4e05e86 | - | 0x4e05e86 | `0x4e05e86  call qword ptr [0xF99FFA0]` | calls sub_eea6040 which does `jmp rax` (tail-call to vtable function = sub_4e05e50 via recursive path) | [V live] |
| [rcx+0x10] read | struct +0x10 | 8 (qword) | 0x4e05e8c | `0x4e05e8c  mov rdx,[rdi+0x10]` | reads [rcx+0x10] refcounted pointer | [V live] |
| [rcx+0x10]+8 refcount | struct +0x10+8 | 4 (dword) | 0x4e05e95 | `0x4e05e95  mov eax,[rdx+8]` | reads refcount at [rcx+0x10]+8 | [V live] |
| atomic refcount inc | struct +0x10+8 | 4 (dword) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | atomic compare-exchange refcount increment (TexturePtr add_ref pattern) | [V live] |
| [rcx+0x8] read | struct +0x8 | 8 (qword) | 0x4e05eb0 | `0x4e05eb0  mov rcx,[rdi+8]` | reads [rcx+0x8] pointer | [V live] |
| refcount inc at [rbx+8] | struct +8 | 4 (dword) | 0x4e05ebd | `0x4e05ebd  lock inc dword ptr [rbx+8]` | refcount increment | [V live] |
| refcount dec at [rbx+8] | struct +8 | 4 (dword) | 0x4e05ec9 | `0x4e05ec9  lock dec dword ptr [rbx+8]` | refcount decrement; if zero, destroys object | [V live] |
| [rbx] vtable read | struct +0 | 8 (qword) | 0x4e05ecf | `0x4e05ecf  mov rax,[rbx]` | reads vtable pointer from object | [V live] |
| [[rbx]+0] vtable slot 0 | struct +0+0 | 8 (qword) | 0x4e05ed2 | `0x4e05ed2  mov rax,[rax]` | reads vtable slot 0 (destructor?) | [V live] |
| call sub_eea6040 thunk #2 | code 0x4e05ed8 | - | 0x4e05ed8 | `0x4e05ed8  call qword ptr [0xF99FFA0]` | calls sub_eea6040 thunk | [V live] |
| refcount dec at [rbx+0xC] | struct +0xC | 4 (dword) | 0x4e05ede | `0x4e05ede  lock dec dword ptr [rbx+0xC]` | refcount decrement at +0xC | [V live] |
| [[rbx]+8] vtable slot 1 | struct +0+8 | 8 (qword) | 0x4e05ee7 | `0x4e05ee7  mov rax,[rax+8]` | reads vtable slot 1 | [V live] |
| call sub_eea6040 thunk #3 | code 0x4e05eee | - | 0x4e05eee | `0x4e05eee  call qword ptr [0xF99FFA0]` | calls sub_eea6040 thunk | [V live] |
| [rcx+0x10] re-read | struct +0x10 | 8 (qword) | 0x4e05f04 | `0x4e05f04  mov rcx,[rdi+0x10]` | re-reads [rcx+0x10] for second refcount phase | [V live] |
| [rcx+0x10]+8 refcount re-read | struct +0x10+8 | 4 (dword) | 0x4e05f0d | `0x4e05f0d  mov eax,[rcx+8]` | re-reads refcount | [V live] |
| atomic refcount inc #2 | struct +0x10+8 | 4 (dword) | 0x4e05f17 | `0x4e05f17  lock cmpxchg [rcx+8],edx` | atomic refcount increment #2 | [V live] |
| refcount dec at [rbx+8] #2 | struct +8 | 4 (dword) | 0x4e05f27 | `0x4e05f27  lock dec dword ptr [rbx+8]` | refcount decrement #2 | [V live] |
| [[rbx]+0] vtable slot 0 #2 | struct +0+0 | 8 (qword) | 0x4e05f30 | `0x4e05f30  mov rax,[rax]` | reads vtable slot 0 again | [V live] |
| call sub_eea6040 thunk #4 | code 0x4e05f36 | - | 0x4e05f36 | `0x4e05f36  call qword ptr [0xF99FFA0]` | calls sub_eea6040 thunk | [V live] |
| refcount dec at [rbx+0xC] #2 | struct +0xC | 4 (dword) | 0x4e05f3c | `0x4e05f3c  lock dec dword ptr [rbx+0xC]` | refcount decrement at +0xC #2 | [V live] |
| [[rbx]+8] vtable slot 1 #2 | struct +0+8 | 8 (qword) | 0x4e05f45 | `0x4e05f45  mov rax,[rax+8]` | reads vtable slot 1 again | [V live] |
| call sub_eea6040 thunk #5 | code 0x4e05f4c | - | 0x4e05f4c | `0x4e05f4c  call qword ptr [0xF99FFA0]` | calls sub_eea6040 thunk | [V live] |
| null check result | local [rbp+0x40] | 8 (qword) | 0x4e05f52 | `0x4e05f52  cmp qword ptr [rbp+0x40],0` | checks if processed result is null | [V live] |
| [rcx+0xE0] read | struct +0xE0 | 8 (qword) | 0x4e05f61 | `0x4e05f61  mov r9,[rdi+0xE0]` | reads [rcx+0xE0] after refcount ops | [V live] |
| advance rdi by 0x58 | code 0x4e05f68 | - | 0x4e05f68 | `0x4e05f68  add rdi,0x58` | advances rdi by 0x58 (next texture element) | [V live] |

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 entry | code 0x12893d0 | - | - | `0x12893f4  mov rdi,rcx` | sub_12893d0 (0x12893d0..0x128b3d0, size 0x2000): array iterator calling vtable slot 1 on each element; 4 static xrefs in | [V live] |
| array start [rcx+0] | struct +0x0 | 8 (qword) | 0x1289406 | `0x1289406  mov r13,[rcx]` | r13 = array start pointer | [V live] |
| array end [rcx+8] | struct +0x8 | 8 (qword) | 0x1289409 | `0x1289409  mov r14,[rcx+8]` | r14 = array end pointer | [V live] |
| loop condition | code 0x1289424 | - | 0x1289424 | `0x1289424  cmp r13,r14` | loop: continue while r13 != r14 | [V live] |
| array stride | code 0x1289420 | - | 0x1289420 | `0x1289420  add r13,0x18` | stride 0x18 per element | [V live] |
| element ptr [r13+8] | struct +0x8 | 8 (qword) | 0x1289431 | `0x1289431  mov rcx,[r13+8]` | rcx = element pointer | [V live] |
| element refcount [rcx+8] | struct +0x8 | 4 (dword) | 0x128943a | `0x128943a  mov eax,[rcx+8]` | reads element refcount | [V live] |
| element vtable [rcx] | struct +0x0 | 8 (qword) | 0x1289486 | `0x1289486  mov rax,[rcx]` | reads element vtable pointer | [V live] |
| vtable slot 1 [rax+8] | struct +0x8 | 8 (qword) | 0x1289489 | `0x1289489  mov rax,[rax+8]` | rax = vtable[1] = sub_4e05e50 (virtual method) | [V live] |
| indirect call via thunk | code 0x1289490 | - | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | calls sub_eea6040 which does `jmp rax` -> sub_4e05e50; return address = 0x1289496 (next instr = nop) | [V live] |
| ret=0x1289496 caller | code 0x1289496 | - | 0x1289496 | `0x1289496  nop` | return address after sub_4e05e50 returns; capture confirms all 32 hits have ret=0x1289496 | [V live] |

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_6632bf0 "Deferred Texture Transactions" | code 0x6632bf0 | - | - | `0x6632c19  lea rax,[0xF54E8AF]` | references "Deferred Texture Transactions" string at data_f54e8af; extracts pointer pair from [rcx+0x18], calls sub_12893d0 | [V] |
| [rcx+0x18] pointer pair | struct +0x18 | 16 (movups) | 0x6632c28 | `0x6632c28  movups xmm0,[rcx+0x18]` | reads 16-byte pointer pair (start,end) from [rcx+0x18] | [V] |
| clear [rcx+0x0]/[rcx+0x10]/[rcx+0x20] | struct +0x0/+0x10/+0x20 | 16 (movups) | 0x6632c2f | `0x6632c2f  movups [rcx+0x20],xmm1` | clears [rcx+0x20], [rcx+0x0], [rcx+0x10] to zero | [V] |
| call sub_12893d0 | code 0x6632c55 | - | 0x6632c55 | `0x6632c55  call 0x12893D0` | calls array iterator with rcx=&saved pointer pair | [V] |

## Live capture evidence — l8b_texcreate_record (TextureD3D12::create entry 0xe81bf30)
Capture result available at docs/data/live/l8b_texcreate_record.txt (7 hits). Key: all observed texture creations go through createTexture slot 26 (ret=0xE814560) -> TextureD3D12::create 0xe81bf30. All use uncompressed DXGI_FORMAT 0x1C. No atlas names ("TerrainAtlas", "ItemAtlas") appear in any hit. All numMips=1. Confirms: compression absent, no mip generation (single-mip textures only), no atlas texture creation via this path. R8 data shows UTF-16 names like "texture: 2815" and URLs like "ui://./hbui/index.html" — these are UI textures, not atlas textures.

## Conclusion from live capture — sub_4e05e50 path is texture RELEASE, not creation
The mc_root_4e05e50_callers.txt capture decodes as follows:
- sub_4e05e50: per-texture-object function that manages refcounts (lock cmpxchg/inc/dec on [ptr+8] — classic TexturePtr/shared_ptr pattern), reads [rcx+0xE0], advances by 0x58. This is a texture RELEASE/deferred-transaction function, not a creator.
- Called via sub_eea6040 thunk (`call qword ptr [0xF99FFA0]` at 0x1289490, which does `jmp rax` where rax = vtable[1] = sub_4e05e50) from sub_12893d0 at ret=0x1289496.
- sub_12893d0 iterates an array (stride 0x18) calling vtable slot 1 on each element. Called by sub_6632bf0 ("Deferred Texture Transactions").
- This path releases texture references — it does NOT create atlases, generate mips, or compress textures.

## What was tried that failed (new angle, NOT repeated static proof)
- Static search for atlas creation: xref "ItemAtlas" gives only the registration call (0x186f7fc inside sub_186e6a0); no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task. [proven, not redone]
- Static search for mip generation: xref GenMip/Mips/MipMap/mipchain -> refs=[]; no mip-gen Blit task. [proven, not redone]
- Static search for compression: BC1/BC3/BC7/DXT1-DXT5 strings all xref refs=[]; only PNG/zlib decompression exists. [proven, not redone]
- NEW: live capture at sub_4e05e50 (docs/data/live/mc_root_4e05e50_callers.txt) — decoded the indirect caller (sub_12893d0, ret=0x1289496) and connected it to TexturePtr refcounting (sub_12893d0 reads vtable[1]=sub_4e05e50 per element via sub_eea6040 thunk at 0x1289490; sub_12893d0 is called by sub_6632bf0 "Deferred Texture Transactions"). Result: sub_4e05e50 is texture RELEASE, not atlas/mip/compression creation — this angle does NOT close the item.
- NEW: live capture at TextureD3D12::create (docs/data/live/l8b_texcreate_record.txt) — all 7 hits format 0x1C uncompressed, numMips=1, no atlas names, ret=0xE814560 via createTexture slot 26. Confirms no compression/mip/atlas via this path.

## CLOSES?
CLOSES? NO. Blocking fact: all three pending parts of the checklist item remain unproven in the exe:
1. Item-atlas texture creation NOT located — "ItemAtlas" name registered idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) but NO createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to ItemAtlas; no ItemAtlasBlit task; live texture creation shows no atlas names, all format 0x1C uncompressed, numMips=1 [V live].
2. Mipmap generation function NOT located — xref GenMip/Mips/MipMap/mipchain -> refs=[] [V via xref]; no mip-gen Blit task [V]; numMips=1 for all 7 live-observed texture creations [V live]; no generator code found.
3. Compression provably ABSENT [V] — BC1/BC3/BC7/DXT1-DXT5 strings all xref refs=[] [V via xref]; only PNG/zlib decompression exists [V]; all 1465 live textures uncompressed [V live]; all 7 l8b_texcreate_record hits format 0x1C uncompressed [V live]; create path selects uncompressed 0x42 fallback [V at 0xe81c12b/0xe81c077].

What IS proven [V]: terrain atlas "TerrainAtlas" idx 6 and item atlas "ItemAtlas" idx 7 both registered inside sub_186e6a0 via sub_1870de0; TerrainAtlasBlit task name [V] and blit body sub_bc02090 [V]; texture record +0xB1 numMips and +0xB0 actual format [V]; material mip keys [V]. But the mc_root_4e05e50_callers capture (new angle) reveals sub_4e05e50 is a texture release/deferred-transaction path via TexturePtr refcounting — not atlas/mip/compression creation. Static analysis is exhausted; these features are data-driven / external to the exe (textures CPU-decoded from png/tga then uploaded uncompressed per createtexture_callers.txt [V live]).

## Verification
Re-check with `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`.

## TOOL REQUESTS
CAPTURE REQUESTED l8b_texcreate_record (done — result in docs/data/live/l8b_texcreate_record.txt)
CAPTURE REQUESTED mc_root_4e05e50_callers (done — result in docs/data/live/mc_root_4e05e50_callers.txt)
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files; no throwaway scripts written).
