## NEXT
DONE

# oc U-EM1b — M1b Inventory per layer (checklist item M1b)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only; no build, no game launch or attach. No input data was regenerated; every input file below was read in full.

## 1. Input data read (fully; none regenerated)

- docs/data/inventory_L1_bgfx.tsv — 323 rows, region 0xbc5e0f0-0xbc7dee0 [V: wc -l = 324 incl. header]
- docs/data/inventory_L2_d3d12.tsv — 1854 rows, region 0xe800c10-0xe8bff30 [V: wc -l = 1855 incl. header]
- docs/data/inventory_L3_dragon.tsv — 978 rows, region 0xc250000-0xc29ffc0 [V: wc -l = 979 incl. header]
- docs/data/inventory_L4L5_builder.tsv — 6391 rows, region 0x6600040-0x67dffe0 [V: wc -l = 6392 incl. header]
- docs/data/inventory_L6_graph.tsv — 5567 rows, region 0x5500590-0x56ffa00 [V: wc -l = 5568 incl. header]
- Total inventory rows: 323+1854+978+6391+5567 = 15113, all unique RVAs, no duplicates across the 5 files [V: python set check]
- docs/data/function_classes.tsv — 15113 rows, exactly the same RVA set as the 5 inventories (0 missing, 0 extra) [V: python set check]
- docs/data/functions.tsv — 15209 data rows / 15207 distinct RVAs (2 duplicate RVAs: 0xbc65720 and 0xe81e860 each appear twice); layout `rva | layer | name | status | doc` [V: wc -l + grep]
- docs/BGFX_MAP.md section 6el [I: region meaning], docs/data/vv_closures.txt [V: mechanical closure table], docs/functions/vv_lambda_bodies.md [V/I: dossier]

Inventory columns: `rva | size | layer | class | ncallers | callers3 | ncallees | strings2 | vcalls | name | status`; all inventory status D0.

## 2. Step 1 (this file)

docs/progress/oc_U-EM1b.md created now: line 1 is `## NEXT`, line 2 is `step 2`. Resume point after this unit's work is recorded below.

## 3. Merge into docs/data/functions.tsv — complete on disk, count check [V]

tools/merge_inventories.py already exists and is idempotent: it appends each inventory RVA missing from functions.tsv in functions.tsv's own 5-column layout `rva | layer | name | status | doc` with status forced to D0, skipping RVAs already present (name taken from function_classes.tsv if non-empty, else the inventory name, else empty; `doc` left empty; `size`/callers/strings stay in the inventory TSVs keyed by RVA; `class` stays in function_classes.tsv).

Run: `PYTHONUTF8=1 python tools/merge_inventories.py` → `inventory rows total=15113 already_present=15113 newly_added=0`; `functions.tsv data rows now=15209 (= 15207 distinct RVAs)` [V: script output].

Every one of the 15113 inventory RVAs is already present in functions.tsv: 0 missing [V: set check]. The 145 inventory RVAs that were already D1/D2 anchors were skipped per spec (e.g. 0xbc60740 bgfx::Encoder::submit D2, 0xe82e230 D3D12 submit D2, 0xc250000-area L3 rows, 0x55f1450 VV builder D1); the ~14968 appended rows are all D0 [V: r2 inventory, confirmed by my set check showing 0 missing].

Status tally on functions.tsv now: D0=15005 / D1=73 / D2=131 (15209 data rows) [V: grep]. (r2 noted D1=74/D2=130; my count differs by one row, likely one of the 2 duplicate RVAs carrying a different status in its second occurrence — not resolved here, [?].)

No data file was modified by this unit: the merge result already exists on disk, and the script is idempotent (re-running adds 0 rows).

## 4. Layer counts and L6 noise exclusion [V: data files]

| layer | region | inventory rows | excluded as noise (rva < 0x55f0000) | signal rows |
|---|---|---|---|---|
| L1 bgfx core | 0xbc5e0f0-0xbc7dee0 | 323 | 0 | 323 |
| L2 D3D12 backend | 0xe800c10-0xe8bff30 | 1854 | 0 | 1854 |
| L3 RenderDragon | 0xc250000-0xc29ffc0 | 978 | 0 | 978 |
| L4/L5 BgfxFrameBuilder | 0x6600040-0x67dffe0 | 6391 | 0 | 6391 |
| L6 frame-graph renderers | 0x5500000-0x5700000 | 5567 | 3075 | 2492 |

L6 exclusion rule (annotation only; the inventory TSV is not regenerated, per "do not redo the listing"): per BGFX_MAP.md 6el the first ~0xF0000 bytes of the L6 range (rva < 0x55f0000) are command/JSON parsing, not render passes; the VV/Fancy pass declarations start at the giant 0x55f1450 builder and run to ~0x5700000. Filter rva >= 0x55f0000 → 2492 L6 signal functions; 3075 excluded [V: row counts from inventory_L6_graph.tsv].

[V] command/JSON string xrefs confirmed inside the excluded region: "commands.hasitem.fail.noItem" referenced at 0x558134a (function 0x557fd00); "Missing rule derivation, rule: %s, derivation: %s" referenced at 0x5588aa3 (function 0x5587ac0) — both below 0x55f0000 [V: tools/sigs/xref.py str].

