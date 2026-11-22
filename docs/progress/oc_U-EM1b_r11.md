## NEXT
DONE — M1b verified on docs/progress/oc_U-EM1b.md: all 15113 inventory RVAs in docs/data/functions.tsv (D0=15005), merge idempotent (newly_added=0), lambda class present (0x56ad350, 0x56aeeb0), L6 noise quantified (clean >=0x55f0000 = 2492); CLOSES? NO — classify/annotate open.

# oc U-EM1b — M1b Inventory per layer (checklist item M1b)

Minecraft.Windows.exe 1.26.62.01. Static analysis only; no build, no game launch or attach. RVAs relative to image base. Output file: docs/progress/oc_U-EM1b.md only. Proof lines are verbatim from `rdis.exe dis <rva>` for the exe and re-checked by `tools/sigs/verify_oc.py`.

## 1. Input data read in full (none regenerated)

| layer | region | inventory file | rows |
|---|---|---|---|
| L1 bgfx core | 0xbc5f000-0xbc7d000 | docs/data/inventory_L1_bgfx.tsv | 323 |
| L2 D3D12 backend | ~0xe800000-0xe900000 | docs/data/inventory_L2_d3d12.tsv | 1854 |
| L3 RenderDragon | ~0xc250000-0xc2e0000 | docs/data/inventory_L3_dragon.tsv | 978 |
| L4/L5 BgfxFrameBuilder | 0x6600000-0x67e0000 | docs/data/inventory_L4L5_builder.tsv | 6391 |
| L6 frame-graph renderers | 0x5500000-0x5700000 | docs/data/inventory_L6_graph.tsv | 5567 |

Total: 15113 unique inventory RVAs [V: set check over the 5 files]. docs/data/function_classes.tsv: 15113 rows, exactly the same RVA set [V]. Classes [V: file read]: leaf 5996, entry-indirect 6249, helper 1117, frame-helper 705, thunk 882, structural 137, big 25, lambda 2. All 25 big render-function RVAs are present in docs/data/functions.tsv [V: membership check].

## 2. Merge — mechanical step (orchestrator hint), already on disk and re-verified idempotent

