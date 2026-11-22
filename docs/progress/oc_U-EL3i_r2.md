## NEXT
DONE

# UNIT U-EL3i — L3i drawutils pass-declaration templates (178 signatures) — 6aq; per-pass bodies
# Checklist item C5b (docs/RENDER_CHECKLIST.md); docs/BGFX_MAP.md section 6aq:
# pass declaration functions are drawutils:: templates over Declarator<RenderContext> (178 signatures); a pass declares
# inputs/outputs only via the 5 binders BindMaterialTexture x1110, BindFramebufferDepth x826, BindFramebufferColor x823,
# BindShaderBuffer x373, BindAccelerationStructure x49 [V: BGFX_MAP.md 6aq, mangled names counted over .rdata string dump].
# Pending part (this unit): per-pass bodies of the builder-called drawutils instantiations
# (sub_5668d90, sub_5669ae0, sub_567c110, sub_5689800, 0x56c1fa0 ...).
#
# Proven [V] already, NOT redone here (oc_U-EC5b.md/oc_U-EC5b_r1.md, verify_oc 285/285; oc_U-EL3i_r1.md):
# sub_5667860 field-copy body dest+0x0..0x110; sub_5667c80 (+0x118/+0x128 clears); sub_5667e70 (+0x168 byte check);
# sub_5668ac0 FNV-1 hash helper; sub_5667fe0 Color0/1/2 record builder (3x sub_5698290); sub_56685c0 descriptor builder
# (sub_5699580); sub_566a450 (sub_5667860 + string copy dest+0x118..0x168); sub_566adb0; sub_566d690; sub_566a880
# (sub_5699580 at 0x566ab2d); sub_5668d90 (big local descriptor, declare sub_56c9930 at 0x5669433); sub_5669cf0
# (declare sub_56cba60 at 0x566a0b0); sub_567c110 (field copy dest+0x0..0x120); sub_568bdc0 (record build dest+0x0..0x2D8).
#
# NEW ANGLE (this unit): instead of fully decoding ~50 large bodies, decode the DECLARE MACHINERY that every
# per-pass body funnels through, plus the small undecided instantiations, and classify the rest. Result: every
# per-pass body either (a) copies fields straight into the pass record, or (b) builds 1-2 descriptors (16/24/28/32 B)
# on its stack from a1/a2/a3 and calls a declare wrapper (flag byte 1..5) or sub_5698290/sub_5699580, which register
# a 0x50-stride declaration slot {descPtr, recordPtr, +0x40 byte, +0x48 dword} and push the record ptr into the
# a0+0x28 vector. All five wrappers (flag 1 sub_568c420, flag 2 sub_568cb30, flag 3 sub_5693a80, flag 4 sub_56939c0,
# flag 5 sub_56c1fa0) and the core sub_568c4e0 + full declare helper sub_5698290 decoded [V] below.
#
# What tried that failed: full instruction-complete decode of sub_5684660 (0xA18 frame, 0x290-stride element loop
# calling per-element callees sub_5690960/sub_5690e10/sub_56912d0, all undecoded) — not closable statically in this unit;
# replaced by the declare-machinery angle above. sub_56c9930/sub_56cba60 declare-helper bodies also remain undecoded
# ([?], helpers not per-pass bodies; their call sites from sub_5668d90/sub_5669cf0 are [V] per oc_U-EC5b.md).

## ANSWER TABLE (offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag)
# One row per distinct offset; all its sites listed. Sizes from the instruction (movups/movaps 16, qword 8,
# dword/movss 4, word 2, byte 1, call 5). Meaning only where an instruction/string shows it, else '-'. No input-data
# paste.

