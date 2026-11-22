## NEXT
DONE

# UNIT U-EL10b — L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound

## Pending part of this item line
Checklist item L10b (docs/RENDER_CHECKLIST.md line 361): "[ ] L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound".
- Field part ("frustum_visibility ... — 6bj"): frustum_visibility is a field of the lighting-config JSON deserializer fn 0x10f09f0 — proven [V] below.
- Pending/not-found part: "real cull unfound" — the real camera frustum-cull function. Addressed below; it does not exist in the static binary.

## Input data (precomputed by the orchestrator; read fully; no tools re-run per unit rules)
- docs/progress/oc_U-H3c.md — 0x660ecd0 bgfx Caps JSON dump; 0x10f09f0 lighting-config JSON deserializer (listing docs/listings/L_10f09f0.txt, 3511 lines, 0x10f09f0..0x10f5921); 0x6646980 item material dispatcher
- docs/progress/oc_U-H3d.md — string search: frustum_visibility string 0xF516745 has only ref 0x10f45d0 in 0x10f09f0; max_shadow_frustum_radius 0xF543489 -> 0x53fcac0 shadow cascade; aim-assist frustum component 0xF59D48F no code refs; step 2 CreateQueryHeap/vtable+0xB8 negative; step 3: 0x791f170 compute + 0x792e630 task body = voxel flood fill (Block+0xA3 opaque flag)
- docs/progress/oc_U-EH2.md — occlusion-query user chain (Frame+0x14300, 0xe85e5c0, executor 0xe821120) [context only]
- docs/BGFX_MAP.md — 6bj (frustum_visibility = light-scoring weight, site 0x10f45d0; no engine frustum-cull function behind the string), 6bi/6bl anchors (839-844, 846-850)
- docs/RENDER_CHECKLIST.md — L10b line 361; H3b/L9e mirror lines 174/356 (real cull stays open there)
- docs/listings/L_10f09f0.txt — frustum_visibility site 0x10f45d0 at line 2579

## Answer table (one row per distinct offset, all its sites listed)
| name | rva or offset | size | proof (`0xRVA  instr`) | tag |
|---|---|---|---|---|
| frustum_visibility field: string key "frustum_visibility" loaded for JSON field deserialization (lighting config) | fn 0x10f09f0, site 0x10f45d0; string RVA 0xF516745 | 4 (float scoring-weight field [I]; key ptr/len stored as qword at 0x10f45d7 / 0x10f45de) | `0x10f45d0  lea rax,[0xF516745]`; `0x10f45d7  mov [rbp+0x280],rax`; `0x10f45de  mov qword ptr [rbp+0x288],0x12`; `0x10f45fa  call 0x117d460` | [V] |
| frustum_visibility role: the only frustum anchor in fn 0x10f09f0; function body is pure JSON config deserialization (fields light_update_frequency @0x10f0c45 .. near_plane @0x10f229b; probe/tile fields via helper 0x1171a80; helpers 0x116b3a0/0x116c930/0x116d950/0x10f05e0/0xeea6040); no 6-plane frustum test anywhere in 0x10f09f0..0x10f5921 => not a cull | fn 0x10f09f0 (0x4f31 bytes) | - | `0x10f45d0  lea rax,[0xF516745]` (sole frustum_visibility string load in listing L_10f09f0.txt; xref str "frustum": only ref to string 0xF516745) | [V] |
| Chunk/actor visibility = voxel flood fill, not camera frustum culling | 0x791f170 (compute), 0x792e630 (task body); Block+0xA3 opaque flag | - | `0x791F4AC  cmp byte ptr [rax+0xA3],1`; `0x7924211  movzx r8d,byte ptr [rbx+0x3E]` | [V] |
| D3D12 CreateQueryHeap (occlusion-query heap creation; device vtable slot 23 = offset 0xB8): no call site | device init 0xe807ff0 scanned | - | `0xE80821A  mov rax,[rax+0x18]`; `0xE8082C9  mov rax,[rax+0x20]`; `0xE8082DF  mov rax,[rax+0x28]`; `0xE80834E  mov rax,[rax+0x68]` (device init uses offsets 0x18/0x20/0x28/0x68; no 0xB8 site anywhere in static .text; no "CreateQueryHeap" string in the exe) | [V] |

