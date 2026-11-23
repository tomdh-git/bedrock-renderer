## NEXT
DONE — verified CloudLightingParameters type-level metadata [V] (sizeof 0x2A, member count 20, hash 0x8DE632ED, RTTI name, full descriptor layout at sub_1188250; member-builder sub_11886F0 takes name ptr/offset/type in registers). Proved no static per-member `mov [..], imm` rows exist for CloudLightingParameters/CloudParameters/ShadowParameters/ShadowRange (callbacks runtime-invoked, member-name strings have 0 data-section refs, located data table 0xF2922E0 unreferenced/not a description struct). RenderShadowDescription: insert RTTI string at 0xF65790F [V], insert vtable not located. Count 28/62, unchanged. CLOSES? NO — single blocking fact: per-field reflected member rows not instruction-locatable.

# UNIT U-EM2c — M2c: description types as structs with confirmed fields (Cloud*/Shadow* reflected types)

GOAL: Close checklist item M2c — every description type (62) as a struct with confirmed fields (Descriptions.h-compatible struct text). This run handles the remaining reflected blocker types CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange, RenderShadowDescription.

Rules (OPENCODE_BRIEF.md): static analysis only; every claim tagged [V]/[I]/[?]; verbatim `0xRVA  instr` lines (two spaces after address, copied from rdis); no skipped offsets; run `python tools/delegate.py check docs/progress/oc_U-EM2c.md` and fix every failure; only then set ## NEXT to DONE. Never ask questions — write [UNVERIFIED: 0xaddr question] and continue. Create only docs/progress/oc_U-EM2c.md; no src/, header, Sigs.json, CMake, or hook edits; no build, no game launch/attach.

62 framebuilder description types in the catalog. ~28-30 already typed (Descriptions.h or dedicated headers under src/sdk/mc/deps/minecraft_renderer/framebuilder/). Remaining untyped per orchestrator 2026-11-22: CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange, RenderShadowDescription.

These 5 are reflected (entt/JSON) types: no constructor, no visitor, no extractor, no per-member `mov [struct+off], <scalar>` store in static disassembly (DOM parsed generically via sub_eea6040/sub_1db850; DOM->struct consumer does hash-key lookup via sub_1d4fd0/sub_1188170, not per-field struct stores). Members are registered via callbacks stored in a type descriptor; member name|offset|type triples are built at runtime.

## 1) Verified type-level metadata: CloudLightingParameters

sub_1188250 (type-descriptor builder, called from sub_1188400 init) — fully disassembled and verified against the exe:

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| desc+0x00 | 8 | `0x11882a9  mov [rax],rdx` | type-descriptor+0x0 := address of name-ptr global 0x128E48E0 [V] |
| desc+0x08 | 4 | `0x11882ac  mov [rax+8],ecx` | +0x08 := type hash 0x8DE632ED [V] |
| desc+0x10 | 8 | `0x11882af  mov qword ptr [rax+0x10],0` | +0x10 := 0 [V] |
| desc+0x18 | 4 | `0x11882b7  mov dword ptr [rax+0x18],0x80` | +0x18 := flags 0x80 [V] |
| desc+0x20 | 8 | `0x11882be  mov qword ptr [rax+0x20],0x14` | +0x20 := member count = 0x14 (20) [V] |
| desc+0x28 | 8 | `0x11882cd  mov [rax+0x28],rcx` (lea rcx,[0x1188170] at 0x11882c6) | +0x28 := lookup callback sub_1188170 [V] |
| desc+0x30 | 8 | `0x11882d8  mov [rax+0x30],rcx` (lea rcx,[0x11884A0] at 0x11882d1) | +0x30 := callback sub_11884a0 [V] |
| desc+0x40 | 8 | `0x11882eb  mov [rax+0x40],rcx` (lea rcx,[0x11886F0] at 0x11882e4) | +0x40 := member-builder callback sub_11886F0 [V] |
| global 0x128E48E4 | 4 | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash 0x8DE632ED [V] |
| global 0x128E48E8 | 8 | `0x1188442  mov [0x128E48E8],rax` (lea rax,[0xF6416AB] at 0x118843b) | RTTI name ptr -> "mce::framebuilder::CloudLightingParameters" substring at 0xF6416AB (inside pretty_function string at 0xF641675, bytes verified) [V] |
| global 0x128E48F0 | 8 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof(CloudLightingParameters) = 0x2A (42 bytes) [V] |

Verified strings (rdis str / raw exe bytes, no code refs — they are data-only entt pretty_function strings):
- "mce::framebuilder::CloudLightingParameters" at 0xF6416AB (0xF641675 string base) [V]
- "mce::framebuilder::CloudParameters" at 0xF6419FD [V]
- "mce::framebuilder::ShadowParameters" at 0xF641005 [V]
- "mce::framebuilder::ShadowRange" at 0xF67B699 [V]
- "void __cdecl mce::framebuilder::FrameBuilder::insert(const TDescription &) [TDescription = mce::framebuilder::RenderShadowDescri..." at 0xF65790F [V] — RenderShadowDescription insert RTTI name; "(no code refs)", referenced only as data.

## 2) Why no per-member [V] rows exist for these types (verified negative)

Member-builder callback sub_11886F0 — fully disassembled (0x11886F0..0x1188772). Key lines:

- `0x11886f0  mov rax,rcx`
- `0x1188710  mov dword ptr [rax+0x20],0x8DE632ED` | member entry+0x20 := parent type hash (immediate, identical for every member)
- `0x1188726  mov [rax],r8` | member entry+0x0 := name pointer passed in REGISTER r8 (not an immediate)
- `0x118875a  mov [rax+0x28],rdx` | member entry+0x28 := offset passed in REGISTER rdx (not an immediate)

`rdis xr 0x11886F0` -> exactly 1 xref: `0x11882e4  lea rcx,[0x11886F0]` (xr context: sub_1188250+0x94; stored as descriptor+0x40 callback). sub_11886F0 is never called directly with member immediates; it is invoked indirectly by the generic registration driver at runtime with (name ptr, offset, type) in registers. Therefore:

- No per-member `mov [..], imm` name/offset/type stores exist anywhere in .text for CloudLightingParameters (and by the same callback architecture, for the other reflected types).
- Member name|offset|type triples are runtime-built; they are NOT instruction-locatable statically.

Data-table method (orchestrator 2026-11-22 after r14) — executed, negative:
- `rdis ptr 0xF54B67F` ("cloud_lighting_parameters" container key) -> 0 pointers in data sections [V]
- `rdis ptr 0xF6416AB` and `rdis ptr 0xF6419FD` (CLP / CloudParameters RTTI name strings) -> 0 pointers [V]
- `rdis ptr 0xF5F9B66` ("cloud_lighting_enabled", a JSON member key seen in sub_1152460+0x373b via `movups xmm0,[0xF5F9B66]`) -> 0 pointers [V]
- One data table was located at 0xF2922E0 (0x10-stride rows {name-ptr32, type_tag=1, offset, 0}; contains SHADOW_*/CLOUD_INTERIOR_FOG_*/CLOUDS*_*/SMOOTH_LIGHTING names). `rdis xr 0xF2922E0` -> 0 code refs; `rdis ptr 0xF2922E0` -> 0 data refs; the table is unreferenced and its offsets repeat across the CLOUDS0..CLOUDS4 layers, so it is not one description struct's member table and is not tied to any of the 5 target types [V data]. Unusable for member rows.

## 3) Per-type status this run

| Type | sizeof | members located | what is verified [V] | missing |
|---|---|---|---|---|
| CloudLightingParameters | 0x2A (42) | 20 members, count only | type hash 0x8DE632ED, RTTI name, descriptor layout (above), member-builder sub_11886F0 signature | all 20 member offsets/names/types [?] |
| CloudParameters | unknown | none | RTTI string at 0xF6419FD (no code refs) | no container key, no registration function, no sizeof, no members [?] |
| ShadowParameters | unknown | none | RTTI string at 0xF641005; container key "shadow_config" at 0xF5B8368 (xref sub_1152460+0x270b) [V] | no sizeof, no member rows [?] |
| ShadowRange | unknown | none | RTTI string at 0xF67B699; "shadow_range" string at 0xF5E056A (sub_53fcac0+0x1c60) [I per prior-run note] | no sizeof, no member rows [?] |
| RenderShadowDescription | unknown [I: 0x20 per prior-run note, unverified] | none | insert RTTI name string at 0xF65790F | insert vtable receiving the 0x14-byte entry not located; shadow-pass execute-body [desc+off] reads not located [?] |

## 4) Descriptions.h-compatible struct text

```cpp
namespace mce::framebuilder {

// CloudLightingParameters: sizeof 0x2A [V], 20 reflected members [V count].
// Member offsets/names/types are NOT statically locatable (runtime-reflected via
// descriptor callbacks sub_1188170/sub_11884a0/sub_11886F0; see section 2).
// Entire object [?] until per-member offsets are recovered.
struct CloudLightingParameters {
    char pad_0x00[0x2A];   // [?] no member field has a confirmed offset
};
static_assert(sizeof(CloudLightingParameters) == 0x2A, "CloudLightingParameters size");

// CloudParameters, ShadowParameters, ShadowRange: no sizeof or member evidence;
// RenderShadowDescription: insert RTTI name string located [V], insert vtable not
// located, no [desc+off] stores/reads located — no struct text this run.

}
```

## 5) Count of types done out of 62

This run: 0 new fully-typed types (no per-field [V] rows instruction-locatable for any of the 5 reflected blocker types).
Cumulative: **28/62** (unchanged from prior runs).

## CLOSES?

NO — M2c requires every description type (62) as a struct with confirmed fields and per-field [V] rows. Single blocking fact: per-field name|offset|type rows for CloudLightingParameters (20 members), CloudParameters, ShadowParameters and ShadowRange are NOT instruction-locatable statically — their member tables are built at runtime by callbacks (sub_1188170 lookup, sub_11884a0, sub_11886F0 member builder taking name ptr/offset/type in registers), no per-member `mov [..], imm` exists in .text, member-name strings have zero data-section references (`rdis ptr` = 0), and the only located data table (0xF2922E0) is unreferenced and not a description struct's member table. RenderShadowDescription additionally lacks a located insert vtable and located shadow-pass [desc+off] reads. Type-level metadata for CloudLightingParameters (sizeof 0x2A, 20 members, hash 0x8DE632ED, descriptor layout, RTTI name) is [V]-proven above; per-field reversing remains the single unknown.

## TOOL REQUESTS

None — rdis dis/str/ptr/xr plus a one-off PE byte reader sufficed; no helper script worth keeping was written.
