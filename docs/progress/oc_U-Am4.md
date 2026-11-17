## NEXT
DONE

# U-Am4 — atlas_meta_parse 0x4e1a0a0, chunk 4 of 7: listed slice 0x4e1ae52..0x4e1b30b

Input data: docs/progress/_part_Am4.txt — 250 listed instructions, first 0x4e1ae52, last 0x4e1b30b (`mov rax,[rbp+0x130]`; the slice ends mid-idiom, targets beyond 0x4e1b30b belong to later chunks). Orchestrator-computed; not regenerated here.

Every instruction below is quoted verbatim (two spaces after the address, copied from the input data), assigned to exactly one phase; each phase holds at most 40 instructions; no instruction is skipped and no ellipsis is used. Quoted lines were validated with tools/sigs/verify_oc.py against C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01); `python tools/delegate.py check docs/progress/oc_U-Am4.md` must exit 0.

Tags: [V] = seen in the listed disassembly (cite RVA). Meanings are stated ONLY when an instruction, immediate, or string in this slice shows them; otherwise '-'. Jump/call targets outside the slice (0x392920, 0x15B7F0, 0x282A8E0, 0x392920, 0xE935700, 0xE932EB0, 0xE943178, 0xE94319C, 0x3B2020, 0x58E370, 0xE933260, 0xDA490, 0x4E196B0, 0xE932F90, 0x9D6D0, 0xEEC6EC0, 0xEEC6DE0, 0xE9325C0, 0xE932460, 0xE932380, 0x746640, 0xE932500, and bail targets 0x4E1BFC5, 0x4E1B74D, 0x4E1B390, 0x4E1B312) are not part of this slice. String lea targets (0xF60B4F1, 0x128C1508, 0xF7F0B17, 0xF5FDA08, 0xF5572AD, 0xF52FE18, 0xF5636E5, 0xF5BCEE1) reference rodata not dumped here; contents not shown. Absolute globals: [0xF0FFAB0] (16-byte constant), [0x128C1568] (atomic qword), [0x128C1570] (object pointer gated by byte [rax]==1), [0x128C1578] (refcounted ctrl), [0x128C1580] (qword). Backward edges: 0x4e1b218 `jb 0x4E1B100` and 0x4e1b221 `jmp 0x4E1B100` target an instruction listed in phase 4, so the element loop spans phases 4-6.

## Phases

### Phase 1: 0x4e1ae52..0x4e1af2a — 36 instructions

Two call 0x392920 paths (rcx=[rbx+0x28] or rcx=[rbx+1]) return rax; the original pointer is stored at [rax-8] after rax is aligned up by 32 ((rax+0x27)&-0x20), i.e. a heap back-pointer stored 8 bytes before the aligned block [V 0x4e1ae52-0x4e1ae67]. rax/rdi/rbx are stored at [rbp+0x130/0x140/0x148], rdi is incremented, 0xEEC6EC0 is called with rcx=rax, rdx=rsi, r8=rdi, and rbx is reloaded from [rbp+0x2C8] [V 0x4e1ae77-0x4e1ae9d]. Three zeroed 16-byte buffers ([rbp+0x150], [rbp+0x170], [rbp+0x190]) are paired with qword fields (4,0xF), (0,0xF), (0,0xF) at +0x10/+0x8; the dword 'pat' (0x68746170) is written at [rbp+0x150]; the 16-byte constant from [0xF0FFAB0] goes to [rbp+0x1B0]; word 0x101 to [rbp+0x1C0]; byte 1 to [rbp+0x1C2]; then 0x282A8E0 is called with rcx=rbx, rdx=&[rbp+0x130] [V 0x4e1aea4-0x4e1af2a].

0x4e1ae52  lea rcx,[rbx+0x28]
0x4e1ae56  call 0x392920
0x4e1ae5b  nop
0x4e1ae5c  mov rcx,rax
0x4e1ae5f  add rax,0x27
0x4e1ae63  and rax,0xFFFFFFFFFFFFFFE0
0x4e1ae67  mov [rax-8],rcx
0x4e1ae6b  jmp short 0x4E1AE77
0x4e1ae6d  lea rcx,[rbx+1]
0x4e1ae71  call 0x392920
0x4e1ae76  nop
0x4e1ae77  mov [rbp+0x130],rax
0x4e1ae7e  mov [rbp+0x140],rdi
0x4e1ae85  mov [rbp+0x148],rbx
0x4e1ae8c  inc rdi
0x4e1ae8f  mov rcx,rax
0x4e1ae92  mov rdx,rsi
0x4e1ae95  mov r8,rdi
0x4e1ae98  call 0xEEC6EC0
0x4e1ae9d  mov rbx,[rbp+0x2C8]
0x4e1aea4  movaps [rbp+0x150],xmm6
0x4e1aeab  mov qword ptr [rbp+0x160],4
0x4e1aeb6  mov qword ptr [rbp+0x168],0xF
0x4e1aec1  mov dword ptr [rbp+0x150],0x68746170
0x4e1aecb  movaps [rbp+0x170],xmm6
0x4e1aed2  mov qword ptr [rbp+0x180],0
0x4e1aedd  mov qword ptr [rbp+0x188],0xF
0x4e1aee8  movaps [rbp+0x190],xmm6
0x4e1aeef  mov qword ptr [rbp+0x1A0],0
0x4e1aefa  mov qword ptr [rbp+0x1A8],0xF
0x4e1af05  movaps xmm0,[0xF0FFAB0]
0x4e1af0c  movaps [rbp+0x1B0],xmm0
0x4e1af13  mov word ptr [rbp+0x1C0],0x101
0x4e1af1c  mov byte ptr [rbp+0x1C2],1
0x4e1af23  lea rsi,[rbp+0x130]
0x4e1af2a  mov rcx,rbx

