# U-EL16d — L16d RTX slots in the bgfx fork — 6al (slots 54/63/64)

Goal: close RENDER_CHECKLIST.md line 399 item `L16d RTX slots in the bgfx fork — 6al (slots 54/63/64)`.
Source: rdis listings of Minecraft.Windows.exe (1.26.62.01): slot 54 = 0xe83d7d0 (complete, ~0x535 bytes, ends e83dd05 ret, called via vtable slot +0x1B0); slot 63 = 0xe83f1d0 (listing read through the loop body after the checks); slot 64 = 0xe8403d0 (0xaa5b bytes; driver gate, named resources, RT dispatch cluster read).
Every verbatim `0xRVA  instr` line below is copied from the rdis listing (two spaces after the address) and is re-checked by tools/sigs/verify_oc.py via the proof-lines listing at the end of this file.
Verdicts: [V] = proven by verbatim instruction/string, [I] = lead only, [?] = undecoded.

CLOSES?: YES — all pending parts of the item line are proven by [V] rows: slot 54 (queue push, 0x30 request) was already [V]; slot 63 loop body after the checks is now [V] (queue walk, FNV-1 named lookup, mismatch/range strings, releases); slot 64 middle RT dispatch cluster is now [V] (calls to 0xe8542d0/0xe8546c0/0xed360d0 located inside the function).

## Slot 54 — 0xe83d7d0 — queue push (0x30-byte request element) — [V]

| slot54-field | size | address | `0xRVA  instr` proof | meaning | verdict |
|---|---|---|---|---|---|
| [rbp-8] | 2 | e83d81a | `e83d81a  mov [rbp-8],dx` | request field A: u16 | [V] |
| [rbp-4] | 4 | e83d81e | `e83d81e  mov [rbp-4],r8d` | request field B: u32 | [V] |
| [rbp] | 2 | e83d822 | `e83d822  mov [rbp],r9w` | request field C: u16 | [V] |
| [rbp+4] | 4 | e83d827 | `e83d827  mov [rbp+4],r11d` | request field D: u32 | [V] |
| [rbp+8] | 2 | e83d82b | `e83d82b  mov [rbp+8],r10w` | request field E: u16 | [V] |
| [rbp+0xC] | 4 | e83d830 | `e83d830  mov [rbp+0xC],ecx` | request field F: u32 | [V] |
| [rbp+0x10] | 8 | e83d833 | `e83d833  mov [rbp+0x10],rax` | request field G: u64 | [V] |
| [rbp+0x18] | 8 | e83d83e | `e83d83e  mov [rbp+0x18],r15` | element string ptr (empty const data [0xF847A07]) | [V] |
| name-check | 4 | e83d849 | `e83d849  cmp dword ptr [rdi+8],0` | skip name copy when the name field is 0 | [V] |
| name-len | 4 | e83d852 | `e83d852  mov edx,0x7FFFFFFF` | cap name length | [V] |
| name-len-call | 5 | e83d857 | `e83d857  call 0xEBCE610` | string length | [V] |
| name-copy | 5 | e83d8ad | `e83d8ad  call 0xEBCE650` | copy name into request element | [V] |
| request-alloc | 5 | e83d88e | `e83d88e  call qword ptr [0xF99FFA0]` | sub_eea6040 allocator | [V] |
| queue-end | 8 | e83d8be | `e83d8be  mov rdi,[rax+0x3C964C0]` | vector end (ctx+0x3C964C0) | [V] |
| queue-cap | 8 | e83d8c5 | `e83d8c5  cmp rdi,[rax+0x3C964C8]` | end vs cap (ctx+0x3C964C8) | [V] |
| grow-branch | 2 | e83d8cc | `e83d8cc  je 0xE83D95A` | take grow path when full | [V] |
| append-lo | 16 | e83d8d2 | `e83d8d2  movups xmm0,[rbp-8]` | element bytes 0-15 | [V] |
| append-hi | 16 | e83d8d6 | `e83d8d6  movups xmm1,[rbp+8]` | element bytes 16-31 | [V] |
| store-hi | 16 | e83d8da | `e83d8da  movups [rdi+0x10],xmm1` | store element bytes 16-31 | [V] |
| store-lo | 16 | e83d8de | `e83d8de  movups [rdi],xmm0` | store element bytes 0-15 | [V] |
| name-ptr | 8 | e83d8e1 | `e83d8e1  mov [rdi+0x20],r15` | element field: name pointer | [V] |
| namelen-clear | 4 | e83d8e5 | `e83d8e5  mov dword ptr [rdi+0x28],0` | element field: name length cleared | [V] |
| end-stride | 8 | e83da48 | `e83da48  add qword ptr [rax+0x3C964C0],0x30` | end += 0x30 element stride | [V] |
| grow-base | 8 | e83d95a | `e83d95a  add rax,0x3C964B8` | vector base (ctx+0x3C964B8) | [V] |
| alloc-fail | 8 | e83da07 | `e83da07  test rax,rax` | grow alloc failure branch | [V] |
| grow-alloc | 5 | e83d9fd | `e83d9fd  call qword ptr [0xF99FFA0]` | grow realloc via sub_eea6040 | [V] |
| copy-lo | 16 | e83dd75 | `e83dd75  movups xmm0,[r15-0x20]` | grow loop: copy element lo | [V] |
| final-base | 8 | e83dc7b | `e83dc7b  mov [rcx+0x3C964B8],r14` | commit new base | [V] |
| final-end | 8 | e83dc91 | `e83dc91  mov [rcx+0x3C964C0],rax` | commit new end | [V] |
| final-cap | 8 | e83dca3 | `e83dca3  mov [rcx+0x3C964C8],rax` | commit new cap | [V] |
| end | 1 | e83dd05 | `e83dd05  ret` | function epilogue end (~0x535 bytes, not 0x671) | [V] |

