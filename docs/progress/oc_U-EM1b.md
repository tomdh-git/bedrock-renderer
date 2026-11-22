## NEXT
DONE

# oc U-EM1b — M1b Inventory per layer (checklist item M1b, still `- [ ]`)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only; no build, no game launch or attach.
Input data read in full (all precomputed by the orchestrator, not regenerated):
- docs/data/inventory_L1_bgfx.tsv (323), inventory_L2_d3d12.tsv (1854), inventory_L3_dragon.tsv (978),
  inventory_L4L5_builder.tsv (6391, rva 0x6600000-0x67e0000), inventory_L6_graph.tsv (5567, rva 0x5500000-0x5700000)
- docs/data/function_classes.tsv (15113 rows = 323+1854+978+6391+5567 [V per data files])
- docs/data/functions.tsv (234 named rows before this unit; 242 after)
- docs/BGFX_MAP.md section 6el (M1b inventories; L6 rows below 0x55f0000 are command/JSON noise, not render passes [I])

Inventory columns: rva | size | layer | class | ncallers | callers3 | ncallees | strings2 | vcalls | name | status; all status D0.

## 1. Inventory status per layer

| layer | region | inventory file | rows | status |
|---|---|---|---|---|
| L1 bgfx core | 0xbc5f000-0xbc7d000 | docs/data/inventory_L1_bgfx.tsv | 323 | D0 |
| L2 D3D12 backend | approx 0xe800000-0xe900000 | docs/data/inventory_L2_d3d12.tsv | 1854 | D0 |
| L3 RenderDragon | approx 0xc250000-0xc2e0000 | docs/data/inventory_L3_dragon.tsv | 978 | D0 |
| L4/L5 BgfxFrameBuilder | 0x6600000-0x67e0000 | docs/data/inventory_L4L5_builder.tsv | 6391 | D0 |
| L6 frame-graph renderers | 0x5500000-0x5700000 | docs/data/inventory_L6_graph.tsv | 5567 | D0 |

L1 region bound is from BGFX_MAP.md section 1 [V]; L2/L3 bounds are approximate [I] (first/last inventory rows). Counts match the checklist progress line exactly [V per data files]. L6: the ~0xF0000 bytes below 0x55f0000 are command/JSON parsing (strings "commands.hasitem.fail.noItem", "format_version", "Missing rule derivation"), not render passes; pass bodies start at the giant 0x55f1450 [I per 6el].

## 2. Classification (inventory class -> item taxonomy: structural / helper / lambda / thunk) [I mapping]

Class counts across all 15,113 functions [V per function_classes.tsv]:

| class | count | mapped taxonomy |
| entry-indirect | 6250 | lambda [I] |
| leaf | 5997 | helper [I] |
| helper | 1117 | helper [I] |
| frame-helper | 705 | helper [I] |
| thunk | 882 | thunk [V mechanical — class name matches taxonomy] |
| structural | 137 | structural [V mechanical] |
| big | 25 | helper by size [I] |

"big" (25 functions, incl. 0x56e1990) are outsized non-thunk bodies; mapped to helper [I] pending per-function dossiers. Name and layer annotations do not come from the inventory itself; both are [I] (name from string analysis of the function, layer from address region/caller).

## 3. Rows added to docs/data/functions.tsv (8 big render functions missing from the anchor list)

Appended (tab-separated: rva | layer | name | status | doc), all status D0, names [I] from inventory string analysis, layers [I] by caller/region:

| rva | size | layer | name | callers | strings2 | callees | vcalls | class | doc |
|---|---|---|---|---|---|---|---|---|---|
| 0x670b6e0 | 0x8584 | L5 | RenderChunkFogAlpha draw-builder | 0x66ea3d0 | 2 | 49 | 1 | frame-helper -> helper | 6el |
| 0x6722cb0 | 0x77b4 | L5 | RenderChunkFogAlpha draw-builder | 0x66ea3d0 | 1 | 50 | 1 | frame-helper -> helper | 6el |
| 0x67762e0 | 0x7e86 | L5 | RenderChunkFogAlpha draw-builder | 0x66ea3d0 | 1 | 50 | 1 | frame-helper -> helper | 6el |
| 0x6792d90 | 0x7794 | L5 | RenderChunkFogAlpha draw-builder | 0x66ea3d0 | 1 | 50 | 1 | frame-helper -> helper | 6el |
| 0x67aa700 | 0x2cae | L5 | RenderChunkFogAlpha draw-builder | 0x66ea3d0 | 2 | 33 | 2 | frame-helper -> helper | 6el |
| 0x66a6830 | 0x2097 | L5 | Shadow volume builder (ShadowVolume|ShadowOverlay) | 0x666aca0 | 1 | 34 | 1 | frame-helper -> helper | 6el |
| 0x56a06a0 | 0x4b94 | L6 | SkyProbeDeferredShading / DoDeferredShading pass body | 0x55f1450 | 1 | 41 | 1 | frame-helper -> helper | 6el |
| 0x56e1990 | 0x33c0 | L6 | Upscaling pass execute | none (0 callers) | 1 | 17 | 1 | big -> helper | 6el |

Layer rationale [I]: the five RenderChunkFogAlpha functions and the shadow volume builder are called by L5 functions (0x66ea3d0, 0x666aca0); SkyProbe is called by the L6 VV builder 0x55f1450; Upscaling has no callers and lives in the L6 region. String contents are not in the inventory (strings2 is a count only) [?].

## 4. Verified entry-proof rows ([V] instruction lines from rdis)

| offset | size | site | verbatim `0xRVA  instr` line | meaning |
|---|---|---|---|---|
| 0x670b6e0 (entry proof) | 0x8584 | entry (called by 0x66ea3d0 [I]) | `0x670b6e0  push rbp` | - |
| 0x6722cb0 (entry proof) | 0x77b4 | entry (called by 0x66ea3d0 [I]) | `0x6722cb0  push rbp` | - |
| 0x67762e0 (entry proof) | 0x7e86 | entry (called by 0x66ea3d0 [I]) | `0x67762e0  push rbp` | - |
| 0x6792d90 (entry proof) | 0x7794 | entry (called by 0x66ea3d0 [I]) | `0x6792d90  push rbp` | - |
| 0x67aa700 (entry proof) | 0x2cae | entry (called by 0x66ea3d0 [I]) | `0x67aa700  push rbp` | - |
| 0x66a6830 (entry proof) | 0x2097 | entry (called by 0x666aca0 [I]) | `0x66a6830  push rbp` | - |
| 0x56a06a0 (entry proof) | 0x4b94 | entry (called by 0x55f1450 [I]) | `0x56a06a0  push rbp` | - |
| 0x56e1990 (entry proof) | 0x33c0 | entry (no callers) | `0x56e1990  push rbp` | - |

`push rbp` is a standard prologue; no instruction or string in the entry shows a semantic meaning, so meaning is `-` per the rules. Sizes are from the inventory TSVs [I mechanical]; the movups/movaps/movdqu/movdqa/movss/movsd size rules do not apply (no such instruction claimed).

## 5. What changed on disk

- docs/data/functions.tsv: appended 8 rows (section 3), all status D0. Row count 234 -> 242.
- docs/progress/oc_U-EM1b.md: this note.

Nothing else was touched: no builds, no game launch/attach, no edits to Sigs.json, CMake, HookManager.cpp, or any existing hook registration.

## CLOSES?

NO — blocking fact: the item's full wording ("list EVERY function of each region into functions.tsv as D0 with size, callers, strings; then classify (structural/helper/lambda/thunk)") is not met by what exists on disk now: docs/data/functions.tsv holds 234 named anchor rows (242 with the 8 added); the exhaustive per-function D0 listing with size/callers/strings for all ~15,113 inventory functions exists only in the five layer inventory TSVs (with classifications in docs/data/function_classes.tsv), not consolidated into functions.tsv; and name + layer-split annotations remain [I] (the L4/L5/L6 call-graph layer split is not proven). Exact remaining step: append the remaining inventory rows to functions.tsv (D0, size/callers/strings from the TSVs, ~15k rows — beyond one unit sitting; split by layer) or re-scope the checklist item to treat the inventory TSVs as the D0 listing.

## TOOL REQUESTS

- None.
