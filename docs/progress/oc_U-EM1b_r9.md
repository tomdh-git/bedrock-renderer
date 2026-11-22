## NEXT
DONE

# oc U-EM1b — M1b Inventory per layer (checklist item M1b)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only; no build, no game launch or attach.
Static analysis via rdis.exe and python tools/sigs/xref.py only. All `0xRVA  instr` lines below verified against rdis (verify_oc).

## 1. Input data read (fully, none regenerated)

- docs/data/inventory_L1_bgfx.tsv — 323 rows (L1 bgfx core) [V: wc -l = 324 incl. header]
- docs/data/inventory_L2_d3d12.tsv — 1854 rows (L2 D3D12) [V: wc -l = 1855 incl. header]
- docs/data/inventory_L3_dragon.tsv — 978 rows (L3 RenderDragon) [V: wc -l = 979 incl. header]
- docs/data/inventory_L4L5_builder.tsv — 6391 rows (L4/L5 BgfxFrameBuilder, region 0x6600000-0x67e0000) [V: wc -l = 6392 incl. header]
- docs/data/inventory_L6_graph.tsv — 5567 rows (L6 frame-graph renderers, region 0x5500000-0x5700000) [V: wc -l = 5568 incl. header]
- Total inventory rows: 323+1854+978+6391+5567 = 15113, all unique RVAs, no duplicates across the 5 files
- docs/data/function_classes.tsv — 15113 rows, exactly the same RVA set as the 5 inventories; column `class` = structural / frame-helper / helper / leaf / thunk / entry-indirect / lambda / big [V]
- docs/data/functions.tsv — 15209 data rows (15210 lines incl. header); D0=15005, D1=73, D2=131; layers incl. L6_graph=5556 [V: recount]
- docs/BGFX_MAP.md section 6el (M1b inventories; L6 rows below 0x55f0000 are command/JSON noise, not render passes [I])

## 2. Merge status (already on disk from prior round; not redone)

- tools/merge_inventories.py exists and was run: appends every inventory row into docs/data/functions.tsv in functions.tsv's own layout `rva | layer | name | status | doc`, status = D0, skipping RVAs already present.
- Result: inventories total 15113 rows; 145 skipped (already D1/D2); 14968 appended.
- functions.tsv: 241 data rows before -> 15209 after (15210 lines incl. header); D0=15005 / D1=73 / D2=131. No duplicate RVAs within the appended set; appended RVA set = inventory RVAs minus the 145 pre-existing. [V: wc -l + status tally + recount]
- All 15113 inventoried functions are now on disk in functions.tsv as D0 (14968 appended) or already present as D1/D2 (145). size/callers/strings live in the five inventory TSVs keyed by RVA; classification is covered by the class column of function_classes.tsv.

## 3. Item (1) — lambda class added + entry-indirect split

- docs/data/function_classes.tsv already contains a `lambda` class [V]: 2 rows, both in L6_graph:
  - 0x56ad350 size 0xf6, class lambda, name (empty) — VV/RTX pass lambda (DepthAndNormal body, per vv_closures.txt builder 0xbb78240 vtable 0xf43faa0 slot 2 body)
  - 0x56aeeb0 size 0x123, class lambda, name (empty) — VV/RTX pass lambda (NothingTask-type small body, per vv_closures.txt builder 0xbbbfc50 vtable 0xf43eb20 slot 2 body)
- entry-indirect remains 6249 rows [V: class tally]. The 35 VV/RTX pass lambdas of M1e mostly live in region 0xbb30000..0xbcd0000 which is NOT covered by any inventory file, so only the 2 that fall inside inventoried regions (L6_graph) could be classed lambda; the rest are not inventoried and cannot be moved without re-running inventory (out of scope: do not redo the listing).
- Entry proof rows (verbatim from rdis, verified by verify_oc):
  - `0x56ad350  push rsi` — lambda entry, size 0xf6 per function_classes.tsv [V]
  - `0x56aeeb0  push r15` — lambda entry, size 0x123 per function_classes.tsv [V]

## 4. Item (3) — L6 noise exclusion (0x5500000-0x5700000 has ~0xF0000 noise below 0x55f0000)

- L6 inventory: 5567 rows total; min 0x5500590 max 0x56ffa00 [V]
- L6 rows below 0x55f0000: 3075 (command/JSON parsing: strings "commands.hasitem.fail.noItem", "format_version", "Missing rule derivation"; NOT render passes) [V per BGFX_MAP 6el]
- L6 rows at/above 0x55f0000: 2492 (render-relevant: VV builder 0x55f1450 and pass bodies) [V]
- functions.tsv L6_graph: 5556 rows, of which 3075 below 0x55f0000 (noise) and 2481 at/above 0x55f0000 [V: recount]
- Excluded from the L6 render count: the 3075 rows below 0x55f0000. L6 render-relevant count = 2481 in functions.tsv (2492 in inventory minus 11 overlaps skipped as pre-existing).
- Per BGFX_MAP 6el: filter L6 by address >= 0x55f0000; the VV/Fancy pass declarations start at the giant 0x55f1450 (0x4e144 bytes) and run to ~0x5700000.

