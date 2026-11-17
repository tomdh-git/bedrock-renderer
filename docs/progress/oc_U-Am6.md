## NEXT
DONE

# Unit U-Am6 dossier — atlas_meta_parse_4e1a0a0_4e1bff4, chunk 6 of 7, slice 0x4e1b7c8..0x4e1bc34

Source listing: docs/progress/_part_Am6.txt (250 instructions), verbatim disassembly [V] of Minecraft.Windows.exe 1.26.62.01 at image-base RVAs. Every instruction in the slice belongs to exactly one phase below; nothing is skipped or summarized. `0xRVA  instr` lines are copied verbatim from the listing (two-space separator). Sizes: qword register operand = 8, movups/movaps = 16, dword = 4, word = 2, byte = 1. A meaning is given only where an instruction or string shows it, otherwise "-".

## Phases

### Piece 1 of 5 (listing lines 1-60)

0x4e1b7c8..0x4e1b899: Stores 0 to [rbp+0x330], calls 0x3B2020 with [0x128C1508], then either jumps to 0x4E1BD09 after releasing [rbp+0x130] through 0x4E196B0 and [rbp+0x2D0] through 0x75C10, or falls through to a locked cmpxchg increment of [rcx+8]; on success it copies 16 bytes from [r15] to [rbp+0x340] and keeps r15 as r12.
0x4e1b7c8  mov qword ptr [rbp+0x330],0
0x4e1b7d3  lea rcx,[0x128C1508]
0x4e1b7da  call 0x3B2020
0x4e1b7df  jmp short 0x4E1B831
0x4e1b7e1  lea rcx,[rbp+0x130]
0x4e1b7e8  call 0x4E196B0
0x4e1b7ed  lea rcx,[rbp+0x2D0]
0x4e1b7f4  call 0x75C10
0x4e1b7f9  mov rdi,[rbp+0x338]
0x4e1b800  jmp 0x4E1BD09
0x4e1b805  xor ecx,ecx
0x4e1b807  mov rdx,[0x128C1580]
0x4e1b80e  mov [rbp+0x310],rsi
0x4e1b815  mov byte ptr [rbp+0x318],1
0x4e1b81c  mov [rbp+0x320],rax
0x4e1b823  mov [rbp+0x328],rcx
0x4e1b82a  mov [rbp+0x330],rdx
0x4e1b831  mov rax,[rbp+0x358]
0x4e1b838  mov r15,[rax+0x188]
0x4e1b83f  lea r14,[rbp+0x140]
0x4e1b846  xorps xmm6,xmm6
0x4e1b849  lea r13,[rbp+0x130]
0x4e1b850  mov rax,[rbp+0x358]
0x4e1b857  mov rsi,[rax+0x190]
0x4e1b85e  cmp r15,rsi
0x4e1b861  je 0x4E1BC63
0x4e1b867  movaps [rbp+0x340],xmm6
0x4e1b86e  mov rcx,[r15+8]
0x4e1b872  test rcx,rcx
0x4e1b875  je short 0x4E1B8B7
0x4e1b877  mov eax,[rcx+8]
0x4e1b87a  nop [rax+rax]
0x4e1b880  test eax,eax
0x4e1b882  je 0x4E1B960
0x4e1b888  lea edx,[rax+1]
0x4e1b88b  lock cmpxchg [rcx+8],edx
0x4e1b890  jne short 0x4E1B880
0x4e1b892  movups xmm0,[r15]
0x4e1b896  mov r12,[r15]
0x4e1b899  movaps [rbp+0x340],xmm0

