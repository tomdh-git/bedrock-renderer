## NEXT
DONE

# UNIT U-EM2c — reflected type member-table recipe (CloudLightingParameters et al.)

GOAL (orchestrator, overrides prior notes): produce [V] instruction rows + one-line recipe so the orchestrator can dump reflected-type members live with CE:
"read qword [exe+RVA] -> descriptor; members = [desc+Xbegin..desc+Xend) stride S; name at +a (std::string), offset at +b (u32), type at +c".
Scope: sub_1188250 descriptor builder, sub_11884a0 (desc+0x30 callback), sub_11886f0 (desc+0x40 callback/member entry builder), sibling type-inits near 0x1188000..0x1189000.
Result file only: docs/progress/oc_U-EM2c.md.

## INPUT / VERIFIED GLOBALS (orchestrator live run, treated as verified fact unless disassembly contradicts)
- registry object = [exe+0x1233E1A8] (heap/data object); allocator used by registration is sub_eea6040 via [data_f99ffa0]
- CloudLightingParameters hash global = exe+0x128E48E0; RTTI name global exe+0x128E48E8 ("mce::framebuilder::CloudLightingParameters]"); sizeof global exe+0x128E48F0 (=0x2A=42); init-once flag exe+0x128E4900; hash-value storage exe+0x128E48FC; tag global exe+0x128E48E4.
- callbacks stored at desc+0x28=0x1188170, desc+0x30=0x11884a0, desc+0x40=0x11886f0.
- Live descriptor (CloudLightingParameters) @0x22FC64D4560: +0x00=&global, +0x08=hash, +0x18=flags 0x80, +0x20=count 0x14 (20 members), +0x28/+0x30/+0x40=callbacks, +0x60=0xD4C25870 (u32), +0x68->node(+0x00 ptr,+0x30=0xF), +0x70->shared_ptr-like ctl(vtable exe+0xF0DFBA0), +0x78->member vector node(+0x48=begin,+0x50=end). Members NOT directly in descriptor; container is at desc+0x78.

## (1) sub_1188250 descriptor builder — every store into desc+0x00..+0x78 ([V], RVA from listing oc_U-EM2c_1188250.txt)
All use rax = descriptor pointer (rcx in). Range 0x1188250..0x118830b, ret at 0x118830b.
| offset | size | store address | verbatim instr | meaning |
| +0x00 | qword | 0x11882a9 | `mov [rax],rdx` | desc+0x00 = rdx = lea [0x128E48E0] (pointer to hash global) at 0x11882a2 |
| +0x08 | dword | 0x11882ac | `mov [rax+8],ecx` | desc+0x08 = ecx = [0x128E48E4] (hash value) at 0x118829c |
| +0x10 | qword | 0x11882af | `mov qword ptr [rax+0x10],0` | desc+0x10 = 0 |
| +0x18 | dword | 0x11882b7 | `mov dword ptr [rax+0x18],0x80` | desc+0x18 = flags 0x80 |
| +0x20 | qword | 0x11882be | `mov qword ptr [rax+0x20],0x14` | desc+0x20 = member count 0x14 |
| +0x28 | qword | 0x11882cd | `mov [rax+0x28],rcx` | desc+0x28 = callback 0x1188170 (lea rcx,[0x1188170] at 0x11882c6) |
| +0x30 | qword | 0x11882d8 | `mov [rax+0x30],rcx` | desc+0x30 = callback 0x11884a0 (lea rcx,[0x11884A0] at 0x11882d1) |
| +0x38 | qword | 0x11882dc | `mov qword ptr [rax+0x38],0` | desc+0x38 = 0 |
| +0x40 | qword | 0x11882eb | `mov [rax+0x40],rcx` | desc+0x40 = callback 0x11886f0 (lea rcx,[0x11886F0] at 0x11882e4) |
| +0x48 | xmm(16) | 0x11882f2 | `movups [rax+0x48],xmm0` | desc+0x48 = 0 (begin of something, zeroed) |
| +0x54 | xmm(16) | 0x11882f6 | `movups [rax+0x54],xmm0` | desc+0x54 = 0 |
| +0x68 | xmm(16) | 0x11882fa | `movups [rax+0x68],xmm0` | desc+0x68 = 0 (node ptr, zeroed here) |
| +0x78 | qword | 0x11882fe | `mov qword ptr [rax+0x78],0` | desc+0x78 = 0 (member vector node, zeroed here) |
Notes: +0x60 and +0x70 are NOT written by sub_1188250. +0x60=0xD4C25870 and +0x68/+0x70/+0x78 non-null are set by later registration/clone (sub_1d4fd0 moves them; original fill site not yet statically located). Init-gating: sub_1188250 is reached only after [0x128E48F8] init-once (0x1188258/0x118827d) and sub_1188400 sets up the hash globals (0x1188425..0x1188454).

