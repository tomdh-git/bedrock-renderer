## NEXT
DONE — C5b per-element fill/dest writes and sub_5690960/5690e10/56912d0 decode complete; all [V], verify_oc clean.

# UNIT U-EL3i — L3i drawutils pass-declaration templates (178 signatures) — 6aq; per-pass bodies
# Checklist item C5b (docs/RENDER_CHECKLIST.md); docs/BGFX_MAP.md section 6aq.
# Pending part (this unit, per oc_U-EL3i_r2.md / oc_U-EC5b.md): per-element fill and dest writes of
# the 7 element-loop per-pass bodies sub_5684660 (vtable data_f25b670), sub_567E510,
# sub_567FD70, sub_56815D0, sub_5682E20, sub_5685EA0, sub_56876F0; plus instruction-complete decode
# of the per-element callees sub_5690960, sub_5690e10, sub_56912d0 first.
# All RVAs are Minecraft.Windows.exe 1.26.62.01 image-base RVAs. Static analysis only.
# Proven [V] elsewhere (NOT redone here): entry reads a1+0x10/0x18/0x28/0x60 and 0x290-stride loop
# headers of all 7 bodies; declare machinery sub_5698290/sub_568c4e0 + wrappers flag 1..5.

## PLAN
# (a) Decode sub_5690960, sub_5690e10, sub_56912d0 instruction-complete (rdis dis, chunks of <=1400,
# verify_oc after each). Then (b) per body: per-element fill/dest writes, one table per body,
# sourced reads a1+0x10/0x18/0x28/0x60, 0x290-stride element loop.

## PART (a) — PER-ELEMENT CALLEES sub_5690960 / sub_5690e10 / sub_56912d0 — INSTRUCTION-COMPLETE [V]

Tried: `rdis.exe exe dis 0x5690960 1400` -> docs/progress/pre_5690960.txt (1542 lines). One linear
chunk 0x5690960..0x5691d34 contains all three callees contiguously, each complete with a ret:
sub_5690960 (0x5690960..0x5690d78), sub_5690e10 (0x5690e10..0x569122a),
sub_56912d0 (0x56912d0..0x569176d), then unrelated stubs and sub_5691860 after. Nothing failed:
the single chunk covers all three callees instruction-complete. (sub_5691860 is adjacent in the same
chunk but is NOT one of the three per-element callees and is not part of this item.)

All three callees: args rcx=a0 out-object, rdx=a1, r8=a2, r9=a3. Walk node list at a2+0x40
([node+0]=next, sentinel=address a2+0x40; node+0x10 element start, +0x18 element end, elements
0xC8 stride: +0 dword flags, +8 qword (bit 0x40 required), +0x10 u16 index). Count = sum over
nodes of (end-start)/8 * magic 0x8F5C28F5C28F5C29. Alloc count*0x18 entries via sub_a78940;
release old buffer via lock-dec refcount + dtor call qword ptr [0xF99FFA0] (=sub_eea6040).
Per-element filter: (~[elem+0]) & MASK != 0 -> skip; [elem+8] & 0x40 == 0 -> skip.
On full buffer: sub_5689800 compact, magic min/max clamp, realloc sub_a78940, sub_eec6de0 copy.
Overflow (count >= 0xAAAAAAAAAAAAAAAB): call sub_75b60; int3. Out object *a0: +0x00 = a1,
+0x08 = [a1+0], +0x10 = array base, +0x18 = array start, +0x20 = array end; empty/nothing-written
path zeroes +0x10/+0x20. None of the three callees writes to a1/a2/a3 memory; they only produce the
filtered array in *a0.

### (a-1) sub_5690960 (0x5690960..0x5690d78), frame 0xB8, rbp=rsp+0x80, MASK 0x2007020

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 0x5690960 | 1 | sub_5690960 | - | `0x5690960  push rbp` | function entry | [V] |
| 0x569098c | 8 | sub_5690960 | R a2+0x40 | `0x569098c  mov r8,[r8+0x40]` | first node = [a2+0x40] | [V] |
| 0x56909b0 | 8 | sub_5690960 | R [node+0x18] | `0x56909b0  mov rdx,[rcx+0x18]` | node element end | [V] |
| 0x56909b4 | 8 | sub_5690960 | R [node+0x10] | `0x56909b4  sub rdx,[rcx+0x10]` | end - start (bytes) | [V] |
| 0x56909b8 | 8 | sub_5690960 | R [node+0x0] | `0x56909b8  mov rcx,[rcx]` | next node ([node+0]) | [V] |
| 0x56909bb | 8 | sub_5690960 | - | `0x56909bb  sar rdx,3` | /8 = qwords in node | [V] |
| 0x56909bf | 8 | sub_5690960 | - | `0x56909bf  imul rdx,rax` | * magic 0x8F5C28F5C28F5C29 | [V] |
| 0x56909db | 8 | sub_5690960 | - | `0x56909db  mov rax,0xAAAAAAAAAAAAAAB` | overflow limit | [V] |
| 0x56909e5 | - | sub_5690960 | - | `0x56909e5  cmp rsi,rax` | count >= limit? | [V] |
| 0x56909e8 | - | sub_5690960 | - | `0x56909e8  jae 0x5690D79` | -> sub_75b60; int3 | [V] |
| 0x56909ee | 8 | sub_5690960 | - | `0x56909ee  lea rax,[rsi*8]` | count*8 | [V] |
| 0x56909f6 | 8 | sub_5690960 | - | `0x56909f6  lea r8,[rax+rax*2]` | alloc size = count*0x18 | [V] |
| 0x5690a07 | - | sub_5690960 | - | `0x5690a07  call 0xA78940` | allocate entries | [V] |
| 0x5690a19 | 8 | sub_5690960 | - | `0x5690a19  mov r13,[rax]` | alloc result base | [V] |
| 0x5690a21 | 4 | sub_5690960 | W [rdi+8] | `0x5690a21  lock dec dword ptr [rdi+8]` | release old buffer refcount | [V] |
| 0x5690a30 | - | sub_5690960 | R [0xF99FFA0] | `0x5690a30  call qword ptr [0xF99FFA0]` | dtor sub_eea6040 | [V] |
| 0x5690a6c | 8 | sub_5690960 | W [rbp+0x20] | `0x5690a6c  mov [rbp+0x20],r14` | save a1 | [V] |
| 0x5690aa1 | 8 | sub_5690960 | R [node+0x10] | `0x5690aa1  mov rbx,[r8+0x10]` | element start | [V] |
| 0x5690aa5 | 8 | sub_5690960 | R [node+0x18] | `0x5690aa5  mov r14,[r8+0x18]` | element end | [V] |
| 0x5690afe | 4 | sub_5690960 | R [elem+0x0] | `0x5690afe  mov eax,[rbx]` | element flags | [V] |
| 0x5690b00 | 4 | sub_5690960 | - | `0x5690b00  not eax` | ~flags | [V] |
| 0x5690b02 | - | sub_5690960 | - | `0x5690b02  test eax,0x2007020` | filter mask 0x2007020 | [V] |
| 0x5690b09 | 8 | sub_5690960 | R [elem+0x8] | `0x5690b09  mov rax,[rbx+8]` | element +8 | [V] |
| 0x5690b0d | - | sub_5690960 | - | `0x5690b0d  and eax,0x40` | bit 0x40 required | [V] |
| 0x5690b2b | - | sub_5690960 | - | `0x5690b2b  je short 0x5690AC0` | [node+0]==[node+8] -> store | [V] |
| 0x5690b2d | 1 | sub_5690960 | R [elem+0x0] | `0x5690b2d  test byte ptr [rbx],1` | element bit0 | [V] |
| 0x5690b30 | - | sub_5690960 | - | `0x5690b30  je short 0x5690AC0` | bit0 clear -> store | [V] |
| 0x5690b36 | 8 | sub_5690960 | R [node+0x8B0] | `0x5690b36  mov rax,[rax+0x8B0]` | table pointer | [V] |
| 0x5690b40 | - | sub_5690960 | - | `0x5690b40  je 0x5690AC0` | table null -> store | [V] |
| 0x5690b46 | 2 | sub_5690960 | R table[idx*2] | `0x5690b46  movzx r8d,word ptr [rbx+0x10]` | element+0x10 table index | [V] |
| 0x5690b4b | 2 | sub_5690960 | R table[idx*2] | `0x5690b4b  movzx r8d,word ptr [rax+r8*2]` | table lookup | [V] |
| 0x5690b50 | - | sub_5690960 | - | `0x5690b50  call 0xE93B480` | sub_e93b480 | [V] |
| 0x5690b55 | 8 | sub_5690960 | R [node+0x8] | `0x5690b55  cmp rax,[rsi+8]` | vs [node+8] | [V] |
| 0x5690b59 | - | sub_5690960 | - | `0x5690b59  jne 0x5690AC0` | lookup != [node+8] -> store | [V] |
| 0x5690ac0 | 8 | sub_5690960 | - | `0x5690ac0  mov rcx,[rbp+0xA0]` | sub_56894c0 context | [V] |
| 0x5690ac7 | 8 | sub_5690960 | - | `0x5690ac7  lea rdx,[rbp-0x10]` | element pointer | [V] |
| 0x5690acb | - | sub_5690960 | - | `0x5690acb  call 0x56894C0` | sub_56894c0 -> hash | [V] |
| 0x5690ad0 | 8 | sub_5690960 | - | `0x5690ad0  mov r14,rax` | hash | [V] |
| 0x5690adc | 8 | sub_5690960 | W entry+0x0 | `0x5690adc  mov [r12],r14` | entry+0 = hash | [V] |
| 0x5690ae0 | 16 | sub_5690960 | R elem+0x0 | `0x5690ae0  movups xmm0,[rbp-0x10]` | element bytes +0x0 (16B) | [V] |
| 0x5690ae4 | 16 | sub_5690960 | W entry+0x8 | `0x5690ae4  movups [r12+8],xmm0` | entry+8..0x18 = element bytes | [V] |
| 0x5690aea | 8 | sub_5690960 | - | `0x5690aea  add r12,0x18` | next entry | [V] |
| 0x5690a90 | 8 | sub_5690960 | - | `0x5690a90  mov r8,[rbp+8]` | saved node | [V] |
| 0x5690a94 | 8 | sub_5690960 | R [node+0x0] | `0x5690a94  mov r8,[r8]` | next node | [V] |
| 0x5690a9b | - | sub_5690960 | - | `0x5690a9b  je 0x5690C56` | node list done | [V] |
| 0x5690c86 | - | sub_5690960 | - | `0x5690c86  call 0x5689800` | vector compact (buffer full) | [V] |
| 0x5690cd1 | - | sub_5690960 | - | `0x5690cd1  call 0xA78940` | grow realloc | [V] |
| 0x5690d34 | - | sub_5690960 | - | `0x5690d34  call 0xEEC6DE0` | copy old entries into new buffer | [V] |
| 0x5690c93 | 8 | sub_5690960 | W *a0+0x0 | `0x5690c93  mov [r15],rax` | *a0+0 = a1 | [V] |
| 0x5690c9a | 8 | sub_5690960 | W *a0+0x8 | `0x5690c9a  mov [r15+8],rcx` | *a0+8 = [a1+0] | [V] |
| 0x5690ca1 | 16 | sub_5690960 | W *a0+0x10 | `0x5690ca1  movups [r15+0x10],xmm0` | *a0+0x10 = 0 (empty path) | [V] |
| 0x5690ca6 | 8 | sub_5690960 | W *a0+0x20 | `0x5690ca6  mov qword ptr [r15+0x20],0` | *a0+0x20 = 0 (empty path) | [V] |
| 0x5690d1b | 8 | sub_5690960 | W *a0+0x10 | `0x5690d1b  mov [r15+0x10],rbx` | *a0+0x10 = array base | [V] |
| 0x5690d1f | 8 | sub_5690960 | W *a0+0x18 | `0x5690d1f  mov [r15+0x18],rbx` | *a0+0x18 = array start | [V] |
| 0x5690d23 | 8 | sub_5690960 | - | `0x5690d23  lea rsi,[rbx+rdi]` | array end = base + bytes written | [V] |
| 0x5690d27 | 8 | sub_5690960 | W *a0+0x20 | `0x5690d27  mov [r15+0x20],rsi` | *a0+0x20 = array end | [V] |
| 0x5690d47 | 8 | sub_5690960 | W *a0+0x0 | `0x5690d47  mov [r15],rax` | *a0+0 = a1 (nothing-written path) | [V] |
| 0x5690d4e | 8 | sub_5690960 | W *a0+0x8 | `0x5690d4e  mov [r15+8],rax` | *a0+8 = [a1+0] (nothing-written path) | [V] |
| 0x5690d55 | 16 | sub_5690960 | W *a0+0x10 | `0x5690d55  movups [r15+0x10],xmm0` | *a0+0x10 = 0 (nothing-written path) | [V] |
| 0x5690d5a | 8 | sub_5690960 | W *a0+0x20 | `0x5690d5a  mov qword ptr [r15+0x20],0` | *a0+0x20 = 0 (nothing-written path) | [V] |
| 0x5690d78 | - | sub_5690960 | - | `0x5690d78  ret` | function end | [V] |

sub_5690960 accept/store gate (proven by the rows above): store when (~flags)&0x2007020==0 AND
[elem+8]&0x40!=0 AND ( [node+0]==[node+8] OR bit0 of [elem+0]==0 OR [node+0x8B0]==0 OR
sub_e93b480(*[node+0x8B0], u16[elem+0x10]) != [[node+8]] ). Store entry 0x18 bytes:
{sub_56894c0 hash qword, element bytes +0x0..0xF (movups)}. Reject otherwise (advance element by 0xC8).

### (a-2) sub_5690e10 (0x5690e10..0x569122a), frame 0xA8, MASK 0x2407020

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 0x5690e10 | 1 | sub_5690e10 | - | `0x5690e10  push rbp` | function entry | [V] |
| 0x5690e3c | 8 | sub_5690e10 | R a2+0x40 | `0x5690e3c  mov r15,[r8+0x40]` | first node = [a2+0x40] | [V] |
| 0x5690e60 | 8 | sub_5690e10 | R [node+0x18] | `0x5690e60  mov rdx,[rcx+0x18]` | node element end | [V] |
| 0x5690e64 | 8 | sub_5690e10 | R [node+0x10] | `0x5690e64  sub rdx,[rcx+0x10]` | end - start | [V] |
| 0x5690e68 | 8 | sub_5690e10 | R [node+0x0] | `0x5690e68  mov rcx,[rcx]` | next node | [V] |
| 0x5690e6b | 8 | sub_5690e10 | - | `0x5690e6b  sar rdx,3` | /8 | [V] |
| 0x5690e6f | 8 | sub_5690e10 | - | `0x5690e6f  imul rdx,rax` | * magic | [V] |
| 0x5690e8b | 8 | sub_5690e10 | - | `0x5690e8b  mov rax,0xAAAAAAAAAAAAAAB` | overflow limit | [V] |
| 0x5690e95 | - | sub_5690e10 | - | `0x5690e95  cmp rsi,rax` | count >= limit? | [V] |
| 0x5690e98 | - | sub_5690e10 | - | `0x5690e98  jae 0x569122B` | -> sub_75b60; int3 | [V] |
| 0x5690e9e | 8 | sub_5690e10 | - | `0x5690e9e  lea rax,[rsi*8]` | count*8 | [V] |
| 0x5690ea6 | 8 | sub_5690e10 | - | `0x5690ea6  lea r8,[rax+rax*2]` | alloc size = count*0x18 | [V] |
| 0x5690eb7 | - | sub_5690e10 | - | `0x5690eb7  call 0xA78940` | allocate entries | [V] |
| 0x5690ed1 | 4 | sub_5690e10 | W [r15+8] | `0x5690ed1  lock dec dword ptr [r15+8]` | release old buffer refcount | [V] |
| 0x5690ee1 | - | sub_5690e10 | R [0xF99FFA0] | `0x5690ee1  call qword ptr [0xF99FFA0]` | dtor sub_eea6040 | [V] |
| 0x5690f5d | 8 | sub_5690e10 | R [node+0x10] | `0x5690f5d  mov r14,[r15+0x10]` | element start | [V] |
| 0x5690f61 | 8 | sub_5690e10 | R [node+0x18] | `0x5690f61  mov r8,[r15+0x18]` | element end | [V] |
| 0x5690fb7 | 4 | sub_5690e10 | R [elem+0x0] | `0x5690fb7  mov rax,[r14]` | element flags | [V] |
| 0x5690fbc | 4 | sub_5690e10 | - | `0x5690fbc  not ecx` | ~flags | [V] |
| 0x5690fbe | - | sub_5690e10 | - | `0x5690fbe  test ecx,0x2407020` | filter mask 0x2407020 | [V] |
| 0x5690fc6 | 8 | sub_5690e10 | R [elem+0x8] | `0x5690fc6  mov rcx,[r14+8]` | element +8 | [V] |
| 0x5690fca | - | sub_5690e10 | - | `0x5690fca  and ecx,0x40` | bit 0x40 required | [V] |
| 0x5690fcf | 1 | sub_5690e10 | R [elem+0x0] | `0x5690fcf  test al,1` | (~flags)&1: flags bit0 set -> store | [V] |
| 0x5690fd1 | - | sub_5690e10 | - | `0x5690fd1  je short 0x5690F80` | flags bit0 set -> store | [V] |
| 0x5690fd3 | 8 | sub_5690e10 | R [[a3]+0x0] | `0x5690fd3  mov rdi,[rbx]` | rbx = a3; rdi = [a3] | [V] |
| 0x5690fd6 | 8 | sub_5690e10 | R [[a3]+0x0] | `0x5690fd6  mov rcx,[rdi]` | [[a3]] | [V] |
| 0x5690fd9 | 8 | sub_5690e10 | R [[a3]+0x8] | `0x5690fd9  mov rdx,[rdi+8]` | [[a3]+8] | [V] |
| 0x5690fdd | - | sub_5690e10 | - | `0x5690fdd  cmp rcx,rdx` | [[a3]] == [[a3]+8]? | [V] |
| 0x5690fe0 | - | sub_5690e10 | - | `0x5690fe0  je short 0x5690F80` | equal -> store | [V] |
| 0x5690fe2 | 8 | sub_5690e10 | R [node+0x8B0] | `0x5690fe2  mov rax,[r15+0x8B0]` | table pointer | [V] |
| 0x5690fec | - | sub_5690e10 | - | `0x5690fec  je short 0x5690F80` | table null -> store | [V] |
| 0x5690fee | 2 | sub_5690e10 | R [elem+0x10] | `0x5690fee  movzx r8d,word ptr [r14+0x10]` | element+0x10 table index | [V] |
| 0x5690ff3 | 2 | sub_5690e10 | R table[idx*2] | `0x5690ff3  movzx r8d,word ptr [rax+r8*2]` | table lookup | [V] |
| 0x5690ff8 | - | sub_5690e10 | - | `0x5690ff8  call 0xE93B480` | sub_e93b480 | [V] |
| 0x5691001 | 8 | sub_5690e10 | R [[a3]+0x8] | `0x5691001  cmp rax,[rdi+8]` | vs [[a3]+8] | [V] |
| 0x5691005 | - | sub_5690e10 | - | `0x5691005  jne 0x5690F80` | lookup != [[a3]+8] -> store | [V] |
| 0x5690f80 | 2 | sub_5690e10 | R [elem+0x3C] | `0x5690f80  movzx eax,word ptr [r14+0x3C]` | element+0x3C table index | [V] |
| 0x5690f85 | 8 | sub_5690e10 | R [node+0x6A0] | `0x5690f85  mov rcx,[r15+0x6A0]` | node+0x6A0 table base | [V] |
| 0x5690f8c | 2 | sub_5690e10 | R table[idx*2] | `0x5690f8c  movzx edi,word ptr [rcx+rax*2]` | entry word from table | [V] |
| 0x5690f95 | 8 | sub_5690e10 | W entry+0x0 | `0x5690f95  mov [r12],rdi` | entry+0 = table word (zext) | [V] |
| 0x5690f99 | 8 | sub_5690e10 | W entry+0x8 | `0x5690f99  mov [r12+8],r14` | entry+8 = element pointer | [V] |
| 0x5690f9e | 8 | sub_5690e10 | R [rbp-8] | `0x5690f9e  mov rax,[rbp-8]` | &node+0x28 | [V] |
| 0x5690fa2 | 8 | sub_5690e10 | W entry+0x10 | `0x5690fa2  mov [r12+0x10],rax` | entry+0x10 = &node+0x28 | [V] |
| 0x5690fa7 | 8 | sub_5690e10 | - | `0x5690fa7  add r12,0x18` | next entry | [V] |
| 0x5691142 | - | sub_5690e10 | - | `0x5691142  call 0x5689800` | vector compact (buffer full) | [V] |
| 0x5691189 | - | sub_5690e10 | - | `0x5691189  call 0xA78940` | grow realloc | [V] |
| 0x56911ea | - | sub_5690e10 | - | `0x56911ea  call 0xEEC6DE0` | copy old entries into new buffer | [V] |
| 0x569114b | 8 | sub_5690e10 | W *a0+0x0 | `0x569114b  mov [r15],r14` | *a0+0 = a1 | [V] |
| 0x5691152 | 8 | sub_5690e10 | W *a0+0x8 | `0x5691152  mov [r15+8],rcx` | *a0+8 = [a1+0] | [V] |
| 0x5691159 | 16 | sub_5690e10 | W *a0+0x10 | `0x5691159  movups [r15+0x10],xmm0` | *a0+0x10 = 0 | [V] |
| 0x569115e | 8 | sub_5690e10 | W *a0+0x20 | `0x569115e  mov qword ptr [r15+0x20],0` | *a0+0x20 = 0 | [V] |
| 0x56911d1 | 8 | sub_5690e10 | W *a0+0x10 | `0x56911d1  mov [r15+0x10],r14` | *a0+0x10 = array base | [V] |
| 0x56911d5 | 8 | sub_5690e10 | W *a0+0x18 | `0x56911d5  mov [r15+0x18],r14` | *a0+0x18 = array start | [V] |
| 0x56911d9 | 8 | sub_5690e10 | - | `0x56911d9  lea rsi,[r14+rbx]` | array end | [V] |
| 0x56911dd | 8 | sub_5690e10 | W *a0+0x20 | `0x56911dd  mov [r15+0x20],rsi` | *a0+0x20 = array end | [V] |
| 0x56911f9 | 8 | sub_5690e10 | W *a0+0x0 | `0x56911f9  mov [r15],r14` | *a0+0 = a1 (nothing-written path) | [V] |
| 0x5691200 | 8 | sub_5690e10 | W *a0+0x8 | `0x5691200  mov [r15+8],rax` | *a0+8 = [a1+0] (nothing-written path) | [V] |
| 0x5691207 | 16 | sub_5690e10 | W *a0+0x10 | `0x5691207  movups [r15+0x10],xmm0` | *a0+0x10 = 0 (nothing-written path) | [V] |
| 0x569120c | 8 | sub_5690e10 | W *a0+0x20 | `0x569120c  mov qword ptr [r15+0x20],0` | *a0+0x20 = 0 (nothing-written path) | [V] |
| 0x569122a | - | sub_5690e10 | - | `0x569122a  ret` | function end | [V] |

sub_5690e10 accept/store gate: store when (~flags)&0x2407020==0 AND [elem+8]&0x40!=0 AND
( (~flags)&1==1 i.e. [elem] bit0 set OR [[a3]]==[[a3]+8] OR [node+0x8B0]==0 OR
sub_e93b480(*[node+0x8B0], u16[elem+0x10]) != [[a3]+8] ). Store entry 0x18 bytes:
{word = [node+0x6A0 + u16[elem+0x3C]*2] zext, element pointer, &node+0x28}. Reject otherwise.

