## NEXT
DONE

# Unit U-Sx1 — shadow extractor 0x66a9d50, slice 0x66a9d50..0x66aa1de

Input: docs/progress/_part_Sx1.txt — 250 instructions (0x66a9d50 .. 0x66aa1de), the full listed slice (chunk 1 of 6 of effect_shadow_extractor_66a9d50_66ab74e). Split into 7 phases of at most 40 instructions each. Every instruction below is quoted verbatim from the input (two spaces after the address) and its phase covers every instruction of the slice with nothing skipped.

All field claims are [V] (seen in this disassembly listing). No string and no instruction in this slice documents field semantics, so every table meaning is '-'.

## Phase 1: 0x66a9d50..0x66a9e27 — 40 instructions
Prologue: push eight callee-saved registers (rbp, r15, r14, r13, r12, rsi, rdi, rbx), subtract 0x568 from rsp, and set frame pointer rbp=rsp+0x80. Spill xmm8-xmm15 to [rbp+0x440]..[rbp+0x4D0], store sentinel qword 0xFFFFFFFFFFFFFFFE at [rbp+0x438], copy the four arguments (r14=r9, r12=r8, rbx=rdx, r15=rcx), read the two global counters at 0x129F8D08 and 0x128767C8 and the TEB pointer from gs:[0x58] for the cookie check (jg 0x66AB66F on failure), load [r15+0x40] and [r15+0x68], zero [rbp+0x1B0], build a descriptor at [rbp+0xD0] (qword 0xF56F38F, then qword 0xE at [rbp+0xD8]), stage argument pointers at [rsp+0x20] and [rsp+0x28], and call 0x675E440. [V]

0x66a9d50  push rbp
0x66a9d51  push r15
0x66a9d53  push r14
0x66a9d55  push r13
0x66a9d57  push r12
0x66a9d59  push rsi
0x66a9d5a  push rdi
0x66a9d5b  push rbx
0x66a9d5c  sub rsp,0x568
0x66a9d63  lea rbp,[rsp+0x80]
0x66a9d6b  movaps [rbp+0x4D0],xmm15
0x66a9d73  movaps [rbp+0x4C0],xmm14
0x66a9d7b  movaps [rbp+0x4B0],xmm13
0x66a9d83  movaps [rbp+0x4A0],xmm12
0x66a9d8b  movaps [rbp+0x490],xmm11
0x66a9d93  movaps [rbp+0x480],xmm10
0x66a9d9b  movaps [rbp+0x470],xmm9
0x66a9da3  movaps [rbp+0x460],xmm8
0x66a9dab  movaps [rbp+0x450],xmm7
0x66a9db2  movaps [rbp+0x440],xmm6
0x66a9db9  mov qword ptr [rbp+0x438],0xFFFFFFFFFFFFFFFE
0x66a9dc4  mov r14,r9
0x66a9dc7  mov r12,r8
0x66a9dca  mov rbx,rdx
0x66a9dcd  mov r15,rcx
0x66a9dd0  mov eax,[0x129F8D08]
0x66a9dd6  mov ecx,[0x128767C8]
0x66a9ddc  mov rdx,gs:[0x58]
0x66a9de5  mov rcx,[rdx+rcx*8]
0x66a9de9  cmp eax,[rcx+4]
0x66a9def  jg 0x66AB66F
0x66a9df5  mov r9,[r15+0x40]
0x66a9df9  mov rcx,[r15+0x68]
0x66a9dfd  xorps xmm0,xmm0
0x66a9e00  movaps [rbp+0x1B0],xmm0
0x66a9e07  lea rax,[0xF56F38F]
0x66a9e0e  mov [rbp+0xD0],rax
0x66a9e15  mov qword ptr [rbp+0xD8],0xE
0x66a9e20  lea rax,[rbp+0x1B0]
0x66a9e27  mov [rsp+0x28],rax

