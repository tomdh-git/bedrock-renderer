## NEXT
DONE

# U-Vfg — instruction-complete dossier: VolumetricFog clone (0x53e3aa0..0x53e4d77)

Source listing: docs/data/listings/effect_volfog_clone_53e3aa0_53e4d77.txt — one function, 1001 instructions, 0x53e3aa0..0x53e4d76. Every instruction is in exactly one phase below (phases of ≤40 instructions in listing order). Verbatim `0xRVA  instr` lines are copied from the input data.

## Phases

### Phase 1 — 0x53e3aa0..0x53e3b64: Prologue: save all nonvolatile GPRs, allocate 0x318 stack, frame rbp=rsp+0x80, spill xmm6-xmm15 to [rbp+0x1F0..0x280] and cookie 0xFFFFFFFFFFFFFFFE to [rbp+0x1E8]; load this-object fields r12=[rcx+8], r13=[rcx+0x10]; acquire/ref the global service at 0x128C4FD0 (calls 0xE943178 and 0xE94319C with lock inc qword [0x128C5030]) and read globals 0x128C5038/0x128C5040, refcounting one via lock inc [rax+8].
```
0x53e3aa0  push rbp
0x53e3aa1  push r15
0x53e3aa3  push r14
0x53e3aa5  push r13
0x53e3aa7  push r12
0x53e3aa9  push rsi
0x53e3aaa  push rdi
0x53e3aab  push rbx
0x53e3aac  sub rsp,0x318
0x53e3ab3  lea rbp,[rsp+0x80]
0x53e3abb  movaps [rbp+0x280],xmm15
0x53e3ac3  movaps [rbp+0x270],xmm14
0x53e3acb  movaps [rbp+0x260],xmm13
0x53e3ad3  movaps [rbp+0x250],xmm12
0x53e3adb  movaps [rbp+0x240],xmm11
0x53e3ae3  movaps [rbp+0x230],xmm10
0x53e3aeb  movaps [rbp+0x220],xmm9
0x53e3af3  movaps [rbp+0x210],xmm8
0x53e3afb  movaps [rbp+0x200],xmm7
0x53e3b02  movaps [rbp+0x1F0],xmm6
0x53e3b09  mov qword ptr [rbp+0x1E8],0xFFFFFFFFFFFFFFFE
0x53e3b14  mov r12,[rcx+8]
0x53e3b18  mov r13,[rcx+0x10]
0x53e3b1c  lea rsi,[0x128C4FD0]
0x53e3b23  mov rcx,rsi
0x53e3b26  call 0xE943178
0x53e3b2b  lock inc qword ptr [0x128C5030]
0x53e3b33  mov rcx,rsi
0x53e3b36  call 0xE94319C
0x53e3b3b  mov r14,[0x128C5038]
0x53e3b42  test r14,r14
0x53e3b45  je short 0x53E3B6D
0x53e3b47  cmp byte ptr [r14],1
0x53e3b4b  jne short 0x53E3B6D
0x53e3b4d  mov rax,[0x128C5040]
0x53e3b54  test rax,rax
0x53e3b57  je short 0x53E3BAA
0x53e3b59  lock inc dword ptr [rax+8]
0x53e3b5d  mov r14,[0x128C5038]
0x53e3b64  mov rax,[0x128C5040]
```

### Phase 2 — 0x53e3b6b..0x53e3c24: Fast path: take cached handles rdi=[0x128C5048], rax/r14 from 0x128C5040/0x128C5038 and build the local record at [rbp+0x128..0x148]; slow path (0x53e3b6d) zeroes the record and calls 0x3B2020 on 0x128C4FD0 (sil=1); both paths join at 0x53e3bf6 where head rdi's vtable slot [rax+0x270] is called with rdx=rbp+0x70 (out config pointer stored at [rbp+0x70]), then vtable slot [rax+8] is called returning a bool in al.
```
0x53e3b6b  jmp short 0x53E3BAC
0x53e3b6d  mov qword ptr [rbp+0x128],0
0x53e3b78  mov byte ptr [rbp+0x130],0
0x53e3b7f  xorps xmm0,xmm0
0x53e3b82  movups [rbp+0x138],xmm0
0x53e3b89  mov qword ptr [rbp+0x148],0
0x53e3b94  lea rcx,[0x128C4FD0]
0x53e3b9b  call 0x3B2020
0x53e3ba0  mov sil,1
0x53e3ba3  xor r14d,r14d
0x53e3ba6  xor edi,edi
0x53e3ba8  jmp short 0x53E3BF6
0x53e3baa  xor eax,eax
0x53e3bac  mov rdi,[0x128C5048]
0x53e3bb3  mov [rbp+0x128],rsi
0x53e3bba  mov byte ptr [rbp+0x130],1
0x53e3bc1  mov [rbp+0x138],r14
0x53e3bc8  mov [rbp+0x140],rax
0x53e3bcf  mov [rbp+0x148],rdi
0x53e3bd6  test r14,r14
0x53e3bd9  je short 0x53E3BF0
0x53e3bdb  cmp byte ptr [r14],0
0x53e3bdf  jne short 0x53E3BEC
0x53e3be1  mov dword ptr [0],0xDEADC0DE
0x53e3bec  xor esi,esi
0x53e3bee  jmp short 0x53E3BF6
0x53e3bf0  mov sil,1
0x53e3bf3  xor r14d,r14d
0x53e3bf6  mov rax,[rdi]
0x53e3bf9  mov rax,[rax+0x270]
0x53e3c00  lea rdx,[rbp+0x70]
0x53e3c04  mov rcx,rdi
0x53e3c07  call qword ptr [0xF99FFA0]
0x53e3c0d  nop
0x53e3c0e  test sil,sil
0x53e3c11  jne 0x53E4AF2
0x53e3c17  cmp byte ptr [r14],1
0x53e3c1b  jne 0x53E4AF2
0x53e3c21  mov rax,[rdi]
0x53e3c24  mov rax,[rax+8]
```

### Phase 3 — 0x53e3c2b..0x53e3cfc: DEADC0DE guard on [r14]==0, then calls vtable slot [rax+0x218] with out buffer [rbp+0x90]; if dword [rbp+0x90]!=1 jumps to 0x53E3D53; else reads dimensions from the config pointer [rbp+0x70]: [rcx+0xC28]→[rbp+0x1E0], [rcx+0xC2C]→edi, [rcx+0xC30]→[rbp+0x1B0], sets rsi=r12+0x338 and al=byte[r12+0x368]; if config byte [rcx+0xC1C]==1 and cached values at r12+0x360/0x350/0x354 all match those dims, skips the rebuild (0x53E3DE4); otherwise fills a descriptor record at rbp+0x170 (dims, dword 0x1C, word 0x202, 0).
```
0x53e3c2b  call qword ptr [0xF99FFA0]
0x53e3c31  nop
0x53e3c32  test al,al
0x53e3c34  je 0x53E4AF2
0x53e3c3a  cmp byte ptr [r14],0
0x53e3c3e  jne short 0x53E3C4B
0x53e3c40  mov dword ptr [0],0xDEADC0DE
0x53e3c4b  mov rax,[rdi]
0x53e3c4e  mov rax,[rax+0x218]
0x53e3c55  lea rdx,[rbp+0x90]
0x53e3c5c  mov rcx,rdi
0x53e3c5f  call qword ptr [0xF99FFA0]
0x53e3c65  nop
0x53e3c66  cmp dword ptr [rbp+0x90],1
0x53e3c6d  jne 0x53E3D53
0x53e3c73  mov rcx,[rbp+0x70]
0x53e3c77  mov eax,[rcx+0xC28]
0x53e3c7d  mov [rbp+0x1E0],rax
0x53e3c84  mov edi,[rcx+0xC2C]
0x53e3c8a  mov eax,[rcx+0xC30]
0x53e3c90  mov [rbp+0x1B0],rax
0x53e3c97  lea rsi,[r12+0x338]
0x53e3c9f  movzx eax,byte ptr [r12+0x368]
0x53e3ca8  cmp byte ptr [rcx+0xC1C],1
0x53e3caf  jne 0x53E3D8C
0x53e3cb5  test al,al
0x53e3cb7  je short 0x53E3CE9
0x53e3cb9  mov rax,[rbp+0x1B0]
0x53e3cc0  cmp [r12+0x360],eax
0x53e3cc8  jne short 0x53E3CE9
0x53e3cca  mov rax,[rbp+0x1E0]
0x53e3cd1  cmp [r12+0x350],eax
0x53e3cd9  jne short 0x53E3CE9
0x53e3cdb  cmp [r12+0x354],edi
0x53e3ce3  je 0x53E3DE4
0x53e3ce9  mov rax,[rbp+0x1E0]
0x53e3cf0  mov [rbp+0x170],eax
0x53e3cf6  mov [rbp+0x174],edi
0x53e3cfc  mov dword ptr [rbp+0x178],0x1C
```

### Phase 4 — 0x53e3d06..0x53e3dca: Finishes the record at rbp+0x170 (word 0x202, byte 0, [rbp+0x1B0]) and calls 0x5A4C340(rdx=rbp+0x170, rcx=[rbp+0x90]); depending on byte[r12+0x368] and the descriptor dword it either updates via 0x5A4C6A0(rsi, [rbp+0x90]) or releases/inserts via vtable on [r12+0x340] and 0x5A4C4F0(rsi, [rbp+0x90]) setting byte[r12+0x368]=1/0, then at 0x53e3dca releases [rbp+0x98] via vtable on [rbp+0x90] if nonzero.
```
0x53e3d06  mov word ptr [rbp+0x17C],0x202
0x53e3d0f  mov byte ptr [rbp+0x17E],0
0x53e3d16  mov rax,[rbp+0x1B0]
0x53e3d1d  mov [rbp+0x180],eax
0x53e3d23  lea rcx,[rbp+0x90]
0x53e3d2a  lea rdx,[rbp+0x170]
0x53e3d31  call 0x5A4C340
0x53e3d36  nop
0x53e3d37  cmp byte ptr [r12+0x368],1
0x53e3d40  jne short 0x53E3DB2
0x53e3d42  lea rdx,[rbp+0x90]
0x53e3d49  mov rcx,rsi
0x53e3d4c  call 0x5A4C6A0
0x53e3d51  jmp short 0x53E3DCA
0x53e3d53  cmp byte ptr [r12+0x368],1
0x53e3d5c  jne 0x53E4AF2
0x53e3d62  mov rcx,[r12+0x340]
0x53e3d6a  test rcx,rcx
0x53e3d6d  je short 0x53E3D7E
0x53e3d6f  mov rax,[r12+0x338]
0x53e3d77  call qword ptr [0xF99FFA0]
0x53e3d7d  nop
0x53e3d7e  mov byte ptr [r12+0x368],0
0x53e3d87  jmp 0x53E4AF2
0x53e3d8c  test al,al
0x53e3d8e  je short 0x53E3DE4
0x53e3d90  mov rcx,[r12+0x340]
0x53e3d98  test rcx,rcx
0x53e3d9b  je short 0x53E3DA7
0x53e3d9d  mov rax,[rsi]
0x53e3da0  call qword ptr [0xF99FFA0]
0x53e3da6  nop
0x53e3da7  mov byte ptr [r12+0x368],0
0x53e3db0  jmp short 0x53E3DE4
0x53e3db2  lea rdx,[rbp+0x90]
0x53e3db9  mov rcx,rsi
0x53e3dbc  call 0x5A4C4F0
0x53e3dc1  mov byte ptr [r12+0x368],1
0x53e3dca  mov rcx,[rbp+0x98]
```

### Phase 5 — 0x53e3dd1..0x53e3e9c: If [rbp+0x98] nonzero, releases it via vtable on [rbp+0x90]; zero-inits [rbp+0x90]/[rbp+0xA0]; allocates 0x20 bytes via vtable on global [0x1233E1A8] (rbx) and builds a 0x16-char name in it (16 bytes copied from 0xF55882A, then imm 0x73656C706D615379 = "ySamples" at +0xE, terminator at +0x16); wraps {ptr,0x16} at [rbp-0x10] and registers via 0x393660(r8d=1), frees rbx via 0xE935700(rcx=rbx, edx=0x20); zero-inits [rbp+0x150] and loads config [rbp+0x70] checking byte[rax+0xC1C]==1.
```
0x53e3dd1  test rcx,rcx
0x53e3dd4  je short 0x53E3DE4
0x53e3dd6  mov rax,[rbp+0x90]
0x53e3ddd  call qword ptr [0xF99FFA0]
0x53e3de3  nop
0x53e3de4  xorps xmm0,xmm0
0x53e3de7  movaps [rbp+0xA0],xmm0
0x53e3dee  movaps [rbp+0x90],xmm0
0x53e3df5  mov rcx,[0x1233E1A8]
0x53e3dfc  mov rax,[rcx]
0x53e3dff  mov rax,[rax+8]
0x53e3e03  mov edx,0x20
0x53e3e08  call qword ptr [0xF99FFA0]
0x53e3e0e  nop
0x53e3e0f  mov rbx,rax
0x53e3e12  test rax,rax
0x53e3e15  je 0x53E4C26
0x53e3e1b  mov [rbp+0x90],rbx
0x53e3e22  mov qword ptr [rbp+0xA0],0x16
0x53e3e2d  mov qword ptr [rbp+0xA8],0x1F
0x53e3e38  movups xmm0,[0xF55882A]
0x53e3e3f  movups [rbx],xmm0
0x53e3e42  mov rax,0x73656C706D615379
0x53e3e4c  mov [rbx+0xE],rax
0x53e3e50  mov byte ptr [rbx+0x16],0
0x53e3e54  mov [rbp-0x10],rbx
0x53e3e58  mov qword ptr [rbp-8],0x16
0x53e3e60  lea rcx,[rbp-0x48]
0x53e3e64  lea rdx,[rbp-0x10]
0x53e3e68  mov r8d,1
0x53e3e6e  call 0x393660
0x53e3e73  nop
0x53e3e74  mov edx,0x20
0x53e3e79  mov rcx,rbx
0x53e3e7c  call 0xE935700
0x53e3e81  xorps xmm0,xmm0
0x53e3e84  movaps [rbp+0x150],xmm0
0x53e3e8b  mov rax,[rbp+0x70]
0x53e3e8f  cmp byte ptr [rax+0xC1C],1
0x53e3e96  jne 0x53E4904
0x53e3e9c  cmp byte ptr [r12+0x368],0
```

