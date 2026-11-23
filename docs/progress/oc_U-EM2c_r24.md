## NEXT
DONE

# U-EM2c — reflected type member-table recipe (CloudLightingParameters; CloudParameters/ShadowParameters/ShadowRange same 3-callback shape)

GOAL (this run): [V] instruction rows + the one-line CE recipe:
  "read qword [exe+RVA] -> descriptor; members = [desc+Xbegin..desc+Xend) stride S; name at +a (std::string), offset at +b (u32), type at +c".
Static analysis only (rdis.exe on Minecraft.Windows.exe 1.26.62.01, RVAs image-relative). Every quoted `0xRVA  instr` line is verbatim from `rdis ... dis` output (see verify tags). `a0` = the object pointer passed in rcx to callback 2 (sub_11884a0) / callback 3 (sub_11886f0); `desc` = the type descriptor built by sub_1188250; `cb2`/`cb3` = the objects those callbacks initialize (a0 in each).

## Type-level globals (set by the per-type sub_1188400-style initializer, CloudLightingParameters = 0x1188400)

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| [0x128E48E0] | 4 | W | `0x118842b  mov [0x128E48E0],eax` | type id counter stored here; eax = [0x128E48FC] (next id) [V] |
| [0x128E48E4] | 4 | W | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash = 0x8DE632ED [V] |
| [0x128E48E8] | 8 | W | `0x118843b  lea rax,[0xF6416AB]`; `0x1188442  mov [0x128E48E8],rax` | RTTI name ptr = "mce::framebuilder::CloudLightingParameters]" [V] |
| [0x128E48F0] | 8 | W | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof = 0x2A [V] |
| [0x128E48F8] | 4 | R | `0x1188404  mov eax,[0x128E4900]`; `0x1188258  mov ecx,[0x128E48F8]` | init guard/counter [V] |
| [0x1233E1A8] | 8 | R | `0x11884ce  mov rcx,[0x1233E1A8]` | registry object (heap/data); [rcx]->[rax+8] = allocator fn slot, called via `0x11884e1  call qword ptr [0xF99FFA0]` = sub_eea6040 [V] |

## Descriptor stores (desc+0x00..+0x78) — sub_1188250 builder plus sub_1d4fd0 registration; all sites merged, all verified [V]

sub_1188250(rcx=desc) zero-inits every field in desc+0x38..+0x80. It performs NO alloc/ctor calls and stores NO non-zero value at +0x60/+0x68/+0x70/+0x78; those fields are zero here and filled later at registration time. sub_1d4fd0 (called from `0x11887e4  call 0x1D4FD0` in sub_1188780) copies desc+0x60/+0x68/+0x70/+0x78 into a registration block and zeroes them on desc.

| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| desc+0x00 | 8 | W | `0x11882a9  mov [rax],rdx` (rdx = `0x11882a2  lea rdx,[0x128E48E0]`) | desc+0x00 = &global 0x128E48E0 (type-handle global; live: scan memory for this pointer to find desc) [V] |
| desc+0x08 | 8 | W | `0x11882ac  mov [rax+8],ecx` (ecx = `0x118829c  mov ecx,[0x128E48E4]`) | desc+0x08 = type hash [V] |
| desc+0x10 | 8 | W | `0x11882af  mov qword ptr [rax+0x10],0` | desc+0x10 = 0 [V] |
| desc+0x18 | 4 | W | `0x11882b7  mov dword ptr [rax+0x18],0x80` | desc+0x18 = flags 0x80 [V] |
| desc+0x20 | 8 | W | `0x11882be  mov qword ptr [rax+0x20],0x14` | desc+0x20 = member count 0x14 (20) [V] |
| desc+0x28 | 8 | W | `0x11882cd  mov [rax+0x28],rcx` (rcx = `0x11882c6  lea rcx,[0x1188170]`) | desc+0x28 = callback 1 = sub_1188170 [V] |
| desc+0x30 | 8 | W | `0x11882d8  mov [rax+0x30],rcx` (rcx = `0x11882d1  lea rcx,[0x11884A0]`) | desc+0x30 = callback 2 = sub_11884a0 [V] |
| desc+0x38 | 8 | W | `0x11882dc  mov qword ptr [rax+0x38],0` | desc+0x38 = 0 [V] |
| desc+0x40 | 8 | W | `0x11882eb  mov [rax+0x40],rcx` (rcx = `0x11882e4  lea rcx,[0x11886F0]`) | desc+0x40 = callback 3 = sub_11886f0 [V] |
| desc+0x48 | 16 | W | `0x11882f2  movups [rax+0x48],xmm0` | desc+0x48..+0x57 = 0 [V] |
| desc+0x54 | 16 | W | `0x11882f6  movups [rax+0x54],xmm0` | desc+0x54..+0x63 = 0 (covers desc+0x60) [V] |
| desc+0x60 | 16 | W,R | `0x11882f6  movups [rax+0x54],xmm0` zero (builder); `0x1d50ab  mov eax,[rcx+0x60]` read; `0x1d50ae  mov [rbx+0x60],eax` copy to reg block | desc+0x60 = 0 at end of builder; live value 0xD4C25870 (u32) is written later, no static store found [?] |
| desc+0x68 | 16 | W,R | `0x11882fa  movups [rax+0x68],xmm0` zero (builder, covers +0x68..+0x77); `0x1d50b1  mov rax,[rcx+0x68]` read; `0x1d50b5  mov [rbx+0x68],rax` copy to reg block; `0x1d50c4  movups [rcx+0x68],xmm0` zero desc+0x68/+0x70 on desc | desc+0x68 moved into reg block, then zeroed on desc [V] |
| desc+0x70 | 16 | W,R | `0x1d50b9  mov rax,[rcx+0x70]` read; `0x1d50bd  mov [rbx+0x70],rax` copy to reg block; zeroed by `0x1d50c4  movups [rcx+0x68],xmm0` (16 bytes covers +0x68..+0x77) and builder `0x11882fa` | desc+0x70 moved into reg block, then zeroed on desc [V] |
| desc+0x78 | 8 | W,R | `0x11882fe  mov qword ptr [rax+0x78],0` zero (builder); `0x1d50c8  mov rax,[rcx+0x78]` read; `0x1d50cc  mov qword ptr [rcx+0x78],0` zero on desc; `0x1d50d4  mov [rbx+0x78],rax` move to reg block | desc+0x78 moved into reg block, then zeroed on desc [V] |
| alloc-0x80 | - | - | `0x1d5061  mov edx,0x80`; `0x1d5066  call qword ptr [0xF99FFA0]` (sub_eea6040) | sub_1d4fd0 allocates a 0x80-byte registration block [V] |
| alloc-0x78 | - | - | `0x1d5173  mov edx,0x78`; `0x1d5178  call qword ptr [0xF99FFA0]` (sub_eea6040); new block zeroed `0x1d518e  movups [rdi+0x60],xmm0` ... `0x1d51a6  movups [rdi],xmm0` (rdi+0x0..+0x67) and `0x1d51a9  mov qword ptr [rdi+0x70],0`; linked `0x1d51b5  mov rbx,[rax+0x78]`; `0x1d51b9  mov [rax+0x78],rdi` ([ [rsi+0x10] + 0x78 ] = container) | sub_1d4fd0 allocates a 0x78-byte container block [V] |
| alloc-0xE0/0x10 | - | - | `0x1188b58  mov edx,0xE0`; `0x1188b5d  call qword ptr [0xF99FFA0]`; `0x1188ad7  mov edx,0x10`; `0x1188adc  call qword ptr [0xF99FFA0]` | sub_1188780 allocates 0xE0 and 0x10-byte blocks for the per-type registration record [V] |

## Callback 2 (desc+0x30 = sub_11884a0) and callback 3 (desc+0x40 = sub_11886f0) — object a0 (rcx) layout, all stores verified [V]

sub_11884a0(rcx=a0, rdx=arg2):
| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| cb2+0x00 | 8 | W | `0x11884fd  mov [rsi],rax` (rsi=a0; rax = result of `0x11884e1  call qword ptr [0xF99FFA0]` sub_eea6040(rcx=[0x1233E1A8], rax=[[rcx]+8], edx=0x14=20 entries)) | cb2+0x00 = alloc block for 20 entries; call site `0x11884e1` [V] |
| cb2+0x10 | 8 | W | `0x11884b4  mov [rcx+0x10],rax` (rax = `0x11884ad  lea rax,[0x1188560]`) | cb2+0x10 = &sub_1188560 (copy/compare fn) [V] |
| cb2+0x18 | 8 | W | `0x11884c6  mov [rcx+0x18],rax` (rax = `0x11884bf  lea rax,[0x11886D0]`) | cb2+0x18 = &sub_11886d0 (dtor/release fn) [V] |
| cb2+0x20 | 4 | W | `0x11884b8  mov dword ptr [rcx+0x20],0x8DE632ED` | cb2+0x20 = type tag hash 0x8DE632ED [V] |
| cb2+0x24 | 1 | W | `0x11884ca  mov byte ptr [rcx+0x24],1` | cb2+0x24 = kind byte 1 [V] |
| cb2+0x28 | 8 | W | `0x1188500  mov [rsi+0x28],rdi` (rdi = arg2, saved `0x11884a7  mov rdi,rdx`) | cb2+0x28 = arg2 [V] |
| cb2+0x30 | 8 | W | `0x1188504  mov qword ptr [rsi+0x30],0` | cb2+0x30 = 0 [V] |
| cb2+0x38 | 8 | W | `0x1188513  mov [rsi+0x38],rax` (rax = `0x118850c  lea rax,[0x1188540]`) | cb2+0x38 = &sub_1188540 [V] |

