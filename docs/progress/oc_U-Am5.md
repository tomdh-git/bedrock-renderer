## NEXT
DONE

# Unit U-Am5 dossier — atlas_meta_parse_4e1a0a0_4e1bff4, chunk 5 of 7, slice 0x4e1b312..0x4e1b7c1

Source listing: docs/progress/_part_Am5.txt (250 instructions), treated as verbatim disassembly [V] of Minecraft.Windows.exe 1.26.62.01 at image-base RVAs. Every instruction in the slice is covered by one of the phases below; nothing is skipped or summarized with a catch-all ellipsis. `0xRVA  instr` lines are copied verbatim from the listing (two-space separator). Sizes: qword register operand = 8, movups/movaps = 16, dword = 4, movss = 4, byte = 1. Meaning column gives a meaning only where an instruction or string shows it, else '-'; [V] = seen in the listing, [I] = inferred from instruction behavior.

## Phases

### Piece 1 of 4 (listing lines 1-60)

0x4e1b312..0x4e1b3ca: Stores rax into the [rbp+0x340] slot (also spilled to [rsp+0x20]), then releases an r13 refcounted object: lock-decrements [r13+8] and [r13+0xC], running the two-stage destructor through calls via [0xF99FFA0], and always branches to 0x4E1B5E0. When call 0xE9325A0 returns nonzero, call 0xE932760 yields an element count used to address a 0x18-stride element (r15 = [rbp+0x158] + n*24) passed together with [rbp+0x160] to 0x4E5F5C0, after which [rbp+0x160] = r15 and control jumps to 0x4E1B4A5.
0x4e1b312  mov [rbp+0x340],rax
0x4e1b319  lea rax,[rbp+0x340]
0x4e1b320  mov [rsp+0x20],rax
0x4e1b325  mov cl,1
0x4e1b327  mov edx,3
0x4e1b32c  mov r8d,0x20
0x4e1b332  lea r9,[0xF81E31B]
0x4e1b339  call 0xDA490
0x4e1b33e  nop
0x4e1b33f  test r13,r13
0x4e1b342  je 0x4E1B5E0
0x4e1b348  lock dec dword ptr [r13+8]
0x4e1b34d  jne 0x4E1B5E0
0x4e1b353  mov rax,[r13]
0x4e1b357  mov rax,[rax]
0x4e1b35a  mov rcx,r13
0x4e1b35d  call qword ptr [0xF99FFA0]
0x4e1b363  lock dec dword ptr [r13+0xC]
0x4e1b368  jne 0x4E1B5E0
0x4e1b36e  mov rax,[r13]
0x4e1b372  mov rax,[rax+8]
0x4e1b376  mov rcx,r13
0x4e1b379  call qword ptr [0xF99FFA0]
0x4e1b37f  jmp 0x4E1B5E0
0x4e1b384  nop [rax+rax]
0x4e1b390  mov rcx,rdi
0x4e1b393  call 0xE9325A0
0x4e1b398  nop
0x4e1b399  test al,al
0x4e1b39b  je short 0x4E1B3F9
0x4e1b39d  mov rcx,rdi
0x4e1b3a0  call 0xE932760
0x4e1b3a5  nop
0x4e1b3a6  mov edx,eax
0x4e1b3a8  mov rcx,[rbp+0x158]
0x4e1b3af  mov r12,[rbp+0x160]
0x4e1b3b6  mov r8,r12
0x4e1b3b9  sub r8,rcx
0x4e1b3bc  sar r8,3
0x4e1b3c0  mov rax,0xAAAAAAAAAAAAAAAB
0x4e1b3ca  imul r8,rax

0x4e1b3ce..0x4e1b41e: Continues the count computation (rdx-high minus low, jae to 0x4E1B471 on borrow), then derives element address r15 = [rbp+0x158] + index*24 via lea ([rdx+rdx*2]*8) and calls 0x4E5F5C0(r15, [rbp+0x160]); stores r15 to [rbp+0x160] and jumps to 0x4E1B4A5.
0x4e1b3ce  mov rax,rdx
0x4e1b3d1  sub rax,r8
0x4e1b3d4  jae 0x4E1B471
0x4e1b3da  lea rax,[rdx+rdx*2]
0x4e1b3de  lea r15,[rcx+rax*8]
0x4e1b3e2  mov rcx,r15
0x4e1b3e5  mov rdx,r12
0x4e1b3e8  call 0x4E5F5C0
0x4e1b3ed  mov [rbp+0x160],r15
0x4e1b3f4  jmp 0x4E1B4A5
0x4e1b3f9  mov r12,[rbp+0x158]
0x4e1b400  mov r15,[rbp+0x160]
0x4e1b407  mov rax,r15
0x4e1b40a  sub rax,r12
0x4e1b40d  mov rcx,rax
0x4e1b410  sar rcx,3
0x4e1b414  mov rdx,0xAAAAAAAAAAAAAAAB
0x4e1b41e  imul rcx,rdx

