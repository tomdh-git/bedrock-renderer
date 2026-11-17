## NEXT
DONE

## UNIT U-Sx6 — effect_shadow_extractor_66a9d50_66ab74e, chunk 6 of 6 (shadow extractor 0x66a9d50)
Slice: 0x66ab56b..0x66ab74d (102 instructions). Source listing: docs/progress/_part_Sx6.txt (orchestrator-computed).

Format: each phase covers at most 40 instructions as `RVA..RVA: <one or two sentences>` followed by the verbatim `0xRVA  instr` lines it covers (copied two-space-form from the source listing). Every listed instruction belongs to exactly one phase; nothing is skipped. The field table after the phases lists every [reg+off] load/store once per distinct field, with all sites of that field listed.

Tags: [V] = observed in the disassembly at the cited RVA (verified against the exe with rdis); '-' = the slice shows no meaning for the field (no instruction operand, immediate, or string reveals it).

== Piece 1 — instructions 0x66ab56b..0x66ab65c (source lines 1-52)

### Phase 1: 0x66ab56b..0x66ab597 — 11 instructions [V]
Combine packed shadow bits: load dword [rbx+0x240], bitwise-not it, add dword [rbx+0x248], store the resulting word (ax) at [rbp+0x168]. Then resolve the global pointer at [0x1233E1B0] through [rcx] and [rax+0x10] to an indirect call through [0xF99FFA0] with dl=0x4A, and store the resulting byte al at [rbp+0x437].
0x66ab56b  mov eax,[rbx+0x240]
0x66ab571  not eax
0x66ab573  add eax,[rbx+0x248]
0x66ab579  mov [rbp+0x168],ax
0x66ab580  mov rcx,[0x1233E1B0]
0x66ab587  mov rax,[rcx]
0x66ab58a  mov rax,[rax+0x10]
0x66ab58e  mov dl,0x4A
0x66ab590  call qword ptr [0xF99FFA0]
0x66ab596  nop
0x66ab597  mov [rbp+0x437],al

### Phase 2: 0x66ab59d..0x66ab5c4 — 9 instructions [V]
Branch on the rbx cursor: if [rbx+8] == [rbx+0x10], call 0x5ABA6D0 with rcx=rbx and r8=[rbp+0xD0]; otherwise copy 0xC8 bytes from [rbx+8] to the stack buffer at [rbp+0xD0] via call 0xEEC6EC0, and advance the cursor with a qword store [rbx+8] += 0xC8.
0x66ab59d  mov rdx,[rbx+8]
0x66ab5a1  cmp rdx,[rbx+0x10]
0x66ab5a5  je short 0x66AB5C6
0x66ab5a7  mov r8d,0xC8
0x66ab5ad  mov rcx,rdx
0x66ab5b0  lea rdx,[rbp+0xD0]
0x66ab5b7  call 0xEEC6EC0
0x66ab5bc  add qword ptr [rbx+8],0xC8
0x66ab5c4  jmp short 0x66AB5D6

### Phase 3: 0x66ab5c6..0x66ab5d5 — 4 instructions [V]
Equal-branch target: rcx=rbx, r8=[rbp+0xD0], call 0x5ABA6D0 (shadow-buffer initializer), nop.
0x66ab5c6  mov rcx,rbx
0x66ab5c9  lea r8,[rbp+0xD0]
0x66ab5d0  call 0x5ABA6D0
0x66ab5d5  nop

### Phase 4: 0x66ab5d6..0x66ab60c — 11 instructions [V]
Re-resolve [0x1233E1B0]->[rcx]->[rax+0x10] and indirect-call via [0xF99FFA0] with dl = zero-extended byte [rbp+0x437]; call 0x66A9AD0 with rcx=[rbp+0x1B0]; test flag byte [rbp+0x380] == 1, set rsi=[rbp+0xD0], and branch to 0x66AA2DA when the flag is not 1.
0x66ab5d6  mov rcx,[0x1233E1B0]
0x66ab5dd  mov rax,[rcx]
0x66ab5e0  mov rax,[rax+0x10]
0x66ab5e4  movzx edx,byte ptr [rbp+0x437]
0x66ab5eb  call qword ptr [0xF99FFA0]
0x66ab5f1  nop
0x66ab5f2  lea rcx,[rbp+0x1B0]
0x66ab5f9  call 0x66A9AD0
0x66ab5fe  cmp byte ptr [rbp+0x380],1
0x66ab605  lea rsi,[rbp+0xD0]
0x66ab60c  jne 0x66AA2DA