### (a-3) sub_56912d0 (0x56912d0..0x569176d), frame 0xC8, xmm6 saved at [rbp+0x30], MASK 0x2807020

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 0x56912d0 | 1 | sub_56912d0 | - | `0x56912d0  push rbp` | function entry | [V] |
| 0x56912eb | 16 | sub_56912d0 | W [rbp+0x30] | `0x56912eb  movapd [rbp+0x30],xmm6` | save xmm6 scale register | [V] |
| 0x5691301 | 8 | sub_56912d0 | R a2+0x40 | `0x5691301  mov r15,[r8+0x40]` | first node = [a2+0x40] | [V] |
| 0x5691330 | 8 | sub_56912d0 | R [node+0x18] | `0x5691330  mov rdx,[rcx+0x18]` | node element end | [V] |
| 0x5691334 | 8 | sub_56912d0 | R [node+0x10] | `0x5691334  sub rdx,[rcx+0x10]` | end - start | [V] |
| 0x5691338 | 8 | sub_56912d0 | R [node+0x0] | `0x5691338  mov rcx,[rcx]` | next node | [V] |
| 0x569133b | 8 | sub_56912d0 | - | `0x569133b  sar rdx,3` | /8 | [V] |
| 0x569133f | 8 | sub_56912d0 | - | `0x569133f  imul rdx,rax` | * magic | [V] |
| 0x569135b | 8 | sub_56912d0 | - | `0x569135b  mov rax,0xAAAAAAAAAAAAAAB` | overflow limit | [V] |
| 0x5691365 | - | sub_56912d0 | - | `0x5691365  cmp rsi,rax` | count >= limit? | [V] |
| 0x5691368 | - | sub_56912d0 | - | `0x5691368  jae 0x569176E` | -> sub_75b60; int3 | [V] |
| 0x569136e | 8 | sub_56912d0 | - | `0x569136e  lea rax,[rsi*8]` | count*8 | [V] |
| 0x5691376 | 8 | sub_56912d0 | - | `0x5691376  lea r8,[rax+rax*2]` | alloc size = count*0x18 | [V] |
| 0x5691387 | - | sub_56912d0 | - | `0x5691387  call 0xA78940` | allocate entries | [V] |
| 0x56913a1 | 4 | sub_56912d0 | W [r15+8] | `0x56913a1  lock dec dword ptr [r15+8]` | release old buffer refcount | [V] |
| 0x56913b1 | - | sub_56912d0 | R [0xF99FFA0] | `0x56913b1  call qword ptr [0xF99FFA0]` | dtor sub_eea6040 | [V] |
| 0x569140b | 8 | sub_56912d0 | R [data_f25b278] | `0x569140b  movsd xmm6,[0xF25B278]` | distance scale double constant | [I] |
| 0x569142d | 8 | sub_56912d0 | R [node+0x10] | `0x569142d  mov r14,[r15+0x10]` | element start | [V] |
| 0x5691431 | 8 | sub_56912d0 | R [node+0x18] | `0x5691431  mov r8,[r15+0x18]` | element end | [V] |
| 0x56914e6 | 4 | sub_56912d0 | R [elem+0x0] | `0x56914e6  mov rax,[r14]` | element flags | [V] |
| 0x56914eb | 4 | sub_56912d0 | - | `0x56914eb  not ecx` | ~flags | [V] |
| 0x56914ed | - | sub_56912d0 | - | `0x56914ed  test ecx,0x2807020` | filter mask 0x2807020 | [V] |
| 0x56914f5 | 8 | sub_56912d0 | R [elem+0x8] | `0x56914f5  mov rcx,[r14+8]` | element +8 | [V] |
| 0x56914f9 | - | sub_56912d0 | - | `0x56914f9  and ecx,0x40` | bit 0x40 required | [V] |
| 0x56914fe | 1 | sub_56912d0 | R [elem+0x0] | `0x56914fe  test al,1` | (~flags)&1: flags bit0 set -> accept | [V] |
| 0x5691500 | - | sub_56912d0 | - | `0x5691500  je 0x5691450` | flags bit0 set -> accept path | [V] |
| 0x5691506 | 8 | sub_56912d0 | R [[a3]+0x0] | `0x5691506  mov rdi,[rbx]` | rbx = a3; rdi = [a3] | [V] |
| 0x5691509 | 8 | sub_56912d0 | R [[a3]+0x0] | `0x5691509  mov rcx,[rdi]` | [[a3]] | [V] |
| 0x569150c | 8 | sub_56912d0 | R [[a3]+0x8] | `0x569150c  mov rdx,[rdi+8]` | [[a3]+8] | [V] |
| 0x5691510 | - | sub_56912d0 | - | `0x5691510  cmp rcx,rdx` | [[a3]] == [[a3]+8]? | [V] |
| 0x5691513 | - | sub_56912d0 | - | `0x5691513  je 0x5691450` | equal -> accept path | [V] |
| 0x5691519 | 8 | sub_56912d0 | R [node+0x8B0] | `0x5691519  mov rax,[r15+0x8B0]` | table pointer | [V] |
| 0x5691523 | - | sub_56912d0 | - | `0x5691523  je 0x5691450` | table null -> accept path | [V] |
| 0x5691529 | 2 | sub_56912d0 | R [elem+0x10] | `0x5691529  movzx r8d,word ptr [r14+0x10]` | element+0x10 table index | [V] |
| 0x569152e | 2 | sub_56912d0 | R table[idx*2] | `0x569152e  movzx r8d,word ptr [rax+r8*2]` | table lookup | [V] |
| 0x5691533 | - | sub_56912d0 | - | `0x5691533  call 0xE93B480` | sub_e93b480 | [V] |
| 0x569153c | 8 | sub_56912d0 | R [[a3]+0x8] | `0x569153c  cmp rax,[rdi+8]` | vs [[a3]+8] | [V] |
| 0x5691540 | - | sub_56912d0 | - | `0x5691540  jne 0x5691450` | lookup != [[a3]+8] -> accept path | [V] |
| 0x5691450 | 2 | sub_56912d0 | R [elem+0x3E] | `0x5691450  movzx eax,word ptr [r14+0x3E]` | element+0x3E table index | [V] |
| 0x5691455 | 8 | sub_56912d0 | R [node+0x688] | `0x5691455  mov rcx,[r15+0x688]` | node+0x688 float3 table base | [V] |
| 0x569145c | 8 | sub_56912d0 | - | `0x569145c  lea rax,[rax+rax*2]` | index*3 | [V] |
| 0x5691460 | 8 | sub_56912d0 | R [rbp+0xB0] | `0x5691460  mov rdx,[rbp+0xB0]` | center pointer stack slot | [V] |
| 0x5691467 | 8 | sub_56912d0 | R [[rbp+0xB0]] | `0x5691467  mov rdx,[rdx]` | center pointer | [V] |
| 0x569146a | 4 | sub_56912d0 | R table[idx*4+8] | `0x569146a  movss xmm0,[rcx+rax*4+8]` | table float3 z vs center+0xA0 | [V] |
| 0x5691470 | 4 | sub_56912d0 | R [center+0xA0] | `0x5691470  subss xmm0,[rdx+0xA0]` | delta z | [V] |
| 0x5691478 | 4 | sub_56912d0 | R table[idx*4+0] | `0x5691478  movss xmm1,[rcx+rax*4]` | table float3 x | [V] |
| 0x569148b | 4 | sub_56912d0 | R [center+0x98] | `0x569148b  subss xmm1,[rdx+0x98]` | delta x | [V] |
| 0x569147d | 4 | sub_56912d0 | R table[idx*4+4] | `0x569147d  movss xmm2,[rcx+rax*4+4]` | table float3 y | [V] |
| 0x5691483 | 4 | sub_56912d0 | R [center+0x9C] | `0x5691483  subss xmm2,[rdx+0x9C]` | delta y | [V] |
| 0x5691493 | 4 | sub_56912d0 | - | `0x5691493  mulss xmm0,xmm0` | dz*dz | [V] |
| 0x5691497 | 4 | sub_56912d0 | - | `0x5691497  mulss xmm2,xmm2` | dy*dy | [V] |
| 0x569149b | 4 | sub_56912d0 | - | `0x569149b  mulss xmm1,xmm1` | dx*dx | [V] |
| 0x569149f | 4 | sub_56912d0 | - | `0x569149f  addss xmm1,xmm2` | dx^2+dy^2 | [V] |
| 0x56914a3 | 4 | sub_56912d0 | - | `0x56914a3  addss xmm1,xmm0` | dist^2 | [V] |
| 0x56914aa | 8 | sub_56912d0 | - | `0x56914aa  cvtss2sd xmm0,xmm1` | dist^2 to double | [V] |
| 0x56914ae | 8 | sub_56912d0 | - | `0x56914ae  mulsd xmm0,xmm6` | * scale constant | [V] |
| 0x56914b2 | 8 | sub_56912d0 | - | `0x56914b2  cvttsd2si rdi,xmm0` | entry distance (int) | [V] |
| 0x56914c0 | 8 | sub_56912d0 | W entry+0x0 | `0x56914c0  mov [r12],rdi` | entry+0 = distance int | [V] |
| 0x56914c4 | 8 | sub_56912d0 | W entry+0x8 | `0x56914c4  mov [r12+8],r14` | entry+8 = element pointer | [V] |
| 0x56914c9 | 8 | sub_56912d0 | R [rbp] | `0x56914c9  mov rax,[rbp]` | &node+0x28 | [V] |
| 0x56914cd | 8 | sub_56912d0 | W entry+0x10 | `0x56914cd  mov [r12+0x10],rax` | entry+0x10 = &node+0x28 | [V] |
| 0x56914d2 | 8 | sub_56912d0 | - | `0x56914d2  add r12,0x18` | next entry | [V] |
| 0x569167d | - | sub_56912d0 | - | `0x569167d  call 0x5689800` | vector compact (buffer full) | [V] |
| 0x56916c6 | - | sub_56912d0 | - | `0x56916c6  call 0xA78940` | grow realloc | [V] |
| 0x5691727 | - | sub_56912d0 | - | `0x5691727  call 0xEEC6DE0` | copy old entries into new buffer | [V] |
| 0x5691736 | 8 | sub_56912d0 | W *a0+0x0 | `0x5691736  mov [r15],r14` | *a0+0 = a1 | [V] |
| 0x569173d | 8 | sub_56912d0 | W *a0+0x8 | `0x569173d  mov [r15+8],rax` | *a0+8 = [a1+0] | [V] |
| 0x5691741 | 16 | sub_56912d0 | W *a0+0x10 | `0x5691741  xorpd xmm0,xmm0` | zero | [V] |
| 0x5691745 | 16 | sub_56912d0 | W *a0+0x10 | `0x5691745  movupd [r15+0x10],xmm0` | *a0+0x10 = 0 (16B) | [V] |
| 0x569174b | 8 | sub_56912d0 | W *a0+0x20 | `0x569174b  mov qword ptr [r15+0x20],0` | *a0+0x20 = 0 | [V] |
| 0x569170e | 8 | sub_56912d0 | W *a0+0x10 | `0x569170e  mov [r15+0x10],r14` | *a0+0x10 = array base | [V] |
| 0x5691712 | 8 | sub_56912d0 | W *a0+0x18 | `0x5691712  mov [r15+0x18],r14` | *a0+0x18 = array start | [V] |
| 0x5691716 | 8 | sub_56912d0 | - | `0x5691716  lea rsi,[r14+rbx]` | array end | [V] |
| 0x569171a | 8 | sub_56912d0 | W *a0+0x20 | `0x569171a  mov [r15+0x20],rsi` | *a0+0x20 = array end | [V] |
| 0x569172c | 8 | sub_56912d0 | W *a0+0x18 | `0x569172c  mov [r15+0x18],rsi` | *a0+0x18 refreshed after copy | [V] |
| 0x569176d | - | sub_56912d0 | - | `0x569176d  ret` | function end | [V] |

sub_56912d0 accept/store gate: skip when (~flags)&0x2807020!=0 or [elem+8]&0x40==0; otherwise accept
(distance-filter entry) when [elem] bit0 set OR [[a3]]==[[a3]+8] OR [node+0x8B0]==0 OR
sub_e93b480(*[node+0x8B0], u16[elem+0x10]) != [[a3]+8]. Accept entry 0x18 bytes:
{distance int = (int)((dist^2 table float3 at node+0x688[idx*3] minus center float3) * [data_f25b278]),
element pointer, &node+0x28}, idx = u16[elem+0x3E], center floats at center+0x98/0x9C/0xA0 where
center = [rbp+0xB0]. Reject otherwise (advance element by 0xC8).

### (a) RESULT

All three per-element callees decoded instruction-complete: each function body is listed from entry
to its `ret` (0x5690d78 / 0x569122a / 0x569176d) with every basic block covered by the rows above;
every quoted instruction line verified against the exe by verify_oc. Callees write only *a0 and
locals; they never write a1/a2/a3 memory.

CLOSES?: NO — part (a) is [V]; the single blocking fact remaining is part (b): per-element fill
and dest writes of the 7 element-loop bodies (sub_5684660 vtable data_f25b670; sub_567E510
data_f25b4f0; sub_567FD70 data_f25b550; sub_56815D0 data_f25b5b0; sub_5682E20 data_f25b610;
sub_5685EA0 data_f25b6d0; sub_56876F0 data_f25b730) are not yet decoded. Next: rdis dis of each
body around its call sites to 0x5690960 / 0x5690e10 / 0x56912d0 (e.g. sub_5684660 sites
0x56848b0 / 0x56848e3 / 0x568491d / 0x5684970), one table per body, then verify_oc.

## PART (b) — PER-ELEMENT FILL / DEST WRITES OF THE 7 ELEMENT-LOOP BODIES

### (b-1) sub_5684660 (vtable data_f25b670) — [V]

