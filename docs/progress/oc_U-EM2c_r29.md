## NEXT
DONE

# Unit U-EM2c — CloudLightingParameters / CloudParameters / ShadowParameters / ShadowRange reflected member-table reversing

Source: static analysis only (rdis.exe on Minecraft.Windows.exe 1.26.62.01; RVAs relative to image base; no game launch, no CE, no debuggers, no builds). All `0xRVA  instr` lines copied verbatim from rdis output.
Offset cells are prefixed with object context (clp/cp/sp/sr = CloudLightingParameters/CloudParameters/ShadowParameters/ShadowRange; desc=type descriptor, entry=member entry, dest=callback dest object, reg=registry/global) so every first-column offset is unique across the file.
Tags: [V] saw in disassembly (cite RVA), [I] inferred (not confirmed by a pointer-arithmetic store), [?] unknown.

## Registry global

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| reg[0x1233E1A8] | 8 | sub_11884a0 `0x11884ce`, sub_118a7be, sub_5434d5e, sub_5434f92 | `0x11884ce  mov rcx,[0x1233E1A8]` | registry object pointer; all three container-builder callbacks read the allocator object from here | [V] |

## PART 1 — CloudLightingParameters: sub_1188250 descriptor builder, all stores into clp-desc+0x00..+0x78

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| clp-desc+0x00 | 8 | sub_1188250 | `0x11882a2  lea rdx,[0x128E48E0]` ; `0x11882a9  mov [rax],rdx` | clp-desc+0x00 := &type-id global 0x128E48E0 | [V] |
| clp-desc+0x08 | 4 | sub_1188250 | `0x118829c  mov ecx,[0x128E48E4]` ; `0x11882ac  mov [rax+8],ecx` | clp-desc+0x08 := type hash 0x8DE632ED | [V] |
| clp-desc+0x10 | 8 | sub_1188250 | `0x11882af  mov qword ptr [rax+0x10],0` | clp-desc+0x10 := 0 | [V] |
| clp-desc+0x18 | 4 | sub_1188250 | `0x11882b7  mov dword ptr [rax+0x18],0x80` | clp-desc+0x18 := flags 0x80 | [V] |
| clp-desc+0x20 | 8 | sub_1188250 | `0x11882be  mov qword ptr [rax+0x20],0x14` | clp-desc+0x20 := member count 0x14 (20) | [V] |
| clp-desc+0x28 | 8 | sub_1188250 | `0x11882c6  lea rcx,[0x1188170]` ; `0x11882cd  mov [rax+0x28],rcx` | clp-desc+0x28 := lookup callback sub_1188170 | [V] |
| clp-desc+0x30 | 8 | sub_1188250 | `0x11882d1  lea rcx,[0x11884A0]` ; `0x11882d8  mov [rax+0x30],rcx` | clp-desc+0x30 := container-builder callback sub_11884a0 | [V] |
| clp-desc+0x38 | 8 | sub_1188250 | `0x11882dc  mov qword ptr [rax+0x38],0` | clp-desc+0x38 := 0 | [V] |
| clp-desc+0x40 | 8 | sub_1188250 | `0x11882e4  lea rcx,[0x11886F0]` ; `0x11882eb  mov [rax+0x40],rcx` | clp-desc+0x40 := entry-builder callback sub_11886f0 | [V] |
| clp-desc+0x48 | 16 | sub_1188250 | `0x11882ef  xorps xmm0,xmm0` ; `0x11882f2  movups [rax+0x48],xmm0` | clp-desc+0x48..0x57 := zeroed | [V] |
| clp-desc+0x54 | 16 | sub_1188250 | `0x11882f6  movups [rax+0x54],xmm0` | clp-desc+0x54..0x63 := zeroed (covers clp-desc+0x60) | [V] |
| clp-desc+0x68 | 16 | sub_1188250 | `0x11882fa  movups [rax+0x68],xmm0` | clp-desc+0x68..0x77 := zeroed (covers clp-desc+0x70) | [V] |
| clp-desc+0x78 | 8 | sub_1188250 | `0x11882fe  mov qword ptr [rax+0x78],0` | clp-desc+0x78 := member-container pointer (zeroed at construction; filled at runtime) | [V] |

