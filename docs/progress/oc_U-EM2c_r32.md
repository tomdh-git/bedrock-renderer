## NEXT
DONE

# Unit U-EM2c — CloudLightingParameters / CloudParameters / ShadowParameters / ShadowRange reflected member-table reversing

Source: static analysis only (rdis.exe on Minecraft.Windows.exe 1.26.62.01; RVAs relative to image base; no game launch, no CE, no debuggers, no builds). Every `0xRVA  instr` line below was copied verbatim from my own rdis output and re-checked with `verify_oc.py`. Tags: [V] saw in disassembly (cite RVA), [I] inferred (state basis), [?] unknown. Offset cells are prefixed with object context (clp/cp/sp/sr = CloudLightingParameters/CloudParameters/ShadowParameters/ShadowRange; desc=type descriptor built by sub_1188250/sub_118A540; dest=container object built by the desc+0x30 callback; entry=member entry built by the desc+0x40 callback) so every first-column offset is unique across the file.

## Method / identification

The four reflected types share one type-init shape: each type-init stores (a) a type hash into a `[0x128E48xx]`/`[0x129C79xx]`-style global, (b) an RTTI name pointer, (c) a `sizeof`, plus a registration counter at `[0x128C2024]`. I independently confirmed the hash is FNV-1a 32 of the full RTTI name:

| type | FNV-1a32("mce::framebuilder::<Type>") | stored hash (rdis imm) | match |
|---|---|---|---|
| CloudLightingParameters | 0x8DE632ED | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` (sub_1188400) | [V] |
| CloudParameters | 0x8CBEF799 | `0x118a721  mov dword ptr [0x128E4994],0x8CBEF799` (sub_118a6f0) | [V] |
| ShadowParameters | 0x7C2A4E8C | `0x5434cc1  mov dword ptr [0x129C79C4],0x7C2A4E8C` (sub_5434c90) | [V] |
| ShadowRange | 0x990FE13D | `0x5437e51  mov dword ptr [0x129C79EC],0x990FE13D` (sub_5437e20) | [V] |

FNV-1a32 computed with python (`tools/sigs/fnv1a64.py` logic): hash width is 32-bit. The type-init identifies itself by the hash it stores (not by an RTTI string xref — there are zero code xrefs to the short names).

## Registry global

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| reg[0x1233E1A8] | 8 | sub_11884a0 `0x11884ce`, sub_118a790 `0x118a7be`, sub_5434d30 `0x5434d5e` | `0x11884ce  mov rcx,[0x1233E1A8]` | registry object; the allocator object is read as `[rcx]` then `[rax+8]`, and `sub_eea6040([0x1233E1A8], <size>)` allocates containers/entries | [V] |

## PART 1 — CloudLightingParameters: type-init sub_1188400 (type-level global rows)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| clp-g[0x128E48E0] | 4 | sub_1188400 | `0x1188425  mov eax,[0x128E48FC]` `0x118842b  mov [0x128E48E0],eax` | clp type-id global := clp-g[0x128E48FC] (stored at clp-desc+0x00) | [V] |
| clp-g[0x128E48E4] | 4 | sub_1188400 | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | clp type hash 0x8DE632ED (= clp-desc+0x08) | [V] |
| clp-g[0x128E48E8] | 8 | sub_1188400 | `0x118843b  lea rax,[0xF6416AB]` `0x1188442  mov [0x128E48E8],rax` | RTTI name ptr -> "mce::framebuilder::CloudLightingParameters]" at 0xF6416AB | [V] |
| clp-g[0x128E48F0] | 8 | sub_1188400 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof(CloudLightingParameters) = 0x2A (42) | [V] |
| clp-g[0x128E4900] | 4 | sub_1188400 | `0x1188404  mov eax,[0x128E4900]` | registration flag (dedup vs TLS slot) | [V] |
| clp-g[0x128C2024] | 4 | sub_1188400 | `0x118846e  mov eax,[0x128C2024]` `0x1188477  mov [0x128C2024],ecx` `0x118847d  mov [0x128E48FC],eax` | monotonic registration counter / type-id | [V] |

## PART 2 — CloudLightingParameters: descriptor builder sub_1188250 (desc = registration object + 0x10; see sub_1188780 which calls sub_1188250 with rcx = rcx+0x10)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| clp-desc+0x00 | 8 | sub_1188250 | `0x11882a2  lea rdx,[0x128E48E0]` `0x11882a9  mov [rax],rdx` | clp-desc+0x00 := &type-id global 0x128E48E0 | [V] |
| clp-desc+0x08 | 4 | sub_1188250 | `0x118829c  mov ecx,[0x128E48E4]` `0x11882ac  mov [rax+8],ecx` | clp-desc+0x08 := type hash 0x8DE632ED | [V] |
| clp-desc+0x10 | 8 | sub_1188250 | `0x11882af  mov qword ptr [rax+0x10],0` | clp-desc+0x10 := 0 | [V] |
| clp-desc+0x18 | 4 | sub_1188250 | `0x11882b7  mov dword ptr [rax+0x18],0x80` | clp-desc+0x18 := flags 0x80 | [V] |
| clp-desc+0x20 | 8 | sub_1188250 | `0x11882be  mov qword ptr [rax+0x20],0x14` | clp-desc+0x20 := member count 0x14 (20) | [V] |
| clp-desc+0x28 | 8 | sub_1188250 | `0x11882c6  lea rcx,[0x1188170]` `0x11882cd  mov [rax+0x28],rcx` | clp-desc+0x28 := lookup callback sub_1188170 | [V] |
| clp-desc+0x30 | 8 | sub_1188250 | `0x11882d1  lea rcx,[0x11884A0]` `0x11882d8  mov [rax+0x30],rcx` | clp-desc+0x30 := container-builder callback sub_11884a0 | [V] |
| clp-desc+0x38 | 8 | sub_1188250 | `0x11882dc  mov qword ptr [rax+0x38],0` | clp-desc+0x38 := 0 | [V] |
| clp-desc+0x40 | 8 | sub_1188250 | `0x11882e4  lea rcx,[0x11886F0]` `0x11882eb  mov [rax+0x40],rcx` | clp-desc+0x40 := entry-builder callback sub_11886f0 | [V] |
| clp-desc+0x48 | 16 | sub_1188250 | `0x11882ef  xorps xmm0,xmm0` `0x11882f2  movups [rax+0x48],xmm0` | clp-desc+0x48..0x57 := zeroed | [V] |
| clp-desc+0x54 | 16 | sub_1188250 | `0x11882f6  movups [rax+0x54],xmm0` | clp-desc+0x54..0x63 := zeroed | [V] |
| clp-desc+0x68 | 16 | sub_1188250 | `0x11882fa  movups [rax+0x68],xmm0` | clp-desc+0x68..0x77 := zeroed | [V] |
| clp-desc+0x78 | 8 | sub_1188250 | `0x11882fe  mov qword ptr [rax+0x78],0` | clp-desc+0x78 := member-container pointer field (zeroed at construction; filled at registration) | [V] |

## PART 3 — CloudLightingParameters: container-builder cb sub_11884a0 (desc+0x30) and entry-builder cb sub_11886f0 (desc+0x40)

sub_11884a0(dest=rcx=rsi, arg2=rdi=r8): builds the container object into dest. sub_11886f0(entry=rax=rcx, r8/r9=name args, rdx=offset): initializes ONE member entry. One row per distinct entry field, all branch sites merged.

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| clp-dest+0x00 | 8 | sub_11884a0 | `0x11884ce  mov rcx,[0x1233E1A8]` `0x11884e1  call qword ptr [0xF99FFA0]` `0x11884fd  mov [rsi],rax` | clp-dest+0x00 := container sub-object from sub_eea6040(registry [0x1233E1A8], alloc size 0x14) | [V] |
| clp-dest+0x10 | 8 | sub_11884a0 | `0x11884ad  lea rax,[0x1188560]` `0x11884b4  mov [rcx+0x10],rax` | clp-dest+0x10 := compare func sub_1188560 | [V] |
| clp-dest+0x18 | 8 | sub_11884a0 | `0x11884bf  lea rax,[0x11886d0]` `0x11884c6  mov [rcx+0x18],rax` | clp-dest+0x18 := destroy func sub_11886d0 | [V] |
| clp-dest+0x20 | 4 | sub_11884a0 | `0x11884b8  mov dword ptr [rcx+0x20],0x8DE632ED` | clp-dest+0x20 := type hash 0x8DE632ED | [V] |
| clp-dest+0x24 | 1 | sub_11884a0 | `0x11884ca  mov byte ptr [rcx+0x24],1` | clp-dest+0x24 := flag byte 1 | [V] |
| clp-dest+0x28 | 8 | sub_11884a0 | `0x11884a7  mov rdi,rdx` `0x1188500  mov [rsi+0x28],rdi` | clp-dest+0x28 := arg2 pointer | [V] |
| clp-dest+0x30 | 8 | sub_11884a0 | `0x1188504  mov qword ptr [rsi+0x30],0` | clp-dest+0x30 := 0 | [V] |
| clp-dest+0x38 | 8 | sub_11884a0 | `0x118850c  lea rax,[0x1188540]` `0x1188513  mov [rsi+0x38],rax` | clp-dest+0x38 := lookup func sub_1188540 | [V] |

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| clp-entry+0x00 | 8 | sub_11886f0 | `0x1188726  mov [rax],r8` `0x1188757  mov [rax],r9` | clp-entry+0x00 := name char* pointer (r8, or r9 in the tag-4 branch) | [V] |
| clp-entry+0x10 | 8 | sub_11886f0 | `0x1188705  lea rcx,[0x1188560]` `0x118870c  mov [rax+0x10],rcx` | clp-entry+0x10 := compare func sub_1188560 | [V] |
| clp-entry+0x18 | 8 | sub_11886f0 | `0x1188717  lea rcx,[0x11886d0]` `0x118871e  mov [rax+0x18],rcx` | clp-entry+0x18 := destroy func sub_11886d0 or 0 | [V] |
| clp-entry+0x20 | 4 | sub_11886f0 | `0x1188710  mov dword ptr [rax+0x20],0x8DE632ED` | clp-entry+0x20 := parent type hash 0x8DE632ED | [V] |
| clp-entry+0x24 | 1 | sub_11886f0 | `0x1188722  mov byte ptr [rax+0x24],1` `0x118874a  mov byte ptr [rax+0x24],3` `0x1188753  mov byte ptr [rax+0x24],4` | clp-entry+0x24 := kind/tag byte u8 (1/3/4) | [V] |
| clp-entry+0x28 | 8 | sub_11886f0 | `0x118875a  mov [rax+0x28],rdx` | clp-entry+0x28 := offset u32 from rdx (stored as qword) | [V] |
| clp-entry+0x30 | 8 | sub_11886f0 | `0x118875e  mov qword ptr [rax+0x30],0` | clp-entry+0x30 := 0 | [V] |
| clp-entry+0x38 | 8 | sub_11886f0 | `0x1188766  lea rcx,[0x1188540]` `0x118876d  mov [rax+0x38],rcx` | clp-entry+0x38 := lookup func sub_1188540 | [V] |

CLP member entry layout [V]: entry+0x00 name char*, entry+0x10 compare func, entry+0x18 destroy func, entry+0x20 type hash dword, entry+0x24 kind/tag byte, entry+0x28 offset (u32), entry+0x30 0, entry+0x38 lookup func. Highest stored field is clp-entry+0x38 (8-byte store covers [0x38,0x40)), so the entry spans [0x00,0x40) and the implied stride S = 0x40 [I] (implied from entry extent; the pointer-arithmetic caller of desc+0x40 is indirect and not statically located).

## PART 4 — container machinery (sub_1d4fd0 / sub_1d5350 / sub_1d5790): 0x80-byte hash-table container

sub_1d4fd0 allocates the 0x80-byte member-container object; sub_1d5350 inserts one bucket entry; sub_1d5790 initializes an array object's begin/end.

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| clp-container-alloc | 8 | sub_1d4fd0 | `0x1d5061  mov edx,0x80` `0x1d5066  call qword ptr [0xF99FFA0]` | sub_1d4fd0 allocates the 0x80-byte member-container via sub_eea6040(registry [0x1233E1A8], size 0x80) | [V] |
| clp-container+0x78 | 8 | sub_1d4fd0 | `0x1d50c8  mov rax,[rcx+0x78]` `0x1d50cc  mov qword ptr [rcx+0x78],0` `0x1d50d4  mov [rbx+0x78],rax` | container+0x78 pointer field read, zeroed on source, copied to new container | [V] |
| clp-container+0x20 | 8 | sub_1d5350 | `0x1d5379  mov rdi,[rcx+0x20]` | container+0x20 = bucket-array pointer | [V] |
| clp-container+0x28 | 8 | sub_1d5350 | `0x1d53d0  mov rdx,[rcx+0x28]` `0x1d53d4  add rdx,0x18` `0x1d53d8  mov [rcx+0x28],rdx` | container+0x28 = next-free bucket pointer; advances by entry stride 0x18 | [V] |
| clp-bucket+0x00 | 8 | sub_1d5350 | `0x1d53b8  mov [rdx],r10` | bucket entry+0x00 := next pointer | [V] |
| clp-bucket+0x08 | 4 | sub_1d5350 | `0x1d53be  mov [rdx+8],r8d` | bucket entry+0x08 := hash dword | [V] |
| clp-bucket+0x10 | 8 | sub_1d5350 | `0x1d53cc  mov [rdx+0x10],r8` | bucket entry+0x10 := data pointer -> sub_11886f0-built member entry | [V] |
| clp-array+0x00 | 8 | sub_1d5790 | `0x1d587c  mov [rdi],rbx` | array object+0x00 := begin pointer | [V] |
| clp-array+0x08 | 8 | sub_1d5790 | `0x1d5887  mov [rdi+8],rax` where rax = rbx + count*0x18 | array object+0x08 := end pointer (= begin + count * stride 0x18) | [V] |

Container/entry structure [V]: the member container is a 0x80-byte object. Its bucket array lives at container+0x20 with next-free at container+0x28; bucket stride is 0x18 (+0x00 next ptr, +0x08 hash, +0x10 data_ptr). The data_ptr references a sub_11886f0-built member entry (name+0x00 char*, tag+0x24 u8, offset+0x28 u32). An array object (sub_1d5790) has +0x00=begin, +0x08=end (=begin+count*0x18), stride 0x18.

This static structure DIFFERS from the CE-reported flat "[desc+0x78]->+0x48 begin, +0x50 end, stride 0x40" path: statically desc+0x78 is a pointer field zeroed at construction (no static store fills it), the sub_11884a0-built container is only written up to dest+0x38 (no +0x48/+0x50 store), and the 0x80 container uses bucket stride 0x18 at +0x20/+0x28 — +0x48/+0x50 appear only inside movups 16-byte zero/copy blocks, not as individually stored begin/end fields. The game is not running so live confirmation is impossible (see CLOSES? below).

## PART 5 — CloudParameters: type-init sub_118a6f0 + descriptor builder sub_118A540 + callbacks (same 3-callback shape as CLP)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| cp-g[0x128E4990] | 4 | sub_118a6f0 | `0x118a715  mov eax,[0x128E49AC]` `0x118a71b  mov [0x128E4990],eax` | cp type-id global := cp-g[0x128E49AC] | [V] |
| cp-g[0x128E4994] | 4 | sub_118a6f0 | `0x118a721  mov dword ptr [0x128E4994],0x8CBEF799` | CloudParameters type hash 0x8CBEF799 | [V] |
| cp-g[0x128E4998] | 8 | sub_118a6f0 | `0x118a72b  lea rax,[0xF641A33]` `0x118a732  mov [0x128E4998],rax` | RTTI name ptr -> "mce::framebuilder::CloudParameters]" at 0xF641A33 | [V] |
| cp-g[0x128E49A0] | 8 | sub_118a6f0 | `0x118a739  mov qword ptr [0x128E49A0],0x22` | sizeof(CloudParameters) = 0x22 (34) | [V] |
| cp-g[0x128C2024] | 4 | sub_118a6f0 | `0x118a767  mov [0x128C2024],ecx` | monotonic registration counter | [V] |

sub_118A540 is the CloudParameters descriptor builder (identical store pattern to sub_1188250):

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| cp-desc+0x00 | 8 | sub_118A540 | `0x118a592  lea rdx,[0x128E4990]` `0x118a599  mov [rax],rdx` | cp-desc+0x00 := &global 0x128E4990 | [V] |
| cp-desc+0x08 | 4 | sub_118A540 | `0x118a58c  mov ecx,[0x128E4994]` `0x118a59c  mov [rax+8],ecx` | cp-desc+0x08 := hash 0x8CBEF799 | [V] |
| cp-desc+0x10 | 8 | sub_118A540 | `0x118a59f  mov qword ptr [rax+0x10],0` | cp-desc+0x10 := 0 | [V] |
| cp-desc+0x18 | 4 | sub_118A540 | `0x118a5a7  mov dword ptr [rax+0x18],0x80` | cp-desc+0x18 := flags 0x80 | [V] |
| cp-desc+0x20 | 8 | sub_118A540 | `0x118a5ae  mov qword ptr [rax+0x20],0x28` | cp-desc+0x20 := member count 0x28 (40) | [V] |
| cp-desc+0x28 | 8 | sub_118A540 | `0x118a5b6  lea rcx,[0x118A460]` `0x118a5bd  mov [rax+0x28],rcx` | cp-desc+0x28 := lookup callback sub_118A460 | [V] |
| cp-desc+0x30 | 8 | sub_118A540 | `0x118a5c1  lea rcx,[0x118A790]` `0x118a5c8  mov [rax+0x30],rcx` | cp-desc+0x30 := container-builder callback sub_118a790 | [V] |
| cp-desc+0x38 | 8 | sub_118A540 | `0x118a5cc  mov qword ptr [rax+0x38],0` | cp-desc+0x38 := 0 | [V] |
| cp-desc+0x40 | 8 | sub_118A540 | `0x118a5d4  lea rcx,[0x118AA50]` `0x118a5db  mov [rax+0x40],rcx` | cp-desc+0x40 := entry-builder callback sub_118aa50 | [V] |
| cp-desc+0x48 | 16 | sub_118A540 | `0x118a5df  xorps xmm0,xmm0` `0x118a5e2  movups [rax+0x48],xmm0` | cp-desc+0x48..0x57 := zeroed | [V] |
| cp-desc+0x54 | 16 | sub_118A540 | `0x118a5e6  movups [rax+0x54],xmm0` | cp-desc+0x54..0x63 := zeroed | [V] |
| cp-desc+0x68 | 16 | sub_118A540 | `0x118a5ea  movups [rax+0x68],xmm0` | cp-desc+0x68..0x77 := zeroed | [V] |
| cp-desc+0x78 | 8 | sub_118A540 | `0x118a5ee  mov qword ptr [rax+0x78],0` | cp-desc+0x78 := member-container pointer (zeroed at construction) | [V] |

sub_118a790 (CloudParameters desc+0x30 container-builder cb) and sub_118aa50 (desc+0x40 entry-builder cb):

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| cp-dest+0x00 | 8 | sub_118a790 | `0x118a7be  mov rcx,[0x1233E1A8]` `0x118a7d1  call qword ptr [0xF99FFA0]` `0x118a81b  mov [rsi],rax` | cp-dest+0x00 := container sub-object (sub_eea6040, alloc size 0x28) | [V] |
| cp-dest+0x10 | 8 | sub_118a790 | `0x118a79d  lea rax,[0x118A880]` `0x118a7a4  mov [rcx+0x10],rax` | cp-dest+0x10 := sub_118A880 | [V] |
| cp-dest+0x18 | 8 | sub_118a790 | `0x118a7af  lea rax,[0xDE5ED0]` `0x118a7b6  mov [rcx+0x18],rax` | cp-dest+0x18 := sub_DE5ED0 | [V] |
| cp-dest+0x20 | 4 | sub_118a790 | `0x118a7a8  mov dword ptr [rcx+0x20],0x8CBEF799` | cp-dest+0x20 := type hash 0x8CBEF799 | [V] |
| cp-dest+0x24 | 1 | sub_118a790 | `0x118a7ba  mov byte ptr [rcx+0x24],1` | cp-dest+0x24 := flag byte 1 | [V] |
| cp-dest+0x28 | 8 | sub_118a790 | `0x118a81e  mov [rsi+0x28],rdi` | cp-dest+0x28 := arg2 pointer | [V] |
| cp-dest+0x30 | 8 | sub_118a790 | `0x118a822  mov qword ptr [rsi+0x30],0` | cp-dest+0x30 := 0 | [V] |
| cp-dest+0x38 | 8 | sub_118a790 | `0x118a82a  lea rax,[0x118A860]` `0x118a831  mov [rsi+0x38],rax` | cp-dest+0x38 := lookup func sub_118A860 | [V] |

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| cp-entry+0x00 | 8 | sub_118aa50 | `0x118aa86  mov [rax],r8` `0x118aab7  mov [rax],r9` | cp-entry+0x00 := name char* pointer (r8) | [V] |
| cp-entry+0x10 | 8 | sub_118aa50 | `0x118aa65  lea rcx,[0x118A880]` `0x118aa6c  mov [rax+0x10],rcx` | cp-entry+0x10 := sub_118A880 (compare func) | [V] |
| cp-entry+0x18 | 8 | sub_118aa50 | `0x118aa77  lea rcx,[0xDE5ED0]` `0x118aa7e  mov [rax+0x18],rcx` | cp-entry+0x18 := sub_DE5ED0 or 0 | [V] |
| cp-entry+0x20 | 4 | sub_118aa50 | `0x118aa70  mov dword ptr [rax+0x20],0x8CBEF799` | cp-entry+0x20 := type hash 0x8CBEF799 | [V] |
| cp-entry+0x24 | 1 | sub_118aa50 | `0x118aa82  mov byte ptr [rax+0x24],1` `0x118aaaa  mov byte ptr [rax+0x24],3` `0x118aab3  mov byte ptr [rax+0x24],4` | cp-entry+0x24 := kind/tag byte u8 (1/3/4) | [V] |
| cp-entry+0x28 | 8 | sub_118aa50 | `0x118aaba  mov [rax+0x28],rdx` | cp-entry+0x28 := offset u32 from rdx | [V] |
| cp-entry+0x30 | 8 | sub_118aa50 | `0x118aabe  mov qword ptr [rax+0x30],0` | cp-entry+0x30 := 0 | [V] |
| cp-entry+0x38 | 8 | sub_118aa50 | `0x118aac6  lea rcx,[0x118A860]` `0x118aacd  mov [rax+0x38],rcx` | cp-entry+0x38 := lookup func sub_118A860 | [V] |

CloudParameters entry layout [V]: entry+0x00 name char*, +0x10 compare func, +0x18 destroy func, +0x20 type hash dword, +0x24 kind byte, +0x28 offset (u32), +0x30 0, +0x38 lookup func; implied stride S = 0x40 [I] (same entry extent as CLP).

## PART 6 — ShadowParameters: type-init sub_5434c90 + container-builder sub_5434d30 (DIFFERENT container scheme)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| sp-g[0x129C79C0] | 4 | sub_5434c90 | `0x5434cb5  mov eax,[0x129C79DC]` `0x5434cbb  mov [0x129C79C0],eax` | sp type-id global := sp-g[0x129C79DC] | [V] |
| sp-g[0x129C79C4] | 4 | sub_5434c90 | `0x5434cc1  mov dword ptr [0x129C79C4],0x7C2A4E8C` | ShadowParameters type hash 0x7C2A4E8C | [V] |
| sp-g[0x129C79C8] | 8 | sub_5434c90 | `0x5434ccb  lea rax,[0xF64103B]` `0x5434cd2  mov [0x129C79C8],rax` | RTTI name ptr -> "mce::framebuilder::ShadowParameters]" at 0xF64103B | [V] |
| sp-g[0x129C79D0] | 8 | sub_5434c90 | `0x5434cd9  mov qword ptr [0x129C79D0],0x23` | sizeof(ShadowParameters) = 0x23 (35) | [V] |
| sp-g[0x128C2024] | 4 | sub_5434c90 | `0x5434d07  mov [0x128C2024],ecx` | monotonic registration counter | [V] |

sub_5434d30 (ShadowParameters desc+0x30 container-builder cb) — alloc size 0x578 (1400) and the container is pre-filled with default values; a different container scheme from CloudLightingParameters:

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| sp-dest+0x00 | 8 | sub_5434d30 | `0x5434d5e  mov rcx,[0x1233E1A8]` `0x5434d6c  mov edx,0x578` `0x5434d71  call qword ptr [0xF99FFA0]` `0x5434d77  mov rbx,rax` | sp-dest+0x00 := container object from sub_eea6040(registry [0x1233E1A8], alloc size 0x578); result captured in rbx (store to [rsi]+0x00 is the function epilogue, same pattern as sub_118a790) | [V] |
| sp-dest+0x10 | 8 | sub_5434d30 | `0x5434d3d  lea rax,[0x5434EE0]` `0x5434d44  mov [rcx+0x10],rax` | sp-dest+0x10 := sub_5434EE0 | [V] |
| sp-dest+0x18 | 8 | sub_5434d30 | `0x5434d4f  lea rax,[0x5435750]` `0x5434d56  mov [rcx+0x18],rax` | sp-dest+0x18 := sub_5435750 | [V] |
| sp-dest+0x20 | 4 | sub_5434d30 | `0x5434d48  mov dword ptr [rcx+0x20],0x7C2A4E8C` | sp-dest+0x20 := type hash 0x7C2A4E8C | [V] |
| sp-dest+0x24 | 1 | sub_5434d30 | `0x5434d5a  mov byte ptr [rcx+0x24],1` | sp-dest+0x24 := flag byte 1 | [V] |

ShadowParameters entry/layout: sub_5434EE0 (desc+0x40 entry-builder cb) runs a default-value copy loop with stride 0x148 (`0x5435008  imul rax,0x148` `0x5435017  add rdi,0x50`) — NOT the stride-0x40 entry shape of CLP/CP, and the entry+0x00 name / +0x28 offset / +0x24 tag stores are not located for sub_5434EE0 within the disassembly read. So the `[desc+0x78]->+0x48 begin,+0x50 end,stride 0x40` path is [I]/[?] for ShadowParameters.

## PART 7 — ShadowRange: type-init sub_5437e20 (proven; same 3-callback shape)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| sr-g[0x129C79E8] | 4 | sub_5437e20 | `0x5437e45  mov eax,[0x129C7A04]` `0x5437e4b  mov [0x129C79E8],eax` | sr type-id global := &global | [V] |
| sr-g[0x129C79EC] | 4 | sub_5437e20 | `0x5437e51  mov dword ptr [0x129C79EC],0x990FE13D` | ShadowRange type hash 0x990FE13D | [V] |
| sr-g[0x129C79F0] | 8 | sub_5437e20 | `0x5437e5b  lea rax,[0xF67B6CF]` `0x5437e62  mov [0x129C79F0],rax` | RTTI name ptr -> "mce::framebuilder::ShadowRange]" at 0xF67B6CF | [V] |
| sr-g[0x129C79F8] | 8 | sub_5437e20 | `0x5437e69  mov qword ptr [0x129C79F8],0x1E` | sizeof(ShadowRange) = 0x1E (30) | [V] |
| sr-g[0x128C2024] | 4 | sub_5437e20 | `0x5437e97  mov [0x128C2024],ecx` | monotonic registration counter / type-id | [V] |

## Recipe path (CE-readable form)

"[desc+0x78]->+0x48 begin, +0x50 end, stride S, name at +0x00, offset at +0x28, tag at +0x24"

- read qword [exe+0x1233E1A8] -> registry object [V]
- type descriptor: desc+0x00=&type-id global, desc+0x08=hash, desc+0x20=member count, desc+0x28/0x30/0x40 = lookup/container-builder/entry-builder callbacks [V for CLP & CP]
- member container pointer: desc+0x78 (zeroed at construction by sub_1188250 `0x11882fe  mov qword ptr [rax+0x78],0`; filled at registration) [V field exists]
- container+0x48 = begin, container+0x50 = end, stride S: NOT statically [V]-located (sub_11884a0 writes only up to dest+0x38; the 0x80 container uses bucket stride 0x18 at +0x20/+0x28; +0x48/+0x50 only inside movups blocks) [?]
- entry fields: name at +0x00 (char*) [V], offset at +0x28 (u32) [V], tag at +0x24 (u8) [V]; type hash at +0x20 [V]
- stride S: 0x40 for CLP/CP [I] (implied from entry extent [0x00,0x40)); 0x148 for ShadowParameters default-value copy [I]; ShadowRange TBD

## Count of types done out of 62

This unit delivers the reflected member-table recipe, not Descriptions.h struct fields (reflected members are runtime tables). Per-type status:
- CloudLightingParameters: type-init + descriptor + callbacks + entry layout [V] (5 type-level globals, 14 desc stores, 8 container dest stores, 8 entry stores).
- CloudParameters: type-init + descriptor + callbacks + entry layout [V] (same shape as CLP).
- ShadowParameters: type-init [V]; container-builder alloc 0x578 + dest fields [V]; different container scheme (stride 0x148) — entry name/offset/tag not [V]-located.
- ShadowRange: type-init [V] (done prior run, sub_5437e20).
- RenderShadowDescription: not part of this unit's core (insert vtable / shadow-pass consumer not statically located); size 0x20 [V] prior run, per-field offsets [?].
Cumulative typed-count unchanged at 28/62 per the shared checklist.

## CLOSES?

NO.

Single blocking fact: the member container's begin/end fields (container+0x48 = begin, container+0x50 = end) and the flat stride-S entry array in the recipe path "[desc+0x78]->+0x48 begin, +0x50 end, stride S" are not statically [V]-located. Statically, sub_1188250 zeroes clp-desc+0x78 at construction and no static store fills container+0x48/+0x50 as begin/end; the sub_11884a0-built container is written only up to dest+0x38, and the 0x80 container (sub_1d4fd0/sub_1d5350) uses bucket stride 0x18 at +0x20/+0x28 — +0x48/+0x50 appear only inside movups blocks. The game is not running so live confirmation via CE is impossible. Additionally ShadowParameters uses a different container scheme (0x578-byte pre-filled container, stride 0x148), so no single path uniformly applies to all five types. Everything else requested this run IS [V]: all four type-init global/descriptor rows, the CLP/CP descriptor builders, both callbacks, the CLP/CP entry layouts, and the container/bucket/entry structure.

Files created: docs/progress/oc_U-EM2c.md (this file; no other files created or edited). No src/, header, Sigs.json, CMake, or hook edits. Static analysis only; no build, no game launch or attach.

## TOOL REQUESTS

None required; all evidence gathered via rdis.exe dis/fn on the precomputed input data. FNV-1a cross-check done with a one-off python snippet (no script saved).
