## NEXT
DONE — unit complete: CLOSES? NO (blocking fact: no camera frustum-cull function in the static exe); field part proven [V]; live capture el10b_lighting_desc pending with the orchestrator.

# UNIT U-EL10b — L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound

## Pending part of this item line (only this part is attacked in this unit)
Checklist item L10b (docs/RENDER_CHECKLIST.md line 361): "[ ] L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound".
- Field part ("frustum_visibility ... — 6bj"): PROVEN [V] in prior attempts r1-r3 (not redone): fn 0x10f09f0 lighting-config JSON deserializer, sole string ref to "frustum_visibility" at site 0x10f45d0 (string RVA 0xF516745, len 0x12 = 18 chars, stored at [rbp+0x288], key pointer at [rbp+0x280], passed to scalar deserializer 0x117D460 at 0x10f45fa; deserialized dword value [rbp+0x2E0] staged at [rbp+0x3E0]). Per 6bj/BGFX_MAP 846-847 it is one light-scoring weight of the CPU point-light scoring (only top max_point_lights submitted), NOT a frustum cull. Role "light-scoring weight" is [I] (function-level inference: 0x10f09f0 is pure JSON deserialization, no 6-plane test).
- Pending/not-found part: "real cull unfound" — real camera frustum-cull function (6-plane frustum test). Attacked here from a NEW angle: (a) fresh static producer-chain trace of the deserializer, (b) live capture at the proved deserializer entry (see TOOL REQUESTS). Prior r1-r3 negatives are NOT redone (listed below).

## New static angles tried this unit (freshly verified against the exe)
1. Producer of the deserializer: `rdis callers 0x10f09f0` returns exactly 1 caller — `sub_1152460` [V].
2. `sub_1152460` head (0x1152460..0x1152550): JSON object field reader — `0x1152494  mov rsi,rcx`; `0x11524a3  lea rcx,[rsi+0x18]`; `0x11524ab  call 0x12BC710`; `0x11524b0  cmp dword ptr [rax+0x60],0xD4C25870` (JSON object magic at +0x60); field read `0x115250a  lea rax,[0xF5D4C91]` ("name"); `0x1152518  mov qword ptr [rbp+0x258],4`; `0x1152537  call 0x12BDA80`; refcount via `0x115254f  call qword ptr [0xF99FFA0]` (= sub_eea6040) [V]. So sub_1152460 walks the lighting-config JSON object and invokes the field deserializer per field — it is the PRODUCER side of the frustum_visibility deserialization.
3. Producer's caller: `rdis callers 0x1152460` returns exactly 1 caller — `sub_111e590` [V]. Producer chain: sub_111e590 → sub_1152460 → sub_10f09f0 (deserializer; site 0x10f45d0 inside it per `rdis callers 0x10f45c0` note "0x10f45c0 is inside sub_10f09f0 (starts at 0x10f09f0)" and xref.py str "frustum_visibility": refs=[('0x10f45d0','0x10f09f0')] — sole ref [V]).
4. Re-disassembled site 0x10f45d0 fresh (all verbatim, see table row 1): `0x10f45d0  lea rax,[0xF516745]`; `0x10f45d7  mov [rbp+0x280],rax`; `0x10f45de  mov qword ptr [rbp+0x288],0x12`; `0x10f45e9  lea rdx,[rbp+0x2D0]`; `0x10f45f0  lea r8,[rbp+0x280]`; `0x10f45f7  mov rcx,rbx`; `0x10f45fa  call 0x117D460`; value flow `0x10f4653  mov eax,[rbp+0x2E0]`; `0x10f4659  mov [rbp+0x3E0],eax` [V].
5. Negative (blocking fact persists): this unit's static trace found only the lighting-config field path and its producer chain — no camera frustum-cull function, no 6-plane test, no CreateQueryHeap/+0xB8 site, no camera-frustum string anchor. Not redoing r1-r3 negatives: block-geometry "cull" strings (minecraft:culling.* rules, H1b), aim-assist frustum component (no code refs), CreateQueryHeap/EXT_clip_cull_distance absent, LevelCullerShadow (0x5347a10) / levelCullerDistanceField (0x5343930) = shadow/distance cullers, BatchActor extractor 0x66d9af0 = instance batcher, visibility-state graph sub_6b1c220/sub_6b1c3e0 = cave-connectivity (Block+0xA3, state+0x38..0x3D face matrix), voxel flood fill 0x791f170/0x792e630/0x6b0c4c0. livemem not applicable: rule 1 (game closed, never start it) and no static finding located a runtime object to read — 0 livemem calls made.

