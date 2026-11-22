## NEXT
DONE

# UNIT U-EM2c — Cloud*/Shadow* parameter types: JSON-key → struct-offset stores

GOAL (overrides all prior runs): type the Cloud*/Shadow* parameter description types FIRST — for each type, find the JSON key strings (xref.py str), find the parse/deserialize function, walk up to the function that stores into the description, and list for each key: name | offset stored to | scalar type, each as a [V] instruction row. Then repeat for the Shadow* types. Output file: docs/progress/oc_U-EM2c.md only. Static analysis only; no build, no game launch/attach. No rtools.* (OPENCODE_BRIEF.md §6). exe: Minecraft.Windows.exe 1.26.62.01.

## Scope note

RenderCloudsDescription (0xA8) itself has NO JSON deserializer: it is filled by its ctor 0x668e940 from arguments, every field [V] (docs/progress/oc_U-EM2c_r3.md). This unit concerns the Cloud*/Shadow* PARAMETER types loaded from JSON by key name: CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange, plus the remaining 8 parameter types.

## Method (per type)

1. xref.py str "<JSON key>" → locate the key string and the function that references it.
2. Walk up into the parse/deserialize function; find `mov [struct+off], <scalar>` keyed to each member key.
3. Emit one row per key: name | offset | size | verbatim `0xRVA  instr` | meaning [V]. If no struct store exists for a key, emit a [UNVERIFIED] row with the question; never guess offsets or types as fact.

## 2.1 CloudLightingParameters — type-level metadata [V]

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

Per-field rows (name | offset stored to | scalar type): [UNVERIFIED] — sub_11884a0 (names) and sub_11886f0 (member descriptors: hash dword at desc+0x20, typecode byte at desc+0x24) build runtime member tables; no static `mov [struct+off], <scalar>` store located for any of the 20 members. [UNVERIFIED: 0x11884a0/0x11886f0 what are the 20 member name/offset/typecode triples for CloudLightingParameters?]

## 2.2 CloudParameters

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| CP.rttiString | - | - | (dead entt string only) | "mce::framebuilder::CloudParameters" at 0xF6419FD, xref refs=[] — no code references whatsoever [V] |

Container key string: not located in code [?]. No deserializer, no ctor, no visitor. Per-field rows (name | offset stored to | scalar type): [UNVERIFIED]. [UNVERIFIED: 0xf6419fd where is CloudParameters constructed/deserialized and what are its fields?]

## 2.3 ShadowParameters

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| SP.rttiString | - | - | (dead entt string only) | "mce::framebuilder::ShadowParameters" at 0xF641005, xref refs=[] — no code references whatsoever [V] |
| SP.containerKey | - | 0x1154b6b | `0x1154b6b  lea rax,[0xF5B8368]` | JSON container key "shadow_config" (len 0xD), ref'd in sub_1154800 inside sub_1152460 [V] |
| SP.cbBlock | 8 | 0x1154c23 | (descriptor callback block at 0x1154c23-0x1154c5b) | sub_12ceb10/sub_12ce750/sub_12ceb40/sub_12cf0c0 descriptor callbacks registered [V] |

RTTI size/name: not located [?]. Per-field rows (name | offset stored to | scalar type): [UNVERIFIED] — no struct store found. [UNVERIFIED: 0x1154800 where is ShadowParameters constructed and what are its field offsets/types?]

## 2.4 ShadowRange — key dispatch located inside sub_53fcac0, NO struct store

sub_53fcac0 [0x53fcac0..0x53feac0), size 0x2000, 1 xref in (from 0x1152460 [V]). It is a JSON settings walker: each member key is looked up (sub_5437360) and the value is wrapped into an 8-byte JsonValue node (sub_eea6040 edx=8) then inserted into a map (sub_1db850) — JSON DOM only, no C++ struct store. Verified sites:

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| SR.shadowRangeKey | - | 0x53fe720 | `0x53fe720  lea rax,[0xF5E056A]` | JSON key "shadow_range" (str 0xF5E056A) loaded for member lookup at sub_53fcac0+0x1660 [V] |
| SR.shadowRangeLen | - | 0x53fe72e | `0x53fe72e  mov qword ptr [rbp+0x208],0xC` | key length 0xC for "shadow_range" [V] |
| SR.shadowRangeLookup | - | 0x53fe753 | `0x53fe753  call 0x5437360` | JSON member-lookup dispatch for shadow_range [V] |
| SR.shadowRangeNodeAlloc | - | 0x53fe76b | `0x53fe76b  call qword ptr [0xF99FFA0]` | sub_eea6040(edx=8): 8-byte JsonValue node allocation for the shadow_range value [V] |
| SR.shadowRangeInsert | - | 0x53fe844 | `0x53fe844  call 0x1db850` | map insert of the shadow_range node (JsonMap DOM) [V] |
| SR.shadowChunkRadiusKey | - | 0x53fe93e | `0x53fe93e  lea rax,[0xF543515]` | JSON key "shadow_chunk_radius" (str 0xF543515) — same walker, same DOM-only pattern [V] |

