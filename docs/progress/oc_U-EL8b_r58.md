## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #18)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — table of rows (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted), [V live] read-only live capture (docs/data/live/), [I] inferred (say from what), [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Do not paste the input data as-is; one annotated row per distinct offset, all sites listed; every offset covered, none skipped or summarized; no catch-all rows.

## 0. Input reviewed this session (NOT re-derived)

- docs/progress/oc_U-EL8b_r54..r57 carried: atlas registration [V], blit consumption [V], createTexture/resizeTexture decode [V], mip keys [V], numMips store [V], format fallback [V], BC strings unreferenced [V], sub_4e05e50/texgroup_load/texload/TexturePtr decode [V + V live], live capture census [V live]. Every verbatim `0xRVA  instr` line below was re-confirmed against the exe with `rdis.exe dis` this session (see Verification); all match.
- docs/progress/oc_U-L8b.md (predecessor PNG/TGA decoder unit — unrelated to atlases; no atlas or compression code there; read fully).
- docs/data/live/mc_root_4e05e50_callers.txt [V live] re-read: line 3 `CALLER ret=0x1289496 first_hit=1`; all 150 hits/32 samples → sub_12893d0.
- docs/data/live/l8b_texcreate_record.txt [V live] re-read: line 3 `CALLER ret=0xE814560 first_hit=1`; 24 samples, format 0x1C uncompressed, numMips=1, no atlas names.
- NEW today, read in full: docs/data/live/dragon_texture_caller_bc41420.txt [V live] (rva 0xBC41420): line 3 `CALLER ret=0x4E05F7C first_hit=1` = sub_4e05e50 at `0x4e05f7c  nop` right after `0x4e05f77  call 0xBC41420`; RCX = description ptr (format 0x1C at +0x04, dims 1/1/1, fourcc "tex" at +0x10) — the dragon-layer upload bridge receives the same 1x1 uncompressed description seen in mc_root_4e05e50_callers.
- NEW today, read in full: docs/data/live/dragon_texture_entry_c296b50.txt [V live] (rva 0xC296B50): line 3 `CALLER ret=0xBC41B3E first_hit=1` = sub_bc41420 → sub_c296b50; continues the L8a chain bc41420→c296b50→bc73bf0→bc73770(cmd-byte-14)→dispatcher slot-26→createTexture 0xe8143c0.
- docs/data/live/README.md [I] — capture format (regs kind: REG=value hit=N hexbytes).
- `python tools/livecap/request.py result l8b_resizetex_slot31` → "no result yet (orchestrator has not run it)" [V live via tool].
- docs/progress/capture_requests.json: 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) → queue at the 4-pending limit; `python tools/livecap/request.py add l8b_atlas_reg_dispatcher 0x186e6a0 ...` → "4 requests already pending, ask again next unit" (exit 1) [V live via tool run]. No new L8b capture can be added this unit.
- livemem read of +0x00 other-module pointer 0x00007ff6a8215838 → "unreadable" (stale pointer) [V live, r57] — dead lead.

