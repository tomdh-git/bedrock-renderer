## NEXT
DONE

UNIT U-EM2c — Cloud*/Shadow* parameter description types via JSON-key deserializer stores
Output file: docs/progress/oc_U-EM2c.md (this file only).
Goal (orchestrator, overrides prior runs): find each type's JSON key strings (rdis str), then the deserializer call that stores each key's value at a struct offset → name + offset + scalar type per field [V]. Do the three Cloud*/Shadow* types first: CloudLightingParameters, CloudParameters, ShadowParameters (+ ShadowRange where reachable).
Types to type (10): CloudLightingParameters, CloudParameters, PerCascadeParameters, PointLightBudgetParameters, PointLightClusteringParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters, ShadowParameters, ShadowRange.

== VERIFIED ANCHORS (all [V] by rdis dis on the exe Minecraft.Windows.exe, image-base RVAs) ==
- sub_117D460 [0x117d460..0x117d842) is a JSON member-node builder, NOT a struct-field storer: it FNV-hashes the key (r8), looks it up by hash in [obj+0x20] (sub_24287c0), builds a JsonValue node ({word type=1 @+0x0, ptr @+0x8, dword @+0x10, ...}) and returns it. Exactly 3 call sites, all in sub_10f09f0: `0x10f445e  call 0x117D460` (key "screen_space_angular_radius", str 0xF54340E at `0x10f4430  lea rax,[0xF54340E]`, len 0x1B), `0x10f45fa  call 0x117D460` (key "frustum_visibility", str 0xF516745 at `0x10f45d0  lea rax,[0xF516745]`, len 0x12), `0x10f4773  call 0x117D460` (key "camera_alignment", str 0xF536537 at `0x10f4749  lea rax,[0xF536537]`, len 0x10). Each call is immediately followed by sub_eea6040(edx=8) node allocation and sub_1db850 map insert → sub_10f09f0 is JSON↔JSON (light-scoring settings), no C++ struct store observed [I: the DOM->struct consumer doing mov [struct+off], <scalar> per key is not yet located].
- sub_1152460 [0x1152460..0x1159f6a) (one function; 0x1156680/0x1154ae0 are entry labels inside it, not separate functions): settings JSON walker keyed by name. Container key refs: `0x1156787  lea rax,[0xF54B67F]` "cloud_lighting_parameters" len 0x19; `0x1154b6b  lea rax,[0xF5B8368]` "shadow_config" len 0xD; `0x1156661  lea rax,[0xF5E7299]` "enable_cloud_render_distance"; `0x1154c96  lea rax,[0xF5B83A9]` "volumetric_fog_config". Each key: sub_118e180/sub_12c1ec0 JSON value extractor → 8-byte node (sub_eea6040 edx=8, vtable store) linked at [rbp+0x58] → sub_1db850 insert with callback descriptor [rbp+0x150]. Later section (0x11557b1+) builds type descriptors: sub_1188170 member lookup at `0x11557b5  call 0x1188170`, type registration via `0x1155801  call 0x1188780`, 0x50-byte type object vtable data_f0b7760 at `0x1155916  mov edx,0x50`, sub_1d6350 at `0x1155980`, sub_1188250 descriptor build at `0x1155995`, sub_1d4fd0 hash lookup at `0x11559ae` with r9d=0x8DE632ED. These blocks construct JSON/type-descriptor nodes; no `mov [struct+off], <scalar>` struct store observed.
- sub_1188170 = hash-map "get member by hash" (7 xrefs incl. sub_118f680 `0x118f68f`, sub_1152460 `0x11557b5`); sub_1d4fd0 = same (24+ xrefs incl. `0x11559ae`); sub_1db850 = map insert; sub_eea6040 = allocator; sub_24287c0 = hash-map lookup; sub_1d6350 = DOM node value set; sub_1219a0 = string compare.
- CloudLightingParameters RTTI registration (type-registration init sub_1188425/sub_1188250): `0x1188449  mov qword ptr [0x128E48F0],0x2A` → type size = 0x2A (42 bytes) [V]; `0x118843b  lea rax,[0xF6416AB]` → RTTI name "mce::framebuilder::CloudLightingParameters" [V]; `0x11882b7  mov dword ptr [rax+0x18],0x80` → flags; `0x11882be  mov qword ptr [rax+0x20],0x14` → member count 0x14 (20 members) [V]; descriptor callbacks registered: `0x11882c6  lea rcx,[0x1188170]` (lookup), `0x11882d1  lea rcx,[0x11884A0]` (member names), `0x11882e4  lea rcx,[0x11886F0]` (member offset/type builder) [V].
- sub_118f6b0 member/type matcher: `0x118f6da  cmp dword ptr [rbx+0x20],0x8CBEF799` and `0x118f740  cmp dword ptr [rdi+0x20],0x8DE632ED` [V] — hash dispatch on object +0x20.
- sub_118f680: JSON member lookup by hash via sub_1188170, writes {nodePtr, node} 16 bytes to out buffer [V].