### Phase 6 — 0x53e3ea5..0x53e3f79: Exits to 0x53E4904 unless byte[r12+0x368]!=0; saves rdi→[rbp+0x80], rsi→[rbp+0x18], r15=[r12+0x978], copies floats r12+0x64C/0x650/0x654 → [rbp+0xF8/0xFC/0x100], r12→[rbp+0x1B8], r13→[rbp+0x88]; pulls a 0x40-byte element from a ring buffer of r13's object ([rax+0x88..0xA0]) into [rbp+0x90..0xCC], picks an element from a second ring ([rax+8..0x20]) and calls 0xAA6580(rcx=rbp+0x30 out, rdx=first elem, r8=second elem), then 0xAB49C0(rcx=rbp+0x170, rdx=rbp+0x30) and 0xAB49C0(rcx=rbp+0x30, rdx=rbp+0x90).
```
0x53e3ea5  je 0x53E4904
0x53e3eab  mov [rbp+0x80],rdi
0x53e3eb2  mov [rbp+0x18],rsi
0x53e3eb6  mov r15,[r12+0x978]
0x53e3ebe  movss xmm0,[r12+0x64C]
0x53e3ec8  movss [rbp+0xF8],xmm0
0x53e3ed0  movss xmm0,[r12+0x650]
0x53e3eda  movss [rbp+0xFC],xmm0
0x53e3ee2  mov [rbp+0x1B8],r12
0x53e3ee9  movss xmm0,[r12+0x654]
0x53e3ef3  movss [rbp+0x100],xmm0
0x53e3efb  mov [rbp+0x88],r13
0x53e3f02  mov rax,[r13+0x18]
0x53e3f06  mov rcx,[rax+0xA0]
0x53e3f0d  mov rdx,[rax+0x98]
0x53e3f14  add rcx,rdx
0x53e3f17  dec rcx
0x53e3f1a  mov rdx,[rax+0x88]
0x53e3f21  mov r8,[rax+0x90]
0x53e3f28  dec r8
0x53e3f2b  and r8,rcx
0x53e3f2e  mov rdx,[rdx+r8*8]
0x53e3f32  movups xmm0,[rdx]
0x53e3f35  movaps [rbp+0x90],xmm0
0x53e3f3c  movups xmm0,[rdx+0x10]
0x53e3f40  movaps [rbp+0xA0],xmm0
0x53e3f47  movups xmm0,[rdx+0x20]
0x53e3f4b  movaps [rbp+0xB0],xmm0
0x53e3f52  movups xmm0,[rdx+0x30]
0x53e3f56  movaps [rbp+0xC0],xmm0
0x53e3f5d  mov rcx,[rax+0x20]
0x53e3f61  mov r8,[rax+0x18]
0x53e3f65  add rcx,r8
0x53e3f68  dec rcx
0x53e3f6b  mov r8,[rax+8]
0x53e3f6f  mov rax,[rax+0x10]
0x53e3f73  dec rax
0x53e3f76  and rax,rcx
0x53e3f79  mov r8,[r8+rax*8]
```

### Phase 7 — 0x53e3f81..0x53e4028: Calls 0xAA6580(rcx=rbp+0x30, rdx=first ring elem, r8=second ring elem) then 0xAB49C0(rcx=rbp+0x170, rdx=rbp+0x30) and 0xAB49C0(rcx=rbp+0x30, rdx=rbp+0x90); asserts r12+0x348 index!=-1 and (rsi=[r12+0x340]!=0 or index==0) else 0x53E4C20 (call 0x78ED0); requires rsi!=0 && dword[rbp+0x1B0]>0 && rdx=[rbp+0x80]>0 else 0x53E4543; then accumulates weight sums from the floats at [rbp+0x38..0x6C] (products against xmm0, zeroed at 0x53e4006), XORs xmm0/xmm15 with vector constant [0xEF3F050] and divides xmm0 by xmm2, storing the result as double at [rbp].
```
0x53e3f81  call 0xAA6580
0x53e3f86  nop
0x53e3f87  lea rcx,[rbp+0x170]
0x53e3f8e  lea rdx,[rbp+0x30]
0x53e3f92  call 0xAB49C0
0x53e3f97  nop
0x53e3f98  lea rcx,[rbp+0x30]
0x53e3f9c  lea rdx,[rbp+0x90]
0x53e3fa3  call 0xAB49C0
0x53e3fa8  nop
0x53e3fa9  mov rcx,[rbp+0x1B8]
0x53e3fb0  mov rax,[rcx+0x348]
0x53e3fb7  cmp rax,0xFFFFFFFFFFFFFFFF
0x53e3fbb  je 0x53E4C20
0x53e3fc1  mov rsi,[rcx+0x340]
0x53e3fc8  test rsi,rsi
0x53e3fcb  setne cl
0x53e3fce  test rax,rax
0x53e3fd1  sete al
0x53e3fd4  or al,cl
0x53e3fd6  mov rdx,[rbp+0x80]
0x53e3fdd  je 0x53E4C20
0x53e3fe3  test rsi,rsi
0x53e3fe6  setne al
0x53e3fe9  cmp dword ptr [rbp+0x1B0],0
0x53e3ff0  setg cl
0x53e3ff3  and cl,al
0x53e3ff5  cmp cl,1
0x53e3ff8  jne 0x53E4543
0x53e3ffe  test edx,edx
0x53e4000  jle 0x53E4543
0x53e4006  xorps xmm0,xmm0
0x53e4009  movss xmm1,[rbp+0x3C]
0x53e400e  mulss xmm1,xmm0
0x53e4012  movss xmm2,[rbp+0x38]
0x53e4017  mulss xmm2,xmm0
0x53e401b  movss xmm3,[rbp+0x4C]
0x53e4020  mulss xmm3,xmm0
0x53e4024  addss xmm3,xmm1
0x53e4028  movss xmm4,[rbp+0x48]
```

### Phase 8 — 0x53e402d..0x53e40e0: Continues the weight sums and the divss by xmm2; converts the three (dim-1) values to floats into [rbp+0x104] (from [rbp+0x1E0]), [rbp+0x110] (from width rdx), [rbp+0x114] (from [rbp+0x1B0]); divss xmm15,xmm1; sets xmm10=0, r14=rbp+0x30, loads float constants xmm11=[0xEEC8060], xmm12=[0xEF40D58], zeroes the y-counter [rbp+0x168]=0 and jumps into the sweep loop at 0x53E412C.
```
0x53e402d  mulss xmm4,xmm0
0x53e4031  addss xmm4,xmm2
0x53e4035  movss xmm15,[rbp+0x58]
0x53e403b  movss xmm1,[rbp+0x5C]
0x53e4040  movaps xmm2,xmm1
0x53e4043  mulss xmm2,xmm0
0x53e4047  mulss xmm0,xmm15
0x53e404c  movss xmm5,[rbp+0x68]
0x53e4051  movss xmm6,[rbp+0x6C]
0x53e4056  addss xmm2,xmm6
0x53e405a  addss xmm0,xmm5
0x53e405e  addss xmm2,xmm3
0x53e4062  addss xmm0,xmm4
0x53e4066  addss xmm1,xmm6
0x53e406a  addss xmm15,xmm5
0x53e406f  addss xmm1,xmm3
0x53e4073  addss xmm15,xmm4
0x53e4078  movaps xmm3,[0xEF3F050]
0x53e407f  xorps xmm15,xmm3
0x53e4083  xorps xmm0,xmm3
0x53e4086  divss xmm0,xmm2
0x53e408a  cvtss2sd xmm0,xmm0
0x53e408e  movsd [rbp],xmm0
0x53e4093  mov rax,[rbp+0x1E0]
0x53e409a  lea eax,[rax-1]
0x53e409d  xorps xmm0,xmm0
0x53e40a0  cvtsi2ss xmm0,eax
0x53e40a4  movss [rbp+0x104],xmm0
0x53e40ac  lea eax,[rdx-1]
0x53e40af  xorps xmm0,xmm0
0x53e40b2  cvtsi2ss xmm0,eax
0x53e40b6  movss [rbp+0x110],xmm0
0x53e40be  mov rax,[rbp+0x1B0]
0x53e40c5  lea eax,[rax-1]
0x53e40c8  xorps xmm0,xmm0
0x53e40cb  cvtsi2ss xmm0,eax
0x53e40cf  movss [rbp+0x114],xmm0
0x53e40d7  divss xmm15,xmm1
0x53e40dc  xorps xmm10,xmm10
0x53e40e0  lea r14,[rbp+0x30]
```

### Phase 9 — 0x53e40e4..0x53e41bf: Loads the two float constants into xmm11/xmm12 and zeroes the y-loop counter [rbp+0x168]; y-loop: increments [rbp+0x168] and exits to 0x53E4543 when >= [rbp+0x1B0], skips the row if width [rbp+0x1E0]<=0; per row computes uv = row/[rbp+0x114] scaled by double constant [0xEF6D158] into xmm6, precomputes row offsets (row-1)*width → [rbp+0x10] and row*width → [rbp+0x10C], and enters the x-loop at 0x53E4197 with eax=0.
```
0x53e40e4  movss xmm11,[0xEEC8060]
0x53e40ed  movss xmm12,[0xEF40D58]
0x53e40f6  mov qword ptr [rbp+0x168],0
0x53e4101  jmp short 0x53E412C
0x53e4103  nop [rax+rax]
0x53e4110  mov rax,[rbp+0x168]
0x53e4117  inc eax
0x53e4119  mov [rbp+0x168],rax
0x53e4120  cmp eax,[rbp+0x1B0]
0x53e4126  jge 0x53E4543
0x53e412c  cmp dword ptr [rbp+0x1E0],0
0x53e4133  jle short 0x53E4110
0x53e4135  mov rax,[rbp+0x168]
0x53e413c  lea ecx,[rax-1]
0x53e413f  xorps xmm0,xmm0
0x53e4142  cvtsi2ss xmm0,eax
0x53e4146  divss xmm0,[rbp+0x114]
0x53e414e  xorps xmm6,xmm6
0x53e4151  cvtss2sd xmm6,xmm0
0x53e4155  mulsd xmm6,[0xEF6D158]
0x53e415d  imul ecx,edx
0x53e4160  mov [rbp+0x10],rcx
0x53e4164  imul eax,edx
0x53e4167  mov [rbp+0x10C],eax
0x53e416d  xor eax,eax
0x53e416f  jmp short 0x53E4197
0x53e4171  nop [rax+rax]
0x53e4180  mov eax,[rbp+0x108]
0x53e4186  inc eax
0x53e4188  mov rdx,[rbp+0x80]
0x53e418f  cmp eax,edx
0x53e4191  jge 0x53E4110
0x53e4197  cvtsi2ss xmm13,eax
0x53e419c  divss xmm13,[rbp+0x110]
0x53e41a5  mov [rbp+0x108],eax
0x53e41ab  mov r12d,eax
0x53e41ae  not r12d
0x53e41b1  addss xmm13,xmm13
0x53e41b6  addss xmm13,[0xEF1D470]
0x53e41bf  add r12d,edx
```

### Phase 10 — 0x53e41c2..0x53e426e: X-loop head: computes voxel base index [rbp+8]=(width-1-x+rowoffset)*height and r12d=(~x+width+row*width)*height, broadcasts xmm13 into xmm14; inner z-loop at 0x53E4200 loads the texel dword [rsi+idx*4], extracts two bytes (cl, ch) into an xmm and converts via cvtdq2ps + mulps [0xF247120]; then checks [rax+0xE0] (rax=[rax+0x68]) against global [0x12968190] (setne r14b) and clamps/muls the texel floats with xmm11/xmm12 before two calls to 0xEEC74F0 (results in xmm8 and the second call's return).
```
0x53e41c2  mov rax,[rbp+0x10]
0x53e41c6  lea ecx,[r12+rax]
0x53e41ca  mov rax,[rbp+0x1E0]
0x53e41d1  imul ecx,eax
0x53e41d4  mov [rbp+8],rcx
0x53e41d8  add r12d,[rbp+0x10C]
0x53e41df  imul r12d,eax
0x53e41e3  movaps xmm14,xmm13
0x53e41e7  shufps xmm14,xmm13,0
0x53e41ec  xor edi,edi
0x53e41ee  jmp 0x53E42AE
0x53e41f3  nop [rax+rax]
0x53e4200  mov rcx,[rbp+8]
0x53e4204  add ecx,edi
0x53e4206  movsxd rcx,ecx
0x53e4209  mov ecx,[rsi+rcx*4]
0x53e420c  movzx edx,ch
0x53e420f  movzx ecx,cl
0x53e4212  movd xmm0,ecx
0x53e4216  pinsrw xmm0,edx,2
0x53e421b  cvtdq2ps xmm1,xmm0
0x53e421e  mulps xmm1,[0xF247120]
0x53e4225  xor ebx,ebx
0x53e4227  mov rax,[rax+0x68]
0x53e422b  mov rcx,[0x12968190]
0x53e4232  xor r14d,r14d
0x53e4235  cmp [rax+0xE0],rcx
0x53e423c  setne r14b
0x53e4240  lea r13d,[rdi+r12]
0x53e4244  movaps xmm7,xmm11
0x53e4248  minss xmm7,xmm1
0x53e424c  shufps xmm1,xmm1,0x55
0x53e4250  movaps xmm0,xmm11
0x53e4254  minss xmm0,xmm1
0x53e4258  mulss xmm0,xmm12
0x53e425d  mulss xmm7,xmm12
0x53e4262  call 0xEEC74F0
0x53e4267  movaps xmm8,xmm0
0x53e426b  movaps xmm0,xmm7
0x53e426e  call 0xEEC74F0
```