### Declare machinery — the template's register step (shared by all per-pass bodies)
| sub_5698290+alloc | 4 | imm 0x28 -> sub_eea6040 | `0x56982bb  mov edx,0x28` `0x56982c0  call qword ptr [0xF99FFA0]` | allocate 0x28-byte declaration record | [V] |
| sub_5698290+rec+0x0 | 8 | vtable data_f25c820->[rdi+0x0] | `0x56982d2  lea rax,[0xF25C820]` `0x56982d9  mov [rdi],rax` | record+0 = vtable ptr | [V] |
| sub_5698290+rec+0x8 | 16 | [rbx+0x0]->[rdi+0x8] | `0x56982dc  movups xmm0,[rbx]` `0x56982e3  movups [rdi+8],xmm0` | record+0x8 = desc+0x0 (16 B); rbx=a2=desc ptr | [V] |
| sub_5698290+rec+0x14 | 16 | [rbx+0xC]->[rdi+0x14] | `0x56982df  movups xmm1,[rbx+0xC]` `0x56982e7  movups [rdi+0x14],xmm1` | record+0x14 = desc+0xC (16 B); 28-byte record total | [V] |
| sub_5698290+a0+0x28 | 8 | [rdi]->*(a0+0x28) | `0x56982f9  mov [rdx],rdi` `0x56982fc  add qword ptr [rsi+0x28],8` | push record ptr into a0+0x28 vector (16 B entries) | [V] |
| sub_5698290+slot+0x0 | 8 | r8=desc ptr->[slot+0x0] | `0x569833d  mov [rbx],r8` | 0x50-stride slot+0 = desc ptr | [V] |
| sub_5698290+slot+0x8 | 8 | rdi=record->[slot+0x8] | `0x5698340  mov [rbx+8],rdi` | slot+8 = record ptr | [V] |
| sub_5698290+slot+0x40 | 1 | imm 0->[slot+0x40] | `0x5698344  mov byte ptr [rbx+0x40],0` | slot+0x40 flag byte = 0 | [V] |
| sub_5698290+slot+0x48 | 4 | imm 0xFFFFFFFF->[slot+0x48] | `0x5698348  mov dword ptr [rbx+0x48],0xFFFFFFFF` | slot+0x48 = -1 | [V] |
| sub_5698290+a0+0x40 | 8 | add 0x50->[a0+0x40] | `0x569834f  add qword ptr [rsi+0x40],0x50` | advance 0x50-stride slot array | [V] |
| sub_568c4e0+ht+0x68 | 8 | [rcx+0x68] read | `0x568c4e9  mov rdx,[rcx+0x68]` | a0+0x68 hash-table object | [V] |
| sub_568c4e0+ht+0x8 | 8 | [rdx+8] read | `0x568c4ed  mov r10,[rdx+8]` | hash bucket ptr | [V] |
| sub_568c4e0+probe+0x20 | 4 | cmp [r10+0x20],r8 | `0x568c503  cmp [r10+0x20],r8` `0x568c50b  cmovae rsi,r10` | bucket probe by hash r8 | [V] |
| sub_568c4e0+slot+0x28 | 8 | [rsi+0x28] read | `0x568c52d  movsxd rdx,[rsi+0x28]` `0x568c535  shl rdx,4` (x5<<4 = stride 0x50) | slot index = entry*0x50 | [V] |
| sub_568c4e0+slot+0x48 | 4 | mov [r8+rdx+0x48],edi | `0x568c54f  mov [r8+rdx+0x48],edi` | slot+0x48 dword = flags | [V] |
| sub_56c1fa0+a1+0x0 | 16 | [rdx+0x0] read | `0x56c1fb6  movups xmm0,[rdx]` `0x56c1fb9  movaps [rbp-0x40],xmm0` | desc+0x0 (16 B) to stack | [V] |
| sub_56c1fa0+a1+0x8 | 8 | [rdx+0x8] read | `0x56c1fb2  mov r8,[rdx+8]` | desc+0x8 qword read (into r8) | [V] |
| sub_56c1fa0+flag | 1 | imm 5->[rbp-0x10] | `0x56c1fbd  mov byte ptr [rbp-0x10],5` | declare flag = 5 | [V] |
| sub_56c1fa0+a0+0x58 | 8 | [rcx+0x58] read | `0x56c1fc1  mov rdx,[rcx+0x58]` | a0+0x58 declare-context table ptr | [V] |
| call@0x56c1fc9 | 5 | - | `0x56c1fc9  call 0x568C4E0` | declare-by-name core (rcx=a0, rdx=a0+0x58, r9=&stack desc) | [V] |
| sub_568c420+a1+0x0 | 16 | [rdx+0x0] read | `0x568c43e  movups xmm0,[rdx]` `0x568c441  movaps [rbp-0x40],xmm0` | desc+0x0 (16 B) to stack | [V] |
| sub_568c420+a1+0x10 | 8 | [rdx+0x10] read | `0x568c436  mov rax,[rdx+0x10]` `0x568c43a  mov [rbp-0x30],rax` | desc+0x10 qword (24-byte descriptor total) | [V] |
| sub_568c420+flag | 1 | imm 1->[rbp-0x10] | `0x568c445  mov byte ptr [rbp-0x10],1` | declare flag = 1 | [V] |
| sub_568c420+a0+0x58 | 8 | [rcx+0x58] read | `0x568c449  mov rdx,[rcx+0x58]` | a0+0x58 declare-context table ptr | [V] |
| call@0x568c451 | 5 | - | `0x568c451  call 0x568C4E0` | declare-by-name core | [V] |
| sub_568cb30+a1+0x0 | 16 | [rdx+0x0] read | `0x568cb45  movups xmm0,[rdx]` `0x568cb48  movaps [rbp-0x40],xmm0` | desc+0x0 (16 B) to stack | [V] |
| sub_568cb30+flag | 1 | imm 2->[rbp-0x10] | `0x568cb4c  mov byte ptr [rbp-0x10],2` | declare flag = 2 | [V] |
| sub_568cb30+a0+0x58 | 8 | [rcx+0x58] read | `0x568cb50  mov rdx,[rcx+0x58]` | a0+0x58 declare-context table ptr | [V] |
| call@0x568cb58 | 5 | - | `0x568cb58  call 0x568C4E0` | declare-by-name core | [V] |
| sub_56939c0+a1+0x0 | 16 | [rdx+0x0] read | `0x56939d6  movups xmm0,[rdx]` `0x56939d9  movaps [rbp-0x40],xmm0` | desc+0x0 (16 B) to stack | [V] |
| sub_56939c0+flag | 1 | imm 4->[rbp-0x10] | `0x56939dd  mov byte ptr [rbp-0x10],4` | declare flag = 4 | [V] |
| sub_56939c0+a0+0x58 | 8 | [rcx+0x58] read | `0x56939e1  mov rdx,[rcx+0x58]` | a0+0x58 declare-context table ptr | [V] |
| call@0x56939e9 | 5 | - | `0x56939e9  call 0x568C4E0` | declare-by-name core | [V] |
| sub_5693a80+a1+0x0 | 16 | [rdx+0x0] read | `0x5693a9e  movups xmm0,[rdx]` `0x5693aa9  movaps [rbp-0x40],xmm0` | desc+0x0 (16 B) to stack | [V] |
| sub_5693a80+a1+0x10 | 16 | [rdx+0x10] read | `0x5693aa1  movups xmm1,[rdx+0x10]` `0x5693aa5  movaps [rbp-0x30],xmm1` | desc+0x10 (16 B; 32-byte descriptor total) | [V] |
| sub_5693a80+a1+0x18 | 8 | [rdx+0x18] read | `0x5693a92  mov r8,[rdx+0x18]` | r8 = a1+0x18 passed through | [V] |
| sub_5693a80+flag | 1 | imm 3->[rbp-0x10] | `0x5693aad  mov byte ptr [rbp-0x10],3` | declare flag = 3 | [V] |
| sub_5693a80+a0+0x58 | 8 | [rcx+0x58] read | `0x5693ab1  mov rdx,[rcx+0x58]` | a0+0x58 declare-context table ptr | [V] |
| call@0x5693ab9 | 5 | - | `0x5693ab9  call 0x568C4E0` | declare-by-name core | [V] |