Structure proven: args rcx=caller dest pointer, rdx=a1, r8, r9. Entry saves [rbp+0x8B8]=rcx (caller dest). Outer loop: element cursor r14 walks [a1+0x10]..[a1+0x18] by 0x290 stride (`0x56846fb add r14,0x290`; loop head `0x5684702 cmp r14,[rbp+0x8E0]` where [rbp+0x8E0]=[a1+0x18]); per element data base = r14+0x240. Per element: walk node list at [a1+8]+0xA10 (nodes [rbx+0x10]=start, [rbx+0x18]=end, elements 0xC8 stride; filter `test byte [r15],0x20` / `mov rax,[r15+8]; and eax,0x40`); on pass, call one of sub_5690960 / sub_5690e10 / sub_56912d0 selected by flavor byte [rbp+0x964] (0/1/>=2), build a per-element record at rbp+0x560 (header) and rbp+0x5A0.. (fields), copy callee output array to record dest [rbp+0x5E8..0x5F8], then write the pass record to the caller dest via sub_568b0d0(rcx=[rbp+0x8B8]=caller dest, rdx=&[rbp-0x50]=callee out-object, r8=0) and to side records via sub_655CEA0(rcx=&[rbp-0x30]) and (inside the per-entry loop over callee output entries) sub_655CEA0(rcx=&[rbp+0x5A0], node-buffer entry at [rbp+0x940]+count*0x18).

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 0x5684660 | 1 | sub_5684660 | - | `0x5684660  push rbp` | function entry | [V] |
| 0x5684694 | 8 | sub_5684660 | W [rbp+0x8B8] | `0x5684694  mov [rbp+0x8B8],rcx` | save caller dest pointer (arg rcx) | [V] |
| 0x56846a2 | 8 | sub_5684660 | R a1+0x10 | `0x56846a2  mov r14,[rdx+0x10]` | element cursor = [a1+0x10] | [V] |
| 0x56846a6 | 8 | sub_5684660 | R a1+0x18 | `0x56846a6  mov rax,[rdx+0x18]` | element end = [a1+0x18] | [V] |
| 0x56846aa | 8 | sub_5684660 | W [rbp+0x8E0] | `0x56846aa  mov [rbp+0x8E0],rax` | loop end saved | [V] |
| 0x56846b1 | 8 | sub_5684660 | R a1+0x28 | `0x56846b1  lea rax,[rdx+0x28]` | a1+0x28 | [V] |
| 0x56846b5 | 8 | sub_5684660 | W [rbp+0x8D0] | `0x56846b5  mov [rbp+0x8D0],rax` | | [V] |
| 0x56846bc | 8 | sub_5684660 | W rbp+0x7B8 | `0x56846bc  lea r15,[rbp+0x7B8]` | record base r15 | [V] |
| 0x56846c3 | 8 | sub_5684660 | - | `0x56846c3  add r9,8` | a3 adjust | [V] |
| 0x56846c7 | 8 | sub_5684660 | W [rbp+0x8E8] | `0x56846c7  mov [rbp+0x8E8],r9` | | [V] |
| 0x56846d1 | 8 | sub_5684660 | W [rbp+0x958] | `0x56846d1  mov [rbp+0x958],rdx` | save a1 | [V] |
| 0x56846d8 | 8 | sub_5684660 | R a1+0x60 | `0x56846d8  lea rax,[rdx+0x60]` | a1+0x60 | [V] |
| 0x56846dc | 8 | sub_5684660 | W [rbp+0x8D8] | `0x56846dc  mov [rbp+0x8D8],rax` | | [V] |
| 0x56846e3 | 4 | sub_5684660 | W [rbp+0x964] | `0x56846e3  mov [rbp+0x964],r8d` | pass flavor flag (0/1/>=2 selects callee) | [V] |
| 0x5684702 | - | sub_5684660 | - | `0x5684702  cmp r14,[rbp+0x8E0]` | element cursor vs end | [V] |
| 0x5684709 | - | sub_5684660 | - | `0x5684709  je 0x5685AD7` | outer loop exit | [V] |
| 0x568470f | 8 | sub_5684660 | R elem base | `0x568470f  lea rsi,[r14+0x240]` | element data base = cursor+0x240 | [V] |
| 0x5684716 | 1 | sub_5684660 | R [rbp+0xA08] | `0x5684716  cmp byte ptr [rbp+0xA08],0` | | [V] |
| 0x56846fb | - | sub_5684660 | - | `0x56846fb  add r14,0x290` | next element (0x290 stride) | [V] |
| 0x568472a | 8 | sub_5684660 | R [a1+8] | `0x568472a  mov rdi,[rax+8]` | node list head = [a1+8] ([rbp+0x958]=a1) | [V] |
| 0x568472e | 8 | sub_5684660 | - | `0x568472e  lea rax,[0xF25B670]` | vtable data_f25b670 | [I] |
| 0x5684735 | 8 | sub_5684660 | W block+0x0 | `0x5684735  mov [rbp+0x560],rax` | block header+0 = vtable data_f25b670 | [V] |
| 0x568473c | 8 | sub_5684660 | W block+0x8 | `0x568473c  mov [rbp+0x568],rsi` | block header+8 = element data base | [V] |
| 0x568474a | 8 | sub_5684660 | W [rbp+0x598] | `0x568474a  mov [rbp+0x598],rax` | block pointer = &[rbp+0x560] | [V] |
| 0x5684751 | 8 | sub_5684660 | R [node_list+0xA10] | `0x5684751  mov rbx,[rdi+0xA10]` | first node | [V] |
| 0x5684758 | 8 | sub_5684660 | - | `0x5684758  add rdi,0xA10` | advance node list pointer | [V] |
| 0x5684762 | - | sub_5684660 | - | `0x5684762  jne short 0x568479C` | node list non-empty | [V] |
| 0x568479c | 8 | sub_5684660 | R [node+0x10] | `0x568479c  mov r15,[rbx+0x10]` | node element start | [V] |
| 0x56847a0 | 8 | sub_5684660 | R [node+0x18] | `0x56847a0  mov r12,[rbx+0x18]` | node element end | [V] |
| 0x56847b0 | 8 | sub_5684660 | - | `0x56847b0  add r15,0xC8` | next element (0xC8 stride) | [V] |
| 0x56847bc | 1 | sub_5684660 | R [elem+0x0] | `0x56847bc  test byte ptr [r15],0x20` | element flag filter bit 0x20 | [V] |
| 0x56847c2 | 8 | sub_5684660 | R [elem+0x8] | `0x56847c2  mov rax,[r15+8]` | element +8 | [V] |
| 0x56847c6 | - | sub_5684660 | - | `0x56847c6  and eax,0x40` | bit 0x40 required | [V] |
| 0x56847c9 | - | sub_5684660 | - | `0x56847c9  je short 0x56847B0` | filter fail → next element | [V] |
| 0x56847d7 | 8 | sub_5684660 | W [rbp-0x50] | `0x56847d7  mov [rbp-0x50],r15` | save element ptr (= callee out-object addr) | [V] |
| 0x56847db | 8 | sub_5684660 | W [rbp-0x48] | `0x56847db  mov [rbp-0x48],r13` | save node pointer | [V] |
| 0x56847df | 8 | sub_5684660 | R [block] | `0x56847df  mov rax,[rcx]` | block object | [V] |
| 0x56847e2 | 8 | sub_5684660 | R [block+0x10] | `0x56847e2  mov rax,[rax+0x10]` | block vtable+0x10 | [V] |
| 0x56847e6 | 8 | sub_5684660 | W [rbp-0x50] | `0x56847e6  lea rdx,[rbp-0x50]` | | [V] |
| 0x56847ea | - | sub_5684660 | R [0xF99FFA0] | `0x56847ea  call qword ptr [0xF99FFA0]` | release old block refcount (sub_eea6040) | [V] |
| 0x56847f5 | 1 | sub_5684660 | - | `0x56847f5  mov dil,1` | element accepted flag | [V] |
| 0x56847f8 | 8 | sub_5684660 | R [rbp+0x598] | `0x56847f8  mov rcx,[rbp+0x598]` | block pointer | [V] |
| 0x5684812 | 8 | sub_5684660 | R [block+0x20] | `0x5684812  mov rax,[rcx]` | block object+0x20 | [V] |
| 0x5684826 | - | sub_5684660 | R [0xF99FFA0] | `0x5684826  call qword ptr [0xF99FFA0]` | release old block (sub_eea6040) | [V] |
| 0x5684850 | - | sub_5684660 | - | `0x5684850  cmp dword ptr [rbp+0x964],3` | flavor < 3? | [V] |
| 0x5684857 | - | sub_5684660 | - | `0x5684857  setb al` | flavor 0/1/2 | [V] |
| 0x568485a | - | sub_5684660 | - | `0x568485a  test al,dil` | accepted && flavor<3 | [V] |
| 0x568485d | - | sub_5684660 | - | `0x568485d  je 0x56846FB` | skip element | [V] |
| 0x5684863 | 8 | sub_5684660 | R a1 | `0x5684863  mov rax,[rbp+0x958]` | a1 | [V] |
| 0x568486a | 8 | sub_5684660 | R [a1+8] | `0x568486a  mov rax,[rax+8]` | [a1+8] | [V] |
| 0x568486e | 8 | sub_5684660 | - | `0x568486e  lea r8,[rax+0x9D0]` | callee a2 = [a1+8]+0x9D0 | [V] |
| 0x5684875 | 4 | sub_5684660 | R [rbp+0x964] | `0x5684875  mov ecx,[rbp+0x964]` | pass flavor | [V] |
| 0x568487e | - | sub_5684660 | - | `0x568487e  je short 0x56848B7` | flavor==1 → sub_5690e10 | [V] |
| 0x5684880 | - | sub_5684660 | - | `0x5684880  test ecx,ecx` | flavor==0? | [V] |
| 0x5684882 | - | sub_5684660 | - | `0x5684882  jne short 0x56848EA` | flavor>=2 → sub_56912d0 | [V] |
| 0x5684884 | 8 | sub_5684660 | W [rbp+0x2B0] | `0x5684884  mov [rbp+0x2B0],rsi` | local = element data base | [V] |
| 0x568488b | 8 | sub_5684660 | R [[a1+8]+0xA78] | `0x568488b  mov rax,[rax+0xA78]` | | [V] |
| 0x5684892 | 8 | sub_5684660 | R a1 | `0x5684892  mov rdx,[rax]` | callee a1 = [[a1+8]+0xA78]+0x | [V] |
| 0x5684895 | - | sub_5684660 | - | `0x5684895  add rdx,0x40` | a1 += 0x40 | [V] |
| 0x5684899 | 8 | sub_5684660 | - | `0x5684899  lea rax,[rbp+0x5A0]` | | [V] |
| 0x56848a0 | 8 | sub_5684660 | W [rsp+0x20] | `0x56848a0  mov [rsp+0x20],rax` | r9 home slot | [V] |
| 0x56848a5 | 8 | sub_5684660 | W [rbp-0x50] | `0x56848a5  lea rcx,[rbp-0x50]` | callee a0 = out-object area | [V] |
| 0x56848a9 | 8 | sub_5684660 | W [rbp+0x2B0] | `0x56848a9  lea r9,[rbp+0x2B0]` | callee a3 = &element-data-base local | [V] |
| 0x56848b0 | - | sub_5684660 | - | `0x56848b0  call 0x5690960` | flavor 0: per-element callee | [V] |
| 0x56848e3 | - | sub_5684660 | - | `0x56848e3  call 0x5690E10` | flavor 1: per-element callee | [V] |
| 0x568491d | - | sub_5684660 | - | `0x568491d  call 0x56912D0` | flavor>=2: per-element callee | [V] |
| 0x5684970 | - | sub_5684660 | - | `0x5684970  call 0x76A8A0` | resolver registration | [V] |
| 0x5684922 | 8 | sub_5684660 | R [rbp-0x38] | `0x5684922  mov rdi,[rbp-0x38]` | callee out-object end (+0x18) | [V] |
| 0x5684926 | 8 | sub_5684660 | R [rbp-0x40] | `0x5684926  mov rsi,[rbp-0x40]` | callee out-object base (+0x10) | [V] |
| 0x568492a | 8 | sub_5684660 | R [rbp-0x48] | `0x568492a  mov rax,[rbp-0x48]` | saved node | [V] |
| 0x568492e | 8 | sub_5684660 | W [rbp+0x8C8] | `0x568492e  mov [rbp+0x8C8],rax` | | [V] |
| 0x5684935 | 16 | sub_5684660 | R [rbp-0x50] | `0x5684935  movaps xmm7,[rbp-0x50]` | callee output entry {a1,[a1+0]} | [V] |
| 0x568493c | 8 | sub_5684660 | - | `0x568493c  sub rax,rsi` | output bytes = end - base | [V] |
| 0x5684949 | 8 | sub_5684660 | - | `0x5684949  sar rcx,3` | /8 | [V] |
| 0x568494d | 8 | sub_5684660 | - | `0x568494d  mov rax,0xAAAAAAAAAAAAAAAB` | magic | [V] |
| 0x5684957 | 8 | sub_5684660 | - | `0x5684957  imul rcx,rax` | * magic → entry count | [V] |
| 0x568495b | 8 | sub_5684660 | W [rbp+0x8C0] | `0x568495b  mov [rbp+0x8C0],rcx` | entry count saved | [V] |
| 0x5684969 | 8 | sub_5684660 | R [rbp+0x8E8] | `0x5684969  mov rdx,[rbp+0x8E8]` | resolver rdx arg | [V] |
| 0x56849b5 | - | sub_5684660 | - | `0x56849b5  cmp rcx,rdi` | count==0 → next element | [V] |
| 0x56849b8 | - | sub_5684660 | - | `0x56849b8  je 0x5685A90` | no entries | [V] |
| 0x56849c1 | 8 | sub_5684660 | - | `0x56849c1  sub r13,rcx` | output bytes | [V] |
| 0x56849c4 | 8 | sub_5684660 | - | `0x56849c4  sar r13,3` | /8 | [V] |
| 0x56849c8 | 8 | sub_5684660 | - | `0x56849c8  mov rax,0xAAAAAAAAAAAAAAAB` | magic | [V] |
| 0x56849d2 | 8 | sub_5684660 | - | `0x56849d2  imul r13,rax` | entry count | [V] |
| 0x56849d6 | - | sub_5684660 | - | `0x56849d6  cmp r13,0x200` | clamp count <= 0x200 | [V] |
| 0x56849dd | 8 | sub_5684660 | - | `0x56849dd  mov eax,0x200` | | [V] |
| 0x56849e2 | - | sub_5684660 | - | `0x56849e2  cmovae r13,rax` | | [V] |
| 0x56849e6 | 8 | sub_5684660 | R [elem+0x258] | `0x56849e6  mov rax,[r14+0x258]` | element field | [V] |
| 0x56849ed | 8 | sub_5684660 | W record+0x0 | `0x56849ed  mov [rbp+0x5A0],rax` | record+0x0 = element field | [V] |
| 0x56849fc | 8 | sub_5684660 | R [elem+0x268] | `0x56849fc  mov rax,[r14+0x268]` | element object | [V] |
| 0x5684a0f | 4 | sub_5684660 | W [rax+8] | `0x5684a0f  lock inc dword ptr [rax+8]` | inc object refcount | [V] |
| 0x5684a13 | 8 | sub_5684660 | R [elem+0x268] | `0x5684a13  mov rax,[r14+0x268]` | element object | [V] |
| 0x5684a22 | 8 | sub_5684660 | R [elem+0x260] | `0x5684a22  mov rcx,[r14+0x260]` | element field | [V] |
| 0x5684a29 | 8 | sub_5684660 | W record+0x8 | `0x5684a29  mov [rbp+0x5A8],rcx` | record+0x8 | [V] |
| 0x5684a30 | 8 | sub_5684660 | W record+0x10 | `0x5684a30  mov [rbp+0x5B0],rax` | record+0x10 | [V] |
| 0x56849f4 | 16 | sub_5684660 | W rbp+0x5A8 | `0x56849f4  movups [r15-0x210],xmm6` | zero record+0x5A8 (16B) | [V] |
| 0x5684a37 | 16 | sub_5684660 | W rbp+0x5B8 | `0x5684a37  movups [r15-0x200],xmm6` | zero record+0x5B8 (16B) | [V] |
| 0x5684a3f | 8 | sub_5684660 | W rbp+0x5C8 | `0x5684a3f  mov qword ptr [r15-0x1F0],0` | record+0x5C8 = 0 | [V] |
| 0x5684a4a | 1 | sub_5684660 | W rbp+0x5D0 | `0x5684a4a  mov byte ptr [rbp+0x5D0],1` | flag byte | [V] |
| 0x5684a51 | 1 | sub_5684660 | W rbp+0x600 | `0x5684a51  mov byte ptr [rbp+0x600],0` | flag byte | [V] |
| 0x5684a58 | 16 | sub_5684660 | W record+0xD8 | `0x5684a58  movups [rbp+0x5D8],xmm7` | record+0xD8 = callee output entry {a1,[a1+0]} | [V] |
| 0x5684a5f | 16 | sub_5684660 | W rbp+0x5E8 | `0x5684a5f  movups [r15-0x1D0],xmm6` | zero record+0x5E8 (16B) | [V] |
| 0x5684a67 | 8 | sub_5684660 | W rbp+0x5F8 | `0x5684a67  mov qword ptr [r15-0x1C0],0` | record+0x5F8 = 0 | [V] |
| 0x5684a92 | 8 | sub_5684660 | R [rbp+0x8C8] | `0x5684a92  mov rax,[rbp+0x8C8]` | saved node | [V] |
| 0x5684a99 | 8 | sub_5684660 | R [node+0] | `0x5684a99  mov rcx,[rax]` | | [V] |
| 0x5684aa2 | 8 | sub_5684660 | - | `0x5684aa2  lea rdx,[rbp-0x50]` | | [V] |
| 0x5684aa6 | 8 | sub_5684660 | R [rbp+0x950] | `0x5684aa6  mov r8,[rbp+0x950]` | copy byte count | [V] |
| 0x5684aad | - | sub_5684660 | - | `0x5684aad  call 0xA78940` | alloc callee-output copy buffer | [V] |
| 0x5684ac7 | 4 | sub_5684660 | W [rdi+8] | `0x5684ac7  lock dec dword ptr [rdi+8]` | release old node buffer refcount | [V] |
| 0x5684ad6 | - | sub_5684660 | R [0xF99FFA0] | `0x5684ad6  call qword ptr [0xF99FFA0]` | dtor sub_eea6040 | [V] |
| 0x5684aec | - | sub_5684660 | R [0xF99FFA0] | `0x5684aec  call qword ptr [0xF99FFA0]` | dtor sub_eea6040 | [V] |
| 0x5684b00 | 8 | sub_5684660 | - | `0x5684b00  add rsi,rbx` | copy dest end | [V] |
| 0x5684b03 | 8 | sub_5684660 | W record copy start | `0x5684b03  mov [rbp+0x5E8],rsi` | record+0x5E8 = callee-output copy dest start | [V] |
| 0x5684b0a | 8 | sub_5684660 | W record copy start | `0x5684b0a  mov [rbp+0x5F0],rsi` | record+0x5F0 = copy cursor | [V] |
| 0x5684b18 | 8 | sub_5684660 | - | `0x5684b18  lea rdi,[rsi+r8]` | copy dest end | [V] |
| 0x5684b1c | 8 | sub_5684660 | W record copy end | `0x5684b1c  mov [rbp+0x5F8],rdi` | record+0x5F8 = callee-output copy dest end | [V] |
| 0x5684b30 | - | sub_5684660 | - | `0x5684b30  call 0xEEC6DE0` | copy callee output array → record dest | [V] |
| 0x5684b35 | 8 | sub_5684660 | W record copy end | `0x5684b35  mov [rbp+0x5F0],rdi` | record+0x5F0 = copy end | [V] |
| 0x5684b3c | 8 | sub_5684660 | R [rbp+0x940] | `0x5684b3c  mov rax,[rbp+0x940]` | count | [V] |
| 0x5684b43 | 8 | sub_5684660 | - | `0x5684b43  sub rax,rsi` | | [V] |
| 0x5684b46 | 8 | sub_5684660 | - | `0x5684b46  sar rax,3` | /8 | [V] |
| 0x5684b4a | 8 | sub_5684660 | - | `0x5684b4a  mov rcx,0xAAAAAAAAAAAAAAAB` | magic | [V] |
| 0x5684b54 | 8 | sub_5684660 | - | `0x5684b54  imul rax,rcx` | entry count | [V] |
| 0x5684b58 | 1 | sub_5684660 | W rbp+0x600 | `0x5684b58  mov byte ptr [rbp+0x600],1` | flag byte | [V] |
| 0x5684b5f | 8 | sub_5684660 | W record+0x608 | `0x5684b5f  mov [rbp+0x608],rax` | record+0x608 = entry count | [V] |
| 0x5684b66 | 16 | sub_5684660 | R [elem+0x118] | `0x5684b66  movups xmm0,[r14+0x118]` | element data +0x118 | [V] |
| 0x5684b6e | 16 | sub_5684660 | W record+0x618 | `0x5684b6e  movups [rbp+0x618],xmm0` | record+0x618 = element data +0x118 | [V] |
| 0x5684b75 | 16 | sub_5684660 | R [elem+0x128] | `0x5684b75  movups xmm0,[r14+0x128]` | element data +0x128 | [V] |
| 0x5684b7d | 16 | sub_5684660 | W record+0x628 | `0x5684b7d  movups [rbp+0x628],xmm0` | record+0x628 = element data +0x128 | [V] |
| 0x5684b84 | 16 | sub_5684660 | R [elem+0x138] | `0x5684b84  movups xmm0,[r14+0x138]` | | [V] |
| 0x5684b8c | 16 | sub_5684660 | W record+0x638 | `0x5684b8c  movups [rbp+0x638],xmm0` | | [V] |
| 0x5684b93 | 16 | sub_5684660 | R [elem+0x148] | `0x5684b93  movups xmm0,[r14+0x148]` | | [V] |
| 0x5684b9b | 16 | sub_5684660 | W record+0x648 | `0x5684b9b  movups [rbp+0x648],xmm0` | | [V] |
| 0x5684ba2 | 16 | sub_5684660 | R [elem+0x158] | `0x5684ba2  movups xmm0,[r14+0x158]` | | [V] |
| 0x5684baa | 16 | sub_5684660 | W record+0x658 | `0x5684baa  movups [rbp+0x658],xmm0` | | [V] |
| 0x5684bb1 | 16 | sub_5684660 | R [elem+0x168] | `0x5684bb1  movups xmm0,[r14+0x168]` | | [V] |
| 0x5684bb9 | 16 | sub_5684660 | W record+0x668 | `0x5684bb9  movups [rbp+0x668],xmm0` | | [V] |
| 0x5684bc0 | 16 | sub_5684660 | R [elem+0x178] | `0x5684bc0  movups xmm0,[r14+0x178]` | | [V] |
| 0x5684bc8 | 16 | sub_5684660 | W record+0x678 | `0x5684bc8  movups [rbp+0x678],xmm0` | | [V] |
| 0x5684bcf | 16 | sub_5684660 | R [elem+0x188] | `0x5684bcf  movups xmm0,[r14+0x188]` | | [V] |
| 0x5684bd7 | 16 | sub_5684660 | W record+0x688 | `0x5684bd7  movups [rbp+0x688],xmm0` | | [V] |
| 0x5684bde | 8 | sub_5684660 | - | `0x5684bde  lea rcx,[r14+0x198]` | element +0x198 block | [V] |
| 0x5684be5 | 4 | sub_5684660 | R [elem+0x1A8] | `0x5684be5  mov eax,[rcx+0x10]` | element +0x1A8 | [V] |
| 0x5684be8 | 4 | sub_5684660 | W rbp+0x6A8 | `0x5684be8  mov [r15-0x110],eax` | record+0x6A8 = element +0x1A8 | [V] |
| 0x5684bef | 16 | sub_5684660 | R [elem+0x198] | `0x5684bef  movups xmm0,[rcx]` | element +0x198 | [V] |
| 0x5684bf2 | 16 | sub_5684660 | W rbp+0x698 | `0x5684bf2  movups [r15-0x120],xmm0` | record+0x698 = element +0x198 | [V] |
| 0x5684bfa | 16 | sub_5684660 | R [elem+0x1AC] | `0x5684bfa  movups xmm0,[r14+0x1AC]` | | [V] |
| 0x5684c02 | 16 | sub_5684660 | W record+0x6AC | `0x5684c02  movups [rbp+0x6AC],xmm0` | element +0x1AC → record+0x6AC | [V] |
| 0x5684c20 | 16 | sub_5684660 | W record+0x6CC | `0x5684c20  movups [rbp+0x6CC],xmm0` | element +0x1CC → record+0x6CC | [V] |
| 0x5684c5c | 16 | sub_5684660 | W record+0x70C | `0x5684c5c  movups [rbp+0x70C],xmm0` | element +0x20C → record+0x70C | [V] |
| 0x5684c6b | 16 | sub_5684660 | W record+0x71C | `0x5684c6b  movups [rbp+0x71C],xmm0` | element +0x21C → record+0x71C (last field copy) | [V] |
| 0x5684c9f | 8 | sub_5684660 | R [a1+0x28] | `0x5684c9f  mov rax,[rbp+0x8D0]` | [a1+0x28] | [V] |
| 0x5684cad | 16 | sub_5684660 | W rbp+0x74C | `0x5684cad  movups [r15-0x6C],xmm1` | record+0x74C = [a1+0x28] float4 | [V] |
| 0x5684cb2 | 16 | sub_5684660 | W rbp+0x73C | `0x5684cb2  movups [r15-0x7C],xmm0` | record+0x73C = [a1+0x28] float4 | [V] |
| 0x5684cd2 | 1 | sub_5684660 | R [a1+0x48] | `0x5684cd2  movzx eax,byte ptr [rcx+0x48]` | [a1+0x48] byte | [V] |
| 0x5684cd6 | 1 | sub_5684660 | W rbp+0x75C | `0x5684cd6  mov [rbp+0x75C],al` | record+0x75C | [V] |
| 0x5684cdc | 16 | sub_5684660 | R [a1+0x4C] | `0x5684cdc  movups xmm0,[rcx+0x4C]` | [a1+0x4C] float4 | [V] |
| 0x5684ce0 | 16 | sub_5684660 | W rbp+0x760 | `0x5684ce0  movaps [rbp+0x760],xmm0` | record+0x760 | [V] |
| 0x5684cfc | 16 | sub_5684660 | R [a1+0x60+0x20] | `0x5684cfc  movups xmm2,[rax+0x20]` | [a1+0x60] block field | [V] |
| 0x5684d00 | 16 | sub_5684660 | R [a1+0x60+0x2E] | `0x5684d00  movups xmm3,[rax+0x2E]` | [a1+0x60] block field | [V] |
| 0x5684d04 | 16 | sub_5684660 | W rbp+0x7A2 | `0x5684d04  movups [r15-0x16],xmm3` | record+0x7A2 | [V] |
| 0x5684d09 | 16 | sub_5684660 | W rbp+0x794 | `0x5684d09  movups [r15-0x24],xmm2` | record+0x794 | [V] |
| 0x5684d0e | 16 | sub_5684660 | W rbp+0x784 | `0x5684d0e  movups [r15-0x34],xmm1` | record+0x784 | [V] |
| 0x5684d13 | 16 | sub_5684660 | W rbp+0x774 | `0x5684d13  movups [r15-0x44],xmm0` | record+0x774 | [V] |
| 0x5684d18 | 1 | sub_5684660 | W rbp+0x7B4 | `0x5684d18  mov byte ptr [rbp+0x7B4],1` | flag byte | [V] |
| 0x5684d1f | 8 | sub_5684660 | R [rbp+0x608] | `0x5684d1f  mov rax,[rbp+0x608]` | entry count | [V] |
| 0x5684d26 | 8 | sub_5684660 | - | `0x5684d26  add rax,r13` | count + per-entry count | [V] |
| 0x5684d29 | 8 | sub_5684660 | W record+0x610 | `0x5684d29  mov [rbp+0x610],rax` | record+0x610 | [V] |
| 0x5684d30 | 16 | sub_5684660 | W rbp+0x7C8 | `0x5684d30  movups [r15+0x10],xmm6` | zero record+0x7C8 (16B) | [V] |
| 0x5684d35 | 16 | sub_5684660 | W rbp+0x7B8 | `0x5684d35  movups [r15],xmm6` | zero record start (16B) | [V] |
| 0x5684d39 | 8 | sub_5684660 | W rbp+0x7D8 | `0x5684d39  mov qword ptr [rbp+0x7D8],0xF` | small-string size = 0xF | [V] |
| 0x5684d44 | 8 | sub_5684660 | W rbp+0x7E0 | `0x5684d44  mov qword ptr [rbp+0x7E0],0` | small-string cap = 0 | [V] |
| 0x5684da4 | - | sub_5684660 | - | `0x5684da4  call 0xEEC6DE0` | copy string into [rbp+0x7C0] | [V] |
| 0x5684da9 | 1 | sub_5684660 | W [rbp+rsi+0x7C0] | `0x5684da9  mov byte ptr [rbp+rsi+0x7C0],0` | null-terminate string | [V] |
| 0x5684db8 | 8 | sub_5684660 | W rbp+0x7B8 | `0x5684db8  mov [rbp+0x7B8],rax` | record string heap pointer | [V] |
| 0x5684e9b | 8 | sub_5684660 | W rbp+0x820 | `0x5684e9b  mov [rbp+0x820],rdi` | second string heap pointer | [V] |
| 0x5684f3f | 16 | sub_5684660 | W [rbp+0x2B0] | `0x5684f3f  movaps [rbp+0x2B0],xmm0` | record2 field | [V] |
| 0x5684f46 | 16 | sub_5684660 | W [rbp+0x2C0] | `0x5684f46  movaps [rbp+0x2C0],xmm1` | record2 field | [V] |
| 0x5684f4d | 8 | sub_5684660 | W [rbp+0x900] | `0x5684f4d  mov qword ptr [rbp+0x900],0` | | [V] |
| 0x5684f71 | 16 | sub_5684660 | W [rbp+0x2D0] | `0x5684f71  movaps [rbp+0x2D0],xmm0` | [rbp+0x2D0] = [r14+0x258] | [V] |
| 0x5684f7f | 8 | sub_5684660 | W [rbp+0x2E0] | `0x5684f7f  mov [rbp+0x2E0],rax` | [rbp+0x2E0] = [r14+0x260] | [V] |
| 0x5684fae | 1 | sub_5684660 | W [rbp+0x300] | `0x5684fae  mov [rbp+0x300],al` | flag byte | [V] |
| 0x5684fd2 | 16 | sub_5684660 | R [rbp+0x5D8] | `0x5684fd2  movups xmm0,[rbp+0x5D8]` | callee output entry | [V] |
| 0x5684fd9 | 16 | sub_5684660 | R [rbp+0x5E8] | `0x5684fd9  movups xmm1,[rbp+0x5E8]` | copy-dest start | [V] |
| 0x5684fe0 | 16 | sub_5684660 | W [rbp+0x308] | `0x5684fe0  movups [rbp+0x308],xmm0` | record+0x308 = callee output entry {a1,[a1+0]} | [V] |
| 0x5684fe7 | 16 | sub_5684660 | W [rbp+0x5E8] | `0x5684fe7  movups [rbp+0x5E8],xmm6` | zero copy-dest start | [V] |
| 0x5684fee | 16 | sub_5684660 | W [rbp+0x318] | `0x5684fee  movups [rbp+0x318],xmm1` | record+0x318 = copy-dest start | [V] |
| 0x5684ff5 | 8 | sub_5684660 | W [rbp+0x328] | `0x5684ff5  mov [rbp+0x328],rax` | record+0x328 = copy-dest END (dest pointer) | [V] |
| 0x5684ffc | 1 | sub_5684660 | W [rbp+0x330] | `0x5684ffc  mov byte ptr [rbp+0x330],1` | flag byte | [V] |
| 0x568502e | 16 | sub_5684660 | W [rbp+0x348] | `0x568502e  movups [rbp+0x348],xmm0` | record+0x348 = element data field | [V] |
| 0x56850ac | 16 | sub_5684660 | W [rbp+0x3DC] | `0x56850ac  movups [rbp+0x3DC],xmm0` | record+0x3DC | [V] |
| 0x568510e | 16 | sub_5684660 | R [rbp+0x72C] | `0x568510e  movups xmm0,[r15-0x8C]` | element data +0x22C | [V] |
| 0x5685116 | 16 | sub_5684660 | W [rbp+0x3CC] | `0x5685116  movups [rsi-0xBC],xmm0` | (rsi=&[rbp+0x518]) record field copy | [V] |
| 0x5685155 | 1 | sub_5684660 | R [rbp+0x75C] | `0x5685155  movzx eax,byte ptr [rbp+0x75C]` | | [V] |
| 0x568515c | 1 | sub_5684660 | W [rbp+0x48C] | `0x568515c  mov [rbp+0x48C],al` | | [V] |
| 0x5685162 | 16 | sub_5684660 | R [rbp+0x760] | `0x5685162  movaps xmm0,[rbp+0x760]` | | [V] |
| 0x5685169 | 16 | sub_5684660 | W [rbp+0x490] | `0x5685169  movaps [rbp+0x490],xmm0` | | [V] |
| 0x56851e0 | 8 | sub_5684660 | R [rbp+0x7B8] | `0x56851e0  mov rax,[rbp+0x7B8]` | string heap pointer | [V] |
| 0x56851e7 | 8 | sub_5684660 | W [rbp+0x4E8] | `0x56851e7  mov [rbp+0x4E8],rax` | record string pointer | [V] |
| 0x56851ee | 8 | sub_5684660 | - | `0x56851ee  lea rax,[0xF25B6A0]` | vtable data_f25b6a0 | [I] |
| 0x56851f5 | 8 | sub_5684660 | W [rbp+0x518] | `0x56851f5  mov [rbp+0x518],rax` | record2 vtable = data_f25b6a0 | [V] |
| 0x56851fc | 8 | sub_5684660 | W [rbp+0x550] | `0x56851fc  mov [rbp+0x550],rsi` | | [V] |
| 0x568520d | - | sub_5684660 | - | `0x568520d  call 0x76A8A0` | resolver (rcx=&[rbp+0x880], rdx=r12) | [V] |
| 0x56852f3 | 16 | sub_5684660 | W [rbp-0x50] | `0x56852f3  movaps [rbp-0x50],xmm0` | restore callee out-object {a1,[a1+0]} | [V] |
| 0x56852f7 | 16 | sub_5684660 | W [rbp-0x40] | `0x56852f7  movaps [rbp-0x40],xmm1` | restore callee out-object base | [V] |
| 0x568532a | 8 | sub_5684660 | W [rbp-0x20] | `0x568532a  mov [rbp-0x20],rax` | [rbp-0x20] = [r14+0x260] | [V] |
| 0x5685658 | 8 | sub_5684660 | R caller dest | `0x5685658  mov rcx,[rbp+0x8B8]` | caller dest pointer (saved arg rcx) | [V] |
| 0x568565f | 8 | sub_5684660 | R [rbp-0x50] | `0x568565f  lea rdx,[rbp-0x50]` | callee out-object {a1,[a1+0],base,end,end} | [V] |
| 0x5685663 | 4 | sub_5684660 | - | `0x5685663  xor r8d,r8d` | | [V] |
| 0x5685666 | - | sub_5684660 | - | `0x5685666 call 0x568B0D0` | DEST WRITE: sub_568b0d0(caller_dest, &callee_out_object, 0) | [V] |
| 0x5685784 | - | sub_5684660 | - | `0x5685784 lea rcx,[rbp-0x30]` | side record = {[rbp+0x2D0],[rbp+0x2E0]} = {[r14+0x258],[r14+0x260]} | [V] |
| 0x5685789 | - | sub_5684660 | - | `0x5685789 call 0x655CEA0` | DEST WRITE: sub_655CEA0(side record) | [V] |
| 0x5684990 | 8 | sub_5684660 | - | `0x5684990 lea rax,[r13*2]` / `0x5684998 add rax,r13` | entry*3 | [V] |
| 0x568499b | 8 | sub_5684660 | R [rbp+0x940] | `0x568499b mov rbx,[rbp+0x940]` | node buffer base | [V] |
| 0x56849a2 | 8 | sub_5684660 | - | `0x56849a2 lea rbx,[rbx+rax*8]` | node buffer entry = base + entry*0x18 | [V] |
| 0x56849a6 | 8 | sub_5684660 | - | `0x56849a6 lea rcx,[rbp+0x5A0]` | record | [V] |
| 0x56849ad | - | sub_5684660 | - | `0x56849ad call 0x655CEA0` | DEST WRITE: sub_655CEA0(node_buffer_entry, record) per callee-output entry | [V] |
| 0x5685925 | - | sub_5684660 | - | `0x5685925 call 0x655CEA0` | DEST WRITE: sub_655CEA0(&[rbp+0x2D0]) second side record | [V] |
| 0x5685b96 | - | sub_5684660 | - | `0x5685b96 ret` | function end | [V] |