### Piece 2 of 4 (listing lines 61-120)

0x4e1b422..0x4e1b4e0: If the element count is below 2 it jumps to 0x4E1B440 (and there to 0x4E1B6EF when begin==end); otherwise it erases the first 0x18-byte element (add r12,0x18, call 0x4E5F5C0, [rbp+0x160]=r12) and falls to 0x4E1B449 where xmm7 is stored to [rbp+0x340] and, if r13 is set, [r13+8] is lock-incremented and r14=[rbp+0x2A0], r13=[rbp+0x2A8] are captured before jumping to 0x4E1B693. From 0x4E1B471 a recomputed count from [rbp+0x168] calls 0x4E5F790(&[rbp+0x158]) when below rdx; at 0x4E1B4a5, 0xE9335A0(&[rbp+0x340]) and 0xE9335F0(&[rbp+0xA8]) run, then r15=r13, edi=0, r12=&[rbp+0x310] open the element loop.
0x4e1b422  cmp rcx,2
0x4e1b426  jb short 0x4E1B440
0x4e1b428  add r12,0x18
0x4e1b42c  mov rcx,r12
0x4e1b42f  mov rdx,r15
0x4e1b432  call 0x4E5F5C0
0x4e1b437  mov [rbp+0x160],r12
0x4e1b43e  jmp short 0x4E1B449
0x4e1b440  cmp r15,r12
0x4e1b443  je 0x4E1B6EF
0x4e1b449  movaps [rbp+0x340],xmm7
0x4e1b450  test r13,r13
0x4e1b453  je 0x4E1B690
0x4e1b459  lock inc dword ptr [r13+8]
0x4e1b45e  mov r14,[rbp+0x2A0]
0x4e1b465  mov r13,[rbp+0x2A8]
0x4e1b46c  jmp 0x4E1B693
0x4e1b471  jbe short 0x4E1B4A5
0x4e1b473  mov r8,[rbp+0x168]
0x4e1b47a  sub r8,rcx
0x4e1b47d  sar r8,3
0x4e1b481  mov rcx,0xAAAAAAAAAAAAAAAB
0x4e1b48b  imul r8,rcx
0x4e1b48f  cmp r8,rdx
0x4e1b492  jae 0x4E1B716
0x4e1b498  lea rcx,[rbp+0x158]
0x4e1b49f  call 0x4E5F790
0x4e1b4a4  nop
0x4e1b4a5  mov rcx,rdi
0x4e1b4a8  lea rdx,[rbp+0x340]
0x4e1b4af  call 0xE9335A0
0x4e1b4b4  nop
0x4e1b4b5  mov rcx,rdi
0x4e1b4b8  lea rdx,[rbp+0xA8]
0x4e1b4bf  call 0xE9335F0
0x4e1b4c4  nop
0x4e1b4c5  mov r15,r13
0x4e1b4c8  xor edi,edi
0x4e1b4ca  lea r12,[rbp+0x310]
0x4e1b4d1  nop [rax+rax]
0x4e1b4e0  lea rcx,[rbp+0x340]

0x4e1b4e7..0x4e1b53a: Calls 0xE934700(&[rbp+0x340], &[rbp+0xA8]); if al==0 it calls 0xE9346D0(&[rbp+0x340]) and stores xmm7 to [rbp+0xC0]. If r15 is set it lock-increments [r15+8] and saves r14=[rbp+0x2A0], r13=[rbp+0x2A8] with r15=r13 (else r15=0), finishing with [rbp+0xC0]=r14 and [rbp+0xC8]=r15.
0x4e1b4e7  lea rdx,[rbp+0xA8]
0x4e1b4ee  call 0xE934700
0x4e1b4f3  nop
0x4e1b4f4  test al,al
0x4e1b4f6  jne 0x4E1B5B9
0x4e1b4fc  lea rcx,[rbp+0x340]
0x4e1b503  call 0xE9346D0
0x4e1b508  nop
0x4e1b509  movaps [rbp+0xC0],xmm7
0x4e1b510  test r15,r15
0x4e1b513  je short 0x4E1B530
0x4e1b515  lock inc dword ptr [r15+8]
0x4e1b51a  mov r14,[rbp+0x2A0]
0x4e1b521  mov r13,[rbp+0x2A8]
0x4e1b528  mov r15,r13
0x4e1b52b  jmp short 0x4E1B533
0x4e1b52d  nop [rax]
0x4e1b530  xor r15d,r15d
0x4e1b533  mov [rbp+0xC0],r14
0x4e1b53a  mov [rbp+0xC8],r15

