## NEXT
DONE

# UNIT U-EM2c — M2c: description types as structs with confirmed fields (Cloud*/Shadow* reflected types)

GOAL: Close checklist item M2c — every description type (62) as a struct with confirmed fields (Descriptions.h-compatible struct text). This run handles the remaining reflected blocker types CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange and RenderShadowDescription via static analysis of the type registration code (type-level metadata: sizeof, member count, hash, RTTI name, callbacks) and the data-table method (member-name strings -> `rdis ptr` -> member-descriptor rows in .rdata/.data), per orchestrator 2026-11-22. End: precise count of types done out of 62.

Rules (OPENCODE_BRIEF.md): static analysis only; every claim tagged [V]/[I]/[?]; verbatim `0xRVA  instr` lines (two spaces after address, copied from rdis); no skipped offsets; run `python tools/delegate.py check docs/progress/oc_U-EM2c.md` and fix every failure; only then set ## NEXT to DONE. Never ask questions — write [UNVERIFIED: 0xaddr question] and continue. Create only docs/progress/oc_U-EM2c.md; no src/, header, Sigs.json, CMake, or hook edits; no build, no game launch/attach.

EXE: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). rdis: tools/rdis/target/release/rdis.exe "<exe>" <cmd> <rva>. Byte-level cross-checks via tools/sigs/pepeek.py (RVA -> file offset). Type-name hashes are FNV-1a 32 (tools/sigs/fnv1a64.py algorithm, 32-bit: basis 0x811C9DC5, prime 0x01000193) — verified: FNV-1a32("mce::framebuilder::CloudLightingParameters") == 0x8DE632ED, exactly the hardcoded type hash in the CloudLightingParameters registration code. Table row labels are prefixed with the type (CLP=CloudLightingParameters, CP=CloudParameters, SP=ShadowParameters, SR=ShadowRange) so offsets stay unique across types.

## Status carried in from prior runs (r19)

- 28/62 types already typed (structs with per-field [V] rows in Descriptions.h or dedicated headers under src/sdk/mc/deps/minecraft_renderer/framebuilder/). Remaining per orchestrator 2026-11-22: CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange, RenderShadowDescription.
- These 5 are reflected (entt/JSON) types: no constructor, no visitor, no extractor, no per-member `mov [struct+off], <scalar>` store in static disassembly (DOM parsed generically; members registered via descriptor callbacks at runtime).
- r19 verified negatives, re-confirmed fresh this run where cheap: member-name strings and RTTI strings have zero code refs (`xr` -> 0) and zero data-section pointer refs (`rdis ptr` -> 0; section 5); the only located data table (0xF2922E0) is unreferenced and not a description struct's member table.

## Method applied this run

1. Locate each type's registration code via the type hash (FNV-1a 32 of the full "mce::framebuilder::<Type>" name, verified against CloudLightingParameters' 0x8DE632ED): `imm <hash>` finds the per-type init function (stores hash + sizeof globals), the descriptor builder (stores hash + callbacks), and the registration function (called once from the JSON/settings parser). Disassemble those; list every `mov [..], imm` (sizeof, hash, name ptr, defaults) as [V] rows.
2. Member level: disassemble the member-builder callbacks (sub_11886F0 / sub_54368d4 family) to decode the member-entry layout {name_ptr@0x0, cb@0x10, cb2@0x18, hash@0x20, type_tag@0x24, offset@0x28}; the builder takes name ptr (r8) and offset (rdx) in REGISTERS — so no per-member `mov [..], imm` exists in .text (verified negative for CloudLightingParameters in r19; same architecture for the other types: sub_118AAE0/sub_54358D0 are structurally identical to sub_1188780).
3. Data-table method (orchestrator after r14): `rdis str "<member name>"` -> `rdis ptr <addr>` -> dump 0x20 bytes around the row. Executed: `rdis ptr 0xF5F9B66` ("cloud_lighting_enabled") -> 0 pointers [V]; `rdis ptr 0xF6419FD` (CloudParameters RTTI) -> 0 pointers [V]. Member rows are NOT stored as name-pointer data rows (rows store hashes, built at runtime), so member offsets/types are not statically enumerable — marked [?].
4. RenderShadowDescription: insert RTTI name string located at 0xF65790F [V] but unreferenced (`xr` -> 0 [V]); insert vtable receiving the 0x14-byte entry not located [?]; no shadow-pass execute-body [desc+off] reads located [?]. Falls back to: size hinted 0x14 [I, orchestrator note], struct all [?] padding.