### Phase 2: 0x4e1af2d..0x4e1afc9 — 36 instructions

rcx=rsi and 0x15B7F0 is called, then rax=[rbp+0x2E8] is validated as a heap block: size vs 0x10 (jb to 0x4E1AF82), total [rax+1] vs 0x1000, header qword [rcx-8] (rcx=[rbp+0x2D0]); rcx-8-r8 compared to 0x20 — blocks at least 0x20 bail to 0x4E1BFC5 — otherwise rax+=0x28 and the block is freed by 0xE935700 [V 0x4e1af30-0x4e1af7d]. At 0x4E1AF82 the [rbp+0x408] object pointer's [rcx+8] is either refcount-incremented (lock inc dword) or the [rbp+0x2B0]/[rbp+0x2B8] ptr/ref pair is null-initialized [V 0x4e1af82-0x4e1afaf]. Then 0xE932EB0 loads the string at global 0xF60B4F1 into r12, the atomic qword at [0x128C1568] is lock-incremented, globals [0x128C1570] (only if byte [rax]==1) and [0x128C1578] (lock inc dword [rcx+8]) are loaded [V 0x4e1afb6-0x4e1afc9].

0x4e1af2d  mov rdx,rsi
0x4e1af30  call 0x282A8E0
0x4e1af35  mov rcx,rsi
0x4e1af38  call 0x15B7F0
0x4e1af3d  mov rax,[rbp+0x2E8]
0x4e1af44  cmp rax,0x10
0x4e1af48  jb short 0x4E1AF82
0x4e1af4a  mov rcx,[rbp+0x2D0]
0x4e1af51  lea rdx,[rax+1]
0x4e1af55  cmp rdx,0x1000
0x4e1af5c  jb short 0x4E1AF7D
0x4e1af5e  mov r8,[rcx-8]
0x4e1af62  add rcx,0xFFFFFFFFFFFFFFF8
0x4e1af66  sub rcx,r8
0x4e1af69  cmp rcx,0x20
0x4e1af6d  jae 0x4E1BFC5
0x4e1af73  add rax,0x28
0x4e1af77  mov rdx,rax
0x4e1af7a  mov rcx,r8
0x4e1af7d  call 0xE935700
0x4e1af82  movaps [rbp+0x2B0],xmm6
0x4e1af89  mov rcx,[rbp+0x408]
0x4e1af90  mov rax,[rcx+8]
0x4e1af94  test rax,rax
0x4e1af97  je short 0x4E1AFA3
0x4e1af99  lock inc dword ptr [rax+8]
0x4e1af9d  mov rax,[rcx+8]
0x4e1afa1  jmp short 0x4E1AFA5
0x4e1afa3  xor eax,eax
0x4e1afa5  mov rcx,[rcx]
0x4e1afa8  mov [rbp+0x2B0],rcx
0x4e1afaf  mov [rbp+0x2B8],rax
0x4e1afb6  lea rdx,[0xF60B4F1]
0x4e1afbd  mov rcx,[rbp+0x350]
0x4e1afc4  call 0xE932EB0
0x4e1afc9  nop

### Phase 3: 0x4e1afca..0x4e1b085 — 36 instructions

r12 captures the string result from 0xE932EB0; globals [0x128C1570]/[0x128C1578] are re-loaded with the same protocol (byte [rax]==1 gate at 0x4e1aff8, lock inc dword [rcx+8] at 0x4e1b009), bumping atomic [0x128C1568] again [V 0x4e1afca-0x4e1b01b]. The paths merge at 0x4E1B054 into an optional-like triple: disengaged (0x4E1B01D) zeroes [rbp+0x278], [rbp+0x280], [rbp+0x288] (16 bytes via movups) and [rbp+0x298], then calls 0x3B2020 with rcx=&global 0x128C1508; engaged stores [rbp+0x278]=rsi (&global 0x128C1508), [rbp+0x280]=1, [rbp+0x288]=rax, [rbp+0x290]=rcx, [rbp+0x298]=rdx=[0x128C1580] [V 0x4e1b01d-0x4e1b077]. Finally rdi=[rbp+0x358] and rcx=&[rdi+0x120] [V 0x4e1b07e-0x4e1b085].

