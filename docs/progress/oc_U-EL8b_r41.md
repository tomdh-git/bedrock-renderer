## NEXT
DONE

# Unit U-EL8b — Atlases (terrain, items), mipmaps and compression (Minecraft.Windows.exe 1.26.62.01, PE ImageBase 0x140000000)

GOAL: close checklist item L8b (terrain atlas idx6 / item atlas idx7 registration, mipmaps, BC1/BC3/BC7 compression).
VERDICT: registration YES [V]; mipmaps NO [V + V live]; BC1/BC3/BC7 compression NO [V + V live]. The atlas stitcher (who builds the atlas texture description from the registered nodes) is NOT in the exe — static search exhausted; the live object's +0x00 pointer 0x7FF6A8215838 resolves outside the Minecraft.Windows.exe image [V live mc_root_4e05e50_callers.txt:4], consistent with atlas logic living in another module or being data-driven.

## 1. Atlas registration [V] — sub_186e6a0 / sub_1870de0

sub_186e6a0 (0x186e6a0..0x18706a0, size 0x2000, exactly 2 static xrefs in: initStep1 sub_8f6810 at `0x8f6919  call 0x186E6A0` and ServerLevelLoad sub_1042320 at `0x104237e  call 0x186E6A0`) is the registration dispatcher. Entry `0x186e6a0  push rbp`; it installs the dispatch object from data_efcc480 (`0x186e6cc  lea rax,[0xEFCC480]`, `0x186e6d3  mov [rcx],rax`) and allocates an 0x18-byte object via `0x186e6e4  mov edx,0x18` / `0x186e6e9  call qword ptr [0xF99FFA0]`. Per registered name it builds a {ptr,len} name descriptor and calls sub_1870DE0. The listing of sub_186e6a0 (0x186e6a0..0x1870358) contains NO createTexture (0xe8143c0/0xe81bf30), resizeTexture (0xe815840) or createDynamicTexture (0xbc74a80) call [V listing].
- TerrainAtlas: `0x186f731  lea rax,[0xF55CDD3]` (string data 0xF55CDD3), len `0x186f73f  mov qword ptr [rbp+0x108],0xC`, idx `0x186f767  mov r9d,6`, `0x186f76d  call 0x1870DE0` → registered idx 6 [V]
- ItemAtlas: `0x186f7fc  lea rax,[0xF55CDE0]`, len `0x186f80a  mov qword ptr [rbp+0x118],9`, idx `0x186f832  mov r9d,7`, `0x186f838  call 0x1870DE0` → registered idx 7 [V]
- AnimatedAtlas idx 8: `0x186f8c7  lea rax,[0xF55CE42]`, `0x186f8fd  mov r9d,8` [V]; BlockThumbnailAtlas idx 0x26 also registered [V carried].

sub_1870DE0 (rcx=manager object, rdx={name ptr,len}, r8=output slot, r9d=registration index): the registry is a dword array at manager+0x20/+0x28 scanned for the '*' (0x2A) sentinel and bounded at slot 0x29: `0x1870e30  cmp dword ptr [rcx],0x2A` ; `0x1870e4c  cmp r14d,0x29` (loop bound; rescan path `0x1870f28  inc r14d`, `0x1870f2b  cmp r14d,0x29`) [V]. On a '*' slot it allocates the 0x48-byte node (`0x1870e70  mov edx,0x48`, `0x1870e75  call qword ptr [0xF99FFA0]` -> sub_eea6040), takes the dispatch object from the registry head and nulls the source slot (`0x1870e93  mov qword ptr [rcx+0x10],0`, `0x1870ebe  mov qword ptr [rcx],0`), then initializes the node:
- `0x1870ec5  mov [rsi],rax` — node+0x0 = dispatch object [V]
- `0x1870ecb  mov [rsi+8],eax` — node+0x8 = atlas idx from caller r9d [V]
- `0x18711c9  mov [rdi+0x10],rdx` — node+0x10 = name pointer [V]
- `0x18711d0  movups [rdi+0x18],xmm0` — node+0x18 zeroed (16-byte store) [V]
- `0x1871271  mov [rdi+0x18],r15` — node+0x18 = name length [V]

Right after each registration the object is consumed, not kept: `0x186f782  call 0x2FE440` then `0x186f78f  call 0xE935700` (edx=0x138) — sub_2FE440 (cleanup-only: releases description buffers +0xF8/+0xB0/+0x98 and refcounts) followed by sub_E935700 free [V carried]. The sub_1870DE0 → sub_2FE440 → sub_E935700 pattern repeats for every registered name in sub_186e6a0 [V listing].

## 2. Stitcher: not located [V + ?]

- xref str "TerrainAtlas" → only `0x186f731` inside sub_186e6a0; "ItemAtlas" → only `0x186f7fc` inside sub_186e6a0 [V via xref]. No other code references either name, so no stitcher / texture-creation site names them in .text.
- Texture creation entry points: TextureD3D12::create 0xe81bf30 has exactly one static caller `0xe81455b  call 0xE81BF30` (next instr `0xe814560 nop`, observed live as ret=0xe814560 [V live l8b_texcreate_record.txt:3]); resizeTexture slot 31 at 0xe815840 (`0xe815840  push rbp`, `0xe815866  mov edi,r9d` -> r9d = mips param) has 0 static xrefs and was never observed live [V]. No static path from the registered atlas nodes to either [V].
- sub_1042320 (ServerLevelLoad) after sub_186e6a0 only re-enters sub_1870de0 with idx 0x28/0x29 load-phase names then frees them — no atlas texture creation [V carried].
- Cross-module object pointer: live MC_obj+0x00 = 0x7FF6A8215838, outside the exe image (ImageBase 0x140000000; exe range ~0x7ff7a59c0000..0x7ff7bd2fe000) [V live mc_root_4e05e50_callers.txt:4]. Stitcher/mip/compression logic may live in another module or be data-driven → not statically decidable from the exe.

