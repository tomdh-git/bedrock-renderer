## NEXT
DONE

# UNIT U-Full — FullscreenEffect clone / ctor / emplace (instruction-complete dossiers)

Input data (read fully, verbatim source of every quoted line):
- docs/data/listings/effect_fullscreen_clone_530a1b0_530a81c.txt (371 instrs, 0x530A1B0..0x530A81B)
- docs/data/listings/effect_fullscreen_ctor_668bf20_668c1cd.txt (161 instrs, 0x668BF20..0x668C1CC)
- docs/data/listings/effect_fullscreen_emplace_66b2b30_66b2dd9.txt (176 instrs, 0x66B2B30..0x66B2DD8)

Tags: [V] seen in the listing; [I] inferred from instruction patterns only. Every instruction of every listing is inside a phase below (linear chunks of <=40, no skips). Index-form operands ([base+idx*scale]), absolute [0xADDR] operands, and `lea` (address formation only) are not [reg+off] fields; they stay visible in the phase listings. `call/jmp` targets kept as printed.

## Function 1 — clone, 0x530A1B0..0x530A81B

Arg map at entry [V]: rcx -> rdi (dest effect), rdx -> rsi (src), r8 -> [rbp+0x1D8] (shared handle, rcx-target of 0x4DEF080), r9 -> r14; 5th arg [rbp+0x250] -> rbx (owner/description holder).

### 0x530A1B0..0x530A24D: Prologue; saves the four register args; calls 0x4DEF080 (rcx=rdx) and bails to the epilogue path 0x530A743 if it returns false, if the handle is null, or if [[handle]+0x40]==0; then loads rbx=[rbp+0x250] and starts the description checks.
```
0x530a1b0  push rbp
0x530a1b1  push r15
0x530a1b3  push r14
0x530a1b5  push r13
0x530a1b7  push r12
0x530a1b9  push rsi
0x530a1ba  push rdi
0x530a1bb  push rbx
0x530a1bc  sub rsp,0x268
0x530a1c3  lea rbp,[rsp+0x80]
0x530a1cb  mov qword ptr [rbp+0x1E0],0xFFFFFFFFFFFFFFFE
0x530a1d6  mov r14,r9
0x530a1d9  mov [rbp+0x1D8],r8
0x530a1e0  mov rsi,rdx
0x530a1e3  mov rdi,rcx
0x530a1e6  mov rcx,rdx
0x530a1e9  call 0x4DEF080
0x530a1ee  nop
0x530a1ef  test al,al
0x530a1f1  mov r8,[rbp+0x1D8]
0x530a1f8  je 0x530A743
0x530a1fe  mov rax,[r8]
0x530a201  test rax,rax
0x530a204  je 0x530A743
0x530a20a  cmp qword ptr [rax+0x40],0
0x530a20f  je 0x530A743
0x530a215  mov rbx,[rbp+0x250]
0x530a21c  mov rax,[rbx+0x10]
0x530a220  test rax,rax
0x530a223  je 0x530A2D3
0x530a229  cmp byte ptr [rax],1
0x530a22c  jne 0x530A2D3
0x530a232  mov rcx,[rbx+0x20]
0x530a236  mov rax,[rcx]
0x530a239  mov rax,[rax+8]
0x530a23d  call qword ptr [0xF99FFA0]
0x530a243  nop
0x530a244  test al,al
0x530a246  mov r8,[rbp+0x1D8]
0x530a24d  je 0x530A2D3
```

### 0x530A253..0x530A2CE: Fast path: sets byte [rdi->+8 ->+0x78]=1 and, using the ring-buffer head math over [rax+0x48..0x68], copies 64 bytes of the last entry into frame copies [rbp+0xB0..0xE0]; if byte [rax+0x70]==1 it then loads a second entry pointer into r15 (the [rax+0x48..0x68] buffer), else jumps to 0x530A49F where r15=&[rbp+0xB0].
```
0x530a253  mov rax,[rdi+8]
0x530a257  mov byte ptr [rax+0x78],1
0x530a25b  mov rcx,[rax+0x60]
0x530a25f  mov rdx,[rax+0x58]
0x530a263  add rcx,rdx
0x530a266  dec rcx
0x530a269  mov rdx,[rax+0x48]
0x530a26d  mov rax,[rax+0x50]
0x530a271  dec rax
0x530a274  and rax,rcx
0x530a277  mov rax,[rdx+rax*8]
0x530a27b  movups xmm0,[rax]
0x530a27e  movaps [rbp+0xB0],xmm0
0x530a285  movups xmm0,[rax+0x10]
0x530a289  movaps [rbp+0xC0],xmm0
0x530a290  movups xmm0,[rax+0x20]
0x530a294  movaps [rbp+0xD0],xmm0
0x530a29b  movups xmm0,[rax+0x30]
0x530a29f  movaps [rbp+0xE0],xmm0
0x530a2a6  mov rax,[rdi+8]
0x530a2aa  cmp byte ptr [rax+0x70],1
0x530a2ae  jne 0x530A49F
0x530a2b4  mov rcx,[rax+0x58]
0x530a2b8  add rcx,[rax+0x68]
0x530a2bc  mov rdx,[rax+0x48]
0x530a2c0  mov rax,[rax+0x50]
0x530a2c4  dec rax
0x530a2c7  and rax,rcx
0x530a2ca  mov r15,[rdx+rax*8]
0x530a2ce  jmp 0x530A4A6
```

### 0x530A2D3..0x530A379: Slow path: stores 0 to byte [rbp+0x158], zeroes [rbp-0x20], builds two 16-byte ref-counted handles on the frame from r14 (+0x0 object ptr, +0x8/+0x18 ref-count object, `lock inc [ref+8]`, flag byte 1 at [rbp]), spills &[rbp+0x140] plus three dwords as stack args and calls 0x4DEFED0 (rcx=rsi, rdx=rdi, r9=&[rbp-0x20]); then dispatches byte [rbp] (0..3) via jump table 0xF249988; the first case target 0x530A379 loads [rbp-0x18] (its release body starts the next phase).
```
0x530a2d3  mov byte ptr [rbp+0x158],0
0x530a2da  xorps xmm0,xmm0
0x530a2dd  movaps [rbp-0x20],xmm0
0x530a2e1  mov rax,[r14+8]
0x530a2e5  test rax,rax
0x530a2e8  je short 0x530A2F4
0x530a2ea  lock inc dword ptr [rax+8]
0x530a2ee  mov rax,[r14+8]
0x530a2f2  jmp short 0x530A2F6
0x530a2f4  xor eax,eax
0x530a2f6  mov rcx,[r14]
0x530a2f9  mov [rbp-0x20],rcx
0x530a2fd  mov [rbp-0x18],rax
0x530a301  movaps [rbp-0x10],xmm0
0x530a305  mov rax,[r14+0x18]
0x530a309  test rax,rax
0x530a30c  je short 0x530A318
0x530a30e  lock inc dword ptr [rax+8]
0x530a312  mov rax,[r14+0x18]
0x530a316  jmp short 0x530A31A
0x530a318  xor eax,eax
0x530a31a  mov rcx,[r14+0x10]
0x530a31e  mov [rbp-0x10],rcx
0x530a322  mov [rbp-8],rax
0x530a326  mov byte ptr [rbp],1
0x530a32a  lea rax,[rbp+0x140]
0x530a331  mov [rsp+0x30],rax
0x530a336  mov qword ptr [rsp+0x38],0
0x530a33f  mov dword ptr [rsp+0x28],0
0x530a347  mov dword ptr [rsp+0x20],0
0x530a34f  lea r9,[rbp-0x20]
0x530a353  mov rcx,rsi
0x530a356  mov rdx,rdi
0x530a359  call 0x4DEFED0
0x530a35e  nop
0x530a35f  movzx eax,byte ptr [rbp]
0x530a363  cmp rax,3
0x530a367  ja short 0x530A3AD
0x530a369  lea rcx,[0xF249988]
0x530a370  movsxd rax,[rcx+rax*4]
0x530a374  add rax,rcx
0x530a377  jmp rax
0x530a377  jmp rax
0x530a379  mov rsi,[rbp-0x18]
```

### 0x530A37D..0x530A41D: Release cases: inline shared-ptr release of the [rbp-0x18] ref-count object (`lock dec` +8 then +0xC, two virtual deletes via 0xF99FFA0 slots), then dispatch of byte [rbp+0x158] via jump table 0xF249998 whose first case (0x530A3CE) releases the [rbp+0x150] object the same way and jumps to the common tail; next case (0x530A416) starts releasing the [rbp-8] ref-count object.
```
0x530a37d  test rsi,rsi
0x530a380  je short 0x530A3AD
0x530a382  lock dec dword ptr [rsi+8]
0x530a386  jne short 0x530A3AD
0x530a388  mov rax,[rsi]
0x530a38b  mov rax,[rax]
0x530a38e  mov rcx,rsi
0x530a391  call qword ptr [0xF99FFA0]
0x530a397  lock dec dword ptr [rsi+0xC]
0x530a39b  jne short 0x530A3AD
0x530a39d  mov rax,[rsi]
0x530a3a0  mov rax,[rax+8]
0x530a3a4  mov rcx,rsi
0x530a3a7  call qword ptr [0xF99FFA0]
0x530a3ad  movzx eax,byte ptr [rbp+0x158]
0x530a3b4  cmp rax,3
0x530a3b8  ja 0x530A73C
0x530a3be  lea rcx,[0xF249998]
0x530a3c5  movsxd rax,[rcx+rax*4]
0x530a3c9  add rax,rcx
0x530a3cc  jmp rax
0x530a3ce  mov rsi,[rbp+0x150]
0x530a3d5  test rsi,rsi
0x530a3d8  je 0x530A73C
0x530a3de  lock dec dword ptr [rsi+8]
0x530a3e2  jne 0x530A73C
0x530a3e8  mov rax,[rsi]
0x530a3eb  mov rax,[rax]
0x530a3ee  mov rcx,rsi
0x530a3f1  call qword ptr [0xF99FFA0]
0x530a3f7  lock dec dword ptr [rsi+0xC]
0x530a3fb  jne 0x530A73C
0x530a401  mov rax,[rsi]
0x530a404  mov rax,[rax+8]
0x530a408  mov rcx,rsi
0x530a40b  call qword ptr [0xF99FFA0]
0x530a411  jmp 0x530A73C
0x530a416  mov rsi,[rbp-8]
0x530a41a  test rsi,rsi
0x530a41d  je 0x530A379
```

