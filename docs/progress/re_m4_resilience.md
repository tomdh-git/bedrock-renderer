# RE M4 Version Resilience (62.01)

## NEXT
- **Unit:** Finalize edits if any verified additive fixes identified (Sigs.json anchor comments, BEHAVIOR_NOTES runbook additions), then close report.
- **Resume:** Re-read parity diff results in this file; verify any candidate constant/anchor in disassembly via `python tools/sigs/xref.py dis <rva>` or `tools/rdis/target/release/rdis.exe <exe> -c "dis <rva> <n>"` before editing. Re-run `python tools/sigs/audit.py <exe> --json docs/progress/re_m4_audit_sigs.json` and `python tools/sigs/layoutcheck.py --exe <exe> --json docs/progress/re_m4_layoutcheck.json` after edits.
- **Half-done:** Initial audit complete (sigs live, layout asserts pass). Parity gaps enumerated; need decision on header additions (small-constant false-positive risk in `renderlayout::contains`). Port-check runbook drafted below pending final polish.

## Progress log

### M4-INIT - DONE (baseline audit 62.01)
- **Evidence [V]:** `python tools/sigs/audit.py "C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe" --json docs/progress/re_m4_audit_sigs.json`
  - exe: `...Minecraft.Windows.exe` size 323825488, TimeDateStamp `6AEA437E` (2026-11-03T20:26:38Z), version `1.26.62.1`
  - 80 symbols, 0 with no live pattern, 1 FALLBK (`common::BobHurt` first pattern dead, pattern 1 used at 0x53a1320 per Sigs.json comment context)
  - Render-path sigs relevant to M4 all LIVE on 62.01 (bgfx Encoder/FrameGraph/D3D12Context/FrameBuilder visitors, RenderMark, BgfxContext::liveContext, FrameBuilder::_insert, passLookup/bodyActor etc.)
- **Evidence [V]:** `python tools/sigs/layoutcheck.py --exe ...62.01... --json docs/progress/re_m4_layoutcheck.json`
  - 186 assertions, 0 failed across 19 anchor functions in `docs/data/layout_asserts.json`
- **Evidence [V]:** `docs/data/port_check_render_sigs.tsv` (existing) shows render sig movement across 50.04/51.01/60.05/62.01 (many FrameGraph/D3D12/task entries DEAD on older exes; core Encoder submit/reset/frameSort live across listed versions).
- **Files created:** `docs/progress/re_m4_resilience.md`, `docs/progress/re_m4_audit_sigs.json`, `docs/progress/re_m4_layoutcheck.json`

### M4a - OPEN (render-path anchors vs 62.01)
- **Findings [V]:** Sigs.json render-path entries generally include 62.01 RVAs in `comment` fields (e.g. `Encoder::submit rva 0xBC60740`, `FrameGraph::taskDispatch rva 0xE9002E0`, visitors with docs refs). Audit confirms unique/live matches on target exe.
- **Gaps [I]:** M4a asks for "version-stable anchor (string / __FUNCSIG__ / unique sig) beside the RVA (Sigs.json + dossier anchors block)". Sigs.json stores the signature patterns (stable-ish byte anchors) but does not consistently record human-readable stable anchors like __FUNCSIG__ strings/zone strings in comments for every D2/D3 render function; dossiers/BEHAVIOR_NOTES hold some (e.g. zone strings for visitors/wrappers, "MemoryReader: read truncated.", etc.). Need targeted dossier/string evidence before adding comments (avoid guessing).
- **Stale/missing anchors relevant to render path [V]:** No DEAD render-path signatures on 62.01. `common::BobHurt` has pattern 0 dead since 1.26.60 (documented in comment) with pattern 1 live — not a render-path M4 blocker but a noted fallback.