### Phase 5: 0x66ab612..0x66ab64e — 13 instructions [V]
Require [rbp+0x340] non-null, compute available size [rbp+0x350]-[rbp+0x340] and reject below 0x1000, then validate the heap slot: load [rcx-8], rebase rcx by -8, subtract the slot size, require remainder >= 0x20, and jump to 0x66AB71A (exits via 0x66AA2D5/0x66AA2CE otherwise).
0x66ab612  mov rcx,[rbp+0x340]
0x66ab619  test rcx,rcx
0x66ab61c  je 0x66AA2DA
0x66ab622  mov rdx,[rbp+0x350]
0x66ab629  sub rdx,rcx
0x66ab62c  cmp rdx,0x1000
0x66ab633  jb 0x66AA2D5
0x66ab639  mov rax,[rcx-8]
0x66ab63d  add rcx,0xFFFFFFFFFFFFFFF8
0x66ab641  sub rcx,rax
0x66ab644  cmp rcx,0x20
0x66ab648  jb 0x66AA2CE
0x66ab64e  jmp 0x66AB71A

### Phase 6: 0x66ab653..0x66ab65c — 5 instructions [V]
Out-of-line case target: call 0x9BC830 with rcx=r13, then jump to 0x66AAD11.
0x66ab653  mov rcx,r13
0x66ab656  call 0x9BC830
0x66ab65b  nop
0x66ab65c  jmp 0x66AAD11
== Piece 2 — instructions 0x66ab661..0x66ab74d (source lines 53-102)

### Phase 7: 0x66ab661..0x66ab66a — 4 instructions [V]
Out-of-line case target: call 0x9BC830 with rcx=r13, then jump to 0x66AB24D.
0x66ab661  mov rcx,r13
0x66ab664  call 0x9BC830
0x66ab669  nop
0x66ab66a  jmp 0x66AB24D

### Phase 8: 0x66ab66f..0x66ab6d2 — 17 instructions [V]
Global-slot path for [0x129F8D08]: call 0xE938CB0; if dword [0x129F8D08] is not 0xFFFFFFFF jump to 0x66A9DF5. Otherwise zero xmm0 and store 16 bytes at [rbp+0x80], store [rbp+0x198]=0xF56F38F and [rbp+0x1A0]=0xE (qword stores), call 0x5668AC0 with rcx=&[0x129F8CF8], rdx=[rbp+0x198], r8=[rbp+0x80], then call 0xE938D70 and jump 0x66A9DF5.
0x66ab66f  lea rcx,[0x129F8D08]
0x66ab676  call 0xE938CB0
0x66ab67b  cmp dword ptr [0x129F8D08],0xFFFFFFFF
0x66ab682  jne 0x66A9DF5
0x66ab688  xorps xmm0,xmm0
0x66ab68b  movaps [rbp+0x80],xmm0
0x66ab692  lea rax,[0xF56F38F]
0x66ab699  mov [rbp+0x198],rax
0x66ab6a0  mov qword ptr [rbp+0x1A0],0xE
0x66ab6ab  lea rcx,[0x129F8CF8]
0x66ab6b2  lea rdx,[rbp+0x198]
0x66ab6b9  lea r8,[rbp+0x80]
0x66ab6c0  call 0x5668AC0
0x66ab6c5  nop
0x66ab6c6  lea rcx,[0x129F8D08]
0x66ab6cd  call 0xE938D70
0x66ab6d2  jmp 0x66A9DF5

### Phase 9: 0x66ab6d7..0x66ab715 — 12 instructions [V]
Global-slot path for [0x129CA5E0]: call 0xE938CB0; if [0x129CA5E0] != 0xFFFFFFFF jump 0x66A9E83. Otherwise call 0x567DB00 with rcx=[0x129CA568], call 0xE935740 with rcx=0x567DBA0, call 0xE938D70 with rcx=[0x129CA5E0], jump 0x66A9E83.
0x66ab6d7  lea rcx,[0x129CA5E0]
0x66ab6de  call 0xE938CB0
0x66ab6e3  cmp dword ptr [0x129CA5E0],0xFFFFFFFF
0x66ab6ea  jne 0x66A9E83
0x66ab6f0  lea rcx,[0x129CA568]
0x66ab6f7  call 0x567DB00
0x66ab6fc  nop
0x66ab6fd  lea rcx,[0x567DBA0]
0x66ab704  call 0xE935740
0x66ab709  lea rcx,[0x129CA5E0]
0x66ab710  call 0xE938D70
0x66ab715  jmp 0x66A9E83