0x4e1b8a0..0x4e1b8f0: If r12 is zero it reloads [rax+0x190] and branches to 0x4E1B91E; otherwise it walks [rdi] forward in 0x10 steps up to [rax+0x190], moving each 16-byte slot through xmm0 and zeroing the slot, then release-decrements [rcx+0xC] at [rdi-8] and frees the node via [0xF99FFA0] when the count reaches zero.
0x4e1b8a0  test r12,r12
0x4e1b8a3  jne 0x4E1B970
0x4e1b8a9  mov rax,[rbp+0x358]
0x4e1b8b0  mov rsi,[rax+0x190]
0x4e1b8b7  lea rdi,[r15+0x10]
0x4e1b8bb  cmp rdi,rsi
0x4e1b8be  jne short 0x4E1B8D9
0x4e1b8c0  jmp short 0x4E1B91E
0x4e1b8c2  nop [rax+rax]
0x4e1b8d0  add rdi,0x10
0x4e1b8d4  cmp rdi,rsi
0x4e1b8d7  je short 0x4E1B910
0x4e1b8d9  movups xmm0,[rdi]
0x4e1b8dc  movups [rdi],xmm6
0x4e1b8df  mov rcx,[rdi-8]
0x4e1b8e3  movups [rdi-0x10],xmm0
0x4e1b8e7  test rcx,rcx
0x4e1b8ea  je short 0x4E1B8D0
0x4e1b8ec  lock dec dword ptr [rcx+0xC]
0x4e1b8f0  jne short 0x4E1B8D0

### Piece 2 of 5 (listing lines 61-120)

0x4e1b8f2..0x4e1b9a5: Runs the second destructor stage for the node (loads [rcx] and [rax+8], calls [0xF99FFA0]), subtracts 0x10 from the size at [rax+0x190], sets edi=3 and jumps to 0x4E1BBD6; otherwise loads r12=[rbp+0x340], calls 0x4E192D0([rbp+0x130]), stores [r12+0x20] to [rbp+0x140], and chooses r9=[r12+0x28] when [r12+0x40] >= 0x10 else r9=r12+0x28.
0x4e1b8f2  mov rax,[rcx]
0x4e1b8f5  mov rax,[rax+8]
0x4e1b8f9  call qword ptr [0xF99FFA0]
0x4e1b8ff  jmp short 0x4E1B8D0
0x4e1b901  nop [rax+rax]
0x4e1b910  mov rax,[rbp+0x358]
0x4e1b917  mov rsi,[rax+0x190]
0x4e1b91e  mov rcx,[rsi-8]
0x4e1b922  test rcx,rcx
0x4e1b925  je short 0x4E1B93A
0x4e1b927  lock dec dword ptr [rcx+0xC]
0x4e1b92b  jne short 0x4E1B93A
0x4e1b92d  mov rax,[rcx]
0x4e1b930  mov rax,[rax+8]
0x4e1b934  call qword ptr [0xF99FFA0]
0x4e1b93a  mov rax,[rbp+0x358]
0x4e1b941  add qword ptr [rax+0x190],0xFFFFFFFFFFFFFFF0
0x4e1b949  mov edi,3
0x4e1b94e  jmp 0x4E1BBD6
0x4e1b953  nop [rax+rax]
0x4e1b960  mov r12,[rbp+0x340]
0x4e1b967  test r12,r12
0x4e1b96a  je 0x4E1B8A9
0x4e1b970  mov rcx,r13
0x4e1b973  call 0x4E192D0
0x4e1b978  nop
0x4e1b979  lea rcx,[r12+0x20]
0x4e1b97e  mov eax,[r12+0x20]
0x4e1b983  mov [rbp+0x140],eax
0x4e1b989  mov rax,r12
0x4e1b98c  cmp r14,rcx
0x4e1b98f  je short 0x4E1B9FF
0x4e1b991  cmp qword ptr [r12+0x40],0x10
0x4e1b997  jb short 0x4E1B9A0
0x4e1b999  mov r9,[r12+0x28]
0x4e1b99e  jmp short 0x4E1B9A5
0x4e1b9a0  lea r9,[r12+0x28]
0x4e1b9a5  mov rsi,[r12+0x38]

