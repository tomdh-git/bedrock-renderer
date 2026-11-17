## NEXT
DONE

# U-Tg4 — texgroup_load 0x5421c90, slice 0x54229f5..0x5422e48 (chunk 4 of 6)

Source listing: docs/progress/_part_Tg4.txt, 250 instructions from 0x54229f5 to 0x5422e48 inclusive, as computed by the orchestrator. Every instruction below is quoted verbatim from that listing (two spaces after the address). Every listed instruction is covered by a phase; nothing is skipped.

Legend for the field table: R = load/read from memory, W = store/write to memory, R/W = atomic read-modify-write (lock inc). The meaning column is "-" unless the instruction itself shows the meaning (lock inc = atomic increment; cmp byte ...,0 = byte compared against 0). lea instructions and absolute memory operands ([0x1233E1A8], [0xF99FFA0] indirect calls) do not access a [reg+off] field and appear in phase prose only.

## Phases

### Phase 1: 0x54229f5..0x5422a26
eax is zeroed; [rsi+0x1B8] is stored at [rbp+0x190] with zero at [rbp+0x198]; [rsi+0x1C8] is stored at [rbp+0x1A0]; rcx is tested and control exits to 0x54233E1 if rcx is zero or its first byte is 0.
0x54229f5  xor eax,eax
0x54229f7  mov rcx,[rsi+0x1B8]
0x54229fe  mov [rbp+0x190],rcx
0x5422a05  mov [rbp+0x198],rax
0x5422a0c  mov rax,[rsi+0x1C8]
0x5422a13  mov [rbp+0x1A0],rax
0x5422a1a  test rcx,rcx
0x5422a1d  je 0x54233E1
0x5422a23  cmp byte ptr [rcx],0
0x5422a26  je 0x54233E1

### Phase 2: 0x5422a2c..0x5422a74
xmm0 is stored at [rbp+0x1A8] and dword [rdx+8] is atomically incremented; [rbp+0x230] is saved at [rbp+0x1A8] and [rbp+0x1B0] and [rbp+0x28] is zeroed; [0x1233E1A8]->[rax]->[rax+8] is called through [0xF99FFA0] with edx=0x80, the result moves to rbx, and control exits to 0x5423417 if the result is null.
0x5422a2c  movups [rbp+0x1A8],xmm0
0x5422a33  lock inc dword ptr [rdx+8]
0x5422a37  mov rax,[rbp+0x230]
0x5422a3e  mov [rbp+0x1A8],rax
0x5422a45  mov [rbp+0x1B0],rdx
0x5422a4c  mov qword ptr [rbp+0x28],0
0x5422a54  mov rcx,[0x1233E1A8]
0x5422a5b  mov rax,[rcx]
0x5422a5e  mov rax,[rax+8]
0x5422a62  mov edx,0x80
0x5422a67  call qword ptr [0xF99FFA0]
0x5422a6d  nop
0x5422a6e  mov rbx,rax
0x5422a71  test rax,rax
0x5422a74  je 0x5423417

### Phase 3: 0x5422a7a..0x5422ae0
vtable pointer [0xF24D400] is stored at [rbx+0] and 16 bytes are zeroed at [rbx+8]. If [rbp+0x148] is non-null it is stored at [rbx+0x10] with [rbp+0x140] at [rbx+8] and dword [rax+0xC] atomically incremented; [rbp+0x150] is stored at [rbx+0x18], [rbx+0x20] and [rbx+0x30] are zeroed, r12 = [rbp+0x168] (r15 = [rbp+0x158] when [rbp+0x170] > 0x10), and control exits to 0x5423564 if r12 is negative or to 0x5422B01 if r12 > 0xF.
0x5422a7a  lea rax,[0xF24D400]
0x5422a81  mov [rbx],rax
0x5422a84  xorps xmm0,xmm0
0x5422a87  movups [rbx+8],xmm0
0x5422a8b  mov rax,[rbp+0x148]
0x5422a92  test rax,rax
0x5422a95  je short 0x5422AAA
0x5422a97  mov rcx,[rbp+0x140]
0x5422a9e  mov [rbx+8],rcx
0x5422aa2  mov [rbx+0x10],rax
0x5422aa6  lock inc dword ptr [rax+0xC]
0x5422aaa  mov eax,[rbp+0x150]
0x5422ab0  mov [rbx+0x18],eax
0x5422ab3  movups [rbx+0x20],xmm0
0x5422ab7  movups [rbx+0x30],xmm0
0x5422abb  mov r12,[rbp+0x168]
0x5422ac2  cmp qword ptr [rbp+0x170],0x10
0x5422aca  jb short 0x5422AD3
0x5422acc  mov r15,[rbp+0x158]
0x5422ad3  test r12,r12
0x5422ad6  js 0x5423564
0x5422adc  cmp r12,0xF
0x5422ae0  ja short 0x5422B01

