## NEXT
DONE

# UNIT U-Sx5 — effect_shadow_extractor slice 0x66ab0df..0x66ab560 (shadow extractor 0x66a9d50, chunk 5 of 6)

Source: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01); RVAs relative to image base.
Input listing: docs/progress/_part_Sx5.txt — 250 instructions, 0x66ab0df..0x66ab560; every instruction below is copied verbatim from that listing.
Tags: [V] = seen in the disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.

Entry register map (observed in this slice) [V]:
- rdx = target shadow/output struct: stores at +0x18..+0x24 (singles) and +0x28/+0x38/+0x47 (16-byte blocks).
- r14 = source struct: 16-byte loads at +0x28/+0x38/+0x47.
- rbx = heap object: size counters [rbx+0x750]/[rbx+0x758]; growable buffer cursors/limits [rbx+0x228]/[rbx+0x230]/[rbx+0x238] and [rbx+0x240]/[rbx+0x248]/[rbx+0x250].
- rbp = stack frame: floats [rbp+0x1D0..0x1D8], flag byte [rbp+0x437], saved pointer [rbp+0x428], saved registers [rbp+0x408]/[rbp+0x410], scratch [rbp+0x16A]/[rbp+0xD0]/[rbp+0xD8], loop state [rbp+0x340]/[rbp+0x350]/[rbp+0x380]/[rbp+0x1A8].
- rax/rcx/rdx/r8/r9/xmm0-xmm2 = scratch. Global interface pointers [0x1233E1A8] (allocator) and [0x1233E1B0] (virtual calls) are absolute loads, not [reg+off], so they are excluded from the field table.

## Phases — every instruction of the slice is covered verbatim; each phase covers at most 40 instructions

### Phase 1: 0x66ab0df..0x66ab1a4 (40 instructions)
Serialize a shadow block through rdx: singles [rbp+0x1D0/0x1D4/0x1D8] -> [rdx+0x18/0x1C/0x20/0x24], then 16-byte blocks [r14+0x28/0x38/0x47] -> [rdx+0x28/0x38/0x47]; bump [rbx+0x758] by 0x58 and jump to 0x66ab143. Not-taken path at 0x66ab130: rcx=rbx+0x750, r8=r14, call 0x6760A80. At 0x66ab143: virtual call through global interface [0x1233E1B0]->[rax+0x10] with flag byte [rbp+0x437]; scratch slot [rbp+0xD0] tagged with immediate 0x2007009; (cur-base)>>3 * 0xFFFF8BA3 - 1 stored as a word at [rbp+0xFC]; second virtual call with dl=0x4A, result flag stored at [rbp+0x437].
0x66ab0df  movss [rdx+0x18],xmm0
0x66ab0e4  movss xmm0,[rbp+0x1D0]
0x66ab0ec  movss [rdx+0x1C],xmm0
0x66ab0f1  movss xmm0,[rbp+0x1D4]
0x66ab0f9  movss [rdx+0x20],xmm0
0x66ab0fe  movss xmm0,[rbp+0x1D8]
0x66ab106  movss [rdx+0x24],xmm0
0x66ab10b  movups xmm0,[r14+0x28]
0x66ab110  movups xmm1,[r14+0x38]
0x66ab115  movups xmm2,[r14+0x47]
0x66ab11a  movups [rdx+0x28],xmm0
0x66ab11e  movups [rdx+0x38],xmm1
0x66ab122  movups [rdx+0x47],xmm2
0x66ab126  add qword ptr [rbx+0x758],0x58
0x66ab12e  jmp short 0x66AB143
0x66ab130  mov rcx,rbx
0x66ab133  add rcx,0x750
0x66ab13a  mov r8,r14
0x66ab13d  call 0x6760A80
0x66ab142  nop
0x66ab143  mov rcx,[0x1233E1B0]
0x66ab14a  mov rax,[rcx]
0x66ab14d  mov rax,[rax+0x10]
0x66ab151  movzx edx,byte ptr [rbp+0x437]
0x66ab158  call qword ptr [0xF99FFA0]
0x66ab15e  nop
0x66ab15f  mov qword ptr [rbp+0xD0],0x2007009
0x66ab16a  mov eax,[rbx+0x758]
0x66ab170  sub eax,[rbx+0x750]
0x66ab176  shr eax,3
0x66ab179  imul eax,0xFFFF8BA3
0x66ab17f  dec eax
0x66ab181  mov [rbp+0xFC],ax
0x66ab188  mov rcx,[0x1233E1B0]
0x66ab18f  mov rax,[rcx]
0x66ab192  mov rax,[rax+0x10]
0x66ab196  mov dl,0x4A
0x66ab198  call qword ptr [0xF99FFA0]
0x66ab19e  mov [rbp+0x437],al