## Phase 2: 0x66a9e2c..0x66a9ed9 — 40 instructions
After the call, stage the second argument pointer at [rsp+0x20] and call 0x675E440 (already entered); then reload rax=[rbp+0x3F8], rsi=[rax], and exit to 0x66AA235 if rsi is null or if byte [rsi+0x10] != 1; repeat the global/TEB cookie check (jg 0x66AB6D7). Reload rax=[rbp+0x3F8], rcx=[rax+8]; if rcx is nonzero, lock-inc the dword at [rcx+8]. Then rcx=[rax], rsi=[rax+8], rax=[rcx+0x18], rdi=[rax]; release rsi: lock-dec dword [rsi+8], and if it reaches zero run the two-step teardown — mov rax,[rsi]; mov rax,[rax]; call qword ptr [0xF99FFA0]; lock-dec dword [rsi+0xC]; mov rax,[rsi]; mov rax,[rax+8]; call qword ptr [0xF99FFA0]. The rcx==0 path jumps to 0x66A9EE1 and loads rax=[rax], rax=[rax+0x18], rdi=[rax]; both paths converge at 0x66A9EEB, where the phase ends with test rdi,rdi. [V]

0x66a9e2c  lea rax,[rbp+0xD0]
0x66a9e33  mov [rsp+0x20],rax
0x66a9e38  lea r8,[0x129F8CF8]
0x66a9e3f  lea rdx,[rbp+0x3F8]
0x66a9e46  call 0x675E440
0x66a9e4b  mov rax,[rbp+0x3F8]
0x66a9e52  mov rsi,[rax]
0x66a9e55  test rsi,rsi
0x66a9e58  je 0x66AA235
0x66a9e5e  mov eax,[0x129CA5E0]
0x66a9e64  mov ecx,[0x128767C8]
0x66a9e6a  mov rdx,gs:[0x58]
0x66a9e73  mov rcx,[rdx+rcx*8]
0x66a9e77  cmp eax,[rcx+4]
0x66a9e7d  jg 0x66AB6D7
0x66a9e83  cmp byte ptr [rsi+0x10],1
0x66a9e87  jne 0x66AA235
0x66a9e8d  mov rax,[rbp+0x3F8]
0x66a9e94  mov rcx,[rax+8]
0x66a9e98  test rcx,rcx
0x66a9e9b  je short 0x66A9EE1
0x66a9e9d  lock inc dword ptr [rcx+8]
0x66a9ea1  mov rcx,[rax]
0x66a9ea4  mov rsi,[rax+8]
0x66a9ea8  mov rax,[rcx+0x18]
0x66a9eac  mov rdi,[rax]
0x66a9eaf  test rsi,rsi
0x66a9eb2  je short 0x66A9EEB
0x66a9eb4  lock dec dword ptr [rsi+8]
0x66a9eb8  jne short 0x66A9EEB
0x66a9eba  mov rax,[rsi]
0x66a9ebd  mov rax,[rax]
0x66a9ec0  mov rcx,rsi
0x66a9ec3  call qword ptr [0xF99FFA0]
0x66a9ec9  lock dec dword ptr [rsi+0xC]
0x66a9ecd  jne short 0x66A9EEB
0x66a9ecf  mov rax,[rsi]
0x66a9ed2  mov rax,[rax+8]
0x66a9ed6  mov rcx,rsi
0x66a9ed9  call qword ptr [0xF99FFA0]

## Phase 3: 0x66a9edf..0x66a9f98 — 40 instructions
Unconditional jmp short to 0x66A9EEB; the fall-through target 0x66A9EE1 loads rax=[rax], rax=[rax+0x18], rdi=[rax] (the rcx==0 path from phase 2). At 0x66A9EEB: if rdi is zero, exit to 0x66AA235. Otherwise zero [rbp+0x418] (qword), [rbp+0x420] (dword), [rbp+0x392] and [rbp+0x398] (qwords), reload rdi=[r15] and rax=[rbp+0x3F8], zero [rbp+0x1B0] (xmm0), then rcx=[rax+8]; if rcx is nonzero, lock-inc the dword at [rcx+8]. rsi=[rbp+0x1B8]; copy 16 bytes [rax] into xmm0 and store at [rbp+0x1B0]. Release rsi: lock-dec dword [rsi+8], and if it reaches zero run the same two-step teardown via call qword ptr [0xF99FFA0] twice. Finally rax=[rax] is stored to [rbp+0x1B0] and [rbp+0x1B8] is cleared to 0. [V]