0x4e1afca  mov r12,rax
0x4e1afcd  lea rsi,[0x128C1508]
0x4e1afd4  mov rcx,rsi
0x4e1afd7  call 0xE943178
0x4e1afdc  lock inc qword ptr [0x128C1568]
0x4e1afe4  mov rcx,rsi
0x4e1afe7  call 0xE94319C
0x4e1afec  mov rax,[0x128C1570]
0x4e1aff3  test rax,rax
0x4e1aff6  je short 0x4E1B01D
0x4e1aff8  cmp byte ptr [rax],1
0x4e1affb  jne short 0x4E1B01D
0x4e1affd  mov rcx,[0x128C1578]
0x4e1b004  test rcx,rcx
0x4e1b007  je short 0x4E1B052
0x4e1b009  lock inc dword ptr [rcx+8]
0x4e1b00d  mov rax,[0x128C1570]
0x4e1b014  mov rcx,[0x128C1578]
0x4e1b01b  jmp short 0x4E1B054
0x4e1b01d  mov qword ptr [rbp+0x278],0
0x4e1b028  mov byte ptr [rbp+0x280],0
0x4e1b02f  xorps xmm0,xmm0
0x4e1b032  movups [rbp+0x288],xmm0
0x4e1b039  mov qword ptr [rbp+0x298],0
0x4e1b044  lea rcx,[0x128C1508]
0x4e1b04b  call 0x3B2020
0x4e1b050  jmp short 0x4E1B07E
0x4e1b052  xor ecx,ecx
0x4e1b054  mov rdx,[0x128C1580]
0x4e1b05b  mov [rbp+0x278],rsi
0x4e1b062  mov byte ptr [rbp+0x280],1
0x4e1b069  mov [rbp+0x288],rax
0x4e1b070  mov [rbp+0x290],rcx
0x4e1b077  mov [rbp+0x298],rdx
0x4e1b07e  mov rdi,[rbp+0x358]
0x4e1b085  lea rcx,[rdi+0x120]

### Phase 4: 0x4e1b08c..0x4e1b142 — 36 instructions

mov rsi=[rdi+0x120] and r8=[rsi+8]; call 0x58E370 with rdx=&[rdi+0x120], then the node at rsi is made circular ([rsi+8]=[rsi]=[rsi+0x10]=rsi) and [rdi+0x128] is zeroed [V 0x4e1b08c-0x4e1b0aa]. Call 0xE933260 (rcx=r12, rdx=&[rbp+0x2D0]) establishes the iteration range rbx=[rbp+0x2D0]..r13=[rbp+0x2D8]; &[rdi+0x100] is saved at [rbp+0x100], [rbp+0x2C8]=r12, [rbp+0xB8]=r13 [V 0x4e1b0b5-0x4e1b0eb]. The loop entry jumps to cmp rbx,r13 (je exits to 0x4E1B74D); the body at 0x4E1B13f calls 0xE932F90 (rcx=r12, rdx=element rbx) -> rsi=rax, and the jump target 0x4E1B100 stores [rbp+0x310]=rax and [rsp+0x20]=r15, calls 0xDA490 (cl=1, edx=3, r8d=0x20, r9=string 0xF7F0B17), calls 0x4E196B0 (rcx=&[rbp+0x130]), adds rbx,0x20 and loops back to cmp rbx,r13 [V 0x4e1b0f2-0x4e1b142].

0x4e1b08c  mov rsi,[rdi+0x120]
0x4e1b093  mov r8,[rsi+8]
0x4e1b097  mov rdx,rcx
0x4e1b09a  call 0x58E370
0x4e1b09f  mov [rsi+8],rsi
0x4e1b0a3  mov [rsi],rsi
0x4e1b0a6  mov [rsi+0x10],rsi
0x4e1b0aa  mov qword ptr [rdi+0x128],0
0x4e1b0b5  lea rdx,[rbp+0x2D0]
0x4e1b0bc  mov rcx,r12
0x4e1b0bf  call 0xE933260
0x4e1b0c4  nop
0x4e1b0c5  lea rax,[rdi+0x100]
0x4e1b0cc  mov [rbp+0x100],rax
0x4e1b0d3  mov rbx,[rbp+0x2D0]
0x4e1b0da  mov r13,[rbp+0x2D8]
0x4e1b0e1  xorps xmm7,xmm7
0x4e1b0e4  mov [rbp+0x2C8],r12
0x4e1b0eb  mov [rbp+0xB8],r13
0x4e1b0f2  jmp short 0x4E1B136
0x4e1b0f4  nop [rax+rax]
0x4e1b100  mov [rbp+0x310],rax
0x4e1b107  mov [rsp+0x20],r15
0x4e1b10c  mov cl,1
0x4e1b10e  mov edx,3
0x4e1b113  mov r8d,0x20
0x4e1b119  lea r9,[0xF7F0B17]
0x4e1b120  call 0xDA490
0x4e1b125  nop
0x4e1b126  lea rcx,[rbp+0x130]
0x4e1b12d  call 0x4E196B0
0x4e1b132  add rbx,0x20
0x4e1b136  cmp rbx,r13
0x4e1b139  je 0x4E1B74D
0x4e1b13f  mov rcx,r12
0x4e1b142  mov rdx,rbx

