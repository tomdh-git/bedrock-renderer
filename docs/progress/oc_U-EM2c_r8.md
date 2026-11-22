## NEXT
DONE field anchors verified; per-type field->offset stores not yet located (see CLOSES?)

UNIT U-EM2c — Cloud*/Shadow* parameter description types (typing via JSON-key deserializer stores)
Output file: docs/progress/oc_U-EM2c.md (this file only).
Goal: type the 10 'purely untyped' parameter types by finding each type's JSON key strings (rdis str), then the deserializer call that stores each key's value at a struct offset → name + offset + scalar type per field [V]. Do the three Cloud*/Shadow* types first.

Types to type (10): CloudLightingParameters, CloudParameters, PerCascadeParameters, PointLightBudgetParameters, PointLightClusteringParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters, ShadowParameters, ShadowRange.

== METHOD VERIFIED (anchors, all [V] by rdis dis/str/callers on the exe) ==
- Scalar deserializer 0x117D460 (sub_117d460): rdis callers shows exactly ONE caller, sub_10f09f0, with 3 call sites [V]: 0x10f445e, 0x10f45fa, 0x10f4773.
- Key string "frustum_visibility" lives at 0xF516745 and is referenced at 0x10f45d0 inside sub_10f09f0 (the BGFX_MAP 0x10f45d0 site is the code ref, not the string address) [V].
- Container key strings located [V]: "cloud_lighting_parameters" str 0xF54B67F ref'd at 0x1156787 (sub_1156680); "shadow_config" str 0xF5B8368 ref'd at 0x1154b6b (sub_1154800); "cloud_mesh_size" str 0xF5bb7a4 ref'd ~0x115642a.
- Deserializer functions located [V]: sub_10f09f0 (lighting settings; single call site at sub_1152460+0x403 = 0x1152863), sub_1156680 (cloud_lighting_parameters), sub_1154800 (shadow_config), sub_53fcac0 (shadow/cloud settings, refs max_shadow_frustum_radius, shadow_range, cloud_shadow_*, sun/moon_shadows).
- sub_10f09f0 / sub_1156680 / sub_1154800 build a JsonObject via the shared DOM framework: 0x50-byte allocation (sub_eea6040 edx=0x50) at 0x10f0bd1/0x10f0bd8 (r14) and 0x1156a12/0x1156a1e (r14), vtable data_f0b7760, then sub_1db850 (hash-map member insert) + sub_1d4fd0 (get member by hash) + sub_1d6350 (DOM node value set). No direct C++ struct field store observed in these functions [I: stores are in the separate DOM->struct consumer, not yet located].

== ANSWER TABLE (offset | size | site | verbatim `0xRVA  instr` | meaning [tag]) ==
| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| 0xF516745 | - | R | `0x10f45d0  lea rax,[0xF516745]` | JSON key string "frustum_visibility", loaded inside sub_10f09f0 [V] |
| 0x10f45fa | 8 | C | `0x10f45fa  call 0x117D460` | scalar deserializer call for frustum_visibility (key at 0x10f45d0) [V] |
| 0x10f445e | 8 | C | `0x10f445e  call 0x117D460` | scalar deserializer call for screen_space_angular_radius (key at 0x10f4430) [V] |
| 0x10f4773 | 8 | C | `0x10f4773  call 0x117D460` | scalar deserializer call for camera_alignment (key at 0x10f4749) [V] |
| 0xF54B67F | - | R | `0x1156787  lea rax,[0xF54B67F]` | JSON key string "cloud_lighting_parameters", ref'd in sub_1156680 [V] |
| 0xF5B8368 | - | R | `0x1154b6b  lea rax,[0xF5B8368]` | JSON key string "shadow_config", ref'd in sub_1154800 [V] |
| 0x10f0bcc | 4 | - | `0x10f0bcc  mov edx,0x50` | 0x50-byte allocation size for the JsonObject built by sub_10f09f0; result stored in r14 at `0x10f0bd8  mov r14,rax` [V] |
| 0x1156a12 | 4 | - | `0x1156a12  mov edx,0x50` | 0x50-byte allocation size for the JsonObject built by sub_1156680; store at 0x1156a1e `mov r14,rax` [V] |

== PER-TYPE STATUS (field name + offset + scalar type) ==
CloudLightingParameters: container key "cloud_lighting_parameters" (0xF54B67F @ 0x1156787, sub_1156680) [V]; field keys/offsets/stores not yet instruction-verified [?].
CloudParameters: no field key strings located yet; deserializer not yet located [?].
ShadowParameters: container key "shadow_config" (0xF5B8368 @ 0x1154b6b, sub_1154800); sub_53fcac0 references shadow_range (0xF5e056a @ 0x53fcac0+0x1c60), max_shadow_frustum_radius (+0x1fc1), cloud_shadow_* [V string refs]; field offsets/stores not yet instruction-verified [?].
ShadowRange: key "shadow_range" str 0xF5e056a ref'd in sub_53fcac0+0x1c60 [V]; offset/store [?].
Remaining 6 types (PerCascadeParameters, PointLightBudgetParameters, PointLightClusteringParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters): no keys/deserializer located yet [?].

== BLOCKING FACT ==
The JSON deserializers found (sub_10f09f0, sub_1156680, sub_1154800, sub_53fcac0) build JsonValue/JsonMap DOM objects (0x50-byte allocations, sub_1db850 map insert, sub_1d4fd0 hash lookup) — none of them writes a C++ struct field at a concrete offset in the ranges disassembled. The DOM->struct consumer that performs `mov [struct+off], <scalar>` for each key has NOT been located, so field name+offset+scalar type for CloudLightingParameters/CloudParameters/ShadowParameters cannot yet be proven [V].

CLOSES? NO — the single blocking fact: the JSON-key→struct-offset store (DOM->struct consumer) for the Cloud*/Shadow* parameter types is not yet instruction-located; only container-key strings, deserializer entry points, and 0x117D460 call sites are [V]-proven above. Field name/offset/type rows remain [?].

== NEXT ==
Locate the DOM->struct consumer (callers of the JsonObject built by sub_10f09f0/sub_1156680, or the struct-filling reads of shadow_range/cloud_lighting_parameters fields), then write name|offset|size|instr|[V] rows per field for CloudLightingParameters, CloudParameters, ShadowParameters (and ShadowRange).

== WHAT CHANGED ==
Created docs/progress/oc_U-EM2c.md only. No src/, tools/, Sigs.json, CMake, or hook edits. Static analysis only; no build, no game launch/attach.

== TOOL REQUESTS ==
None.
