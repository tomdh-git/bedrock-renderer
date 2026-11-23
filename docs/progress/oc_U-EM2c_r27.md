## NEXT
DONE

# UNIT U-EM2c — M2c: Cloud*/Shadow* reflected parameter member tables (static recipe)

GOAL (orchestrator, overrides prior runs): produce the Cheat-Engine-readable recipe that lets the orchestrator read the CloudLightingParameters / CloudParameters / ShadowParameters / ShadowRange member tables live:
(1) where the registration stores the built type descriptor / member vector (global/static RVA or heap chain from a known global);
(2) the member entry layout (stride, which entry field is the name char*, the offset, the type tag) read from the push/emplace in sub_11886f0;
(3) the vector begin/end field offsets in the descriptor.
Deliver as [V] instruction rows plus a one-line recipe, path form "[desc+0x78]->+0x48 begin, +0x50 end, stride S, name at +a, offset at +b, tag at +c". Also cover RenderShadowDescription.

EXE (data only, RVA-relative to image base): C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe
Static analysis ONLY (rdis dis/str/ptr/xr; no game, no CE, no debuggers, no builds). All instruction lines verbatim from `rdis.exe dis` of that exe.

------------------------------------------------------------
SUMMARY OF WHAT IS [V]-PROVEN (CloudLightingParameters, registration sub_11884a0)
------------------------------------------------------------
- Type-init sub_1188400 stores hash / RTTI name ptr / sizeof into [0x128E48xx] globals [V].
- Descriptor builder sub_1188250 builds the type descriptor at caller-provided rax=rcx and stores desc+0x00..desc+0x78 [V].
- sub_11884a0 (desc+0x30 callback) allocates the member container via sub_eea6040(registry [0x1233E1A8], count 0x14) and fills the dest object [V].
- sub_11886f0 (desc+0x40 callback) initializes ONE member entry: name ptr at entry+0x00, kind at entry+0x24, offset candidate at entry+0x28 [V stores]; implied stride 0x40 [I].
- Lookup sub_1188170 (desc+0x28 callback) reads container+0x00=begin, +0x08=end, +0x20=entries array (stride 0x18, entry+0x10 = member-desc ptr) [V].
- sub_1d4fd0 resolves a member by hash-walking the bucket/entries and copies desc fields incl. +0x60,+0x68,+0x70,+0x78 [V].
- sub_1188780 builds a descriptor on the stack via sub_1188250 then calls sub_1d4fd0 to populate members; allocates containers via sub_eea6040 [V].

------------------------------------------------------------
1) [V] INSTRUCTION ROWS — TYPE-LEVEL GLOBALS (sub_1188400, CloudLightingParameters type-init) [0x1188400..0x1188491)
------------------------------------------------------------

| global | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| g[0x128E48E0] | 4 | sub_1188400 | `0x1188425  mov eax,[0x128E48FC]` ; `0x118842b  mov [0x128E48E0],eax` | g[0x128E48E0] := g[0x128E48FC] (this address is stored at desc+0x00) [V] |
| g[0x128E48E4] | 4 | sub_1188400 | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash 0x8DE632ED (= desc+0x08) [V] |
| g[0x128E48E8] | 8 | sub_1188400 | `0x118843b  lea rax,[0xF6416AB]` ; `0x1188442  mov [0x128E48E8],rax` | RTTI name ptr -> "mce::framebuilder::CloudLightingParameters]" at 0xF6416AB [V] |
| g[0x128E48F0] | 8 | sub_1188400 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof(CloudLightingParameters) = 0x2A (42) [V] |
| g[0x128E4900] | 4 | sub_1188400 | `0x1188404  mov eax,[0x128E4900]` | registration flag/counter (dedup vs [tls+4]) [V] |

------------------------------------------------------------
2) [V] INSTRUCTION ROWS — TYPE DESCRIPTOR LAYOUT (sub_1188250, descriptor built at caller-provided rax=rcx) [0x1188250..0x118830b)
------------------------------------------------------------
sub_1188250 is invoked with rax = rcx = pointer to the descriptor buffer. One row per distinct field, all sites merged.

