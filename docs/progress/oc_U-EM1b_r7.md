## NEXT
DONE

# oc U-EM1b — M1b Inventory per layer (checklist item M1b)

## Goal (from unit)
Close checklist item M1b: list EVERY function of each region (L1 bgfx core ~290, L2 D3D12 ~1,900, L3 RenderDragon ~980, L4/L5 BgfxFrameBuilder ~2,300, L6 frame-graph renderers ~3,600) into docs/data/functions.tsv as D0 with size, callers, strings; then classify (structural / helper / lambda / thunk).

## 1. State on disk (verified, none regenerated)
- docs/data/inventory_L1_bgfx.tsv — 323 rows (L1 bgfx core) [V: wc -l]
- docs/data/inventory_L2_d3d12.tsv — 1854 rows (L2 D3D12) [V: wc -l]
- docs/data/inventory_L3_dragon.tsv — 978 rows (L3 RenderDragon) [V: wc -l]
- docs/data/inventory_L4L5_builder.tsv — 6391 rows (L4/L5, region 0x6600000-0x67e0000) [V: wc -l]
- docs/data/inventory_L6_graph.tsv — 5567 rows (L6, region 0x5500000-0x5700000) [V: wc -l]
- Total inventory rows: 323+1854+978+6391+5567 = 15113, all unique RVAs [V: set check]
- docs/data/function_classes.tsv — 15113 data rows, same RVA set as the 5 inventories [V]. class column = structural/helper/lambda/thunk (+ leaf, frame-helper, entry-indirect, big).
- docs/data/functions.tsv — 15210 lines incl. header = 15209 data rows [V: wc -l]. Status tally D0=15005 / D1=74 / D2=130. All 15113 inventory RVAs present: 14968 appended as D0 + 145 already present as D1/D2 (skipped, idempotent). No duplicate RVAs. [V: wc -l + status tally]

Tool: tools/merge_inventories.py (already exists; appends each inventory RVA not already in functions.tsv, 5-col layout rva|layer|name|status|doc, status=D0, skipping existing RVAs; idempotent/safe to re-run). It was run and produced the current 15209-row state. Size/callers/strings/class live in the inventory TSVs and function_classes.tsv, keyed by RVA — functions.tsv keeps its own 5-column layout per the merge spec ("functions.tsv's own column layout").

## 2. Refinement (a): lambda class — already present on disk
function_classes.tsv already contains a `lambda` class (contradicts the stale r2 note claiming none). [V] direct read:
- 0x56ad350 — class=lambda, name="" — VV pass body "DepthAndNormal" (draw list), vtable 0xf43faa0, size 0xf6, in inventory [V: vv_closures.txt line 13 + function_classes.tsv + inventory_L3_dragon.tsv]
- 0x56aeeb0 — class=lambda, name="" — VV pass body "NothingTask-type small body", vtable 0xf43eb20, size 0x123, in inventory [V: vv_closures.txt line 15 + function_classes.tsv]
- entry-indirect = 6249 rows remain (genuinely indirect vtable/std::function entries; per BGFX_MAP 6el, L4/L5 has 2189 indirect-entry = vtable/std::function only). Only 2 of the 35 VV/RTX pass-lambda test set are inside the 5 inventory regions; both are already classed lambda. The other 33 VV/RTX bodies (e.g. 0xbc8cfd0 TAAUpscaling, 0xbc0b240 CombineVoxelLighting) are OUTSIDE the inventory regions and not part of M1b's listing [V: vv_closures.txt + membership check].
rdis-verified entries:
| offset | size | site | verbatim `0xRVA  instr` line | meaning | tag |
| 0x56ad350 | 0xf6 | lambda body DepthAndNormal (vv_closures line 13) | `0x56ad350  push rsi` | function entry; class=lambda per function_classes.tsv | [V] |
| 0x56aeeb0 | 0x123 | lambda body NothingTask (vv_closures line 15) | `0x56aeeb0  push r15` | function entry; class=lambda per function_classes.tsv | [V] |

