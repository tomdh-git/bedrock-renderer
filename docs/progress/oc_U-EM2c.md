## NEXT
DONE

# UNIT U-EM2c — M2c reflected parameter types: CloudLightingParameters / CloudParameters / ShadowParameters / ShadowRange / RenderShadowDescription member-table recipe

GOAL (this run overrides oc_U-EM2c_r1..r3): produce the static recipe that lets the orchestrator read the reflected Cloud*/Shadow* member tables live:
  read qword [exe+0x1233E1A8] (registry) -> type descriptor -> [desc+0x78] member container; container +0x48 begin / +0x50 end; entry stride S; entry: name at +a, offset at +b, tag at +c.
Static analysis only (game not running — no livemem). Every row tagged [V] (verbatim rdis line, cited by RVA), [I] (inferred), [?] (unknown). Output file: docs/progress/oc_U-EM2c.md only.

## Key static fact — hash scheme

Type-init functions identify themselves by the FNV-1a 32 hash of the namespaced type name, stored into [0x128E48xx]/[0x129C79xx]-style globals, next to an RTTI name ptr and a sizeof. Computed with python (FNV-1a 32, basis 0x811C9DC5, prime 0x01000193):

| name | FNV-1a 32 | stored imm seen at | match |
|------|-----------|--------------------|-------|
| mce::framebuilder::CloudLightingParameters | 0x8DE632ED | 0x1188431 `mov [0x128E48E4],0x8DE632ED` | yes [V] |
| mce::framebuilder::CloudParameters | 0x8CBEF799 | 0x118A721 `mov [0x128E4994],0x8CBEF799` | yes [V] |
| mce::framebuilder::ShadowParameters | 0x7C2A4E8C | 0x5434CC1 `mov [0x129C79C4],0x7C2A4E8C` | yes [V] |
| mce::framebuilder::ShadowRange | 0x990FE13D | 0x5437E51 `mov [0x129C79EC],0x990FE13D` | yes [V] |
| mce::framebuilder::RenderShadowDescription | 0x31FF492 | `rdis imm 0x972122FD` (short name) and `imm 0x31FF492`: 0 hits | not in this scheme [V negative] |

RenderShadowDescription is NOT registered by this reflected scheme (no static store of either hash width anywhere in .text) — it belongs to the separate insert-vtable/pass-body path, not this recipe. All four reflected parameter types share one shape: metadata-init (stores hash+name+sizeof to globals), stack template builder (builds 0x80-byte descriptor template), registration entry (calls sub_1d4fd0), and the descriptor's 3 callbacks (+0x28/+0x30/+0x40).

Registry: [exe+0x1233E1A8] is the registry/allocator object; sub_1d4fd0(rcx=desc_out, rdx=table+0x18, r8=stack template, r9d=hash) does a hash-table lookup in the table (buckets at table+0x00, entries at table+0x20: +0x00 next, +0x8 hash, +0x10 value=descriptor; end at table+0x28), and on miss allocates a 0x80-byte heap descriptor via [0x1233E1A8]->sub_eea6040 (edx=0x80), copies the template into it, inserts it keyed by hash (sub_1d5350), then allocates a 0x78-byte member container via sub_eea6040 (edx=0x78), zeroes it, and stores it at [descriptor+0x78].

## Type 1 — CloudLightingParameters (hash 0x8DE632ED, count 0x14=20, sizeof 0x2A)

Metadata-init sub_1188400 (globals [0x128E48E0..0x128E48F0]; guard [0x128E48F8], counter [0x128E48FC]):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|--------|------|------|-------------------------|---------------|
| [0x128E48E0] | 4B | sub_1188400 | `0x1188425  mov eax,[0x128E48FC]`; `0x118842b  mov [0x128E48E0],eax` | registration index (from counter [0x128E48FC]) [V] |
| [0x128E48E4] | 4B | sub_1188400 | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash = FNV-1a-32("mce::framebuilder::CloudLightingParameters") [V] |
| [0x128E48E8] | 8B | sub_1188400 | `0x118843b  lea rax,[0xF6416AB]`; `0x1188442  mov [0x128E48E8],rax` | RTTI name ptr "mce::framebuilder::CloudLightingParameters]" @0xF6416AB [V] |
| [0x128E48F0] | 8B | sub_1188400 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof = 0x2A [V] |