0x66a9edf  jmp short 0x66A9EEB
0x66a9ee1  mov rax,[rax]
0x66a9ee4  mov rax,[rax+0x18]
0x66a9ee8  mov rdi,[rax]
0x66a9eeb  test rdi,rdi
0x66a9eee  je 0x66AA235
0x66a9ef4  mov qword ptr [rbp+0x418],0
0x66a9eff  mov dword ptr [rbp+0x420],0
0x66a9f09  mov qword ptr [rbp+0x392],0
0x66a9f14  mov qword ptr [rbp+0x398],0
0x66a9f1f  mov rdi,[r15]
0x66a9f22  mov rax,[rbp+0x3F8]
0x66a9f29  xorps xmm0,xmm0
0x66a9f2c  movaps [rbp+0x1B0],xmm0
0x66a9f33  mov rcx,[rax+8]
0x66a9f37  test rcx,rcx
0x66a9f3a  je short 0x66A9F83
0x66a9f3c  lock inc dword ptr [rcx+8]
0x66a9f40  mov rsi,[rbp+0x1B8]
0x66a9f47  movups xmm0,[rax]
0x66a9f4a  movaps [rbp+0x1B0],xmm0
0x66a9f51  test rsi,rsi
0x66a9f54  je short 0x66A9F98
0x66a9f56  lock dec dword ptr [rsi+8]
0x66a9f5a  jne short 0x66A9F98
0x66a9f5c  mov rax,[rsi]
0x66a9f5f  mov rax,[rax]
0x66a9f62  mov rcx,rsi
0x66a9f65  call qword ptr [0xF99FFA0]
0x66a9f6b  lock dec dword ptr [rsi+0xC]
0x66a9f6f  jne short 0x66A9F98
0x66a9f71  mov rax,[rsi]
0x66a9f74  mov rax,[rax+8]
0x66a9f78  mov rcx,rsi
0x66a9f7b  call qword ptr [0xF99FFA0]
0x66a9f81  jmp short 0x66A9F98
0x66a9f83  mov rax,[rax]
0x66a9f86  mov [rbp+0x1B0],rax
0x66a9f8d  mov qword ptr [rbp+0x1B8],0

## Phase 4: 0x66a9f9f..0x66aa032 — 40 instructions
rax=[rbp+0x1B0]; follow [rax+0x18] then [rax] and save the result at [rbp-8]. lea rcx=[rbp], r8=[rdi], rdx=[rax+0x170], call 0xE86B370, nop, then store rdi at [rbp+0x78]. Release rsi=[rbp+0x1B8] again: lock-dec dword [rsi+8] with the same two-step indirect-call teardown via qword ptr [0xF99FFA0]. Then rsi=[rbx+0x48], call 0x4DEF080, nop, test al,al and exit to 0x66AA235 if zero; mov rcx,rsi, call 0x4DEF2B0, test al,al and exit to 0x66AA235 if zero. Finally compute eax=([rsi+0x60]-[rsi+0x58])>>2, imul eax,0xAAAAAAAB, and exit to 0x66AA05D if eax==0. [V]