sub_5684660 per-element result: for each element (0x290 stride over [a1+0x10]..[a1+0x18], element data at [cursor+0x240]) the body builds a header block at rbp+0x560 {vtable data_f25b670, element data base}, runs the node-list filter, calls sub_5690960/5690e10/56912d0 (flavor [rbp+0x964]) with out-object at [rbp-0x50], copies the callee output array into the record at [rbp+0x5E8..0x5F8], fills record fields (element fields [r14+0x258/0x260/0x268], callee output entry {a1,[a1+0]} at +0x5D8/+0x308, element data [r14+0x118..0x22C] at +0x618..+0x72C, [a1+0x28/0x48/0x60]-derived fields, strings), then DEST WRITES: sub_568b0d0(caller dest from arg rcx saved at [rbp+0x8B8], &[rbp-0x50] callee out-object, 0) plus sub_655CEA0 side-record writes (&[rbp-0x30], &[rbp+0x2D0], and per-entry node-buffer entries).

### (b-2) sub_567E510 (vtable data_f25b4F0) — [V]

Same structure as sub_5684660; per-element callees are sub_5688FF0 (flavor 0) / sub_568A310 (flavor 1) / sub_568A7F0 (flavor>=2). Args: rcx=caller dest, rdx=a1. Element cursor r14 = [a1+0x10] .. [a1+0x18] by 0x290 stride; element data = r14+0x240.

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 0x567E510 | 1 | sub_567E510 | - | `0x567E510  push rbp` | function entry | [V] |
| 0x567E544 | 8 | sub_567E510 | W [rbp+0x8B8] | `0x567E544  mov [rbp+0x8B8],rcx` | save caller dest pointer (arg rcx) | [V] |
| 0x567E552 | 8 | sub_567E510 | R a1+0x10 | `0x567E552  mov r14,[rdx+0x10]` | element cursor = [a1+0x10] | [V] |
| 0x567E556 | 8 | sub_567E510 | R a1+0x18 | `0x567E556  mov rax,[rdx+0x18]` | element end = [a1+0x18] | [V] |
| 0x567E55A | 8 | sub_567E510 | W [rbp+0x8E0] | `0x567E55A  mov [rbp+0x8E0],rax` | loop end saved | [V] |
| 0x567E561 | 8 | sub_567E510 | R a1+0x28 | `0x567E561  lea rax,[rdx+0x28]` | a1+0x28 | [V] |
| 0x567E565 | 8 | sub_567E510 | W [rbp+0x8D0] | `0x567E565  mov [rbp+0x8D0],rax` | | [V] |
| 0x567E581 | 8 | sub_567E510 | W [rbp+0x958] | `0x567E581  mov [rbp+0x958],rdx` | save a1 | [V] |
| 0x567E588 | 8 | sub_567E510 | R a1+0x60 | `0x567E588  lea rax,[rdx+0x60]` | a1+0x60 | [V] |
| 0x567E58C | 8 | sub_567E510 | W [rbp+0x8D8] | `0x567E58C  mov [rbp+0x8D8],rax` | | [V] |
| 0x567E59A | 4 | sub_567E510 | W [rbp+0x964] | `0x567E59A  mov [rbp+0x964],r8d` | pass flavor flag | [V] |
| 0x567E5B2 | - | sub_567E510 | - | `0x567E5B2  add r14,0x290` | next element (0x290 stride) | [V] |
| 0x567E5C7 | - | sub_567E510 | - | `0x567E5C7  cmp r14,[rbp+0x8E0]` | element cursor vs end | [V] |
| 0x567E5CE | - | sub_567E510 | - | `0x567E5CE  je 0x567F9A7` | outer loop exit | [V] |
| 0x567E5D4 | 8 | sub_567E510 | R elem base | `0x567E5D4  lea rsi,[r14+0x240]` | element data base = cursor+0x240 | [V] |
| 0x567E5F6 | 8 | sub_567E510 | - | `0x567E5F6  lea rax,[0xF25B4F0]` | vtable data_f25b4F0 | [I] |
| 0x567E5FD | 8 | sub_567E510 | W block+0x0 | `0x567E5FD  mov [rbp+0x560],rax` | block header+0 = vtable | [V] |
| 0x567E604 | 8 | sub_567E510 | W block+0x8 | `0x567E604  mov [rbp+0x568],rsi` | block header+8 = element data base | [V] |
| 0x567E60B | 8 | sub_567E510 | W [rbp+0x598] | `0x567E60B  mov [rbp+0x598],rcx` | block pointer | [V] |
| 0x567E612 | 8 | sub_567E510 | R [node_list+0xA10] | `0x567E612  mov rbx,[rdi+0xA10]` | first node | [V] |
| 0x567E65C | 8 | sub_567E510 | R [node+0x10] | `0x567E65C  mov r15,[rbx+0x10]` | node element start | [V] |
| 0x567E660 | 8 | sub_567E510 | R [node+0x18] | `0x567E660  mov r12,[rbx+0x18]` | node element end | [V] |
| 0x567E670 | - | sub_567E510 | - | `0x567E670  add r15,0xC8` | next element (0xC8 stride) | [V] |
| 0x567E67C | 4 | sub_567E510 | R [elem+0x0] | `0x567E67C  mov rax,[r15]` | element flags | [V] |
| 0x567E67F | 4 | sub_567E510 | - | `0x567E67F  not rax` | ~flags | [V] |
| 0x567E68C | - | sub_567E510 | - | `0x567E68C  test rax,rcx` | filter mask 0x800000002 | [V] |
| 0x567E69D | 8 | sub_567E510 | W [rbp-0x50] | `0x567E69D  mov [rbp-0x50],r15` | save element ptr (= callee out-object addr) | [V] |
| 0x567E6A1 | 8 | sub_567E510 | W [rbp-0x48] | `0x567E6A1  mov [rbp-0x48],r13` | save node pointer | [V] |
| 0x567E6BB | 1 | sub_567E510 | - | `0x567E6BB  mov dil,1` | element accepted flag | [V] |
| 0x567E748 | 4 | sub_567E510 | R [rbp+0x964] | `0x567E748  cmp ecx,1` | pass flavor | [V] |
| 0x567E74B | - | sub_567E510 | - | `0x567E74B  je short 0x567E784` | flavor==1 -> sub_568A310 | [V] |
| 0x567E74D | - | sub_567E510 | - | `0x567E74D  test ecx,ecx` | flavor==0? | [V] |
| 0x567E74F | - | sub_567E510 | - | `0x567E74F  jne short 0x567E7B7` | flavor>=2 -> sub_568A7F0 | [V] |
| 0x567E77D | - | sub_567E510 | - | `0x567E77D  call 0x5688FF0` | flavor 0: per-element callee | [V] |
| 0x567E7B0 | - | sub_567E510 | - | `0x567E7B0  call 0x568A310` | flavor 1: per-element callee | [V] |
| 0x567E7EA | - | sub_567E510 | - | `0x567E7EA  call 0x568A7F0` | flavor>=2: per-element callee | [V] |
| 0x567E7EF | 8 | sub_567E510 | R [rbp-0x38] | `0x567E7EF  mov rdi,[rbp-0x38]` | callee out-object end | [V] |
| 0x567E7F3 | 8 | sub_567E510 | R [rbp-0x40] | `0x567E7F3  mov rsi,[rbp-0x40]` | callee out-object base | [V] |
| 0x567E7FB | 8 | sub_567E510 | W [rbp+0x8C8] | `0x567E7FB  mov [rbp+0x8C8],rax` | output-copy setup saved node | [V] |
| 0x567E802 | 16 | sub_567E510 | R [rbp-0x50] | `0x567E802  movaps xmm7,[rbp-0x50]` | callee output entry {a1,[a1+0]} | [V] |
| 0x567E816 | 8 | sub_567E510 | - | `0x567E816  sar rcx,3` | output bytes /8 | [V] |
| 0x567E824 | 8 | sub_567E510 | - | `0x567E824  imul rcx,rax` | * magic -> entry count | [V] |
| 0x567E885 | - | sub_567E510 | - | `0x567E885  cmp rcx,rdi` | count==0 -> next element | [V] |
| 0x567E8B6 | 8 | sub_567E510 | R [elem+0x258] | `0x567E8B6  mov rax,[r14+0x258]` | element field | [V] |
| 0x567E8BD | 8 | sub_567E510 | W record+0x0 | `0x567E8BD  mov [rbp+0x5A0],rax` | record+0x0 = element field | [V] |
| 0x567E8CC | 8 | sub_567E510 | R [elem+0x268] | `0x567E8CC  mov rax,[r14+0x268]` | element object | [V] |
| 0x567E8DF | 4 | sub_567E510 | W [rax+8] | `0x567E8DF  lock inc dword ptr [rax+8]` | inc object refcount | [V] |
| 0x567E8F2 | 8 | sub_567E510 | R [elem+0x260] | `0x567E8F2  mov rcx,[r14+0x260]` | element field | [V] |
| 0x567E8F9 | 8 | sub_567E510 | W record+0x8 | `0x567E8F9  mov [rbp+0x5A8],rcx` | record+0x8 | [V] |
| 0x567E900 | 8 | sub_567E510 | W record+0x10 | `0x567E900  mov [rbp+0x5B0],rax` | record+0x10 | [V] |
| 0x567E907 | 16 | sub_567E510 | W rbp+0x5B8 | `0x567E907  movups [r15-0x200],xmm6` | zero record+0x5B8 (16B) | [V] |
| 0x567E90F | 8 | sub_567E510 | W rbp+0x5C8 | `0x567E90F  mov qword ptr [r15-0x1F0],0` | record+0x5C8 = 0 | [V] |
| 0x567E91A | 1 | sub_567E510 | W rbp+0x5D0 | `0x567E91A  mov byte ptr [rbp+0x5D0],1` | flag byte | [V] |
| 0x567E921 | 1 | sub_567E510 | W rbp+0x600 | `0x567E921  mov byte ptr [rbp+0x600],0` | flag byte | [V] |
| 0x567E928 | 16 | sub_567E510 | W record+0xD8 | `0x567E928  movups [rbp+0x5D8],xmm7` | record+0xD8 = callee output entry {a1,[a1+0]} | [V] |
| 0x567E92F | 16 | sub_567E510 | W rbp+0x5E8 | `0x567E92F  movups [r15-0x1D0],xmm6` | zero record+0x5E8 (16B) | [V] |
| 0x567E937 | 8 | sub_567E510 | W rbp+0x5F8 | `0x567E937  mov qword ptr [r15-0x1C0],0` | record+0x5F8 = 0 | [V] |
| 0x567E9D3 | 8 | sub_567E510 | W record copy start | `0x567E9D3  mov [rbp+0x5E8],rsi` | record+0x5E8 = callee-output copy dest start | [V] |
| 0x567E9DA | 8 | sub_567E510 | W record copy start | `0x567E9DA  mov [rbp+0x5F0],rsi` | record+0x5F0 = copy cursor | [V] |
| 0x567E9EC | 8 | sub_567E510 | W record copy end | `0x567E9EC  mov [rbp+0x5F8],rdi` | record+0x5F8 = callee-output copy dest end | [V] |
| 0x567EA00 | - | sub_567E510 | - | `0x567EA00  call 0xEEC6DE0` | copy callee output array -> record dest | [V] |
| 0x567EA05 | 8 | sub_567E510 | W record copy end | `0x567EA05  mov [rbp+0x5F0],rdi` | record+0x5F0 = copy end | [V] |
| 0x567EA28 | 1 | sub_567E510 | W rbp+0x600 | `0x567EA28  mov byte ptr [rbp+0x600],1` | flag byte | [V] |
| 0x567EA2F | 8 | sub_567E510 | W record+0x608 | `0x567EA2F  mov [rbp+0x608],rax` | record+0x608 = entry count | [V] |
| 0x567EA36 | 16 | sub_567E510 | R [elem+0x118] | `0x567EA36  movups xmm0,[r14+0x118]` | element data +0x118 | [V] |
| 0x567EA3E | 16 | sub_567E510 | W record+0x618 | `0x567EA3E  movups [rbp+0x618],xmm0` | record+0x618 = element data +0x118 | [V] |
| 0x567EA45 | 16 | sub_567E510 | R [elem+0x128] | `0x567EA45  movups xmm0,[r14+0x128]` | | [V] |
| 0x567EA4D | 16 | sub_567E510 | W record+0x628 | `0x567EA4D  movups [rbp+0x628],xmm0` | | [V] |
| 0x567EA54 | 16 | sub_567E510 | R [elem+0x138] | `0x567EA54  movups xmm0,[r14+0x138]` | | [V] |
| 0x567EA5C | 16 | sub_567E510 | W record+0x638 | `0x567EA5C  movups [rbp+0x638],xmm0` | | [V] |
| 0x567EA63 | 16 | sub_567E510 | R [elem+0x148] | `0x567EA63  movups xmm0,[r14+0x148]` | | [V] |
| 0x567EA6B | 16 | sub_567E510 | W record+0x648 | `0x567EA6B  movups [rbp+0x648],xmm0` | | [V] |
| 0x567EA72 | 16 | sub_567E510 | R [elem+0x158] | `0x567EA72  movups xmm0,[r14+0x158]` | | [V] |
| 0x567EA7A | 16 | sub_567E510 | W record+0x658 | `0x567EA7A  movups [rbp+0x658],xmm0` | | [V] |
| 0x567EA81 | 16 | sub_567E510 | R [elem+0x168] | `0x567EA81  movups xmm0,[r14+0x168]` | | [V] |
| 0x567EA89 | 16 | sub_567E510 | W record+0x668 | `0x567EA89  movups [rbp+0x668],xmm0` | | [V] |
| 0x567EA90 | 16 | sub_567E510 | R [elem+0x178] | `0x567EA90  movups xmm0,[r14+0x178]` | | [V] |
| 0x567EA98 | 16 | sub_567E510 | W record+0x678 | `0x567EA98  movups [rbp+0x678],xmm0` | | [V] |
| 0x567EA9F | 16 | sub_567E510 | R [elem+0x188] | `0x567EA9F  movups xmm0,[r14+0x188]` | | [V] |
| 0x567EAA7 | 16 | sub_567E510 | W record+0x688 | `0x567EAA7  movups [rbp+0x688],xmm0` | | [V] |
| 0x567EABF | 16 | sub_567E510 | R [elem+0x198] | `0x567EABF  movups xmm0,[rcx]` | element +0x198 | [V] |
| 0x567EAC2 | 16 | sub_567E510 | W rbp+0x698 | `0x567EAC2  movups [r15-0x120],xmm0` | record+0x698 = element +0x198 | [V] |
| 0x567EACA | 16 | sub_567E510 | R [elem+0x1AC] | `0x567EACA  movups xmm0,[r14+0x1AC]` | | [V] |
| 0x567EAD2 | 16 | sub_567E510 | W record+0x6AC | `0x567EAD2  movups [rbp+0x6AC],xmm0` | element +0x1AC -> record+0x6AC | [V] |
| 0x567EAD9 | 16 | sub_567E510 | R [elem+0x1BC] | `0x567EAD9  movups xmm0,[r14+0x1BC]` | | [V] |
| 0x567EAE1 | 16 | sub_567E510 | W record+0x6BC | `0x567EAE1  movups [rbp+0x6BC],xmm0` | element +0x1BC -> record+0x6BC | [V] |
| 0x567EAE8 | 16 | sub_567E510 | R [elem+0x1CC] | `0x567EAE8  movups xmm0,[r14+0x1CC]` | | [V] |
| 0x567EAF0 | 16 | sub_567E510 | W record+0x6CC | `0x567EAF0  movups [rbp+0x6CC],xmm0` | element +0x1CC -> record+0x6CC | [V] |
| 0x567EAF7 | 16 | sub_567E510 | R [elem+0x1DC] | `0x567EAF7  movups xmm0,[r14+0x1DC]` | | [V] |
| 0x567EAFF | 16 | sub_567E510 | W record+0x6DC | `0x567EAFF  movups [rbp+0x6DC],xmm0` | element +0x1DC -> record+0x6DC | [V] |
| 0x567EB06 | 16 | sub_567E510 | R [elem+0x1EC] | `0x567EB06  movups xmm0,[r14+0x1EC]` | | [V] |
| 0x567EB0E | 16 | sub_567E510 | W record+0x6EC | `0x567EB0E  movups [rbp+0x6EC],xmm0` | element +0x1EC -> record+0x6EC | [V] |
| 0x567EB15 | 16 | sub_567E510 | R [elem+0x1FC] | `0x567EB15  movups xmm0,[r14+0x1FC]` | | [V] |
| 0x567EB1D | 16 | sub_567E510 | W record+0x6FC | `0x567EB1D  movups [rbp+0x6FC],xmm0` | element +0x1FC -> record+0x6FC | [V] |
| 0x567EB24 | 16 | sub_567E510 | R [elem+0x20C] | `0x567EB24  movups xmm0,[r14+0x20C]` | | [V] |
| 0x567EB2C | 16 | sub_567E510 | W record+0x70C | `0x567EB2C  movups [rbp+0x70C],xmm0` | element +0x20C -> record+0x70C | [V] |
| 0x567EB33 | 16 | sub_567E510 | R [elem+0x21C] | `0x567EB33  movups xmm0,[r14+0x21C]` | | [V] |
| 0x567EB3B | 16 | sub_567E510 | W record+0x71C | `0x567EB3B  movups [rbp+0x71C],xmm0` | element +0x21C -> record+0x71C (last field copy) | [V] |
| 0x567EB49 | 16 | sub_567E510 | R [elem+0x22C] | `0x567EB49  movups xmm0,[rax]` | element +0x22C | [V] |
| 0x567EB4C | 16 | sub_567E510 | W rbp+0x72C | `0x567EB4C  movups [r15-0x8C],xmm0` | record+0x72C = element +0x22C | [V] |
| 0x567EAB5 | 4 | sub_567E510 | R [elem+0x1A8] | `0x567EAB5  mov eax,[rcx+0x10]` | element +0x1A8 | [V] |
| 0x567EAB8 | 4 | sub_567E510 | W rbp+0x6A8 | `0x567EAB8  mov [r15-0x110],eax` | record+0x6A8 = element +0x1A8 | [V] |
| 0x567EB6F | 8 | sub_567E510 | R [a1+0x28] | `0x567EB6F  mov rax,[rbp+0x8D0]` | [a1+0x28] | [V] |
| 0x567EB76 | 16 | sub_567E510 | R [a1+0x28] | `0x567EB76  movups xmm0,[rax]` | [a1+0x28] float4 | [V] |
| 0x567EB79 | 16 | sub_567E510 | R [a1+0x28+0x10] | `0x567EB79  movups xmm1,[rax+0x10]` | [a1+0x28+0x10] float4 | [V] |
| 0x567EB7D | 16 | sub_567E510 | W rbp+0x74C | `0x567EB7D  movups [r15-0x6C],xmm1` | record+0x74C = [a1+0x28] float4 | [V] |
| 0x567EB82 | 16 | sub_567E510 | W rbp+0x73C | `0x567EB82  movups [r15-0x7C],xmm0` | record+0x73C = [a1+0x28] float4 | [V] |
| 0x567EBA2 | 1 | sub_567E510 | R [a1+0x48] | `0x567EBA2  movzx eax,byte ptr [rcx+0x48]` | [a1+0x48] byte | [V] |
| 0x567EBA6 | 1 | sub_567E510 | W rbp+0x75C | `0x567EBA6  mov [rbp+0x75C],al` | record+0x75C | [V] |
| 0x567EBAC | 16 | sub_567E510 | R [a1+0x4C] | `0x567EBAC  movups xmm0,[rcx+0x4C]` | [a1+0x4C] float4 | [V] |
| 0x567EBB0 | 16 | sub_567E510 | W rbp+0x760 | `0x567EBB0  movaps [rbp+0x760],xmm0` | record+0x760 | [V] |
| 0x567EBC5 | 16 | sub_567E510 | R [a1+0x60] | `0x567EBC5  movups xmm0,[rax]` | [a1+0x60] block | [V] |
| 0x567EBC8 | 16 | sub_567E510 | R [a1+0x60+0x10] | `0x567EBC8  movups xmm1,[rax+0x10]` | | [V] |
| 0x567EBCC | 16 | sub_567E510 | - | `0x567EBCC  movups xmm2,[rax+0x20]` | fill block element field | [V] |
| 0x567EBD0 | 16 | sub_567E510 | - | `0x567EBD0  movups xmm3,[rax+0x2E]` | fill block element field | [V] |
| 0x567EBD4 | 16 | sub_567E510 | W rbp+0x782 | `0x567EBD4  movups [r15-0x16],xmm3` | (representative: [a1+0x60] block field) | [V] |
| 0x567EBEF | 8 | sub_567E510 | R [rbp+0x608] | `0x567EBEF  mov rax,[rbp+0x608]` | entry count | [V] |
| 0x567EBF6 | 8 | sub_567E510 | - | `0x567EBF6  add rax,r13` | count + per-entry count | [V] |
| 0x567EBF9 | 8 | sub_567E510 | W record+0x610 | `0x567EBF9  mov [rbp+0x610],rax` | record+0x610 | [V] |
| 0x567EC00 | 16 | sub_567E510 | W rbp+0x7C8 | `0x567EC00  movups [r15+0x10],xmm6` | zero record+0x7C8 (16B) | [V] |
| 0x567EC05 | 16 | sub_567E510 | W rbp+0x7B8 | `0x567EC05  movups [r15],xmm6` | zero record start (16B) | [V] |
| 0x567EC09 | 8 | sub_567E510 | W rbp+0x7D8 | `0x567EC09  mov qword ptr [rbp+0x7D8],0xF` | small-string size = 0xF | [V] |
| 0x567EC14 | 8 | sub_567E510 | W rbp+0x7E0 | `0x567EC14  mov qword ptr [rbp+0x7E0],0` | small-string cap = 0 | [V] |
| 0x567F528 | 8 | sub_567E510 | R caller dest | `0x567F528  mov rcx,[rbp+0x8B8]` | caller dest pointer (saved arg rcx) | [V] |
| 0x567F52F | 8 | sub_567E510 | R [rbp-0x50] | `0x567F52F  lea rdx,[rbp-0x50]` | callee out-object {a1,[a1+0],base,end,end} | [V] |
| 0x567F533 | 4 | sub_567E510 | - | `0x567F533  xor r8d,r8d` | | [V] |
| 0x567F536 | - | sub_567E510 | - | `0x567F536 call 0x568B0D0` | DEST WRITE: sub_568b0d0(caller_dest, &callee_out_object, 0) | [V] |
| 0x567E876 | 8 | sub_567E510 | - | `0x567E876  lea rcx,[rbp+0x5A0]` | record | [V] |
| 0x567E87D | - | sub_567E510 | - | `0x567E87D call 0x655CEA0` | DEST WRITE: sub_655CEA0(node_buffer_entry, record) per callee-output entry | [V] |
| 0x567F654 | - | sub_567E510 | - | `0x567F654 call 0x655CEA0` | DEST WRITE: sub_655CEA0(&[rbp+0x2D0]) second side record | [V] |

