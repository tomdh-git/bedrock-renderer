## NEXT
DONE

# Unit U-Sx2: shadow extractor slice 0x66aa1e0..0x66aa751

Source: docs/progress/_part_Sx2.txt (250 instructions, chunk 2 of 6 of effect_shadow_extractor_66a9d50_66ab74e, shadow extractor 0x66a9d50).

## Phase 1: 0x66aa1e0..0x66aa26c (40 instructions)

Reference-counted cleanup loop over a linked list walked from rdi to rbx ([rbp+0x3B0]); for each node with byte tag [rdi+0x18]==2 it decrements the refcount at [rsi+8] and, if zero, runs the release path ([rsi], [rax] via IAT [0xF99FFA0], then [rsi+0xC] and [rax+8]). After the loop it repeats the same release on [rbp+0x400].

    0x66aa1e0  mov rbx,[rbp+0x3B0]
    0x66aa1e7  jmp short 0x66AA1F4
    0x66aa1e9  nop [rax]
    0x66aa1f0  add rdi,0x28
    0x66aa1f4  cmp rdi,rbx
    0x66aa1f7  je short 0x66AA235
    0x66aa1f9  cmp byte ptr [rdi+0x18],2
    0x66aa1fd  jne short 0x66AA1F0
    0x66aa1ff  mov rsi,[rdi+8]
    0x66aa203  test rsi,rsi
    0x66aa206  je short 0x66AA1F0
    0x66aa208  lock dec dword ptr [rsi+8]
    0x66aa20c  jne short 0x66AA1F0
    0x66aa20e  mov rax,[rsi]
    0x66aa211  mov rax,[rax]
    0x66aa214  mov rcx,rsi
    0x66aa217  call qword ptr [0xF99FFA0]
    0x66aa21d  lock dec dword ptr [rsi+0xC]
    0x66aa221  jne short 0x66AA1F0
    0x66aa223  mov rax,[rsi]
    0x66aa226  mov rax,[rax+8]
    0x66aa22a  mov rcx,rsi
    0x66aa22d  call qword ptr [0xF99FFA0]
    0x66aa233  jmp short 0x66AA1F0
    0x66aa235  mov rsi,[rbp+0x400]
    0x66aa23c  test rsi,rsi
    0x66aa23f  je short 0x66AA26C
    0x66aa241  lock dec dword ptr [rsi+8]
    0x66aa245  jne short 0x66AA26C
    0x66aa247  mov rax,[rsi]
    0x66aa24a  mov rax,[rax]
    0x66aa24d  mov rcx,rsi
    0x66aa250  call qword ptr [0xF99FFA0]
    0x66aa256  lock dec dword ptr [rsi+0xC]
    0x66aa25a  jne short 0x66AA26C
    0x66aa25c  mov rax,[rsi]
    0x66aa25f  mov rax,[rax+8]
    0x66aa263  mov rcx,rsi
    0x66aa266  call qword ptr [0xF99FFA0]
    0x66aa26c  movaps xmm6,[rbp+0x440]

Non-field instructions in this phase (covered in prose only): add rdi,0x28 (advance list node); cmp rdi,rbx / je / jne (loop control); test rsi,rsi / je (null check); mov rcx,rsi; jmp short 0x66AA1F0 (loop tail); test rsi,rsi / je (second null check); jne short 0x66AA26C; jmp short 0x66AA1F0; movaps xmm7..xmm15 from [rbp+0x450..0x4D0] (start of callee save, continues into phase 2).

## Phase 2: 0x66aa273..0x66aa2cd (19 instructions)

Function epilogue: restores xmm7..xmm15 from the stack frame, pops all callee-saved registers, and returns.

    0x66aa273  movaps xmm7,[rbp+0x450]
    0x66aa27a  movaps xmm8,[rbp+0x460]
    0x66aa282  movaps xmm9,[rbp+0x470]
    0x66aa28a  movaps xmm10,[rbp+0x480]
    0x66aa292  movaps xmm11,[rbp+0x490]
    0x66aa29a  movaps xmm12,[rbp+0x4A0]
    0x66aa2a2  movaps xmm13,[rbp+0x4B0]
    0x66aa2aa  movaps xmm14,[rbp+0x4C0]
    0x66aa2b2  movaps xmm15,[rbp+0x4D0]
    0x66aa2ba  add rsp,0x568
    0x66aa2c1  pop rbx
    0x66aa2c2  pop rdi
    0x66aa2c3  pop rsi
    0x66aa2c4  pop r12
    0x66aa2c6  pop r13
    0x66aa2c8  pop r14
    0x66aa2ca  pop r15
    0x66aa2cc  pop rbp
    0x66aa2cd  ret

Non-field instructions: none remaining.

## Phase 3: 0x66aa2ce..0x66aa2eb (6 instructions)

Sets up and calls an external function (0xE935700), then advances rdi by 0x14 and compares against [rbp+0x1A8] to decide whether to loop back to 0x66AA194.

    0x66aa2ce  or rdx,0x27
    0x66aa2d2  mov rcx,rax
    0x66aa2d5  call 0xE935700
    0x66aa2da  add rdi,0x14
    0x66aa2de  cmp rdi,[rbp+0x1A8]
    0x66aa2e5  je 0x66AA194

## Phase 4: 0x66aa2eb..0x66aa3a6 (40 instructions)