### Piece 3 of 4 (listing lines 121-180)

0x4e1b541..0x4e1b5da: Spills locals to [rsp+0x20..0x40] (rcx=&[rbp+0x130], xmm6, edi, sil), then loops calling 0x4E18A00(rcx=[rbp+0x358], rdx=[rbp+0x418], r8=[rbp+0xC0], r9=rax); each iteration counts elements (([rbp+0x160]-[rbp+0x158])/8) and compares iteration rdi against that count. While below the count it calls 0xE9346F0(&[rbp+0x340]) per element and jumps back to re-enter 0x4E1B4E0; at exit it calls 0xE933C40 on [rbp+0xA8] and [rbp+0x340], and if r13 != 0 jumps to 0x4E1B348 (refcount release).
0x4e1b541  mov [rsp+0x40],sil
0x4e1b546  mov [rsp+0x38],r12
0x4e1b54b  movss [rsp+0x30],xmm6
0x4e1b551  mov [rsp+0x28],edi
0x4e1b555  lea rcx,[rbp+0x130]
0x4e1b55c  mov [rsp+0x20],rcx
0x4e1b561  mov rcx,[rbp+0x358]
0x4e1b568  mov rdx,[rbp+0x418]
0x4e1b56f  lea r8,[rbp+0xC0]
0x4e1b576  mov r9,rax
0x4e1b579  call 0x4E18A00
0x4e1b57e  nop
0x4e1b57f  mov rax,[rbp+0x160]
0x4e1b586  sub rax,[rbp+0x158]
0x4e1b58d  inc rdi
0x4e1b590  sar rax,3
0x4e1b594  mov rcx,0xAAAAAAAAAAAAAAAB
0x4e1b59e  imul rax,rcx
0x4e1b5a2  cmp rdi,rax
0x4e1b5a5  jae short 0x4E1B5B9
0x4e1b5a7  lea rcx,[rbp+0x340]
0x4e1b5ae  call 0xE9346F0
0x4e1b5b3  nop
0x4e1b5b4  jmp 0x4E1B4E0
0x4e1b5b9  lea rcx,[rbp+0xA8]
0x4e1b5c0  call 0xE933C40
0x4e1b5c5  lea rcx,[rbp+0x340]
0x4e1b5cc  call 0xE933C40
0x4e1b5d1  test r13,r13
0x4e1b5d4  jne 0x4E1B348
0x4e1b5da  nop [rax+rax]

0x4e1b5e0..0x4e1b678: If byte [rbp+0x350]==0 loads r14=[rbp+0x2C0], r12=[rbp+0x2C8], r13=[rbp+0xB8] (else jumps to 0x4E1B126); treats [rbp+0x358] as an iterator: if current [rax+0x108] != end [rax+0x110], copies current into [rbp+0x130] via 0x4E5FDA0 and advances [rax+0x108] by 0x40, otherwise calls 0x4E5F9A0([rbp+0x100], &[rbp+0x130]). If [rbp+0x288] holds a non-empty string (byte [rax]!=0) it executes `mov dword ptr [0],0xDEADC0DE` (null-page crash marker); otherwise it loads [rbp+0x298] and [rax+0x20].
0x4e1b5e0  cmp byte ptr [rbp+0x350],0
0x4e1b5e7  mov r14,[rbp+0x2C0]
0x4e1b5ee  lea r15,[rbp+0x310]
0x4e1b5f5  mov r12,[rbp+0x2C8]
0x4e1b5fc  mov r13,[rbp+0xB8]
0x4e1b603  jne 0x4E1B126
0x4e1b609  mov rax,[rbp+0x358]
0x4e1b610  mov rdx,[rax+0x108]
0x4e1b617  cmp rdx,[rax+0x110]
0x4e1b61e  je short 0x4E1B641
0x4e1b620  mov rcx,rdx
0x4e1b623  lea rdx,[rbp+0x130]
0x4e1b62a  call 0x4E5FDA0
0x4e1b62f  nop
0x4e1b630  mov rax,[rbp+0x358]
0x4e1b637  add qword ptr [rax+0x108],0x40
0x4e1b63f  jmp short 0x4E1B655
0x4e1b641  mov rcx,[rbp+0x100]
0x4e1b648  lea r8,[rbp+0x130]
0x4e1b64f  call 0x4E5F9A0
0x4e1b654  nop
0x4e1b655  mov rax,[rbp+0x288]
0x4e1b65c  test rax,rax
0x4e1b65f  je short 0x4E1B671
0x4e1b661  cmp byte ptr [rax],0
0x4e1b664  jne short 0x4E1B671
0x4e1b666  mov dword ptr [0],0xDEADC0DE
0x4e1b671  mov rax,[rbp+0x298]
0x4e1b678  mov rax,[rax+0x20]

