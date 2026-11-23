## NEXT
DONE

# UNIT U-EM2c — M2c: description types as structs (Cloud*/Shadow* reflected parameter types)

GOAL: Close checklist item M2c — every description type (62) as a struct with confirmed fields (Descriptions.h-compatible struct text). This run handles the remaining reflected blocker types CloudLightingParameters, CloudParameters, ShadowParameters (3 per run), applying the orchestrator's data-table method (member-name/container string → `rdis str` → `rdis ptr` → data-table descriptor rows). Ends with a precise count of types done out of 62.

Scope note: CloudParameters and ShadowParameters have RTTI name strings with zero code references; no constructor/extractor/visitor exists. CloudLightingParameters has a located registration function but it builds member tables at runtime via callbacks (no static per-member `mov [struct+off], <scalar>` stores). Per the hard rules, nothing is invented; every claim below carries a verbatim `0xRVA  instr` proof or is tagged [?]/[UNVERIFIED].

## Method applied (data-table method, orchestrator 2026-11-22 / after r14)
1. `rdis str "<name>"` → string RVA in the exe.
2. `rdis ptr <string RVA>` → 8-byte pointer references to that string in .rdata/.data (member-descriptor rows); NOT `xr` (code refs only).
3. Dump 0x20 bytes around the descriptor row; decode name ptr | type tag | offset; list all rows as [V] data rows.
Applied to: "cloud_lighting_parameters" (0xF54B67F), "shadow_range" (0xF5E056A), "enable_cloud_render_distance" (0xF5E7299).
Result: `rdis ptr` returned **0 pointer(s)** for all three. These strings have code references only (JSON key lookups in sub_1152460/sub_53fcac0); no data-section member-descriptor table references them statically. This confirms the member tables are built at runtime from the JSON DOM (callbacks sub_1188560/sub_11886d0/sub_1188540), not stored as static name|offset|type data rows.

## Type 1: CloudLightingParameters — type-level metadata [V]
Type-level metadata located via registration function sub_11884a0 (0x11884a0), which stores the RTTI name pointer, the hash, sizeof, and member count, then installs runtime callbacks.

| offset | size | site | verbatim `0xRVA  instr` | name/meaning [tag] |
|---|---|---|---|---|
| RTTI name ptr | 8 | 0x118843b / 0x1188442 | `0x118843b  lea rax,[0xF6416AB]`; `0x1188442  mov [0x128E48E8],rax` | RTTI name "mce::framebuilder::CloudLightingParameters" at 0xF6416AB → global 0x128E48E8 [V] |
| type hash | 4 | 0x1188431 | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash 0x8DE632ED at global 0x128E48E4 [V] |
| sizeof | 8 | 0x1188449 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof(CloudLightingParameters) = 0x2A (42 bytes) at global 0x128E48F0 [V] |
| member count | 4 | 0x11884dc | `0x11884dc  mov edx,0x14` | member count = 0x14 (20) passed to allocator sub_eea6040 [V] |
| name callback | 8 | 0x11884ad / 0x11884b4 | `0x11884ad  lea rax,[0x1188560]`; `0x11884b4  mov [rcx+0x10],rax` | descriptor[+0x10] = names callback sub_1188560 [V] |
| desc callback | 8 | 0x11884bf / 0x11884c6 | `0x11884bf  lea rax,[0x11886D0]`; `0x11884c6  mov [rcx+0x18],rax` | descriptor[+0x18] = member-descriptor callback sub_11886d0 [V] |
| count callback | 8 | 0x11884ca | `0x11884ca  mov byte ptr [rcx+0x24],1` | descriptor[+0x24] = flag/state byte = 1 [V] |

Per-member fields (name | offset | type): **[UNVERIFIED] for all 20 members.**
- sub_11884a0 does NOT store any member name pointer, offset, or type tag as an immediate into a static table; it allocates 0x14=20 member descriptors via `0x11884dc  mov edx,0x14` → `0x11884e1  call qword ptr [0xF99FFA0]` (sub_eea6040) and fills them at runtime through callbacks sub_1188560/sub_11886d0/sub_1188540.
- In sub_11886d0, the descriptor fields are written from runtime arguments (`0x1188726  mov [rax],r8` = name-ptr argument; `0x118875a  mov [rax+0x28],rdx` = offset argument), i.e. name/offset/type arrive as arguments, not as static immediates.
- `rdis ptr 0xF54B67F` ("cloud_lighting_parameters") → 0 pointers in data sections: no static data row references this string [V data].
- No `rdis str "<membername>"` yielded a string with a data-section pointer reference; the located strings are JSON container keys referenced only in code.

So no per-field `mov [..], imm` name/offset/type rows are instruction-locatable for CloudLightingParameters. All 20 member offsets/types remain [UNVERIFIED] / [?].

## Type 2: CloudParameters — RTTI string only
- RTTI string "mce::framebuilder::CloudParameters" at 0xF6419FD, `xref refs=[]` — no code references whatsoever [V data].
- No sizeof store, no RTTI-name store, no member-count store, no registration function located for CloudParameters [V].
- Per-field rows: [UNVERIFIED] — type metadata not located; sizeof/member-count/fields unknown.

## Type 3: ShadowParameters — descriptor callbacks in generic registrar
- RTTI string "mce::framebuilder::ShadowParameters" at 0xF641005, `xref refs=[]` — no code references [V data].
- Generic registrar sub_1154800 stores descriptor callbacks at `0x1154c23..0x1154c5b` (sub_12ceb10/sub_12ce750/sub_12ceb40/sub_12cf0c0); attribution to ShadowParameters is [I] (prior-run context), no sizeof/RTTI-name/member-count store located for ShadowParameters itself [V].
- `rdis ptr 0xF5B8368` ("shadow_config") → 0 pointers in data sections [V data].
- Per-field rows: [UNVERIFIED] — sizeof/member-count/offsets/types unknown.

## Types deferred to next run (3-per-run rule): ShadowRange, RenderShadowDescription
- ShadowRange: `rdis str "shadow_range"` → 0xF5E056A (code ref sub_53fcac0+0x1c60 only); `rdis ptr 0xF5E056A` → 0 pointers [V data]. No static member table.
- RenderShadowDescription: no [desc+off] constructor store located; clone builds a 0x14-byte entry handed to an (unlocated) insert vtable; pass-body [desc+off] reads not located.

## Count
Types done out of 62: **28 / 62** (unchanged this run — none of CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange, RenderShadowDescription has per-field [V] rows; all 5 remain blocked at the reflected/runtime level).

## CLOSES?
NO — single blocking fact: the Cloud*/Shadow* parameter types are reflected (JSON DOM → runtime callbacks), not constructed by static per-member stores. `rdis str` → `rdis ptr` yields 0 data-section pointers for their name/container strings, and the located registration (sub_11884a0 for CloudLightingParameters) fills member name/offset/type from runtime callback arguments, not static `mov [..], imm` immediates. Therefore per-field name|offset|type rows cannot be produced statically for CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange (and RenderShadowDescription lacks a located insert vtable / pass-body consumer). All 5 remain untyped; count stays 28/62. Nothing further can be proved on disk without a runtime capture of the registration callbacks (live capture of sub_11884a0/sub_11886f0 returned 0 hits in a 60 s window) or the member-name→offset mapping from the running process.

## TOOL REQUESTS
None.