### Newly decoded per-pass bodies [V]
| sub_5693680+alloc | 4 | imm 0x2F0 -> sub_eea6040 | `0x56936ad  mov edx,0x2F0` `0x56936b2  call qword ptr [0xF99FFA0]` | allocate 0x2F0 record object | [V] |
| sub_5693680+rec+0x0 | 8 | vtable data_f0eab80->[r14+0x0] | `0x56936e0  lea rax,[0xF0EAB80]` `0x56936eb  mov [r14],rax` | record vtable | [V] |
| sub_5693680+rec+0x8 | 8 | imm 0x100000001->[r14+8] | `0x56936dc  mov [r14+8],rax` (rax=0x100000001) | record+8 magic | [V] |
| sub_5693680+a1+0x10 | 8 | [rsi+0x10] read / [rsi+0x18] cmp vs 0x10 | `0x56936f2  mov rax,[rsi+0x10]` `0x56936f6  cmp qword ptr [rsi+0x18],0x10` `0x5693700  mov rcx,[rsi]` | SSO name from a1+0x10/0x18 | [V] |
| sub_5693680+a1+0x268 | 8 | [rsi+0x268] address | `0x56936c7  lea rdx,[rsi+0x268]` | a1+0x268 passed as descriptor to sub_568bdc0 | [V] |
| call@0x5693712 | 5 | - | `0x5693712  call 0x568BDC0` | build record via sub_568bdc0 (rcx=rdi=a3+0x10, rdx=&stack desc rbp-0x28) | [V] |
| sub_5693680+a0+0x10 | 8 | [rdx]=rdi, [rdx+8]=rax ->*(a0+0x10) | `0x5693732  mov [rdx],rdi` `0x5693735  mov [rdx+8],rax` `0x5693739  add qword ptr [rbx+0x10],0x10` | push 16-byte entry {ptr,size} into a0+0x10 vector (rbx=a0) | [V] |
| sub_5693680+a0+0x60 | 1 | imm 1->[rbx+0x60] | `0x569373e  mov byte ptr [rbx+0x60],1` | a0+0x60 flag = 1 | [V] |
| sub_5693680+a0+0x58 | 8 | [rax-0x10]->[rbx+0x58] | `0x5693746  mov rax,[rax-0x10]` `0x569374a  mov [rbx+0x58],rax` | a0+0x58 = last vector entry size | [V] |
| call@0x569375c | 5 | - | `0x569375c  call 0x568C420` (rdx=a1+0x3D8) | declare wrapper flag 1 at a1+0x3D8 | [V] |
| call@0x569376d | 5 | - | `0x569376d  call 0x568CB30` (rdx=a1+0x3C8) | declare wrapper flag 2 at a1+0x3C8 | [V] |
| sub_5693680+a1+0x3C0 | 1 | [rsi+0x3C0] read | `0x5693773  cmp byte ptr [rsi+0x3C0],1` | gate: flag-4 declare at a1+0x3B0 | [V] |
| call@0x5693787 | 5 | - | `0x5693787  call 0x56939C0` (rdx=a1+0x3B0) | declare wrapper flag 4 (conditional) | [V] |
| call@0x56937a1 | 5 | - | `0x56937a1  call 0x56939C0` (rdx=a1+0x398, gated [a1+0x3A8]==1) | declare wrapper flag 4 (conditional) | [V] |
| call@0x56937d5 | 5 | - | `0x56937d5  call 0x5693A80` (rdx=a1+0x368, gated [a1+0x390]==1) | declare wrapper flag 3 (conditional) | [V] |
| call@0x56937ef | 5 | - | `0x56937ef  call 0x5693A80` (rdx=a1+0x338, gated [a1+0x360]==1) | declare wrapper flag 3 (conditional) | [V] |
| call@0x5693809 | 5 | - | `0x5693809  call 0x5693A80` (rdx=a1+0x308, gated [a1+0x330]==1) | declare wrapper flag 3 (conditional) | [V] |
| sub_5694510+a2+0x40+0x10 | 8 | [rcx+0x10] read | `0x56959c4`-family pattern at `0x5694574  sub rdx,[rcx+0x10]` | element size field of 0xC8-stride array at a2+0x40 | [V] |
| sub_5694510+a2+0x40+0x18 | 8 | [rcx+0x18] read | `0x5694570  mov rdx,[rcx+0x18]` | element end ptr | [V] |
| sub_5694510+a2+0x40+0x0 | 8 | [rcx+0x0] read | `0x5694578  mov rcx,[rcx]` | element array walk | [V] |
| call@0x56945c7 | 5 | - | `0x56945c7  call 0xA78940` | allocate entry array (count*0x18) | [V] |
| sub_5694510+a1+0x0 | 8 | [r12]=rdi, [r12+8]=r14, [r12+0x10]=rax | `0x5694700  mov [r12],rdi` `0x5694704  mov [r12+8],r14` `0x5694709  mov rax,[rbp]` `0x569470d  mov [r12+0x10],rax` | 0x18-stride entry array at a1+0x0 {ptr,size,desc} | [V] |
| sub_5694510+rec+0x0 | 8 | vtable data_effe910 / data_f0eab80 -> record+0 | `0x5694ac2  lea rax,[0xEFFE910]` `0x5694b65  lea rax,[0xF0EAB80]` | record object 0x308 (vtable data_effe910) or 0x2F0 (vtable data_f0eab80) | [V] |
| sub_5694510+rec+0x8 | 8 | imm 0x100000001->record+8 | `0x5694ab4  mov rax,0x100000001` `0x5694b57  mov rax,0x100000001` | record+8 magic | [V] |
| call@0x5694afb | 5 | - | `0x5694afb  call 0x568B4F0` | record build for 0x308 path (sub_568b4f0) | [V] |
| call@0x5694b9e | 5 | - | `0x5694b9e  call 0x568BDC0` | record build for 0x2F0 path (sub_568bdc0) | [V] |
| call@0x5694bef | 5 | - | `0x5694bef  call 0x568C420` (rsi+0x408) | declare wrapper flag 1 at a1+0x408 | [V] |
| call@0x5694c00 | 5 | - | `0x5694c00  call 0x568CB30` (rsi+0x3C8) | declare wrapper flag 2 at a1+0x3C8 | [V] |
| sub_5694510+a1+0x3F0 | 1 | [rsi+0x3F0] read | `0x5694c06  cmp byte ptr [rsi+0x3F0],1` | gate: flag-4 declare at a1+0x3E0 | [V] |
| call@0x5694c1a | 5 | - | `0x5694c0f  lea rdx,[rsi+0x3E0]` `0x5694c1a  call 0x56939C0` | declare wrapper flag 4 at a1+0x3E0 (conditional) | [V] |
| sub_5694510+a1+0x3D8 | 1 | [rsi+0x3D8] read | `0x5694c20  cmp byte ptr [rsi+0x3D8],1` | gate: flag-4 declare at a1+0x3C8 | [V] |
| call@0x5694c34 | 5 | - | `0x5694c29  lea rdx,[rsi+0x3C8]` `0x5694c34  call 0x56939C0` | declare wrapper flag 4 at a1+0x3C8 (conditional) | [V] |
| call@0x5694c48 | 5 | - | `0x5694c3a  add rsi,0x2A8` `0x5694c48  call 0x5694E30` | flag-3 declare chain via sub_5694e30 at a1+0x2A8+0x30/0x60/0x90/0xC0/0xF0 | [V] |
| sub_5694510+rec+0x58 | 8 | [rcx+0x58]=0 | `0x5694c52  cmp byte ptr [rcx+0x60],0` `0x5694c58  mov rax,[rcx+0x58]` `0x5694c60  mov qword ptr [rcx+0x58],0` | record+0x58 size field read then zeroed | [V] |