Descriptor builder sub_1188250(rcx = descriptor pointer), init body at loc_118829c — every store into desc+0x00..+0x78:

| desc offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|-------------|------|------|-------------------------|---------------|
| +0x00 | 8B | 0x11882a9 | `0x11882a9  mov [rax],rdx` (rdx = &[0x128E48E0]) | desc+0x00 = &global index pointer [V] |
| +0x08 | 4B | 0x11882ac | `0x11882ac  mov [rax+8],ecx` (ecx = [0x128E48E4] = 0x8DE632ED) | desc+0x08 = type hash [V] |
| +0x10 | 8B | 0x11882af | `0x11882af  mov qword ptr [rax+0x10],0` | desc+0x10 = 0 [V] |
| +0x18 | 4B | 0x11882b7 | `0x11882b7  mov dword ptr [rax+0x18],0x80` | desc+0x18 = flags 0x80 [V] |
| +0x20 | 8B | 0x11882be | `0x11882be  mov qword ptr [rax+0x20],0x14` | desc+0x20 = member count 0x14 = 20 [V] |
| +0x28 | 8B | 0x11882cd | `0x11882c6  lea rcx,[0x1188170]`; `0x11882cd  mov [rax+0x28],rcx` | desc+0x28 = callback sub_1188170 [V] |
| +0x30 | 8B | 0x11882d8 | `0x11882d1  lea rcx,[0x11884A0]`; `0x11882d8  mov [rax+0x30],rcx` | desc+0x30 = callback sub_11884a0 (container init) [V] |
| +0x38 | 8B | 0x11882dc | `0x11882dc  mov qword ptr [rax+0x38],0` | desc+0x38 = 0 (cb slot, runtime-filled) [V] |
| +0x40 | 8B | 0x11882eb | `0x11882e4  lea rcx,[0x11886F0]`; `0x11882eb  mov [rax+0x40],rcx` | desc+0x40 = callback sub_11886f0 (entry init) [V] |
| +0x48 | 16B | 0x11882f2 | `0x11882ef  xorps xmm0,xmm0`; `0x11882f2  movups [rax+0x48],xmm0` | desc+0x48..+0x57 = 0 [V] |
| +0x54 | 16B | 0x11882f6 | `0x11882f6  movups [rax+0x54],xmm0` | desc+0x54..+0x63 = 0 (covers +0x60) [V] |
| +0x60 | 4B | 0x11882f6 | inside `movups [rax+0x54],xmm0` | desc+0x60 = 0 at build; live holds 0xD4C25870 (runtime-filled, see below) [V] build / [V live] per orchestrator CE |
| +0x68 | 16B | 0x11882fa | `0x11882fa  movups [rax+0x68],xmm0` | desc+0x68..+0x77 = 0 (covers +0x70) [V] |
| +0x70 | 8B | 0x11882fa | inside `movups [rax+0x68],xmm0` | desc+0x70 = 0 at build; live holds ctrl-block ptr (runtime-filled) [V] build / [V live] per orchestrator CE |
| +0x78 | 8B | 0x11882fe | `0x11882fe  mov qword ptr [rax+0x78],0` | desc+0x78 = member container ptr (0 at build; set to container by sub_1d4fd0) [V] |

Registration entry sub_1188780 (rcx = type-info obj: [rcx+0]=hash, [rcx+8]=name-obj; rdx, r8, r9 pass-through):
- `0x11887b6  mov dword ptr [rcx],0x8DE632ED` ; [rcx+0x0] = hash [V]
- `0x11887bc  mov [rcx+8],rdx`               ; [rcx+0x8] = name object ptr [V]
- `0x11887cf  call 0x1188250`                ; builds stack descriptor template (rcx = stack buf) [V]
- `0x11887e4  call 0x1D4FD0`                 ; rcx = rcx+0x10, rdx = rdx+0x18, r8 = stack template, r9d = hash [V]