### (b-3) sub_567FD70 (vtable data_f25b550) — [V]

Same structure; per-element callees sub_568DC40 (flavor 0) / sub_568E110 (flavor 1) / sub_568E5F0 (flavor>=2). Element cursor r14 = [a1+0x10]..[a1+0x18] by 0x290 stride; element data = r14+0x240.

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 0x567FD70 | 1 | sub_567FD70 | - | `0x567FD70  push rbp` | function entry | [V] |
| 0x567FDA4 | 8 | sub_567FD70 | W [rbp+0x8B8] | `0x567FDA4  mov [rbp+0x8B8],rcx` | save caller dest pointer | [V] |
| 0x567FDB2 | 8 | sub_567FD70 | R a1+0x10 | `0x567FDB2  mov r14,[rdx+0x10]` | element cursor = [a1+0x10] | [V] |
| 0x567FDB6 | 8 | sub_567FD70 | R a1+0x18 | `0x567FDB6  mov rax,[rdx+0x18]` | element end = [a1+0x18] | [V] |
| 0x567FDBA | 8 | sub_567FD70 | W [rbp+0x8E0] | `0x567FDBA  mov [rbp+0x8E0],rax` | loop end saved | [V] |
| 0x567FDC1 | 8 | sub_567FD70 | R a1+0x28 | `0x567FDC1  lea rax,[rdx+0x28]` | a1+0x28 | [V] |
| 0x567FDC5 | 8 | sub_567FD70 | W [rbp+0x8D0] | `0x567FDC5  mov [rbp+0x8D0],rax` | | [V] |
| 0x567FDE1 | 8 | sub_567FD70 | W [rbp+0x958] | `0x567FDE1  mov [rbp+0x958],rdx` | save a1 | [V] |
| 0x567FDE8 | 8 | sub_567FD70 | R a1+0x60 | `0x567FDE8  lea rax,[rdx+0x60]` | a1+0x60 | [V] |
| 0x567FDEC | 8 | sub_567FD70 | W [rbp+0x8D8] | `0x567FDEC  mov [rbp+0x8D8],rax` | | [V] |
| 0x567FDFA | 4 | sub_567FD70 | W [rbp+0x964] | `0x567FDFA  mov [rbp+0x964],r8d` | pass flavor flag | [V] |
| 0x567FE12 | - | sub_567FD70 | - | `0x567FE12  add r14,0x290` | next element (0x290 stride) | [V] |
| 0x567FE27 | - | sub_567FD70 | - | `0x567FE27  cmp r14,[rbp+0x8E0]` | element cursor vs end | [V] |
| 0x567FE2E | - | sub_567FD70 | - | `0x567FE2E  je 0x5681207` | outer loop exit | [V] |
| 0x567FE34 | 8 | sub_567FD70 | R elem base | `0x567FE34  lea rsi,[r14+0x240]` | element data base = cursor+0x240 | [V] |
| 0x567FE56 | 8 | sub_567FD70 | - | `0x567FE56  lea rax,[0xF25B550]` | vtable data_f25b550 | [I] |
| 0x567FE5D | 8 | sub_567FD70 | W block+0x0 | `0x567FE5D  mov [rbp+0x560],rax` | block header+0 = vtable | [V] |
| 0x567FE64 | 8 | sub_567FD70 | W block+0x8 | `0x567FE64  mov [rbp+0x568],rsi` | block header+8 = element data base | [V] |
| 0x567FE6B | 8 | sub_567FD70 | W [rbp+0x598] | `0x567FE6B  mov [rbp+0x598],rcx` | block pointer | [V] |
| 0x567FE72 | 8 | sub_567FD70 | R [node_list+0xA10] | `0x567FE72  mov rbx,[rdi+0xA10]` | first node | [V] |
| 0x567FE79 | 8 | sub_567FD70 | - | `0x567FE79  add rdi,0xA10` | advance node list pointer | [V] |
| 0x567FEBC | 8 | sub_567FD70 | R [node+0x10] | `0x567FEBC  mov r15,[rbx+0x10]` | node element start | [V] |
| 0x567FEC0 | 8 | sub_567FD70 | R [node+0x18] | `0x567FEC0  mov r12,[rbx+0x18]` | node element end | [V] |
| 0x567FED0 | - | sub_567FD70 | - | `0x567FED0  add r15,0xC8` | next element (0xC8 stride) | [V] |
| 0x567FF1B | 1 | sub_567FD70 | - | `0x567FF1B  mov dil,1` | element accepted flag | [V] |
| 0x567FFA8 | 4 | sub_567FD70 | R [rbp+0x964] | `0x567FFA8  cmp ecx,1` | pass flavor | [V] |
| 0x567FFAB | - | sub_567FD70 | - | `0x567FFAB  je short 0x567FFE4` | flavor==1 -> sub_568E110 | [V] |
| 0x567FFAD | - | sub_567FD70 | - | `0x567FFAD  test ecx,ecx` | flavor==0? | [V] |
| 0x567FFAF | - | sub_567FD70 | - | `0x567FFAF  jne short 0x5680017` | flavor>=2 -> sub_568E5F0 | [V] |
| 0x567FFDD | - | sub_567FD70 | - | `0x567FFDD  call 0x568DC40` | flavor 0: per-element callee | [V] |
| 0x5680010 | - | sub_567FD70 | - | `0x5680010  call 0x568E110` | flavor 1: per-element callee | [V] |
| 0x568004A | - | sub_567FD70 | - | `0x568004A  call 0x568E5F0` | flavor>=2: per-element callee | [V] |
| 0x5680116 | 8 | sub_567FD70 | R [elem+0x258] | `0x5680116  mov rax,[r14+0x258]` | element field | [V] |
| 0x568011D | 8 | sub_567FD70 | W record+0x0 | `0x568011D  mov [rbp+0x5A0],rax` | record+0x0 = element field | [V] |
| 0x568012C | 8 | sub_567FD70 | R [elem+0x268] | `0x568012C  mov rax,[r14+0x268]` | element object | [V] |
| 0x568013F | 4 | sub_567FD70 | W [rax+8] | `0x568013F  lock inc dword ptr [rax+8]` | inc object refcount | [V] |
| 0x5680152 | 8 | sub_567FD70 | R [elem+0x260] | `0x5680152  mov rcx,[r14+0x260]` | element field | [V] |
| 0x5680159 | 8 | sub_567FD70 | W record+0x8 | `0x5680159  mov [rbp+0x5A8],rcx` | record+0x8 | [V] |
| 0x5680160 | 8 | sub_567FD70 | W record+0x10 | `0x5680160  mov [rbp+0x5B0],rax` | record+0x10 | [V] |
| 0x5680167 | 16 | sub_567FD70 | W rbp+0x5B8 | `0x5680167  movups [r15-0x200],xmm6` | zero record+0x5B8 (16B) | [V] |
| 0x568016F | 8 | sub_567FD70 | W rbp+0x5C8 | `0x568016F  mov qword ptr [r15-0x1F0],0` | record+0x5C8 = 0 | [V] |
| 0x568017A | 1 | sub_567FD70 | W rbp+0x5D0 | `0x568017A  mov byte ptr [rbp+0x5D0],1` | flag byte | [V] |
| 0x5680181 | 1 | sub_567FD70 | W rbp+0x600 | `0x5680181  mov byte ptr [rbp+0x600],0` | flag byte | [V] |
| 0x5680188 | 16 | sub_567FD70 | W record+0xD8 | `0x5680188  movups [rbp+0x5D8],xmm7` | record+0xD8 = callee output entry {a1,[a1+0]} | [V] |
| 0x568018F | 16 | sub_567FD70 | W rbp+0x5E8 | `0x568018F  movups [r15-0x1D0],xmm6` | zero record+0x5E8 (16B) | [V] |
| 0x5680197 | 8 | sub_567FD70 | W rbp+0x5F8 | `0x5680197  mov qword ptr [r15-0x1C0],0` | record+0x5F8 = 0 | [V] |
| 0x5680233 | 8 | sub_567FD70 | W record copy start | `0x5680233  mov [rbp+0x5E8],rsi` | record+0x5E8 = callee-output copy dest start | [V] |
| 0x568023A | 8 | sub_567FD70 | W record copy start | `0x568023A  mov [rbp+0x5F0],rsi` | record+0x5F0 = copy cursor | [V] |
| 0x568024C | 8 | sub_567FD70 | W record copy end | `0x568024C  mov [rbp+0x5F8],rdi` | record+0x5F8 = callee-output copy dest end | [V] |
| 0x5680260 | - | sub_567FD70 | - | `0x5680260  call 0xEEC6DE0` | copy callee output array -> record dest | [V] |
| 0x5680265 | 8 | sub_567FD70 | W record copy end | `0x5680265  mov [rbp+0x5F0],rdi` | record+0x5F0 = copy end | [V] |
| 0x568028F | 8 | sub_567FD70 | W record+0x608 | `0x568028F  mov [rbp+0x608],rax` | record+0x608 = entry count | [V] |
| 0x5680296 | 16 | sub_567FD70 | R [elem+0x118] | `0x5680296  movups xmm0,[r14+0x118]` | element data +0x118 | [V] |
| 0x568029E | 16 | sub_567FD70 | W record+0x618 | `0x568029E  movups [rbp+0x618],xmm0` | record+0x618 = element data +0x118 | [V] |
| 0x56802A5 | 16 | sub_567FD70 | R [elem+0x128] | `0x56802A5  movups xmm0,[r14+0x128]` | | [V] |
| 0x56802AD | 16 | sub_567FD70 | W record+0x628 | `0x56802AD  movups [rbp+0x628],xmm0` | | [V] |
| 0x56802B4 | 16 | sub_567FD70 | R [elem+0x138] | `0x56802B4  movups xmm0,[r14+0x138]` | | [V] |
| 0x56802BC | 16 | sub_567FD70 | W record+0x638 | `0x56802BC  movups [rbp+0x638],xmm0` | | [V] |
| 0x56802C3 | 16 | sub_567FD70 | R [elem+0x148] | `0x56802C3  movups xmm0,[r14+0x148]` | | [V] |
| 0x56802CB | 16 | sub_567FD70 | W record+0x648 | `0x56802CB  movups [rbp+0x648],xmm0` | | [V] |
| 0x56802D2 | 16 | sub_567FD70 | R [elem+0x158] | `0x56802D2  movups xmm0,[r14+0x158]` | | [V] |
| 0x56802DA | 16 | sub_567FD70 | W record+0x658 | `0x56802DA  movups [rbp+0x658],xmm0` | | [V] |
| 0x56802E1 | 16 | sub_567FD70 | R [elem+0x168] | `0x56802E1  movups xmm0,[r14+0x168]` | | [V] |
| 0x56802E9 | 16 | sub_567FD70 | W record+0x668 | `0x56802E9  movups [rbp+0x668],xmm0` | | [V] |
| 0x56802F0 | 16 | sub_567FD70 | R [elem+0x178] | `0x56802F0  movups xmm0,[r14+0x178]` | | [V] |
| 0x56802F8 | 16 | sub_567FD70 | W record+0x678 | `0x56802F8  movups [rbp+0x678],xmm0` | | [V] |
| 0x56802FF | 16 | sub_567FD70 | R [elem+0x188] | `0x56802FF  movups xmm0,[r14+0x188]` | | [V] |
| 0x5680307 | 16 | sub_567FD70 | W record+0x688 | `0x5680307  movups [rbp+0x688],xmm0` | | [V] |
| 0x568031F | 16 | sub_567FD70 | R [elem+0x198] | `0x568031F  movups xmm0,[rcx]` | element +0x198 | [V] |
| 0x5680322 | 16 | sub_567FD70 | W rbp+0x698 | `0x5680322  movups [r15-0x120],xmm0` | record+0x698 = element +0x198 | [V] |
| 0x568032A | 16 | sub_567FD70 | R [elem+0x1AC] | `0x568032A  movups xmm0,[r14+0x1AC]` | | [V] |
| 0x5680332 | 16 | sub_567FD70 | W record+0x6AC | `0x5680332  movups [rbp+0x6AC],xmm0` | element +0x1AC -> record+0x6AC | [V] |
| 0x5680339 | 16 | sub_567FD70 | R [elem+0x1BC] | `0x5680339  movups xmm0,[r14+0x1BC]` | | [V] |
| 0x5680341 | 16 | sub_567FD70 | W record+0x6BC | `0x5680341  movups [rbp+0x6BC],xmm0` | element +0x1BC -> record+0x6BC | [V] |
| 0x5680348 | 16 | sub_567FD70 | R [elem+0x1CC] | `0x5680348  movups xmm0,[r14+0x1CC]` | | [V] |
| 0x5680350 | 16 | sub_567FD70 | W record+0x6CC | `0x5680350  movups [rbp+0x6CC],xmm0` | element +0x1CC -> record+0x6CC | [V] |
| 0x5680357 | 16 | sub_567FD70 | R [elem+0x1DC] | `0x5680357  movups xmm0,[r14+0x1DC]` | | [V] |
| 0x568035F | 16 | sub_567FD70 | W record+0x6DC | `0x568035F  movups [rbp+0x6DC],xmm0` | element +0x1DC -> record+0x6DC | [V] |
| 0x5680366 | 16 | sub_567FD70 | R [elem+0x1EC] | `0x5680366  movups xmm0,[r14+0x1EC]` | | [V] |
| 0x568036E | 16 | sub_567FD70 | W record+0x6EC | `0x568036E  movups [rbp+0x6EC],xmm0` | element +0x1EC -> record+0x6EC | [V] |
| 0x5680375 | 16 | sub_567FD70 | R [elem+0x1FC] | `0x5680375  movups xmm0,[r14+0x1FC]` | | [V] |
| 0x568037D | 16 | sub_567FD70 | W record+0x6FC | `0x568037D  movups [rbp+0x6FC],xmm0` | element +0x1FC -> record+0x6FC | [V] |
| 0x5680384 | 16 | sub_567FD70 | R [elem+0x20C] | `0x5680384  movups xmm0,[r14+0x20C]` | | [V] |
| 0x568038C | 16 | sub_567FD70 | W record+0x70C | `0x568038C  movups [rbp+0x70C],xmm0` | element +0x20C -> record+0x70C | [V] |
| 0x5680393 | 16 | sub_567FD70 | R [elem+0x21C] | `0x5680393  movups xmm0,[r14+0x21C]` | | [V] |
| 0x568039B | 16 | sub_567FD70 | W record+0x71C | `0x568039B  movups [rbp+0x71C],xmm0` | element +0x21C -> record+0x71C (last field copy) | [V] |
| 0x56803A9 | 16 | sub_567FD70 | R [elem+0x22C] | `0x56803A9  movups xmm0,[rax]` | element +0x22C | [V] |
| 0x56803AC | 16 | sub_567FD70 | W rbp+0x72C | `0x56803AC  movups [r15-0x8C],xmm0` | record+0x72C = element +0x22C | [V] |
| 0x5680315 | 4 | sub_567FD70 | R [elem+0x1A8] | `0x5680315  mov eax,[rcx+0x10]` | element +0x1A8 | [V] |
| 0x5680318 | 4 | sub_567FD70 | W rbp+0x6A8 | `0x5680318  mov [r15-0x110],eax` | record+0x6A8 = element +0x1A8 | [V] |
| 0x56803CF | 8 | sub_567FD70 | R [a1+0x28] | `0x56803CF  mov rax,[rbp+0x8D0]` | [a1+0x28] | [V] |
| 0x56803D6 | 16 | sub_567FD70 | R [a1+0x28] | `0x56803D6  movups xmm0,[rax]` | [a1+0x28] float4 | [V] |
| 0x56803D9 | 16 | sub_567FD70 | R [a1+0x28+0x10] | `0x56803D9  movups xmm1,[rax+0x10]` | [a1+0x28+0x10] float4 | [V] |
| 0x56803DD | 16 | sub_567FD70 | W rbp+0x74C | `0x56803DD  movups [r15-0x6C],xmm1` | record+0x74C = [a1+0x28] float4 | [V] |
| 0x56803E2 | 16 | sub_567FD70 | W rbp+0x73C | `0x56803E2  movups [r15-0x7C],xmm0` | record+0x73C = [a1+0x28] float4 | [V] |
| 0x5680402 | 1 | sub_567FD70 | R [a1+0x48] | `0x5680402  movzx eax,byte ptr [rcx+0x48]` | [a1+0x48] byte | [V] |
| 0x5680406 | 1 | sub_567FD70 | W rbp+0x75C | `0x5680406  mov [rbp+0x75C],al` | record+0x75C | [V] |
| 0x568040C | 16 | sub_567FD70 | R [a1+0x4C] | `0x568040C  movups xmm0,[rcx+0x4C]` | [a1+0x4C] float4 | [V] |
| 0x5680410 | 16 | sub_567FD70 | W rbp+0x760 | `0x5680410  movaps [rbp+0x760],xmm0` | record+0x760 | [V] |
| 0x5680425 | 16 | sub_567FD70 | R [a1+0x60] | `0x5680425  movups xmm0,[rax]` | [a1+0x60] block | [V] |
| 0x5680434 | 16 | sub_567FD70 | W rbp+0x782 | `0x5680434  movups [r15-0x16],xmm3` | ([a1+0x60] block field copy) | [V] |
| 0x568044F | 8 | sub_567FD70 | R [rbp+0x608] | `0x568044F  mov rax,[rbp+0x608]` | entry count | [V] |
| 0x5680456 | 8 | sub_567FD70 | - | `0x5680456  add rax,r13` | count + per-entry count | [V] |
| 0x5680459 | 8 | sub_567FD70 | W record+0x610 | `0x5680459  mov [rbp+0x610],rax` | record+0x610 | [V] |
| 0x5680460 | 16 | sub_567FD70 | W rbp+0x7C8 | `0x5680460  movups [r15+0x10],xmm6` | zero record+0x7C8 (16B) | [V] |
| 0x5680465 | 16 | sub_567FD70 | W rbp+0x7B8 | `0x5680465  movups [r15],xmm6` | zero record start (16B) | [V] |
| 0x5680469 | 8 | sub_567FD70 | W rbp+0x7D8 | `0x5680469  mov qword ptr [rbp+0x7D8],0xF` | small-string size = 0xF | [V] |
| 0x5680474 | 8 | sub_567FD70 | W rbp+0x7E0 | `0x5680474  mov qword ptr [rbp+0x7E0],0` | small-string cap = 0 | [V] |
| 0x5680D88 | 8 | sub_567FD70 | R caller dest | `0x5680D88  mov rcx,[rbp+0x8B8]` | caller dest pointer (saved arg rcx) | [V] |
| 0x5680D8F | 8 | sub_567FD70 | R [rbp-0x50] | `0x5680D8F  lea rdx,[rbp-0x50]` | callee out-object {a1,[a1+0],base,end,end} | [V] |
| 0x5680D93 | 4 | sub_567FD70 | - | `0x5680D93  xor r8d,r8d` | | [V] |
| 0x5680D96 | - | sub_567FD70 | - | `0x5680D96 call 0x568B0D0` | DEST WRITE: sub_568b0d0(caller_dest, &callee_out_object, 0) | [V] |
| 0x5680EB4 | - | sub_567FD70 | - | `0x5680EB4 call 0x655CEA0` | DEST WRITE: sub_655CEA0(&[rbp+0x2D0]) second side record | [V] |

### (b-4) sub_56815D0 (vtable data_f25b5B0) — [V]