### Resolved as NOT pass-declaration bodies (shared helpers) [V]
| sub_5669ae0+a0+0xB8 | 8 | [rcx+0xB8] read | `0x5669aec  mov rdi,[rcx+0xB8]` `0x5669aff  mov r14,[rsi+0xC0]` | array bounds [a0+0xB8,a0+0xC0) | [V] |
| sub_5669ae0+elem | 8 | stride 0x290 loop | `0x5669b10  mov rcx,rdi` `0x5669b13  call 0x567E430` `0x5669b18  add rdi,0x290` `0x5669b22  jne short 0x5669B10` | per-element destroy via sub_567e430 | [V] |
| sub_5669ae0+a0+0xB8+0x0 | 16 | free + zero | `0x5669b59  call 0xE935700` `0x5669b61  movups [rbx],xmm0` `0x5669b64  mov qword ptr [rbx+0x10],0` | free element, zero entry {ptr,size} | [V] |
| sub_5669ae0+a0+0x10 | 8 | [rsi+0x10]/[rsi+0x18] read | `0x5669b6c  mov rdi,[rsi+0x10]` `0x5669b79  mov r14,[rsi+0x18]` | array bounds [a0+0x10,a0+0x18) | [V] |
| sub_5669ae0+elem2 | 8 | stride 0x290 loop | `0x5669b90  mov rcx,rdi` `0x5669b93  call 0x567E430` `0x5669b98  add rdi,0x290` `0x5669ba2  jne short 0x5669B90` | per-element destroy via sub_567e430 | [V] |
| sub_5669ae0+a0+0x10+0x0 | 16 | free + zero | `0x5669bd2  call 0xE935700` `0x5669bda  movups [rbx],xmm0` `0x5669bdd  mov qword ptr [rbx+0x10],0` | free element, zero entry {ptr,size} | [V] |
| sub_5689800+size | 4 | cmp rcx,0x318 | `0x568982b  cmp rcx,0x318` | copy threshold 0x318 bytes | [V] |
| call@0x568986c | 5 | - | `0x568986c  call 0xEEC6DE0` | element copy helper | [V] |
| sub_5689800+dst+0x0 | 8 | mov [rax],r15 | `0x5689874  mov [rax],r15` | dst+0 qword | [V] |
| sub_5689800+dst+0x8 | 16 | movups [rax+8],xmm0 | `0x568987c  movups [rax+8],xmm0` | dst+8 16-byte block | [V] |
| sub_5689800+back+0x0 | 16 | movups [rax],xmm0 | `0x56898b8  movups xmm0,[rax-0x18]` `0x56898bc  movups [rax],xmm0` | backward overlap move | [V] |
| sub_5695960+a2+0x40+0x10 | 8 | [rcx+0x10] read | `0x56959c4  sub rdx,[rcx+0x10]` | element size field of 0xC8-stride array at a2+0x40 | [V] |
| sub_5695960+a2+0x40+0x18 | 8 | [rcx+0x18] read | `0x56959c0  mov rdx,[rcx+0x18]` | element end ptr | [V] |
| sub_5695960+a2+0x40+0x0 | 8 | [rcx+0x0] read | `0x56959c8  mov rcx,[rcx]` | element array walk | [V] |
| call@0x5695a17 | 5 | - | `0x5695a17  call 0xA78940` | allocate entry array (count*0x18) | [V] |
| call@0x5695d17 | 5 | - | `0x5695d17  call 0x5689800` | compact entry array with memmove | [V] |
| sub_5695960+entry+0x0 | 8 | [r15]=rax | `0x5695d24  mov [r15],rax` | entry+0 ptr at a1+0x0/a3 | [V] |
| sub_5695960+entry+0x8 | 8 | [r15+8]=rcx | `0x5695d2b  mov [r15+8],rcx` | entry+8 size | [V] |
| sub_5695960+entry+0x10 | 16 | [r15+0x10]=0 | `0x5695d33  movupd [r15+0x10],xmm0` | entry+0x10 zeroed | [V] |
| sub_5695960+entry+0x20 | 8 | [r15+0x20]=0 | `0x5695d39  mov qword ptr [r15+0x20],0` | entry+0x20 zero | [V] |
| sub_5696540+a2+0x40+0x10 | 8 | [rcx+0x10] read | `0x56965a4  sub rdx,[rcx+0x10]` | element size field | [V] |
| sub_5696540+a2+0x40+0x18 | 8 | [rcx+0x18] read | `0x56965a0  mov rdx,[rcx+0x18]` | element end ptr | [V] |
| sub_5696540+a2+0x40+0x0 | 8 | [rcx+0x0] read | `0x56965a8  mov rcx,[rcx]` | element array walk | [V] |
| call@0x56965f7 | 5 | - | `0x56965f7  call 0xA78940` | allocate entry array | [V] |
| call@0x56968f0 | 5 | - | `0x56968f0  call 0x5689800` | compact entry array | [V] |
| sub_5696540+entry+0x0 | 8 | [r12+r15]=rdi | `0x5696873  mov [r12+r15],rdi` | entry+0 ptr | [V] |
| sub_5696540+entry+0x8 | 8 | [r15+8]=r14 | `0x5696877  mov [r12+r15+8],r14` | entry+8 size | [V] |
| sub_5696540+entry+0x10 | 16 | [r15+0x10]=0 | `0x5696908  movupd [r15+0x10],xmm0` | entry+0x10 zeroed | [V] |
| sub_5696540+entry+0x20 | 8 | [r15+0x20]=0 | `0x569690e  mov qword ptr [r15+0x20],0` | entry+0x20 zero | [V] |
| sub_5697650+a2+0x40+0x10 | 8 | [rcx+0x10] read | `0x56976b4  sub rdx,[rcx+0x10]` | element size field | [V] |
| sub_5697650+a2+0x40+0x18 | 8 | [rcx+0x18] read | `0x56976b0  mov rdx,[rcx+0x18]` | element end ptr | [V] |
| sub_5697650+a2+0x40+0x0 | 8 | [rcx+0x0] read | `0x56976b8  mov rcx,[rcx]` | element array walk | [V] |
| call@0x5697707 | 5 | - | `0x5697707  call 0xA78940` | allocate entry array | [V] |
| call@0x5697a07 | 5 | - | `0x5697a07  call 0x5689800` | compact entry array | [V] |
| sub_5697650+entry+0x0 | 8 | [r15]=rax | `0x5697984  mov [r12+r15],r14` | entry+0 ptr | [V] |
| sub_5697650+entry+0x8 | 8 | [r15+8]=rbx | `0x5697988  mov [r12+r15+8],rbx` | entry+8 size | [V] |
| sub_5697650+entry+0x10 | 16 | [r15+0x10]=0 | `0x5697a23  movupd [r15+0x10],xmm0` | entry+0x10 zeroed | [V] |
| sub_5697650+entry+0x20 | 8 | [r15+0x20]=0 | `0x5697a29  mov qword ptr [r15+0x20],0` | entry+0x20 zero | [V] |
| sub_5697650+cb-elem | 8 | stride 0x170 loop | `0x5697c43  call 0x5667E70` `0x5697c48  add rdi,0x170` | per-element callback via sub_5667e70 (stride 0x170) | [V] |
| sub_56cb540+a2+0x40+0x10 | 8 | [rcx+0x10] read | `0x56cb594  sub rdx,[rcx+0x10]` | element size field | [V] |
| sub_56cb540+a2+0x40+0x18 | 8 | [rcx+0x18] read | `0x56cb590  mov rdx,[rcx+0x18]` | element end ptr | [V] |
| sub_56cb540+a2+0x40+0x0 | 8 | [rcx+0x0] read | `0x56cb598  mov rcx,[rcx]` | element array walk | [V] |
| call@0x56cb5e7 | 5 | - | `0x56cb5e7  call 0xA78940` | allocate entry array | [V] |
| call@0x56cb828 | 5 | - | `0x56cb828  call 0x5689800` | compact entry array | [V] |
| sub_56cb540+entry+0x0 | 8 | [r14]=r12 | `0x56cb82d  mov [r14],r12` | entry+0 ptr | [V] |
| sub_56cb540+entry+0x8 | 8 | [r14+8]=rsi | `0x56cb830  mov [r14+8],rsi` | entry+8 size | [V] |
| sub_56cb540+entry+0x10 | 16 | [r14+0x10]=0 | `0x56cb837  movups [r14+0x10],xmm0` | entry+0x10 zeroed | [V] |
| sub_56cb540+entry+0x20 | 8 | [r14+0x20]=0 | `0x56cb83c  mov qword ptr [r14+0x20],0` | entry+0x20 zero | [V] |

