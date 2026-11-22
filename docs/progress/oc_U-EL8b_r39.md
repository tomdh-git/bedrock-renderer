## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression — RETRY #4

Goal: close checklist item "L8b Atlases (terrain, items), mipmaps and compression pending" (docs/RENDER_CHECKLIST.md:345).
Static analysis only (OPENCODE_BRIEF.md rule 1); exe = Minecraft.Windows.exe 1.26.62.01; RVAs relative to image base. No tools.rtools.*; no game interaction.
Tags: [V] = verbatim instruction line seen in a fresh rdis dump of the exe (cite RVA); [V live] = docs/data/live capture file + line; [I] = inferred (say from what); [?] = unknown.
Carried proven facts from oc_U-EL8b_r1..r38 are NOT re-derived; key instruction lines were re-dumped this unit and match verbatim (see table). One carried line was wrong and is corrected here: `0x1870f0e` is `mov [rbx+8],r15` (a local string object), not `mov [rbx+0x10],rax` into the node.

## Scope carried (proven earlier, not re-redone)

- Atlas registration: sub_186f720 passes name+len+idx to sub_1870DE0: TerrainAtlas string 0xF55CDD3 len 0xC idx 6 (`0x186f731 lea rax,[0xF55CDD3]`, `0x186f73f mov qword ptr [rbp+0x108],0xC`, `0x186f767 mov r9d,6`, `0x186f76d call 0x1870DE0`); ItemAtlas string 0xF55CDE0 len 9 idx 7 (`0x186f7fc lea rax,[0xF55CDE0]`, `0x186f80a mov qword ptr [rbp+0x118],9`, `0x186f832 mov r9d,7`, `0x186f838 call 0x1870DE0`); AnimatedAtlas string 0xF55CE42 idx 8 also registered (`0x186f8c7 lea rax,[0xF55CE42]`, `0x186f8fd mov r9d,8`) [V]. Triggered from ServerLevelLoad sub_1042320 (call at 0x104237e) and initStep1 sub_8f6810 (call at 0x8f6919) [V carried].
- Registry slot scan: `0x1870e30 cmp dword ptr [rcx],0x2A` ('*' sentinel), `0x1870e4c cmp r14d,0x29` (slots 0..41) [V]. Node allocated 0x48 bytes (`0x1870e70 mov edx,0x48`, `0x1870e75 call qword ptr [0xF99FFA0]` -> sub_eea6040 per disassembly annotation [I]) [V].
- TextureD3D12::create entry 0xe81bf30 via createTexture wrapper slot 26: exactly one static caller `0xe81455b call 0xE81BF30` (next instr `0xe814560 nop`, observed live as ret=0xe814560 [V]). Desc fields: +0xB0 format byte (`0xe81c077 mov [rdi+0xB0],r13b`), +0xB1 numMips byte (`0xe81c0d1 mov [rdi+0xB1],dl`) [V]; numMips only store located [V].
- resizeTexture slot 31 at 0xe815840 (`0xe815840 push rbp`, `0xe815866 mov edi,r9d` -> r9d = mips param): 0 static xrefs, never observed live [V].
- Negative: BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V]; no compression path in the exe (only PNG/zlib decompression) [V]; mip generation absent [V] (material mip keys are load-time params; glGenerateMipmap@0xe92c2c0 GLES glue only); no static path from registration nodes to createTexture/resizeTexture [V carried].
- Live texture census l8b_texcreate_record.txt (entry 0xe81bf30, caller ret=0xe814560): 24 samples, ALL format 0x1C uncompressed with numMips=1, names "tex" / "Texture: 2815" / "Texture: 2799"; zero atlas names, zero compressed formats [V live lines 4-27].

## New work this unit — decode of sub_12893d0 (the indirect caller of sub_4e05e50)

The live capture mc_root_4e05e50_callers.txt names the indirect caller of sub_4e05e50: `CALLER ret=0x1289496 first_hit=1` (line 3), and ret=0x1289496 is `0x1289496 nop`, the instruction immediately after `0x1289490 call qword ptr [0xF99FFA0]` inside sub_12893d0 — so at runtime [0xF99FFA0] at that call site = sub_4e05e50 [V live].

Earlier notes called it sub_1289440, but 0x1289440 is only a loop label; the real function entry is sub_12893d0 [0x12893d0..], 0 static xrefs (invoked indirectly) [V].

