## NEXT
DONE

# UNIT U-EL10b — L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound

Source item: docs/RENDER_CHECKLIST.md line 361: "[ ] L10b frustum_visibility (light-scoring field, not cull) — 6bj; real cull unfound". Canonical file per the 2026-11-22 orchestrator restart; prior proofs live in docs/progress/oc_U-EL10b_r1..r8.md (r8: verify_oc 14/14, ticked 2026-11-22).

## 1. Live-capture status (checked first, per 2026-11-22 handoff)
- `python tools/livecap/request.py result el10b_lighting_desc` -> docs/data/live/el10b_lighting_desc.txt exists (captured at entry 0x10F09F0, kind=regs, size=0x100) but header-only: hits=0 samples=0; no REG=value lines, no hit=N, no ret= caller, no description bytes [V live][LIVE docs/data/live/el10b_lighting_desc.txt:1-2]. The deserializer entry did not run in the capture window — known zero-hit capture per HANDOFF 2026-11-22.
- `grep docs/data/live/*.txt` for 10f09f0 / 10f45d0 / frustum_visibility -> no matches in any live file [V]; no live capture names these RVAs or the string, so live data adds nothing beyond what static analysis already named.
- Queue state: entry `done`; `request.py add` rejects re-add ("already queued"); 3 of 4 pending slots held by other units (q6b_cull_detour_entry, u_eq5c_submitcustom, u_eq5c_executor). Cannot be re-queued by this unit.
- el10b_lighting_desc at 0x10f09f0 IS the proved entry (the lighting-config JSON deserializer, sole frustum_visibility site) — but zero hits means it can dump neither descriptor bytes nor a ret= caller chain [V]. It cannot reveal a camera-frustum cull path because 0x10f09f0 is load-time JSON parsing, not per-frame culling [V].

## 2. What static analysis proves (not redone; summarized from oc_U-EL10b_r1..r8)
- Producer chain: `rdis callers 0x10f09f0` = exactly sub_1152460 (1 call site) [V]; callers of 0x1152460 = exactly sub_111e590 [V]; callers of 0x111e590 = sub_923000 and sub_111e410 [V]. Chain sub_111e590 -> sub_1152460 -> sub_10f09f0 is a load-time JSON-array config loader (sub_111e590 walks a 32-byte-entry table at 0xF0CD7A0 at load time), not per-frame camera culling [V]. No cull path reachable from frustum_visibility [V].
- No camera frustum cull anywhere in the static binary: whole-.text scans found no 6-plane frustum test, no CreateQueryHeap call (no such string in the exe [V]), no vtable+0xB8 (CreateQueryHeap slot 23) call site, no camera-frustum string anchor (CameraAimAssistCacheFrustumSystem/CameraAimAssistCachedFrustumComponent 0xF59D48F have zero code refs [V]) [V].
- Located visibility/cull code is block-geometry culling, not camera frustum: voxel flood fill compute 0x791f170 (Block+0xA3 opaque flag) driven by task body 0x792e630 calling compute 0x6b0c4c0 per section [V]; device init 0xe807ff0 reads vtable slots only +0x18/+0x20/+0x28/+0x68 [V].
- BGFX_MAP 6bj (lines 846-847): fn 0x10f09f0 is a data-driven light-scoring/ambient-transition settings deserializer; frustum_visibility (site 0x10f45d0) is one scoring weight; "there is no engine frustum-cull function behind this string" [V].

## 3. Answer table (one row per distinct offset, all its sites listed)
| name ([offset]) | size | address(es) | proof (`0xRVA  instr`) | meaning | tag |
|---|---|---|---|---|---|
| frustum_visibility key pointer slot ([rbp+0x280]) | 8 | [rbp+0x280] | `0x10f45d0  lea rax,[0xF516745]`; `0x10f45d7  mov [rbp+0x280],rax`; `0x10f45f0  lea r8,[rbp+0x280]`; `0x10f45fa  call 0x117D460` | string key "frustum_visibility" (RVA 0xF516745) loaded; key pointer stored and its address passed as key param to scalar deserializer 0x117D460 | [V] |
| frustum_visibility key length slot ([rbp+0x288]) | 8 | [rbp+0x288] | `0x10f45de  mov qword ptr [rbp+0x288],0x12` | 0x12 = 18 chars, matches "frustum_visibility" | [V] |
| frustum_visibility value out-param slot ([rbp+0x2D0]) | 8 | [rbp+0x2D0] | `0x10f45e9  lea rdx,[rbp+0x2D0]` | deserializer writes the scalar result here | [V] |
| frustum_visibility deserialized dword value ([rbp+0x2E0]) | 4 | [rbp+0x2E0] | `0x10f4653  mov eax,[rbp+0x2E0]` | dword read back from the deserialized scalar | [V] |
| frustum_visibility staged dword value ([rbp+0x3E0]) | 4 | [rbp+0x3E0] | `0x10f4659  mov [rbp+0x3E0],eax` | value staged for the downstream config struct | [V] |
| Chunk/section visibility = voxel flood fill, opaque flag Block+0xA3 — compute 0x791f170 | 1 | [rax+0xA3] | `0x791f4ac  cmp byte ptr [rax+0xA3],1` | per-voxel opaque-flag byte compare inside the flood fill; "not a camera frustum plane test" is [I] | [V] |
| Flood-fill task body driver 0x792e630 calls per-section compute 0x6b0c4c0 | 8 | call target 0x6B0C4C0 | `0x792e92c  call 0x6B0C4C0` | task body drives the flood fill per section | [V] |
| Device init 0xe807ff0 vtable slot read [rax+0x18] | 8 | [rax+0x18] | `0xe8082b3  mov rax,[rax+0x18]` | CheckFeatureSupport slot (+0x18) used at device init; CreateQueryHeap slot +0xB8 absent | [V] |
| Device init vtable slot read [rax+0x20] | 8 | [rax+0x20] | `0xe8082c9  mov rax,[rax+0x20]` | CreateCommandQueue slot (+0x20) used | [V] |
| Device init vtable slot read [rax+0x28] | 8 | [rax+0x28] | `0xe8082df  mov rax,[rax+0x28]` | CreateCommandAllocator slot (+0x28) used | [V] |
| Device init vtable slot read [rax+0x68] | 8 | [rax+0x68] | `0xe80834e  mov rax,[rax+0x68]` | CreateDescriptorHeap slot (+0x68) used | [V] |

