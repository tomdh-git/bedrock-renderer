## NEXT
DONE

# U-Pvis — PlayerVision effect (0x53E62B0) and shadow producer (0x53E6C30)

Instruction-complete dossiers for the two listings docs/data/listings/effect_playervision_53e62b0_53e6842.txt and docs/data/listings/effect_shadow_producer_53e6c30_53e74c8.txt. Every instruction of every listing belongs to exactly one phase below; the `0xRVA  instr` lines are copied verbatim from the input data (two spaces after the address).

## Function 1: PlayerVision effect — 0x53E62B0..0x53E6842

rcx = effect object; r13 = [rcx+8] payload ([V 0x53e62fc]). Acquires a global helper object at 0x128C4FD0, validates it, computes a tint/fog strength from player state (0x53e646e..0x53e668a) and posts it through a vtable call (0x53e6711).

### 0x53e62b0..0x53e62f1: Prologue: save rbx,rsi,rdi,r12-r15,rbp; reserve 0x168 bytes; rbp = rsp+0x80; spill xmm6-xmm10 and the frame cookie.

```
0x53e62b0  push rbp
0x53e62b1  push r15
0x53e62b3  push r14
0x53e62b5  push r13
0x53e62b7  push r12
0x53e62b9  push rsi
0x53e62ba  push rdi
0x53e62bb  push rbx
0x53e62bc  sub rsp,0x168
0x53e62c3  lea rbp,[rsp+0x80]
0x53e62cb  movaps [rbp+0xD0],xmm10
0x53e62d3  movaps [rbp+0xC0],xmm9
0x53e62db  movaps [rbp+0xB0],xmm8
0x53e62e3  movaps [rbp+0xA0],xmm7
0x53e62ea  movaps [rbp+0x90],xmm6
0x53e62f1  mov qword ptr [rbp+0x88],0xFFFFFFFFFFFFFFFE
```

### 0x53e62fc..0x53e633b: r13 = [rcx+8]; acquire the global at 0x128C4FD0 (call 0xE943178, lock inc counter 0x128C5030, call 0xE94319C); read global slots 0x128C5038 (r15) and 0x128C5040 (rax); require [r15]==1 else fall to slow init.

```
0x53e62fc  mov r13,[rcx+8]
0x53e6300  lea rbx,[0x128C4FD0]
0x53e6307  mov rcx,rbx
0x53e630a  call 0xE943178
0x53e630f  lock inc qword ptr [0x128C5030]
0x53e6317  mov rcx,rbx
0x53e631a  call 0xE94319C
0x53e631f  mov r15,[0x128C5038]
0x53e6326  test r15,r15
0x53e6329  je short 0x53E6351
0x53e632b  cmp byte ptr [r15],1
0x53e632f  jne short 0x53E6351
0x53e6331  mov rax,[0x128C5040]
0x53e6338  test rax,rax
0x53e633b  je short 0x53E63B2
```

### 0x53e633d..0x53e63b1: Lock-inc the refcount at [rax+8] and keep r15/rsi; if the helper was null, zero the local holder ([rbp+0x58]/[rbp+0x60]) and (re)init it via 0x3B2020; then the early-return path: restore xmm6-xmm10 and epilogue/ret.

```
0x53e633d  lock inc dword ptr [rax+8]
0x53e6341  mov r15,[0x128C5038]
0x53e6348  mov rsi,[0x128C5040]
0x53e634f  jmp short 0x53E63B4
0x53e6351  mov qword ptr [rbp+0x58],0
0x53e6359  mov byte ptr [rbp+0x60],0
0x53e635d  lea rcx,[0x128C4FD0]
0x53e6364  call 0x3B2020
0x53e6369  cmp byte ptr [rbp+0x60],1
0x53e636d  jne short 0x53E6378
0x53e636f  mov rcx,[rbp+0x58]
0x53e6373  call 0x3B2020
0x53e6378  movaps xmm6,[rbp+0x90]
0x53e637f  movaps xmm7,[rbp+0xA0]
0x53e6386  movaps xmm8,[rbp+0xB0]
0x53e638e  movaps xmm9,[rbp+0xC0]
0x53e6396  movaps xmm10,[rbp+0xD0]
0x53e639e  add rsp,0x168
0x53e63a5  pop rbx
0x53e63a6  pop rdi
0x53e63a7  pop rsi
0x53e63a8  pop r12
0x53e63aa  pop r13
0x53e63ac  pop r14
0x53e63ae  pop r15
0x53e63b0  pop rbp
0x53e63b1  ret
```

### 0x53e63b2..0x53e6402: Slow-init tail: cache globals in locals ([rbp+0x58]=rbx, [rbp+0x60]=1, [rbp+0x68]=r15, [rbp+0x70]=rsi, [rbp+0x78]=rdi=[0x128C5048]); if r15 is null, [r15]!=1, or the virtual call on rdi (slot [rax+8], then [0xF99FFA0]) returns 0, jump to the release path at 0x53E6736; else load rax=[r13+0x998] and rbx=[rax+0x418].

```
0x53e63b2  xor esi,esi
0x53e63b4  mov rdi,[0x128C5048]
0x53e63bb  mov [rbp+0x58],rbx
0x53e63bf  mov byte ptr [rbp+0x60],1
0x53e63c3  mov [rbp+0x68],r15
0x53e63c7  mov [rbp+0x70],rsi
0x53e63cb  mov [rbp+0x78],rdi
0x53e63cf  test r15,r15
0x53e63d2  je 0x53E6736
0x53e63d8  cmp byte ptr [r15],1
0x53e63dc  jne 0x53E6736
0x53e63e2  mov rax,[rdi]
0x53e63e5  mov rax,[rax+8]
0x53e63e9  mov rcx,rdi
0x53e63ec  call qword ptr [0xF99FFA0]
0x53e63f2  nop
0x53e63f3  test al,al
0x53e63f5  je 0x53E6736
0x53e63fb  mov rax,[r13+0x998]
0x53e6402  mov rbx,[rax+0x418]
```

### 0x53e6409..0x53e646b: Call 0xAA7FE0(rbx); if false r12b=0; else fetch an object through vtable slot +0xF0 and look it up with 0xBD11A0 (edx=0x10, retry edx=0x1A); r12b = whether the lookup found something.

```
0x53e6409  mov rcx,rbx
0x53e640c  call 0xAA7FE0
0x53e6411  nop
0x53e6412  test al,al
0x53e6414  je short 0x53E646B
0x53e6416  mov rax,[rbx]
0x53e6419  mov rax,[rax+0xF0]
0x53e6420  mov rcx,rbx
0x53e6423  call qword ptr [0xF99FFA0]
0x53e6429  nop
0x53e642a  mov rcx,rax
0x53e642d  mov edx,0x10
0x53e6432  call 0xBD11A0
0x53e6437  nop
0x53e6438  mov r12b,1
0x53e643b  test rax,rax
0x53e643e  jne short 0x53E646E
0x53e6440  mov rax,[rbx]
0x53e6443  mov rax,[rax+0xF0]
0x53e644a  mov rcx,rbx
0x53e644d  call qword ptr [0xF99FFA0]
0x53e6453  nop
0x53e6454  mov rcx,rax
0x53e6457  mov edx,0x1A
0x53e645c  call 0xBD11A0
0x53e6461  nop
0x53e6462  test rax,rax
0x53e6465  setne r12b
0x53e6469  jmp short 0x53E646E
0x53e646b  xor r12d,r12d
```

### 0x53e646e..0x53e64f4: Load r14=[r13+0x978] and floats [r13+0x654], [r13+0x64C], [r13+0x650]; convert each through 0xEEC75A0 and pack two results as ints into [rbp+0x38] and one into [rbp+0x40]; call 0x32D0F30(r14, rdx=[rbp+0x86], r8=[rbp+0x38], r9=0) and store its byte result at [rbp+0x80]; finally fetch an object from rbx through vtable slot +0x5F0.

```
0x53e646e  mov r14,[r13+0x978]
0x53e6475  movss xmm6,[r13+0x654]
0x53e647e  movss xmm0,[r13+0x64C]
0x53e6487  movss xmm7,[r13+0x650]
0x53e6490  call 0xEEC75A0
0x53e6495  movaps xmm8,xmm0
0x53e6499  movaps xmm0,xmm7
0x53e649c  call 0xEEC75A0
0x53e64a1  unpcklps xmm8,xmm0
0x53e64a5  cvttps2dq xmm0,xmm8
0x53e64aa  movlps [rbp+0x38],xmm0
0x53e64ae  movaps xmm0,xmm6
0x53e64b1  call 0xEEC75A0
0x53e64b6  cvttss2si eax,xmm0
0x53e64ba  mov [rbp+0x40],eax
0x53e64bd  lea rdx,[rbp+0x86]
0x53e64c4  lea r8,[rbp+0x38]
0x53e64c8  mov rcx,r14
0x53e64cb  xor r9d,r9d
0x53e64ce  call 0x32D0F30
0x53e64d3  nop
0x53e64d4  movzx eax,byte ptr [rbp+0x86]
0x53e64db  mov [rbp+0x80],eax
0x53e64e1  mov rax,[rbx]
0x53e64e4  mov rax,[rax+0x5F0]
0x53e64eb  mov rcx,rbx
0x53e64ee  call qword ptr [0xF99FFA0]
0x53e64f4  nop
```

### 0x53e64f5..0x53e6561: Read int [rcx+0x390] through [r13+0x998] and convert it to float (negative path: shr 1 / or low bit / double); load floats [rax+0x64] and [rax+0x68]; xmm0 = (f+[0xEF1D470])*[0xF09BDD4] then call [0xF9A8E18] gives xmm6; xmm10=0, xmm8=[r13+0x4D4]; branch on r12b.

```
0x53e64f5  mov rcx,[r13+0x998]
0x53e64fc  mov rcx,[rcx+0x390]
0x53e6503  test rcx,rcx
0x53e6506  js short 0x53E6512
0x53e6508  xorps xmm0,xmm0
0x53e650b  cvtsi2ss xmm0,rcx
0x53e6510  jmp short 0x53E652A
0x53e6512  mov rdx,rcx
0x53e6515  shr rdx,1
0x53e6518  and ecx,1
0x53e651b  or rcx,rdx
0x53e651e  xorps xmm0,xmm0
0x53e6521  cvtsi2ss xmm0,rcx
0x53e6526  addss xmm0,xmm0
0x53e652a  movss xmm7,[rax+0x64]
0x53e652f  movss xmm9,[rax+0x68]
0x53e6535  addss xmm0,[0xEF1D470]
0x53e653d  mulss xmm0,[0xF09BDD4]
0x53e6545  call qword ptr [0xF9A8E18]
0x53e654b  movaps xmm6,xmm0
0x53e654e  xorps xmm10,xmm10
0x53e6552  movss xmm8,[r13+0x4D4]
0x53e655b  xorps xmm0,xmm0
0x53e655e  test r12b,r12b
0x53e6561  je 0x53E664B
```

### 0x53e6567..0x53e65da: If r12b: fetch an object via vtable slot +0xF0, run 0xBD11A0(edx=0x10) into rbx and 0xBD11A0(edx=0x1A) into rax; if either is non-null, compare dword ids [rbx+4] and [rax+4] (0xFFFFFFFF treated as unset) and keep the winning id in ecx.

```
0x53e6567  mov rax,[rbx]
0x53e656a  mov rax,[rax+0xF0]
0x53e6571  mov rcx,rbx
0x53e6574  call qword ptr [0xF99FFA0]
0x53e657a  nop
0x53e657b  mov r14,rax
0x53e657e  mov rcx,rax
0x53e6581  mov edx,0x10
0x53e6586  call 0xBD11A0
0x53e658b  nop
0x53e658c  mov rbx,rax
0x53e658f  mov rcx,r14
0x53e6592  mov edx,0x1A
0x53e6597  call 0xBD11A0
0x53e659c  nop
0x53e659d  mov rcx,rbx
0x53e65a0  or rcx,rax
0x53e65a3  xorps xmm0,xmm0
0x53e65a6  je 0x53E664B
0x53e65ac  test rbx,rbx
0x53e65af  je short 0x53E65B6
0x53e65b1  mov ecx,[rbx+4]
0x53e65b4  jmp short 0x53E65B8
0x53e65b6  xor ecx,ecx
0x53e65b8  test rax,rax
0x53e65bb  je short 0x53E65DC
0x53e65bd  mov eax,[rax+4]
0x53e65c0  cmp ecx,eax
0x53e65c2  je short 0x53E65DC
0x53e65c4  cmp eax,0xFFFFFFFF
0x53e65c7  je short 0x53E65DA
0x53e65c9  cmp ecx,0xFFFFFFFF
0x53e65cc  sete dl
0x53e65cf  cmp ecx,eax
0x53e65d1  setge r8b
0x53e65d5  or r8b,dl
0x53e65d8  jne short 0x53E65DC
0x53e65da  mov ecx,eax
```

