## NEXT
DONE

# UNIT U-EM2c — M2c: description types as structs with confirmed fields (Cloud*/Shadow* parameter types first)

GOAL (overrides all prior runs): type the Cloud*/Shadow* parameter description types FIRST, then continue a batch of 8 untyped types with known size + [V] ctor/visitor evidence. Output file: docs/progress/oc_U-EM2c.md only. Static analysis only; no build, no game launch/attach.

## 1. What changed

- Created docs/progress/oc_U-EM2c.md (this note). No src/, tools/, Sigs.json, CMake, or hook edits. No existing files edited (Descriptions.h not modified).

## 2. Types targeted this run (Cloud*/Shadow* first)

The 12 parameter types have NO ctor/visitor evidence — they are lighting/atmosphere settings loaded from JSON by key name, not visited per-frame. The M2c r2 method (insert<Description> by-id route, rdis class/vt on RTTI names, functions_full.tsv strings2/callers3 to find ctors, ctor store dumps) does NOT apply: these types have no insert clones in BGFX_MAP.md section 6g, no constructors in functions_full.tsv, and no ctor stores. rdis `class` on 0xF6416AB returns "no vtable matches"; `vt` reads only the string data. The JSON-deserializer route (sub_10f09f0, sub_1152460, sub_117D460) builds JsonValue/JsonMap DOM objects (allocator sub_eea6040, map insert sub_1db850, hash lookup sub_1d4fd0/sub_1188170) — sub_117D460 has exactly 3 call sites in sub_10f09f0, none writing a C++ struct field. The DOM->struct consumer (`mov [struct+off], <scalar>` per key) was NOT located despite exhaustive searching (r8/r9). xref callers of sub_1d4fd0 (30+ sites, all general hash-map/lookup) and sub_1188170 (5 sites: sub_1152460 type-registration walker, sub_1188540/1188f00/1188f70 type-registration init, sub_118f680 JSON member lookup writing to an out buffer) — none fills a struct from JSON.

Per-field name|offset|scalar-type rows are therefore [UNVERIFIED] / [?] for all 4 Cloud*/Shadow* types. Only type-level metadata (sizeof, RTTI name, member count, callbacks, container keys) is [V]-proven.

### 2.1 CloudLightingParameters (sizeof 0x2A = 42 bytes [V])

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| CLP.sizeof | 8 | 0x1188449 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | type size stored at global 0x128E48F0 = 0x2A (42 bytes) [V] |
| CLP.rttiNamePtr | 8 | 0x118843b | `0x118843b  lea rax,[0xF6416AB]` | RTTI name string pointer → "mce::framebuilder::CloudLightingParameters" at 0xF6416AB [V] |
| CLP.memberCount | 8 | 0x11882be | `0x11882be  mov qword ptr [rax+0x20],0x14` | member count = 0x14 (20 members) in type descriptor [V] |
| CLP.cbNames | 8 | 0x11882d1 | `0x11882d1  lea rcx,[0x11884A0]` | member names callback sub_11884a0 registered [V] |
| CLP.cbMemberBuilder | 8 | 0x11882e4 | `0x11882e4  lea rcx,[0x11886F0]` | member offset/type builder callback sub_11886f0 registered [V] |
| CLP.cbLookup | 8 | 0x11882c6 | `0x11882c6  lea rcx,[0x1188170]` | hash-map lookup callback sub_1188170 registered [V] |
| CLP.containerKey | - | 0x1156787 | `0x1156787  lea rax,[0xF54B67F]` | JSON container key "cloud_lighting_parameters" (len 0x19), ref'd in sub_1156680 inside sub_1152460 [V] |
| CLP.hashCmpA | 4 | 0x118f740 | `0x118f740  cmp dword ptr [rdi+0x20],0x8DE632ED` | type/member hash compare in sub_118f6b0 member matcher [V] |
| CLP.hashCmpB | 4 | 0x118f6da | `0x118f6da  cmp dword ptr [rbx+0x20],0x8CBEF799` | type/member hash compare in sub_118f6b0 member matcher [V] |

Per-field rows (name | offset | scalar type): [UNVERIFIED] — sub_11884a0 (names) and sub_11886f0 (member descriptors with typecode byte at desc+0x24 and hash dword at desc+0x20) build runtime member tables; no static `mov [struct+off], <scalar>` store located. [UNVERIFIED: 0x11884a0/0x11886f0 what are the 20 member offsets/types for CloudLightingParameters?]

### 2.2 CloudParameters

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| CP.rttiString | - | - | (dead entt string only) | "mce::framebuilder::CloudParameters" at 0xF6419FD, no code references [V] |

Container key string: not located in code [?]. Per-field rows: [UNVERIFIED] — no deserializer, no container key, no ctor, no visitor. [UNVERIFIED: 0xf6419fd where is CloudParameters constructed/deserialized and what are its fields?]

### 2.3 ShadowParameters

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| SP.containerKey | - | 0x1154b6b | `0x1154b6b  lea rax,[0xF5B8368]` | JSON container key "shadow_config" (len 0xD), ref'd in sub_1154800 inside sub_1152460 [V] |
| SP.cbA | 8 | 0x1154c23 | (descriptor callback block at 0x1154c23-0x1154c5b) | sub_12ceb10/sub_12ce750/sub_12ceb40/sub_12cf0c0 descriptor callbacks registered [V] |

RTTI size/name: not located [?]. Per-field rows: [UNVERIFIED] — no struct store found. [UNVERIFIED: 0x1154800 where is ShadowParameters constructed and what are its field offsets/types?]

### 2.4 ShadowRange

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| SR.key | - | sub_53fcac0+0x1c60 | (string ref in sub_53fcac0) | JSON key "shadow_range" at str 0xF5e056a, referenced inside sub_53fcac0 [V string ref] |

Offset/store: [UNVERIFIED]. [UNVERIFIED: sub_53fcac0+0x1c60 what struct offset does shadow_range get stored at?]

## 3. Remaining 8 parameter types (not started)

PerCascadeParameters, PerCascadeParameters*, PointLightBudgetParameters, PointLightBudgetParameters::ScoringWeights, PointLightClusteringParameters, PointLightShadowParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters — no keys, no deserializers, no RTTI, no per-field evidence located [?].

## 4. Blocker

Per-field name|offset|scalar-type rows for CloudLightingParameters (20 members), CloudParameters, ShadowParameters, ShadowRange cannot be produced from static analysis: the JSON deserializers build DOM objects (JsonValue/JsonMap via sub_eea6040+sub_1db850) and the DOM->struct consumer that performs `mov [struct+off], <scalar>` per member key has not been located. xref of sub_1d4fd0/sub_1188170 shows only type-registration and JSON↔JSON callers, no struct-filling context. rdis `class`/`vt` on the RTTI name strings finds no vtables (the names are data, not vtables). functions_full.tsv has no constructor entries for these types.

## 6. CLOSES?

NO — M2c requires every description type (62) as a struct with confirmed fields. The 4 Cloud*/Shadow* types have type-level [V] metadata (sizeof, RTTI name, member count, callbacks, container keys) but NO per-field [V] rows. Single blocking fact: the JSON-key→struct-offset store (DOM->struct consumer) for the parameter types is not instruction-located, so per-field name|offset|scalar-type cannot be proven [V].

## 7. TOOL REQUESTS

None — rdis.exe dis/class/vt/str and tools/sigs/xref.py callers only; no helper scripts written.