### 0x530A423..0x530A4F8: Finishes the [rbp-8] release (same lock dec / virtual delete pattern), then the third case (0x530A45B) releases the [rbp+0x140] object (two-level release, then `operator delete(0xE935700, size 0x20)`) and jumps to the common tail; rejoin at 0x530A49F/0x530A4A6: r15=&[rbp+0xB0] fallback, frame range struct [rbp+0x108..0x138] zeroed, rbx=[rbx+0x20], rax=[r14] or fallback 0x129C1210, and [rbp+0x1C0] zeroed (movaps).
```
0x530a423  lock dec dword ptr [rsi+8]
0x530a427  jne 0x530A379
0x530a42d  mov rax,[rsi]
0x530a430  mov rax,[rax]
0x530a433  mov rcx,rsi
0x530a436  call qword ptr [0xF99FFA0]
0x530a43c  lock dec dword ptr [rsi+0xC]
0x530a440  jne 0x530A379
0x530a446  mov rax,[rsi]
0x530a449  mov rax,[rax+8]
0x530a44d  mov rcx,rsi
0x530a450  call qword ptr [0xF99FFA0]
0x530a456  jmp 0x530A379
0x530a45b  mov rcx,[rbp+0x140]
0x530a462  test rcx,rcx
0x530a465  je 0x530A73C
0x530a46b  mov rdx,[rcx+8]
0x530a46f  test rdx,rdx
0x530a472  je short 0x530A490
0x530a474  lock dec dword ptr [rdx+0xC]
0x530a478  jne short 0x530A490
0x530a47a  mov rax,[rdx]
0x530a47d  mov rax,[rax+8]
0x530a481  mov rsi,rcx
0x530a484  mov rcx,rdx
0x530a487  call qword ptr [0xF99FFA0]
0x530a48d  mov rcx,rsi
0x530a490  mov edx,0x20
0x530a495  call 0xE935700
0x530a49a  jmp 0x530A73C
0x530a49f  lea r15,[rbp+0xB0]
0x530a4a6  mov qword ptr [rbp+0x108],0xFFFFFFFFFFFFFFFF
0x530a4b1  mov qword ptr [rbp+0x110],0
0x530a4bc  mov byte ptr [rbp+0x118],0
0x530a4c3  mov byte ptr [rbp+0x138],0
0x530a4ca  mov rax,[rbx+0x10]
0x530a4ce  test rax,rax
0x530a4d1  je short 0x530A4E3
0x530a4d3  cmp byte ptr [rax],0
0x530a4d6  jne short 0x530A4E3
0x530a4d8  mov dword ptr [0],0xDEADC0DE
0x530a4e3  mov rbx,[rbx+0x20]
0x530a4e7  mov rcx,[r14]
0x530a4ea  test rcx,rcx
0x530a4ed  lea rax,[0x129C1210]
0x530a4f4  cmovne rax,rcx
0x530a4f8  xorps xmm0,xmm0
```

### 0x530A4FB..0x530A5AB: Publishes the new handle: stores the [r14]-based pointer (or fallback 0x129C1210) into [rbp+0x1C0], reads a word through its vtable if non-null ([rcx+0x10]), takes a reference on [rax+8] (`lock inc`), then releases the old [rbp+0x1C8] handle inline (lock dec +8/+0xC with virtual deletes) keeping r8=[rbp+0x1D8] live; reads the last-entry float pair through r15 (movsd [r15+0x30], movss [r15+0x38]) into [rbp+0x1B0]/[rbp+0x1B8]; copies byte [rdi+0x64] into word [rbp+0x1D6].
```
0x530a4fb  movaps [rbp+0x1C0],xmm0
0x530a502  mov rcx,[rax]
0x530a505  test rcx,rcx
0x530a508  je short 0x530A50E
0x530a50a  movzx ecx,word ptr [rcx+0x10]
0x530a50e  mov rcx,[rax+8]
0x530a512  test rcx,rcx
0x530a515  je short 0x530A521
0x530a517  lock inc dword ptr [rcx+8]
0x530a51b  mov rcx,[rax+8]
0x530a51f  jmp short 0x530A523
0x530a521  xor ecx,ecx
0x530a523  movzx r13d,byte ptr [rbp+0x260]
0x530a52b  movzx r12d,byte ptr [rbp+0x258]
0x530a533  mov rax,[rax]
0x530a536  mov [rbp+0x1C0],rax
0x530a53d  mov r14,[rbp+0x1C8]
0x530a544  mov [rbp+0x1C8],rcx
0x530a54b  test r14,r14
0x530a54e  je short 0x530A58B
0x530a550  lock dec dword ptr [r14+8]
0x530a555  jne short 0x530A58B
0x530a557  mov rax,[r14]
0x530a55a  mov rax,[rax]
0x530a55d  mov rcx,r14
0x530a560  call qword ptr [0xF99FFA0]
0x530a566  mov r8,[rbp+0x1D8]
0x530a56d  lock dec dword ptr [r14+0xC]
0x530a572  jne short 0x530A58B
0x530a574  mov rax,[r14]
0x530a577  mov rax,[rax+8]
0x530a57b  mov rcx,r14
0x530a57e  call qword ptr [0xF99FFA0]
0x530a584  mov r8,[rbp+0x1D8]
0x530a58b  movss xmm0,[r15+0x38]
0x530a591  movsd xmm1,[r15+0x30]
0x530a597  movsd [rbp+0x1B0],xmm1
0x530a59f  movss [rbp+0x1B8],xmm0
0x530a5a7  movzx eax,byte ptr [rdi+0x64]
0x530a5ab  mov [rbp+0x1D6],ax
```

### 0x530A5B2..0x530A68C: Spills seven stack arguments for the constructor call ([rsp+0x20..0x50], including &[rbp+0x108], &[rbp+0x1D6], &[rbp+0x1B0], &[rbp+0x1C0], the two bytes r12b/r13b) and calls 0x668BF20 (rcx=&[rbp-0x20] out, rdx=rdi, r8=rsi, r9=&[rbp+0xB0]); TLS guard check against gs:[0x58] (slow path 0x530A78C at the end of the listing); initializes [rbp+0x190]/[rbp+0x198], zeroes [rbp+0x1A8] and [rbp+0x178], and calls 0x39A7D40 (rdx=rsi=&[rbp+0x1A0], r8=&[rbp+0x140]).
```
0x530a5b2  mov [rsp+0x50],r13b
0x530a5b7  mov [rsp+0x48],r12b
0x530a5bc  lea rax,[rbp+0x108]
0x530a5c3  mov [rsp+0x40],rax
0x530a5c8  lea rax,[rbp+0x1D6]
0x530a5cf  mov [rsp+0x38],rax
0x530a5d4  lea rax,[rbp+0x1B0]
0x530a5db  mov [rsp+0x30],rax
0x530a5e0  lea rax,[rbp+0x1C0]
0x530a5e7  mov [rsp+0x28],rax
0x530a5ec  mov [rsp+0x20],r8
0x530a5f1  lea r14,[rbp-0x20]
0x530a5f5  lea r9,[rbp+0xB0]
0x530a5fc  mov rcx,r14
0x530a5ff  mov rdx,rdi
0x530a602  mov r8,rsi
0x530a605  call 0x668BF20
0x530a60a  nop
0x530a60b  mov eax,[0x129C5598]
0x530a611  mov ecx,[0x128767C8]
0x530a617  mov rdx,gs:[0x58]
0x530a620  mov rcx,[rdx+rcx*8]
0x530a624  cmp eax,[rcx+4]
0x530a62a  jg 0x530A78C
0x530a630  lea rcx,[0x129C5460]
0x530a637  mov [rbp+0x190],rcx
0x530a63e  mov byte ptr [rbp+0x198],0
0x530a645  lea rsi,[rbp+0x1A0]
0x530a64c  mov qword ptr [rbp+0x1A8],0
0x530a657  mov byte ptr [rbp+0x178],0
0x530a65e  lea r8,[rbp+0x140]
0x530a665  mov rdx,rsi
0x530a668  call 0x39A7D40
0x530a66d  nop
0x530a66e  mov [rbp+0x198],al
0x530a674  mov [rbp+0x140],r14
0x530a67b  mov byte ptr [rbp+0x148],7
0x530a682  mov rax,[rbx]
0x530a685  mov rax,[rax+0x360]
0x530a68c  lea rdx,[rbp+0x140]
```

### 0x530A693..0x530A730: Dispatches the event object &[rbp+0x140] (ptr=[rbp-0x20], tag byte 7) through vtable slot [ [rbx]+0x360 ] (rcx=rbx); if byte [rbp+0x198]==1 logs via 0x77A2500 with data table 0x1244FD00; calls destructor 0x530A9F0 on &[rbp-0x20]; releases the [rbp+0x1C8] handle inline; then switches byte [rbp+0x138] (0..3) via jump table 0xF249978 (case 0x530A71E tests [rbp+0x130] and chains to the [rbp+0x150] release; case 0x530A730 calls 0x4DFB470 on &[rbp+0x120]).
```
0x530a693  mov rcx,rbx
0x530a696  call qword ptr [0xF99FFA0]
0x530a69c  nop
0x530a69d  cmp byte ptr [rbp+0x198],1
0x530a6a4  jne short 0x530A6C1
0x530a6a6  mov r8,[rbp+0x190]
0x530a6ad  add r8,0x60
0x530a6b1  lea rcx,[0x1244FD00]
0x530a6b8  mov rdx,rsi
0x530a6bb  call 0x77A2500
0x530a6c0  nop
0x530a6c1  lea rcx,[rbp-0x20]
0x530a6c5  call 0x530A9F0
0x530a6ca  mov rsi,[rbp+0x1C8]
0x530a6d1  test rsi,rsi
0x530a6d4  je short 0x530A701
0x530a6d6  lock dec dword ptr [rsi+8]
0x530a6da  jne short 0x530A701
0x530a6dc  mov rax,[rsi]
0x530a6df  mov rax,[rax]
0x530a6e2  mov rcx,rsi
0x530a6e5  call qword ptr [0xF99FFA0]
0x530a6eb  lock dec dword ptr [rsi+0xC]
0x530a6ef  jne short 0x530A701
0x530a6f1  mov rax,[rsi]
0x530a6f4  mov rax,[rax+8]
0x530a6f8  mov rcx,rsi
0x530a6fb  call qword ptr [0xF99FFA0]
0x530a701  movzx eax,byte ptr [rbp+0x138]
0x530a708  cmp rax,3
0x530a70c  ja short 0x530A73C
0x530a70e  lea rcx,[0xF249978]
0x530a715  movsxd rax,[rcx+rax*4]
0x530a719  add rax,rcx
0x530a71c  jmp rax
0x530a71e  mov rsi,[rbp+0x130]
0x530a725  test rsi,rsi
0x530a728  jne 0x530A3DE
0x530a72e  jmp short 0x530A73C
0x530a730  lea rcx,[rbp+0x120]
```