## Slot 63 — 0xe83f1d0 — slot-54 queue consumer — [V]

| slot63-field | size | address | `0xRVA  instr` proof | meaning | verdict |
|---|---|---|---|---|---|
| 0x3C5646C | 1 | e83f206 | `e83f206  cmp byte ptr [rcx+0x3C5646C],1` | driver gate byte == 1 | [V] |
| 0x3C964B8 | 8 | e83f216 | `e83f216  mov rax,[rcx+0x3C964B8]` | queue base | [V] |
| 0x3C964C0 | 8 | e83f21d | `e83f21d  cmp rax,[rcx+0x3C964C0]` | queue non-empty: base != end | [V] |
| cmd+0x30 | 8 | e83f22d | `e83f22d  mov rcx,[rdx+0x30]` | command list via [command+0x30] | [V] |
| vtable-dispatch | 5 | e83f242 | `e83f242  call qword ptr [0xF99FFA0]` | indirect call via sub_eea6040 pointer | [V] |
| 0x50 | 4 | e83f258 | `e83f258  mov eax,[rsi+0x50]` | load [ctx+0x50] | [V] |
| 0x415E620 | 4 | e83f25b | `e83f25b  mov [rsi+0x415E620],eax` | store [ctx+0x50] at ring slot ctx+0x415E620 | [V] |
| 0x415E614 | 4 | e83f261 | `e83f261  mov eax,[rsi+0x415E614]` | ring index load | [V] |
| ring-inc | 4 | e83f267 | `e83f267  inc eax` | ring index + 1 | [V] |
| 0x415E60C | 4 | e83f26b | `e83f26b  div dword ptr [rsi+0x415E60C]` | ring index % ring size | [V] |
| ring-store | 4 | e83f271 | `e83f271  mov [rsi+0x415E614],edx` | ring index = (idx+1) % size | [V] |
| count-sar | 8 | e83f299 | `e83f299  sar rax,4` | queue element count = (end-base) >> 4 | [V] |
| workvec-imul | 8 | e83f2c7 | `e83f2c7  imul rdi,rax,0x230` | working vector size (count+1) * 0x230 | [V] |
| elem-idx*3 | 8 | e83f6d9 | `e83f6d9  lea rax,[rbx+rbx*2]` | queue element index * 3 | [V] |
| elem-stride | 8 | e83f6dd | `e83f6dd  shl rax,4` | element byte offset idx * 0x30 | [V] |
| elem-field-A | 2 | e83f6e4 | `e83f6e4  movzx r14d,word ptr [rsi]` | queue element u16 field A | [V] |
| slot-null | 8 | e83f70d | `e83f70d  cmp qword ptr [rdx+r15],0` | named-slot table entry null check | [V] |
| fnv-basis | 8 | e83f73a | `e83f73a  mov rdx,0xBF29CE484222325` | FNV-1a basis xor | [V] |
| fnv-prime | 8 | e83f751 | `e83f751  imul rax,rdx` | FNV-1a prime multiply | [V] |
| fnv-fold | 8 | e83f762 | `e83f762  imul rax,rcx` | fold/high multiply | [V] |
| lookup-dc70 | 5 | e83f7bf | `e83f7bf  call 0xE84DC70` | sub_e84dc70 named-slot lookup | [V] |
| lookup-df40 | 5 | e83f8e4 | `e83f8e4  call 0xE84DF40` | sub_e84df40 named-slot lookup | [V] |
| mismatch-str | 8 | e83fafe | `e83fafe  lea rdx,[0xF5602AD]` | "Type Mismatch in Vertex format used for GPU skinning Vertices of Actor" | [V] |
| mismatch-report | 5 | e83fb05 | `e83fb05  call 0xBC5F110` | report vertex-format mismatch | [V] |
| range-str | 8 | e83fbb0 | `e83fbb0  lea rdx,[0xF7F9F9D]` | "Our skinning vertex buffer is asking for a range that will extend past the end of the buffer" | [V] |
| range-report | 5 | e83fbb7 | `e83fbb7  call 0xBC5F110` | report buffer-range error | [V] |
| release-e935700 | 5 | e83f6b3 | `e83f6b3  call 0xE935700` | sub_e935700 release | [V] |
| release-e8360f0 | 5 | e83fe3a | `e83fe3a  call 0xE8360F0` | sub_e8360f0 release | [V] |