0x4e1b9b1..0x4e1b9ff: Compares [r12+0x38] with [rbp+0x160]; when greater it calls 0x9D6D0 with rcx=[rbp+0x148] and rdx=length, else it uses the inline buffer [rbp+0x148] (taking the heap pointer stored at [rbp+0x148] once rax >= 0x10); it records the length in [rbp+0x158], calls 0xEEC6DE0(rdi, r9, rsi, r8=rsi), null-terminates with [rdi+rsi]=0, then loads 16 bytes from [r12+0x48].
0x4e1b9b1  cmp rsi,rax
0x4e1b9b4  jbe short 0x4E1B9CF
0x4e1b9b6  lea rcx,[rbp+0x148]
0x4e1b9bd  mov rdx,rsi
0x4e1b9c0  call 0x9D6D0
0x4e1b9c5  nop
0x4e1b9c6  mov rax,[rbp+0x340]
0x4e1b9cd  jmp short 0x4E1B9FF
0x4e1b9cf  lea rdi,[rbp+0x148]
0x4e1b9d6  cmp rax,0x10
0x4e1b9da  jb short 0x4E1B9E3
0x4e1b9dc  mov rdi,[rbp+0x148]
0x4e1b9e3  mov [rbp+0x158],rsi
0x4e1b9ea  mov rcx,rdi
0x4e1b9ed  mov rdx,r9
0x4e1b9f0  mov r8,rsi
0x4e1b9f3  call 0xEEC6DE0
0x4e1b9f8  mov byte ptr [rdi+rsi],0
0x4e1b9fc  mov rax,r12
0x4e1b9ff  movups xmm0,[r12+0x48]

### Piece 3 of 5 (listing lines 121-180)

0x4e1ba05..0x4e1babc: Stores the 16 bytes from xmm0 to [r14+0x28] where r14=[rbp+0x140], then zeroes the stack string: [rbp+0x2D0] by movaps, [rbp+0x2E0]=0, [rbp+0x2E8]=0xF, [rbp+0x2F0]=0, 16 bytes at [rcx] and 8 bytes at [rcx+0x10] with rcx=rbp+0x2F8; chooses heap source [rax] when [rax+0x18] >= 0x10 else inline source [rax+0x28], copies the bytes into [rbp+0x2E0] via 0x9D6D0 or a direct mov, null-terminates at [rbp+rsi+0x2D0], then computes (end-[rbp+0x2F8])/8 scaled by 0xAAAAAAAAAAAAAAAB and loops while the result is at least 2, advancing rsi by 0x18 per 0x4E5F5C0 call.
0x4e1ba05  movups [r14+0x28],xmm0
0x4e1ba0a  movaps [rbp+0x2D0],xmm6
0x4e1ba11  mov qword ptr [rbp+0x2E0],0
0x4e1ba1c  mov qword ptr [rbp+0x2E8],0xF
0x4e1ba27  mov word ptr [rbp+0x2F0],0
0x4e1ba30  lea rcx,[rbp+0x2F8]
0x4e1ba37  movups [rcx],xmm6
0x4e1ba3a  mov qword ptr [rcx+0x10],0
0x4e1ba42  cmp rbx,rax
0x4e1ba45  je short 0x4E1BA89
0x4e1ba47  cmp qword ptr [rax+0x18],0x10
0x4e1ba4c  mov r9,rax
0x4e1ba4f  jb short 0x4E1BA54
0x4e1ba51  mov r9,[rax]
0x4e1ba54  mov rsi,[rax+0x10]
0x4e1ba58  cmp rsi,0xF
0x4e1ba5c  jbe short 0x4E1BA6C
0x4e1ba5e  mov rcx,rbx
0x4e1ba61  mov rdx,rsi
0x4e1ba64  call 0x9D6D0
0x4e1ba69  nop
0x4e1ba6a  jmp short 0x4E1BA89
0x4e1ba6c  mov [rbp+0x2E0],rsi
0x4e1ba73  mov rcx,rbx
0x4e1ba76  mov rdx,r9
0x4e1ba79  mov r8,rsi
0x4e1ba7c  call 0xEEC6DE0
0x4e1ba81  mov byte ptr [rbp+rsi+0x2D0],0
0x4e1ba89  mov rsi,[rbp+0x2F8]
0x4e1ba90  mov rdx,[rbp+0x300]
0x4e1ba97  mov rax,rdx
0x4e1ba9a  sub rax,rsi
0x4e1ba9d  mov rcx,rax
0x4e1baa0  sar rcx,3
0x4e1baa4  mov r8,0xAAAAAAAAAAAAAAAB
0x4e1baae  imul rcx,r8
0x4e1bab2  cmp rcx,2
0x4e1bab6  jb short 0x4E1BACD
0x4e1bab8  add rsi,0x18
0x4e1babc  mov rcx,rsi