## Part 1 — Atlases (terrain, items): registration PROVEN [V]; texture-creation stitcher NOT located [?] (single blocking fact)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| str data 0xf55cdd3 (TerrainAtlas name) | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" (len 0xC) loaded before the sub_1870de0 call; registered idx 6 (r9d=6) inside sub_186e6a0; string data xrefs only from registration | [V] |
| str data 0xf55cde0 (ItemAtlas name) | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" (len 9) loaded before the sub_1870de0 call; registered idx 7 (r9d=7) inside sub_186e6a0 — item atlas EXISTS as a registered name in this exe | [V] |
| registered obj +0 (name) | 8 (qword store) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 inside sub_1870de0 | [V] |
| registered obj +8 (index) | 4 (dword store) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at registered object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocates a 0x48-byte registered object via sub_eea6040 | [V] |
| sub_1870de0 alloc call | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk for the 0x48-byte registered object | [V] |
| registry scan dword +0 | 4 (dword cmp) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | fixed registry scanned for 0x2A '*' free-slot sentinel; loop-bound sites `0x1870f28  inc r14d`, `0x1870f2b  cmp r14d,0x29` bound idx to 0..0x29 (0..41) | [V] |
| sub_186e6a0 registration dispatcher | 4 (dword imm) | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop (0x186e6a0..~0x18706a0): allocs named objects via sub_1870de0; NO createTexture/resizeTexture call anywhere inside | [V] |
| sub_186e6a0 static callers | - | xref sub_186e6a0 callers | - | exactly 2 static callers: initStep1 sub_8f6810 (`0x8f685b  lea rcx,[0xF7DE3DB]` "initStep1", call at +0x61d) and ServerLevelLoad sub_1042320 (`0x104237e  call 0x186E6A0` at +0x1d1) [V via xref.py callers] | [V] |
| sub_1042320 ServerLevelLoad trigger | - | 0x104237e | `0x104237e  call 0x186E6A0` | ServerLevelLoad triggers atlas registration via sub_186e6a0; loads "ResourceLoadType::ServerLevelLoad" `0x104239b  lea rax,[0xF602326]` | [V] |
| sub_1042320 full listing | - | full listing (0x1042320..0x1044320) | - | 1778-line listing grep: NO `call 0xE8143C0` / `0xE815840` / `0xE81BF30` and no TerrainAtlas/ItemAtlas string — registers atlas names, creates NO atlas texture | [V] |
| sub_8f6810 initStep1 caller | - | 0x8f685b | `0x8f685b  lea rcx,[0xF7DE3DB]` | "initStep1"; second caller of sub_186e6a0; registers objects | [V] |
| MaterialTerrainTextureAtlas string | - | none | - | atlas-name string at str data 0xf55ce1b; xref.py refs=[] (no code references it) | [?] |
| TerrainAtlasBlit task name | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name inside 0xbb418d0; functor vtable 0xF43E9E0; atlas BLIT consumption, not creation | [V] |
| BlitUncompressed key | - | ref 0x560be9f | `0x560be9f  lea r9,[0xF5F440C]` | "BlitUncompressed" referenced once, from 0x560be9f inside 0x55f1450: atlas/texture blit path is uncompressed | [V] |
| terrain-atlas texture creation | - | none | - | not located: xref "TerrainAtlas" refs=[(0x186f731,0x186e6a0)] only; no createTexture(0xe8143c0)/resizeTexture(0xe815840) call tied to TerrainAtlas | [?] |
| item-atlas texture creation | - | none | - | not located: xref "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture/resizeTexture call tied to ItemAtlas; no ItemAtlasBlit task exists | [?] |

