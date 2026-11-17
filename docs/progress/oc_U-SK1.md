## NEXT
DONE

# UNIT U-Sk1 — sub_6b84e60..6b852c2 (skinned_clone_6b84e60, chunk 1 of 9)

Source: docs/progress/_part_Sk1.txt — 240 instructions, 0x6b84e60..0x6b852c2.
Split into 7 phases of at most 40 instructions; every instruction of the slice is named in the phase prose below.
Table: one row per distinct [reg+off] offset, all sites listed; meaning is "-" unless an instruction or string shows it.

## Phase 1: 6b84e60..6b84efa
Prologue and argument capture: push rbp/r15/r14/r13/r12/rsi/rdi/rbx; sub rsp,0x3D8; lea rbp,[rsp+0x80]; mov qword [rbp+0x350],0xFFFFFFFFFFFFFFFE; cmp byte [rcx],1 then jne loc_6b86790 when it is not 1; mov r15,r9 / mov rsi,rdx / mov r14,rcx; pxor xmm0,xmm0; movdqa [rbp+0x2F0],xmm0; mov rax,[rdx+0x110]; test rax,rax and jne to lock inc dword [rax+8], then mov rax,[rsi+0x110] and jmp loc_6b84ebf (else xor eax,eax); mov rdx,[rsi+0x108]; mov [rbp+0x2F0],rdx and [rbp+0x2F8],rax; mov rcx,[rsi+0x118]; mov [rbp+0x300],rcx; test rdx,rdx; mov [rbp+0x308],r8; je, or cmp byte [rdx],1 / jne to loc_6b84f06; mov rax,[rcx]; mov rax,[rax+8]; call qword ptr [0xF99FFA0] (sub_eea6040); nop; mov r12d,eax; jmp loc_6b84f09; xor r12d,r12d.
  6b84e60  push rbp
  6b84e7b  mov qword ptr [rbp+0x350],0xFFFFFFFFFFFFFFFE
  6b84e86  cmp byte ptr [rcx],1                    ; R a0+0x0
  6b84e89  jne 0x6B86790                           ; -> loc_6b86790
  6b84ea4  mov rax,[rdx+0x110]                    ; R a1+0x110
  6b84eb0  lock inc dword ptr [rax+8]             ; W *(a1+0x110)+0x8
  6b84efa  call qword ptr [0xF99FFA0]             ; [data_f99ffa0] = sub_eea6040

## Phase 2: 6b84f00..6b84f9f
Branch join and guard dispatch: mov r12d,eax (or xor r12d,r12d at loc_6b84f06); mov rbx,[rbp+0x3D8]; mov rdi,[rbp+0x3D0]; test rbx,rbx / test r12b,r12b → loc_6b8503f if rbx==0 or r12b!=0; mov r12,rdi; lea rdi,[r14+0x20]; mov rcx,rdi; call sub_4def080; nop; test al,al → loc_6b8528c if al==0; mov eax,[r14+0x1F8]; and eax,2; mov rdx,[rbp+0x3C8]; mov rcx,[rdx+rax*8]; test rcx,rcx → loc_6b85272 if 0; cmp qword [rcx+0x40],0 → loc_6b85272 if 0; lea r8,[rdx+rax*8]; mov [rsp+0x20],r12; mov rcx,rbx / mov rdx,r15 / mov r9,rdi; call sub_6b86e80; nop; mov rdi,rax.
  6b84f09  mov rbx,[rbp+0x3D8]
  6b84f33  call 0x4DEF080                          ; -> sub_4def080
  6b84f3b  je 0x6B8528C                            ; -> loc_6b8528c
  6b84f5f  cmp qword ptr [rcx+0x40],0
  6b84f7c  call 0x6B86E80                          ; -> sub_6b86e80