sub_11886f0(rcx=a0, r8, r9, rdx): branches on (r8==0 && r9==0):
| offset | size | site | instr | meaning [tag] |
|---|---|---|---|---|
| cb3+0x00 | 8 | W | `0x1188726  mov [rax],r8` (r8!=0 path); `0x118874e  mov [rax],r8` (both-zero path, r8==0 so stores 0); `0x1188757  mov [rax],r9` (r8==0, r9!=0 path) | cb3+0x00 = name pointer: char* r8, else char* r9, else 0 (std::string is NOT used — raw char* ptr) [V] |
| cb3+0x24 | 1 | W | `0x1188722  mov byte ptr [rax+0x24],1` (both-zero); `0x118874a  mov byte ptr [rax+0x24],3` (r8!=0); `0x1188753  mov byte ptr [rax+0x24],4` (r8==0, r9!=0) | cb3+0x24 = kind byte: 1 no name / 3 r8 name / 4 r9 name [V] |
| cb3+0x10 | 8 | W | `0x118870c  mov [rax+0x10],rcx`; `0x1188732  mov [rax+0x10],rcx` (rcx = `lea [0x1188560]`) | cb3+0x10 = &sub_1188560 [V] |
| cb3+0x18 | 8 | W | `0x118871e  mov [rax+0x18],rcx` (rcx = `&sub_11886d0`, both-zero path); `0x118873d  mov qword ptr [rax+0x18],0` (else path) | cb3+0x18 = &sub_11886d0 or 0 [V] |
| cb3+0x20 | 4 | W | `0x1188710  mov dword ptr [rax+0x20],0x8DE632ED`; `0x1188736  mov dword ptr [rax+0x20],0x8DE632ED` | cb3+0x20 = type tag hash 0x8DE632ED [V] |
| cb3+0x28 | 8 | W | `0x118875a  mov [rax+0x28],rdx` | cb3+0x28 = rdx = member offset (u32 stored as qword) [V] |
| cb3+0x30 | 8 | W | `0x118875e  mov qword ptr [rax+0x30],0` | cb3+0x30 = 0 [V] |
| cb3+0x38 | 8 | W | `0x118876d  mov [rax+0x38],rcx` (rcx = `0x1188766  lea rcx,[0x1188540]`) | cb3+0x38 = &sub_1188540 [V] |

sub_1188540(rdx, ecx): `0x1188549  mov rcx,[rdx+0x28]`; `0x1188550  call 0x1188170`; `0x1188555  mov [rsi+0x30],rax` — lookup helper, result stored at cb2/cb3+0x30 [V].
sub_1188170(rcx=desc): hash-table lookup over [rcx+0x0]/[rcx+0x8] array using edx=[0x128E4858+4]; reads [rcx+0x20], [rcx+0x28]; returns [match+0x10] (`0x11881f2  mov rax,[rdx+0x10]`) [V].

Reachability from descriptor: sub_1188250 zeroes desc+0x68/+0x70/+0x78 (descriptor table); sub_1d4fd0 moves them into a registration block and zeroes them on desc (descriptor table); the driver that (re)fills desc+0x68/+0x70/+0x78 from the callback-built objects is invoked INDIRECTLY through desc+0x30/desc+0x40 — no static code xrefs to sub_11884a0 or sub_11886f0 exist (`xr_11884a0.txt`/`xr_11886f0.txt` empty). Live (orchestrator CE): desc+0x68 -> node (+0x00 ptr, +0x30 = 0xF), desc+0x70 -> shared_ptr-like control block (vtable exe+0xF0DFBA0), desc+0x78 -> member container (+0x48/+0x50 = begin/end pointers 0x22FC607E9A0/...) [V live]. The stores that write desc+0x60 (live 0xD4C25870), desc+0x68, desc+0x70, desc+0x78 with their final object pointers are not statically located [?].

