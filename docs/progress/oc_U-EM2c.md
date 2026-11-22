## NEXT
step 2

# U-EM2c - Cloud*/Shadow* parameter types (remaining M2c blockers)

## Context (from prior runs r1-r13, not re-verified here except where cited)
- 28/62 description types typed; remaining blockers: CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange, RenderShadowDescription.
- Orchestrator (2026-11-22, after 2nd NO): STOP looking for a per-key JSON->struct `mov [struct+off], <scalar>` store; it does not exist (DOM parsed generically, callback/ctor fills the struct).
- Orchestrator HINT: these are reflected types with member tables next to type-level metadata (sizeof, member count, callbacks). For each member, registration gives (name, offset, type tag). Disassemble the registration function that fills the member array (stores sizeof + member count) and list each member's `mov [..], imm` for name pointer / offset / type as [V] rows. 3 types per run. RenderShadowDescription: find the insert vtable receiving the 0x14-byte entry and list what it copies in.

## Known type-level metadata [V] (from prior runs, to be re-confirmed by disassembly in this run)
- CloudLightingParameters: sizeof 0x2A @ `0x1188449  mov qword ptr [0x128E48F0],0x2A`; RTTI name `0x118843b  lea rax,[0xF6416AB]` ("mce::framebuilder::CloudLightingParameters"); member count 0x14 (20) @ `0x11882be  mov qword ptr [rax+0x20],0x14`; callbacks: lookup sub_1188170, member names sub_11884A0, member offset/type builder sub_11886F0. Container key "cloud_lighting_parameters" (0xF54B67F @ 0x1156787, sub_1156680).
- CloudParameters: RTTI string only "mce::framebuilder::CloudParameters" at 0xF6419FD, no code refs. Container key not located.
- ShadowParameters: container key "shadow_config" (0xF5B8368 @ 0x1154b6b, sub_1154800); descriptor callbacks sub_12ceb10/sub_12ce750/sub_12ceb40/sub_12cf0c0 @ 0x1154c23-0x1154c5b.
- ShadowRange: key "shadow_range" str 0xF5e056a @ sub_53fcac0+0x1c60.
- RenderShadowDescription: Effect tag 4, 0x20 header exists; clone builds 0x14-byte entry handed to an insert vtable (not located).

## Work this run
Pick up to 3 of: CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange via the member-table method; then RenderShadowDescription via the insert-vtable method. Write [V] rows per member (name | offset | type tag/source). End with precise count of types done out of 62.