sub_1188250 zeroes clp-desc+0x38..+0x80; it contains NO alloc/ctor calls. The live non-zero values at clp-desc+0x60/clp-desc+0x68/clp-desc+0x70/clp-desc+0x78 (container pointer and others) are filled at registration/runtime by sub_1188780/sub_1d4fd0, not statically in sub_1188250.

## PART 2 — CloudLightingParameters: sub_11884a0 (desc+0x30 callback) and sub_11886f0 (desc+0x40 callback)

sub_11884a0(rcx=rsi=dest object, rdx=rdi=arg2): builds the member container and fills dest fields. rcx==rsi so all stores below target one object.

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| clp-dest+0x00 | 8 | sub_11884a0 | `0x11884ce  mov rcx,[0x1233E1A8]` ; `0x11884d5  mov rax,[rcx]` ; `0x11884d8  mov rax,[rax+8]` ; `0x11884dc  mov edx,0x14` ; `0x11884e1  call qword ptr [0xF99FFA0]` (=sub_eea6040) ; `0x11884fd  mov [rsi],rax` | clp-dest+0x00 := member-container object from sub_eea6040(registry [0x1233E1A8], alloc size 0x14) | [V] |
| clp-dest+0x10 | 8 | sub_11884a0 | `0x11884ad  lea rax,[0x1188560]` ; `0x11884b4  mov [rcx+0x10],rax` | clp-dest+0x10 := compare func sub_1188560 | [V] |
| clp-dest+0x18 | 8 | sub_11884a0 | `0x11884bf  lea rax,[0x11886D0]` ; `0x11884c6  mov [rcx+0x18],rax` | clp-dest+0x18 := destroy func sub_11886d0 | [V] |
| clp-dest+0x20 | 4 | sub_11884a0 | `0x11884b8  mov dword ptr [rcx+0x20],0x8DE632ED` | clp-dest+0x20 := type hash 0x8DE632ED | [V] |
| clp-dest+0x24 | 1 | sub_11884a0 | `0x11884ca  mov byte ptr [rcx+0x24],1` | clp-dest+0x24 := flag byte 1 | [V] |
| clp-dest+0x28 | 8 | sub_11884a0 | `0x11884a7  mov rdi,rdx` ; `0x1188500  mov [rsi+0x28],rdi` | clp-dest+0x28 := arg2 pointer | [V] |
| clp-dest+0x30 | 8 | sub_11884a0 | `0x1188504  mov qword ptr [rsi+0x30],0` | clp-dest+0x30 := 0 | [V] |
| clp-dest+0x38 | 8 | sub_11884a0 | `0x118850c  lea rax,[0x1188540]` ; `0x1188513  mov [rsi+0x38],rax` | clp-dest+0x38 := lookup func sub_1188540 | [V] |