0x66a9f98  mov rax,[rbp+0x1B0]
0x66a9f9f  mov rax,[rax+0x18]
0x66a9fa3  mov rax,[rax]
0x66a9fa6  mov [rbp-8],rax
0x66a9faa  lea rcx,[rbp]
0x66a9fae  mov r8,[rdi]
0x66a9fb1  mov rdx,[rax+0x170]
0x66a9fb8  call 0xE86B370
0x66a9fbd  nop
0x66a9fbe  mov [rbp+0x78],rdi
0x66a9fc2  mov rsi,[rbp+0x1B8]
0x66a9fc9  test rsi,rsi
0x66a9fcc  je short 0x66A9FF9
0x66a9fce  lock dec dword ptr [rsi+8]
0x66a9fd2  jne short 0x66A9FF9
0x66a9fd4  mov rax,[rsi]
0x66a9fd7  mov rax,[rax]
0x66a9fda  mov rcx,rsi
0x66a9fdd  call qword ptr [0xF99FFA0]
0x66a9fe3  lock dec dword ptr [rsi+0xC]
0x66a9fe7  jne short 0x66A9FF9
0x66a9fe9  mov rax,[rsi]
0x66a9fec  mov rax,[rax+8]
0x66a9ff0  mov rcx,rsi
0x66a9ff3  call qword ptr [0xF99FFA0]
0x66a9ff9  mov rsi,[rbx+0x48]
0x66a9ffd  mov rcx,rsi
0x66aa000  call 0x4DEF080
0x66aa005  nop
0x66aa006  test al,al
0x66aa008  je 0x66AA235
0x66aa00e  mov rcx,rsi
0x66aa011  call 0x4DEF2B0
0x66aa016  test al,al
0x66aa018  je 0x66AA235
0x66aa01e  mov rax,[rsi+0x60]
0x66aa022  sub rax,[rsi+0x58]
0x66aa026  shr rax,2
0x66aa02a  imul eax,0xAAAAAAAB
0x66aa030  test eax,eax
0x66aa032  je short 0x66AA05D

## Phase 5: 0x66aa034..0x66aa0f0 — 40 instructions
edx=0x250, then add rdx,[rbp-8]; lea rcx=[rbp+0x1B0], xor r8d,r8d, call 0xBBD7C70, nop. Then lea rdx=[rbp+0x1B0], mov rcx=rsi, call 0x4DEDD00, nop; lea rdx=[rbp+0x1B0], mov rcx=rsi, call 0x4DE9FA0, nop. Then rdx=[r15], lea rcx=[rbp+0x3A0], lea r8=[rbp+0x1B0], call 0x66A6190, nop. Then rsi=[rbp+0x550], lea rcx=[rbp+0x1B0], call 0x1751590. Finish by writing float 1.0 (immediate 0x3F800000) to dword [rbp+0x1B0] and dword [rbp+0x1C4], zeroing xmm6 and storing 16 bytes at [rbp+0x1B4] and [rbp+0x1C8]. Then vector math begins: xmm1=movsd [rsi] (8 bytes), xmm0=16-byte constant at 0xF0A4080, xmm2=xmm1*xmm0 (mulps), xmm3=shuffle(xmm2,0x55)+xmm2, xmm4=movss [rsi+8], xmm5=constant at 0xEF5EAAC *xmm4 (mulss), xmm7=xmm5+xmm3, xmm3-=xmm4. [V]

0x66aa034  mov edx,0x250
0x66aa039  add rdx,[rbp-8]
0x66aa03d  lea rcx,[rbp+0x1B0]
0x66aa044  xor r8d,r8d
0x66aa047  call 0xBBD7C70
0x66aa04c  nop
0x66aa04d  lea rdx,[rbp+0x1B0]
0x66aa054  mov rcx,rsi
0x66aa057  call 0x4DEDD00
0x66aa05c  nop
0x66aa05d  lea rdx,[rbp+0x1B0]
0x66aa064  mov rcx,rsi
0x66aa067  call 0x4DE9FA0
0x66aa06c  nop
0x66aa06d  mov rdx,[r15]
0x66aa070  lea rcx,[rbp+0x3A0]
0x66aa077  lea r8,[rbp+0x1B0]
0x66aa07e  call 0x66A6190
0x66aa083  nop
0x66aa084  mov rsi,[rbp+0x550]
0x66aa08b  lea rcx,[rbp+0x1B0]
0x66aa092  call 0x1751590
0x66aa097  mov dword ptr [rbp+0x1B0],0x3F800000
0x66aa0a1  xorps xmm6,xmm6
0x66aa0a4  movups [rbp+0x1B4],xmm6
0x66aa0ab  mov dword ptr [rbp+0x1C4],0x3F800000
0x66aa0b5  movups [rbp+0x1C8],xmm6
0x66aa0bc  movsd xmm1,[rsi]
0x66aa0c0  movaps xmm0,[0xF0A4080]
0x66aa0c7  movaps xmm2,xmm1
0x66aa0ca  mulps xmm2,xmm0
0x66aa0cd  movaps xmm3,xmm2
0x66aa0d0  shufps xmm3,xmm2,0x55
0x66aa0d4  addss xmm3,xmm2
0x66aa0d8  movss xmm4,[rsi+8]
0x66aa0dd  movss xmm5,[0xEF5EAAC]
0x66aa0e5  mulss xmm5,xmm4
0x66aa0e9  movaps xmm7,xmm5
0x66aa0ec  addss xmm7,xmm3
0x66aa0f0  subss xmm3,xmm4