### Phase 2: 0x66ab1ab..0x66ab250 (40 instructions)
Buffer cursor check on rbx: rsi=[rbx+0x248] vs limit [rbx+0x250]; if equal, [rbp+0x428]=rdi and need=rdi-[rbx+0x240] is grown by the rdi+(rdi>>1) sequence clamped below 0x7FFFFFFFFFFFFFFF and floored at rdi+1; size r15+0x27 is allocated from the global allocator [0x1233E1A8]->[rax+8] (result r12, then r12+=0x27). If allocation fails jump 0x66ab661; if the cursor already matches the limit jump 0x66ab4b4 (alignment and header store continue in Phase 3).
0x66ab1ab  cmp rsi,[rbx+0x250]
0x66ab1b2  je short 0x66AB1C3
0x66ab1b4  inc rsi
0x66ab1b7  mov [rbx+0x248],rsi
0x66ab1be  jmp 0x66AB544
0x66ab1c3  mov [rbp+0x428],rdi
0x66ab1ca  mov rdi,rsi
0x66ab1cd  sub rdi,[rbx+0x240]
0x66ab1d4  mov r15,0x7FFFFFFFFFFFFFFF
0x66ab1de  cmp rdi,r15
0x66ab1e1  je 0x66AB734
0x66ab1e7  lea r14,[rdi+1]
0x66ab1eb  mov rax,rdi
0x66ab1ee  shr rax,1
0x66ab1f1  mov rcx,rax
0x66ab1f4  xor rcx,r15
0x66ab1f7  add rax,rdi
0x66ab1fa  cmp rax,r14
0x66ab1fd  cmovbe rax,r14
0x66ab201  cmp rdi,rcx
0x66ab204  ja short 0x66AB209
0x66ab206  mov r15,rax
0x66ab209  test r15,r15
0x66ab20c  je 0x66AB4A4
0x66ab212  cmp r15,0x1000
0x66ab219  jb short 0x66AB26B
0x66ab21b  cmp r15,0xFFFFFFFFFFFFFFD9
0x66ab21f  jae 0x66AB740
0x66ab225  lea r13,[r15+0x27]
0x66ab229  mov rcx,[0x1233E1A8]
0x66ab230  mov rax,[rcx]
0x66ab233  mov rax,[rax+8]
0x66ab237  mov rdx,r13
0x66ab23a  call qword ptr [0xF99FFA0]
0x66ab240  nop
0x66ab241  mov r12,rax
0x66ab244  test rax,rax
0x66ab247  je 0x66AB661
0x66ab24d  mov rax,r12
0x66ab250  add r12,0x27