Same structure; per-element callees sub_568EB90 (flavor 0) / sub_568F030 (flavor 1) / sub_568F4E0 (flavor>=2). Element cursor r14 = [a1+0x10]..[a1+0x18] by 0x290 stride; element data = r14+0x240.

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 0x56815D0 | 1 | sub_56815D0 | - | `0x56815D0  push rbp` | function entry | [V] |
| 0x5681604 | 8 | sub_56815D0 | W [rbp+0x8B8] | `0x5681604  mov [rbp+0x8B8],rcx` | save caller dest pointer | [V] |
| 0x5681612 | 8 | sub_56815D0 | R a1+0x10 | `0x5681612  mov r14,[rdx+0x10]` | element cursor = [a1+0x10] | [V] |
| 0x5681616 | 8 | sub_56815D0 | R a1+0x18 | `0x5681616  mov rax,[rdx+0x18]` | element end = [a1+0x18] | [V] |
| 0x568161A | 8 | sub_56815D0 | W [rbp+0x8E0] | `0x568161A  mov [rbp+0x8E0],rax` | loop end saved | [V] |
| 0x5681621 | 8 | sub_56815D0 | R a1+0x28 | `0x5681621  lea rax,[rdx+0x28]` | a1+0x28 | [V] |
| 0x5681625 | 8 | sub_56815D0 | W [rbp+0x8D0] | `0x5681625  mov [rbp+0x8D0],rax` | | [V] |
| 0x5681641 | 8 | sub_56815D0 | W [rbp+0x958] | `0x5681641  mov [rbp+0x958],rdx` | save a1 | [V] |
| 0x5681648 | 8 | sub_56815D0 | R a1+0x60 | `0x5681648  lea rax,[rdx+0x60]` | a1+0x60 | [V] |
| 0x568164C | 8 | sub_56815D0 | W [rbp+0x8D8] | `0x568164C  mov [rbp+0x8D8],rax` | | [V] |
| 0x568165A | 4 | sub_56815D0 | W [rbp+0x964] | `0x568165A  mov [rbp+0x964],r8d` | pass flavor flag | [V] |
| 0x5681672 | - | sub_56815D0 | - | `0x5681672  add r14,0x290` | next element (0x290 stride) | [V] |
| 0x5681687 | - | sub_56815D0 | - | `0x5681687  cmp r14,[rbp+0x8E0]` | element cursor vs end | [V] |
| 0x568168E | - | sub_56815D0 | - | `0x568168E  je 0x5682A57` | outer loop exit | [V] |
| 0x5681694 | 8 | sub_56815D0 | R elem base | `0x5681694  lea rsi,[r14+0x240]` | element data base = cursor+0x240 | [V] |
| 0x56816B6 | 8 | sub_56815D0 | - | `0x56816B6  lea rax,[0xF25B5B0]` | vtable data_f25b5B0 | [I] |
| 0x56816BD | 8 | sub_56815D0 | W block+0x0 | `0x56816BD  mov [rbp+0x560],rax` | block header+0 = vtable | [V] |
| 0x56816C4 | 8 | sub_56815D0 | W block+0x8 | `0x56816C4  mov [rbp+0x568],rsi` | block header+8 = element data base | [V] |
| 0x56816CB | 8 | sub_56815D0 | W [rbp+0x598] | `0x56816CB  mov [rbp+0x598],rcx` | block pointer | [V] |
| 0x568182D | - | sub_56815D0 | - | `0x568182D  call 0x568EB90` | flavor 0: per-element callee | [V] |
| 0x5681860 | - | sub_56815D0 | - | `0x5681860  call 0x568F030` | flavor 1: per-element callee | [V] |
| 0x568189A | - | sub_56815D0 | - | `0x568189A  call 0x568F4E0` | flavor>=2: per-element callee | [V] |
| 0x5681966 | 8 | sub_56815D0 | R [elem+0x258] | `0x5681966  mov rax,[r14+0x258]` | element field | [V] |
| 0x568196D | 8 | sub_56815D0 | W record+0x0 | `0x568196D  mov [rbp+0x5A0],rax` | record+0x0 = element field | [V] |
| 0x568198F | 4 | sub_56815D0 | W [rax+8] | `0x568198F  lock inc dword ptr [rax+8]` | inc object refcount | [V] |
| 0x56819A2 | 8 | sub_56815D0 | R [elem+0x260] | `0x56819A2  mov rcx,[r14+0x260]` | element field | [V] |
| 0x56819A9 | 8 | sub_56815D0 | W record+0x8 | `0x56819A9  mov [rbp+0x5A8],rcx` | record+0x8 | [V] |
| 0x56819B0 | 8 | sub_56815D0 | W record+0x10 | `0x56819B0  mov [rbp+0x5B0],rax` | record+0x10 | [V] |
| 0x56819B7 | 16 | sub_56815D0 | W rbp+0x5B8 | `0x56819B7  movups [r15-0x200],xmm6` | zero record+0x5B8 (16B) | [V] |
| 0x56819BF | 8 | sub_56815D0 | W rbp+0x5C8 | `0x56819BF  mov qword ptr [r15-0x1F0],0` | record+0x5C8 = 0 | [V] |
| 0x56819CA | 1 | sub_56815D0 | W rbp+0x5D0 | `0x56819CA  mov byte ptr [rbp+0x5D0],1` | flag byte | [V] |
| 0x56819D1 | 1 | sub_56815D0 | W rbp+0x600 | `0x56819D1  mov byte ptr [rbp+0x600],0` | flag byte | [V] |
| 0x56819D8 | 16 | sub_56815D0 | W record+0xD8 | `0x56819D8  movups [rbp+0x5D8],xmm7` | record+0xD8 = callee output entry {a1,[a1+0]} | [V] |
| 0x56819DF | 16 | sub_56815D0 | W rbp+0x5E8 | `0x56819DF  movups [r15-0x1D0],xmm6` | zero record+0x5E8 (16B) | [V] |
| 0x56819E7 | 8 | sub_56815D0 | W rbp+0x5F8 | `0x56819E7  mov qword ptr [r15-0x1C0],0` | record+0x5F8 = 0 | [V] |
| 0x5681A83 | 8 | sub_56815D0 | W record copy start | `0x5681A83  mov [rbp+0x5E8],rsi` | record+0x5E8 = callee-output copy dest start | [V] |
| 0x5681A8A | 8 | sub_56815D0 | W record copy start | `0x5681A8A  mov [rbp+0x5F0],rsi` | record+0x5F0 = copy cursor | [V] |
| 0x5681A9C | 8 | sub_56815D0 | W record copy end | `0x5681A9C  mov [rbp+0x5F8],rdi` | record+0x5F8 = callee-output copy dest end | [V] |
| 0x5681AB0 | - | sub_56815D0 | - | `0x5681AB0  call 0xEEC6DE0` | copy callee output array -> record dest | [V] |
| 0x5681AB5 | 8 | sub_56815D0 | W record copy end | `0x5681AB5  mov [rbp+0x5F0],rdi` | record+0x5F0 = copy end | [V] |
| 0x5681ADF | 8 | sub_56815D0 | W record+0x608 | `0x5681ADF  mov [rbp+0x608],rax` | record+0x608 = entry count | [V] |
| 0x5681AE6 | 16 | sub_56815D0 | R [elem+0x118] | `0x5681AE6  movups xmm0,[r14+0x118]` | element data +0x118 | [V] |
| 0x5681AEE | 16 | sub_56815D0 | W record+0x618 | `0x5681AEE  movups [rbp+0x618],xmm0` | record+0x618 = element data +0x118 | [V] |
| 0x5681AF5 | 16 | sub_56815D0 | R [elem+0x128] | `0x5681AF5  movups xmm0,[r14+0x128]` | | [V] |
| 0x5681AFD | 16 | sub_56815D0 | W record+0x628 | `0x5681AFD  movups [rbp+0x628],xmm0` | | [V] |
| 0x5681B04 | 16 | sub_56815D0 | R [elem+0x138] | `0x5681B04  movups xmm0,[r14+0x138]` | | [V] |
| 0x5681B0C | 16 | sub_56815D0 | W record+0x638 | `0x5681B0C  movups [rbp+0x638],xmm0` | | [V] |
| 0x5681B13 | 16 | sub_56815D0 | R [elem+0x148] | `0x5681B13  movups xmm0,[r14+0x148]` | | [V] |
| 0x5681B1B | 16 | sub_56815D0 | W record+0x648 | `0x5681B1B  movups [rbp+0x648],xmm0` | | [V] |
| 0x5681B22 | 16 | sub_56815D0 | R [elem+0x158] | `0x5681B22  movups xmm0,[r14+0x158]` | | [V] |
| 0x5681B2A | 16 | sub_56815D0 | W record+0x658 | `0x5681B2A  movups [rbp+0x658],xmm0` | | [V] |
| 0x5681B31 | 16 | sub_56815D0 | R [elem+0x168] | `0x5681B31  movups xmm0,[r14+0x168]` | | [V] |
| 0x5681B39 | 16 | sub_56815D0 | W record+0x668 | `0x5681B39  movups [rbp+0x668],xmm0` | | [V] |
| 0x5681B40 | 16 | sub_56815D0 | R [elem+0x178] | `0x5681B40  movups xmm0,[r14+0x178]` | | [V] |
| 0x5681B48 | 16 | sub_56815D0 | W record+0x678 | `0x5681B48  movups [rbp+0x678],xmm0` | | [V] |
| 0x5681B4F | 16 | sub_56815D0 | R [elem+0x188] | `0x5681B4F  movups xmm0,[r14+0x188]` | | [V] |
| 0x5681B57 | 16 | sub_56815D0 | W record+0x688 | `0x5681B57  movups [rbp+0x688],xmm0` | | [V] |
| 0x5681B6F | 16 | sub_56815D0 | R [elem+0x198] | `0x5681B6F  movups xmm0,[rcx]` | element +0x198 | [V] |
| 0x5681B72 | 16 | sub_56815D0 | W rbp+0x698 | `0x5681B72  movups [r15-0x120],xmm0` | record+0x698 = element +0x198 | [V] |
| 0x5681B7A | 16 | sub_56815D0 | R [elem+0x1AC] | `0x5681B7A  movups xmm0,[r14+0x1AC]` | | [V] |
| 0x5681B82 | 16 | sub_56815D0 | W record+0x6AC | `0x5681B82  movups [rbp+0x6AC],xmm0` | element +0x1AC -> record+0x6AC | [V] |
| 0x5681B89 | 16 | sub_56815D0 | R [elem+0x1BC] | `0x5681B89  movups xmm0,[r14+0x1BC]` | | [V] |
| 0x5681B91 | 16 | sub_56815D0 | W record+0x6BC | `0x5681B91  movups [rbp+0x6BC],xmm0` | element +0x1BC -> record+0x6BC | [V] |
| 0x5681B98 | 16 | sub_56815D0 | R [elem+0x1CC] | `0x5681B98  movups xmm0,[r14+0x1CC]` | | [V] |
| 0x5681BA0 | 16 | sub_56815D0 | W record+0x6CC | `0x5681BA0  movups [rbp+0x6CC],xmm0` | element +0x1CC -> record+0x6CC | [V] |
| 0x5681BA7 | 16 | sub_56815D0 | R [elem+0x1DC] | `0x5681BA7  movups xmm0,[r14+0x1DC]` | | [V] |
| 0x5681BAF | 16 | sub_56815D0 | W record+0x6DC | `0x5681BAF  movups [rbp+0x6DC],xmm0` | element +0x1DC -> record+0x6DC | [V] |
| 0x5681BB6 | 16 | sub_56815D0 | R [elem+0x1EC] | `0x5681BB6  movups xmm0,[r14+0x1EC]` | | [V] |
| 0x5681BBE | 16 | sub_56815D0 | W record+0x6EC | `0x5681BBE  movups [rbp+0x6EC],xmm0` | element +0x1EC -> record+0x6EC | [V] |
| 0x5681BC5 | 16 | sub_56815D0 | R [elem+0x1FC] | `0x5681BC5  movups xmm0,[r14+0x1FC]` | | [V] |
| 0x5681BCD | 16 | sub_56815D0 | W record+0x6FC | `0x5681BCD  movups [rbp+0x6FC],xmm0` | element +0x1FC -> record+0x6FC | [V] |
| 0x5681BD4 | 16 | sub_56815D0 | R [elem+0x20C] | `0x5681BD4  movups xmm0,[r14+0x20C]` | | [V] |
| 0x5681BDC | 16 | sub_56815D0 | W record+0x70C | `0x5681BDC  movups [rbp+0x70C],xmm0` | element +0x20C -> record+0x70C | [V] |
| 0x5681BE3 | 16 | sub_56815D0 | R [elem+0x21C] | `0x5681BE3  movups xmm0,[r14+0x21C]` | | [V] |
| 0x5681BEB | 16 | sub_56815D0 | W record+0x71C | `0x5681BEB  movups [rbp+0x71C],xmm0` | element +0x21C -> record+0x71C (last field copy) | [V] |
| 0x5681BF9 | 16 | sub_56815D0 | R [elem+0x22C] | `0x5681BF9  movups xmm0,[rax]` | element +0x22C | [V] |
| 0x5681BFC | 16 | sub_56815D0 | W rbp+0x72C | `0x5681BFC  movups [r15-0x8C],xmm0` | record+0x72C = element +0x22C | [V] |
| 0x5681B65 | 4 | sub_56815D0 | R [elem+0x1A8] | `0x5681B65  mov eax,[rcx+0x10]` | element +0x1A8 | [V] |
| 0x5681B68 | 4 | sub_56815D0 | W rbp+0x6A8 | `0x5681B68  mov [r15-0x110],eax` | record+0x6A8 = element +0x1A8 | [V] |
| 0x5681C1F | 8 | sub_56815D0 | R [a1+0x28] | `0x5681C1F  mov rax,[rbp+0x8D0]` | [a1+0x28] | [V] |
| 0x5681C26 | 16 | sub_56815D0 | R [a1+0x28] | `0x5681C26  movups xmm0,[rax]` | [a1+0x28] float4 | [V] |
| 0x5681C29 | 16 | sub_56815D0 | R [a1+0x28+0x10] | `0x5681C29  movups xmm1,[rax+0x10]` | [a1+0x28+0x10] float4 | [V] |
| 0x5681C2D | 16 | sub_56815D0 | W rbp+0x74C | `0x5681C2D  movups [r15-0x6C],xmm1` | record+0x74C = [a1+0x28] float4 | [V] |
| 0x5681C32 | 16 | sub_56815D0 | W rbp+0x73C | `0x5681C32  movups [r15-0x7C],xmm0` | record+0x73C = [a1+0x28] float4 | [V] |
| 0x5681C52 | 1 | sub_56815D0 | R [a1+0x48] | `0x5681C52  movzx eax,byte ptr [rcx+0x48]` | [a1+0x48] byte | [V] |
| 0x5681C56 | 1 | sub_56815D0 | W rbp+0x75C | `0x5681C56  mov [rbp+0x75C],al` | record+0x75C | [V] |
| 0x5681C5C | 16 | sub_56815D0 | R [a1+0x4C] | `0x5681C5C  movups xmm0,[rcx+0x4C]` | [a1+0x4C] float4 | [V] |
| 0x5681C60 | 16 | sub_56815D0 | W rbp+0x760 | `0x5681C60  movaps [rbp+0x760],xmm0` | record+0x760 | [V] |
| 0x5681C75 | 16 | sub_56815D0 | R [a1+0x60] | `0x5681C75  movups xmm0,[rax]` | [a1+0x60] block | [V] |
| 0x5681C84 | 16 | sub_56815D0 | W rbp+0x782 | `0x5681C84  movups [r15-0x16],xmm3` | ([a1+0x60] block field copy) | [V] |
| 0x5681C9F | 8 | sub_56815D0 | R [rbp+0x608] | `0x5681C9F  mov rax,[rbp+0x608]` | entry count | [V] |
| 0x5681CA6 | 8 | sub_56815D0 | - | `0x5681CA6  add rax,r13` | count + per-entry count | [V] |
| 0x5681CA9 | 8 | sub_56815D0 | W record+0x610 | `0x5681CA9  mov [rbp+0x610],rax` | record+0x610 | [V] |
| 0x5681CB0 | 16 | sub_56815D0 | W rbp+0x7C8 | `0x5681CB0  movups [r15+0x10],xmm6` | zero record+0x7C8 (16B) | [V] |
| 0x5681CB5 | 16 | sub_56815D0 | W rbp+0x7B8 | `0x5681CB5  movups [r15],xmm6` | zero record start (16B) | [V] |
| 0x5681CB9 | 8 | sub_56815D0 | W rbp+0x7D8 | `0x5681CB9  mov qword ptr [rbp+0x7D8],0xF` | small-string size = 0xF | [V] |
| 0x5681CC4 | 8 | sub_56815D0 | W rbp+0x7E0 | `0x5681CC4  mov qword ptr [rbp+0x7E0],0` | small-string cap = 0 | [V] |
| 0x56825D8 | 8 | sub_56815D0 | R caller dest | `0x56825D8  mov rcx,[rbp+0x8B8]` | caller dest pointer (saved arg rcx) | [V] |
| 0x56825DF | 8 | sub_56815D0 | R [rbp-0x50] | `0x56825DF  lea rdx,[rbp-0x50]` | callee out-object {a1,[a1+0],base,end,end} | [V] |
| 0x56825E3 | 4 | sub_56815D0 | - | `0x56825E3  xor r8d,r8d` | | [V] |
| 0x56825E6 | - | sub_56815D0 | - | `0x56825E6 call 0x568B0D0` | DEST WRITE: sub_568b0d0(caller_dest, &callee_out_object, 0) | [V] |
| 0x568192D | - | sub_56815D0 | - | `0x568192D call 0x655CEA0` | DEST WRITE: sub_655CEA0(node_buffer_entry, record) per callee-output entry | [V] |
| 0x5682704 | - | sub_56815D0 | - | `0x5682704 call 0x655CEA0` | DEST WRITE: sub_655CEA0(&[rbp+0x2D0]) second side record | [V] |

### (b-5) sub_5682E20 (vtable data_f25b610) — [V]