## Slot 64 — 0xe8403d0 — driver gate, named GPU resources, RT dispatch cluster — [V]

| slot64-field | size | address | `0xRVA  instr` proof | meaning | verdict |
|---|---|---|---|---|---|
| 0xF56666A | 8 | e840615 | `e840615  lea rdx,[0xF56666A]` | "SuperSampling.NeedsUpdatedDriver" driver gate query | [V] |
| e840629 | 4 | e840629 | `e840629  and eax,0xFFF00000` | driver version vendor/device mask | [V] |
| e84062e | 4 | e84062e | `e84062e  cmp eax,0xBAD00000` | bad-driver magic compare | [V] |
| e840635 | 4 | e840635 | `e840635  cmp dword ptr [rbp+0x920],0` | driver info present test | [V] |
| 0x3C56418 | 1 | e8406ce | `e8406ce  mov byte ptr [rax+0x3C56418],1` | sets driver-RTX enabled flag at ctx+0x3C56418 | [V] |
| 0x12ADFA54 | 1 | e8406d5 | `e8406d5  or byte ptr [0x12ADFA54],1` | global RTX available flag | [V] |
| 0xF848A8E | 8 | e840762 | `e840762  lea rdx,[0xF848A8E]` | "LPBRTextureData" named resource | [V] |
| e84076f | 5 | e84076f | `e84076f  call 0xE812740` | named GPU resource create via sub_e812740 | [V] |
| 0xF847C42 | 8 | e8407e8 | `e8407e8  lea rdx,[0xF847C42]` | "LCheckerboardActions" named resource | [V] |
| e8407fb | 5 | e8407fb | `e8407fb  call 0xE812740` | named GPU resource create via sub_e812740 | [V] |
| 0xF847D6C | 8 | e8409b3 | `e8409b3  lea rdx,[0xF847D6C]` | "LRefractionIndices" named resource | [V] |
| e8409c6 | 5 | e8409c6 | `e8409c6  call 0xE812740` | named GPU resource create via sub_e812740 | [V] |
| 0xF847CDC | 8 | e840b7c | `e840b7c  lea rdx,[0xF847CDC]` | "LVertexIrradianceCacheUpdates" named resource | [V] |
| e840b89 | 5 | e840b89 | `e840b89  call 0xE812740` | named GPU resource create via sub_e812740 | [V] |
| e847eaa | 5 | e847eaa | `e847eaa  call 0xE8542D0` | RT dispatch call to sub_e8542d0 (first of cluster) | [V] |
| e848cfd | 5 | e848cfd | `e848cfd  call 0xE8542D0` | RT dispatch call to sub_e8542d0 | [V] |
| e849335 | 5 | e849335 | `e849335  call 0xE8542D0` | RT dispatch call to sub_e8542d0 | [V] |
| e84a008 | 5 | e84a008 | `e84a008  call 0xE8542D0` | RT dispatch call to sub_e8542d0 | [V] |
| e84ab9e | 5 | e84ab9e | `e84ab9e  call 0xE8542D0` | RT dispatch call to sub_e8542d0 | [V] |
| e84ad3e | 5 | e84ad3e | `e84ad3e  call 0xE8542D0` | RT dispatch call to sub_e8542d0 (last of cluster) | [V] |
| e84270c | 5 | e84270c | `e84270c  call 0xE8546C0` | resource transition call to sub_e8546c0 | [V] |
| e844783 | 5 | e844783 | `e844783  call 0xE8546C0` | resource transition call to sub_e8546c0 | [V] |
| e847e6d | 5 | e847e6d | `e847e6d  call 0xE8546C0` | resource transition call to sub_e8546c0 | [V] |
| e84ad56 | 5 | e84ad56 | `e84ad56  call 0xE8546C0` | resource transition call to sub_e8546c0 (late) | [V] |
| e84a7ca | 5 | e84a7ca | `e84a7ca  call 0xED360D0` | DLSS evaluate call to sub_ed360d0 | [V] |