### Piece 4 of 4 (listing lines 181-250)

0x4e1b67c..0x4e1b731: If bit 0 of the flag byte is clear it jumps to 0x4E1B126 or 0x4E1B7E1; if set (0x4E1B690): r13=0, stores [rbp+0x340]=r14, [rbp+0x348]=r13, spills args ([rsp+0x20]=&[rbp+0x130], [rsp+0x28]=0) and calls 0x4E18A00(rcx=[rbp+0x358], rdx=[rbp+0x418], r8=[rbp+0x340], r9=rdi), then loops to 0x4E1B33F. If [rbp+0x168]!=r15 it calls 0xEEC6ED0 to relocate/grow a 0x18-byte element buffer (rdx=0, r8=byte count) and resumes at 0x4E1B437; the 0x4E1B716 path grows by rax*24 bytes, sets r15 to the new end, and jumps to 0x4E1B3ED.
0x4e1b67c  movzx eax,byte ptr [rax+0x248]
0x4e1b683  test al,1
0x4e1b685  je 0x4E1B126
0x4e1b68b  jmp 0x4E1B7E1
0x4e1b690  xor r13d,r13d
0x4e1b693  lea rax,[rbp+0x310]
0x4e1b69a  mov [rbp+0x340],r14
0x4e1b6a1  mov [rbp+0x348],r13
0x4e1b6a8  mov [rsp+0x40],sil
0x4e1b6ad  mov [rsp+0x38],rax
0x4e1b6b2  movss [rsp+0x30],xmm6
0x4e1b6b8  lea rax,[rbp+0x130]
0x4e1b6bf  mov [rsp+0x20],rax
0x4e1b6c4  mov dword ptr [rsp+0x28],0
0x4e1b6cc  mov rcx,[rbp+0x358]
0x4e1b6d3  mov rdx,[rbp+0x418]
0x4e1b6da  lea r8,[rbp+0x340]
0x4e1b6e1  mov r9,rdi
0x4e1b6e4  call 0x4E18A00
0x4e1b6e9  nop
0x4e1b6ea  jmp 0x4E1B33F
0x4e1b6ef  cmp [rbp+0x168],r15
0x4e1b6f6  je short 0x4E1B736
0x4e1b6f8  mov r12d,0x18
0x4e1b6fe  sub r12,rax
0x4e1b701  mov rcx,r15
0x4e1b704  xor edx,edx
0x4e1b706  mov r8,r12
0x4e1b709  call 0xEEC6ED0
0x4e1b70e  add r12,r15
0x4e1b711  jmp 0x4E1B437
0x4e1b716  shl rax,3
0x4e1b71a  lea r15,[rax+rax*2]
0x4e1b71e  mov rcx,r12
0x4e1b721  xor edx,edx
0x4e1b723  mov r8,r15
0x4e1b726  call 0xEEC6ED0
0x4e1b72b  add r12,r15
0x4e1b72e  mov r15,r12
0x4e1b731  jmp 0x4E1B3ED