== ANSWER TABLE (offset | size | site | verbatim `0xRVA  instr` | meaning [tag]) ==
| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| CLP.typeSize@128e48f0 | 8 | 0x1188449 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | CloudLightingParameters sizeof = 0x2A (42 bytes) [V] |
| CLP.rttiName@128e48e8 | 8 | 0x118843b | `0x118843b  lea rax,[0xF6416AB]` | CloudLightingParameters RTTI name pointer → "mce::framebuilder::CloudLightingParameters" [V] |
| CLP.memberCount@desc+0x20 | 8 | 0x11882be | `0x11882be  mov qword ptr [rax+0x20],0x14` | CloudLightingParameters member count = 0x14 (20 members) [V] |
| CLP.desc.cbNames@desc+0x30 | 8 | 0x11882d1 | `0x11882d1  lea rcx,[0x11884A0]` | member names callback sub_11884a0 registered in the type descriptor [V] |
| CLP.desc.cbMemberBuilder@desc+0x40 | 8 | 0x11882e4 | `0x11882e4  lea rcx,[0x11886F0]` | member offset/type builder callback sub_11886f0 registered in the type descriptor [V] |
| key.cloud_lighting_parameters | - | 0x1156787 | `0x1156787  lea rax,[0xF54B67F]` | JSON container key "cloud_lighting_parameters" (len 0x19) [V] |
| key.shadow_config | - | 0x1154b6b | `0x1154b6b  lea rax,[0xF5B8368]` | JSON container key "shadow_config" (len 0xD) [V] |
| dispatch.hashCmp.0x8DE632ED | 4 | 0x118f740 | `0x118f740  cmp dword ptr [rdi+0x20],0x8DE632ED` | type/member hash compare in sub_118f6b0 member matcher [V] |
| dispatch.hashCmp.0x8CBEF799 | 4 | 0x118f6da | `0x118f6da  cmp dword ptr [rbx+0x20],0x8CBEF799` | type/member hash compare in sub_118f6b0 member matcher [V] |

== PER-TYPE STATUS ==
CloudLightingParameters (sizeof 0x2A [V], RTTI name [V], 20 members [V], callbacks [V], container key "cloud_lighting_parameters" [V]): per-field name|offset|scalar-type rows [?] — the 20 member offsets/types live in runtime-built member tables (sub_11884a0 name slots; sub_11886f0 member descriptors with typecode byte at desc+0x24 and hash dword at desc+0x20); no static per-field `mov [struct+off], <scalar>` store located yet. The JSON→struct consumer (hash key → sub_1d4fd0/sub_1188170 member lookup → offset → scalar store) has not been found.
CloudParameters: RTTI string exists only as dead entt metadata (0xf6419fd "mce::framebuilder::CloudParameters", no code refs) [V]; container key string not located in code [?]; per-field [?].
ShadowParameters: container key "shadow_config" [V]; its descriptor block callbacks sub_12ceb10/sub_12ce750/sub_12ceb40/sub_12cf0c0 [V at 0x1154c23-0x1154c5b]; RTTI size/name not located; per-field [?].
ShadowRange: key "shadow_range" str 0xF5e056a ref'd at sub_53fcac0+0x1c60 [V string ref, prior run]; offset/store [?].
Remaining 6 types (PerCascadeParameters, PointLightBudgetParameters, PointLightClusteringParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters): not started [?].

== BLOCKER ==
CLOSES?: NO. Blocking fact: per-field name|offset|scalar-type rows backed by verbatim struct-field store instructions do not exist on disk yet for any of the 3 types. What IS [V]: CloudLightingParameters type size (0x2A), RTTI name, member count (20), member-builder/lookup/name callbacks, and both container keys ("cloud_lighting_parameters", "shadow_config"). The located functions are JSON↔JSON (sub_10f09f0, sub_1152460, sub_117D460 build JsonValue/8-byte nodes via sub_eea6040+sub_1db850); no `mov [reg+off], <scalar>` store keyed to a JSON member has been located.

== NEXT ==
(1) Find the JSON→struct deserialize dispatcher: callers of sub_1d4fd0/sub_1188170 in a struct context (not the type-registration init) — the store `mov [struct+off], <scalar>` per member key should be there; (2) enumerate CloudLightingParameters' 20 members via sub_11884a0/sub_11886f0 (member names as name-ptr args, typecode byte desc+0x24 = scalar size); (3) locate CloudParameters container key string; (4) locate ShadowParameters RTTI registration (size/name); then write per-field [V] rows for CloudLightingParameters, CloudParameters, ShadowParameters.