### Phase 4: 0x5422ae2..0x5422afc
Small-string path (r12 <= 0xF): rax = rbx + 0x20; r12 is stored at [rbx+0x30] and 0xF at [rbx+0x38]; 16 bytes are copied from [r15] to [rax] ([rbx+0x20]) and control jumps to 0x5422BA3.
0x5422ae2  mov rax,rbx
0x5422ae5  add rax,0x20
0x5422ae9  mov [rbx+0x30],r12
0x5422aed  mov qword ptr [rbx+0x38],0xF
0x5422af5  movups xmm0,[r15]
0x5422af9  movups [rax],xmm0
0x5422afc  jmp 0x5422BA3

### Phase 5: 0x5422b01..0x5422b5c
Large path: [rbp+0x230] = rbx; size is computed as r12 | 0xF clamped to at least 0x16 (edi = 0x16, cmovae); [0x1233E1A8]->[rax]->[rax+8] is called through [0xF99FFA0]; control exits to 0x54234E2 if null; otherwise rsi = (rsi + 0x27) & 0xFFFFFFFFFFFFFFE0, the original pointer is stored at [rsi-8], and control jumps to 0x5422B78.
0x5422b01  mov [rbp+0x230],rbx
0x5422b08  mov rdx,r12
0x5422b0b  or rdx,0xF
0x5422b0f  cmp rdx,0x17
0x5422b13  mov edi,0x16
0x5422b18  cmovae rdi,rdx
0x5422b1c  mov rcx,[0x1233E1A8]
0x5422b23  mov rax,[rcx]
0x5422b26  mov rax,[rax+8]
0x5422b2a  cmp rdx,0xFFF
0x5422b31  jb short 0x5422B5E
0x5422b33  lea rbx,[rdi+0x28]
0x5422b37  mov rdx,rbx
0x5422b3a  call qword ptr [0xF99FFA0]
0x5422b40  nop
0x5422b41  mov rsi,rax
0x5422b44  test rax,rax
0x5422b47  je 0x54234E2
0x5422b4d  mov rax,rsi
0x5422b50  add rsi,0x27
0x5422b54  and rsi,0xFFFFFFFFFFFFFFE0
0x5422b58  mov [rsi-8],rax
0x5422b5c  jmp short 0x5422B78

### Phase 6: 0x5422b5e..0x5422b97
Fallback allocation of rdi + 1 through [0xF99FFA0]; control exits to 0x54234F0 if null; then rbx = [rbp+0x230], rsi is stored at [rbx+0x20], r12 at [rbx+0x30], rdi at [rbx+0x38], r12 is incremented, and 0xEEC6EC0 is called with rcx = rsi, rdx = r15, r8 = r12.
0x5422b5e  lea rbx,[rdi+1]
0x5422b62  mov rdx,rbx
0x5422b65  call qword ptr [0xF99FFA0]
0x5422b6b  nop
0x5422b6c  mov rsi,rax
0x5422b6f  test rax,rax
0x5422b72  je 0x54234F0
0x5422b78  mov rbx,[rbp+0x230]
0x5422b7f  mov [rbx+0x20],rsi
0x5422b83  mov [rbx+0x30],r12
0x5422b87  mov [rbx+0x38],rdi
0x5422b8b  inc r12
0x5422b8e  mov rcx,rsi
0x5422b91  mov rdx,r15
0x5422b94  mov r8,r12
0x5422b97  call 0xEEC6EC0