## Part 2 — mipmaps: provably ABSENT [V] (not the blocker)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| str data 0xf5515c8 (num_mip_levels key) | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key "num_mip_levels" parsed by sub_4e1a0a0 | [V] |
| str data 0xf52fe18 (mip_fade_amount key) | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key "mip_fade_amount" parsed by sub_4e1a0a0 | [V] |
| str data 0xf5636e5 (mip_fade_color key) | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key "mip_fade_color" parsed by sub_4e1a0a0 | [V] |
| str data 0xf593be9 (mip_chain key) | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key "mip_chain" parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | 1 (byte store) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored inside TextureD3D12::create sub_e81bf30; dl loaded `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | 1 (byte store) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| uncompressed-format fallback 0x42 | 1 (byte cmp) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain → refs=[] (no functions) [V via xref]; no mip-generation Blit task [V]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; sampler bit 10 is mip FILTER (usage, not generation) [I]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression: provably ABSENT [V] (not the blocker)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| str data 0xf84ad1c (BC1) | - | none | - | BC1/DXT1 format name at str data 0xf84ad1c; xref.py refs=[] (no code references it) | [?] |
| str data 0xf84aaf8 (BC3) | - | none | - | BC3/DXT5 format name at str data 0xf84aaf8; xref.py refs=[] | [?] |
| str data 0xf84a930 (BC7) | - | none | - | BC7 format name at str data 0xf84a930; xref.py refs=[] | [?] |
| str data 0xf7ddd18/0xf7d3d04/0xf7d6ac8/0xef3ffec (DXT1-DXT5) | - | none | - | DXT names; all xref.py refs=[] | [?] |
| str data 0xf58ff5a ("bad compression") | - | 0x766542 | - | referenced from 0x765330 and PNG decoder 0x777ed0 — PNG/zlib decompression error paths, not BC texture compression | [V] |
| str data 0xf5e339b (decompressImage) | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): PNG/zlib image decompression from the PNG decoder dispatcher, not BC compression | [V] |
| D3D format name table | - | data 0x56e3a12..0x56e42f6 | - | table includes BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live] | [V] |

## Part 4 — creation entries, TexturePtr chain, and live census (all negative for atlases)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| createTexture → TextureD3D12::create call | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (slot 26) builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture 0 static callers (vtable slot 26, offset 0xD0); live callers ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 entry decode | mixed | 0xe815866 | `0xe815866  mov edi,r9d` | entry decode `sub_e815840 [0xe815840..0xe817840) size 0x2000 0 xrefs in`: RCX=this renderer `0xe81586c  mov r14,rcx`; DX=handle word `0xe81586f  mov [rbp+0x8E],dx`; R8D=width→ebx `0xe815869  mov ebx,r8d`; R9D=mips→edi `0xe815866  mov edi,r9d`; stack word mips `0xe815980  movzx r13d,word ptr [rbp+0x108]`; stack byte layers `0xe815988  movzx r12d,byte ptr [rbp+0x100]`; renderer+0xBDE178 handle array `0xe815876  lea rsi,[rcx+0xBDE178]`; resizeTexture(handle,w,h,mips,layers), mips specifiable; 0 static xrefs; never observed live | [V] |
| TextureD3D12::create callers | - | xref TextureD3D12::create callers | - | exactly 2 static callers: createTexture (`0xe8143c0 0x2e1` site `0xe81455b`) and resizeTexture (`0xe815840 0x3ae`); xref hit at 0xe8403d0+0xaa5b verified as vtable DATA store `0xe8eaf2b  mov [rax+0x40],rcx`, not a call | [V] |
| sub_4e05e50 entry | - | sub header | `0x4e05e50  push rbp` | TexturePtr ensure-loaded/release function; 0 static xrefs in; reached indirect via [0xF99FFA0] from sub_12893d0 at runtime | [V] |
| sub_4e05e50 arg rsi | - | sub_4e05e50 +0x1b | `0x4e05e6b  mov rsi,rdx` | rsi = out pointer | [V] |
| sub_4e05e50 arg rdi | - | sub_4e05e50 +0x1e | `0x4e05e6e  mov rdi,rcx` | rdi = a0 = TexturePtr-like object (+0x10 pointee, +0x18, +0x58 desc region) | [V] |
| sub_4e05e50 pointee add-ref | 4 (dword cmpxchg) | pointee +8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref loop on refcount at *(a0+0x10)+8 | [V] |
| sub_4e05e50 desc-region call | - | desc at a0+0x58 | `0x4e05f77  call 0xBC41420` | sub_bc41420 (dragon-layer upload bridge) called with rcx = a0+0x58 description region — ensure-loaded/upload, NOT atlas creation | [V] |
| sub_4e05e50 result call | - | out | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 called on the produced result | [V] |
| sub_4e05e50 pointee read | 8 (qword load) | pointee +0x10 | `0x4e05e8c  mov rdx,[rdi+0x10]` | reads the pointee texture object pointer | [V] |
| sub_4e05e50 pointee destroy | 8 (qword) | pointee | `0x4e05ed8  call qword ptr [0xF99FFA0]` | destroys pointee when refcount hits 0 (vtable dtor via thunk) | [V] |
| sub_12893d0 entry | - | sub header | `0x12893d0  push rbp` | TexturePtr release/collect: walks 0x18-strided entry array [r13..r14), [r13+8] = object pointer | [V] |
| sub_12893d0 array walk stride | - | elem stride 0x18 | `0x1289420  add r13,0x18` | next array entry | [V] |
| sub_12893d0 add-ref | 4 (dword cmpxchg) | entry obj +8 | `0x1289447  lock cmpxchg [rcx+8],edx` | add-ref object at [r13+8] | [V] |
| sub_12893d0 entry copy | 16 (movups) | entry | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of array entry | [V] |
| sub_12893d0 release pointee (LIVE-CAPTURED SITE) | 8 (qword call) | sub_12893d0 pointee +0x10 | `0x1289490  call qword ptr [0xF99FFA0]` | LIVE-CAPTURED SITE: runtime target = sub_4e05e50; fall-through `0x1289496  nop` = ret=0x1289496 seen for ALL 32 samples in mc_root_4e05e50_callers.txt line 3 | [V live] |
| sub_12893d0 release sites | 8 (qword call) | sub_12893d0 pointee/entry | `0x12894b3  call qword ptr [0xF99FFA0]` | same instr text at 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612; seven more release/decrement calls on old pointees and array entries | [V] |
| sub_12893d0 refcount dec strong | 4 (dword) | object +8 | `0x1289515  lock dec dword ptr [r15+8]` | decrements refcount; object destroyed when it reaches zero | [V] |
| sub_12893d0 refcount dec weak | 4 (dword) | object +0xC | `0x128958c  lock dec dword ptr [rcx+0xC]` | second (weak) count decrement | [V] |
| sub_12893d0 count output | 8 (qword store) | out +0 | `0x12895a8  mov [rsi],r12` | stores collected count r12 into the output pointer | [V] |
| sub_12893d0 static callers | - | xref sub_12893d0 callers | - | 13 xrefs in: 0x1145c20 (+0x4ae), 0x6622610 (+0x1c8), 0x66232b0 (+0xb3d0), 0x6632bf0 (+0x34b) — none is a texture creator [V via xref.py callers] | [V] |
| sub_4e05e50 live RCX +0x00 (other-module pointer) | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x00: 385821A8F67F0000 → qword 0x00007ff6a8215838 | pointer into ANOTHER MODULE (outside exe image [0x7FF7A59C0000, 0x7FF7B91FE000)); livemem read → "unreadable" (stale) | [V live] |
| sub_4e05e50 live RCX +0x10 (pointee) | 8 (qword) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x10: B00291BE90030000 → qword 0x000390BE9102B0 | pointee texture object pointer; sub_4e05e50 reads [rdi+0x10] at `0x4e05e8c  mov rdx,[rdi+0x10]` | [V live] |
| sub_4e05e50 live RCX +0x60/64/68/6C (dims + format) | 4 (dword) x4 | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x60/0x64/0x68/0x6C: 00000001 1C000000 01000000 01000000 → w/h/array = 1/1/1, format 0x1C at desc+0x64 | [V live] |
| sub_4e05e50 live RCX +0x70 (fourcc tag) | 4 (byte tag) | mc_root_4e05e50_callers.txt hit=1 RCX | bytes at RCX+0x70: 74657800 → "tex\0" description fourcc tag | [V live] |
| sub_4e05e50 live caller | - | capture header line 3 | `CALLER ret=0x1289496 first_hit=1` (mc_root_4e05e50_callers.txt line 3) | all 150 hits/32 samples: sub_12893d0 is the only live caller of sub_4e05e50 — TexturePtr release/ensure-loaded, NOT a creator | [V live] |
| texgroup_load | - | 0x5421dec | `0x5421dec  call 0x5477A30` | looks up a texture by name in the texture table via sub_5477a30 (rcx=rsi+0x248); add-ref `0x5421e0a  lock inc dword ptr [rcx+8]` on looked-up texture — lookup only, not creation | [V] |
| texgroup_load add-ref | 4 (dword) | texture +8 | `0x5421e0a  lock inc dword ptr [rcx+8]` | add-ref looked-up texture ([rax+0x68]+8) | [V] |
| texload | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks 0x30-strided rect list [rbx+0x160..0x168); per-rect float `0x58a1450  movss xmm3,[rcx+8]` — atlas UV CONSUMPTION, not creation | [V] |
| texload rect read | 4 (movss) | 0x8 | `0x58a1450  movss xmm3,[rcx+8]` | per-rect float read in the rect walk | [V] |
| sub_5477a30 callers | - | xref sub_5477a30 callers | - | ONLY two static callers: texgroup_load (+0x190f) and sub_541f8f0 (+0xc7d) — no stitcher looks up atlas textures by name | [V] |

## Part 5 — new angles tried this session (all exhausted)

1. `python tools/livecap/request.py result l8b_resizetex_slot31` → "no result yet (orchestrator has not run it)" — the resizeTexture slot-31 capture (rva 0xe815840, size 0x100, max 6) remains the highest-value live ask (ret= would name the stitcher caller; mips>1 would be mip-generation evidence) but no result exists in docs/data/live/ [V live via tool].
2. `python tools/livecap/request.py add l8b_atlas_reg_dispatcher 0x186e6a0 ...` → "4 requests already pending, ask again next unit" (exit 1): capture queue at its 4-pending limit (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc); no new capture can be added this unit [V live via tool run].
3. dragon_texture_caller_bc41420.txt + dragon_texture_entry_c296b50.txt (new today, read in full): confirm the create chain sub_4e05e50→sub_bc41420 (ret=0x4E05F7C)→sub_c296b50 (ret=0xBC41B3E)→bc73bf0→bc73770 (cmd-byte-14 producer)→dispatcher slot-26→createTexture 0xe8143c0 carries ONLY 1x1 format-0x1C "tex"-tagged descriptions ("Texture: 2815"/"Texture: 2799" among others) — zero atlas names, zero mips>1 [V live].
4. livemem read of the +0x00 other-module pointer 0x00007ff6a8215838 → "unreadable" (stale) [V live, r57] — dead lead; no module-enumerate command exists, so the module name/RVA of that pointer cannot be identified from this side [I].
5. Static re-search: NOT repeated — sub_186e6a0 (2 callers, registration only), sub_1870de0 (37 xrefs, all registration-side, decoded fully [V]), sub_1042320 full listing (no createTexture/resizeTexture), sub_5477a30 callers (2, no stitcher), all BC/DXT strings unreferenced — all already proven [V] in oc_U-EL8b_r54..r57; orchestrator hint (2026-11-22) treats static analysis alone as exhausted for this item.

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas TEXTURE-CREATION STITCHER is not located in this exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, `0xe81455b  call 0xE81BF30`) or resizeTexture (slot 31, `0xe815866  mov edi,r9d`, takes mips) with atlas params:

- Atlas registration IS proven [V]: "TerrainAtlas" idx 6 (`0x186f731  lea rax,[0xF55CDD3]`) and "ItemAtlas" idx 7 (`0x186f7fc  lea rax,[0xF55CDE0]`) inside sub_186e6a0 (sub_1870de0 0x48-byte object; name at obj+0 `0x1870ec5  mov [rsi],rax`; idx at obj+8 `0x1870ecb  mov [rsi+8],eax`; registry sentinel `0x1870e30  cmp dword ptr [rcx],0x2A`), triggered by ServerLevelLoad `0x104237e  call 0x186E6A0` and initStep1 sub_8f6810 (+0x61d). But sub_1042320's full listing creates NO atlas texture [V]; sub_186e6a0 contains no create/resize call [V]; sub_1870de0's xrefs are all registration-side; the registered objects are consumed by NO located reader/stitcher [V]. No ItemAtlasBlit task exists; blit side is uncompressed ("BlitUncompressed" `0x560be9f  lea r9,[0xF5F440C]`; TerrainAtlasBlit task `0xbb431ee  lea rdx,[0xF539A0B]`) [V].
- Creation entry points fully enumerated and negative: createTexture census (live x3: l8b_texcreate_record + createtexture_callers + bgfx_createtexture_producer; UI/misc names only, format 0x1C, numMips=1, ZERO atlas names [V live]); dragon-layer chain (new today [V live]) produces only 1x1 format-0x1C "tex"-tagged descriptions ("Texture: 2815"/"Texture: 2799"); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture 0 static xrefs and never captured [V]; sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release, not creation [V + V live mc_root_4e05e50_callers]; sub_5477a30 texture lookup callers = texgroup_load + sub_541f8f0 only, no stitcher [V via xref].
- Live mc_root objects carry +0x00 vtable pointer provably in ANOTHER MODULE (0x00007ff6a8215838 vs exe image [0x7FF7A59C0000, 0x7FF7B91FE000)) [V live] — consistent with the original assessment "likely CPU decode in another module / data-driven"; livemem read of it "unreadable" (stale) [V live].
- The one capture that could name the stitcher caller — l8b_resizetex_slot31 (resizeTexture slot 31, takes mips; mips>1 would be mip-generation evidence) — is queued (pending, rva 0xe815840, size 0x100, max 6) but has NO result yet; capture queue is at its 4-pending limit, so no new capture can be added this unit.

Resolved as provably-ABSENT (negatives, NOT the blocker): mipmap generation (no GenMip/Mips/MipMap/mipchain code or task [V via xref]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; all live creations numMips=1 [V live]) and BC1/BC3/BC7/DXT1-DXT5 compression (all those strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed 0x42 fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]).

CLOSES? YES only when the stitcher call site is found (pending l8b_resizetex_slot31 capture result) or an orchestrator decision marks atlas creation external/data-driven (MIRROR_SKIP).

## Verification

Every quoted `0xRVA  instr` line re-confirmed this session against the exe with `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x<RVA> 4` — all match (incl. `0x4e05e50  push rbp`, `0x12893d0  push rbp`, `0x128944e  movups xmm0,[r13]`, `0x58a1450  movss xmm3,[rcx+8]`, `0x4e05f77  call 0xBC41420`, `0xe815876  lea rsi,[rcx+0xBDE178]`). Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; only when delegate exits 0 set the line after `## NEXT` to DONE.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — ALREADY QUEUED (pending, rva 0xe815840 = resizeTexture slot 31 entry, size 0x100, max 6), no result in docs/data/live/ yet. Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); ret= names the stitcher caller; mips>1 is mip-generation evidence; atlas-name params would close the terrain/item-atlas creation rows. Cannot re-queue (duplicate) and queue is full (4 pending) — `request.py add` refused with "4 requests already pending, ask again next unit".
Livemem capability gap: direct read of external-module address 0x00007ff6a8215838 returns "unreadable" (livemem restricted to exe/heap ranges); no module-enumeration command available, so the module name of the +0x00 pointer cannot be determined from this side [I].
Helper scripts: none (all verbatim lines taken directly from rdis dis output, xref output, and live capture files; no throwaway scripts written).