### 0x53e65dc..0x53e664b: Map id ecx: 0xC8, 0xFFFFFFFF or >=0xC9 yields constant [0xEEC8060]; otherwise ecx to float, +[0xEF1D470], *=[0xEF3F024]*[0xEFD3240]*[0xEFD3338], truncated to a ushort index into the float table at 0x128F8BDC, *=[0xF07C9C4], +[0xF135DE4]; then xmm1 = the [rbp+0x80] byte as float.

```
0x53e65dc  cmp ecx,0xC8
0x53e65e2  je short 0x53E6601
0x53e65e4  cmp ecx,0xFFFFFFFF
0x53e65e7  sete al
0x53e65ea  cmp ecx,0xC9
0x53e65f0  setge dl
0x53e65f3  or dl,al
0x53e65f5  je short 0x53E6601
0x53e65f7  movss xmm0,[0xEEC8060]
0x53e65ff  jmp short 0x53E664B
0x53e6601  xorps xmm0,xmm0
0x53e6604  cvtsi2ss xmm0,ecx
0x53e6608  addss xmm0,[0xEF1D470]
0x53e6610  mulss xmm0,[0xEF3F024]
0x53e6618  mulss xmm0,[0xEFD3240]
0x53e6620  mulss xmm0,[0xEFD3338]
0x53e6628  cvttss2si eax,xmm0
0x53e662c  movzx eax,ax
0x53e662f  lea rcx,[0x128F8BDC]
0x53e6636  movss xmm0,[rcx+rax*4]
0x53e663b  mulss xmm0,[0xF07C9C4]
0x53e6643  addss xmm0,[0xF135DE4]
0x53e664b  cvtsi2ss xmm1,dword ptr [rbp+0x80]
```

### 0x53e6653..0x53e66e0: Finish the strength math (xmm7 scaled by [0xF215E90], xmm1 by [0xF0A3FD0], xmm6=xmm6*xmm7 clamped by maxss xmm6,xmm10) and store the 5-byte result block at [rbp+0x44..0x54]; assert [r15]!=0 (else fault-write 0xDEADC0DE), then check the TLS counter [0x129C6498] against the per-slot count ([gs:0x58] walk, cmp [rcx+4]); if over limit jump to 0x53E67C1, else start the event record ([rbp+0x18]=0x129C6360, flag byte 0, buffer [rbp+0x28]/[rbp+0x30]=0).

```
0x53e6653  subss xmm7,xmm9
0x53e6658  addss xmm7,xmm9
0x53e665d  mulss xmm7,[0xF215E90]
0x53e6665  mulss xmm1,[0xF0A3FD0]
0x53e666d  mulss xmm6,xmm7
0x53e6671  maxss xmm6,xmm10
0x53e6676  mov [rbp+0x44],r12b
0x53e667a  movss [rbp+0x48],xmm0
0x53e667f  movss [rbp+0x4C],xmm8
0x53e6685  movss [rbp+0x50],xmm1
0x53e668a  movss [rbp+0x54],xmm6
0x53e668f  cmp byte ptr [r15],0
0x53e6693  jne short 0x53E66A0
0x53e6695  mov dword ptr [0],0xDEADC0DE
0x53e66a0  mov eax,[0x129C6498]
0x53e66a6  mov ecx,[0x128767C8]
0x53e66ac  mov rdx,gs:[0x58]
0x53e66b5  mov rcx,[rdx+rcx*8]
0x53e66b9  cmp eax,[rcx+4]
0x53e66bf  jg 0x53E67C1
0x53e66c5  lea rcx,[0x129C6360]
0x53e66cc  mov [rbp+0x18],rcx
0x53e66d0  mov byte ptr [rbp+0x20],0
0x53e66d4  lea rbx,[rbp+0x28]
0x53e66d8  mov qword ptr [rbp+0x30],0
```

### 0x53e66e0..0x53e6735: Call 0x39A7D40(rdx=[rbp+0x28], r8=[rbp-0x50]) to fetch an event key (result byte saved at [rbp+0x20]); build the record [rbp-0x50] = pointer to the result block [rbp+0x44] with tag byte 3 at [rbp-0x48]; call the vtable slot +0x360 on rdi with it; if the saved byte==1, call 0x77A2500(0x1244FD00, rdx=rbx, r8=[rbp+0x18]+0x60).

```
0x53e66e0  mov byte ptr [rbp-0x18],0
0x53e66e4  lea r8,[rbp-0x50]
0x53e66e8  mov rdx,rbx
0x53e66eb  call 0x39A7D40
0x53e66f0  nop
0x53e66f1  mov [rbp+0x20],al
0x53e66f4  lea rax,[rbp+0x44]
0x53e66f8  mov [rbp-0x50],rax
0x53e66fc  mov byte ptr [rbp-0x48],3
0x53e6700  mov rax,[rdi]
0x53e6703  mov rax,[rax+0x360]
0x53e670a  lea rdx,[rbp-0x50]
0x53e670e  mov rcx,rdi
0x53e6711  call qword ptr [0xF99FFA0]
0x53e6717  nop
0x53e6718  cmp byte ptr [rbp+0x20],1
0x53e671c  jne short 0x53E6736
0x53e671e  mov r8,[rbp+0x18]
0x53e6722  add r8,0x60
0x53e6726  lea rcx,[0x1244FD00]
0x53e672d  mov rdx,rbx
0x53e6730  call 0x77A2500
0x53e6735  nop
```

### 0x53e6736..0x53e6778: Release path entered from all early exits: clear the 16 bytes at [rbp+0x68] (movups), then drop the rsi reference: lock dec [rsi+8]; on zero call the [0xF99FFA0] delete (after [rsi]→[rax] vtable deref), then lock dec [rsi+0xC] and delete again via slot [rax+8]; reload rsi=[rbp+0x70] and null the [rbp+0x78] slot.

```
0x53e6736  lea rax,[rbp+0x68]
0x53e673a  xorps xmm0,xmm0
0x53e673d  movups [rax],xmm0
0x53e6740  test rsi,rsi
0x53e6743  je 0x53E6369
0x53e6749  lock dec dword ptr [rsi+8]
0x53e674d  jne short 0x53E6774
0x53e674f  mov rax,[rsi]
0x53e6752  mov rax,[rax]
0x53e6755  mov rcx,rsi
0x53e6758  call qword ptr [0xF99FFA0]
0x53e675e  lock dec dword ptr [rsi+0xC]
0x53e6762  jne short 0x53E6774
0x53e6764  mov rax,[rsi]
0x53e6767  mov rax,[rax+8]
0x53e676b  mov rcx,rsi
0x53e676e  call qword ptr [0xF99FFA0]
0x53e6774  mov rsi,[rbp+0x70]
0x53e6778  mov qword ptr [rbp+0x78],0
```

### 0x53e6780..0x53e67bc: Drop the second reference (rsi=[rbp+0x70]) with the same lock dec [rsi+8] / lock dec [rsi+0xC] and vtable-delete pairs, then jump to 0x53E6369 (the epilogue).

```
0x53e6780  test rsi,rsi
0x53e6783  je 0x53E6369
0x53e6789  lock dec dword ptr [rsi+8]
0x53e678d  jne 0x53E6369
0x53e6793  mov rax,[rsi]
0x53e6796  mov rax,[rax]
0x53e6799  mov rcx,rsi
0x53e679c  call qword ptr [0xF99FFA0]
0x53e67a2  lock dec dword ptr [rsi+0xC]
0x53e67a6  jne 0x53E6369
0x53e67ac  mov rax,[rsi]
0x53e67af  mov rax,[rax+8]
0x53e67b3  mov rcx,rsi
0x53e67b6  call qword ptr [0xF99FFA0]
0x53e67bc  jmp 0x53E6369
```

### 0x53e67c1..0x53e6841: TLS counter exceeded path: call 0xE938CB0(0x129C6498); if the counter became 0xFFFFFFFF, build a fatal-error record (message ptr 0xF52E07A, length 0x15, xmm data from 0xF0BCBF8, source 0xF248EF0) and call 0x2FE330(0x129C6360, ...), then 0xE935740(0x53DECE0) and 0xE938D70(0x129C6498); return to 0x53E66C5 either way; padding nop.

```
0x53e67c1  lea rcx,[0x129C6498]
0x53e67c8  call 0xE938CB0
0x53e67cd  cmp dword ptr [0x129C6498],0xFFFFFFFF
0x53e67d4  jne 0x53E66C5
0x53e67da  lea rax,[0xF52E07A]
0x53e67e1  mov [rbp+8],rax
0x53e67e5  mov qword ptr [rbp+0x10],0x15
0x53e67ed  movups xmm0,[0xF0BCBF8]
0x53e67f4  movaps [rbp-0x10],xmm0
0x53e67f8  lea rax,[0xF248EF0]
0x53e67ff  mov [rsp+0x28],rax
0x53e6804  mov dword ptr [rsp+0x20],0
0x53e680c  lea rcx,[0x129C6360]
0x53e6813  lea rdx,[rbp-0x10]
0x53e6817  lea r9,[rbp+8]
0x53e681b  mov r8b,1
0x53e681e  call 0x2FE330
0x53e6823  nop
0x53e6824  lea rcx,[0x53DECE0]
0x53e682b  call 0xE935740
0x53e6830  lea rcx,[0x129C6498]
0x53e6837  call 0xE938D70
0x53e683c  jmp 0x53E66C5
0x53e6841  nop [rax+rax]
```

## Function 2: shadow producer — 0x53E6C30..0x53E74C8

rcx = producer object: r13 = [rcx+0x10] source ([V 0x53e6c5d]), queue object = [[rcx+8]+0x18] ([V 0x53e6da4/0x53e731f]). Per element of the array [r13+0x5F0..0x5F8) (stride 0x14) it pops a matrix from the queue, transforms its rows by camera floats, and runs three 0x4DEF480 passes ([r13+0x640], [r13+0x638], [r13+0x618]) writing into a 0x148-byte buffer at [rbp-0x38]; result block is stored at the end.

### 0x53e6c30..0x53e6c52: Prologue: save rbx,rsi,rdi,r12-r15,rbp; reserve 0x298 bytes; rbp = rsp+0x80; spill xmm6 and the frame cookie.

```
0x53e6c30  push rbp
0x53e6c31  push r15
0x53e6c33  push r14
0x53e6c35  push r13
0x53e6c37  push r12
0x53e6c39  push rsi
0x53e6c3a  push rdi
0x53e6c3b  push rbx
0x53e6c3c  sub rsp,0x298
0x53e6c43  lea rbp,[rsp+0x80]
0x53e6c4b  movaps [rbp+0x200],xmm6
0x53e6c52  mov qword ptr [rbp+0x1F8],0xFFFFFFFFFFFFFFFE
```

### 0x53e6c5d..0x53e6cc7: r13 = [rcx+0x10]; if [r13+0x5F8] == [r13+0x5F0] (empty element array) jump to the epilogue 0x53E729E; else cache [rcx+8] at [rbp+0x1D0], the movsd 8 bytes [r13+0xC] at [rbp+0x1C0], the float [r13+0x14] at [rbp+0x1C8], the pointers [r13+0x638] and [r13+0x640] and [r13+0x648] at [rbp+0x178]/[rbp+0x170]/rdi, and the 16-byte block [r13+0x650] at [rbp+0x120].

