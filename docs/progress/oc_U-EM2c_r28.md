## NEXT
DONE

# Unit U-EM2c — CloudLightingParameters / CloudParameters / ShadowParameters / ShadowRange reflected member-table reversing

Source: static analysis only (exe data via rdis.exe; no game launch; no tools.rtools MCP). Exe: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base.
Input listings: docs/progress/oc_U-EM2c_1188250.txt, oc_U-EM2c_1d4fd0.txt, oc_U-EM2c_1188170.txt, oc_U-EM2c_range_1188000_1189000.lst, str files.
All offsets are prefixed with their object context (desc=type descriptor, entry=member entry, reg=registry object) so every first-column offset is unique.
Every row tagged [V] (saw in disassembly, cite RVA), [I] (inferred), [?] (unknown), [V live] (prior-run live capture, cited).
No skipped offsets.

================================================================================
PART (1) — sub_1188250 descriptor builder: stores into desc+0x38..+0x80
================================================================================

sub_1188250 (desc=rax=rcx) zero-initialises the type descriptor. It contains NO
alloc/ctor calls. The stores at +0x60,+0x68,+0x70,+0x78 are zero-init stores;
the live non-zero values (+0x60=0xD4C25870, +0x68->node, +0x70->ctrlblock,
+0x78->container) are filled at registration runtime (sub_1d4fd0 /
sub_1188780), not here.

| offset   | size | read/store address (site) | verbatim `0xRVA  instr` proof | meaning | tag |
|----------|------|---------------------------|-------------------------------|---------|-----|
| desc+0x38 | 8 | `0x11882dc` | `0x11882dc  mov qword ptr [rax+0x38],0` | 0 (no cb stored yet) | [V] |
| desc+0x48 | 16 | `0x11882f2` | `0x11882f2  movups [rax+0x48],xmm0` | 0 (xmm0 zeroed) | [V] |
| desc+0x54 | 16 | `0x11882f6` | `0x11882f6  movups [rax+0x54],xmm0` | 0 (bytes 0x54-0x63, covers +0x60) | [V] |
| desc+0x68 | 16 | `0x11882fa` | `0x11882fa  movups [rax+0x68],xmm0` | 0 (bytes 0x68-0x77, covers +0x68,+0x70) | [V] |
| desc+0x78 | 8 | `0x11882fe` | `0x11882fe  mov qword ptr [rax+0x78],0` | 0 (container ptr, zeroed here) | [V] |

Other sub_1188250 stores (context, at/below +0x38): desc+0x00=&global 0x128E48E0 [`0x11882a9  mov [rax],rdx`], desc+0x08=hash[0x128E48E4] [`0x11882ac  mov [rax+8],ecx`], desc+0x10=0 [`0x11882af  mov qword ptr [rax+0x10],0`], desc+0x18=flags 0x80 [`0x11882b7  mov dword ptr [rax+0x18],0x80`], desc+0x20=count 0x14 (20) [`0x11882be  mov qword ptr [rax+0x20],0x14`], desc+0x28=cb sub_1188170 [`0x11882cd  mov [rax+0x28],rcx`], desc+0x30=cb sub_11884a0 [`0x11882d8  mov [rax+0x30],rcx`], desc+0x40=cb sub_11886f0 [`0x11882eb  mov [rax+0x40],rcx`].

CONCLUSION part (1): sub_1188250 only zeroes desc+0x38..+0x80; NO alloc/ctor calls inside sub_1188250. Runtime fill of +0x60,+0x68,+0x70,+0x78 happens via sub_1d4fd0 (preserves/moves: [`0x1d50ab  mov eax,[rcx+0x60]` / `0x1d50ae  mov [rbx+0x60],eax`], [`0x1d50b1  mov rax,[rcx+0x68]` / `0x1d50b5  mov [rbx+0x68],rax`], [`0x1d50b9  mov rax,[rcx+0x70]` / `0x1d50bd  mov [rbx+0x70],rax`], [`0x1d50c8  mov rax,[rcx+0x78]` / `0x1d50cc  mov qword ptr [rcx+0x78],0` / `0x1d50d4  mov [rbx+0x78],rax`]) and sub_1188780 ([`0x11887ea  mov dword ptr [rsi+0x30],0`], [`0x11887f1  mov eax,[rsi]` / `0x11887f3  mov [rsi+0x34],eax`], [`0x11887f6  mov word ptr [rsi+0x38],0`]).