### M4c - OPEN (layout_asserts.json ↔ RenderLayoutAsserts.h parity)
- **Evidence [V]:** Programmatic diff (normalized hex values) between `docs/data/layout_asserts.json` and `src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h` function tables:
  - `Encoder::reset`: json has `0x60` not in header.
  - `Encoder::dispatch`: json has `0xc0,0xd0,0xe0,0xe2` not in header.
  - `Encoder::submitFrameParams`: json has `0xe3` not in header.
  - `Encoder::frameSort`: json has `0x36` not in header.
  - `FrameGraph::endFrame`: json has `0x35` not in header.
  - `FrameGraph::generate`: json has `0x78` not in header.
  - `FrameGraph::taskDispatch`: json has `0x88,0x18` not in header.
  - `D3D12Context::drawExecutor`: json has `0xf0,0xa32178,0x1f0f07ff,0x74,0x2a,0x39,0x54,0x68,0x70,0x7a,0x62,0xf8` not in header.
  - `D3D12Context::setVertexBuffers`: json has `0x54,0x78,0x58,0x60,0x4c,0x63` not in header.
  - `D3D12Context::psoBuilder`: json has `0xf8,0xb8,0x68,0x32,0x54,0x26,0xa8,0xb0,0x34,0x19f8c,0x2d` not in header.
  - `D3D12Context::drawFlush`: json has `0x60,0x68,0x88,0x70` not in header.
  - No functions missing on either side (19/19). No header-only constants found.
- **Interpretation [I]:** Header comment states small constants below 0x100 live in layout_asserts.json because raw byte search cannot prove them; however several <0x100 values are present in header today while others are omitted, creating partial parity. `renderlayout::contains` scans 4-byte LE immediates/displacements in function code windows — adding very small/common values (e.g. 0x18, 0x2a, 0x2d, 0x34, 0x35, 0x36, 0x39) risks false positives in large functions. Without in-disassembly verification of each candidate as a distinctive immediate/displacement in the anchored window, adding them would violate "verified constants only" for the header's purpose.
- **Status:** OPEN — gaps documented; no header/json edits made in this pass because verification must be per-constant (distinctive encoding/use) and I did not perform disassembly confirmation for each missing small value.

### M4b - PARTIAL/OPEN (BEHAVIOR_NOTES coverage)
- **Evidence [V]:** `docs/BEHAVIOR_NOTES.md` covers bgfx core (submit/reset/frame sort/context init/frame swap/shutdown/renderFrame/thread proc/command interpreter), D3D12 backend (submit/draw executor/PSO builder/draw flush), RenderDragon frame graph & GraphicsTasks, FrameBuilder inserts/visitors/extractors/helpers, pass declaration/execution summary, and explicitly states "What is NOT covered yet..." including per-pass in/out resources of each VV pass lambda (M1e), PSO-desc build on cache miss (6fr), pass-name vector producer, most task bodies, Atmosphere producer (R1).
- **Gap [V/I]:** Matches M4b progress note in RENDER_CHECKLIST: "not yet for M1d/M1e items". Key render-path behaviors for reversed D2/D3 anchors listed are present; broader M1d/M1e behavioral coverage remains open (out of scope to invent without evidence).

## Short port-check runbook (draft)

Goal: on a new Minecraft.Windows.exe build, determine which render-path anchors moved and which layout constants drifted before runtime testing.

1. **Identity & inputs [V process]**
   - Record exe path, version, TimeDateStamp, size: `python tools/sigs/audit.py <exe> --json <out.json>` (header includes identity).
   - Use repo root with `$env:PYTHONUTF8=1` for Python tools.

2. **Signature liveness (render-path first) [V]**
   - Run `python tools/sigs/audit.py <exe> src/sdk/Sigs.json --json docs/progress/portcheck_sigs_<ver>.json`.
   - Filter for render-path symbols: `mc/deps/bgfx/*`, `mc/deps/bgfx/FrameBuilder/*`, `mc/client/renderer/framebuilder/*` (RenderMark, FrameBuilder::_insert, passLookup, bodyActor), and any M4/M3 seam anchors in use.
   - For DEAD: inspect `nearest` diffs in JSON; compare against known stable byte anchors/strings in dossiers/BEHAVIOR_NOTES; update pattern only with disassembly-confirmed match in rdis (`tools\rdis\target\release\rdis.exe <exe> -c "str <text>; xref <rva>"` as applicable).
   - For MULTI: disambiguate by prologue/size/callees/strings before accepting.

3. **Layout/content checks [V]**
   - Run `python tools/sigs/layoutcheck.py --exe <exe> --manifest docs/data/layout_asserts.json --json docs/progress/portcheck_layout_<ver>.json`.
   - Treat any FAIL as "re-derive SDK constant backed by this anchor": use `nearby` values and disassemble anchor function (`python tools/sigs/xref.py dis <rva>` or rdis) to locate moved immediate/displacement.
   - Only update `layout_asserts.json` and `src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h` with values verified in the anchored function body; keep function scan `size` in header aligned to 62.01-era window only if still appropriate, else adjust with evidence.