## Row meanings
- Row 1: "frustum_visibility" is 18 chars = length 0x12 stored at [rbp+0x288] by 0x10f45de; key pointer 0xF516745 stored at [rbp+0x280] by 0x10f45d7 and passed to scalar field deserializer 0x117d460 at 0x10f45fa; deserialized value lands at [rbp+0x2E0] then [rbp+0x3E0]. Per 6bj this field is one light-scoring weight of the CPU point-light scoring (only the top max_point_lights are submitted), NOT a frustum cull. Field location + string load: [V]. Role "light-scoring weight": [I] per 6bj (function-level inference).
- Row 2: 0x10f45d0 is the only frustum_visibility reference in fn 0x10f09f0 (verified against listing L_10f09f0.txt); the function deserializes lighting-config JSON fields only, so it cannot be the camera cull. Instruction fact [V]; "not cull" conclusion [I] per 6bj.
- Row 3: chunk visibility (launcher 0x7923d50, task body 0x792e630, compute 0x791f170) is a voxel flood fill over the section grid checking the Block+0xA3 opaque flag — not a 6-plane frustum test [V].
- Row 4: device init 0xe807ff0 touches device-vtable offsets 0x18 (CheckFeatureSupport), 0x20 (CreateCommandQueue), 0x28 (CreateCommandAllocator), 0x68 (CreateDescriptorHeap); CreateQueryHeap = slot 23 = offset 0xB8 — no call site with that offset anywhere in static .text, and no "CreateQueryHeap" string in the exe [V per oc_U-H3d.md step 2].

## Other frustum/cull anchors (input data oc_U-H3d.md step 1; listed for completeness, not table rows since no verbatim instruction line exists for them)
- frustum_visibility string 0xF516745 -> only ref 0x10f45d0 in 0x10f09f0 (lighting config) [V row 1]
- max_shadow_frustum_radius string 0xF543489 -> fn 0x53fcac0 (shadow cascade setup) [V]
- CameraAimAssistCacheFrustumSystem / CameraAimAssistCachedFrustumComponent 0xF59D48F -> no code refs; aim-assist entt component only [V]
- No string or RTTI anchor for a camera frustum-cull class exists in the exe [V negative]

## CLOSES?
CLOSES? NO — the pending part of the item line ("real cull unfound") is NOT [V]-proven: no camera frustum-cull function exists in this static binary. Proven [V] instead: frustum_visibility is a light-scoring-weight field in lighting-config JSON deserializer 0x10f09f0 (site 0x10f45d0 loads string 0xF516745); its function body is pure JSON deserialization, not culling; every other frustum/cull anchor is non-cull (shadow cascade 0x53fcac0; aim-assist component, no code refs); chunk visibility is voxel flood fill (0x791f170/0x792e630, Block+0xA3); no 6-plane frustum test anywhere; no CreateQueryHeap (vtable+0xB8) call site (device init 0xe807ff0 uses only offsets 0x18/0x20/0x28/0x68). Single blocking fact: the real frustum-cull function is absent from / not locatable in the exe, so "real cull unfound" cannot be closed here and stays open under H3b/L9e (docs/progress/oc_U-H3d.md). The field part itself (frustum_visibility = light-scoring field, not cull) is proven [V].

## Verification
Run `python tools/delegate.py check docs/progress/oc_U-EL10b.md` (verify_oc re-disassembles the exe and compares every claimed `0xRVA  instr`; shape checks: rows, sizes, no raw dumps, no dup offsets). All quoted instructions are copied verbatim from docs/listings/L_10f09f0.txt line 2579 (0x10f45d0 group) and docs/progress/oc_U-H3d.md (0x791F4AC, 0x7924211, 0xE80821A/0xE8082C9/0xE8082DF/0xE80834E).

## TOOL REQUESTS
None — all input data precomputed by the orchestrator; no tools re-run; no new helpers written.
