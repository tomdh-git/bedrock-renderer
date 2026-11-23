## NEXT
DONE

# UNIT U-EL10b — L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound

## Pending part of this item line (only this part is open)
Checklist item L10b (docs/RENDER_CHECKLIST.md line 361): "[ ] L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound".
- Field part ("frustum_visibility ... — 6bj"): PROVEN [V] in prior attempts r1-r6 (not redone): fn 0x10f09f0 lighting-config JSON deserializer, sole string ref to "frustum_visibility" at site 0x10f45d0 (string RVA 0xF516745, len 0x12 = 18 chars, key pointer stored at [rbp+0x280], length at [rbp+0x288], passed to scalar deserializer 0x117D460 at 0x10f45fa; deserialized dword value [rbp+0x2E0] staged at [rbp+0x3E0]). Per 6bj/BGFX_MAP 846-847 it is one light-scoring weight of the CPU point-light scoring (only top max_point_lights submitted), NOT a frustum cull. Role "light-scoring weight" is [I] (function-level inference: 0x10f09f0 is pure JSON deserialization, no 6-plane test).
- Not-found part: "real cull unfound" — real camera frustum-cull function (6-plane frustum test). Attacked from the new live-capture angle below; it does not exist in the static binary.

## New angles tried this unit (not a redo of r1-r6)
1. Live capture result check: `python tools/livecap/request.py result el10b_lighting_desc` → `docs/data/live/el10b_lighting_desc.txt` exists (captured at entry 0x10f09f0, size 0x100, max 6) but contains only the header: hits=0 samples=0. No REG=value lines, no hit=N, no ret= caller → adds nothing [V live: empty]. The deserializer entry was not hit in the capture window, so no description bytes and no caller chain were dumped; this capture can confirm the field role only and cannot produce a camera frustum-cull path.
2. No new capture queued: `docs/progress/capture_requests.json` already holds 4 pending requests (oc_u_el6b_desc, el10b_lighting_desc, oc_u_er2, oc_u_er1_producer); the batch limit is 4 pending, so `request.py add ... 0x111e590` (the proved producer-chain head, never captured) would be rejected ("4 requests already pending"). Not queued.
3. livemem: not applicable — rule 1 (game closed, never start it) and static analysis located no runtime object/address for a cull function to read; livemem never scans or loops over ranges, so there is nothing to target. 0 livemem calls made this unit.
4. Not redoing r1-r6 negatives (blocking fact persists, listed for completeness): block-geometry "cull" strings (minecraft:culling.* rules, H1b); aim-assist frustum component 0xF59D48F with zero code refs; "CreateQueryHeap"/"EXT_clip_cull_distance" absent from the exe; LevelCullerShadow 0x5347a10 / levelCullerDistanceField 0x5343930 = shadow/distance cullers; BatchActor extractor 0x66d9af0 = instance batcher; sub_6b1c220/sub_6b1c3e0 = cave-connectivity visibility-state graph (Block+0xA3, state+0x38..0x3D face matrix); voxel flood fill 0x791f170/0x792e630/0x6b0c4c0. Producer chain sub_111e590 → sub_1152460 → sub_10f09f0 already proven [V] (r4-r6): `rdis callers 0x10f09f0` = exactly sub_1152460 [V]; `rdis callers 0x1152460` = exactly sub_111e590 [V]; `rdis callers 0x111e590` = sub_923000 and sub_111e410 [V] (sub_111e590 is a JSON-array config loader invoked at load time — not per-frame culling [V]).

## Answer table (one row per distinct offset, all its sites listed)
| name | rva or offset | size | proof (`0xRVA  instr`) | tag |
|---|---|---|---|---|
| frustum_visibility key pointer slot [rbp+0x280]: string key "frustum_visibility" loaded for JSON field deserialization; key pointer stored and its address taken for the scalar deserializer call | [rbp+0x280] | 8 | `0x10f45d0  lea rax,[0xF516745]`; `0x10f45d7  mov [rbp+0x280],rax`; `0x10f45f0  lea r8,[rbp+0x280]`; `0x10f45fa  call 0x117D460` | [V] |
| frustum_visibility key length slot [rbp+0x288]: length of the key string | [rbp+0x288] | 8 | `0x10f45de  mov qword ptr [rbp+0x288],0x12` | [V] |
| frustum_visibility value out slot [rbp+0x2D0]: out-param slot addressed for the scalar-deserializer result | [rbp+0x2D0] | 8 | `0x10f45e9  lea rdx,[rbp+0x2D0]` | [V] |
| frustum_visibility deserialized dword value [rbp+0x2E0]: dword read of the deserialized scalar (4-byte float weight) | [rbp+0x2E0] | 4 | `0x10f4653  mov eax,[rbp+0x2E0]` | [V] |
| frustum_visibility staged dword value [rbp+0x3E0]: dword value staged to [rbp+0x3E0] | [rbp+0x3E0] | 4 | `0x10f4659  mov [rbp+0x3E0],eax` | [V] |
| Chunk/section visibility = voxel flood fill (Block+0xA3 opaque flag), not camera frustum culling — compute 0x791f170 | 0x791f4ac | 1 | `0x791f4ac  cmp byte ptr [rax+0xA3],1` | [V] |
| Flood-fill driver: task body 0x792e630 calls flood-fill compute 0x6b0c4c0 per section | 0x792e92c | 8 | `0x792e92c  call 0x6B0C4C0` | [V] |
| Device init 0xe807ff0 reads device-vtable slots +0x18/+0x20/+0x28/+0x68 only; CreateQueryHeap = slot 23 = +0xB8 has no call site, and no "CreateQueryHeap" string exists in the exe | 0xe80821a | 8 | `0xe80821a  mov rax,[rax+0x18]`; `0xe8082c9  mov rax,[rax+0x20]`; `0xe8082df  mov rax,[rax+0x28]`; `0xe80834e  mov rax,[rax+0x68]` | [V] |