### Phase 5: 0x4e1b145..0x4e1b1ea — 36 instructions

0xE932F90 (rcx=r12, rdx=rbx) returns the next element in rax, moved to rsi [V 0x4e1b145-0x4e1b14b]. The destination small string at [rbp+0x130] is reset: movaps [rbp+0x130]=xmm7, qword [rbp+0x140]=0, qword [rbp+0x148]=0xF, word [rbp+0x150]=0 (size 0, cap 0xF), and 16 bytes at [rbp+0x158] are zeroed through rax=lea [rbp+0x158] (movups [rax],xmm7; qword [rax+0x10]=0) [V 0x4e1b14e-0x4e1b17e]. If &[rbp+0x130]!=rbx, the source string at rbx is copied: [rbx+0x18] vs 0x10 selects the path — [rbx+0x18]>0x10 calls 0x9D6D0 (rcx=&[rbp+0x130], rdx=[rbx+0x10] size, src=[rbx]); otherwise [rbp+0x140]=rdi=[rbx+0x10] and 0xEEC6DE0 (rcx=&[rbp+0x130], rdx=r9, r8=rdi) copies inline, then byte 0 is written at [rbp+rdi+0x130] (NUL terminator) [V 0x4e1b186-0x4e1b1d9]. Ends with mov rcx,rsi; call 0xE9325C0; test al,al [V 0x4e1b1e1-0x4e1b1ea].

0x4e1b145  call 0xE932F90
0x4e1b14a  nop
0x4e1b14b  mov rsi,rax
0x4e1b14e  movaps [rbp+0x130],xmm7
0x4e1b155  mov qword ptr [rbp+0x140],0
0x4e1b160  mov qword ptr [rbp+0x148],0xF
0x4e1b16b  mov word ptr [rbp+0x150],0
0x4e1b174  lea rax,[rbp+0x158]
0x4e1b17b  movups [rax],xmm7
0x4e1b17e  mov qword ptr [rax+0x10],0
0x4e1b186  lea rax,[rbp+0x130]
0x4e1b18d  cmp rax,rbx
0x4e1b190  je short 0x4E1B1E1
0x4e1b192  cmp qword ptr [rbx+0x18],0x10
0x4e1b197  mov r9,rbx
0x4e1b19a  jb short 0x4E1B19F
0x4e1b19c  mov r9,[rbx]
0x4e1b19f  mov rdi,[rbx+0x10]
0x4e1b1a3  cmp rdi,0xF
0x4e1b1a7  jbe short 0x4E1B1C0
0x4e1b1a9  lea rcx,[rbp+0x130]
0x4e1b1b0  mov rdx,rdi
0x4e1b1b3  call 0x9D6D0
0x4e1b1b8  nop
0x4e1b1b9  jmp short 0x4E1B1E1
0x4e1b1bb  nop [rax+rax]
0x4e1b1c0  mov [rbp+0x140],rdi
0x4e1b1c7  lea rcx,[rbp+0x130]
0x4e1b1ce  mov rdx,r9
0x4e1b1d1  mov r8,rdi
0x4e1b1d4  call 0xEEC6DE0
0x4e1b1d9  mov byte ptr [rbp+rdi+0x130],0
0x4e1b1e1  mov rcx,rsi
0x4e1b1e4  call 0xE9325C0
0x4e1b1e9  nop
0x4e1b1ea  test al,al

### Phase 6: 0x4e1b1ec..0x4e1b281 — 36 instructions

On al==0 (je 0x4E1B210) the source pointer is selected — rax=rbx if [rbx+0x18]<=0x10, else rax=[rbx] — and control jumps back to 0x4E1B100 (loop tail in phase 4) [V 0x4e1b1ec-0x4e1b221]. Otherwise r13d=0 and the ref pair is snapshotted ([rbp+0x2A0]=r14=[rbp+0x2B0], [rbp+0x2A8]=0) [V 0x4e1b226-0x4e1b237]. Three 0xE932EB0 calls consume string constants 0xF5FDA08, 0xF5572AD, 0xF52FE18 (results in rax/rdi/rax); 0xE932460 (rcx=last rax, edx=0) returns al stored at [rbp+0x150]; 0xE932380 (rcx=rax) returns xmm0, copied into xmm6 [V 0x4e1b23e-0x4e1b281].