0x4e1babf..0x4e1bb13: Stores [rbp+0x300]=rsi after the count loop (or jumps to 0x4E1BC23 when begin==end), reads rdx=[rsi+8] and, when [rsi+8] differs from [rsi+0x10], zeroes 16 bytes at [rdx], increments [rax+8] (rax=[rbp+0x138]) under lock, stores [rbp+0x130] at [rdx] and [rbp+0x138] at [rdx+8], records [rbp+0x350]=rdx and calls 0x4E5F280 with rdx=r14.
0x4e1babf  call 0x4E5F5C0
0x4e1bac4  mov [rbp+0x300],rsi
0x4e1bacb  jmp short 0x4E1BAD6
0x4e1bacd  cmp rdx,rsi
0x4e1bad0  je 0x4E1BC23
0x4e1bad6  mov rsi,[rbp+0x2F8]
0x4e1badd  mov rdx,[rsi+8]
0x4e1bae1  cmp rdx,[rsi+0x10]
0x4e1bae5  je short 0x4E1BB40
0x4e1bae7  movups [rdx],xmm6
0x4e1baea  mov rax,[rbp+0x138]
0x4e1baf1  test rax,rax
0x4e1baf4  je short 0x4E1BAFA
0x4e1baf6  lock inc dword ptr [rax+8]
0x4e1bafa  mov rax,[rbp+0x130]
0x4e1bb01  mov [rdx],rax
0x4e1bb04  mov rax,[rbp+0x138]
0x4e1bb0b  mov [rdx+8],rax
0x4e1bb0f  lea rcx,[rdx+0x10]
0x4e1bb13  mov [rbp+0x350],rdx

### Piece 4 of 5 (listing lines 181-240)

0x4e1bb23..0x4e1bbc0: Calls 0x4E5F280(rdx=r14), stores [rbp+0x270] at [rcx+0x140] where rcx=[rbp+0x350], and adds 0x148 to [rsi+8]; when the queue is full ([rax+0x108]==[rax+0x110]) it calls 0x4E5F9A0([rbp+0x100], rbx), otherwise it calls 0x4E5FDA0(rdx, rbx) and steps [rax+0x108] by 0x40; finally, if [rbp+0x320] is nonzero and byte [rax]==1, it loads [rax+0x20] and sets edi=1 when bit 0 of byte [rax+0x248] is set, otherwise edi=0.
0x4e1bb1a  mov rdx,r14
0x4e1bb1d  call 0x4E5F280
0x4e1bb22  nop
0x4e1bb23  mov eax,[rbp+0x270]
0x4e1bb29  mov rcx,[rbp+0x350]
0x4e1bb30  mov [rcx+0x140],eax
0x4e1bb36  add qword ptr [rsi+8],0x148
0x4e1bb3e  jmp short 0x4E1BB4C
0x4e1bb40  mov rcx,rsi
0x4e1bb43  mov r8,r13
0x4e1bb46  call 0x4E5EC90
0x4e1bb4b  nop
0x4e1bb4c  mov rax,[rbp+0x358]
0x4e1bb53  mov rdx,[rax+0x108]
0x4e1bb5a  cmp rdx,[rax+0x110]
0x4e1bb61  je short 0x4E1BB80
0x4e1bb63  mov rcx,rdx
0x4e1bb66  mov rdx,rbx
0x4e1bb69  call 0x4E5FDA0
0x4e1bb6e  nop
0x4e1bb6f  mov rax,[rbp+0x358]
0x4e1bb76  add qword ptr [rax+0x108],0x40
0x4e1bb7e  jmp short 0x4E1BB90
0x4e1bb80  mov rcx,[rbp+0x100]
0x4e1bb87  mov r8,rbx
0x4e1bb8a  call 0x4E5F9A0
0x4e1bb8f  nop
0x4e1bb90  mov rax,[rbp+0x320]
0x4e1bb97  test rax,rax
0x4e1bb9a  je short 0x4E1BBC0
0x4e1bb9c  cmp byte ptr [rax],1
0x4e1bb9f  jne short 0x4E1BBC0
0x4e1bba1  mov rax,[rbp+0x330]
0x4e1bba8  mov rax,[rax+0x20]
0x4e1bbac  movzx eax,byte ptr [rax+0x248]
0x4e1bbb3  mov edi,1
0x4e1bbb8  test al,1
0x4e1bbba  jne short 0x4E1BBC2
0x4e1bbbc  nop [rax]
0x4e1bbc0  xor edi,edi