Entry layout (from sub_11886f0 stores, the per-member initializer): last store is at +0x38 (qword) -> entry span = 0x40 bytes; fields: name char* at +0x00, type tag u32 hash at +0x20, kind u8 at +0x24, offset u32 (qword store) at +0x28, copy fn at +0x10, dtor at +0x18, lookup fn at +0x38 [V]. No pointer arithmetic (no push_back/emplace stride computation) exists in sub_11886f0 — it is a pure entry initializer; the task's premise that sub_11886f0 contains the push_back is contradicted by the disassembly [V].

Container stride evidence (sub_1d6350, called from `0x1188cad  call 0x1D6350` in sub_1188780 with rcx=a0): array base = `0x1d63a5  mov rax,[rax+0x48]` where [rcx+0x10]->+0x78 = the container; iteration `0x1d63ae  add rax,0x68` (stride 0x68 for THAT array); elements get `0x1d63cf  mov [rax+0x50],ecx` (dword) and `0x1d63e1  movups [rax+0x58],xmm0` (16 bytes). This stride-0x68 array holds {dword key, ..., dword, 16B} uniform-slot entries — it is NOT the reflection member vector (no name pointer), so it does not give the member-entry stride [V].

## Sibling types CloudParameters / ShadowParameters / ShadowRange

RTTI name strings located [V] (xref str, refs=[] — no code xrefs recorded):
- "mce::framebuilder::CloudParameters]" at data 0xF6419FD — only code ref found by ripscan: 0xEE3F545 (func ee3f460, unrelated animation code; incidental) [V]
- "mce::framebuilder::ShadowParameters]" at data 0xF641005 — 0 code refs [V]
- "mce::framebuilder::ShadowRange]" at data 0xF67B699 — 0 code refs [V]

Their type-init functions (the ones that store a hash to a [0x128E48xx]-style global, the RTTI name ptr, and a sizeof, then build the descriptor via sub_1188250-equivalent and register via sub_1d4fd0) were NOT statically located: they are not adjacent to sub_1188400/sub_1188250 in the address space (the 0x1188000..0x1189000 neighborhood contains only CloudLightingParameters machinery: sub_1188170/1188250/1188390/1188400/11884a0/1188540/1188560/11886d0/11886f0/1188780/1188f00), and none of the RTTI strings above is referenced by a type-init [V]. Callers of sub_1d4fd0 exist across .text (5389 xrefs, incl. `0x1188780 0x656`) but none in 0x1188xxx-0x1189xxx other than sub_1188780 [V]. Sibling global/descriptor rows: [?] init functions not found.

## Recipe (one line, for the orchestrator's CE dump)

No static `read qword [exe+RVA] -> descriptor` qword exists; desc+0x00 stores &global 0x128E48E0 (`0x11882a9  mov [rax],rdx`, rdx=`0x11882a2  lea rdx,[0x128E48E0]`), so find desc by scanning memory for qword == image_base + 0x128E48E0 [V + V live], then:
  members = [desc+0x78] -> +0x48 begin .. +0x50 end, count at desc+0x20 = 0x14 [V]; stride S = 0x40 [I] (entry span from sub_11886f0 stores through +0x38; push_back pointer arithmetic not statically located); entry fields: name char* at +0x00 [V], offset u32 at +0x28 [V], type tag u32 hash at +0x20 [V]. Container begin/end offsets +0x48/+0x50 on desc+0x78's container: [V live] (code-corroborated only on the homologous sub_1d6350 container object: array base at container+0x48 `0x1d63a5  mov rax,[rax+0x48]`).

## CLOSES?

NO — single blocking fact: the member-vector entry stride S / push_back code is not statically located. sub_11886f0 (the claimed push_back location) contains no pointer arithmetic — it only initializes one 0x40-byte member entry (name char* +0x00, type tag +0x20, offset +0x28 [V]); the callbacks are invoked indirectly through desc+0x30/+0x40 with no static callers, and the stores filling desc+0x60 (live 0xD4C25870), desc+0x68, desc+0x70, desc+0x78 with final object pointers are not found statically [?]. Stride can only be given as [I] = 0x40 (entry span), not [V]. Every other RVA/offset in the recipe is [V] (container +0x48/+0x50 is [V live]).

## What changed

Created: docs/progress/oc_U-EM2c.md (this file). No other file created or edited.

## TOOL REQUESTS

rdis `imm <value>` returned 0 hits for 0x1188170/0x11884a0/0x11886f0 even though `lea rcx,[0x1188170]` and similar exist in sub_1188250 — the imm scanner appears to miss lea immediates; a general `lea <imm>` scan over .text would have helped find sibling type-inits that reuse these callbacks. Done by hand instead: reading dis files + ripscan of RTTI strings.