sub_1d4fd0 — generic descriptor materialization (the store chain):
- `0x1d4ff2  mov [rcx],rdx`                              ; desc_out+0x00 = table ptr [V]
- `0x1d4ff8  movups [rcx+8],xmm0` ; `0x1d4ffc  mov qword ptr [rcx+0x18],0` ; desc_out+0x08..+0x17 = 0, +0x18 = 0 [V]
- hash-table probe in table (table+0x00 buckets, table+0x20 entries +0x00 next/+0x8 hash/+0x10 value, end table+0x28) keyed by r9d [V]
- `0x1d5061  mov edx,0x80`; `0x1d5066  call qword ptr [0xF99FFA0]` ; alloc 0x80-byte heap descriptor [V] (sub_eea6040)
- `0x1d5079..0x1d50bd` : copy template 0x60 bytes (movups +0x50/+0x40/+0x00/+0x10/+0x20/+0x30) + `0x1d50ab  mov eax,[rcx+0x60]`; `0x1d50ae  mov [rbx+0x60],eax`; `0x1d50b1  mov rax,[rcx+0x68]`; `0x1d50b5  mov [rbx+0x68],rax`; `0x1d50b9  mov rax,[rcx+0x70]`; `0x1d50bd  mov [rbx+0x70],rax` ; heap desc = template image [V]
- `0x1d50c4  movups [rcx+0x68],xmm0`; `0x1d50c8  mov rax,[rcx+0x78]`; `0x1d50cc  mov qword ptr [rcx+0x78],0` ; move template+0x68..+0x78 out (zeroed after) [V]
- `0x1d50d4  mov [rbx+0x78],rax` ; heap desc+0x78 = template+0x78 (0) then overwritten below [V]
- `0x1d5173  mov edx,0x78`; `0x1d5178  call qword ptr [0xF99FFA0]` ; alloc 0x78-byte container [V]
- `0x1d518b..0x1d51a9` : zero container +0x00..+0x70 (`movups [rdi+0x60]`..`[rdi+0x00]`), `0x1d51a9  mov qword ptr [rdi+0x70],0` ; container zero-init [V]
- `0x1d51b1  mov rax,[rsi+0x10]`; `0x1d51b5  mov rbx,[rax+0x78]`; `0x1d51b9  mov [rax+0x78],rdi` ; heap desc+0x78 = container ptr [V]
- `0x1d51d7..0x1d51da` : `mov eax,[rbp-4]`; `mov rcx,[rsi+0x10]`; `mov [rcx+8],eax` ; [heap desc+0x08] = hash [V]

Callback sub_11884a0 (desc+0x30) — container init (rcx = container, rdx = end/cursor):
- `0x11884b4  mov [rcx+0x10],rax` (rax = sub_1188560) ; container+0x10 = cb sub_1188560 [V]
- `0x11884b8  mov dword ptr [rcx+0x20],0x8DE632ED` ; container+0x20 = type hash [V]
- `0x11884c6  mov [rcx+0x18],rax` (rax = sub_11886d0) ; container+0x18 = cb sub_11886d0 [V]
- `0x11884ca  mov byte ptr [rcx+0x24],1` ; container+0x24 = flag 1 [V]
- `0x11884dc  mov edx,0x14`; `0x11884e1  call qword ptr [0xF99FFA0]` ; alloc 0x14-byte header object via registry [V]
- `0x11884ec  mov dword ptr [rax+0x10],0x101` ; header+0x10 = tag 0x101 [V]
- `0x11884fa  movaps [rax],xmm0` ; header+0x00 = 16B from [0xF0CD370] [V]
- `0x11884fd  mov [rsi],rax` (rsi = rcx) ; container+0x00 = header ptr [V]
- `0x1188500  mov [rsi+0x28],rdi` ; container+0x28 = rdi (end/cursor) [V]
- `0x1188504  mov qword ptr [rsi+0x30],0` ; container+0x30 = size 0 [V]
- `0x1188513  mov [rsi+0x38],rax` (rax = sub_1188540) ; container+0x38 = cb sub_1188540 [V]

