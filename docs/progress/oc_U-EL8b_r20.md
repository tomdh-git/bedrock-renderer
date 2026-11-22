## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #19)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched. Game process observed running (livemem status: pid 13452 base 0x7ff7a59c0000 size 0x1383e000, version OK).
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized; no summary/abbreviation rows allowed.

Inputs reviewed (NOT re-derived): oc_U-EL8b_r1..r18 (registration [V], blit [V], createTexture/resizeTexture decode [V], mip keys [V], numMips store [V], format fallback [V], BC strings unreferenced [V], sub_4e05e50/texgroup_load/texload/TexturePtr chain [V], live census [V live]). Live data read: docs/data/live/mc_root_4e05e50_callers.txt (150 hits/32 samples, DONE) and docs/data/live/l8b_texcreate_record.txt (24 samples, DONE) per docs/data/live/_status.txt; `python tools/livecap/request.py result l8b_resizetex_slot31` -> no result yet (orchestrator has not run it; capture queue full at 4, not re-queued this unit).

NEW THIS UNIT (attack on the single blocking fact — the atlas texture-creation stitcher): (1) forward trace — full decode of sub_1870de0 shows it is a generic idx->name registry manager (37 static callers, not atlas-specific) with no createTexture/resizeTexture inside; (2) livemem read `python tools/sigs/livemem.py read 0x7ff6a8215838 0x40` -> unreadable (target released/stale), so the other-module pointer at sampled-object +0x00 (0x00007FF6A8215838, outside the exe image base 0x7ff7a59c0000..0x7ff7b91fe000) cannot be identified. Both attempts failed; documented in Part 5.

## Part 1 — Atlases (terrain, items) — carried [V]/[?] rows from oc_U-EL8b_r1..r18 (NOT re-derived), registry re-decoded this unit

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| str 0xf55cdd3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name (len 0xC) loaded before sub_1870de0 call inside sub_186e6a0; registered idx 6 (r9d=6) | [V] |
| str 0xf55cde0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name (len 9) loaded before sub_1870de0 call inside sub_186e6a0; registered idx 7 (r9d=7) — item atlas EXISTS as a registered name | [V] |
| registry sentinel scan | 4 (dword) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | sub_1870de0 scans each registry-slot dword for the 0x2A '*' free sentinel; loop `0x1870e35  add rcx,4` until end | [V] |
| registry array end reset | 8 (qword) | 0x1870e45 | `0x1870e45  mov [rdx+8],r15` | on sentinel hit, sub_1870de0 resets the registry array end (slot reuse path), `0x1870e49  xor r14d,r14d`, `0x1870e4c  cmp r14d,0x29`, `0x1870e50  jbe 0x1870F35` (index bound 0..41) | [V] |
| slot index write | 4 (dword) | 0x1870f40 | `0x1870f40  mov [r15],r14d` | registration index (6 TerrainAtlas / 7 ItemAtlas / 8 AnimatedAtlas / 0x26 BlockThumbnailAtlas) written into the registry slot, replacing the 0x2A sentinel — INDEX stored, not object pointer; loop `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29; 0x1870f2f  ja 0x1870E56` | [V] |
| registered object alloc size | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocates a 0x48-byte registered object via sub_eea6040 | [V] |
| registered object alloc call | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object ([data_f99ffa0]) | [V] |
| registered object +0 | 8 (qword) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | first 8 bytes of the atlas name stored at registered object +0 | [V] |
| registered object +8 | 4 (dword) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index stored at registered object +8 | [V] |
| sub_1870de0 nature | - | sub header | `sub_1870de0 [0x1870de0..0x1872de0) size 0x2000 37 xrefs in` | generic idx->name registry manager (37 static callers), NOT atlas-specific: NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 registration dispatcher | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 (0x186e6a0..0x18706a0, size 0x2000, 2 xrefs in) registers named atlases via sub_1870de0; NO createTexture/resizeTexture call anywhere inside | [V] |
| registration trigger | - | 0x104237e | `0x104237e  call 0x186E6A0` | sub_1042320 ServerLevelLoad triggers atlas registration via sub_186e6a0 ("ResourceLoadType::ServerLevelLoad" `0x104239b  lea rax,[0xF602326]`); second caller initStep1 sub_8f6810 (+0x61d, `0x8f685b  lea rcx,[0xF7DE3DB]`) | [V] |
| post-registration cleanup | - | 0x186f782 | `0x186f782  call 0x2FE440` | immediately after TerrainAtlas sub_1870de0 returns (0x186f76d), sub_2fe440 cleanup then sub_e935700 frees the registered object (same pattern for ItemAtlas at 0x186f84d/0x186f85a); object discarded, not retained | [V] |
| post-registration free | - | 0x186f78f | `0x186f78f  call 0xE935700` | sub_e935700 frees the registered object after sub_2fe440 cleanup | [V] |
| sub_1042320 ServerLevelLoad listing | - | full listing | - | grep of the 1778-line listing (0x1042320..0x1044320): NO `call 0xE8143C0` / `0xE815840` / `0xE81BF30` and no TerrainAtlas/ItemAtlas string — ServerLevelLoad registers atlas names but creates NO atlas texture | [V] |
| MaterialTerrainTextureAtlas string | str data 0xf55ce1b | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it; BGFX_MAP.md L337: "string only, referenced via table") | [?] |
| TerrainAtlasBlit task name | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task name referenced inside 0xbb418d0 (BGFX_MAP.md L336 PointLightShadowTextureAtlas at 0xbb682b0 is a different atlas); body sub_bc02090 reads atlas fields, constant uploads via sub_ebce390 to cbv data_12AE1748, draw loop via sub_e7ebfc0 stride 0x28 — BLIT only, no texture creation | [V] |
| BlitUncompressed key | - | ref 0x560be9f | - | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| atlas texture creation (terrain + item) | - | none | - | NOT located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] and "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture/resizeTexture call tied to either atlas; no ItemAtlasBlit task exists; registered objects freed right after registration | [?] |

