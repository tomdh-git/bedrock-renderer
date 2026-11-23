## NEXT
DONE

# U-EM2c - Cloud*/Shadow* parameter types (remaining M2c blockers)
Output file: docs/progress/oc_U-EM2c.md (only file created/edited this unit). Exe: Minecraft.Windows.exe 1.26.62.01. All `0xRVA  instr` lines below were disassembled with rdis and are quoted verbatim.

## Method (orchestrator 2026-11-22, after 2nd NO)
Aborted the search for a per-key JSON->struct `mov [struct+off], <scalar>` store: it does not exist (DOM parsed generically, callback/constructor fills the struct). Applied the member-table method: disassemble each reflected type's registration function (the one storing sizeof + member count) and list each member's `mov [..], imm` for name pointer / location / type tag as [V] rows.

## CloudLightingParameters — type-level metadata located [V]
Registration chain: sub_1188400 fills the type-info globals; sub_1188250 registers the type entry (member count 0x14 = 20, callbacks sub_1188170/sub_11884a0/sub_11886f0).

| offset | size | site | instruction | meaning | tag |
| 0x128e48f0 | 8 | 0x1188449 | `0x1188449  mov qword ptr [0x128e48f0],0x2A` | type-info global := 0x2A = sizeof(CloudLightingParameters) | [V] |
| 0x128e48e4 | 4 | 0x1188431 | `0x1188431  mov dword ptr [0x128e48e4],0x8DE632ED` | type-info nameHash := 0x8DE632ED | [V] |
| 0xf6416ab | 8 | 0x118843b | `0x118843b  lea rax,[0xF6416AB]` | RTTI name address 0xF6416AB loaded into rax | [V] |
| 0x128e48e8 | 8 | 0x1188442 | `0x1188442  mov [0x128e48e8],rax` | type-info namePtr stored (rax = RTTI name address) | [V] |
| 0x128e48e0 | 4 | 0x118842b | `0x118842b  mov [0x128e48e0],eax` | type-info type-info ptr stored | [V] |
| 0x20 | 8 | 0x11882be | `0x11882be  mov qword ptr [rax+0x20],0x14` | type-entry+0x20 := 0x14 = member count 20 | [V] |
| 0x18 | 4 | 0x11882b7 | `0x11882b7  mov dword ptr [rax+0x18],0x80` | type-entry+0x18 := 0x80 flags | [V] |
| 0x28 | 8 | 0x11882c6 | `0x11882c6  lea rcx,[0x1188170]` | type-entry+0x28 := 0x1188170 = lookup callback | [V] |
| 0x30 | 8 | 0x11882d1 | `0x11882d1  lea rcx,[0x11884A0]` | type-entry+0x30 := 0x11884A0 = member-names callback | [V] |
| 0x40 | 8 | 0x11882e4 | `0x11882e4  lea rcx,[0x11886F0]` | type-entry+0x40 := 0x11886F0 = member location/type builder | [V] |

## Member table (per-member name / location / type tag) — NOT instruction-located [blocking fact]
sub_11884a0 allocates the 20-member array and zero-initializes each entry:
| ma_cnt | 4 | 0x11884dc | `0x11884dc  mov edx,0x14` | sub_11884a0 member-array element count = 20 | [V] |
| ma_init | 16 | 0x11884fa | `0x11884fa  movaps [rax],xmm0` | sub_11884a0 zero-init each member entry (movaps 16 bytes) | [V] |
sub_11886f0 builds each member descriptor but passes name/location/type in REGISTERS (r8/r9/rdx) via an indirect callback, not as immediates:
| md+0x0 | 8 | 0x1188726 | `0x1188726  mov [rax],r8` | member descriptor+0x0 := r8 (register arg, not an immediate name/location) | [V] |
| md+0x20 | 4 | 0x1188710 | `0x1188710  mov dword ptr [rax+0x20],0x8DE632ED` | member descriptor+0x20 := type-hash imm (shared type tag, not per-member) | [V] |
| md+0x28 | 8 | 0x118875a | `0x118875a  mov [rax+0x28],rdx` | member descriptor+0x28 := rdx (register arg) | [V] |
No per-member `mov [..], imm` name/location/type-tag store table exists in static disassembly for CloudLightingParameters. The same callback-based design (generic config registrar for shadow_config) applies to the other parameter types, so per-member rows cannot be [V]-proven from instruction disassembly.

## Other remaining blockers (context only, not [V] in this run)
- CloudParameters: RTTI string only "mce::framebuilder::CloudParameters" at 0xF6419FD, no code refs; container key not located. [I] prior-run context, not re-verified.
- ShadowParameters: "shadow_config" key `0x1154b6b  lea rax,[0xF5B8368]`; descriptor callbacks sub_12ceb10/sub_12ce750/sub_12ceb40/sub_12cf0c0 stored @ 0x1154c23-0x1154c5b in generic registrar sub_1154800; no sizeof/member-count imm store located for ShadowParameters itself. Callback stores [V] seen in disassembly; attribution to ShadowParameters [I] prior context.
- ShadowRange: key "shadow_range" str 0xF5e056a @ sub_53fcac0+0x1c60. No member table located.
- RenderShadowDescription: Effect tag 4, 0x20 header; clone builds 0x14-byte entry handed to an insert vtable (not located). Not addressed this run.

## Count
28/62 description types typed prior to this run. This run [V]-documents CloudLightingParameters type-level metadata (sizeof, member count, name, hash, callbacks) but does NOT locate per-member name/location/type-tag rows. Types done out of 62: 28 (unchanged); per-field member rows for the 5 remaining blockers incomplete.

## CLOSES?
NO — item wording not met on disk. Single blocking fact: the per-member name/location/type-tag imm store table (and any JSON-key -> struct-offset store) does not exist as instruction-located disassembly for these reflected parameter types; the DOM is parsed generically and the struct is filled by callbacks (sub_11886f0 register-arg member builder / generic config registrar), so per-member [V] rows cannot be produced from static disassembly.

## TOOL REQUESTS
None.