## 3. Refinement (b): L6 noise exclusion (~0xF0000 below 0x55f0000)
BGFX_MAP.md 6el: "in L6 the functions below ~0x55f0000 are command/JSON parsing (strings 'commands.hasitem.fail.noItem', 'format_version', 'Missing rule derivation'), NOT render passes; ... filter by address >= 0x55f0000". [V: direct count of inventory_L6_graph.tsv]
- L6 total: 5567 rows [V]
- L6 noise (< 0x55f0000): 3075 rows (command/JSON parsing, excluded) [V: python count]
- L6 render-relevant (>= 0x55f0000): 2492 rows kept [V: python count]
This is the verified L6 render-function count; it does NOT match the item's rough ~3600 estimate (the estimate was approximate; the filter threshold 0x55f0000 is the BGFX_MAP 6el directive). Pass bodies start at the giant 0x55f1450 (VV graph builder, 0x4e144 bytes) [V: BGFX_MAP 6el].
rdis-verified:
| offset | size | site | verbatim `0xRVA  instr` line | meaning | tag |
| 0x55f1450 | 0x2000 (rdis range size) | L6 VV graph builder start (>= 0x55f0000, render-relevant) | `0x55f1450  push rbp` | entry of pass builder 0x55f1450 ("Shadow Cascades") | [V] |
| 0x5500590 | 0x34 | L6 noise example (< 0x55f0000, excluded) | `0x5500590  mov [rsp+0x10],rdx` | entry of a sub-0x55f0000 L6 function (command/JSON noise) | [V] |

## 4. Refinement (c): names / layer split by call graph
Status: [I] / open. BGFX_MAP 6el note: "the L4/L5 file mixes the FrameBuilder layer (extractors/clones) with the frame-renderer pass bodies that consume it (material draw functions); splitting into L4/L5/L6 proper needs the call graph, not an address range." The inventory `layer` column carries the region-derived tag (L1/L2/L3/L4L5_builder/L6_graph); a true call-graph layer split (separating L4 extractors from L5 draw builders from L6 renderers) is not proven by disassembly and is a separate annotate step, not part of this mechanical merge.

## 5. What changed on disk (this unit)
- No source edits needed for the merge: tools/merge_inventories.py already existed and had already been run; docs/data/functions.tsv = 15210 lines (15209 data rows) reflects the completed merge [V: wc -l on disk].
- This progress file docs/progress/oc_U-EM1b.md created (was missing; r1/r2/r3 existed but oc_U-EM1b.md did not).
- Nothing else touched: no builds, no game launch/attach, no edits to Sigs.json, CMake, HookManager.cpp, or any existing hook registration.

## CLOSES?
NO — single blocking fact: the item's wording requires listing every function "into functions.tsv as D0 with size, callers, strings". The D0 listing IS complete and verified on disk (all 15,113 inventory functions present as D0; row count 15,209 data rows / 15,210 lines; D0=15,005/D1=74/D2=130; delegate.py verify_oc passes), but functions.tsv's layout is the 5-column `rva|layer|name|status|doc` — it does NOT carry size/callers/strings (those live in the five inventory TSVs and function_classes.tsv, keyed by RVA). So "with size, callers, strings inside functions.tsv" is not literally met. Additionally the call-graph L4/L5/L6 layer split is [I]/open (needs call graph, not address range). What IS done: exhaustive D0 listing [V], lambda class present with 2 VV/RTX pass bodies [V], entry-indirect=6249 [V], L6 noise quantified (3075 excluded / 2492 kept at >= 0x55f0000) [V]. Remaining: consolidate size/callers/strings into functions.tsv rows (or treat inventory TSVs as the size/callers/strings source keyed by RVA), and prove the L4/L5/L6 call-graph layer split.
