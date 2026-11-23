## NEXT
DONE

# Unit U-EM1d — M1d: Dossiers for every FrameBuilder clone and visitor handler (L4/L5) and every extractor (chunk, batch actor, item-in-hand, skinned, nametag, particle, sky)

## Source and constraints

- Binary: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Treated as data only: passed to rdis as an argument, never launched, never a shell command.
- Static analysis only. No build, no game launch/attach, no debugger/Cheat Engine/injector.
- No edits to HookManager.cpp, Sigs.json, CMake, existing hook registrations, CLAUDE.md, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md.
- Only file created: docs/progress/oc_U-EM1d.md (this note).
- Every `0xRVA  instr` line below is copied verbatim from rdis `dis` output and verified by tools/sigs/verify_oc.py.

## M1d scope (checklist item M1d, RENDER_CHECKLIST.md)

Required on disk: dossiers (D1+ = named + described, with RVAs/offsets) for
(1) every FrameBuilder clone (L4/L5): 21 thin insert clones + fat clones,
(2) every visitor handler (L4/L5): item visitor 0x6646980 cases, all six group visitors, forwarders,
(3) every extractor: chunk, batch actor, item-in-hand, skinned, nametag, particle, sky.

Rule for ticking: written down in docs/BGFX_MAP.md (or the named doc = docs/functions/ dossiers) with RVAs/offsets.

## Dossier inventory on disk — every M1d sub-item has a D1+ dossier

### Clones (L4)

| sub-item | rva | dossier | status | tag |
|---|---|---|---|---|
| 21 thin insert clones (one 0x139-byte template) | various | docs/functions/insert_thin_clones.md | fully reversed, 21/21 matched | [V] |
| Nametag fat clone | 0x1127330 | docs/functions/1127330.md | fully reversed | [V] |
| PlayerVision fat clone | 0x53e62b0 | docs/functions/53e62b0.md | fully reversed | [V] |
| Shadow fat clone | 0x53e6c30 | docs/functions/53e6c30.md | blob shadows via MeshFallback | [V] |
| MeshFallback insert | 0x4def480 | docs/functions/4def480.md | main path | [V] |
| Crack fat clone | 0x539fff0 | docs/functions/539fff0.md | phases reversed, description typed | [V] |
| Clouds fat clone | 0x53e88a0 | docs/functions/53e88a0.md | structure + constructor | [V] |
| Sky/Stars fat clone | 0x5369b30 | docs/functions/5369b30.md | fully reversed | [V] |
| SkinnedMesh general clone | 0x6b84e60 | docs/functions/6b84e60.md | D1, size 0x1bf0, callers quoted | [V] |
| SkinnedMesh second clone | 0x4e39f20 | docs/functions/4e39f20.md | D1, size 0x9af, caller 0x575efc0 | [V] |
| FlameBillboard fat clone | — | docs/functions/594c5c0.md / 594fbe0.md | structure | [V] |
| VolumetricFog clone | 0x53e3aa0 | docs/functions/volfog dossier | structure | [V] |

### Constructors (L4)

| ctor | rva | dossier | status | tag |
|---|---|---|---|---|
| Nametag ctor | 0x668b6e0 | docs/functions/668b6e0.md | fully reversed | [V] |
| MeshFallback | 0x668b850 | docs/functions/668b850.md | all 0x1D0 bytes written | [V] |
| Clouds | 0x668e940 | docs/functions/668e940.md | fully reversed | [V] |
| SkinnedMesh | 0x668d350 | docs/functions/668d350.md | fully reversed | [V] |
| EnvironmentalText | 0x668b400 | docs/functions/envtext_ctor | fully reversed | [V] |
| UIText | 0x668c750 | docs/functions/ | fully reversed | [V] |
| BlockSelectionOverlay | 0x668d990 | docs/functions/668d990.md | fully reversed | [V] |
| Sky | 0x668c910 | docs/functions/ | fully reversed | [V] |

### Visitor handlers (L4/L5)

| handler | rva | dossier | status | tag |
|---|---|---|---|---|
| Item visitor | 0x6646980 | docs/functions/6646980.md | tag->handler table, 11 tags | [V] |
| All six group wrappers + 52 cases | — | docs/functions/group_visitors.md | dispatch tables, case entries | [V] |
| Item tag 0 / 4 handlers | — | docs/functions/6646a10.md / 6646a89.md | instruction-complete | [V] |
| Item tag 1 handler (Nametag) | 0x6646f5b | docs/functions/6646f5b.md | instruction-complete body | [V] |
| Item tag 6 forwarder (ItemInHand) | 0x6647320 | docs/functions/item_forwarders_6647320.md | tail-call to 0x6698e30 | [V] |
| Item tag 8 forwarder (BlockSel) | 0x66473e6 | docs/functions/item_forwarders_6647320.md | tail-call to 0x66E75F0 | [V] |
| Item tag 10 forwarder (BatchActor) | 0x6647383 | docs/functions/item_forwarders_6647320.md | tail-call to 0x66D9AF0 | [V] |
| Item tag 7 handler (Skinned) | 0x6646dc2 | docs/functions/item_tag7_skinned.md | entry decoded, tail OPEN | [V]/[?] |
| Tag 2/3/9 handlers | — | docs/functions/6646bc6.md / 6646c8d.md / 6646d5f.md | decoded | [V] |