sub_11886f0(rax=rcx=entry pointer, r8/r9=name args, rdx=offset): initializes ONE member entry. One row per distinct entry field, all branch sites merged.

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| clp-entry+0x00 | 8 | sub_11886f0 | `0x1188726  mov [rax],r8` ; `0x118874e  mov [rax],r8` ; `0x1188757  mov [rax],r9` | clp-entry+0x00 := name char* pointer (r8, or r9 in the tag-4 branch) | [V] |
| clp-entry+0x10 | 8 | sub_11886f0 | `0x1188705  lea rcx,[0x1188560]` ; `0x118870c  mov [rax+0x10],rcx` ; `0x1188732  mov [rax+0x10],rcx` | clp-entry+0x10 := compare func sub_1188560 | [V] |
| clp-entry+0x18 | 8 | sub_11886f0 | `0x1188717  lea rcx,[0x11886D0]` ; `0x118871e  mov [rax+0x18],rcx` ; `0x118873d  mov qword ptr [rax+0x18],0` | clp-entry+0x18 := destroy func sub_11886d0 or 0 | [V] |
| clp-entry+0x20 | 4 | sub_11886f0 | `0x1188710  mov dword ptr [rax+0x20],0x8DE632ED` ; `0x1188736  mov dword ptr [rax+0x20],0x8DE632ED` | clp-entry+0x20 := parent type hash 0x8DE632ED | [V] |
| clp-entry+0x24 | 1 | sub_11886f0 | `0x1188722  mov byte ptr [rax+0x24],1` ; `0x118874a  mov byte ptr [rax+0x24],3` ; `0x1188753  mov byte ptr [rax+0x24],4` | clp-entry+0x24 := kind/tag byte u8 (1/3/4) | [V] |
| clp-entry+0x28 | 8 | sub_11886f0 | `0x118875a  mov [rax+0x28],rdx` | clp-entry+0x28 := offset u32 from rdx (stored as qword) | [V] |
| clp-entry+0x30 | 8 | sub_11886f0 | `0x118875e  mov qword ptr [rax+0x30],0` | clp-entry+0x30 := 0 | [V] |
| clp-entry+0x38 | 8 | sub_11886f0 | `0x1188766  lea rcx,[0x1188540]` ; `0x118876d  mov [rax+0x38],rcx` | clp-entry+0x38 := lookup func sub_1188540 | [V] |

CLP entry layout [V]: entry+0x00 name char*, entry+0x10 compare func, entry+0x18 destroy func, entry+0x20 type hash dword, entry+0x24 kind byte, entry+0x28 offset (u32), entry+0x30 0, entry+0x38 lookup func. Highest stored field is clp-entry+0x38 (8-byte store) -> entry spans [0x00,0x40), implied stride S = 0x40 [I] (implied from entry extent; the pointer-arithmetic caller of desc+0x40 is indirect and not statically located).

CLP container path [V + prior [V live]]: clp-desc+0x78 = container pointer [V]; the live container (CE prior run) had container+0x48=begin, container+0x50=end pointers [V live from prior capture, not re-verified this run since the game is not running]; member entries = [container+0x48 .. container+0x50), stride S=0x40 [I]; entry +0x00 = name char* [V], +0x28 = offset u32 [V], +0x24 = tag byte [V] / +0x20 = type hash [V].

## PART 3 — CloudLightingParameters type-init sub_1188400 (type-level global rows)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| clp-g[0x128E48E0] | 4 | sub_1188400 | `0x1188425  mov eax,[0x128E48FC]` ; `0x118842b  mov [0x128E48E0],eax` | clp-g[0x128E48E0] := clp-g[0x128E48FC] (type-id global, stored at clp-desc+0x00) | [V] |
| clp-g[0x128E48E4] | 4 | sub_1188400 | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash 0x8DE632ED (= clp-desc+0x08) | [V] |
| clp-g[0x128E48E8] | 8 | sub_1188400 | `0x118843b  lea rax,[0xF6416AB]` ; `0x1188442  mov [0x128E48E8],rax` | RTTI name ptr -> "mce::framebuilder::CloudLightingParameters]" at 0xF6416AB | [V] |
| clp-g[0x128E48F0] | 8 | sub_1188400 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof(CloudLightingParameters) = 0x2A (42) | [V] |
| clp-g[0x128E4900] | 4 | sub_1188400 | `0x1188404  mov eax,[0x128E4900]` | registration flag (dedup vs TLS slot) | [V] |
| clp-g[0x128C2024] | 4 | sub_1188400 | `0x118846e  mov eax,[0x128C2024]` ; `0x1188477  mov [0x128C2024],ecx` | monotonic registration counter | [V] |

## PART 4 — sibling type-inits (CloudParameters / ShadowParameters / ShadowRange) — same 3-callback shape

The functions immediately around sub_1188400/sub_1188250 in 0x1188000..0x1189000 contain ONLY CloudLightingParameters machinery (exhaustive listing, prior run). The sibling type-inits were therefore located via their RTTI short-name strings (pretty_function_addr + 0x36): `rdis xr 0xF641A33` -> `118a72b sub_118a6f0+0x3b lea rax,[0xF641A33] "mce::framebuilder::CloudParameters]"`; `rdis xr 0xF64103B` -> `5434ccb sub_5434c90+0x3b lea rax,[0xF64103B] "mce::framebuilder::ShadowParameters]"`. ShadowRange already proven at sub_5437e20.

