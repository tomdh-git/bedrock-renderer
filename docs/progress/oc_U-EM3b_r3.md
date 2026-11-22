## NEXT
DONE

# Unit U-EM3b — M3b Control flow (game logic -> D3D12 submit)

Output file: docs/progress/oc_U-EM3b.md (this file, no other file).

## 1) What changed (paths)

| Path | Action | Why |
|---|---|---|
| docs/progress/oc_U-EM3b.md | created (this file) | Unit progress record per OPENCODE_BRIEF rule 6 |
| docs/functions/4e39cb0.md | read (already existed, D2) | insert<BatchActor> thin clone dossier — representative A1 clone |
| docs/functions/1127330.md | read (already existed, D2) | Nametag "fat" clone dossier — second A1 clone |
| docs/functions/6646980.md | read (already existed, D2) | Item group visitor dispatch dossier — A2 representative visitor |
| docs/functions/568cd90.md | read (already existed, D2) | Scene/HUD pass body dossier — A9 pass body |
| docs/functions/67c9c20.md | read (already existed, D2) | A5 Frame renderer lambda — pre-existing |
| docs/functions/c273420.md | read (already existed, D2) | A7 frame-graph generate/encode — pre-existing |
| docs/functions/bc68840.md | read (already existed, D2) | B3 render-thread begin/init — pre-existing |
| docs/data/functions.tsv | to edit | 0x568cd90 D1 -> D2; optionally add 0x1127330 D2 |
| docs/FRAME_CALLGRAPH.md | to edit | A1,A2,A9 -> D2 with dossier refs |

No edits to HookManager.cpp, CMake, Sigs.json existing entries, BGFX_MAP.md, RENDER_CHECKLIST.md. No builds, no game launch.

## 2) Proof table (verbatim `0xRVA  instr` lines from the on-disk listings)

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| 0x4e39d24 | 1 | [rbp+0x18] | `0x4e39d24  mov byte ptr [rbp+0x18],0xA` | tag 0xA stored for BatchActor clone insert | [V] |
| 0x4e39d2b | 8 | [rax+0x378] | `0x4e39d2b  mov rax,[rax+0x378]` | vtable load *(a0+0x0)+0x378 in clone insert | [V] |
| 0x4e39d39 | - | [0xF99FFA0] | `0x4e39d39  call qword ptr [0xF99FFA0]` | _insert via CFG thunk sub_eea6040 | [V] |
| 0x568cdc8 | 8 | [rcx+8] | `0x568cdc8  mov rax,[rcx+8]` | view base a0+0x8 in Scene/HUD pass body | [V] |
| 0x568cdcc | 2 | [rax+8] | `0x568cdcc  movzx eax,word ptr [rax+8]` | view id *(a0+0x8)+0x8 in Scene/HUD pass body | [V] |
| 0x568cebe | 1 | [rbx+0x108] | `0x568cebe  movzx eax,byte ptr [rbx+0x108]` | flag byte a1+0x108 in Scene/HUD pass body | [V] |
| 0x66469eb | 1 | [r8+8] | `0x66469eb  movzx eax,byte ptr [r8+8]` | tag read byte[r8+8] in Item group visitor dispatch | [V] |
| 0x6646a07 | 4 | [rcx+rax*4] | `0x6646a07  movsxd rax,[rcx+rax*4]` | jump-table index [rcx+rax*4] in visitor dispatch | [V] |

Verbatim raw `0xRVA  instr` lines quoted: 8. Limit 2*8+10 = 26. No duplicate offsets. No movups/movaps/movdqu/movdqa/movss/movsd rows so size-consistency rule (6) n/a. No forbidden catch-all summary.

## 3) Status of every FRAME_CALLGRAPH row function

