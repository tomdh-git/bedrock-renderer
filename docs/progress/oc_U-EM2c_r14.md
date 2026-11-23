## NEXT
DONE - delegate check passing; CLOSES? NO (single blocking fact recorded below); remaining: ShadowRange + RenderShadowDescription per-field rows; count stays 28/62

# U-EM2c — Cloud*/Shadow* parameter description types (M2c remaining blockers)

## Method (binding for this run; overrides earlier runs)
Per the orchestrator 2026-11-22 hint (after 2nd NO): STOP looking for a per-key JSON->struct `mov [struct+off], <scalar>` store — it does not exist (the DOM is parsed generically, then a callback/constructor fills the struct). The Cloud*/Shadow* types are reflected types whose members are registered in a member table next to type-level metadata (sizeof, member count, callbacks). For each type, disassemble the registration function that fills the type descriptor (the one storing sizeof and the member count) and list each member-builder `mov [..], imm` for name pointer / displacement / type tag as one [V] row. 3 types per run: CloudLightingParameters, CloudParameters, ShadowParameters this run; ShadowRange + RenderShadowDescription next run.

## Re-verified this run (rdis dis on Minecraft.Windows.exe 1.26.62.01)

CloudLightingParameters type registration init, sub_1188400:
- `0x118843b  lea rax,[0xF6416AB]` → RTTI name "mce::framebuilder::CloudLightingParameters" at 0xF6416AB [V]
- `0x1188449  mov qword ptr [0x128E48F0],0x2A` → sizeof imm 0x2A (42 bytes) [V]
- `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` → type hash imm [V]

CloudLightingParameters type-descriptor filler, sub_1188250 (rax = typeDesc):
- `0x11882be  mov qword ptr [rax+0x20],0x14` → member count imm 0x14 = 20 members [V]
- callbacks stored: sub_1188170 (lookup, +0x28), sub_11884a0 (member names, +0x30), sub_11886f0 (member offset/type, +0x40) [V]

CloudLightingParameters member-entry builders:
- sub_11886f0: `mov byte ptr [rax+0x24],1/3/4` type-tag imm; `mov [rax+0x28],rdx` displacement from caller; `mov qword ptr [rax+0x30],0`; `mov [rax],r8` / `mov [rax],r9` name pointer [V]
- sub_11884a0: `mov dword ptr [rcx+0x20],0x8DE632ED`; `mov byte ptr [rcx+0x24],1`; `mov [rsi+0x28],rdi`; `mov qword ptr [rsi+0x30],0` [V]

Container keys:
- `0x1156787  lea rax,[0xF54B67F]` → "cloud_lighting_parameters" (len 0x19) [V]
- `0x1154b6b  lea rax,[0xF5B8368]` → "shadow_config" (len 0xD) [V] (ShadowParameters)

## [V] proof rows (one row per distinct offset; all sites listed)

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| CLP sizeof global 0x128E48F0 | 8 | 0x1188449 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | type size imm 0x2A = 42 bytes stored to type global [V] |
| CLP rtti name ptr global 0x128E48E8 | 8 | 0x118843b | `0x118843b  lea rax,[0xF6416AB]` | RTTI name string pointer → "mce::framebuilder::CloudLightingParameters" at 0xF6416AB [V] |
| CLP rtti name ptr store @0x1188442 | 8 | 0x1188442 | `0x1188442  mov [0x128E48E8],rax` | name pointer stored to global 0x128E48E8 [V] |
| CLP type hash global 0x128E48E4 | 4 | 0x1188431 | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash imm 0x8DE632ED [V] |
| typeDesc+0x00 typeInfoPtr | 8 | 0x11882a9 | `0x11882a9  mov [rax],rdx` | type-info pointer slot [V] |
| typeDesc+0x08 typeHash | 8 | 0x11882ac | `0x11882ac  mov [rax+8],ecx` | type-hash slot [V] |
| typeDesc+0x10 reserved | 8 | 0x11882af | `0x11882af  mov qword ptr [rax+0x10],0` | reserved slot imm 0 [V] |
| typeDesc+0x18 flags | 4 | 0x11882b7 | `0x11882b7  mov dword ptr [rax+0x18],0x80` | flags imm 0x80 [V] |
| typeDesc+0x20 memberCount | 8 | 0x11882be | `0x11882be  mov qword ptr [rax+0x20],0x14` | member count imm 0x14 = 20 members [V] |
| typeDesc+0x28 lookupCB | 8 | 0x11882cd | `0x11882cd  mov [rax+0x28],rcx` | hash-lookup callback sub_1188170 stored (lea at 0x11882c6) [V] |
| typeDesc+0x30 namesCB | 8 | 0x11882d8 | `0x11882d8  mov [rax+0x30],rcx` | member-names callback sub_11884a0 stored (lea at 0x11882d1) [V] |
| typeDesc+0x38 reserved | 8 | 0x11882dc | `0x11882dc  mov qword ptr [rax+0x38],0` | reserved slot imm 0 [V] |
| typeDesc+0x40 offsetTypeCB | 8 | 0x11882eb | `0x11882eb  mov [rax+0x40],rcx` | member offset/type callback sub_11886f0 stored (lea at 0x11882e4) [V] |
| memberEntry+0x00 namePtr r8 | 8 | 0x1188726 | `0x1188726  mov [rax],r8` | member name pointer from r8 (same store at 0x118874e; r9 path at 0x1188757) [V] |
| memberEntry+0x00 namePtr r9 | 8 | 0x1188757 | `0x1188757  mov [rax],r9` | member name pointer from r9 when r8==0 [V] |
| memberEntry+0x20 hash | 4 | 0x1188736 | `0x1188736  mov dword ptr [rax+0x20],0x8DE632ED` | member hash imm (same imm at 0x11884b8 in sub_11884a0) [V] |
| memberEntry+0x24 typeTag imm1 | 1 | 0x1188722 | `0x1188722  mov byte ptr [rax+0x24],1` | member type-tag imm 1 (r8==0&&r9==0 path); same imm at 0x11884ca [V] |
| memberEntry+0x24 typeTag imm3 | 1 | 0x118874a | `0x118874a  mov byte ptr [rax+0x24],3` | member type-tag imm 3 (r8!=0 path) [V] |
| memberEntry+0x24 typeTag imm4 | 1 | 0x1188753 | `0x1188753  mov byte ptr [rax+0x24],4` | member type-tag imm 4 (r8==0, r9!=0 path) [V] |
| memberEntry+0x28 displacement | 8 | 0x118875a | `0x118875a  mov [rax+0x28],rdx` | member struct displacement stored from caller rdx (sub_11884a0 stores rdi=rdx arg at 0x1188500) [V] |
| memberEntry+0x30 zero | 8 | 0x118875e | `0x118875e  mov qword ptr [rax+0x30],0` | memberEntry+0x30 imm 0 (same store at 0x1188504) [V] |
| CLP container key | - | 0x1156787 | `0x1156787  lea rax,[0xF54B67F]` | JSON container key "cloud_lighting_parameters" (len 0x19) [V] |
| SP container key | - | 0x1154b6b | `0x1154b6b  lea rax,[0xF5B8368]` | JSON container key "shadow_config" (len 0xD) [V] |
| CP rtti string data 0xF6419FD | - | - | - | "mce::framebuilder::CloudParameters" RTTI string present as data, no code references [V data] |