## (2) sub_11884a0 (desc+0x30 callback) — [V], oc_U-EM2c_11884a0.txt, range 0x11884a0..0x1188521
Arg map: rcx=desc-ish object (->rsi), rdx=other (->rdi).
- 0x11884b4 `mov [rcx+0x10],rax` : +0x10 = 0x1188560 (copy ctor ptr)
- 0x11884b8 `mov dword ptr [rcx+0x20],0x8DE632ED` : +0x20 = type/state tag 0x8DE632ED
- 0x11884c6 `mov [rcx+0x18],rax` : +0x18 = 0x11886D0 (dtor ptr)
- 0x11884ca `mov byte ptr [rcx+0x24],1` : +0x24 = byte 1
- 0x11884ce rcx=[0x1233E1A8] registry; rax=[rcx]; rax=[rax+8]; edx=0x14; `call qword ptr [0xF99FFA0]` (sub_eea6040) alloc 0x14 bytes -> rax = new object
- 0x11884ec `mov dword ptr [rax+0x10],0x101` ; newobj+0x10 = 0x101
- 0x11884f3 `movaps xmm0,[0xF0CD370]` (sub_1800000); `movaps [rax],xmm0` ; newobj+0x0 = vtable-ish
- 0x11884fd `mov [rsi],rax` : object(rsi=desc)+0x0 = new object pointer
- 0x1188500 `mov [rsi+0x28],rdi` : +0x28 = rdi
- 0x1188504 `mov qword ptr [rsi+0x30],0` : +0x30 = 0
- 0x1188513 `mov [rsi+0x38],rax` where rax=lea [0x1188540] : +0x38 = callback 0x1188540
- return rax (new object). On alloc failure (0x1188522): alloc 0x14 via sub_9bc830 then retry.
Note: when invoked as the desc+0x30 callback it overwrites +0x28 with rdi; called from sub_1d4fd0 path and sub_1188560 (entry copy).

## (2b) sub_11886f0 (desc+0x40 callback) — builds ONE member entry at rax — [V], oc_U-EM2c_11886f0.txt, range 0x11886f0..0x1188771
Arg map: rax=rcx=entry pointer (this); rdx=offset; r8=name ptr candidate A; r9=name ptr candidate B. Branches on (r8==0)||(r9==0).
- 0x118870c `mov [rax+0x10],rcx` rcx=lea [0x1188560] : entry+0x10 = copy ctor 0x1188560 (both branches, e.g. 0x118870c/0x1188732/0x11883fa-path via sub_1188560)
- `mov dword ptr [rax+0x20],0x8DE632ED` (0x1188710 / 0x1188736) : entry+0x20 = type tag 0x8DE632ED
- `mov [rax+0x18],rcx` rcx=lea [0x11886D0] (0x118871e) : entry+0x18 = dtor 0x11886D0 (branch where r8/r9 not both zero)
- `mov qword ptr [rax+0x18],0` (0x118873d) : entry+0x18 = 0 (branch r8==0&&r9==0)
- `mov byte ptr [rax+0x24],1` (0x1188722) : entry+0x24 = 1 (name null)
- `mov [rax],r8` (0x1188726) : entry+0x00 = name = r8 (r8!=0 branch) ; `mov byte ptr [rax+0x24],3` (0x118874a)
- `mov [rax],r9` (0x1188757) : entry+0x00 = name = r9 (r8==0,r9!=0 branch) ; `mov byte ptr [rax+0x24],4` (0x1188753)
- 0x118875a `mov [rax+0x28],rdx` : entry+0x28 = offset = rdx (qword)
- 0x118875e `mov qword ptr [rax+0x30],0` : entry+0x30 = 0
- 0x118876d `mov [rax+0x38],rcx` rcx=lea [0x1188540] : entry+0x38 = callback 0x1188540
Entry field span: +0x00..+0x38 inclusive (8 bytes at +0x38) => entry size/stride S = 0x40 ([I] inferred from field span; vector append/push_back stride not yet observed statically — no direct code xref to sub_11886f0, it is invoked via the desc+0x40 callback pointer).
Member entry layout (from sub_11886f0):
| field | entry offset | size | source | tag |
| name (char* / std::string ptr) | +0x00 | qword | r8 or r9 | [V] |
| copy ctor ptr | +0x10 | qword | 0x1188560 | [V] |
| dtor ptr | +0x18 | qword | 0x11886D0 or 0 | [V] |
| type tag | +0x20 | dword | imm 0x8DE632ED | [V] |
| name-kind byte | +0x24 | byte | 1/3/4 | [V] |
| offset | +0x28 | qword | rdx | [V] (store is qword; holds member struct offset) |
| zero | +0x30 | qword | 0 | [V] |
| callback ptr | +0x38 | qword | 0x1188540 | [V] |