### 0x530A737..0x530A7D8: Case tail: call 0x4DFB470 on &[rbp+0x120]; common tail 0x530A73C reloads r8=[rbp+0x1D8] and releases the [r8+8] ref-count object inline (lock dec +8/+0xC, two virtual deletes); epilogue pops/ret; TLS slow path 0x530A78C: calls 0xE938CB0 on the guard, re-tests it for -1, and on failure prepares a report: string ptr 0xF52E07A len 0x15 into [rbp+0x180]/[rbp+0x188], 16 bytes from 0xF0BCBF8 into [rbp+0xF0], and two more stack args.
```
0x530a737  call 0x4DFB470
0x530a73c  mov r8,[rbp+0x1D8]
0x530a743  mov rsi,[r8+8]
0x530a747  test rsi,rsi
0x530a74a  je short 0x530A778
0x530a74c  lock dec dword ptr [rsi+8]
0x530a750  jne short 0x530A778
0x530a752  mov rax,[rsi]
0x530a755  mov rax,[rax]
0x530a758  mov rcx,rsi
0x530a75b  call qword ptr [0xF99FFA0]
0x530a761  lock dec dword ptr [rsi+0xC]
0x530a765  jne short 0x530A778
0x530a767  mov rax,[rsi]
0x530a76a  mov rax,[rax+8]
0x530a76e  mov rcx,rsi
0x530a771  call qword ptr [0xF99FFA0]
0x530a777  nop
0x530a778  add rsp,0x268
0x530a77f  pop rbx
0x530a780  pop rdi
0x530a781  pop rsi
0x530a782  pop r12
0x530a784  pop r13
0x530a786  pop r14
0x530a788  pop r15
0x530a78a  pop rbp
0x530a78b  ret
0x530a78c  lea rcx,[0x129C5598]
0x530a793  call 0xE938CB0
0x530a798  cmp dword ptr [0x129C5598],0xFFFFFFFF
0x530a79f  jne 0x530A630
0x530a7a5  lea rax,[0xF52E07A]
0x530a7ac  mov [rbp+0x180],rax
0x530a7b3  mov qword ptr [rbp+0x188],0x15
0x530a7be  movups xmm0,[0xF0BCBF8]
0x530a7c5  movaps [rbp+0xF0],xmm0
0x530a7cc  lea rax,[0xF2487E0]
0x530a7d3  mov [rsp+0x28],rax
0x530a7d8  mov dword ptr [rsp+0x20],0
```

### 0x530A7E0..0x530A81B: Fires the report (call 0x2FE330: rcx=logger 0x129C5460, rdx=&[rbp+0xF0], r8b=1, r9=&[rbp+0x180], plus 0xF2487E0 via [rsp+0x28]), then 0xE935740 (rcx=0x53D6C30) and guard release 0xE938D70 (rcx=0x129C5598), jumps back to 0x530A630; trailing padding.
```
0x530a7e0  lea rcx,[0x129C5460]
0x530a7e7  lea rdx,[rbp+0xF0]
0x530a7ee  lea r9,[rbp+0x180]
0x530a7f5  mov r8b,1
0x530a7f8  call 0x2FE330
0x530a7fd  nop
0x530a7fe  lea rcx,[0x53D6C30]
0x530a805  call 0xE935740
0x530a80a  lea rcx,[0x129C5598]
0x530a811  call 0xE938D70
0x530a816  jmp 0x530A630
0x530a81b  nop [rax+rax]
```

## Function 2 — ctor, 0x668BF20..0x668C1CC (called from the clone at 0x530A605)

Arg map at entry [V]: rcx -> rsi = `this` (dest effect), rdx -> rdi (src description), r8 -> [this] (qword store), r9 -> rbx (float array, 17 floats); stack args: [rbp+0x70] -> r12, [rbp+0x78] -> rdx-arg of 0x4DFB570, [rbp+0x80] -> r13 (3 floats), [rbp+0x88] -> r15 (word), [rbp+0x90] -> r14 (source data struct); [rbp+0x98]/[rbp+0xA0] bytes copied to rsi+0xC8/0xC9.

### 0x668BF20..0x668BFC2: Prologue with frame cookie; loads the five stack args; stores r8 into [this]; calls base ctor 0x4DFB570 (rcx=this+8 via [rbp-0x18] spill, rdx=[rbp+0x78]); copies floats rbx+0x00..0x20 into rsi+0x18..0x34 (movss one at a time).
```
0x668bf20  push rbp
0x668bf21  push r15
0x668bf23  push r14
0x668bf25  push r13
0x668bf27  push r12
0x668bf29  push rsi
0x668bf2a  push rdi
0x668bf2b  push rbx
0x668bf2c  sub rsp,0x48
0x668bf30  lea rbp,[rsp+0x40]
0x668bf35  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x668bf3d  mov rbx,r9
0x668bf40  mov rdi,rdx
0x668bf43  mov rsi,rcx
0x668bf46  mov r14,[rbp+0x90]
0x668bf4d  mov r15,[rbp+0x88]
0x668bf54  mov r12,[rbp+0x70]
0x668bf58  mov r13,[rbp+0x80]
0x668bf5f  mov rdx,[rbp+0x78]
0x668bf63  mov [rcx],r8
0x668bf66  add rcx,8
0x668bf6a  mov [rbp-0x18],rcx
0x668bf6e  call 0x4DFB570
0x668bf73  movss xmm0,[rbx]
0x668bf77  movss [rsi+0x18],xmm0
0x668bf7c  movss xmm0,[rbx+4]
0x668bf81  movss [rsi+0x1C],xmm0
0x668bf86  movss xmm0,[rbx+8]
0x668bf8b  movss [rsi+0x20],xmm0
0x668bf90  movss xmm0,[rbx+0xC]
0x668bf95  movss [rsi+0x24],xmm0
0x668bf9a  movss xmm0,[rbx+0x10]
0x668bf9f  movss [rsi+0x28],xmm0
0x668bfa4  movss xmm0,[rbx+0x14]
0x668bfa9  movss [rsi+0x2C],xmm0
0x668bfae  movss xmm0,[rbx+0x18]
0x668bfb3  movss [rsi+0x30],xmm0
0x668bfb8  movss xmm0,[rbx+0x1C]
0x668bfbd  movss [rsi+0x34],xmm0
0x668bfc2  movss xmm0,[rbx+0x20]
```

### 0x668BFCC..0x668C076: Copies the remaining floats rbx+0x24..0x3C into rsi+0x3C..0x54, three floats from [rbp+0x80] (r13) into rsi+0x58..0x60, 16 bytes from [rdi+0x20] into rsi+0x64, and zeroes rsi+0x78 (16 bytes); takes a reference on [r12+8] (`lock inc`) and stores the shared handle into rsi+0x78 (object ptr) / rsi+0x80 (ref-count ptr); copies word [r15] into rsi+0x88 and 16 bytes from [r14] into rsi+0x90.
```
0x668bfcc  movss xmm0,[rbx+0x24]
0x668bfd1  movss [rsi+0x3C],xmm0
0x668bfd6  movss xmm0,[rbx+0x28]
0x668bfdb  movss [rsi+0x40],xmm0
0x668bfe0  movss xmm0,[rbx+0x2C]
0x668bfe5  movss [rsi+0x44],xmm0
0x668bfea  movss xmm0,[rbx+0x30]
0x668bfef  movss [rsi+0x48],xmm0
0x668bff4  movss xmm0,[rbx+0x34]
0x668bff9  movss [rsi+0x4C],xmm0
0x668bffe  movss xmm0,[rbx+0x38]
0x668c003  movss [rsi+0x50],xmm0
0x668c008  movss xmm0,[rbx+0x3C]
0x668c00d  movss [rsi+0x54],xmm0
0x668c012  movss xmm0,[r13]
0x668c018  movss [rsi+0x58],xmm0
0x668c01d  movss xmm0,[r13+4]
0x668c023  movss [rsi+0x5C],xmm0
0x668c028  movss xmm0,[r13+8]
0x668c02e  movss [rsi+0x60],xmm0
0x668c033  mov rax,[rdi+0x20]
0x668c037  movups xmm0,[rax]
0x668c03a  movups [rsi+0x64],xmm0
0x668c03e  xorps xmm0,xmm0
0x668c041  movups [rsi+0x78],xmm0
0x668c045  mov rax,[r12+8]
0x668c04a  test rax,rax
0x668c04d  je short 0x668C053
0x668c04f  lock inc dword ptr [rax+8]
0x668c053  mov rax,[r12]
0x668c057  mov [rsi+0x78],rax
0x668c05b  mov rax,[r12+8]
0x668c060  mov [rsi+0x80],rax
0x668c067  movzx eax,word ptr [r15]
0x668c06b  mov [rsi+0x88],ax
0x668c072  movups xmm0,[r14]
0x668c076  movups [rsi+0x90],xmm0
```

### 0x668C07D..0x668C12D: Copies byte [r14+0x10] into rsi+0xA0, sets byte [rsi+0xC0]=0xFF, and switches byte [r14+0x30] (0..3 via table 0xF2BF670; >3 falls through to 0x668C18E); case 0 (0x668C0AE) stores [r14+0x18] into rsi+0xA8, zeroes 16 bytes at rsi+0xB0, takes a reference on [r14+0x28], advances r14 by 0x28 and publishes [rsi+0xB0]=ref-count ptr / [rsi+0xB8]=object ptr, then jumps to the common tail 0x668C188; case 1 (0x668C0F1) allocates 0x20 bytes through global allocator vtable [0x1233E1A8]+8 (fallback 0x668C1BC -> call 0x9BC830) and zeroes the new 0x20-byte object (rdi) in both halves.
```
0x668c07d  movzx eax,byte ptr [r14+0x10]
0x668c082  mov [rsi+0xA0],al
0x668c088  mov byte ptr [rsi+0xC0],0xFF
0x668c08f  movzx ebx,byte ptr [r14+0x30]
0x668c094  cmp rbx,3
0x668c098  ja 0x668C18E
0x668c09e  lea rax,[0xF2BF670]
0x668c0a5  movsxd rcx,[rax+rbx*4]
0x668c0a9  add rcx,rax
0x668c0ac  jmp rcx
0x668c0ae  mov rax,[r14+0x18]
0x668c0b2  mov [rsi+0xA8],rax
0x668c0b9  lea rax,[rsi+0xB0]
0x668c0c0  xorps xmm0,xmm0
0x668c0c3  movups [rsi+0xB0],xmm0
0x668c0ca  mov rcx,[r14+0x28]
0x668c0ce  test rcx,rcx
0x668c0d1  je short 0x668C0D7
0x668c0d3  lock inc dword ptr [rcx+8]
0x668c0d7  mov rcx,[r14+0x20]
0x668c0db  add r14,0x28
0x668c0df  mov [rax],rcx
0x668c0e2  mov rax,[r14]
0x668c0e5  mov [rsi+0xB8],rax
0x668c0ec  jmp 0x668C188
0x668c0f1  lea rax,[rsi+0x78]
0x668c0f5  mov [rbp-8],rax
0x668c0f9  lea rax,[rsi+0xA8]
0x668c100  mov [rbp-0x10],rax
0x668c104  mov rcx,[0x1233E1A8]
0x668c10b  mov rax,[rcx]
0x668c10e  mov rax,[rax+8]
0x668c112  mov edx,0x20
0x668c117  call qword ptr [0xF99FFA0]
0x668c11d  nop
0x668c11e  mov rdi,rax
0x668c121  test rax,rax
0x668c124  je 0x668C1BC
0x668c12a  xorps xmm0,xmm0
0x668c12d  movups [rdi+0x10],xmm0
```

