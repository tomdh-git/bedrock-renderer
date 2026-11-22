## NEXT
DONE

# Unit U-EL9e — L9e Frustum/culling anchors: real cull fn

## Goal
Close checklist item L9e: "Frustum/culling anchors (6bf, 6bi); 6bj: frustum_visibility is a light-scoring weight (fn 0x10f09f0), real cull fn still unfound".
DO ONLY the pending part: "real cull fn still unfound".

## Pending part resolved — the real cull fn is located and [V]-proven

The engine does NOT have a camera 6-plane frustum cull test. frustum_visibility is a light-scoring weight, not a cull fn. The real chunk cull function is the LevelCuller per-section visibility query, vtable slot 9 = `0x5343590` (isSectionVisible).

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning |
|---|---|---|---|---|
| 0x10f45d0 | 8 | `[0xF516745]` = "frustum_visibility" string | `0x10f45d0  lea rax,[0xF516745]` | fn 0x10f09f0 (light-scoring/ambient-transition deserializer) loads the "frustum_visibility" config name — it is one scoring weight among light_update_frequency/max_point_lights/light_scoring_weights, NOT a cull function [V] (site 0x10f45d0, 6bj) |
| 0x5343590 | 8 | function entry, LevelCuller vtable slot 9 (+0x24) | `0x5343590  push r15` | isSectionVisible(culler*, RenderChunkState*) — the real per-section chunk cull query, shared base slot of all 6 culler vtable kinds [V] |
| 0x5343679 | 1 | `[r10+r11+0xE]` grid cell+0xE flag byte | `0x5343679  movzx ecx,byte ptr [r10+r11+0xE]` | isSectionVisible reads the culler grid cell flag byte (+0xE) that decides whether the section is visible [V] |
| 0x53436bb | 1 | `[rdi]` state+0 | `0x53436bb  xor cl,[rdi]` | isSectionVisible XORs the cell flag with state+0 and returns the visibility bool in ebx (after FNV-1 owner lock/unlock via 0xEEC58F0) [V] |

## Culling mechanism (context, not part of the pending row set)

- frustum_visibility (string rva 0xf516745, load site 0x10f45d0 inside fn 0x10f09f0) is a light-scoring weight for VV/deferred point-light scoring — confirmed NOT a cull function [V, 6bj].
- No camera 6-plane frustum cull test exists in the exe: no plane array, no dot(plane,corner) sign tests, no cmpps/movmskps frustum sites in the chunk or actor render path (whole-.text shape scan found none) [V per prior verified scan].
- The real chunk cull = LevelCuller grid visibility query: task bodies (e.g. body 0x53cc570 spawned by launcher 0x5347a10 via vtable 0xf248640 slot 2) build a view-ray/distance-limited visibility grid; slot 9 0x5343590 (isSectionVisible) reads cell+0xE to decide per-section visibility [V]. RenderChunk depth reaches draws via record +0x63 (0x5334850), reader at 0x53398ee.
- Actor side: no actor-vs-frustum/AABB geometry cull test found (actor render step 0x53e1160 has no plane/AABB test) [V per prior verified read] — this is the remaining actor-visibility concern (H3b/H1b), not the cull fn itself.

## CLOSES?
YES — every pending part of L9e is proven by [V] rows: the real cull fn is found (0x5343590 = LevelCuller::isSectionVisible, vtable slot 9), and frustum_visibility is confirmed as a light-scoring weight (0x10f09f0), not a cull fn.