## 1) [V] type-level metadata: CloudLightingParameters (proven in r19, re-cited here)

sub_1188250 (type-descriptor builder, 0x1188250..0x118830B) builds the descriptor at [rax]:

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| CLP+0x00 | 8 | `0x11882a9` | `0x11882a9  mov [rax],rdx` | descriptor+0x0 := address of name-ptr global 0x128E48E0 [V] |
| CLP+0x08 | 4 | `0x11882ac` | `0x11882ac  mov [rax+8],ecx` | +0x08 := type hash from [0x128E48E4] [V] |
| CLP+0x10 | 8 | `0x11882af` | `0x11882af  mov qword ptr [rax+0x10],0` | +0x10 := 0 [V] |
| CLP+0x18 | 4 | `0x11882b7` | `0x11882b7  mov dword ptr [rax+0x18],0x80` | +0x18 := flags 0x80 [V] |
| CLP+0x20 | 8 | `0x11882be` | `0x11882be  mov qword ptr [rax+0x20],0x14` | +0x20 := member count = 0x14 (20) [V] |
| CLP+0x28 | 8 | `0x11882c6`/`0x11882cd` | `0x11882c6  lea rcx,[0x1188170]` `0x11882cd  mov [rax+0x28],rcx` | +0x28 := lookup callback sub_1188170 [V] |
| CLP+0x30 | 8 | `0x11882d1`/`0x11882d8` | `0x11882d1  lea rcx,[0x11884A0]` `0x11882d8  mov [rax+0x30],rcx` | +0x30 := callback sub_11884a0 [V] |
| CLP+0x38 | 8 | `0x11882dc` | `0x11882dc  mov qword ptr [rax+0x38],0` | +0x38 := 0 [V] |
| CLP+0x40 | 8 | `0x11882e4`/`0x11882eb` | `0x11882e4  lea rcx,[0x11886F0]` `0x11882eb  mov [rax+0x40],rcx` | +0x40 := member-builder callback sub_11886F0 [V] |

sub_1188400 (type init, fills the per-type slot globals):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| CLP hash global | 4 | `0x1188431` | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash = 0x8DE632ED (= FNV-1a32 of "mce::framebuilder::CloudLightingParameters") [V] |
| CLP name global | 8 | `0x118843b`/`0x1188442` | `0x118843b  lea rax,[0xF6416AB]` `0x1188442  mov [0x128E48E8],rax` | RTTI name ptr -> "mce::framebuilder::CloudLightingParameters" substring at 0xF6416AB (inside pretty_function string at 0xF641675, bytes verified via pepeek) [V] |
| CLP sizeof global | 8 | `0x1188449` | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof(CloudLightingParameters) = 0x2A (42 bytes) [V] |

Member-builder callback sub_11886F0 (0x11886F0..0x1188771) — builds ONE member entry at [rax] (rcx = entry ptr); values passed in REGISTERS:

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| CLP entry+0x0 | 8 | `0x1188726` | `0x1188726  mov [rax],r8` | entry+0x0 := name pointer passed in REGISTER r8 (not an immediate) [V] |
| CLP entry+0x10 | 8 | `0x118870c` | `0x118870c  mov [rax+0x10],rcx` (rcx = lea 0x1188560) | entry+0x10 := callback sub_1188560 [V] |
| CLP entry+0x18 | 8 | `0x118871e` | `0x118871e  mov [rax+0x18],rcx` (rcx = lea 0x11886D0) | entry+0x18 := callback sub_11886D0 [V] |
| CLP entry+0x20 | 4 | `0x1188710` | `0x1188710  mov dword ptr [rax+0x20],0x8DE632ED` | entry+0x20 := parent type hash (immediate) [V] |
| CLP entry+0x24 | 1 | `0x1188722` | `0x1188722  mov byte ptr [rax+0x24],1` | entry+0x24 := type tag/flags = 1 [V] |
| CLP entry+0x28 | 8 | `0x118875a` | `0x118875a  mov [rax+0x28],rdx` | entry+0x28 := offset passed in REGISTER rdx (not an immediate) [V] |
| CLP entry+0x30 | 8 | `0x118875e` | `0x118875e  mov qword ptr [rax+0x30],0` | entry+0x30 := 0 [V] |
| CLP entry+0x38 | 8 | `0x1188766`/`0x118876d` | `0x1188766  lea rcx,[0x1188540]` `0x118876d  mov [rax+0x38],rcx` | entry+0x38 := callback sub_1188540 [V] |