### 0x668C131..0x668C1C6: Case 1 continued: zeroes [rdi] (16 bytes), binds r14=[r14+0x18] (now a ref-counted object: +0x0 data ptr, +0x8 ref-count, +0x10.. payload), takes a reference on [r14+8] (`lock inc [rax+0xC]`), publishes [rdi]=data ptr / [rdi+8]=ref-count ptr (releasing the old [rdi+8] ref inline if non-zero), copies 16 bytes [r14+0x10] into [rdi+0x10]; common tail 0x668C188: [rsi+0xC0]=bl; switch exit 0x668C18E copies bytes [rbp+0x98]->rsi+0xC8 and [rbp+0xA0]->rsi+0xC9, returns rsi; alloc-failure path 0x668C1BC calls 0x9BC830 (0x20).
```
0x668c131  movups [rdi],xmm0
0x668c134  lea rax,[rsi+0xA8]
0x668c13b  mov [rax],rdi
0x668c13e  mov r14,[r14+0x18]
0x668c142  mov rax,[r14+8]
0x668c146  test rax,rax
0x668c149  je short 0x668C177
0x668c14b  mov rdx,[r14]
0x668c14e  lock inc dword ptr [rax+0xC]
0x668c152  mov rcx,[rdi+8]
0x668c156  mov [rdi],rdx
0x668c159  mov [rdi+8],rax
0x668c15d  test rcx,rcx
0x668c160  je short 0x668C17F
0x668c162  lock dec dword ptr [rcx+0xC]
0x668c166  jne short 0x668C17F
0x668c168  mov rax,[rcx]
0x668c16b  mov rax,[rax+8]
0x668c16f  call qword ptr [0xF99FFA0]
0x668c175  jmp short 0x668C17F
0x668c177  mov qword ptr [rdi+8],0
0x668c17f  movups xmm0,[r14+0x10]
0x668c184  movups [rdi+0x10],xmm0
0x668c188  mov [rsi+0xC0],bl
0x668c18e  movzx eax,byte ptr [rbp+0xA0]
0x668c195  movzx ecx,byte ptr [rbp+0x98]
0x668c19c  mov [rsi+0xC8],cl
0x668c1a2  mov [rsi+0xC9],al
0x668c1a8  mov rax,rsi
0x668c1ab  add rsp,0x48
0x668c1af  pop rbx
0x668c1b0  pop rdi
0x668c1b1  pop rsi
0x668c1b2  pop r12
0x668c1b4  pop r13
0x668c1b6  pop r14
0x668c1b8  pop r15
0x668c1ba  pop rbp
0x668c1bb  ret
0x668c1bc  mov ecx,0x20
0x668c1c1  call 0x9BC830
0x668c1c6  nop
```

### 0x668C1C7..0x668C1CC: Rejoin after the slow allocation jumps back into the zero-init sequence; padding.
```
0x668c1c7  jmp 0x668C12A
0x668c1cc  nop [rax]
```

## Function 3 — emplace, 0x66B2B30..0x66B2DD8

Arg map at entry [V]: rcx -> rax = output parameter block (filled in place), rdx = pointer to a pointer, followed to [[rdx]]->[+0x40] = source description object; r8b = slot index (validated 0..4 after `dec`, else assert call 0x1A2800); output fields [rax+0x00..0x56] all written [V].

### 0x66B2B30..0x66B2BBF: Zero-initializes the output block (byte [rcx+0xE]=2, dword [rcx+0x10]=0, byte [rcx+0x14]=0, 32 zero bytes at [rcx+0x18]/[rcx+0x24], word [rcx+0x54]=0); follows rdx to the description; then a chained byte-compare on [rdx+0x180]/[rdx+0x181] (xors against 3/2, 6/8, 4/5) selects a variant code 1..8 into r11d (0 when nothing matches).
```
0x66b2b30  push rsi
0x66b2b31  push rdi
0x66b2b32  push rbp
0x66b2b33  push rbx
0x66b2b34  sub rsp,0x28
0x66b2b38  mov rax,rcx
0x66b2b3b  mov byte ptr [rcx+0xE],2
0x66b2b3f  mov dword ptr [rcx+0x10],0
0x66b2b46  mov byte ptr [rcx+0x14],0
0x66b2b4a  xorps xmm0,xmm0
0x66b2b4d  movups [rcx+0x18],xmm0
0x66b2b51  movups [rcx+0x24],xmm0
0x66b2b55  mov word ptr [rcx+0x54],0
0x66b2b5b  mov rcx,[rdx]
0x66b2b5e  mov rdx,[rcx+0x40]
0x66b2b62  xor r11d,r11d
0x66b2b65  cmp byte ptr [rdx+0x185],1
0x66b2b6c  jne 0x66B2C11
0x66b2b72  movzx ecx,byte ptr [rdx+0x180]
0x66b2b79  movzx r9d,byte ptr [rdx+0x181]
0x66b2b81  mov ebx,ecx
0x66b2b83  xor bl,3
0x66b2b86  mov r10d,r9d
0x66b2b89  xor r10b,2
0x66b2b8d  mov r11d,1
0x66b2b93  mov esi,ebx
0x66b2b95  or sil,r10b
0x66b2b98  je short 0x66B2C11
0x66b2b9a  mov esi,ecx
0x66b2b9c  xor sil,6
0x66b2ba0  mov edi,r9d
0x66b2ba3  xor dil,8
0x66b2ba7  mov r11d,3
0x66b2bad  mov ebp,esi
0x66b2baf  or bpl,dil
0x66b2bb2  je short 0x66B2C11
0x66b2bb4  mov r11d,4
0x66b2bba  or dil,bl
0x66b2bbd  je short 0x66B2C11
0x66b2bbf  mov edi,ecx
```

### 0x66B2BC1..0x66B2C5D: Finishes the variant chain (codes 5..8 plus the final equality test yielding 9 via `lea r11d,[r10+r10*8]`) and stores it at [rax]; computes [rax+8] from byte [rdx+0x1A8] (1 -> 2, 2 -> 1, else 0); validates r8b (dec, >=5 -> jump 0x66B2DD2 assert `call 0x1A2800`); stores dword LUT[0xF2BF190][r8b] at [rax+0x10].
```
0x66b2bc1  xor dil,4
0x66b2bc5  mov ebp,r9d
0x66b2bc8  xor bpl,5
0x66b2bcc  mov r11d,5
0x66b2bd2  or bpl,dil
0x66b2bd5  je short 0x66B2C11
0x66b2bd7  mov edi,r9d
0x66b2bda  xor dil,3
0x66b2bde  mov r11d,6
0x66b2be4  or bl,dil
0x66b2be7  je short 0x66B2C11
0x66b2be9  mov r11d,7
0x66b2bef  or sil,dil
0x66b2bf2  je short 0x66B2C11
0x66b2bf4  mov r11d,8
0x66b2bfa  or r10b,cl
0x66b2bfd  je short 0x66B2C11
0x66b2bff  xor r9b,1
0x66b2c03  xor r10d,r10d
0x66b2c06  or cl,r9b
0x66b2c09  sete r10b
0x66b2c0d  lea r11d,[r10+r10*8]
0x66b2c11  mov [rax],r11d
0x66b2c14  movzx ecx,byte ptr [rdx+0x1A8]
0x66b2c1b  xor r9d,r9d
0x66b2c1e  cmp cl,1
0x66b2c21  sete r9b
0x66b2c25  add r9d,r9d
0x66b2c28  cmp cl,2
0x66b2c2b  mov ecx,1
0x66b2c30  cmovne ecx,r9d
0x66b2c34  mov [rax+8],ecx
0x66b2c37  dec r8b
0x66b2c3a  cmp r8b,5
0x66b2c3e  jae 0x66B2DD2
0x66b2c44  mov r9,0x104070502080603
0x66b2c4e  movzx ecx,r8b
0x66b2c52  lea r8,[0xF2BF190]
0x66b2c59  mov ecx,[r8+rcx*4]
0x66b2c5d  mov [rax+0x10],ecx
```

### 0x66B2C60..0x66B2D02: Copies bytes [rdx+0x189]->[rax+0x54] and [rdx+0x19C]->[rax+0x55]; derives [rax+0x34] by shifting the constant 0x104070502080603 right by 8*[rdx+0x18B] (fallback 2 when the byte >=8), and fills [rax+0x38], [rax+0x3C], [rax+0x40] from bytes [rdx+0x18C], [rdx+0x18E], [rdx+0x18D] biased by 0xFE through dword LUT 0xF2BF1A4 (0 when out of range).
```
0x66b2c60  movzx ecx,byte ptr [rdx+0x189]
0x66b2c67  mov [rax+0x54],cl
0x66b2c6a  movzx ecx,byte ptr [rdx+0x19C]
0x66b2c71  mov [rax+0x55],cl
0x66b2c74  movzx ecx,byte ptr [rdx+0x18B]
0x66b2c7b  mov r8d,ecx
0x66b2c7e  shl ecx,3
0x66b2c81  mov r10,r9
0x66b2c84  shr r10,cl
0x66b2c87  cmp r8b,8
0x66b2c8b  mov ecx,2
0x66b2c90  cmovb ecx,r10d
0x66b2c94  movzx r10d,byte ptr [rdx+0x18C]
0x66b2c9c  add r10b,0xFE
0x66b2ca0  xor r11d,r11d
0x66b2ca3  lea r8,[0xF2BF1A4]
0x66b2caa  mov esi,0
0x66b2caf  cmp r10b,8
0x66b2cb3  ja short 0x66B2CBD
0x66b2cb5  movzx r10d,r10b
0x66b2cb9  mov esi,[r8+r10*4]
0x66b2cbd  movzx r10d,byte ptr [rdx+0x18E]
0x66b2cc5  add r10b,0xFE
0x66b2cc9  cmp r10b,8
0x66b2ccd  ja short 0x66B2CD7
0x66b2ccf  movzx r10d,r10b
0x66b2cd3  mov r11d,[r8+r10*4]
0x66b2cd7  movzx ebx,byte ptr [rdx+0x18D]
0x66b2cde  add bl,0xFE
0x66b2ce1  xor r10d,r10d
0x66b2ce4  mov edi,0
0x66b2ce9  cmp bl,8
0x66b2cec  ja short 0x66B2CF5
0x66b2cee  movzx edi,bl
0x66b2cf1  mov edi,[r8+rdi*4]
0x66b2cf5  mov [rax+0x34],cl
0x66b2cf8  mov [rax+0x38],esi
0x66b2cfb  mov [rax+0x3C],edi
0x66b2cfe  mov [rax+0x40],r11d
0x66b2d02  movzx ecx,byte ptr [rdx+0x190]
```

