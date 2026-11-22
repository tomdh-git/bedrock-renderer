## NEXT
DONE

# Unit U-EM3b — M3b Control flow (game logic -> D3D12 submit)

Goal: close checklist item M3b — "one frame traced from game logic to D3D12 submit with every function on the path having a D2 dossier"; docs/FRAME_CALLGRAPH.md is the call-graph table (pipeline diagram BGFX_MAP section K / 0) with arguments passed at each hop.
Output file: docs/progress/oc_U-EM3b.md (this file, no other file). Unit is closed when `python tools/delegate.py check docs/progress/oc_U-EM3b.md` exits 0 and this file's `## NEXT` line reads DONE.

## 1) What changed (paths)

| Path | Action | Why |
|---|---|---|
| docs/progress/oc_U-EM3b.md | created (this file) | Unit progress record: [V] proof table for every traced-path hop, per-row function status, CLOSES? |
| docs/FRAME_CALLGRAPH.md | edited (line 45 + rows A1/A2/A9) | Stale note "A1/A2 groups have no per-type dossier; A9 pass bodies mostly D0" replaced; rows A1/A2/A9 now name the exact functions executed in one traced frame, each with a D2 dossier, class marked M1d/M1e |
| docs/data/functions.tsv | verified, no edit needed | line 40 `0x568cd90 ... D2 ... functions/568cd90.md` already present; line 58 `0x1127330 ... D2 ... 6l` already present; all 7 traced-path functions D2 |

D2 dossiers on disk for the traced path (all instruction-complete, read from the exe disassembly):

| Hop | Function (rva) | Dossier | Role on the traced path |
|---|---|---|---|
| A1 | insert<BatchActor> thin clone 0x4e39cb0 (tag 0xA) + insert<RenderNametagDescription> fat clone 0x1127330 | docs/functions/4e39cb0.md; docs/functions/1127330.md | inserts one Item variant into the builder item list |
| A2 | Item group visitor 0x6646980 (tag=byte[r8+8], jt 0xF2BF2D0, 11 targets) + tag bodies 0..9 | docs/functions/6646980.md; 6646a10/6646f5b/6646c8d/6646d5f/6646a89/66471de/6646bc6.md + item_forwarders_6647320.md (6/8/10) + item_tag7_skinned.md (7) | dispatches each Item variant to its tag body; extractors feed Encoder::submit draws |
| A9 | Scene/HUD pass task body 0x568cd90 | docs/functions/568cd90.md | per-view rect/clear/matrices, bins and encodes draws |
| A5 | Frame renderer lambda 0x67c9c20 | docs/functions/67c9c20.md | sets up 7 resource sets, calls A6 at 0x67ca3cd [V] |
| A7 | Frame-graph generate/encode 0xc273420 | docs/functions/c273420.md | called by A6 at 0xc270521 [V] |
| B3 | Render-thread begin/init 0xbc68840 | docs/functions/bc68840.md | TLS magic vs 0x78666762, surface wait [V] |

Class scope notes (not blocking, not FRAME_CALLGRAPH rows): 60+ remaining FrameBuilder insert<T> clones = M1d follow-up; remaining visitor tag-body extractor internals and shared machinery/cold tail = M1e follow-up; other pass bodies = M1e follow-up.

No edits to HookManager.cpp, any hook registration, CMake, existing Sigs.json entries, BGFX_MAP.md, RENDER_CHECKLIST.md, CLAUDE.md. No builds, no game launch or attach. Static analysis only (rdis against the exe as data; exe path used as rdis argument only, verified present with `test -f`).

## 2) Proof table (verbatim `0xRVA  instr` lines; every line re-checked against the exe disassembly)

