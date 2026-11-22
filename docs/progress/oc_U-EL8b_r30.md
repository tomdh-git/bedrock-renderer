## NEXT
DONE

# Unit U-EL8b — Atlases (terrain, items), mipmaps and compression

## Blocking fact (single)
Atlas texture-creation stitcher not located in the exe; BC1/BC3/BC7/DXT strings all unreferenced; mip generation not located (numMips only at texture record +0xB1); all live creations numMips=1 format 0x1C. Static analysis exhausted — all creation entry points enumerated and negative; cross-module pointer 0x00007FF6A8215838 (from l8b_texcreate_record / mc_root_4e05e50_callers) points outside the exe image, suggesting atlas logic lives in another module or is data-driven. Needs live capture (l8b_resizetex_slot31 pending at rva 0xE815840) or a decision to mark as external / parked in MIRROR_SKIP.

## What was tried that failed (new angles vs r29)

1. **Direct decode of sub_1870de0 [0x1870de0..0x18716f5]** (new angle, replaces r29's second-hand reading):
   - `0x1870e70  mov edx,0x48` — allocation size exactly 0x48 bytes [V]
   - `0x1870e75  call qword ptr [0xF99FFA0]` — sub_eea6040 allocator call [V]
   - `0x1870ec5  mov [rsi],rax` — obj+0 = old head pointer (linked list), NOT name [V direct decode]
   - `0x1870ecb  mov [rsi+8],eax` — obj+8 = index (6=TerrainAtlas, 7=ItemAtlas) [V]
   - Name stored separately: inline [rbp-0x10] buffer (small, len<0x10) or heap (large, len>=0x10) [V]
   - Conclusion: registration stores idx+head only, no texture creation inside sub_1870de0 [V]

2. **descscan2 on sub_2fe440 [0x2FE440..0x2FE572]** (new angle, sub_2fe440 is called right after registration by sub_186e6a0):
   - sub_2fe440 reads fields at +0x98/+0xA8/+0xB0/+0xC0/+0xC8/+0xF8/+0x108 — ALL beyond the 0x48-byte registered object [V descscan2]
   - This proves sub_2fe440 is NOT operating on the registered atlas object; it's a different cleanup function [I from field offsets]
   - sub_186e6a0 passes the registered object to sub_2fe440, but sub_2fe440's field layout (0x98+) doesn't match [I contradiction]

3. **All texture-creation entry points enumerated and negative** (redo not needed, confirmed by r29 + live captures):
   - createTexture slot 26 -> TextureD3D12::create 0xe81bf30 [V BGFX_MAP.md line 1812]
   - resizeTexture slot 31 handle,w,h,mips,layers [V BGFX_MAP.md line 1511]
   - l8b_texcreate_record.txt: 24 samples, all format 0x1C uncompressed, numMips=1, ZERO atlas names [V live]
   - mc_root_4e05e50_callers.txt: ret=0x1289496 inside sub_12893d0 `0x1289490 call qword ptr [0xF99FFA0]`; RCX+0 = cross-module pointer 0x00007FF6A8215838 outside exe [V live]

4. **xref for BC1/BC3/BC7/DXT strings** — all unreferenced (no compression path found) [V via xref, r29]

5. **Mip generation** — not located; numMips only written at texture record +0xB1 `0xe81c0d1 mov [rdi+0xB1],dl` [V BGFX_MAP.md line 1885]

## Findings table

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning |
|--------|------|-------------------|------------------------------|---------|
| obj+0 | 8 | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | old head pointer stored at registered object +0 (linked-list next), NOT name [V direct decode of sub_1870de0] |
| obj+8 | 4 | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index stored at registered object +8 (6=TerrainAtlas, 7=ItemAtlas) [V direct decode of sub_1870de0] |
| alloc size | - | 0x1870e70 | `0x1870e70  mov edx,0x48` | allocation size exactly 0x48 bytes via sub_eea6040 [V direct decode] |
| alloc call | - | 0x1870e75 | `0x1870e75  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator call [V direct decode] |
| +0xF8 | 8 | 0x2FE449 | `0x2FE449  mov rcx,[rcx+0xF8]` | sub_2fe440 reads qword at +0xF8 — beyond 0x48-byte registered object [V descscan2 + rdis] |
| +0x98 | 8 | 0x2FE500 | `0x2FE500  mov rcx,[rsi+0x98]` | sub_2fe440 reads qword at +0x98 [V descscan2 + rdis] |
| +0x108 | 8 | 0x2FE455 | `0x2FE455  mov rdx,[rsi+0x108]` | sub_2fe440 reads qword at +0x108 [V descscan2 + rdis] |
| +0xA8 | 8 | 0x2FE50C | `0x2FE50C  mov rdx,[rsi+0xA8]` | sub_2fe440 reads qword at +0xA8 [V descscan2 + rdis] |
| +0xB0 | 1/8 | 0x2FE4AB / 0x2FE4F9 | `0x2FE4AB  mov rcx,[rsi+0xB0]` / `0x2FE4F9  mov byte ptr [rsi+0xB0],0` | sub_2fe440 reads byte/qword at +0xB0, writes byte 0 at +0xB0 [V descscan2 + rdis] |
| +0xC0 | 8 | 0x2FE4E3 | `0x2FE4E3  mov qword ptr [rsi+0xC0],0` | sub_2fe440 writes qword 0 at +0xC0 [V descscan2 + rdis] |
| +0xC8 | 8 | 0x2FE49E / 0x2FE4EE | `0x2FE49E  mov rax,[rsi+0xC8]` / `0x2FE4EE  mov qword ptr [rsi+0xC8],0xF` | sub_2fe440 reads qword at +0xC8, writes qword 0xF at +0xC8 [V descscan2 + rdis] |
| createTexture slot 26 | - | 0xE8143C0 | - | texture creation entry point; base of slot 26 (RTX thunk 0xe83d400 tracks handle) [V BGFX_MAP.md line 1812] |
| TextureD3D12::create | - | 0xE81BF30 | - | texture create implementation called by createTexture [V BGFX_MAP.md line 1812; live capture ret=0xE814560 `0xe81455b call 0xE81BF30`] |
| resizeTexture slot 31 | - | 0xE815840 | - | resizeTexture(handle,w,h,mips,layers) entry point [V BGFX_MAP.md line 1511] |
| texture record +0xB0 | 1 | 0xE81C0D1 | `0xE81C0D1  mov [rdi+0xB1],dl` | actual format at +0xB0 (0x42 fallback when caps lack type); +0xB1 = numMips [V BGFX_MAP.md lines 1812, 1885] |
| texture record +0xB1 | 1 | 0xE81C0D1 | `0xE81C0D1  mov [rdi+0xB1],dl` | numMips stored at texture record +0xB1 [V BGFX_MAP.md lines 1812, 1885] |
| BC1/BC3/BC7/DXT strings | - | - | - | all unreferenced in .text; no compression path found statically [V via xref, r29] |
| mip generation | - | - | - | not located in exe; only material mip params + numMips +0xB1 found [V] |
| MaterialTerrainTextureAtlas | - | - | - | "string only, referenced via table" — no code directly references it [V BGFX_MAP.md line 337] |
| cross-module pointer | 8 | - | - | RCX+0 = 0x00007FF6A8215838 outside exe image; unreadable by livemem [V live mc_root_4e05e50_callers.txt] |

## CLOSES?

NO — Single blocking fact: atlas texture-creation stitcher not located in the exe. Static analysis exhausted: (1) sub_186e6a0/sub_1870de0 register atlas objects (0x48 bytes, idx at +8) but contain NO createTexture/resizeTexture call [V]; (2) sub_2fe440 (called after registration) reads fields at +0x98+ beyond the 0x48-byte object — not the stitcher [V descscan2]; (3) all texture-creation entry points enumerated (0xe8143c0, 0xe815840, 0xe81bf30) — live captures show all creations format 0x1C, numMips=1, zero atlas names [V live]; (4) BC1/BC3/BC7/DXT strings all unreferenced [V via xref]; (5) mip generation not located — numMips only at texture record +0xB1 [V]. Cross-module pointer 0x00007FF6A8215838 suggests atlas logic in another module / data-driven. l8b_resizetex_slot31 capture (rva 0xE815840) is PENDING (queue full at 4: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc). Cannot close until capture returns or a decision is made to mark as external/parked.

## TOOL REQUESTS

None — all 4 capture queue slots are pending; l8b_resizetex_slot31 (rva 0xE815840, resizeTexture slot 31) is already queued and waiting for the orchestrator to run it. No new scripts written; descscan2.py and rdis.exe used directly per brief toolbox.