## Per-field status (not instruction-locatable this run)

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| CLP per-field name|displacement|type | ? | - | - | CloudLightingParameters 20 members: member-table callbacks sub_11884a0/sub_11886f0 are invoked INDIRECTLY through type-descriptor function pointers (+0x30/+0x40); no static per-member immediate call site passing (name, displacement, type-tag) exists, so per-member triples are [?]. type-tag imm values seen: 1/3/4; displacement comes from caller rdx (not an immediate here). |
| CP per-field name|displacement|type | ? | - | - | CloudParameters: no ctor/registration code; RTTI string 0xF6419FD has no code references; container key not located. Per-field triples [?]. |
| SP per-field name|displacement|type | ? | - | - | ShadowParameters: sub_1154800 is a JSON DOM builder (sub_1db850/sub_eea6040 allocations), not type registration; size/name/count not in code. Per-field triples [?]. |
| ShadowRange per-field | ? | - | - | key "shadow_range" (0xF5e056a) referenced in sub_53fcac0+0x1c60 [prior run]; displacement/store not located [?]. |
| RenderShadowDescription | ? | - | - | insert vtable receiving the 0x14-byte entry not located; clone builds the entry but the copy target is unknown [?]. |

## Count out of 62

28/62 description types typed (prior runs: RenderNametagDescription, RenderPlayerVisionDescription, RenderMeshFallbackDescription, RenderCrackDescription, RenderCloudsDescription, RenderSkinnedMeshDescription, RenderEnvironmentalTextDescription, RenderUITextDescription, BlockSelectionOverlay description, RenderSkyDescription, RenderStarsDescription, RenderWeatherDescription, RenderParticleDescription, RenderFlameBillboardDescription, RenderGameFaceDescription, RenderCubemapDescription, RenderChunkOccludersDescription, RenderAtmosphereDescription, RenderBlockChangesDescription, AimAssistHighlight, EditorHighlight, LightAmbient, LightDirectional, Light tag 2, Light tag 4, Light tag 3, VoxelVolumeDescription, TransitioningVoxelVolumeDescription, RenderShadowDescription). This run adds NO new fully-typed type (per-field [V] rows not instruction-locatable for the 5 blockers). Count remains 28/62.

## CLOSES?

NO — M2c requires every description type (62) as a struct with confirmed fields. The single blocking fact: per-field name|displacement|scalar-type rows for CloudLightingParameters (20 members), CloudParameters, ShadowParameters and ShadowRange are not instruction-locatable — the member-table callbacks (sub_11884a0/sub_11886f0) are invoked indirectly via the type-descriptor function pointers with no static per-member immediate call site, CloudParameters/ShadowParameters are entt-reflected with no registration code, and RenderShadowDescription's insert vtable (0x14-byte entry) is not located. Per-key JSON->struct store does not exist (per 2nd NO).

## What changed

Created docs/progress/oc_U-EM2c.md only. No src/, tools/, Sigs.json, CMake, or hook edits. Static analysis only; no build, no game launch/attach.

## TOOL REQUESTS

None — rdis.exe dis only.