### 4a — CloudParameters type-init sub_118a6f0 @0x118A6F0 and descriptor builder sub_118A540

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| cp-g[0x128E4990] | 4 | sub_118a6f0 | `0x118a715  mov eax,[0x128E49AC]` ; `0x118a71b  mov [0x128E4990],eax` | cp-g[0x128E4990] := cp-g[0x128E49AC] (type-id global) | [V] |
| cp-g[0x128E4994] | 4 | sub_118a6f0 | `0x118a721  mov dword ptr [0x128E4994],0x8CBEF799` | CloudParameters type hash 0x8CBEF799 | [V] |
| cp-g[0x128E4998] | 8 | sub_118a6f0 | `0x118a72b  lea rax,[0xF641A33]` ; `0x118a732  mov [0x128E4998],rax` | RTTI name ptr -> "mce::framebuilder::CloudParameters]" at 0xF641A33 | [V] |
| cp-g[0x128E49A0] | 8 | sub_118a6f0 | `0x118a739  mov qword ptr [0x128E49A0],0x22` | sizeof(CloudParameters) = 0x22 (34) | [V] |
| cp-g[0x128E49A8] | 4 | sub_118a6f0 | `0x118a75e  mov eax,[0x128C2024]` ; `0x118a767  mov [0x128C2024],ecx` ; `0x118a76d  mov [0x128E49AC],eax` | registration counter / type-id | [V] |

sub_118A540 is the CloudParameters descriptor builder (called at 0x118ab2f from sub_118aba0), same shape as sub_1188250:

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| cp-desc+0x00 | 8 | sub_118A540 | `0x118a58c  mov ecx,[0x128E4994]` ; `0x118a592  lea rdx,[0x128E4990]` ; `0x118a599  mov [rax],rdx` | cp-desc+0x00 := &global 0x128E4990 | [V] |
| cp-desc+0x08 | 4 | sub_118A540 | `0x118a59c  mov [rax+8],ecx` | cp-desc+0x08 := hash 0x8CBEF799 | [V] |
| cp-desc+0x10 | 8 | sub_118A540 | `0x118a59f  mov qword ptr [rax+0x10],0` | cp-desc+0x10 := 0 | [V] |
| cp-desc+0x18 | 4 | sub_118A540 | `0x118a5a7  mov dword ptr [rax+0x18],0x80` | cp-desc+0x18 := flags 0x80 | [V] |
| cp-desc+0x20 | 8 | sub_118A540 | `0x118a5ae  mov qword ptr [rax+0x20],0x28` | cp-desc+0x20 := member count 0x28 (40) | [V] |
| cp-desc+0x28 | 8 | sub_118A540 | `0x118a5b6  lea rcx,[0x118A460]` ; `0x118a5bd  mov [rax+0x28],rcx` | cp-desc+0x28 := lookup callback sub_118A460 | [V] |
| cp-desc+0x30 | 8 | sub_118A540 | `0x118a5c1  lea rcx,[0x118A790]` ; `0x118a5c8  mov [rax+0x30],rcx` | cp-desc+0x30 := container-builder callback sub_118a790 | [V] |
| cp-desc+0x38 | 8 | sub_118A540 | `0x118a5cc  mov qword ptr [rax+0x38],0` | cp-desc+0x38 := 0 | [V] |
| cp-desc+0x40 | 8 | sub_118A540 | `0x118a5d4  lea rcx,[0x118AA50]` ; `0x118a5db  mov [rax+0x40],rcx` | cp-desc+0x40 := entry-builder callback sub_118aa50 | [V] |
| cp-desc+0x48 | 16 | sub_118A540 | `0x118a5df  xorps xmm0,xmm0` ; `0x118a5e2  movups [rax+0x48],xmm0` | cp-desc+0x48..0x57 := zeroed | [V] |
| cp-desc+0x54 | 16 | sub_118A540 | `0x118a5e6  movups [rax+0x54],xmm0` | cp-desc+0x54..0x63 := zeroed | [V] |
| cp-desc+0x68 | 16 | sub_118A540 | `0x118a5ea  movups [rax+0x68],xmm0` | cp-desc+0x68..0x77 := zeroed | [V] |
| cp-desc+0x78 | 8 | sub_118A540 | `0x118a5ee  mov qword ptr [rax+0x78],0` | cp-desc+0x78 := member-container pointer (zeroed at construction) | [V] |