## Part 2 — mipmaps — carried [V]/[I]/[?] rows from oc_U-EL8b_r1..r13 (NOT re-derived)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| num_mip_levels material key | str data 0xf5515c8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xf52fe18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xf5636e5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xf593be9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored inside TextureD3D12::create (sub_e81bf30); dl loaded `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte stored inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| mip generation function | - | none | - | NOT located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-gen Blit task [V]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; sampler bit 10 is mip FILTER (usage, not generation) [I] (BGFX_MAP.md 6ao); all live creations numMips=1 [V live] | [?] |

## Part 3 — compression — carried [V]/[I]/[?] rows from oc_U-EL8b_r1..r13 (NOT re-derived)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| BC1 string | str data 0xf84ad1c | - | none | - | BC1/DXT1 format name; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xf84aaf8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xf84a930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xf7ddd18, 0xf7d3d04, 0xf7d6ac8, 0xef3ffec-0xef40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 name strings; all xref.py refs=[] | [?] |
| BC compression code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V] (mce::ImageUtils::decompressImage refs inside 0x1994f90); create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` [V]; D3D format name table (BGFX_MAP.md L448) lists BC3/BC7 names as DATA only, no compression code path [I]; live census all-uncompressed [V live] | [V] |

## Part 4 — texture creation entries, TexturePtr/texgroup/texload chain, and live census

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| createTexture slot 26 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (slot 26) builds bimg params then calls TextureD3D12::create 0xe81bf30; 0 static callers (reached indirect via [vptr+0xD0]); live callers all ret=0xBC6A2C8 command interpreter; R8 description objects format 0x1C, UI/screen texture names only, ZERO atlas names [V live createtexture_callers.txt] | [V] |
| TextureD3D12::create callers | - | xref | - | `0xe8143c0 0x2e1`, `0xe815840 0x3ae`: only createTexture (slot 26) and resizeTexture (slot 31) call TextureD3D12::create; the 0xe8403d0+0xaa5b hit verified as a vtable DATA store `0xe8eaf2b  mov [rax+0x40],rcx`, not a call | [V] |
| resizeTexture slot 31 entry | - | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode `sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in`: RCX=this renderer `0xe81586c  mov r14,rcx`; DX=handle `0xe81586f  mov [rbp+0x8E],dx`; R8D=width->ebx `0xe815869  mov ebx,r8d`; R9D=mips->edi; stack word mips `0xe815980  movzx r13d,word ptr [rbp+0x108]`; stack byte layers `0xe815988  movzx r12d,byte ptr [rbp+0x100]`; renderer+0xBDE178 handle array `0xe815876  lea rsi,[rcx+0xBDE178]`; resizeTexture(handle,w,h,mips,layers), mips can be specified; 0 static xrefs (indirect vtable dispatch only); never observed live | [V] |
| sub_4e05e50 entry | - | sub header | `sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in` | TexturePtr ensure-loaded/release; 0 static xrefs; reached only indirectly via [0xF99FFA0] from sub_12893d0 at runtime | [V] |
| sub_4e05e50 arg map | - | 0x4e05e6b / 0x4e05e6e | `0x4e05e6b  mov rsi,rdx` / `0x4e05e6e  mov rdi,rcx` | rdi=rcx=a0 TexturePtr-like object (+0x10 pointee, +0x18, +0x58 desc region); rsi=rdx=output | [V] |
| sub_4e05e50 pointee add-ref | pointee +8 | 4 (dword cmpxchg) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref loop on refcount at *(a0+0x10)+8 | [V] |
| sub_4e05e50 pointee destroy | pointee +0 | 8 (qword) | 0x4e05ed8 | `0x4e05ed8  call qword ptr [0xF99FFA0]` | destroys pointee when refcount hits 0 (vtable dtor via thunk) | [V] |
| sub_4e05e50 desc-region call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 dragon-layer upload bridge called with rcx=a0+0x58 description region — upload/ensure-loaded, NOT atlas creation | [V] |
| sub_4e05e50 pointee read | pointee +0x10 | 8 (qword) | 0x4e05e8c | `0x4e05e8c  mov rdx,[rdi+0x10]` | reads the pointee texture object pointer | [V] |
| sub_12893d0 entry | - | sub header | `sub_12893d0 [0x12893d0..0x12895d3) size 0x203 13 xrefs in` | TexturePtr release/collect; walks 0x18-strided entry array; the ONLY live caller of sub_4e05e50 (ret=0x1289496, all 32 samples) [V live mc_root_4e05e50_callers.txt] | [V] |
| sub_12893d0 array walk | stride 0x18 | - | 0x1289560 | `0x1289560  add rbx,0x18` | walks a 0x18-strided array releasing [rbx+0x10] and [rbx+8] entries | [V] |
| sub_12893d0 release pointee | pointee +0x10 | 8 (qword) | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | live-captured site: runtime target = sub_4e05e50; fall-through `0x1289496  nop` = ret=0x1289496 seen for ALL 32 samples of mc_root_4e05e50_callers.txt line 3 [V live] | [V live] |
| sub_12893d0 refcount dec | object +8 / +0xC | 4 (dword) | 0x1289515 / 0x128958c | `0x1289515  lock dec dword ptr [r15+8]` (strong) / `0x128958c  lock dec dword ptr [rcx+0xC]` (weak); object destroyed at zero | [V] |
| sub_12893d0 further release sites | entry +0x10 | 8 (qword) | 0x12894b3 | `0x12894b3  call qword ptr [0xF99FFA0]` (same instruction text at 0x12894ff, 0x1289529, 0x1289544, 0x1289599, 0x1289612) | seven more release/decrement calls through [0xF99FFA0] on old pointees and array entries | [V] |
| texgroup_load | - | 0x5421dec | `0x5421dec  call 0x5477a30` | looks up a texture by name in the texture table via sub_5477a30 (rcx=rsi+0x248, rdx=built name), then add-ref `0x5421e0a  lock inc dword ptr [rcx+8]`; 7 static xrefs in | [V] |
| texgroup_load callers | - | xref | - | `0x541f8f0 +0xc7d`, `0x5421c90 +0x190f`: ONLY two static callers — no stitcher looks up atlas textures by name | [V] |
| texload | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list ([rbx+0x160..0x168)) calling sub_5417950 per entry, tracking min/max UV at [rbx+0x6C]/[rbx+0x78]; 2 static xrefs in — atlas UV CONSUMPTION, not creation | [V] |
| texload rect read | 0x8 | 4 (movss) | 0x58a1450 | `0x58a1450  movss xmm3,[rcx+8]` | per-rect float read in the rect walk | [V] |
| l8b_texcreate_record capture | capture | - | `CALLER ret=0xE814560` line 3 | 24 samples at TextureD3D12::create entry 0xe81bf30; format 0x1C at desc+0x40 (`1C000000` at RCX+0x40); R8 names "Texture: 2815" (line 1) / "Texture: 2799" (line 8) UTF-16; NO atlas names; no compressed formats; all numMips=1 [V live docs/data/live/l8b_texcreate_record.txt] | [V live] |
| mc_root_4e05e50_callers capture | capture | - | `CALLER ret=0x1289496` line 3 | 150 hits / 32 samples at sub_4e05e50 entry; all share ONE caller: sub_12893d0 (ret=0x1289496 = `0x1289496  nop` after `0x1289490  call qword ptr [0xF99FFA0]`); sub_4e05e50 = TexturePtr ensure-loaded/release, NOT atlas creation [V live docs/data/live/mc_root_4e05e50_callers.txt] | [V live] |

## Part 5 — NEW THIS UNIT: stitcher hunt (tried, failed)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| obj +0x00 pointer value | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt:4 (hit=1 RCX) | `385821A8F67F0000` -> 0x00007FF6A8215838 at object+0x00 in every sampled sub_4e05e50 object (all sampled objects are item textures, e.g. ".legs" in R9 dumps, NOT atlases) | [V live] |
| obj +0x00 module placement | VA 0x00007FF6A8215838 | - | - | livemem status: exe image base 0x7ff7a59c0000 size 0x1383e000 (spans 0x7ff7a59c0000..0x7ff7b91fe000); 0x00007FF6A8215838 lies OUTSIDE the exe image -> another module; `python tools/sigs/livemem.py read 0x7ff6a8215838 0x40` -> unreadable (target released/stale), so the module/RVA cannot be identified | [I] |
| forward trace: sub_1870de0 decode | - | sub header | `sub_1870de0 [0x1870de0..0x1872de0) size 0x2000 37 xrefs in` | decoded this unit: generic dynamic registry (sentinel scan `0x1870e30  cmp dword ptr [rcx],0x2A`, slot write `0x1870f40  mov [r15],r14d`, object alloc `0x1870e70  mov edx,0x48`, name at obj+0 `0x1870ec5  mov [rsi],rax`, idx at obj+8 `0x1870ecb  mov [rsi+8],eax`) — not a stitcher, no createTexture/resizeTexture inside | [V] |
| forward trace: registration consumers | - | - | - | sub_186e6a0 calls sub_1870de0 then immediately frees the object (sub_2fe440 `0x186f782  call 0x2FE440` + sub_e935700 `0x186f78f  call 0xE935700`; ItemAtlas at 0x186f84d/0x186f85a); no located reader consumes the registry idx->name entries as a texture description | [V] |
| l8b_resizetex_slot31 capture | capture | - | - | queued (rva 0xe815840, size 0x100, max 6), NO result (orchestrator has not run it; queue full at 4 pending, not re-queued this unit); ret= would name the stitcher caller and mips>1 would be mip-generation evidence | [?] |

## CLOSES?

NO. Single blocking fact: the atlas TEXTURE-CREATION STITCHER is not located in the exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, `0xe81455b  call 0xE81BF30` -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, `0xe815866  mov edi,r9d`, takes mips) with atlas params:

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) inside sub_186e6a0 via sub_1870de0 (0x48-byte object `0x1870e70  mov edx,0x48`; name at obj+0 `0x1870ec5  mov [rsi],rax`; idx at obj+8 `0x1870ecb  mov [rsi+8],eax`; slot write `0x1870f40  mov [r15],r14d`, sentinel scan `0x1870e30  cmp dword ptr [rcx],0x2A`), triggered by ServerLevelLoad sub_1042320 -> sub_186e6a0 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810 (+0x61d). BUT sub_1870de0 is a generic idx->name registry (37 xrefs, not atlas-specific) and sub_186e6a0 frees the registered 0x48-byte objects immediately after registration (sub_2fe440 `0x186f782  call 0x2FE440` + sub_e935700 `0x186f78f  call 0xE935700`; ItemAtlas at 0x186f84d/0x186f85a); sub_1042320's full listing creates NO atlas texture [V]; sub_186e6a0 contains no createTexture/resizeTexture call [V]; the registered objects are consumed by NO located reader/stitcher [V]; no ItemAtlasBlit task exists; blit side is uncompressed ("BlitUncompressed" key ref 0x560be9f, TerrainAtlasBlit task `0xbb431ee  lea rdx,[0xF539A0B]`) [V].
- All creation entry points enumerated and NEGATIVE: createTexture census (live x2: l8b_texcreate_record + createtexture_callers; all format 0x1C uncompressed, numMips=1, names "Texture: 2799/2815" and UI/screen paths, ZERO atlas names [V live]); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture slot 31 has 0 static xrefs and has never been observed live [V]; sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release, not creation [V + V live mc_root_4e05e50_callers]; sub_5477a30 texture lookup callers = sub_541f8f0 + texgroup_load only, no stitcher [V via xref].
- New angles tried this unit, BOTH FAILED: (1) forward trace — sub_1870de0 fully decoded (generic registry, no stitcher, no texture creation); sub_186e6a0 frees objects post-registration; no registry reader located. (2) livemem read `python tools/sigs/livemem.py read 0x7ff6a8215838 0x40` -> unreadable (transient/stale); the other-module pointer at sampled-object +0x00 cannot be placed (exe base 0x7ff7a59c0000, VA outside image). l8b_resizetex_slot31 capture pending, queue full, not re-queued.
- Resolved as provably ABSENT (not blockers): mipmap generation (no GenMip/mipchain code or task [V via xref]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; all live creations numMips=1 [V live]) and BC1/BC3/BC7/DXT1-DXT5 compression (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` [V] / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]).

## Verification

Verbatim `0xRVA  instr` lines copied from `rdis.exe dis` output; all quoted lines re-confirmed against current rdis output this session. Newly confirmed this unit: every sub_1870de0 line (`0x1870e30`, `0x1870e35`, `0x1870e45`, `0x1870e49`, `0x1870e4c`, `0x1870e50`, `0x1870e70`, `0x1870e75`, `0x1870ec5`, `0x1870ecb`, `0x1870f28`, `0x1870f2b`, `0x1870f2f`, `0x1870f35`, `0x1870f40`) from `rdis dis 0x1870de0 400`. Earlier rows (oc_U-EL8b_r1..r18) were already verify_oc.py clean; the exe is unchanged. Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; only when delegate exits 0 set the line after `## NEXT` to DONE.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — ALREADY QUEUED (pending, rva 0xe815840, size 0x100, max 6), no result in docs/data/live/; queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), NOT re-queued this unit. Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= would name the stitcher caller and mips>1 would be mip-generation evidence.
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files; no throwaway scripts written).