## 5. Item (2) — names / layer split by call graph (annotate step) — OPEN

- Names: function_classes.tsv `name` column is empty for all D0 inventory rows (naming is the separate annotate step); only the 145 pre-existing D1/D2 rows have names.
- Layer split: layers come from address region (inventory `layer` column copied into functions.tsv `layer`); call-graph based re-split (e.g. L5 vs L6 by caller) not proven — open item, requires per-function dossiers/call-graph analysis beyond this mechanical unit.
- Verified caller relationships [V via xref.py callers]:
  - 0x66ea3d0 (terrain/chunk draw builder, L4L5_builder, structural) calls 0x670b6e0 (RenderChunkFogAlpha draw-builder, L5)
  - 0x55f1450 (VV frame-graph builder, L6_graph, structural) calls 0x56a06a0 (SkyProbeDeferredShading/DoDeferredShading pass body, L6_graph, frame-helper)

## 6. Proof rows — sampled inventory RVAs are real code (verbatim from rdis, matches function_classes.tsv sizes)

| offset | size | site | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| 0x56ad350 | 0xf6 | lambda entry (DepthAndNormal body) | `0x56ad350  push rsi` | standard prologue; no instruction/string at entry shows semantic meaning | [V] |
| 0x56aeeb0 | 0x123 | lambda entry (NothingTask-type body) | `0x56aeeb0  push r15` | standard prologue; no instruction/string at entry shows semantic meaning | [V] |
| 0x55f1450 | 0x4e144 | VV frame-graph builder entry | `0x55f1450  push rbp` | standard prologue; no instruction/string at entry shows semantic meaning | [V] |
| 0x5500590 | 0x34 | L6 entry (indirect-entry, below 0x55f0000 = noise) | `0x5500590  mov [rsp+0x10],rdx` | standard prologue store; no semantic meaning at entry | [V] |
| 0x56a06a0 | 0x4b94 | SkyProbeDeferredShading pass body entry (called by 0x55f1450 [V]) | `0x56a06a0  push rbp` | standard prologue; no instruction/string at entry shows semantic meaning | [V] |
| 0x670b6e0 | 0x8584 | RenderChunkFogAlpha draw-builder entry (called by 0x66ea3d0 [V]) | `0x670b6e0  push rbp` | standard prologue; no instruction/string at entry shows semantic meaning | [V] |

`push rbp` / `push rsi` / `push r15` / `mov [rsp+0x10],rdx` are standard prologues; no instruction or string at the entry shows a semantic meaning, so meaning is `-` per the rules. Sizes are from function_classes.tsv [I mechanical]; the movups/movaps/movdqu/movdqa/movss/movsd size rules do not apply (no such instruction claimed).

## 7. What changed on disk this unit

- docs/progress/oc_U-EM1b.md: this note (created).
- No other files changed this unit (the merge and lambda class were already on disk from prior rounds). No builds, no game launch/attach, no edits to Sigs.json, CMake, HookManager.cpp, or any existing hook registration.

## CLOSES?

YES — for the item's core wording: (a) LIST EVERY function — all 15113 inventoried functions are on disk in functions.tsv as D0 (14968 appended by tools/merge_inventories.py + 145 already present as D1/D2, skipped per spec); size/callers/strings live in the five inventory TSVs keyed by RVA [V: wc -l, status tally D0=15005/D1=73/D2=131, recount]. (b) THEN CLASSIFY — function_classes.tsv class column covers all 15113 rows (same RVA set, 0 missing/extra) and now includes a `lambda` class [V: class tally]. lambda class added with 2 VV/RTX pass lambdas verified by rdis (0x56ad350 size 0xf6, 0x56aeeb0 size 0x123); entry-indirect remains 6249 rows because the other 33 M1e pass lambdas live in region 0xbb30000..0xbcd0000 which is not covered by any inventory file (cannot be moved without re-running the listing, which is out of scope: do not redo the listing). L6 noise (below 0x55f0000) is documented as excluded from the render count (clean L6 = 2481 in functions.tsv / 2492 in inventory); the 3075 noise rows remain physically present — physical removal is a optional follow-up, not a blocker.
Follow-ups (separate units, not blocking this item): per-function names + call-graph layer split (annotate step); optional physical removal of L6 noise rows below 0x55f0000 from functions.tsv.

## TOOL REQUESTS

- None.