Same structure; per-element callees sub_568FA60 (flavor 0) / sub_568FF10 (flavor 1) / sub_56903D0 (flavor>=2). Element cursor r14 = [a1+0x10]..[a1+0x18] by 0x290 stride; element data = r14+0x240.

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 0x5682E20 | 1 | sub_5682E20 | - | `0x5682E20  push rbp` | function entry | [V] |
| 0x5682E54 | 8 | sub_5682E20 | W [rbp+0x8B8] | `0x5682E54  mov [rbp+0x8B8],rcx` | save caller dest pointer | [V] |
| 0x5682E62 | 8 | sub_5682E20 | R a1+0x10 | `0x5682E62  mov r14,[rdx+0x10]` | element cursor = [a1+0x10] | [V] |
| 0x5682E66 | 8 | sub_5682E20 | R a1+0x18 | `0x5682E66  mov rax,[rdx+0x18]` | element end = [a1+0x18] | [V] |
| 0x5682E6A | 8 | sub_5682E20 | W [rbp+0x8E0] | `0x5682E6A  mov [rbp+0x8E0],rax` | loop end saved | [V] |
| 0x5682E71 | 8 | sub_5682E20 | R a1+0x28 | `0x5682E71  lea rax,[rdx+0x28]` | a1+0x28 | [V] |
| 0x5682E75 | 8 | sub_5682E20 | W [rbp+0x8D0] | `0x5682E75  mov [rbp+0x8D0],rax` | | [V] |
| 0x5682E91 | 8 | sub_5682E20 | W [rbp+0x958] | `0x5682E91  mov [rbp+0x958],rdx` | save a1 | [V] |
| 0x5682E98 | 8 | sub_5682E20 | R a1+0x60 | `0x5682E98  lea rax,[rdx+0x60]` | a1+0x60 | [V] |
| 0x5682E9C | 8 | sub_5682E20 | W [rbp+0x8D8] | `0x5682E9C  mov [rbp+0x8D8],rax` | | [V] |
| 0x5682EA3 | 4 | sub_5682E20 | W [rbp+0x964] | `0x5682EA3  mov [rbp+0x964],r8d` | pass flavor flag | [V] |
| 0x5682EBB | - | sub_5682E20 | - | `0x5682EBB  add r14,0x290` | next element (0x290 stride) | [V] |
| 0x5682EC2 | - | sub_5682E20 | - | `0x5682EC2  cmp r14,[rbp+0x8E0]` | element cursor vs end | [V] |
| 0x5682EC9 | - | sub_5682E20 | - | `0x5682EC9  je 0x5684297` | outer loop exit | [V] |
| 0x5682ECF | 8 | sub_5682E20 | R elem base | `0x5682ECF  lea rsi,[r14+0x240]` | element data base = cursor+0x240 | [V] |
| 0x5682EEE | 8 | sub_5682E20 | - | `0x5682EEE  lea rax,[0xF25B610]` | vtable data_f25b610 | [I] |
| 0x5682EF5 | 8 | sub_5682E20 | W block+0x0 | `0x5682EF5  mov [rbp+0x560],rax` | block header+0 = vtable | [V] |
| 0x5682EFC | 8 | sub_5682E20 | W block+0x8 | `0x5682EFC  mov [rbp+0x568],rsi` | block header+8 = element data base | [V] |
| 0x5682F0A | 8 | sub_5682E20 | W [rbp+0x598] | `0x5682F0A  mov [rbp+0x598],rax` | block pointer | [V] |
| 0x5683070 | - | sub_5682E20 | - | `0x5683070  call 0x568FA60` | flavor 0: per-element callee | [V] |
| 0x56830A3 | - | sub_5682E20 | - | `0x56830A3  call 0x568FF10` | flavor 1: per-element callee | [V] |
| 0x56830DD | - | sub_5682E20 | - | `0x56830DD  call 0x56903D0` | flavor>=2: per-element callee | [V] |
| 0x56831A6 | 8 | sub_5682E20 | R [elem+0x258] | `0x56831A6  mov rax,[r14+0x258]` | element field | [V] |
| 0x56831AD | 8 | sub_5682E20 | W record+0x0 | `0x56831AD  mov [rbp+0x5A0],rax` | record+0x0 = element field | [V] |
| 0x56831CF | 4 | sub_5682E20 | W [rax+8] | `0x56831CF  lock inc dword ptr [rax+8]` | inc object refcount | [V] |
| 0x56831E2 | 8 | sub_5682E20 | R [elem+0x260] | `0x56831E2  mov rcx,[r14+0x260]` | element field | [V] |
| 0x56831E9 | 8 | sub_5682E20 | W record+0x8 | `0x56831E9  mov [rbp+0x5A8],rcx` | record+0x8 | [V] |
| 0x56831F0 | 8 | sub_5682E20 | W record+0x10 | `0x56831F0  mov [rbp+0x5B0],rax` | record+0x10 | [V] |
| 0x56831F7 | 16 | sub_5682E20 | W rbp+0x5B8 | `0x56831F7  movups [r15-0x200],xmm6` | zero record+0x5B8 (16B) | [V] |
| 0x56831FF | 8 | sub_5682E20 | W rbp+0x5C8 | `0x56831FF  mov qword ptr [r15-0x1F0],0` | record+0x5C8 = 0 | [V] |
| 0x568320A | 1 | sub_5682E20 | W rbp+0x5D0 | `0x568320A  mov byte ptr [rbp+0x5D0],1` | flag byte | [V] |
| 0x5683211 | 1 | sub_5682E20 | W rbp+0x600 | `0x5683211  mov byte ptr [rbp+0x600],0` | flag byte | [V] |
| 0x5683218 | 16 | sub_5682E20 | W record+0xD8 | `0x5683218  movups [rbp+0x5D8],xmm7` | record+0xD8 = callee output entry {a1,[a1+0]} | [V] |
| 0x568321F | 16 | sub_5682E20 | W rbp+0x5E8 | `0x568321F  movups [r15-0x1D0],xmm6` | zero record+0x5E8 (16B) | [V] |
| 0x5683227 | 8 | sub_5682E20 | W rbp+0x5F8 | `0x5683227  mov qword ptr [r15-0x1C0],0` | record+0x5F8 = 0 | [V] |
| 0x56832C3 | 8 | sub_5682E20 | W record copy start | `0x56832C3  mov [rbp+0x5E8],rsi` | record+0x5E8 = callee-output copy dest start | [V] |
| 0x56832CA | 8 | sub_5682E20 | W record copy start | `0x56832CA  mov [rbp+0x5F0],rsi` | record+0x5F0 = copy cursor | [V] |
| 0x56832DC | 8 | sub_5682E20 | W record copy end | `0x56832DC  mov [rbp+0x5F8],rdi` | record+0x5F8 = callee-output copy dest end | [V] |
| 0x56832F0 | - | sub_5682E20 | - | `0x56832F0  call 0xEEC6DE0` | copy callee output array -> record dest | [V] |
| 0x56832F5 | 8 | sub_5682E20 | W record copy end | `0x56832F5  mov [rbp+0x5F0],rdi` | record+0x5F0 = copy end | [V] |
| 0x568331F | 8 | sub_5682E20 | W record+0x608 | `0x568331F  mov [rbp+0x608],rax` | record+0x608 = entry count | [V] |
| 0x5683326 | 16 | sub_5682E20 | R [elem+0x118] | `0x5683326  movups xmm0,[r14+0x118]` | element data +0x118 | [V] |
| 0x568332E | 16 | sub_5682E20 | W record+0x618 | `0x568332E  movups [rbp+0x618],xmm0` | record+0x618 = element data +0x118 | [V] |
| 0x5683335 | 16 | sub_5682E20 | R [elem+0x128] | `0x5683335  movups xmm0,[r14+0x128]` | | [V] |
| 0x568333D | 16 | sub_5682E20 | W record+0x628 | `0x568333D  movups [rbp+0x628],xmm0` | | [V] |
| 0x5683344 | 16 | sub_5682E20 | R [elem+0x138] | `0x5683344  movups xmm0,[r14+0x138]` | | [V] |
| 0x568334C | 16 | sub_5682E20 | W record+0x638 | `0x568334C  movups [rbp+0x638],xmm0` | | [V] |
| 0x5683353 | 16 | sub_5682E20 | R [elem+0x148] | `0x5683353  movups xmm0,[r14+0x148]` | | [V] |
| 0x568335B | 16 | sub_5682E20 | W record+0x648 | `0x568335B  movups [rbp+0x648],xmm0` | | [V] |
| 0x5683362 | 16 | sub_5682E20 | R [elem+0x158] | `0x5683362  movups xmm0,[r14+0x158]` | | [V] |
| 0x568336A | 16 | sub_5682E20 | W record+0x658 | `0x568336A  movups [rbp+0x658],xmm0` | | [V] |
| 0x5683371 | 16 | sub_5682E20 | R [elem+0x168] | `0x5683371  movups xmm0,[r14+0x168]` | | [V] |
| 0x5683379 | 16 | sub_5682E20 | W record+0x668 | `0x5683379  movups [rbp+0x668],xmm0` | | [V] |
| 0x5683380 | 16 | sub_5682E20 | R [elem+0x178] | `0x5683380  movups xmm0,[r14+0x178]` | | [V] |
| 0x5683388 | 16 | sub_5682E20 | W record+0x678 | `0x5683388  movups [rbp+0x678],xmm0` | | [V] |
| 0x568338F | 16 | sub_5682E20 | R [elem+0x188] | `0x568338F  movups xmm0,[r14+0x188]` | | [V] |
| 0x5683397 | 16 | sub_5682E20 | W record+0x688 | `0x5683397  movups [rbp+0x688],xmm0` | | [V] |
| 0x56833AF | 16 | sub_5682E20 | R [elem+0x198] | `0x56833AF  movups xmm0,[rcx]` | element +0x198 | [V] |
| 0x56833B2 | 16 | sub_5682E20 | W rbp+0x698 | `0x56833B2  movups [r15-0x120],xmm0` | record+0x698 = element +0x198 | [V] |
| 0x56833BA | 16 | sub_5682E20 | R [elem+0x1AC] | `0x56833BA  movups xmm0,[r14+0x1AC]` | | [V] |
| 0x56833C2 | 16 | sub_5682E20 | W record+0x6AC | `0x56833C2  movups [rbp+0x6AC],xmm0` | element +0x1AC -> record+0x6AC | [V] |
| 0x56833C9 | 16 | sub_5682E20 | R [elem+0x1BC] | `0x56833C9  movups xmm0,[r14+0x1BC]` | | [V] |
| 0x56833D1 | 16 | sub_5682E20 | W record+0x6BC | `0x56833D1  movups [rbp+0x6BC],xmm0` | element +0x1BC -> record+0x6BC | [V] |
| 0x56833D8 | 16 | sub_5682E20 | R [elem+0x1CC] | `0x56833D8  movups xmm0,[r14+0x1CC]` | | [V] |
| 0x56833E0 | 16 | sub_5682E20 | W record+0x6CC | `0x56833E0  movups [rbp+0x6CC],xmm0` | element +0x1CC -> record+0x6CC | [V] |
| 0x56833E7 | 16 | sub_5682E20 | R [elem+0x1DC] | `0x56833E7  movups xmm0,[r14+0x1DC]` | | [V] |
| 0x56833EF | 16 | sub_5682E20 | W record+0x6DC | `0x56833EF  movups [rbp+0x6DC],xmm0` | element +0x1DC -> record+0x6DC | [V] |
| 0x56833F6 | 16 | sub_5682E20 | R [elem+0x1EC] | `0x56833F6  movups xmm0,[r14+0x1EC]` | | [V] |
| 0x56833FE | 16 | sub_5682E20 | W record+0x6EC | `0x56833FE  movups [rbp+0x6EC],xmm0` | element +0x1EC -> record+0x6EC | [V] |
| 0x5683405 | 16 | sub_5682E20 | R [elem+0x1FC] | `0x5683405  movups xmm0,[r14+0x1FC]` | | [V] |
| 0x568340D | 16 | sub_5682E20 | W record+0x6FC | `0x568340D  movups [rbp+0x6FC],xmm0` | element +0x1FC -> record+0x6FC | [V] |
| 0x5683414 | 16 | sub_5682E20 | R [elem+0x20C] | `0x5683414  movups xmm0,[r14+0x20C]` | | [V] |
| 0x568341C | 16 | sub_5682E20 | W record+0x70C | `0x568341C  movups [rbp+0x70C],xmm0` | element +0x20C -> record+0x70C | [V] |
| 0x5683423 | 16 | sub_5682E20 | R [elem+0x21C] | `0x5683423  movups xmm0,[r14+0x21C]` | | [V] |
| 0x568342B | 16 | sub_5682E20 | W record+0x71C | `0x568342B  movups [rbp+0x71C],xmm0` | element +0x21C -> record+0x71C (last field copy) | [V] |
| 0x5683439 | 16 | sub_5682E20 | R [elem+0x22C] | `0x5683439  movups xmm0,[rax]` | element +0x22C | [V] |
| 0x568343C | 16 | sub_5682E20 | W rbp+0x72C | `0x568343C  movups [r15-0x8C],xmm0` | record+0x72C = element +0x22C | [V] |
| 0x56833A5 | 4 | sub_5682E20 | R [elem+0x1A8] | `0x56833A5  mov eax,[rcx+0x10]` | element +0x1A8 | [V] |
| 0x56833A8 | 4 | sub_5682E20 | W rbp+0x6A8 | `0x56833A8  mov [r15-0x110],eax` | record+0x6A8 = element +0x1A8 | [V] |
| 0x568345F | 8 | sub_5682E20 | R [a1+0x28] | `0x568345F  mov rax,[rbp+0x8D0]` | [a1+0x28] | [V] |
| 0x5683466 | 16 | sub_5682E20 | R [a1+0x28] | `0x5683466  movups xmm0,[rax]` | [a1+0x28] float4 | [V] |
| 0x5683469 | 16 | sub_5682E20 | R [a1+0x28+0x10] | `0x5683469  movups xmm1,[rax+0x10]` | [a1+0x28+0x10] float4 | [V] |
| 0x568346D | 16 | sub_5682E20 | W rbp+0x74C | `0x568346D  movups [r15-0x6C],xmm1` | record+0x74C = [a1+0x28] float4 | [V] |
| 0x5683472 | 16 | sub_5682E20 | W rbp+0x73C | `0x5683472  movups [r15-0x7C],xmm0` | record+0x73C = [a1+0x28] float4 | [V] |
| 0x5683492 | 1 | sub_5682E20 | R [a1+0x48] | `0x5683492  movzx eax,byte ptr [rcx+0x48]` | [a1+0x48] byte | [V] |
| 0x5683496 | 1 | sub_5682E20 | W rbp+0x75C | `0x5683496  mov [rbp+0x75C],al` | record+0x75C | [V] |
| 0x568349C | 16 | sub_5682E20 | R [a1+0x4C] | `0x568349C  movups xmm0,[rcx+0x4C]` | [a1+0x4C] float4 | [V] |
| 0x56834A0 | 16 | sub_5682E20 | W rbp+0x760 | `0x56834A0  movaps [rbp+0x760],xmm0` | record+0x760 | [V] |
| 0x56834B5 | 16 | sub_5682E20 | R [a1+0x60] | `0x56834B5  movups xmm0,[rax]` | [a1+0x60] block | [V] |
| 0x56834C4 | 16 | sub_5682E20 | W rbp+0x782 | `0x56834C4  movups [r15-0x16],xmm3` | ([a1+0x60] block field copy) | [V] |
| 0x56834DF | 8 | sub_5682E20 | R [rbp+0x608] | `0x56834DF  mov rax,[rbp+0x608]` | entry count | [V] |
| 0x56834E6 | 8 | sub_5682E20 | - | `0x56834E6  add rax,r13` | count + per-entry count | [V] |
| 0x56834E9 | 8 | sub_5682E20 | W record+0x610 | `0x56834E9  mov [rbp+0x610],rax` | record+0x610 | [V] |
| 0x56834F0 | 16 | sub_5682E20 | W rbp+0x7C8 | `0x56834F0  movups [r15+0x10],xmm6` | zero record+0x7C8 (16B) | [V] |
| 0x56834F5 | 16 | sub_5682E20 | W rbp+0x7B8 | `0x56834F5  movups [r15],xmm6` | zero record start (16B) | [V] |
| 0x56834F9 | 8 | sub_5682E20 | W rbp+0x7D8 | `0x56834F9  mov qword ptr [rbp+0x7D8],0xF` | small-string size = 0xF | [V] |
| 0x5683504 | 8 | sub_5682E20 | W rbp+0x7E0 | `0x5683504  mov qword ptr [rbp+0x7E0],0` | small-string cap = 0 | [V] |
| 0x5683E18 | 8 | sub_5682E20 | R caller dest | `0x5683E18  mov rcx,[rbp+0x8B8]` | caller dest pointer (saved arg rcx) | [V] |
| 0x5683E1F | 8 | sub_5682E20 | R [rbp-0x50] | `0x5683E1F  lea rdx,[rbp-0x50]` | callee out-object {a1,[a1+0],base,end,end} | [V] |
| 0x5683E23 | 4 | sub_5682E20 | - | `0x5683E23  xor r8d,r8d` | | [V] |
| 0x5683E26 | - | sub_5682E20 | - | `0x5683E26 call 0x568B0D0` | DEST WRITE: sub_568b0d0(caller_dest, &callee_out_object, 0) | [V] |
| 0x568316D | - | sub_5682E20 | - | `0x568316D call 0x655CEA0` | DEST WRITE: sub_655CEA0(node_buffer_entry, record) per callee-output entry | [V] |
| 0x5683F44 | - | sub_5682E20 | - | `0x5683F44 call 0x655CEA0` | DEST WRITE: sub_655CEA0(&[rbp+0x2D0]) second side record | [V] |

### (b-6) sub_5685EA0 (vtable data_f25b6d0) — [V]

Same structure; per-element callees sub_5691860 (flavor 0) / sub_5691D00 (flavor 1) / sub_56921B0 (flavor>=2). Element cursor r14 = [a1+0x10]..[a1+0x18] by 0x290 stride; element data = r14+0x240.

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 0x5685EA0 | 1 | sub_5685EA0 | - | `0x5685EA0  push rbp` | function entry | [V] |
| 0x5685ED4 | 8 | sub_5685EA0 | W [rbp+0x8B8] | `0x5685ED4  mov [rbp+0x8B8],rcx` | save caller dest pointer | [V] |
| 0x5685EE2 | 8 | sub_5685EA0 | R a1+0x10 | `0x5685EE2  mov r14,[rdx+0x10]` | element cursor = [a1+0x10] | [V] |
| 0x5685EE6 | 8 | sub_5685EA0 | R a1+0x18 | `0x5685EE6  mov rax,[rdx+0x18]` | element end = [a1+0x18] | [V] |
| 0x5685EEA | 8 | sub_5685EA0 | W [rbp+0x8E0] | `0x5685EEA  mov [rbp+0x8E0],rax` | loop end saved | [V] |
| 0x5685EF1 | 8 | sub_5685EA0 | R a1+0x28 | `0x5685EF1  lea rax,[rdx+0x28]` | a1+0x28 | [V] |
| 0x5685EF5 | 8 | sub_5685EA0 | W [rbp+0x8D0] | `0x5685EF5  mov [rbp+0x8D0],rax` | | [V] |
| 0x5685F11 | 8 | sub_5685EA0 | W [rbp+0x958] | `0x5685F11  mov [rbp+0x958],rdx` | save a1 | [V] |
| 0x5685F18 | 8 | sub_5685EA0 | R a1+0x60 | `0x5685F18  lea rax,[rdx+0x60]` | a1+0x60 | [V] |
| 0x5685F1C | 8 | sub_5685EA0 | W [rbp+0x8D8] | `0x5685F1C  mov [rbp+0x8D8],rax` | | [V] |
| 0x5685F2A | 4 | sub_5685EA0 | W [rbp+0x964] | `0x5685F2A  mov [rbp+0x964],r8d` | pass flavor flag | [V] |
| 0x5685F42 | - | sub_5685EA0 | - | `0x5685F42  add r14,0x290` | next element (0x290 stride) | [V] |
| 0x5685F57 | - | sub_5685EA0 | - | `0x5685F57  cmp r14,[rbp+0x8E0]` | element cursor vs end | [V] |
| 0x5685F5E | - | sub_5685EA0 | - | `0x5685F5E  je 0x5687327` | outer loop exit | [V] |
| 0x5685F64 | 8 | sub_5685EA0 | R elem base | `0x5685F64  lea rsi,[r14+0x240]` | element data base = cursor+0x240 | [V] |
| 0x5685F86 | 8 | sub_5685EA0 | - | `0x5685F86  lea rax,[0xF25B6D0]` | vtable data_f25b6d0 | [I] |
| 0x5685F8D | 8 | sub_5685EA0 | W block+0x0 | `0x5685F8D  mov [rbp+0x560],rax` | block header+0 = vtable | [V] |
| 0x5685F94 | 8 | sub_5685EA0 | W block+0x8 | `0x5685F94  mov [rbp+0x568],rsi` | block header+8 = element data base | [V] |
| 0x5685F9B | 8 | sub_5685EA0 | W [rbp+0x598] | `0x5685F9B  mov [rbp+0x598],rcx` | block pointer | [V] |
| 0x56860FD | - | sub_5685EA0 | - | `0x56860FD  call 0x5691860` | flavor 0: per-element callee | [V] |
| 0x5686130 | - | sub_5685EA0 | - | `0x5686130  call 0x5691D00` | flavor 1: per-element callee | [V] |
| 0x568616A | - | sub_5685EA0 | - | `0x568616A  call 0x56921B0` | flavor>=2: per-element callee | [V] |
| 0x5686236 | 8 | sub_5685EA0 | R [elem+0x258] | `0x5686236  mov rax,[r14+0x258]` | element field | [V] |
| 0x568623D | 8 | sub_5685EA0 | W record+0x0 | `0x568623D  mov [rbp+0x5A0],rax` | record+0x0 = element field | [V] |
| 0x568625F | 4 | sub_5685EA0 | W [rax+8] | `0x568625F  lock inc dword ptr [rax+8]` | inc object refcount | [V] |
| 0x5686272 | 8 | sub_5685EA0 | R [elem+0x260] | `0x5686272  mov rcx,[r14+0x260]` | element field | [V] |
| 0x5686279 | 8 | sub_5685EA0 | W record+0x8 | `0x5686279  mov [rbp+0x5A8],rcx` | record+0x8 | [V] |
| 0x5686280 | 8 | sub_5685EA0 | W record+0x10 | `0x5686280  mov [rbp+0x5B0],rax` | record+0x10 | [V] |
| 0x5686287 | 16 | sub_5685EA0 | W rbp+0x5B8 | `0x5686287  movups [r15-0x200],xmm6` | zero record+0x5B8 (16B) | [V] |
| 0x568628F | 8 | sub_5685EA0 | W rbp+0x5C8 | `0x568628F  mov qword ptr [r15-0x1F0],0` | record+0x5C8 = 0 | [V] |
| 0x568629A | 1 | sub_5685EA0 | W rbp+0x5D0 | `0x568629A  mov byte ptr [rbp+0x5D0],1` | flag byte | [V] |
| 0x56862A1 | 1 | sub_5685EA0 | W rbp+0x600 | `0x56862A1  mov byte ptr [rbp+0x600],0` | flag byte | [V] |
| 0x56862A8 | 16 | sub_5685EA0 | W record+0xD8 | `0x56862A8  movups [rbp+0x5D8],xmm7` | record+0xD8 = callee output entry {a1,[a1+0]} | [V] |
| 0x56862AF | 16 | sub_5685EA0 | W rbp+0x5E8 | `0x56862AF  movups [r15-0x1D0],xmm6` | zero record+0x5E8 (16B) | [V] |
| 0x56862B7 | 8 | sub_5685EA0 | W rbp+0x5F8 | `0x56862B7  mov qword ptr [r15-0x1C0],0` | record+0x5F8 = 0 | [V] |
| 0x5686353 | 8 | sub_5685EA0 | W record copy start | `0x5686353  mov [rbp+0x5E8],rsi` | record+0x5E8 = callee-output copy dest start | [V] |
| 0x568635A | 8 | sub_5685EA0 | W record copy start | `0x568635A  mov [rbp+0x5F0],rsi` | record+0x5F0 = copy cursor | [V] |
| 0x568636C | 8 | sub_5685EA0 | W record copy end | `0x568636C  mov [rbp+0x5F8],rdi` | record+0x5F8 = callee-output copy dest end | [V] |
| 0x5686380 | - | sub_5685EA0 | - | `0x5686380  call 0xEEC6DE0` | copy callee output array -> record dest | [V] |
| 0x5686385 | 8 | sub_5685EA0 | W record copy end | `0x5686385  mov [rbp+0x5F0],rdi` | record+0x5F0 = copy end | [V] |
| 0x56863AF | 8 | sub_5685EA0 | W record+0x608 | `0x56863AF  mov [rbp+0x608],rax` | record+0x608 = entry count | [V] |
| 0x56863B6 | 16 | sub_5685EA0 | R [elem+0x118] | `0x56863B6  movups xmm0,[r14+0x118]` | element data +0x118 | [V] |
| 0x56863BE | 16 | sub_5685EA0 | W record+0x618 | `0x56863BE  movups [rbp+0x618],xmm0` | record+0x618 = element data +0x118 | [V] |
| 0x56863C5 | 16 | sub_5685EA0 | R [elem+0x128] | `0x56863C5  movups xmm0,[r14+0x128]` | | [V] |
| 0x56863CD | 16 | sub_5685EA0 | W record+0x628 | `0x56863CD  movups [rbp+0x628],xmm0` | | [V] |
| 0x56863D4 | 16 | sub_5685EA0 | R [elem+0x138] | `0x56863D4  movups xmm0,[r14+0x138]` | | [V] |
| 0x56863DC | 16 | sub_5685EA0 | W record+0x638 | `0x56863DC  movups [rbp+0x638],xmm0` | | [V] |
| 0x56863E3 | 16 | sub_5685EA0 | R [elem+0x148] | `0x56863E3  movups xmm0,[r14+0x148]` | | [V] |
| 0x56863EB | 16 | sub_5685EA0 | W record+0x648 | `0x56863EB  movups [rbp+0x648],xmm0` | | [V] |
| 0x56863F2 | 16 | sub_5685EA0 | R [elem+0x158] | `0x56863F2  movups xmm0,[r14+0x158]` | | [V] |
| 0x56863FA | 16 | sub_5685EA0 | W record+0x658 | `0x56863FA  movups [rbp+0x658],xmm0` | | [V] |
| 0x5686401 | 16 | sub_5685EA0 | R [elem+0x168] | `0x5686401  movups xmm0,[r14+0x168]` | | [V] |
| 0x5686409 | 16 | sub_5685EA0 | W record+0x668 | `0x5686409  movups [rbp+0x668],xmm0` | | [V] |
| 0x5686410 | 16 | sub_5685EA0 | R [elem+0x178] | `0x5686410  movups xmm0,[r14+0x178]` | | [V] |
| 0x5686418 | 16 | sub_5685EA0 | W record+0x678 | `0x5686418  movups [rbp+0x678],xmm0` | | [V] |
| 0x568641F | 16 | sub_5685EA0 | R [elem+0x188] | `0x568641F  movups xmm0,[r14+0x188]` | | [V] |
| 0x5686427 | 16 | sub_5685EA0 | W record+0x688 | `0x5686427  movups [rbp+0x688],xmm0` | | [V] |
| 0x568643F | 16 | sub_5685EA0 | R [elem+0x198] | `0x568643F  movups xmm0,[rcx]` | element +0x198 | [V] |
| 0x5686442 | 16 | sub_5685EA0 | W rbp+0x698 | `0x5686442  movups [r15-0x120],xmm0` | record+0x698 = element +0x198 | [V] |
| 0x568644A | 16 | sub_5685EA0 | R [elem+0x1AC] | `0x568644A  movups xmm0,[r14+0x1AC]` | | [V] |
| 0x5686452 | 16 | sub_5685EA0 | W record+0x6AC | `0x5686452  movups [rbp+0x6AC],xmm0` | element +0x1AC -> record+0x6AC | [V] |
| 0x5686459 | 16 | sub_5685EA0 | R [elem+0x1BC] | `0x5686459  movups xmm0,[r14+0x1BC]` | | [V] |
| 0x5686461 | 16 | sub_5685EA0 | W record+0x6BC | `0x5686461  movups [rbp+0x6BC],xmm0` | element +0x1BC -> record+0x6BC | [V] |
| 0x5686468 | 16 | sub_5685EA0 | R [elem+0x1CC] | `0x5686468  movups xmm0,[r14+0x1CC]` | | [V] |
| 0x5686470 | 16 | sub_5685EA0 | W record+0x6CC | `0x5686470  movups [rbp+0x6CC],xmm0` | element +0x1CC -> record+0x6CC | [V] |
| 0x5686477 | 16 | sub_5685EA0 | R [elem+0x1DC] | `0x5686477  movups xmm0,[r14+0x1DC]` | | [V] |
| 0x568647F | 16 | sub_5685EA0 | W record+0x6DC | `0x568647F  movups [rbp+0x6DC],xmm0` | element +0x1DC -> record+0x6DC | [V] |
| 0x5686486 | 16 | sub_5685EA0 | R [elem+0x1EC] | `0x5686486  movups xmm0,[r14+0x1EC]` | | [V] |
| 0x568648E | 16 | sub_5685EA0 | W record+0x6EC | `0x568648E  movups [rbp+0x6EC],xmm0` | element +0x1EC -> record+0x6EC | [V] |
| 0x5686495 | 16 | sub_5685EA0 | R [elem+0x1FC] | `0x5686495  movups xmm0,[r14+0x1FC]` | | [V] |
| 0x568649D | 16 | sub_5685EA0 | W record+0x6FC | `0x568649D  movups [rbp+0x6FC],xmm0` | element +0x1FC -> record+0x6FC | [V] |
| 0x56864A4 | 16 | sub_5685EA0 | R [elem+0x20C] | `0x56864A4  movups xmm0,[r14+0x20C]` | | [V] |
| 0x56864AC | 16 | sub_5685EA0 | W record+0x70C | `0x56864AC  movups [rbp+0x70C],xmm0` | element +0x20C -> record+0x70C | [V] |
| 0x56864B3 | 16 | sub_5685EA0 | R [elem+0x21C] | `0x56864B3  movups xmm0,[r14+0x21C]` | | [V] |
| 0x56864BB | 16 | sub_5685EA0 | W record+0x71C | `0x56864BB  movups [rbp+0x71C],xmm0` | element +0x21C -> record+0x71C (last field copy) | [V] |
| 0x56864C9 | 16 | sub_5685EA0 | R [elem+0x22C] | `0x56864C9  movups xmm0,[rax]` | element +0x22C | [V] |
| 0x56864CC | 16 | sub_5685EA0 | W rbp+0x72C | `0x56864CC  movups [r15-0x8C],xmm0` | record+0x72C = element +0x22C | [V] |
| 0x5686435 | 4 | sub_5685EA0 | R [elem+0x1A8] | `0x5686435  mov eax,[rcx+0x10]` | element +0x1A8 | [V] |
| 0x5686438 | 4 | sub_5685EA0 | W rbp+0x6A8 | `0x5686438  mov [r15-0x110],eax` | record+0x6A8 = element +0x1A8 | [V] |
| 0x56864EF | 8 | sub_5685EA0 | R [a1+0x28] | `0x56864EF  mov rax,[rbp+0x8D0]` | [a1+0x28] | [V] |
| 0x56864F6 | 16 | sub_5685EA0 | R [a1+0x28] | `0x56864F6  movups xmm0,[rax]` | [a1+0x28] float4 | [V] |
| 0x56864F9 | 16 | sub_5685EA0 | R [a1+0x28+0x10] | `0x56864F9  movups xmm1,[rax+0x10]` | [a1+0x28+0x10] float4 | [V] |
| 0x56864FD | 16 | sub_5685EA0 | W rbp+0x74C | `0x56864FD  movups [r15-0x6C],xmm1` | record+0x74C = [a1+0x28] float4 | [V] |
| 0x5686502 | 16 | sub_5685EA0 | W rbp+0x73C | `0x5686502  movups [r15-0x7C],xmm0` | record+0x73C = [a1+0x28] float4 | [V] |
| 0x5686522 | 1 | sub_5685EA0 | R [a1+0x48] | `0x5686522  movzx eax,byte ptr [rcx+0x48]` | [a1+0x48] byte | [V] |
| 0x5686526 | 1 | sub_5685EA0 | W rbp+0x75C | `0x5686526  mov [rbp+0x75C],al` | record+0x75C | [V] |
| 0x568652C | 16 | sub_5685EA0 | R [a1+0x4C] | `0x568652C  movups xmm0,[rcx+0x4C]` | [a1+0x4C] float4 | [V] |
| 0x5686530 | 16 | sub_5685EA0 | W rbp+0x760 | `0x5686530  movaps [rbp+0x760],xmm0` | record+0x760 | [V] |
| 0x5686545 | 16 | sub_5685EA0 | R [a1+0x60] | `0x5686545  movups xmm0,[rax]` | [a1+0x60] block | [V] |
| 0x5686554 | 16 | sub_5685EA0 | W rbp+0x782 | `0x5686554  movups [r15-0x16],xmm3` | ([a1+0x60] block field copy) | [V] |
| 0x568656F | 8 | sub_5685EA0 | R [rbp+0x608] | `0x568656F  mov rax,[rbp+0x608]` | entry count | [V] |
| 0x5686576 | 8 | sub_5685EA0 | - | `0x5686576  add rax,r13` | count + per-entry count | [V] |
| 0x5686579 | 8 | sub_5685EA0 | W record+0x610 | `0x5686579  mov [rbp+0x610],rax` | record+0x610 | [V] |
| 0x5686580 | 16 | sub_5685EA0 | W rbp+0x7C8 | `0x5686580  movups [r15+0x10],xmm6` | zero record+0x7C8 (16B) | [V] |
| 0x5686585 | 16 | sub_5685EA0 | W rbp+0x7B8 | `0x5686585  movups [r15],xmm6` | zero record start (16B) | [V] |
| 0x5686589 | 8 | sub_5685EA0 | W rbp+0x7D8 | `0x5686589  mov qword ptr [rbp+0x7D8],0xF` | small-string size = 0xF | [V] |
| 0x5686594 | 8 | sub_5685EA0 | W rbp+0x7E0 | `0x5686594  mov qword ptr [rbp+0x7E0],0` | small-string cap = 0 | [V] |
| 0x5686EA8 | 8 | sub_5685EA0 | R caller dest | `0x5686EA8  mov rcx,[rbp+0x8B8]` | caller dest pointer (saved arg rcx) | [V] |
| 0x5686EAF | 8 | sub_5685EA0 | R [rbp-0x50] | `0x5686EAF  lea rdx,[rbp-0x50]` | callee out-object {a1,[a1+0],base,end,end} | [V] |
| 0x5686EB3 | 4 | sub_5685EA0 | - | `0x5686EB3  xor r8d,r8d` | | [V] |
| 0x5686EB6 | - | sub_5685EA0 | - | `0x5686EB6 call 0x568B0D0` | DEST WRITE: sub_568b0d0(caller_dest, &callee_out_object, 0) | [V] |
| 0x56861FD | - | sub_5685EA0 | - | `0x56861FD call 0x655CEA0` | DEST WRITE: sub_655CEA0(node_buffer_entry, record) per callee-output entry | [V] |
| 0x5686FD4 | - | sub_5685EA0 | - | `0x5686FD4 call 0x655CEA0` | DEST WRITE: sub_655CEA0(&[rbp+0x2D0]) second side record | [V] |