## Phase 3: 6b84fa5..6b85056
Clone node init from sub_6b86e80 result: lea rcx,[r14+0x4E0]; mov byte [rbp+0x290],1; mov [rbp+0x60],r14; mov r13,[rax+0x10]; cmp r13,[rax+0x18] → loc_6b85450 if equal; movsxd rax,[r14+0x528]; mov [r13],r14; mov byte [r13+8],1; mov [r13+0x10],rax; mov rax,[rsi+0x30]; mov ecx,[rax+0x10]; mov [r13+0x28],ecx; movups xmm0,[rax]; movups [r13+0x18],xmm0; mov rax,[rsi+0x38]; mov ecx,[rax+0x10]; mov [r13+0x3C],ecx; movdqu xmm0,[rax]; movdqu [r13+0x2C],xmm0; lea rcx,[r13+0x40]; mov rdx,rsi; call sub_6b87e00; lea rcx,[r13+0x190]; pxor xmm0,xmm0; movdqu [r13+0x190],xmm0; mov qword [r13+0x1A0],0; lea r9,[r14+0x4E8]; mov rdx,[r14+0x4E8]; sub rdx,[r14+0x4E0]; sar rdx,6; lea r8,[r14+0x4E0]; call sub_6760560; nop; add qword [rdi+0x10],0x1A8; jmp loc_6b8528c. Alternate path loc_6b8503f: mov rax,[r14+0x10]; cmp rax,[r14+8] → loc_6b8517d if equal; xor eax,eax; xor ecx,ecx; jmp loc_6b85146; nop [rax+rax].
  6b84f97  mov r13,[rax+0x10]                     ; R ret@6b86e80+0x10
  6b84fc4  movups xmm0,[rax]
  6b84fd7  movdqu xmm0,[rax]
  6b84fe8  call 0x6B87E00                          ; -> sub_6b87e00
  6b8502c  call 0x6760560                          ; -> sub_6760560
  6b85032  add qword ptr [rdi+0x10],0x1A8          ; W ret@6b86e80+0x10
  6b85060  mov r8,[r8+0xB0]

## Phase 4: 6b85060..6b85139
Dword copy loop (0x40-byte stride): loc_6b85060: mov r8,[r8+0xB0]; mov r9,[r8+0x40]; movss xmm0,[rdx+rax]; movss [r9],xmm0; loc_6b85075: movss xmm0,[rdx+rax+4] → movss [r9+4],xmm0; +8 → [r9+8]; +0xC → [r9+0xC]; +0x10 → [r9+0x10]; +0x14 → [r9+0x14]; +0x18 → [r9+0x18]; +0x1C → [r9+0x1C]; +0x20 → [r9+0x20]; +0x24 → [r9+0x24]; +0x28 → [r9+0x28]; +0x2C → [r9+0x2C]; +0x30 → [r9+0x30]; +0x34 → [r9+0x34]; +0x38 → [r9+0x38]; movd xmm0,[rdx+rax+0x3C] → movd [r9+0x3C],xmm0; mov byte [r8+0x31],1; mov rdx,[r14+0x10]; sub rdx,[r14+8]; inc rcx; sar rdx,3; add rax,0x40; cmp rcx,rdx → je loc_6b8517d when counts match; loc_6b85146: mov r8,[rsi+0x20]; mov rdx,[r14+0x4E0]; cmp byte [r14+0x530],1 → jne loc_6b85060; mov r8,[r8+0xA8]; mov r9,[r8+0x40]; movss xmm0,[rdx+rax]; movss [r9+rax],xmm0; add r9,rax; jmp loc_6b85075.
  6b8506b  movss xmm0,[rdx+rax]
  6b85075  movss xmm0,[rdx+rax+4]
  6b8511d  movd xmm0,[rdx+rax+0x3C]
  6b85129  mov byte ptr [r8+0x31],1
  6b85151  cmp byte ptr [r14+0x530],1

