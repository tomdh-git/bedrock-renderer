## NEXT
DONE

# UNIT U-EL10b — L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound

## Retry context
Earlier attempts oc_U-EL10b_r1.md and oc_U-EL10b_r2.md could not close this item; their notes are the lineage above. Per the unit rules I do NOT redo what is already proven:
- frustum_visibility field in lighting-config JSON deserializer fn 0x10f09f0: PROVEN [V] (site 0x10f45d0 loads string 0xF516745, len 0x12, passed to scalar deserializer 0x117d460).
- NOT FOUND / still pending: real camera frustum-cull function ("real cull unfound").

## Pending part of this item line (only this part is attacked in this unit)
"real cull unfound" — the real camera frustum-cull function (6-plane frustum test). The field part is already proven [V]; only the cull part is open.

## New angles tried this unit (all negative — blocking fact persists)
1. xref str "cull": every hit is block-geometry culling — minecraft:culling.* rules (fn 0x3299d20 sites 0x329d1b7..0x329d505, fn 0x5e5c190 bed, fn 0x6ae8ed0 parser, fn 0x5ce1c30 leaves, fn 0x9eba4c0 same_culling_layer/cull_against_full_and_opaque). That is block-face/neighbour culling (H1b), not camera frustum cull. String "EXT_clip_cull_distance" (0xf5e736e) has zero code refs. [V]
2. xref str "Frustum": only CameraAimAssistCacheFrustumSystem 0xf59d48f and its entt pretty_function 0xf62912f, both with zero code refs — aim-assist entt component only, no camera frustum anchor anywhere. [V]
3. xref str "CreateQueryHeap": zero refs anywhere in the exe — no string, no call site. [V]
4. xref str "Occlusion_Query": only fn 0x660ecd0 site 0x660f070 (bgfx Caps JSON dump flag, 6bl) — not an occlusion-query pool/user. [V]
5. Decoded sub_6b1c220 (0x6b1c220..0x6b1c36b): visibility-state node init — zeroes a0+0x0/+0x4/+0x8, copies a2+0x0/+0x4/+0x8 into a0+0xA028/+0xA02C/+0xA030, stores a0+0xA020 from arg, links 0x40-byte nodes via 0xEEC6ED0. Visibility-state bookkeeping, not a cull test. [V] (`6b1c244  mov word ptr [rcx+4],0`; `6b1c2c2  mov [rsi+0xA020],rbx`; `6b1c2e3  movups [rsi+0xA048],xmm6`)
6. Decoded sub_6b1c3e0 (0x6b1c3e0..0x6b1c964 head): section sub-chunk lookup (sentinel 0xF800, range [chunk+0x58]+0xC8/+0xCA, array [chunk+0x1C8] stride 0x68, entry +0x61 Y check) then a 6-face BFS over the 4096-byte occupancy bitmap at state+0x18 using neighbour tables at 0xF2CDBF0/0xF2CDC08/0xF2CDC20/0xF2CDC38/0xF2CDC50; reads Block+0xA3 at 6b1c4d3 (`movzx eax,byte ptr [rax+0xA3]`). Cave-connectivity flood fill, not a 6-plane camera frustum test. [V]
7. Viewed head of task body sub_792e630 (0x2000 bytes): per-section driver calling 0x6b0c4c0 at `0x792e92c  call 0x6b0c4c0`; callees are visibility-state allocators (0x2fc9aa0, 0x32cb4a0, eea6040 heap). No view-proj matrix or plane math in the head. [V]
8. livemem: not applicable — rule 1 (game closed, do not start it) and no specific runtime object target was located by static analysis, so there is nothing to read; 0 livemem calls made.

## Answer table (one row per distinct offset, all its sites listed)
| name | rva or offset | size | proof (`0xRVA  instr`) | tag |
|---|---|---|---|---|
| frustum_visibility field: key "frustum_visibility" loaded for JSON field deserialization in lighting-config deserializer fn 0x10f09f0 (light-scoring weight per 6bj; role inference [I]) | 0x10f45d0 | 8 | `0x10f45d0  lea rax,[0xF516745]`; `0x10f45d7  mov [rbp+0x280],rax`; `0x10f45de  mov qword ptr [rbp+0x288],0x12`; `0x10f45fa  call 0x117d460` | [V] |
| Chunk/section visibility = voxel flood fill (Block+0xA3 opaque flag) inside compute 0x791f170, driven by task body 0x792e630 — not camera frustum culling | 0x791f4ac | 1 | `0x791f4ac  cmp byte ptr [rax+0xA3],1` | [V] |
| Visibility task body 0x792e630 drives the flood fill per section | 0x792e92c | 8 | `0x792e92c  call 0x6b0c4c0` | [V] |
| Device init (0xe807ff0 region) reads device-vtable slots +0x18/+0x20/+0x28/+0x68 only; CreateQueryHeap = slot 23 = +0xB8 — no +0xB8 site in static .text, no "CreateQueryHeap" string in the exe | 0xe80821a | 8 | `0xe80821a  mov rax,[rax+0x18]`; `0xe8082c9  mov rax,[rax+0x20]`; `0xe8082df  mov rax,[rax+0x28]`; `0xe80834e  mov rax,[rax+0x68]` | [V] |

