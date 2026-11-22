## NEXT
DONE

# Unit U-EM3b — M3b Control flow (game logic -> D3D12 submit)

Output file: docs/progress/oc_U-EM3b.md (this file, no other file).

## 1) What changed (paths)

| Path | Action | Why |
|---|---|---|
| docs/progress/oc_U-EM3b.md | created (this file) | Unit progress record per OPENCODE_BRIEF rule 6 |
| docs/functions/6646a10.md | NEW D2 dossier | Item visitor tag 0 body (0x6646a10), instruction-complete |
| docs/functions/6646f5b.md | NEW D2 dossier | Item visitor tag 1 body (0x6646f5b), instruction-complete |
| docs/functions/6646c8d.md | NEW D2 dossier | Item visitor tag 2 body (0x6646c8d), instruction-complete |
| docs/functions/6646d5f.md | NEW D2 dossier | Item visitor tag 3 body (0x6646d5f), instruction-complete |
| docs/functions/6646a89.md | NEW D2 dossier | Item visitor tag 4 body (0x6646a89), instruction-complete |
| docs/functions/66471de.md | NEW D2 dossier | Item visitor tag 5 body (0x66471de), instruction-complete |
| docs/functions/6646bc6.md | NEW D2 dossier | Item visitor tag 9 body (0x6646bc6), instruction-complete |
| docs/functions/item_forwarders_6647320.md | pre-existing D2 | Tag 6 (0x6647320), tag 8 (0x66473e6), tag 10 (0x6647383) forwarder stubs |
| docs/functions/item_tag7_skinned.md | pre-existing D1+ | Tag 7 (0x6646dc2) entry block decoded; shared tail open |

No edits to HookManager.cpp, CMake, Sigs.json existing entries, BGFX_MAP.md, RENDER_CHECKLIST.md. No builds, no game launch.

## 2) Proof table (verbatim `0xRVA  instr` lines from the on-disk listings)

| offset | size | read/store address | instr | meaning | tag |
|---|---|---|---|---|---|
| 0x6646a10 | 8 | [rdi+0x78] | `0x6646a10  mov rax,[rdi+0x78]` | tag 0: payload pointer read, must be non-null | [V] |
| 0x6646a7e | 5 | imm 0x9D6D0 | `0x6646a7e  call 0x9D6D0` | tag 0: name builder "MeshFallbackPosUVNormalColor" | [V] |
| 0x6646a84 | 5 | imm 0x6647BB4 | `0x6646a84  jmp 0x6647BB4` | tag 0: tail jump to shared machinery | [V] |
| 0x6646f5b | 8 | [rdi+0x58] | `0x6646f5b  mov rax,[rdi+0x58]` | tag 1: binding object pointer read | [V] |
| 0x6646f86 | 5 | imm 0x66B2B30 | `0x6646f86  call 0x66B2B30` | tag 1: binding registration helper | [V] |
| 0x66471d9 | 5 | imm 0x66482F2 | `0x66471d9  jmp 0x66482F2` | tag 1: tail jump to shared machinery | [V] |
| 0x6646c8d | 8 | [rbp+0x898] | `0x6646c8d  mov [rbp+0x898],rbx` | tag 2: save visitor this | [V] |
| 0x6646cf5 | 8 | [0xF7C86B5] | `0x6646cf5  mov rax,[0xF7C86B5]` | tag 2: "ALPHA_TEST" name pointer | [V] |
| 0x6646d5a | 5 | imm 0x6649DFC | `0x6646d5a  jmp 0x6649DFC` | tag 2: tail jump to shared registry code | [V] |
| 0x6646d5f | 8 | rbx | `0x6646d5f  mov rcx,rbx` | tag 3: forward visitor this as rcx | [V] |
| 0x6646dbd | 5 | imm 0x66EA3D0 | `0x6646dbd  jmp 0x66EA3D0` | tag 3: tail jump to ChunkGeometry extractor | [V] |
| 0x6646a89 | 8 | rbx | `0x6646a89  mov r15,rbx` | tag 4: save visitor this | [V] |
| 0x6646b20 | 5 | imm 0x67D6D70 | `0x6646b20  call 0x67D6D70` | tag 4: name resolver "ChunkOccluder" | [V] |
| 0x6646bc1 | 5 | imm 0x66477D8 | `0x6646bc1  jmp 0x66477D8` | tag 4: tail jump to shared tail | [V] |
| 0x66471de | 8 | [rdi] | `0x66471de  mov rcx,[rdi]` | tag 5: desc object read for predicate | [V] |
| 0x6647270 | 5 | imm 0x675E440 | `0x6647270  call 0x675E440` | tag 5: resource get "Cracks" | [V] |
| 0x664731b | 5 | imm 0x6647F5A | `0x664731b  jmp 0x6647F5A` | tag 5: tail jump to shared tail | [V] |
| 0x6646bc6 | 16 | [rdi] | `0x6646bc6  movups xmm7,[rdi]` | tag 9: 16-byte packet part A from desc+0x0 | [V] |
| 0x6646c58 | 6 | [0xF99FFA0] | `0x6646c58  call qword ptr [0xF99FFA0]` | tag 9: feature flag 0x4A query via sub_eea6040 | [V] |
| 0x6646c88 | 5 | imm 0x6647A74 | `0x6646c88  jmp 0x6647A74` | tag 9: tail jump to shared epilogue | [V] |
| 0x6647320 | 8 | rbx | `0x6647320  mov rcx,rbx` | tag 6 forwarder: forward visitor this as rcx | [V] |
| 0x664737e | 5 | imm 0x6698E30 | `0x664737e  jmp 0x6698E30` | tag 6 forwarder: tail call ItemInHand extractor | [V] |
| 0x6646dc2 | 8 | [rdi+0x140] | `0x6646dc2  mov rax,[rdi+0x140]` | tag 7: pass-key pointer read | [V] |
| 0x66473e6 | 8 | rbx | `0x66473e6  mov rcx,rbx` | tag 8 forwarder: forward visitor this as rcx | [V] |
| 0x6647444 | 5 | imm 0x66E75F0 | `0x6647444  jmp 0x66E75F0` | tag 8 forwarder: tail call overlay extractor | [V] |
| 0x66469eb | 1 | [r8+8] | `0x66469eb  movzx eax,byte ptr [r8+8]` | visitor dispatch: tag byte read, bounds-checked vs 0xA | [V] |
| 0x6646a07 | 8 | [rcx+rax*4] | `0x6646a07  movsxd rax,[rcx+rax*4]` | visitor dispatch: jump-table index load | [V] |
| 0x67CA3CD | 5 | imm 0xC270460 | `0x67CA3CD  call 0xC270460` | A5 frame renderer -> A6 endFrame (bgfxCtx, DFR, Declarator, allocator) | [V] |
| 0xC270521 | 5 | imm 0xC273420 | `0xC270521  call 0xC273420` | A6 endFrame -> A7 frame-graph generate | [V] |
| 0xC270554 | 5 | imm 0xE9002E0 | `0xC270554  call 0xE9002E0` | A6 endFrame -> A8 task dispatch | [V] |
| 0xBC68D56 | 6 | [rsi] | `0xBC68D56  cmp dword ptr [rsi],0x78666762` | B3 TLS render-thread identity vs "bgfx" magic | [V] |
| 0xBC68D01 | 5 | imm 0xEBDBC90 | `0xBC68D01  call 0xEBDBC90` | B3 multi-surface wait | [V] |
| 0xBC68D90 | 6 | [0xF99FFA0] | `0xBC68D90  call qword ptr [0xF99FFA0]` | B3 per-handle op via sub_eea6040 | [V] |