### Phase 7: 0x5422b9c..0x5422c09
rsi = [rbp+0x228]; 16 bytes are loaded from [rbp+0x178] (via rax) and stored at [rbx+0x40]; [rbp+0x188] is stored at [rbx+0x50] and 16 bytes are zeroed at [rbx+0x58]; if [rbp+0x198] is non-null it is reloaded after an atomic increment of dword [rax+8], and rsi advances by 0x248; eax = 0 otherwise; rcx = [rbp+0x190] is stored at [rbx+0x58], eax at [rbx+0x60] and [rbp+0x1A0] at [rbx+0x68]; control exits to 0x54233E1 if rcx is zero or its first byte is 0.
0x5422b9c  mov rsi,[rbp+0x228]
0x5422ba3  lea rax,[rbp+0x178]
0x5422baa  movups xmm0,[rax]
0x5422bad  movups [rbx+0x40],xmm0
0x5422bb1  mov eax,[rbp+0x188]
0x5422bb7  mov [rbx+0x50],eax
0x5422bba  xorps xmm0,xmm0
0x5422bbd  movups [rbx+0x58],xmm0
0x5422bc1  mov rax,[rbp+0x198]
0x5422bc8  test rax,rax
0x5422bcb  lea rsi,[rsi+0x248]
0x5422bd2  je short 0x5422BE1
0x5422bd4  lock inc dword ptr [rax+8]
0x5422bd8  mov rax,[rbp+0x198]
0x5422bdf  jmp short 0x5422BE3
0x5422be1  xor eax,eax
0x5422be3  mov rcx,[rbp+0x190]
0x5422bea  mov [rbx+0x58],rcx
0x5422bee  mov [rbx+0x60],rax
0x5422bf2  mov rax,[rbp+0x1A0]
0x5422bf9  mov [rbx+0x68],rax
0x5422bfd  test rcx,rcx
0x5422c00  je 0x54233E1
0x5422c06  cmp byte ptr [rcx],0
0x5422c09  je 0x54233E1

### Phase 8: 0x5422c0f..0x5422c92
[rbx+0x70] is zeroed (xmm0); if [rbp+0x1B0] is non-null, dword [rax+8] is atomically incremented and rax is reloaded, else eax = 0; [rbp+0x1A8] is stored at [rbx+0x70] and rax at [rbx+0x78]; rbx is stored at [rbp+0x28]; rax = [r14]->[rax+0x10] is loaded, rdx = [rbp-0x10] is computed, [0xF99FFA0] is called with rcx = r14, then 0x5424130 is called with rcx = &[rbp+0x140].
0x5422c0f  movups [rbx+0x70],xmm0
0x5422c13  mov rax,[rbp+0x1B0]
0x5422c1a  test rax,rax
0x5422c1d  je short 0x5422C2C
0x5422c1f  lock inc dword ptr [rax+8]
0x5422c23  mov rax,[rbp+0x1B0]
0x5422c2a  jmp short 0x5422C2E
0x5422c2c  xor eax,eax
0x5422c2e  mov rcx,[rbp+0x1A8]
0x5422c35  mov [rbx+0x70],rcx
0x5422c39  mov [rbx+0x78],rax
0x5422c3d  mov [rbp+0x28],rbx
0x5422c41  mov rax,[r14]
0x5422c44  mov rax,[rax+0x10]
0x5422c48  lea rdx,[rbp-0x10]
0x5422c4c  mov rcx,r14
0x5422c4f  call qword ptr [0xF99FFA0]
0x5422c55  nop
0x5422c56  lea rcx,[rbp+0x140]
0x5422c5d  call 0x5424130
0x5422c62  mov rdx,[rbp+0x110]
0x5422c69  mov rcx,[rbp+0x118]
0x5422c70  xorps xmm0,xmm0
0x5422c73  movaps [rbp+0x110],xmm0
0x5422c7a  mov [rbp+0x140],rdx
0x5422c81  mov [rbp+0x148],rcx
0x5422c88  mov r8,[rsi]
0x5422c8b  mov rax,[r8+8]
0x5422c8f  mov r15b,1
0x5422c92  cmp byte ptr [rax+0x19],0