================================================================================
PART (2) — sub_11884a0 (cb desc+0x30) and sub_11886f0 (cb desc+0x40): entry layout + container path
================================================================================

Both callbacks build ONE member entry at rcx/rsi with the same field layout.
Sites from both callbacks are listed per offset.

| offset   | size | read/store address (site) | verbatim `0xRVA  instr` proof | meaning | tag |
|----------|------|---------------------------|-------------------------------|---------|-----|
| entry+0x00 | 8 | sub_11884a0 `0x11884fd` / sub_11886f0 `0x1188726`,`0x118874e`,`0x1188757` | `0x11884fd  mov [rsi],rax` (rax=alloc'd block) | ptr to owned name block | [V] |
| entry+0x10 | 8 | sub_11884a0 `0x11884b4` / sub_11886f0 `0x118870c` | `0x11884b4  mov [rcx+0x10],rax` (rax=lea [0x1188560]) | compare func sub_1188560 | [V] |
| entry+0x18 | 8 | sub_11884a0 `0x11884c6` / sub_11886f0 `0x118871e`,`0x118873d` | `0x11884c6  mov [rcx+0x18],rax` (rax=lea [0x11886D0]) | destroy func sub_11886d0 or 0 | [V] |
| entry+0x20 | 4 | sub_11884a0 `0x11884b8` / sub_11886f0 `0x1188710` | `0x11884b8  mov dword ptr [rcx+0x20],0x8DE632ED` | type hash | [V] |
| entry+0x24 | 1 | sub_11884a0 `0x11884ca` / sub_11886f0 `0x1188722`,`0x118874a`,`0x1188757-area` | `0x11884ca  mov byte ptr [rcx+0x24],1` | tag byte (1/3/4) | [V] |
| entry+0x28 | 8 | sub_11884a0 `0x1188500` / sub_11886f0 `0x118875a` | `0x1188500  mov [rsi+0x28],rdi` | rdi/rdx = offset | [V] |
| entry+0x30 | 8 | sub_11884a0 `0x1188504` / sub_11886f0 `0x118875e` | `0x1188504  mov qword ptr [rsi+0x30],0` | 0 | [V] |
| entry+0x38 | 8 | sub_11884a0 `0x1188513` / sub_11886f0 `0x118876d` | `0x1188513  mov [rsi+0x38],rax` (rax=lea [0x1188540]) | sub_1188540 | [V] |

sub_11884a0 (rcx=rsi=entry obj, rdx=rdi) allocation: [`0x11884ce  mov rcx,[0x1233E1A8]`], [`0x11884d8  mov rax,[rax+8]`], [`0x11884dc  mov edx,0x14`] (alloc size 0x14 = 20 bytes from registry [0x1233E1A8]), [`0x11884e1  call qword ptr [0xF99FFA0]`]. Allocated block: [`0x11884ec  mov dword ptr [rax+0x10],0x101`], [`0x11884fa  movaps [rax],xmm0`] (xmm0=data_f0cd370=vtable sub_1800000) -> block +0x0=vtable, +0x10=0x101.

sub_11886f0 branches on test r8,r8 / test r9,r9: case r8==0&&r9==0 -> tag 1, name=0, destroy=sub_11886D0; case r8!=0,r9==0 -> tag 3, name=r8, destroy=0; case r8==0,r9!=0 -> tag 4, name=r9; case r8!=0,r9!=0 -> tag 3, name=r8. All cases: entry+0x10=sub_1188560, entry+0x20=hash 0x8DE632ED, entry+0x28=rdx offset, entry+0x30=0, entry+0x38=sub_1188540.

ENTRY layout summary [V]: entry+0x00 name ptr (char*/std::string), entry+0x10 compare func (sub_1188560), entry+0x18 destroy func (sub_11886d0 or 0), entry+0x20 type hash dword (0x8DE632ED), entry+0x24 byte tag (1/3/4), entry+0x28 offset (u32, from rdx), entry+0x30 0, entry+0x38 sub_1188540. Highest stored field is entry+0x38 (qword) -> entry spans [0x00,0x40) -> stride S = 0x40 (64) [I inferred from field layout; not yet confirmed by append-code pointer arithmetic].

sub_1188540 (called at entry+0x38): [`0x1188549  mov rcx,[rdx+0x28]`], [`0x1188550  call 0x1188170`], [`0x1188555  mov [rsi+0x30],rax`] — entry+0x30 = hash-lookup result [V].

sub_1188170 (cb desc+0x28, hash-lookup): reads [rcx+0x0],[rcx+0x8],[rcx+0x20],[rcx+0x28]; returns [rdx+0x10] [`0x1188170-0x118821e`]. Registry table at [0x128E4858].

CONTAINER PATH (from descriptor to member array) [V + V live]:
- desc+0x78 = container pointer [V]: sub_1d4fd0 moves it: [`0x1d50c8  mov rax,[rcx+0x78]`], [`0x1d50cc  mov qword ptr [rcx+0x78],0`], [`0x1d50d4  mov [rbx+0x78],rax`] (container moved from desc to registry object rbx). sub_1188780 builds the container (0xE0 block, vtable 0xEFCFBA0) [`0x1188b58-0x1188b85`].
- [desc+0x78] -> container object; container +0x48 = begin ptr, +0x50 = end ptr [V live cited: prior run desc @0x22FC64D4560, +0x78 -> container @0x22FC61DB700, +0x48/+0x50 = begin/end 0x22FC607E9A0/0x...EA08].
- Member entries = [container+0x48 .. container+0x50), stride S=0x40 [I]; entry +0x00 = name std::string/char*, +0x28 = offset u32, +0x24 = type tag byte / +0x20 = type hash.

RECIPE (partial): read qword [exe+0x1233E1A8] -> registry object; walk to type descriptor; desc+0x78 -> container; members = [container+0x48 .. container+0x50) stride S=0x40 [I]; name at entry+0x00 (std::string/char* [V]), offset at entry+0x28 (u32 [V]), type tag at entry+0x24 (byte [V]) / type hash at entry+0x20 (dword [V]).

================================================================================
PART (3) — sibling type-inits for CloudParameters / ShadowParameters / ShadowRange
================================================================================

Each sibling type-init follows the same shape: stores hash to [0x128E48xx]-style global, RTTI name ptr to global, sizeof to global (same pattern as CloudLightingParameters sub_1188400).

CloudLightingParameters (reference, already proven) [V]:
- sub_1188400 @0x1188400: [`0x118842b  mov [0x128E48E0],eax`] ([0x128E48E0]=[0x128E48FC] &global); [`0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED`] (hash); [`0x118843b  lea rax,[0xF6416AB]`] / [`0x1188442  mov [0x128E48E8],rax`] (RTTI "mce::framebuilder::CloudLightingParameters]"); [`0x1188449  mov qword ptr [0x128E48F0],0x2A`] (sizeof). Init flag [0x128E4900], counter [0x128C2024].

ShadowRange [V]:
- sub_5437e20 @0x5437e20: [`0x5437e45  mov eax,[0x129C7A04]`] / [`0x5437e4b  mov [0x129C79E8],eax`] (&global); [`0x5437e51  mov dword ptr [0x129C79EC],0x990FE13D`] (hash); [`0x5437e5b  lea rax,[0xF67B6CF]`] / [`0x5437e62  mov [0x129C79F0],rax`] (RTTI "mce::framebuilder::ShadowRange]"); [`0x5437e69  mov qword ptr [0x129C79F8],0x1E`] (sizeof). Init flag [0x129C7A08], counter [0x128C2024]. Globals 0x129C79E8-0x129C7A08.

PointLightShadowParameters (related Shadow* type, same shape) [V]:
- sub_116fb60 @0x116fb60: [`0x116fb85  mov eax,[0x128E453C]`] / [`0x116fb8b  mov [0x128E4520],eax`] (&global); [`0x116fb91  mov dword ptr [0x128E4524],0xACB08936`] (hash); [`0x116fb9b  lea rax,[0xF640FD6]`] / [`0x116fba2  mov [0x128E4528],rax`] (RTTI "mce::framebuilder::PointLightShadowParameters]"); [`0x116fba9  mov qword ptr [0x128E4530],0x2D`] (sizeof). Init flag [0x128E4540], counter [0x128C2024]. Globals 0x128E4520-0x128E4540.
- Its callback sub_116fc00 @0x116fc00: [`0x116fc14  mov [rcx+0x10],rax`] (entry+0x10=sub_116FD50); [`0x116fc18  mov dword ptr [rcx+0x20],0xACB08936`] (hash); [`0x116fc26  mov [rcx+0x18],rax`] (entry+0x18=sub_116FE80); [`0x116fc2a  mov byte ptr [rcx+0x24],1`] (tag); [`0x116fc3c  mov edx,0x90`] / [`0x116fc41  call qword ptr [0xF99FFA0]`] (alloc 0x90).

CloudParameters [UNVERIFIED — type-init RVA not located]:
- str f6419fd "mce::framebuilder::CloudParameters]" (no code refs). RTTI guess f6419d3 (string+0x36 prefix) -> ripscan returned NO hit; tried f6419d0-f6419df, nothing.
- No type-init function located that stores CloudParameters hash/RTTI/sizeof to globals via immediate-LEA (unlike the three above).
- [UNVERIFIED: 0xF6419D3 CloudParameters type-init RVA not located; RTTI immediate-LEA absent from .text]

ShadowParameters [UNVERIFIED — type-init RVA not located]:
- str f641005 "mce::framebuilder::ShadowParameters]" (no code refs). RTTI guess f64102b (string+0x36) -> ripscan returned NO hit.
- No type-init function located that stores ShadowParameters hash/RTTI/sizeof to globals via immediate-LEA.
- [UNVERIFIED: 0xF64102B ShadowParameters type-init RVA not located; RTTI immediate-LEA absent from .text]

Note: ripscan for 0x128C2024 (global type-registration counter written by every type-init) returned ~60 type-init functions (e.g. 120420, 120630, 1d40c0, 1d64d0, ... 1fxxxx, 2f9fe0, ...). CloudParameters/ShadowParameters may be among these but load RTTI non-immediately so they are not found by RTTI-address ripscan. Too many to disassemble all within this unit.

Sibling type-inits are NOT in range 0x1188000-0x1189000 (that range contains only CloudLightingParameters-related functions — all use hash 0x8DE632ED).

================================================================================
FINAL RECIPE (deliverable)
================================================================================

"read qword [exe+0x1233E1A8] -> registry object; walk to the type descriptor
(desc+0x78 holds the container pointer); members = [container+0x48 .. container+0x50)
stride S=0x40 [I]; name at entry+0x00 (std::string/char* [V]), offset at entry+0x28 (u32 [V]), type tag at entry+0x24 (byte [V]) / type hash at entry+0x20 (dword [V])."

The same container walk applies to CloudParameters/ShadowParameters/ShadowRange/RenderShadowDescription once their descriptors are found in the registry. ShadowRange descriptor globals are proven above [V]; CloudParameters and ShadowParameters are not yet located.

================================================================================
CLOSES?
================================================================================

CLOSES? NO

Single blocking fact: the type-init RVAs (and their global/descriptor rows: hash global, RTTI-ptr global, sizeof global) for CloudParameters and ShadowParameters are NOT located. Their RTTI name-pointer strings (f6419fd CloudParameters, f641005 ShadowParameters) have no code references and no immediate-LEA ripscan hit, so their registration functions cannot be identified statically from the inputs available. ShadowRange IS complete (sub_5437e20). Until CloudParameters and ShadowParameters type-inits are found (e.g. by disassembling candidates from the 0x128C2024 type-init list, or a live capture of the registration call site), part (3) is incomplete for those two types and the recipe cannot be marked fully [V] for all five types.

Files created: docs/progress/oc_U-EM2c.md (this file; no other files created or edited).

## TOOL REQUESTS
None required for this unit; all evidence gathered via rdis.exe dis and ripscan.py. No helper scripts written.