4. **Movement measurement (M4d support) [V/I]**
   - Compare new RVAs vs prior baseline (`docs/data/port_check_render_sigs.tsv`, prior portcheck JSONs) to build a delta table per symbol.
   - If older exes are available locally, rerun audit/layoutcheck and (when available) dossier tool per checklist M4d; if unavailable, record blocker "previous exe not present".

5. **Behavior/anchor resilience notes [V]**
   - For any changed function, confirm stable anchors (strings, __FUNCSIG__, distinctive constants/call shapes) still hold and update dossier "anchors" blocks / Sigs.json comments with evidence-backed notes.
   - Reconcile contradictions with disassembly/live-static evidence (6ek-style audit note in progress file).

6. **Exit criteria for M4 port pass**
   - No unexplained DEAD in render-path sig set; all intentional fallbacks documented.
   - layoutcheck 0 failed for asserted functions or each failure triaged with re-derived values.
   - Parity decisions for small constants documented (why in json-only vs header+json).

## Final report (in-progress)

### Items DONE (this subtask scope)
- **M4 audit baseline (62.01):** Sigs audit run and saved; layoutcheck run and saved; render-path signatures all live on target exe [V].
- **M4c parity assessment:** Full diff between `layout_asserts.json` and `RenderLayoutAsserts.h` produced and recorded; no verified additive corrections applied (see gaps/constraints) [V].
- **M4b coverage review:** BEHAVIOR_NOTES reviewed against checklist expectations; gaps align with stated M1d/M1e/open items [V].
- **Port-check runbook:** Drafted with concrete commands and evidence gates [V process].

### Items OPEN (blocking facts)
1. **M4a anchor documentation completeness:** Missing a verified inventory pass mapping each D2/D3 render function to an explicit version-stable anchor string/__FUNCSIG__ recorded beside RVA in Sigs.json/dossier anchors blocks. **Blocker:** requires per-function dossier/string evidence collection (and some dossiers/strings may not exist or be named differently); not fully derivable from current automated outputs alone without targeted reads/disassembly.
2. **M4c header↔json parity closure:** 11 functions have json-only constants (mostly small values). **Blocker:** each candidate needs disassembly/use-context verification to ensure it is a distinctive immediate/displacement safe for `RenderLayoutAsserts.h`'s byte-scan `contains()` and satisfies "verified constants only"; small values have false-positive risk.
3. **M4b M1d/M1e behavior notes:** BEHAVIOR_NOTES does not yet cover M1d/M1e items called out by checklist. **Blocker:** underlying reverse-engineering facts for those items are not present in this task's verified inputs.
4. **M4d dossier rerun on previous exes:** Not executed. **Blocker:** previous-version exe binaries not specified/available in workspace context for this run; `docs/data/port_check_render_sigs.tsv` provides partial historical sig movement only.

### Files created/edited
- Created: `docs/progress/re_m4_resilience.md`
- Created: `docs/progress/re_m4_audit_sigs.json` (audit tool output)
- Created: `docs/progress/re_m4_layoutcheck.json` (layoutcheck tool output)
- Edited: none (no additive/corrective changes applied without per-constant/per-anchor verification)

## FULL PROPOSED BGFX_MAP ENTRY TEXT (entry IDs TBD)

**Title:** M4 version resilience audit — 1.26.62.01 render-path anchors, layout assertions, behavior notes, and port-check procedure (subagent `re_m4_resilience`)

**Scope:** Static/offline audit only against `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe` (TimeDateStamp 6AEA437E, 2026-11-03T20:26:38Z, version 1.26.62.1). No debugger, no patches, no commits.