## Phase 5: 6b8513d..6b851eb
loc_6b8517d: lea r13,[r14+0x20]; mov rcx,r13; call sub_4def080; nop; lea rbx,[r14+0x280]; test al,al; cmovne rbx,r13; mov rcx,rbx; call sub_4def080; nop; test al,al → loc_6b8670a; test r12b,r12b → loc_6b853bc if zero; pxor xmm0,xmm0; movdqu [rbp+0x2B8],xmm0; mov byte [rbp+0x2C8],0; movdqa [rbp+0x290],xmm0; movdqa [rbp+0x2A0],xmm0; mov byte [rbp+0x2B0],0; movdqa [rbp+0x2D0],xmm0; movdqa [rbp+0x2E0],xmm0; mov rax,[rdi]; test rax,rax → loc_6b85cab; mov r12,[rax]; test r12,r12 → loc_6b85cab.
  6b85184  call 0x4DEF080                          ; -> sub_4def080
  6b8519a  call 0x4DEF080                          ; -> sub_4def080
  6b851b5  movdqu [rbp+0x2B8],xmm0
  6b851eb  mov rax,[rdi]
  6b851f7  mov r12,[rax]

## Phase 6: 6b851f7..6b8529b
Version/table validation and refcount: mov eax,[0x128D8FC8]; mov ecx,[0x128767C8]; mov rdx,gs:[0x58]; mov rcx,[rdx+rcx*8]; cmp eax,[rcx+4] → jg loc_6b867a9; loc_6b85228: lock inc word [r12+0x10]; movzx eax,byte [r12+0x12]; test al,1 → je loc_6b85cab; mov rax,[rdi]; pxor xmm0,xmm0; movdqa [rbp+0x310],xmm0; mov rcx,[rax]; test rcx,rcx; if nonzero movzx ecx,word [rcx+0x10]; rcx=[rax+8]; test rcx → loc_6b854c2; lock inc dword [rcx+8]; mov rcx,[rax+8]; jmp loc_6b854c4. Error path loc_6b85272: lea r9,[0xF52AED4] ("Quad material doesn't exist"); mov cl,1; mov edx,3; mov r8d,0x1A; call sub_eaa30; nop. loc_6b8528c: lea rdi,[r14+0x280]; mov rcx,rdi; call sub_4def080; nop; test al,al → loc_6b8670a.
  6b8520f  mov rdx,gs:[0x58]
  6b8521c  cmp eax,[rcx+4]
  6b85228  lock inc word ptr [r12+0x10]
  6b8522f  movzx eax,byte ptr [r12+0x12]
  6b85244  movdqa [rbp+0x310],xmm0
  6b85272  lea r9,[0xF52AED4]                      ; [data_f52aed4] "Quad material doesn't exist"
  6b85286  call 0xEAA30                            ; -> sub_eaa30
  6b85296  call 0x4DEF080                          ; -> sub_4def080

## Phase 7: 6b8529c..6b852c2
Tail: test al,al → loc_6b8670a if al==0; mov eax,[r14+0x458]; and eax,2; mov rdx,[rbp+0x3C8]; mov rcx,[rdx+rax*8]; test rcx,rcx → loc_6b8539d if 0; cmp qword [rcx+0x40],0.
  6b852a4  mov eax,[r14+0x458]
  6b852b5  mov rcx,[rdx+rax*8]
  6b852c2  cmp qword ptr [rcx+0x40],0

## [reg+off] field map (one row per distinct offset, all sites listed)