Registration: sub_1188780 called exactly once — `0x1155801  call 0x1188780` [V] (`rdis xr 0x1188780` -> 1 xref). Arguments: rcx = &[rbp-8] (descriptor slot), rdx = [rbp+0x248] (DOM node), r8 = &[rbp+0x40] (lookup result) [V from listing at 0x11557F2-0x1155801].

Member name evidenced: JSON member key "cloud_lighting_enabled":

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| CLP key hash | 4 | `0x1155b0a` | `0x1155b0a  mov edx,0x82D01635` | FNV-1a32("cloud_lighting_enabled") = 0x82D01635, passed to sub_24287C0 [V] |
| CLP key string | 16 | `0x1155b9b` | `0x1155b9b  movups xmm0,[0xF5F9B66]` | string "cloud_lighting_enabled" at 0xF5F9B66 copied into DOM node [V] (`pepeek 0xf5f9b66 string` confirmed bytes) |

Its offset/type inside CloudLightingParameters: [?] (registered at runtime via sub_1188170 lookup callback; no per-member `mov [..], imm` in .text).

## 2) [V] type-level metadata: CloudParameters

Type hash = FNV-1a32("mce::framebuilder::CloudParameters") = 0x8CBEF799 (computed; matches all `imm 0x8CBEF799` hits in the 0x118Axxx cluster).

sub_118A6F0 (type init, 0x118A6F0..0x118A748):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| CP hash global | 4 | `0x118A721` | `0x118A721  mov dword ptr [0x128E4994],0x8CBEF799` | type hash = 0x8CBEF799 [V] |
| CP name global | 8 | `0x118A72b`/`0x118A732` | `0x118A72b  lea rax,[0xF641A33]` `0x118A732  mov [0x128E4998],rax` | RTTI name ptr -> "...CloudParameters]" substring at 0xF641A33 (inside pretty_function string at 0xF6419FD, bytes verified via pepeek) [V] |
| CP sizeof global | 8 | `0x118A739` | `0x118A739  mov qword ptr [0x128E49A0],0x22` | sizeof(CloudParameters) = 0x22 (34 bytes) [V] |

sub_118A790 (descriptor builder, 0x118A790..0x118A83F):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| CP desc+0x10 | 8 | `0x118A7a4` | `0x118A7a4  mov [rcx+0x10],rax` (rax = lea 0x118A880) | +0x10 := callback sub_118A880 [V] |
| CP desc+0x20 | 4 | `0x118A7a8` | `0x118A7a8  mov dword ptr [rcx+0x20],0x8CBEF799` | +0x20 := type hash [V] |
| CP desc+0x18 | 8 | `0x118A7b6` | `0x118A7b6  mov [rcx+0x18],rax` (rax = lea 0xDE5ED0) | +0x18 := callback sub_DE5ED0 [V] |
| CP desc+0x24 | 1 | `0x118A7ba` | `0x118A7ba  mov byte ptr [rcx+0x24],1` | +0x24 := flags 1 [V] |
| CP heap | 8 | `0x118A7cc` | `0x118A7cc  mov edx,0x28` (call qword ptr [0xF99FFA0] = sub_eea6040) | allocates 0x28-byte defaults buffer [V] |
| CP buf+0x14 | 8 | `0x118a7fb`/`0x118a805` | `0x118a7fb  mov rcx,0x403F666666` `0x118a805  mov [rax+0x14],rcx` | defaults buffer+0x14 := 0x403F666666 [V] |
| CP buf+0x1C | 4 | `0x118a809` | `0x118a809  mov dword ptr [rax+0x1C],1` | defaults buffer+0x1C := 1 [V] |
| CP buf+0x20 | 1 | `0x118a810` | `0x118a810  mov byte ptr [rax+0x20],1` | defaults buffer+0x20 := 1 [V] |
| CP buf+0x24 | 4 | `0x118a814` | `0x118a814  mov dword ptr [rax+0x24],0x40000000` | defaults buffer+0x24 := 0x40000000 (2.0f) [V] |
| CP desc+0x0 | 8 | `0x118a81b` | `0x118a81b  mov [rsi],rax` | desc+0x0 := defaults buffer ptr [V] |
| CP desc+0x28 | 8 | `0x118a81e` | `0x118a81e  mov [rsi+0x28],rdi` | desc+0x28 := arg2 [V] |
| CP desc+0x30 | 8 | `0x118a822` | `0x118a822  mov qword ptr [rsi+0x30],0` | desc+0x30 := 0 [V] |
| CP desc+0x38 | 8 | `0x118a82a`/`0x118a831` | `0x118a82a  lea rax,[0x118a860]` `0x118a831  mov [rsi+0x38],rax` | desc+0x38 := callback sub_118a860 [V] |