SSE lighting/shadow math: loads [rdi+0x10], [rdi+0xC], [rdi+4] into xmm registers; shuffles and multiplies with xmm7/xmm10/xmm11; accumulates into xmm3/xmm4/xmm5; stores results to [rbp+0x1B0], [rbp+0x1B4], [rbp+0x1C4], [rbp+0x1C8], [rbp+0x1D8], [rbp+0x1E8]; writes constants 0x3F800000 to [rbp+0x340] and [rbp+0x354]; stores xmm6 to [rbp+0x344] and [rbp+0x358] (via rax); stores xmm7 low quad to [rbp+0x368].

    0x66aa2eb  movss xmm0,[rdi+0x10]
    0x66aa302  movss xmm3,[rdi+0xC]
    0x66aa307  movsd xmm4,[rdi+4]
    0x66aa30c  movss [rbp+0x1B0],xmm0
    0x66aa314  movups [rbp+0x1B4],xmm1
    0x66aa31b  movss [rbp+0x1C4],xmm0
    0x66aa32e  addss xmm3,xmm9
    0x66aa343  movups [rbp+0x1C8],xmm1
    0x66aa34a  movdqu [rbp+0x1D8],xmm2
    0x66aa352  movsd [rbp+0x1E8],xmm12
    0x66aa35b  mov dword ptr [rbp+0x340],0x3F800000
    0x66aa365  lea rax,[rbp+0x344]
    0x66aa36c  movups [rax],xmm6
    0x66aa36f  mov dword ptr [rbp+0x354],0x3F800000
    0x66aa379  movups [rax+0x14],xmm6
    0x66aa37d  movlps [rbp+0x368],xmm7
    0x66aa392  mulps xmm2,xmm6
    0x66aa395  movaps xmm3,xmm1
    0x66aa398  shufps xmm3,xmm1,0x55
    0x66aa39c  addps xmm3,xmm2
    0x66aa39f  movaps xmm4,xmm2
    0x66aa3a2  shufps xmm4,xmm2,0x55
    0x66aa3a6  addss xmm4,xmm2

Non-field instructions: movaps/shufps/mulps/movq/movss/movsd/addss/movaps/movaps/shufps/mulps/movaps/shufps/addps/movaps/shufps/addss/movaps/addss/movaps/shufps/shufps/unpcklps/addps/movlhps/shufps/addps (register-only SSE ops); lea rax,[rbp+0x344] (address setup).

## Phase 5: 0x66aa3aa..0x66aa494 (40 instructions)

Completes the vector accumulation (movups [rbp+0x370],xmm1); calls 0xAA6580 twice with descriptor pointers ([rbp-0x48]/[rbp+0x340] and [rbp+0x90]/[rbp+0x1B0]); tests byte [rdi]==1 and branches to 0x66AA5F0 if not equal; otherwise loads xmm13-xmm15/xmm8 from stack, stores them to [rbp+0x340..0x370], zeroes [rbp+0x380], loads si from [r12+0x18], initializes descriptor fields [rbp+0x1B4..0x1C8], and stores xmm6 to [r14+0x18].

    0x66aa3aa  movaps xmm5,xmm0
    0x66aa3ad  addss xmm5,xmm4
    0x66aa3b1  movaps xmm8,xmm0
    0x66aa3b5  shufps xmm8,xmm2,0xD4
    0x66aa3ba  shufps xmm8,xmm2,0xE2
    0x66aa3bf  unpcklps xmm1,xmm3
    0x66aa3c2  addps xmm1,xmm8
    0x66aa3c6  movlhps xmm5,xmm4
    0x66aa3c9  shufps xmm1,xmm5,0x24
    0x66aa3cd  addps xmm1,xmm0
    0x66aa3d0  movups [rbp+0x370],xmm1
    0x66aa3d7  mov rcx,rsi
    0x66aa3da  lea rdx,[rbp-0x48]
    0x66aa3de  lea r8,[rbp+0x340]
    0x66aa3e5  call 0xAA6580
    0x66aa3ea  nop
    0x66aa3eb  lea rcx,[rbp+0x90]
    0x66aa3f2  mov rdx,rsi
    0x66aa3f5  lea r8,[rbp+0x1B0]
    0x66aa3fc  call 0xAA6580
    0x66aa401  nop
    0x66aa405  jne 0x66AA5F0
    0x66aa402  cmp byte ptr [rdi],1
    0x66aa40b  movaps xmm13,[rbp+0x90]
    0x66aa413  movaps xmm14,[rbp+0xA0]
    0x66aa41b  movaps xmm15,[rbp+0xB0]
    0x66aa423  movaps xmm8,[rbp+0xC0]
    0x66aa42b  movaps [rbp+0x340],xmm13
    0x66aa433  movaps [rbp+0x350],xmm14
    0x66aa43b  movaps [rbp+0x360],xmm15
    0x66aa443  movaps [rbp+0x370],xmm8
    0x66aa44b  mov byte ptr [rbp+0x380],0
    0x66aa452  mov si,[r12+0x18]
    0x66aa458  mov dword ptr [rbp+0x1B4],0
    0x66aa462  mov byte ptr [rbp+0x1B8],7
    0x66aa469  mov dword ptr [rbp+0x1BC],1
    0x66aa473  mov word ptr [rbp+0x1C0],0x101
    0x66aa47c  mov byte ptr [rbp+0x1C2],2
    0x66aa483  mov dword ptr [rbp+0x1C4],0
    0x66aa48d  mov byte ptr [rbp+0x1C8],0
    0x66aa494  movups [r14+0x18],xmm6