### Phase 11 — 0x53e4273..0x53e4334: Converts both 0xEEC74F0 results with cvttss2si and packs the RGBA dword: (r14d<<24)|ebx|(c<<8)|a + 0xFF000000 stored back to [rsi+rcx*4] (in-place texel write); loop control edi vs [rbp+0x1E0]; then the z-loop head at 0x53E42AE computes xmm8 = edi/[rbp+0x104]*2+const([0xEF1D470]) and evaluates xmm6 (row angle) through 0xEEC7420 / addsd [0xEF04EF0] / divsd [0xF247110]; builds xmm0 = (1-angle)*[rbp] + angle*xmm15 as float, and starts assembling a vector from the double pairs at [rbp+0x98/0xA8/0xB8/0xC8] (mulps by zero xmm10 and adds).
```
0x53e4273  cvttss2si eax,xmm0
0x53e4277  cvttss2si ecx,xmm8
0x53e427c  shl r14d,0x18
0x53e4280  or r14d,ebx
0x53e4283  movzx ecx,cl
0x53e4286  shl ecx,8
0x53e4289  add ecx,r14d
0x53e428c  movzx eax,al
0x53e428f  add eax,ecx
0x53e4291  add eax,0xFF000000
0x53e4296  movsxd rcx,r13d
0x53e4299  mov [rsi+rcx*4],eax
0x53e429c  inc edi
0x53e429e  cmp edi,[rbp+0x1E0]
0x53e42a4  lea r14,[rbp+0x30]
0x53e42a8  jge 0x53E4180
0x53e42ae  xorps xmm8,xmm8
0x53e42b2  cvtsi2ss xmm8,edi
0x53e42b7  divss xmm8,[rbp+0x104]
0x53e42c0  addss xmm8,xmm8
0x53e42c5  addss xmm8,[0xEF1D470]
0x53e42ce  movapd xmm0,xmm6
0x53e42d2  call 0xEEC7420
0x53e42d7  addsd xmm0,[0xEF04EF0]
0x53e42df  divsd xmm0,[0xF247110]
0x53e42e7  cvtsd2ss xmm0,xmm0
0x53e42eb  xorps xmm1,xmm1
0x53e42ee  cvtss2sd xmm1,xmm0
0x53e42f2  movsd xmm2,[0xEEC8068]
0x53e42fa  subsd xmm2,xmm1
0x53e42fe  mulsd xmm2,[rbp]
0x53e4303  mulss xmm0,xmm15
0x53e4308  cvtss2sd xmm0,xmm0
0x53e430c  addsd xmm0,xmm2
0x53e4310  cvtsd2ss xmm0,xmm0
0x53e4314  movsd xmm2,[rbp+0x98]
0x53e431c  movsd xmm3,[rbp+0xA8]
0x53e4324  movsd xmm4,[rbp+0xB8]
0x53e432c  movsd xmm1,[rbp+0xC8]
0x53e4334  mulps xmm2,xmm10
```

### Phase 12 — 0x53e4338..0x53e4403: Finishes the ray vector (mulps xmm3,xmm10, addps, perspective divide divss xmm1,xmm0 after shufps 0x55); then transforms it by the 4 row-vectors at [rbp+0x170..0x1AC] (built in Phase 6 via 0xAB49C0): multiplies rows by broadcast xmm8/xmm13/xmm14/xmm1 and accumulates into xmm7/xmm0/xmm4/xmm8 (a world/eye-space position), ending with unpcklps xmm8,xmm2 and addps xmm8,xmm1/xmm4.
```
0x53e4338  mulps xmm3,xmm10
0x53e433c  addps xmm3,xmm2
0x53e433f  shufps xmm0,xmm0,0
0x53e4343  mulps xmm0,xmm4
0x53e4346  subps xmm1,xmm0
0x53e4349  addps xmm1,xmm3
0x53e434c  movaps xmm0,xmm1
0x53e434f  shufps xmm0,xmm1,0x55
0x53e4353  divss xmm1,xmm0
0x53e4357  movss xmm0,[rbp+0x178]
0x53e435f  mulss xmm0,xmm8
0x53e4364  movss xmm2,[rbp+0x170]
0x53e436c  mulss xmm2,xmm8
0x53e4371  movss xmm3,[rbp+0x188]
0x53e4379  mulss xmm3,xmm13
0x53e437e  addss xmm3,xmm0
0x53e4382  movss xmm4,[rbp+0x180]
0x53e438a  mulss xmm4,xmm13
0x53e438f  addss xmm4,xmm2
0x53e4393  movss xmm7,[rbp+0x198]
0x53e439b  mulss xmm7,xmm1
0x53e439f  movss xmm0,[rbp+0x190]
0x53e43a7  addss xmm7,[rbp+0x1A8]
0x53e43af  mulss xmm0,xmm1
0x53e43b3  addss xmm7,xmm3
0x53e43b7  addss xmm0,[rbp+0x1A0]
0x53e43bf  movups xmm2,[rbp+0x174]
0x53e43c6  addss xmm0,xmm4
0x53e43ca  movss xmm3,[rbp+0x17C]
0x53e43d2  movlhps xmm3,xmm2
0x53e43d5  shufps xmm3,xmm2,0xE2
0x53e43d9  movups xmm2,[rbp+0x184]
0x53e43e0  shufps xmm8,xmm8,0
0x53e43e5  mulps xmm3,xmm8
0x53e43e9  movss xmm4,[rbp+0x18C]
0x53e43f1  movlhps xmm4,xmm2
0x53e43f4  shufps xmm4,xmm2,0xE2
0x53e43f8  movups xmm2,[rbp+0x194]
0x53e43ff  mulps xmm4,xmm14
0x53e4403  addps xmm4,xmm3
```

### Phase 13 — 0x53e4406..0x53e44bc: Finishes the matrix transform (third row via movlhps/shufps 0xE2, mulps by broadcast xmm1, unpcklps xmm8 with [rbp+0x1AC]/[rbp+0x1A4]); divides xmm7/xmm8/xmm0 by w (shufps 0x55) and adds the camera offsets [rbp+0x100/0xFC/0xF8]; quantizes via three calls to 0xEEC75A0, cvttps2dq, storing two dwords at [rbp+0x30] and one at [rbp+0x38]; calls 0x32D0F30(r15, rdx=rbp+0x118, r8=r14=rbp+0x30, r9=0), reads word [rbp+0x118] → ebx, and computes block coords [rbp+0x1C0]/[rbp+0x1C4] = [rbp+0x30]/[rbp+0x38] >> 4 (sar 4).
```
0x53e4406  movss xmm3,[rbp+0x19C]
0x53e440e  movlhps xmm3,xmm2
0x53e4411  shufps xmm3,xmm2,0xE2
0x53e4415  shufps xmm1,xmm1,0
0x53e4419  mulps xmm1,xmm3
0x53e441c  movss xmm2,[rbp+0x1AC]
0x53e4424  movss xmm8,[rbp+0x1A4]
0x53e442d  unpcklps xmm8,xmm2
0x53e4431  addps xmm8,xmm1
0x53e4435  addps xmm8,xmm4
0x53e4439  movaps xmm1,xmm8
0x53e443d  shufps xmm1,xmm8,0x55
0x53e4442  divss xmm7,xmm1
0x53e4446  divss xmm8,xmm1
0x53e444b  divss xmm0,xmm1
0x53e444f  addss xmm7,[rbp+0x100]
0x53e4457  addss xmm8,[rbp+0xFC]
0x53e4460  addss xmm0,[rbp+0xF8]
0x53e4468  call 0xEEC75A0
0x53e446d  movaps xmm9,xmm0
0x53e4471  movaps xmm0,xmm8
0x53e4475  call 0xEEC75A0
0x53e447a  unpcklps xmm9,xmm0
0x53e447e  cvttps2dq xmm0,xmm9
0x53e4483  movlps [rbp+0x30],xmm0
0x53e4487  movaps xmm0,xmm7
0x53e448a  call 0xEEC75A0
0x53e448f  cvttss2si eax,xmm0
0x53e4493  mov [rbp+0x38],eax
0x53e4496  mov rcx,r15
0x53e4499  lea rdx,[rbp+0x118]
0x53e44a0  mov r8,r14
0x53e44a3  xor r9d,r9d
0x53e44a6  call 0x32D0F30
0x53e44ab  nop
0x53e44ac  movzx ebx,word ptr [rbp+0x118]
0x53e44b3  mov eax,[rbp+0x30]
0x53e44b6  mov ecx,[rbp+0x38]
0x53e44b9  sar eax,4
0x53e44bc  sar ecx,4
```

### Phase 14 — 0x53e44bf..0x53e4566: Stores the block coords to [rbp+0x1C0]/[rbp+0x1C4]; calls r15's vtable [rax+0x70] with rdx=&[rbp+0x1C0] (bool → r13b) and vtable [rax+0x10] with rdx=r14 (rbp+0x30); loops back to 0x53E4200 while [rbp+0x168]<2 && !r13b; converts word ebx to floats via mulps [0xF0A3FE0] and sets ebx=0xFF0000 when r13b (cmovne); on loop exit 0x53e4543: checks byte[r12+0x368]==0 → 0x53E4CBF, loads rbx=[r12+0x9F8] and calls 0x5A4CB80(rcx=rbp+0x30, rdx=[rbp+0x18]).
```
0x53e44bf  mov [rbp+0x1C0],eax
0x53e44c5  mov [rbp+0x1C4],ecx
0x53e44cb  mov rax,[r15]
0x53e44ce  mov rax,[rax+0x70]
0x53e44d2  mov rcx,r15
0x53e44d5  lea rdx,[rbp+0x1C0]
0x53e44dc  xor r8d,r8d
0x53e44df  call qword ptr [0xF99FFA0]
0x53e44e5  nop
0x53e44e6  mov r13b,al
0x53e44e9  mov rax,[r15]
0x53e44ec  mov rax,[rax+0x10]
0x53e44f0  mov rcx,r15
0x53e44f3  mov rdx,r14
0x53e44f6  call qword ptr [0xF99FFA0]
0x53e44fc  nop
0x53e44fd  cmp dword ptr [rbp+0x168],2
0x53e4504  setae cl
0x53e4507  mov edx,r13d
0x53e450a  xor dl,1
0x53e450d  test cl,dl
0x53e450f  jne 0x53E4200
0x53e4515  movzx ecx,bl
0x53e4518  movzx edx,bh
0x53e451b  movd xmm0,edx
0x53e451f  pinsrw xmm0,ecx,2
0x53e4524  cvtdq2ps xmm1,xmm0
0x53e4527  mulps xmm1,[0xF0A3FE0]
0x53e452e  test r13b,r13b
0x53e4531  mov ebx,0
0x53e4536  mov ecx,0xFF0000
0x53e453b  cmovne ebx,ecx
0x53e453e  jmp 0x53E4227
0x53e4543  mov rax,[rbp+0x1B8]
0x53e454a  cmp byte ptr [rax+0x368],0
0x53e4551  je 0x53E4CBF
0x53e4557  mov rbx,[rax+0x9F8]
0x53e455e  lea rcx,[rbp+0x30]
0x53e4562  mov rdx,[rbp+0x18]
0x53e4566  call 0x5A4CB80
```

### Phase 15 — 0x53e456b..0x53e4613: Calls 0x5420860(rbx, rdx=[rbp-0x48], r8=[rbp+0x30]); then 0x541F8F0(rcx=[r12+0x9F8]+0x18, rdx=rbp+0x90, r8=rbp-0x48, r9=0, stack args 0); picks rax = [rbp+0x90] if nonzero else global 0x129C1210, zero-inits [rbp+0x1C0..0x1CF], reads the object's refcount block ([rax] / [rax+8] with lock inc [rcx+8], word [rcx+0x10]) and stores the shared-ptr pair to [rbp+0x1C0]/[rbp+0x1C8]; releases the old pointer rdi=[rbp+0x1C8] (lock dec, vtable calls, dec [rdi+0xC]); reloads r12=[rbp+0x1B8], r13=[rbp+0x88].
```
0x53e456b  nop
0x53e456c  lea rdx,[rbp-0x48]
0x53e4570  lea r8,[rbp+0x30]
0x53e4574  mov rcx,rbx
0x53e4577  call 0x5420860
0x53e457c  nop
0x53e457d  mov rax,[rbp+0x1B8]
0x53e4584  mov rcx,[rax+0x9F8]
0x53e458b  add rcx,0x18
0x53e458f  mov byte ptr [rsp+0x28],0
0x53e4594  mov qword ptr [rsp+0x20],0
0x53e459d  lea rdx,[rbp+0x90]
0x53e45a4  lea r8,[rbp-0x48]
0x53e45a8  xor r9d,r9d
0x53e45ab  call 0x541F8F0
0x53e45b0  nop
0x53e45b1  mov rcx,[rbp+0x90]
0x53e45b8  test rcx,rcx
0x53e45bb  lea rax,[0x129C1210]
0x53e45c2  cmovne rax,rcx
0x53e45c6  xorps xmm0,xmm0
0x53e45c9  movaps [rbp+0x1C0],xmm0
0x53e45d0  mov rcx,[rax]
0x53e45d3  test rcx,rcx
0x53e45d6  je short 0x53E45DC
0x53e45d8  movzx ecx,word ptr [rcx+0x10]
0x53e45dc  mov rcx,[rax+8]
0x53e45e0  test rcx,rcx
0x53e45e3  je short 0x53E45EF
0x53e45e5  lock inc dword ptr [rcx+8]
0x53e45e9  mov rcx,[rax+8]
0x53e45ed  jmp short 0x53E45F1
0x53e45ef  xor ecx,ecx
0x53e45f1  mov rax,[rax]
0x53e45f4  mov [rbp+0x1C0],rax
0x53e45fb  mov rdi,[rbp+0x1C8]
0x53e4602  mov [rbp+0x1C8],rcx
0x53e4609  test rdi,rdi
0x53e460c  mov r12,[rbp+0x1B8]
0x53e4613  mov r13,[rbp+0x88]
```