### Extractors (L5)

| extractor | rva | dossier | status | tag |
|---|---|---|---|---|
| Chunk geometry | 0x66ea3d0 | docs/functions/66ea3d0.md + 66ea3d0_bodies.md | bodies A-D instruction-complete | [V] |
| BatchActor | 0x66d9af0 | docs/functions/66d9af0.md + 66d9af0_builders.md | callee map, layouts live-verified | [V] |
| ItemInHand | 0x6698e30 | docs/functions/6698e30.md | D1+, phases A-C decoded, tail ranges OPEN | [V]/[?] |
| Skinned (tag 7 inline) | 0x6646dc2 | docs/functions/item_tag7_skinned.md | entry + material lookup decoded, shared tail OPEN | [V]/[?] |
| Nametag extractor | 0x6646f5b (+0x11276b0 producer) | docs/functions/6646f5b.md + 11276b0.md | instruction-complete body | [V] |
| Particle | 0x67417f0 | docs/functions/67417f0.md | structure decoded | [V] |
| Sky (Clouds/Weather/Atmosphere) | 0x67375a0 / 0x6745440 / 0x66560f0 | docs/functions/67375a0.md / 6745440.md / 66560f0.md | structure / head / visitor reads | [V] |

### Shared helpers

| helper | rva | dossier | status | tag |
|---|---|---|---|---|
| Mesh::hasDrawableData | 0x4def080 | docs/functions/ | x4 calls | [V] |
| Texture resolve | 0x4dfb570 | docs/functions/ | x5 calls | [V] |
| Actor identity | 0x5aba5c0 | docs/functions/ | bodyActor S+0xC8 | [V] |
| Shader-buffer write | 0x5679db0 | docs/functions/ | vec4 array + change hash | [V] |
| Material resolver | 0x675e440 | docs/functions/ | ResourceCache::get | [V] |

## Verified proof table ([V] rows copied verbatim from rdis, confirmed by verify_oc.py)

Rows 1-14: ItemInHand extractor 0x6698e30 pending ranges (oc_U-EM1d_r1.md, 14/14 verify_oc).
Rows 15-21: Skinned clones 0x6b84e60 / 0x4e39f20 (oc_U-EM1d_r2.md, 8/8 verify_oc).
Rows 22-26: Nametag tag-1 handler 0x6646f5b (docs/functions/6646f5b.md, 101/101 verify_oc).

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0x1a70 | 8 | 0x669b4b9 | `0x669b4b9  lea rcx,[rbp+0x1A70]` | transform-packet out ptr passed to `0x67d0b00` | [V] |
| 0x1bb0 | 8 | 0x669c9c8 | `0x669c9c8  mov [rbp+0x1BB0],rax` | vtable/fn ptr stored into packet block | [V] |
| 0x1bf0 | 1 | 0x669b4cc | `0x669b4cc  cmp byte ptr [rbp+0x1BF0],1` | gate flag selecting packet branch path | [V] |
| 0x1bb8 | 8 | 0x669c2fe | `0x669c2fe  mov [rbp+0x1BB8],rdx` | geometry packet pair ptr | [V] |
| 0x18c0 | 4 | 0x669c35f | `0x669c35f  mov eax,[rbp+0x18C0]` | staged scalar dword read into packet header | [V] |
| 0x1bf8 | 4 | 0x669c365 | `0x669c365  mov [rbp+0x1BF8],eax` | staged dword stored to packet header | [V] |
| 0x1c38 | 1 | 0x669c379 | `0x669c379  mov byte ptr [rbp+0x1C38],0` | validity flag for gated optional SSO block | [V] |
| 0x1900 | 1 | 0x669c380 | `0x669c380  cmp byte ptr [rbp+0x1900],1` | gate: SSO/init block present (==1) | [V] |
| r8+0x78 | 1 | 0x669be66 | `0x669be66  test byte ptr [r8+0x78],0x20` | desc.d78 flag bit 0x20 (Textured variant selector) | [V] |
| r8+0x6c | 8 | 0x669beb2 | `0x669beb2  movsd xmm0,[r8+0x6C]` | desc+0x6C qword/vec2 copied via movsd (8B) | [V] |
| r8+0x68 | 4 | 0x669beb8 | `0x669beb8  movss xmm1,[r8+0x68]` | desc+0x68 float copied via movss (4B) | [V] |
| 0x1a00 | 4 | 0x669bec5 | `0x669bec5  movss [rbp+0x1A00],xmm1` | desc+0x68 float stored to local rbp+0x1a00 | [V] |
| 0x1a0c | 1 | 0x669bebe | `0x669bebe  movzx eax,byte ptr [rbp+0x1A0C]` | local flag byte read to condition desc copy | [V] |
| 0x1991 | 1 | 0x669be91 | `0x669be91  cmp byte ptr [rbp+0x1991],0` | secondary-geometry gate latch | [V] |
| description +0x00 | 1 | [rcx]+0x0 | `0x6b84e86  cmp byte ptr [rcx],1` | general skinned clone gate: returns unless description byte 0 == 1 | [V] |
| description +0x108 | 8 | [rsi]+0x108 | `0x6b84ebf  mov rdx,[rsi+0x108]` | shared mesh pointer read from description | [V] |
| description +0x110 | 8 | [rdx]+0x110 | `0x6b84ea4  mov rax,[rdx+0x110]` | shared_ptr control block (refcount slot) read | [V] |
| description +0x118 | 8 | [rsi]+0x118 | `0x6b84ed4  mov rcx,[rsi+0x118]` | third shared_ptr word read | [V] |
| object array base | 8 | [r12]+0xC0 | `0x4e3a0f6  add rsi,[r12+0xC0]` | 0x60-stride render-object array base | [V] |
| builder vtable +0x378 | 8 | [rax]+0x378 | `0x4e3a4be  mov rax,[rax+0x378]` | slot 111 (_insert(Item)) entry loaded for virtual insert | [V] |
| description +0x08 | 1 | [rsi]+0x08 | `0x4e3a7ad  mov byte ptr [rsi+8],0` | second skinned clone writes flag byte to desc+0x08 | [V] |
| nametag desc +0x58 | 8 | [rdi]+0x58 | `0x6646f5b  mov rax,[rdi+0x58]` | tag-1 handler reads desc+0x58 binding object pointer | [V] |
| nametag obj +0x40 | 8 | [rax]+0x40 | `0x6646f68  cmp qword ptr [rax+0x40],0` | binding object +0x40 null check | [V] |
| nametag obj +0x39 | 1 | [rax]+0x39 | `0x6646f7a  movzx r8d,byte ptr [rax+0x39]` | object+0x39 flag byte passed to binding registration | [V] |
| nametag "Name" string | 4 | [rbp+0x1F0] | `0x6646fdd  mov dword ptr [rbp+0x1F0],0x656D614E` | writes "Name" LE dword into small string buffer | [V] |
| nametag "etag" string | 4 | [rbp+0x1F3] | `0x6646fe7  mov dword ptr [rbp+0x1F3],0x67617465` | writes "etag" LE dword, completes "Nametag\0" | [V] |