| offset | size | direction | sites (verbatim `0xRVA  instr`) | meaning |
|--------|------|-----------|-----------------------------------|---------|
| 0x0 | 16,8,4,1 | R/W |   0x6b84e86  cmp byte ptr [rcx],1                    ; R a0+0x0\n   0x6b84ef3  mov rax,[rcx]\n   0x6b84fc4  movups xmm0,[rax]\n   0x6b84fd7  movdqu xmm0,[rax]\n   0x6b8506b  movss xmm0,[rdx+rax]\n   0x6b85070  movss [r9],xmm0\n   0x6b8516a  movss xmm0,[rdx+rax]\n   0x6b851eb  mov rax,[rdi]\n   0x6b851f7  mov r12,[rax]\n   0x6b8524c  mov rcx,[rax] | - |
| 0x4 | 4 | R |   0x6b85075  movss xmm0,[rdx+rax+4]\n   0x6b8521c  cmp eax,[rcx+4] | - |
| 0x8 | 4/8 | R/W |   0x6b84eb0  lock inc dword ptr [rax+8]             ; W *(a1+0x110)+0x8\n   0x6b84ef6  mov rax,[rax+8]\n   0x6b85043  cmp rax,[r14+8]\n   0x6b85132  sub rdx,[r14+8]\n   0x6b85258  mov rcx,[rax+8]\n   0x6b85265  lock inc dword ptr [rcx+8]\n   0x6b85269  mov rcx,[rax+8] | - |
| 0xC | 4 | R/W |   0x6b8508d  movss xmm0,[rdx+rax+0xC]\n   0x6b85093  movss [r9+0xC],xmm0 | - |
| 0x10 | 8/4/2 | R/W |   0x6b84f97  mov r13,[rax+0x10]                     ; R ret@6b86e80+0x10\n   0x6b84fb5  mov [r13+0x10],rax                     ; W *(ret@6b86e80+0x10)+0x10\n   0x6b84fbd  mov ecx,[rax+0x10]\n   0x6b84fd0  mov ecx,[rax+0x10]\n   0x6b8503f  mov rax,[r14+0x10]\n   0x6b85032  add qword ptr [rdi+0x10],0x1A8         ; W ret@6b86e80+0x10\n   0x6b8512e  mov rdx,[r14+0x10]\n   0x6b85254  movzx ecx,word ptr [rcx+0x10] | - |
| 0x12 | 1 | R |   0x6b8522f  movzx eax,byte ptr [r12+0x12] | - |
| 0x14 | 4 | R/W |   0x6b850a5  movss xmm0,[rdx+rax+0x14]\n   0x6b850ab  movss [r9+0x14],xmm0 | - |
| 0x18 | 16,4 | R/W |   0x6b84fc7  movups [r13+0x18],xmm0                 ; W *(ret@6b86e80+0x10)+0x18\n   0x6b850b1  movss xmm0,[rdx+rax+0x18]\n   0x6b850b7  movss [r9+0x18],xmm0 | - |
| 0x1C | 4 | R/W |   0x6b850bd  movss xmm0,[rdx+rax+0x1C]\n   0x6b850c3  movss [r9+0x1C],xmm0 | - |
| 0x20 | 4,8 | R/W |   0x6b84f6e  mov [rsp+0x20],r12\n   0x6b850c9  movss xmm0,[rdx+rax+0x20]\n   0x6b850cf  movss [r9+0x20],xmm0\n   0x6b85146  mov r8,[rsi+0x20] | - |
| 0x24 | 4 | R/W |   0x6b850d5  movss xmm0,[rdx+rax+0x24]\n   0x6b850db  movss [r9+0x24],xmm0 | - |
| 0x28 | 4 | R/W |   0x6b84fc0  mov [r13+0x28],ecx                     ; W *(ret@6b86e80+0x10)+0x28\n   0x6b850e1  movss xmm0,[rdx+rax+0x28]\n   0x6b850e7  movss [r9+0x28],xmm0 | - |
| 0x2C | 16,4 | R/W |   0x6b84fdb  movdqu [r13+0x2C],xmm0                 ; W *(ret@6b86e80+0x10)+0x2C\n   0x6b850ed  movss xmm0,[rdx+rax+0x2C]\n   0x6b850f3  movss [r9+0x2C],xmm0 | - |
| 0x30 | 4,8 | R/W |   0x6b84fb9  mov rax,[rsi+0x30]\n   0x6b850f9  movss xmm0,[rdx+rax+0x30]\n   0x6b850ff  movss [r9+0x30],xmm0 | - |
| 0x31 | 1 | W |   0x6b85129  mov byte ptr [r8+0x31],1 | - |
| 0x34 | 4 | R/W |   0x6b85105  movss xmm0,[rdx+rax+0x34]\n   0x6b8510b  movss [r9+0x34],xmm0 | - |
| 0x38 | 4,8 | R/W |   0x6b84fcc  mov rax,[rsi+0x38]\n   0x6b85111  movss xmm0,[rdx+rax+0x38]\n   0x6b85117  movss [r9+0x38],xmm0 | - |
| 0x3C | 4 | R/W |   0x6b84fd3  mov [r13+0x3C],ecx                     ; W *(ret@6b86e80+0x10)+0x3C\n   0x6b8511d  movd xmm0,[rdx+rax+0x3C]\n   0x6b85123  movd [r9+0x3C],xmm0 | - |
| 0x40 | 8 | R |   0x6b84f5f  cmp qword ptr [rcx+0x40],0\n   0x6b85067  mov r9,[r8+0x40]\n   0x6b85166  mov r9,[r8+0x40]\n   0x6b852c2  cmp qword ptr [rcx+0x40],0 | - |
| 0x58 | 8 | R |   0x6b8520f  mov rdx,gs:[0x58] | - |
| 0x60 | 8 | W |   0x6b84f93  mov [rbp+0x60],r14 | - |
| 0xA8 | 8 | R |   0x6b8515f  mov r8,[r8+0xA8] | - |
| 0xB0 | 8 | R |   0x6b85060  mov r8,[r8+0xB0] | - |
| 0x110 | 8 | R |   0x6b84ea4  mov rax,[rdx+0x110]                    ; R a1+0x110\n   0x6b84eb4  mov rax,[rsi+0x110] | - |
| 0x118 | 8 | R |   0x6b84ed4  mov rcx,[rsi+0x118] | - |
| 0x1F8 | 4 | R |   0x6b84f41  mov eax,[r14+0x1F8] | - |
| 0x290 | 16,1 | W |   0x6b84f8c  mov byte ptr [rbp+0x290],1\n   0x6b851c4  movdqa [rbp+0x290],xmm0 | - |
| 0x2A0 | 16 | W |   0x6b851cc  movdqa [rbp+0x2A0],xmm0 | - |
| 0x2B0 | 1 | W |   0x6b851d4  mov byte ptr [rbp+0x2B0],0 | - |
| 0x2B8 | 16 | W |   0x6b851b5  movdqu [rbp+0x2B8],xmm0 | - |
| 0x2C8 | 1 | W |   0x6b851bd  mov byte ptr [rbp+0x2C8],0 | - |
| 0x2D0 | 16 | W |   0x6b851db  movdqa [rbp+0x2D0],xmm0 | - |
| 0x2E0 | 16 | W |   0x6b851e3  movdqa [rbp+0x2E0],xmm0 | - |
| 0x2F0 | 16,8 | W |   0x6b84e9c  movdqa [rbp+0x2F0],xmm0\n   0x6b84ec6  mov [rbp+0x2F0],rdx | - |
| 0x2F8 | 8 | W |   0x6b84ecd  mov [rbp+0x2F8],rax | - |
| 0x300 | 8 | W |   0x6b84edb  mov [rbp+0x300],rcx | - |
| 0x308 | 8 | W |   0x6b84ee5  mov [rbp+0x308],r8 | - |
| 0x310 | 16 | W |   0x6b85244  movdqa [rbp+0x310],xmm0 | - |
| 0x350 | 8 | W |   0x6b84e7b  mov qword ptr [rbp+0x350],0xFFFFFFFFFFFFFFFE | - |
| 0x3C8 | 8 | R |   0x6b84f4b  mov rdx,[rbp+0x3C8]\n   0x6b852ae  mov rdx,[rbp+0x3C8] | - |
| 0x3D0 | 8 | R |   0x6b84f10  mov rdi,[rbp+0x3D0] | - |
| 0x3D8 | 8 | R |   0x6b84f09  mov rbx,[rbp+0x3D8] | - |
| 0x4E0 | 8 | R |   0x6b8501a  sub rdx,[r14+0x4E0]\n   0x6b8514a  mov rdx,[r14+0x4E0] | - |
| 0x4E8 | 8 | R |   0x6b85013  mov rdx,[r14+0x4E8] | - |
| 0x528 | 4 | R |   0x6b84fa5  movsxd rax,[r14+0x528] | - |
| 0x530 | 1 | R |   0x6b85151  cmp byte ptr [r14+0x530],1 | - |