## Phase 6: 0x66aa0f4..0x66aa1c7 — 40 instructions
Continue vector math: xmm2=shufps(xmm2,0xE1), xmm3=unpcklps(xmm3,xmm7), addps xmm3 with the 128-bit constant at 0xEFD32F0, subps xmm2,xmm1, unpcklps xmm5,xmm5, addps xmm5,xmm2, xmm0=movlhps(xmm0,xmm5), xmm7=movss constant at 0xEEC8060, addps xmm0,xmm7; store xmm0 (16 bytes) at [rbp+0x1D8] and the low 8 bytes of xmm3 at [rbp+0x1E8] (movlps). Then lea rcx=[rbp-0x48], lea r8=[rbp+0x1B0], mov rdx=r14, call 0xAA6580, nop. Finally: r13=[rbp], rdi=[rbx+0x10], rax=[rbx+0x18], store [rbp+0x1A8]=rax, lea r14=[rbp+0x1B4], xmm9=0, xmm10=16-byte constant at 0xF08EF60, xmm11=16-byte constant at 0xF0A9630, xmm12=movsd constant at 0xEFD32F0, lea rsi=[rbp+0xD0], [rbp+0x408]=r12, [rbp+0x410]=r15. If rdi != [rbp+0x1A8] jump to 0x66AA2EB. If byte [rbp+0x3D8]==3 and rsi=[rbp+0x3D0] is nonzero: lock-dec dword [rsi+8], and on reaching zero run the two-step teardown (mov rax,[rsi]; mov rax,[rax]; call qword ptr [0xF99FFA0]; lock-dec dword [rsi+0xC]; mov rax,[rsi]; mov rax,[rax+8]; call qword ptr [0xF99FFA0]). [V]