### Phase 3: 0x66ab254..0x66ab2fb (40 instructions)
Align r12 down to 32 bytes and store the original allocation size as a header at [r12-8]; if cursor==[rbx+0x248] jump to 0x66ab4b4 (buffer-reuse join). Small-allocation variant: same global allocator with size r15, failure jump 0x66ab49B. Copy path: source r12+rdi (+1), length rsi-[rbx+0x240], call 0xEEC6DE0, jump 0x66ab4C4. On failure path 0x66ab2cd: call 0x9BC830 (rcx=r15), zero r12d; if rdi==[rbx+0x230] jump out to 0x66AAD60; else rdi-=[rbx+0x228], call 0xEEC6DE0 again, reload flag byte [rbp+0x437] into esi.
0x66ab254  and r12,0xFFFFFFFFFFFFFFE0
0x66ab258  mov [r12-8],rax
0x66ab25d  cmp rsi,[rbx+0x248]
0x66ab264  jne short 0x66AB29C
0x66ab266  jmp 0x66AB4B4
0x66ab26b  mov rcx,[0x1233E1A8]
0x66ab272  mov rax,[rcx]
0x66ab275  mov rax,[rax+8]
0x66ab279  mov rdx,r15
0x66ab27c  call qword ptr [0xF99FFA0]
0x66ab282  nop
0x66ab283  mov r12,rax
0x66ab286  test rax,rax
0x66ab289  je 0x66AB49B
0x66ab28f  cmp rsi,[rbx+0x248]
0x66ab296  je 0x66AB4B4
0x66ab29c  lea r13,[r12+rdi]
0x66ab2a0  inc r13
0x66ab2a3  mov rdx,[rbx+0x240]
0x66ab2aa  mov r8,rsi
0x66ab2ad  sub r8,rdx
0x66ab2b0  mov rcx,r12
0x66ab2b3  call 0xEEC6DE0
0x66ab2b8  mov r8,[rbx+0x248]
0x66ab2bf  sub r8,rsi
0x66ab2c2  mov rcx,r13
0x66ab2c5  mov rdx,rsi
0x66ab2c8  jmp 0x66AB4C4
0x66ab2cd  mov rcx,r15
0x66ab2d0  call 0x9BC830
0x66ab2d5  nop
0x66ab2d6  xor r12d,r12d
0x66ab2d9  cmp rdi,[rbx+0x230]
0x66ab2e0  jne 0x66AAD60
0x66ab2e6  mov rdx,[rbx+0x228]
0x66ab2ed  sub rdi,rdx
0x66ab2f0  mov rcx,r12
0x66ab2f3  mov r8,rdi
0x66ab2f6  call 0xEEC6DE0
0x66ab2fb  movzx esi,byte ptr [rbp+0x437]

### Phase 4: 0x66ab302..0x66ab3c1 (40 instructions)
Commit/free the old buffer: rcx=[rbx+0x228]; if non-null, available=[rbx+0x238]-rcx; when >=0x1000, validate the guard via [rcx-8] and free through 0xE935700, else free with size+0x27 (rcx=previous rax); otherwise call 0xE935700 directly. Then [rbx+0x228]=0; [rbx+0x230]=[rbp+0x428]+r12; [rbx+0x238]=r15+r12; restore r12=[rbp+0x408], r15=[rbp+0x410]; virtual call [0x1233E1B0]->[rax+0x10] with edx=[rbp+0x437] flag byte.
0x66ab302  mov rcx,[rbx+0x228]
0x66ab309  test rcx,rcx
0x66ab30c  mov rdi,r14
0x66ab30f  je short 0x66AB345
0x66ab311  mov rdx,[rbx+0x238]
0x66ab318  sub rdx,rcx
0x66ab31b  cmp rdx,0x1000
0x66ab322  jb short 0x66AB340
0x66ab324  mov rax,[rcx-8]
0x66ab328  add rcx,0xFFFFFFFFFFFFFFF8
0x66ab32c  sub rcx,rax
0x66ab32f  cmp rcx,0x20
0x66ab333  jae 0x66AB71A
0x66ab339  add rdx,0x27
0x66ab33d  mov rcx,rax
0x66ab340  call 0xE935700
0x66ab345  mov [rbx+0x228],r12
0x66ab34c  mov rax,[rbp+0x428]
0x66ab353  add rax,r12
0x66ab356  mov [rbx+0x230],rax
0x66ab35d  add r15,r12
0x66ab360  mov [rbx+0x238],r15
0x66ab367  mov r12,[rbp+0x408]
0x66ab36e  mov r15,[rbp+0x410]
0x66ab375  lea r13,[rbp]
0x66ab379  mov rcx,[0x1233E1B0]
0x66ab380  mov rax,[rcx]
0x66ab383  mov rax,[rax+0x10]
0x66ab387  mov edx,esi
0x66ab389  call qword ptr [0xF99FFA0]
0x66ab38f  nop