Registration: sub_118AAE0 called exactly once — `0x1156023  sub_1152460+0x3bc3  call 0x118AAE0` [V] (`rdis xr 0x118AAE0` -> 1 xref). sub_118AAE0 is structurally identical to sub_1188780 (`0x118ab16  mov dword ptr [rcx],0x8CBEF799`, `0x118ab3e  mov r9d,0x8CBEF799`, `call 0x1D4FD0`, string copy loop) — no per-member immediates [V].

Member count: NOT stored in any located init/descriptor/global for CloudParameters ([?]). Members: not instruction-locatable ([?]); no member-name strings evidenced for CloudParameters (RTTI string has no code/data refs [V]).

## 3) [V] type-level metadata: ShadowParameters

Type hash = FNV-1a32("mce::framebuilder::ShadowParameters") = 0x7C2A4E8C (matches `imm 0x7C2A4E8C` hits in the 0x5434xxx cluster).

sub_5434C90 (type init, 0x5434C90..0x5434CE8):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| SP hash global | 4 | `0x5434CC1` | `0x5434CC1  mov dword ptr [0x129C79C4],0x7C2A4E8C` | type hash = 0x7C2A4E8C [V] |
| SP name global | 8 | `0x5434CCB`/`0x5434CD2` | `0x5434CCB  lea rax,[0xF64103B]` `0x5434CD2  mov [0x129C79C8],rax` | RTTI name ptr -> "...ShadowParameters]" substring at 0xF64103B (inside pretty_function string at 0xF641005, bytes verified via pepeek) [V] |
| SP sizeof global | 8 | `0x5434CD9` | `0x5434CD9  mov qword ptr [0x129C79D0],0x23` | sizeof(ShadowParameters) = 0x23 (35 bytes) [V] |