```
0x53e6c5d  mov r13,[rcx+0x10]
0x53e6c61  mov rax,[r13+0x5F8]
0x53e6c68  cmp rax,[r13+0x5F0]
0x53e6c6f  je 0x53E729E
0x53e6c75  mov rax,[rcx+8]
0x53e6c79  mov [rbp+0x1D0],rax
0x53e6c80  movsd xmm0,[r13+0xC]
0x53e6c86  movsd [rbp+0x1C0],xmm0
0x53e6c8e  movss xmm0,[r13+0x14]
0x53e6c94  movss [rbp+0x1C8],xmm0
0x53e6c9c  mov rax,[r13+0x638]
0x53e6ca3  mov [rbp+0x178],rax
0x53e6caa  mov rax,[r13+0x640]
0x53e6cb1  mov [rbp+0x170],rax
0x53e6cb8  mov rdi,[r13+0x648]
0x53e6cbf  movups xmm0,[r13+0x650]
0x53e6cc7  movaps [rbp+0x120],xmm0
```

### 0x53e6cce..0x53e6d27: Acquire the global at 0x128C4FD0 (0xE943178, lock inc 0x128C5030, 0xE94319C), read rsi=[0x128C5038], save rdi at [rbp+0x180]; if the helper is missing or [rsi]!=1 take the slow-init path 0x53E6D2C, else lock inc [rax+8], reload rsi/r14=[0x128C5040] and jump to 0x53E72BC.

```
0x53e6cce  lea r12,[0x128C4FD0]
0x53e6cd5  mov rcx,r12
0x53e6cd8  call 0xE943178
0x53e6cdd  lock inc qword ptr [0x128C5030]
0x53e6ce5  mov rcx,r12
0x53e6ce8  call 0xE94319C
0x53e6ced  mov rsi,[0x128C5038]
0x53e6cf4  test rsi,rsi
0x53e6cf7  mov [rbp+0x180],rdi
0x53e6cfe  je short 0x53E6D2C
0x53e6d00  cmp byte ptr [rsi],1
0x53e6d03  jne short 0x53E6D2C
0x53e6d05  mov rax,[0x128C5040]
0x53e6d0c  test rax,rax
0x53e6d0f  je 0x53E72B9
0x53e6d15  lock inc dword ptr [rax+8]
0x53e6d19  mov rsi,[0x128C5038]
0x53e6d20  mov r14,[0x128C5040]
0x53e6d27  jmp 0x53E72BC
```

### 0x53e6d2c..0x53e6d97: Slow path: zero the local shared-state slots ([rbp+0x188..0x1A8]) and init them via 0x3B2020(0x128C4FD0); reload the element array bounds rbx=[r13+0x5F0], rsi=[r13+0x5F8], set r14=[rbp+0x1D0]+0x10, xmm6=[0xEF3F050], r15=[rbp-0x38]; loop head: advance rbx by 0x14 per element, exit to 0x53E70FE when rbx==rsi.

```
0x53e6d2c  mov qword ptr [rbp+0x188],0
0x53e6d37  mov byte ptr [rbp+0x190],0
0x53e6d3e  xorps xmm0,xmm0
0x53e6d41  movups [rbp+0x198],xmm0
0x53e6d48  mov qword ptr [rbp+0x1A8],0
0x53e6d53  lea rcx,[0x128C4FD0]
0x53e6d5a  call 0x3B2020
0x53e6d5f  mov rbx,[r13+0x5F0]
0x53e6d66  mov rsi,[r13+0x5F8]
0x53e6d6d  mov rax,[rbp+0x1D0]
0x53e6d74  lea r14,[rax+0x10]
0x53e6d78  movaps xmm6,[0xEF3F050]
0x53e6d7f  lea r15,[rbp-0x38]
0x53e6d83  jmp short 0x53E6D94
0x53e6d85  nop [rax+rax]
0x53e6d90  add rbx,0x14
0x53e6d94  cmp rbx,rsi
0x53e6d97  je 0x53E70FE
```

### 0x53e6d9d..0x53e6dd8: rdi = [[rbp+0x1D0]+0x18] queue object, r12 = rdi+0x40 sub-object; set [rdi+0x78]=1; pop the front element by ring arithmetic (tail [rdi+0x60]+head [rdi+0x58], dec, and mask [rdi+0x50], table [rdi+0x48]) and call 0x53D0BE0(r12) on it.

```
0x53e6d9d  mov rax,[rbp+0x1D0]
0x53e6da4  mov rdi,[rax+0x18]
0x53e6da8  lea r12,[rdi+0x40]
0x53e6dac  mov byte ptr [rdi+0x78],1
0x53e6db0  mov rax,[rdi+0x60]
0x53e6db4  mov rcx,[rdi+0x58]
0x53e6db8  add rax,rcx
0x53e6dbb  dec rax
0x53e6dbe  mov rcx,[rdi+0x48]
0x53e6dc2  mov rdx,[rdi+0x50]
0x53e6dc6  dec rdx
0x53e6dc9  and rdx,rax
0x53e6dcc  mov rdx,[rcx+rdx*8]
0x53e6dd0  mov rcx,r12
0x53e6dd3  call 0x53D0BE0
0x53e6dd8  nop
```

### 0x53e6dd9..0x53e6e27: Pop the front element again with the same ring arithmetic, remember r12 at [rbp+0x1B0] and the element matrix pointer rax at [rbp+0x1B8], set [rdi+0x78]=1; load the three cached camera floats [rbp+0x1C0], [rbp+0x1C4], [rbp+0x1C8] and splat/negate them (xorps xmm0,xmm6).

```
0x53e6dd9  mov rax,[rdi+0x60]
0x53e6ddd  mov rcx,[rdi+0x58]
0x53e6de1  add rax,rcx
0x53e6de4  dec rax
0x53e6de7  mov rcx,[rdi+0x48]
0x53e6deb  mov rdx,[rdi+0x50]
0x53e6def  dec rdx
0x53e6df2  and rdx,rax
0x53e6df5  mov rax,[rcx+rdx*8]
0x53e6df9  mov [rbp+0x1B0],r12
0x53e6e00  mov [rbp+0x1B8],rax
0x53e6e07  mov byte ptr [rdi+0x78],1
0x53e6e0b  movss xmm0,[rbp+0x1C0]
0x53e6e13  movss xmm1,[rbp+0x1C4]
0x53e6e1b  movss xmm2,[rbp+0x1C8]
0x53e6e23  shufps xmm0,xmm0,0
0x53e6e27  xorps xmm0,xmm6
```

### 0x53e6e2a..0x53e6e57: Matrix row 3 transform: row3 = row0*(-x) - row1*(y) - row2*(z) + row3 using the splatted camera floats, store back [rax+0x30], set [rdi+0x78]=1.

```
0x53e6e2a  movups xmm3,[rax]
0x53e6e2d  mulps xmm3,xmm0
0x53e6e30  movups xmm0,[rax+0x10]
0x53e6e34  movups xmm4,[rax+0x20]
0x53e6e38  movups xmm5,[rax+0x30]
0x53e6e3c  shufps xmm1,xmm1,0
0x53e6e40  mulps xmm1,xmm0
0x53e6e43  subps xmm3,xmm1
0x53e6e46  shufps xmm2,xmm2,0
0x53e6e4a  mulps xmm2,xmm4
0x53e6e4d  subps xmm3,xmm2
0x53e6e50  addps xmm3,xmm5
0x53e6e53  movups [rax+0x30],xmm3
0x53e6e57  mov byte ptr [rdi+0x78],1
```

### 0x53e6e5b..0x53e6e9b: Matrix row 3 second transform with the element floats [rbx+4], [rbx+8], [rbx+0xC]: row3 = row0*f0 + row1*f1 + row2*f2 + row3 (f2 splatted over row2 first), store back [rax+0x30], set [rdi+0x78]=1.

```
0x53e6e5b  movss xmm0,[rbx+4]
0x53e6e60  movss xmm1,[rbx+8]
0x53e6e65  movss xmm2,[rbx+0xC]
0x53e6e6a  shufps xmm2,xmm2,0
0x53e6e6e  movups xmm3,[rax]
0x53e6e71  movups xmm4,[rax+0x10]
0x53e6e75  movups xmm5,[rax+0x20]
0x53e6e79  mulps xmm5,xmm2
0x53e6e7c  movups xmm2,[rax+0x30]
0x53e6e80  shufps xmm1,xmm1,0
0x53e6e84  mulps xmm1,xmm4
0x53e6e87  shufps xmm0,xmm0,0
0x53e6e8b  mulps xmm0,xmm3
0x53e6e8e  addps xmm0,xmm1
0x53e6e91  addps xmm0,xmm5
0x53e6e94  addps xmm0,xmm2
0x53e6e97  movups [rax+0x30],xmm0
0x53e6e9b  mov byte ptr [rdi+0x78],1
```

### 0x53e6e9f..0x53e6ec7: Scale rows 0-2 of the matrix by the splatted element float [rbx+0x10] and store them back ([rax], [rax+0x10], [rax+0x20]); then r12 = [r13+0x608] (first pass object).

```
0x53e6e9f  movss xmm0,[rbx+0x10]
0x53e6ea4  shufps xmm0,xmm0,0
0x53e6ea8  movups xmm1,[rax]
0x53e6eab  movups xmm2,[rax+0x10]
0x53e6eaf  movups xmm3,[rax+0x20]
0x53e6eb3  mulps xmm1,xmm0
0x53e6eb6  movups [rax],xmm1
0x53e6eb9  mulps xmm2,xmm0
0x53e6ebc  movups [rax+0x10],xmm2
0x53e6ec0  mulps xmm3,xmm0
0x53e6ec3  movups [rax+0x20],xmm3
0x53e6ec7  mov r12,[r13+0x608]
```

### 0x53e6ece..0x53e6f1a: First pass: clear the result flag bytes [rbp+0x1F0]/[rbp+0x168]; zero the 0x148-byte buffer at r15 via 0xEEC6ED0(rcx=r15, edx=0, r8d=0x148); set the out params ([rsp+0x40]=[rbp+0x130], [rsp+0x30]=[rbp+0x1D8]) and call 0x4DEF480(rcx=[r13+0x608], rdx=r14, r8=[rbp+0x170], r9=r15).

```
0x53e6ece  mov byte ptr [rbp+0x1F0],0
0x53e6ed5  mov byte ptr [rbp+0x168],0
0x53e6edc  mov r8d,0x148
0x53e6ee2  mov rcx,r15
0x53e6ee5  xor edx,edx
0x53e6ee7  call 0xEEC6ED0
0x53e6eec  nop
0x53e6eed  lea rax,[rbp+0x130]
0x53e6ef4  mov [rsp+0x40],rax
0x53e6ef9  lea rax,[rbp+0x1D8]
0x53e6f00  mov [rsp+0x30],rax
0x53e6f05  mov rcx,r12
0x53e6f08  mov rdx,r14
0x53e6f0b  mov r8,[rbp+0x170]
0x53e6f12  mov r9,r15
0x53e6f15  call 0x4DEF480
0x53e6f1a  nop
```

### 0x53e6f1b..0x53e6f79: Switch on the status byte [rbp+0x1F0] through jump table 0xF24A198 (values >3 skip the switch); the release branch drops the returned shared_ptr: lock dec [r12+8], on zero delete via vtable ([r12]→[rax] slot and [0xF99FFA0]), then lock dec [r12+0xC], on zero delete via slot [rax+8].

```
0x53e6f1b  movzx eax,byte ptr [rbp+0x1F0]
0x53e6f22  cmp rax,3
0x53e6f26  ja 0x53E6FC0
0x53e6f2c  lea rcx,[0xF24A198]
0x53e6f33  movsxd rax,[rcx+rax*4]
0x53e6f37  add rax,rcx
0x53e6f3a  jmp rax
0x53e6f3c  mov r12,[rbp+0x1E8]
0x53e6f43  test r12,r12
0x53e6f46  je short 0x53E6FC0
0x53e6f48  lock dec dword ptr [r12+8]
0x53e6f4e  jne short 0x53E6FC0
0x53e6f50  mov rax,[r12]
0x53e6f54  mov rax,[rax]
0x53e6f57  mov rcx,r12
0x53e6f5a  call qword ptr [0xF99FFA0]
0x53e6f60  lock dec dword ptr [r12+0xC]
0x53e6f66  jne short 0x53E6FC0
0x53e6f68  mov rax,[r12]
0x53e6f6c  mov rax,[rax+8]
0x53e6f70  mov rcx,r12
0x53e6f73  call qword ptr [0xF99FFA0]
0x53e6f79  jmp short 0x53E6FC0
```