Non-field instructions: movaps xmm1/xmm2/xmm3/xmm4/xmm5/xmm0/xmm8 (register SSE); addps/mulps/shufps/movlhps/shufps/addps (math); lea rdx,[rbp-0x48]/lea r8,[rbp+0x340]/call 0xAA6580/nop (first call); lea rcx,[rbp+0x90]/mov rdx,rsi/lea r8,[rbp+0x1B0]/call 0xAA6580/nop (second call); jne 0x66AA5F0 (branch).

## Phase 6: 0x66aa499..0x66aa5a1 (40 instructions)

Descriptor fill: loads [rbp+0x420] and [rbp+0x418] into [r14+0x30]/[r14+0x28]; initializes [rbp+0x1E8..0x1F8]; loads byte [rbp+0x39F] to [r14+0x55]; loads 16 bytes [rbp+0x38F] to [r14+0x45]; sets [rbp+0x20A]=0xFF; stores [rbp-8] to [rbp+0x210]; calls 0xE869FF0; stores [rbp+0x78] to [rbp+0x290] and zeroes it; stores xmm13-xmm15/xmm8 to [rbp+0x298..0x2C8]; zeroes [rbp+0x2D8]; stores si to [rbp+0x2E0], [rbp+0x3A0] to [rbp+0x2E8]; stores xmm6 to [r14+0x13C] and zeroes [r14+0x14C]; computes (rdx count)/8 via magic multiply and calls 0x56B8630.

    0x66aa499  mov eax,[rbp+0x420]
    0x66aa49f  mov [r14+0x30],eax
    0x66aa4a3  mov rax,[rbp+0x418]
    0x66aa4aa  mov [r14+0x28],rax
    0x66aa4ae  mov byte ptr [rbp+0x1E8],8
    0x66aa4b5  mov qword ptr [rbp+0x1EC],0
    0x66aa4c0  mov dword ptr [rbp+0x1F4],0
    0x66aa4ca  mov byte ptr [rbp+0x1F8],8
    0x66aa4d1  movzx eax,byte ptr [rbp+0x39F]
    0x66aa4d8  mov [r14+0x55],al
    0x66aa4dc  movups xmm0,[rbp+0x38F]
    0x66aa4e3  movups [r14+0x45],xmm0
    0x66aa4e8  mov byte ptr [rbp+0x20A],0xFF
    0x66aa4ef  mov rax,[rbp-8]
    0x66aa4f3  mov [rbp+0x210],rax
    0x66aa4fa  lea rcx,[rbp+0x218]
    0x66aa501  mov rdx,r13
    0x66aa504  call 0xE869FF0
    0x66aa509  nop
    0x66aa50a  mov rax,[rbp+0x78]
    0x66aa50e  mov [rbp+0x290],rax
    0x66aa515  mov qword ptr [rbp+0x78],0
    0x66aa51d  movups [rbp+0x298],xmm13
    0x66aa525  movups [rbp+0x2A8],xmm14
    0x66aa52d  movups [rbp+0x2B8],xmm15
    0x66aa535  movups [rbp+0x2C8],xmm8
    0x66aa53d  mov byte ptr [rbp+0x2D8],0
    0x66aa544  mov [rbp+0x2E0],si
    0x66aa54b  mov rax,[rbp+0x3A0]
    0x66aa552  mov [rbp+0x2E8],rax
    0x66aa559  movups [r14+0x13C],xmm6
    0x66aa561  mov qword ptr [r14+0x14C],0
    0x66aa56c  mov rdx,[rbp+0x3B0]
    0x66aa573  sub rdx,[rbp+0x3A8]
    0x66aa57a  sar rdx,3
    0x66aa57e  mov rax,0xCCCCCCCCCCCCCCCD
    0x66aa588  imul rdx,rax
    0x66aa58c  lea rcx,[rbp+0x2E8]
    0x66aa593  lea r8,[rbp+0x3A8]
    0x66aa59a  lea r9,[rbp+0x3B0]
    0x66aa5a1  call 0x56B8630

Non-field instructions: lea rcx,[rbp+0x218]/mov rdx,r13/call 0xE869FF0/nop; lea rcx,[rbp+0x2E8]/lea r8,[rbp+0x3A8]/lea r9,[rbp+0x3B0]; sar rdx,3; mov rax,0xCCCCCCCCCCCCCCCD; imul rdx,rax; nop.

## Phase 7: 0x66aa5a6..0x66aa6af (40 instructions)