### Phase 4b: 0x66ab390..0x66ab3c1 (9 instructions)
Re-point scratch stack slot r14=[rbp+0x1B4], tag scratch size [rbp+0xD8]=0x20; compute word ~[rbx+0x228]+[rbx+0x230] via not/add; reload the global interface pointer [0x1233E1B0] and its vtable function [rax+0x10] for the next virtual call.
0x66ab390  lea r14,[rbp+0x1B4]
0x66ab397  mov qword ptr [rbp+0xD8],0x20
0x66ab3a2  mov eax,[rbx+0x228]
0x66ab3a8  not eax
0x66ab3aa  add eax,[rbx+0x230]
0x66ab3b0  mov [rbp+0x16A],ax
0x66ab3b7  mov rcx,[0x1233E1B0]
0x66ab3be  mov rax,[rcx]
0x66ab3c1  mov rax,[rax+0x10]

### Phase 5: 0x66ab3c5..0x66ab473 (40 instructions)
Store flag result [rbp+0x437]=al; scratch [rbp+0xD8]=0x20; word ~[rbx+0x228]+[rbx+0x230] -> [rbp+0x16A]; second virtual call [0x1233E1B0]->[rax+0x10] with dl=0x4A, result flag stored at [rbp+0x437]. If [rbx+8] != [rbx+0x10]: copy 0xC8 bytes from [rbx+8] to stack [rbp+0xD0] via 0xEEC6EC0, then [rbx+8]+=0xC8; else call 0x5ABA6D0(rbx, &[rbp+0xD0]). Third virtual call with flag byte; call 0x66A9AD0(&[rbp+0x1B0]); if byte [rbp+0x380]==1 and [rbp+0x340] non-null, check room [rbp+0x350]-[rbp+0x340] >= 0x1000, guard-check [rcx-8] and free via 0xE935700 (else size|0x27).
0x66ab3c5  mov dl,0x4A
0x66ab3c7  call qword ptr [0xF99FFA0]
0x66ab3cd  nop
0x66ab3ce  mov [rbp+0x437],al
0x66ab3d4  mov rdx,[rbx+8]
0x66ab3d8  cmp rdx,[rbx+0x10]
0x66ab3dc  je short 0x66AB3FD
0x66ab3de  mov r8d,0xC8
0x66ab3e4  mov rcx,rdx
0x66ab3e7  lea rdx,[rbp+0xD0]
0x66ab3ee  call 0xEEC6EC0
0x66ab3f3  add qword ptr [rbx+8],0xC8
0x66ab3fb  jmp short 0x66AB40D
0x66ab3fd  mov rcx,rbx
0x66ab400  lea r8,[rbp+0xD0]
0x66ab407  call 0x5ABA6D0
0x66ab40c  nop
0x66ab40d  mov rcx,[0x1233E1B0]
0x66ab414  mov rax,[rcx]
0x66ab417  mov rax,[rax+0x10]
0x66ab41b  movzx edx,byte ptr [rbp+0x437]
0x66ab422  call qword ptr [0xF99FFA0]
0x66ab428  nop
0x66ab429  lea rcx,[rbp+0x1B0]
0x66ab430  call 0x66A9AD0
0x66ab435  cmp byte ptr [rbp+0x380],1
0x66ab43c  lea rsi,[rbp+0xD0]
0x66ab443  jne short 0x66AB485
0x66ab445  mov rcx,[rbp+0x340]
0x66ab44c  test rcx,rcx
0x66ab44f  je short 0x66AB485
0x66ab451  mov rdx,[rbp+0x350]
0x66ab458  sub rdx,rcx
0x66ab45b  cmp rdx,0x1000
0x66ab462  jb short 0x66AB480
0x66ab464  mov rax,[rcx-8]
0x66ab468  add rcx,0xFFFFFFFFFFFFFFF8
0x66ab46c  sub rcx,rax
0x66ab46f  cmp rcx,0x20
0x66ab473  jae 0x66AB71A

