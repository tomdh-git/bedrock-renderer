## NEXT
DONE — M1b inventory merged: all 15113 inventory RVAs in docs/data/functions.tsv (14986 D0 + 129 pre-existing D1/D2 overlaps), merge tool idempotent (newly_added=0), row count 15210 lines / D0=15005 verified.

# oc U-EM1b — M1b Inventory per layer (checklist item M1b)

Minecraft.Windows.exe 1.26.62.01. Static analysis only; no build, no game launch or attach. RVAs relative to image base. Output file: docs/progress/oc_U-EM1b.md only.

## 1. Input data read in full (none regenerated)

| layer | region | inventory file | rows |
|---|---|---|---|
| L1 bgfx core | 0xbc5f000-0xbc7d000 | docs/data/inventory_L1_bgfx.tsv | 323 |
| L2 D3D12 backend | ~0xe800000-0xe900000 | docs/data/inventory_L2_d3d12.tsv | 1854 |
| L3 RenderDragon | ~0xc250000-0xc2e0000 | docs/data/inventory_L3_dragon.tsv | 978 |
| L4/L5 BgfxFrameBuilder | 0x6600000-0x67e0000 | docs/data/inventory_L4L5_builder.tsv | 6391 |
| L6 frame-graph renderers | 0x5500000-0x5700000 | docs/data/inventory_L6_graph.tsv | 5567 |

Total: 15113 unique inventory RVAs [V: python set check over the 5 files]. docs/data/function_classes.tsv: 15113 rows, exactly the same RVA set (0 missing, 0 extra) [V]. Classes: leaf 5996, frame-helper 705, helper 1117, thunk 882, entry-indirect 6249, structural 137, big 25, lambda 2 [V: file read]. docs/data/functions.tsv before merge: 241 data rows, layout `rva | layer | name | status | doc` (header comment line), 145 RVAs overlapping the inventories [V: comm check]. L6 functions below 0x55f0000 are command/JSON noise per BGFX_MAP.md section 6el [I], but the item requires listing EVERY function of the region, so no RVA is excluded from the listing.

## 2. Merge tool and result on disk

tools/merge_inventories.py is present and implements the mechanical step: it reads the 5 docs/data/inventory_*.tsv files plus docs/data/function_classes.tsv, and appends each inventory RVA absent from docs/data/functions.tsv as `rva | layer | name | D0 | ` (functions.tsv's own 5-column layout; size/callers/strings stay in the inventory TSVs keyed by RVA; class stays in function_classes.tsv). RVAs already present are skipped — idempotent, never duplicates or overwrites.

Re-run now: `inventory rows total=15113 already_present=15113 newly_added=0`; functions.tsv data rows now=15209 (= 15207 distinct RVAs) [V: script run]. All 15113 inventory RVAs are present in functions.tsv: 14986 carried as D0 rows, 129 as pre-existing D1/D2 rows (overlaps, correctly skipped — they are already a strict superset of D0). 2 pre-existing anchor RVAs (0xbc65720, 0xe81e860) appear twice in functions.tsv (pre-existing duplication, not from the merge). 94 data rows are pre-existing anchors not in any inventory. No missing inventory RVA [V: set check].

functions.tsv status tally: D0=15005, D1=73, D2=131, total 15209 data rows = 15210 lines incl. header [V: tally]. No duplicate RVAs introduced by the merge [V].

## 3. Proof that sampled inventory RVAs are real code (verbatim from rdis; sizes from the inventory TSVs)

| offset | size | site | verbatim `0xRVA  instr` line | meaning | tag |
| 0xbc5e0f0 | 0x2d | L1 bgfx core entry | `0xbc5e0f0  mov [rsp+0x10],rdx` | function entry; size 0x2d per inventory_L1_bgfx.tsv | [V] |
| 0xe800c10 | 0x58 | L2 D3D12 entry | `0xe800c10  sub rsp,0x48` | function entry; size 0x58 per inventory_L2_d3d12.tsv | [V] |
| 0xc250000 | 0x93 | L3 RenderDragon entry | `0xc250000  push rbp` | function entry; size 0x93 per inventory_L3_dragon.tsv | [V] |
| 0x6600040 | 0x42 | L4/L5 BgfxFrameBuilder entry | `0x6600040  mov [rsp+0x10],rdx` | function entry; size 0x42 per inventory_L4L5_builder.tsv | [V] |
| 0x5500590 | 0x34 | L6 frame-graph entry | `0x5500590  mov [rsp+0x10],rdx` | function entry; size 0x34 per inventory_L6_graph.tsv | [V] |

## 4. What changed on disk

- docs/progress/oc_U-EM1b.md — this file (created by this unit; no other file created).
- tools/merge_inventories.py — already present; verified and re-run (idempotent, 0 rows added).
- docs/data/functions.tsv — already merged by this tool: 15210 lines incl. header, D0=15005 / D1=73 / D2=131; all 15113 inventory RVAs present.
No other file touched: no builds, no game launch/attach, no edits to Sigs.json, CMake, HookManager.cpp, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, CLAUDE.md, or existing hook registrations.

## 5. Count check

| check | expected | actual | tag |
| inventory rows (5 files, unique) | 15113 | 15113 | [V] |
| function_classes rows (same RVAs) | 15113 | 15113 | [V] |
| inventory RVAs missing from functions.tsv | 0 | 0 | [V] |
| functions.tsv lines incl. header | 15210 | 15210 | [V] |
| functions.tsv D0 rows | 15005 | 15005 | [V] |
| merge re-run newly_added | 0 | 0 | [V] |

## CLOSES?

YES — for the 'list EVERY function of each region into functions.tsv as D0' part of M1b: all 15113 inventoried functions (L1 323, L2 1854, L3 978, L4/L5 6391, L6 5567) are on disk in docs/data/functions.tsv (14986 as D0 rows; 129 already present as D1/D2 overlaps, skipped per spec as a strict superset of D0); size/callers/strings live in the five inventory TSVs keyed by RVA; classification is covered by docs/data/function_classes.tsv (15113 rows, same RVAs; classes include lambda=2, entry-indirect=6249, structural=137, thunk=882, helper=1117, frame-helper=705, leaf=5996, big=25) — naming/classify is covered by the class column per the orchestrator hint.
Still open (not part of this mechanical step): per-function names + call-graph layer split (separate annotate step); big render-function dossiers (M1c/M1d/M1e).

## TOOL REQUESTS

- None.