0x4e1b736..0x4e1b7c1: The 0x4E1B736 path calls 0x4E5F790(edx=1, &[rbp+0x158]) and jumps to 0x4E1B449. The tail calls 0x75C10(&[rbp+0x2D0]), then uses global 0x128C1508 via 0xE943178, lock-increments the qword at 0x128C1568, calls 0xE94319C, and if global [0x128C1570] is a pointer whose byte at +0 != 1 it skips, otherwise lock-increments [rcx+8] (rcx=[0x128C1578]). Finally clears [rbp+0x310] (qword 0), [rbp+0x318] (byte 0), zeroes xmm0 and stores it to [rbp+0x320] via movups.
0x4e1b736  mov edx,1
0x4e1b73b  lea rcx,[rbp+0x158]
0x4e1b742  call 0x4E5F790
0x4e1b747  nop
0x4e1b748  jmp 0x4E1B449
0x4e1b74d  lea rbx,[rbp+0x2D0]
0x4e1b754  mov rcx,rbx
0x4e1b757  call 0x75C10
0x4e1b75c  lea rsi,[0x128C1508]
0x4e1b763  mov rcx,rsi
0x4e1b766  call 0xE943178
0x4e1b76b  lock inc qword ptr [0x128C1568]
0x4e1b773  mov rcx,rsi
0x4e1b776  call 0xE94319C
0x4e1b77b  mov rax,[0x128C1570]
0x4e1b782  test rax,rax
0x4e1b785  je short 0x4E1B7AC
0x4e1b787  cmp byte ptr [rax],1
0x4e1b78a  jne short 0x4E1B7AC
0x4e1b78c  mov rcx,[0x128C1578]
0x4e1b793  test rcx,rcx
0x4e1b796  je short 0x4E1B805
0x4e1b798  lock inc dword ptr [rcx+8]
0x4e1b79c  mov rax,[0x128C1570]
0x4e1b7a3  mov rcx,[0x128C1578]
0x4e1b7aa  jmp short 0x4E1B807
0x4e1b7ac  mov qword ptr [rbp+0x310],0
0x4e1b7b7  mov byte ptr [rbp+0x318],0
0x4e1b7be  xorps xmm0,xmm0
0x4e1b7c1  movups [rbp+0x320],xmm0

## Field table — every [reg+off] field stored or loaded in the slice

