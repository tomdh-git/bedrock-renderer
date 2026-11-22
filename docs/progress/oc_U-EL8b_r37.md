## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression — RETRY #2

Goal: close checklist item "L8b Atlases (terrain, items), mipmaps and compression pending" (docs/RENDER_CHECKLIST.md:345).
Static analysis only (OPENCODE_BRIEF.md rule 1); exe = Minecraft.Windows.exe 1.26.62.01; RVAs relative to image base.
Tags: [V] = verbatim instruction line seen in an rdis listing and re-checked against the exe with tools/sigs/verify_oc.py; [I] = inferred (say from what); [-] = meaning not shown by any instruction/string.
One annotated row per distinct offset; all instruction sites listed.

## Carried proven facts (from oc_U-EL8b_r36.md, NOT re-derived)
- Atlas registration [V]: sub_186e6a0 -> sub_1870de0; node 0x48 bytes, name at obj+0, idx at obj+8; triggered from ServerLevelLoad sub_1042320 (call 0x186e6a0 at 0x104237e) and initStep1 sub_8f6810 (call at 0x8f6919).
- "TerrainAtlas" string 0xF55CDD3 and "ItemAtlas" string 0xF55CDE0 referenced ONLY by registration inside sub_186e6a0 [V via xref str]; no item-atlas string/code elsewhere [V].
- No createTexture/resizeTexture inside sub_186e6a0/sub_1870de0/sub_772520 [V]; sub_2fe440 cleanup-only [V].
- TextureD3D12::create at 0xe81bf30 via createTexture slot 26 (`call 0xE81BF30` at 0xe81455b; 0 static callers); resizeTexture slot 31 at 0xe815840 (r9d = mips, 0 static xrefs, never observed live) [V].
- numMips only store located: desc+0xB1 `0xe81c0d1 mov [rdi+0xB1],dl` [V]; format byte desc+0xB0 `0xe81c077 mov [rdi+0xB0],r13b` [V].
- BC1/BC3/BC7/DXT1-DXT5 strings unreferenced [V via xref]; no compression path [V]. mip generation not located [V]; material mip keys are load-time params; glGenerateMipmap@0xe92c2c0 GLES glue only.

## Input data processed this session
docs/progress/oc_U-L8b.md (unit U-L8b: PNG/TGA decoder + texture-loading entry; all RVAs [V via rdis]).
This file converts its [reg+off] memory accesses into the field/offset map below: one row per distinct offset, every instruction site listed, size from the instruction, verbatim line copied from the input data listing.
Note: two sites in the input listing carried transposed addresses (0x599de52/0x599de59 around [rbp+0x340]/[rbp+0x338]; 0x3f7edef around [rbp+8]); rows here use the addresses confirmed by `rdis dis` of the exe, not the typos in the input text.