tools/merge_inventories.py is present and appends each inventory RVA absent from docs/data/functions.tsv as `rva | layer | name | D0 | ` (functions.tsv's own 5-column layout; size/callers/strings stay in the five inventory TSVs keyed by RVA; class stays in function_classes.tsv). RVAs already present are skipped — idempotent, never duplicates or overwrites.

Re-run this session: `inventory rows total=15113 already_present=15113 newly_added=0`; functions.tsv data rows now=15209 (15207 distinct RVAs) [V: script run]. All 15113 inventory RVAs are present in functions.tsv: 15005 carried as D0 rows, the remaining inventory RVAs present as pre-existing D1/D2 rows correctly skipped by the merge [V: tally + set check]. functions.tsv: D0=15005 / D1=73 / D2=131, 15210 lines incl. header [V].

No build, no game launch/attach. Nothing else touched: no edits to Sigs.json, CMake, HookManager.cpp, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, CLAUDE.md, or any existing hook registration.

## 3. Classify — lambda class present [V]; entry-indirect split remains open

function_classes.tsv already contains a lambda class (2 rows), both from the VV/RTX pass test set (vv_closures.txt): 0x56ad350 size 0xf6 = DepthAndNormal draw-list body, and 0x56aeeb0 size 0x123 = NothingTask-type small body; both are class=lambda with status D0 [V: function_classes.tsv + vv_closures.txt read; the two bodies are listed in vv_closures.txt as closure vtable slot 2 bodies]. The other test-set bodies lie outside the inventoried regions and are not in function_classes.tsv [V: membership check over the 33 bodies parsed from vv_closures.txt]. entry-indirect = 6249 rows remain unsplit; per the orchestrator hint, naming/classify is covered by the class column. Structural 137 / helper 1117 / thunk 882 classes exist [V: file read].

## 4. L6 noise — identified and quantified [V]

BGFX_MAP.md section 6el: functions below ~0x55f0000 in the L6 region are command/JSON parsing, not render passes; filter by address >= 0x55f0000 ([I] region meaning, verified mechanically below).

Verified counts over docs/data/inventory_L6_graph.tsv [V: Python count over the file]:
- region 0x5500000-0x5700000: 5567 functions
- below 0x55f0000 (~0xF0000 bytes): 3075 functions / 943694 bytes — command/JSON noise
- >= 0x55f0000 (clean L6 render functions): 2492 functions / 1080686 bytes

Noise strings verified referenced by functions below 0x55f0000 [V: rdis str]:
- "commands.hasitem.fail.noItem" referenced inside sub_557fd00 (0x557fd00 < 0x55f0000)
- "Missing rule derivation, rule: %s, derivation: %s" referenced inside sub_5587ac0 (0x5587ac0 < 0x55f0000)

The full listing is kept (every function of the region is listed, per the GOAL wording — the listing is not redone); the clean render count is reported separately. The verified clean L6 count is 2492 functions, not the ~3600 estimate — the estimate was too high.

## 5. Names / layer split by call graph — OPEN

Still open per the checklist PROGRESS line and BGFX_MAP.md 6el: splitting L4/L5/L6 proper needs the call graph, not an address range [I]. No call-graph layer annotation exists on disk for the inventories; not done in this unit.

## 6. Proof rows (verbatim from rdis; sizes from the inventory / function_classes TSVs)

| rva | size | layer | site | first instruction | meaning | tag |
|---|---|---|---|---|---|---|
| 0xbc5e0f0 | 0x2d | L1 | L1 inventory entry | `0xbc5e0f0  mov [rsp+0x10],rdx` | function entry; size 0x2d per inventory_L1_bgfx.tsv | [V] |
| 0xe800c10 | 0x58 | L2 | L2 inventory entry | `0xe800c10  sub rsp,0x48` | function entry; size 0x58 per inventory_L2_d3d12.tsv | [V] |
| 0xc250000 | 0x93 | L3 | L3 inventory entry | `0xc250000  push rbp` | function entry; size 0x93 per inventory_L3_dragon.tsv | [V] |
| 0x6600040 | 0x42 | L4/L5 | L4/L5 inventory entry | `0x6600040  mov [rsp+0x10],rdx` | function entry; size 0x42 per inventory_L4L5_builder.tsv | [V] |
| 0x5500590 | 0x34 | L6_graph | L6 inventory entry (noise range) | `0x5500590  mov [rsp+0x10],rdx` | function entry; size 0x34 per inventory_L6_graph.tsv | [V] |
| 0x55f1450 | 0x4e144 | L6_graph | L6 clean VV frame-graph builder | `0x55f1450  push rbp` | giant pass body "Shadow Cascades"; size 0x4e144 per inventory_L6_graph.tsv; name "VV frame-graph builder (giant)" | [V] |
| 0x56ad350 | 0xf6 | L6_graph | lambda body (DepthAndNormal) | `0x56ad350  push rsi` | class=lambda per function_classes.tsv; body in vv_closures.txt test set | [V] |
| 0x56aeeb0 | 0x123 | L6_graph | lambda body (NothingTask-type) | `0x56aeeb0  push r15` | class=lambda per function_classes.tsv; body in vv_closures.txt test set | [V] |

Every `0xRVA  instr` line above was copied verbatim from `rdis.exe dis <rva> 2` output for Minecraft.Windows.exe 1.26.62.01 and re-checked by verify_oc [V].

## 7. Count check

| check | expected | actual | tag |
|---|---|---|---|
| inventory rows, 5 files, unique | 15113 | 15113 | [V] |
| function_classes rows (same RVAs) | 15113 | 15113 | [V] |
| inventory RVAs missing from functions.tsv | 0 | 0 | [V] |
| functions.tsv lines incl. header | 15210 | 15210 | [V] |
| functions.tsv D0 rows | 15005 | 15005 | [V] |
| merge re-run newly_added | 0 | 0 | [V] |
| big render-function RVAs in functions.tsv | 25 | 25 | [V] |
| L6 clean functions >= 0x55f0000 | - | 2492 | [V] |
| L6 noise functions < 0x55f0000 | - | 3075 | [V] |

## 8. What changed on disk

- docs/progress/oc_U-EM1b.md — this file (unit output; no other progress file created).
- docs/data/functions.tsv — already merged by tools/merge_inventories.py (earlier session); re-run this session confirms idempotent: newly_added=0; 15210 lines / D0=15005 / D1=73 / D2=131; all 15113 inventory RVAs present.
- tools/merge_inventories.py — present and idempotent; no change needed.

## CLOSES?

NO — single blocking fact: the M1b classify/annotate step is not complete on disk: entry-indirect = 6249 rows are not split further (only the 2 in-scope VV/RTX lambda bodies are class=lambda) and the names/layer split by call graph is open (BGFX_MAP 6el requires the call graph); additionally verified clean L6 = 2492 functions, not ~3600. The 'list EVERY function into functions.tsv as D0' part IS met: all 15113 inventory RVAs present (15005 D0; the rest as pre-existing D1/D2 rows).

## TOOL REQUESTS

- None.