| offset | size | direction | verbatim line | meaning |
|--------|------|-----------|---------------|---------|
| 0x0 | 8/1 | R | `0x4e1b353  mov rax,[r13]`<br>`0x4e1b357  mov rax,[rax]`<br>`0x4e1b36e  mov rax,[r13]`<br>`0x4e1b661  cmp byte ptr [rax],0`<br>`0x4e1b787  cmp byte ptr [rax],1` | object vtable/interface pointer read at object+0 ([I]); byte comparisons of [rax] against 0 and 1 ([V]) |
| 8 | 4 | R/W | `0x4e1b348  lock dec dword ptr [r13+8]`<br>`0x4e1b459  lock inc dword ptr [r13+8]`<br>`0x4e1b798  lock inc dword ptr [rcx+8]` | intrusive refcount at +8, lock inc/dec ([I]) |
| 0xC | 4 | R/W | `0x4e1b363  lock dec dword ptr [r13+0xC]` | second counted field at +0xC, lock dec ([I]) |
| 0x20 | 8 | R/W | `0x4e1b320  mov [rsp+0x20],rax`<br>`0x4e1b55c  mov [rsp+0x20],rcx`<br>`0x4e1b6bf  mov [rsp+0x20],rax`<br>`0x4e1b678  mov rax,[rax+0x20]` | spill slot holding &[rbp+0x340] or &[rbp+0x130] ([I]); object pointer read at object+0x20 ([V]) |
| 0x28 | 4 | W | `0x4e1b551  mov [rsp+0x28],edi`<br>`0x4e1b6c4  mov dword ptr [rsp+0x28],0` | spill slot ([I]) |
| 0x30 | 4 | W | `0x4e1b54b  movss [rsp+0x30],xmm6`<br>`0x4e1b6b2  movss [rsp+0x30],xmm6` | spill slot ([I]) |
| 0x38 | 8 | W | `0x4e1b546  mov [rsp+0x38],r12`<br>`0x4e1b6ad  mov [rsp+0x38],rax` | spill slot ([I]) |
| 0x40 | 1 | W | `0x4e1b541  mov [rsp+0x40],sil`<br>`0x4e1b6a8  mov [rsp+0x40],sil` | sil byte spill ([I]) |
| 0xB8 | 8 | R | `0x4e1b5fc  mov r13,[rbp+0xB8]` | - |
| 0x100 | 8 | R | `0x4e1b641  mov rcx,[rbp+0x100]` | - |
| 0x108 | 8 | R/W | `0x4e1b610  mov rdx,[rax+0x108]`<br>`0x4e1b637  add qword ptr [rax+0x108],0x40` | iterator current position at +0x108 ([I]); +=0x40 shows 0x40 element stride ([V]) |
| 0x110 | 8 | R | `0x4e1b617  cmp rdx,[rax+0x110]` | iterator end at +0x110 ([I]) |
| 0x158 | 8 | R | `0x4e1b3a8  mov rcx,[rbp+0x158]`<br>`0x4e1b3f9  mov r12,[rbp+0x158]`<br>`0x4e1b586  sub rax,[rbp+0x158]` | vector begin pointer ([I] from begin/end element arithmetic) |
| 0x160 | 8 | R/W | `0x4e1b3af  mov r12,[rbp+0x160]`<br>`0x4e1b3ed  mov [rbp+0x160],r15`<br>`0x4e1b400  mov r15,[rbp+0x160]`<br>`0x4e1b437  mov [rbp+0x160],r12`<br>`0x4e1b57f  mov rax,[rbp+0x160]` | vector end pointer ([I]) |
| 0x168 | 8 | R | `0x4e1b473  mov r8,[rbp+0x168]`<br>`0x4e1b6ef  cmp [rbp+0x168],r15` | - |
| 0x248 | 1 | R | `0x4e1b67c  movzx eax,byte ptr [rax+0x248]` | flag byte at +0x248 tested for bit 0 ([I]) |
| 0x298 | 8 | R | `0x4e1b671  mov rax,[rbp+0x298]` | - |
| 0x2A0 | 8 | R | `0x4e1b45e  mov r14,[rbp+0x2A0]`<br>`0x4e1b51a  mov r14,[rbp+0x2A0]` | - |
| 0x2A8 | 8 | R | `0x4e1b465  mov r13,[rbp+0x2A8]`<br>`0x4e1b521  mov r13,[rbp+0x2A8]` | - |
| 0x2C0 | 8 | R | `0x4e1b5e7  mov r14,[rbp+0x2C0]` | - |
| 0x2C8 | 8 | R | `0x4e1b5f5  mov r12,[rbp+0x2C8]` | - |
| 0x310 | 8 | W | `0x4e1b7ac  mov qword ptr [rbp+0x310],0` | cleared qword slot / buffer start ([I]) |
| 0x318 | 1 | W | `0x4e1b7b7  mov byte ptr [rbp+0x318],0` | cleared flag byte ([I]) |
| 0x320 | 16 | W | `0x4e1b7c1  movups [rbp+0x320],xmm0` | zeroed 16 bytes stored ([V]) |
| 0x340 | 16/8 | W | `0x4e1b312  mov [rbp+0x340],rax`<br>`0x4e1b449  movaps [rbp+0x340],xmm7`<br>`0x4e1b69a  mov [rbp+0x340],r14` | saved object/slot pointer ([I]) |
| 0x348 | 8 | W | `0x4e1b6a1  mov [rbp+0x348],r13` | r13 slot stored (zeroed) ([I]) |
| 0x350 | 1 | R | `0x4e1b5e0  cmp byte ptr [rbp+0x350],0` | flag byte gating the 0x4E1B126 path ([I]) |
| 0x358 | 8 | R | `0x4e1b561  mov rcx,[rbp+0x358]`<br>`0x4e1b609  mov rax,[rbp+0x358]`<br>`0x4e1b630  mov rax,[rbp+0x358]`<br>`0x4e1b6cc  mov rcx,[rbp+0x358]` | iterator object pointer ([I]) |
| 0x418 | 8 | R | `0x4e1b568  mov rdx,[rbp+0x418]`<br>`0x4e1b6d3  mov rdx,[rbp+0x418]` | - |

Notes: lea address computations ([rbp+0x340], [rbp+0x158], [rbp+0xA8], [rbp+0x130], [rbp+0x310], [rbp+0x2D0], [0xF81E31B], [0x128C1508]) compute addresses but do not load or store, so they are not in the table. Padding nops `nop [rax+rax]` / `nop [rax]` do not access memory. Absolute-address operands (not [reg+off]): `call qword ptr [0xF99FFA0]`, `mov dword ptr [0],0xDEADC0DE`, `lock inc qword ptr [0x128C1568]`, `mov rax,[0x128C1570]`, `mov rcx,[0x128C1578]`.

## TOOL REQUESTS

None