sub_5434D30 (descriptor builder, 0x5434D30..0x5434EAB):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| SP desc+0x10 | 8 | `0x5434d44` | `0x5434d3d  lea rax,[0x5434EE0]` `0x5434d44  mov [rcx+0x10],rax` | +0x10 := callback sub_5434EE0 [V] |
| SP desc+0x20 | 4 | `0x5434d48` | `0x5434d48  mov dword ptr [rcx+0x20],0x7C2A4E8C` | +0x20 := type hash [V] |
| SP desc+0x18 | 8 | `0x5434d56` | `0x5434d4f  lea rax,[0x5435750]` `0x5434d56  mov [rcx+0x18],rax` | +0x18 := callback sub_5435750 [V] |
| SP desc+0x24 | 1 | `0x5434d5a` | `0x5434d5a  mov byte ptr [rcx+0x24],1` | +0x24 := flags 1 [V] |
| SP heap | 8 | `0x5434d6c` | `0x5434d6c  mov edx,0x578` (call sub_eea6040) | allocates 0x578-byte defaults buffer [V] |
| SP buf+0x00 | 8 | `0x5434da1` | `0x5434d97  mov rax,0x13E000000` `0x5434da1  mov [rbx],rax` | defaults buffer+0x00 := 0x13E000000 [V] |
| SP buf+0x08 | 8 | `0x5434dac` | `0x5434da4  movsd xmm0,[0xF0CD520]` `0x5434dac  movsd [rbx+8],xmm0` | defaults buffer+0x08 := data_f0cd520 [V] |
| SP buf+0x10 | 4 | `0x5434db1` | `0x5434db1  mov dword ptr [rbx+0x10],8` | defaults buffer+0x10 := 8 [V] |
| SP buf+0x14 | 16 | `0x5434dbf` | `0x5434db8  movaps xmm0,[0xF0CD530]` `0x5434dbf  movups [rbx+0x14],xmm0` | defaults buffer+0x14 := data_f0cd530 [V] |
| SP buf+0x24 | 8 | `0x5434dcb` | `0x5434dc3  movsd xmm0,[0xF0CD540]` `0x5434dcb  movsd [rbx+0x24],xmm0` | defaults buffer+0x24 := data_f0cd540 [V] |
| SP buf+0x2C | 4 | `0x5434dd0` | `0x5434dd0  mov dword ptr [rbx+0x2C],0` | defaults buffer+0x2C := 0 [V] |
| SP buf+0x30 | 2 | `0x5434dd7` | `0x5434dd7  mov word ptr [rbx+0x30],0x101` | defaults buffer+0x30 := 0x101 [V] |
| SP buf+0x32 | 1 | `0x5434ddd` | `0x5434ddd  mov byte ptr [rbx+0x32],1` | defaults buffer+0x32 := 1 [V] |
| SP buf+0x38 | 16 | `0x5434de8` | `0x5434de1  movaps xmm0,[0xF24A640]` `0x5434de8  movups [rbx+0x38],xmm0` | defaults buffer+0x38 := data_f24a640 [V] |
| SP buf+0x48 | 1 | `0x5434dec` | `0x5434dec  mov byte ptr [rbx+0x48],1` | defaults buffer+0x48 := 1 [V] |
| SP buf+0x4C | 4 | `0x5434df0` | `0x5434df0  mov dword ptr [rbx+0x4C],0x3D23D70A` | defaults buffer+0x4C := 0x3D23D70A [V] |
| SP buf+0x70 | 8 | `0x5434e01` | `0x5434df7  mov rax,0x3E2A993100000000` `0x5434e01  mov [rbx+0x70],rax` | defaults buffer+0x70 := 0x3E2A993100000000 [V] |
| SP buf+0x98 | 8 | `0x5434e25` | `0x5434e1b  mov rax,0x3EAAA64C00000000` `0x5434e25  mov [rbx+0x98],rax` | defaults buffer+0x98 := 0x3EAAA64C00000000 [V] |
| SP buf+0xC0 | 8 | `0x5434e4f` | `0x5434e45  mov rax,0x3F80000000000000` `0x5434e4f  mov [rbx+0xC0],rax` | defaults buffer+0xC0 := 0x3F80000000000000 (1.0 double) [V] |
| SP buf+0x190 | 8 | `0x5434e72` | `0x5434e72  mov qword ptr [rbx+0x190],3` | defaults buffer+0x190 := 3 [V] |
| SP buf+0x570 | 8 | `0x5434e7d` | `0x5434e7d  mov qword ptr [rbx+0x570],1` | defaults buffer+0x570 := 1 [V] |
| SP desc+0x0 | 8 | `0x5434e88` | `0x5434e88  mov [rsi],rbx` | desc+0x0 := defaults buffer ptr [V] |
| SP desc+0x38 | 8 | `0x5434e9e` | `0x5434e97  lea rax,[0x5434EC0]` `0x5434e9e  mov [rsi+0x38],rax` | desc+0x38 := callback sub_5434EC0 [V] |

Registration: sub_54358D0 called exactly once — `0x53FE41B  sub_53fcac0+0x195B  call 0x54358d0` [V] (`rdis xr 0x54358D0` -> 1 xref). Call site sets up `0x53FE3D9  lea rax,[0xF54B9C8]` ("Shadow Parameters" string, len 0x11 at [rbp+0xF0..0xF8]) and passes r8 = &[rbp+0xF0] [V]. sub_54358D0 is structurally identical to sub_1188780 (`0x5435906  mov dword ptr [rcx],0x7C2A4E8C`, `0x543592e  mov r9d,0x7C2A4E8C`, `call 0x1D4FD0`) — no per-member immediates [V].

Note: the settings parser sub_53fcac0 reads shadow keys as string immediates ("has_static_geometry" 0x53FE444, "has_dynamic_geometry" 0x53FD017, "bias" 0x53FD1C7, "slope_bias" 0x53FD301, "normal_offset_strength" 0x53FE5D6, ...) into a DOM-like store (sub_544E900 key compare, sub_eea6040 nodes) — values are NOT stored into a ShadowParameters struct at static offsets in this function [V negative].