0x4e1bbc2..0x4e1bc07: With edi=0 it calls 0x4E196B0(rbx) and 0x4E19500(r13=rbp+0x130), then release-drops [rbp+0x348] — [rsi+8] then [rsi+0xC] — running both destructor stages via [0xF99FFA0] when each count hits zero.
0x4e1bbc2  add r15,0x10
0x4e1bbc6  mov rcx,rbx
0x4e1bbc9  call 0x4E196B0
0x4e1bbce  mov rcx,r13
0x4e1bbd1  call 0x4E19500
0x4e1bbd6  mov rsi,[rbp+0x348]
0x4e1bbdd  test rsi,rsi
0x4e1bbe0  je short 0x4E1BC10
0x4e1bbe2  lock dec dword ptr [rsi+8]
0x4e1bbe6  jne short 0x4E1BC10
0x4e1bbe8  mov rax,[rsi]
0x4e1bbeb  mov rax,[rax]
0x4e1bbee  mov rcx,rsi
0x4e1bbf1  call qword ptr [0xF99FFA0]
0x4e1bbf7  lock dec dword ptr [rsi+0xC]
0x4e1bbfb  jne short 0x4E1BC10
0x4e1bbfd  mov rax,[rsi]
0x4e1bc00  mov rax,[rax+8]
0x4e1bc04  mov rcx,rsi
0x4e1bc07  call qword ptr [0xF99FFA0]

### Piece 5 of 5 (listing lines 240-250)

0x4e1bc0d..0x4e1bc34: Tests edi and loops back to the outer element head 0x4E1B850 when edi is 0 or 3, otherwise exits to 0x4E1BC63; then compares [rbp+0x308] with rdx and, when unequal, computes esi = 0x18 - rax and sets rcx = rdx.
0x4e1bc0d  nop [rax]
0x4e1bc10  test edi,edi
0x4e1bc12  je 0x4E1B850
0x4e1bc18  cmp edi,3
0x4e1bc1b  je 0x4E1B850
0x4e1bc21  jmp short 0x4E1BC63
0x4e1bc23  cmp [rbp+0x308],rdx
0x4e1bc2a  je short 0x4E1BC4C
0x4e1bc2c  mov esi,0x18
0x4e1bc31  sub rsi,rax
0x4e1bc34  mov rcx,rdx

## Field table — every [reg+off] field stored or loaded