### 0x66B2D09..0x66B2DA3: Fills the mirrored four-slot block: dword LUT 0xF2BF1A4 of byte [rdx+0x190] into r10d ([rax+0x48]); bytes [rdx+0x18F], [rdx+0x192], [rdx+0x191] (0xFE-biased LUT) into [rax+0x44] (also shifted-constant derived from [rdx+0x18F], fallback 2), [rax+0x4C], [rax+0x50]; copies [rdx+0x184]->[rax+4], [rdx+0x188]->[rax+0xC], computes [rax+0xD]=([rdx+0x188]!=0 && [rdx+0x193]!=0).
```
0x66b2d09  add cl,0xFE
0x66b2d0c  cmp cl,8
0x66b2d0f  ja short 0x66B2D18
0x66b2d11  movzx ecx,cl
0x66b2d14  mov r10d,[r8+rcx*4]
0x66b2d18  movzx ecx,byte ptr [rdx+0x18F]
0x66b2d1f  movzx ebx,byte ptr [rdx+0x192]
0x66b2d26  add bl,0xFE
0x66b2d29  xor r11d,r11d
0x66b2d2c  mov esi,0
0x66b2d31  cmp bl,8
0x66b2d34  ja short 0x66B2D3D
0x66b2d36  movzx esi,bl
0x66b2d39  mov esi,[r8+rsi*4]
0x66b2d3d  movzx ebx,byte ptr [rdx+0x191]
0x66b2d44  add bl,0xFE
0x66b2d47  cmp bl,8
0x66b2d4a  ja short 0x66B2D54
0x66b2d4c  movzx r11d,bl
0x66b2d50  mov r11d,[r8+r11*4]
0x66b2d54  mov r8d,ecx
0x66b2d57  shl ecx,3
0x66b2d5a  mov rdi,r9
0x66b2d5d  shr rdi,cl
0x66b2d60  cmp r8b,8
0x66b2d64  mov r8d,2
0x66b2d6a  cmovae edi,r8d
0x66b2d6e  mov [rax+0x44],dil
0x66b2d72  mov [rax+0x48],r10d
0x66b2d76  mov [rax+0x4C],r11d
0x66b2d7a  mov [rax+0x50],esi
0x66b2d7d  movzx ecx,byte ptr [rdx+0x184]
0x66b2d84  mov [rax+4],cl
0x66b2d87  movzx ecx,byte ptr [rdx+0x188]
0x66b2d8e  mov [rax+0xC],cl
0x66b2d91  cmp byte ptr [rdx+0x193],0
0x66b2d98  setne r10b
0x66b2d9c  and r10b,cl
0x66b2d9f  mov [rax+0xD],r10b
0x66b2da3  movzx ecx,byte ptr [rdx+0x18A]
```

### 0x66B2DAA..0x66B2DD8: Derives [rax+0xE] from byte [rdx+0x18A] by the same 0x104070502080603 shift (fallback 2); copies byte [rdx+0x194]->[rax+0x56]; epilogue; out-of-range r8b path (0x66B2DD2): assert `call 0x1A2800`; int3 padding.
```
0x66b2daa  mov r10d,ecx
0x66b2dad  shl ecx,3
0x66b2db0  shr r9,cl
0x66b2db3  cmp r10b,8
0x66b2db7  cmovae r9d,r8d
0x66b2dbb  mov [rax+0xE],r9b
0x66b2dbf  movzx ecx,byte ptr [rdx+0x194]
0x66b2dc6  mov [rax+0x56],cl
0x66b2dc9  add rsp,0x28
0x66b2dcd  pop rbx
0x66b2dce  pop rbp
0x66b2dcf  pop rdi
0x66b2dd0  pop rsi
0x66b2dd1  ret
0x66b2dd2  call 0x1A2800
0x66b2dd7  int3
0x66b2dd8  int3
```

## Field map — every [reg+off] store/load, one row per distinct (function, base, off)

Columns: first cell = function + base + off (unique key) | size in bytes (from the instruction; when sites differ the SIMD size leads) | direction (W=store, R=load, RW=read-modify-write like `lock inc/dec`) | verbatim site line(s) | meaning only where an instruction/string shows it, else '-'. Index-form ([base+idx*scale]) and absolute ([0xADDR]) operands are not reg+off fields and are not rows; they remain visible in the phase listings above. [rax] style bare operands are listed as +0x0.

### clone (0x530A1B0..0x530A81B)