Offset/store for shadow_range: [UNVERIFIED] — no `mov [struct+off], <scalar>` for shadow_range anywhere in sub_53fcac0 (the walker's value path is node allocation + map insert). [UNVERIFIED: sub_53fcac0+0x1660 what struct offset does shadow_range get stored at, if any?]

## 2.5 What the located deserializers actually do (all [V], confirms the blocker)

- sub_10f09f0: JSON↔JSON light-scoring settings; exactly 3 call sites (0x10f445e "screen_space_angular_radius", 0x10f45fa "frustum_visibility", 0x10f4773 "camera_alignment"), each followed by sub_eea6040(edx=8) node alloc + sub_1db850 map insert. No struct store.
- sub_117D460: JSON member-node builder (FNV-hash key, sub_24287c0 lookup, {type,ptr,dword} node), 3 call sites, all in sub_10f09f0. No struct store.
- sub_1152460 (0x1152460..0x1159f6a): settings JSON walker keyed by container name ("cloud_lighting_parameters" at 0x1156787, "shadow_config" at 0x1154b6b, ...); builds JsonValue/8-byte nodes via sub_eea6040 + sub_1db850, registers type descriptors (sub_1188170 lookup, sub_1188780 registration, sub_1d6350 node set). No `mov [struct+off], <scalar>`.
- sub_53fcac0: shadow/cloud settings walker (above), DOM-only.
- sub_5438220 / sub_5438250 / sub_5438460: JsonValue node builders / type dispatch on byte at +0x24 with hash compares 0x7C2A4E8C / 0x990FE13D — node construction, not struct stores [V].

## 2.6 Remaining 8 parameter types (not started)

PerCascadeParameters, PerCascadeParameters*, PointLightBudgetParameters, PointLightBudgetParameters::ScoringWeights, PointLightClusteringParameters, PointLightShadowParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters — no keys, no deserializers, no RTTI code refs, no per-field evidence located [?].

## 3. Blocker (single blocking fact)

Per-field name|offset|scalar-type rows cannot be produced for any Cloud*/Shadow* parameter type: every located JSON deserializer builds JsonValue/JsonMap DOM objects (allocator sub_eea6040, map insert sub_1db850, hash lookup sub_1d4fd0/sub_1188170) and registers type descriptors at init; none performs `mov [struct+off], <scalar>` per member key. xref of sub_1d4fd0/sub_1188170 callers shows only type-registration and JSON↔JSON callers, no struct-filling context. CloudParameters and ShadowParameters have RTTI strings with zero code references (xref refs=[]). rdis `class`/`vt` on the RTTI name strings finds no vtables (the names are data, not vtables). The DOM→struct consumer that performs the key→offset store is not instruction-located.

## CLOSES?

NO — M2c requires every description type (62) as a struct with confirmed fields including per-field rows for all Cloud*/Shadow* parameter types. Per-field name|offset|scalar-type rows cannot be [V]-proven because the JSON-key→struct-offset store (DOM→struct consumer) for parameter types is not instruction-located: all located deserializers build JSON DOM only, no `mov [struct+off], <scalar>` per key found despite exhaustive xref of sub_1d4fd0/sub_1188170/sub_117D460/sub_53fcac0. All 62 types therefore do not have per-field rows. Single blocking fact: the JSON-key → struct-offset store for parameter types (Cloud*/Shadow*) is not instruction-located.

## What changed

Created: docs/progress/oc_U-EM2c.md only. No src/, tools/, Sigs.json, CMake, or hook edits. No existing files edited. Static analysis only; no build, no game launch/attach.

## TOOL REQUESTS

None — rdis.exe dis/str and tools/sigs/xref.py str/callers only; no helper scripts written.