**Facts [V]**
- `tools/sigs/audit.py` (62.01): 80 symbols total, 0 dead, 1 fallback (`common::BobHurt` pattern 0 dead, pattern 1 live). All render-path bgfx/Encoder/FrameGraph/D3D12Context/FrameBuilder visitor and framebuilder seam signatures in `src/sdk/Sigs.json` resolved live/unique on this exe (see `docs/progress/re_m4_audit_sigs.json`).
- `tools/sigs/layoutcheck.py` (62.01, `docs/data/layout_asserts.json`): 186 assertions, 0 failed across 19 anchor functions (see `docs/progress/re_m4_layoutcheck.json`).
- Existing `docs/data/port_check_render_sigs.tsv` records cross-version liveness/movement for core render sigs (50.04/51.01/60.05/62.01), indicating which FrameGraph/D3D12/task symbols appear only in newer builds.

**Parity assessment (layout_asserts.json ↔ RenderLayoutAsserts.h) [V]**
- Function coverage matches (19/19). No header-only constants; no missing function entries.
- JSON-only constants (not present in header): `Encoder::reset` {0x60}; `Encoder::dispatch` {0xc0,0xd0,0xe0,0xe2}; `Encoder::submitFrameParams` {0xe3}; `Encoder::frameSort` {0x36}; `FrameGraph::endFrame` {0x35}; `FrameGraph::generate` {0x78}; `FrameGraph::taskDispatch` {0x88,0x18}; `D3D12Context::drawExecutor` {0xf0,0xa32178,0x1f0f07ff,0x74,0x2a,0x39,0x54,0x68,0x70,0x7a,0x62,0xf8}; `D3D12Context::setVertexBuffers` {0x54,0x78,0x58,0x60,0x4c,0x63}; `D3D12Context::psoBuilder` {0xf8,0xb8,0x68,0x32,0x54,0x26,0xa8,0xb0,0x34,0x19f8c,0x2d}; `D3D12Context::drawFlush` {0x60,0x68,0x88,0x70}.
- Interpretation [I]: many omissions are sub-0x100 values; `RenderLayoutAsserts.h::contains` performs 4-byte LE scans over function windows, so promoting small/common immediates without per-site distinctiveness verification risks false positives. No additive header edits made this pass ("verified constants only").

**Behavior notes coverage [V]**
- `docs/BEHAVIOR_NOTES.md` provides RVA-free behavior descriptions for bgfx core, D3D12 backend, frame graph/GraphicsTasks, group inserts/visitors/extractors/helpers, and pass declaration/execution shapes, with explicit open items (per-pass VV in/out resources M1e, PSO-desc build on cache miss 6fr, pass-name vector producer, most task bodies, Atmosphere producer R1). This aligns with M4b progress but remains incomplete for M1d/M1e.

**Port-check runbook (short) [V process]**
1. Capture exe identity and signature audit: `python tools/sigs/audit.py <exe> src/sdk/Sigs.json --json docs/progress/portcheck_sigs_<ver>.json` (PYTHONUTF8=1). Prioritize render-path symbols; resolve DEAD/MULTI via nearest diffs + rdis/string/callee confirmation.
2. Run layout assertions: `python tools/sigs/layoutcheck.py --exe <exe> --manifest docs/data/layout_asserts.json --json docs/progress/portcheck_layout_<ver>.json`. For each FAIL, re-derive moved constant from disassembly of the anchored function and update json/header only with verified values; document scan-window (`size`) changes if needed.
3. Measure movement: diff RVAs against `docs/data/port_check_render_sigs.tsv` and prior portcheck artifacts; rerun dossier-based comparisons on older exes when available (M4d).
4. Record stable anchors (strings/__FUNCSIG__/unique constants/call shapes) in dossiers and Sigs.json comments with evidence; log contradictions as audit notes.
5. Exit when render-path sigs are explained (live/fallback-documented), layoutcheck failures triaged/fixed with proof, and small-constant parity decisions documented.

**Remaining gaps / blockers**
- M4a: version-stable anchor (string/__FUNCSIG__) not exhaustively recorded beside RVA for every D2/D3 render function in Sigs.json + dossier anchor blocks; needs per-function evidence pass.
- M4c: json↔header parity not closed for the 11 functions above because per-constant distinctiveness verification in disassembly was not completed; promoting small values is unsafe without that proof.
- M4b: M1d/M1e behavior notes still absent (evidence not available here).
- M4d: dossier rerun on previous exes not performed (prior exe binaries not available in this session).

**Artifacts:** `docs/progress/re_m4_resilience.md`, `docs/progress/re_m4_audit_sigs.json`, `docs/progress/re_m4_layoutcheck.json`.