## Row meanings
- Row 1: "frustum_visibility" is 18 chars = length 0x12 stored at [rbp+0x288] by 0x10f45de; key pointer 0xF516745 stored at [rbp+0x280] by 0x10f45d7 and passed to scalar field deserializer 0x117d460 at 0x10f45fa; deserialized value lands at [rbp+0x2E0] then [rbp+0x3E0]. Per 6bj this field is one light-scoring weight of the CPU point-light scoring (only the top max_point_lights are submitted), NOT a frustum cull. Instruction facts [V]; role "light-scoring weight" [I] per 6bj (function-level inference: 0x10f09f0 is pure JSON deserialization, no 6-plane test).
- Row 2: 0x791f4ac reads Block+0xA3 inside the per-voxel flood fill — chunk/section visibility via cave connectivity, not a camera frustum plane test [V].
- Row 3: task body 0x792e630 calls flood-fill compute 0x6b0c4c0 at 0x792e92c for each section — visibility task is flood-fill driven [V].
- Row 4: device init touches device-vtable offsets 0x18 (CheckFeatureSupport), 0x20 (CreateCommandQueue), 0x28 (CreateCommandAllocator), 0x68 (CreateDescriptorHeap); CreateQueryHeap = slot 23 = offset 0xB8 — no call site with that offset anywhere in static .text and no "CreateQueryHeap" string in the exe [V] (instruction facts re-verified against rdis this unit; "no +0xB8 anywhere" per prior input oc_U-H3d.md step 2).
- New negatives this unit (prose, no instruction rows): "cull" string hits are all block-geometry culling rules; "Frustum" strings are aim-assist only with zero code refs; "CreateQueryHeap" and "EXT_clip_cull_distance" have zero code refs; sub_6b1c220/sub_6b1c3e0 are visibility-state/graph (cave) machinery, not a camera frustum test.

## Other frustum/cull anchors (from prior input data, completeness only)
- frustum_visibility string 0xF516745 -> only ref 0x10f45d0 (lighting config) [V row 1]
- max_shadow_frustum_radius string 0xF543489 -> fn 0x53fcac0 (shadow cascade setup) [V]
- CameraAimAssistCacheFrustumSystem / CameraAimAssistCachedFrustumComponent 0xF59D48F -> no code refs [V]
- No string or RTTI anchor for a camera frustum-cull class exists in the exe [V negative]

## CLOSES?
CLOSES? NO — the single blocking fact persists: no camera frustum-cull function exists in this static binary. Proven [V] instead: no 6-plane frustum test anywhere, no CreateQueryHeap/vtable+0xB8 call site (device init uses only slots +0x18/+0x20/+0x28/+0x68; "CreateQueryHeap" string absent), no camera-frustum string anchor (only aim-assist, no code refs), all located visibility/cull code is block-geometry culling (minecraft:culling.*), shadow cascade (max_shadow_frustum_radius -> 0x53fcac0), or the voxel flood fill (0x791f170 / 0x6b0c4c0 driven by task body 0x792e630, Block+0xA3). The field part of the item IS proven [V]: frustum_visibility is a light-scoring-weight field in lighting-config deserializer 0x10f09f0 (site 0x10f45d0 loads string 0xF516745, len 0x12, passed to 0x117d460). The "real cull unfound" part remains open and stays with H3b/H1b (docs/RENDER_CHECKLIST.md lines 174/356); this unit contributes the new negative angles 1-8 above.

## Verification
Run `python tools/delegate.py check docs/progress/oc_U-EL10b.md`. All quoted `0xRVA  instr` lines are copied verbatim from rdis `dis` output of Minecraft.Windows.exe 1.26.62.01: frustum_visibility site 0x10f45d0 group; 0x791f4ac; 0x792e92c; device-init vtable reads 0xe80821a/0xe8082c9/0xe8082df/0xe80834e (disassembled from function entry 0xe807ff0 so instruction boundaries align); 0x6b1c244/0x6b1c2c2/0x6b1c2e3/0x6b1c4d3 from sub_6b1c220/sub_6b1c3e0. verify_oc re-disassembles the exe and compares every claimed line; shape checks: rows, sizes, no raw dumps, no dup offsets, no placeholder omissions.

## TOOL REQUESTS
None — existing tools only (rdis dis/fn, xref.py str, verify_oc.py); no helper scripts written, no livemem calls made.