| offset | size | direction | verbatim line(s) | meaning |
|--|--|--|--|--|
| clone rax+0x0 | 16 | R | 0x530a229  cmp byte ptr [rax],1<br>0x530a27b  movups xmm0,[rax]<br>0x530a38b  mov rax,[rax]<br>0x530a3eb  mov rax,[rax]<br>0x530a42d  mov rax,[rax]<br>0x530a4d3  cmp byte ptr [rax],0<br>0x530a502  mov rcx,[rax]<br>0x530a533  mov rax,[rax]<br>0x530a55a  mov rax,[rax]<br>0x530a6df  mov rax,[rax]<br>0x530a755  mov rax,[rax] | - (movups site is the 64-byte entry copy; mov sites load vtables/objects; sites see different rax bindings) |
| clone rax+0x8 | 8 | R | 0x530a235  mov rax,[rax+8]<br>0x530a3a0  mov rax,[rax+8]<br>0x530a404  mov rax,[rax+8]<br>0x530a449  mov rax,[rax+8]<br>0x530a47d  mov rax,[rax+8]<br>0x530a50e  mov rcx,[rax+8]<br>0x530a51b  mov rcx,[rax+8]<br>0x530a577  mov rax,[rax+8]<br>0x530a6f4  mov rax,[rax+8]<br>0x530a76a  mov rax,[rax+8] | - |
| clone rax+0x10 | 16 | R | 0x530a285  movups xmm0,[rax+0x10] | - |
| clone rax+0x20 | 16 | R | 0x530a290  movups xmm0,[rax+0x20] | - |
| clone rax+0x30 | 16 | R | 0x530a29b  movups xmm0,[rax+0x30] | - |
| clone rax+0x40 | 8 | R | 0x530a20a  cmp qword ptr [rax+0x40],0 | null-checked qword before clone proceeds [V] |
| clone rax+0x48 | 8 | R | 0x530a269  mov rdx,[rax+0x48]<br>0x530a2bc  mov rdx,[rax+0x48] | base of index math at 0x530a263..0x530a274 [I] |
| clone rax+0x50 | 8 | R | 0x530a26d  mov rax,[rax+0x50]<br>0x530a2c0  mov rax,[rax+0x50] | `dec` + `and` mask operand at 0x530a271..0x530a274 [I] |
| clone rax+0x58 | 8 | R | 0x530a25f  mov rdx,[rax+0x58]<br>0x530a2b4  mov rcx,[rax+0x58] | - |
| clone rax+0x60 | 8 | R | 0x530a25b  mov rcx,[rax+0x60] | added to +0x58, then dec/and at 0x530a263..0x530a274 [I] |
| clone rax+0x68 | 8 | R | 0x530a2b8  add rcx,[rax+0x68] | added to +0x58 in the second index computation [I] |
| clone rax+0x70 | 1 | R | 0x530a2aa  cmp byte ptr [rax+0x70],1 | byte flag selecting the second entry load [V:cmp 1] |
| clone rax+0x78 | 1 | W | 0x530a257  mov byte ptr [rax+0x78],1 | set to 1 on the fast path [V] |
| clone rax+0x360 | 8 | R | 0x530a685  mov rax,[rax+0x360] | vtable slot read, then `call qword ptr [0xF99FFA0]` at 0x530a696 [V] |
| clone rbx+0x0 | 8 | R | 0x530a682  mov rax,[rbx] | rax then rebound to [rax+0x360] (0x530a685); rbx was reassigned at 0x530a4e3 [V] |
| clone rbx+0x10 | 8 | R | 0x530a21c  mov rax,[rbx+0x10]<br>0x530a4ca  mov rax,[rbx+0x10] | null-tested, then byte [rax] compared to 1 / 0 [V] |
| clone rbx+0x20 | 8 | R | 0x530a232  mov rcx,[rbx+0x20]<br>0x530a4e3  mov rbx,[rbx+0x20] | - |
| clone rcx+0x4 | 4 | R | 0x530a624  cmp eax,[rcx+4] | guard value compared against eax=[0x129C5598] [V] |
| clone rcx+0x8 | 8 | R | 0x530a46b  mov rdx,[rcx+8] | - |
| clone rcx+0x10 | 2 | R | 0x530a50a  movzx ecx,word ptr [rcx+0x10] | read only when rcx=[rax] non-null (0x530a502..0x530a508) [V] |
| clone rdi+0x8 | 8 | R | 0x530a253  mov rax,[rdi+8]<br>0x530a2a6  mov rax,[rdi+8] | sub-object pointer whose +0x48..0x78 fields follow [I] |
| clone rdi+0x64 | 1 | R | 0x530a5a7  movzx eax,byte ptr [rdi+0x64] | byte copied into word [rbp+0x1D6] [V] |
| clone rsi+0x0 | 8 | R | 0x530a388  mov rax,[rsi]<br>0x530a3e8  mov rax,[rsi]<br>0x530a401  mov rax,[rsi]<br>0x530a446  mov rax,[rsi]<br>0x530a6dc  mov rax,[rsi]<br>0x530a6f1  mov rax,[rsi]<br>0x530a752  mov rax,[rsi]<br>0x530a767  mov rax,[rsi] | - |
| clone rsi+0x8 | 4 | RW | 0x530a382  lock dec dword ptr [rsi+8]<br>0x530a3de  lock dec dword ptr [rsi+8]<br>0x530a423  lock dec dword ptr [rsi+8]<br>0x530a6d6  lock dec dword ptr [rsi+8]<br>0x530a74c  lock dec dword ptr [rsi+8] | `lock dec` release site [V] |
| clone rsi+0xC | 4 | RW | 0x530a397  lock dec dword ptr [rsi+0xC]<br>0x530a3f7  lock dec dword ptr [rsi+0xC]<br>0x530a43c  lock dec dword ptr [rsi+0xC]<br>0x530a6eb  lock dec dword ptr [rsi+0xC]<br>0x530a761  lock dec dword ptr [rsi+0xC] | second `lock dec` after the +8 one reaches 0 [V] |
| clone rbp+0x0 | 1 | W/R | 0x530a326  mov byte ptr [rbp],1<br>0x530a35f  movzx eax,byte ptr [rbp] | flag byte dispatching jump table 0xF249988 [V] |
| clone rbp-0x8 | 8 | W/R | 0x530a322  mov [rbp-8],rax<br>0x530a416  mov rsi,[rbp-8] | - |
| clone rbp-0x10 | 16 | W | 0x530a301  movaps [rbp-0x10],xmm0<br>0x530a31e  mov [rbp-0x10],rcx | second handle's object ptr slot (16-byte zero then 8-byte store) [V] |
| clone rbp-0x18 | 8 | W/R | 0x530a2fd  mov [rbp-0x18],rax<br>0x530a379  mov rsi,[rbp-0x18] | first handle's ref-count ptr, released by the 0xF249988 case [I] |
| clone rbp-0x20 | 16 | W | 0x530a2dd  movaps [rbp-0x20],xmm0<br>0x530a2f9  mov [rbp-0x20],rcx | first handle's object ptr slot; passed as r9=&[rbp-0x20] to 0x4DEFED0 [V] |
| clone rbp+0xB0 | 16 | W | 0x530a27e  movaps [rbp+0xB0],xmm0 | 64-byte entry copy part 1; later r9=&[rbp+0xB0] arg [V] |
| clone rbp+0xC0 | 16 | W | 0x530a289  movaps [rbp+0xC0],xmm0 | 64-byte entry copy part 2 [V] |
| clone rbp+0xD0 | 16 | W | 0x530a294  movaps [rbp+0xD0],xmm0 | 64-byte entry copy part 3 [V] |
| clone rbp+0xE0 | 16 | W | 0x530a29f  movaps [rbp+0xE0],xmm0 | 64-byte entry copy part 4 [V] |
| clone rbp+0xF0 | 16 | W | 0x530a7c5  movaps [rbp+0xF0],xmm0 | 16 bytes from 0xF0BCBF8 (TLS slow path report data) [V] |
| clone rbp+0x108 | 8 | W | 0x530a4a6  mov qword ptr [rbp+0x108],0xFFFFFFFFFFFFFFFF | stored -1 [V] |
| clone rbp+0x110 | 8 | W | 0x530a4b1  mov qword ptr [rbp+0x110],0 | stored 0 [V] |
| clone rbp+0x118 | 1 | W | 0x530a4bc  mov byte ptr [rbp+0x118],0 | stored 0 [V] |
| clone rbp+0x130 | 8 | R | 0x530a71e  mov rsi,[rbp+0x130] | tested, chains to the [rbp+0x150] release case [I] |
| clone rbp+0x138 | 1 | W/R | 0x530a4c3  mov byte ptr [rbp+0x138],0<br>0x530a701  movzx eax,byte ptr [rbp+0x138] | flag byte dispatching jump table 0xF249978 [V] |
| clone rbp+0x140 | 8 | R/W | 0x530a45b  mov rcx,[rbp+0x140]<br>0x530a674  mov [rbp+0x140],r14 | object slot built by 0x39A7D40 / 0x4DEFED0, released at 0x530A45B [I] |
| clone rbp+0x148 | 1 | W | 0x530a67b  mov byte ptr [rbp+0x148],7 | tag byte 7 stored [V] |
| clone rbp+0x158 | 1 | W/R | 0x530a2d3  mov byte ptr [rbp+0x158],0<br>0x530a3ad  movzx eax,byte ptr [rbp+0x158] | flag byte dispatching jump table 0xF249998 [V] |
| clone rbp+0x178 | 1 | W | 0x530a657  mov byte ptr [rbp+0x178],0 | stored 0 [V] |
| clone rbp+0x180 | 8 | W | 0x530a7ac  mov [rbp+0x180],rax | string ptr 0xF52E07A (report arg, len follows) [V] |
| clone rbp+0x188 | 8 | W | 0x530a7b3  mov qword ptr [rbp+0x188],0x15 | string length 0x15 paired with [rbp+0x180] [V] |
| clone rbp+0x190 | 8 | W/R | 0x530a637  mov [rbp+0x190],rcx<br>0x530a6a6  mov r8,[rbp+0x190] | rcx=0x129C5460 (logger object); later +0x60 passed to 0x77A2500 [V] |
| clone rbp+0x198 | 1 | W/R | 0x530a63e  mov byte ptr [rbp+0x198],0<br>0x530a66e  mov [rbp+0x198],al<br>0x530a69d  cmp byte ptr [rbp+0x198],1 | result byte of call 0x39A7D40 gating the log call [V] |
| clone rbp+0x1A8 | 8 | W | 0x530a64c  mov qword ptr [rbp+0x1A8],0 | stored 0 [V] |
| clone rbp+0x1B0 | 8 | W | 0x530a597  movsd [rbp+0x1B0],xmm1 | copy of movsd [r15+0x30] [V] |
| clone rbp+0x1B8 | 4 | W | 0x530a59f  movss [rbp+0x1B8],xmm0 | copy of movss [r15+0x38] [V] |
| clone rbp+0x1C0 | 16 | W | 0x530a4fb  movaps [rbp+0x1C0],xmm0<br>0x530a536  mov [rbp+0x1C0],rax | handle slot: zeroed then object ptr ([r14]-derived or 0x129C1210) [V] |
| clone rbp+0x1C8 | 8 | R/W | 0x530a53d  mov r14,[rbp+0x1C8]<br>0x530a544  mov [rbp+0x1C8],rcx<br>0x530a6ca  mov rsi,[rbp+0x1C8] | paired ref-count slot of [rbp+0x1C0], released at 0x530a6d6 [I] |
| clone rbp+0x1D6 | 2 | W | 0x530a5ab  mov [rbp+0x1D6],ax | copy of byte [rdi+0x64] (word store) [V] |
| clone rbp+0x1D8 | 8 | W/R | 0x530a1d9  mov [rbp+0x1D8],r8<br>0x530a1f1  mov r8,[rbp+0x1D8]<br>0x530a246  mov r8,[rbp+0x1D8]<br>0x530a566  mov r8,[rbp+0x1D8]<br>0x530a584  mov r8,[rbp+0x1D8]<br>0x530a73c  mov r8,[rbp+0x1D8] | spilled 3rd arg, reloaded around calls [V] |
| clone rbp+0x1E0 | 8 | W | 0x530a1cb  mov qword ptr [rbp+0x1E0],0xFFFFFFFFFFFFFFFE | stored -2 sentinel [V] (frame guard pattern [I]) |
| clone rbp+0x250 | 8 | R | 0x530a215  mov rbx,[rbp+0x250] | 5th stack arg, owner/description holder used at [rbx+0x10]/[rbx+0x20] [I] |
| clone rbp+0x258 | 1 | R | 0x530a52b  movzx r12d,byte ptr [rbp+0x258] | byte arg, spilled to [rsp+0x48] [V] |
| clone rbp+0x260 | 1 | R | 0x530a523  movzx r13d,byte ptr [rbp+0x260] | byte arg, spilled to [rsp+0x50] [V] |
| clone rdx+0x0 | 8 | R | 0x530a47a  mov rax,[rdx] | - |
| clone rdx+0xC | 4 | RW | 0x530a474  lock dec dword ptr [rdx+0xC] | `lock dec` release site [V] |
| clone r8+0x0 | 8 | R | 0x530a1fe  mov rax,[r8] | - |
| clone r8+0x8 | 8 | R | 0x530a743  mov rsi,[r8+8] | ref-count object released at 0x530a74c/0x530a761 [I] |
| clone r14+0x0 | 8 | R | 0x530a2f6  mov rcx,[r14]<br>0x530a4e7  mov rcx,[r14]<br>0x530a557  mov rax,[r14]<br>0x530a574  mov rax,[r14] | object ptr / handle source loaded from r14 [V] |
| clone r14+0x8 | 8/4 | R/RW | 0x530a2e1  mov rax,[r14+8]<br>0x530a2ee  mov rax,[r14+8]<br>0x530a550  lock dec dword ptr [r14+8] | ref-count ptr loaded, then `lock dec` release [I] |
| clone r14+0xC | 4 | RW | 0x530a56d  lock dec dword ptr [r14+0xC] | second release site [V] |
| clone r14+0x10 | 8 | R | 0x530a31a  mov rcx,[r14+0x10] | object ptr stored to [rbp-0x10] [V] |
| clone r14+0x18 | 8 | R | 0x530a305  mov rax,[r14+0x18]<br>0x530a312  mov rax,[r14+0x18] | ref-count ptr stored to [rbp-8] [V] |
| clone r15+0x30 | 8 | R | 0x530a591  movsd xmm1,[r15+0x30] | last-entry pair copied to [rbp+0x1B0] [V] |
| clone r15+0x38 | 4 | R | 0x530a58b  movss xmm0,[r15+0x38] | last-entry float copied to [rbp+0x1B8] [V] |
| clone rsp+0x20 | 4 | W | 0x530a347  mov dword ptr [rsp+0x20],0<br>0x530a7d8  mov dword ptr [rsp+0x20],0 | stack arg spill (0) [V] |
| clone rsp+0x28 | 4/8 | W | 0x530a33f  mov dword ptr [rsp+0x28],0<br>0x530a5e7  mov [rsp+0x28],rax<br>0x530a7d3  mov [rsp+0x28],rax | stack arg spill (&[rbp+0x1C0], then 0xF2487E0) [V] |
| clone rsp+0x30 | 8 | W | 0x530a331  mov [rsp+0x30],rax<br>0x530a5db  mov [rsp+0x30],rax | stack arg spill (&[rbp+0x140], then &[rbp+0x1B0]) [V] |
| clone rsp+0x38 | 8 | W | 0x530a336  mov qword ptr [rsp+0x38],0<br>0x530a5cf  mov [rsp+0x38],rax | stack arg spill (0, then &[rbp+0x1D6]) [V] |
| clone rsp+0x40 | 8 | W | 0x530a5c3  mov [rsp+0x40],rax | stack arg spill (&[rbp+0x108]) [V] |
| clone rsp+0x48 | 1 | W | 0x530a5b7  mov [rsp+0x48],r12b | stack arg spill (byte [rbp+0x258]) [V] |
| clone rsp+0x50 | 1 | W | 0x530a5b2  mov [rsp+0x50],r13b | stack arg spill (byte [rbp+0x260]) [V] |
| clone gs:0x58 | 8 | R | 0x530a617  mov rdx,gs:[0x58] | TLS array base for the guard check at 0x530a624 [I] |

### ctor (0x668BF20..0x668C1CC)

