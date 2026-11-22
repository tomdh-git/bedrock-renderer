## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression — RETRY #3

Goal: close checklist item "L8b Atlases (terrain, items), mipmaps and compression pending" (docs/RENDER_CHECKLIST.md:345).
Static analysis only (OPENCODE_BRIEF.md rule 1); exe = Minecraft.Windows.exe 1.26.62.01; RVAs relative to image base.
Tags: [V] = verbatim instruction line seen in an rdis listing of the exe; [V live] = docs/data/live capture file + line; [I] = inferred; [?] = unknown.
Carried proven facts from oc_U-EL8b_r1..r37 are NOT re-derived; they are cited as [V] and used as context.
This unit adds: (a) full decode of sub_4e05e50 (previously only its entry was known), (b) the indirect caller of sub_4e05e50 named from the live capture (sub_1289440, ret=0x1289496), (c) connection of sub_4e05e50 to sub_bc41420/createTexture, (d) honest CLOSES? assessment.

## Carried proven facts (not re-derived)

- Atlas registration: sub_186f720 region passes name+len+idx to sub_1870DE0: TerrainAtlas string 0xF55CDD3 len 0xC idx 6 (`0x186f731 lea rax,[0xF55CDD3]`, `0x186f767 mov r9d,6`, `0x186f76d call 0x1870DE0`); ItemAtlas string 0xF55CDE0 len 9 idx 7 (`0x186f7fc lea rax,[0xF55CDE0]`, `0x186f832 mov r9d,7`, `0x186f838 call 0x1870DE0`) [V]. Note: the 2026-11-21 claim "no item-atlas string/code in the exe" is FALSE — ItemAtlas IS in the exe [V].
- Triggered from ServerLevelLoad sub_1042320 (call at 0x104237e) and initStep1 sub_8f6810 (call at 0x8f6919) [V carried].
- Registry slot scan: `0x1870e30 cmp dword ptr [rcx],0x2A` ('*' sentinel), `0x1870e4c cmp r14d,0x29` (slots 0..41) [V]. Node allocated 0x48 bytes (`0x1870e70 mov edx,0x48`, `0x1870e75 call qword ptr [0xF99FFA0]` -> sub_eea6040) [V]. Node fields: +0 vptr cleared (`0x1870ec5 mov [rsi],rax`), +8 idx (`0x1870ecb mov [rsi+8],eax`), +0x10 dispatch object (`0x1870f0e mov [rbx+0x10],rax`) [V].
- TextureD3D12::create entry 0xe81bf30 via createTexture wrapper slot 26: `0xe81455b call 0xE81BF30` (next instr 0xe814560 = the observed caller ret) [V]. Desc fields: +0xB0 format byte (`0xe81c077 mov [rdi+0xB0],r13b`), +0xB1 numMips byte (`0xe81c0d1 mov [rdi+0xB1],dl`) [V]; numMips only store located [V].
- resizeTexture slot 31 at 0xe815840 (`0xe815840 push rbp`, `0xe815866 mov edi,r9d` -> r9d = mips param): 0 static xrefs, never observed live [V].
- Negative: BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V]; no compression path [V]; mip generation absent [V] (material mip keys are load-time params; glGenerateMipmap@0xe92c2c0 GLES glue only); no static stitcher from registration nodes to createTexture/resizeTexture [V carried].

## New proof this session (sub_4e05e50 + live captures)