sub_118a790 (CloudParameters desc+0x30 container-builder cb) and sub_118aa50 (desc+0x40 entry-builder cb):

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| cp-dest+0x00 | 8 | sub_118a790 | `0x118a7be  mov rcx,[0x1233E1A8]` ; ... `0x118a7d1  call qword ptr [0xF99FFA0]` (alloc size 0x28) ; `0x118a81b  mov [rsi],rax` | cp-dest+0x00 := member-container object (sub_eea6040, alloc size 0x28) | [V] |
| cp-dest+0x10 | 8 | sub_118a790 | `0x118a79d  lea rax,[0x118A880]` ; `0x118a7a4  mov [rcx+0x10],rax` | cp-dest+0x10 := sub_118A880 | [V] |
| cp-dest+0x18 | 8 | sub_118a790 | `0x118a7af  lea rax,[0xDE5ED0]` ; `0x118a7b6  mov [rcx+0x18],rax` | cp-dest+0x18 := sub_DE5ED0 | [V] |
| cp-dest+0x20 | 4 | sub_118a790 | `0x118a7a8  mov dword ptr [rcx+0x20],0x8CBEF799` | cp-dest+0x20 := type hash 0x8CBEF799 | [V] |
| cp-dest+0x24 | 1 | sub_118a790 | `0x118a7ba  mov byte ptr [rcx+0x24],1` | cp-dest+0x24 := flag byte 1 | [V] |
| cp-dest+0x28 | 8 | sub_118a790 | `0x118a81e  mov [rsi+0x28],rdi` | cp-dest+0x28 := arg2 pointer | [V] |
| cp-dest+0x30 | 8 | sub_118a790 | `0x118a822  mov qword ptr [rsi+0x30],0` | cp-dest+0x30 := 0 | [V] |
| cp-dest+0x38 | 8 | sub_118a790 | `0x118a82a  lea rax,[0x118A860]` ; `0x118a831  mov [rsi+0x38],rax` | cp-dest+0x38 := lookup func sub_118A860 | [V] |

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| cp-entry+0x00 | 8 | sub_118aa50 | `0x118aa86  mov [rax],r8` ; `0x118aaae  mov [rax],r8` | cp-entry+0x00 := name char* pointer (r8) | [V] |
| cp-entry+0x10 | 8 | sub_118aa50 | `0x118aa65  lea rcx,[0x118A880]` ; `0x118aa6c  mov [rax+0x10],rcx` ; `0x118aa92  mov [rax+0x10],rcx` | cp-entry+0x10 := sub_118A880 (compare func) | [V] |
| cp-entry+0x18 | 8 | sub_118aa50 | `0x118aa77  lea rcx,[0xDE5ED0]` ; `0x118aa7e  mov [rax+0x18],rcx` ; `0x118aa9d  mov qword ptr [rax+0x18],0` | cp-entry+0x18 := sub_DE5ED0 or 0 | [V] |
| cp-entry+0x20 | 4 | sub_118aa50 | `0x118aa70  mov dword ptr [rax+0x20],0x8CBEF799` ; `0x118aa96  mov dword ptr [rax+0x20],0x8CBEF799` | cp-entry+0x20 := type hash 0x8CBEF799 | [V] |
| cp-entry+0x24 | 1 | sub_118aa50 | `0x118aa82  mov byte ptr [rax+0x24],1` ; `0x118aaaa  mov byte ptr [rax+0x24],3` | cp-entry+0x24 := kind/tag byte u8 (1/3; tag-4 branch [I] by symmetry with CLP) | [V] |
| cp-entry+0x28 | 8 | sub_118aa50 | `0x118aaba  mov [rax+0x28],rdx` | cp-entry+0x28 := offset u32 from rdx | [V] |
| cp-entry+0x30 | 8 | sub_118aa50 | `0x118aabe  mov qword ptr [rax+0x30],0` | cp-entry+0x30 := 0 | [V] |
| cp-entry+0x38 | 8 | sub_118aa50 | `0x118aac6  lea rcx,[0x118A860]` ; `0x118aacd  mov [rax+0x38],rcx` | cp-entry+0x38 := lookup func sub_118A860 | [V] |