| offset | size | direction | verbatim line(s) | meaning |
|--|--|--|--|--|
| ctor rcx+0x0 (this) | 8 | W | 0x668bf63  mov [rcx],r8 | r8 (4th arg) stored at [this] [V] |
| ctor rcx+0x0 (alloc glob) | 8 | R | 0x668c10b  mov rax,[rcx] | rcx=[0x1233E1A8] global; next loads [rax+8] (alloc fn slot) [V] |
| ctor rcx+0x0 (old handle) | 8 | R | 0x668c168  mov rax,[rcx] | - |
| ctor rbp+0x0 | 8 | W | 0x668bf35  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE | stored -2 sentinel [V] (frame guard pattern [I]) |
| ctor rbp-0x18 | 8 | W | 0x668bf6a  mov [rbp-0x18],rcx | this+8 saved as rcx for the 0x4DFB570 call [V] |
| ctor rbp-0x10 | 8 | W | 0x668c100  mov [rbp-0x10],rax | saved &[rsi+0xA8] in case-1 path [V] |
| ctor rbp-0x8 | 8 | W | 0x668c0f5  mov [rbp-8],rax | saved &[rsi+0x78] in case-1 path [V] |
| ctor rbp+0x70 | 8 | R | 0x668bf54  mov r12,[rbp+0x70] | 6th stack arg -> shared-handle source [I] |
| ctor rbp+0x78 | 8 | R | 0x668bf5f  mov rdx,[rbp+0x78] | 7th stack arg -> rdx of call 0x4DFB570 [V] |
| ctor rbp+0x80 | 8 | R | 0x668bf58  mov r13,[rbp+0x80] | 8th stack arg -> 3-float source (r13+0x0/0x4/0x8) [V] |
| ctor rbp+0x88 | 8 | R | 0x668bf4d  mov r15,[rbp+0x88] | 9th stack arg -> word source [V] |
| ctor rbp+0x90 | 8 | R | 0x668bf46  mov r14,[rbp+0x90] | 10th stack arg -> source data struct (fields +0x0/+0x10/+0x18/+0x20/+0x28/+0x30) [V] |
| ctor rbp+0x98 | 1 | R | 0x668c195  movzx ecx,byte ptr [rbp+0x98] | byte copied to rsi+0xC8 [V] |
| ctor rbp+0xA0 | 1 | R | 0x668c18e  movzx eax,byte ptr [rbp+0xA0] | byte copied to rsi+0xC9 [V] |
| ctor rbx+0x0 | 4 | R | 0x668bf73  movss xmm0,[rbx] | float 1 of r9 array -> rsi+0x18 [V] |
| ctor rbx+0x4 | 4 | R | 0x668bf7c  movss xmm0,[rbx+4] | float 2 -> rsi+0x1C [V] |
| ctor rbx+0x8 | 4 | R | 0x668bf86  movss xmm0,[rbx+8] | float 3 -> rsi+0x20 [V] |
| ctor rbx+0xC | 4 | R | 0x668bf90  movss xmm0,[rbx+0xC] | float 4 -> rsi+0x24 [V] |
| ctor rbx+0x10 | 4 | R | 0x668bf9a  movss xmm0,[rbx+0x10] | float 5 -> rsi+0x28 [V] |
| ctor rbx+0x14 | 4 | R | 0x668bfa4  movss xmm0,[rbx+0x14] | float 6 -> rsi+0x2C [V] |
| ctor rbx+0x18 | 4 | R | 0x668bfae  movss xmm0,[rbx+0x18] | float 7 -> rsi+0x30 [V] |
| ctor rbx+0x1C | 4 | R | 0x668bfb8  movss xmm0,[rbx+0x1C] | float 8 -> rsi+0x34 [V] |
| ctor rbx+0x20 | 4 | R | 0x668bfc2  movss xmm0,[rbx+0x20] | float 9 -> rsi+0x38 [V] |
| ctor rbx+0x24 | 4 | R | 0x668bfcc  movss xmm0,[rbx+0x24] | float 10 -> rsi+0x3C [V] |
| ctor rbx+0x28 | 4 | R | 0x668bfd6  movss xmm0,[rbx+0x28] | float 11 -> rsi+0x40 [V] |
| ctor rbx+0x2C | 4 | R | 0x668bfe0  movss xmm0,[rbx+0x2C] | float 12 -> rsi+0x44 [V] |
| ctor rbx+0x30 | 4 | R | 0x668bfea  movss xmm0,[rbx+0x30] | float 13 -> rsi+0x48 [V] |
| ctor rbx+0x34 | 4 | R | 0x668bff4  movss xmm0,[rbx+0x34] | float 14 -> rsi+0x4C [V] |
| ctor rbx+0x38 | 4 | R | 0x668bffe  movss xmm0,[rbx+0x38] | float 15 -> rsi+0x50 [V] |
| ctor rbx+0x3C | 4 | R | 0x668c008  movss xmm0,[rbx+0x3C] | float 16 -> rsi+0x54 [V] |
| ctor rsi+0x18 | 4 | W | 0x668bf77  movss [rsi+0x18],xmm0 | from [rbx+0x0] [V] |
| ctor rsi+0x1C | 4 | W | 0x668bf81  movss [rsi+0x1C],xmm0 | from [rbx+0x4] [V] |
| ctor rsi+0x20 | 4 | W | 0x668bf8b  movss [rsi+0x20],xmm0 | from [rbx+0x8] [V] |
| ctor rsi+0x24 | 4 | W | 0x668bf95  movss [rsi+0x24],xmm0 | from [rbx+0xC] [V] |
| ctor rsi+0x28 | 4 | W | 0x668bf9f  movss [rsi+0x28],xmm0 | from [rbx+0x10] [V] |
| ctor rsi+0x2C | 4 | W | 0x668bfa9  movss [rsi+0x2C],xmm0 | from [rbx+0x14] [V] |
| ctor rsi+0x30 | 4 | W | 0x668bfb3  movss [rsi+0x30],xmm0 | from [rbx+0x18] [V] |
| ctor rsi+0x34 | 4 | W | 0x668bfbd  movss [rsi+0x34],xmm0 | from [rbx+0x1C] [V] |
| ctor rsi+0x38 | 4 | W | 0x668bfc7  movss [rsi+0x38],xmm0 | from [rbx+0x20] [V] |
| ctor rsi+0x3C | 4 | W | 0x668bfd1  movss [rsi+0x3C],xmm0 | from [rbx+0x24] [V] |
| ctor rsi+0x40 | 4 | W | 0x668bfdb  movss [rsi+0x40],xmm0 | from [rbx+0x28] [V] |
| ctor rsi+0x44 | 4 | W | 0x668bfe5  movss [rsi+0x44],xmm0 | from [rbx+0x2C] [V] |
| ctor rsi+0x48 | 4 | W | 0x668bfef  movss [rsi+0x48],xmm0 | from [rbx+0x30] [V] |
| ctor rsi+0x4C | 4 | W | 0x668bff9  movss [rsi+0x4C],xmm0 | from [rbx+0x34] [V] |
| ctor rsi+0x50 | 4 | W | 0x668c003  movss [rsi+0x50],xmm0 | from [rbx+0x38] [V] |
| ctor rsi+0x54 | 4 | W | 0x668c00d  movss [rsi+0x54],xmm0 | from [rbx+0x3C] [V] |
| ctor r13+0x0 | 4 | R | 0x668c012  movss xmm0,[r13] | float A -> rsi+0x58 [V] |
| ctor r13+0x4 | 4 | R | 0x668c01d  movss xmm0,[r13+4] | float B -> rsi+0x5C [V] |
| ctor r13+0x8 | 4 | R | 0x668c028  movss xmm0,[r13+8] | float C -> rsi+0x60 [V] |
| ctor rsi+0x58 | 4 | W | 0x668c018  movss [rsi+0x58],xmm0 | from [r13+0x0] [V] |
| ctor rsi+0x5C | 4 | W | 0x668c023  movss [rsi+0x5C],xmm0 | from [r13+0x4] [V] |
| ctor rsi+0x60 | 4 | W | 0x668c02e  movss [rsi+0x60],xmm0 | from [r13+0x8] [V] |
| ctor rdi+0x20 | 8 | R | 0x668c033  mov rax,[rdi+0x20] | pointer then deref-copy of 16 bytes [V] |
| ctor rax+0x0 | 16/8 | R/W | 0x668c037  movups xmm0,[rax]<br>0x668c0df  mov [rax],rcx | 16-byte copy source ([rdi+0x20] target) at 0x668c037; rax=rsi+0xB0 store at 0x668c0df [V] |
| ctor rsi+0x64 | 16 | W | 0x668c03a  movups [rsi+0x64],xmm0 | 16 bytes from [[rdi+0x20]] [V] |
| ctor rsi+0x78 | 16/8 | W | 0x668c041  movups [rsi+0x78],xmm0<br>0x668c057  mov [rsi+0x78],rax | zeroed 16 bytes, then object ptr of the [r12] handle [V] |
| ctor rax+0x8 | 4/8 | RW/R | 0x668c04f  lock inc dword ptr [rax+8]<br>0x668c10e  mov rax,[rax+8]<br>0x668c16b  mov rax,[rax+8] | ref-count `lock inc` (r12 handle); the mov sites read vtable/size through other rax bindings [V] |
| ctor r12+0x0 | 8 | R | 0x668c053  mov rax,[r12] | object ptr stored to rsi+0x78 [V] |
| ctor r12+0x8 | 8 | R | 0x668c045  mov rax,[r12+8]<br>0x668c05b  mov rax,[r12+8] | ref-count ptr stored to rsi+0x80 [V] |
| ctor rsi+0x80 | 8 | W | 0x668c060  mov [rsi+0x80],rax | copy of [r12+8] [V] |
| ctor r15+0x0 | 2 | R | 0x668c067  movzx eax,word ptr [r15] | word copied to rsi+0x88 [V] |
| ctor rsi+0x88 | 2 | W | 0x668c06b  mov [rsi+0x88],ax | copy of [r15] word [V] |
| ctor r14+0x0 | 16 | R | 0x668c072  movups xmm0,[r14]<br>0x668c0e2  mov rax,[r14]<br>0x668c14b  mov rdx,[r14] | 0x668c072 copies 16 bytes to rsi+0x90; 0x668c0e2 runs after `add r14,0x28` (reads old [r14+0x28]); 0x668c14b reads the rebound r14 (case-1 object) [V] |
| ctor rsi+0x90 | 16 | W | 0x668c076  movups [rsi+0x90],xmm0 | 16 bytes from [r14] [V] |
| ctor r14+0x8 | 8 | R | 0x668c142  mov rax,[r14+8] | ref-count ptr of the case-1 object (r14 rebound at 0x668c13e) [V] |
| ctor r14+0x10 | 16/1 | R | 0x668c07d  movzx eax,byte ptr [r14+0x10]<br>0x668c17f  movups xmm0,[r14+0x10] | byte flag copied to rsi+0xA0 (r14 = arg5 struct); movups copies 16 bytes to [rdi+0x10] (r14 = case-1 object) [V] |
| ctor r14+0x18 | 8 | R | 0x668c0ae  mov rax,[r14+0x18]<br>0x668c13e  mov r14,[r14+0x18] | 0x668c0ae stores to rsi+0xA8; 0x668c13e rebinds r14 to that sub-object [V] |
| ctor r14+0x20 | 8 | R | 0x668c0d7  mov rcx,[r14+0x20] | object ptr stored to [rsi+0xB0] slot [V] |
| ctor r14+0x28 | 8 | R | 0x668c0ca  mov rcx,[r14+0x28] | ref-count ptr, `lock inc` at 0x668c0d3, stored to [rsi+0xB0] (rax=rsi+0xB0) [I] |
| ctor r14+0x30 | 1 | R | 0x668c08f  movzx ebx,byte ptr [r14+0x30] | byte selecting the switch (0..3 via table 0xF2BF670) [V] |
| ctor rcx+0x8 | 4 | RW | 0x668c0d3  lock inc dword ptr [rcx+8] | `lock inc` on [r14+0x28]'s ref-count [I] |
| ctor rax+0xC | 4 | RW | 0x668c14e  lock inc dword ptr [rax+0xC] | `lock inc` on case-1 object ref-count [I] |
| ctor rsi+0xA0 | 1 | W | 0x668c082  mov [rsi+0xA0],al | copy of byte [r14+0x10] [V] |
| ctor rsi+0xA8 | 8 | W | 0x668c0b2  mov [rsi+0xA8],rax<br>0x668c13b  mov [rax],rdi | case 0 stores [r14+0x18]; case 1 stores the new 0x20-byte object (rdi) [V] |
| ctor rsi+0xB0 | 16 | W | 0x668c0c3  movups [rsi+0xB0],xmm0 | zeroed 16 bytes (rax=rsi+0xB0 used for the [rax] store) [V] |
| ctor rsi+0xB8 | 8 | W | 0x668c0e5  mov [rsi+0xB8],rax | copy of old [r14+0x28] (after `add r14,0x28`) [V] |
| ctor rsi+0xC0 | 1 | W | 0x668c088  mov byte ptr [rsi+0xC0],0xFF<br>0x668c188  mov [rsi+0xC0],bl | 0xFF default; bl = switch byte [r14+0x30] [V] |
| ctor rdi+0x0 | 16/8 | W | 0x668c131  movups [rdi],xmm0<br>0x668c156  mov [rdi],rdx | new 0x20-byte object zeroed, then data ptr published [V] |
| ctor rdi+0x8 | 8 | R/W | 0x668c152  mov rcx,[rdi+8]<br>0x668c159  mov [rdi+8],rax<br>0x668c177  mov qword ptr [rdi+8],0 | ref-count slot: old read/released, new stored, or 0 [V] |
| ctor rdi+0x10 | 16 | W | 0x668c12d  movups [rdi+0x10],xmm0<br>0x668c184  movups [rdi+0x10],xmm0 | zeroed, then 16 bytes from [r14+0x10] [V] |
| ctor rcx+0xC | 4 | RW | 0x668c162  lock dec dword ptr [rcx+0xC] | `lock dec` release of the old [rdi+8] ref-count [I] |