- sub_4e05e50 fully decoded [0x4e05e50..0x4e06074), size 0x224, 0 static xrefs (invoked only indirectly). It is the dragon-layer texture-upload bridge, not an atlas stitcher: rcx = MC_obj, rdx = out ptr; reads MC_obj+0x18 (release target, passed with MC_obj+0x58 to [0xF99FFA0]); refcounted control block at MC_obj+0x10 (lock cmpxchg inc on +8, dec/release paths on +8 and +0xC); computes dragon_obj = MC_obj+0x58 (`0x4e05e7e lea rdx,[rdi+0x58]`; `0x4e05f68 add rdi,0x58`); reads MC_obj+0xE0 -> r9 (`0x4e05f61 mov r9,[rdi+0xE0]`); calls sub_bc41420(rcx=dragon_obj, rdx=&desc at rbp-0x50, r8=[MC_obj+8], r9=[MC_obj+0xE0]) then sub_4e061b0; some paths null [rsi] and release [rbp+0x48] (`0x4e06010 mov qword ptr [rsi],0`). Chain per L8a/L7e captures: sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (cmd-byte-14) -> dispatcher slot-26 -> TextureD3D12::create 0xe81bf30 [V]. Live entries of sub_4e05e50 show format 0x1C, numMips=1, names "tex"/"Texture: ####" — regular textures, no atlas names [V live].
- Indirect caller of sub_4e05e50 NAMED: capture entry 0x4e05e50 (docs/data/live/mc_root_4e05e50_callers.txt) has CALLER ret=0x1289496 only [V live line 3]. ret=0x1289496 is the instruction immediately after `0x1289490 call qword ptr [0xF99FFA0]` in sub_1289440 (`0x1289496 nop`) [V]. So sub_1289440 calls sub_4e05e50 indirectly via data slot [0xF99FFA0] at 0x1289490; sub_1289440 is a TexturePtr-style ensure-load/release consumer (refcount CAS `0x1289447 lock cmpxchg [rcx+8],edx`, fetches+nuls [r13+0x10] at `0x1289497`/`0x128949b`) — NOT the atlas stitcher [V]. Static xrefs to sub_4e05e50 and sub_1289440: 0 [V].
- Connection to texgroup_load 0x5421c90 / texload 0x58a1310 and TexturePtr.mClientTexture: NOT established (sub_1289440_callers capture pending; 0 static xrefs) [?].
- Live texture census l8b_texcreate_record.txt (entry 0xe81bf30, caller ret=0xe814560): 24 samples, ALL format 0x1C uncompressed, numMips=1, names "Texture: 2815"/"Texture: 2799"/"tex"; zero atlas names, zero compressed formats [V live lines 4-27].
- mc_root_4e05e50_callers.txt: live objects at RCX carry [MC_obj+0x0] = 0x00007FF6A8215838, a cross-module pointer outside the exe image (image 0x7ff7a59c0000..0x7ff7bd2fe000) [V live line 4 RCX bytes] — object decode may live in another module / driver; supports "CPU decode in another module / data-driven".

## ANSWER TABLE — one row per distinct offset; all instruction sites listed; sizes from the instruction; verbatim lines from rdis listings of the exe