### Phase 9: 0x5422c96..0x5422d01
rcx, rdx and r8 are saved at [rbp+0x208], [rbp+0x128] and [rbp+0x130]; if byte [rax+0x19] == 0 control jumps to 0x5422D06; otherwise r12 = rax and [rbp+0x230] = r8, and control jumps to 0x5422E20 if byte [rax+0x19] != 0; rbx is selected as &[rbp+0x1C8] or [rbp+0x1C8] depending on whether qword [rbp+0x1E0] is below 0x10; rdi = [rbp+0x1D8]; rax = [rbp+0x230]; r13 = [rax+0x38]; if [rax+0x40] > 0x10 then rsi = [rax+0x28] and control jumps to 0x5422DEE.
0x5422c96  mov [rbp+0x208],rcx
0x5422c9d  mov [rbp+0x128],rdx
0x5422ca4  mov [rbp+0x130],r8
0x5422cab  je short 0x5422D06
0x5422cad  mov r12,rax
0x5422cb0  mov [rbp+0x230],r8
0x5422cb7  mov rax,[rbp+0x230]
0x5422cbe  cmp byte ptr [rax+0x19],0
0x5422cc2  jne 0x5422E20
0x5422cc8  cmp qword ptr [rbp+0x1E0],0x10
0x5422cd0  lea rbx,[rbp+0x1C8]
0x5422cd7  jb short 0x5422CE0
0x5422cd9  mov rbx,[rbp+0x1C8]
0x5422ce0  mov rdi,[rbp+0x1D8]
0x5422ce7  mov rax,[rbp+0x230]
0x5422cee  mov r13,[rax+0x38]
0x5422cf2  cmp qword ptr [rax+0x40],0x10
0x5422cf7  jb 0x5422DEA
0x5422cfd  mov rsi,[rax+0x28]
0x5422d01  jmp 0x5422DEE

### Phase 10: 0x5422d06..0x5422d4f
Alternate case entered from 0x5422cab: r14 = &[rbp+0x1C8] or [rbp+0x1C8], rdi = [rbp+0x1D8], r13d = [rbp+0x1F8], [rbp+0x230] = r8 and control jumps to 0x5422D55; at 0x5422D40: rax = [r12+0x10], r15b = 1, rax = [rax], and control jumps to 0x5422CB7 if byte [rax+0x19] != 0.
0x5422d06  cmp qword ptr [rbp+0x1E0],0x10
0x5422d0e  lea r14,[rbp+0x1C8]
0x5422d15  jb short 0x5422D1E
0x5422d17  mov r14,[rbp+0x1C8]
0x5422d1e  mov rdi,[rbp+0x1D8]
0x5422d25  mov r13d,[rbp+0x1F8]
0x5422d2c  mov [rbp+0x230],r8
0x5422d33  jmp short 0x5422D55
0x5422d35  nop [rax+rax]
0x5422d40  lea rax,[r12+0x10]
0x5422d45  mov r15b,1
0x5422d48  mov rax,[rax]
0x5422d4b  cmp byte ptr [rax+0x19],0
0x5422d4f  jne 0x5422CB7

### Phase 11: 0x5422d55..0x5422d9e
r12 = rax; if [rax+0x40] > 0x10 then rsi = [r12+0x28] else rsi = &[r12+0x28]; r15 = [r12+0x38]; rbx = min(r15, rdi) via cmovb; 0xEEC6EB0 is called with rcx = rsi, rdx = r14, r8 = rbx; ecx = (r15 < rdi), edx = sign(eax), then ecx = edx if eax != 0.
0x5422d55  mov r12,rax
0x5422d58  cmp qword ptr [rax+0x40],0x10
0x5422d5d  jb short 0x5422D70
0x5422d5f  mov rsi,[r12+0x28]
0x5422d64  jmp short 0x5422D75
0x5422d66  nop [rax+rax]
0x5422d70  lea rsi,[r12+0x28]
0x5422d75  mov r15,[r12+0x38]
0x5422d7a  cmp rdi,r15
0x5422d7d  mov rbx,r15
0x5422d80  cmovb rbx,rdi
0x5422d84  mov rcx,rsi
0x5422d87  mov rdx,r14
0x5422d8a  mov r8,rbx
0x5422d8d  call 0xEEC6EB0
0x5422d92  xor ecx,ecx
0x5422d94  cmp r15,rdi
0x5422d97  setb cl
0x5422d9a  xor edx,edx
0x5422d9c  test eax,eax
0x5422d9e  sets dl

