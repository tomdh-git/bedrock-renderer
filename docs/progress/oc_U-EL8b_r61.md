## NEXT
DONE - U-EL8b complete: atlas registration proven [V]; atlas texture-creation stitcher, mip generation and BC compression all provably absent/external [V live + V]; CLOSES? NO (single blocking fact: stitcher not in this exe, cross-module pointer 0x7FF6A8215838, static analysis exhausted per orchestrator hint 2026-11-22).

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression — RETRY #1

Goal: close checklist item "L8b Atlases (terrain, items), mipmaps and compression pending".
Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched.
Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted), [I] inferred from that, [?] unknown / not located, [V live] read-only live capture (docs/data/live/*.txt).

## Status carried from prior attempts (oc_U-EL8b_r1..r36 — NOT re-derived)

- Atlas registration PROVEN [V]: "TerrainAtlas" idx 6 and "ItemAtlas" idx 7 registered inside sub_186e6a0 via sub_1870de0 (0x48-byte node; +0 prev, +8 idx, +0x10 dispatch object, +0x18/+0x20/+0x28 name/region), registry slot array scanned for '*' (0x2A) sentinel over slots 0..41.
- Triggered by ServerLevelLoad sub_1042320 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810 (`0x8f6919  call 0x186E6A0`). [V]
- sub_186e6a0/sub_1870de0/sub_772520 contain NO createTexture/resizeTexture call [V]; post-registration objects are not consumed by any located reader; sub_2fe440 call is skipped (`0x186f77d  je short 0x186F794` taken since scratch+0=0) then `0x186f78f  call 0xE935700` frees NULL. xref of "TerrainAtlas"/"ItemAtlas" shows refs only inside sub_186e6a0 [V].
- TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; createTexture has 0 static callers (indirect via vtable slot 26).
- TexturePtr chain: sub_4e05e50 (ensure-loaded/upload) entered only from sub_12893d0 (ret=0x1289496) [V live]; upload path to sub_bc41420 confirmed [V]. texgroup_load/texload are consumers, not creators [V].
- Live census [V live]: mc_root_4e05e50_callers.txt + l8b_texcreate_record.txt + createtexture_callers.txt — all texture creations format 0x1C uncompressed, numMips=1, ZERO atlas names; object +0x00 carries cross-module pointer 0x00007FF6A8215838 (outside exe image 0x7ff7a59c0000..0x7ff7bd2fe000).
- BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; mip generation not located (numMips only stored at desc+0xB1) [V]; material mip keys are load-time params [V].

## NEW ANGLE TRIED THIS SESSION (blocking fact: atlas texture-creation STITCHER not located)

1. Re-read docs/data/live/mc_root_4e05e50_callers.txt (150 hits, 32 samples): line 3 `CALLER ret=0x1289496` — sub_4e05e50 entered only from sub_12893d0; objects carry +0x00 = 0x00007FF6A8215838 (cross-module). Consumers only, no stitcher [V live].
2. Re-read docs/data/live/l8b_texcreate_record.txt (24 samples): line 3 `CALLER ret=0xE814560` — all creations format 0x1C uncompressed, numMips=1, names "Texture: 2815"/"Texture: 2799"/"tex", no atlas names [V live].
3. Read NEW L8a chain captures (producer→entry→wrapper→createTexture per orchestrator hint 2026-11-22):
   - bgfx_createtexture_producer rva=0xBC73770 (ret=0xBC73EAD): RDX/R8 description objects carry "TEXC" type tag, format 0x1C, texture PATH names ("textures/entity/...", "vanilla.CoreData", UUIDs, "ApplyGradientWith") and cross-module vtable ptrs at desc+0x20/+0x28 (0x7FF6A8441980/90) — NO atlas names [V live].
   - dragon_texture_entry rva=0xC296B50 (CALLER ret=0xBC41B3E): format 0x1C, numMips=1 [V live].
   - dragon_texture_caller rva=0xBC41420 (CALLER ret=0x4E05F7C = return into sub_4e05e50 after `0x4e05f77  call 0xBC41420`): RCX description objects format 0x1C, "tex" name, 240x60, numMips=1 — upload path, not creation [V live].
   - bgfx_texture_wrapper rva=0xBC73BF0 (CALLER ret=0xC296D7E): header only, no samples.
   Result: the whole producer chain creates ordinary textures (path-named, uncompressed, numMips=1), never an atlas; no stitcher caller [V live].
4. Read docs/data/live/texture_table.txt (2950+ handles): record = ctx+0xBDE178+h*0xB8, width @+0x18, height @+0x20, DXGI_FORMAT @+0x28 — ALL handles uncompressed (fmt 28 dominant; 11/61/26/10/41/44 also uncompressed), ZERO BC formats, no atlas names (handle-only table) [V live].
5. Cross-module pointer 0x7FF6A8215838 at obj+0x00: outside the exe image; livemem read/vt attempted (docs/data/live/readlog.txt lines 125/144-145/164-168/212) but the module was never identified and the pointers are now unreadable (stale capture instance) [V live carried].

Result: no new angle located the stitcher. The single blocking fact stands.

## ANSWER TABLE (one row per distinct field offset; verbatim `0xRVA  instr` quoted from rdis; sizes from the instruction)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning shown by instruction or string | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas registered name string | str data 0xF55CDD3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" name loaded; len 0xC at `0x186f73f  mov qword ptr [rbp+0x108],0xC`; registered idx 6 (`0x186f767  mov r9d,6`) inside sub_186e6a0 | [V] |
| ItemAtlas registered name string | str data 0xF55CDE0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" name loaded; len 9 at `0x186f80a  mov qword ptr [rbp+0x118],9`; registered idx 7 (`0x186f832  mov r9d,7`) — item-atlas name EXISTS in the exe | [V] |
| sub_1870de0 node alloc size | code 0x1870e70 | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocates a 0x48-byte registration node via `0x1870e75  call qword ptr [0xF99FFA0]` | [V] |
| registration node +0 prev/scratch | node +0x0 | 8 (qword store) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | node+0 = 0 (rax = [&scratch], zeroed by `0x1870ebe  mov qword ptr [rcx],0`) inside sub_1870de0 | [V] |
| registration node +8 index | node +0x8 | 4 (dword store) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at node +8 | [V] |
| registration node +0x10 dispatch object | node +0x10 | 8 (qword store) | 0x18711c9 | `0x18711c9  mov [rdi+0x10],rdx` | node+0x10 = 0x150 resource-dispatch object (rdi=node via `0x18711c1  mov rdi,[rbp+0x28]`) | [V] |
| registry '*' 0x2A sentinel scan | registry dword array | 4 (dword cmp) | 0x1870e30 | `0x1870e30  cmp dword ptr [rcx],0x2A` | slot array scanned for '*' (0x2A) free sentinel (`0x1870e35  add rcx,4; 0x1870e3c  jne short 0x1870E30`) | [V] |
| registry slot cursor increment | registry scan | 1 (inc) | 0x1870f28 | `0x1870f28  inc r14d` | slot cursor r14d incremented, bounded by `0x1870f2b  cmp r14d,0x29` (slots 0..41) | [V] |
| registry slot index write | registry dword array | 4 (dword store) | 0x1870f40 | `0x1870f40  mov [r15],r14d` | resolved atlas slot index written to registry slot (index, not object pointer) | [V] |
| sub_1870de0 dispatch registration call | code sub_1870de0 | - | 0x18711b3 | `0x18711b3  mov [rbp+0x18],rsi` | sub_772520 generic refcounted field setter (`0x772542  mov [rcx],rax` vtable data_f08f110; `0x772554  mov rax,[r8+0x10]` add-ref; `0x7725d0  mov rax,[rbx+0x10]` release old) registers (name, idx) only — NO texture creation | [V] |
| sub_2fe440 conditional skip (not taken) | code 0x186f773/0x186f77d | - | 0x186f773 / 0x186f77d | `0x186f773  mov rdi,[rbp+0x530]` / `0x186f77d  je short 0x186F794` | scratch+0 zeroed by sub_1870de0 so rdi=0 and the `0x186f782  call 0x2FE440` site is skipped; only `0x186f78f  call 0xE935700` (edx=0x138, free(NULL)) follows — sub_2fe440 is cleanup, not a stitcher | [V] |
| ServerLevelLoad registration trigger | code 0x104237e | 5 (call rel32) | 0x104237e | `0x104237e  call 0x186E6A0` | sub_1042320 (ServerLevelLoad) calls sub_186e6a0 after `0x104239b  lea rax,[0xF602326]` ("ResourceLoadType::ServerLevelLoad") | [V] |
| initStep1 registration trigger | code 0x8f6919 | 5 (call rel32) | 0x8f6919 | `0x8f6919  call 0x186E6A0` | sub_8f6810 (initStep1) calls sub_186e6a0 after `0x8f685b  lea rcx,[0xF7DE3DB]` ("initStep1") | [V] |
| createTexture slot 26 -> TextureD3D12::create | code 0xe81455b | 5 (call rel32) | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture builds bimg params then calls TextureD3D12::create 0xe81bf30 via vtable slot 26; createTexture has 0 static callers | [V] |
| texture record +0xB0 actual format | desc +0xB0 | 1 (byte store) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte stored inside TextureD3D12::create; chosen via u16-per-format table `0xe81c022  movzx eax,word ptr [rax+r13*2+0x15AC]` | [V] |
| texture record +0xB1 numMips | desc +0xB1 | 1 (byte store) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips byte stored (dl loaded `0xe81c0cd  movzx edx,byte ptr [rbp+0x38]`); the ONLY numMips store located | [V] |
| uncompressed format fallback 0x42 | desc +0xB0 cmp | 1 (byte cmp) | 0xe81c12b | `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | actual format compared to 0x42 (uncompressed BGRA) fallback when caps lack the type | [V] |
| resizeTexture slot 31 entry | code 0xe815866 | 4 (mov r9d) | 0xe815866 | `0xe815866  mov edi,r9d` | resizeTexture(handle,w,h,mips,layers): r9d=mips->edi; 0 static xrefs; never observed live | [V] |
| sub_4e05e50 arg map (rdx->rsi) | code 0x4e05e6b | - | 0x4e05e6b | `0x4e05e6b  mov rsi,rdx` | sub_4e05e50 (TexturePtr ensure-loaded/upload): rsi=rdx=output; rdi=rcx=a0 object | [V] |
| sub_4e05e50 arg map (rcx->rdi) | code 0x4e05e6e | - | 0x4e05e6e | `0x4e05e6e  mov rdi,rcx` | rdi=a0 TexturePtr-like object (+0x10 pointee, +0x58 desc region) | [V] |
| sub_4e05e50 pointee add-ref | pointee +0x8 | 4 (dword cmpxchg) | 0x4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | add-ref CAS loop on refcount at *(a0+0x10)+8 | [V] |
| sub_4e05e50 16-byte object copy | entry obj +0x0 | 16 (movups) | 0x128944e | `0x128944e  movups xmm0,[r13]` | copies 16 bytes of the texture object; movups = 16-byte store | [V] |
| sub_4e05e50 pointee read | pointee +0x10 | 8 (qword load) | 0x4e05e8c | `0x4e05e8c  mov rdx,[rdi+0x10]` | reads the pointee texture object pointer | [V] |
| sub_4e05e50 upload bridge call | desc a0+0x58 | - | 0x4e05f77 | `0x4e05f77  call 0xBC41420` | sub_bc41420 dragon-layer upload bridge called with rcx=a0+0x58 description region — upload/ensure-loaded, NOT atlas creation | [V] |
| sub_4e05e50 live caller chain | live mc_root_4e05e50_callers.txt:3 | - | capture line 3 | `CALLER ret=0x1289496` — all 150 hits / 32 samples: sub_4e05e50 entered only from sub_12893d0; ret=0x1289496 = `0x1289496  nop` after `0x1289490  call qword ptr [0xF99FFA0]` | TexturePtr ensure-load/release consumer, not a creator; objects carry +0x00 = 0x7FF6A8215838 (cross-module) | [V live] |
| sub_12893d0 entry | sub header 0x12893d0 | - | sub_12893d0 | `0x12893d0..0x12895d3` size 0x203, 13 xrefs in | TexturePtr release/collect; walks a 0x18-strided entry array; the ONLY live caller of sub_4e05e50 (ret=0x1289496, all 32 samples) | [V] |
| sub_12893d0 release old pointee | entry obj +0x10 | 8 (qword) | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | release call through allocator thunk; fall-through `0x1289496  nop` = ret=0x1289496 seen for ALL 32 samples | [V live] |
| sub_12893d0 refcount dec strong | object +0x8 | 4 (dword) | 0x1289515 | `0x1289515  lock dec dword ptr [r15+8]` | decrements strong refcount; object destroyed at zero | [V] |
| sub_12893d0 refcount dec weak | object +0xC | 4 (dword) | 0x128958c | `0x128958c  lock dec dword ptr [rcx+0xC]` | second (weak) count decrement | [V] |
| sub_12893d0 array walk stride | array elem +0x18 | - | 0x1289560 | `0x1289560  add rbx,0x18` | walks a 0x18-strided array releasing [rbx+0x10] and [rbx+8] entries | [V] |
| texgroup_load lookup | code 0x5421dec | - | 0x5421dec | `0x5421dec  call 0x5477a30` | looks up a texture by name in the texture table (rcx=rsi+0x248); TexturePtr CONSUMER (lookup), not creator | [V] |
| texgroup_load add-ref | texture +0x8 | 4 (dword) | 0x5421e0a | `0x5421e0a  lock inc dword ptr [rcx+8]` | add-ref on the looked-up texture | [V] |
| texload rect walk | code 0x58a1430 | - | 0x58a1430 | `0x58a1430  add rdi,0x30` | walks a 0x30-strided rect list calling sub_5417950 per entry; atlas UV CONSUMPTION, not creation | [V] |
| texload rect float read | rect +0x8 | 4 (movss) | 0x58a1450 | `0x58a1450  movss xmm3,[rcx+8]` | per-rect float read in the rect walk; movss = 4-byte store | [V] |
| item parser atlas-name store | code 0x5755283 | - | 0x5755283 | `0x5755283  call 0x7F1A0` | item-definition parser stores atlas texture names ("atlas.items", "atlas.terrain", "textures/items/compass_atlas", compass/watch/lodestone_atlas) at item+0x78 — referenced as DATA only, never as createTexture arguments | [V] |
| sub_18718d0 resource get-or-load by name | code 0x18718fe | - | 0x18718fe | `0x18718fe  mov rcx,[rcx+0x30]` | walks a 0x10-strided entry array keyed by name; "TerrainAtlas"/"ItemAtlas" strings are referenced ONLY inside sub_186e6a0 [V via xref], so sub_18718d0 never receives them — not the atlas stitcher | [V] / [I] |
| BC1/BC3/BC7/DXT compression strings | str data (absent) | - | none | - | BC1/BC3/BC7/DXT1-DXT5 strings unreferenced (xref.py refs=[]); no compression path statically | [V] |
| texture table compression census | live texture_table.txt | - | capture header | DXGI_FORMAT u32 @+0x28 (28=R8G8B8A8_UNORM); 2950+ handles ALL uncompressed (28/11/61/26/10/41/44), ZERO BC formats, no atlas names | [V live] |
| live texture creation census | live l8b_texcreate_record.txt | - | capture line 3 | `CALLER ret=0xE814560` — 24 TextureD3D12::create samples all format 0x1C uncompressed, numMips=1, names "Texture: 2815"/"Texture: 2799"/"tex", ZERO atlas names, ZERO compressed formats | [V live] |
| bgfx producer texture descriptions | live bgfx_createtexture_producer.txt | - | capture | rva=0xBC73770 (ret=0xBC73EAD): RDX/R8 desc objects carry "TEXC" tag, format 0x1C, texture PATH names ("textures/entity/...", "vanilla.CoreData", UUIDs, "ApplyGradientWith"), cross-module vtable ptrs desc+0x20/+0x28 (0x7FF6A8441980/90) — NO atlas names | [V live] |
| bgfx producer chain entry | live dragon_texture_entry_c296b50.txt | - | capture line 3 | rva=0xC296B50, `CALLER ret=0xBC41B3E`: format 0x1C, numMips=1 | [V live] |
| dragon upload bridge caller | live dragon_texture_caller_bc41420.txt | - | capture line 3 | rva=0xBC41420, `CALLER ret=0x4E05F7C` (return into sub_4e05e50): RCX desc objects format 0x1C, "tex", 240x60, numMips=1 — upload, not creation | [V live] |
| cross-module pointer at obj +0x00 | obj +0x00 | 8 (qword) | mc_root_4e05e50_callers.txt:4 | RCX hit=1 bytes `385821A8F67F0000` = 0x00007FF6A8215838 at object +0x00 — pointer into ANOTHER MODULE (outside exe image); stable across all 32 samples; module never identified | [V live] |
| mip generation function | not located | none | - | - | NOT located: xref str GenMip/Mips/MipMap/mipchain → refs=[] (no functions) [V via xref]; numMips only stored at +0xB1 `0xe81c0d1  mov [rdi+0xB1],dl` [V]; all live creations numMips=1 [V live] | [?] |
| atlas texture-creation stitcher | not located | none | - | - | NOT located: no code builds the TerrainAtlas/ItemAtlas texture description or calls createTexture/resizeTexture with atlas parameters; registration objects discarded after sub_186e6a0 | [?] |

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas TEXTURE-CREATION STITCHER is not located in this exe — no code builds the TerrainAtlas (idx 6) / ItemAtlas (idx 7) texture description and calls createTexture (slot 26, `0xe81455b  call 0xE81BF30` → TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, `0xe815866  mov edi,r9d`, takes mips) with atlas parameters:

- Registration IS proven [V]: both names exist in the exe ("TerrainAtlas" `0x186f731  lea rax,[0xF55CDD3]` idx 6; "ItemAtlas" `0x186f7fc  lea rax,[0xF55CDE0]` idx 7) inside sub_186e6a0 via sub_1870de0 (0x48-byte node; registry '*' sentinel scan `0x1870e30  cmp dword ptr [rcx],0x2A`, bound `0x1870f28  inc r14d` / `0x1870f2b  cmp r14d,0x29`), triggered by ServerLevelLoad `0x104237e  call 0x186E6A0` and initStep1 `0x8f6919  call 0x186E6A0`. BUT sub_186e6a0 contains no createTexture/resizeTexture call [V]; post-registration the objects are discarded (sub_2fe440 call skipped `0x186f77d  je short 0x186F794`; `0x186f78f  call 0xE935700` frees NULL) and xref shows the atlas names referenced ONLY inside sub_186e6a0 [V].
- Creation entry points fully enumerated and NEGATIVE [V + V live]: createTexture census (l8b_texcreate_record + createtexture_callers — all format 0x1C uncompressed, numMips=1, UI/screen texture names, ZERO atlas names [V live]); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture slot 31 has 0 static xrefs and never observed live [V]; sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release (live caller chain ret=0x1289496 = `0x1289496  nop` after `0x1289490  call qword ptr [0xF99FFA0]` [V live]); upload path to sub_bc41420 confirmed (desc format 0x1C "tex" [V live]); sub_5477a30 lookup callers = texgroup_load + sub_541f8f0 only, no stitcher [V via xref]; resource-by-name lookup sub_18718d0 never receives the atlas names [V]/[I]; sub_186dac0 async enqueue is not texture creation [V].
- Cross-module pointer: objects passed to sub_4e05e50 carry +0x00 = 0x00007FF6A8215838 [V live docs/data/live/mc_root_4e05e50_callers.txt line 4], outside the exe image (base 0x7ff7a59c0000, end 0x7ff7bd2fe000) → ANOTHER MODULE; livemem read/vt of that address unproductive (readlog lines 125/144-145/164-168/212), now unreadable [V live carried]. Atlas creation logic is external to this exe (another module / data-driven / bgfx command-stream driven) — not closable from static analysis of this exe alone (orchestrator hint 2026-11-22: static analysis alone is exhausted for this item).
- New angle this session (producer chain forward + texture table): the L8a producer chain (0xBC73770 → 0xC296B50 → 0xBC73BF0 → 0xe8143c0) creates only ordinary uncompressed format-0x1C numMips=1 textures with PATH names, never atlases [V live]; texture_table.txt shows 2950+ handles ALL uncompressed, ZERO BC formats [V live]. No stitcher located.

Resolved as provably-ABSENT (negatives, NOT the blocker): mipmap generation (no GenMip/Mips/MipMap/mipMap code or task [V via xref]; numMips only stored at +0xB1 [V]; all live creations numMips=1 [V live]) and BC1/BC3/BC7/DXT1-DXT5 compression (all those strings unreferenced [V via xref]; texture table all uncompressed [V live]; create path uncompressed `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` / `0xe81c077  mov [rdi+0xB0],r13b` [V]).

Decision: park as MIRROR_SKIP / external (another module or data-driven); re-open only if a live capture (e.g. l8b_resizetex_slot31 pending, or a capture at createTexture/TextureD3D12::create entry 0xe81bf30) returns a stitcher caller with mips>1 or atlas-name arguments, or if the module at 0x00007FF6A8215838 is identified and found to contain atlas creation.

## WHAT I TRIED THAT FAILED (this session; do not redo)

- Forward stitcher from registration objects: full static decode of sub_1870de0 (node layout, sub_772520 refcounted setter, registry sentinel scan) — NO createTexture/resizeTexture anywhere in sub_186e6a0/sub_1870de0/sub_772520 [V]. sub_2fe440 call skipped (scratch+0=0); sub_2fe440 is cleanup-only [V].
- docs/progress/pre/ bundles (0x18718d0, 0x18718d0_callers, 0x55f1450, 0x157fe0_part2-5, 0x1048c80, 0x1020e09_ctx) — none contains a stitcher [V].
- xref str "TerrainAtlas" → refs only inside sub_186e6a0 [V]; xref str "ItemAtlas" → refs only inside sub_186e6a0 [V]; xref str "Mip" → mip-key strings only, no generator [V]; xref str BC1/BC3/BC7/DXT → refs=[] [V].
- Backward chain from createTexture: exhausted — 0 static callers; all live callers ret=command interpreter / bc41420 upload bridge; no atlas names [V live].
- Cross-module pointer 0x7FF6A8215838 module identification: livemem read/vt attempted multiple times (readlog) but unproductive / now unreadable [V live carried].

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — ALREADY QUEUED (rva 0xe815840 = resizeTexture slot 31, size 0x100, max 6, why: "L8b: does the atlas stitcher create/resize atlases via resizeTexture(handle,w,h,mips,layers); ret= names the stitcher caller; mips>1 is mip-generation evidence"). Result NOT yet in docs/data/live/ (_status.txt DONE list lacks it). Queue full at 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) — cannot re-queue this unit. Check `python tools/livecap/request.py result l8b_resizetex_slot31` next unit; if it returns no atlas/mips>1 evidence, close with CLOSES? NO (external/data-driven).
Helper scripts: none (all verbatim lines taken directly from rdis dis output and live capture files; no throwaway scripts written; nothing left in temp).
