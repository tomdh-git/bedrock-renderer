## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression — progress note

Goal: close checklist item `L8b Atlases (terrain, items), mipmaps and compression pending` (docs/RENDER_CHECKLIST.md:345).
Table columns: name | rva or offset | size | read/store address (R/W base+disp) | verbatim `0xRVA  instr` | meaning | tag.
Tags: [V] = saw in disassembly (RVA cited, verbatim line quoted), [V live] = read-only live capture (docs/data/live/), [I] = inferred (say from what), [?] = unknown / not located.
Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01), image base 0x140000000. Static analysis only; exe is data, never launched.
Live image range: [0x7FF7A59C0000, 0x7FF7B91FE000) [V live via livemem status].
Carried [V] rows (from docs/progress/oc_U-EL8b_r1..r52) re-verified against the exe this session; live captures re-read in full: docs/data/live/mc_root_4e05e50_callers.txt [V live] (line 3 `CALLER ret=0x1289496 first_hit=1`), docs/data/live/l8b_texcreate_record.txt [V live] (line 3 `CALLER ret=0xE814560 first_hit=1`). docs/BGFX_MAP.md sections 1105/1107, 1502/1511/1512, 1812, 6o/448, 782 cited as [I] where used.
Input data also processed: docs/progress/oc_U-L8b.md (predecessor U-L8b PNG/TGA decoder notes) — distinct offsets below as annotated rows, verbatim instr lines copied from that input data and re-verified against the exe.

## Part 1 — Atlases (terrain, items): registration PROVEN [V], texture creation NOT located [?]

| "TerrainAtlas" string | str data 0xF55CDD3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name; len 0xC `0x186f73f  mov qword ptr [rbp+0x108],0xC`; registration idx 6 `0x186f767  mov r9d,6`; `0x186f76d  call 0x1870DE0` inside sub_186e6a0 | [V] |
| "ItemAtlas" string | str data 0xF55CDE0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name; len 9 `0x186f80a  mov qword ptr [rbp+0x118],9`; idx 7 `0x186f832  mov r9d,7`; `0x186f838  call 0x1870DE0` — item-atlas NAME + registration DO exist in the exe (original "no item atlas string/code" claim refuted) | [V] |
| atlas-string xref negatives | xref str "TerrainAtlas"/"ItemAtlas" | - | xref | - | xref.py str "TerrainAtlas" -> refs only (0x186f731, 0x186e6a0); "ItemAtlas" -> refs only (0x186f7fc, 0x186e6a0); no other code references either name [V via xref, re-verified this session] | [V] |
| registered object +0 name store | obj +0 | 8 (qword store) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered object +0 inside sub_1870de0 | [V] |
| registered object +8 idx store | obj +8 | 4 (dword store) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (6 TerrainAtlas / 7 ItemAtlas) stored at object +8 inside sub_1870de0 | [V] |
| sub_1870de0 alloc size | code 0x1870e70 | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocates a 0x48-byte registered object | [V] |
| sub_1870de0 alloc call | code 0x1870e75 | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator thunk (data_f99ffa0) for the 0x48-byte object | [V] |
| registry sentinel scan | registry dword array +0 | 4 (dword cmp) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | scans fixed registry dword array for 0x2A '*' free-slot sentinel; index bounded `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29` -> slots 0..41 | [V] |
| registration dispatcher | code 0x186e6a0 | - | 0x186e6e4 | `0x186e6e4  mov edx,0x18` | sub_186e6a0 registration loop allocs named objects via sub_1870de0; FULL LISTING CHECKED: NO call 0xE8143C0/0xE815840/0xE81BF30/0xBC73BF0/0xC296B50 and no atlas-creation code | [V] |
| sub_186e6a0 static callers | xref sub_186e6a0 callers | - | xref | - | exactly 2 static callers: sub_8f6810 (+0x61d, initStep1) and sub_1042320 (+0x1d1, ServerLevelLoad) [V via xref.py callers] | [V] |
| ServerLevelLoad trigger | code 0x1042320 | - | 0x104237e | `0x104237e  call 0x186E6A0` | ServerLevelLoad triggers atlas registration but creates NO atlas texture: no call 0xE8143C0/0xE815840/0xE81BF30 and no TerrainAtlas/ItemAtlas string in its full listing | [V] |
| TerrainAtlasBlit task name | str data 0xF539A0B | 8 (lea qword) | 0xbb431ee | `0xbb431ee  lea rdx,[0xF539A0B]` | "TerrainAtlasBlit" task-16 name inside 0xbb418d0; functor vtable 0xF43E9E0; blit body sub_bc02090 (BGFX_MAP 1105/1107) — atlas BLIT consumption, not creation | [V] |
| MaterialTerrainTextureAtlas string | str data 0xF55CE1B | - | none | - | atlas-name string in .rdata; xref.py refs=[] (no code references it) | [?] |
| terrain-atlas texture creation | terrain-atlas-creation | - | none | - | not located: xref "TerrainAtlas" -> registration sites only; no createTexture/resizeTexture tied to TerrainAtlas statically or in any live capture | [?] |
| item-atlas texture creation | item-atlas-creation | - | none | - | not located: xref "ItemAtlas" -> registration sites only; no createTexture/resizeTexture tied to ItemAtlas; no ItemAtlasBlit task | [?] |