0x66aa0f4  shufps xmm2,xmm2,0xE1
0x66aa0f8  unpcklps xmm3,xmm7
0x66aa0fb  addps xmm3,[0xEFD32F0]
0x66aa102  subps xmm2,xmm1
0x66aa105  unpcklps xmm5,xmm5
0x66aa108  addps xmm5,xmm2
0x66aa10b  movlhps xmm0,xmm5
0x66aa10e  movss xmm7,[0xEEC8060]
0x66aa116  addps xmm0,xmm7
0x66aa119  movups [rbp+0x1D8],xmm0
0x66aa120  movlps [rbp+0x1E8],xmm3
0x66aa127  lea rcx,[rbp-0x48]
0x66aa12b  lea r8,[rbp+0x1B0]
0x66aa132  mov rdx,r14
0x66aa135  call 0xAA6580
0x66aa13a  nop
0x66aa13b  lea r13,[rbp]
0x66aa13f  mov rdi,[rbx+0x10]
0x66aa143  mov rax,[rbx+0x18]
0x66aa147  mov [rbp+0x1A8],rax
0x66aa14e  lea r14,[rbp+0x1B4]
0x66aa155  xorps xmm9,xmm9
0x66aa159  movaps xmm10,[0xF08EF60]
0x66aa161  movaps xmm11,[0xF0A9630]
0x66aa169  movsd xmm12,[0xEFD32F0]
0x66aa172  lea rsi,[rbp+0xD0]
0x66aa179  mov [rbp+0x408],r12
0x66aa180  mov [rbp+0x410],r15
0x66aa187  cmp rdi,[rbp+0x1A8]
0x66aa18e  jne 0x66AA2EB
0x66aa194  cmp byte ptr [rbp+0x3D8],3
0x66aa19b  jne short 0x66AA1D4
0x66aa19d  mov rsi,[rbp+0x3D0]
0x66aa1a4  test rsi,rsi
0x66aa1a7  je short 0x66AA1D4
0x66aa1a9  lock dec dword ptr [rsi+8]
0x66aa1ad  jne short 0x66AA1D4
0x66aa1af  mov rax,[rsi]
0x66aa1b2  mov rax,[rax]
0x66aa1b5  mov rcx,rsi
0x66aa1b8  call qword ptr [0xF99FFA0]
0x66aa1be  lock dec dword ptr [rsi+0xC]
0x66aa1c2  jne short 0x66AA1D4
0x66aa1c4  mov rax,[rsi]
0x66aa1c7  mov rax,[rax+8]

## Phase 7: 0x66aa1cb..0x66aa1de — 5 instructions
Complete the release: mov rcx,rsi, call qword ptr [0xF99FFA0]. Then load rdi=[rbp+0x3A8], test rdi,rdi, and if zero exit to 0x66AA235 — the slice ends here on the conditional branch. [V]

0x66aa1cb  mov rcx,rsi
0x66aa1ce  call qword ptr [0xF99FFA0]
0x66aa1d4  mov rdi,[rbp+0x3A8]
0x66aa1db  test rdi,rdi
0x66aa1de  je short 0x66AA235

## Field map: every [reg+off] store/load in the slice
One row per distinct offset/address form; all sites listed with verbatim lines. Size from the instruction (movups/movaps 16, qword 8, dword/movss 4, byte 1, plain 64-bit mov 8). Direction: W = store, R = load, R/W = locked read-modify-write. Meaning is '-' everywhere: no instruction or string in this slice documents field semantics.

