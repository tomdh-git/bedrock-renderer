## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — answer table (name | offset | size | read/store addr | verbatim `0xRVA  instr` | meaning | tag) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched; no game process touched by me. Read-only live captures under docs/data/live/*.txt were produced by the orchestrator; I only read them on disk.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted, re-confirmed with rdis.exe this session); [V live] read-only live capture (cite file + line); [I] inferred (say from what); [?] unknown / not located.
Row rule: one annotated row per distinct offset; offset | size | read/store addr | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No skipped offsets, no catch-all rows, no raw listing dumps.

## State carried from oc_U-EL8b_r1..r69 (proven, NOT re-derived; key instructions re-verified with rdis.exe this session)

- Atlas registration PROVEN [V]: sub_186e6a0 loads "TerrainAtlas" (`0x186f731  lea rax,[0xF55CDD3]`, len 0xC at `0x186f73f  mov qword ptr [rbp+0x108],0xC`) idx 6 (`0x186f767  mov r9d,6` → `0x186f76d  call 0x1870DE0`) and "ItemAtlas" (`0x186f7fc  lea rax,[0xF55CDE0]`, len 9 at `0x186f80a  mov qword ptr [rbp+0x118],9`) idx 7 (`0x186f838  call 0x1870DE0`) via sub_1870de0: 0x48-byte node (`0x1870e70  mov edx,0x48`, `0x1870e75  call qword ptr [0xF99FFA0]`), name at node+0 (`0x1870ec5  mov [rsi],rax`), idx at node+8 (`0x1870ecb  mov [rsi+8],eax`), dispatch object at node+0x10; registry '*' (0x2A) sentinel scan (`0x1870e30  cmp dword ptr [rcx],0x2A`), resolved slot index written (`0x1870f40  mov [r15],r14d`). Triggered by ServerLevelLoad `0x104237e  call 0x186E6A0` and initStep1 `0x8f6919  call 0x186E6A0`. sub_186e6a0 contains NO createTexture/resizeTexture [V]; post-registration objects are discarded (cleanup call skipped, then `call 0xE935700` frees NULL); atlas names referenced ONLY inside sub_186e6a0 [V via xref]. After registration ServerLevelLoad registers non-atlas entries only (idx 0x28; idx 0x29 with sentinel 0x2A) [V]. Item-atlas NAME exists in the exe but only as registration data [V]; item parser stores atlas texture NAMES ("atlas.items", "atlas.terrain", "textures/items/compass_atlas", compass/watch/lodestone_atlas) as DATA only at item+0x78 (`0x575527d  lea edx,[0xF550917]` → `0x5755283  call 0x7F1A0`) [V].
- Blit side uncompressed [V]: "TerrainAtlasBlit" task `0xbb431ee  lea rdx,[0xF539A0B]`; "BlitUncompressed" `0x560be9f  lea r9,[0xF5F440C]`.
- Mip generation NOT located [?]: xref GenMip/Mips/MipMap/mipchain → refs=[] [V via xref]; only numMips store `0xe81c0d1  mov [rdi+0xB1],dl` [V]; all live creations numMips=1 [V live].
- BC1/BC3/BC7/DXT compression NOT located [V]: all those strings xref.py refs=[] [V via xref]; create path uncompressed `0xe81c077  mov [rdi+0xB0],r13b` with fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` [V]; live census all format 0x1C uncompressed [V live].
- Negative angles [V]: sub_e82e00→sub_e84070 "DefaultFont" (`0xe830bc  lea rdx,[0xF0BC570]` → `0xe830ce  call 0xE84070`) = default-font descriptor setter, not the atlas stitcher; sub_18718d0 name-lookup never receives atlas names (`0x18718fe  mov rcx,[rcx+0x30]`); sub_4e05e50/sub_12893d0 = TexturePtr ensure-loaded/release consumer (`0x4e05f77  call 0xBC41420` upload bridge; indirect caller `0x1289490  call qword ptr [0xF99FFA0]`, ret=0x1289496 = `0x1289496  nop` [V live]); texgroup_load/texload = consumers via sub_5477a30 (callers sub_541f8f0 + texgroup_load only, no stitcher) [V].
- Cross-module lead PROVEN DEAD [V live]: obj +0x00 = 0x00007FF6A8215838 at sub_4e05e50 entry; livemem read unreadable; read-only Toolhelp32 of pid 13452: no loaded module contains 0x7FF6A8215838 [V live mc_root_4e05e50_callers.txt line 4].

## Live data re-read this session (no new results available)

- docs/data/live/l8b_texcreate_record.txt (entry 0xE81BF30 TextureD3D12::create): `CALLER ret=0xE814560` first_hit=1 — 24 samples, all format 0x1C uncompressed, numMips=1, names "Texture: 2815"/"Texture: 2799"/"tex", ZERO atlas names, ZERO compressed [V live line 3].
- docs/data/live/mc_root_4e05e50_callers.txt (entry 0x4e05e50): `CALLER ret=0x1289496` first_hit=1 — 32 samples; ret=0x1289496 = `0x1289496  nop` after `0x1289490  call qword ptr [0xF99FFA0]` (indirect caller of sub_4e05e50); RCX desc dumps uncompressed single-mip (0x1C at +0x60, "tex\0" fourcc at +0x70); cross-module pointer 0x7FF6A8215838 dead [V live line 4].
- docs/data/live/createtexture_callers.txt (entry 0xE8143C0 createTexture): `CALLER ret=0xBC6A2C8` first_hit=1 — 25 hits, EVERY createTexture entry returns to 0xBC6A2C8 inside bgfx executor sub_bc6a290 (`0xBC6A2C2  call qword ptr [0xF99FFA0]` / `0xBC6A2C8  test rax,rax`); R8 packets format 0x1C, sizes 128x128/64x64, UI/content names, ZERO atlas names, ZERO mips>1, ZERO compressed [V live line 3].
- Queue: `python tools/livecap/request.py result l8b_resizetex_slot31` → "no result yet (orchestrator has not run it)"; 4 pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) → `add` exits "4 requests already pending, ask again next unit". No new capture requested by this unit. No new livemem reads (brief allows reads only after an unsettled rdis finding; cross-module lead is dead).

## ANSWER TABLE (one row per distinct offset)

| name | offset | size | read/store addr | verbatim `0xRVA  instr` | meaning shown by instruction or string | tag |
|---|---|---|---|---|---|---|
| TerrainAtlas name load | str data 0xF55CDD3 | 8 (lea qword) | 0x186f731 | `0x186f731  lea rax,[0xF55CDD3]` | "TerrainAtlas" ([data_f55cdd3]) loaded, len 0xC at `0x186f73f  mov qword ptr [rbp+0x108],0xC`, idx 6 at `0x186f767  mov r9d,6` → `0x186f76d  call 0x1870DE0` inside sub_186e6a0 | [V] |
| ItemAtlas name load | str data 0xF55CDE0 | 8 (lea qword) | 0x186f7fc | `0x186f7fc  lea rax,[0xF55CDE0]` | "ItemAtlas" ([data_f55cde0]) loaded — item-atlas NAME exists in the exe; len 9 at `0x186f80a  mov qword ptr [rbp+0x118],9`, idx 7 → `0x186f838  call 0x1870DE0` | [V] |
| registration node alloc size | code 0x1870e70 | 4 (dword imm) | 0x1870e70 | `0x1870e70  mov edx,0x48` | sub_1870de0 allocates a 0x48-byte registration node via `0x1870e75  call qword ptr [0xF99FFA0]` | [V] |
| name stored at node +0 | node +0x0 | 8 (qword store) | 0x1870ec5 | `0x1870ec5  mov [rsi],rax` | name pointer stored at registered node +0 inside sub_1870de0 | [V] |
| index stored at node +8 | node +0x8 | 4 (dword store) | 0x1870ecb | `0x1870ecb  mov [rsi+8],eax` | index (r9d = 6 TerrainAtlas / 7 ItemAtlas) stored at node +8 | [V] |
| registry slot index write | registry slot [r15] | 4 (dword store) | 0x1870f40 | `0x1870f40  mov [r15],r14d` | resolved atlas slot index written to registry slot (an index, not an object pointer) | [V] |
| ServerLevelLoad registration trigger | code 0x104237e | 5 (call rel32) | 0x104237e | `0x104237e  call 0x186E6A0` | sub_1042320 (ServerLevelLoad) calls sub_186e6a0 (registers both atlases); no createTexture/resizeTexture with atlas parameters follows | [V] |
| createTexture slot 26 → TextureD3D12::create | code 0xe81455b | 5 (call rel32) | 0xe81455b | `0xe81455b  call 0xE81BF30` | createTexture (entry `0xe8143c0  push rbp`, 0 static xrefs) builds bimg params then calls TextureD3D12::create 0xe81bf30 | [V] |
| texture desc +0xB0 actual format | desc +0xB0 | 1 (byte store) | 0xe81c077 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format byte stored inside TextureD3D12::create; uncompressed fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` | [V] |
| texture desc +0xB1 numMips | desc +0xB1 | 1 (byte store) | 0xe81c0d1 | `0xe81c0d1  mov [rdi+0xB1],dl` | the ONLY numMips store located | [V] |
| resizeTexture slot-31 entry | code 0xe815840 | 1 (push) | 0xe815840 | `0xe815840  push rbp` | resizeTexture slot 31 entry (takes handle,w,h,mips,layers); 0 static xrefs; never observed live | [V] |
| live createTexture census | call site 0xBC6A2C2 | 6 (call [imm64]) | 0xBC6A2C2 | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | every createTexture entry returns to 0xBC6A2C8 (`0xBC6A2C8  test rax,rax`) in bgfx executor sub_bc6a290; 25 hits, format 0x1C, sizes 128x128/64x64, UI/content names, ZERO atlas names, ZERO mips>1 [V live createtexture_callers.txt line 3] | [V live] |
| live TextureD3D12::create census | entry 0xE81BF30 | 1 (push) | 0xE81BF30 | `0xE81BF30  push rbp` | 24 samples, ret=0xE814560 (inside createTexture), all format 0x1C uncompressed, numMips=1, names Texture:2815/2799/tex, ZERO atlas names, ZERO compressed [V live l8b_texcreate_record.txt line 3] | [V live] |
| atlas texture-creation stitcher | not located (stitcher) | none | - | - | no code builds idx 6 / idx 7 atlas texture description and calls createTexture (slot 26) or resizeTexture (slot 31, takes mips) with atlas parameters | [?] |
| mip generation function | not located (mipgen) | none | - | - | GenMip/Mips/MipMap/mipchain xref refs=[] [V via xref]; numMips only at +0xB1; all live numMips=1 | [?] |
| BC1/BC3/BC7/DXT compression | strings data 0xF84AD1C/0xF84AAF8/0xF84A930 | - | none | - | all those strings xref.py refs=[] (no code references them); create path uncompressed only | [V] |