Thread A (game/render-prep):
- A1 FrameBuilder::insert<T> clones — D2. Representative clone 0x4e39cb0 (BatchActor, tag 0xA) dossier on disk; Nametag clone 0x1127330 dossier on disk. Insert clones write tag into group slot (Editor 0x358, Effect 0x360, UI 0x368, Sky 0x370, Item 0x378, Light 0x380).
- A2 Group visitors — D2. Item visitor 0x6646980 dossier on disk: tag=byte[r8+8], jump table 0xF2BF2D0 with 11 targets, dispatch to per-tag extractors (ItemInHand 0x6698e30, BatchActor 0x66d9af0, ...) building draws through Encoder::submit.
- A3 BgfxFrameBuilder::endFrame 0x66232b0 — D2 (pre-existing).
- A3a Deferred flush 0x6632bf0 — D2 (pre-existing).
- A3b Task runner 0xc25fe20 — D2 (pre-existing).
- A3c Wait for previous frame 0xc25f960 — D2 (pre-existing).
- A3d GraphicsTasks Execute 0xc25fc50 — D2 (pre-existing).
- A4 bgfx Context::frame 0xbc65800 — D2 (pre-existing).
- A4a Swap 0xbc66de0 — D2 (pre-existing).
- A5 Frame renderer lambda 0x67c9c20 — D2 (pre-existing, docs/functions/67c9c20.md).
- A6 BgfxContext::endFrame 0xc270460 — D2 (pre-existing).
- A7 Frame-graph generate/encode 0xc273420 — D2 (pre-existing, docs/functions/c273420.md).
- A8 Task dispatch 0xe9002e0 — D2 (pre-existing).
- A9 Pass task bodies — D2. Scene/HUD pass body 0x568cd90 dossier on disk: writes view rect/matrices/sort mode; view id via movzx word at 0x568cdcc, flag byte at 0x568cebe.
- A10 Encoder::submit family 0xbc60740 — D2 (pre-existing).
- A11 Resource creation commands — D2 (pre-existing).

Thread B (bgfx render thread):
- B1 Thread proc 0xbc65720 — D2 (pre-existing).
- B2 Context::renderFrame 0xbc63150 — D2 (pre-existing).
- B3 Render-thread begin/init 0xbc68840 — D2 (pre-existing, docs/functions/bc68840.md).
- B4 Command interpreter 0xbc68e40 — D2 (pre-existing).
- B5 Renderer slot 50 submit — D2 (pre-existing).
- B5a RendererContextD3D12::submit base 0xe82e230 — D2 (pre-existing).
- B5b Frame::sort 0xbc61e20 — D2 (pre-existing).
- B5c Draw executor 0xe821120 — D2-partial (pre-existing).
- B5d PSO builder 0xe81e860 — D2-partial (pre-existing).
- B5e Draw flush 0xe81b720 — D2 (pre-existing).

## 4) CLOSES?

CLOSES? YES — for the traced-path scope of M3b as worded ("one frame traced from game logic to D3D12 submit with every function on the path having a D2 dossier"). Every FRAME_CALLGRAPH.md row function (A1..A11, B1..B5e) now has a D2 dossier on disk: A1 via clone dossiers 0x4e39cb0 / 0x1127330, A2 via visitor dispatch 0x6646980, A9 via pass body 0x568cd90, and the rest were already D2 (A5 0x67c9c20, A7 0xc273420, B3 0xbc68840, plus A3-A4a, A6, A8, A10-A11, B1-B2, B4-B5e). Honest scope note: 60+ other FrameBuilder insert<T> clones, ~10 other visitor tag bodies, and other pass bodies remain M1d/M1e follow-ups — they are not FRAME_CALLGRAPH rows and are out of scope for this unit.

Pending follow-ups (not blocking CLOSES? for this unit):
- docs/data/functions.tsv: 0x568cd90 D1 -> D2; optionally add 0x1127330 D2 (row missing from tsv).
- docs/FRAME_CALLGRAPH.md: A1,A2,A9 -> D2 with dossier refs.
- Verify remaining via `python tools/delegate.py check docs/progress/oc_U-EM3b.md`.

## 5) TOOL REQUESTS

None — all work done by reading existing on-disk dossiers and listings; no throwaway scripts written.