| offset | size | direction | verbatim `0xRVA  instr` line(s) | meaning |
|--------|------|-----------|---------------------------------|---------|
| 0x0 ([reg+0]) | 8B | R | 0x66a9e52  mov rsi,[rax] 0x66a9ea1  mov rcx,[rax] 0x66a9eac  mov rdi,[rax] 0x66a9eba  mov rax,[rsi] 0x66a9ebd  mov rax,[rax] 0x66a9ecf  mov rax,[rsi] 0x66a9ee1  mov rax,[rax] 0x66a9ee8  mov rdi,[rax] 0x66a9f5c  mov rax,[rsi] 0x66a9f5f  mov rax,[rax] 0x66a9f71  mov rax,[rsi] 0x66a9f83  mov rax,[rax] 0x66a9fa3  mov rax,[rax] 0x66a9fd4  mov rax,[rsi] 0x66a9fd7  mov rax,[rax] 0x66a9fe9  mov rax,[rsi] 0x66aa0bc  movsd xmm1,[rsi] 0x66aa1af  mov rax,[rsi] 0x66aa1b2  mov rax,[rax] 0x66aa1c4  mov rax,[rsi] | - |
| 0x4 ([rcx+4]) | 4B | R | 0x66a9de9  cmp eax,[rcx+4] 0x66a9e77  cmp eax,[rcx+4] | - |
| 0x8 ([reg+8]) | 4B/8B | R/R/W | 0x66a9e94  mov rcx,[rax+8] 0x66a9ea4  mov rsi,[rax+8] 0x66a9e9d  lock inc dword ptr [rcx+8] 0x66a9eb4  lock dec dword ptr [rsi+8] 0x66a9ed2  mov rax,[rax+8] 0x66a9f33  mov rcx,[rax+8] 0x66a9f3c  lock inc dword ptr [rcx+8] 0x66a9f56  lock dec dword ptr [rsi+8] 0x66a9f74  mov rax,[rax+8] 0x66a9fce  lock dec dword ptr [rsi+8] 0x66a9fec  mov rax,[rax+8] 0x66aa0d8  movss xmm4,[rsi+8] 0x66aa1c7  mov rax,[rax+8] | - |
| 0xC ([rsi+0xC]) | 4B | R/W | 0x66a9ec9  lock dec dword ptr [rsi+0xC] 0x66a9f6b  lock dec dword ptr [rsi+0xC] 0x66a9fe3  lock dec dword ptr [rsi+0xC] 0x66aa1be  lock dec dword ptr [rsi+0xC] | - |
| 0x10 ([rsi+0x10]) | 1B | R | 0x66a9e83  cmp byte ptr [rsi+0x10],1 | - |
| 0x18 ([reg+0x18]) | 8B | R | 0x66a9ea8  mov rax,[rcx+0x18] 0x66a9ee4  mov rax,[rax+0x18] 0x66a9f9f  mov rax,[rax+0x18] | - |
| 0x40 ([r15+0x40]) | 8B | R | 0x66a9df5  mov r9,[r15+0x40] | - |
| 0x48 ([rbx+0x48]) | 8B | R | 0x66a9ff9  mov rsi,[rbx+0x48] | - |
| 0x58 ([rsi+0x58]) | 8B | R | 0x66aa022  sub rax,[rsi+0x58] | - |
| 0x60 ([rsi+0x60]) | 8B | R | 0x66aa01e  mov rax,[rsi+0x60] | - |
| 0x68 ([r15+0x68]) | 8B | R | 0x66a9df9  mov rcx,[r15+0x68] | - |
| 0x170 ([rax+0x170]) | 8B | R | 0x66a9fb1  mov rdx,[rax+0x170] | - |
| rbp-0x8 | 8B | W/R | 0x66a9fa6  mov [rbp-8],rax 0x66aa039  add rdx,[rbp-8] | - |
| rsp+0x20 | 8B | W | 0x66a9e33  mov [rsp+0x20],rax | - |
| rsp+0x28 | 8B | W | 0x66a9e27  mov [rsp+0x28],rax | - |
| gs+0x58 | 8B | R | 0x66a9ddc  mov rdx,gs:[0x58] | - |
| rdx+rcx*8 | 8B | R | 0x66a9de5  mov rcx,[rdx+rcx*8] | - |
| rbp+0xD0 | 8B | W | 0x66a9e0e  mov [rbp+0xD0],rax | - |
| rbp+0xD8 | 8B | W | 0x66a9e15  mov qword ptr [rbp+0xD8],0xE | - |
| rbp+0x1A8 | 8B | W/R | 0x66aa147  mov [rbp+0x1A8],rax 0x66aa187  cmp rdi,[rbp+0x1A8] | - |
| rbp+0x1B0 | 16B/8B | W/R | 0x66a9e00  movaps [rbp+0x1B0],xmm0 0x66a9f2c  movaps [rbp+0x1B0],xmm0 0x66a9f86  mov [rbp+0x1B0],rax 0x66a9f98  mov rax,[rbp+0x1B0] | - |
| rbp+0x1B4 | 16B | W | 0x66aa0a4  movups [rbp+0x1B4],xmm6 | - |
| rbp+0x1B8 | 8B | W/R | 0x66a9f40  mov rsi,[rbp+0x1B8] 0x66a9f8d  mov qword ptr [rbp+0x1B8],0 0x66a9fc2  mov rsi,[rbp+0x1B8] | - |
| rbp+0x1C4 | 4B | W | 0x66aa0ab  mov dword ptr [rbp+0x1C4],0x3F800000 | - |
| rbp+0x1C8 | 16B | W | 0x66aa0b5  movups [rbp+0x1C8],xmm6 | - |
| rbp+0x1D8 | 16B | W | 0x66aa119  movups [rbp+0x1D8],xmm0 | - |
| rbp+0x1E8 | 8B | W | 0x66aa120  movlps [rbp+0x1E8],xmm3 | - |
| rbp+0x392 | 8B | W | 0x66a9f09  mov qword ptr [rbp+0x392],0 | - |
| rbp+0x398 | 8B | W | 0x66a9f14  mov qword ptr [rbp+0x398],0 | - |
| rbp+0x3A8 | 8B | R | 0x66aa1d4  mov rdi,[rbp+0x3A8] | - |
| rbp+0x3D0 | 8B | R | 0x66aa19d  mov rsi,[rbp+0x3D0] | - |
| rbp+0x3D8 | 1B | R | 0x66aa194  cmp byte ptr [rbp+0x3D8],3 | - |
| rbp+0x3F8 | 8B | R | 0x66a9e4b  mov rax,[rbp+0x3F8] 0x66a9e8d  mov rax,[rbp+0x3F8] 0x66a9f22  mov rax,[rbp+0x3F8] | - |
| rbp+0x408 | 8B | W | 0x66aa179  mov [rbp+0x408],r12 | - |
| rbp+0x410 | 8B | W | 0x66aa180  mov [rbp+0x410],r15 | - |
| rbp+0x418 | 8B | W | 0x66a9ef4  mov qword ptr [rbp+0x418],0 | - |
| rbp+0x420 | 4B | W | 0x66a9eff  mov dword ptr [rbp+0x420],0 | - |
| rbp+0x438 | 8B | W | 0x66a9db9  mov qword ptr [rbp+0x438],0xFFFFFFFFFFFFFFFE | - |
| rbp+0x440 | 16B | W | 0x66a9db2  movaps [rbp+0x440],xmm6 | - |
| rbp+0x450 | 16B | W | 0x66a9dab  movaps [rbp+0x450],xmm7 | - |
| rbp+0x460 | 16B | W | 0x66a9da3  movaps [rbp+0x460],xmm8 | - |
| rbp+0x470 | 16B | W | 0x66a9d9b  movaps [rbp+0x470],xmm9 | - |
| rbp+0x480 | 16B | W | 0x66a9d93  movaps [rbp+0x480],xmm10 | - |
| rbp+0x490 | 16B | W | 0x66a9d8b  movaps [rbp+0x490],xmm11 | - |
| rbp+0x4A0 | 16B | W | 0x66a9d83  movaps [rbp+0x4A0],xmm12 | - |
| rbp+0x4B0 | 16B | W | 0x66a9d7b  movaps [rbp+0x4B0],xmm13 | - |
| rbp+0x4C0 | 16B | W | 0x66a9d73  movaps [rbp+0x4C0],xmm14 | - |
| rbp+0x4D0 | 16B | W | 0x66a9d6b  movaps [rbp+0x4D0],xmm15 | - |
| rbx+0x10 | 8B | R | 0x66aa13f  mov rdi,[rbx+0x10] | - |
| rbx+0x18 | 8B | R | 0x66aa143  mov rax,[rbx+0x18] | - |
| rbp+0x550 | 8B | R | 0x66aa084  mov rsi,[rbp+0x550] | - |

Notes: lea rcx,[rbp+0x3A0] / lea rax,[rbp+0x1B0] / lea rdx,[rbp+0x1B0] / lea rax,[rbp+0xD0] / lea rax,[0xF56F38F] / lea r8,[...] compute addresses but do not load or store. Absolute-address loads (movaps xmm0,[0xF0A4080]; movss xmm5,[0xEF5EAAC]; addps xmm3,[0xEFD32F0]; movss xmm7,[0xEEC8060]; movaps xmm10,[0xF08EF60]; movaps xmm11,[0xF0A9630]; movsd xmm12,[0xEFD32F0]) are not [reg+off] fields and are excluded from this map. No string in the slice names any field; every meaning is '-'. 