### Phase 12: 0x5422da1..0x5422dd2
If cl != 0 control jumps back to 0x5422D40; otherwise 0xEEC6EB0 is called with rcx = r14, rdx = rsi, r8 = rbx; ecx = (rdi >= r15), edx = (eax >= 0) via setns, then ecx = edx if eax != 0; if cl != 1 control jumps to 0x5422DD8, otherwise dword [r12+0x58] is compared with r13d and control jumps to 0x5422D40 if below.
0x5422da1  cmovne ecx,edx
0x5422da4  test cl,cl
0x5422da6  jne short 0x5422D40
0x5422da8  mov rcx,r14
0x5422dab  mov rdx,rsi
0x5422dae  mov r8,rbx
0x5422db1  call 0xEEC6EB0
0x5422db6  xor ecx,ecx
0x5422db8  cmp rdi,r15
0x5422dbb  setae cl
0x5422dbe  xor edx,edx
0x5422dc0  test eax,eax
0x5422dc2  setns dl
0x5422dc5  cmovne ecx,edx
0x5422dc8  cmp cl,1
0x5422dcb  jne short 0x5422DD8
0x5422dcd  cmp [r12+0x58],r13d
0x5422dd2  jb 0x5422D40

### Phase 13: 0x5422dd8..0x5422e1a
r15d = 0, [rbp+0x230] = r12, rax = r12 and control jumps to 0x5422D48; at 0x5422DEA/0x5422DEE: rsi = [rax+0x28] (or &[rax+0x28]), r14 = min(r13, rdi); 0xEEC6EB0 is called with rcx = rbx, rdx = rsi, r8 = r14; ecx = (rdi < r13), edx = sign(eax), then ecx = edx if eax != 0; control exits to 0x542339D if cl == 0.
0x5422dd8  xor r15d,r15d
0x5422ddb  mov [rbp+0x230],r12
0x5422de2  mov rax,r12
0x5422de5  jmp 0x5422D48
0x5422dea  lea rsi,[rax+0x28]
0x5422dee  cmp r13,rdi
0x5422df1  mov r14,rdi
0x5422df4  cmovb r14,r13
0x5422df8  mov rcx,rbx
0x5422dfb  mov rdx,rsi
0x5422dfe  mov r8,r14
0x5422e01  call 0xEEC6EB0
0x5422e06  xor ecx,ecx
0x5422e08  cmp rdi,r13
0x5422e0b  setb cl
0x5422e0e  xor edx,edx
0x5422e10  test eax,eax
0x5422e12  sets dl
0x5422e15  cmovne ecx,edx
0x5422e18  test cl,cl
0x5422e1a  je 0x542339D

### Phase 14: 0x5422e20..0x5422e48
rax = 0x249249249249249; rsi = [rbp+0x228]; if qword [rsi+0x250] == rax control jumps to 0x5423571; otherwise the [0x1233E1A8]->[rax]->[rax+8] pointer-chain walk resumes at the end of the slice.
0x5422e20  mov rax,0x249249249249249
0x5422e2a  mov rsi,[rbp+0x228]
0x5422e31  cmp [rsi+0x250],rax
0x5422e38  je 0x5423571
0x5422e3e  mov rcx,[0x1233E1A8]
0x5422e45  mov rax,[rcx]
0x5422e48  mov rax,[rax+8]

## Field table: every [reg+off] load/store in the slice

One row per distinct (base, offset); size and direction come from the instruction(s); meaning is "-" unless the instruction itself shows it. All instruction sites for the field are listed verbatim, in slice order. Fields addressed only by lea (no memory access: [rbp+0x178] via lea, [rbp-0x10], [rsi+0x248], [r12+0x10], [r12+0x28] in lea forms) and absolute operands ([0x1233E1A8], [0xF99FFA0]) are not table rows.