## CLOSES?

CLOSES? NO. Single blocking fact: the atlas TEXTURE-CREATION STITCHER is not located — no code in this exe builds the TerrainAtlas (idx 6) / ItemAtlas (idx 7) texture description and calls createTexture (slot 26, `0xe81455b  call 0xE81BF30` → TextureD3D12::create 0xe81bf30) or resizeTexture (slot 31, `0xe815840  push rbp`, takes mips) with atlas parameters:

- Registration IS proven [V] (both names exist in the exe, idx 6/7, name at node+0, idx at node+8, triggered by ServerLevelLoad `0x104237e  call 0x186E6A0` and initStep1 `0x8f6919  call 0x186E6A0`), but sub_186e6a0 contains no createTexture/resizeTexture [V], post-registration objects are discarded, xref shows the atlas names referenced ONLY inside sub_186e6a0 [V via xref], and ServerLevelLoad registers non-atlas entries only after registration [V].
- Creation entry points fully enumerated and NEGATIVE [V + V live]: createTexture census (all 25 hits return to the bgfx executor `0xBC6A2C2  call qword ptr [0xF99FFA0]` / `0xBC6A2C8  test rax,rax`; format 0x1C, numMips=1, zero atlas names [V live]); TextureD3D12::create callers = createTexture + resizeTexture only [V via xref]; resizeTexture slot 31 has 0 static xrefs and was never observed live [V]; sub_4e05e50/sub_12893d0 = TexturePtr consumer (`0x4e05f77  call 0xBC41420` upload bridge; indirect caller `0x1289490  call qword ptr [0xF99FFA0]`, ret=0x1289496 = `0x1289496  nop`, all 32 samples [V live]); texgroup_load/texload = consumers via sub_5477a30 only [V]; sub_18718d0 never receives the atlas names [V]/[I]; sub_e84070/e82e00 = default-font setter `0xe830bc  lea rdx,[0xF0BC570]` → `0xe830ce  call 0xE84070` [V]; blit path uncompressed (`0x560be9f  lea r9,[0xF5F440C]`, `0xbb431ee  lea rdx,[0xF539A0B]`) [V]; item parser atlas names are DATA only at item+0x78 (`0x575527d  lea edx,[0xF550917]` → `0x5755283  call 0x7F1A0`) [V].
- Live creation funnel [V live]: ALL observed texture creations are format 0x1C uncompressed with numMips=1 and zero atlas names (l8b_texcreate_record.txt 24 samples [V live line 3]; createtexture_callers.txt 25 hits [V live line 3]). Atlas textures are never created in any observed path.
- Mip generation and BC1/BC3/BC7/DXT compression are provably ABSENT [V via xref + V live] (see table rows above) — negatives, not the blocker.
- Cross-module lead PROVEN DEAD [V live] (0x7FF6A8215838 unreadable, no containing module). Static analysis exhausted per orchestrator hint 2026-11-22. Remaining live capture l8b_resizetex_slot31 (entry 0xe815840 resizeTexture slot 31) is pending, queue full (4 pending) → this unit cannot re-queue. Item stays CLOSES? NO (external/data-driven or pending capture) until that capture returns atlas creation or mips>1 evidence.

