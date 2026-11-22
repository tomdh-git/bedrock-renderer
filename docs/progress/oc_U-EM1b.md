## NEXT
DONE

# oc U-EM1b — M1b Inventory per layer (checklist item M1b)

## Source and constraints
- Binary: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Treated as data only: passed to rdis as an argument, never launched, never a shell command.
- Static analysis only. No build, no game launch/attach, no debugger/Cheat Engine/injector.
- No edits to HookManager.cpp, Sigs.json, CMake, existing hook registrations, CLAUDE.md, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md.
- Only file created: docs/progress/oc_U-EM1b.md (this note). tools/merge_inventories.py confirmed idempotent (re-run adds 0 rows).

## 1. Input data read (fully, none regenerated)
| file | rows | region |
|---|---|---|
| docs/data/inventory_L1_bgfx.tsv | 323 | L1 bgfx core (~0xbc5f000-0xbc7d000) |
| docs/data/inventory_L2_d3d12.tsv | 1854 | L2 D3D12 backend (~0xe800000-0xe900000) |
| docs/data/inventory_L3_dragon.tsv | 978 | L3 RenderDragon (~0xc250000-0xc2e0000) |
| docs/data/inventory_L4L5_builder.tsv | 6391 | L4/L5 BgfxFrameBuilder (0x6600000-0x67e0000) |
| docs/data/inventory_L6_graph.tsv | 5567 | L6 frame-graph renderers (0x5500000-0x5700000) |
| docs/data/function_classes.tsv | 15113 | class per RVA; RVA set == the 5 inventories |
| docs/data/functions.tsv | 15209 data rows | master list rva|layer|name|status|doc |
| docs/data/functions_full.tsv | 15113 rows | consolidated rva|size|layer|class|ncallers|callers3|strings2|status |

Total inventory rows: 323+1854+978+6391+5567 = 15113, all unique RVAs [V: set equality]. RVA set equality confirmed: function_classes.tsv == functions_full.tsv == inventory_union (fc==ff==inv, 0 missing, 0 extra), and every inventory RVA is present in functions.tsv [V: inv <= ftsv].

## 2. Listing: every function as D0 in functions.tsv (DONE)
tools/merge_inventories.py appends each inventory RVA absent from functions.tsv as a D0 row in functions.tsv's own layout (rva|layer|name|status|doc), skipping RVAs already present; the script is idempotent (re-run: total=15113 already_present=15113 newly_added=0) [V: script output].
- All 15113 inventory RVAs present in functions.tsv: 14968 appended as D0 + 145 already present as D1/D2 (skipped per spec) [V: inv <= ftsv].
- functions.tsv: 15209 data rows / 15210 lines incl. header; unique RVAs 15207 (2 pre-existing duplicate anchor rows); status tally D0=15005 / D1=73 / D2=131 [V: wc -l + tally]. Plus 94 non-inventory anchor rows (named functions not in any layer inventory).

## 3. size/callers/strings columns — met via docs/data/functions_full.tsv (r10 "or functions_full.tsv" option)
docs/data/functions_full.tsv holds rva|size|layer|class|ncallers|callers3|strings2|status for all 15113 functions, built from function_classes.tsv + the 5 inventory TSVs keyed by RVA. RVA set identical to functions.tsv's inventory subset [V: fc==ff]. So size/callers/strings are on disk for every inventoried function.

## 4. Proof: sampled inventory RVAs are real code (verbatim rdis entry instructions; sizes match the inventory TSVs)
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| 0xbc5e0f0 | 0x2d | - | `0xbc5e0f0  mov [rsp+0x10],rdx` | L1 bgfx core entry; size 0x2d per inventory_L1_bgfx.tsv [V] |
| 0xe800c10 | 0x58 | - | `0xe800c10  sub rsp,0x48` | L2 D3D12 entry; size 0x58 per inventory_L2_d3d12.tsv [V] |
| 0xc250000 | 0x93 | - | `0xc250000  push rbp` | L3 RenderDragon entry; size 0x93 per inventory_L3_dragon.tsv [V] |
| 0x6600040 | 0x42 | - | `0x6600040  mov [rsp+0x10],rdx` | L4/L5 BgfxFrameBuilder entry; size 0x42 per inventory_L4L5_builder.tsv [V] |
| 0x5500590 | 0x34 | - | `0x5500590  mov [rsp+0x10],rdx` | L6 frame-graph entry (indirect-entry); size 0x34 per inventory_L6_graph.tsv [V] |

Each `0xRVA  instr` line was copied from rdis `dis 0xRVA 1` output and matches verbatim (verified by tools/sigs/verify_oc.py) [V].

## 5. Classification vs the item wording (structural/helper/lambda/thunk) — NOT met
function_classes.tsv class distribution [V]:
| class | count | mapped to wording taxonomy |
|---|---|---|
| structural | 137 | structural |
| thunk | 882 | thunk |
| helper | 1117 | helper |
| frame-helper | 705 | helper (helper variant) [I] |
| leaf | 5996 | helper (leaf = no-callee body) [I] |
| big | 25 | helper (outsized body) [I] |
| lambda | 2 | lambda |
| entry-indirect | 6249 | UNRESOLVED — must be split into lambda/helper/thunk |

The wording requires a lambda class and a split of entry-indirect. r2 test set: the 35 VV/RTX pass lambdas of M1e (vtable/closure-call-operator pattern). That test set is not available on disk, so entry-indirect (6249 rows) cannot be split and lambda stays at 2 rows. [UNVERIFIED: 0xaddr the 35 M1e VV/RTX pass-lambda RVAs are not on disk]

## 6. L6 noise exclusion
L6 region 0x5500000-0x5700000 holds 5567 inventory functions. Per docs/BGFX_MAP.md section 6el, 0x5500000-0x55f0000 (~0xF0000 bytes) is command/JSON parsing noise (strings "commands.hasitem.fail.noItem", "format_version", "Missing rule derivation"), not render passes [I per 6el]. Data: 3075 L6 rows below 0x55f0000; excluding them leaves 2492 real render functions (dense cluster 0x5630000-0x5700000 = 2475; 0x55f0000-0x5600000 = 17). The checklist's ~3600 L6 figure is not matched by this inventory — boundary/estimate open [I].

## 7. Names / call-graph layer split — OPEN (annotate step, out of scope for this mechanical listing)

## What changed on disk
- docs/progress/oc_U-EM1b.md: this note (created).
- Confirmed on disk (no modification needed): tools/merge_inventories.py (idempotent), docs/data/functions.tsv (all 15113 inventory RVAs as D0/D1/D2), docs/data/functions_full.tsv (size/callers/strings/class for all 15113).
- No builds run, no game launched/attached, no protected files edited.

## CLOSES?
NO — single blocking fact: the item's classification wording "(structural / helper / lambda / thunk)" is not met by what exists on disk now. function_classes.tsv still uses leaf/entry-indirect/helper/thunk/frame-helper/structural/big; lambda has only 2 rows and the 6249 entry-indirect rows are not split into lambda/helper/thunk, because the M1e 35-VV/RTX pass-lambda test set (vtable/closure-call-operator pattern) is not available on disk to identify the lambdas. The listing part (every function as D0 with size/callers/strings via functions_full.tsv) IS met.

## TOOL REQUESTS
- None.
