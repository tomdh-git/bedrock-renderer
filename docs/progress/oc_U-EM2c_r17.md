## NEXT
DONE - delegate check passing; verify_oc match=17 mismatch=0 no-such-instr=0; CLOSES? NO (per-field rows for CloudLightingParameters/CloudParameters/ShadowParameters not instruction-locatable — runtime-reflected member tables, no static per-member imm stores); count stays 28/62; ShadowRange + RenderShadowDescription remain for next run.

# UNIT U-EM2c — M2c: description types as structs with confirmed fields (Cloud*/Shadow* reflected types)

GOAL: Close checklist item M2c — every description type (62) as a struct with confirmed fields (Descriptions.h). This run handles the remaining reflected blocker types CloudLightingParameters, CloudParameters, ShadowParameters (3 types per the orchestrator 2026-11-22 instruction). They are reflected types whose members are registered in a member table next to type-level metadata (sizeof, member count, callbacks). For each type: take the metadata RVA, rdis-dis the registration function that fills the member array (stores sizeof and the member count), and list each member's `mov [..], imm` for name pointer / offset / type as [V] rows. Where no code xref exists, use the data-table method: take a member name string, search for 8-byte POINTER references to that string's address in .rdata/.data (`rdis ptr <addr>`, NOT `xr`), dump 0x20 bytes around the descriptor row, decode name ptr | type tag | offset, list all rows as [V] data rows with verbatim `rdis` dump bytes.

Rules (OPENCODE_BRIEF.md): static analysis only; every claim tagged [V]/[I]/[?]; verbatim `0xRVA  instr` lines (two spaces after address, copied from rdis); no skipped offsets; run `python tools/delegate.py check docs/progress/oc_U-EM2c.md` and fix every failure; only then set ## NEXT to DONE. Never ask questions — write [UNVERIFIED: 0xaddr question] and continue. Create only docs/progress/oc_U-EM2c.md; no src/, header, Sigs.json, CMake, or hook edits; no build, no game launch/attach.

## Context

62 framebuilder description types in the catalog. ~28-30 already typed (Descriptions.h or dedicated headers under src/sdk/mc/deps/minecraft_renderer/framebuilder/). Remaining untyped per orchestrator 2026-11-22: CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange, RenderShadowDescription.

These 5 are reflected (entt/JSON) types: no constructor, no visitor, no extractor, no `mov [struct+off], <scalar>` per-member store exists in static disassembly (the DOM is parsed generically via sub_eea6040/sub_1db850 and the DOM→struct consumer performs hash-key lookup via sub_1d4fd0/sub_1188170, not per-field struct stores). Members are registered via callbacks stored in a type descriptor.

## Type 1: CloudLightingParameters — type-level metadata [V]

Type-level metadata located in sub_1188400 (type-registration init) and sub_1188250 (type-descriptor filler).

| CLP item | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| CLP RTTI hash | 4 | 0x1188431 | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash 0x8DE632ED stored at global 0x128E48E4 [V] |
| CLP RTTI name ptr | 8 | 0x118843b / 0x1188442 | `0x118843b  lea rax,[0xF6416AB]`; `0x1188442  mov [0x128E48E8],rax` | RTTI name "mce::framebuilder::CloudLightingParameters" at 0xF6416AB → global 0x128E48E8 [V] |
| CLP sizeof | 8 | 0x1188449 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof(CloudLightingParameters) = 0x2A (42 bytes) at global 0x128E48F0 [V] |
| CLP desc+0x0 | 8 | 0x11882a9 | `0x11882a9  mov [rax],rdx` | type-descriptor +0x0 := name-ptr global 0x128E48E0 [V] |
| CLP desc+0x8 | 8 | 0x11882ac | `0x11882ac  mov [rax+8],ecx` | type-descriptor +0x8 := hash global 0x128E48E4 [V] |
| CLP desc+0x10 | 8 | 0x11882af | `0x11882af  mov qword ptr [rax+0x10],0` | type-descriptor +0x10 := 0 [V] |
| CLP desc+0x18 | 4 | 0x11882b7 | `0x11882b7  mov dword ptr [rax+0x18],0x80` | type-descriptor +0x18 := flags 0x80 [V] |
| CLP desc+0x20 member-count | 8 | 0x11882be | `0x11882be  mov qword ptr [rax+0x20],0x14` | member count = 0x14 (20 members) [V] |
| CLP desc+0x28 lookup-cb | 8 | 0x11882c6 / 0x11882cd | `0x11882c6  lea rcx,[0x1188170]`; `0x11882cd  mov [rax+0x28],rcx` | lookup callback sub_1188170 at +0x28 [V] |
| CLP desc+0x30 names-cb | 8 | 0x11882d1 / 0x11882d8 | `0x11882d1  lea rcx,[0x11884A0]`; `0x11882d8  mov [rax+0x30],rcx` | member-names callback sub_11884a0 at +0x30 [V] |
| CLP desc+0x40 offset/type-cb | 8 | 0x11882e4 / 0x11882eb | `0x11882e4  lea rcx,[0x11886F0]`; `0x11882eb  mov [rax+0x40],rcx` | member offset/type builder sub_11886f0 at +0x40 [V] |
| CLP container key | 8 | 0x1156787 | `0x1156787  lea rax,[0xF54B67F]` | JSON container key "cloud_lighting_parameters" (len 0x19) [V] |