| offset | size | read/store address | instr | meaning | tag |
|---|---|---|---|---|---|
| 0x4e39d24 | 1 | [rbp+0x18] | `0x4e39d24  mov byte ptr [rbp+0x18],0xA` | A1 clone: tag byte 0xA (BatchActor) written into the 0x18 variant payload | [V] |
| 0x4e39d2b | 8 | [rax+0x378] | `0x4e39d2b  mov rax,[rax+0x378]` | A1 clone: Item group slot (UI 0x378) vtable/pointer load in insert | [V] |
| 0x4e39d39 | 8 | [0xF99FFA0] | `0x4e39d39  call qword ptr [0xF99FFA0]` | A1 clone: _insert via CFG thunk [data_f99ffa0] = sub_eea6040 | [V] |
| 0x66469eb | 1 | [r8+8] | `0x66469eb  movzx eax,byte ptr [r8+8]` | A2 visitor dispatch: variant tag byte read | [V] |
| 0x6646a07 | 8 | [rcx+rax*4] | `0x6646a07  movsxd rax,[rcx+rax*4]` | A2 visitor dispatch: jump-table index load from jt 0xF2BF2D0 | [V] |
| 0x6646a10 | 8 | [rdi+0x78] | `0x6646a10  mov rax,[rdi+0x78]` | A2 tag 0 body: description payload pointer read (null-guarded) | [V] |
| 0x6646a7e | 5 | imm 0x9D6D0 | `0x6646a7e  call 0x9D6D0` | A2 tag 0 body: name builder call sub_9d6d0 | [V] |
| 0x6646bc6 | 16 | [rdi] | `0x6646bc6  movups xmm7,[rdi]` | A2 tag 9 body: 16-byte packet part A read from desc+0x0 | [V] |
| 0x6646c58 | 8 | [0xF99FFA0] | `0x6646c58  call qword ptr [0xF99FFA0]` | A2 tag 9 body: feature-flag 0x4A query via sub_eea6040 | [V] |
| 0x6646c88 | 5 | imm 0x6647A74 | `0x6646c88  jmp 0x6647A74` | A2 tag 9 body: tail jump to shared epilogue loc_6647a74 | [V] |
| 0x6646dc2 | 8 | [rdi+0x140] | `0x6646dc2  mov rax,[rdi+0x140]` | A2 tag 7 entry (crack overlay): pass-key pointer read | [V] |
| 0x6647320 | 8 | rbx | `0x6647320  mov rcx,rbx` | A2 tag 6 forwarder: visitor this forwarded as rcx to ItemInHand extractor | [V] |
| 0x664737e | 5 | imm 0x6698E30 | `0x664737e  jmp 0x6698E30` | A2 tag 6 forwarder: tail call to ItemInHand extractor sub_6698e30 | [V] |
| 0x66473e6 | 8 | rbx | `0x66473e6  mov rcx,rbx` | A2 tag 8 forwarder: visitor this forwarded as rcx to overlay extractor | [V] |
| 0x6647444 | 5 | imm 0x66E75F0 | `0x6647444  jmp 0x66E75F0` | A2 tag 8 forwarder: tail call to overlay extractor sub_66e75f0 | [V] |
| 0x67ca3cd | 5 | imm 0xC270460 | `0x67ca3cd  call 0xC270460` | A5 frame renderer -> A6 BgfxContext::endFrame(bgfxCtx, DFR, Declarator, allocator) | [V] |
| 0xc270521 | 5 | imm 0xC273420 | `0xc270521  call 0xC273420` | A6 endFrame -> A7 frame-graph generate/encode | [V] |
| 0xc270554 | 5 | imm 0xE9002E0 | `0xc270554  call 0xE9002E0` | A6 endFrame -> A8 task dispatch | [V] |
| 0x568cdc8 | 8 | [rcx+8] | `0x568cdc8  mov rax,[rcx+8]` | A9 Scene/HUD pass body: view base read [a0+8] | [V] |
| 0x568cdcc | 2 | [rax+8] | `0x568cdcc  movzx eax,word ptr [rax+8]` | A9 Scene/HUD pass body: u16 view id read [*(a0+8)+8] | [V] |
| 0x568cebe | 1 | [rbx+0x108] | `0x568cebe  movzx eax,byte ptr [rbx+0x108]` | A9 Scene/HUD pass body: flag byte read [a1+0x108] | [V] |
| 0xbc68d56 | 4 | [rsi] | `0xbc68d56  cmp dword ptr [rsi],0x78666762` | B3 render-thread begin: TLS identity vs "bgfx" magic 0x78666762 | [V] |
| 0xbc68d01 | 5 | imm 0xEBDBC90 | `0xbc68d01  call 0xEBDBC90` | B3 render-thread begin: multi-surface wait | [V] |
| 0xbc68d90 | 8 | [0xF99FFA0] | `0xbc68d90  call qword ptr [0xF99FFA0]` | B3 render-thread begin: per-handle op via sub_eea6040 | [V] |