### 0x53e6f7b..0x53e6fb6: Release the holder written by the pass ([rbp+0x1D8]): if non-null, lock dec the inner object refcount [rdx+0xC]; on zero delete through the vtable chain ([rdx]→[rax+8]) with [0xF99FFA0]; then free the outer object with 0xE935700(edx=0x20).

```
0x53e6f7b  mov rcx,[rbp+0x1D8]
0x53e6f82  test rcx,rcx
0x53e6f85  je short 0x53E6FC0
0x53e6f87  mov rdx,[rcx+8]
0x53e6f8b  test rdx,rdx
0x53e6f8e  je short 0x53E6FAC
0x53e6f90  lock dec dword ptr [rdx+0xC]
0x53e6f94  jne short 0x53E6FAC
0x53e6f96  mov rax,[rdx]
0x53e6f99  mov rax,[rax+8]
0x53e6f9d  mov rdi,rcx
0x53e6fa0  mov rcx,rdx
0x53e6fa3  call qword ptr [0xF99FFA0]
0x53e6fa9  mov rcx,rdi
0x53e6fac  mov edx,0x20
0x53e6fb1  call 0xE935700
0x53e6fb6  nop [rax+rax]
```

### 0x53e6fc0..0x53e7013: Second pass: identical to the first but with r12=[r13+0x608] and r8=[rbp+0x178]; buffer r15 re-zeroed by 0xEEC6ED0, then 0x4DEF480.

```
0x53e6fc0  mov r12,[r13+0x608]
0x53e6fc7  mov byte ptr [rbp+0x1F0],0
0x53e6fce  mov byte ptr [rbp+0x168],0
0x53e6fd5  mov r8d,0x148
0x53e6fdb  mov rcx,r15
0x53e6fde  xor edx,edx
0x53e6fe0  call 0xEEC6ED0
0x53e6fe5  nop
0x53e6fe6  lea rax,[rbp+0x130]
0x53e6fed  mov [rsp+0x40],rax
0x53e6ff2  lea rax,[rbp+0x1D8]
0x53e6ff9  mov [rsp+0x30],rax
0x53e6ffe  mov rcx,r12
0x53e7001  mov rdx,r14
0x53e7004  mov r8,[rbp+0x178]
0x53e700b  mov r9,r15
0x53e700e  call 0x4DEF480
0x53e7013  nop
```

### 0x53e7014..0x53e7072: Second switch on [rbp+0x1F0] via jump table 0xF24A1A8; same shared_ptr release path (lock dec [r12+8]/[r12+0xC], vtable deletes).

```
0x53e7014  movzx eax,byte ptr [rbp+0x1F0]
0x53e701b  cmp rax,3
0x53e701f  ja 0x53E70B0
0x53e7025  lea rcx,[0xF24A1A8]
0x53e702c  movsxd rax,[rcx+rax*4]
0x53e7030  add rax,rcx
0x53e7033  jmp rax
0x53e7035  mov r12,[rbp+0x1E8]
0x53e703c  test r12,r12
0x53e703f  je short 0x53E70B0
0x53e7041  lock dec dword ptr [r12+8]
0x53e7047  jne short 0x53E70B0
0x53e7049  mov rax,[r12]
0x53e704d  mov rax,[rax]
0x53e7050  mov rcx,r12
0x53e7053  call qword ptr [0xF99FFA0]
0x53e7059  lock dec dword ptr [r12+0xC]
0x53e705f  jne short 0x53E70B0
0x53e7061  mov rax,[r12]
0x53e7065  mov rax,[rax+8]
0x53e7069  mov rcx,r12
0x53e706c  call qword ptr [0xF99FFA0]
0x53e7072  jmp short 0x53E70B0
```

### 0x53e7074..0x53e70af: Release the second [rbp+0x1D8] holder: lock dec inner [rdx+0xC], vtable delete ([rdx]→[rax+8]), then 0xE935700(edx=0x20) on the outer.

```
0x53e7074  mov rcx,[rbp+0x1D8]
0x53e707b  test rcx,rcx
0x53e707e  je short 0x53E70B0
0x53e7080  mov rdx,[rcx+8]
0x53e7084  test rdx,rdx
0x53e7087  je short 0x53E70A5
0x53e7089  lock dec dword ptr [rdx+0xC]
0x53e708d  jne short 0x53E70A5
0x53e708f  mov rax,[rdx]
0x53e7092  mov rax,[rax+8]
0x53e7096  mov rdi,rcx
0x53e7099  mov rcx,rdx
0x53e709c  call qword ptr [0xF99FFA0]
0x53e70a2  mov rcx,rdi
0x53e70a5  mov edx,0x20
0x53e70aa  call 0xE935700
0x53e70af  nop
```

### 0x53e70b0..0x53e70f9: End-of-element bookkeeping on the popped sub-object ([rbp+0x1B0] = rdi+0x40): set [rax+0x38]=1; if byte [rax+0x30] is set and (count [rax+0x20]-1) <= [rax+0x28], clear [rax+0x30]; decrement [rax+0x20]; when it hits 0, zero [rax+0x18]; loop back to 0x53E6D90.

```
0x53e70b0  mov rax,[rbp+0x1B0]
0x53e70b7  test rax,rax
0x53e70ba  je 0x53E6D90
0x53e70c0  mov byte ptr [rax+0x38],1
0x53e70c4  cmp byte ptr [rax+0x30],0
0x53e70c8  je short 0x53E70E0
0x53e70ca  mov rcx,[rax+0x20]
0x53e70ce  lea rdx,[rcx-1]
0x53e70d2  cmp rdx,[rax+0x28]
0x53e70d6  ja short 0x53E70E4
0x53e70d8  mov byte ptr [rax+0x30],0
0x53e70dc  jmp short 0x53E70E4
0x53e70de  xchg ax,ax
0x53e70e0  mov rcx,[rax+0x20]
0x53e70e4  dec rcx
0x53e70e7  mov [rax+0x20],rcx
0x53e70eb  jne 0x53E6D90
0x53e70f1  mov qword ptr [rax+0x18],0
0x53e70f9  jmp 0x53E6D90
```

### 0x53e70fe..0x53e7113: Loop finished: rax = [[rbp+0x1D0]+0x30] output object; store the cached 16 bytes [rbp+0x120] to [rax] and set the byte [rax+0x10] = 1.

```
0x53e70fe  mov rax,[rbp+0x1D0]
0x53e7105  mov rax,[rax+0x30]
0x53e7109  movaps xmm0,[rbp+0x120]
0x53e7110  movups [rax],xmm0
0x53e7113  mov byte ptr [rax+0x10],1
```

### 0x53e7117..0x53e716e: Third pass: r15=[r13+0x618]; clear the status bytes [rbp+0x1F0]/[rbp+0x168]; rbx=[rbp-0x38]; zero the 0x148-byte buffer via 0xEEC6ED0(rcx=rbx, edx=0, r8d=0x148); set the out params ([rsp+0x40]=[rbp+0x130], [rsp+0x30]=[rbp+0x1D8]) and call 0x4DEF480(rcx=r15, rdx=r14, r8=[rbp+0x180], r9=rbx). r8=[rbp+0x180] is the rdi=[r13+0x648] pointer cached at 0x53e6cf7 [V].

```
0x53e7117  mov r15,[r13+0x618]
0x53e711e  mov byte ptr [rbp+0x1F0],0
0x53e7125  mov byte ptr [rbp+0x168],0
0x53e712c  lea rbx,[rbp-0x38]
0x53e7130  mov r8d,0x148
0x53e7136  mov rcx,rbx
0x53e7139  xor edx,edx
0x53e713b  call 0xEEC6ED0
0x53e7140  nop
0x53e7141  lea rax,[rbp+0x130]
0x53e7148  mov [rsp+0x40],rax
0x53e714d  lea rax,[rbp+0x1D8]
0x53e7154  mov [rsp+0x30],rax
0x53e7159  mov rcx,r15
0x53e715c  mov rdx,r14
0x53e715f  mov r8,[rbp+0x180]
0x53e7166  mov r9,rbx
0x53e7169  call 0x4DEF480
0x53e716e  nop
```

### 0x53e716f..0x53e71c7: Third switch on the status byte [rbp+0x1F0] via jump table 0xF24A1B8 (values >3 skip the switch). Decoded [V jt]: tag 0 -> 0x53E7204 (skip), tag 1 -> 0x53E71C9 (release the [rbp+0x1D8] holder), tags 2/3 -> 0x53E7190 (release the returned shared_ptr). Release branch on rsi=[rbp+0x1E8]: lock dec [rsi+8], on zero delete via vtable ([rsi]→[rax] slot and [0xF99FFA0]), then lock dec [rsi+0xC], on zero delete via slot [rax+8].

```
0x53e716f  movzx eax,byte ptr [rbp+0x1F0]
0x53e7176  cmp rax,3
0x53e717a  ja 0x53E7204
0x53e7180  lea rcx,[0xF24A1B8]
0x53e7187  movsxd rax,[rcx+rax*4]
0x53e718b  add rax,rcx
0x53e718e  jmp rax
0x53e7190  mov rsi,[rbp+0x1E8]
0x53e7197  test rsi,rsi
0x53e719a  je short 0x53E7204
0x53e719c  lock dec dword ptr [rsi+8]
0x53e71a0  jne short 0x53E7204
0x53e71a2  mov rax,[rsi]
0x53e71a5  mov rax,[rax]
0x53e71a8  mov rcx,rsi
0x53e71ab  call qword ptr [0xF99FFA0]
0x53e71b1  lock dec dword ptr [rsi+0xC]
0x53e71b5  jne short 0x53E7204
0x53e71b7  mov rax,[rsi]
0x53e71ba  mov rax,[rax+8]
0x53e71be  mov rcx,rsi
0x53e71c1  call qword ptr [0xF99FFA0]
0x53e71c7  jmp short 0x53E7204
```

### 0x53e71c9..0x53e7203: Release the third [rbp+0x1D8] holder (table tag 1): if non-null, lock dec the inner object refcount [rdx+0xC]; on zero delete through the vtable chain ([rdx]→[rax+8]) with [0xF99FFA0]; then free the outer object with 0xE935700(edx=0x20).

```
0x53e71c9  mov rcx,[rbp+0x1D8]
0x53e71d0  test rcx,rcx
0x53e71d3  je short 0x53E7204
0x53e71d5  mov rdx,[rcx+8]
0x53e71d9  test rdx,rdx
0x53e71dc  je short 0x53E71FA
0x53e71de  lock dec dword ptr [rdx+0xC]
0x53e71e2  jne short 0x53E71FA
0x53e71e4  mov rax,[rdx]
0x53e71e7  mov rax,[rax+8]
0x53e71eb  mov rsi,rcx
0x53e71ee  mov rcx,rdx
0x53e71f1  call qword ptr [0xF99FFA0]
0x53e71f7  mov rcx,rsi
0x53e71fa  mov edx,0x20
0x53e71ff  call 0xE935700
0x53e7204  mov r14,[rbp+0x1A0]
```

### 0x53e7204..0x53e7288: Post-loop release of the slow-init helper image ([rbp+0x198]/[rbp+0x1A0]/[rbp+0x1A8], written at 0x53e72bc): r14=[rbp+0x1A0]; zero [rbp+0x198] with movups; release r14 (lock dec [r14+8], on zero delete via vtable [r14]→[rax] with [0xF99FFA0], then lock dec [r14+0xC], on zero delete via slot [rax+8]); then rsi=[rbp+0x1A0], [rbp+0x1A8]=0, and release rsi the same way. [I] the +8 and +0xC counters are the two refcount halves of the same helper object (acquired once at 0x53e6d15); [rbp+0x198]=rsi and [rbp+0x1A8]=r15 are dropped here without a release call.