The ~3600 L6 estimate in BGFX_MAP.md 6el is a pre-filter estimate; measured post-exclusion signal is 2492 functions. The gap (2492 vs ~3600) is not resolved by this unit [?].

## 5. Classification: structural / helper / lambda / thunk [V: function_classes.tsv]

Class counts over all 15113 inventoried functions [V: function_classes.tsv]:

| class | count | mapping to item taxonomy |
|---|---|---|
| entry-indirect | 6249 | unclassified in effect (not structural/helper/lambda/thunk) |
| leaf | 5996 | helper |
| helper | 1117 | helper |
| frame-helper | 705 | helper |
| thunk | 882 | thunk [V mechanical — class name matches taxonomy] |
| structural | 137 | structural [V mechanical — class name matches taxonomy] |
| big | 25 | helper by size [I] |
| lambda | 2 | lambda [V] |

lambda rows [V: docs/data/vv_closures.txt lists builder-installed std::function closures whose vtable slot 2 is the body; both rows are in the L6 inventory and class lambda in function_classes.tsv]:

| rva | size | class | note |
|---|---|---|---|
| 0x56ad350 | 0xf6 | lambda | DepthAndNormal draw-list body; slot-2 body of vtable 0xf4407f0 (builder 0xbb78240) [V vv_closures.txt] |
| 0x56aeeb0 | 0x123 | lambda | NothingTask-type small body; slot-2 body of vtable 0xf43eb20 [V vv_closures.txt] |

The remaining VV/RTX pass bodies (e.g. 0xbc0b240 CombineVoxelLighting, 0xbc2c590 CausticsMultiplierPass, 0xbc080c0 RTX driver) live at 0xbb30000-0xbcd0000, outside all five inventory regions (verified: not present in any inventory_*.tsv [V: set check]), so they are not in function_classes.tsv and cannot be marked lambda there without breaking its verified 1:1 RVA set with the inventories. The 35 VV/RTX pass lambda test set (M1e) cannot be completed inside function_classes.tsv on this basis; 6249 entry-indirect rows remain entry-indirect (split of entry-indirect into lambda/not-lambda not done).

## 6. Names / layer split by call graph [open]

functions.tsv has 241 named rows; all other rows are unnamed D0 by design — naming is the separate annotate step and is not done for this unit. Layer is assigned by address region in both functions.tsv and the inventories; a call-graph-based layer split (e.g. an L4/L5 function whose only callers are in L6) is not proven and remains [I]. Not redone here (no re-listing per spec).

## 7. Proof rows (verbatim instruction lines from rdis)

Each `0xRVA  instr` line below is copied verbatim from `rdis.exe ... dis <rva>` output and checked with `tools/sigs/verify_oc.py`. Meaning is `-` where the entry instruction shows no semantic content (prologue only), per the rules.

| name | rva | size | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| L1 bgfx core entry (D0, merged) | 0xbc5e0f0 | 0x2d | `0xbc5e0f0  mov [rsp+0x10],rdx` | - | [V] |
| L2 D3D12 entry (D0, merged) | 0xe800c10 | 0x58 | `0xe800c10  sub rsp,0x48` | - | [V] |
| L3 RenderDragon entry (D0, merged) | 0xc250000 | 0x93 | `0xc250000  push rbp` | - | [V] |
| L4/L5 builder entry (D0, merged) | 0x6600040 | 0x42 | `0x6600040  mov [rsp+0x10],rdx` | - | [V] |
| L6 frame-graph entry (D0, merged, indirect-entry) | 0x5500590 | 0x34 | `0x5500590  mov [rsp+0x10],rdx` | - | [V] |
| class lambda: DepthAndNormal draw-list body | 0x56ad350 | 0xf6 | `0x56ad350  push rsi` | - | [V] |
| class lambda: NothingTask small body | 0x56aeeb0 | 0x123 | `0x56aeeb0  push r15` | - | [V] |
| L6 VV frame-graph builder (giant, D1) | 0x55f1450 | 0x4e144 | `0x55f1450  push rbp` | - | [V] |

## 8. What changed on disk

- Created: docs/progress/oc_U-EM1b.md (this note).
- Modified: none. docs/data/functions.tsv already contained all 15113 inventory RVAs (merge_inventories.py run: newly_added=0, idempotent). docs/data/function_classes.tsv already carries class lambda for 0x56ad350/0x56aeeb0.
- Not touched: no builds, no game launch/attach, no HookManager.cpp or any hook registration, no Sigs.json, no CMake, no docs/BGFX_MAP.md.

## CLOSES?

NO — blocking fact: the item's wording ("list EVERY function of each region into functions.tsv as D0 with size, callers, strings; then classify (structural/helper/lambda/thunk)") is not met by what exists on disk now: classification is incomplete — 6249 of 15113 functions remain entry-indirect (unclassified in effect) and only 2 of the 35 VV/RTX pass lambdas (M1e test set) carry class lambda; the remaining pass bodies live outside the five inventories so the lambda test set cannot be completed in docs/data/function_classes.tsv without breaking its verified 1:1 RVA set. Also open: names/call-graph layer split (section 6), and the L6 count (measured 2492 signal functions after noise exclusion vs the ~3600 estimate, section 4).

## TOOL REQUESTS

- None.
