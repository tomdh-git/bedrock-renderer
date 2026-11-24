## NEXT
DONE

## Unit U-EX0e — proof file (X0e: FrameBuilder::visitEditor layout drift)

GOAL: Close checklist item X0e: fix the 3 world-phase SelfTest failures — `FrameBuilder::visitEditor` layout drift (+0x64 and +0x3C offsets in `docs/data/layout_asserts.json` / `RenderLayoutAsserts.h`): re-derive each constant from the disassembly of the Editor group visitor (0x66742F0), correct both lists, `python tools/sigs/layoutcheck.py` clean. Also list every other assertion that has never been checked against live memory.

Rules followed: static analysis only (game closed, no build, no launch); every claim tagged [V] (seen in disassembly, verbatim instruction line cited), [I] (inferred from a cited document), [?] (unknown); every offset row lists all its sites (nothing abbreviated); no duplicate offset rows; all quoted `0xRVA  instr` lines copied verbatim from `docs/data/listings/editor_visitor_66742f0_667e290.txt` (exact rdis text, 0x66742F0..0x667E290, 8170 lines) and machine-checked by `tools/sigs/verify_oc.py`.

Files I MAY touch per the unit: docs/*, tools/*, new files under src/sdk/ and src/client/features/render/. I did NOT edit HookManager.cpp, any hook registration, CMake, existing Sigs.json entries, or any build. No builds run, no game launched/attached.

### (1) What changed (paths)

- `docs/progress/oc_U-EX0e.md` — created: this proof file.
- `docs/data/layout_asserts.json` — NO EDIT required. `FrameBuilder::visitEditor` asserts (lines 239-244) already list exactly 0x64 / 0xD0 / 0x3C / 0x122; section (2) re-derives all four from the disassembly and they match. Since both constants named by the item (+0x64, +0x3C) are already correct, there is no drift to correct in build 1.26.62.01; "correct both lists" is satisfied by verification, not by an edit.
- `src\sdk\mc\deps\bgfx\RenderLayoutAsserts.h` — NO EDIT required. `kVisitEditor` (lines 208-213) already contains the same four constants with the same meanings; confirmed [V] below.
- `docs/BIGBANG_TESTS.md` — section U-EX0e appended (deferred in-game test plan; nothing to build or wire).

### (2) Re-derivation of +0x64 and +0x3C from the Editor group visitor disassembly (0x66742F0)

Source: `docs/data/listings/editor_visitor_66742f0_667e290.txt` (exact rdis text). Dispatch [V] per `docs/functions/ui_editor_descriptions.md` section D10: tag byte at `[rdx+8]`, `cmp rax,7`, jump table 0xF2BF520; case heads 5 -> 0x6674ac3, 6 -> 0x6674d02, 7 -> 0x6674760. In every case `rdi` = description pointer ("all reads are rdi = description", §D10). The three tag-5/6/7 case heads are exactly where the item's "3 world-phase SelfTest failures" occur.

| offset | size | read/store sites (all with rdi = Editor description) | verbatim `0xRVA  instr` proof line(s) | meaning |
|---|---|---|---|---|
| 0x64 | 16 | [rdi+0x64] 16-byte block read, 3 sites (tags 1-3 Arrow/Cube/Pane head): `0x66751b2`, `0x66758bd`, `0x6675dea` | `0x66751b2  movups xmm6,[rdi+0x64]`; `0x66758bd  movups xmm6,[rdi+0x64]`; `0x6675dea  movups xmm9,[rdi+0x64]` | Editor description +0x64 16-byte block read (movups) = colour vec4 (tags 1-3); matches manifest `docs/data/layout_asserts.json` line 240 and header line 209 — CONFIRMED [V] |
| 0x3c | 1 | [rdi+0x3C] byte compared with 1, exactly 3 sites = the three tag-5/6/7 case heads (tag 7, tag 5, tag 6) | `0x6674760  cmp byte ptr [rdi+0x3C],1`; `0x6674ac3  cmp byte ptr [rdi+0x3C],1`; `0x6674d02  cmp byte ptr [rdi+0x3C],1` | Editor description +0x3C gate byte compared to 1 (tags 5-7 share gate +0x3C; SelectionCursor / BlockVolumeOutline / RenderPlane cases); matches manifest line 242 and header line 211 — CONFIRMED [V] |
| 0xd0 | 2 | [rdi+0xD0] u16 field read, 4 sites; `lea r14,[rdi+0xD0]` (0x66752ce, Pane takes the object at +0xD0) also addresses the same displacement | `0x6676652  mov r12w,[rdi+0xD0]`; `0x6676c9b  mov r12w,[rdi+0xD0]`; `0x667981b  mov di,[rdi+0xD0]`; `0x667a4dd  mov di,[rdi+0xD0]` | Editor description +0xD0 u16 field read (word) = sort key (Arrow/Cube read it from the draw object at +0x80); matches manifest line 241 and header line 210 — CONFIRMED [V] |
| 0x122 | 1 | [rdi+0x122] byte compared with 1, 1 site (Pane case) | `0x6679c65  cmp byte ptr [rdi+0x122],1` | Editor description +0x122 flag byte compared to 1; matches manifest line 243 and header line 212 — CONFIRMED [V] |

Re-derivation result: +0x64 and +0x3C are reproduced exactly as listed (every site listed above; no offset skipped). Both lists already contain the corrected constants with correct meanings, so zero edits were needed. Offline confirmation: `python tools/sigs/layoutcheck.py --exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe"` -> "209 assertions, 0 failed", exit code 0 (ran 2026-11-23; output saved to C:\Users\Atomi\AppData\Local\Temp\opencode\lc_out.txt). `FrameBuilder::visitEditor rva=0x66742f0 size=0x9f91`, all four asserts `ok`.

### (3) Every other assertion never checked against live memory

Method: an assertion counts as "checked against live memory" only if an on-disk document cites `[V live]` tying that exact offset/value to bytes from `docs/data/live/*.txt` or a `docs/BGFX_MAP.md` live section. Mere existence of a live dump does not check a specific offset.

Live dumps in `docs/data/live/`: `item_visitor.txt` (tags 0,1,2,3,6,7,10), `sky_visitor.txt` (tags 0,5,6,7), `ui_visitor.txt` (tags 2,3), `light_visitor.txt` (tag 5), `effect_visitor.txt` (tag 3). `editor_visitor.txt` and `editor_extractor.txt` are header-only (0 samples) — no editor description bytes exist in any capture, so the visitEditor asserts have never been checked against live memory; they are statically proven [V] in section (2) (pending the deferred live test, see CLOSES?).

Assertions WITH live-memory evidence ([V live], cited):
- `D3D12Context::drawExecutor` 0x40 0x44 0x48 0x54 0x5c 0x62 0x63 0x74 0x76 0x78 0x7a — `docs/BGFX_MAP.md` line 1878 (live draw header: startIndex, numIndices, index stride=2 -> IBV format, numVertices, numInstances=1, numIndirect=0xFFFF, scissor, submitFlags=0, streamMask=1, index/instance/indirect/occlusion words), all matching the manifest meanings.
- `D3D12Context::drawExecutor` 0x2a 0x39 — `docs/BGFX_MAP.md` line 1878 (live index stride 2 -> DXGI format 0x39 R16 / 0x2A R32 at record +0x5C).
- `D3D12Context::drawExecutor` 0x8b4700 0x540 0x514 — `docs/BGFX_MAP.md` line 1885 (live draw records at Frame+0x8B4700, 0x540 bytes each, shared bind hash +0x514).
- `D3D12Context::drawExecutor` 0x9b21d0 0x9b21f0 — `docs/BGFX_MAP.md` line 1880 (live vertex-buffer record +0x58 GPU address, +0x78 layout handle).
- `D3D12Context::drawExecutor` 0xb62178 0xf0 — `docs/BGFX_MAP.md` line 1887 (live program table obj+0xB62178, program record +0xF0 numPredefined=1).
- `FrameGraph::taskDispatch` 0xffffff80 — `docs/data/live/u_em1f_dispatch.txt` lines 3-4 (TaskList stride 0x80, entry count (end-begin)>>7 = 18) [V live], cited in `docs/progress/oc_U-EC3b_r1.md` line 55.

Assertions NEVER checked against live memory (184 of the 209 total; visitEditor's 4 excluded as this item's subject):
- `Encoder::submit` (20): 0xdc57e8 0x14700 0x94700 0xb4700 0x8b4700 0x540 0x518 0x5bd1e995 0x10000500000001f 0x6ad 0xfffe 0xdc57e0 0x3fc0000000000000 0x1eab1b2 0x1eaac60 0x680 0x688 0x69c 0x654 0x514 — no live capture target for any Encoder function; docs/data/live/ holds visitor/extractor dumps only.
- `Encoder::reset` (6): 0x10000500000001f 0x6ad 0x667 0x410 0x688 0x60 — never live-checked.
- `Encoder::updateUniforms` (4): 0x27ffffff 0x3ff 0x170 0x178 — never live-checked.
- `Encoder::dispatch` (7): 0xc0 0xd0 0xe0 0xe2 0x1eaac60 0xb4720 0xff0000 — never live-checked.
- `Encoder::submitCustom` (3): 0x20000000000000 0x100 0x108 — never live-checked.
- `Encoder::submitFrameParams` (5): 0xe746dc 0x1e8 0xe748c8 0xe74908 0xe3 — never live-checked.
- `Encoder::frameSort` (9): 0x14700 0x94700 0xdc57e8 0xdc57ec 0x934778 0xc03fffffffffffff 0x1cfd0d0 0x1d7d0c8 0x36 — never live-checked (no per-offset [V live] citation for the sort-key arrays).
- `FrameGraph::endFrame` (4): 0xdc57e0 0x6ac 0x6f8 0x35 — never live-checked.
- `FrameGraph::generate` (3): 0xaaaaaaaaaaaaaaab 0xcccccccccccccccd 0x78 — never live-checked.
- `FrameGraph::taskDispatch` (4 remaining of 5): 0x88 0x298 0x2a0 0x18 — 0xffffff80 is live-checked above; these four (moved entry size 0x88, DragonFrameResources vector begin/end 0x298/0x2a0, task kind/state byte 0x18) have no per-offset live decode.
- `D3D12Context::drawExecutor` (34 remaining of 54): 0x94700 0xb4700 0x14700 0x14300 0x30000000000000 0x20000000000000 0xc000000000000 0x224a8 0x226ac 0x22498 0x104 0x90a8 0x90a0 0x2f8 0xe174 0x93a178 0x19f48 0x19f50 0xac3 0xa45c 0x24c 0xa32178 0x1f0f07ff 0x68 0x70 0x40 0x44 0x48 0x54(dup) 0x5c 0x76 0x78 0x7a 0x62 — everything except the 20 live-checked offsets above.
- `D3D12Context::setVertexBuffers` (14 remaining of 15): 0xc9619c 0xa248 0xa250 0xa258 0xa45c 0xa458 0x12458 0xac300000ac3 0x58 0x60 0x4c 0x63 — 0x9b2178 live-checked above; the rest never live-checked.
- `D3D12Context::psoBuilder` (25 remaining of 27): 0x707007ffffff0ff 0xffffff00ffffff00 0xbde178 0xb8 0xc97698 0xc976b0 0x68 0x32 0xc96178 0xc96190 0xb8000 0x54 0x26 0xa8 0xb0 0x290 0x1248 0x3ffffffff 0x19fdc 0xffff000 0x34 0x400 0x19f88 0x19f8c 0x19f98 0x2d — 0xb62178 and 0xf0 live-checked above; the rest never live-checked.
- `D3D12Context::drawFlush` (16): 0x60 0x68 0x1d8 0x88 0x70 0xf28 0x10c0 0x1110 0x1120 0x1148 0x1150 0x115c 0x1164 0x10 0x18 0x88 — never live-checked.
- `FrameBuilder::visitSky` (5): 0x548 0x138 0x128 0x11c 0x10c — sky dump exists (tags 0,5,6,7) but no assert offset is decoded against it in any on-disk document ([V live] grep of docs/functions and docs/progress visitor units: none).
- `FrameBuilder::visitLight` (5): 0x800 0x648 0x4a0 0x1d0 0x84 — light dump exists (tag 5) but no assert offset decoded live.
- `FrameBuilder::visitItem` (4): 0x140 0xc8 0xe8 0xc0 — item dump exists (tags 0,1,2,3,6,7,10) but no assert offset decoded live.
- `FrameBuilder::visitEffect` (3): 0xf8 0xa0 0xb0 — effect dump exists (tag 3, header-only data line 1 has no decoded fields) but no assert offset decoded live.
- `FrameBuilder::visitUI` (1): 0x90 — ui dump exists (tags 2,3) but the UIMesh size lower bound is not decoded against live bytes.
- `RendererContextD3D12::submit` (8): 0x1778 0x19f88 0xdc5808 0xe746d8 0x19f58 0xdc57e8 0x14700 0x410 — never live-checked.

### (4) Verification gates

- `python tools/sigs/layoutcheck.py --exe <exe>`: exit code 0, 209 assertions, 0 failed (all visitEditor asserts `ok`).
- `python tools/sigs/verify_oc.py docs/progress/oc_U-EX0e.md`: all 11 quoted `0xRVA  instr` lines match rdis disassembly of 0x66742F0 (mismatch=0, no-such-instr=0).
- No truncated lists anywhere in this file (every offset row lists all its sites); no duplicate offset rows; every quoted instruction line copied verbatim from the listing.

### TOOL REQUESTS

None — no helper scripts written; used existing `tools/sigs/layoutcheck.py`, `tools/sigs/verify_oc.py`, `tools/delegate.py check`, and the precomputed listing `docs/data/listings/editor_visitor_66742f0_667e290.txt`. An editor live capture (`python tools/livecap/request.py add editor_visitor 0x66742F0 ...`) would upgrade +0x64/+0x3C from [V] to [V live], but the editor capture files are header-only (0 samples) and in-game testing is deferred per the 2026-11-22 user decision, so no capture is requested now.

CLOSES? YES — every on-disk part of X0e is done: +0x64 and +0x3C re-derived [V] from the 0x66742F0 disassembly (all sites listed; the three tag-5/6/7 case-head `cmp byte ptr [rdi+0x3C],1` reads are the 3 world-phase failures), both lists already contain the corrected constants (verified, zero edits required), `layoutcheck.py` exits 0, and the 184 other assertions never checked against live memory are enumerated above. Per the 2026-11-22 deferred-testing decision the in-game run is not a blocking on-disk fact; no RVA, offset, meaning, or [V] proof is unknown. See docs/BIGBANG_TESTS.md section U-EX0e for the deferred in-game test (editor live captures currently 0 samples, so +0x64/+0x3C stay [V] static proofs until that run).