## 4. Row meanings
- Rows 1-5: instruction facts [V]; all proof lines re-disassembled verbatim from `rdis dis 0x10f45d0`; string 0xF516745 shows the name "frustum_visibility" [V]; length 0x12 = 18 chars matches [V]; deserialized value is a dword (`mov eax`/`mov [rbp+0x3E0],eax`) [V].
- Row 6: Block+0xA3 opaque-flag byte compare inside per-voxel flood fill — chunk/section visibility via cave connectivity [V]; "not a camera frustum plane test" is [I] (frustum-aware traversal consumer unlocated — H3b/H1b).
- Row 7: task body drives the flood fill per section [V].
- Rows 8-11: device init touches only vtable slots +0x18/+0x20/+0x28/+0x68 [V]; CreateQueryHeap slot 23 = +0xB8 absent; no "CreateQueryHeap" string in the exe [V] (older note's `0xe80821a` was a misquote — the +0x18 read is at 0xe8082b3 [V]).

## 5. Other frustum/cull anchors (completeness only)
- frustum_visibility string 0xF516745 -> only ref 0x10f45d0 (lighting config) [V row 1]
- max_shadow_frustum_radius string 0xF543489 -> fn 0x53fcac0 (shadow cascade setup) [V]
- CameraAimAssistCacheFrustumSystem / CameraAimAssistCachedFrustumComponent 0xF59D48F -> no code refs [V]
- No string or RTTI anchor for a camera frustum-cull class exists in the exe [V negative]

## CLOSES?
CLOSES? NO — the single blocking fact: live confirmation of el10b_lighting_desc at 0x10f09f0 is still missing — the capture exists but returned hits=0 samples=0 (no REG=value bytes, no ret= caller chain, no description bytes) and request.py won't re-add it (entry state `done`, rejected as already queued). Everything static is proven [V]: frustum_visibility is a scalar float light-scoring-weight field in lighting-config deserializer 0x10f09f0, sole site 0x10f45d0 (key ptr [rbp+0x280], len 0x12 at [rbp+0x288], value dword [rbp+0x2E0] -> [rbp+0x3E0]); producer chain sub_111e590 -> sub_1152460 -> sub_10f09f0 (load-time JSON config load, not per-frame culling); no 6-plane frustum test, no CreateQueryHeap/vtable+0xB8 call site, no camera-frustum string anchor anywhere in the static binary; located visibility culling is voxel flood fill (Block+0xA3, 0x791f170/0x792e630/0x6b0c4c0). What remains unconfirmed (needs a live hit that does not exist yet): descriptor bytes at the 0x10f09f0 entry and the ret= caller chain naming sub_1152460/sub_111e590 live. BGFX_MAP 6bj: "there is no engine frustum-cull function behind this string" [V].

## Verification
Run `python tools/delegate.py check docs/progress/oc_U-EL10b.md`. All quoted `0xRVA  instr` lines re-disassembled verbatim from rdis `dis` output of Minecraft.Windows.exe 1.26.62.01: frustum_visibility site group 0x10f45d0 (0x10f45d0/0x10f45d7/0x10f45de/0x10f45e9/0x10f45f0/0x10f45fa/0x10f4653/0x10f4659); 0x791f4ac; 0x792e92c; device-init vtable reads 0xe8082b3/0xe8082c9/0xe8082df/0xe80834e. No raw instruction dumps pasted; every proof line is inside a table cell; no duplicate first-column offsets; 11 rows >= 3; no shorthand ellipsis anywhere.

## TOOL REQUESTS
- CAPTURE REQUESTED el10b_lighting_desc — needed: descriptor bytes + ret= caller chain at entry 0x10f09f0; existing entry state `done` with hits=0 samples=0 (header-only) [V live][LIVE docs/data/live/el10b_lighting_desc.txt:1-2]; re-add blocked ("already queued"); 3 of 4 pending slots held by other units. (Would-be command: `python tools/livecap/request.py add el10b_lighting_desc 0x10f09f0 --size 0x100 --max 6 --why "L10b: confirm frustum_visibility descriptor bytes live and name the ret= caller chain (producer sub_1152460/sub_111e590); triggers on loading lighting config JSON in a lobby"`)
- Helper scripts: None (all verification via rdis.exe; no new helpers needed).