### Element-loop per-pass body — entry [V], per-element part blocked
| sub_5684660+a1+0x10 | 8 | [rdx+0x10] read | `0x56846a2  mov r14,[rdx+0x10]` | element-loop start | [V] |
| sub_5684660+a1+0x18 | 8 | [rdx+0x18] read | `0x56846a6  mov rax,[rdx+0x18]` | element-loop end | [V] |
| sub_5684660+a1+0x28 | 8 | [rdx+0x28] read | `0x56846b1  lea rax,[rdx+0x28]` | a1+0x28 read | [V] |
| sub_5684660+a1+0x60 | 8 | [rdx+0x60] read | `0x56846d8  lea rax,[rdx+0x60]` | a1+0x60 read | [V] |
| sub_5684660+elem | 8 | stride 0x290 loop | `0x56846fb  add r14,0x290` `0x5684702  cmp r14,[rbp+0x8E0]` | 0x290-stride element loop [V]; per-element fill/dest writes NOT decoded | [V] |
| sub_5684660+elem+0x240 | 8 | `lea rsi,[r14+0x240]` | `0x568470f  lea rsi,[r14+0x240]` | element data base | [V] |
| sub_5684660+block+0x0 | 8 | vtable data_f25b670->[rbp+0x560] | `0x568472e  lea rax,[0xF25B670]` `0x5684735  mov [rbp+0x560],rax` | per-element block vtable (data_f25b670) | [V] |
| call@0x56848b0 | 5 | - | `0x56848b0  call 0x5690960` | per-element callee (undecoded body) | [V] |
| call@0x56848e3 | 5 | - | `0x56848e3  call 0x5690E10` | per-element callee (undecoded body) | [V] |
| call@0x568491d | 5 | - | `0x568491d  call 0x56912D0` | per-element callee (undecoded body) | [V] |
| call@0x5684970 | 5 | - | `0x5684970  call 0x76A8A0` | resolver (sub_76a8a0) | [V] |