## ANSWER TABLE — field/offset map extracted from oc_U-L8b.md
| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
| 0x0 | 8B/1B/4B by site | [rbx] [rcx] [r9] [rdi] [rax] [rsi] [rbp] | `0x777f1e  mov qword ptr [rbx],8` ; `0x777f52  movzx ecx,byte ptr [rcx]` ; `0x777f63  cmp dword ptr [r9],0` ; `0x781595  mov rsi,[rcx]` ; `0x7815cd  movzx ecx,byte ptr [rcx]` ; `0x14754c4  mov [rdi],rax` ; `0x147549f  mov rax,[rcx]` ; `0x39976b  mov [rcx],r9` ; `0x3f7ee12  mov rax,[rcx]` ; `0x3f7ee30  mov [rsi],rsi` ; `0x779ae33  mov rax,[rax]` ; `0x779ae36  mov byte ptr [rax],0` ; `0x147548d  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE` | - | [V] |
| 0x4 | 4B | [r8+4] | `0x39973a  cmp eax,[r8+4]` | - | [V] |
| 0x8 | 16B (movups), 8B/4B others | [rbx+8] [rcx+8] [rax+8] [rsi+8] [rbp+8] | `0x777f25  mov dword ptr [rbx+8],0` ; `0x7815a3  movups [rcx+8],xmm0` ; `0x14754a2  mov rax,[rax+8]` ; `0x399774  mov [rcx+8],rdx` ; `0x3f7ee15  mov rax,[rax+8]` ; `0x3f7ee33  mov [rsi+8],rsi` ; `0x3f7edef  mov qword ptr [rbp+8],0xFFFFFFFFFFFFFFFE` | - | [V] |
| 0x10 | 8B/4B by site | [r15+0x10] [rsi+0x10] [rbp+0x10] [rcx+0x10] [r14+0x10] | `0x777f71  mov rax,[r15+0x10]` ; `0x7815e8  mov rax,[rsi+0x10]` ; `0x3f7edec  sub [rbp+0x10],esi` ; `0x599de71  mov rcx,[rcx+0x10]` ; `0x779ae39  mov rax,[r14+0x10]` | - | [V] |
| 0x18 | 8B | [rcx+0x18] [rax+0x18] | `0x7815a7  mov qword ptr [rcx+0x18],0` ; `0x779ae20  mov rax,[rcx+0x18]` ; `0x779ae2c  cmp qword ptr [rax+0x18],0x10` | - | [V] |
| 0x28 | 8B | [r15+0x28] [rsi+0x28] | `0x777f75  mov rcx,[r15+0x28]` ; `0x7815ec  mov rcx,[rsi+0x28]` | - | [V] |
| 0x30 | 4B | [rsi+0x30] | `0x7815da  cmp dword ptr [rsi+0x30],0` | - | [V] |
| 0x34 | 4B | [r15+0x34] [rsi+0x34] | `0x777f6d  mov r8d,[r15+0x34]` ; `0x7815e4  mov r8d,[rsi+0x34]` | - | [V] |
| 0x40 | 8B | [rdi+0x40] [rsi+0x40] | `0x14754cf  mov qword ptr [rdi+0x40],0` ; `0x14754d7  mov rcx,[rsi+0x40]` | - | [V] |
| 0x50 | 4B | [rdx+0x50] | `0x14747c2  cmp dword ptr [rdx+0x50],0xC8` | - | [V] |
| 0x58 gs | 8B | gs:[0x58] | `0x39972d  mov r9,gs:[0x58]` | - | [V] |
| 0x10C | 2B | [rsp+0x10C] | `0x78158b  mov word ptr [rsp+0x10C],0` | - | [V] |
| 0x10E | 1B | [rsp+0x10E] | `0x781583  mov byte ptr [rsp+0x10E],0` | - | [V] |
| 0x260 | 16B | [rbp+0x260] | `0x599de6a  movaps [rbp+0x260],xmm0` | - | [V] |
| 0x2F8 | 8B | [rbp+0x2F8] | `0x14747cf  mov [rbp+0x2F8],rcx` | - | [V] |
| 0x300 | 16B | [rbp+0x300] | `0x14747ac  movaps [rbp+0x300],xmm0` | - | [V] |
| 0x310 | 8B | [rbp+0x310] | `0x14747b3  mov qword ptr [rbp+0x310],0` | - | [V] |
| 0x320 | 8B | [rbp+0x320] | `0x147479b  mov qword ptr [rbp+0x320],0xFFFFFFFFFFFFFFFE` | - | [V] |
| 0x338 | 8B | [rbp+0x338] | `0x599de59  mov qword ptr [rbp+0x338],0xFFFFFFFFFFFFFFFE` | - | [V] |
| 0x340 | 16B | [rbp+0x340] | `0x599de52  movaps [rbp+0x340],xmm6` | - | [V] |
| 0x430 | 16B | [rbp+0x430] | `0x69c95a3  movaps [rbp+0x430],xmm0` | - | [V] |
| 0x440 | 16B | [rbp+0x440] | `0x69c95ad  movaps [rbp+0x440],xmm0` | - | [V] |
| 0x450 | 1B | [rbp+0x450] | `0x69c95b4  mov byte ptr [rbp+0x450],0` | - | [V] |
| 0x458 | 4B | [rbp+0x458] | `0x69c95bb  mov dword ptr [rbp+0x458],0xFFFFFFFF` | - | [V] |
| 0x460 | 16B | [rbp+0x460] | `0x69c95c5  movaps [rbp+0x460],xmm0` | - | [V] |
| 0x470 | 8B | [rbp+0x470] | `0x69c95cc  mov qword ptr [rbp+0x470],0` | - | [V] |
| 0x478 | 8B | [rbp+0x478] | `0x69c95d7  mov qword ptr [rbp+0x478],0xF` | - | [V] |
| 0x480 | 16B | [rbp+0x480] | `0x69c95e2  movaps [rbp+0x480],xmm0` | - | [V] |
| 0x490 | 8B | [rbp+0x490] | `0x69c95e9  mov qword ptr [rbp+0x490],0` | - | [V] |
| 0x498 | 8B | [rbp+0x498] | `0x69c95f4  mov qword ptr [rbp+0x498],0xF` | - | [V] |
| 0x89B8 | 8B | [rsp+0x89B8] | `0x777f16  mov [rsp+0x89B8],rax` | - | [V] |
| 0x89C0 | 16B | [rsp+0x89C0] | `0x777ee9  movaps [rsp+0x89C0],xmm6` | - | [V] |
| 0x8A40 | 4B | [rsp+0x8A40] | `0x777f05  mov edi,[rsp+0x8A40]` | - | [V] |
| 0x8A48 | 8B | [rsp+0x8A48] | `0x777efd  mov rbx,[rsp+0x8A48]` | - | [V] |
| 0xC0 | 8B | [rcx+0xC0] [r15+0xC0] [rsi+0xC0] | `0x777f34  mov rcx,[rcx+0xC0]` ; `0x777f4b  mov [r15+0xC0],rdx` ; `0x7815af  mov rcx,[rsi+0xC0]` ; `0x7815c6  mov [rsi+0xC0],rdx` | - | [V] |
| 0xC8 | 8B | [r15+0xC8] [rsi+0xC8] | `0x777f3b  mov rax,[r15+0xC8]` ; `0x7815b6  mov rax,[rsi+0xC8]` | - | [V] |
| -0x8 | 8B | [rbp-8] | `0x14754de  mov [rbp-8],rdi` | - | [V] |
| -0x18 | 8B | [rbp-0x18] | `0x14754cb  mov [rbp-0x18],rax` | - | [V] |
| -0x46 | 1B | [rbp-0x46] | `0x779ae8e  movzx ecx,byte ptr [rbp-0x46]` | - | [V] |
| -0x48 | 4B | [rbp-0x48] | `0x779ae8b  xor eax,[rbp-0x48]` | - | [V] |