| name | offset | size | site(s) (read/store address) | verbatim `0xRVA  instr` | meaning shown by instruction or string | tag |
| Atlas node vptr | 0x0 | 8B | [rsi] (node, sub_1870DE0) | `0x1870ec5  mov [rsi],rax` | node+0 = vptr cleared; node allocated 0x48 bytes (`0x1870e70 mov edx,0x48`) | [V] |
| Atlas node idx / object+0x8 refcount | 0x8 | 4B | [rsi+8] (node idx); [rcx+8] [rdx+8] [rbx+8] (refcount CAS/inc/dec) | `0x1870ecb  mov [rsi+8],eax` ; `0x1289447  lock cmpxchg [rcx+8],edx` ; `0x4e05ebd  lock inc dword ptr [rbx+8]` ; `0x4e05ec9  lock dec dword ptr [rbx+8]` | node+8 = atlas idx (TerrainAtlas 6 / ItemAtlas 7); object+0x8 = refcount | [V] |
| Object+0x10 refcounted control block | 0x10 | 8B | [r13+0x10] (sub_1289440); [rdi+0x10] and [rax+0x10] (sub_4e05e50, MC_obj) | `0x1289497  mov rcx,[r13+0x10]` ; `0x128949b  mov qword ptr [r13+0x10],0` ; `0x4e05e8c  mov rdx,[rdi+0x10]` ; `0x4e05e82  mov rax,[rax+0x10]` | object+0x10 = refcounted control block; fetched, nulled, released via vtable | [V] |
| Object+0xC second refcount | 0xC | 4B | [rbx+0xC] [rdi+0xC] [r15+0xC] | `0x4e05ede  lock dec dword ptr [rbx+0xC]` ; `0x4e05f3c  lock dec dword ptr [rbx+0xC]` ; `0x4e06035  lock dec dword ptr [rdi+0xC]` ; `0x128952f  lock dec dword ptr [r15+0xC]` | +0xC = second (weak/inner) refcount, released to zero | [V] |
| MC_obj+0x18 release target | 0x18 | 8B | [rcx+0x18] | `0x4e05e71  mov rax,[rcx+0x18]` ; `0x4e05e86  call qword ptr [0xF99FFA0]` | sub_4e05e50: MC_obj+0x18 object released with MC_obj+0x58 as argument | [V] |
| MC_obj+0x58 dragon_obj (address math) | 0x58 | 8B | [rdi+0x58] computed via lea, then rdi += 0x58 | `0x4e05e7e  lea rdx,[rdi+0x58]` ; `0x4e05f68  add rdi,0x58` ; `0x4e05f77  call 0xBC41420` | MC_obj+0x58 = dragon_obj passed as rcx to upload bridge sub_bc41420 (lea/add address arithmetic; no memory read of dragon_obj inside sub_4e05e50) | [V] |
| Stack flag [rbp+0x38] | 0x38 | 1B | [rbp+0x38] | `0x4e05f5d  mov byte ptr [rbp+0x38],0` ; `0x4e05fcf  cmp byte ptr [rbp+0x38],1` | flag gating sub_e935700 cleanup path in sub_4e05e50 | [V] |
| Stack saved ptr [rbp+0x40] | 0x40 | 8B | [rbp+0x40] | `0x4e05f52  cmp qword ptr [rbp+0x40],0` | saved pointer (MC_obj+0x8); zero skips the upload bridge | [V] |
| MC_obj+0xE0 upload arg | 0xE0 | 8B | [rdi+0xE0] | `0x4e05f61  mov r9,[rdi+0xE0]` | sub_4e05e50: MC_obj+0xE0 passed as 4th arg (r9) to sub_bc41420 | [V] |
| Indirect-call data slot | 0xF99FFA0 | 8B | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` ; `0x4e05e86  call qword ptr [0xF99FFA0]` (5 sites in sub_4e05e50) | indirect-call data slot; capture at entry 0x4e05e50 shows caller ret=0x1289496 = instr right after the 0x1289490 call => [0xF99FFA0] = sub_4e05e50 at that site [V live docs/data/live/mc_root_4e05e50_callers.txt:3] | [V live] |
| Texture desc format byte | 0xB0 | 1B | [rdi+0xB0] | `0xe81c077  mov [rdi+0xB0],r13b` | TextureD3D12::create desc+0xB0 format byte; every live creation format 0x1C uncompressed [V live docs/data/live/l8b_texcreate_record.txt:4-27] | [V] |
| Texture desc numMips byte | 0xB1 | 1B | [rdi+0xB1] | `0xe81c0d1  mov [rdi+0xB1],dl` | desc+0xB1 numMips byte; live numMips=1 [V live docs/data/live/l8b_texcreate_record.txt:4-27] | [V] |

## CLOSES?

NO — single blocking fact: the atlas TEXTURE-CREATION STITCHER is still not located. Registration is proven [V] (TerrainAtlas idx 6, ItemAtlas idx 7, 0x48-byte nodes, registry slots 0..41), but no static or live path leads from the registered nodes to createTexture/resizeTexture with atlas parameters: createTexture wrapper slot 26 has exactly one static caller (`0xe81455b call 0xE81BF30`, ret=0xe814560 observed live [V]); resizeTexture slot 31 (0xe815840, r9d = mips — mips>1 would be mip-generation evidence) has 0 static xrefs, was never observed live, and its capture (l8b_resizetex_slot31) together with sub_1289440_callers is still pending (orchestrator has not run them). Compression is answered negatively [V]: BC1/BC3/BC7/DXT strings unreferenced, only PNG/zlib decompression exists, all live creations format 0x1C numMips=1 [V live]. Mip generation absent [V]. Item blocked on the stitcher; parked in MIRROR_SKIP/external (another module or data-driven, consistent with the cross-module +0x00 pointer at MC_obj+0x0 [V live]) pending the live captures.

## What I tried that failed (do not redo)

- descscan2.py: TypeError in ranges_for — unusable for walking the description build.
- livemem read/vt on captured object addresses (e.g. 0x7FF6A8215838): unreadable — pointers were from a previous capture instance.
- xref str "Atlas": only tangential hits (BlockThumbnailAtlas 0x1585e00 builds a 0x130 description at a0+0x90 via sub_15ab4d0, no texture creation in first 80 instrs; shadow atlas 0xbb682b0; mip sampling funcs 0xbc7f6e0/bcd77b0).
- xref str "Mip": mip-key strings only (load-time params), no generator code.
- Backward from createTexture: exhausted — one static caller (wrapper 0xe81455b); all live callers ret=0xe814560 / 0xBC6A2C8 command interpreter; l8b_texcreate_record (24 samples) all format 0x1C numMips=1, no atlas names.
- Forward stitcher from registration objects: sub_2fe440 cleanup-only, sub_772520 registers name+idx only, no createTexture/resizeTexture inside sub_186f720/sub_1870e00/sub_2fe440/sub_772520 [V]. Not located.

## TOOL REQUESTS

None new by this unit (pending-capture limit of 4 already reached). Relevant pending requests queued by earlier attempts, results not yet available: l8b_resizetex_slot31 (rva 0xe815840, resizeTexture slot 31 mips param — ret= would name the stitcher caller; mips>1 is mip-gen evidence) and sub_1289440_callers (rva 0x1289440 — would connect the TexturePtr consumer to texgroup_load 0x5421c90 / texload 0x58a1310). If l8b_resizetex_slot31 returns a caller chain into level-load/atlas code with mips>1 or atlas names, revisit CLOSES?; otherwise CLOSES? stays NO with the stitcher as the single blocking fact.