### Member-name / offset / type data table — [UNVERIFIED]

`rdis ptr 0xF54B67F` → 0 pointer(s) in data sections: no static data row references the container-key string, so the container-key data-table method yields nothing [V data]. Callbacks sub_11884a0 (names) and sub_11886f0 (offset/type) BUILD member descriptors at RUNTIME from register args (r8=name ptr, rdx=offset, r9=type) via heap-allocation sub_eea6040; they contain NO `lea rax,[member-name-string]` and NO per-member `mov [..], imm` name/offset/type stores (verified by full disassembly of sub_11884a0 0x11884a0..0x1188700 and sub_11886f0 0x11886f0..0x1188772). sub_11884a0/sub_11886f0 each have exactly 1 xref (sub_1188250 storing them as callback pointers), i.e. they are invoked indirectly at runtime, not with static per-member immediates.

Therefore no per-field `mov [..], imm` name/offset/type rows are instruction-locatable for CloudLightingParameters. The 20 member offsets/types are runtime-built; member name strings not located statically.

[UNVERIFIED: 0x11884a0/0x11886f0 what are the 20 CloudLightingParameters member name/offset/type triples, and where (runtime) are the name strings supplied?]

CloudLightingParameters per-field rows: [UNVERIFIED] for all 20 members (offset, width, source all unknown statically).

## Type 2: CloudParameters — [V] container key + RTTI string only

| CP item | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| CP RTTI string | - | - | (dead entt string, no code refs) | "mce::framebuilder::CloudParameters" at 0xF6419FD, xref refs=[] — no code references whatsoever [V data] |
| CP container key | - | - | not located in code | JSON container key for CloudParameters not located [?] |

No registration function (sizeof/member-count/callbacks) located for CloudParameters. No `mov qword ptr [global], <size>` sizeof store, no RTTI-name `lea` reference, no member-count store found. Per-field rows impossible without the type metadata.

[UNVERIFIED: 0xF6419FD where is CloudParameters constructed/registered, what is its sizeof/member-count, and what are its fields?]

CloudParameters per-field rows: [UNVERIFIED] (type metadata not located).

## Type 3: ShadowParameters — [V] container key + descriptor callbacks

| SP item | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| SP container key | 8 | 0x1154b6b | `0x1154b6b  lea rax,[0xF5B8368]` | JSON container key "shadow_config" (len 0xD) [V] |
| SP descriptor callbacks | 8 | 0x1154c23-0x1154c5b | `0x1154c23..0x1154c5b` store sub_12ceb10/sub_12ce750/sub_12ceb40/sub_12cf0c0 | descriptor callbacks stored in generic registrar sub_1154800 [V] (attribution to ShadowParameters [I] prior-run context) |

No sizeof store, no RTTI-name store, no member-count store located for ShadowParameters itself. `rdis ptr 0xF5B8368` → 0 pointer(s) in data sections: no static data row references the "shadow_config" string [V data].

[UNVERIFIED: 0x1154800 where is ShadowParameters sizeof/member-count stored, and what are its fields?]

ShadowParameters per-field rows: [UNVERIFIED] (type metadata not located).

## ShadowRange and RenderShadowDescription — deferred to next run

Not addressed this run (orchestrator: 3 types per run; ShadowRange + RenderShadowDescription next run). ShadowRange: key "shadow_range" str 0xF5E056A at sub_53fcac0+0x1c60 [V string ref], offset/store [UNVERIFIED]. RenderShadowDescription: insert vtable receiving the 0x14-byte entry not located [UNVERIFIED]; header exists (Effect tag 4, sizeof 0x20) but lacks [desc+off] ctor evidence.

## Types done this run

0 new fully-typed types (no per-field [V] rows instruction-locatable for any of the 3 reflected types — they are runtime-reflected, not constructor-filled).

Type-level [V] documentation added for CloudLightingParameters (sizeof 0x2A, RTTI name, hash 0x8DE632ED, member count 20, 4 callbacks, container key), plus partial [V] for CloudParameters (RTTI string) and ShadowParameters (container key, callbacks).

## Count of types done out of 62

28/62 (unchanged from prior runs). The 3 Cloud*/Shadow* types this run contribute type-level [V] metadata but no per-field [V] rows, so they are not counted as fully typed.

## [V] proof rows summary

All quoted instruction lines above are verbatim from `rdis dis` of the exe and were confirmed by `rdis str` / `rdis ptr` / `rdis dis`. Sizes: qword=8, dword=4 per instruction.

## What changed

- Created docs/progress/oc_U-EM2c.md with type-level + per-field analysis for CloudLightingParameters, CloudParameters, ShadowParameters.
- No other file created or edited.

## CLOSES?

NO — M2c requires every description type (62) as a struct with confirmed fields with per-field [V] rows. The single blocking fact: per-field name|offset|type rows for CloudLightingParameters (20 members), CloudParameters, and ShadowParameters are NOT instruction-locatable — their member tables are built at runtime by callbacks sub_11884a0/sub_11886f0 from register args with no static per-member `mov [..], imm`, no member-name strings located statically, and `rdis ptr` on both container keys returns 0 data pointers. Type-level metadata [V] is documented; per-field reversing remains the single unknown.

## TOOL REQUESTS

None — existing rdis dis/str/ptr and delegate.py/verify_oc only.