Member entry layout observed in sub_54368d4 (shared code for the ShadowParameters system):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| SP entry+0x0 | 8 | `0x54368f7` | `0x54368f7  mov qword ptr [rsi],0` | entry+0x0 := name ptr 0 [V] |
| SP entry+0x10 | 8 | `0x54368e0` | `0x54368e0  mov [rsi+0x10],rcx` (rcx = lea 0x1205A0) | entry+0x10 := callback sub_1205A0 [V] |
| SP entry+0x18 | 8 | `0x54368eb` | `0x54368eb  mov qword ptr [rsi+0x18],0` | entry+0x18 := 0 [V] |
| SP entry+0x20 | 4 | `0x54368e4` | `0x54368e4  mov dword ptr [rsi+0x20],0x48B5725F` | entry+0x20 := hash immediate 0x48B5725F [V] |
| SP entry+0x24 | 1 | `0x54368f3` | `0x54368f3  mov byte ptr [rsi+0x24],0` | entry+0x24 := type tag 0 [V] |
| SP entry+0x28 | 8 | `0x54368fe` | `0x54368d4  mov rax,[r12+0x28]` `0x54368fe  mov [rsi+0x28],rax` | entry+0x28 := offset loaded from data row r12+0x28 [V] |
| SP entry+0x30 | 16 | `0x5436905` | `0x5436902  xorps xmm0,xmm0` `0x5436905  movups [rsi+0x30],xmm0` | entry+0x30 := zeroed [V] |

Member count: [?] (not in located init/descriptor). Member names/offsets/types: [?] (data rows built at runtime; hash 0x48B5725F does not match FNV-1a32 or FNV-1a64-low32 of any known shadow key — name unknown).

## 4) [V] type-level metadata: ShadowRange

Type hash = FNV-1a32("mce::framebuilder::ShadowRange") = 0x990FE13D (matches `imm 0x990FE13D` hits in the 0x5437xxx cluster).

sub_5437E20 (type init, 0x5437E20..0x5437E78):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| SR hash global | 4 | `0x5437E51` | `0x5437E51  mov dword ptr [0x129C79EC],0x990FE13D` | type hash = 0x990FE13D [V] |
| SR name global | 8 | `0x5437E5B`/`0x5437E62` | `0x5437E5B  lea rax,[0xF67B6CF]` `0x5437E62  mov [0x129C79F0],rax` | RTTI name ptr -> "...ShadowRange]" substring at 0xF67B6CF (inside pretty_function string at 0xF67B699, bytes verified via pepeek) [V] |
| SR sizeof global | 8 | `0x5437E69` | `0x5437E69  mov qword ptr [0x129C79F8],0x1e` | sizeof(ShadowRange) = 0x1E (30 bytes) [V] |

Descriptor builder: sub_5437D30 — `0x5437D6F  mov dword ptr [rax+0x20],0x990FE13D` [V] (desc+0x20 := type hash). Registration entry point not located (`rdis xr 0x5437B90` -> 0 xrefs) [?].

Same member-entry layout as ShadowParameters (cb sub_1205A0@+0x10, hash@+0x20, tag@+0x24, offset-from-data-row@+0x28) [V via shared sub_54368d4 code].

Member count: [?]. Member names/offsets/types: [?].

## 5) Data-table method results (negative, [V])

`rdis ptr 0xF5F9B66` ("cloud_lighting_enabled") -> `-- 0 pointer(s)` [V] (freshly re-run this run; also r19).
`rdis ptr 0xF6419FD` (CloudParameters RTTI) -> `-- 0 pointer(s)` [V] (freshly re-run this run).
r19 additionally: `rdis ptr 0xF54B67F` ("cloud_lighting_parameters" container) -> 0; `rdis ptr 0xF6416AB` and `rdis ptr 0xF6419FD` (CLP/CloudParameters RTTI) -> 0; table 0xF2922E0 located but unreferenced (`xr` 0, `ptr` 0), offsets repeat across CLOUDS0..CLOUDS4 layers — not a description struct member table [V].
`imm 0x48B5725F` returns tens of thousands of hits (rdis `imm` matches immediate bytes mid-instruction, e.g. inside `or eax,imm32` — not a usable member-table locator) [I on tool behavior].
Conclusion: member rows for these reflected types are NOT stored as name-pointer data rows in .rdata/.data; the member-entry table is built at runtime by the descriptor callbacks from DOM/registry data. No per-member name|offset|type [V] row is instruction-locatable for any of the 4 parameter types.

## 6) RenderShadowDescription