### Phase 10: 0x66ab71a..0x66ab74d — 17 instructions [V]
Epilogue: store qword 0 at [rsp+0x20], zero ecx/edx/r8d/r9d, indirect call through [0xF9A8C78], then four calls (0x75B60 twice, 0x75740 twice, each followed by nop), int3, and the end-boundary pad nop [rax] at 0x66ab74d.
0x66ab71a  mov qword ptr [rsp+0x20],0
0x66ab723  xor ecx,ecx
0x66ab725  xor edx,edx
0x66ab727  xor r8d,r8d
0x66ab72a  xor r9d,r9d
0x66ab72d  call qword ptr [0xF9A8C78]
0x66ab733  nop
0x66ab734  call 0x75B60
0x66ab739  nop
0x66ab73a  call 0x75B60
0x66ab73f  nop
0x66ab740  call 0x75740
0x66ab745  nop
0x66ab746  call 0x75740
0x66ab74b  nop
0x66ab74c  int3
0x66ab74d  nop [rax]

## Field table — every [reg+off] field stored or loaded in the slice

Sizes come from the instruction (qword/movaps 8/16, dword 4, word 2, byte 1). Direction R = load, W = store, R/W = both. All sites for each distinct field are listed; the meaning column shows '-' because no instruction operand, immediate, or string in the slice documents what any of these fields means.

| offset | size | read/store address | verbatim line(s) | meaning |
| rbx+0x240 | 4B | R [rbx+0x240] | `0x66ab56b  mov eax,[rbx+0x240]` | - |
| rbx+0x248 | 4B | R [rbx+0x248] | `0x66ab573  add eax,[rbx+0x248]` | - |
| rbp+0x168 | 2B | W [rbp+0x168] | `0x66ab579  mov [rbp+0x168],ax` | - |
| rcx+0 | 8B | R [rcx] | `0x66ab587  mov rax,[rcx]` | - |
| rax+0x10 | 8B | R [rax+0x10] | `0x66ab58a  mov rax,[rax+0x10]` | - |
| rbx+8 | 8B | R/W [rbx+8] | `0x66ab59d  mov rdx,[rbx+8]` (R)<br>`0x66ab5bc  add qword ptr [rbx+8],0xC8` (W) | - |
| rbx+0x10 | 8B | R [rbx+0x10] | `0x66ab5a1  cmp rdx,[rbx+0x10]` | - |
| rbp+0x437 | 1B | W/R [rbp+0x437] | `0x66ab597  mov [rbp+0x437],al` (W)<br>`0x66ab5e4  movzx edx,byte ptr [rbp+0x437]` (R) | - |
| rbp+0x380 | 1B | R [rbp+0x380] | `0x66ab5fe  cmp byte ptr [rbp+0x380],1` | - |
| rbp+0x340 | 8B | R [rbp+0x340] | `0x66ab612  mov rcx,[rbp+0x340]` | - |
| rbp+0x350 | 8B | R [rbp+0x350] | `0x66ab622  mov rdx,[rbp+0x350]` | - |
| rcx-8 | 8B | R [rcx-8] | `0x66ab639  mov rax,[rcx-8]` | - |
| rbp+0x80 | 16B | W [rbp+0x80] | `0x66ab68b  movaps [rbp+0x80],xmm0` | - |
| rbp+0x198 | 8B | W [rbp+0x198] | `0x66ab699  mov [rbp+0x198],rax` | - |
| rbp+0x1A0 | 8B | W [rbp+0x1A0] | `0x66ab6a0  mov qword ptr [rbp+0x1A0],0xE` | - |
| rsp+0x20 | 8B | W [rsp+0x20] | `0x66ab71a  mov qword ptr [rsp+0x20],0` | - |

## TOOL REQUESTS
None — no helper scripts were written; verification uses existing tools/sigs/verify_oc.py against the exe via rdis.
