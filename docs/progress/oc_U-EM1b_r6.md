## NEXT
DONE

# oc U-EM1b — M1b Inventory per layer: merge check, lambda class, L6 noise filter, count check

## 1. What changed

Only docs/progress/oc_U-EM1b.md (this note). tools/merge_inventories.py already existed and is idempotent; no on-disk code change was needed. docs/data/functions.tsv, docs/data/inventory_*.tsv, docs/data/function_classes.tsv untouched this sitting. No builds, no game launch/attach, no src edits.

## 2. Inventory merge into docs/data/functions.tsv (mechanical, ORCHESTRATOR HINT)

tools/merge_inventories.py re-run: total=15113, already_present=15113, newly_added=0. It appends each RVA from the 5 docs/data/inventory_*.tsv files (class/name from function_classes.tsv) not already in functions.tsv, status D0, layout `rva | layer | name | status | doc`, never duplicates.

docs/data/functions.tsv on disk: 15210 lines = header + 15209 data rows; D0=15005 / D1=74 / D2=130. All 15113 inventory RVAs are present. The listing is complete and was NOT redone (per instructions).

Inventory rows: L1 323, L2 1854, L3 978, L4L5_builder 6391, L6_graph 5567 (region 0x5500000-0x5700000). Columns rva|size|layer|class|ncallers|callers3|ncallees|strings2|vcalls|name|status — size/callers/strings live here, keyed by RVA.

function_classes.tsv: 15113 rows, identical RVA set to the inventories (verified 15113/15113). Classes: leaf 5996 / entry-indirect 6249 / helper 1117 / thunk 882 / structural 137 / big 25 / frame-helper 705 / lambda 2.

## 3. Lambda class + split entry-indirect

class lambda exists with 2 verified members (class edits done in prior sitting r5):
- 0x56ad350: entry-indirect -> lambda, size 0xf6, DepthAndNormal closure body
- 0x56aeeb0: leaf -> lambda, size 0x123, NothingTask-type body

entry-indirect remains 6249 (unclassified in effect). Splitting entry-indirect beyond these 2 members requires closure bodies outside the inventoried regions — see coverage extension below; not invented here.

Test set = VV/RTX pass lambdas of M1e per docs/data/vv_closures.txt: 33 documented rows / 31 unique bodies (2 garbled), 29 clean bodies; only 0x56ad350 and 0x56aeeb0 sit inside inventoried regions; the other 27 clean 0xbc* bodies are absent from all inventories / function_classes.tsv / functions.tsv (verified per-RVA) -> coverage extension, separate item, NOT counted here.

## 4. Names / layer split by call graph

D0 rows are unnamed by design (~14968 unnamed D0 rows). Only big render functions plus verified samples are named (partial evidence: rdis callees of 0x66ea3d0 call sub_670b6e0 x1, sub_6722cb0 x1, sub_67762e0 x1). Annotate step still open.

## 5. L6 noise exclusion

docs/BGFX_MAP.md 6el: functions below 0x55f0000 in inventory_L6_graph.tsv are command/JSON parsing noise (~0xF0000 bytes). Documented filter at count time: rva >= 0x55f0000; listing rows are NOT deleted ("do not redo the listing").

Measured from docs/data/inventory_L6_graph.tsv: rows <0x55f0000 = 3075 rows total size 0xE664E (~0xF0000 matches BGFX_MAP) [V]; rows >=0x55f0000 = 2492 render-relevant [V]. Checklist estimate ~3600 NOT reproduced -> discrepancy flagged [I].

Noise side proven [V]: 0x558134a `lea rdx,[0xF59F616]` references "commands.hasitem.fail.noItem"; xref str "commands.hasitem.fail.noItem" -> refs 0x558134a and 0x557fd00, both below 0x55f0000.

## 6. Count check

- inventories == function_classes.tsv == 15113 RVAs [V both files].
- docs/data/functions.tsv data rows = 15209 (15210 lines incl. header; D0 15005 / D1 74 / D2 130) [V].
- L6 filtered render-relevant = 2492 with filter rva >= 0x55f0000 [V inventory_L6_graph.tsv].

## 7. Proof table (verbatim instructions)

| offset | size | verbatim `0xRVA  instr` proof line | meaning |
| 0x56ad350 | 0xf6 | `0x56ad350  push rsi` | DepthAndNormal closure body; class lambda [V rdis dis + function_classes.tsv] |
| 0x56aeeb0 | 0x123 | `0x56aeeb0  push r15` | NothingTask-type body; class lambda [V rdis dis + function_classes.tsv] |
| 0x55f1450 | 0x4e144 | `0x55f1450  push rbp` | VV frame-graph builder giant; size per inventory/BGFX_MAP 350 [V rdis dis + inventory] |
| 0x5500590 | 0x34 | `0x5500590  mov [rsp+0x10],rdx` | L6 noise-side entry below 0x55f0000 [V rdis dis + inventory] |
| 0x558134a | - | `0x558134a  lea rdx,[0xF59F616]` | references "commands.hasitem.fail.noItem"; both xref refs below 0x55f0000 => L6 noise side [V rdis dis + xref str] |

No duplicate offsets. No ellipsis or abbreviation used anywhere in this file.

## CLOSES?

NO. The listing part ("list EVERY function of each region into functions.tsv as D0 with size, callers, strings") IS met: all 15113 inventory RVAs present as D0 with size/callers/strings from the inventories and class column from function_classes.tsv; merge verified idempotent.

The classify part is NOT met. Single blocking fact: classify incomplete — 6249 rows are still entry-indirect (unclassified in effect; lambda split covers only 2 verified members, the rest of the M1e test set lies outside inventoried regions), names/layer split by call graph is open, and the L6 ~3600 count discrepancy remains unresolved [I].

## TOOL REQUESTS

None.