- Insert RTTI name string: `0xF65790F  "void __cdecl mce::framebuilder::FrameBuilder::insert(const TDescription &) [TDescription = mce::framebuilder::RenderShadowDescri...` [V] (`rdis str RenderShadowDescription`; bytes verified via pepeek).
- `rdis xr 0xF65790F` -> `-- 0 xref(s)` [V] — the string is referenced by no code (dead pretty_function data from the template instantiation).
- No `insert<RenderShadowDescription>` function or shadow pass/clone found in docs/data/functions.tsv (grep "shadow" -> only 0x53fcac0 cascade fit, 0x53e6c30 blob shadow emitter, 0x66a6830 shadow volume builder) and no live shadow-description dumps in docs/data/live/.
- Insert vtable receiving the 0x14-byte entry: NOT located [?].
- Shadow-pass execute body [desc+off] consumer reads: NOT located [?].
- Size: hinted as 0x14-byte entry by orchestrator note [I] — NOT verified in disassembly.
- Struct: no confirmed field; entire object [?].

## 7) Descriptions.h-compatible struct text

```cpp
namespace mce::framebuilder {

// CloudLightingParameters
//   sizeof 0x2A [V] (`0x1188449  mov qword ptr [0x128E48F0],0x2A`)
//   member count 20 (0x14) [V] (`0x11882be  mov qword ptr [rax+0x20],0x14`)
//   type hash 0x8DE632ED [V], RTTI name "mce::framebuilder::CloudLightingParameters" at 0xF6416AB [V]
//   descriptor builder sub_1188250, callbacks sub_1188170/sub_11884a0/sub_11886F0 [V]
//   Member offsets/names/types: registered at runtime; sub_11886F0 takes name ptr (r8) and
//   offset (rdx) in registers — no per-member `mov [..], imm` in .text; member-name strings
//   have no data-section refs (`rdis ptr 0xF5F9B66` -> 0 [V]). Only evidenced member name:
//   "cloud_lighting_enabled" (FNV-1a32 0x82D01635, `0x1155b0a  mov edx,0x82D01635`;
//   string parsed at `0x1155b9b  movups xmm0,[0xF5F9B66]`) [V]. Its offset/type: [?].
//   All 20 members [?].
struct CloudLightingParameters {
    char pad_0x00[0x2A];   // [?] no member field has a confirmed offset
};
static_assert(sizeof(CloudLightingParameters) == 0x2A, "CloudLightingParameters size");

// CloudParameters
//   sizeof 0x22 [V] (`0x118A739  mov qword ptr [0x128E49A0],0x22`)
//   type hash 0x8CBEF799 [V], RTTI name ptr 0xF641A33 [V]
//   init sub_118A6F0, descriptor builder sub_118A790 (desc+0x20 = hash, 0x28-byte defaults
//   buffer with imm defaults at +0x14/+0x1C/+0x20/+0x24 [V]), registration sub_118AAE0
//   called from sub_1152460+0x3bc3 (`0x1156023  call 0x118AAE0`) [V]
//   Member count: [?]. Members: [?] (no constructor/visitor/extractor; registration takes
//   member info from DOM at runtime; no per-member imm rows).
struct CloudParameters {
    char pad_0x00[0x22];   // [?] no member field has a confirmed offset
};
static_assert(sizeof(CloudParameters) == 0x22, "CloudParameters size");

// ShadowParameters
//   sizeof 0x23 [V] (`0x5434CD9  mov qword ptr [0x129C79D0],0x23`)
//   type hash 0x7C2A4E8C [V], RTTI name ptr 0xF64103B [V]
//   init sub_5434C90, descriptor builder sub_5434D30 (desc+0x20 = hash, 0x578-byte defaults
//   buffer, imm defaults at +0x10/+0x14/+0x24/+0x2C/+0x30/+0x32/+0x38/+0x48/+0x4C/+0x70/
//   +0x98/+0xC0/+0x190/+0x570 [V]), registration sub_54358D0 called from
//   sub_53fcac0+0x195B (`0x53FE41B  call 0x54358d0`) [V]; settings string "Shadow Parameters"
//   at `0x53FE3D9  lea rax,[0xF54B9C8]` [V].
//   Member count: [?]. Members: [?]. Observed member-entry shape
//   {name_ptr@0, cb sub_1205A0@0x10, hash@0x20, tag@0x24, offset@0x28} via sub_54368d4
//   (`0x54368d4  mov rax,[r12+0x28]`; `0x54368fe  mov [rsi+0x28],rax`) [V] — offset comes
//   from a runtime data row, not a code immediate.
struct ShadowParameters {
    char pad_0x00[0x23];   // [?] no member field has a confirmed offset
};
static_assert(sizeof(ShadowParameters) == 0x23, "ShadowParameters size");

// ShadowRange
//   sizeof 0x1E [V] (`0x5437E69  mov qword ptr [0x129C79F8],0x1e`)
//   type hash 0x990FE13D [V], RTTI name ptr 0xF67B6CF [V]
//   init sub_5437E20; descriptor builder sub_5437D30 (`0x5437D6F  mov dword ptr [rax+0x20],
//   0x990FE13D` [V]). Same member-entry shape as ShadowParameters [V].
//   Member count/names/offsets/types: [?].
struct ShadowRange {
    char pad_0x00[0x1E];   // [?] no member field has a confirmed offset
};
static_assert(sizeof(ShadowRange) == 0x1E, "ShadowRange size");