```
0x53e7204  mov r14,[rbp+0x1A0]
0x53e720b  xorps xmm0,xmm0
0x53e720e  movups [rbp+0x198],xmm0
0x53e7215  test r14,r14
0x53e7218  je short 0x53E7289
0x53e721a  lock dec dword ptr [r14+8]
0x53e721f  jne short 0x53E7247
0x53e7221  mov rax,[r14]
0x53e7224  mov rax,[rax]
0x53e7227  mov rcx,r14
0x53e722a  call qword ptr [0xF99FFA0]
0x53e7230  lock dec dword ptr [r14+0xC]
0x53e7235  jne short 0x53E7247
0x53e7237  mov rax,[r14]
0x53e723a  mov rax,[rax+8]
0x53e723e  mov rcx,r14
0x53e7241  call qword ptr [0xF99FFA0]
0x53e7247  mov rsi,[rbp+0x1A0]
0x53e724e  mov qword ptr [rbp+0x1A8],0
0x53e7259  test rsi,rsi
0x53e725c  je short 0x53E7289
0x53e725e  lock dec dword ptr [rsi+8]
0x53e7262  jne short 0x53E7289
0x53e7264  mov rax,[rsi]
0x53e7267  mov rax,[rax]
0x53e726a  mov rcx,rsi
0x53e726d  call qword ptr [0xF99FFA0]
0x53e7273  lock dec dword ptr [rsi+0xC]
0x53e7277  jne short 0x53E7289
0x53e7279  mov rax,[rsi]
0x53e727c  mov rax,[rax+8]
0x53e7280  mov rcx,rsi
0x53e7283  call qword ptr [0xF99FFA0]
0x53e7289  cmp byte ptr [rbp+0x190],1
0x53e7290  jne short 0x53E729E
0x53e7292  mov rcx,[rbp+0x188]
0x53e7299  call 0x3B2020
```

### 0x53e729e..0x53e72b8: Epilogue: restore xmm6 from [rbp+0x200], add rsp,0x298, pop rbx,rdi,rsi,r12,r13,r14,r15,rbp, ret.

```
0x53e729e  movaps xmm6,[rbp+0x200]
0x53e72a5  add rsp,0x298
0x53e72ac  pop rbx
0x53e72ad  pop rdi
0x53e72ae  pop rsi
0x53e72af  pop r12
0x53e72b1  pop r13
0x53e72b3  pop r14
0x53e72b5  pop r15
0x53e72b7  pop rbp
0x53e72b8  ret
```

### 0x53e72b9..0x53e7308: Slow-init tail: if the helper was null, r14d=0; r15=[0x128C5048]; cache the helper image ([rbp+0x188]=r12, [rbp+0x190]=1, [rbp+0x198]=rsi, [rbp+0x1A0]=r14, [rbp+0x1A8]=r15); if rsi is null or [rsi]!=1 jump to the loop setup 0x53E6D5F; else virtual call slot [rax+8] on r15 through [0xF99FFA0] and, if it returns 0, also jump to 0x53E6D5F.

```
0x53e72b9  xor r14d,r14d
0x53e72bc  mov r15,[0x128C5048]
0x53e72c3  mov [rbp+0x188],r12
0x53e72ca  mov byte ptr [rbp+0x190],1
0x53e72d1  mov [rbp+0x198],rsi
0x53e72d8  mov [rbp+0x1A0],r14
0x53e72df  mov [rbp+0x1A8],r15
0x53e72e6  test rsi,rsi
0x53e72e9  je 0x53E6D5F
0x53e72ef  cmp byte ptr [rsi],1
0x53e72f2  jne 0x53E6D5F
0x53e72f8  mov rax,[r15]
0x53e72fb  mov rax,[rax+8]
0x53e72ff  mov rcx,r15
0x53e7302  call qword ptr [0xF99FFA0]
0x53e7308  nop
```

### 0x53e7309..0x53e737a: Event-data build: r13 += 0x5E0 (so the record will carry a pointer 0x10 before the element array begin [r13+0x5F0]); pop the front queue element again with the same ring arithmetic on [[rbp+0x1D0]+0x18] (tail [rax+0x60]+head [rax+0x58], dec, mask [rax+0x50], table [rax+0x48]); assert [rsi]!=0 (else fault-write 0xDEADC0DE); build the record block [rbp+0x1D8]=r13, [rbp+0x1E0]=rax (popped element), [rbp+0x1E8]=&[rbp+0x1C0] (the cached camera floats); read the flag byte [[rbp+0x1D0]+0x74] and store it as a word at [rbp+0x1F0] (overwriting the pass status slot [V 0x53e737a]).

```
0x53e7309  test al,al
0x53e730b  je 0x53E6D5F
0x53e7311  add r13,0x5E0
0x53e7318  mov rax,[rbp+0x1D0]
0x53e731f  mov rax,[rax+0x18]
0x53e7323  mov rcx,[rax+0x60]
0x53e7327  mov rdx,[rax+0x58]
0x53e732b  add rcx,rdx
0x53e732e  dec rcx
0x53e7331  mov rdx,[rax+0x48]
0x53e7335  mov rax,[rax+0x50]
0x53e7339  dec rax
0x53e733c  and rax,rcx
0x53e733f  mov rax,[rdx+rax*8]
0x53e7343  cmp byte ptr [rsi],0
0x53e7346  jne short 0x53E7353
0x53e7348  mov dword ptr [0],0xDEADC0DE
0x53e7353  mov [rbp+0x1D8],r13
0x53e735a  mov [rbp+0x1E0],rax
0x53e7361  lea rax,[rbp+0x1C0]
0x53e7368  mov [rbp+0x1E8],rax
0x53e736f  mov rax,[rbp+0x1D0]
0x53e7376  movzx eax,byte ptr [rax+0x74]
0x53e737a  mov [rbp+0x1F0],ax
```

### 0x53e7381..0x53e73a0: Check the TLS counter [0x129C6D58] against the per-slot count ([gs:0x58] walk, index [0x128767C8], cmp [rcx+4]); if over limit jump to 0x53E7438.

```
0x53e7381  mov eax,[0x129C6D58]
0x53e7387  mov ecx,[0x128767C8]
0x53e738d  mov rdx,gs:[0x58]
0x53e7396  mov rcx,[rdx+rcx*8]
0x53e739a  cmp eax,[rcx+4]
0x53e73a0  jg 0x53E7438
```

### 0x53e73a6..0x53e7433: Start the event record ([rbp+0x130]=0x129C6C20, flag byte [rbp+0x138]=0, rsi=[rbp+0x140], [rbp+0x148]=0, [rbp]=0); call 0x39A7D40(rdx=rsi, r8=[rbp-0x38]) to fetch an event key (result byte saved at [rbp+0x138]) — r8 points at the 0x148 pass-output buffer at [rbp-0x38], which is consumed here and then reused for the tagged record [I]; build the tagged record [rbp-0x38] = pointer to the [rbp+0x1D8] block with tag byte 4 at [rbp-0x30]; call the vtable slot +0x360 on r15 with it; if the saved byte==1, call 0x77A2500(0x1244FD00, rdx=rsi, r8=[rbp+0x130]+0x60); jump to 0x53E720B.

```
0x53e73a6  lea rcx,[0x129C6C20]
0x53e73ad  mov [rbp+0x130],rcx
0x53e73b4  mov byte ptr [rbp+0x138],0
0x53e73bb  lea rsi,[rbp+0x140]
0x53e73c2  mov qword ptr [rbp+0x148],0
0x53e73cd  mov byte ptr [rbp],0
0x53e73d1  lea r8,[rbp-0x38]
0x53e73d5  mov rdx,rsi
0x53e73d8  call 0x39A7D40
0x53e73dd  nop
0x53e73de  mov [rbp+0x138],al
0x53e73e4  lea rax,[rbp+0x1D8]
0x53e73eb  mov [rbp-0x38],rax
0x53e73ef  mov byte ptr [rbp-0x30],4
0x53e73f3  mov rax,[r15]
0x53e73f6  mov rax,[rax+0x360]
0x53e73fd  lea rdx,[rbp-0x38]
0x53e7401  mov rcx,r15
0x53e7404  call qword ptr [0xF99FFA0]
0x53e740a  nop
0x53e740b  cmp byte ptr [rbp+0x138],1
0x53e7412  jne 0x53E720B
0x53e7418  mov r8,[rbp+0x130]
0x53e741f  add r8,0x60
0x53e7423  lea rcx,[0x1244FD00]
0x53e742a  mov rdx,rsi
0x53e742d  call 0x77A2500
0x53e7432  nop
0x53e7433  jmp 0x53E720B
```

### 0x53e7438..0x53e74c7: TLS counter exceeded path: call 0xE938CB0(0x129C6D58); if the counter became 0xFFFFFFFF, build a fatal-error record (message ptr 0xF52E07A, length 0x15, xmm data from 0xF0BCBF8 stored at [rbp+0x110], source 0xF248FD0) and call 0x2FE330(0x129C6C20, ...), then 0xE935740(0x53DED50) and 0xE938D70(0x129C6D58); return to 0x53E73A6 either way; padding nop.

```
0x53e7438  lea rcx,[0x129C6D58]
0x53e743f  call 0xE938CB0
0x53e7444  cmp dword ptr [0x129C6D58],0xFFFFFFFF
0x53e744b  jne 0x53E73A6
0x53e7451  lea rax,[0xF52E07A]
0x53e7458  mov [rbp+0x1B0],rax
0x53e745f  mov qword ptr [rbp+0x1B8],0x15
0x53e746a  movups xmm0,[0xF0BCBF8]
0x53e7471  movaps [rbp+0x110],xmm0
0x53e7478  lea rax,[0xF248FD0]
0x53e747f  mov [rsp+0x28],rax
0x53e7484  mov dword ptr [rsp+0x20],0
0x53e748c  lea rcx,[0x129C6C20]
0x53e7493  lea rdx,[rbp+0x110]
0x53e749a  lea r9,[rbp+0x1B0]
0x53e74a1  mov r8b,1
0x53e74a4  call 0x2FE330
0x53e74a9  nop
0x53e74aa  lea rcx,[0x53DED50]
0x53e74b1  call 0xE935740
0x53e74b6  lea rcx,[0x129C6D58]
0x53e74bd  call 0xE938D70
0x53e74c2  jmp 0x53E73A6
0x53e74c7  nop [rax+rax]
```

## Field map ([reg+off])

### Function 1: PlayerVision effect (rcx = effect object, r13 = [rcx+8] payload)

- [rcx+8] ptr 8 R — payload object → r13 [V 0x53e62fc]
- [r13+0x4D4] f32 4 R — strength term (→ xmm8, stored to [rbp+0x4C]) [V 0x53e6552]
- [r13+0x64C] f32 4 R — converted via 0xEEC75A0, packed [V 0x53e647e]
- [r13+0x650] f32 4 R — converted via 0xEEC75A0, packed [V 0x53e6487]
- [r13+0x654] f32 4 R — converted via 0xEEC75A0, packed [V 0x53e6475]
- [r13+0x978] ptr 8 R — arg0 of 0x32D0F30 [V 0x53e646e]
- [r13+0x998] ptr 8 R — object A [V 0x53e63fb]; through A: [A+0x64] f32 R [V 0x53e652a], [A+0x68] f32 R [V 0x53e652f], [A+0x390] i32 4 R [V 0x53e64fc]
- [r15] u8 1 R — validity flag, must be 1; 0 faults (0xDEADC0DE at 0x53e6695) [V 0x53e632b, 0x53e63d8, 0x53e668f]
- refcounts: [rax+8] i32 lock inc on acquire [V 0x53e633d]; release path: [rsi+8] lock dec [V 0x53e6749], [rsi+0xC] lock dec [V 0x53e675e] (twice: 0x53e6736 block and 0x53e6780 block)
- vtable slots: [rdi]→slot +8 (predicate, result gates the body) [V 0x53e63e5..0x53e63ec]; [rbx]→slot +0xF0 [V 0x53e6419], slot +0x5F0 [V 0x53e64e4]; [rdi]→slot +0x360 posts the tagged record [V 0x53e6703..0x53e6711]
- lookup objects (0xBD11A0 edx=0x10/0x1A results rbx/rax): [rbx+4] u32 4 R, [rax+4] u32 4 R — dword ids compared, 0xFFFFFFFF = unset, winner kept in ecx [V 0x53e65b1, 0x53e65bd]
- stack image (rbp = rsp+0x80): [rbp+0x58] helper ptr / [rbp+0x60] u8 flag (holder, 0x3B2020-inited) [V 0x53e6351, 0x53e6359]; [rbp+0x68]/[rbp+0x70]/[rbp+0x78] helper image copies [V 0x53e63c3..0x53e63cb]; [rbp+0x38]/[rbp+0x40] packed converted ints [V 0x53e64aa, 0x53e64ba]; [rbp+0x86] u8 out byte of 0x32D0F30 [V 0x53e64d4]; [rbp+0x80] u8 copy of it [V 0x53e64db]; result block [rbp+0x44] u8, [rbp+0x48]/[rbp+0x4C]/[rbp+0x50]/[rbp+0x54] f32 [V 0x53e6676..0x53e668a]; event record [rbp+0x18] dispatcher 0x129C6360, [rbp+0x20] u8 key flag, [rbp+0x28]/[rbp+0x30] key buffer [V 0x53e66cc..0x53e66d8]; tagged record [rbp-0x50] ptr to result block, [rbp-0x48] tag byte 3, [rbp-0x18] u8 0 [V 0x53e66e0, 0x53e66f8, 0x53e66fc]