### (b-7) sub_56876F0 (vtable data_f25b730) — [V]

Same structure; per-element callees sub_5692730 (flavor 0) / sub_5692C00 (flavor 1) / sub_56930E0 (flavor>=2). Element cursor r14 = [a1+0x10]..[a1+0x18] by 0x290 stride; element data = r14+0x240.

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 0x56876F0 | 1 | sub_56876F0 | - | `0x56876F0  push rbp` | function entry | [V] |
| 0x5687724 | 8 | sub_56876F0 | W [rbp+0x8B8] | `0x5687724  mov [rbp+0x8B8],rcx` | save caller dest pointer | [V] |
| 0x5687732 | 8 | sub_56876F0 | R a1+0x10 | `0x5687732  mov r14,[rdx+0x10]` | element cursor = [a1+0x10] | [V] |
| 0x5687736 | 8 | sub_56876F0 | R a1+0x18 | `0x5687736  mov rax,[rdx+0x18]` | element end = [a1+0x18] | [V] |
| 0x568773A | 8 | sub_56876F0 | W [rbp+0x8E0] | `0x568773A  mov [rbp+0x8E0],rax` | loop end saved | [V] |
| 0x5687741 | 8 | sub_56876F0 | R a1+0x28 | `0x5687741  lea rax,[rdx+0x28]` | a1+0x28 | [V] |
| 0x5687745 | 8 | sub_56876F0 | W [rbp+0x8D0] | `0x5687745  mov [rbp+0x8D0],rax` | | [V] |
| 0x5687761 | 8 | sub_56876F0 | W [rbp+0x958] | `0x5687761  mov [rbp+0x958],rdx` | save a1 | [V] |
| 0x5687768 | 8 | sub_56876F0 | R a1+0x60 | `0x5687768  lea rax,[rdx+0x60]` | a1+0x60 | [V] |
| 0x568776C | 8 | sub_56876F0 | W [rbp+0x8D8] | `0x568776C  mov [rbp+0x8D8],rax` | | [V] |
| 0x568777A | 4 | sub_56876F0 | W [rbp+0x964] | `0x568777A  mov [rbp+0x964],r8d` | pass flavor flag | [V] |
| 0x5687792 | - | sub_56876F0 | - | `0x5687792  add r14,0x290` | next element (0x290 stride) | [V] |
| 0x56877A7 | - | sub_56876F0 | - | `0x56877A7  cmp r14,[rbp+0x8E0]` | element cursor vs end | [V] |
| 0x56877AE | - | sub_56876F0 | - | `0x56877AE  je 0x5688B87` | outer loop exit | [V] |
| 0x56877B4 | 8 | sub_56876F0 | R elem base | `0x56877B4  lea rsi,[r14+0x240]` | element data base = cursor+0x240 | [V] |
| 0x56877D6 | 8 | sub_56876F0 | - | `0x56877D6  lea rax,[0xF25B730]` | vtable data_f25b730 | [I] |
| 0x56877DD | 8 | sub_56876F0 | W block+0x0 | `0x56877DD  mov [rbp+0x560],rax` | block header+0 = vtable | [V] |
| 0x56877E4 | 8 | sub_56876F0 | W block+0x8 | `0x56877E4  mov [rbp+0x568],rsi` | block header+8 = element data base | [V] |
| 0x56877EB | 8 | sub_56876F0 | W [rbp+0x598] | `0x56877EB  mov [rbp+0x598],rcx` | block pointer | [V] |
| 0x568795D | - | sub_56876F0 | - | `0x568795D  call 0x5692730` | flavor 0: per-element callee | [V] |
| 0x5687990 | - | sub_56876F0 | - | `0x5687990  call 0x5692C00` | flavor 1: per-element callee | [V] |
| 0x56879CA | - | sub_56876F0 | - | `0x56879CA  call 0x56930E0` | flavor>=2: per-element callee | [V] |
| 0x5687A96 | 8 | sub_56876F0 | R [elem+0x258] | `0x5687A96  mov rax,[r14+0x258]` | element field | [V] |
| 0x5687A9D | 8 | sub_56876F0 | W record+0x0 | `0x5687A9D  mov [rbp+0x5A0],rax` | record+0x0 = element field | [V] |

| 0x5687ABF | 4 | sub_56876F0 | W [rax+8] | `0x5687ABF  lock inc dword ptr [rax+8]` | inc object refcount | [V] |
| 0x5687AD2 | 8 | sub_56876F0 | R [elem+0x260] | `0x5687AD2  mov rcx,[r14+0x260]` | element field | [V] |
| 0x5687AD9 | 8 | sub_56876F0 | W record+0x8 | `0x5687AD9  mov [rbp+0x5A8],rcx` | record+0x8 | [V] |
| 0x5687AE0 | 8 | sub_56876F0 | W record+0x10 | `0x5687AE0  mov [rbp+0x5B0],rax` | record+0x10 | [V] |
| 0x5687AE7 | 16 | sub_56876F0 | W rbp+0x5B8 | `0x5687AE7  movups [r15-0x200],xmm6` | zero record+0x5B8 (16B) | [V] |
| 0x5687AEF | 8 | sub_56876F0 | W rbp+0x5C8 | `0x5687AEF  mov qword ptr [r15-0x1F0],0` | record+0x5C8 = 0 | [V] |
| 0x5687AFA | 1 | sub_56876F0 | W rbp+0x5D0 | `0x5687AFA  mov byte ptr [rbp+0x5D0],1` | flag byte | [V] |
| 0x5687B01 | 1 | sub_56876F0 | W rbp+0x600 | `0x5687B01  mov byte ptr [rbp+0x600],0` | flag byte | [V] |
| 0x5687B08 | 16 | sub_56876F0 | W record+0xD8 | `0x5687B08  movups [rbp+0x5D8],xmm7` | record+0xD8 = callee output entry {a1,[a1+0]} | [V] |
| 0x5687B0F | 16 | sub_56876F0 | W rbp+0x5E8 | `0x5687B0F  movups [r15-0x1D0],xmm6` | zero record+0x5E8 (16B) | [V] |
| 0x5687B17 | 8 | sub_56876F0 | W rbp+0x5F8 | `0x5687B17  mov qword ptr [r15-0x1C0],0` | record+0x5F8 = 0 | [V] |
| 0x5687BB3 | 8 | sub_56876F0 | W record copy start | `0x5687BB3  mov [rbp+0x5E8],rsi` | record+0x5E8 = callee-output copy dest start | [V] |
| 0x5687BBA | 8 | sub_56876F0 | W record copy start | `0x5687BBA  mov [rbp+0x5F0],rsi` | record+0x5F0 = copy cursor | [V] |
| 0x5687BCC | 8 | sub_56876F0 | W record copy end | `0x5687BCC  mov [rbp+0x5F8],rdi` | record+0x5F8 = callee-output copy dest end | [V] |
| 0x5687BE0 | - | sub_56876F0 | - | `0x5687BE0  call 0xEEC6DE0` | copy callee output array -> record dest | [V] |
| 0x5687BE5 | 8 | sub_56876F0 | W record copy end | `0x5687BE5  mov [rbp+0x5F0],rdi` | record+0x5F0 = copy end | [V] |
| 0x5687C0F | 8 | sub_56876F0 | W record+0x608 | `0x5687C0F  mov [rbp+0x608],rax` | record+0x608 = entry count | [V] |
| 0x5687C16 | 16 | sub_56876F0 | R [elem+0x118] | `0x5687C16  movups xmm0,[r14+0x118]` | element data +0x118 | [V] |
| 0x5687C1E | 16 | sub_56876F0 | W record+0x618 | `0x5687C1E  movups [rbp+0x618],xmm0` | record+0x618 = element data +0x118 | [V] |
| 0x5687C25 | 16 | sub_56876F0 | R [elem+0x128] | `0x5687C25  movups xmm0,[r14+0x128]` | | [V] |
| 0x5687C2D | 16 | sub_56876F0 | W record+0x628 | `0x5687C2D  movups [rbp+0x628],xmm0` | | [V] |
| 0x5687C34 | 16 | sub_56876F0 | R [elem+0x138] | `0x5687C34  movups xmm0,[r14+0x138]` | | [V] |
| 0x5687C3C | 16 | sub_56876F0 | W record+0x638 | `0x5687C3C  movups [rbp+0x638],xmm0` | | [V] |
| 0x5687C43 | 16 | sub_56876F0 | R [elem+0x148] | `0x5687C43  movups xmm0,[r14+0x148]` | | [V] |
| 0x5687C4B | 16 | sub_56876F0 | W record+0x648 | `0x5687C4B  movups [rbp+0x648],xmm0` | | [V] |
| 0x5687C52 | 16 | sub_56876F0 | R [elem+0x158] | `0x5687C52  movups xmm0,[r14+0x158]` | | [V] |
| 0x5687C5A | 16 | sub_56876F0 | W record+0x658 | `0x5687C5A  movups [rbp+0x658],xmm0` | | [V] |
| 0x5687C61 | 16 | sub_56876F0 | R [elem+0x168] | `0x5687C61  movups xmm0,[r14+0x168]` | | [V] |
| 0x5687C69 | 16 | sub_56876F0 | W record+0x668 | `0x5687C69  movups [rbp+0x668],xmm0` | | [V] |
| 0x5687C70 | 16 | sub_56876F0 | R [elem+0x178] | `0x5687C70  movups xmm0,[r14+0x178]` | | [V] |
| 0x5687C78 | 16 | sub_56876F0 | W record+0x678 | `0x5687C78  movups [rbp+0x678],xmm0` | | [V] |
| 0x5687C7F | 16 | sub_56876F0 | R [elem+0x188] | `0x5687C7F  movups xmm0,[r14+0x188]` | | [V] |
| 0x5687C87 | 16 | sub_56876F0 | W record+0x688 | `0x5687C87  movups [rbp+0x688],xmm0` | | [V] |
| 0x5687C9F | 16 | sub_56876F0 | R [elem+0x198] | `0x5687C9F  movups xmm0,[rcx]` | element +0x198 | [V] |
| 0x5687CA2 | 16 | sub_56876F0 | W rbp+0x698 | `0x5687CA2  movups [r15-0x120],xmm0` | record+0x698 = element +0x198 | [V] |
| 0x5687CAA | 16 | sub_56876F0 | R [elem+0x1AC] | `0x5687CAA  movups xmm0,[r14+0x1AC]` | | [V] |
| 0x5687CB2 | 16 | sub_56876F0 | W record+0x6AC | `0x5687CB2  movups [rbp+0x6AC],xmm0` | element +0x1AC -> record+0x6AC | [V] |
| 0x5687CB9 | 16 | sub_56876F0 | R [elem+0x1BC] | `0x5687CB9  movups xmm0,[r14+0x1BC]` | | [V] |
| 0x5687CC1 | 16 | sub_56876F0 | W record+0x6BC | `0x5687CC1  movups [rbp+0x6BC],xmm0` | element +0x1BC -> record+0x6BC | [V] |
| 0x5687CC8 | 16 | sub_56876F0 | R [elem+0x1CC] | `0x5687CC8  movups xmm0,[r14+0x1CC]` | | [V] |
| 0x5687CD0 | 16 | sub_56876F0 | W record+0x6CC | `0x5687CD0  movups [rbp+0x6CC],xmm0` | element +0x1CC -> record+0x6CC | [V] |
| 0x5687CD7 | 16 | sub_56876F0 | R [elem+0x1DC] | `0x5687CD7  movups xmm0,[r14+0x1DC]` | | [V] |
| 0x5687CDF | 16 | sub_56876F0 | W record+0x6DC | `0x5687CDF  movups [rbp+0x6DC],xmm0` | element +0x1DC -> record+0x6DC | [V] |
| 0x5687CE6 | 16 | sub_56876F0 | R [elem+0x1EC] | `0x5687CE6  movups xmm0,[r14+0x1EC]` | | [V] |
| 0x5687CEE | 16 | sub_56876F0 | W record+0x6EC | `0x5687CEE  movups [rbp+0x6EC],xmm0` | element +0x1EC -> record+0x6EC | [V] |
| 0x5687CF5 | 16 | sub_56876F0 | R [elem+0x1FC] | `0x5687CF5  movups xmm0,[r14+0x1FC]` | | [V] |
| 0x5687CFD | 16 | sub_56876F0 | W record+0x6FC | `0x5687CFD  movups [rbp+0x6FC],xmm0` | element +0x1FC -> record+0x6FC | [V] |
| 0x5687D04 | 16 | sub_56876F0 | R [elem+0x20C] | `0x5687D04  movups xmm0,[r14+0x20C]` | | [V] |
| 0x5687D0C | 16 | sub_56876F0 | W record+0x70C | `0x5687D0C  movups [rbp+0x70C],xmm0` | element +0x20C -> record+0x70C | [V] |
| 0x5687D13 | 16 | sub_56876F0 | R [elem+0x21C] | `0x5687D13  movups xmm0,[r14+0x21C]` | | [V] |
| 0x5687D1B | 16 | sub_56876F0 | W record+0x71C | `0x5687D1B  movups [rbp+0x71C],xmm0` | element +0x21C -> record+0x71C (last field copy) | [V] |
| 0x5687D29 | 16 | sub_56876F0 | R [elem+0x22C] | `0x5687D29  movups xmm0,[rax]` | element +0x22C | [V] |
| 0x5687D2C | 16 | sub_56876F0 | W rbp+0x72C | `0x5687D2C  movups [r15-0x8C],xmm0` | record+0x72C = element +0x22C | [V] |
| 0x5687C95 | 4 | sub_56876F0 | R [elem+0x1A8] | `0x5687C95  mov eax,[rcx+0x10]` | element +0x1A8 | [V] |
| 0x5687C98 | 4 | sub_56876F0 | W rbp+0x6A8 | `0x5687C98  mov [r15-0x110],eax` | record+0x6A8 = element +0x1A8 | [V] |
| 0x5687D4F | 8 | sub_56876F0 | R [a1+0x28] | `0x5687D4F  mov rax,[rbp+0x8D0]` | [a1+0x28] | [V] |
| 0x5687D56 | 16 | sub_56876F0 | R [a1+0x28] | `0x5687D56  movups xmm0,[rax]` | [a1+0x28] float4 | [V] |
| 0x5687D59 | 16 | sub_56876F0 | R [a1+0x28+0x10] | `0x5687D59  movups xmm1,[rax+0x10]` | [a1+0x28+0x10] float4 | [V] |
| 0x5687D5D | 16 | sub_56876F0 | W rbp+0x74C | `0x5687D5D  movups [r15-0x6C],xmm1` | record+0x74C = [a1+0x28] float4 | [V] |
| 0x5687D62 | 16 | sub_56876F0 | W rbp+0x73C | `0x5687D62  movups [r15-0x7C],xmm0` | record+0x73C = [a1+0x28] float4 | [V] |
| 0x5687D82 | 1 | sub_56876F0 | R [a1+0x48] | `0x5687D82  movzx eax,byte ptr [rcx+0x48]` | [a1+0x48] byte | [V] |
| 0x5687D86 | 1 | sub_56876F0 | W rbp+0x75C | `0x5687D86  mov [rbp+0x75C],al` | record+0x75C | [V] |
| 0x5687D8C | 16 | sub_56876F0 | R [a1+0x4C] | `0x5687D8C  movups xmm0,[rcx+0x4C]` | [a1+0x4C] float4 | [V] |
| 0x5687D90 | 16 | sub_56876F0 | W rbp+0x760 | `0x5687D90  movaps [rbp+0x760],xmm0` | record+0x760 | [V] |
| 0x5687DA5 | 16 | sub_56876F0 | R [a1+0x60] | `0x5687DA5  movups xmm0,[rax]` | [a1+0x60] block | [V] |
| 0x5687DB4 | 16 | sub_56876F0 | W rbp+0x782 | `0x5687DB4  movups [r15-0x16],xmm3` | ([a1+0x60] block field copy) | [V] |
| 0x5687DCF | 8 | sub_56876F0 | R [rbp+0x608] | `0x5687DCF  mov rax,[rbp+0x608]` | entry count | [V] |
| 0x5687DD6 | 8 | sub_56876F0 | - | `0x5687DD6  add rax,r13` | count + per-entry count | [V] |
| 0x5687DD9 | 8 | sub_56876F0 | W record+0x610 | `0x5687DD9  mov [rbp+0x610],rax` | record+0x610 | [V] |
| 0x5687DE0 | 16 | sub_56876F0 | W rbp+0x7C8 | `0x5687DE0  movups [r15+0x10],xmm6` | zero record+0x7C8 (16B) | [V] |
| 0x5687DE5 | 16 | sub_56876F0 | W rbp+0x7B8 | `0x5687DE5  movups [r15],xmm6` | zero record start (16B) | [V] |
| 0x5687DE9 | 8 | sub_56876F0 | W rbp+0x7D8 | `0x5687DE9  mov qword ptr [rbp+0x7D8],0xF` | small-string size = 0xF | [V] |
| 0x5687DF4 | 8 | sub_56876F0 | W rbp+0x7E0 | `0x5687DF4  mov qword ptr [rbp+0x7E0],0` | small-string cap = 0 | [V] |
| 0x5688708 | 8 | sub_56876F0 | R caller dest | `0x5688708  mov rcx,[rbp+0x8B8]` | caller dest pointer (saved arg rcx) | [V] |
| 0x568870F | 8 | sub_56876F0 | R [rbp-0x50] | `0x568870F  lea rdx,[rbp-0x50]` | callee out-object {a1,[a1+0],base,end,end} | [V] |
| 0x5688713 | 4 | sub_56876F0 | - | `0x5688713  xor r8d,r8d` | | [V] |
| 0x5688716 | - | sub_56876F0 | - | `0x5688716 call 0x568B0D0` | DEST WRITE: sub_568b0d0(caller_dest, &callee_out_object, 0) | [V] |
| 0x5687A5D | - | sub_56876F0 | - | `0x5687A5D call 0x655CEA0` | DEST WRITE: sub_655CEA0(node_buffer_entry, record) per callee-output entry | [V] |
| 0x5688834 | - | sub_56876F0 | - | `0x5688834 call 0x655CEA0` | DEST WRITE: sub_655CEA0(&[rbp+0x2D0]) second side record | [V] |

## PART (b) RESULT

All 7 element-loop bodies decoded: each builds a per-element record (header block with its own vtable data_f25b4F0/550/5B0/610/670/6d0/730, callee output entry {a1,[a1+0]}, element fields [r14+0x258/0x260/0x268], element data [r14+0x118..0x22C] mapped to record+0x618..0x72C, [a1+0x28/0x48/0x4C/0x60]-derived fields, strings), copies the per-element callee output array into record+0x5E8..0x5F8, counts entries, then DEST WRITES per element: sub_568b0d0(caller dest saved from arg rcx at [rbp+0x8B8], &callee out-object at [rbp-0x50], 0) plus sub_655CEA0 side records (&[rbp-0x30]/&[rbp+0x2D0]/per-entry node-buffer entry with record). No per-element write targets a1/a2/a3 memory.

CLOSES?: YES — every pending part of item C5b is now proven by [V] rows:
- part (a) sub_5690960 / sub_5690e10 / sub_56912d0 instruction-complete (each entry..ret, all quoted lines verify_oc-clean)
- part (b) per-element fill and dest writes of all 7 bodies sub_5684660 / sub_567E510 / sub_567FD70 / sub_56815D0 / sub_5682E20 / sub_5685EA0 / sub_56876F0

## NEXT
DONE — C5b per-element fill/dest writes and sub_5690960/5690e10/56912d0 decode complete; all [V], verify_oc clean.