Post-call store [rbp+0x3C0]->[rbp+0x308]; sets [rbp+0x320]=0xFF; switch on byte [rbp+0x3D8] (jump table via [0xF2BF858]); case 0 stores [rbp+0x3C8] to [rbp+0x310] and jumps to 0x66AA862. Then the alternate branch (from 0x66AA5F0): loads xmm8-xmm15 from [rbp+0x90..0xC0], stores to [rbp+0x340..0x370], zeroes [rbp+0x380], loads si from [r12+0x18], initializes descriptor fields [rbp+0x1B4..0x1C8], stores xmm6 to [r14+0x18], loads [rbp+0x420]/[rbp+0x418] to [r14+0x30]/[r14+0x28], initializes [rbp+0x1E8..0x1F8].

    0x66aa5a6  nop
    0x66aa5a7  mov rax,[rbp+0x3C0]
    0x66aa5ae  mov [rbp+0x308],rax
    0x66aa5b5  mov byte ptr [rbp+0x320],0xFF
    0x66aa5bc  movzx eax,byte ptr [rbp+0x3D8]
    0x66aa5c3  cmp rax,3
    0x66aa5c7  ja 0x66AA868
    0x66aa5cd  lea rdx,[0xF2BF858]
    0x66aa5d4  movsxd rcx,[rdx+rax*4]
    0x66aa5d8  add rcx,rdx
    0x66aa5db  jmp rcx
    0x66aa5dd  mov rcx,[rbp+0x3C8]
    0x66aa5e4  mov [rbp+0x310],rcx
    0x66aa5eb  jmp 0x66AA862
    0x66aa5f0  movaps xmm8,[rbp+0x90]
    0x66aa5f8  movaps xmm13,[rbp+0xA0]
    0x66aa600  movaps xmm14,[rbp+0xB0]
    0x66aa608  movaps xmm15,[rbp+0xC0]
    0x66aa610  movaps [rbp+0x340],xmm8
    0x66aa618  movaps [rbp+0x350],xmm13
    0x66aa620  movaps [rbp+0x360],xmm14
    0x66aa628  movaps [rbp+0x370],xmm15
    0x66aa630  mov byte ptr [rbp+0x380],0
    0x66aa637  mov si,[r12+0x18]
    0x66aa63d  mov dword ptr [rbp+0x1B4],0
    0x66aa647  mov byte ptr [rbp+0x1B8],7
    0x66aa64e  mov dword ptr [rbp+0x1BC],1
    0x66aa658  mov word ptr [rbp+0x1C0],0x101
    0x66aa661  mov byte ptr [rbp+0x1C2],2
    0x66aa668  mov dword ptr [rbp+0x1C4],0
    0x66aa672  mov byte ptr [rbp+0x1C8],0
    0x66aa679  movups [r14+0x18],xmm6
    0x66aa67e  mov eax,[rbp+0x420]
    0x66aa684  mov [r14+0x30],eax
    0x66aa688  mov rax,[rbp+0x418]
    0x66aa68f  mov [r14+0x28],rax
    0x66aa693  mov byte ptr [rbp+0x1E8],8
    0x66aa69a  mov qword ptr [rbp+0x1EC],0
    0x66aa6a5  mov dword ptr [rbp+0x1F4],0
    0x66aa6af  mov byte ptr [rbp+0x1F8],8

Non-field instructions: nop; cmp rax,3 / ja 0x66AA868; lea rdx,[0xF2BF858]; movsxd rcx,[rdx+rax*4]; add rcx,rdx; jmp rcx; jmp 0x66AA862; nop.

## Phase 8: 0x66aa6b6..0x66aa751 (25 instructions)

Continues descriptor fill from phase 7: loads byte [rbp+0x39F] to [r14+0x55]; loads 16 bytes [rbp+0x38F] to [r14+0x45]; sets [rbp+0x20A]=0xFF; stores [rbp-8] to [rbp+0x210]; calls 0xE869FF0; stores [rbp+0x78] to [rbp+0x290] and zeroes it; stores xmm8-xmm15 to [rbp+0x298..0x2C8]; zeroes [rbp+0x2D8]; stores si to [rbp+0x2E0], [rbp+0x3A0] to [rbp+0x2E8]; stores xmm6 to [r14+0x13C] and zeroes [r14+0x14C]; ends with [rbp+0x3B0] load (start of next chunk).

    0x66aa6b6  movzx eax,byte ptr [rbp+0x39F]
    0x66aa6bd  mov [r14+0x55],al
    0x66aa6c1  movups xmm0,[rbp+0x38F]
    0x66aa6c8  movups [r14+0x45],xmm0
    0x66aa6cd  mov byte ptr [rbp+0x20A],0xFF
    0x66aa6d4  mov rax,[rbp-8]
    0x66aa6d8  mov [rbp+0x210],rax
    0x66aa6df  lea rcx,[rbp+0x218]
    0x66aa6e6  mov rdx,r13
    0x66aa6e9  call 0xE869FF0
    0x66aa6ee  nop
    0x66aa6ef  mov rax,[rbp+0x78]
    0x66aa6f3  mov [rbp+0x290],rax
    0x66aa6fa  mov qword ptr [rbp+0x78],0
    0x66aa702  movups [rbp+0x298],xmm8
    0x66aa70a  movups [rbp+0x2A8],xmm13
    0x66aa712  movups [rbp+0x2B8],xmm14
    0x66aa71a  movups [rbp+0x2C8],xmm15
    0x66aa722  mov byte ptr [rbp+0x2D8],0
    0x66aa729  mov [rbp+0x2E0],si
    0x66aa730  mov rax,[rbp+0x3A0]
    0x66aa737  mov [rbp+0x2E8],rax
    0x66aa73e  movups [r14+0x13C],xmm6
    0x66aa746  mov qword ptr [r14+0x14C],0
    0x66aa751  mov rdx,[rbp+0x3B0]

Non-field instructions: lea rcx,[rbp+0x218]/mov rdx,r13/call 0xE869FF0/nop.