| desc field | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| desc+0x00 | 8 | sub_1188250 | `0x11882a2  lea rdx,[0x128E48E0]` ; `0x11882a9  mov [rax],rdx` | desc+0x00 := &global 0x128E48E0 [V] |
| desc+0x08 | 4 | sub_1188250 | `0x118829c  mov ecx,[0x128E48E4]` ; `0x11882ac  mov [rax+8],ecx` | desc+0x08 := type hash 0x8DE632ED [V] |
| desc+0x10 | 8 | sub_1188250 | `0x11882af  mov qword ptr [rax+0x10],0` | desc+0x10 := 0 [V] |
| desc+0x18 | 4 | sub_1188250 | `0x11882b7  mov dword ptr [rax+0x18],0x80` | desc+0x18 := flags 0x80 [V] |
| desc+0x20 | 8 | sub_1188250 | `0x11882be  mov qword ptr [rax+0x20],0x14` | desc+0x20 := member count = 0x14 (20) [V] |
| desc+0x28 | 8 | sub_1188250 | `0x11882c6  lea rcx,[0x1188170]` ; `0x11882cd  mov [rax+0x28],rcx` | desc+0x28 := lookup callback sub_1188170 [V] |
| desc+0x30 | 8 | sub_1188250 | `0x11882d1  lea rcx,[0x11884A0]` ; `0x11882d8  mov [rax+0x30],rcx` | desc+0x30 := callback sub_11884a0 [V] |
| desc+0x38 | 8 | sub_1188250 | `0x11882dc  mov qword ptr [rax+0x38],0` | desc+0x38 := 0 [V] |
| desc+0x40 | 8 | sub_1188250 | `0x11882e4  lea rcx,[0x11886F0]` ; `0x11882eb  mov [rax+0x40],rcx` | desc+0x40 := member-builder callback sub_11886f0 [V] |
| desc+0x48 | 16 | sub_1188250 | `0x11882ef  xorps xmm0,xmm0` ; `0x11882f2  movups [rax+0x48],xmm0` | desc+0x48..0x57 := zeroed [V] |
| desc+0x54 | 16 | sub_1188250 | `0x11882f6  movups [rax+0x54],xmm0` | desc+0x54..0x63 := zeroed (covers +0x60) [V] |
| desc+0x68 | 16 | sub_1188250 | `0x11882fa  movups [rax+0x68],xmm0` | desc+0x68..0x77 := zeroed (covers +0x70) [V] |
| desc+0x78 | 8 | sub_1188250 | `0x11882fe  mov qword ptr [rax+0x78],0` | desc+0x78 := 0 at construction [V] |

Note: desc+0x60 has no separate store (covered by the +0x54 movups zero block); desc+0x70 likewise (covered by the +0x68 movups block). desc+0x38..+0x80 stores are exactly: +0x38=0, +0x40=sub_11886f0, +0x48=0, +0x54=0, +0x68=0, +0x78=0. No static `mov [desc+0x60]`, `mov [desc+0x70]`, or `mov [desc+0x78],<container>` store exists in sub_1188250 [V]. The member-container pointer at desc+0x78 is populated at runtime via the indirect callback path, not statically located [see blocking fact below].

sub_1188400 calls sub_1188250 twice (0x118832d / 0x118836b) after the dedup dance on g[0x128E48F8]; sub_1188170 calls sub_1188250 at 0x1188225 with rcx = lea [0x128E4858] (builds the static template descriptor at global RVA 0x128E4858) [V]. CE found the live descriptor on the heap (scanned for &[0x128E48E0]); the static global 0x128E4858 vs the heap live instance link is not [V]-resolved statically.

------------------------------------------------------------
3) [V] INSTRUCTION ROWS — MEMBER-CONTAINER OBJECT (sub_11884a0, callback stored at desc+0x30) [0x11884a0..0x1188521)
------------------------------------------------------------
sub_11884a0(rcx = dest object, rdx = arg2). It allocates the member container then fills dest:

| dest field | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| dest+0x10 | 8 | sub_11884a0 | `0x11884ad  lea rax,[0x1188560]` ; `0x11884b4  mov [rcx+0x10],rax` | dest+0x10 := sub_1188560 [V] |
| dest+0x20 | 4 | sub_11884a0 | `0x11884b8  mov dword ptr [rcx+0x20],0x8DE632ED` | dest+0x20 := type hash 0x8DE632ED [V] |
| dest+0x18 | 8 | sub_11884a0 | `0x11884bf  lea rax,[0x11886D0]` ; `0x11884c6  mov [rcx+0x18],rax` | dest+0x18 := sub_11886d0 [V] |
| dest+0x24 | 1 | sub_11884a0 | `0x11884ca  mov byte ptr [rcx+0x24],1` | dest+0x24 := flag byte 1 [V] |
| dest+0x00 | 8 | sub_11884a0 | `0x11884ce  mov rcx,[0x1233E1A8]` ; `0x11884d5  mov rax,[rcx]` ; `0x11884d8  mov rax,[rax+8]` ; `0x11884dc  mov edx,0x14` ; `0x11884e1  call qword ptr [0xF99FFA0]` (=sub_eea6040) ; `0x11884fd  mov [rsi],rax` | dest+0x00 := member-container object from sub_eea6040(registry [0x1233E1A8], count 0x14); alloc size = 0x14 [V] |
| dest+0x28 | 8 | sub_11884a0 | `0x11884a7  mov rdi,rdx` ; `0x1188500  mov [rsi+0x28],rdi` | dest+0x28 := arg2 pointer [V] |
| dest+0x30 | 8 | sub_11884a0 | `0x1188504  mov qword ptr [rsi+0x30],0` | dest+0x30 := 0 [V] |
| dest+0x38 | 8 | sub_11884a0 | `0x118850c  lea rax,[0x1188540]` ; `0x1188513  mov [rsi+0x38],rax` | dest+0x38 := sub_1188540 [V] |

dest+0x08 is never written by sub_11884a0 [V]. The registry global read `0x11884ce  mov rcx,[0x1233E1A8]` and the allocator thunk `0x11884e1  call qword ptr [0xF99FFA0]` (= sub_eea6040) are [V]. The container object (heap) holds begin/end and the member entries; its layout is NOT statically confirmed (CE: container+0x48=begin, +0x50=end) [?].

------------------------------------------------------------
4) [V] INSTRUCTION ROWS — MEMBER ENTRY LAYOUT (sub_11886f0, callback stored at desc+0x40) [0x11886f0..0x1188771)
------------------------------------------------------------
sub_11886f0(rax = rcx = entry pointer, r8, r9, rdx) initializes ONE new member entry at rax. One row per distinct entry field, all branch sites merged.

| entry field | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| entry+0x00 | 8 | sub_11886f0 | `0x1188726  mov [rax],r8` ; `0x118874e  mov [rax],r8` ; `0x1188757  mov [rax],r9` | entry+0x00 := name char* pointer (r8, or r9 when r8==0) [V] |
| entry+0x10 | 8 | sub_11886f0 | `0x1188705  lea rcx,[0x1188560]` ; `0x118870c  mov [rax+0x10],rcx` ; `0x1188732  mov [rax+0x10],rcx` | entry+0x10 := sub_1188560 (fn ptr) [V] |
| entry+0x18 | 8 | sub_11886f0 | `0x1188717  lea rcx,[0x11886D0]` ; `0x118871e  mov [rax+0x18],rcx` ; `0x118873d  mov qword ptr [rax+0x18],0` | entry+0x18 := sub_11886d0 or 0 (fn ptr) [V] |
| entry+0x20 | 4 | sub_11886f0 | `0x1188710  mov dword ptr [rax+0x20],0x8DE632ED` ; `0x1188736  mov dword ptr [rax+0x20],0x8DE632ED` | entry+0x20 := constant parent type hash 0x8DE632ED (NOT a per-member type tag) [V] |
| entry+0x24 | 1 | sub_11886f0 | `0x1188722  mov byte ptr [rax+0x24],1` ; `0x118874a  mov byte ptr [rax+0x24],3` ; `0x1188753  mov byte ptr [rax+0x24],4` | entry+0x24 := kind byte u8 (1 = both null, 3 = r8 set, 4 = r9 only) [V] |
| entry+0x28 | 8 | sub_11886f0 | `0x118875a  mov [rax+0x28],rdx` | entry+0x28 := rdx (offset candidate; stored as qword, task asks u32 — size mismatch) [V] |
| entry+0x30 | 8 | sub_11886f0 | `0x118875e  mov qword ptr [rax+0x30],0` | entry+0x30 := 0 [V] |
| entry+0x38 | 8 | sub_11886f0 | `0x1188766  lea rcx,[0x1188540]` ; `0x118876d  mov [rax+0x38],rcx` | entry+0x38 := sub_1188540 (fn ptr) [V] |