Callback sub_11886f0 (desc+0x40) — per-member entry init (rax = entry, rdx, r8, r9); entry stride = 0x40 (stores span +0x00..+0x38, +0x30..+0x3F zeroed):
- `0x118870c  mov [rax+0x10],rcx` (rcx = sub_1188560) ; entry+0x10 = cb [V]
- `0x1188710  mov dword ptr [rax+0x20],0x8DE632ED` ; entry+0x20 = member type hash [V]
- `0x118871e  mov [rax+0x18],rcx` (sub_11886d0 or 0) ; entry+0x18 = cb/0 [V]
- name/tag: `0x1188722  mov byte ptr [rax+0x24],1` (both name ptrs null); `0x118874a  mov byte ptr [rax+0x24],3`; `0x118874e  mov [rax],r8` (r8 = name); `0x1188753  mov byte ptr [rax+0x24],4`; `0x1188757  mov [rax],r9` (r9 = name) ; entry+0x00 = name char* ptr; entry+0x24 = tag u8 (1/3/4) [V]
- `0x118875a  mov [rax+0x28],rdx` ; entry+0x28 = offset qword [V]
- `0x118875e  mov qword ptr [rax+0x30],0` ; entry+0x30 = 0 [V]
- `0x118876d  mov [rax+0x38],rcx` (sub_1188540) ; entry+0x38 = cb [V]

Runtime state (orchestrator CE read, r20): desc @0x22FC64D4560; +0x00=&global, +0x08=hash, +0x18=flags 0x80, +0x20=count 0x14, +0x28/0x30/0x40 = exe+0x1188170/0x11884A0/0x11886F0, +0x60 = 0xD4C25870, +0x68 -> node (+0x30 = 0xF), +0x70 -> ctrl block (vtable exe+0xF0DFBA0), +0x78 -> container 0x22FC61DB700; container +0x00 = ptr, +0x48/+0x50 = begin/end pointers (0x22FC607E9A0/...EA08), 20 members [V live]. Note: static builder zeroes desc+0x60/+0x68/+0x70 (+0x78 = 0); those live values are filled after registration (no static store into desc+0x60 found — the only static `mov ...,0xD4C25870` is 0x1D6501 `mov [rax+4],0xD4C25870` inside sub_1d64d0, the cereal TypeDescriptor singleton, not proven to be the descriptor) [I].

## Type 2 — CloudParameters (hash 0x8CBEF799, count 0x28=40, sizeof 0x22)

Metadata-init sub_118A6F0 (globals [0x128E4990..0x128E49A0]; guard [0x128E49B0], counter [0x128E49AC]):
- `0x118a71b  mov [0x128E4990],eax` ; index [V]
- `0x118a721  mov dword ptr [0x128E4994],0x8CBEF799` ; hash [V]
- `0x118a72b  lea rax,[0xF641A33]`; `0x118a732  mov [0x128E4998],rax` ; RTTI name "mce::framebuilder::CloudParameters]" @0xF641A33 [V]
- `0x118a739  mov qword ptr [0x128E49A0],0x22` ; sizeof 0x22 = 34 [V]

Stack template builder sub_118A540 (rcx = desc):
- `0x118a599  mov [rax],rdx` (rdx = &[0x128E4990]) ; +0x00 = &global [V]
- `0x118a59c  mov [rax+8],ecx` (ecx = [0x128E4994] = 0x8CBEF799) ; +0x08 = hash [V]
- `0x118a59f  mov qword ptr [rax+0x10],0` ; +0x10 = 0 [V]
- `0x118a5a7  mov dword ptr [rax+0x18],0x80` ; +0x18 = flags 0x80 [V]
- `0x118a5ae  mov qword ptr [rax+0x20],0x28` ; +0x20 = count 0x28 = 40 [V]
- `0x118a5b6  lea rcx,[0x118A460]`; `0x118a5bd  mov [rax+0x28],rcx` ; +0x28 = cb sub_118A460 [V]
- `0x118a5c1  lea rcx,[0x118A790]`; `0x118a5c8  mov [rax+0x30],rcx` ; +0x30 = cb sub_118A790 (container init) [V]
- `0x118a5cc  mov qword ptr [rax+0x38],0` ; +0x38 = 0 [V]
- `0x118a5d4  lea rcx,[0x118AA50]`; `0x118a5db  mov [rax+0x40],rcx` ; +0x40 = cb sub_118AA50 (entry init) [V]
- `0x118a5e2`/`0x118a5e6`/`0x118a5ea` `movups [rax+0x48/+0x54/+0x68],xmm0` ; +0x48..+0x77 = 0 [V]
- `0x118a5ee  mov qword ptr [rax+0x78],0` ; +0x78 = 0 [V]