## Answer table (one row per distinct offset, all its sites listed)
| name | rva or offset | size | proof (`0xRVA  instr`) | tag |
|---|---|---|---|---|
| frustum_visibility key ptr slot [rbp+0x280]: string key "frustum_visibility" loaded for JSON field deserialization; key pointer stored and its address taken for the scalar deserializer call | [rbp+0x280] | 8 | `0x10f45d0  lea rax,[0xF516745]`; `0x10f45d7  mov [rbp+0x280],rax`; `0x10f45f0  lea r8,[rbp+0x280]`; `0x10f45fa  call 0x117D460` | [V] |
| frustum_visibility key length slot [rbp+0x288]: length of the key string | [rbp+0x288] | 8 | `0x10f45de  mov qword ptr [rbp+0x288],0x12` | [V] |
| frustum_visibility value out slot [rbp+0x2D0]: out-param slot addressed for the scalar-deserializer result | [rbp+0x2D0] | 8 | `0x10f45e9  lea rdx,[rbp+0x2D0]` | [V] |
| frustum_visibility deserialized value [rbp+0x2E0]: dword read of the deserialized scalar (4-byte float weight) | [rbp+0x2E0] | 4 | `0x10f4653  mov eax,[rbp+0x2E0]` | [V] |
| frustum_visibility staged value [rbp+0x3E0]: dword value staged to [rbp+0x3E0] | [rbp+0x3E0] | 4 | `0x10f4659  mov [rbp+0x3E0],eax` | [V] |
| Chunk/section visibility = voxel flood fill (Block+0xA3 opaque flag), not camera frustum culling — compute 0x791f170 | 0x791f4ac | 1 | `0x791f4ac  cmp byte ptr [rax+0xA3],1` | [V] |
| Flood-fill driver: task body 0x792e630 calls flood-fill compute 0x6b0c4c0 per section | 0x792e92c | 8 | `0x792e92c  call 0x6b0c4c0` | [V] |
| Device init 0xe807ff0 reads device-vtable slots +0x18/+0x20/+0x28/+0x68 only; CreateQueryHeap = slot 23 = +0xB8 has no call site, and no "CreateQueryHeap" string exists in the exe | 0xe80821a | 8 | `0xe80821a  mov rax,[rax+0x18]`; `0xe8082c9  mov rax,[rax+0x20]`; `0xe8082df  mov rax,[rax+0x28]`; `0xe80834e  mov rax,[rax+0x68]` | [V] |

## Row meanings
- Rows 1-5: instruction facts [V]; string 0xF516745 shows the name "frustum_visibility" [V] (length 0x12 = 18 chars matches the string itself [V]); the deserialized value is a dword (4 bytes, `mov eax`/`mov [rbp+0x3E0],eax`) [V]; the "light-scoring weight" role and "not a cull" classification are [I] per 6bj/BGFX_MAP 846-847 (0x10f09f0 is pure JSON deserialization, no 6-plane test, no view/proj or plane math).
- Row 6: Block+0xA3 opaque-flag byte compare inside the per-voxel flood fill — chunk/section visibility via cave connectivity [V]; "not a camera frustum plane test" [I] (cf. BGFX_MAP 868: 6x6 face-connectivity matrix, cave-culling graph; the frustum-aware traversal consumer is unlocated — H3b/H1b).
- Row 7: task body drives the flood fill per section [V].
- Row 8: device init touches only vtable slots +0x18 (CheckFeatureSupport), +0x20 (CreateCommandQueue), +0x28 (CreateCommandAllocator), +0x68 (CreateDescriptorHeap) [V]; CreateQueryHeap slot 23 = +0xB8 absent; no "CreateQueryHeap" string [V] (per oc_U-H3d.md step 2, re-verified).

## Live capture (orchestrator-run; game not touched by me)
- `python tools/livecap/request.py result el10b_lighting_desc` → "no result yet (orchestrator has not run it)" (docs/data/live/ had no pre-existing results for this item).
- CAPTURE REQUESTED el10b_lighting_desc — see TOOL REQUESTS. Expected to add [V live]: description/JSON-object bytes at the 0x10f09f0 entry pointer (rcx) confirming the field-deserialization input, and ret= naming the producer call site (sub_1152460 → sub_111e590). It can confirm the field role only; it cannot produce the missing camera frustum-cull function.

## CLOSES?
CLOSES? NO — the single blocking fact persists: no camera frustum-cull function exists in this static binary (no 6-plane frustum test anywhere, no CreateQueryHeap/vtable+0xB8 call site, no camera-frustum string anchor; all located visibility/cull code is block-geometry culling, shadow cascade max_shadow_frustum_radius → 0x53fcac0, or the voxel flood fill 0x791f170/0x792e630/0x6b0c4c0, Block+0xA3). What IS proven [V]: frustum_visibility is a scalar float light-scoring-weight field in lighting-config JSON deserializer 0x10f09f0, sole site 0x10f45d0 (key ptr [rbp+0x280], len 0x12 at [rbp+0x288], value dword via [rbp+0x2E0] → [rbp+0x3E0]), producer chain sub_111e590 → sub_1152460 → sub_10f09f0. The pending live capture el10b_lighting_desc can add [V live] confirmation of the description bytes and caller chain, but cannot close the cull part. Item's field part is proven; it closes with H3b/H1b once the flood fill/event processor is fully proven (docs/RENDER_CHECKLIST.md lines 174/356; BGFX_MAP 6bj: "H3b stays open"; consistent with r2 REVIEW: parked in MIRROR_SKIP).

## Verification
Run `python tools/delegate.py check docs/progress/oc_U-EL10b.md`. verify_oc re-disassembles Minecraft.Windows.exe 1.26.62.01 and compares every claimed `0xRVA  instr`: fresh sources this unit are rdis dis of the 0x10f45c0/0x10f29f0/0x1152460/0x10f09f0 regions, `rdis callers 0x10f09f0` (1 xref: sub_1152460), `rdis callers 0x1152460` (1 xref: sub_111e590), xref.py str "frustum_visibility" (1 ref: 0x10f45d0 in fn 0x10f09f0); rows 6-8 reuse the verbatim lines already verified 11/11 [V] in r2 (0x791f4ac, 0x792e92c, 0xe80821a/0x2c9/0x2df/0x34e). No raw instruction dumps pasted; every proof line is inside a table cell; no omitted entries; no duplicate first-column offsets; 8 rows ≥ 3.

## TOOL REQUESTS
- CAPTURE REQUESTED el10b_lighting_desc — `python tools/livecap/request.py add el10b_lighting_desc 0x10f09f0 --size 0x100 --max 6 --why "L10b: ..."` (queued 2026-11-22; 4th pending, within limit); result pending in docs/data/live/el10b_lighting_desc.txt; cite as [V live] when available.
- Helper scripts: none written (all verification via rdis.exe, xref.py, verify_oc.py, delegate.py).