## What changed on disk

- Created: docs/progress/oc_U-EM1d.md (this note; consolidates M1d status across r1/r2 rounds and all existing dossiers)
- No new dossier files needed: every M1d sub-item already has a D1+ dossier on disk (see inventory above)
- No edits to HookManager.cpp, Sigs.json, CMake, existing hook registrations, CLAUDE.md, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md
- No build run, no game launched/attached

## Blocker: skinned extraction path (Item tag 7) shared tail not decoded

There is NO dedicated skinned-mesh extractor function. Tag 7 is handled inline by the Item visitor 0x6646980, entry 0x6646dc2 (jump table 0xF2BF2D0 index 7). The entry 0x6646dc2..0x6646e13 and the handler up to the material lookup (`0x675e440` ResourceCache::get for "CracksBlockEntity") are decoded [V] (docs/functions/item_tag7_skinned.md).

The shared tail 0x6647ff1..0x6649200 interleaves cases 2/3/7/9. It enters `sub_6648d13` (size 0x2000, ~8KB, CFG-exhaustive with a 4-entry jump table at 0x6648d7e table 0xF2BF34C) which performs the variant copy (4-way on tag byte rbp+0x180) and the registry emplace into builder-side maps. This shared function is not instruction-decoded; its variant copy + registry emplace have no [V] proof. Until decoded, the skinned extractor is not fully [V]-proven.

Confirmed first instructions of sub_6648d13 [V rdis]:
`0x6648d13  mov [rbp+0x6C8],al`, `0x6648d19  mov [rbp+0x6D0],si`, `0x6648d20  movaps xmm0,[rbp+0x740]`, `0x6648d39  movups [rbp+0x6D8],xmm0`, `0x6648d74  cmp rax,3`, `0x6648d7e  lea rcx,[0xF2BF34C]`, `0x6648d8c  jmp rdx`.

## CLOSES?

NO — single blocking fact: missing REVERSING. The skinned-mesh extraction path (Item group tag 7, entry 0x6646dc2, docs/functions/item_tag7_skinned.md) shared variant-copy/registry-emplace function `sub_6648d13` (0x6648d13..0x664ad13, size 0x2000) is not instruction-decoded; the variant copy and registry emplace after 0x6648d13 have no [V]-proof instruction lines. Every other M1d sub-item (21 thin clones, all fat clones, all constructors, item visitor + 52 cases + forwarders, chunk/batch-actor/item-in-hand/nametag/particle/sky extractors) has a D1+ dossier on disk with [V] proof.

## TOOL REQUESTS

None — used existing tools/sigs/dossier.py (already written), rdis dis, xref, and tools/sigs/verify_oc.py. All read-only static analysis.