| offset | size | direction | verbatim line | meaning |
| rsi+0x1B8 | 8 | R | `0x54229f7  mov rcx,[rsi+0x1B8]` | - |
| rbp+0x190 | 8 | W,R | `0x54229fe  mov [rbp+0x190],rcx` ; `0x5422be3  mov rcx,[rbp+0x190]` | - |
| rbp+0x198 | 8 | W,R,R | `0x5422a05  mov [rbp+0x198],rax` ; `0x5422bc1  mov rax,[rbp+0x198]` ; `0x5422bd8  mov rax,[rbp+0x198]` | - |
| rsi+0x1C8 | 8 | R | `0x5422a0c  mov rax,[rsi+0x1C8]` | - |
| rbp+0x1A0 | 8 | W,R | `0x5422a13  mov [rbp+0x1A0],rax` ; `0x5422bf2  mov rax,[rbp+0x1A0]` | - |
| rbp+0x1A8 | 16 W ; 8 W ; 8 R | `0x5422a2c  movups [rbp+0x1A8],xmm0` ; `0x5422a3e  mov [rbp+0x1A8],rax` ; `0x5422c2e  mov rcx,[rbp+0x1A8]` | - |
| rdx+8 | 4 | R/W | `0x5422a33  lock inc dword ptr [rdx+8]` | atomic dword increment [V] |
| rbp+0x230 | 8 | R,W,R,W,R,R,W,W | `0x5422a37  mov rax,[rbp+0x230]` ; `0x5422b01  mov [rbp+0x230],rbx` ; `0x5422b78  mov rbx,[rbp+0x230]` ; `0x5422cb0  mov [rbp+0x230],r8` ; `0x5422cb7  mov rax,[rbp+0x230]` ; `0x5422ce7  mov rax,[rbp+0x230]` ; `0x5422d2c  mov [rbp+0x230],r8` ; `0x5422ddb  mov [rbp+0x230],r12` | - |
| rbp+0x28 | 8 | W,W | `0x5422a4c  mov qword ptr [rbp+0x28],0` ; `0x5422c3d  mov [rbp+0x28],rbx` | - |
| rax+8 | 8 R ; 4 R/W ; 4 R/W | `0x5422a5e  mov rax,[rax+8]` ; `0x5422bd4  lock inc dword ptr [rax+8]` ; `0x5422c1f  lock inc dword ptr [rax+8]` | pointer-chain load [V] ; atomic dword increment [V] |
| rbx+0 | 8 | W | `0x5422a81  mov [rbx],rax` | - |
| rbx+8 | 16 W ; 8 W | `0x5422a87  movups [rbx+8],xmm0` ; `0x5422a9e  mov [rbx+8],rcx` | - |
| rbp+0x148 | 8 | R,W | `0x5422a8b  mov rax,[rbp+0x148]` ; `0x5422c81  mov [rbp+0x148],rcx` | - |
| rbx+0x10 | 8 | W | `0x5422aa2  mov [rbx+0x10],rax` | - |
| rax+0xC | 4 | R/W | `0x5422aa6  lock inc dword ptr [rax+0xC]` | atomic dword increment [V] |
| rbp+0x150 | 4 | R | `0x5422aaa  mov eax,[rbp+0x150]` | - |
| rbx+0x18 | 4 | W | `0x5422ab0  mov [rbx+0x18],eax` | - |
| rbx+0x20 | 16 W ; 8 W | `0x5422ab3  movups [rbx+0x20],xmm0` ; `0x5422b7f  mov [rbx+0x20],rsi` | - |
| rbx+0x30 | 16 W ; 8 W ; 8 W | `0x5422ab7  movups [rbx+0x30],xmm0` ; `0x5422ae9  mov [rbx+0x30],r12` ; `0x5422b83  mov [rbx+0x30],r12` | - |
| rbp+0x168 | 8 | R | `0x5422abb  mov r12,[rbp+0x168]` | - |
| rbp+0x170 | 8 | R | `0x5422ac2  cmp qword ptr [rbp+0x170],0x10` | - |
| rbp+0x158 | 8 | R | `0x5422acc  mov r15,[rbp+0x158]` | - |
| rbx+0x38 | 8 | W,W | `0x5422aed  mov qword ptr [rbx+0x38],0xF` ; `0x5422b87  mov [rbx+0x38],rdi` | - |
| r15+0 | 16 | R | `0x5422af5  movups xmm0,[r15]` | - |
| rax+0 | 16 W ; 16 R ; 8 R | `0x5422af9  movups [rax],xmm0` ; `0x5422baa  movups xmm0,[rax]` ; `0x5422d48  mov rax,[rax]` | - |
| rsi-8 | 8 | W | `0x5422b58  mov [rsi-8],rax` | - |
| rbp+0x228 | 8 | R,R | `0x5422b9c  mov rsi,[rbp+0x228]` ; `0x5422e2a  mov rsi,[rbp+0x228]` | - |
| rbp+0x188 | 4 | R | `0x5422bb1  mov eax,[rbp+0x188]` | - |
| rbx+0x50 | 4 | W | `0x5422bb7  mov [rbx+0x50],eax` | - |
| rbx+0x58 | 16 W ; 8 W | `0x5422bbd  movups [rbx+0x58],xmm0` ; `0x5422bea  mov [rbx+0x58],rcx` | - |
| rbx+0x60 | 8 | W | `0x5422bee  mov [rbx+0x60],rax` | - |
| rbx+0x68 | 8 | W | `0x5422bf9  mov [rbx+0x68],rax` | - |
| rcx+0 | 1 | R,R | `0x5422a23  cmp byte ptr [rcx],0` ; `0x5422c06  cmp byte ptr [rcx],0` | byte compared against 0 [V] |
| rbx+0x70 | 16 W ; 8 W | `0x5422c0f  movups [rbx+0x70],xmm0` ; `0x5422c35  mov [rbx+0x70],rcx` | - |
| rbx+0x78 | 8 | W | `0x5422c39  mov [rbx+0x78],rax` | - |
| r14+0 | 8 | R | `0x5422c41  mov rax,[r14]` | - |
| rax+0x10 | 8 | R | `0x5422c44  mov rax,[rax+0x10]` | - |
| rbp+0x140 | 8 | R,W | `0x5422a97  mov rcx,[rbp+0x140]` ; `0x5422c7a  mov [rbp+0x140],rdx` | - |
| rbp+0x110 | 16 W ; 8 R | `0x5422c73  movaps [rbp+0x110],xmm0` ; `0x5422c62  mov rdx,[rbp+0x110]` | - |
| rbp+0x118 | 8 | R | `0x5422c69  mov rcx,[rbp+0x118]` | - |
| rsi+0 | 8 | R | `0x5422c88  mov r8,[rsi]` | - |
| r8+8 | 8 | R | `0x5422c8b  mov rax,[r8+8]` | - |
| rax+0x19 | 1 | R,R,R | `0x5422c92  cmp byte ptr [rax+0x19],0` ; `0x5422cbe  cmp byte ptr [rax+0x19],0` ; `0x5422d4b  cmp byte ptr [rax+0x19],0` | byte compared against 0 [V] |
| rbp+0x208 | 8 | W | `0x5422c96  mov [rbp+0x208],rcx` | - |
| rbp+0x128 | 8 | W | `0x5422c9d  mov [rbp+0x128],rdx` | - |
| rbp+0x130 | 8 | W | `0x5422ca4  mov [rbp+0x130],r8` | - |
| rbp+0x1E0 | 8 | R,R | `0x5422cc8  cmp qword ptr [rbp+0x1E0],0x10` ; `0x5422d06  cmp qword ptr [rbp+0x1E0],0x10` | - |
| rbp+0x1C8 | 8 | R,R | `0x5422cd9  mov rbx,[rbp+0x1C8]` ; `0x5422d17  mov r14,[rbp+0x1C8]` | - |
| rbp+0x1D8 | 8 | R,R | `0x5422ce0  mov rdi,[rbp+0x1D8]` ; `0x5422d1e  mov rdi,[rbp+0x1D8]` | - |
| rax+0x38 | 8 | R | `0x5422cee  mov r13,[rax+0x38]` | - |
| rax+0x40 | 8 | R,R | `0x5422cf2  cmp qword ptr [rax+0x40],0x10` ; `0x5422d58  cmp qword ptr [rax+0x40],0x10` | - |
| rax+0x28 | 8 | R | `0x5422cfd  mov rsi,[rax+0x28]` | - |
| rbp+0x1F8 | 4 | R | `0x5422d25  mov r13d,[rbp+0x1F8]` | - |
| r12+0x28 | 8 | R | `0x5422d5f  mov rsi,[r12+0x28]` | - |
| r12+0x38 | 8 | R | `0x5422d75  mov r15,[r12+0x38]` | - |
| r12+0x58 | 4 | R | `0x5422dcd  cmp [r12+0x58],r13d` | - |
| rsi+0x250 | 8 | R | `0x5422e31  cmp [rsi+0x250],rax` | - |

## TOOL REQUESTS
None
