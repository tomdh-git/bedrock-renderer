## NEXT
DONE

## Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Exe = Minecraft.Windows.exe 1.26.62.01 at base 0x7ff605be0000 (game running pid 8420; livemem read-only OK).

### Proven [V]

Atlas registration inside sub_186e6a0 via sub_1870de0:
- 0x48-byte node allocated: `0x1870e70  mov edx,0x48` / `0x1870e75  call qword ptr [0xF99FFA0]`
- Name stored at node+0: `0x1870ec5  mov [rsi],rax`
- Slot index stored at node+8: `0x1870ecb  mov [rsi+8],eax`
- Fixed registry scanned for 0x2A '*' sentinel: `0x1870e30  cmp dword ptr [rcx],0x2A`, bound `0x1870f28  inc r14d; 0x1870f2b  cmp r14d,0x29` (slots 0..41)
- Registered slot index written: `0x1870f40  mov [r15],r14d`

Four registered objects (names referenced ONLY inside sub_186e6a0):
- 'TerrainAtlas' idx 6, str 0xF55CDD3: `0x186f731  lea rax,[0xF55CDD3]`
- 'ItemAtlas' idx 7, str 0xF55CDE0: `0x186f7fc  lea rax,[0xF55CDE0]`
- 'AnimatedAtlas' idx 8, str 0xF55CE42: `0x186f8c7  lea rax,[0xF55CE42]`
- 'BlockThumbnailAtlas' idx 0x26, str 0xF55CDEA: `0x186f996  lea rax,[0xF55CDEA]`
- 'MaterialTerrainTextureAtlas' str 0xF55CE1B refs=[] [V via xref]

Triggered by ServerLevelLoad sub_1042320 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810.
sub_186e6a0 (0x186e6a0..0x18706a0, size 0x2000, 2 static xrefs) contains NO createTexture/resizeTexture call.

Post-registration: node consumed by sub_2fe440 (`0x186f782  call 0x2FE440`, pure cleanup — frees desc buffers +0xF8/+0xB0/+0x98 via `call 0xE935700`) then freed by sub_e935700 edx=0x138 (`0x186f78f  call 0xE935700`) — discarded, NOT retained. No reader/stitcher of registered objects located in exe.

Item atlas names as DATA only (never passed to createTexture/resizeTexture):
- 'atlas.items' str 0xF550917: `0x575527c  lea rdx,[0xF550917]` -> item+0x78 via `call 0x7F1A0`
- 'textures/items/compass_atlas' str 0xF55CCD6: `0x5755303  lea rdx,[0xF55CCD6]` -> item+0x78 via `call 0x7F1A0`

### Texture creation entry points (renderer vtable 0xF4ED2D0 [V via rdis vt])

- Slot 26 = sub_e8143c0 createTexture: `0xe8143c0  push rbp`; builds bimg params; `0xe81455b  call 0xE81BF30` -> TextureD3D12::create; ret `0xe814560  nop`; 0 static xrefs
- Slot 31 = sub_e815840 resizeTexture: `0xe815840  push rbp`; takes mips `0xe815866  mov edi,r9d`; texture table base `0xe815876  lea rsi,[rcx+0xBDE178]`, stride 0xB8; 0 static xrefs; NEVER observed live
- Slot 29 = sub_e814a70, slot 30 = sub_e8150f0 (both 0 xrefs in)

TextureD3D12::create entry 0xe81bf30; callers = createTexture + resizeTexture only [V via xref].
- +0xB0 actual format: `0xe81c077  mov [rdi+0xB0],r13b`
- +0xB1 numMips: `0xe81c0d1  mov [rdi+0xB1],dl`
- Uncompressed fallback: `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42`
- Format table: `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]`

### Live captures [V live]