## Verbatim proof lines (checked by tools/sigs/verify_oc.py)

e83d81a  mov [rbp-8],dx
e83d81e  mov [rbp-4],r8d
e83d822  mov [rbp],r9w
e83d827  mov [rbp+4],r11d
e83d82b  mov [rbp+8],r10w
e83d830  mov [rbp+0xC],ecx
e83d833  mov [rbp+0x10],rax
e83d83e  mov [rbp+0x18],r15
e83d849  cmp dword ptr [rdi+8],0
e83d852  mov edx,0x7FFFFFFF
e83d857  call 0xEBCE610
e83d8ad  call 0xEBCE650
e83d88e  call qword ptr [0xF99FFA0]
e83d8be  mov rdi,[rax+0x3C964C0]
e83d8c5  cmp rdi,[rax+0x3C964C8]
e83d8cc  je 0xE83D95A
e83d8d2  movups xmm0,[rbp-8]
e83d8d6  movups xmm1,[rbp+8]
e83d8da  movups [rdi+0x10],xmm1
e83d8de  movups [rdi],xmm0
e83d8e1  mov [rdi+0x20],r15
e83d8e5  mov dword ptr [rdi+0x28],0
e83da48  add qword ptr [rax+0x3C964C0],0x30
e83d95a  add rax,0x3C964B8
e83da07  test rax,rax
e83d9fd  call qword ptr [0xF99FFA0]
e83dd75  movups xmm0,[r15-0x20]
e83dc7b  mov [rcx+0x3C964B8],r14
e83dc91  mov [rcx+0x3C964C0],rax
e83dca3  mov [rcx+0x3C964C8],rax
e83dd05  ret
e83f206  cmp byte ptr [rcx+0x3C5646C],1
e83f216  mov rax,[rcx+0x3C964B8]
e83f21d  cmp rax,[rcx+0x3C964C0]
e83f22d  mov rcx,[rdx+0x30]
e83f242  call qword ptr [0xF99FFA0]
e83f258  mov eax,[rsi+0x50]
e83f25b  mov [rsi+0x415E620],eax
e83f261  mov eax,[rsi+0x415E614]
e83f267  inc eax
e83f26b  div dword ptr [rsi+0x415E60C]
e83f271  mov [rsi+0x415E614],edx
e83f299  sar rax,4
e83f2c7  imul rdi,rax,0x230
e83f6d9  lea rax,[rbx+rbx*2]
e83f6dd  shl rax,4
e83f6e4  movzx r14d,word ptr [rsi]
e83f70d  cmp qword ptr [rdx+r15],0
e83f73a  mov rdx,0xBF29CE484222325
e83f751  imul rax,rdx
e83f762  imul rax,rcx
e83f7bf  call 0xE84DC70
e83f8e4  call 0xE84DF40
e83fafe  lea rdx,[0xF5602AD]
e83fb05  call 0xBC5F110
e83fbb0  lea rdx,[0xF7F9F9D]
e83fbb7  call 0xBC5F110
e83f6b3  call 0xE935700
e83fe3a  call 0xE8360F0
e840615  lea rdx,[0xF56666A]
e840629  and eax,0xFFF00000
e84062e  cmp eax,0xBAD00000
e840635  cmp dword ptr [rbp+0x920],0
e8406ce  mov byte ptr [rax+0x3C56418],1
e8406d5  or byte ptr [0x12ADFA54],1
e840762  lea rdx,[0xF848A8E]
e84076f  call 0xE812740
e8407e8  lea rdx,[0xF847C42]
e8407fb  call 0xE812740
e8409b3  lea rdx,[0xF847D6C]
e8409c6  call 0xE812740
e840b7c  lea rdx,[0xF847CDC]
e840b89  call 0xE812740
e847eaa  call 0xE8542D0
e848cfd  call 0xE8542D0
e849335  call 0xE8542D0
e84a008  call 0xE8542D0
e84ab9e  call 0xE8542D0
e84ad3e  call 0xE8542D0
e84270c  call 0xE8546C0
e844783  call 0xE8546C0
e847e6d  call 0xE8546C0
e84ad56  call 0xE8546C0
e84a7ca  call 0xED360D0

Notes: slot 64 spans 0xe8403d0..0xe84ae2b (0xaa5b). rdiscan found 42 call sites to 0xe8542d0 (disp addresses e847eab..e84ad3f) inside this function; six are shown above. 0xe8546c0 transitions (21 sites) and the 0xed360d0 DLSS evaluate (call at e84a7ca) sit inside the same function. ~17 named resources flow through 0xe812740; four are shown above with their name-string lea.

## NEXT
DONE