### emplace (0x66B2B30..0x66B2DD8) — `rax` = `rcx` = output block (mov rax,rcx at 0x66b2b38); all output fields written [V]

| offset | size | direction | verbatim line(s) | meaning |
|--|--|--|--|--|
| emp rdx+0x0 | 8 | R | 0x66b2b5b  mov rcx,[rdx] | deref of 2nd arg, then [rcx+0x40] [V] |
| emp rcx+0x40 | 8 | R | 0x66b2b5e  mov rdx,[rcx+0x40] | description object pointer, all [rdx+...] reads follow [I] |
| emp rdx+0x180 | 1 | R | 0x66b2b72  movzx ecx,byte ptr [rdx+0x180] | byte A of the variant tests [V] |
| emp rdx+0x181 | 1 | R | 0x66b2b79  movzx r9d,byte ptr [rdx+0x181] | byte B of the variant tests [V] |
| emp rdx+0x184 | 1 | R | 0x66b2d7d  movzx ecx,byte ptr [rdx+0x184] | copied to [rax+0x4] [V] |
| emp rdx+0x185 | 1 | R | 0x66b2b65  cmp byte ptr [rdx+0x185],1 | gate for the whole variant chain [V] |
| emp rdx+0x188 | 1 | R | 0x66b2d87  movzx ecx,byte ptr [rdx+0x188] | copied to [rax+0xC], also ANDed into [rax+0xD] [V] |
| emp rdx+0x189 | 1 | R | 0x66b2c60  movzx ecx,byte ptr [rdx+0x189] | copied to [rax+0x54] [V] |
| emp rdx+0x18A | 1 | R | 0x66b2da3  movzx ecx,byte ptr [rdx+0x18A] | shifted-constant index -> [rax+0xE] [V] |
| emp rdx+0x18B | 1 | R | 0x66b2c74  movzx ecx,byte ptr [rdx+0x18B] | shift count for the 0x104070502080603 constant -> [rax+0x34] [V] |
| emp rdx+0x18C | 1 | R | 0x66b2c94  movzx r10d,byte ptr [rdx+0x18C] | 0xFE-biased LUT 0xF2BF1A4 index -> [rax+0x38] [V] |
| emp rdx+0x18D | 1 | R | 0x66b2cd7  movzx ebx,byte ptr [rdx+0x18D] | 0xFE-biased LUT index -> [rax+0x40] [V] |
| emp rdx+0x18E | 1 | R | 0x66b2cbd  movzx r10d,byte ptr [rdx+0x18E] | 0xFE-biased LUT index -> [rax+0x3C] [V] |
| emp rdx+0x18F | 1 | R | 0x66b2d18  movzx ecx,byte ptr [rdx+0x18F] | shift count -> [rax+0x44] [V] |
| emp rdx+0x190 | 1 | R | 0x66b2d02  movzx ecx,byte ptr [rdx+0x190] | 0xFE-biased LUT index -> [rax+0x48] [V] |
| emp rdx+0x191 | 1 | R | 0x66b2d3d  movzx ebx,byte ptr [rdx+0x191] | 0xFE-biased LUT index -> [rax+0x4C] [V] |
| emp rdx+0x192 | 1 | R | 0x66b2d1f  movzx ebx,byte ptr [rdx+0x192] | 0xFE-biased LUT index -> [rax+0x50] [V] |
| emp rdx+0x193 | 1 | R | 0x66b2d91  cmp byte ptr [rdx+0x193],0 | ANDed (as !0) into [rax+0xD] [V] |
| emp rdx+0x194 | 1 | R | 0x66b2dbf  movzx ecx,byte ptr [rdx+0x194] | copied to [rax+0x56] [V] |
| emp rdx+0x19C | 1 | R | 0x66b2c6a  movzx ecx,byte ptr [rdx+0x19C] | copied to [rax+0x55] [V] |
| emp rdx+0x1A8 | 1 | R | 0x66b2c14  movzx ecx,byte ptr [rdx+0x1A8] | byte mapped (1->2, 2->1, else 0) into [rax+0x8] [V] |
| emp rcx+0xE | 1 | W | 0x66b2b3b  mov byte ptr [rcx+0xE],2 | init value 2 [V] |
| emp rcx+0x10 | 4 | W | 0x66b2b3f  mov dword ptr [rcx+0x10],0 | init 0 [V] |
| emp rcx+0x14 | 1 | W | 0x66b2b46  mov byte ptr [rcx+0x14],0 | init 0 [V] |
| emp rcx+0x18 | 16 | W | 0x66b2b4d  movups [rcx+0x18],xmm0 | zeroed 16 bytes [V] |
| emp rcx+0x24 | 16 | W | 0x66b2b51  movups [rcx+0x24],xmm0 | zeroed 16 bytes [V] |
| emp rcx+0x54 | 2 | W | 0x66b2b55  mov word ptr [rcx+0x54],0 | init word 0 [V] |
| emp rax+0x0 | 4 | W | 0x66b2c11  mov [rax],r11d | variant code 0..9 [V] |
| emp rax+0x4 | 1 | W | 0x66b2d84  mov [rax+4],cl | copy of [rdx+0x184] [V] |
| emp rax+0x8 | 4 | W | 0x66b2c34  mov [rax+8],ecx | mapped value of [rdx+0x1A8] [V] |
| emp rax+0xC | 1 | W | 0x66b2d8e  mov [rax+0xC],cl | copy of [rdx+0x188] [V] |
| emp rax+0xD | 1 | W | 0x66b2d9f  mov [rax+0xD],r10b | ([rdx+0x188]!=0 && [rdx+0x193]!=0) [V] |
| emp rax+0xE | 1 | W | 0x66b2dbb  mov [rax+0xE],r9b | shifted-constant byte from [rdx+0x18A], fallback 2 [V] |
| emp rax+0x10 | 4 | W | 0x66b2c5d  mov [rax+0x10],ecx | dword LUT[0xF2BF190][r8b] [V] |
| emp rax+0x34 | 1 | W | 0x66b2cf5  mov [rax+0x34],cl | shifted-constant byte from [rdx+0x18B], fallback 2 [V] |
| emp rax+0x38 | 4 | W | 0x66b2cf8  mov [rax+0x38],esi | LUT 0xF2BF1A4 of [rdx+0x18C] [V] |
| emp rax+0x3C | 4 | W | 0x66b2cfb  mov [rax+0x3C],edi | LUT of [rdx+0x18E] [V] |
| emp rax+0x40 | 4 | W | 0x66b2cfe  mov [rax+0x40],r11d | LUT of [rdx+0x18D] [V] |
| emp rax+0x44 | 1 | W | 0x66b2d6e  mov [rax+0x44],dil | shifted-constant byte from [rdx+0x18F], fallback 2 [V] |
| emp rax+0x48 | 4 | W | 0x66b2d72  mov [rax+0x48],r10d | LUT of [rdx+0x190] [V] |
| emp rax+0x4C | 4 | W | 0x66b2d76  mov [rax+0x4C],r11d | LUT of [rdx+0x191] [V] |
| emp rax+0x50 | 4 | W | 0x66b2d7a  mov [rax+0x50],esi | LUT of [rdx+0x192] [V] |
| emp rax+0x54 | 1 | W | 0x66b2c67  mov [rax+0x54],cl | copy of [rdx+0x189] [V] |
| emp rax+0x55 | 1 | W | 0x66b2c71  mov [rax+0x55],cl | copy of [rdx+0x19C] [V] |
| emp rax+0x56 | 1 | W | 0x66b2dc6  mov [rax+0x56],cl | copy of [rdx+0x194] [V] |

## TOOL REQUESTS
None

<!--APPEND-->