sub_12893d0 decode [0x12893d0..0x12895d2], phases:
- Prologue 0x12893d0..0x1289414: rcx=a0 is an object holding a pointer range; `0x1289406 mov r13,[rcx]` = begin, `0x1289409 mov r14,[rcx+8]` = end; r12d=0 counter; rbx = &[rbp-0x20] out cursor; `0x1289414 jmp short 0x1289424` into the loop test [V].
- Loop head 0x1289424: `cmp r13,r14; je 0x128954f` (done). Per element rcx=`0x1289431 mov rcx,[r13+8]`; null -> next element (`0x1289420 add r13,0x18`) [V]. eax=`0x128943a mov eax,[rcx+8]` = object refcount; if eax==0 skip (`0x1289470`), else spin add-ref: `0x1289440 test eax,eax`; `0x1289444 lea edx,[rax+1]`; `0x1289447 lock cmpxchg [rcx+8],edx`; `0x128944c jne short 0x1289440` (retry until [rcx+8]==eax or the count dropped to 0) [V].
- Element copy + consume: 16-byte element copy (`movups xmm0,[r13]` at 0x128944e, `movaps [rbp-0x50],xmm0` at 0x1289457); `0x1289453 mov rax,[r13]`; `test rax,rax; jne short 0x128947d` [V]. At 0x128947d: rcx=`0x128947d mov rcx,[r13+0x10]` (the entry's +0x10 pointee); null -> `0x1289505 inc r12`; else virtual call rax=[rcx]; rax=`0x1289489 mov rax,[rax+8]` (vtable slot 1); rdx=rbx; `0x1289490 call qword ptr [0xF99FFA0]` -> live identity = sub_4e05e50 (`0x1289496 nop` is the ret=0x1289496 from the capture) [V live]. Then consume: [r13+0x10] = 0 via `0x128949b mov qword ptr [r13+0x10],0`; if the old pointee was non-null: rax=[rcx]; rax=`0x12894ab mov rax,[rax]` (vtable slot 0 = release); edx=1; `0x12894b3 call qword ptr [0xF99FFA0]` -> release old pointee [V].
- Tail 0x1289508: r15=[rbp-0x48]; if set: `0x1289515 lock dec dword ptr [r15+8]`; when it hits zero: rax=[r15]; rax=`0x128953d mov rax,[rax+8]` (vtable slot 1); `0x1289544 call qword ptr [0xF99FFA0]` (final release); `0x128952f lock dec dword ptr [r15+0xC]` (second refcount) [V].
- Array-release tail 0x128954f: walk entries step 0x18 (`0x1289560 add rbx,0x18`); per entry `0x1289569 mov rcx,[rbx+0x10]` (release via slot 0 at 0x128957d) or `0x1289583 mov rcx,[rbx+8]` then `0x128958c lock dec dword ptr [rcx+0xC]` and slot-1 release at 0x1289599 [V].
- Exit 0x12895a8: `mov [rsi],r12` (count), ret; returns rsi [V].

Conclusion: sub_12893d0 is a TexturePtr-style texture-ref array consumer (add-ref new, call upload bridge sub_4e05e50 on each entry's +0x10 pointee, release old pointees + container refcounts +0x8/+0xC). It consumes textures; it creates nothing. NOT the atlas stitcher [V]. Object at runtime: RCX heap objects (e.g. 0x3908FFDE900) whose [+0x00] = 0x00007FF6A8215838, a pointer outside the exe image (0x7ff7a59c0000..0x7ff7bd2fe000) — cross-module object [V live mc_root_4e05e50_callers.txt:4].

### Connection to texgroup_load 0x5421c90 / texload 0x58a1310 — not established

texgroup_load sub_5421c90: takes a desc-like arg (r8), reads [r8+0] count, [r8+0x18], builds a name string with SSO cap 0xF at [rbp+0x1C8], allocates via [0xF99FFA0] when name > 0xFFF [V]. texload sub_58a1310: reads [a0+0xF0]/[a0+0xE8] (loaded/total), flags [rsi+0x254]/[rsi+0x1B4], sets [rsi+0x1B0]=0xFFFFFFFF, [rsi+0x159]=1, iterates [rbx+0x160, rbx+0x168) [V]. There are 0 static xrefs between sub_12893d0 and either function, and sub_12893d0 itself has 0 static xrefs (called via indirection) [V]. The runtime caller chain of sub_12893d0 is still unknown; capture sub_1289440_callers (rva 0x1289440, state pending in docs/progress/capture_requests.json) will name its callers via ret= when the orchestrator runs it [?].

### BGFX_MAP.md atlas sections — tangential only

Grepped "atlas": `PointLightShadowTextureAtlas` at 0xbb682b0 (shadow atlas, not terrain/item) [I]; `MaterialTerrainTextureAtlas` string only, referenced via table [I]; `TerrainAtlasBlit` is a render-frame task (0xF43E9C0, functor vtable 0xF43E9E0) that USES an atlas, does not create one [I]. No stitcher, no BC1/BC3/BC7 creation path, no mip generation documented there [I].

## Node layout verified this unit (sub_1870de0, rdi = node = [rbp+0x28], the 0x48-byte allocation)

- +0x00: `0x1870ec5 mov [rsi],rax` — node+0 = dispatch object taken from registry head; source nulled by `0x1870e8b mov qword ptr [rcx+0x10],0` / `0x1870ebe mov qword ptr [rcx],0` [V]
- +0x08: `0x1870ecb mov [rsi+8],eax` — node+8 = atlas idx from caller r9d (6 TerrainAtlas / 7 ItemAtlas / 8 AnimatedAtlas) [V]
- +0x10: `0x18711c9 mov [rdi+0x10],rdx` — node+0x10 = name buffer pointer (atlas name string) [V]
- +0x18: `0x1871271 mov [rdi+0x18],r15` — node+0x18 = name length (zeroed first via `movups [rdi+0x18],xmm0` at 0x18711d0) [V]

## ANSWER TABLE — one row per distinct offset; all instruction sites listed; sizes from the instruction; verbatim lines from fresh rdis dumps of the exe

| name | offset | size | site(s) (read/store address) | verbatim `0xRVA  instr` | meaning shown by instruction or string | tag |
|---|---|---|---|---|---|---|
| Atlas node +0x0 dispatch object (taken) | node+0x0 | 8B | [rsi] (node init, sub_1870DE0) | `0x1870ec5  mov [rsi],rax` | node+0 = dispatch object taken from registry head; source nulled by `0x1870e93  mov qword ptr [rcx+0x10],0` and `0x1870ebe  mov qword ptr [rcx],0` | [V] |
| Atlas node +0x8 idx | node+0x8 | 4B | [rsi+8] (node init) | `0x1870ecb  mov [rsi+8],eax` | node+8 = atlas idx from caller r9d: TerrainAtlas 6 (`0x186f767  mov r9d,6`, `0x186f76d  call 0x1870DE0`; string `0x186f731  lea rax,[0xF55CDD3]` "TerrainAtlas", len `0x186f73f  mov qword ptr [rbp+0x108],0xC`); ItemAtlas 7 (`0x186f832  mov r9d,7`, `0x186f838  call 0x1870DE0`; string `0x186f7fc  lea rax,[0xF55CDE0]` len 9); AnimatedAtlas 8 also registered (`0x186f8c7  lea rax,[0xF55CE42]`, `0x186f8fd  mov r9d,8`) | [V] |
| Atlas node +0x10 name pointer | node+0x10 | 8B | [rdi+0x10] (node init) | `0x18711c9  mov [rdi+0x10],rdx` | node+0x10 = name buffer pointer holding the atlas name string (rdx = [rbp+0x18] = the 0x150-byte name buffer built by sub_1870de0) | [V] |
| Atlas node +0x18 name length | node+0x18 | 8B | [rdi+0x18] (node init) | `0x1871271  mov [rdi+0x18],r15` | node+0x18 = name length (r15); the field is zeroed first by `movups [rdi+0x18],xmm0` at 0x18711d0 (prose only — movups not quoted in table rows) | [V] |
| Registry '*' sentinel + slot bound | reg+0 | 4B | [rcx] (registry scan) | `0x1870e30  cmp dword ptr [rcx],0x2A` ; `0x1870e4c  cmp r14d,0x29` | registry slot terminator is '*' (0x2A); slots scanned 0..41 (0x29) | [V] |
| MC_obj +0x18 release target | MC_obj+0x18 | 8B | [rcx+0x18] (sub_4e05e50) | `0x4e05e71  mov rax,[rcx+0x18]` | MC_obj+0x18 object released with MC_obj+0x58 as argument via `0x4e05e86  call qword ptr [0xF99FFA0]` | [V] |
| MC_obj +0x58 dragon_obj | MC_obj+0x58 | 8B | lea/add address math, no memory read inside sub_4e05e50 | `0x4e05e7e  lea rdx,[rdi+0x58]` ; `0x4e05f68  add rdi,0x58` | dragon_obj = MC_obj+0x58, passed as rcx to upload bridge `0x4e05f77  call 0xBC41420`; chain per L8a/L7e: sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (cmd-byte-14) -> dispatcher slot-26 -> TextureD3D12::create 0xe81bf30 [V carried] | [V] |
| MC_obj +0xE0 upload arg | MC_obj+0xE0 | 8B | [rdi+0xE0] (sub_4e05e50) | `0x4e05f61  mov r9,[rdi+0xE0]` | MC_obj+0xE0 passed as 4th arg (r9) to sub_bc41420 | [V] |
| Texture desc +0xB0 format byte | 0xB0 | 1B | [rdi+0xB0] (TextureD3D12::create 0xe81bf30) | `0xe81c077  mov [rdi+0xB0],r13b` | desc+0xB0 = format byte; all 24 live creations format 0x1C uncompressed, names "tex"/"Texture: ####", no atlas names [V live docs/data/live/l8b_texcreate_record.txt:4-27] | [V] |
| Texture desc +0xB1 numMips byte | 0xB1 | 1B | [rdi+0xB1] (TextureD3D12::create 0xe81bf30) | `0xe81c0d1  mov [rdi+0xB1],dl` | desc+0xB1 = numMips byte; live numMips=1 [V live docs/data/live/l8b_texcreate_record.txt:4-27]; numMips>1 would be mip-generation evidence | [V] |
| Indirect-call data slot [0xF99FFA0] | 0xF99FFA0 | 8B | `0x1289490  call qword ptr [0xF99FFA0]` (sub_12893d0); 5 sites in sub_4e05e50 e.g. `0x4e05e86` | `0x1289490  call qword ptr [0xF99FFA0]` | slot holds sub_4e05e50 at the sub_12893d0 call site: capture mc_root_4e05e50_callers.txt:3 `CALLER ret=0x1289496` = instr `0x1289496  nop` right after this call; same slot = allocator at registration sites (`0x1870e75  call qword ptr [0xF99FFA0]`) — contents vary by call site [V live] | [V live] |
| Object ptr range begin/end (sub_12893d0) | rcx+0/rcx+8 | 8B | [rcx] (begin), [rcx+8] (end) | `0x1289406  mov r13,[rcx]` ; `0x1289409  mov r14,[rcx+8]` | sub_12893d0 iterates [begin,end) step 0x18 (TexturePtr-style array of 0x18-byte entries); real entry is 0x12893d0 (0x1289440 is a loop label); 0 static xrefs | [V] |
| Texture-ref entry +0x8 object (+refcount) | entry+0x8 | 8B | [r13+8] | `0x1289431  mov rcx,[r13+8]` ; `0x128943a  mov eax,[rcx+8]` | entry object pointer (from [r13+8]); its refcount read at [rcx+8] for the spin add-ref `0x1289440  test eax,eax` / `0x1289444  lea edx,[rax+1]` / `0x1289447  lock cmpxchg [rcx+8],edx` (retry until [rcx+8]==eax or count hit 0) | [V] |
| Texture-ref entry +0x10 pointee | entry+0x10 | 8B | [r13+0x10] | `0x128947d  mov rcx,[r13+0x10]` ; `0x128949b  mov qword ptr [r13+0x10],0` | pointee fetched then nulled (consume); virtual slot-1 call `0x1289490  call qword ptr [0xF99FFA0]` (rdx=&local) = sub_4e05e50 per live capture [V live]; old pointee released `0x12894ab  mov rax,[rax]` (vtable slot 0) `0x12894b3  call qword ptr [0xF99FFA0]` | [V] |
| Refcounted object +0x8 strong refcount | obj+0x8 | 4B | [rbx+8] (sub_4e05e50) | `0x4e05ebd  lock inc dword ptr [rbx+8]` ; `0x4e05ec9  lock dec dword ptr [rbx+8]` | strong refcount inc around the upload bridge, dec after; balanced inc/dec pair | [V] |
| Refcounted object +0xC weak refcount | obj+0xC | 4B | [rbx+0xC] [rdi+0xC] [r15+0xC] | `0x4e05ede  lock dec dword ptr [rbx+0xC]` ; `0x4e05f3c  lock dec dword ptr [rbx+0xC]` ; `0x4e06035  lock dec dword ptr [rdi+0xC]` ; `0x128952f  lock dec dword ptr [r15+0xC]` | second (weak/inner) refcount, released to zero on all release paths | [V] |
| Refcounted object +0x10 control block | obj+0x10 | 8B | [rdi+0x10] [r15] [rax+8] | `0x4e05e8c  mov rdx,[rdi+0x10]` ; `0x1289515  lock dec dword ptr [r15+8]` ; `0x128953d  mov rax,[rax+8]` | MC_obj+0x10 = refcounted control block (`0x4e05e8c`); release chain reads object vptr then vtable slot 1 `0x128953a  mov rax,[r15]` `0x128953d  mov rax,[rax+8]` `0x1289544  call qword ptr [0xF99FFA0]` (final release) | [V] |
| Stack flag [rbp+0x38] | rbp+0x38 | 1B | [rbp+0x38] | `0x4e05f5d  mov byte ptr [rbp+0x38],0` ; `0x4e05fcf  cmp byte ptr [rbp+0x38],1` | flag gating the sub_e935700 cleanup path in sub_4e05e50 | [V] |
| Stack saved ptr [rbp+0x40] | rbp+0x40 | 8B | [rbp+0x40] | `0x4e05f52  cmp qword ptr [rbp+0x40],0` | saved pointer (MC_obj+0x8); zero skips the upload bridge | [V] |
| Released 0x18-byte array entries | array+0x8/array+0x10 | 8B | [rbx+0x10] [rbx+8] [rcx+0xC] | `0x1289569  mov rcx,[rbx+0x10]` ; `0x1289583  mov rcx,[rbx+8]` ; `0x128958c  lock dec dword ptr [rcx+0xC]` | tail releases each array entry: release slot-0 (`0x128957d  call qword ptr [0xF99FFA0]`) or dec +0xC then slot-1 release (`0x1289599  call qword ptr [0xF99FFA0]`); step 0x18 via `0x1289560  add rbx,0x18` | [V] |

## CLOSES?

NO — single blocking fact: the atlas TEXTURE-CREATION STITCHER is still not located. Registration is fully proven [V] (TerrainAtlas string/len/idx 6, ItemAtlas idx 7, AnimatedAtlas idx 8; 0x48-byte nodes with +0 dispatch object/+8 idx/+0x10 name/+0x18 length; registry slots 0..41 with '*' sentinel), but no static or live path leads from the registered nodes to createTexture (slot 26, one static caller `0xe81455b call 0xE81BF30`) or resizeTexture (slot 31, 0 static xrefs, never observed live) with atlas parameters (name, size, layers, mips>1). Everything else in the item line is answered: compression answered negatively [V] (BC1/BC3/BC7/DXT strings unreferenced; only PNG/zlib decompression exists; all 24 live creations format 0x1C uncompressed), mip generation absent [V] (numMips only store is desc+0xB1; live numMips=1; material mip keys are load-time params). The cross-module object pointer at MC_obj+0x00 = 0x00007FF6A8215838 [V live] is consistent with atlas/stitcher logic living in another module or being data-driven, which is why static analysis of the exe alone cannot close it.

## What I tried that failed (do not redo)

- xref str "Atlas" (earlier attempts): only tangential hits (BlockThumbnailAtlas, shadow atlas 0xbb682b0, mip sampling funcs); not repeated here.
- descscan2.py: TypeError in ranges_for — unusable for walking the description build (earlier attempt).
- Backward from createTexture and forward stitcher from registration objects (sub_2fe440 cleanup-only, sub_772520 name+idx only): exhausted earlier; not repeated.
- BGFX_MAP.md grep "atlas" this unit: tangential only (PointLightShadowTextureAtlas, MaterialTerrainTextureAtlas string-only, TerrainAtlasBlit render task) — no stitcher [I].
- livemem read on 0x7FF6A8215838: not attempted — the cross-module pointer is already [V live] from the capture and a read cannot find a stitcher that is not in the exe.

## TOOL REQUESTS

- sub_1289440_callers (rva 0x1289440) — state pending in docs/progress/capture_requests.json (4-pending limit reached, so no new request can be added yet). When the orchestrator runs it, check `python tools/livecap/request.py result sub_1289440_callers`: ret= values name sub_12893d0's runtime callers; if a caller chain reaches texgroup_load 0x5421c90 / texload 0x58a1310 building atlas descriptions, that closes the "connection" question [?].
- l8b_resizetex_slot31 (rva 0xe815840) — state pending. ret= would name the stitcher caller; mips>1 or atlas parameters would be mip-generation/atlas-creation evidence. If either capture flips the stitcher question, revisit CLOSES?; otherwise CLOSES? stays NO with the stitcher as the single blocking fact.
- None else. No helper scripts written this unit.