0x4e1b1ec  je short 0x4E1B210
0x4e1b1ee  movaps [rbp+0x2A0],xmm7
0x4e1b1f5  mov rax,[rbp+0x2B8]
0x4e1b1fc  test rax,rax
0x4e1b1ff  je short 0x4E1B226
0x4e1b201  lock inc dword ptr [rax+8]
0x4e1b205  mov r13,[rbp+0x2B8]
0x4e1b20c  jmp short 0x4E1B229
0x4e1b20e  xchg ax,ax
0x4e1b210  cmp qword ptr [rbx+0x18],0x10
0x4e1b215  mov rax,rbx
0x4e1b218  jb 0x4E1B100
0x4e1b21e  mov rax,[rbx]
0x4e1b221  jmp 0x4E1B100
0x4e1b226  xor r13d,r13d
0x4e1b229  mov r14,[rbp+0x2B0]
0x4e1b230  mov [rbp+0x2A0],r14
0x4e1b237  mov [rbp+0x2A8],r13
0x4e1b23e  mov rcx,rsi
0x4e1b241  lea rdx,[0xF5FDA08]
0x4e1b248  call 0xE932EB0
0x4e1b24d  nop
0x4e1b24e  mov rcx,rax
0x4e1b251  xor edx,edx
0x4e1b253  call 0xE932460
0x4e1b258  nop
0x4e1b259  mov [rbp+0x150],al
0x4e1b25f  mov rcx,rsi
0x4e1b262  lea rdx,[0xF5572AD]
0x4e1b269  call 0xE932EB0
0x4e1b26e  nop
0x4e1b26f  mov rdi,rax
0x4e1b272  mov rcx,rsi
0x4e1b275  lea rdx,[0xF52FE18]
0x4e1b27c  call 0xE932EB0
0x4e1b281  nop

### Phase 7: 0x4e1b282..0x4e1b30b — 34 instructions

xmm1 is zeroed and [rbp+0x310] is cleared (movaps [rbp+0x310],xmm7) [V 0x4e1b282-0x4e1b291]. 0xE932EB0 (rcx=rsi, rdx=string 0xF5636E5) -> rax, then 0x746640 (rcx=rax, rdx=&[rbp+0x310], r8b=1) [V 0x4e1b298-0x4e1b2b5]. 0xE932EB0 (rdx=string 0xF5BCEE1) -> rdi; 0xE932460 (rcx=rax, edx=0) -> al; sil=al; byte [rbp+0x151]=al; call 0xE932500 (rcx=rdi) -> al stored at [rbp+0x350], compared to 0 (je 0x4E1B390) [V 0x4e1b2bb-0x4e1b2e7]. Finally [rbp+0x148] vs 0x10 selects SSO (lea rax,[rbp+0x130], jb 0x4E1B312) else rax=[rbp+0x130] — slice ends at this load [V 0x4e1b2ed-0x4e1b30b].

0x4e1b282  xorps xmm1,xmm1
0x4e1b285  mov rcx,rax
0x4e1b288  call 0xE932380
0x4e1b28d  nop
0x4e1b28e  movaps xmm6,xmm0
0x4e1b291  movaps [rbp+0x310],xmm7
0x4e1b298  mov rcx,rsi
0x4e1b29b  lea rdx,[0xF5636E5]
0x4e1b2a2  call 0xE932EB0
0x4e1b2a7  nop
0x4e1b2a8  mov rcx,rax
0x4e1b2ab  lea rdx,[rbp+0x310]
0x4e1b2b2  mov r8b,1
0x4e1b2b5  call 0x746640
0x4e1b2ba  nop
0x4e1b2bb  mov rcx,rsi
0x4e1b2be  lea rdx,[0xF5BCEE1]
0x4e1b2c5  call 0xE932EB0
0x4e1b2ca  nop
0x4e1b2cb  mov rcx,rax
0x4e1b2ce  xor edx,edx
0x4e1b2d0  call 0xE932460
0x4e1b2d5  nop
0x4e1b2d6  mov sil,al
0x4e1b2d9  mov [rbp+0x151],al
0x4e1b2df  mov rcx,rdi
0x4e1b2e2  call 0xE932500
0x4e1b2e7  mov [rbp+0x350],al
0x4e1b2ed  cmp byte ptr [rbp+0x350],0
0x4e1b2f4  je 0x4E1B390
0x4e1b2fa  cmp qword ptr [rbp+0x148],0x10
0x4e1b302  lea rax,[rbp+0x130]
0x4e1b309  jb short 0x4E1B312
0x4e1b30b  mov rax,[rbp+0x130]

## [reg+off] field access table — every load/store in the 250 listed instructions