Entry extent: the last store into a new entry is entry+0x38 (8-byte store), so the entry spans +0x00..+0x3F and the implied stride is 0x40 [I] — inferred from entry extent; the actual pointer arithmetic (rax = begin + i*stride) is performed by the indirect caller of desc+0x40, which has 0 direct xrefs and was NOT located statically [V: 0 direct xrefs; I: stride]. A clean "name char* / u32-offset / type-tag" mapping is NOT fully established: entry+0x20 is a constant hash, entry+0x24 is a kind byte (1/3/4), entry+0x28 is stored as qword [?].

Branch logic [V]: `0x11886f3  test r8,r8` / `0x11886f6  sete cl` ; `0x11886f9  test r9,r9` / `0x11886fc  sete r10b` ; `0x1188700  or r10b,cl` ; `0x1188703  jne short 0x118872B`. Both r8,r9 zero -> entry+0x00=r8(=0), entry+0x24=1. Else entry+0x18=0, entry+0x20=0x8DE632ED; if r8!=0: entry+0x24=3, entry+0x00=r8; else: entry+0x24=4, entry+0x00=r9. Common tail: entry+0x28=rdx, entry+0x30=0, entry+0x38=sub_1188540.

------------------------------------------------------------
5) [V] INSTRUCTION ROWS — CONTAINER WALK / LOOKUP (sub_1188170, callback stored at desc+0x28) [0x1188170..0x11881fb)
------------------------------------------------------------
sub_1188170(rcx = container pointer from sub_eea6040) reads the member container:

| container field | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| container+0x00 | 8 | sub_1188170 | `0x11881a0  mov rax,[rcx]` | container+0x00 := bucket/vector begin pointer [V] |
| container+0x08 | 8 | sub_1188170 | `0x11881a3  mov r8,[rcx+8]` | container+0x08 := bucket/vector end pointer [V] |
| count | - | sub_1188170 | `0x11881a7  sub r8,rax` / `0x11881aa  shr r8,3` / `0x11881ae  dec r8d` / `0x11881b1  and r8d,edx` | count = (end - begin) / 8, then -1 & mask (edx = [g[0x128E4858]+4]) [V] |
| container+0x20 | 8 | sub_1188170 | `0x11881b8  mov r8,[rcx+0x20]` | container+0x20 := entries array base [V] |
| entry walk | - | sub_1188170 | `0x11881dd  lea r9,[r8+r10*8]` / `0x11881e1  cmp [r8+r10*8+8],edx` | entries indexed stride 24 (0x18): [+0x00] index/chain, [+0x08] hash, [+0x10] ptr [V] |
| resolved member | 8 | sub_1188170 | `0x11881f2  mov rax,[rdx+0x10]` | [rdx+0x10] := pointer to member descriptor (stride 0x40 per section 4) [V] |

------------------------------------------------------------
6) [V] INSTRUCTION ROWS — MEMBER POPULATION (sub_1d4fd0) and DESCRIPTOR BUILD (sub_1188780)
------------------------------------------------------------
sub_1d4fd0(rcx = desc+0x10, rdx = bucket object, r8 = desc addr, r9d = hash) resolves one member by bucket hash-walk and writes [rsi+0x10] = member-desc ptr; copies desc fields:

| field | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| dst+0x60 | 4 | sub_1d4fd0 | `0x1d50ab  mov eax,[rcx+0x60]` ; `0x1d50ae  mov [rbx+0x60],eax` | copies desc+0x60 (u32, CE: 0xD4C25870) [V] |
| dst+0x68 | 8 | sub_1d4fd0 | `0x1d50b1  mov rax,[rcx+0x68]` ; `0x1d50b5  mov [rbx+0x68],rax` | copies desc+0x68 [V] |
| dst+0x70 | 8 | sub_1d4fd0 | `0x1d50b9  mov rax,[rcx+0x70]` ; `0x1d50bd  mov [rbx+0x70],rax` | copies desc+0x70 [V] |
| src+0x68 zero | 16 | sub_1d4fd0 | `0x1d50c1  xorps xmm0,xmm0` ; `0x1d50c4  movups [rcx+0x68],xmm0` | zeroes src+0x68 [V] |
| src+0x78 read+clear | 8 | sub_1d4fd0 | `0x1d50c8  mov rax,[rcx+0x78]` ; `0x1d50cc  mov qword ptr [rcx+0x78],0` | reads desc+0x78, clears src+0x78 [V] |
| dst+0x78 | 8 | sub_1d4fd0 | `0x1d50d4  mov [rbx+0x78],rax` | copies desc+0x78 to dst [V] |

sub_1188780(rcx = desc, rdx, r8) builds a descriptor (typically on stack at rbp-0x20) then populates members:
- `0x11887b6  mov dword ptr [rcx],0x8DE632ED` ; `0x11887bc  mov [rcx+8],rdx` — [rcx+0]=hash, [rcx+8]=rdx [V]
- `0x11887c0  lea rdi,[rcx+0x10]` ; `0x11887cf  call 0x1188250` — builds descriptor at rcx+0x10 via sub_1188250 [V]
- `0x11887d5  mov rcx,rdi` ; `0x11887d8  mov rdx,rbx` ; `0x11887db  mov r8,r15` ; `0x11887de  mov r9d,0x8DE632ED` ; `0x11887e4  call 0x1D4FD0` — sub_1d4fd0(desc+0x10, rdx+0x18, desc_addr, hash) [V]
- `0x11887ea  mov dword ptr [rsi+0x30],0` ; `0x11887f1  mov eax,[rsi]` ; `0x11887f3  mov [rsi+0x34],eax` ; `0x11887f6  mov word ptr [rsi+0x38],0` — clears [rsi+0x30], copies [rsi] to [rsi+0x34], zeroes [rsi+0x38] [V]
- container allocation via sub_eea6040 (size 0x80 or computed, `0x118885c` / `0x1188887  call qword ptr [0xF99FFA0]`) [V]

sub_1d5350 (called from sub_1d4fd0 at 0x1d50eb) rehashes the bucket array (container+0x28/+0x30) and computes load factor; sub_1d54f0 grows the entries array (stride 0x18 entries) via sub_eea6040 [V]. These confirm entries are stride-0x18 bucket entries whose [+0x10] points to stride-0x40 member descriptors.

------------------------------------------------------------
7) ONE-LINE RECIPE (CE-readable path; [V] where marked)
------------------------------------------------------------
Static [V] elements:
  - registry object pointer: read qword [exe+0x1233E1A8] [V] (sub_11884a0 `0x11884ce mov rcx,[0x1233E1A8]`)
  - descriptor layout: built by sub_1188250; desc+0x78 field exists and is zeroed at construction [V]; desc+0x28=sub_1188170, desc+0x30=sub_11884a0, desc+0x40=sub_11886f0 [V]
  - member entry initializer: sub_11886f0 stores name-ptr at entry+0x00, rdx at entry+0x28, kind byte at entry+0x24, implied stride 0x40 [V stores / I stride]
  - member-container object allocated by sub_eea6040(registry [0x1233E1A8], count 0x14) and stored at dest+0x00 by sub_11884a0 [V]

Not [V]-located statically (blocking the complete recipe):
  - the store that makes desc+0x78 hold the member-container pointer (sub_1188250 only zeroes it; the container write is via the indirect callback/allocator path, not found [V])
  - container object layout: container+0x48=begin, container+0x50=end (CE-reported only; sub_1188170 confirms +0x00/+0x08 bucket begin/end and +0x20 entries array, NOT +0x48/+0x50) [?]
  - entry stride S pointer arithmetic (caller of desc+0x40 not found; implied 0x40 from entry extent) [I]