### Function 2: shadow producer (rcx = producer object, r13 = [rcx+0x10] source)

- [rcx+8] ptr 8 R — holder object, cached [rbp+0x1D0] [V 0x53e6c75]
- [rcx+0x10] ptr 8 R — source → r13 [V 0x53e6c5d]
- [r13+0xC] 8 R (movsd) — two floats cached at [rbp+0x1C0]/[rbp+0x1C4] [V 0x53e6c80]
- [r13+0x14] f32 4 R — cached [rbp+0x1C8] [V 0x53e6c8e]
- [r13+0x5E0] — base pointer stored into the event record ([rbp+0x1D8]=r13+0x5E0) [V 0x53e7311, 0x53e7353]; points 0x10 before the element array begin, contents not accessed here [I]
- [r13+0x5F0] / [r13+0x5F8] ptr 8 R — element array begin/end; rbx walks it with stride 0x14 [V 0x53e6c61, 0x53e6c68, 0x53e6d5f, 0x53e6d66, 0x53e6d90]
- element [rbx]: [rbx+4]/[rbx+8]/[rbx+0xC] f32 4 R — re-transform matrix row 3 [V 0x53e6e5b, 0x53e6e60, 0x53e6e65]; [rbx+0x10] f32 4 R — scales rows 0-2 [V 0x53e6e9f]
- matrix [rax] (popped queue element, saved [rbp+0x1B8]): rows [rax]/[rax+0x10]/[rax+0x20] RW 16 movups [V 0x53e6e2a..0x53e6ec3]; [rax+0x30] W 16 twice (camera-float transform, then element-float transform) [V 0x53e6e53, 0x53e6e97]
- queue rdi = [[holder]+0x18] [V 0x53e6da4, 0x53e731f]: [rdi+0x48] table R [V 0x53e6dbe, 0x53e7331], [rdi+0x50] mask R [V 0x53e6dc2, 0x53e7335], [rdi+0x58] head R [V 0x53e6db4, 0x53e7327], [rdi+0x60] tail R [V 0x53e6db0, 0x53e7323], [rdi+0x78] u8 W 1 (dirty flag, set 4x) [V 0x53e6dac, 0x53e6e07, 0x53e6e57, 0x53e6e9b]
- queue sub-object r12 = rdi+0x40 → arg0 of 0x53D0BE0 [V 0x53e6da8, 0x53e6dd3]; saved [rbp+0x1B0]; fields on it: [rax+0x18] W 0 [V 0x53e70f1], [rax+0x20] count RW [V 0x53e70ca, 0x53e70e7], [rax+0x28] limit R [V 0x53e70d2], [rax+0x30] u8 RW [V 0x53e70c4, 0x53e70d8], [rax+0x38] u8 W 1 [V 0x53e70c0]
- [r13+0x608] ptr 8 R — pass 1 and pass 2 objects [V 0x53e6ec7, 0x53e6fc0]; [r13+0x618] ptr 8 R — pass 3 object [V 0x53e7117]
- [r13+0x638]/[r13+0x640]/[r13+0x648] ptr 8 R — the r8 args of passes 2/1/3 [V 0x53e6c9c, 0x53e6caa, 0x53e6cb8]
- [r13+0x650] 16 R (movups) — cached [rbp+0x120], stored to the output object at the end [V 0x53e6cbf, 0x53e7109]
- [holder+0x30] ptr 8 R — output object [V 0x53e7105]; [out+0] W 16, [out+0x10] u8 W 1 [V 0x53e7110, 0x53e7113]
- [holder+0x74] u8 1 R — flag stored as a word at [rbp+0x1F0] [V 0x53e7376, 0x53e737a]
- [rsi] u8 R — helper validity (must be 1 / nonzero) [V 0x53e6d00, 0x53e72ef, 0x53e7343]
- refcounts: [rax+8] lock inc on acquire [V 0x53e6d15]; [r12+8]/[r12+0xC] lock dec (pass 1/2 shared_ptr) [V 0x53e6f48, 0x53e6f60], same for rsi pass 3 [V 0x53e719c, 0x53e71b1]; [rdx+0xC] lock dec (holder inner) [V 0x53e6f90, 0x53e71de]; [r14+8]/[r14+0xC] and [rsi+8]/[rsi+0xC] lock dec (post-loop helper release) [V 0x53e721a..0x53e7273]
- vtable slots: [r15]→slot +8 (predicate) [V 0x53e72fb..0x53e7302]; [r15]→slot +0x360 posts the tagged record [V 0x53e73f6..0x53e7404]; delete thunks via [obj]→[rax] / [rax+8] with [0xF99FFA0]
- stack image (rbp = rsp+0x80): [rbp+0x120] cached 16B block; event record [rbp+0x130] dispatcher 0x129C6C20, [rbp+0x138] u8 key flag, [rbp+0x140]/[rbp+0x148] key buffer, [rbp] u8 0 [V 0x53e73ad..0x53e73cd]; [rbp+0x170]/[rbp+0x178]/[rbp+0x180] pass r8 args [V 0x53e6cb1..0x53e6cf7]; helper image [rbp+0x188] ptr / [rbp+0x190] u8 flag / [rbp+0x198] 16B / [rbp+0x1A0] ptr / [rbp+0x1A8] ptr [V 0x53e6d2c..0x53e6d48, 0x53e72c3..0x53e72df]; [rbp+0x1B0] sub-object, [rbp+0x1B8] matrix ptr [V 0x53e6df9, 0x53e6e00]; [rbp+0x1C0]/[rbp+0x1C4]/[rbp+0x1C8] cached camera floats [V 0x53e6c86, 0x53e6c94]; [rbp+0x1D0] holder [V 0x53e6c79]; [rbp+0x1D8] record base (also the 0x4DEF480 out param via [rsp+0x30]) / [rbp+0x1E0] popped element / [rbp+0x1E8] ptr to camera floats [V 0x53e6ff9, 0x53e7353, 0x53e735a, 0x53e7368]; [rbp+0x1F0] u8 pass status / u16 holder flag (word store) [V 0x53e6f1b, 0x53e737a]; [rbp-0x38] 0x148-byte pass buffer, reused as the tagged record ([rbp-0x38] ptr, [rbp-0x30] tag byte 4) [V 0x53e712c, 0x53e73eb, 0x53e73ef]

## Callees

Function 1 (0x53E62B0):
- 0xE943178 / 0xE94319C — global-helper acquire pair around lock inc [0x128C5030] [V 0x53e630a..0x53e631a]
- 0x3B2020 — helper holder init / release [V 0x53e6364, 0x53e6373]
- 0xAA7FE0 — predicate on rbx (gates the id-lookup block) [V 0x53e640c]
- 0xBD11A0 — lookup, edx=0x10 and edx=0x1A [V 0x53e6432, 0x53e645c, 0x53e6586, 0x53e6597]
- 0xEEC75A0 — float convert (3 calls) [V 0x53e6490..0x53e64b1]
- 0x32D0F30 — byte query (rcx=r14, rdx=[rbp+0x86], r8=[rbp+0x38], r9=0) [V 0x53e64ce]
- 0x39A7D40 — event-key fetch [V 0x53e66eb]
- 0x77A2500 — (0x1244FD00, key, dispatcher+0x60) when key flag==1 [V 0x53e6730]
- 0xE938CB0 / 0xE938D70 — TLS counter (0x129C6498) check-path calls [V 0x53e67c8, 0x53e6837]
- 0x2FE330 — fatal-error report; 0xE935740 — companion call [V 0x53e681e, 0x53e682b]
- [0xF99FFA0] — indirect thunk for every vtable call and delete [V 0x53e63ec et al.]

Function 2 (0x53E6C30):
- 0xE943178 / 0xE94319C — same global-helper acquire pair [V 0x53e6cd8..0x53e6ce8]
- 0x3B2020 — helper holder init / release [V 0x53e6d5a, 0x53e7299]
- 0x53D0BE0 — called on the queue sub-object rdi+0x40 [V 0x53e6dd3]; meaning unknown [?]
- 0xEEC6ED0 — zero-fill (rcx=buffer, edx=0, r8d=0x148); memset-like [V 0x53e6ee7, 0x53e6fe0, 0x53e713b], semantics [I]
- 0x4DEF480 — the three transform passes (rcx=pass object, rdx=r14, r8=pass ptr, r9=buffer; out params [rsp+0x30]/[rsp+0x40]) [V 0x53e6f15, 0x53e700e, 0x53e7169]
- 0xE935700 — free outer holder (edx=0x20) [V 0x53e6fb1, 0x53e70aa, 0x53e71ff]
- 0x39A7D40 — event-key fetch from the pass buffer [V 0x53e73d8]
- 0x77A2500 — (0x1244FD00, key, dispatcher+0x60) when key flag==1 [V 0x53e742d]
- 0xE938CB0 / 0xE938D70 — TLS counter (0x129C6D58) check-path calls [V 0x53e743f, 0x53e74bd]
- 0x2FE330 — fatal-error report; 0xE935740 — companion call [V 0x53e74a4, 0x53e74b1]
- [0xF99FFA0] — indirect thunk for every vtable call and delete [V 0x53e7302 et al.]

## OPEN questions

- [UNVERIFIED: 0x53e7311] Meaning of the record pointer r13+0x5E0: it points 0x10 before the element array begin [r13+0x5F0]; the region is never read or written inside this function.
- [UNVERIFIED: 0x53e6f15] What the three 0x4DEF480 passes compute (objects [r13+0x608], [r13+0x608], [r13+0x618]; r8 = [r13+0x640]/[r13+0x638]/[r13+0x648]); the 0x148-byte output buffer layout at [rbp-0x38] is opaque here — only its address is consumed by 0x39A7D40 at 0x53e73d8.
- [UNVERIFIED: 0x53e6dd3] Semantics of 0x53D0BE0 on the queue sub-object rdi+0x40.
- [I] The queue front is popped twice per element with identical ring arithmetic (0x53e6db0..0x53e6dd3 and 0x53e7323..0x53e733f) and no head/tail write in between, so both pops see the same element: the first feeds 0x53D0BE0, the second feeds the matrix transform and event record.
- [I] xmm6 = [0xEF3F050] (0x53e6d78) is used only as a splat/negate mask via xorps at 0x53e6e27; the 16-byte constant's value was not read.
- [?] Semantic names for: element floats +4/+8/+0xC/+0x10, matrix layout, the [holder+0x74] flag, and the distinction between the three pass slots.

## TOOL REQUESTS
None