## (2c) Member container path from descriptor — [V] (orchestrator live) + partial static
Descriptor +0x78 holds a node object: node+0x48 = members begin pointer, node+0x50 = members end pointer. So:
members = [ [desc+0x78] + 0x48 .. [desc+0x78] + 0x50 ), stride S.
Static corroboration: sub_1d6350 (oc_U-EM2c_1d6350.txt) at 0x1d63a5/0x1d63c0 walks `[rax+0x78]+0x48` array comparing entry+0x00 and advancing `add rax,0x68` — a 0x68-stride array at +0x78/+0x48 exists elsewhere (type registry buckets), NOT confirmed to be the desc+0x78 member vector; desc+0x78 member-vector stride S is separate.

## (3) sub_1d4fd0 — central registration / descriptor clone — [V], oc_U-EM2c_1d4fd0.txt
Called by sub_1188780 (0x11887e4 `call 0x1D4FD0`) and 10115 other sites. Args: rcx=src desc-like, rdx=type-info, r8=?, r9d=hash tag.
- 0x1d4ff2 `mov [rcx],rdx` ; dst+0x0 = rdx
- 0x1d4ff8 `movups [rcx+8],xmm0` ; dst+0x8 = 0
- 0x1d4ffc `mov qword ptr [rcx+0x18],0` ; dst+0x18 = 0
- 0x1d5004 rax=[rdx]; 0x1d5007 rcx=[rdx+8]; computes bucket idx = ((([rdx+8]-[rdx])>>3)-1)&r9d ; 0x1d5017 `lea rcx,[rax+rcx*8]` bucket walk
- 0x1d5020..0x1d5036 walks bucket table *(rdx+0x20) stride 0x18 (`lea rdx,[rcx+rcx*2]` = idx*3; `lea rcx,[rax+rdx*8]` = idx*24) comparing [entry+8]==r9d
- 0x1d5038 `lea rax,[rax+rdx*8]`; 0x1d503c `cmp [rdi+0x28],rax`; 0x1d5042 `mov rax,[rax+0x10]`; 0x1d5046 `mov [rsi+0x10],rax` : resolves existing entry
- Alloc path (0x1d504f): `mov edx,0x80; call sub_eea6040` alloc 0x80 bytes -> rbx = clone object
- 0x1d5079..0x1d50d4 copies src([rbp-0x10]) 0x80 bytes into clone rbx:
  - movups [rbx+0x50]=[src+0x50] (0x1d507d); [rbx+0x40]=[src+0x40] (0x1d5089)
  - movups [rbx+0x30]=[src+0x30] (0x1d509c); [rbx+0x20]=[src+0x20] (0x1d50a0); [rbx+0x10]=[src+0x10] (0x1d50a4); [rbx+0x00]=[src+0x00] (0x1d50a8)
  - 0x1d50ab `mov eax,[rcx+0x60]`; `mov [rbx+0x60],eax` : clone+0x60 = src+0x60 (0xD4C25870) [V]
  - 0x1d50b1 `mov rax,[rcx+0x68]`; `mov [rbx+0x68],rax` : clone+0x68 = src+0x68 (node) [V]
  - 0x1d50b9 `mov rax,[rcx+0x70]`; `mov [rbx+0x70],rax` : clone+0x70 = src+0x70 (shared_ptr ctl) [V]
  - 0x1d50c4 `movups [rcx+0x68],xmm0` : src+0x68 = 0 (moved out)
  - 0x1d50c8 `mov rax,[rcx+0x78]`; `mov qword ptr [rcx+0x78],0` ; `mov [rbx+0x78],rax` : clone+0x78 = src+0x78 (member vector node), src+0x78=0 (moved out) [V]
- Then sub_1d5350 inserts into bucket table *(rdi+0x28) with 0x18-stride entries {+0x0 value,+0x8 hash,+0x10 next}.
- 0x1d5165..: allocates another 0x78 object (rdi), zeroes +0x00..+0x70, sets [rdi+0x70]=0, then `mov rbx,[rax+0x78]` where rax=[rsi+0x10]; `mov [rax+0x78],rdi` — links the 0x78 node into +0x78 chain.
- 0x1d51de `mov [rcx+8],eax` (eax=[rbp-4]=hash tag) : stores tag at object+8.