One-line recipe (partially [V]):
  read qword [exe+0x1233E1A8] -> registry object; walk to the CloudLightingParameters descriptor (desc+0x00=&[0x128E48E0]); members = [desc+0x78]->container+0x48 begin, +0x50 end; stride S=0x40 [I]; name at +0x00 (char* pointer), offset at +0x28 (rdx, stored qword), type tag at +0x24 (kind byte 1/3/4) [?].
  Path form: [desc+0x78]->+0x48 begin, +0x50 end, stride 0x40 [I], name at +0x00 [V], offset at +0x28 [V qword], tag at +0x24 [? kind byte].

------------------------------------------------------------
8) SIBLING TYPE-INITS: CloudParameters / ShadowParameters / ShadowRange [0x1188000..0x1189000]
------------------------------------------------------------
The region 0x1188000..0x1189000 was exhaustively listed (`oc_U-EM2c_range_1188000_1189000.lst`). It contains exactly these functions:
- 0x1188000 / 0x1188110 / 0x1188150 (small helpers)
- sub_1188170 (lookup callback)
- sub_1188250 (descriptor builder)
- sub_1188390 (release)
- sub_1188400 (CloudLightingParameters type-init)
- sub_11884a0, sub_1188540, sub_1188560, sub_11886d0, sub_11886f0 (callbacks)
- sub_1188780 (descriptor build + member population)

There is NO separate sibling type-init for CloudParameters, ShadowParameters, or ShadowRange in 0x1188000..0x1189000 [V: exhaustive listing]. sub_1188400 is the only type-init there (stores hash 0x8DE632ED, RTTI ptr 0xF6416AB "mce::framebuilder::CloudLightingParameters]", sizeof 0x2A). Its direct callees are sub_1188250 (2x), sub_e938cb0, sub_e938d70; its callers are sub_1188250 (2x), sub_1188560 (1x), sub_11892d0 (2x), sub_1189500 (1x) [V: callers file]. None of those callers is a sibling type-init for another type [V].

RTTI strings exist but have zero code refs (verified negative in r19: `rdis ptr` = 0):
- CloudParameters: RTTI string 0xF6419FD (data-only)
- ShadowParameters: RTTI string 0xF641005; key "shadow_config" 0xF5B8368 at sub_1152460+0x270b
- ShadowRange: RTTI string 0xF67B699; key "shadow_range" 0xF5E056A at sub_53fcac0+0x1c60 [I]

So the global/descriptor rows (hash global, RTTI name ptr global, sizeof global, desc+0x00..+0x78, callback slots, container layout, entry stride) CANNOT be given for CloudParameters/ShadowParameters/ShadowRange — their registration functions are not located statically [?]. The recipe in section 7 applies identically once their registration functions (the sub_11884a0-equivalents storing sizeof + member count + callbacks) are found.

| Type | sizeof | registration located | member layout | status |
|---|---|---|---|---|
| CloudLightingParameters | 0x2A [V] (0x1188449) | sub_11884a0 [V] | stride 0x40 [I], name +0x00 [V], tag +0x24 [?], offset +0x28 [V qword] | partial recipe [V] |
| CloudParameters | unknown | NOT located (RTTI string 0xF6419FD only, zero code refs) | not located | [?] |
| ShadowParameters | unknown | NOT located (RTTI string 0xF641005; key "shadow_config" 0xF5B8368 at sub_1152460+0x270b) | not located | [?] |
| ShadowRange | unknown | NOT located (RTTI string 0xF67B699; key "shadow_range" 0xF5E056A at sub_53fcac0+0x1c60 [I]) | not located | [?] |

------------------------------------------------------------
9) RenderShadowDescription
------------------------------------------------------------
RenderShadowDescription size 0x20 [V] (end 0x1A + align 8) via its producer/clone 0x53e6c30 (fat 0x897, Effect tag 4) — see docs/progress/descriptions.md entry R-D7b and BGFX_MAP.md line 307. The insert vtable receiving the 0x14-byte entry and the shadow-pass execute-body [desc+off] reads are NOT located statically, so no per-field [V] rows beyond size 0x20; never-referenced fields are [?] padding per the live note.