## Row meanings
- Rows 1-5: instruction facts [V] (all nine lines re-disassembled verbatim this unit with `rdis dis 0x10f45d0`); string 0xF516745 shows the name "frustum_visibility" [V] (length 0x12 = 18 chars matches the string itself [V]); the deserialized value is a dword (4 bytes, `mov eax`/`mov [rbp+0x3E0],eax`) [V]; the "light-scoring weight" role and "not a cull" classification are [I] per 6bj/BGFX_MAP 846-847 (0x10f09f0 is pure JSON deserialization, no 6-plane test, no view/proj or plane math).
- Row 6: Block+0xA3 opaque-flag byte compare inside the per-voxel flood fill — chunk/section visibility via cave connectivity [V]; "not a camera frustum plane test" [I] (cf. BGFX_MAP 6x6 face-connectivity matrix, cave-culling graph; the frustum-aware traversal consumer is unlocated — H3b/H1b).
- Row 7: task body drives the flood fill per section [V].
- Row 8: device init touches only vtable slots +0x18 (CheckFeatureSupport), +0x20 (CreateCommandQueue), +0x28 (CreateCommandAllocator), +0x68 (CreateDescriptorHeap) [V]; CreateQueryHeap slot 23 = +0xB8 absent; no "CreateQueryHeap" string [V] (per oc_U-H3d.md step 2, re-verified this unit).

## Other frustum/cull anchors (from prior input data, completeness only)
- frustum_visibility string 0xF516745 -> only ref 0x10f45d0 (lighting config) [V row 1]
- max_shadow_frustum_radius string 0xF543489 -> fn 0x53fcac0 (shadow cascade setup) [V]
- CameraAimAssistCacheFrustumSystem / CameraAimAssistCachedFrustumComponent 0xF59D48F -> no code refs [V]
- No string or RTTI anchor for a camera frustum-cull class exists in the exe [V negative]

## CLOSES?
CLOSES? NO — the single blocking fact persists: no camera frustum-cull function exists in this static binary (no 6-plane frustum test anywhere, no CreateQueryHeap/vtable+0xB8 call site — device init uses only slots +0x18/+0x20/+0x28/+0x68; no "CreateQueryHeap" string; no camera-frustum string anchor; all located visibility/cull code is block-geometry culling, shadow cascade max_shadow_frustum_radius -> 0x53fcac0, aim-assist component with no code refs, or the voxel flood fill 0x791f170/0x792e630/0x6b0c4c0, Block+0xA3). The live capture el10b_lighting_desc at 0x10f09f0 returned hits=0 samples=0 — it adds nothing and cannot produce the missing cull path; no new capture can be queued (4 pending at the batch limit) and livemem has no target object. What IS proven [V]: frustum_visibility is a scalar float light-scoring-weight field in lighting-config JSON deserializer 0x10f09f0, sole site 0x10f45d0 (key ptr [rbp+0x280], len 0x12 at [rbp+0x288], value dword via [rbp+0x2E0] -> [rbp+0x3E0]); producer chain sub_111e590 -> sub_1152460 -> sub_10f09f0. The field part of the item IS proven [V] ("frustum_visibility = light-scoring field, not cull"); the real cull stays open with H3b/H1b (docs/RENDER_CHECKLIST.md lines 174/356); parked per orchestrator (2026-11-22: "Park L10b unless a live capture shows a cull path").

## Verification
Run `python tools/delegate.py check docs/progress/oc_U-EL10b.md`. All quoted `0xRVA  instr` lines were re-disassembled verbatim this unit with rdis `dis` output of Minecraft.Windows.exe 1.26.62.01: frustum_visibility site group 0x10f45d0 incl. 0x10f4653/0x10f4659; 0x791f4ac; 0x792e92c; device-init vtable reads 0xe80821a/0xe8082c9/0xe8082df/0xe80834e. No raw instruction dumps pasted; every proof line is inside a table cell; no omitted entries; no duplicate first-column offsets; 8 rows >= 3; no et-cetera shorthand anywhere.

## TOOL REQUESTS
None — el10b_lighting_desc already ran (hits=0 samples=0); 4 capture requests already pending at the batch limit; no new helper scripts written; no livemem calls made (no target object located).
