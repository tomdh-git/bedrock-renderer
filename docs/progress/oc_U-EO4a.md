# Unit U-EO4a — behaviour notes for M1d/M1e structural functions

## What was missing
O4a (RENDER_CHECKLIST.md:525): behaviour notes without RVAs for every structural function in docs/BEHAVIOR_NOTES.md so they survive re-mapping; not yet written for M1d/M1e items — M4b. M4b (RENDER_CHECKLIST.md:462) is [x] but covers only structural functions that have a D2 dossier. BEHAVIOR_NOTES.md's M1d/M1e section already covered thin insert clones (21, one template), group insert wrappers (6), group visitors (6), Item visitor 0x6646980, extractors (ItemInHand, BatchActor, chunk geometry, skinned mesh, nametag, clouds, particle, weather) and pass lambdas — but lacked per-function behaviour notes for these D2-dossiered M1d/M1e fat clones/constructors:

- PlayerVision 0x53e62b0 (Effect tag 3)
- Shadow blob-shadow emitter 0x53e6c30
- MeshFallback clone 0x4def480 + description ctor 0x668b850 (Item tag 2)
- Crack clone 0x539fff0 (Item tag 5)
- shared text clone 0xe71330 + ctors 0x668b400 (EnvironmentalText, 0xE8 bytes) / 0x668c750 (UIText, 0x60 bytes) (Item tag 0 / UI tag 3)
- BlockSelectionOverlay clone 0x539b7c0 + ctor 0x668d990 (Item tag 8)
- Sky clone 0x5369b30 + Sky ctor 0x668c910 (0xB0-byte RenderSkyDescription)
- shared helpers 0x4def080 / 0x4dfb570 / 0x5aba5c0

Functions without dossiers (FlameBillboard, Gameface, Editor block-volume extractors) cannot get notes yet; that is an M1d dossier gap tracked in R14, not part of this item.

## What changed
- docs/BEHAVIOR_NOTES.md: appended eleven RVA-free behaviour paragraphs to the M1d/M1e section, FrameBuilder clones and visitors (L4) subsection, after the Item visitor paragraph and before the Extractors subsection. One paragraph per structural function above; every claim tagged [V] (verified in disassembly) / [I] (instruction-decoded dossier fact) / mixed. RVAs appear only as [0x..] index tags; no RVAs appear in prose.
- docs/progress/oc_U-EO4a.md: this note.

## Proof table (verbatim 0xRVA  instr lines from the exe, checked by verify_oc)
| offset | size | site | instr | meaning | tag |
|--------|------|------|-------|---------|-----|
| 0x53e62fc | 8 | [rcx+8] | `0x53e62fc  mov r13,[rcx+8]` | PlayerVision clone reads ctx->player | [V] |
| 0x53e6300 | - | - | `0x53e6300  lea rbx,[0x128C4FD0]` | PlayerVision clone loads global frame-builder ref | [V] |
| 0x53e6c5d | 8 | [rcx+0x10] | `0x53e6c5d  mov r13,[rcx+0x10]` | Shadow emitter reads shadow-state ptr | [V] |
| 0x4def4c0 | - | - | `0x4def4c0  call 0x4DEF080` | MeshFallback clone: shouldRender gate | [V] |
| 0x4def4d9 | 8 | *(a2+0x0)+0x40 | `0x4def4d9  cmp qword ptr [rax+0x40],0` | material null check | [V] |
| 0x668b8a3 | 8 | a0+0x0 | `0x668b8a3  mov [rsi],r8` | MeshFallback ctor stores out->mMesh | [V] |
| 0x668b8b1 | 4 | a3+0x0 | `0x668b8b1  movss xmm0,[r9]` | camera matrix row 0 copy (movss = 4 bytes) | [V] |
| 0x53a0031 | 8 | a1+0x28 | `0x53a0031  mov r14,[rdx+0x28]` | Crack clone reads extract context | [V] |
| 0x53a00c3 | - | rbx+0x3280 | `0x53a00c3  mov r12,[rbx+0x3280]` | crack entry vector load | [V] |
| 0xe7138b | 4 | *(a1+0x98)+0x8 | `0xe7138b  lock inc dword ptr [rcx+8]` | text clone: font/texture refcount +1 | [V] |
| 0x668b446 | 8 | a0+0x0 | `0x668b446  mov [rcx],rdx` | EnvironmentalText ctor: out->mSource | [V] |
| 0x668b450 | - | - | `0x668b450  call 0x4DFB570` | font texture conversion | [V] |
| 0x668c7c1 | 1 | a0+0x58 | `0x668c7c1  mov byte ptr [rsi+0x58],0xFF` | UIText ctor: variant index = 0xFF | [V] |
| 0x668c7a6 | - | - | `0x668c7a6  call 0x4DFB570` | font texture conversion | [V] |
| 0x539b81c | - | - | `0x539b81c  call qword ptr [0xF99FFA0]` | BlockSelectionOverlay clone CFG-thunk dispatch | [V] |
| 0x539b805 | 8 | *(a1+0x28)+0xB0 | `0x539b805  mov r12,[r14+0xB0]` | overlay context +0xB0 load | [V] |
| 0x668d9c6 | 4 | a1+0x0 | `0x668d9c6  movss xmm0,[rdx]` | BlockSelectionOverlay ctor matrix row 0 (movss = 4 bytes) | [V] |
| 0x5369bbd | - | - | `0x5369bbd  lea r13,[0x128C4FD0]` | Sky clone global ref load | [V] |
| 0x668c938 | 8 | a1+0x0 | `0x668c938  mov rax,[rdx]` | Sky ctor: out->mSource = *src | [V] |
| 0x668c945 | - | - | `0x668c945  lea rax,[0x129C1210]` | default sky texture fallback | [V] |

## CLOSES?
CLOSES?: YES — one behaviour paragraph per M1d/M1e structural function that has a D2 dossier (surviving exceptions: FlameBillboard/Gameface/Editor block-volume extractors, which have no dossiers yet; M1d gap tracked in R14). All 20 proof rows verified against the exe by verify_oc (mismatch=0, no-such-instr=0).

## NEXT
DONE