CloudParameters entry layout [V]: entry+0x00 name char*, +0x10 compare func, +0x18 destroy func, +0x20 type hash dword, +0x24 kind byte, +0x28 offset (u32), +0x30 0, +0x38 lookup func; implied stride S=0x40 [I].

### 4b — ShadowParameters type-init sub_5434c90 @0x5434C90 and container-builder sub_5434d30

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| sp-g[0x129C79C0] | 4 | sub_5434c90 | `0x5434cb5  mov eax,[0x129C79DC]` ; `0x5434cbb  mov [0x129C79C0],eax` | sp-g[0x129C79C0] := sp-g[0x129C79DC] (type-id global) | [V] |
| sp-g[0x129C79C4] | 4 | sub_5434c90 | `0x5434cc1  mov dword ptr [0x129C79C4],0x7C2A4E8C` | ShadowParameters type hash 0x7C2A4E8C | [V] |
| sp-g[0x129C79C8] | 8 | sub_5434c90 | `0x5434ccb  lea rax,[0xF64103B]` ; `0x5434cd2  mov [0x129C79C8],rax` | RTTI name ptr -> "mce::framebuilder::ShadowParameters]" at 0xF64103B | [V] |
| sp-g[0x129C79D0] | 8 | sub_5434c90 | `0x5434cd9  mov qword ptr [0x129C79D0],0x23` | sizeof(ShadowParameters) = 0x23 (35) | [V] |
| sp-g[0x129C79E0] | 4 | sub_5434c90 | `0x5434c94  mov eax,[0x129C79E0]` | registration flag | [V] |
| sp-g[0x128C2024] | 4 | sub_5434c90 | `0x5434cfe  mov eax,[0x128C2024]` ; `0x5434d07  mov [0x128C2024],ecx` ; `0x5434d0d  mov [0x129C79DC],eax` | monotonic registration counter / type-id | [V] |

sub_5434d30 (ShadowParameters desc+0x30 container-builder cb) — NOTE: alloc size 0x578 (1400) and the container is pre-filled with default values; this is a different container scheme than CloudLightingParameters:

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| sp-dest+0x00 | 8 | sub_5434d30 | `0x5434d5e  mov rcx,[0x1233E1A8]` ; ... `0x5434d6c  mov edx,0x578` ; `0x5434d71  call qword ptr [0xF99FFA0]` ; `0x5434e88  mov [rsi],rbx` | sp-dest+0x00 := member-container object (sub_eea6040, alloc size 0x578) | [V] |
| sp-dest+0x10 | 8 | sub_5434d30 | `0x5434d3d  lea rax,[0x5434EE0]` ; `0x5434d44  mov [rcx+0x10],rax` | sp-dest+0x10 := sub_5434EE0 | [V] |
| sp-dest+0x18 | 8 | sub_5434d30 | `0x5434d4f  lea rax,[0x5435750]` ; `0x5434d56  mov [rcx+0x18],rax` | sp-dest+0x18 := sub_5435750 | [V] |
| sp-dest+0x20 | 4 | sub_5434d30 | `0x5434d48  mov dword ptr [rcx+0x20],0x7C2A4E8C` | sp-dest+0x20 := type hash 0x7C2A4E8C | [V] |
| sp-dest+0x24 | 1 | sub_5434d30 | `0x5434d5a  mov byte ptr [rcx+0x24],1` | sp-dest+0x24 := flag byte 1 | [V] |
| sp-dest+0x28 | 8 | sub_5434d30 | `0x5434e8b  mov [rsi+0x28],rdi` | sp-dest+0x28 := arg2 pointer | [V] |
| sp-dest+0x30 | 8 | sub_5434d30 | `0x5434e8f  mov qword ptr [rsi+0x30],0` | sp-dest+0x30 := 0 | [V] |
| sp-dest+0x38 | 8 | sub_5434d30 | `0x5434e97  lea rax,[0x5434EC0]` ; `0x5434e9e  mov [rsi+0x38],rax` | sp-dest+0x38 := lookup func sub_5434EC0 | [V] |