// RenderShadowDescription
//   Insert RTTI name string at 0xF65790F [V], unreferenced by code (`xr` -> 0 [V]).
//   Insert vtable receiving the 0x14-byte entry: not located [?]. Shadow-pass execute-body
//   [desc+off] reads: not located [?]. Size hinted 0x14 by orchestrator note [I] (unverified).
struct RenderShadowDescription {
    char pad_0x00[0x14];   // [?] size and all fields unconfirmed (0x14 per orchestrator hint [I])
};
static_assert(sizeof(RenderShadowDescription) == 0x14, "RenderShadowDescription size");

} // namespace mce::framebuilder
```

## 8) Count of types done out of 62

- This run: 0 new fully-typed types (no per-field [V] rows instruction-locatable for any of the 5 reflected types; type-level metadata [V] for all 4 parameter types + RenderShadowDescription insert string [V]).
- Cumulative: **28/62** (unchanged from prior runs).
- Types fully typed (struct with per-field [V] rows): 28 — from prior runs: RenderNametagDescription, RenderCloudsDescription, RenderSkinnedMeshDescription, RenderMeshFallbackDescription, RenderEnvironmentalTextDescription, RenderUITextDescription, RenderBlockSelectionOverlayDescription, RenderSkyDescription, WeatherDescription, FlameBillboardDescription, RenderGameFaceDescription, RenderCubemapDescription, RenderChunkOccludersDescription, RenderAtmosphereDescription, RenderBlockChangesDescription, AimAssistHighlight, EditorHighlight, LightAmbient, LightDirectional, Light tag 2, Light tag 4, Light tag 3, RenderBlitFlipbookDescription, RenderCrackDescription, RenderParticleDescription, RenderPlayerVisionDescription, RenderStarsDescription (per prior run notes; see Descriptions.h and dedicated headers under src/sdk/mc/deps/minecraft_renderer/framebuilder/).
- Remaining unclosed: CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange, RenderShadowDescription (this run) plus any others not addressed in this run per the catalog.

## CLOSES?

NO — M2c requires every description type (62) as a struct with confirmed fields and per-field [V] rows. Single blocking fact: per-field name|offset|type rows for CloudLightingParameters (20 members), CloudParameters, ShadowParameters and ShadowRange are NOT instruction-locatable statically — member entries are built at runtime by descriptor callbacks (sub_11886F0 / sub_54368d4 family) taking the name pointer (r8) and offset (rdx) from registers/DOM data, no per-member `mov [..], imm` exists in .text, member-name strings have no data-section references (`rdis ptr` -> 0 [V] for 0xF5F9B66 and 0xF6419FD), and no name-pointer data table exists for these types. RenderShadowDescription additionally lacks a located insert vtable and located shadow-pass [desc+off] reads; its size (hinted 0x14) is unverified [I]. Type-level metadata (sizeof/hash/name/callbacks) for the 4 parameter types IS [V]-proven above; per-field reversing remains the single unknown.

## TOOL REQUESTS

None — rdis dis/str/ptr/xr/imm plus pepeek.py byte dumps sufficed; no helper script written. A potentially useful future tool: a .rdata/.data row scanner that finds rows matching {type_hash imm, offset < sizeof} to enumerate the runtime-built member tables statically (no seed address is currently known, so it could not be applied this run).