## APPENDIX: verbatim quote of every instruction in the slice (instruction-complete)
Each line below is `0xRVA  instr` copied verbatim from docs/progress/_part_Sk1.txt (rdis output),
so every instruction of 0x6b84e60..0x6b852c2 is quoted somewhere in this file.
0x6b84e60  push rbp
0x6b84e61  push r15
0x6b84e63  push r14
0x6b84e65  push r13
0x6b84e67  push r12
0x6b84e69  push rsi
0x6b84e6a  push rdi
0x6b84e6b  push rbx
0x6b84e6c  sub rsp,0x3D8
0x6b84e73  lea rbp,[rsp+0x80]
0x6b84e89  jne 0x6B86790                                 ; -> loc_6b86790
0x6b84e8f  mov r15,r9
0x6b84e92  mov rsi,rdx
0x6b84e95  mov r14,rcx
0x6b84e98  pxor xmm0,xmm0
0x6b84eab  test rax,rax
0x6b84eae  je short 0x6B84EBD                            ; -> loc_6b84ebd
0x6b84ebb  jmp short 0x6B84EBF                           ; -> loc_6b84ebf
0x6b84ebd  xor eax,eax
0x6b84ebf  mov rdx,[rsi+0x108]
0x6b84ee2  test rdx,rdx
0x6b84eec  je short 0x6B84F06                            ; -> loc_6b84f06
0x6b84eee  cmp byte ptr [rdx],1
0x6b84ef1  jne short 0x6B84F06                           ; -> loc_6b84f06
0x6b84efa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6b84f00  nop
0x6b84f01  mov r12d,eax
0x6b84f04  jmp short 0x6B84F09                           ; -> loc_6b84f09
0x6b84f06  xor r12d,r12d
0x6b84f17  test rbx,rbx
0x6b84f1a  je 0x6B8503F                                  ; -> loc_6b8503f
0x6b84f20  test r12b,r12b
0x6b84f23  jne 0x6B8503F                                 ; -> loc_6b8503f
0x6b84f29  mov r12,rdi
0x6b84f2c  lea rdi,[r14+0x20]
0x6b84f30  mov rcx,rdi
0x6b84f33  call 0x4DEF080                                ; -> sub_4def080
0x6b84f38  nop
0x6b84f39  test al,al
0x6b84f3b  je 0x6B8528C                                  ; -> loc_6b8528c
0x6b84f48  and eax,2
0x6b84f52  mov rcx,[rdx+rax*8]
0x6b84f56  test rcx,rcx
0x6b84f59  je 0x6B85272                                  ; -> loc_6b85272
0x6b84f64  je 0x6B85272                                  ; -> loc_6b85272
0x6b84f6a  lea r8,[rdx+rax*8]
0x6b84f73  mov rcx,rbx
0x6b84f76  mov rdx,r15
0x6b84f79  mov r9,rdi
0x6b84f7c  call 0x6B86E80                                ; -> sub_6b86e80
0x6b84f81  nop
0x6b84f82  mov rdi,rax
0x6b84f85  lea rcx,[r14+0x4E0]
0x6b84f9b  cmp r13,[rax+0x18]                            ; R ret@6b86e80+0x18
0x6b84f9f  je 0x6B85450                                  ; -> loc_6b85450
0x6b84fac  mov [r13],r14                                 ; W *(ret@6b86e80+0x10)+0x0
0x6b84fb0  mov byte ptr [r13+8],1                        ; W *(ret@6b86e80+0x10)+0x8
0x6b84fe1  lea rcx,[r13+0x40]                            ; R *(ret@6b86e80+0x10)+0x40
0x6b84fe5  mov rdx,rsi
0x6b84fe8  call 0x6B87E00                                ; -> sub_6b87e00
0x6b84fed  lea rcx,[r13+0x190]                           ; R *(ret@6b86e80+0x10)+0x190
0x6b84ff4  pxor xmm0,xmm0
0x6b84ff8  movdqu [r13+0x190],xmm0                       ; W *(ret@6b86e80+0x10)+0x190
0x6b85001  mov qword ptr [r13+0x1A0],0                   ; W *(ret@6b86e80+0x10)+0x1A0
0x6b8500c  lea r9,[r14+0x4E8]
0x6b85021  sar rdx,6
0x6b85025  lea r8,[r14+0x4E0]
0x6b8502c  call 0x6760560                                ; -> sub_6760560
0x6b85031  nop
0x6b8503a  jmp 0x6B8528C                                 ; -> loc_6b8528c
0x6b85047  je 0x6B8517D                                  ; -> loc_6b8517d
0x6b8504d  xor eax,eax
0x6b8504f  xor ecx,ecx
0x6b85051  jmp 0x6B85146                                 ; -> loc_6b85146
0x6b85056  nop [rax+rax]
0x6b8507b  movss [r9+4],xmm0
0x6b85081  movss xmm0,[rdx+rax+8]
0x6b85087  movss [r9+8],xmm0
0x6b85099  movss xmm0,[rdx+rax+0x10]
0x6b8509f  movss [r9+0x10],xmm0
0x6b85136  inc rcx
0x6b85139  sar rdx,3
0x6b8513d  add rax,0x40
0x6b85141  cmp rcx,rdx
0x6b85144  je short 0x6B8517D                            ; -> loc_6b8517d
0x6b85159  jne 0x6B85060                                 ; -> loc_6b85060
0x6b8516f  movss [r9+rax],xmm0
0x6b85175  add r9,rax
0x6b85178  jmp 0x6B85075                                 ; -> loc_6b85075
0x6b8517d  lea r13,[r14+0x20]
0x6b85181  mov rcx,r13
0x6b85184  call 0x4DEF080                                ; -> sub_4def080
0x6b85189  nop
0x6b8518a  lea rbx,[r14+0x280]
0x6b85191  test al,al
0x6b85193  cmovne rbx,r13
0x6b85197  mov rcx,rbx
0x6b8519a  call 0x4DEF080                                ; -> sub_4def080
0x6b8519f  nop
0x6b851a0  test al,al
0x6b851a2  je 0x6B8670A                                  ; -> loc_6b8670a
0x6b851a8  test r12b,r12b
0x6b851ab  je 0x6B853BC                                  ; -> loc_6b853bc
0x6b851b1  pxor xmm0,xmm0
0x6b851ee  test rax,rax
0x6b851f1  je 0x6B85CAB                                  ; -> loc_6b85cab
0x6b851fa  test r12,r12
0x6b851fd  je 0x6B85CAB                                  ; -> loc_6b85cab
0x6b85203  mov eax,[0x128D8FC8]                          ; [data_128d8fc8]
0x6b85209  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6b85218  mov rcx,[rdx+rcx*8]
0x6b85222  jg 0x6B867A9                                  ; -> loc_6b867a9
0x6b85228  lock inc word ptr [r12+0x10]
0x6b85235  test al,1
0x6b85237  je 0x6B85CAB                                  ; -> loc_6b85cab
0x6b8523d  mov rax,[rdi]
0x6b85240  pxor xmm0,xmm0
0x6b8524f  test rcx,rcx
0x6b85252  je short 0x6B85258                            ; -> loc_6b85258
0x6b8525c  test rcx,rcx
0x6b8525f  je 0x6B854C2                                  ; -> loc_6b854c2
0x6b8526d  jmp 0x6B854C4                                 ; -> loc_6b854c4
0x6b85272  lea r9,[0xF52AED4]                            ; [data_f52aed4] "Quad material doesn't exist"
0x6b85279  mov cl,1
0x6b8527b  mov edx,3
0x6b85280  mov r8d,0x1A
0x6b85286  call 0xEAA30                                  ; -> sub_eaa30
0x6b8528b  nop
0x6b8528c  lea rdi,[r14+0x280]
0x6b85293  mov rcx,rdi
0x6b85296  call 0x4DEF080                                ; -> sub_4def080
0x6b8529b  nop
0x6b8529c  test al,al
0x6b8529e  je 0x6B8670A                                  ; -> loc_6b8670a
0x6b852a4  mov eax,[r14+0x458]
0x6b852ab  and eax,2
0x6b852b5  mov rcx,[rdx+rax*8]
0x6b852b9  test rcx,rcx
0x6b852bc  je 0x6B8539D                                  ; -> loc_6b8539d

## TOOL REQUESTS
None