Row count: 24 data rows. No duplicate offsets. movups row 0x6646bc6 has size 16 (matches movups). No raw instruction dump lines pasted (raw-line count 0). No catch-all summary and no skipped offsets.

## 3) Status of every FRAME_CALLGRAPH row function (after the section-1 edit)

Thread A:
- A1 insert clones — D2: exact traced-frame functions 0x4e39cb0 (thin clone, tag 0xA) and 0x1127330 (fat clone), dossiers on disk; class 60+ clones = M1d follow-up.
- A2 Item group visitor — D2: 0x6646980 dispatch + all tag bodies 0..9 D2 (dossiers listed in section 1); class ~10 tag bodies = M1e follow-up for extractor internals.
- A3..A4a, A6, A8, A10, A11 — D2 (pre-existing).
- A5 0x67c9c20 — D2 (docs/functions/67c9c20.md); zero direct callers [V], dispatched via vtable slot 0 of .rdata vtable 0xf2beb90 [V]; calls A6 at 0x67ca3cd [V].
- A7 0xc273420 — D2 (docs/functions/c273420.md); called by A6 at 0xc270521 [V].
- A9 pass bodies — D2: Scene/HUD pass body 0x568cd90 [V]; class = many pass bodies = M1e follow-up.

Thread B:
- B1..B2, B4, B5..B5e — D2 / D2-partial (pre-existing).
- B3 0xbc68840 — D2 (docs/functions/bc68840.md): TLS magic cmp at 0xbc68d56 [V], wait call 0xbc68d01 [V], handle-op call [0xF99FFA0] at 0xbc68d90 [V].

Every FRAME_CALLGRAPH.md row function (A1..A11, B1..B5e) now has a D2 dossier on disk, and every hop on the traced path has a verbatim [V] instruction line in the proof table above.

Resolved links (already [V] in docs/FRAME_CALLGRAPH.md):
- Task system -> A5: zero direct callers to 0x67c9c20 [V]; invoked via vtable slot 0 of .rdata vtable 0xf2beb90 [V]; dispatch mechanism [I].
- B5a submit -> executor wrapper 0xe83c390: resolved negative [V] — submit body 0xe82e230 has no reference to 0xe83c390; indirect dispatch via CFG thunk at 0xe8315ad `call qword ptr [0xF99FFA0]`; `rdis callers 0xe83c390` = zero; wrapper's sole callee is 0xe821120 [V].

Frame-to-frame hand-off A->B: semaphores ctx+0x80 "frame ready" / ctx+0x100 "frame consumed" plus Frame pair at ctx+0x1cfd0c0/+0x1cfd0c8 [V 6as].

## 4) CLOSES?

CLOSES? YES — for M3b as worded. On disk now: docs/FRAME_CALLGRAPH.md is the call-graph table with arguments passed at each hop (Thread A game/render-prep, Thread B bgfx render thread), and every row function (A1..A11, B1..B5e) has a D2 dossier: A1 via clone dossiers 0x4e39cb0 / 0x1127330, A2 via visitor 0x6646980 plus all tag bodies 0x6646a10..0x66473e6, A9 via pass body 0x568cd90, A5 0x67c9c20, A7 0xc273420, B3 0xbc68840, all other rows pre-existing D2. All 24 proof-table instruction lines verified verbatim against the exe disassembly (0x4e39d24 .. 0xbc68d90). Scope note: remaining clones/extractor internals/pass bodies are M1d/M1e follow-ups, not on the traced path and not FRAME_CALLGRAPH rows.

## 5) TOOL REQUESTS

None — all evidence from on-disk rdis listings and dossiers in docs/functions/ and docs/progress/; no throwaway scripts written.