### Phase 6: 0x66ab479..0x66ab508 (33 instructions)
Guard-check free completion: or rdx,0x27; mov rcx,rax; call 0xE935700. Loop: rdi+=0x14; cmp rdi,[rbp+0x1A8]; if not equal jump 0x66AA2EB, else jump 0x66AA194. Allocation-failure path 0x66ab49b: call 0x9BC830 (rcx=r15); xor r12d,r12d; if rsi!=[rbx+0x248] jump to copy path 0x66ab29c. Rejoin copy: rdx=[rbx+0x240]; rsi-=rdx; rcx=r12; r8=rsi; call 0xEEC6DE0. Commit path: rdi=[rbp+0x428]; rcx=[rbx+0x240]; if rcx==0 jump 0x66ab510; else rdx=[rbx+0x250]; rdx-=rcx; if <0x1000 jump 0x66ab50B; else guard-check [rcx-8], size vs 0x20, then add rdx,0x27; mov rcx,rax; call 0xE935700.
0x66ab479  or rdx,0x27
0x66ab47d  mov rcx,rax
0x66ab480  call 0xE935700
0x66ab485  add rdi,0x14
0x66ab489  cmp rdi,[rbp+0x1A8]
0x66ab490  jne 0x66AA2EB
0x66ab496  jmp 0x66AA194
0x66ab49b  mov rcx,r15
0x66ab49e  call 0x9BC830
0x66ab4a3  nop
0x66ab4a4  xor r12d,r12d
0x66ab4a7  cmp rsi,[rbx+0x248]
0x66ab4ae  jne 0x66AB29C
0x66ab4b4  mov rdx,[rbx+0x240]
0x66ab4bb  sub rsi,rdx
0x66ab4be  mov rcx,r12
0x66ab4c1  mov r8,rsi
0x66ab4c4  call 0xEEC6DE0
0x66ab4c9  mov rdi,[rbp+0x428]
0x66ab4d0  mov rcx,[rbx+0x240]
0x66ab4d7  test rcx,rcx
0x66ab4da  je short 0x66AB510
0x66ab4dc  mov rdx,[rbx+0x250]
0x66ab4e3  sub rdx,rcx
0x66ab4e6  cmp rdx,0x1000
0x66ab4ed  jb short 0x66AB50B
0x66ab4ef  mov rax,[rcx-8]
0x66ab4f3  add rcx,0xFFFFFFFFFFFFFFF8
0x66ab4f7  sub rcx,rax
0x66ab4fa  cmp rcx,0x20
0x66ab4fe  jae 0x66AB71A
0x66ab504  add rdx,0x27
0x66ab508  mov rcx,rax

### Phase 7: 0x66ab50b..0x66ab560 (17 instructions)
Finish commit/free: call 0xE935700; then [rbx+0x240]=r12 (reset base); r14+=r12; [rbx+0x248]=r14 (advance cursor); r15+=r12; [rbx+0x250]=r15 (advance limit); restore r12=[rbp+0x408], r15=[rbp+0x410]; lea r13,[rbp]; lea r14,[rbp+0x1B4]; virtual call [0x1233E1B0]->[rax+0x10] with flag byte [rbp+0x437]; scratch [rbp+0xD8]=0x10.
0x66ab50b  call 0xE935700
0x66ab510  mov [rbx+0x240],r12
0x66ab517  add r14,r12
0x66ab51a  mov [rbx+0x248],r14
0x66ab521  add r15,r12
0x66ab524  mov [rbx+0x250],r15
0x66ab52b  mov r12,[rbp+0x408]
0x66ab532  mov r15,[rbp+0x410]
0x66ab539  lea r13,[rbp]
0x66ab53d  lea r14,[rbp+0x1B4]
0x66ab544  mov rcx,[0x1233E1B0]
0x66ab54b  mov rax,[rcx]
0x66ab54e  mov rax,[rax+0x10]
0x66ab552  movzx edx,byte ptr [rbp+0x437]
0x66ab559  call qword ptr [0xF99FFA0]
0x66ab55f  nop
0x66ab560  mov qword ptr [rbp+0xD8],0x10

## Field table — every [reg+off] field stored or loaded, one row per distinct offset, all sites listed