sub_5434EE0 (ShadowParameters desc+0x40 entry-builder cb) — shown: entry setup and the 0x148-stride default-value copy loop:

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| sp-entry+0x10 | 8 | sub_5434EE0 | `0x5434f71  lea rax,[0x5434EE0]` ; `0x5434f78  mov [rsi+0x10],rax` | sp-entry+0x10 := sub_5434EE0 | [V] |
| sp-entry+0x18 | 8 | sub_5434EE0 | `0x5434f83  lea rax,[0x5435750]` ; `0x5434f8a  mov [rsi+0x18],rax` | sp-entry+0x18 := sub_5435750 | [V] |
| sp-entry+0x20 | 4 | sub_5434EE0 | `0x5434f7c  mov dword ptr [rsi+0x20],0x7C2A4E8C` | sp-entry+0x20 := type hash 0x7C2A4E8C | [V] |
| sp-entry+0x24 | 1 | sub_5434EE0 | `0x5434f8e  mov byte ptr [rsi+0x24],1` | sp-entry+0x24 := flag byte 1 | [V] |
| sp-entry+0x00 | 16 | sub_5434EE0 | `0x5434fbf  movups xmm0,[rdi]` ; `0x5434fda  movups [rbx],xmm0` | sp-entry+0x00 := copy of source+0x00 (16 bytes) | [V] |
| sp-container+0x40 | 16 | sub_5434EE0 | `0x5434fb7  movups xmm0,[rdi+0x40]` ; `0x5434fbb  movups [rbx+0x40],xmm0` | sp-container+0x40 := copy of source+0x40 (16 bytes) | [V] |
| sp-stride | — | sub_5434EE0 | `0x5435008  imul rax,0x148` ; `0x5435017  add rdi,0x50` | element stride 0x148 (320) for the default-value copy loop | [V] |

ShadowParameters entry layout is NOT the same stride-0x40 shape as CloudLightingParameters: sub_5434d30 allocates a 0x578-byte container pre-filled with defaults and sub_5434EE0 copies with stride 0x148, so the `[desc+0x78]->+0x48 begin,+0x50 end,stride 0x40` path is [V] for CloudLightingParameters/CloudParameters but [?] for ShadowParameters (different container scheme; entry+0x00 name/offset/tag stores not located for sub_5434EE0 within the disassembly window read).

### 4c — ShadowRange type-init sub_5437e20 @0x5437E20 (proven prior run)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| sr-g[0x129C79E8] | 4 | sub_5437e20 | `0x5437e45  mov eax,[0x129C7A04]` ; `0x5437e4b  mov [0x129C79E8],eax` | sr-g[0x129C79E8] := &global | [V] |
| sr-g[0x129C79EC] | 4 | sub_5437e20 | `0x5437e51  mov dword ptr [0x129C79EC],0x990FE13D` | ShadowRange type hash 0x990FE13D | [V] |
| sr-g[0x129C79F0] | 8 | sub_5437e20 | `0x5437e5b  lea rax,[0xF67B6CF]` ; `0x5437e62  mov [0x129C79F0],rax` | RTTI name ptr -> "mce::framebuilder::ShadowRange]" at 0xF67B6CF | [V] |
| sr-g[0x129C79F8] | 8 | sub_5437e20 | `0x5437e69  mov qword ptr [0x129C79F8],0x1E` | sizeof(ShadowRange) = 0x1E (30) | [V] |