## sub_1188780 — registration wrapper (single caller sub_1152460+0x7b0a per xref; call site itself not cleanly re-disambiguated) — [V]
- 0x11887b6 `mov dword ptr [rcx],0x8DE632ED` ; obj+0x0 = tag
- 0x11887bc `mov [rcx+8],rdx` ; obj+0x8 = rdx
- 0x11887c0 `lea rdi,[rcx+0x10]` ; rdi = obj+0x10 (desc being built)
- 0x11887c4 `add rbx,0x18` ; rbx += 0x18
- 0x11887cc `mov rcx,r15`; `call 0x1188250` : build descriptor at r15 (via sub_1188250) into obj+0x10
- 0x11887d5 `mov rcx,rdi`; `mov rdx,rbx`; `mov r8,r15`; `mov r9d,0x8DE632ED`; `call 0x1D4FD0` : register
- 0x11887ea `mov dword ptr [rsi+0x30],0`; 0x11887f1 `mov eax,[rsi]`; `mov [rsi+0x34],eax`; 0x11887f6 `mov word ptr [rsi+0x38],0`

## Sibling type-inits (CloudParameters / ShadowParameters / ShadowRange) — part (3)
Sibling hash globals in the 0x128E48xx range observed: sub_1188170 (desc+0x28 callback) uses [0x128E48D8] and [0x128E4858]; sub_1188250 uses [0x128E48F8]; sub_1188400 (CloudLightingParameters) uses [0x128E4900]/[0x128E48FC]/[0x128E48E0]/[0x128E48E8]/[0x128E48F0]. The plain names "CloudParameters]"/"ShadowParameters]"/"ShadowRange]" have NO string xref; RTTI strings appear as entt pretty_function templates (f641675 "mce::f...", f641005, f616f66 Shadow..., f67b699) with no code refs. Functions in 0x1188000..0x1189000 sharing the 0x8DE632ED descriptor pattern (imm search): sub_1188fe0, sub_1189390, sub_11892d0, sub_1189500, sub_1189560, sub_118a020, sub_118a220, sub_118f6b0, sub_118f8c0, sub_118faf0 — all reference [0x1233E1A8] registry and allocate 0x14-byte objects storing [+0x28]=rdi,[+0x30]=0,[+0x38]=0x1188540, i.e. the same 3-callback shape. Specific split of which global/RTTI/sizeof belongs to CloudParameters vs ShadowParameters vs ShadowRange was NOT located statically (no per-type hash global or RTTI name string found for them). [I] they reuse the identical sub_1188250/sub_11884a0/sub_11886f0 machinery, so the same recipe/path applies to each once its descriptor is located.

## RECIPE (one line)
"read qword [exe+0x1233E1A8] -> registry object; walk registry to the reflected type descriptor (CloudLightingParameters desc found by scanning for &[exe+0x128E48E0]); members = [desc+0x78] +0x48 begin .. +0x50 end, stride S=0x40; name at +0x00 (char* ptr), offset at +0x28 (qword store; u32 member offset), type tag at +0x20 (u32 imm 0x8DE632ED)."

Note on the "[exe+RVA] -> descriptor" direct-deref form: no single global was observed to point straight at the descriptor; sub_1188250 stores desc+0x00 = &global 0x128E48E0, and the descriptor itself is a heap object located by scanning for &[exe+0x128E48E0] (orchestrator live). The registry [exe+0x1233E1A8] is the allocation root.