struct RenderShadowDescription { char pad_0x00[0x20]; };  // [?] per-field offsets unknown; size 0x20 [V]

------------------------------------------------------------
10) Descriptions.h-compatible struct text
------------------------------------------------------------

```cpp
namespace mce::framebuilder {

// CloudLightingParameters: sizeof 0x2A [V], 20 reflected members [V count].
// Member offsets/names/types are runtime-reflected (NOT statically locatable):
//   descriptor globals: [exe+0x128E48E8]=RTTI name ptr, [exe+0x128E48F0]=sizeof 0x2A,
//   [exe+0x128E48E4]=hash 0x8DE632ED, [exe+0x128E48E0]=type-id global.
//   member container (heap) via sub_eea6040(registry [exe+0x1233E1A8], count 0x14);
//   container+0x00=begin, +0x08=end, +0x20=entries array (stride 0x18, +0x10=member-desc ptr) [V sub_1188170];
//   member descriptor stride 0x40 [I]: name char* +0x00 [V], type tag/kind u8 +0x24 [?], offset +0x28 [V qword].
// The actual member objects are written by the DOM->struct consumer at runtime;
// this header only records the reflected layout recipe, not field values.
struct CloudLightingParameters {
    char pad_0x00[0x2A];   // [?] individual member offsets not statically recoverable
};
static_assert(sizeof(CloudLightingParameters) == 0x2A, "CloudLightingParameters size");

// CloudParameters, ShadowParameters, ShadowRange: sizeof and member offsets unknown [?]
// (registration functions not located; RTTI strings only).
struct CloudParameters { char pad[?]; };
struct ShadowParameters { char pad[?]; };
struct ShadowRange { char pad[?]; };

// RenderShadowDescription: sizeof 0x20 [V] via producer 0x53e6c30; per-field offsets [?].
struct RenderShadowDescription {
    char pad_0x00[0x20];   // [?] insert vtable / shadow-pass reads not located
};
static_assert(sizeof(RenderShadowDescription) == 0x20, "RenderShadowDescription size");

}
```

------------------------------------------------------------
11) Count of types done out of 62
------------------------------------------------------------
This run adds NO new fully-typed type (per-field [V] rows not instruction-locatable for CloudParameters/ShadowParameters/ShadowRange; their registration functions are not located). CloudLightingParameters now has a complete [V] CE recipe skeleton but its per-member offsets are runtime-reflected, not static struct fields.
Cumulative: **28/62** (unchanged).

------------------------------------------------------------
CLOSES?
------------------------------------------------------------
NO — the item's wording (per-field rows / recipe for CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange, RenderShadowDescription with every RVA/offset [V]) is not fully met on disk. Single blocking fact: the member-container pointer store at desc+0x78, the container's +0x48/+0x50 begin/end layout, the entry stride S pointer-arithmetic, and the registration functions for CloudParameters/ShadowParameters/ShadowRange are populated at runtime through indirect calls through the descriptor callback slots (+0x30=sub_11884a0, +0x40=sub_11886f0) and the IAT allocator thunk [0xF99FFA0]=sub_eea6040; no static `mov [desc+0x78],<container>` store, no container +0x48/+0x50 layout, no push_back pointer arithmetic, and no sibling type-inits are [V]-located in the 0x1188xxx code (static-only analysis; CE live reads are not available to this agent). Everything else (registry global [0x1233E1A8], full descriptor layout via sub_1188250, CloudLightingParameters type-init via sub_1188400, both callbacks sub_11884a0/sub_11886f0 entry stores, lookup sub_1188170, member population sub_1d4fd0/sub_1188780) is [V]-proven above. RenderShadowDescription: size 0x20 [V] only; insert vtable / shadow-pass reads [?].

------------------------------------------------------------
WHAT CHANGED
------------------------------------------------------------
Created: docs/progress/oc_U-EM2c.md. No other file created or edited. No src/, header, Sigs.json, CMake, or hook edits. Static analysis only; no build, no game launch or attach.

------------------------------------------------------------
TOOL REQUESTS
------------------------------------------------------------
None — used only rdis.exe dis/fn/callers/fld and precomputed input data in docs/progress/; no helper script worth keeping was written.