### Phase 16 — 0x53e461a..0x53e46b4: Finishes releasing the old shared-ptr rdi (lock dec [rdi+8], vtable delete calls, lock dec [rdi+0xC]); calls 0x4DFB570(rcx=rbp+0x170, rdx=rdi=&[rbp+0x1C0]); then a shared_ptr assign for the result at [rbp+0x178]: increments [rax+8], moves [rbp+0x170]/[rbp+0x158] into [rbp+0x150]/[rbp+0x158] and releases the old rbx=[rbp+0x158] the same way.
```
0x53e461a  je short 0x53E4648
0x53e461c  lock dec dword ptr [rdi+8]
0x53e4620  jne short 0x53E4648
0x53e4622  mov rax,[rdi]
0x53e4625  mov rax,[rax]
0x53e4628  mov rcx,rdi
0x53e462b  call qword ptr [0xF99FFA0]
0x53e4631  lock dec dword ptr [rdi+0xC]
0x53e4635  jne short 0x53E4648
0x53e4637  mov rax,[rdi]
0x53e463a  mov rax,[rax+8]
0x53e463e  mov rcx,rdi
0x53e4641  call qword ptr [0xF99FFA0]
0x53e4647  nop
0x53e4648  lea rcx,[rbp+0x170]
0x53e464f  lea rdi,[rbp+0x1C0]
0x53e4656  mov rdx,rdi
0x53e4659  call 0x4DFB570
0x53e465e  nop
0x53e465f  mov rax,[rbp+0x178]
0x53e4666  test rax,rax
0x53e4669  je short 0x53E4678
0x53e466b  lock inc dword ptr [rax+8]
0x53e466f  mov rax,[rbp+0x178]
0x53e4676  jmp short 0x53E467A
0x53e4678  xor eax,eax
0x53e467a  mov rcx,[rbp+0x170]
0x53e4681  mov [rbp+0x150],rcx
0x53e4688  mov rbx,[rbp+0x158]
0x53e468f  mov [rbp+0x158],rax
0x53e4696  test rbx,rbx
0x53e4699  je short 0x53E46C6
0x53e469b  lock dec dword ptr [rbx+8]
0x53e469f  jne short 0x53E46C6
0x53e46a1  mov rax,[rbx]
0x53e46a4  mov rax,[rax]
0x53e46a7  mov rcx,rbx
0x53e46aa  call qword ptr [0xF99FFA0]
0x53e46b0  lock dec dword ptr [rbx+0xC]
0x53e46b4  jne short 0x53E46C6
```

### Phase 17 — 0x53e46b6..0x53e4746: Completes the release of rbx; releases rbx=[rbp+0x178] (the 0x4DFB570 input), rbx=[rbp+0x1C8], and rbx=[rbp+0xA8] in turn — each the same refcount-2 pattern (lock dec [rbx+8], vtable delete, lock dec [rbx+0xC]).
```
0x53e46b6  mov rax,[rbx]
0x53e46b9  mov rax,[rax+8]
0x53e46bd  mov rcx,rbx
0x53e46c0  call qword ptr [0xF99FFA0]
0x53e46c6  mov rbx,[rbp+0x178]
0x53e46cd  test rbx,rbx
0x53e46d0  je short 0x53E46FD
0x53e46d2  lock dec dword ptr [rbx+8]
0x53e46d6  jne short 0x53E46FD
0x53e46d8  mov rax,[rbx]
0x53e46db  mov rax,[rax]
0x53e46de  mov rcx,rbx
0x53e46e1  call qword ptr [0xF99FFA0]
0x53e46e7  lock dec dword ptr [rbx+0xC]
0x53e46eb  jne short 0x53E46FD
0x53e46ed  mov rax,[rbx]
0x53e46f0  mov rax,[rax+8]
0x53e46f4  mov rcx,rbx
0x53e46f7  call qword ptr [0xF99FFA0]
0x53e46fd  mov rbx,[rbp+0x1C8]
0x53e4704  test rbx,rbx
0x53e4707  je short 0x53E4734
0x53e4709  lock dec dword ptr [rbx+8]
0x53e470d  jne short 0x53E4734
0x53e470f  mov rax,[rbx]
0x53e4712  mov rax,[rax]
0x53e4715  mov rcx,rbx
0x53e4718  call qword ptr [0xF99FFA0]
0x53e471e  lock dec dword ptr [rbx+0xC]
0x53e4722  jne short 0x53E4734
0x53e4724  mov rax,[rbx]
0x53e4727  mov rax,[rax+8]
0x53e472b  mov rcx,rbx
0x53e472e  call qword ptr [0xF99FFA0]
0x53e4734  mov rbx,[rbp+0xA8]
0x53e473b  test rbx,rbx
0x53e473e  je short 0x53E476B
0x53e4740  lock dec dword ptr [rbx+8]
0x53e4744  jne short 0x53E476B
0x53e4746  mov rax,[rbx]
```

### Phase 18 — 0x53e4749..0x53e47eb: Finishes releasing [rbp+0xA8] and [rbp+0x98] (same refcount pattern); DEADC0DE guard on [rbp+0x138]; rbx=[rbp+0x148]; copies byte [r13+0x74] → word [rbp+0x1C0], zero-inits [rbp+0x1C8..0x1D7] via movups, then increments [rax+8] on [rbp+0x158] and stores the shared-ptr pair {ptr=[rbp+0x150], ref=[rbp+0x158]} into [rbp+0x1C8]/[rbp+0x1D0].
```
0x53e4749  mov rax,[rax]
0x53e474c  mov rcx,rbx
0x53e474f  call qword ptr [0xF99FFA0]
0x53e4755  lock dec dword ptr [rbx+0xC]
0x53e4759  jne short 0x53E476B
0x53e475b  mov rax,[rbx]
0x53e475e  mov rax,[rax+8]
0x53e4762  mov rcx,rbx
0x53e4765  call qword ptr [0xF99FFA0]
0x53e476b  mov rbx,[rbp+0x98]
0x53e4772  test rbx,rbx
0x53e4775  je short 0x53E47A2
0x53e4777  lock dec dword ptr [rbx+8]
0x53e477b  jne short 0x53E47A2
0x53e477d  mov rax,[rbx]
0x53e4780  mov rax,[rax]
0x53e4783  mov rcx,rbx
0x53e4786  call qword ptr [0xF99FFA0]
0x53e478c  lock dec dword ptr [rbx+0xC]
0x53e4790  jne short 0x53E47A2
0x53e4792  mov rax,[rbx]
0x53e4795  mov rax,[rax+8]
0x53e4799  mov rcx,rbx
0x53e479c  call qword ptr [0xF99FFA0]
0x53e47a2  mov rax,[rbp+0x138]
0x53e47a9  test rax,rax
0x53e47ac  je short 0x53E47BE
0x53e47ae  cmp byte ptr [rax],0
0x53e47b1  jne short 0x53E47BE
0x53e47b3  mov dword ptr [0],0xDEADC0DE
0x53e47be  mov rbx,[rbp+0x148]
0x53e47c5  movzx eax,byte ptr [r13+0x74]
0x53e47ca  mov [rbp+0x1C0],ax
0x53e47d1  xorps xmm0,xmm0
0x53e47d4  movups [rbp+0x1C8],xmm0
0x53e47db  mov rax,[rbp+0x158]
0x53e47e2  test rax,rax
0x53e47e5  je short 0x53E47F4
0x53e47e7  lock inc dword ptr [rax+8]
0x53e47eb  mov rax,[rbp+0x158]
```

### Phase 19 — 0x53e47f2..0x53e48c8: Stores the shared-ptr (rcx=[rbp+0x150], rax=[rbp+0x158]) to [rbp+0x1C8]/[rbp+0x1D0]; checks the TLS refcount guard ([0x129C60D8] vs gs:[0x58]-based [rcx+4], jg 0x53E4CC5); sets [rbp+0x170]=0x129C5FA0, byte[rbp+0x178]=0, [rbp+0x188]=0, byte[rbp+0xC8]=0; calls 0x39A7D40(rdx=r14=rbp+0x180, r8=rbp+0x90) storing its bool to [rbp+0x178]; sets [rbp+0x90]=rdi, byte[rbp+0x98]=0xA; calls rbx's vtable [rax+0x370] with rdx=rbp+0x90; if [rbp+0x178]==1 calls 0x77A2500(rcx=0x1244FD00, rdx=r14, r8=[rbp+0x170]+0x60).
```
0x53e47f2  jmp short 0x53E47F6
0x53e47f4  xor eax,eax
0x53e47f6  mov rcx,[rbp+0x150]
0x53e47fd  mov [rbp+0x1C8],rcx
0x53e4804  mov [rbp+0x1D0],rax
0x53e480b  mov eax,[0x129C60D8]
0x53e4811  mov ecx,[0x128767C8]
0x53e4817  mov rdx,gs:[0x58]
0x53e4820  mov rcx,[rdx+rcx*8]
0x53e4824  cmp eax,[rcx+4]
0x53e482a  jg 0x53E4CC5
0x53e4830  lea rcx,[0x129C5FA0]
0x53e4837  mov [rbp+0x170],rcx
0x53e483e  mov byte ptr [rbp+0x178],0
0x53e4845  lea r14,[rbp+0x180]
0x53e484c  mov qword ptr [rbp+0x188],0
0x53e4857  mov byte ptr [rbp+0xC8],0
0x53e485e  lea r8,[rbp+0x90]
0x53e4865  mov rdx,r14
0x53e4868  call 0x39A7D40
0x53e486d  nop
0x53e486e  mov [rbp+0x178],al
0x53e4874  mov [rbp+0x90],rdi
0x53e487b  mov byte ptr [rbp+0x98],0xA
0x53e4882  mov rax,[rbx]
0x53e4885  mov rax,[rax+0x370]
0x53e488c  lea rdx,[rbp+0x90]
0x53e4893  mov rcx,rbx
0x53e4896  call qword ptr [0xF99FFA0]
0x53e489c  nop
0x53e489d  cmp byte ptr [rbp+0x178],1
0x53e48a4  jne short 0x53E48C1
0x53e48a6  mov r8,[rbp+0x170]
0x53e48ad  add r8,0x60
0x53e48b1  lea rcx,[0x1244FD00]
0x53e48b8  mov rdx,r14
0x53e48bb  call 0x77A2500
0x53e48c0  nop
0x53e48c1  mov rdi,[rbp+0x1D0]
0x53e48c8  test rdi,rdi
```

### Phase 20 — 0x53e48cb..0x53e49b9: Releases the shared-ptr rdi=[rbp+0x1D0] (standard pattern); DEADC0DE guard on r14=[rbp+0x138]; rdi=[rbp+0x148]; copies byte [r13+0x74] → word [rbp+0x90]; then builds a parameter struct at rbp+0x90 from r12 fields: movsd [r12+0x45C]→[rbp+0x94], movss [r12+0x464]→[rbp+0x9C], movups [r12+0x468]→[rbp+0xA0], movups [r12+0x478]→[rbp+0xB0], movss [r12+0x4C8]→[rbp+0xC0], movups [r12+0x488]→[rbp+0xC4], movups [r12+0x498]→[rbp+0xD4], movss [r12+0x4CC]→[rbp+0xE4], byte [r12+0x968]→[rbp+0xE8].
```
0x53e48cb  je short 0x53E48F8
0x53e48cd  lock dec dword ptr [rdi+8]
0x53e48d1  jne short 0x53E48F8
0x53e48d3  mov rax,[rdi]
0x53e48d6  mov rax,[rax]
0x53e48d9  mov rcx,rdi
0x53e48dc  call qword ptr [0xF99FFA0]
0x53e48e2  lock dec dword ptr [rdi+0xC]
0x53e48e6  jne short 0x53E48F8
0x53e48e8  mov rax,[rdi]
0x53e48eb  mov rax,[rax+8]
0x53e48ef  mov rcx,rdi
0x53e48f2  call qword ptr [0xF99FFA0]
0x53e48f8  mov r14,[rbp+0x138]
0x53e48ff  test r14,r14
0x53e4902  je short 0x53E4915
0x53e4904  cmp byte ptr [r14],0
0x53e4908  jne short 0x53E4915
0x53e490a  mov dword ptr [0],0xDEADC0DE
0x53e4915  mov rdi,[rbp+0x148]
0x53e491c  movzx eax,byte ptr [r13+0x74]
0x53e4921  mov [rbp+0x90],ax
0x53e4928  movsd xmm0,[r12+0x45C]
0x53e4932  movsd [rbp+0x94],xmm0
0x53e493a  movss xmm0,[r12+0x464]
0x53e4944  movss [rbp+0x9C],xmm0
0x53e494c  movups xmm0,[r12+0x468]
0x53e4955  movups [rbp+0xA0],xmm0
0x53e495c  movups xmm0,[r12+0x478]
0x53e4965  movups [rbp+0xB0],xmm0
0x53e496c  movss xmm0,[r12+0x4C8]
0x53e4976  movss [rbp+0xC0],xmm0
0x53e497e  movups xmm0,[r12+0x488]
0x53e4987  movups [rbp+0xC4],xmm0
0x53e498e  movups xmm0,[r12+0x498]
0x53e4997  movups [rbp+0xD4],xmm0
0x53e499e  movss xmm0,[r12+0x4CC]
0x53e49a8  movss [rbp+0xE4],xmm0
0x53e49b0  movzx eax,byte ptr [r12+0x968]
0x53e49b9  mov [rbp+0xE8],al
```