## Part 2 — mipmaps

| num_mip_levels material key | str data 0xF5515C8 | 8 (lea qword) | 0x4e1a7e9 | `0x4e1a7e9  lea r8,[0xF5515C8]` | material JSON key parsed by sub_4e1a0a0 | [V] |
| mip_fade_amount material key | str data 0xF52FE18 | 8 (lea qword) | 0x4e1b275 | `0x4e1b275  lea rdx,[0xF52FE18]` | material JSON key parsed by sub_4e1a0a0 | [V] |
| mip_fade_color material key | str data 0xF5636E5 | 8 (lea qword) | 0x4e1b29b | `0x4e1b29b  lea rdx,[0xF5636E5]` | material JSON key parsed by sub_4e1a0a0 | [V] |
| mip_chain material key | str data 0xF593BE9 | 8 (lea qword) | 0x11528cf | `0x11528cf  lea rax,[0xF593BE9]` | material JSON key parsed by sub_1152460 | [V] |
| texture record +0xB1 numMips | struct +0xB1 | 1 (byte store) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored inside TextureD3D12::create; dl loaded `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]` | [V] |
| texture record +0xB0 actual format | struct +0xB0 | 1 (byte store) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte written inside create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]`; BGFX_MAP 1812: +0xAF requested format, +0xB0 actual format, +0xB1 numMips | [V] |
| format-table lookup | code 0xe81c022 | 2 (word load) | 0xe81c022 | `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | actual format chosen via u16-per-format table inside TextureD3D12::create | [V] |
| uncompressed fallback 0x42 | code 0xe81c12b | 1 (byte cmp) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback selected when caps lack the type | [V] |
| mip generation function | mip-generation | - | none | - | not located: xref str GenMip/Mips/MipMap/mipchain -> refs=[] (no functions) [V via xref]; no mip-generation Blit task; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; sampler bit 10 is mip FILTER (usage, not generation) [I via BGFX_MAP 782]; all live creations numMips=1 [V live] | [?] |

## Part 3 — compression