One row per distinct offset, all access sites listed. Size from the instruction (qword=8, movups/movaps=16, dword=4, word=2, byte=1). Meaning only where an instruction or string shows it, else '-'. [V] = seen in the listing.

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning |
|--------|------|-------------------|------------------------------|---------|
| rbp+0x330 | 8 | [rbp+0x330] | 0x4e1b7c8  mov qword ptr [rbp+0x330],0<br>0x4e1b82a  mov [rbp+0x330],rdx<br>0x4e1bba1  mov rax,[rbp+0x330] | zeroed slot, then reloaded from [0x128C1580], then read for [rax+0x20] |
| rbp+0x130 | 8 | [rbp+0x130] | 0x4e1b7e1  lea rcx,[rbp+0x130]<br>0x4e1bafa  mov rax,[rbp+0x130]<br>0x4e1bbce  mov rcx,r13 (r13=&[rbp+0x130]) | refcounted object address slot |
| rbp+0x2D0 | 16 | [rbp+0x2D0] | 0x4e1b7ed  lea rcx,[rbp+0x2D0]<br>0x4e1ba0a  movaps [rbp+0x2D0],xmm6 | released via 0x75C10, then zeroed |
| rbp+0x338 | 8 | [rbp+0x338] | 0x4e1b7f9  mov rdi,[rbp+0x338] | rdi = node pointer |
| rbp+0x310 | 8 | [rbp+0x310] | 0x4e1b80e  mov [rbp+0x310],rsi | rsi spilled to stack slot |
| rbp+0x318 | 1 | [rbp+0x318] | 0x4e1b815  mov byte ptr [rbp+0x318],1 | flag byte set to 1 |
| rbp+0x320 | 8 | [rbp+0x320] | 0x4e1b81c  mov [rbp+0x320],rax<br>0x4e1bb90  mov rax,[rbp+0x320] | rax spilled, later tested for nonzero |
| rbp+0x328 | 8 | [rbp+0x328] | 0x4e1b823  mov [rbp+0x328],rcx | rcx (zero) spilled |
| rbp+0x358 | 8 | [rbp+0x358] | 0x4e1b831  mov rax,[rbp+0x358]<br>0x4e1b8a9  mov rax,[rbp+0x358]<br>0x4e1b910  mov rax,[rbp+0x358]<br>0x4e1b93a  mov rax,[rbp+0x358]<br>0x4e1bb4c  mov rax,[rbp+0x358]<br>0x4e1bb6f  mov rax,[rbp+0x358] | base object pointer, reloaded repeatedly |
| rax+0x188 | 8 | [rax+0x188] | 0x4e1b838  mov r15,[rax+0x188] | r15 = current node |
| rbp+0x140 | 16 | [rbp+0x140] / [r14+0x28] | 0x4e1b83f  lea r14,[rbp+0x140]<br>0x4e1b983  mov [rbp+0x140],eax<br>0x4e1ba05  movups [r14+0x28],xmm0 | lea address, dword stored from [r12+0x20], r14+0x28 receives 16 bytes |
| rbp+0x340 | 16 | [rbp+0x340] | 0x4e1b867  movaps [rbp+0x340],xmm6<br>0x4e1b899  movaps [rbp+0x340],xmm0<br>0x4e1b960  mov r12,[rbp+0x340]<br>0x4e1b9c6  mov rax,[rbp+0x340] | zeroed, then loaded 16 bytes from node, then reloaded |
| r15+8 | 8 | [r15+8] | 0x4e1b86e  mov rcx,[r15+8] | node refcount low word |
| rcx+8 | 4 | [rcx+8] | 0x4e1b877  mov eax,[rcx+8]<br>0x4e1b88b  lock cmpxchg [rcx+8],edx | refcount read, then lock cmpxchg increment |
| rax+0x190 | 8 | [rax+0x190] | 0x4e1b857  mov rsi,[rax+0x190]<br>0x4e1b8b0  mov rsi,[rax+0x190]<br>0x4e1b917  mov rsi,[rax+0x190]<br>0x4e1b941  add qword ptr [rax+0x190],0xFFFFFFFFFFFFFFF0 | end pointer read, then decremented by 0x10 |
| rdi-8 | 8 | [rdi-8] | 0x4e1b8df  mov rcx,[rdi-8] | back-pointer / node header at slot-8 |
| rcx+0xC | 4 | [rcx+0xC] | 0x4e1b8ec  lock dec dword ptr [rcx+0xC]<br>0x4e1b927  lock dec dword ptr [rcx+0xC] | refcount high dword release-decremented |
| [rdi] | 16 | [rdi] | 0x4e1b892  movups xmm0,[r15]<br>0x4e1b8d9  movups xmm0,[rdi]<br>0x4e1b8dc  movups [rdi],xmm6 | 16-byte slot read and zeroed |
| rsi-8 | 8 | [rsi-8] | 0x4e1b91e  mov rcx,[rsi-8] | node header read for destructor |
| r12+0x20 | 4 | [r12+0x20] | 0x4e1b97e  mov eax,[r12+0x20]<br>0x4e1b983  mov [rbp+0x140],eax | element count/length dword copied to stack |
| r12+0x40 | 8 | [r12+0x40] | 0x4e1b991  cmp qword ptr [r12+0x40],0x10 | small-string threshold comparison |
| r12+0x28 | 8 | [r12+0x28] | 0x4e1b999  mov r9,[r12+0x28]<br>0x4e1b9a0  lea r9,[r12+0x28] | heap pointer or inline address chosen by size |
| r12+0x38 | 8 | [r12+0x38] | 0x4e1b9a5  mov rsi,[r12+0x38] | string length |
| rbp+0x160 | 8 | [rbp+0x160] | 0x4e1b9aa  mov rax,[rbp+0x160]<br>0x4e1b9b1  cmp rsi,rax | end-of-string pointer compared with length |
| rbp+0x148 | 8/16 | [rbp+0x148] | 0x4e1b9b6  lea rcx,[rbp+0x148]<br>0x4e1b9cf  lea rdi,[rbp+0x148]<br>0x4e1b9dc  mov rdi,[rbp+0x148] | inline buffer address, used as heap pointer when rax >= 0x10 |
| rbp+0x158 | 8 | [rbp+0x158] | 0x4e1b9e3  mov [rbp+0x158],rsi | length stored |
| rdi+rsi | 1 | [rdi+rsi] | 0x4e1b9f8  mov byte ptr [rdi+rsi],0 | null terminator stored |
| r12+0x48 | 16 | [r12+0x48] | 0x4e1b9ff  movups xmm0,[r12+0x48] | 16 bytes copied from element |
| r14+0x28 | 16 | [r14+0x28] | 0x4e1ba05  movups [r14+0x28],xmm0 | 16 bytes stored to output slot |
| rbp+0x2E0 | 8 | [rbp+0x2E0] | 0x4e1ba11  mov qword ptr [rbp+0x2E0],0<br>0x4e1ba6c  mov [rbp+0x2E0],rsi | zeroed, then length stored |
| rbp+0x2E8 | 8 | [rbp+0x2E8] | 0x4e1ba1c  mov qword ptr [rbp+0x2E8],0xF | set to 0xF (small-string max len) |
| rbp+0x2F0 | 2 | [rbp+0x2F0] | 0x4e1ba27  mov word ptr [rbp+0x2F0],0 | zeroed |
| rbp+0x2F8 | 16 | [rbp+0x2F8] / [rcx] / [rcx+0x10] | 0x4e1ba30  lea rcx,[rbp+0x2F8]<br>0x4e1ba37  movups [rcx],xmm6<br>0x4e1ba3a  mov qword ptr [rcx+0x10],0<br>0x4e1ba89  mov rsi,[rbp+0x2F8] | lea address, 16 bytes zeroed, qword at +0x10 zeroed, base reloaded |
| rcx+0x10 | 8 | [rcx+0x10] | 0x4e1ba3a  mov qword ptr [rcx+0x10],0 | qword at offset 0x10 zeroed |
| rax+0x18 | 8 | [rax+0x18] | 0x4e1ba47  cmp qword ptr [rax+0x18],0x10 | source small-string threshold test |
| rax | 8/1 | [rax] | 0x4e1ba51  mov r9,[rax]<br>0x4e1bb9c  cmp byte ptr [rax],1 | heap pointer used as source; byte compared to 1 |
| rax+0x10 | 8 | [rax+0x10] | 0x4e1ba54  mov rsi,[rax+0x10] | source length |
| rbp+rsi+0x2D0 | 1 | [rbp+rsi+0x2D0] | 0x4e1ba81  mov byte ptr [rbp+rsi+0x2D0],0 | null terminator after copy |
| rbp+0x300 | 8 | [rbp+0x300] | 0x4e1ba90  mov rdx,[rbp+0x300]<br>0x4e1bac4  mov [rbp+0x300],rsi | queue head/tail cursor, then updated |
| rsi+8 | 8/4 | [rsi+8] | 0x4e1badd  mov rdx,[rsi+8]<br>0x4e1bbe2  lock dec dword ptr [rsi+8]<br>0x4e1bb36  add qword ptr [rsi+8],0x148 | read as qword, lock-dec'd as dword, advanced by 0x148 |
| rsi+0x10 | 8 | [rsi+0x10] | 0x4e1bae1  cmp rdx,[rsi+0x10] | queue end compared |
| rdx | 16 | [rdx] | 0x4e1bae7  movups [rdx],xmm6 | slot zeroed |
| rbp+0x138 | 8 | [rbp+0x138] / [rax+8] | 0x4e1baea  mov rax,[rbp+0x138]<br>0x4e1baf6  lock inc dword ptr [rax+8]<br>0x4e1bb04  mov rax,[rbp+0x138] | refcounted object, low dword lock-incremented |
| rdx+8 | 8 | [rdx+8] | 0x4e1bb0b  mov [rdx+8],rax | [rbp+0x138] stored at slot+8 |
| rbp+0x350 | 8 | [rbp+0x350] | 0x4e1bb13  mov [rbp+0x350],rdx<br>0x4e1bb29  mov rcx,[rbp+0x350] | slot pointer saved, then reloaded |
| rcx+0x140 | 4 | [rcx+0x140] | 0x4e1bb30  mov [rcx+0x140],eax | [rbp+0x270] dword stored |
| rax+0x108 | 8 | [rax+0x108] | 0x4e1bb53  mov rdx,[rax+0x108]<br>0x4e1bb76  add qword ptr [rax+0x108],0x40 | queue write cursor read, then advanced by 0x40 |
| rax+0x110 | 8 | [rax+0x110] | 0x4e1bb5a  cmp rdx,[rax+0x110] | queue end compared for full test |
| rbp+0x100 | 8 | [rbp+0x100] | 0x4e1bb80  mov rcx,[rbp+0x100] | object passed to 0x4E5F9A0 |
| rax+0x20 | 8 | [rax+0x20] | 0x4e1bba8  mov rax,[rax+0x20] | object pointer dereferenced |
| rax+0x248 | 1 | [rax+0x248] | 0x4e1bbac  movzx eax,byte ptr [rax+0x248] | flag byte zero-extended |
| rbp+0x348 | 8 | [rbp+0x348] | 0x4e1bbd6  mov rsi,[rbp+0x348] | refcounted object loaded for release |
| rsi+0xC | 4 | [rsi+0xC] | 0x4e1bbf7  lock dec dword ptr [rsi+0xC] | second-stage refcount release-decremented |
| [rsi] | 8 | [rsi] | 0x4e1bbe8  mov rax,[rsi]<br>0x4e1bbfd  mov rax,[rsi] | vtable / first qword read for destructor |
| [rax] | 8 | [rax] | 0x4e1bbeb  mov rax,[rax]<br>0x4e1bc00  mov rax,[rax+8] | vtable read, destructor called via [0xF99FFA0] |
| rax+8 | 8 | [rax+8] | 0x4e1bc00  mov rax,[rax+8] | destructor function pointer read |
| rbp+0x308 | 8 | [rbp+0x308] | 0x4e1bc23  cmp [rbp+0x308],rdx | compared with rdx at slice end |