## Field map table (offset | size | site | instr | meaning)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| [rcx+8] payload (F1) | 8 | F1 0x53e62fc | 0x53e62fc  mov r13,[rcx+8] | effect payload object -> r13 |
| [rcx+8] holder (F2) | 8 | F2 0x53e6c75 | 0x53e6c75  mov rax,[rcx+8] | holder object, cached at [rbp+0x1D0] |
| [rcx+0x10] (F2) | 8 | F2 0x53e6c5d | 0x53e6c5d  mov r13,[rcx+0x10] | producer source object -> r13 |
| [r13+0x4D4] | 4 | F1 0x53e6552 | 0x53e6552  movss xmm8,[r13+0x4D4] | strength term float |
| [r13+0x64C] | 4 | F1 0x53e647e | 0x53e647e  movss xmm0,[r13+0x64C] | float -> 0xEEC75A0, packed int |
| [r13+0x650] PV float (F1) | 4 | F1 0x53e6487 | 0x53e6487  movss xmm7,[r13+0x650] | float -> 0xEEC75A0, packed int |
| [r13+0x654] | 4 | F1 0x53e6475 | 0x53e6475  movss xmm6,[r13+0x654] | float -> 0xEEC75A0, third int |
| [r13+0x978] | 8 | F1 0x53e646e | 0x53e646e  mov r14,[r13+0x978] | object arg0 of 0x32D0F30 |
| [r13+0x998] | 8 | F1 0x53e63fb | 0x53e63fb  mov rax,[r13+0x998] | object A pointer |
| [rcx+0x390] | 8 | F1 0x53e64fc | 0x53e64fc  mov rcx,[rcx+0x390] | int field of A (rcx=A) -> float |
| [rax+0x64] | 4 | F1 0x53e652a | 0x53e652a  movss xmm7,[rax+0x64] | float of A |
| [rax+0x68] | 4 | F1 0x53e652f | 0x53e652f  movss xmm9,[rax+0x68] | float of A |
| [rbx+4] lookup id (F1) | 4 | F1 0x53e65b1 | 0x53e65b1  mov ecx,[rbx+4] | dword id of lookup (edx=0x10); 0xFFFFFFFF = unset |
| [rax+4] (F1) | 4 | F1 0x53e65bd | 0x53e65bd  mov eax,[rax+4] | dword id of second lookup (edx=0x1A) |
| [rbx+4] element f (F2) | 4 | F2 0x53e6e5b | 0x53e6e5b  movss xmm0,[rbx+4] | element float, row-3 transform |
| [rbx+8] | 4 | F2 0x53e6e60 | 0x53e6e60  movss xmm1,[rbx+8] | element float, row-3 transform |
| [rbx+0xC] | 4 | F2 0x53e6e65 | 0x53e6e65  movss xmm2,[rbx+0xC] | element float, row-3 transform |
| [rbx+0x10] | 4 | F2 0x53e6e9f | 0x53e6e9f  movss xmm0,[rbx+0x10] | element float, scales rows 0-2 |
| [r15] helper flag | 1 | F1 0x53e632b, 0x53e63d8, 0x53e668f; F2 0x53e6d00, 0x53e72ef, 0x53e7343 | 0x53e632b  cmp byte ptr [r15],1 | validity flag, must be 1; 0 faults (0xDEADC0DE at 0x53e6695 / 0x53e7348) |

| [rax+8] refcount | 4 | F1 0x53e633d; F2 0x53e6d15 | 0x53e633d  lock inc dword ptr [rax+8] | shared-state refcount inc on acquire |
| [rsi+8] helper rel (F1) | 4 | F1 0x53e6749, 0x53e6789 | 0x53e6749  lock dec dword ptr [rsi+8] | refcount half release |
| [rsi+0xC] helper rel (F1) | 4 | F1 0x53e675e, 0x53e67a2 | 0x53e675e  lock dec dword ptr [rsi+0xC] | second refcount half |
| [rax+8] vtable slot | 8 | F1 0x53e63e5; F2 0x53e72fb | 0x53e63e5  mov rax,[rax+8] | vtable slot +8, predicate call on the dispatcher |
| [rax+0xF0] | 8 | F1 0x53e6419, 0x53e6443, 0x53e656a | 0x53e6419  mov rax,[rax+0xF0] | vtable slot +0xF0 on rbx |
| [rax+0x5F0] | 8 | F1 0x53e64e4 | 0x53e64e4  mov rax,[rax+0x5F0] | vtable slot +0x5F0 on rbx |
| [rax+0x360] | 8 | F1 0x53e6703; F2 0x53e73f6 | 0x53e6703  mov rax,[rax+0x360] | vtable slot +0x360, posts the tagged record |
| [rax] vtable ptr | 8 | F1 0x53e6752, 0x53e6796; F2 0x53e6f54, 0x53e704d, 0x53e71a5, 0x53e7224, 0x53e7267 | 0x53e6f54  mov rax,[rax] | second deref (object -> vtable) before delete thunks |
| [0x128C5030] | 8 | F1 0x53e630f; F2 0x53e6cdd | 0x53e630f  lock inc qword ptr [0x128C5030] | global acquire counter |
| [0x128C5038] | 8 | F1 0x53e631f, 0x53e6341; F2 0x53e6ced, 0x53e6d19 | 0x53e631f  mov r15,[0x128C5038] | helper state pointer -> r15/rsi |
| [0x128C5040] | 8 | F1 0x53e6331, 0x53e6348; F2 0x53e6d05, 0x53e6d20 | 0x53e6331  mov rax,[0x128C5040] | shared object pointer |
| [0x128C5048] | 8 | F1 0x53e63b4; F2 0x53e72bc | 0x53e63b4  mov rdi,[0x128C5048] | dispatcher pointer -> rdi/r15 |
| [0x129C6498] | 4 | F1 0x53e66a0, 0x53e67cd | 0x53e66a0  mov eax,[0x129C6498] | TLS event counter (0xE938CB0/0xE938D70) |
| [0x129C6D58] | 4 | F2 0x53e7381, 0x53e7444 | 0x53e7381  mov eax,[0x129C6D58] | TLS event counter (0xE938CB0/0xE938D70) |
| [0x128767C8] | 4 | F1 0x53e66a6; F2 0x53e7387 | 0x53e66a6  mov ecx,[0x128767C8] | TLS slot index |
| [rdx+rcx*8] | 8 | F1 0x53e66b5; F2 0x53e7396 | 0x53e66b5  mov rcx,[rdx+rcx*8] | TLS slot pointer from gs:[0x58] table |
| [rcx+4] TLS count | 4 | F1 0x53e66b9; F2 0x53e739a | 0x53e66b9  cmp eax,[rcx+4] | per-slot count vs counter; over -> fatal path |
| [0xF99FFA0] | 8 | F1 0x53e63ec; F2 0x53e7302; 30+ sites in both | 0x53e63ec  call qword ptr [0xF99FFA0] | indirect thunk for all vtable calls and deletes |

| [rbp+0x88] cookie (F1) | 8 | F1 0x53e62f1 | 0x53e62f1  mov qword ptr [rbp+0x88],0xFFFFFFFFFFFFFFFE | frame cookie |
| [rbp+0x90] | 16 | F1 0x53e62ea (restore 0x53e6378) | 0x53e62ea  movaps [rbp+0x90],xmm6 | xmm6 spill |
| [rbp+0xA0] | 16 | F1 0x53e62e3 (restore 0x53e637f) | 0x53e62e3  movaps [rbp+0xA0],xmm7 | xmm7 spill |
| [rbp+0xB0] | 16 | F1 0x53e62db (restore 0x53e6386) | 0x53e62db  movaps [rbp+0xB0],xmm8 | xmm8 spill |
| [rbp+0xC0] | 16 | F1 0x53e62d3 (restore 0x53e638e) | 0x53e62d3  movaps [rbp+0xC0],xmm9 | xmm9 spill |
| [rbp+0xD0] | 16 | F1 0x53e62cb (restore 0x53e6396) | 0x53e62cb  movaps [rbp+0xD0],xmm10 | xmm10 spill |
| [rbp+0x58] | 8 | F1 0x53e63bb (init 0 at 0x53e6351) | 0x53e63bb  mov [rbp+0x58],rbx | helper holder pointer |
| [rbp+0x60] | 1 | F1 0x53e63bf (init 0 at 0x53e6359; read 0x53e6369) | 0x53e63bf  mov byte ptr [rbp+0x60],1 | helper flag byte |
| [rbp+0x68] | 8 | F1 0x53e63c3 (cleared 0x53e673a..0x53e673d) | 0x53e63c3  mov [rbp+0x68],r15 | helper image slot 1 |
| [rbp+0x70] | 8 | F1 0x53e63c7 (reload 0x53e6774) | 0x53e63c7  mov [rbp+0x70],rsi | helper image slot 2 |
| [rbp+0x78] | 8 | F1 0x53e63cb (nulled 0x53e6778) | 0x53e63cb  mov [rbp+0x78],rdi | helper image slot 3 |
| [rbp+0x38] | 8 | F1 0x53e64aa | 0x53e64aa  movlps [rbp+0x38],xmm0 | two packed ints from converted floats |
| [rbp+0x40] | 4 | F1 0x53e64ba | 0x53e64ba  mov [rbp+0x40],eax | third converted int |
| [rbp+0x86] | 1 | F1 0x53e64d4 | 0x53e64d4  movzx eax,byte ptr [rbp+0x86] | out byte of 0x32D0F30 |
| [rbp+0x80] | 4 | F1 0x53e64db | 0x53e64db  mov [rbp+0x80],eax | copy of the 0x32D0F30 byte |
| [rbp+0x44] | 1 | F1 0x53e6676 | 0x53e6676  mov [rbp+0x44],r12b | result flag byte |
| [rbp+0x48] | 4 | F1 0x53e667a | 0x53e667a  movss [rbp+0x48],xmm0 | result float 1 |
| [rbp+0x4C] | 4 | F1 0x53e667f | 0x53e667f  movss [rbp+0x4C],xmm8 | result float 2 |
| [rbp+0x50] | 4 | F1 0x53e6685 | 0x53e6685  movss [rbp+0x50],xmm1 | result float 3 |
| [rbp+0x54] | 4 | F1 0x53e668a | 0x53e668a  movss [rbp+0x54],xmm6 | result float 4 (strength) |

| [rbp+0x18] (F1) | 8 | F1 0x53e66cc | 0x53e66cc  mov [rbp+0x18],rcx | event dispatcher 0x129C6360 |
| [rbp+0x20] (F1) | 1 | F1 0x53e66d0 (init), 0x53e66f1 (save) | 0x53e66f1  mov [rbp+0x20],al | event key flag byte |
| [rbp+0x28] | 8 | F1 0x53e66d4 | 0x53e66d4  lea rbx,[rbp+0x28] | key buffer base (rdx arg of 0x39A7D40) |
| [rbp+0x30] (F1) | 8 | F1 0x53e66d8 | 0x53e66d8  mov qword ptr [rbp+0x30],0 | key buffer init |
| [rbp-0x50] | 8 | F1 0x53e66f8 (r8 arg at 0x53e66e4) | 0x53e66f8  mov [rbp-0x50],rax | tagged record pointer field |
| [rbp-0x48] | 1 | F1 0x53e66fc | 0x53e66fc  mov byte ptr [rbp-0x48],3 | record tag byte 3 |
| [rbp-0x18] | 1 | F1 0x53e66e0 | 0x53e66e0  mov byte ptr [rbp-0x18],0 | flag cleared before key fetch |
| [rbp+8] | 8 | F1 0x53e67e1 | 0x53e67e1  mov [rbp+8],rax | fatal record message ptr |
| [rbp+0x10] (F1) | 8 | F1 0x53e67e5 | 0x53e67e5  mov qword ptr [rbp+0x10],0x15 | fatal record length 0x15 |
| [rbp-0x10] | 16 | F1 0x53e67f4 | 0x53e67f4  movaps [rbp-0x10],xmm0 | fatal record data |
| [rsp+0x28] fatal src | 8 | F1 0x53e67ff; F2 0x53e747f | 0x53e67ff  mov [rsp+0x28],rax | fatal record source ptr |
| [rsp+0x20] fatal flag | 4 | F1 0x53e6804; F2 0x53e7484 | 0x53e6804  mov dword ptr [rsp+0x20],0 | fatal record flag |