| offset | size | direction | verbatim `0xRVA  instr` sites | meaning |
|---|---|---|---|---|
| rdx+0x18 | 4 | W | 0x66ab0df  movss [rdx+0x18],xmm0 | Shadow X component [I] |
| rdx+0x1C | 4 | W | 0x66ab0ec  movss [rdx+0x1C],xmm0 | Shadow Y component [I] |
| rdx+0x20 | 4 | W | 0x66ab0f9  movss [rdx+0x20],xmm0 | Shadow Z component [I] |
| rdx+0x24 | 4 | W | 0x66ab106  movss [rdx+0x24],xmm0 | Shadow W component [I] |
| rdx+0x28 | 16 | W | 0x66ab11a  movups [rdx+0x28],xmm0 | Shadow block 1 [I] |
| rdx+0x38 | 16 | W | 0x66ab11e  movups [rdx+0x38],xmm1 | Shadow block 2 [I] |
| rdx+0x47 | 16 | W | 0x66ab122  movups [rdx+0x47],xmm2 | Shadow block 3 [I] |
| r14+0x28 | 16 | R | 0x66ab10b  movups xmm0,[r14+0x28] | Source block 1 [I] |
| r14+0x38 | 16 | R | 0x66ab110  movups xmm1,[r14+0x38] | Source block 2 [I] |
| r14+0x47 | 16 | R | 0x66ab115  movups xmm2,[r14+0x47] | Source block 3 [I] |
| rbx+0x758 | 8 | RW | 0x66ab126  add qword ptr [rbx+0x758],0x58, 0x66ab16a  mov eax,[rbx+0x758] | Serialized byte counter [I] |
| rbx+0x750 | 4 | R | 0x66ab170  sub eax,[rbx+0x750] | Allocation base [I] |
| rbx+0x248 | 8 | RW | 0x66ab1a4  mov rsi,[rbx+0x248], 0x66ab1b7  mov [rbx+0x248],rsi, 0x66ab25d  cmp rsi,[rbx+0x248], 0x66ab28f  cmp rsi,[rbx+0x248], 0x66ab2b8  mov r8,[rbx+0x248], 0x66ab4a7  cmp rsi,[rbx+0x248], 0x66ab51a  mov [rbx+0x248],r14 | Write cursor [I] |
| rbx+0x250 | 8 | RW | 0x66ab1ab  cmp rsi,[rbx+0x250], 0x66ab524  mov [rbx+0x250],r15 | Write limit [I] |
| rbx+0x240 | 8 | RW | 0x66ab1cd  sub rdi,[rbx+0x240], 0x66ab2a3  mov rdx,[rbx+0x240], 0x66ab4b4  mov rdx,[rbx+0x240], 0x66ab4d0  mov rcx,[rbx+0x240], 0x66ab510  mov [rbx+0x240],r12 | Buffer base [I] |
| rbx+0x230 | 8 | RW | 0x66ab2d9  cmp rdi,[rbx+0x230], 0x66ab356  mov [rbx+0x230],rax | Commit cursor [I] |
| rbx+0x238 | 8 | RW | 0x66ab311  mov rdx,[rbx+0x238], 0x66ab360  mov [rbx+0x238],r15 | Commit limit [I] |
| rbx+0x228 | 8 | RW | 0x66ab2e6  mov rdx,[rbx+0x228], 0x66ab302  mov rcx,[rbx+0x228], 0x66ab345  mov [rbx+0x228],r12 | Old/current buffer pointer [I] |
| rbx+8 | 8 | RW | 0x66ab3d4  mov rdx,[rbx+8], 0x66ab3f3  add qword ptr [rbx+8],0xC8 | Secondary buffer cursor [I] |
| rbx+0x10 | 8 | R | 0x66ab3d8  cmp rdx,[rbx+0x10] | Secondary buffer limit [I] |
| rbp+0x1D0 | 4 | R | 0x66ab0e4  movss xmm0,[rbp+0x1D0] | Float input [?] |
| rbp+0x1D4 | 4 | R | 0x66ab0f1  movss xmm0,[rbp+0x1D4] | Float input [?] |
| rbp+0x1D8 | 4 | R | 0x66ab0fe  movss xmm0,[rbp+0x1D8] | Float input [?] |
| rbp+0x437 | 1 | RW | 0x66ab151  movzx edx,byte ptr [rbp+0x437], 0x66ab19e  mov [rbp+0x437],al, 0x66ab2fb  movzx esi,byte ptr [rbp+0x437], 0x66ab3ce  mov [rbp+0x437],al, 0x66ab41b  movzx edx,byte ptr [rbp+0x437], 0x66ab552  movzx edx,byte ptr [rbp+0x437] | Flag byte [I] |
| rbp+0xD0 | 8 | W | 0x66ab15f  mov qword ptr [rbp+0xD0],0x2007009, 0x66ab3e7  lea rdx,[rbp+0xD0], 0x66ab43c  lea rsi,[rbp+0xD0] | Scratch slot / copy dest [I] |
| rbp+0xFC | 2 | W | 0x66ab181  mov [rbp+0xFC],ax | Word result [(cur-base)>>3 * 0xFFFF8BA3 - 1] [I] |
| rbp+0x428 | 8 | RW | 0x66ab1c3  mov [rbp+0x428],rdi, 0x66ab34c  mov rax,[rbp+0x428] | Saved pointer [I] |
| rbp+0x408 | 8 | R | 0x66ab367  mov r12,[rbp+0x408], 0x66ab52b  mov r12,[rbp+0x408] | Saved register [I] |
| rbp+0x410 | 8 | R | 0x66ab36e  mov r15,[rbp+0x410], 0x66ab532  mov r15,[rbp+0x410] | Saved register [I] |
| rbp+0x16A | 2 | W | 0x66ab3b0  mov [rbp+0x16A],ax | Word ~[rbx+0x228]+[rbx+0x230] [I] |
| rbp+0xD8 | 8 | W | 0x66ab397  mov qword ptr [rbp+0xD8],0x20, 0x66ab560  mov qword ptr [rbp+0xD8],0x10 | Scratch size tag [I] |
| rbp+0x340 | 8 | R | 0x66ab445  mov rcx,[rbp+0x340] | Loop/base pointer [I] |
| rbp+0x350 | 8 | R | 0x66ab451  mov rdx,[rbp+0x350] | Loop end pointer [I] |
| rbp+0x380 | 1 | R | 0x66ab435  cmp byte ptr [rbp+0x380],1 | Enable flag byte [I] |
| rbp+0x1A8 | 8 | R | 0x66ab489  cmp rdi,[rbp+0x1A8] | Loop end [I] |
| rbp+0x1B0 | 8 | R | 0x66ab429  lea rcx,[rbp+0x1B0] | Local object address [I] |
| rbp+0x1B4 | 8 | R | 0x66ab390  lea r14,[rbp+0x1B4], 0x66ab53d  lea r14,[rbp+0x1B4] | Local object address [I] |
| r12-8 | 8 | W | 0x66ab258  mov [r12-8],rax | Allocation header: original size [I] |
| rcx-8 | 8 | R | 0x66ab324  mov rax,[rcx-8], 0x66ab464  mov rax,[rcx-8], 0x66ab4ef  mov rax,[rcx-8] | Allocator header read [I] |
| rax+0x10 | 8 | R | 0x66ab14d  mov rax,[rax+0x10], 0x66ab192  mov rax,[rax+0x10], 0x66ab383  mov rax,[rax+0x10], 0x66ab417  mov rax,[rax+0x10], 0x66ab54e  mov rax,[rax+0x10] | Vtable function pointer [I] |
| rcx+0x0 | 8 | R | 0x66ab14a  mov rax,[rcx], 0x66ab18f  mov rax,[rcx], 0x66ab229  mov rax,[rcx], 0x66ab272  mov rax,[rcx], 0x66ab379  mov rax,[rcx], 0x66ab40d  mov rax,[rcx], 0x66ab544  mov rax,[rcx] | Interface vtable pointer [I] |

## TOOL REQUESTS
None.