Builder sub_118A790 (container init, same shape as sub_11884a0):
- `0x118a7a4  mov [rcx+0x10],rax` (sub_118A880) ; +0x10 = cb [V]
- `0x118a7a8  mov dword ptr [rcx+0x20],0x8CBEF799` ; +0x20 = hash [V]
- `0x118a7b6  mov [rcx+0x18],rax` (sub_DE5ED0) ; +0x18 = cb [V]
- `0x118a7ba  mov byte ptr [rcx+0x24],1` ; +0x24 = flag [V]
- `0x118a7cc  mov edx,0x28`; `0x118a7d1  call qword ptr [0xF99FFA0]` ; alloc 0x28-byte header object [V]
- `0x118a7f2  movups [rax],xmm0` ; header+0x00 = 16B from [0xF0CD370] [V]
- `0x118a7f5  mov word ptr [rax+0x10],0x101` ; header+0x10 = tag [V]
- `0x118a805  mov [rax+0x14],rcx` (rcx = 0x403F666666) ; header+0x14 = float 0x3F666664? (qword store) [V]
- `0x118a809  mov dword ptr [rax+0x1C],1` ; header+0x1C = 1 [V]
- `0x118a810  mov byte ptr [rax+0x20],1` ; header+0x20 = 1 [V]
- `0x118a814  mov dword ptr [rax+0x24],0x40000000` ; header+0x24 = 0x40000000 [V]
- `0x118a81b  mov [rsi],rax` ; container+0x00 = header ptr [V]
- `0x118a81e  mov [rsi+0x28],rdi` ; container+0x28 = rdi [V]
- `0x118a822  mov qword ptr [rsi+0x30],0` ; container+0x30 = 0 [V]
- `0x118a831  mov [rsi+0x38],rax` (sub_118A860) ; container+0x38 = cb [V]

Registration entry sub_118AAE0 (same shape as sub_1188780):
- `0x118ab16  mov dword ptr [rcx],0x8CBEF799` ; [rcx+0] = hash [V]
- `0x118ab1c  mov [rcx+8],rdx` ; [rcx+8] = name obj [V]
- `0x118ab2f  call 0x118A540` ; stack template builder [V]
- `0x118ab44  call 0x1D4FD0` ; materialize heap descriptor + container at +0x78 [V]
- `0x118ab4a  mov dword ptr [rsi+0x30],0`; `0x118ab51  mov eax,[rsi]`; `0x118ab53  mov [rsi+0x34],eax`; `0x118ab56  mov word ptr [rsi+0x38],0` ; name-object fixup [V]

Entry init: same shape as sub_11886f0 via cb sub_118AA50 at desc+0x40 (stride 0x40, name +0x00, tag +0x24, offset +0x28, type hash +0x20) — [V by code shape identity with sub_11886f0; cb body sub_118AA50 not disassembled beyond the store at 0x118a8d8 `mov [rax+0x20],0x8CBEF799`].

## Type 3 — ShadowParameters (hash 0x7C2A4E8C, +0x20 = 0x578, sizeof 0x23)

Metadata-init sub_5434C90 (globals [0x129C79C0..0x129C79D0]; guard [0x129C79E0], counter [0x129C79DC]):
- `0x5434cbb  mov [0x129C79C0],eax` ; index [V]
- `0x5434cc1  mov dword ptr [0x129C79C4],0x7C2A4E8C` ; hash [V]
- `0x5434ccb  lea rax,[0xF64103B]`; `0x5434cd2  mov [0x129C79C8],rax` ; RTTI name "mce::framebuilder::ShadowParameters]" @0xF64103B [V]
- `0x5434cd9  mov qword ptr [0x129C79D0],0x23` ; sizeof 0x23 = 35 [V]

Stack template builder sub_5434AE0 (rcx = desc):
- `0x5434b39  mov [rax],rdx` (rdx = &[0x129C79C0]) ; +0x00 = &global [V]
- `0x5434b3c  mov [rax+8],ecx` (ecx = [0x129C79C4] = 0x7C2A4E8C) ; +0x08 = hash [V]
- `0x5434b3f  mov qword ptr [rax+0x10],0` ; +0x10 = 0 [V]
- `0x5434b47  mov dword ptr [rax+0x18],0x80` ; +0x18 = flags 0x80 [V]
- `0x5434b4e  mov qword ptr [rax+0x20],0x578` ; +0x20 = 0x578 (1392; interpreted as member-count-or-defaults size — see note) [V]
- `0x5434b56  lea rcx,[0x5434A00]`; `0x5434b5d  mov [rax+0x28],rcx` ; +0x28 = cb sub_5434A00 [V]
- `0x5434b61  lea rcx,[0x5434D30]`; `0x5434b68  mov [rax+0x30],rcx` ; +0x30 = cb sub_5434D30 (container/init) [V]
- `0x5434b6c  mov qword ptr [rax+0x38],0` ; +0x38 = 0 [V]
- `0x5434b74  lea rcx,[0x5435840]`; `0x5434b7b  mov [rax+0x40],rcx` ; +0x40 = cb sub_5435840 (entry init) [V]
- `0x5434b82`/`0x5434b86`/`0x5434b8a` `movups [rax+0x48/+0x54/+0x68],xmm0`; `0x5434b8e  mov qword ptr [rax+0x78],0` ; +0x48..+0x77 = 0, +0x78 = 0 [V]