- l8b_texcreate_record (rva 0xE81BF30, 24 samples): CALLER ret=0xE814560; all format 0x1C numMips=1; ZERO atlas names
- createtexture_callers (rva 0xE8143C0, 25 hits): CALLER ret=0xBC6A2C8 inside bgfx executor sub_bc6a290; format 0x1C sizes 128x128/64x64; ZERO atlas names/mips>1/compressed
- l8b_resizetex_slot31 + _b (rva 0xE815840): BOTH EMPTY (no hits) — resizeTexture slot 31 never triggered even with resource-pack-reload retry

### Blit side [V]

- 'TerrainAtlasBlit' task `0xbb431ee  lea rdx,[0xF539A0B]` (task 16, functor vtable 0xF43E9E0); 'BlitUncompressed' `0x560be9f  lea r9,[0xF5F440C]`; no ItemAtlasBlit task

### Mip generation [V] NOT located

xref GenMip/Mips/MipMap/mipchain -> refs=[]; no mip-gen Blit task; numMips only at +0xB1; all live creations numMips=1; sampler bit 10 = mip FILTER usage not generation [I].

### Compression (BC1/BC3/BC7/DXT) [V] provably ABSENT

All those strings unreferenced [V via xref]; only PNG/zlib decompression exists; create path uncompressed; live census all-uncompressed format 0x1C.

### Stitcher — NOT located (blocking fact)

No code builds TerrainAtlas(idx6)/ItemAtlas(idx7) texture description and calls createTexture(slot26) or resizeTexture(slot31) with atlas parameters. Registration proven; creation not found; objects discarded after registration; no reader/stitcher located.

New angles attempted (all negative): rdis dis slot 29/30 (0 xrefs in); xref callers 0xe814a70/0xe8150f0 empty; xref str 'MaterialTerrainTextureAtlas' refs=[]; livemem read 0x7FF6A8215838 unreadable/not in any user module; l8b_resizetex_slot31 + _b captures empty; sub_2fe440 decoded = pure cleanup/free; rdis callers/xr on sub_186e6a0 = exactly 2 callers/no other refs; rdis xr on createTexture = 0 static xrefs.

### Answer table

| offset | size | site | instr | meaning |
|--------|------|------|-------|---------|
| +0x00 | 8/4 | [rsi]+0x00 / [rcx]+0x00 | `0x1870ec5  mov [rsi],rax` / `0x1870e30  cmp dword ptr [rcx],0x2A` | Atlas name pointer at node+0 / registry '*' (0x2A) sentinel scan, slots 0..41 |
| +0x08 | 4 | [rsi]+0x08 | `0x1870ecb  mov [rsi+8],eax` | Atlas slot index stored at node+8 |
| +0xB0 | 1/1/8 | [rdi]+0xB0 / [rdi]+0xB0 / [rsi]+0xB0 | `0xe81c077  mov [rdi+0xB0],r13b` / `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0x2fe4ab  mov rcx,[rsi+0xB0]` | TextureD3D12::create actual format at +0xB0 (all live 0x1C uncompressed) / uncompressed fallback check / post-registration desc buffer freed by sub_2fe440 |
| +0xB1 | 1 | [rdi]+0xB1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips stored at +0xB1 (all live numMips=1) |
| +0xF8 | 8 | [rsi]+0xF8 | `0x2fe484  lea rdi,[rsi+0xF8]` / `0x2fe48b  call 0xE935700` | Post-registration desc buffer at +0xF8 freed by sub_2fe440 |
| +0x98 | 8 | [rsi]+0x98 | `0x2fe500  mov rcx,[rsi+0x98]` / `0x2fe53e  call 0xE935700` | Post-registration desc buffer at +0x98 freed by sub_2fe440 |

CLOSES? NO — atlas texture-creation stitcher not located in exe. Registration proven; creation (createTexture slot 26 / resizeTexture slot 31 with atlas parameters) not found; registered objects discarded after registration; mip generation absent; compression absent (all live creations format 0x1C numMips=1 uncompressed).