### Phase 21 — 0x53e49bf..0x53e4a8e: TLS refcount guard ([0x129C6218] vs gs:[0x58]-based [rcx+4], jg 0x53E4C36); sets [rbp+0x1C0]=0x129C60E0, byte[rbp+0x1C8]=0, [rbp+0x1D8]=0, byte[rbp+0x1A8]=0; calls 0x39A7D40(rdx=rbx=rbp+0x1D0, r8=rbp+0x170) storing its bool to [rbp+0x1C8]; sets [rbp+0x170]=&[rbp+0x90], byte[rbp+0x178]=8; calls rdi's vtable [rax+0x370] with rdx=rbp+0x170; if [rbp+0x1C8]==1 calls 0x77A2500(rcx=0x1244FD00, rdx=rbx, r8=[rbp+0x1C0]+0x60); then begins releasing rsi=[rbp+0x158].
```
0x53e49bf  mov eax,[0x129C6218]
0x53e49c5  mov ecx,[0x128767C8]
0x53e49cb  mov rdx,gs:[0x58]
0x53e49d4  mov rcx,[rdx+rcx*8]
0x53e49d8  cmp eax,[rcx+4]
0x53e49de  jg 0x53E4C36
0x53e49e4  lea rcx,[0x129C60E0]
0x53e49eb  mov [rbp+0x1C0],rcx
0x53e49f2  mov byte ptr [rbp+0x1C8],0
0x53e49f9  lea rbx,[rbp+0x1D0]
0x53e4a00  mov qword ptr [rbp+0x1D8],0
0x53e4a0b  mov byte ptr [rbp+0x1A8],0
0x53e4a12  lea r8,[rbp+0x170]
0x53e4a19  mov rdx,rbx
0x53e4a1c  call 0x39A7D40
0x53e4a21  nop
0x53e4a22  mov [rbp+0x1C8],al
0x53e4a28  lea rax,[rbp+0x90]
0x53e4a2f  mov [rbp+0x170],rax
0x53e4a36  mov byte ptr [rbp+0x178],8
0x53e4a3d  mov rax,[rdi]
0x53e4a40  mov rax,[rax+0x370]
0x53e4a47  lea rdx,[rbp+0x170]
0x53e4a4e  mov rcx,rdi
0x53e4a51  call qword ptr [0xF99FFA0]
0x53e4a57  nop
0x53e4a58  cmp byte ptr [rbp+0x1C8],1
0x53e4a5f  jne short 0x53E4A7C
0x53e4a61  mov r8,[rbp+0x1C0]
0x53e4a68  add r8,0x60
0x53e4a6c  lea rcx,[0x1244FD00]
0x53e4a73  mov rdx,rbx
0x53e4a76  call 0x77A2500
0x53e4a7b  nop
0x53e4a7c  mov rsi,[rbp+0x158]
0x53e4a83  test rsi,rsi
0x53e4a86  je short 0x53E4AB3
0x53e4a88  lock dec dword ptr [rsi+8]
0x53e4a8c  jne short 0x53E4AB3
0x53e4a8e  mov rax,[rsi]
```

### Phase 22 — 0x53e4a91..0x53e4b20: Finishes releasing rsi=[rbp+0x158]; frees the temp string buffer (the one built in Phase 5, now at [rbp-0x48]): if len [rbp-0x28] >= 0x10 and needs heap, calls the free via [rbp-0x40]-based header math, else 0xE935700(rcx=ptr, rdx=len+1); then releases rsi=[rbp+0x78] (same shared-ptr pattern).
```
0x53e4a91  mov rax,[rax]
0x53e4a94  mov rcx,rsi
0x53e4a97  call qword ptr [0xF99FFA0]
0x53e4a9d  lock dec dword ptr [rsi+0xC]
0x53e4aa1  jne short 0x53E4AB3
0x53e4aa3  mov rax,[rsi]
0x53e4aa6  mov rax,[rax+8]
0x53e4aaa  mov rcx,rsi
0x53e4aad  call qword ptr [0xF99FFA0]
0x53e4ab3  mov rax,[rbp-0x28]
0x53e4ab7  cmp rax,0x10
0x53e4abb  jb short 0x53E4AF2
0x53e4abd  mov rcx,[rbp-0x40]
0x53e4ac1  lea rdx,[rax+1]
0x53e4ac5  cmp rdx,0x1000
0x53e4acc  jb short 0x53E4AED
0x53e4ace  mov r8,[rcx-8]
0x53e4ad2  add rcx,0xFFFFFFFFFFFFFFF8
0x53e4ad6  sub rcx,r8
0x53e4ad9  cmp rcx,0x20
0x53e4add  jae 0x53E4D5C
0x53e4ae3  add rax,0x28
0x53e4ae7  mov rdx,rax
0x53e4aea  mov rcx,r8
0x53e4aed  call 0xE935700
0x53e4af2  mov rsi,[rbp+0x78]
0x53e4af6  test rsi,rsi
0x53e4af9  je short 0x53E4B26
0x53e4afb  lock dec dword ptr [rsi+8]
0x53e4aff  jne short 0x53E4B26
0x53e4b01  mov rax,[rsi]
0x53e4b04  mov rax,[rax]
0x53e4b07  mov rcx,rsi
0x53e4b0a  call qword ptr [0xF99FFA0]
0x53e4b10  lock dec dword ptr [rsi+0xC]
0x53e4b14  jne short 0x53E4B26
0x53e4b16  mov rax,[rsi]
0x53e4b19  mov rax,[rax+8]
0x53e4b1d  mov rcx,rsi
0x53e4b20  call qword ptr [0xF99FFA0]
```

### Phase 23 — 0x53e4b26..0x53e4bcc: Zeroes the record [rbp+0x138..0x147] via movups and releases rsi=[rbp+0x140] (shared-ptr pattern, twice: [rbp+0x140] then [rbp+0x148] with [rbp+0x148]=0); if byte[rbp+0x130]==1 calls 0x3B2020([rbp+0x128]); then epilogue begins: restores xmm6, xmm7, xmm8 from the frame.
```
0x53e4b26  xorps xmm0,xmm0
0x53e4b29  mov rsi,[rbp+0x140]
0x53e4b30  movups [rbp+0x138],xmm0
0x53e4b37  test rsi,rsi
0x53e4b3a  je short 0x53E4BA9
0x53e4b3c  lock dec dword ptr [rsi+8]
0x53e4b40  jne short 0x53E4B67
0x53e4b42  mov rax,[rsi]
0x53e4b45  mov rax,[rax]
0x53e4b48  mov rcx,rsi
0x53e4b4b  call qword ptr [0xF99FFA0]
0x53e4b51  lock dec dword ptr [rsi+0xC]
0x53e4b55  jne short 0x53E4B67
0x53e4b57  mov rax,[rsi]
0x53e4b5a  mov rax,[rax+8]
0x53e4b5e  mov rcx,rsi
0x53e4b61  call qword ptr [0xF99FFA0]
0x53e4b67  mov rsi,[rbp+0x140]
0x53e4b6e  mov qword ptr [rbp+0x148],0
0x53e4b79  test rsi,rsi
0x53e4b7c  je short 0x53E4BA9
0x53e4b7e  lock dec dword ptr [rsi+8]
0x53e4b82  jne short 0x53E4BA9
0x53e4b84  mov rax,[rsi]
0x53e4b87  mov rax,[rax]
0x53e4b8a  mov rcx,rsi
0x53e4b8d  call qword ptr [0xF99FFA0]
0x53e4b93  lock dec dword ptr [rsi+0xC]
0x53e4b97  jne short 0x53E4BA9
0x53e4b99  mov rax,[rsi]
0x53e4b9c  mov rax,[rax+8]
0x53e4ba0  mov rcx,rsi
0x53e4ba3  call qword ptr [0xF99FFA0]
0x53e4ba9  cmp byte ptr [rbp+0x130],1
0x53e4bb0  jne short 0x53E4BBE
0x53e4bb2  mov rcx,[rbp+0x128]
0x53e4bb9  call 0x3B2020
0x53e4bbe  movaps xmm6,[rbp+0x1F0]
0x53e4bc5  movaps xmm7,[rbp+0x200]
0x53e4bcc  movaps xmm8,[rbp+0x210]
```

### Phase 24 — 0x53e4bd4..0x53e4c9c: Epilogue: restores xmm9-xmm15 from the frame, add rsp,0x318, pops and ret; out-of-line stubs: 0x53e4c20 calls 0x78ED0 (assert); 0x53e4c26 allocates 0x20 via 0x9BC830 and jumps back to 0x53E3E1B; 0x53e4c36 refreshes the TLS refcount [0x129C6218] via 0xE938CB0/0xE938D70 and on 0xFFFFFFFF failure builds an error message at [rbp+0x118] (ptr [0xF52E07A], len 0x15, const xmm from [0xF0BCBF8], arg [0xF248EB0]) and calls 0x2FE330 with r8b=1, then 0xE935740(0x53DECC0).
```
0x53e4bd4  movaps xmm9,[rbp+0x220]
0x53e4bdc  movaps xmm10,[rbp+0x230]
0x53e4be4  movaps xmm11,[rbp+0x240]
0x53e4bec  movaps xmm12,[rbp+0x250]
0x53e4bf4  movaps xmm13,[rbp+0x260]
0x53e4bfc  movaps xmm14,[rbp+0x270]
0x53e4c04  movaps xmm15,[rbp+0x280]
0x53e4c0c  add rsp,0x318
0x53e4c13  pop rbx
0x53e4c14  pop rdi
0x53e4c15  pop rsi
0x53e4c16  pop r12
0x53e4c18  pop r13
0x53e4c1a  pop r14
0x53e4c1c  pop r15
0x53e4c1e  pop rbp
0x53e4c1f  ret
0x53e4c20  call 0x78ED0
0x53e4c25  nop
0x53e4c26  mov ecx,0x20
0x53e4c2b  call 0x9BC830
0x53e4c30  nop
0x53e4c31  jmp 0x53E3E1B
0x53e4c36  lea rcx,[0x129C6218]
0x53e4c3d  call 0xE938CB0
0x53e4c42  cmp dword ptr [0x129C6218],0xFFFFFFFF
0x53e4c49  jne 0x53E49E4
0x53e4c4f  lea rax,[0xF52E07A]
0x53e4c56  mov [rbp+0x118],rax
0x53e4c5d  mov qword ptr [rbp+0x120],0x15
0x53e4c68  movups xmm0,[0xF0BCBF8]
0x53e4c6f  movaps [rbp+0x20],xmm0
0x53e4c73  lea rax,[0xF248EB0]
0x53e4c7a  mov [rsp+0x28],rax
0x53e4c7f  mov dword ptr [rsp+0x20],0
0x53e4c87  lea rcx,[0x129C60E0]
0x53e4c8e  lea rdx,[rbp+0x20]
0x53e4c92  lea r9,[rbp+0x118]
0x53e4c99  mov r8b,1
0x53e4c9c  call 0x2FE330
```

### Phase 25 — 0x53e4ca1..0x53e4d75: Finishes the error path (0xE935740(0x53DECC0), 0xE938D70(0x129C6218), jmp 0x53E49E4); mirror stub 0x53e4cbf calls 0x1A2800 (assert); 0x53e4cc5 is the [0x129C60D8] TLS guard twin (0xE938CB0, on 0xFFFFFFFF builds the same message with arg [0xF248E90], 0x2FE330, 0xE935740(0x53DECB0), 0xE938D70, reloads r12/r13 and jmp 0x53E4830); 0x53e4d5c is the huge-allocation failure path: zero stack args and call [0xF9A8C78], ending in int3.
```
0x53e4ca1  nop
0x53e4ca2  lea rcx,[0x53DECC0]
0x53e4ca9  call 0xE935740
0x53e4cae  lea rcx,[0x129C6218]
0x53e4cb5  call 0xE938D70
0x53e4cba  jmp 0x53E49E4
0x53e4cbf  call 0x1A2800
0x53e4cc4  nop
0x53e4cc5  lea rcx,[0x129C60D8]
0x53e4ccc  call 0xE938CB0
0x53e4cd1  cmp dword ptr [0x129C60D8],0xFFFFFFFF
0x53e4cd8  jne 0x53E4830
0x53e4cde  lea rax,[0xF52E07A]
0x53e4ce5  mov [rbp+0x118],rax
0x53e4cec  mov qword ptr [rbp+0x120],0x15
0x53e4cf7  movups xmm0,[0xF0BCBF8]
0x53e4cfe  movaps [rbp+0x20],xmm0
0x53e4d02  lea rax,[0xF248E90]
0x53e4d09  mov [rsp+0x28],rax
0x53e4d0e  mov dword ptr [rsp+0x20],0
0x53e4d16  lea rcx,[0x129C5FA0]
0x53e4d1d  lea rdx,[rbp+0x20]
0x53e4d21  lea r9,[rbp+0x118]
0x53e4d28  mov r8b,1
0x53e4d2b  call 0x2FE330
0x53e4d30  nop
0x53e4d31  lea rcx,[0x53DECB0]
0x53e4d38  call 0xE935740
0x53e4d3d  lea rcx,[0x129C60D8]
0x53e4d44  call 0xE938D70
0x53e4d49  mov r12,[rbp+0x1B8]
0x53e4d50  mov r13,[rbp+0x88]
0x53e4d57  jmp 0x53E4830
0x53e4d5c  mov qword ptr [rsp+0x20],0
0x53e4d65  xor ecx,ecx
0x53e4d67  xor edx,edx
0x53e4d69  xor r8d,r8d
0x53e4d6c  xor r9d,r9d
0x53e4d6f  call qword ptr [0xF9A8C78]
0x53e4d75  int3
```

### Phase 26 — 0x53e4d76: Final 8-byte alignment padding nop after the int3; end of the listing range.
```
0x53e4d76  nop [rax+rax]
```

## Field table — every fixed `[reg+off]` field (one row per distinct field, all sites listed)

`offset` is `base+off` as it appears in the verbatim lines; `size` in bytes comes from the instruction (movups/movaps 16, qword/movsd 8, dword/movss 4, word 2, byte 1 — listed per site order when a field is touched at several widths); `dir` per site: R = read, W = write, RMW = read-modify-write. Meaning is given only where the instruction itself shows the role. [V] mechanical, [I] inferred from instruction behavior.