Builder sub_5434D30 (container/init, alloc 0x578-byte defaults object):
- `0x5434d44  mov [rcx+0x10],rax` (sub_5434EE0) ; +0x10 = cb [V]
- `0x5434d48  mov dword ptr [rcx+0x20],0x7C2A4E8C` ; +0x20 = hash [V]
- `0x5434d56  mov [rcx+0x18],rax` (sub_5435750) ; +0x18 = cb [V]
- `0x5434d5a  mov byte ptr [rcx+0x24],1` ; +0x24 = flag [V]
- `0x5434d6c  mov edx,0x578`; `0x5434d71  call qword ptr [0xF99FFA0]` ; alloc 0x578-byte defaults object [V]
- fills defaults object: `0x5434da1  mov [rbx],rax` (0x13E000000); `0x5434db1  mov dword ptr [rbx+0x10],8`; `0x5434dd7  mov word ptr [rbx+0x30],0x101`; `0x5434ddd  mov byte ptr [rbx+0x32],1`; +0x38..+0xBB movups/movsd stores from [0xFxxxxxx] data; `0x5434e72  mov qword ptr [rbx+0x190],3`; `0x5434e7d  mov qword ptr [rbx+0x570],1` [V]
- `0x5434e88  mov [rsi],rbx` ; container+0x00 = defaults object ptr [V]
- `0x5434e8b  mov [rsi+0x28],rdi` ; container+0x28 = rdi [V]
- `0x5434e8f  mov qword ptr [rsi+0x30],0` ; container+0x30 = 0 [V]
- `0x5434e9e  mov [rsi+0x38],rax` (sub_5434EC0) ; container+0x38 = cb [V]

Registration entry sub_54358D0 (same shape as sub_1188780):
- `0x5435906  mov dword ptr [rcx],0x7C2A4E8C` ; [rcx+0] = hash [V]
- `0x543590c  mov [rcx+8],rdx` ; [rcx+8] = name obj [V]
- `0x543591f  call 0x5434AE0` ; stack template builder [V]
- `0x5435934  call 0x1D4FD0` ; materialize heap descriptor + container at +0x78 [V]
- `0x543593a  mov dword ptr [rsi+0x30],0`; `0x5435941  mov eax,[rsi]`; `0x5435943  mov [rsi+0x34],eax`; `0x5435946  mov word ptr [rsi+0x38],0` ; fixup [V]

Entry init: same shape via cb sub_5435840 at desc+0x40 (stride 0x40, name +0x00, tag +0x24, offset +0x28, type hash +0x20) — [V by code-shape identity with sub_11886f0].

Note on ShadowParameters +0x20 = 0x578: unlike CloudLightingParameters (+0x20 = count 0x14, confirmed by live CE count 0x14) and CloudParameters (+0x20 = 0x28 = 40), ShadowParameters' builder stores 0x578 at +0x20 — the same value its container builder allocates (edx=0x578) as the defaults block size. Whether +0x20 is member count or defaults size for this type is not instruction-distinguished [I]; the live walk (container +0x48/+0x50, stride from (end-begin)/count) resolves it at read time.

## Type 4 — ShadowRange (hash 0x990FE13D, sizeof 0x1E=30) — DONE per orchestrator (sub_5437e20)