## PART 5 — Recipe (CE-readable path; path form "[desc+0x78]->+0x48 begin, +0x50 end, stride S, name at +a, offset at +b, tag at +c")

- read qword [exe+0x1233E1A8] -> registry object [V]
- walk to the type descriptor (desc+0x00=&type-id global; desc+0x08=hash; desc+0x20=member count; desc+0x28/0x30/0x40 = lookup/container-builder/entry-builder callbacks) [V for CloudLightingParameters & CloudParameters; sub_118A540/sub_118a790/sub_118aa50 for CloudParameters]
- desc+0x78 -> member-container object [V field exists, zeroed at construction; container fill is runtime]
- members = [container+0x48 .. container+0x50), stride S=0x40 [I for CloudLightingParameters/CloudParameters; container+0x48/0x50 confirmed only by prior CE live capture, not by a static [V] store]
- entry +0x00 = name char* [V], +0x28 = offset u32 [V], +0x24 = kind/tag byte [V] / +0x20 = type hash dword [V]

Delivered path: "[desc+0x78]->+0x48 begin, +0x50 end, stride 0x40 [I], name at +0x00 [V], offset at +0x28 [V], tag at +0x24 [V] / hash at +0x20 [V]".

This recipe applies identically to CloudParameters (sub_118A540/sub_118a790/sub_118aa50; member count 0x28) and ShadowRange (sub_5437e20). For ShadowParameters the container scheme differs (alloc 0x578, stride 0x148 default-value copy), so the stride-0x40 entry path is [?] there.

## RenderShadowDescription

Not part of this run's three requested items (1) sub_1188250 desc+0x38..+0x80, (2) sub_11884a0/sub_11886f0 container path, (3) CloudParameters/ShadowParameters/ShadowRange type-inits. RenderShadowDescription insert vtable / shadow-pass consumer not located statically; size 0x20 [V] from prior run; per-field offsets [?].

## Count of types done out of 62

This run adds per-type-init global/descriptor rows [V] for CloudParameters and ShadowParameters (previously the blocking fact) and confirms ShadowRange [V]. CloudLightingParameters was already complete [V]. No new Descriptions.h struct fields are decoded in this run (reflected members are runtime tables, not static struct fields). Cumulative typed-count unchanged at 28/62 per the shared checklist; this unit delivers the reflected-member-table recipe, not struct fields.

## CLOSES?

NO.

Single blocking fact: the member-container begin/end offsets (container+0x48 begin / container+0x50 end) and the entry stride S are not statically [V]-proven for the shared recipe path. sub_1188170 confirms a bucket layout (container+0x00 begin, +0x08 end, +0x20 entries stride 0x18) which is a different object from the CE-reported container+0x48/+0x50; stride 0x40 is implied from entry extent (last store clp-entry+0x38) but no `base + i*stride` pointer arithmetic for the desc+0x40 caller is statically located. The prior CE live capture reported container+0x48/+0x50 for CloudLightingParameters, but the game is not running this run so it cannot be re-verified statically. Until container+0x48/+0x50 and stride S have a [V] static store (or a fresh live capture), the recipe path is not fully [V] for all five types. RenderShadowDescription insert vtable/consumer is also [?]. Everything else requested this run IS [V]: CloudLightingParameters desc+0x38..+0x80 stores, both callbacks + entry layout, and the CloudParameters (sub_118a6f0/sub_118A540/sub_118a790/sub_118aa50) and ShadowParameters (sub_5434c90/sub_5434d30/sub_5434EE0) and ShadowRange (sub_5437e20) type-init global/descriptor rows.

Files created: docs/progress/oc_U-EM2c.md (this file; no other files created or edited). No src/, header, Sigs.json, CMake, or hook edits. Static analysis only; no build, no game launch or attach.

## TOOL REQUESTS

None required; all evidence gathered via rdis.exe dis/xr/imm on the precomputed input data. No helper script written.