| offset | size | dir (per site) | verbatim line(s) | meaning |
|---|---|---|---|---|
| r12+0x338 | 8 | 0x53e3d6f:R | `0x53e3d6f  mov rax,[r12+0x338]` | - |
| r12+0x340 | 8 | 0x53e3d62:R, 0x53e3d90:R | `0x53e3d62  mov rcx,[r12+0x340]`<br>`0x53e3d90  mov rcx,[r12+0x340]` | - |
| r12+0x350 | 4 | 0x53e3cd1:R | `0x53e3cd1  cmp [r12+0x350],eax` | - |
| r12+0x354 | 4 | 0x53e3cdb:R | `0x53e3cdb  cmp [r12+0x354],edi` | - |
| r12+0x360 | 4 | 0x53e3cc0:R | `0x53e3cc0  cmp [r12+0x360],eax` | - |
| r12+0x368 | 1 | 0x53e3c9f:R, 0x53e3d37:R, 0x53e3d53:R, 0x53e3d7e:W, 0x53e3da7:W, 0x53e3dc1:W, 0x53e3e9c:R | `0x53e3c9f  movzx eax,byte ptr [r12+0x368]`<br>`0x53e3d37  cmp byte ptr [r12+0x368],1`<br>`0x53e3d53  cmp byte ptr [r12+0x368],1`<br>`0x53e3d7e  mov byte ptr [r12+0x368],0`<br>`0x53e3da7  mov byte ptr [r12+0x368],0`<br>`0x53e3dc1  mov byte ptr [r12+0x368],1`<br>`0x53e3e9c  cmp byte ptr [r12+0x368],0` | 1-byte flag: tested against 0/1, written 0/1 [I] |
| r12+0x45C | 8 | 0x53e4928:R | `0x53e4928  movsd xmm0,[r12+0x45C]` | - |
| r12+0x464 | 4 | 0x53e493a:R | `0x53e493a  movss xmm0,[r12+0x464]` | - |
| r12+0x468 | 16 | 0x53e494c:R | `0x53e494c  movups xmm0,[r12+0x468]` | - |
| r12+0x478 | 16 | 0x53e495c:R | `0x53e495c  movups xmm0,[r12+0x478]` | - |
| r12+0x488 | 16 | 0x53e497e:R | `0x53e497e  movups xmm0,[r12+0x488]` | - |
| r12+0x498 | 16 | 0x53e498e:R | `0x53e498e  movups xmm0,[r12+0x498]` | - |
| r12+0x4C8 | 4 | 0x53e496c:R | `0x53e496c  movss xmm0,[r12+0x4C8]` | - |
| r12+0x4CC | 4 | 0x53e499e:R | `0x53e499e  movss xmm0,[r12+0x4CC]` | - |
| r12+0x64C | 4 | 0x53e3ebe:R | `0x53e3ebe  movss xmm0,[r12+0x64C]` | - |
| r12+0x650 | 4 | 0x53e3ed0:R | `0x53e3ed0  movss xmm0,[r12+0x650]` | - |
| r12+0x654 | 4 | 0x53e3ee9:R | `0x53e3ee9  movss xmm0,[r12+0x654]` | - |
| r12+0x968 | 1 | 0x53e49b0:R | `0x53e49b0  movzx eax,byte ptr [r12+0x968]` | - |
| r12+0x978 | 8 | 0x53e3eb6:R | `0x53e3eb6  mov r15,[r12+0x978]` | pointer read into r15; [r15] is read afterwards [I] |
| r13+0x18 | 8 | 0x53e3f02:R | `0x53e3f02  mov rax,[r13+0x18]` | - |
| r13+0x74 | 1 | 0x53e47c5:R, 0x53e491c:R | `0x53e47c5  movzx eax,byte ptr [r13+0x74]`<br>`0x53e491c  movzx eax,byte ptr [r13+0x74]` | 1-byte value tested against 0/1 [I] |
| r14+0x0 | 1 | 0x53e3b47:R, 0x53e3bdb:R, 0x53e3c17:R, 0x53e3c3a:R, 0x53e4904:R | `0x53e3b47  cmp byte ptr [r14],1`<br>`0x53e3bdb  cmp byte ptr [r14],0`<br>`0x53e3c17  cmp byte ptr [r14],1`<br>`0x53e3c3a  cmp byte ptr [r14],0`<br>`0x53e4904  cmp byte ptr [r14],0` | 1-byte value tested against 0/1 [I] |
| r15+0x0 | 8 | 0x53e44cb:R, 0x53e44e9:R | `0x53e44cb  mov rax,[r15]`<br>`0x53e44e9  mov rax,[r15]` | - |
| rax+0x0 | 8 (also 1) | 0x53e45d0:R, 0x53e45f1:R, 0x53e4625:R, 0x53e46a4:R, 0x53e46db:R, 0x53e4712:R, 0x53e4749:R, 0x53e4780:R, 0x53e47ae:R, 0x53e48d6:R, 0x53e4a91:R, 0x53e4b04:R, 0x53e4b45:R, 0x53e4b87:R | `0x53e45d0  mov rcx,[rax]`<br>`0x53e45f1  mov rax,[rax]`<br>`0x53e4625  mov rax,[rax]`<br>`0x53e46a4  mov rax,[rax]`<br>`0x53e46db  mov rax,[rax]`<br>`0x53e4712  mov rax,[rax]`<br>`0x53e4749  mov rax,[rax]`<br>`0x53e4780  mov rax,[rax]`<br>`0x53e47ae  cmp byte ptr [rax],0`<br>`0x53e48d6  mov rax,[rax]`<br>`0x53e4a91  mov rax,[rax]`<br>`0x53e4b04  mov rax,[rax]`<br>`0x53e4b45  mov rax,[rax]`<br>`0x53e4b87  mov rax,[rax]` | - |
| rax+0x10 | 8 | 0x53e3f6f:R, 0x53e44ec:R | `0x53e3f6f  mov rax,[rax+0x10]`<br>`0x53e44ec  mov rax,[rax+0x10]` | - |
| rax+0x18 | 8 | 0x53e3f61:R | `0x53e3f61  mov r8,[rax+0x18]` | - |
| rax+0x20 | 8 | 0x53e3f5d:R | `0x53e3f5d  mov rcx,[rax+0x20]` | - |
| rax+0x68 | 8 | 0x53e4227:R | `0x53e4227  mov rax,[rax+0x68]` | - |
| rax+0x70 | 8 | 0x53e44ce:R | `0x53e44ce  mov rax,[rax+0x70]` | - |
| rax+0x88 | 8 | 0x53e3f1a:R | `0x53e3f1a  mov rdx,[rax+0x88]` | - |
| rax+0x90 | 8 | 0x53e3f21:R | `0x53e3f21  mov r8,[rax+0x90]` | - |
| rax+0x98 | 8 | 0x53e3f0d:R | `0x53e3f0d  mov rdx,[rax+0x98]` | - |
| rax+0xA0 | 8 | 0x53e3f06:R | `0x53e3f06  mov rcx,[rax+0xA0]` | - |
| rax+0xE0 | 8 | 0x53e4235:R | `0x53e4235  cmp [rax+0xE0],rcx` | - |
| rax+0x218 | 8 | 0x53e3c4e:R | `0x53e3c4e  mov rax,[rax+0x218]` | - |
| rax+0x270 | 8 | 0x53e3bf9:R | `0x53e3bf9  mov rax,[rax+0x270]` | pointer fetched; next instructions: lea rdx,[rbp+0x70], rcx=object, call [I] |
| rax+0x368 | 1 | 0x53e454a:R | `0x53e454a  cmp byte ptr [rax+0x368],0` | - |
| rax+0x370 | 8 | 0x53e4885:R, 0x53e4a40:R | `0x53e4885  mov rax,[rax+0x370]`<br>`0x53e4a40  mov rax,[rax+0x370]` | - |
| rax+0x9F8 | 8 | 0x53e4557:R, 0x53e4584:R | `0x53e4557  mov rbx,[rax+0x9F8]`<br>`0x53e4584  mov rcx,[rax+0x9F8]` | - |
| rax+0xC1C | 1 | 0x53e3e8f:R | `0x53e3e8f  cmp byte ptr [rax+0xC1C],1` | 1-byte value compared to 1 [I] |
| rbp+0x0 | 8 | 0x53e408e:W, 0x53e42fe:R | `0x53e408e  movsd [rbp],xmm0`<br>`0x53e42fe  mulsd xmm2,[rbp]` | - |
| rbp+0x10 | 8 | 0x53e4160:W, 0x53e41c2:R | `0x53e4160  mov [rbp+0x10],rcx`<br>`0x53e41c2  mov rax,[rbp+0x10]` | - |
| rbp+0x18 | 8 | 0x53e3eb2:W, 0x53e4562:R | `0x53e3eb2  mov [rbp+0x18],rsi`<br>`0x53e4562  mov rdx,[rbp+0x18]` | - |
| rbp+0x20 | 16 | 0x53e4c6f:W, 0x53e4cfe:W | `0x53e4c6f  movaps [rbp+0x20],xmm0`<br>`0x53e4cfe  movaps [rbp+0x20],xmm0` | - |
| rbp+0x30 | 8 (also 4) | 0x53e4483:W, 0x53e44b3:R | `0x53e4483  movlps [rbp+0x30],xmm0`<br>`0x53e44b3  mov eax,[rbp+0x30]` | - |
| rbp+0x38 | 4 | 0x53e4012:R, 0x53e4493:W, 0x53e44b6:R | `0x53e4012  movss xmm2,[rbp+0x38]`<br>`0x53e4493  mov [rbp+0x38],eax`<br>`0x53e44b6  mov ecx,[rbp+0x38]` | - |
| rbp+0x3C | 4 | 0x53e4009:R | `0x53e4009  movss xmm1,[rbp+0x3C]` | - |
| rbp+0x48 | 4 | 0x53e4028:R | `0x53e4028  movss xmm4,[rbp+0x48]` | - |
| rbp+0x4C | 4 | 0x53e401b:R | `0x53e401b  movss xmm3,[rbp+0x4C]` | - |
| rbp+0x58 | 4 | 0x53e4035:R | `0x53e4035  movss xmm15,[rbp+0x58]` | - |
| rbp+0x5C | 4 | 0x53e403b:R | `0x53e403b  movss xmm1,[rbp+0x5C]` | - |
| rbp+0x68 | 4 | 0x53e404c:R | `0x53e404c  movss xmm5,[rbp+0x68]` | - |
| rbp+0x6C | 4 | 0x53e4051:R | `0x53e4051  movss xmm6,[rbp+0x6C]` | - |
| rbp+0x70 | 8 | 0x53e3c73:R, 0x53e3e8b:R | `0x53e3c73  mov rcx,[rbp+0x70]`<br>`0x53e3e8b  mov rax,[rbp+0x70]` | - |
| rbp+0x78 | 8 | 0x53e4af2:R | `0x53e4af2  mov rsi,[rbp+0x78]` | - |
| rbp+0x80 | 8 | 0x53e3eab:W, 0x53e3fd6:R, 0x53e4188:R | `0x53e3eab  mov [rbp+0x80],rdi`<br>`0x53e3fd6  mov rdx,[rbp+0x80]`<br>`0x53e4188  mov rdx,[rbp+0x80]` | - |
| rbp+0x88 | 8 | 0x53e3efb:W, 0x53e4613:R, 0x53e4d50:R | `0x53e3efb  mov [rbp+0x88],r13`<br>`0x53e4613  mov r13,[rbp+0x88]`<br>`0x53e4d50  mov r13,[rbp+0x88]` | - |
| rbp+0x90 | 16 (also 4, 8, 2) | 0x53e3c66:R, 0x53e3dd6:R, 0x53e3dee:W, 0x53e3e1b:W, 0x53e3f35:W, 0x53e45b1:R, 0x53e4874:W, 0x53e4921:W | `0x53e3c66  cmp dword ptr [rbp+0x90],1`<br>`0x53e3dd6  mov rax,[rbp+0x90]`<br>`0x53e3dee  movaps [rbp+0x90],xmm0`<br>`0x53e3e1b  mov [rbp+0x90],rbx`<br>`0x53e3f35  movaps [rbp+0x90],xmm0`<br>`0x53e45b1  mov rcx,[rbp+0x90]`<br>`0x53e4874  mov [rbp+0x90],rdi`<br>`0x53e4921  mov [rbp+0x90],ax` | - |
| rbp+0x94 | 8 | 0x53e4932:W | `0x53e4932  movsd [rbp+0x94],xmm0` | - |
| rbp+0x98 | 8 (also 1) | 0x53e3dca:R, 0x53e4314:R, 0x53e476b:R, 0x53e487b:W | `0x53e3dca  mov rcx,[rbp+0x98]`<br>`0x53e4314  movsd xmm2,[rbp+0x98]`<br>`0x53e476b  mov rbx,[rbp+0x98]`<br>`0x53e487b  mov byte ptr [rbp+0x98],0xA` | - |
| rbp+0xA0 | 16 (also 8) | 0x53e3de7:W, 0x53e3e22:W, 0x53e3f40:W, 0x53e4955:W | `0x53e3de7  movaps [rbp+0xA0],xmm0`<br>`0x53e3e22  mov qword ptr [rbp+0xA0],0x16`<br>`0x53e3f40  movaps [rbp+0xA0],xmm0`<br>`0x53e4955  movups [rbp+0xA0],xmm0` | - |
| rbp+0xA8 | 8 | 0x53e3e2d:W, 0x53e431c:R, 0x53e4734:R | `0x53e3e2d  mov qword ptr [rbp+0xA8],0x1F`<br>`0x53e431c  movsd xmm3,[rbp+0xA8]`<br>`0x53e4734  mov rbx,[rbp+0xA8]` | - |
| rbp+0xB0 | 16 | 0x53e3f4b:W, 0x53e4965:W | `0x53e3f4b  movaps [rbp+0xB0],xmm0`<br>`0x53e4965  movups [rbp+0xB0],xmm0` | - |
| rbp+0xB8 | 8 | 0x53e4324:R | `0x53e4324  movsd xmm4,[rbp+0xB8]` | - |
| rbp+0xC0 | 16 (also 4) | 0x53e3f56:W, 0x53e4976:W | `0x53e3f56  movaps [rbp+0xC0],xmm0`<br>`0x53e4976  movss [rbp+0xC0],xmm0` | - |
| rbp+0xC4 | 16 | 0x53e4987:W | `0x53e4987  movups [rbp+0xC4],xmm0` | - |
| rbp+0xC8 | 8 (also 1) | 0x53e432c:R, 0x53e4857:W | `0x53e432c  movsd xmm1,[rbp+0xC8]`<br>`0x53e4857  mov byte ptr [rbp+0xC8],0` | - |
| rbp+0xD4 | 16 | 0x53e4997:W | `0x53e4997  movups [rbp+0xD4],xmm0` | - |
| rbp+0xE4 | 4 | 0x53e49a8:W | `0x53e49a8  movss [rbp+0xE4],xmm0` | - |
| rbp+0xE8 | 1 | 0x53e49b9:W | `0x53e49b9  mov [rbp+0xE8],al` | - |
| rbp+0xF8 | 4 | 0x53e3ec8:W, 0x53e4460:R | `0x53e3ec8  movss [rbp+0xF8],xmm0`<br>`0x53e4460  addss xmm0,[rbp+0xF8]` | - |
| rbp+0xFC | 4 | 0x53e3eda:W, 0x53e4457:R | `0x53e3eda  movss [rbp+0xFC],xmm0`<br>`0x53e4457  addss xmm8,[rbp+0xFC]` | - |
| rbp+0x100 | 4 | 0x53e3ef3:W, 0x53e444f:R | `0x53e3ef3  movss [rbp+0x100],xmm0`<br>`0x53e444f  addss xmm7,[rbp+0x100]` | - |
| rbp+0x104 | 4 | 0x53e40a4:W, 0x53e42b7:R | `0x53e40a4  movss [rbp+0x104],xmm0`<br>`0x53e42b7  divss xmm8,[rbp+0x104]` | - |
| rbp+0x108 | 4 | 0x53e4180:R, 0x53e41a5:W | `0x53e4180  mov eax,[rbp+0x108]`<br>`0x53e41a5  mov [rbp+0x108],eax` | - |
| rbp+0x10C | 4 | 0x53e4167:W, 0x53e41d8:R | `0x53e4167  mov [rbp+0x10C],eax`<br>`0x53e41d8  add r12d,[rbp+0x10C]` | - |
| rbp+0x110 | 4 | 0x53e40b6:W, 0x53e419c:R | `0x53e40b6  movss [rbp+0x110],xmm0`<br>`0x53e419c  divss xmm13,[rbp+0x110]` | - |
| rbp+0x114 | 4 | 0x53e40cf:W, 0x53e4146:R | `0x53e40cf  movss [rbp+0x114],xmm0`<br>`0x53e4146  divss xmm0,[rbp+0x114]` | - |
| rbp+0x118 | 2 (also 8) | 0x53e44ac:R, 0x53e4c56:W, 0x53e4ce5:W | `0x53e44ac  movzx ebx,word ptr [rbp+0x118]`<br>`0x53e4c56  mov [rbp+0x118],rax`<br>`0x53e4ce5  mov [rbp+0x118],rax` | - |
| rbp+0x120 | 8 | 0x53e4c5d:W, 0x53e4cec:W | `0x53e4c5d  mov qword ptr [rbp+0x120],0x15`<br>`0x53e4cec  mov qword ptr [rbp+0x120],0x15` | - |
| rbp+0x128 | 8 | 0x53e3b6d:W, 0x53e3bb3:W, 0x53e4bb2:R | `0x53e3b6d  mov qword ptr [rbp+0x128],0`<br>`0x53e3bb3  mov [rbp+0x128],rsi`<br>`0x53e4bb2  mov rcx,[rbp+0x128]` | local record field: zero-initialized, filled, re-read at epilogue [I] |
| rbp+0x130 | 1 | 0x53e3b78:W, 0x53e3bba:W, 0x53e4ba9:R | `0x53e3b78  mov byte ptr [rbp+0x130],0`<br>`0x53e3bba  mov byte ptr [rbp+0x130],1`<br>`0x53e4ba9  cmp byte ptr [rbp+0x130],1` | local record byte: set 0/1, re-tested at epilogue [I] |
| rbp+0x138 | 16 (also 8) | 0x53e3b82:W, 0x53e3bc1:W, 0x53e47a2:R, 0x53e48f8:R, 0x53e4b30:W | `0x53e3b82  movups [rbp+0x138],xmm0`<br>`0x53e3bc1  mov [rbp+0x138],r14`<br>`0x53e47a2  mov rax,[rbp+0x138]`<br>`0x53e48f8  mov r14,[rbp+0x138]`<br>`0x53e4b30  movups [rbp+0x138],xmm0` | local record field: filled twice, re-read twice [I] |
| rbp+0x140 | 8 | 0x53e3bc8:W, 0x53e4b29:R, 0x53e4b67:R | `0x53e3bc8  mov [rbp+0x140],rax`<br>`0x53e4b29  mov rsi,[rbp+0x140]`<br>`0x53e4b67  mov rsi,[rbp+0x140]` | local record field: filled, re-read at epilogue [I] |
| rbp+0x148 | 8 | 0x53e3b89:W, 0x53e3bcf:W, 0x53e47be:R, 0x53e4915:R, 0x53e4b6e:W | `0x53e3b89  mov qword ptr [rbp+0x148],0`<br>`0x53e3bcf  mov [rbp+0x148],rdi`<br>`0x53e47be  mov rbx,[rbp+0x148]`<br>`0x53e4915  mov rdi,[rbp+0x148]`<br>`0x53e4b6e  mov qword ptr [rbp+0x148],0` | local record field: zero-initialized, filled, re-read at epilogue [I] |
| rbp+0x150 | 16 (also 8) | 0x53e3e84:W, 0x53e4681:W, 0x53e47f6:R | `0x53e3e84  movaps [rbp+0x150],xmm0`<br>`0x53e4681  mov [rbp+0x150],rcx`<br>`0x53e47f6  mov rcx,[rbp+0x150]` | - |
| rbp+0x158 | 8 | 0x53e4688:R, 0x53e468f:W, 0x53e47db:R, 0x53e47eb:R, 0x53e4a7c:R | `0x53e4688  mov rbx,[rbp+0x158]`<br>`0x53e468f  mov [rbp+0x158],rax`<br>`0x53e47db  mov rax,[rbp+0x158]`<br>`0x53e47eb  mov rax,[rbp+0x158]`<br>`0x53e4a7c  mov rsi,[rbp+0x158]` | - |
| rbp+0x168 | 8 (also 4) | 0x53e40f6:W, 0x53e4110:R, 0x53e4119:W, 0x53e4135:R, 0x53e44fd:R | `0x53e40f6  mov qword ptr [rbp+0x168],0`<br>`0x53e4110  mov rax,[rbp+0x168]`<br>`0x53e4119  mov [rbp+0x168],rax`<br>`0x53e4135  mov rax,[rbp+0x168]`<br>`0x53e44fd  cmp dword ptr [rbp+0x168],2` | counter: zeroed, loaded/stored, compared to 2 [I] |
| rbp+0x170 | 4 (also 8) | 0x53e3cf0:W, 0x53e4364:R, 0x53e467a:R, 0x53e4837:W, 0x53e48a6:R, 0x53e4a2f:W | `0x53e3cf0  mov [rbp+0x170],eax`<br>`0x53e4364  movss xmm2,[rbp+0x170]`<br>`0x53e467a  mov rcx,[rbp+0x170]`<br>`0x53e4837  mov [rbp+0x170],rcx`<br>`0x53e48a6  mov r8,[rbp+0x170]`<br>`0x53e4a2f  mov [rbp+0x170],rax` | - |
| rbp+0x174 | 16 (also 4) | 0x53e3cf6:W, 0x53e43bf:R | `0x53e3cf6  mov [rbp+0x174],edi`<br>`0x53e43bf  movups xmm2,[rbp+0x174]` | - |
| rbp+0x178 | 4 (also 8, 1) | 0x53e3cfc:W, 0x53e4357:R, 0x53e465f:R, 0x53e466f:R, 0x53e46c6:R, 0x53e483e:W, 0x53e486e:W, 0x53e489d:R, 0x53e4a36:W | `0x53e3cfc  mov dword ptr [rbp+0x178],0x1C`<br>`0x53e4357  movss xmm0,[rbp+0x178]`<br>`0x53e465f  mov rax,[rbp+0x178]`<br>`0x53e466f  mov rax,[rbp+0x178]`<br>`0x53e46c6  mov rbx,[rbp+0x178]`<br>`0x53e483e  mov byte ptr [rbp+0x178],0`<br>`0x53e486e  mov [rbp+0x178],al`<br>`0x53e489d  cmp byte ptr [rbp+0x178],1`<br>`0x53e4a36  mov byte ptr [rbp+0x178],8` | - |
| rbp+0x17C | 4 (also 2) | 0x53e3d06:W, 0x53e43ca:R | `0x53e3d06  mov word ptr [rbp+0x17C],0x202`<br>`0x53e43ca  movss xmm3,[rbp+0x17C]` | - |
| rbp+0x17E | 1 | 0x53e3d0f:W | `0x53e3d0f  mov byte ptr [rbp+0x17E],0` | - |
| rbp+0x180 | 4 | 0x53e3d1d:W, 0x53e4382:R | `0x53e3d1d  mov [rbp+0x180],eax`<br>`0x53e4382  movss xmm4,[rbp+0x180]` | - |
| rbp+0x184 | 16 | 0x53e43d9:R | `0x53e43d9  movups xmm2,[rbp+0x184]` | - |
| rbp+0x188 | 4 (also 8) | 0x53e4371:R, 0x53e484c:W | `0x53e4371  movss xmm3,[rbp+0x188]`<br>`0x53e484c  mov qword ptr [rbp+0x188],0` | - |
| rbp+0x18C | 4 | 0x53e43e9:R | `0x53e43e9  movss xmm4,[rbp+0x18C]` | - |
| rbp+0x190 | 4 | 0x53e439f:R | `0x53e439f  movss xmm0,[rbp+0x190]` | - |
| rbp+0x194 | 16 | 0x53e43f8:R | `0x53e43f8  movups xmm2,[rbp+0x194]` | - |
| rbp+0x198 | 4 | 0x53e4393:R | `0x53e4393  movss xmm7,[rbp+0x198]` | - |
| rbp+0x19C | 4 | 0x53e4406:R | `0x53e4406  movss xmm3,[rbp+0x19C]` | - |
| rbp+0x1A0 | 4 | 0x53e43b7:R | `0x53e43b7  addss xmm0,[rbp+0x1A0]` | - |
| rbp+0x1A4 | 4 | 0x53e4424:R | `0x53e4424  movss xmm8,[rbp+0x1A4]` | - |
| rbp+0x1A8 | 4 (also 1) | 0x53e43a7:R, 0x53e4a0b:W | `0x53e43a7  addss xmm7,[rbp+0x1A8]`<br>`0x53e4a0b  mov byte ptr [rbp+0x1A8],0` | - |
| rbp+0x1AC | 4 | 0x53e441c:R | `0x53e441c  movss xmm2,[rbp+0x1AC]` | - |
| rbp+0x1B0 | 8 (also 4) | 0x53e3c90:W, 0x53e3cb9:R, 0x53e3d16:R, 0x53e3fe9:R, 0x53e40be:R, 0x53e4120:R | `0x53e3c90  mov [rbp+0x1B0],rax`<br>`0x53e3cb9  mov rax,[rbp+0x1B0]`<br>`0x53e3d16  mov rax,[rbp+0x1B0]`<br>`0x53e3fe9  cmp dword ptr [rbp+0x1B0],0`<br>`0x53e40be  mov rax,[rbp+0x1B0]`<br>`0x53e4120  cmp eax,[rbp+0x1B0]` | - |
| rbp+0x1B8 | 8 | 0x53e3ee2:W, 0x53e3fa9:R, 0x53e4543:R, 0x53e457d:R, 0x53e460c:R, 0x53e4d49:R | `0x53e3ee2  mov [rbp+0x1B8],r12`<br>`0x53e3fa9  mov rcx,[rbp+0x1B8]`<br>`0x53e4543  mov rax,[rbp+0x1B8]`<br>`0x53e457d  mov rax,[rbp+0x1B8]`<br>`0x53e460c  mov r12,[rbp+0x1B8]`<br>`0x53e4d49  mov r12,[rbp+0x1B8]` | - |
| rbp+0x1C0 | 16 (also 4, 8, 2) | 0x53e44bf:W, 0x53e45c9:W, 0x53e45f4:W, 0x53e47ca:W, 0x53e49eb:W, 0x53e4a61:R | `0x53e44bf  mov [rbp+0x1C0],eax`<br>`0x53e45c9  movaps [rbp+0x1C0],xmm0`<br>`0x53e45f4  mov [rbp+0x1C0],rax`<br>`0x53e47ca  mov [rbp+0x1C0],ax`<br>`0x53e49eb  mov [rbp+0x1C0],rcx`<br>`0x53e4a61  mov r8,[rbp+0x1C0]` | - |
| rbp+0x1C4 | 4 | 0x53e44c5:W | `0x53e44c5  mov [rbp+0x1C4],ecx` | - |
| rbp+0x1C8 | 16 (also 8, 1) | 0x53e45fb:R, 0x53e4602:W, 0x53e46fd:R, 0x53e47d4:W, 0x53e47fd:W, 0x53e49f2:W, 0x53e4a22:W, 0x53e4a58:R | `0x53e45fb  mov rdi,[rbp+0x1C8]`<br>`0x53e4602  mov [rbp+0x1C8],rcx`<br>`0x53e46fd  mov rbx,[rbp+0x1C8]`<br>`0x53e47d4  movups [rbp+0x1C8],xmm0`<br>`0x53e47fd  mov [rbp+0x1C8],rcx`<br>`0x53e49f2  mov byte ptr [rbp+0x1C8],0`<br>`0x53e4a22  mov [rbp+0x1C8],al`<br>`0x53e4a58  cmp byte ptr [rbp+0x1C8],1` | - |
| rbp+0x1D0 | 8 | 0x53e4804:W, 0x53e48c1:R | `0x53e4804  mov [rbp+0x1D0],rax`<br>`0x53e48c1  mov rdi,[rbp+0x1D0]` | - |
| rbp+0x1D8 | 8 | 0x53e4a00:W | `0x53e4a00  mov qword ptr [rbp+0x1D8],0` | - |
| rbp+0x1E0 | 8 (also 4) | 0x53e3c7d:W, 0x53e3cca:R, 0x53e3ce9:R, 0x53e4093:R, 0x53e412c:R, 0x53e41ca:R, 0x53e429e:R | `0x53e3c7d  mov [rbp+0x1E0],rax`<br>`0x53e3cca  mov rax,[rbp+0x1E0]`<br>`0x53e3ce9  mov rax,[rbp+0x1E0]`<br>`0x53e4093  mov rax,[rbp+0x1E0]`<br>`0x53e412c  cmp dword ptr [rbp+0x1E0],0`<br>`0x53e41ca  mov rax,[rbp+0x1E0]`<br>`0x53e429e  cmp edi,[rbp+0x1E0]` | - |
| rbp+0x1E8 | 8 | 0x53e3b09:W | `0x53e3b09  mov qword ptr [rbp+0x1E8],0xFFFFFFFFFFFFFFFE` | slot initialized to -2 (0xFFFFFFFFFFFFFFFE) [I] |
| rbp+0x1F0 | 16 | 0x53e3b02:W, 0x53e4bbe:R | `0x53e3b02  movaps [rbp+0x1F0],xmm6`<br>`0x53e4bbe  movaps xmm6,[rbp+0x1F0]` | callee-saved xmm6 spill/restore [V] |
| rbp+0x200 | 16 | 0x53e3afb:W, 0x53e4bc5:R | `0x53e3afb  movaps [rbp+0x200],xmm7`<br>`0x53e4bc5  movaps xmm7,[rbp+0x200]` | callee-saved xmm7 spill/restore [V] |
| rbp+0x210 | 16 | 0x53e3af3:W, 0x53e4bcc:R | `0x53e3af3  movaps [rbp+0x210],xmm8`<br>`0x53e4bcc  movaps xmm8,[rbp+0x210]` | callee-saved xmm8 spill/restore [V] |
| rbp+0x220 | 16 | 0x53e3aeb:W, 0x53e4bd4:R | `0x53e3aeb  movaps [rbp+0x220],xmm9`<br>`0x53e4bd4  movaps xmm9,[rbp+0x220]` | callee-saved xmm9 spill/restore [V] |
| rbp+0x230 | 16 | 0x53e3ae3:W, 0x53e4bdc:R | `0x53e3ae3  movaps [rbp+0x230],xmm10`<br>`0x53e4bdc  movaps xmm10,[rbp+0x230]` | callee-saved xmm10 spill/restore [V] |
| rbp+0x240 | 16 | 0x53e3adb:W, 0x53e4be4:R | `0x53e3adb  movaps [rbp+0x240],xmm11`<br>`0x53e4be4  movaps xmm11,[rbp+0x240]` | callee-saved xmm11 spill/restore [V] |
| rbp+0x250 | 16 | 0x53e3ad3:W, 0x53e4bec:R | `0x53e3ad3  movaps [rbp+0x250],xmm12`<br>`0x53e4bec  movaps xmm12,[rbp+0x250]` | callee-saved xmm12 spill/restore [V] |
| rbp+0x260 | 16 | 0x53e3acb:W, 0x53e4bf4:R | `0x53e3acb  movaps [rbp+0x260],xmm13`<br>`0x53e4bf4  movaps xmm13,[rbp+0x260]` | callee-saved xmm13 spill/restore [V] |
| rbp+0x270 | 16 | 0x53e3ac3:W, 0x53e4bfc:R | `0x53e3ac3  movaps [rbp+0x270],xmm14`<br>`0x53e4bfc  movaps xmm14,[rbp+0x270]` | callee-saved xmm14 spill/restore [V] |
| rbp+0x280 | 16 | 0x53e3abb:W, 0x53e4c04:R | `0x53e3abb  movaps [rbp+0x280],xmm15`<br>`0x53e4c04  movaps xmm15,[rbp+0x280]` | callee-saved xmm15 spill/restore [V] |
| rbx+0x0 | 16 (also 8) | 0x53e3e3f:W, 0x53e46a1:R, 0x53e46b6:R, 0x53e46d8:R, 0x53e46ed:R, 0x53e470f:R, 0x53e4724:R, 0x53e4746:R, 0x53e475b:R, 0x53e477d:R, 0x53e4792:R, 0x53e4882:R | `0x53e3e3f  movups [rbx],xmm0`<br>`0x53e46a1  mov rax,[rbx]`<br>`0x53e46b6  mov rax,[rbx]`<br>`0x53e46d8  mov rax,[rbx]`<br>`0x53e46ed  mov rax,[rbx]`<br>`0x53e470f  mov rax,[rbx]`<br>`0x53e4724  mov rax,[rbx]`<br>`0x53e4746  mov rax,[rbx]`<br>`0x53e475b  mov rax,[rbx]`<br>`0x53e477d  mov rax,[rbx]`<br>`0x53e4792  mov rax,[rbx]`<br>`0x53e4882  mov rax,[rbx]` | - |
| rbx+0xC | 4 | 0x53e46b0:RMW, 0x53e46e7:RMW, 0x53e471e:RMW, 0x53e4755:RMW, 0x53e478c:RMW | `0x53e46b0  lock dec dword ptr [rbx+0xC]`<br>`0x53e46e7  lock dec dword ptr [rbx+0xC]`<br>`0x53e471e  lock dec dword ptr [rbx+0xC]`<br>`0x53e4755  lock dec dword ptr [rbx+0xC]`<br>`0x53e478c  lock dec dword ptr [rbx+0xC]` | dword atomically decremented (lock dec) [I] |
| rbx+0xE | 8 | 0x53e3e4c:W | `0x53e3e4c  mov [rbx+0xE],rax` | - |
| rbx+0x16 | 1 | 0x53e3e50:W | `0x53e3e50  mov byte ptr [rbx+0x16],0` | - |
| rcx+0x0 | 8 | 0x53e3dfc:R | `0x53e3dfc  mov rax,[rcx]` | - |
| rcx+0x10 | 8 (also 2) | 0x53e3b18:R, 0x53e45d8:R | `0x53e3b18  mov r13,[rcx+0x10]`<br>`0x53e45d8  movzx ecx,word ptr [rcx+0x10]` | - |
| rcx+0x340 | 8 | 0x53e3fc1:R | `0x53e3fc1  mov rsi,[rcx+0x340]` | - |
| rcx+0x348 | 8 | 0x53e3fb0:R | `0x53e3fb0  mov rax,[rcx+0x348]` | - |
| rcx+0xC1C | 1 | 0x53e3ca8:R | `0x53e3ca8  cmp byte ptr [rcx+0xC1C],1` | 1-byte value compared to 1 [I] |
| rcx+0xC28 | 4 | 0x53e3c77:R | `0x53e3c77  mov eax,[rcx+0xC28]` | - |
| rcx+0xC2C | 4 | 0x53e3c84:R | `0x53e3c84  mov edi,[rcx+0xC2C]` | - |
| rcx+0xC30 | 4 | 0x53e3c8a:R | `0x53e3c8a  mov eax,[rcx+0xC30]` | - |
| rdi+0x0 | 8 | 0x53e3bf6:R, 0x53e3c21:R, 0x53e3c4b:R, 0x53e4622:R, 0x53e4637:R, 0x53e48d3:R, 0x53e48e8:R, 0x53e4a3d:R | `0x53e3bf6  mov rax,[rdi]`<br>`0x53e3c21  mov rax,[rdi]`<br>`0x53e3c4b  mov rax,[rdi]`<br>`0x53e4622  mov rax,[rdi]`<br>`0x53e4637  mov rax,[rdi]`<br>`0x53e48d3  mov rax,[rdi]`<br>`0x53e48e8  mov rax,[rdi]`<br>`0x53e4a3d  mov rax,[rdi]` | - |
| rdi+0xC | 4 | 0x53e4631:RMW, 0x53e48e2:RMW | `0x53e4631  lock dec dword ptr [rdi+0xC]`<br>`0x53e48e2  lock dec dword ptr [rdi+0xC]` | dword atomically decremented (lock dec) [I] |
| rdx+0x0 | 16 | 0x53e3f32:R | `0x53e3f32  movups xmm0,[rdx]` | - |
| rdx+0x10 | 16 | 0x53e3f3c:R | `0x53e3f3c  movups xmm0,[rdx+0x10]` | - |
| rdx+0x20 | 16 | 0x53e3f47:R | `0x53e3f47  movups xmm0,[rdx+0x20]` | - |
| rdx+0x30 | 16 | 0x53e3f52:R | `0x53e3f52  movups xmm0,[rdx+0x30]` | - |
| rsi+0x0 | 8 | 0x53e3d9d:R, 0x53e4a8e:R, 0x53e4aa3:R, 0x53e4b01:R, 0x53e4b16:R, 0x53e4b42:R, 0x53e4b57:R, 0x53e4b84:R, 0x53e4b99:R | `0x53e3d9d  mov rax,[rsi]`<br>`0x53e4a8e  mov rax,[rsi]`<br>`0x53e4aa3  mov rax,[rsi]`<br>`0x53e4b01  mov rax,[rsi]`<br>`0x53e4b16  mov rax,[rsi]`<br>`0x53e4b42  mov rax,[rsi]`<br>`0x53e4b57  mov rax,[rsi]`<br>`0x53e4b84  mov rax,[rsi]`<br>`0x53e4b99  mov rax,[rsi]` | - |
| rsi+0xC | 4 | 0x53e4a9d:RMW, 0x53e4b10:RMW, 0x53e4b51:RMW, 0x53e4b93:RMW | `0x53e4a9d  lock dec dword ptr [rsi+0xC]`<br>`0x53e4b10  lock dec dword ptr [rsi+0xC]`<br>`0x53e4b51  lock dec dword ptr [rsi+0xC]`<br>`0x53e4b93  lock dec dword ptr [rsi+0xC]` | dword atomically decremented (lock dec) [I] |
| rsp+0x20 | 8 (also 4) | 0x53e4594:W, 0x53e4c7f:W, 0x53e4d0e:W, 0x53e4d5c:W | `0x53e4594  mov qword ptr [rsp+0x20],0`<br>`0x53e4c7f  mov dword ptr [rsp+0x20],0`<br>`0x53e4d0e  mov dword ptr [rsp+0x20],0`<br>`0x53e4d5c  mov qword ptr [rsp+0x20],0` | outgoing argument slots [I] |
| rsp+0x28 | 1 (also 8) | 0x53e458f:W, 0x53e4c7a:W, 0x53e4d09:W | `0x53e458f  mov byte ptr [rsp+0x28],0`<br>`0x53e4c7a  mov [rsp+0x28],rax`<br>`0x53e4d09  mov [rsp+0x28],rax` | outgoing argument slots [I] |