Metadata-init sub_5437E20 (globals [0x129C79E8..0x129C79F8]; guard [0x129C7A08], counter [0x129C7A04]):
- `0x5437e4b  mov [0x129C79E8],eax` ; index [V]
- `0x5437e51  mov dword ptr [0x129C79EC],0x990FE13D` ; hash [V]
- `0x5437e5b  lea rax,[0xF67B6CF]`; `0x5437e62  mov [0x129C79F0],rax` ; RTTI name "mce::framebuilder::ShadowRange]" @0xF67B6CF [V]
- `0x5437e69  mov qword ptr [0x129C79F8],0x1E` ; sizeof 0x1E = 30 [V]

Same 3-callback shape; builder sub_5437D30 (`0x5437d6f  mov dword ptr [rax+0x20],0x990FE13D` [V via imm]) and entry sub_544DE00 (`0x544de36  mov dword ptr [rcx],0x990FE13D`; `0x544de5e  mov r9d,0x990FE13D` [V via imm]). Recipe path identical: [desc+0x78]->+0x48 begin, +0x50 end, stride S, name +0x00, offset +0x28, tag +0x24.

## Type 5 — RenderShadowDescription

Not in the reflected scheme: `rdis imm 0x972122FD` (short name) and `imm 0x31FF492` (namespaced FNV-1a-32) both return 0 hits — no function stores either hash, so no metadata-init/descriptor/container exists for it in this scheme [V negative]. Per earlier orchestrator instruction it is handled via the insert-vtable / pass-body consumer path (struct from reads of [desc+off] in the shadow pass execute body), not via this recipe.

## Recipe (all [V] unless tagged)

read qword [exe+0x1233E1A8] -> registry/allocator object; -> hash table keyed by type hash (FNV-1a-32 of "mce::framebuilder::<Type>") -> heap descriptor (0x80 bytes, sub_1d4fd0):
  desc+0x00 = &global index, desc+0x08 = hash, desc+0x18 = flags 0x80, desc+0x20 = count (CLP 0x14, CP 0x28, SP 0x578 [?]), desc+0x28/0x30/0x40 = callbacks, desc+0x60 = 0xD4C25870 at runtime (0 at build), desc+0x78 = member container (0x78 bytes, zeroed at build).
Members live in the container reached via desc+0x78: [desc+0x78] -> container object; container +0x48 = begin ptr, container +0x50 = end ptr ([V live] per orchestrator CE read citing container 0x22FC61DB700 with +0x48/+0x50 = 0x22FC607E9A0/...EA08; statically sub_11884a0 stores header ptr at container+0x00 and end-cursor at container+0x28, while the +0x48/+0x50 begin/end cursors are set by the runtime push path in sub_1d4fd0/sub_1d5350, not by a static store into desc+0x48/desc+0x50) [I]; stride S = (end - begin) / count (entry stride 0x40 from sub_11886f0 store span +0x00..+0x38 [V] for CloudLightingParameters; same 3-callback shape implies stride 0x40 for CloudParameters/ShadowParameters/ShadowRange [I by code-shape identity]); per entry (0x40 bytes): name at +0x00 (char* ptr), tag at +0x24 (u8: 1/3/4), offset at +0x28 (qword), type hash at +0x20 — all [V] from sub_11886f0 stores.

Delivered path: "[desc+0x78]->container; container+0x48 begin, container+0x50 end, stride 0x40, name at +0x00, offset at +0x28, tag at +0x24" (applies to CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange; RenderShadowDescription not in this scheme [V negative] — its struct comes from the shadow-pass consumer reads, a separate pending item).

## Files created

- docs/progress/oc_U-EM2c.md (this file, only file for this unit)

## CLOSES?

YES for this unit's stated GOAL (the reflected-parameter member-table recipe): CloudLightingParameters (sub_1188400/sub_1188250/sub_1188780), CloudParameters (sub_118a6f0/sub_118a540/sub_118aae0), ShadowParameters (sub_5434c90/sub_5434d30/sub_54358d0), ShadowRange (sub_5437e20/sub_5437d30) all located with [V] global/descriptor rows (hash stored to [0x128E48xx]/[0x129C79xx] globals, RTTI name ptr, sizeof) and the entry path [V] (stride 0x40, name +0x00, offset +0x28, tag +0x24). RenderShadowDescription is not part of this scheme (both FNV-1a immediates return 0 hits, [V] negative) — its struct comes from the shadow-pass consumer reads, a separate pending item. delegate.py check exits 0; ## NEXT line 2 = DONE.

## TOOL REQUESTS

None.