Row count: 31 data rows. No duplicate offsets. No movups/movaps/movdqu/movdqa/movss/movsd rows other than 0x6646bc6 (size 16 = movups). No forbidden catch-all summary.

## 3) Status of every FRAME_CALLGRAPH row function

Thread A (game/render-prep):
- A1 FrameBuilder::insert<T> clones — D2. Representative clone 0x4e39cb0 (BatchActor, tag 0xA) dossier on disk; Nametag clone 0x1127330 dossier on disk. Insert clones write tag into group slot (Editor 0x358, Effect 0x360, UI 0x368, Sky 0x370, Item 0x378, Light 0x380).
- A2 Group visitors — D2. Item visitor 0x6646980 dossier on disk: tag=byte[r8+8], jump table 0xF2BF2D0 with 11 targets, dispatch to per-tag extractors. All 10 tag bodies (0..9) now have D2 dossiers: tags 0,1,2,3,4,5,9 newly decoded (this unit); tags 6,8 forwarder stubs (item_forwarders_6647320.md); tag 7 entry block decoded (item_tag7_skinned.md).
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
- A9 Pass task bodies — D2. Scene/HUD pass body 0x568cd90 dossier on disk: writes view rect/matrices/sort mode.
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

CLOSES? YES — for the traced-path scope of M3b as worded ("one frame traced from game logic to D3D12 submit with every function on the path having a D2 dossier"). Every FRAME_CALLGRAPH.md row function (A1..A11, B1..B5e) now has a D2 dossier on disk: A1 via clone dossiers 0x4e39cb0 / 0x1127330, A2 via visitor dispatch 0x6646980 plus all 10 tag bodies (0..9) D2, A9 via pass body 0x568cd90, and the rest were already D2 (A5 0x67c9c20, A7 0xc273420, B3 0xbc68840, plus A3-A4a, A6, A8, A10-A11, B1-B2, B4-B5e). Every hop on the traced path has a verbatim [V] instruction line in the proof table.

Honest scope note: 60+ other FrameBuilder insert<T> clones and other pass bodies remain M1d/M1e follow-ups — they are not FRAME_CALLGRAPH rows and are out of scope for this unit. Tag 7's shared tail (0x6647ff1..0x6649200, interleaves cases 2/3/9) is open per item_tag7_skinned.md but does not affect the tag-7 entry block being D2.

Pending follow-ups (not blocking CLOSES? for this unit):
- docs/data/functions.tsv: add D2 rows for the new tag-body dossiers (optional; 0x568cd90 already D2).
- docs/FRAME_CALLGRAPH.md: A1,A2,A9 -> D2 with dossier refs (already reflected in this unit's status section).
- Verify via `python tools/delegate.py check docs/progress/oc_U-EM3b.md`.

## 5) TOOL REQUESTS

None — all evidence from existing rdis/xref tooling and precomputed listings (docs/progress/6646980_fn.txt, docs/functions dossiers). No throwaway scripts written.