## CLOSES?
NO — single blocking fact: the element-loop per-pass bodies (sub_5684660, vtable data_f25b670, 1 builder site; siblings
sub_567E510/567FD70/56815D0/5682E20/5685EA0/56876F0 per oc_U-EC5b.md) have entry reads and the 0x290-stride loop proven
[V], but their per-element fill and any dest/pass-record writes are not instruction-complete [V]; the per-element callees
sub_5690960/sub_5690e10/sub_56912d0 are undecoded. Every other instantiation named in the item line is now [V] either as
a pass-declaration body (sub_5667860/c80/e70, sub_5667fe0, sub_56685c0, sub_566a450, sub_566adb0, sub_566d690,
sub_566a880, sub_5668d90, sub_5669cf0, sub_567c110, sub_568bdc0, sub_5693680, sub_5694510), as declare machinery
(sub_5698290, sub_568c4e0, wrappers flag 1..5: sub_568c420/sub_568cb30/sub_5693a80/sub_56939c0/sub_56c1fa0), or proven
not to be a declaration body (sub_5669ae0 array destroyer stride 0x290, sub_5689800 memmove, sub_5695960/sub_5696540/
sub_5697650/sub_56cb540 entry-array builders, sub_5697650 sub_5667e70 element callback). Declare-helper bodies
sub_56c9930/sub_56cba60 remain [?] but are helpers, not per-pass bodies; their call sites are [V] (oc_U-EC5b.md).

## TOOL REQUESTS
rdis.exe dis | exe -> verbatim instr listings | all proof lines copied from listings; no custom script needed, verify_oc re-checks every quoted line against the exe