| offset | size | read/store address | verbatim `0xRVA  instr` sites | meaning |
|---|---|---|---|---|
| rax-8 | 8 B | [rax-8] qword store | `0x4e1ae67  mov [rax-8],rcx` | heap header at [block-8]: back-pointer stored here; read back as block size at 0x4e1af5e ([rcx-8]) and bounded by 0x20 at 0x4e1af69-0x4e1af6d [V] |
| 0x100 | 8 B | [rbp+0x100] qword store | `0x4e1b0cc  mov [rbp+0x100],rax` | &[rdi+0x100] saved (rax = lea [rdi+0x100] at 0x4e1b0c5) [V] |
| 0x130 | 16 B movaps / 8 B qword / 1 B byte | [rbp+0x130] qword store/load, 16-byte movaps store, byte store (indexed by rdi) | `0x4e1ae77  mov [rbp+0x130],rax`<br>`0x4e1b14e  movaps [rbp+0x130],xmm7`<br>`0x4e1b30b  mov rax,[rbp+0x130]` | destination small string: cap field [rbp+0x148]=0xF tested against SSO threshold 0x10 at 0x4e1b2fa [V]; buffer written via [rbp+0x130] and NUL-terminated at [rbp+rdi+0x130] (0x4e1b1d9) [V] |
| 0x130 (rdi-indexed) | 1 B | [rbp+rdi+0x130] byte store | `0x4e1b1d9  mov byte ptr [rbp+rdi+0x130],0` | NUL terminator after inline string copy (size rdi=[rbx+0x10]) [V] |
| 0x140 | 8 B | [rbp+0x140] qword store | `0x4e1ae7e  mov [rbp+0x140],rdi`<br>`0x4e1b155  mov qword ptr [rbp+0x140],0` | small-string size field: set to rdi (source length), reset to 0 [V] |
| 0x148 | 8 B | [rbp+0x148] qword store/load | `0x4e1ae85  mov [rbp+0x148],rbx`<br>`0x4e1b160  mov qword ptr [rbp+0x148],0xF`<br>`0x4e1b2fa  cmp qword ptr [rbp+0x148],0x10` | small-string capacity field (=0xF); compared to 0x10 for SSO path select at 0x4e1b2fa [V] |
| 0x150 | 16 B movaps / 4 B dword / 2 B word / 1 B byte | [rbp+0x150] movaps store, dword store, word store, byte store | `0x4e1aea4  movaps [rbp+0x150],xmm6`<br>`0x4e1aec1  mov dword ptr [rbp+0x150],0x68746170`<br>`0x4e1b16b  mov word ptr [rbp+0x150],0`<br>`0x4e1b259  mov [rbp+0x150],al` | buffer start: imm 0x68746170 = 'p','a','t' tag [V]; size dword overwritten by word 0 then byte al (result of call 0xE932460, edx=0, at 0x4e1b253) [V] |
| 0x151 | 1 B | [rbp+0x151] byte store | `0x4e1b2d9  mov [rbp+0x151],al` | byte result of second call 0xE932460 (edx=0) [V] |
| 0x158 | 16 B movups / 8 B qword | [rax]=[rbp+0x158] 16-byte store (rax = lea [rbp+0x158] at 0x4e1b174) | `0x4e1b174  lea rax,[rbp+0x158]`<br>`0x4e1b17b  movups [rax],xmm7` | 16-byte scratch zeroed [V] |
| 0x160 | 8 B | [rbp+0x160] qword store | `0x4e1aeab  mov qword ptr [rbp+0x160],4` | small-string size field = 4 (matches 'pat' length) [V] |
| 0x168 | 8 B | [rbp+0x168] qword store (direct and via [rax+0x10], rax=[rbp+0x158]) | `0x4e1aeb6  mov qword ptr [rbp+0x168],0xF`<br>`0x4e1b17e  mov qword ptr [rax+0x10],0` | capacity field = 0xF, then cleared via scratch rax [V] |
| 0x170 | 16 B | [rbp+0x170] 16-byte movaps store | `0x4e1aecb  movaps [rbp+0x170],xmm6` | second small-string zeroed [V] |
| 0x180 | 8 B | [rbp+0x180] qword store | `0x4e1aed2  mov qword ptr [rbp+0x180],0` | second small-string size = 0 [V] |
| 0x188 | 8 B | [rbp+0x188] qword store | `0x4e1aedd  mov qword ptr [rbp+0x188],0xF` | second small-string capacity = 0xF [V] |
| 0x190 | 16 B | [rbp+0x190] 16-byte movaps store | `0x4e1aee8  movaps [rbp+0x190],xmm6` | third small-string zeroed [V] |
| 0x1A0 | 8 B | [rbp+0x1A0] qword store | `0x4e1aeef  mov qword ptr [rbp+0x1A0],0` | third small-string size = 0 [V] |
| 0x1A8 | 8 B | [rbp+0x1A8] qword store | `0x4e1aefa  mov qword ptr [rbp+0x1A8],0xF` | third small-string capacity = 0xF [V] |
| 0x1B0 | 16 B | [rbp+0x1B0] 16-byte movaps store | `0x4e1af0c  movaps [rbp+0x1B0],xmm0` (xmm0 = 16-byte load from [0xF0FFAB0] at 0x4e1af05) | 16-byte rodata constant from [0xF0FFAB0]; contents not shown in this slice [V load, meaning -] |
| 0x1C0 | 2 B | [rbp+0x1C0] word store | `0x4e1af13  mov word ptr [rbp+0x1C0],0x101` | value shown (0x101); semantics not shown [V store, meaning -] |
| 0x1C2 | 1 B | [rbp+0x1C2] byte store | `0x4e1af1c  mov byte ptr [rbp+0x1C2],1` | value shown (1); semantics not shown [V store, meaning -] |
| 0x278 | 8 B | [rbp+0x278] qword store | `0x4e1b01d  mov qword ptr [rbp+0x278],0`<br>`0x4e1b05b  mov [rbp+0x278],rsi` | optional engaged pointer: 0 or &global 0x128C1508 (rsi set at 0x4e1afcd) [V] |
| 0x280 | 1 B | [rbp+0x280] byte store | `0x4e1b028  mov byte ptr [rbp+0x280],0`<br>`0x4e1b062  mov byte ptr [rbp+0x280],1` | optional engaged flag: 0 or 1 [V] |
| 0x288 | 16 B movups / 8 B qword | [rbp+0x288] 16-byte movups store, qword store | `0x4e1b032  movups [rbp+0x288],xmm0`<br>`0x4e1b069  mov [rbp+0x288],rax` | optional 16-byte payload: zeroed or rax [V] |
| 0x290 | 8 B | [rbp+0x290] qword store | `0x4e1b070  mov [rbp+0x290],rcx` | rcx = [0x128C1578] or 0 (from the engage/disengage merge) [V] |
| 0x298 | 8 B | [rbp+0x298] qword store | `0x4e1b039  mov qword ptr [rbp+0x298],0`<br>`0x4e1b077  mov [rbp+0x298],rdx` | 0 or rdx = [0x128C1580] (loaded at 0x4e1b054) [V] |
| 0x2A0 | 8 B | [rbp+0x2A0] qword store | `0x4e1b230  mov [rbp+0x2A0],r14` | ref-pair snapshot: ptr = [rbp+0x2B0] (r14) [V] |
| 0x2A8 | 8 B | [rbp+0x2A8] qword store | `0x4e1b237  mov [rbp+0x2A8],r13` | ref-pair snapshot: ref = 0 (r13d=0 at 0x4e1b226) [V] |
| 0x2B0 | 16 B movaps / 8 B qword | [rbp+0x2B0] 16-byte movaps store, qword store | `0x4e1af82  movaps [rbp+0x2B0],xmm6`<br>`0x4e1afa8  mov [rbp+0x2B0],rcx` | ref-pair slot: zeroed, then loaded object pointer rcx (rcx=[rcx] at 0x4e1afa5) [V] |
| 0x2B8 | 8 B | [rbp+0x2B8] qword store/load | `0x4e1afaf  mov [rbp+0x2B8],rax`<br>`0x4e1b1f5  mov rax,[rbp+0x2B8]`<br>`0x4e1b205  mov r13,[rbp+0x2B8]` | ref-pair refcounted pointer: refcount incremented via lock inc dword [rax+8] at 0x4e1b201 [V] |
| 0x2C8 | 8 B | [rbp+0x2C8] qword load/store | `0x4e1ae9d  mov rbx,[rbp+0x2C8]`<br>`0x4e1b0e4  mov [rbp+0x2C8],r12` | context pointer r12 copied into rbx [V] |
| 0x2D0 | 8 B | [rbp+0x2D0] qword load | `0x4e1af4a  mov rcx,[rbp+0x2D0]`<br>`0x4e1b0d3  mov rbx,[rbp+0x2D0]` | iteration range begin (element pointer), used by 0xE933260 and as loop cursor [V] |
| 0x2D8 | 8 B | [rbp+0x2D8] qword load | `0x4e1b0da  mov r13,[rbp+0x2D8]` | iteration range end (loop bound vs rbx at 0x4e1b136) [V] |
| 0x2E8 | 8 B | [rbp+0x2E8] qword load | `0x4e1af3d  mov rax,[rbp+0x2E8]` | heap block size candidate, compared to 0x10 at 0x4e1af44 [V] |
| 0x310 | 16 B movaps / 8 B qword | [rbp+0x310] qword store, 16-byte movaps store | `0x4e1b100  mov [rbp+0x310],rax`<br>`0x4e1b291  movaps [rbp+0x310],xmm7` | per-iteration rax save; cleared (16 bytes) before call 0x746640 [V] |
| 0x350 | 1 B | [rbp+0x350] byte store/load | `0x4e1b2e7  mov [rbp+0x350],al`<br>`0x4e1b2ed  cmp byte ptr [rbp+0x350],0` | boolean result of call 0xE932500 (rcx=rdi), compared to 0 at 0x4e1b2ed [V] |
| 0x358 | 8 B | [rbp+0x358] qword load | `0x4e1b07e  mov rdi,[rbp+0x358]` | object base; [rdi+0x120] is the list head [V] |
| 0x408 | 8 B | [rbp+0x408] qword load | `0x4e1af89  mov rcx,[rbp+0x408]` | object pointer; [rcx+8] is refcount-tested and lock-incremented [V] |
| rsp+0x20 | 8 B | [rsp+0x20] qword store | `0x4e1b107  mov [rsp+0x20],r15` | r15 spill slot in the element loop [V] |
| rax+0 | 1 B | [rax] byte load | `0x4e1aff8  cmp byte ptr [rax],1` | global object [0x128C1570] engaged-flag gate (byte == 1) [V] |
| rax+0 | 8 B | [rax] 16-byte effective store via movups [rax] (rax=[rbp+0x158]) | `0x4e1b17b  movups [rax],xmm7` | see offset 0x158 row [V] |
| rax+8 | 4 B | [rax+8] lock-inc dword (RMW), two call sites | `0x4e1af99  lock inc dword ptr [rax+8]`<br>`0x4e1b201  lock inc dword ptr [rax+8]` | refcount +1 (lock inc dword idiom): object pointer rax=[rcx+8] at 0x4e1af99 [V]; ref-pair pointer rax=[rbp+0x2B8] at 0x4e1b201 [V] |
| rcx+0 | 8 B | [rcx] qword load | `0x4e1afa5  mov rcx,[rcx]` | ref-pair ptr slot loaded after null-check of [rcx+8] [V] |
| rcx+8 | 8 B qword / 4 B lock inc | [rcx+8] qword load x2, lock-inc dword RMW | `0x4e1af90  mov rax,[rcx+8]`<br>`0x4e1af9d  mov rax,[rcx+8]`<br>`0x4e1b009  lock inc dword ptr [rcx+8]` | refcounted object pointer loaded from [rbp+0x408] [V]; refcount +1 on global refcounted ctrl (lock inc dword idiom) [V] |
| rcx-8 | 8 B | [rcx-8] qword load | `0x4e1af5e  mov r8,[rcx-8]` | heap block header read as block size [V] |
| rbx+0 | 8 B | [rbx] qword load | `0x4e1b19c  mov r9,[rbx]`<br>`0x4e1b21e  mov rax,[rbx]` | source string heap pointer (large path) or SSO fallback (rax=rbx at 0x4e1b215) [V] |
| rbx+0x10 | 8 B | [rbx+0x10] qword load | `0x4e1b19f  mov rdi,[rbx+0x10]` | source string size used as copy length (rdx=rdi at 0x4e1b1b0) [V] |
| rbx+0x18 | 8 B | [rbx+0x18] qword load | `0x4e1b192  cmp qword ptr [rbx+0x18],0x10`<br>`0x4e1b210  cmp qword ptr [rbx+0x18],0x10` | source string field vs 0x10 SSO boundary [V] |
| rdi+0x120 | 8 B | [rdi+0x120] qword load | `0x4e1b08c  mov rsi,[rdi+0x120]` | list head node [V] |
| rdi+0x128 | 8 B | [rdi+0x128] qword store | `0x4e1b0aa  mov qword ptr [rdi+0x128],0` | list size/count field cleared [V] |
| rsi+0 | 8 B | [rsi] qword store | `0x4e1b0a3  mov [rsi],rsi` | circular list: node points to itself [V idiom] |
| rsi+8 | 8 B | [rsi+8] qword load/store | `0x4e1b093  mov r8,[rsi+8]`<br>`0x4e1b09f  mov [rsi+8],rsi` | circular list self-link ([rsi+8]=[rsi]=[rsi+0x10]=rsi) [V idiom] |
| rsi+0x10 | 8 B | [rsi+0x10] qword store | `0x4e1b0a6  mov [rsi+0x10],rsi` | circular list self-link [V idiom] |
| 0xF0FFAB0 | 16 B | [0xF0FFAB0] 16-byte movaps load | `0x4e1af05  movaps xmm0,[0xF0FFAB0]` | rodata constant copied to [rbp+0x1B0]; contents not shown [V load, meaning -] |
| 0x128C1568 | 8 B | [0x128C1568] lock-inc qword (RMW) | `0x4e1afdc  lock inc qword ptr [0x128C1568]` | atomic global increment [V idiom] |
| 0x128C1570 | 8 B | [0x128C1570] qword load | `0x4e1afec  mov rax,[0x128C1570]`<br>`0x4e1b00d  mov rax,[0x128C1570]` | global object pointer; gated by byte [rax]==1 at 0x4e1aff8 [V] |
| 0x128C1578 | 8 B | [0x128C1578] qword load | `0x4e1affd  mov rcx,[0x128C1578]`<br>`0x4e1b014  mov rcx,[0x128C1578]` | global refcounted ctrl; lock inc dword [rcx+8] at 0x4e1b009 [V] |
| 0x128C1580 | 8 B | [0x128C1580] qword load | `0x4e1b054  mov rdx,[0x128C1580]` | global qword stored at [rbp+0x298] on the engaged path [V] |

## Coverage notes

- All 250 listed instructions (0x4e1ae52..0x4e1b30b) appear verbatim above, each in exactly one phase; phases 1-7 hold 36/36/36/36/36/36/34 instructions. Nothing is skipped and no ellipsis is used.
- Jump/call targets outside the slice are listed in the header and are not covered by this unit.
- The element loop spans phases 4-6 via backward edges 0x4e1b218 `jb 0x4E1B100` and 0x4e1b221 `jmp 0x4E1B100` (0x4e1b100 is listed in phase 4).
- Field-table sizes come from the instructions: movups/movaps = 16 B, qword = 8 B, dword = 4 B, word = 2 B, byte = 1 B.
- Meanings are stated only where an instruction, immediate, or string in this slice shows them; all other rows carry '-'. No offsets are guessed.

## TOOL REQUESTS

None — no helper scripts written; existing tools only (verify_oc.py via delegate.py check).