## WHAT I TRIED THAT FAILED (this session — do not redo)

- Checked `python tools/livecap/request.py result l8b_resizetex_slot31` → "no result yet (orchestrator has not run it)"; queue FULL at 4 pending → `add` exits "4 requests already pending, ask again next unit". No new capture requested.
- Re-read docs/data/live/l8b_texcreate_record.txt and docs/data/live/mc_root_4e05e50_callers.txt in full; both already decoded in r68/r69: no atlas names, no mips>1, no compressed formats in any sample. No new evidence to add.
- No new static angles: forward from sub_186e6a0/sub_1870de0, backward from createTexture, sub_e84070/e82e00, sub_18718d0 — all negative in r1..r69; static analysis exhausted per orchestrator hint 2026-11-22.
- No new livemem reads: cross-module pointer lead already dead.

## TOOL REQUESTS

CAPTURE REQUESTED l8b_resizetex_slot31 — already queued by prior units: entry rva 0xe815840 (resizeTexture slot 31), size 0x100, max 6, why: "L8b: does the atlas stitcher create/resize atlases via resizeTexture(handle,w,h,mips,layers); ret= names the stitcher caller; mips>1 is mip-generation evidence". State: pending, NO result yet (`python tools/livecap/request.py result l8b_resizetex_slot31` → "no result yet (orchestrator has not run it)"). Queue full at 4 pending — this unit cannot re-queue. If it returns atlas creation or mips>1 evidence the item can close; otherwise it stays CLOSES? NO (external/data-driven, not closable from static analysis of this exe).
Live reads done this session: none (cross-module lead already dead). Instructions verified with rdis.exe dis this session: every `0xRVA  instr` line quoted above.
Helper scripts: none.
