## NEXT
DONE

# oc U-EM1b — M1b Inventory per layer (checklist item M1b)

## 1. Input data read (fully, none regenerated)
- docs/data/inventory_L1_bgfx.tsv — 323 rows (L1 bgfx core) [V: wc -l = 324 incl. header]
- docs/data/inventory_L2_d3d12.tsv — 1854 rows (L2 D3D12) [V: wc -l = 1855 incl. header]
- docs/data/inventory_L3_dragon.tsv — 978 rows (L3 RenderDragon) [V: wc -l = 979 incl. header]
- docs/data/inventory_L4L5_builder.tsv — 6391 rows (L4/L5 BgfxFrameBuilder, region 0x6600000-0x67e0000) [V: wc -l = 6392 incl. header]
- docs/data/inventory_L6_graph.tsv — 5567 rows (L6 frame-graph renderers, region 0x5500000-0x5700000) [V: wc -l = 5568 incl. header]
- Total inventory rows: 323+1854+978+6391+5567 = 15113, all unique RVAs [V: python set check]
- docs/data/function_classes.tsv — 15113 rows, exactly the same RVA set as the 5 inventories (0 missing, 0 extra); column `class` = structural / frame-helper / helper / leaf / thunk / entry-indirect / lambda / big [V]
- docs/data/functions.tsv — pre-existing 241 data rows, layout `rva | layer | name | status | doc`; 145 RVAs overlap the inventories and are skipped (already D1/D2) [V: comm check]

## 2. Merge done — new tool tools/merge_inventories.py
- Appends every inventory row into docs/data/functions.tsv in functions.tsv's own 5-column layout `rva | layer | name | status | doc`, status = D0, skipping RVAs already present.
- `name`: function_classes.tsv name if non-empty, else inventory name if non-empty, else empty (D0 = unnamed by design; naming is the separate annotate step). `doc`: empty. `class` from function_classes.tsv stays there (classification column); size, callers, strings stay in inventory TSVs keyed by RVA.
- Result [V]: 15113 inventory rows total; 145 skipped (already D1/D2, e.g. 0xbc60740 Encoder::submit D2, 0xe82e230 D3D12 submit slot 50, 0xc273420 generate); 14968 appended.
- functions.tsv: 241 data rows before -> 15209 after (15210 lines incl. header); D0=15005, D1=74, D2=130 (= 37 pre-existing D0 + 14968 appended). No duplicate RVAs. [V: wc -l + status tally]
- Sample appended rows: `0xbc5e0f0	L1		D0	`; `0x6600040	L4L5_builder		D0	`; `0x5500590	L6_graph		D0	`.

## 3. Proof that sampled inventory RVAs are real code (verbatim from rdis, matches inventory sizes)
| # | offset | size | site | instr | meaning | tag |
| 1 | 0xbc5e0f0 | 0x2d | - | `0xbc5e0f0  mov [rsp+0x10],rdx` | L1 bgfx core function entry; size 0x2d per inventory_L1_bgfx.tsv | [V] |
| 2 | 0xe800c10 | 0x58 | - | `0xe800c10  sub rsp,0x48` | L2 D3D12 function entry; size 0x58 per inventory_L2_d3d12.tsv | [V] |
| 3 | 0xc250000 | 0x93 | - | `0xc250000  push rbp` | L3 RenderDragon function entry; size 0x93 per inventory_L3_dragon.tsv | [V] |
| 4 | 0x6600040 | 0x42 | - | `0x6600040  mov [rsp+0x10],rdx` | L4L5 BgfxFrameBuilder function entry; size 0x42 per inventory_L4L5_builder.tsv | [V] |
| 5 | 0x5500590 | 0x34 | - | `0x5500590  mov [rsp+0x10],rdx` | L6 frame-graph renderer entry (indirect-entry); size 0x34 per inventory_L6_graph.tsv | [V] |

## CLOSES?
YES — every function of all 5 regions listed in functions.tsv as D0: 14968 appended + 145 already present as D1/D2 = all 15113 inventory functions on disk; classification covered by class column of function_classes.tsv (15113 rows, same RVAs). Row count verified on disk: 15209 data rows (15210 lines incl. header), D0=15005 / D1=74 / D2=130. delegate.py check exits 0 (verify_oc: all 5 verbatim instruction lines match rdis).
Out of scope for this mechanical step (remain open): per-function names + call-graph layer split (annotate step); big render-function dossiers (M1c/M1d/M1e).
