## NEXT
DONE

# oc U-EM1b — M1b Inventory per layer: lambda class, L6 noise filter, count check

## Status on disk at start of this sitting (read, not regenerated)
- docs/data/functions.tsv: 15210 lines = header + 15209 data rows; status D0=15005, D1=74, D2=130; layout `rva | layer | name | status | doc`. All 15113 inventory RVAs are present (14968 appended D0 by tools/merge_inventories.py, 145 pre-existing D1/D2 skipped).
- docs/data/inventory_*.tsv: 15113 rows total (L1 323, L2 1854, L3 978, L4L5_builder 6391, L6_graph 5567), unique RVAs, columns rva|size|layer|class|ncallers|callers3|ncallees|strings2|vcalls|name|status. Size/callers/strings live here, keyed by RVA.
- docs/data/function_classes.tsv: 15113 rows, same RVA set as the inventories; classes were leaf/frame-helper/helper/thunk/entry-indirect/structural/big — NO 'lambda' class; entry-indirect=6250 (effectively unclassified).
- tools/merge_inventories.py: present, idempotent, already run (re-running changes nothing; no re-run needed).

## 1. Lambda class added; entry-indirect split (test set = VV/RTX pass lambdas of M1e)
docs/data/vv_closures.txt [V] lists closure bodies (builder -> closure vtable -> slot-2 body): 32 body rows, 30 unique bodies. Only 2 of them fall inside the inventoried regions and are therefore present in docs/data/function_classes.tsv; the other 28 documented bodies sit at 0xbc* RVAs outside all 5 inventory regions and are absent from function_classes.tsv/inventories (extending coverage is a separate item, not invented here).
Edits to docs/data/function_classes.tsv (class column only; row count and RVA set unchanged):
- 0x56ad350: entry-indirect -> lambda (size 0xf6; DepthAndNormal closure body, builder 0xbb78240, vtable 0xf43faa0 slot 2)
- 0x56aeeb0: leaf -> lambda (size 0x123; NothingTask-type small closure body, builder 0xbbbfc50, vtable 0xf43eb20 slot 2)
New class counts [V after edit]: entry-indirect 6249, lambda 2, leaf 5996, frame-helper 705, helper 1117, thunk 882, structural 137, big 25; total 15113. The remaining 6249 entry-indirect rows need per-function call-site analysis; out of scope for this sitting.

## 2. Names / layer split by call graph (annotate step) — partial
- D0 rows are unnamed by design; naming is a separate per-function step. Named on disk: the 8 big render functions in functions.tsv (0x670b6e0/0x6722cb0/0x67762e0/0x6792d90/0x67aa700 RenderChunkFogAlpha draw-builders, 0x66a6830 shadow volume builder, 0x56a06a0 SkyProbe/DoDeferredShading, 0x56e1990 Upscaling) [I from r1/r2 string analysis; layers by caller/region].
- Call-graph evidence verified on the exe: rdis callees of 0x66ea3d0 (L4L5 terrain/chunk draw builder, size 0xf430): calls sub_670b6e0 x1, sub_6722cb0 x1, sub_67762e0 x1, sub_6792d90 x1, sub_67aa700 x1 [V rdis] -> the five RenderChunkFogAlpha builders are direct callees of the L5 terrain builder, supporting their L5 draw-builder naming. L6 pass declarations are registered indirectly (std::function/vtable declarators in 0x55f1450 / 0xbbe2d50) [V BGFX_MAP 6hb/6ar].
- Full names + call-graph layer split for all ~15k D0 rows remains open (per-function string analysis + caller walk).

## 3. L6 noise exclusion — count check
- docs/data/inventory_L6_graph.tsv: 5567 rows, region 0x5500000-0x5700000.
- Filter per docs/BGFX_MAP.md 6el: functions below 0x55f0000 are command/JSON parsing noise (strings incl. "commands.hasitem.fail.noItem"), not render passes; treat the first ~0xF0000 bytes as noise (filter rva >= 0x55f0000).
- Measured [V from the TSVs]: below 0x55f0000: 3075 rows, total size 0xE664E bytes (~0xF0000, matches 6el); at/above 0x55f0000: 2492 rows = L6 render-relevant functions.
- Note: r2's "~3600" estimate is not reproduced by the address filter; measured render-relevant L6 = 2492 [I discrepancy flagged, not resolved].

## 4. Re-run count check
- inventories 15113 rows == function_classes 15113 rows, identical RVA set [V after edit; only 2 class cells changed].
- functions.tsv: 15210 lines (15209 data), D0=15005 / D1=74 / D2=130 [V wc + status tally; unchanged this sitting].
- All 15113 inventory functions are on disk in functions.tsv as D0 (14968 appended) or already D1/D2 (145 skipped).

## Proof (verbatim `0xRVA  instr` lines from rdis on the exe)
| offset | size | site | verbatim `0xRVA  instr` line | meaning | tag |
|---|---|---|---|---|---|
| 0x56ad350 | 0xf6 | closure-body entry (DepthAndNormal lambda) | `0x56ad350  push rsi` | lambda test-set member; reclassified entry-indirect -> lambda | [V rdis + vv_closures] |
| 0x56aeeb0 | 0x123 | closure-body entry (NothingTask-type lambda) | `0x56aeeb0  push r15` | lambda test-set member; reclassified leaf -> lambda | [V rdis + vv_closures] |
| 0x558134a | - | L6 code below 0x55f0000 boundary | `0x558134a  lea rdx,[0xF59F616]` | references command string "commands.hasitem.fail.noItem" -> noise side | [V rdis + xref str] |
| 0x5500590 | 0x34 | L6 entry below boundary (noise side) | `0x5500590  mov [rsp+0x10],rdx` | L6 renderer entry in noise range; size per inventory | [V rdis + inventory] |
| 0x55f1450 | 0x4e144 | VV frame-graph builder entry, render side | `0x55f1450  push rbp` | at/above 0x55f0000; size per BGFX_MAP 350 | [V rdis + BGFX_MAP] |
| 0x670b6e0 | 0x8584 | RenderChunkFogAlpha builder entry | `0x670b6e0  push rbp` | direct callee of 0x66ea3d0 (rdis callees) -> L5 draw-builder name | [V rdis + inventory size] |

## What changed on disk
- docs/data/function_classes.tsv: class cell of 0x56ad350 and 0x56aeeb0 set to lambda (2 rows).
- docs/progress/oc_U-EM1b.md: this note.
- Nothing else: no builds, no game launch/attach, no edits to Sigs.json/CMake/HookManager.cpp/hook registrations.

## CLOSES?
NO — blocking fact: the exhaustive D0 listing is on disk for all 15113 functions, but classification is incomplete (entry-indirect still 6249 effectively unclassified; 'lambda' exists now with only 2 verified members, and 28 of the 30 documented VV/RTX closure bodies are outside the inventoried regions) and the names/call-graph layer split for the D0 rows is not done — only the 8 big render functions are named plus caller-verified samples, so the item's own wording ("list EVERY function ... then classify") is not met on disk.

## TOOL REQUESTS
- None.
