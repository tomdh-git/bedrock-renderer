## NEXT
DONE

# UNIT U-EL10b — L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound

## Pending part (from prior attempt oc_U-EL10b_r1; NOT redone)
- frustum_visibility field in lighting-config JSON deserializer fn 0x10f09f0: PROVEN [V] (site 0x10f45d0 loads string 0xF516745, len 0x12, passed to scalar deserializer 0x117d460).
- NOT FOUND / pending: real camera frustum-cull function ("real cull unfound").

## New angles tried this unit (all negative — blocking fact persists)
1. Callers of flood fill: 0x791f170 <- 0x6b0c4c0 <- 0x792e630 = voxel flood fill over sections, Block+0xA3 opaque flag — chunk visibility, NOT camera frustum cull [V].
2. 0x66d9af0 BatchActor extractor: instance batcher/sorter over [r8+0xE0] instances (sorted insert), no frustum math [V] (BGFX_MAP 6bn anchor, checked as a possible per-instance frustum filter).
3. Culler tasks: "LevelCullerShadow task" (fn 0x5347a10, reads light cascade params at +0x5E8..+0xF4) and "levelCullerDistanceField task" (fn 0x5343930) — shadow/distance cullers, NOT camera frustum cull [V] (strings 0xF5A6FB4 @0x5347b07, 0xF5A70C7 @0x5343a15).
4. String xref "frustum"/"Frustum": only frustum_visibility (0x10f45d0), max_shadow_frustum_radius (0x53fea81 -> shadow cascade 0x53fcac0), aim-assist component (no code refs) — no camera-frustum string anchor anywhere [V].
5. Flood-fill consumption 0x6b0c4c0 XOR-compares the 6 face bytes (state+0x38..0x3D) against a global with per-face masks (0x3e/0x3d/0x3b/0x37/0x2f/0x1f) — cave-connectivity cull, not a 6-plane camera frustum test [V].

## Answer table (one row per distinct offset, all its sites listed)
| name | rva | size | proof | tag |
| frustum_visibility field: key "frustum_visibility" loaded for JSON field deserialization (lighting config; light-scoring weight per 6bj) | 0x10f45d0 | 4 | `0x10f45d0  lea rax,[0xF516745]`; `0x10f45d7  mov [rbp+0x280],rax`; `0x10f45de  mov qword ptr [rbp+0x288],0x12`; `0x10f45fa  call 0x117D460` | [V] |
| Chunk visibility = voxel flood fill (Block+0xA3 opaque flag), not camera frustum cull | 0x791f4ac | 1 | `0x791f4ac  cmp byte ptr [rax+0xA3],1` | [V] |
| No camera frustum cull / CreateQueryHeap: device init reads vtable slots at +0x18/+0x20/+0x28/+0x68, never +0xB8 | 0xe80821a | 8 | `0xe80821a  mov rax,[rax+0x18]`; `0xe8082c9  mov rax,[rax+0x20]`; `0xe8082df  mov rax,[rax+0x28]`; `0xe80834e  mov rax,[rax+0x68]` | [V] |
| LevelCullerShadow task = shadow-cascade culler, not camera frustum cull | 0x5347b07 | 8 | `0x5347b07  lea rax,[0xF5A6FB4]` | [V] |
| levelCullerDistanceField task = distance-field culler, not camera frustum cull | 0x5343a15 | 8 | `0x5343a15  lea rcx,[0xF5A70C7]` | [V] |

## Row meanings
- Row 1: "frustum_visibility" is 18 chars = length 0x12 stored at [rbp+0x288] by 0x10f45de; key pointer 0xF516745 stored at [rbp+0x280] by 0x10f45d7 and passed to scalar field deserializer 0x117d460 at 0x10f45fa. Field part (light-scoring weight) proven [V]; role "light-scoring weight" [I] per 6bj (function-level inference: 0x10f09f0 is the light_scoring_weights/ambient-transition deserializer, pure JSON deserialization, no 6-plane test).
- Row 2: 0x791f4ac reads Block+0xA3 (opaque/full-cube flag) inside the per-voxel flood fill — chunk/section visibility via cave connectivity, not a camera frustum plane test [V].
- Row 3: device init (0xe807ff0 region) reads device-vtable slots +0x18 (CheckFeatureSupport), +0x20 (CreateCommandQueue), +0x28 (CreateCommandAllocator), +0x68 (CreateDescriptorHeap); CreateQueryHeap = slot 23 = +0xB8 — no +0xB8 site anywhere in static .text, no "CreateQueryHeap" string [V per oc_U-H3d.md].
- Row 4: 0x5347b07 loads the "LevelCullerShadow task" string; fn 0x5347a10 reads light/cascade data (+0x5E8..+0xF4) — this culls shadow casters against a light frustum/cascade, not the camera frustum [V].
- Row 5: 0x5343a15 loads the "levelCullerDistanceField task" string — distance-field culling, not camera frustum [V].

## CLOSES?
CLOSES? NO — the single blocking fact persists: no camera frustum-cull function exists in this static binary (no 6-plane frustum test, no CreateQueryHeap vtable+0xB8 site, no camera-frustum string anchor; only shadow/distance/block cullers and the voxel flood fill). Proven [V] instead: frustum_visibility is a light-scoring-weight field in lighting-config deserializer 0x10f09f0 (site 0x10f45d0). This item's field part is proven; it closes with H3b/H1b once the flood fill/event processor is fully proven (the real camera cull is H3b/H1b's domain, docs/RENDER_CHECKLIST.md lines 174/356).

## Verification
Run `python tools/delegate.py check docs/progress/oc_U-EL10b.md`. All quoted `0xRVA  instr` lines are verbatim from rdis dis output: frustum_visibility site 0x10f45d0 group (rdis dis 0x10f45d0); 0x791f4ac (docs/progress/pre_791f170.txt); 0xe80821a/0x2c9/0x2df/0x34e (oc_U-H3d.md / rdis device init); 0x5347b07 and 0x5343a15 (rdis dis above). verify_oc re-disassembles the exe and compares every claim.

## TOOL REQUESTS
None — all verification done with rdis.exe and xref.py; no new helpers written.