## 3. Mipmaps [V + V live]

- desc+0xB1 is the only numMips store: `0xe81c0d1  mov [rdi+0xB1],dl` [V]. Live census l8b_texcreate_record.txt (entry 0xe81bf30, 24 samples): every creation numMips=1 [V live lines 4-27]. numMips>1 would be mip-generation evidence; none exists.
- resizeTexture slot 31 (0xe815840): 0 static xrefs, never live → no mip-generation path [V].

## 4. Compression [V + V live]

- desc+0xB0 is the format store: `0xe81c077  mov [rdi+0xB0],r13b` [V]; format fallback path `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` (0x42 uncompressed fallback) [V]. BC1/BC3/BC7/DXT1-DXT5 strings unreferenced in .text [V via xref]; only PNG/zlib decompression exists [V carried].
- Live census: all 24 creations format 0x1C uncompressed, names "tex"/"Texture: ####", zero atlas names [V live l8b_texcreate_record.txt:4-27].

## ANSWER TABLE (offset | size | site | verbatim `0xRVA  instr` | meaning | tag)

| Atlas node +0x0 dispatch object | node+0x0 | 8B | [rsi] node init in sub_1870DE0 | `0x1870ec5  mov [rsi],rax` | node+0 = dispatch object taken from registry head; source nulled by `0x1870e93  mov qword ptr [rcx+0x10],0` and `0x1870ebe  mov qword ptr [rcx],0` | [V] |
| Atlas node +0x8 idx | node+0x8 | 4B | [rsi+8] node init | `0x1870ecb  mov [rsi+8],eax` | node+8 = atlas idx from caller r9d: TerrainAtlas 6 (`0x186f767  mov r9d,6`), ItemAtlas 7 (`0x186f832  mov r9d,7`), AnimatedAtlas 8 (`0x186f8fd  mov r9d,8`) | [V] |
| Atlas node +0x10 name pointer | node+0x10 | 8B | [rdi+0x10] node init | `0x18711c9  mov [rdi+0x10],rdx` | node+0x10 = name buffer pointer holding the registered atlas name string | [V] |
| Atlas node +0x18 name length | node+0x18 | 8B | [rdi+0x18] node init | `0x1871271  mov [rdi+0x18],r15` | node+0x18 = name length (zeroed first by movups xmm0 store at 0x18711d0) | [V] |
| Registry '*' sentinel | reg+0 scan | 4B | [rcx] sentinel scan in sub_1870DE0 | `0x1870e30  cmp dword ptr [rcx],0x2A` | slot terminator is '*' (0x2A) | [V] |
| Registry slot bound | reg+0 bound | 4B | loop bound in sub_1870DE0 | `0x1870f2b  cmp r14d,0x29` | slots scanned 0..41 (0x29), step `0x1870f28 inc r14d` | [V] |
| Texture desc +0xB0 format byte | desc+0xB0 | 1B | [rdi+0xB0] TextureD3D12::create | `0xe81c077  mov [rdi+0xB0],r13b` | desc+0xB0 = format byte; fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42`; live format 0x1C uncompressed | [V + V live] |
| Texture desc +0xB1 numMips byte | desc+0xB1 | 1B | [rdi+0xB1] TextureD3D12::create | `0xe81c0d1  mov [rdi+0xB1],dl` | desc+0xB1 = numMips byte; only numMips store located; live numMips=1 | [V + V live] |
| TextureD3D12::create entry (slot 26) | 0xe81bf30 | – | `0xe81455b` static call site | `0xe81455b  call 0xE81BF30` | only static caller of createTexture entry 0xe81bf30; ret=0xe814560 nop observed live | [V + V live] |
| resizeTexture slot 31 entry | 0xe815840 | – | `0xe815840` function entry | `0xe815840  push rbp` ; `0xe815866  mov edi,r9d` | resizeTexture entry; r9d = mips param; 0 static xrefs, never live | [V] |

## CLOSES?

NO — not as stated. Registration YES [V]: TerrainAtlas idx 6 and ItemAtlas idx 7 are registered in sub_186e6a0 via sub_1870de0 (0x48-byte nodes, name at +0, idx at +8), triggered by ServerLevelLoad sub_1042320 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810 (`0x8f6919  call 0x186E6A0`). Mipmaps NO [V + V live]: numMips only store is desc+0xB1; every live creation numMips=1; resizeTexture slot 31 never called. BC1/BC3/BC7 compression NO [V + V live]: BC strings unreferenced; all live creations format 0x1C uncompressed. The atlas stitcher is not located in the exe (no consumer of the registered nodes; objects consumed by sub_2FE440 then freed by sub_E935700; cross-module pointer 0x7FF6A8215838 [V live] outside the exe image). L8b as a compound item (registration + mipmaps + BC compression on terrain/item atlases) is therefore NOT present in this build; the missing stitcher location and any runtime atlas format/mips require the other module or live data — not decidable statically.

## TOOL REQUESTS

- l8b_resizetex_slot31 (rva 0xe815840) — pending in docs/progress/capture_requests.json (queue at 4/4 cap). ret= would name the stitcher caller; mips>1 or atlas parameters at resizeTexture would flip the mip/atlas question. Re-add once the queue drains.
- sub_1289440_callers (rva 0x1289440) — pending; would name sub_12893d0's runtime callers (texgroup_load 0x5421c90 / texload 0x58a1310 connection).
- livemem read of cross-module pointer 0x7FF6A8215838: not needed for the L8b verdict (static analysis settled registration/mips/compression); optional only if the orchestrator wants the other module identified.
- No helper scripts written this unit.