## New angle attempted for the blocking fact (sub_4e05e50 / sub_1289440 chain)
- Decoded sub_1289440 (`rdis dis 0x1289440 48`, size 0x2000, 0 xrefs in): refcount decref/release path on [rcx+8] — `0x1289447  lock cmpxchg [rcx+8],edx`; on zero it reads `0x128947d  mov rcx,[r13+0x10]` and calls `0x1289490  call qword ptr [0xF99FFA0]` (= sub_eea6040) then releases via `0x12894b3  call qword ptr [0xF99FFA0]`. This is a TexturePtr ensure-loaded/release CONSUMER, not an atlas stitcher [V via rdis]. `xref.py callers 0x1289440` = 0 hits (called only indirectly) [V via xref]. The mc_root_4e05e50_callers.txt capture confirms CALLER ret=0x1289496 only (sub_4e05e50 entered from the 0x1289490 call site) — consumer side, no stitcher [V live].
- Live texture census docs/data/live/l8b_texcreate_record.txt [V live]: 24 creations via createTexture/TextureD3D12::create (CALLER ret=0xE814560), all format 0x1C uncompressed, numMips=1, names "Texture: 2815"/"Texture: 2799"/"tex"; zero atlas names, zero compressed formats.
- Pending live captures (queued earlier, NO results yet): l8b_resizetex_slot31 (rva 0xe815840, resizeTexture slot 31 — would show mips>1 or atlas handle), sub_1289440_callers (rva 0x1289440 — would name the indirect caller). `python tools/livecap/request.py result <name>` returns "no result yet" for both.

## TOOL REQUESTS
None new. Pending live captures queued by earlier attempts (results not yet available): l8b_resizetex_slot31, sub_1289440_callers.

CLOSES? NO — single blocking fact: the TerrainAtlas/ItemAtlas stitcher (code that builds an atlas texture description and issues createTexture/resizeTexture with atlas params/slots), mip generation, and BC1/BC3/BC7 compression are not present in the exe statically; no item-atlas string/code anywhere [V]; BC strings unreferenced [V]; numMips only store is desc+0xB1 (0xe81c0d1) [V]; live census shows only uncompressed format 0x1C numMips=1 creations [V live]; the sub_4e05e50/sub_1289440 chain is a TexturePtr consumer only, not the stitcher [V]. Blocking fact remains: stitcher/mip-gen/compression not located; needs the pending live captures above or a cross-module/live decode; item parked in MIRROR_SKIP per prior reviews.