| [r13+0xC] | 8 | F2 0x53e6c80 | 0x53e6c80  movsd xmm0,[r13+0xC] | two camera floats cached [rbp+0x1C0]/[rbp+0x1C4] |
| [r13+0x14] | 4 | F2 0x53e6c8e | 0x53e6c8e  movss xmm0,[r13+0x14] | camera float cached [rbp+0x1C8] |
| [r13+0x5E0] | 8 | F2 0x53e7311 | 0x53e7311  add r13,0x5E0 | record base ptr; 0x10 before element array begin |
| [r13+0x5F0] | 8 | F2 0x53e6d5f (cmp at 0x53e6c68) | 0x53e6d5f  mov rbx,[r13+0x5F0] | element array begin, walked with stride 0x14 |
| [r13+0x5F8] | 8 | F2 0x53e6c61 (also 0x53e6d66) | 0x53e6c61  mov rax,[r13+0x5F8] | element array end |
| [r13+0x608] | 8 | F2 0x53e6ec7, 0x53e6fc0 | 0x53e6ec7  mov r12,[r13+0x608] | pass 1 and pass 2 objects |
| [r13+0x618] | 8 | F2 0x53e7117 | 0x53e7117  mov r15,[r13+0x618] | pass 3 object |
| [r13+0x638] | 8 | F2 0x53e6c9c | 0x53e6c9c  mov rax,[r13+0x638] | pass 2 r8 arg, cached [rbp+0x178] |
| [r13+0x640] | 8 | F2 0x53e6caa | 0x53e6caa  mov rax,[r13+0x640] | pass 1 r8 arg, cached [rbp+0x170] |
| [r13+0x648] | 8 | F2 0x53e6cb8 | 0x53e6cb8  mov rdi,[r13+0x648] | pass 3 r8 arg, cached [rbp+0x180] |
| [r13+0x650] | 16 | F2 0x53e6cbf | 0x53e6cbf  movups xmm0,[r13+0x650] | 16-byte block cached [rbp+0x120] |
| [rax+0x18] queue ptr (F2) | 8 | F2 0x53e6da4, 0x53e731f | 0x53e6da4  mov rdi,[rax+0x18] | queue object = [holder+0x18] |
| [rax+0x18] sub reset (F2) | 8 | F2 0x53e70f1 | 0x53e70f1  mov qword ptr [rax+0x18],0 | sub-object field zeroed when count hits 0 |
| [rax+0x20] matrix row 2 (F2) | 16 | F2 0x53e6e34 (store 0x53e6ec3) | 0x53e6e34  movups xmm4,[rax+0x20] | matrix row 2 |
| [rax+0x20] sub count (F2) | 8 | F2 0x53e70ca (dec/store 0x53e70e7) | 0x53e70ca  mov rcx,[rax+0x20] | sub-object count, decremented per element |
| [rax+0x28] | 8 | F2 0x53e70d2 | 0x53e70d2  cmp rdx,[rax+0x28] | sub-object limit |
| [rax+0x30] matrix row 3 (F2) | 16 | F2 0x53e6e53 (2nd write 0x53e6e97) | 0x53e6e53  movups [rax+0x30],xmm3 | row 3: camera then element transform |
| [rax+0x30] sub flag (F2) | 1 | F2 0x53e70c4 (clear 0x53e70d8) | 0x53e70c4  cmp byte ptr [rax+0x30],0 | sub-object active flag |
| [rax+0x30] out ptr (F2) | 8 | F2 0x53e7105 | 0x53e7105  mov rax,[rax+0x30] | output object = [holder+0x30] |
| [rax+0x38] | 1 | F2 0x53e70c0 | 0x53e70c0  mov byte ptr [rax+0x38],1 | sub-object processed flag |

| [rax] matrix row 0 (F2) | 16 | F2 0x53e6e2a (store 0x53e6eb6) | 0x53e6e2a  movups xmm3,[rax] | matrix row 0 |
| [rax+0x10] matrix row 1 (F2) | 16 | F2 0x53e6e30 (store 0x53e6ebc) | 0x53e6e30  movups xmm0,[rax+0x10] | matrix row 1 |
| [rax+0x10] out flag (F2) | 1 | F2 0x53e7113 | 0x53e7113  mov byte ptr [rax+0x10],1 | output ready flag |
| [rax+0x74] (F2) | 1 | F2 0x53e7376 | 0x53e7376  movzx eax,byte ptr [rax+0x74] | holder flag byte -> word at [rbp+0x1F0] |
| [rdi+0x48] | 8 | F2 0x53e6dbe (2nd pop via rax 0x53e7331) | 0x53e6dbe  mov rcx,[rdi+0x48] | ring table base |
| [rdi+0x50] | 8 | F2 0x53e6dc2 (2nd pop via rax 0x53e7335) | 0x53e6dc2  mov rdx,[rdi+0x50] | ring mask |
| [rdi+0x58] | 8 | F2 0x53e6db4 (2nd pop via rax 0x53e7327) | 0x53e6db4  mov rcx,[rdi+0x58] | ring head |
| [rdi+0x60] | 8 | F2 0x53e6db0 (2nd pop via rax 0x53e7323) | 0x53e6db0  mov rax,[rdi+0x60] | ring tail |
| [rdi+0x78] | 1 | F2 0x53e6dac, 0x53e6e07, 0x53e6e57, 0x53e6e9b | 0x53e6dac  mov byte ptr [rdi+0x78],1 | queue dirty flag |

| [r12+8] pass result (F2) | 4 | F2 0x53e6f48, 0x53e7041 | 0x53e6f48  lock dec dword ptr [r12+8] | pass 1/2 result shared_ptr release |
| [rsi+8] pass3 (F2) | 4 | F2 0x53e719c | 0x53e719c  lock dec dword ptr [rsi+8] | pass 3 result release |
| [r12+0xC] | 4 | F2 0x53e6f60, 0x53e7059 | 0x53e6f60  lock dec dword ptr [r12+0xC] | second refcount half, passes 1/2 |
| [rsi+0xC] pass3 (F2) | 4 | F2 0x53e71b1 | 0x53e71b1  lock dec dword ptr [rsi+0xC] | second half, pass 3 |
| [rdx+0xC] | 4 | F2 0x53e6f90, 0x53e71de | 0x53e6f90  lock dec dword ptr [rdx+0xC] | holder inner refcount |
| [r14+8] (F2) | 4 | F2 0x53e721a | 0x53e721a  lock dec dword ptr [r14+8] | helper release after loop |
| [r14+0xC] (F2) | 4 | F2 0x53e7230 | 0x53e7230  lock dec dword ptr [r14+0xC] | helper release second half |
| [rsi+8] helper post (F2) | 4 | F2 0x53e725e | 0x53e725e  lock dec dword ptr [rsi+8] | second helper release |
| [rsi+0xC] helper post (F2) | 4 | F2 0x53e7273 | 0x53e7273  lock dec dword ptr [rsi+0xC] | its second half |

| [rbp+0x200] (F2) | 16 | F2 0x53e6c4b (restore 0x53e729e) | 0x53e6c4b  movaps [rbp+0x200],xmm6 | xmm6 spill |
| [rbp+0x1F8] | 8 | F2 0x53e6c52 | 0x53e6c52  mov qword ptr [rbp+0x1F8],0xFFFFFFFFFFFFFFFE | frame cookie |
| [rbp+0x1D0] | 8 | F2 0x53e6c79 (reads 0x53e6d6d, 0x53e7318, 0x53e736f) | 0x53e6c79  mov [rbp+0x1D0],rax | holder cache |
| [rbp+0x1C0] | 8 | F2 0x53e6c86 (read 0x53e6e0b) | 0x53e6c86  movsd [rbp+0x1C0],xmm0 | camera floats 0-1 |
| [rbp+0x1C4] | 4 | F2 0x53e6e13 | 0x53e6e13  movss xmm1,[rbp+0x1C4] | camera float 1 |
| [rbp+0x1C8] | 4 | F2 0x53e6c94 (read 0x53e6e1b) | 0x53e6c94  movss [rbp+0x1C8],xmm0 | camera float 2 |
| [rbp+0x178] | 8 | F2 0x53e6ca3 (read 0x53e7004) | 0x53e6ca3  mov [rbp+0x178],rax | pass 2 r8 arg |
| [rbp+0x170] | 8 | F2 0x53e6cb1 (read 0x53e6f0b) | 0x53e6cb1  mov [rbp+0x170],rax | pass 1 r8 arg |
| [rbp+0x180] | 8 | F2 0x53e6cf7 (read 0x53e715f) | 0x53e6cf7  mov [rbp+0x180],rdi | pass 3 r8 arg |
| [rbp+0x120] | 16 | F2 0x53e6cc7 (stored out at 0x53e7109) | 0x53e6cc7  movaps [rbp+0x120],xmm0 | cached 16-byte block |

| [rbp+0x188] | 8 | F2 0x53e6d2c (init 0), 0x53e72c3 (read 0x53e7292) | 0x53e72c3  mov [rbp+0x188],r12 | helper holder pointer |
| [rbp+0x190] | 1 | F2 0x53e6d37 (init 0), 0x53e72ca (read 0x53e7289) | 0x53e72ca  mov byte ptr [rbp+0x190],1 | helper flag byte |
| [rbp+0x198] | 16 | F2 0x53e6d41 (zero), 0x53e72d1, 0x53e720e (zero) | 0x53e72d1  mov [rbp+0x198],rsi | helper image slot |
| [rbp+0x1A0] | 8 | F2 0x53e72d8 (reads 0x53e7204, 0x53e7247) | 0x53e72d8  mov [rbp+0x1A0],r14 | helper image slot |
| [rbp+0x1A8] | 8 | F2 0x53e6d48 (zero), 0x53e72df, 0x53e724e (zero) | 0x53e72df  mov [rbp+0x1A8],r15 | helper image slot |
| [rbp+0x1B0] sub cache (F2) | 8 | F2 0x53e6df9 (read 0x53e70b0) | 0x53e6df9  mov [rbp+0x1B0],r12 | popped sub-object cache |
| [rbp+0x1B0] fatal msg (F2) | 8 | F2 0x53e7458 | 0x53e7458  mov [rbp+0x1B0],rax | fatal record message ptr (reused) |
| [rbp+0x1B8] matrix ptr (F2) | 8 | F2 0x53e6e00 | 0x53e6e00  mov [rbp+0x1B8],rax | popped matrix pointer |
| [rbp+0x1B8] fatal len (F2) | 8 | F2 0x53e745f | 0x53e745f  mov qword ptr [rbp+0x1B8],0x15 | fatal record length 0x15 (reused) |

| [rbp+0x1D8] (F2) | 8 | F2 0x53e7353 (out param 0x53e6ff9; reads 0x53e6f7b, 0x53e7074, 0x53e71c9) | 0x53e7353  mov [rbp+0x1D8],r13 | pass out-holder + record base (r13+0x5E0) |
| [rbp+0x1E0] | 8 | F2 0x53e735a | 0x53e735a  mov [rbp+0x1E0],rax | record field: popped element |
| [rbp+0x1E8] | 8 | F2 0x53e7368 (pass result read 0x53e6f3c, 0x53e7035, 0x53e7190) | 0x53e7368  mov [rbp+0x1E8],rax | record field: ptr to camera floats |
| [rbp+0x1F0] | 2 | F2 0x53e737a (word store; byte reads 0x53e6f1b, 0x53e7014, 0x53e716f; inits 0x53e6ece, 0x53e6fc7, 0x53e711e) | 0x53e737a  mov [rbp+0x1F0],ax | pass status byte / holder flag word |
| [rbp-0x38] buffer (F2) | 8 | F2 0x53e712c (r8 arg 0x53e73d1) | 0x53e712c  lea rbx,[rbp-0x38] | 0x148-byte pass output buffer base |
| [rbp-0x38] record (F2) | 8 | F2 0x53e73eb | 0x53e73eb  mov [rbp-0x38],rax | record pointer field (buffer reused) |
| [rbp-0x30] | 1 | F2 0x53e73ef | 0x53e73ef  mov byte ptr [rbp-0x30],4 | record tag byte 4 |
| [rbp+0x130] | 8 | F2 0x53e73ad (out param 0x53e6eed) | 0x53e73ad  mov [rbp+0x130],rcx | event dispatcher 0x129C6C20 |
| [rbp+0x138] | 1 | F2 0x53e73b4 (init), 0x53e73de (read 0x53e740b) | 0x53e73de  mov [rbp+0x138],al | event key flag byte |
| [rbp+0x140] | 8 | F2 0x53e73bb | 0x53e73bb  lea rsi,[rbp+0x140] | key buffer base |
| [rbp+0x148] | 8 | F2 0x53e73c2 | 0x53e73c2  mov qword ptr [rbp+0x148],0 | key buffer init |
| [rbp] (F2) | 1 | F2 0x53e73cd | 0x53e73cd  mov byte ptr [rbp],0 | flag cleared before key fetch |
| [rsp+0x30] | 8 | F2 0x53e6ef4, 0x53e6fe6, 0x53e7148 | 0x53e6ef4  mov [rsp+0x30],rax | pass out param ([rbp+0x1D8]) |
| [rsp+0x40] | 8 | F2 0x53e6f00, 0x53e6fed, 0x53e714d | 0x53e6f00  mov [rsp+0x40],rax | pass out param ([rbp+0x130]) |
| [rbp+0x110] | 16 | F2 0x53e7471 | 0x53e7471  movaps [rbp+0x110],xmm0 | fatal record data |

<!-- APPEND -->