## VERBATIM PROOF LINES (0xRVA  instr)
`0x118829c  mov ecx,[0x128E48E4]`
`0x11882a2  lea rdx,[0x128E48E0]`
`0x11882a9  mov [rax],rdx`
`0x11882ac  mov [rax+8],ecx`
`0x11882af  mov qword ptr [rax+0x10],0`
`0x11882b7  mov dword ptr [rax+0x18],0x80`
`0x11882be  mov qword ptr [rax+0x20],0x14`
`0x11882c6  lea rcx,[0x1188170]`
`0x11882cd  mov [rax+0x28],rcx`
`0x11882d1  lea rcx,[0x11884A0]`
`0x11882d8  mov [rax+0x30],rcx`
`0x11882dc  mov qword ptr [rax+0x38],0`
`0x11882e4  lea rcx,[0x11886F0]`
`0x11882eb  mov [rax+0x40],rcx`
`0x11882f2  movups [rax+0x48],xmm0`
`0x11882f6  movups [rax+0x54],xmm0`
`0x11882fa  movups [rax+0x68],xmm0`
`0x11882fe  mov qword ptr [rax+0x78],0`
`0x118842b  mov [0x128E48E0],eax`
`0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED`
`0x1188442  mov [0x128E48E8],rax`
`0x1188449  mov qword ptr [0x128E48F0],0x2A`
`0x11884b4  mov [rcx+0x10],rax`
`0x11884b8  mov dword ptr [rcx+0x20],0x8DE632ED`
`0x11884c6  mov [rcx+0x18],rax`
`0x11884ca  mov byte ptr [rcx+0x24],1`
`0x11884e1  call qword ptr [0xF99FFA0]`
`0x11884ec  mov dword ptr [rax+0x10],0x101`
`0x11884f3  movaps xmm0,[0xF0CD370]`
`0x11884fa  movaps [rax],xmm0`
`0x11884fd  mov [rsi],rax`
`0x1188500  mov [rsi+0x28],rdi`
`0x1188504  mov qword ptr [rsi+0x30],0`
`0x1188513  mov [rsi+0x38],rax`
`0x118852a  call 0x9BC830`
`0x1188549  mov rcx,[rdx+0x28]`
`0x1188550  call 0x1188170`
`0x1188555  mov [rsi+0x30],rax`
`0x118870c  mov [rax+0x10],rcx`
`0x1188710  mov dword ptr [rax+0x20],0x8DE632ED`
`0x118871e  mov [rax+0x18],rcx`
`0x1188722  mov byte ptr [rax+0x24],1`
`0x1188726  mov [rax],r8`
`0x118873d  mov qword ptr [rax+0x18],0`
`0x118874a  mov byte ptr [rax+0x24],3`
`0x118874e  mov [rax],r8`
`0x1188753  mov byte ptr [rax+0x24],4`
`0x1188757  mov [rax],r9`
`0x118875a  mov [rax+0x28],rdx`
`0x118875e  mov qword ptr [rax+0x30],0`
`0x118876d  mov [rax+0x38],rcx`
`0x1d4ff2  mov [rcx],rdx`
`0x1d50ab  mov eax,[rcx+0x60]`
`0x1d50ae  mov [rbx+0x60],eax`
`0x1d50b1  mov rax,[rcx+0x68]`
`0x1d50b5  mov [rbx+0x68],rax`
`0x1d50b9  mov rax,[rcx+0x70]`
`0x1d50bd  mov [rbx+0x70],rax`
`0x1d50c4  movups [rcx+0x68],xmm0`
`0x1d50c8  mov rax,[rcx+0x78]`
`0x1d50cc  mov qword ptr [rcx+0x78],0`
`0x1d50d4  mov [rbx+0x78],rax`
`0x1d50eb  call 0x1D5350`
`0x1d5165  mov rcx,[0x1233E1A8]`
`0x1d5178  call qword ptr [0xF99FFA0]`
`0x1d51b1  mov rax,[rsi+0x10]`
`0x1d51b5  mov rbx,[rax+0x78]`
`0x1d51b9  mov [rax+0x78],rdi`
`0x1d51de  mov [rcx+8],eax`
`0x1d63a5  mov rax,[rax+0x48]`
`0x1d63a9  cmp [rax],r8d`
`0x1d63ae  add rax,0x68`

## CLOSES?
NO — single blocking fact: member-table stride S=0x40 is inferred [I] from sub_11886f0's entry field span (highest written field +0x38 => 0x40 bytes) but the vector append/push_back site that would confirm stride [V] was not located (no direct code xref to sub_11886f0; invoked via desc+0x40 callback). Also not [V]: a direct "[exe+RVA] -> descriptor" global deref (descriptor reached via registry scan / &[exe+0x128E48E0]), and the static setters for desc+0x60/desc+0x70 (desc+0x68/+0x78 moved by sub_1d4fd0). All member-entry field offsets (name +0x00, type +0x20, offset +0x28) and descriptor field stores are [V]. Once stride S is confirmed [V] (e.g. by observing the vector element advance or computing (end-begin)/count live = 0x14 members), the recipe is complete.

## FILES
- docs/progress/oc_U-EM2c.md (this result file)
- docs/progress/oc_U-EM2c_1188250.txt, oc_U-EM2c_11884a0.txt, oc_U-EM2c_11886f0.txt, oc_U-EM2c_1188400.txt, oc_U-EM2c_1d4fd0.txt, oc_U-EM2c_1d6350.txt, oc_U-EM2c_1d5350.txt, oc_U-EM2c_1189560.txt, oc_U-EM2c_1188fe0.txt, oc_U-EM2c_1189390.txt, oc_U-EM2c_1159EE0.txt, oc_U-EM2c_range_1188000_1189000.lst, oc_U-EM2c_xref_*.txt (working disassembly/xref dumps under docs/progress/)