### Non-fixed accesses (footnote)

Dynamic-index (no fixed offset; element selected by another register):

- `0x53e3f2e  mov rdx,[rdx+r8*8]`
- `0x53e3f79  mov r8,[r8+rax*8]`
- `0x53e4103  nop [rax+rax]`
- `0x53e4171  nop [rax+rax]`
- `0x53e41c6  lea ecx,[r12+rax]`
- `0x53e41f3  nop [rax+rax]`
- `0x53e4209  mov ecx,[rsi+rcx*4]`
- `0x53e4240  lea r13d,[rdi+r12]`
- `0x53e4299  mov [rsi+rcx*4],eax`
- `0x53e4820  mov rcx,[rdx+rcx*8]`
- `0x53e49d4  mov rcx,[rdx+rcx*8]`
- `0x53e4d76  nop [rax+rax]`

Absolute/global (no register base): `lea rsi,[0x128C4FD0]` / `lea rcx,[0x128C4FD0]` (service object), `lock inc qword ptr [0x128C5030]` (global counter), `mov r14,[0x128C5038]`, `mov rax,[0x128C5040]`, `mov rdi,[0x128C5048]`, `mov dword ptr [0],0xDEADC0DE` (4x debug fill), `call qword ptr [0xF99FFA0]` (import thunk, many sites), `mov rdx,gs:[0x58]` (TLS), `mov rcx,[0x1233E1A8]`, `mov rcx,[0x12968190]`, `mov eax,[0x129C60D8]` / `mov eax,[0x129C6218]` and matching `cmp dword ptr ...,0xFFFFFFFF` + `lea rcx,[...]` on the same addresses, plus float constant loads `[0xF55882A]`, `[0xEF3F050]`, `[0xEEC8060]`, `[0xEF40D58]`, `[0xEF6D158]`, `[0xEF1D470]`, `[0xF247120]`, `[0xEF04EF0]`, `[0xF247110]`, `[0xEEC8068]`, `[0xF0A3FE0]`, `[0xF0BCBF8]`, string/lea data `[0xF52E07A]`, `[0xF248EB0]`, `[0xF248E90]`, `[0x129C5FA0]`, `[0x129C1210]`, `[0x1244FD00]`, `[0x53DECC0]`, `[0x53DECB0]`, `[0xF9A8C78]`. [V] quoted verbatim from the listing.

## ADDENDUM (orchestrator): 2 instructions missing from the phases above, verbatim from effect_volfog_clone_53e3aa0_53e4d77.txt
```
0x53e3c28  mov rcx,rdi
0x53e3f7d  lea rcx,[rbp+0x30]
```