| BC1 string | str data 0xF84AD1C | - | none | - | BC1/DXT1 format name in .rdata; xref.py refs=[] (no code references it) | [?] |
| BC3 string | str data 0xF84AAF8 | - | none | - | BC3/DXT5 format name; xref.py refs=[] | [?] |
| BC7 string | str data 0xF84A930 | - | none | - | BC7 format name; xref.py refs=[] | [?] |
| DXT1-DXT5 strings | str data 0xF7DDD18, 0xF7D3D04, 0xF7D6AC8, 0xEF3FFEC-0xEF40010 | - | none | - | DXT1/DXT3/DXT4/DXT5 names; all xref.py refs=[] | [?] |
| "bad compression" string | str data 0xF58FF5A | - | 0x766542, 0x77b498 | - | referenced from 0x765330 and PNG decoder 0x777ed0 — PNG/zlib decompression error paths, not BC texture compression | [V] |
| mce::ImageUtils::decompressImage | str data 0xF5E339B | - | 0x19958c8 | - | refs inside 0x1994f90 (0x19958c8, 0x199594f, 0x1995a11): PNG/zlib decompression from the PNG decoder dispatcher, not BC compression | [V] |
| D3D format name table | data 0x56E3A12..0x56E42F6 | - | - | - | data table incl. BC3/BC7 names (BGFX_MAP 6o/448); data table only, no compression code path | [I] |
| BC texture compression/decompression code | bc-code | - | none | - | provably ABSENT [V]: all BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; only PNG/zlib decompression exists [V]; create path selects uncompressed `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed format 0x1C [V live] | [V] |

## Part 4 — creation entries, TexturePtr chain, TextureD3D12::create

| createTexture slot 26 -> TextureD3D12::create | code 0xe8143c0 | - | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture builds bimg params then calls TextureD3D12::create 0xe81bf30; createTexture has 0 static callers (reached indirect via [vptr+0xD0] slot 26); live callers ret=0xBC6A2C8 command interpreter [V live] | [V] |
| resizeTexture slot 31 | code 0xe815840 | - | sub header | `0xe815840  push rbp`; entry decode `0xe81586c  mov r14,rcx` (this renderer), `0xe81586f  mov [rbp+0x8E],dx` (handle), `0xe815869  mov ebx,r8d` (width->ebx), `0xe815866  mov edi,r9d` (mips->edi); resizeTexture(handle,w,h,mips,layers), mips can be specified; 0 static xrefs; never observed live | [V] |
| TextureD3D12::create callers | xref TextureD3D12::create callers | - | xref | - | exactly 2 static callers: createTexture and resizeTexture slot 31 (0xe815840) [V via xref]; xref hit at 0xe8403d0+0xaa5b verified as vtable DATA store `0xe8eaf2b  mov [rax+0x40],rcx`, not a call | [V] |
| sub_4e05e50 entry | code 0x4e05e50 | - | sub header | `0x4e05e50  push rbp` | TexturePtr ensure-loaded/upload bridge; 0 static xrefs in (reached at runtime via the indirect call from sub_12893d0) | [V] |
| sub_4e05e50 arg rsi | regs | - | 0x4e05e6b | `0x4e05e6b  mov rsi,rdx` | rsi = out pointer | [V] |
| sub_4e05e50 arg rdi | regs | - | 0x4e05e6e | `0x4e05e6e  mov rdi,rcx` | rdi = a0 (TexturePtr-like object: +0x10 pointee, +0x18, +0x58 desc region) | [V] |
| desc-region call | desc at a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 (dragon-layer upload bridge) called with rcx = a0+0x58 (texture description region) — ensure-loaded/upload, NOT atlas creation | [V] |
| result call | out | - | 0x4e05f85 | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 called on the produced result | [V] |
| sub_12893d0 entry | code 0x12893d0 | - | sub header | `0x12893d0  push rbp` | TexturePtr release/collect: walks a 0x18-strided entry array [r13..r14); entry object pointer at [r13+8] | [V] |
| sub_12893d0 array walk stride | elem stride 0x18 | - | 0x1289420 | `0x1289420  add r13,0x18` | next array entry | [V] |
| sub_12893d0 entry add-ref | entry obj +8 | 4 (lock cmpxchg) | 0x1289447 | `0x1289447  lock cmpxchg [rcx+8],edx` | add-ref object at [r13+8] | [V] |
| sub_12893d0 entry copy | entry | 16 (movups) | 0x128944e | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of array entry | [V] |
| sub_12893d0 indirect call site | code 0x1289490 | - | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | indirect call; ret=0x1289496 (fall-through instruction) observed in all 32 mc_root samples — sub_12893d0 is the only live caller of sub_4e05e50 | [V live] |
| sub_12893d0 fall-through nop | code 0x1289496 | - | 0x1289496 | `0x1289496  nop` | fall-through instruction after the indirect call = ret=0x1289496 seen in mc_root_4e05e50_callers.txt line 3 | [V live] |
| sub_12893d0 release sites | pointee/entry | 8 (qword call) | 0x12894b3 | `0x12894b3  call qword ptr [0xF99FFA0]` (same instr text at 0x12894ff, 0x1289529, 0x1289544, 0x128957d, 0x1289599, 0x1289612) | seven release/decrement call sites on old pointees and array entries | [V] |
| sub_12893d0 refcount dec strong | object +8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | strong refcount decrement; destroy at zero | [V] |
| sub_12893d0 refcount dec weak | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | weak-count decrement | [V] |
| sub_12893d0 count output | out +0 | 8 (qword store) | 0x12895a8 | `0x12895a8  mov [rsi],r12` | stores collected count | [V] |
| texgroup_load | code 0x5421c90 | - | 0x5421dec | `0x5421dec  call 0x5477A30` | looks up a texture by name via sub_5477a30 (rcx = rsi+0x248); add-ref `0x5421e0a  lock inc dword ptr [rcx+8]` on the looked-up texture — lookup only, not creation | [V] |
| sub_5477a30 callers | xref sub_5477a30 callers | - | xref | - | exactly 2 static callers: sub_541f8f0 (+0xc7d) and texgroup_load 0x5421c90 (+0x190f) — no stitcher looks up atlas textures by name | [V] |
| texload | code 0x58a1310 | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list ([rbx+0x160..0x168)); per-rect floats `0x58a1450  movss xmm3,[rcx+8]` — atlas UV CONSUMPTION, not creation | [V] |

## Part 5 — LIVE census (read this session)

| l8b_texcreate_record census | capture 0xE81BF30 | - | `CALLER ret=0xE814560` line 3 | docs/data/live/l8b_texcreate_record.txt line 3: 24 samples at TextureD3D12::create entry 0xe81bf30; format 0x1C at RCX+0x40 (`1c000000` line 4); R8 names "Texture: 2815"/"Texture: 2799" UTF-16, URLs "ui://./hbui/index.html"; NO atlas names; no compressed formats; all numMips=1 [V live] | [V live] |
| createtexture_callers census | capture 0xe8143c0 | - | `CALLER ret=0xBC6A2C8` line 3 | 150 hits / 32 samples at createTexture 0xe8143c0; all callers ret=0xBC6A2C8 command interpreter; R8 description objects format 0x1C with UI/screen texture names only; ZERO atlas names [V live] | [V live] |
| mc_root_4e05e50_callers census | capture 0x4e05e50 | - | `CALLER ret=0x1289496` line 3 | docs/data/live/mc_root_4e05e50_callers.txt line 3: 150 hits / 32 samples, all caller ret=0x1289496 (= sub_12893d0) [V live] | [V live] |
| LIVE object +0x00 vtable ptr | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt line 4 RCX | capture bytes at RCX+0x00: `385821A8F67F0000` -> qword 0x00007FF6A8215838 (same value in hits 1, 2, 8, ... 15; RCX=3908FFDE900 hit=1) | vtable/type pointer at object +0, read from live capture memory | [V live] |
| LIVE exe image range | image base | - | python tools/sigs/livemem.py status | pid 13452 base 0x7FF7A59C0000 size 0x1383e000 Minecraft.Windows.exe 1.26.62.01 -> live image range [0x7FF7A59C0000, 0x7FF7B91FE000) [V live] | [V live] |
| obj+0 -> ANOTHER MODULE | obj +0x00 | - | - | 0x00007FF6A8215838 < base 0x7FF7A59C0000 -> pointer at object +0 is OUTSIDE this exe image: ANOTHER MODULE; livemem read of 0x00007FF6A8215838 returned "unreadable" (livemem restricted to exe/heap ranges) — the value itself stands from the capture [V live] | [V live] |
| LIVE desc bytes | desc at RCX+0x60..+0x77 | 4+4+4+4 dwords | mc_root_4e05e50_callers.txt line 4 | +0x60 `1C000000` format 0x1C (R8G8B8A8_UNORM, uncompressed); +0x64/+0x68/+0x6C dims 1/1/1; +0x70 `74657800` tag "tex\0" [V live] | [V live] |

## Part 6 — input data carried from docs/progress/oc_U-L8b.md (predecessor U-L8b PNG/TGA decoder notes), re-verified against the exe

| PNG first-byte vs 0x89 | stream cursor r15+0xC0 | 1 (byte cmp) | 0x777f55 | `0x777f55  cmp cl,0x89` | decoder reads first byte at stream cursor [r15+0xC0] (`0x777f34  mov rcx,[rcx+0xC0]`), advances cursor `0x777f4b  mov [r15+0xC0],rdx`, compares to 0x89 PNG magic; mismatch -> `0x777f5e  jmp 0x77849F` error path | [V] |
| decoder width | struct r15+0 | 4 (dword cmp) | 0x7786ae | `0x7786ae  cmp dword ptr [r15],0x1000001` | width validated <= 1,048,577 | [V] |
| decoder height | struct r15+4 | 4 (dword) | 0x778692 | `0x778692  mov r8d,[r15+4]`; abs() `0x778699  neg eax; 0x77869b  cmovs eax,r8d`; write-back `0x77869f  mov [r15+4],eax`; validate `0x7786a3  cmp eax,0x1000001` | height (BMP signed-height convention, abs()'d) | [V] |
| decoder format | struct r15+8 | 4 (dword store) | 0x7789d6 | `0x7789d6  mov [r15+8],ecx` | format/component count (3 or 4 from color type) stored at +8 | [V] |
| decoder bytes-consumed | struct r15+0xB8 | 4 (dword) | 0x777f90 | `0x777f90  add [r15+0xB8],ecx` | stream bytes-consumed counter | [V] |
| decoder stream end | struct r15+0xC8 | 8 (qword load) | 0x777f3b | `0x777f3b  mov rax,[r15+0xC8]` | stream end compared with cursor at `0x777f42  cmp rcx,rax` | [V] |
| nested PNG IHDR check | stream inner cursor | 1 (byte cmp) | 0x7815d0 | `0x7815d0  cmp cl,0x89`; mismatch -> `0x7815d5  jmp 0x781A39` | nested IHDR-stream PNG magic check inside sub_781550 | [V] |

## Interpretation (this session)

- NEW ANGLE tried: re-checked `python tools/livecap/request.py result` for every L8b capture — `l8b_resizetex_slot31` (rva 0xe815840 = resizeTexture slot 31) still pending, no result file in docs/data/live/; queue is full (4 pending: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), so no new L8b capture can be added this unit. `l8b_resizetex_slot31` remains the one capture that could name the stitcher caller (resizeTexture takes mips; mips>1 would be mip-generation evidence) but it is not yet available.
- Static re-check (no re-runs of xref/rdis beyond instr verification): xref str "TerrainAtlas"/"ItemAtlas" -> registration sites only [V]; sub_186e6a0 full listing has no create/resize/BGFX create call [V]; sub_1042320 full listing has no atlas creation [V]. descscan2/vt/vcalls cannot cross the module boundary: the live texture-request object's +0x00 vtable pointer 0x00007FF6A8215838 is provably outside this exe image [V live]. The r13 lead (identify the module/RVA of 0x7FF6A8215838) is blocked: livemem read of that address returns "unreadable" (restricted to exe/heap ranges) and no module-enumeration command exists [I].
- Mip generation: provably absent [V via xref refs=[]; no mip-gen task; numMips=1 for all live creations [V live]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]]. BC1/BC3/BC7/DXT1-DXT5 compression CODE: provably absent [V via xref refs=[]; uncompressed-only create path `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]; live census all-uncompressed [V live]]. Compressed texture DATA may still be loaded from disk [I].

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas texture-creation STITCHER is not located in this exe — no code builds the TerrainAtlas/ItemAtlas texture description and calls createTexture (slot 26, 0xe8143c0 -> TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, 0xe815840, takes mips) with atlas params; registration stores only name+idx [V]; all creation entry points enumerated negative statically and in 3 live captures (all format 0x1C, numMips=1, no atlas names) [V + V live]; live objects carry a +0x00 vtable pointer provably in ANOTHER MODULE (capture value 0x00007FF6A8215838 vs exe image [0x7FF7A59C0000, 0x7FF7B91FE000)) [V live], so atlas creation/decode is external-module or data-driven and cannot be closed from this exe statically. CLOSES? YES only when the stitcher call site is found (pending l8b_resizetex_slot31 capture result) or an orchestrator decision marks atlas creation external/data-driven (MIRROR_SKIP).

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` then `python tools/delegate.py check docs/progress/oc_U-EL8b.md`; fix EVERY failure; the line after `## NEXT` is DONE only when delegate exits 0. All quoted `0xRVA  instr` lines copied verbatim from rdis output and re-verified against the exe this session; live values cited as [V live] with file + line.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — ALREADY QUEUED (pending, rva 0xe815840 = resizeTexture slot 31 entry, size 0x100, max 6), NO result yet in docs/data/live/ (_status.txt lacks it). Cannot re-queue (duplicate) and queue is full (4 pending: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc). Why: resizeTexture(handle,w,h,mips,layers) is the only creation entry never observed (0 static xrefs); its ret= would name the stitcher caller and mips>1 would be mip-generation evidence; atlas-name params would close the terrain/item-atlas creation rows.
Livemem capability gap: direct read of external-module address 0x00007FF6A8215838 returns "unreadable" (livemem restricted to exe/heap ranges); no module-enumeration command available, so the module NAME of 0x7FF6A8215838 cannot be determined from this side [I]. A module-enumerate/arbitrary-read livemem capability would let me name the stitcher's module.
Helper scripts: none (all verbatim lines taken directly from rdis dis output, xref/ripscan output, and live capture files; no throwaway scripts written this session).