## Field table: every [reg+off] load/store in the slice

| offset | size | address | verbatim line | meaning |
|---|---|---|---|---|
| 0x0 | 1B | [rdi] | `0x66aa402  cmp byte ptr [rdi],1` | type tag compared to 1 |
| 0x4 | 8B | [rdi+4] | `0x66aa307  movsd xmm4,[rdi+4]` | double field at rdi+4 |
| 0x8 | 8B | [rdi+8] | `0x66aa1ff  mov rsi,[rdi+8]` | pointer/next node at rdi+8 |
| 0xC | 4B | [rdi+0xC] | `0x66aa302  movss xmm3,[rdi+0xC]` | float field at rdi+0xC |
| 0x10 | 4B | [rdi+0x10] | `0x66aa2eb  movss xmm0,[rdi+0x10]` | float field at rdi+0x10 |
| 0x18 | var | [rdi+0x18],[r12+0x18],[r14+0x18] | `0x66aa1f9  cmp byte ptr [rdi+0x18],2` / `0x66aa452  mov si,[r12+0x18]` / `0x66aa637  mov si,[r12+0x18]` / `0x66aa494  movups [r14+0x18],xmm6` / `0x66aa679  movups [r14+0x18],xmm6` | type tag vs 2 / index word / vector store |
| 0x1A8 | 8B | [rbp+0x1A8] | `0x66aa2de  cmp rdi,[rbp+0x1A8]` | loop bound compared against rdi |
| 0x1B0 | 4B | [rbp+0x1B0] | `0x66aa30c  movss [rbp+0x1B0],xmm0` | float store |
| 0x1B4 | var | [rbp+0x1B4] | `0x66aa314  movups [rbp+0x1B4],xmm1` / `0x66aa458  mov dword ptr [rbp+0x1B4],0` / `0x66aa63d  mov dword ptr [rbp+0x1B4],0` | vector store / dword zero init |
| 0x1B8 | 1B | [rbp+0x1B8] | `0x66aa462  mov byte ptr [rbp+0x1B8],7` / `0x66aa647  mov byte ptr [rbp+0x1B8],7` | byte store = 7 |
| 0x1BC | 4B | [rbp+0x1BC] | `0x66aa469  mov dword ptr [rbp+0x1BC],1` / `0x66aa64e  mov dword ptr [rbp+0x1BC],1` | dword store = 1 |
| 0x1C0 | 2B | [rbp+0x1C0] | `0x66aa473  mov word ptr [rbp+0x1C0],0x101` / `0x66aa658  mov word ptr [rbp+0x1C0],0x101` | word store = 0x101 |
| 0x1C2 | 1B | [rbp+0x1C2] | `0x66aa47c  mov byte ptr [rbp+0x1C2],2` / `0x66aa661  mov byte ptr [rbp+0x1C2],2` | byte store = 2 |
| 0x1C4 | 4B | [rbp+0x1C4] | `0x66aa31b  movss [rbp+0x1C4],xmm0` / `0x66aa483  mov dword ptr [rbp+0x1C4],0` / `0x66aa668  mov dword ptr [rbp+0x1C4],0` | float/dword store / zero init |
| 0x1C8 | var | [rbp+0x1C8] | `0x66aa343  movups [rbp+0x1C8],xmm1` / `0x66aa48d  mov byte ptr [rbp+0x1C8],0` / `0x66aa672  mov byte ptr [rbp+0x1C8],0` | vector store / byte zero init |
| 0x1D8 | 16B | [rbp+0x1D8] | `0x66aa34a  movdqu [rbp+0x1D8],xmm2` | unaligned 16-byte store |
| 0x1E8 | var | [rbp+0x1E8] | `0x66aa352  movsd [rbp+0x1E8],xmm12` / `0x66aa4ae  mov byte ptr [rbp+0x1E8],8` / `0x66aa693  mov byte ptr [rbp+0x1E8],8` | qword store / byte store = 8 |
| 0x1EC | 8B | [rbp+0x1EC] | `0x66aa4b5  mov qword ptr [rbp+0x1EC],0` / `0x66aa69a  mov qword ptr [rbp+0x1EC],0` | qword zero init |
| 0x1F4 | 4B | [rbp+0x1F4] | `0x66aa4c0  mov dword ptr [rbp+0x1F4],0` / `0x66aa6a5  mov dword ptr [rbp+0x1F4],0` | dword zero init |
| 0x1F8 | 1B | [rbp+0x1F8] | `0x66aa4ca  mov byte ptr [rbp+0x1F8],8` / `0x66aa6af  mov byte ptr [rbp+0x1F8],8` | byte store = 8 |
| 0x20A | 1B | [rbp+0x20A] | `0x66aa4e8  mov byte ptr [rbp+0x20A],0xFF` / `0x66aa6cd  mov byte ptr [rbp+0x20A],0xFF` | byte store = 0xFF |
| 0x210 | 8B | [rbp+0x210] | `0x66aa4f3  mov [rbp+0x210],rax` / `0x66aa6d8  mov [rbp+0x210],rax` | qword store from [rbp-8] |
| 0x290 | 8B | [rbp+0x290] | `0x66aa50e  mov [rbp+0x290],rax` / `0x66aa6f3  mov [rbp+0x290],rax` | qword store from [rbp+0x78] |
| 0x298 | 16B | [rbp+0x298] | `0x66aa51d  movups [rbp+0x298],xmm13` / `0x66aa702  movups [rbp+0x298],xmm8` | 16-byte vector store |
| 0x2A8 | 16B | [rbp+0x2A8] | `0x66aa525  movups [rbp+0x2A8],xmm14` / `0x66aa70a  movups [rbp+0x2A8],xmm13` | 16-byte vector store |
| 0x2B8 | 16B | [rbp+0x2B8] | `0x66aa52d  movups [rbp+0x2B8],xmm15` / `0x66aa712  movups [rbp+0x2B8],xmm14` | 16-byte vector store |
| 0x2C8 | 16B | [rbp+0x2C8] | `0x66aa535  movups [rbp+0x2C8],xmm8` / `0x66aa71a  movups [rbp+0x2C8],xmm15` | 16-byte vector store |
| 0x2D8 | 1B | [rbp+0x2D8] | `0x66aa53d  mov byte ptr [rbp+0x2D8],0` / `0x66aa722  mov byte ptr [rbp+0x2D8],0` | byte zero init |
| 0x2E0 | 2B | [rbp+0x2E0] | `0x66aa544  mov [rbp+0x2E0],si` / `0x66aa729  mov [rbp+0x2E0],si` | word store from si |
| 0x2E8 | 8B | [rbp+0x2E8] | `0x66aa552  mov [rbp+0x2E8],rax` / `0x66aa737  mov [rbp+0x2E8],rax` | qword store from [rbp+0x3A0] |
| 0x308 | 8B | [rbp+0x308] | `0x66aa5ae  mov [rbp+0x308],rax` | qword store from [rbp+0x3C0] |
| 0x310 | 8B | [rbp+0x310] | `0x66aa5e4  mov [rbp+0x310],rcx` | qword store from [rbp+0x3C8] (switch case 0) |
| 0x320 | 1B | [rbp+0x320] | `0x66aa5b5  mov byte ptr [rbp+0x320],0xFF` | byte store = 0xFF |
| 0x340 | var | [rbp+0x340] | `0x66aa35b  mov dword ptr [rbp+0x340],0x3F800000` / `0x66aa42b  movaps [rbp+0x340],xmm13` / `0x66aa610  movaps [rbp+0x340],xmm8` | dword const 1.0f / 16-byte vector store |
| 0x344 | 16B | [rbp+0x344] | `0x66aa36c  movups [rax],xmm6` (rax = rbp+0x344) | 16-byte vector store via rax |
| 0x350 | 16B | [rbp+0x350] | `0x66aa433  movaps [rbp+0x350],xmm14` / `0x66aa618  movaps [rbp+0x350],xmm13` | 16-byte vector store |
| 0x354 | 4B | [rbp+0x354] | `0x66aa36f  mov dword ptr [rbp+0x354],0x3F800000` | dword const 1.0f |
| 0x358 | 16B | [rbp+0x358] | `0x66aa379  movups [rax+0x14],xmm6` (rax+0x14 = rbp+0x358) | 16-byte vector store via rax |
| 0x360 | 16B | [rbp+0x360] | `0x66aa43b  movaps [rbp+0x360],xmm15` / `0x66aa620  movaps [rbp+0x360],xmm14` | 16-byte vector store |
| 0x368 | 8B | [rbp+0x368] | `0x66aa37d  movlps [rbp+0x368],xmm7` | low quadword store |
| 0x370 | 16B | [rbp+0x370] | `0x66aa3d0  movups [rbp+0x370],xmm1` / `0x66aa443  movaps [rbp+0x370],xmm8` / `0x66aa628  movaps [rbp+0x370],xmm15` | 16-byte vector store |
| 0x380 | 1B | [rbp+0x380] | `0x66aa44b  mov byte ptr [rbp+0x380],0` / `0x66aa630  mov byte ptr [rbp+0x380],0` | byte zero init |
| 0x38F | 16B | [rbp+0x38F] | `0x66aa4dc  movups xmm0,[rbp+0x38F]` / `0x66aa6c1  movups xmm0,[rbp+0x38F]` | 16-byte load |
| 0x39F | 1B | [rbp+0x39F] | `0x66aa4d1  movzx eax,byte ptr [rbp+0x39F]` / `0x66aa6b6  movzx eax,byte ptr [rbp+0x39F]` | byte load (zero-extended) |
| 0x3A0 | 8B | [rbp+0x3A0] | `0x66aa54b  mov rax,[rbp+0x3A0]` / `0x66aa730  mov rax,[rbp+0x3A0]` | qword load |
| 0x3A8 | 8B | [rbp+0x3A8] | `0x66aa573  sub rdx,[rbp+0x3A8]` | qword load (subtrahend for count) |
| 0x3B0 | 8B | [rbp+0x3B0] | `0x66aa1e0  mov rbx,[rbp+0x3B0]` / `0x66aa235  mov rsi,[rbp+0x400]` is separate / `0x66aa56c  mov rdx,[rbp+0x3B0]` / `0x66aa751  mov rdx,[rbp+0x3B0]` | list head / end pointer load |
| 0x3C0 | 8B | [rbp+0x3C0] | `0x66aa5a7  mov rax,[rbp+0x3C0]` | qword load |
| 0x3C8 | 8B | [rbp+0x3C8] | `0x66aa5dd  mov rcx,[rbp+0x3C8]` | qword load (switch case 0 target) |
| 0x3D8 | 1B | [rbp+0x3D8] | `0x66aa5bc  movzx eax,byte ptr [rbp+0x3D8]` | switch discriminant byte |
| 0x400 | 8B | [rbp+0x400] | `0x66aa235  mov rsi,[rbp+0x400]` | qword load (second object) |
| 0x418 | 8B | [rbp+0x418] | `0x66aa4a3  mov rax,[rbp+0x418]` / `0x66aa688  mov rax,[rbp+0x418]` | qword load |
| 0x420 | 4B | [rbp+0x420] | `0x66aa499  mov eax,[rbp+0x420]` / `0x66aa67e  mov eax,[rbp+0x420]` | dword load |
| 0x440 | 16B | [rbp+0x440] | `0x66aa26c  movaps xmm6,[rbp+0x440]` | 16-byte load (callee restore) |
| 0x450 | 16B | [rbp+0x450] | `0x66aa273  movaps xmm7,[rbp+0x450]` | 16-byte load |
| 0x460 | 16B | [rbp+0x460] | `0x66aa27a  movaps xmm8,[rbp+0x460]` | 16-byte load |
| 0x470 | 16B | [rbp+0x470] | `0x66aa282  movaps xmm9,[rbp+0x470]` | 16-byte load |
| 0x480 | 16B | [rbp+0x480] | `0x66aa28a  movaps xmm10,[rbp+0x480]` | 16-byte load |
| 0x490 | 16B | [rbp+0x490] | `0x66aa292  movaps xmm11,[rbp+0x490]` | 16-byte load |
| 0x4A0 | 16B | [rbp+0x4A0] | `0x66aa29a  movaps xmm12,[rbp+0x4A0]` | 16-byte load |
| 0x4B0 | 16B | [rbp+0x4B0] | `0x66aa2a2  movaps xmm13,[rbp+0x4B0]` | 16-byte load |
| 0x4C0 | 16B | [rbp+0x4C0] | `0x66aa2aa  movaps xmm14,[rbp+0x4C0]` | 16-byte load |
| 0x4D0 | 16B | [rbp+0x4D0] | `0x66aa2b2  movaps xmm15,[rbp+0x4D0]` | 16-byte load |
| 0x78 | 8B | [rbp+0x78] | `0x66aa50a  mov rax,[rbp+0x78]` / `0x66aa515  mov qword ptr [rbp+0x78],0` / `0x66aa6ef  mov rax,[rbp+0x78]` / `0x66aa6fa  mov qword ptr [rbp+0x78],0` | qword load/store (save/restore/zero) |
| -8 | 8B | [rbp-8] | `0x66aa4ef  mov rax,[rbp-8]` / `0x66aa6d4  mov rax,[rbp-8]` | qword load (stack cookie/saved value) |
| 0x90 | 16B | [rbp+0x90] | `0x66aa40b  movaps xmm13,[rbp+0x90]` / `0x66aa5f0  movaps xmm8,[rbp+0x90]` | 16-byte load |
| 0xA0 | 16B | [rbp+0xA0] | `0x66aa413  movaps xmm14,[rbp+0xA0]` / `0x66aa5f8  movaps xmm13,[rbp+0xA0]` | 16-byte load |
| 0xB0 | 16B | [rbp+0xB0] | `0x66aa41b  movaps xmm15,[rbp+0xB0]` / `0x66aa600  movaps xmm14,[rbp+0xB0]` | 16-byte load |
| 0xC0 | 16B | [rbp+0xC0] | `0x66aa423  movaps xmm8,[rbp+0xC0]` / `0x66aa608  movaps xmm15,[rbp+0xC0]` | 16-byte load |
| r14+0x28 | 8B | [r14+0x28] | `0x66aa4aa  mov [r14+0x28],rax` / `0x66aa68f  mov [r14+0x28],rax` | qword store |
| r14+0x30 | 4B | [r14+0x30] | `0x66aa49f  mov [r14+0x30],eax` / `0x66aa684  mov [r14+0x30],eax` | dword store |
| r14+0x45 | 16B | [r14+0x45] | `0x66aa4e3  movups [r14+0x45],xmm0` / `0x66aa6c8  movups [r14+0x45],xmm0` | 16-byte vector store |
| r14+0x55 | 1B | [r14+0x55] | `0x66aa4d8  mov [r14+0x55],al` / `0x66aa6bd  mov [r14+0x55],al` | byte store |
| r14+0x13C | 16B | [r14+0x13C] | `0x66aa559  movups [r14+0x13C],xmm6` / `0x66aa73e  movups [r14+0x13C],xmm6` | 16-byte vector store |
| r14+0x14C | 8B | [r14+0x14C] | `0x66aa561  mov qword ptr [r14+0x14C],0` / `0x66aa746  mov qword ptr [r14+0x14C],0` | qword zero init |
| rsi | 8B | [rsi] | `0x66aa20e  mov rax,[rsi]` / `0x66aa223  mov rax,[rsi]` / `0x66aa247  mov rax,[rsi]` / `0x66aa25c  mov rax,[rsi]` | qword load (vtable/control block) |
| rsi+8 | 4B | [rsi+8] | `0x66aa208  lock dec dword ptr [rsi+8]` / `0x66aa241  lock dec dword ptr [rsi+8]` | refcount decrement (R/W) |
| rsi+0xC | 4B | [rsi+0xC] | `0x66aa21d  lock dec dword ptr [rsi+0xC]` / `0x66aa256  lock dec dword ptr [rsi+0xC]` | refcount decrement (R/W) |
| rax | 8B | [rax] | `0x66aa211  mov rax,[rax]` / `0x66aa24a  mov rax,[rax]` | qword load (vtable deref) |
| rax+8 | 8B | [rax+8] | `0x66aa226  mov rax,[rax+8]` / `0x66aa25f  mov rax,[rax+8]` | qword load (destructor/release) |
| 0x66aa1e7 | — | — | `0x66aa1e7  jmp short 0x66AA1F4` | loop tail jump |
| 0x66aa1e9 | — | — | `0x66aa1e9  nop [rax]` | alignment nop |
| 0x66aa1f0 | — | — | `0x66aa1f0  add rdi,0x28` | advance to next list node |
| 0x66aa1f4 | — | — | `0x66aa1f4  cmp rdi,rbx` | compare node pointer to list end |
| 0x66aa1f7 | — | — | `0x66aa1f7  je short 0x66AA235` | exit loop when rdi==rbx |
| 0x66aa1fd | — | — | `0x66aa1fd  jne short 0x66AA1F0` | skip node if tag != 2 |
| 0x66aa203 | — | — | `0x66aa203  test rsi,rsi` | null check on node pointer |
| 0x66aa206 | — | — | `0x66aa206  je short 0x66AA1F0` | skip if null |
| 0x66aa20c | — | — | `0x66aa20c  jne short 0x66AA1F0` | loop if refcount not zero |
| 0x66aa214 | — | — | `0x66aa214  mov rcx,rsi` | set 'this' for release call |
| 0x66aa221 | — | — | `0x66aa221  jne short 0x66AA1F0` | loop if second refcount not zero |
| 0x66aa22a | — | — | `0x66aa22a  mov rcx,rsi` | set 'this' for destructor call |
| 0x66aa233 | — | — | `0x66aa233  jmp short 0x66AA1F0` | loop tail |
| 0x66aa23c | — | — | `0x66aa23c  test rsi,rsi` | null check on [rbp+0x400] object |
| 0x66aa23f | — | — | `0x66aa23f  je short 0x66AA26C` | skip if null |
| 0x66aa245 | — | — | `0x66aa245  jne short 0x66AA26C` | loop if refcount not zero |
| 0x66aa24d | — | — | `0x66aa24d  mov rcx,rsi` | set 'this' for release call |
| 0x66aa25a | — | — | `0x66aa25a  jne short 0x66AA26C` | loop if second refcount not zero |
| 0x66aa263 | — | — | `0x66aa263  mov rcx,rsi` | set 'this' for destructor call |
| 0x66aa2ba | — | — | `0x66aa2ba  add rsp,0x568` | deallocate stack frame |
| 0x66aa2ce | — | — | `0x66aa2ce  or rdx,0x27` | set flags for external call |
| 0x66aa2d2 | — | — | `0x66aa2d2  mov rcx,rax` | set 'this' for external call |
| 0x66aa2d5 | — | — | `0x66aa2d5  call 0xE935700` | external function call |
| 0x66aa2da | — | — | `0x66aa2da  add rdi,0x14` | advance outer loop pointer |
| 0x66aa2e5 | — | — | `0x66aa2e5  je 0x66AA194` | loop back if rdi==bound |
| 0x66aa2f0 | — | — | `0x66aa2f0  movaps xmm1,xmm0` | copy vector to xmm1 |
| 0x66aa2f3 | — | — | `0x66aa2f3  shufps xmm1,xmm0,0` | broadcast xmm0 element 0 |
| 0x66aa2f7 | — | — | `0x66aa2f7  mulps xmm1,xmm7` | multiply by xmm7 |
| 0x66aa2fa | — | — | `0x66aa2fa  movq xmm2,xmm1` | copy low quadword to xmm2 |
| 0x66aa2fe | — | — | `0x66aa2fe  shufps xmm1,xmm1,0x55` | shuffle xmm1 |
| 0x66aa323 | — | — | `0x66aa323  movaps xmm5,xmm0` | copy xmm0 to xmm5 |
| 0x66aa326 | — | — | `0x66aa326  mulss xmm5,[0xEEE7C00]` | multiply by constant |
| 0x66aa333 | — | — | `0x66aa333  movaps xmm0,xmm10` | copy xmm10 to xmm0 |
| 0x66aa337 | — | — | `0x66aa337  movss xmm0,xmm3` | move xmm3 to xmm0 |
| 0x66aa33b | — | — | `0x66aa33b  shufps xmm0,xmm0,0xC4` | shuffle xmm0 |
| 0x66aa33f | — | — | `0x66aa33f  mulps xmm0,xmm11` | multiply by xmm11 |
| 0x66aa384 | — | — | `0x66aa384  movq xmm1,xmm5` | copy low quadword to xmm1 |
| 0x66aa388 | — | — | `0x66aa388  shufps xmm1,xmm6,0xE2` | shuffle with xmm6 |
| 0x66aa38c | — | — | `0x66aa38c  addps xmm1,xmm4` | add xmm4 to xmm1 |
| 0x66aa38f | — | — | `0x66aa38f  movaps xmm2,xmm1` | copy xmm1 to xmm2 |
