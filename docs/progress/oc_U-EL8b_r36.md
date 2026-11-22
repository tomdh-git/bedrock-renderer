## NEXT
DONE - static analysis for U-EL8b is complete and written to this file; CLOSES? NO (see below): the TerrainAtlas/ItemAtlas texture-creation stitcher is not located in the exe; mip generation and BC1/BC3/BC7 compression are absent statically; the l8b_resizetex_slot31 capture is already queued and pending.

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression — FINAL

Goal: close checklist item "L8b Atlases (terrain, items), mipmaps and compression pending".
Static analysis only (OPENCODE_BRIEF.md rule 1); exe = Minecraft.Windows.exe 1.26.62.01; RVAs relative to image base.
Tags: [V] saw in disassembly (RVA cited), [I] inferred from that, [?] unknown, [V live] from docs/data/live capture files.

## ANSWER TABLE (one row per distinct field offset; all instruction sites listed in the site cell; sizes come from the instruction)

| name | field | size | site(s) (read/store address) | verbatim `0xRVA  instr` | meaning shown by instruction or string | tag |
| TerrainAtlas registration (sub_186e6a0 -> sub_1870de0; called from initStep1 0x8f6919 and ServerLevelLoad 0x104237e) | rva 0xF55CDD3 "TerrainAtlas" | 12 (len from `0x186f73f mov qword ptr [rbp+0x108],0xC`) | `0x186f731 lea rax,[0xF55CDD3]`; `0x186f767 mov r9d,6` (idx); `0x186f76d call 0x1870DE0` | `0x186f731  lea rax,[0xF55CDD3]` | name string + len 0xC + idx 6 passed to the 0x48-byte atlas node allocator | [V] |
| ItemAtlas registration (same path) | rva 0xF55CDE0 "ItemAtlas" | 9 (len from `0x186f80a mov qword ptr [rbp+0x118],9`) | `0x186f7fc lea rax,[0xF55CDE0]`; `0x186f832 mov r9d,7` (idx); `0x186f838 call 0x1870DE0` | `0x186f7fc  lea rax,[0xF55CDE0]` | item-atlas name EXISTS in the exe; idx 7 | [V] |
| atlas node+0 vptr | node+0x0 | 8 | `0x1870ec5 mov [rsi],rax` | `0x1870ec5  mov [rsi],rax` | node+0 = 0 (vptr cleared); node allocated 0x48 bytes (`0x1870e70 mov edx,0x48`) | [V] |
| atlas node+8 idx | node+0x8 | 4 | `0x1870ecb mov [rsi+8],eax` | `0x1870ecb  mov [rsi+8],eax` | node+8 = idx | [V] |
| atlas node+0x10 dispatch object | node+0x10 | 8 | `0x18711c9 mov [rdi+0x10],rdx` | `0x18711c9  mov [rdi+0x10],rdx` | node+0x10 = 0x150 dispatch object | [V] |
| atlas node+0x18/0x20/0x28 name/region/extent | node+0x18/0x20/0x28 | 8 | `0x1871271 mov [rdi+0x18],r15`; `0x1871275 mov [rdi+0x20],r15`; `0x187127f mov [rdi+0x28],rsi` | `0x1871271  mov [rdi+0x18],r15` | node+0x18/0x20/0x28 = name/region/extent pointers | [V] |
| atlas registry '*' sentinel + slot scan | registry dword array | 4 | `0x1870e30 cmp dword ptr [rcx],0x2A`; `0x1870f28 inc r14d`; `0x1870f2b cmp r14d,0x29`; `0x1870f40 mov [r15],r14d` | `0x1870e30  cmp dword ptr [rcx],0x2A` | slots 0..41 scanned for '*' (0x2A) sentinel; found index written to [r15] | [V] |
| createTexture entry (vtable slot 26 -> TextureD3D12::create) | rva 0xe8143c0 | 5 (call rel32) | `0xe81455b call 0xE81BF30` | `0xe81455b  call 0xE81BF30` | slot 26, indirect vtable call; 0 static callers | [V] |
| TextureD3D12::create desc+0xB0 format byte | desc+0xB0 | 1 | `0xe81c077 mov [rdi+0xB0],r13b`; `0xe81c12b cmp byte ptr [rdi+0xB0],0x42` | `0xe81c077  mov [rdi+0xB0],r13b` | format byte; fallback compares 0x42 ('B'); per-format word table `0xe81c022 movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| TextureD3D12::create desc+0xB1 numMips byte | desc+0xB1 | 1 | `0xe81c0d1 mov [rdi+0xB1],dl` | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte | [V] |
| resizeTexture entry (vtable slot 31) | rva 0xe815840 | 4 | `0xe815866 mov edi,r9d` | `0xe815866  mov edi,r9d` | r9d = mips param; 0 static xrefs; never observed live | [V] |
| live texture census | live l8b_texcreate_record.txt / createtexture_callers.txt | - | capture files (no instruction line) | - | 24 TextureD3D12::create samples all format 0x1C, numMips=1, names "Texture: 2815"/"Texture: 2799"/"tex"; 32 createTexture samples all ret=0xBC6A2C8 command interpreter; zero atlas names; zero compressed formats | [V live] |
| TexturePtr ensure-load chain | rva 0x1289490 | 6 (call qword ptr [disp32]) | `0x1289490 call qword ptr [0xF99FFA0]`; `0x1289496 nop` | `0x1289490  call qword ptr [0xF99FFA0]` | sub_12893d0 -> sub_4e05e50, ret=0x1289496; objects carry cross-module +0x00 = 0x7FF6A8215838 outside exe image; livemem read attempted, now unreadable | [V] + read attempted [V live, unreadable] |
| compression strings | BC1/BC3/BC7/DXT1-DXT5 | - | xref str refs=[] | - | no compression path statically; only PNG/zlib decompression exists | [V] |
| mip generation | GenMip/MipMap/mipchain | - | xref str refs=[] | - | no mip generator code; material mip keys num_mip_levels 0x4e1a7e9, mip_fade_amount 0x4e1b275, mip_fade_color 0x4e1b29b, mip_chain 0x11528cf are load-time params; glGenerateMipmap@0xe92c2c0 is GLES glue only | [V] |
| shadow atlas (separate, not Terrain/Item) | rva 0xbb682b0 | - | string PointLightShadowTextureAtlas `0xf55cdfe` @0xbb68563 | - | shadow atlas exists in the exe | [V] |
| BlockThumbnailAtlas description builder (tangential) | rva 0x1585e00 | - | first 80 instrs build 0x130 description object at a0+0x90 via sub_15ab4d0 | - | idx 0x26; description-object builder only, no texture creation seen; not the Terrain/Item stitcher | [V] |

## CLOSES?
NO — single blocking fact: the atlas TEXTURE-CREATION STITCHER for TerrainAtlas (idx 6) and ItemAtlas (idx 7) is not located in the exe. Registration is proven [V] (both names exist in the exe; nodes allocated 0x48 bytes with name/idx/dispatch-object fields; registry slots 0..41), but no static path leads from the registered node to createTexture/resizeTexture: createTexture has 0 static callers and every live sample returns to 0xBC6A2C8 (bgfx command interpreter); resizeTexture slot 31 (mips param) has 0 static xrefs and was never observed live. Mip generation is absent [V] (no GenMip/MipMap code; all live creations numMips=1 [V live]) and BC1/BC3/BC7 compression is absent [V] (strings unreferenced; only PNG/zlib decompression; live census all format 0x1C [V live]). Registered objects carry a cross-module +0x00 pointer (0x7FF6A8215838, outside the exe image 0x7ff7a59c0000..0x7ff7bd2fe000) that livemem can no longer read (stale capture-instance pointers; attempted livemem, unreadable). Creation is likely bgfx command-stream driven at level load or in another module (CPU decode / data-driven) — parked MIRROR_SKIP/external. CLOSES? NO unless the already-queued l8b_resizetex_slot31 capture returns a stitcher caller chain with atlas names and mips>1.

## WHAT I TRIED THAT FAILED (this session; do not redo)
- descscan2.py: TypeError in ranges_for — unusable for walking the description build.
- livemem read/vt on captured object addresses (e.g. 0x7FF6A8215838): unreadable now — pointers were from a previous capture instance; cited as attempted livemem.
- xref str "Atlas": only tangential hits — 0x1585e00 builds a 0x130 description object at a0+0x90 for BlockThumbnailAtlas idx 0x26 via sub_15ab4d0 (no texture creation in first 80 instrs); shadow atlas 0xbb682b0; mip sampling funcs 0xbc7f6e0/bcd77b0.
- xref str "Mip": mip-key strings only (load-time params), no generator code.
- Backward chain from createTexture: exhausted — 0 static callers; all live callers ret=0xBC6A2C8 command interpreter; l8b_texcreate_record.txt (24 samples) all format 0x1C numMips=1, no atlas names.
- Forward stitcher from registration objects: sub_2fe440 is cleanup-only (frees NULL scratch; `0x186f78f call 0xE935700`), sub_772520 registers name+idx only, no createTexture/resizeTexture inside sub_186e6a0/sub_1870de0/sub_772520 [V]. Not located.

## TOOL REQUESTS
l8b_resizetex_slot31 | python tools/livecap/request.py add l8b_resizetex_slot31 0xe815840 --size 0x100 --max 6 --why "L8b: resizeTexture slot 31 (mips param r9d) — who calls it, does desc carry atlas names or mips>1" | already queued (earlier run), awaiting orchestrator execution; result would return the resizeTexture caller (ret=) and desc bytes (mips, format, atlas names) — the one observation that could close the stitcher question. No new request filed.
